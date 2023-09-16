 unsigned int weldcurrent=0,pweldcurrent=0,weldvoltage=0,pweldvoltage=0,portvalue=0,result0=0,result1=0,result2=0,result3=0,result4=0,result5=0,trip_ip=0,
             psetcurrent=0,offset=0,hsetcurrent=1,phsetcurrent=0,hsetvoltage=1,phsetvoltage=0,precweldvtg=0,recweldvtg=0,transstatus=0,reclower=0,rechigher=0,
             dispweldcurrent=0,pdispweldcurrent=0,offsetsh1=0,offsetsh2=0,iSetcurrbuff;
             
volatile unsigned int mma_weldvoltage=0,cnt_mma=0;
unsigned long resultv_mma=0;

unsigned char CURR[4],VOLT[4],arr[8],disdigit=1,abc=0,weldon=0,setdp=0,offsetf=0,offsetcnt=0,welding_flag=0,count_1ms=0;

unsigned char trans_flag,uartdata=0,startrec=0,recdata_arr[8],rec_cnt=0,transchksum=0,recchksum=0,recstatus=0,pwelding_status='x',welding_status='F';	

unsigned char uartdata1=0,startrec1=0,recdata_arr1[8],rec_cnt1=0,transchksum1=0,recchksum1=0,reclower1=0,rechigher1=0,motoronf=0;  
    
unsigned long resulti=0,resultsm=0,resultv=0,resultt=0,resultic=0,resultvc=0,resultfm=0,resultsh1=0,resultsh2=0;

unsigned int setcurrent=50,cnt=0,disp_flag=0,count_5sec,count_3sec,poweron_flag=0,memdata=0,refmotorvtg=0;

unsigned char encod,temp,old,firstpulse,secondpulse,new,plus,minus,switchh_flag=0,switchl_flag=0,eswitch=0,Arcstrikef1=0,Arconf=0,migmodeon=0,	migcount=0;
  
unsigned char count_1ms,count_10ms,count_100ms,cali_flag,cali_on1,Disp_updatef=0,PrevTorchans=0,Torchans=0,softstartf=0;

unsigned char remoteonf=0,setflag=0,mma_flag=0,mig_flag=0,saw_flag=0,display_flag=0,process_flag,mma_init=0,weldoff_dis=0,disp_1sec=0,trip_flag=0,comm_flag=0,trip_status=0,Keyans=0,Prevkeyans=0,danger_flag=0;

unsigned int mili_100=0,pluscount=0,minuscount=0,pluspara=0,minuspara=0,aaa=0,PWMcount=0,Arccounter=0,tempvolt=0,Addoffsetvtg=0,PWMcount1=0,mvoltage=0,tempmvolt=0;

volatile unsigned int comm_count=0,setvoltage1=1,psetvoltage1=0;
unsigned int disp_cnt=0,remotecnt=0,avg_vtg=0,offsetsetvtg=0,resistance=0,avgcntr=0,bbb=0,xyz=0,ccc=0;
unsigned char operator='P',calibrationf=0,disp_calf=0,read_hvtgf=0,recvtgcntr=0,Read_Ensw=0,Read_torchswf=0;
unsigned long measured_vtg=0,avg_hvtg=0,avg_psvtg=0,avg_pscur=0,measured_hvtg=0,measured_psvtg=0,measured_pscur=0;

unsigned char startptr1=0,startptr2=0,CCCVmodef=0,cModel,cLockfg,cLockkeyfoundfg; 
unsigned int rsetcurrent=0,rsetvoltage=0,prsetcurrent=0,prsetvoltage=0,newpwm=0,mcnt=0,motorerrcnt=0,over=0,over1=0;
unsigned char Torchkey=0,Inchkey=0,Motorerr=0,Torchmode=0,Gasonkey=0,kpressread=0,sawweldmode='V';
unsigned int shfb1curr=0,shfb2curr=0,shfbweldcurr=0;dVal0=0,dVal1=0,dVal4=0,dVal5=0,dispshfb1=0,dispshfb2=0,curimb=0,dVal2=0,dVal3=0,imbal=0;
unsigned char cyclestrt=0,burnbackcnt=0,torchrelease=0,crateron=0,motortrip=0,start_cv=0,overflag=0;
unsigned long counter=0;
unsigned char scalmode=0,releasef=0,shuntcal1f=0,shuntcal2f=0,curimbf=0,imtrip_flag=0,startdf=0,arcforcemodef=0,keyrelease=0;
unsigned int arcforce=0,newcurrent=0,hotstartcount=0,dvalcnt=0,iSetmincurrbuff,iLockcnt;
float fweldvoltage=0.0,farcforce=0,fnewcurrent=0.0,fsetcurrent=0.0;
unsigned char hotf=0,calmodef=0,setupcalmode=0,dispcalmodef=0;
enum {pre,weld,burn,exit1}oper;
unsigned int parcforce=0xFFFF,pcurrent=0xFFFF;
unsigned int iSetAmpLimit;
unsigned char EEpromWrfg;
unsigned char cCurrCalicntfg,cCalikeyfoundfg,cCalifg,cTestfg,cCaliFoundfg,cCaliEditfg;
float fCalicnt;
unsigned int iCalicnt;

struct Type_D
{
	unsigned char digitdp1	:1;
	unsigned char digitdp2	:1;
	unsigned char digitdp3	:1;
	unsigned char digitdp4	:1;
	unsigned char digitdp5	:1;
	unsigned char digitdp6	:1;
	unsigned char digitdp7	:1;
	unsigned char digitdp8	:1;
};

union Type_DP
{
	struct Type_D TypeD;
	unsigned char DPGROUP[1];
};

union 	Type_DP 	TypeDP;
#define Typedp		TypeDP.TypeD


long double kp_prev,ki_prev,kd_prev;
double gamma1,gamma2,gamma3;
/*struct pidParameters
{
	float Kp;
	float Ki;
	float Kd;
	float Kf;
	
	float error;
	float output1;
      float output;
      float previous_output;
      float plant_output;
      float plant_previous_output;
      float plant_pre_previous_output;
	float outmax;
	float ReferenceSetpoint;
	float feedback;
	float integral;
	float derivitive;
	float previous_error;
      unsigned long absolute_error;
	float saturated;
	float pidoutput;
} 	pidParams,pidParamsv;*/

struct PID_s_Parameters
{
	float a;
	float b;
	float c;
	unsigned long  d;

	signed long  error;
	signed long output;
      signed long poutput;
	signed long outmax;
	signed long ReferenceSetpoint;
	signed long feedback;
	signed long integral;
	signed long derivitive;
	signed long previous_error;
      signed long pprevious_error;
      unsigned long absolute_error;
	signed long saturated;
	signed long smcoutput;
      signed long surface;
      unsigned long abs_surface;
} 	PID_sParams;

