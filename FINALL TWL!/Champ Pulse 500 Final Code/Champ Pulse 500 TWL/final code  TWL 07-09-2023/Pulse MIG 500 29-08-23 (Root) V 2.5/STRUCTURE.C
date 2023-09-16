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


struct Type_S
{
	unsigned char wirespeed	:1;
	unsigned char current		:1;
	unsigned char thickness	:1;
	unsigned char job	 		:1;
	unsigned char arcforce		:1;
	unsigned char voltage	  	:1;
	unsigned char arclength	:1;	
	unsigned char time  		:1;//1TypeU.LEDGROUP[1]
	
	unsigned char mma			:1;
	unsigned char tig	  		:1;
	unsigned char mig			:1;
	unsigned char pulsemig		:1;
	unsigned char twot			:1;//  **************************************downslope	:1;
	unsigned char fourt		:1;
	unsigned char extra1		:1;	
	unsigned char extra2		:1; //2TypeU.LEDGROUP[2]

	unsigned char ampa		:1;
	unsigned char ampb		:1;
	unsigned char ampc		:1;
	unsigned char ampd		:1;
	unsigned char ampe		:1;
	unsigned char ampf		:1;
	unsigned char ampg		:1;
	unsigned char amph		:1;//3TypeU.LEDGROUP[3]

	unsigned char volta		:1;
	unsigned char voltb 		:1;
	unsigned char voltc		:1;
	unsigned char voltd		:1;
	unsigned char volte		:1;
	unsigned char voltf			:1;
	unsigned char voltg		:1;
	unsigned char volth		:1;	//4TypeU.LEDGROUP[4]
};
union Type_U
{
	struct Type_S TypeS;
	unsigned char LEDGROUP[4];
};

union 	Type_U TypeU;
#define Type	TypeU.TypeS

//*******************************************************************************************************************************
struct para_s
{
	unsigned int dummy;							//0000
	struct		// prog = 0
	{
		unsigned int hotstart;					//0001
		unsigned int setcurrent;				//0002
		unsigned int arcforce;					//0003
		unsigned int mmaterial;					//0004
		unsigned int melectrodesize;			//0005
		unsigned int melectrotype;				//0006
	}
	mmamode;
	struct		// prog = 1
	{
		unsigned int preflow;					//0007
		unsigned int startcurrent;				//0008
		unsigned int upslopetime;				//0009
		unsigned int setcurrent;				//0010
		unsigned int endcurrent;				//0011
		unsigned int tmaterial;					//0012
		unsigned int tplatesize;				//0013		-----added
		unsigned int tjointtype;				//0014		-----added
	}
	tigmode;
	struct		// prog = 1
	{
		unsigned int preflow;					//0015
		unsigned int setcurrent;				//0016
		unsigned int setvoltage;				//0017
		unsigned int craterspeed;				//0018
		unsigned int cratervoltage;				//0019
		unsigned int burnback;					//0020
		unsigned int setwspeed;					//0021
		unsigned int thickness;					//0022
		unsigned int postflow;					//0023
		unsigned int gmaterial;					//0024-----added
		unsigned int gdiameter;					//0025-----added
		unsigned int ggas;						//0026-----added
		unsigned int inductance;				//0027----------------added
	 }
	migmode;
	struct		// prog = 1
	{
		unsigned int preflow;					//0028
		unsigned int setcurrent;				//0029
		unsigned int setvoltage;				//0030
		unsigned int craterspeed;				//0031
		unsigned int cratervoltage;				//0032
		unsigned int burnback;					//0033
		unsigned int setwspeed;				    //0034
		unsigned int thickness;					//0035
		unsigned int arclength;					//0036
		unsigned int postflow;					//0037
		unsigned int pmaterial;					//0038
		unsigned int pdiameter;					//0039 3
		unsigned int pgas;						//0040 3------added
	}
	pmigmode;
	
	unsigned char 	ledgp1;						//0041 4 	(lower byte)
	unsigned char 	ledgp2;						//0041 4 	(higher byte)
	unsigned char 	ledgp3;						//0042 5 	(lower byte)
	unsigned char 	ledgp4;						//0042 5 	(higher byte)
	unsigned char 	material;					//0043 6
	unsigned char 	diameter;					//0043 6
	unsigned char 	gas;						//0044 7
	unsigned char 	program;					//0044 7
	unsigned char 	weldmode;					//0045 8
	unsigned char 	extra8;						//0045 8
		
