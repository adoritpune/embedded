//FOR CATHODES
//************************************************************************************************************
#define DECODA 		PORTCbits.RC1              // FOR READ
#define DECODEAIO  	TRISCbits.TRISC1          // FOR INPUT OUTPUT
#define DECODEALAT 	LATCbits.LATC1            // FOR WRITE  

#define DECODB 		PORTCbits.RC2              // FOR READ
#define DECODEBIO  	TRISCbits.TRISC2          // FOR INPUT OUTPUT
#define DECODEBLAT 	LATCbits.LATC2            // FOR WRITE  

#define DECODC 		PORTCbits.RC3              // FOR READ
#define DECODECIO  	TRISCbits.TRISC3          // FOR INPUT OUTPUT
#define DECODECLAT 	LATCbits.LATC3            // FOR WRITE  

//#define LEDGP1    		PORTGbits.RG6              // FOR READ
//#define LEDGP1IO  		TRISGbits.TRISG6         	// FOR INPUT OUTPUT
//#define LEDGP1LAT 		LATGbits.LATG6            	// FOR WRITE  
//
//#define LEDGP2    		PORTGbits.RG7              // FOR READ
//#define LEDGP2IO  		TRISGbits.TRISG7         	// FOR INPUT OUTPUT
//#define LEDGP2LAT 		LATGbits.LATG7            	// FOR WRITE  
//
#define LEDGP3    		PORTBbits.RB0              // FOR READ
#define LEDGP3IO  		TRISBbits.TRISB0         	// FOR INPUT OUTPUT
#define LEDGP3LAT 		LATBbits.LATB0            	// FOR WRITE  

#define LEDGP4    		PORTBbits.RB1              // FOR READ
#define LEDGP4IO  		TRISBbits.TRISB1         	// FOR INPUT OUTPUT
#define LEDGP4LAT 		LATBbits.LATB1            	// FOR WRITE  

//******************************************************************************************************************
//FOR SEGMENT LED'S
#define SEGA      	PORTGbits.RG0            // FOR READ
#define SEGAIO    	TRISGbits.TRISG0			// FOR INPUT OUTPUT
#define SEGALAT   	LATGbits.LATG0			// FOR WRITE 

#define SEGB      	PORTGbits.RG1    			// FOR READ
#define SEGBIO    	TRISGbits.TRISG1			// FOR INPUT OUTPUT
#define SEGBLAT   	LATGbits.LATG1			// FOR WRITE 

#define SEGC      	PORTGbits.RG2				// FOR READ
#define SEGCIO    	TRISGbits.TRISG2			// FOR INPUT OUTPUT
#define SEGCLAT   	LATGbits.LATG2			// FOR WRITE 

#define SEGD      	PORTGbits.RG3				// FOR READ
#define SEGDIO    	TRISGbits.TRISG3			// FOR INPUT OUTPUT
#define SEGDLAT   	LATGbits.LATG3			// FOR WRITE 

#define SEGE      	PORTGbits.RG12				// FOR READ
#define SEGEIO    	TRISGbits.TRISG12			// FOR INPUT OUTPUT
#define SEGELAT  	LATGbits.LATG12			// FOR WRITE 

#define SEGF      	PORTGbits.RG13				// FOR READ
#define SEGFIO    	TRISGbits.TRISG13			// FOR INPUT OUTPUT
#define SEGFLAT   	LATGbits.LATG13			// FOR WRITE 

#define SEGG      	PORTGbits.RG14				// FOR READ
#define SEGGIO    	TRISGbits.TRISG14			// FOR INPUT OUTPUT
#define SEGGLAT   	LATGbits.LATG14			// FOR WRITE 

#define SEGDP      	PORTGbits.RG15				// FOR READ
#define SEGDPIO    	TRISGbits.TRISG15			// FOR INPUT OUTPUT
#define SEGDPLAT   	LATGbits.LATG15			// FOR WRITE 
//******************************************************************************************************************
//FOR KEYPAD INTERFACE
#define ROW1 		PORTDbits.RD9		//for read data
#define ROW2 		PORTDbits.RD10		//for read data
#define ROW3 		PORTDbits.RD11		//for read data
#define ROW4 		PORTDbits.RD12		//for read data

