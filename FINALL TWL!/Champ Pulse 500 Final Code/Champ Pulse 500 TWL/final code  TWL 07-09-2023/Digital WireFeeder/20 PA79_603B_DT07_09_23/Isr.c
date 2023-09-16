
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) //used for sending data to control PCB
{
      IFS0bits.U1TXIF = 0;      //clear TX interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)   //used for receiving data from control PCB
{
	IFS0bits.U1RXIF = 0; //clear rX interrupt flag
	rxdata= U1RXREG;
	//Send_Byte(rxdata);
    // uc1Rxfalg=1;
	//if(txonf==0)
	{
		if(rxdata=='@' && startptr1==0 && statusptr1==0 )// && txonf==0)
		{    
			startptr1   =1;
			arrptr      =0;
			statusptr1  =0;
			recchksum   =0;
		}
		else if(rxdata=='#' && startptr1==0 && statusptr1==0)// && txonf==0)
		{
			startptr1   =0;
			statusptr1  =1;
			arrptr      =0;
			recchksum   =0;
		}
		else if(startptr1==0 && statusptr1==1)
		{
			if(recstatus==0)
			{
				recpsstatus=rxdata;
				recstatus=1;
			}
			else if(recstatus==1)
			{
				if(rxdata==recpsstatus)//'?')
				{
				   comm_error_count=0;
				   psstatusu.psstatusbyte[0]=recpsstatus;
				   pstowfstr.psstatusbyte=recpsstatus;
				   
				   if(psstatus.motoroncommand==1 && psstatus.twinpulseon==1 )
				   {
				       if(psstatus.Hi_speedon==1)
				       {
//***				       TRISMTRFB=0;					uncomment After add Motor PWM
//***				       MTRFB=1;						uncomment After add Motor PWM
				           //TRISMOTOR_TRIP11=0;
					       //MOTOR_TRIP11=  1;
				           Update_PWM(Hi_setppwm);		
					       //Type.thickness=1;
				       }
				       else
				       {
//**** 				       TRISMTRFB=0;		uncomment After add Motor PWM
//***				       MTRFB=0;			uncomment After add Motor PWM
				           //TRISMOTOR_TRIP11=0;
				//         MOTOR_TRIP11=  0;
						   Update_PWM(Lo_setppwm);  
				//         Type.thickness=0;
				       }
				   }
				   /*if(psstatus.creepspeedon==0)
				   {
				        TRISMOTOR_TRIP11=0;
				        MTRFB=0;
				   }
				   else
				   {
				       TRISMOTOR_TRIP11=0;
				       MTRFB=1;
				   }
				   */
				   recstatus=0;
				   startptr1=0;
				   statusptr1=0;
				   arrptr=0;
				   recchksum=0;
				   send_statusf=1;
				   //send_status();          //send wf status immediately
				}
				else
				{
				   recstatus=0;
				   startptr1=0;
				   statusptr1=0;
				   arrptr=0;
				   recchksum=0;
				}
			}     
		}
		else if(startptr1==1 && statusptr1==0)
		{    
			if(arrptr<=RECEIVE_STRING_LENGTH)//21)
			{    
				rec_arr[arrptr]=rxdata;
				recchksum=recchksum+rxdata;
				arrptr++;	 
			}
			else if(recchksum==rxdata)
			{
				comm_error_count=0;
				
				for(ijk=0;ijk<=RECEIVE_STRING_LENGTH;ijk++)  //20 21 15 status byte controlled by wf
				{    
				   pstowfstru.pstransarr[ijk]=rec_arr[ijk];
				}
				
				weldmode=pstowfstr.weldmode;
				if(cEditfg == 0)
				{
				   setwirespeed=pstowfstr.setwspeed;
				}
				
				wfstatusu.wfstatusbyte[0]=pstowfstr.wfstatusbyte;
				
				if(wfstatus.twotfourtmode1==1)
				{
					Type.twot=0;
					Type.fourt=1;
				}
				else
				{
					Type.twot=1;
					Type.fourt=0;
				}
				
				if(cEditfg == 0)
				{
				   setvoltage=pstowfstr.Hi_setvoltage;
				   setvoltage<<=8;
				   setvoltage|=pstowfstr.Lo_setvoltage;
				}
				
				setcurrent=pstowfstr.Hi_setcurrent;
				setcurrent<<=8;
				setcurrent|=pstowfstr.Lo_setcurrent;
				
				Actual_amp=pstowfstr.Hi_actualcurrent;
				Actual_amp<<=8;
				Actual_amp|=pstowfstr.Lo_actualcurrent;
				
				Actual_vtg=pstowfstr.Hi_actualvoltage;
				Actual_vtg<<=8;
				Actual_vtg|=pstowfstr.Lo_actualvoltage;
				
				//Actual_amp = setpfreq;
				//Actual_vtg = Fltpfreq;
				cRelSpeedSign = pstowfstr.pulse_freq;
				rel_wirespeed=pstowfstr.rel_wirespeed;
				crater_speed=pstowfstr.crater_speed;
				
				if(cEditfg == 0)
				{
				   psstatusu.psstatusbyte[0]=pstowfstr.psstatusbyte;
				}
				
				error_code1=pstowfstr.error_code1;
				error_code2=pstowfstr.error_code2;
				
				commandu.commandbyte[0]=pstowfstr.command_to_wf;
				if(cMtrOverLdfg == 0)
				{
				   erroru.errorstatusbyte[0]=pstowfstr.error_code1;
				   erroru.errorstatusbyte[1]=pstowfstr.error_code2;
				}
				
				creep_speed=pstowfstr.creep_speed;
				
				if(command.volt_or_arc==1)
				//if(psstatus.migpmigmode==0)
				{
				   Type.arclength=0;
				   Type.vtg      =1;
				}
				else
				{
				   Type.arclength=1;
				   Type.vtg      =0;
				}
				if(wfstatus.twotfourtmode1 == 1)
				{
				   cWf2t4tmodefg = 1;
				}
				else
				{
				   cWf2t4tmodefg = 0;
				}
				startptr1=0;
				arrptr=0;
				recchksum=0;
				recstatus=0;
				statusptr1=0;
				transmitonf=1;
				onesecf=1;          //DATA WILL BE SEND ONLY WHEN DATA RECEIVED
			}    
			else
			{
			
			recstatus=0;
			startptr1=0;
			statusptr1=0;
			arrptr=0;
			recchksum=0;
			}
		}  
	}
	/*else
		{
		startptr1=0;
		arrptr=0;
		recchksum=0;
		
		} */   	
}

void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) //used for sending data to remote pcb  
{
      IFS1bits.U2TXIF = 0;      //clear TX interrupt flag
}