	unsigned int 	pulseweldmode;				//0046 39
	unsigned int 	twinpulsefreq;				//0047 0
	unsigned int 	twinpulseduty;				//0048 1
	unsigned int 	twinpulseratio;				//0049 2
	unsigned int 	creepspeedrate;				//0050 3  //for mig
	
	unsigned int 	pcreepspeedrate;			//0051 4
	unsigned int 	currentlow;					//0052 5
	unsigned int 	extra16;					//0053 6
	unsigned int 	extra17;					//0054 7
	unsigned int 	extra18;					//0055 8
};

union para_u
{
	struct para_s paras;
	unsigned int arrayu[56];//[55];//54];//51];//49  //48];    
};

union para_u 	parau;
#define para 	parau.paras

union para_u para_tempu;
union para_u const para_minu = {	
									0,			//dummy						//0000
									0,			//hotstart;					//0001
									15,			//setcurrent;				//0002
									0,			//arcforce;					//0003
									0,			//mmaterial					//0004
									0,			//melctrodesize;			//0005
									0,			//melectrotype				//0006
																	
									0,			//preflow;					//0007  // changed to 0 on 05102019
									0,			//startcurrent;				//0008
									0,			//upslopetime;				//0009
									15,			//setcurrent;				//0010
									0,			//endcurrent;				//0011
									0,			//tmaterial;				//0012
									0,			//tplatesize;				//0013
									0,			//tjointtype;				//0014
									
									0,			//preflow;					//0015
									30,			//setcurrent;				//0016
									100,		//setvoltage;				//0017
									20,			//@crater speed   			//0018
									140,		//cratervoltage;			//0019
									0,			//burnback;					//0020
									10,			//setwspeed;				//0021						//changed on 20012021
									0,			//thickness;				//0022
									0,			//postflow;					//0023
									0,			//gmaterial					//0024----added
									0,			//gdiameter					//0025----added
									0,			//ggas						//0026----addded
									0,			//INDUCTANCE				//0027--------------added
									
									0,			//preflow;					//0028
									30,			//setcurrent;				//0029
									100,		//setvoltage;				//0030
									50,			//cratercurrent;			//0031
									140,			//cratervoltage;			//0032
									0,			//burnback;					//0033
									10,			//setwspeed;				//0034
									0,			//thickness;				//0035
									0,			//arclength;				//0036
									0,			//postflow;					//0037
									0,			//pmaterial;				//0038
									0,			//pdiameter;				//0039
									0,			//pgas						//0040----addded
										
									0,			//ledgp1;					//0041 4 	(lower byte)
									0,			//ledgp2;					//0041 4 	(higher byte)
									0,			//ledgp3;					//0042 5 	(lower byte)
									0,			//ledgp4;					//0042 5 	(higher byte)
									0,			//material;					//0043 6
									0,			//diameter;					//0043 6
									0,			//gas;						//0044 7
									0,			//program;					//0044 7
									0,			//weldmode;					//0045 8
									0,			//extra1;					//0045 8
									
									0,			//Pulseweldmode				//0046 39
									1,			//Twinpulsefreq 			//0047 0
									10,			//Twinpulseduty				//0048 1
									0,			//Twinpulseratio			//0049 2
									20,			//MIG Creepspeedrate		//0050 3
									
									20,			//Pulse Mig Creepspeedrate;	//0051 4
									0,			//currentlow;					//0052 5
									0,			//extra8;					//0053 6
									0,			//extra9;					//0054 7
									0			//extraa;					//0055 8
								};								
	
				
union para_u const para_maxu = {	
									0,				//Dummy					//0000
									100,			//hotstart;				//0001
									500,			//setcurrent;			//0002
									100,			//arcforce;				//0003
									2,				//mmaterial 			//0004
									3,				//melctrodesize;		//0005
									4,				//melectrotype;			//0006
																	
									10,				//preflow;				//0007
									500,			//startcurrent;			//0008
									10,				//upslopetime;			//0009
									500,			//setcurrent;			//0010
									500,			//endcurrent;			//0011
									1,				//tmaterial;			//0012
									5,				//tplatesize;			//0013
									3,				//tjointtype;			//0014
																		
									10,				//preflow;				//0015
									500,			//setcurrent;			//0016
									440,			//setvoltage;			//0017
									220,			//@L Crater speed  ;	//0018
									440,			//cratervoltage;		//0019
									500,				//burnback;				//0020
									220,			//setwspeed;			//0021
									100,			//thickness;			//0022
									20,				//postflow;				//0023
									0,				//gmaterial				//0024----added
									0,				//gdiameter				//0025----added
									0,				//ggas					//0026----addded
									40,				//inductance			//0027-----------added
																	
