struct pidParameters
{
	float Kp;
	float Ki;
	float Kd;
	float Kf;
	float Tsampling;
	float ReferenceSetpoint;
	float feedback;
	float error;
	float error_new;
	float error_old;
	float integral_old;
	float integral_new;
	float derivitive;
	float absolute_error;
	float saturated;
	float pidoutput;
	float outmax;
	float outmin;
	float scalefactor;
}   pidParams;


void Base_vtg_pid1()
{
 //#################################################################################################################	    
      newpulseduty=100000.0/pulsefreq;
      if(newpulseduty>=10000)
      newpulseduty=10000;
      else if(newpulseduty<=400) //333)
      newpulseduty=400;//333;
      
      newpidstepbasetime=newpulseduty-260;//(45+15+100+100)=260
      //dispnum2=newpidstepbasetime/10.0;
      if(newpidstepbasetime<=100)//260+100 
      {
    	//newpidstepbasetime=newpidstepbasetime-260;
    	newsteptime=newpidstepbasetime;//newpidstepbasetime;  //fix decay time
		if(newsteptime<30)
		newsteptime=30;
	    newbasetime=1;
	    shiftbvtgf=1;
       }
       else
       {
    	 newsteptime=100;
	     newbasetime=newpidstepbasetime-newsteptime;//(newsteptime+100); //100 FOR DECAY TIME
	     shiftbvtgf=0;
       }
		PID_basetm		=newbasetime>>1;///5;
		PID_steptm		=newsteptime>>1;///5;	
		
		PID_pulsetm		=OPEN_pulsetm;
		PID_pulserisetm	=OPEN_pulserisetm;
		PID_pulsefalltm	=OPEN_pulsefalltm;
		PID_startpulsetm=OPEN_startpulsetm;
		PID_uppdaccount	=FRQ_uppdaccount;//OPEN_uppdaccount;
		PID_pdaccount	=FRQ_pdaccount;//OPEN_pdaccount;
		PID_sdaccount	=FRQ_sdaccount;//(newstepamp*CCSLOPENEW)-CCOFFSETNEW;
		PID_bdaccount	=FRQ_bdaccount;//(newbaseamp*CCSLOPENEW)-CCOFFSETNEW;
		PID_newupstep	=(PID_uppdaccount-PID_bdaccount)/pulserisetm;
		PID_newdownstep	=(PID_pdaccount-PID_sdaccount)/pulsefalltm;
//#################################################################################################################	    
}	
void Base_vtg_pid()
{
	unsigned int newstepamp=0,newbaseamp=0,intpidoutput=0;
	signed long scaled_val=0;
	float powercostant=15000.0,bkpgain=20.0,bkigain=0.1,bkdgain=0.5;//6.0; //actually 150 power=IB(A)*TB(msec)
	//bkpgain=10.0;//(210.0-para.pmigmode.setwspeed)/10.0; //20
	//pidParams.Kp=150.0;//0.5;//0.1;
	bkpgain=pidParams.Kp;
	bkigain=pidParams.Ki/10.0;//=1.0;//0.1;//0.08;//0.01;//0.02;
	bkdgain=pidParams.Kd/10.0;//=1.0;//0.1;//0.08;//0.01;//0.02;
	//pidParams.Kd=0.50;//0.02;
	
	
	pidParams.Tsampling=1.0;
	powercostant=Basepowerconstant;//+Steppowerconstant;
	
	pidParams.ReferenceSetpoint	=parcbasevtg;//setmvtg;
	pidParams.feedback			=CVOLTAGE;//actualmvtg;
	pidParams.error 			=pidParams.ReferenceSetpoint - pidParams.feedback;
	pidParams.absolute_error	=abs(pidParams.error);
	pidParams.outmax			=50000.0;
	pidParams.scalefactor		=pidParams.outmax/pidmaxbaseamp;//250.0;//280.0;
    pidParams.outmin			=pidParams.scalefactor*pidminbaseamp;//-(pidParams.outmax-(pidParams.scalefactor*minbaseamp));//-(pidParams.outmax-(pidParams.scalefactor*minoutputfreq));//0.0;
    pidParams.error_new			=pidParams.error;
    if(firsttimef==0)
    {
		firsttimef=1;
		pidParams.integral_old=0;//pidParams.outmin/bkigain;
		pidParams.error_new=0;
		pidParams.error_old=0;
	} 
    {
		pidParams.integral_new = pidParams.integral_old + bkigain*(pidParams.error_new + pidParams.error_old)*pidParams.Tsampling/2.0; // Area of the trapezoid
		//pidParams.integral_new = pidParams.integral_old + pidParams.Ki*(pidParams.error_new + pidParams.error_old)*pidParams.Tsampling/2.0; // Area of the trapezoid
		//if((pidParams.integral_new >= pidParams.outmax) || (pidParams.integral_new < pidParams.outmin)) //-pidParams1.outmax1))// This is anti wind up protect
		//pidParams.integral_new = pidParams.integral_old;
		
		if(pidParams.integral_new >= pidParams.outmax) 
			pidParams.integral_new = pidParams.outmax;
		else if (pidParams.integral_new < pidParams.outmin)
		   pidParams.integral_new = pidParams.outmin;
		    
		//pidParams.integral_new = pidParams.integral_old;
		//pidParams.pidoutput	 = pidParams.Kp*pidParams.error_new + bkdgain*(pidParams.error_new-pidParams.error_old)/pidParams.Tsampling + pidParams.integral_new;
		pidParams.pidoutput	 	  = bkpgain*pidParams.error_new + bkdgain*(pidParams.error_new-pidParams.error_old)/pidParams.Tsampling + pidParams.integral_new;
		pidParams.integral_old    = pidParams.integral_new;
		pidParams.error_old 	  = pidParams.error_new;
	}
	
	if(pidParams.pidoutput >= pidParams.outmax)
	{
		pidParams.pidoutput = pidParams.outmax;
	}
	else if(pidParams.pidoutput < pidParams.outmin) 
	{
		pidParams.pidoutput = pidParams.outmin;
	}
	intpidoutput=pidParams.pidoutput;
	OC3RS=intpidoutput>>5;
	
	scaled_val=(pidParams.pidoutput/pidParams.scalefactor); 
    
    if(scaled_val<pidminbaseamp)
    scaled_val=pidminbaseamp;
    else if(scaled_val>pidmaxbaseamp)
    scaled_val=pidmaxbaseamp;
   
    scaled_val=baseamp;						//for testing purpose only
    newbaseamp=scaled_val;
   
    //dispnum1=newbaseamp;
    //dispnewbaseamp=newbaseamp;   
    //newbasetime		=powercostant/scaled_val;
    //dispnum1=Peakpowerconstant/100.0;
    //dispnum2=powercostant/100.0;
    newpidstepbasetime=100000/pulsefreq;// powercostant/scaled_val;
    //newpidstepbasetime	=powercostant/pulsefreq;//scaled_val;
    
    dispnum2=newpidstepbasetime/10.0;
    if(newpidstepbasetime<201) //130)
    {
    	if(newpidstepbasetime<130)
    	newpidstepbasetime=130;
    	
    	newpidstepbasetime=newpidstepbasetime-100; //fix decay time
    	newsteptime=newpidstepbasetime;  //fix decay time
		if(newsteptime<30)
		newsteptime=30;
	    newbasetime=1;
	    shiftbvtgf=1;
    }
    else
    {
    	newsteptime=100;//250;//100;
	    newbasetime=newpidstepbasetime-(newsteptime+100); //100 FOR DECAY TIME
	    shiftbvtgf=0;
    }
    
   /* 
    if(newpidstepbasetime >200)//100
    {
	    newsteptime=100;
	    newbasetime=newpidstepbasetime-(newsteptime+100); //100 FOR DECAY TIME
	    shiftbvtgf=0;
	}
	else if(newpidstepbasetime >100)
	{
		newsteptime=newpidstepbasetime-100;
		if(newsteptime<30)
		newsteptime=30;
	    newbasetime=1;
	    shiftbvtgf=1;
	}    
	else
	{
	}
	*/	
   
    if((program_number ==21) ||(program_number ==20))   //for 5356 alu wire no step current
    {
	     if(newbaseamp<=30)
	     {
		     //newstepamp=newbaseamp*2.0;
		     //if(newstepamp<=60)
		     newstepamp=40;
		 }
		 else
		 { 
	     	newstepamp=newbaseamp;
   		 }    	
   		 //newstepamp=100;
   	 //newbasetime=newbasetime-newsteptime;  //to run step routine in switch case 
	} 
    else
    {    
    	if(refstepamp>=newbaseamp)
    		newstepamp=refstepamp;
    	else
    	newstepamp=newbaseamp;
    }    
    
    
    
    PID_basetm		=newbasetime>>1;///5;
	PID_steptm		=newsteptime>>1;///5;	
    
   	//dispnum1=PID_basetm;
   	//dispnum2=newbasetime/10.0;
   	
      
	setpidbamp=scaled_val;
	
	//disp_newbaseamp=newbaseamp;	
	if(newbaseamp<=15) //20) //30)
	newbaseamp=15;//20;
	PID_pulsetm		=OPEN_pulsetm;
	PID_pulserisetm	=OPEN_pulserisetm;
	PID_pulsefalltm	=OPEN_pulsefalltm;
	PID_startpulsetm=OPEN_startpulsetm;
	PID_uppdaccount	=OPEN_uppdaccount;
	PID_pdaccount	=OPEN_pdaccount;
	PID_sdaccount	=FRQ_sdaccount;//(newstepamp*CCSLOPENEW)-CCOFFSETNEW;
	PID_bdaccount	=FRQ_bdaccount;//(newbaseamp*CCSLOPENEW)-CCOFFSETNEW;
	PID_newupstep	=(PID_uppdaccount-PID_bdaccount)/pulserisetm;
	PID_newdownstep	=(PID_pdaccount-PID_sdaccount)/pulsefalltm;
	
	//FRQ_sdaccount	 	=(FRQ_stepamp*CCSLOPENEW)  -CCOFFSETNEW;
	//FRQ_bdaccount
	
}	


