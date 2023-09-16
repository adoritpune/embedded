
//FOR CATHODES
//************************************************************************************************************
#define VERSA400             						// FOR READ

#define DECODA 			PORTCbits.RC1              	// FOR READ
#define DECODEAIO  		TRISCbits.TRISC1          	// FOR INPUT OUTPUT
#define DECODEALAT 		LATCbits.LATC1            	// FOR WRITE  

#define DECODB 			PORTCbits.RC2              	// FOR READ
#define DECODEBIO  		TRISCbits.TRISC2          	// FOR INPUT OUTPUT
#define DECODEBLAT 		LATCbits.LATC2            	// FOR WRITE  

#define DECODC 			PORTCbits.RC3              	// FOR READ
#define DECODECIO  		TRISCbits.TRISC3          	// FOR INPUT OUTPUT
#define DECODECLAT 		LATCbits.LATC3            	// FOR WRITE   

#define LEDGP3    		PORTBbits.RB0              	// FOR READ
#define LEDGP3IO  		TRISBbits.TRISB0         	// FOR INPUT OUTPUT
#define LEDGP3LAT 		LATBbits.LATB0            	// FOR WRITE  

#define LEDGP4    		PORTBbits.RB1              	// FOR READ
#define LEDGP4IO  		TRISBbits.TRISB1         	// FOR INPUT OUTPUT
#define LEDGP4LAT 		LATBbits.LATB1            	// FOR WRITE  

//******************************************************************************************************************
//FOR SEGMENT LED'S

#define SEGA      		PORTGbits.RG0            	// FOR READ
#define SEGAIO    		TRISGbits.TRISG0			// FOR INPUT OUTPUT
#define SEGALAT   		LATGbits.LATG0				// FOR WRITE 

#define SEGB      		PORTGbits.RG1    			// FOR READ
#define SEGBIO    		TRISGbits.TRISG1			// FOR INPUT OUTPUT
#define SEGBLAT   		LATGbits.LATG1				// FOR WRITE 

#define SEGC      		PORTGbits.RG2				// FOR READ
#define SEGCIO    		TRISGbits.TRISG2			// FOR INPUT OUTPUT
#define SEGCLAT   		LATGbits.LATG2				// FOR WRITE 

#define SEGD      		PORTGbits.RG3				// FOR READ
#define SEGDIO    		TRISGbits.TRISG3			// FOR INPUT OUTPUT
#define SEGDLAT   		LATGbits.LATG3				// FOR WRITE 

#define SEGE      		PORTGbits.RG12				// FOR READ
#define SEGEIO    		TRISGbits.TRISG12			// FOR INPUT OUTPUT
#define SEGELAT  		LATGbits.LATG12				// FOR WRITE 

#define SEGF      		PORTGbits.RG13				// FOR READ
#define SEGFIO    		TRISGbits.TRISG13			// FOR INPUT OUTPUT
#define SEGFLAT   		LATGbits.LATG13				// FOR WRITE 

#define SEGG      		PORTGbits.RG14				// FOR READ
#define SEGGIO    		TRISGbits.TRISG14			// FOR INPUT OUTPUT
#define SEGGLAT   		LATGbits.LATG14				// FOR WRITE 

#define SEGDP      		PORTGbits.RG15				// FOR READ
#define SEGDPIO    		TRISGbits.TRISG15			// FOR INPUT OUTPUT
#define SEGDPLAT   		LATGbits.LATG15				// FOR WRITE 
//******************************************************************************************************************
//FOR KEYPAD INTERFACE

#define ROW1 			PORTDbits.RD9		//for read data
#define ROW2 			PORTDbits.RD10		//for read data
#define ROW3 			PORTDbits.RD11		//for read data
#define ROW4 			PORTDbits.RD12		//for read data

#define COLUMN1 		PORTDbits.RD13 		//for read data
#define COLUMN2 		PORTDbits.RD14		//for read data
#define COLUMN3 		PORTDbits.RD15		//for read data

#define ROW1IO			TRISDbits.TRISD9	//For direction
#define ROW2IO			TRISDbits.TRISD10	//For direction
#define ROW3IO			TRISDbits.TRISD11	//For direction
#define ROW4IO			TRISDbits.TRISD12	//For direction

#define COLUMN1IO  		TRISDbits.TRISD13	//For direction
#define COLUMN2IO  		TRISDbits.TRISD14	//For direction
#define COLUMN3IO  		TRISDbits.TRISD15	//For direction

#define ROW1LAT			LATDbits.LATD9		//for write data
#define ROW2LAT			LATDbits.LATD10		//for write data
#define ROW3LAT			LATDbits.LATD11		//for write data
#define ROW4LAT			LATBbits.LATB12		//for write data

#define COLUMN1LAT		LATDbits.LATD13		//for write data
#define COLUMN2LAT		LATDbits.LATD14		//for write data
#define COLUMN3LAT		LATDbits.LATD15		//for write data

