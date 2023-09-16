///***********************MODIFICATION DETAILS***************************************************************************
//***********************************************************************************************************************
//    Date    	REV. No   	DONE BY      		DESCRIPTION
// 01/01/2019 	REV-1.0		Akshay Nirgude		Added new function to store the max cnt for voltage.
//                                  			also did changes in KEYPAD.C
//												ARCLENGTH RECEIVED VRIABLE DISABLED IN ISR
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
//#include "incap.h" 

#include "DEFINE.C"

#include "STRUCTURE.C"
#include "VARIABLE.C"
#include "FUNCTION.C"
#include "LCDARRAY.C"
#include "SYNERGICDATA.C"
#include "PMIGSYNDATA.C"
#include "TESTEEPROM.C"
#include "ROOTSYNERGICDATA.C"

#include "FONT.C"
#include "FONT1.C"
#include "ADORLOGO.C"


//#include "NEWCONTROL.C"
//#include "PULSEMIGCONTROL.C"
#include "ISR2.C"
#include "LCD.C"
#include "DISPLAY.C"
#include "ENCODER.C"
#include "KEYPAD.C"

//#include "MMA.C"
//#include "TIG.C"
//#include "MIG.C"
//#include "PULSEMIG.C"

//#include "TORCHCYCLE.C"
#include "MODBUS.C"
#include "CRC.C"
#include "I2C.C"

//#include "PIDWITHFILTER.C"
_FOSC(CSW_FSCM_OFF & FRC_PLL16);  		  	//FAIL SAFE CLOCK SWITCHING IS OFF AND OPERATING FREQUENCY FCY=16MHZ
_FWDT(WDT_OFF);                 		  	//WATCH DOG TIMER 0FF
_FGS(CODE_PROT_ON);            		  	//CODE PROTECTION DISABLED
_FBORPOR(MCLR_EN & PBOR_ON & PWRT_64 & BORV_27); 	//rev1.2 brown out at 2.7volt

