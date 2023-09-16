
unsigned char disp_data_arr[4];

enum{mms=0,mss=1,mci=2}mmat;
enum{twoptfive=0,threepttwo=1,fourptzero=2,fiveptzero=3}mdia;
enum{sevenzero=0,sixzero=1,celwel=2,threezero=3,nicl=4}melectrode;	

const unsigned char ar11[]="SMAW/MMA MODE";
const unsigned char ar12[]="CURRENTXXX:XXXXXXAXX";
const unsigned char ar13[]="ARCFORCEXX:XXXXXX%XX";
const unsigned char ar14[]="OCVOFF>>PARA KEY";
const unsigned char ar15[]="XXXXXXXXXXXXXXXXXXXXXXXXXXX";


const unsigned char ar20[]="MSXXXXXX2.5XXXE7018X";

const unsigned char mmatms[] 	="MSX";//XXXXX1.2XXXXXARCO2";
const unsigned char mmatss[] 	="SSX";//XXXXX1.2XXXXXARCO2";
const unsigned char mmatci[] 	="CIX";//XXXX1.2XXXXXARCO2";

const unsigned char mdiatwoptfive[]		="2.5";//XXXXX1.2XXXXXARCO2";
const unsigned char mdiathreepttwo[]	="3.2";//XXXXX1.2XXXXXARCO2";
const unsigned char mdiafourptzero[]	="4.0";//XXXX1.2XXXXXARCO2";
const unsigned char mdiafiveptzero[]	="5.0";//XXXX1.2XXXXXARCO2";

const unsigned char msevenzero[]="E7018X";//XXXXX1.2XXXXXARCO2";
const unsigned char msixzero[]  ="E6013X";//XXXXX1.2XXXXXARCO2";
const unsigned char mcelwel[]   ="E6010X";//XXXX1.2XXXXXARCO2";
const unsigned char mthreezero[]="E308LX";//XXXXX1.2XXXXXARCO2";
const unsigned char mnicl[]  	="Ni-CLX";//XXXXX1.2XXXXXARCO2";

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$mig$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
enum{ms,ss,alu4043,alu5356,msfcaw,ssfcaw,sifcaw}mat;
enum{zeropteight,oneptzero,onepttwo,oneptsix,twoptzero}dia;
enum{arco2,co2,ar,aro2,dcen,dcep}gas;

const unsigned char ar81[]="EDIT PARAMETER";
const unsigned char ar82[]=" SAVE                                 LOC";
const unsigned char ar83[]=" RECALL                              LOC";
const unsigned char ar84[]="SAVING DATA";
const unsigned char ar85[]="RECALLING DATA";

const unsigned char ar86[]="Set Mode";
const unsigned char ar87[]="Arc On Time";

const unsigned char ar88[]="Set   Password:";
const unsigned char ar89[]="Enter Password:";

const unsigned char ar90[]="Save to USB:";

const unsigned char ar31[]="GMAW/MIG MODE";
const unsigned char ar32[]="CURRENTXXX:XXXXXXAXX";
const unsigned char ar33[]="VOLTAGEXXX:XXXXXXVXX";
const unsigned char ar34[]="MIG-PARAMETERS";

const unsigned char ar35[]="PREFLOWXXX:XXXXXXSEC";
const unsigned char ar36[]="BURNBACKXX:XXXXXXSEC";
const unsigned char ar37[]="POSTFLOWXX:XXXXXXSEC";
const unsigned char ar38[]="CRAT. CURXX:XXXXXXXAXX";
const unsigned char ar39[]="CRAT. VOLTX:XXXXXXXVXX";

const unsigned char ar40[]="MSXXXXXX1.2XXXXXCO2X";
const unsigned char ar45[]="SELF SHIELDED";


const unsigned char matms[]	="MSXXXXX";//XXXXX1.2XXXXXARCO2";
const unsigned char matss[]	="SSXXXXX";//XXXXX1.2XXXXXARCO2";
const unsigned char matalu[]="ALUXXXX";//XXXX1.2XXXXXARCO2";
const unsigned char matssfcaw[]="SSFCAWX";//XXXX1.2XXXXXARCO2";
const unsigned char matmsfcaw[]="MSFCAWX";//XXXX1.2XXXXXARCO2";

const unsigned char diazeropteight[]="0.8";//XXXXX1.2XXXXXARCO2";
const unsigned char diaoneptzero[]	="1.0";//XXXXX1.2XXXXXARCO2";
const unsigned char diaonepttwo[]	="1.2";//XXXX1.2XXXXXARCO2";
const unsigned char diaoneptsix[]	="1.6";//XXXX1.2XXXXXARCO2";

const unsigned char gasarco2[]	="ArCo2";//XXXXX1.2XXXXXARCO2";
const unsigned char gasco2[]  	="XCo2X";//XXXXX1.2XXXXXARCO2";
const unsigned char gastype1[]  ="(80+20)";
const unsigned char gastype2[]  ="(98+02)";
//const unsigned char gastype3[]  ="(100)";
const unsigned char gasaro2[] 	="Aro2X";//XXXX1.2XXXXXARCO2";
const unsigned char gasar[]   	="XArXX";//XXXX1.2XXXXXARCO2";

