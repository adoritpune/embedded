#define ROW0 		PORTDbits.RD0		//for read data
#define ROW1 		PORTDbits.RD1		//for read data
#define ROW2 		PORTDbits.RD2		//for read data
#define ROW3 		PORTBbits.RB0		//for read data

#define COLUMN0 	PORTCbits.RC2		//for read data
#define COLUMN1 	PORTFbits.RF6 		//for read data
#define COLUMN2 	PORTDbits.RD5		//for read data
#define COLUMN3 	PORTDbits.RD6		//for read data

#define ROW0IO		TRISDbits.TRISD0	//For direction
#define ROW1IO		TRISDbits.TRISD1	//For direction
#define ROW2IO		TRISDbits.TRISD2	//For direction
#define ROW3IO		TRISBbits.TRISB0	//For direction

#define COLUMN0IO  	TRISCbits.TRISC2	//For direction
#define COLUMN1IO  	TRISFbits.TRISF6	//For direction
#define COLUMN2IO  	TRISDbits.TRISD5	//For direction
#define COLUMN3IO  	TRISDbits.TRISD6	//For direction

#define ROW0LAT		LATDbits.LATD0		//for write data
#define ROW1LAT		LATDbits.LATD1		//for write data
#define ROW2LAT		LATDbits.LATD2		//for write data
#define ROW3LAT		LATBbits.LATB0		//for write data

#define COLUMN0LAT	LATCbits.LATC2		//for write data
#define COLUMN1LAT	LATFbits.LATF6		//for write data
#define COLUMN2LAT	LATDbits.LATD5		//for write data
#define COLUMN3LAT	LATDbits.LATD6		//for write data

//#define KEYINT		PORTDbits.RD10
//#define KEYINTLAT	LATDbits.LATD10		//for write data
//#define KEYINTIO  	TRISDbits.TRISD10	//For direction

#define ENCODERA		PORTDbits.RD8
#define ENCODERB		PORTDbits.RD9 
#define ENCODERALAT	LATDbits.LATD8 		//for write data
#define ENCODERBLAT	LATDbits.LATD9 		//for write data
#define ENCODERAIO 	TRISDbits.TRISD8 	//For direction
#define ENCODERBIO 	TRISDbits.TRISD9 	//For direction

#define ENCODER    		 PORTD
#define ENCODERIO		TRISD
#define set 		1
/*
#define REMOTEA		PORTFbits.RF4
#define REMOTEB		PORTFbits.RF5 
#define REMOTEALAT	LATFbits.LATF4 		//for write data
#define REMOTEBLAT	LATFbits.LATF5 		//for write data
#define REMOTEAIO 	TRISFbits.TRISF4 	//For direction
#define REMOTEBIO 	TRISFbits.TRISF5 	//For direction
#define REMOTEENC   PORTF
#define REMOTEENCIO	TRISF
#define THERMALIN	 PORTCbits.RC1		//for read data	
#define THERMALINLAT LATCbits.LATC1		//for write data
#define THERMALINIO TRISCbits.TRISC1 	//For direction
*/
#define SW1		    	PORTFbits.RF4		//for read data	
#define SW1LAT			LATFbits.LATF4 		//for write data
#define SW1IO 			TRISFbits.TRISF4 	//For direction
#define SW2		    	PORTFbits.RF5		//for read data	
#define SW2LAT			LATFbits.LATF5 		//for write data
#define SW2IO 			TRISFbits.TRISF5 	//For direction
//#define SW3		    	PORTCbits.RC1		//for read data	
//#define SW3LAT 		LATCbits.LATC1		//for write data
//#define SW3IO 			TRISCbits.TRISC1 	//For direction
//
#define ENCODER1		PORTB
#define ENCODER1A		PORTBbits.RB6
#define ENCODER1B		PORTBbits.RB7 
#define ENCODER1ALAT	LATBbits.LATB6 		//for write data
#define ENCODER1BLAT	LATBbits.LATB7 		//for write data
#define ENCODER1AIO 	TRISBbits.TRISB6 	//For direction
#define ENCODER1BIO 	TRISBbits.TRISB7 	//For direction

