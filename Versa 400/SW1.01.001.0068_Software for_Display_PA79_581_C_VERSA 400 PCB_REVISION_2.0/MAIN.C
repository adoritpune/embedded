///***********************MODIFICATION DETAILS***************************************************************************
//***********************************************************************************************************************
//    Date    	REV. No   	DONE BY      		DESCRIPTION
// 01/01/2019 	REV-1.0		Akshay Nirgude		Added new function to store the max cnt for voltage.
//                                  			also did changes in KEYPAD.C
//												ARCLENGTH RECEIVED VARIABLE DISABLED IN ISR
//NEW MODE CV FOR BASE & PULSE CV
//AFTER INDIANA GREETING VISIT 01.11.2017 DIWALI
//********************************************************************************************************************
#include "stdio.h"
#include "libpic30.h"
#include "p30f6014A.h"
#include "math.h"
#include "dsp.h"
#include "pid.c"
#include "float.h"
#include "stdlib.h"

#include "DEFINE.C"
#include "STRUCTURE400.C"
#include "VARIABLE.C"
#include "FUNCTION.C"
#include "LCDARRAY.C"
#include "TESTEEPROM.C"

#include "ISR2.C"
#include "DISPLAY.C"
#include "KEYPAD.C"
#include "MMA.C"
#include "TIG.C"
#include "MIG.C"

#include "TORCHCYCLE.C"

_FOSC(CSW_FSCM_OFF & FRC_PLL16);  		  	//FAIL SAFE CLOCK SWITCHING IS OFF AND OPERATING FREQUENCY FCY=16MHZ
_FWDT(WDT_OFF);                 		  	//WATCH DOG TIMER 0FF
_FGS(CODE_PROT_ON);            		  	//CODE PROTECTION DISABLED
_FBORPOR(MCLR_EN & PBOR_ON & PWRT_64 & BORV_27); 	//rev1.2 brown out at 2.7volt

