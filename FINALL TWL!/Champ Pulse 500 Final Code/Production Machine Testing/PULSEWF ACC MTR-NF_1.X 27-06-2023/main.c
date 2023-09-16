
//#include"pic16f1786.h"
//#include"disp.c"
// PIC16F1786 Configuration Bit Settings
// 'C' source line config statements

//#include <xc.h>
#include<xc.h>
#include"VARIABLE.c"
#include"DEFINE.c"
#include"STRUCTURE.C"
#include"function.h"
#include"DISPLAY.C"
#include"ENCODER.C"
#include"MOTORCONTROL.C"

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC     = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE     = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE    = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE    = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP       = ON          // Flash Program Memory Code Protection (Program memory code protection is enabled)
#pragma config CPD      = ON         // Data Memory Code Protection (Data memory code protection is enabled)
#pragma config BOREN    = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO     = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN    = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT      = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN   = OFF     // Voltage Regulator Capacitor Enable bit (Vcap functionality is disabled on RA6.)
#pragma config PLLEN    = ON      // PLL Enable (4x PLL enabled)
#pragma config STVREN   = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV     = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR    = OFF      // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP      = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void interrupt ISR_Function(void)
{
    if(INTCONbits.TMR0IF==1)      //INTERRRUPT @ 2MSEC
    {
        INTCONbits.TMR0IF=0;
        TMR0=0x00;//0X85;                 //7D
        updatedispf=0;//1;
        Display();
        count_1ms++;
        count_2ms++;
        count_1msec++;
        count_pid++;
        count_transms++;

        if(cPowerOnErrSkipfg == 1)
        {
            if(iPowerOnErrSkipCnt == 0)
            {
                cPowerOnErrSkipfg = 0;
                iPowerOnErrSkipCnt = 0;
            }else
            {
                iPowerOnErrSkipCnt--;
            }
        }

        if(cGasRlyClrfg == 1)
        {
            if(iGasDbCnt == 0 )
            {
                Type.gason      =0;
                GAS_RLY         =0;        
                dispupdatef     =1;
                cGasRlyClrfg = 0;
            }
            else
            {
                iGasDbCnt--;
            }
        }
//---------------------------------------------------------------------
            if((cMtrOverLdfg == 0)&&(cPowerOnErrSkipfg == 0))
            {
                if((MOTOR_TRIP11 == 0)&&(cMtrOverLdDbfg == 0))
                {
                    cMtrOverLdDbfg = 1;
                    cMtrOverLdDbCnt = MTROVLDTIME;
                }
                else if((MOTOR_TRIP11 == 0)&&(cMtrOverLdDbfg == 1))
                {
                    cMtrOverLdDbCnt--;
                    if(cMtrOverLdDbCnt == 0)
                    {
                        cMtrOverLdDbfg = 0;
                        cMtrOverLdfg = 1;
                        cMtrOverLdDbCnt = MTROVLDTIME;
                        errorstatus.motor_over_ld_er5 = 1;
                        Update_PWM(setwirespeed*0);
				        speeedrate=0;
                    }
                }
                else if(MOTOR_TRIP11 == 1)
                {
                    cMtrOverLdDbfg = 0;

                }
            }
            /* // this logic is for testing purpose to disable the cMtrOverLdfg by time
            else
            {
                if(cMtrOverLdDbCnt == 0)
                {
                    cMtrOverLdfg = 0;
                    errorstatus.motor_over_ld_er5 = 0;
                }
                else
                {
                    cMtrOverLdDbCnt--;
                }
            }
            */
//---------------------------------------------------------------------
        if(RCSTAbits.FERR==1 || RCSTAbits.OERR==1)
        {
            RCSTAbits.SPEN=0;
            RCSTAbits.CREN=0;
            RCSTAbits.SPEN=1;
            RCSTAbits.CREN=1;
        }
        if(count_1ms>=500) //1000)
        {    
            count_1ms=0;
            comm_error_count++;
          
            if(weldmode=='P' || weldmode=='G')
            {
            if(comm_error_count>3)
            {
            error8=1;
            comm_error_count=4;
            }
            else
             error8=0;
            }
            else
            {
                error8=0;
                comm_error_count=0;
            }

            //onesecf=1;  //mahesh disabled
            
            /*if(RCSTAbits.FERR)
            {
              RCSTAbits.SPEN=0;
              RCSTAbits.SPEN=1;
            }
            if(RCSTAbits.OERR)
            {
              RCSTAbits.CREN=0;
              RCSTAbits.CREN=1;
              RCSTAbits.SPEN=0;
              RCSTAbits.SPEN=1;
            }*/
        }
        if(count_2ms >=1)
        {       
            count_2ms=0;
            read_enc1f=1;
        }
        
        if(count_1msec >= 2)//10)//20)
        {
            count_1msec=0;
            if(kpressread==0)
            {
                torchstatus1=TORCHIN;
                kpressread=1;
            }
            else
            {
                kpressread=0;
                torchstatus2=TORCHIN;
                tans   =(torchstatus1   ==   torchstatus2    ? 1:0);
                if(tans==1)
                {
                    TORCH=(torchstatus2   ==   0    ? 'P':'X');
                    if(TORCH=='P')
                    {
                        wfstatus.torchonstatus=1;
if(cTorchPressfg == 0)
{
    cPowerOnErrSkipfg = 1;
    iPowerOnErrSkipCnt = 1000;
    cTorchPressfg = 1;
}
                    }
                    else
                    {
                        wfstatus.torchonstatus=0;
                        if(cTorchPressfg == 1)
                        {
                            cTorchPressfg = 0;
                        }
                    }
                }
                if(prevTORCH != TORCH)
                {
                    count_1ms=0;
                    //onesecf=1;
                    //txonf=1;
                }    
                prevTORCH = TORCH;
            }
        }
      }
    
    if(PIE1bits.TMR2IE & PIR1bits.TMR2IF)       //PWM
    {
         PIR1bits.TMR2IF=0;
         return;
    }
    if(PIE1bits.TXIE & PIR1bits.TXIF)
    {
        PIR1bits.TXIF=0;
        return;
    }
 
    if(PIE2bits.CCP2IE & PIR2bits.CCP2IF)
    {    
        PIR2bits.CCP2IF =0;    //to test if my program will go into isr() 
        if(Count == 0)         // capture the first signal 
        { 
            OneH = CCPR2H; 
            OneL = CCPR2L; 
            Count = 1; 
        } 
        else                   // capture the second signal 
        { 
            TwoH = CCPR2H;     // save the time of second rising edge to some register 
            TwoL = CCPR2L;
            TMR1H = 0x00;          // clear timer1 
            TMR1L = 0x00; 
            Count = 0; 
            Two = TwoH;
            Two <<= 8;
            Two |= TwoL;
            One = OneH;
            One <<= 8;
            One |= OneL;
            Total_Count = Two - One;
            
            pperiod=Total_Count; //65535/8=8192             //unit usec min 0 t0 32768;
            Total_Period=Total_Period+pperiod;
            pcount++;
            if(pcount>=16)
            {
                pcount=0;
                avgpperiod=Total_Period>>5; //LHS 3 TIMES = DIVIDE / 8 & LS 1 TIMES, 65535 COUNTS =32768USEC
                pfreq=1000000/avgpperiod; //in hz
                Total_Period=0;

                Tsampling =avgpperiod/1000.0;//avgpperiod/1000000.0;

                //pfreq = pfreq / 16;
                
                if(pfreq>=MAX_P_FB_FREQ)
                    pfreq=MAX_P_FB_FREQ;
                else if(pfreq<=0)
                   pfreq=0;

                //Fltpfreq=(0.2*pfreq)+(0.8)*prevFltpfreq;
                Fltpfreq=(0.2*pfreq)+(0.8)*prevFltpfreq;
//------------------------------------
                pstowfstr.Hi_data1 = pfreq / MTR_FREQ_CONSTANT;
//------------------------------------
                if(Fltpfreq>=MAX_P_FB_FREQ)
                    Fltpfreq=MAX_P_FB_FREQ;
                else if(Fltpfreq<=0)
                   Fltpfreq=0;
                
                 prevFltpfreq=Fltpfreq;
                 capintervalf=1;
                 fixintervalf=0;
                 count_pid=0;
                 //if(cyclestrtf==1)// && closeloopf==1)

                 if(cyclestrtf==1 && psstatus.twinpulseon==0)// && closeloopf==1))
                    adaptivepidf=1; //disabled for twin pulsse
                 else
                     adaptivepidf=0;
                    //Adaptive_base_pid();
              }
        }    
    }
   
    if(PIE1bits.RCIE & PIR1bits.RCIF) //&& (serialintf==1))
    {
        PIR1bits.RCIF=0;
        rxdata= RCREG;
        //Send_Byte(rxdata);
        if(RCSTAbits.FERR)
        {
          RCSTAbits.SPEN=0;
          RCSTAbits.SPEN=1;
        }
        if(RCSTAbits.OERR)
        {
          RCSTAbits.CREN=0;
          RCSTAbits.CREN=1;
          RCSTAbits.SPEN=0;
          RCSTAbits.SPEN=1;
        }
        //if(txonf==0)
        {
            if(rxdata=='@' && startptr1==0 && statusptr1==0 )// && txonf==0)
            {    
                startptr1   =1;
                arrptr      =0;
                statusptr1  =0;
                recchksum   =0;
            }
            else if(rxdata=='#' && startptr1==0 && statusptr1==0)// && txonf==0)
            {
                startptr1   =0;
                statusptr1  =1;
                arrptr      =0;
                recchksum   =0;
            }
            else if(startptr1==0 && statusptr1==1)
            {
                if(recstatus==0)
                {
                    recpsstatus=rxdata;
                    recstatus=1;
                }
                else if(recstatus==1)
                {
                    if(rxdata==recpsstatus)//'?')
                    {
                        comm_error_count=0;
                        psstatusu.psstatusbyte[0]=recpsstatus;
                        pstowfstr.psstatusbyte=recpsstatus;
                        
                        if(psstatus.motoroncommand==1 && psstatus.twinpulseon==1 )
                        {
                            if(psstatus.Hi_speedon==1)
                            {
                                TRISMTRFB=0;
                                MTRFB=1;
                                //TRISMOTOR_TRIP11=0;
//                                MOTOR_TRIP11=  1;
                                Update_PWM(Hi_setppwm);
//                                Type.thickness=1;
                            }
                            else
                            {
                                TRISMTRFB=0;
                                MTRFB=0;
                                //TRISMOTOR_TRIP11=0;
//                                MOTOR_TRIP11=  0;
                                Update_PWM(Lo_setppwm);
//                                Type.thickness=0;
                            }
                        }
                        /*if(psstatus.creepspeedon==0)
                        {
                             TRISMOTOR_TRIP11=0;
                             MTRFB=0;
                        }
                        else
                        {
                            TRISMOTOR_TRIP11=0;
                            MTRFB=1;
                        }
                        */
                        recstatus=0;
                        startptr1=0;
                        statusptr1=0;
                        arrptr=0;
                        recchksum=0;
                        send_statusf=1;
                        //send_status();          //send wf status immediately
                    }
                    else
                    {
                        recstatus=0;
                        startptr1=0;
                        statusptr1=0;
                        arrptr=0;
                        recchksum=0;
                    }
                }     
            }
            else if(startptr1==1 && statusptr1==0)
            {    
                if(arrptr<=RECEIVE_STRING_LENGTH)//21)
                {    
                    rec_arr[arrptr]=rxdata;
                    recchksum=recchksum+rxdata;
                    arrptr++;
                      
                }
                else if(recchksum==rxdata)
                {
                    comm_error_count=0;

                    for(ijk=0;ijk<=RECEIVE_STRING_LENGTH;ijk++)  //20 21 15 status byte controlled by wf
                    {    
                        pstowfstru.pstransarr[ijk]=rec_arr[ijk];
                    }

                    weldmode=pstowfstr.weldmode;
                    if(cEditfg == 0)
                    {
                        setwirespeed=pstowfstr.setwspeed;
                    }
          
                    wfstatusu.wfstatusbyte[0]=pstowfstr.wfstatusbyte;

                    if(wfstatus.twotfourtmode1==1)
                    {
                    Type.twot=0;
                    Type.fourt=1;
                    }
                    else
                    {
                    Type.twot=1;
                    Type.fourt=0;
                    }

                    if(cEditfg == 0)
                    {
                        setvoltage=pstowfstr.Hi_setvoltage;
                        setvoltage<<=8;
                        setvoltage|=pstowfstr.Lo_setvoltage;
                    }
                    setcurrent=pstowfstr.Hi_setcurrent;
                    setcurrent<<=8;
                    setcurrent|=pstowfstr.Lo_setcurrent;

                    Actual_amp=pstowfstr.Hi_actualcurrent;
                    Actual_amp<<=8;
                    Actual_amp|=pstowfstr.Lo_actualcurrent;
                    
                    Actual_vtg=pstowfstr.Hi_actualvoltage;
                    Actual_vtg<<=8;
                    Actual_vtg|=pstowfstr.Lo_actualvoltage;

//Actual_amp = setpfreq;
//Actual_vtg = Fltpfreq;
cRelSpeedSign = pstowfstr.pulse_freq;

                    rel_wirespeed=pstowfstr.rel_wirespeed;

                    crater_speed=pstowfstr.crater_speed;

                    if(cEditfg == 0)
                    {
                        psstatusu.psstatusbyte[0]=pstowfstr.psstatusbyte;
                    }

                    error_code1=pstowfstr.error_code1;
                    error_code2=pstowfstr.error_code2;

                    commandu.commandbyte[0]=pstowfstr.command_to_wf;
                    if(cMtrOverLdfg == 0)
                    {
                        erroru.errorstatusbyte[0]=pstowfstr.error_code1;
                        erroru.errorstatusbyte[1]=pstowfstr.error_code2;
                    }
                    
                    creep_speed=pstowfstr.creep_speed;

                    if(command.volt_or_arc==1)
                  //if(psstatus.migpmigmode==0)
                    {
                        Type.arclength=0;
                        Type.vtg      =1;
                    }
                    else
                    {
                        Type.arclength=1;
                        Type.vtg      =0;
                    }
                    if(wfstatus.twotfourtmode1 == 1)
                    {
                        cWf2t4tmodefg = 1;
                    }
                    else
                    {
                        cWf2t4tmodefg = 0;
                    }
                    startptr1=0;
                    arrptr=0;
                    recchksum=0;
                    recstatus=0;
                    statusptr1=0;
                    transmitonf=1;
                    onesecf=1;          //DATA WILL BE SEND ONLY WHEN DATA RECEIVED
                }    
                else
                {

                    recstatus=0;
                    startptr1=0;
                    statusptr1=0;
                    arrptr=0;
                    recchksum=0;
                }
            }  
        }
        /*else
        {
            startptr1=0;
            arrptr=0;
            recchksum=0;
            
        } */
    }    
    
}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void main (void)
{
   // Delayms(1000);
    system_init();
    for(delay==0;delay<5000;delay++);
    Delayms(1000);
    portpin_init();
    Timer0_init();
    PWM_init();
    capture_init();
    uart_init();
    INTCONbits.GIE  =1;
    INTCONbits.PEIE =1;
    //Update_PWM(current);
    //Delayms(2000);
    GAS_RLY=0;
//------------------------------------
    TRISMTRFB = 0;
    cPowerOnErrSkipfg = 1;
    iPowerOnErrSkipCnt = 2000;
//------------------------------------
    diswin1[0]=0x0B;//'A';
    diswin1[1]=0x0E;//'D';
    diswin1[2]=0x1C;//'R';
    diswin1[3]=0x1C;//'R';
    diswin1[4]='2'-0x30;  //rev 2 @sbm
    diswin1[5]='3'-0x30;// changed on 2.1
    Typedp.digitdp5=1;
    
    Delayms(2000);
   
    DECODE_EN=0;
    Typedp.digitdp5=0;
    TypeU.LEDGROUP[0]   =0x00;
    TypeU.LEDGROUP[1]   =0x00;
    Type.wirespeed      =1;
    Type.vtg            =1;
    Type.twot           =1;
    TypeDP.DPGROUP[0]   =0x00;
    Typedp.digitdp2	=1;
    Typedp.digitdp5	=1;
    
    psstatusu.psstatusbyte[0]=0x00;
   
    
    setcurrent=0;
    setvoltage=0;
    disp_hex_window1(setcurrent);
    disp_hex_window2(setvoltage);
    TXSTAbits.TXEN  =1;       //Transmit enabled
    RCSTAbits.CREN  =1;       //Enables receiver
    PIE1bits.RCIE   =1;        //Enables the EUSART receive interrupt
    INTCONbits.GIE  =1;
    INTCONbits.PEIE =1;
    Delayms(5000);
    PIE1bits.TXIE   =0;        //Enables the EUSART receive interrupt
while(1)
{
//----------------------------------------------
        if(cMtrOverLdfg == 1)
        {
            Update_PWM(setwirespeed*0);
			speeedrate=0;	   
        }
/***************************communication section start******************************************/
        if(send_statusf==1 && onesecf==0)
        {
           send_statusf=0;
           send_status();
        }
        if(onesecf==1 && transmitonf==1)
        {
            onesecf=0;
            transmittops();
            txonf=0;
            cEditfg = 0;
/*
if(cTestfg == 0)
{
    cTestfg = 1;
    Type.sec         =1;
}
else
{
    Type.sec         =0;
    cTestfg = 0;
}
*/
//            transmitonf = 0;

        }
  /***************************communication section end*****************************************/

if(universal_error==0)
{
        disp_hex_window11(crater_speed);
        disp_hex_window22(creep_speed);

        if(adaptivepidf==1)
        {
            adaptivepidf=0;
            Adaptive_base_pid();
        }
  /**************************Encoder read start here*************************************************/
        if(read_enc1f==1)
        {    
            read_enc1f=0;
            if(enccount==0)
            {
                encod1=SCANENCODER1();
                mili1_100++;
                {
                    if(encod1=='+')
                    {
                        setwirespeed=setwirespeed+pluspara1;
                        if(setwirespeed >= 240)
                        setwirespeed=240;
                        cEditfg = 1;
                    }
                    else if(encod1=='-')
                    {
                        if(setwirespeed >= minuspara1)
                        setwirespeed=setwirespeed-minuspara1;
                        else if(setwirespeed >= 10)
                        setwirespeed=setwirespeed--;
                        if(setwirespeed <= 10)
                        setwirespeed=10;
                        cEditfg = 1;
                    }
                }
                if(mili1_100<200)
                {
                    if(encod1=='+')
                        pluscount1++;
                    else if(encod1=='-')
                        minuscount1++;
                }
                else if(mili1_100>=200)
                {
                    mili1_100=0;
                    pluspara1=pluscount1>>1;
                    minuspara1=minuscount1>>1;
                    if(pluspara1<=1)
                    pluspara1=1;
                    if(minuspara1<=1)
                    minuspara1=1;
                    pluscount1=0;
                    minuscount1=0;
                }
               enccount++;
            }  
            else
            {    
                mili2_100++;
                encod2=SCANENCODER2();
                if(Type.vtg==1)//psstatus.migpmigmode==0)   //mig mode
                {
                    if(encod2=='+')
                    {
                        setvoltage=setvoltage+pluspara2;
                        if(setvoltage>440)
                        setvoltage=440;
                    cEditfg = 1;
                    }
                    else if(encod2=='-')
                    {
                        if(setvoltage>=minuspara2)
                        setvoltage=setvoltage-minuspara2;
                        else if(setvoltage>=100)
                        setvoltage=setvoltage--;
                        
                        if(setvoltage<=100)
                        setvoltage=100;
                    cEditfg = 1;
                    }
//                    iTest = setvoltage;
                    encod2 = '$';

                }
                else if(Type.arclength==1)
                {
                    if(encod2=='+')
                    {
                        pstowfstr.arclength=pstowfstr.arclength+pluspara2;

                        if(weldmode=='P')
                        {
                        if(pstowfstr.arclength>80)
                        pstowfstr.arclength=80;
                        }
                        else if(weldmode=='G')
                        {
                           if(pstowfstr.arclength>40)
                            pstowfstr.arclength=40;
                        }

                    

                    }
                    else if(encod2=='-')
                    {
                        if(pstowfstr.arclength>=minuspara2)
                            pstowfstr.arclength=pstowfstr.arclength-minuspara2;
                        else if(pstowfstr.arclength>=1)
                            pstowfstr.arclength=pstowfstr.arclength--;

                        if(pstowfstr.arclength<=0)
                        pstowfstr.arclength=0;
                    }
                    cEditfg = 1;
                }
                if(mili2_100<200)
                {
                    if(encod2=='+')
                        pluscount2++;
                    else if(encod2=='-')
                        minuscount2++;
                }
                else if(mili2_100>=200)
                {
                    mili2_100=0;
                    pluspara2=pluscount2;
                    minuspara2=minuscount2;
                    if(pluspara2<=1)
                    pluspara2=1;
                    if(minuspara2<=1)
                    minuspara2=1;
                    pluscount2=0;
                    minuscount2=0;
                }
                enccount=0;
            }
        }
/**************************Encoder read start here*************************************************/

/**************************Key application start here*************************************************/
            if(prevkey!=key)
            {
                //Send_Byte(key);
                key_application(key);
                if(key!=key_no) 
                {
                    count_1ms=0;
                    onesecf=1;
                    txonf=1;
                }
            }    
            prevkey=key;
/**************************Key application end here*************************************************/

/******************************When weld is OFF********************************************************/
      if((psstatus.weldoncyclestrt!=1)&&(cGasRlyClrfg == 0))//(TORCH=='X')
        {
            if( (prevsetwirespeed!=setwirespeed) || (prevsetcurrent!=setcurrent) || dispupdatef==1 )
            {
                if((prevsetwirespeed!=setwirespeed) && (prevsetwirespeed > setwirespeed))
                {
                    wfspeedchangef=1;
                }
                if(Type.wirespeed==1)
                {
                    Type.wirespeed=1;
                    Type.amp=0;
                    Type.thickness=0;
                    //TypeDP.DPGROUP[0]=0x00;
                    Typedp.digitdp1	 =0;
                    Typedp.digitdp2	 =1;
                    Typedp.digitdp3	 =0;
                    disp_hex_window1(setwirespeed);
                }
                else if(Type.amp==1)
                {
                    Type.wirespeed=0;
                    Type.amp=1;
                    Type.thickness=0;
                    Typedp.digitdp1	 =0;
                    Typedp.digitdp2	 =0;
                    Typedp.digitdp3	 =0;
                    disp_hex_window1(setcurrent);
                }
                else if(Type.thickness==1)
                {
                    Type.wirespeed       =0;
                    Type.amp             =0;
                    Type.thickness       =1;
                    Typedp.digitdp1	 =0;
                    Typedp.digitdp2	 =1;
                    Typedp.digitdp3	 =0;
                    disp_hex_window1(pstowfstr.setthickness);
                }
                
                           
                pstowfstr.setwspeed=setwirespeed;  //@ send wire speed to power source

                count_1ms=0;
                onesecf=1;
                txonf=1;
            }
            prevsetwirespeed=setwirespeed;
            prevsetcurrent=setcurrent;

            if(((prevsetvoltage!=setvoltage) || dispupdatef==1) && (Type.vtg==1) )
            {
                Typedp.digitdp4	 =0;
                Typedp.digitdp5	 =1;
                Typedp.digitdp6	 =0;
                Type.arclength   =0;
                Type.vtg         =1;
                Type.sec         =0;
                disp_hex_window2(setvoltage);
//                disp_hex_window1(iTest);
                pstowfstr.Lo_setvoltage=setvoltage;
                pstowfstr.Hi_setvoltage=setvoltage >> 8;
                count_1ms=0;
                onesecf=1;
                txonf=1;
                prevsetvoltage=setvoltage;
                parclength=100; //dummy right to update display
            }
            //prevsetvoltage=setvoltage;

            if(((parclength!=pstowfstr.arclength) || dispupdatef==1) && (Type.arclength==1))
            {


                if(weldmode=='P')
                {
                if(pstowfstr.arclength>=40)
                    disparclength=pstowfstr.arclength-40;
                else
                    disparclength=40 - pstowfstr.arclength;
                }

                if(weldmode=='G')
                {
                disparclength=pstowfstr.arclength;
                }

               Typedp.digitdp4	 =0;
                Typedp.digitdp5	 =0;
                Typedp.digitdp6	 =0;
                Type.arclength   =1;
                Type.vtg         =0;
                Type.sec         =0;
                disp_hex_window2(disparclength);


                if(weldmode=='P')
                {
                if(pstowfstr.arclength>=40)
                    diswin1[3]=0x25;        //display Blank
                else
                    diswin1[3]=0x26;        //display dash--
                }
                else
                    diswin1[3]=0x25;        //display Blank

                //disp_hex_window2(transoff.arclegth);//disparclength);//transoff.arclegth);
                count_1ms=0;
                onesecf=1;
                txonf=1;
               prevsetvoltage=0; //dummy right to update display
              parclength=pstowfstr.arclength;
            }
            
            //if(inchkeyon==0)
            if(psstatus.gasoncommand!=1)
                GAS_RLY         =0;
            if((psstatus.motoroncommand!=1) || ((TORCH == 'X') && (wfstatus.twotfourtmode1 == 0)) )
                Update_PWM(setwirespeed*0);
            
			speeedrate=0;		  
            openloopcnt =0;
            softstartf  =0;
            dispupdatef =0;
            closeloopf=0;
            cyclestrtf=0;

            psstatus.creepspeedon=1;
            //transoff.creepspeedon=1;
            //GAS_RLY     =0;
        }
/******************************When weld is on********************************************************/
        else if(psstatus.weldoncyclestrt==1)//(TORCH=='P')
        {

            if(cEditfg == 1)
            {
                if((prevsetwirespeed!=setwirespeed))
                {
                    pstowfstr.setwspeed=setwirespeed;
                    
                    count_1ms=0;
                    onesecf=1;
                    txonf=1;
                    
                    prevsetwirespeed=setwirespeed;
					newsetwirespeed=setwirespeed;
					Update_PWM(newsetwirespeed*MTR_VTG_CONSTANT);			  
                }
            }
            if(cEditfg == 1)
            {
                if(prevsetvoltage!=setvoltage)
                {
                    pstowfstr.Lo_setvoltage=setvoltage;
                    pstowfstr.Hi_setvoltage=setvoltage >> 8;
                    count_1ms=0;
                    onesecf=1;
                    txonf=1;
                    prevsetvoltage=setvoltage;
                }
            }

            if(psstatus.gasoncommand==1)
            {
                GAS_RLY         =1;
            }
            else
            {
                GAS_RLY         =0;
            }
            if(psstatus.motoroncommand==1)
            {
               if(psstatus.creepspeedon==1)
               {
                    cyclestrtf=0;
                 //   newsetwirespeed=(setwirespeed>>1);

                    newsetwirespeed=setwirespeed*creep_speed*0.01;

                    if(newsetwirespeed<=10)
                      newsetwirespeed=10;//setwirespeed;                // 30  changed on 12042021

                //    else if(newsetwirespeed>=60)
                //       newsetwirespeed=60;
                     Update_PWM(speeedrate*4); ///50% pwm 400 count
                    
                    if(speeedrate < newsetwirespeed)
                    {
                         speeedrate=speeedrate+4;
                         for(delinch1=0;delinch1<3;delinch1++)
                         for(delinch=0;delinch<30000;delinch++);
                    }
                     //Update_PWM(newsetwirespeed*MTR_VTG_CONSTANT);
                     //TRISMOTOR_TRIP11=0;
//                     MTRFB=1;
                    
              }   
               else if(psstatus.creepspeedon==0)
               {
                   cyclestrtf=1;
                   if(cMtrOverLdfg == 0)
                   {
                    newsetwirespeed=setwirespeed;
                   }else
                   {
                    newsetwirespeed=0;
                   }
                   if(closeloopf==0)
                   {
                        Update_PWM(newsetwirespeed*MTR_VTG_CONSTANT);
                        if(wfspeedchangef==1)
                        {
//                            integral_old=newsetwirespeed*scalefactor2*MTR_VTG_CONSTANT;//2.6;
                            integral_old=newsetwirespeed*scalefactor2*2.6;
                            wfspeedchangef=0;
                            integral_new =0;
                            //integral_old=0;
                            error_old =0;
                            error_new=0;
                            controller_out=0;
                            prevFltpfreq=0;
                            Fltpfreq=0;
                        }
                       closeloopf=1;
                   }
                   //TRISMOTOR_TRIP11=0;
//                   MTRFB=0;
               }

               if(psstatus.craterspeedon==1 && wfstatus.twotfourtmode1==1)
                 newsetwirespeed=crater_speed;
               
                if(newsetwirespeed >= 10)
                    setpfreq=(MTR_FREQ_CONSTANT*newsetwirespeed);//setpfreq=(3.1878*setwirespeed)-0.044;
               if(cRelSpeedSign == '+')
               {
                    Hi_setppwm=(newsetwirespeed+rel_wirespeed)*MTR_FREQ_CONSTANT;
               }
               else
               {
                    Hi_setppwm=(newsetwirespeed-rel_wirespeed)*MTR_FREQ_CONSTANT;
               }
//                Lo_setppwm=(newsetwirespeed-rel_wirespeed)*MTR_VTG_CONSTANT;
                Lo_setppwm=(newsetwirespeed)*MTR_FREQ_CONSTANT;// changed on 10122020.
            }
            else if((psstatus.motoroncommand!=1) || ((TORCH == 'X') && (wfstatus.twotfourtmode1 == 0)) )//(psstatus.motoroncommand!=1)
            {
                Update_PWM(setwirespeed*0);
                openloopcnt =0;
                closeloopf  =0;
                closeloop1f =0;
                cyclestrtf=0;

            }
                Type.wirespeed=0;
                Type.amp=1;
                Type.thickness=0;
                Type.arclength   =0;
                Type.vtg         =1;
                Type.sec         =0;

                TypeDP.DPGROUP[0]=0x00;
                Typedp.digitdp5	 =1;
                disp_hex_window1(Actual_amp);
                disp_hex_window2(Actual_vtg);
                dispupdatef     =1;
            //GAS_RLY         =1;
       }
    }

      if(universal_error_latch==1)
      {
          dispupdatef=1;
          universal_error_latch=0;
      }
        if(( (weldmode=='P') || (weldmode=='G') ))
       detect_display_error();
    }
}

