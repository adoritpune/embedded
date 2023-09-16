#include "curandref.h"
//#include "D:\PRIYANKA\PROJECT\DPM\current&ref\DPM.h"
#include "controller.c"
#include "variable.c"
#include "interrupt.c"
#include "display.c"

//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7)


void main()
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
      initialise();
      adc_init();
  // current=000;
  // inttochar1(current);
   //set_tris_a(0x38);
   set_tris_a(0x38);
   set_tris_b(0x10);//(0x00);
   set_tris_c(0x00);

   //short_del();
   delay_ms(2);
   //voltage=985;
   //inttochar(voltage);
   //inttochar1(voltage);

   digit[0]='D'- 0x30;;
   digit[1]='O'- 0x30;
   digit[2]='R'- 0x30;
   digit[3]='A'- 0x30;
   delay_ms(100);
   delay_ms(100);
   model= readswitch();
   dispmodel();
   delay_ms(100);
   delay_ms(100);
   //mma=1;
   while(1)
   {

             if(readadcf==1)
             {
                   readadc();
                   readadcf=0;
             }

              if(weldon==1)
              {
                if(prevcur!=current)
                 {
                    inttochar1(current);
                    prevcur=current;
                    prevref=0;
                 }
              }
              else
              {
                 if(prevref!=ref)
                 {
                    inttochar1(ref);
                    prevref=ref;
                    prevcur=0;
                 }
              }
   }//while
}//main

void inttochar1(unsigned int16 parameter)
{
   if(model=='G' || model=='H')
   {
      digit[2]=parameter % 10;//;//0;//'0';
      parameter /= 10;
      digit[1] = parameter % 10;
      parameter /= 10;
      digit[0] = parameter % 10;
      parameter /= 10;
      digit[3] = parameter;
   }
   else
   {
      digit[3]=0;
      digit[2] = parameter % 10;
      parameter /= 10;
      digit[1] = parameter % 10;
      parameter /= 10;
      digit[0] = parameter;
   }
}
void inttochar(unsigned int16 parameter)
{
   digit[0]='A'- 0x30;;
   digit[1]='D' - 0x30;
   digit[2]='O' - 0x30;
   digit[3]='R' - 0x30;
}

void short_del()
{
  unsigned int16 i=0,j=0;
  for(i=0;i<100;i++)
  {
     for(j=0;j<30;j++);
  }
}

