//*****************************************************************************************************
//SOFTWARE REV.NO:00   ** PCB N0:-PA9/513/A
//************************************MODIFICATION DETAILS*********************************************
//DATE:          //MODIFICATION NOTE NO.:          //DONE BY:




//*****************************************************************************************************
//#include "D:\TDC\MAHESH\MAESTRO_1200\POWERSOURCE\REMOTE\rev0.h"
//#include "D:\suresh\SAW POWER SOURCE NEW\Remote\Working\rev0.h"
#include <rev0.h>
#use delay(clock=8000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7) //baud rate modified mahesh 22.05.2015
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7) //baud rate modified saurabh 10.01.2020
//------------------------------------------------------------------------------
#byte MCU_STATUS = 0x003
#bit    MCU_C = MCU_STATUS.0
#bit    MCU_DC = MCU_STATUS.1
#bit    MCU_Z = MCU_STATUS.2
#bit    MCU_PD = MCU_STATUS.3
#bit    MCU_TO = MCU_STATUS.4
#bit    MCU_RP0 = MCU_STATUS.5
#bit    MCU_RP1 = MCU_STATUS.6
#bit    MCU_IRP = MCU_STATUS.7
#byte MCU_PORTA = 0x005
#byte MCU_PORTB = 0x006
#byte MCU_PORTC = 0x007
#byte MCU_PORTD = 0x008
#byte MCU_PORTE = 0x009
#bit    MCU_RE0 = MCU_PORTE.0
#bit    MCU_RE1 = MCU_PORTE.1
#bit    MCU_RE2 = MCU_PORTE.2
#byte MCU_INTCON = 0x00B
#bit    MCU_RBIF = MCU_INTCON.0
#bit    MCU_INTF = MCU_INTCON.1
#bit    MCU_T0IF = MCU_INTCON.2
#bit    MCU_RBIE = MCU_INTCON.3
#bit    MCU_INTE = MCU_INTCON.4
#bit    MCU_T0IE = MCU_INTCON.5
#bit    MCU_PEIE = MCU_INTCON.6
#bit    MCU_GIE = MCU_INTCON.7
#byte MCU_PIR1 = 0x00C
#bit    MCU_TMR1IF = MCU_PIR1.0
#bit    MCU_TMR2IF = MCU_PIR1.1
#bit    MCU_CCP1IF = MCU_PIR1.2
#bit    MCU_SSPIF = MCU_PIR1.3
#bit    MCU_TXIF = MCU_PIR1.4
#bit    MCU_RCIF = MCU_PIR1.5
#bit    MCU_ADIF = MCU_PIR1.6
#bit    MCU_PSPIF = MCU_PIR1.7
#byte MCU_OPTION_REG = 0x181
#bit    MCU_PS0 = MCU_OPTION_REG.0
#bit    MCU_PS1 = MCU_OPTION_REG.1
#bit    MCU_PS2 = MCU_OPTION_REG.2
#bit    MCU_PSA = MCU_OPTION_REG.3
#bit    MCU_T0SE = MCU_OPTION_REG.4
#bit    MCU_T0CS = MCU_OPTION_REG.5
#bit    MCU_INTEDG = MCU_OPTION_REG.6
#bit    MCU_RBPU = MCU_OPTION_REG.7
#byte MCU_ANSEL = 0x188
#bit    MCU_ANSELANSO = MCU_ANSEL.0
#bit    MCU_ANSELANS1 = MCU_ANSEL.1
#bit    MCU_ANSELANS2 = MCU_ANSEL.2
#bit    MCU_ANSELANS3 = MCU_ANSEL.3
#bit    MCU_ANSELANS4 = MCU_ANSEL.4
#bit    MCU_ANSELANS5 = MCU_ANSEL.5
#bit    MCU_ANSELANS6 = MCU_ANSEL.6
#bit    MCU_ANSELANS7 = MCU_ANSEL.7
#byte MCU_ANSELH = 0x189
#bit    MCU_ANSELHANS8 = MCU_ANSELH.0
#bit    MCU_ANSELHANS9 = MCU_ANSELH.1
#bit    MCU_ANSELHANS10 = MCU_ANSELH.2
#bit    MCU_ANSELHANS11 = MCU_ANSELH.3
#byte MCU_OSCCON = 0x08F
#byte MCU_OSCTUNE= 0x090

