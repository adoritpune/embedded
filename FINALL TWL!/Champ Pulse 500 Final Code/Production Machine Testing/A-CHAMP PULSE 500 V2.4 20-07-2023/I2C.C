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
	for(i=0;i<10;i++)
	{
		Nop(); 
		//j++;
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
	datal = I2C_Read(address);
	datah = I2C_Read(address+1);	
	
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
void Check_E2p(void)
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
}
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
	iPno = iLocation_no;

	I2C_Write1(isaveaddr,1);
				 
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
		volt = i*80;//newpautobasevtg[iLocation_no][i+2];;
		amp = i*15;//newpautocurrent[iLocation_no][i+2];
		cThickness = i*9;//newpautothickness[iLocation_no][i+2];
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
		temp=123;//newpulsemigparameter[iLocation_no][i];
//		temp = 46 +i;
		cE2p[0] = temp;
		cE2p[1] = temp >> 8;		
		I2C_Write1(isaveaddr+PMIG_PARA,2);	
		isaveaddr = isaveaddr + 2;			
	}		
	
//----------------------------------------------------------------------------------------------------------------------------	

}

/*void write_USB_data_in_external_memory(unsigned int iLocation_no)
{
	unsigned int i,temp,volt,amp;
	unsigned char cThickness;
//----------------------------------------------------------------------------------------------------------------------------
	isaveaddr = (iLocation_no -1)* E2POFFSET;
	cE2p[0] = iLocation_no;
	iPno = iLocation_no;

	I2C_Write1(isaveaddr,1);
//----------------------Material Write---------------------------------------------------------------------------------------
	cE2p[0]= cUSBdata[0];//'K';
	cE2p[1]= cUSBdata[1];//'T';
	cE2p[2]= cUSBdata[2];//'M';
	cE2p[3]= cUSBdata[3];//'X';
	cE2p[4]= cUSBdata[4];//'X';
	cE2p[5]= cUSBdata[5];//'X';
	cE2p[6]= cUSBdata[6];//'X';
	I2C_Write1(isaveaddr+PROG_NAME, 7);
	
//----------------------Gas Dia Write-----------------------------------------------------------------------------------------	
	
	cE2p[0] = 0x12;
/*
0000	Co2		0000  0.8			
0001	ArCo2	0001  1.0	
0010	ArO2	0010  1.2	
0011	Ar		0011  1.6	
*/	
/*	I2C_Write1(isaveaddr+GAS_DIA,1);
	
//----------------------SYN Data --------------------------------------------------------------------------------------
		
	for(i = 0;i < 22; ++i)
	{	
		volt = iUSBData[2][i];//newpautobasevtg[iLocation_no][i+2];;
		amp = iUSBData[1][i];//newpautocurrent[iLocation_no][i+2];
		cThickness = iUSBData[3][i];//newpautothickness[iLocation_no][i+2];
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
		temp=iUSBData[4][i];//newpulsemigparameter[iLocation_no][i];
//		temp = 46 +i;
		cE2p[0] = temp;
		cE2p[1] = temp >> 8;		
		I2C_Write1(isaveaddr+PMIG_PARA,2);	
		isaveaddr = isaveaddr + 2;			
	}		
	
//----------------------------------------------------------------------------------------------------------------------------		
}*/