int main()
{
	//PORTPIN_INIT();
	SHDNLAT = 1;		//OCV ON
	SYSTEM_INIT();	


	i=786;
    //OC4RS=0;
   	TRIP_LEDLAT=1;
 	
	TypeU.LEDGROUP[0]=0xFF;
	TypeU.LEDGROUP[1]=0xFF;
	TypeU.LEDGROUP[2]=0xFF;
	TypeU.LEDGROUP[3]=0xFF;
	TypeDP.DPGROUP[0]=0x00;
  //Typedp.digitdp1	=1;



/*Read welding mode store at Zeroth location*/      
	memoryzone='X';
	eedata=EEPROM_Read(0*2);
	weldmode=eedata;

	eedata1=EEPROM_Read(6*2);
	//if(eedata1 <= 2)
	//eedata1 = 2;	
	cModel_Select = eedata1;
	/*
	eedata2=EEPROM_Read(8*2);
	iWS_Min_Count = eedata2;
	
	eedata3=EEPROM_Read(10*2);
	iWS_Max_Count = eedata3;
	
	eedata4=EEPROM_Read(12*2);
	iVTG_Min_Count = eedata4;
	
	eedata5=EEPROM_Read(14*2);
	iVTG_Max_Count = eedata5;	
	
	eedata6=EEPROM_Read(16*2);
	iFinal_WS_Count = eedata6;	
	
	eedata7=EEPROM_Read(18*2);
	iFinal_VTG_Count = eedata7;
	*/			
/*********************EEPRROM READ AT START=start************************/
	modechangef=1;
	read_current_status();
	check_eeprom_values();
	

	for(j=0;j<100;j++)
	for(i=0;i<20000;i++); //50000
/*********************EEPRROM READ AT START=end	*******************/
	if(cModeSelectDonefg == 0)
	{
		diswin1[0]	='A';
		diswin1[1]	='D';
		diswin1[2]	='R';
		diswin2[0]	='W';
		diswin2[1]	='L';
		diswin2[2]	='D';
		for(j=0;j<100;j++)
		for(i=0;i<20000;i++); //50000	
		/*		
		diswin1[0]	='R';
		diswin1[1]	='E';
		diswin1[2]	='V';
		diswin2[0]	='0';
		diswin2[1]	='0';
		diswin2[2]	='0';
		Typedp.digitdp4=1;
		for(j=0;j<10;j++)
		for(i=0;i<5000;i++); //50000
		*/
		
		
	    if(cModel_Select == 1)
	    {
		    Typedp.digitdp4=1;
			diswin1[0]='2';
			diswin1[1]='5';
			diswin1[2]='0';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='0';        
	    }
	    else if(cModel_Select == 2)
	    {
		    Typedp.digitdp4=1;
			diswin1[0]='4';
			diswin1[1]='0';
			diswin1[2]='0';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='0';        
	    }
	    else if(cModel_Select == 3)
	    {
		    Typedp.digitdp4=1;
			diswin1[0]='6';
			diswin1[1]='0';
			diswin1[2]='0';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='0';    
	    }
	   	Typedp.digitdp4=0;
	   if(weldmode=='M')//MMA
	   {
			weldmode='M';
			TypeU.LEDGROUP[0]=0x00;
			Type.current	=1;
			Type.voltage	=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.mma		=1;
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
	   }
	   else if(weldmode=='T') //TIG
	   {
			weldmode='T';  //@versa400
			TypeU.LEDGROUP[0]=0x00;
			Type.current		=1;
			Type.voltage		=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.tig			=1;
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;	    
	   }
	   else if(weldmode=='G')//MIG
	   {
			weldmode='G';
			TypeU.LEDGROUP[0]=0x00;
			Type.wirespeed		=1;
			Type.voltage		=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.mig			=1;
			Type.twot			=1;        
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
	
	   }//@versa 
	   else
	   {
			weldmode='G';
			TypeU.LEDGROUP[0]=0x00;
			Type.wirespeed		=1;
			Type.voltage		=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.mig			=1;
			Type.twot			=1;        
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
	   }	
		
	}
	
	
	IFS0bits.ADIF 	  	=  0;		// clear A to D conversion complete flag 
	IEC0bits.ADIE 	  	=  1;		// enable A to D conversion interrupt 
	
	IFS1bits.T5IF=0;	//Clear the Timer5 interrupt status flag
	IEC1bits.T5IE=1;	//Enable Timer5 interrupts
	
	power_on_flag=1;	
	//---------------11/07/2019
	//here we are initializing power on time count to 0;
	pontime.sec = pontime.min = pontime.hr = 0;
	 
	/******Debug Area start****************/
				 
	mig_Kp = 30;//70;//60;//50;//10;//5;			20/70/2/1/5	//10		//1/10/1/4/2
	mig_Ki = 1;//2;//1;//3;//70;//8;//45;//8;//70;				//45
	mig_Kd = 95;//80;//50;//100;//95;//1;//2;					//2
	mig_Ka = 1;//0;//2;						//2
	mig_Kb = 380;//135;//180;//300;//180;//380;						//7
	mig_Kc = 10;//150;//15;//5; //PPC
	
	iPrevSetcurrent=0;

	//Typedp.digitdp5	= 1;
	
	
	key=keypad_read();
	
	if(key=='A')
    {	
	    ADC_Reference();  
		
	    cModeSelectDonefg = 1;
		model_selection();
			
	}
	else
	{
		Typedp.digitdp2=1;
		cModel_Select = 2;	
		diswin1[0]='0';
		diswin1[1]='0';
		diswin1[2]='1';//software rev
		diswin2[0]='4';
		diswin2[1]='0';
		diswin2[2]='0';  
		cModeSelectDonefg==0;
		//iFinal_WS_Count = 400;
		//iFinal_VTG_Count = 360;
		//Typedp.digitdp4=0;		
	}	
	//Typedp.digitdp3=0;
	for(j=0;j<1000;j++)
	for(i=0;i<20000;i++);
		
	while(1)
	{	
						
		if((weldmode=='G') && (cForcefullyOFFOCVfg == 1))
		{
			SHDNLAT	= 0;//1;
		}
					
		ADC_Reference();
		
	//------------11/07/2019
	//here we are sending the data of current and voltage into usb;
		if((load_data_into_usb_fg == 1)&&(usbDataLogStartfg == 1))
		{
		    //write_file_usb();      //changed on 26-10-19 
			load_data_into_usb_fg = 0;
		}
		if((pon_usb_fg==1)&&(cPonCntr == 0))
		{
			//pon_create_file();
			pon_usb_fg = 0;
			iHeaderdly = 60;
			HeaderWrfg = 1;
		}	
		if((HeaderWrfg == 1)&&(iHeaderdly == 0))
		{
			//header_usb();
			HeaderWrfg = 0;
			usbDataLogStartfg = 1;				
		}	
	//here we are checking the analog remote frame
		if(analogFramRxfg == 1)	
		{
			//analogRemoteFrameDecode();
			analogFramRxfg = 0;
		}	
	//------------
		if ((testmigfg==1) && (samplecnt>=150))
		{
			//datafordebug(iTestpeak1);
			testmigfg=0;
			samplecnt =iTestpeak1= iTestpeak2 = iTestpeak3 = 0;	
		}
	//------------
	
		//Toggle_pin();
		if(keyreadf==1)
		{
			key=keypad_read();
			
			keyreadf=0;

			if((key == 'B') && (cSwitchPressfg == 0))
			{		
				cBKeyLockfg=1;		
				cSwitchPressfg = 1;	
			}
		 	else if((cSwitchPressfg == 1) && (keyrelease()))
		 	{		
				if(0)
				{
				}
				else if(0)
				{
				}	
				else 
				{						
					key_application('B'); 
					if(cVoltageoffsetmenufg == 1 && cVoltageoffsetfg == 0)
					{
						cVoltageoffsetmenufg = 0;
					}
				}						
				cSwitchPressfg = 0;
				cBKeyLockfg = 0;
				cEEPROMSavefg = 0;
			}
	
			if((Prevkey!=key) && (cSwitchPressfg == 0))
			{
				password_set_count=0;
				Prevkey=key;
				key_application(key);
			}
						
		}
		
		if(universal_error_flag == 0) 
		{
			if(weldmode == 'G')
			{
				if(cMIGParaMenufg == 1)
				{
					cMIGMenu();	
				}
				else if((cGaSMenufg == 1) && (cVoltageoffsetfg == 0) &&(cMIGParaMenufg == 0))
				{
					cMIGGasMenu();	
				}
				else if(cVoltageoffsetfg == 1)
				{
					cVoltageoffsetMenu();
				}	
			}
			
			if(weldmode == 'M')  //PPC
			{
				if(cVRDMenufg == 1)
				{
					MMAVRDMenu();
				}
			}
		}	
							
			
		if(SCKavgf==1)
		{
			SCKavgf=0;
			
			FLTSCKvtg=(0.9*SCKvtg)+(0.1*prevFLTSCKvtg);//((1.0-0.7)*prevFLTSCKvtg);
		
			if(FLTSCKvtg>=4000)
			   FLTSCKvtg=4000;
			else if(FLTSCKvtg<=0)
				FLTSCKvtg=0;
			prevFLTSCKvtg=FLTSCKvtg;
	    		SCKVOLTAGE=FLTSCKvtg>>2;	//	(adcvtg*10.0)/40.0;//37.0
	    		if(SCKVOLTAGE>500)			//for voltage greater than 100=50V
	    		SCKVOLTAGE=500;
	    		//SCKVOLTAGE=SCKvtg>>2;	    //	(adcvtg*10.0)/40.0;//37.0
			SCKCURRENT=SCKamp*0.135;	//	(adcvtg*10.0)/40.0;//37.0
	
			if(weldmode=='G')
			{			
				if(PULSEavgf==1)
				{
	//				if((PULSEamp>=para.migmode.setcurrent / 3)||(PULSEvtg <= (para.migmode.setvoltage + 20)) && (cSoftDonefg == 0))
					if(cSoftDonefg == 0)
					{
						if(cSoftStrCnt > 200)
						{
							IRCreepcurr = 0;
							iStartSetVoltCnt = 0;
							cStartPulsefg = 0;					
							cSoftStrCnt  = 0;
							cSoftStrfg = 0;	
							cSoftDonefg = 1;						
						}													
					}
					if(0)//PULSEamp >= 74)//&& (cPIDtriggerfg == 1))//74
					{
						MIGweldon_detectf = 1;
						if(cCreepSpeedDowncntfg == 0)
						{
							//cCreepSpeedDowncntfg=1;
						}		
						
						//iDummyvoltageref = 400;//Recall_location * 10;
						//iStepforStartVoltRef = (iDummyvoltageref - para.migmode.setvoltage)/3;																	
					}						
					//else if(PULSEamp<35)//&& PULSEvtg>=2400) // 2400=60v //3000)//vtg >75V //16.11.2017
					//	MIGweldon_detectf=0;
					PULSEavgf=0;	
				}
			}		
		}
					
		if(DISPavgf==1)
		{
			CURRENT	=DISPamp*0.135;//	(adccur*5.0)/37.0;
			//VOLTAGE	=(DISPvtg>>2)*0.95;	//	(adcvtg*10.0)/40.0;//37.0
			VOLTAGE	=(DISPvtg>>2);	//	(adcvtg*10.0)/40.0;//37.0
			//TRIPVTG1=DISPerr1*0.270; //	(adctripvtg*10.0)/37.0;
			//TRIPVTG2=DISPerr2*0.270;	
            if(0)//cRecordVRDONvtg == 1)
            {
                iSampleVRDvtgcnt++;
                if(iSampleVRDvtgcnt >= 2)
                {
                    iActualVRDvtgON = VOLTAGE;
                    cRecordVRDONvtg = 0;
                    iSampleVRDvtgcnt = 0;
                }
            }
            	
			cCurrFBUpdatefg = 1;
			cVtgFBUpdatefg = 1;
			DISPavgf=0;
	
			if(weldmode=='M')
			{
				if(CURRENT>=WELDON_START_CURR_MMA) 
				{
					weldonf=1;
				}
				else
				{
					weldonf=0;
					cHotfg=1;
					//disp_hex_dec_curr(iSetcurrent);
				}			
			}
				
			if(weldmode=='T')
			{
				if(CURRENT>=WELDON_START_CURR_TIG) 
				{
					weldonf=1;
				}
				else
				{
					weldonf=0;
					//disp_hex_dec_curr(iSetcurrent);
				}	
			}
			
			if(weldmode == 'G')
			{
				if((CURRENT >= HSAMP_CNT) && (weldcyclestrt == 0))
				{
					er5++;
			
					if(er5 > ER_DEBOUNCE_TIME)
					{
						HS_errorf 	= 1;
						er5			= ER_DEBOUNCE_TIME;
					}
				}
				else
				{  
					HS_errorf = 0;    
					er5 	  = 0;
				}			
			}
			
			if(VOLTAGE>=999)
			VOLTAGE=999;
		}
	
	//******************************************Password Setting******************************************************************************
		
	//************************************************************************************************************************
		if(weldmode=='M' && universal_error_flag==0)
		{
			MMAWELD();
		}
	//*********************************************************************************************************************************************
		else if(weldmode=='T' && universal_error_flag==0)
		{		 
			TIGWELD();	
		}
	//*********************************************************************************************************************************************
		else if(weldmode=='G' && universal_error_flag==0)
		{
			MIGWELD();
		}
			
		Detect_error();
			
	}//while
}//main file