int main()
{
	unsigned int iData;
	unsigned int *BuffAddr;	
	PORTPIN_INIT();
	SHDNLAT=0;		//OCV OFF
//	GASRELAYLAT		=OFF;						//TO CONTROL THE GAS SOLENOID VALVE
//	HFRELAYLAT		=OFF;						//TO CONTROL THE HF RELAY
	CCCVCTRLLAT		=CCMODE;					//CCCV CONTROL  INPUT TO PWM CARD.
	ARCONLAT		=OFF;						//ARCON CONTROL SIGNAL INPUT TO PWM CARD
	OC2RS			=0;

	SYSTEM_INIT();
	i=786;
   
 
	TypeU.LEDGROUP[0]=0xFF;
	TypeU.LEDGROUP[1]=0xFF;
	TypeU.LEDGROUP[2]=0xFF;
	TypeU.LEDGROUP[3]=0xFF;
	TypeDP.DPGROUP[0]=0x00;
  //Typedp.digitdp1	=1;

/*	TRANS1('A');
	TRANS1('D');
	TRANS1('O');	
	TRANS1('R');	
	TRANS1(' ');
	TRANS1('W');
	TRANS1('E');	
	TRANS1('L');
	TRANS1('D');
	TRANS1('I');
	TRANS1('N');	
	TRANS1('G');
	*/
	

/*Read welding mode store at Zeroth location*/      
	memoryzone='X';
	eedata=EEPROM_Read(0*2);
	weldmode=eedata;

/*********************EEPRROM READ AT START=start************************/
	modechangef=1;
	read_current_status();
	check_eeprom_values();
						/****************Read Password Start*****************/
						set_password= EEPROM_Read(196);
						password_protection_enabled= EEPROM_Read(198);
						if(set_password==0xFFFF || set_password >999)
						{
						set_password=0;
						password_protection_enabled=0;
						EEPROM_Erase_Write((196),set_password);
						EEPROM_Erase_Write((198),password_protection_enabled);
						
							
						}
						if(password_protection_enabled!=0x0000 && password_protection_enabled!=0x0001)
						{
						set_password=0;
						password_protection_enabled=0;
						EEPROM_Erase_Write((196),set_password);
						EEPROM_Erase_Write((198),password_protection_enabled);
						}
						/****************Read Password End*****************/
	//disp_hex_dec_curr(786);
//	disp_hex_dec_volt(para.creepspeedrate);
/*********************EEPRROM READ AT START=start*************************///end

/*********************System Reset Function******************************/
	key=keypad_read();
	if(key=='B')		//B-S2	-DIAMETER/INCH
    {
	weldmode='G';  
	 
    dia=zeropteight;
    gas=co2;
    mat=ms;
    
	para.migmode.gdiameter=dia;
	para.migmode.ggas=gas;
	para.migmode.gmaterial=mat; 
    
    
    
	set_password=0;
	password_protection_enabled=0;
	EEPROM_Erase_Write((196),set_password);
	EEPROM_Erase_Write((198),password_protection_enabled);	
    
    
    para.migmode.preflow=mini.migmode.preflow;
    para.migmode.setcurrent=mini.migmode.setcurrent;
    para.migmode.setvoltage=mini.migmode.setvoltage;
    para.migmode.craterspeed=mini.migmode.craterspeed;
    para.migmode.cratervoltage=mini.migmode.cratervoltage;
    para.migmode.burnback=mini.migmode.burnback;
    para.migmode.setwspeed=mini.migmode.setwspeed;
    para.migmode.inductance=mini.migmode.inductance;
    para.creepspeedrate=mini.creepspeedrate;
    para.migmode.thickness=mini.migmode.thickness;
     
    para.pulseweldmode=0;  //single pulse mode
    
    write_current_status();
    
    for(i=1;i<=100;i++)
    write_mode_mem(i);
    
    diswin1[0]	='S';
	diswin1[1]	='Y';
	diswin1[2]	='S';
	diswin2[0]	='R';
	diswin2[1]	='S';
	diswin2[2]	='T';
    for(j=0;j<100;j++)
	for(i=0;i<20000;i++); //50000
    
    
    pdia=pzeropteight;
    pgas=parco2;
    pmat=pms;
    
	para.pmigmode.pdiameter=pdia;
	para.pmigmode.pgas=pgas;
	para.pmigmode.pmaterial=pmat; 
    
    
    para.pmigmode.preflow=mini.pmigmode.preflow;
    para.pmigmode.setcurrent=mini.pmigmode.setcurrent;
    para.pmigmode.setvoltage=mini.pmigmode.setvoltage;
    para.pmigmode.craterspeed=mini.pmigmode.craterspeed;
    para.pmigmode.cratervoltage=mini.pmigmode.cratervoltage;
    para.pmigmode.burnback=mini.pmigmode.burnback;
    para.pmigmode.setwspeed=mini.pmigmode.setwspeed;
    para.pmigmode.arclength=mini.pmigmode.arclength;
    para.pcreepspeedrate=mini.pcreepspeedrate;
    para.pmigmode.thickness=mini.pmigmode.thickness;
     
    para.pulseweldmode=0;  //single pulse mode
}
/*********************System Reset Function******************************/
	
	for(j=0;j<100;j++)
	for(i=0;i<20000;i++); //50000
/*********************EEPRROM READ AT START=end	*******************/

   if(weldmode=='M')
   {
      weldmode='M';
      TypeU.LEDGROUP[0]   	=0x00;
      Type.current      	=1;
      Type.voltage      	=1;
      TypeU.LEDGROUP[1]   	=0x00;
      Type.mma         		=1;
      TypeU.LEDGROUP[2]   	=0x00;
      TypeU.LEDGROUP[3]   	=0x00;
      
      power_on_in_mma=1; //to set the ocv on in mma mode if machine gets on in mma mode
   }
   else if(weldmode=='T')
   {
      weldmode='T';
      TypeU.LEDGROUP[0]   =0x00;
      Type.current      =1;
      Type.voltage      =1;
      TypeU.LEDGROUP[1]   =0x00;
      Type.tig         =1;
      TypeU.LEDGROUP[2]   =0x00;
      TypeU.LEDGROUP[3]   =0x00;
      
      power_on_in_tig=1;
   }
   else if(weldmode=='G')
   {
      weldmode='G';
      TypeU.LEDGROUP[0]   =0x00;
      //Type.wirespeed      =1;
      Type.current      =1;
      Type.voltage      =1;
      TypeU.LEDGROUP[1]   =0x00;
      Type.mig         =1;
      Type.twot         =1;
      TypeU.LEDGROUP[2]   =0x00;
      TypeU.LEDGROUP[3]   =0x00;
      
   }
   else if(weldmode=='P')
   {
      weldmode='P';
      TypeU.LEDGROUP[0]   =0x00;
      Type.wirespeed      =1;
      Type.voltage      =1;
      TypeU.LEDGROUP[1]   =0x00;
      Type.pulsemig      =1;
      Type.twot         =1;
      TypeU.LEDGROUP[2]   =0x00;
      TypeU.LEDGROUP[3]   =0x00;
   }
   else
   {
      weldmode='G';
      TypeU.LEDGROUP[0]   =0x00;
      Type.wirespeed      =1;
      Type.voltage      =1;
      TypeU.LEDGROUP[1]   =0x00;
      Type.mig         =1;
      Type.twot         =1;
      TypeU.LEDGROUP[2]   =0x00;
      TypeU.LEDGROUP[3]   =0x00;
   }

	diswin1[0]	='A';
	diswin1[1]	='D';
	diswin1[2]	='R';
	diswin2[0]	='W';
	diswin2[1]	='L';
	diswin2[2]	='D';
	for(j=0;j<100;j++)
	for(i=0;i<20000;i++); //50000

	
	pidParams2.Kp2	=40.0;//20.0;//5;
	pidParams2.Ki2	=5.0;//5.0;//10
	pidParams2.Kd2	=10.0;//0;//20 //5
	
	
	//pulse mig gain
	//pidParams.Kp=200.0;//140.0;//10.0;//0.5;//0.1;
    //pidParams.Ki=4.0;//1.0;//=1.0;//0.1;//0.08;//0.01;//0.02;
	//pidParams.Kd=5.0;//0.02;
				
	//MIG gain*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	pidParams1.Kp1	=120.0;//60.0;//50.0;//70.0;//100.0;//150;//100;//10; //25;//10; modified on 21.04.2017 promoda
	pidParams1.Ki1	=4.0;//5.0;//8.0;//10.0;//2;//10;//2;//10
	pidParams1.Kd1	=6.0;//30.0;//15.0;//0.0;//20;//0;//20 //5
	pidParams1.previous_error1=0;
	
	pidkp=pidParams1.Kp1;
	pidki=pidParams1.Ki1;
	pidkd=pidParams1.Kd1;	
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	//OC2RS=1000;
	//OC3RS=500;

	fooPID.abcCoefficients = &abcCoefficient[0];    //*Set up pointer to derived coefficients */
    fooPID.controlHistory  = &controlHistory[0];    //*Set up pointer to controller history samples */
    PIDInit(&fooPID);                               //*Clear the controler history and the controller output */
	kCoeffs[0] = Q15(0.4);                          // converting from fractional to signed integer
	kCoeffs[1] = Q15(0.3); 
	kCoeffs[2] = Q15(0.1); 
    PIDCoeffCalc(&kCoeffs[0], &fooPID);             //*Derive the a,b, & c coefficients from the Kp, Ki & Kd */


		{
			/*
			if(pmat==pms)
			lcdput(6,0,pmatms);
			else if(pmat==p71t1)
			lcdput(6,0,pmat71t1);
			else if(pmat==p180r)
			lcdput(6,0,pmat180r);
			else if(pmat==pss18)
			lcdput(6,0,pmatss18);
			else if(pmat==pss19)
			lcdput(6,0,pmatss19);
			else if(pmat==palu4043)
			lcdput(6,0,pmatalu4043);
			else if(pmat==palu5356)
			lcdput(6,0,pmatalu5356);
			else if(pmat==palu99)
			lcdput(6,0,pmatalu99);
			*/
//			lcdput(6,0,cMatTxt[pmat]);			
		}
		{
			/*
			if(pdia==pzeropteight)
			lcdput(6,48,diazeropteight);
			else if(pdia==poneptzero)
			lcdput(6,48,diaoneptzero);
			else if(pdia==ponepttwo)
			lcdput(6,48,diaonepttwo);
			else if(pdia==poneptsix)
			lcdput(6,48,diaoneptsix);
			*/
//			lcdput(6,48,cDiaTxt[pdia]);	
			
		}
		{
/*
			if(pgas==parco2)
			lcdput(7,90,gasarco2);
			else if(pgas==par)
			lcdput(7,90,gasar);	
			else if(pgas==paro2)
			lcdput(7,90,gasaro2);
*/
//		lcdput(6,88,cGasTxt[pgas]);		
//		lcdput(7,80,cGasPercent[pgas]);				
				
		}

		cE2pData[0] = '1';
		cE2pData[1] = '5';			
		
		diswin1[0]	='R';
		diswin1[1]	='E';
		diswin1[2]	='V';
		diswin2[0]	=cE2pData[0];
		diswin2[1]	=cE2pData[1];  //rev changed 1.5 19-08//rev 1.2 @sbm//1.3 changed on 19092019//rev 1.4 changed on 23092019
		diswin2[2]	='0';
		// R1.6 on 27072020  For WAPS
		Typedp.digitdp4=1;
		for(j=0;j<100;j++)
		for(i=0;i<20000;i++); //50000
		Typedp.digitdp4=0;	
//--------------------------
		cSerialPortTask = EEPROM_Read_for_SaveRecall((E2P_SERIALPORTTASK_ADDR));
		if((cSerialPortTask != 'U') && (cSerialPortTask != 'H'))
		{
			cSerialPortTask = 'U';
			EEPROM_Erase_Write((E2P_SERIALPORTTASK_ADDR),cSerialPortTask);				
		}
//-----------------------------------
	IFS0bits.ADIF 	  	=  0;		// clear A to D conversion complete flag 
	IEC0bits.ADIE 	  	=  1;		// enable A to D conversion interrupt 
	
	IFS1bits.T5IF=0;	//Clear the Timer5 interrupt status flag
	IEC1bits.T5IE=1;	//Enable Timer5 interrupts
	power_on_flag=1;
	
	
	//write_in_external_memory(4);

	
	
	clrlcd();

//	cMatarray[] = "ABCDEFG";

//---------------------------------
		//ctoggleflag = 1;
       clrlcd();
	   lcdput_bold(2,5,"New E2p Found");		
	   ctoggleflag = 1;
	   Clear_EEPROM_Prog_Num_Locations();
	
		/*if((cE2pData[0] != I2C_Read1(ADOR_WRL)) || (cE2pData[1] != I2C_Read1(ADOR_WRH)))
		{
			clrlcd();
			lcdput_bold(2,5,"New E2p Found");		
			ctoggleflag = 1;
			Clear_EEPROM_Prog_Num_Locations();									
		}
		else
		{
			lcdput_bold(2,5,"Program Found");			
		}	*/		
//---------------------------------	
while(1)
	{
		
		if((encod1!='$'))// && (setlcdweldparameter == 0) && (cPMainMenufg == 0))
		{
			iProgramLoadLoc = updatedata(iProgramLoadLoc,0,30,encod1);
			encod1='$';
		}
		
		
	/*	if(prevProgramLoadLoc != iProgramLoadLoc)
		{
			NumberUpdate(3,80,itempo1);
			NumberUpdate(5,80,iProgramLoadLoc);	
			//program_check_from_mem(iProgramLoadLoc);
			prevProgramLoadLoc = iProgramLoadLoc;
			//datafordebugonlcd(55,56);	//iTest1		
		}*/
				
		//datafordebugonlcd(55,56);
			
		cPMainMenufg = 1;
		
		if(ctoggleflag == 1)
		{
			
			clrlcd();
			lcdput_bold(2,5,ar421);
			diswin1[0]='P';
			diswin1[1]='E';
			diswin1[2]='R';	
			disp_hex_dec_volt(iPercentagecnt);	
			
						
			cWeldmode = 'P';
			for(iThickChk = 0;iThickChk < 4;iThickChk++)
			{
				for(iMatChk = 0;iMatChk < 12;iMatChk++)
				{
					for(iGasChk = 0;iGasChk < 4;iGasChk++)
					{
						if(newpmmmatgas[iThickChk][iMatChk][iGasChk] != 0)
						{
							iProgramNo = newpmmmatgas[iThickChk][iMatChk][iGasChk];
							update_mat_dia_gas();
							Write_in_EEPROM(iProgramNo,iProgramNo);//iPulseAddress);
							iPulseAddress++;						
							
							iProgramCnt++;
							iPercentagecnt = ((iProgramCnt*100)/TOTAL_PROGRAMS);
							disp_hex_dec_volt(iPercentagecnt);//iPercentagecnt);	
						}
					}				
				}
			}
		
		   ////////////////////////////////////////////NORMAL MIG/////////////////////////////////////////////////////////////////
			cWeldmode = 'G';
			for(iThickChk = 0;iThickChk < 4;iThickChk++)
			{
				for(iMatChk = 0;iMatChk < 5 ;iMatChk++)
				{
					for(iGasChk = 0;iGasChk < 4;iGasChk++)
					{
						iMigProgNo = mmmatgas[iThickChk][iMatChk][iGasChk];
						
						if(autocurrent[iMigProgNo][2] != 0)
						{
							
							update_mig_mat_dia_gas();
							Write_Mig_Data_in_EEPROM(iMigProgNo,iMigAddress);
							iMigAddress++;
							
							iProgramCnt++;
							iPercentagecnt = ((iProgramCnt*100)/TOTAL_PROGRAMS);
							disp_hex_dec_volt(iPercentagecnt);							
						}
					}
				}
			}
			/////////////////////////////////////////ROOT MIG////////////////////////////////////////////////////////////////////////////
			cWeldmode = 'G';
			for(iThickChk = 0;iThickChk < 4;iThickChk++)
			{
				for(iMatChk = 0;iMatChk < 5 ;iMatChk++)
				{
					for(iGasChk = 0;iGasChk < 4;iGasChk++)
					{
						iMigProgNo = rootmmmatgas[iThickChk][iMatChk][iGasChk];
						
						if(rootautocurrent[iMigProgNo][2] != 0)
						{
							update_mig_mat_dia_gas_root();
							Write_Mig_root_Data_in_EEPROM(iMigProgNo,iMigRootAddress);
							iMigRootAddress++;
							
							iProgramCnt++;
							iPercentagecnt = ((iProgramCnt*100)/TOTAL_PROGRAMS);
							disp_hex_dec_volt(iPercentagecnt);							
						}
					}
				}
			}
			
				
			if(ctoggleflag == 1)
			{
				Check_Updated_EEPROM();
				if(cMatchFoundfg == 1)
				{
//					I2C_Write(ADOR_WR,ADOR_DATA);
					EEPROM_Erase_Write_for_SaveRecall((17*2),3); 
					
					cE2p[0] = 0X03;
					cE2p[1] = 0X00;	
					
					//iTest = cE2p[1];
					//iTest = iTest << 8;
					//iTest |= cE2p[0];
														
					I2C_Write1(PROGRAM_ADDR,2);
					

					cE2p[0] = 0X03;
					cE2p[1] = 0X00;	
					cE2p[1] = 0X02;	
					I2C_Write1(MPROGRAM_ADDR,3);					
					//iTest = cE2p[1];
					//iTest = iTest << 8;
					//iTest |= cE2p[0];					
					
					cE2p[0] = cE2pData[0];										
					I2C_Write1(ADOR_WRL,1);
					cE2p[0] = cE2pData[1];										
					I2C_Write1(ADOR_WRH,1);
																
					lcdput(4,12,"successfully");
					lcdput(5,12,"Completed.");	
				}
				else
				{
					lcdput(5,0,"Downloading Failed");
				}		
			}
			ctoggleflag = 0;			
		}
		
		//program_check_from_mem(18);//iProgramLoadLoc);
		

		
		
		
		
		
		cTestfg = 1;	
		if(cParaUpdatefg == 0) // modbus serial communication
		{	
			UpdateParaIntoHMI();	
		}	
//-----test mode---------
		if((cTestfg == 1)&&(iSampleCnt > 500))
		{			
/*			
			BuffAddr = (unsigned int )(STARTADDRESS + 0);
			iTest1 = *BuffAddr;			
			BuffAddr = (unsigned int )(STARTADDRESS + 2);
			iTest2 = *BuffAddr;		
*/				
//			Load_Initial_Constant(para.pmigmode.setwspeed);
			//datafordebugonlcd(iTest1,iTest2);	//iTest1		
//			lcdput(5,0,cReceive_buffer);
			cTestfg = 0;
			iSampleCnt = 0;
		}	
		if(cFrameFoundfg == 1)
		{
//			datafordebugonlcd(cReceive_buffer[cByte_cntr-1],cReceive_buffer[cByte_cntr]);			
			Decode_querry();
//			cTestfg = 1;
			cFrameFoundfg = 0;
		}
		if((c200Msecfg == 1))
		{
			if(cCursorOnfg == 1)
			{
				CursorBlink(cCursorPosition,cLineNo);
			}		
			c200Msecfg = 0;
		}				
		if((cMacMenufg == 1))
		{
			if(encod1 != '$')
			{
				UpdateMacMenuScreenDataField(encod1);	
				encod1 = '$';			
			}			
		}
		if(0)//cMainScreenfg == 1)
		{
			MainScreenShow();
			cMainScreenfg = 0;
		}			
//-----------------------						
		//Toggle_pin();
		if(keyreadf==1)
		{
			key=keypad_read();
			
			keyreadf=0;
			
			if(key=='I')  //@-VOLTAGE ENCODER
			{
			  password_set_count++;
			  if(password_set_count>=PASSWORD_SET_COUNT_LIMIT) //20MSEC*250 ==5000SEC
			  {
			  password_set_count=PASSWORD_SET_COUNT_LIMIT;
			  passwod_set_flag=1;
			  }			
		    }
//-----------------------------------------------------------------
//here we are checking the two press
			if((weldmode != 'M')&& (weldcyclestrt == 0)) // block during weld on
			{
				 if((key == 'J') && (ChkForAnotherfg == 0)&&(ocvonfg == 0))
				 {
					ChkForAnotherfg = 1;
				 }
				 else if((ChkForAnotherfg == 1) && (keyrelease()))
				 {
					if(ocvonfg)
					{
						ocvonfg = 0;
						SHDNLAT	= OFF;
					}	
					else 
					{
						password_set_count=0;
						key_application('J'); 
					}										
					ChkForAnotherfg = 0;
				 }
				if((ChkForAnotherfg == 1)&&(key == 'A'))
				{
					SHDNLAT=ON;     //ocv on
					TypeDP.DPGROUP[0]=0x00;
					//Typedp.digitdp5		= 1;
				  
				  	diswin1[0]	='O';
		          	diswin1[1]	='C';
		          	diswin1[2]	='V';
	 			  	//disp_hex_dec_volt(VOLTAGE); //ocv 99.9 on RHS display
					ocvonfg =1;					
				} 
			} 
//-----------------------------------------------------------------		
			if(Prevkey!=key && passwod_set_flag==0 && (password_protection_enabled==0 || key=='H' || key=='K')&& (ChkForAnotherfg == 0)  )
			{
				password_set_count=0;
				Prevkey=key;
				key_application(key);				
			}
//			else if(Prevkey==key && key=='A')
//			{
//			    key_application(key);
//			}			
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
					if((PULSEamp>=para.migmode.setcurrent / 3)||(PULSEvtg <= (para.migmode.setvoltage + 20)) && (cSoftDonefg == 0)) //40) //74)  //3700adc count =500A so 7.40=1Amp  so74=10amp
					{
						cSoftStrfg = 1;
						if(cSoftStrCnt > ( 20 * 10))//save_location
						{
							psstatus.creepspeedon=0;
							cSoftStrCnt  = 0;	
							cSoftDonefg = 1;						
						}													
					}
					if((PULSEamp>=74))
					{
						MIGweldon_detectf=1;						
					}
						
					//else if(PULSEamp<35)//&& PULSEvtg>=2400) // 2400=60v //3000)//vtg >75V //16.11.2017
					//	MIGweldon_detectf=0;
					PULSEavgf=0;	
				}
			}	
//#############################################################################################################			
			if(weldmode=='P') 
			{
				if(PULSEavgf==1)
				{
					if(PULSEamp>=740) //40) //74)  //3700adc count =500A so 7.40=1Amp  so74=10amp
						Aweldon_detectf=1;
					else if(PULSEamp<35)//&& PULSEvtg>=2400) // 2400=60v //3000)//vtg >75V //16.11.2017
						Aweldon_detectf=0;
					PULSEavgf=0;	
				}
				if(startbmeasuref==1 &&	endbmeasuref==0)
				{
					//if(SCKVOLTAGE>=140 && SCKVOLTAGE<=400)
					if(SCKVOLTAGE>=440)
					SCKVOLTAGE=440;
					{					
						totalsumbvtg=totalsumbvtg+SCKVOLTAGE;
						totalsumbcnt++;
					}	
				}
				else if(startbmeasuref==0 && endbmeasuref==1)
				{
					BCNT=0;
					AVGBVTG=totalsumbvtg/totalsumbcnt;
					totalsumbvtg=0;
					totalsumbcnt=0;
					BVOLTAGE	=AVGBVTG;//(AVGBVTG>>2);//)/4.0;//37.0  scaling 4000=1000=100.0 volt
					//if(BVOLTAGE>=140 && BVOLTAGE<=440)  //to avoid ocv voltage to call PID
					{
						circular_arr[circular_cnt]=BVOLTAGE;
						circular_cnt++;
						if(circular_cnt>1)
						circular_cnt=0;
						
						CVOLTAGE=(circular_arr[0]+circular_arr[1])>>1;//+circular_arr[2]+circular_arr[3])>>2;
						startbmeasuref=0;
						endbmeasuref=0;
						//OC2RS=CVOLTAGE<<1;//*2949.0/1000.0;
					}
					//PFREQ_pid();
					//FRQ_sck_voltage_pid();
					//Base_vtg_pid1();
					
					//Base_vtg_pid();
					pulsetm		=PID_pulsetm;
					steptm		=PID_steptm;
					basetm		=PID_basetm;
					pulserisetm	=PID_pulserisetm;
					pulsefalltm	=PID_pulsefalltm;
					startpulsetm=PID_startpulsetm;
					uppdaccount	=PID_uppdaccount;
					pdaccount	=PID_pdaccount;
					sdaccount	=PID_sdaccount;
					bdaccount	=PID_bdaccount;
					newupstep	=PID_newupstep;
					newdownstep	=PID_newdownstep;
					//refbasetm=PID_refbasetm;
				}    
			 }
		}
