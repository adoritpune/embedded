#define EE_bSIZE           0x1000               // 1024 Bytes  dsPIC30F6014A specific
#define EE_wSIZE           0x0800               // 512 words  dsPIC30F6014A specific
#define EE_START_ADDR      0x7FF000             // dsPIC30F6014A specific
#define EE_END_ADDR        0x800000             // dsPIC30F6014A specific
#define EEPROM_ROW_SIZE    16                   // dsPIC30F EEPROM ROW siz

#define MMA_EE_START_ADDR	 0x7FF010			//MMA ADDRESSS 7FF010--> FOR CURRENNT & NEXT 10 MEMORY ARRARY
#define TIG_EE_START_ADDR	 0x7FF0C0			//TIG ADDRESS  7FF0C0--> FOR CURRENNT & NEXT 10 MEMORY ARRARY
#define MIG_EE_START_ADDR	 0x7FF000			//MIG address
#define PMIG_EE_START_ADDR	 0x7FF2D0			//PMIG ADDRESS

#define MIG_PARA_MAX_SIZE 18//16

#define CURRENT_PARAMTR_SAVING_OFFSET 220

void write_mode_mem(unsigned char cMemoryLocation)
{
	unsigned long int eeprom_location;
 
	if(weldmode=='G')  //@ mig welding mode
	{
		eeprom_location=CURRENT_PARAMTR_SAVING_OFFSET+(cMemoryLocation-1)*MIG_PARA_MAX_SIZE*2; //@calculate the fixed offset in eeprom for different mem location

		EEPROMstruct_mig.p_mode=weldmode;
		
		EEPROMstruct_mig.Twot0_fourt1=Type.twot;
	
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+0*2),weldmode);  					 //0 weld Mode
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_mig.EEPROM_struct_u);  //1 eeprom structure
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),mig_preflow);  		 //2 preflow
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+7*2),mig_burnback);  		 //7 burn back
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+10*2),mig_postflow);  		 //10 postflow 		
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+12*2),mig_creepspeedrate);  		 //12 creep speed  twinpulsefreq		
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+14*2),mig_creepspeedtime);  		 //14 creep speed		 
	}

	else if((weldmode=='T'))// || (weldmode=='M'))  //@ tig welding mode
	{
		eeprom_location=CURRENT_PARAMTR_SAVING_OFFSET+(cMemoryLocation-1)*MIG_PARA_MAX_SIZE*2;
	
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+0*2),weldmode);  					 //0 weld Mode
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_tig.EEPROM_struct_ut);  //1 eeprom structure          
	}	
	
}
	
