#define EE_bSIZE           0x1000               // 1024 Bytes  dsPIC30F6014A specific
#define EE_wSIZE           0x0800               // 512 words  dsPIC30F6014A specific
#define EE_START_ADDR      0x7FF000             // dsPIC30F6014A specific
#define EE_END_ADDR        0x800000             // dsPIC30F6014A specific
#define EEPROM_ROW_SIZE    16                   // dsPIC30F EEPROM ROW siz

#define MMA_EE_START_ADDR	 0x7FF010			//MMA ADDRESSS 7FF010--> FOR CURRENNT & NEXT 10 MEMORY ARRARY
#define TIG_EE_START_ADDR	 0x7FF0C0			//TIG ADDRESS  7FF0C0--> FOR CURRENNT & NEXT 10 MEMORY ARRARY
#define MIG_EE_START_ADDR	 0x7FF000			//MIG address
#define PMIG_EE_START_ADDR	 0x7FF2D0			//PMIG ADDRESS

#define MIG_PARA_MAX_SIZE 19

#define CURRENT_PARAMTR_SAVING_OFFSET 200

void write_mode_mem(unsigned char cMemoryLocation)
{
	unsigned long int eeprom_location;
 
	if(weldmode=='G')  //@ mig welding mode
	{
		eeprom_location=CURRENT_PARAMTR_SAVING_OFFSET+(cMemoryLocation-1)*MIG_PARA_MAX_SIZE*2; //@calculate the fixed offset in eeprom for different mem location
	
		
		para.migmode.gdiameter=dia;
		para.migmode.ggas=gas;
	    para.migmode.gmaterial=mat;
		
		EEPROMstruct_mig.dia=para.migmode.gdiameter;
		EEPROMstruct_mig.gas=para.migmode.ggas;
		EEPROMstruct_mig.p_mode=para.pulseweldmode;
		
		EEPROMstruct_mig.Twot0_fourt1=Type.twot;
	
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+0*2),weldmode);  					 //0 weld Mode
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_mig.EEPROM_struct_u);  //1 eeprom structure
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),para.migmode.preflow);  		 //2 preflow
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+3*2),para.migmode.setcurrent);  	 //3 set current
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),para.migmode.setvoltage);   	 //4 set vtg
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+5*2),para.migmode.craterspeed);  	 //5 crater curr
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+6*2),para.migmode.cratervoltage);  	 //6 crater vtg
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+7*2),para.migmode.burnback);  		 //7 burn back
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+8*2),para.migmode.setwspeed);  		 //8 set wirespeed
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.migmode.gmaterial);  		 //9 material 
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+10*2),para.migmode.postflow);  		 //10 postflow 
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+11*2),para.migmode.inductance);  	 //11 inductance=G/arc_length=P
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+12*2),para.creepspeedrate);  		 //12 creep speed  twinpulsefreq
//		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+13*2),twinpulsefreq);  				 //13 twinpulsefreq
//		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+14*2),twinpulseduty);  				 //14 twinpulseduty
//		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+15*2),twinpulseratio);  			 //15 twinpulseratio
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+16*2),pmig_auto0_man1);  	 	//16 thickness 
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+18*2),iProgramLoadLoc);  	 //18 Program Number 		
		 
	}
	else if(weldmode=='P')
	{
		eeprom_location=CURRENT_PARAMTR_SAVING_OFFSET+(cMemoryLocation-1)*MIG_PARA_MAX_SIZE*2; //@calculate the fixed offset in eeprom for different mem location
		
		para.pmigmode.setvoltage=Tbasevoltage;
		
		para.pmigmode.pdiameter=pdia;
		para.pmigmode.pgas=pgas;
	    para.pmigmode.pmaterial=pmat;
		
		EEPROMstruct_pmig.dia=para.pmigmode.pdiameter;
		EEPROMstruct_pmig.gas=para.pmigmode.pgas;
		EEPROMstruct_pmig.p_mode=para.pulseweldmode;
		EEPROMstruct_pmig.Twot0_fourt1=Type.twot;
		
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+0*2),weldmode);  					 //0 weld Mode
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_pmig.EEPROM_struct_u); //1 eeprom structure
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),para.pmigmode.preflow);  		 //2 preflow
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+3*2),para.pmigmode.setcurrent);  	 //3 set current
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),para.pmigmode.setvoltage);   	 //4 set vtg
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+5*2),para.migmode.craterspeed);  //5 crater curr
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+6*2),para.pmigmode.cratervoltage);  //6 crater vtg
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+7*2),para.pmigmode.burnback);  	 //7 burn back
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+8*2),para.pmigmode.setwspeed);  	 //8 set wirespeed
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.pmigmode.pmaterial);  	 //9 material 
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+10*2),para.pmigmode.postflow);  	 //10 postflow 
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+11*2),para.pmigmode.arclength);  	 //11 inductance=G/arc_length=P
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+12*2),para.pcreepspeedrate);  		 //12 creep speed  twinpulsefreq
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+13*2),para.twinpulsefreq);  		 //13 twinpulsefreq
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+14*2),para.twinpulseduty);  		 //14 twinpulseduty
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+15*2),para.twinpulseratio);  		 //15 twinpulseratio
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+16*2),pmig_auto0_man1);  	 //16 thickness 
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+18*2),iProgramLoadLoc);  	 //18 Program Number 
	}
	
//		cTestfg = 1;
//		iTest = eeprom_location;	
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+17*2),cMemoryLocation);  	 //16 thickness 

}
	
