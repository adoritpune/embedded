/*
pressure error code is moodified from 006 to 007

Modified with ESD issue for Champ multi 600
tested ok 05.08.2014 Rev-1.0

For demo of Siemens
modified tig on mode in champ mig 600 mode
added interlock for arc on key & lock key. 
when arc on timer key or Lock key is pressed, all other keys are ignored.
Model A== CHamp  multi 400
Model B== Champ multi 600
dated 21.07.2014

MODEL C== CHAMP MULTI 250
*/ 
#include "stdio.h"
#include "math.h"
#include "p30f5011.h" 
#include "libpic30.h"
#include "variable1.h"
#include "structure.c"

#include "define1.h"
#include "keypad1.c"
#include "encoder21.c"
#include "interrupt1.c"
#include "eeprom1.c"
#include "display1.c"
#include "autodata.c"

//Macros for Configuration Fuse Registers (copied from device header file):
_FOSC(CSW_FSCM_OFF & FRC_PLL16);  			//Set up for crystal multiplied by 8x PLL
_FWDT(WDT_OFF);                 					//Turn off the Watch-Dog Timer.
_FGS(CODE_PROT_OFF);            				//Disable Code Protection
_FBORPOR(MCLR_EN & PBOR_OFF & PWRT_64); 	//updated at godhra testing
int main()
{
	for(i=0;i<200;i++)
	delay();
	portpin_init();
	uart_init();
	encoder_init();
	timer1_init();
	init_portpin();
	pwm_init();
	display_init();
	allcolumnlogic1();
	//adc_init();
	read_model();
	if(mc_model=='A')				//MMA-TIG-MIG-FCAW-400A
	{
		vtgmulti			=42.0;
 		curmulti			=716.0;
      	motormulti		=200.0;
		Currentfactor	=9.20;
		maxmmacurrent	=399.0;
		maxmigvolts		=40.0;
		cratervoltfactor	=0.22;
	}
	else if(mc_model=='B')		//MMA-TIG-MIG-FCAW-600A
	{
		vtgmulti=56.0;
 		curmulti=980.0;
     		motormulti=200.0;
		Currentfactor=6.13;
		maxmmacurrent=599.0;
		maxmigvolts=46.0;
		cratervoltfactor=0.27;
	}
	else if(mc_model=='C')		//MMA-TIG-MIG-FCAW-250A
	{
		vtgmulti			=42.0;
 		curmulti			=716.0;
      	motormulti		=200.0;
		Currentfactor	=9.20;
		maxmmacurrent	=249.0;		//399.0;
		maxmigvolts		=34.0;		//40.0;
		cratervoltfactor	=0.22;
	}





/*	else if(mc_model=='D')		//MMA-SSPW-MIG-FCAW-600A
	{
		vtgmulti=56.0;
 		curmulti=980.0;
      	motormulti=200.0;
		fcawwfmul=10.0;		//42 v motor
		autodatarow=60;
		Currentfactor=6.13;
		maxmmacurrent=599.0;
		maxmigvolts=46.0;
		cratervoltfactor=0.27;
	}*/
	else
	{
		vtgmulti=42.0;
 		curmulti=716.0;
      	motormulti=200.0;
		Currentfactor=9.20;
		maxmmacurrent=399.0;
		maxmigvolts=40.0;
		cratervoltfactor=0.22;
	}

/*	 if(mc_model=='E')
	maxmigwf=60;
	else if(mc_model=='F')
	maxmigwf=70;
	else if(mc_model=='G')
	maxmigwf=80;
	else if(mc_model=='H')
	maxmigwf=90;
*/

	DISICNTbits.DISICNT=0x3FFF;
	{
		win1[0]='A';
		win1[1]='D';
		win1[2]='R';
		win2[0]='2';
		win2[1]='0';
		win2[2]=mc_model;
		win1dpcnt=3;
		win2dpcnt=3;
		for(i=0;i<4000;i++)
		delay();
		if(mc_model=='A') 
		{
			win1[0]='M';
			win1[1]='I';
			win1[2]='G';
			win2[0]='4';
			win2[1]='0';
			win2[2]='0';
		}
		/*else if(mc_model=='B')
		{
			win1[0]='S';
			win1[1]='S';
			win1[2]='P';
			win2[0]='4';
			win2[1]='0';
			win2[2]='0';
		}*/
		else if(mc_model=='B')
		{
			win1[0]='M';
			win1[1]='I';
			win1[2]='G';
			win2[0]='6';
			win2[1]='0';
			win2[2]='0';
		}
		else if(mc_model=='C')
		{
			win1[0]='M';
			win1[1]='I';
			win1[2]='G';
			win2[0]='2';
			win2[1]='5';
			win2[2]='0';
		}

		/*else if(mc_model=='D')
		{
			win1[0]='S';
			win1[1]='S';
			win1[2]='P';
			win2[0]='6';
			win2[1]='0';
			win2[2]='0';
		}*/
		else 
		{
			win1[0]='M';
			win1[1]='I';
			win1[2]='G';
			win2[0]='4';
			win2[1]='0';
			win2[2]='0';
		}
		for(i=0;i<4000;i++)
		delay();
	}
	WeldMode=EEPROM_Read(36*2);
	if(WeldMode > 0x04)
	{
		WeldMode=0x03;	
      	EEPROM_Erase_Write((36*2),WeldMode); 
 	}     
	readmematstrt(); 
	oper=pre;
	ARCONLAT=0;
	genref(0);	   	//generate reference
/*	cccvmode=0;
	cccvmode=EEPROM_Read(2*33);
      prevcccv=cccvmode;


	if(Type.tig==0 && (mc_model=='A' || mc_model=='B'))
	{
		cccvmode=0;	
		if(prevcccv!=cccvmode)
		{
			EEPROM_Erase_Write((33*2),cccvmode);
			prevcccv=cccvmode;
  		}      
	}
	else if(Type.tig==0 && (mc_model!='A' || mc_model!='B'))
	{
		cccvmode=1;
		if(prevcccv!=cccvmode)
		{
			EEPROM_Erase_Write((33*2),cccvmode);
			prevcccv=cccvmode;
  		}      		
	} 
	if(cccvmode==0xff)
	{
		cccvmode=0;
		if(prevcccv!=cccvmode)
		{
			EEPROM_Erase_Write((33*2),cccvmode);
			prevcccv=cccvmode;
  		}      
	}
	if(cccvmode==1 && (Type.mma==0 || (Type.tig==0 && mc_model !='A' && mc_model !='B')))
	{
		TypeU.LEDGROUP[1]=0xFF;
		TypeU.LEDGROUP[3]=0xFF;
		if(Type.mma==0)		
		TypeU.LEDGROUP[2]=0xFF;
		else if(Type.tig==0)
		TypeU.LEDGROUP[2]=0x7F;
	}mahesh 17.09.2013
	*/
/*	if(WeldMode==0x01 || 	WeldMode=0x02)
	{
		TypeU.LEDGROUP[1]=0xFF;
		TypeU.LEDGROUP[3]=0xFF;
		 if(Type.mma==0)		
		TypeU.LEDGROUP[2]=0xFF;
		else if(Type.tig==0)
		TypeU.LEDGROUP[2]=0x7F;
	}*/

	modechangef=1;
	arconhr=EEPROM_Read(2*37);
	arconmin=EEPROM_Read(2*38);
	arconsec=EEPROM_Read(2*39);
    	if(arconhr==0xffff || arconhr > 999)
	{
		arconhr=0;
        	EEPROM_Erase_Write((37*2),arconhr);
    	}
	if(arconmin==0xffff || arconmin >60)
	{
		arconmin=0;
		EEPROM_Erase_Write((38*2),arconmin);
	}
	if(arconsec==0xffff || arconsec >60)
	{
		arconsec=0;
		EEPROM_Erase_Write((39*2),arconsec);
	}
	
	while(1)
	{
	
		if(modechangef==1)
		{
			modechangef=0;
			if(Type.mma==0)
			{
				win1[0]='M';
				win1[1]='M';
				win1[2]='A';
				win2[0]='O';
				win2[1]='N';
				win2[2]='/';
				win1dpcnt=3;
				win2dpcnt=3;
				for(ijk=0;ijk<=4000;ijk++)
				delay();	
			}
			else if(Type.tig==0) // && (mc_model == 'A' || mc_model !='B'))
			{
				win1[0]='T';
				win1[1]='I';
				win1[2]='G';
				win2[0]='O';
				win2[1]='N';
				win2[2]='/';
				win1dpcnt=3;
				win2dpcnt=3;
				for(ijk=0;ijk<=4000;ijk++)
				delay();	
			}
		    /* else if(Type.tig==0) && (mc_model=='C' || mc_model=='D'))
			{
				win1[0]='S';
				win1[1]='S';
				win1[2]='P';
				win2[0]='O';
				win2[1]='N';
				win2[2]='/';
				win1dpcnt=3;
				win2dpcnt=3;
				for(ijk=0;ijk<=4000;ijk++)
				delay();	
			}*/
			else if(Type.mig==0)
			{
				win1[0]='M';
				win1[1]='I';
				win1[2]='G';
				win2[0]='O';
				win2[1]='N';
				win2[2]='/';
				win1dpcnt=3;
				win2dpcnt=3;
				for(ijk=0;ijk<=4000;ijk++)
				delay();	
			}
			else if(Type.fcaw==0)
			{
				win1[0]='F';
				win1[1]='C';
				win1[2]='W';
				win2[0]='O';
				win2[1]='N';
				win2[2]='/';
				win1dpcnt=3;
				win2dpcnt=3;
				for(ijk=0;ijk<=4000;ijk++)
				delay();	
			}
			adc_init();
			offallkeyf=0;
    	}
	
	if(sendtoremotef==1)
	{
		sendtoremotef=0;
		transon=0;
		if(Type.mma==0 && Type.tig==1 && Type.mig==1 && Type.fcaw==1 )	// cc mode
		{
			model='M';
			errflag1='N';//no vtg controll in mma mode
			transtoremote(para.pwmtime1,sendvtg,para.weldcurrent,sendcur,model,errflag1,errflag2);
			VRDRELAYLAT=0;	//tig mode disable
			//VRDBYPASSLAT=0;
		}
		else if(Type.mma==1 && Type.tig==1 && Type.mig==0 && Type.fcaw==1 )	// cv mode
		{
			model='G';
			//errflag2='N';//becaz curent varies from 0 t0 400;
			transtoremote(para.weld.volts,sendvtg,para.weld.wfs,sendcur,model,errflag1,errflag2);
			VRDRELAYLAT=1;	//tig mode enable
			//VRDBYPASSLAT=1;
		}

		else if(Type.mma==1 && Type.tig==1 && Type.mig==1 && Type.fcaw==0)	// cv mode
		{
			model='G';
			//errflag2='N';//becaz curent varies from 0 t0 400;
			transtoremote(para.fcaw.volts,sendvtg,para.fcaw.wfs,sendcur,model,errflag1,errflag2);
			VRDRELAYLAT=1;	//tig mode enable
			//VRDBYPASSLAT=1;
		}
		/*else if(Type.mma==1 && Type.mig==1 && Type.tig==0 )//&& (mc_model=='A' || mc_model=='B'))	// tig mode
		{
			model='G';
			if(para.weld.wfs>=maxfcawwf) //6 meter/min
			errflag2='O';//becaz curent varies from 0 t0 400;
			else
			errflag2='N';//becaz curent varies from 0 t0 400;
			transtoremote(para.weld.volts,sendvtg,para.weld.wfs,sendcur,model,errflag1,errflag2);
			VRDRELAYLAT=1;	//tig mode enable
		}*/
		else if(Type.mma==1 && Type.tig==0 && Type.mig==1 && Type.fcaw==1 ) //&& (mc_model !='A' || mc_model !='B')) // tig mode
		{
			model='M';//'T';
			errflag1='N';//no vtg controll in tig mode
			transtoremote(para.pwmtime1,sendvtg,para.weldcurrent,sendcur,model,errflag1,errflag2);
			VRDRELAYLAT=1;		//tig mode enable
			//VRDBYPASSLAT=1;
		}
	}
	//if(cyclestrt==0 && keyscan== 1 && offallkeyf==0)			//keypad must be disable during welding
	if(keyscan==1)
	{
			keyscan=0;
			key=keypad_read();
	
			if(cyclestrt==0)
			{
				keydetect=1;
				if(key=='H')
				{
					keyaction(key);
					keydetect=0;
				}
			}
			else
			{
				if(key=='O')
				     Dispmampf=1;
				else
					Dispmampf=0;	
			}
	}

//********************************************************************************
	{
		if(UV_errorf==1 && OV_errorf==0 && TH_errorf==0)
		{
				win1[0]='E';
				win1[1]='R';
				win1[2]='R';
				win2[0]='0';
				win2[1]='0';
				win2[2]='1';
				win1dpcnt=3;
				win2dpcnt=3;
				drive_motor(0);
				GASONLAT=0;
				ARCONLAT=0;
				genref(0);	//generate reference
		}
		else if(UV_errorf==0 && OV_errorf==1 && TH_errorf==0)
		{
				win1[0]='E';
				win1[1]='R';
				win1[2]='R';
				win2[0]='0';
				win2[1]='0';
				win2[2]='2';
				win1dpcnt=3;
				win2dpcnt=3;
				drive_motor(0);
				GASONLAT=0;
				ARCONLAT=0;
				genref(0);	//generate reference
		}
		else if(UV_errorf==0 && OV_errorf==0 && TH_errorf==1)
		{
				win1[0]='E';
				win1[1]='R';
				win1[2]='R';
				win2[0]='0';
				win2[1]='0';
				win2[2]='3';
				win1dpcnt=3;
				win2dpcnt=3;
				drive_motor(0);
				GASONLAT=0;
				ARCONLAT=0;
				genref(0);	//generate reference
		}
		while(Errorf==1);
	}

//************************************************************************************************
//****************************************************************************************************************
//***************************************** CC MODE **************************************************************
//****************************************************************************************************************
	if(cccvmode==1)
	{
		CCCVCTRLLAT=1;
		if(encoderscan ==1)
		{
			encres=scanencoder1();
			encres1=scanencoder();//1
			encoderscan=0;
			updatedatacc(encres,encres1);
		}	
		if(keydetect==1)
		{	
			keydetect=0;
			if((key=='N' || key=='Z' || key=='D'|| key=='H') && weldingstart==0)	
			{
				keyaction(key);
   			}			
		} 
		genref(para.pwmtime1);
	}

//****************************************************************************************************************
//***************************************** CV MODE **************************************************************
//****************************************************************************************************************
	else if(cccvmode==0)
	{
		CCCVCTRLLAT=0;
		if(encoderscan ==1 && gasocvinch==0 )//&& passprotect==0x0000 )// || setpasswordf==1))
		{
			encres=scanencoder1();
			encres1=scanencoder();
			encoderscan=0;
			updatedatacv(encres,encres1);
		}
		if(keydetect==1)
		{	
			keydetect=0;
			if(Type.fcaw==1  && Type.mig==0 && Type.mma==1 && Type.tig==1)  //mahesh 16.09.2013
			{
				if(passprotect==0x0001)	
				{
					 if(key=='H' || key=='D'|| key=='Z'|| key=='O') //only menu and encoder1 switch operates,
					 {
						keyaction(key);
					 }
				}
				else
				{
						keyaction(key);
				}
			}
			else if(Type.fcaw==0 && Type.mig==1 && Type.mma==1 && Type.tig==1)  //mahesh 16.09.2013
			{
				if(passprotect==0x0001)	
				{
					 if(key=='H' || key=='D'|| key=='Z'|| key=='O')//only menu and encoder1 switch operates,
					 {
						keyaction(key);
					 }
				}
				else
				{
					keyaction(key);
				}
			}

		}   
		if(setupmode==0)
		{
			if(torch==1 || cyclestrt==1) //torch function scan
			{
				torchaction();
			}
			else 
			{
				genref(0);
			}
		}
		
		if(Read_SWf==1)// && (mc_model=='C' || mc_model=='D'))		//mahesh
     		{	
	           Read_SWf=0;
			Read_GWSW();
	           	Read_Pressure_SW();
			Read_WSAMP_SW();
			//Read_Motorovld_SW();
	           if(Watercooledf==1)
	           {
				if(Pressureonf==0)
				{
					Pressure_ERRf=1;
	                	}
				else
				{
					Pressure_ERRf=0;
	                	}
			}
			else
			{
				Pressure_ERRf=0;
			}
		}	
	}//cv mode end
 }//while
}//main

