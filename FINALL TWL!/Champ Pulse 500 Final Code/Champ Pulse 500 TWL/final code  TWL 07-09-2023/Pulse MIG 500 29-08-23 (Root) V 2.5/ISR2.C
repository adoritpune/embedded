void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void)
{
   IFS1bits.INT1IF =0;
}

void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt(void)
{
         IFS1bits.INT2IF =0;
         /*if(Aweldon_detectf==0)
      {
         Aweldonf=1;
         //Aweldon_detectf=1;
         INTCON2bits.INT2EP=1;//0;      //0 Positive EDGE
         //INCHTESTIPLAT=1;
         //Aweldon_detectf=1;
      }
      */ 
		if(Aweldon_detectf==0)
		{
			Aweldon_detectf=1;
			INTCON2bits.INT2EP=0;      //0 Positive EDGE
			//INCHTESTIPLAT=1;
		}		
		else
		{
			//if(weldonf==0)
			{
			Aweldon_detectf=0;
			}
			INTCON2bits.INT2EP=1;      //1 Negative EDGE
			//INCHTESTIPLAT=0;
		}
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
   IFS0bits.T1IF=0;                            //1 MSEC
   count_1ms++; 
   count_key_5000ms++;   

 //-----------------------------------
 /*	if(cChardlyStrfg == 1)
 	{
	 	if(cCharDelay == 0)
	 	{
		 	cCharDelay = 0;
		 	cChardlyStrfg = 0;
		 	cFrameFoundfg = 1;
		 	cFrameStrfg = 0;
		} 		
		else
		{
			cCharDelay--;		
		}	 	
	}	*/
//------------------------------------
		if(cDefaultLoadfg == 1)
		{
			if(iDefaultLoadCntr == 0)
			{
				iDefaultLoadCntr = 0;
				cDefaultLoadfg = 0;
				if(weldmode=='P')
				{
					iLoadBlockCnt = PMIGMINPROGRAMLOAD;
				}
				else
				{
					iLoadBlockCnt = MIGMINPROGRAMLOAD;
				}										
			}
			else
			{
				iDefaultLoadCntr--;
			}		
		}	
		if(cSoftStrfg == 1)
		{
			cSoftStrCnt++;
			cSoftStrfg = 0;
		}
		
		if(cKeyPressStartfg == 1)				
		{
			if(iKeyDoubleChkCntr == 0)
			{
				cKeyPressStartfg = 0;
				iMacMenuCntr = 0;
				iKeyDoubleChkCntr = KEYDOUBLECHKCNT;
			}
			else
			{
				iKeyDoubleChkCntr--;
			}		
		}	
 //-----------------------------------
	if(count_1ms>=2)
	{
		count_1ms=0;  
		//if(torch!='T')
		{
		display_data();                        //DISPLAY UPDATE AFTER 2MSEC
		}
		count_1ms=0;  
	}

	
   if(count_tx2_1ms>=10)//50)  //update status after 10ms
   {	  
      count_tx2_1ms=0;
      count_tx2++;
      if(count_tx2 < 50)//50) //10) //update data after 200msec
      {
         pstowfstr.psstatusbyte=psstatusu.psstatusbyte[0];
         if(starttx2==0)
         {
               startstatustx2=1;
               tx2statuscounter=0;
               U2TXREG='#';
         }
      }
      if(count_tx2 >= 20)//50) //10)
      {
         count_tx2=0;
         transmit2f=1;
         trans2_onf=1;
      }
   }
   if(iCntChk != 0)
   {
	   iCntChk --;
   }
   
   
   
   if(count_20ms>=20)
   {
      count_20ms=0;
      if(torchonstatus!='T' && weldcyclestrt==0)
      {
         keyreadf=1;
         //Toggle_pin();
      }

      if((U1STAbits.OERR==1) || (U1STAbits.FERR==1) || (U1STAbits.PERR==1))
      {
         U1STAbits.OERR=0;
         U1STAbits.FERR=0;
         U1STAbits.PERR=0;
      }   
      if((U2STAbits.OERR==1) || (U2STAbits.FERR==1) || (U2STAbits.PERR==1))
      {
         U2STAbits.OERR=0;
         U2STAbits.FERR=0;
         U2STAbits.PERR=0;
      }   
   }
   	if(key=='A')//key A pressed for 5 sec, OCV ON @sbm
	{
		if(count_key_5000ms>5000)  //5 sec 
		{
			mig_ocv_check_f=1;      //used in keypad.c @sbm
			//count_key_5000ms=0;
			//Type.mma=1;
		
		}
	
	}
	else
	{
	    count_key_5000ms=0;
	    mig_ocv_check_f=0;
	
	}
   
   if(emg_sendf==1)      //update status after 1ms
   {
      count_tx2_1ms=0;
      count_tx2=0;
      emg_sendf=0;
      pstowfstr.psstatusbyte=psstatusu.psstatusbyte[0];
      startstatustx2=1;
      tx2statuscounter=0;
      U2TXREG='#';
   }

if(power_on_flag==1)
{
	count_20ms++;   
	count_200ms++;
	count_500ms++;
	count_500ms1++;
	count_1sec++;
	count_tx2_1ms++;
	err11_delay_counter++;
	communication_time_out++;	
	arcontime.msec++;
	count200Msec++;
	
    //-------------
   	iSampleCnt++;
   	count_6ms++;
   	idel++;
   	itemp++;
   	iDlyCnt++;
	iStarDisplaycnt++;
	iCursorBlinkcnt++;
	iPFREQTmr++;
	itstcnt++;
	iArcMissCnt--;
	iOCVManipulationCnt++;
	
	if((weldcyclestrt == 0) && (cWeldDataLogfg == 1)) 
	{
		if(iFileReopenCntr == 0)
		{
			iFileReopenCntr = 0;	
		}
		else
		{		
			iFileReopenCntr--;
		}	
	}	


	
	/*if(iArcMissCnt <= 0)
	{
		iArcMissCnt = 0;	
	}*/	
	if(cSoftStrTimefg == 1)
	{
		iStartSetVoltCnt++;
	}		
    //-------------	
    if((cMacMenufg == 1))
    {
		count700MS++;    
	} 
//--------------------------------------------------------------------------------------
/*	if(iPFREQTmr >= Recall_location)
	{
		iPFREQTmr = 0;
		if((weldmode=='P') && (weldcyclestrt==1) )
		{
			PFREQ_pid();    
		}
	}*/	
    
//-------------------------------------------------------------------------------------------------------
	if(disparclen == 1)
	{
		/*if(itgtcnt >=300)
		{
			itgtcnt = 0;	
			if(ctog)
			{
				//Type.job = 1;
				datafordebugonlcd(1,2);
				ctog = 0;	
			}
			else
			{
				//Type.job = 0;
				datafordebugonlcd(2,1);
				ctog = 1;		
			}		
		}*/		
		if(iALtoVoltShiftCNT == 0)
		{
			iALtoVoltShiftCNT = 0;
			disparclen = 0;	
			Type.voltage		=1;
			Type.arclength		=0;
			Typedp.digitdp5		=1;				
		}
		else
		{
			iALtoVoltShiftCNT--;
		}	
	}
	    
//------------------Hot Start--------------------------------------------------------------------------
	if((cHotstartfg == 1) && (weldonf == 1))
	{
		iHotStartTime++	;
		if(iHotStartTime >= 1000)
			cHotstartfg = 0;
	}
	else 
		iHotStartTime = 0;	
		
//--------------------------------------------------------------------------------------------    
	
/*********************Arc On Time Save*********************************************/
	if(arcontime.msec>1000)
	{
		arcontime.msec=0;
		
		if(weldcyclestrt==1 && CURRENT>ERROR_4_THRESHOLD) //weldcyclestr== 1 in only MIG and P-MIg Welding
		{
			arcontime.sec++;
			if(arcontime.sec>=60)
			{
				arcontime.sec=0;
				arcontime.min++;
				//iMinStart++;
			}
			if(arcontime.min>=60)
			{
				arcontime.min=0;
				arcontime.sec=0;
				arcontime.hr++;
				//iHrStart++;
				//iMinStart = 0;
			}
			if(arcontime.hr>=999)
			{
				arcontime.min=9;
				arcontime.sec=9;
				arcontime.hr=9;
			}
		}
	}
	
	if(count_1sec >= 1000)
	{
		count_1sec = 0;
		
		if(cPWstarblinkcnt !=0)
		{
			cPWstarblinkcnt --;
			if(setPasswordfg == 1)
			{
				setPasswordfg = 0;
			}
		}
	}	
//----------------------- HR:MIN:SEC -------------------------------------------------------------------
	if(cWeldDataLogfg == 1)//cWeldDataLogfg)
	{
		iHrMinSeccnt++;
	}
	else
	{
		iHrMinSeccnt = 0;
	}
//	RealTime();	

	if(iHrMinSeccnt >= 1000)
	{
		iHrMinSeccnt = 0;
		iseconds++;
	}		
	if(iseconds>=59)
	{
		iseconds = 0;
		iMinutes++;
		iMinStart++;
	}
	if(iMinutes >= 59)
	{
		iHours++;
		iHrStart++;
		
		if(iHrStart > 999)
		{
			iHrStart = 0;	
		}	
		
		if(iHours >= 23 && (iMinutes >= 59))
		{
			iMinutes = 0;
			iHours = 0;
			iseconds = 0;	
		}	
		
		iMinutes = 0;
	}		

//------------------------------------------------------------------------------------------------------			

/*********************communication Error*********************************************/
    if(communication_time_out>=COMMUNICATION_TIME_OUT && (weldmode=='G' || weldmode=='P') )
    {
    comm_errorf=1; 
    communication_time_out=COMMUNICATION_TIME_OUT;
    }
    else
    {
   	comm_errorf=0;
    }
    
    
/*********************Gas Water Selection*********************************************/        

		if(GASWATERIP==1 && PRESSERRIP==1 && (weldmode=='G' || weldmode=='P') )
        {
            dVal_press0=0;
            if(++dVal_press1>1000)
            {
            pressure_error_flag=1;
            dVal_press1=1000;
            }
        }
        else
        {
            dVal_press1=0;
            if(++dVal_press0>1000);
            {
            pressure_error_flag=0;
            dVal_press0=1000;
           }
        }
        
        
/*********************No current Error*********************************************/        
		if(error_4_check4t==1)
		{
		cntsecond_er4++;
			if(CURRENT<ERROR_4_THRESHOLD)  
			{
			error4_flag=1;
			}
			else
			{
			error4_flag=0;
			cntsecond_er4=0;
			}	
		
			if((error4_flag==1)&&(cntsecond_er4>ERROR4_DEBOUNCE_TIME))
			{
			ERROR_4_errorf=1;
			cntsecond_er4=ERROR4_DEBOUNCE_TIME;	
			}
		
		}
		else
		{
			cntsecond_er4=0;
		}	 
/****************************************************************************************/


//twinpulseperiod=10000.0/para.twinpulsefreq;
//twinpulseonperiod=twinpulseperiod*para.twinpulseduty/100.0;
//twinpulseoffperiod=twinpulseperiod-twinpulseonperiod;

 if(pulseweldonf==1 && psstatus.twinpulseon==1)
   {
      twinpulsecnt++;
      if(twinpulsecnt>=twinpulseonperiod && psstatus.Hi_speedon==1)//100)         //default 100ms for 1hz freq
      {
         twinpulsecnt=0;
         psstatus.Hi_speedon=0;
         base_ramp_down_flag=0;
         base_amp_twin_pulse=min_base_amp;      
//         pulsefreq=Lo_pulsefreq;  
		cLoadFreqfg = 1;
		iLoadFreqCntr = LOADFREQCNT; 
		ARCONOKLAT = 0;     
      }
      else if(twinpulsecnt>=twinpulseoffperiod && psstatus.Hi_speedon==0)//100)         //default 100ms for 1hz freq
      {
         twinpulsecnt=0;
         psstatus.Hi_speedon=1;
//         pulsefreq=Hi_pulsefreq;
		cLoadFreqfg = 1;
		iLoadFreqCntr = LOADFREQCNT;
		ARCONOKLAT = 1;		
      }

      if(twinpulsecnt>=(twinpulseonperiod-twn_rmp_down_offst_tm) && psstatus.Hi_speedon==1)//100)         //default 100ms for 1hz freq
      {
         base_ramp_down_flag=1;
      }
   }
//--------------------------------------------------	   
//--------------------------------------------------
	if(cLoadFreqfg == 1)
	{  		
  		if(iLoadFreqCntr == 0)
  		{
  			cLoadFreqfg = 0;
  			if(psstatus.Hi_speedon == 1)
  			{
         		pulsefreq=Hi_pulsefreq;	  
		  		cLoadVoltfg = 1;         		       					
	  		}
	  		else
	  		{
         		pulsefreq=Lo_pulsefreq; 
         		cLoadVoltfg = 0;
		  	}			  		
	  	}
	  	else
	  	{
			iLoadFreqCntr --;		  	
		}				
	}	   
//-------------------------------------------------- 
	if(cLoadReffg == 1)
	{
  		if(iLoadRefCntr == 0)
  		{
	  		genpwmcvref(cvoffsetref,voltageref);
  			cLoadReffg = 0;	
  			cWeldStartfg = 0;			  		  			
	  	}
	  	else
	  	{
			iLoadRefCntr --;		  	
		}	
	}	
//--------------------------------------------------

	if(cStartPulsefg == 1)
	{
		if(cPulseCnt == 0)
		{
			cPulseCnt = 0;
			cStartPulsefg = 0;
			migdaccount = 0;		
		}
		else
		{
			cPulseCnt--;		
		}
	}
			
//--------------------------------------------------
	if((cEndPulsefg == 1)&&(cWaitToStopMtrfg == 0))
	{
		if(cEndPulseCnt == 0 )
		{
			cEndPulseCnt = 0;
			cEndPulsefg = 0;
				CCCVCTRLLAT		=CCMODE;
				SHDNLAT			=OFF;								
				ARCONLAT		=OFF;  					
		    	if(SPI2STATbits.SPITBF==0)
				{
					DACCSLAT	=0;
					daccount   =0;//(cENPULSECURR*CCSLOPENEW)-CCOFFSETNEW;
					SPI2BUF		=28672+daccount;     		//850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
				}	
		}
		else
		{
			cEndPulseCnt--;
		}		
	}
	if(cWaitToStopMtrfg == 1)			
	{
		if(iWaitToStopMtrCnt == 0)
		{
			cWaitToStopMtrfg = 0;
			cEndPulsefg = 1;	
			cEndPulseCnt = ENPULSECNT;
			ENPULSECURR = LoadPeakCurrentasperDia();						
//			oper=burn;
		}	
		else
		{
			iWaitToStopMtrCnt--;
		}	
	}	
	if((cEndPulsefg == 1)||(cStartPulsefg == 1)||(cWaitToStopMtrfg == 1))
	{
		genpwmcvref(cvoffsetref,voltageref);		
	}					
//-------------------------------------------------- 
   
   if(count_200ms>=20)//200)
   {
      count_200ms=0;
      check_torch_action();
      //READ_PORTPIN();
      if(setlcdweldparameter!=0)
      {
            if(point>=20) //00)
            {
            if(lcdscan_flag==1)
               lcdscan_flag=0;
            else
               lcdscan_flag=1;
            point=0;
            }
            else
               point++;
      }
   }
   if(count200Msec>=500)
   {
	   c200Msecfg = 1;
	   count200Msec=0; 
   } 
   
   //if(count_1sec>=1000)
   //{
   //   count_1sec=0;
   //   transmit2f=1;
   //}
   
   if(strttmr==1)         //during only preflow and postflow, burnback time only
      {
         timerval++;
         if(timerval >= 100 && (oper != burn))
         {
               cntsecond++;
               timerval=0;
         }
         if(timerval >= 20 && (oper == burn))
         {
               cntsecond++;
               timerval=0;
         }         
      }
      
      }//power on flag
} 
/************************************************************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)  //50usec
{
   IFS0bits.T2IF=0; 
   PR2=900;//900=30usec,1470=50usec, 2940=100usec 3600;//120usec 1470;//2948;//1470;//29387;     //1 ms 0X6000;   //Load the Period register with the value 0xFFFF 0x72cb interrupt after every 1.20msec
   IEC0bits.T2IE	=0;	T2CONbits.TON	=0;
   //Toggle_pin();
   if(weldmode=='M')
   {
      if(adcreadoverf==1)
      {
            adcreadoverf=0;
            INT_sck_voltage_pid();   //temporary disabled for static
            
      }
   } 
   /////////////////////////////////////////////////////////////////////////////  
   else if((weldmode=='G') && (weldcyclestrt==1))
   {
     if(adcreadf==1)
     {
        ACT_CVOLTAGE=AFvtg>>2; 
        
         if((voltageref>0) && (pidParams2.migweldmode == 0))
			{
				if(ACT_CVOLTAGE<=(voltageref-(voltageref*0.15)) && (ucLowState==0)&&(ucCCCVCONTROL==0))	//&& (ucSecondP==0))
				{
					ucLowState=1;  ucCCCVCONTROL=1;uiIntCount=0;  
				}
				if(ACT_CVOLTAGE>=(voltageref+(voltageref*0.15)) && (ucLowState==1)&&(ucCCCVCONTROL==0))
				{
					ucLowState=0;
				}
				if((ACT_CVOLTAGE>=(voltageref-(voltageref*0.35)))&&(ucSecondPStart==0)&& (ucSecondP==1))
				{
					uiIntCount=0;LEDGP3LAT=1; ucSecondPStart=1;	 ucCCCVCONTROL=3;
				}
				
				if(ucCCCVCONTROL>0)
				{
					uiIntCount++;
					if(para.migmode.setcurrent<=170)
					{		
						if(uiIntCount==7)   	//9		
						{
							ucCCCVCONTROL=2;		
						}
						else if(uiIntCount>7)   //10
						{	
							ucCCCVCONTROL=0; ucSecondP=1;uiIntCount=0;		
						}
				 	}
				 	else if((para.migmode.setcurrent>170)&&(para.migmode.setcurrent<=216))
					{		
						if(uiIntCount==3)   			
						{
							ucCCCVCONTROL=2;		
						}
						else if(uiIntCount>3)   
						{	
							ucCCCVCONTROL=0; ucSecondP=1;uiIntCount=0;		
						}
				 	}  
				}
				if(ucSecondPStart==1)
				{
					uiIntCount++;
					if(uiIntCount==1)
					{
				 	 	//ucCCCVCONTROL=4;	
				 	}	
				 	else if(uiIntCount>2)
					{
				 	 	uiIntCount=0;LEDGP3LAT=0;ucSecondPStart=0;ucSecondP=0; ucCCCVCONTROL=0;
				 	}
				}	
			}
          
	         if(ACT_CVOLTAGE <= 100)
		     {
		         ACT_CVOLTAGE=100;
		     } 
	         if(ACT_CVOLTAGE>=800)// 800
	         {
	           ACT_CVOLTAGE=800;//800
	         }
	         MIG_superfast_PID();	      
	         adcreadf=0;
	         if(MIGweldon_detectf == 1)
	         {
			 	genpwmcvref(0,voltageref);                      
			 }
        
        
        /*if(pidParams2.migweldmode == 0)  //ROOT Mode
        {
	       
		 
		 }
		 else if(pidParams2.migweldmode==1) // Normal Mig Mode 
		 {
			if(ACT_CVOLTAGE <= 100)
		     {
		         ACT_CVOLTAGE=100;
		     } 
	         if(ACT_CVOLTAGE>=800)// 800
	         {
	           ACT_CVOLTAGE=800;//800
	         }
	         MIG_superfast_PID();	      
	         adcreadf=0;
	         if(MIGweldon_detectf == 1)
	         {
			 	genpwmcvref(0,voltageref);                      
			 } 
		 
		 
		 }*/
		 
		 
		 
      }   
    }
    /////////////////////////////////////////////////////////////////////////////////
     
   else if((weldmode=='P') && (weldcyclestrt==1) )
   {
      if(adcreadf==1)
      {
         //Toggle_pin();
         adcreadf=0;
         ACT_CVOLTAGE=AFvtg>>2;  //@convert adc count to actual voltage
          if(ACT_CVOLTAGE <= 100)
	     {
	         ACT_CVOLTAGE=100;
	     }    
         if(ACT_CVOLTAGE>=700) //500)
         {   
         	ACT_CVOLTAGE=700;   //500;
         }   
         superfast_PID();
         scaled_sf_pidoutput=sf_pidoutput;
         sckdaccount=scaled_sf_pidoutput*CCSLOPENEW;//(sf_pidoutput*CCSLOPENEW);//-CCOFFSETNEW;    
      }       
   }   
     
	IEC0bits.T2IE	=1;	T2CONbits.TON	=1;
}

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)  //interrupt at 100usec
{
   IFS2bits.INT3IF=0;
   PR3=29387;
   //Toggle_pin();
   IEC2bits.INT3IE=0;            //DISABLE INTERRUPT
} 