void key_application(unsigned char keypress)
{
    if(keypress==key_gason)//'A')
    {
        while(key==key_gason)
        {
           Type.gason      =1;
           GAS_RLY         =1;
           //status.gasoncommand    =1;
           
           diswin1[0]= 0x11;//'G';
           diswin1[1]= 0x0B;//'A';
           diswin1[2]= 0x1D;//'S';
           
           diswin1[3]= 0x19;//'O';
           diswin1[4]= 0x18;//'N';
           diswin1[5]= 0x25;// all off
           cGasRlyClrfg = 1;
           iGasDbCnt = 500;

         }
        if(iGasDbCnt == 0)
        {
        Type.gason      =0;
        GAS_RLY         =0;
        dispupdatef     =1;
        }

    }
    else if(keypress==key_inch)//'B')
    {
        inchcnt=10;
        while(key==key_inch)
        {
           Type.inch       =1;
           //status.inchon   =1;
           //inchkeyon    =1;
           diswin1[0]   =0x13;//'I';
           diswin1[1]   =0x18;//'N';
           diswin1[2]   =0x0D;//'C';
           Update_PWM(inchcnt*4); ///50% pwm 400 count
           disp_hex_window2(inchcnt);
           if(inchcnt<100)
           {
                inchcnt=inchcnt+10;
                for(delinch1=0;delinch1<5;delinch1++)
                for(delinch=0;delinch<50000;delinch++);
           }
         }
         Update_PWM(inchcnt*0);
         Type.inch       =0;
         //status.inchon   =0;
         inchkeyon       =0;
         dispupdatef     =1;
    }
    else if(keypress==key_mode)//'C')//Key_s3==1)
    {
        //current++;
        //disp_hex_window1(current);
        //Display();
        if(Type.twot==1)
        {
            Type.twot=0;
            Type.fourt=1; 
            wfstatus.twotfourtmode1=1;
            cWf2t4tmodefg = 1;
        }
        else if(Type.fourt==1)
        {
            Type.fourt=0;
            Type.twot =1;
            wfstatus.twotfourtmode1=0;
            cWf2t4tmodefg = 0;
        }
        cEditfg = 1;
    }
    else if(keypress==key_disp)//'D')//Key_s4==1)
    {
        //Send_Byte('1');
        if(Type.wirespeed==1)
        {
            //TypeU.LEDGROUP[0]=0x00;
            //TypeU.LEDGROUP[1]=0x00;
            Type.wirespeed=0;
            Type.amp=1;
            Type.thickness=0;
            TypeDP.DPGROUP[0]=0x00;
            Typedp.digitdp5	 =1;
            //Send_Byte('W');
        }    
        else if(Type.amp==1)
        {
            //TypeU.LEDGROUP[0]=0x00;
            //TypeU.LEDGROUP[1]=0x00;
            Type.wirespeed=0;
            Type.amp=0;
            Type.thickness=1;
            TypeDP.DPGROUP[0]=0x00;
            Typedp.digitdp2	 =1;
            Typedp.digitdp5	 =1;
            //Send_Byte('a');
        }
        
        else if(Type.thickness==1)
        {
            //TypeU.LEDGROUP[0]=0x00;
            //TypeU.LEDGROUP[1]=0x00;
            Type.wirespeed=1;
            Type.amp=0;
            Type.thickness=0;
            TypeDP.DPGROUP[0]=0x00;
            Typedp.digitdp2	 =1;
            Typedp.digitdp5	 =1;
            //Send_Byte('t');
        }

        dispupdatef     =1;
    }
    else if(keypress==key_no) //'X')
    {
        Type.gason       =0;
        Type.inch        =0;
        //GAS_RLY          =0;
        //status.gason     =0;
        //status.inchon    =0;
        inchkeyon        =0;
    }    
}
void system_init()
{
   
    //CONFIG1bits.FOSC=4;
    OSCCONbits.IRCF=14;
    //OSCCONbits.SPLLEN=1;
    OSCCONbits.SCS=0;
    OSCTUNEbits.TUN=0;
}