void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)  //used for recieving data from remote
{
	IFS1bits.U2RXIF = 0;   						// clear rX interrupt flag 
	uartdata		= U2RXREG;
	
	switch(ucState)
	{
		case 0: if(uartdata=='*')
				{
					ucState=1;uartdata=0;
				}
				else
				{
					ucState=0;uartdata=0;
				}
				break;
		case 1: if(uartdata=='A')
				{
					ucWireSpeedInc=1;pluspara1=1;minuspara1=0;ucState=0;uartdata=0;uiComunCount=0; 
				}
				else if(uartdata=='B')
				{
					ucWireSpeedDec=1;pluspara1=0;minuspara1=1;ucState=0;uartdata=0;uiComunCount=0; 
				}
				else if(uartdata=='C')
				{
					ucState=0;uartdata=0;uiComunCount=0; 
				}
				else if(uartdata=='D')
				{
					//Send_Byte2('$');Send_Byte2('P');
					ucTorchChk=0;ucState=0;uartdata=0;uiComunCount=0; 
				}
				else if(uartdata=='E')
				{
					//Send_Byte2('$');Send_Byte2('P');
					ucTorchChk=1;ucState=0;uartdata=0;uiComunCount=0; 
				}
				else if(uartdata=='F')
				{
					uiComunCount=0; ucState=0;uartdata=0;	//	setvoltage=22;
				}
				else
				{
					ucState=0;uartdata=0;
				}	
				break;			
		default:
				break;			
	}
}

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
 {                           
	IFS0bits.T1IF=0;
	IEC0bits.T1IE=0;	//Enable Timer1 interrupts
	T1CONbits.TON=0;	//start the timer
	updatedispf=0;
	updatedispf=0;//1;
    Display();
    count_1ms++;
    count_2ms++;
   	count_1msec++;
    count_pid++;
    //count_transms++;
    
    if(ucSTCheckCom==1)
    {
	    if(ucTorchComFail==0)
	  		uiComunCount++;
	  		
	  	if(uiComunCount>=25000)
	  	{
	  		ucTorchComFail=1;uiComunCount=0;ucSTCheckCom=0;TORCH_SELLAT=1;//setvoltage=33;		ucSTCheckCom=0;
	  		ucDipsInd=1;
	  	}
 	}
 		
    if(count_2ms >=1)
    {       
        count_2ms=0;
        read_enc1f=1;
    }
    
    if(cPowerOnErrSkipfg == 1)
    {
        if(iPowerOnErrSkipCnt == 0)
        {
            cPowerOnErrSkipfg = 0;
            iPowerOnErrSkipCnt = 0;
        }else
        {
            iPowerOnErrSkipCnt--;
        }
    }
        
    if(cGasRlyClrfg == 1)
    {
        if(iGasDbCnt == 0 )
        {
            Type.gason      =0;
            GAS_RLYLAT		=0;		//GAS_RLY         =0;        
            dispupdatef     =1;
            cGasRlyClrfg 	=0;
        }
        else
        {
            iGasDbCnt--;
        }
    }
    //---------------------------------------------------------------------
    if((cMtrOverLdfg == 0)&&(cPowerOnErrSkipfg == 0))
    {
        if((MOTOR_TRIP11 == 0)&&(cMtrOverLdDbfg == 0))
        {
            cMtrOverLdDbfg = 1;
            cMtrOverLdDbCnt = MTROVLDTIME;
        }
        else if((MOTOR_TRIP11 == 0)&&(cMtrOverLdDbfg == 1))
        {
            cMtrOverLdDbCnt--;
            if(cMtrOverLdDbCnt == 0)
            {
                cMtrOverLdDbfg = 0;
                cMtrOverLdfg = 1;						
                cMtrOverLdDbCnt = MTROVLDTIME;
                errorstatus.motor_over_ld_er5 = 1;  	
                Update_PWM(setwirespeed*0); 
                speeedrate=0;
            }
        }
        else if(MOTOR_TRIP11 == 1)
        {
            cMtrOverLdDbfg = 0;
        }
    }
            
    if(count_1ms>=500) //1000)
    {    
        count_1ms=0;
        comm_error_count++;
        if(weldmode=='P' || weldmode=='G')
        {
        	if(comm_error_count>3)
        	{
        		error8=1;
        		comm_error_count=4;
        	}
        	else
         		error8=0;
        }
        else
        {
            error8=0;
            comm_error_count=0;
        }
        //onesecf=1;  //mahesh disabled
    }
 	if(count_1msec >= 2)//10)//20)
    {
        count_1msec=0;
        if(kpressread==0)
        {
	       if(ucTorchComFail==0)
            	torchstatus1=ucTorchChk;	//	TORCHIN;
           else if(ucTorchComFail==1)
           		torchstatus1=TORCHIN;  
           				
            kpressread=1;
        }
        else
        {
            kpressread=0;
            
           if(ucTorchComFail==0)
            	torchstatus2=ucTorchChk;	//	TORCHIN;	
           else if(ucTorchComFail==1)
           		torchstatus2=TORCHIN;  	
            
            //torchstatus2=ucTorchChk;		//TORCHIN;
            
            tans   =(torchstatus1   ==   torchstatus2    ? 1:0);
            
            if(tans==1)
            {
                TORCH=(torchstatus2   ==   0    ? 'P':'X');
                //TORCH='X';
                if(TORCH=='P')
                {
                    wfstatus.torchonstatus=1;
                    if(cTorchPressfg == 0)
                    {
                        cPowerOnErrSkipfg = 1;
                        iPowerOnErrSkipCnt = 1000;
                        cTorchPressfg = 1;
                    }
                }
                else
                {
                    wfstatus.torchonstatus=0;
                    if(cTorchPressfg == 1)
                    {
                        cTorchPressfg = 0;
                    }
                }
            }
            
            //if((TORCH=='P')&&(ucTorchComFail==0))
	         //   uiComunCount=0;
	         
            if(prevTORCH != TORCH)
            {
                count_1ms=0;
                //onesecf=1;
                //txonf=1;
            }    
            prevTORCH = TORCH;
        }
    }
    
	IEC0bits.T1IE=1;	//Enable Timer1 interrupts
	T1CONbits.TON=1;	//start the timer
}

