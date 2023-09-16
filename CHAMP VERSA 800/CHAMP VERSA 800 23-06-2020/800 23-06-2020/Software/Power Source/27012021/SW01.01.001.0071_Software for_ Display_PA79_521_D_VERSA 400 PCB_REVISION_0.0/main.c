//*****************************************************************************************************
//SOFTWARE REV.NO:01   ** PCB N0:-PA79/521/D
//************************************MODIFICATION DETAILS*********************************************
//DATE:31/03/2019          //MODIFICATION NOTE NO.:          //DONE BY:Sayali Mahajan
//for versa 800
//mma and mig mode
//BLANK PCB 521/D
//MODIFIED FOR CV USING FEEDLITE 40 WIREFEEDER
//wirefeeder communication added for mig mode
//ARCFORCE ADDED IN MMA 
//For 800A in MMA mode, reference to PWM card is 4.2V.
//*****************************************************************************************************
#include "p30f5011.h"
#include "math.h"
#include "dsp.h"
#include "float.h"
#include "define.c"
#include "variable.c"
#include "function.c"
#include "structure.c"
#include "display.c"
#include "encoder.c"
#include "isr.c"
#include "MMA.c"
//#include "SAW.c"
#include "MIG1.c"
#include "eeprom.c"

_FOSC(CSW_FSCM_OFF & FRC_PLL16);  		//FAIL SAFE CLOCK SWITCHING IS OFF AND OPERATING FREQUENCY FCY=16MHZ
_FWDT(WDT_OFF);                 		//WATCH DOG TIMER 0FF
_FGS(CODE_PROT_OFF);            		//CODE PROTECTION DISABLED
_FBORPOR(MCLR_EN & PBOR_OFF & PWRT_64); //MASTER CLEAR ENABLE AND BROWN OUT RESET OFF AND POWER ON TIMER DELAY ON

