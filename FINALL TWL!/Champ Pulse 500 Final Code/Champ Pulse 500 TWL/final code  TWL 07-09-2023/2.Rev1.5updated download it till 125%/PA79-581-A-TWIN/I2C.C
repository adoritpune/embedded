#include "p30f6014A.h"
//#include "FUNCTION.C"
//#include "VARIABLE.C"
unsigned char byteread(void);
void bytewrite(unsigned char data);
void NOACK(void);
void ACK(void);
void startBitGen(void);
void stopBitGen(void);
unsigned int I2C_ReadInt(unsigned int address);
void SendACK(void);

void I2C_init(void)
{
	//initialise port pins
	SCLIO = 0;										// clock output
	SDAIO = 0;										// data output					 	
}

void I2C_Write(unsigned int addr,unsigned int data)
{
	unsigned int addrh ,addrl;
	unsigned int datah,datal;
			
	datah = data;										//data output
	datah >>= 8;
	datal = (data & 0x00FF);
	addrh = addr;
	addrh >>= 8;
	addrl = (addr & 0x00FF);
 
/*******************START BIT********************************/	
	startBitGen();
/******************SENDING BYTE******************************/	
	bytewrite(0xA0);
	bytewrite(addrh);
	bytewrite(addrl);
	bytewrite(datah);
	bytewrite(datal);			
/*******************STOP BIT*********************************/
	stopBitGen();	
	count_6ms = 0;
	while(count_6ms <= 10)
	{
	}	
}

void I2C_Write1(unsigned int addr, unsigned char byteno)
{
	unsigned int addrh ,addrl;
	//unsigned int datah,datal;
	unsigned char i;
	
	for(i = 0; i < byteno; ++i)
	{
		addrh = addr;
		addrh >>= 8;
		addrl = (addr & 0x00FF);
	/*******************START BIT********************************/	
		startBitGen();
	/******************SENDING BYTE******************************/	
		bytewrite(0xA0);
		bytewrite(addrh);
		bytewrite(addrl);
	
		bytewrite(cE2p[i]);	
	
	//	bytewrite(datah);
	//	bytewrite(datal);		
	/*******************STOP BIT*********************************/
		stopBitGen();	
		count_6ms = 0;
		addr++;
		while(count_6ms <= 6)
		{
		}		
	}		
		
}


unsigned int I2C_Read1(unsigned int addr)
{
	unsigned int addrh ,addrl;	
	unsigned char i,tem[2],abc;
	
	
	//for(i=0;i<7;++i)
	{
		addrh = addr;
		addrh >>= 8;
		addrl = (addr & 0x00FF);
				
		startBitGen();
		bytewrite(0xA0);
		bytewrite(addrh);
		bytewrite(addrl);	
		startBitGen();
		bytewrite(0xA1);
		abc = byteread();
		NOACK();	
		stopBitGen();	
		//addr++;
	}
	//i=tem[1];
	return abc;
}
void bytewrite(unsigned char data)
{
	unsigned char temp,i;
	temp = data;	
	SDAIO = 0;		
	for(i=0;i<8;i++)
	{						
		temp = data;
		temp = temp << i;		
		SDA = (temp & 0x80) ? 1:0;
		delayI2C();	
			
		SCL = 1;
		delayI2C();					
		SCL = 0;
		delayI2C();		
	}		
/*	for(icnt=0;icnt<8;icnt++)
	{

		if(temp & 0x80)
			SDA = 1;
		else
			SDA = 0;
		SCL = 1;
		delayI2C();	
		SCL = 0;
		delayI2C();	
		temp = temp << 1;
	}
*/
	ACK();		
			   
}

void startBitGen()
{
	SDAIO = 0;
		
	SDA = 1;
	delayI2C();
	SCL = 1;
	delayI2C();
	SDA = 0;
	delayI2C();		
	SCL = 0;
	delayI2C();
	
	SDAIO = 0;
	
}
void stopBitGen()
{
	SDAIO = 0;
	
	SDA = 0;
	delayI2C();	
	SCL = 1;
	delayI2C();
	SDA = 1;
	delayI2C();
	
	SDAIO = 0;
}

void ACK()
{
	unsigned int cTimeout;
	SDAIO = 0;
	SDA = 1;
	delayI2C();	
	SCL = 1;	
	delayI2C();	
	cTimeout = 0;
	SDAIO = 1;	
	delayI2C();				
	while(SDA == 1)
	{
		cTimeout++;
		if(cTimeout >= 500)
		{
		//	SDA = 0;
		}
	}
	SDAIO = 0;
	SCL = 0;
	delayI2C();		
}
void NOACK()
{
	SDAIO = 1;
		
	SDA = 1;
	delayI2C();	
	SCL =1;
	delayI2C();
	SCL = 0;	
	delayI2C();
	SDA = 1;	
	delayI2C();		
}