void __attribute__((__interrupt__)) _IC2Interrupt(void) 
{    
   IFS0bits.IC2IF=0;    		//to test if my program will go into isr() 
   if(Count == 0)         		// capture the first signal 
   { 
       //OneH = CCPR2H; 
       //OneL = CCPR2L; 
       OneH=IC2BUF;
       Count = 1; 
   } 
   else                   		// capture the second signal 
   { 
       //TwoH = CCPR2H;     	// save the time of second rising edge to some register 
       //TwoL = CCPR2L;
       //TMR1H = 0x00;          // clear timer1 
       //TMR1L = 0x00; 
       TwoH=IC2BUF;
       Count = 0; 
       Two = TwoH;
       //Two <<= 8;
       //Two |= TwoL;
       One = OneH;
      // One <<= 8;
      // One |= OneL;
       Total_Count = Two - One;
       pperiod=Total_Count; //65535/8=8192             //unit usec min 0 t0 32768;
       Total_Period=Total_Period+pperiod;
       pcount++;
       
       if(pcount>=16)
       {
           pcount=0;
           avgpperiod=Total_Period>>5; //LHS 3 TIMES = DIVIDE / 8 & LS 1 TIMES, 65535 COUNTS =32768USEC
           pfreq=1000000/avgpperiod; //in hz
           Total_Period=0;
           Tsampling =avgpperiod/1000.0;//avgpperiod/1000000.0;
           //pfreq = pfreq / 16;
           
           if(pfreq>=MAX_P_FB_FREQ)
               pfreq=MAX_P_FB_FREQ;
           else if(pfreq<=0)
              pfreq=0;

           //Fltpfreq=(0.2*pfreq)+(0.8)*prevFltpfreq;
           Fltpfreq=(0.2*pfreq)+(0.8)*prevFltpfreq;
//------------------------------------
           pstowfstr.Hi_data1 = pfreq / MTR_FREQ_CONSTANT;
//------------------------------------
           if(Fltpfreq>=MAX_P_FB_FREQ)
               Fltpfreq=MAX_P_FB_FREQ;
           else if(Fltpfreq<=0)
              Fltpfreq=0;
           
            prevFltpfreq=Fltpfreq;
            capintervalf=1;
            fixintervalf=0;
            count_pid=0;
            //if(cyclestrtf==1)// && closeloopf==1)
            if(cyclestrtf	==1 && psstatus.twinpulseon	==0)// && closeloopf==1))
               adaptivepidf	=1; //disabled for twin pulsse
            else
                adaptivepidf=0;
               //Adaptive_base_pid();
         }
   }    
}


