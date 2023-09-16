/*
 CHAMP 250A/400A/600A
 * Author: SW05
 * CHAMP 400X Revision 2.4 Bluetooth Testing use newmain3.c
 */

#include "pic18f46k40.h"
#include<xc.h>
//#include "math.h"
#include "define.h"
#include "structure.h"
#include "variable.h"
#include "function.h"

// CONFIG1L
#pragma config FEXTOSC  = OFF                   // ->Oscillator not enabled
//#pragma config RSTOSC   = HFINTOSC_64MHZ    	// ->HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1
//#pragma config FEXTOSC  = 0x04
//#pragma config RSTOSC   = 0x00
//#pragma config CSWEN    = 0

#pragma config BOREN    = OFF
#pragma config MCLRE    = EXTMCLR 
#pragma config LVP      = OFF              //ON

#pragma config STVREN   = OFF 
#pragma config WDTE     = OFF

// CONFIG1H
/*#pragma config CLKOUTEN   = OFF       // ->CLKOUT function is disabled
#pragma config CSWEN        = ON        // ->Writing to NOSC and NDIV is allowed
#pragma config FCMEN        = ON        // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor enabled

// CONFIG2L
#pragma config MCLRE        = EXTMCLR    // ->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR 
#pragma config PWRTE        = OFF       // Power-up Timer Enable bit->Power up timer disabled
#pragma config LPBOREN      = OFF       // ->ULPBOR disabled
#pragma config BOREN        = SBORDIS   // Brown-out Reset Enable bits->Brown-out Reset enabled , SBOREN bit is ignored

// CONFIG2H
#pragma config BORV         = VBOR_2P45    // Brown Out Reset Voltage selection bits->Brown-out Reset Voltage (VBOR) set to 2.45V
#pragma config ZCD          = OFF    // ZCD Disable bit->ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON
#pragma config PPS1WAY      = ON    // PPSLOCK bit One-Way Set Enable bit->PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle
#pragma config STVREN       = ON    // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config DEBUG        = OFF    // Debugger Enable bit->Background debugger disabled
#pragma config XINST        = OFF    // Extended Instruction Set Enable bit->Extended Instruction Set and Indexed Addressing Mode disabled

// CONFIG3L
#pragma config WDTCPS   = WDTCPS_31    // ->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE     = OFF    // WDT operating mode->WDT Disabled

// CONFIG3H
#pragma config WDTCWS   = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS   = SC    // WDT input clock selector->Software Control

// CONFIG4L
#pragma config WRT0     = OFF    // Write Protection Block 0->Block 0 (000800-003FFFh) not write-protected
#pragma config WRT1     = OFF    // Write Protection Block 1->Block 1 (004000-007FFFh) not write-protected
#pragma config WRT2     = OFF    // Write Protection Block 2->Block 2 (008000-00BFFFh) not write-protected
#pragma config WRT3     = OFF    // Write Protection Block 3->Block 3 (00C000-00FFFFh) not write-protected

// CONFIG4H
#pragma config WRTC     = OFF    // Configuration Register Write Protection bit->Configuration registers (300000-30000Bh) not write-protected
#pragma config WRTB     = OFF    // Boot Block Write Protection bit->Boot Block (000000-0007FFh) not write-protected
#pragma config WRTD     = OFF    // Data EEPROM Write Protection bit->Data EEPROM not write-protected
#pragma config SCANE    = ON    // ->Scanner module is available for use, SCANMD bit can control the module
#pragma config LVP      = ON    // Low Voltage Programming Enable bit->Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored

// CONFIG5L
#pragma config CP       = OFF    // UserNVM Program Memory Code Protection bit->UserNVM code protection disabled
#pragma config CPD      = OFF    // DataNVM Memory Code Protection bit->DataNVM code protection disabled

// CONFIG6L
#pragma config EBTR0    = OFF    // Table Read Protection Block 0->Block 0 (000800-003FFFh) not protected from table reads executed in other blocks
#pragma config EBTR1    = OFF    // Table Read Protection Block 1->Block 1 (004000-007FFFh) not protected from table reads executed in other blocks
#pragma config EBTR2    = OFF    // Table Read Protection Block 2->Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks
#pragma config EBTR3    = OFF    // Table Read Protection Block 3->Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks

// CONFIG6H
#pragma config EBTRB    = OFF    // Boot Block Table Read Protection bit->Boot Block (000000-0007FFh) not protected from table reads executed in other blocks
*/



//void Write_EEPROM(unsigned int,unsigned int);
//unsigned int Read_EEPROM(unsigned int);
//void memorystore(void);
//void memoryread(void);
//void ADCC_ISR(void);