//******************************************************************************************************************
//FOR DAC INTERFACE

#define DACSCK	      	PORTGbits.RG6         // FOR READ
#define DACSCKIO    	TRISGbits.TRISG6      // FOR INPUT OUTPUT
#define DACSCKLAT  	 	LATGbits.LATG6        // FOR WRITE

#define DACSDI	      	PORTGbits.RG7         // FOR READ
#define DACSDIIO    	TRISGbits.TRISG7      // FOR INPUT OUTPUT
#define DACSDILAT  		LATGbits.LATG7        // FOR WRITE

#define DACSDO      	PORTGbits.RG8         // FOR READ
#define DACSDOIO    	TRISGbits.TRISG8      // FOR INPUT OUTPUT
#define DACSDOLAT 		LATGbits.LATG8        // FOR WRITE

#define DACCS	      	PORTGbits.RG9         // FOR READ
#define DACCSIO	   		TRISGbits.TRISG9      // FOR INPUT OUTPUT
#define DACCSLAT	  	LATGbits.LATG9        // FOR WRITE

//****************************************************************************************************************************

#define DECOD_EN		PORTBbits.RB6		//for read data	
#define DECOD_ENIO   	TRISBbits.TRISB6 	//For direction
#define DECOD_ENLAT 	LATBbits.LATB6		//for write data

#define GASWATERIP 	 	PORTCbits.RC4	    //PORTDbits.RD4		//for read data	1:water 0:gas cooled
#define GASWATERIPIO 	TRISCbits.TRISC4 	//TRISDbits.TRISD4 	//For direction
#define GASWATERIPLAT  	LATCbits.LATC4   	//LATDbits.LATD4	//for write data

#define PRESSERRIP 		PORTCbits.RC13	    //PORTDbits.RD4	//for read data	1:water cooling off; 0:water cooling on;
#define PRESSERRIPIO   	TRISCbits.TRISC13 	//TRISDbits.TRISD4 	//For direction
#define PRESSERRIPLAT	LATCbits.LATC13   	//LATDbits.LATD4	//for write data

#define TORCHIP         PORTCbits.RC15	    //PORTDbits.RD4		//for read data	
#define TORCHIPIO 		TRISCbits.TRISC15 	//TRISDbits.TRISD4 	//For direction
#define TORCHIPLAT      LATCbits.LATC15   	//LATDbits.LATD4	//for write data

#define MIG_TORCH	    PORTFbits.RF7	    //PORTDbits.RD4		//for read data	
#define MIG_TORCHIO 	TRISFbits.TRISF7 	//TRISDbits.TRISD4 	//For direction
#define MIG_TORCHLAT    LATFbits.LATF7   	//LATDbits.LATD4	//for write data

#define INCH		    PORTFbits.RF8	    //PORTDbits.RD4		//for read data	
#define INCHIO   		TRISFbits.TRISF8 	//TRISDbits.TRISD4 	//For direction
#define INCHLAT	    	LATFbits.LATF8   	//LATDbits.LATD4	//for write data

#define MTR_TRIP	    PORTCbits.RC14	    //PORTDbits.RD4		//for read data	
#define MTR_TRIPIO   	TRISCbits.TRISC14 	//TRISDbits.TRISD4 	//For direction
#define MTR_TRIPLAT	    LATCbits.LATC14   	//LATDbits.LATD4	//for write data

#define SHDN    		PORTDbits.RD0	    //PORTDbits.RD4		//for read data	
#define SHDNIO   		TRISDbits.TRISD0 	//TRISDbits.TRISD4 	//For direction
#define SHDNLAT			LATDbits.LATD0   	//LATDbits.LATD4	//for write data

#define MPWM    		PORTDbits.RD1	    //PORTDbits.RD4		//for read data //toggle purpose used but M/C ready pin	
#define MPWMIO   		TRISDbits.TRISD1 	//TRISDbits.TRISD4 	//For direction
#define MPWMLAT		    LATDbits.LATD1   	//LATDbits.LATD4	//for write data

#define VRD_SWITCH      PORTBbits.RB15	    // FOR READ
#define VRD_SWITCHIO    TRISBbits.TRISB15   // FOR INPUT OUTPUT
#define VRD_SWITCHLAT   LATBbits.LATB15     // FOR WRITE
 
#define GAS_RELAY      	PORTDbits.RD2         // FOR READ
#define GAS_RELAYIO    	TRISDbits.TRISD2      // FOR INPUT OUTPUT
#define GAS_RELAYLAT	LATDbits.LATD2        // FOR WRITE 

#define TRIP_LED      	PORTAbits.RA9         // FOR READ
#define TRIP_LEDIO    	TRISAbits.TRISA9      // FOR INPUT OUTPUT
#define TRIP_LEDLAT		LATAbits.LATA9        // FOR WRITE 

#define FACTORY_CHECK   TRISBbits.RB1


