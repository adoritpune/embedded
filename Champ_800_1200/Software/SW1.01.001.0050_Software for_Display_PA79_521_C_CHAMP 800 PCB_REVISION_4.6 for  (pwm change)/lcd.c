void lcd_int()
{
    int j;
    //TRISD=0;
    LCDAIO=0;
    LCDBIO=0;
	LCDCIO=0;
	LCDDIO=0;
	LCDEIO=0;
	LCDFIO=0;
	LCDGIO=0;
	LCDHIO=0;
    LCDRSIO=0;  
    LCDENIO=0;
    LCDENLAT=0;
    delay(300);
    lcdcmd(0X38);
    delay(300);       // 300 msec delaY
    lcdcmd(0X01);                    
    delay(20);
    lcdcmd(0X0E);
    delay(20);
    lcdcmd(0X06);
    delay(20);
    //char arr[]={"ADOR  WELDING"};
    //char arrr[]={"LIMITED"};
    //char arrrr[]={"SAW  WELDING HEAD"};
    //lcdcmd(0X81);
    //for(j=0;j<=11;j++)
    { 
      // lcddata(arr[j]);
	}
    //delay(32000);
    lcd();
 	

}
    

void lcdcmd(unsigned char value)
{	
  
	 unsigned int k;
	 k=((value << 2)& 0X03FC) ;
	 LATD=k;
	 LCDRSLAT=0;
	 LCDENLAT=1;
	 delay(10);
	 LCDENLAT=0;
	 LATD=0x0000;

}
void lcddata(unsigned char value)
{
   
	 unsigned int k;
	 k=((value << 2)& 0X03FC) ;
	 LATD= k;
	 LCDRSLAT=1;
	 LCDENLAT=1;
	 delay(10);
	 LCDENLAT=0;
	 LATD=0x0000;
 
}
void delay(unsigned int time)          //delay to t milli sec
{
        unsigned int i, j;
        for (i = 0; i < time; i++)
                for(j=0;j<200;j++);   //6000gives a delay of 1msec   
            
}                
 
void lcd() 
{
   int i;
   lcdcmd(0X81);   
   delay(10);
   for(i=0;i<=14;i++)
    { 
       lcddata(curr[i]);
	}
   lcdcmd(0XC1);
   delay(10);
   for(i=0;i<=14;i++)
    {
	  lcddata(volt[i]);
	}
   lcdcmd(0X91);
   delay(10);
   for(i=0;i<=15;i++)
    {
	   lcddata(cs[i]);   
	}
   lcdcmd(0XD1);
   delay(10);
   for(i=0;i<=14;i++)
    {
	   lcddata(wire[i]);
	}
   lcdcmd(0X80);
   //lcddata('>');
   delay(10);
   
}              
void lcdscan()
{
     int i;
     encod1=scanencoder1();
 //*******************************************************
  if(encod1!='$' && eswitch==0)
     {
        if(encod1=='+')// && prevstatus>4)
           {  //if(prevstatus>2) 
	          if(line<4 && prevstatus>4)      
               {
	              line+=1;
                  prevstatus=0; 
	           }
              else if(line>=4 && prevstatus>4)
               {
	              line=1;
	              prevstatus=0;
               } 
              prevstatus++;
           }
        else if(encod1=='-')// && prevstatus>4) 
           {
	          if(line>1 && prevstatus>4) 
                {
	              line-=1;
                  prevstatus=0; 
	            }  
              else if(line<=1 && prevstatus>4)
                {
	              line=4;
	              prevstatus=0;
                }
              prevstatus++;
           }   
     }
           
  else
    {
       line=line;
    }
  //********************************************************  
 if(line==1 && eswitch==0)// && prevstatus==1)
 {
  lcdcmd(0X80);
  lcdcmd(0X0E);
  onoff_flag=0;
  delay(10);
 }
  else if(line==2 && eswitch==0)
  {
   lcdcmd(0XC0);
   delay(10);
   lcdcmd(0X0E);
   onoff_flag=0;
   delay(10);
   //LCDGLAT=0;
  }
 else if(line==3 && eswitch==0)
  {
   lcdcmd(0X90);
   delay(10);
   lcdcmd(0X0E);
   onoff_flag=0;
   delay(10);
  }
 else if(line==4 && eswitch==0)
  {
   lcdcmd(0XD0);
   delay(10);
   lcdcmd(0X0E);
   onoff_flag=0;
   delay(10);
 }
 //*********************************************************** 
  if(line==1 && eswitch==1)
	    {
		    //lcdcmd(0X88);
	        lcdcmd(0X0E);
	        if(onoff_flag==1)
	        onoff_flag=0;
	        else if(onoff_flag==0)
	        onoff_flag=1;
	     delay(10);
	     if(encod1!='$')
	         {
			     if(encod1=='+' && setcurrent<iSetcurrbuff)
			     { 
		           setcurrent=setcurrent+1; 
                   
		         }
		         
			     else if(encod1=='-' && setcurrent>iSetmincurrbuff)
			     { 
		           setcurrent=setcurrent-1;
              
		         }
	         }     
		     
		  else  
			 {
			    setcurrent=setcurrent;
			 }
          
	    }
       
   else if(line==2 && eswitch==1)
		    {
			   if(onoff_flag==1)
	        onoff_flag=0;
	        else if(onoff_flag==0)
	        onoff_flag=1;
		     lcdcmd(0X0E);
		     //lcdcmd(0X0C);
		     delay(10);
		     if(encod1 != '$')
			     {
				     if(encod1=='+' && setvoltage<440)
				     { 
			           setvoltage=setvoltage+1;
			         }
				     else if(encod1=='-' && setvoltage>=51)
				     { 
			           setvoltage=setvoltage-1;
			         }
		         }    
				    else 
				     {
				      setvoltage=setvoltage;
				     }
		    }

   else if(line==3 && eswitch==1)
		    {
                if(onoff_flag==1)
	        onoff_flag=0;
	        else if(onoff_flag==0)
	        onoff_flag=1;
			    lcdcmd(0X0E);
		     //lcdcmd(0X0C);
		     delay(10);
			    if(encod1 != '$')
				     {
					     if(encod1 =='+' && setcarrspeed<160)
					     { 
				            setcarrspeed=setcarrspeed+1;
				         }
					     else if(encod1 =='-' && setcarrspeed>10)
					     { 
				           setcarrspeed=setcarrspeed-1;
				         }
			         }    
					    else 
					     {
					       setcarrspeed=setcarrspeed;
			               
					     }
		    }

   else if(line==4 && eswitch==1)
		    {
			    if(onoff_flag==1)
	        onoff_flag=0;
	        else if(onoff_flag==0)
	        onoff_flag=1;
		     lcdcmd(0X0E);
		     //lcdcmd(0X0C);
		     delay(10);
		     if(encod1 != '$')
			     {
				     if(encod1=='+' && settime<10)
				     { 
			           settime=settime+1;
			         }
				     else if(encod1=='-' && settime>=1)
				     { 
			           settime=settime-1;
			         }
		         }    
				    else 
				     {
				      settime=settime;
				     }
		    }

          wirehex_dec=settime;
          wire[10]=0X30+wirehex_dec/10;
          wire[11]=0X30+wirehex_dec%10;
          lcdscan_flag=1;

}


    