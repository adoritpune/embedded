   /*
* File:  PA79-557-B-REV0.c
* Author: PT03
*
*
* ********************* # MODIFICATION DETAILS # *******************************
*   Date     Rev.No      Done By         Description
* 14-08-14   REV 0.0       PPT         DPM shows Actual current,Voltage & Ref current
*                                      ARC ON TIME & RESET, ESD ON/OFF
* 16-10-14   REV 0.0       PPT         Added ERROR 04 for NO OCV
* 03-02-22   REV 2.0                  Display shows  Set and Actual Current
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
   digit[3]=0X0B; //'A'- 0x30;
   dispmodel();
   setdp=0;
   delay_ms(500);
   delay_ms(500);

   digit[0]=0x0F; //'D'- 0x30;  //0X40;   //'D'- 0x30;;    0F
   digit[1]=0X20;
   digit[2]=0x01;  //19  ***
   digit[3]=0x1C; //'R'- 0x30;

   digit[4]=0X00;
   digit[5]=0X00;
   digit[6]=0X00;
   digit[7]=0X00;
   setdp=1;
   delay_ms(1000);
   esdonf=0;
   //mma=1;
   ref2=10;
   current=0;
   inttochar1(current);
   while(1)
   {

         if(readadcf==1)
         {
            readadc();
            readadcf=0;
         }

        // if(weldon==1)
        if(voltage<8000)
         {
            if((prevcur!=current))// && offsetokf==1)
            {
             /*
               if(ucSetCurr<310)
               {
                  if((current > (ucSetCurr+10)) && (current > (ucSetCurr-15)))
                    current   =  current + (current-ucSetCurr);
                  else if((current < (ucSetCurr-10)) && (current > (ucSetCurr-15)))
                    current   =  current + (ucSetCurr-current);
               }

               if(ucSetCurr>300)
               {
                  if((current > (ucSetCurr+15)) && (current > (ucSetCurr-60)))
                    current   =  current + (current-ucSetCurr);
                  else if((current < (ucSetCurr-15)) && (current > (ucSetCurr-60)))
                    current   =  current + (ucSetCurr-current);
               }*/

               inttochar1(current);
               prevcur=current;
            }
            prevref=0;
         }
         else
         {
              current=0;
              inttochar1(current);
         }

      /*   else if(weldon==0)
         {
            if((prevref!=ref2))
            {

              if(ucModelSel==1)
                 SetCurrentCal_500();
               else if(ucModelSel==2)
                 SetCurrentCal_300();

               ucSetCurr=ref2;
               inttochar1(ref2);
               prevref=ref2;
            }
         }*/

         if((prevvtg!=voltage))
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

         if(dispcnt==1)
         {
            dispcnt=0;
            dispvalf=1;
         }
      }

}//main

