
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
    static unsigned char count=0,count1=0;
    clear_interrupt(INT_TIMER1);
    set_timer1(0xFC40);            //FC40 for 500usec at 8mhz
    count++;
    count1++;



   if(count>=5)  //10
   {
         count=0;
         display();
   }
   if(count1>=2)
   {
      count1=0;
      readadcf=1;
   }





}