void __interrupt() INTERRUPT_InterruptManager (void)
{
    if(OCV_OFF == 1)
    {
        Error_flag= 1;
        err_dispfg= 1;
        SHDNLAT= 1;
        daccount= 0;
        VRD_LEDLAT= 0;
        Delay(30,'s');
        Error_flag=0;
        err_dispfg=0;
        SHDNLAT=0;
        OCV_OFF=0;
        VRD_LEDLAT=1;
        
    }
      
    if(PIR0bits.TMR0IF == 1)  //1 MS
    {
        PIR0bits.IOCIF  = 0;
        PIR0bits.TMR0IF = 0;
        TMR0H   =   0xD1;
        TMR0L   =   0x20;
        cnt1ms++;
        display();
        ADCON0bits.ADGO = 1;
        VRDTimecnt_1s++;
        count_10Ms++;
        cnt_10ms++;
        if(ucBlutoothInit==1)
        {
            uiBCnt++;
            if(uiBCnt>2000)
            {
               uiBCnt=0;ucCMDSEND=1; 
            }
        }
        else
        {
            uiBCnt++;
            if(uiBCnt>1000)
            {
               uiBCnt=0;ucDataSend=1; 
            }  
        }
        if(cPowerONfg == 1)
        {
            if(iPowerONcnt == 0)
            {
                iPowerONcnt = 0;
                cPowerONfg = 0;
            }
            else
            {
                iPowerONcnt--;
            }
        }
        
        
        if(( ucArcOnTimeReset == 0) && (cArcOnfoundfg == 0) && (cResetMenufg == 0))                    //SWITCH PRESSED
        {                
            iTimeResetSwitchcnt++;

            if(iTimeResetSwitchcnt >= 5) 
            {               
                cArcOnfoundfg = 1;                    
            }                       
        }
        else if(( ucArcOnTimeReset == 0) && (cArcOnfoundfg == 1) && (cResetMenufg == 0))
        {
            iTimeResetSwitchcnt++;
            
            if(iTimeResetSwitchcnt >= 5000) 
            {       
                cArcOnfoundfg = 0;
                cResetMenufg = 1;                    
                ArcOnMenuMode = 2;                               
            }  
        }

        else if(( ucArcOnTimeReset == 1) && (cArcOnfoundfg == 1))
        {          
            iResetcnt1++;
            if(iResetcnt1 >= 5)
            {
                ArcOnMenuMode++;          

                if(ArcOnMenuMode >= 2)
                {
                    ArcOnMenuMode = 0;
                }    
                cArcOnfoundfg = 0;
                iResetcnt1 = 0;
            }
        } 
        else if(( ucArcOnTimeReset== 1) && (cResetMenufg == 1))
        {          
            iResetcnt1++;
            if(iResetcnt1 >= 5)
            {                       
                if(ArcOnMenuMode == 2)
                {
                    ArcOnMenuMode = 0;
                }                               
                cResetMenufg = 0;
                iResetcnt1 = 0;
                iTimeResetSwitchcnt=0;
            }
        } 
            

//-------------------------------------------------------------------------------------------------------------------        
        if(VRDTimecnt_1s >= 10)
        {
            VRDTimecnt_1s = 0;
            if(iVRD_Time != 0) 
            {
                if((iActualvolt1 > 650) && (weldonfg == 0) && (cEditfg == 0))       //700
                {
                    if(cMode == 'M')
                    {
                        ivrdcnt++;
                    }
                    if((ivrdcnt >= (iVRD_Time*100)) && (cVRD_fg == 0) && (cMode == 'M'))                   
                    {                   
                        SHDNLAT = 1;
                        VRD_LEDLAT = 0;
                        ivrdcnt = 0;
                        cVRD_fg = 1;
                        cRecordVRDONvtg = 1;
                        iSampleVRDvtgcnt = 0;
                    }                
                }
                else if(cVRD_fg == 0)
                {
                    SHDNLAT = 0;
                    VRD_LEDLAT = 1;
                }
            }
            else if(iVRD_Time == 0)
            {            
                SHDNLAT = 0;
                VRD_LEDLAT = 1;
                cVRD_fg = 0;
                ivrdcnt = 0;
            }

            if(cVRD_fg == 1) 
            {
                if((((iActualVRDvtgON*90)/100) > iActualvolt1) && (cRecordVRDONvtg == 0))
                {
                    ivrdcnt = 0;
                    cVRD_fg = 0;
                }
            }
        }
//-------------------------------------------------------------------------------------------------------------------
        if(cnt1ms >=10)
        {
            c10Msecfg = 1;
            
            if(iPOndelay == 0)
            {
                
            }
            else
            {
                iPOndelay--;
            }
            cnt1ms = 0;
        }
     
        if(cFlashCntr != 0)
        {
            cFlashCntr--;
        }
        else
        {
            cFlashCntr = 0;
        }
        
        if(weldonfg == 1)
        {
            timecnt++;
            
            if(timecnt>=1000)
            {
                timecnt=0;
                sec++;
                if(sec>=60)
                {
                    sec=0;
                    min++;
                }
                if(min>=60)
                {
                    min=0;
                    sec=0;
                    hr++;
                }
                if(hr>=99)
                {
                    min=0;
                    sec=0;
                    hr=0;
                }               
            }
        }      
    }    

    if(PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
    {        
        ADC_BUF = ADRESH;
        ADC_BUF = ADC_BUF << 8;
        ADC_BUF  = (ADC_BUF + ADRESL);
                    
        if(channel == 0)
        {                
            iVolt = ADC_BUF;

            AFvtg+=iVolt;
            AFvtgcnt++;
            if(AFvtgcnt >= 16)
            {
                iActualvolt = AFvtg;
                iActualvolt = iActualvolt >> 4;
                iActualvolt = iActualvolt * 1.5338;
                dispvtgupdatefg=1;
                AFvtg = 0;
                AFvtgcnt = 0;
            }
            //----------------------------------------------------------------
            iVolt1 = ADC_BUF;
            AFvtg1+=iVolt1;
            AFvtgcnt1++;
            if(AFvtgcnt1 >= 64)
            {
                iActualvolt1 = AFvtg1;
                iActualvolt1 = iActualvolt1 >> 6;
                iActualvolt1 = iActualvolt1 * 1.5338;
                if(cRecordVRDONvtg == 1)
                {
                    iSampleVRDvtgcnt++;
                    if(iSampleVRDvtgcnt >= 3)
                    {
                        iActualVRDvtgON = iActualvolt1;
                        cRecordVRDONvtg = 0;
                        iSampleVRDvtgcnt = 0;
                    }
                }
                dispvtgfg = 1;
                AFvtg1 = 0;
                AFvtgcnt1 = 0;
            }
            //----------------------------------------------------------------
            channel = 1;
            ADPCH = 0x01;      
        }
        else if(channel == 1)
        {          
            iCurr = ADC_BUF;

            AFcurr+=iCurr;
            AFcurrcnt++;
            if(AFcurrcnt >= 64)
            {
                iActualcurr = AFcurr;
                iActualcurr = (iActualcurr >> 6);
                
                if(iActualcurr<=80)
                 iActualcurr = (iActualcurr * 5.3)/10; //+ iDispFBCurrCaliCount;//4.5;
                else if((iActualcurr>80) && (iActualcurr<=245))
                 iActualcurr = (iActualcurr * 5.2)/10; //+ iDispFBCurrCaliCount;//4.5;
                else
                   iActualcurr = (iActualcurr * 5.0)/10; 
                
                //iActualcurr = ((iActualcurr * 4.88)/10) ;
                iActualcurr = iActualcurr*2.3;
                dispcurrfg = 1;
                AFcurr = 0;
                AFcurrcnt = 0;
            }                       
            channel = 13;
            ADPCH = 0x0D;
        } 
        else if(channel == 13)
        {             
            iRemote = ADC_BUF;    
            AFremotecurr+=iRemote;
            AFremotecnt++;
            
            if(AFremotecnt >= 32) 
            {                           
                AFremotecurr      = AFremotecurr >> 5;
                iActualRemotecurr = AFremotecurr;             
                iActualRemotecurr = iActualRemotecurr * 4.88;
                iRemoteCheckcnt   = iActualRemotecurr;
                
                ftemp = iActualRemotecurr;

                fGndRes = (ftemp * 10000) /(5000 - ftemp);
 
                ftemp = (fGndRes * 5000) / (10000 + 9600); 

                iActualRemotecurr = ftemp; 
                               
 
                if(cModel_Select == 1)
                {
                    fOffset = 9.5;                         
                }
                else if(cModel_Select == 2)
                {                
                    fOffset = 6.2;                            
                }                
                else if(cModel_Select == 3)
                {
                    fOffset = 4.0;                       
                }
                iRemotecnt = 3900;                                        
                if(iRemoteCheckcnt <= iRemotecnt)               
                {                  
                    cRemoteDetectedfg = 1;                   
                    iActualRemotecurr = iActualRemotecurr/fOffset;
                    
                    if(cModel_Select == 1)
                    {
                        if(iActualRemotecurr <= 10)
                            iActualRemotecurr = 10;                        
                        if(iActualRemotecurr >= 250)
                            iActualRemotecurr = 250;                        
                        setcurrent = iActualRemotecurr;
                    }
                    else if(cModel_Select == 2)
                    {           
                        if(iActualRemotecurr <= 10)
                            iActualRemotecurr = 10;                         
                        if(iActualRemotecurr >= 400)
                            iActualRemotecurr = 400;                        
                        setcurrent = iActualRemotecurr;                        
                    }
                    else if(cModel_Select == 3)
                    {         
                        if(iActualRemotecurr <= 20)
                            iActualRemotecurr = 20;                         
                        if(iActualRemotecurr >= 600)
                            iActualRemotecurr = 600; 
                        
                        setcurrent = iActualRemotecurr;
                    }
                    if(iPrevSetcurrent != setcurrent)
                    {
                        iPrevSetcurrent = setcurrent;
                        cRemoteEnDCurrUpdatefg = 1; 
                    }                                       
                }
                else    
                {     
                    if(cRemoteDetectedfg == 1)
                    {                       
                        iPrevDisplaySetcurrent = 0;
                        Display_updatefg = 1;                       
                    }
                    cRemoteDetectedfg = 0;                    
                }
                
                AFremotecurr = 0;
                AFremotecnt = 0;
            } 
            channel = 2;         
            ADPCH = 0x02;             
        } 
        else if(channel == 2)
        {
            iTripVolt = ADC_BUF;
            count_3s++;
            AFtripvtg+=iTripVolt;
            AFtripvtgcnt++;
            if(AFtripvtgcnt >= 64)
            {
                iActualtripvolt = AFtripvtg;
                iActualtripvolt = iActualtripvolt >> 6;
                iActualtripvolt = iActualtripvolt * 4.88;

                disptripvtgfg = 1;
                AFtripvtg = 0;
                AFtripvtgcnt = 0;
            }
            Trip_detect(tripvoltage); 
            channel = 21;
            ADPCH = 0x15;   
                         
        }
        else if(channel == 21)
        {
            iTripVolt1 = ADC_BUF;

            AFtripvtg1+=iTripVolt1;
            AFtripvtgcnt1++;
            if(AFtripvtgcnt1 >= 64)
            {
                iActualtripvolt1 = AFtripvtg1;
                iActualtripvolt1 = iActualtripvolt1 >> 6;
                iActualtripvolt1 = iActualtripvolt1 * 4.88;
                
                AFtripvtg1 = 0;
                AFtripvtgcnt1 = 0;
            }
            Trip_detect_OV(tripvoltage1); 
            channel = 4;
            ADPCH = 0x04;                
        }     
        else if(channel == 4)
        {    
            iPotSetcurrent = ADC_BUF;
            ASetcurrent+=iPotSetcurrent;
            if(cRemoteDetectedfg == 0)
            {                    
                ASetcurrentcnt++;    
            }
            if(ASetcurrentcnt >= 16)  
            {         
                ASetcurrent = ASetcurrent >> 4;
                iDispSetcurrent  = ASetcurrent;             
                iDispSetcurrent  = iDispSetcurrent * 4.88; //divide by 10;                
                iModelSelectBand = iDispSetcurrent;    
                
                /*
                iDispSetcurrent = iDispSetcurrent/10;
                iDispSetcurrent = iDispSetcurrent*1.25;
                setcurrent = iDispSetcurrent;
                */
                if(cModel_Select == 1)
                {                    
                    iDispSetcurrent = iDispSetcurrent/19;
                    setcurrent      = iDispSetcurrent;

                    if(setcurrent <= 10)
                        setcurrent = 10;                         
                    if(setcurrent >= 250)
                        setcurrent = 250; 
                }
                else if((cModel_Select == 2)&&(ucBLE_CON_DIS==0)&&(ucB_M_SEL==0))   //** APP Interlock Add
                {
                    iDispSetcurrent = iDispSetcurrent/12.2;
                    setcurrent      = iDispSetcurrent;

                    if(setcurrent <= 10)
                        setcurrent = 10;                         
                    if(setcurrent >= 400)
                        setcurrent = 400;                        
                }
                else if((cModel_Select == 2)&&(ucBLE_CON_DIS==0)&&(ucB_M_SEL==1))   //** APP Interlock Add
                {
                    iDispSetcurrent = iDispSetcurrent/12.2;
                    setcurrent      = iDispSetcurrent;

                    if(setcurrent <= 10)
                        setcurrent = 10;                         
                    if(setcurrent >= 200)
                        setcurrent = 200;                        
                }
                else if(cModel_Select == 3)
                {
                    iDispSetcurrent = iDispSetcurrent/8.0;
                    setcurrent      = iDispSetcurrent;

                    if(setcurrent <= 20)
                        setcurrent = 20;                         
                    if(setcurrent >= 600)
                        setcurrent = 600;                        
                }               
                if((iPrevDisplaySetcurrent != setcurrent)&&(ucBLE_CON_DIS==0))  //** App Interlock Add
                {
                    iPrevDisplaySetcurrent = setcurrent;                  
                    cEnDCurrUpdatefg    = 1; 
                    cDispSetcurrentfg   = 1;
                }
                
                ASetcurrentcnt = 0;
                ASetcurrent = 0;
            }
            channel = 32;
            ADPCH = 0x20; 
        }
        else if(channel == 32)
        {
            iPotArcForce = ADC_BUF;
            AArcForce+=iPotArcForce;
            AArcForcecnt++;
            if(AArcForcecnt >= 32)  
            {                            
                AArcForce = AArcForce >> 5;
                iDispArcForce = AArcForce;             
                iDispArcForce = iDispArcForce * 4.88;
                iDispArcForce = iDispArcForce/49;
                
                if((cMaxFBCurrCalibrationfg == 1) && (cVRDCountSettingfg == 0))// && (cMinFBCurrCalibrationfg == 0))
                {
                    fDispArcForce = AArcForce;             
                    fDispArcForce = fDispArcForce / 2.88; 
                    fDispArcForce = fDispArcForce/49;
                    //iOffsetBand = iDispArcForce;        
                        fSLOPE1 = fDispArcForce;       
                        iMAXFBCurrOffset=fSLOPE1*100;
                        fSLOPE1=((float)iMAXFBCurrOffset/100);                                      
                }
                if((cMinFBCurrCalibrationfg == 1))// && (cVRDCountSettingfg == 0) && (cMaxFBCurrCalibrationfg == 0))
                {
                    iOffsetBand1    = iDispArcForce;
                    iMINFBCurrOffset = iOffsetBand1;                                           
                }

                if(iDispArcForce<=0)
                    iDispArcForce=0;
                else if(iDispArcForce>=100)
                    iDispArcForce=100;
                
                if(ucBLE_CON_DIS==0)
                    iArcforce   = iDispArcForce;
                else
                   iArcforce    = iBLEArcForce;
                
                if(iPrevArcforce != iArcforce)
                {
                    iPrevArcforce = iArcforce;
                    cEnDCurrUpdatefg = 1;                  
                }
                
                AArcForcecnt = 0;
                AArcForce = 0;
            }
            channel = 33;
            ADPCH = 0x21; 
        }
        else if(channel == 33)
        {
            iPotHotStart = ADC_BUF;
            AHotStart+=iPotHotStart;
            AHotStartcnt++;
            
            if(AHotStartcnt >= 32)  
            {                            
                AHotStart = AHotStart >> 5;
                iDispHotStart = AHotStart;             
                iDispHotStart = iDispHotStart * 4.88;
                iDispHotStart = iDispHotStart/49;

                if((cVRDCountSettingfg == 1) && (cMaxFBCurrCalibrationfg == 0)) // && (cMinFBCurrCalibrationfg == 0))
                {
                    cDispVRDcountfg = 1;
                    iVRDCount       = iDispHotStart;
                }    
                
                /*if(cDispFBCurrCalifg == 1)
                {
                   iDispFBCurrCaliCount = iDispHotStart*10; 
                }*/
                
                if(iDispHotStart<=0)
                    iDispHotStart=0;
                else if(iDispHotStart>=100)
                    iDispHotStart=100;
                
                if(ucBLE_CON_DIS==0)
                    iHotstart = iDispHotStart;
                else
                    iHotstart = iBLEHotStart;
                
                if(iPrevHotstart != iHotstart)
                {
                    iPrevHotstart = iHotstart;
                    cEnDCurrUpdatefg = 1;                  
                }        
                
                AHotStartcnt = 0;
                AHotStart = 0;
            }
            channel = 0;
            ADPCH = 0x00; 
        }

        PIR1bits.ADIF = 0;                    
    } //ADC END 
    
    if (PIR3bits.RC1IF)
    { 
        PIE3bits.RC1IE = 0;     //Disable interrupts
        Rx1Receive = RCREG1;    //Read RX register
        switch(ucState)         //+EVENT:BLE_CONNECTED
        {
            case 0 :if((Rx1Receive=='?')&&(ucBlutoothInit==0)&&(ucBLE_CON_DIS==4))
                    {
                        ucState=1; ucCount=0;
                    }
                    else if((Rx1Receive=='+')&&(ucBlutoothInit==0))
                    {
                        ucState=2; ucCount=0;
                    }
                    else
                        ucState=0;ucCount=0;
                    break;
            case 1 :if(ucCount<4)
                    {
                      ucSetCur[ucCount]=Rx1Receive;
                      ucCount++;
                      if(ucSetCur[0]=='R')
                      {
                         ucState=0; ucArcOnTimeReset=1;
                      }
                      if(ucCount==4)
                      {
                        if(ucSetCur[0]=='A')  
                        {
                            uiBRSetCurr=((ucSetCur[1]-0x30)*100)+((ucSetCur[2]-0x30)*10)+(ucSetCur[3]-0x30);
                        }
                        if(ucSetCur[0]=='H')
                        {
                          iBLEHotStart=((ucSetCur[1]-0x30)*100)+((ucSetCur[2]-0x30)*10)+(ucSetCur[3]-0x30);
                          //send_string_u1("!H");
                        }
                        if(ucSetCur[0]=='F')  
                        {
                            iBLEArcForce=((ucSetCur[1]-0x30)*100)+((ucSetCur[2]-0x30)*10)+(ucSetCur[3]-0x30);
                            //send_string_u1("!F");
                        }
                        if((cModel_Select == 2)&&(ucB_M_SEL==0))
                        {
                            setcurrent=uiBRSetCurr;
                            
                            if(setcurrent <= 10)
                                setcurrent = 10;                         
                            if(setcurrent >= 400)
                                setcurrent = 400;                        
                        }
                         if((cModel_Select == 2)&&(ucB_M_SEL==1))
                        {
                            setcurrent=uiBRSetCurr;
                            
                            if(setcurrent <= 10)
                                setcurrent = 10;                         
                            if(setcurrent >= 200)
                                setcurrent = 200;                        
                        }
                        
                        if(iPrevDisplaySetcurrent != setcurrent)
                        {
                            iPrevDisplaySetcurrent = setcurrent;                  
                            cEnDCurrUpdatefg    = 1; 
                            cDispSetcurrentfg   = 1;
                            //Display_updatefg    = 1;
                        }
                        ucState=0; //ucRXFlag=1; 
                      }
                    }
                    break;  
            case 2 :if((Rx1Receive=='_')&&(ucBlutoothInit==0))
                        ucState=3; 
                    else
                        ucState=2;
            
                    break;
            case 3 :if((Rx1Receive=='C')&&(ucBlutoothInit==0))
                    {
                      ucState=4; 
                    }
                    else if((Rx1Receive=='D')&&(ucBlutoothInit==0))
                      ucState=5; 
                    else
                        ucState=0;
            
                    break;
            case 4 :if((Rx1Receive=='D')&&(ucBlutoothInit==0))
                    {
                       ucBLE_CON_DIS=1;ucState=0; ucCount=0;
                    }
                   else
                       ucState=4;
                    break;
            case 5 :if((Rx1Receive=='T')&&(ucBlutoothInit==0))
                    {
                        ucBLE_CON_DIS=2;ucState=0; ucCount=0;
                    }
                    else
                        ucState=5;
                    break;
            default:
                     break;
        }
        
        PIR3bits.RC1IF = 0;     //Clear rx flag
        PIE3bits.RC1IE = 1;     //Enable interrupts again
    }
    
    if (PIR3bits.RC2IF)
    { 
        PIE3bits.RC2IE = 0;     //Disable interrupts
        PIR3bits.RC2IF = 0;     //Clear rx flag
        Rx2Receive = RCREG2;    //Read RX register
       
        switch(ucState1) 
        {
            case 0:if(Rx2Receive == '@')
                   {
                       ucState1 = 1; 
                       ucCount1 = 0;
                   }
                   else
                   {
                       ucState1 = 0;
                   }
                     break;
             case 1:if(ucCount1<8)
                    {
                        Temp[ucCount1] =  Rx2Receive;
                        if(ucCount1==7)
                        {
                           ucRx2Flag=1;
                           ucState1 = 0;
                           uiBPer    = (unsigned int)Temp[0];
                        }
                        ucCount1++;
                    }
                    break;

                    default:
                         break;
         }         
        PIE3bits.RC2IE = 1;     //Enable interrupts again
    }
    
}



void oscillator_init()
{
    OSCCON1           = 0X60;
    OSCCON3           = 0X00;
    OSCENbits.HFOEN   = 1;
    OSCENbits.ADOEN   = 1;
    OSCFRQ            = 0x07; //  0x07
    OSCTUNE           = 0x00;  
    OSCSTAT           = 0x00;
    BORCONbits.SBOREN = 0;    
}

void portpin_init()
{ 
    //FOR DISPLAY
    ANSELBbits.ANSELB0 = 0;
    ANSELBbits.ANSELB1 = 0;
    ANSELBbits.ANSELB2 = 0;
    ANSELBbits.ANSELB4 = 0;
    ANSELAbits.ANSELA7 = 0;
    ANSELAbits.ANSELA6 = 0;
    ANSELCbits.ANSELC1 = 0;
    ANSELAbits.ANSELA3 = 0;
  
    SEL1IO = 0; //RB0
    SEL2IO = 0; //RB1
    SEL3IO = 0; //RB2
    SEL4IO = 0; //RB4
    SEL5IO = 1; //RC1
    SEL6IO = 0; //RA6
    SEL7IO = 0; //RC1
    SEL8IO = 0; //RA3
    
    ANSELDbits.ANSELD0 = 0; 
    ANSELDbits.ANSELD1 = 0; 
    ANSELDbits.ANSELD2 = 0; 
    ANSELDbits.ANSELD3 = 0; 
    ANSELDbits.ANSELD4 = 0; 
    ANSELDbits.ANSELD5 = 0; 
    ANSELDbits.ANSELD6 = 0;                 
    ANSELDbits.ANSELD7 = 0;
    
    SEGAIO  = 0; //RD0
    SEGBIO  = 0; //RD1
    SEGCIO  = 0; //RD2
    SEGDIO  = 0; //RD3
    SEGEIO  = 0; //RD4
    SEGFIO  = 0; //RD5
    SEGGIO  = 0; //RD6
    SEGDPIO = 0; //RD7
     
    //FOR LED

    ANSELEbits.ANSELE2 = 0;
    //ANSELCbits.ANSELC5 = 0;
    //ARCFORCE_LEDIO = 0;
    VRD_LEDIO          = 0;
    
    //TRIP_LEDIO         = 0 ;
    
    //FOR SWITCH
    ANSELCbits.ANSELC0 = 0;
    ANSELAbits.ANSELA5 = 0;
    ANSELBbits.ANSELB3 = 0;
    
    MMA_TIG_SWITCHIO    = 1;
    
    VRD_SWITCHIO        = 1;
    Battery_LEDIO       = 0;
    //FOR DAC
    ANSELCbits.ANSELC3 = 0;
    ANSELCbits.ANSELC4 = 0;
    
    //PMD
    PMD3bits.CCP2MD       = 1;
    CCP2CONbits.CCP2EN    = 0x00;
    CCP2CONbits.CCP2MODE0 = 0;
    CCP2CONbits.CCP2MODE1 = 0;
    CCP2CONbits.CCP2MODE2 = 0;
    CCP2CONbits.CCP2MODE3 = 0;    
    PIR6bits.CCP2IF = 0;
    PIE6bits.CCP2IE = 0;
    
    ANSELCbits.ANSELC2 = 0;
    SHDNIO = 0;
    
    //FOR MODEL SELECTION
    ANSELCbits.ANSELC6     = 0;
    ANSELCbits.ANSELC7     = 0;
    
    TXLAT = 1;  
    TXIO = 0;   
    RXIO = 1;   
}

void timer0_init()
{  
    T0CON0bits.T016BIT  = 1;         // 16 bit timer
    
    T0CON0bits.T0OUTPS0 = 0;        // post scaler 1:2
    T0CON0bits.T0OUTPS1 = 0;   //1
    T0CON0bits.T0OUTPS2 = 0;   //1
    T0CON0bits.T0OUTPS3 = 0;   //1
    
    T0CON1bits.T0CS0    = 0;        //clock selection
    T0CON1bits.T0CS1    = 1;
    T0CON1bits.T0CS2    = 0;    
    T0CON1bits.T0ASYNC  = 0;        //synchronous with internal clock
    
    T0CON1bits.T0CKPS0  = 0;        //clock pre-scaler 1:4
    T0CON1bits.T0CKPS1  = 0;
    T0CON1bits.T0CKPS2  = 0;
    T0CON1bits.T0CKPS3  = 0;
    
    T0CON0bits.T0EN     = 1;
    PIE0bits.TMR0IE     = 1;        //Timer 0 interrupt enable
    PIR0bits.TMR0IF     = 0;

    INTCONbits.IPEN     = 0;
    INTCONbits.GIE      = 1;
    INTCONbits.PEIE     = 1;
    TMR0H               = 0xD1;
    TMR0L               = 0x20;  
}

void ADC_init()
{
    TRISAbits.TRISA0   = 1;
    TRISAbits.TRISA1   = 1;
    TRISAbits.TRISA2   = 1;
    TRISBbits.TRISB5   = 1;
    TRISCbits.TRISC5   = 1;
    TRISEbits.TRISE0   = 1; //RE0
	TRISEbits.TRISE1   = 1; //RE1  
    TRISAbits.TRISA4   = 1; //RA4
    
    ANSELAbits.ANSELA0 = 1;
    ANSELAbits.ANSELA1 = 1;
    ANSELAbits.ANSELA2 = 1;
    ANSELBbits.ANSELB5 = 1;
    ANSELCbits.ANSELC5 = 1;
    ANSELEbits.ANSELE0 = 1; 
    ANSELEbits.ANSELE1 = 1; 
    ANSELAbits.ANSELA4 = 1;     
    
    PMD2bits.ADCMD     = 0;
    //PMD2bits.CMP1MD     = 1;
    //PMD2bits.CMP2MD     = 1;
    
    ADPCHbits.ADPCH0    = 0;// 0x0B;                    // channel selection RB3
    ADPCHbits.ADPCH1    = 0;
    ADPCHbits.ADPCH2    = 0;
    ADPCHbits.ADPCH3    = 0;
    ADPCHbits.ADPCH4    = 0;
    ADPCHbits.ADPCH5    = 0;
    
    channel = 0;
    
    ADREFbits.ADPREF0   = 0;                    //VREF+ is connected to VDD
    ADREFbits.ADPREF1   = 0;
    ADREFbits.ADNREF    = 0;                    //VREF- is connected to AVSS    

    ADCON0bits.ADCS     = 0;                    // FRC
    ADCLK               = 0x3F;                 //clk(Hz) = (Fosc/(2*(n+1)))=Fosc/2      
    ADCON0bits.ADFM     = 1;                    //Right justified    
    ADACQ               = 0x00;//0x80;
    
    PIR1bits.ADIF       =0;                            //clear interupt flag
    PIE1bits.ADIE       =1;                            //Enable interrupt.
    INTCONbits.PEIE     =1;
    INTCONbits.GIE      =1;  
    Delay(500,'m'); 
    ADCON0bits.ADON     =1;
    ADCON0bits.ADGO     =1;
}

void system_init()
{
    oscillator_init();
    timer0_init();
    portpin_init();
    ADC_init();
    I2C_init();
}

void I2C_init(void)
{
	SCLIO = 0;										// clock output
	SDAIO = 0;										// data output					 	
}

void Delay100uSec(void)
{
    unsigned int a;
    for (a=0;a<8;a++);
}


void Delay(unsigned int iCnt, unsigned char cUnit)
{
    unsigned int a,b,c;
        
    if(cUnit == 's')
    {
        for (c = 0; c < iCnt; c++)
            for (b = 0; b < 1000; b++)
                for(a = 0; a < 10; a++)
                {
                    Delay100uSec();                  
                } 
    }
    else if(cUnit == 'm')
    {
        for (b = 0;b < iCnt; b++)
            for(a = 0; a < 10; a++)
            {
                Delay100uSec();                  
            } 
    }
   
}



void Bluetooth_Init(void)
{        
    switch(ucInitCMD)
    {
         case 0:if(ucCMDSEND==1)
                {
                    send_string_u1(AT);
                    ucInitCMD=1;ucCMDSEND=0;uiBCnt=0;
                }
                break;
         case 1:if(ucCMDSEND==1)
                {
                    send_string_u1(BLENAME_R);
                    ucInitCMD=2;ucCMDSEND=0;uiBCnt=0;
                }
                break;
         case 2:if(ucCMDSEND==1)
                {
                    send_string_u1(BLENAME_S);
                    ucInitCMD=3;ucCMDSEND=0;uiBCnt=0;
                }
                break;
         case 3:if(ucCMDSEND==1)
                {
                    send_string_u1(BLEMODE_R);
                    ucInitCMD=4;ucCMDSEND=0;uiBCnt=0;
                }
                break;
         case 4:if(ucCMDSEND==1)
                {
                    send_string_u1(BLEMODE_S);
                    ucInitCMD=5;ucCMDSEND=0;uiBCnt=0;
                }
                break;
         case 5:if(ucCMDSEND==1)
                {
                    send_string_u1(TRANSENTER);
                    ucInitCMD=6;ucCMDSEND=0;uiBCnt=0;
                }
                break;
          case 6:if(ucCMDSEND==1)
                {
                    send_string_u1(CMDMODE);
                    ucInitCMD=0;ucBlutoothInit=0;ucCMDSEND=0;uiBCnt=0;
                }
                break;
        default:
                break;
    }
}
void main (void)
{ 
    system_init();
    
    cPowerONfg = 1;
    iPowerONcnt = 10000;
    cModel_Select = 2;
    ModelSelection();
    
    if(123 == Read_EEPROM(0x00FF))
    {  
        //memdatamode = Read_EEPROM(WELDMODE_ADDR);
        //cMode = memdatamode;
       
        cModel_Select = Read_EEPROM(MODEL_SELECTION_ADDR);  // location
        sec = Read_EEPROM(ARCONTIME_SEC_ADDR); 
        min = Read_EEPROM(ARCONTIME_MIN_ADDR);
        hr  = Read_EEPROM(ARCONTIME_HR_ADDR); 
        
        iMAXFBCurrOffset = Read_EEPROM(MAX_CURR_OFFSET);
        
        if(iMAXFBCurrOffset <= 300 ||  iMAXFBCurrOffset >=650)       // 300  650
        {
            Write_EEPROM(556,MAX_CURR_OFFSET);
            iMAXFBCurrOffset = Read_EEPROM(MAX_CURR_OFFSET);
            fSLOPE1 = ((float)iMAXFBCurrOffset/100);
        }
        else
        {
            fSLOPE1 = ((float)iMAXFBCurrOffset/100);
        }
                
        iVRD_Time = iSetVRD_Time = Read_EEPROM(VRD_COUNT_ADDR);
        iMINFBCurrOffset = Read_EEPROM(MIN_CURR_OFFSET);
         //iDispFBCurrCaliCount = Read_EEPROM(DISP_FB_OFFSET);
    }
    else
    {
        Write_EEPROM(cModel_Select,MODEL_SELECTION_ADDR);
        //Write_EEPROM('M',WELDMODE_ADDR);
        //Write_EEPROM(100,SETCURRENT_ADDR);
        //Write_EEPROM(0,ARCON_RESET_ADDR);
        Write_EEPROM(0,ARCONTIME_SEC_ADDR);
        Write_EEPROM(0,ARCONTIME_MIN_ADDR);
        Write_EEPROM(0,ARCONTIME_HR_ADDR);
        Write_EEPROM(565,MAX_CURR_OFFSET);
        iVRD_Time = 2;
        Write_EEPROM(iVRD_Time,VRD_COUNT_ADDR);
     //-----------------------------------------------------------------
        Write_EEPROM(123,0x00FF);
        cModel_Select = Read_EEPROM(MODEL_SELECTION_ADDR);
        //cResetDecide = Read_EEPROM(ARCON_RESET_ADDR);                                                                                                                             
        sec = Read_EEPROM(ARCONTIME_SEC_ADDR); 
        
        if((sec==0XFF)||(sec>60))
        {
           sec=0;
        }

        min = Read_EEPROM(ARCONTIME_MIN_ADDR);
        //iPrevmin = min;
        if((min==0XFF)||(min>60))
        {
           min=0;
        }

        hr  = Read_EEPROM(ARCONTIME_HR_ADDR);
        //iPrevhr = hr;
        if((hr==0XFF)||(hr>99))
        {
           hr=0;
        } 
        iMAXFBCurrOffset = Read_EEPROM(MAX_CURR_OFFSET); 
        
        if(iMAXFBCurrOffset <= 300 ||  iMAXFBCurrOffset >=650)          // 300  650
        {
             Write_EEPROM(556,MAX_CURR_OFFSET);
             // Read
             iMAXFBCurrOffset = Read_EEPROM(MAX_CURR_OFFSET); //*** Read
             fSLOPE1 = ((float)iMAXFBCurrOffset/100);                   //BSJ for slop cal value  
        } 
        else
        {
            fSLOPE1 = ((float)iMAXFBCurrOffset/100);                    //BSJ for slop cal value
        }
        iSetVRD_Time = iVRD_Time = Read_EEPROM(VRD_COUNT_ADDR);
        iMINFBCurrOffset = Read_EEPROM(MIN_CURR_OFFSET);
        //iDispFBCurrCaliCount = Read_EEPROM(DISP_FB_OFFSET);
    }
   
    if(cModelSelectfg == 0) 
    {
        iDispcurr[0]	= '[';
        iDispcurr[1]	= 'A';
        iDispcurr[2]	= 'D';
        iDispcurr[3]	= 'R';
        iDispvolt[0]	= '[';
        iDispvolt[1]	= '[';
        iDispvolt[2]	= '[';
        iDispvolt[3]	= '[';
        Delay(5, 's');   
        Typedp.digitdp3 = 1;
        iDispcurr[0]	= '[';
        iDispcurr[1]	= 'R';
        iDispcurr[2]	= '1';
        iDispcurr[3]	= '0';
        iDispvolt[0]	= '[';
        iDispvolt[1]	= '[';
        iDispvolt[2]	= '[';
        iDispvolt[3]	= '[';
        Delay(5, 's');
        Typedp.digitdp3 = 0;         
       
        if(cModel_Select == 1)
        {
           iDispcurr[0]	= '[';
           iDispcurr[1]	= '2';
           iDispcurr[2]	= '5';
           iDispcurr[3]	= '0';
           iDispvolt[0]	= '[';
           iDispvolt[1]	= '[';
           iDispvolt[2]	= '[';
           iDispvolt[3]	= '[';
           Delay(5, 's');  
           //iDigiRXmaxcurrmin = 10;
           //iDigiRXmaxcurrmax = 250;
        }
        else if(cModel_Select == 2)
        {
           iDispcurr[0]	= '[';
           iDispcurr[1]	= '4';
           iDispcurr[2]	= '0';
           iDispcurr[3]	= '0';
           iDispvolt[0]	= '[';
           iDispvolt[1]	= '[';
           iDispvolt[2]	= '[';
           iDispvolt[3]	= '[';
           Delay(5, 's');  
           //iDigiRXmaxcurrmin = 10;
           //iDigiRXmaxcurrmax = 400;
        }
        else if(cModel_Select == 3)
        {
           iDispcurr[0]	= '[';
           iDispcurr[1]	= '6';
           iDispcurr[2]	= '0';
           iDispcurr[3]	= '0';
           iDispvolt[0]	= '[';
           iDispvolt[1]	= '[';
           iDispvolt[2]	= '[';
           iDispvolt[3]	= '[';
           Delay(5, 's'); 
           //iDigiRXmaxcurrmin = 20;
           //iDigiRXmaxcurrmax = 600;
        }
    }    
    Typedp.digitdp7 = 1;
    
    Modelcalibration(); 
    iPrevSetcurrent = 0;

    if(cModel_Select == 2)
    {
        if(setcurrent <= HOT_START_SETCURR_LIMIT) //&& (cMode=='M'))
        {
            iHotfg = 1;
        }
    }
    if(cModel_Select == 3)
    {       
        if(setcurrent <= HOT_START_SETCURR_CHAMP600_LIMIT) //&& (cMode=='M'))
        {
            iHotfg = 1;
        }
    }
    
    cModeLatchfg = 1;
    if(ivrdcalibrationfg==0 && icalibrationfg==0)
    {
        USART_initialize();ucBlutoothInit=1;
    }
    else
    {
        ucBlutoothInit=0;ucBLE_CON_DIS=0;
    }
    USART2_initialize();
    
  /* while(1)
{
            Battery_LEDLAT=1;
            Delay(1,'s');
            Battery_LEDLAT=0;
            Delay(1,'s');


}*/
  /* while(1)
   
    {
         
        if(ucRXFlag==1)
        {
            TRANS1('A');
            send_string_u1("HI");
            ucRXFlag=0;
        }
        //Delay(10, 's'); 
        iDispcurr[1]	= '1';
        iDispcurr[2]	= '1';
        iDispcurr[3]	= '1';
        iDispvolt[1]	= '0';
        iDispvolt[2]	= '7';
        iDispvolt[3]	= '9';
       
       if(ucRx2Flag==1)
       {
           ucRx2Flag=0;
           TRANS2('C');
       }
       TRANS2('D');
       Delay(5, 's'); 
    }*/
    //   if(ucRx2Flag==1)
//            {
//              //ucRx2Flag=0;
//              TRANS2("$");
//              send_string_u2("OK");
//              for(i=0;i<8;i++)
//                TRANS1(Temp[i]+0x30);
              //TRANS1(Rx2Receive);
    //}
    
    //Bluetooth_Init();
    ucCMDSEND=0;uiBCnt=0;ucBLE_CON_DIS=0;
	while(1)
	{    
        if(ucBlutoothInit)
            Bluetooth_Init();
        
      /*if(ucRXFlag==1)  
        {
          TRANS1('A');
          //for(i=0;i<3;i++)
          //  TRANS1(ucSetCur[i]); 
           ucRXFlag=0;
        }*/
       
        if(ucBLE_CON_DIS==1)
        {
           send_string_u1("APP CONNECTED"); ucBLE_CON_DIS=4;
        }
        else if(ucBLE_CON_DIS==2)
        {
           send_string_u1("APP DISCONNECT");
           ucBLE_CON_DIS=0;
        }
            
        if((ucDataSend==1)&&(ucBLE_CON_DIS==4))
        {   
            
           TRANS1('@');
           send_string_u1("M:");       
           TRANS1(cMode);
           TRANS1(';');
           send_string_u1("SC:"); //SET CURRENT
           TRANSNUM(setcurrent);
           TRANS1(';');
           send_string_u1("AV:"); //ACT Voltage
           TRANSNUM(iActualvolt1);
           TRANS1(';');
           send_string_u1("AC:"); //ACT Current
           TRANSNUM(iActualcurr);
           TRANS1(';');
           send_string_u1("Hr:"); 
           TIME(hr);
           TRANS1(';');
           send_string_u1("Min:"); 
           TIME(min);
           TRANS1(';');
           send_string_u1("Sec:"); 
           TIME(sec);
           TRANS1(';');
           send_string_u1("VR:");
           TRANS1(cVRD_fg + '0');
           TRANS1(';');
           send_string_u1("MB:"); 
           TRANS1(ucB_M_SEL + '0');
           TRANS1('#');
           ucDataSend=0;

           if(ucRx2Flag==1)
           {
              ucRx2Flag=0;
              TRANS1('$');
              //send_string_u1("OK");
              uiBPer    = (unsigned int)Temp[0];
              uiBTemp   = (unsigned int)Temp[3];
              uiBatV    = ((uiBPer*0.012)+3)*200;
              send_string_u1("BV:"); //Battery Voltage
              TRANSNUM2(uiBatV);
              TRANS1(';');
              send_string_u1("BP:"); //Battery Percentage
              TRANSNUM2(uiBPer);
              TRANS1(';');
              send_string_u1("BT:"); //Battery Temperature
              TRANSNUM2(uiBTemp);
              TRANS1('&');
              //for(i=0;i<8;i++)
              // TRANS1(Temp[i]);
           } 
        }
        
        if((cPrevmode != cMode) && (cModelSelectfg == 0))// && (cVRDCountSettingfg == 0))
        {
            if(cMode == 'M')
            {
                Typedp.digitdp7 = 0;
                Typedp.digitdp6 = 0; 
                iDispcurr[0]	= '[';
                iDispcurr[1]	= 'M';
                iDispcurr[2]	= 'M';   
                iDispcurr[3]	= 'A';
                iDispvolt[0]	= '[';
                iDispvolt[1]	= '[';
                iDispvolt[2]	= '['; 
                iDispvolt[3]	= '['; 
                Delay(5, 's');  
                Typedp.digitdp7 = 1;                 
            }
            else if(cMode == 'T')
            {
                Typedp.digitdp7 = 0;
                Typedp.digitdp6 = 0; 
                iDispcurr[0]	= '[';
                iDispcurr[1]	= 'T';
                iDispcurr[2]	= 'I';   
                iDispcurr[3]	= 'G';
                iDispvolt[0]	= '[';
                iDispvolt[1]	= '[';
                iDispvolt[2]	= '['; 
                iDispvolt[3]	= '['; 
                Delay(5, 's');
                Typedp.digitdp7 = 1;                 
            }
            cPrevmode = cMode;  
            Display_updatefg = 1;
        }
                     
        if((cRemoteEnDCurrUpdatefg == 1)||(cEnDCurrUpdatefg == 1))
        //if( ((cRemoteEnDCurrUpdatefg == 1)||(cEnDCurrUpdatefg == 1))&& (iHotstart >= 2) )
        {            
            if(iHotfg == 1) 
            {
                if(cModel_Select == 2)
                {
                    if(setcurrent <= HOT_START_SETCURR_LIMIT) 
                    {                   
                        iHotstartCurrent = setcurrent+((setcurrent*iHotstart)/100);
                        if(iHotstartCurrent >=270)
                        {
                            iHotstartCurrent = 270;
                        }
                        daccount=MMACCLookup(iHotstartCurrent);
                    }
                    else
                    {
                        daccount = MMACCLookup(setcurrent);
                    }
                }
                if(cModel_Select == 3)
                {
                    if((setcurrent <= HOT_START_SETCURR_LIMIT) || ((setcurrent >= HOT_START_SETCURR_CHAMP600_LIMIT_1) && (setcurrent <= HOT_START_SETCURR_CHAMP600_LIMIT))) 
                    {                   
                        iHotstartCurrent = setcurrent+((setcurrent*iHotstart)/100);
                        if(iHotstartCurrent >=530)
                        {
                            iHotstartCurrent = 530;
                        }
                        daccount=MMACCLookup(iHotstartCurrent);
                    }
                    else
                    {
                        daccount = MMACCLookup(setcurrent);
                    }                                       
                }
            }
            else if((iHotfg == 0) && (antistickfg == 0)) 
            {
                daccount = MMACCLookup(setcurrent);
            }
            dacoutfg = 1;            
            cEnDCurrUpdatefg = 0;
            cRemoteEnDCurrUpdatefg = 0;
        }
               
        if(dacoutfg==1)
        {
            I2C_Write(daccount);
            dacoutfg=0;
        }   
                
        if(memoryfg == 1)
        {
            memoryfg = 0;
        } 

        if(c10Msecfg == 1)
        {            
            if((iActualvolt <= ANTISTICK_VTG_LIMIT) && (weldonfg == 1) && (cMode=='M')) 
            {
                cnt200ms++;            
                if(cnt200ms >= 300)
                {
                    daccount    = MMACCLookup(10);           // 5
                    dacoutfg    = 1;                
                    antistickfg = 1;
                    cnt200ms    = 0;  
                }
            }
            else
            {                
                cnt200ms = 0; 
            }
            if((iActualvolt > ANTISTICK_VTG_LIMIT) && (antistickfg == 1))
            {
                cnt1sec++;
                if(cnt1sec >= ANTISTICK_LEAVE_TIME)
                {
                    cEnDCurrUpdatefg = 1;  
                    antistickfg      = 0;                
                    cnt1sec          = 0;
                }
            }
            
            if((iHotfg == 1) && (weldonfg == 1)) 
            {
                hotstartcount++;
                if(hotstartcount >= HOT_START_TIME)	  
                {
                    cEnDCurrUpdatefg = 1;  
                    hotstartcount = 0;
                    iHotfg = 0;
                }	
            } 

            if((iActualcurr >= WELDON_START_CURR) && (weldonfg == 0) && ivrdcalibrationfg==0) 
            {    
                Display_updatefg = 1;
                weldonfg = 1; 
                ivrdcnt = 0;
                cVRD_fg = 0;
            }
            else if((iActualcurr < WELDON_START_CURR) && (weldonfg == 1))
            {
                weldoncnt++;
                if(weldoncnt >= 1) 
                {   
                    if((weldonfg == 1)&&(memoryfg == 0))
                    {
                        memoryfg = 1;
                    }                    
                    weldoncnt = 0;
                    weldonfg  = 0;
                    cEnDCurrUpdatefg = 1;
                    Display_updatefg = 1;

                    if(cModel_Select == 2)
                    {                        
                        if((setcurrent <= HOT_START_SETCURR_LIMIT) && (cMode=='M'))
                        {
                            iHotfg    = 1;                   
                        }
                    }
                    if(cModel_Select == 3)
                    {                        
                        if((setcurrent <= HOT_START_SETCURR_CHAMP600_LIMIT) && (cMode=='M'))
                        {
                            iHotfg    = 1;                   
                        }                        
                    }
                    hotstartcount = 0;
                    cArcForceOnfg = 0;
                    iArcForceTimeCnt = 0;  
                    cMeasureARCOnTimefg = 1;
                }
            }
                      
            Read_RockerSwitch();
            if(cMode == 'M')
            {
                Read_VRD_Switch();
            }       
        if (SEL5 ==1)
        {
           ucB_M_SEL=1;
           
             if(TH_ERR_fg == 1)
                {
                    if((cFlashCntr == 0) && (cFlashfg == 1))
                    {
                        Typedp.digitdp7 = 0;
                        iDispcurr[0]='[';
                        iDispcurr[1]='E';
                        iDispcurr[2]='R';
                        iDispcurr[3]='R';
                        iDispvolt[0]='[';
                        iDispvolt[1]='[';
                        iDispvolt[2]='[';
                        iDispvolt[3]='[';	

                        Display_updatefg = 1;
                        cFlashfg = 0;
                        cFlashCntr = 1000;
                    }
                    else if((cFlashCntr == 0) && (cFlashfg == 0))
                    {
                        //Typedp.digitdp7 = 0;
                        iDispcurr[0]='[';
                        iDispcurr[1]='0';
                        iDispcurr[2]='0';
                        iDispcurr[3]='3';
                        iDispvolt[0]='[';
                        iDispvolt[1]='[';
                        iDispvolt[2]='[';
                        iDispvolt[3]='[';

                        Display_updatefg = 1;
                        cFlashfg = 1;                 
                        cFlashCntr = 1000;	
                    }	   
                }
        }
                    
        else 
        {
            ucB_M_SEL=0;
           if(((UV_ERR_fg == 1) || (OV_ERR_fg == 1) || (TH_ERR_fg == 1) || (NO_CN9_CONNECTOR_ERR_fg == 1)) && (cModelSelectfg == 0) && ((cDispVRDcountfg == 0) || (cVRDCountSettingfg == 0))) 
            {
                Typedp.digitdp7 = 0;
                if(UV_ERR_fg == 1)
                {
                    if((cFlashCntr == 0) && (cFlashfg == 1))
                    {
                        Typedp.digitdp7 = 0;
                        iDispcurr[0]='[';
                        iDispcurr[1]='E';
                        iDispcurr[2]='R';
                        iDispcurr[3]='R';
                        iDispvolt[0]='[';
                        iDispvolt[1]='[';
                        iDispvolt[2]='[';
                        iDispvolt[3]='[';	

                        Display_updatefg = 1;
                        cFlashfg = 0;
                        cFlashCntr = 1000;
                    }
                    else if((cFlashCntr == 0) && (cFlashfg == 0))
                    {
                        //Typedp.digitdp7 = 0;
                        iDispcurr[0]='[';
                        iDispcurr[1]='0';
                        iDispcurr[2]='0';
                        iDispcurr[3]='1';
                        iDispvolt[0]='[';
                        iDispvolt[1]='[';
                        iDispvolt[2]='[';
                        iDispvolt[3]='[';

                        Display_updatefg = 1;
                        cFlashfg = 1;                 
                        cFlashCntr = 1000;	
                    }	   
                }
                if(OV_ERR_fg == 1)
                {
                    if((cFlashCntr == 0) && (cFlashfg == 1))
                    {
                        Typedp.digitdp7 = 0;
                        iDispcurr[0]='[';
                        iDispcurr[1]='E';
                        iDispcurr[2]='R';
                        iDispcurr[3]='R';
                        iDispvolt[0]='[';
                        iDispvolt[1]='[';
                        iDispvolt[2]='[';
                        iDispvolt[3]='[';	

                        Display_updatefg = 1;
                        cFlashfg = 0;
                        cFlashCntr = 1000;
                    }
                    else if((cFlashCntr == 0) && (cFlashfg == 0))
                    {
                        //Typedp.digitdp7 = 0;
                        iDispcurr[0]='[';
                        iDispcurr[1]='0';
                        iDispcurr[2]='0';
                        iDispcurr[3]='2';
                        iDispvolt[0]='[';
                        iDispvolt[1]='[';
                        iDispvolt[2]='[';
                        iDispvolt[3]='[';

                        Display_updatefg = 1;
                        cFlashfg = 1;                 
                        cFlashCntr = 1000;	
                    }	   
                }
                if(TH_ERR_fg == 1)
                {
                    if((cFlashCntr == 0) && (cFlashfg == 1))
                    {
                        Typedp.digitdp7 = 0;
                        iDispcurr[0]='[';
                        iDispcurr[1]='E';
                        iDispcurr[2]='R';
                        iDispcurr[3]='R';
                        iDispvolt[0]='[';
                        iDispvolt[1]='[';
                        iDispvolt[2]='[';
                        iDispvolt[3]='[';	

                        Display_updatefg = 1;
                        cFlashfg = 0;
                        cFlashCntr = 1000;
                    }
                    else if((cFlashCntr == 0) && (cFlashfg == 0))
                    {
                        //Typedp.digitdp7 = 0;
                        iDispcurr[0]='[';
                        iDispcurr[1]='0';
                        iDispcurr[2]='0';
                        iDispcurr[3]='3';
                        iDispvolt[0]='[';
                        iDispvolt[1]='[';
                        iDispvolt[2]='[';
                        iDispvolt[3]='[';

                        Display_updatefg = 1;
                        cFlashfg = 1;                 
                        cFlashCntr = 1000;	
                    }	   
                }
                if(NO_CN9_CONNECTOR_ERR_fg == 1)
                {
                    if((cFlashCntr == 0) && (cFlashfg == 1))
                    {
                        Typedp.digitdp7 = 0;
                        iDispcurr[0]='[';
                        iDispcurr[1]='E';
                        iDispcurr[2]='R';
                        iDispcurr[3]='R';
                        iDispvolt[0]='[';
                        iDispvolt[1]='[';
                        iDispvolt[2]='[';
                        iDispvolt[3]='[';	

                        Display_updatefg = 1;
                        cFlashfg = 0;
                        cFlashCntr = 1000;
                    }
                    else if((cFlashCntr == 0) && (cFlashfg == 0))
                    {
                        //Typedp.digitdp7 = 0;
                        iDispcurr[0]='[';
                        iDispcurr[1]='0';
                        iDispcurr[2]='1';
                        iDispcurr[3]='1';
                        iDispvolt[0]='[';
                        iDispvolt[1]='[';
                        iDispvolt[2]='[';
                        iDispvolt[3]='[';

                        Display_updatefg = 1;
                        cFlashfg = 1;                 
                        cFlashCntr = 1000;	
                    }	   
                }
                
                Error_flag = 1; 
                err_dispfg=1;
                SHDNLAT = 1; 
                daccount = 0;
                dacoutfg = 1;  
            }
            else
            {
                Error_flag = 0;  
                if(err_dispfg == 1)
                {
                    err_dispfg = 0;
                    SHDNLAT = 0; 
                    if(cModel_Select == 2)
                    {                        
                        if((setcurrent <= HOT_START_SETCURR_LIMIT) && (cMode=='M'))
                        {
                            iHotfg    = 1;                   
                        }
                    }                   
                    if(cModel_Select == 3)
                    {
                        if((setcurrent <= HOT_START_SETCURR_CHAMP600_LIMIT) && (cMode=='M'))
                        {
                            iHotfg    = 1;                   
                        }                        
                    }
                    cEnDCurrUpdatefg = 1;
                   
                    Display_updatefg = 1;
                }
            }
            c10Msecfg = 0;
        }
    }
       if(ucB_M_SEL==0)
        {
         Battery_LEDLAT=0;
        }
        else if((ucB_M_SEL==1)&&(uiBPer<=20))
        {
            Battery_LEDLAT=1;
            Delay(1,'s');
            Battery_LEDLAT=0;
            Delay(1,'s');
        }
        else 
        {
           Battery_LEDLAT = 1;
        } 
        if(cMeasureARCOnTimefg == 1)
        {
            if(iPrevsec != sec)
            {
                Write_EEPROM(sec,ARCONTIME_SEC_ADDR);
                iPrevsec = sec;
            }
            if(iPrevmin != min)
            {
            
                Write_EEPROM(min,ARCONTIME_MIN_ADDR);        
                iPrevmin = min;
            }
            if(iPrevhr != hr)
            {
                Write_EEPROM(hr,ARCONTIME_HR_ADDR);
                iPrevhr = hr;
            } 
            cMeasureARCOnTimefg = 0;            
        }
        
        if(cResetDecide)
        {
            Write_EEPROM(0,ARCONTIME_SEC_ADDR);
            Write_EEPROM(0,ARCONTIME_MIN_ADDR);        
            Write_EEPROM(0,ARCONTIME_HR_ADDR);
            hr=0;
            min=0;
            sec=0;
        }   

       /* if(ArcOnMenuMode==1) 
        {
            Typedp.digitdp7 = 0;
            Typedp.digitdp6 = 1; 
            iDispcurr[0]	= 'H';
            iDispcurr[1]	= 'H';
            iDispcurr[2]	= 'M';
            iDispcurr[3]	= 'M'; 

            hex_to_dec_time(min,hr);

            Display_updatefg = 1;  
            
        }*/
        if(ArcOnMenuMode==2)
        {

            Typedp.digitdp7 = 0;
            Typedp.digitdp6 = 0;

            iDispcurr[0]	= 'R';
            iDispcurr[1]	= 'S';
            iDispcurr[2]	= 'E';
            iDispcurr[3]	= 'T';
            iDispvolt[0]	= 'D';
            iDispvolt[1]	= 'O';
            iDispvolt[2]	= 'N';  
            iDispvolt[3]	= 'E';

            cResetDecide = 1;            
            Display_updatefg = cResetdonefg = 1;  
            
        }            
        if((dispvtgupdatefg == 1) && (iArcforce != 0) && (cMode=='M'))
        {
            if(cModel_Select == 2)
            {
                if((iActualvolt > ANTISTICK_VTG_LIMIT) && (iActualvolt <= ARCFORCE_VTG_LIMIT))
                {                                         
                    iArcforceCurrent = (int)setcurrent + ((((300.0 - iActualvolt)/300.0)*(125*iArcforce))/100); 
                 
                    if(iArcforceCurrent >=300.0)
                    {
                        iArcforceCurrent = 300.0;
                    }

                    if(setcurrent <= ARCFORCE_SETCURR_LIMIT_2)
                    {
                        daccount = MMACCLookup(iArcforceCurrent);
                        dacoutfg = 1; 
                    }
                    iArcForceTimeCnt = 0;
                }
                else if((iActualvolt > ARCFORCE_VTG_LIMIT)&&(iHotfg == 0))
                {
                    iArcForceTimeCnt++;            
                    if(iArcForceTimeCnt >= 3)
                    {         
                        iArcForceTimeCnt = 0; 
                        cEnDCurrUpdatefg = 1;   
                    }            
                }
                dispvtgupdatefg = 0;
            }
            if(cModel_Select == 3)
            {
                if(setcurrent <= ARCFORCE_SETCURR_LIMIT_2)
                {
                    if((iActualvolt > ANTISTICK_VTG_LIMIT) && (iActualvolt <= ARCFORCE_VTG_LIMIT) )
                    {                                         
                        iArcforceCurrent = (int)setcurrent + ((((300.0 - iActualvolt)/300.0)*(125*iArcforce))/100); 
                        if(iArcforceCurrent >= 300.0)
                        {
                            iArcforceCurrent = 300.0;
                        }

                        if(setcurrent <= ARCFORCE_SETCURR_LIMIT_2)
                        {
                            daccount = MMACCLookup(iArcforceCurrent);
                            dacoutfg = 1; 
                        }
                        iArcForceTimeCnt = 0;
                    }
                    else if((iActualvolt > ARCFORCE_VTG_LIMIT) && (iHotfg == 0))
                    {
                        iArcForceTimeCnt++;            
                        if(iArcForceTimeCnt >= 3)
                        {         
                            iArcForceTimeCnt = 0; 
                            cEnDCurrUpdatefg = 1;   
                        }            
                    }
                    dispvtgupdatefg = 0;  
                }
                else if((setcurrent >= ARCFORCE_SETCURR_CHAMP600_LIMIT_1) && (setcurrent <= ARCFORCE_SETCURR_CHAMP600_LIMIT_2))
                {
                    if((iActualvolt > ANTISTICK_VTG_LIMIT) && (iActualvolt <= ARCFORCE_VTG_CHAMP600_LIMIT))
                    {                                         
                        iArcforceCurrent = (int)setcurrent + ((((350.0 - iActualvolt)/350.0)*(125*iArcforce))/100); 
                        
                        if((setcurrent >= ARCFORCE_SETCURR_CHAMP600_LIMIT_1) && (setcurrent <= ARCFORCE_SETCURR_CHAMP600_LIMIT_2))
                        {
                            daccount = MMACCLookup(iArcforceCurrent);
                            dacoutfg = 1; 
                        }
                        iArcForceTimeCnt = 0;
                    }
                    else if((iActualvolt > ARCFORCE_VTG_CHAMP600_LIMIT) && (iHotfg == 0))
                    {
                        iArcForceTimeCnt++;            
                        if(iArcForceTimeCnt >= 3)
                        {         
                            iArcForceTimeCnt = 0; 
                            cEnDCurrUpdatefg = 1;   
                        }            
                    }
                    dispvtgupdatefg = 0;                                       
                }               
            }
        }
        
   
        if(((cMode=='M') || (cMode=='T')) && (weldonfg == 0) && (Error_flag == 0) && (cModelSelectfg == 0) && (cVRDCountSettingfg == 0) && (cDispVRDcountfg == 0))
        {
            Typedp.digitdp7 = 1;
            Typedp.digitdp6 = 0; 
            if((psetcurrent!= setcurrent) || (Display_updatefg == 1))                
            //if((dispDisplaycurrupdatefg == 1) || (dispRemotecurrupdatefg == 1) || (Display_updatefg == 1))
            //if((cDispSetcurrentfg == 1) || (Display_updatefg == 1))
            {
                
                hex_to_dec_curr(setcurrent);//iMAXFBCurrOffset);//setcurrent);//iSetVRD_Time);//setcurrent);
                //hex_to_dec_curr(iHotstart);
                //psetcurrent = setcurrent;
                
            }
            if((dispvtgfg == 1) || (Display_updatefg == 1))                   
            {
                hex_to_dec_volt(iActualvolt1);//fSLOPE1*10);//iActualvolt1);                    
                //prevweldvoltage = iActualvolt;
                //hex_to_dec_volt(iArcforce);
                //hex_to_dec_volt(iDispSetcurrent);
                //hex_to_dec_volt(iOffsetDiv);
            }  
            dispvtgfg = 0; 
            cDispSetcurrentfg = 0;
            //dispDisplaycurrupdatefg = 0;
            //dispRemotecurrupdatefg = 0;
            Display_updatefg = 0;
        }
        else if((weldonfg == 1) && (Error_flag == 0) && (cModelSelectfg == 0) && (cDispVRDcountfg == 0) && (cVRDCountSettingfg == 0) && (ivrdcalibrationfg==0)) // && ((cMode=='M') || (cMode=='T')))
        {
            //Typedp.digitdp7 = 1;  
            Typedp.digitdp6 = 0;  
            if(((dispcurrfg == 1)) || (Display_updatefg == 1))         
            {
                hex_to_dec_curr(iActualcurr);//iMAXFBCurrOffset);
            }
            //if(1)//((dispvtgfg == 1)) || (Display_updatefg == 1))       
            if((dispvtgfg == 1) || (Display_updatefg == 1))     
            {
                hex_to_dec_volt(iActualvolt1);//fSLOPE1*10);
            }
            dispcurrfg = 0;
            dispvtgfg = 0;
            Display_updatefg = 0;         
        }
        
           
          CheckPinShort();
        
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*if(cMode=='T')
        {
              if(((setcurrent >= 398) && (cModel_Select == 2)) || ((setcurrent >= 598) && (cModel_Select == 3)))					 
            //{    
                if(weldonfg == 0)
                {
                    //CheckPinShort();
                    cCaliDetectfg = 1;
                    if((cMaxFBCurrCalibrationfg == 1) && (cVRDCountSettingfg == 0))// && (cMinFBCurrCalibrationfg == 0))
                    {          
                        daccount = MMACCLookup(setcurrent);  
                        dacoutfg = 1; 
                    }
                    if(cMaxFBCurrCalibrationfg == 0) 
                    {   
                        iMAXFBCurrOffset = fSLOPE1*100; // BSJ
                        Write_EEPROM(iMAXFBCurrOffset,MAX_CURR_OFFSET); //BSJ
                    } 
                    if(((dispcurrfg == 1)) || (Display_updatefg == 1))         
                    {
                        hex_to_dec_curr(fSLOPE1*100);
                    }    
                    if((dispvtgfg == 1) || (Display_updatefg == 1))     
                    {
                        hex_to_dec_volt(iActualvolt1);
                    }

                    dispcurrfg = 0;
                    dispvtgfg = 0;
                    Display_updatefg = 0;   
                }
        
        }*/
        //////////////////////////////////////////////////////////////////////////////////////////////////
        
        if(cMode=='M')
        {     
                         
            if(weldonfg == 1 && icalibrationfg==1)
            {
               cCaliDetectfg = 1;
                if((cMaxFBCurrCalibrationfg == 1) && (cVRDCountSettingfg == 0))
                {          
                    daccount = MMACCLookup(setcurrent);  
                    dacoutfg = 1; 

                }
                if(cMaxFBCurrCalibrationfg == 0)
                {
                   iMAXFBCurrOffset = fSLOPE1*100; // BSJ
                   Write_EEPROM(iMAXFBCurrOffset,MAX_CURR_OFFSET); //BSJ
                   //fSLOPE1=(float)(iMAXFBCurrOffset/100);
                   icalibrationfg=0;
                }
                if(((dispcurrfg == 1)) || (Display_updatefg == 1))         
                {
                    hex_to_dec_curr(iActualcurr);
                }    
                if((dispvtgfg == 1) || (Display_updatefg == 1))     
                {
                    hex_to_dec_volt(iActualvolt1);
                }

                dispcurrfg = 0;
                dispvtgfg = 0;
                Display_updatefg = 0;   
            }

            if((weldonfg == 0) && (Error_flag == 0) && (ivrdcalibrationfg == 1) && (icalibrationfg==0))// && (cVRDcntDispf==1))//(cVRDCountSettingfg == 1))
            {
                
                if((cVRDCountSettingfg == 1) && (cMaxFBCurrCalibrationfg == 0))
                {         
                    if((cDispVRDcountfg == 1) || (Display_updatefg == 1))     
                    {
                        Typedp.digitdp7 = 0;
                        Typedp.digitdp6 = 0;
                        hex_to_dec_curr(iVRDCount);
                    }                    
                    
                     iSetVRD_Time = iVRDCount*10;
                     if(iSetVRD_Time == 0)
                     {
                         iSetVRD_Time = 2;
                     }
                     
                    cVRDCntSavefg = 1;
                    cDispVRDcountfg = 0;
                    Display_updatefg = 0;
                    Typedp.digitdp7 = 1; 
                    
                     //if((cVRDCntSavefg == 1))// && (cVRDCountSettingfg == 0))
                    {
                        Write_EEPROM(iSetVRD_Time,VRD_COUNT_ADDR);  
                        iVRD_Time = iSetVRD_Time;
                        cVRDCntSavefg = 0;
                    } 
                } 
            }
        }
    }
}

void Read_RockerSwitch(void)
{
    if(MMA_TIG_SWITCH == 0)
    {
        iModeSwitchcnt++;            
        if(iModeSwitchcnt >= 1)
        {
            if(MMA_TIG_SWITCH == 0)
            {
                cMode =  'M';
                //MMA_TIG_LEDLAT = 1;
                if(cModeLatchfg == 0)
                {
                    cModeLatchfg = 1;
                    cEnDCurrUpdatefg = 1;
                    //iVRD_Time = iSetVRD_Time;//180;    //VRD_TIME_MAX;
                    //iHotstart = Read_EEPROM(HOTSTART_ADDR); 
                    //iArcforce = Read_EEPROM(ARCFORCE_ADDR);
                    iVRD_Time = iSetVRD_Time = Read_EEPROM(VRD_COUNT_ADDR); 
                    if(cModel_Select == 2)
                    {                      
                        if(setcurrent <= HOT_START_SETCURR_LIMIT) 
                        {
                            iHotfg = 1;
                        }
                    }
                    if(cModel_Select == 3)
                    {                       
                        if(setcurrent <= HOT_START_SETCURR_CHAMP600_LIMIT) 
                        {
                            iHotfg = 1;
                        }                        
                    }
                }
            }
            iModeSwitchcnt = 0;
        }                
    }
    else if(MMA_TIG_SWITCH == 1)
    {
        iModeSwitchcnt++;            
        if(iModeSwitchcnt >= 1)
        {
            if(MMA_TIG_SWITCH == 1)
            {
                cMode =  'T';
                //MMA_TIG_LEDLAT = 0;
                if(cModeLatchfg == 1)
                {
                    iHotfg = 0;
                    iHotstart = 0;
                    iArcforce = 0; 
                    ivrdcnt = 0;
                    cVRD_fg = 0;                                       
                    iVRD_Time = 0;
                    cEnDCurrUpdatefg = 1;
                    cModeLatchfg = 0;
                }                                
            }
            iModeSwitchcnt = 0;
        }            
    }    
}

void Read_VRD_Switch(void)
{
        
        if(VRD_SWITCH == 1)
        {
            if(ivrdcalibrationfg == 1)
            {
               cVRD_fg=1; 
               iVRD_Time = 0;
            }
            else   
            {
                iVRDSwitchcnt++;            
                if(iVRDSwitchcnt >= 1)
                {
                    if(VRD_SWITCH == 1)
                    {
                        //iVRD_Time = iSetVRD_Time;//180;    //VRD_TIME_MAX;
                        iVRD_Time = iSetVRD_Time = Read_EEPROM(VRD_COUNT_ADDR); 
                    }
                    iVRDSwitchcnt = 0;
                }
            
            }
        }
    
    else if(VRD_SWITCH == 0) //&& (cMode != 'T'))
    {
        iVRDSwitchcnt++;            
        if(iVRDSwitchcnt >= 1)
        {
            if(VRD_SWITCH == 0)
            {
                iVRD_Time = 0;  //VRD_TIME_MIN;                             
            }
            iVRDSwitchcnt = 0;
        }            
    }    
}



unsigned int MMACCLookup(unsigned int iCurrent)
{
    if(cModel_Select == 1)
    {
       iDacref = (iCurrent*fSLOPE1) + MMACCOFFSET250;
    }
	if(cModel_Select == 2)
    {         
        iDacref = (iCurrent*fSLOPE1) + MMACCOFFSET400; //BSJ
	}
    if(cModel_Select == 3)
    {      
      
        iDacref = (iCurrent*fSLOPE1) + MMACCOFFSET600;
    }
    return(iDacref);
}		

void Write_EEPROM(unsigned int data,unsigned int adrs)
{
    unsigned int iTempH,iTempl;
    iTempl = data;
    iTempH = data >> 8;   
    Write_byte(iTempl,adrs);  
    Write_byte(iTempH,adrs+1);
}

unsigned int Read_EEPROM(unsigned int adrs)
{
    unsigned int iTempH,iTempl,iTemp;
    iTempl = Read_byte(adrs);
    iTempH = Read_byte(adrs+1);
    iTemp = (iTempH<<8)|(iTempl);
    return (iTemp);
}

void Write_byte(unsigned int data,unsigned int adrs)
{
    unsigned int adrh,adrl;
    
    adrl = adrs;
    adrl = (adrl & 0xFF);
    adrh = (adrs >> 8);
    adrh = (adrh & 0x00FF);
        
    NVMCON1bits.NVMREG0 = 0;
    NVMCON1bits.NVMREG1 = 0;                    //Data EEPROM Memory locations write access
    
    NVMADRH = adrh;//0x00;
    NVMADRL = adrl;//0x00;

    NVMDAT = data;//200;//0xA0;

    NVMCON1bits.WREN = 1;    
    
    INTCONbits.GIE = 0; 
    
    NVMCON2 = 0x55;
    
    NVMCON2 = 0xAA;
    
    NVMCON1bits.WR = 1;
    INTCONbits.GIE = 1;  

    //Delay(2 , 's');
    Delay(10 , 'm');
    while(NVMCON1bits.WR == 1){}
    PIR7bits.NVMIF = 0; 
    NVMCON1bits.WREN = 0;   
    
}

unsigned char Read_byte(unsigned int adrs)
{
    unsigned int adrl,adrh,temp;
    unsigned char cHigh_Byte;
     
    adrh = adrs;
    adrl = (adrh & 0x00FF);
    adrh = (adrs >> 8);
    adrh = (adrh & 0x00FF);
    
    NVMCON1bits.NVMREG0 = 0;
    NVMCON1bits.NVMREG1 = 0;
    
    NVMADRH = adrh;//0x00;
    NVMADRL = adrl;//0x00;
    
    NVMCON1bits.RD = 1;
    
    while(NVMCON1bits.RD == 1){}
    
    temp = NVMDAT;  
    
    return temp;   
}

void Trip_detect(unsigned int trip_vtg)
{
    trip_vtg = iActualtripvolt;

    if((trip_vtg > UV_1) && (trip_vtg < UV_2))      //UV
	{
        er1++;
        er3=0;
        er4=0;

		if(er1>ER_DEBOUNCE_TIME)
		{
            UV_ERR_fg=1;
            TH_ERR_fg=0;
            NO_CN9_CONNECTOR_ERR_fg=0;
            cErrorFlashfg = 1;
            er1=ER_DEBOUNCE_TIME;
		}
	}
	else if((trip_vtg > TH_1) && (trip_vtg < TH_2))       //TH
	{
        er1=0;
        er3++;
        er4=0;
		if(er3>ER_DEBOUNCE_TIME)
		{		
            UV_ERR_fg=0;
            TH_ERR_fg=1;
            NO_CN9_CONNECTOR_ERR_fg=0;
            cErrorFlashfg = 1;
            er3=ER_DEBOUNCE_TIME;
		}
	}
    else if(trip_vtg < NO_CN9_CONNECTOR_2)
    {
        if(count_3s>=50)    //500
        {
            count_3s=0;
            
            er4++;
            er3=0;
            er1=0;        
            if(er4>ER_DEBOUNCE_TIME)
            {
                UV_ERR_fg=0;
                TH_ERR_fg=0;
                NO_CN9_CONNECTOR_ERR_fg =0;//1;

               cErrorFlashfg = 1;
               er4=ER_DEBOUNCE_TIME;
            }
        }
        
    }
	else
	{
        UV_ERR_fg=0;
        TH_ERR_fg=0;
        NO_CN9_CONNECTOR_ERR_fg=0;
        
        er1=0;
        er3=0;
        er4=0;

	}	   
}

void Trip_detect_OV(unsigned int trip_vtge)
{
    trip_vtge = iActualtripvolt1;

    if((trip_vtge > OV_1) && (trip_vtge < OV_2))       //OV
	{	
        er2++;
		if(er2>ER_DEBOUNCE_TIME)
		{	
            OV_ERR_fg=1;
            NO_CN9_CONNECTOR_ERR_fg=0;
            
            cErrorFlashfg = 1;
            er2=ER_DEBOUNCE_TIME;
		}	
	}
	else
	{
        OV_ERR_fg=0;
        
        er2=0;
	}	   
}

void CheckPinShort(void)
{
    unsigned int x,y;
    TXLAT = 1;    
    for (x = 0; x < 30; x++)
        for(y = 0; y < 50; y++);
            if(RX == 1)
            {
                TXLAT = 0; 
                //VRD_LEDLAT=1;
                for (x = 0; x < 30; x++)
                    for(y = 0; y < 50; y++);
                        if(RX == 0)
                        {
                            TXLAT = 1;
                            //VRD_LEDLAT=0;
                            for (x = 0; x < 30; x++)
                                for(y = 0; y < 50; y++); 
                                    if(RX == 1)
                                    {
                                        
                                        /*cModelSelectfg = 1;  
                                        if( cCaliDetectfg == 1)//cCaliDispFBCurrfg == 1)
                                        {
                                            cMaxFBCurrCalibrationfg = 1;
                                            cMinFBCurrCalibrationfg = 1;
                                            cVRDCountSettingfg = 0;
                                            cVRDcntDispf=0; 
                                            cDispFBCurrCalifg =1;
                                        } */ //model selection code...
                                    
                                        if(cCaliDetectfg == 1)
                                        {
                                            cMaxFBCurrCalibrationfg = 1;
                                            cMinFBCurrCalibrationfg = 1;
                                            cVRDCountSettingfg = 0;
                                            cVRDcntDispf=0;
                                            cDispFBCurrCalifg=0;
                                        }                                       
                                        if((weldonfg == 0) && (cPowerONfg == 0))
                                        {
                                           
                                            cVRDCountSettingfg = 1;
                                            cVRDcntDispf=1;
                                            cMaxFBCurrCalibrationfg = 0;
                                            cMinFBCurrCalibrationfg = 0;
                                            cDispFBCurrCalifg=0;
                                        }
                                    }
                                    else
                                    {
                                        cModelSelectfg = 0; 
                                        cMaxFBCurrCalibrationfg = 0;
                                        cMinFBCurrCalibrationfg = 0;
                                        cVRDCountSettingfg = 0;
                                        cVRDcntDispf=0;
                                        cDispVRDcountfg=0;
                                        cDispFBCurrCalifg=0;
                                       // icalibrationfg=0;
                                        ivrdcalibrationfg=0;
                                        ivrdledfg=0;
                                        
                                    }
                        }
                        else
                        {
                            cModelSelectfg = 0; 
                            cMaxFBCurrCalibrationfg = 0;
                            cMinFBCurrCalibrationfg = 0;
                            cVRDCountSettingfg = 0;
                            cDispVRDcountfg=0;
                            cDispFBCurrCalifg=0;
                            //icalibrationfg=0;
                            ivrdcalibrationfg=0;
                            ivrdledfg=0;
                        }
            }    
            else
            {
               cModelSelectfg = 0; 
               cMaxFBCurrCalibrationfg = 0;
               cMinFBCurrCalibrationfg = 0;
               cVRDCountSettingfg = 0;
               cDispVRDcountfg=0;
               cDispFBCurrCalifg=0;
              // icalibrationfg=0;
               ivrdcalibrationfg=0;
               ivrdledfg=0;
            }

}
///////////////////////////////////////Mode Selection////////////////////////////////////////////////////
void ModelSelection(void)
{
    
    cModel_Select = 2;            
    Display_updatefg = cModeSelectDonefg = 1;    
    if(cModeSelectDonefg == 1)
    {
      Write_EEPROM(cModel_Select,MODEL_SELECTION_ADDR); 
      cModeSelectDonefg = 0;
    }
    
    /*CheckPinShort();
        Typedp.digitdp7 = 0;
        Typedp.digitdp6 = 0;*/
           
        /*if((iModelSelectBand > 0) && (iModelSelectBand <= 1664))
        {   
            iDispcurr[0]	= '[';
            iDispcurr[1]	= '2';
            iDispcurr[2]	= '5';
            iDispcurr[3]	= '0';
            iDispvolt[0]	= '[';
            iDispvolt[1]	= '[';
            iDispvolt[2]	= '[';
            iDispvolt[3]	= '[';

            cModel_Select = 1;
            Display_updatefg = cModeSelectDonefg = 1;  
        }
        else if((iModelSelectBand >= 1665) && (iModelSelectBand <= 3329))
        {
            iDispcurr[0]	= '[';
            iDispcurr[1]	= '4';
            iDispcurr[2]	= '0';
            iDispcurr[3]	= '0';
            iDispvolt[0]	= '[';
            iDispvolt[1]	= '[';
            iDispvolt[2]	= '[';
            iDispvolt[3]	= '[';

            cModel_Select = 2;            
            Display_updatefg = cModeSelectDonefg = 1;      
        }              
        else if((iModelSelectBand >= 3330) && (iModelSelectBand <= 4992))
        {   
            iDispcurr[0]	= '[';
            iDispcurr[1]	= '6';
            iDispcurr[2]	= '0';
            iDispcurr[3]	= '0';
            iDispvolt[0]	= '[';
            iDispvolt[1]	= '[';
            iDispvolt[2]	= '[';
            iDispvolt[3]	= '[';

            cModel_Select = 3;
            Display_updatefg = cModeSelectDonefg = 1;      
        } */
    
    //CheckPinShort();
}
void Modelcalibration(void)
{
   unsigned int x,y;
    TXLAT = 1;    
    for (x = 0; x < 300; x++)
        for(y = 0; y < 500; y++);
            if(RX == 1)
            {
                TXLAT = 0; 
                for (x = 0; x < 1000; x++)
                    for(y = 0; y < 1000; y++);
                        if(RX == 0)
                        {
                            TXLAT = 1;
                            for (x = 0; x < 300; x++)
                                for(y = 0; y < 500; y++); 
                                    if(RX == 1)
                                    {
                                        if(VRD_SWITCH == 1 )
                                        {
                                            ivrdcalibrationfg=1;
                                            icalibrationfg=0;cMaxFBCurrCalibrationfg = 0;cCaliDetectfg = 0;
                                        }
                                        else
                                        {
                                            ivrdcalibrationfg=0;
                                            icalibrationfg=1;cMaxFBCurrCalibrationfg = 1;cCaliDetectfg = 1;
                                        }                                         
                                    }
                        }
            }
           if(RX==0)
           {
               icalibrationfg=0;
               ivrdcalibrationfg=0;
               RX=0;
           }
    
    
     /*Typedp.digitdp7 = 0;
     Typedp.digitdp6 = 0;
    CheckPinShort();
    
    while(cModelSelectfg)
    {
        cCaliDetectfg=1;
        if(cMode=='M')
        {  
            if(weldonfg==0)
            {    
            Typedp.digitdp7 = 1;
            Typedp.digitdp6 = 0; 
             hex_to_dec_curr(setcurrent);

            if((dispvtgfg == 1) || (Display_updatefg == 1))                   
            {
                hex_to_dec_volt(iActualvolt1);//fSLOPE1*10);//iActualvolt1);                    

            }  
            dispvtgfg = 0; 
            cDispSetcurrentfg = 0;
            Display_updatefg = 0; 
            }
              
        if(((setcurrent >= 398) && (cModel_Select == 2)) || ((setcurrent >= 598) && (cModel_Select == 3)))					 
        //{    
            if(weldonfg == 1)
            {
                //CheckPinShort();
                cCaliDetectfg = 1;
                if((cMaxFBCurrCalibrationfg == 1) && (cVRDCountSettingfg == 0))// && (cMinFBCurrCalibrationfg == 0))
                {          
                    daccount = MMACCLookup(setcurrent);  
                    dacoutfg = 1; 
                }
                if(cMaxFBCurrCalibrationfg == 0) 
                {   
                    iMAXFBCurrOffset = fSLOPE1*100; // BSJ
                    Write_EEPROM(iMAXFBCurrOffset,MAX_CURR_OFFSET); //BSJ
                } 
                hex_to_dec_curr(iActualcurr);
                hex_to_dec_volt(iActualvolt1);
                
                /*if(((dispcurrfg == 1)) || (Display_updatefg == 1))         
                {
                    //fSLOPE1*100);//iActualcurr);//iActualcurr);
                }    
                if((dispvtgfg == 1) || (Display_updatefg == 1))     
                {
                    //fSLOPE1*10);
                }
      * 
                dispcurrfg = 0;
                dispvtgfg = 0;
                Display_updatefg = 0;   
            }
        }
    } */ 
}

void USART_initialize(void)
{
    //Configuration TX and RX pins
    PMD4bits.MSSP1MD    = 1; 
    PMD4bits.MSSP2MD    = 1;
    PMD4bits.CWG1MD     = 1;
    PMD4bits.UART1MD    = 0;
    
    RC7PPS              = 0x16;       //17
    RC6PPS              = 0x09;       //09
    
    ANSELCbits.ANSELC6 = 0;
    ANSELCbits.ANSELC7 = 0;
    TRISCbits.TRISC6   = 0;     // TX
    TRISCbits.TRISC7   = 1;     // RX

    //TXSTA: Transmit Status and Control Register
    TXSTA1bits.SYNC    = 0;    //Asynchronous mode
    TXSTA1bits.TX9     = 0;    //8bit transmission
    TXSTA1bits.TXEN    = 1;    //Enable transmitter
    TXSTA1bits.BRGH    = 0;    //**Set LOW Baud rate
    
    //RCSTA: Receive Status and Control Register
    RCSTA1bits.SPEN    = 1;    //Serial Port enabled
    RCSTA1bits.RX9     = 0;    //8bit reception
    RCSTA1bits.CREN    = 1;    //Enables Receiver
  
    //BAUDCON Control register
    BAUD1CONbits.BRG16 = 0;   //8bit baud rate generator   
    SP1BRGL            = 77; //BAUD RATE: 9600=  103  48MH = 77 (9600)
    SP1BRGH            = 0;
    PIE3bits.RC1IE     = 1;    // ENABLE USART receive interrupt
    PIE3bits.TX1IE     = 0;    // DISABLE USART TX interrupt
    
    // USART interrupts configuration
    INTCONbits.GIE     = 1;    // ENABLE interrupts
    INTCONbits.PEIE    = 1;    // ENABLE peripheral interrupts.    
}

void USART2_initialize(void)
{
    //Configuration TX and RX pins
    PMD4bits.MSSP1MD    = 1; 
    PMD4bits.MSSP2MD    = 1;
    PMD4bits.CWG1MD     = 1;
    PMD4bits.UART2MD    = 0;
    
    RB7PPS  =   0x0E;       //17
    RB6PPS  =   0x0B;       //09

    ANSELBbits.ANSELB6  = 0;
    ANSELBbits.ANSELB7  = 0;
    TRISBbits.TRISB6    = 0;     // TX
    TRISBbits.TRISB7    = 1;     // RX

    //TXSTA: Transmit Status and Control Register
    TXSTA2bits.SYNC     = 0;    //Asynchronous mode
    TXSTA2bits.TX9      = 0;    //8bit transmission
    TXSTA2bits.TXEN     = 1;    //Enable transmitter
    TXSTA2bits.BRGH     = 0;    //**Set LOW Baud rate
    
    //RCSTA: Receive Status and Control Register
    RCSTA2bits.SPEN    = 1;    //Serial Port enabled
    RCSTA2bits.RX9     = 0;    //8bit reception
    RCSTA2bits.CREN    = 1;    //Enables Receiver
  
    //BAUDCON Control register
    BAUD2CONbits.BRG16 = 0;   //8bit baud rate generator   
    SP2BRGL            = 77; //BAUD RATE: 9600=  103  48MH = 77 (9600)
    SP2BRGH            = 0;
    PIE3bits.RC2IE     = 1;    // ENABLE USART receive interrupt
    PIE3bits.TX2IE     = 0;    // DISABLE USART TX interrupt
    
    // USART interrupts configuration
    //INTCONbits.GIE     = 1;    // ENABLE interrupts
    //INTCONbits.PEIE    = 1;    // ENABLE peripheral interrupts.    
}

void TRANS1(unsigned char data)
{
	//while(PIE3bits.TX1IE==1);	
    while(0 == PIR3bits.TX1IF)
    {
        ;
    }
	TX1REG=data;
}
void send_string_u1(char *s)
{
	while(*s)
	{
	   TRANS1(*s++);
	}
} 

void TRANS2(unsigned char data) 
{
	//while(PIE3bits.TX1IE==1);	
    while(0 == PIR3bits.TX2IF)
    {
        ;
    }
	TX2REG=data;
}
void send_string_u2(char *s)
{
	while(*s)
	{
	   TRANS2(*s++);
	}
} 

void TRANSNUM(unsigned int iTemp)
{

    SendBuff[2] = 0x30 + (iTemp % 10);
    iTemp = iTemp / 10;
    SendBuff[1] = 0x30 + (iTemp % 10);
    iTemp = iTemp / 10;
    SendBuff[0] = 0x30 + iTemp % 10;
    
    for(i=0;i<3;i++)
    {
        TRANS1(SendBuff[i]);
    }
}
void TRANSNUM2(unsigned int iTemp2)     //
{
	//SendBuff2[3] =  (iTemp2 % 10)+'0';
    //iTemp2 = iTemp2 / 10;
    SendBuff2[2] = (iTemp2 % 10)+'0';
    iTemp2 = iTemp2 / 10;
    SendBuff2[1] = (iTemp2 % 10)+'0';
    iTemp2 = iTemp2 / 10;
    SendBuff2[0] = (iTemp2 % 10)+'0';

    for(i=0;i<3;i++)
    {
        TRANS1(SendBuff2[i]);
    }
}
void TIME(unsigned int iTemp2)     //
{
   TimeBuf[1] = (iTemp2 % 10)+'0';
   iTemp2 = iTemp2 / 10;
   TimeBuf[0] = (iTemp2 % 10)+'0';
   
    for(i=0;i<2;i++)
    {
        TRANS1(TimeBuf[i]);
    }
}