/*void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
 
	unsigned int  adc_result=0;
	
	ADCON1bits.ASAM = 0;
	IFS0bits.ADIF = 0; 
	
	adc_result =ADCBUF0;   
	ADC_VAL_AVG=ADC_VAL_AVG+adc_result;     
	adc_loopcnt++; 
	
	if(adc_loopcnt>=10)
	{
		ADC_VAL=   ADC_VAL_AVG/10;

	    //ADC_VAL = (ADC_VAL/4095)*45.0;
		//ADC_VAL= ADC_VAL/4;
		ADC_VAL_AVG=0;
		adc_loopcnt=0;
        //pid_timer++;
	 }	
}
*/

void transmittops()
{
    chksum=0;
    pstowfstr.psstatusbyte=0xBB;//psstatusu.psstatusbyte[0];

    if(cWf2t4tmodefg == 1)
    {
        wfstatus.twotfourtmode1 = 1;
    }
    else
    {
        wfstatus.twotfourtmode1 = 0;
    }
    pstowfstr.wfstatusbyte=wfstatusu.wfstatusbyte[0];
    //TRISMOTOR_TRIP1=0;
    //if( wfstatus.torchonstatus==1)
    //MOTOR_TRIP1=1;
    //else
    //MOTOR_TRIP1=0;
    
    // transoffu.transarr[21]=transoff.wfstatusbyte;

    Tx_ptr=0;
    Send_Byte('@');
    if(cMtrOverLdfg == 1)
    {
        pstowfstru.pstransarr[16] = 0x10;//erroru.errorstatusbyte[0];
    }
    for(lmn=0;lmn<=TRANSMIT_STRING_LENGTH;lmn++)        //21
    {
		chksum=chksum+pstowfstru.pstransarr[lmn];
		Send_Byte(pstowfstru.pstransarr[lmn]);
    }
    if(cEditfg == 1)
    {
        Send_Byte('E');
    }
    else
    {
         Send_Byte('X');
    }
    Send_Byte(chksum);
}

