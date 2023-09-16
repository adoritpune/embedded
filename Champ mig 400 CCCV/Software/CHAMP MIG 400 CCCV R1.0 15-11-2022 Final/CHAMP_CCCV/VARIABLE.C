unsigned char trans_ps_wf_arr[25];

unsigned char tempkey=0,temp=0,ijk=0,disdigit=1,setdp=0,diswin1[3],diswin2[3],arr[8],firstpulse1=0,secondpulse1,plus111=0,result=0,minus111=0,new1=0,
firstpulse2=0,secondpulse2,plus222=0,minus222=0,new2=0,firstpulse3=0,secondpulse3,plus333=0,minus333=0,new3=0,scan_count=0,encod1=0,encod2=0,encod3=0,old1=0,old2=0,old3=0,
col=0,glcd_flag=0,key=0,ans=0,Prevkey=0,softstartf=0,weldmodeoff=0,setptimef=0,setstimef=0,openloopnew=0,Aweldonf=0;

unsigned char keyrow=0,keycolumn=0,keypad=0,weldingonf=0,PULSEavgf=0,adcreadf=0;	
volatile unsigned char shortcktonf=0,MIGweldon_detectf=0;
volatile unsigned int pulseweldonf=0,twinpulsecnt=0;
float weldwiredia=0.8;
static unsigned char m=0X00,n=0Xff,torchonstatus='X',inch=0,weldmode='G',prev_weldmode=0,keyreadf=0,dispupdatef=1,weldingdone=0,inchcntr=0;
unsigned int power_delay=0,i=0,j=0,k=0,num1=0,num2=0,val=0,CURRENT=0,VOLTAGE=0,BVOLTAGE=0,PVOLTAGE=0,MVOLTAGE =0,TRIPVTG=0,daccount=0;
unsigned int count_1ms=0,count_20ms=0,count_500ms=0,count_200ms=0,cout_100us=0,prevwirespeed=0xFFFF,curwirespeed=0,count_500ms1=0,count_500ms2=0;
unsigned long maxbasetime=0,minbasetime=0,pulsebase=0,pulsepeak=0,pulsestep=0,pdaccount=0,uppeakamp=0,uppdaccount=0,sdaccount=0,bdaccount=0,peakamp=0,stepamp=0,baseamp=0,pulseduty=0;
volatile unsigned char weldonf=0,peakf=0,stepf=0,basef=0,mbase1f=0,mbase2f=0,mpeak1f=0,mpeak2f=0,setupmode=0,setpeakf=0,setstepf=0,setbasef=0,setfreqf=0,modechangef=1;
unsigned long peaktime=0,steptime=0,newbasetime=0,newsteptime=0,startpulsetime=0;
unsigned int timer_first_edge=0,timer_second_edge=0,mperiod=0,Prev_mperiod=0xFFFF,mfreq=0,newpeakamp=0,refbtime=0,maxrefbtime=0,minrefbtime=0;
unsigned int setwsfreq=0,softstartcnt=0,refpulsebase=0,refbaseamp=0,newpulsebase=0,maxpulsefreq=0,minpulsefreq=0;
signed long scaled_baseval2=0,scaled_baseval22=0,OPEN_scaled_val1=0,OPEN_pidoutput1=0,pulsefreq=0,Hi_pulsefreq=0,Lo_pulsefreq=0;
unsigned int circular_arr[5]={0,0,0,0,0},sum_circular_arr=0,circular_cnt=0,pulseontime=0,PULSEamp=0,PULSEvtg=0;//,carr=0;
unsigned int CVOLTAGE=0,loadbasetime=0,loadbaseamp=0,adel=0,bdel=0,wirestickupcnt=0,wirestickdowncnt=0,SCKCURRENT=0;
float ARCLFACTOR=0.025,pidkp=0.0,pidki=0.0,pidkd=0.0;//0.03;
 
unsigned int disp_kiterm=0,constpeakamp=0,const_arc_strike_pdaccount=0,count_weldonms=0,delarcon11=0,prevFltbvtg=0,Fltbvtg=0,rel_wirespeed=0;
volatile unsigned char startbmeasuref=0,endbmeasuref=0,arcforceonf=0,trans2_onf=0,adcreadoverf=0,addafref=0,lcdpage=1;

unsigned int SUMSCKBVTGARR=0,SCKCNT=0,AVGBSCKVTG=0,SCKBVOLTAGE=0,id=0,jd=0,count_tx2_1ms=0,count_tx2=0,vtg_circular_arr[8],vtg_circular_cnt=0,ACT_CVOLTAGE=0;
unsigned char Shortcktf=0,wfchangef=0,stopbasef=0,firstpulsef=0,DISPavgf=0,SCKavgf=0,intkp=0,intki,intkd=0;
unsigned long totalsumbvtg=0,totalsumbcnt=0,newpulseduty=0,totalsumtrip=0;
unsigned int total_fltbvtg=0,Fltbvtgcnt=0,avg_fltbvtg=0,afbcurrent=0,setpidbamp=0,af_bdaccount=0,actual_fltbvtg=0;	
volatile int pidfactor=1,pulsestartcnt=0;
volatile unsigned long twinpulsefreq=1,twinpulseperiod=100,twinpulseduty=50,twinpulseratio=10,
			twinpulseonperiod=0,twinpulseoffperiod=0;	
static int minoutputfreq=0,temp_mjp_vtg=0,arcforce_current=0,cvopenloopcnt=0;
static long controller_out=0,integral_max=0,integral_min=0;
//static long integral_old= 0;
signed long scaled_val1=0,scaled_baseval=0;//,scaled_newval=0;
signed long minoutmax=0;	
float addrippleamp=0.1;			

unsigned int totaltempvtg=0,tempvtgcnt=0,avgtempvtg=0,mavgtempvtg=0,wirestickf=0,tempvtg=0,presumdaccount=0,ALEN_pulsefreq=0;	
static unsigned int ADCAresult=0,ADCVresult=0,ADCEresult=0,SCKTloopcnt=16,SCKTcnt=0,ADCFresult;
static unsigned int DISPloopcnt=4096, DISPcnt=0,PULSEONOFFloopcnt=4,PULSEONOFFcnt=0;
static unsigned long Total_SCKFresult=0,Total_SCKAresult=0,Total_SCKVresult=0,Total_SCKEresult=0,Total_PULSEONOFFAresult=0;
static unsigned long Total_DISPFresult=0,Total_DISPAresult=0,Total_DISPVresult=0,Total_DISPEresult=0,Total_PULSEONOFFVresult=0,Total_AFVresult=0;
	