void recall_mode_mem(unsigned char cMemoryLocation)
{
	unsigned int eeprom_location;
	
	/*Calculate EEPROM memory address*/
	eeprom_location=CURRENT_PARAMTR_SAVING_OFFSET+(cMemoryLocation-1)*MIG_PARA_MAX_SIZE*2; //@calculate the fixed offset in eeprom for different mem location
	
	if (cMemoryLocation == EEPROM_Read_for_SaveRecall((eeprom_location+17*2)))
	{        
	/*Read Mode in which last power off save operation has been done*/
	weldmode=EEPROM_Read_for_SaveRecall((eeprom_location+0*2));  					 //0 weld Mode
	
	 /*Read MIG mode parameter*/
	if(weldmode=='G') 
	{ 
	    EEPROM_struct_mig.EEPROM_struct_u=EEPROM_Read_for_SaveRecall((eeprom_location+1*2));  	//1 eeprom structure
		mig_preflow			=EEPROM_Read_for_SaveRecall((eeprom_location+2*2));  	//2 preflow
		mig_burnback		=EEPROM_Read_for_SaveRecall((eeprom_location+7*2));  	//7 burn back
	    mig_postflow		=EEPROM_Read_for_SaveRecall((eeprom_location+10*2));  	//10 postflow 
		mig_creepspeedrate	=EEPROM_Read_for_SaveRecall((eeprom_location+12*2));  	//12 creep speed  twinpulsefreq
		mig_creepspeedtime	=EEPROM_Read_for_SaveRecall((eeprom_location+14*2));  	//12 creep speed 
		weldmode=EEPROMstruct_mig.p_mode;
		
		//wfstatus.twotfourtmode1=EEPROMstruct_mig.Twot0_fourt1;
		Type.twot=EEPROMstruct_mig.Twot0_fourt1;
		Type.fourt= Type.twot^1; 

	} 
/*
	else if(weldmode == 'M')
	{
		EEPROM_struct_tig.EEPROM_struct_ut=EEPROM_Read_for_SaveRecall((eeprom_location+1*2));
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),mma_vrd_time);  		 //12 creep speed  twinpulsefreq	
	}
*/
	else if((weldmode=='T'))//|| (weldmode=='M'))  
	{		
		EEPROM_struct_tig.EEPROM_struct_ut=EEPROM_Read_for_SaveRecall((eeprom_location+1*2));  	//1 eeprom structure
	}
	check_eeprom_values();
	}		
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
	arcontime.sec=EEPROM_Read(194);
	
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
	if(arcontime.sec==0xffff || arcontime.sec >60)
	{
		arcontime.sec=0;
		EEPROM_Erase_Write(194,arcontime.sec);
	}
/********************************Arc On Time**************************/

/********************************Machine Serial Number start**************************/
	first_digits=EEPROM_Read(180);
	second_digits=EEPROM_Read(182);
	third_digits=EEPROM_Read(184);
	fourth_digits=EEPROM_Read(186);
	
	if(first_digits==0xffff || first_digits > 99)
	{
		first_digits=0;
        EEPROM_Erase_Write((180),first_digits);
    }
    
    if(second_digits==0xffff || second_digits > 99)
	{
		second_digits=0;
        EEPROM_Erase_Write((182),second_digits);
    }
    
    if(third_digits==0xffff || third_digits > 99)
	{
		third_digits=0;
        EEPROM_Erase_Write((184),third_digits);
    }
    
    if(fourth_digits==0xffff || fourth_digits > 99)
	{
		fourth_digits=0;
        EEPROM_Erase_Write((186),fourth_digits);
    }
/********************************Machine Serial Number End**************************/

	if(weldmode=='G')    
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*0;												//@Offset for MIG ParaMeter 
        EEPROM_struct_mig.EEPROM_struct_u=EEPROM_Read_for_SaveRecall((eeprom_location+1*2));     //1 eeprom structure
		mig_preflow			=EEPROM_Read_for_SaveRecall((eeprom_location+2*2));  	//2 preflow
		mig_burnback		=EEPROM_Read_for_SaveRecall((eeprom_location+7*2));  	//7 burn back
	    mig_postflow		=EEPROM_Read_for_SaveRecall((eeprom_location+10*2));  	//10 postflow 

		mig_creepspeedrate	=EEPROM_Read_for_SaveRecall((eeprom_location+12*2));  	//12 creep speed  twinpulsefreq
		mig_creepspeedtime	=EEPROM_Read_for_SaveRecall((eeprom_location+14*2));  	//12 creep speed
		Type.twot=EEPROMstruct_mig.Twot0_fourt1;
		Type.fourt= Type.twot^1;
		
		prev_eeprom_mig_struct=EEPROM_struct_mig.EEPROM_struct_u;
		read_gpreflow		=mig_preflow;   				//2
		read_gburnback		=mig_burnback;				//7
		read_gpostflow		=mig_postflow;				//10
		prevcreepspeedrate	=mig_creepspeedrate;				//12
	 	read_gcreepspeedtime=mig_creepspeedtime;
										
	}

	else if(weldmode=='M')
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*2;

	    //EEPROM_struct_tig.EEPROM_struct_ut=EEPROM_Read_for_SaveRecall((eeprom_location+1*2)); 	 //1 eeprom structure       
		
		//prev_weldmode=weldmode;
		//prev_eeprom_tig_struct=EEPROM_struct_tig.EEPROM_struct_ut;

		//mma_vrd_time = EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),mma_vrd_time);  		 //12 creep speed  twinpulsefreq
		//read_mma_vrd_time=mma_vrd_time;											
	}

	else if((weldmode=='T'))// || (weldmode=='M'))
	{
	    eeprom_location=MIG_PARA_MAX_SIZE*2*3;
	    EEPROM_struct_tig.EEPROM_struct_ut=EEPROM_Read_for_SaveRecall((eeprom_location+1*2)); 	 //1 eeprom structure       
		
		prev_weldmode=weldmode;
		prev_eeprom_tig_struct=EEPROM_struct_tig.EEPROM_struct_ut;
	}	
	
}


