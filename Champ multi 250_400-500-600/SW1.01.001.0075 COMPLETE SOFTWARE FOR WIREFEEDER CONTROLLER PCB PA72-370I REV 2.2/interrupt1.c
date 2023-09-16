void __attribute__((interrupt, no_auto_psv)) _INT3Interrupt(void)
{
	IFS2bits.INT3IF=0;
	IEC2bits.INT3IE=0;				//DISABLE INTERRUPT
} 
//***********************************************************
//void _ISR _T1Interrupt(void)
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
	IFS0bits.T1IF=0;
	msec++;
	mlsec++;
	if(msec==1)
	{
		encoderscan=1;
		msec=0;
		//**************
		count_1ms++;
		if(count_1ms == 10)			//10 msec delay
		{
			read_torchsw();
			//encoderscan=1;
			count_1ms=0;
			count_10ms++;
			if(strtinchcntr==1)
			{
				inchcounter++;		//autoinching off10 msec delay    
			}
			if(strtmtrovldcntrf==1)
			{
				if(inrushf==0)
				{
					inrushcounter++;		//autoinching off10 msec delay    
					if(inrushcounter>=200)
					inrushf=1;
				}
				else
				{
					MOTOROVLDIO =1;	
					if(MOTOROVLD==0)
					{
						movldcounter++;
						if(movldcounter>=100)
						Motorerrf=1;
					}	
					else
						movldcounter=0;
				}
			}
		}
		if(count_10ms ==10)			//100 msec delay
		{
			count_1ms=0;
			count_10ms=0;
			keyscan=1;
			count_100ms++;
		}
		if(count_100ms==10)			//1 SEC DELAY
		{
			count_1ms=0;
			count_10ms=0;
			count_100ms=0;
			thscan=1;				//thermal switch scan
			sendtoremotef=1;
			Read_SWf=1;
			count_1sec++;
			if(arcon==1)
			{
				arconsec++;
				if(arconsec>=60)
				{
					arconsec=0;
					arconmin++;
				}
				if(arconmin>=60)
				{
					arconmin=0;
					arconsec=0;
					arconhr++;
				}
				if(arconhr>=999)
				{
					arconmin=0;
					arconsec=0;
   					arconhr=0;
				}
			}
		}
		//******************
		if(strttmr==1)			//during only preflow and postflow, burnback time only
		{
			timerval++;
			if(timerval == 100)
			{
				cntsecond++;
				timerval=0;
			}
		}	
		if(maheshkp==0)
		{
			diswin1[0]=win1[0];
			diswin1[1]=win1[1];
			diswin1[2]=win1[2];
			diswin2[0]=win2[0];
			diswin2[1]=win2[1];
			diswin2[2]=win2[2];
		}
		display_data();
	}
	/*if(mlsec==1)
	{
		mlsec=0;
		if(maheshkp==0)
		{
			diswin1[0]=win1[0];
			diswin1[1]=win1[1];
			diswin1[2]=win1[2];
			diswin2[0]=win2[0];
			diswin2[1]=win2[1];
			diswin2[2]=win2[2];
		}
		display_data();
    }*/

	}
//***************************************************
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
	static unsigned long totalfbvtg=0L,totalshuntvtg=0L,totalmotorvtg=0,totalerrorvtg=0;//totalvmulti=0,totalcmulti=0,totalwsmulti=0;
    static unsigned int msrfbvtg=loop,msrmotorvtg=loopm;
	static unsigned int cntloop=update,cntloopm=updatem;
	static unsigned int loopfbvtg=0,loopfbcur=0,loopmotorvtg=0,looperrorvtg=0;//,loopvmulti=0,loopcmulti=0,loopwsmulti=0;
	unsigned int weld_adc_status,shunt_adc_status,wire_adc_status,error_adc_status;//,vmulti,cmulti,wsmulti;
	ADCON1bits.ASAM = 0; 			// stop sampling
	ADCValue = 0; 					// clear value
	IFS0bits.ADIF = 0; 				// clear ADC interrupt flag
	weld_adc_status 	= 	(ADCBUF0 + ADCBUF4 + ADCBUF8 + ADCBUFC)/4;
	wire_adc_status 	=	(ADCBUF1 + ADCBUF5 + ADCBUF9 + ADCBUFD)/4;
	shunt_adc_status 	= 	(ADCBUF2 + ADCBUF6 + ADCBUFA + ADCBUFE)/4;
	error_adc_status	=	(ADCBUF3 + ADCBUF7 + ADCBUFB + ADCBUFF)/4;

	totalfbvtg	 =totalfbvtg 	+ weld_adc_status;
	totalshuntvtg=totalshuntvtg + shunt_adc_status;
	totalmotorvtg=totalmotorvtg + wire_adc_status;
      totalerrorvtg =totalerrorvtg  + error_adc_status;
      
	msrmotorvtg=msrmotorvtg -1;
	if(msrmotorvtg==0)
	{	
		loopmotorvtg=totalmotorvtg/loopm;
		msrmotorvtg=loopm;
		totalmotorvtg=0;
	}
	cntloopm=cntloopm-1;
	if(cntloopm==0)
	{
		float temp=0;
		cntloopm=updatem;
		temp=loopmotorvtg;
		temp=temp/88.0;//55.0;//53.0;//46.0;
		fbmvtg=temp -(temp*0.06);
		mvtgmesrf=1;				//display motor vtg mesured.
	}	