void send_status()
{
   pstowfstr.wfstatusbyte=wfstatusu.wfstatusbyte[0];
   Send_Byte('#');
   Send_Byte(pstowfstr.wfstatusbyte);
   Send_Byte(pstowfstr.wfstatusbyte); //?
}

void timer1_init()
{	
	T1CON			=0;			//Stops the Timer1 and reset control reg.
	TMR1			=0;			//Clear contents of the timer register
	T1CONbits.TGATE =0;  		//Disable Gate Time Accumulation Mode
	T1CONbits.TCKPS	=0;
    T1CONbits.TCS	=0;
	PR1				=4500;     //1 ms 0X6000;	//Load the Period register with the value 0xFFFF 0x72cb interrupt after every 1.20msec
	//IPC0bits.T1IP	=3;			//Setup Timer1 interrupt 
	IFS0bits.T1IF	=0;			//Clear the Timer1 interrupt status flag
	IEC0bits.T1IE	=1;			//Enable Timer1 interrupts
	T1CONbits.TON	=1;			//strat the timer
}

/*void timer3_init()
{
	T3CON=0;			//Stops the Timer1 and reset control reg.
	TMR3=0;				//Clear contents of the timer register
	T1CONbits.TCKPS	=0;
	//T3CONbits.TCS	=0;
	PR3=0x7328;			//0xE650;//0x7328;         //1m sec//Load the Period register with the value 0xFFFF FREQ @ DISPLAY 168HZ & IN SAW 171 HZ.
	//IPC1bits.T3IP=5;	//Setup Timer1 interrupt,TO SET THE INTERRUPT PRIORITY
	IFS0bits.T3IF=0;	//Clear the Timer1 interrupt status flag
	IEC0bits.T3IE=1;	//Enable Timer1 interrupts
	T3CONbits.TON=1;	//start the timer
}*/

void uart2_init()   		//for comm with remote control
{
	TX2IO=0;RX2IO=1;
  	U2BRG=780;    			//780@2400  //@                        //9600 BAUD RATE
  	U2MODE=0X8000;        	//@ // uart enable	//00 = 8-bit data, no parity /0=1 Stop bit/operation in idle mode
  	IFS1bits.U2RXIF =0;    
  	IFS1bits.U2TXIF =0;
  	U2STAbits.UTXEN	=1;    	//@  //Uart transmit enable
  	IEC1bits.U2RXIE	=1;           //Uart reception interrupt enable
  	IEC1bits.U2TXIE	=1;
  	//IPC6bits.U2RXIP	=4;
}