void clock_high()
{
	SCL = 1;
	delayI2C();
}
void clock_low()
{
	SCL = 0;
	delayI2C();
}
void delayI2C()
{
	int i,j;
	j = 0;	
	for(i=0;i<100;i++)
	{
//		Nop(); 
		j++;
	}
}

unsigned int I2C_Read(unsigned int address)
{
	unsigned char addrh,addrl,datal,datah;
	unsigned int iReaddata;
	SCLIO = 0;
	iReaddata = datal = datah = addrh = addrl = 0;
	addrh = (address >> 8);
	addrl = (address & 0x00FF);
/*******************START BIT********************************/	

	startBitGen();
	bytewrite(0xA0);
	bytewrite(addrh);
	bytewrite(addrl);	
	startBitGen();
	bytewrite(0xA1);
	datah = byteread();
	NOACK();	
	stopBitGen();
	
	address++;
	
	addrh = (address >> 8);
	addrl = (address & 0x00FF);	
	startBitGen();
	bytewrite(0xA0);
	bytewrite(addrh);
	bytewrite(addrl);	
	startBitGen();
	bytewrite(0xA1);
	datal = byteread();
	NOACK();	
	stopBitGen();	
		
	iReaddata = datah;
	iReaddata = (iReaddata << 8);
	iReaddata = (iReaddata & 0xFF00);
	iReaddata |= datal ;	
	return iReaddata;
		
}

unsigned char byteread()
{
	unsigned char itemp,data,cnt;
	data = 0;
	SDAIO = 1;	
	delayI2C();	
	for(cnt=0;cnt<8;cnt++)
	{		
		SCL = 1;
		delayI2C();	
		data <<= 1;
		data = (data | SDA);		
//		if(SDA == 1)		
//		data |= 0x01;//|= (SDA & 0x01);
//		else 
//		data |= 0x00;	
//		data = (data << 1);
		  
		SCL = 0;
		delayI2C();		
	}
	SDAIO = 0;	
	return data;	
}


//----------------------------------------------------------------------------------
unsigned int I2C_ReadInt(unsigned int address)
{
	unsigned char addrh,addrl,datal,datah;
	unsigned int iReaddata,ctempread[5];
	
	SCLIO = 0;
	iReaddata = datal = datah = addrh = addrl = 0;
	
	addrh = (address >> 8);
	addrl = (address & 0x00FF);
/*******************START BIT********************************/	
	datah = I2C_Read(address);
	datal = I2C_Read(address+1);	
	
/*
	startBitGen();
	bytewrite(0xA0);
	bytewrite(addrh);
	bytewrite(addrl);	
	startBitGen();
	bytewrite(0xA1);
	datah=byteread();
	SendACK();
	datal = byteread();
	NOACK();	
	stopBitGen();
*/	
	iReaddata = datah;
	iReaddata = (iReaddata << 8);
	iReaddata = (iReaddata & 0xFF00);
	iReaddata |= datal ;
	
	return iReaddata;
}
//----------------------------------------------------------------------------------
void SendACK(void)
{
	SDAIO = 0;	
//	delayI2C();	
//	SCL = 1;
//	delayI2C();	
//	SDA = 1;
//	delayI2C();	
	SDA = 0;
	delayI2C();
	SCL = 1;
	delayI2C();	
	SDAIO = 0;		
}
//----------------------------------------------------------------------------------
/*void Check_E2p(void)
{	
	unsigned int i,j;
	if(ADOR_DATA != I2C_Read(ADOR_WR))
	{
	// it mean E2P is new so clean the e2p and write some defaults
	
		for(iWrAddr = 0; iWrAddr < 0xFFFF; )
		{		
//			for(j = 0; j < 10 ; j++)
//			{
				E2P_Write(iWrAddr);			
				++iWrAddr;
//			}
			count_6ms = 0;
			while(count_6ms <= 6)
			{
			}
			//datafordebugonlcd1(iWrAddr);			
		}
		
		I2C_Write(ADOR_WR,ADOR_DATA); 
	}
	else{
//			iData = I2C_Read(iWrAddr);
			//datafordebugonlcd(12345);		
	}
}*/
//-----------------------------------------------------------------------------
void E2P_Write(unsigned int addr)
{
	unsigned int addrh ,addrl;
	addrh = addr;
	addrh >>= 8;
	addrl = (addr & 0x00FF);
/*******************START BIT********************************/	
	startBitGen();
/******************SENDING ADDR & BYTE***********************/	
	bytewrite(0xA0);
	bytewrite(addrh);
	bytewrite(addrl);
	bytewrite(0);
	bytewrite(0);		
/*******************STOP BIT*********************************/
	stopBitGen();		
}

//-----------------------------------------------------------------------------