volatile unsigned char error_tx_flag=0;

//unsigned int MIGCCOFFSETNEW = 0;
//float MIGCCSLOPENEW  = 0;
unsigned char cEditfg;
//static unsigned int PID_bdaccount,PID_sdaccount,PID_newupstep=0,PID_newdownstep=0,PID_basetm=0,PID_steptm=0;
//******************************************************************************************************************************************

volatile long double kp2_prev,ki2_prev,kd2_prev,kp1_prev,ki1_prev,kd1_prev;
double kpgamma2,kigamma2,kdgamma2,Kiterm2,Kiterm1,kpgamma1,kigamma1,kdgamma1,fSampling_freq=0.0;
unsigned int scalefactor2=0,scalefactor1=0,reference_area=0,refpulsefreq=0,Pvolterr=0,weldonstartfcnt=0,weldonstartbcnt=0;
signed int scaled_val2,pulsebase_trial,scaled_output1=0,maxpulseduty=0,minpulseduty=0,adaptivekp=0;
float newpulsefreq=0.0,errorrate=0.0;
unsigned int num11=0,num12=0,ans11=0,errdaccount=0,ptosslope=0,middaccount=0,lowdaccount=0,upstep=0,downstep=0,newupstep=0;
unsigned char setparaBkpf=0,setparaBkif=0,setparaBkdf=0,setparaPkpf=0,setparaPkif=0,setparaPkdf=0,
              paraA=0,paraB=0,paraC=0,dispwirespeed=1,pweldonf=0,ploopcnt=0,transmit2f=0,baseonf=0,togglepin=0;

volatile unsigned char sendoncef=0,pulsecyclestrt=0,weldcyclestrt=0,prevpulsecycle=0,dummypulsecycle=0,startstatus1=0,
					   recstatus=0,recwfstatus=0,cvrefon=0,pulsestrtf=0,Vweldon_detectf=0,Aweldon_detectf=0,openloopf=0,
					   peakonf=0,Vweldon=0;

volatile unsigned int decaycurrent=0,setbaseamp=0,count_100ms=0,prevwirespeed1=0,micromulti=0,PID_interval=0,sckdaccount=0;//,basevtgcnt=0;

unsigned int psetcurrent=0,psetvoltage=0,outputpulsebase=0,minbaseamp=0,maxbaseamp=0,presetcurrent=0,count4_1ms=0,DACREF=0;
signed int minbase=0,maxbase=0,maxpulsedutyterm=0,minpulsedutyterm=0,temperror1=0,temperror2=0;
//signed int temperror1=0,temperror2=0;
unsigned int wfspeed=0,presultcur=0,PCURRENT=0,padccur=0,addonbase=0,addonbase1=0,tx2data=0,pmigsetwirespeed=0xffff,pmigsetvoltage=0xffff;

volatile unsigned int baseunit=0,loopcount=0,loopinterval=0,count_1sec=0,uartdata1=0,uartdata2=0,MAHESH=0,microsec=0;  
unsigned char loadpara1=0,iii=0,chksum=0,startptr1=0,arrptr=0,recchksum=0,rec_arr[22],transmitonf=0,transonf=0,frepidf=0,weldcycleon=0;

unsigned int ppmigsetwirespeed=0,ppmigsetvoltage=0,basecurcnt=0,basetime=0,peakvtg=0,peakvtgcnt=0,totalpeakvtg=0,startpulsetm=0,refbasetm=0;
unsigned int pidminbaseamp=30,temp_pidminbaseamp=0;//para.pmigmode.setwspeed*0.5; //30
unsigned int pidmaxbaseamp=200,temp_pidmaxbaseamp=0,total_pulse_tm=0;//minbaseamp=para.pmigmode.setwspeed*1.1;//0.5200;

float pulsetmfactor=0.25,pulsecurfactor=0.25,pulsefreqfactor=12.0;;
float MAXFBMULTIPLIER=12000.0;//10000.0;//2000.0; 

unsigned int OPEN_pulsetm=0,OPEN_steptm=0,OPEN_basetm=0,OPEN_pulserisetm=0, 
			 OPEN_pulsefalltm=0,OPEN_startpulsetm=0,OPEN_uppdaccount=0,OPEN_pdaccount=0,OPEN_sdaccount=0,
			 OPEN_bdaccount=0,OPEN_newupstep=0,OPEN_newdownstep=0,sum_setcurrent=0,sumdaccount=0;
			 			 
unsigned int PID_pulsetm=0,PID_steptm=0,PID_basetm=0,PID_pulserisetm=0, 
			 PID_pulsefalltm=0,PID_startpulsetm=0,PID_uppdaccount=0,PID_pdaccount=0,PID_sdaccount=0,
			 PID_bdaccount=0,PID_newupstep=0,PID_newdownstep=0,arcforce_amp=0;	

unsigned int FRQ_uppdaccount=0,FRQ_pdaccount=0,FRQ_sdaccount=0,FRQ_bdaccount=0,FRQ_newupstep=0,
			 FRQ_peakamp=0,FRQ_stepamp=0,FRQ_baseamp=0,tarbasevtg=0;			 


unsigned int PFREQ_uppdaccount=0,PFREQ_pdaccount=0,PFREQ_sdaccount=0,PFREQ_bdaccount=0,PFREQ_newupstep=0,
			 PFREQ_peakamp=0,PFREQ_stepamp=0,PFREQ_baseamp=0,low_base_amp,high_base_amp,base_amp_twin_pulse=0,min_base_amp=0,max_base_amp=0,min_freq=0,max_freq=0,step_base=0,step_freq=0,base_ramp_down_flag=0,twn_rmp_down_offst_tm=0;			 

			 
unsigned char extint1status1=0,extint2status1=0,extint1status2=0,extint2status2=0,pincheck=0,ext1ans=0,ext2ans=0,
			  count_1ms_ext=0,tx2chksum=0,starttx2=0,tx2counter=0,startstatustx2=0,tx2statuscounter=0,firsttimef=0;			 		 
	  			
