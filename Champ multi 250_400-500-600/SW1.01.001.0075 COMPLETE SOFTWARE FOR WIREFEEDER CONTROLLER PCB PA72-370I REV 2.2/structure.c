struct Type_S
{
	unsigned char speed		:1;
	unsigned char amp			:1;
	unsigned char crateron		:1;
	unsigned char cratcurr 		:1;
	unsigned char cratvolt		:1;
	unsigned char arcforce  	:1;
	unsigned char voltage		:1;	
	unsigned char time  		:1;//1TypeU.LEDGROUP[0]
	
	unsigned char preflow		:1;
	unsigned char ini	  		:1;
	unsigned char upslope		:1;
	unsigned char weld			:1;
	unsigned char mma			:1;//  **************************************downslope	:1;
	unsigned char crater		:1;
	unsigned char burnback	:1;	
	unsigned char postflow		:1; //2TypeU.LEDGROUP[1]

	unsigned char zeropteight	:1;
	unsigned char oneptzero	:1;
	unsigned char onepttwo	:1;
	unsigned char oneptsix		:1;
	unsigned char fe			:1;
	unsigned char nic			:1;
	unsigned char alu			:1;
	unsigned char fcaw		:1;//**************************************tig		:1;	//3TypeU.LEDGROUP[2]

	unsigned char arco2		:1;
	unsigned char co2	 		:1;
	unsigned char ar			:1;
	unsigned char aro2			:1;
	unsigned char multispot	:1;
	unsigned char spot			:1;
	unsigned char fourt		:1;
	unsigned char twot			:1;	//4TypeU.LEDGROUP[3]

	unsigned char gascheck	:1;
	unsigned char ocvcheck  	:1;
	unsigned char inching		:1;
	unsigned char recall		:1;
	unsigned char automan		:1;
	unsigned char save			:1;
	unsigned char tig			:1;//****************************************mma		:1;
	unsigned char mig        	:1;	//5TypeU.LEDGROUP[4]

};
union Type_U
{
	struct Type_S TypeS;
	unsigned char LEDGROUP[5];
};

union Type_U TypeU;

#define Type	TypeU.TypeS

//*******************************************************************************************************************************
struct para_s
{
	unsigned int dummy;						//0000
	struct		// prog = 0
	{
		unsigned int time;						//0001
	}
	preflow;
//******************************************************************************
//******************************************************************************
//MODIFIED FOR fcaw MODE DATA SAVING
/*	struct		// prog = 1
	{
		unsigned int ledgpsizemat;				//0002
		unsigned int ledgpgasmode;				//0003
	}
	//strike;	
*/
	struct		// prog = 2
	{
		unsigned char migledgp2;				//0002						//TypeU.LEDGROUP[2]
		unsigned char migledgp3;				//0002						//TypeU.LEDGROUP[3]
		unsigned char fcawledgp2;				//0003						//TypeU.LEDGROUP[2]
		unsigned char fcawledgp3;				//0003						//TypeU.LEDGROUP[3]
		unsigned int wfs;						//0004
		unsigned int volts;						//0005
		unsigned int craterwfs;					//time;						//0006
		unsigned int cratervolts;				//carrs;						//0007	
	}
	fcaw;										//modified for memory location start;
//******************************************************************************
//******************************************************************************
	struct		// prog = 3
	{
		unsigned int time;						//0008
	}
	upslope;
	struct		// prog = 4
	{
		unsigned int wfs;						//0009
		unsigned int volts;						//0010
		unsigned int carrs;						//0011
	}
	weld;
	struct		// prog = 5
	{
		unsigned int time;						//0012
	}
	dnslope;
	struct		// prog = 6
	{
		unsigned int wfs;						//0013
		unsigned int volts;						//0014
		unsigned int time;						//0015
		unsigned int carrs;						//0016
	}
	crater;
	struct		// prog = 7
	{
		unsigned int time;						//0017
	}
	burnback;
	struct		// prog = 8
	{
		unsigned int time;						//0018
	}
	postflow;
	unsigned int 	spottime;					//0019
	unsigned int 	pausetime;					//0020
	unsigned int 	pwmtime;					//0021  (for wire speed)
	unsigned char 	ledgp1;						//0022 	(lower byte)
	unsigned char 	ledgp2;						//0022 	(higher byte)
	unsigned char 	ledgp3;						//0023 	(lower byte)
	unsigned char 	ledgp4;						//0023 	(higher byte)
	unsigned char 	ledgp5;						//0024	(lower byte)
	unsigned char 	passprotect1;			    	//0024	(higher byte)
	unsigned int    password1;	                		//0025	//location for current multiplier
	unsigned int  	migws;     					//0026 	passprotect1;					
	unsigned char 	spottimef;					//0027	(lower byte)	
	unsigned char 	pausetimef;					//0027	(higher byte)
	unsigned char 	burnbackf;					//0028	(lower byte)
	unsigned char 	postflowf;					//0028	(higher byte)
	unsigned int  	weldcurrent;				//0029
	unsigned int  	weldarcforce;				//0030
	unsigned int  	pwmtime1;   				//0031	//for voltage or current encoder
	unsigned int  	fcawws;					//0032	//currmult;						
};
union para_u
{
	struct para_s paras;
	unsigned int arrayu[32];    
};
union para_u parau;
#define para 	parau.paras

