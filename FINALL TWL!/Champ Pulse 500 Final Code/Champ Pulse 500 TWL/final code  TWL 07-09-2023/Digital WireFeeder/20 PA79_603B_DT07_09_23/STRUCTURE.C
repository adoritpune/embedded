struct Type_S
{
	unsigned char wirespeed	:1;
	unsigned char thickness	:1;
	unsigned char arclength :1;
	unsigned char gason 	:1;
	unsigned char twot    	:1;
	unsigned char fourt    	:1;
	unsigned char SP1   	:1;
	unsigned char SP2   	:1;
    
    unsigned char amp       :1;
	unsigned char vtg	:1;
	unsigned char sec	:1;
	unsigned char inch  :1;
	unsigned char SP3	:1;//  **************************************downslope	:1;
	unsigned char SP4   :1;
	unsigned char SP5   :1;	
	unsigned char SP6	:1; //2TypeU.LEDGROUP[2]
};

union Type_U
{
	struct Type_S TypeS;
	unsigned char LEDGROUP[2];
};

union 	Type_U TypeU;
#define Type	TypeU.TypeS


//TypeU.LEDGROUP[0]=0xFF;
//TypeU.LEDGROUP[1]=0xFF;
//Type.wirespeed		=1;
//Type.voltage		=1;

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

//TypeDP.DPGROUP[0]=0x00;
//Typedp.digitdp1		=1;

struct PID_s_Parameters
{
    float a;
    float b;
    float c;
    unsigned long  d;

    signed long error;
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

/*
struct transoff_s
{
	unsigned char weldmode;					//0
	unsigned char preflowtime;				//1
	unsigned char Hi_setwspeed;				//2
	unsigned char Lo_setwspeed;				//3
	unsigned char Hi_setvoltage;			//4
	unsigned char Lo_setvoltage;			//5
	unsigned char Hi_setcurrent;			//6
	unsigned char Lo_setcurrent;			//7
	unsigned char setthickness;				//8
	unsigned char Hi_cratercurrent;			//9
	unsigned char Lo_cratercurrent;			//10
	unsigned char Hi_cratervoltage;			//11
	unsigned char Lo_cratervoltage;			//12
	unsigned char burnbacktime;				//13
	unsigned char postflow;					//14
	unsigned char statusbyte;				//15
};
*/

/*
struct transoff_s
{
	unsigned char weldmode;				//0
	unsigned char preflowtime;			//1
	unsigned char Hi_setwspeed;			//2
	unsigned char Lo_setwspeed;			//3
	unsigned char Hi_setvoltage;			//4
	unsigned char Lo_setvoltage;			//5
	unsigned char Hi_setcurrent;			//6
	unsigned char Lo_setcurrent;			//7
	unsigned char setthickness;			//8
	unsigned char Hi_cratercurrent;			//9
	unsigned char Lo_cratercurrent;			//10
	unsigned char Hi_cratervoltage;			//11
	unsigned char Lo_cratervoltage;			//12
	unsigned char burnbacktime;			//13
	unsigned char arclength;			//14
        unsigned char Hi_actualcurrent;			//15
	unsigned char Lo_actualcurrent;			//16
	unsigned char Hi_actualvoltage;			//17
	unsigned char Lo_actualvoltage;			//18
        unsigned char weldmodestatus;			//19  preflow,weld,burnback,postflow
	unsigned char psstatusbyte;			//20
        unsigned char wfstatusbyte;                     //21
};

union transoff_u
{
	struct transoff_s transoffs;
	unsigned char transarr[21];
};

union transoff_u	transoffu;
#define transoff	transoffu.transoffs
*/
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
	unsigned char pstransarr[RECEIVE_STRING_LENGTH+1];
};

union pstowfstr_u	pstowfstru;
#define pstowfstr	pstowfstru.pstowfstrs

/*********************************Error Code**************************************************8*/
struct error_s
{
	unsigned char uv_er1		     	:1;	//0 Bit
	unsigned char ov_er2			:1; 	//1 Bit
	unsigned char th_er3			:1;  	//2 Bit
	unsigned char no_curr_er4		:1;  	//3 Bit
	unsigned char motor_over_ld_er5		:1;   	//4 Bit
	unsigned char wirefdr_er6   		:1;   	//5 Bit
	unsigned char water_press_er7		:1;    	//6 Bit
	unsigned char comm_er8			:1;   	//7 Bit

	unsigned char spare1			:1;    	//6 Bit
	unsigned char over_current_er10		:1;   	//7 Bit	unsigned char spare1			:1;    	//6 Bit
	unsigned char motor_fb_err		:1;   	//7 Bit	unsigned char spare1			:1;    	//6 Bit
	unsigned char spare4			:1;    	//6 Bit
	unsigned char spare5			:1;   	//7 Bit	unsigned char spare1			:1;    	//6 Bit
	unsigned char spare6			:1;   	//7 Bit	unsigned char spare1			:1;    	//6 Bit
	unsigned char spare7			:1;   	//7 Bit
	unsigned char spare8			:1;   	//7 Bit;   	//7 Bit
};
union error_u
{
	struct error_s	errors;
	unsigned char 	 	errorstatusbyte[2];
};

union 	error_u		erroru;
#define errorstatus	erroru.errors

/*********************************Error Code end**************************************************8*/

struct psstatus_s
{
	unsigned char migpmigmode		:1;		//0 Bit
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


struct wfstatus_s
{
	unsigned char twotfourtmode1    :1;
	unsigned char torchonstatus     :1;
	unsigned char wfbusystatus      :1;
        unsigned char spare11           :1;
	unsigned char spare12           :1;
	unsigned char spare13           :1;
	unsigned char spare14           :1;
	unsigned char spare15           :1;
};

union wfstatus_u
{
	struct wfstatus_s	wfstatuss;
	unsigned char 	 	wfstatusbyte[1];
};

union 	wfstatus_u	wfstatusu;
#define wfstatus	wfstatusu.wfstatuss

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