int main()
{   
	//int i,j;
	system_init();                        //SYSTEM INITiLISATION
	power_on();                           //POWER ON DISPLAY
	adc_init();
    TypeDP.DPGROUP[0]=0x00;
    //Typedp.digitdp1=1;
    //rsetcurrent=22;
    NC1IO=0;
    //--------------
    cPowerFlashfg = 1;
    cFlashCntr = 1000;
    cFlashfg = 0;
    iNoofshift = 3;
    iAvg_cnt = 0X01;
    iAvg_cnt = (iAvg_cnt << iNoofshift);
    
    iNoofDispShift = 15;
    loop = 0x01;
    loop = (loop << iNoofDispShift);
	//---------------
	//recall_mode_mem(1);
	
	//---------------   
	//rsetvoltage=240; 
    iKp=EEPROM_Read(28*2);//250;
    iKi=EEPROM_Read(30*2);;//10;
    iKd=EEPROM_Read(24*2);//10;
    iMul = EEPROM_Read(26*2);//10; 
    if(iKd>= 200)
    {
    	iKp=50;//1200;//250;
    	iKi=10;//60;
    	iKd=10;//20;	
    	iMul = 25;
		EEPROM_Erase_Write(28*2,iKp);
		EEPROM_Erase_Write(30*2,iKi);
		EEPROM_Erase_Write(24*2,iKd);    	
		EEPROM_Erase_Write(26*2,iMul); 		
	} 
	MPWMIO = 0;
	GASCHKSWIO = 0;
    //--------------
    // read EEPROM data
	ReadLastWeldData();    
    //--------------
    //dispweldcurrent=44;
    //weldvoltage=22;
		/*
		    disp_hex_dec_volt(1234);
		for(i = 0; i <= 1000; i++)
			for(j = 0; j <= 10000; j++);

		for(i = 0; i <= 1000; i++)
			for(j = 0; j <= 10000; j++);
			*/
//	trans_head('A');
communication.creep_speed = 50; //35//100;
iMigOffset = 450;
iLowpidvalue = 5;
imfvalue = 30;
//scalevalue = 6;

   	while(1)
	{ 	
//---------------
//		if(cTestfg == 1)
//		{
//			trans_head(cTest);
//			cTestfg = 0;
//		}	
//--------------- 
	if( cPowerFlashfg == 1)
	{
		communication_time_out=0;
		powerONflash();		
	}	
//----------------
		    //OCV_FLAGLAT=0;
		    //dispweldcurrent=44;
            //weldvoltage=22;
	      	if((process_flag==MMAMODE) &&(cPowerFlashfg == 0))               // MMA MODE 
			{ 
			    mma(); 
				Typedp.digitdp7	=1;			    
			    if(arcforce != 0)
			    {
					CURR_LEDLAT=1;				
				}else
				{
					CURR_LEDLAT=0;					
				}	
	      	}
	      	else if((process_flag==MIGMODE)&&(cPowerFlashfg == 0))
	      	{
				if(ENCODERSW==0 &&  keyfoundfg == 0)                    //SWITCH PRESSED
				{
//					keyfoundfg=1;
				}
				else if(ENCODERSW==1 &&  keyfoundfg == 1)
				{
					cpidmode++;
					if(cpidmode >= 8)
					{
						cpidmode = 0;
						EEPROM_Erase_Write(28*2,iKp);
						EEPROM_Erase_Write(30*2,iKi);
						EEPROM_Erase_Write(24*2,iKd);
						EEPROM_Erase_Write(26*2,iMul);
					}
					keyfoundfg = 0;	
				}							      	
		      	if(cpidmode==1 && weldon==0) //@Display set Arcforce
				{
					Typedp.digitdp7	=0;
					CURR[0]='K';
					CURR[1]='P';
					CURR[2]='/';
					CURR[3]='/'; 
					disp_hex_dec_volt(iKp);	
				}
				if(cpidmode==2 && weldon==0) //@Display set Arcforce
				{
					Typedp.digitdp7	=0;
					CURR[0]='K';
					CURR[1]='I';
					CURR[2]='/';
					CURR[3]='/'; 
					disp_hex_dec_volt(iKi);	
				}
		      	if(cpidmode==3 && weldon==0) //@Display set Arcforce
				{
					Typedp.digitdp7	=0;
					CURR[0]='K';
					CURR[1]='D';
					CURR[2]='/';
					CURR[3]='/'; 
					disp_hex_dec_volt(iKd);	
				}								
		      	if(cpidmode==4 && weldon==0) //@Display set Arcforce
				{
					Typedp.digitdp7	=0;
					CURR[0]='K';
					CURR[1]='M';
					CURR[2]='/';
					CURR[3]='/'; 
					disp_hex_dec_volt(iMul);	
				}			
		      	if(cpidmode==5 && weldon==0) //@Display set Arcforce
				{
					Typedp.digitdp7	=0;
					CURR[0]='O';
					CURR[1]='F';
					CURR[2]='F';
					CURR[3]='S'; 
					disp_hex_dec_volt(iMigOffset);	
				}	
		      	if(cpidmode==6 && weldon==0) //@Display set Arcforce
				{
					Typedp.digitdp7	=0;
					CURR[0]='L';
					CURR[1]='O';
					CURR[2]='W';
					CURR[3]='/'; 
					disp_hex_dec_volt(iLowpidvalue);	
				}
				if(cpidmode==7 && weldon==0) //@Display set Arcforce
				{
					Typedp.digitdp7	=0;
					CURR[0]='M';
					CURR[1]='U';
					CURR[2]='F';
					CURR[3]='/'; 
					disp_hex_dec_volt(imfvalue);	
				}					
	      		mig();	
	      		//Type.twot=1;      		
				if(dispweldcurrent>= 20) //46)   //45)) //74) //40) //74)  
//					if(weldcurrent >= 20)
					{
						MIGweldon_detectf=1;
						psstatus.creepspeedon=0;
					}	
	      		if(cFramefg == 1)//transmit2wf_f==1)//trans_flag==1 && mig_trans_f==1 ) //trans_flag in MIG1
	      		{	
	      		   transmittowf();
	      		   //transmit2wf_f=0;
	      		   cFramefg = 0;
	      		   //mig_trans_f=0;
	      		}
				if(Torchkey=='P' || cyclestrt==1) 	//torch function scan
				{
					//trans_chk_f=1;
//					tx2chksm=0;
					torchaction();
				}
				else if(gas_check_f!=0)// && Torchkey=='R' && cyclestrt!=1)
				{
					gas_check();
				
				}
				/*else if(receive_parameter.Gas_check_key==1)
				{
					//for(check=0; check<3;check++)
					
					while(receive_parameter.Gas_check_key==1)
					{
						TypeDP.DPGROUP[0]=0x00;
      					GASRELAYLAT=1;		//GAS ON RELAY.
      					OCV_FLAGLAT=1;     	//OCV ON
						ARCONLAT=1;			//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT=CVMODE;	    //CV MODE SELECTION IN PWM CARD
						CURR[0]='G';
						CURR[1]='A';
						CURR[2]='S';
						CURR[3]='/';          			//-
						VOLT[0]='O';
						VOLT[1]='C';
						VOLT[2]='V';
						VOLT[3]='/';	
					}
						GASRELAYLAT	=0;				//GAS ON RELAY.
						OCV_FLAGLAT	=0;          	//OCV ON
						ARCONLAT	=0;				//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT	  	=CVMODE;		//CV MODE SELECTION IN PWM CARD
						Disp_updatef=1;

				}
				
				else if(Inchkey=='P')
				{
					aaa=0;
					while(Inchkey=='P')
					{
						if(aaa<=10)
						{
							TypeDP.DPGROUP[0]=0x00;
      						CURR[0]='I';
							CURR[1]='N';
							CURR[2]='C';
							CURR[3]='H';          //-
							disp_hex_dec_volt(aaa);                         		//DISPLAY ARC VOLTAGE
				           	OC2RS= aaa* 100.0;
							for(ccc=0;ccc<20;ccc++)
							for(bbb=0;bbb<30000;bbb++);
							aaa++;
						}
					}
						OC2RS=0;
				}*/
	       	}  
	       	
	} //while ends here  
return(0);
}