void initialise()
{
         setup_adc_ports(NO_ANALOGS|VSS_VDD);
         setup_comparator(NC_NC_NC_NC);
         setup_adc(ADC_CLOCK_INTERNAL  );
         enable_interrupts(GLOBAL);
         enable_interrupts(INT_TIMER1);
         setup_timer_0(T1_DISABLED);
         setup_timer_1(T1_DISABLED);
         setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
         disable_interrupts(INT_EXT);
         set_timer0(0x0f);
         set_timer1(0xFC40);
}
//==============================================================================
void adc_init()
{
   setup_adc_ports(sAN0|sAN1|sAN2|VSS_VDD);
     //setup_adc_ports(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL );
   //set_adc_channel(0);
}
//------------------------------------------------------------------------------
const unsigned char lookup_table[45] = {
                                     //{dp,g,f,e,d,c,b,a}
                                     0x3F,   //0
                                     0x06,   //1
                                     0x5B,   //2
                                     0x4F,   //3
                                     0x66,   //4
                                     0x6D,   //5
                                     0x7D,   //6
                                     0x07,   //7
                                     0x7F,   //8
                                     0x6F,   //9
                                     0x00,   //3A Blank
                                     0x00,   //3B Blank
                                     0x00,   //3C Blank
                                     0x00,   //3D Blank
                                     0x00,   //3E Blank
                                     0x00,   //3F Blank
                                     0x00,   //40 Blank
                                     0x77,   //A
                                     0x7C,   //B
                                     0x39,   //C
                                     0x5E,   //D
                                     0x79,   //E
                                     0x71,   //F
                                     0x3D,   //G
                                     0x76,   //H
                                     0x03,   //I
                                     0x1E,   //J
                                     0x70,   //K
                                     0x38,   //L
                                     0x55,   //M
                                     0x54,   //N
                                     0x5C,   //O
                                     0x73,   //P
                                     0x67,   //Q
                                     0x50,   //R
                                     0x6D,   //S
                                     0x78,   //T
                                     0x3E,   //U
                                     0x1C    //V
                                     0x6A,   //W
                                     0x68,   //X
                                     0x6E,   //Y
                                     0x89,   //Z
                                     };
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void display()
{
   if(digitcnt==0)
   {
     OUTPUT_BIT(disp4,0);
     //digit[0]=5;
     hexvalue=lookup_table[digit[2]];
     output_c(hexvalue);
     //set_tris_b(0x01);
     OUTPUT_BIT(disp1,1);
     OUTPUT_BIT(disp2,0);
     OUTPUT_BIT(disp3,0);
     OUTPUT_BIT(disp4,0);
     digitcnt++;
   }
   else if(digitcnt==1)
   {
     OUTPUT_BIT(disp1,0);
      //digit[1]=8;
      hexvalue =lookup_table[digit[1]];
     output_c(hexvalue);
     //set_tris_b(0x01);
     OUTPUT_BIT(disp1,0);
     OUTPUT_BIT(disp2,1);
     OUTPUT_BIT(disp3,0);
     OUTPUT_BIT(disp4,0);
     digitcnt++;// ++;
   }
   else if(digitcnt==2)
   {
     OUTPUT_BIT(disp2,0);
      //digit[2]=7;
     hexvalue = lookup_table[digit[0]];
     output_c(hexvalue);
     //set_tris_b(0x01);
     OUTPUT_BIT(disp1,0);
     OUTPUT_BIT(disp2,0);
     OUTPUT_BIT(disp3,1);
     OUTPUT_BIT(disp4,0);
     digitcnt++;
   }
   else if(digitcnt==3)
   {
     OUTPUT_BIT(disp3,0);
     //digit[3]=6;
     hexvalue = lookup_table[digit[3]];
     output_c(hexvalue);
     //set_tris_b(0x01);
     OUTPUT_BIT(disp1,0);
     OUTPUT_BIT(disp2,0);
     OUTPUT_BIT(disp3,0);
     OUTPUT_BIT(disp4,1);
     digitcnt=0;
   }
}


void readadc()
{
    static unsigned int32 totalcur=0,totalvtg=0,adccntr=0,totalref=0;//
    /*set_adc_channel(0);
    delay_us(10);
    value=read_adc();
    totalvtg= totalvtg + value;
    ;*/
    set_adc_channel(0);
    delay_us(5);
    value=read_adc();
    totalcur= totalcur + value;
    ;
    set_adc_channel(2);
    delay_us(10);
    value=read_adc();
    totalref= totalref + value;
    ;
    {
       setup_adc_ports(ALL_ANALOG);
       set_adc_channel(11);
       delay_us(10);
       value=read_adc();
       offset1=value;
       setup_adc_ports(sAN0|sAN1|sAN2|VSS_VDD);

    }

    adccntr++;

    if(adccntr >=256)//128)
    {
         cur=totalcur>>8;
         calcur=(cur*maxshunt)/maxadc;
      //calcur=(cur*400)/590;  //580;

      //#####################################################

        ref2=totalref>>8;

        if(ref2<=120) //110
         {
            ref=10.0;
         }
         else
         {
             errorp=ref2;
             errorp=errorp/4.616;   //4.616
             offset=constant-errorp;
             ref=ref2-offset;
             ref=ref-refoffset;
             //ref=(ref*40)/57;
             ref=ref/0.9;         //   //1.05

         }
         if(ref<=10.0)
         {
            ref=10.0;
         }

        /* if(ref>=400)
         {
            ref=400;
         }*/

     if(offsetokf==0)
      {
         offcnt++;
         if(offcnt==3)
         {
            offsetokf=1;
            offcnt=0;
            curoffset=calcur;

         }
         else
         {
           current=1;//curoffset;
         }
      }
      else
      {
         if(calcur >= curoffset)
         {
            current=calcur-curoffset;

            if(current >= 10.0)
            {
               weldon=1;                  //welding started...
            }
            else
            {
               weldon=0;
            }
         }
         else
         {
            current=1;
            weldon=0;
         }
      }

      totalvtg=0;
      totalcur=0;
      adccntr=0;
      totalref=0;
      //inttochar1(current);
      //printf("%lx",current);
      //putchar(0x0D);
      //putchar(0x0A);
    }
  }