void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void)  //interrupt at 50usec
{
   IFS1bits.T5IF=0;
   PR5      =600;//725=25usec;//300=10usec , 600=20usec 1475=50usec;  //1400;//293;//586;
   count_1ms_ext++; //disabled by mahesh
   //Toggle_pin();
         
   //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    EXTINT1IO    =1;   
    EXTINT2IO    =1;   
/*   if(EXTINT1IP==1)   //ZERO OCV
   {
      TORCHTESTIPIO=0;
      TORCHTESTIOLAT=1;
   }
   else         //OCV above 15V
   {
      TORCHTESTIPIO=0;
      TORCHTESTIOLAT=0;
   }      
*/   
   if(count_1ms_ext>=1)//4)   //4=50USEC*4=200usec
    {
       count_1ms_ext=0;   
       EXTINT1IO    =1;   
       EXTINT2IO    =1;   
      if(pincheck==0)
      {
         extint1status1=EXTINT1IP;
         extint2status1=EXTINT2IP;
         pincheck=1;
      }
      else if(pincheck==1)
      {
         extint1status2=EXTINT1IP;
         extint2status2=EXTINT2IP;
         ext1ans      =(extint1status1   ==   extint1status2    ? 1:0);
         ext2ans      =(extint2status1   ==   extint2status2    ? 1:0);
         
         if(ext1ans==1) //voltage below 9 volt
         {
            //Toggle_pin();
            Vweldon_detectf=(extint1status1   ==   1    ? 1:0);//;'T':'X');
            if(weldmode=='G')
            {
               if(Vweldon_detectf==1) //VOLTAGE BELOW 9V ------SLOW RIsE
               {
                  piditeration=1;
                  pidfactor=1;
                  //TORCHTESTIPIO=0;
                  //TORCHTESTIOLAT=1;
                  shortcktonf=1;
                  //if(shortcktonf==1)
                  //{
                  //   shortcktonf=0;
                     //Total_SCKVresult=0;
                     //sckpidParams.sckintegral_old=0;
                  //}      
               }   
               else            //VOLTAGE IS ABOVE 15V----FAST FALL            
               {
                  piditeration=1;
                  if(shortcktonf==1)
                  {
                     shortcktonf=0;
                     //INT_sckpidParams.INT_sckintegral_old =INT_sckpidParams.INT_sckintegral_old/2;
                  }   
                  pidfactor=1;
                  //TORCHTESTIPIO=0;
                  //TORCHTESTIOLAT=0;
               }
            }
            /*if(Vweldon_detectf==1) //VOLTAGE BELOW 9V ------SLOW RICE
            {
               //Toggle_pin();
               //TORCHTESTIPIO=0;
               //TORCHTESTIOLAT=1;
               piditeration=1;
               pidkp=pidParams1.Kp1;//-(para.migmode.setwspeed/10.0);//   =40.0;//150;//100;//10; //25;//10; modified on 21.04.2017 promoda
               pidki=pidParams1.Ki1;//   =5.0;//2;//10;//2;//10
               pidkd=pidParams1.Kd1;//   =10.0;//20;//0;//20 //5
            }
            else            //VOLTAGE IS ABOVE 15V----FAST FALL            
            {
               Toggle_pin();
               //TORCHTESTIPIO=0;
               //TORCHTESTIOLAT=0;
               piditeration=1;
               pidkp=pidParams2.Kp2;//+(para.migmode.setwspeed/4.0);//   =40.0;//150;//100;//10; //25;//10; modified on 21.04.2017 promoda
               pidki=pidParams2.Ki2;//   =5.0;//2;//10;//2;//10
               pidkd=pidParams2.Kd2;//   =10.0;//20;//0;//20 //5
            }*/
         }
         /*if(ext2ans==1)
         {
            Aweldon_detectf=(extint2status1   ==   1    ? 0:1);//1:0);//;'T':'X');
         }*/
         pincheck=0;
      }
   } 

   if(weldmode=='P' && pulsestrtf==0)// && cvrefon==0)
   {
      if(cvrefon==0)
      {
         MAHESH      =0;//310+(300*7.22);//pdaccount;
         if(SPI2STATbits.SPITBF==0)
         {
            DACCSLAT=0;
            SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
         }
      }
      else
      {
         ARCONLAT      =ON;                  //ARCON CONTROL SIGNAL INPUT TO PWM CARD
         CCCVCTRLLAT   =CVMODE;               //CCCV CONTROL  INPUT TO PWM CARD.
         MAHESH         =(190.0*CVSLOPE)-CVOFFSET;
         if(SPI2STATbits.SPITBF==0)
         {
            DACCSLAT=0;
            SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
         }
      }
      //openloop=0;
   }
   else if( (pulsecyclestrt==1 && weldmode=='P' && Aweldon_detectf==0 && pulsestrtf==1) ||(weld_p_para_latch==1) )
     {
     weld_p_para_latch=0;  
       //Toggle_pin(); 
      //psstatus.creepspeedon   =1;
      //openloop=0;          // for starting purpose
      //cc mode
      //SHDNLAT        =0;         //OCV ON
      ARCONLAT      =OFF;                  //ARCON CONTROL SIGNAL INPUT TO PWM CARD
      CCCVCTRLLAT   =CCMODE;               //CCCV CONTROL  INPUT TO PWM CARD.
      
      //ARCONLAT      =OFF;                  //ARCON CONTROL SIGNAL INPUT TO PWM CARD
      //CCCVCTRLLAT   =CCMODE;               //CCCV CONTROL  INPUT TO PWM CARD.
      MAHESH        =const_arc_strike_pdaccount;//pdaccount;//sdaccount;
      DACCSLAT=0;
      SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
      
      if(firstpulsef==0)
      {   
         pulsetm      =OPEN_pulsetm;
         steptm      =OPEN_steptm;
         basetm      =OPEN_basetm;//1000/5;//OPEN_basetm;
         pulserisetm   =OPEN_pulserisetm;
         pulsefalltm   =OPEN_pulsefalltm;
         startpulsetm=OPEN_startpulsetm;
         uppdaccount   =OPEN_uppdaccount;
         pdaccount   =OPEN_pdaccount;
         sdaccount   =OPEN_sdaccount;
         bdaccount   =OPEN_bdaccount;
         newupstep   =OPEN_newupstep;
         newdownstep   =OPEN_newdownstep;
         firstpulsef =1;
      }   
   
      pulsecycle   =startpulseop;//baseonop;//startpulseop;//baseonop;
       cout_100us=0; //++;
      microsec=1;
      startbmeasuref=0;
      endbmeasuref=0;
      BCNT=0;
   }
  
   else if(pulsecyclestrt==1 && weldmode=='P' && Aweldon_detectf==1 && pulsestrtf==1)
   {   
      {
         ARCONLAT            =OFF;                  //ARCON CONTROL SIGNAL INPUT TO PWM CARD
         CCCVCTRLLAT            =CCMODE;               //CCCV CONTROL  INPUT TO PWM CARD.
         psstatus.creepspeedon   =0   ;                  //transoff.creepspeedon=0;
         if(changestatusf==0)
         {
            changestatusf=1;
            emg_sendf=1;
            pulseweldonf=1;
            twinpulsecnt=0;
         }
         dummypulsecycle=pulsecycle;
         cout_100us++;
         switch(dummypulsecycle)
         {
            case pulseriseop:
            {   
               if(microsec <= pulserisetm)
               {
                  pulseoncnt=0;//mahesh ++;
                  pulserefonf=0;//mahesh 1;
                  baserefonf=0;
                  microsec++;
                  upcnt   =bdaccount + (newupstep*microsec);   //+bdacount;      //(baseamp+(upstep*microsec));
                  MAHESH   =upcnt;                         //310.0+(upcnt*7.22);
                  addafref   =0;
               }
               else
               {
                  cout_100us   =0;
                  microsec   =1;
                  pulsecycle   =startpulseop;//pulseonop;
                  MAHESH      =uppdaccount;
                  
               }
               //if(SPI2STATbits.SPITBF==0)
               //{
               //   DACCSLAT=0;
               //   SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
               //}
                  ripplecnt=0;
                  firstpulsef=1;
               break;
            }
            case startpulseop:
            {
               if(microsec <=startpulsetm)
               {
                  pulseoncnt=0;//mahesh++;
                  pulserefonf=0;//mahesh1;
                  baserefonf=0;
                  MAHESH   =uppdaccount;
                  microsec++;
               }
               else
               {
                  cout_100us   =0;
                  microsec   =1;
                  pulsecycle   =pulseonop;//pdaccount;//steponop;//pulsedecayop;
                  MAHESH      =pdaccount;//sdaccount;
                  msrpulsevtgf=1;
               }
               //if(SPI2STATbits.SPITBF==0)
                 //{
               //   DACCSLAT=0;
                 //   SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
                 //}
               break;
            }
            case pulseonop:
            {   
               if(microsec <= pulsetm)
               {
                  pulseoncnt++;
                  pulserefonf=1;
                  baserefonf=0;
                  MAHESH   =pdaccount;
                  pulsecycle=pulseonop;
                  microsec++;
               
                  if(mbase1f==1 && stopbasef==0)
                  {
                     mbase1f=0;   //ador 
                     mbase2f=1;  //ador
                     stopbasef=1;
                  }   
               }
               else
               {
                  cout_100us   =0;
                  microsec   =1;
                  pulsecycle   =pulsedecayop;//steponop;//pulsedecayop;
                  MAHESH      =pdaccount;//sdaccount;
                  peakonf=0;
                  
                  mbase1f=0;   //ador 
                  mbase2f=0;  //ador
                  stopbasef=0;//ador
                  msrpulsevtgf=0;
                  avgmpulsevtg=mpulsevtg;                 
               }
               //if(SPI2STATbits.SPITBF==0)
                 //{
               //   DACCSLAT=0;
                 //   SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
                 //}
               break;   
            }
      
              case pulsedecayop:
            {   
               if(microsec < 51)//21 pulsefalltm)
               {   
                  //pulseoncnt++;
                  pulserefonf=0;//mahesh1;
                  baserefonf=0;
                  idecaycount =sdaccount+Decay_lookup2[microsec-1];  //LOOKUP1 USED sdaccount+
                  //idecaycount =sdaccount+sinefall_lookup[microsec-1];  //sdaccount+
                  if(idecaycount>pdaccount)
                  idecaycount=pdaccount;
                  MAHESH      =idecaycount;         
                  microsec++;
               }         
               else
               {
                  cout_100us   =0;
                  microsec   =1;
                  pulsecycle   =steponop;
                  MAHESH      =sdaccount;
                  startbmeasuref=1;
                  endbmeasuref=0;
                  //addafref=0;//1; mahesh 24.11.2017
                  //if(shiftbvtgf==1)
                  //{
                  //   mbase1f=1;
                  //   mbase2f=0;
                  //   BCNT=0;
                  //}   
                  if(shiftbvtgf==1)
                  {
                     addafref=1;
                  }
                  else
                  {
                     addafref=0;
                  }   
               }
                 //if(SPI2STATbits.SPITBF==0)
                 //{
               //   DACCSLAT=0;
               //   SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
                 //}
               break;
            }
         
            case steponop:
            {   
               //pulseoncnt++;
               pulserefonf=0;
               baserefonf=1;
               
               if(microsec <= steptm)
               {
                  MAHESH      =sdaccount;                  //1/(1+ax)
                  microsec++;
               }
               else
               {
                  cout_100us   =0;
                  microsec   =1;
                  if(shiftbvtgf==1)//if(basetm <=1)
                  {
                     pulsecycle   =pulseriseop;
                     MAHESH      =sdaccount;
				
                     mbase1f      =0;
                     mbase2f      =1;
                     startbmeasuref=0;
                     endbmeasuref=1;
                     
                     pulserefonf=0;
                     baserefonf=0;   
                     //msrpulseoncnt=(pulserisetm+ startpulsetm+pulsetm+20); //decay ==20 pulseoncnt;
                     //msrbaseoncnt=(steptm+basetm);//baseoncnt;
                     msrpulsevtg=sumpulsevoltage/pulsevoltagecnt;
                     msrbasevtg=sumbasevoltage/basevoltagecnt;
                     sumpulsevoltage=0;
                     pulsevoltagecnt=0;
                     sumbasevoltage=0;
                     basevoltagecnt=0;
                     pulseoncnt=0;
                     baseoncnt=0;

                  }
                  else
                  {
                     pulsecycle   =baseonop;//stepdecayop;
                     MAHESH      = bdaccount;
                     addafref=1;               //mahesh 16.11.2017
                     if(shiftbvtgf==0)
                     {
                        mbase1f=1;
                        mbase2f=0;
                        BCNT=0;
                     }
                  }
               }
            
                 //if(SPI2STATbits.SPITBF==0)
                 //{
               //   DACCSLAT=0;
               //   SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
                 //}
               break;
            }
         case baseonop:
         {   
            //pulseoncnt++;
            pulserefonf=0;
            baserefonf=1;
            if(microsec <= basetm)
            {
               MAHESH   =bdaccount;//bdaccount_rp;//bdaccount;//
                  microsec++;
               pulsecycle   =baseonop;
            }
            else
            {
                cout_100us   =0;
               microsec   =1;
               pulsecycle   =pulseriseop;
               ripplecnt   =0;
               MAHESH      =bdaccount;
               if(firstpulsef==1)
               {
                  startbmeasuref=0;
                  endbmeasuref=1;
                  mbase1f=0;
                  mbase2f=1;
                  
                  pulserefonf=0;
                  baserefonf=0;   
                  //msrpulseoncnt=(pulserisetm+ startpulsetm+pulsetm+20); //decay ==20 pulseoncnt;
                  //msrbaseoncnt=(steptm+basetm);//baseoncnt;
                  msrpulsevtg=sumpulsevoltage/pulsevoltagecnt;
                  msrbasevtg=sumbasevoltage/basevoltagecnt;
                  sumpulsevoltage=0;
                  pulsevoltagecnt=0;
                  sumbasevoltage=0;
                  basevoltagecnt=0;
                  pulseoncnt=0;
                  baseoncnt=0;
               }   
            }
            //if(SPI2STATbits.SPITBF==0)
              //{
            //   DACCSLAT=0;
            //   SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
              //}
            break;
         }
      }
      DACCSLAT=0;
        if(SPI2STATbits.SPITBF==0)
        {
         if(addafref==1)
         {
            sumdaccount=MAHESH+sckdaccount;		
            /*
			if(sumdaccount >= ((para.pmigmode.setwspeed * save_location) + 30)) //
			{
				sumdaccount = (para.pmigmode.setwspeed * save_location) + 30;
			} 			           
			*/
            presumdaccount=sumdaccount;				
         }
         else
         {
            sumdaccount=MAHESH;
            if(sumdaccount<=presumdaccount)
            sumdaccount=presumdaccount;
            else
            sumdaccount=sumdaccount;
         }
         
         //sumdaccount=MAHESH;            //for testing purpose only	
         if(sumdaccount>=4060)//3683)//pdaccount)//3351)            //500*6.702+0.4
         sumdaccount=4060;//3683;//pdaccount;//3351;
         SPI2BUF=28672+(sumdaccount-20);//MAHESH+sckdaccount;//DACREF;//1300;//102A 600
        }   
   }
   }
}