#define COLUMN1 	PORTDbits.RD13 		//for read data
#define COLUMN2 	PORTDbits.RD14		//for read data
#define COLUMN3 	PORTDbits.RD15		//for read data

#define ROW1IO		TRISDbits.TRISD9	//For direction
#define ROW2IO		TRISDbits.TRISD10	//For direction
#define ROW3IO		TRISDbits.TRISD11	//For direction
#define ROW4IO		TRISDbits.TRISD12	//For direction

#define COLUMN1IO  	TRISDbits.TRISD13	//For direction
#define COLUMN2IO  	TRISDbits.TRISD14	//For direction
#define COLUMN3IO  	TRISDbits.TRISD15	//For direction

#define ROW1LAT		LATDbits.LATD9		//for write data
#define ROW2LAT		LATDbits.LATD10	//for write data
#define ROW3LAT		LATDbits.LATD11	//for write data
#define ROW4LAT		LATBbits.LATB12		//for write data

#define COLUMN1LAT	LATDbits.LATD13		//for write data
#define COLUMN2LAT	LATDbits.LATD14		//for write data
#define COLUMN3LAT	LATDbits.LATD15		//for write data

//******************************************************************************************************************
//FOR ENCODER
#define ENCODER1A	    PORTAbits.RA6
#define ENCODER1B	    PORTAbits.RA7
#define ENCODER1AIO 	TRISAbits.TRISA6	//For direction
#define ENCODER1BIO 	TRISAbits.TRISA7	//For direction
#define ENCODER1ALAT	LATAbits.LATA6		//for write data
#define ENCODER1BLAT	LATAbits.LATA7		//for write data

#define ENCODER2A	    PORTAbits.RA9
#define ENCODER2B	    PORTAbits.RA10
#define ENCODER2AIO 	TRISAbits.TRISA9	//For direction
#define ENCODER2BIO 	TRISAbits.TRISA10	//For direction
#define ENCODER2ALAT	LATAbits.LATA9	    //for write data
#define ENCODER2BLAT	LATAbits.LATA10 	//for write data

#define ENCODER3A	    PORTAbits.RA14
#define ENCODER3B	    PORTAbits.RA15
#define ENCODER3AIO 	TRISAbits.TRISA14	//For direction
#define ENCODER3BIO 	TRISAbits.TRISA15	//For direction
#define ENCODER3ALAT	LATAbits.LATA14		//for write data
#define ENCODER3BLAT	LATAbits.LATA15		//for write data

//#define ENCODERSW      PORTBbits.RB15         // FOR READ
//#define ENCODERSWIO   TRISBbits.TRISB15      // FOR INPUT OUTPUT
//#define ENCODERSWLAT LATBbits.LATB15        // FOR WRITE

//*************************************************************************************************
//LCD DATA DEFINES
#define LCDEN    	PORTDbits.RD6          	// FOR READ
#define LCDENIO  	TRISDbits.TRISD6             // FOR INPUT OUTPUT
#define LCDENLAT 	LATDbits.LATD6              // FOR WRITE 

#define LCDRS    	PORTDbits.RD7                // FOR READ
#define LCDRSIO  	TRISDbits.TRISD7           // FOR INPUT OUTPUT
#define LCDRSLAT 	LATDbits.LATD7             // FOR WRITE 

#define LCDCS1    	PORTDbits.RD4              // FOR READ
#define LCDCS1IO  	TRISDbits.TRISD4           // FOR INPUT OUTPUT
#define LCDCS1LAT 	LATDbits.LATD4             // FOR WRITE 

#define LCDCS2    	PORTDbits.RD5              // FOR READ
#define LCDCS2IO  	TRISDbits.TRISD5           // FOR INPUT OUTPUT
#define LCDCS2LAT 	LATDbits.LATD5             // FOR WRITE

#define DB0    		PORTBbits.RB8              // FOR READ
#define DB0IO  		TRISBbits.TRISB8           // FOR INPUT OUTPUT
#define DB0LAT 		LATBbits.LATB8             // FOR WRITE

#define DB1    		PORTBbits.RB9              // FOR READ
#define DB1IO  		TRISBbits.TRISB9           // FOR INPUT OUTPUT
#define DB1LAT 		LATBbits.LATB9             // FOR WRITE

#define DB2    		PORTBbits.RB10              // FOR READ
#define DB2IO  		TRISBbits.TRISB10           // FOR INPUT OUTPUT
#define DB2LAT 		LATBbits.LATB10             // FOR WRITE