void recall_mode_mem(unsigned char cMemoryLocation)
{
	unsigned int eeprom_location;
//	unsigned char current_weldmode=0;
	/*Calculate EEPROM memory address*/
	eeprom_location=CURRENT_PARAMTR_SAVING_OFFSET+(cMemoryLocation-1)*MIG_PARA_MAX_SIZE*2; //@calculate the fixed offset in eeprom for different mem location

	if(cMemoryLocation	== EEPROM_Read_for_SaveRecall((eeprom_location+17*2)))
	{
	weldmode = 'N';
	/*Read Mode in which last power off save operation has been done*/
   weldmode=EEPROM_Read_for_SaveRecall((eeprom_location+0*2));  					 //0 weld Mode
	
	
	
//	if(current_weldmode!=weldmode)
//	{
//		modechangef=1;
//	}

	cTestmmr[0]=weldmode;
        if(weldmode=='T')
		{
			 
			TypeU.LEDGROUP[0]=0x00;
			Type.current		=1;
			Type.voltage		=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.tig				=1;
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
		}
		else if(weldmode=='G')
		{
		 
			TypeU.LEDGROUP[0]=0x00;
			Type.wirespeed		=1;
			Type.voltage		=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.mig			=1;
			Type.twot			=1;
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
		}
		else if(weldmode=='P')
		{
			 
			TypeU.LEDGROUP[0]=0x00;
			Type.wirespeed		=1;
			Type.voltage		=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.pulsemig		=1;
			Type.twot			=1;
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
		}
		else if(weldmode=='M')
		{
		 
			TypeU.LEDGROUP[0]=0x00;
			Type.current	=1;
			Type.arcforce	=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.mma		=1;
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
		}
	 	setlcdweldparameter=0;
		clearlcdf=0;
		TypeDP.DPGROUP[0]=0x00;

	
	 /*Read MIG mode parameter*/
	if(weldmode=='G') 
	{ 
	    EEPROM_struct_mig.EEPROM_struct_u=EEPROM_Read_for_SaveRecall((eeprom_location+1*2));  	//1 eeprom structure
		para.migmode.preflow		=EEPROM_Read_for_SaveRecall((eeprom_location+2*2));  	//2 preflow
		para.migmode.setcurrent 	=EEPROM_Read_for_SaveRecall((eeprom_location+3*2));  	//3 set current
		para.migmode.setvoltage 	=EEPROM_Read_for_SaveRecall((eeprom_location+4*2));   	//4 set vtg
	    para.migmode.craterspeed	=EEPROM_Read_for_SaveRecall((eeprom_location+5*2));  	//5 crater curr
		para.migmode.cratervoltage	=EEPROM_Read_for_SaveRecall((eeprom_location+6*2));  	//6 crater vtg
		para.migmode.burnback		=EEPROM_Read_for_SaveRecall((eeprom_location+7*2));  	//7 burn back
		para.migmode.setwspeed		=EEPROM_Read_for_SaveRecall((eeprom_location+8*2));  	//8 set wirespeed
		para.migmode.gmaterial		=EEPROM_Read_for_SaveRecall((eeprom_location+9*2));  	//9 material 
	    para.migmode.postflow		=EEPROM_Read_for_SaveRecall((eeprom_location+10*2));  	//10 postflow 
		para.migmode.inductance		=EEPROM_Read_for_SaveRecall((eeprom_location+11*2));  	//11 inductance=G/arc_length=P
		para.creepspeedrate			=EEPROM_Read_for_SaveRecall((eeprom_location+12*2));  	//12 creep speed  twinpulsefreq
//		EEPROM_Read_for_SaveRecall((eeprom_location+13*2),twinpulsefreq);  				//13 twinpulsefreq
//		EEPROM_Read_for_SaveRecall((eeprom_location+14*2),twinpulseduty);  				//14 twinpulseduty
//		EEPROM_Read_for_SaveRecall((eeprom_location+15*2),twinpulseratio);  			 	//15 twinpulseratio
		pmig_auto0_man1		=EEPROM_Read_for_SaveRecall((eeprom_location+16*2));  	//16 thickness
		
		iProgramLoadLoc = EEPROM_Read_for_SaveRecall((eeprom_location+18*2));  	//16 Program Number. 
	
	    para.migmode.gdiameter=EEPROMstruct_mig.dia;
		para.migmode.ggas=EEPROMstruct_mig.gas;
		para.pulseweldmode=EEPROMstruct_mig.p_mode;
		wfstatus.twotfourtmode1=EEPROMstruct_mig.Twot0_fourt1;
		Type.twot=EEPROMstruct_mig.Twot0_fourt1;
		Type.fourt= Type.twot^1; 
		
		
		gas=para.migmode.ggas;
		dia=para.migmode.gdiameter;
		mat=para.migmode.gmaterial;
	
	    pmigsetwirespeed=para.migmode.setwspeed;
	} 
	else if(weldmode=='P')/*Read P-MIG mode parameter*/
	{
		EEPROM_struct_pmig.EEPROM_struct_u=EEPROM_Read_for_SaveRecall((eeprom_location+1*2)); 	 //1 eeprom structure
		para.pmigmode.preflow		 =EEPROM_Read_for_SaveRecall((eeprom_location+2*2));  	 //2 preflow
		para.pmigmode.setcurrent	 =EEPROM_Read_for_SaveRecall((eeprom_location+3*2));  	 //3 set current
		para.pmigmode.setvoltage	 =EEPROM_Read_for_SaveRecall((eeprom_location+4*2));    //4 set vtg
		para.pmigmode.craterspeed    =EEPROM_Read_for_SaveRecall((eeprom_location+5*2));    //5 crater curr
		para.pmigmode.cratervoltage  =EEPROM_Read_for_SaveRecall((eeprom_location+6*2));    //6 crater vtg
		para.pmigmode.burnback		 =EEPROM_Read_for_SaveRecall((eeprom_location+7*2));  	 //7 burn back
		para.pmigmode.setwspeed		 =EEPROM_Read_for_SaveRecall((eeprom_location+8*2));  	 //8 set wirespeed
		para.pmigmode.pmaterial		 =EEPROM_Read_for_SaveRecall((eeprom_location+9*2));  	 //9 material 
		para.pmigmode.postflow		 =EEPROM_Read_for_SaveRecall((eeprom_location+10*2));   //10 postflow 
		para.pmigmode.arclength		 =EEPROM_Read_for_SaveRecall((eeprom_location+11*2));   //11 inductance=G/arc_length=P
		para.pcreepspeedrate		 =EEPROM_Read_for_SaveRecall((eeprom_location+12*2));   //12 creep speed  twinpulsefreq
		para.twinpulsefreq			 =EEPROM_Read_for_SaveRecall((eeprom_location+13*2));   //13 twinpulsefreq
		para.twinpulseduty			 =EEPROM_Read_for_SaveRecall((eeprom_location+14*2));   //14 twinpulseduty
		para.twinpulseratio			 =EEPROM_Read_for_SaveRecall((eeprom_location+15*2));   //15 twinpulseratio
		pmig_auto0_man1		 		 =EEPROM_Read_for_SaveRecall((eeprom_location+16*2));   //16 thickness 
		
		iProgramLoadLoc = EEPROM_Read_for_SaveRecall((eeprom_location+18*2));  	//16 Program Number. 
		
		para.pmigmode.pdiameter=EEPROMstruct_pmig.dia;
		para.pmigmode.pgas=EEPROMstruct_pmig.gas;
		para.pulseweldmode=EEPROMstruct_pmig.p_mode;
		wfstatus.twotfourtmode1=EEPROMstruct_pmig.Twot0_fourt1;
		Type.twot=EEPROMstruct_pmig.Twot0_fourt1;
		Type.fourt= Type.twot^1;
		
		pgas=para.pmigmode.pgas;
		pdia=para.pmigmode.pdiameter;
		pmat=para.pmigmode.pmaterial;
		
		ppmigsetwirespeed=para.pmigmode.setwspeed;
		ppmigsetvoltage=0;
		Tbasevoltage=para.pmigmode.setvoltage;
	}
		check_eeprom_values();
	}
	else
	{
	    clrlcd();
    	lcdput(3,0,"*InValid Recall*");   					    
	    for(j=0;j<5000;j++)
	    delay_pmig();				    					
		
		
	}
//		cTestfg = 1;
//		iTest = eeprom_location;
}

unsigned int EEPROM_Read(unsigned long int EE_Addr)
{
   	//unsigned long int Act_EE_Addr = EE_Addr + EE_START_ADDR;
   	unsigned int EE_Data = 0xFFFF;
   	//unsigned int SAV_TBLPAG = TBLPAG;
   	if(memoryzone=='X')
	{
		EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
	}
	else if(memoryzone=='M')
	{
		EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + MMA_EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
	}	
	else if(memoryzone=='T')
	{
		EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + TIG_EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
	}	
	else if(memoryzone=='G')
	{
		EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + MIG_EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
	}	
	else if(memoryzone=='P')
	{
		EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + PMIG_EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
	}	
   	 	
    TBLPAG = Act_EE_Addr >> 16;
    __asm__("TBLRDL [%1], %0" : /* outputs */ "=r"(EE_Data) : /* inputs */ "r"(Act_EE_Addr));
   	TBLPAG = SAV_TBLPAG;
   	return EE_Data;
}

unsigned int EEPROM_Erase_Write(unsigned int EE_Addr,unsigned int EE_Data)
{
   	//unsigned int EE_Stat = 0;
   	//unsigned long int Act_EE_Addr = EE_Addr + EE_START_ADDR;
   	//unsigned int SAV_TBLPAG = TBLPAG;
	if(memoryzone=='X')
	{
		EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
	}
	else if(memoryzone=='M')
	{
		EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + MMA_EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
	}	
	else if(memoryzone=='T')
	{
		EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + TIG_EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
	}	
	else if(memoryzone=='G')
	{
		EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + MIG_EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
	}	
	else if(memoryzone=='P')
	{
		EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + PMIG_EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
	}
		
   	if(NVMCONbits.WRERR == 0) 					//Privious NV write error detected
   	{
		NVMADRU = (Act_EE_Addr >> 16) & 0x7F;
		NVMADR = Act_EE_Addr & 0xFFFF;
      
        NVMCONbits.WREN = set;             		//Enable an program operation
        NVMCONbits.PROGOP = 0x44;           	//Word Erase command
              
		__builtin_write_NVM();       			//Unlock, iniate erase/write & wait till complete
		while(NVMCONbits.WR == 1);   			//Wait for operation complete       
                  
		if(EEPROM_Read(EE_Addr) == 0xFFFF) 
       	{
           	TBLPAG = Act_EE_Addr >> 16;
           	__asm__("TBLWTL %1, [%0]" : /*no outputs*/ : /*inputs*/ "r"(Act_EE_Addr), "r"(EE_Data));
            NVMCONbits.WREN = set;             	//Enable an program operation
            NVMCONbits.PROGOP = 0x04;           //EE Word Write
            __builtin_write_NVM();       		//Unlock, iniate erase/write & wait till complete
            while(NVMCONbits.WR == 1);   		//Wait for operation complete       

            if(EEPROM_Read(EE_Addr) != EE_Data) //EE Write error (MCLR,BOR,WDT)
            	EE_Stat = 1;
       	}   
       	else 
       		EE_Stat = 2;                    	//EE Erase error (MCLR,BOR,WDT)
    }
   	TBLPAG = SAV_TBLPAG;
   	return EE_Stat;
}
 
