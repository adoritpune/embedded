static unsigned char trans_ps_wf_arr[20];

unsigned char tempkey=0,temp=0,ijk=0,disdigit=1,setdp=0,diswin1[3],diswin2[3],arr[8],firstpulse1=0,secondpulse1,plus111=0,result=0,minus111=0,new1=0,
firstpulse2=0,secondpulse2,plus222=0,minus222=0,new2=0,firstpulse3=0,secondpulse3,plus333=0,minus333=0,new3=0,scan_count=0,encod1=0,encod2=0,encod3=0,old1=0,old2=0,old3=0,
col=0,glcd_flag=0,key=0,ans=0,Prevkey=0,softstartf=0,weldmodeoff=0,setptimef=0,setstimef=0,openloopnew=0,Aweldonf=0,antistick_f=0;

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
float Tsampling=1.0,ARCLFACTOR=0.025,pidkp=0.0,pidki=0.0,pidkd=0.0;//0.03;
 
unsigned int disp_kiterm=0,constpeakamp=0,const_arc_strike_pdaccount=0,count_weldonms=0,delarcon11=0,prevFltbvtg=0,Fltbvtg=0,rel_wirespeed=0;
volatile unsigned char startbmeasuref=0,endbmeasuref=0,arcforceonf=0,trans2_onf=0,adcreadoverf=0,addafref=0,lcdpage=1;

unsigned int SUMSCKBVTGARR=0,SCKCNT=0,AVGBSCKVTG=0,SCKBVOLTAGE=0,id=0,jd=0,count_tx2_1ms=0,count_tx2=0,vtg_circular_arr[8],vtg_circular_cnt=0,ACT_CVOLTAGE=0;
unsigned char Shortcktf=0,wfchangef=0,stopbasef=0,firstpulsef=0,DISPavgf=0,SCKavgf=0,intkp = 30,intki = 1,intkd=0;
unsigned long totalsumbvtg=0,totalsumbcnt=0,newpulseduty=0,totalsumtrip=0;
unsigned int total_fltbvtg=0,Fltbvtgcnt=0,avg_fltbvtg=0,afbcurrent=0,setpidbamp=0,af_bdaccount=0,actual_fltbvtg=0;	
volatile int pidfactor=1,pulsestartcnt=0;
volatile unsigned long twinpulsefreq=1,twinpulseperiod=100,twinpulseduty=50,twinpulseratio=10,
			twinpulseonperiod=0,twinpulseoffperiod=0;	
static int error_old = 0,error_new=0,minoutputfreq=0,temp_mjp_vtg=0,arcforce_current=0,cvopenloopcnt=0;
static long integral_old= 0,integral_new=0,controller_out=0,integral_max=0,integral_min=0;
signed long scaled_val1=0,scaled_baseval=0;//,scaled_newval=0;
signed long minoutmax=0;	
float addrippleamp=0.1;			

unsigned int totaltempvtg=0,tempvtgcnt=0,avgtempvtg=0,mavgtempvtg=0,wirestickf=0,tempvtg=0,presumdaccount=0,ALEN_pulsefreq=0;	
static unsigned int ADCAresult=0,ADCVresult=0,ADCEresult=0,SCKTloopcnt=16,SCKTcnt=0;
static unsigned int DISPloopcnt=4096, DISPcnt=0,PULSEONOFFloopcnt=4,PULSEONOFFcnt=0;
static unsigned long Total_SCKAresult=0,Total_SCKVresult=0,Total_SCKEresult=0,Total_PULSEONOFFAresult=0;
static unsigned long Total_DISPAresult=0,Total_DISPVresult=0,Total_DISPEresult=0,Total_PULSEONOFFVresult=0,Total_AFVresult=0;
	
 volatile unsigned char error_tx_flag=0;
       
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
					   peakonf=0,Vweldon=0,mig_ocv_check_f=0;

volatile unsigned int decaycurrent=0,setbaseamp=0,count_100ms=0,prevwirespeed1=0,micromulti=0,PID_interval=0,
sckdaccount=0,count_key_5000ms=0;//,basevtgcnt=0;

unsigned int psetcurrent=0,psetvoltage=0,outputpulsebase=0,minbaseamp=0,maxbaseamp=0,presetcurrent=0,count4_1ms=0,DACREF=0;
signed int minbase=0,maxbase=0,maxpulsedutyterm=0,minpulsedutyterm=0,temperror1=0,temperror2=0;
//signed int temperror1=0,temperror2=0;
unsigned int wfspeed=0,presultcur=0,PCURRENT=0,padccur=0,addonbase=0,addonbase1=0,tx2data=0,pmigsetwirespeed=0xffff,pmigsetvoltage=0xffff;

