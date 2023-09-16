void Adaptive_freq_pid()
{
   	  /*static int error_old = 0,error_new=0,minoutputfreq=0;
      static long integral_old= 0,integral_new=0,controller_out=0;
      signed long scaled_val1=0,scaled_baseval=0;//,scaled_newval=0;
      signed long minoutmax=0;
      */
	  {
		pidParams1.ReferenceSetpoint1=parcbasevtg;//(para.pmigmode.setvoltage);//+4.0);;//psetcurrent;//440.0;//(para.pmigmode.setvoltage);
		pidParams1.feedback1=CVOLTAGE;//(BVOLTAGE);//psetcurrent;//PVOLTAGE;//(BVOLTAGE);
		//pidParams1.error1 = pidParams1.feedback1 - pidParams1.ReferenceSetpoint1;
		/*	
			if(pidParams1.feedback1>=400)
			pidParams1.feedback1=400;
			else if(pidParams1.feedback1<=50)
			pidParams1.feedback1=50;
		*/	
		pidParams1.error1 = pidParams1.ReferenceSetpoint1 - pidParams1.feedback1;
		pidParams1.absolute_error1=abs(pidParams1.error1);
		pidParams1.outmax1=50000;
		scalefactor1=280;//140;
		//minoutputfreq=5;//  15 for 1.0 ;//20 for 1.2;
		minoutmax=-(pidParams1.outmax1-(scalefactor1*minoutputfreq));
		
		error_new=pidParams1.error1;
		//scalefactor1=pidParams1.outmax1/refpulsefreq;//250;  
		//if((pidParams.error > 0.5) || (pidParams.error < -0.5))
    		{
	    	
	    	/*	
	    		
			pidParams1.integral1 = pidParams1.integral1+pidParams1.error1;
	
			if(pidParams1.integral1 >= (pidParams1.outmax1/(pidParams1.Ki1*fSampling_freq)))
			{
				pidParams1.integral1=(pidParams1.outmax1/(pidParams1.Ki1*fSampling_freq));
			}
			else if(pidParams1.integral1 < -(pidParams1.outmax1/(pidParams1.Ki1*fSampling_freq)))
			{
				pidParams1.integral1=-(pidParams1.outmax1/pidParams1.Ki1);
			}
	
			pidParams1.Kiterm1= pidParams1.integral1;
			pidParams1.Kiterm1=(fSampling_freq*pidParams1.Ki1*pidParams1.integral1);
			
			if(pidParams1.Kiterm1 >= pidParams1.outmax1)
			{
				pidParams1.Kiterm1=pidParams1.outmax1;
			}
			else if(pidParams1.Kiterm1 < -41440)//-pidParams1.outmax1)
			{
				pidParams1.Kiterm1=-41440;//-pidParams1.outmax1;
			}
			
			*/
//##################################################################################################			

/*
//double Tsampling = 0.001// 1kHz frequency, you must call this function by a timer interrupt or delays but i prefer interrupts allways
// you must set this sampling value correct if you want to match simulation results in real systems 
static int error_old = 0;
static double integral_old = 0;
int controller_out;// if pwm is not less than 16 bit resolution then this and return type can be long int (or simply multiply them by 2, 
// max int value 2^15 - 1 but pwm max is 2^16-1, so multiply controller output by 2 )

integral_new = integral_old + Ki*(error_new + error_old)*Tsampling/2 // Area of the trapezoid
if((integral_new > integral_max) || (integral_new < integral_min))// This is anti wind up protect
integral_new = integral_old;
// in a control system if a parameter gets satured integral term winds up despite no change on the parameter
//for example you are driving a dc motor with a 48V power supply.
//In this case dc motor input voltage is saturated at +-48V.
//There is no meaning but worse results of keeping integral summing the error when H bridge is at full pwm.
//You can simply limit integral term rather than checking all system parameters saturation status that will result an integral wind up.

controller_out = Kp*error_new + Kd*(error_new-error_old)/Tsampling + integral_new;

integral_old = integral_new;
error_old = error_new;

scalefactor=280;
50000=178;
for 30hz==41440
for 20hz==44240

*/
		//	if((error_new > 10.0) || (error_new < -10.0))
    		{
				integral_new = integral_old + pidParams1.Ki1*(error_new + error_old)*Tsampling/2; // Area of the trapezoid
				if((integral_new > pidParams1.outmax1) || (integral_new < minoutmax)) //-pidParams1.outmax1))// This is anti wind up protect
				integral_new = integral_old;
				
				controller_out = pidParams1.Kp1*error_new + pidParams1.Kd1*(error_new-error_old)/Tsampling + integral_new;
				integral_old = integral_new;
				error_old = error_new;
				pidParams1.pidoutput1=controller_out;
			}
		//	disp_kiterm=500+integral_old/100;
		//##################################################################################################			
		//	pidParams1.derivitive1 = pidParams1.error1 - pidParams1.previous_error1;
		//	pidParams1.pidoutput1  =  ((pidParams1.Kp1 * pidParams1.error1)
		//                			   + (pidParams1.Kiterm1)
		//               			   + (pidParams1.Kd1 * pidParams1.derivitive1));
				
			if(pidParams1.pidoutput1 >= pidParams1.outmax1)
			{
				pidParams1.pidoutput1 = pidParams1.outmax1;
			}
			else if(pidParams1.pidoutput1 < minoutmax) //pidParams1.outmax1)
			{
				pidParams1.pidoutput1 = minoutmax;//pidParams1.outmax1;
			}
				scaled_val1=(pidParams1.pidoutput1/scalefactor1); //50000
	   			newpulsefreq=178+scaled_val1;//refpulsefreq+scaled_val1;
	   			
	   			//if(newpulsefreq >= 350)//maxpulsefreq)
	   			//newpulsefreq = 350;//maxpulsefreq;
	   			
				//if(newpulsefreq <= 30) //30)//minpulsefreq)
	   			//	newpulsefreq = 30;//30;//minpulsefreq;
	   			//else
	   			//	newpulsefreq = newpulsefreq;
	   			
	   			if(newpulsefreq>0.0)
				 	pulseduty=100000.0/newpulsefreq;
				else
				 	pulseduty=10000;
				 	
				if(pulseduty >=tpulsetime) //tpulsetime=pulserisetime+peaktime+steptime+pulsefalltime;
				{
					newbasetime=pulseduty-tpulsetime;
				 	newsteptime=steptime;
				 	shiftbvtgf=0;
				}
				else
				{
					newbasetime=1;
					pulseontime=(pulserisetime+peaktime+pulsefalltime);
					if(pulseduty>=pulseontime)
						newsteptime=(pulseduty-pulseontime);//-peaktime;
					else
						newsteptime=50;//30;
					
					if(newsteptime<=50)//30)
						newsteptime=50;//30;
					
					shiftbvtgf=1;	
					disptemp=newsteptime;
				}
				PID_basetm		=newbasetime/5;
	   			PID_steptm		=newsteptime/5;
	   			
		        fSampling_freq	=newbasetime*0.01;	//10usec/100000
		        Tsampling=1;//newbasetime*0.001; //0.001;	
	   			//ripplecnt=newbasetime/
				//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	   			
	   			//scaled_baseval2=15000.0/newbasetime;  		//newbasetime in usec
	   			//scaled_baseval2=8000.0/newbasetime;  		//newbasetime in usec
	   			
	   			if(program_number ==20)//26) // //ALU+SI 1.2 AR
	   			{
		   			MAXFBMULTIPLIER=(560.0 -(2.36*para.pmigmode.setwspeed))*100.0;
		   			scaled_baseval2=MAXFBMULTIPLIER/(newsteptime+newbasetime);  		//newbasetime in usec
		   			if(scaled_baseval2>=(para.pmigmode.setwspeed*2.0)) //200)
		   			scaled_baseval2=para.pmigmode.setwspeed*2.0;     //;//200;
		   			
		   			if(scaled_baseval2<=(para.pmigmode.setwspeed*1.2))
		   			scaled_baseval2=para.pmigmode.setwspeed*1.2;
		   			
		   			baseamp=scaled_baseval2;
		   			stepamp=baseamp;
		   			refstepamp=stepamp;
	   			}
	   			else if(program_number ==21) //26) // //ALU+MG 1.2 AR
	   			{
		   			MAXFBMULTIPLIER=(560.0 -(2.36*para.pmigmode.setwspeed))*100.0;
		   			//MAXFBMULTIPLIER=(800.0 -(3.0*para.pmigmode.setwspeed))*100.0;
		   			scaled_baseval2=MAXFBMULTIPLIER/(newsteptime+newbasetime);  		//newbasetime in usec
		   			if(scaled_baseval2>=(para.pmigmode.setwspeed*2.0))//1.5))//2.0)) //200)
		   			scaled_baseval2=para.pmigmode.setwspeed*2.0;//1.5;//2.0;     //;//200;
		   			
		   			if(scaled_baseval2<=(para.pmigmode.setwspeed*0.5))//1.2));//0.75)) //1.2))
		   			scaled_baseval2=para.pmigmode.setwspeed*0.5;//1.2;//0.75;//1.2;
		   			
		   			
		   			if(scaled_baseval2<=30)
		   			scaled_baseval2=30;
		   			
		   			baseamp=scaled_baseval2;
		   			stepamp=baseamp;
		   			refstepamp=stepamp;
	   			}   			
	   			else if((program_number ==35)|| (program_number ==36)) // //ALU 1.6 AR
	   			{
		   			MAXFBMULTIPLIER=(848.0 -(9.32*para.pmigmode.setwspeed))*100.0;
		   			scaled_baseval2=MAXFBMULTIPLIER/(newsteptime+newbasetime);  		//newbasetime in usec
		   			
		   			if(scaled_baseval2>=(para.pmigmode.setwspeed*3.0)) //200)
		   			scaled_baseval2=para.pmigmode.setwspeed*3.0;     //;//200;
		   			
		   			baseamp=scaled_baseval2;
		   			stepamp=baseamp;
		   			refstepamp=stepamp;
	   			}
	   			else
	   			{   			
	   				scaled_baseval2=baseamp;		//FOR FIX BASE CURRENT
	   			}
	   			setpidbamp=scaled_baseval2;
	   		    
	   		    /*	
	   			if(scaled_baseval2>=100)//300) //100)  //300)
	   			{
		   			scaled_baseval2=100;//300;//100; //300;
	   			}
	   			    
	   			if (scaled_baseval2<=baseamp)//40)  //50000 for base voltage calculation 0.5msec
   				{
       				scaled_baseval2=baseamp;//40;
       				PID_sdaccount	=CCOFFSET+(refstepamp*CCSLOPE);
       				shiftbvtgf=0;
       			}
       			else if(scaled_baseval2<stepamp)//baseamp)//200)
   				{
       				stepamp=refstepamp;//100;//scaled_baseval2;//=stepamp;//baseamp;//MAHESH200;
       				PID_sdaccount=CCOFFSET+(stepamp*CCSLOPE);
       				shiftbvtgf=0;
       			}
       			else if(scaled_baseval2>=stepamp)//baseamp)//200)
   				{
       				//stepamp=scaled_baseval2;//=stepamp;//baseamp;//MAHESH200;
       				PID_sdaccount	=CCOFFSET+(scaled_baseval2*CCSLOPE);
       				shiftbvtgf=1;
       			}
				
				*/
			    PID_pulsetm=OPEN_pulsetm;
				//steptm=PID_steptm;
				//basetm=PID_basetm;
				PID_pulserisetm=OPEN_pulserisetm;
				PID_pulsefalltm=OPEN_pulsefalltm;
				PID_startpulsetm=OPEN_startpulsetm;
				PID_uppdaccount=OPEN_uppdaccount;
				PID_pdaccount=OPEN_pdaccount;
				//sdaccount=PID_sdaccount;
				//bdaccount=PID_bdaccount;
				//newupstep=PID_newupstep;
				//newdownstep=PID_newdownstep;
				//refbasetm=PID_refbasetm;
				PID_sdaccount	=CCOFFSET+(refstepamp*CCSLOPE);
       			//shiftbvtgf=0;
       			PID_bdaccount	=CCOFFSET+(scaled_baseval2*CCSLOPE);
       			PID_newupstep	=(PID_uppdaccount-PID_bdaccount)/pulserisetm;
       			PID_newdownstep	=(PID_pdaccount-PID_sdaccount)/pulsefalltm;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	   			
	   		/*	if(pidParams1.pidoutput1<0)
       			   pidParams1.pidoutput1=0;
       	
   				scaled_baseval=baseamp+(pidParams1.pidoutput1/1250.0);
   				if (scaled_baseval<baseamp)//40)  //50000 for base voltage calculation 0.5msec
   				{
       				scaled_baseval=baseamp;//40;
       			}
       			else if(scaled_baseval>stepamp)//baseamp)//200)
   				{
       				scaled_baseval=stepamp;//baseamp;//MAHESH200;
       			}
       			bdaccount	=CCOFFSET+(scaled_baseval*CCSLOPE);
			*/
		}
				//pidParams1.previous_error1 = pidParams1.error1;
    }
	kp1_prev=pidParams1.Kp1;
	ki1_prev=pidParams1.Ki1;
	kd1_prev=pidParams1.Kd1;
	//new_gain_update1();
	pidParams1.previous_error1 = pidParams1.error1;
	//pidParams1.Kp1=pidParams.kpgain;
	//pidParams1.Ki1=pidParams.kigain;
	//pidParams1.Kd1=pidParams.kdgain;
	
	
		/*kigamma1=0.000001*para.pmigmode.setwspeed;//0.000005;////0.00001;//0;//0.1;//5;
	    pidParams1.Ki1=ki1_prev+(kigamma1*pidParams1.error1*integral_new);//pidParams1.integral1);
	    	    
	    if(pidParams1.Ki1>=(para.pmigmode.setwspeed*0.04))//10)
	    pidParams1.Ki1=para.pmigmode.setwspeed*0.04;
	    else if(pidParams1.Ki1<=0.1)
	    pidParams1.Ki1=0.1;    
		*/
		//pidParams1.Ki1=para.pmigmode.setwspeed*0.02;
	    	
}


