#ifndef _VARIABLE_C_
#define _VARIABLE_C_



const unsigned int lookup_table[44]=
				{ //{a,b,c,d,e,f,g,dp}
				       0x3F, //0    // Position - 0x00
                                       0x06, //1    // Position - 0x01
                                       0x5B, //2    // Position - 0x02
                                       0x4F, //3    // Position - 0x03
                                       0x66, //4    // Position - 0x04
                                       0x6D, //5    // Position - 0x05
                                       0x7D, //6    // Position - 0x06
                                       0x07, //7    // Position - 0x07
                                       0x7F, //8    // Position - 0x08
                                       0x6F, //9    // Position - 0x09
                                       0x80, //DP   // Position - 0x0A
                                       0x77, //A    // Position - 0x0B
                                       0x7C, //B    // Position - 0x0C
                                       0x39, //c    // Position - 0x0D
                                       0x5E, //D    // Position - 0x0E
                                       0x79, //E    // Position - 0x0F
                                       0x71, //F    // Position - 0x10
                                       0x3D, //G    // Position - 0x11
                                       0x76, //H    // Position - 0x12
                                       0x06, //I    // Position - 0x13
                                       0x1E, //J    // Position - 0x14
                                       0x70, //K    // Position - 0x15
                                       0x38, //L    // Position - 0x16
                                       0x55, //M    // Position - 0x17
                                       0x54, //N    // Position - 0x18
                                       0x3F, //O    // Position - 0x19
                                       0x73, //P    // Position - 0x1A
                                       0x67, //Q    // Position - 0x1B
                                       0x50, //R    // Position - 0x1C
                                       0x6D, //S    // Position - 0x1D
                                       0x78, //T    // Position - 0x1E
                                       0x1C, //U    // Position - 0x1F
                                       0x3E, //V    // Position - 0x20
                                       0x6A, //W    // Position - 0x21
                                       0x68, //X    // Position - 0x22
                                       0x6E, //Y    // Position - 0x23
                                       0x89, //Z    // Position - 0x24
                                       0x00, //all seg off  // Position - 0x25
                                       0x40, //-         // Position - 0x26
                                       0xFF, //ALL SEG ON// Position - 0x27
				};
//==============================================================================




/*
const unsigned int lookup_table[44][8]=
							{ //{a,b,c,d,e,f,g,dp}
								{0,0,0,0,0,0,0,0},		//   0x00   null character forword slash '/'
								{1,1,1,1,1,1,0,0},		//0  0x3F
								{0,1,1,0,0,0,0,0},		//1  0x06
								{1,1,0,1,1,0,1,0},		//2  0x5B
								{1,1,1,1,0,0,1,0},		//3  0X4F
								{0,1,1,0,0,1,1,0},		//4  0X66
								{1,0,1,1,0,1,1,0},		//5  0X6D
								{1,0,1,1,1,1,1,0},		//6  0X7D
								{1,1,1,0,0,0,0,0},		//7  0X07
								{1,1,1,1,1,1,1,0},		//0   0X7F  
								{1,1,1,1,0,1,1,0},		//9   0X6F
								{1,1,1,1,1,1,0,0},		//3A  0X3F
								{0,1,1,0,0,0,0,0},		//3B  0X06
								{1,1,0,1,1,0,1,0},		//3C  0X5B
								{1,1,1,1,0,0,1,0},		//3D  0X4F
								{0,1,1,0,0,1,1,0},		//3E	0X66
								{1,0,1,1,0,1,1,0},		//3F	0X6D
								{1,0,1,1,1,1,1,0},		//41	0x7D
								{1,1,1,0,1,1,1,0},		//A	0X77
								{0,0,1,1,1,1,1,0},		//B	0X7C
								{1,0,0,1,1,1,0,0},		//C	0X39
								{0,1,1,1,1,0,1,0},		//D	0X5E
								{1,0,0,1,1,1,1,0},		//E	0X79
								{1,0,0,0,1,1,1,0},		//F	0X71
								{1,0,1,1,1,1,0,0},		//G	0X3D
								{0,1,1,0,1,1,1,0},		//H	0X76
								{0,0,1,0,0,0,0,0},		//I	0X04
								{0,1,1,1,1,0,0,0},		//J	0X1E
								{0,0,0,0,1,1,1,0},		//K	0X70
								{0,0,0,1,1,1,0,0},		//L	0X38
								{1,0,1,0,1,0,1,0},		//M	0X55
								{0,0,1,0,1,0,1,0},		//N	0X54
								{0,0,1,1,1,0,1,0},		//O	0X5C
								{1,1,0,0,1,1,1,0},		//P	0X73
								{1,1,1,0,0,1,1,0},		//Q	0X67
								{0,0,0,0,1,0,1,0},		//R	0X50
								{1,0,1,1,0,1,1,0},		//S	0X6D
								{0,0,0,1,1,1,1,0},		//T	0X78
								{0,1,1,1,1,1,0,0},		//U	0X3E
								{0,1,1,1,1,1,0,0},		//V	0X3E
								{0,1,0,1,0,1,1,0},		//W	0X65
								{0,0,1,0,0,0,0,0},		//X	0X04
								{0,1,1,1,0,1,1,0},		//Y	0X6E
								{1,0,0,1,0,0,1,0},		//Z	0X49
							};
//==============================================================================
*/