void portpin_init()
{
    TRISA=0x1F;                 //0001 1111
    TRISB=0x00;
    TRISC=0x00;
    ANSELA=0X00;
    ANSELB=0X00;
    //ANSELC=0X00;
    //DECODE_EN=1;
     PORTA=0X00;
     PORTC=0X00;
     TRISEN1A   =1;
     TRISEN1B   =1;
     TRISEN2A   =1;
     TRISEN2B   =1;
     TRISMPULSE =1;
     TRISGAS_RLY=0;
     TRISMOTOR_TRIP11=1;//1;
     TRISTORCHIN=1;
     TRISMTRFB=0;
    //unsigned int delay=0;
}

void Timer0_init(void)
{
    TMR0=0;
    OPTION_REGbits.PSA=0;       //PRESCALER ASSIGN TO timer0
    OPTION_REGbits.T0CS=0;      // INTERNAL CLK
    OPTION_REGbits.PS=5;//3;    //3=1:16 prescale value
    INTCONbits.GIE=0;//1;
    INTCONbits.PEIE=0;//1;
    INTCONbits.T0IF=0;          //Period = (256 - TMR0)*(4/fosc)*(Prescaler)
                                //250usec=(256-TMR)*(4/32mhz)*16
                                //250usec=(256-TMR0)*0.125usec*16;
                                //250usec=(256-TMR0)*2usec
                                //125usec=(256-TMR0)
                                //TMR0   =(256-125)=131==0x83;
    TMR0=0x85;                  //125=7D    85 PRACTICALLY CALCULATED. //0X85=250USEC INTERRUPT 
    INTCONbits.T0IE=1;
}