#define DB3    		PORTBbits.RB11              // FOR READ
#define DB3IO  		TRISBbits.TRISB11           // FOR INPUT OUTPUT
#define DB3LAT	 	LATBbits.LATB11             // FOR WRITE

#define DB4    		PORTBbits.RB12              // FOR READ
#define DB4IO  		TRISBbits.TRISB12           // FOR INPUT OUTPUT
#define DB4LAT 		LATBbits.LATB12             // FOR WRITE

#define DB5    		PORTBbits.RB13             // FOR READ
#define DB5IO  		TRISBbits.TRISB13           // FOR INPUT OUTPUT
#define DB5LAT 		LATBbits.LATB13             // FOR WRITE

#define DB6    		PORTBbits.RB14              // FOR READ
#define DB6IO  		TRISBbits.TRISB14           // FOR INPUT OUTPUT
#define DB6LAT 		LATBbits.LATB14             // FOR WRITE

#define DB7    		PORTBbits.RB15              // FOR READ
#define DB7IO  		TRISBbits.TRISB15           // FOR INPUT OUTPUT
#define DB7LAT 		LATBbits.LATB15             // FOR WRITE

//#define LCDDATA    PORTD                     // FOR READ
//#define LCDDATAIO  TRISD                     // FOR INPUT OUTPUT
//#define LCDDATALAT LATD                      // FOR WRITE

//**************************************************************************************
//FOR DAC INTERFACE***********************************************************************
#define DACSCK	      	PORTGbits.RG6         // FOR READ
#define DACSCKIO    	TRISGbits.TRISG6     // FOR INPUT OUTPUT
#define DACSCKLAT  	 	LATGbits.LATG6      // FOR WRITE

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
#define GASRELAY      	PORTDbits.RD2         // FOR READ
#define GASRELAYIO    	TRISDbits.TRISD2      // FOR INPUT OUTPUT
#define GASRELAYLAT1  	 LATDbits.LATD2        // FOR WRITE

#define HFRELAY      	PORTDbits.RD3         // FOR READ
#define HFRELAYIO    	TRISDbits.TRISD3      // FOR INPUT OUTPUT
#define HFRELAYLAT1   	LATDbits.LATD3        // FOR WRITE

#define ARCON    		PORTFbits.RF7	    	//PORTDbits.RD4		//for read data	
#define ARCONIO   		TRISFbits.TRISF7 	//TRISDbits.TRISD4 	//For direction
#define ARCONLAT  		LATFbits.LATF7   	//LATDbits.LATD4		//for write data

#define DECOD_EN		PORTBbits.RB6		//for read data	
#define DECOD_ENIO   	TRISBbits.TRISB6 	//For direction
#define DECOD_ENLAT 	LATBbits.LATB6		//for write data

//#define MCOK		 	PORTBbits.RB6		//for read data	
//#define MCOKIO   		TRISBbits.TRISB6 	//For direction
//#define MCOKLAT 		LATBbits.LATB6		//for write data

#define ARCONOK    		PORTBbits.RB7	    	//PORTDbits.RD4		//for read data	
#define ARCONOKIO   	TRISBbits.TRISB7 	//TRISDbits.TRISD4 	//For direction
#define ARCONOKLAT		LATBbits.LATB7   	//LATDbits.LATD4	//for write data

#define GASWATERIP 	 	PORTCbits.RC4	    //PORTDbits.RD4		//for read data	1:water 0:gas cooled
#define GASWATERIPIO 	TRISCbits.TRISC4 	//TRISDbits.TRISD4 	//For direction
#define GASWATERIPLAT  	LATCbits.LATC4   	//LATDbits.LATD4	//for write data

#define PRESSERRIP 		PORTCbits.RC13	    //PORTDbits.RD4	//for read data	1:water cooling off; 0:water cooling on;
#define PRESSERRIPIO   	TRISCbits.TRISC13 	//TRISDbits.TRISD4 	//For direction
#define PRESSERRIPLAT	LATCbits.LATC13   	//LATDbits.LATD4	//for write data

#define TORCHTEST1IP    PORTCbits.RC15	    	//PORTDbits.RD4		//for read data	
#define TORCHTEST1IPIO  TRISCbits.TRISC15 	//TRISDbits.TRISD4 	//For direction
#define TORCHTEST1IOLAT	LATCbits.LATC15   	//LATDbits.LATD4	//for write data

