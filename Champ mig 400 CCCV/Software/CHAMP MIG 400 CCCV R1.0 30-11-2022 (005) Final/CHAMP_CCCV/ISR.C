void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void)
{
   IFS1bits.INT1IF =0;
}

void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt(void)
{
	IFS1bits.INT2IF =0;
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
   IFS0bits.T1IF=0;                            //1 MSEC
   
 //----------------Crater WS/Voltage update--------------------
 
 iCraterdisptime++;  
//-------------------MOTOR TRIP--------------------------------------------------
  iMotorTripcnt_100ms++;
  
  if((weldmode=='G') && ((weldcyclestrt == 1) || (cInchLatchfg == 1)))
  {
  	if(iMotorTripcnt_100ms >= 100)
  	{
		if(MTR_TRIP == 1)
	  	{
			Motor_OverLoad_errorf = 0;
			iMotorTripChkcntr = 0;
	  	}
	  	else if(MTR_TRIP == 0)
	  	{
		  	iMotorTripChkcntr++;
		  	if(iMotorTripChkcntr >= MOTOR_OVERLOAD_ERROR_DETECTION_TIME)	//mig_Kc)
		  	{
			  	iMotorTripChkcntr = 0;
			  	Motor_OverLoad_errorf = 1;
			}			  
      	}
      	iMotorTripcnt_100ms = 0;
  	}
  }	      

//----------------------------------------------------------------------------
   if(cStartPulsefg == 1)
   {			
		if(cPulseCnt == 0)
		{
			cPulseCnt = 0;
			cStartPulsefg = 0;
			migdaccount = 0;			
			MIGweldon_detectf = 1;
			//MPWM = 0;		
		}
		else
		{
			cPulseCnt--;		
		}
   }
	
   if(cSoftStrfg == 1)
   {
		cSoftStrCnt++;
		cSoftStrfg = 0;
   }	
//----------------------------------------------------------------------------   
   if(cPWMLockfg == 1)
   {
	   iPWMClosecnt--;	 
	   if(iPWMClosecnt == 0)
	   {
		  cPWMLockfg = 0; 
	   } 
   }
	    		
//-------------------MOTOR FEEDBACK & PID LOOP---------------------------------
	iMotorPIDcnt++;
	if(iMotorPIDcnt >= 10)		//4
	{
		if((weldcyclestrt == 1) && (cMotorStopfg == 0) && (cratersetup == 0) && (cCreepSpeedDowncntfg == 0))
		{		
			motor_control_pid();
		}		
		iMotorPIDcnt = 0;		
	}	  
//-----------------------------------------------------------------------------
	if(cCreepSpeedDowncntfg == 1)
	{						
		iCreepSpeedDowncnt--;
		if(iCreepSpeedDowncnt<=0)
		{			
			cCreepEndfg=1;
			cCreepSpeedDowncntfg=0;
			cCreepLatchfg=0;
			if((cCreepEndfg == 1) && (cCreepKifg == 1))
			{
				cCreepKifg = 0;
				cCreepEndfg=0;	
				Generate_Reference(iWireSpeed);		
			}			
		}		
	}
//-------------------HOTSTART & ARCFORCE & ANTISTICK---------------------------
	//iArcForceTimeCnt++;
	
	iArcforcecnt++;
	if(iArcforcecnt >= 10)
	{
		cArcforcefg=1;
	    iArcforcecnt = 0;
	}	   	
	count_20ms++; 
//-------------------------------------------------------------------------------
	if((cHotfg == 1) && (weldonf == 1) && (weldmode == 'M')) 
	{
		iHotstartcount++;
		if(iHotstartcount >= HOT_START_TIME)	  
		{
			cEnDCurrUpdatefg = 1;  
			iHotstartcount = 0;
			cHotfg = 0;
		}	
	}    
//-------------------------------------------------------------------------------
 //if(cVRDMenufg != 1)
 //{
	if((VOLTAGE <= ANTISTICK_VTG_LIMIT) && (weldonf == 1) && (weldmode=='M'))
	{
		cnt200ms++;            
		if(cnt200ms >= 500)
		{
			daccount = MMACCLookup(ANTISTICK_CURR); 
			cDacoutfg = 1;                
			cAntistickfg = 1;
			cnt200ms = 0;  
		}
	}
	else
	{                
		cnt200ms = 0; 
	}
	if((VOLTAGE > ANTISTICK_VTG_LIMIT) && (cAntistickfg == 1))
	{
		cnt1sec++;
		if(cnt1sec >= ANTISTICK_LEAVE_TIME)
		{
			cEnDCurrUpdatefg = 1;  
			cAntistickfg = 0;                
			cnt1sec = 0;
		}
	}
//}
//----------------------TIG-------------------------------------
/*
	if((VOLTAGE <= SHORT_CIRCUIT_VTG_LIMIT) && (weldonf == 1) && (weldmode == 'T'))
	{
		cnt200ms_tig++;            
		if(cnt200ms_tig >= 5)
		{
			daccount = TIGCCLookup(SHORT_CIRCUIT_CURR); 
			cDacoutfg = 1;                
			cShortCktfg = 1;
			cnt200ms_tig = 0;  
		}
	}
	else
	{                
		cnt200ms_tig = 0; 
	}
	if((VOLTAGE > SHORT_CIRCUIT_VTG_LIMIT) && (cShortCktfg == 1))
	{
		cnt1sec_tig++;
		if(cnt1sec_tig >= SHORT_CIRCUIT_LEAVE_TIME)
		{
			cEnDCurrUpdatefg = 1;  
			cShortCktfg = 0;                
			cnt1sec_tig = 0;
		}
	}
*/
//-----------------------------------------------------------
	iWeldoncnt++;
	if(0)//iWeldoncnt >= 1000)
	{
		iWeldoncnt = 0;
		//cWeldondetectfg = 1;
	}
//-----------------------------------------------------------
    if(cFlashCntr != 0)
    {
        cFlashCntr--;
    }
    else
    { 
      	cFlashCntr = 0;	      	
    }

	count_1ms++;    
	iSecCntr++;
	mili1_100++;

	count_1sec++;
 	if(iSecCntr >= 1000)
 	{
	 	cOneSecfg = 1;
		iSecCntr = 0;
		if(cPonCntr != 0)
		{
			cPonCntr--;
		}
		if(iHeaderdly != 0)
		{
			iHeaderdly--;
		}			
//-------------------------------------------------------------------------------------------------
//11/07/2019
//here we are updating the power on time 
	//power_ontime();
//-------------------------------------------------------------------------------------------------		
	}	
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
      if(count_tx2 < 20)//50) //10) //update data after 200msec
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
   
//----------------------
	if(iCntChk != 0)
	{
		iCntChk--;
	}	
//----------------------
   
   if(count_20ms>=20)
   {
      count_20ms=0;
	  //keyreadf=1;
      if((weldcyclestrt==0))// && (weldonf == 0))
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

	if(count_1sec >= 1000)
	{
		count_1sec = 0;
      	if(cGaSMenufg == 1)
      	{
	      	
	      	
          	if(igascntr > 0)
          	{
              	if(iGasChStopCnt==2)
		        {
			        igascntr 		  = 0;
					cMigVtgUpdatefg   = 1;
					cMIGWSUpdatefg 	  = 1;
					cGaSMenufg 		  = 0;
					GAS_RELAYLAT      = 0;
					TypeDP.DPGROUP[0] = 0x00;
					cGASMenuMode      = 0;
					dispupdatef       = 1;
					cGasAndWeldParalockfg = 0;
					iGasChStopCnt=0;
		        }
		        else
			    {	
              	    igascntr--;
              	    cGasAndWeldParalockfg = 0;
                }
                          	
                
          	}
			else
          	{
				igascntr 		  = 0;
				iGasChStopCnt     = 0;
				cMigVtgUpdatefg   = 1;
				cMIGWSUpdatefg 	  = 1;
				cGaSMenufg 		  = 0;
				GAS_RELAYLAT      = 0;
				TypeDP.DPGROUP[0] = 0x00;
				cGASMenuMode      = 0;
				dispupdatef       = 1;
				cGasAndWeldParalockfg = 0;
				//cMIGParaMenufg    = 0;
          	}
      	}
	}

if(power_on_flag==1)
{  
	count_200ms++;
	count_500ms++;
	count_500ms1++;	
	count_tx2_1ms++;
	err11_delay_counter++;
	communication_time_out++;	
	arcontime.msec++;         
	short_circuit_cnt_100ms++;
	samplecnt++;

//----------------------------------------------------------------
	if(count_200ms>=20)//200)
	{
		count_200ms=0;
		check_torch_action();
	}
//----------------------------------------------------------------
	if(cSoftStrTimefg == 1)
	{
		iStartSetVoltCnt++;
	}	
//----------------------------------------------------------------
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
			}
			if(arcontime.min>=60)
			{
				arcontime.min=0;
				arcontime.sec=0;
				arcontime.hr++;
			}
			if(arcontime.hr>=999)
			{
				arcontime.min=0;
				arcontime.sec=0;
				arcontime.hr=0;
			}		
		}
	}


	if(weldmode=='G')
	{
		MIG_TORCHIO = 1;
		if(MIG_TORCH ==1)
		{ 
			dValm_torch0=0;
			if(++dValm_torch1 > TORCH_DETECT_DB)
			{
				TORCH_SW='T';
				GAS_RELAYLAT = 1;				
				dValm_torch1=1; 
				cTestMotorStopfg = 1;
				if((Type.twot == 1) && (cCreepDetectafterPreflowfg == 1))
				{
					cCreepKifg=1;					
					IRCreepcurr = iWireSpeed*mig_creepspeedrate*0.01;
					iCreepSpeedDowncnt=mig_creepspeedtime*10;	//CREEP_SPEED_DOWN_CNT;
					Generate_Reference(IRCreepcurr);
					cCreepDetectafterPreflowfg=0;
					cCreepLatchfg=1;
				}	
				if((Type.fourt == 1) && (c4Tstatus == 0))
				{
					cMotorStopfg=1;	
					c4Tstatus = 1;
					//MPWM=1;				
				}
				else if((Type.fourt == 1) && (c4Tstatus == 2))
				{
					TORCH_SW='T';				
					dValm_torch1=1; 						
					c4Tstatus = 3;									
				}		
			}			
		}
		else
		{ 
			dValm_torch1=0;
	
			if(++dValm_torch0 > TORCH_DETECT_DB);
			{
				if((cTestMotorStopfg == 1) && (Type.twot == 1))
				{
					cTestMotorStopfg = 0;
					OC4RS=0;
					cMotorStopfg=1;
					TORCH_SW='X';						
				}	
				else if((cTestMotorStopfg == 1) && (Type.fourt == 1) && (c4Tstatus == 1) && (cMotorStopfg == 1))
				{	
					TORCH_SW='X';
					//MPWM=0;
					//cMotorStopfg = 0;
					if(TORCH_SW == 'X') 
					{												
						dValm_torch0=1; 
						c4Tstatus = 2;						
					}		
				}
				else if((cTestMotorStopfg == 1) && (Type.fourt == 1) && (c4Tstatus == 3))
				{
					cTestMotorStopfg=0;
//					OC4RS=0;	
					cMotorStopfg=1;					
					TORCH_SW='X';	
					dValm_torch0=1; 
					c4Tstatus = 0;
					error_4_check4t=0;
					error4_flag=0;
					ERROR_4_errorf=0;
					cntsecond_er4=0;
				}	
			}
		} 
	}
	