void write_in_external_memory(unsigned int iLocation_no)
{
	unsigned int i,temp,volt,amp;
	unsigned char cThickness;
//----------------------------------------------------------------------------------------------------------------------------
	isaveaddr = (iLocation_no -1)* E2POFFSET;
	cE2p[0] = iLocation_no;
	cE2p[1] = iLocation_no >> 8;
	iPno = iLocation_no;


	I2C_Write1(isaveaddr,2);
	
//-----------------WELD_MODE----------------------------------------------------------------------------------------
	cE2p[0] = 'P';
	I2C_Write1(isaveaddr+WELD_MODE, 1);
				 
//----------------------Material Write---------------------------------------------------------------------------------------
	cE2p[0]= 'K';
	cE2p[1]= 'T';
	cE2p[2]= 'M';
	cE2p[3]= 'X';
	cE2p[4]= 'X';
	cE2p[5]= 'X';
	cE2p[6]= 'X';
	I2C_Write1(isaveaddr+PROG_NAME, 7);
	
//----------------------Gas Dia Write-----------------------------------------------------------------------------------------	
	cE2p[0] = 0x12;
/*
0000	Co2		0000  0.8			
0001	ArCo2	0001  1.0	
0010	ArO2	0010  1.2	
0011	Ar		0011  1.6	
*/	
	I2C_Write1(isaveaddr+GAS_DIA,1);
	
//----------------------SYN Data --------------------------------------------------------------------------------------
		
	for(i = 0;i < 22; ++i)
	{	
		volt = newpautobasevtg[iLocation_no][i+2];;
		amp = newpautocurrent[iLocation_no][i+2];
		cThickness = newpautothickness[iLocation_no][i+2];
		cE2p[0]= (volt & 0x00ff);
		temp  = (volt & 0x0f00);
		cE2p[1]= (temp >> 8);
		temp = amp;
		temp = temp << 4;
		cE2p[1] |= temp;
		temp = amp;
		temp = temp >> 4;
		cE2p[2]= ((temp) & 0x00ff);	
		cE2p[3]= cThickness;		

			
		I2C_Write1(isaveaddr+SYN_DATA, 4);	
		isaveaddr = isaveaddr + 4;
	}
	
//-----------------Pulse Parameter----------------------------------------------------------------------------------------

	isaveaddr = (iLocation_no -1)* E2POFFSET;	
		
	for(i = 0; i < 10; ++i)
	{
		temp=newpulsemigparameter[iLocation_no][i];
//		temp = 46 +i;
		cE2p[0] = temp;
		cE2p[1] = temp >> 8;		
		I2C_Write1(isaveaddr+PMIG_PARA,2);	
		isaveaddr = isaveaddr + 2;			
	}		
	
//----------------------------------------------------------------------------------------------------------------------------	

}

void update_mat_dia_gas()
{
	int i;
	for(i=0;i<8;i++)
	{
		cMatarray[i] = cMatTxt[iMatChk][i];
	}
	
	switch(iThickChk)
	{	
		case 0:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x00;
					break;
				case 1:
					cGasDiaupdate = 0x10;
					break;
				case 2:
					cGasDiaupdate = 0x20;
					break;
				case 3:
					cGasDiaupdate = 0x30;
					break;
				//default															
					
			}
			break;
		case 1:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x01;
					break;
				case 1:
					cGasDiaupdate = 0x11;
					break;
				case 2:
					cGasDiaupdate = 0x21;
					break;
				case 3:
					cGasDiaupdate = 0x31;
					break;
				//default														
					
			}
			break;
		case 2:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x02;
					break;
				case 1:
					cGasDiaupdate = 0x12;
					break;
				case 2:
					cGasDiaupdate = 0x22;
					break;
				case 3:
					cGasDiaupdate = 0x32;
					break;
				//default
			}
			break;
		case 3:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x03;
					break;
				case 1:
					cGasDiaupdate = 0x13;
					break;
				case 2:
					cGasDiaupdate = 0x23;
					break;
				case 3:
					cGasDiaupdate = 0x33;
					break;
				//default
			}
			break;									
		
	}
}