#define INCHTESTIP	    PORTFbits.RF8	    	//PORTDbits.RD4		//for read data	
#define INCHTESTIPIO   	TRISFbits.TRISF8 	//TRISDbits.TRISD4 	//For direction
#define INCHTESTIPLAT	LATFbits.LATF8   	//LATDbits.LATD4	//for write data

#define PULSEIP    		PORTDbits.RD8	    	//PORTDbits.RD4		//for read data	
#define PULSEIPIO   	TRISDbits.TRISD8 	//TRISDbits.TRISD4 	//For direction
#define PULSEIPLAT		LATDbits.LATD8   	//LATDbits.LATD4	//for write data

#define MOVLDIP    		PORTCbits.RC14	    //PORTDbits.RD4		//for read data	
#define MOVLDIPIO  		TRISCbits.TRISC14 	//TRISDbits.TRISD4 	//For direction
#define MOVLDIPLAT		LATCbits.LATC14   	//LATDbits.LATD4	//for write data

#define SHDN    		PORTDbits.RD0	    //PORTDbits.RD4		//for read data	
#define SHDNIO   		TRISDbits.TRISD0 	//TRISDbits.TRISD4 	//For direction
#define SHDNLAT			LATDbits.LATD0   	//LATDbits.LATD4	//for write data

//#define MPWM    		PORTDbits.RD1	    //PORTDbits.RD4		//for read data	
//#define MPWMIO   		TRISDbits.TRISD1 	//TRISDbits.TRISD4 	//For direction
//#define MPWMLAT		LATDbits.LATD1   	//LATDbits.LATD4	//for write data

#define SCL    			PORTDbits.RD1	    //PORTDbits.RD4		//for read data	
#define SCLIO   		TRISDbits.TRISD1 	//TRISDbits.TRISD4 	//For direction
#define SCLLAT			LATDbits.LATD1   	//LATDbits.LATD4	//for write data
#define SDA	    		PORTBbits.RB4	    //PORTDbits.RD4		//for read data	
#define SDAIO	  		TRISBbits.TRISB4 	//TRISDbits.TRISD4 	//For direction
#define SDALAT			LATBbits.LATB4   	//LATDbits.LATD4	//for write data

#define EXTINT1IP		PORTAbits.RA12		//for read data	
#define EXTINT1IO   	TRISAbits.TRISA12 	//For direction
#define EXTINT1LAT 		LATAbits.LATA12		//for write data

#define EXTINT2IP    	PORTAbits.RA13	    //PORTDbits.RD4		//for read data	
#define EXTINT2IO   	TRISAbits.TRISA13	//TRISDbits.TRISD4 	//For direction
#define EXTINT2LAT		LATAbits.LATA13   	//LATDbits.LATD4	//for write data

#define CCCVCTRL	 	PORTFbits.RF6		//for read data	
#define CCCVCTRLIO   	TRISFbits.TRISF6 	//For direction
#define CCCVCTRLLAT 	LATFbits.LATF6		//for write data

/*
#define EXTRA2    		PORTAbits.RA9	    	//PORTDbits.RD4		//for read data	
#define EXTRA2IO   		TRISAbits.TRISA9 	//TRISDbits.TRISD4 	//For direction
#define EXTRA2LAT		LATAbits.LATA9   	//LATDbits.LATD4	//for write data
*/

//#define avgcnt         	1024  //64    

#define	LEFTSHIFT		11     //10 	//12  // 8//10//13
#define AVGCNT			2048 //1024 //4096 //256//1024//8192
#define	CCMODE		1
#define CVMODE			0
#define ON				1
#define	OFF				0
#define set				1

#define	CCOFFSETNEW	  46.47 //44.15 //0.4   
#define CCSLOPENEW	  4.559 //7.454 //6.702 

#define MIN_BASE_AMP 20
#define MIN_FREQ 10

#define MAX_BASE_AMP 90

#define TX_DATA_LENGTH 22

#define CVOFFSET	140.0  //520 //700.2
#define CVSLOPE		8.90 //4.490

#define MINI_SAVE_COUNT 1
#define MAX_SAVE_COUNT  100

