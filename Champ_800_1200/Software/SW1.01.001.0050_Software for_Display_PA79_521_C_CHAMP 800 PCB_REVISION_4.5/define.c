//FOR CATHODES
//************************************************************************************************************
#define CATHODE1    	PORTGbits.RG0              // FOR READ
#define CATHODE1IO  	TRISGbits.TRISG0           // FOR INPUT OUTPUT
#define CATHODE1LAT 	LATGbits.LATG0             // FOR WRITE  

#define CATHODE2    	PORTGbits.RG1              // FOR READ
#define CATHODE2IO  	TRISGbits.TRISG1           // FOR INPUT OUTPUT
#define CATHODE2LAT 	LATGbits.LATG1             // FOR WRITE  

#define CATHODE3    	PORTGbits.RG2              // FOR READ
#define CATHODE3IO  	TRISGbits.TRISG2           // FOR INPUT OUTPUT
#define CATHODE3LAT 	LATGbits.LATG2             // FOR WRITE  

#define CATHODE4    	PORTGbits.RG3              // FOR READ
#define CATHODE4IO  	TRISGbits.TRISG3           // FOR INPUT OUTPUT
#define CATHODE4LAT	 	LATGbits.LATG3             // FOR WRITE  

#define CATHODE5    	PORTGbits.RG6              // FOR READ
#define CATHODE5IO  	TRISGbits.TRISG6           // FOR INPUT OUTPUT
#define CATHODE5LAT 	LATGbits.LATG6             // FOR WRITE  

#define CATHODE6    	PORTGbits.RG7              // FOR READ
#define CATHODE6IO  	TRISGbits.TRISG7           // FOR INPUT OUTPUT
#define CATHODE6LAT 	LATGbits.LATG7             // FOR WRITE  

#define CATHODE7    	PORTGbits.RG8              // FOR READ
#define CATHODE7IO  	TRISGbits.TRISG8           // FOR INPUT OUTPUT
#define CATHODE7LAT 	LATGbits.LATG8             // FOR WRITE  

#define CATHODE8    	PORTGbits.RG9              // FOR READ
#define CATHODE8IO  	TRISGbits.TRISG9           // FOR INPUT OUTPUT
#define CATHODE8LAT 	LATGbits.LATG9             // FOR WRITE  

#define TRIPLED     	PORTGbits.RG12              // FOR READ
#define TRIPLEDIO   	TRISGbits.TRISG12           // FOR INPUT OUTPUT
#define TRIPLEDLAT  	LATGbits.LATG12             // FOR WRITE  

#define MMALED      	PORTGbits.RG13              // FOR READ
#define MMALEDIO    	TRISGbits.TRISG13           // FOR INPUT OUTPUT
#define MMALEDLAT   	LATGbits.LATG13             // FOR WRITE  

#define SAWLED      	PORTGbits.RG14              // FOR READ
#define SAWLEDIO    	TRISGbits.TRISG14           // FOR INPUT OUTPUT
#define SAWLEDLAT   	LATGbits.LATG14             // FOR WRITE  

#define REMOTELED    	PORTGbits.RG15              // FOR READ
#define REMOTELEDIO  	TRISGbits.TRISG15           // FOR INPUT OUTPUT
#define REMOTELEDLAT 	LATGbits.LATG15             // FOR WRITE  
//******************************************************************************************************************
//FOR SEGMENT LED'S
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
#define TORCHSW	    	PORTBbits.RB9		//TORCH SWITCH DETECTION
#define TORCHSWLAT		LATBbits.LATB9		//for write data
#define TORCHSWIO 		TRISBbits.TRISB9	//For direction

#define INCHSW	    	PORTBbits.RB10		//EXTERNALLY INCH SWITCH
#define INCHSWLAT		LATBbits.LATB10		//for write data
#define INCHSWIO 		TRISBbits.TRISB10	//For direction

#define MOVLD	    	PORTBbits.RB12		//MOTOR OVERLOADING SIGNAL
#define MOVLDLAT		LATBbits.LATB12		//for write data
#define MOVLDIO 		TRISBbits.TRISB12	//For direction

#define GASRELAY	    PORTBbits.RB13		//MOTOR OVERLOADING SIGNAL
#define GASRELAYLAT		LATBbits.LATB13		//for write data
#define GASRELAYIO 		TRISBbits.TRISB13	//For direction

#define TMODESW	    	PORTCbits.RC13		//DETECTION OF 2T 4T SWITCH
#define TMODESWLAT		LATCbits.LATC13	//for write data
#define TMODESWIO 		TRISCbits.TRISC13	//For direction

#define GASCHKSW 		PORTCbits.RC14		//GAS CHECK SWITCH.
#define GASCHKSWLAT		LATCbits.LATC14	//for write data
#define GASCHKSWIO 		TRISCbits.TRISC14	//For direction

#define NC1	    PORTCbits.RC1		//MOTOR OVERLOADING SIGNAL
#define NC1LAT	LATCbits.LATC1	//for write data
#define NC1IO 	TRISCbits.TRISC1	//For direction



//****************************************************************************************************************
#define avgcnt         	4    
#define disvolt_cnt    	4096   
#define loop           	4096  
#define set            	1
#define CCMODE		1
#define CVMODE		0
#define MMAMODE	1
#define	MIGMODE	2
#define	SAWMODE	3


#define VTG_AVG_COUNT 256
#define VTG_AVG_SHIFT 8

#define HOT_STRT_TIME    500
#define HOTSTRT_PERCNT_1 15
#define HOTSTRT_PERCNT_2 15  //@ not used

#define DISPOFFSET	20
#define DISPSLOPE	5