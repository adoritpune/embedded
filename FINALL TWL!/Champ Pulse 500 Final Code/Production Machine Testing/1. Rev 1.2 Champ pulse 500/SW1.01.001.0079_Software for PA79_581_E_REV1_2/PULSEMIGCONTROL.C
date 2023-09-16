struct PFREQ_sckpidParameters
{
   int PFREQ_sckKp;
   int PFREQ_sckKi;
   int PFREQ_sckKd;
   int PFREQ_sckKf;
   int PFREQ_sckTsampling;
   
   int PFREQ_sckReferenceSetpoint;
   int PFREQ_sckfeedback;
   int PFREQ_sckerror;
   int PFREQ_sckerror_new;
   int PFREQ_sckerror_old;
   int PFREQ_sckintegral_old;
   int PFREQ_sckintegral_new;
   int PFREQ_sckderivitive;
   int PFREQ_sckabsolute_error;
   int PFREQ_scksaturated;
   int PFREQ_sckpidoutput;
   int PFREQ_sckoutmax;
   int PFREQ_sckoutmin;
   int PFREQ_sckscalefactor;
}   PFREQ_sckpidParams;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

/*
input: target_bvtg ===> pulsepararr[9];

*/
void PFREQ_pid()   //execution time 60usec
{
//#################################################################################################################	    
  unsigned int ref_wirespeed=0;
  
  unsigned int iFreqMulFactor;
  if(setrefparaf_crater==0)
  ref_wirespeed=para.pmigmode.setwspeed;
  else 
  ref_wirespeed=para.pmigmode.craterspeed;
  
  PFREQ_peakamp=peakamp;
  
  if(para.pulseweldmode==0)	//@ in single pulse mode
  	{
//15;//+(para.pmigmode.setwspeed/8);//20;		  	
	    if(pulsestartcnt<5)
		{	
			PFREQ_baseamp=MIN_BASE_AMP+(ref_wirespeed/4);
			pulsestartcnt++;
		}
		else
		{
			PFREQ_baseamp=MIN_BASE_AMP+(ref_wirespeed/2);
		}
	}
	
   if(para.pulseweldmode==1)  //@ in twin pulse mode
 	{
//	    rel_wirespeed= twinpulseratio>>1; //@ max deviation of wire speed from its set wire speed is 50*0.5=25=>+/-2.5	           
	    max_base_amp=35+(ref_wirespeed+rel_wirespeed)/4;	  
	    min_base_amp=15+(ref_wirespeed-rel_wirespeed)/4;     //@no need to check minus 15+(15-25)/4   == 15-2.5==>12.5  

//----------------------
//cTestfg = 1;  
//iTest = rel_wirespeed;        
//----------------------	 	
	    
	    if(min_base_amp<MIN_BASE_AMP)
	    min_base_amp=MIN_BASE_AMP;
	    
	    if(max_base_amp>MAX_BASE_AMP)
	    max_base_amp=MAX_BASE_AMP;
	    	          	
		step_base =	(max_base_amp-min_base_amp)/5;
				
		if(0)//base_ramp_down_flag==1) //low pulse frequency
		{
			base_amp_twin_pulse=base_amp_twin_pulse-step_base;
			
			pulsefreq=pulsefreq-step_freq;
			
			if(base_amp_twin_pulse<=min_base_amp)	
			base_amp_twin_pulse=min_base_amp;
			
			if(pulsefreq<min_freq)
			pulsefreq=min_freq	;
		}
		else if (0)//psstatus.Hi_speedon==1) //high pulse frequency		
		{
			base_amp_twin_pulse=base_amp_twin_pulse+step_base;
			pulsefreq=pulsefreq+step_freq;
			
			if(base_amp_twin_pulse>=max_base_amp)	
			base_amp_twin_pulse=max_base_amp;
			
			if(pulsefreq>max_freq)
			pulsefreq=max_freq ;
		}
//-----------------
		if(psstatus.Hi_speedon==1)
		{
			base_amp_twin_pulse = max_base_amp ;			
		}
		else
		{
			base_amp_twin_pulse = min_base_amp ;			
		}		
//-----------------	
		PFREQ_baseamp= base_amp_twin_pulse;
	}
		
	if(PFREQ_baseamp<MIN_BASE_AMP)
	PFREQ_baseamp=MIN_BASE_AMP;
	
	if(PFREQ_baseamp<stepamp)//50)
	{
		PFREQ_stepamp=stepamp;//50;//PFREQ_baseamp*2;
	}
	else
	{
		PFREQ_stepamp=PFREQ_baseamp;
	}		
   	PFREQ_uppdaccount  	=(PFREQ_peakamp*CCSLOPENEW)  -CCOFFSETNEW;
	PFREQ_pdaccount	 	=(PFREQ_peakamp*CCSLOPENEW)  -CCOFFSETNEW;
	PFREQ_sdaccount	 	=(PFREQ_stepamp*CCSLOPENEW)  -CCOFFSETNEW;
	PFREQ_bdaccount	 	=(PFREQ_baseamp*CCSLOPENEW)  -CCOFFSETNEW;
	PFREQ_newupstep		=(PFREQ_uppdaccount-PFREQ_bdaccount)/OPEN_pulserisetm;

  
    
    if(para.pmigmode.arclength>=40)
    {
    	ALEN_pulsefreq=pulsefreq+((para.pmigmode.arclength-40)*1);
    }
    else
    {
    	if(pulsefreq >(40-para.pmigmode.arclength))
       	ALEN_pulsefreq=pulsefreq -((40-para.pmigmode.arclength)*1);
       	else
       	ALEN_pulsefreq = MIN_FREQ;
       	
    }
      flttmpeakvtg=avgmpulsevtg;//avgmpulsevtg;
//      if(flttmpeakvtg>440)
//      flttmpeakvtg=440;
	   {
		   
		  	if((program_number == 3)||(program_number == 2)||(program_number == 20) ||(program_number == 35)||(program_number == 36) 
		  	||(program_number == 21)||(program_number == 9) ||(program_number == 10)
		  	)
		  	{
			  	iFreqMulFactor = 10;
			} 
			else
			{
			  	iFreqMulFactor = 12;				
			}	
	      if(flttmpeakvtg<(target_bvtg-5)) //275)//target_bvtg
	      {
		    PFREQERR=ALEN_pulsefreq*((target_bvtg-flttmpeakvtg)/target_bvtg);
		    PFREQ=ALEN_pulsefreq+ (PFREQERR * iFreqMulFactor) / 10;
	      }
	      else if(flttmpeakvtg>=(target_bvtg-5)&& flttmpeakvtg<=(target_bvtg+5))
	      {
		  	PFREQERR=0;
		  	PFREQ=ALEN_pulsefreq-PFREQERR;
		  }
	      else if(flttmpeakvtg>(target_bvtg+5))
	      {
		    PFREQERR=ALEN_pulsefreq*((flttmpeakvtg-target_bvtg)/target_bvtg);
		    PFREQ=ALEN_pulsefreq - (PFREQERR * iFreqMulFactor) / 10 ;
		  }
		  
		  /*
		  if(cFreqErrorupdatefg == 1)
		  {
			  iFbVoltage = avgmpulsevtg;//VOLTAGE;//avgmpulsevtg;
			  iFbVoltage = iFbVoltage >> 1;
		      if(iFbVoltage < (230-5)) //Tbasevoltage //VOLTAGE
		      {
			    iFreqError++;
			    if(iFreqError > save_location)
			     {
					iFreqError = save_location;
				 } 
			    PFREQERR = iFreqError;
			    PFREQ = ALEN_pulsefreq + PFREQERR;
		      }
		      else if((iFbVoltage >= (230-5) )&& (iFbVoltage <= (230+5)))
		      {
			  	PFREQERR =  iFreqError = 0;
			  	PFREQ=ALEN_pulsefreq-PFREQERR;
			  }
		      else if(iFbVoltage > (230+5))
		      {
			    iFreqError++;
			    if(iFreqError > save_location)
			     {
					iFreqError = save_location;
				 } 
			    PFREQERR = iFreqError;
			    PFREQ=ALEN_pulsefreq - PFREQERR ;
			  }
			  cFreqErrorupdatefg = 0;
		  }
		  */
	  }
	  
	  if(PFREQ<=MIN_FREQ)
	  PFREQ=MIN_FREQ;
	  if(PFREQ>=300)
	  PFREQ=300;				

//-----------------------------
//iTest2 = flttmpeakvtg;
//iTest1 = PFREQ;
//cTestfg = 1;
//-----------------------------      

           
      newpulseduty=100000.0/PFREQ;//pulsefreq;
      if(newpulseduty>=10000)
      newpulseduty=10000;
      else if(newpulseduty<=333) //400 to 333 changes on  27072020 
      newpulseduty=333;
      
      newpidstepbasetime=newpulseduty-total_pulse_tm;//260;//(45+15+100+100)=260
      if(newpidstepbasetime<=steptime)//100)//260+100 
      {
    	//newpidstepbasetime=newpidstepbasetime-260;
    	newsteptime=newpidstepbasetime;//newpidstepbasetime;  //fix decay time
	
		if(newsteptime<30)
		{
			newsteptime=30;
	    }   
	    newbasetime=1;
	    shiftbvtgf=1;
      }
		else
		{
			newsteptime=steptime;//200;//100;
			newbasetime=newpidstepbasetime-newsteptime;//(newsteptime+100); //100 FOR DECAY TIME
			shiftbvtgf=0;
		}
		PID_basetm		=newbasetime>>1;///5;
		PID_steptm		=newsteptime>>1;///5;	
		
		PID_pulsetm		=OPEN_pulsetm;
		PID_pulserisetm	=OPEN_pulserisetm;
		PID_pulsefalltm	=OPEN_pulsefalltm;
		PID_startpulsetm=OPEN_startpulsetm;
		PID_uppdaccount	=OPEN_uppdaccount;//PFREQ_uppdaccount;//OPEN_uppdaccount;
		PID_pdaccount	=PFREQ_pdaccount;//OPEN_pdaccount;
		PID_sdaccount	=PFREQ_sdaccount;//(newstepamp*CCSLOPENEW)-CCOFFSETNEW;
		PID_bdaccount	=PFREQ_bdaccount;//(newbaseamp*CCSLOPENEW)-CCOFFSETNEW;
		PID_newupstep	=(PID_uppdaccount-PID_bdaccount)/pulserisetm;
		PID_newdownstep	=(PID_pdaccount-PID_sdaccount)/pulsefalltm;
     }
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void superfast_PID(void)
{
 //TORCHTEST1IPIO=0;
 //TORCHTEST1IOLAT=1;
 sf_kpgain=30;//64;//85//save_location;//save_location;//64;75;//100;//50;//20//200;//100;//arams.Kp;
 sf_kigain=1;//2;//1//Recall_location;//pidParams.Ki;
 sf_kdgain=15;//8;//5//Recall_location;//8;10;//5;//pidParams.Kd;
	 	if((para.pulseweldmode==1)&&(cLoadVoltfg == 1))
	 	{
		 	if(pstowfstr.pulse_freq == '+')
		 	{
	 			sf_setpoint=parcbasevtg + iTwinSetVolt;				 	
			}
			else
			{
	 			sf_setpoint=parcbasevtg - iTwinSetVolt;					
			}		 	
		}
		else if((para.pulseweldmode==1)&&(cLoadVoltfg == 0))
		{
	 		sf_setpoint=parcbasevtg ;//- iTwinSetVolt;		// IN MIG mode iTwinSetVolt = 0;
		}
		else 
		{
			sf_setpoint=parcbasevtg;
		}			 
	if((program_number == 20) ||(program_number == 35)||(program_number == 36) ||(program_number == 21)||(program_number == 9) ||(program_number == 10))
	{
 		sf_feedback=(ACT_CVOLTAGE);		
	}
	else
	{
 		sf_feedback=(ACT_CVOLTAGE + 56);//Recall_location); // changes on 27072020			
	}		
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
 //sf_pid+=sf_kdgain*(sf_error-sf_preverror);
 sf_dterm=(sf_error-sf_preverror)*sf_kdgain;//(sf_error-sf_preverror)<<sf_kdgain;
 sf_preverror=sf_error;
 ;
 sf_pid=sf_pterm+sf_iterm+sf_dterm;
 if(sf_pid>=sf_outputmax)
 sf_pid=sf_outputmax;
 else if(sf_pid<=sf_outputmin)
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
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void MIG_superfast_PID(void)
{
 //TORCHTEST1IPIO=0;
 //TORCHTEST1IOLAT=1;
 sf_outputmax=51200;// 64000;// 128*500=64000 51200;  //128*400amp
 if(1)//;//para.migmode.burnback==0)
 {
 	sf_kpgain=intkp;//64;//75;//100;//50;//20//200;//100;//arams.Kp;
 	sf_kigain=intki;//2;//10;//2;//pidParams.Ki;
 	sf_kdgain=intkd;//8;//10;//5;//pidParams.Kd;
 } 
 else
 {
/*
 	sf_kpgain= 85;//intkp;// 64;//75;//100;//50;//20//200;//100;//arams.Kp;
	sf_kigain= 2;//intki;//2;//10;//2;//pidParams.Ki;
 	sf_kdgain=0;//intkd;//8;//10;//5;//pidParams.Kd;	 
*/
	 
 	sf_kpgain= 30;//save_location;//85;//intkp;// 64;//75;//100;//50;//20//200;//100;//arams.Kp;
 	sf_kigain= 1;//Recall_location;//2;//intki;//2;//10;//2;//pidParams.Ki;
 	sf_kdgain= 0;//para.migmode.inductance;//intkd;//8;//10;//5;//pidParams.Kd;	 
 } 

 
 sf_setpoint=voltageref;//para.migmode.setvoltage;//parcbasevtg;//FRQbasevtg;//parcbasevtg;  //para.migmode.setvoltage
 sf_feedback=ACT_CVOLTAGE;//ACT_CVOLTAGE;
 sf_error=sf_setpoint-sf_feedback;
 
 if(0)//program_number==13)
 {
	sf_outputmax=32000;
	sf_kpgain= save_location;
 	sf_kigain= Recall_location;
 	sf_kdgain= 20;
	mult_factor= para.migmode.inductance;
	 
	if(sf_feedback <= 80)
		sf_pterm=(sf_kpgain*sf_error*mult_factor)/10;
	else		
		sf_pterm=sf_kpgain*sf_error;
	
	sf_accumulator+=((sf_error*sf_kigain)/10);
		
	if(sf_accumulator>=sf_outputmax)
	{
 		sf_accumulator=(sf_outputmax);
	}
	else if((sf_accumulator <= sf_outputmin))
	{
		sf_accumulator= sf_outputmin; 
	}
			
		sf_dterm=(((sf_error-sf_preverror)*sf_kdgain)/10);
		sf_preverror=sf_error;
		
		sf_pid=sf_pterm+sf_iterm+sf_dterm;
		
		if(sf_pid>=sf_outputmax)
			sf_pid=sf_outputmax;
		else if(sf_pid<=sf_outputmin)
			sf_pid=sf_outputmin;				
 }
 
 sf_pterm=sf_kpgain*sf_error;//sf_error<<sf_kpgain;//sf_kpgain*sf_error;			//-----pterm;
 
 sf_accumulator+=sf_error;
 if(sf_accumulator>=sf_outputmax)
 sf_accumulator=sf_outputmax;
 else if(sf_accumulator<=sf_outputmin)
 sf_accumulator=sf_outputmin;
 //sf_iterm=sf_accumulator<<sf_kigain;
 sf_iterm=sf_accumulator*sf_kigain;
 
 //sf_pid+=sf_accumulator;
 //sf_pid=sf_pid<<sf_kigain;
 //sf_pid+=sf_kdgain*(sf_error-sf_preverror);
 sf_dterm=(sf_error-sf_preverror)*sf_kdgain;//(sf_error-sf_preverror)<<sf_kdgain;
 sf_preverror=sf_error;
 ;
 sf_pid=sf_pterm+sf_iterm+sf_dterm;
 if(sf_pid>=sf_outputmax)
 sf_pid=sf_outputmax;
 else if(sf_pid<=sf_outputmin)
 sf_pid=sf_outputmin;
 ;
 sf_pidoutput=sf_pid>>sf_mig_scalefactor;
 if(sf_pidoutput<=20)
 sf_pidoutput=20;
 if(sf_pidoutput>=500)//500)
 sf_pidoutput=500;//500;

  if(MIGweldon_detectf==0)
  {
    migdaccount=200;
  }	  
  else
  {
	 migdaccount=sf_pidoutput;
  }	  	

 /*if(cvopenloopcnt>10) //60)
 {
   	 migdaccount=sf_pidoutput;
   	 //sckdaccount   =(sf_pidoutput*CCSLOPENEW)-CCOFFSETNEW;
 }
 else
 {
    cvopenloopcnt++;
    migdaccount=para.migmode.setwspeed;//50;
   	//sckdaccount   =(50.0*CCSLOPENEW)-CCOFFSETNEW;
 }
*/
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void superfast_PID22(void)
{
 //TORCHTEST1IPIO=0;
 //TORCHTEST1IOLAT=1;
 sf_kpgain=75;//100;//50;//20//200;//100;//arams.Kp;
 sf_kigain=2;//10;//2;//pidParams.Ki;
 sf_kdgain=10;//5;//pidParams.Kd;
 
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
 sf_pidoutput=sf_pid>>sf_scalefactor;   //1000
// scaled_sf_pidoutput=peakamp*sf_pidoutput/1000;
 
 
 
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

