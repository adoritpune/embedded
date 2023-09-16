void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)       //TIMER1 INTERRUPT
{
    IFS0bits.T1IF=0;
	count_1ms++;
	count_tx2_1ms++;
	count_transmit++;
	communication_time_out++;
	cFrameStr++;
	if(iRemotechkCntr == 0)
	{
		remote_flag = 0;
	}
	else
	{
		iRemotechkCntr--;
	}	
	if(cFlashCntr != 0)
	{
		cFlashCntr--;
	}
	else
	{
		cFlashCntr = 0;
	}		
	if(cPowerOnblockrxfg == 1)
	{
		if(iPowerOnCntr == 0)
		{			
			cPowerOnblockrxfg = 0;							 		
		}
		else 
		{
			iPowerOnCntr--;
		}		
	}		
	if(receive_parameter.Gas_check_key==1)  //gas check operation
    {
	   gas_check_f=1;
	   //CURR_LEDLAT=1;
		    
	}
	else
	{
	
	   gas_check_f=2;
	   //CURR_LEDLAT=0;
	}
/*				
	if(mig_parameters ==1)
	{
		parametercnt++;
		if(parametercnt >= 1 )
		{
			count_preflow++;
			burnbackcnt++;
			count_postflow++;
			parametercnt = 0;
		}
	}
*/
//---------------------------------------------------

	if(error_4_check4t==1)
	{
		if(cntsecond_er4>ERROR4_DEBOUNCE_TIME)
		{
			error_4_check4t = 0;
			cErrorChkoverfg = 1;	
			if(error4_flag==1)
			{
				ERROR_4_errorf=1;
				cntsecond_er4=ERROR4_DEBOUNCE_TIME;					
				error4_flag = 0;
				psstatus.motoron=0;
				psstatus.gasoncommand=0;								
			}					
		}
		else
		{
			cntsecond_er4++;
			ERROR_4_errorf=0;
		}				
		if(dispweldcurrent<ERROR_4_THRESHOLD)  
		{
			error4_flag=1;
		}	
		else
		{
			error4_flag=0;
		}
	}
	
//---------------------------------------------------
	if((communication_time_out>=COMMUNICATION_TIME_OUT) && (process_flag==MIGMODE))
    {
    	comm_errorf=1; 
    	communication_time_out=COMMUNICATION_TIME_OUT;
    }
    else
    {
   		comm_errorf=0;
    }

//---------------------------------------------------			
				
	
	/*if(count_transmit>50)
	{
	
	    mig_trans_f=1;
	    count_transmit=0;
	    
	}
	else
	{
		mig_trans_f=0;
	
	}*/
	if(MIGON==0)
	{
		process_flag=MIGMODE;
		migmodeon=1;
		
	}
	else
	{
		process_flag=MMAMODE;
		migmodeon=0;
	
	
	}	
	/*
	if(count_preflow>500)
	{
	   count_preflow=0; 
	}
	*/
	if(count_tx2_1ms>=10)   //update status after 10msec
	{
		count_tx2_1ms=0;
		count_tx2++;
		

		if(count_tx2<20)//55
		{
			//transmit_parameter.psstatusbyte=psstatusu.psstatusbyte[0];
			communication.psstatusbyte=psstatusu.psstatusbyte[0];
			
			if(starttx2==0)
			{
				startstatustx2=1;    //send status
				tx2statuscounter=0;
			    U2TXREG='#';
			
			}
		}
		
		if(count_tx2>=20)//55
		{
			count_tx2=0;
//			transmit2wf_f=1;          //send data					
	    } 		
		
	}
	if(cFrameStr >= 100)
	{	
		cFramefg=1;
		cFrameStr = 0;
	}	
	if( (hotf==1) && (weldon==1) && (process_flag==MMAMODE) ) //in isr, hotf=1 when weld current<50
	{
		    hotstartcount++;
			if(hotstartcount>HOT_STRT_TIME)	   //HOT_STRT_TIME=500
			{
			hotstartcount=HOT_STRT_TIME;
			hotf=0;
			}	
	}
	else
	{
		hotstartcount=0;

	}
	
	if(weldcurrent >=2000)
	{
		over1=0;
		if(++over>=2000)
		{
		over=2000;
		overflag=1;           //machine trip
		}
	}
	else                      //continuously, for 5 sec current is<2000.
	{
		over=0;
		if(++over1>=5)
		{
		over1=5;
		overflag=0;
		}
		
	}
	
	if(weldon==1)
	{
		dVal4=0;
		if(++dVal5>=2000)
		{
		dVal5=2000;
		startdf=1;       //welding is continuously going on 2000 counts 
		}
	}
	else
	{
		dVal5=0;
		if(++dVal4>=15)  //weld on=0 , continuously for 15
		{
		dVal4=15;
		startdf=0;
		}
	}	
	if((curimb>imbal)&&(startdf==1))  //check for current imbalance startdf=>welding on for 2000 counts
	{
		dVal2=0;
		if(++dVal3>=2000)
		{
		dVal3=5000;
		curimbf=1;        //current imbalance error
		}
	}
	else
	{
		dVal3=0;
		if(++dVal2>=5)
		{
		dVal2=5;
		curimbf=0;
		}
	}		
	if(count_1ms>=50)
	{
		count_1ms=0;
//		Read_portpin();	
		if(cyclestrt==1 && motoronf ==1) //torch function scan
		{
//			second_order_pid();
			if(Motorerr=='E')
				motorerrcnt++;
			else
				motorerrcnt=0;
		}
	}
     	if(count_10ms==10)     // 10 MSEC DELAY
      {
          count_10ms=0;        // CHECK FOR TRIP CONDITION AFTER EVERY 10 MSEC    
          disp_cnt++;
          remotecnt++;
          trip(); 
          if(remoteonf==1 && process_flag==MMAMODE)  //only in MMA mode
          {
	          	if(remotecnt>=500)
	          	{
	          		operator='P';
	          		remotecnt=0;
	          		remoteonf=0;
	          	//	REMOTELEDLAT=0;	
	           	}
	          	else
	          	{
	          		operator='R';
	          	//	REMOTELEDLAT=1;
	           	}
          }
          if(disp_cnt>=100)//20)
          {
          		disp_cnt=0;
          		disp_flag=1;
			migcount++;
			if(migcount > 25)
			{
				migmodeon=0;
				migcount=0;	
			}
	      }
        if(count_100ms>=100)
		{
			count_100ms=0;             //1 SEC DELAY
		   	mma_init=1;
		   	//disp_flag=1;
		   	Read_Ensw=1;
		   	cali_on1=1;
		}
          count_100ms++;
        }
     
        //display_data();                       //DISPLAY ROUTINE
        refresh_display();
      	count_10ms++;
      	count_3sec++;    
      	if(comm_count>=1000)                  	//FOR COMMUNICATION ERROR
      	{ 
      	        welding_status=0;   
	     }  
	    if(process_flag==MMAMODE)				//shunt fb calibration
	    {
	       if(calmodef==0)
		  {
			   if(ENCODERSW==0 && arcforcemodef==0 && keyrelease==1)                    //SWITCH PRESSED
			   {
					arcforcemodef=1;
					Disp_updatef=1;
					keyrelease=0;
			   }
			   else if(ENCODERSW==0 && arcforcemodef==1 && 	keyrelease==1)              //SWITCH PRESSED
			   {
					arcforcemodef=0;
					Disp_updatef=1;
					keyrelease=0;
			   }
			   if(ENCODERSW==1)                        //SWITCH released
			   {
				keyrelease=1;
			   }
		  } 
		  else  if(calmodef==1)
		  {
			Check_cal_mode();                          //cal mode function is in ISR file
		  } 

		  if(calmodef==0 && setupcalmode==0)
		  {
			if(ENCODERSW==0)          //encoder switch is pressed for 5 sec then enters in calibration mode
			{
				dvalcnt++;
				if(dvalcnt>=5000)    //5sec
				{
					calmodef=1;       //entry in calibration mode
					setupcalmode=1;
					arcforcemodef=0;
					Disp_updatef=1;
					keyrelease=0;
					dvalcnt=0;
					dispcalmodef=1;
				}
			}
			else
			{
				dvalcnt=0;
				calmodef=0;
				setupcalmode=0;
				dispcalmodef=0;
			}
		 }

	  }
	  else
	  {						 
	  } 
	  if(process_flag==MIGMODE && cyclestrt==1)
	  {
		  if(adcread_overf==1) //FOR cv
		  {
		  
//		     adcread_overf=0; //commented on 25052020
//		     actual_voltage=(resultv*10)/50;   
	//	     actual_voltage=(resultmig*10)/35;
//		     if(actual_voltage>=500)
//		     actual_voltage=500;
//		     resultmig=0;
//		     superfast_pid();
		     //second_order_pid();
		     //scaled_sf_pidoutput=sf_pidoutput;
		     //dac_counts=scaled_sf_pidoutput*CVSLOPE;
		     //dac_counts=(migdaccount*MIGCCSLOPE) -  MIGCCOFFSET;	//original	     
		  }
	  
	  
	  }
}
void Check_cal_mode()
{
		if((ENCODERSW==1)&&(scalmode==0))
	  	{
			dVal0=0;
			if(++dVal1>=15)
			{
				dVal1=15;
				shuntcal1f=0;
				shuntcal2f=0;
				releasef=1;
			}  		
 		}
	     if((ENCODERSW==0)&&(scalmode==0)&&(releasef==1))
	   
	    		{
	    			dVal1=0;
	    			if(++dVal0>=5000)
	    			{
	    				dVal0=5000;
	    				shuntcal1f=1;
	    				scalmode=1;
	    				releasef=0;
					dispcalmodef=0;

	    			}
	    		
	    		} 
	    if((ENCODERSW==1)&&(scalmode==1))
	    	{
	    			dVal0=0;
	  				if(++dVal1>=15)
	  				{
	  					dVal1=15;
	  					releasef=1;
	  				}  	
	    		
	    	}	
	    if((ENCODERSW==0)&&(shuntcal1f==1)&&(releasef==1))
	   
	    		{
	    			dVal1=0;
	    			if(++dVal0>=5000)
	    			{
	    				dVal0=5000;
	    				shuntcal1f=0;
	    				shuntcal2f=1;
	    				scalmode=1;
	    				releasef=0;

	    			}
	    		
	    		}
	    if((ENCODERSW==0)&&(shuntcal2f==1)&&(releasef==1))
	   
	    		{
	    			dVal1=0;
	    			if(++dVal0>=5000)
	    			{
	    				dVal0=5000;
	    				shuntcal1f=0;
	    				shuntcal2f=0;
	    				scalmode=0;
	    				releasef=0;
					calmodef=0;
					setupcalmode=0;
					arcforcemodef=0;
					Disp_updatef=1;
					keyrelease=0;
					dvalcnt=0;
					dispcalmodef=0;
	    			}
	    		
	    		} 	 			
	    }