//##############################################################################################################				
		if(DISPavgf==1)
		{
			CURRENT	=DISPamp*0.135;//	(adccur*5.0)/37.0;
			VOLTAGE	=DISPvtg>>2;	//	(adcvtg*10.0)/40.0;//37.0
			TRIPVTG	=DISPerr*0.270; //	(adctripvtg*10.0)/37.0;	
			DISPavgf=0;
			if(weldmode=='M')
			{
				if(CURRENT>=20) //20) 
				{
					weldonf=1;
				}
				else
				{
					weldonf=0;
					//INT_sckpidParams.INT_sckintegral_old=0;
					//INT_sckpidParams.INT_sckerror_old=0;
				}
			}
			
			if(weldmode=='T')
			{
				if(CURRENT>=15) //20) 
				{
					weldonf=1;
				}
				else
				{
					weldonf=0;
				}
			}
			
			
			
			
			
		/*	else if(weldmode=='G')
			{
				if(CURRENT>=20) 
				{
					psstatus.creepspeedon=0;
				}
			}*/
					
			if(VOLTAGE>=999)
			VOLTAGE=999;
			
			pstowfstr.Lo_actualcurrent=CURRENT;
			pstowfstr.Hi_actualcurrent=CURRENT >> 8;
			
			pstowfstr.Lo_actualvoltage=VOLTAGE;
			pstowfstr.Hi_actualvoltage=VOLTAGE >> 8;
		}