									10,				//preflow;				//0028
									500,			//setcurrent;			//0029
									440,			//setvoltage;			//0030
									500,			//cratercurrent;		//0031
									440,			//cratervoltage;		//0032
									500,				//burnback;				//0033
									220,			//setwspeed;			//0034
									100,			//thickness;			//0035
									80,             //20,				//arclength;			//0036
									20,				//postflow;				//0037
									0,				//pmaterial;			//0038
									0,				//pdia;					//0039
									0,				//pgas					//0040----addded
									
									0,				//ledgp1;				//0041 4 	(lower byte)
									0,				//ledgp2;				//0041 4 	(higher byte)
									0,				//ledgp3;				//0042 5 	(lower byte)
									0,				//ledgp4;				//0042 5 	(higher byte)
									10,				//material;				//0043 6
									10,				//diameter;				//0043 6
									10,				//gas;					//0044 7
									100,			//program;				//0044 7
									10,				//weldmode;				//0045 8
									0,				//extra1;				//0045 8
									
									1,				//Pulseweldmode			//0046 39
									100,			//Twinpulsefreq 		//0047 0
									90,	     		//Twinpulseduty			//0048 1
									300, 			//Twinpulseratio		//0049 2
									100, 	   		//Creepspeedrate		//0050 3
									
									100,			//extra6;				//0051 4
									99,				//currentlow;				//0052 5
									0,				//extra8;				//0053 6
									0,				//extra9;				//0054 7
									0				//extraa;				//0055 8
								};				

#define mini 	para_minu.paras
#define maxi 	para_maxu.paras