void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)       //FOR PWM PERIOD
{
     IFS0bits.T2IF=0;         
}
    
    
void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)       //FOR ENCODER SCANNING
{
     IFS1bits.T4IF=0;
     if(process_flag==MMAMODE && operator=='P')
     {
	 	mili_100++;
     	encod=scanencoder();
     	if(arcforcemodef==0)
		{
			if(encod=='+' && setcurrent<=800)   
	        		setcurrent=setcurrent+pluspara;
		     else if(encod=='-' && setcurrent>50)   //
			    	setcurrent=setcurrent-minuspara;
		     else if(setcurrent>=800)
		        	setcurrent=800;
		     else if(setcurrent<=100)   //50
		        	setcurrent=100;   //50
	     }    
		else if(arcforcemodef==1)
		{
			if(encod=='+' && arcforce<=100)   
	        		arcforce=arcforce+pluspara;
		     else if(encod=='-' && arcforce>0)    
		     {        
		         if(arcforce>=minuspara)
		    	 arcforce=arcforce-minuspara;
		    	 else if(arcforce>0)
		    	 {
			     arcforce=arcforce-1;
			     }			    	 
			 }	
		     else if(arcforce>=100)
		        	arcforce=100;
		     else if(arcforce<=0)
		        	arcforce=0;
	     }    

	    if(mili_100<200)
	    {
	           if(encod=='+')
	              pluscount++;
	           else if(encod=='-')
	              minuscount++;
	 	}
	     else if(mili_100>=200)
	     {
		        mili_100=0;
		        pluspara=pluscount;
		        minuspara=minuscount;
		        if(pluspara<=1)
		          pluspara=1;
		        if(minuspara<=1)
		          minuspara=1;
		          pluscount=0;
		          minuscount=0;
	    }                   
	}
	else if(process_flag==MIGMODE)
	{
		trans_chk_f=1;
		mili_100++;
     	encod=scanencoder();
//--------------------- 
		if(cpidmode == 0)
		{
     	     if(encod=='+' && rset_wirespeed<=220)
     	     {
				rset_wirespeed=rset_wirespeed+pluspara;
				communication.setwspeed	= rset_wirespeed;   
				//transmit2wf_f = 1;
			//	cFramefg =1;
				cEditfg = 1;
     	     }      
     	     else if(encod=='-' && rset_wirespeed>20)   //
     	     {
			    rset_wirespeed=rset_wirespeed-minuspara;
		        communication.setwspeed	= rset_wirespeed;   			    	
				//transmit2wf_f = 1;
				//cFramefg = 1;		        
				cEditfg = 1;				
			 }
		     else if(rset_wirespeed>=220)
		        	rset_wirespeed=220;
		     else if(rset_wirespeed<=20)
		        	rset_wirespeed=20;  
		        	 
     	           /*
     	     if(encod=='+' && rsetcurrent<=800)   
	        		rsetcurrent=rsetcurrent+pluspara;
		     else if(encod=='-' && rsetcurrent>50)   //
			    	rsetcurrent=rsetcurrent-minuspara;
		     else if(rsetcurrent>=800)
		        	rsetcurrent=800;
		     else if(rsetcurrent<=50)
		        	rsetcurrent=50;
		        	*/
		}
		else if(cpidmode == 1)
		{
			if((encod=='+'))
				iKp = iKp + pluspara;
			else if((encod=='-')&&(iKp >= 10))
				iKp = iKp - minuspara;
				
			if(iKp>= 9999)
			{
				iKp = 0;
			}			
			if(iKp <= 10)
			{
				iKp = 10;
			}	
		}
		
		else if(cpidmode == 2)
		{
			if(encod=='+')
				iKi = iKi + pluspara;
			else if((encod=='-') &&(iKi >= 1))
				iKi = iKi - minuspara;
				
			if(iKi>= 9999)
			{
				iKi = 1;
			}			
			if(iKi <= 1)
			{
				iKi = 1;
			}	
		}
		
		else if(cpidmode == 3)
		{
			if(encod=='+')
				iKd = iKd + pluspara;
			else if((encod=='-')&&(iKd >= 1))
				iKd = iKd - minuspara;
				
			if(iKd>= 9999)
			{
				iKd = 0;
			}			
			if(iKd <= 1)
			{
				iKd = 1;
			}	
		}	
		else if(cpidmode == 4)
		{
			if(encod=='+')
				iMul = iMul + pluspara;
			else if((encod=='-')&&(iMul >= 1))
				iMul = iMul - minuspara;
				
			if(iMul>= 9999)
			{
				iMul = 0;
			}			
			if(iMul <= 1)
			{
				iMul = 1;
			}	
		}		
		else if(cpidmode == 5)
		{
			if(encod=='+')
				iMigOffset = iMigOffset + pluspara;
			else if((encod=='-')&&(iMigOffset >= 1))
				iMigOffset = iMigOffset - minuspara;
				
			if(iMigOffset>= 9999)
			{
				iMigOffset = 0;
			}			
			if(iMigOffset <= 1)
			{
				iMigOffset = 1;
			}	
		}
		else if(cpidmode == 6)
		{
			if(encod=='+')
				iLowpidvalue = iLowpidvalue + pluspara;
			else if((encod=='-')&&(iLowpidvalue >= 1))
				iLowpidvalue = iLowpidvalue - minuspara;
				
			if(iLowpidvalue>= 9999)
			{
				iLowpidvalue = 0;
			}			
			if(iLowpidvalue <= 1)
			{
				iLowpidvalue = 1;
			}
		}
		else if(cpidmode == 7)
		{
			if(encod=='+')
				imfvalue = imfvalue + pluspara;
			else if((encod=='-')&&(imfvalue >= 1))
				imfvalue = imfvalue - minuspara;
				
			if(imfvalue>= 9999)
			{
				imfvalue = 0;
			}			
			if(imfvalue <= 1)
			{
				imfvalue = 1;
			}
		}
										        	
//-------------------------------
		        	
		     
	    if(mili_100<200)
	    {
	           if(encod=='+')
	              pluscount++;
	           else if(encod=='-')
	              minuscount++;
	 	}
	     else if(mili_100>=200)
	     {
		        mili_100=0;
		        pluspara=pluscount;
		        minuspara=minuscount;
		        if(pluspara<=1)
		          pluspara=1;
		        if(minuspara<=1)
		          minuspara=1;
		          pluscount=0;
		          minuscount=0;
	    }     
	
	
	}
	else 
	{
		encod=scanencoder();
     		if(encod=='+' && hsetvoltage<460)   
        		hsetvoltage=hsetvoltage + 1;
	     else if(encod=='-' && hsetvoltage>140)
		    	hsetvoltage=hsetvoltage-1;
	     else if(hsetvoltage>=460)
	        	hsetvoltage=460;
	     else if(hsetvoltage<=140)
	        	hsetvoltage=140;
	}
}