unsigned int DISPfoot=0,DISPamp=0,DISPvtg=0,DISPerr=0,SCKamp=0,SCKvtg=0,SCKerr=0,SCKfoot=0,SCKVOLTAGE=0,sck_current_ref=0,temp_mjp=0,FLTSCKvtg=0,prevFLTSCKvtg=0,disp_newbaseamp=0;	  			
double footref_precent=0;	
	  			
//volatile enum {pulseriseop=1,startpulseop=2,pulseonop=3,pulsedecayop=4,steponop=5,stepdecayop=6,baseonop=7}pulsecycle;
#define pulseriseop		1
#define startpulseop 	2
#define pulseonop 		3
#define pulsedecayop 	4
#define steponop 		5
#define stepdecayop 	6
#define baseonop 		7
unsigned char pulsecycle=pulseriseop;

//volatile enum {pre,weld,burn,post,pause,exiti}oper;	
#define pre		1
#define	weld	2
#define	burn	3
#define post	4
#define	pause	5
#define	exiti		6
unsigned char oper=pre;

//volatile enum {dispws,dispamp,dispthickness,dispjob}displedptr1;
#define	dispws			1
#define dispamp			2
#define	dispthickness	3
#define	dispjob			4
unsigned char displedptr1=dispws;

//volatile enum {disparcforce,dispvolt,disparclength,disptime}displedptr2;
#define	disparcforce		1
#define	dispvolt			2
#define	disparclength		3
#define	disptime			4
unsigned char displedptr2=disparcforce,ak47=0,emg_sendf=0,changestatusf=0,currentchangef=0,voltagechangef=0,OCVON_command=0,prev_OCVON_command=8,power_on_in_mma=0,power_on_in_tig=0,T_weldingonf=0,M_weldingonf=0;
unsigned int mili1_100=0,pluspara1=0,pluscount1=0,minuspara1=0,minuscount1=0;


unsigned int pulserisetm=30.0,pulsefalltm=0;//,pulsedecaytm=100.0,stepdecaytm=50.0,
unsigned int pulsetm=120.0,steptm=50.0,basetm=200.0,disptemp=0,disptemp1=0;
float decayslope=0.0,linearcnt=0.0,decaycnt=0.0,decaycount=0,ptosmslope=0.0,upcnt=0.0,tempval=0.0,mkf=0.0;
unsigned char Adaptive_freq_pidf=0,keychange1=0,keychange2=0;		
unsigned int newdownstep=0,downcnt=0,baseavgcnt=0,idecaycount=0,refstepamp=0,tpulsetime=0,pulserisetime=0,pulsefalltime=0;
float adtemp=0.0,ECONSTANT=2.72;
volatile unsigned char shiftbvtgf=0,weldon_detectf=1;
unsigned int SUMBVTGARR=0,BCNT=0,AVGBVTG=0,BVTGARR[4],weldoncnt=0,ptigsetcurrent=0xFFFF;
unsigned int ripplecnt=0,ripplecurrent=0,dispautocurrent=0,dispautovoltage,dispautothickness=0,parcforce=0xFFFF,testmahe=0,
             parclength=0xFFFF,parcbasevtg=0,tempmjp=0,refpeakamp=0,refpeaktm=0,eedata=0;
volatile unsigned int RP_BVOLTAGE=0,bdaccount_rp=0,prowno=0,piii=0,piditeration=1,piditerationcnt=0;

unsigned int pulsepararr[10]={0,0,0,0,0,0,0,0,0,0};
unsigned char program_number=0,tungsten_size=0,disparclen=1,setrefparaf=0;
float ftemp=0.0,fwirespeed=0.0;
unsigned int wirespeed=0,current1=0,current2=0,voltage1=0,voltage2=0,thickness1=0,thickness2=0,Tbasevoltage1=0,Tbasevoltage2=0,
			Tbasevoltage=0;

unsigned char strttmr=0,torchval=0,dummytorch=0,prevpscyclestatus=0xFF,prevwfcyclestatus=0xFF,torchrelease=0,cratersetup=0,torchenable=0,crateron=0,fastexit=0,setlcdweldparameter=0,clearlcdf=0;
unsigned char lcdmigpointer=1,updatelcdf=0,lcdscan_flag=0,point=0,memoryzone='X',AFcnt=0;
unsigned int timerval=0, cntsecond=0,voltageref=0,fttrefvolt=0,cvoffsetref=0,prevpreflow=0xFFFF,prevburnback=0xFFFF,prevpostflow=0xFFFF,prevcratervoltage=0xFFFF,prevgcraterspeed=0xFFFF;
unsigned int prevpulseweldmode=0xFFFF,prevtwinpulsefreq=0xFFFF,prevtwinpulseduty=0xFFFF,prevtwinpulseratio=0xFFFF,prev_pcreepspeedrate=0xFFFF,prevcreepspeedrate; 
unsigned int timecount11=0,dispnum1=0,dispnum2=0,AFvtg=0;	
unsigned int don=0,donmin=0,donmax=100,prevdon=0xffff,flt,max_lcd_cnt=5;
/////debug variables
unsigned int EE_Stat = 0;
unsigned long int Act_EE_Addr =0;// EE_Addr + EE_START_ADDR;
unsigned int SAV_TBLPAG =0;// TBLPAG;
volatile unsigned int aks =0;

unsigned int read_mhotstart,read_msetcurrent,read_marcforce,read_mmaterial,read_melectrodesize,read_melectrotype,diffpeakvtg=0;
unsigned int read_tpreflow,read_tstartcurrent,read_tupslopetime,read_tsetcurrent,read_tendcurrent,read_tmaterial,
			read_tplatesize,read_tjointtype=0,read_gsetcurrent=0,read_tpostflow=0;
unsigned int read_gpreflow,read_gsetcurrent,read_gsetvoltage,read_gcratercurrent,read_gcratervoltage,
			 read_gburnback,read_gsetwspeed,read_gthickness,read_gpostflow,read_gmaterial,read_gdiameter,
			 read_ggas,read_inductance,pinductance=0xFFFF,read_gcratercurrent,read_gcratervoltag,
			 read_gthickness=0,prev_eeprom_mig_struct,prev_eeprom_tig_struct;						
			
