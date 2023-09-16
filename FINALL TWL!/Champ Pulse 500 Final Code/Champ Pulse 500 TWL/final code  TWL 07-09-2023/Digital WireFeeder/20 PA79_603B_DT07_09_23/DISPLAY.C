
const unsigned int lookup_table[46][8]=
							{ //{a,b,c,d,e,f,g,dp}
								{0,0,0,0,0,0,0,0},		//null character forword slash '/' //0
								{1,1,1,1,1,1,0,0},		//0
								{0,1,1,0,0,0,0,0},		//1
								{1,1,0,1,1,0,1,0},		//2
								{1,1,1,1,0,0,1,0},		//3
								{0,1,1,0,0,1,1,0},		//4
								{1,0,1,1,0,1,1,0},		//5
								{1,0,1,1,1,1,1,0},		//6	
								{1,1,1,0,0,0,0,0},		//7
								{1,1,1,1,1,1,1,0},		//8
								{1,1,1,1,0,1,1,0},		//9
								{1,1,1,1,1,1,0,0},		//3A
								{0,1,1,0,0,0,0,0},		//3B
								{1,1,0,1,1,0,1,0},		//3C
								{1,1,1,1,0,0,1,0},		//3D
								{0,1,1,0,0,1,1,0},		//3E
								{1,0,1,1,0,1,1,0},		//3F
								{1,0,1,1,1,1,1,0},		//41
								{1,1,1,0,1,1,1,0},		//A
								{0,0,1,1,1,1,1,0},		//B
								{1,0,0,1,1,1,0,0},		//C
								{0,1,1,1,1,0,1,0},		//D
								{1,0,0,1,1,1,1,0},		//E
								{1,0,0,0,1,1,1,0},		//F
								{1,0,1,1,1,1,0,0},		//G
								{0,1,1,0,1,1,1,0},		//H
								{0,0,1,0,0,0,0,0},		//I
								{0,1,1,1,1,0,0,0},		//J
								{0,0,0,0,1,1,1,0},		//K
								{0,0,0,1,1,1,0,0},		//L
								{1,0,1,0,1,0,1,0},		//M
								{0,0,1,0,1,0,1,0},		//N
								{0,0,1,1,1,0,1,0},		//O	
								{1,1,0,0,1,1,1,0},		//P
								{1,1,1,0,0,1,1,0},		//Q
								{0,0,0,0,1,0,1,0},		//R
								{1,0,1,1,0,1,1,0},		//S
								{0,0,0,1,1,1,1,0},		//T	
								{0,1,1,1,1,1,0,0},		//U
								{0,1,1,1,1,1,0,0},		//V
								{0,1,0,1,0,1,1,0},		//W
								{0,0,1,0,0,0,0,0},		//X
								{0,1,1,1,0,1,1,0},		//Y
								{1,0,0,1,0,0,1,0},		//Z
								{1,1,1,1,1,1,1,1},		//[
								{0,0,0,0,0,0,1,0},		//]  {0,0,0,0,0,0,1,0} 
							};
							