//##############################
	msrfbvtg=msrfbvtg -1;
	if(msrfbvtg==0)
	{
		loopfbvtg=totalfbvtg/loop;
		loopfbcur=totalshuntvtg/loop;
		//looperrorvtg=totalerrorvtg/loop;
		tripvtg=totalerrorvtg/loop;
		;
		totalfbvtg		=0;
		totalshuntvtg	=0;
		totalerrorvtg	=0;
		msrfbvtg		=loop;
		
		
		if(setoffset==1)				//auto offset calculation
		{
			if(loopfbcur <= curoffset)
			{
				loopfbcur=curoffset;
			}	
			loopfbcur=loopfbcur-curoffset;
		}
		if(weldingstart==0 && loopfbcur > 50 && setoffset==1)//20
		{
			weldingstart=1;
			if(Type.mig==0 || Type.fcaw==0 )
			{	arcon=1;
			}
		}
		else if(weldingstart==1 && loopfbcur < 50 && setoffset==1) //20						//welding stop
		{
			weldingstart=0;
			arcon=0;
			if(Type.mma==0 || Type.tig==0)
			{
				writemematstop();
			}
		}
		if(loopfbcur>50) //30
		{
			inchcounter=0;		//reset autoinch counter to zero if current is detected		
		}
		{
			totaltripvtg=totaltripvtg+tripvtg;
			tripcount++;
			if(tripcount>=4)
			{
				looperrorvtg=totaltripvtg>>2;
				totaltripvtg=0;
				tripcount=0;
			
				if((looperrorvtg>=650) && (looperrorvtg<=980))
				{
					UV_errorf=1;
					OV_errorf=0;
					TH_errorf=0;
					HS_errorf=0;
					Errorf=1;
				}
				else if((looperrorvtg>=1475) && (looperrorvtg<=1800))
				{
					UV_errorf=0;
					OV_errorf=1;
					TH_errorf=0;
					HS_errorf=0;
					Errorf=1;
				}
			      else if((looperrorvtg>=2290) && (looperrorvtg<=2620))
				{
					UV_errorf=0;
					OV_errorf=0;
					TH_errorf=1;
					HS_errorf=0;
					Errorf=1;
				}
				else if((Type.mig==0 || Type.fcaw==0) && (cyclestrt==0) && (loopfbcur >=1600))
				{
					UV_errorf=0;
					OV_errorf=0;
					TH_errorf=0;
					HS_errorf=1;
					Errorf=1;		
				}
				else
				{
					UV_errorf=0;
					OV_errorf=0;
					TH_errorf=0;
					HS_errorf=0;
					Errorf=0;
				}
			} //avg of 4
		}
	}
	cntloop=cntloop-1;
	if(cntloop==0)
	{
		float temp=0;
		cntloop=update;
		temp=loopfbvtg;
		fbvtg=temp/37.0;//36.0;//46;				//display feedeback voltage
		temp=loopfbcur;
		fbcurr=temp/Currentfactor;//6.13;//9.20;//7.37;//8.6   previous 4.2v=8.6 now 3.6=7.37	//display feedback current 
		{
			/*if(fbcurr<5.0)
			{
				fbcurr=0.0;
			}
			else if(fbcurr <=300.0)
			{
				fbcurr=fbcurr+((300.0 - fbcurr)*0.03);
			}*/

			if(fbcurr<5.0)
			{
				fbcurr=0.0;
			}
			else if(fbcurr <=190.0)
			{
				fbcurr=fbcurr+((200.0 - fbcurr)*0.03);//0.06);
			}
			else if(fbcurr >=210.0)
			{
				fbcurr=fbcurr-((fbcurr- 200.0)*0.02);//0.06);
			}
		}
		if(setoffset==0)
		{
			offsetcnt++;
			if(offsetcnt >= 5)
			{
				if((Type.mma==0 || Type.tig==0) )//&& (weldstart==0)) //(weldingstart==0))
				{
					curoffset=loopfbcur;
					vtgoffset=loopfbvtg;
				}
				else if((Type.mig==0 || Type.fcaw==0) && (cyclestrt==0) && (HS_errorf==0))
				{
					curoffset=loopfbcur;
					vtgoffset=loopfbvtg;
				}
				else
				{
					curoffset=0;
					vtgoffset=0;
				}
				offsetcnt=0;
				setoffset=1;
			}
		}
	//	if(setoffset==0)
	//	{
	//		curoffset=loopfbcur;
	//		vtgoffset=loopfbvtg;
	//		setoffset=1;
	//	}
		
		dispfbvtg=fbvtg;
		dispfbcurr=fbcurr;
		updatedisp=1;
	}
   	ADCON1bits.ASAM = 1; 		//auto start sampling	
}

