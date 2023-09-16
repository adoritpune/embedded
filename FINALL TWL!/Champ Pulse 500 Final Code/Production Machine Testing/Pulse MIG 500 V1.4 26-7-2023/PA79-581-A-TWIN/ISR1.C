void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF=0;                            //1 MSEC
    count_1ms++;    
  	count_20ms++;	
	count_200ms++;
	count_500ms++;
	count_500ms1++;
	count_1sec++;
	{
		if(cyclestrt==1)
			count_100ms++;
    	else
    		count_100ms=0;
 	}   
    if(count_1ms>=2)
    {
        //if(torch!='T')
		{
			display_data();                        //DISPLAY UPDATE AFTER 2MSEC
		}
		count_1ms=0;  
	}
	if(count_20ms>=20)
	{
		count_20ms=0;
		if(torch!='T')
		{
			keyreadf=1;
		}		
	}
	if(count_200ms>=100)//200)
	{
		count_200ms=0;
		READ_PORTPIN();
	}
	if(count_500ms>=10) //50  10 ms interval
	{
		count_500ms=0;
		//count_500ms2++;
		if(torch=='T')
		{
			//if(frepidf==0)
			{
				Adaptive_freq_pid();
				//frepidf=1;
			}
			//else if(frepidf==1)
			//{
			   //Adaptive_base_pid();
			//	frepidf=0;
			//}	
		}
	} 
	
	/* disabled motor pulse feedback routine when seperate wirefeeder added.
	if(count_500ms1>=100 ) //100
	{
		count_500ms1=0;
		if(torch=='T')
		{
			second_order_pid();			//For Pulse motor
		}
	} 
	*/
	if(count_1sec>=1000)
	{
		count_1sec=0;
		transmit2f=1;
		//TRANS2('A');
	}
	
} 
/************************************************************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
   IFS0bits.T2IF=0;     
}

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)  //interrupt at 100usec
{
	IFS2bits.INT3IF=0;
	IEC2bits.INT3IE=0;				//DISABLE INTERRUPT
} 

/*void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void)  //interrupt at 10usec
{
	IFS1bits.T5IF=0;
	
	if(weldcycleon==1)
	{
	    ARCONOKIO=0;//   		TRISFbits.TRISF7 	//TRISDbits.TRISD4 	//For direction
		if(togglepin==0)
		{
			ARCONOKLAT=1;
			togglepin=1;
		}
		else if(togglepin==1)
		{
			togglepin=0;
			ARCONOKLAT=0;
		}
	    microsec++;
	    if(microsec>400)
	    microsec=0;
	    //upcnt=(unsigned int)microsec*10;
	    micromulti=microsec*10.0;  
	    micromulti=micromulti*1.0;
	    micromulti=micromulti*1.0;  
	    if(SPI2STATbits.SPITBF==0)
		{
			DACCSLAT=0;
			SPI2BUF=28672+micromulti;//DACREF;//1300;//102A 600
	  	}
 } 	
  
}
*/