inline void delay_mig_torch()
{
	unsigned int i;
	for(i=0;i<=50000;i++);
}



void SYSTEM_INIT()
{
	PORTPIN_INIT();
	TIMER1_INIT();
 	//TIMER3_INIT();
	TIMER4_INIT();	
	//TIMER5_INIT(); 
	ADC_INIT();
	//UART1_INIT();
	//UART2_INIT();
	SPI_INIT();
 	PWM_INIT();
}


void SPI_INIT(void)
{
  DACCSLAT	=0;
  IFS1bits.SPI2IF=0;                    	/*CLEAR FLAG*/
  IEC1bits.SPI2IE=1;                   	/*ENABLE INTERRUPT*/
  IPC6bits.SPI2IP=1;
  SPI2CONbits.FRMEN=0;           		/*FRAME MODE SUPPORT DISABLED*/
  SPI2CONbits.DISSDO=0;                	/*SDO PIN IS CONTROLLED BY MODULE*/
  SPI2CONbits.MODE16=1;               	/*16 BIT SUPPORTED*/
  SPI2CONbits.SMP=0;                   	/*INPUT IS SAMPLED AT MIDDLE OF DATA OUTPUT TIME*/
  SPI2CONbits.CKE=0;				/*DATA CHANGES WHEN HIGH TO LOW PULSE*/
  SPI2CONbits.SSEN=0;				/*CONTROLLED BY PORT PIN*/
  SPI2CONbits.CKP=1;				/*IDLE CLOCK*/
  SPI2CONbits.MSTEN=1;                 /*MASTER MODE*/
  SPI2CONbits.SPRE=6;//6;//2;//0;               /*SECONDARY PRESCALE 3:1 SO FSPI=5MHZ*/
  SPI2CONbits.PPRE=3;//2;//0;               /*PRIMARY PRESCALE 1:1*/
  SPI2STATbits.SPIROV=0;
  
  SPI2STATbits.SPISIDL=0;              /*CONTINUE ON IDEAL MODE*/
  SPI2STATbits.SPITBF=0;               /*TRANSMITT BUFFER EMPTY*/
  SPI2STATbits.SPIEN=1;                 /*ENABLE OR DISABLE MODULE*/
  
 SPI2BUF=0X7000;///7FF;
}
void TIMER1_INIT(void)
{
	T1CON			=0;			//Stops the Timer1 and reset control reg.
	TMR1			=0;			//Clear contents of the timer register
	PR1				=29387;     //1 ms 0X6000;	//Load the Period register with the value 0xFFFF 0x72cb interrupt after every 1.20msec
	IPC0bits.T1IP	=1;			//Setup Timer1 interrupt 
	IFS0bits.T1IF	=0;			//Clear the Timer1 interrupt status flag
	IEC0bits.T1IE	=1;			//Enable Timer1 interrupts
	T1CONbits.TON	=1;			//strat the timer
}
/*
void TIMER2_INIT(void)
{
	T2CON			=0;			//Stops the Timer1 and reset control reg.
	TMR2			=0;			//Clear contents of the timer register
	PR2				=1470;      //3600;//120usec 1470;//2948;//1470;//29387;     //1 ms 0X6000;	//Load the Period register with the value 0xFFFF 0x72cb interrupt after every 1.20msec
	IPC1bits.T2IP	=1;			//Setup Timer1 interrupt 
	IFS0bits.T2IF	=0;			//Clear the Timer1 interrupt status flag
	IEC0bits.T2IE	=0;			//Enable Timer1 interrupts
	T2CONbits.TON	=0;			//strat the timer
}
*/


void TIMER3_INIT(void)
{
	T3CON			=0;			//Stops the Timer1 and reset control reg.
	TMR3			=0;			    //Clear contents of the timer register
	PR3				=1470;			//1470;   // for 50usec //0x0B84; //0xB84=2948=100usec; 0x024B=587=20usec//0x72CB=29387=1msec;	//Load the Period register with the value 0xFFFF
	IPC1bits.T3IP	=1;	//Setup Timer1 interrupt 
	IFS0bits.T3IF	=0;	//Clear the Timer1 interrupt status flag
	IEC0bits.T3IE	=0;	//Enable Timer1 interrupts
	T3CONbits.TON	=1;	//start the timer
}

void TIMER4_INIT(void)
{
	T4CON			=0;			//Stops the Timer1 and reset control reg.
	TMR4			=0;			//Clear contents of the timer register
	PR4				=1470;  //100;		//1470;		//0X7500;	//Load the Period register with the value 0xFFFF 0x72cb interrupt after every 1.20msec
	IPC5bits.T4IP	=1;			//Setup Timer1 interrupt 
	IFS1bits.T4IF	=0;			//Clear the Timer1 interrupt status flag
	IEC1bits.T4IE	=1;			//Enable Timer1 interrupts
	T4CONbits.TON	=1;			//strat the timer
}
void TIMER5_INIT(void)
{
	T5CON	=0;		//Stops the Timer1 and reset control reg.
	TMR5	=0;		//Clear contents of the timer register
	PR5		=1470;  //1400;//293;//586;   //732;//2930;//293;//29387;//293;//0x0B84;//293=10USEC	//0xB84=2948=100usec; 0x024B=587=20usec//0x72CB=29387=1msec;	//Load the Period register with the value 0xFFFF
	IPC5bits.T5IP=7;//1;	//Setup Timer1 interrupt 

	T5CONbits.TON=1;	//strat the timer
}	