unsigned int read_ppreflow,read_psetcurrent,read_psetvoltage,read_pcratercurrent,read_pcratervoltage,read_psetcurrent,
			 read_pburnback,read_psetwspeed,read_pthickness,read_parclength,read_ppostflow,read_pmaterial,read_pdiameter,
			 read_pgas,newpidstepbasetime=0,read_ptwinpulseratio=0,
			 read_pcreepspeedrate=0,read_ptwinpulseduty=0,read_ptwinpulsefreq=0,read_ppulseweldmode=0,prev_eeprom_pmig_struct;
			 
unsigned long Totalpulsepower=0,Peakpowerconstant=0,Steppowerconstant=0,Basepowerconstant=0,actpvtg=0,actpcount=0;
volatile unsigned int pulseoncnt=0,baseoncnt=0;
volatile unsigned char pulserefonf=0,baserefonf=0,startpcvloop=0;
unsigned long sumpulsevoltage=0,sumbasevoltage=0;
unsigned int pulsevoltagecnt=0,basevoltagecnt=0,msrpulseoncnt=0,msrbaseoncnt=0,
          msrpulsevtg=0,msrbasevtg=0,avgpulsevtg=0,dispavgpulsevtg=0,msrbpvtg=0,FRQbaseamp=0,FRQbasevtg=0,fbavgpulsevtg=0,prevavgpulsevtg=0;
int FRQ_sckscaled_val=0,PFREQ_sckscaled_val=0;
float peaktmfactor=0.0,basetmfactor=0.0,peakvtgpart=0.0,basevtgpart=0.0,PFREQ=0.0,PFREQERR=0.0;
float tmmsrpulseoncnt=0.0,tmmsrbaseoncnt=0.0,tmpeakvtg=0.0,tmbasevtg=0.0,flttmpeakvtg=0,prevtmpeakvtg=0;
unsigned int peakvtgarr[4],peakvtgarrcnt=0,avgpeakvtg=0;    	
volatile unsigned int mpulsevtgarr[16],mpulsevtgcnt=0,avgmpulsevtg=0,mpulsevtg=0,migdaccount=0;  
unsigned long sum_mpulsevtg=0;  
float target_bvtg=0;

volatile unsigned char msrpulsevtgf=0,power_on_flag=0;	
			 
int sf_setpoint;
int sf_feedback;
int sf_error,sf_neg_error;
//signed int sf_error;
int sf_preverror;
//signed int sf_preverror;

unsigned int pidvalue,mult_factor;

int Ts,scale_factor=0;
long integral_old=0;


int  sf_kpgain=200;//5;//2;
int  sf_kigain=10;//1;//2;
int  sf_kdgain=5;//2;
long fKi,fFd;
long sf_outputmax=25600;//32000;	//32,000
long sf_outputmin=0;		//-32,000
long sf_accumulator=0;
long sf_pid,sf_pterm=0,sf_iterm=0,sf_dterm=0;				//64,000
int  sf_scalefactor=7;     //2^7=128; 128*200=25600 ; max base current 200A
int  sf_mig_scalefactor=6;     //2^6=64; 64*800=51200 ; max base current 200A

volatile unsigned int sf_pidoutput=0,scaled_sf_pidoutput=0;

/*****************************GLCD VAriables Start************************************/
volatile unsigned int lcd_saverecall_ptr=0,save_location=1,Recall_location=1,prev_save_location=0,prev_Recall_location=0;
/*****************************GLCD VAriables End************************************/
unsigned char Testfg;
float Ti;

/***************debug variables***********************/
volatile unsigned int max_Pws,max_Gws;

/***************Error Code Variables**********/
volatile unsigned char mma_tig_error_latch=0,universal_error_flag=0,universal_error_latch=0;
volatile unsigned char UV_errorf=0,OV_errorf=0,TH_errorf=0,HS_errorf=0,comm_errorf=0,ERROR_4_errorf=0,pressure_error_flag=0,over_curr_error_flag=0;
volatile unsigned char motor_encoder_errorf=0,trip_adc_complet_flag=0,error4_flag,error_4_check4t;
unsigned char WireFeeder_errorf,Motor_OverLoad_errorf,Error_flag,err_dispfg;
volatile unsigned int er1,er2,er3,looperrorvtg=0,err11_delay_counter,dVal_press1,dVal_press0,cntsecond_er4,communication_time_out=0;;

/*********************Torch cycle **********************************/
volatile unsigned char weld_p_para_latch=0,setrefparaf_crater=0;
volatile unsigned int P_crater_current=0, G_crater_current=0,prevgcreepspeedrate=0;

/**************************************Arc On TImer***************************************************/
unsigned int prevhr=0; prevmin=0; prevsec=0,prev_arcontimehr,prev_arcontimemin,arc_on_reset_count=0,read_pmig_auto0_man1=0;
volatile unsigned char pmig_auto0_man1=0,prev_pmig_auto0_man1=0;

/**************************************Password***************************************************/
volatile unsigned int password_set_count=0,password=0;
volatile unsigned char passwod_set_flag=0,password_protection_enabled=0,lcd_update_password=0,prev_2t_4t_mode=0;
unsigned int set_password;
int temp_password;
unsigned int prevtpreflow=0,prevtstartcurrent,prevtupslopetime,prevtdownslopetime=0,prevtendcurrent=0,prevtpostflowtime=0;


/*************versa400*****tig**/
unsigned int read_tigmodepreflow=0,tig_twot_fourt=0,foot_1_normal_0=0,prev_foot_1_normal_0=0,tig_pulse1_normal0=0,prev_tig_pulse1_normal0=0,
read_tigmodestartcurrent=0,
read_tigmodeupslopetime=0,
read_tigdownslopetime=0,pwmresult,
read_tigmodeendcurrent=0,read_tigmodepostflow=0,
read_tig_twot_fourt=0,timerval_1ms,
time_100ms=0,Time_ms=0,footref_I,msec10_cntr,Upslope_cntr,Downslope_cntr,tig4tupslpbrkcurrent=0,read_foot_1_normal_0=0;

float UP_Step,Down_Step,Upcurrent,Downcurrent;

unsigned char tig_torch_relse_4t=0,cyclestart,dummytigtorch=0,tig_ocv_on_flag=0,torchreleasef=0,currerrf=0,upslopef=0,downslopef=0,TORCH_SW;

volatile unsigned int dVal_torch0=0,dVal_torch1=0;

volatile unsigned int tig_weld_cycle_current=0;

