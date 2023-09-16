#define EE_bSIZE  			0x0400            	// 1024 Bytes  dsPIC30F5011 specific
#define EE_wSIZE  			0x0200            	// 512 words  dsPIC30F5011 specific
#define EE_START_ADDR  		0x7FFC00       		// dsPIC30F5011 specific
#define EE_END_ADDR  		0x800000
#define EEPROM_ROW_SIZE 	16           		// dsPIC30F EEPROM ROW size

#define MIG_PARA_MAX_SIZE 10

#define CURRENT_PARAMTR_SAVING_OFFSET 200

unsigned int EEPROM_Read(unsigned int EE_Addr)
{
   	unsigned long int Act_EE_Addr = EE_Addr + EE_START_ADDR; //got to the adress BYTE BY BYTE
   	unsigned int EE_Data = 0xFFFF;                           //move 0XFFFF
   	unsigned int SAV_TBLPAG = TBLPAG;                        //USE TO HOLD hold the upper 8 bits of a program memory address during table read and write operations.
                                                             //Table instructions are used to transfer data between program memory space and data memory space.
    TBLPAG = Act_EE_Addr >> 16;                              //left shift 16 times The TBLPAG register is loaded with the 8 MSbs of the EEPROM address.
                                                             // single word write getting table page number value
    __asm__("TBLRDL [%1], %0" : /* outputs */ "=r"(EE_Data) : /* inputs */ "r"(Act_EE_Addr));//READING ONE BYTE AT A TIME
   	TBLPAG = SAV_TBLPAG;                                   
   	return EE_Data;
}