#define	LEFTSHIFT		11     //10 	//12  // 8//10//13
#define AVGCNT			2048 //1024 //4096 //256//1024//8192
#define	CCMODE	    	1
#define CVMODE			0

#define ON				0
#define	OFF				1

#define set				1


#ifdef VERSA400
		#define	CCOFFSETNEW	  20.0//20.0 //44.15 //0.4   
		#define CCSLOPENEW	  7.0//5.5 //4.7 for 600A HS//6.62 for 400A HS//4.559//latest6.5 //7.454 //6.702
#else
		#define	CCOFFSETNEW	  46.47 //44.15 //0.4   
		#define CCSLOPENEW	  4.559 //7.454 //6.702 
#endif

#define MMACCSLOPENEW   7.0//5.5 //4.75 for 600A HS //6.62 for 400A HS//6.5   //@sayali

#define MIGCCOFFSETNEW  40.0 //22//40.0//10          // 19-9-19

#define MIGCCSLOPENEW	7.0//6.6//12.0//12.0//4.559//3.6//

#define MIN_BASE_AMP 20

#define MIN_FREQ 10

#define MAX_BASE_AMP 90

#define TX_DATA_LENGTH 21

#define CVOFFSET	140.0  //100//520 //700.2  19-9-19

#define CVSLOPE		8.90 //4.490

#define MINI_SAVE_COUNT 1
#define MAX_SAVE_COUNT  100

#define MINI_RECALL_COUNT 1
#define MAX_RECALL_COUNT  100

#define ER_DEBOUNCE_TIME  2//5

#define ERROR4_DEBOUNCE_TIME 4000

#define COMMUNICATION_TIME_OUT 4000  //mSec

#define ERROR_4_THRESHOLD 10 //Amps

#define ARC_ON_RESET_COUNT_LIMIT 250//20MSEC*250 ==5000SEC

#define PASSWORD_SET_COUNT_LIMIT 250//20MSEC*250 ==5000SEC

#define CURRENT_THRESH_HOLD 15

#define min_current 5     


//--------------
#define CABLECHKCOUNT		1
 
//-------------
#define PWSTARBLINKCNT		3

#define MASTER_PASSWORD		1469
//----------------------------------------------------------

#define MATTXT			0
#define DIATXT			52
#define GASTXT			88
#define GASPER			80

#define MMACCSLOPE400  				6.3
#define MMACCOFFSET400 				346.15//350	//340		

#define TIGCCSLOPE400  				6.3
#define TIGCCOFFSET400 				350	//340

//#define MIGCVSLOPE400				5		//9.5		//10.0 //10.0 30 A base	//8.5	10-15 A base
#define MIGCVOFFSET400				120		//500	 //450  30 A base	//400  10-15 A base

#define HOT_START_TIME  			1500 
#define HOT_START_SETCURR_LIMIT  	200

#define ANTISTICK_CURR          	15
#define ANTISTICK_LEAVE_TIME    	1500

#define SHORT_CIRCUIT_CURR			10
#define SHORT_CIRCUIT_LEAVE_TIME   	1500

#define WELDON_START_CURR_MMA		5  
#define WELDON_START_CURR_TIG		5

#define ANTISTICK_VTG_LIMIT     	100
#define SHORT_CIRCUIT_VTG_LIMIT     50.0

#define ARCFORCE_SETCURR_LIMIT_1    10
#define ARCFORCE_SETCURR_LIMIT_2    200
#define ARCFORCE_VTG_LIMIT       	300.0

#define VRD_TIME_MAX    			30
#define VRD_TIME_MIN    			0

#define MTR_PWM_SLOPE				6.80//6.20//6.19//6.0//6.5	//5.5		//7.0	    //5.5  for 20Khz
#define MTR_PWM_OFFSET				1	//55.0	//70.0		//10.0 for 20Khz

#define MTR_PWM_SLOPE_min				9
#define MTR_PWM_OFFSET_min				1

#define MTR_FB_SLOPE		180	 //2.19 //1.49435
#define MTR_FB_OFFSET		5	 //27.75652

#define PWM_CLOSE_CNT		10//300

#define LOADREFCNT 			10
#define LOADFREQCNT 		20

#define GAS_CHECK_CNT		10

#define CREEP_SPEED_DOWN_CNT	500

#define TORCH_DETECT_DB			5


#define STARTPULSECNT		1	//1
#define ENPULSECNT			2	//2
#define WAITTOSTOPCNT		5
#define STARTPULSECURRENT	300;//350
#define ENPULSECURR			300;//350


#define PID_CNTR	2


#define UV_1    2390
#define UV_2    3300	//3100

#define OV_1    2300
#define OV_2    4500

#define TH_1    3700
#define TH_2    4000

#define NO_ERR_CONNECTOR_2    50

#define HSAMP_CNT	15

#define MIG_Kp		50
#define MIG_Ki		3
#define MIG_Kd		5
#define MOTOR_OVERLOAD_ERROR_DETECTION_TIME		10