void write_current_status(void)
{
	unsigned long int eeprom_location;
	
	iWeldcount++;
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
		
		if(read_gpreflow!=mig_preflow)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),mig_preflow);  		 //2 preflow
		read_gpreflow=mig_preflow;
		}
		
		
		if(read_gburnback!=mig_burnback)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+7*2),mig_burnback);  		 //7 burn back
		read_gburnback=mig_burnback;
		}
		
		
		if(read_gpostflow!=mig_postflow)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+10*2),mig_postflow);  		 //10 postflow 
		read_gpostflow=mig_postflow;
		}
		
		
		if(prevcreepspeedrate!=mig_creepspeedrate)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+12*2),mig_creepspeedrate);  		 //12 creep speed  twinpulsefreq
		prevcreepspeedrate=mig_creepspeedrate;
		}

		if(read_gcreepspeedtime!=mig_creepspeedtime)
		{
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+14*2),mig_creepspeedtime);  		 //12 creep speed  twinpulsefreq
		read_gcreepspeedtime=mig_creepspeedtime;
		}
	
	}

	else if(weldmode=='M')
	{
		
		if(prev_weldmode!=weldmode)
		{
			EEPROM_Erase_Write_for_SaveRecall(0,weldmode);  					 //0 weld Mode
			prev_weldmode=weldmode;
		}

		eeprom_location=MIG_PARA_MAX_SIZE*2*2;

		if(0)//read_mma_vrd_time!=mma_vrd_time)
		{
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),mma_vrd_time);  		 //12 creep speed  twinpulsefreq
			read_mma_vrd_time=mma_vrd_time;
		}
		
		
	}	

 	else if((weldmode=='T'))// || (weldmode=='M'))
 	{
	 
	 	eeprom_location=MIG_PARA_MAX_SIZE*2*3;


	 	if(prev_weldmode!=weldmode)
		{
			EEPROM_Erase_Write_for_SaveRecall(0,weldmode);  					 //0 weld Mode
			prev_weldmode=weldmode;
		}	 
				
		if(prev_eeprom_tig_struct!=EEPROM_struct_tig.EEPROM_struct_ut)
	    {
		EEPROM_Erase_Write_for_SaveRecall((eeprom_location+1*2),EEPROM_struct_tig.EEPROM_struct_ut);  //1 eeprom structure
		prev_eeprom_tig_struct=EEPROM_struct_tig.EEPROM_struct_ut;
		}
		
	}	
}


void check_eeprom_values(void)
{
	unsigned long int eeprom_location;
	
	if(weldmode!='G' && weldmode!='M' && weldmode!='T')
	{
		weldmode='G';
		EEPROM_Erase_Write_for_SaveRecall(0,'G');  
		prev_weldmode=weldmode;		
	}
	
	if(weldmode=='G')
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*0;   //For Mig mode
		
		if(mig_preflow <= 0 || mig_preflow >= 10)
		{
			mig_preflow=0;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+2*2),mig_preflow);  		 			//2 preflow
			read_gpreflow=mig_preflow;   
		}
		
		
		if(mig_burnback <= 0 || mig_burnback>=200)
		{
			mig_burnback=2;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+7*2),mig_burnback);  	 //7 burn back
			read_gburnback=mig_burnback;	
		}
		
		
		if(mig_postflow<=0 || mig_postflow>=10)
		{
			mig_postflow=0;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+10*2),mig_postflow);  	 //10 postflow 
			read_gpostflow=mig_postflow;
		}			
		
		if(mig_creepspeedrate<=0 || mig_creepspeedrate>=100)
		{
			mig_creepspeedrate=30;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+12*2),mig_creepspeedrate);  		 //12 creep speed  twinpulsefreq
			prevcreepspeedrate=mig_creepspeedrate;	
		}


		if(mig_creepspeedtime<=0 || mig_creepspeedtime>=100)
		{
			mig_creepspeedtime=1;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+14*2),mig_creepspeedtime);  		 //12 creep speed  twinpulsefreq
			read_gcreepspeedtime=mig_creepspeedtime;
		}
			
	}
		
	else if(weldmode=='M')  //MMA MODE
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*2;

		if(0)//mma_vrd_time<=0 || mma_vrd_time>=500)
		{
			mma_vrd_time=18;
			EEPROM_Erase_Write_for_SaveRecall((eeprom_location+4*2),mma_vrd_time);  		 //12 creep speed  twinpulsefreq
			read_mma_vrd_time=mma_vrd_time;
		}  				
	}

	else if(weldmode=='T') //|| (weldmode=='M')) 
	{
		eeprom_location=MIG_PARA_MAX_SIZE*2*3;  
	}		
}			

