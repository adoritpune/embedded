/*
* File:  PA79-557-A-REV0.c
* Author: PT03
*
*
* ********************* # MODIFICATION DETAILS # *******************************
*   Date     Rev.No      Done By         Description
* 14-08-14   REV 0.0       PPT         DPM shows Actual current,Voltage & Ref current
*                                      ARC ON TIME & RESET, ESD ON/OFF
* 16-10-14   REV 0.0       PPT         Added ERROR 04 for NO OCV
********************************************************************************
*/


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
    model= readswitch();
   set_tris_a(0x2F); //0x38
   set_tris_b(0xD0);//(0x10);
   set_tris_c(0x00);

   delay_ms(2);
   digit[0]=0x27; //'D'- 0x30;  //0X40;   //'D'- 0x30;;
   digit[1]=0X27;
   digit[2]=0X27;
   digit[3]=0x27; //'R'- 0x30;
   digit[4]=0X27;
   digit[5]=0X27;
   digit[6]=0X27;
   digit[7]=0X27;
   //setdp=1;
   delay_ms(500);

   digit[0]=0x0E; //'D'- 0x30;
   digit[1]=0x19; //'O'- 0x30;
   digit[2]=0x1C; //'R'- 0x30;
   digit[3]=0X0B;  //'A'- 0x30;
   dispmodel();
   setdp=0;
   delay_ms(500);
   delay_ms(500);

   digit[0]=0x0F; //'D'- 0x30;  //0X40;   //'D'- 0x30;;
   digit[1]=0X20;
   digit[2]=0X01;
   digit[3]=0x1C; //'R'- 0x30;
   digit[4]=0X00;
   digit[5]=0X00;
   digit[6]=0X00;
   digit[7]=0X00;
   setdp=1;
   delay_ms(500);
   read_memory();
    esdonf=0;
   //mma=1;

   while(1)
   {

           if(readadcf==1)
           {
               readadc();
               readadcf=0;
           }
          //********************************************************************
         /* if(!input(ESDIN))
          {
             if(arconf==0)
             {
                digit[0]=0x0F; //'D'- 0x30;  //0X40;   //'D'- 0x30;;
                digit[1]=0X1D;
                digit[2]=0X0E;
                digit[3]=0x25; //'R'- 0x30;
                digit[4]=0X25;
                digit[5]=0X19;
                digit[6]=0X18;
                digit[7]=0X25;
                setdp=0;
                esdonf=1;
                dispvalf=1;
             }
          }
          else
          {
            esdonf=0;
          }*/

          //********************************************************************
          if((!input(ARCONKEY))&&(arcrstkeyf==0))
          {
             debounce();
             debounce();
             delay_ms(500);
             arconkeyf=1;
             if(!input(ARCONKEY))
             {
                if(tempf==0)
                {
                   setdp=0;
                   digit[0]=0x1C;
                   digit[1]=0X19;
                   digit[2]=0X18;//r   //aron time
                   digit[3]=0x0B;//a
                   digit[4]=0X1E;
                   digit[5]=0X13;
                   digit[6]=0X17;
                   digit[7]=0X0F;
                   delay_ms(1000);
                   tempf=1;
                }
                digit[0]=0x1C;
                digit[1]=0X17;
                digit[2]=0X18;
                digit[3]=0x12;
                //inttochar2(min,sec);
                inttochar2(min,hr);
                setdp2=1;
                arconf=1;
                if(weldon==0)
                {
                  setdp=1;
                  setdp1=1;
                }
                dispvalf=1;
                //setdp=0;
             }
          }
          else if(arcrstkeyf==0)
          {
             arconf=0;
             setarcdp=0;
             setdp1=0;
             setdp2=0;
             tempf=0;
             arconkeyf=0;
          }

          if((!input(ARCONRST)) && (weldon==0)&& (arconkeyf==0))
          {
            // arconrstf=1;
             arcrstkeyf=1;
             arconrstf=1;
             arconf=1;
             setdp1=0;
             setdp2=0;
             setdp=0;
             if(arconrstcnt<8000 && arcrstf==0)
             {
                if((rstcnt>=1000)&& !blink)
                {
                    rstcnt=0;
                    blink=1;
                    digit[0]=0x0F; //E  //0X40;   //'D'- 0x30;;
                    digit[1]=0X1D; //S
                    digit[2]=0X1E; //T
                    digit[3]=0x1C; //R
                    digit[4]=0X17; //M
                    digit[5]=0X19; //O
                    digit[6]=0X0E; //D
                    digit[7]=0X0F; //E
                }
                else if((rstcnt>=1000)&& blink)
                {
                    rstcnt=0;
                    blink=0;
                    digit[0]=0x25; //'D'- 0x30;  //0X40;   //'D'- 0x30;;
                    digit[1]=0x25;
                    digit[2]=0x25;
                    digit[3]=0x25; //'R'- 0x30;
                    digit[4]=0x25;
                    digit[5]=0x25;
                    digit[6]=0x25;
                    digit[7]=0x25;
                }
             }
             else if(arconrstcnt>=8000)
             {
               arcrstf=2;
               rstcnt=0;
               arconrstf=0;
               arconrstcnt=0;
               digit[0]=0x0F; //E  //0X40;   //'D'- 0x30;;
               digit[1]=0X1D; //S
               digit[2]=0X1E; //T
               digit[3]=0x1C; //R
               digit[4]=0X0E; //D
               digit[5]=0X19; //O
               digit[6]=0X18; //N
               digit[7]=0X0F; //E
               hr=0;
               min=0;
               sec=0;
               write_memory();
               delay_ms(1000);
             }
             dispvalf=1;
          }
          else if((arconkeyf==0))
          {
            arconrstf=0;
            arconrstcnt=0;
            arcrstf=0;
            arcrstkeyf=0;
            arconf=0;
            blink=0;
            rstcnt=0;
          }
         //****************************************************************
           if(uverrf==1 || overrf==1 || therrf==1 || ocverrf==1)
           {
              if(uverrf==1)
              {
                 digit[0]=0x1C; //R
                 digit[1]=0X1C; //R
                 digit[2]=0X26; //E
                 digit[3]=0x0F; //
                 digit[4]=0X00;
                 digit[5]=0X00;
                 digit[6]=0X00;
                 digit[7]=0X01;
              }
              else if(overrf==1)
              {
                 digit[0]=0x1C; //'D'- 0x30;  //0X40;   //'D'- 0x30;;
                 digit[1]=0X1C;
                 digit[2]=0X26;
                 digit[3]=0x0F; //'R'- 0x30;
                 digit[4]=0X00;
                 digit[5]=0X00;
                 digit[6]=0X00;
                 digit[7]=0X02;
              }
              else if(therrf==1)
              {
                 digit[0]=0x1C; //'D'- 0x30;  //0X40;   //'D'- 0x30;;
                 digit[1]=0X1C;
                 digit[2]=0X26;
                 digit[3]=0x0F; //'R'- 0x30;
                 digit[4]=0X00;
                 digit[5]=0X00;
                 digit[6]=0X00;
                 digit[7]=0X03;
              }
              else if(ocverrf==1)
              {
                 digit[0]=0x1C; //'D'- 0x30;  //0X40;   //'D'- 0x30;;
                 digit[1]=0X1C;
                 digit[2]=0X26;
                 digit[3]=0x0F; //'R'- 0x30;
                 digit[4]=0X00;
                 digit[5]=0X00;
                 digit[6]=0X00;
                 digit[7]=0X04;
              }
              errorf=1;
              setdp=0;
              dispcnt=1;
           }
           else
           {
              errorf=0;
              if(dispcnt==1)
              {
                 dispcnt=0;
                 dispvalf=1;
              }
           }
          //********************************************************************
           if((errorf==0) && (arconf==0) && (esdonf==0))
           {
              if(weldon==1)
              {

                if((prevcur!=current)||(dispvalf==1))// && offsetokf==1)
                 {
                    inttochar1(current);
                    prevcur=current;
                    prevref=0;
                 }
                 if((prevvtg!=voltage)||(dispvalf==1))
                 {

                    if(voltage<=9999)
                    {
                       inttochar(voltage);
                       setdp=1;
                    }
                    else
                    {
                        voltage1=(voltage/100.0);
                        inttochar(voltage1);
                        setdp=0;
                    }
                    prevvtg=voltage;
                 }
                 dispvalf=0;
              }
              else
              {
                 if((prevref!=ref)||(dispvalf==1))
                 {
                    inttochar1(ref);
                    prevref=ref;
                    prevcur=0;
                 }
                 if((prevvtg!=voltage)||(dispvalf==1))
                 {
                    if(voltage<=9999)
                    {
                       inttochar(voltage);
                       setdp=1;
                    }
                    else
                    {
                        voltage1=(voltage/100.0);
                        inttochar(voltage1);
                        setdp=0;
                    }

                    prevvtg=voltage;
                 }
                 dispvalf=0;
                 if((prevhr!=hr)||(prevmin!=min)||(prevsec!=sec))
                 {
                    write_memory();
                    prevsec=sec;
                    prevhr=hr;
                    prevmin=min;
                 }
              }
            }
   }//while
}//main

