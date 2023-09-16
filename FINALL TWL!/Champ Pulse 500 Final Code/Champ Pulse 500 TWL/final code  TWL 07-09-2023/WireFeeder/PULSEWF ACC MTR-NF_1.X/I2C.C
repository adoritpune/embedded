#include "p30f6014A.h"
//#include "FUNCTION.C"
//#include "VARIABLE.C"
unsigned char byteread1();
void bytewrite(unsigned char data);
void NOACK(void);
void ACK(void);
void startBitGen(void);
void stopBitGen(void);

void I2C_init(void)
{
	//initialise port pins
	SCLIO = 0;										// clock output
	SDAIO = 0;										// data output					 	
}

void I2C_Write(unsigned int addr,unsigned int data)
{
	int icnt=0,addrh,addrl;
	int datah,datal;										//data output
	datah = (data >> 8);
	datal = (data & 0x00FF);
	addrh = (addr >> 8);
	addrl = (addr & 0x00FF);
/*******************START BIT********************************/	
	startBitGen();
/******************SENDING BYTE******************************/	
	bytewrite(0xA0);
	bytewrite(addrh);
	bytewrite(addrl);
	bytewrite(datal);
//	bytewrite(datal);		
/*******************STOP BIT*********************************/
	stopBitGen();
		
	count_6ms = 0;
	while(count_6ms <= 150)
	{
	}	
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
//	SDA = 1;
//	delayI2C();
//	SDAIO = 1;

	SDAIO = 0;
	SCL = 1;	
	delayI2C();
	SDA = 1;
	delayI2C();	
	cTimeout = 0;
	SDAIO = 1;			
	while(cTimeout < 200)
	{
		cTimeout++;
		if(SDA == 0)
		{
			cTimeout = 200;
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
	int i;	
	for(i=0;i<1000;i++)
	{
		Nop();
	}
}

unsigned int I2C_Read(unsigned int address)
{
	unsigned char addrh,addrl;//,datal,datah;
	unsigned int data;
	SCLIO = 0;
	data = 0;
	addrh = (address >> 8);
	addrl = (address & 0x00FF);
/*******************START BIT********************************/	
	startBitGen();
	bytewrite(0xA0);
	bytewrite(addrh);
	bytewrite(addrl);	
	startBitGen();
	bytewrite(0xA1);
	data=byteread1();
//	data = (data << 8);
//	ACK();
//	data |=byteread1();
//	ACK();	
//	byteread1();
	NOACK();	
	stopBitGen();
//	data = datah;
//	data = (data << 8);
//	data = (data & 0xFF00);
//	data |= datal ;	
	 //= datal;
	return data;
}

unsigned char byteread1()
{
	unsigned char itemp,data,cnt;
//	SDAIO = 0;
	
	data = 0;
//	SDA = 1;
	SDAIO = 1;	
	delayI2C();	
//	SCL = 0;
//	delayI2C();	
	for(cnt=0;cnt<8;cnt++)
	{		
		SCL = 1;
		delayI2C();	
		
		if(SDA == 1)		
		data |= 0x01;//|= (SDA & 0x01);
		else 
		data |= 0x00;	
		data = (data << 1);
		SCL = 0;
		delayI2C();		
	}
	SDAIO = 0;	
	return data;	
}