//********************************************************************************************************************************
///*struct para_s
//{
//	unsigned int dummy;						//0000
//	struct		// prog = 0
//	{
//		unsigned int time;						//0001
//	}
//	preflow;
//	struct		// prog = 1
//	{
//		unsigned int startcur					//0002
//		unsigned int time;						//0003
//	}
//	upslope;
//	struct		// prog = 2
//	{
//		unsigned int wfs;						//0004
//		unsigned int amp;						//0005
//		unsigned int thickness;					//0006
//		unsigned int memloc;					//0007
//		unsigned int arcforce;					//0008		
//		unsigned int volts;						//0009
//		unsigned int arclength;					//0010
//		unsigned int time;						//0011
//	}
//	weld;
//	struct		// prog = 3
//	{
//		unsigned int endcur					//0002
//		unsigned int time;						//0012
//	}
//	dnslope;
//	struct		// prog = 4
//	{
//		unsigned int wfs;						//0009
//		unsigned int amp;						//0009
//		unsigned int volts;						//0009
//	}
//	crater;
//	struct		// prog = 5
//	{
//		unsigned int time;						//0017
//	}
//	burnback;
//	struct		// prog = 6
//	{
//		unsigned int time;						//0018
//	}
//	postflow;
//	unsigned int 	spottime;					//0019
//	unsigned int 	pausetime;					//0020
//	unsigned int 	pwmtime;					//0021  (for wire speed)
//	unsigned char 	ledgp1;						//0022 	(lower byte)
//	unsigned char 	ledgp2;						//0022 	(higher byte)
//	unsigned char 	ledgp3;						//0023 	(lower byte)
//	unsigned char 	ledgp4;						//0023 	(higher byte)
//	unsigned char 	ledgp5;						//0024	(lower byte)
//	unsigned char 	passprotect1;			    	//0024	(higher byte)
//	unsigned int    password1;	                		//0025	//location for current multiplier
//	unsigned int  	migws;     					//0026 	passprotect1;					
//	unsigned char 	spottimef;					//0027	(lower byte)	
//	unsigned char 	pausetimef;					//0027	(higher byte)
//	unsigned char 	burnbackf;					//0028	(lower byte)
//	unsigned char 	postflowf;					//0028	(higher byte)
//	unsigned int  	weldcurrent;				//0029
//	unsigned int  	weldarcforce;				//0030
//	unsigned int  	pwmtime1;   				//0031	//for voltage or current encoder
//	unsigned int  	fcawws;					//0032	//currmult;						
//};
//union para_u
//{
//	struct para_s paras;
//	unsigned int arrayu[32];    
//};
//union para_u parau;
//#define para 	parau.paras
//
//union para_u para_tempu;
//union para_u const para_minu = {	0,		// dummy
//
//									0,		// preflow time 
//									
//									0,		// strike wfs 
//									0,		// strike volts
//									0,		//mp1
//									0,		//mp2
//
//									0,		// start wfs 
//									0,		// start volts
//									0,		// start time
//									0,		// start carrs
//
//									0,		// upslope time
//
//									0,		// weld wfs 
//									0,		// weld volts
//									0,		// weld carrs
//
//									0,		// dnslope time
//
//									0,		// crater wfs 
//									0,		// crater volts
//									0,		// crater time
//									0,		// crater carrs
//
//									0,		// burnback time
//
//									0,		// postflow time
//									
//									0,		//spot time
//									0,		//pause time
//									0,		//pwm time
//									
//									0,		//led gp1
//									0,		//led gp2
//									0,		//led gp3
//									0,		//led gp4
//									0,		//led gp5
//									0,		//mahesh1
//									0,		//mahesh 1 current multiplier
//									0,		//mahesh 2 autoooset
//									
//									0,		//spotimef
//									0,		//pausetimef
//									0,		//burnbackf
//									0,		//postflowf
//									18,		//weldcurrent
//									0,		//weldarcforce
//									0,		//pwmtime1
//									0		//currntmulti
//								};
//
//
//union para_u const para_maxu = {	0,		// dummy
//
//									10,		// preflow time 
//									
//									0,		//400,	// strike wfs 
//									0,		//99,	// strike volts
//									0,
//									0, 
//
//									180,	//400 start wfs 
//									340,     //99,// start volts
//									180,	//crater curent	// start time
//									170,	//crater voltage	// start carrs
//
//									10,		// upslope time
//
//									180,	// weld wfs 
//									340,     // 170,	// weld volts
//									150,	//weld carrs
//
//									10,		//dnslope time
//
//									180,	//crater wfs 
//									170,     //crater volts
//									10,		//crater time
//									150,	//crater carrs
//
//									20,		//burnback time
//
//									20,		//postflow time
//									
//									30,		//spot time
//									30,		//pause time
//									540,	//pwm time
//									
//									0,		//led gp1
//									0,		//led gp2
//									0,		//led gp3
//									0,		//led gp4
//									0,		//led gp5
//									0,		//mahesh1
//						
//									999,	//mahesh 1 
//									10,	     //mahesh 2
//									
//									0,		//spotimef
//									0,		//pausetimef
//									0,		//burnbackf
//									0,		//postflowf
//									144,	//140,     //weldcurrent
//									100,	//weldarcforce
//									100,	//pwmtime1
//									1000	//current multiplier
//								};
//#define min 	para_minu.paras
//#define max 	para_maxu.paras
//*/
////*******************************************************************************************************************************
///*
//long double kp_prev,ki_prev,kd_prev;
//double gamma1,gamma2,gamma3;
//struct pidParameters
//{
//	float Kp;
//	float Ki;
//	float Kd;
//	float Kf;
//	
//	float error;
//	float output1;
//    float output;
//    float previous_output;
//    float plant_output;
//    float plant_previous_output;
//    float plant_pre_previous_output;
//	float outmax;
//	float ReferenceSetpoint;
//	float feedback;
//	float integral;
//	float derivitive;
//	float previous_error;
//    unsigned long absolute_error;
//	float saturated;
//	float pidoutput;
//} 	pidParams,pidParamsv;
//*/
//
//struct PID_s_Parameters
//{
//	float a;
//	float b;
//	float c;
//	unsigned long  d;
//
//	signed long error;
//	signed long output;
//	signed long poutput;
//	signed long outmax;
//	signed long ReferenceSetpoint;
//	signed long feedback;
//	signed long integral;
//	signed long derivitive;
//	signed long previous_error;
//	signed long pprevious_error;
//	unsigned long absolute_error;
//	signed long saturated;
//	signed long smcoutput;
//	signed long surface;
//	unsigned long abs_surface;
//} 	PID_sParams;
//
///*
//struct PID_s_Parameters1
//{
//	float a1;
//	float b1;
//	float c1;
//	unsigned long  d1;
//	
//	signed long error1;
//	signed long output1;
//	signed long poutput1;
//	signed long outmax1;
//	signed long ReferenceSetpoint1;
//	signed long feedback1;
//	signed long integral1;
//	signed long derivitive1;
//	signed long previous_error1;
//	signed long pprevious_error1;
//	unsigned long absolute_error1;
//	signed long saturated1;
//	signed long smcoutput1;
//	signed long surface1;
//	unsigned long abs_surface1;
//} 	PID_sParams1;
//*/
//
//struct pidParameters
//{
//	float Kp;
//	float Ki;
//	float Kd;
//	float Kf;
//	
//	float error;
//    float output;
//    float previous_output;
//    float Kpnew;
//	float Kinew;
//	float Kdnew;
//	float kpgain;
//	float kigain;
//	float kdgain;
//	//float plant_output;
//    //float plant_previous_output;
//    //float plant_pre_previous_output;
//	float outmax;
//	float ReferenceSetpoint;
//	float feedback;
//	float integral;
//	float derivitive;
//	float previous_error;
//    unsigned long absolute_error;
//	float saturated;
//	float pidoutput;
//	float Kpterm;
//	float Kiterm;
//	float kdterm;
//    /*
//	float Kp1;
//	float Ki1;
//	float Kd1;
//	float output1;
//    float previous_output1;
//    float plant_output1;
//    float plant_previous_output1;
//    float plant_pre_previous_output1;
//	float outmax1;
//	float integral1;
//	float derivitive1;
//	float previous_error1;
//	float pidoutput1;
//	float outmin1;
//	*/
//} 	pidParams; 
//
//
struct pidParameters1
{
	float Kp1;
	float Ki1;
	float Kd1;
	float Kf1;
	