unsigned int EEPROM_Read_for_SaveRecall(unsigned long int EE_Addr)
{
   		unsigned int EE_Data = 0xFFFF;
    	EE_Stat = 0;
   		Act_EE_Addr = EE_Addr + EE_START_ADDR;
   		SAV_TBLPAG = TBLPAG;
   		
		TBLPAG = Act_EE_Addr >> 16;
		__asm__("TBLRDL [%1], %0" : /* outputs */ "=r"(EE_Data) : /* inputs */ "r"(Act_EE_Addr));
		TBLPAG = SAV_TBLPAG;
		return EE_Data;
}

unsigned int EEPROM_Erase_Write_for_SaveRecall(unsigned int EE_Addr,unsigned int EE_Data)
{
	EE_Stat = 0;
	Act_EE_Addr = EE_Addr + EE_START_ADDR;
	SAV_TBLPAG = TBLPAG;
	
		if(NVMCONbits.WRERR == 0) 					//Privious NV write error detected
		{
		NVMADRU = (Act_EE_Addr >> 16) & 0x7F;
		NVMADR = Act_EE_Addr & 0xFFFF;
		
		NVMCONbits.WREN = set;             		//Enable an program operation
		NVMCONbits.PROGOP = 0x44;           	//Word Erase command
		
		__builtin_write_NVM();       			//Unlock, iniate erase/write & wait till complete
		while(NVMCONbits.WR == 1);   			//Wait for operation complete       
		
			if(EEPROM_Read(EE_Addr) == 0xFFFF) 
			{
				TBLPAG = Act_EE_Addr >> 16;
				__asm__("TBLWTL %1, [%0]" : /*no outputs*/ : /*inputs*/ "r"(Act_EE_Addr), "r"(EE_Data));
				NVMCONbits.WREN = set;             	//Enable an program operation
				NVMCONbits.PROGOP = 0x04;           //EE Word Write
				__builtin_write_NVM();       		//Unlock, iniate erase/write & wait till complete
				while(NVMCONbits.WR == 1);   		//Wait for operation complete       
				
				if(EEPROM_Read(EE_Addr) != EE_Data) //EE Write error (MCLR,BOR,WDT)
				EE_Stat = 1;
			}   
			else 
				EE_Stat = 2;                    	//EE Erase error (MCLR,BOR,WDT)
		}
		
	TBLPAG = SAV_TBLPAG;
//-------------------------------------------------------------
// here adding the delay of appr. 2msec to write the byte in eeprom
/*
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();
	delay_pmig();	
*/			
//-------------------------------------------------------------
	return EE_Stat;
}  
/*
	eeprom_location=0;//@for mig parameter 
	eeprom_location=MIG_PARA_MAX_SIZE*1;//@for Pmig parameter 
	eeprom_location=2;//@for mma parameter 
	eeprom_location=3;//@for tig parameter 
*/
void read_current_status(void)
{
		unsigned int eeprom_location;
		
/*Read memory location '0' for weld mode, for that memoryzone 'X' is selected*/
		memoryzone='X';
		weldmode=EEPROM_Read(0);  
							 
/********************************Arc On Time**************************/
	arcontime.hr=EEPROM_Read(190);
	arcontime.min=EEPROM_Read(192);
//	arcontime.sec=EEPROM_Read(194);
	
    if(arcontime.hr==0xffff || arcontime.hr > 999)
	{
		arcontime.hr=0;
        EEPROM_Erase_Write((190),arcontime.hr);
    }
	if(arcontime.min==0xffff || arcontime.min >60)
	{
		arcontime.min=0;
		EEPROM_Erase_Write(192,arcontime.min);
	}
//	if(arcontime.sec==0xffff || arcontime.sec >60)
//	{
//		arcontime.sec=0;
//		EEPROM_Erase_Write(194,arcontime.sec);
//	}
/********************************Arc On Time**************************/



	if(weldmode=='G')    
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*0;												//@Offset for MIG ParaMeter 
        EEPROM_struct_mig.EEPROM_struct_u=EEPROM_Read_for_SaveRecall((eeprom_location+1*2));     //1 eeprom structure
		para.migmode.preflow		=EEPROM_Read_for_SaveRecall((eeprom_location+2*2));  	//2 preflow
		para.migmode.setcurrent 	=EEPROM_Read_for_SaveRecall((eeprom_location+3*2));  	//3 set current
		para.migmode.setvoltage 	=EEPROM_Read_for_SaveRecall((eeprom_location+4*2));   	//4 set vtg
	    para.migmode.craterspeed	=EEPROM_Read_for_SaveRecall((eeprom_location+5*2));  	//5 crater curr
		para.migmode.cratervoltage	=EEPROM_Read_for_SaveRecall((eeprom_location+6*2));  	//6 crater vtg
		para.migmode.burnback		=EEPROM_Read_for_SaveRecall((eeprom_location+7*2));  	//7 burn back
		para.migmode.setwspeed		=EEPROM_Read_for_SaveRecall((eeprom_location+8*2));  	//8 set wirespeed
		para.migmode.gmaterial		=EEPROM_Read_for_SaveRecall((eeprom_location+9*2));  	//9 material 
	    para.migmode.postflow		=EEPROM_Read_for_SaveRecall((eeprom_location+10*2));  	//10 postflow 
		para.migmode.inductance		=EEPROM_Read_for_SaveRecall((eeprom_location+11*2));  	//11 inductance=G/arc_length=P
		para.creepspeedrate			=EEPROM_Read_for_SaveRecall((eeprom_location+12*2));  	//12 creep speed  twinpulsefreq
//		EEPROM_Read_for_SaveRecall((eeprom_location+13*2),twinpulsefreq);  					//13 twinpulsefreq  only for P-mig
//		EEPROM_Read_for_SaveRecall((eeprom_location+14*2),twinpulseduty);  					//14 twinpulseduty  only for P-mig 
//		EEPROM_Read_for_SaveRecall((eeprom_location+15*2),twinpulseratio);  			 	//15 twinpulseratio only for P-mig
		pmig_auto0_man1				=EEPROM_Read_for_SaveRecall((eeprom_location+16*2));  	//16 thickness 
		//iProgramLoadLoc				=EEPROM_Read_for_SaveRecall((eeprom_location+17*2));    //17 Program Number 		
		
		para.migmode.gdiameter=EEPROMstruct_mig.dia;
		para.migmode.ggas=EEPROMstruct_mig.gas;
//		para.pulseweldmode=EEPROMstruct_mig.p_mode;  //only for P-mig
		wfstatus.twotfourtmode1=EEPROMstruct_mig.Twot0_fourt1;
		Type.twot=EEPROMstruct_mig.Twot0_fourt1;
		Type.fourt= Type.twot^1;
		
		prev_eeprom_mig_struct=EEPROM_struct_mig.EEPROM_struct_u;
		read_gpreflow=para.migmode.preflow;   				//2
		read_gsetcurrent=para.migmode.setcurrent;			//3
		read_gsetvoltage=para.migmode.setvoltage;			//4
		read_gcratercurrent=para.migmode.craterspeed;		//5
		read_gcratervoltage=para.migmode.cratervoltage;		//6
		read_gburnback=para.migmode.burnback;				//7
		read_gsetwspeed=para.migmode.setwspeed;				//8
		read_gmaterial=para.migmode.gmaterial;				//9
		read_gpostflow=para.migmode.postflow;				//10
		read_inductance=para.migmode.inductance;			//11
		prevcreepspeedrate=para.creepspeedrate;				//12
	 
		
		pmigsetwirespeed=para.migmode.setwspeed;
		pinductance=para.migmode.inductance;
		pmigsetvoltage=para.migmode.setvoltage;
		
//		gas=para.migmode.ggas;
//		dia=para.migmode.gdiameter;
//		mat=para.migmode.gmaterial;
		 		
	}
	else if(weldmode=='P')
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*1;
		EEPROM_struct_pmig.EEPROM_struct_u=EEPROM_Read_for_SaveRecall((eeprom_location+1*2)); 	 //1 eeprom structure
		para.pmigmode.preflow		 =EEPROM_Read_for_SaveRecall((eeprom_location+2*2));  	 //2 preflow
		para.pmigmode.setcurrent	 =EEPROM_Read_for_SaveRecall((eeprom_location+3*2));  	 //3 set current
		para.pmigmode.setvoltage	 =EEPROM_Read_for_SaveRecall((eeprom_location+4*2));    //4 set vtg
		para.pmigmode.craterspeed    =EEPROM_Read_for_SaveRecall((eeprom_location+5*2));    //5 crater curr
		para.pmigmode.cratervoltage  =EEPROM_Read_for_SaveRecall((eeprom_location+6*2));    //6 crater vtg
		para.pmigmode.burnback		 =EEPROM_Read_for_SaveRecall((eeprom_location+7*2));  	 //7 burn back
		para.pmigmode.setwspeed		 =EEPROM_Read_for_SaveRecall((eeprom_location+8*2));  	 //8 set wirespeed
		para.pmigmode.pmaterial		 =EEPROM_Read_for_SaveRecall((eeprom_location+9*2));  	 //9 material 
		para.pmigmode.postflow		 =EEPROM_Read_for_SaveRecall((eeprom_location+10*2));   //10 postflow 
		para.pmigmode.arclength		 =EEPROM_Read_for_SaveRecall((eeprom_location+11*2));   //11 inductance=G/arc_length=P
		para.pcreepspeedrate		 =EEPROM_Read_for_SaveRecall((eeprom_location+12*2));   //12 creep speed  twinpulsefreq
		para.twinpulsefreq			 =EEPROM_Read_for_SaveRecall((eeprom_location+13*2));   //13 twinpulsefreq
		para.twinpulseduty			 =EEPROM_Read_for_SaveRecall((eeprom_location+14*2));   //14 twinpulseduty
		para.twinpulseratio			 =EEPROM_Read_for_SaveRecall((eeprom_location+15*2));   //15 twinpulseratio
		pmig_auto0_man1				 =EEPROM_Read_for_SaveRecall((eeprom_location+16*2));   //16 thickness 
		//para.pulseweldmode			 =EEPROM_Read_for_SaveRecall((eeprom_location+19*2));   //19 pulse weld mode 
		//iProgramLoadLoc			EEPROM_struct_pmig.EEPROM_struct_u=EEPROM_Read_for_SaveRecall((eeprom_location+1*2));
		
		para.pmigmode.pdiameter=EEPROMstruct_pmig.dia;
		para.pmigmode.pgas=EEPROMstruct_pmig.gas;
		para.pulseweldmode=EEPROMstruct_pmig.p_mode;
		wfstatus.twotfourtmode1=EEPROMstruct_pmig.Twot0_fourt1;
		Type.twot=EEPROMstruct_pmig.Twot0_fourt1;
		Type.fourt= Type.twot^1;
			
		