unsigned int updatedata(unsigned int current,unsigned int minimum,unsigned int maximum,unsigned char sign)
{
	if(sign == '+')
	{
		current++;
		if(current>=maximum)
		{
			current=maximum;
		}
		updatedisp=1;
		transon=1;	
	}
	else if (sign == '-')
	{
		if(current==minimum)
		{
			current=minimum;
		}
		else
		{
			current--;
		}
	    transon=1;
		updatedisp=1;
	}
	return(current);
}
void genref(unsigned int pwmtm1)
{
	unsigned int result1=0;
	float temp1=0;
	static unsigned int prevpwmcnt1=0;	
	temp1=pwmtm1; //enabled for no pid
	if(setupmode==0)
	{
		result1=((temp1 * 29.49));
	}
	else if(setupmode==1)
	{
		result1=((temp1 * 29.49)/10.0);
	}	

//if(prevpwmcnt1 != result1)
	{
		OC4RS=result1;
	}
	prevpwmcnt1=result1;
}

inline void drive_motor(unsigned int pwmtm)
{
		unsigned int result=0;
		static unsigned int newpwm=0;
		float temp=0;
		if(mvtgmesrf==1 && pwmtm!=0)
		{
			newpwm=calmvtgerr(pwmtm);
			mvtgmesrf=0;
		}
		else if(pwmtm==0)
		{
			newpwm=pwmtm;
			pidovershootf=0;
			startmotor=0;
		}
		if(motormulti <= 100 || Type.crater==0 || Type.spot==0 || Type.multispot==0)//no motor voltage closed loop
		{
			temp=pwmtm; //enabled for no pid
		}
		
		else   //closed loop > 100
		{
			temp=newpwm;//disabled for no pid
			temp=temp/10;// mahesh
		}	
		result=((temp * 29.49));
		if(prepwmcnt != result)
		{
			OC8RS=result;
		}
		prepwmcnt=result;
	
}
void softstart_motor(unsigned int pwmtm)
{
	unsigned int i,j,step;
	unsigned int result=0;
	float temp=0,temp1=0;
	temp1=pwmtm;
	for(step=1;step<=128;step++) //128
	{
		temp=(temp1 * step);
		temp=temp/128; //128
		temp=temp * 29.49;
		result=temp;
	    OC8RS=result;
		for(i=0;i<1000;i++)
		{
			for(j=0;j<4;j++);
		}
	}
	pidovershootf=0;
	overshootcnt=0;
	newpwm=pwmtm*2.0;//10.0;
}

void inch_motor(unsigned int pwmtm)
{
	float temp=0,result=0;
	temp=pwmtm;
	temp=temp * 29.49;
	result=temp;
	OC8RS=result;
}

inline unsigned int calmvtgerr(unsigned int pwmtm1)
{
    double refvtg=0,motorvtg=0,fpwm=0,err=0,fnewpwm=0;
	signed long error=0;
	static unsigned int errdiv=128;
	motorvtg= fbmvtg*10.0;
	refvtg=(pwmtm1*5.20);  ///5.0)*10.0)/9.0;
      error=(refvtg - motorvtg);
	fpwm=((error*1.8));//3.0)/1.66;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if(refvtg < motorvtg)
	{
		err=(motorvtg - refvtg);
		fnewpwm=newpwm;
		fnewpwm= (fnewpwm - ((err*1.8)/errdiv));//err*0.45));//1.8));
		newpwm=fnewpwm;		
	}
	else if(refvtg > motorvtg )
	{
		err= (refvtg - motorvtg);
		fnewpwm=newpwm;
		fnewpwm= (fnewpwm + ((err*1.8)/errdiv));//err*0.45));//1.8));
		newpwm=fnewpwm;	
	}
	else 
	{
		newpwm=newpwm;
	}

	if(newpwm > 800.0) 
			newpwm= 800;
    else if(newpwm <= 0.0) 
			newpwm= 0;

	errdiv--;
	if(errdiv<=4)
	errdiv=4;
	return(newpwm);
}
	
	
void uart_init() //38400 baud rate
{
   U1BRG=190;//48, 190;  //48 for 38400 baud rate, and 190 for 9600 baud rate {[((7.37 * 1000000*16)/4)/9600]/16}- 1;
   U1MODE=0X8800;// uart enable	
   U1STAbits.UTXEN=1; //Uart transmit enable
   IEC0bits.U1RXIE=1; //Uart reception interrupt enable	38400 baud rate
}
void SENDSERIAL(unsigned int result)
{
	unsigned int aa;
	unsigned char higher,lower;
	aa=(result & 0xff00);
	aa= (aa >> 8);
	higher=aa;
	aa=(result & 0X00ff);
	lower=aa;
	trans('$');
	trans(higher);
	trans(lower);
	trans(0X0D);
	trans(0X0A);
}

void trans(unsigned char a)
{
	while(U1STAbits.UTXBF == 1);	
    	U1TXREG=a;
}

void adc_init(void)
{
	ADPCFG = 0xFFFF;			// all port B pin as digital input pin
	ADPCFGbits.PCFG1 = 0;		// port B.1 as analog (welding voltage) input pin 
	ADPCFGbits.PCFG5= 0;		// port B.5 as analog (shunt voltage) input pin 
	ADPCFGbits.PCFG2 = 0;		// port B.2 as analog (wire feed motor voltage) input pin 
	//mahesh ADPCFGbits.PCFG8 = 0;		// port B.8 as analog (wire feed motor voltage) input pin 
	//ADPCFGbits.PCFG9 = 0;	// port B.9 as analog (wire feed motor voltage) input pin 
	ADPCFGbits.PCFG10= 0;	// port B.10 as analog(wire feed motor voltage) input pin 



	//ADPCFGbits.PCFG7 = 0;		// port B.7 as analog (carriage motor voltage) input pin 
	ADCSSL = 0x0000;			// skip all analog channels for input scanning
	ADCSSLbits.CSSL1 = 1;		// select AN1 (welding voltage) for input scanning 
	ADCSSLbits.CSSL5 = 1;		// select AN5 (shunt voltage) for input scanning 
	ADCSSLbits.CSSL2 = 1;		// select AN2 (wire feed motor voltage) for input scanning 
	//ADCSSLbits.CSSL8 = 1;		// select AN2 (wire feed motor voltage) for input scanning 
	//ADCSSLbits.CSSL9 = 1;		// select AN2 (wire feed motor voltage) for input scanning 
	ADCSSLbits.CSSL10 = 1;		// select AN10 (wire feed motor voltage) for input scanning 

//	ADCSSLbits.CSSL7 = 1;		// select AN7 (carriage motor voltage) for input scanning 
	ADCON1bits.FORM = 0;		// data output format in unsigned integer 
	ADCON1bits.SSRC = 7;		// internal counter ends sampleing and starts conversion 
	ADCON2bits.VCFG = 0;		// setup adc voltage reference source AVdd & AVss 	
	ADCON2bits.CSCNA = 1;		// scan inputs 	
	ADCON2bits.SMPI = 15;		// interrupt after every 15th sample 	
	ADCON2bits.BUFM = 0;		// buffer configure as one 16-word buffer 	
	ADCON2bits.ALTS = 0;		// always use MUX A input multiplexer settings 	
	ADCON3bits.SAMC = 4;//2;//6;//4 now 4 TAD //1; auto sample time bit = 1Tad //1=TAD,4=4 TAD,6=6 TAD
	ADCON3bits.ADRC = 0;		// AD conversion clock source from system clock 
	ADCON3bits.ADCS = 10;//10;//12;//12 //6;//19;		// setup adc clock value = 2*Tay/Tcy-1 = 2*666.66n/.67816802n-1 = 19 
	//ADCON3 = 0x1F02;//3F;//1f02;//0F00; // Sample time = 15Tad, Tad = internal Tcy/2
	ADCHSbits.CH0NA = 0;		// -ve input is Vref- 
//	ADCHSbits.CH0SA = 0;		// connect B.4 / AN4 as channel 0 input 
//	IPC2bits.ADIP = ad_p;		// assigning priority 
	IFS0bits.ADIF = 0;			// clear A to D conversion complete flag 
	IEC0bits.ADIE = 1;			// enable A to D conversion interrupt 
	ADCON1bits.ADON = 1;		// on adc 
	ADCON1bits.ASAM = 1;		// Auto sample / conversion start 
}
void extint3_init()
{
	IFS2bits.INT3IF=0; //Clear the external interrupt status flag
    	INTCON2bits.INT3EP=0; //negative edge interrupt
    	IEC2bits.INT3IE=1;	//ENABLE INTERRUPT.
}

void encoder_init()
{
	ENCODERAIO=1;
	ENCODERAIO=1;
	U2MODE=0X0000;		// uart DISABLE
//	REMOTEAIO =1;		//initialise remote
//	REMOTEBIO =1;
	ENCODER1AIO=1;
	ENCODER1BIO=1;
//	REMOTE1AIO=1;
//	REMOTE1BIO=1;
}
void timer1_init()
{
	T1CON=0;			//Stops the Timer1 and reset control reg.
	TMR1=0;				//Clear contents of the timer register
	PR1=0X72CB;			//Load the Period register with the value 0xFFFF
	IPC0bits.T1IP=1;	//Setup Timer1 interrupt 
	IFS0bits.T1IF=0;	//Clear the Timer1 interrupt status flag
	IEC0bits.T1IE=1;	//Enable Timer1 interrupts
	T1CONbits.TON=1;	//strat the timer
}
void pwm_init()
{
	
	OC4CON=0;			//Turn off output compare module 1
	OC4RS=0;			//write duty cycle biffer register
	OC4R=0;				//write to initial duty cycle value
	OC4CONbits.OCM=6;	//output compare is configured as pwm generated
//**************
	OC8CON=0;			//Turn off output compare module 1
	OC8RS=0;			//write duty cycle biffer register
	OC8R=0;				//write to initial duty cycle value
	OC8CONbits.OCM=6;	//output compare is configured as pwm generated
	PR2=2949;			//1472 for 20khz,2949 for 10khz fred	//736 for 40khz freq.		//initialise pr2 reg. for freq.
	IPC1bits.T2IP=1;	//setup timer2 at desired priority level
	IFS0bits.T2IF=0;	//clear timer2 interrupt flag	
	IEC0bits.T2IE=1;	//enable timer2 interrupt flag
	T2CONbits.TCKPS=0;	//timer2 prescaler 1
	T2CONbits.TON=1;	//start timer2
}

void send_mesg()
{
	trans('@');	
	trans('A');
	trans('D');
	trans('O');
	trans('R');
	trans(' ');
	trans('W');
	trans('E');
	trans('L');
	trans('D');
	trans('I');
	trans('N');
      trans('G');
	trans(' '); 
}
inline unsigned char float_to_ascii_str(unsigned char *ptr,float nnn)
{
  	unsigned char temp,jjj,iii = 4;
  	unsigned char sign = (nnn < 0);
  	unsigned long int trunc;
  	unsigned long int fract;
	unsigned char dotcount=0;
 	maheshkp=1;
	if(sign)
	{
    		nnn *= -1;
	}
  	trunc = (unsigned long int)nnn;
  	fract = (unsigned long int)((nnn - (unsigned long int)nnn) * 10000);
  	if(fract == 0)
	{
    		ptr[iii++] = '0';
  	}
  	else for(jjj = 0;jjj < 4;jjj++) 
	{
    		ptr[jjj] = (unsigned int)((fract % 10) + '0');
    		fract /= 10;
  	}
  	//ptr[i++] = '.';		//	mahesh
  	if(trunc == 0)
	{
    		ptr[iii++] = '0';
  		dotcount++;
	}
  	else while(trunc > 0) 
	{
    	ptr[iii++] = (unsigned int)((trunc % 10) + '0');
    	trunc /= 10;
		dotcount++;
  	}
	if(sign)
	{
    		ptr[iii++] = '-';
	}
  	for(jjj = 0;jjj < (iii / 2);jjj++) 
	{
    		temp = ptr[jjj];
    		ptr[jjj] = ptr[(iii - jjj) - 1];
    		ptr[(iii - jjj) - 1] = temp;
  	}
  	ptr[iii] = '\0';
	maheshkp=0;
	return(dotcount);
}

void led_init()
{
	TypeU.LEDGROUP[0]=0XFF;
	Type.amp=0;
	Type.voltage=0;
	TypeU.LEDGROUP[1]=0XFF;
	Type.weld=0;
	TypeU.LEDGROUP[2]=0XFF;
	Type.zeropteight=0;
	Type.fe=0;
	TypeU.LEDGROUP[3]=0XFF;
	Type.arco2=0;
	Type.twot=0;
	TypeU.LEDGROUP[4]=0XFF;
	Type.automan=0;
}
void portpin_init()
{
	GASONIO=0;
	///******CONTACTORIO=0;
	GASONLAT=0;
	///******CONTACTORLAT=0;
	TORCHONIO=1;
	ADPCFGbits.PCFG3=1;		//portpin used as i/o port
	ADPCFGbits.PCFG4=1;		//portpin used as i/o port
	CCCVCTRLIO=0;
	ARCONIO=0;
	ARCONLAT=0;
      WSAMPIO=1;
	MOTOROVLDIO=1;
	SW1IO=1;
	SW2IO=1;
     VRDRELAYIO=0;

}
void read_torchsw()
{
	TORCHONIO =1;	
	if(TORCHON == 1)
	{
		delay();
		if(TORCHON == 1)
		torch=1;
	}
	else
	{
		delay();
		if(TORCHON == 0)
		torch=0;
	}	
}

void Read_GWSW()
{
	GWSWIO =1;	
	if(GWSW == 0)
	{
		delay();
		if(GWSW == 0)
		{
			Watercooledf=1;
		}
	}
	else
	{
		delay();
		if(GWSW == 1)
		{
			Watercooledf=0;
        	}
	}	
}


void Read_Pressure_SW()
{
	PRESSUREIO =1;	
	if(PRESSURE == 0)
	{
		delay();
		if(PRESSURE == 0)
		{
			Pressureonf=1;
		}
	}
	else
	{
		delay();
		if(PRESSURE== 1)
		{
			Pressureonf=0;
		}
	}	
}

void Read_WSAMP_SW()
{
	WSAMPIO =1;	
	if(WSAMPSW== 0)
	{
		delay();
		if(WSAMPSW== 0)
		{
			DispWSf=1;
		}
	}
	else
	{
		delay();
		if(WSAMPSW == 1)
		{
			DispWSf=0;
		}         	
	}	
}

void Read_Motorovld_SW()
{
	MOTOROVLDIO =1;	
	if(MOTOROVLD== 0)
	{
		delay();
		delay();
		if(MOTOROVLD== 0)
		{
			Moverloadf=1;
			Motorerrf=1;
		}
	}
	else
	{
		delay();
		if(MOTOROVLD == 1)
		{
			Moverloadf=0;
		}         	
	}	
}


