//*****************************************************************************************************
//SOFTWARE REV.NO:01   ** PCB N0:-PA9/521/C
//************************************MODIFICATION DETAILS*********************************************
//DATE:21/01/2016          //MODIFICATION NOTE NO.:          //DONE BY:JYOTI & MAHESH
//calibration in saw process added
//mma saving mode on
//error codes are added
//BLANK PCB 521/C
//MODIFIED FOR CV USING FEEDLITE 40 WIREFEEDER
//champ multi 1200
//ARCFORCE ADDED IN MMA BY MAHESH ////////////////////////////////27/12/2019
//REV 4.2 done by Lomesh with selection of champ 800/1200 and locking/unlocking of parameters
//REV 4.3 done by Saurabh with min setcurrent limit changed from 100 to 60.
//REV 4.5 done by Bhushan with min setcurrent limit changed from 60 to 100 only in 1200A.
//*****************************************************************************************************
#include "p30f5011.h"
#include "math.h"
#include "dsp.h"
#include "float.h"
#include "define.c"
#include "variable.c"
#include "function.c"
#include "display.c"
#include "encoder.c"
#include "isr.c"
#include "MMA.c"
#include "SAW.c"
#include "MIG1.c"
#include "eeprom.c"

_FOSC(CSW_FSCM_OFF & FRC_PLL16);  		//FAIL SAFE CLOCK SWITCHING IS OFF AND OPERATING FREQUENCY FCY=16MHZ
_FWDT(WDT_OFF);                 		//WATCH DOG TIMER 0FF
_FGS(CODE_PROT_OFF);            		//CODE PROTECTION DISABLED
_FBORPOR(MCLR_EN & PBOR_OFF & PWRT_64); //MASTER CLEAR ENABLE AND BROWN OUT RESET OFF AND POWER ON TIMER DELAY ON