//****************************************************
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
	IFS0bits.T2IF=0;
}
//****************************************************

unsigned char check_window(float voltage,float previousvtg)
{
	if(voltage==previousvtg)
	{
		return ('Y');
	}
	else
	{
		if(voltage > previousvtg)
		{
			if((voltage - previousvtg) <= window)
			{
				return('Y');
			}		
			else
			{
				return('N');
			}
		}
		else
		{
			if((previousvtg - voltage) <= window)
			{
				return('Y');
			}		
			else
			{
				return('N');
			}

		}
	}
}

/*
void __attribute__((interrupt, no_auto_psv))_LVDInterrupt(void)
{
	IFS2bits.LVDIF=0;
	IEC2bits.LVDIE=0;
	for(i=0;i<32;i++)
	{
		EE_Addr=(i*2);
		EE_Data=parau.arrayu[i];
		EEPROM_Erase_Write(EE_Addr,EE_Data);
	}
	//writemematstop();
	trans('L');
	trans('O');
	trans('W');
}
*/
void __attribute__((interrupt, no_auto_psv))_U1RXInterrupt(void)
{
	IFS0bits.U1RXIF = 0; // clear rX interrupt flag
	uartdata = U1RXREG; //
	//trans(uartdata);
	if(uartdata=='$' && recstrtptr==0 && receivef==0 && passprotect==0x0000)
   {
      reccnt=0;
      receivef=0;
      recstrtptr=1;
	  recchksum=0x00;
	  count_1ms=0;
	  count_10ms=0;
	  count_100ms=0;
	  sendtoremotef=0;
   }
   else if(recstrtptr==1)
   {
      rec_arr[reccnt]=uartdata;
	  if(reccnt<4)
	  {
		recchksum=recchksum + uartdata;
 	  }    	
	  reccnt++;
      if(reccnt==5)//4)
      {
        reccnt=0;
        recstrtptr=0;
		if(recchksum==rec_arr[4])
		{
			reclower=rec_arr[0];
	 		rechigher=rec_arr[1];
	 		recremotevtg=(reclower | (rechigher <<8));
			
			reclower=rec_arr[2];
	 		rechigher=rec_arr[3];
	 		recremotews=(reclower | (rechigher <<8));
			
			if(Type.mma==0 && Type.mig==1 && Type.tig==1 && Type.fcaw==1)	// cc mode
			{	
				para.weldcurrent=recremotews;	
			}
			else if(Type.mma==1 && Type.mig==0 && Type.tig==1 && Type.fcaw==1)	// cv mode
			{
		 		para.weld.volts=recremotevtg;
		 		para.weld.wfs=recremotews;
			} 
			else if(Type.mma==1 && Type.mig==1  && Type.fcaw==0 && Type.tig==1)	// cv mode
			{
		 		para.fcaw.volts=recremotevtg;
		 		para.fcaw.wfs=recremotews;
			} 
			else if(Type.mma==1 && Type.mig==1 && Type.tig==0 && Type.fcaw==1 )//&& (mc_model!='A' || mc_model!='B'))	// tig mode
			{	
				para.weldcurrent=recremotews;	
			}
			
			/*else if(Type.mma==1 && Type.mig==1 && Type.tig==0 && (mc_model=='A' || mc_model=='B'))	// tig mode
			{	
				para.weld.volts=recremotevtg;
		 		para.weld.wfs=recremotews;
				//para.weldcurrent=recremotews;	
			}
			else if(Type.mma==1 && Type.mig==1 && Type.tig==0 && (mc_model!='A' || mc_model!='B'))	// tig mode
			{	
				para.weldcurrent=recremotews;	
			}*/
         		receivef=1;
		 	transon=1;
			count_1ms=0;
			count_10ms=0;
			count_100ms=0;
			sendtoremotef=0;
			//prevrecremotevtg=recremotevtg;
			//prevrecremotews=recremotews;
			//IEC0bits.U1RXIE=0; //Uart reception interrupt enable	38400 baud rate
		}
		else
		{
			recchksum=0;
	 	}   
      }
   }
}