unsigned int hextodec(unsigned int hexnum)
{
	unsigned int one,ten,hundred,temp,ans=0;
	temp=hexnum;
	temp= (temp & 0x000f);
	one=temp;
	;
	temp=hexnum;
	temp= (temp & 0x00F0);
	temp=(temp >>4);
	ten=temp;
	;
	temp=hexnum;
	temp= (temp & 0x0F00);
	temp=(temp >>8);
	hundred=temp;
	;
	ans=(hundred * 16 *16) + (ten * 16) + (one *1);
	SENDSERIAL(ans);
	return(ans);
}

void transmit_dec(unsigned int num)
{
	unsigned char temp0,temp1,temp2,temp3,temp4;
	temp4 = (num % 10) + '0';
	num /= 10;
	temp3 = (num % 10) + '0';
	num /= 10;
	temp2 = (num % 10) + '0';
	num /= 10;
	temp1 = (num % 10) + '0';
	num /= 10;
	temp0 = num + '0';
	trans('@');
	trans(temp0);
	trans(temp1);
	trans(temp2);
	trans(temp3);
	trans(temp4);
	trans(' ');
}

void readmematstrt()
{
	for(i=0; i<33; i++)
  	{
    		parau.arrayu[i]= EEPROM_Read(2*i);
		prevmemarr[i]=parau.arrayu[i];
  	}
		temp=para.burnback.time;
		fburnbacktime=temp/10;
		;
		TypeU.LEDGROUP[0]=para.ledgp1; 
		TypeU.LEDGROUP[1]=para.ledgp2;
		TypeU.LEDGROUP[2]=para.ledgp3;		//restore 
		TypeU.LEDGROUP[3]=para.ledgp4;
		TypeU.LEDGROUP[4]=para.ledgp5;
		Type.recall=1;
		Type.save=1;
		Type.inching=1;
		Type.gascheck=1;
		Type.ocvcheck=1;	
		;
		if(para.preflow.time==0xffff || para.preflow.time > 10)
		{
			para.preflow.time=0;
		}
		if(para.postflow.time==0xffff || para.postflow.time > 20)
		{
			para.postflow.time=0;
		}
		if(para.burnback.time==0xffff || para.burnback.time > 20)
		{
			para.burnback.time=0;
		}
		if(para.spottime==0xffff || para.spottime > 30)
		{
			para.spottime=0;
		}
		if(para.pausetime==0xffff || para.pausetime > 30)
		{
			para.pausetime=0;
		}
		if(para.pwmtime==0xffff || para.pwmtime > 540)
		{
			para.pwmtime=0;
		}	
		if(para.weldcurrent==0xffff || para.weldcurrent > 140)
		{
		 	para.weldcurrent=0;
		}
		if(para.weldarcforce==0xffff || para.weldarcforce > 100)
		{	
			para.weldarcforce=0;
		}
		if(para.fcawws==0xffff || para.fcawws > 180)
		{	
			para.fcawws=0;
		}
		if(para.weld.wfs==0xffff || para.weld.wfs > 180)
		{
			para.weld.wfs=0;
		}
		if(para.fcaw.wfs==0xffff || para.fcaw.wfs > 180)
		{
			para.fcaw.wfs=0;
		}
		if(para.migws==0xffff || para.migws > 180)
		{
			para.migws=0;
		}
		if(para.fcawws==0xffff || para.fcawws > 65)
		{
			para.fcawws=0;
		}
		if(para.weld.volts==0xffff || para.weld.volts > 340)
		{
			para.weld.volts=0;
		}
		if(para.fcaw.volts==0xffff || para.fcaw.volts > 340)
		{
			para.fcaw.volts=0;
		}
		if(para.crater.wfs==0xffff || para.crater.wfs > 180)
		{
			para.crater.wfs=0;
		}
		if(para.fcaw.craterwfs==0xffff || para.fcaw.craterwfs > 180)
		{
			para.fcaw.craterwfs=0;
		}
		if(para.fcaw.cratervolts==0xffff || para.fcaw.cratervolts > 170)
		{
			para.fcaw.cratervolts=0;
		}
		if(para.crater.volts==0xffff || para.crater.volts > 170)
		{
			para.crater.volts=0;
		}
          	if(para.ledgp1==0xff)
		{
			Type.amp=0;
			Type.voltage=0;
		}
		if(para.ledgp2==0xff)
		{
			Type.weld=0;
		}
		if((para.ledgp3==0xff) || (para.ledgp3==0x7f))
		{
			Type.fe=0;
			Type.zeropteight=0;
		}
		if(para.ledgp4==0xff) 
		{
			Type.arco2=0;
			Type.twot=0;
		}
		if(para.ledgp5==0xff)
		{
			Type.mig=0;
			Type.fcaw=1;
		}
		if(WeldMode==0x01)			//MMA mode
		{
			cccvmode=1;
			TypeU.LEDGROUP[0]=0xFF; 
			TypeU.LEDGROUP[1]=0xFF;
			TypeU.LEDGROUP[2]=0xFF;		
			TypeU.LEDGROUP[3]=0xFF;
			TypeU.LEDGROUP[4]=0xFF;
			Type.mma=0;
			Type.mig=1;
			Type.tig=1;
			Type.fcaw=1;
			Type.amp=0;
			//VRDRELAYLAT=1;
			//VRDBYPASSLAT=0;
		}
		else if(WeldMode==0x02)	//TIG mode
		{
			cccvmode=1;
			TypeU.LEDGROUP[0]=0xFF; 
			TypeU.LEDGROUP[1]=0xFF;
			TypeU.LEDGROUP[2]=0xFF;		
			TypeU.LEDGROUP[3]=0xFF;
			TypeU.LEDGROUP[4]=0xFF;
			Type.mma=1;
			Type.mig=1;
			Type.tig=0;
			Type.fcaw=1;
			Type.amp=0;
			//VRDRELAYLAT=0;
			//VRDBYPASSLAT=1;
		}
		else if(WeldMode==0x03) 	//MIG mode
		{
			Type.mig=0;
			Type.fcaw=1;
			//tempdata=para.migws;
			//para.weld.wfs=tempdata;
			cccvmode=0;
			//memdata=EEPROM_Read(2*2);
			//VRDRELAYLAT=0;
			//VRDBYPASSLAT=1;
		}
		else if(WeldMode==0x04) 	//FCAW MODE
		{
			Type.mig=1;
			Type.fcaw=0;
			//tempdata=para.migws;
			//para.fcaw.wfs=tempdata;
			cccvmode=0;
			if(Type.onepttwo==0) // || Type.oneptsix=0)    //mahesh pharande 18.09.2013
			{
				para.ledgp3=0x7f;
				TypeU.LEDGROUP[2]=0x7F;		
				Type.fe=0;
				Type.onepttwo=0;
			}
			else if(Type.oneptsix==0) 
			{
				para.ledgp3=0x7f;
				TypeU.LEDGROUP[2]=0x7F;		
				Type.fe=0;
				Type.oneptsix=0;
			} 
			else
			{
				para.ledgp3=0x7f;
				TypeU.LEDGROUP[2]=0x7F;		
				Type.fe=0;
				Type.onepttwo=0;
			}
			
			{
				if(Type.twot==0)
				{
					TypeU.LEDGROUP[3]=0xFF;	
					para.ledgp4=0xff;
					Type.twot=0;
					Type.co2=0;	
				}
				else if(Type.fourt==0)
				{
					TypeU.LEDGROUP[3]=0xFF;	
					para.ledgp4=0xff;
					Type.co2=0;
					Type.fourt=0;
				}
				else
				{
					TypeU.LEDGROUP[3]=0xFF;	
					para.ledgp4=0xff;
					Type.twot=0;
					Type.co2=0;
				}	
			}
		}
		password= EEPROM_Read(34*2);
		passprotect= EEPROM_Read(35*2);
		if(password==0xFFFF || password >999)
		{
			password=0;
		      passprotect=0;
			EEPROM_Erase_Write((34*2),password);
			EEPROM_Erase_Write((35*2),passprotect);	
		}
		if(passprotect!=0x0000 && passprotect!=0x0001)
		{
			password=0;
		    	passprotect=0;
			EEPROM_Erase_Write((34*2),password);
			EEPROM_Erase_Write((35*2),passprotect);
		}
}









void readmematstrt1()				//reading memory at start of program
{
	for(i=0; i<33; i++)
  	{
    		parau.arrayu[i]= EEPROM_Read(2*i);
		prevmemarr[i]=parau.arrayu[i];
  	}
		temp=para.burnback.time;
		fburnbacktime=temp/10;
		;
		TypeU.LEDGROUP[0]=para.ledgp1; 
		TypeU.LEDGROUP[1]=para.ledgp2;
		TypeU.LEDGROUP[2]=para.ledgp3;		//restore 
		TypeU.LEDGROUP[3]=para.ledgp4;
		TypeU.LEDGROUP[4]=para.ledgp5;
		Type.recall=1;
		Type.save=1;
		Type.inching=1;
		Type.gascheck=1;
		Type.ocvcheck=1;	
		//*************************************************************************
		TypeU.LEDGROUP[0]=0xFF; //menu operation
		Type.amp=0;
		Type.voltage=0;
		;
		TypeU.LEDGROUP[1]=0xFF;
		Type.weld=0;
		;
		/*if(Type.tig==0) //by mahesh
		{
			TypeU.LEDGROUP[2]=0xFF;
			Type.fe=0;
			Type.zeropteight=0;
			Type.tig=0;
			TypeU.LEDGROUP[3]=0xFF;
			Type.arco2=0;
			Type.twot=0;
			para.preflow.time=0;
			para.postflow.time=0;
			para.spottime=0;
			para.pausetime=0;
		}*/
		{
			if(Type.mma==0)
			{
				TypeU.LEDGROUP[4]=0xFF;
				Type.mma=0;
			}	
			else if(Type.mig==0)
			{
				TypeU.LEDGROUP[4]=0xFF;
				Type.mig=0;
			}
		}
		//************************************************************************************
		//default if eeprom is empty at the start of the program.
		if(para.ledgp1==0xff)
		{
			Type.amp=0;
			Type.voltage=0;
		}
		if(para.ledgp2==0xff)
		{
			Type.weld=0;
		}
		if(para.ledgp3==0xff)
		{
			Type.fe=0;
			Type.zeropteight=0;
		}
		if(para.ledgp4==0xff)
		{
			Type.arco2=0;
			Type.twot=0;
		}
		if(para.ledgp5==0xff)
		{
	       // by mahesh
		  /*	
			Type.mma=1;
			if(Type.tig==1)
			{
				Type.mig=0;
			}
			else if(Type.tig==0)
			{
				Type.mig=1;
				para.preflow.time=0;
				para.postflow.time=0;
				para.spottime=0;
				para.pausetime=0;
			}
			*/
		//	if(Type.fcaw==1)
			{
				Type.mig=0;
				Type.fcaw=1;
			}
		//	else if(Type.fcaw==0)
		//	{
		//		Type.mig=1;
		//		Type.fcaw=1;
		//	}	
		}
		password= EEPROM_Read(34*2);
		passprotect= EEPROM_Read(35*2);
		if(password==0xFFFF || password >999)
		{
			password=0;
		      passprotect=0;
			EEPROM_Erase_Write((34*2),password);
			EEPROM_Erase_Write((35*2),passprotect);	
		}
		if(passprotect!=0x0000 && passprotect!=0x0001)
		{
			password=0;
		    	passprotect=0;
			EEPROM_Erase_Write((34*2),password);
			EEPROM_Erase_Write((35*2),passprotect);
		}
	
		if(para.preflow.time==0xffff || para.preflow.time > 10)
		{
			para.preflow.time=0;
		}
		if(para.postflow.time==0xffff || para.postflow.time > 20)
		{
			para.postflow.time=0;
		}
		if(para.burnback.time==0xffff || para.burnback.time > 20)
		{
			para.burnback.time=0;
		}
		if(para.spottime==0xffff || para.spottime > 30)
		{
			para.spottime=0;
		}
		if(para.pausetime==0xffff || para.pausetime > 30)
		{
			para.pausetime=0;
		}
		if(para.pwmtime==0xffff || para.pwmtime > 540)
		{
			para.pwmtime=0;
		}	
		if(para.weldcurrent==0xffff || para.weldcurrent > 140)
		{
		 	para.weldcurrent=0;
		}
		if(para.weldarcforce==0xffff || para.weldarcforce > 100)
		{	
			para.weldarcforce=0;
		}
		if(para.fcawws==0xffff || para.fcawws > 180)
		{	
			para.fcawws=0;
		}
		if(para.weld.wfs==0xffff || para.weld.wfs > 180)
		{
			para.weld.wfs=0;
		}
		if(para.fcaw.wfs==0xffff || para.fcaw.wfs > 180)
		{
			para.fcaw.wfs=0;
		}
		if(para.migws==0xffff || para.migws > 180)
		{
			para.migws=0;
		}
		if(para.fcawws==0xffff || para.fcawws > 65)
		{
			para.fcawws=0;
		}
		if(para.weld.volts==0xffff || para.weld.volts > 340)
		{
			para.weld.volts=0;
		}
		if(para.fcaw.volts==0xffff || para.fcaw.volts > 340)
		{
			para.fcaw.volts=0;
		}
		if(para.crater.wfs==0xffff || para.crater.wfs > 180)
		{
			para.crater.wfs=0;
		}
		if(para.fcaw.craterwfs==0xffff || para.fcaw.craterwfs > 180)
		{
			para.fcaw.craterwfs=0;
		}
		if(para.fcaw.cratervolts==0xffff || para.fcaw.cratervolts > 170)
		{
			para.fcaw.cratervolts=0;
		}
		if(para.crater.volts==0xffff || para.crater.volts > 170)
		{
			para.crater.volts=0;
		}
		{
		/*if(Type.mig==0)
		{
				tempdata=para.migws;
				para.weld.wfs=tempdata;
		}
		if(Type.fcaw==0)
		{
				tempdata=para.migws;
				para.fcaw.wfs=tempdata;
		}*/	
			/*else if(Type.tig==0)
			{
				tempdata=para.fcawws;
				para.weld.wfs=tempdata;
			}*/
		}		
		cccvmode=0;
}