void inttochar1(unsigned int16 parameter)
{

if(model=='G' || model=='H')
   {
      digit[3]=0;
      digit[2] = parameter % 10;
      parameter /= 10;
      digit[1] = parameter % 10;
      parameter /= 10;
      digit[0] = parameter;
   }
   else{

      digit[2]=parameter % 10;
      parameter /= 10;
      digit[1] = parameter % 10;
      parameter /= 10;
      digit[0] = parameter % 10;
      parameter /= 10;
      digit[3] = parameter;
   }
}

/*void inttochar2(unsigned int16 hour,unsigned int16 min)
{
      digit[7] = hour % 10;
      hour /= 10;               //Hour
      digit[6] = hour % 10;

      digit[5] = min % 10;
      min /= 10;               //min
      digit[4] =  min % 10;
} */
void inttochar2(unsigned char hour,unsigned char min)
{
      digit[7] = hour % 10;
      hour /= 10;               //Hour
      digit[6] = hour % 10;

      digit[5] = min % 10;
      min /= 10;               //min
      digit[4] =  min % 10;
}
void inttochar(unsigned int16 parameter)
{
      digit[7] = parameter % 10;
      parameter /= 10;
      digit[6] = parameter % 10;
      parameter /= 10;
      digit[5] = parameter % 10;
      parameter /= 10;
      digit[4] = parameter;
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
   setup_adc_ports(sAN0|sAN1|sAN2|sAN3|sAN4|VSS_VDD);
     //setup_adc_ports(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL );
   //set_adc_channel(0);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void display()
{
   if(digitcnt==0)
   {
     OUTPUT_BIT(disp8,0);
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
      if(setdp2==1)
        output_bit(segmentdp,1);
     else
        output_bit(segmentdp,0);
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
     digitcnt++;
   }
   else if(digitcnt==4)
   {
     OUTPUT_BIT(disp4,0);
     //digit[3]=6;
     hexvalue = lookup_table[digit[4]];
     output_c(hexvalue);
     //set_tris_b(0x01);
     OUTPUT_BIT(disp1,0);
     OUTPUT_BIT(disp2,0);
     OUTPUT_BIT(disp3,0);
     OUTPUT_BIT(disp4,0);
     OUTPUT_BIT(disp5,1);
     OUTPUT_BIT(disp6,0);
     OUTPUT_BIT(disp7,0);
     OUTPUT_BIT(disp8,0);
     digitcnt++;
   }
   else if(digitcnt==5)
   {
     OUTPUT_BIT(disp5,0);
     //digit[3]=6;
     hexvalue = lookup_table[digit[5]];
     output_c(hexvalue);
     if(setdp==1)
        output_bit(segmentdp,1);
     else
        output_bit(segmentdp,0);
     //set_tris_b(0x01);
     OUTPUT_BIT(disp1,0);
     OUTPUT_BIT(disp2,0);
     OUTPUT_BIT(disp3,0);
     OUTPUT_BIT(disp4,0);
     OUTPUT_BIT(disp5,0);
     OUTPUT_BIT(disp6,1);
     OUTPUT_BIT(disp7,0);
     OUTPUT_BIT(disp8,0);
     digitcnt++;
   }
   else if(digitcnt==6)
   {
     OUTPUT_BIT(disp6,0);
     //digit[3]=6;
     hexvalue = lookup_table1[digit[6]];
     output_c(hexvalue);
     if(setdp1==1)
        output_bit(segmentg,1);
     else
        output_bit(segmentg,0);
     //set_tris_b(0x01);
     OUTPUT_BIT(disp1,0);
     OUTPUT_BIT(disp2,0);
     OUTPUT_BIT(disp3,0);
     OUTPUT_BIT(disp4,0);
     OUTPUT_BIT(disp5,0);
     OUTPUT_BIT(disp6,0);
     OUTPUT_BIT(disp7,1);
     OUTPUT_BIT(disp8,0);
     digitcnt++;
   }
    else if(digitcnt==7)
   {
     OUTPUT_BIT(disp7,0);
     //digit[3]=6;
     hexvalue = lookup_table[digit[7]];
     output_c(hexvalue);
     //set_tris_b(0x01);
     OUTPUT_BIT(disp1,0);
     OUTPUT_BIT(disp2,0);
     OUTPUT_BIT(disp3,0);
     OUTPUT_BIT(disp4,0);
     OUTPUT_BIT(disp5,0);
     OUTPUT_BIT(disp6,0);
     OUTPUT_BIT(disp7,0);
     OUTPUT_BIT(disp8,1);
     digitcnt=0;
   }
}

void write_memory()
{
   write_eeprom(0x01,sec);
   write_eeprom(0x02,min);
   write_eeprom(0x03,hr);
}
void read_memory()
{
   sec=read_EEPROM (0x01);
   if((sec==0XFF)||(sec>60))
   {
      sec=0;
   }
   min=read_EEPROM (0x02);
   if((min==0XFF)||(min>60))
   {
      min=0;
   }
   hr=read_EEPROM (0x03);
   if((hr==0XFF)||(hr>99))
   {
      hr=0;
   }
}
void readadc()
{
    static unsigned int32 totalcur=0,totalvtg=0,totalref2=0,totalref=0,tripref=0;
    static unsigned int16 adccntr=0,adccntr1=0;
    /*set_adc_channel(0);
    delay_us(10);
    value=read_adc();
    totalvtg= totalvtg + value;
    ;*/
    set_adc_channel(0);
    //delay_us(10);
    delay_us(100);  //@
    value=read_adc();
    totalcur= totalcur + value;
    ;
    set_adc_channel(1);
    //delay_us(10);
     delay_us(100);  //@
    value=read_adc();
    totalvtg= totalvtg + value;
    ;
    set_adc_channel(2);
    //delay_us(10);
      delay_us(100);  //@
    value=read_adc();
    totalref= totalref + value;

    set_adc_channel(3);
    //delay_us(10);
      delay_us(100);  //@
    value=read_adc();
    tripref= tripref + value;

    set_adc_channel(4);
    //delay_us(10);
    delay_us(100); //@
    value=read_adc();
    totalref2= totalref2 + value;
    ;


    {
    /*   setup_adc_ports(ALL_ANALOG);
       set_adc_channel(11);
       delay_us(10);
       value=read_adc();
        offset1=value;
       setup_adc_ports(sAN0|sAN1|sAN2|VSS_VDD);*/

    }
    adccntr++;
    adccntr1++;

    if(adccntr >=adcavg)//256)//128)  //@prev if(adccntr1 >=adcavg1)//256)//128)
    {
       ref2=totalref2>>leftshift;//8;  //@prev ref2=totalref2>>leftshift1;//8;
        //*******************************************************
         if(ref2<=120) //110
         {
            ref=20.0;//10
         }
         else
         {
             errorp=ref2;
             errorp=errorp/4.616;   //4.616
             offset=constant-errorp;
             ref=ref2-offset;
             ref=ref-refoffset;
             //ref=(ref*40)/57;
             ref=ref/0.9;         //1.385

         }
         if(ref<=20.0)//10
         {
            ref=20.0;//210
         }
         totalref2=0;
         adccntr1=0;

      //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    }

    if(adccntr >=adcavg)//256)//128)
    {
      cur=totalcur>>leftshift;//8;

      calcur=(cur*maxshunt)/maxadc;
      //#####################################################
     // ref2=totalref2>>leftshift;//8;
      vtgref=totalref>>leftshift;//8;
      tripvolt=tripref>>leftshift;//8;
      //ref2=totalref>>8;
      //*******************************************************
       /*  if(ref2<=120) //110
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
             ref=ref/1.385;         //1.385

         }
         if(ref<=10.0)
         {
            ref=10.0;
         }

         */

      //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
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
            //current=50;
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

      //*******************************************************************
     vtg=totalvtg>>leftshift;//8;
     voltage=(vtg*1000.0)/62.5;//17.0;//3.3=97V fvtg;//decimal count
     //if(voltage<=0)
     //voltage=1;
     if((voltage<4000.0) && (weldon==0))
     {
        noocvf=1;
        if(cnt4sec>=40)
        {
           ocverrf=1;
        }
     }
     else
     {
        ocverrf=0;
        noocvf=0;
        cnt4sec=0;
     }
   //*******************************************************************
    {
         if(tripvolt>1000.0)
         {
            uverrf=0;
            overrf=0;
            therrf=0;
         }
         else if(tripvolt > 180.0 && tripvolt < 220.0)
         {
            uverrf=1;
            overrf=0;
            therrf=0;
         }
         else if(tripvolt > 390.0 && tripvolt < 430.0)
         {
            uverrf=0;
            overrf=1;
            therrf=0;
         }
         else if(tripvolt > 590.0 && tripvolt < 630.0)
         {
            uverrf=0;
            overrf=0;
            therrf=1;
         }
         else
         {
            uverrf=0;
            overrf=0;
            therrf=0;
         }
      }
   //**********************************************************************
      totalvtg=0;
      totalcur=0;
      adccntr=0;
      totalref=0;
      //totalref2=0;
      tripref=0;
      //inttochar1(current);
      //printf("%lx",current);
      //putchar(0x0D);
      //putchar(0x0A);
    }
  }

//=========================
 /*unsigned char chk_band(unsigned int16 cur11,unsigned int16 prevcur11)
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
 }*/

//=========================

/*unsigned char readswitch()
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
} */

unsigned char readswitch()
{
   unsigned char data=0,data1=0;
   data=input_c();
   data=data & 0x07;
  // data=data>>1;
   delay_us(200);
   data1=input_c();
   data1=data1 & 0x07;
   //data1=data1>>1;
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
/*void dispmodel()
{
   if(model=='A')
   {
     // digit[0]=0X02; //'2'- 0x30;;
      //digit[1]=0X05; //'5'- 0x30;
     // digit[2]=0X00; //'0'- 0x30;
      //digit[3]=0x0D; //'C'- 0x30;
      digit[4]=0X02;
      digit[5]=0X05;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=250;
   }
   else if(model=='B')
   {
      digit[4]=0X03;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=300;
   }
   else if(model=='C')
   {
      digit[4]=0X04;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=400;
   }
   else if(model=='D')
   {
      digit[4]=0X06;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=600;
   }
   else if(model=='E')
   {
      digit[4]=0X08;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=800;
   }
   else if(model=='F')
   {
      digit[4]=0X01;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X00;
      maxadc=625;
      maxshunt=100;
   }
   else if(model=='G')
   {
      digit[4]=0X01;
      digit[5]=0X02;
      digit[6]=0X00;
      digit[7]=0X00;
      maxadc=625;
      maxshunt=1200;
   }
   else if(model=='H')
   {
      digit[4]=0X01;
      digit[5]=0X05;
      digit[6]=0X00;
      digit[7]=0X00;
      maxadc=625;
      maxshunt=1500;
   }
 }*/

void dispmodel()
{
   if(model=='A')
   {
     // digit[0]=0X02; //'2'- 0x30;;
      //digit[1]=0X05; //'5'- 0x30;
     // digit[2]=0X00; //'0'- 0x30;
      //digit[3]=0x0D; //'C'- 0x30;
      digit[4]=0X01;
      digit[5]=0X05;
      digit[6]=0X00;
      digit[7]=0X00;
      maxadc=625;
      maxshunt=1500;
   }
   else if(model=='B')
   {
      digit[4]=0X01;
      digit[5]=0X02;
      digit[6]=0X00;
      digit[7]=0X00;
      maxadc=625;
      maxshunt=1200;
   }
   else if(model=='C')
   {
      digit[4]=0X01;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X00;
      maxadc=625;
      maxshunt=1000;
   }
   else if(model=='D')
   {
      digit[4]=0X08;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=800;
   }
   else if(model=='E')
   {
      digit[4]=0X06;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=600;
   }
   else if(model=='F')
   {
      digit[4]=0X04;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=400;
   }
   else if(model=='G')
   {
      digit[4]=0X03;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=300;
   }
   else if(model=='H')
   {
      digit[4]=0X02;
      digit[5]=0X05;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=250;
   }
 }



