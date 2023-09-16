#include "p30f4013.h"
#include "stdio.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "define.c"
#include "DELAY.C"
#include "function.c"
#include "DISPLAY.c"
//#include "STRUCTURE.c"
#include "variable.c"
#include "Isr.c"
#include"ENCODER.C"
#include"MOTORCONTROL.C"

//14 to 15 Sec - for Power On- for Dissconnect Torch 
// 4 to 5 Sec - Torch Dissconnect

_FOSC(CSW_FSCM_OFF & FRC_PLL16);	//30mhz clock  clock switching and failsafe monitor disabled,
_FWDT(WDT_OFF);
//_FBORPOR(PBOR_OFF & MCLR_DIS)
_FBORPOR(PBOR_OFF & MCLR_EN & PWRT_64 ); //MCLR_DIS  MCLR_EN PWRT_OFF

int main(void)
{
	systemInit();
	dispdigit=1;
	//Update_PWM(current);
    for(delay==0;delay<5000;delay++);
    Delayms(1000);
    GAS_RLYLAT=0; //GAS_RLY=0;
//------------------------------------
	//****TRISMTRFB = 0;  Need to Check
    cPowerOnErrSkipfg = 1;
    iPowerOnErrSkipCnt = 2000;
//------------------------------------
    diswin1[0]='A';		//0x0B;//'A';
    diswin1[1]='D';		//0x0E;//'D';
    diswin1[2]='R';		//0x1C;//'R';
    diswin1[3]='R';		//'R';
    diswin1[4]='2';		//-0x30;  //rev 2 @sbm
    diswin1[5]='2';		//-0x30;// changed on 2.1
    Typedp.digitdp5=1;
    
    Delayms(5000);
    DECODENLAT=0;
   	Typedp.digitdp5		=0;
    TypeU.LEDGROUP[0]   =0x00;
    TypeU.LEDGROUP[1]   =0x00;
    Type.wirespeed      =1;
    Type.vtg            =1;
    Type.twot           =1;
    TypeDP.DPGROUP[0]   =0x00;
    
    Typedp.digitdp2		=1;
    Typedp.digitdp5		=1;
    
    psstatusu.psstatusbyte[0]=0x00;
    
    setcurrent			=0;
    setvoltage			=0;
    disp_hex_window1(setcurrent);
    disp_hex_window2(setvoltage);
    Delayms(5000);
    ucTorchComFail=0;uiComunCount=0;TORCH_SELLAT=0;
 
	while(1)
	{
	
		/*if(prevsetvoltage!=setvoltage)
		{
			Typedp.digitdp5	 =1;
			prevsetvoltage=setvoltage;
			disp_hex_window2(setvoltage);
		}
		if(prevsetcurrent!=setcurrent)		
		{
			prevsetcurrent=setcurrent;
			disp_hex_window1(setcurrent);
		}*/
		
		while(ucDipsInd)
		{
			diswin1[0]='/';	diswin1[1]='/';diswin1[2]='/';diswin1[3]='/';	diswin1[4]='/';diswin1[5]='/';
			Delayms(5000);ucDipsInd=0;cEditfg = 1;setvoltage=0;setwirespeed=0;setcurrent=0;
		}	
		/***************************communication section start******************************************/
        if(send_statusf==1 && onesecf==0)
        {
           send_statusf=0;
           send_status();
           
           uiCountDT++;
		   if(uiCountDT>=15)
		   {
			  uiCountDT=0;  
			  Transmitt_string();
		    } 
        }
        
        if(onesecf==1 && transmitonf==1)
        {
            onesecf=0;
            transmittops();
            //Transmitt_string();
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
			
			//transmitonf = 0;
		
        }
       
  /***************************communication section end*****************************************/				
		if(universal_error==0)
		{
	        if(adaptivepidf==1)
	        {
	            adaptivepidf=0;
	            //Adaptive_base_pid();
	        }			
				/**************************Encoder read start here*************************************************/
		    if(read_enc1f==1)
		    {    
		        read_enc1f=0;
		        if(enccount==0)
		        {
		            encod1=SCANENCODER1();
		            mili1_100++;	
		               
		            if((encod1=='+')||(ucWireSpeedInc==1))
		            {
			            ucWireSpeedInc=0;
		                setwirespeed=setwirespeed+pluspara1;
		                if(setwirespeed >= 240)
		                	setwirespeed=240;
		                cEditfg = 1;
		            }
		           else if((encod1=='-')||(ucWireSpeedDec==1))
		            {
			            ucWireSpeedDec=0;
		                if(setwirespeed >= minuspara1)
		                	setwirespeed=setwirespeed-minuspara1;
		                else if(setwirespeed >= 10)
		                	setwirespeed=setwirespeed--;
		                if(setwirespeed <= 10)
		                	setwirespeed=10;
		                cEditfg = 1;
		            }
		            
		            if(mili1_100<100)				//200
		            {
		                if(encod1=='+')
		                    pluscount1++;
		                else if(encod1=='-')
		                    minuscount1++;
		            }
		            else if(mili1_100>=100)			//200
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
		              //iTest = setvoltage;
		                encod2 = '$';
		
		            }
		            //else 
		            if(Type.arclength==1)
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
		            if(mili2_100<100)		//200
		            {
		                if(encod2=='+')
		                    pluscount2++;
		                else if(encod2=='-')
		                    minuscount2++;
		            }
		            else if(mili2_100>=100) 	//200
		            {
		                mili2_100=0;
		                pluspara2	=pluscount2;
		                minuspara2	=minuscount2;
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
	            if((prevsetwirespeed!=setwirespeed) || (prevsetcurrent!=setcurrent) || dispupdatef==1 )
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
	                    Typedp.digitdp1	 	 =0;
	                    Typedp.digitdp2	 	 =1;
	                    Typedp.digitdp3	 	 =0;
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
	//              disp_hex_window1(iTest);
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
		                    diswin1[3]='/'; //0x25;        //display Blank
		                else
		                    diswin1[3]=']'; //0x26;        //display dash-- 
	                }
	                else
	                    diswin1[3]='/'; //0x25;        	//display Blank
	
	                //disp_hex_window2(transoff.arclegth);//disparclength);//transoff.arclegth);
	                count_1ms=0;
	                onesecf=1;
	                txonf=1;
	               	prevsetvoltage=0; //dummy right to update display
	              	parclength=pstowfstr.arclength;
	            }
	            
	            //if(inchkeyon==0)
	            if(psstatus.gasoncommand!=1)
	              GAS_RLYLAT=0;	//  GAS_RLY         =0;
	            if((psstatus.motoroncommand!=1) || ((TORCH == 'X') && (wfstatus.twotfourtmode1 == 0)) )
	                Update_PWM(setwirespeed*0);  
	            
	            speeedrate				=0;
	            openloopcnt 			=0;
	            softstartf  			=0;
	            dispupdatef 			=0;
	            closeloopf				=0;
	            cyclestrtf				=0;
	
	            psstatus.creepspeedon	=1;
	            //transoff.creepspeedon	=1;
	            //GAS_RLYLAT=0;		//GAS_RLY     =0;
	        }
	/******************************When weld is on********************************************************/
	        else if(psstatus.weldoncyclestrt==1)//(TORCH=='P')
	        {
	            //speeedrate=20;
	            uiComunCount=0;
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
	                    //Update_PWM(newsetwirespeed*MTR_VTG_CONSTANT);
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
	                GAS_RLYLAT=1;		//GAS_RLY         =1;
	            }
	            else
	            {
	                GAS_RLYLAT=0;		//GAS_RLY         =0;
	            }
	            if(psstatus.motoroncommand==1)
	            {
	               if(psstatus.creepspeedon==1)
	               {
	                    cyclestrtf=0;
	                 //   newsetwirespeed=(setwirespeed>>1);
	                 // 	creep_speed=100;  //updated 
	                    newsetwirespeed=setwirespeed*creep_speed*0.01;
	
	                    if(newsetwirespeed<=10)
	                      	newsetwirespeed=10;//setwirespeed;                // 30  changed on 12042021
	
	                      //    else if(newsetwirespeed>=60)
	                     //       newsetwirespeed=60;
	                   /* Update_PWM(speeedrate*4); ///50% pwm 400 count			
	                    
	                    if(speeedrate < newsetwirespeed)
	                    {
	                         speeedrate=speeedrate+4;
	                         for(delinch1=0;delinch1<3;delinch1++)
	                         for(delinch=0;delinch<30000;delinch++);
	                    }*/
	                    /*if(setwirespeed<30)
	                    	Update_PWM(newsetwirespeed*13.5);
	                    else*/
	                   	 	Update_PWM(newsetwirespeed*MTR_VTG_CONSTANT);
	                    
	                     //TRISMOTOR_TRIP11=0;
	//                     MTRFB=1;
	                    
	              }   
	              else if(psstatus.creepspeedon==0)
	               {
	                   cyclestrtf=1;
	                   if(cMtrOverLdfg == 0)
	                   {
	                    	newsetwirespeed=setwirespeed;
	                   }
	                   else
	                   {
	                    	newsetwirespeed=0;
	                   }
	                   if(closeloopf==0)
	                   {
		                  /*if(setwirespeed<30)
	                    	Update_PWM(newsetwirespeed*13.5);
	                      else*/
	                       	Update_PWM(newsetwirespeed*MTR_VTG_CONSTANT);  
	                       
	                       //Update_PWM(setwirespeed*2.8);//MTR_VTG_CONSTANT);
	                       
	                        if(wfspeedchangef==1)
	                        {
	//                          integral_old=newsetwirespeed*scalefactor2*MTR_VTG_CONSTANT;//2.6;
	                            integral_old=newsetwirespeed*scalefactor2*2.6;
	                            wfspeedchangef	=0;
	                            integral_new 	=0;
	                            //integral_old=0;
	                            error_old 		=0;
	                            error_new		=0;
	                            controller_out	=0;
	                            prevFltpfreq	=0;
	                            Fltpfreq		=0;
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
	                	Lo_setppwm=(newsetwirespeed)*MTR_FREQ_CONSTANT;// changed on 10122020.*/
	            }
	            else if((psstatus.motoroncommand!=1) || ((TORCH == 'X') && (wfstatus.twotfourtmode1 == 0)) )//(psstatus.motoroncommand!=1)
	            {
	                Update_PWM(setwirespeed*0); 
	                openloopcnt =0;
	                closeloopf  =0;
	                closeloop1f =0;
	                cyclestrtf=0;
	                speeedrate=0;
	            }
	            
                Type.wirespeed=0;
                Type.amp=1;
                Type.thickness=0;
                Type.arclength   =0;
                Type.vtg         =1;
                Type.sec         =0;

                TypeDP.DPGROUP[0]=0x00;
                Typedp.digitdp5	 =1;
                disp_hex_window1(Actual_amp);//newsetwirespeed);//Actual_amp);
                disp_hex_window2(Actual_vtg);//speeedrate);//Actual_vtg);
                dispupdatef     =1;
	            //GAS_RLYLAT=1;		//GAS_RLY         =1;
	       }
		}
		
		if(universal_error_latch==1)
      	{
          	dispupdatef=1;
          	universal_error_latch=0;
      	}
       	if(((weldmode=='P') || (weldmode=='G')))
       		detect_display_error();	
	}	
}


void IOinit(void)
{
	SEGAIO=0;SEGBIO=0;SEGCIO=0;SEGDIO=0;SEGEIO=0;SEGFIO=0;SEGGIO=0;SEGDPIO=0;DECODAIO=0;DECODBIO=0;DECODCIO=0;DECODENIO=0;
	GAS_RLYIO=0;GAS_RLYLAT=0;
	TORCH_SELIO	=0;TRISTORCHIN=1;TRISMOTOR_TRIP11=1;
	ENCODER_INIT();
	TORCH_SELLAT=0;
}

void systemInit(void)
{
	OSCTUNbits.TUN0=0;
	OSCTUNbits.TUN1=0;
	OSCTUNbits.TUN2=0;
	OSCTUNbits.TUN3=0;
    Delay_ms(10); 				//@ for unnecessary spike of motor pwm 
    ADPCFG=0XFFFF;				//FOR CONFIGURING AS DIGITAL IO
	IOinit();  					//@ for unnecessary spike of motor pwm 
	//INTCON1bits.NSTDIS=0;
	//INTCON2bits.ALTIVT=0;
	timer1_init();
	uart2_init();
	uart_init();
	init_pwm();
    PWM_INIT_DT();
    capture_init();
}

void key_application(unsigned char keypress)
{
    if(keypress==key_gason)//'A')
    {
        while(key==key_gason)
        {
           Type.gason      	 =1;
           GAS_RLYLAT		 =1;	//GAS_RLY         =1;
           //status.gasoncommand    =1;
           diswin1[0]= 'G'; //0x11
           diswin1[1]= 'A'; //0x0B;
           diswin1[2]= 'S'; //0x1D;
           diswin1[3]= 'O';	//0x19
           diswin1[4]= 'N';	//0x18;
           diswin1[5]= '/';	//0x25;// all off
           cGasRlyClrfg = 1;
           iGasDbCnt = 5000;
           uiComunCount=0;
        }
        if(iGasDbCnt == 0)
        {
        	Type.gason      =0;
        	GAS_RLYLAT		=0;	//GAS_RLY         =0;
        	dispupdatef     =1;
        }
    }
    else if(keypress==key_inch)//'B')
    {
        inchcnt=10;
        while(key==key_inch)
        { 
           Type.inch      	 =1;
           //status.inchon   =1;
           //inchkeyon    =1;
           diswin1[0]   ='I';	//0x13;//'I';
           diswin1[1]   ='N';	//0x18;//'N';
           diswin1[2]   ='C';	//0x0D;//'C';
           
	       Update_PWM(inchcnt*24); ///50% pwm 400 count 
           disp_hex_window2(inchcnt);
           
           if(inchcnt<100)
           {
                inchcnt=inchcnt+10;
                for(delinch1=0;delinch1<7;delinch1++)
                for(delinch=0;delinch<50000;delinch++);
           }
           uiComunCount=0;
         }
         
	     Update_PWM(inchcnt*0);		
         Type.inch       =0;
         //status.inchon =0;
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
            //TypeU.LEDGROUP[0]	=0x00;
            //TypeU.LEDGROUP[1]	=0x00;
            Type.wirespeed		=0;
            Type.amp			=0;
            Type.thickness		=1;
            TypeDP.DPGROUP[0]	=0x00;
            Typedp.digitdp2	 	=1;
            Typedp.digitdp5	 	=1;
            //Send_Byte('a');
        }
        else if(Type.thickness==1)
        {
            //TypeU.LEDGROUP[0]	=0x00;
            //TypeU.LEDGROUP[1]	=0x00;
            Type.wirespeed		=1;
            Type.amp			=0;
            Type.thickness		=0;
            TypeDP.DPGROUP[0]	=0x00;
            Typedp.digitdp2	 	=1;
            Typedp.digitdp5	 	=1;
            //Send_Byte('t');
        }

        dispupdatef     =1;
    }   
    else if(keypress==key_no) //'X')
    {
        Type.gason       =0;
        Type.inch        =0;
        //GAS_RLYLAT	 =0;			//GAS_RLY        =0;
        //status.gason   =0;
        //status.inchon  =0;
        inchkeyon        =0;
    }  
}