void Write_in_EEPROM(unsigned int iPrgNo,unsigned int iaddress)
{
	unsigned int i,temp,volt,amp;
	unsigned char cThickness;
//-----------------------------------------------------------------------------------------------------------------
	isaveaddr = (iaddress -1)* E2POFFSET;
	cE2p[0] = iPrgNo;//iaddress;//iPrgNo;
	cE2p[1] = iPrgNo >> 8;//iaddress >> 8 ;//iPrgNo >> 8;
	iPno = iPrgNo;

	I2C_Write1(isaveaddr,2);
	
//-----------------WELD_MODE----------------------------------------------------------------------------------------
	cE2p[0] = cWeldmode;
	I2C_Write1(isaveaddr+WELD_MODE, 1);
				 
//----------------------Material Write------------------------------------------------------------------------------
	cE2p[0]= cMatarray[0];
	cE2p[1]= cMatarray[1];
	cE2p[2]= cMatarray[2];
	cE2p[3]= cMatarray[3];
	cE2p[4]= cMatarray[4];
	cE2p[5]= cMatarray[5];
	cE2p[6]= cMatarray[6];
	I2C_Write1(isaveaddr+PROG_NAME, 7);
	
//----------------------Gas Dia Write-----------------------------------------------------------------------------------
	cE2p[0] = cGasDiaupdate;
/*
0000	Co2		0000  0.8			
0001	ArCo2	0001  1.0	
0010	ArO2	0010  1.2	
0011	Ar		0011  1.6	
*/	
	I2C_Write1(isaveaddr+GAS_DIA,1);
	
//----------------------SYN Data --------------------------------------------------------------------------------------
		
	for(i = 0;i < 27; ++i)
	{	
		volt = newpautobasevtg[iPrgNo][i];;
		amp = newpautocurrent[iPrgNo][i];
		cThickness = newpautothickness[iPrgNo][i];
		cE2p[0]= (volt & 0x00ff);
		temp  = (volt & 0x0f00);
		cE2p[1]= (temp >> 8);
		temp = amp;
		temp = temp << 4;
		cE2p[1] |= temp;
		temp = amp;
		temp = temp >> 4;
		cE2p[2]= ((temp) & 0x00ff);	
		cE2p[3]= cThickness;		

			
		I2C_Write1(isaveaddr+SYN_DATA, 4);	
		isaveaddr = isaveaddr + 4;
	}
	
	
	
//-----------------Pulse Parameter------------------------------------------------------------------------------

	isaveaddr = (iaddress -1)* E2POFFSET;	
		
	for(i = 0; i < 10; ++i)
	{
		temp=newpulsemigparameter[iPrgNo][i];
//		temp = 46 +i;
		cE2p[0] = temp;
		cE2p[1] = temp >> 8;		
		I2C_Write1(isaveaddr+PMIG_PARA,2);	
		isaveaddr = isaveaddr + 2;			
	}		
//-----------------FACTORS-------------------------------------------------------------------------------------------------
		
		isaveaddr = (iaddress -1)* E2POFFSET;
		
			temp=factors[iPrgNo][0];//iPulseFreqFact;
			cE2p[0] = temp;
			cE2p[1] = temp >> 8;		
			I2C_Write1(isaveaddr+FACTORS,2);	
			isaveaddr = isaveaddr + 2;	
			
			temp=factors[iPrgNo][1];//iPulsetmfactor;
			cE2p[0] = temp;
			cE2p[1] = temp >> 8;		
			I2C_Write1(isaveaddr+FACTORS,2);	
			isaveaddr = isaveaddr + 2;	
			
			temp=factors[iPrgNo][2];//iPulsecurfactor;
			cE2p[0] = temp;
			cE2p[1] = temp >> 8;		
			I2C_Write1(isaveaddr+FACTORS,2);	
			isaveaddr = isaveaddr + 2;									

			temp=factors[iPrgNo][3];//iUSBsfConst;
			cE2p[0] = temp%10;
			temp = temp / 10;
			cE2p[1] = temp%10;
			temp = temp / 10;			
			cE2p[2] = temp%10;
			//itempo2 = cE2p[2]*100 + cE2p[1]*10 + cE2p[0];
			I2C_Write1(isaveaddr+FACTORS,3);	
	
//------------------------------------------------------------------------------------------------------------------	
}

void Clear_EEPROM_Prog_Num_Locations()
{
	unsigned int i,j;
	

	
	for(i=201;i<=300;i++)
	{
		isaveaddr = FRAME_GAP + (i -1)* mE2POFFSET;
		cE2p[0] = 0;
		cE2p[1] = 0;

		I2C_Write1(isaveaddr,2);		
		
	}
	for(i=301;i<=400;i++)
	{
		isaveaddr = FRAME_GAP + (i -1)* mE2POFFSET;
		cE2p[0] = 0;
		cE2p[1] = 0;

		I2C_Write1(isaveaddr,2);		
		
	}
	
	for(i=2;i<=200;i++)
	{
		isaveaddr = (i -1)* E2POFFSET;
		cE2p[0] = 0;
		cE2p[1] = 0;

		I2C_Write1(isaveaddr,2);		
		
	}		
	
	
}	