void PWM_INIT(void)
{
	OC4CON				=0;			//Turn off output compare module 1    //@versa400
	OC4RS				=0;			//write duty cycle biffer register
	OC4R				=0;			//write to initial duty cycle value
	OC4CONbits.OCM		=6;			//output compare is configured as pwm generated
		
	T2CON			=0;			//Stops the Timer1 and reset control reg.
	TMR2			=0;			//Clear contents of the timer register
	PR2				=1949;		//1470;      //3600;//120usec 1470;//2948;//1470;//29387;     //1 ms 0X6000;	//Load the Period register with the value 0xFFFF 0x72cb interrupt after every 1.20msec
	IPC1bits.T2IP	=0;			//Setup Timer1 interrupt 
	IFS0bits.T2IF	=0;			//Clear the Timer1 interrupt status flag
	IEC0bits.T2IE	=0;			//Enable Timer1 interrupts
	T2CONbits.TON	=1;			//start the timer
}

void ADC_INIT(void)
{
	ADPCFG 				= 0xFFFF;	// all port B pin as digital input pin
	ADPCFGbits.PCFG2 	= 0;		// port B.2 as analog (CURRENT FEEDBACK) input pin  
	ADPCFGbits.PCFG3 	= 0;		// port B.3 as analog (VOLTAGE FEEDBACK) input pin  
	ADPCFGbits.PCFG4 	= 0;		// port B.4 as analog (MOTOR FEEDBACK VOLTAGE) input pin 
	ADPCFGbits.PCFG5 	= 0;		// port B.8 as analog (TRIP1 VOLTAGE) input pin 
	ADPCFGbits.PCFG7 	= 0;		// port B.8 as analog (TRIP2 VOLTAGE) input pin
	ADPCFGbits.PCFG8 	= 0;		// port B.8 as analog (MIG VOLT REFERENCE) input pin  
	ADPCFGbits.PCFG9 	= 0;		// port B.9 as analog (MIG CURR REFERENCE) input pin 
	ADPCFGbits.PCFG10 	= 0;		// port B.10 as analog (CRATER WS/SETCURRENT) input pin 
	ADPCFGbits.PCFG12 	= 0;		// port B.12 as analog (INDUCTANCE/HOTSTART) input pin 
	ADPCFGbits.PCFG13 	= 0;		// port B.13 as analog (CRATER VOLT/ARCFORCE) input pin 
	ADPCFGbits.PCFG14 	= 0;		// port B.14 as analog (REMOTE VOLTAGE) input pin

	ADCSSL 				= 0x0000;	// skip all analog channels for input scanning
    ADCSSLbits.CSSL2 	= 1;		// select AN2 (CURRENT FEEDBACK) for input scanning //BUF0
	ADCSSLbits.CSSL3 	= 1;		// select AN3 (VOLTAGE FEEDBACK) for input scanning //BUF1
	ADCSSLbits.CSSL4 	= 1;		// select AN4 (MOTOR FEEDBACK VOLTAGE) for input scanning 
	ADCSSLbits.CSSL5 	= 1;		// select AN4 (TRIP1 VOLTAGE) for input scanning 
	ADCSSLbits.CSSL7 	= 1;		// select AN8 (TRIP2 VOLTAGE) for input scanning //BUF2
	ADCSSLbits.CSSL8 	= 1;		// select AN8 (MIG VOLT REFERENCE) for input scanning //BUF2
	ADCSSLbits.CSSL9 	= 1;		// select AN9 (MIG CURR REFERENCE) for input scanning //BUF3
	ADCSSLbits.CSSL10 	= 1;		// select AN10 (CRATER WS/SETCURRENT) for input scanning //BUF4
	ADCSSLbits.CSSL12 	= 1;		// select AN12 (INDUCTANCE/HOTSTART) for input scanning //BUF5
	ADCSSLbits.CSSL13 	= 1;		// select AN13 (CRATER VOLT/ARCFORCE) for input scanning //BUF6
	ADCSSLbits.CSSL14 	= 1;		// select AN14 (REMOTE VOLTAGE) for input scanning //BUF2

	ADCON1bits.FORM 	= 0;		// data output format in unsigned integer 
	ADCON1bits.SSRC 	= 7;		// internal counter ends sampling and starts conversion 
	ADCON2bits.VCFG 	= 0;		// setup adc voltage reference source AVdd & AVss 	
	ADCON2bits.CSCNA 	= 1;		// scan inputs 	
	ADCON2bits.SMPI 	= 12;        //4;        //3;// interrupt after 4 samples 	
	ADCON2bits.BUFM 	= 0;		// buffer configure as one 16-word buffer 	
	ADCON2bits.ALTS 	= 0;		// always use MUX A input multiplexer settings 	
	ADCON3bits.SAMC 	= 1;//1;//4;  	//  4 now 4 TAD //1; auto sample time bit = 1Tad //1=TAD,4=4 TAD,6=6 TAD
	ADCON3bits.ADRC 	= 0;		// AD conversion clock source from system clock 
	ADCON3bits.ADCS 	= 19;//39;
	ADCHSbits.CH0NA 	=  0;		// -ve input is Vref- 
	IFS0bits.ADIF 	  	=  0;		// clear A to D conversion complete flag 
	IEC0bits.ADIE 	  	=  1;		// enable A to D conversion interrupt 
	ADCON1bits.ADON 	=  1;		// on adc 
	ADCON1bits.ASAM 	=  1;		// Auto sample / conversion start 
}