volatile unsigned int baseunit=0,loopcount=0,loopinterval=0,count_1sec=0,uartdata1=0,uartdata2=0,MAHESH=0,microsec=0;  
unsigned char loadpara1=0,iii=0,chksum=0,startptr1=0,arrptr=0,recchksum=0,rec_arr[25],transmitonf=0,transonf=0,frepidf=0,weldcycleon=0;

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
	  			
unsigned int DISPamp=0,DISPvtg=0,DISPerr=0,SCKamp=0,SCKvtg=0,SCKerr=0,SCKVOLTAGE=0,sck_current_ref=0,temp_mjp=0,FLTSCKvtg=0,prevFLTSCKvtg=0,disp_newbaseamp=0;	  			
	  		 	
	  			
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
unsigned char displedptr2=disparcforce,ak47=0,emg_sendf=0,changestatusf=0,voltagechangef=0,OCVON_command=0,prev_OCVON_command=8,power_on_in_mma=0,power_on_in_tig=0,T_weldingonf=0,M_weldingonf=0;
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
unsigned int timerval=0, cntsecond=0,voltageref=0,fttrefvolt=0,cvoffsetref=0,prevpreflow=0xFFFF,prevburnback=0xFFFF,prevpostflow=0xFFFF,prevcratervoltage=0xFFFF,prevcraterspeed=0xFFFF,prevgcraterspeed=0xFFFF;
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
			read_tplatesize,read_tjointtype=0,read_gsetcurrent=0;
unsigned int read_gpreflow,read_gsetcurrent,read_gsetvoltage,read_gcratercurrent,read_gcratervoltage,
			 read_gburnback,read_gsetwspeed,read_gthickness,read_gpostflow,read_gmaterial,read_gdiameter,
			 read_ggas,read_inductance,pinductance=0xFFFF,read_gcratercurrent,read_gcratervoltag,
			 read_gthickness=0,prev_eeprom_mig_struct;						
			
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
int sf_error;
int sf_preverror;
;
int  sf_kpgain=200;//5;//2;
int  sf_kigain=10;//1;//2;
int  sf_kdgain=5;//2;
long sf_outputmax=25600;//32000;	//32,000
long sf_outputmin=0;		//-32,000
long sf_accumulator=0;
long sf_pid,sf_pterm=0,sf_iterm=0,sf_dterm=0;				//64,000
int  sf_scalefactor=7;     //2^7=128; 128*200=25600 ; max base current 200A
int  sf_mig_scalefactor=6;     //2^6=64; 64*800=51200 ; max base current 200A

volatile unsigned int sf_pidoutput=0,scaled_sf_pidoutput=0;
unsigned int mult_factor;
/*****************************GLCD VAriables Start************************************/
volatile unsigned int lcd_saverecall_ptr=0,save_location=1,Recall_location=1,prev_save_location=0,prev_Recall_location=0;
/*****************************GLCD VAriables End************************************/

/***************debug variables***********************/
volatile unsigned int max_Pws,max_Gws;

/***************Error Code Variables**********/
volatile unsigned char mma_tig_error_latch=0,universal_error_flag=0,universal_error_latch=0;
volatile unsigned char UV_errorf=0,OV_errorf=0,TH_errorf=0,HS_errorf=0,comm_errorf=0,ERROR_4_errorf=0,pressure_error_flag=0,over_curr_error_flag=0;
volatile unsigned char motor_encoder_errorf=0,trip_adc_complet_flag=0,error4_flag,error_4_check4t;

volatile unsigned int er1,er2,er3,looperrorvtg=0,err11_delay_counter,dVal_press1,dVal_press0,cntsecond_er4,communication_time_out=0;;

/*********************Torch cycle **********************************/
volatile unsigned char weld_p_para_latch=0,setrefparaf_crater=0;
volatile unsigned int P_crater_current=0, G_crater_current=0,prevgcreepspeedrate=0;

/**************************************Arc On TImer***************************************************/
unsigned int prevhr=0; prevmin=0; prevsec=0,prev_arcontimehr,prev_arcontimemin,arc_on_reset_count=0,read_pmig_auto0_man1=0;
volatile unsigned char pmig_auto0_man1=0,prev_pmig_auto0_man1=0;

/**************************************Password***************************************************/
volatile unsigned int password_set_count=0,password=0,set_password=0;

int temp_password=0;

volatile unsigned char passwod_set_flag=0,password_protection_enabled=0,lcd_update_password=0,prev_2t_4t_mode=0;
//-------------------------------------------------------------------------------------------------------------
unsigned char cEditfg,cTestfg,cWfVChangefg,iCntChk,setPasswordfg,cPWstarblinkcnt;
unsigned int iTest1,iTest2,iSampleCnt,iRxwfVoltage;
unsigned char cTestmmr[2];

