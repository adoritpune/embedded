//FOR CATHODES
//************************************************************************************************************
//#define CATHODE1    	PORTGbits.RG0              // FOR READ
//#define CATHODE1IO  	TRISGbits.TRISG0           // FOR INPUT OUTPUT
//#define CATHODE1LAT 	LATGbits.LATG0             // FOR WRITE  

#define MIGON    	PORTGbits.RG1              // FOR READ
#define MIGONIO  	TRISGbits.TRISG1           // FOR INPUT OUTPUT
#define MIGONLAT 	LATGbits.LATG1             // FOR WRITE  

#define CURR_LED    	PORTGbits.RG2              // FOR READ
#define CURR_LEDIO  	TRISGbits.TRISG2           // FOR INPUT OUTPUT
#define CURR_LEDLAT 	LATGbits.LATG2             // FOR WRITE  

#define WS_SPEED_LED   		PORTGbits.RG3            // FOR READ
#define WS_SPEED_LEDIO  	TRISGbits.TRISG3           // FOR INPUT OUTPUT
#define WS_SPEED_LEDLAT	 	LATGbits.LATG3            // FOR WRITE 


//FOR DAC INTERFACE

#define DACSCK PORTGbits.RG6
#define DACSCKIO TRISGbits.TRISG6
#define DACSCKLAT LATGbits.LATG6

#define DACSDO PORTGbits.RG8
#define DACSDOIO TRISGbits.TRISG8
#define DACSDOLAT LATGbits.LATG8

#define DACCS PORTGbits.RG9
#define DACCSIO TRISGbits.TRISG9
#define DACCSLAT LATGbits.LATG9

/*******************************decoder*****************************/
#define DECODEB     	PORTGbits.RG12              // FOR READ
#define DECODEBIO   	TRISGbits.TRISG12           // FOR INPUT OUTPUT
#define DECODEBLAT  	LATGbits.LATG12             // FOR WRITE  

#define DECODEC      	PORTGbits.RG13              // FOR READ
#define DECODECIO    	TRISGbits.TRISG13           // FOR INPUT OUTPUT
#define DECODECLAT   	LATGbits.LATG13             // FOR WRITE  

#define DECODEA      	PORTGbits.RG14              // FOR READ
#define DECODEAIO    	TRISGbits.TRISG14           // FOR INPUT OUTPUT
#define DECODEALAT   	LATGbits.LATG14             // FOR WRITE  

#define DECODEEN    	PORTGbits.RG15              // FOR READ
#define DECODEENIO  	TRISGbits.TRISG15           // FOR INPUT OUTPUT
#define DECODEENLAT 	LATGbits.LATG15             // FOR WRITE  
 



/************************FOR SEGMENT LEDS**************************************************************/

#define SEGA      		PORTBbits.RB15             // FOR READ					//RD1
#define SEGAIO    		TRISBbits.TRISB15		// FOR INPUT OUTPUT		//RD1
#define SEGALAT   	    LATBbits.LATB15		     // FOR WRITE 				//RD1

#define SEGB      		PORTDbits.RD2             	// FOR READ
#define SEGBIO    		TRISDbits.TRISD2		// FOR INPUT OUTPUT
#define SEGBLAT  		LATDbits.LATD2			// FOR WRITE

#define SEGC      		PORTDbits.RD3             	// FOR READ
#define SEGCIO    		TRISDbits.TRISD3		// FOR INPUT OUTPUT
#define SEGCLAT   		LATDbits.LATD3			// FOR WRITE

#define SEGD      		PORTDbits.RD4             	// FOR READ
#define SEGDIO    		TRISDbits.TRISD4		// FOR INPUT OUTPUT
#define SEGDLAT   		LATDbits.LATD4			// FOR WRITE

#define SEGE      		PORTDbits.RD5             	// FOR READ
#define SEGEIO    		TRISDbits.TRISD5		// FOR INPUT OUTPUT
#define SEGELAT   		LATDbits.LATD5			// FOR WRITE

#define SEGF      		PORTDbits.RD6             	// FOR READ
#define SEGFIO    		TRISDbits.TRISD6		// FOR INPUT OUTPUT
#define SEGFLAT   		LATDbits.LATD6			// FOR WRITE

#define SEGG      		PORTDbits.RD7             	// FOR READ
#define SEGGIO    		TRISDbits.TRISD7		// FOR INPUT OUTPUT
#define SEGGLAT   		LATDbits.LATD7			// FOR WRITE

#define SEGDP      		PORTDbits.RD8             	// FOR READ
#define SEGDPIO    		TRISDbits.TRISD8		// FOR INPUT OUTPUT
#define SEGDPLAT   		LATDbits.LATD8			// FOR WRITE


//-----------------------------------------------------------------------------
#define MPWM      		PORTDbits.RD1             	// FOR READ
#define MPWMIO    		TRISDbits.TRISD1		// FOR INPUT OUTPUT
#define MPWMLAT  		LATDbits.LATD1			// FOR WRITE
//-----------------------------------------------------------------------------