enum operation {tig_pre,tig_arcdet,tig_initI,tig_upslpe,tig_weld,tig_dwnslope,tig_endI,tig_post,tig_end}oper_tig;
 
/*unsigned int ADC_Volt,ADC_Current,ADC_Footsw,Disp_mesg_cntr=0,fbcuroff=0,footrefadc=0,fminoffset=0,fminoffset1=0,fmaxoffset1=0;
unsigned long Total_ADC_Volt=0,Total_ADC_Current=0,Total_ADC_Footsw=0;
unsigned int Actual_Volt=0,Avg_Footsw=0,Upslope_cntr=0,Downslope_cntr=0,msec10_cntr=0,Avg_Current=0,fmaxoffset;
volatile unsigned int Actual_Current=0,Actual_Footsw=0;
unsigned char channel=0,avgcnt0=0,avgcnt1=0,avgcnt2=0,offsetf=0,MODEL=0,offcnt=0,OR_FOOT_SW;
*/
//MAchine serial number 
unsigned char first_digits,second_digits,third_digits,fourth_digits;
//usb
unsigned char usb_0error_1ok=0,cPonCntr = 2,iCntChk,usb_start_fg=0;
unsigned char pon_usb_fg;
unsigned char load_data_into_usb_fg,HeaderWrfg ,usbDataLogStartfg;
unsigned char setPasswordfg,invalid_recall_fg;
unsigned int iSecCntr,iHeaderdly;
//unsigned char Integrator_ok;

unsigned char testmigfg;
unsigned int iTest,iTestpeak1,iTestpeak2,iTestpeak3, iPrevDacCnt;
unsigned char cSign1,cSign2,cSign3;
unsigned int samplecnt=0;

unsigned char gasChkfg,tig_ocv_check_f,ocvonfg,weld_short_tig_fg;
unsigned char chkLongkeyPressfg = 0;
unsigned int short_delay = 0, short_circuit_cnt_100ms= 0;
unsigned char longKeyPressfg = 0,cCableChkfg,cCableChkCntr,cCableErrorfg,cNofbVoltCnt;
unsigned int  iWeldcount;
unsigned char ChkForAnotherfg,cErrorNo,cFlashCnt,cFalshMsgfg,cOneSecfg;
unsigned int iFlashCntr;
long sf_accumulator_new;
unsigned char strRXFramefg,analogFramRxfg;
unsigned int iRXCntr;

unsigned char cPWstarblinkcnt,WfEditfg;
//------------------------
int fAcc,fPrevError;
//------------------------
unsigned char cAnRemoteFrameArr[10];
//---------------------------------------------
unsigned char cMIGMenumodelockfg,cGasChkMenufg,cStartGasChkcntfg,cTIGMenumodelockfg,ReferenceReadfg;
unsigned int iGasChkMenuModecnt,iGAScnt,count_gaschk_1ms,iMenuModecnt,count_gas_1sec,iResetcnt1;
unsigned char cMIGMenuMode,cMIGMenuOnfg,cTIGMenuMode,cTIGMenuOnfg,cEncupdatefg,cGaschkDowncntfg,cGASMenuMode;
unsigned char cMMAmenumodelockfg,cMMAMenuMode,cMMAparaupdatefg;
unsigned char keyfoundfg,remotekeyfoundfg,cRemoteCalfg;
unsigned char cArcOnfoundfg,cResetMenufg;
unsigned int iTimeResetSwitchcnt,iResetcnt1;
//unsigned int VRvtg,IRcurr,Setcurrent;

//--------------------------Remote-------------
static unsigned int long Total_AFRresult;
static unsigned int ADCRresult;
unsigned char cRemoteDetectedfg;
unsigned int iRemotecnt,iActualRemotecurr,iTest,iRemoteCurrcnt,iPrevSetcurrent,iPrevDisplaySetcurrent,iRemoteCheckcnt;
float fRemoteCheckCurr,fRemoteCurr,fOffset;

//-------------------------MMA MODE-------------------------------
unsigned char cMMA_TIG_setcurrentfg,cDispFBvtgfg,cArcforcefg;
unsigned char cHotfg,cArcForceTimefg,cAntistickfg,cFastUpdateFBvtg;

static unsigned int long Total_AFCWSCresult,Total_AFCVAFresult,Total_Moderesult;
static unsigned int long Total_AFINDHSresult,Total_SCKARCFVresult;

static unsigned int iArcforceCurrent,iArcForceTimeCnt,iHotstartCurrent,iHotstart,iArcforce;
static unsigned int ADCCWSCresult,AFCWSCcnt,iSetcurrent,AFCVAFcnt,ADCCVAFresult;
static unsigned int ADCINDHSresult,AFINDHScnt;
unsigned int DISPArcforcevtg,ADCARCFVresult;
unsigned int iHotstartcount,cnt200ms,cnt1sec,iArcforcecnt,iArcforceVtgcnt,ARCFORCEVOLTAGE;

//--------------------------TIG MODE--------------------------------
unsigned int cnt200ms_tig,cnt1sec_tig;
unsigned char cShortCktfg,cDispUpdatefg;

//--------------------------MIG MODE--------------------------------
static unsigned int long Total_AFVRresult,Total_AFIRresult,Total_SCKMresult;
static unsigned int ADCVRresult,ADCIRresult,AFVRcnt,AFIRcnt,VRvtg,ADCMresult,IRCreepcurr;
unsigned char cMig_arcdetectfg,torch,cMotorfg,cCreepSpeedDowncntfg;
unsigned int dValm_torch0=0,dValm_torch1=0;
unsigned int iMigOffset,iMigSlope,iDacCnt;
unsigned int mig_preflow,mig_burnback,mig_postflow,mig_creepspeedrate,mig_Kp,mig_Ki,mig_Kd;
int mig_Ka,mig_Kb,mig_Kc;
unsigned int iGasCntr,iMigWeldPara,iTemp,iMigWeldPara1,iMigWeldPara2,iMigWeldPara3,iMigWeldPara4,iMigWeldPara5,iMigWeldPara6,igascntr;
float fRef_pwm_new=0,fRef_pwm_new_result=0;
//static unsigned int long f_motorvtg,iPrevMotorvtg,fbmvtg,iResult_motorvtg;
static unsigned int iMotorvtg,iMotorcnt,iPrevMotor_pwm,newpwm,SCKmotor_vtg;
unsigned char cMigDACref,cMigWeldparaupdatefg;
static unsigned int iCraterWS,iCraterVtg,iInductance;
unsigned char cSwitchPressfg,cSwitchPressfg1,cSwitchPressfg2,cSwitchPressfg3,cSwitchPressfg4,cDebounce2;
unsigned int iDebounce1,iTestcntr,iMotorPIDcnt;
unsigned char cMIGWeldStartfg;
unsigned int iFBmotor_finalvtg;
unsigned int iRefmvtg,iPrevMotorvtg,iResult_motorvtg,iFBmvtg,iFBMotorvtg;