unsigned char diswin1[8]= {'0','0','0','0','0','0','0','0'};
//unsigned char arr[8]={'0','0','0','0','0','0','0','0'};
const unsigned int Displayarr[11]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0xFF};
unsigned int setvoltage=0,setcurrent=0,prevsetcurrent=0,prevsetvoltage=0,setwirespeed=0,prevsetwirespeed=0x00,newsetwirespeed=0;
//unsigned char dVal0=0,dVal1=0,dVal2=0,dVal3=0,dVal4=0,dVal5=0,dVal6=0,dVal7=0;
//unsigned char Key_s1=0,Key_s2=0,Key_s3=0,Key_s4=0,keypresson=0;
unsigned char static  digit=0;
volatile unsigned char wfstatusbyte=0,updatedispf=0,displayonf=1,portbstatus=0x00,pportb=0x00,prevkey='Z',key='X',crater_speed=0;
unsigned char temp=0,i=0,plus111=0,minus111=0,firstpulse1=0,secondpulse1=0,plus222=0,minus222=0,firstpulse2=0,secondpulse2=0;
unsigned int  new1=0,old1=0,new2=0,old2=0,setpfreq=0,Hi_setppwm=0,Lo_setppwm=0,rel_wirespeed=0;
unsigned char encod1=0,encod2=0,TORCH='X',pcount=0,prevTORCH=0xFF,torchonf=0;

volatile unsigned char OneH=0x00,OneL=0x00,TwoH=0x00,TwoL=0x00,Count=0,onesecf=0,softstartf=0,rxdata=0,
                       txonf=0,count_2ms=0,read_enc1f=0,enccount=0,dispupdatef=1,fixintervalf=0,capintervalf=0,count_pid=0;
volatile unsigned int  Two=0,One,Total_Count=0,count_1ms=0,pperiod=0,avgpperiod=0,pfreq=0;
unsigned long Total_Period=0;
unsigned int iii=0,ijk=0,lmn=0,Actual_amp=0xFFFF,Actual_vtg=0xFFFF,recpsstatus=0,recstatus=0,statusptr1=0;

unsigned char startptr1=0,arrptr=0,recchksum=0,rec_arr[22],transmitonf=0,chksum=0,inchkeyon=0,inchcnt,send_statusf=0;
unsigned int delinch=0,delinch1=0,creepspeed=0,openloopcnt=0,disp1term=0,disp2term=0,disp3term=0,disp4term=0,gapfreq=0;
unsigned char closeloopf=0,cyclestrtf=0, Tx_ptr=0,count_1msec=0,kpressread=0;
unsigned char minuspara1=0,pluspara1=0,pluscount1=0,minuscount1=0,mili1_100=0,tans=0,adaptivepidf=0;
unsigned char minuspara2=0,pluspara2=0,pluscount2=0,minuscount2=0,mili2_100=0,torchstatus1=0,torchstatus2=0,wfspeedchangef=1;
unsigned int parclength=0xFFFF,disparclength=0x0000;
volatile unsigned int count_transms=0;
unsigned int delay=0,prevFltpfreq=0,Fltpfreq=0,mahesh_test=50;

double integral_new =0, integral_old=0,error_old =0,error_new=0,minoutmax=0,controller_out=0;
float Tsampling =1.0;
unsigned int scalefactor2=71.0,minfmspeed=50,scaled_baseval2=0,maxfmspeed=750;//2800;
unsigned char togglepin=1,closeloop1f=0;
unsigned char cEditfg,cWf2t4tmodefg,cTestfg,cGasRlyClrfg;
unsigned int iTest,iGasDbCnt = 0;
unsigned char cRelSpeedSign;
volatile unsigned char weldmode=0,comm_error_count=0,error4=0,universal_error=0,error8,universal_error_latch=0;

volatile unsigned char error_code1,error_code2,creep_speed=0;
//enum()

#define key_gason   1
#define key_inch    2
#define key_mode    3
#define key_disp    4
#define key_no      0

#endif