void PWM_init()
{
    //CCP1CONbits.P1M=0;
    CCP1CONbits.CCP1M=13;               //PWM MODE
    CCP1CONbits.DC1B=0;                 //LSB OF PWM COUNT
    CCPR1L=0;
    TRISCbits.TRISC2=0;
    PR2=0xC7;//0X9F;//0xC7;
    T2CONbits.T2CKPS=1;//1;//0;     //PRESCALE IS 1
    T2CONbits.T2OUTPS=0;     //POST SCALE 1
    PIR1bits.TMR2IF=0;
    PIE1bits.TMR2IE=1;
    T2CONbits.TMR2ON=1;     //START TIMER 2
}
void Update_PWM(unsigned int setwsduty)
{
    unsigned int Temp1=0x00, Dutycnt=0;
    Dutycnt=setwsduty;
    CCP1CONbits.DC1B=Dutycnt;
    Temp1=Dutycnt >> 2;
    CCPR1L=Temp1;
    iTest = Temp1;
}

void capture_init()
{
    TRISMPULSE =1; //TRISC=0b00000100;      // 00000100; set RC2 to input(CCP1)         OSCCON = 0x70;         // 01110000; system clock - 8MHz 
    //IPR2 = 0x04;           // 00000100; CCP1 interrupt set to high priority 
    PIE2bits.CCP2IE = 1;//mahesh 1;    // CCP1 interrupt enabled
    CCP2CONbits.CCP2M=0x05; // 00000101; CCP1 as capture mode, every rising edge
    TMR1H = 0x00;          // clear timer1 
    TMR1L = 0x00; 
    PIR1  = 0x00;           // clear the interrupt flags 
    //RCONbits.IPEN = 1;     // interrupt priority enabled         CCP1CON = 0x05;        // 00000101; CCP1 as capture mode, every rising edge  
    T1CON = 0x21;//fosc/4, 1:4  0.5usec-32msec 0x61;//0x71;//B1;//81;    1:16      // 10000001; Timer1 enabled; prescale 1:1
    INTCONbits.GIE = 1;    // enable interrupts 
    INTCONbits.PEIE = 1; 
    //      while(1)            // main loop 
    //      { 
    //         //PIR1bits.CCP1IF =1; //to test if my program will go into isr() 
    //      } 
}    

 void uart_init()
{
    RCSTAbits.SPEN=1;       //Serial Port Enable bit 0=disabled  1= enabled
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=1;
    TXSTAbits.BRGH=0;       //High Baud Rate Select bit 0= low speed  1=high speed
    BAUDCTLbits.BRG16=0;    //0 = 8-bit Baud Rate Generator is used  1=16 bit
    TXSTAbits.SYNC=0;       //0= Asynchronous mode  1=Synchronous mode
    SPBRG=51;//25;//51;//12;//9600@51,19.2k@25,38.4k@12               //Fosc=32M Hz Fosc/[64(n+1)]
    TXSTA=0x20;             //Transmit enabled
    TXSTAbits.TXEN=0;//1;       //Transmit enabled
    RCSTAbits.CREN=0;//1;       //Enables receiver
    PIE1bits.RCIE=0;        //Enables the EUSART receive interrupt
    PIE1bits.TXIE=0;        //Enables the EUSART receive interrupt
    
}
 /*
 void uart_init()
{
    RCSTAbits.SPEN=1;       //Serial Port Enable bit 0=disabled  1= enabled
    TRISCbits.TRISC6=1;
    TRISCbits.TRISC7=1;
    TXSTAbits.BRGH=0;       //High Baud Rate Select bit 0= low speed  1=high speed
    BAUDCTLbits.BRG16=0;    //0 = 8-bit Baud Rate Generator is used  1=16 bit
    TXSTAbits.SYNC=0;       //0= Asynchronous mode  1=Synchronous mode
    SPBRG=12;//51;//12;//51;//12=9600@8MHz , 51=9600@32MHz  25;//51;//12;               //Fosc=32M Hz Fosc/[64(n+1)]
    TXSTA=0x20;             //Transmit enabled
    TXSTAbits.TXEN=1;       //Transmit enabled
    RCSTAbits.CREN=1;       //Enables receiver
    PIE1bits.RCIE=0;        //Enables the EUSART receive interrupt
}
*/
 