/*
void UART1_INIT()
{
  	U1BRG=48;//780;//16;   //48;//780;    //194= 9600 BAUD RATE , 780=2400   48=38400  16=115200 92 = 19200
  	U1MODE=0X8800;                               		// uart enable	//00 = 8-bit data, no parity /0=1 Stop bit/operation in idle mode
  	IFS0bits.U1RXIF = 0; 
  	U1STAbits.UTXEN=1;                           		//Uart transmit enable
  	IEC0bits.U1RXIE=1;                             		//Uart reception interrupt enable
}
void UART1_INIT_REMOTE()
{
  	U1BRG=194;//780;//16;   //48;//780;    //194= 9600 BAUD RATE , 780=2400   48=38400  16=115200 92 = 19200
  	U1MODE=0X8800;                               		// uart enable	//00 = 8-bit data, no parity /0=1 Stop bit/operation in idle mode
  	IFS0bits.U1RXIF = 0; 
  	U1STAbits.UTXEN=1;                           		//Uart transmit enable
  	IEC0bits.U1RXIE=1;                             		//Uart reception interrupt enable	
}
void TRANS1(unsigned char data)
{
	while(U1STAbits.UTXBF == 1);	
	U1TXREG=data;
}

void TRANSNUM(unsigned int num)
{
	unsigned char lower=0,higher=0;
	lower=num;
	higher=(num>>8);
	TRANS1(higher);
	TRANS1(lower);
}

void UART2_INIT()
{
  	U2BRG=194;                                       	//9600 BAUD RATE
  	U2MODE=0X8800;                               		// uart enable	//00 = 8-bit data, no parity /0=1 Stop bit/operation in idle mode
  	IFS1bits.U2RXIF = 0; 
 	IEC1bits.U2RXIE=1;                             		//Uart reception interrupt enable
  	IEC1bits.U2TXIE=1;                             		//Uart reception interrupt enable
   	U2STAbits.UTXEN=1;                           		//Uart transmit enable
}

void TRANS2(unsigned char data)
{
	while(U2STAbits.UTXBF == 1);	
 	U2TXREG=data;
}

void Send_num(unsigned int num)
{
	unsigned char higher=0,lower=0;	
	TRANS2('@');
	lower=num;
	higher=num >> 8;
	TRANS2(higher);
	TRANS2(lower);
	TRANS2(0x0D);
	TRANS2(0x0A);
}
*/
void PORTPIN_INIT()
{
	DECODEAIO		= 0;
	DECODEBIO		= 0;
	DECODECIO		= 0;
	
	LEDGP3IO 		= 0;
	LEDGP4IO 		= 0;  

	SEGAIO			= 0;
	SEGBIO			= 0;
	SEGCIO			= 0;
	SEGDIO			= 0;
	SEGEIO			= 0;
	SEGFIO			= 0;
	SEGGIO			= 0;
	SEGDPIO	    	= 0;

	ROW1IO			= 1;
	ROW2IO			= 1;
	ROW3IO			= 1;
	ROW4IO			= 1;
	
	COLUMN1IO 		= 1;
	COLUMN2IO 		= 1;
	COLUMN3IO 		= 1;


	DACSCKIO		= 0;
	DACSDIIO		= 1;
	DACSDOIO 		= 0;
	DACCSIO			= 0;
	MIG_TORCHIO 	= 1;
 	INCHIO 			= 1;

	DECOD_ENIO		= 0;

	GASWATERIPIO	= 1;
	PRESSERRIPIO	= 1;

	SHDNIO			= 0;
	TRIP_LEDIO  	= 0;
	MPWMIO			= 0;
	//MPWM = 0;
	//default state of portpin
	DECODEALAT		= 0;
	DECODEBLAT		= 0;
	DECODECLAT		= 0;
	
	LEDGP3LAT 		= 0;
	LEDGP4LAT 		= 0;  

	SEGALAT			= 0;
	SEGBLAT			= 0;
	SEGCLAT			= 0;
	SEGDLAT			= 0;
	SEGELAT			= 0;
	SEGFLAT			= 0;
	SEGGLAT			= 0;
	SEGDPLAT		= 0;
	
	DACSCKLAT	   	= 0;
	DACSDOLAT		= 0;
	DACCSLAT		= 0;
	
	VRD_SWITCHIO 	= 1;
    TORCHIPIO    	= 1;  
    GAS_RELAYIO 	= 0;
	MTR_TRIPIO   	= 1;
	DECOD_ENLAT	 	= 0;

}


void INT12_INIT(void)
{
   INTCON2=0X00;
   INTCON2bits.INT1EP=1;         //0 POSITIVE EDGE
   IFS1bits.INT1IF=0;              //
   IPC4bits.INT1IP=1;            //PRIORITY
   IEC1bits.INT1IE=0;//1;              //voltage ENABLE INTERRUPT
   Vweldon_detectf=0;            //

   INTCON2bits.INT2EP=1;         //0 POSITIVE EDGE
   IFS1bits.INT2IF=0;            //
   IPC5bits.INT2IP=1;            //PRIORITY
   IEC1bits.INT2IE=0;//1;            //current ENABLE INTERRUPT
   Aweldon_detectf=0;            //
}

void trip_detection(unsigned int looperrorvtg)
{
 
	looperrorvtg = iTrip1vtg;
	iErr1=looperrorvtg;
    if((looperrorvtg > UV_1) && (looperrorvtg < UV_2))      //UV
	{
        er1++;
        er3=0;
        er4=0;

		if(er1>ER_DEBOUNCE_TIME)
		{
            UV_errorf=1;						   
            TH_errorf=0;
				
            NO_ERROR_CONNECTOR_fg=0;			   
            er1=ER_DEBOUNCE_TIME;
	
		}
	}
	else if((looperrorvtg > TH_1) && (looperrorvtg < TH_2))       //TH
	{
        er1=0;
        er3++;
        er4=0;
		
		if(er3>ER_DEBOUNCE_TIME)
		{		
            UV_errorf=0;
            TH_errorf=1;
            NO_ERROR_CONNECTOR_fg=0;

            er3=ER_DEBOUNCE_TIME;
		}
	}
    else if(looperrorvtg < NO_ERR_CONNECTOR_2)
    {
        if(count_3s>=100)
        {
            count_3s=0;
            
            er4++;
            er3=0;
            er1=0;        
            if(er4>ER_DEBOUNCE_TIME)
            {
	            UV_errorf=0;
	            TH_errorf=0;
	            NO_ERROR_CONNECTOR_fg=1;

                er4=ER_DEBOUNCE_TIME;
            }
        }
        
    }
	else
	{
        UV_errorf=0;
        TH_errorf=0;
        NO_ERROR_CONNECTOR_fg=0;
        
        er1=0;
        er3=0;
        er4=0;

	}	   
}

void trip1_detection(unsigned int errvtg)
{
	errvtg = iTrip2vtg;
	iErr2=errvtg;
	if((errvtg >= OV_1) && (looperrorvtg <= OV_2)) 
	{
		er2++;

		if(er2 > ER_DEBOUNCE_TIME)
		{
			OV_errorf  = 1;
			er2		   = ER_DEBOUNCE_TIME;
		}
	}
	else
	{
        OV_errorf = 0;    
        er2 	  = 0;
	}	
}	