	signed long error1;
	signed long output1;
	signed long previous_output1;
	float Kp1new;
	float Ki1new;
	float Kd1new;
	float kpgain1;
	float kigain1;
	float kdgain1;
	//float plant_output;
    //float plant_previous_output;
    //float plant_pre_previous_output;
	signed long outmax1;
	signed long ReferenceSetpoint1;
	signed long feedback1;
	signed long integral1;
	signed long derivitive1;
	signed long previous_error1;
    unsigned long absolute_error1;
	signed long saturated1;
	signed long pidoutput1;
	signed long Kpterm1;
	signed long Kiterm1;
	signed long kdterm1;
} 	pidParams1;

struct pidParameters2
{
	unsigned int Kp2;
	unsigned int Ki2;
	unsigned int Kd2;
	float Kf2;
	signed long migweldmode;
	signed long error2;
    signed long output2;
    signed long previous_output2;
    float Kp2new;
	float Ki2new;
	float Kd2new;
	float kpgain2;
	float kigain2;
	float kdgain2;
	//float plant_output;
     //float plant_previous_output;
     //float plant_pre_previous_output;
	signed long outmax2;
	signed long ReferenceSetpoint2;
	signed long feedback2;
	signed long integral2;
	signed long derivitive2;
	signed long previous_error2;
    unsigned long absolute_error2;
	signed long saturated2;
	signed long pidoutput2;
	//signed long Kpterm2;
	//signed long Kiterm2;
	//signed long kdterm2;
} 	pidParams2;

struct pstowfstr_s
{
	unsigned char weldmode;					//0
	unsigned char setwspeed;				//1
	unsigned char Hi_setcurrent;			//2
	unsigned char Lo_setcurrent;			//3
	unsigned char setthickness;				//4
		
	unsigned char Hi_setvoltage;			//5
	unsigned char Lo_setvoltage;			//6
	unsigned char arclength;				//7
	
	unsigned char Hi_actualcurrent;			//8
	unsigned char Lo_actualcurrent;			//9
	unsigned char Hi_actualvoltage;			//10
	unsigned char Lo_actualvoltage;			//11
	
	unsigned char psstatusbyte;				//12
	unsigned char wfstatusbyte;				//13
		
	unsigned char rel_wirespeed;			//14
	unsigned char pulse_freq;				//15
	
	unsigned char error_code1;				//16
	
	unsigned char error_code2;				//17
	
	unsigned char crater_speed;				//18
	
	unsigned char creep_speed;              //19
	
	unsigned char command_to_wf;                  //20
    unsigned char Hi_data1;                  //21
    unsigned char Lo_data1;                  //22	
};

union pstowfstr_u
{
	struct pstowfstr_s pstowfstrs;
	unsigned char pstransarr[TX_DATA_LENGTH+1];
};

union pstowfstr_u	pstowfstru;
#define pstowfstr	pstowfstru.pstowfstrs