void Write_Mig_root_Data_in_EEPROM (unsigned int iPrgNo,unsigned int iaddress)
{
	unsigned int i,temp,volt,amp,iTempaddr;
	unsigned char cThickness;
//-----------------------------------------------------------------------------------------------------------------
	isaveaddr = FRAME_GAP + (iaddress -1)* mE2POFFSET;
	iTempaddr = isaveaddr;
	cE2p[0] = iaddress;//iPrgNo;
	cE2p[1] = iaddress >> 8;//iPrgNo >> 8;
	iPno = iPrgNo;
	//datafordebugonlcd(isaveaddr,55);
	I2C_Write1(isaveaddr,2);
	
//-----------------WELD_MODE----------------------------------------------------------------------------------------	
	cE2p[0] = cWeldmode;
	I2C_Write1(isaveaddr+mWELD_MODE, 1);
				 
//----------------------Material Write------------------------------------------------------------------------------
	cE2p[0]= cMatarray[0];
	cE2p[1]= cMatarray[1];
	cE2p[2]= cMatarray[2];
	cE2p[3]= cMatarray[3];
	cE2p[4]= cMatarray[4];
	cE2p[5]= cMatarray[5];
	cE2p[6]= cMatarray[6];
	I2C_Write1(isaveaddr+mPROG_NAME, 7);
	
//----------------------Gas Dia Write-------------------------------------------------------------------------------
	cE2p[0] = cGasDiaupdate;
/*
0000	Co2		0000  0.8			
0001	ArCo2	0001  1.0	
0010	ArO2	0010  1.2	
0011	Ar		0011  1.6	
*/	
	I2C_Write1(isaveaddr+mGAS_DIA,1);
	
//----------------------SYN Data ------------------------------------------------------------------------------------

	for(i = 0;i < 27; ++i)
	{	
		volt = rootautovoltage[iPrgNo][i];;
		amp = rootautocurrent[iPrgNo][i];
		cThickness = autothickness[iPrgNo][i];
		cE2p[0]= (volt & 0x00ff);
		temp  = (volt & 0x0f00);
		cE2p[1]= (temp >> 8);
		temp = amp;
		temp = temp << 4;
		cE2p[1] |= temp;
		temp = amp;
		temp = temp >> 4;
		cE2p[2]= ((temp) & 0x00ff);	
		cE2p[3]= cThickness;		

			
		I2C_Write1(isaveaddr+mSYN_DATA, 4);	
		isaveaddr = isaveaddr + 4;
	}
	
	cE2p[0] = (max_Pwire_speed[iPrgNo] & 0x00ff);
	cE2p[1] = (max_Pwire_speed[iPrgNo] & 0xff00);
		
	I2C_Write1(iTempaddr+MAX_WS, 2);	
	
}



void Write_Mig_Data_in_EEPROM (unsigned int iPrgNo,unsigned int iaddress)
{
	unsigned int i,temp,volt,amp,iTempaddr;
	unsigned char cThickness;
//-----------------------------------------------------------------------------------------------------------------
	isaveaddr = FRAME_GAP + (iaddress -1)* mE2POFFSET;
	iTempaddr = isaveaddr;
	cE2p[0] = iaddress;//iPrgNo;
	cE2p[1] = iaddress >> 8;//iPrgNo >> 8;
	iPno = iPrgNo;
	//datafordebugonlcd(isaveaddr,55);
	I2C_Write1(isaveaddr,2);
	
//-----------------WELD_MODE----------------------------------------------------------------------------------------	
	cE2p[0] = cWeldmode;
	I2C_Write1(isaveaddr+mWELD_MODE, 1);
				 
//----------------------Material Write------------------------------------------------------------------------------
	cE2p[0]= cMatarray[0];
	cE2p[1]= cMatarray[1];
	cE2p[2]= cMatarray[2];
	cE2p[3]= cMatarray[3];
	cE2p[4]= cMatarray[4];
	cE2p[5]= cMatarray[5];
	cE2p[6]= cMatarray[6];
	I2C_Write1(isaveaddr+mPROG_NAME, 7);
	
//----------------------Gas Dia Write-------------------------------------------------------------------------------
	cE2p[0] = cGasDiaupdate;
/*
0000	Co2		0000  0.8			
0001	ArCo2	0001  1.0	
0010	ArO2	0010  1.2	
0011	Ar		0011  1.6	
*/	
	I2C_Write1(isaveaddr+mGAS_DIA,1);
	
//----------------------SYN Data ------------------------------------------------------------------------------------

	for(i = 0;i < 27; ++i)
	{	
		volt = autovoltage[iPrgNo][i];;
		amp = autocurrent[iPrgNo][i];
		cThickness = autothickness[iPrgNo][i];
		cE2p[0]= (volt & 0x00ff);
		temp  = (volt & 0x0f00);
		cE2p[1]= (temp >> 8);
		temp = amp;
		temp = temp << 4;
		cE2p[1] |= temp;
		temp = amp;
		temp = temp >> 4;
		cE2p[2]= ((temp) & 0x00ff);	
		cE2p[3]= cThickness;		

			
		I2C_Write1(isaveaddr+mSYN_DATA, 4);	
		isaveaddr = isaveaddr + 4;
	}
	
	cE2p[0] = (max_Pwire_speed[iPrgNo] & 0x00ff);
	cE2p[1] = (max_Pwire_speed[iPrgNo] & 0xff00);
		
	I2C_Write1(iTempaddr+MAX_WS, 2);	
	
}
void update_mig_mat_dia_gas_root()
{
	
		int i;
	for(i=0;i<8;i++)
	{
		  cMatarray[i] = cMatMigRootTxt[iMatChk][i];
		  
	}
	

	switch(iThickChk)
	{	
		case 0:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x00;
					break;
				case 1:
					cGasDiaupdate = 0x10;
					break;
				case 2:
					cGasDiaupdate = 0x20;
					break;
				case 3:
					cGasDiaupdate = 0x30;
					break;
				//default															
					
			}
			break;
		case 1:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x01;
					break;
				case 1:
					cGasDiaupdate = 0x11;
					break;
				case 2:
					cGasDiaupdate = 0x21;
					break;
				case 3:
					cGasDiaupdate = 0x31;
					break;
				//default														
					
			}
			break;
		case 2:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x02;
					break;
				case 1:
					cGasDiaupdate = 0x12;
					break;
				case 2:
					cGasDiaupdate = 0x22;
					break;
				case 3:
					cGasDiaupdate = 0x32;
					break;
				//default
			}
			break;
		case 3:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x03;
					break;
				case 1:
					cGasDiaupdate = 0x13;
					break;
				case 2:
					cGasDiaupdate = 0x23;
					break;
				case 3:
					cGasDiaupdate = 0x33;
					break;
				//default
			}
			break;	
			
	}

	
}	