struct INT_sckpidParameters
{
  /* unsigned int INT_sckKp;
   unsigned int INT_sckKi;
   unsigned int INT_sckKd;
   unsigned int INT_sckKf;
   unsigned int INT_sckTsampling;
   
   signed long INT_sckReferenceSetpoint;
   signed long INT_sckfeedback;
   signed long INT_sckerror;
   signed long INT_sckerror_new;
   signed long INT_sckerror_old;
   signed long INT_sckintegral_old;
   signed long INT_sckintegral_new;
   signed long INT_sckderivitive;
   signed long INT_sckabsolute_error;
   signed long INT_scksaturated;
   signed long INT_sckpidoutput;
   signed long INT_sckoutmax;
   signed long INT_sckoutmin;
   signed long INT_sckscalefactor;
   */
   
   int INT_sckKp;
   int INT_sckKi;
   int INT_sckKd;
   int INT_sckKf;
   int INT_sckTsampling;
   
   int INT_sckReferenceSetpoint;
   int INT_sckfeedback;
   int INT_sckerror;
   int INT_sckerror_new;
   int INT_sckerror_old;
   int INT_sckintegral_old;
   int INT_sckintegral_new;
   int INT_sckderivitive;
   int INT_sckabsolute_error;
   int INT_scksaturated;
   int INT_sckpidoutput;
   int INT_sckoutmax;
   int INT_sckoutmin;
   int INT_sckscalefactor;
}   INT_sckpidParams;