void Display(void)
{   
    if(dispdigit == 1)	    
	{
	    DECODENLAT=1;
		DECODALAT=0;  //A=0
        DECODBLAT=0;  //B=0
        DECODCLAT=0;  //C=0
        
        latchdata(diswin1[0]);	
        
       	if(Typedp.digitdp1==1)
       		SEGDPLAT=1;			//SEGDP=1;
       	else
        	SEGDPLAT=0;			//SEGDP=0; 	
        
        DECODENLAT=0;
		dispdigit++;
	 }
	 else if(dispdigit == 2)	    
	 {
	    DECODENLAT=1;
		DECODALAT=1;  //A=0
        DECODBLAT=0;  //B=0
        DECODCLAT=0;  //C=0
        latchdata(diswin1[1]);	
        
        if(Typedp.digitdp2==1)
       		SEGDPLAT=1;			//SEGDP=1;
        else
        	SEGDPLAT=0;			//SEGDP=0; 	
        DECODENLAT=0;
        dispdigit++;
	 }
	 else if(dispdigit == 3)	    
	 {
	    DECODENLAT=1;
		DECODALAT=0;  //A=0
        DECODBLAT=1;  //B=0
        DECODCLAT=0;  //C=0
        
        latchdata(diswin1[2]);	
        
        if(Typedp.digitdp3==1)
       		SEGDPLAT=1;//SEGDP=1;
        else
        	SEGDPLAT=0;	//SEGDP=0; 	
        	
        DECODENLAT=0;
        dispdigit++;
	 }
	 else if(dispdigit == 4)	    
	 {
	    DECODENLAT=1;
		DECODALAT=1;  //A=0
        DECODBLAT=1;  //B=0
        DECODCLAT=0;  //C=0
        
        latchdata(diswin1[3]);	
        
        if(Typedp.digitdp4==1)
       		SEGDPLAT=1;//SEGDP=1;
        else
        	SEGDPLAT=0;	//SEGDP=0; 	
        	
        DECODENLAT=0;
        dispdigit++;
	 }
	 else if(dispdigit == 5)	    
	 {
	    DECODENLAT=1;
		DECODALAT=0;  		//A=0
        DECODBLAT=0;  		//B=0
        DECODCLAT=1;  		//C=0
        
        latchdata(diswin1[4]);	
        if(Typedp.digitdp5==1)
       		SEGDPLAT=1;		//SEGDP=1;
        else
        	SEGDPLAT=0;		//SEGDP=0; 	
        	
        DECODENLAT=0;
        dispdigit++;
	 }
	 else if(dispdigit == 6)	    
	 {
	    DECODENLAT=1;
		DECODALAT=1;  		//A=0
        DECODBLAT=0;  		//B=0
        DECODCLAT=1;  		//C=0
        
        latchdata(diswin1[5]);	
       	if(Typedp.digitdp6==1)
       		SEGDPLAT=1;		//SEGDP=1;
       	else
        	SEGDPLAT=0;		//SEGDP=0;
        	 	
        DECODENLAT=0;
        dispdigit++;
	  } 
   	else if(dispdigit == 7)
   	{
        // DECODE_A=0;
         //DECODE_B=1;
         //DECODE_C=1;
         //PORTB=0x00;//Displayarr[diswin1[digit]];
        DECODENLAT	=1;
        DECODALAT	=0;  //A=0
     	DECODBLAT	=1;  //B=0
     	DECODCLAT	=1;  //C=0
     	latchdata(TypeU.LEDGROUP[0]);	
         //OUTPORTB=TypeU.LEDGROUP[0];//0x0F;//Displayarr[diswin1[digit]];
        DECODENLAT=0;
        dispdigit++;
     }
     else if(dispdigit == 8)
     {
           //DECODE_A=1;
           //DECODE_B=1;
           //DECODE_C=1;
           //PORTB=0xFF;//Displayarr[diswin1[digit]];
        DECODENLAT=1;
        DECODALAT=1;  //A=0
       	DECODBLAT=1;  //B=0
       	DECODCLAT=1;  //C=0
       	latchdata(TypeU.LEDGROUP[1]);
       	DECODENLAT=0;
       //OUTPORTB=TypeU.LEDGROUP[1];//0x00;//Displayarr[diswin1[digit]];
       //TRISB=0X0F; 
        dispdigit++;
      }
     else if(dispdigit == 9)
	  {
		//DECODENLAT	=1;
		Delay_us(5);
		SEGALAT=1;
		Delay_us(25);
		SEGAIO=1;
		Delay_us(25);
		
		if(SEGA==0)
		{
			dVal1=0;
			if(++dVal0>=DEBOUNCE)
			{
				temp1=SEGA;
				if((!temp1)&&(!temp2)&&(!temp3)&&(!temp4))
					key=key_no;
					
				dVal0=DEBOUNCE;
			}	
		}
		else if(SEGA==1)
		{
			dVal0=0;
			if(++dVal1>=DEBOUNCE)
			{
				key=key_gason;
				dVal1=DEBOUNCE;	
				temp1=SEGA;	
			}
		}
		
		SEGAIO=0;
		Nop();
		SEGALAT=0;
		dispdigit++;
	}
	else if(dispdigit==10)
	{
		//Delay_us(5);	
		SEGBLAT=1;
		Delay_us(25);
		SEGBIO=1;
		Delay_us(25);
			
		if(SEGB==0)
		{
			dVal3=0;
			if(++dVal2>=DEBOUNCE)
			{
				temp2=SEGB;
				if((!temp1)&&(!temp2)&&(!temp3)&&(!temp4))
					key=key_no;
					
				dVal2=DEBOUNCE;
			}
		}
		else if(SEGB==1)
		{
			dVal2=0;
			if(++dVal3>=DEBOUNCE)
			{
				key=key_inch;
				dVal3=DEBOUNCE;
				temp2=SEGB;
			}
		}
		SEGBIO=0;
		Nop();
		SEGBLAT=0;
		dispdigit++;
	}
	else if(dispdigit==11)
	{
		//Delay_us(5);
		SEGCLAT=1;
		Delay_us(25);
		SEGCIO=1;
		Delay_us(25);
				
		if(SEGC==0)
		{
			dVal5=0;
			if(++dVal4>=DEBOUNCE)
			{
				temp3=SEGC;	
				if((!temp1)&&(!temp2)&&(!temp3)&&(!temp4))	
					key=key_no;
				dVal4=DEBOUNCE;
			}
		}
		else if(SEGC==1)
		{
			dVal4=0;
			if(++dVal5>=DEBOUNCE)
			{	
				key=key_mode;
				dVal5=DEBOUNCE;
				temp3=SEGC;
			}
		}
		
		SEGCIO=0;
		Nop();
		SEGCLAT=0;
		dispdigit++;
	}
	else if(dispdigit==12)
	{
		SEGDLAT=1;
		Delay_us(25);
		SEGDIO=1;
		Delay_us(25);
			
		if(SEGD==0)
		{
			dVal7=0;
			if(++dVal6>=DEBOUNCE)
			{
				temp4=SEGD;
				if((!temp1)&&(!temp2)&&(!temp3)&&(!temp4))
					key=key_no;
				dVal6=DEBOUNCE;
			}
		}
		else if(SEGD==1)
		{
			dVal6=0;
			if(++dVal7>=DEBOUNCE)
			{
				key=key_disp;
				dVal7=DEBOUNCE;
				temp4=SEGD;
			}
		}
		SEGDIO=0;
		Nop();
		Delay_us(25);
		SEGDLAT=0;
		dispdigit++;
	}
        /*else if(dispdigit == 9)
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
        }*/
        
      if(dispdigit>12)
       	dispdigit=1;
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
////    SEGD=arr[3];
////    SEGE=arr[4];
////   	SEGF=arr[5];
////   	SEGG=arr[6];
////   	SEGDP=arr[7];
//////
//
//  // PORTB=Displayarr[num];
//}

void latchdata(unsigned char num)
{
	
	unsigned char tempdisplay=0,j=0; 
				 
	tempdisplay=num;
	if(dispdigit<=6)
	{
 		num=(num-0x2F);
 		
 		for(j=0;j<8;j++)
 		{
		 	arr[j]=lookup_table[num][j];
 		} 		
		SEGALAT =arr[0];	
		SEGBLAT =arr[1];
		SEGCLAT =arr[2];
		SEGDLAT =arr[3];
		SEGELAT =arr[4];
		SEGFLAT =arr[5];
		if((Type.arclength==1)&&(dispdigit == 4))
			SEGGLAT =1;
		else
			SEGGLAT =arr[6];	
		//SEGDPLAT=arr[7];
	}
	else
	{
		SEGALAT =tempdisplay;
		SEGBLAT =tempdisplay>>1;
		SEGCLAT =tempdisplay>>2;
		SEGDLAT =tempdisplay>>3;
		SEGELAT =tempdisplay>>4;
		SEGFLAT =tempdisplay>>5;
		SEGGLAT =tempdisplay>>6;
		//SEGDPLAT=tempdisplay>>7;
	}		
}

void disp_hex_window1(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
 
     diswin1[2]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     diswin1[1]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     diswin1[0]= 0x30 + (hex_data % 10);   
}

void disp_hex_window2(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
     diswin1[5]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     diswin1[4]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     diswin1[3]= 0x30 + (hex_data % 10);
     diswin1[6]=0x00;
     diswin1[7]=0x00;
}

void disp_hex_window11(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
  /*   diswin1[2]= hex_data % 10;
     hex_data /= 10;
     diswin1[1]= hex_data % 10;
     hex_data /= 10;
     diswin1[0]= hex_data % 10;
   */
}

void disp_hex_window22(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
  /*  diswin1[5]= hex_data % 10;
     hex_data /= 10;
     diswin1[4]= hex_data % 10;
     hex_data /= 10;
     diswin1[3]= hex_data % 10;
     diswin1[6]=0x00;
     diswin1[7]=0x00;
  */
}

void Delayms(unsigned int delay)
{
   unsigned int yyy=0,xxx=0;
   for(xxx=0;xxx<delay;xxx++)          //50 ms delay
   {
       for(yyy=0;yyy<138;yyy++);       // 1 msec delay
   }
}