void TogglePin()
{
	if(pidfg==1)
	{
		pidfg=0;
		MPWMLAT = 1;
		GASCHKSWLAT = 1;
	}
	else
	{
		pidfg=1;
		MPWMLAT = 0;	
		GASCHKSWLAT = 0;	
	}	
}	
void system_init()
{
     	ADPCFG = 0xFFFF;
     	Portpin_init();
		display_int();
     	timer1_init();
     	timer4_init();	
     	encoder_init();
     	//adc_init();
     	pwm_init();
     	uart_init();
		OCV_FLAGLAT=0;  // OCV OFF
		spi_init();
}
    
void Portpin_init()
{
	ARCONIO=0;
	CCCVIO=0;
	OCV_FLAGIO=0;
	CURR_LEDIO=0;
	WS_SPEED_LEDIO=0; 
	MIGONIO=1;	        //reading mig mode
	DACSCKIO=0;
	DACSDOIO=0;
	DACCSIO=0;
	
	DACSDOLAT=0;
	DACSCKLAT=0;
	DACCSLAT=0;
}
void timer1_init()
{
	T1CON=0;			//Stops the Timer1 and reset control reg.
	TMR1=0;		    	//Clear contents of the timer register
	PR1=29481;			//0X4650;		//Load the Period register with the value 0xFFFF 0x4650 interrupt after every 1 msec
						///t=1/(4*7.37MHZ)= 33.92nsec //1usec= 29.48 =0x001D //100usec=2948 =0x0B84 //1msec=29,481=0x7329
	IPC5bits.T4IP=1;	//Setup Timer1 interrupt 
	IFS0bits.T1IF=0;	//Clear the Timer1 interrupt status flag
	IEC0bits.T1IE=1;	//Enable Timer1 interrupts
	T1CONbits.TON=1;	//start the timer
}