/*********************Gas Water Selection*********************************************/  
      
	if((GASWATERIP==1) && (PRESSERRIP==0) && (weldmode=='G'))
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


//--------------------------------------------------------------------------------	

	if((cBKeyLockfg==1) && (cVRDMenufg == 0))                    //SWITCH PRESSED //PPC
	{               
		iVRDMenucnt++;
	
		if(iVRDMenucnt >= 5000) 
		{            
			cGasChkMenufg = 0;                  
			cMIGParaMenufg = 0;    
			cVRDMenufg = 1;                        
		}                       
	} 
		
//--------------------------------------------------------------------------------
      if(weldmode == 'G')
      {                  
	      if((cBKeyLockfg==1) && (cGasChkMenufg == 0) && (cMIGParaMenufg == 0) && (cGasAndWeldParalockfg == 0)&& (cVoltageoffsetmenufg==0))                    //SWITCH PRESSED
	      {               
	          iGasChkMenuModecnt++;
	
	          if(iGasChkMenuModecnt >= 5) 
	          {     
		                
	              	cGasChkMenufg = 1;
	           	    iGasChStopCnt++;	                   
	              //cMIGParaMenufg = 1;                             
	          }                       
	      } 
	      else if((cBKeyLockfg==1) && (cGasChkMenufg == 1) && (cMIGParaMenufg == 0))
	      {
	          iGasChkMenuModecnt++;
	          
	          if(iGasChkMenuModecnt >= 8000) 		//5000
	          {       
		          //iGasChkMenuModecnt=0;
	             // cGasChkMenufg = 0;                  
	              cMIGParaMenufg = 1; 
	              iGasChStopCnt     = 0;
	                                         
	          }  	       
	      }
	      else if((cBKeyLockfg==1) && (cGasChkMenufg == 1) && (cMIGParaMenufg == 1) && (cVoltageoffsetfg==0))
	      {
	          iGasChkMenuModecnt++; 
	          
	          if(iGasChkMenuModecnt >= 10000) 		//5000 PPC for volage offset
	          {       
		          iGasChkMenuModecnt=0;
	              cGasChkMenufg = 0;                  
	              cMIGParaMenufg = 0;  
	              cVoltageoffsetmenufg=1; 
	              cVoltageoffsetfg = 1; 
	              iGasChStopCnt     = 0 ;                        
	          }  	       
	      }
	      else if((cBKeyLockfg == 0) && (cGasChkMenufg == 1)&& (cMIGParaMenufg == 0))// && (cVoltageoffsetfg==0))
	      {          
	          iMIGParaMenucnt++;
	          if(iMIGParaMenucnt >= 5)
	          {
	           	  cGaSMenufg=1;
	           	  igascntr=GAS_CHECK_CNT;
	              cGasChkMenufg = 0;
	              iMIGParaMenucnt = 0;
				  cGasAndWeldParalockfg = 1;	
	          }
	      }    
	      else if(0)//(cBKeyLockfg==0) && (cMIGMenufg == 1))
	      {          
	          iMIGParaMenucnt++;
	          if(iMIGParaMenucnt >= 5)
	          {                                                     
	              cMIGMenufg = 0;
	              cMIGParaMenufg=0;
	              iMIGParaMenucnt = 0;
	              iGasChkMenuModecnt=0;
	              iGasChStopCnt     = 0;
	          }
	      }
	}