void Send_Byte(unsigned char transbyte)
{
    while(TXSTAbits.TRMT != 1);
    TXREG=transbyte;
}



 
void transmittops()
{
    chksum=0;
    pstowfstr.psstatusbyte=0xBB;//psstatusu.psstatusbyte[0];

    if(cWf2t4tmodefg == 1)
    {
        wfstatus.twotfourtmode1 = 1;
    }
    else
    {
        wfstatus.twotfourtmode1 = 0;
    }
    pstowfstr.wfstatusbyte=wfstatusu.wfstatusbyte[0];
    //TRISMOTOR_TRIP1=0;
    //if( wfstatus.torchonstatus==1)
    //MOTOR_TRIP1=1;
    //else
    //MOTOR_TRIP1=0;
    
    // transoffu.transarr[21]=transoff.wfstatusbyte;

    Tx_ptr=0;
    Send_Byte('@');
    if(cMtrOverLdfg == 1)
    {
        pstowfstru.pstransarr[16] = 0x10;//erroru.errorstatusbyte[0];
    }
    for(lmn=0;lmn<=TRANSMIT_STRING_LENGTH;lmn++)        //21
    {
	chksum=chksum+pstowfstru.pstransarr[lmn];
	Send_Byte(pstowfstru.pstransarr[lmn]);
    }
    if(cEditfg == 1)
    {
        Send_Byte('E');
    }
    else
    {
         Send_Byte('X');
    }
    Send_Byte(chksum);
}
//8237421336
void send_status()
{
   pstowfstr.wfstatusbyte=wfstatusu.wfstatusbyte[0];
   Send_Byte('#');
   Send_Byte(pstowfstr.wfstatusbyte);
   Send_Byte(pstowfstr.wfstatusbyte); //?
}