void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void)  //interrupt at 10usec
{
	//enum {pulserise,pulseon,pulsedecay,stepon,stepdecay,baseon}pulsecycle;
	IFS1bits.T5IF=0;
	//if(cyclestrt==1)
	
	
	
	if(weldcycleon==1)
	{
		/*
		peakamp		=400.0;
		stepamp		=20.0;//100.0;
		baseamp		=10.0;//50.0;
		
		pulsetm		=120.0;
		steptm		=50.0;
		basetm		=400.0;
		
		pulserisetm	=30.0;
		pulsedecaytm=50.0;
		stepdecaytm	=10.0;
		
		pdaccount	=310.0+(peakamp*7.22);
		sdaccount	=310.0+(stepamp*7.22);
		bdaccount	=310.0+(baseamp*7.22);
		*/
		//MAHESH=pdaccount;
		//pulsecycle	=pulseriseop;	
	    
	    cout_100us++;
		switch(pulsecycle)
		{
			case pulseriseop:
			{	
				if(microsec <= pulserisetm)
				{
					//upcnt   =400 + (100*microsec);	//+bdacount;		//(baseamp+(upstep*microsec));
					upcnt   =bdaccount + (upstep*microsec);	//+bdacount;		//(baseamp+(upstep*microsec));
					//upcnt   =upcnt+upstep;//bdaccount + (upstep*microsec);	//+bdacount;		//(baseamp+(upstep*microsec));
					MAHESH	=upcnt;							//310.0+(upcnt*7.22);
					microsec++;
					
					/*ARCONOKIO=0;//   		TRISFbits.TRISF7 	//TRISDbits.TRISD4 	//For direction
    				if(togglepin==0)
    				{
	    				ARCONOKLAT=1;
    					togglepin=1;
    				}
    				else if(togglepin==1)
    				{
	    				togglepin=0;
	   					ARCONOKLAT=0;
    				}*/
    			}
				else
				{
					cout_100us	=0;
					microsec	=0;
					upcnt		=bdaccount;
					pulsecycle	=startpulseop;//pulseonop;
					MAHESH		=uppdaccount;
				}
				if(SPI2STATbits.SPITBF==0)
				{
					DACCSLAT=0;
					SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
				}
				break;
			}
			case startpulseop:
			{
				if(microsec < startpulsetm)
				{
					MAHESH	=uppdaccount;
					pulsecycle=pulseonop;
					microsec++;
				}
				else
				{
					cout_100us	=0;
					microsec	=0;
					pulsecycle	=pdaccount;//steponop;//pulsedecayop;
					MAHESH		=pulseonop;//sdaccount;
				}
				if(SPI2STATbits.SPITBF==0)
  				{
					DACCSLAT=0;
  					SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
  				}
				break;
			
			
			}
			case pulseonop:
			{	
				if(microsec < pulsetm)
				{
					MAHESH	=pdaccount;
					pulsecycle=pulseonop;
					microsec++;
				}
				else
				{
					cout_100us	=0;
					microsec	=0;
					pulsecycle	=steponop;//pulsedecayop;
					MAHESH		=sdaccount;
				}
				if(SPI2STATbits.SPITBF==0)
  				{
					DACCSLAT=0;
  					SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
  				}
				break;	
			}
			case pulsedecayop:
			{	
				if(microsec < pulsedecaytm)
				{
					mslope		= (pdaccount-sdaccount)/pulsedecaytm;
					linearcnt 	=  pdaccount-(mslope*microsec);
					//mkf			=  microsec;
					tempval		= (1.0+(0.50*microsec));//microsec))
					decayslope	= 1.0/tempval;
					
					//decayslope  =1.0/(1.0+(0.2*microsec));
					decaycnt	=linearcnt*decayslope;
					if(decaycnt<=sdaccount)
						decaycnt=sdaccount;
					decaycount	=decaycnt;//310.0+(decaycnt*7.22);//add actual formula.
					MAHESH		=decaycount;		   //1/(1+ax)
					microsec++;
				}
				else
				{
					cout_100us	=0;
					microsec	=0;
					pulsecycle	=steponop;
					MAHESH		=sdaccount;
				}
		  		if(SPI2STATbits.SPITBF==0)
		  		{
					DACCSLAT=0;
					SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
		  		}
				break;
			}
			case steponop:
			{	
				if(microsec < steptm)
				{
					MAHESH		=sdaccount;						//1/(1+ax)
					microsec++;
				}
				else
				{
					cout_100us	=0;
					microsec	=0;
					pulsecycle	=baseonop;//stepdecayop;
					MAHESH		=bdaccount;
				}
				
		  		if(SPI2STATbits.SPITBF==0)
		  		{
					DACCSLAT=0;
					SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
		  		}
				break;
			}
			case stepdecayop:
			{	
				if(microsec < stepdecaytm)
				{
					mslope		=(stepamp-baseamp)/stepdecaytm;
					linearcnt 	=stepamp-(mslope*cout_100us);
					decayslope  =1.0/(1.0 + (0.5*microsec));
					decaycnt	=linearcnt*decayslope;
					if(decaycnt<=baseamp)
					decaycnt=baseamp;
					decaycount	=310.0+(decaycnt*7.22);//add actual formula.
					MAHESH		=decaycount;		   //1/(1+ax)
					microsec++;
				}
				else
				{
					cout_100us	=0;
					microsec	=0;
					pulsecycle	=baseonop;
					MAHESH		=bdaccount;
				}
				if(SPI2STATbits.SPITBF==0)
  				{
					DACCSLAT=0;
					SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
  				}
				break;
			}
			case baseonop:
			{	
				if(microsec < basetm)
				{
					MAHESH	=bdaccount;						//1/(1+ax)
					microsec++;
				}
				else
				{
					cout_100us	=0;
					microsec	=0;
					pulsecycle	=pulseriseop;
					MAHESH		=bdaccount;
				}
				if(SPI2STATbits.SPITBF==0)
  				{
					DACCSLAT=0;
					SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
  				}
				break;
			}
		}
		//DACCSLAT=0;
  		//if(SPI2STATbits.SPITBF==0)
  		//{
		//	SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
  		//}	
	}
}
////void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void)  //interrupt at 100usec
//{
//	IFS1bits.T5IF=0;
//	/*if(cyclestrt==1 && pweldonf==0)
//	{
//		//DACCSLAT=0;
//		//if(SPI2STATbits.SPITBF==0)
//		//{
//		//	SPI2BUF=28672+bdaccount;     //850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
//		//}
//		DACREF=bdaccount;//pdaccount
//	}*/
//	if(cyclestrt==1)
//	//else if(cyclestrt==1 && pweldonf==1)	
//	{
//		if((cout_100us>=(pulsebase+pulsepeak)) && peakf==1)
//		{
//			if(mpeak1f==1)
//			{
//				mpeak1f=0;
//				mpeak2f=1;
//			}
//			if(ptosslope < 150) //10.0 MODIFIED TO 5 MS 25.02.2016
//			{
//				/*DACCSLAT=0;
//				//if(SPI2STATbits.SPITBF==0)
//				{
//					SPI2BUF=28672+ (middaccount- (downstep* ptosslope));//((middaccount-bdaccount)*ptosslope/50.0));//3800;// 3800=500, 3200=400A 2650;//Refpeakcnt;//2650;
//				}
//				*/
//				//DACREF=(middaccount- (downstep* ptosslope));//((middaccount-bdaccount)*ptosslope/50.0));//3800;// 3800=500, 3200=400A 2650;//Refpeakcnt;//2650;
//				decaycurrent=Decay_lookup[ptosslope];
//				decaycurrent=310+(decaycurrent+setbaseamp);
//				if(decaycurrent>=pdaccount)
//				decaycurrent=pdaccount;
//				DACREF=decaycurrent;//310.0+(decaycurrent*7.22);
//				peakf=1;
//				stepf=0;	
//				basef=0;
//				ptosslope++;
//			}
//			else
//			{
//				/*DACCSLAT=0;
//				//if(SPI2STATbits.SPITBF==0)
//				{
//					SPI2BUF=28672+bdaccount;     //850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
//				}*/
//				basecurcnt=bdaccount;	
//				
//				//if(CURRENT<100)
//					addonbase=addonbase1;//basecurcnt;//
//				//else
//				//	addonbase=basecurcnt;//
//				
//				DACREF=basecurcnt;//bdaccount;
//				pulsebase=basetime;				
//				mbase1f=1;
//				mbase2f=0;
//				baseonf=1;
//				cout_100us=0;
//				peakf=0;
//				stepf=0;	
//				basef=0;
//				ptosslope=0;
//				loopcount=0;
//				loopinterval=0;
//				
//			}
//		}
//		else if((cout_100us<pulsebase) && peakf==0)//ripplecount
//		{
//			loopcount++;
//			if(loopcount>=50)
//			{
//				loopcount=0;
//				loopinterval++;
//				if(loopinterval<(baseunit-2))//baseunit=newpulsebase/50;
//				{
//					if(baseonf==1)
//					{
//						DACREF=basecurcnt;//bdaccount;
//						baseonf=0;
//						mbase1f=1;
//					}
//					else
//					{
//						DACREF=addonbase;
//						baseonf=1;
//						mbase1f=0;
//					}
//				}
//				else
//				{
//					DACREF=basecurcnt;//bdaccount;
//					mbase1f=1;
//					//loopinterval=0;
//				
//				}
//				
//			}
//		}
//		else if((cout_100us>=pulsebase) && peakf==0)
//		{
//			if(mbase1f==1)
//			{
//				mbase1f=0;
//				mbase2f=1;
//				//basevtgcnt++;
//			}	
//			
//			if(ptosslope<30)			
//			{
//				/*DACCSLAT=0;
//				//if(SPI2STATbits.SPITBF==0)
//				{
//					SPI2BUF=28672+ (bdaccount+(upstep*ptosslope));//((pdaccount-bdaccount)*ptosslope)/50.0);//1300;//102A 600
//				}*/
//				DACREF	=(basecurcnt+(upstep*ptosslope));// (bdaccount+(upstep*ptosslope));
//				peakf	=0;
//				stepf	=0;	
//				basef	=0;
//				ptosslope++;
//			}
//			else
//			{
//				/*DACCSLAT=0;
//				//if(SPI2STATbits.SPITBF==0)
//				{
//					SPI2BUF=28672+pdaccount;//1300;//102A 600
//				}*/
//				DACREF=pdaccount;
//				peakf=1;
//				stepf=0;	
//				basef=0;
//				ptosslope=0;
//				mpeak1f=1;
//				//mpeak2f=0;
//			}
//			//stobslope=0;
//		}
//		cout_100us++;
//	}
//}
/************************************************************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)          //FOR ENCODER SCANNING
{
  IFS1bits.T4IF=0;  
  count4_1ms++;
  
  /*DACCSLAT=0;
  if(SPI2STATbits.SPITBF==0)
  {
		SPI2BUF=28672+MAHESH;//DACREF;//1300;//102A 600
  }*/
  /*
  if(count4_1ms>=100)
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
  }	*/
}
/************************************************************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
	static unsigned long resultcur=0, resultvtg=0, resultmvtg=0, resulttripvtg=0,bresultvtg=0,mbasevtg=0,presultvtg=0,mpeakvtg=0;
	unsigned int result1=0, result2=0, result3=0, result4=0;
	static unsigned int adccur=0,adcvtg=0,adcmvtg=0,adctripvtg=0,loopcnt=0,bvoltcnt=0,pvoltcnt=0;
	ADCON1bits.ASAM = 0;
	IFS0bits.ADIF = 0; 
	
	result1 		= (ADCBUF0);//+ADCBUF4+ADCBUF8+ADCBUFC) >>2;
	result2 		= (ADCBUF1);//+ADCBUF5+ADCBUF9+ADCBUFD) >>2;
	result3 		= (ADCBUF2);//+ADCBUF6+ADCBUFA+ADCBUFE) >>2;
	result4 		= (ADCBUF3);//+ADCBUF7+ADCBUFB+ADCBUFF) >>2;
	;   
	resultcur		=	resultcur	+	result1;                       //arc Current
	resultvtg		=	resultvtg	+	result2;                      	//arc voltage
	resultmvtg		=	resultmvtg	+	result3;                      	//feed motor voltage
	resulttripvtg	=	resulttripvtg	+	result4;                   	//Trip voltage
	
		
	{	
		if(mbase1f==1 && mbase2f==0)
		{
			bresultvtg	=	bresultvtg	+ result2;
			bvoltcnt++;
		}
		else if(mbase1f==0 && mbase2f==1)
		{
			//if(basevtgcnt>=10)
			if(count_100ms>=20)//10)
			{
				mbasevtg	=bresultvtg/bvoltcnt;
				BVOLTAGE	=(mbasevtg *10.0)/40.0;//37.0
				bresultvtg	=0;
				bvoltcnt	=0;
				count_100ms	=0;
				//basevtgcnt	=0;	
			}
			mbase1f=0;
			mbase2f=0;
		}
	}
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	{
		if(mpeak1f==1 && mpeak2f==0)
		{
			presultvtg	=	presultvtg	+ result2;
			pvoltcnt++;
		}
		else if(mpeak1f==0 && mpeak2f==1)
		{
			//if(count_100ms>=100)
			{
				mpeakvtg	=presultvtg/pvoltcnt;
				peakvtg 	=(mpeakvtg *10.0)/40.0;//37.0 answer 100v=1000;
				totalpeakvtg=totalpeakvtg+peakvtg;
				presultvtg	=0;
				pvoltcnt	=0;
				peakvtgcnt++;
				if(peakvtgcnt>=2)
				{
					PVOLTAGE=totalpeakvtg>>1;
					totalpeakvtg=0;
					peakvtg=0;
					peakvtgcnt=0;
				}
			}
			mpeak1f=0;
			mpeak2f=0;
		}
	}
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	
	presultcur		=	presultcur	+	result1;
	ploopcnt++;
	if(ploopcnt>=64)//16)//8)
	{
		padccur		=	presultcur	>> 	6;//4;//3;
		PCURRENT	=	(padccur * 5.0)/37.0;
		ploopcnt=0;
		presultcur=0;
		
		if(PCURRENT>=10)
		{
			pweldonf=1;
		}
		else
		{
			pweldonf=0;
		}	
	}
	
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	loopcnt++; 
	if(loopcnt>=AVGCNT)
	{
		adccur		=	resultcur	>> 	LEFTSHIFT;
		adcvtg		=	resultvtg	>>	LEFTSHIFT;
		adcmvtg	=	resultmvtg	>>	LEFTSHIFT;
		adctripvtg	=	resulttripvtg	>>	LEFTSHIFT;
		//if(setoffsetf==0 && offsetcount<=10)
		//{
		//	curoffset
		//}
		//else if(setoffsetf==1)
		{
			CURRENT	=	(adccur * 5.0)/37.0;
			VOLTAGE	=	(adcvtg *10.0)/40.0;//37.0
			MVOLTAGE=	(adcmvtg *5.0)/37.0;
			TRIPVTG	=	(adctripvtg *10.0)/37.0;
			
			transoff.Lo_actualcurrent=CURRENT;
			transoff.Hi_actualcurrent=CURRENT >> 8;
			
			transoff.Lo_actualvoltage=VOLTAGE;
			transoff.Hi_actualvoltage=VOLTAGE >> 8;
			
		}
		loopcnt		=	0;
		resultcur	=	0;
		resultvtg	=	0;
		resultmvtg	=	0;
		resulttripvtg	=	0;
		{
			if(CURRENT>=20)
			{
				weldonf=1;
			}
			else 
			{
				weldonf=0;
				if(weldingdone==1)
				dispupdatef=1;
			}
		}
	}
	ADCON1bits.ASAM = 1;
}

void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void)
{
	IFS1bits.SPI2IF=0;
	DACCSLAT=1;
	if(SPI2STATbits.SPIROV==1)
	SPI2STATbits.SPIROV=0;
}
//================================================================================================
void __attribute__((interrupt, no_auto_psv)) _IC1Interrupt(void)
{
    static unsigned long summperiod=0;
	static unsigned int mperiodcnt=0, avgmperiod=0;
	IFS0bits.IC1IF = 0;
    //CloseCapture3(); 
    //IC3CONbits.ICM = 0; /* Input Capture x(ic_no) Off */
    ReadCapture1(&timer_first_edge);
    ReadCapture1(&timer_second_edge);
    mperiod = timer_second_edge -  timer_first_edge;
      
	summperiod=summperiod + mperiod;
	mperiodcnt++;
	if(mperiodcnt>=16)
	{
		avgmperiod=summperiod>>4;
		mperiodcnt=0;
		summperiod=0;
		if(Prev_mperiod != mperiod)
		{
			mfreq=(1000000.0/(mperiod*2.16));// 1cap
			Prev_mperiod = mperiod;
			//second_order_pid();
			//TRANS1('@');
		    //TRANSNUM(mfreq);
	        //transmit_dec(mfreq);
		  	//trans(0x0D);
		   	//trans(0x0A);
		}
		//second_order_pid();
	}
	if(pweldonf==1 && softstartf==0)
	{
		//OC2RS=para.migmode.setwspeed*10.0;			//100%=64V=2949  60%=38V=1769 
		softstartcnt++;
		if(softstartcnt >=5)
		{
			softstartf=1;// open loop;
			//TRANS1('S');
		}
	}
}