const unsigned char cMatMigTxt[][9] = 	{
											{"MSXXXXXX"},
											{"SSXXXXXX"},
											{"AL4043XX"},
											("AL5356XX"),											
											{"MSFCAWXX"},
											{"SSFCAWXX"},
											{"INSFCAWX"}																																	
									};
														
									
const unsigned char cDiaTxt[][6] = {
											{"0.8"},
											{"1.0"},
											{"1.2"},											
											{"1.6"},
											{"2.0"}																					
									};

const unsigned char cGasTxt[][6] = {
											{"ARCO2"},
											{"CO2XX"},
											{"ARXXX"},
											{"ARO2X"},
											{"DCENX"},	
											{"DCEPX"}																																
																					
									};
const unsigned char cGasPercent[][8] = {								
											{"(80+20)"},
											{"XXXXXXX"},
											{"XXXXXXX"},
											{"(98+02)"},
											{"XXXXXXX"},																																
											{"XXXXXXX"}											
										};					


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

//const unsigned char ar45[]="PREFLOWXXXXXX:";
//const unsigned char ar46[]="CRATERCURRENT:";
//const unsigned char ar47[]="CRATERVOLTAGE:";
//const unsigned char ar48[]="BURNBACK TIME:";
//const unsigned char ar49[]="POSTFLOWXXXXX:";

//const unsigned char ar51[]="WELDMODEXXXXX:";
//const unsigned char ar52[]="FREQUENCYXXXX:";
//const unsigned char ar53[]="DUTYXCYCLEXXX:";
//const unsigned char ar54[]="CURRENTXRATIO:";
//const unsigned char ar55[]="CREEPXSPEEDXX:";
//nst unsigned char ar35[]="PREFLOWXXX:XXXXXXSEC";

const unsigned char ar51[]="P-WELDMODEXX:SINGLEX";
const unsigned char ar52[]="FREQUENCYXXX:XXXXXHZ";
const unsigned char ar53[]="DUTYXCYCLEXX:XXXXX%X";
const unsigned char ar54[]="CURRENTRATIO:XXXXX%X";
const unsigned char ar55[]="CREEPSPEEDXX:XXXXX%X";

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
enum{tss=0,tdcu=1}tmat;
enum{toneptsix=0,ttwoptfour=1,tthreepttwo=2,tfourpteight=3,tsixptfour=4,ttwelvepteight=5}tdia;
enum{butt=0,lap=1,corner=2,fillet=3}tjoint;

const unsigned char ar21[]="GTAW/TIG MODE";
const unsigned char ar22[]="CURRENTXXXXXX:XXXXXA";
const unsigned char ar23[]="TUNGSTENXDIA.:XXXXmm";
const unsigned char ar30[]="SSXXXXXX1.6XXXXBUTTX";

  const unsigned char ar24[]="PREFLOWXXX:XXXXXXSEC";
  const unsigned char ar25[]="START CURX:XXXXXXAXX";
  const unsigned char ar26[]="UPSLOPEXXX:XXXXXXSEC";
  const unsigned char ar27[]="DOWNSLOPEX:XXXXXXSEC";
  const unsigned char ar28[]="END CURRXX:XXXXXXAXX";
  const unsigned char ar29[]="POSTXFLOWX:XXXXXXSEC";//@versa
  const unsigned char arFOOT[]="FOOT MODE  ";//@versa
  const unsigned char arNORM[]="NORMAL MODE";//@versa
  
const unsigned char tmatss[] 	="SSX";//XXXXX1.2XXXXXARCO2";
const unsigned char tmatdcu[] 	="DCu";//XXXX1.2XXXXXARCO2";

const unsigned char tdiaoneptsix[]		="1.6X";//1/16";//XXXXX1.2XXXXXARCO2"; //1.6mm
const unsigned char tdiatwoptfour[]	    ="2.4X";//3/32";//XXXXX1.2XXXXXARCO2"; //2.4mm
const unsigned char tdiathreepttwo[]	="3.2X";//1/8";//XXXX1.2XXXXXARCO2";   //3.2mm
const unsigned char tdiafourpteight[]	="4.8X";//3/16";//XXXX1.2XXXXXARCO2";  //4.8mm
const unsigned char tdiasixptfour[]	    ="6.4X";//1/4";//XXXX1.2XXXXXARCO2";   //6.4mm
const unsigned char tdiatwelvepteight[] ="12.8";//1/2";//XXXX1.2XXXXXARCO2";   //12.8mm

const unsigned char tbutt[]		="XBUTTX";//XXXXX1.2XXXXXARCO2";
const unsigned char tlap[]  	="XLAPXX";//XXXXX1.2XXXXXARCO2";
const unsigned char tcorner[]   ="CORNER";//XXXX1.2XXXXXARCO2";
const unsigned char tfillet[]	="FILLET";//XXXXX1.2XXXXXARCO2";