#define MINI_RECALL_COUNT 1
#define MAX_RECALL_COUNT  100

#define ER_DEBOUNCE_TIME  5

#define ERROR4_DEBOUNCE_TIME 8000

#define COMMUNICATION_TIME_OUT 4000  //mSec

#define ERROR_4_THRESHOLD 15 //Amps

#define ARC_ON_RESET_COUNT_LIMIT 250//20MSEC*250 ==5000SEC
#define PASSWORD_SET_COUNT_LIMIT 250//20MSEC*250 ==5000SEC

#define MASTER_PASSWORD 1469
#define PWSTARBLINKCNT  3
//-------------------------------------------------------
//EEPROM ADDRESS LOCATION
#define E2P_SERIALPORTTASK_ADDR		120
//-------------------------------------------------------
#define LOADREFCNT 			20
#define LOADFREQCNT 		20
//-------------------------------
#define ENPULSECNT			10
//-------------------------------
#define CHARDELAY3BY5		50
#define SLAVEADDRESS		1
#define STARTADDRESS		0x1000
//------------------------------------------------------
// HMI address
#define HMI_VOLATGE				0x00
#define HMI_WIRESPEED			0x01
#define HMI_CURRENT				0x02
#define HMI_DIA					0x03
#define HMI_GAS					0x04
#define HMI_MAT					0x05
#define HMI_ARCLENGTH			0x06

#define HMI_ACT_CURRENT			0x08
#define HMI_ACT_VOLTAGE			0x09
//-------------------------------------------------------
#define KEYDOUBLECHKCNT			1000
#define MACMENUCNTR				3
#define DATAPOSITION			80
//-------------------------------------------------------
//#define disvolt_cnt    	8192  //4096   
//#define loop           		1024  
//#define set            		1            
//#define max_pwm_limit	1500 //2500 //1500 //2500
//#define min_pwm_limit	310
/*

#define EE_bSIZE  			0x1000				//0x0400            	// 1024 Bytes  dsPIC30F5011 specific
#define EE_wSIZE  			0x0800				//0x0200            	// 512 words  dsPIC30F5011 specific
#define EE_START_ADDR  		0x7FF000            //0x7FFC00       		// dsPIC30F5011 specific
#define EE_END_ADDR  		0x7FFFFE            //0x800000
#define EEPROM_ROW_SIZE 	16           		// dsPIC30F EEPROM ROW size
*/

//-----------------------------------------------------------------------------
#define ADOR_DATA			1469
// E2p Address
#define ADOR_WRL				0x0000
#define ADOR_WRH				0x0001	
#define PROGRAM_ADDR		0x0012
#define MPROGRAM_ADDR		0x0010
//-----------------------------------------------------------------------------


//------------------EEPROM_INTERFACING-----------------------------------------
//First 150    	Address for Spare Purpose
//PULSE MIG    	Start_Address => 2(0x97)     End_Address => 500(0x01258D)
//MIG		   	Start_Address => 501(0x0124F9)   End_Address => 800(0x01BB77)
//Free address  0x01BB78 to 0x01FFFF
#define E2POFFSET						170
// E2p address list
#define PROG_NO							1
#define WELD_MODE						PROG_NO+2
#define PROG_NAME						WELD_MODE+1
#define GAS_DIA							PROG_NAME+10
#define SYN_DATA						GAS_DIA+1
#define PMIG_PARA						SYN_DATA+27*4
#define FACTORS							PMIG_PARA + 15*2
#define FRAME_GAP						42*500
#define FRAME_GAP_root					43*500

//----------------------------------------------------------------------------

#define mE2POFFSET						128
#define mPROG_NO						1
#define mWELD_MODE						mPROG_NO+2
#define mPROG_NAME						mWELD_MODE+1
#define mGAS_DIA						mPROG_NAME+10
#define mSYN_DATA						mGAS_DIA+1
#define MAX_WS							mSYN_DATA+27*4


#define TOTAL_PROGRAMS					52
//----------------------------------------------------------------------------

#define MATCH_DATA						17
#define MATCH_LOCATION					17

//----------------------------------------------------------------------------

#define MIN_LOAD_LOCATION				1
#define MAX_LOAD_LOCATION 				48

#define MIN_STORE_LOCATION				51
#define MAX_STORE_LOCAION				100

//-----------------------------------------------------------------------------