//-----------------------------------------------------------------
	if((cEndPulsefg == 1)&&(cMotorStopForENDPulsefg == 0))
	{
		if(cEndPulseCnt == 0 )
		{
			cEndPulseCnt = 0;
			cEndPulsefg = 0;

			SHDNLAT			=0;//1;								
			
	    	if(SPI2STATbits.SPITBF==0)
			{
				DACCSLAT	=0;
				daccount    =0;
				SPI2BUF		=28672+daccount;     	
			}	
		}
		else
		{
			cEndPulseCnt--;
		}		
	}
 	
	if(cMotorStopForENDPulsefg == 1)			
	{
		if(iWaitToStopMtrCnt == 0)
		{
			cMotorStopForENDPulsefg = 0;
			cEndPulsefg = 1;	
			cEndPulseCnt = ENPULSECNT;
			iEndPulseCurr = ENPULSECURR;
		}	
		else
		{
			iWaitToStopMtrCnt--;
		}	
	}	
	
	if((cEndPulsefg == 1)||(cStartPulsefg == 1)||(cMotorStopForENDPulsefg == 1))
	{
		//Generate_DAC_Reference(VRvtg);	 	
	}					
//-------------------------------------------------- 	 
   
   if(count_500ms>=5)// PID_interval)   //5) //100) //50  10 ms interval //para.pmigmode.setwspeed
   {
      count_500ms=0;
   }    
   /*
   if(strttmr==1)         //during only preflow and postflow, burnback time only
      {
         timerval++;
         if(timerval >= 100)
         {
	         cntsecond++;
	         timerval=0;
	         time_100ms++;
	         Time_ms++;
         }
      }
    */
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
	timerval_1ms++;
	if(timerval_1ms>=10)
	{
		timerval_1ms=0;
		if(upslopef==1)
		{
			msec10_cntr++;
			if(Upslope_cntr >= msec10_cntr)             //upsolpe
			{
				Upcurrent=Upcurrent+UP_Step;
				pwmresult=(unsigned int)Upcurrent;                
			}
			else
			{
				upslopef=0;                
			}
		}
	
		if(downslopef==1)
		{
			msec10_cntr++;
			if(Downslope_cntr >= msec10_cntr)           //downslope
			{
				if(Downcurrent>=Down_Step)
				{
					Downcurrent=Downcurrent-Down_Step;
					pwmresult=(unsigned int)Downcurrent;
				}
				else
				{
					pwmresult=0;
				}                
			}
			else
			{
				downslopef=0;                
				pwmresult=0;               
			}
		}
	}        
  }	//power on flag
} 
/************************************************************************************************************************/
/*
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)  //50usec
{
   IFS0bits.T2IF=0; 
   PR2=1949; 
}
*/
void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)  //interrupt at 100usec
{
	IFS0bits.T3IF=0;
	PR3=1470;
} 