//******************************************************************************************************************
//FOR ENCODER
#define ENCODERA		PORTFbits.RF0
#define ENCODERB		PORTFbits.RF1
#define ENCODERAIO 		TRISFbits.TRISF0		//For direction
#define ENCODERBIO 		TRISFbits.TRISF1		//For direction
#define ENCODERALAT		LATFbits.LATF0			//for write data
#define ENCODERBLAT		LATFbits.LATF1			//for write data

#define ENCODER     	PORTF
#define ENCODERIO		TRISF
#define ENCODERLAT		LATF

#define ENCODERSW    	PORTFbits.RF6			// FOR READ
#define ENCODERSWIO 	TRISFbits.TRISF6        // FOR INPUT OUTPUT
#define ENCODERSWLAT	LATFbits.LATF6          // FOR WRITE
//******************************************************************************************************************
#define OCV_FLAG     	PORTDbits.RD9           // FOR READ
#define OCV_FLAGIO    	TRISDbits.TRISD9        // FOR INPUT OUTPUT
#define OCV_FLAGLAT  	LATDbits.LATD9          // FOR WRITE  
//******************************************************************************************************************
#define ARCON			PORTBbits.RB4
#define ARCONLAT		LATBbits.LATB4			//for write data
#define ARCONIO 		TRISBbits.TRISB4		//For direction

#define CCCVMODE		PORTBbits.RB8
#define CCCVLAT			LATBbits.LATB8			//for write data
#define CCCVIO 	    	TRISBbits.TRISB8		//For direction

//*****************************************************************************************************************
#define TORCHSW	    	PORTBbits.RB9		//TORCH SWITCH DETECTION   //not used in versa 800
#define TORCHSWLAT		LATBbits.LATB9		//for write data
#define TORCHSWIO 		TRISBbits.TRISB9	//For direction

#define INCHSW	    	PORTBbits.RB10		//EXTERNALLY INCH SWITCH   //not used in versa 800
#define INCHSWLAT		LATBbits.LATB10		//for write data
#define INCHSWIO 		TRISBbits.TRISB10	//For direction

#define MOVLD	    	PORTBbits.RB12		//MOTOR OVERLOADING SIGNAL
#define MOVLDLAT		LATBbits.LATB12		//for write data
#define MOVLDIO 		TRISBbits.TRISB12	//For direction

#define GASRELAY	    PORTBbits.RB13		//MOTOR OVERLOADING SIGNAL
#define GASRELAYLAT		LATBbits.LATB13		//for write data
#define GASRELAYIO 		TRISBbits.TRISB13	//For direction

#define TMODESW	    	PORTCbits.RC13		//DETECTION OF 2T 4T SWITCH //not uused in versa 800
#define TMODESWLAT		LATCbits.LATC13	    //for write data
#define TMODESWIO 		TRISCbits.TRISC13	//For direction

#define GASCHKSW 		PORTCbits.RC14		//GAS CHECK SWITCH.
#define GASCHKSWLAT		LATCbits.LATC14	    //for write data
#define GASCHKSWIO 		TRISCbits.TRISC14	//For direction

#define NC1	    PORTCbits.RC1		        //MOTOR OVERLOADING SIGNAL
#define NC1LAT	LATCbits.LATC1	            //for write data
#define NC1IO 	TRISCbits.TRISC1	        //For direction




//****************************************************************************************************************
#define avgcnt         	4    
#define disvolt_cnt    	4096   
//#define loop           	4096  
#define set            	1
#define CCMODE		1
#define CVMODE		1
#define MMAMODE	1
#define	MIGMODE	2
#define	SAWMODE	3


#define VTG_AVG_COUNT 256
#define VTG_AVG_SHIFT 8

#define HOT_STRT_TIME    500
#define HOTSTRT_PERCNT_1 15
#define HOTSTRT_PERCNT_2 15  //@ not use
//#define CVSLOPE 15 //6.5

//#define MIGCCOFFSET 400.0 //700.0 //800.0 //20.88 //22//40.0//10          // 19-9-19
#define MIGCCSLOPE	0.5 //5.22 //6.6//12.0//12.0//4.559//3.6//

#define MMACCSLOPE		2.0//2.25 //2.072   //3.9225
#define MMACCOFFSET		610.0//510.0//610.0 //470.0 //427.0

//-----------------------------------------
#define MMACCSLOPE100		1.05
#define MMACCSLOPE200		1.45
#define MMACCSLOPE400		1.70
#define MMACCSLOPE600		1.80
#define MMACCSLOPE700		2.07

#define CURRENT100			100
#define CURRENT200			200
#define CURRENT400			400
#define CURRENT600			600
#define CURRENT700			700
#define CURRENT800			800
//-----------------------------------------
#define STRING_LENGTH 21

#define dt 0.1
#define epsilon 0.01

//-----------------------------------------------------------------
//Min Range

#define MIN_SETVOLTAGE	140
#define MIN_WIRESPEED	20

//Max Range

#define MAX_SETVOLTAGE	400
#define MAX_WIRESPEED	220
 
//Parameters

#define PREF	1000
#define POSTF	1000
#define BURN	500

//-----------------------------------------------------------------

#define ERROR_4_THRESHOLD		60
#define ERROR4_DEBOUNCE_TIME	4000
#define COMMUNICATION_TIME_OUT	4000 