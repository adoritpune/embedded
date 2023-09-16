
/*#int_timer0
void timer0_isr(void)
{
    static unsigned int count3=0;
    clear_interrupt(INT_TIMER0);
    set_timer0(0xFC40);              //sets timer to interrupt in 6ms
    count3++;
     if(count3==10)
        {
            count3=0;
            readswitch1=1;
        }
}*/

#int_timer1
void timer1_isr(void)
{
    static unsigned char count=0,count1=0,count2=0;
    clear_interrupt(INT_TIMER1);
    set_timer1(0xFC40);            //FC40 for 500usec at 8mhz
    count++;
    count1++;
    count2++;

    /*if(pinout==0)
     {
         pinout=1;
         output_a(0X00);
         //MCU_PORTA=0X00;
     }
     else if(pinout==1)
     {
         pinout=0;
         output_a(0xff);
         //MCU_PORTA=0XFF;
     }*/
   if(count>=5)  //10
   {
         count=0;
         //inttochar(voltage);
         display();
   }
   if(count1>=2)
   {
      count1=0;
      readadcf=1;
   }
   if(noocvf==1)
   {
      count3++;
      if(count3>=200)
      {
         count3=0;
         cnt4sec++;
      }
   }
  /* if(count2==10)
   {
      count2=0;
      readswitch1=1;
   }*/
   if(arconrstf>=1)
   {
      arconrstcnt++;
      rstcnt++;
   }
   if(weldon==1)
   {
      timecnt++;
      //blinkcnt++;
      if(timecnt>=2000)//2000
      {
         timecnt=0;
         sec++;
         if(arconf==1)
         {
            //blinkcnt=0;
            if(setarcdp==1)
            {
               setarcdp=0;
               setdp=0;
               setdp1=0;
            }
            else
            {
               setarcdp=1;
               setdp=1;
               setdp1=1;
            }
         }
      }
      if(sec>=60)
      {
         sec=0;
         min++;
      }
      if(min>=60)
      {
         min=0;
         hr++;
         if(hr>99)
         {
            hr=0;
         }
      }
      /*if(blinkcnt>=2000 && arconf==1)
      {
         blinkcnt=0;
         if(setarcdp==1)
         {
            setarcdp=0;
            setdp=0;
            setdp1=0;
         }
         else
         {
            setarcdp=1;
            setdp=1;
            setdp1=1;
         }

      }*/
   }

}