void Detect_error(void)
{
	//trip_detection(iTRIPVTG1);
	//trip1_detection(iTRIPVTG2);
	
	if((universal_error_flag == 1) && (universal_error_latch == 0) && ((TORCH_SW=='T') || (weldcyclestrt==1))) 
	{
		universal_error_latch=1;
	}
	else if((universal_error_latch == 1) && (TORCH_SW!='T'))	
	{
		universal_error_latch=0;
		universal_error_flag=0;
		weldcyclestrt=0;
	}	
	 
	if(UV_errorf == 1)
    {
		Typedp.digitdp5	= 0;
		Typedp.digitdp2	= 0;
		if((cFlashCntr == 0) && (cFlashfg == 1))
		{
			
			diswin1[0]='E';
			diswin1[1]='R';
			diswin1[2]='R';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='1';
            cFlashfg = 0;
            cFlashCntr = 500;	
									
			universal_error_flag=1;	
			dispupdatef=1;	
		}
		else if((cFlashCntr == 0) && (cFlashfg == 0))
		{
			no_display_fg = 1;
		}
	}
	else if(OV_errorf==1)
	{	
		Typedp.digitdp5	= 0;
		Typedp.digitdp2	= 0;		 
		if((cFlashCntr == 0) && (cFlashfg == 1))
		{
			
			diswin1[0]='E';
			diswin1[1]='R';
			diswin1[2]='R';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='2';
            cFlashfg = 0;
            cFlashCntr = 500;
           
			universal_error_flag=1;	
			dispupdatef=1;
		}
		else if((cFlashCntr == 0) && (cFlashfg == 0))
		{
			no_display_fg = 1;
		}
	}
	else if(TH_errorf==1)
	{
		Typedp.digitdp5	= 0;
		Typedp.digitdp2	= 0;
		if((cFlashCntr == 0) && (cFlashfg == 1))
		{
			
			diswin1[0]='E';
			diswin1[1]='R';
			diswin1[2]='R';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='3';
	        cFlashfg = 0;
	        cFlashCntr = 500;	      	        
			universal_error_flag=1;	
			dispupdatef=1;
		}
		else if((cFlashCntr == 0) && (cFlashfg == 0))
		{
			no_display_fg = 1;
		}
 	}
	else if((ERROR_4_errorf==1) && (weldmode=='G'))
	{
		Typedp.digitdp5	= 0;
		Typedp.digitdp2	= 0;
		if((cFlashCntr == 0) && (cFlashfg == 1))
		{			
			diswin1[0]='E';
			diswin1[1]='R';
			diswin1[2]='R';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='4';
	        cFlashfg = 0;
	        cFlashCntr = 500;
	        if(Type.twot==1)
	        {	
				error_4_check4t=0;
				error4_flag=0;
				ERROR_4_errorf=0;
			}         	        
			universal_error_flag=1;	
			dispupdatef=1;
		}
		else if((cFlashCntr == 0) && (cFlashfg == 0))
		{
			no_display_fg = 1;
		}					
	}
	else if(Motor_OverLoad_errorf==1)
	{
		Typedp.digitdp5	= 0;
		Typedp.digitdp2	= 0;
		if((cFlashCntr == 0) && (cFlashfg == 1))
		{
			diswin1[0]='E';
			diswin1[1]='R';
			diswin1[2]='R';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='5';
            cFlashfg = 0;
            cFlashCntr = 500;
			universal_error_flag=1;	
			dispupdatef=1;
		}
		else if((cFlashCntr == 0) && (cFlashfg == 0))
		{
			no_display_fg = 1;
		}
	}
	else if((WireFeeder_errorf==1) && (weldmode == 'G'))
	{
		Typedp.digitdp5	= 0;
		Typedp.digitdp2	= 0;
		if((cFlashCntr == 0) && (cFlashfg == 1))
		{
			diswin1[0]='E';
			diswin1[1]='R';
			diswin1[2]='R';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='6';
            cFlashfg = 0;
            cFlashCntr = 500;
            //WireFeeder_errorf=0;
			universal_error_flag=1;	
			dispupdatef=1;
		}
		else if((cFlashCntr == 0) && (cFlashfg == 0))
		{
			no_display_fg = 1;
		}	
	}
	else if(pressure_error_flag==1)
	{
		Typedp.digitdp5	= 0;
		Typedp.digitdp2	= 0;
		if((cFlashCntr == 0) && (cFlashfg == 1))
		{
			diswin1[0]='E';
			diswin1[1]='R';
			diswin1[2]='R';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='7';
            cFlashfg = 0;
            cFlashCntr = 500;
			universal_error_flag=1;	
			dispupdatef=1;
		}
		else if((cFlashCntr == 0) && (cFlashfg == 0))
		{
			no_display_fg = 1;
		}
	}
	else if(HS_errorf==1)
	{
		Typedp.digitdp5	= 0;
		Typedp.digitdp2	= 0;
		if((cFlashCntr == 0) && (cFlashfg == 1))
		{
			diswin1[0]='E';
			diswin1[1]='R';
			diswin1[2]='R';
			diswin2[0]='0';
			diswin2[1]='0';
			diswin2[2]='9';
            cFlashfg = 0;
            cFlashCntr = 500;
			universal_error_flag=1;	
			dispupdatef=1;
		}
		else if((cFlashCntr == 0) && (cFlashfg == 0))
		{
			no_display_fg = 1;
		}
	}	
	else if(NO_ERROR_CONNECTOR_fg==1)
	{
		Typedp.digitdp5	= 0;
		Typedp.digitdp2	= 0;
		if((cFlashCntr == 0) && (cFlashfg == 1))
		{
			Typedp.digitdp5	= 0;
			diswin1[0]='E';
			diswin1[1]='R';
			diswin1[2]='R';
			diswin2[0]='0';
			diswin2[1]='1';
			diswin2[2]='1';
            cFlashfg = 0;
            cFlashCntr = 500;
			universal_error_flag=1;
			dispupdatef=1;	
		}
		else if((cFlashCntr == 0) && (cFlashfg == 0))
		{
			no_display_fg = 1;
		}
	}
	else if(universal_error_latch==0)
	{
		universal_error_flag=0;					  				  
		dispupdatef=1; 												  												  													  
	}
 
	if(no_display_fg == 1)
	{
       diswin1[0]='[';
       diswin1[1]='[';
       diswin1[2]='[';
       diswin2[0]='[';
       diswin2[1]='[';
       diswin2[2]='[';
       cFlashfg = 1;                 
       cFlashCntr = 500;
       no_display_fg = 0;
	   universal_error_flag=1;
	   dispupdatef=1;	
	}

	if(universal_error_flag==1)
	{
		dispupdatef=1;
		Error_flag = 1; 
		err_dispfg=1;
		SHDNLAT = 0;//1; 
		daccount = 0;
		cDacoutfg = 1;
		TRIP_LEDLAT = 0;
		weldcyclestrt=0;
		pulsestrtf=0;
		cvrefon=0;
		torchenable=0;
		torchrelease=0;
		strttmr=0;
		cntsecond=0;
		timerval=0;	
		cratersetup=0;
		crateron=0;
		iWireSpeed=0;
		inch_motor(0);
		Generate_DAC_Reference(0);
		Generate_Reference(0);		   																				
	}
    else 
    {
        Error_flag = 0;  
        if(err_dispfg == 1)
        {
			dispupdatef = 1;
            err_dispfg  = 0;
            TRIP_LEDLAT = 1;
			if(weldmode=='M' && universal_error_flag==0)
			{
				SHDNLAT = 1;//0;
				if(iSetcurrent <= HOT_START_SETCURR_LIMIT) 
				{
					cHotfg    = 1;                   
				}
				cRemoteEnDCurrUpdatefg = 1;
				cEnDCurrUpdatefg = 1;			
			}		
			else if(weldmode=='T' && universal_error_flag==0)
			{	
				SHDNLAT = 1;//0;	 
				cRemoteEnDCurrUpdatefg = 1;
				cEnDCurrUpdatefg = 1;
				cDacoutfg = 1;	
			}		
			else if(weldmode=='G' && universal_error_flag==0)
			{
				SHDNLAT = 0;//1;
				Generate_DAC_Reference(iVoltage);
				Generate_Reference(iWireSpeed);
			}     
        }
    } 
}