void timer4_init()      //USED FOR ENCODER SCANNING
{
	T4CON=0;			//Stops the Timer1 and reset control reg.
	TMR4=0;				//Clear contents of the timer register
	PR4=0XFFFF;			// 2.2msec  AAAA;//Load the Period register with the value 0xFFFF 0x4650 interrupt after every 2.7 msec
	IPC5bits.T4IP=1;	//Setup Timer1 interrupt 
	IFS1bits.T4IF=0;	//Clear the Timer1 interrupt status flag
	IEC1bits.T4IE=1;	//Enable Timer1 interrupts
	T4CONbits.TON=1;	//start the timer
}
void pwm_init()
{
	OC1CON=0;			//Turn off output compare module 1
	OC1RS=0;			//write duty cycle buffer register
	OC1R=0;				//write to initial duty cycle value
	OC1CONbits.OCM=6;	//output compare is configured as pwm generated  for reference.
	
	OC2CON=0;			//Turn off output compare module 1
	OC2RS=0;			//write duty cycle biffer register
	OC2R=0;				//write to initial duty cycle value
	OC2CONbits.OCM=6;	//output compare is configured as pwm generated  for motor pwm.

	PR2=2949;			//1470;	//1470 for 10khz @ 8 PLL , 2949 for 10khZ 10KHZ
	IPC1bits.T2IP=2;	//setup timer2 at desired priority level
	IFS0bits.T2IF=0;	//clear timer2 interrupt flag	
	IEC0bits.T2IE=1;	//enable timer2 interrupt flag
	T2CONbits.TCKPS=0;  //timer2 prescaler 1
	T2CONbits.TON=1;	//start timer2
    OC1RS=0;//1000.0;         //fixed pwm
	OC2RS=0;//1000.0;         //fixed pwm	
}

void adc_init(void)
{
	ADPCFG = 0XFFFF;			// all port B pin as digital input pin
//	ADPCFG = 0XBFF0;	        // RBO,RB1,RB2,RB3,RB14 CONFIGURED AS ANALOG INPUT 
	ADPCFG = 0XB7F0;			// RBO,RB1,RB2,RB3,RB11,RB14 CONFIGURED AS ANALOG INPUT
	ADCSSL = 0x0000;			// skip all analog channels for input scanning
//  ADCSSL = 0x400F;            // SELECT AN0,AN1,AN2,AN3, AN14 FOR INPUT SCANNING
	ADCSSL = 0x480F;            // SELECT AN0,AN1,AN2,AN3,AN11,AN14  FOR INPUT SCANNING
	ADCON1bits.FORM = 0;		// data output format in unsigned integer 
	ADCON1bits.SSRC = 7;		// internal counter ends sampleing and starts conversion 
	ADCON2bits.VCFG = 0;		// setup adc voltage reference source AVdd & AVss 	
	ADCON2bits.CSCNA = 1;		// scan inputs 	
	ADCON2bits.SMPI = 5; //5;//m3;	// interrupt after every 6th sample one sample from each channel 	24012020
	ADCON2bits.BUFM = 0;		// buffer configure as one 16-word buffer 	
	ADCON2bits.ALTS = 0;		// always use MUX A input multiplexer settings 	
	ADCON3bits.SAMC = 1;   //@PREV:4 NOW:1     m10;  //10 now 10 TAD
	ADCON3bits.ADRC = 0;		//AD conversion clock source from system clock 
	ADCON3bits.ADCS = 19;  //@PREV:39 NOW:19		//10 modified on 12-8-2016
	ADCHSbits.CH0NA = 0;		// -ve input is Vref- 
	IFS0bits.ADIF = 0;			// clear A to D conversion complete flag 
	IEC0bits.ADIE = 1;			// enable A to D conversion interrupt 
	ADCON1bits.ADSIDL =0;       // Continue module operation in Idle mode
    ADCON1bits.ADON = 1;		// on adc 
	ADCON1bits.ASAM = 1;		// Auto sample / conversion start 
}