//#define REMOTE1ALAT		LATDbits.LATD10 		//for write data
#define REMOTE1BLAT		LATDbits.LATD11 		//for write data
//#define REMOTE1AIO 		TRISDbits.TRISD10 	//For direction
#define REMOTE1BIO 		TRISDbits.TRISD11 	//For direction

#define DIGIT0		PORTGbits.RG0		//for read data	
#define DIGIT0LAT	LATGbits.LATG0		//for write data
#define DIGIT0IO  	TRISGbits.TRISG0 	//For direction
#define DIGIT1		PORTGbits.RG1		//for read data	
#define DIGIT1LAT	LATGbits.LATG1		//for write data
#define DIGIT1IO  	TRISGbits.TRISG1 	//For direction
#define DIGIT2		PORTGbits.RG6		//for read data
#define DIGIT2LAT	LATGbits.LATG6		//for write data
#define DIGIT2IO  	TRISGbits.TRISG6 	//For direction
#define DIGIT3		PORTGbits.RG7		//for read data
#define DIGIT3LAT	LATGbits.LATG7		//for write data
#define DIGIT3IO  	TRISGbits.TRISG7 	//For direction
#define DIGIT4		PORTGbits.RG8		//for read data
#define DIGIT4LAT	LATGbits.LATG8		//for write data
#define DIGIT4IO  	TRISGbits.TRISG8 	//For direction
#define DIGIT5		PORTGbits.RG9		//for read data
#define DIGIT5LAT	LATGbits.LATG9		//for write data
#define DIGIT5IO  	TRISGbits.TRISG9 	//For direction
#define DIGIT6		PORTGbits.RG12		//for read data
#define DIGIT6LAT	LATGbits.LATG12		//for write data
#define DIGIT6IO  	TRISGbits.TRISG12 	//For direction
#define DIGIT7		PORTGbits.RG13		//for read data
#define DIGIT7LAT	LATGbits.LATG13		//for write data
#define DIGIT7IO  	TRISGbits.TRISG13	//For direction
#define DIGIT8		PORTGbits.RG14		//for read data
#define DIGIT8LAT	LATGbits.LATG14		//for write data
#define DIGIT8IO  	TRISGbits.TRISG14	//For direction
#define DIGIT9		PORTGbits.RG15		//for read data
#define DIGIT9LAT	LATGbits.LATG15		//for write data
#define DIGIT9IO  	TRISGbits.TRISG15	//For direction
#define DIGIT10		PORTFbits.RF0		//for read data
#define DIGIT10LAT	LATFbits.LATF0		//for write data
#define DIGIT10IO  	TRISFbits.TRISF0	//For direction

#define SEGA		PORTBbits.RB8        //RD10		//for read data	
#define SEGALAT	LATBbits.LATB8		//for write data
#define SEGAIO  	TRISBbits.TRISB8 	//For direction
#define SEGB		PORTDbits.RD11		//for read data	
#define SEGBLAT	LATDbits.LATD11		//for write data
#define SEGBIO  	TRISDbits.TRISD11 	//For direction
#define SEGC		PORTDbits.RD4  	    //for read data	
#define SEGCLAT	LATDbits.LATD4		//for write data
#define SEGCIO  	TRISDbits.TRISD4 	//For direction
#define SEGD		PORTBbits.RB11		//for read data	
#define SEGDLAT	LATBbits.LATB11		//for write data
#define SEGDIO  	TRISBbits.TRISB11 	//For direction
#define SEGE		PORTBbits.RB12		//for read data	
#define SEGELAT	LATBbits.LATB12		//for write data
#define SEGEIO  	TRISBbits.TRISB12 	//For direction
#define SEGF		PORTBbits.RB13		//for read data	
#define SEGFLAT	LATBbits.LATB13		//for write data
#define SEGFIO  	TRISBbits.TRISB13 	//For direction
#define SEGG		PORTBbits.RB14		//for read data	
#define SEGGLAT	LATBbits.LATB14		//for write data
#define SEGGIO  	TRISBbits.TRISB14 	//For direction
#define SEGH		PORTBbits.RB15		//for read data	
#define SEGHLAT	LATBbits.LATB15		//for write data
#define SEGHIO  	TRISBbits.TRISB15 	//For direction