void writemematstop()
{
	if(Type.mma==0)
	{
		if(prevweldcurrent!=para.weldcurrent)
		{
			EEPROM_Erase_Write((29*2),para.weldcurrent);
			prevweldcurrent=para.weldcurrent;
		}
		if(prevarcforce!=para.weldarcforce)
		{
			EEPROM_Erase_Write((30*2),para.weldarcforce);
			prevarcforce=para.weldarcforce;
		}
		if(prevpwmtime11!=para.pwmtime1)
		{ 
			EEPROM_Erase_Write((31*2),para.pwmtime1);
			prevpwmtime11=para.pwmtime1;
		}
		if(prevcccv!=cccvmode)
		{
			EEPROM_Erase_Write((33*2),cccvmode);
			prevcccv=cccvmode;
  		}     
	}
	else if(Type.mig==0 || Type.fcaw==0)
	{
		unsigned int i=0;
		tempdata=para.weld.wfs;
		para.migws=tempdata;
		for(i=0;i<29;i++)
		{
			EE_Addr=(i*2);
			EE_Data=parau.arrayu[i];
			if(EE_Data != prevmemarr[i])
			{
				EEPROM_Erase_Write(EE_Addr,EE_Data);
			}
		}
		for(i=0;i<29;i++)
		{
			prevmemarr[i]=parau.arrayu[i];
		}
		if(prevcccv!=cccvmode)
		{
			EEPROM_Erase_Write((33*2),cccvmode);
			prevcccv=cccvmode;
  		}  
		if(prevhr!= arconhr)
		{
			EEPROM_Erase_Write((37*2),arconhr);
			prevhr= arconhr;
  		}   
		if(prevmin!=arconmin)
		{
			EEPROM_Erase_Write((38*2),arconmin);
			prevmin=arconmin;
  		}   
		if(prevsec!=arconsec)
		{
			EEPROM_Erase_Write((39*2),arconsec);
			prevsec=arconsec;
  		}   
 	}

	/*else if(Type.tig==0 && (mc_model=='A' || mc_model=='B'))	// FCAW mode
	{
		tempdata=para.weld.wfs;
		para.fcawws=tempdata;
		EEPROM_Erase_Write((10*2),para.weld.volts);
		EEPROM_Erase_Write((32*2),para.fcawws);
		if(prevcccv!=cccvmode)
		{
			EEPROM_Erase_Write((33*2),cccvmode);
			prevcccv=cccvmode;
  		}   
	}*/
	else if(Type.tig==0)//&& (mc_model !='A' || mc_model !='B'))	// Tig mode
	{
		if(prevweldcurrent!=para.weldcurrent)
		{
			EEPROM_Erase_Write((29*2),para.weldcurrent);
			prevweldcurrent=para.weldcurrent;
		}
		if(prevarcforce!=para.weldarcforce)
		{
			EEPROM_Erase_Write((30*2),para.weldarcforce);
			prevarcforce=para.weldarcforce;
		}
		if(prevpwmtime11!=para.pwmtime1)
		{ 
			EEPROM_Erase_Write((31*2),para.pwmtime1);
			prevpwmtime11=para.pwmtime1;
		}
		if(prevcccv!=cccvmode)
		{
			EEPROM_Erase_Write((33*2),cccvmode);
			prevcccv=cccvmode;
  		}   	
	}
}
void lowvtg_init()
{
	unsigned int i,j;
	for(i=0;i<5000;i++)
	{
		for(j=0;j<500;j++);
	}
}
/*unsigned char scanthswitch()
{
	unsigned char thermalerr=0;
	if(THERMALIN==1)
	{
		thermalerr=1;
	}
	else
	{
		thermalerr=0;
	}
	return (thermalerr);
}*/
//*************************************************************************************************
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%CV MODE%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//&&&                            MIG MODE                                                                                           %%%%
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&	
void updatedatacv(unsigned char encres,unsigned char encres1) //exchanged enc and enc1
{
			if(chkpausetime==1)
			{
				if(cyclestrt==0)
				{
					para.pausetime=updatedata(para.pausetime,min.pausetime,max.pausetime,encres);
				}
				win2dpcnt=float_to_ascii_str(&win2[0],para.pausetime);
				if(win2dpcnt==1)
				{
					win2[2]='/';		//for disply empty display
				}
				win1[0]='P';
				win1[1]='T';
				win1[2]='M';
				win1dpcnt=3;
				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
				Type.time=0;
			}
		
//################################################################################
			if(Dispmampf==1)
			{
				win1[0]='A';
				win1[1]='M';
				win1[2]='P';
				feedamp=(fwirespeed*10.0)/12.0;
				feedamp=feedamp/10.0;
    				if(feedamp < 1.0)
				feedamp=1.0;
				win2dpcnt=float_to_ascii_str(&win2[0],feedamp);
				if(win2dpcnt==1)
					win2[2]='/';		//for disply empty display
				win1dpcnt=3;
				//win2dpcnt=3;
				for(ijk=0;ijk<=200;ijk++)
				delay();	
			}
			else if(mesgdispf==1)
			{
				if(acrmesg==0 && unitf==0)
				{
					win1[0]='A';
					win1[1]='R';
					win1[2]='C';
					win1dpcnt=3;
					win2[0]='O';
					win2[1]='N';
					win2[2]='/';
					win2dpcnt=3;
					if(count_1sec==1)
					{
						acrmesg=1;
						unitf=0;
						count_1ms=0;
				  		count_10ms=0;
				   		count_100ms=0;
				   		count_1sec=0;
						arcrstf=0;
						arczerof=0;
					}
				}
				else if(acrmesg==1 && unitf==0)
				{
					win1[0]='H';
					win1[1]='R';
					win1[2]='/';
					win1dpcnt=3;
					win2[0]='M';
					win2[1]='I';
					win2[2]='N';
					win2dpcnt=3;
					if(count_1sec==1)
					{
						archr=EEPROM_Read(2*37);
						arcmin=EEPROM_Read(2*38);
						acrmesg=1;
                        		unitf=1;
						count_1ms=0;
				  		count_10ms=0;
				   		count_100ms=0;
				   		count_1sec=0;
					}
				}
				else if(acrmesg==1 && unitf==1)
				{
					win1dpcnt=float_to_ascii_str(&win1[0],archr);
			    		win2dpcnt=float_to_ascii_str(&win2[0],arcmin);
					if(win2dpcnt==1)
					win2[2]='/';		//for disply empty display
					if(win1dpcnt==1)
					win1[2]='/';		//for disply empty display
					if(count_1sec >=2 && key!='O'&& arcrstf==0)
					{
						acrmesg=0;
						unitf=0;
						mesgdispf=0;
						count_1ms=0;
				  		count_10ms=0;
				   		count_100ms=0;
				   		count_1sec=0;
					}
					
					if(count_1sec > 3 && arcrstf==0 && key=='O' && passprotect==0)
					{
						arcrstf=1;
					}
					else if(arcrstf==1)
					{
						if(chkpass==0)
						{
							passtemp=updatedata(passtemp,0,999,encres);
							win2dpcnt=float_to_ascii_str(&win2[0],passtemp);
							if(win2dpcnt==1)
							{
								win2[2]='/';		//for disply empty display
							}
							win1[0]='P';
							win1[1]='A';
							win1[2]='S';
							win1dpcnt=3;
							TypeU.LEDGROUP[0]=0xFF;
							Type.time=0;
							enblencoder=1;
							if(passtemp >1)
							{
								enblpasskey=1;
							}
						}			
						else if(chkpass==1)
						{
							if(passtemp==password) 
							{
								if(arczerof==0)
								{
									win1[0]='P';
									win1[1]='A';
									win1[2]='S';
									win1dpcnt=3;
									win2[0]='O';
									win2[1]='K';
									win2[2]='/';
									win2dpcnt=3;
									arconsec=0;
									arconmin=0;
									arconhr=0;
									EEPROM_Erase_Write((39*2),arconsec);
									EEPROM_Erase_Write((38*2),arconmin);
									EEPROM_Erase_Write((37*2),arconhr);
									archr=arconhr;
									arcmin=arconmin;
									arczerof=1;
								}
								else
								{
									win1[0]='A';
									win1[1]='R';
									win1[2]='C';
									win1dpcnt=3;
									win2[0]='R';
									win2[1]='S';
									win2[2]='T';
									win2dpcnt=3;
								}
	           				    }
							else if(passtemp!=password)
							{
								win1[0]='P';
								win1[1]='A';
								win1[2]='S';
								win1dpcnt=3;
								win2[0]='E';
								win2[1]='R';
								win2[2]='R';
								win2dpcnt=3;
								for(i=0;i<2000;i++)//5000 200
								delay();
							}
							if(count_1sec==2)
							{
								mesgsvd=0;
								setpasswordf=0;
								count_1ms=0;
								count_10ms=0;
								count_100ms=0;
								count_1sec=0;
								Type.save=1;
								chkpass=0;
								passtemp=0;
								arcrstf=0;
								//chkpass=0;
								enblpasskey=0;
								setpasswordf=0;
								enblencoder=0;
								arczerof=0;
								acrmesg=0;
								unitf=0;
								mesgdispf=0;
										
							}
	   					}
				
					}
		     		}
			}
//################################################################################
			else if(Type.crater==0 && cyclestrt==0)
			{
				float temp=0;
				unsigned int wirespeed=0,current1=0,current2=0;
				if(Type.mig==0) //|| Type.fcaw==0)
				{
					para.crater.volts=updatedata(para.crater.volts,min.crater.volts,max.crater.volts,encres);
					cratervoltage=(para.crater.volts*cratervoltfactor);//0.27);//0.22);
				
					para.crater.wfs=updatedata(para.crater.wfs,min.crater.wfs,maxmigwf,encres1);
					temp=para.crater.wfs;
					fwirespeed=temp*0.101;
					if((fwirespeed!=prevfws) || keychange1==1 )
					{
						keychange1=0;
						wirespeed=fwirespeed;
						current1=findmatindex1(wirespeed);
						current2=findmatindex1((wirespeed+1));
						autocur=current1+((fwirespeed-wirespeed)*(current2-current1));
					}
					prevfws=fwirespeed;
				}
				else if(Type.fcaw==0)
				{
					para.fcaw.cratervolts=updatedata(para.fcaw.cratervolts,min.fcaw.cratervolts,max.fcaw.cratervolts,encres);
					cratervoltage=(para.fcaw.cratervolts*cratervoltfactor);//0.27);//0.22);
				
					para.fcaw.craterwfs=updatedata(para.fcaw.craterwfs,min.fcaw.craterwfs,maxmigwf,encres1);
					temp=para.fcaw.craterwfs;
					fwirespeed=temp*0.101;
					if((fwirespeed!=prevfws) || keychange1==1 )
					{
						keychange1=0;
						wirespeed=fwirespeed;
						current1=findmatindex1(wirespeed);
						current2=findmatindex1((wirespeed+1));
						autocur=current1+((fwirespeed-wirespeed)*(current2-current1));
					}
					prevfws=fwirespeed;
				}
				
				//display current w.r.t.wirespeedMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
				/*if(Type.tig==0)
				{
					para.crater.wfs=updatedata(para.crater.wfs,min.crater.wfs,maxfcawwf,encres1);
					temp=para.crater.wfs;
					fwirespeed=temp*0.101;
					if((fwirespeed!=prevfws) || keychange1==1 )
					{
						keychange1=0;
						wirespeed=fwirespeed;
						current1=findmatindex4(wirespeed);
						current2=findmatindex4((wirespeed+1));
						autocur=current1+((fwirespeed-wirespeed)*(current2-current1));
					}
				}*/
				//prevfws=fwirespeed;
				//display current w.r.t.wirespeedMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
				if(DispWSf==1)
					win1dpcnt=float_to_ascii_str(&win1[0],fwirespeed);
				else
					win1dpcnt=float_to_ascii_str(&win1[0],autocur);
				win2dpcnt=float_to_ascii_str(&win2[0],cratervoltage);
				if(win1dpcnt==1)
				{
					win1[2]='/';		//for disply empty display
				}
				if(win2dpcnt==1)
				{
					win2[2]='/';		//for disply empty display
				}
			}
			else if(Type.weld==0 && cyclestrt==0 && setmemloc==0 && setrecall==0 && setupmode==0 && setpasswordf==0)//show pwmtime and voltage on display after welding off
			{
				if(Type.mig==0) 
				{
						if(errflag2=='N' || (errflag2=='U' && encres1=='+') || (errflag2=='O' && encres1=='-'))
						para.weld.wfs=updatedata(para.weld.wfs,min.weld.wfs,maxmigwf,encres1);
					     {
							do
							{
								if(((mc_model=='A')  && autocur > 400) || ((mc_model=='C')  && autocur > 250))
								para.weld.wfs=para.weld.wfs-1;

								temp1=para.weld.wfs;
								fwirespeed=temp1*0.101;//30;
//----------------------------------------------------								
								wirespeed=fwirespeed;
								if(wirespeed<=20)
								{
									fpwmtime=fwirespeed*WFPWMCALFACTOR;									
								}
								else
								{
									fpwmtime=20*WFPWMCALFACTOR;									
								}
								para.pwmtime=fpwmtime;						
//----------------------------------------------------	
								if((fwirespeed!=prevfws) || keychange1==1)
								{
									keychange1=0;
									wirespeed=fwirespeed;									
//									if(wirespeed <= 220)
//									{																	
				                        current1=findmatindex1(wirespeed);
										current2=findmatindex1((wirespeed+1));
										autocur=current1+((fwirespeed-wirespeed)*(current2-current1));				
										if(Type.automan==0)
										{
											voltage1=findmatindex2(wirespeed);
											voltage2=findmatindex2((wirespeed+1));
											autovolt=voltage1+((fwirespeed-wirespeed)*(voltage2-voltage1));
											para.weld.volts=((autovolt - (cvoffset*10))* 40.0)/vtgmulti; //20
										}
//									}
									/*
									else
									{
									// above 22mtr/min cal current and voltage.
										autocur = CalCurrAsPerWirespeed(wirespeed);
										if(Type.automan==0)
										{
											autovolt = CalVolAsPerWiresped(wirespeed);
											para.weld.volts=((autovolt - (cvoffset*10))* 40.0)/vtgmulti; //20
										}		
									}
									*/
									
								}	
								prevfws=fwirespeed;	
							}
							while(((mc_model=='A')  && autocur > 400) || ((mc_model=='C')  && autocur > 250));
						}

					if(errflag1=='N' || (errflag1=='U' && encres=='+') || (errflag1=='O' && encres=='-')) 
						para.weld.volts=updatedata(para.weld.volts,min.weld.volts,max.weld.volts,encres);
					paravolt=para.weld.volts;
					para.pwmtime1=(paravolt/4.0);//2.0);	
					setvoltage=(((paravolt*vtgmulti)/400.0) + cvoffset);//0.215);//200
					
					sendcur=autocur;				
					sendvtg=setvoltage*10;	
					{	
						if(setvoltage >=maxmigvolts) //40.0
							errflag1='O';
						else if(setvoltage <=15.0)
							errflag1='U';
						else
							errflag1='N';
					}
					{	
						if(autocur >=maxmmacurrent) 
							errflag2='O';
						else if(autocur<=10.0)
							errflag2='U';
						else
							errflag2='N';
					}
					if(transon==1)//enable only when data received and encoder varies
					{
						transon=0;
						count_1ms=0;
						count_10ms=0;
						count_100ms=0;
						sendtoremotef=0;
						transtoremote(para.weld.volts,sendvtg,para.weld.wfs,sendcur,model,errflag1,errflag2);
						IEC0bits.U1RXIE=1; //Uart reception interrupt enable	38400 baud rate
					}
				
			}
//*************************************************************************************************
				else if(Type.fcaw==0)
				{
					if(errflag2=='N' || (errflag2=='U' && encres1=='+') || (errflag2=='O' && encres1=='-'))
					para.fcaw.wfs=updatedata(para.fcaw.wfs,min.fcaw.wfs,maxmigwf,encres1);
					{
						do
						{
							if(((mc_model=='A')  && autocur > 400) || ((mc_model=='C')  && autocur > 250))
								para.fcaw.wfs=para.fcaw.wfs-1;

								temp1=para.fcaw.wfs;
								fwirespeed=temp1*0.101;//30;
//----------------------------------------------------								
								wirespeed=fwirespeed;
								if(wirespeed<=20)
								{
									fpwmtime=fwirespeed*WFPWMCALFACTOR;									
								}
								else
								{
									fpwmtime=20*WFPWMCALFACTOR;									
								}
								para.pwmtime=fpwmtime;						
//----------------------------------------------------								
								if((fwirespeed!=prevfws) || keychange1==1 )
								{
									keychange1=0;
									wirespeed=fwirespeed;
//									if(wirespeed <= 220)
//									{
				                        current1=findmatindex1(wirespeed);
										current2=findmatindex1((wirespeed+1));
										autocur=current1+((fwirespeed-wirespeed)*(current2-current1));
										if(Type.automan==0)
										{
											voltage1=findmatindex2(wirespeed);
											voltage2=findmatindex2((wirespeed+1));
											autovolt=voltage1+((fwirespeed-wirespeed)*(voltage2-voltage1));
											para.fcaw.volts=((autovolt - (cvoffset*10))* 40.0) /vtgmulti; //20
										}										
//									}
									/*
									else
									{
									// above 22mtr/min cal current and voltage.
										autocur = CalCurrAsPerWirespeed(wirespeed);
										if(Type.automan==0)
										{
											autovolt = CalVolAsPerWiresped(wirespeed);
											para.weld.volts=((autovolt - (cvoffset*10))* 40.0)/vtgmulti; //20
										}									
									}
									*/																			
								}
						 		prevfws=fwirespeed;
						}
						while(((mc_model=='A')  && autocur > 400) || ((mc_model=='C')  && autocur > 250));
					}

					if(errflag1=='N' || (errflag1=='U' && encres=='+') || (errflag1=='O' && encres=='-')) //exchange enc and enc1
						para.fcaw.volts=updatedata(para.fcaw.volts,min.fcaw.volts,max.fcaw.volts,encres);//exchange enc and enc1
					paravolt=para.fcaw.volts;
					para.pwmtime1=(paravolt/4.0);//2.0);	
					setvoltage=(((paravolt*vtgmulti)/400.0) + cvoffset);//0.215);//200
					
					sendcur=autocur;				
					sendvtg=setvoltage*10;
					{	
						if(autocur >=maxmmacurrent) 
							errflag2='O';
						else if(autocur<=10.0)
							errflag2='U';
						else
							errflag2='N';
					}
					{
						if(setvoltage >=maxmigvolts) //40.0
							errflag1='O';
						else if(setvoltage <=15.0)
							errflag1='U';
						else
							errflag1='N';
					}
					if(transon==1)//enable only when data received and encoder varies
					{
						transon=0;
						count_1ms=0;
						count_10ms=0;
						count_100ms=0;
						sendtoremotef=0;
						transtoremote(para.fcaw.volts,sendvtg,para.fcaw.wfs,sendcur,model,errflag1,errflag2);
						IEC0bits.U1RXIE=1; //Uart reception interrupt enable	38400 baud rate
					}

				}
//*************************************************************************************************
			if(updatedisp==1)
				{
					if(Pressure_ERRf==0)
					{
							if(DispWSf==1)
								win1dpcnt=float_to_ascii_str(&win1[0],fwirespeed);
							else
								win1dpcnt=float_to_ascii_str(&win1[0],autocur);//fwirespeed);
							win2dpcnt=float_to_ascii_str(&win2[0],setvoltage);//para.weld.volts);//para.pwmtime1);//autocur);//,fpwmtime);
					}
					else
					{
						win1[0]='E';
						win1[1]='R';
						win1[2]='R';
						win1dpcnt=3;
						win2[0]='0';
						win2[1]='0';
						win2[2]='7';
						win2dpcnt=3;
					}
					updatedisp=0;
				}		
				if(win1dpcnt==1)
				{
					win1[2]='/';					//for display empty display
				}
				if(win2dpcnt==1)
				{
					win2[2]='/';
				}
				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
				if(DispWSf==1)
					Type.speed=0;
				else
					Type.amp=0;
				Type.voltage=0;	
			}
			else if((Type.weld==0 || Type.crater==0) && cyclestrt==1 && setmemloc==0 && setrecall==0 && setupmode==0 && setpasswordf==0 && Dispmampf==0) //show current and voltage during welding on
			{
		       		if(updatedisp==1)
					{
						if(autoinch==0 && Pressure_ERRf==0 && Motorerrf==0)
						{
							maheshkp=1;
							tempdisp1=dispfbcurr;
							tempdisp2=dispfbvtg;
							win1dpcnt=float_to_ascii_str(&win1[0],tempdisp1);//dispfbcurr);
							win2dpcnt=float_to_ascii_str(&win2[0],tempdisp2);//dispfbvtg);
                    				maheshkp=0;
							updatedisp=0;
						}
						else if (autoinch==1 && Pressure_ERRf==0 && Motorerrf==0)
						{
							maheshkp=1;
							win1[0]='E';
							win1[1]='R';
							win1[2]='R';
							win1dpcnt=3;
							win2[0]='0';
							win2[1]='0';
							win2[2]='4';
							win2dpcnt=3;
							maheshkp=0;
							updatedisp=0;
	        				}
						else if(autoinch==0 && Pressure_ERRf==1 && Motorerrf==0)
				           {
							maheshkp=1;
							win1[0]='E';
							win1[1]='R';
							win1[2]='R';
							win1dpcnt=3;
							win2[0]='0';
							win2[1]='0';
							win2[2]='7';
							win2dpcnt=3;
							maheshkp=0;
							updatedisp=0;
							drive_motor(0);
							GASONLAT=0;
							ARCONLAT=0;
							genref(0);	//generate reference
						}
						else if(autoinch==0 && Pressure_ERRf==0 && Motorerrf==1)
						{
							maheshkp=1;
							win1[0]='E';
							win1[1]='R';
							win1[2]='R';
							win1dpcnt=3;
							win2[0]='0';
							win2[1]='0';
							win2[2]='5';
							genref(0);								//generate reference
							drive_motor(0);
							GASONLAT=0;
							ARCONLAT=0;	
							win2dpcnt=3;
							maheshkp=0;
							updatedisp=0;
						}
					}

					if(Type.mig==0)
					{	
						para.weld.wfs=updatedata(para.weld.wfs,min.weld.wfs,maxmigwf,encres1);//exchange enc and enc1
						//#######################################################################
						{
							do
							{
								if(((mc_model=='A')  && autocur > 400) || ((mc_model=='C')  && autocur > 250))
								para.weld.wfs=para.weld.wfs-1;

								temp1=para.weld.wfs;
								fwirespeed=temp1*0.101;//30;
								fpwmtime=fwirespeed*3.0;
								para.pwmtime=fpwmtime;
								if((fwirespeed!=prevfws) || keychange1==1)
								{
									keychange1=0;
									wirespeed=fwirespeed;
			                        		current1=findmatindex1(wirespeed);
									current2=findmatindex1((wirespeed+1));
									autocur=current1+((fwirespeed-wirespeed)*(current2-current1));
			
								/*	if(Type.automan==0)
									{
										voltage1=findmatindex2(wirespeed);
										voltage2=findmatindex2((wirespeed+1));
										autovolt=voltage1+((fwirespeed-wirespeed)*(voltage2-voltage1));
										para.weld.volts=((autovolt - (cvoffset*10))* 40.0)/vtgmulti; //20
									}
								*/
								}	
								prevfws=fwirespeed;	
							}
							while(((mc_model=='A')  && autocur > 400) || ((mc_model=='C')  && autocur > 250));
						}
						//########################################################################
						//temp=para.weld.wfs;
						//fwirespeed=temp*0.101;//30;
						//fpwmtime=fwirespeed*3.0;
						//para.pwmtime=fpwmtime;
						;
						para.weld.volts=updatedata(para.weld.volts,min.weld.volts,max.weld.volts,encres);//exchange enc and enc1
						paravolt=para.weld.volts;
						para.pwmtime1=(paravolt/4.0);
						paravolt=para.weld.volts;
						setvoltage=(((paravolt*vtgmulti)/400.0) + cvoffset);//0.215);//200
						sendcur=fbcurr;				
						sendvtg=fbvtg*10;
						if(transon==1)//enable only when data received and encoder varies
						{
							transon=0;
							count_1ms=0;
							count_10ms=0;
							count_100ms=0;
							sendtoremotef=0;
							transtoremote(para.weld.volts,sendvtg,para.weld.wfs,sendcur,model,errflag1,errflag2);
							IEC0bits.U1RXIE=1; //Uart reception interrupt enable	38400 baud rate
						}
					}
					else if(Type.fcaw==0)
					{
						para.fcaw.wfs=updatedata(para.fcaw.wfs,min.fcaw.wfs,maxmigwf,encres1);//exchange enc and enc1
						//###############################################################################
						{
							do
							{
								if(((mc_model=='A')  && autocur > 400) || ((mc_model=='C')  && autocur > 250))
									para.fcaw.wfs=para.fcaw.wfs-1;
	
									temp1=para.fcaw.wfs;
									fwirespeed=temp1*0.101;//30;
									fpwmtime=fwirespeed*3.0;
									para.pwmtime=fpwmtime;
									if((fwirespeed!=prevfws) || keychange1==1 )
									{
										keychange1=0;
										wirespeed=fwirespeed;
				                        		current1=findmatindex1(wirespeed);
										current2=findmatindex1((wirespeed+1));
										autocur=current1+((fwirespeed-wirespeed)*(current2-current1));
									//	if(Type.automan==0)
									//	{
									//		voltage1=findmatindex2(wirespeed);
									//		voltage2=findmatindex2((wirespeed+1));
									//		autovolt=voltage1+((fwirespeed-wirespeed)*(voltage2-voltage1));
									//		para.fcaw.volts=((autovolt - (cvoffset*10))* 40.0) /vtgmulti; //20
									//	}
									}
							 		prevfws=fwirespeed;
							}
							while(((mc_model=='A')  && autocur > 400) || ((mc_model=='C')  && autocur > 250));
						}	
						//###############################################################################
						//temp1=para.fcaw.wfs;
						//fwirespeed=temp1*0.101;//30;
						//fpwmtime=fwirespeed*3.0;
						//para.pwmtime=fpwmtime;
						;
						para.fcaw.volts=updatedata(para.fcaw.volts,min.fcaw.volts,max.fcaw.volts,encres);//exchange enc and enc1
						paravolt=para.fcaw.volts;
						para.pwmtime1=(paravolt/4.0);
						paravolt=para.fcaw.volts;
						setvoltage=(((paravolt*vtgmulti)/400.0) + cvoffset);//0.215);//200
						sendcur=fbcurr;				
						sendvtg=fbvtg*10;
						if(transon==1) //enable only when data received and encoder varies
						{
							transon=0;
							count_1ms=0;
							count_10ms=0;
							count_100ms=0;
							sendtoremotef=0;
							transtoremote(para.fcaw.volts,sendvtg,para.fcaw.wfs,sendcur,model,errflag1,errflag2);
							IEC0bits.U1RXIE=1; //Uart reception interrupt enable	38400 baud rate
						}
					}
						if(setvoltage >=maxmigvolts)//46)//40)
						{	errflag1='O';}
						else if(setvoltage <=15)
						{	errflag1='U';}
						else
						{	errflag1='N';}
							
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.amp=0;
					Type.voltage=0;
					
			}
			else if(setmemloc==1 && setrecall==0 && setpasswordf==0)//&& Type.automan==1)
			{
				if(displprev==0 && savemesg==0)
				{
					memlocation=updatedata(memlocation,1,5,encres);
					win2dpcnt=float_to_ascii_str(&win2[0],memlocation);
					if(win2dpcnt==1)
					{
						win2[2]='/';		//for disply empty display
					}
					win1[0]='L';
					win1[1]='O';
					win1[2]='C';
					win1dpcnt=3;
				}
				else if(displprev==1 && savemesg==0)
				{
					win1dpcnt=float_to_ascii_str(&win1[0],fwirespeed);
					win2dpcnt=float_to_ascii_str(&win2[0],fpwmtime);
					if(win1dpcnt==1)
					{
						win1[2]='/';					//for display empty display
					}
					if(win2dpcnt==1)
					{
						win2[2]='/';
					}
					if(count_1sec==1)
					{
						savemesg=1;
						count_1ms=0;
						count_10ms=0;
						count_100ms=0;
						count_1sec=0;
						for(i=0;i<32;i++)						//save memory  
						{
							if(Type.mig==0)
								EE_Addr=(40*memlocation*2)+(i*2);
							else if(Type.fcaw==0)
								EE_Addr=(40*(memlocation+5)*2)+(i*2);
							EE_Data=parau.arrayu[i];
							EEPROM_Erase_Write(EE_Addr,EE_Data);
						}
					}
				}
				else
				{
					memlocation=updatedata(memlocation,1,5,encres);
					win2dpcnt=float_to_ascii_str(&win2[0],memlocation);
					if(win2dpcnt==1)
					{
						win2[2]='/';		//for disply empty display
					}
					win1[0]='S';
					win1[1]='V';
					win1[2]='D';
					win1dpcnt=3;
					if(count_1sec ==1)
					{
						savemesg=0;
						displprev=0;
						setmemloc=0;
						count_1ms=0;
						count_10ms=0;
						count_100ms=0;
						count_1sec=0;
						Type.save=1;
					}
				}
			}
//**********************************************************************************************************************************************
			else if(setmemloc==0 && setrecall==1 && setpasswordf==0)// && Type.automan==1)
			{
					float temp=0;
					if(disprcl==0 && disrcldata==0)
					{
						memlocation=updatedata(memlocation,1,5,encres);
						win2dpcnt=float_to_ascii_str(&win2[0],memlocation);
						if(win2dpcnt==1)
						{
							win2[2]='/';		//for disply empty display
						}
						win1[0]='L';
						win1[1]='O';
						win1[2]='C';
						win1dpcnt=3;
					}
					else if(disprcl==1 && disrcldata==0)
					{
						memlocation=updatedata(memlocation,1,5,encres);
						win2dpcnt=float_to_ascii_str(&win2[0],memlocation);
						if(win2dpcnt==1)
						{
							win2[2]='/';		//for disply empty display
						}
						win1[0]='R';
						win1[1]='C';
						win1[2]='L';
						win1dpcnt=3;
						if(count_1sec ==1)
						{
							savemesg=0;
							displprev=0;
							setmemloc=0;
							count_1ms=0;
							count_10ms=0;
							count_100ms=0;
							count_1sec=0;
							disrcldata=1;
					
								for(i=0; i<33; i++)	//reading current multiplier count extra 	//read memory memory  
  								{
      								if(Type.mig==0)
										EE_Addr=(40*memlocation*2)+(i*2);
									else if(Type.fcaw==0)
										EE_Addr=(40*(memlocation+5)*2)+(i*2);	
									parau.arrayu[i]= EEPROM_Read(EE_Addr);//2*i);
  								}
									temp=para.burnback.time;
									fburnbacktime=temp/10;
									TypeU.LEDGROUP[0]=para.ledgp1; 
									TypeU.LEDGROUP[1]=para.ledgp2;
									TypeU.LEDGROUP[2]=para.ledgp3;		//restore 
									TypeU.LEDGROUP[3]=para.ledgp4;
									temp=para.pwmtime;
									fpwmtime=(0.101 * temp);
			
									temp=para.pwmtime;
									fwirespeed=temp/30;
									//default if eeprom is empty at the start of the program.
									if(para.ledgp1==0xff)
									{
										Type.amp=0;
										Type.voltage=0;
									}
									if(para.ledgp2==0xff)
									{
										Type.weld=0;
									}
									if(para.ledgp3==0xff)
									{
										Type.fe=0;
										Type.zeropteight=0;
									}
									if(para.ledgp4==0xff)
									{
										Type.arco2=0;
										Type.twot=0;
									}
							}//end of if
					}//end of else if
					else
					{
						win1dpcnt=float_to_ascii_str(&win1[0],fwirespeed);
						win2dpcnt=float_to_ascii_str(&win2[0],fpwmtime);
						if(win1dpcnt==1)
						{
							win1[2]='/';					//for display empty display
						}
						if(win2dpcnt==1)
						{
							win2[2]='/';
						}
						if(count_1sec ==1)
						{
							
							setrecall=0;
							disprcl=0;
							disrcldata=0;
							count_1ms=0;
							count_10ms=0;
							count_100ms=0;
							count_1sec=0;
							Type.recall=1;
						}
					}
				}
//******************************************************************************************************************************************************
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		else if(setpasswordf==1)
		{
			if(passprotect==0)
			{
				if(mesgsvd==0)
				{
					lockvalue=updatedata(lockvalue,0,999,encres);//min.password,max.password,encres);
					win2dpcnt=float_to_ascii_str(&win2[0],lockvalue);
					if(win2dpcnt==1)
					{
						win2[2]='/';		//for disply empty display
					}
					win1[0]='L';
					win1[1]='C';
					win1[2]='K';
					win1dpcnt=3;
					TypeU.LEDGROUP[0]=0xFF;
					Type.time=0;
					if(lockvalue > 0)
					{
						savepassf=1;
					}
					else
					{
						savepassf=0;
					}
				}
				else
				{
					if(savepassf==1)
					{
						Type.save=0;
						password=lockvalue;
						//password=updatedata(password,0,999,encres);
						win2dpcnt=float_to_ascii_str(&win2[0],password);
						if(win2dpcnt==1)
						{
							win2[2]='/';		//for disply empty display
						}
						win1[0]='S';
						win1[1]='V';
						win1[2]='D';
						win1dpcnt=3;
						if(count_1sec==1)
						{
							mesgsvd=0;
							setpasswordf=0;
							count_1ms=0;
							count_10ms=0;
							count_100ms=0;
							count_1sec=0;
							Type.save=1;
							passprotect=1;
							savepassf=0;
							lockvalue=0;
							EEPROM_Erase_Write((34*2),password);
							EEPROM_Erase_Write((35*2),passprotect);
							writemematstop();
							for(ijk=0;ijk<=1000;ijk++)	
                        			for(abc=0;abc<100;abc++);
						}
					}
					else
					{
						mesgsvd=0;
						setpasswordf=0;
						count_1ms=0;
						count_10ms=0;
						count_100ms=0;
						count_1sec=0;
						Type.save=1;
						passprotect=0;
						savepassf=0;
					}
				}
			}//if passprotect==0;
			else
			{
				if(chkpass==0)
				{
					passtemp=updatedata(passtemp,0,999,encres);
					win2dpcnt=float_to_ascii_str(&win2[0],passtemp);
					if(win2dpcnt==1)
					{
						win2[2]='/';		//for disply empty display
					}
					win1[0]='P';
					win1[1]='A';
					win1[2]='S';
					win1dpcnt=3;
					TypeU.LEDGROUP[0]=0xFF;
					Type.time=0;
					enblencoder=1;
					if(passtemp >1)
					{
						enblpasskey=1;
					}
				}			
				else if(chkpass==1)
				{
					if(passtemp==password)
					{
						win1[0]='P';
						win1[1]='A';
						win1[2]='S';
						win1dpcnt=3;
						win2[0]='O';
						win2[1]='K';
						win2[2]='/';
						win2dpcnt=3;
						passerr=1;
					}
					else if(passtemp!=password)
					{
						win1[0]='P';
						win1[1]='A';
						win1[2]='S';
						win1dpcnt=3;
						win2[0]='E';
						win2[1]='R';
						win2[2]='R';
						win2dpcnt=3;
						passprotect=1;
					}
					if(count_1sec==2)
					{
						mesgsvd=0;
						setpasswordf=0;
						count_1ms=0;
						count_10ms=0;
						count_100ms=0;
						count_1sec=0;
						Type.save=1;
						chkpass=0;
						passtemp=0;
						enblpasskey=0;
						setpasswordf=0;
						enblencoder=0;
						if(passerr==1)
						{
							passprotect=0;
							passerr=0;
						}
						EEPROM_Erase_Write((34*2),password);
						EEPROM_Erase_Write((35*2),passprotect);
					}
				}
			}
		}
//##################################################################################################################################################
		else if(Type.preflow==0)
		{
			if(cyclestrt==0)
			{
				para.preflow.time=updatedata(para.preflow.time,min.preflow.time,max.preflow.time,encres);
			}
			win2dpcnt=float_to_ascii_str(&win2[0],para.preflow.time);
			if(win2dpcnt==1)
			{
				win2[2]='/';		//for disply empty display
			}
			win1[0]='P';
			win1[1]='R';
			win1[2]='E';
			win1dpcnt=3;
			TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
			Type.time=0;
		}
		else if(Type.burnback==0 && (Type.twot==0 || Type.fourt==0 || para.burnbackf==1))
		{
			float temp;
			if(cyclestrt==0)
			{
				para.burnback.time=updatedata(para.burnback.time,min.burnback.time,max.burnback.time,encres);
			}
			temp=para.burnback.time;
			fburnbacktime=(0.101 * temp);
			win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
			if(win2dpcnt==1)
			{
				win2[2]='/';		//for disply empty display
			}
			win1[0]='B';
			win1[1]='R';
			win1[2]='N';
			win1dpcnt=3;
			TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
			Type.time=0;
		}
	
		else if(Type.postflow==0 && (Type.twot==0 || Type.fourt==0 || para.postflowf==1))
		{
			if(cyclestrt==0)
			{
				para.postflow.time=updatedata(para.postflow.time,min.postflow.time,max.postflow.time,encres);
			}
			win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
			if(win2dpcnt==1)
			{
				win2[2]='/';		//for disply empty display
			}
			win1[0]='P';
			win1[1]='S';
			win1[2]='T';
			win1dpcnt=3;
			TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
			Type.time=0;
		}
		else if((Type.multispot==0 || Type.spot==0) && para.spottimef==1 && para.pausetimef==0)
		{
			if(cyclestrt==0)
			{
				para.spottime=updatedata(para.spottime,min.spottime,max.spottime,encres);
			}
			win2dpcnt=float_to_ascii_str(&win2[0],para.spottime);
			if(win2dpcnt==1)
			{
				win2[2]='/';		//for disply empty display
			}
			win1[0]='S';
			win1[1]='T';
			win1[2]='M';
			win1dpcnt=3;
			TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
			Type.time=0;
		}
		else if(Type.multispot==0 && para.pausetimef==1 && para.spottimef==0)
		{
			if(cyclestrt==0)
			{
				para.pausetime=updatedata(para.pausetime,min.pausetime,max.pausetime,encres);
			}
			win2dpcnt=float_to_ascii_str(&win2[0],para.pausetime);
			if(win2dpcnt==1)
			{
				win2[2]='/';		//for disply empty display
			}
			win1[0]='P';
			win1[1]='T';
			win1[2]='M';
			win1dpcnt=3;
			TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
			Type.time=0;
		}
 }