void uart_init() //9600 baud rate
{
   U1BRG=190;                    	//190---9600 //96 for 4800 baud rate {[((7.37 * 1000000*16)/4)/9600]/16}- 1;
   U1MODE=0X8800;               	//uart enable,00 = 8-bit data, no parity ,0=1 Stop bit/operation in idle mode
   IFS0bits.U1RXIF = 0;         	//clear flag
   U1STAbits.UTXEN=1;           	//Uart transmit enable
   IEC0bits.U1RXIE=1; 
//   IEC0bits.U1TXIE=1; 

   U2BRG=190;                           //190 ----9600	//48, 190;  //48 for 38400 baud rate, and 190 for 4800 baud rate {[((7.37 * 1000000*8)/4)/4800]/8}- 1;
   U2MODE=0X8800;               	// uart enable	//00 = 8-bit data, no parity /0=1 Stop bit/operation in idle mode
   IFS1bits.U2RXIF = 0; 
   IEC1bits.U2TXIE=1;
   U2STAbits.UTXEN=1;           	//Uart transmit enable
   IEC1bits.U2RXIE=1;           	//Uart reception interrupt enable	38400 baud rate
}

void trans_head(unsigned char data)  //Transmit data to saw head in SAW mode
{
	while(U1STAbits.UTXBF == 1);	
   U1TXREG=data;
}

void trans(unsigned char data)  //Transmit 
{
   while(U2STAbits.UTXBF == 1);	
   U2TXREG=data;
}



void trip(void)                  //refer protection ckt in schematic
{

   //if(trip_ip>=1550 && trip_ip<=1750)
   if(trip_ip>=1390 && trip_ip<=1800)				//1.7V-2.2V
   {
	    CURR[0]='E';
	    CURR[1]='R';
	    CURR[2]='R';
	    CURR[3]=91;
	    VOLT[0]='0';
	    VOLT[1]='0';
	    VOLT[2]='0';
	    VOLT[3]='2';  
	    trip_status='Y';
	    trip_flag=1;
   }
  //else if(trip_ip>=2400 && trip_ip<=2600)
  else if(trip_ip>=2210 && trip_ip<=2620)
   {
	    CURR[0]='E';
	    CURR[1]='R';
	    CURR[2]='R';
	    CURR[3]=91;
	    VOLT[0]='0';
	    VOLT[1]='0';
	    VOLT[2]='0';
	    VOLT[3]='3';//1';  
	    trip_status='Y';
	    trip_flag=1;  
   }
  //else if(trip_ip>=3600 && trip_ip<=3800)
 else if(trip_ip>=570 && trip_ip<=980)
   {
	    CURR[0]='E';
	    CURR[1]='R';
	    CURR[2]='R';
	    CURR[3]=91;
	    VOLT[0]='0';
	    VOLT[1]='0';
	    VOLT[2]='0';
	    VOLT[3]='1';  
	    trip_status='Y';
	    trip_flag=1;  
   }
 else if((Motorerr=='E' && motorerrcnt>=40) ||(motortrip==1))//&& cyclestrt==1))	
 {
		CURR[0]='E';
		CURR[1]='R';
		CURR[2]='R';
		CURR[3]=91;
		VOLT[0]='0';
		VOLT[1]='0';
		VOLT[2]='0';
		VOLT[3]='5';  
		motortrip=1;
		trip_status='Y';
		trip_flag=1;
		//trans('T');
}
else if(ERROR_4_errorf==1)
	{
		CURR[0]='E';
		CURR[1]='R';
		CURR[2]='R';
		CURR[3]=91;
		VOLT[0]='0';
		VOLT[1]='0';
		VOLT[2]='0';
		VOLT[3]='4';
		trip_status='Y';
		trip_flag=1;
		error_4_check4t=0;
		error4_flag=0;
//		ERROR_4_errorf=0;			
	}
else if(comm_errorf==1)
	{
		CURR[0]='E';
		CURR[1]='R';
		CURR[2]='R';
		CURR[3]=91;
		VOLT[0]='0';
		VOLT[1]='0';
		VOLT[2]='0';
		VOLT[3]='8';
		trip_status='Y';
		trip_flag=1;
	}

 else if(weldcurrent >=2000 && overflag==1)
{
	  	       
	  	       trip_status='Y';
		       trip_flag=1;
		       danger_flag=1;
}
else if(curimbf==1 && scalmode==0)		//current imbalance error.
{
 		CURR[0]='E';
	    CURR[1]='R';
	    CURR[2]='R';
	    CURR[3]=91;
	    VOLT[0]='0';
	    VOLT[1]='0';
	    VOLT[2]='1';
	    VOLT[3]='0';  
	    trip_status='Y';
	    trip_flag=1; 
	    imtrip_flag=1;

}

  else if(danger_flag==0)
   {
	   
	   
	    trip_flag=0;
	    //OCV_FLAGLAT=0;
	    //over=0;
	    //TRIPLEDLAT=0;       TEMP
	    if( trip_status=='Y')
	    {
			Disp_updatef=1;
			disp_flag=1;
	    }
	    trip_status='N';
   }
}