void update_mig_mat_dia_gas()
{
	int i;
	for(i=0;i<8;i++)
	{
		  cMatarray[i] = cMatMigTxt[iMatChk][i];
		  
	}
	

	switch(iThickChk)
	{	
		case 0:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x00;
					break;
				case 1:
					cGasDiaupdate = 0x10;
					break;
				case 2:
					cGasDiaupdate = 0x20;
					break;
				case 3:
					cGasDiaupdate = 0x30;
					break;
				//default															
					
			}
			break;
		case 1:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x01;
					break;
				case 1:
					cGasDiaupdate = 0x11;
					break;
				case 2:
					cGasDiaupdate = 0x21;
					break;
				case 3:
					cGasDiaupdate = 0x31;
					break;
				//default														
					
			}
			break;
		case 2:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x02;
					break;
				case 1:
					cGasDiaupdate = 0x12;
					break;
				case 2:
					cGasDiaupdate = 0x22;
					break;
				case 3:
					cGasDiaupdate = 0x32;
					break;
				//default
			}
			break;
		case 3:
			switch(iGasChk)
			{
				case 0:
					cGasDiaupdate = 0x03;
					break;
				case 1:
					cGasDiaupdate = 0x13;
					break;
				case 2:
					cGasDiaupdate = 0x23;
					break;
				case 3:
					cGasDiaupdate = 0x33;
					break;
				//default
			}
			break;	
			
	}								

}

void Check_Updated_EEPROM()
{
	int i,j,itemp,iaddr,itempaddr,program;
	unsigned char ctemp[4];
	
	
	
	iaddr = (MATCH_LOCATION - 1)*E2POFFSET;
	itempaddr=iaddr;
	ctemp[0] =I2C_Read1(iaddr);	
	iaddr++;
	ctemp[1] =I2C_Read1(iaddr);
	program = ctemp[1];
	program = program << 8;
	program |= ctemp[0];  
	
	if(program == MATCH_DATA)
	{
		cMatchFoundfg = 1;
	}

	iaddr++;		
}

/*void read_array(unsigned int iLoc)
{
	int i,j,temp,temp2,temp3,iaddr,itempaddr,itmp,ia,ic;
	unsigned char ctemp[4];
	
	
	iaddr = (iLoc - 1)*E2POFFSET;
	itempaddr=iaddr;
	
//-----------------------------------------------------------------------------------------------------------------

	iaddr = itempaddr + SYN_DATA;


	for(j=0;j<4;j++)
	{
		ctemp[j]= I2C_Read1(iaddr);
		iaddr++;
	}
	
	iReadpara[0][i] =ctemp[0];
	temp = (ctemp[1] & 0x0f);
	temp = (temp<<8);				//voltage
	ia |= temp;
	
	temp = (ctemp[1] & 0xf0);
	temp = (temp >> 4);
	temp |= (ctemp[2]<<4);
	itempo1 =(temp);										//current
	
	ic = ctemp[3];									//thickness
	
	
	for(j=0;j<4;j++)
	{
		ctemp[j]= I2C_Read1(iaddr);
		iaddr++;
	}
	
	iReadpara[0][i] =ctemp[0];
	temp = (ctemp[1] & 0x0f);
	temp = (temp<<8);				//voltage
	ia |= temp;
	
	temp = (ctemp[1] & 0xf0);
	temp = (temp >> 4);
	temp |= (ctemp[2]<<4);
	itempo2 =(temp);										//current
	
	ic = ctemp[3];									//thickness	
		
	
			
}*/