void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)  //FOR ENCODER SCANNING
{
  IFS1bits.T4IF=0;  
  //count4_1ms++;
   /*DACCSLAT=0;
  if(SPI2STATbits.SPITBF==0)
  {
      SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
  }*/
  //if(count4_1ms>=100)
  {
   count4_1ms=0;
   if(scan_count==0) 
   {
      encod1=SCANENCODER1();
      scan_count++;
   }
   else if(scan_count==1) 
   {
      encod2=SCANENCODER2();
      scan_count++;
   }
   else if(scan_count==2) 
   {
      encod3=SCANENCODER3();
      scan_count=0;
   }
  }   
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)// for Each channel adc conversion=5usec; for 3=15usec
{
   ADCAresult=ADCBUF0;
   ADCVresult=ADCBUF1;
   ADCEresult=ADCBUF2;
   IFS0bits.ADIF = 0; 

   if(weldmode=='G')
   {
      AFcnt++;
      Total_AFVresult+=ADCVresult;
		Total_AvgCurr += ADCAresult;
      /*
      if(cSoftStartUSecfg == 0)
      {
	      iStartSetVoltCnt++;
	  }
	  */
	   
      if(AFcnt>=4)               //15usec*8=120usec
      {
         AFvtg=Total_AFVresult>>2;
	   	 iACT_CURRENT =  Total_AvgCurr >> 2;			//3		changed on  23022020	   
	   	 Total_AvgCurr = 0; 
         Total_AFVresult=0;         
         AFcnt=0;
         adcreadf=1;
      }                
		if((iACT_CURRENT > 740)&&(MIGweldon_detectf == 0)&&(cTorchPressFoundfg == 1) )
		{			
			MIGweldon_detectf = 1;
//			cSoftStartUSecfg = 1;
			cStartPulsefg = 1;
			cSoftStrfg = 1;				
//			cStartCCReffg = 0;
			cPulseCnt =  STARTPULSECNT;	
			cTorchPressFoundfg = 0;	
			
			if(cSoftwireDetfg == 0)//iProgramLoadLoc != 212)
			{
				iStartCurr = STARTPULSECURRENT;
			}
			else
			{	
				iStartCurr = STARTPULSECURRENT/2;
			}
			
			genpwmcvref(cvoffsetref,voltageref);			 																					
			iDummyvoltageref = para.migmode.setvoltage + (para.migmode.setvoltage / 2);// Recall_location * 10;
			iSoftStrTimecnt = 80;//save_location *10;
			cSoftStrTimefg = 1;
			iStepforStartVoltRef = (iDummyvoltageref - para.migmode.setvoltage)/3;			
			iStartSetVoltCnt = 0;			
		}
		else if((iACT_CURRENT > 150)&&(MIGweldon_detectf == 1) && (psstatus.creepspeedon == 1))
		{
			cSoftStrfg = 1;
   			
		}	        
      
       
      
   }
   if((addafref==1) && (weldmode=='P')) //startbmeasuref==1)
   {
      AFcnt++;
      Total_AFVresult+=ADCVresult;
      if(AFcnt>=4)//8)               //15usec*8=120usec
      {
         AFvtg=Total_AFVresult>>2;//3;
         Total_AFVresult=0;
         AFcnt=0;
         adcreadf=1;
      }
   }
   SCKTcnt++;
   
 
   Total_SCKAresult+=ADCAresult;
   Total_SCKVresult+=ADCVresult;
   Total_SCKEresult+=ADCEresult;
   if(SCKTcnt>=SCKTloopcnt)      //for avg of 16 sample 16*15usec=240usec required
   {
      SCKamp=Total_SCKAresult>>4;
      SCKvtg=Total_SCKVresult>>4;
      SCKerr=Total_SCKEresult>>4;
      SCKTcnt         =0;
      Total_SCKAresult=0;
      Total_SCKVresult=0;
      Total_SCKEresult=0;
      SCKavgf=1;
      trip_adc_complet_flag=1;
      adcreadoverf=1;
      //Toggle_pin();
      OC3RS=SCKvtg>>1;
      ;
//########################## ############################################################
      if(msrpulsevtgf==1) //@measure pulsevtg
      {
         mpulsevtg=SCKvtg>>2;
         cFreqErrorupdatefg = 1;
         //sum_mpulsevtg=sum_mpulsevtg+mpulsevtg;
         //mpulsevtgcnt++;
         //mpulsevtgarr[mpulsevtgcnt]=mpulsevtg;
         //mpulsevtgcnt++;
         //if(mpulsevtgcnt>3) //15)
         //mpulsevtgcnt=0;
      }

//   if(SCKamp>=100)//100=15amp //3700=500
   {
      if(pulserefonf==1 && baserefonf==0)
      {
         msrbpvtg=SCKvtg>>2;
         sumpulsevoltage=sumpulsevoltage+msrbpvtg;
         pulsevoltagecnt++;
         
      
      }
      else if(pulserefonf==0 && baserefonf==1)
      {
          msrbpvtg=SCKvtg>>2;
          sumbasevoltage=sumbasevoltage+msrbpvtg;
          basevoltagecnt++;   
      }   
   }
//#######################################################################################      
      PULSEONOFFcnt++;
      Total_PULSEONOFFAresult+=SCKamp;
      Total_PULSEONOFFVresult+=SCKvtg;
      if(PULSEONOFFcnt>=PULSEONOFFloopcnt) //for average of 240*4=960usec==1msec time
      {
         PULSEamp=Total_PULSEONOFFAresult>>2;  
         PULSEvtg=Total_PULSEONOFFVresult>>2;
         Total_PULSEONOFFAresult=0;
         Total_PULSEONOFFVresult=0;
         PULSEONOFFcnt=0;
         PULSEavgf=1;
      }
      ;
      DISPcnt++;
      Total_DISPAresult+=SCKamp;
      Total_DISPVresult+=SCKvtg;
      Total_DISPEresult+=SCKerr;
      //Toggle_pin();   
      if(DISPcnt>=DISPloopcnt)
      {
         DISPamp=Total_DISPAresult>>12;
         DISPvtg=Total_DISPVresult>>12;
         DISPerr=Total_DISPEresult>>12;
         Total_DISPAresult=0;
         Total_DISPVresult=0;
         Total_DISPEresult=0;
         //CURRENT   =DISPamp*0.135; //5.0)   (adccur*5.0)/37.0;
         //VOLTAGE   =DISPvtg>>2;   //   (adcvtg*10.0)/40.0;//37.0
         //TRIPVTG   =DISPerr*0.270; //   (adctripvtg*10.0)/37.0;   
         DISPcnt=0;
         DISPavgf=1;
      }   
      
   }   
}