void detect_display_error(void)
{
//add complete array to comm array and sent to power source
 pstowfstr.error_code1=erroru.errorstatusbyte[0];
 pstowfstr.error_code2=erroru.errorstatusbyte[1];
    
    if(errorstatus.uv_er1==1)
    {
        universal_error=1;
        diswin1[5]=1; //1
    }
    else if(errorstatus.ov_er2==1)
    {
        universal_error=1;
        diswin1[5]=2; //2
    }
    else if(errorstatus.th_er3==1)
    {
        universal_error=1;
        diswin1[5]=3; //3
    }
    else if(errorstatus.no_curr_er4==1)
    {
        universal_error=1;
        diswin1[5]=4; //4
    }else if(errorstatus.motor_over_ld_er5==1)
    {
        universal_error=1;
        diswin1[5]=5; //4
    }
    else if(errorstatus.wirefdr_er6==1)
    {
        universal_error=1;
        diswin1[5]=6; //4
    }
    else if(errorstatus.water_press_er7==1 && ( (weldmode=='P') || (weldmode=='G') )  )
    {
        universal_error=1;
        diswin1[5]=7; //4
    }
    else if(error8==1)
    {
       universal_error=1;
       diswin1[5]=8; //8
    }
    else if(errorstatus.motor_fb_err==1)
    {
       universal_error=1;
       diswin1[4]=1; //8
       diswin1[5]=0; //8
    }
    else
        universal_error=0;

    if(universal_error==1)
    {
    universal_error_latch=1;
    diswin1[0]=0x0F; //E
    diswin1[1]=0x1C; //R
    diswin1[2]=0x1C; //R

    diswin1[3]=0; //0
    diswin1[4]=0; //0
    
    GAS_RLY         =0;
    Update_PWM(0);
    TypeDP.DPGROUP[0]=0;
    errorstatus.comm_er8=1;
    }

}