//		pgas=para.pmigmode.pgas;
//		pdia=para.pmigmode.pdiameter;
//		pmat=para.pmigmode.pmaterial;
		
		read_pcreepspeedrate=para.pcreepspeedrate;
		
		ppmigsetwirespeed=para.pmigmode.setwspeed;
	}
	else if(weldmode=='M')
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*2;												//@Offset for MIG ParaMeter 
		para.mmamode.setcurrent		=EEPROM_Read_for_SaveRecall((eeprom_location+1*2));  	//2 preflow
		para.mmamode.arcforce	 	=EEPROM_Read_for_SaveRecall((eeprom_location+2*2));  	//3 set current
	    
	    para.mmamode.mmaterial		=EEPROM_Read_for_SaveRecall((eeprom_location+3*2));  	//2 preflow
		para.mmamode.melectrodesize	=EEPROM_Read_for_SaveRecall((eeprom_location+4*2));  	//3 set current

		para.mmamode.melectrotype	=EEPROM_Read_for_SaveRecall((eeprom_location+5*2));  	//2 preflow

		iHotstartper	=EEPROM_Read_for_SaveRecall((eeprom_location+6*2));  	//2 preflow
		
		if(para.mmamode.setcurrent <= HOT_START_SET_CURR_LMT)
		{
			cHotstartfg = 1;
		}	
	
		mmat=para.mmamode.mmaterial;
		mdia=para.mmamode.melectrodesize;
		melectrode=para.mmamode.melectrotype;
	
	}
	else if(weldmode=='T')
	{
	    eeprom_location=MIG_PARA_MAX_SIZE*2*3;
	    
	    para.tigmode.setcurrent=EEPROM_Read_for_SaveRecall((eeprom_location+1*2)); 
	    para.tigmode.tmaterial=EEPROM_Read_for_SaveRecall((eeprom_location+2*2)); 
	    para.tigmode.tplatesize=EEPROM_Read_for_SaveRecall((eeprom_location+3*2)); 
	    para.tigmode.tjointtype=EEPROM_Read_for_SaveRecall((eeprom_location+4*2)); 	
	    
	    tmat=para.tigmode.tmaterial;
		tdia=para.tigmode.tplatesize;
		tjoint=para.tigmode.tjointtype;	
	}	
	
}


void write_current_status(void)
{
	unsigned long int eeprom_location;
	
 /********************************Arc On Time**************************/

	if(prevhr!= arcontime.hr)
	{
		EEPROM_Erase_Write((190),arcontime.hr);
		prevhr= arcontime.hr;
	}   
	if(prevmin!=arcontime.min)
	{
		EEPROM_Erase_Write((192),arcontime.min);
		prevmin=arcontime.min;
	}   
//	if(prevsec!=arcontime.sec)
//	{
//		EEPROM_Erase_Write((194),arcontime.sec);
//		prevsec=arcontime.sec;
//	}   
/********************************Arc On Time**************************/
	
	if(weldmode=='G')  //@ mig welding mode
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*0;
		
		EEPROMstruct_mig.dia=para.migmode.gdiameter;
		EEPROMstruct_mig.gas=para.migmode.ggas;
	//	EEPROMstruct_mig.p_mode=para.pulseweldmode;  //only for pulse mode
	    EEPROMstruct_mig.Twot0_fourt1=Type.twot;
	
		if(prev_weldmode!=weldmode)
		{
			EEPROM_Erase_Write_for_SaveRecall(0,weldmode);  					 //0 weld Mode
			prev_weldmode=weldmode;
		}
			 
				
		if(prev_eeprom_mig_struct!=EEPROM_struct_mig.EEPROM_struct_u)
	    {
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_mig.EEPROM_struct_u);  //1 eeprom structure
		prev_eeprom_mig_struct=EEPROM_struct_mig.EEPROM_struct_u; 
		}
		
		if(read_gpreflow!=para.migmode.preflow)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),para.migmode.preflow);  		 //2 preflow
		read_gpreflow=para.migmode.preflow;
		}
		
		if(read_gsetcurrent!=para.migmode.setcurrent)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+3*2),para.migmode.setcurrent);  	 //3 set current
		read_gsetcurrent=para.migmode.setcurrent;
		}
		
		if(read_gsetvoltage!=para.migmode.setvoltage)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),para.migmode.setvoltage);   	 //4 set vtg
		read_gsetvoltage=para.migmode.setvoltage;
		}		
		
		if(read_gcratercurrent!=para.migmode.craterspeed)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+5*2),para.migmode.craterspeed);  	 //5 crater curr
		read_gcratercurrent=para.migmode.craterspeed;
		}
		
		if(read_gcratervoltage!=para.migmode.cratervoltage)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+6*2),para.migmode.cratervoltage);  	 //6 crater vtg
		read_gcratervoltage=para.migmode.cratervoltage;
		}
		
		if(read_gburnback!=para.migmode.burnback)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+7*2),para.migmode.burnback);  		 //7 burn back
		read_gburnback=para.migmode.burnback;
		}
		
		if(read_gsetwspeed!=para.migmode.setwspeed)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+8*2),para.migmode.setwspeed);  		 //8 set wirespeed
		read_gsetwspeed=para.migmode.setwspeed;
		}
		
		if(read_gmaterial!=para.migmode.gmaterial)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.migmode.gmaterial);  		 //9 material 
		read_gmaterial=para.migmode.gmaterial;
		}
		
		if(read_gpostflow!=para.migmode.postflow)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+10*2),para.migmode.postflow);  		 //10 postflow 
		read_gpostflow=para.migmode.postflow;
		}
		
		if(read_inductance!=para.migmode.inductance)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+11*2),para.migmode.inductance);  	 //11 inductance=G/arc_length=P
		read_inductance=para.migmode.inductance;
		}
		
		if(prevcreepspeedrate!=para.creepspeedrate)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+12*2),para.creepspeedrate);  		 //12 creep speed  twinpulsefreq
		prevcreepspeedrate=para.creepspeedrate;
		}