void detect_display_error(void)
{
	//add complete array to comm array and sent to power source
	 pstowfstr.error_code1=erroru.errorstatusbyte[0];
	 pstowfstr.error_code2=erroru.errorstatusbyte[1];
    
    if(errorstatus.uv_er1==1)
    {
        universal_error=1;
        diswin1[5]='1'; //1
    }
    else if(errorstatus.ov_er2==1)
    {
        universal_error=1;
        diswin1[5]='2'; //2
    }
    else if(errorstatus.th_er3==1)
    {
        universal_error=1;
        diswin1[5]='3'; //3
    }
    else if(errorstatus.no_curr_er4==1)
    {
        universal_error=1;
        diswin1[5]='4'; //4
    }
    else if(errorstatus.motor_over_ld_er5==1)
    {
        universal_error=1;
        diswin1[5]='5'; //4
    }
    else if(errorstatus.wirefdr_er6==1)
    {
        universal_error=1;
        diswin1[5]='6'; //4
    }
    else if(errorstatus.water_press_er7==1 && ( (weldmode=='P') || (weldmode=='G') )  )
    {
        universal_error=1;
        diswin1[5]='7'; //4
    }
    else if(error8==1)
    {
       universal_error=1;
       diswin1[5]='8'; //8
    }
    else if(errorstatus.motor_fb_err==1)
    {
       universal_error=1;
       diswin1[4]='1'; //8
       diswin1[5]='0'; //8
    }
    else
        universal_error=0;

    if(universal_error==1)
    {
	    universal_error_latch=1;
	    
	    diswin1[0]='E';	//0x0F; //E
	    diswin1[1]='R';	//0x1C; //R
	    diswin1[2]='R';	//0x1C; //R
	    diswin1[3]='0'; //0
	    diswin1[4]='0'; //0
	    
	    GAS_RLYLAT=0;	//GAS_RLY         =0;
	    Update_PWM(0);   
	    TypeDP.DPGROUP[0]	=0;
	    errorstatus.comm_er8=1;
    }
}

void Transmitt_string()
{
    unsigned char low=0,high=0;
    unsigned char trancheksum=0;
    
    low		=  setcurrent;			//pstowfstr.Lo_setcurrent	(setcurrent&0x00ff)
    high	= (setcurrent>>8);		//pstowfstr.Hi_setcurrent 	(setcurrent&0xff00)>>8
                    
    trancheksum = low+high+'#';
    
    Send_Byte2('?');             //?- One Board and $ -Other Board
    Send_Byte2(high); 	         //0
    Send_Byte2(low);             //1
    Send_Byte2('#');             //2
    Send_Byte2(trancheksum);     //3
    
    if((setcurrent>0)&&(ucTorchComFail==0))
    	ucSTCheckCom=1;
}

