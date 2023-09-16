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
        display_data();                        //DISPLAY UPDATE AFTER 2MSEC
		count_1ms=0;  
	}
	if(count_20ms>=20)
	{
		count_20ms=0;
		keyreadf=1;
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
			Adaptive_freq_pid();
			Adaptive_base_pid();
		}
	} 
	
	if(count_500ms1>=100 ) //100
	{
		count_500ms1=0;
		if(torch=='T')
		{
			second_order_pid();			//For Pulse motor
		}
	} 
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

void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void)  //interrupt at 100usec
{
	IFS1bits.T5IF=0;
	if(cyclestrt==1 && pweldonf==0)
	{
		//DACCSLAT=0;
		//if(SPI2STATbits.SPITBF==0)
		//{
		//	SPI2BUF=28672+bdaccount;     //850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
		//}
		DACREF=bdaccount;//pdaccount
	}
	//if(cyclestrt==1)
	else if(cyclestrt==1 && pweldonf==1)	
	{
		if((cout_100us>=(pulsebase+pulsepeak)) && peakf==1)
		{
			if(mpeak1f==1)
			{
				mpeak1f=0;
				mpeak2f=1;
			}
					
			if(ptosslope < 150) //10.0 MODIFIED TO 5 MS 25.02.2016
			{
				/*DACCSLAT=0;
				//if(SPI2STATbits.SPITBF==0)
				{
					SPI2BUF=28672+ (middaccount- (downstep* ptosslope));//((middaccount-bdaccount)*ptosslope/50.0));//3800;// 3800=500, 3200=400A 2650;//Refpeakcnt;//2650;
				}
				*/
				
				//DACREF=(middaccount- (downstep* ptosslope));//((middaccount-bdaccount)*ptosslope/50.0));//3800;// 3800=500, 3200=400A 2650;//Refpeakcnt;//2650;
				decaycurrent=Decay_lookup[ptosslope];
				decaycurrent=310+(decaycurrent+setbaseamp);
				if(decaycurrent>=pdaccount)
				decaycurrent=pdaccount;
				DACREF=decaycurrent;//310.0+(decaycurrent*7.22);
				peakf=1;
				stepf=0;	
				basef=0;
				ptosslope++;
			}
			else
			{
				/*DACCSLAT=0;
				//if(SPI2STATbits.SPITBF==0)
				{
					SPI2BUF=28672+bdaccount;     //850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
				}*/
				
				DACREF=bdaccount;
				mbase1f=1;
				mbase2f=0;
				cout_100us=0;
				peakf=0;
				stepf=0;	
				basef=0;
				ptosslope=0;
				loopcount=0;
				loopinterval=0;
				
			}
		}
		else if((cout_100us<pulsebase) && peakf==0)//ripplecount
		{
			loopcount++;
			if(loopcount>=50)
			{
				loopcount=0;
				loopinterval++;
				if(loopinterval<(baseunit-2))//baseunit=newpulsebase/50;
				{
					if(loopinterval==1)
					{
						DACREF=bdaccount;
					}
					else if(loopinterval==2)
					{
						DACREF=addonbase;
					}
					else if(loopinterval==3)
					{
						DACREF=bdaccount;
					}
					else if(loopinterval==4)
					{
						loopinterval=0;
						DACREF=addonbase;
					}
				}
				else
				{
					DACREF=bdaccount;
				}
				
			}
		}
		else if((cout_100us>=pulsebase) && peakf==0)
		{
			if(mbase1f==1)
			{
				mbase1f=0;
				mbase2f=1;
				//basevtgcnt++;
			}	
			
			if(ptosslope<30)			
			{
				/*DACCSLAT=0;
				//if(SPI2STATbits.SPITBF==0)
				{
					SPI2BUF=28672+ (bdaccount+(upstep*ptosslope));//((pdaccount-bdaccount)*ptosslope)/50.0);//1300;//102A 600
				}*/
				DACREF	=(bdaccount+(upstep*ptosslope));
				peakf	=0;
				stepf	=0;	
				basef	=0;
				ptosslope++;
			}
			else
			{
				/*DACCSLAT=0;
				//if(SPI2STATbits.SPITBF==0)
				{
					SPI2BUF=28672+pdaccount;//1300;//102A 600
				}*/
				DACREF=pdaccount;
				peakf=1;
				stepf=0;	
				basef=0;
				ptosslope=0;
				mpeak1f=1;
				//mpeak2f=0;
			}
			//stobslope=0;
		}
		cout_100us++;
	}
}
/************************************************************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)          //FOR ENCODER SCANNING
{
  IFS1bits.T4IF=0;  
  count4_1ms++;
  
  DACCSLAT=0;
  //if(SPI2STATbits.SPITBF==0)
  {
		SPI2BUF=28672+DACREF;//1300;//102A 600
  }
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
  }	
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
			if(count_100ms>=10)
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
				PVOLTAGE	=(mpeakvtg *10.0)/40.0;//37.0 answer 100v=1000;
				presultvtg	=0;
				pvoltcnt	=0;
			}
			mpeak1f=0;
			mpeak2f=0;
		}
	}
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	
	presultcur		=	presultcur	+	result1;
	ploopcnt++;
	if(ploopcnt>=8)
	{
		padccur		=	presultcur	>> 	3;
		PCURRENT	=	(padccur * 5.0)/37.0;
		ploopcnt=0;
		presultcur=0;
		
		if(PCURRENT>=20)
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