void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)      //ADC INTERRUPTS
 {
/* 
   if(Testfg==1)
   {
	 Testfg=0;
	 CURR_LEDLAT = 1;
   }
   else 
   {
     Testfg=1;
	 CURR_LEDLAT = 0; 		
   }	 
*/   
   ADCON1bits.ASAM = 0;
   IFS0bits.ADIF = 0; 
   result0	= ADCBUF0;                        //FEEDBACK VOLTAGE
   result1 	= ADCBUF1;                        //FEEDBACK CURRENT
   result2 	= ADCBUF2;                        //TRIP CONDITION
   result3 	= ADCBUF3;                        //SAW/MMA MODE
   result4 	= ADCBUF4;                        //AN11     NC1     
   result5 	= ADCBUF5;                        //AN14     MTR VTG
   
   resultmig =resultmig +   result0;            //25012020 
   resultv	=resultv	+	result0;
   resulti	=resulti	+	result1;
   resultt	=resultt	+	result2;  
   resultsm	=resultsm   +	result3;
   resultsh1 =resultsh1	+ 	result4;
   resultsh2 =resultsh2	+ 	result5;
     
   
   cnt++;                                             //mig counts
   cnt_mma++;                                         //mma counts
   
   //mma averaging
   resultv_mma=resultv_mma+result0;                   //mma voltage
  
   if(cnt_mma>=VTG_AVG_COUNT)                        //256(2^8)
   {
   mma_weldvoltage=resultv_mma 	>>  VTG_AVG_SHIFT;	 //8 TIMES SHIFTED
   
   mma_weldvoltage=(mma_weldvoltage*10)/35;          //mma_weldvoltage ->final variable for mma voltage
   
   cnt_mma=0;
   resultv_mma=0;
   
   }
	
	iAvg_cntr++;
	//resultmig=resultv;
	
	if(iAvg_cntr >= iAvg_cnt)
	{
     	resultmig = resultmig >> iNoofshift;
     	iAvg_cntr = 0;
     	adcread_overf=1;
	    //actual_voltage =(resultmig*10)/35;					// commented on 24012020  
	    actual_voltage =(resultmig*10)/35;					// commented on 24012020  
	    resultmig = 0;   	
	}	
   //mig mode averaging
   if(cnt>=loop)                                     //counts->4096(2^12)
    {
     resultv 		=   resultv 	>>  iNoofDispShift;          //12 times shifing
     resulti		=   resulti 	>> 	iNoofDispShift;
     resultt 		=   resultt 	>> 	iNoofDispShift;
     resultsm   	=   resultsm	>>	iNoofDispShift;
     resultsh1		=	resultsh1	>>	iNoofDispShift;
     resultsh2		=	resultsh2	>>	iNoofDispShift;
   
     cnt=0;
     //shfb1curr=resultsh1*1/10;    //*10/54;
     shfb1curr=resultsh1*13/100;
     resultsh1=0;
     //shfb2curr=resultsh2*1/10;    //*10/54;
     shfb2curr=resultsh2*13/100;
     resultsh2=0;
//     adcread_overf=1;
     
  	
	
			if(migmodeon==0)
			{ 
				process_flag=MMAMODE;           //only MMA present. No SAW.                      
				/*if(resultsm >= 3600 )			//SAW MMA SELECTION INPUT
				{                               //when saw and mma both were present
					process_flag=MMAMODE;
				}
				else 
				{
					process_flag=SAWMODE;
				}*/
				resultsm = 0;
			}	
			                            
	        //TRIP                   
			trip_ip=resultt;             //TRIP CONDITIONS. Error type is decided using these counts.
	 		resultt=0;
	
            //VOLTAGE                             //RC VOLTAGE CALCULATION
	        tempvolt=(resultv*10)/35;					// commented on 24012020
	        weldvoltage=tempvolt;      //(resultv*10)/35;   // 100 VOLTS = 3500 COUNTS 4.27v // commented on 24012020
	        resultvc=resultv;
	        resultv=0;
      
           //CURRENT                            //RC VOLTAGE CALCULATION
           weldcurrent=(resulti*20)/49;		// /12)/37;//1200AMPS=3700 COUNTS
           resultic=resulti-(offset*49);	//20;//37)/12;
           resulti=0;
           /*if(weldcurrent >=300)
           {
	  	       OCV_FLAGLAT	=0;          		//OCV ON
	  	       TRIPLEDLAT=1;
	  	   }*/
	       	if(offsetf==0)                //OFFSET, this flag will become zero only on machine off
		   	{
				if(offsetcnt>=10)  //10)		//  check at 2/3/4/5 changed on 19062020
				{
				  offset=weldcurrent;     //total current
				  offsetsh1=shfb1curr;    //shfb1curr= op of shunt1(max 400) Initial value(ideally zero) is loaded here
				  offsetsh2=shfb2curr;    //shfb1curr= op of shunt2(max 400)
				  offsetf=1;
				  cPowerFlashfg = 0;
				}
	              offsetcnt++;
		   	}
		   	else
		   	{
				
					
				//comparison with offset
				if(shfb1curr>=offsetsh1)                               //shunt1
				{
					shfb1curr=shfb1curr-offsetsh1;                     //200//300
					if(shfb1curr<=300.0)                                //200
						dispshfb1=shfb1curr+((300.0-shfb1curr)*0.050);
					else 
						dispshfb1=shfb1curr-((shfb1curr-300.0)*0.050);
				}
				else
				shfb1curr=0;	
					
				if(shfb2curr>=offsetsh2)                              //shunt 2
				{
					shfb2curr=shfb2curr-offsetsh2;                    //200//300
					if(shfb2curr<=300.0)
						dispshfb2=shfb2curr+((300.0-shfb2curr)*0.050);
					else 
						dispshfb2=shfb2curr-((shfb2curr-300.0)*0.050);	
				}
				else
				shfb2curr=0;
				
				
				
				if(weldcurrent >=offset)
				{
					weldcurrent=weldcurrent-offset;
					shfbweldcurr=shfb1curr+shfb2curr;    //total current from both shunts
					if(shfbweldcurr>=100)
					{ //imbal is approximately 1/5th of total current
							
							if(shfbweldcurr>=590)         //390
							imbal=(20.0*shfbweldcurr)/100.0;
							else if(shfbweldcurr< 590.0)
							imbal=(25.0*shfbweldcurr)/100.0;// 30 to 25 changed on 22012020
							else
							imbal=100; 
					}


				    //display weldcurrent
					if(weldcurrent< 590.0)                                    //390
						dispweldcurrent=weldcurrent+((600.0-weldcurrent)*0.07);
					else if(weldcurrent>=590.0 && weldcurrent<= 610.0)
							dispweldcurrent=weldcurrent;
					else if (weldcurrent>610.0)                               //610
							dispweldcurrent=weldcurrent-((weldcurrent-600.0)*0.01);
								
				}
				else
					weldcurrent=0;	
				
				
					if(dispshfb1>dispshfb2)
						curimb=abs(dispshfb1-dispshfb2);
					else if(dispshfb2>dispshfb1)
						curimb=abs(dispshfb2-dispshfb1);
				
				//curimb should always be less than imbal, otherwise error 10.
			
         }
	
	
	   if(offsetf==1)		
	    {
		    if(migmodeon==1)
		    {
			    if(psstatus.weldon==1)
			    {
			       weldon=1;
			    }
			    else
			    {
			    
			       weldon=0;
			    }
		    
		    }
		    else
		    {
					//if(weldcurrent >= 50)//50)
					if(weldcurrent >= 10)
					weldon=1;        //WELDING ON
					else                 //if welding current is <50
					{
					if(weldon==1 && process_flag==MMAMODE)
					{
					if(pcurrent!=setcurrent)
					{
					EEPROM_Erase_Write((1*2),setcurrent);
					pcurrent=setcurrent;
					}
					if(parcforce!=arcforce)
					{
					EEPROM_Erase_Write((3*2),arcforce);
					parcforce=arcforce;
					}
					weldon=0;   //WELDING OFF
					hotstartcount=0;          //hotstart time counter ON
					hotf=1;                   //hotstart ON
					}
					}
			}
		
		}
		//##############################################################################################
		if( welding_status=='O' && calibrationf==1 && avgcntr<=16)  //to be verified //sayali
		{
			measured_psvtg=measured_psvtg+weldvoltage;
			measured_pscur=measured_pscur+weldcurrent;
			avgcntr++;
			if(avgcntr==16)
			{
				read_hvtgf=0;
				avg_hvtg= measured_hvtg/recvtgcntr;//;measured_hvtg>>5;
				avg_psvtg=measured_psvtg>>4;
				avg_pscur=measured_pscur>>4;
				if(avg_psvtg>=avg_hvtg)
					resistance=(avg_psvtg-avg_hvtg)*1000.0/avg_pscur;    
				else
					resistance=0;

				EEPROM_Erase_Write((2*2),(resistance*10.0));
				offsetsetvtg=resistance;
			}	
			else
				if(avgcntr <=16)
				offsetsetvtg=avgcntr;
			
		}
		//#############################################################################################
     }
     
    
     
   ADCON1bits.ASAM = 1;
}