unsigned int Kp,Ki,Kd,Tsampling,ReferenceSetpoint,FeedbackSetpoint,scalefactor;


signed int error1,error_new,error_old,error_neg;


long integral_new,integral_old,pidoutmax,pidoutmin;
signed int outmax,outmin;
unsigned int PWM_Ref,DAC_Ref,iMIGParaMenucnt;
unsigned char cPWMLockfg,cTestWSLockfg,cGaSMenufg,cMIGMenufg,cForcefullyOFFOCVfg,cLock4TModefg;
unsigned int iPWMClosecnt,iCreepSpeedcnt,iActualWireSpeedcnt,iActualWS;
signed int iTest2;
float scaled_val,pidoutput,motor_integral_acc;
unsigned char cCreepEndfg,cUpdate4TModefg,cUpdate2TModefg,cUpdateModefg,cActualWireSpeedfg,c4Tstatus,cCreepDetectafterPreflowfg;
unsigned char cMotorStopfg,cTestMotorStopfg,cTorchStatus,cCreepKifg,cMIGParaMenufg,cMotorStopForENDPulsefg;
float fCalKp,fCalKi;
unsigned char cCreepLatchfg;
unsigned int read_gcreepspeedtime,mig_creepspeedtime,read_iOffset;
//--------------------------DAC--------------------------------------
unsigned char cDacoutfg,cLockDACreffg,cTestVtgLockfg;
unsigned int iConvertedDACRef,CUrrrent,iCreepSpeedDowncnt,iSlowIncrementWireSpeed;

//------------------------POT UPDATE---------------------------------------
unsigned char cEnDCurrUpdatefg,cRemoteEnDCurrUpdatefg;
unsigned int iPrevWireSpeed,IRcurr,iWireSpeed,iVoltage;

//-------------------------TRIP-----------------------------------------
unsigned int long Total_SCKE1result,Total_SCKE2result,Total_DISPT1result,Total_DISPT2result;
unsigned int ADCT1result,ADCT2result,iTrip1vtg,iTrip2vtg,DISPT1vtg,DISPT2vtg;

//------------------------FEEDBACK----------------------------------
static unsigned int long Total_AFFBAresult,Total_AFFBVresult;
static unsigned int AFFBAcnt,iFeedbackcurr,AFFBVcnt,iFeedbackvtg,ADCFBAresult,ADCFBVresult;
unsigned char cDispFBcurrfg,cWeldondetectfg,cWeldonfg;
unsigned int iWeldoncnt;
unsigned int adc16;
unsigned char Channel;
unsigned int iACT_CURRENT,Total_AvgCurr;
unsigned char cSoftStrfg,cSoftDonefg,cWaitToStopMtrfg;
unsigned int cSoftStrCnt,iWaitToStopMtrCnt;
unsigned int iPrevPidOutput;
unsigned int iPidCal,iDummyvoltageref;
unsigned char cTestfg;
unsigned char cStartPulsefg,cPulseCnt,cStartCCReffg;
unsigned char cPIDtriggerfg,cTorchPressFoundfg;
unsigned int iStartSetVoltCnt,iSimpleCnt,iStepforStartVoltRef,iSoftStrTimecnt;
unsigned int iMaxWSLimit;
unsigned char cWeldStartfg,cSoftStartUSecfg,cSoftStrTimefg;
unsigned int iStartCurr,iEndPulseCurr;
unsigned char cLoadFreqfg;
unsigned int iLoadFreqCntr;
unsigned char cLoadReffg,cKeychangefg;
unsigned int iLoadRefCntr,iPrevRef;
unsigned char cFrameSendfg,cEndPulsefg,cEndPulseCnt,cMainScreenfg,cCursorPosition,cSoftwireDetfg;
unsigned char cDispSetCurrUpdatefg,cCraterWSUpdatefg,cArcforceUpdatefg,cCraterVtgUpdatefg,cHotstartUpdatefg,
			  cInductanceUpdatefg,cMigVtgUpdatefg,cMIGWSUpdatefg,cCurrFBUpdatefg,cVtgFBUpdatefg,cVRDSwitchfg;
unsigned int inch_pwm,iSlope,iOffset,iMMASlope,iMMAOffset,vOffset;
unsigned char cCraterLatchfg,cInchLatchfg,cError4chkfg,cGasAndWeldParalockfg,cVoltoffMenuMode;
unsigned int iTest1,MIGCVSLOPE400;	
		  