//		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+13*2),twinpulsefreq);  				 //13 twinpulsefreq
//		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+14*2),twinpulseduty);  				 //14 twinpulseduty
//		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+15*2),twinpulseratio);  			 //15 twinpulseratio
		
		if(read_pmig_auto0_man1!=pmig_auto0_man1)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+16*2),pmig_auto0_man1);  	 //16 thickness 
		read_pmig_auto0_man1=pmig_auto0_man1;
		}
		
		
		/*if(iPrevProgNoInMemoery != iProgramLoadLoc)
		{
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+17*2),iProgramLoadLoc);  	 //17 Program Number 
			iPrevProgNoInMemoery = iProgramLoadLoc;
		}*/
	}
	else if(weldmode=='P')
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*1;
		
		EEPROMstruct_pmig.dia=para.pmigmode.pdiameter;
		EEPROMstruct_pmig.gas=para.pmigmode.pgas;
       	EEPROMstruct_pmig.p_mode=para.pulseweldmode;  //only for pulse mode
	    EEPROMstruct_pmig.Twot0_fourt1=Type.twot;
	    
		para.pmigmode.setvoltage=Tbasevoltage;
		para.pmigmode.setcurrent=dispautocurrent;
	
		if(prev_weldmode!=weldmode)
		{
			EEPROM_Erase_Write_for_SaveRecall(0,weldmode);  					 //0 weld Mode
			prev_weldmode=weldmode;
		}
			 
				
		if(prev_eeprom_pmig_struct!=EEPROM_struct_pmig.EEPROM_struct_u)
	    {
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_pmig.EEPROM_struct_u);  //1 eeprom structure
		prev_eeprom_pmig_struct=EEPROM_struct_pmig.EEPROM_struct_u;
		}
		
		if(read_ppreflow!=para.pmigmode.preflow)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),para.pmigmode.preflow);  		 //2 preflow
		read_ppreflow=para.pmigmode.preflow;
		}
		
		 if(read_psetcurrent!=para.pmigmode.setcurrent)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+3*2),para.pmigmode.setcurrent);  	 //3 set current
		read_psetcurrent=para.pmigmode.setcurrent;
		}
		
		if(read_psetvoltage!=para.pmigmode.setvoltage)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),para.pmigmode.setvoltage);   	 //4 set vtg
		read_psetvoltage=para.pmigmode.setvoltage;
		}		
		
		if(read_pcratercurrent!=para.pmigmode.craterspeed)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+5*2),para.pmigmode.craterspeed);  	 //5 crater curr
		read_pcratercurrent=para.pmigmode.craterspeed;
		}
		
		if(read_pcratervoltage!=para.pmigmode.cratervoltage)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+6*2),para.pmigmode.cratervoltage);  	 //6 crater vtg
		read_pcratervoltage=para.pmigmode.cratervoltage;
		}
		
		if(read_pburnback!=para.pmigmode.burnback)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+7*2),para.pmigmode.burnback);  		 //7 burn back
		read_pburnback=para.pmigmode.burnback;
		}
		
		if(read_psetwspeed!=para.pmigmode.setwspeed)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+8*2),para.pmigmode.setwspeed);  		 //8 set wirespeed
		read_psetwspeed=para.pmigmode.setwspeed;
		}
		
		if(read_pmaterial!=para.pmigmode.pmaterial)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.pmigmode.pmaterial);  		 //9 material 
		read_pmaterial=para.pmigmode.pmaterial;
		}
		
		if(read_ppostflow!=para.pmigmode.postflow)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+10*2),para.pmigmode.postflow);  		 //10 postflow 
		read_ppostflow=para.pmigmode.postflow;
		}
		
		if(read_parclength!=para.pmigmode.arclength)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+11*2),para.pmigmode.arclength);  	 //11 inductance=G/arc_length=P
		read_parclength=para.pmigmode.arclength;
		}
		
		if(read_pcreepspeedrate!=para.pcreepspeedrate)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+12*2),para.pcreepspeedrate);  		 //12 creep speed  twinpulsefreq
		read_pcreepspeedrate=para.pcreepspeedrate;
		}
		
		
		if(read_ptwinpulsefreq!=para.twinpulsefreq)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+13*2),para.twinpulsefreq);  				 //13 twinpulsefreq
		read_ptwinpulsefreq=para.twinpulsefreq;
		}
		
		if(read_ptwinpulseduty!=para.twinpulseduty)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+14*2),para.twinpulseduty);  				 //14 twinpulseduty
		read_ptwinpulseduty=para.twinpulseduty;
		}
		
		
		if(read_ptwinpulseratio!=para.twinpulseratio)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+15*2),para.twinpulseratio);  			 //15 twinpulseratio
		read_ptwinpulseratio=para.twinpulseratio;
		}
		
		
		if(read_pmig_auto0_man1!=pmig_auto0_man1)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+16*2),pmig_auto0_man1);  	 //16 auto manual
		read_pmig_auto0_man1=pmig_auto0_man1;
		}


		/*if(read_ppulseweldmode!=para.pulseweldmode)
		{
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+19*2),para.pulseweldmode);	//19 pulse weld mode
			read_ppulseweldmode=para.pulseweldmode;
			
		}*/			
		/*if(iPrevProgNoInMemoery != iProgramLoadLoc)
		{
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+17*2),iProgramLoadLoc);  	 //17 Program Number 
			iPrevProgNoInMemoery = iProgramLoadLoc;
		}		
		*/
	}
	else if(weldmode=='M')
	{
		
		if(prev_weldmode!=weldmode)
		{
			EEPROM_Erase_Write_for_SaveRecall(0,weldmode);  					 //0 weld Mode
			prev_weldmode=weldmode;
		}
		
		eeprom_location=MIG_PARA_MAX_SIZE*2*2;
				
		para.mmamode.mmaterial=mmat;
		para.mmamode.melectrodesize=mdia;
		para.mmamode.melectrotype=melectrode;		
		
		if(read_msetcurrent!=para.mmamode.setcurrent)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),para.mmamode.setcurrent);  	 //1 set current
		read_msetcurrent=para.mmamode.setcurrent;
		}
		
		if(para.mmamode.setcurrent <= HOT_START_SET_CURR_LMT)
		{
			cHotstartfg = 1;
		}	
				
		if(read_marcforce!=para.mmamode.arcforce)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),para.mmamode.arcforce);  	 //2 arcforce
		read_marcforce=para.mmamode.arcforce;
		}
		
		if(read_mmaterial!=para.mmamode.mmaterial)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+3*2),para.mmamode.mmaterial);  	 //3 material
		read_mmaterial=para.mmamode.mmaterial;
		}
		
		if(read_melectrodesize!=para.mmamode.melectrodesize)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),para.mmamode.melectrodesize); //4 electrode size
		read_melectrodesize=para.mmamode.melectrodesize;
		}
		
		if(read_melectrotype!=para.mmamode.melectrotype)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+5*2),para.mmamode.melectrotype); //4 electrode type
		read_melectrotype=para.mmamode.melectrotype;
		}

		if(read_mHotstart!= iHotstartper)
		{
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+6*2),iHotstartper); //4 electrode type
			read_mHotstart= iHotstartper;
		}		
	}	
 	else if(weldmode=='T')
 	{
	 
	 	if(prev_weldmode!=weldmode)
		{
			EEPROM_Erase_Write_for_SaveRecall(0,weldmode);  					 //0 weld Mode
			prev_weldmode=weldmode;
		}
		
		eeprom_location=MIG_PARA_MAX_SIZE*2*3;
				
		para.tigmode.tmaterial=tmat;
		para.tigmode.tplatesize=tdia;
		para.tigmode.tjointtype=tjoint;		
		
		if(read_tsetcurrent!=para.tigmode.setcurrent)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),para.tigmode.setcurrent); //set current
		read_tsetcurrent=para.tigmode.setcurrent;
		}
	 
	    if(read_tmaterial!=para.tigmode.tmaterial)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),para.tigmode.tmaterial);  //material  
		read_tmaterial=para.tigmode.tmaterial;
		}
		
		
		if(read_tplatesize!=para.tigmode.tplatesize)										//plate size
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+3*2),para.tigmode.tplatesize);  	  
		read_tplatesize=para.tigmode.tplatesize;
		}
		
		
		if(read_tjointtype!=para.tigmode.tjointtype)								//joint
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),para.tigmode.tjointtype);  	  
		read_tjointtype=para.tigmode.tjointtype;
		}
	}	
}

