unsigned char temp=0,ijk=0,disdigit=1,arr[8],ucB_M_SEL=0,B_led=0;
unsigned int uiBatV=0;
unsigned char setdp=0;
unsigned char iDispcurr[4],iDispvolt[4];
unsigned int iTemp,iTemp2,count_1ms,count_3s;
unsigned char encod,old,firstpulse,secondpulse,new1,plus,minus,temp1,encoder;
unsigned int setcurrent,hotstart=0,Rsetcurrent;
unsigned char count_100ms=0,count2_100ms=0,pluspara=0,minuspara=0,psetcurrent=0,pluscount=0,minuscount=0,arcforce=0;
unsigned char memoryfg;
unsigned int iDacref;
unsigned char tfg,iCntChk;
unsigned int cnt1ms,cnt10ms,cnt_1s;
unsigned char cMemorybusyfg,cPrevmode,cMode;
unsigned char dacoutfg,dispvtgupdatefg,switchfg;
unsigned int stateButton1=0,prevstateButton=0,stateButton2,stateSwitch,prevstateSwitch;
unsigned char arcrstkeyfg=0,tempfg=0,arconkeyfg=0,arconrstfg=0,setarcdp=0,arconfg=0,arcrstfg=0,OCV_OFF=1,battery_switch=0;
unsigned int weldoncnt=0;
unsigned char channel = 11;
unsigned char high_byte=0,low_byte=0;
unsigned int adc=0,iCnt=0;
volatile unsigned int ADC_Volt,ADC_Current,Avg_Current;
volatile unsigned int Total_ADC_Volt=0,Total_ADC_Current=0;
unsigned char adc_vcnt=0,adc_ccnt=0;
volatile unsigned int VOLTAGE=0,CURRENT=0;
unsigned int daccount=0,iHotStartdaccount=0,iArcforcedaccount=0;
unsigned int arconrstcnt=0,rstcnt=0,timecnt=0,count1_100ms=0;
volatile unsigned int min=0,sec=0,hr=0;
unsigned char cMode,cArcforceMode,cHotstartMode,cDisplayfg,cPrevmode,cDisplaylockfg,cReleasefg,cModechangefg,cSkipfg, ARCFORCE_LEDLAT ;
unsigned int iHotStrRePresscnt,iHotfg=0;
unsigned char cFlashMenufg, cHotStrRePressfg,Read_ADC_fg;
unsigned char cEncupdatefg,iResetfg,iArconDispfg;
unsigned int iHotstartcnt,iHotstart=0,iArcforce=0,ADC_BUF,iRemote,iData,iADCcnt,iEncoderdbcnt,iSkipcnt; 
unsigned int iVolt,iCurr,iTripVolt,iTripVolt1,iVolt1;
unsigned char MMA_WELD_ON=0,TIG_WELD_ON=0;
unsigned int hotstartcount=0,iResetcnt=0,iArconDiscnt=0,iModeSwitchcnt=0,iTimeResetcnt=0;
unsigned int memdata=0,memdatacurr,memdatarcf,memdatahot,memdatamode,memdataswitchselcnt,memdataswitchsel;
unsigned char memorypara[6];
unsigned char readpara[6];
volatile  unsigned int d=0;
unsigned int cnt1ms,delaymsec,remotedispcnt=0,cnt100ms;
unsigned char weldonfg=0,Display_updatefg,Error_flag,dispfg;
unsigned int prevsetcurrent=0,weldvoltage=0,weldcurrent=0,prevweldcurrent=0,prevweldvoltage=0,iHotstartCurrent=0,iArcforceCurrent=0;
unsigned int iSamplecnt,tripvoltage=0,iRemotecurr=0,tripvoltage1=0;
unsigned char UV_ERR_fg,OV_ERR_fg,TH_ERR_fg,LP_ERR_fg,OCV_ERR_fg,NO_CN9_CONNECTOR_ERR_fg;
unsigned char testdisplayfg,AFcurrcnt=0,AFtripvtgcnt=0,AFtripvtgcnt1=0;
unsigned int AFvtgcnt=0,AFvtgcnt1=0,AFremotecnt=0;
unsigned char adcremotecurrreadfg,adcfeedbackcurrfg,adcfeedbackvtgfg;
unsigned int iActualcurr=0,iActualtripvolt=0,iActualtripvolt1=0;
unsigned int iActualvolt,iRemoteoffset,iActualRemotecurr1,iActualRemotecurr2,iActualvolt1;
unsigned int long AFremotecurr,AFvtg,AFcurr,AFtripvtg,AFtripvtg1,AFvtg1;
unsigned char antistickfg,dispcurrfg,dispvtgfg,iRemotefg,premotesetcurrent=0,disptripvtgfg;
unsigned int cnt200ms=0,cnt1sec=0;
unsigned char prevsec=0,prevmin=0,prevhr=0;
unsigned int iArcForceTimeCnt,default_setcurrent,default_cModel;
unsigned char cEnDCurrUpdatefg,cArcForceUpdatefg,cHotStartUpdatefg,cRemoteEnDCurrUpdatefg,cEnDCurrfg;
unsigned char c10Msecfg,SwitchModefg,c100Msecfg;
unsigned char cArcForceOnfg,cSkipHotfg,cHotstartmenufg,cSwitchmodefg;
unsigned int iRockerORtactileSwitchcnt,iModeSelection;
unsigned char cForSwitchSelectionfg,cForSwitchSelectionMode,cSkipModefg,count3_100ms=0,cModel,cTest=0,cFlashMenuSWfg;
unsigned int tem1=1,SwitchMode;
unsigned int tem2=1,tem3=1;
unsigned char cSkipTRfg,cResetRePressfg,cFlashTRMenufg,cArcOnMode,cResetMode,ArcOnMenuMode,cReset=0,cResetDecide,cArcOnfoundfg;
unsigned char MenuMode,keyfoundfg,Switchkeyfoundfg,SwitchMenuMode,Display_EnDUpdatefg;
unsigned char err_dispfg=0;
volatile unsigned int er1,er2,er3,er4;
unsigned char cErrorFlashfg,cFlashfg;
unsigned int cFlashCntr,iEncodercnt,iRemoteoffset1;
unsigned char no_connector_fg;
unsigned char cOffsetSavefg,cRemoteCalfg;
unsigned int iPerCentage,iOffsetDiv;
unsigned char cRemoteOnfg;
unsigned char RemoteOffsetMenu,remotekeyfoundfg,cRemotemaxoffsetfg,cRemoteMenufg,cRemoteoffsetmaxmode,cRemoteoffsetminmode;
unsigned int iPOndelay;
unsigned int iPrevSetcurrent;
unsigned int iRemoteoffsetmin,iRemoteoffsetmax,iActualRemotecurr;
unsigned int iRemoteoffCal;
unsigned int iPrevsetcurrent,iPrevMode,iPrevHotstart,iPrevArcforce;
unsigned char cModeLatchfg;
unsigned int remotecurr;
unsigned char cVRD_sel=0,cVRD_mode,cVRD_fg,cVRDTimerSavefg,cnt3fg,cRecordVRDONvtg;
unsigned int ivrdcnt,iPrevVRDTime,ivrdcnt1,iVRD_Time;
unsigned int iActualVRDvtgON,iSampleVRDvtgcnt,VRDTimecnt_1s;
unsigned char cEditfg;
unsigned char cModel_Select=2,ModelMenuMode,menukeyfoundfg,MainMenuMode=0,secondmenukeyfoundfg;
unsigned int temp3,tem4=1,model_setcurrent;
unsigned char cTest1,cEncoderPressDetectfg;
unsigned char cCommonEnDUpdatefg,cMenudata_changefg;
unsigned int iMenudata_no_change_cnt,iMenudata_no_change_cntt;
unsigned int iRemotecnt,iRemotecnt1;
unsigned char cBypass_Menudata_no_change_cnt_fg;
float fOffset,fOffsetpart_600,fOffset1;
float fGndRes,ftemp,ftest1,fremotecurr;
unsigned int iGndRes,count_10Ms,cnt_10ms,cnt_10s;
unsigned int iBLEHotStart=0,iBLEArcForce=0;
unsigned int iPotSetcurrent,ASetcurrentcnt,iDispSetcurrent,iPotArcForce,AArcForcecnt,iDispArcForce,iPotHotStart,AHotStartcnt,iDispHotStart;
unsigned int long ASetcurrent,AArcForce,AHotStart,ASetBand;
unsigned char cModelSelectfg,cSwitchSelectionfg,cGoToModelSelectionfg,cSaveModelfg,cModelReadfg,cTestfg=0,ctestfg;
unsigned char cSaveModel1fg,cSaveModel2fg,cSaveModel3fg,cModel_CurrSelect1,cModel_CurrSelect2,cAlreadyModelSelectedfg=0,cModel_CurrSelect3;
unsigned int iVRDSwitchcnt,iModelSelectBand;
unsigned char cCheckPinStatefg,cPrevModel,cDefaultMemoryReadfg,cSETResetfg;
unsigned char cModeSelectDonefg,cRemoteDetectedfg=0,cDisplayDetectedfg,dispDisplaycurrupdatefg,dispRemotecurrupdatefg;
unsigned int iPrevDisplaySetcurrent,iRemoteCheckcnt,cFlashResetcntr,iPrevDisplayUARTSetcurrent;
unsigned char cResetfg,cResetdonefg,cMeasureARCOnTimefg,cLongPressResetfg,cResetMenufg;
unsigned int iPrevsec,iPrevmin,iPrevhr,iPotBand,iPotBandcnt,iTimeResetSwitchcnt,iResetcnt1,cFlashResetfg,iEnterResetMenucnt;
float ftemp_disp,fGndRes_disp;
unsigned int iOffsetBand,iMAXFBCurrOffset,iSlope,iOffsetBand1,iMINFBCurrOffset;
unsigned char cMaxFBCurrCalibrationfg,cOffsetCalifg,cCaliCurrfg,cSetcurrentfg;
unsigned char reccnt,creceivefg,recstrtptr,rec_arr[10];
unsigned char ctranschksum,crecchksum,csendtoremotefg,count_10ms,cDigitalremoteDetectfg,model,cDigitalFramRxfg;
unsigned int reclower,rechigher,recremotevtg,recremotecurr,sendcur,sendvtg,iUARTRemotecurr;
char uartdata=0;
unsigned char cRemoteSetcurrentfg;
unsigned int cDigitalRXMonitorcnt,count_1s,iDigiRXmaxcurrmax,iDigiRXmaxcurrmin,iPrevRemoteCurr,RSetcurrent;
signed int iOFFSET_TERM_400,iOFFSET_TERM_600;
float fOFFSET_MID_400,fOFFSET_MID_600,fSLOPE_MID_400,fOFFSET_MID_400_MIN,fOFFSET_MID_600_MIN,fOFFSET_TERM_600;
unsigned char cVRDCountSettingfg,cDispVRDcountfg,cVRDCntSavefg,cCaliDetectfg,cDispSetcurrentfg,cVRDcntDispf=0;
unsigned int iSetVRD_Time,iVRDCount,memdatavrdcnt,iVRDCount2;
unsigned char cPowerONfg,cMinFBCurrCalibrationfg;
unsigned int iPowerONcnt , cDispFBCurrCalifg,iDispFBCurrCaliCount,cCaliDispFBCurrfg;
float fSLOPE_400,fSLOPE1,fDispArcForce;
unsigned int MMASLOPE_400,iMaxCurrent,x,icalibrationfg=0,ivrdcalibrationfg=0,ivrdledfg=1;
unsigned long int iDispArcForce1;
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