void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void)
{
   IFS1bits.SPI2IF=0;
   DACCSLAT=1;
   if(SPI2STATbits.SPIROV==1)
   SPI2STATbits.SPIROV=0;
}
//================================================================================================
//void __attribute__((interrupt, no_auto_psv)) _IC1Interrupt(void)
//{
//    static unsigned long summperiod=0;
//   static unsigned int mperiodcnt=0, avgmperiod=0;
//   IFS0bits.IC1IF = 0;
//    //CloseCapture3(); 
//    //IC3CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
//    ReadCapture1(&timer_first_edge);
//    ReadCapture1(&timer_second_edge);
//    mperiod = timer_second_edge -  timer_first_edge;
//      
//   summperiod=summperiod + mperiod;
//   mperiodcnt++;
//   if(mperiodcnt>=16)
//   {
//      avgmperiod=summperiod>>4;
//      mperiodcnt=0;
//      summperiod=0;
//      if(Prev_mperiod != mperiod)
//      {
//         mfreq=(1000000.0/(mperiod*2.16));// 1cap
//         Prev_mperiod = mperiod;
//         //second_order_pid();
//         //TRANS1('@');
//          //TRANSNUM(mfreq);
//           //transmit_dec(mfreq);
//           //trans(0x0D);
//            //trans(0x0A);
//      }
//      //second_order_pid();
//   }
//   if(pweldonf==1 && softstartf==0)
//   {
//      //OC2RS=para.migmode.setwspeed*10.0;         //100%=64V=2949  60%=38V=1769 
//      softstartcnt++;
//      if(softstartcnt >=5)
//      {
//         softstartf=1;// open loop;
//         //TRANS1('S');
//      }
//   }
//}
//
void __attribute__((interrupt, no_auto_psv))_U1RXInterrupt(void)
{
	IFS0bits.U1RXIF = 0; // clear rX interrupt flag
	uartdata1       = U1RXREG; //
	
	
	if(cReadWholeFilefg == 1)
	{
		cReadWholeFile[iabc] = uartdata1;
		iabc++;
	}		
/*	if(cSerialPortTask == 'H')// cSerialPortTask == HMI 
	{
		if((cFrameStrfg == 0))
	   	{
		   	cByte_cntr = 0;
		   	cReceive_buffer[cByte_cntr] = uartdata1;
		   	cFrameStrfg = 1;
		   	cChardlyStrfg = 1;
		   	cCharDelay = CHARDELAY3BY5;
		} 
		else if((cFrameStrfg == 1))
		{
		   	cByte_cntr++;
		   	cReceive_buffer[cByte_cntr] = uartdata1;
		   	cCharDelay = CHARDELAY3BY5;	
		   	cFrameStrfg = 1;   	
		   			
		}		
	}
	else
	{
	}*/			
}