unsigned int EEPROM_Erase_Write(unsigned int EE_Addr,unsigned int EE_Data) //PASS DATA AND ADRESS RELATED TO THE DATA
{
   	unsigned int EE_Stat = 0;
   	unsigned long int Act_EE_Addr = EE_Addr + EE_START_ADDR; // GO TO THE SPECIFIC MEMORY
   	unsigned int SAV_TBLPAG = TBLPAG;

   	if(NVMCONbits.WRERR == 0) 					//Privious NV write error detected 
                                                //1 = A write operation is prematurely terminated (any MCLR or WDT Reset during programming operation)0 = The write operation completed successfully
   	{
		NVMADRU = (Act_EE_Addr >> 16) & 0x7F;   //NVMADRU register loaded with contents of TBLPAG register during last table-write instruction

		NVMADR = Act_EE_Addr & 0xFFFF;
      
        NVMCONbits.WREN = set;             		//Enable an earse and program operation SET=1
        NVMCONbits.PROGOP = 0x44;           	//Word Erase command //Erase 1 data word from data EEPROM
              
		__builtin_write_NVM();       			//Unlock, iniate erase/write & wait till complete  available in C30 User manual
		while(NVMCONbits.WR == 1);   			//Wait for operation complete //Write cycle is complete      
                  
		if(EEPROM_Read(EE_Addr) == 0xFFFF)      //SEND ADDRESS TO READ FUNCTION
       	{
           	TBLPAG = Act_EE_Addr >> 16;
           	__asm__("TBLWTL %1, [%0]" : /*no outputs*/ : /*inputs*/ "r"(Act_EE_Addr), "r"(EE_Data));
            NVMCONbits.WREN = set;             	//Enable an program operation
            NVMCONbits.PROGOP = 0x04;           //EE Word Write // Program 1 data word into data EEPROM
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




void write_mode_mem(unsigned char cMemoryLocation)
{
	unsigned long int eeprom_location;
 
	if(process_flag==MIGMODE)  //@ mig welding mode
	{
		
		eeprom_location=CURRENT_PARAMTR_SAVING_OFFSET+(cMemoryLocation-1)+MIG_PARA_MAX_SIZE*2; //@calculate the fixed offset in eeprom for different mem location
		
	//	EEPROMstruct_mig.Twot0_fourt1=Torchmode;
	

		EEPROM_Erase_Write((eeprom_location+1*2),EEPROM_struct_mig.EEPROM_struct_u);  //1 eeprom structure

		EEPROM_Erase_Write((eeprom_location+2*2),rset_wirespeed);  	 //2 set current/wirespeed
		EEPROM_Erase_Write((eeprom_location+4*2),rsetvoltage); //210); //   	 	//3 set vtg
	}
	
	if(process_flag==MMAMODE)
	{
		EEPROM_Erase_Write((eeprom_location+1*2),EEPROM_struct_mig.EEPROM_struct_u);  //1 eeprom structure

		EEPROM_Erase_Write((eeprom_location+2*2),setcurrent);  	 //2 set current
		
	}	
}


void recall_mode_mem(unsigned char cMemoryLocation)
{
	unsigned int eeprom_location;
	
   eeprom_location=CURRENT_PARAMTR_SAVING_OFFSET+(cMemoryLocation-1)+MIG_PARA_MAX_SIZE*2; //@calculate the fixed offset in eeprom for different mem location
	
	if(1) //(cMemoryLocation == EEPROM_Read((eeprom_location+17*2)))
	{        

	if(process_flag==MIGMODE) 
	{ 
	    EEPROM_struct_mig.EEPROM_struct_u=EEPROM_Read((eeprom_location+1*2));  	//1 eeprom structure

		rset_wirespeed			 	=EEPROM_Read((eeprom_location+2*2));  	//2 set current/wirespeed
		rsetvoltage				 	=EEPROM_Read((eeprom_location+4*2));   	//3 set vtg
		
		communication.setwspeed = rset_wirespeed;
		set_v = rsetvoltage; 
		communication.Lo_setvoltage = set_v & 0xFF;
		communication.Hi_setvoltage = (set_v >> 8);		
		
	//	wfstatus.twotfourtmode1=EEPROMstruct_mig.Twot0_fourt1;
	}
	
	} 

	if(process_flag==MMAMODE) 
	{ 
	    EEPROM_struct_mig.EEPROM_struct_u=EEPROM_Read((eeprom_location+1*2));  	//1 eeprom structure

		setcurrent				 	=EEPROM_Read((eeprom_location+2*2));  	//2 set current
	
	} 
}
void ReadLastWeldData(void)
{
	
//	EEPROM_Erase_Write(10*2,222);  //writing rsetvoltage to memory 
//	EEPROM_Erase_Write(12*2,33);  //writing rset_wirespeed to memory 
	
	rset_wirespeed = EEPROM_Read(14*2);
	rsetvoltage = EEPROM_Read(10*2);
	communication.setwspeed = rset_wirespeed;
	set_v = rsetvoltage; 
	communication.Lo_setvoltage = set_v & 0xFF;
	communication.Hi_setvoltage = (set_v >> 8);	
	cPowerOnblockrxfg = 1;
	iPowerOnCntr = 4000;
	
	if((set_v < MIN_SETVOLTAGE) || (set_v > MAX_SETVOLTAGE) )
	{
		rsetvoltage=220;
		EEPROM_Erase_Write(10*2,rsetvoltage);  //writing rsetvoltage to memory 
		rsetvoltage = EEPROM_Read(10*2);
		set_v = rsetvoltage; 
		communication.Lo_setvoltage = set_v & 0xFF;
		communication.Hi_setvoltage = (set_v >> 8);			
	}
	if((rset_wirespeed < MIN_WIRESPEED) || (rset_wirespeed > MAX_WIRESPEED-10) )//&& (cEditfg == 0) && (blockrxfg = 0))
	{
		rset_wirespeed=40;
		EEPROM_Erase_Write(14*2,rset_wirespeed);  //writing rset_wirespeed to memory 
		rset_wirespeed = EEPROM_Read(14*2);
		communication.setwspeed = rset_wirespeed;				
	} 		
	
}	

void WriteLastWeldData(void)
{
	EEPROM_Erase_Write(10*2,rsetvoltage);  //writing rsetvoltage to memory 
	EEPROM_Erase_Write(14*2,communication.setwspeed);  //writing rset_wirespeed to memory 	
}	