//-------------------------MISCELLANEOUS-----------------------------
unsigned int iVRDSwitchcnt,iModeSwitchcnt,iVRD_Time,cGaschkcntr,iGascntr;
unsigned char cGaschkfg,cGasChkfg,gaschkfg,cBKeyLockfg,iPIDcntrfg;
float ftemp,fGndRes,fGndRes_WF;
unsigned int iPIDcntr;
float fSetCurrent,fCraterWS,fHotStart,fInductance,fArcForce,fCraterVtg;
unsigned char cVRD_fg,cVRDTimerSavefg,cRecordVRDONvtg,cMotorTripfg;
unsigned int ivrdcnt,iPrevVRDTime,ivrdcnt1,iVRD_Time;
unsigned int iActualVRDvtgON,iSampleVRDvtgcnt,VRDTimecnt_1s,iMotorTripcnt_100ms,iMotorTripChkcntr;
unsigned int cFlashCntr,count_3s,er4,er5,iTripcnt,iTRIPVTG1,iTRIPVTG2,iRemoteCurr;
unsigned char cFlashfg,NO_ERROR_CONNECTOR_fg,no_display_fg,cAKeyLockfg;  
unsigned char cVRDMenufg,cEEPROMSavefg,keyreadfg,cPowerONfg,cFirstTimefg;
unsigned int iVRDMenucnt,iPowerONcnt,iModeSelcnt;
long mma_vrd_time,iVRDTimecnt,read_mma_vrd_time;//,VRD_TIME_MAX;
unsigned int iErr1,iErr2;
unsigned char cModeSelectDonefg,cEnterModelSelectionMenufg,cModel_Select,cMaxFBCurrCalibrationfg,cModelSelectfg;
unsigned int iModelcnt,Moderesult;
unsigned int iModelSelectBand,eedata1,ACT_CVOLTAGE_1,AFtestcnt,iWireFeeder_error;
unsigned int mult_factor,mult_factor_1;
unsigned char cEEPROMModelSavefg,adctestreadfg,cDonefg,cVoltageoffsetfg;
unsigned int eedata2,eedata3,eedata4,eedata5,eedata6,eedata7,iWS_Min_Count,iWS_Max_Count,iVTG_Min_Count,iVTG_Max_Count,iFinal_WS_Count,iFinal_VTG_Count;
unsigned int long iAdccrateriref,padccrateriref,padccratervref,iAdccratervref;
unsigned int diff,iCraterdisptime;
unsigned char cCraterdispfg,cMenucnt,cVoltageoffsetmenufg;
unsigned int iRef_pwm_new_result=0,iGasChStopCnt=0;
unsigned char expon_lookup[]={20,20,20,20,20,20,20,20,21,21,21,22,22,22,
                                 23,23,23,24,24,24,25,25,25,26,26,26,
                                 27,27,27,28,28,28,29,29,29,30,30,30,31,31,31,
                                 32,32,32,33,33,33,34,34,34,35,35,35,36,36,36,37,37,37,
                                 38,38,38,39,39,39,40,40,40,41,41,41,42,42,42,43,43,
								 43,44,44,44,45,45,45,46,46,46,47,47,47,48,48,
								 48,49,49,49,50,50,50,51,51,51,52,52,52,
                                 53,53,53,54,54,54,55,55,55,56,56,56,57,57,57,
								 58,58,58,59,59,59,60,60,60,61,61,61,62,62,
                                 62,63,63,63,64,64,64,65,65,65,66,66,66,67,67,
								 67,68,68,68,69,69,69,70,70,70,71,71,71,72,72,72,
                                 73,73,73,74,74,74,75,75,75,76,76,76,77,77,77,78,
                                 78,78,79,79,79,80,80,80,81,81,81,82,82,82,83,
                                 83,83,84,84,84,85,85,85,86,86,86,87,87,87,88,
                                 88,88,89,89,89,90,90,90,91,91,91,92,92,92,
                                 93,93,93,94,94,94,95,95,95,96,96,96,97,97,97,98,
                                 98,98,99,99,99,100,100,100,101,101,101,102,102,102,

                                 103,103,103,104,104,104,105,105,105,106,106,106,107,107,107,
								 108,108,108,109,109,109,110,110,110,111,111,111,112,112,112,113,113,113,
								 114,114,114,115,115,115,115,116,116,116,117,117,117,118,
								 118,118,119,119,119,
								 
								 120,120,120,121,121,121,122,122,122,
                                 123,123,123,124,124,124,125,125,125,126,126,126,
                                 127,127,127,128,128,128,129,129,129,130,130,130,131,131,131,
                                 132,132,132,133,133,133,134,134,134,135,135,135,136,136,136,137,137,137,
                                 138,138,138,139,139,139,140,140,140,141,141,141,142,142,142,143,143,
								 143,144,144,144,145,145,145,146,146,146,147,147,147,148,148,
								 148,149,149,149,150,150,150,151,151,151,152,152,152,
                                 153,153,153,154,154,154,155,155,155,156,156,156,157,157,157,
								 158,158,158,159,159,159,160,160,160,161,161,161,162,162,
                                 162,163,163,163,164,164,164,165,165,165,166,166,166,167,167,
								 167,168,168,168,169,169,169,170,170,170,171,171,171,172,172,172,
                                 173,173,173,174,174,174,175,175,175,176,176,176,177,177,177,178,
                                 178,178,179,179,179,180,180,180,181,181,181,182,182,182,183,
                                 183,183,184,184,184,185,185,185,186,186,186,187,187,187,188,
                                 188,188,189,189,189,190,190,190,191,191,191,192,192,192,
                                 193,193,193,194,194,194,195,195,195,196,196,196,197,197,197,198,
                                 198,198,199,199,199,200,200,200,201,201,201,202,202,202,
                                 
                                 203,203,203,204,204,204,205,205,205,206,206,206,207,207,207,
								 208,208,208,209,209,209,210,210,210,211,211,211,212,212,212,213,213,213,
								 214,214,214,215,215,215,216,216,216,217,217,217,218,
								 218,218,219,219,219,220,220,220,221,222,221,222,222,222,
                                 
                                 223,223,223,224,224,224,225,225,225,226,226,226,
                                 227,227,227,228,228,228,229,229,229,230,230,230,231,231,231,
                                 232,232,232,233,233,233,234,234,234,235,235,235,236,236,236,237,237,237,
                                 238,238,238,239,239,239,240,240,240,240,240,241,241,241,

};
/*
unsigned char expon_lookup_1[301]=	{
	
140,141,142,143,144,145,146,147,148,149,150,
151,152,153,154,155,156,157,158,159,160,
161,162,163,164,165,166,167,168,169,170,
171,172,173,174,175,176,177,178,179,180,
181,182,183,184,185,186,187,188,189,190,
191,192,193,194,195,196,197,198,199,200,
201,202,203,204,205,206,207,208,209,210,
211,212,213,214,215,216,217,218,219,220,
221,222,223,224,225,226,227,228,229,230,
231,232,233,234,235,236,237,238,239,240,
241,242,243,244,245,246,247,248,249,250,
251,252,253,254,255,256,257,258,259,260,
261,262,263,264,265,266,267,268,269,270,
271,272,273,274,275,276,277,278,279,280,
281,282,283,284,285,286,287,288,289,290,
291,292,293,294,295,296,297,298,299,300,
301,302,303,304,305,306,307,308,309,310,
311,312,313,314,315,316,317,318,319,320,
321,322,323,324,325,326,327,328,329,330,
331,332,333,334,335,336,337,338,339,340,
341,342,343,344,345,346,347,348,349,350,
351,352,353,354,355,356,357,358,359,360,
361,362,363,364,365,366,367,368,369,370,
371,372,373,374,375,376,377,378,379,380,
381,382,383,384,385,386,387,388,389,390,
391,392,393,394,395,396,397,398,399,400,
                                 	
};
*/