void __attribute__((interrupt, no_auto_psv))_U2TXInterrupt(void)
{
   IFS1bits.U2TXIF = 0; // clear rX interrupt flag
   if(starttx2==1)
   {
      if(tx2counter<=TX_DATA_LENGTH) //21)
      {
         U2TXREG=trans_ps_wf_arr[tx2counter];//pstowfstru.pstransarr[tx2counter];
         tx2counter++;
      }
      else if(tx2counter==(TX_DATA_LENGTH+1))//22)
      {
         U2TXREG=trans_ps_wf_arr[(TX_DATA_LENGTH+1)];//tx2chksum;
         tx2counter++;
         cEditfg = 0;
      }
      else
      {
         starttx2=0;
         tx2counter=0;
         tx2chksum=0;   
      }
   }
   else if(startstatustx2==1)
   {
      //TRANS2('#');
      //TRANS2(transoff.psstatusbyte);
      //TRANS2(transoff.psstatusbyte); //?
      
      pstowfstr.psstatusbyte=psstatusu.psstatusbyte[0];
      if(tx2statuscounter==0)
      {
         U2TXREG=pstowfstr.psstatusbyte;//transoffu.transarr[tx2counter];
         tx2statuscounter++;
      }
      else if(tx2statuscounter==1)
      {
         U2TXREG=pstowfstr.psstatusbyte;//transoffu.transarr[tx2counter];
         tx2statuscounter=0;
         startstatustx2=0;
      }
   }   
}