//******************************************Password Setting******************************************************************************
if((passwod_set_flag==1)&&(weldmode=='G'||weldmode=='P')&&(weldcyclestrt==0))
		{
		Prevkey=key;  //@SO THAT 	key_application() WILL NOT EXECUTED AFTER PRESSING KEY 'A'  'B' 'C'
			if(lcd_update_password==0)  //to avoid continous clear of LCD
			{
		    clrlcd();
		    }	   
			if(lcd_update_password==0) //to avoid continous clear of LCD
			{
				lcdput(0,0,"Enter Password:");  //@Enter Password   
			    lcdput(6,0,"To Ent Press MAT KEY ");  //@Press MAT/OCV KEY
			    lcdput(7,0,"To Esc Press GAS KEY");  //@Press GAS/FLW KEY			    
			    lcd_update_password=1;
		        temp_password=0;
	        } 
		
//			if(encod2!='$')
//			{
//				temp_password=updatedata(temp_password,0,9999,encod2);
//				encod2='$';
//			}
			if(encod2=='+')
			{
				if(iCntChk == 0)
					temp_password++;
				else 
				{
					temp_password = temp_password + iCntChk*3;//<<1;
//					iCntChk = 0;
				}	
				if(temp_password >= 9999)
				temp_password = 9999;	
				encod2='$';
				iCntChk = 50;
			}
			else if(encod2=='-')
			{
				if(iCntChk == 0)
					temp_password--;
				else 
					{
						temp_password = temp_password - iCntChk*3;//>>1;
//						iCntChk = 0;
					}	
				if(temp_password <= 0)
				temp_password = 0;
				encod2='$';
				iCntChk = 50;
			}	
			//passwordupdate(temp_password);
					
		 		if(key=='A')////@Press MAT/OCV KEY
			    {
					if((lcd_update_password == 1)&&(temp_password == set_password))
					{
					    password_protection_enabled=0;					    
						EEPROM_Erase_Write((198),password_protection_enabled);	
					    clrlcd();
				    	lcdput(3,0,"Valid Password");   					    
					    for(j=0;j<5000;j++)
					    delay_pmig();				    					
						temp_password=0;
						dispupdatef=1;
						lcd_update_password=5;  //FOR NEXT pASSWORD SCREEN						
					}
					else if((lcd_update_password == 1)&&(temp_password != set_password))
					{
					    password_protection_enabled=1;
						EEPROM_Erase_Write((198),password_protection_enabled);						    					    
					    clrlcd();
				    	lcdput(3,0,"Invalid Password");  //@Set Password   					    
					    for(j=0;j<5000;j++)
					    delay_pmig();				    					
						temp_password=0;
						dispupdatef=1;
						lcd_update_password=5;  //FOR NEXT pASSWORD SCREEN
					}						    			
				    dispupdatef=1;
			    }
			    else if(key=='C')  			//GAS/FLOW pressed ESCAPE
				{
					temp_password=0;
					dispupdatef=1;
					lcd_update_password=5;  //FOR NEXT pASSWORD SCREEN
					setPasswordfg = 0;
				}
				else if((key=='F'))
				{
			    	//passwod_set_flag=0;
			    	if((lcd_update_password == 1)&&(temp_password==MASTER_PASSWORD))
				    {
				    	lcdput(0,0,"Set Password:     ");  //@Set Password   
						lcdput(6,0,"To Set Press CURRENT");  //@Press MAT/OCV KEY
			    		lcdput(7,0,"To Esc Press GAS KEY");  //@Press GAS/FLW KEY
						lcd_update_password=2;     //FOR NEXT pASSWORD SCREEN	
						setPasswordfg = 1;		
						temp_password = 0;	    
				    }
				    else if((lcd_update_password == 2)&&(setPasswordfg == 0))
				    {					    
					    password_protection_enabled = 0;
					    clrlcd();
					    set_password = temp_password;
					    EEPROM_Erase_Write((196),set_password);
						EEPROM_Erase_Write((198),password_protection_enabled);	
				    	clrlcd();
				    	lcdput(3,0,"Set Password      ");  //@Set Password   
						lcdput(4,0,"Successfully...      ");  //@Press MAT/OCV KEY					    
					    for(j=0;j<5000;j++)
					    delay_pmig();				    					
						temp_password=0;
						dispupdatef=1;
						lcd_update_password=5;  //FOR NEXT pASSWORD SCREEN
					} 
				    else if((lcd_update_password == 1)&&(temp_password!=MASTER_PASSWORD)&&(setPasswordfg == 0))
				    {
						temp_password=0;    
				    	clrlcd();
				    	lcdput(4,0,"Invalid Password");  //@Press MAT/OCV KEY
				    	
				    	for(j=0;j<5000;j++)
				    	delay_pmig();
						dispupdatef=1;
						lcd_update_password=5;  //FOR NEXT pASSWORD SCREEN				    	
				    
				    }					
				}			
			if(lcd_update_password == 5)//passwod_set_flag==0)
			{
				if(weldmode=='G')
				{
				clrlcd();
				//lcdput_bold(0,0,ar31);
				//lcdput(2,0,ar32);
				//lcdput(4,0,ar33);
				LCD_mig_syn_data_write();
				//lcdput(7,0,ar40);
				lcd_disp_hex_dec(dispautocurrent);
				//currupdate();
				lcd_disp_hex_dec(program_number);
				//programupdate();
				lcd_disp_hex_dec(para.migmode.setvoltage);
				//voltupdate();
				}
				if(weldmode=='P')
				{
				clrlcd();
				lcdput_bold(0,0,ar41);
				lcdput(2,0,ar42);
				lcdput(4,0,ar43);
				LCD_pulsemig_syn_data_write();
				//lcdput(7,0,ar50);
				lcd_disp_hex_dec(dispautocurrent);
				//currupdate();
				lcd_disp_hex_dec(program_number);
				//programupdate();
				lcd_disp_hex_dec(para.pmigmode.setvoltage);
				//voltupdate();
				}
				passwod_set_flag=0;	
				lcd_update_password = 0;
				password_set_count = 0;			
			}
		}