//**********
void updatedatacc(unsigned char encres,unsigned char encres1)
{
	if(weldingstart==0 && setupmode==0)
	{
		float fccslope=0.0;
		unsigned int foffset=0;
		if(errflag2=='N' || (errflag2=='U' && encres1=='+') || (errflag2=='O' && encres1=='-'))// && encres1=='+') || (errflag2=='U' && encres1=='-'))
		para.weldcurrent=updatedata(para.weldcurrent,min.weldcurrent,max.weldcurrent,encres1);
		fccslope=curmulti/200.0;
		foffset=fccslope*ccoffset*2.0;
		setcurrent=((para.weldcurrent*fccslope) - foffset);//87.0);// (ccoffset * fccslope));//87.0);//ccslope/200.0)- 87.0);//6.67 min. weldcurrent 18, max weld currnt=138
		if(setcurrent >=maxmmacurrent)//399.0)
		{
			errflag2='O';
		}
		else if((Type.mma==0 && setcurrent <=50.0) || (Type.tig==0 && setcurrent <=10.0))
		{
			errflag2='U';
		}
		else
		{
			errflag2='N';
		}
		win1dpcnt=float_to_ascii_str(&win1[0],setcurrent);//para.weldcurrent);
		sendcur=setcurrent;				
		sendvtg=fbvtg*10.0;
		if(win1dpcnt==1)
		{
			win1[2]='/';		//for disply empty display
		}
		if(Type.mma==0 && Type.tig==1)
		{
			para.weldarcforce=updatedata(para.weldarcforce,min.weldarcforce,max.weldarcforce,encres);
			win2dpcnt=float_to_ascii_str(&win2[0],para.weldarcforce);
			if(win2dpcnt==1)
			{
				win2[2]='/';		//for disply empty display
			}
		}
		else if(Type.mma==1 && Type.tig==0)
		{
			para.weldarcforce=0;
			win2dpcnt=float_to_ascii_str(&win2[0],para.weldarcforce);
			if(win2dpcnt==1)
			{
				win2[2]='/';		//for disply empty display
			}
		}

		TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XDF);
		Type.amp=0;
		
		 para.pwmtime1=(para.weldcurrent/2.0);//+((para.weldcurrent/2.0)*0.3);//100;//full ocv available para.weldcurrent;// * 1.0;	//1 is for current multiplier. during display of setting current.
		if(transon==1)//enable only when data received and encoder varies
		{
			transon=0;
			count_1ms=0;
			count_10ms=0;
			count_100ms=0;
			sendtoremotef=0;
			transtoremote(para.pwmtime1,sendvtg,para.weldcurrent,sendcur,model,errflag1,errflag2);
			IEC0bits.U1RXIE=1; //Uart reception interrupt enable	38400 baud rate
		}
	}
	else if(weldingstart==1 && setupmode==0)
	{
		unsigned int mahesh1=0,currentref=0;
		float fccslope=0.0;
		unsigned int foffset=0;
		para.weldcurrent=updatedata(para.weldcurrent,min.weldcurrent,max.weldcurrent,encres1);
		currentref=para.weldcurrent/2.0;//offset of pwm must be minus
		win1dpcnt=float_to_ascii_str(&win1[0],fbcurr);
		win2dpcnt=float_to_ascii_str(&win2[0],fbvtg);
		sendcur=fbcurr;				
		sendvtg=fbvtg*10;
		TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XDF);
		Type.amp=0;
		Type.voltage=0;
		//********************************************************
		fccslope=curmulti/200.0;
		foffset=fccslope*ccoffset*2.0;
		setcurrent=((para.weldcurrent*fccslope) - foffset);//87.0);// (ccoffset * fccslope));//87.0);//ccslope/200.0)- 87.0);//6.67 min. weldcurrent 18, max weld currnt=138
		if(setcurrent >=maxmmacurrent)//399.0)
		{
			errflag2='O';
		}
		else if((Type.mma==0 && setcurrent <=50.0) || (Type.tig==0 && setcurrent <=10.0))
		{
			errflag2='U';
		}
		else
		{
			errflag2='N';
		}
		//********************************************************
		if(fbvtg <=33.0 && Type.arcforce==0 && setcurrent <=200 && Type.mma==0 && Type.tig==1)
		{
			mahesh1= currentref + ((para.weldarcforce/100.0)*((33.0 - fbvtg)/33.0)*(currentref-ccoffset));// prev arcforce voltage==30v now 33v
		}
		else
		{
			mahesh1=currentref;//para.weldcurrent;
		}
		if(transon==1)//enable only when data received and encoder varies
		{
			transon=0;
			count_1ms=0;
			count_10ms=0;
			count_100ms=0;
			sendtoremotef=0;
			transtoremote(para.pwmtime1,sendvtg,para.weldcurrent,sendcur,model,errflag1,errflag2);
			IEC0bits.U1RXIE=1; //Uart reception interrupt enable	38400 baud rate
		}
		para.pwmtime1=mahesh1;
	} 	
	else if(setupmode==1)
	{
		if(slopept1==1 && slopept2==0)// && Type.weld==0)
		{
			pwmtime1=updatedata(pwmtime1,0,1000,encres1);
			win2dpcnt=float_to_ascii_str(&win2[0],pwmtime1); //fbvtg display fbvoltage
			win1[0]='C';
			win1[1]='U';
			win1[2]='1';
			win1dpcnt=3;
			if(pwmtime1 != prevpwmtime1)
			{
				para.pwmtime1=pwmtime1;
			}
			prevpwmtime1=pwmtime1;
			slope1=pwmtime1;		
		}
		else if(slopept1==0 && slopept2==1)// && Type.weld==0)
		{
			pwmtime1=updatedata(pwmtime1,0,1000,encres1);
			win2dpcnt=float_to_ascii_str(&win2[0],pwmtime1); //fbvtg
			win1[0]='C';
			win1[1]='U';
			win1[2]='2';
			win1dpcnt=3;
			if(pwmtime1 != prevpwmtime1)
			{
				para.pwmtime1=pwmtime1;
			}
			prevpwmtime1=pwmtime1;
			slope2=pwmtime1;	
		}		
	}
}
		
