#include "define.h"
#include "structure.h"
#include "variable.h"
#include "function.h"



void latdata(unsigned char num)
{   
//	if(disdigit <=8)
//	{
		num =(num - 0x2F);
		for(ijk=0;ijk<8;ijk++)
		{
			arr[ijk]=lookup_table[num][ijk];
		}	
		if(setdp==1) 
            arr[7]=1;
//	}
//	else
//	{
//		for(ijk=0;ijk<8;ijk++)
//		{
//			temp=num;
//			temp=(temp >> ijk);
//			temp= (temp & 0X01);
//			if(temp==0)
//			{
//				temp=0;
//			}
//			else if(temp==1)
//			{
//				temp=1;
//			}
//			arr[ijk]=temp;
//		}
//	}
    
	SEGALAT=arr[0];
	SEGBLAT=arr[1];
	SEGCLAT=arr[2];
	SEGDLAT=arr[3];
	SEGELAT=arr[4];
	SEGFLAT=arr[5];
	SEGGLAT=arr[6];
	SEGDPLAT=arr[7];

}

void display(void)
{
    
    if(disdigit == 1)
    {
		if(Typedp.digitdp1==1)
			setdp=1;
		else
			setdp=0;
        
        latdata(iDispcurr[0]);
        SEL1LAT = 1;
        SEL2LAT = 0; //0
        SEL3LAT = 0; //0
        SEL4LAT = 0;
        SEL5LAT = 0;
        SEL6LAT = 0;
        SEL7LAT = 0;
        SEL8LAT = 0;
        disdigit++;        

    }
    
    else if(disdigit == 2)
    {
		if(Typedp.digitdp2==1)
			setdp=1;
		else
			setdp=0;

        latdata(iDispcurr[1]);
        SEL1LAT = 0;
        SEL2LAT = 1;
        SEL3LAT = 0;
        SEL4LAT = 0;
        SEL5LAT = 0;
        SEL6LAT = 0;
        SEL7LAT = 0;
        SEL8LAT = 0;
        disdigit++;         
    }    
    else if(disdigit == 3)
    {
		if(Typedp.digitdp3==1)
			setdp=1;
		else
			setdp=0;

        latdata(iDispcurr[2]);
        SEL1LAT = 0;
        SEL2LAT = 0;
        SEL3LAT = 1;
        SEL4LAT = 0;
        SEL5LAT = 0;
        SEL6LAT = 0;
        SEL7LAT = 0;
        SEL8LAT = 0;        
        disdigit++;     
                 
    }  
    
    else if(disdigit == 4)
    {
		if(Typedp.digitdp4==1)
			setdp=1;
		else
			setdp=0;

        latdata(iDispcurr[3]);
        SEL1LAT = 0;
        SEL2LAT = 0;
        SEL3LAT = 0;
        SEL4LAT = 1;
        SEL5LAT = 0;
        SEL6LAT = 0;
        SEL7LAT = 0;
        SEL8LAT = 0;        
        disdigit++;        
    }
    else if(disdigit == 5)
    {
		if(Typedp.digitdp5==1)
			setdp=1;
		else
			setdp=0;

        latdata(iDispvolt[0]);
        SEL1LAT = 0;
        SEL2LAT = 0;
        SEL3LAT = 0;
        SEL4LAT = 0;
        SEL5LAT = 1;
        SEL6LAT = 0;
        SEL7LAT = 0;
        SEL8LAT = 0;        
        disdigit++;        
    }
    else if(disdigit == 6)
    {
		if(Typedp.digitdp6==1)
			setdp=1;
		else
			setdp=0;

        latdata(iDispvolt[1]);
        SEL1LAT = 0;
        SEL2LAT = 0;
        SEL3LAT = 0;
        SEL4LAT = 0;
        SEL5LAT = 0;
        SEL6LAT = 1;
        SEL7LAT = 0;
        SEL8LAT = 0;        
        disdigit++;
    }
    else if(disdigit == 7)
    {
		if(Typedp.digitdp7==1)
			setdp=1;
		else
			setdp=0;

        latdata(iDispvolt[2]);
        SEL1LAT = 0;
        SEL2LAT = 0;
        SEL3LAT = 0;
        SEL4LAT = 0;
        SEL5LAT = 0;
        SEL6LAT = 0;
        SEL7LAT = 1;
        SEL8LAT = 0;        
        disdigit++;
    }
    else if(disdigit == 8)
    {
		if(Typedp.digitdp8==1)
			setdp=1;
		else
			setdp=0;

        latdata(iDispvolt[3]);
        SEL1LAT = 0;
        SEL2LAT = 0;
        SEL3LAT = 0;
        SEL4LAT = 0;
        SEL5LAT = 0;
        SEL6LAT = 0;
        SEL7LAT = 0;
        SEL8LAT = 1;        
        disdigit = 1;
    }
      
}


void hex_to_dec_curr(unsigned int iTemp) 
{
    iDispcurr[3] = 0x30 + (iTemp % 10);
    iTemp = iTemp / 10;
    iDispcurr[2] = 0x30 + (iTemp % 10);
    iTemp = iTemp / 10;
    iDispcurr[1] = 0x30 + (iTemp % 10);
    iTemp = iTemp / 10;
    iDispcurr[0] = 0x30 + iTemp % 10;    
}

void hex_to_dec_volt(unsigned int iTemp)
{
    iDispvolt[3] = 0x30 + (iTemp % 10);
    iTemp = iTemp / 10;
    iDispvolt[2] = 0x30 + (iTemp % 10);
    iTemp = iTemp / 10;
    iDispvolt[1] = 0x30 + (iTemp % 10);
    iTemp = iTemp / 10;
    iDispvolt[0] = 0x30 + (iTemp % 10);
}

void hex_to_dec_time(unsigned int Hour, unsigned int Min)
{
    // HOUR  
    iDispvolt[3] = 0x30 + (Hour % 10);
    Hour = Hour / 10;
    iDispvolt[2] = 0x30 + (Hour % 10);

    // MIN
    iDispvolt[1] = 0x30 + (Min % 10);
    Min = Min / 10;
    iDispvolt[0] = 0x30 + (Min % 10);
}