//************************************************************************************************************************
        else if(weldmode=='M' && universal_error_flag==0)
		{
		    if(mma_tig_error_latch==1) //@return from Error in MMA or tig mode
			{
			prev_OCVON_command=0;
			OCVON_command=1;
			mma_tig_error_latch=0;
			}
			//MMAWELD();
		}
//*********************************************************************************************************************************************
		else if(weldmode=='T' && universal_error_flag==0)
		{
			if(mma_tig_error_latch==1)
			{
			prev_OCVON_command=0;
			OCVON_command=1;
			mma_tig_error_latch=0;
			}
			//TIGWELD();	
		}
//*********************************************************************************************************************************************
		else if(weldmode=='G')
		{
			max_lcd_cnt=6;
			psstatus.migpmigmode1	=0;
			
			if(universal_error_flag==0)
			//MIGWELD();
			
			pstowfstr.weldmode		='G';			//1
			pstowfstr.setthickness	=0;				//9
			if(transmit2f==1 && transmitonf==1 && trans2_onf==1)
			{
				pstowfstr.psstatusbyte=psstatusu.psstatusbyte[0];
				transmittowf();
				trans2_onf=0;
				transmit2f=0;
				transonf=1;				
				transonf=0;
			}
		}
//*********************************************************************************************************************************************
		else if(weldmode=='P')
		{
			max_lcd_cnt=10;
			psstatus.migpmigmode1		=1; //
			
			if(universal_error_flag==0)
			//PULSEWELD();
			
			pstowfstr.weldmode		 	='P';			//1
			pstowfstr.setthickness	 	=para.pmigmode.thickness;				//9
			if(transmit2f==1 && transmitonf==1 && trans2_onf==1)
			{
				//transmitonf=0;
				/*
				if(Testfg == 1)
				{
					Type.time = 0;
         			Type.arcforce = 0;
         			Testfg = 0;
    			}else
    			{
					Type.time = 1;
         			Type.arcforce = 1;	 
         			Testfg = 1;   			
	    		}	     			
				*/
				pstowfstr.psstatusbyte=psstatusu.psstatusbyte[0];
				transmittowf();
				trans2_onf=0;
				transmit2f=0;
				transonf=1;				
				transonf=0;
			}
		}//pulse mode
		
		Detect_error();
		
	}//while
}//main file

 inline void delay_pmig()
{
	unsigned int i;
	for(i=0;i<=1500;i++)
	ClrWdt();  //@rev1.2
}


void updatemccparameter(unsigned char encres3, unsigned char encres2)
{
	if(encres3!='$')
	{
		para.mmamode.setcurrent=updatedata(para.mmamode.setcurrent,mini.mmamode.setcurrent,maxi.mmamode.setcurrent,encres3);
	//	disp_hex_dec_curr(para.mmamode.setcurrent);
	}	
	if(encres2!='$')
	{
		para.mmamode.arcforce=updatedata(para.mmamode.arcforce,mini.mmamode.arcforce,maxi.mmamode.arcforce,encres2);
		//disp_hex_dec_volt(para.mmamode.arcforce);	
	}
}


 	