void power_on(void)
{
    CURR[0]=92;
    CURR[1]=92;
    CURR[2]=92;
    CURR[3]=92;
    VOLT[0]=92;
    VOLT[1]=92;
    VOLT[2]=92;
    VOLT[3]=92;
    //MMALEDLAT=1;      //TEMP
    //SAWLEDLAT=1;      //TEMP
    //TRIPLEDLAT=1;     //TEMP
    //REMOTELEDLAT=1;
    poweron_flag=1;
    delay(1000);
    //MMALEDLAT=0;      //TEMP
    //SAWLEDLAT=0;      //TEMP
    //TRIPLEDLAT=0;      //TEMP
    //REMOTELEDLAT=0;
    CURR[0]='A';
    CURR[1]='D';
    CURR[2]='O';
    CURR[3]='R';
    VOLT[0]='W';
    VOLT[1]='E';
    VOLT[2]='L';
    VOLT[3]='D';
    delay(7000);
    CURR[0]='R';
    CURR[1]='E';
    CURR[2]='V';
    CURR[3]='N';
    VOLT[0]='0';
    VOLT[1]='0';
    VOLT[2]='0';
    VOLT[3]='0';	
    cali_flag=1;
    poweron_flag=0;
    delay(7000);
    cali_flag=0;
    return;
}

void powerONflash()
{
	if((cFlashCntr == 0)&&(cFlashfg == 1))
	{
		CURR[0]='A';
    	CURR[1]='D';
    	CURR[2]='O';
    	CURR[3]='R';
    	VOLT[0]='W';
    	VOLT[1]='E';
    	VOLT[2]='L';
    	VOLT[3]='D';
    	cFlashfg = 0;
    	cFlashCntr = 1000;
 	}
 	else if((cFlashCntr == 0)&&(cFlashfg == 0))
 	{
		CURR[0]=0x2f;//'0';
    	CURR[1]=0x2f;//'0';
    	CURR[2]=0x2f;'0';
    	CURR[3]=0x2f;' ';
    	VOLT[0]=0x2f;' ';
    	VOLT[1]=0x2f;' ';
    	VOLT[2]=0x2f;' ';
    	VOLT[3]=0x2f;' ';	 	
    	cFlashfg = 1;    
    	cFlashCntr = 1000;	
	}	   	
}	
void delay(unsigned int y)
{
  unsigned int i=0,j=0;
  while(i<y)
  {
	  j=0;
      while(j<600)
      {
	    j++;
	 } 	  
       i++;
  }     
  return;
}

unsigned char Read_Encodersw(void)
{
	unsigned char Keydetect=0;
	if(ENCODERSW==0)
	{
		for(aaa=0;aaa<1000;aaa++);
		if(ENCODERSW==0)
		{
			Keydetect='Y';
		}
	}
	else
		    Keydetect='X';

	return(Keydetect);
}

unsigned char Read_Torchsw(void)
{
	unsigned char Keydetect=0;
	if(ENCODERSW==0)
	{
		for(aaa=0;aaa<1000;aaa++);
		if(ENCODERSW==0)
		{
			Keydetect='Y';
		}
	}
	else
		Keydetect='X';

	return(Keydetect);
}