void inttochar1(unsigned int16 parameter)
{
   if(model=='G' || model=='H')
   {
      digit[2]=parameter % 10;
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
   setup_adc_ports(sAN0|sAN1|VSS_VDD);
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

void readadc()
{
    static unsigned int32 totalcur=0,totalvtg=0,totalref2=0;//
    static unsigned int16 adccntr=0,adccntr1=0;

    set_adc_channel(0);          //current
    delay_ms(1);
    value=read_adc();
    totalcur= totalcur + value;
    set_adc_channel(1);          //voltage
    delay_ms(1);
    value=read_adc();
    totalvtg= totalvtg + value;

    set_adc_channel(4);
   // delay_ms(1);
    delay_us(100);
    value=read_adc();
    totalref2= totalref2 + value;

    adccntr++;
    adccntr1++;

    if(adccntr>=adcavg)//256)//128)
    {
         cur=totalcur>>leftshift;//8;
        // if(cur>=300)
       //    calcur=(cur*maxshunt)/560;   //575
       //  else
            calcur=(cur*maxshunt)/maxadc;

         //calcur=cur;

/*         if(cur>=0 && cur<=65)                              //10 to 50AMP
            calcur=(((cur*0.77))+10);

         else if(cur>65 && cur<=136)                         //>50 to 100AMP
           calcur=(((cur-65)*0.70)+50);

         else if(cur>136 && cur<=214)                         //>100 to 150AMP
           calcur=(((cur-136)*0.641)+100);

         else if(cur>214 && cur<=286)                         //>150 to 200AMP
           calcur=(((cur-214)*0.704)+150);

         else if(cur>286 && cur<=343)                        //>200 to 250AMP
           calcur=(((cur-286)*0.862)+200);

         else if(cur>343 && cur<=394)                        //>250 to 300AMP
           calcur=(((cur-343)*0.961)+250);
         else
          calcur=(cur*maxshunt)/maxadc;
         */




         if(offsetokf==0)                        //executes once on power ON to calculate offset
         {
            offcnt++;
            if(offcnt==3)     //for reading offset
            {
               offsetokf=1;
               offcnt=0;
               curoffset=calcur;
            }
            else
            {
                current=1;      //curoffset;   //current=1 changed by sayali 18.08.18
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
               current=1;  //current=1 changed   16.08.18
               weldon=0;
            }
         }

      vtg=totalvtg>>leftshift;//8;
      voltage=(vtg*1000.0)/62.5;//17.0;//3.3=97V fvtg;//decimal count
      totalvtg=0;
      totalcur=0;
      adccntr=0;

    //**  ref2=totalref2>>leftshift; //8;
    //**  ref2=(ref2*4.88)/10;// 3.02V =600Amp  POt Output=4.347V


     /* if(ref2<148)
         ref2=((ref2*18.88)+100)/10;
      else
     //    ref2=((ref2*20)+100)/10;      //18.4375 =4.456   //20==4.242 // tp6 =2.95
      */
      totalref2=0;

     }
}


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


void debounce()
{
    for(jj=0;jj<255;jj++);
}


void dispmodel()
{
   if(model=='A')
   {
     // digit[0]=0X02; //'2'- 0x30;;
      //digit[1]=0X05; //'5'- 0x30;
     // digit[2]=0X00; //'0'- 0x30;
      //digit[3]=0x0D; //'C'- 0x30;
      digit[4]=0X00;
      digit[5]=0X05;
      digit[6]=0X00;
      digit[7]=0X00;
      maxadc =615;         // 625
      maxshunt=500;
      ucModelSel=1;
   }
   else if(model=='B')
   {
      digit[4]=0X01;
      digit[5]=0X02;
      digit[6]=0X02;
      digit[7]=0X00;
      maxadc=625;
      maxshunt=1200;
   }
   else if(model=='C')
   {
      digit[4]=0X01;
      digit[5]=0X00;
      digit[6]=0X03;
      digit[7]=0X00;
      maxadc=625;
      maxshunt=1000;
   }
   else if(model=='D')
   {
      digit[4]=0X08;
      digit[5]=0X00;
      digit[6]=0X04;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=800;
   }
   else if(model=='E')   //600A
   {
      digit[4]=0X06;
      digit[5]=0X00;
      digit[6]=0X00;
      digit[7]=0X25;
      maxadc=625;
      maxshunt=600;
      //ucModelSel=1;
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
      maxadc=615;
      maxshunt=300;
      ucModelSel=2;
   }
   else if(model=='H')
   {
      digit[4]=0X02;
      digit[5]=0X05;
      digit[6]=0X08;
      digit[7]=0X25;
      maxadc  =625;
      maxshunt=250;
   }
 }


void SetCurrentCal_600(void)
{

      if(ref2>=0 && ref2<=30)                              //10 to 50AMP
           ref2=(((ref2*12.89)+100))/10;

      else if(ref2>30 && ref2<=55)                         //>50 to 100AMP
           ref2=((((ref2-30)*19.60)+500))/10;     //507

      else if(ref2>55 && ref2<=79)                         //>100 to 150AMP
           ref2=((((ref2-55)*20.42)+1000))/10;    //999

      else if(ref2>79 && ref2<=125)                         //>150 to 250AMP
           ref2=((((ref2-79)*21.78)+1500))/10;    //1487

      else if(ref2>125 && ref2<=200)                        //>250 to 400AMP
           ref2=((((ref2-125)*20.50)+2500))/10;    //2487

      else if(ref2>200 && ref2<=248)                        //>400 to 500AMP
           ref2=((((ref2-200)*20.24)+4000))/10;

      else if(ref2>248 && ref2<=302)                        //>500 to 600AMP
           ref2=((((ref2-248)*18.76)+5000))/10;

      else if(ref2>302)
           ref2=600;
}

void SetCurrentCal_400(void)
{
      if(ref2>=0 && ref2<=32)                              //10 to 50AMP
           ref2=(((ref2*12.66)+100))/10;

      else if(ref2>32 && ref2<=72)                         //>50 to 100AMP
           ref2=((((ref2-32)*11.60)+500))/10;

      else if(ref2>72 && ref2<=110)                        //>100 to 150AMP
           ref2=((((ref2-72)*12.14)+1000))/10;   //12.53

      else if(ref2>110 && ref2<=149)                        //>150 to 200AMP
           ref2=((((ref2-110)*12.76)+1500))/10;  //14.49

      else if(ref2>149 && ref2<=227)                        //>200 to 300AMP
           ref2=((((ref2-149)*12.85)+2000))/10;

      else if(ref2>227 && ref2<=302)                        //>300 to 400AMP
           ref2=((((ref2-227)*13.25)+3000))/10;

      else if(ref2>302)
           ref2=400;
}

void SetCurrentCal_500(void)
{

      if(ref2>=0 && ref2<=11)                              //10 to 50AMP
           ref2=(((ref2*35.40)+100))/10;

      else if(ref2>11 && ref2<=37)                         //>50 to 100AMP
           ref2=((((ref2-11)*19.61)+500))/10;     //507

      else if(ref2>37 && ref2<=64)                         //>100 to 150AMP
           ref2=((((ref2-37)*18.18)+1000))/10;    //999

      else if(ref2>64 && ref2<=114)                         //>150 to 250AMP
           ref2=((((ref2-64)*20.08)+1500))/10;    //1487

      else if(ref2>114 && ref2<=190)                        //>250 to 400AMP
           ref2=((((ref2-114)*19.87)+2500))/10;    //2487

      else if(ref2>190 && ref2<=235)                        //>400 to 500AMP
           ref2=((((ref2-190)*22.12)+4000))/10;

      else if(ref2>235)
           ref2=500;
}

void SetCurrentCal_300(void)
{
      if(ref2>=0 && ref2<=32)                              //10 to 50AMP
           ref2=(((ref2*12.66)+100))/10;

      else if(ref2>32 && ref2<=72)                         //>50 to 100AMP
           ref2=((((ref2-32)*11.60)+500))/10;

      else if(ref2>72 && ref2<=110)                        //>100 to 150AMP
           ref2=((((ref2-72)*12.14)+1000))/10;   //12.53

      else if(ref2>110 && ref2<=149)                        //>150 to 200AMP
           ref2=((((ref2-110)*12.76)+1500))/10;  //14.49

      else if(ref2>149 && ref2<=227)                        //>200 to 300AMP
           ref2=((((ref2-149)*12.85)+2000))/10;

      else if(ref2>302)
           ref2=300;
}