void __attribute__((interrupt, no_auto_psv))_U2RXInterrupt(void)
{
   IFS1bits.U2RXIF = 0; // clear rX interrupt flag
   uartdata2      = U2RXREG; //
   if(uartdata2=='@' && startptr1==0 && startstatus1==0 )//&& transonf==0)
   {    
      startptr1=1;
      startstatus1=0;
      recchksum=0;
   }
   else if(uartdata2=='#' && startptr1==0 && startstatus1==0)// && transonf==0)
   {    
      startstatus1=1;
      startptr1=0;
      arrptr=0;
      recchksum=0;
   }
   else if(startptr1==0 && startstatus1==1 )//&& transonf==0)
   {
      if(recstatus==0)
      {
         recwfstatus=uartdata2;
         recstatus=1;
      }
      else if(recstatus==1)
      {
         if(uartdata2==recwfstatus) //?
         {
            comm_errorf=0; 
			communication_time_out=0;
                      
            wfstatusu.wfstatusbyte[0]=recwfstatus;
                     
            startstatus1=0;
            startptr1=0;
            recstatus=0;
            arrptr=0;
            
            if(wfstatus.torchonstatus==1)
            {
               torchonstatus='T';
            }
            else
            {
               torchonstatus='X';
            } 
            
            /*   
            transoff.psstatusbyte=psstatusu.psstatusbyte[0];
            if(starttx2==0)
            {
               startstatustx2=1;
               tx2statuscounter=0;
               U2TXREG='#';
            }*/
         }
         else           
         {
            startptr1=0;
            arrptr=0;
            recchksum=0;
            startstatus1=0;
            recstatus=0;
          }
      }
   }
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   
    else if(startptr1==1 && startstatus1==0 )//&& transonf==0)
    {    
      if(arrptr<=TX_DATA_LENGTH) //15//21)//Check 
        {    
         rec_arr[arrptr]=uartdata2;
         recchksum=recchksum+uartdata2;
         arrptr++;
        }
        else if ((uartdata2 == 'E')||(uartdata2 == 'X'))
        {
        	if(uartdata2 == 'E')
        	{
        		WfEditfg = 1;
        	}
        	else if(uartdata2 == 'X')
        	{
        		WfEditfg = 0;        	
        	}
        }
        else if(recchksum==uartdata2) // for testing 23112020
        {
            
            comm_errorf=0; 
			communication_time_out=0;
                       
            for(iii=1;iii<=TX_DATA_LENGTH;iii++) //20//TX_DATA_LENGTH
            {    
                pstowfstru.pstransarr[iii]=rec_arr[iii]; 
            }
         //pstowfstru.pstransarr[12]=rec_arr[12];      //weldmode status
         //transoffu.transarr[20]=rec_arr[20];          //PSstatus byte
         //pstowfstru.pstransarr[13]=rec_arr[13];      //WFstatus byte
            if(pstowfstru.pstransarr[16] ==  (0x10))
            {
				HS_errorf = 1;	            
	        } 
		//iTest1 = pstowfstru.pstransarr[16];
		//iTest1 = pstowfstru.pstransarr[17];	                 
         if(pstowfstr.weldmode=='G' && (password_protection_enabled==0) )
         {               //1
            //para.migmode.setwspeed=pstowfstr.Hi_setwspeed;
            //para.migmode.setwspeed<<=8;
            //para.migmode.setwspeed|=pstowfstr.Lo_setwspeed;            
            
            if((pstowfstr.setwspeed >= mini.migmode.setwspeed) && (pstowfstr.setwspeed <= iMaxWSLimit) && (WfEditfg == 1))
            {
            	para.migmode.setwspeed=pstowfstr.setwspeed;            

            	para.migmode.setvoltage=pstowfstr.Hi_setvoltage;
            	para.migmode.setvoltage<<=8;
            	para.migmode.setvoltage|=pstowfstr.Lo_setvoltage;            	
				iTest1 = para.migmode.setvoltage;
			//iTest1 = pstowfstru.pstransarr[17];
            }         
            para.migmode.inductance=pstowfstr.arclength; 
         }
         else if(pstowfstr.weldmode=='P' && (password_protection_enabled==0) )
         {               //1
            //para.pmigmode.setwspeed=transoff.Hi_setwspeed;
            //para.pmigmode.setwspeed<<=8;
            //para.pmigmode.setwspeed|=transoff.Lo_setwspeed;
            
            if((pstowfstr.setwspeed >= mini.pmigmode.setwspeed) && (pstowfstr.setwspeed <= iMaxWSLimit) && (WfEditfg == 1))
            {
	            para.pmigmode.setwspeed=pstowfstr.setwspeed;
	            para.pmigmode.arclength=pstowfstr.arclength;          // commented for testing on 29082019
            	
            }
	           	iRxwfVoltage=pstowfstr.Hi_setvoltage;
	            iRxwfVoltage<<=8;
	            iRxwfVoltage|=pstowfstr.Lo_setvoltage;
            
            if((para.pmigmode.setvoltage != iRxwfVoltage) &&(cWfVChangefg == 0) && (WfEditfg == 1))//&&(cVoltUpdateLatchCnt == 0))
            {
//	          cWfVChangefg = 1;   
//	          iTest2 = iRxwfVoltage;
//	          cTestfg = 1;	          
				Tbasevoltage = para.pmigmode.setvoltage = iRxwfVoltage;            	          
	        } 
         }
         //psstatusu.psstatusbyte[0]=transoff.psstatusbyte;                      //no need to read
         if(cEditfg == 0)
         {
         	wfstatusu.wfstatusbyte[0]=pstowfstr.wfstatusbyte;
         }	
         
		if(WfEditfg == 1)
		{
			if(wfstatus.twotfourtmode1==1)
			{
				Type.twot=0;
				Type.fourt=1;
			//	wfstatus.twotfourtmode1 = 0;
			//	Type.twot=1;
			//	Type.fourt=0;		
			//	Type.job = 1;
			}
			else
			{
				Type.twot=1;
				Type.fourt=0;
			}
		}	 
//         Type.time = 1;
//         Type.arcforce = 1;
         if(wfstatus.torchonstatus==1)
         {
            torchonstatus='T';
         }
         else
         {
            torchonstatus='X';
         } 
         startptr1=0;
         arrptr=0;
         recchksum=0;
      }    
      else
      {
         startptr1=0;
         arrptr=0;
         recchksum=0;
         startstatus1=0;
         recstatus=0;
      }
   }   
   else           
   {
      startptr1=0;
      arrptr=0;
      recchksum=0;
      startstatus1=0;
      recstatus=0;
   }
}   
/*void __attribute__((interrupt, no_auto_psv))_U2RXInterrupt(void)
{
   IFS1bits.U2RXIF = 0; // clear rX interrupt flag
   uartdata2      = U2RXREG; //
   //TRANS1(uartdata2);
   {
            if(uartdata2=='@' && startptr1==0 && startstatus1==0 )//&& transonf==0)
            {    
	         startptr1=1;
	         startstatus1=0;
	         recchksum=0;
	         //TRANS1('@');
          }
          else if(uartdata2=='#' && startptr1==0 && startstatus1==0)// && transonf==0)
            {    
         startstatus1=1;
         startptr1=0;
         arrptr=0;
         recchksum=0;
         //TRANS1('A');
         //TRANS1(uartdata2);
          }
            else if(startptr1==0 && startstatus1==1 )//&& transonf==0)
            {
            if(recstatus==0)
            {
               recwfstatus=uartdata2;
               recstatus=1;
            //   TRANS1('B');
            //   TRANS1(uartdata2);
         }
         else if(recstatus==1)
         {
            if(uartdata2==recwfstatus) //?
            {
               wfstatusu.wfstatusbyte[0]=recwfstatus;
               startstatus1=0;
               startptr1=0;
               recstatus=0;
               arrptr=0;
            //   TRANS1('C');
            //   TRANS1(uartdata2);
               if(wfstatus.torchonstatus==1)
                          {
                            torchonstatus='T';
            //      TORCHIPIO=0;
            //      TORCHIOLAT=1;
               //   TRANS1('D');
               //   TRANS1(wfstatusu.wfstatusbyte[0]);
                         }
                          else
                          {
                             torchonstatus='X';
            //      TORCHIPIO=0;
             //         TORCHIOLAT=0;
                         } 
               transoff.psstatusbyte=psstatusu.psstatusbyte[0];
               //TRANS2('#');
               //TRANS2(transoff.psstatusbyte);
               //TRANS2(transoff.psstatusbyte); //?
               //sendpsstatus();
            }
            else           
            {
                startptr1=0;
                arrptr=0;
                recchksum=0;
                startstatus1=0;
                recstatus=0;
            }
         }
       }
       else if(startptr1==1 && startstatus1==0 )//&& transonf==0)
            {    
                if(arrptr<=21)
                {    
            rec_arr[arrptr]=uartdata2;
            //TRANS1(uartdata2);
            recchksum=recchksum+uartdata2;
            arrptr++;
                }
                else if(recchksum==uartdata2)
                {
                     for(iii=2;iii<=14;iii++) //20
                    {    
                        transoffu.transarr[iii]=rec_arr[iii]; 
                    }
                       transoffu.transarr[19]=rec_arr[19];      //weldmode status
                      //transoffu.transarr[20]=rec_arr[20];      //PSstatus byte
                         transoffu.transarr[21]=rec_arr[21];      //WFstatus byte

            //TRANS1('A');
            //TRANS1(transoffu.transarr[21]);
            //TRANS1(transoff.wfstatusbyte);


                    if(transoff.weldmode=='G')
                    {               //1
               para.migmode.setwspeed=transoff.Hi_setwspeed;
               para.migmode.setwspeed<<=8;
               para.migmode.setwspeed|=transoff.Lo_setwspeed;
               
               para.migmode.setvoltage=transoff.Hi_setvoltage;
               para.migmode.setvoltage<<=8;
               para.migmode.setvoltage|=transoff.Lo_setvoltage;
            }
            else if(transoff.weldmode=='P')
                    {               //1
                    para.pmigmode.setwspeed=transoff.Hi_setwspeed;
                       para.pmigmode.setwspeed<<=8;
                         para.pmigmode.setwspeed|=transoff.Lo_setwspeed;

                       para.pmigmode.setvoltage=transoff.Hi_setvoltage;
                       para.pmigmode.setvoltage<<=8;
                       para.pmigmode.setvoltage|=transoff.Lo_setvoltage;

               //   para.pmigmode.arclength=transoff.arclength;         //DISABLED BY MAHESH
               //TRANS1('A');
               //TRANS1(transoff.arclength);
               //TRANS1(para.pmigmode.arclength);
            }
             //psstatusu.psstatusbyte[0]=transoff.psstatusbyte;                      //no need to read
                     wfstatusu.wfstatusbyte[0]=transoff.wfstatusbyte;
             //TRANS1('@');
             //TRANS1(transoff.wfstatusbyte);

                    //TRANS1('A');
                    //TRANS1(transoff.statusbyte);
                    //TRANS1(statusu.statusbyte[0]);
                    if(wfstatus.torchonstatus==1)
                    {
                      torchonstatus='T';
                      //TRANS1('T'); 
                    }
                    else
                    {
                       torchonstatus='X';
                       //TRANS1('X');
                   } 
                    startptr1=0;
                    arrptr=0;
                    recchksum=0;
                    //transmitonf=1;
                }    
                else
                {
                    startptr1=0;
                    arrptr=0;
                    recchksum=0;
            		startstatus1=0;
            		recstatus=0;
                }
            }   
      else           
      {
          startptr1=0;
          arrptr=0;
          recchksum=0;
          startstatus1=0;
          recstatus=0;
    
      }

     }

}*/