struct psstatus_s
{
	unsigned char migpmigmode1		:1;		//0 Bit
	unsigned char gasoncommand		:1; 	//1 Bit
	unsigned char weldoncyclestrt	:1;  	//2 Bit
	unsigned char motoroncommand	:1;  	//3 Bit
	unsigned char craterspeedon		:1;   	//4 Bit 1:on 0:off
	unsigned char creepspeedon   	:1;   	//5 Bit
	unsigned char twinpulseon		:1;    	//6 Bit 
	unsigned char Hi_speedon		:1;   	//7 Bit
};
union psstatus_u
{
	struct psstatus_s	psstatuss;
	unsigned char 	 	psstatusbyte[1];
};

union 	psstatus_u	psstatusu;
#define psstatus	psstatusu.psstatuss

struct command_s
{
	unsigned char volt_or_arc	:1;		//0 Bit
	unsigned char spare1		:1; 	//1 Bit
	unsigned char spare2		:1;  	//2 Bit
	unsigned char spare3		:1;  	//3 Bit
	unsigned char spare4		:1;   	//4 Bit 1:on 0:off
	unsigned char spare5   		:1;   	//5 Bit
	unsigned char spare6		:1;    	//6 Bit 
	unsigned char spare7		:1;   	//7 Bit
};
union command_u
{
	struct command_s	commands;
	unsigned char 	 	commandbyte[1];
};

union 	command_u	commandu;
#define command	commandu.commands

/******************Error code*********************/
struct error_s
{
	unsigned char uv_er1		     	:1;		//0 Bit
	unsigned char ov_er2				:1; 	//1 Bit
	unsigned char th_er3				:1;  	//2 Bit
	unsigned char no_curr_er4			:1;  	//3 Bit
	unsigned char motor_over_ld_er5		:1;   	//4 Bit
	unsigned char wirefdr_er6   		:1;   	//5 Bit
	unsigned char water_press_er7		:1;    	//6 Bit 
	unsigned char comm_er8				:1;   	//7 Bit
	
	unsigned char spare1				:1;    	//6 Bit 
	unsigned char over_current_er10		:1;   	//7 Bit	unsigned char spare1			:1;    	//6 Bit 
	unsigned char motor_fb_err			:1;   	//7 Bit	unsigned char spare1			:1;    	//6 Bit 
	unsigned char spare4				:1;    	//6 Bit 
	unsigned char spare5				:1;   	//7 Bit	unsigned char spare1			:1;    	//6 Bit 
	unsigned char spare6				:1;   	//7 Bit	unsigned char spare1			:1;    	//6 Bit 
	unsigned char spare7				:1;   	//7 Bit
	unsigned char spare8				:1;   	//7 Bit;   	//7 Bit
};
union error_u
{
	struct error_s	errors;
	unsigned char 	 	errorstatusbyte[2];
};

union 	error_u		erroru;
#define errorstatus	erroru.errors  
/******************Error code*********************/

struct wfstatus_s
{
	unsigned char twotfourtmode1	:1;   	//5 Bit
	unsigned char torchonstatus		:1;    	//6 Bit 
	unsigned char wfbusystatus		:1;   	//7 Bit
	unsigned char spare11			:1;    	//6 Bit 
	unsigned char spare22			:1;   	//7 Bit	unsigned char spare1			:1;    	//6 Bit 
	unsigned char spare33			:1;   	//7 Bit	unsigned char spare1			:1;    	//6 Bit 
	unsigned char spare44			:1;   	//7 Bit
	unsigned char spare55			:1;   	//7 Bit
};
union wfstatus_u
{
	struct wfstatus_s	wfstatuss;
	unsigned char 	 	wfstatusbyte[1];
};

union 	wfstatus_u	wfstatusu;
#define wfstatus	wfstatusu.wfstatuss


struct EEPROM_DIA_GAS_MODE
{
	unsigned char dia    		:3;
	unsigned char gas			:2;
	unsigned char p_mode		:1;  //@single or Double pulse 
	unsigned char Twot0_fourt1	:1;
	unsigned char nc2			:1;
};

union EEPROM_STRUCT_U
{
	struct EEPROM_DIA_GAS_MODE EEPROM_dia_gas_mode;
	unsigned char EEPROM_struct_u;
};

union 	EEPROM_STRUCT_U 	EEPROM_struct_mig,EEPROM_struct_pmig;

#define EEPROMstruct_pmig	EEPROM_struct_pmig.EEPROM_dia_gas_mode
#define EEPROMstruct_mig	EEPROM_struct_mig.EEPROM_dia_gas_mode

struct ArcOnTime
{
   unsigned int  msec;
   unsigned int  hr;
   unsigned char min;
   unsigned char sec;
};

struct ArcOnTime arcontime;