#fuses HS,NOWDT,NOLVP,INTRC_IO,NOWDT,NOMCLR
//------------------------------------------------------------------------------
void transmit(unsigned int16);
void readadc(void);
unsigned char aaa=0;
unsigned int16 value=0,current_count=0,prevcurrent_count=0,error1=0,setcurrent=0,psetcurrent=0;
unsigned char transchksum=0,adccnt=0,readadcf=0,bk,bk1;
//------------------------------------------------------------------------------
#int_timer1
void timer1_isr(void)
{
    clear_interrupt(INT_TIMER1);
    set_timer1(0xFC40);
    adccnt++;
    if(adccnt>=1)
    {
      adccnt=0;
      readadcf=1;
    }
}

#int_timer2
void timer2_isr(void)
{
  MCU_TMR2IF=0;
}

//------------------------------------------------------------------------------
void initialize(void)
{
    #asm
         CLRF  MCU_ANSEL ;      //0-i/o,1-analog
         CLRF  MCU_ANSELH ;
         ;
         BCF   MCU_RP1;
         BCF   MCU_RP0;
         ;
         BCF   MCU_RP1;
         BSF   MCU_RP0;
         MOVLW  0xff
         MOVWF  0X90
         MOVLW  0x73
         MOVWF  0X8F
         BCF   MCU_RP1;
         BCF   MCU_RP0;
    #endasm
         setup_adc_ports(NO_ANALOGS|VSS_VDD);
         setup_comparator(NC_NC_NC_NC);
         setup_adc(ADC_CLOCK_INTERNAL  );
         enable_interrupts(global);
         setup_timer_1(T1_DISABLED);
         setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
         set_timer1(0xFC00);
         disable_interrupts(INT_RDA);
         enable_interrupts(INT_TIMER1);
         disable_interrupts(INT_RDA);
}
//------------------------------------------------------------------------------
void main()
{
    enable_interrupts(global);
    for(bk=0;bk<25;bk++)
    for(bk1=0;bk1<250;bk1++);
    initialize();
    disable_interrupts(INT_RDA);
    for(bk=0;bk<50;bk++);
    //for(bk1=0;bk1<250;bk1++);
    for(bk=0;bk<50;bk++);
    set_tris_a(0x03);

    while(1)
    {
       if(readadcf==1)
         {
           readadcf=0;
           readadc();
         }
    }//WHILE
}//VOID
//------------------------------------------------------------------------------
// read analog reference =======================================================
void readadc()
{
    static unsigned int32 current=0,adccntr=0;//
    set_adc_channel(0);
    for(aaa=0;aaa<=100;aaa++);                           //delay_us(20);
    value=read_adc();                                    // maincurrent read CN4. JP1 2-3
    current= current + value;
    value=0;
    ;

    adccntr++;
    if(adccntr >=128)
    {
      current_count=current>>7;
      current = 0;
      adccntr   = 0;
      {
      if(current_count >= 750)//905)
         current_count=750;//905;
      }
      ;
      {
      if(prevcurrent_count > current_count)
          error1=prevcurrent_count - current_count;
      else if (current_count > prevcurrent_count)
          error1=current_count -  prevcurrent_count;
              if(current_count==prevcurrent_count)
                 error1=0;
      }

         if (error1>2)
            {
             setcurrent=(current_count*5.4)/5.0;//4)/3;
             if(setcurrent<=100)
                setcurrent=100;
             if(setcurrent>=800)
                setcurrent=800;
             psetcurrent = setcurrent;
             transmit(setcurrent);
            }
         else
            {
              transmit(psetcurrent);
            }
      }//adccntr
 }
//==============================================================================
void transmit(unsigned int16 transdata)
{
 unsigned char higher=0,lower=0;
 lower=transdata;
 higher=transdata >>8;
 transchksum=0;
 putchar('$');
 putchar('%');
 transchksum=transchksum +'%';
 putchar(lower);
 transchksum=transchksum + lower;
 putchar(higher);
 transchksum=transchksum + higher;
 //transchksum=transchksum +'M';
 putchar(transchksum);
 transchksum=0;
}
//==============================================================================
