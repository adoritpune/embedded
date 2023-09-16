/* 
 * File:   function.h
 * Author: MV01
 *
 * Created on March 19, 2016, 11:35 AM
 */

#include "STRUCTURE.c"

#define DEBOUNCE	4
#define key_gason   1
#define key_inch    2
#define key_mode    3
#define key_disp    4
#define key_no      0


unsigned char temp1=0,temp2=0,temp3=0,temp4=0,ucState=0,ucSTCheckCom=0, ucTorchCheckStart=0,ucDipsInd=0;
volatile unsigned char dVal0=0,dVal1=0,dVal2=0,dVal3=0,dVal4=0,dVal5=0,dVal6=0,dVal7=0;
unsigned char encod1=0,encod2=0,TORCH='X',pcount=0,prevTORCH=0xFF,torchonf=0;
unsigned char minuspara1=0,pluspara1=0,pluscount1=0,minuscount1=0,mili1_100=0,tans=0,adaptivepidf=0;
unsigned char minuspara2=0,pluspara2=0,pluscount2=0,minuscount2=0,mili2_100=0,torchstatus1=0,torchstatus2=0,wfspeedchangef=1;
unsigned char cEditfg,cWf2t4tmodefg,cTestfg,cGasRlyClrfg;
unsigned int setvoltage=0,setcurrent=0,prevsetcurrent=0,prevsetvoltage=0,setwirespeed=0,prevsetwirespeed=0x00,newsetwirespeed=0;
volatile unsigned char weldmode=0,comm_error_count=0,error4=0,universal_error=0,error8,universal_error_latch=0;
volatile unsigned char wfstatusbyte=0,displayonf=1,portbstatus=0x00,pportb=0x00,prevkey='Z',key='X',crater_speed=0;
unsigned int uiCountDT=0;

unsigned char diswin1[8];
unsigned char arr[8];
unsigned char dispdigit=1,updatedispf=0;

volatile unsigned int received_data=0;
volatile unsigned char string_recvd = 0,uartdata=0,reccnt=0,startptr=0,checksum=0,lowbyte=0,hibyte=0;

unsigned char temp=0,i=0,plus111=0,minus111=0,firstpulse1=0,secondpulse1=0,plus222=0,minus222=0,firstpulse2=0,secondpulse2=0;
//unsigned int  new1=0,old1=0,new2=0,old2=0;
unsigned int  new1=0,old1=0,new2=0,old2=0,setpfreq=0,Hi_setppwm=0,Lo_setppwm=0,rel_wirespeed=0;
volatile unsigned char OneH=0x00,OneL=0x00,TwoH=0x00,TwoL=0x00,Count=0,onesecf=0,softstartf=0,rxdata=0,
                       txonf=0,count_2ms=0,read_enc1f=0,enccount=0,dispupdatef=1,fixintervalf=0,capintervalf=0,count_pid=0;
unsigned int speedcontrolfc=0,delinch=0,delinch1=0,creepspeed=0,openloopcnt=0,disp1term=0,disp2term=0,disp3term=0,disp4term=0,gapfreq=0;

unsigned char startptr1=0,arrptr=0,recchksum=0,rec_arr[22],transmitonf=0,chksum=0,inchkeyon=0,inchcnt,send_statusf=0;
unsigned char closeloopf=0,cyclestrtf=0, Tx_ptr=0,count_1msec=0,kpressread=0;
volatile unsigned int  Two=0,One,Total_Count=0,count_1ms=0,pperiod=0,avgpperiod=0,pfreq=0;
unsigned char cPowerOnErrSkipfg,cTorchPressfg;
unsigned int iPowerOnErrSkipCnt;

unsigned int iii=0,ijk=0,lmn=0,Actual_amp=0xFFFF,Actual_vtg=0xFFFF,recpsstatus=0,recstatus=0,statusptr1=0;
volatile unsigned char error_code1,error_code2,creep_speed=0;
unsigned char cRelSpeedSign;
unsigned int parclength=0xFFFF,disparclength=0x0000;
unsigned int delay=0,prevFltpfreq=0,Fltpfreq=0,mahesh_test=50,speeedrate=10;
double integral_new =0, integral_old=0,error_old =0,error_new=0,minoutmax=0,controller_out=0;
unsigned int scalefactor2=71.0,minfmspeed=50,scaled_baseval2=0,maxfmspeed=750;
unsigned char togglepin=1,closeloop1f=0;
unsigned char cMtrOverLdDbfg,cMtrOverLdfg;
unsigned int cMtrOverLdDbCnt;

unsigned char uc1Rxfalg=0;
                       
unsigned int iTest,iGasDbCnt = 0;                       
unsigned char cMtrOverLdDbfg,cMtrOverLdfg;
unsigned char ucTorchChk=1,ucWireSpeedInc=0,ucWireSpeedDec=0;
unsigned long Total_Period=0;
float Tsampling =1.0;
unsigned int uiComunCount=0;
unsigned char ucTorchComFail=0;

unsigned char recdata[5];
void uart2_init();
void uart_init();
void Send_Byte(unsigned char transbyte);
void Send_Byte2(unsigned char data);
void send_status(); 
void transmittops();
void Transmitt_string();

void systemInit(void);
void IOinit(void);
void latchdata(unsigned char num);
void disp_hex_window1(unsigned int hex_data);
void disp_hex_window2(unsigned int hex_data) ;
void Display(void);
void timer1_init();
void timer3_init();
void PWM_INIT_DT();
void  init_pwm();
void Update_PWM(unsigned int setwsduty);
void capture_init(); 
void ENCODER_INIT();
unsigned char SCANENCODER1();
unsigned char SCANENCODER2();
unsigned char enc1_port();
unsigned char enc2_port();
void key_application(unsigned char keypress);








