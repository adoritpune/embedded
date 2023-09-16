#define EE_bSIZE                    0x1000               // 1024 Bytes  dsPIC30F6014A specific
#define EE_wSIZE                    0x0800               // 512 words  dsPIC30F6014A specific
#define EE_START_ADDR       0x7FF000             // dsPIC30F6014A specific
#define EE_END_ADDR           0x800000             // dsPIC30F6014A specific
#define EEPROM_ROW_SIZE    16                   // dsPIC30F EEPROM ROW siz


#define MMA_EE_START_ADDR	0x7FF010			//8384528 MMA ADDRESSS 7FF010--> FOR CURRENNT & NEXT 10 MEMORY ARRARY
#define TIG_EE_START_ADDR	0x7FF0C0			//8384704 TIG ADDRESS  7FF0C0--> FOR CURRENNT & NEXT 10 MEMORY ARRARY
#define MIG_EE_START_ADDR	0x7FF170			//8384880 MIG address
#define PMIG_EE_START_ADDR	0x7FF2D0			//8385232 PMIG ADDRESS


#define  MMA_EEPROM_PAGE_SIZE 10
#define  TIG_EEPROM_PAGE_SIZE 10
#define  MIG_EEPROM_PAGE_SIZE  15
#define  PMIG_EEPROM_PAGE_SIZE 15


unsigned int EEPROM_Read(unsigned long int EE_Addr)
{
   	unsigned long int Act_EE_Addr = EE_Addr + EE_START_ADDR;
   	unsigned int EE_Data = 0xFFFF;
   	unsigned int SAV_TBLPAG = TBLPAG;
   	
   	Act_EE_Addr=EE_Addr;
   	   	 	
    TBLPAG = Act_EE_Addr >> 16;
    __asm__("TBLRDL [%1], %0" : /* outputs */ "=r"(EE_Data) : /* inputs */ "r"(Act_EE_Addr));
   	TBLPAG = SAV_TBLPAG;
   	return EE_Data;
}

unsigned int EEPROM_Erase_Write1(unsigned int EE_Addr,unsigned int EE_Data,unsigned char cMemoryLocation)
{
	return 0;
}	
	 

void write_mode_mem(unsigned char cMemoryLocation)
{
	unsigned int i=0;
		
	memoryzone='G';	

	if(memoryzone=='G')
	{     		
	//	if(read_gpreflow!=para.migmode.preflow) //preflow
		{
		EEPROM_Erase_Write1(0*2,para.migmode.preflow,cMemoryLocation);
		read_gpreflow=para.migmode.preflow;
		}
		
	//	if(read_gsetwspeed!=para.migmode.setwspeed) 		//wire speed
		{
		EEPROM_Erase_Write1(1*2,para.migmode.setwspeed,cMemoryLocation);
		read_gsetwspeed=para.migmode.setwspeed;
		}
		
	//	if(read_gsetvoltage!=para.migmode.setvoltage)  		//setvtg
		{
		EEPROM_Erase_Write1(2*2,para.migmode.setvoltage,cMemoryLocation);
		read_gsetvoltage=para.migmode.setvoltage;
		}
		
	//	if(read_gcratercurrent!=para.migmode.cratercurrent) //crater current
		{
		EEPROM_Erase_Write1(3*2,para.migmode.cratercurrent,cMemoryLocation);
		read_gcratercurrent=para.migmode.cratercurrent;
		} 
		
	//	if(read_gcratervoltag!=para.migmode.cratervoltage)	//crater voltage
		{
		EEPROM_Erase_Write1(4*2,para.migmode.cratervoltage,cMemoryLocation);
		read_gcratervoltag=para.migmode.cratervoltage;
		}
		
	//	if(read_gburnback!=para.migmode.burnback)			//burnbaack
		{
		EEPROM_Erase_Write1(5*2,para.migmode.burnback,cMemoryLocation);
		read_gburnback=para.migmode.burnback;
		}
		
	//	if(read_gpostflow!=para.migmode.postflow)			//postflow
		{
		EEPROM_Erase_Write1(6*2,para.migmode.postflow,cMemoryLocation);
		read_gpostflow=para.migmode.postflow;
		}
		
	//	if(read_gmaterial!=para.migmode.gmaterial)			//gmaterial
		{
		EEPROM_Erase_Write1(7*2,para.migmode.gmaterial,cMemoryLocation);
		read_gmaterial=para.migmode.gmaterial;
		}
		
	//	if(read_gdiameter!=para.migmode.gdiameter)			//gdiameter
		{
		EEPROM_Erase_Write1(8*2,para.migmode.gdiameter,cMemoryLocation);
		read_gdiameter=para.migmode.gdiameter;
		}
		
	//	if(read_ggas!=para.migmode.ggas)                    //ggas
		{
		EEPROM_Erase_Write1(9*2,para.migmode.ggas,cMemoryLocation);
		read_ggas=para.migmode.ggas;
		}		
		
//		if(read_inductance!=para.migmode.inductance)
		{
		EEPROM_Erase_Write1(10*2,para.migmode.inductance,cMemoryLocation);	
		read_inductance=para.migmode.inductance;
		}
	}	
	else if(memoryzone=='P')
	{
		Act_EE_Addr = PMIG_EE_START_ADDR+cMemoryLocation*PMIG_EEPROM_PAGE_SIZE*2;;
   	}
	
	/*
		for(i=0;i<17;i++)
		{
			EE_Addr=(i*2);
			EE_Data=parau.arrayu[i];
			if(EE_Data != prevmemarr[i])
			{
				EEPROM_Erase_Write(EE_Addr,EE_Data);
			}
		}
		for(i=0;i<17;i++)
		{
			prevmemarr[i]=parau.arrayu[i];
		}
		*/
}