unsigned char ChkForAnotherfg,ocvonfg;
unsigned char Testfg,WfEditfg;
unsigned int iCalHiFreq,iCalLowFreq;
unsigned char cLoadFreqfg;
unsigned int iLoadFreqCntr;

unsigned char cLoadReffg;
unsigned int iLoadRefCntr;
unsigned char cTogglePinfg;
unsigned int iTwinSetVolt,iTwinSetVolt2;
unsigned int iTwinwirespeed;
float fTwinwirespeed;
unsigned char cLoadVoltfg;
unsigned char cSoftStrfg,cSoftStrCnt,cSoftDonefg;
//---------------------

unsigned char cByte_cntr,cSlave_addr,cFunction_code,cNo_of_byte,cPort_addr,String_received_fg,cFrameStrfg,cFrameFoundfg,cChardlyStrfg;
unsigned char cParaUpdatefg;
unsigned char cCharDelay,cReceive_buffer[40],Response_array[40];
unsigned int iCrc_querry_word,sCRC_response_word,iInput_reg_addr,iPara_addr,iPara_update,iInput_data;

unsigned char cFrameSendfg,cEndPulsefg,cEndPulseCnt;
unsigned int ENPULSECURR;
unsigned int iFbVoltage,iFreqError;
unsigned char cFreqErrorupdatefg;

//-----I2C-EEPROM-------------------------------------------------------------------------------------------------------
unsigned int count_6ms,iWrAddr,ireadaddr,ireadmmry[];

unsigned char cE2p[8],cReadmat[7],cGasdia,cUpKeyLongPressfg,cMemoryScannerfg,ctogglefg,cProgramupdatefg,cUpdatenamefg;
unsigned int isaveaddr,iPno,iReadPno,iReadpara[3][24],iPulsepara[10],iProgramLoadLoc,iProgramStrLoc,prevProgramStrLoc,prevProgramLoadLoc;
unsigned int iFirstaddr,iSecondaddr,iUpKeyLongPresscnt,iProgramChkLoc,prevProgramChkLoc,iProgupdateptr,iProgRestoreLoc,prevprogrestoreLoc,iCursorptr;
unsigned int iPnoChk,iArrayindex,prevarrayindex,iDiaindex,prevdiaindex,iGasindex,prevgasindex,pulseptr,prevpulseptr,iPulseparachk[10];
unsigned char cProgramChk[6],cGasdiachk,cParachangeflag,cDnKeyLongPressfg;
unsigned int cDnKeyLongPresscnt;


unsigned int iThickChk,iMatChk,iGasChk,iPulseAddress = 2,iMigAddress = 201,iMigRootAddress=301,iProgramNo,iMigProgNo,iPercentagecnt=0,
					iProgramCnt=0;
unsigned char cWeldmode,cMatarray[10],cGasDiaupdate,cMatchFoundfg,ctoggleflag,cUpdatecursorfg,cPMainMenufg;
unsigned int iE2pData,iProNo = 1;
unsigned char cE2pData[2];//cDisplayGas,cDisplayDia,cDisplayMat[10];

//unsigned int itempo1,itempo2;

//unsigned int iPulsetmfactor,iPulseFreqFact,iPulsecurfactor,iPSetCurrent[27],iPSetBaseVoltage[27],iPThickness[27]
//			,iPulseParameter[15],iPProgramNo,iSfOutputMax;
//----------------------------------------------------------------------------------------------------------------------

unsigned int iKeyDoubleChkCntr,count200Msec;
unsigned char iMacMenuCntr,cCursorPosition,cLineNo,cSerialPortTask,cMacMenuNo;
unsigned char cMacMenufg,cKeyPressStartfg,cMainScreenfg,cCursorBlinkfg,cCursorOnfg,c200Msecfg,cCursorOfffg;
//--------------------------------------------
int __attribute__((address (STARTADDRESS + HMI_VOLATGE*2))) 	iVoltage;
int __attribute__((address (STARTADDRESS + HMI_WIRESPEED*2))) 	iWireSpeed;
int __attribute__((address (STARTADDRESS + HMI_CURRENT*2))) 	iCurrent;

int __attribute__((address (STARTADDRESS + HMI_DIA*2))) 		iDiaNo;
int __attribute__((address (STARTADDRESS + HMI_GAS*2))) 		iGasNo;
int __attribute__((address (STARTADDRESS + HMI_MAT*2))) 		iMatNo;
int __attribute__((address (STARTADDRESS + HMI_ARCLENGTH*2))) 	iArcLength;

int __attribute__((address (STARTADDRESS + HMI_ACT_CURRENT*2))) iActualCurrent;
int __attribute__((address (STARTADDRESS + HMI_ACT_VOLTAGE*2))) iActualVoltage;
//--------------------------------------------

//---------------------
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
								{0,0,1,0,0,0,0,0},		//I
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
							    