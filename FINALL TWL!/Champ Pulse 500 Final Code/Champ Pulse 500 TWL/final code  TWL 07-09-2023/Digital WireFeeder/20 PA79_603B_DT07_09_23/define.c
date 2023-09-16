//#define PA603_A //PA603

#define RECEIVE_STRING_LENGTH 22
#define TRANSMIT_STRING_LENGTH 22
#define MTR_VTG_CONSTANT 	 	  11.0 //11.5     //10.70 //10.20	//2.8//3.2//3.65  //3.4
#define MTROVLDTIME     		1000
#define MTR_FREQ_CONSTANT  		3.4//4//6.5//2.5
#define MAX_P_FB_FREQ 			999//999


#define SEGA 		PORTBbits.RB0
#define SEGAIO		TRISBbits.TRISB0
#define SEGALAT		LATBbits.LATB0

#define SEGB		PORTBbits.RB1
#define SEGBIO		TRISBbits.TRISB1
#define SEGBLAT		LATBbits.LATB1

#define SEGC		PORTBbits.RB2
#define SEGCIO		TRISBbits.TRISB2
#define SEGCLAT		LATBbits.LATB2

#define SEGD		PORTBbits.RB3
#define SEGDIO		TRISBbits.TRISB3
#define SEGDLAT		LATBbits.LATB3

#define SEGE		PORTBbits.RB4
#define SEGEIO		TRISBbits.TRISB4
#define SEGELAT		LATBbits.LATB4

#define SEGF		PORTBbits.RB5
#define SEGFIO		TRISBbits.TRISB5
#define SEGFLAT		LATBbits.LATB5

#define SEGG		PORTBbits.RB6
#define SEGGIO		TRISBbits.TRISB6
#define SEGGLAT		LATBbits.LATB6

#define SEGDP		PORTBbits.RB7
#define SEGDPIO		TRISBbits.TRISB7
#define SEGDPLAT	LATBbits.LATB7

#define DECODA		PORTFbits.RF6
#define DECODAIO	TRISFbits.TRISF6
#define DECODALAT	LATFbits.LATF6

#define DECODB		PORTFbits.RF0	
#define DECODBIO	TRISFbits.TRISF0
#define DECODBLAT	LATFbits.LATF0

#define DECODC		PORTDbits.RD3
#define DECODCIO	TRISDbits.TRISD3
#define DECODCLAT	LATDbits.LATD3

#define DECODEN		PORTDbits.RD2
#define DECODENIO	TRISDbits.TRISD2
#define DECODENLAT	LATDbits.LATD2

#define GAS_RLY 		PORTFbits.RF1
#define GAS_RLYIO		TRISFbits.TRISF1
#define GAS_RLYLAT		LATFbits.LATF1

#define TORCH_SEL 		PORTCbits.RC15
#define TORCH_SELIO		TRISCbits.TRISC15
#define TORCH_SELLAT 	LATCbits.LATC15

#define TX1IO			TRISCbits.TRISC13
#define RX1IO			TRISCbits.TRISC14
#define TX2IO			TRISFbits.TRISF5
#define RX2IO			TRISFbits.TRISF4

//FOR ENCODER
#define ENCODER2A	    PORTDbits.RD8 
#define ENCODER2B	    PORTAbits.RA11
#define ENCODER2AIO 	TRISDbits.TRISD8	//For direction
#define ENCODER2BIO 	TRISAbits.TRISA11	//For direction
#define ENCODER2ALAT	LATDbits.LATD8		//for write data
#define ENCODER2BLAT	LATAbits.LATA11		//for write data

#define ENCODER1A	    PORTFbits.RF3
#define ENCODER1B	    PORTFbits.RF2
#define ENCODER1AIO 	TRISFbits.TRISF3	//For direction
#define ENCODER1BIO 	TRISFbits.TRISF2	//For direction
#define ENCODER1ALAT	LATFbits.LATF3	    //for write data
#define ENCODER1BLAT	LATFbits.LATF2 	//for write data


#define TORCHIN				PORTBbits.RB8
#define TRISTORCHIN			TRISBbits.TRISB8
#define TORCHIN_LAT			LATBbits.LATB8

#define MOTOR_TRIP11		PORTBbits.RB10
#define MOTOR_TRIP_LAT      LATBbits.LATB10
#define TRISMOTOR_TRIP11    TRISBbits.TRISB10

#define MPULSE_FB			PORTDbits.RD9       
#define TRISMPULSE  		TRISDbits.TRISD9
#define MPULSE_FBLAT 		LATDbits.LATD9

/*

#define TORCHSEL    PORTCbits.RC15// for TORCHSEL ADDED on 12072023 KK
#define TORCHSELIO  TRISCbits.TRISC15
#define TORCHSELLAT LATCbits.LATC15

#define MPULSE          PORTDbits.RD9


#define TORCHIN         PORTBbits.RB8
#define TRISTORCHIN     TRISBbits.TRISB8

#define TRISMPULSE      TRISDbits.TRISD9
#define TRISGAS_RLY     TRISFbits.TRISF1



#define ENCODER1A       PORTFbits.RF3           
#define ENCODER1B       PORTAbits.RA11
#define ENCODER2A       PORTDbits.RD8
#define ENCODER2B       PORTFbits.RF2

#define TRISEN1A        TRISDbits.TRISD8
#define TRISEN1B        TRISAbits.TRISA11
#define TRISEN2A        TRISFbits.TRISF3
#define TRISEN2B        TRISFbits.TRISF2

#define PORTBSTATUS     PORTB
#define OUTPORTB        LATB

#define MTRFB           PORTBbits.RB9
#define TRISMTRFB       TRISBbits.TRISB9

//#define MTR_FREQ_CONSTANT  3.25   //3.25//2.7//3.58  //3.58 //modified for pulse proto to coimbtore

#define MTR_FREQ_CONSTANT  3.4//4//6.5//2.5
#define MTR_VTG_CONSTANT 2.8//2.9//2.8//3.4//2.8//1.2//1.4//    changed on 230919
#define MAX_P_FB_FREQ 999//999



#define RECEIVE_STRING_LENGTH 22


#ifdef PA603_A

    
    #define MOTOR_TRIP11        PORTBbits.RB10
    #define TRISMOTOR_TRIP11    TRISBbits.TRISB10
#else
    #define DECODE_A        LATBbits.LATB10
    #define TRISMOTOR_TRIP11    TRISFbits.TRISF6
    #define MOTOR_TRIP11        PORTFbits.RF6
#endif


#endif
*/