void Toggle_pin11()
{
   if(togglepin==0)
   {
      TORCHTEST1IPIO=0;
      TORCHTEST1IOLAT=1;
      togglepin=1;
      
      //EXTINT1IO    =0;   
       //EXTINT1LAT   =1;
      
   }
   else if(togglepin==1)
   {
      TORCHTEST1IPIO=0;
      TORCHTEST1IOLAT=0;
      togglepin=0;
      
      //EXTINT1IO    =0;   
       //EXTINT1LAT   =0;
      
   }
}
   
/*   MCOKIO=0;
   if(togglepin==1)
   {
      MCOKLAT=0;
      togglepin=0;
   }
   else
   {
      MCOKLAT=1;
      togglepin=1;
   }
}*/   

void Reload_pulse_para()
{
   if(openloopf==0)
   {
      pulsetm      =PID_pulsetm;
      steptm      =PID_steptm;
      basetm      =PID_basetm;
      pulserisetm   =PID_pulserisetm;
      pulsefalltm   =PID_pulsefalltm;
      startpulsetm=PID_startpulsetm;
      uppdaccount   =PID_uppdaccount;
      pdaccount   =PID_pdaccount;
      sdaccount   =PID_sdaccount;
      bdaccount   =PID_bdaccount;
      newupstep   =PID_newupstep;
      newdownstep   =PID_newdownstep;
      //refbasetm=PID_refbasetm;
   }
   else
   {
      pulsetm      =OPEN_pulsetm;
      steptm      =OPEN_steptm;
      basetm      =OPEN_basetm;
      pulserisetm   =OPEN_pulserisetm;
      pulsefalltm   =OPEN_pulsefalltm;
      startpulsetm=OPEN_startpulsetm;
      uppdaccount   =OPEN_uppdaccount;
      pdaccount   =OPEN_pdaccount;
      sdaccount   =OPEN_sdaccount;
      bdaccount   =OPEN_bdaccount;
      newupstep   =OPEN_newupstep;
      newdownstep   =OPEN_newdownstep;
      //refbasetm=OPEN_refbasetm;
   }   
}   
   