void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void)  //interrupt at 50usec
{
   IFS1bits.T5IF=0;
   PR5      =1470;

}

void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)  
{
  	IFS1bits.T4IF=0; 
	PR4=1470;		
    if(weldmode=='G')
	{
		AFcnt++;
		Total_AFVresult+=ADCBUF1;// + (mig_Kc*10); 	//7
		Total_AvgCurr+=ADCBUF0;
			
		if(AFcnt>=2)               
		{
			AFvtg=Total_AFVresult >> 1 ;
			iACT_CURRENT =  Total_AvgCurr >> 1;		
			Total_AFVresult=0;       
			Total_AvgCurr=0;
			AFcnt=0;
			iPIDcntr = PID_CNTR;
			adcreadf=1;
			Call_MIG_PID();
			if(0)//weldcyclestrt==1)
			{	 				
				ACT_CVOLTAGE=AFvtg>>2;	
				if(ACT_CVOLTAGE>=800)
				ACT_CVOLTAGE=800;	
				//MIG_superfast_PID();
				//adcreadf=0;
			} 						
		}
		if((iACT_CURRENT > 740) && (MIGweldon_detectf == 0) && (cTorchPressFoundfg == 1))
		{		
			cStartPulsefg = 1;
			cSoftStrfg = 1;				
			cPulseCnt =  STARTPULSECNT;	
			cTorchPressFoundfg = 0;

			if(cCreepSpeedDowncntfg == 0)
			{
				cCreepSpeedDowncntfg=1;				
			}		
			
			iStartCurr = STARTPULSECURRENT;			
														
		}
		else if((iACT_CURRENT > 150) && (MIGweldon_detectf == 1))
		{
			cSoftStrfg = 1;
		}		 		  
	}
		  	
	/*if((weldmode=='G') && (weldcyclestrt==1))
	{
		if(adcreadf == 1)
		{	
			adcreadf = 0;
			ACT_CVOLTAGE=AFvtg>>2;	
			if(ACT_CVOLTAGE>=800)
			ACT_CVOLTAGE=800;	
			MIG_superfast_PID();
			iPIDcntr--;	
			if(iPIDcntr == 0)
			{
				adcreadf = 0;
			}							
		} 		  
	} */ 
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)// for Each channel adc conversion=5usec; for 3=15usec
{
  //GASWATERIPLAT=1;	
//------------------MODIFICATIONS IN ADC ISR--------------------
	
	if(SCKTcnt < 16)	//64)
	{
		SCKTcnt++;
		Total_SCKAresult+=ADCBUF0;
		/*
		if(weldmode=='G')
		{	
			if(0)//iWireSpeed >= 100)
			{
				//mult_factor_1 = iWireSpeed*mig_Kc/10;
				//Total_SCKVresult+=ADCBUF1 + mig_Kc;//mult_factor_1 - mig_Ka;  //28062022
			}	  	
			else
			{
				Total_SCKVresult+=ADCBUF1;
			}		
		}
		else
		{
			Total_SCKVresult+=ADCBUF1;
		}	
		*/
		Total_SCKVresult+=ADCBUF1;		
	}

	if(DISPcnt < 8192)//16384)
	{
		DISPcnt++;
		Total_DISPAresult+=SCKamp;
		Total_DISPVresult+=SCKvtg;
	}
		
	if(PULSEONOFFcnt < 4)
	{
		PULSEONOFFcnt++;
		Total_PULSEONOFFAresult+=SCKamp;
	}

	if(iArcforceVtgcnt < 64)
	{
		iArcforceVtgcnt++;
		Total_SCKARCFVresult+=ADCBUF1;
	}

	/*if(weldmode=='G')
	{
		AFcnt++;
		Total_AFVresult+=ADCBUF1;// + (mig_Kc*10); 	//7
		Total_AvgCurr+=ADCBUF0;
			
		if(AFcnt>=2)               
		{
			AFvtg=Total_AFVresult >> 1 ;
			iACT_CURRENT =  Total_AvgCurr >> 1;		
			Total_AFVresult=0;       
			Total_AvgCurr=0;
			AFcnt=0;
			iPIDcntr = PID_CNTR;
			adcreadf=1;
			Call_MIG_PID();
			if(0)//weldcyclestrt==1)
			{	 				
				ACT_CVOLTAGE=AFvtg>>2;	
				if(ACT_CVOLTAGE>=800)
				ACT_CVOLTAGE=800;	
				//MIG_superfast_PID();
				//adcreadf=0;
			} 						
		}
		if((iACT_CURRENT > 740) && (MIGweldon_detectf == 0) && (cTorchPressFoundfg == 1))
		{		
			cStartPulsefg = 1;
			cSoftStrfg = 1;				
			cPulseCnt =  STARTPULSECNT;	
			cTorchPressFoundfg = 0;

			if(cCreepSpeedDowncntfg == 0)
			{
				cCreepSpeedDowncntfg=1;				
			}		
			
			iStartCurr = STARTPULSECURRENT;			
														
		}
		else if((iACT_CURRENT > 150) && (MIGweldon_detectf == 1))
		{
			cSoftStrfg = 1;
		}		 		  
	}*/

	if(iMotorcnt < 64)						//MIG motor voltage
	{
		iMotorcnt++;
		Total_SCKMresult+=ADCBUF2;
	}


	if(iTripcnt < 512)
	{
		iTripcnt++;
		Total_SCKE1result+=ADCBUF3;
		Total_SCKE2result+=ADCBUF4;
	}
	
	if(AFVRcnt < 8192)						//MIG voltage reference	
	{
		AFVRcnt++;
		Total_AFVRresult+=ADCBUF5;			
	}
	
	if(AFIRcnt < 4096)						//MIG wirespeed reference
	{
		AFIRcnt++;
		Total_AFIRresult+=ADCBUF6;
	}
	
	if(AFCWSCcnt < 512)						//Crater WS & Setcurrent		
    {
	    AFCWSCcnt++;
		Total_AFCWSCresult+=ADCBUF7;     	
	}
			
	if(AFINDHScnt < 512)					//Inductance & Hotstart
	{
		AFINDHScnt++;
		Total_AFINDHSresult+=ADCBUF8;		
	}		
	if(AFCVAFcnt < 512)						//Crater voltage & Arcforce
	{
		AFCVAFcnt++;
		Total_AFCVAFresult+=ADCBUF9;
	}	
	if(iRemotecnt < 128)					//MMA-TIG Remote
	{
		iRemotecnt++;
		Total_AFRresult+=ADCBUFA;
	}

 	IFS0bits.ADIF = 0;  
 	//GASWATERIPLAT=0;
    //Toggle_Test_Pin();			
}