void Send_Byte2(unsigned char data)
 {
	while(U2STAbits.UTXBF == 1);	
     U2TXREG=data;
 }
 
 void uart_init()
 {
	TX1IO=0;RX1IO=1;
   	U1BRG=194;                         //194==9615   191=>9765; 9600 BAUD RATE
   	U1MODE=0X8400;                     // uart enable	//00 = 8-bit data, no parity /0=1 Stop bit/operation in idle mode
  	IFS0bits.U1RXIF =0; 
   	IFS0bits.U1TXIF =0; 
   	U1STAbits.UTXEN=1;                 //Uart transmit enable
   	IEC0bits.U1RXIE=1;                 //Uart reception interrupt enable
   	IEC0bits.U1TXIE=1; 
 }
 
void Send_Byte(unsigned char transbyte)
 {
	while(U1STAbits.UTXBF == 1);	
    	U1TXREG=transbyte;
 }

 
void  init_pwm()  //10khz with count 0 to 3000 // for TORCH 26/06/2023
{ 
    OC2CONbits.OCM		=0;
    OC2CONbits.OCTSEL	=1; 		// FOR TIMER3 MOTOR PWM
    OC2CONbits.OCM		=6;         //toggle on compare match output compare is configured as pwm generated
    TRISDbits.TRISD1	=0;         //1472 for 20khz,2949 for 10khz freq    //736 for 40khz freq.    327=100Khz    //initialise pr2 reg. for freq.
    PR3					=2949;                     
    T3CONbits.TCKPS     =0;     	//timer2 prescaler 1    
    IFS0bits.T3IF       =0;        	//Clear the Timer1 interrupt status flag
    IEC0bits.T3IE       =0;        	// ENABLE Interrupt 
    T3CONbits.TON       =1;        	//start timer2
    OC2RS             	=0;  	 	//write duty cycle biffer register 50% DUTY cycle
}

void Update_PWM(unsigned int setwsduty)
{
   /* unsigned int Temp1=0x00, Dutycnt=0;
    Dutycnt=setwsduty;
    CCP1CONbits.DC1B=Dutycnt;
    Temp1=Dutycnt >> 2;
    CCPR1L=Temp1;
    iTest = Temp1;*/
    
    if(setwsduty>2760)  // 2450// 2570  updated on 31/08/2023
		setwsduty=2760;
		
	OC2RS=setwsduty;
} 
 
void PWM_INIT_DT()
{     
    OC1CONbits.OCM		 =0;
    OC1CONbits.OCTSEL	 =0;
    OC1CONbits.OCM       =6;//toggle on compare match output compare is configured as pwm generated
    TRISDbits.TRISD0     =0;// OUTPUT PIN FOR CARRIER WAVE IN digital torch
    //PR2                =2999; // PR1=327  for 100KHz freq.  
    PR2					 =290;	
    //PR2					 =199;
    OC1RS                =0;                       
    T2CONbits.TCKPS      =0;     //timer2 prescaler 1    
    IFS0bits.T2IF        =0;        //Clear the Timer1 interrupt status flag
    IEC0bits.T2IE        =0;        // ENABLE Interrupt 
    T2CONbits.TON        =1;        //start timer2
    OC1RS              	 =150;   //write duty cycle biffer register 50% DUTY cycle
    //OC1RS                =100; 
}

