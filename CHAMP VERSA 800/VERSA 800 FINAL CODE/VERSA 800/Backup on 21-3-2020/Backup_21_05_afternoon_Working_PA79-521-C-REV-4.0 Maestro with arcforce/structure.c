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

//data to be transmitted to wirefeeder
struct transmit_parameter_s      //structure for transmitting data from PS to wirefeeder
{
	unsigned char set_wire_speed;       //1
	unsigned char lo_set_current;    //2
	unsigned char hi_set_current;    //3
	unsigned char arclength;        //4
	unsigned char lo_actual_current;       //5
	unsigned char hi_actual_current;       //6
	unsigned char lo_actual_voltage;    //7
	unsigned char hi_actual_voltage;    //8
	
	unsigned char psstatusbyte;         //9
	unsigned char wfstatusbyte;         //10
	


};
union transmit_parameter_u
{
	struct transmit_parameter_s transmit_parameters;
	unsigned char transmit_parameter_byte[10];

};

union transmit_parameter_u transmit_parameteru;
#define  transmit_parameter  transmit_parameteru.transmit_parameters

/*
//power source status
struct psstatus_s
{
	unsigned char weldon         :1; //1 bit
	unsigned char motoron        :1; //2
	unsigned char wirefeederoff  :1; //3
	
	unsigned char gasoncommand   :1; //4
	
	unsigned char creepspeedon   :1; //5
	unsigned char unused3        :1; //6
	unsigned char unused4        :1; //7
	unsigned char unused5        :1; //8


};
*/
//power source status
struct psstatus_s
{
	unsigned char unused1        :1; //1
	unsigned char gasoncommand   :1; //2
	unsigned char weldon         :1; //3 bit
	unsigned char motoron        :1; //4
	unsigned char unused2        :1; //5
	unsigned char creepspeedon   :1; //6
	unsigned char unused3        :1; //7
	unsigned char unused4        :1; //8


};

union psstatus_u
{
	struct psstatus_s psstatuss;
	unsigned char psstatusbyte[1];


};

union psstatus_u psstatusu;
#define psstatus psstatusu.psstatuss


//wirefeeder status structure
struct wf_status_s
{
	unsigned char twotfourtmode1   :1; 
	unsigned char torchonstatus    :1;
	unsigned char wfbusstatus      :1;
	unsigned char spare11          :1;
	unsigned char spare12          :1;
	unsigned char spare13          :1;
	unsigned char spare14          :1;
	unsigned char spare15          :1;


};
union wf_status_u
{
	struct wf_status_s wf_statuss;
	unsigned char wfstatusbyte[1];

};
union wf_status_u wf_statusu;
#define wfstatus wf_statusu.wf_statuss

//received data
struct receive_parameter_s       //structure for receiving data from wirefeeder
{
	unsigned char weldmode;				//1  2T 4T
	unsigned char setwspeed;			//2
	unsigned char Hi_setcurrent;		//3
	unsigned char Lo_setcurrent;		//4
	

	unsigned char Hi_setvoltage;		//5
	unsigned char Lo_setvoltage;		//6
	unsigned char arclength;			//7

	unsigned char Gas_check_key;		//8 Hi_actualcurrent
	unsigned char Inch_on;		        //9 Lo_actualcurrent
	unsigned char Torch_on;		        //10 Hi_actualvoltage
	unsigned char spare1;		        //11

	unsigned char psstatusbyte;			//12
	unsigned char wfstatusbyte;			//13

	unsigned char rel_wirespeed;		//14
	unsigned char spare2;				//15
	
	unsigned char preflow_time;			//16
    unsigned char postflow_time;        //17
    unsigned char burnback_time;		//18
	
};
union receive_parameter_u
{
	struct receive_parameter_s receive_parameters;
	unsigned char receive_parameter_byte[18];

};

union receive_parameter_u receive_parameteru;
#define  receive_parameter  receive_parameteru.receive_parameters


struct commu_ps_wf_s
{
	/*
    unsigned char weldmode;				//0
	unsigned char setwspeed;			//1
	unsigned char Lo_setcurrent;			//2
	unsigned char Hi_setcurrent;			//3
	//unsigned char setthickness4
	
	unsigned char Hi_setvoltage;			//4
	unsigned char Lo_setvoltage;			//5
	unsigned char arclength;			//6

	unsigned char Hi_actualcurrent;			//7
	unsigned char Lo_actualcurrent;			//8
	unsigned char Hi_actualvoltage;			//9
	unsigned char Lo_actualvoltage;			//10

	unsigned char psstatusbyte;			//11
	unsigned char wfstatusbyte;			//12
	unsigned char rel_wirespeed;			//13
	//unsigned char spare2;				//

    unsigned char error_code1;	                //14
    unsigned char error_code2;	                //15
    unsigned char crater_speed;	                //16
    unsigned char creep_speed;	                //17

    unsigned char command_to_wf;	                //18

    unsigned char preflow_time;                     //19
    unsigned char postflow_time;                     //20
    unsigned char burnback_time;                     //21
	*/
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
	


};
union commu_ps_wf_u
{
    struct commu_ps_wf_s commu_ps_wfs;
    unsigned char commu_arr[STRING_LENGTH+1];

};
union commu_ps_wf_u commu_ps_wfu;
#define communication commu_ps_wfu.commu_ps_wfs


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

struct fooPID_s{
	unsigned int *abcCoefficients[3];
	unsigned int *controlHistory[3];
	unsigned int measuredOutput;
	unsigned int controlReference;
	int *PIDInit;
	int *PIDCoeffCalc[2];
	int *PID;
};

union fooPID_u
{
    struct fooPID_s fooPIDs;
    unsigned char fooPID_byte[7];

};
union fooPID_u fooPIDu;
#define fooPID fooPIDu.fooPIDs

/*
typedef struct{
	fractional abcCoefficients;
	fractional controlHistory;
	fractional controlOutput;
	fractional measuredOutput;
	fractional controlRefernce;
}tPID;

extern void PIDCoeffCalc(
	fractional* kCoeffs,
	tPID* controller
);

extern void PIDInit (
	tPID* controller
);

extern fractional * PID (
	tPID* controller
);
*/