void __attribute__((interrupt, no_auto_psv))_U2TXInterrupt(void)
{
   IFS1bits.U2TXIF = 0; // clear rX interrupt flag
   if(starttx2==1)
   {
      if(tx2counter<=STRING_LENGTH) //21)
      {
         U2TXREG=trans_ps_wf_arr[tx2counter];//pstowfstru.pstransarr[tx2counter];
         tx2counter++;
      }
      else if(tx2counter==(STRING_LENGTH+1))//22)
      {
         U2TXREG=trans_ps_wf_arr[(STRING_LENGTH+1)];//tx2chksum;                 
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
      
//      pstowfstr.psstatusbyte=psstatusu.psstatusbyte[0];
      communication.psstatusbyte=psstatusu.psstatusbyte[0];
      if(tx2statuscounter==0)
      {
         //U2TXREG=pstowfstr.psstatusbyte;//transoffu.transarr[tx2counter];
         U2TXREG=communication.psstatusbyte;//transoffu.transarr[tx2counter];
         tx2statuscounter++;
      }
      else if(tx2statuscounter==1)
      {
         //U2TXREG=pstowfstr.psstatusbyte;//transoffu.transarr[tx2counter];
         U2TXREG=communication.psstatusbyte;//transoffu.transarr[tx2counter];
         tx2statuscounter=0;
         startstatustx2=0;
      }
   }   
}
void __attribute__((interrupt, no_auto_psv))_U2RXInterrupt(void)
{
   IFS1bits.U2RXIF = 0; // clear rX interrupt flag
   uartdata2      = U2RXREG; 
   /*
	if(U2STAbits.OERR==1)  //receive buffer overrun
	U2STAbits.OERR=0;
	if(U2STAbits.FERR==1)  //framing error
	U2STAbits.FERR=0;
	if(U2STAbits.PERR==1)  //parity error
	U2STAbits.PERR=0;
	*/	
   //if(uartdata2=='@' && startptr1==0 && startstatus1==0 )//&& transonf==0)
   if(uartdata2=='@' && start_rec_data==0 && start_rec_status==0 )//&& transonf==0)
   
   {    
      start_rec_data=1;   //startptr1=1;
      start_rec_status=0; //startstatus1=0;
      recchksum=0;
      arr_pointer=0;
				 
   }
   else if(uartdata2=='#' && startptr1==0 && startstatus1==0)// && transonf==0)
   {    
      start_rec_status=1; //startstatus1=1;
      start_rec_data=0; //startptr1=0;
      arr_pointer=0;
      recchksum=0;
      mig_flag=1;
   }
   else if(start_rec_data==0 && start_rec_status==1 )//&& transonf==0)
   {
      //if(recstatus==0)
      if(rec_status_f==0)
	  {
         rec_wf_status=uartdata2;
         rec_status_f=1;
      }
      else if(rec_status_f==1)
      {
         if(uartdata2==rec_wf_status) //?
         {
            comm_errorf=0; 
			communication_time_out=0;
                      
            wf_statusu.wfstatusbyte[0]=rec_wf_status;
                       
      		start_rec_data=0;   //startptr1=1;
      		start_rec_status=0; //startstatus1=0;
            rec_status_f=0;
            arr_pointer=0;
            if(wfstatus.torchonstatus==1)
            {
               //torchonstatus='T';
               Torchkey='P';
             
            }
            else
            {
               //torchonstatus='X';
               Torchkey='R';
            } 
            
            if(wfstatus.twotfourtmode1==0)
            {         
               //torchonstatus='T';
               Torchmode='2';
             //  Type.twot=1;
			 //  Type.fourt=0;
               
            }
            else
            {
               //torchonstatus='X';
               Torchmode='4';
			   //Type.twot=0;
			  // Type.fourt=1;               
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
            start_rec_data=0; //startptr1=0;
            arr_pointer=0;
            recchksum=0;
            start_rec_status=0;//startstatus1=0;
            rec_status_f=0;
          }
      }
   }
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   
    else if(start_rec_data==1 && start_rec_status==0 )//&& transonf==0)
    {    
      if(arr_pointer<=15) //STRING_LENGTH) //21)
        {    
         received_arr[arr_pointer]=uartdata2;
         recchksum=recchksum+uartdata2;
         arr_pointer++;
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
        else if(1)//recchksum==uartdata2)
        {    
	       //if(process_flag==MIGMODE)
	       //{
		    //if((communication.setwspeed>=20) && (communication.setwspeed<=220) && (WfEditfg == 1)) //((rset_wirespeed >= 20) && (rset_wirespeed <= 220) && (WfEditfg == 1))
		    //{
            comm_errorf=0; 
			communication_time_out=0;
//**********************                       
//            for(iii=1;iii<=15;iii++) //20
//            {    
//                //pstowfstru.pstransarr[iii]=rec_arr[iii]; 
//                commu_ps_wfu.commu_arr[iii]=received_arr[ii];
//            }
//*********************
//		    communication.Lo_setvoltage = 0x64;
//		    communication.Hi_setvoltage = 0;		   		    
         	set_v=received_arr[5] ;//communication.Hi_setvoltage;
		    set_v = (set_v << 8);
		    set_v|=received_arr[6];//communication.Lo_setvoltage;
		    iTest = set_v;
			if((set_v >= MIN_SETVOLTAGE) && (set_v <= MAX_SETVOLTAGE) && (cPowerOnblockrxfg == 0))//&& (cEditfg == 0) && (blockrxfg = 0))
			{
				communication.Lo_setvoltage = received_arr[6];
				communication.Hi_setvoltage = received_arr[5];
				rsetvoltage = set_v; 
								
							
			}	 			
		    if((received_arr[1] >= MIN_WIRESPEED) && (received_arr[1] <= MAX_WIRESPEED) && (cPowerOnblockrxfg == 0) )//&& (cEditfg == 0) && (blockrxfg = 0))
		    {
         		communication.setwspeed = received_arr[1];
         		rset_wirespeed=communication.setwspeed;    		
      		}   	
//         	rset_wirespeed=communication.setwspeed;
//         	receive_parameter.setwspeed=communication.setwspeed;		    
//		    receive_parameter.Hi_setvoltage=communication.Hi_setvoltage;		    
//		    set_v=receive_parameter.Hi_setvoltage;
		    //set_v<<=8;		    		    
//		    receive_parameter.Lo_setvoltage=communication.Lo_setvoltage;
//		    set_v|=receive_parameter.Lo_setvoltage;		    
//		    rsetvoltage1=rsetvoltage1+set_v;
//				if(cTestfg == 1)
//				{
//					CURR_LEDLAT = 0;
//					cTestfg = 0;
//				}	
//				else
//				{
//					CURR_LEDLAT = 1;
//					cTestfg = 1;
//				}
			//} 
		   //}
		    cv_counter++;
		    if(cv_counter>4)
		    {
//		       rsetvoltage1=rsetvoltage1>>2;
//		       rsetvoltage=rsetvoltage1;
		       cv_counter=0;
		       rsetvoltage1=0;
		    
		    }
		   
         wf_statusu.wfstatusbyte[0]=communication.wfstatusbyte; //wfstatusbyte
         if(wfstatus.torchonstatus==1)
         {
            Torchkey='P';
         }
         else
         {
            Torchkey='R';
         } 		    
       /*  
         if(receive_parameter.Torch_on==1)
         {
            Torchkey='P';
         }
         else
         {
            Torchkey='R';
         } 
         if(receive_parameter.weldmode==2)
         {
            Torchmode='2';
         }
         else if (receive_parameter.weldmode==4)
         {
            Torchmode='4';
         } 
     */    
         start_rec_data=0; //startptr1=0;
         arr_pointer=0;
         recchksum=0;
      }    
      else
      {
         start_rec_data=0; //startptr1=0;
         arr_pointer=0;
         recchksum=0;
         start_rec_status=0; //startstatus1=0;
         rec_status_f=0;
      }
   }   
   else           
   {
      start_rec_data=0;
      arr_pointer=0;
      recchksum=0;
      start_rec_status=0;
      rec_status_f=0;
   
   }  
}   



void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) //FOR REMOTE DATA RECEPTION.
	{
	unsigned int intdata=0;
	IFS0bits.U1RXIF = 0; 
	uartdata1=U1RXREG;
     
	
	//trans(uartdata1);
	if(uartdata1=='$' && startptr1==0 && startptr2==0)
	{
	  	recchksum1=0;
	  	startptr1=1;
		rec_cnt1=0;
      }    
	else if(uartdata1=='%' && startptr1==1 && startptr2==0)		//Mma mode
	{
		recchksum1=uartdata1;
	    startptr2=1;
	    remote_flag = 1;
	    iRemotechkCntr = 2000;
	      
	}
	else if(uartdata1=='#' && startptr1==1 && startptr2==0)		//Mig mode
	{
		recchksum1=uartdata1;
	  	startptr2=2;
	}
	else if(uartdata1=='@' && startptr1==1 && startptr2==0)		//Revision display
	{
		recchksum1=uartdata1;
	     startptr2=3;
	}
	else if(startptr1==1 && startptr2==1) //mma mode
	{
		recdata_arr1[rec_cnt1]=uartdata1;
	     if(rec_cnt1<2)
	     { 
			recchksum1=recchksum1 + recdata_arr1[rec_cnt1]; 

		}    	
	     rec_cnt1++;
	     if(rec_cnt1==3)
	     {    	
		      startptr1=0;
			  startptr2=0;
			  rec_cnt1=0;
              	//recchksum1=recchksum1+'M';
		      if(recchksum1==recdata_arr1[2])
		      {
			      reclower1=recdata_arr1[0];
			      rechigher1=recdata_arr1[1];
			      intdata=rechigher1;
			      intdata=(intdata << 8)| reclower1;
			      setcurrent=intdata;
			      iTest=intdata;                       //setcurrent
			      remotecnt=0;
				  recchksum1=0;
			      remoteonf=1;
			 }
			 else
			 {
			     	recchksum=0;
			 }
	     }	    
	}	
	/*else if(startptr1==1 && startptr2==2)    //mig mode
	{
		recdata_arr1[rec_cnt1]=uartdata1;
	     if(rec_cnt1<4)
	     { 
			recchksum1=recchksum1 + recdata_arr1[rec_cnt1]; 
		}    	
	     rec_cnt1++;
	     if(rec_cnt1==5)
	     {    	
		    startptr1=0;
			startptr2=0;
			rec_cnt1=0;
              	//recchksum1=recchksum1+'M';
		      if(recchksum1==recdata_arr1[4])
		      {
			      	process_flag=MIGMODE;
					migmodeon=1;
					migcount=0;
					reclower1=recdata_arr1[0];
			     	rechigher1=recdata_arr1[1];
			      	intdata=rechigher1;
			        intdata=(intdata << 8)| reclower1;
			        rsetcurrent=intdata/4.0;                   //rsetcurrent
				
				  reclower1=recdata_arr1[2];
			      rechigher1=recdata_arr1[3];
			      intdata=rechigher1;
			      intdata=(intdata << 8)| reclower1;
			      rsetvoltage=140.0 +((intdata *3.0)/8.0);     //rsetvoltage
			      remotecnt=0;
				  recchksum1=0;
			      remoteonf=1;
			 }
			 else
			 {
			    recchksum1=0;
	  			startptr1=0;
				startptr2=0;
				rec_cnt1=0;
			 }
	     }	    

	}*/
	else if(startptr1==1 && startptr2==3)             //revision display
	{
			recchksum1=0;
	  		startptr1=0;
			startptr2=0;
			rec_cnt1=0;
	}
	else
	{
		recchksum1=0;
	  	startptr1=0;
		startptr2=0;
	}
}

void __attribute__((interrupt, no_auto_psv))_SPI2Interrupt(void)
{
	IFS1bits.SPI2IF=0;
	DACCSLAT=1;
	if(SPI2STATbits.SPIROV==1)
	SPI2STATbits.SPIROV=0;

}