#define GASON		 PORTBbits.RB4		//for read data	
#define GASONLAT	 LATBbits.LATB4		//for write data
#define GASONIO  	 TRISBbits.TRISB4 	//For direction

//#define CONTACTORON	 PORTCbits.RC13		//for read data	
//#define CONTACTORLAT LATCbits.LATC13	//for write data
//#define CONTACTORIO  TRISCbits.TRISC13 	//For direction

/*
#define TIGON	 		PORTCbits.RC14		//for read data	
#define TIGLAT   		LATCbits.LATC14	//for write data
#define TIGIO    		TRISCbits.TRISC14 	//For direction
*/



#define TORCHON		PORTBbits.RB3		//for read data	
#define TORCHONLAT	LATBbits.LATB3		//for write data
#define TORCHONIO  	TRISBbits.TRISB3 	//For direction

#define PRESSURE		PORTFbits.RF1		//for read data	
#define PRESSURELAT	LATFbits.LATF1		//for write data
#define PRESSUREIO  	TRISFbits.TRISF1 	//For direction

#define GWSW		 	PORTBbits.RB9		//for read data	
#define GWSWLAT	 	LATBbits.LATB9		//for write data
#define GWSWIO  	 	TRISBbits.TRISB9 	//For direction

#define VRDRELAY		PORTCbits.RC14		//for read data	
#define VRDRELAYLAT 	LATCbits.LATC14	//for write data
#define VRDRELAYIO 	TRISCbits.TRISC14 	//For direction

#define WSAMPSW		PORTCbits.RC1		//for read data	
#define WSAMPSWLAT 	LATCbits.LATC1		//for write data
#define WSAMPIO 		TRISCbits.TRISC1 	//For direction

#define MOTOROVLD		PORTDbits.RD10		//for read data	
#define MOTOROVLDLAT	LATDbits.LATD10	//for write data
#define MOTOROVLDIO  	TRISDbits.TRISD10 	//For direction

//#define VRDBYPASS		PORTDbits.RD10		//for read data	
//#define VRDBYPASSLAT	LATDbits.LATD10	//for write data
//#define VRDBYPASSIO  	TRISDbits.TRISD10 	//For direction

//#define PWMON		 PORTFbits.RF1		//for read data	
//#define PWMONLAT	 LATFbits.LATF1		//for write data
//#define PWMONIO  	 TRISFbits.TRISF1 	//For direction

#define loop 		4096  //1024 //1024 //2048 //4096 //2048 //1024	//for averaging the adc count
#define update      	8192 //8192 //4096				    //for display updating	

#define loopm		128 //1024
#define updatem     256 //1024

#define twoseccnt	16 //16					16 mesr count for calculation of autupwm				 	//for 2 sec. count is 25		
#define window      	0.4 //3 //0.2		//1.0 voltage window for autocalculation.
#define REJECTCNT  4 //4 //4   // 5            //5 for neglecting welding vtg at start of welding cycle		

#define	arcforcehi	30
#define	arcforcelo	0

#define	WFPWMCALFACTOR	3.0

//#define INCHINGON	 PORTDbits.RD11		//for read data	
//#define INCHINGONLAT LATDbits.LATD11	//for write data
//#define INCHINGONIO  TRISDbits.TRISD11 	//For direction

#define CCCVCTRL	 	PORTCbits.RC15		//for read data	
#define CCCVCTRLLAT 	LATCbits.LATC15	//for write data
#define CCCVCTRLIO   	TRISCbits.TRISC15 	//For direction

#define ARCON    		PORTCbits.RC13	    //PORTDbits.RD4		//for read data	
#define ARCONLAT  		LATCbits.LATC13   //LATDbits.LATD4		//for write data
#define ARCONIO   		TRISCbits.TRISC13 //TRISDbits.TRISD4 	//For direction

