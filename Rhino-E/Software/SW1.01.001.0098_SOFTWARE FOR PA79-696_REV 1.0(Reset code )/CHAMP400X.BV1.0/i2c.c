#include "variable.h"
#include "function.h"
#include "define.h"
#include "xc.h"
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
	SCL = 1;	
	delayI2C();
	SDA = 1;
	delayI2C();	
	cTimeout = 0;
	SDAIO = 1;			
	delayI2C();
	while(SDA == 1)
	{
		cTimeout++;
		if(cTimeout >= 500)
		{
//			SDA = 0;
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



void SendACK(void)
{
	SDAIO = 0;	

	SDA = 0;
	delayI2C();
	SCL = 1;
	delayI2C();	
	SDAIO = 0;		
}

void I2C_Write(unsigned int data_out)
{
	unsigned int dac_out_h ,dac_out_l;
	unsigned char i;
	i = 0;
       
	dac_out_h = data_out;
	dac_out_h = dac_out_h >> 8;
    dac_out_h = dac_out_h & 0x0F;    
	dac_out_l = data_out;
 
   
///*******************START BIT********************************/	

    startBitGen();

///******************SENDING BYTE******************************/	
	bytewrite(0xC0);                //SLAVE ADDRESS
	bytewrite(dac_out_h);
	bytewrite(dac_out_l);
		
/*******************STOP BIT*********************************/
	stopBitGen();	
	
}

void bytewrite(unsigned char data)
{
	unsigned char temp,i;
	temp = data;	
	SDAIO = 0;
	cMemorybusyfg = 1;		
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
	cMemorybusyfg = 0;		
	ACK();		
}

void delayI2C(void)
{
	int i;	
	for(i=0;i<1;i++)
	{
//		__nop(); 
	}
}