void new_gain_update1()   //original
{
    unsigned int abs_temperror1=0;
    temperror1=pidParams1.error1;//*0.1;//pidParams1.error1/10.0;
    abs_temperror1=abs(temperror1);
    kpgamma1=0.001;//0.1;//0;//0.001;//0.00001;//0.00001;//0.2;//5;
    kigamma1=0.00001;//0.000005;////0.00001;//0;//0.1;//5;
    kdgamma1=0;//0.2;//5;
    if((pidParams1.error1 > 10.0) || (pidParams1.error1 < -10.0))
    {
        if(abs(pidParams1.error1) > abs(pidParams1.previous_error1) && abs(pidParams1.error1 !=0))
       // if(abs(pidParams1.error1) > abs(pidParams1.previous_error1))// && abs(pidParams1.error1 !=0))
          {
        	//pidParams1.Kp1=kp1_prev+(kpgamma1*pidParams1.error1*pidParams1.error1);
        	pidParams1.Ki1=ki1_prev+(kigamma1*pidParams1.error1*pidParams1.integral1);
        	//pidParams1.Kd1=kd1_prev+(kdgamma1*pidParams1.error1*pidParams1.derivitive1);
        
       /*
        if(temperror1<0)
        {
        	adaptivekp=(kpgamma1*abs_temperror1*abs_temperror1);//temperror1);
            if(pidParams1.Kp1>adaptivekp)
            	pidParams1.Kp1=kp1_prev-adaptivekp;
         	else
         		pidParams1.Kp1=0;
        }
        else
        {
       		adaptivekp=(kpgamma1*temperror1*temperror1);//temperror1);
            pidParams1.Kp1=kp1_prev+adaptivekp;
        }
        //pidParams1.Ki1=ki1_prev+(kigamma1*temperror1*pidParams1.integral1);
        //pidParams1.Kd1=kd1_prev+(kdgamma1*temperror1*pidParams1.derivitive1);
        
        if(pidParams1.Kp1>10)
        {
            pidParams1.Kp1=10;
        }
        else if(pidParams1.Kp1<=0)
        {
            pidParams1.Kp1=10;
        }
        temp_mjp=pidParams1.Kp1;
        */
        pidParams1.Kp1=10;
        
        if(pidParams1.Ki1>50)//1)//5 //10)//20)//100)
        {
            pidParams1.Ki1=50;//1;//5;//10;//20;//100;
        }
        else if(pidParams1.Ki1<=0)
        {
            pidParams1.Ki1=1;
        }
        	//Kiterm=pidParams.Ki;//pidParams.Kiterm/100.0;   //used for display the ki term.
		
	/*	if(pidParams1.Kd1>10)//100)
        {
            pidParams1.Kd1=10;//100;
        }
        else if(pidParams1.Kd1<=0)
        {
            pidParams1.Kd1=1;
        }*/
        pidParams1.Kd1=0;
        
      }
     }
     else
    {
        pidParams1.Kp1=kp1_prev;
        pidParams1.Kd1=kd1_prev;
        pidParams1.Ki1=ki1_prev;
    }
}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//void Adaptive_base_pid()
//{
//   	  //signed long scaled_val2=0,scaled_baseval2=0;
//	  {
//    	pidParams2.ReferenceSetpoint2=(para.pmigmode.setvoltage);;//psetcurrent;//440.0;//(para.pmigmode.setvoltage);
//    	pidParams2.feedback2=RP_BVOLTAGE;//BVOLTAGE;//CVOLTAGE;//(BVOLTAGE);//psetcurrent;//PVOLTAGE;//(BVOLTAGE);
//    	//pidParams1.error1 = pidParams1.feedback1 - pidParams1.ReferenceSetpoint1;
//    	/*if(pidParams1.feedback1>=400)
//    		pidParams1.feedback1=400;
//    	else if(pidParams1.feedback1<=50)
//    		pidParams1.feedback1=50;
//    	*/
//    	pidParams2.error2 = pidParams2.ReferenceSetpoint2 - pidParams2.feedback2;
//    	pidParams2.absolute_error2=abs(pidParams2.error2);
//    	pidParams2.outmax2=50000;
//    	
//    	//scalefactor2=pidParams2.outmax2/refpulsefreq;//250;  
//        scalefactor2=pidParams2.outmax2/(stepamp-baseamp);
//		
//        //if((pidParams.error > 0.5) || (pidParams.error < -0.5))
//    	{
//			pidParams2.integral2 = pidParams2.integral2+pidParams2.error2;
//			if(pidParams2.integral2 >= (pidParams2.outmax2/pidParams2.Ki2))
//			{
//				pidParams2.integral2=(pidParams2.outmax2/pidParams2.Ki2);
//			}
//			else if(pidParams2.integral2 < -(pidParams2.outmax2/pidParams2.Ki2))
//			{
//				pidParams2.integral2=-(pidParams2.outmax2/pidParams2.Ki2);
//			}
//			pidParams2.Kiterm2=pidParams2.integral2;
//			pidParams2.Kiterm2=(pidParams2.Ki2*pidParams2.integral2);
//			if(pidParams2.Kiterm2 >= pidParams2.outmax2)
//			{
//				pidParams2.Kiterm2=pidParams2.outmax2;
//			}
//			else if(pidParams2.Kiterm2 < -pidParams2.outmax2)
//			{
//				pidParams2.Kiterm2=-pidParams2.outmax2;
//			}
//			pidParams2.derivitive2 = pidParams2.error2 - pidParams2.previous_error2;
//			
//			pidParams2.pidoutput2  =  ((pidParams2.Kp2 * pidParams2.error2)
//		                  			   + (pidParams2.Kiterm2)
//		                  			   + (pidParams2.Kd2 * pidParams2.derivitive2));
//			if(pidParams2.pidoutput2 >= pidParams2.outmax2)
//			{
//				pidParams2.pidoutput2 = pidParams2.outmax2;
//			}
//			else if(pidParams2.pidoutput2 < -pidParams2.outmax2)
//			{
//				pidParams2.pidoutput2 = -pidParams2.outmax2;
//			}
//		/*		scaled_val2=(pidParams2.pidoutput2/scalefactor2); //50000
//	   			newpulsefreq=refpulsefreq+scaled_val1;
//	   			if(newpulsefreq >= maxpulsefreq)
//	   				newpulsefreq = maxpulsefreq;
//	   			else if(newpulsefreq <= minpulsefreq)
//	   				newpulsefreq = minpulsefreq;
//	   			else
//	   				newpulsefreq = newpulsefreq;
//	   			
//	   			if(newpulsefreq>0.0)
//				 	pulseduty=100000.0/newpulsefreq;
//				else
//				 	pulseduty=10000;
//				 	
//				if(pulseduty >=(peaktime+steptime))
//				{
//					newbasetime=pulseduty-(peaktime+steptime);
//				 	newsteptime=steptime;
//				}
//				else
//				{
//					newbasetime=1;
//					newsteptime=pulseduty-peaktime;
//				} 	
//	   			basetm		=newbasetime/5;
//	   			steptm		=newsteptime/5;
//      	*/		
////$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	   			
//	   			if(pidParams2.pidoutput2<0)
//       			   pidParams2.pidoutput2=0;
// 				
// 				scaled_baseval22=baseamp+(pidParams2.pidoutput2/scalefactor2);//1250.0);
//   				if (scaled_baseval22<baseamp)//40)  //50000 for base voltage calculation 0.5msec
//   				{
//       				scaled_baseval22=baseamp;//40;
//       			}
//       			else if(scaled_baseval22>stepamp)//baseamp)//200)
//   				{
//       				scaled_baseval22=stepamp;//baseamp;//MAHESH200;
//       			}
//       			bdaccount_rp=CCOFFSET+(scaled_baseval22*CCSLOPE);
//		}
//				//pidParams1.previous_error1 = pidParams1.error1;
//    }
//	kp2_prev=pidParams2.Kp2;
//	ki2_prev=pidParams2.Ki2;
//	kd2_prev=pidParams2.Kd2;
//	//new_gain_update2();
//	pidParams2.previous_error2 = pidParams2.error2;
//	//pidParams1.Kp1=pidParams.kpgain;
//	//pidParams1.Ki1=pidParams.kigain;
//	//pidParams1.Kd1=pidParams.kdgain;
//}
//