void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void)
{
   IFS1bits.SPI2IF=0;
   DACCSLAT=1;
   if(SPI2STATbits.SPIROV==1)
   SPI2STATbits.SPIROV=0;
}
void Call_MIG_PID()
{
	if((weldmode=='G') && (weldcyclestrt==1))
	{
		if(adcreadf == 1)
		{	
			adcreadf = 0;
			ACT_CVOLTAGE=AFvtg>>2;
			if(ACT_CVOLTAGE<=100)
			{
				ACT_CVOLTAGE=100;
			}		
			else if(ACT_CVOLTAGE>=800)
			{
			    ACT_CVOLTAGE=800;
			}	
			MIG_superfast_PID();
			iPIDcntr--;	
			if(iPIDcntr == 0)
			{
				adcreadf = 0;
			}							
		} 		  
	}
}
/*
void __attribute__((interrupt, no_auto_psv))_U1RXInterrupt(void)
{
   IFS0bits.U1RXIF = 0; // clear rX interrupt flag
   uartdata1       = U1RXREG; //			  
}

void __attribute__((interrupt, no_auto_psv))_U2TXInterrupt(void)
{
   IFS1bits.U2TXIF = 0; // clear rX interrupt flag 
}

void __attribute__((interrupt, no_auto_psv))_U2RXInterrupt(void)
{
   IFS1bits.U2RXIF = 0; // clear rX interrupt flag
   uartdata2      = U2RXREG; //
}   
*/

/*
	if(cTestfg==1)
	{
		cTestfg=0;
		MPWM = 0;
	}
	else
	{
		cTestfg=1;
		MPWM = 1;
	}
*/