void read_from_external_memory(unsigned int iLoc)
{
	int i,j,temp,temp2,temp3,iaddr,itempaddr,itmp;
	unsigned char ctemp[4];
	
	if(weldmode=='P')
	{
		iaddr = (iLoc - 1)*E2POFFSET;
	}
	else if(weldmode=='G')
	{
		iaddr = (FRAME_GAP + (iLoc - 1)*mE2POFFSET);
	}
	itempaddr=iaddr;
	itmp =I2C_Read1(iaddr);											//program no
	iaddr++;
	iReadPno =I2C_Read1(iaddr);											//program no
	iaddr++;
	iReadPno = iReadPno << 8;
	iReadPno |= itmp;
	
//------------------------------------------------------------------------------------------------------------
	iaddr = itempaddr + WELD_MODE;

	cWeldModeRead = I2C_Read1(iaddr);	
	
//------------------------------------------------------------------------------------------------------------		

	iaddr = itempaddr + PROG_NAME;
	//iDispaddr = iaddr;
	for(i=0;i<7;i++)
	{
		cReadmat[i] = I2C_Read1(iaddr); 									//8 bytes for material
		iaddr++;
	}
	cReadmat[i] = 0; 
	
//---------------Detection Of ALU and MS Wire------------------------------------------------------------------------
	/*if((cReadmat[0] == 'A') && (cReadmat[1] == 'L'))
	{
		cSoftwireDetfg = 1;	
	}
	else
	{
		cSoftwireDetfg = 0;	
	}
	/*
	
	if(((cReadmat[0] == 'M') && (cReadmat[1] == 'S')) || ((cReadmat[1] == 'M') && (cReadmat[2] == 'S')))
	{
		cMSwireDetfg = 1;	
	}
	else
	{
		cMSwireDetfg = 0;	
	}	
	*/	
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
	if(iProgramLoadLoc==203 || iProgramLoadLoc==207 || iProgramLoadLoc==210 )
	{
		lcdput(7,80,cGasPercent[2]);
	}
	else
	{
		lcdput(7,80,cGasPercent[pgas]);	 	
	}
	
//-----------------------------------------------------------------------------------------------------------------

	iaddr = itempaddr + SYN_DATA;

	for(i=0;i<27;i++)
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

	if(weldmode=='G')
	{
		iaddr = itempaddr + MAX_WS;
		ctemp[0] = I2C_Read1(iaddr);
		iaddr++;
		ctemp[1] = I2C_Read1(iaddr);
		
		iMaxWSLimit = ctemp[0];
		temp = ctemp[1];
		temp = (temp<<8);		
		iMaxWSLimit |= temp;
		
	}

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
	
	if(weldmode=='P')
	{
		iMaxWSLimit = iPulsepara[8];		
	}		
	
//------------------------------------------------------------------------------------------------------------------

	iaddr = itempaddr + FACTORS;
		for(j=0;j<2;j++)
		{
			ctemp[j] = I2C_Read1(iaddr);
			iaddr++;
		}																
		
		temp = ctemp[1];
		temp = temp << 8;
		iPulseFreqFact = ctemp[0];
		iPulseFreqFact |= temp;	
		
		for(j=0;j<2;j++)
		{
			ctemp[j] = I2C_Read1(iaddr);
			iaddr++;
		}																
		
		temp = ctemp[1];
		temp = temp << 8;
		iPulsetmfactor = ctemp[0];
		iPulsetmfactor |= temp;	
		
		for(j=0;j<2;j++)
		{
			ctemp[j] = I2C_Read1(iaddr);
			iaddr++;
		}																
		
		temp = ctemp[1];
		temp = temp << 8;
		iPulsecurfactor = ctemp[0];
		iPulsecurfactor |= temp;	
		
		for(j=0;j<3;j++)
		{
			ctemp[j] = I2C_Read1(iaddr);
			iaddr++;
		}
		/*temp = ctemp[2];
		temp3 = temp << 16;
		temp = ctemp[1];		
		temp2 = temp << 8;
		temp = ctemp[0];	
		iSfOutputMax = ((temp | temp2) | (temp3));*/
		//iSfOutputMax |= ;//ctemp[1]<<8;
		//iSfOutputMax |= temp;
		//iSfOutputMax |= ctemp[1];		
		iSfOutputMax = ((ctemp[2])*100 + (ctemp[1])*10 + (ctemp[0]));

//------------------------------------------------------------------------------------------------------------------

	for(i=0;i<27;i++)
	{
		iPSetCurrent[i] = iReadpara[1][i];	
	}
	for(i=0;i<27;i++)
	{
		iPSetBaseVoltage[i] = iReadpara[0][i];	
	}
	for(i=0;i<27;i++)
	{
		iPThickness[i] = iReadpara[2][i];	
	}
	for(i=0;i<10;i++)
	{
		iPulseParameter[i] = iPulsepara[i];
	}
	//iPulseParameter[7] = 100;
	//iPulseParameter[9] = 400;
	for(i=0;i<7;i++)
	{
		cDisplayMat[i] = cReadmat[i];	
	}
	
	cDisplayGas = pgas;
	cDisplayDia = pdia;
	iPProgramNo = iReadPno;
//--------------------------------------------------------------------------------------------------------------------------	
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
	unsigned char ctemp[2];
	
	if(weldmode=='P')
	{
		iaddr = (locno - 1)*E2POFFSET;
	}
	else if(weldmode=='G')
	{
		iaddr = FRAME_GAP +(locno - 1)*mE2POFFSET;
	}
	
	iaddrtemp=iaddr;
	ctemp[0] = I2C_Read1(iaddr);											//program no 
	iaddr++;	
	ctemp[1] = I2C_Read1(iaddr);											//program no 	
	iaddr++;
	iPnoChk = ctemp[1] << 8;
	iPnoChk |= ctemp[0];

	temp =I2C_Read1(iaddr);

	iaddr = iaddrtemp + WELD_MODE;	
	cWeldModeRead = I2C_Read1(iaddr);		
	
	//NumberUpdate(3,5,pdia);
	//NumberUpdate(3,50,pgas);	
	
	//lcdput(4,0,ar412);		
	
	if(iPnoChk == locno)
	{
		
	//--------------------WELD_MODE---------------------------------------
	
		iaddr = iaddrtemp + WELD_MODE;
		cWeldModechk = I2C_Read1(iaddr);
	
		
	/****************Read_Material***************************************/	
		iaddr = iaddrtemp + PROG_NAME;
		for(i=0;i<7;i++)
		{
			cProgramChk[i] = I2C_Read1(iaddr); 									//8 bytes for material
			iaddr++;
		}
		cProgramChk[7] = 0; 		
	/****************Read_Gas_Diameter************************************/	
		
		iaddr = iaddrtemp + GAS_DIA;
		cGasdiachk = I2C_Read1(iaddr);
		pdia = cGasdiachk & 0x03;
		cGasdiachk = cGasdiachk >> 4;
		cGasdiachk = cGasdiachk & 0x03;
		pgas = cGasdiachk;		
		
		
		/*if((cWeldModechk == "P") || (cWeldModechk == "G"))
		{
			//lcdput(5,0,"PULSE");		
		}
		else
		{
			//lcdput(5,0,"Wrong");
			//lcdput(4,0,cWeldModechk);		
		}*/
		
		if(weldmode=='P')
		{
			
			lcdput(6,0,cProgramChk);
			lcdput(6,48,cDiaTxt[pdia]);
			lcdput(6,88,cGasTxt[pgas]);		
			lcdput(7,80,cGasPercent[pgas]);	
  		}      
        else if(weldmode=='G')
        {
	        	
			lcdput(6,0,cProgramChk);
			lcdput(6,48,cDiaTxt[pdia]);
			lcdput(6,88,cGasTxt[pgas]);	
				
			if(iProgramLoadLoc==203 || iProgramLoadLoc==207 || iProgramLoadLoc==210)
			{
				lcdput(7,80,cGasPercent[2]);
			}
			else
			{
				lcdput(7,80,cGasPercent[pgas]);	 	
			}	
		}	

		cNoProgramfg = 0;
	}
	else
	{
		lcdput(6,0,ar413);
		lcdput(7,80,cGasPercent[0]);	
		cNoProgramfg = 1;
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
			
		volt1 = 11;//newpautobasevtg[iSaveloc][i+2];;
		amp1 = 22;//newpautocurrent[iSaveloc][i+2];
		cThick = 33;//newpautothickness[iSaveloc][i+2];
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

void write_USB_data_in_external_memory(unsigned int iLocation_no)
{
	unsigned int i,temp,volt,amp;
	unsigned char cThickness;
//----------------------------------------------------------------------------------------------------------------------------
	if(weldmode == 'P')
	{
		isaveaddr = (iLocation_no -1)* E2POFFSET;
	}
	else if(weldmode == 'G')
	{
		isaveaddr = FRAME_GAP +(iLocation_no -1)* mE2POFFSET;		
	}		
	cE2p[0] = iLocation_no;
	cE2p[1] = iLocation_no >> 8;
	iPno = iLocation_no;

	I2C_Write1(isaveaddr,2);
//----------------------Material Write---------------------------------------------------------------------------------------
	cE2p[0]= cUSBdata[0];//'K';
	cE2p[1]= cUSBdata[1];//'T';
	cE2p[2]= cUSBdata[2];//'M';
	cE2p[3]= cUSBdata[3];//'X';
	cE2p[4]= cUSBdata[4];//'X';
	cE2p[5]= cUSBdata[5];//'X';
	cE2p[6]= cUSBdata[6];//'X';
	I2C_Write1(isaveaddr+PROG_NAME, 7);
	
//----------------------Gas Dia Write-----------------------------------------------------------------------------------------	
	
	cE2p[0] = cUSBGasDia;//0x12;
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
		volt = iUSBData[2][i];//newpautobasevtg[iLocation_no][i+2];;
		amp = iUSBData[1][i];//newpautocurrent[iLocation_no][i+2];
		cThickness = iUSBData[3][i];//newpautothickness[iLocation_no][i+2];
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

	if(weldmode == 'P')
	{
		
	
		isaveaddr = (iLocation_no -1)* E2POFFSET;	
			
		for(i = 0; i < 10; ++i)
		{
			temp=iUSBData[4][i];//newpulsemigparameter[iLocation_no][i];
		//	temp = 46 +i;
			cE2p[0] = temp;
			cE2p[1] = temp >> 8;		
			I2C_Write1(isaveaddr+PMIG_PARA,2);	
			isaveaddr = isaveaddr + 2;			
		}		
		
		isaveaddr = (iLocation_no -1)* E2POFFSET;
		
			temp=iPulseFreqFact;
			cE2p[0] = temp;
			cE2p[1] = temp >> 8;		
			I2C_Write1(isaveaddr+FACTORS,2);	
			isaveaddr = isaveaddr + 2;	
			
			temp=iPulsetmfactor;
			cE2p[0] = temp;
			cE2p[1] = temp >> 8;		
			I2C_Write1(isaveaddr+FACTORS,2);	
			isaveaddr = isaveaddr + 2;	
			
			temp=iPulsecurfactor;
			cE2p[0] = temp;
			cE2p[1] = temp >> 8;		
			I2C_Write1(isaveaddr+FACTORS,2);	
			isaveaddr = isaveaddr + 2;									

			temp=iUSBsfConst;
			cE2p[0] = temp%10;
			temp = temp / 10;
			cE2p[1] = temp%10;
			temp = temp / 10;			
			cE2p[2] = temp%10;
			itempo2 = cE2p[2]*100 + cE2p[1]*10 + cE2p[0];
			I2C_Write1(isaveaddr+FACTORS,3);	
			//isaveaddr = isaveaddr + 2;	
	}
	//iMaxWSLimit = iUSBData[4][8];
//------------------------DELETE FILE  IF FIRST THREE CURRENT VALUES ARE ZERO----------------------------------------------------------------------------------------------------		

	if(weldmode == 'P')
	{
		isaveaddr = (iLocation_no -1)* E2POFFSET;
	}
	else if(weldmode == 'G')
	{
		isaveaddr = FRAME_GAP +(iLocation_no -1)* mE2POFFSET;		
	}
	
	if((iUSBData[1][1] == 0) && (iUSBData[1][2] == 0) && (iUSBData[1][3] == 0))
	{
		cE2p[0] = 0;
		cE2p[1] = 0;
	
		I2C_Write1(isaveaddr,2);							//Replace the program no with zero.		
	}	

}


void save_parameter_into_ROM()
{
	if(cMacMenufg == 1)
	{
		cE2p[0] = cSerialNo[0];	
		cE2p[1] = cSerialNo[1];	
		cE2p[2] = cSerialNo[2];	
		cE2p[3] = cSerialNo[3];	
		
		I2C_Write1(MACHINE_ID_ADDR, 4);			
	}
	
	if(cWeldLatchData == 0)
	{
		cE2p[0] = iCreatFilecntr;
		cE2p[1] = iCreatFilecntr >> 8;
	
		I2C_Write1(USB_FILE_CNTR_ADDR,2);					
	}	
	
	
		
}
void read_parameter_from_ROM()
{
	int i,iaddr,itmp;
	iaddr = MACHINE_ID_ADDR;
	
	for(i=0;i<4;i++)
	{
		cSerialNo[i] = I2C_Read1(iaddr);
		iaddr++;
	}
	
	iaddr = USB_FILE_CNTR_ADDR;
	itmp =I2C_Read1(iaddr);											//program no
	iaddr++;
	iCreatFilecntr =I2C_Read1(iaddr);											//program no
	iaddr++;
	iCreatFilecntr = iCreatFilecntr << 8;
	iCreatFilecntr |= itmp;	

	if(iCreatFilecntr > 9999)
	{
		iCreatFilecntr = 0;
	}	
				
}		
void block_check(unsigned int iBlockaddr)
{
	unsigned int addrh ,addrl;
	
	
	cE2p[0] = 'A';
	
	addrh = iBlockaddr;
	addrh >>= 8;
	addrl = (iBlockaddr & 0x00FF);	

/*******************START BIT********************************/	
	startBitGen();
/******************SENDING BYTE******************************/	
	bytewrite(0xA8);
	bytewrite(addrh);
	bytewrite(addrl);

	bytewrite(cE2p[0]);	

//	bytewrite(datah);
//	bytewrite(datal);		
/*******************STOP BIT*********************************/
	stopBitGen();	
	count_6ms = 0;
	while(count_6ms <= 6)
	{
	}
//--------------------------------------------------------------------------------------	


	startBitGen();
	bytewrite(0xA8);
	bytewrite(addrh);
	bytewrite(addrl);	
	startBitGen();
	bytewrite(0xA9);
	ctempo = byteread();
	NOACK();	
	stopBitGen();


}