int main()
{   
	system_init();                        //SYSTEM INITLISATION
	power_on();                          //POWER ON DISPLAY
		
	iSetcurrbuff = model_select();
	
	if(iSetcurrbuff == 1200)
	{
		iSetmincurrbuff = 100;  		//100 to 60 changed on 2/2/2021;60 to 100 changed on 23.05.2023.
	}
	else if((iSetcurrbuff == 800)||(iSetcurrbuff == 600))
	{
		iSetmincurrbuff = 60;			//100; //changed on 2/2/2021
	}

	
	if(memdata <= 1)//iSetmincurrbuff)
		memdata=1;//iSetmincurrbuff;
		
	iCalicnt=memdata;	
	
	adc_init();
    TypeDP.DPGROUP[0]=0x00;
    //Typedp.digitdp1=1;
	NC1IO=0;
	
   	while(1)
	{ 	
			
	      	if(process_flag==MMAMODE)              // MMA MODE 
			{ 
			    mma(); 
	      	}
	      	else if(process_flag==MIGMODE)
	      	{
	      		mig();
				if(Torchkey=='P' || cyclestrt==1) 	//torch function scan
				{
					torchaction();
				}
				else if(Gasonkey=='P')
				{
					while(Gasonkey=='P')
					{
						TypeDP.DPGROUP[0]=0x00;
      					GASRELAYLAT=1;				//GAS ON RELAY.
      					OCV_FLAGLAT=1;     			//OCV ON
						ARCONLAT=1;					//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT=CVMODE;	    		//CV MODE SELECTION IN PWM CARD
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
				}
	       	}  
	      else if(process_flag==SAWMODE)          //SAW
	      {   
	            saw();
	            if(Read_Ensw==1 && welding_status=='O')
	            {	 
		            Read_Ensw=0;
		            Keyans=Read_Encodersw();
		            
			  		if(Prevkeyans!=Keyans)
			  		{
						if(Keyans=='Y')
						{
							if(calibrationf==1)
							{
								calibrationf=0;
								disp_calf=1;
								read_hvtgf=0;
								REMOTELEDLAT=0;
								avg_hvtg=0;
								avg_psvtg=0;
								avg_pscur=0;
								measured_hvtg=0;
								measured_psvtg=0;
								measured_pscur=0;
								recvtgcntr=0;
								avgcntr=0;
							}
							else
							{
								calibrationf=1;
								disp_calf=1;
								REMOTELEDLAT=1;
								resistance=0;
								read_hvtgf=1;
								avg_hvtg=0;
								avg_psvtg=0;
								avg_pscur=0;
								measured_hvtg=0;
								measured_psvtg=0;
								measured_pscur=0;
								avgcntr=0;
								EEPROM_Erase_Write((2*2),resistance);
							}
				 		}
				 		Prevkeyans=Keyans;
			  		}
		  		}
	      }
	}   
return(0);
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
		OCV_FLAGLAT=0;                                     // OCV OFF
}
    
void Portpin_init()
{
	ARCONIO=0;
	CCCVIO=0;		
	MODELSELIO =1;
	MODELSEL1IO =1;	
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
	T4CONbits.TON=1;	//strat the timer
}
void pwm_init()
{
	OC1CON=0;			//Turn off output compare module 1
	OC1RS=0;			//write duty cycle biffer register
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
    OC1RS=0;//1000.0;   //fixed pwm
	OC2RS=0;//1000.0;   //fixed pwm	
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
	ADCON2bits.SMPI = 5;//m3;	// interrupt after every 6th sample one sample from each channel 	
	ADCON2bits.BUFM = 0;		// buffer configure as one 16-word buffer 	
	ADCON2bits.ALTS = 0;		// always use MUX A input multiplexer settings 	
	ADCON3bits.SAMC = 1;   		//@PREV:4 NOW:1     m10;  //10 now 10 TAD
	ADCON3bits.ADRC = 0;		//AD conversion clock source from system clock 
	ADCON3bits.ADCS = 19;  		//@PREV:39 NOW:19		//10 modified on 12-8-2016
	ADCHSbits.CH0NA = 0;		// -ve input is Vref- 
	IFS0bits.ADIF = 0;			// clear A to D conversion complete flag 
	IEC0bits.ADIE = 1;			// enable A to D conversion interrupt 
	ADCON1bits.ADSIDL =0;       // Continue module operation in Idle mode
    ADCON1bits.ADON = 1;		// on adc 
	ADCON1bits.ASAM = 1;		// Auto sample / conversion start 
}

void uart_init() 					//38400 baud rate
{
   U1BRG=190;                    	//190---9600 //96 for 4800 baud rate {[((7.37 * 1000000*16)/4)/9600]/16}- 1;
   U1MODE=0X8800;               	//uart enable,00 = 8-bit data, no parity ,0=1 Stop bit/operation in idle mode
   IFS0bits.U1RXIF = 0;         	//clear flag
   U1STAbits.UTXEN=1;           	//Uart transmit enable
   IEC0bits.U1RXIE=1;           	//Uart reception interrupt enable	

   U2BRG=190;                           //190 ----9600	//48, 190;  //48 for 38400 baud rate, and 190 for 4800 baud rate {[((7.37 * 1000000*8)/4)/4800]/8}- 1;
   U2MODE=0X8800;               	// uart enable	//00 = 8-bit data, no parity /0=1 Stop bit/operation in idle mode
   IFS1bits.U2RXIF = 0; 
   U2STAbits.UTXEN=1;           	//Uart transmit enable
   IEC1bits.U2RXIE=1;           	//Uart reception interrupt enable	38400 baud rate
}

void trans_head(unsigned char data)  //Transmit data to saw head in SAW mode
{
   while(U1STAbits.UTXBF == 1);	
   U1TXREG=data;
}

void trans(unsigned char data)  //Transmit data to saw head in SAW mode
{
   while(U2STAbits.UTXBF == 1);	
   U2TXREG=data;
}

void data_head(void)
{
   unsigned char higher=0,lower=0;
   unsigned int transdata;
   transchksum=0x00;
   transdata=dispweldcurrent;       		//Welding current
   trans_head('$');
   lower=transdata;
   transchksum=transchksum+lower; 
   trans_head(lower);
   higher=transdata >> 8;
   transchksum=transchksum+higher;
   trans_head(higher);
   transchksum=transchksum+trip_status;
   trans_head(trip_status);     		//Trip status
   trans_head(transchksum);         	//Checksum
}

void trip(void)
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
 else if(weldcurrent >=2000 && overflag==1)
{
	  	       /*OCV_FLAGLAT	=0;          		//OCV ON
	  	       TRIPLEDLAT=1;*/
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
	    TRIPLEDLAT=0;
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
    MMALEDLAT=1;
    SAWLEDLAT=1;
    TRIPLEDLAT=1;
    REMOTELEDLAT=1;
    poweron_flag=1;
    delay(1000);
    MMALEDLAT=0;
    SAWLEDLAT=0;
    TRIPLEDLAT=0;
    REMOTELEDLAT=0;
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
    VOLT[2]='4';
    VOLT[3]='7';	
    Typedp.digitdp7 = 1;
    cali_flag=1;
    poweron_flag=0;
    delay(7000);
    Typedp.digitdp7 = 0;
    cali_flag=0;
    cLockfg = 1;
    return;
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

unsigned int model_select(void)
{
	int tem,tem1=1,tem2;
	char encoder,cTest=0;
	tem1 = ENCODERSW;

	for (tem=0;tem<1000;tem++);
	
//	if((ENCODERSW == tem1) && (ENCODERSW == 0))
//	{				
		//while(1)
		//{
		    if((MODELSEL==0)&&(MODELSEL1==1))
		    {
			    CURR[0]='C';
			    CURR[1]='H';
			    CURR[2]='M';
			    CURR[3]='P';						//CHAMP 800  => cModel=1
			    VOLT[0]='0';
			    VOLT[1]='8';
			    VOLT[2]='0';
			    VOLT[3]='0';
			    iSetAmpLimit = tem2 = 800;
			}
			else if((MODELSEL==1)&&(MODELSEL1 ==1))
		    {
			    CURR[0]='C';
			    CURR[1]='H';
			    CURR[2]='M';
			    CURR[3]='P';						//CHAMP 1200 => cModel=0
			    VOLT[0]='1';
			    VOLT[1]='2';
			    VOLT[2]='0';
			    VOLT[3]='0';
			   iSetAmpLimit = tem2 = 1200;
			}				 
		   	else if((MODELSEL==0)&&(MODELSEL1 ==0))
		    {
			    CURR[0]='0';
			    CURR[1]='6';
			    CURR[2]='0';
			    CURR[3]='0';						//CHAMP 1200 => cModel=0
			    VOLT[0]='0';
			    VOLT[1]='0';
			    VOLT[2]='0';
			    VOLT[3]='0';
			   iSetAmpLimit = tem2 = 600;
			}
		    
//		    encoder=scanencoder();
//		    if(encoder == '+')
//		    {
//			    cTest = '+';
//			    if(cModel == 1)
//			    	cModel = 0;
//			    else
//			    	cModel = 1;
//		    }
//		   else if(encoder =='-')
//		    {
//		    	cTest = '-';			    
//			    if(cModel == 1)
//			    	cModel = 0;
//			    else
//			    	cModel = 1;
//		    }			    
//		    
//		    tem1 = ENCODERSW;
//		    
		   // for(tem=0;tem<2000;tem++);
		    delay(7000);
//		    
//		    
//		    if(cTest == '+' || cTest == '-')
//		    {
//		    	if((ENCODERSW == tem1) && (ENCODERSW == 0))
//		    	{
//			    	EEPROM_Erase_Write((4*2),tem2);
//			    	EEPROM_Erase_Write((8*2),iSetAmpLimit);
//			    	break;
//				}
//			}    				
	//	}
//	}
	
	//tem2=EEPROM_Read(4*2)
	
	/*if((tem2 !=800) && (tem2 != 1200))
	{
		iSetAmpLimit = tem2 = 1200;
		
		EEPROM_Erase_Write((4*2),tem2);
		EEPROM_Erase_Write((8*2),iSetAmpLimit);
	}
	
	iSetAmpLimit = EEPROM_Read(8*2);*/
		
	return tem2;
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
	TORCHSWIO	=1;
	INCHSWIO	=1;
	MOVLDIO		=1;
	TMODESWIO	=1;
	GASCHKSWIO	=1;
	
	if(kpressread==0)
	{
		torchstatus1	=TORCHSW;
		inchstatus1		=INCHSW;
		movldstatus1	=MOVLD;
		tmodestatus1	=TMODESW;
		gaschkstatus1	=GASCHKSW;
		kpressread=1;
		//trans('1');	
		//trans(movldstatus1);
		//trans(gaschkstatus1);	

	}
	else if(kpressread==1)
	{
		torchstatus2	=TORCHSW;
		inchstatus2		=INCHSW;
		movldstatus2	=MOVLD;
		tmodestatus2	=TMODESW;
		gaschkstatus2	=GASCHKSW;

		//trans('2');	
		//trans(movldstatus2);
		//trans(gaschkstatus2);

		tans		=(torchstatus1	==	torchstatus2 	? 1:0);
		ians		=(inchstatus1	==	inchstatus2 	? 1:0);
		movdans		=(movldstatus1	==	movldstatus2 	? 1:0);
		tmodeans	=(tmodestatus1	==	tmodestatus2 	? 1:0);
		gaschkans	=(gaschkstatus1	==	gaschkstatus2 	? 1:0);
		
		if(tans==1)
		{
			Torchkey 	=(torchstatus2	==	1 	? 'P':'R');
		}
		if(ians==1)
		{
			Inchkey		=(inchstatus2	==	1 	? 'P':'R');
		}
		if(movdans==1)
		{
			Motorerr	=(movldstatus2	==	1 	? 'N':'E');
		}
		if(tmodeans==1)
		{
			Torchmode	=(tmodestatus2	==	1 	? '2':'4');
		}
		if(gaschkans==1)
		{
			Gasonkey	=(gaschkstatus2	==	1 	? 'R':'P');
		}
		
		//trans('=');
		//trans('T');
		//trans(Torchkey);
		//trans('I');
		//trans(Inchkey);
		//trans('M');
		//trans(Motorerr);
		//trans('t');
		//trans(Torchmode);
		//trans('G');
		//trans(Gasonkey);
		kpressread=0;
	}	
}


	

	  