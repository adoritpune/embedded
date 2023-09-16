




void Display(void)
{
	if(digit == 1)
	{
               // DECODE_A=0;
		DECODE_A=0;
                DECODE_B=0;
                DECODE_C=0;
		//latchdata(diswin1[1]);
                PORTB=0X00;
                delaymsec(50);
                PORTB=0XFF;
                delaymsec(50);
                digit++;
	}
	else if(digit == 2)
	{
                DECODE_A=1;
                DECODE_B=0;
                DECODE_C=0;
               // latchdata(diswin1[2]);
                PORTB=0X00;
                delaymsec(50);
                PORTB=0XFF;
                delaymsec(50);

		digit++;
	}
	else if(digit == 3)
	{
		DECODE_A=0;
                DECODE_B=1;
                DECODE_C=0;
               // latchdata(diswin1[3]);
                PORTB=0X00;
                delaymsec(50);
                PORTB=0XFF;
                delaymsec(50);

		digit++;
	}
	else if(digit == 4)
	{
		DECODE_A=1;
                DECODE_B=1;
                DECODE_C=0;
		//latchdata(diswin1[4]);
                PORTB=0X00;
                delaymsec(50);
                PORTB=0XFF;
                delaymsec(50);

		digit=1;
	}
        else if(digit == 5)
	{
		DECODE_A=0;
                DECODE_B=0;
                DECODE_C=1;
		//latchdata(diswin1[4]);
                PORTB=0X00;
                delaymsec(50);
                PORTB=0XFF;
                delaymsec(50);

		digit=1;
	}
        else if(digit == 6)
	{
		DECODE_A=1;
                DECODE_B=0;
                DECODE_C=1;
		//latchdata(diswin1[4]);
                PORTB=0X00;
                delaymsec(50);
                PORTB=0XFF;
                delaymsec(50);

		digit=1;
	}
         else if(digit == 7)
	{
		DECODE_A=1;
                DECODE_B=1;
                DECODE_C=1;
		//latchdata(diswin1[4]);
                PORTB=0X00;
                delaymsec(50);
                PORTB=0XFF;
                delaymsec(50);

		digit=1;
	}

}

//void latchdata(unsigned char num)
//{
//	unsigned char temp,i;
//	temp=num;
//	{
//		num=(num - 0x2F);//0x30);
//		for(i=0;i<8;i++)
//		{
//			arr[i]=lookup_table[num][i];
//		}
//	}
//	SEGA=arr[0];
//   	SEGB=arr[1];
//  	SEGC=arr[2];
//        SEGD=arr[3];
//        SEGE=arr[4];
//   	SEGF=arr[5];
//   	SEGG=arr[6];
//   	SEGDP=arr[7];
//    //for(a=0;a<=5;a++);
//}
//
//void disp_hex_dec123(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
//{
//	 diswin1[4]= 0x30 +(hex_data % 10);
//     hex_data /= 10;
//     diswin1[3]= 0x30+(hex_data % 10);
//     hex_data /= 10;
//     diswin1[2]= 0x30 +(hex_data % 10);
//     hex_data /= 10;
//     diswin1[1] =0x30 + hex_data ;
//     //mahesh[1]  =0x31;
//
//   /*  mjp123=0x31;
//     mjp123=diswin1[1];//0x35;
//    //mjp123=0x31;
//    dig1=0x30+1;
//    dig2=0x30+2;
//    dig3=0x30+3;
//    dig4=0x30+4;
//    */
//}
//