//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//enum{pms,pss,palu}pmat;
enum{pms,p71t1,p180r,pss18,pss19,palu4043,palu5356,palu99}pmat;
enum{pzeropteight,poneptzero,ponepttwo,poneptsix}pdia;
enum{pco2,parco2,paro2,par,}pgas;

const unsigned char ar41[]="PULSEMIG MODE";
const unsigned char ar42[]="CURRENTXXX:XXXXXXAXX";
const unsigned char ar43[]="VOLTAGEXXX:XXXXXXVXX";
const unsigned char ar44[]="PMIG-PARAMETERS";
const unsigned char ar50[]="MSXXXXXX1.2XXXArCO2X";

const unsigned char pmatms[]		="MSXXXXX";//XXXXX1.2XXXXXARCO2";
const unsigned char pmat71t1[]		="FCAWXXX";//XXXXX1.2XXXXXARCO2"; //MS71T1
const unsigned char pmat180r[]		="CORTENX";//XXXXX1.2XXXXXARCO2"; //WS180RX 
const unsigned char pmatss18[]		="SS18/8X";//XXXXX1.2XXXXXARCO2";
const unsigned char pmatss19[]		="DSSXXXX";//XXXXX1.2XXXXXARCO2";
const unsigned char pmatalu4043[]	="ALU+SIX";//XXXXX1.2XXXXXARCO2";
const unsigned char pmatalu5356[]	="ALU+MGX";//XXXX1.2XXXXXARCO2";
const unsigned char pmatalu99[]		="ALU99XX";//XXXXX1.2XXXXXARCO2";

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//const unsigned char ar0[]="ABCDEFGHIJKLMNOPQRST";
const unsigned char ar0[]="ADOR WELDING LTD PUNE";
const unsigned char ar1[]="INVERTER BASED";                 
const unsigned char ar2[]="CHAMP VERSA 400";
const unsigned char ar3[]="MMA-TIG-MIG";
               

/*
#ifdef VERSA400
const unsigned char ar3[]="MMA-TIG-MIG";
const unsigned char ar2[]="CHAMP VERSA 400";  
#else
const unsigned char ar3[]="MMA-TIG-MIG-PULSEMIG";
const unsigned char ar2[]="CHAMP PULSE 500";  
#endif
*/

/*
//unsigned char ar0[]="";
//unsigned char ar1[]="ENGINEERSGARAGE";
//unsigned char ar2[]="Inspiring Creations   ";                 
//unsigned char ar3[]="**************  ";
unsigned char ar4[]=" MATERIALX: MS  CV";
unsigned char ar5[]=" DIAMETERX:1.20    MM";
unsigned char ar6[]=" WIRESPEED:3.20   M/m";//  :  0.10    M/m";//unsigned char ar6[]=" WIRESPEED: 0.10 M/m";
//unsigned char ar4[]=" CURRENT :  0200   A      ";
//unsigned char ar5[]=" VOLTAGE :  15.0    V      ";
//unsigned char ar6[]=" SPEED       :  0.10    M/m";
unsigned char ar7[]=" UPXTIMEXX:01    SEC";
unsigned char ar8[]=" SAVE          :  01           LOC";
unsigned char ar9[]=" RECALL    :  01           LOC";
unsigned char ar10[]=" WIRE          :  2.50    MM";
unsigned char ar11[]=" SETUP MODEXXXXXXXXX";  //    :  1.00    MM";
unsigned char ar12[]=" M/C MODELXXXXXXXXXX";//     :  2.00    MM";

unsigned char ar13[]=" (W/F=4.0, CARR=0.0)";  //    :  1.00    MM";
unsigned char ar14[]=" (W/F=4.0, CARR=1.6)";  //    :  2.00    MM";
unsigned char ar15[]=" (W/F=3.0, CARR=0.0)";  //    :  1.00    MM";
unsigned char ar16[]=" (W/F=3.0, CARR=1.6)";  //    :  2.00    MM";

unsigned char ar24[]=" CURRENTXX:0200   A CC";
unsigned char ar25[]=" VOLTAGEXX:15.0    V";
unsigned char ar26[]=" CARRSPEED:0.10    M/m";
*/


const unsigned char cErrorMsgLine1[][13] = 	{
												{"UNDERVOLT"},
												{"OVER VOLT"},
												{"AL4043XX"},
												("AL5356XX"),
												{"MSFCAWXX"},
												{"SSFCAWXX"},
												{"INSFCAWX"},
												{"INSFCAWX"},												
											};
											
const unsigned char cErrorMsgLine2[][13] = 	{
												{"AAAAAAAA"},
												{"SSXXXXXX"},
												{"AL4043XX"},
												("AL5356XX"),
												{"MSFCAWXX"},
												{"SSFCAWXX"},
												{"INSFCAWX"},
												{"INSFCAWX"},
											};
const unsigned char cErrorMsgLine3[][13] = 	{
												{"AAAAAAAA"},
												{"SSXXXXXX"},
												{"AL4043XX"},
												("AL5356XX"),
												{"MSFCAWXX"},
												{"SSFCAWXX"},
												{"INSFCAWX"},
												{"INSFCAWX"},
											};											
											
																						