 unsigned int weldcurrent=0,pweldcurrent=0,weldvoltage=0,pweldvoltage=0,portvalue=0,result0=0,result1=0,result2=0,result3=0,result4=0,result5=0,trip_ip=0,
             psetcurrent=0,offset=0,hsetcurrent=1,phsetcurrent=0,hsetvoltage=1,phsetvoltage=0,precweldvtg=0,recweldvtg=0,transstatus=0,reclower=0,rechigher=0,
             dispweldcurrent=0,pdispweldcurrent=0,offsetsh1=0,offsetsh2=0;
             
volatile unsigned int mma_weldvoltage=0,cnt_mma=0;
unsigned long resultv_mma=0;

unsigned char CURR[4],VOLT[4],arr[8],disdigit=1,abc=0,weldon=0,setdp=0,offsetf=0,offsetcnt=0,welding_flag=0,
count_1ms=0, count_tx2_1ms=0, startstatustx2=0,tx2statuscounter=0,count_tx2=0,transmit2wf_f=0,remote_flag=0;

unsigned char trans_flag,uartdata2=0,start_rec_data=0, start_rec_status=0, recdata_arr[8],rec_status_f=0,
uartdata=0,startrec=0,recdata_arr[8],rec_cnt=0,transchksum=0,recchksum=0,recstatus=0,
pwelding_status='x',welding_status='F',received_arr[25],trans_ps_wf_arr[24];	

unsigned char uartdata1=0,startrec1=0,recdata_arr1[8],rec_cnt1=0,transchksum1=0,recchksum1=0,reclower1=0,
              rechigher1=0,motoronf=0,starttx2=0,tx2counter=0;  //tx2chksm=0,
    
unsigned long resulti=0,resultsm=0,resultv=0,resultt=0,resultic=0,resultvc=0,resultfm=0,resultsh1=0,resultsh2=0;

unsigned int setcurrent=50,cnt=0,disp_flag=0,count_5sec,count_3sec,poweron_flag=0,memdata=0,refmotorvtg=0,
tx2chksm=0,new_tx2chksm=0,cv_counter=0;

unsigned char encod,temp,old,firstpulse,secondpulse,new,plus,minus,switchh_flag=0,switchl_flag=0,eswitch=0,Arcstrikef1=0,Arconf=0,migmodeon=0,	migcount=0;
  
unsigned char count_1ms,count_10ms,count_100ms,cali_flag,cali_on1,Disp_updatef=0,PrevTorchans=0,
              Torchans=0,softstartf=0,ii=0,iii=0,count_transmit=0,check=0;

unsigned int count_preflow=0;

unsigned char remoteonf=0,setflag=0,mma_flag=0,mig_flag=0,saw_flag=0,display_flag=0,process_flag,mig_trans_f=0,
mma_init=0,weldoff_dis=0,disp_1sec=0,trip_flag=0,comm_flag=0,trip_status=0,Keyans=0,
Prevkeyans=0,danger_flag=0,trans_chk_f=0;

unsigned int mili_100=0,pluscount=0,minuscount=0,pluspara=0,minuspara=0,aaa=0,PWMcount=0,Arccounter=0,tempvolt=0,Addoffsetvtg=0,PWMcount1=0,mvoltage=0,tempmvolt=0;

volatile unsigned int comm_count=0,setvoltage1=1,psetvoltage1=0;
unsigned int disp_cnt=0,remotecnt=0,avg_vtg=0,offsetsetvtg=0,resistance=0,avgcntr=0,bbb=0,xyz=0,ccc=0;
unsigned char operator='P',calibrationf=0,disp_calf=0,read_hvtgf=0,recvtgcntr=0,Read_Ensw=0,Read_torchswf=0;
unsigned long measured_vtg=0,avg_hvtg=0,avg_psvtg=0,avg_pscur=0,measured_hvtg=0,measured_psvtg=0,measured_pscur=0;

