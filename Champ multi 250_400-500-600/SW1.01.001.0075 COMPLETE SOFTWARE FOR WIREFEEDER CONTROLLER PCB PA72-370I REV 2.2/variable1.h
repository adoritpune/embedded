void _ISR _INT3Interrupt(void);
void _ISR _T1Interrupt(void);
void _ISR _ADCInterrupt(void);
void _ISR _T2Interrupt(void);
void _ISR _LVDInterrupt(void);
void _ISR _U1RXInterrupt(void);

void adc_init();
void lowvtg_init();
void extint3_init();
inline unsigned char scanencoder();
inline unsigned char scanencoder1();
inline unsigned char scanremote();
inline unsigned char scanremote1();
inline unsigned char read_fport();
inline unsigned char read_bport();
inline unsigned char read_dport();
inline unsigned char read_eport();
void uart_init();
void encoder_init();
void send_mesg();
void trans(unsigned char);
unsigned int hextodec(unsigned int);
void init_portpin(void);
void allrowlogic0();
inline void allcolumnlogic1();
void timer1_init();
void bigdelay();

unsigned char scancolumn();
void pwm_init();
void display_init(void);
void latchdata(unsigned char);
inline void drive_motor(unsigned int);
unsigned char read_keypad();
inline unsigned char key_press();
inline unsigned char getkey();
inline unsigned char columnnum1(unsigned char rowno);
inline void all0exceptcolumn1();
inline void all0exceptcolumn2();
inline void all0exceptcolumn3();
inline void all0exceptcolumn4();
inline void debounce_delay();
unsigned char keyrelease();
void SENDSERIAL(unsigned int);
unsigned int EEPROM_Read(unsigned int);
unsigned int EEPROM_Erase_Write(unsigned int,unsigned int);
inline void delay();
void led_init();
void portpin_init();
void read_torchsw();
void Read_GWSW();
void Read_Pressure_SW();
void Read_WSAMP_SW();

unsigned char a,b,c,ans,temp,encres=0,encres1=0;
unsigned char key,old,timeoff=0,new,thscan=0;
unsigned char oldr=0,newr=0,old1=0,new1=0,oldr1=0,newr1=0;
unsigned char keyscan=0;
unsigned char encoderscan=0,msec=0; 
unsigned int portvalue;
unsigned int EE_Addr;
unsigned int EE_Data;  
unsigned int EE_status;
unsigned int ADCValue=0,password=0,passprotect=0,lockvalue=0;
volatile unsigned int *ADC16Ptr;
void display_data(void);
unsigned int display_latch(unsigned char data);
inline unsigned char float_to_ascii_str(unsigned char *,float);
float voltage,current;
static unsigned char win1[3];
static unsigned char win2[3];
static unsigned char diswin1[3];
static unsigned char diswin2[3];
unsigned char arr[8],displayarr[12];
unsigned char disdigit=1;
unsigned char win1dpcnt=0,win2dpcnt=0;	
unsigned char mahesh=0;
unsigned int mk=0;
unsigned char setdp=0;
void key_application(unsigned char);
unsigned char modeset=0;  //for enable default  weld led
unsigned char strt10cnt=0;		//for starting the timer to count of 10 sec
unsigned int  cntr10sec=0;		// ten second counter for disabling multispot and spot 	
unsigned char ovrflow10sec=0;
unsigned char torch=0;
unsigned char torchonf=0;
unsigned char preflowokf=0;
unsigned char weldstrtf=0;
unsigned char burnbackstrtf=0;
unsigned char postflowstrtf=0;
unsigned int timerval=0;
unsigned char strttmr=0;
unsigned int cntsecond=0;
unsigned char dummytorch=0;
unsigned char torchrelease=0;	
unsigned char exitloop=0;
float fburnbacktime=0.0;
enum {pre,weld,burn,post,pause,exit}oper;
unsigned char cyclestrt=0;
unsigned char torchenable=0;
float fbvtg=0,fbcurr=0,fbmvtg=0,feedamp=0;
float dispfbvtg=0,dispfbcurr=0,dispfbmvtg=0;
float tempdisp1,tempdisp2;
unsigned int ans1=0;
unsigned int hextodec(unsigned int);
void transmit_dec(unsigned int);
unsigned int updatedata(unsigned int,unsigned int,unsigned int,unsigned char);
void softstart_motor(unsigned int);
unsigned int setupmode=0;
unsigned char fastexit=0,arcrstf=0;
unsigned int prepwmcnt=0;
unsigned char coursemode=1;
unsigned char finemode=0;
unsigned char findvalue(unsigned char);
unsigned int findmatindex(unsigned int);
unsigned int findmatindex1(unsigned int);
unsigned int findmatindex2(unsigned int);
unsigned int findmatindex3(unsigned int);
unsigned int findmatindex4(unsigned int);
unsigned char prevkey=0,modechangef=0;
unsigned char count_1ms=0,count_10ms=0,count_100ms=0,count_1sec=0;
unsigned char multiplekey=1,multiplekey1=1,multiplekey2=1,multiplekey3=1;
unsigned int multi1=0,multi2=0;
unsigned char setpt1=0,setpt2=0,Motorerrf=0;
unsigned int weldvtg=0;
unsigned char mesrweldvtg=0;
unsigned int autopwmval=0;
unsigned char setupautomode=0,arcon=0;
unsigned int autooffset=0;
unsigned char check_window(float,float);
static float preweldvtg=0;
unsigned char keychange=0,keychange1=0;
unsigned char torchval=0,Read_SWf=0,Pressure_ERRf=0,Watercooledf=0,Pressureonf=0,Moverloadf=0;
unsigned char chkpausetime=0;
unsigned char memlocation=1;
unsigned char setmemloc=0;
float fpwmtime,fwirespeed,autocur=0,prevfws=0,autovolt=0,fsendvtg=0,fwirespeed_max=22;
unsigned char displprev=0,savemesg=0;
unsigned int i=0,inchcounter=0;
unsigned char setrecall=0,disprcl=0,disrcldata=0;
void readmematstrt();
void writemematstop();
unsigned char gasocvinch=0;	//stop display update during gas ocv and inching checking
unsigned char strtinchcntr=0,autoinch=0; //if inching is started but welding is not started, then stop inching
static unsigned int prevmemarr[40];
static unsigned int curoffset=0,vtgoffset=0;
static unsigned char setoffset=0;
unsigned char firstpulse=0,firstpulse1=0,secondpulse=0,secondpulse1=0;//firstpulser=0,firstpulser1=0,secondpulse=0,secondpulse1=0;
inline unsigned int calmvtgerr(unsigned int pwmtm);
unsigned char mvtgmesrf=0,setpasswordf=0,mesgsvd=0,cratersetup=0,sendtoremotef=0;
unsigned int passtemp=0,ijk=0,abc=0;
unsigned char enblpasskey=0,chkpass=0,passerr=0,enblencoder=0;
unsigned char scanthswitch(void);
unsigned char therrf=0,prevthsw=0,currthsw=0,cntpass=0,overshootcnt=0,pidovershootf=0,DispWSf=0;
unsigned char coursevtgsetf=0,coursevtgset=0,startstoref=0,startmotor=0,weldingstart=0,keydetect=0,Dispmampf=0;
static double startvtg=0;
unsigned char uartdata=0,reccnt=0,receivef=0,recstrtptr=0,rec_arr[5],transon=1;
unsigned int reclower=0,rechigher=0,recremotevtg=0,recremotews=0,sendcur=0,sendvtg=0;
unsigned int pwmtime1=0,prevpwmtime1=0,slope1=0,slope2=0,paravolt=0;
float slope=0.0,prevdispfbvtg=0;
void updatedatacv(unsigned char,unsigned char);
void updatedatacc(unsigned char,unsigned char);
void keyaction(unsigned char);
void torchaction();
void genref(unsigned int);
unsigned int calcarcforce(unsigned int);
void transtoremote(unsigned int,unsigned int,unsigned int,unsigned int,unsigned char,unsigned char,unsigned char);
void Read_Motorovld_SW();