const unsigned int Decay_lookup1[51]=
{
3683,
3494,
3315,
3145,
2983,
2830,
2684,
2546,
2414,
2290,
2172,
2059,
1953,
1852,
1756,
1664,
1578,
1496,
1418,
1343,
1273,
1206,
1143,
1083,
1026,
972,
920,
871,
825,
781,
739,
699,
662,
626,
592,
560,
529,
500,
472,
446,
421,
398,
375,
354,
334,
315,
297,
279,
263,
247,
233
};	

const unsigned int Decay_lookup2[51]=
{
3683,
3414,
3164,
2932,
2717,
2517,
2332,
2161,
2001,
1853,
1716,
1589,
1471,
1362,
1260,
1166,
1078,
997,
922,
852,
787,
727,
672,
620,
572,
527,
486,
448,
412,
379,
349,
320,
294,
270,
247,
226,
206,
188,
171,
156,
141,
128,
116,
104,
93,
83,
74,
66,
58,
50,
44
};
	
/*{
3677,
3467,
3268,
3082,
2905,
2739,
2582,
2434,
2294,
2162,
2037,
1920,
1809,
1705,
1606,
1513,
1425,
1342,
1264,
1190,
1120,
1055,
993,
934,
879,
827,
778,
731,
688,
646,
607,
571,
536,
503,
472,
443,
416,
390,
365,
342,
320,
300,
280,
262,
245,
228,
213,
199,
185,
172
};





const unsigned int Decay_lookup[21]=
{
	2811,
	2189,
	1704,
	1327,
	1033,
	805,
	627,
	488,
	380,
	296,
	230,
	179,
	140,
	109,
	85,
	66,
	51,
	40,
	31,
	24	
};	

const unsigned int Decay_lookup1[21]=
{
	3206,
	2843,
	2521,
	2235,
	1982,
	1758,
	1559,
	1382,
	1226,
	1087,
	964,
	855,
	758,
	672,
	596,
	529,
	469,
	416,
	369,
	327
};

const unsigned int sinramp_lookup[21]=
{
	3206,
	2843,
	2521,
	2235,
	1982,
	1758,
	1559,
	1382,
	1226,
	1087,
	964,
	855,
	758,
	672,
	596,
	529,
	469,
	416,
	369,
	327
};

//everywhere 1ms fix
const unsigned int sinefall_lookup[21]=
{
	3683,
	3661,
	3594,
	3482,
	3325,
	3139,
	2915,
	2662,
	2393,
	2110,
	1820,
	1529,
	1246,
	977,
	724,
	500,
	314,
	157,
	45,
	10
};

const unsigned int newexpo_lookup[31]=
{
	3414,
	3164,
	2932,
	2717,
	2518,
	2332,
	2161,
	2001,
	1854,
	1717,
	1589,
	1471,
	1362,
	1260,
	1166,
	1079,
	997,
	922,
	852,
	788,
	728,
	672,
	620,
	572,
	528,
	486,
	448,
	412,
	379,
	349
};
*/

#define 		ROWSIZE		4
#define			COLUMNSIZE	3

const unsigned char keyeqv[ROWSIZE][COLUMNSIZE]=	
														{	{'A','B','C'},
															{'D','E','F'},
															{'G','H','I'},
															{'J','K','L'}
														};

const unsigned int lookup_table[47][8]=
							{ //{a,b,c,d,e,f,g,d}
								{1,1,1,1,1,1,1,1},		//null character forword slash '/'
								{1,1,1,1,1,1,0,0},		//0
								{0,1,1,0,0,0,0,0},		//1
								{1,1,0,1,1,0,1,0},		//2
								{1,1,1,1,0,0,1,0},		//3
								{0,1,1,0,0,1,1,0},		//4
								{1,0,1,1,0,1,1,0},		//5
								{1,0,1,1,1,1,1,0},		//6	
								{1,1,1,0,0,0,0,0},		//7
								{1,1,1,1,1,1,1,0},		//8
								{1,1,1,1,0,1,1,0},		//9
								{1,1,1,1,1,1,0,0},		//3A
								{0,1,1,0,0,0,0,0},		//3B
								{1,1,0,1,1,0,1,0},		//3C
								{1,1,1,1,0,0,1,0},		//3D
								{0,1,1,0,0,1,1,0},		//3E
								{1,0,1,1,0,1,1,0},		//3F
								{1,0,1,1,1,1,1,0},		//41
								{1,1,1,0,1,1,1,0},		//A
								{0,0,1,1,1,1,1,0},		//B
								{1,0,0,1,1,1,0,0},		//C
								{0,1,1,1,1,0,1,0},		//D
								{1,0,0,1,1,1,1,0},		//E
								{1,0,0,0,1,1,1,0},		//F
								{1,0,1,1,1,1,0,0},		//G
								{0,1,1,0,1,1,1,0},		//H
								{0,1,1,0,0,0,0,0},		//I
								{0,1,1,1,1,0,0,0},		//J
								{0,0,0,0,1,1,1,0},		//K
								{0,0,0,1,1,1,0,0},		//L
								{1,0,1,0,1,0,1,0},		//M
								{0,0,1,0,1,0,1,0},		//N
								{0,0,1,1,1,0,1,0},		//O	
								{1,1,0,0,1,1,1,0},		//P
								{1,1,1,0,0,1,1,0},		//Q
								{0,0,0,0,1,0,1,0},		//R
								{1,0,1,1,0,1,1,0},		//S
								{0,0,0,1,1,1,1,0},		//T	
								{0,1,1,1,1,1,0,0},		//U
								{0,1,1,1,1,1,0,0},		//V
								{0,1,0,1,0,1,1,0},		//W
								{0,0,1,0,0,0,0,0},		//X
								{0,1,1,1,0,1,1,0},		//Y
								{1,0,0,1,0,0,1,0},		//Z
								{0,0,0,0,0,0,0,0},		//[ blank
								{0,0,0,0,0,0,1,0},		//-
								{0,0,0,0,0,0,1,0},		//]
							};
							    