void ADC_Reference(void)
{
	if(SCKTcnt>=16)	//64)    //for avg of 16 sample 16*15usec=240usec required
	{
		SCKamp=Total_SCKAresult>>4;//6;
		SCKvtg=Total_SCKVresult>>4;//6;

		SCKTcnt         	=0;
		SCKavgf		  		=1;
		Total_SCKAresult	=0;
		Total_SCKVresult	=0;

	}
	
	if(DISPcnt>=8192)//16384)//8192)//4096)//2048)
	{
		DISPamp=Total_DISPAresult>>13;//14;//13;//11;//12;
		DISPvtg=Total_DISPVresult>>13;//14;//11;//12;
		
		Total_DISPAresult=0;
		Total_DISPVresult=0;

		DISPcnt=0;
		DISPavgf=1;
	}
	
	if(PULSEONOFFcnt>=4) //for average of 240*4=960usec==1msec time
	{
		PULSEamp=Total_PULSEONOFFAresult>>2;  
		Total_PULSEONOFFAresult=0;
		PULSEONOFFcnt=0;
		PULSEavgf=1;
	}	
	
	  
	if(iArcforceVtgcnt>=64)
	{
		DISPArcforcevtg=Total_SCKARCFVresult>>6;//11;//12;
		
		ARCFORCEVOLTAGE	= DISPArcforcevtg>>2;
		
		cFastUpdateFBvtg = 1;
		Total_SCKARCFVresult=0;
		iArcforceVtgcnt=0;		
	}
	
	
	if(iMotorcnt >= 64)
	{
		Total_SCKMresult=Total_SCKMresult>>6;
		iFBMotorvtg = Total_SCKMresult;
		
		Total_SCKMresult = 0;
		iMotorcnt = 0;
	}

	if(iTripcnt >= 512)
	{	
		Total_SCKE1result=Total_SCKE1result>>9;
		Total_SCKE2result=Total_SCKE2result>>9;
		
		count_3s++;
		
		iTrip1vtg=Total_SCKE1result;///10;//7.2;		//OV
		iTrip2vtg=Total_SCKE2result;		//UV-TH

		iTrip1vtg=iTrip1vtg*1.22;
		iTrip2vtg=iTrip2vtg*1.22;
		

		trip_detection(iTRIPVTG1);
		trip1_detection(iTRIPVTG2);

		Total_SCKE1result=0;
		Total_SCKE2result=0;
		iTripcnt=0;
	}
	
	if(AFVRcnt >= 8192)//2048)
    {
		Total_AFVRresult=Total_AFVRresult>>13;//11;
		if(1)//cTestVtgLockfg == 0)
		{
			VRvtg = Total_AFVRresult;
			//VRvtg = VRvtg/7;
			VRvtg = VRvtg*1.22/10;
			//iVTG_Min_Count = VRvtg;
			//iVTG_Max_Count = VRvtg;
		}
		
		iVoltage=125.0 +((VRvtg*275.0)/360);

		
		//iVoltage = VRvtg+60;
		//iVoltage = 140 + (VRvtg/1.45);		//(total cnt/(total cnt - 140)) 362/(362-140)=1.5
		//iVoltage = 80 + (VRvtg/1.3);	
				
		
		if(iVoltage <= 140)
		     iVoltage = 140;
         	if(iVoltage >= 400)
	    	iVoltage = 400;
		

		cMigVtgUpdatefg = 1;

		Total_AFVRresult=0;
		AFVRcnt=0;  
	     
      }       
	if((AFIRcnt >= 4096) && (cratersetup == 0))
    {   
		Total_AFIRresult=Total_AFIRresult>>12;//11;
		if(1)//cTestWSLockfg == 0)
		{
			IRcurr=Total_AFIRresult;
		
			//IRcurr = IRcurr/12.5;//13.2;///10.0;	//14.5; //19.35; for 18mtr/min
			IRcurr = IRcurr*1.22/10;
			iWireFeeder_error = IRcurr;
			//iWS_Max_Count = IRcurr;			
			
		}
		IRcurr = IRcurr*200.0/400;
		
		if(IRcurr >= 240)//PPC
		{
			IRcurr = 240;
		}	
		
		iWireSpeed=expon_lookup[IRcurr];
				
		
		if(iWireSpeed <= 20)
			iWireSpeed = 20;
		if(iWireSpeed >= 240)//200 //PPC
			iWireSpeed = 240;//200
				
		if(iWireFeeder_error >= 450)
		{
			WireFeeder_errorf=1;
		}
		else
		{
			WireFeeder_errorf=0;
		}	
		
		cMIGWSUpdatefg = 1;

		Total_AFIRresult=0;
		AFIRcnt=0;		 
	}			
		
	if((AFCWSCcnt >= 512) && (cRemoteDetectedfg == 0))
	{
		Total_AFCWSCresult = Total_AFCWSCresult>>9;
		if((weldmode == 'M') || (weldmode == 'T'))
		{
			fSetCurrent = Total_AFCWSCresult;

			if(cModel_Select == 1)
			{
				fSetCurrent = fSetCurrent*1.22/10;
				
				iSetcurrent = fSetCurrent/1.89;
				
				if(iSetcurrent <= 10)
					iSetcurrent = 10;				
				if(iSetcurrent >= 250)
					iSetcurrent = 250;
			}
			else if(cModel_Select == 2)
			{
				fSetCurrent = fSetCurrent*1.22/10;
				
				iSetcurrent = fSetCurrent/1.2;
				
				if(iSetcurrent <= 10)
					iSetcurrent = 10;								
				if(iSetcurrent >= 400)
					iSetcurrent = 400;				
			}
			else if(cModel_Select == 3)
			{
				fSetCurrent = fSetCurrent*1.22/10;
				
				iSetcurrent = fSetCurrent/0.8;
								
				if(iSetcurrent <= 10)
					iSetcurrent = 10;				
				if(iSetcurrent >= 600)
					iSetcurrent = 600;				
			}							
				
			iModelSelectBand = 	iSetcurrent;
			cDispSetCurrUpdatefg = 1; 
            //if(iPrevDisplaySetcurrent != iSetcurrent) 
            {
                //iPrevDisplaySetcurrent = iSetcurrent;
				cDispSetCurrUpdatefg = 1;                  
                //cEnDCurrUpdatefg = 1; 
            }
			
			iCraterWS = 0;
			//cDispSetCurrUpdatefg = 1;
			//cEnDCurrUpdatefg = 1;
		}
		if(weldmode == 'G')
		{
			iAdccrateriref = Total_AFCWSCresult;
			fCraterWS = Total_AFCWSCresult;
			fCraterWS = fCraterWS*1.22/10;///17.5;		//20-201
			iCraterWS=fCraterWS*200.0/480;
			
	        //iCraterWS = 20 + (fCraterWS);
			
			if(iCraterWS <= 20) //PPC
				iCraterWS = 20;
			if(iCraterWS >= 240)//200
				iCraterWS = 240;//200
				
			//Added to display crater Current
			if(Type.fourt==1)	
			{
              if(padccrateriref >= iAdccrateriref)
              diff=padccrateriref-iAdccrateriref;
              else
              diff=iAdccrateriref-padccrateriref;
           
              if(diff>10)//10)
              {
                 cCraterdispfg=1;
                 iCraterdisptime=0;
              }
           }
           else
           {
	           cCraterdispfg=0;
	       } 
			
			
			padccrateriref=iAdccrateriref;
			iSetcurrent = 0;
			cCraterWSUpdatefg = 1;			
			cEnDCurrUpdatefg = 1;
		}
		Total_AFCWSCresult=0;
		AFCWSCcnt=0;		
	}
	
	if(AFINDHScnt >= 512)
    {
		Total_AFINDHSresult=Total_AFINDHSresult>>9;

		if(weldmode == 'M')
		{
			fHotStart = Total_AFINDHSresult;
			fHotStart = fHotStart/40;

			iHotstart = fHotStart;
			
			if(iHotstart <= 0)
				iHotstart = 0;
			if(iHotstart >= 100)
				iHotstart = 100;		

			iInductance = 0;
			cHotstartUpdatefg = 1;
			cEnDCurrUpdatefg = 1;
		}
		if(weldmode == 'G')
		{
			fInductance = Total_AFINDHSresult;
			fInductance = fInductance/40;

			iInductance = fInductance;
			
			if(iInductance <= 0)
				iInductance = 0;
			if(iInductance >= 100)
				iInductance = 100;
					
			iHotstart = 0;
			cInductanceUpdatefg = 1;
			cEnDCurrUpdatefg = 1;
		}
		Total_AFINDHSresult=0;
		AFINDHScnt=0;
	}
	
	
	if(AFCVAFcnt >= 512)
    {
		Total_AFCVAFresult=Total_AFCVAFresult>>9;

		if(weldmode == 'M')
		{
			fArcForce = Total_AFCVAFresult;
			fArcForce = fArcForce/40;

			iArcforce = fArcForce;

			if(iArcforce <= 0)
				iArcforce = 0;
			if(iArcforce >= 100)
				iArcforce = 100;
			
			iCraterVtg = 0;
			cArcforceUpdatefg = 1;
			cEnDCurrUpdatefg = 1;
		}						
		if(weldmode == 'G')
		{
			iAdccratervref = Total_AFCVAFresult;
			fCraterVtg = Total_AFCVAFresult;
			fCraterVtg = fCraterVtg*1.22/10;

            //iCraterVtg = fCraterVtg;
            iCraterVtg=140.0 +((fCraterVtg*255.0)/480);
            
            //iCraterVtg = 140 + (fCraterVtg/1.5); 		//(total cnt/(total cnt - 140)) 405/(405-140)=1.5
			
			if(iCraterVtg <= 140)
				iCraterVtg = 140;
			if(iCraterVtg >= 400)
				iCraterVtg = 400;
			//Added to display crater voltage
				
			if(Type.fourt==1)	
			{
              if(padccratervref >= iAdccratervref)
              diff=padccratervref-iAdccratervref;
              else
              diff=iAdccratervref-padccratervref;
           
              if(diff>10)//10)
              {
                 cCraterdispfg=1;
                 iCraterdisptime=0;
              }
           }
           else
           {
	           cCraterdispfg=0;
	       } 
	       padccratervref = iAdccratervref;
			iArcforce = 0;
			cCraterVtgUpdatefg = 1;				
			cEnDCurrUpdatefg = 1;
		}			
		Total_AFCVAFresult=0;
		AFCVAFcnt=0;
	}
	
	if(iRemotecnt >= 128)
	{
		Total_AFRresult=Total_AFRresult>>7;

		if((weldmode == 'M') || (weldmode == 'T'))
		{	
			fRemoteCurr = Total_AFRresult;
			fRemoteCurr=fRemoteCurr/10;
			
			iRemoteCurr = fRemoteCurr;

            iRemoteCheckcnt = iRemoteCurr;
            
            fRemoteCurr = iRemoteCurr;

            fGndRes = (fRemoteCurr * 10000) /(5000 - fRemoteCurr);

            fRemoteCurr = (fGndRes * 5000) / (10000 + 9600); 

            iRemoteCurr = fRemoteCurr;	

            if(cModel_Select == 1)
            {
                //fOffset = 9.5;                         
            }
            else if(cModel_Select == 2)
            {                
                fOffset = 3.75;                           
            }                
            else if(cModel_Select == 3)
            {
                //fOffset = 4.0;                       
            }
			

			iRemotecnt = 300;

            if(iRemoteCheckcnt <= iRemotecnt)               
            { 
				cRemoteDetectedfg = 1; 
				
                if(cModel_Select == 1)
                {
					//iRemoteCurr = iRemoteCurr*fOffset;
	
	                if(iRemoteCurr <= 10)
	                    iRemoteCurr = 10;
	                if(iRemoteCurr >= 250)
	                    iRemoteCurr = 250; 
				}
                else if(cModel_Select == 2)
                {
					iRemoteCurr = iRemoteCurr*fOffset;
	
	                if(iRemoteCurr <= 10)
	                    iRemoteCurr = 10;
	                if(iRemoteCurr >= 400)
	                    iRemoteCurr = 400; 
				}
                else if(cModel_Select == 3)
                {
					//iRemoteCurr = iRemoteCurr*fOffset;
	
	                if(iRemoteCurr <= 10)
	                    iRemoteCurr = 10;
	                if(iRemoteCurr >= 600)
	                    iRemoteCurr = 600; 
				}								
				iSetcurrent=iRemoteCurr;

                if(iPrevSetcurrent != iSetcurrent)
                {
                    iPrevSetcurrent = iSetcurrent;
                    cRemoteEnDCurrUpdatefg = 1; 
                } 
			}
            else    
            {     
                if(cRemoteDetectedfg == 1)
                {                       
                    iPrevDisplaySetcurrent = 0;
                    dispupdatef = 1;                       
                }
                cRemoteDetectedfg = 0;                    
            }
		}
		Total_AFRresult = 0;
		iRemotecnt = 0;
	}			
}	

 void model_selection(void)
 {   
	cModelSelectfg = 1;
	
	Typedp.digitdp2 = 0;
	Typedp.digitdp5 = 0;
	
	if((iModelSelectBand >= 0) && (iModelSelectBand <= 150))
	{   
		diswin1[0]='M';
		diswin1[1]='I';
		diswin1[2]='G';
		diswin2[0]='2';
		diswin2[1]='5';
		diswin2[2]='0';
		cModel_Select = 1;
		dispupdatef = cEEPROMModelSavefg = 1;   
	}
	else if((iModelSelectBand > 150) && (iModelSelectBand <= 275))
	{
		diswin1[0]='M';
		diswin1[1]='I';
		diswin1[2]='G';
		diswin2[0]='4';
		diswin2[1]='0';
		diswin2[2]='0';
		
		cModel_Select = 2;            
		dispupdatef = cEEPROMModelSavefg = 1;      
	}              
	else if((iModelSelectBand > 275) && (iModelSelectBand <= 400))
	{   
		diswin1[0]='M';
		diswin1[1]='I';
		diswin1[2]='G';
		diswin2[0]='6';
		diswin2[1]='0';
		diswin2[2]='0';
		
		cModel_Select = 3;
		dispupdatef = cEEPROMModelSavefg = 1;      
	}
	
	if(cEEPROMModelSavefg == 1)
	{
		EEPROM_Erase_Write((6*2),cModel_Select); 
		cEEPROMModelSavefg = 0;
		cDonefg=1;
		cModeSelectDonefg = 0;
	} 	    
}