void updatetccparameter(unsigned char encres3, unsigned char encres2)
{
	if(encres3!='$')
	{
		para.tigmode.setcurrent=updatedata(para.tigmode.setcurrent,mini.tigmode.setcurrent,maxi.tigmode.setcurrent,encres3);
		//disp_hex_dec_curr(para.tigmode.setcurrent);
	}	
}	

void updategcvparameter(unsigned char encres3, unsigned char encres2)
{
	if(encres3!='$')
	{
		max_Gws=max_Gwire_speed[program_number];
		para.migmode.setwspeed=updatedata(para.migmode.setwspeed,mini.migmode.setwspeed,max_Gws,encres3);

		pstowfstr.setwspeed=para.migmode.setwspeed;
		
		//transoff.Hi_setwspeed=para.migmode.setwspeed >> 8;
	}	
	if(encres2!='$' && disparclen==0)
	{
		para.migmode.setvoltage=updatedata(para.migmode.setvoltage,mini.migmode.setvoltage,maxi.migmode.setvoltage,encres2);
	
		
		pstowfstr.Lo_setvoltage=para.migmode.setvoltage;
		pstowfstr.Hi_setvoltage=para.migmode.setvoltage >> 8;
		encod2='$';
		voltagechangef=1;
	}
	if(encod2!='$' && disparclen==1)// && (disparclen==1))
	{
		para.migmode.inductance=updatedata1(para.migmode.inductance,mini.migmode.inductance,maxi.migmode.inductance,encod2);
		encod2='$';
		pstowfstr.arclength=para.migmode.inductance;
	}
}	

void updatepccparameter(unsigned char encres3, unsigned char encres2)
{
	if(encres3!='$')
	{
		para.pmigmode.setwspeed=updatedata(para.pmigmode.setwspeed,mini.pmigmode.setwspeed,maxi.pmigmode.setwspeed,encres3);
		pstowfstr.setwspeed=para.pmigmode.setwspeed;
	}	
	if(encres2!='$')
	{
		para.pmigmode.arclength=updatedata1(para.pmigmode.arclength,mini.pmigmode.arclength,maxi.pmigmode.arclength,encres2);
		pstowfstr.arclength=para.pmigmode.arclength;
		
		//para.pmigmode.setvoltage=updatedata1(para.pmigmode.setvoltage,mini.pmigmode.setvoltage,maxi.pmigmode.setvoltage,encres2);
		//disp_hex_dec_volt(para.pmigmode.setvoltage);	
	}
}

void updatemigparameter(unsigned char encres1)
{	
}

void updatepmigparameter(unsigned char encres1)
{	
}





unsigned int updatedata(unsigned int operator1,unsigned int minimum,unsigned int maximum,unsigned char sign)
{
	
	mili1_100++;
    {
		if(sign == '+')
		{
			operator1=operator1+pluspara1;//++;
			if(operator1>=maximum)
			{
				operator1=maximum;
			}
			//updatedisp=1;
			//transon=1;	
		}
		else if (sign == '-')
		{
			if(operator1 >= minuspara1)
               operator1=operator1-minuspara1;
            else if(operator1 > minimum)
               operator1=operator1-1;//-;
            
            if(operator1 <= minimum)
            operator1 = minimum;
					
			
			
			/*if(operator1==minimum)
			{
				operator1=minimum;
			}
			else
			{
				operator1--;
			}*/
		    //transon=1;
		    //updatedisp=1;
		}
	}
	
	if(mili1_100<200)
    {
        if(sign=='+')
            pluscount1++;
        else if(sign=='-')
            minuscount1++;
    }
    else if(mili1_100>=200)
    {
        mili1_100=0;
        pluspara1=pluscount1>>1;
        minuspara1=minuscount1>>1;
        if(pluspara1<=1)
        pluspara1=1;
        if(minuspara1<=1)
        minuspara1=1;
        pluscount1=0;
        minuscount1=0;
    }
	
	return(operator1);
}

unsigned int updatedata1(unsigned int operator1,unsigned int minimum,unsigned int maximum,unsigned char sign)
{
	if(sign == '+')
	{
		operator1=operator1+1;//+5;
		if(operator1>=maximum)
		{
			operator1=maximum;
		}
		//updatedisp=1;
		//transon=1;	
	}
	else if (sign == '-')
	{
		if(operator1==minimum)
		{
			operator1=minimum;
		}
		else
		{
			operator1=operator1-1;//-5;
		}
	    //transon=1;
	    //updatedisp=1;
	}
	return(operator1);
}

void SYSTEM_INIT()
{
	PORTPIN_INIT();
	TIMER1_INIT();
	ENCODER_INIT();
	TIMER2_INIT();
 
	TIMER4_INIT();	
	TIMER5_INIT();
 
	ADC_INIT();
	UART1_INIT();
	UART2_INIT();
	lcd_int();
	SPI_INIT();
 	I2C_init();
}

/*void system_init()
{
	    
	    encoder_init();
	    display_int();
	    
	    scanswitch_init();
	    pid_carr_init();
          Motor_Pid_init();
	     FLEDLAT=1;
	    readmematstrt();	
	    lcd_int();
	    //readmematstrt();
}*/	 