unsigned char startptr1=0,startptr2=0,CCCVmodef=0,arr_pointer=0; 
unsigned int rsetcurrent=0,rsetvoltage=0,rsetvoltage1=0,prsetcurrent=0,prsetvoltage=0,newpwm=0,actual_voltage=0,
mcnt=0,motorerrcnt=0,over=0,over1=0,rset_wirespeed=0,prset_wirespeed=0,p_setvtg=0,p_rsetvoltage1=0,
set_v=0;
unsigned char Torchkey=0,Inchkey=0,Motorerr=0,Torchmode=0,Gasonkey=0,kpressread=0,sawweldmode='V',gas_check_f=0;
unsigned int shfb1curr=0,shfb2curr=0,shfbweldcurr=0;dVal0=0,dVal1=0,dVal4=0,dVal5=0,dispshfb1=0,dispshfb2=0,curimb=0,dVal2=0,dVal3=0,imbal=0;
unsigned char cyclestrt=0,burnbackcnt=0,torchrelease=0,crateron=0,motortrip=0,start_cv=0,overflag=0,adcread_overf=0;
unsigned long counter=0;
unsigned char scalmode=0,releasef=0,shuntcal1f=0,shuntcal2f=0,curimbf=0,imtrip_flag=0,arcforcemodef=0,keyrelease=0;
unsigned int arcforce=0,newcurrent=0,hotstartcount=0,dvalcnt=0,startdf=0,dac_counts=0,dac_counts_new=0;
float fweldvoltage=0.0,farcforce=0,fnewcurrent=0.0,fsetcurrent=0.0;
unsigned char hotf=0,calmodef=0,setupcalmode=0,dispcalmodef=0,err1=0,err2=0;
enum {pre,weld,burn,post,exit1}oper;
unsigned int parcforce=0xFFFF,pcurrent=0xFFFF;
volatile unsigned char rec_wf_status=0;
long double kp_prev,ki_prev,kd_prev;
double gamma1,gamma2,gamma3;
//pid
int sf_setpoint, sf_feedback, sf_error, sf_preverror,sf_ppreverror,sf_corrected_error;
int sf_kpgain=0, sf_kigain=0, sf_kdgain=0;
long sf_outputmax=64000; //128000;//256000; //25600;
long sf_outputmin=0;
long sf_accumulator=0;
long sf_pterm=0,sf_iterm=0,sf_dterm=0,sf_pid=0,sf_pid_old=0,sf_prevpid=0;
int sf_scalefactor; //=7; //8; //7
volatile unsigned int sf_pidoutput=0, scaled_sf_pidoutput=0, migdaccount=0,migdaccount1=0,migdaccount2=0,iLowpidvalue,ishvalue,imfvalue;
volatile unsigned char MIGweldon_detectf=0;
unsigned int mult_factor;

/****************************************************variables for common wirefeeder as versa 400********************/
unsigned char cEditfg,tx2chksum,arrptr;
volatile unsigned char startstatus1,recwfstatus;
unsigned int iAvg_cnt;iAvg_cntr=0,iNoofshift,iNoofDispShift,loop;
unsigned long resultmig=0,iMigOffset;
//int scalevalue;
//-----------------------------------------------------
unsigned char cTestfg,Testfg,keyfoundfg,WfEditfg;
unsigned char cTest;
unsigned int iTest,iRemotechkCntr;
unsigned char cpidmode;
unsigned int iKp,iKi,iKd;iMul;
unsigned int prevdac_counts=0,final_dac=0;
unsigned char piderrorfg,daccountfg;
//unsigned int epsilon,dt;
long sf_dererror=0;
long PID_pterm=0,PID_iterm=0,PID_dterm=0;
unsigned char start_pid_fg,set_pid_fg;
unsigned int count_iTest;
unsigned char pidfg, cEditfg,cFrameStr,cFramefg;
unsigned char cPowerOnblockrxfg;
unsigned int iPowerOnCntr;
//-----------------------------------------------------
//unsigned char Type.twot;
unsigned char count_postflow,mig_parameters;
unsigned int parametercnt=0;
//-----------------------------------------------------
volatile unsigned char error_4_check4t,error4_flag,ERROR_4_errorf,comm_errorf;
volatile unsigned int cntsecond_er4,communication_time_out,cErrorChkoverfg;
unsigned int i=0,j=0;
unsigned char cPowerFlashfg,cFlashfg;
unsigned int cFlashCntr;
unsigned int ArcforceCurr;