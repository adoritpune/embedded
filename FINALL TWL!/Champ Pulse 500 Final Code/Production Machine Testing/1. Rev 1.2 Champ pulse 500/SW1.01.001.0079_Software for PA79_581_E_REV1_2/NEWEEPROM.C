#define EE_bSIZE  			0x1000				//0x0400            	// 1024 Bytes  dsPIC30F5011 specific
#define EE_wSIZE  			0x0800				//0x0200            	// 512 words  dsPIC30F5011 specific
#define EE_START_ADDR  		0x7FF000            // 0x7FFC00       		// dsPIC30F5011 specific
#define EE_END_ADDR  		0x800000
#define EEPROM_ROW_SIZE 	16           		// dsPIC30F EEPROM ROW size

unsigned int EEPROM_Read(unsigned int EE_Addr)
{
   	unsigned long int Act_EE_Addr = EE_Addr + EE_START_ADDR;
   	unsigned int EE_Data = 0xFFFF;
   	unsigned int SAV_TBLPAG = TBLPAG;
    TBLPAG = Act_EE_Addr >> 16;
    __asm__("TBLRDL [%1], %0" : /* outputs */ "=r"(EE_Data) : /* inputs */ "r"(Act_EE_Addr));
   	TBLPAG = SAV_TBLPAG;
   	return EE_Data;
}

unsigned int EEPROM_Erase_Write(unsigned int EE_Addr,unsigned int EE_Data)
{
   	unsigned int EE_Stat = 0;
   	unsigned long int Act_EE_Addr = EE_Addr + EE_START_ADDR;
   	unsigned int SAV_TBLPAG = TBLPAG;

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