void keyaction(unsigned char key)
{
	if((key=='A' || key =='E' || key== 'I' || key=='P') && setmemloc==0 && setrecall==0 )//&& para.passprotect==0)
		{
				gasocvinch=1;
				if(key =='A')
				{
					Type.gascheck=0;
					GASONLAT=1;	
				}
				else if(key=='E')
				{
					Type.ocvcheck=0;
					ARCONLAT=1;
					genref(0);//para.pwmtime1);
				}
				else if(key=='I' || key=='P')
				{
					Type.inching=0;
					motorpwm=0;

					inrushf=0;
					inrushcounter=0;
					movldcounter=0;
					strtmtrovldcntrf=1;
					Motorerrf=0;
				}
				while(keyrelease()!=1)
				{
					if(Type.ocvcheck==0 && Type.gascheck==1 && Type.inching==1 )
					{
						{
							updatedisp=0;
							win2dpcnt=float_to_ascii_str(&win2[0],(dispfbvtg)); //+1.3
							win1[0]='V';
							win1[1]='T';
							win1[2]='G';
							win1dpcnt=3;
							if(win2dpcnt==1)
							win2[2]='/';					//for display empty display
						}
						TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
						Type.voltage=0;
						for(i=0;i<200;i++)
						delay();
					}
					else if(Type.ocvcheck==1 && Type.gascheck==0 && Type.inching==1)
					{
						//win2dpcnt=float_to_ascii_str(&win2[0],fbvtg);
						win1[0]='G';
						win1[1]='A';
						win1[2]='S';
						win1dpcnt=3;
						win2[0]='O';
						win2[1]='N';
						win2[2]='/';
						win2dpcnt=3;
						if(win2dpcnt==1)
						win2[2]='/';					//for display empty display
						TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
						for(i=0;i<200;i++)
						delay();
					}
					else if(Type.ocvcheck==1 && Type.gascheck==1 && Type.inching==0)
					{
						if(Motorerrf==0)
						{
							win1[0]='I';
							win1[1]='N';
							win1[2]='C';
							win1dpcnt=3;
							win2dpcnt=float_to_ascii_str(&win2[0],(motorpwm/3.0));//8fwirespeed);
							if(win1dpcnt==1)
							win1[2]='/';					//for display empty display
							;
							if(win2dpcnt==1)
							win2[2]='/';					//for display empty display
							;
							TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
							Type.speed=0;
							//drive_motor(para.pwmtime);
							inch_motor(motorpwm);	
							for(i=0;i<500;i++)//200
							{
								delay();
							}
							motorpwm=motorpwm + 3.0;
							if(motorpwm >=30) //10 m/min
							motorpwm=30;	
						}
						
						else
						{
							inch_motor(0);
							win1[0]='E';
							win1[1]='R';
							win1[2]='R';
							win1dpcnt=3;
							win2[0]='0';
							win2[1]='0';
							win2[2]='5';
							win2dpcnt=3;
						}
					}
				}//end of while
				gasocvinch=0;
				GASONLAT=0;
				ARCONLAT=0;

				genref(0);
				inrushf=0;
				inrushcounter=0;
				movldcounter=0;
				strtmtrovldcntrf=0;
				Motorerrf=0;
				///******CONTACTORLAT=0;
				inch_motor(0);
				Type.gascheck=1;
				Type.ocvcheck=1;
				Type.inching=1;
				key=0;
		}//end of if
		else
		{
				switch(multiplekey2)				//reset option
				{
					case 1: 
						if(key=='H') 
						{	
							multiplekey2=2;
							count_1sec=0;
						}
						break;
					case 2:
						if(key=='H')
						{
							if(count_1sec==10)
							{
								count_1sec=0;
								multiplekey2=1;
								key='R';
								//trans(key);
							}	
							multiplekey2=2;
						}
						else
						{
							multiplekey2=1;
						}	
						break;
				default:
						multiplekey2=1;
						break;	
				}//end of switch2
//**********************************************************************************************
			if(prevkey != key)
			{
			 
					IEC0bits.T1IE=0;	//Enable Timer1 interrupts
					///IEC0bits.T2IE=0;	//enable timer2 interrupt flag
					IEC0bits.ADIE=0;	//enable A to D conversion interrupt 
					IEC0bits.U1RXIE=0; 	//Uart reception interrupt enable
					IEC2bits.INT3IE=0;	//Enable interrupt
					for(i=0;i<200;i++);
					
					if((setpasswordf==0 || key=='D')  && (mesgdispf==0 || key=='O'))
					key_application(key);
					
					IEC0bits.T1IE=1;	//Enable Timer1 interrupts
					//IEC0bits.T2IE=1;	//enable timer2 interrupt flag
					IEC0bits.ADIE=1;	//enable A to D conversion interrupt 
					IEC0bits.U1RXIE=1; 	//Uart reception interrupt enable
					IEC2bits.INT3IE=1;	//Enable interrupt
					
					if(key =='J' || key =='F' || key=='B' || key=='N')  			//for calculate autopwm, if key is changed but voltage is same
					{
						keychange=1;
						keychange1=1;				//for display auto current when key is changed
					}
					if(key != 'Z' && key !='X')
					{
						para.ledgp1=TypeU.LEDGROUP[0];		//storing data into array for storing in eeprom
						para.ledgp2=TypeU.LEDGROUP[1];
						para.ledgp3=TypeU.LEDGROUP[2];
						para.ledgp4=TypeU.LEDGROUP[3];
						para.ledgp5=TypeU.LEDGROUP[4];	
						IEC2bits.INT3IE=1;					//Enable interrupt
					}
			}	
			prevkey=key;
			key=0;
		}
}//keyscsan