unsigned char	inrushf=0,strtmtrovldcntrf=0;
unsigned int 	inrushcounter=0,movldcounter=0;
						
float setcurrent=0,setvoltage=0,cratervoltage=0;
unsigned char cccvmode=0,model=0,errflag1='N',errflag2='N',prevcccv=0,acrmesg=0;
unsigned char plus1=0,minus1=0,secondpulse11=0,firstpulse11=0,plus111=0,minus111=0,plus222=0,minus222=0;
unsigned char plusr=0,minusr=0,secondpulser=0,slopept1=0,slopept2=0;//,ReceivedChar=0;
unsigned int memdata=0,cvslope=0,ccslope=0,ccoffset=9.0,cvoffset=1.0,memcntr=0,resnum1=0,resnum2=0; //ccoffset=10.0 modified as per quality internatinal
unsigned int curmulti=0,vtgmulti=0,motormulti=0,tempdata=0,newpwm=0;
//unsigned char noplusactionf=0,nominusactionf=0;
unsigned int maxfcawwf=65;//70;		//maximum fcaw wirespeed 6 m/min
unsigned int maxmigwf=180;		     //maximum mig wirespeed 18 m/min
void read_model();
unsigned char mc_model='A',ss=0,mesgdispf=0;
float fcawwfmul=0.0,Currentfactor=9.20,maxmmacurrent=399.0,maxmigvolts=40.0,cratervoltfactor=0.22;
unsigned char autodatarow=58,mlsec=0,unitf=0,savepassf=0,UV_errorf=0,OV_errorf=0,TH_errorf=0,Errorf=0;
unsigned char transchksum=0,recchksum=0,updatedisp=0,WeldMode=0x00;
void inch_motor(unsigned int);
unsigned int motorpwm=0;
char str[4]; 
double flt=2.4567; 
unsigned char maheshkp=0,arczerof=0,offallkeyf=0;//,passprotect=0;
unsigned int prevweldcurrent=0,prevarcforce=0,prevpwmtime11=0,arcmin=0,archr=0,arconmin=0,arconsec=0,arconhr=0;
unsigned int prevhr=0,prevmin=0,prevsec=0;
float temp1;
unsigned int wirespeed=0,current1=0,current2=0,voltage1=0,voltage2=0,craterpwmtime1=0,craterpwmtime=0,tripvtg=0,prevtripvtg=0XFFFF,tripdiff=0;
unsigned char ramdata=0x00,ramdata1=0x00,HS_errorf=0,offsetcnt=0,Weldonerrorf=0,tripcount=0;
unsigned long totaltripvtg=0;
//------------------------------------------------------
unsigned int CalVoltAsPerWirespeed(unsigned int );
unsigned int CalCurrAsPerWirespeed(unsigned int );
unsigned int WFmotorCal(unsigned int );	
//------------------------------------------------------	
	
					