void new_gain_update2()   //original
{
    unsigned int abs_temperror2=0;
    temperror2=pidParams2.error2;//*0.1;//pidParams1.error1/10.0;
    abs_temperror2=abs(temperror2);
    kpgamma2=0.001;//0.1;//0;//0.001;//0.00001;//0.00001;//0.2;//5;
    kigamma2=0.000005;////0.00001;//0;//0.1;//5;
    kdgamma2=0;//0.2;//5;
    if((pidParams2.error2 > 10.0) || (pidParams2.error2 < -10.0))
    {
        if(abs(pidParams2.error2) > abs(pidParams2.previous_error2) && abs(pidParams2.error2 !=0))
       // if(abs(pidParams1.error1) > abs(pidParams1.previous_error1))// && abs(pidParams1.error1 !=0))
          {
        	//pidParams1.Kp1=kp1_prev+(kpgamma1*pidParams1.error1*pidParams1.error1);
        	pidParams2.Ki2=ki2_prev+(kigamma2*pidParams2.error2*pidParams2.integral2);
        	//pidParams1.Kd1=kd1_prev+(kdgamma1*pidParams1.error1*pidParams1.derivitive1);
        
       /*
        if(temperror1<0)
        {
        	adaptivekp=(kpgamma1*abs_temperror1*abs_temperror1);//temperror1);
            if(pidParams1.Kp1>adaptivekp)
            	pidParams1.Kp1=kp1_prev-adaptivekp;
         	else
         		pidParams1.Kp1=0;
        }
        else
        {
       		adaptivekp=(kpgamma1*temperror1*temperror1);//temperror1);
            pidParams1.Kp1=kp1_prev+adaptivekp;
        }
        //pidParams1.Ki1=ki1_prev+(kigamma1*temperror1*pidParams1.integral1);
        //pidParams1.Kd1=kd1_prev+(kdgamma1*temperror1*pidParams1.derivitive1);
        
        if(pidParams1.Kp1>10)
        {
            pidParams1.Kp1=10;
        }
        else if(pidParams1.Kp1<=0)
        {
            pidParams1.Kp1=10;
        }
        temp_mjp=pidParams1.Kp1;
        */
        pidParams2.Kp2=10;
        
        if(pidParams2.Ki2>30)//1)//5 //10)//20)//100)
        {
            pidParams2.Ki2=30;//1;//5;//10;//20;//100;
        }
        else if(pidParams2.Ki2<=0)
        {
            pidParams2.Ki2=1;
        }
        	//Kiterm=pidParams.Ki;//pidParams.Kiterm/100.0;   //used for display the ki term.
		
	/*	if(pidParams1.Kd1>10)//100)
        {
            pidParams1.Kd1=10;//100;
        }
        else if(pidParams1.Kd1<=0)
        {
            pidParams1.Kd1=1;
        }*/
        pidParams2.Kd2=0;
        
      }
     }
     else
    {
        pidParams2.Kp2=kp2_prev;
        pidParams2.Kd2=kd2_prev;
        pidParams2.Ki2=ki2_prev;
    }
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void Adaptive_base_pid()
{
   	  //signed long scaled_val2=0,scaled_baseval2=0;
	  {
    	pidParams2.ReferenceSetpoint2=(para.migmode.setvoltage);;//psetcurrent;//440.0;//(para.pmigmode.setvoltage);
    	pidParams2.feedback2=VOLTAGE;//RP_BVOLTAGE;//BVOLTAGE;//CVOLTAGE;//(BVOLTAGE);//psetcurrent;//PVOLTAGE;//(BVOLTAGE);
    	//pidParams2.error2 = pidParams2.feedback2 - pidParams2.ReferenceSetpoint2;
    	pidParams2.error2 = pidParams2.ReferenceSetpoint2 - pidParams2.feedback2;
    	pidParams2.absolute_error2=abs(pidParams2.error2);
    	pidParams2.outmax2=50000;
    	
    	//scalefactor2=pidParams2.outmax2/refpulsefreq;//250;  
        scalefactor2=pidParams2.outmax2/500;//(stepamp-baseamp);
		
        //if((pidParams.error > 0.5) || (pidParams.error < -0.5))
    	{
			pidParams2.integral2 = pidParams2.integral2+pidParams2.error2;
			if(pidParams2.integral2 >= (pidParams2.outmax2/pidParams2.Ki2))
			{
				pidParams2.integral2=(pidParams2.outmax2/pidParams2.Ki2);
			}
			else if(pidParams2.integral2 < -(pidParams2.outmax2/pidParams2.Ki2))
			{
				pidParams2.integral2=-(pidParams2.outmax2/pidParams2.Ki2);
			}
			pidParams2.Kiterm2=pidParams2.integral2;
			pidParams2.Kiterm2=(pidParams2.Ki2*pidParams2.integral2);
			if(pidParams2.Kiterm2 >= pidParams2.outmax2)
			{
				pidParams2.Kiterm2=pidParams2.outmax2;
			}
			else if(pidParams2.Kiterm2 < -pidParams2.outmax2)
			{
				pidParams2.Kiterm2=-pidParams2.outmax2;
			}
			pidParams2.derivitive2 = pidParams2.error2 - pidParams2.previous_error2;
			
			pidParams2.pidoutput2  =  ((pidParams2.Kp2 * pidParams2.error2)
		                  			   + (pidParams2.Kiterm2)
		                  			   + (pidParams2.Kd2 * pidParams2.derivitive2));
			if(pidParams2.pidoutput2 >= pidParams2.outmax2)
			{
				pidParams2.pidoutput2 = pidParams2.outmax2;
			}
			else if(pidParams2.pidoutput2 < -pidParams2.outmax2)
			{
				pidParams2.pidoutput2 = -pidParams2.outmax2;
			}
		/*		scaled_val2=(pidParams2.pidoutput2/scalefactor2); //50000
	   			newpulsefreq=refpulsefreq+scaled_val1;
	   			if(newpulsefreq >= maxpulsefreq)
	   				newpulsefreq = maxpulsefreq;
	   			else if(newpulsefreq <= minpulsefreq)
	   				newpulsefreq = minpulsefreq;
	   			else
	   				newpulsefreq = newpulsefreq;
	   			
	   			if(newpulsefreq>0.0)
				 	pulseduty=100000.0/newpulsefreq;
				else
				 	pulseduty=10000;
				 	
				if(pulseduty >=(peaktime+steptime))
				{
					newbasetime=pulseduty-(peaktime+steptime);
				 	newsteptime=steptime;
				}
				else
				{
					newbasetime=1;
					newsteptime=pulseduty-peaktime;
				} 	
	   			basetm		=newbasetime/5;
	   			steptm		=newsteptime/5;
      	*/		
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	   			
	   			if(pidParams2.pidoutput2<0)
       			   pidParams2.pidoutput2=0;
 				
 				scaled_baseval22=baseamp+(pidParams2.pidoutput2/scalefactor2);//1250.0);
   				
   				if (scaled_baseval22<50)//baseamp)//40)//50000 for base voltage calculation 0.5msec
   				{
       				scaled_baseval22=50;//baseamp;//40;
       			}
       			else if(scaled_baseval22>500);//stepamp)//baseamp)//200)
   				{
       				scaled_baseval22=500;//stepamp;//baseamp;//MAHESH200;
       			}
       			bdaccount_rp=CCOFFSET+(scaled_baseval22*CCSLOPE);
				if(SPI2STATbits.SPITBF==0)
  				{
					DACCSLAT=0;
  					SPI2BUF=28672+bdaccount_rp;//DACREF;//1300;//102A 600
  				}
		}
				//pidParams1.previous_error1 = pidParams1.error1;
    }
	kp2_prev=pidParams2.Kp2;
	ki2_prev=pidParams2.Ki2;
	kd2_prev=pidParams2.Kd2;
	//new_gain_update2();
	pidParams2.previous_error2 = pidParams2.error2;
	//pidParams1.Kp1=pidParams.kpgain;
	//pidParams1.Ki1=pidParams.kigain;
	//pidParams1.Kd1=pidParams.kdgain;
}