void capture_init()
{
	IC2CONbits.ICM	=0;
	TRISMPULSE 		=1; // set RD9 AS a input(CCP2)
	IC2CONbits.ICTMR=0; // TMR3 contents are captured  
	IC2CONbits.ICI	=0;		/*Interrupt on every capture event*/
	IC2CONbits.ICM	=0x03; // 00000011; CCP2 as capture mode, every rising edge..reference 4013 user manual
	IPC1bits.IC2IP 	=1; // Setup IC1 interrupt priority level
	IFS0bits.IC2IF	=0;
	IEC0bits.IC2IE 	=1;//   // CCP2 interrupt enabled
	//IC2CONbits.ICBNE=0;		/*Input capture buffer is empty*/
	//IC2CONbits.ICOV=0;		/*No input capture overflow occured*/
	T3CONbits.TON	=1;
    T3CONbits.TCKPS =0;//  1 =fosc/8, precale 1:8
      
} 


//void adc_init()
//{
// //The ADCON1, ADCON2 and ADCON3 registers control the operation of the A/D module. The
////ADCHS = register selects the input pins to be connected to the S/H amplifiers. 
//// ADPCFG register configures the analog input pins as analog inputs or as digital I/O. 
//// ADCSSL register selects inputs to be sequentially scanned.
//
//  	/* Set up the ADC Module */
//	ADPCFG = 0XFFFF;              //ALL PORT B PIN AS DIGITAL INPUT PIN
//    ADPCFGbits.PCFG8 = 0;         //PORTB.8 AS ANALOG INPUT PIN(motor VOLTAGE FEEDBACK)
//    
//	ADCSSL=0X0000;              	// SKIP ALL THE CHANNEL FOR INPUT SCANNING
//	
//	ADCSSLbits.CSSL8=1;         	//SCANNING(motor VOLTAGE FEEDBACK)
//	 
//	
//	ADCON1bits.FORM = 0;         //DATA OUTPUT FORMAT IS UNSIGNED INTEGER 0x0dddd
//	ADCON1bits.SSRC = 7; 	     //INTERNAL COUNTER ENDS SAMPLEING AND START CONVERSION(AUTO CONVERT).
//	ADCON1bits.ADSIDL = 0;       // CONTINUE IN IDEAL MODE
//	ADCON1bits.SIMSAM = 0;       //Samples multiple channels individually in sequence
//	ADCON2bits.VCFG = 0;         //REFERENCE VOLTAGE SOURCE AVDD & AVSS
//	ADCON2bits.CSCNA = 1;        //SCAN INPUTS
//	
//	ADCON2bits.SMPI = 1;    	 //INTERRUPT AFTER EVERY 1TH SAMPLE  @ here we get the interrrupt after 15 conversion single of channel
//	ADCON2bits.BUFM = 0;         //BUFFER CONFIGURED AS ONE 16- WORD BUFFER
//	ADCON2bits.ALTS = 0;         //******************ALWAYS USE MUX A SETTINGS
//	ADCON3bits.SAMC = 5;          //ACQUSATION TIME  hold sampled signal for SAMC*Tad cycles before starting of conversion
//	ADCON3bits.ADRC = 0;         // SYSTEM CLOCK FOR A/D CLOCK (T_AD)
//	ADCON3bits.ADCS = 40;        // Select T_AD=> T_AD= TCY(ADCS + 1) /2 ; => TCY= instruction clock cycle=1/30Mhz
//	
//	ADCHSbits.CH0SA = 8;         //@@@@@@@@@@@@@@@@@@@Channel 0 positive input is AN2
//	ADCHSbits.CH0NA = 0;         //Channel 0 negative input is VREFbit
//	ADCON2bits.CHPS = 0;         // CONVERT CHANNEL CH0
//	//	IPC2bits.ADIP = 2;           //PRIORITY
//	IFS0bits.ADIF = 0;           //CLEAR FLAG
//	IEC0bits.ADIE = 1;           //ENABLE A TO D CONVERSION INTERRUPT
//	ADCON1bits.ADON = 1;         // ON A/D
//	ADCON1bits.ASAM = 1;         // 1: AutoCONVERSION START  , 0: Sampling begins when SAMP bit set
//	ADCON1bits.SAMP = 1;         //AUTO SAMPLE/CONVERSION START
//	 
//}