void torchaction()
{
		dummytorch=torch;
		if(cyclestrt==0)
		{
			oper=pre;
			IEC2bits.INT3IE=0;				//DISABLE INTERRUPT
		}
		 if(Type.twot==0)
		{
			switch(oper)
			{
				case pre:
				{
					
					if(cyclestrt==0)
					{
						strttmr=1;
						timerval=0;
						cntsecond=0;
						GASONLAT=1;
						TypeU.LEDGROUP[1]=0xFF;
						Type.preflow=0;
						cyclestrt=1;
						oper=pre;
					}
					if(cntsecond ==(para.preflow.time*10))
					{
						TypeU.LEDGROUP[1]=0xFF;
						Type.weld=0;
						strttmr=0;
						cntsecond=0;
						timerval=0;
						ARCONLAT=1;
						genref(para.pwmtime1);								//generate reference
						softstart_motor(para.pwmtime);						//drive_motor(para.pwmtime);
					
						inrushf=0;
						inrushcounter=0;
						movldcounter=0;
						strtmtrovldcntrf=1;
						Motorerrf=0;

						inchcounter=0;
						strtinchcntr=1; 										//if inching is started but welding is not started, then stop inching
						autoinch=0;
						
						oper=weld;
					}
					if(dummytorch==0)
					{
							oper=exit;
					}
					break;
				}		
				
				case weld:
				{
					oper=weld;
					if(autoinch==0 && Motorerrf==0)
					{
						ARCONLAT=1;
						genref(para.pwmtime1);								//generate reference
						drive_motor(para.pwmtime);
					
						if(dummytorch==0)
						{
							TypeU.LEDGROUP[1]=0xFF;
							Type.burnback=0;
							para.burnbackf=1;
							para.postflowf=0;
							strttmr=1;
							cntsecond=0;
							timerval=0;
							drive_motor(0);									//Stop wire feeder and  start burn back function
							ARCONLAT=1;
							genref((para.pwmtime1*0.75));					//FTT FUNCTION.
							oper=burn;
						}
						else if(inchcounter >=400 || therrf==1 || Pressure_ERRf==1 || Errorf==1 || Motorerrf==1) 
						{
							TypeU.LEDGROUP[1]=0xFF;
							Type.weld=0;
							para.burnbackf=0;
							para.postflowf=0;
							strttmr=0;
							cntsecond=0;
							timerval=0;
							drive_motor(0);						//stop wire feeder and  start burn back function
							GASONLAT=0;
							ARCONLAT=0;
							genref(0);							//generate reference
							oper=weld;
							inchcounter=0;
							strtinchcntr=0; 						//if inching is started but welding is not started, then stop inching
							if(Motorerrf==1)
							{
								autoinch=0;
								Motorerrf=1;
							}
							else
							{
								autoinch=1;
								Motorerrf=0;
							}
						}
					}				
					else
						{
							if(dummytorch==1 && torchval==0)
							{
								torchval=1;
							}
							else if(torchval==1 && dummytorch==0)
							{
								oper=exit;
								autoinch=0;
								Motorerrf=0;
							}
							else
							{
								oper=weld;
							}
						}

				break;
				}
				case burn:
				{
					if(para.burnback.time==cntsecond)	//already burnbacktime is stored in integer so not multiply by 10
					{
						TypeU.LEDGROUP[1]=0xFF;
						Type.postflow=0;
						para.burnbackf=0;
						para.postflowf=1;
						strttmr=1;
						timerval=0;
						cntsecond=0;
						///******CONTACTORLAT=0;
						ARCONLAT=0;
						genref(0);								//generate reference
						//stop burn back fun anf start post flow gas
						postflowstrtf=1;
						oper=post;
					}
					if(dummytorch==1)
					{
							oper=exit;
					}
				    	break;
				}
				case post:
				{
					if(cntsecond ==(para.postflow.time*10))
					{
						TypeU.LEDGROUP[1]=0xFF;
						GASONLAT=0;
						Type.weld=0;
						para.burnbackf=0;
						para.postflowf=0;
						cntsecond=0;
						timerval=0;
						strttmr=0;
						oper=exit;
					}
					if(dummytorch==1)
					{
							oper=exit;
					}
			  		break;
				}
				case exit:
				{
					TypeU.LEDGROUP[1]=0xFF;
					GASONLAT=0;
					ARCONLAT=0;
					genref(0);								//generate reference
					Type.weld=0;
					torch=0;
					cntsecond=0;
					timerval=0;
					strttmr=0;
					cyclestrt=0;
					para.burnbackf=0;
					para.postflowf=0;
					IEC2bits.INT3IE=1;				//Enable INTERRUPT
					autooffset=para.pwmtime;
					setupautomode=0;			//coming out from setupmode
					coursevtgsetf=0;
					startstoref=0;
					coursevtgset=0;
					startvtg=0;
					inrushf=0;
					inrushcounter=0;
					movldcounter=0;
					strtmtrovldcntrf=0;
					Motorerrf=0;
					writemematstop();
					break;
				}
		}//end ig switch
		}//end of if else
		
		else if(Type.fourt==0)
		{
			switch(oper)
			{
				case pre:
				{
					if(cyclestrt==0)
					{
						strttmr=1;
						timerval=0;
						cntsecond=0;
						GASONLAT=1;
						TypeU.LEDGROUP[1]=0xFF;
						Type.preflow=0;
						cyclestrt=1;
						oper=pre;
					}
					else if(cntsecond ==(para.preflow.time*10))
					{
						TypeU.LEDGROUP[1]=0xFF;
						Type.weld=0;
						strttmr=0;
						cntsecond=0;
						timerval=0;
						ARCONLAT=1;
						genref(para.pwmtime1);
						inchcounter=0;
						autoinch=0;
						Motorerrf=0;
						oper=weld;
					}
				break;
				}		
				
				case weld:
				{
					oper=weld;
					if(autoinch==0 && Motorerrf==0)
					{
						if(dummytorch==0 && torchrelease==0)				//VOLTAGE ON, WIRESPEED START AFTER RELEASE TORCH
						{
							TypeU.LEDGROUP[1]=0xFF;
							Type.weld=0;
							torchrelease=1;
							oper=weld;
							softstart_motor(para.pwmtime);
	
							inrushf=0;
							inrushcounter=0;
							movldcounter=0;
							strtmtrovldcntrf=1;
							Motorerrf=0;
							
							inchcounter=0;
							strtinchcntr=1; 										//if inching is started but welding is not started, then stop inching
							autoinch=0;
							ARCONLAT=1;
							genref(para.pwmtime1);								//generate reference
						}
						else if(dummytorch==0 && torchrelease==1 && cratersetup==0)			//VOLTAGE ON, WIRESPEED ON
						{
							TypeU.LEDGROUP[1]=0xFF;
							Type.weld=0;
							torchrelease=1;
							oper=weld;
							ARCONLAT=1;
							{
								drive_motor(para.pwmtime);
								genref(para.pwmtime1);								//generate reference
							}
						}
						else if(dummytorch==1 && torchrelease==1 && cratersetup==0)// && Type.crateron==0)//TORCH PRESSED AGAIN CRATER FUNCTION
						{
							TypeU.LEDGROUP[1]=0xFF;
							Type.crater=0;
							oper=weld;
							ARCONLAT=1;
							if(Type.mig==0 && Type.fcaw==1)
							{
								genref(para.crater.volts/2.0);								//generate reference
								drive_motor((para.crater.wfs*0.101)*3.0);
							}
							else if(Type.mig==1 && Type.fcaw==0)
							{
								genref(para.fcaw.cratervolts/2.0);							//generate reference
								drive_motor((para.fcaw.craterwfs*0.101)*3.0);
							}
							cratersetup=1;
						}
						else if((dummytorch==0 && torchrelease==1 && cratersetup==1 && Type.crateron==0) ||(dummytorch==1 && torchrelease==1 && cratersetup==1 && Type.crateron==1))
						{
							TypeU.LEDGROUP[1]=0xFF;
							Type.burnback=0;
							para.burnbackf=1;
							para.postflowf=0;
							strttmr=1;
							cntsecond=0;
							timerval=0;
							ARCONLAT=1;
							genref((para.pwmtime1*0.75));				//FTT FUNCTION.
							drive_motor(0);
							oper=burn;
						}
					}
					else
					{
						if(dummytorch==0 && torchval==0)
						{
							torchval=1;
						}
						else if(dummytorch==1 && torchval==1)
						{
							oper=exit;
							autoinch=0;
							Motorerrf=0;
						}
						else
						{
							oper=weld;
						}
					}
					//*************************
					if((inchcounter >=400 && strtinchcntr==1) || Pressure_ERRf==1 || Errorf==1 || Motorerrf==1)
					{
							TypeU.LEDGROUP[1]=0xFF;
							Type.weld=0;
							para.burnbackf=0;
							para.postflowf=0;
							strttmr=0;
							cntsecond=0;
							timerval=0;
							drive_motor(0);
							GASONLAT=0;
							ARCONLAT=0;
							genref(0);
							oper=weld;
							inchcounter=0;
							strtinchcntr=0; 				//if inching is started but welding is not started, then stop inching
							if(Motorerrf==1)
							{
								autoinch=0;
								Motorerrf=1;
							}
							else 
							{
								autoinch=1;
								Motorerrf=0;
							}
					}
				break;
				}
				case burn:
				{
														//already burnbacktime is stored in integer so not multiply by 10
					if(para.burnback.time==cntsecond)
					{
						TypeU.LEDGROUP[1]=0xFF;
						Type.postflow=0;
						para.burnbackf=0;
						para.postflowf=1;
						strttmr=1;
						timerval=0;
						cntsecond=0;
						ARCONLAT=0;
						genref(0);
						///******CONTACTORLAT=0;								//stop burn back fun anf start post flow gas
						oper=post;
					}
					if(dummytorch==0 && torchval==0)			//&& Type.crater==1))// || (dummytorch==0 && torchval==0 && Type.crater==0))
					{
						torchval=1;
					}
					else if(dummytorch==1 && torchval==1)
					{
						oper=exit;
					}
					break;
				}
				case post:
				{
					if(cntsecond ==(para.postflow.time*10))
					{
						TypeU.LEDGROUP[1]=0xFF;
						GASONLAT=0;
						Type.weld=0;
						para.burnbackf=0;
						para.postflowf=0;
						cntsecond=0;
						timerval=0;
						strttmr=0;
						oper=exit;
					}
					if(dummytorch==0 && torchval==0 )//&& Type.crater==1)// || (dummytorch==1 && torchval==0 && Type.crater==0))
					{
						torchval=1;
					}
					else if(dummytorch==1 && torchval==1)
					{
						oper=exit;
					}
		  		break;
				}
				case exit:
				{
					if(dummytorch==0)// && torchenable==1)
					{
						TypeU.LEDGROUP[1]=0xFF;
						GASONLAT=0;
						ARCONLAT=0;
						genref(0);
						///******CONTACTORLAT=0;
						drive_motor(0);
						Type.weld=0;
						cntsecond=0;
						timerval=0;
						strttmr=0;
						cyclestrt=0;
						torchenable=0;
						torchrelease=0;
						para.burnbackf=0;
						para.postflowf=0;
						autooffset=para.pwmtime;		//restoring pwmtime in offset reg
						setupautomode=0;				//coming out from setupmode
						IEC2bits.INT3IE=1;				//ENABLE INTERRUPT
						torchval=0;
						fastexit=0;
						coursevtgsetf=0;
						startstoref=0;
						coursevtgset=0;
						startvtg=0;
						cratersetup=0;
						
						inrushf=0;
						inrushcounter=0;
						movldcounter=0;
						strtmtrovldcntrf=0;
						Motorerrf=0;

						writemematstop();
					}
					else
					{
						oper=exit;
					}
					break;
				}
		}//end ig switch
		}
		else if(Type.multispot==0)
		{
			switch(oper)
			{
				case pre:
				{
						GASONLAT=1;
						cyclestrt=1;
						TypeU.LEDGROUP[1]=0xFF;
						Type.weld=0;
						strttmr=0;
						cntsecond=0;
						timerval=0;
						ARCONLAT=1;
						genref(para.pwmtime1);
						///******CONTACTORLAT=1;
						softstart_motor(para.pwmtime);

						inrushf=0;
						inrushcounter=0;
						movldcounter=0;
						strtmtrovldcntrf=1;
						Motorerrf=0;

						inchcounter=0;
						strtinchcntr=1; //if inching is started but welding is not started, then stop inching
						autoinch=0;
						strttmr=1;							//start timer for counting spot time.
						timerval=0;
						cntsecond=0;
						oper=weld;
						break;
				}		
				
				case weld:
				{
					oper=weld;
					if(autoinch==0 && Motorerrf==0)
					{
						ARCONLAT=1;
						genref(para.pwmtime1);								//generate reference
						drive_motor(para.pwmtime);
						if(cntsecond ==(para.spottime*10))
						{
							strttmr=0;
							cntsecond=0;
							timerval=0;
	
							TypeU.LEDGROUP[1]=0xFF;
							Type.burnback=0;
							para.burnbackf=1;
							para.postflowf=0;
							strttmr=1;
							cntsecond=0;
							timerval=0;
							//stop wire feeder and  start burn back function
							drive_motor(0);
							oper=burn;
							//trans('D');
						}
						else if((inchcounter >=400) || therrf==1 || Pressure_ERRf==1 || Errorf==1 || Motorerrf==1)
						{
							TypeU.LEDGROUP[1]=0xFF;
							Type.weld=0;
							para.burnbackf=0;
							para.postflowf=0;
							strttmr=0;
							cntsecond=0;
							timerval=0;
							//stop wire feeder and  start burn back function
							drive_motor(0);
							GASONLAT=0;
							ARCONLAT=0;
							genref(0);
							///******CONTACTORLAT=0;
							oper=weld;
							inchcounter=0;
							strtinchcntr=0; //if inching is started but welding is not started, then stop inching
							if(Motorerrf==1)
							{
								autoinch=0;
								Motorerrf=1;
							}
							else 
							{
								autoinch=1;
								Motorerrf=0;
							}
						}
						else
						{
							if(dummytorch==0 && torchval==0)
							{
								torchval=1;
							}
							else if(torchval==1 && dummytorch==1)//&& torchval==0)
							{
								oper=exit;
								autoinch=0;
								Motorerrf=0;	
							}
						}
					}

					else
					{
						if(dummytorch==0 && torchval==0)
						{
							torchval=1;
						}
						else if(torchval==1 && dummytorch==1)//&& torchval==0)
						{
							oper=exit;
							autoinch=0;
							Motorerrf=0;
						}
					}
				break;
				}
				case burn:
				{
					if(para.burnback.time==cntsecond)	//already burnbacktime is stored in integer so not multiply by 10
					{
						TypeU.LEDGROUP[1]=0xFF;
						Type.postflow=0;
						para.burnbackf=0;
						para.postflowf=1;
						strttmr=1;
						timerval=0;
						cntsecond=0;
						ARCONLAT=0;
						genref(0);
						postflowstrtf=1;
						oper=post;
					}
					if(dummytorch==0 && torchval==0)
					{
						torchval=1;
					}
					else if(torchval==1 && dummytorch==1)//&& torchval==0)
					{
						oper=exit;
					}
				    break;
				}
				case post:
				{
					if(cntsecond ==(para.postflow.time*10))
					{
						TypeU.LEDGROUP[1]=0xFF;
						GASONLAT=0;
						Type.weld=0;
						para.burnbackf=0;
						para.postflowf=0;
						//torch=0;
						cntsecond=0;
						timerval=0;
						strttmr=1;
						oper=pause;
						chkpausetime=1;
						//trans('P');
					}
					if(dummytorch==0 && torchval==0)
					{
						torchval=1;
					}
					else if(torchval==1 && dummytorch==1)//&& torchval==0)
					{
							oper=exit;
							//fastexit=1;
					}
			  		break;
				}
				
				case pause:
						{
							if(cntsecond ==(para.pausetime*10))
							{
								TypeU.LEDGROUP[1]=0xFF;
								GASONLAT=0;
								ARCONLAT=0;
								genref(0);
								///******CONTACTORLAT=0;
								Type.weld=0;
								cntsecond=0;
								timerval=0;
								strttmr=0;
								//cyclestrt=0;
								torchenable=0;
								para.burnbackf=0;
								para.postflowf=0;
								autooffset=para.pwmtime;		//restoring pwmtime in offset reg
								setupautomode=0;				//coming out from setupmode
								IEC2bits.INT3IE=1;				//ENABLE INTERRUPT
								torchval=0;
								fastexit=0;
								oper=pre;
								chkpausetime=0;
								//trans('M');
							}
							if(dummytorch==0 && torchrelease==0)
							{
								TypeU.LEDGROUP[1]=0xFF;
								Type.weld=0;
								torchrelease=1;
								oper=pause;
								//drive_motor(para.pwmtime);
								//trans('R');
							}
							else if(dummytorch==1 && torchrelease==1)
							{
								TypeU.LEDGROUP[1]=0xFF;
								Type.burnback=0;
								para.burnbackf=1;
								para.postflowf=0;
								strttmr=0;
								cntsecond=0;
								timerval=0;
								chkpausetime=0;
								//stop wire feeder and  start burn back function
								//drive_motor(0);
								oper=exit;
								//trans('D');
							}
						break;	
					}

				case exit:
				{
					
					if(dummytorch==1 && torchenable==0) 
					{
						TypeU.LEDGROUP[1]=0xFF;
						GASONLAT=0;
						ARCONLAT=0;
						genref(0);
						///******CONTACTORLAT=0;
						Type.weld=0;
						cntsecond=0;
						timerval=0;
						strttmr=0;
						drive_motor(0);
						//cyclestrt=0;			//do not clear till torch release after second push
						torchrelease=0;
						torchenable=1;
						//trans('X');
					}
					else if(dummytorch==0 && torchenable==1)
					{
						TypeU.LEDGROUP[1]=0xFF;
						GASONLAT=0;
						ARCONLAT=0;
						genref(0);
						///******CONTACTORLAT=0;
						drive_motor(0);
						Type.weld=0;
						cntsecond=0;
						timerval=0;
						strttmr=0;
						cyclestrt=0;
						torchenable=0;
						para.burnbackf=0;
						para.postflowf=0;
						autooffset=para.pwmtime;		//restoring pwmtime in offset reg
						setupautomode=0;				//coming out from setupmode
						IEC2bits.INT3IE=1;				//ENABLE INTERRUPT
						torchval=0;
						fastexit=0;
						coursevtgsetf=0;
						startstoref=0;
						coursevtgset=0;
						startvtg=0;

						inrushf=0;
						inrushcounter=0;
						movldcounter=0;
						strtmtrovldcntrf=0;
						Motorerrf=0;

						writemematstop();
						//trans('E');
						//trans('N');
						//trans('D');
					}
					else
					{
						oper=exit;
						//trans('T');
					}
					
					break;
				}
		}//end ig switch

	//*******************
		}
		else if(Type.spot==0)
		{
			switch(oper)
			{
				case pre:
				{
					
						GASONLAT=1;
						cyclestrt=1;
						TypeU.LEDGROUP[1]=0xFF;
						Type.weld=0;
						strttmr=0;
						cntsecond=0;
						timerval=0;
						ARCONLAT=1;
						genref(para.pwmtime1);
						///******CONTACTORLAT=1;
						softstart_motor(para.pwmtime);

						inrushf=0;
						inrushcounter=0;
						movldcounter=0;
						strtmtrovldcntrf=1;
						Motorerrf=0;

						inchcounter=0;
						strtinchcntr=1; 						//if inching is started but welding is not started, then stop inching
						autoinch=0;
						strttmr=1;							//start timer for counting spot time.
						timerval=0;
						cntsecond=0;
						oper=weld;
						break;
				}		
				
				case weld:
				{
					oper=weld;
					if(autoinch==0 && Motorerrf==0)
					{
						ARCONLAT=1;
						genref(para.pwmtime1);								//generate reference
						drive_motor(para.pwmtime);
						if(cntsecond ==(para.spottime*10))
						{
							strttmr=0;
							cntsecond=0;
							timerval=0;
							TypeU.LEDGROUP[1]=0xFF;
							Type.burnback=0;
							para.burnbackf=1;
							para.postflowf=0;
							strttmr=1;
							cntsecond=0;
							timerval=0;
							//stop wire feeder and  start burn back function
							drive_motor(0);
							oper=burn;
						//trans('D');
						}
						else if(inchcounter >=400 || therrf==1 || Pressure_ERRf==1 || Errorf==1 || Motorerrf==1)
						{
							TypeU.LEDGROUP[1]=0xFF;
							Type.weld=0;
							para.burnbackf=0;
							para.postflowf=0;
							strttmr=0;
							cntsecond=0;
							timerval=0;
							//stop wire feeder and  start burn back function
							drive_motor(0);
							GASONLAT=0;
							ARCONLAT=0;
							genref(0);
							///******CONTACTORLAT=0;
							oper=weld;
							inchcounter=0;
							strtinchcntr=0; //if inching is started but welding is not started, then stop inching
							if(Motorerrf==1)
							{
								autoinch=0;
 								Motorerrf=1;
							}
							else
							{
								autoinch=1;
 								Motorerrf=0;
							}
						}
						else if(dummytorch==0)
						{
							oper=exit;
							fastexit=1;
							autoinch=0;
 							Motorerrf=0;	
						}
					}
					else
					{
						if(dummytorch==0)
						{
							oper=exit;
							fastexit=1;
						}
					}
				break;
				}
				case burn:
				{
					if(para.burnback.time==cntsecond)	//already burnbacktime is stored in integer so not multiply by 10
					{
						TypeU.LEDGROUP[1]=0xFF;
						Type.postflow=0;
						para.burnbackf=0;
						para.postflowf=1;
						strttmr=1;
						timerval=0;
						cntsecond=0;
						ARCONLAT=0;
						genref(0);
						///******CONTACTORLAT=0;
						//stop burn back fun anf start post flow gas
						postflowstrtf=1;
						oper=post;
						//trans('B');
					}
						//oper=burn;
					if(dummytorch==0)//&& torchval==0)
					{
							oper=exit;
							fastexit=1;
					}
					break;
				}
				case post:
				{
					if(cntsecond ==(para.postflow.time*10))
					{
						TypeU.LEDGROUP[1]=0xFF;
						GASONLAT=0;
						Type.weld=0;
						para.burnbackf=0;
						para.postflowf=0;
						//torch=0;
						cntsecond=0;
						timerval=0;
						strttmr=0;
						oper=exit;
						//trans('P');
					}
					if(dummytorch==0)//&& torchval==0)
					{
							oper=exit;
							fastexit=1;
					}
					break;
				}
				case exit:
				{
					if(fastexit==1)
					{
						TypeU.LEDGROUP[1]=0xFF;
						GASONLAT=0;
						ARCONLAT=0;
						genref(0);
						///******CONTACTORLAT=0;
						drive_motor(0);
						Type.weld=0;
						cntsecond=0;
						timerval=0;
						strttmr=0;
						cyclestrt=0;
						torchenable=0;
						para.burnbackf=0;
						para.postflowf=0;
						autooffset=para.pwmtime;		//restoring pwmtime in offset reg
						setupautomode=0;				//coming out from setupmode
						IEC2bits.INT3IE=1;				//ENABLE INTERRUPT
						torchval=0;
						fastexit=0;
						coursevtgsetf=0;
						startstoref=0;
						coursevtgset=0;
						startvtg=0;
						autoinch=0;
 					
						inrushf=0;
						inrushcounter=0;
						movldcounter=0;
						strtmtrovldcntrf=0;
						Motorerrf=0;
						writemematstop();
					}
					else if(torchenable==0) 
					{
						TypeU.LEDGROUP[1]=0xFF;
						GASONLAT=0;
						ARCONLAT=0;
						genref(0);
						///******CONTACTORLAT=0;
						drive_motor(0);
						Type.weld=0;
						cntsecond=0;
						timerval=0;
						strttmr=0;
						//cyclestrt=0;			//do not clear till torch release after second push
						torchrelease=0;
						torchenable=1;
						//trans('X');
					}
					else if(dummytorch==0)
					{
						TypeU.LEDGROUP[1]=0xFF;
						GASONLAT=0;
						ARCONLAT=0;
						genref(0);
						///******CONTACTORLAT=0;
						drive_motor(0);
						Type.weld=0;
						cntsecond=0;
						timerval=0;
						strttmr=0;
						cyclestrt=0;
						torchenable=0;
						para.burnbackf=0;
						para.postflowf=0;
						autooffset=para.pwmtime;		//restoring pwmtime in offset reg
						setupautomode=0;				//coming out from setupmode
						IEC2bits.INT3IE=1;				//ENABLE INTERRUPT
						torchval=0;
						fastexit=0;
						coursevtgsetf=0;
						startstoref=0;
						coursevtgset=0;
						startvtg=0;
						autoinch=0;
 						Motorerrf=0;
						inrushf=0;
						inrushcounter=0;
						movldcounter=0;
						strtmtrovldcntrf=0;
						Motorerrf=0;
						writemematstop();	
					}
					else
					{
						oper=exit;
					}
					
					break;
				}
		}//end ig switch

		}
	}	
