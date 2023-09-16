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
//	    
	    max_base_amp=35+(ref_wirespeed+rel_wirespeed)/4;	  
	    min_base_amp=15+(ref_wirespeed-rel_wirespeed)/4;     //@no need to check minus 15+(15-25)/4   == 15-2.5==>12.5  


	    
	    if(min_base_amp<MIN_BASE_AMP)
	    min_base_amp=MIN_BASE_AMP;
	    
	    if(max_base_amp>MAX_BASE_AMP)
	    max_base_amp=MAX_BASE_AMP;
	    	          	
		step_base =	(max_base_amp-min_base_amp)/5;
		
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
    if(cSoftwireDetfg == 1)  //AL 1/3/2023
	{
		if(cShortCktDetIncFreqfg == 1)	
		{
		 	/*PFREQ_peakamp	= iALUParaPeakCurr[cAlDia][iIndex] + 30;
			PFREQ_stepamp 	= PFREQ_stepamp + 30;
			PFREQ_baseamp 	= PFREQ_baseamp + 20;
			peaktime		= iALUParaPulseTm[cAlDia][iIndex] + iStepPulseTime  + (iALUParaPulseTm[cAlDia][iIndex]) / 2;
			OPEN_pulsetm	= peaktime>>1;*/
			
			PFREQ_pdaccount	= iALUParaPeakCurr[cAlDia][iIndex] + 30;
			PFREQ_sdaccount 	= PFREQ_stepamp + 30;
			PFREQ_bdaccount 	= PFREQ_baseamp + 20;
			peaktime		= iALUParaPulseTm[cAlDia][iIndex] + iStepPulseTime  + (iALUParaPulseTm[cAlDia][iIndex]) / 2;
			OPEN_pulsetm	= peaktime>>1;	
			//PFREQ_newupstep		=(PFREQ_uppdaccount-PFREQ_bdaccount)/OPEN_pulserisetm;
			//PFREQ_uppdaccount  	=(PFREQ_peakamp*CCSLOPENEW)  -CCOFFSETNEW;
							 			
		}
		else
		{
			/*PFREQ_stepamp 	= stepamp ;
			PFREQ_baseamp 	= baseamp ;		  	
		 	PFREQ_peakamp 	= peakamp;	
			peaktime	  	= iALUParaPulseTm[cAlDia][iIndex] + iStepPulseTime;
			OPEN_pulsetm	= peaktime>>1;*/
			
			PFREQ_sdaccount 	= stepamp ;
			PFREQ_bdaccount 	= baseamp ;		  	
		 	PFREQ_pdaccount 	= peakamp ;	
			peaktime	  	= iALUParaPulseTm[cAlDia][iIndex] + iStepPulseTime;
			OPEN_pulsetm	= peaktime>>1;
			//PFREQ_newupstep		=(PFREQ_uppdaccount-PFREQ_bdaccount)/OPEN_pulserisetm;
			//PFREQ_uppdaccount  	=(PFREQ_peakamp*CCSLOPENEW)  -CCOFFSETNEW;
						 	
		}		
	}
	else
	{		
	   	PFREQ_uppdaccount  	=(PFREQ_peakamp*CCSLOPENEW)  -CCOFFSETNEW;
		PFREQ_pdaccount	 	=(PFREQ_peakamp*CCSLOPENEW)  -CCOFFSETNEW;
		PFREQ_sdaccount	 	=(PFREQ_stepamp*CCSLOPENEW)  -CCOFFSETNEW;
		PFREQ_bdaccount	 	=(PFREQ_baseamp*CCSLOPENEW)  -CCOFFSETNEW;
		PFREQ_newupstep		=(PFREQ_uppdaccount-PFREQ_bdaccount)/OPEN_pulserisetm;
    }   
    if(para.pmigmode.arclength>=40)
    {
    	ALEN_pulsefreq=pulsefreq+((para.pmigmode.arclength-40)*1); //40
    }
    else
    {
    	if(pulsefreq >(40-para.pmigmode.arclength))
       	ALEN_pulsefreq=pulsefreq -((40-para.pmigmode.arclength)*1);
       	else
       	ALEN_pulsefreq = MIN_FREQ;
       	
    }
//---------------------------
//---------------------------
// Initial smooth start
	if(psstatus.creepspeedon == 1)
	{
		ALEN_pulsefreq = (ALEN_pulsefreq * para.pcreepspeedrate )/ 100;		
	}	