void __attribute__((interrupt, no_auto_psv))_U1RXInterrupt(void)
{
	IFS0bits.U1RXIF = 0; // clear rX interrupt flag
	uartdata1 		= U1RXREG; //
}

void __attribute__((interrupt, no_auto_psv))_U2RXInterrupt(void)
{
	IFS1bits.U2RXIF = 0; // clear rX interrupt flag
	uartdata2		= U2RXREG; //
	//TRANS2(uartdata2);
	{
            if(uartdata2=='@' && startptr1==0 && transonf==0)
            {    
                startptr1=1;
                arrptr=0;
                recchksum=0;
                //TRANS1('@');
	
            }
            else if(startptr1==1 && transonf==0)
            {    
                if(arrptr<=20)
                {    
                    rec_arr[arrptr]=uartdata2;
                    //TRANS1(uartdata2);
	
                    recchksum=recchksum+uartdata2;
                    arrptr++;
                }
                else if(recchksum==uartdata2)
                {
                   
                    for(iii=2;iii<=8;iii++) //20
                    {    
                        transoffu.transarr[iii]=rec_arr[iii]; 
                    }
                    transoffu.transarr[19]=rec_arr[19];		//weldmode status
                	transoffu.transarr[20]=rec_arr[20];		//status byte
                    
                    if(transoff.weldmode=='G')
                    {					//1
			        	para.migmode.setwspeed=transoff.Hi_setwspeed;
                    	para.migmode.setwspeed<<=8;
                   		para.migmode.setwspeed|=transoff.Lo_setwspeed;

                    	para.migmode.setvoltage=transoff.Hi_setvoltage;
                    	para.migmode.setvoltage<<=8;
                    	para.migmode.setvoltage|=transoff.Lo_setvoltage;
					}
					else if(transoff.weldmode=='P')
                    {					//1
			        	para.pmigmode.setwspeed=transoff.Hi_setwspeed;
                    	para.pmigmode.setwspeed<<=8;
                   		para.pmigmode.setwspeed|=transoff.Lo_setwspeed;

                    	para.pmigmode.setvoltage=transoff.Hi_setvoltage;
                    	para.pmigmode.setvoltage<<=8;
                    	para.pmigmode.setvoltage|=transoff.Lo_setvoltage;
					}
					
					
                    statusu.statusbyte[0]=transoff.statusbyte;
                    
                    //TRANS1('A');
                    //TRANS1(transoff.statusbyte);
                    //TRANS1(statusu.statusbyte[0]);
                    if(status.torchon==1)
                    {
	                   torch='T';
	                  // TRANS1('T'); 
                    }
                    else
                    {
	                    torch='X';
	                   // TRANS1('X');
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
                }
            }   
            else if(transonf==1)
            {
	        	    startptr1=0;
                    arrptr=0;
                    recchksum=0;
                
	            
	        } 
        }

}