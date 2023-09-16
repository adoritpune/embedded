void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)       //TIMER1 INTERRUPT
{
    IFS0bits.T1IF=0;
	count_1ms++;

	if( (hotf==1) && (weldon==1) && (process_flag==MMAMODE) )
	{
		hotstartcount++;
			if(hotstartcount>HOT_STRT_TIME)	
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
			overflag=1;
		}
	}
	else
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
			startdf=1;
		}
	}
	else
	{
		dVal5=0;
		if(++dVal4>=15)
		{
			dVal4=15;
			startdf=0;
		}
	}	
	if((curimb>imbal)&&(startdf==1))
	{
		dVal2=0;
		if(++dVal3>=5000)  //2000  changed on 18062021
		{
			dVal3=5000;
			curimbf=1;
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
		Read_portpin();	
		if(cyclestrt==1 && motoronf ==1) //torch function scan
		{
			second_order_pid();
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
	          		REMOTELEDLAT=0;	
	           	}
	          	else
	          	{
	          		operator='R';
	          		REMOTELEDLAT=1;
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
     
        display_data();                      		//DISPLAY ROUTINE
      	count_10ms++;
      	count_3sec++;    
      	if(comm_count>=1000)                  	//maheshFOR COMMUNICATION ERROR
      	{ 
      	        welding_status=0;   
	     }  
	    if(process_flag==MMAMODE)				//shunt fb calibration
	    {
	        if(calmodef==0)
		  {
			   if(ENCODERSW==0 && arcforcemodef==0 && keyrelease==1)                        //SWITCH PRESSED
			   {
					arcforcemodef=1;
					Disp_updatef=1;
					keyrelease=0;
			   }
			   else if(ENCODERSW==0 && arcforcemodef==1 && 	keyrelease==1)                 //SWITCH PRESSED
			   {
					arcforcemodef=0;
					Disp_updatef=1;
					keyrelease=0;
			   }
			   if(ENCODERSW==1)                        //SWITCH PRESSED
			   {
				keyrelease=1;
				EEpromWrfg = 0;
			   }
		  } 
		  else if(calmodef==1)
		  {
			Check_cal_mode();
		  } 

		  if(calmodef==0 && setupcalmode==0)
		  {
			if(ENCODERSW==0)
			{
				dvalcnt++;

				if(dvalcnt>=5000 && dvalcnt<=7000)  
				{
					if(cCalikeyfoundfg ==0)
					{	
						if(cCalifg == 0)
						{
							cCalifg = 1;
						}
						else
						{
							cCalifg = 0;
						}					
						cCalikeyfoundfg =1;
					}
				}
				else 
				{
					cCalikeyfoundfg = 0;
					cCaliFoundfg 	= 0;				
				}
				if(dvalcnt>=15000)
				{
					calmodef=1;
					setupcalmode=1;
					arcforcemodef=0;
					cCalikeyfoundfg=0;
					Disp_updatef=1;
					keyrelease=0;
					dvalcnt=0;
					dispcalmodef=1;
					cLockfg = 0;					
				}
				if(dvalcnt>=9000 && dvalcnt<=13000 )
				{
					if(cLockkeyfoundfg ==0)
					{
						if(cLockfg == 0)
						{
							cLockfg = 1;
						}
						else
						{
							cLockfg = 0;
						}						
						cLockkeyfoundfg =1;
					}					

					cLockkeyfoundfg = 1;
				}
				else 
				{
					cLockkeyfoundfg = 0;				
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
/*
	    else
	    {
	    				shuntcal1f=0;
	    				shuntcal2f=0;
	    				scalmode=0;
	    				releasef=0;
	    }*/
	    
		    
//   }












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
	 	//if(cLockfg == 0)
	 	//{
     		encod=scanencoder();
   		//}  		
     	if(arcforcemodef==0 && cCalikeyfoundfg==0)
		{
			if(encod=='+' && setcurrent<=iSetAmpLimit && (cLockfg == 1))  		//iSetAmpLimit iSetcurrbuff
	        		setcurrent=setcurrent+pluspara;
	        		
	        else if(encod=='+' && setcurrent<=iSetcurrbuff && (cLockfg == 0))  //iSetAmpLimit iSetcurrbuff
	        		setcurrent=setcurrent+pluspara;
	        		
		    else if(encod=='-' && setcurrent>iSetmincurrbuff)   //
			    	setcurrent=setcurrent-minuspara;
			    	
		    else if(setcurrent>=iSetAmpLimit)
		        	setcurrent=iSetAmpLimit;
		    else if(setcurrent<=iSetmincurrbuff)
		        	setcurrent=iSetmincurrbuff;
	    }  
	    	      
		else if(arcforcemodef==1 && cCalikeyfoundfg==0)
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

		else if(cCaliFoundfg==1)//cCalikeyfoundfg==1 && arcforcemodef==0)
		{
			if(encod=='+' && iCalicnt<=500)
	        	iCalicnt=iCalicnt+pluspara;
		     else if(encod=='-' && iCalicnt>1)    
		     {        
		         if(iCalicnt>=minuspara)
		    	 iCalicnt=iCalicnt-minuspara;
		    	 else if(iCalicnt>1)
		    	 {
			     	iCalicnt=iCalicnt-1;
			     }			    	 
			 }	
		     else if(iCalicnt>=100)
		       	iCalicnt=100;
		     else if(iCalicnt<=1)
		        iCalicnt=1;
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
	else 
	{
		//if(cLockfg == 0)
		//{
			encod=scanencoder();
		//}	
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
   ADCON1bits.ASAM = 0;
   IFS0bits.ADIF = 0; 
   result0	= ADCBUF0;                        //VOLTAGE
   result1 	= ADCBUF1;                        //CURRENT
   result2 	= ADCBUF2;                        //TRIP CONDITION
   result3 	= ADCBUF3;                        //SAW/MMA MODE
   result4 	= ADCBUF4;
   result5 	= ADCBUF5;
   
   resultv	=resultv	+	result0;
   resulti	=resulti	+	result1;
   resultt	=resultt	+	result2;  
   resultsm	=resultsm   +	result3;
   resultsh1 =resultsh1	+ 	result4;
   resultsh2 =resultsh2	+ 	result5;
   
   cnt++;
//   mcnt++;
//   if(mcnt>=512)   	  //MOTOR VOLTAGE CALCULATIONS  
//   {
//	  resultfm	=   resultfm >>	9;	
//	  mcnt=0;
//       //tempmvolt=(resultfm*5.0)/35.00;
//	  tempmvolt=(resultfm*6.0)/35.00; 	
//	  mvoltage= tempmvolt;      // 500 VOLTS = 3500 COUNTS
//       resultfm=0;
//    }

   cnt_mma++;
   resultv_mma=resultv_mma+result0;
   
   if(cnt_mma>=VTG_AVG_COUNT) 
   {
   	mma_weldvoltage=resultv_mma 	>>  VTG_AVG_SHIFT;	
   	mma_weldvoltage=(mma_weldvoltage*10)/35;
   	cnt_mma=0;
   	resultv_mma=0;
   }



   if(cnt>=loop)         
    {
     resultv 		=   resultv 	>>  12;
     resulti		=   resulti 	>> 	12;
     resultt 		=   resultt 	>> 	12;
     resultsm   	=   resultsm	>>	12;
     resultsh1		=	resultsh1	>>	12;
     resultsh2		=	resultsh2	>>	12;
   
     cnt=0;
	if(iSetcurrbuff == 1200)
	{
     shfb1curr=resultsh1*10/54;
     shfb2curr=resultsh2*10/54;     
	}
	else if((iSetcurrbuff == 800)||(iSetcurrbuff == 600))
	{
     shfb1curr=resultsh1*13/100;	//10/54;
     shfb2curr=resultsh2*13/100;		//10/54;     
	}    
     resultsh1=0;
     resultsh2=0;
     
  	
	
	if(migmodeon==0)
	{                                   
		if(resultsm >= 3600)			//SAW MMA SELECTION INPUT
		{
			process_flag=MMAMODE;
		}
		else 
		{
			process_flag=SAWMODE;
		}
		resultsm = 0;
	}	
	                            //TRIP CONDITIONS
			trip_ip=resultt;
	 		resultt=0;
	
                                         //RC VOLTAGE CALCULATION
	        tempvolt=(resultv*10)/35;
	        weldvoltage=tempvolt;      //(resultv*10)/35;   // 100 VOLTS = 3500 COUNTS 4.27v
//			weldvoltage = offset;
	        resultvc=resultv;
	        resultv=0;
      
                                         //RC VOLTAGE CALCULATION
           weldcurrent=(resulti*20)/49;		///12)/37;//1200AMPS=3700 COUNTS
           //weldcurrent=resulti;
           //weldcurrent=(resulti*4.88/4.0);		///12)/37;//1200AMPS=3700 COUNTS
           resultic=resulti-(offset*49);	//20;//37)/12;
           resulti=0;
           /*if(weldcurrent >=300)
           {
	  	       OCV_FLAGLAT	=0;          		//OCV ON
	  	       TRIPLEDLAT=1;
	  	   }*/
	       	if(offsetf==0)                //OFFSET 
		   	{
				if(offsetcnt>=10)
				{
				  offset=weldcurrent;
				  offsetsh1=shfb1curr;
				  offsetsh2=shfb2curr;
				  offsetf=1;
				  
				}
	                offsetcnt++;
		   	}
		   	else
		   	{					
				if(shfb1curr>=offsetsh1)
				{
					shfb1curr=shfb1curr-offsetsh1;
					if(shfb1curr<=300.0)
						dispshfb1=shfb1curr+((300.0-shfb1curr)*0.050);
					else 
						dispshfb1=shfb1curr-((shfb1curr-300.0)*0.050);
				}
				else
				shfb1curr=0;	
					
				if(shfb2curr>=offsetsh2)
				{
					shfb2curr=shfb2curr-offsetsh2;
					if(shfb2curr<=300.0)
						dispshfb2=shfb2curr+((300.0-shfb2curr)*0.050);
					else 
						dispshfb2=shfb2curr-((shfb2curr-300.0)*0.050);	
				}
				else
				shfb2curr=0;
				
				
				
				if((weldcurrent >=offset))// && (cCaliEditfg == 1))
				{
					weldcurrent=weldcurrent-offset;
//					shfbweldcurr=shfb1curr+shfb2curr;
//					if(shfbweldcurr>=100)
//					imbal=(15*shfbweldcurr)/100;
//					else
//					imbal=60;
					
					shfbweldcurr=shfb1curr+shfb2curr;
					if(shfbweldcurr>=100)
					{
						if(shfbweldcurr>=590)
						imbal=(30.0*shfbweldcurr)/100.0;  //changed on 18062021 20%
						else if(shfbweldcurr< 590)
						imbal=(50.0*shfbweldcurr)/100.0; //1-03-2021 //30.0 //changed on 18062021 40%
						else
						imbal=100;
					}
					else if(process_flag==MMAMODE) //changed on 18062021
					{
						imbal=(50.0*shfbweldcurr)/100.0; //1-03-2021 ADDED
					}
/*					
					if(weldcurrent < 105.0)											//14-10-2021
						dispweldcurrent=weldcurrent+((600.0-weldcurrent));
					else if((weldcurrent >= 105.0) && (weldcurrent < 410.0))
						dispweldcurrent=weldcurrent+((600.0-weldcurrent));	
					else if((weldcurrent >= 410.0) && (weldcurrent < 590.0))
						dispweldcurrent=weldcurrent+((600.0-weldcurrent)*0.13);											
					else if(weldcurrent>=590.0 && weldcurrent<= 610.0)
						dispweldcurrent=weldcurrent;
					else if (weldcurrent>610.0)
						dispweldcurrent=weldcurrent-((weldcurrent-600.0)*0.01);					
*/
					if(weldcurrent < 105.0)											//13-10-2021
						dispweldcurrent=weldcurrent+((600.0-weldcurrent)*iCalicnt/100);	//0.04
					else if((weldcurrent >= 105.0) && (weldcurrent < 410.0))
						dispweldcurrent=weldcurrent+((600.0-weldcurrent)*iCalicnt/100);	//0.04
					else if((weldcurrent >= 410.0) && (weldcurrent < 590.0))
						dispweldcurrent=weldcurrent+((600.0-weldcurrent)*0.13);											
					else if(weldcurrent>=590.0 && weldcurrent<= 610.0)
						dispweldcurrent=weldcurrent;
					else if (weldcurrent>610.0)
						dispweldcurrent=weldcurrent-((weldcurrent-600.0)*0.01); //*0.01//0.165

/*
					if(weldcurrent < 75.0)                                    //390
						dispweldcurrent=weldcurrent+((600.0-weldcurrent)*0.08);					
					else if((weldcurrent >= 75.0) && (weldcurrent <= 200.0))                                    //390
						dispweldcurrent=weldcurrent+((600.0-weldcurrent)*0.1);
					else if((weldcurrent > 200.0) && (weldcurrent <= 299.0))                                    //390
						dispweldcurrent=weldcurrent+((600.0-weldcurrent)*0.1);
					else if((weldcurrent>=300.0 && weldcurrent<= 399.0))
					    dispweldcurrent=weldcurrent+((600.0-weldcurrent)*0.07);
					else if ((weldcurrent>=400.0) && (weldcurrent < 590.0))                               //610
						dispweldcurrent=weldcurrent-((weldcurrent-600.0)*0.07);
					else if ((weldcurrent >= 590.0) && (weldcurrent <= 799.0))                             //610
						dispweldcurrent=weldcurrent-((weldcurrent-600.0)*0.01);
					else if (weldcurrent >= 800.0)                               //610
						dispweldcurrent=weldcurrent-((weldcurrent-630.0)*0.001);
*/
					
					//dispweldcurrent=((weldcurrent*arcforce)/10) - DISPOFFSET;
					//dispweldcurrent=weldcurrent+arcforce;
							
				}
				else
					weldcurrent=0;	
					cCaliEditfg=0;
				
					if(dispshfb1>dispshfb2)
						curimb=abs(dispshfb1-dispshfb2);
					else if(dispshfb2>dispshfb1)
						curimb=abs(dispshfb2-dispshfb1);
         }
	
	   if(offsetf==1)		
	    {
		  	if(weldcurrent >= 10) //50)//50)
				weldon=1;        //WELDING ON
			else
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
					hotstartcount=0;
					hotf=1;
				}
			}
		}
		//##############################################################################################
		if( welding_status=='O' && calibrationf==1 && avgcntr<=16)
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
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
	IFS0bits.U1RXIF = 0;        
	uartdata=U1RXREG;
	//trans(uartdata); 
	if(U1STAbits.OERR==1)
	U1STAbits.OERR=0;
	if(U1STAbits.FERR==1)
	U1STAbits.FERR=0;
	if(U1STAbits.PERR==1)
	U1STAbits.PERR=0;
	
	if(uartdata=='$' && startrec==0)
	{
		recchksum=0;
		startrec=1;
	}    
    	else if(startrec==1)
	{
		recdata_arr[rec_cnt]=uartdata;
		if(rec_cnt<8)//7)
		{ 
			recchksum=recchksum + recdata_arr[rec_cnt]; 
		}    	
		rec_cnt++;
		if(rec_cnt==9) //8
		{    	
			rec_cnt=0;
			startrec=0;
			//recchksum=recchksum+'M';
			recchksum=recchksum;
			if(recchksum==recdata_arr[8])//7
			{
				reclower=recdata_arr[0];
				rechigher=recdata_arr[1];
				rechigher=rechigher << 8;
				hsetcurrent=rechigher|reclower;         //Set Current
				reclower=recdata_arr[2];
				rechigher=recdata_arr[3];
				rechigher=rechigher << 8;
				hsetvoltage=reclower|rechigher;         //Set Voltage
				reclower=recdata_arr[4];
				rechigher=recdata_arr[5];
				rechigher=rechigher << 8;
				recweldvtg=reclower|rechigher;          //Arc Voltage
				welding_status=recdata_arr[6];          //Welding Status ON/OFF0
				sawweldmode=recdata_arr[7]; 		  //cc weld mode / cv weldmode
				comm_count=0;
				if( welding_status=='O' && calibrationf==1 && read_hvtgf==1)
				{
					measured_hvtg=measured_hvtg+recweldvtg;
					recvtgcntr++;	
				}
			}
			else
			{																																					
				recchksum=0;
			}
		}	    
	}
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void) //FOR REMOTE DATA RECEPTION.
	{
	unsigned int intdata=0;
	IFS1bits.U2RXIF = 0; 
	uartdata1=U2RXREG;
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
	else if(startptr1==1 && startptr2==1)
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
			      if((iSetcurrbuff == 800)||(iSetcurrbuff == 600))
			      {
					//setcurrent=(intdata * 2 )/ 3;
					setcurrent = intdata*0.2037;
				    if(setcurrent<=iSetmincurrbuff)
				    	setcurrent=iSetmincurrbuff;
				    else if(setcurrent >= iSetcurrbuff)
				        setcurrent=iSetcurrbuff;					     			      
			      }
				  else if(iSetcurrbuff == 1200)
			      {
					//setcurrent=(intdata * 2 )/ 3;
					setcurrent = intdata*0.3055; 
				    if(setcurrent<=iSetmincurrbuff)
				    	setcurrent=iSetmincurrbuff;
				    else if(setcurrent >= iSetcurrbuff)
				        setcurrent=iSetcurrbuff;					     			      
			      }
			      else 
			      {
				      setcurrent=intdata;     
			      }			      
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
	else if(startptr1==1 && startptr2==2)
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
			        rsetcurrent=intdata/4.0; 
				
				  reclower1=recdata_arr1[2];
			      rechigher1=recdata_arr1[3];
			      intdata=rechigher1;
			      intdata=(intdata << 8)| reclower1;
			      rsetvoltage=140.0 +((intdata *3.0)/8.0);     
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

	}
	else if(startptr1==1 && startptr2==3)
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


/*

    
    else if(startrec1==1)
    {
	     recdata_arr1[rec_cnt1]=uartdata1;
	     if(rec_cnt1<2)
	     { 
			recchksum1=recchksum1 + recdata_arr1[rec_cnt1]; 
		 }    	
	     rec_cnt1++;
	     if(rec_cnt1==3)
	     {    	
		      rec_cnt1=0;
		      startrec1=0;
              	recchksum1=recchksum1+'M';
		      if(recchksum1==recdata_arr1[2])
		      {
			      reclower1=recdata_arr1[0];
			      rechigher1=recdata_arr1[1];
			      intdata=rechigher1;
			      intdata=(intdata << 8)| reclower1;
			      setcurrent=intdata;     
			      remotecnt=0;
			      remoteonf=1;
			 }
			 else
			 {
			     	recchksum=0;
			 }
	     }	    
    }
}*/