//=========================
 unsigned char chk_band(unsigned int16 cur11,unsigned int16 prevcur11)
 {
     unsigned int16 diff=0;
     unsigned char ans=0;
     {
        if(cur11 >= prevcur11)
        {
            diff= cur11 - prevcur11;
        }
        else
        {
            diff= prevcur11 - cur11;
        }
     }
     if(diff >=2)
     {ans='Y';}
     else
     {ans='N';}
     return(ans);
 }

//=========================

unsigned char readswitch()
{
   unsigned char data=0,data1=0;
   data=input_a();
   data=data & 0x38;
   data=data>>3;
   delay_us(200);
   data1=input_a();
   data1=data1 & 0x38;
   data1=data1>>3;
   if(data==data1)
   {
      if(data==0x00)
      {range='A';}
      else if(data==0x01)
      {range='B';}
      else if(data==0x02)
      {range='C';}
      else if(data==0x03)
      {range='D';}
      else if(data==0x04)
      {range='E';}
      else if(data==0x05)
      {range='F';}
      else if(data==0x06)
      {range='G';}
      else if(data==0x07)
      {range='H';}
   }
 return(range);
}

/*void mmatigsw()
{
  unsigned char A;
   A=input(PIN_B5);
   if(A==1)
   {
      mma=1;
   }   
   else
   {
      mma=0;
   }
}*/

void debounce()
{
    for(jj=0;jj<255;jj++);
}

/*void readmem(void)
{
  lowbyte=read_eeprom(0x00);   //priyanka
  vrefmaxcnt1=lowbyte;
  hibyte=read_eeprom(0x01);
  vrefmaxcnt=(hibyte*256)+vrefmaxcnt1;
}*/
void dispmodel()
{
   if(model=='A')
   {
      digit[0]='2'- 0x30;;
      digit[1]='5'- 0x30;
      digit[2]='0'- 0x30;
      digit[3]='C'- 0x30;
      maxadc=625;
      maxshunt=250;
   }
   else if(model=='B')
   {
      digit[0]='3'- 0x30;;
      digit[1]='0'- 0x30;
      digit[2]='0'- 0x30;
      digit[3]='C'- 0x30;
      maxadc=625;
      maxshunt=300;
   }
   else if(model=='C')
   {
      digit[0]='4'- 0x30;;
      digit[1]='0'- 0x30;
      digit[2]='0'- 0x30;
      digit[3]='C'- 0x30;
      maxadc=625;
      maxshunt=400;
   }
   else if(model=='D')
   {
      digit[0]='5'- 0x30;;
      digit[1]='0'- 0x30;
      digit[2]='0'- 0x30;
      digit[3]='C'- 0x30;
      maxadc=625;
      maxshunt=500;
   }
   else if(model=='E')
   {
      digit[0]='6'- 0x30;;
      digit[1]='0'- 0x30;
      digit[2]='0'- 0x30;
      digit[3]='C'- 0x30;
      maxadc=625;
      maxshunt=600;
   }
   else if(model=='F')
   {
      digit[0]='8'- 0x30;;
      digit[1]='0'- 0x30;
      digit[2]='0'- 0x30;
      digit[3]='C'- 0x30;
      maxadc=625;
      maxshunt=800;
   }
   else if(model=='G')
   {
      digit[0]='1'- 0x30;;
      digit[1]='0'- 0x30;
      digit[2]='0'- 0x30;
      digit[3]='C'- 0x30;
      maxadc=625;
      maxshunt=1000;
   }
   else if(model=='H')
   {
      digit[0]='1'- 0x30;;
      digit[1]='2'- 0x30;
      digit[2]='0'- 0x30;
      digit[3]='C'- 0x30;
      maxadc=625;
      maxshunt=1200;
   }
 }




