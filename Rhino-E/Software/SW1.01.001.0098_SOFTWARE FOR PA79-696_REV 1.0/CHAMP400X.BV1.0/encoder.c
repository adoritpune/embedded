/*
#include "variable.h"
#include "define.h"
#include "function.h"
#include "structure.h"

unsigned char enc_port(void)
{
	unsigned int portvalue=0x0000,status;
	portvalue=0x0000;
	portvalue=ENCODERA;
	portvalue=portvalue<<1;
	portvalue=portvalue|ENCODERB;
	portvalue=(portvalue & 0X0003);
	new1=portvalue;
	temp1=new1;
	if((temp1 ^ old) !=0)                
	{
		old=new1;
		status = 1;
	}
	else
	{
		old=new1;
		status = 0;
	}
    return (status);
}


unsigned char scanencoder(void)
{
     unsigned char result=0;
     if(enc_port() == 1)
	{
		if(firstpulse==0 && secondpulse==0)
		{
			if(new1==0x02)    //10
			{
				firstpulse=1;
				secondpulse=0;
				plus=1;
				result='$';
			}
			if(new1==0x01)     //01
			{
				firstpulse=1;
				secondpulse=0;
                minus=1;
				result='$';
			}
		}
		else if(firstpulse==1 && secondpulse==0)
		{        
			if(new1==0x03) 
			{
				firstpulse=1;
				secondpulse=1;
				result='$';
			}
		}
		else if(firstpulse==1 && secondpulse==1)
		{
			if(new1==0x01 && plus==1)
			{
				firstpulse=0;
				plus=0;
				result='+';
			}
			if(new1==0x02 && minus==1)
			{
				firstpulse=0;
				minus=0;
				result='-';
			}
			firstpulse=0;
            secondpulse=0;
		}
		else
		{
			plus=0;
			minus=0;
			firstpulse=0;
     		secondpulse=0;
			result='$';
        }
	}
 return(result);
}
*/