void INT_sck_voltage_pid()
{
   unsigned int INT_sckscaled_val=0;
   float fans=0.0;
   if(weldmode=='M')
   {
   	  INT_sckpidParams.INT_sckKp=100;//0;//intkp;//2;//pidParams1.Kp1;//pidkp;//pidParams1.Kp1;//50.0;//40.0;//20.0//10.0 //100.0;// pidParams1.Kp1
      INT_sckpidParams.INT_sckKi=5;  //intki;//4;//pidParams1.Ki1;//pidki;//pidParams1.Ki1;//5.0;//10.0;//2.0;//1.0 //0.5;//0.2;
      INT_sckpidParams.INT_sckKd=6;  //intkd;//1;//pidParams1.Kd1;//pidkd;//pidParams1.Kd1;//p120.0;//10.0 ;2.0;//0.50;//0.02;
      INT_sckpidParams.INT_sckTsampling=1;

      INT_sckpidParams.INT_sckReferenceSetpoint=80;//160;//para.migmode.setvoltage>>1;//160.0;//SCKVOLTAGE;//parcbasevtg;//setmvtg;
      INT_sckpidParams.INT_sckfeedback=SCKVOLTAGE>>1;//CVOLTAGE;//actualmvtg;
      INT_sckpidParams.INT_sckerror =INT_sckpidParams.INT_sckReferenceSetpoint - INT_sckpidParams.INT_sckfeedback;
      //sckpidParams.sckabsolute_error=abs(sckpidParams.sckerror);
      INT_sckpidParams.INT_sckoutmax=25000;//56000.0;
      
   	  //sckpidParams.sckscalefactor=sckpidParams.sckoutmax/(para.mmamode.setcurrent*(para.mmamode.arcforce/100.0));//280.0;//20.0;//140;
 	  //sckpidParams.sckoutmin=0;//-(pidParams.outmax-(pidParams.scalefactor*minoutputfreq));//0.0;
     
      //INT_sckpidParams.INT_sckscalefactor=INT_sckpidParams.INT_sckoutmax/(para.mmamode.setcurrent*(para.mmamode.arcforce/100.0));//62;//50;//125;//75;//150;//125;//300-para.migmode.setwspeed;//sckpidParams.sckoutmax/(para.migmode.setwspeed400.0;   ;//125//100+(sckpidParams.sckoutmax/400.0;//300.0;//500.0;//440.0;//280.0;//20.0;//140;
      if(para.mmamode.arcforce>0)
      {
      	fans=(float)(INT_sckpidParams.INT_sckoutmax/(para.mmamode.setcurrent*(para.mmamode.arcforce/100.0)));//62;//50;//125;//75;//150;//125;//300-para.migmode.setwspeed;//sckpidParams.sckoutmax/(para.migmode.setwspeed400.0;   ;//125//100+(sckpidParams.sckoutmax/400.0;//300.0;//500.0;//440.0;//280.0;//20.0;//140;
      	if(fans>=INT_sckpidParams.INT_sckoutmax)
      	fans=INT_sckpidParams.INT_sckoutmax;
      	INT_sckpidParams.INT_sckscalefactor=(int)fans;
      }
      else
      {
      	INT_sckpidParams.INT_sckscalefactor=INT_sckpidParams.INT_sckoutmax;
      }
      INT_sckpidParams.INT_sckoutmin=0;
   }
   else if(weldmode=='G')
   {
      INT_sckpidParams.INT_sckKp=intkp;//2;//pidParams1.Kp1;//pidkp;//pidParams1.Kp1;//50.0;//40.0;//20.0//10.0 //100.0;// pidParams1.Kp1
      INT_sckpidParams.INT_sckKi=intki;//4;//pidParams1.Ki1;//pidki;//pidParams1.Ki1;//5.0;//10.0;//2.0;//1.0 //0.5;//0.2;
      INT_sckpidParams.INT_sckKd=intkd;//1;//pidParams1.Kd1;//pidkd;//pidParams1.Kd1;//p120.0;//10.0 ;2.0;//0.50;//0.02;
      INT_sckpidParams.INT_sckTsampling=1;

      INT_sckpidParams.INT_sckReferenceSetpoint=para.migmode.setvoltage>>1;//160.0;//SCKVOLTAGE;//parcbasevtg;//setmvtg;
      INT_sckpidParams.INT_sckfeedback=SCKVOLTAGE>>1;//CVOLTAGE;//actualmvtg;
      INT_sckpidParams.INT_sckerror =INT_sckpidParams.INT_sckReferenceSetpoint - INT_sckpidParams.INT_sckfeedback;
      //sckpidParams.sckabsolute_error=abs(sckpidParams.sckerror);
      INT_sckpidParams.INT_sckoutmax=25000;//56000.0;
      INT_sckpidParams.INT_sckscalefactor=INT_sckpidParams.INT_sckoutmax/500;//INT_sckpidParams.INT_sckoutmax/(300+(para.migmode.setwspeed/2.0));//62;//50;//125;//75;//150;//125;//300-para.migmode.setwspeed;//sckpidParams.sckoutmax/(para.migmode.setwspeed400.0;   ;//125//100+(sckpidParams.sckoutmax/400.0;//300.0;//500.0;//440.0;//280.0;//20.0;//140;
      INT_sckpidParams.INT_sckoutmin=50*INT_sckpidParams.INT_sckscalefactor;//baseamp*INT_sckpidParams.INT_sckscalefactor;//2450;//sckpidParams.sckscalefactor*(para.migmode.setwspeed/2.0);//6250.0;//sckpidParams.sckscalefactor*(para.migmode.setwspeed/2.0);
    }
    else if(weldmode=='P')
    {
		INT_sckpidParams.INT_sckKp=120;//100;//150;//10;//0;//intkp;//2;//pidParams1.Kp1;//pidkp;//pidParams1.Kp1;//50.0;//40.0;//20.0//10.0 //100.0;// pidParams1.Kp1
		INT_sckpidParams.INT_sckKi=10;//5;//10;//5;//5;//intki;//4;//pidParams1.Ki1;//pidki;//pidParams1.Ki1;//5.0;//10.0;//2.0;//1.0 //0.5;//0.2;
		INT_sckpidParams.INT_sckKd=10;//6;//intkd;//1;//pidParams1.Kd1;//pidkd;//pidParams1.Kd1;//p120.0;//10.0 ;2.0;//0.50;//0.02;
		INT_sckpidParams.INT_sckTsampling=1;
		
		INT_sckpidParams.INT_sckReferenceSetpoint=parcbasevtg>>1;//80;//160;//para.migmode.setvoltage>>1;//160.0;//SCKVOLTAGE;//parcbasevtg;//setmvtg;
        INT_sckpidParams.INT_sckfeedback=ACT_CVOLTAGE>>1;//SCKVOLTAGE>>1;//CVOLTAGE;//actualmvtg;
    
		
		//INT_sckpidParams.INT_sckReferenceSetpoint=70;//80;//160;//para.migmode.setvoltage>>1;//160.0;//SCKVOLTAGE;//parcbasevtg;//setmvtg;
		//INT_sckpidParams.INT_sckfeedback=ACT_CVOLTAGE>>3;//SCKVOLTAGE>>1;//CVOLTAGE;//actualmvtg;
		INT_sckpidParams.INT_sckerror =INT_sckpidParams.INT_sckReferenceSetpoint - INT_sckpidParams.INT_sckfeedback;
		//sckpidParams.sckabsolute_error=abs(sckpidParams.sckerror);
		INT_sckpidParams.INT_sckoutmax=25000;//56000.0;
		INT_sckpidParams.INT_sckscalefactor=INT_sckpidParams.INT_sckoutmax/500;//(300+(para.migmode.setwspeed/2.0));//62;//50;//125;//75;//150;//125;//300-para.migmode.setwspeed;//sckpidParams.sckoutmax/(para.migmode.setwspeed400.0;   ;//125//100+(sckpidParams.sckoutmax/400.0;//300.0;//500.0;//440.0;//280.0;//20.0;//140;
		INT_sckpidParams.INT_sckoutmin=0;//baseamp*INT_sckpidParams.INT_sckscalefactor;//2450;//sckpidParams.sckscalefactor*(para.migmode.setwspeed/2.0);//6250.0;//sckpidParams.sckscalefactor*(para.migmode.setwspeed/2.0);
	}
   INT_sckpidParams.INT_sckerror_new=INT_sckpidParams.INT_sckerror;
   {
            INT_sckpidParams.INT_sckintegral_new = INT_sckpidParams.INT_sckintegral_old + INT_sckpidParams.INT_sckKi*(INT_sckpidParams.INT_sckerror_new + INT_sckpidParams.INT_sckerror_old)*INT_sckpidParams.INT_sckTsampling/2; // Area of the trapezoid
            //if((sckpidParams.sckintegral_new >= sckpidParams.sckoutmax) || (sckpidParams.sckintegral_new < sckpidParams.sckoutmin)) //-pidParams1.outmax1))// This is anti wind up protect
            //sckpidParams.sckintegral_new = sckpidParams.sckintegral_old;
         	if(INT_sckpidParams.INT_sckintegral_new >= INT_sckpidParams.INT_sckoutmax) //|| (sckpidParams.sckintegral_new < sckpidParams.sckoutmin)) //-pidParams1.outmax1))// This is anti wind up protect
            INT_sckpidParams.INT_sckintegral_new = INT_sckpidParams.INT_sckoutmax;//sckpidParams.sckintegral_old;
         	else if(INT_sckpidParams.INT_sckintegral_new < INT_sckpidParams.INT_sckoutmin) //-pidParams1.outmax1))// This is anti wind up protect
            INT_sckpidParams.INT_sckintegral_new = INT_sckpidParams.INT_sckoutmin;//sckpidParams.sckintegral_old;

            INT_sckpidParams.INT_sckpidoutput    = INT_sckpidParams.INT_sckKp*INT_sckpidParams.INT_sckerror_new + INT_sckpidParams.INT_sckKd*(INT_sckpidParams.INT_sckerror_new-INT_sckpidParams.INT_sckerror_old)/INT_sckpidParams.INT_sckTsampling + INT_sckpidParams.INT_sckintegral_new;

            INT_sckpidParams.INT_sckintegral_old = INT_sckpidParams.INT_sckintegral_new;
            INT_sckpidParams.INT_sckerror_old    = INT_sckpidParams.INT_sckerror_new;
    }

	  INT_sckpidParams.INT_sckpidoutput=INT_sckpidParams.INT_sckpidoutput*pidfactor;
      if(INT_sckpidParams.INT_sckpidoutput >= INT_sckpidParams.INT_sckoutmax)
      {
          INT_sckpidParams.INT_sckpidoutput = INT_sckpidParams.INT_sckoutmax;
      }
      else if(INT_sckpidParams.INT_sckpidoutput < INT_sckpidParams.INT_sckoutmin)
      {
          INT_sckpidParams.INT_sckpidoutput = INT_sckpidParams.INT_sckoutmin;
      }
       INT_sckscaled_val=(INT_sckpidParams.INT_sckpidoutput/INT_sckpidParams.INT_sckscalefactor); //50000
       OC2RS=INT_sckscaled_val<<2;
       disp_newbaseamp=INT_sckscaled_val;
       if(weldmode=='M')
       {
  			if(INT_sckscaled_val>=para.mmamode.setcurrent)
	    	INT_sckscaled_val=para.mmamode.setcurrent;
	    	sck_current_ref=INT_sckscaled_val;     
       }
       else if(weldmode=='G')
       {
          if(INT_sckscaled_val>=500)
          INT_sckscaled_val=500.0;
          //sckdaccount   =(INT_sckscaled_val*CCSLOPENEW)-CCOFFSETNEW;
          //else if(sckscaled_val<=10)
          //sckscaled_val=10.0;
      	  /* 
			else if(sckscaled_val<=(para.migmode.setwspeed/2.0))//50)
			sckscaled_val=para.migmode.setwspeed/2.0;//50.0;//20.0;
			
			if(sckscaled_val<=20)
			sckscaled_val=20.0;
		  */
		  
		  
          if(cvopenloopcnt>10)//60
          {
          	 sckdaccount   =(INT_sckscaled_val*CCSLOPENEW)-CCOFFSETNEW;
		  }
          else
          {
             cvopenloopcnt++;
             sckdaccount   =(50.0*CCSLOPENEW)-CCOFFSETNEW;
          }
       	}
       	else if(weldmode=='P')
       	{
	       	if(INT_sckscaled_val>=500)
	    	INT_sckscaled_val=500;
	    	else if(INT_sckscaled_val<=20)
	    	INT_sckscaled_val=20;
	    	
	    	//dispnum1=INT_sckscaled_val;
	    	sckdaccount=(INT_sckscaled_val*CCSLOPENEW)-CCOFFSETNEW;
	    	//sckdaccount=0;
	    	//Toggle_pin();
	    }	
     }
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