void READ_PORTPIN(void)	//To read Torch,Inch,MotorTrip,Gas/Water, Pressuresw
{
  /*	static unsigned char torchstatus1=0xFF,torchstatus2=0xFF,inchstatus1=0xFF,inchstatus2=0xFF,kpressread=0,tans=0,ians=0;
	TORCHIPIO 	=1;	
	INCHIPIO	=1;
	if(TORCHIP == 1)
	{
		delay();
		if(TORCHIP == 1)
		torch=1;
	}
	else
	{
		delay();
		if(TORCHIP == 0)
		torch=0;

		y = ( x ==1 ? 2 : 0 ) ;
	}*/	
	/*if(kpressread==0)
	{
		torchstatus1=TORCHIP;
		inchstatus1=INCHIP;
		kpressread=1;
	}
	else if(kpressread==1)
	{
		torchstatus2=TORCHIP;
		inchstatus2=INCHIP;
		tans	=(torchstatus1	==	torchstatus2 	? 1:0);
		ians		=(inchstatus1	==	inchstatus2 		? 1:0);
		if(tans==1)
		{
			//torch=(torchstatus2	==	1 	? 'X':'X');//;'T':'X');
			inch	=(inchstatus2	==	1 	? 'I':'X');
		}
		//TRANS1('=');
		//TRANS1(torch);
		//TRANS1(inch);
		kpressread=0;
	}*/
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

void TIMER2_INIT(void)
{
	T2CON			=0;			//Stops the Timer1 and reset control reg.
	TMR2			=0;			//Clear contents of the timer register
	PR2				=1470;      //3600;//120usec 1470;//2948;//1470;//29387;     //1 ms 0X6000;	//Load the Period register with the value 0xFFFF 0x72cb interrupt after every 1.20msec
	IPC1bits.T2IP	=1;			//Setup Timer1 interrupt 
	IFS0bits.T2IF	=0;			//Clear the Timer1 interrupt status flag
	IEC0bits.T2IE	=1;			//Enable Timer1 interrupts
	T2CONbits.TON	=1;			//strat the timer
}



void TIMER3_INIT(void)
{
	T3CON=0;			//Stops the Timer1 and reset control reg.
	TMR3=0;			    //Clear contents of the timer register
	PR3=29387;//1470;   // for 50usec //0x0B84; //0xB84=2948=100usec; 0x024B=587=20usec//0x72CB=29387=1msec;	//Load the Period register with the value 0xFFFF
	IPC1bits.T3IP=1;	//Setup Timer1 interrupt 
	IFS0bits.T3IF=0;	//Clear the Timer1 interrupt status flag
	IEC0bits.T3IE=0;	//Enable Timer1 interrupts
	T3CONbits.TON=0;	//strat the timer
}

void TIMER4_INIT(void)
{
	T4CON			=0;			//Stops the Timer1 and reset control reg.
	TMR4			=0;			//Clear contents of the timer register
	PR4				=29300;//0X7500;	//Load the Period register with the value 0xFFFF 0x72cb interrupt after every 1.20msec
	IPC5bits.T4IP	=1;			//Setup Timer1 interrupt 
	IFS1bits.T4IF	=0;			//Clear the Timer1 interrupt status flag
	IEC1bits.T4IE	=1;			//Enable Timer1 interrupts
	T4CONbits.TON	=1;			//strat the timer
}
void TIMER5_INIT(void)
{
	T5CON	=0;		//Stops the Timer1 and reset control reg.
	TMR5	=0;		//Clear contents of the timer register
	PR5		=1475;  //1400;//293;//586;   //732;//2930;//293;//29387;//293;//0x0B84;//293=10USEC	//0xB84=2948=100usec; 0x024B=587=20usec//0x72CB=29387=1msec;	//Load the Period register with the value 0xFFFF
	IPC5bits.T5IP=7;//1;	//Setup Timer1 interrupt 

	T5CONbits.TON=1;	//strat the timer
}	


void PWM_INIT(void)
{
	/*
	OC1CON				=0;			//Turn off output compare module 1
	OC1RS				=0;			//write duty cycle biffer register
	OC1R				=0;			//write to initial duty cycle value
	OC1CONbits.OCM		=0;//6;			//output compare is configured as pwm generated
	OC2CON				=0;			//Turn off output compare module 1
	OC2RS				=0;			//write duty cycle biffer register
	OC2R				=0;			//write to initial duty cycle value
	OC2CONbits.OCM		=0;//6;			//output compare is configured as pwm generated
	*/
	
	OC2CON				=0;			//Turn off output compare module 1
	OC2RS				=0;			//write duty cycle biffer register
	OC2R				=0;			//write to initial duty cycle value
	OC2CONbits.OCM		=6;			//output compare is configured as pwm generated
	
	OC3CON				=0;			//Turn off output compare module 1
	OC3RS				=0;			//write duty cycle biffer register
	OC3R				=0;			//write to initial duty cycle value
	OC3CONbits.OCM		=6;			//output compare is configured as pwm generated
	
	PR2					=2949;		//1472 for 20khz,2949 for 10khz fred	//736 for 40khz freq.		//initialise pr2 reg. for freq.
	IPC1bits.T2IP		=2;			//setup timer2 at desired priority level
	IFS0bits.T2IF		=0;			//clear timer2 interrupt flag	
	IEC0bits.T2IE		=1;			//enable timer2 interrupt flag
	T2CONbits.TCKPS		=0;			//timer2 prescaler 1
	T2CONbits.TON		=1;			//start timer2
}

void ADC_INIT(void)
{
	ADPCFG 				= 0xFFFF;	// all port B pin as digital input pin
	ADPCFGbits.PCFG2 	= 0;		// port B.2 as analog (CURRENT FEEDBACK) input pin  
	ADPCFGbits.PCFG3 	= 0;		// port B.3 as analog (VOLTAGE FEEDBACK) input pin 
//	ADPCFGbits.PCFG4 	= 0;		// port B.4 as analog (MOTOR FEEDBACK VOLTAGE) input pin 
	ADPCFGbits.PCFG5 	= 0;		// port B.5 as analog (TRIP ERROR VOLTAGE) input pin 
	

	ADCSSL 				= 0x0000;			// skip all analog channels for input scanning
	ADCSSLbits.CSSL2 	= 1;		// select AN2 (CURRENT FEEDBACK) for input scanning 
	ADCSSLbits.CSSL3 	= 1;		// select AN3 (VOLTAGE FEEDBACK) for input scanning 
	//ADCSSLbits.CSSL4 	= 1;		// select AN4 (MOTOR FEEDBACK VOLTAGE) for input scanning 
	ADCSSLbits.CSSL5 	= 1;		// select AN5 (TRIP ERROR VOLTAGE) for input scanning 

	ADCON1bits.FORM 	= 0;		// data output format in unsigned integer 
	ADCON1bits.SSRC 	= 7;		// internal counter ends sampleing and starts conversion 
	ADCON2bits.VCFG 	= 0;		// setup adc voltage reference source AVdd & AVss 	
	ADCON2bits.CSCNA 	= 1;		// scan inputs 	
	ADCON2bits.SMPI 	= 2;        //3;// interrupt after 4 samples 	
	ADCON2bits.BUFM 	= 0;		// buffer configure as one 16-word buffer 	
	ADCON2bits.ALTS 	= 0;		// always use MUX A input multiplexer settings 	
	ADCON3bits.SAMC 	= 1;//1;//4;  	//  4 now 4 TAD //1; auto sample time bit = 1Tad //1=TAD,4=4 TAD,6=6 TAD
	ADCON3bits.ADRC 	= 0;		// AD conversion clock source from system clock 
	ADCON3bits.ADCS 	= 19;//39;
	ADCHSbits.CH0NA 	=  0;		// -ve input is Vref- 
//	IFS0bits.ADIF 	  	=  0;		// clear A to D conversion complete flag 
//	IEC0bits.ADIE 	  	=  1;		// enable A to D conversion interrupt 
	ADCON1bits.ADON 	=  1;		// on adc 
	ADCON1bits.ASAM 	=  1;		// Auto sample / conversion start 
}

void UART1_INIT()
{
  	U1BRG=194;//48;  // 38400    194= 		//9600 BAUD RATE
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

void PORTPIN_INIT()
{
	DECODEAIO	=0;
	DECODEBIO	=0;
	DECODECIO	=0;
	
	LEDGP3IO 	=0;
	LEDGP4IO 	=0;  

	SEGAIO		=0;
	SEGBIO		=0;
	SEGCIO		=0;
	SEGDIO		=0;
	SEGEIO		=0;
	SEGFIO		=0;
	SEGGIO		=0;
	SEGDPIO	=0;

	ROW1IO		=1;
	ROW2IO		=1;
	ROW3IO		=1;
	ROW4IO		=1;
	
	COLUMN1IO =1;
	COLUMN2IO =1;
	COLUMN3IO =1;

	ENCODER1AIO=1;
	ENCODER1BIO=1;
	
	ENCODER2AIO=1;
	ENCODER2BIO=1;
	
   	ENCODER3AIO=1;
	ENCODER3BIO=1;

	LCDENIO	=0;
	LCDRSIO 	=0;
	LCDCS1IO 	=0;
	LCDCS2IO	=0;

	DB0IO		=0;
	DB1IO		=0;
	DB2IO		=0;
	DB3IO		=0;
	DB4IO		=0;
	DB5IO		=0;
	DB6IO		=0;
	DB6IO		=0;
	DB7IO		=0;
	
	DACSCKIO	=0;
	DACSDIIO	=1;
	DACSDOIO 	=0;
	DACCSIO	=0;
	
 
	CCCVCTRLIO	=0;
	ARCONIO		=0;
	DECOD_ENIO	=0;
	ARCONOKIO	=0;
	GASWATERIPIO=1;
	PRESSERRIPIO=1;
//	TORCHIPIO	=1;
//	INCHIPIO	=1;
	PULSEIPIO	=1;
	MOVLDIPIO	=1;
	SHDNIO		=0;
//	MPWWIO		=0;
	EXTINT1IO	=1;
	EXTINT2IO	=1;
//	EXTRA2IO	=1;

	//default state of portpin
	DECODEALAT=0;
	DECODEBLAT=0;
	DECODECLAT=0;
	
	LEDGP3LAT =0;
	LEDGP4LAT =0;  

	SEGALAT=0;
	SEGBLAT=0;
	SEGCLAT=0;
	SEGDLAT=0;
	SEGELAT=0;
	SEGFLAT=0;
	SEGGLAT=0;
	SEGDPLAT=0;

	LCDENLAT	=0;
	LCDRSLAT 	=0;
	LCDCS1LAT 	=0;
	LCDCS2LAT	=0;
	
	DB0LAT		=0;
	DB1LAT		=0;
	DB2LAT		=0;
	DB3LAT		=0;
	DB4LAT		=0;
	DB5LAT		=0;
	DB6LAT		=0;
	DB7LAT		=0;
	
	DACSCKLAT	=0;
	DACSDOLAT	=0;
	DACCSLAT	=0;
	
//	GASRELAYLAT	=0;
//	HFRELAYLAT	=0;
	CCCVCTRLLAT	=0;
	ARCONLAT	=0;
	DECOD_ENLAT	=0;
	ARCONOKLAT	=0;
	SHDNLAT		=0;
//	MPWMLAT		=0;
}



void transmittowf()
{
	tx2chksum=0;
	pstowfstr.psstatusbyte=psstatusu.psstatusbyte[0];
	
	if(Type.twot==1)
	{
	wfstatus.twotfourtmode1=0;	
	}
	else if(Type.fourt==1)
	{
	wfstatus.twotfourtmode1=1;
	}	
	
	pstowfstr.wfstatusbyte=wfstatusu.wfstatusbyte[0];
    
    if(Type.voltage==1)
    {
	    command.volt_or_arc=1;
    }
    else
    	command.volt_or_arc=0;
    
    pstowfstr.command_to_wf=commandu.commandbyte[0];
    pstowfstr.weldmode=weldmode;
    
	for(iii=0;iii<=TX_DATA_LENGTH;iii++) // 
	{
		tx2chksum=tx2chksum+pstowfstru.pstransarr[iii];
		trans_ps_wf_arr[iii]=pstowfstru.pstransarr[iii];
	}
	trans_ps_wf_arr[iii]=tx2chksum;
	starttx2=1;
	tx2counter=0;
	U2TXREG='@';		
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




void display_Ldata()
{
{
			if(pmat==pms)
			lcdput(7,0,pmatms);
			else if(pmat==p71t1)
			lcdput(7,0,pmat71t1);
			else if(pmat==p180r)
			lcdput(7,0,pmat180r);
			else if(pmat==pss18)
			lcdput(7,0,pmatss18);
			else if(pmat==pss19)
			lcdput(7,0,pmatss19);
			else if(pmat==palu4043)
			lcdput(7,0,pmatalu4043);
			else if(pmat==palu5356)
			lcdput(7,0,pmatalu5356);
			else if(pmat==palu99)
			lcdput(7,0,pmatalu99);
			
		}
		{
			if(pdia==pzeropteight)
			lcdput(7,48,diazeropteight);
			else if(pdia==poneptzero)
			lcdput(7,48,diaoneptzero);
			else if(pdia==ponepttwo)
			lcdput(7,48,diaonepttwo);
			else if(pdia==poneptsix)
			lcdput(7,48,diaoneptsix);
		}
		{
			if(pgas==parco2)
			lcdput(7,90,gasarco2);
			else if(pgas==par)
			lcdput(7,90,gasar);	
			else if(pgas==paro2)
			lcdput(7,90,gasaro2);	
		}
		
		
}
 
void trip_detection(unsigned int looperrorvtg)
{
	
	
}	




void Detect_error(void)
{
	

}
void LCD_pulsemig_syn_data_write()
{
		{
			/*
			if(pmat==pms)
			lcdput(6,0,pmatms);
			else if(pmat==p71t1)
			lcdput(6,0,pmat71t1);
			else if(pmat==p180r)
			lcdput(6,0,pmat180r);
			else if(pmat==pss18)
			lcdput(6,0,pmatss18);
			else if(pmat==pss19)
			lcdput(6,0,pmatss19);
			else if(pmat==palu4043)
			lcdput(6,0,pmatalu4043);
			else if(pmat==palu5356)
			lcdput(6,0,pmatalu5356);
			else if(pmat==palu99)
			lcdput(6,0,pmatalu99);
			else if(pmat == ss_fcaw1)
			lcdput(6,0,pmatssfcaw1);
			*/	
			lcdput(6,0,cMatTxt[pmat]);					
			
		}
		{   /*
			if(pdia==pzeropteight)
			lcdput(6,48,diazeropteight);
			else if(pdia==poneptzero)
			lcdput(6,48,diaoneptzero);
			else if(pdia==ponepttwo)
			lcdput(6,48,diaonepttwo);
			else if(pdia==poneptsix)
			lcdput(6,48,diaoneptsix);
			*/
			lcdput(6,48,cDiaTxt[pdia]);			
		}
		{
			/*
			if(pgas==parco2)
			lcdput(6,88,gasarco2);
			else if(pgas==par)
			lcdput(6,88,gasar);	
			else if(pgas==paro2)
			lcdput(6,88,gasaro2);
			else if(pgas==pco2)
			lcdput(6,88,gasco2);
			*/
		lcdput(6,88,cGasTxt[pgas]);		
		lcdput(7,80,cGasPercent[pgas]);								
		}	
}

	
void LCD_mig_syn_data_write()
{
	{
		/*
					if(mat==ms)
						lcdput(7,0,matms);
					else if(mat==ss)
						lcdput(7,0,matss);
					else if(mat==alu)
						lcdput(7,0,matalu);
						*/
				lcdput(6,0,cMatMigTxt[mat]);	
				  //lcdput(6,0,cMatMigRoTxt[mat]);						
	}
	{
		/*
					if(dia==zeropteight)
						lcdput(7,48,diazeropteight);
					else if(dia==oneptzero)
						lcdput(7,48,diaoneptzero);
					else if(dia==onepttwo)
						lcdput(7,48,diaonepttwo);
					else if(dia==oneptsix)
						lcdput(7,48,diaoneptsix);
		*/
			lcdput(6,48,cDiaTxt[dia]);						
	}
	{
/*
					if(gas==arco2)
						lcdput(7,90,gasarco2);
					else if(gas==co2)
						lcdput(7,90,gasco2);
					else if(gas==ar)
						lcdput(7,90,gasar);	
					else if(gas==aro2)
						lcdput(7,90,gasaro2);	
*/
		lcdput(6,88,cGasTxt[gas]);		
		lcdput(7,80,cGasPercent[gas]);							
	}
}
//-------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
void send_string(unsigned char data[])
{
    unsigned char index=0;
	while(data[index]!=0)
	{
	TRANS1(data[index]);
	index++;
	}

}
//-------------------------------------------------------------------------------------------------------------------------------