void check_eeprom_values(void)
{
	unsigned long int eeprom_location;
	
	if(weldmode!='P' && weldmode!='G' && weldmode!='M' && weldmode!='T')
	{
		weldmode='P';
		EEPROM_Erase_Write_for_SaveRecall(0,'P');  
		prev_weldmode=weldmode;	
		cDefaultProgfg = 1;
		para.pmigmode.arclength = 40;
		
			
	}
/*	
	if(weldmode='G');
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*0;   //For Mig mode
	
		if( dia!=zeropteight && dia!=oneptzero && dia!=onepttwo && dia!=oneptsix)
		{
			mat=ms;
			para.migmode.gmaterial=mat;
			
			dia=onepttwo;
		    para.migmode.gdiameter=dia;
		    
		    gas=arco2;
			para.migmode.ggas=gas;
			
			EEPROMstruct_mig.dia=dia;
			EEPROMstruct_mig.gas=gas;
			
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_mig.EEPROM_struct_u);
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.migmode.gmaterial);  		 //9 material 
			read_gmaterial=para.migmode.gmaterial;
		}
		if(gas!=arco2  && gas!=co2 && gas!=ar &&  gas!=aro2)
		{
			mat=ms;
			para.migmode.gmaterial=mat;
			
			dia=onepttwo;
		    para.migmode.gdiameter=dia;
		    
		    gas=arco2;
			para.migmode.ggas=gas;
			
			EEPROMstruct_mig.dia=dia;
			EEPROMstruct_mig.gas=gas;
			
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_mig.EEPROM_struct_u);			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.migmode.gmaterial);  		 //9 material 
			read_gmaterial=para.migmode.gmaterial;
		}		
				
		
		if(para.migmode.preflow<mini.migmode.preflow || para.migmode.preflow>maxi.migmode.preflow)
		{
			para.migmode.preflow=mini.migmode.preflow;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),para.pmigmode.preflow);  		 			//2 preflow
			read_gpreflow=para.migmode.preflow;   
		}
		
		if(para.migmode.setcurrent<mini.migmode.setcurrent || para.migmode.setcurrent>maxi.migmode.setcurrent)  
		{
			para.migmode.setcurrent=mini.migmode.setcurrent;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+3*2),para.migmode.setcurrent);  	 			//3 set current
			read_gsetcurrent=para.migmode.setcurrent;
		}
		
		if(para.migmode.setvoltage<mini.migmode.setvoltage || para.migmode.setvoltage>maxi.migmode.setvoltage)
		{
			para.migmode.setvoltage=mini.migmode.setvoltage;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),para.migmode.setvoltage);   	 			//4 set vtg
			read_gsetvoltage=para.migmode.setvoltage;
		}			
		
		if(para.migmode.cratercurrent<mini.migmode.cratercurrent || para.migmode.cratercurrent>maxi.migmode.cratercurrent)
		{
			para.migmode.cratercurrent=mini.migmode.cratercurrent;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+5*2),para.migmode.cratercurrent);  //5 crater curr
			read_gcratercurrent=para.migmode.cratercurrent;	
		}
		
		if(para.migmode.cratervoltage<mini.migmode.cratervoltage || para.migmode.cratervoltage>maxi.migmode.cratervoltage)
		{
			para.migmode.cratervoltage=mini.migmode.cratervoltage;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+6*2),para.migmode.cratervoltage);  //6 crater vtg
			read_gcratervoltage=para.migmode.cratervoltage;	
		}	
		
		if(para.migmode.burnback<mini.migmode.burnback || para.migmode.burnback>maxi.migmode.burnback)
		{
			para.migmode.burnback=mini.migmode.burnback;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+7*2),para.migmode.burnback);  	 //7 burn back
			read_gburnback=para.migmode.burnback;	
		}
		
		if(para.migmode.setwspeed<mini.migmode.setwspeed || para.migmode.setwspeed>maxi.migmode.setwspeed)
		{
			para.migmode.setwspeed=mini.migmode.setwspeed;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+8*2),para.migmode.setwspeed);  	 //8 set wirespeed
			read_gsetwspeed=para.migmode.setwspeed;	
		}	
		
		if(para.migmode.gmaterial!=ms && para.migmode.gmaterial!=ss && para.migmode.gmaterial!=alu )
		{
		    mat=ms;
			para.migmode.gmaterial=mat;
			
			dia=onepttwo;
		    para.migmode.gdiameter=dia;
		    
		    gas=arco2;
			para.migmode.ggas=gas;
			
			EEPROMstruct_mig.dia=dia;
			EEPROMstruct_mig.gas=gas;
			
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_mig.EEPROM_struct_u);			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.migmode.gmaterial);  		 //9 material 
			read_gmaterial=para.migmode.gmaterial;
	
		}
		
		if(para.migmode.postflow<mini.migmode.postflow || para.migmode.postflow>maxi.migmode.postflow)
		{
			para.migmode.postflow=mini.migmode.postflow;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+10*2),para.migmode.postflow);  	 //10 postflow 
			read_gpostflow=para.migmode.postflow;
		}	
		
		if(para.migmode.inductance<mini.migmode.inductance || para.migmode.inductance>maxi.migmode.inductance)
		{
			para.migmode.inductance=mini.migmode.inductance;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+11*2),para.migmode.inductance);  	 //11 inductance=G/arc_length=P
			read_inductance=para.migmode.inductance;
		}		
		
		if(para.creepspeedrate<mini.creepspeedrate || para.creepspeedrate>maxi.creepspeedrate)
		{
			para.creepspeedrate=mini.creepspeedrate;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+12*2),para.creepspeedrate);  		 //12 creep speed  twinpulsefreq
			prevcreepspeedrate=para.creepspeedrate;	
		}
		
		if(para.migmode.thickness<mini.migmode.thickness || para.migmode.thickness>maxi.migmode.thickness)
		{		
			para.migmode.thickness=mini.migmode.thickness;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+16*2),para.migmode.thickness);  	 //16 thickness 
			read_gthickness=para.migmode.thickness;			 
		}	
	}
	*/
	
	if(weldmode=='G')
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*0;   //For Mig mode
	
		if( 0)//dia!=zeropteight && dia!=oneptzero && dia!=onepttwo && dia!=oneptsix) //if diameter read from eeprom is wrong
		{
			mat=ms;
			para.migmode.gmaterial=mat;
			
			dia=zeropteight;
		    para.migmode.gdiameter=dia;
		    
		    gas=arco2;
			para.migmode.ggas=gas;
			
			EEPROMstruct_mig.dia=dia;
			EEPROMstruct_mig.gas=gas;
			
			EEPROM_struct_mig.EEPROM_struct_u=EEPROM_Read_for_SaveRecall((eeprom_location+1*2));     			//1 eeprom structure	
			
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.migmode.gmaterial);  		 //9 material 
			read_gmaterial=para.migmode.gmaterial;
		}
		if(0)//gas!=arco2  && gas!=co2 && gas!=ar &&  gas!=aro2)
		{
			mat=ms;
			para.migmode.gmaterial=mat;
			
			dia=oneptzero;
		    para.migmode.gdiameter=dia;
		    
		    gas=arco2;
			para.migmode.ggas=gas;
			
			EEPROMstruct_mig.dia=dia;
			EEPROMstruct_mig.gas=gas;
			
			EEPROM_struct_mig.EEPROM_struct_u=EEPROM_Read_for_SaveRecall((eeprom_location+1*2));     			//1 eeprom structure
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.migmode.gmaterial);  		 //9 material 
			read_gmaterial=para.migmode.gmaterial;
		}		
				
		
		if(para.migmode.preflow<mini.migmode.preflow || para.migmode.preflow>maxi.migmode.preflow)
		{
			para.migmode.preflow=mini.migmode.preflow;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),para.pmigmode.preflow);  		 			//2 preflow
			read_gpreflow=para.migmode.preflow;   
		}
		
		if(para.migmode.setcurrent<mini.migmode.setcurrent || para.migmode.setcurrent>maxi.migmode.setcurrent)  
		{
			para.migmode.setcurrent=mini.migmode.setcurrent;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+3*2),para.migmode.setcurrent);  	 			//3 set current
			read_gsetcurrent=para.migmode.setcurrent;
		}
		
		if(para.migmode.setvoltage<mini.migmode.setvoltage || para.migmode.setvoltage>maxi.migmode.setvoltage)
		{
			para.migmode.setvoltage=mini.migmode.setvoltage;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),para.migmode.setvoltage);   	 			//4 set vtg
			read_gsetvoltage=para.migmode.setvoltage;
		}			
		
		if(para.migmode.craterspeed<mini.migmode.craterspeed || para.migmode.craterspeed>maxi.migmode.craterspeed)
		{
			para.migmode.craterspeed=mini.migmode.craterspeed;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+5*2),para.migmode.craterspeed);  //5 crater curr
			read_gcratercurrent=para.migmode.craterspeed;	
		}
		
		if(para.migmode.cratervoltage<mini.migmode.cratervoltage || para.migmode.cratervoltage>maxi.migmode.cratervoltage)
		{
			para.migmode.cratervoltage=mini.migmode.cratervoltage;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+6*2),para.migmode.cratervoltage);  //6 crater vtg
			read_gcratervoltage=para.migmode.cratervoltage;	
		}	
		
		if(para.migmode.burnback<mini.migmode.burnback || para.migmode.burnback>maxi.migmode.burnback)
		{
			para.migmode.burnback=mini.migmode.burnback;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+7*2),para.migmode.burnback);  	 //7 burn back
			read_gburnback=para.migmode.burnback;	
		}
		
		if(para.migmode.setwspeed<mini.migmode.setwspeed || para.migmode.setwspeed>maxi.migmode.setwspeed)
		{
			para.migmode.setwspeed=mini.migmode.setwspeed;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+8*2),para.migmode.setwspeed);  	 //8 set wirespeed
			read_gsetwspeed=para.migmode.setwspeed;	
		}	
		
		if(0)//para.migmode.gmaterial!=ms && para.migmode.gmaterial!=ss && para.migmode.gmaterial!=alu && para.migmode.gmaterial!=msfcaw