void Read_portpin()
{
	static unsigned char  torchstatus1,torchstatus2,inchstatus1,inchstatus2,movldstatus1,movldstatus2,tmodestatus1,tmodestatus2,gaschkstatus1,gaschkstatus2;
	static unsigned char  tans,ians,movdans,tmodeans,gaschkans;
	//trans('R');
	TORCHSWIO=1;
	INCHSWIO=1;
	MOVLDIO=1;
	TMODESWIO=1;      //reading 2T/4T switch
//	GASCHKSWIO=1;	// commented on 25052020
	
	if(kpressread==0)
	{
		torchstatus1	=TORCHSW;
		inchstatus1		=INCHSW;
		movldstatus1	=MOVLD;
		tmodestatus1	=TMODESW;
	//	gaschkstatus1	=GASCHKSW;// commented on 25052020
		kpressread=1;
		//trans('1');	
		//trans(movldstatus1);
		//trans(gaschkstatus1);	

	}
	else if(kpressread==1)
	{
		//torchstatus2	=TORCHSW;  //disabled for versa 800
		//inchstatus2		=INCHSW;
		//movldstatus2	=MOVLD;
		//tmodestatus2	=TMODESW;  //disabled for versa 800
		//gaschkstatus2	=GASCHKSW;

		//trans('2');	
		//trans(movldstatus2);
		//trans(gaschkstatus2);


		//tans	=(torchstatus1	==	torchstatus2 	? 1:0);    disabled for versa 800
		//ians	=(inchstatus1	==	inchstatus2 	? 1:0);
		//movdans	=(movldstatus1	==	movldstatus2 	? 1:0);
		//tmodeans=(tmodestatus1	==	tmodestatus2 	? 1:0); disabled for versa 800
		//gaschkans=(gaschkstatus1==	gaschkstatus2 	? 1:0);
//		if(tans==1)
//		{
//			Torchkey =	(torchstatus2	==	1 	? 'P':'R');
//		}
//		if(ians==1)
//		{
//			Inchkey	=	(inchstatus2	==	1 	? 'P':'R');
//		}
		//if(movdans==1)
		//{
		//	Motorerr=	(movldstatus2	==	1 	? 'N':'E');
		//}
//		if(tmodeans==1)                                      //disabled for versa 800
//		{
//			Torchmode	=(tmodestatus2	==	1 	? '2':'4');
//		}
		/*if(gaschkans==1)
		{
			Gasonkey	=(gaschkstatus2	==	1 	? 'R':'P');
		}*/
		
		 /*if(receive_parameter.Gas_check_key==1)
		 {
		 
		     Gasonkey='P';
		 }
		 else
		 {
		     Gasonkey='R';
		 
		 }*/
		
		kpressread=0;
	}	
}
void gas_check()
{
	if(gas_check_f==1)
	{
		while(gas_check_f==1)
		{
		TypeDP.DPGROUP[0]=0x00;
		GASRELAYLAT=1;		//GAS ON RELAY.
		OCV_FLAGLAT=1;     	//OCV ON
		ARCONLAT=1;			//ARCON OUTPUT SIGNAL TO PWM PCB
		CCCVLAT=CVMODE;	    //CV MODE SELECTION IN PWM CARD
		CURR[0]='G';
		CURR[1]='A';
		CURR[2]='S';
		CURR[3]='/';          			//-
		VOLT[0]='O';
		VOLT[1]='C';
		VOLT[2]='V';
		VOLT[3]='/';
		}
	//gas_check_f=0;
	}
	else if(gas_check_f==2)
	{
		GASRELAYLAT	=0;				//GAS ON RELAY.
		OCV_FLAGLAT	=0;          	//OCV ON
		ARCONLAT	=0;				//ARCON OUTPUT SIGNAL TO PWM PCB
		CCCVLAT	  	=CVMODE;		//CV MODE SELECTION IN PWM CARD
		Disp_updatef=1;
	    gas_check_f=0;
	
	}


}
void spi_init()
{

   DACSCKIO=0;
   DACSDOIO=0;
   DACCSIO=0;
	
   DACSDOLAT=0;
   DACSCKLAT=0;
   //DACCSLAT=0;	
   DACCSLAT=0;
   
   IFS1bits.SPI2IF=0;       //CLEAR FLAG
   IEC1bits.SPI2IE=1;       //enable interrupt
   IPC6bits.SPI2IP=1;       //INTERRUPT PRIORITY 1 LOWEST
   SPI2CONbits.FRMEN=0;      //frame mode support disabled
   SPI2CONbits.DISSDO=0;     //SDO pin is controlled by module
   SPI2CONbits.MODE16=1;     //16 bit supported
   SPI2CONbits.SMP=0;        //input is sampled at middle of data output time
   SPI2CONbits.CKE=0;        //data changes when high to low pulse
   SPI2CONbits.SSEN=0;       //CONTROLLED BY PORT PIN
   SPI2CONbits.CKP=1;        //IDLE CLOCK
   SPI2CONbits.MSTEN=1;      //master mode
   SPI2CONbits.SPRE=6;//6;       //SECONDARY PRESCALE 3:1 SO FSPI 5MHZ
   SPI2CONbits.PPRE=3;       //primary prescale 1:1
   SPI2STATbits.SPIROV=0;
   
   SPI2STATbits.SPISIDL=0;    //continue on ideal mode
   SPI2STATbits.SPITBF=0;     //transmit buffer empty
   SPI2STATbits.SPIEN=1;      //enable or disable module
   
   SPI2BUF=7000;
   
   

}
void transmittowf()
{
unsigned char j,cChksum = 0;
	/*
	//tx2chksm=0;
	trans_chk_f=1;
	//transmit_parameter.psstatusbyte=psstatusu.psstatusbyte[0];
	//transmit_parameter.wfstatusbyte=wf_statusu.wfstatus_byte[0];
	communication.psstatusbyte=psstatusu.psstatusbyte[0];
	communication.wfstatusbyte=wf_statusu.wfstatusbyte[0];
	
	for(iii=0; iii<=STRING_LENGTH; iii++) //STRING_LENGTH=21
	{
		tx2chksm=tx2chksm+commu_ps_wfu.commu_arr[iii];//transmit_parameteru.transmit_parameter_byte[iii];
		trans_ps_wf_arr[iii]=commu_ps_wfu.commu_arr[iii];
		
	
	}
	new_tx2chksm=tx2chksm;
	trans_ps_wf_arr[iii]=new_tx2chksm;
	starttx2=1;
	tx2counter=0;
	U2TXREG='@';
	*/
	tx2chksum=0;
	trans_chk_f=1;
	communication.psstatusbyte=psstatusu.psstatusbyte[0];
	if(Torchmode=='2')
	{
		wfstatus.twotfourtmode1=0;
	}
	else if(Torchmode=='4')
	{
		wfstatus.twotfourtmode1=1;
	}
	/*
	for(iii=0; iii<=STRING_LENGTH; ++iii) 
	{
//		tx2chksm=tx2chksm+commu_ps_wfu.commu_arr[iii];
		trans_ps_wf_arr[iii]=commu_ps_wfu.commu_arr[iii];
		tx2chksm=tx2chksm+trans_ps_wf_arr[iii];
	}
	*/
	for(j=0; j<=STRING_LENGTH; ++j) 
	{
		trans_ps_wf_arr[j]=commu_ps_wfu.commu_arr[j];
		cChksum=cChksum+trans_ps_wf_arr[j];
	}	
	
	communication.wfstatusbyte=wf_statusu.wfstatusbyte[0];	///  need to chk-------

//	communication.weldmode=weldmode;
	new_tx2chksm=tx2chksm & 0XFF;
	trans_ps_wf_arr[STRING_LENGTH+1] = cChksum;
	starttx2=1;
	tx2counter=0;
	U2TXREG='@';
	//U2TXREG='#';	
//	cEditfg = 0;
}
	

	  
	  
	  