union para_u para_tempu;
union para_u const para_minu = {	0,		// dummy

									0,		// preflow time 
									
									0,		// strike wfs 
									0,		// strike volts
									0,		//mp1
									0,		//mp2

									0,		// start wfs 
									0,		// start volts
									0,		// start time
									0,		// start carrs

									0,		// upslope time

									0,		// weld wfs 
									0,		// weld volts
									0,		// weld carrs

									0,		// dnslope time

									0,		// crater wfs 
									0,		// crater volts
									0,		// crater time
									0,		// crater carrs

									0,		// burnback time

									0,		// postflow time
									
									0,		//spot time
									0,		//pause time
									0,		//pwm time
									
									0,		//led gp1
									0,		//led gp2
									0,		//led gp3
									0,		//led gp4
									0,		//led gp5
									0,		//mahesh1
									0,		//mahesh 1 current multiplier
									0,		//mahesh 2 autoooset
									
									0,		//spotimef
									0,		//pausetimef
									0,		//burnbackf
									0,		//postflowf
									18,		//weldcurrent
									0,		//weldarcforce
									0,		//pwmtime1
									0		//currntmulti
								};


union para_u const para_maxu = {	0,		// dummy

									10,		// preflow time 
									
									0,		//400,	// strike wfs 
									0,		//99,	// strike volts
									0,
									0, 

									180,	//400 start wfs 
									340,     //99,// start volts
									180,	//crater curent	// start time
									170,	//crater voltage	// start carrs

									10,		// upslope time

									180,	// weld wfs 
									340,     // 170,	// weld volts
									150,	//weld carrs

									10,		//dnslope time

									180,	//crater wfs 
									170,     //crater volts
									10,		//crater time
									150,	//crater carrs

									50,		//burnback time

									20,		//postflow time
									
									30,		//spot time
									30,		//pause time
									540,	//pwm time
									
									0,		//led gp1
									0,		//led gp2
									0,		//led gp3
									0,		//led gp4
									0,		//led gp5
									0,		//mahesh1
						
									999,	//mahesh 1 
									10,	     //mahesh 2
									
									0,		//spotimef
									0,		//pausetimef
									0,		//burnbackf
									0,		//postflowf
									144,	//140,     //weldcurrent
									100,	//weldarcforce
									100,	//pwmtime1
									1000	//current multiplier
								};
#define min 	para_minu.paras
#define max 	para_maxu.paras
//*******************************************************************************************************************************