//		&& para.migmode.gmaterial!=ssfcaw )
		{
//			para.migmode.gmaterial=ms;
//			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.migmode.gmaterial);  	 //9 material 	
//			read_gmaterial=para.migmode.gmaterial;
//			mat=para.migmode.gmaterial;
		}
		
		if(para.migmode.postflow<mini.migmode.postflow || para.migmode.postflow>maxi.migmode.postflow)
		{
			para.migmode.postflow=mini.migmode.postflow;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+10*2),para.migmode.postflow);  	 //10 postflow 
			read_gpostflow=para.migmode.postflow;
		}	
		
		if(para.migmode.inductance<mini.migmode.inductance || para.migmode.inductance>maxi.migmode.inductance)
		{
			para.migmode.inductance=mini.migmode.inductance;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+11*2),para.migmode.inductance);  	 //11 inductance=G/arc_length=P
			read_inductance=para.migmode.inductance;
		}		
		
		//if(para.creepspeedrate<mini.creepspeedrate || para.migmode.inductance>maxi.creepspeedrate)
		if(para.creepspeedrate<mini.creepspeedrate || para.creepspeedrate>maxi.creepspeedrate)
		{
			para.creepspeedrate=35;//mini.creepspeedrate;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+12*2),para.creepspeedrate);  		 //12 creep speed  twinpulsefreq
			prevcreepspeedrate=para.creepspeedrate;	
		}
		
		if(pmig_auto0_man1!=1 && pmig_auto0_man1!=0)
		{		
		pmig_auto0_man1=0;
		prev_pmig_auto0_man1=pmig_auto0_man1;	
		read_pmig_auto0_man1=prev_pmig_auto0_man1;
		}	
	}
	
	
	
	
	if(weldmode=='P')
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*1;   //For P-Mig mode
	
		if(0)// pdia!=pzeropteight && pdia!=poneptzero && pdia!=ponepttwo && pdia!=poneptsix)
		{
				
			pmat=pms;
			para.pmigmode.pmaterial=pmat;
			
			pdia=pzeropteight;
		    para.pmigmode.pdiameter=pdia;
		    
		    pgas=parco2;
			para.pmigmode.pgas=pgas;
			
			para.pulseweldmode=0;  //single pulse mode
			
			EEPROMstruct_pmig.dia=pdia;
			EEPROMstruct_pmig.gas=pgas;
			EEPROMstruct_pmig.p_mode=0;
			
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_pmig.EEPROM_struct_u);		
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.pmigmode.pmaterial);  		 //9 material 
			read_pmaterial=para.pmigmode.pmaterial;
		}
		if(0)//pgas!=parco2  && pgas!=pco2 && pgas!=par &&  pgas!=paro2)
		{
			pmat=pms;
			para.pmigmode.pmaterial=pmat;
			
			pdia=poneptzero;
		    para.pmigmode.pdiameter=pdia;
		    
		    pgas=parco2;
			para.pmigmode.pgas=pgas;
			
			para.pulseweldmode=0;  //single pulse mode
			
			EEPROMstruct_pmig.dia=pdia;
			EEPROMstruct_pmig.gas=pgas;
			EEPROMstruct_pmig.p_mode=0;
			
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_pmig.EEPROM_struct_u);		
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.pmigmode.pmaterial);  		 //9 material 
			read_pmaterial=para.pmigmode.pmaterial;
		}		
		
		/*if((para.pulseweldmode!= 0) || (para.pulseweldmode != 1))		
		{
			para.pulseweldmode=0;  //single pulse mode		
		}*/
		
		if(para.pmigmode.preflow<mini.pmigmode.preflow || para.pmigmode.preflow>maxi.pmigmode.preflow)
		{
			para.pmigmode.preflow=mini.pmigmode.preflow;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),para.pmigmode.preflow);  		 			//2 preflow
			read_ppreflow=para.pmigmode.preflow;   
		}
		
		if(para.pmigmode.setcurrent<mini.pmigmode.setcurrent || para.pmigmode.setcurrent>maxi.pmigmode.setcurrent)  
		{
			para.pmigmode.setcurrent=mini.pmigmode.setcurrent;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+3*2),para.pmigmode.setcurrent);  	 			//3 set current
			read_psetcurrent=para.pmigmode.setcurrent;
		}
		
		if(para.pmigmode.setvoltage<mini.pmigmode.setvoltage || para.pmigmode.setvoltage>maxi.pmigmode.setvoltage)
		{
			para.pmigmode.setvoltage=mini.pmigmode.setvoltage;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),para.pmigmode.setvoltage);   	 			//4 set vtg
			read_psetvoltage=para.pmigmode.setvoltage;
		}			
		
		if(para.pmigmode.craterspeed<mini.pmigmode.craterspeed || para.pmigmode.craterspeed>maxi.pmigmode.craterspeed)
		{
			para.pmigmode.craterspeed=mini.pmigmode.craterspeed;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+5*2),para.pmigmode.craterspeed);  //5 crater curr
			read_pcratercurrent=para.pmigmode.craterspeed;	
		}
		
		if(para.pmigmode.cratervoltage<mini.pmigmode.cratervoltage || para.pmigmode.cratervoltage>maxi.pmigmode.cratervoltage)
		{
			para.pmigmode.cratervoltage=mini.pmigmode.cratervoltage;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+6*2),para.pmigmode.cratervoltage);  //6 crater vtg
			read_pcratervoltage=para.pmigmode.cratervoltage;	
		}	
		
		if(para.pmigmode.burnback<mini.pmigmode.burnback || para.pmigmode.burnback>maxi.pmigmode.burnback)
		{
			para.pmigmode.burnback=mini.pmigmode.burnback;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+7*2),para.pmigmode.burnback);  	 //7 burn back
			read_pburnback=para.pmigmode.burnback;	
		}
		
		if(para.pmigmode.setwspeed<mini.pmigmode.setwspeed || para.pmigmode.setwspeed>maxi.pmigmode.setwspeed)
		{
			para.pmigmode.setwspeed=mini.pmigmode.setwspeed;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+8*2),para.pmigmode.setwspeed);  	 //8 set wirespeed
			read_psetwspeed=para.pmigmode.setwspeed;	
		}	
	
		if(0)/*para.pmigmode.pmaterial!=pms      && para.pmigmode.pmaterial!=p71t1 && para.pmigmode.pmaterial!=p180r 
						&& para.pmigmode.pmaterial!=pss18    && para.pmigmode.pmaterial!=pss19 && para.pmigmode.pmaterial!=palu4043
						&& para.pmigmode.pmaterial!=palu5356 && para.pmigmode.pmaterial!=palu99 && para.pmigmode.pmaterial!= ss_fcaw1 &&
						 para.pmigmode.pmaterial!=lafcaw && para.pmigmode.pmaterial!=hffcaw
		  )*/
		{
//			pmat=pms;
//			para.pmigmode.pmaterial=pmat;
			
//			pdia=ponepttwo;
//		    para.pmigmode.pdiameter=pdia;
		    
//		    pgas=parco2;
//			para.pmigmode.pgas=pgas;
			
//			para.pulseweldmode=0;  //single pulse mode
			
//			EEPROMstruct_pmig.dia=pdia;
//			EEPROMstruct_pmig.gas=pgas;
//			EEPROMstruct_pmig.p_mode=0;
			
//			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_pmig.EEPROM_struct_u);		
//			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.pmigmode.pmaterial);  		 //9 material 
//			read_pmaterial=para.pmigmode.pmaterial;
		}
		
		if(para.pmigmode.postflow<mini.pmigmode.postflow || para.pmigmode.postflow>maxi.pmigmode.postflow)
		{
			para.pmigmode.postflow=mini.pmigmode.postflow;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+10*2),para.pmigmode.postflow);  	 //10 postflow 
			read_ppostflow=para.pmigmode.postflow;
		}	
		
		if(para.pmigmode.arclength<mini.pmigmode.arclength || para.pmigmode.arclength>maxi.pmigmode.arclength)
		{
			para.pmigmode.arclength=40;//mini.pmigmode.arclength;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+11*2),para.pmigmode.arclength);  	 //11 inductance=G/arc_length=P
			read_parclength=para.pmigmode.arclength;
		}		
		
		if(para.pcreepspeedrate<mini.pcreepspeedrate || para.pcreepspeedrate>maxi.pcreepspeedrate)
		{
			para.pcreepspeedrate=35;//mini.pcreepspeedrate;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+12*2),para.pcreepspeedrate);  		 //12 creep speed  twinpulsefreq
//			prev_pcreepspeedrate=para.pcreepspeedrate;	
			read_pcreepspeedrate=para.pcreepspeedrate;	//3/09/2019
		}
		
		if(para.twinpulsefreq<mini.twinpulsefreq || para.twinpulsefreq>maxi.twinpulsefreq)
		{
			para.twinpulsefreq= mini.twinpulsefreq;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+13*2),para.twinpulsefreq);  		
			read_ptwinpulsefreq=para.twinpulsefreq;								
		}

		if(para.twinpulseduty<mini.twinpulseduty || para.twinpulseduty>maxi.twinpulseduty)
		{
			para.twinpulseduty= 50;//mini.twinpulseduty; // default 50
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+14*2),para.twinpulseduty);  		
			read_ptwinpulseduty=para.twinpulseduty;								
		}				
		if(para.twinpulseratio<mini.twinpulseratio || para.twinpulseratio>maxi.twinpulseratio)
		{
			para.twinpulseratio= 100;//mini.twinpulseratio; // default 100%
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+15*2),para.twinpulseratio);  		
			read_ptwinpulseratio=para.twinpulseratio;
			twinpulseratio=para.twinpulseratio;								
		}		
					
		if(pmig_auto0_man1!=1 && pmig_auto0_man1!=0)
		{		
		pmig_auto0_man1=0;
		prev_pmig_auto0_man1=pmig_auto0_man1;		 
		}
		
		
		ans=iPProgramNo;//newpmmmatgas[pdia][pmat][pgas];
	    program_number=ans;	
	    if(0)//ans==0)
	    {
			pmat=pms;
			para.pmigmode.pmaterial=pmat;
			
			pdia=poneptsix;
		    para.pmigmode.pdiameter=pdia;
		    
		    pgas=parco2;
			para.pmigmode.pgas=pgas;
			
			para.pulseweldmode=0;  //single pulse mode
			
			EEPROMstruct_pmig.dia=pdia;
			EEPROMstruct_pmig.gas=pgas;
			EEPROMstruct_pmig.p_mode=0;
			
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_pmig.EEPROM_struct_u);		
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+9*2),para.pmigmode.pmaterial);  		 //9 material 
			read_pmaterial=para.pmigmode.pmaterial;    
		} 
	}
	
	
	
	if(weldmode=='M')  //MMA MODE
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*2;  
		
		
		
		if(para.mmamode.setcurrent<mini.mmamode.setcurrent || para.mmamode.setcurrent>maxi.mmamode.setcurrent)
		{
			para.mmamode.setcurrent=mini.mmamode.setcurrent;
		} //1
		
		if(para.mmamode.arcforce<mini.mmamode.arcforce || para.mmamode.arcforce>maxi.mmamode.arcforce)
		{
			para.mmamode.arcforce=mini.mmamode.arcforce;
		}//2
		
		if(para.mmamode.mmaterial<mini.mmamode.mmaterial || para.mmamode.mmaterial>maxi.mmamode.mmaterial)
		{
			para.mmamode.mmaterial=mini.mmamode.mmaterial;
		}//3
		
		if(para.mmamode.melectrodesize<mini.mmamode.melectrodesize || para.mmamode.melectrodesize>maxi.mmamode.melectrodesize)
		{
			para.mmamode.melectrodesize=mini.mmamode.melectrodesize;
		}//4
		
		if(para.mmamode.melectrotype<mini.mmamode.melectrotype || para.mmamode.melectrotype>maxi.mmamode.melectrotype)
		{
			para.mmamode.melectrotype=mini.mmamode.melectrotype;
		}//5

		if(iHotstartper<0 || iHotstartper>100)
		{
			iHotstartper=20;
		}//6
			
		mmat=para.mmamode.mmaterial;
		mdia=para.mmamode.melectrodesize;
		melectrode=para.mmamode.melectrotype;	
			
	}
	else if(weldmode=='T')  //TIG MODE
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*3;  
		
		
		
		if(para.tigmode.setcurrent<mini.tigmode.setcurrent || para.tigmode.setcurrent>maxi.tigmode.setcurrent)
		{
			para.tigmode.setcurrent=mini.tigmode.setcurrent;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),para.tigmode.setcurrent); //set current
			read_tsetcurrent=para.tigmode.setcurrent;
		} //1
		
		
		if(para.tigmode.tmaterial<mini.tigmode.tmaterial || para.tigmode.tmaterial>maxi.tigmode.tmaterial)
		{
			para.tigmode.tmaterial=mini.tigmode.tmaterial;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),para.tigmode.tmaterial);  //material 
			read_tmaterial=para.tigmode.tmaterial;
		}//2
		
		if(para.tigmode.tplatesize<mini.tigmode.tplatesize || para.tigmode.tplatesize>maxi.tigmode.tplatesize)
		{
			para.tigmode.tplatesize=mini.tigmode.tplatesize;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+3*2),para.tigmode.tplatesize);  	  
			read_tplatesize=para.tigmode.tplatesize;
		}//3
		
		if(para.tigmode.tjointtype<mini.tigmode.tjointtype || para.tigmode.tjointtype>maxi.tigmode.tjointtype)
		{
			para.tigmode.tjointtype=mini.tigmode.tjointtype;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),para.tigmode.tjointtype);  	  
			read_tjointtype=para.tigmode.tjointtype;
		}//4
		
		tmat=para.tigmode.tmaterial;
		tdia=para.tigmode.tplatesize;
		tjoint=para.tigmode.tjointtype;	
		
	
	}		
}			

