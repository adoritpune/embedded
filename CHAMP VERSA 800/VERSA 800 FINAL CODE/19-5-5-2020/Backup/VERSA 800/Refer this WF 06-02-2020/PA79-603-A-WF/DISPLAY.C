
#ifndef _DISPLAY_C_
#define _DISPLAY_C_


//#include "pic16f886.h"

void Display(void)
{
        PORTB=0x00;
        if(digit<=5)
        {
            switch(digit)
            {
                case 0:
                    DECODE_A=0;
                    DECODE_B=0;
                    DECODE_C=0;
                    OUTPORTB=lookup_table[diswin1[digit]];
                    if(Typedp.digitdp1==1)
                        SEGDP=1;
                    else
                        SEGDP=0;    
                    break;
                case 1:
                    DECODE_A=1;
                    DECODE_B=0;
                    DECODE_C=0;
                    OUTPORTB=lookup_table[diswin1[digit]];
                    if(Typedp.digitdp2==1)
                        SEGDP=1;
                    else
                        SEGDP=0;
                    break;
                case 2:
                    DECODE_A=0;
                    DECODE_B=1;
                    DECODE_C=0;
                    OUTPORTB=lookup_table[diswin1[digit]];
                    if(Typedp.digitdp3==1)
                        SEGDP=1;
                    else
                        SEGDP=0;
                    break;
                case 3:
                    DECODE_A=1;
                    DECODE_B=1;
                    DECODE_C=0;
                    OUTPORTB=lookup_table[diswin1[digit]];
                    if(Typedp.digitdp4==1)
                        SEGDP=1;
                    else
                        SEGDP=0;
                    break;
                case 4:
                    DECODE_A=0;
                    DECODE_B=0;
                    DECODE_C=1;
                    OUTPORTB=lookup_table[diswin1[digit]];
                    if(Typedp.digitdp5==1)
                        SEGDP=1;
                    else
                        SEGDP=0;
                    break;
                case 5:
                    DECODE_A=1;
                    DECODE_B=0;
                    DECODE_C=1;
                    OUTPORTB=lookup_table[diswin1[digit]];
                    if(Typedp.digitdp6==1)
                        SEGDP=1;
                    else
                        SEGDP=0;
                    break;
                default:
                    break;
            }
        }
        else if(digit == 6)
        {
            DECODE_A=0;
            DECODE_B=1;
            DECODE_C=1;
            //PORTB=0x00;//Displayarr[diswin1[digit]];
            OUTPORTB=TypeU.LEDGROUP[0];//0x0F;//Displayarr[diswin1[digit]];
        }
        else if(digit == 7)
        {
            DECODE_A=1;
            DECODE_B=1;
            DECODE_C=1;
            //PORTB=0xFF;//Displayarr[diswin1[digit]];
            OUTPORTB=TypeU.LEDGROUP[1];//0x00;//Displayarr[diswin1[digit]];
            //TRISB=0X0F; 
        }
        else if(digit == 8)
        {
            TRISB=0X0F;
            for(i=0;i>=100;i++);
            portbstatus=PORTB;//PORTBSTATUS;
            for(i=0;i>=200;i++);
            if(pportb==portbstatus)
            {
                temp=portbstatus;
                temp=(temp & 0x0F);
                if(temp==0x01)
                     key=key_gason;//'A';//Key_s1=1;
                else if(temp==0x02)
                     key=key_inch; //'B';//Key_s1=1;
                else if(temp==0x04)
                     key=key_mode; //'C';//Key_s1=1;
                else if(temp==0x08)
                     key=key_disp;//'D';//Key_s1=1;
                else
                     key=key_no;//'X';//Key_s1=0;
            }
            else
            {
                key=key_no;//'X';//Key_s1=0;
            }   
            pportb=portbstatus;
            TRISB=0X00; 
        }
        if(++digit >=9)//8)
        digit=0;
}

//void latchdata(unsigned int num)
//{
////	unsigned char temp,i;
////	temp=num;
////	{
////		num=(num - 0x2F);  //0x30);
////		for(i=0;i<8;i++)
////		{
////			arr[i]=lookup_table[num][i];
////		}
////	}
////	SEGA=arr[0];
////   	SEGB=arr[1];
////  	SEGC=arr[2];
////        SEGD=arr[3];
////        SEGE=arr[4];
////   	SEGF=arr[5];
////   	SEGG=arr[6];
////   	SEGDP=arr[7];
//////
//
//  // PORTB=Displayarr[num];
//}

void disp_hex_window1(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
 
    diswin1[2]= hex_data % 10;
     hex_data /= 10;
     diswin1[1]= hex_data % 10;
     hex_data /= 10;
     diswin1[0]= hex_data % 10;
     
   
}

void disp_hex_window2(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
     diswin1[5]= hex_data % 10;
     hex_data /= 10;
     diswin1[4]= hex_data % 10;
     hex_data /= 10;
     diswin1[3]= hex_data % 10;
     diswin1[6]=0x00;
     diswin1[7]=0x00;
     
   
}

void disp_hex_window11(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
     diswin1[2]= hex_data % 10;
     hex_data /= 10;
     diswin1[1]= hex_data % 10;
     hex_data /= 10;
     diswin1[0]= hex_data % 10;
 
}

void disp_hex_window22(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
    diswin1[5]= hex_data % 10;
     hex_data /= 10;
     diswin1[4]= hex_data % 10;
     hex_data /= 10;
     diswin1[3]= hex_data % 10;
     diswin1[6]=0x00;
     diswin1[7]=0x00;
  
}



void Delayms(unsigned int delay)
{

    unsigned int yyy=0,xxx=0;
    for(xxx=0;xxx<delay;xxx++)          //50 ms delay
   {
       for(yyy=0;yyy<138;yyy++);       // 1 msec delay
   }



}

void read_key(void)
{
   // TRISB=0x0F;






}



#endif