void USART_initialize(void);
void TRANS1(unsigned char data);
void TRANSNUM(unsigned int iTemp);
 void TRANSNUM2(unsigned int iTemp2);
unsigned char Rx1Receive=0,ucRXFlag=0,ucInitCMD=0,ucCMDSEND=0,ucBlutoothInit=0,i=0;
unsigned char RxReceive=0,Rx2Receive=0,ucRx2Flag=0,bit7=0,bit4=0,j=0,ucIDcnt=0;;
unsigned int uiBRSetCurr=0;
unsigned int uiBCnt=0;
void Bluetooth_Init(void);
unsigned char AT[]="AT\r\n";   //0XD, 0X0A
unsigned char BLENAME_R[]="AT+BLENAME?\r\n";
unsigned char BLENAME_S[]="AT+BLENAME=ADOR\r\n";
unsigned char BLEMODE_R[]="AT+BLEMODE?\r\n";
unsigned char BLEMODE_S[]="AT+BLEMODE=0\r\n";
unsigned char TRANSENTER[]="AT+TRANSENTER\r\n";
unsigned char CMDMODE[]="+++";
unsigned char ucState=0,ucCount=0,ucDataSend=0,ucBLE_CON_DIS=0;
unsigned char ucState1=0,ucCount1=0,ucDataSend1=0,ucBLE_CON_DIS1=0;
unsigned char ucSetCur[3]={0};
unsigned int  SendBuff[10]={0};
unsigned char  SendBuff2[4]={0};
unsigned char BLE_CONDIS[]={0};
unsigned char TimeBuf[3]={0};
unsigned char Temp[10];
unsigned int uiBPer=0,uiBTemp=0;