void recall_mode_mem(unsigned char cMemoryLocation)
{
		unsigned long int lTemp_adress=0;		
				          //= 100+0*150*2 == 100  == for current memory
				          //= 100+1*150*2 == 250  == for 1St     memory
				lTemp_adress = (long)(MIG_EE_START_ADDR+cMemoryLocation*MIG_EEPROM_PAGE_SIZE*2);;
					
			
				para.migmode.preflow=EEPROM_Read(lTemp_adress+0*2);
				if(para.migmode.preflow>=100)
				para.migmode.preflow=0;
				read_gpreflow=para.migmode.preflow;
				
				para.migmode.setwspeed=EEPROM_Read(lTemp_adress+1*2);
				if(para.migmode.setwspeed>=200)
				para.migmode.setwspeed=0;
				read_gsetwspeed=para.migmode.setwspeed;
				
				para.migmode.setvoltage=EEPROM_Read(lTemp_adress+2*2);
				if(para.migmode.setvoltage>=440)
				para.migmode.setvoltage=160;
				read_gsetvoltage=para.migmode.setvoltage;
								
				
				para.migmode.cratercurrent=EEPROM_Read(lTemp_adress+3*2);
				if(para.migmode.cratercurrent>=500)
				para.migmode.cratercurrent=50;
				read_gcratercurrent=para.migmode.cratercurrent;
				
				para.migmode.cratervoltage=EEPROM_Read(lTemp_adress+4*2);
				if(para.migmode.cratervoltage>=100)
				para.migmode.cratervoltage=0;
				read_gcratervoltage=para.migmode.cratervoltage;
						
				para.migmode.burnback=EEPROM_Read(lTemp_adress+5*2);
				if(para.migmode.burnback>=100)
				para.migmode.burnback=0;
				read_gburnback=para.migmode.burnback;
				
				para.migmode.postflow=EEPROM_Read(lTemp_adress+6*2);
				if(para.migmode.postflow>=100)
				para.migmode.postflow=0;
				read_gpostflow=para.migmode.postflow;
				
				para.migmode.thickness=EEPROM_Read(lTemp_adress+7*2);
				if(para.migmode.thickness>2)
				para.migmode.thickness=0;					//DEFAULT MS MATERIAL
				read_gthickness=para.migmode.thickness;
				
				para.migmode.gmaterial=EEPROM_Read(lTemp_adress+8*2);
				if(para.migmode.gmaterial>2)
				para.migmode.gmaterial=0;					//DEFAULT MS MATERIAL
				read_gmaterial=para.migmode.gmaterial;
				
				
				para.migmode.gdiameter=EEPROM_Read(lTemp_adress+9*2);
				if(para.migmode.gdiameter>3)
				para.migmode.gdiameter=0;					//DEFAULT 0.8 WIRE
				read_gdiameter=para.migmode.gdiameter;
				
								
				para.migmode.ggas=EEPROM_Read(lTemp_adress+10*2);
				if(para.migmode.ggas>3)
				para.migmode.ggas=1;						//DEFAULT CO2 GAS
				read_ggas=para.migmode.ggas;
				
				mat=para.migmode.gmaterial;
				dia=para.migmode.gdiameter;
				gas=para.migmode.ggas;
				{
					if(mat==ms)
						lcdput(7,0,matms);
					else if(mat==ss)
						lcdput(7,0,matss);
					else if(mat==alu)
						lcdput(7,0,matalu);
				}
				{
					if(dia==zeropteight)
						lcdput(7,48,diazeropteight);
					else if(dia==oneptzero)
						lcdput(7,48,diaoneptzero);
					else if(dia==onepttwo)
						lcdput(7,48,diaonepttwo);
					else if(dia==oneptsix)
						lcdput(7,48,diaoneptsix);
				}
				{
					if(gas==arco2)
						lcdput(7,90,gasarco2);
					else if(gas==co2)
						lcdput(7,90,gasco2);
					else if(gas==ar)
						lcdput(7,90,gasar);	
					else if(gas==aro2)
						lcdput(7,90,gasaro2);	
				}
						
				para.migmode.inductance=EEPROM_Read(lTemp_adress+11*2);
				if(para.migmode.inductance>=40) //20
				para.migmode.inductance=0;
				read_inductance=para.migmode.inductance;
				
				
				intkp=80-(para.migmode.inductance);//*2);  //20+
            	intki=2+(para.migmode.inductance/8);   //1+    //4+(para.migmode.inductance/4);
            	intkd=10;//5;  //para.migmode.inductance/8;//6;
           					
				pidParams1.Kp1=intkp;
				pidParams1.Ki1=intki;
				pidParams1.Kd1=intkd;
				transmitonf=1;	
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
   		Act_EE_Addr = (long)EE_Addr + MIG_EE_START_ADDR;
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