void read_from_external_memory(unsigned int iLoc)
{
	int i,j,temp,iaddr,itempaddr;
	unsigned char ctemp[4];
	
	iaddr = (iLoc - 1)*E2POFFSET;
	itempaddr=iaddr;
	iReadPno =I2C_Read1(iaddr);											//program no
	iaddr++;
//------------------------------------------------------------------------------------------------------------		

	iaddr = itempaddr + PROG_NAME;
	//iDispaddr = iaddr;
	for(i=0;i<7;i++)
	{
		cReadmat[i] = I2C_Read1(iaddr); 									//8 bytes for material
		iaddr++;
	}
	cReadmat[i] = '\0'; 
//--------------------------------------------------------------------------------------------------------------

	iaddr = itempaddr + GAS_DIA;
	cGasdia = I2C_Read1(iaddr);
	pdia = cGasdia & 0x03;
	cGasdia = cGasdia >> 4;
	cGasdia = cGasdia & 0x03;
	pgas = cGasdia ;
			
	lcdput(6,0,cReadmat);			
	lcdput(6,48,cDiaTxt[pdia]);	
	lcdput(6,88,cGasTxt[pgas]);		
	lcdput(7,80,cGasPercent[pgas]);
	
//-----------------------------------------------------------------------------------------------------------------
/*
	iaddr = itempaddr + SYN_DATA;

	for(i=0;i<22;i++)
	{
		for(j=0;j<4;j++)
		{
			ctemp[j]= I2C_Read1(iaddr);
			iaddr++;
		}
		
		iReadpara[0][i] =ctemp[0];
		temp = (ctemp[1] & 0x0f);
		temp = (temp<<8);				//voltage
		iReadpara[0][i] |= temp;
		
		temp = (ctemp[1] & 0xf0);
		temp = (temp >> 4);
		temp |= (ctemp[2]<<4);
		iReadpara[1][i] =(temp);										//current
		
		iReadpara[2][i] = ctemp[3];									//thickness
	}
	
//-----------------------------------------------------------------------		

	iaddr = itempaddr + PMIG_PARA;
	//iDispaddr = iaddr;		
	for(i=0;i<10;i++)
	{
		for(j=0;j<2;j++)
		{
			ctemp[j] = I2C_Read1(iaddr);
			iaddr++;
		}																//Pulse parameter
		
		temp = ctemp[1];
		temp = temp << 8;
		iPulsepara[i] = ctemp[0];
		iPulsepara[i] |= temp;
	}
*/
//------------------------------------------------------------------------------------------------------------------	
}

void mem_to_mem_write(unsigned int iLoadloc,unsigned int iStoreloc)
{
	unsigned int i,temp2;
	unsigned char temp1;
	
	iFirstaddr = ((iLoadloc - 1)* E2POFFSET);
	iSecondaddr = ((iStoreloc - 1)* E2POFFSET);
	
	for(i=0;i<E2POFFSET;i++)
	{
		temp1 = I2C_Read(iFirstaddr);
		cE2p[0] = temp1;
		if(i == 0)
		{
			cE2p[0] = iProgramStrLoc;			
		}		
		I2C_Write(iSecondaddr,1);
		
		iSecondaddr++;
		iFirstaddr++;
	}
	
}


void program_check_from_mem(unsigned int locno)
{
	unsigned int i,temp,iaddr,iaddrtemp;	
	iaddr = FRAME_GAP + (locno - 1)*mE2POFFSET;
	iaddrtemp=iaddr;
	iPnoChk =I2C_Read1(iaddr);											//program no
	iaddr++;	
	datafordebugonlcd(iaddrtemp,iPnoChk);	
/****************Read_Material***************************************/	
	iaddr = iaddrtemp + PROG_NAME;
	for(i=0;i<7;i++)
	{
		cProgramChk[i] = I2C_Read1(iaddr); 									//8 bytes for material
		iaddr++;
	}
	cProgramChk[i] = 0; 		
/****************Read_Gas_Diameter************************************/	
	
	iaddr = iaddrtemp + GAS_DIA;
	cGasdiachk = I2C_Read1(iaddr);
	pdia = cGasdiachk & 0x03;
	cGasdiachk = cGasdiachk >> 4;
	cGasdiachk = cGasdiachk & 0x03;
	pgas = cGasdiachk;	
	//lcdput(4,0,ar412);		
	
	if(1)//iPnoChk == locno)
	{
		lcdput(6,0,cProgramChk);		
		lcdput(6,48,cDiaTxt[pdia]);
		lcdput(6,88,cGasTxt[pgas]);		
		lcdput(7,80,cGasPercent[pgas]);	
		
		//lcd_disp_hex_dec(iPnoChk);
		//currupdate();//
	}
	else
	{
		lcdput(6,0,ar413);
	}			
	

}


