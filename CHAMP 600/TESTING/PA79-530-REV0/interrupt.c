
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
   if(count==10)
   {
         count=0;
         //inttochar(voltage);
         display();
   }
   if(count1==2)
   {
      count1=0;
      readadcf=1;
   }
  /* if(count2==10)
   {
      count2=0;
      readswitch1=1;
   }*/

}