//---------------------------     
      flttmpeakvtg=avgmpulsevtg;//avgmpulsevtg;
      if(flttmpeakvtg > 440)
      flttmpeakvtg = 440;
	   {	
			
				// 15072021
		      if(flttmpeakvtg<(target_bvtg-5)) //275)//target_bvtg
		      {
			    PFREQERR=ALEN_pulsefreq*((target_bvtg-flttmpeakvtg)/target_bvtg);			    
			    PFREQ=ALEN_pulsefreq +  (PFREQERR * 0.2) + (iPrevFreqErr * 0.8);			    
		      }
		      else if(flttmpeakvtg>=(target_bvtg-5)&& flttmpeakvtg<=(target_bvtg+5))
		      {
			  	PFREQERR=0;
			  	PFREQ=ALEN_pulsefreq-(PFREQERR * 0.2) + (iPrevFreqErr * 0.8);
			  }
		      else if(flttmpeakvtg>(target_bvtg+5))
		      {
			    PFREQERR=ALEN_pulsefreq*((flttmpeakvtg-target_bvtg)/target_bvtg);
			    PFREQ=ALEN_pulsefreq - (PFREQERR * 0.8) + (iPrevFreqErr * 0.2) ;
			  }			  
			  iPrevFreqErr = PFREQERR;	  
		 
	  } 
		 
	  
	  
	  if(PFREQ<=MIN_FREQ)
	  PFREQ=MIN_FREQ;
	  if(PFREQ>=300)
	  PFREQ=300;				
	  
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
		PID_bdaccount	=PFREQ_bdaccount-2;//+4;//(newbaseamp*CCSLOPENEW)-CCOFFSETNEW;
		PID_newupstep	=(PID_uppdaccount-PID_bdaccount)/pulserisetm;
		PID_newdownstep	=(PID_pdaccount-PID_sdaccount)/pulsefalltm;
     }

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void superfast_PID(void)
{
     //sf_outputmax=64000; //64000;	
	 sf_kpgain = 42;//64;//30;//64;//85//save_location;//save_location;//64;75;//100;//50;//20//200;//100;//arams.Kp;
	 sf_kigain = 2;//2;//2;//1//Recall_location;//pidParams.Ki;
	 sf_kdgain = 20;//20;//8;//15;//8;//5//Recall_location;//8;10;//5;//pidParams.Kd;
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
	
 
		sf_feedback=(ACT_CVOLTAGE);	
	//	sf_feedback=(ACT_CVOLTAGE + 56);//Recall_location); // changes on 27072020	
    	sf_error=sf_setpoint-sf_feedback;


		 sf_pterm=sf_kpgain*sf_error;
		 
		 sf_accumulator+=sf_error;
		 
		 if(sf_accumulator>=sf_outputmax)
		 	sf_accumulator=sf_outputmax;
		 else if(sf_accumulator<=sf_outputmin)
		 	sf_accumulator=sf_outputmin;
		 
		 sf_iterm = sf_accumulator*sf_kigain;
		 sf_dterm=(sf_error-sf_preverror)*sf_kdgain;
		 sf_preverror=sf_error;
		 
		 
		 sf_pid=sf_pterm+sf_iterm+sf_dterm;
		 
		 if(sf_pid>=sf_outputmax)
		 	sf_pid=sf_outputmax;
		 else if(sf_pid<=sf_outputmin)
		 	sf_pid=sf_outputmin;
	 
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

 
    sf_outputmax=64000; //64000;
    if(cSoftwireMIGALUfg == 1)
	{
		 sf_kpgain= 28;//intkp;
   		 sf_kigain= 4;//intki;pidParams.Ki;
   		 sf_kdgain=20;//intkd;pidParams.Kd;
    }  
    else
    {  
	   sf_kpgain= 42;//intkp;
	   sf_kigain= 2;//intki;pidParams.Ki;
	   sf_kdgain=20;//intkd;pidParams.Kd;	 
    }
	
	if((cSoftStrTimefg == 1)) 
	{
		if((iStartSetVoltCnt >= (iSoftStrTimecnt)/3))
		{
			iDummyvoltageref = (iDummyvoltageref - (iStepforStartVoltRef*iSimpleCnt));			
			iStartSetVoltCnt = 0;
			iSimpleCnt++;
			
			if(iSimpleCnt > 2)
			{
				cSoftStrTimefg = 0;
			}
				
		}	
		
	}	
	
	if(cSoftStrTimefg == 1)
	{
	 	sf_setpoint = iDummyvoltageref;		
	}
	else
	{
		sf_setpoint = voltageref;
		iSimpleCnt = 0;	
	}		
    sf_feedback = ACT_CVOLTAGE ;  
	sf_error=sf_setpoint-sf_feedback;


	 sf_pterm=sf_kpgain*sf_error;
	 
	 sf_accumulator+=sf_error;
	 
	 if(sf_accumulator>=sf_outputmax)
	 	sf_accumulator=sf_outputmax;
	 else if(sf_accumulator<=sf_outputmin)
	 	sf_accumulator=sf_outputmin;
	 
	 sf_iterm = sf_accumulator*sf_kigain;
	 //sf_iterm=sf_iterm/10;
	 sf_dterm=(sf_error-sf_preverror)*sf_kdgain;
	 sf_preverror=sf_error;
	 
	 
	 sf_pid=sf_pterm+sf_iterm+sf_dterm;
	 
	 if(sf_pid>=sf_outputmax)
	 	sf_pid=sf_outputmax;
	 else if(sf_pid<=sf_outputmin)
	 	sf_pid=sf_outputmin;
	 
	 sf_pidoutput=sf_pid>>sf_mig_scalefactor;




 	/*sf_feedback = ACT_CVOLTAGE; 
  	sf_error=sf_setpoint-sf_feedback;
    
    sf_pterm=sf_kpgain*sf_error;
	 
	 sf_accumulator+=sf_error;
	 
	 if(sf_accumulator>=sf_outputmax)
	 	sf_accumulator=sf_outputmax;
	 else if(sf_accumulator<=sf_outputmin)
	 	sf_accumulator=sf_outputmin;
	 
	 sf_iterm = sf_accumulator*sf_kigain;
	 sf_dterm=(sf_error-sf_preverror)*sf_kdgain;
	 sf_preverror=sf_error;
	 
	 
	 sf_pid=sf_pterm+sf_iterm+sf_dterm;
	 
	 if(sf_pid>=sf_outputmax)
	 	sf_pid=sf_outputmax;
	 else if(sf_pid<=sf_outputmin)
	 	sf_pid=sf_outputmin;
	 
	 sf_pidoutput=sf_pid>>sf_mig_scalefactor;*/
	 	 
	 //if(sf_pidoutput<=10)	//50) BY MK
	 	//sf_pidoutput=10;
	 if(sf_pidoutput>=800)
	 	sf_pidoutput=800;	 
	 
	
	if(MIGweldon_detectf==0)
	{
		
		migdaccount = 200;
			
	}	  
	else
	{
		migdaccount = sf_pidoutput;		  			  			
	}
  	  	
 
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