//***********************************************************************************************************************************************************
void transtoremote(unsigned int transdata1,unsigned int transdata2,unsigned int transdata3,unsigned int transdata4,unsigned char model1,unsigned char error11, unsigned char error12)
{
	unsigned char higher=0,lower=0;
	transchksum=0x00;
 	trans('$');
 	;
	lower=transdata1;
 	transdata1=transdata1 >>8;
 	higher=transdata1;
 	trans(lower);
	transchksum=transchksum+lower;
 	trans(higher);
 	transchksum=transchksum+higher;
 	;
	lower=transdata2;
 	transdata2=transdata2 >>8;
 	higher=transdata2;
 	trans(lower);
	transchksum=transchksum+lower;
 	trans(higher);
 	transchksum=transchksum+higher;
 	;
    lower=transdata3;
 	transdata3=transdata3 >>8;
 	higher=transdata3;
 	trans(lower);
	transchksum=transchksum+lower;
 	trans(higher);
 	transchksum=transchksum+higher;
 	;
    lower=transdata4;
 	transdata4=transdata4 >>8;
 	higher=transdata4;
 	trans(lower);
	transchksum=transchksum+lower;
 	trans(higher);
 	transchksum=transchksum+higher;
 	;
 	trans(model1);
	transchksum=transchksum+model1;
 	;
	trans(error11);
	transchksum=transchksum+error11;
 	trans(error12);
	transchksum=transchksum+error12;
	trans(transchksum);
 	transchksum=0;
	transon=0;
	receivef=0;
}

void read_model(void)
{
	if(SW1==0 && SW2==0)// && SW3==0)			//champ multi fcaw-400, 42vwf
	{
		delay();
		if(SW1==0 && SW2==0)// && SW3==0)
		mc_model='A';
		else
		mc_model='A';
	}
	else if(SW1==1 && SW2==1)//&& SW3==1)		//champ multi fcaw-400, 24vwf
	{	
		delay();
		if(SW1==1 && SW2==1)//&& SW3==1)
		mc_model='B';
		else
		mc_model='A';
	}
	else if(SW1==0 && SW2==1)// && SW3==0)			//champ multi fcaw-400, 42vwf
	{
		delay();
		if(SW1==0 && SW2==1)// && SW3==0)
		mc_model='C';
		else
		mc_model='A';
	}
	else if(SW1==1 && SW2==0)// && SW3==0)			//champ multi fcaw-400, 42vwf
	{
		delay();
		if(SW1==1 && SW2==0)// && SW3==0)
		mc_model='C';
		else
		mc_model='A';
	}
	





	/*
	else if(SW1==0 && SW2==1 && SW3==0)		//champ multi 400, 42vwf
	{	
		delay();
		if(SW1==0 && SW2==1 && SW3==0)
		mc_model='C';
		else
		mc_model='A';
	}	
	else if(SW1==0 && SW2==1 && SW3==1)		//champ multi 400, 24vwf
	{	
		delay();
		if(SW1==0 && SW2==1 && SW3==1)
		mc_model='D';
		else
		mc_model='A';
	}	
	else if(SW1==1 && SW2==0 && SW3==0)		//champ multi 250, 42vwf
	{	
		delay();
		if(SW1==1 && SW2==0 && SW3==0)
		mc_model='E';
		else
		mc_model='A';
	}	
	else if(SW1==1 && SW2==0 && SW3==1)		//champ multi 250, 24vwf
	{	
		delay();
		if(SW1==1 && SW2==0 && SW3==1)
		mc_model='F';
		else
		mc_model='A';
	}	
	else if(SW1==1 && SW2==1 && SW3==0)		//champ multi 600, 42vwf
	{	
		delay();
		if(SW1==1 && SW2==1 && SW3==0)
		mc_model='G';
		else
		mc_model='A';
	}
	else if(SW1==1 && SW2==1 && SW3==1)		//champ multi 600, 24vwf
	{	
		delay();
		if(SW1==1 && SW2==1 && SW3==1)
		mc_model='H';
		else
		mc_model='A';
	}*/	
}