void display_update_for_pulse_para()
{
	if(1)//(cPulseparaupdatefg == 1) || (keychange1==1) )//|| (dispupdatef = 1))
	{
		dispupdatef = 1;
		Type.wirespeed		=0;
		Type.current		=0;
		Type.thickness		=0;	
		Type.voltage		=0;
		Type.arclength		=1;							
//PA,SA,BA,RISETM,STARTPULSE,PTM,DECAYTM,STM,SPARE,SPARE    
								
		if(pulseptr == 1)//PA)
		{
			diswin1[0]	='P';
			diswin1[1]	='P';
			diswin1[2]	='A';
//			disp_hex_dec_volt(iPulseparachk[0]);
			
		}
		else if(pulseptr == 2)//SA)
		{
			diswin1[0]	='P';
			diswin1[1]	='S';
			diswin1[2]	='A';
//			disp_hex_dec_volt(iPulseparachk[1]);														
		}
		else if(pulseptr == 3)//BA)
		{
			diswin1[0]	='P';
			diswin1[1]	='B';
			diswin1[2]	='A';	
//			disp_hex_dec_volt(iPulseparachk[2]);													
		}
		else if(pulseptr == 4)//RISETM)
		{
			diswin1[0]	='R';
			diswin1[1]	='T';
			diswin1[2]	='M';	
//			disp_hex_dec_volt(iPulseparachk[3]);													
		}
		else if(pulseptr ==5)//STARTPULSE)
		{
			diswin1[0]	='S';
			diswin1[1]	='T';
			diswin1[2]	='P';	
//			disp_hex_dec_volt(iPulseparachk[4]);													
		}
		else if(pulseptr == 6)//PTM)
		{
			diswin1[0]	='P';
			diswin1[1]	='T';
			diswin1[2]	='M';	
//			disp_hex_dec_volt(iPulseparachk[5]);													
		}
		else if(pulseptr == 7)//DECAYTM)
		{
			diswin1[0]	='D';
			diswin1[1]	='T';
			diswin1[2]	='M';	
//			disp_hex_dec_volt(iPulseparachk[6]);													
		}
		else if(pulseptr == 8)//STM)
		{
			diswin1[0]	='S';
			diswin1[1]	='T';
			diswin1[2]	='M';	
//			disp_hex_dec_volt(iPulseparachk[7]);													
		}
		dispupdatef = 0;																																										
	}
	//cParachangeflag = 0;	
}


void pulse_parameter_update()
{

		
	int i,j;
	
	
	for(i=0;i<10;i++)
	{
		iPulseparachk[i] = iPulsepara [i];
	}	
}

//-----------------------------------------------------------------------------
void write_in_external_memory_updated_data(unsigned int iSaveloc)
{
	unsigned int i,temp1,iaddrtemp,volt1,amp1;
	unsigned char cThick;
	
	
	iaddrtemp = (iSaveloc -1)* E2POFFSET;
	
	cE2p[0] = iPnoChk;
	I2C_Write(iaddrtemp,1);	

/***************Write_Material***************************************/		
	cE2p[0]= cProgramChk[0];
	cE2p[1]= cProgramChk[1];
	cE2p[2]= cProgramChk[2];
	cE2p[3]= cProgramChk[3];
	cE2p[4]= cProgramChk[4];
	cE2p[5]= cProgramChk[5];
	cE2p[6]= cProgramChk[6];
	I2C_Write(iaddrtemp+PROG_NAME, 7);	

/****************Write_Gas_Diameter***********************************/	
	iaddrtemp = (iSaveloc -1)* E2POFFSET;																
	cE2p[0] = cGasdiachk;
/*
0000	0.8		0000	Co2
0001	1.0		0001	ArCo2
0010	1.2		0010	ArO2
0011	1.6		0011	Ar
*/	
	I2C_Write(iaddrtemp+GAS_DIA,1);		
	
/**************Write_Voltage_Current_Thickness***********************/		

		
	for(i = 0;i < 22; ++i)
	{
			
		volt1 = newpautobasevtg[iSaveloc][i+2];;
		amp1 = newpautocurrent[iSaveloc][i+2];
		cThick = newpautothickness[iSaveloc][i+2];
		cE2p[0]= (volt1 & 0x00ff);
		temp1  = (volt1 & 0x0f00);
		cE2p[1]= (temp1 >> 8);
		temp1 = amp1;
		temp1 = temp1 << 4;
		cE2p[1] |= temp1;
		temp1 = amp1;
		temp1 = temp1 >> 4;
		cE2p[2]= ((temp1) & 0x00ff);	
		cE2p[3]= cThick;		

			
		I2C_Write(iaddrtemp+SYN_DATA, 4);	
		iaddrtemp = iaddrtemp + 4;	
	}
/*****************Write_Pulse_Parameter*************************/	
	iaddrtemp = (iSaveloc -1)* E2POFFSET;	
		
	for(i = 0; i < 8; ++i)
	{
		temp1 = iPulseparachk[i];
//		temp = 46 +i;
		cE2p[0] = temp1;
		cE2p[1] = temp1 >> 8;		
		I2C_Write(iaddrtemp+PMIG_PARA,2);	
		iaddrtemp = iaddrtemp + 2;			
	}	
}