void superfast_PID11(void)
{
 
 //TORCHTEST1IPIO=0;
 //TORCHTEST1IOLAT=1;
 sf_kpgain=100;//50//pidParams.Kp;
 sf_kigain=10;//2;//pidParams.Ki;
 sf_kdgain=5;//pidParams.Kd;
 
 sf_setpoint=parcbasevtg;//FRQbasevtg;//parcbasevtg;  //para.migmode.setvoltage
 sf_feedback=ACT_CVOLTAGE;
 sf_error=sf_setpoint-sf_feedback;
 ;
 sf_pterm=sf_kpgain*sf_error;//sf_error<<sf_kpgain;//sf_kpgain*sf_error;			//-----pterm;
 ;
 sf_accumulator+=sf_error;
 if(sf_accumulator>=sf_outputmax)
 sf_accumulator=sf_outputmax;
 else if(sf_accumulator<=sf_outputmin)
 sf_accumulator=sf_outputmin;
 //sf_iterm=sf_accumulator<<sf_kigain;
 sf_iterm=sf_accumulator*sf_kigain;
 
 //sf_pid+=sf_accumulator;
 //sf_pid=sf_pid<<sf_kigain;
 ;
 //sf_pid+=sf_kdgain*(sf_error-sf_preverror);
 sf_dterm=(sf_error-sf_preverror)*sf_kdgain;//(sf_error-sf_preverror)<<sf_kdgain;
 sf_preverror=sf_error;
 ;
 sf_pid=sf_pterm+sf_iterm+sf_dterm;
 if(sf_pid>=(sf_outputmax*2))
 sf_pid=sf_outputmax;
 else if(sf_pid<=(sf_outputmin*2))
 sf_pid=sf_outputmin;
 ;
 sf_pidoutput=sf_pid>>sf_scalefactor;
//if(sf_pidoutput>=500)
//sf_pidoutput=500;
//else if(sf_pidoutput<=20)
//sf_pidoutput=20;

//dispnum1=sf_pidoutput;
//sckdaccount=(sf_pidoutput*CCSLOPENEW)-CCOFFSETNEW; 

 //TORCHTEST1IPIO=0;
 //TORCHTEST1IOLAT=0;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
struct FRQ_sckpidParameters
{
   int FRQ_sckKp;
   int FRQ_sckKi;
   int FRQ_sckKd;
   int FRQ_sckKf;
   int FRQ_sckTsampling;
   
   int FRQ_sckReferenceSetpoint;
   int FRQ_sckfeedback;
   int FRQ_sckerror;
   int FRQ_sckerror_new;
   int FRQ_sckerror_old;
   int FRQ_sckintegral_old;
   int FRQ_sckintegral_new;
   int FRQ_sckderivitive;
   int FRQ_sckabsolute_error;
   int FRQ_scksaturated;
   int FRQ_sckpidoutput;
   int FRQ_sckoutmax;
   int FRQ_sckoutmin;
   int FRQ_sckscalefactor;
}   FRQ_sckpidParams;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void FRQ_sck_voltage_pid()   //execution time 60usec
{
    if(msrbaseoncnt>10000)
    msrbaseoncnt=10000;
    
    if(msrbaseoncnt > (4*msrpulseoncnt))
    {
	    avgpulsevtg=msrbasevtg;
	    tmpeakvtg=msrpulsevtg;
    	tmbasevtg=msrbasevtg;
    	// tarbasevtg=parcbasevtg;
	} 
	else
	{
    	msrbaseoncnt=4*msrpulseoncnt;
    	
    	tmmsrpulseoncnt=msrpulseoncnt;
    	tmmsrbaseoncnt=msrbaseoncnt;
    	tmpeakvtg=msrpulsevtg;
    	tmbasevtg=msrbasevtg;
    	
    	peakvtgpart=(tmpeakvtg*tmmsrpulseoncnt)/(tmmsrpulseoncnt+tmmsrbaseoncnt);
    	basevtgpart=(tmbasevtg*tmmsrbaseoncnt)/(tmmsrpulseoncnt+tmmsrbaseoncnt);
    	
    	//tarbasevtg=(parcbasevtg-10);
    	avgpulsevtg=(int)(peakvtgpart+basevtgpart);//peakvtgpart;//msrbasevtg;//peakvtgpart;//msrpulseoncnt;//(int)peakvtgpart;//+basevtgpart;	            
	}
	fbavgpulsevtg=(0.7*avgpulsevtg)+(0.3*prevavgpulsevtg);//((1.0-0.7)*prevFLTSCKvtg);
	prevavgpulsevtg=avgpulsevtg;
	//FLTSCKvtg=SCKvtg;
	dispavgpulsevtg=tmpeakvtg;//fbavgpulsevtg;
//##############################################################################################	
	FRQbasevtg=parcbasevtg-10;
	if(FRQbasevtg<140)
	FRQbasevtg=140;
	
	FRQbaseamp=FRQbasevtg>>1;//IB=bvtg/2-50
	if(FRQbaseamp>=60)
	FRQbaseamp=FRQbaseamp-60;
	else
	FRQbaseamp=0;
	
	if(FRQbaseamp<15) //20)
	FRQbaseamp=15;//20;

 	FRQ_baseamp=FRQbaseamp;
   	if(FRQ_baseamp <40)
		FRQ_stepamp=50;
   	else
		FRQ_stepamp=FRQ_baseamp;

	if(tmpeakvtg>=320.0)
    {
	    FRQ_peakamp=280.0;
	}
	else
	{
		if(tmpeakvtg>=280.0)
		{
			diffpeakvtg=tmpeakvtg-280.0;
			FRQ_peakamp=peakamp-diffpeakvtg;
			if(FRQ_peakamp<=280.0)
			FRQ_peakamp=280.0;
		}
		else
		{
			diffpeakvtg=280.0-tmpeakvtg;
			FRQ_peakamp=peakamp+(diffpeakvtg);
			if(FRQ_peakamp>=380)
			FRQ_peakamp=380;
		}
	}	
		
   	FRQ_uppdaccount  	=(FRQ_peakamp*CCSLOPENEW)  -CCOFFSETNEW;
	FRQ_pdaccount	 	=(FRQ_peakamp*CCSLOPENEW)  -CCOFFSETNEW;
	FRQ_sdaccount	 	=(FRQ_stepamp*CCSLOPENEW)  -CCOFFSETNEW;
	FRQ_bdaccount	 	=(FRQ_baseamp*CCSLOPENEW)  -CCOFFSETNEW;
	FRQ_newupstep		=(FRQ_uppdaccount-FRQ_bdaccount)/OPEN_pulserisetm;
	
//##############################################################################################	   
    if(weldmode=='P')
    {
		FRQ_sckpidParams.FRQ_sckKp=200;//pidParams.Kp;//200;//100;
		FRQ_sckpidParams.FRQ_sckKi=4;//pidParams.Ki;//20;//5;//2;//pidParams.Ki;//10;//5;//5;//intki;//4;//pidParams1.Ki1;//pidki;//pidParams1.Ki1;//5.0;//10.0;//2.0;//1.0 //0.5;//0.2;
		FRQ_sckpidParams.FRQ_sckKd=5;//pidParams.Kd;//20;//2;//pidParams.Kd;//6;//intkd;//1;//pidParams1.Kd1;//pidkd;//pidParams1.Kd1;//p120.0;//10.0 ;2.0;//0.50;//0.02;
		FRQ_sckpidParams.FRQ_sckTsampling=1;
		
		FRQ_sckpidParams.FRQ_sckReferenceSetpoint=parcbasevtg>>2;//80;//70;//80;//160;//para.migmode.setvoltage>>1;//160.0;//SCKVOLTAGE;//parcbasevtg;//setmvtg;
		FRQ_sckpidParams.FRQ_sckfeedback=fbavgpulsevtg>>2;//msrbasevtg;//VOLTAGE;//CVOLTAGE;//ACT_CVOLTAGE>>2;//>>1;//SCKVOLTAGE>>1;//CVOLTAGE;//actualmvtg;
		FRQ_sckpidParams.FRQ_sckerror =FRQ_sckpidParams.FRQ_sckReferenceSetpoint - FRQ_sckpidParams.FRQ_sckfeedback;
		FRQ_sckpidParams.FRQ_sckabsolute_error=abs(FRQ_sckpidParams.FRQ_sckerror);
		
		FRQ_sckpidParams.FRQ_sckoutmax=25000;//56000.0;
		FRQ_sckpidParams.FRQ_sckscalefactor=FRQ_sckpidParams.FRQ_sckoutmax/300;//400;//peakamp;//250;//500;//(300+(para.migmode.setwspeed/2.0));//62;//50;//125;//75;//150;//125;//300-para.migmode.setwspeed;//sckpidParams.sckoutmax/(para.migmode.setwspeed400.0;   ;//125//100+(sckpidParams.sckoutmax/400.0;//300.0;//500.0;//440.0;//280.0;//20.0;//140;
		FRQ_sckpidParams.FRQ_sckoutmin=0;//baseamp*INT_sckpidParams.INT_sckscalefactor;//2450;//sckpidParams.sckscalefactor*(para.migmode.setwspeed/2.0);//6250.0;//sckpidParams.sckscalefactor*(para.migmode.setwspeed/2.0);
	}
   FRQ_sckpidParams.FRQ_sckerror_new=FRQ_sckpidParams.FRQ_sckerror;
   {
            FRQ_sckpidParams.FRQ_sckintegral_new = FRQ_sckpidParams.FRQ_sckintegral_old + FRQ_sckpidParams.FRQ_sckKi*(FRQ_sckpidParams.FRQ_sckerror_new + FRQ_sckpidParams.FRQ_sckerror_old)*FRQ_sckpidParams.FRQ_sckTsampling/2; // Area of the trapezoid
            //if((sckpidParams.sckintegral_new >= sckpidParams.sckoutmax) || (sckpidParams.sckintegral_new < sckpidParams.sckoutmin)) //-pidParams1.outmax1))// This is anti wind up protect
            //sckpidParams.sckintegral_new = sckpidParams.sckintegral_old;
         	if(FRQ_sckpidParams.FRQ_sckintegral_new >= FRQ_sckpidParams.FRQ_sckoutmax) //|| (sckpidParams.sckintegral_new < sckpidParams.sckoutmin)) //-pidParams1.outmax1))// This is anti wind up protect
            FRQ_sckpidParams.FRQ_sckintegral_new = FRQ_sckpidParams.FRQ_sckoutmax;//sckpidParams.sckintegral_old;
         	else if(FRQ_sckpidParams.FRQ_sckintegral_new < FRQ_sckpidParams.FRQ_sckoutmin) //-pidParams1.outmax1))// This is anti wind up protect
            FRQ_sckpidParams.FRQ_sckintegral_new = FRQ_sckpidParams.FRQ_sckoutmin;//sckpidParams.sckintegral_old;

            FRQ_sckpidParams.FRQ_sckpidoutput    = FRQ_sckpidParams.FRQ_sckKp*FRQ_sckpidParams.FRQ_sckerror_new + FRQ_sckpidParams.FRQ_sckKd*(FRQ_sckpidParams.FRQ_sckerror_new-FRQ_sckpidParams.FRQ_sckerror_old)/FRQ_sckpidParams.FRQ_sckTsampling + FRQ_sckpidParams.FRQ_sckintegral_new;

            FRQ_sckpidParams.FRQ_sckintegral_old = FRQ_sckpidParams.FRQ_sckintegral_new;
            FRQ_sckpidParams.FRQ_sckerror_old    = FRQ_sckpidParams.FRQ_sckerror_new;
    }

	  FRQ_sckpidParams.FRQ_sckpidoutput=FRQ_sckpidParams.FRQ_sckpidoutput*pidfactor;
      if(FRQ_sckpidParams.FRQ_sckpidoutput >= FRQ_sckpidParams.FRQ_sckoutmax)
      {
          FRQ_sckpidParams.FRQ_sckpidoutput = FRQ_sckpidParams.FRQ_sckoutmax;
      }
      else if(FRQ_sckpidParams.FRQ_sckpidoutput < FRQ_sckpidParams.FRQ_sckoutmin)
      {
          FRQ_sckpidParams.FRQ_sckpidoutput = FRQ_sckpidParams.FRQ_sckoutmin;
      }
       FRQ_sckscaled_val=(FRQ_sckpidParams.FRQ_sckpidoutput/FRQ_sckpidParams.FRQ_sckscalefactor); //50000
       //OC2RS=INT_sckscaled_val<<2;
       //disp_newbaseamp=FRQ_sckscaled_val;
   		
   		if(weldmode=='P')
       	{
	       	
	    	if(para.pmigmode.setwspeed<40)
	    	{
	    		if(FRQ_sckscaled_val<=para.pmigmode.setwspeed/2)//(para.pmigmode.setwspeed/2)) 
	    	       FRQ_sckscaled_val=para.pmigmode.setwspeed/2;//50 //20;//500;
	    	}
	    	else
	    	{
	    		if(FRQ_sckscaled_val<=para.pmigmode.setwspeed)//(para.pmigmode.setwspeed/2)) 
	    		FRQ_sckscaled_val=para.pmigmode.setwspeed;///2;//50 //20;//500;
	       	}
	    	
	    	if(FRQ_sckscaled_val>=300) //400) //peakamp)//500)
	    	FRQ_sckscaled_val=300;//400;//peakamp;//500;
	    	   	
	    	else if(FRQ_sckscaled_val<=10)
	    	FRQ_sckscaled_val=10;
	    	
	    	dispnum1=FRQ_sckscaled_val;
	    	pulsefreq=FRQ_sckscaled_val;
	    }	
     }
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
///*
////unsigned int motor_control_pid()
//void Adaptive_freq_pid()
//{
//	unsigned int minoutputfreq=30.0;
//	signed long scaled_val=0;
//	pidParams.Kp=50.0;//0.5;//0.1;
//	pidParams.Ki=0.08;//0.01;//0.02;
//	pidParams.Kd=0.50;//0.02;
//	pidParams.Tsampling=1.0;
//
//
//	pidParams.ReferenceSetpoint=parcbasevtg;//setmvtg;
//	pidParams.feedback=CVOLTAGE;//actualmvtg;
//	pidParams.error = pidParams.ReferenceSetpoint - pidParams.feedback;
//	pidParams.absolute_error=abs(pidParams.error);
//	pidParams.outmax=50000.0;//56000.0;
//	pidParams.scalefactor=280.0;//20.0;//140;
//    pidParams.outmin=-(pidParams.outmax-(pidParams.scalefactor*minoutputfreq));//0.0;
//    pidParams.error_new=pidParams.error;
//		{
//            pidParams.integral_new = pidParams.integral_old + pidParams.Ki*(pidParams.error_new + pidParams.error_old)*pidParams.Tsampling/2; // Area of the trapezoid
//            if((pidParams.integral_new >= pidParams.outmax) || (pidParams.integral_new < pidParams.outmin)) //-pidParams1.outmax1))// This is anti wind up protect
//            pidParams.integral_new = pidParams.integral_old;
//
//            pidParams.pidoutput	 = pidParams.Kp*pidParams.error_new + pidParams.Kd*(pidParams.error_new-pidParams.error_old)/pidParams.Tsampling + pidParams.integral_new;
//            
//		    pidParams.integral_old    = pidParams.integral_new;
//            pidParams.error_old 	  = pidParams.error_new;
//            
//         }
//
//		if(pidParams.pidoutput >= pidParams.outmax)
//		{
//		    pidParams.pidoutput = pidParams.outmax;
//		}
//		else if(pidParams.pidoutput < pidParams.outmin) 
//		{
//		    pidParams.pidoutput = pidParams.outmin;
//		}
//	    scaled_val=(pidParams.pidoutput/pidParams.scalefactor); //50000
//	    //return(scaled_val);
//	    newpulsefreq=178+scaled_val;//refpulsefreq+scaled_val1;
//	   	if(newpulsefreq>0.0)
//				 pulseduty=100000.0/newpulsefreq;
//		else
//			 	pulseduty=10000;
//				 	
//		if(pulseduty >=tpulsetime) //tpulsetime=pulserisetime+peaktime+steptime+pulsefalltime;
//		{
//			newbasetime=pulseduty-tpulsetime;
//		 	newsteptime=steptime;
//		 	shiftbvtgf=0;
//		}
//		else
//		{
//			newbasetime=1;
//			pulseontime=(pulserisetime+peaktime+pulsefalltime);
//			if(pulseduty>=pulseontime)
//				newsteptime=(pulseduty-pulseontime);//-peaktime;
//			else
//				newsteptime=50;//30;
//			if(newsteptime<=50)//30)
//				newsteptime=50;//30;
//					
//			shiftbvtgf=1;	
//			disptemp=newsteptime;
//		}
//				PID_basetm		=newbasetime/5;
//	   			PID_steptm		=newsteptime/5;	
//	    
//			if(program_number ==20)//26) // //ALU+SI 1.2 AR
//   			{
//	   			MAXFBMULTIPLIER=(560.0 -(2.36*para.pmigmode.setwspeed))*100.0;
//	   			scaled_baseval2=MAXFBMULTIPLIER/(newsteptime+newbasetime);  		//newbasetime in usec
//	   			if(scaled_baseval2>=(para.pmigmode.setwspeed*2.0)) //200)
//	   			scaled_baseval2=para.pmigmode.setwspeed*2.0;     //;//200;
//	   			
//	   			if(scaled_baseval2<=(para.pmigmode.setwspeed*1.2))
//	   			scaled_baseval2=para.pmigmode.setwspeed*1.2;
//	   			
//	   			baseamp=scaled_baseval2;
//	   			stepamp=baseamp;
//	   			refstepamp=stepamp;
//   			}
//   			else if(program_number ==21) //26) // //ALU+MG 1.2 AR
//   			{
//	   			MAXFBMULTIPLIER=(560.0 -(2.36*para.pmigmode.setwspeed))*100.0;
//	   			//MAXFBMULTIPLIER=(800.0 -(3.0*para.pmigmode.setwspeed))*100.0;
//	   			scaled_baseval2=MAXFBMULTIPLIER/(newsteptime+newbasetime);  		//newbasetime in usec
//	   			if(scaled_baseval2>=(para.pmigmode.setwspeed*2.0))//1.5))//2.0)) //200)
//	   			scaled_baseval2=para.pmigmode.setwspeed*2.0;//1.5;//2.0;     //;//200;
//	   			
//	   			if(scaled_baseval2<=(para.pmigmode.setwspeed*0.5))//1.2));//0.75)) //1.2))
//	   			scaled_baseval2=para.pmigmode.setwspeed*0.5;//1.2;//0.75;//1.2;
//	   			
//	   			
//	   			if(scaled_baseval2<=30)
//	   			scaled_baseval2=30;
//	   			
//	   			baseamp=scaled_baseval2;
//	   			stepamp=baseamp;
//	   			refstepamp=stepamp;
//   			}   			
//   			else if((program_number ==35)|| (program_number ==36)) // //ALU 1.6 AR
//   			{
//	   			MAXFBMULTIPLIER=(848.0 -(9.32*para.pmigmode.setwspeed))*100.0;
//	   			scaled_baseval2=MAXFBMULTIPLIER/(newsteptime+newbasetime);  		//newbasetime in usec
//	   			
//	   			if(scaled_baseval2>=(para.pmigmode.setwspeed*3.0)) //200)
//	   			scaled_baseval2=para.pmigmode.setwspeed*3.0;     //;//200;
//	   			
//	   			baseamp=scaled_baseval2;
//	   			stepamp=baseamp;
//	   			refstepamp=stepamp;
//   			}
//   			else
//   			{   			
//   				scaled_baseval2=baseamp;		//FOR FIX BASE CURRENT
//   			}
//	   		setpidbamp=scaled_baseval2;
//			
//			PID_pulsetm		=OPEN_pulsetm;
//			PID_pulserisetm	=OPEN_pulserisetm;
//			PID_pulsefalltm	=OPEN_pulsefalltm;
//			PID_startpulsetm=OPEN_startpulsetm;
//			PID_uppdaccount	=OPEN_uppdaccount;
//			PID_pdaccount	=OPEN_pdaccount;
//			PID_sdaccount	=CCOFFSET+(refstepamp*CCSLOPE);
//			PID_bdaccount	=CCOFFSET+(scaled_baseval2*CCSLOPE);
//			PID_newupstep	=(PID_uppdaccount-PID_bdaccount)/pulserisetm;
//			PID_newdownstep	=(PID_pdaccount-PID_sdaccount)/pulsefalltm;
//}
//*/
//
//
//struct sckpidParameters
//{
//	float sckKp;
//	float sckKi;
//	float sckKd;
//	float sckKf;
//	float sckTsampling;
//	float sckReferenceSetpoint;
//	float sckfeedback;
//	float sckerror;
//	float sckerror_new;
//	float sckerror_old;
//	float sckintegral_old;
//	float sckintegral_new;
//	float sckderivitive;
//	float sckabsolute_error;
//	float scksaturated;
//	float sckpidoutput;
//	float sckoutmax;
//	float sckoutmin;
//	float sckscalefactor;
//}   sckpidParams;
//
//
//void sck_voltage_pid()
//{
//	unsigned int sckscaled_val=0;
//	sckpidParams.sckKp=100.0;//50.0;//0.5;//50.0;//0.5;//0.1; pidParams1.Kp1
//	sckpidParams.sckKi=2.0;//0.2;//0.08;//0.01;//0.02;
//	sckpidParams.sckKd=0.50;//0.02;
//	sckpidParams.sckTsampling=1.0;
//
//	if(weldmode=='M')
//	{
//		sckpidParams.sckKp=100.0;//50.0;//0.5;//50.0;//0.5;//0.1; pidParams1.Kp1
//		sckpidParams.sckKi=2.0;//0.2;//0.08;//0.01;//0.02;
//		sckpidParams.sckKd=0.50;//0.02;
//		sckpidParams.sckTsampling=1.0;
//
//		sckpidParams.sckReferenceSetpoint=160.0;//SCKVOLTAGE;//parcbasevtg;//setmvtg;
//		sckpidParams.sckfeedback=SCKVOLTAGE;//CVOLTAGE;//actualmvtg;
//		sckpidParams.sckerror = sckpidParams.sckReferenceSetpoint - sckpidParams.sckfeedback;
//		//sckpidParams.sckabsolute_error=abs(sckpidParams.sckerror);
//		sckpidParams.sckoutmax=50000.0;//56000.0;
//		sckpidParams.sckscalefactor=sckpidParams.sckoutmax/(para.mmamode.setcurrent*(para.mmamode.arcforce/100.0));//280.0;//20.0;//140;
// 		sckpidParams.sckoutmin=0;//-(pidParams.outmax-(pidParams.scalefactor*minoutputfreq));//0.0;
//    
// 	}
// 	else if(weldmode=='G')
//	{
//		pidParams1.Kp1=50.0;//30.0+(para.migmode.setwspeed/4.0); //30.0
//		pidParams1.Ki1=5.0;// +(para.migmode.setwspeed/100.0);
//		pidParams1.Kd1=5.0;//0;//5.0+(para.migmode.setwspeed/20.0);
//		sckpidParams.sckKp=pidParams1.Kp1;//pidkp;//pidParams1.Kp1;//50.0;//40.0;//20.0//10.0 //100.0;// pidParams1.Kp1
//		sckpidParams.sckKi=pidParams1.Ki1;//pidki;//pidParams1.Ki1;//5.0;//10.0;//2.0;//1.0 //0.5;//0.2;
//		sckpidParams.sckKd=pidParams1.Kd1;//pidkd;//pidParams1.Kd1;//p120.0;//10.0 ;2.0;//0.50;//0.02;
//		sckpidParams.sckTsampling=1.0;
//
//		sckpidParams.sckReferenceSetpoint=para.migmode.setvoltage;//160.0;//SCKVOLTAGE;//parcbasevtg;//setmvtg;
//		sckpidParams.sckfeedback=SCKVOLTAGE;//CVOLTAGE;//actualmvtg;
//		sckpidParams.sckerror = sckpidParams.sckReferenceSetpoint - sckpidParams.sckfeedback;
//		//sckpidParams.sckabsolute_error=abs(sckpidParams.sckerror);
//		sckpidParams.sckoutmax=50000.0;//56000.0;
//		sckpidParams.sckscalefactor=125;//sckpidParams.sckoutmax/400.0;//300.0;//500.0;//440.0;//280.0;//20.0;//140;
// 		sckpidParams.sckoutmin=2450;//sckpidParams.sckscalefactor*(para.migmode.setwspeed/2.0);//6250.0;//sckpidParams.sckscalefactor*(para.migmode.setwspeed/2.0);
//    
// 	}
//    else if(weldmode=='P')  //'M'
//    {
//		sckpidParams.sckKp=200.0;//100.0;
//		sckpidParams.sckKi=5.0;//2.0;
//		sckpidParams.sckKd=0.50;//0.02;
//		sckpidParams.sckTsampling=1.0;
//	   
//	    sckpidParams.sckReferenceSetpoint=560.0;//720.0;//560.0;//14v=560; 600;//160.0;//SCKVOLTAGE;//parcbasevtg;//setmvtg;
//		sckpidParams.sckfeedback=ACT_CVOLTAGE;//SCKVOLTAGE;//CVOLTAGE;//actualmvtg;
//		sckpidParams.sckerror = sckpidParams.sckReferenceSetpoint - sckpidParams.sckfeedback;
//		//sckpidParams.sckabsolute_error=abs(sckpidParams.sckerror);
//		sckpidParams.sckoutmax=50000.0;//56000.0;
//	    sckpidParams.sckscalefactor=sckpidParams.sckoutmax/peakamp;//100.0;//500.0;  
//    	sckpidParams.sckoutmin=0;//-(pidParams.outmax-(pidParams.scalefactor*minoutputfreq));//0.0;
//    
//    }
//    
//    
//    sckpidParams.sckerror_new=sckpidParams.sckerror;
//	{
//            sckpidParams.sckintegral_new = sckpidParams.sckintegral_old + sckpidParams.sckKi*(sckpidParams.sckerror_new + sckpidParams.sckerror_old)*sckpidParams.sckTsampling/2; // Area of the trapezoid
//            
//			            
//            //if((sckpidParams.sckintegral_new >= sckpidParams.sckoutmax) || (sckpidParams.sckintegral_new < sckpidParams.sckoutmin)) //-pidParams1.outmax1))// This is anti wind up protect
//            //sckpidParams.sckintegral_new = sckpidParams.sckintegral_old;
//            
//			if(sckpidParams.sckintegral_new >= sckpidParams.sckoutmax) //|| (sckpidParams.sckintegral_new < sckpidParams.sckoutmin)) //-pidParams1.outmax1))// This is anti wind up protect
//            sckpidParams.sckintegral_new = sckpidParams.sckoutmax;//sckpidParams.sckintegral_old;
//			else if(sckpidParams.sckintegral_new < sckpidParams.sckoutmin) //-pidParams1.outmax1))// This is anti wind up protect
//            sckpidParams.sckintegral_new = sckpidParams.sckoutmin;//sckpidParams.sckintegral_old;
//	
//            sckpidParams.sckpidoutput	 = sckpidParams.sckKp*sckpidParams.sckerror_new + sckpidParams.sckKd*(sckpidParams.sckerror_new-sckpidParams.sckerror_old)/sckpidParams.sckTsampling + sckpidParams.sckintegral_new;
//            
//		    sckpidParams.sckintegral_old    = sckpidParams.sckintegral_new;
//            sckpidParams.sckerror_old 	  = sckpidParams.sckerror_new;
//            
//    }
//
//		if(sckpidParams.sckpidoutput >= sckpidParams.sckoutmax)
//		{
//		    sckpidParams.sckpidoutput = sckpidParams.sckoutmax;
//		}
//		else if(sckpidParams.sckpidoutput < sckpidParams.sckoutmin) 
//		{
//		    sckpidParams.sckpidoutput = sckpidParams.sckoutmin;
//		}
//	    sckscaled_val=(sckpidParams.sckpidoutput/sckpidParams.sckscalefactor); //50000
//	    OC2RS=sckscaled_val<<2;
//	    disp_newbaseamp=sckscaled_val;
//	    if(weldmode=='M')
//	    {
//		    if(sckscaled_val>=para.mmamode.setcurrent)
//	    	sckscaled_val=para.mmamode.setcurrent;
//	    	sck_current_ref=sckscaled_val;
//	  	}
//	  	else if(weldmode=='G')
//	    {
//		    if(sckscaled_val>=400)
//	    	sckscaled_val=400.0;
//	    	sckdaccount	=(sckscaled_val*CCSLOPENEW)-CCOFFSETNEW;
//	    
//	    	//else if(sckscaled_val<=10)
//	    	//sckscaled_val=10.0;
//	    	  
//	   /* 	else if(sckscaled_val<=(para.migmode.setwspeed/2.0))//50)
//	    	sckscaled_val=para.migmode.setwspeed/2.0;//50.0;//20.0;
//	    	
//	    	if(sckscaled_val<=20)
//	    	sckscaled_val=20.0;
//	    	
//	    	if(cvopenloopcnt>60)
//	    	{
//	    		sckdaccount	=(sckscaled_val*CCSLOPENEW)-CCOFFSETNEW;
//	    	}
//	    	else
//	    	{
//		    	cvopenloopcnt++;
//		    	sckdaccount	=(50.0*CCSLOPENEW)-CCOFFSETNEW;
//		    	//Toggle_pin();
//		    }	
//	    */	
//	  	}
//	  	else if(weldmode=='P')
//	  	{
//	  	    if(sckscaled_val>=500)
//	    	sckscaled_val=500.0;  
//	    	sckdaccount	=(sckscaled_val*CCSLOPENEW)-CCOFFSETNEW;	
//	  	}
//	  }
//	  
////$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	  
/////*struct INT_sckpidParameters
////{
////	unsigned int INT_sckKp;
////	unsigned int INT_sckKi;
////	unsigned int INT_sckKd;
////	unsigned int INT_sckKf;
////	unsigned int INT_sckTsampling;
////	signed int INT_sckReferenceSetpoint;
////	signed int INT_sckfeedback;
////	signed int INT_sckerror;
////	signed int INT_sckerror_new;
////	signed int INT_sckerror_old;
////	signed int INT_sckintegral_old;
////	signed int INT_sckintegral_new;
////	signed int INT_sckderivitive;
////	unsigned int INT_sckabsolute_error;
////	unsigned int INT_scksaturated;
////	unsigned int INT_sckpidoutput;
////	unsigned int INT_sckoutmax;
////	unsigned int INT_sckoutmin;
////	unsigned int INT_sckscalefactor;
////}   INT_sckpidParams;
////
////
////void INT_sck_voltage_pid()
////{
////	unsigned int INT_sckscaled_val=0;
//// 	if(weldmode=='G')
////	{
////		//pidParams1.Kp1=50;//30.0+(para.migmode.setwspeed/4.0); //30.0
////		//pidParams1.Ki1=5;// +(para.migmode.setwspeed/100.0);
////		//pidParams1.Kd1=5;//0;//5.0+(para.migmode.setwspeed/20.0);
////		INT_sckpidParams.INT_sckKp=pidParams1.Kp1;//pidkp;//pidParams1.Kp1;//50.0;//40.0;//20.0//10.0 //100.0;// pidParams1.Kp1
////		INT_sckpidParams.INT_sckKi=pidParams1.Ki1;//pidki;//pidParams1.Ki1;//5.0;//10.0;//2.0;//1.0 //0.5;//0.2;
////		INT_sckpidParams.INT_sckKd=pidParams1.Kd1;//pidkd;//pidParams1.Kd1;//p120.0;//10.0 ;2.0;//0.50;//0.02;
////		INT_sckpidParams.INT_sckTsampling=1;
////
////		INT_sckpidParams.INT_sckReferenceSetpoint=para.migmode.setvoltage;//160.0;//SCKVOLTAGE;//parcbasevtg;//setmvtg;
////		INT_sckpidParams.INT_sckfeedback=SCKVOLTAGE;//CVOLTAGE;//actualmvtg;
////		INT_sckpidParams.INT_sckerror = INT_sckpidParams.INT_sckReferenceSetpoint - INT_sckpidParams.INT_sckfeedback;
////		//sckpidParams.sckabsolute_error=abs(sckpidParams.sckerror);
////		INT_sckpidParams.INT_sckoutmax=25000.0;//50000.0;//56000.0;
////		INT_sckpidParams.INT_sckscalefactor=80;//150;//125;//300-para.migmode.setwspeed;//sckpidParams.sckoutmax/(para.migmode.setwspeed400.0;   ;//125//100+(sckpidParams.sckoutmax/400.0;//300.0;//500.0;//440.0;//280.0;//20.0;//140;
//// 		INT_sckpidParams.INT_sckoutmin=baseamp*INT_sckpidParams.INT_sckscalefactor;//2450;//sckpidParams.sckscalefactor*(para.migmode.setwspeed/2.0);//6250.0;//sckpidParams.sckscalefactor*(para.migmode.setwspeed/2.0);
////    
//// 	}
////    
////    INT_sckpidParams.INT_sckerror_new=INT_sckpidParams.INT_sckerror;
////	{
////            INT_sckpidParams.INT_sckintegral_new = INT_sckpidParams.INT_sckintegral_old + INT_sckpidParams.INT_sckKi*(INT_sckpidParams.INT_sckerror_new + INT_sckpidParams.INT_sckerror_old)*INT_sckpidParams.INT_sckTsampling/2; // Area of the trapezoid
////            
////			            
////            //if((sckpidParams.sckintegral_new >= sckpidParams.sckoutmax) || (sckpidParams.sckintegral_new < sckpidParams.sckoutmin)) //-pidParams1.outmax1))// This is anti wind up protect
////            //sckpidParams.sckintegral_new = sckpidParams.sckintegral_old;
////            
////			if(INT_sckpidParams.INT_sckintegral_new >= INT_sckpidParams.INT_sckoutmax) //|| (sckpidParams.sckintegral_new < sckpidParams.sckoutmin)) //-pidParams1.outmax1))// This is anti wind up protect
////            INT_sckpidParams.INT_sckintegral_new = INT_sckpidParams.INT_sckoutmax;//sckpidParams.sckintegral_old;
////			else if(INT_sckpidParams.INT_sckintegral_new < INT_sckpidParams.INT_sckoutmin) //-pidParams1.outmax1))// This is anti wind up protect
////            INT_sckpidParams.INT_sckintegral_new = INT_sckpidParams.INT_sckoutmin;//sckpidParams.sckintegral_old;
////	
////            INT_sckpidParams.INT_sckpidoutput	 = INT_sckpidParams.INT_sckKp*INT_sckpidParams.INT_sckerror_new + INT_sckpidParams.INT_sckKd*(INT_sckpidParams.INT_sckerror_new-INT_sckpidParams.INT_sckerror_old)/INT_sckpidParams.INT_sckTsampling + INT_sckpidParams.INT_sckintegral_new;
////            
////		    INT_sckpidParams.INT_sckintegral_old    = INT_sckpidParams.INT_sckintegral_new;
////            INT_sckpidParams.INT_sckerror_old 	  = INT_sckpidParams.INT_sckerror_new;
////            
////    }
////
////		if(INT_sckpidParams.INT_sckpidoutput >= INT_sckpidParams.INT_sckoutmax)
////		{
////		    INT_sckpidParams.INT_sckpidoutput = INT_sckpidParams.INT_sckoutmax;
////		}
////		else if(INT_sckpidParams.INT_sckpidoutput < INT_sckpidParams.INT_sckoutmin) 
////		{
////		    INT_sckpidParams.INT_sckpidoutput = INT_sckpidParams.INT_sckoutmin;
////		}
////	    INT_sckscaled_val=(INT_sckpidParams.INT_sckpidoutput/INT_sckpidParams.INT_sckscalefactor); //50000
////	    OC2RS=INT_sckscaled_val<<2;
////	    disp_newbaseamp=INT_sckscaled_val;
////	  	if(weldmode=='G')
////	    {
////		    if(INT_sckscaled_val>=400)
////	    	INT_sckscaled_val=400.0;
////	    	sckdaccount	=(INT_sckscaled_val*CCSLOPENEW)-CCOFFSETNEW;
////	    
////	    	//else if(sckscaled_val<=10)
////	    	//sckscaled_val=10.0;
////	    	  
////	   /* 	else if(sckscaled_val<=(para.migmode.setwspeed/2.0))//50)
////	    	sckscaled_val=para.migmode.setwspeed/2.0;//50.0;//20.0;
////	    	
////	    	if(sckscaled_val<=20)
////	    	sckscaled_val=20.0;
////	    	
////	    	if(cvopenloopcnt>60)
////	    	{
////	    		sckdaccount	=(sckscaled_val*CCSLOPENEW)-CCOFFSETNEW;
////	    	}
////	    	else
////	    	{
////		    	cvopenloopcnt++;
////		    	sckdaccount	=(50.0*CCSLOPENEW)-CCOFFSETNEW;
////		    	//Toggle_pin();
////		    }	
////	    */	
////	  	}
////	  	
////	  }	  
////*/
//
////$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//void DSP_PID()
//{
//	float setpara=0.0,mesurepara=0.0;
//	unsigned int dsp_scaled_val=0;
//	setpara=0.5;//(float)(para.migmode.setvoltage/1000.0);
//	mesurepara=0.6;//(float)(SCKVOLTAGE/1000.0);
//	fooPID.controlReference = Q15(setpara); 	//fooPID1.controlReference = Q15(setwirefeedspeed/4000.0);  //GENERATING REFERENCE FOR PID CONTROLLER
//	fooPID.measuredOutput=Q15(mesurepara);    
//	PID(&fooPID);
//	if(fooPID.controlOutput > Q15(0.0) )
//	{ 
//		dsp_scaled_val = __builtin_mulsu(fooPID.controlOutput,400) >> 15;
//	} 
//	else  
//	{
//		dsp_scaled_val = 20;
//	}  
//	sckdaccount	=1200;//(dsp_scaled_val*CCSLOPENEW)- CCOFFSETNEW;
//			
//}
//
//
//
////int PID(int error_new)
//void NEWPID()
//{
////PID parameters
//
//double Kp = 1.0;///proportion term.
//double Kd = 0.01;// derivative
//double Ki = 0.1;// integral
//double Tsampling = 0.001;// 1kHz frequency, you must call this function by a timer interrupt or delays but i prefer interrupts allways
//// you must set this sampling value correct if you want to match simulation results in real systems
//static int error_old = 0;
//static double integral_old = 0;
//float error_new;
//int controller_out;// if pwm is not less than 16 bit resolution then this and return type can be long int (or simply multiply them by 2, 
//// max int value 2^15 - 1 but pwm max is 2^16-1, so multiply controller output by 2 )
//
//
//error_new=para.migmode.setvoltage-SCKVOLTAGE;;
//
//integral_new = integral_old + Ki*(error_new + error_old)*Tsampling/2 ;// Area of the trapezoid
//if((integral_new > integral_max) || (integral_new < integral_min))// This is anti wind up protect
//integral_new = integral_old;// in a control system if a parameter gets satured integral term winds up despite no change on the parameter
////for example you are driving a dc motor with a 48V power supply.
////In this case dc motor input voltage is saturated at +-48V.
////There is no meaning but worse results of keeping integral summing the error when H bridge is at full pwm.
////You can simply limit integral term rather than checking all system parameters saturation status that will result an integral wind up.
//
//controller_out = Kp*error_new + Kd*(error_new-error_old)/Tsampling + integral_new;
//
//integral_old = integral_new;
//error_old = error_new;
//
////return controller_out;// the sign of the controller output determines (for example) the transistor couples in conduct in an H bridge
//// so in this case motor direction
//// absolute value must be taken before assigning pwm output
//}		  	    