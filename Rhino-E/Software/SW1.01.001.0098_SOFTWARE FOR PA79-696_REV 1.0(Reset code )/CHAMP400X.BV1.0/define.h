#include "pic18f46k40.h"


//FOR SEGMENT LED'S

#define SEGA      	PORTDbits.RD0           // FOR READ
#define SEGAIO    	TRISDbits.TRISD0		// FOR INPUT OUTPUT
#define SEGALAT   	LATDbits.LATD0			// FOR WRITE 

#define SEGB      	PORTDbits.RD1    		// FOR READ
#define SEGBIO    	TRISDbits.TRISD1		// FOR INPUT OUTPUT
#define SEGBLAT   	LATDbits.LATD1			// FOR WRITE 

#define SEGC      	PORTDbits.RD2			// FOR READ
#define SEGCIO    	TRISDbits.TRISD2		// FOR INPUT OUTPUT
#define SEGCLAT   	LATDbits.LATD2			// FOR WRITE 

#define SEGD      	PORTDbits.RD3			// FOR READ
#define SEGDIO    	TRISDbits.TRISD3		// FOR INPUT OUTPUT
#define SEGDLAT   	LATDbits.LATD3			// FOR WRITE 

#define SEGE      	PORTDbits.RD4			// FOR READ
#define SEGEIO    	TRISDbits.TRISD4		// FOR INPUT OUTPUT
#define SEGELAT  	LATDbits.LATD4			// FOR WRITE 

#define SEGF      	PORTDbits.RD5			// FOR READ
#define SEGFIO    	TRISDbits.TRISD5		// FOR INPUT OUTPUT
#define SEGFLAT   	LATDbits.LATD5			// FOR WRITE 

#define SEGG      	PORTDbits.RD6			// FOR READ
#define SEGGIO    	TRISDbits.TRISD6		// FOR INPUT OUTPUT
#define SEGGLAT   	LATDbits.LATD6          // FOR WRITE 

#define SEGDP      	PORTDbits.RD7			// FOR READ
#define SEGDPIO    	TRISDbits.TRISD7		// FOR INPUT OUTPUT
#define SEGDPLAT   	LATDbits.LATD7			// FOR WRITE 

#define SEL1        PORTBbits.RB0           // FOR READ
#define SEL1IO      TRISBbits.TRISB0		// FOR INPUT OUTPUT
#define SEL1LAT     LATBbits.LATB0			// FOR WRITE 

#define SEL2        PORTBbits.RB1           // FOR READ
#define SEL2IO      TRISBbits.TRISB1		// FOR INPUT OUTPUT
#define SEL2LAT     LATBbits.LATB1			// FOR WRITE 

#define SEL3        PORTBbits.RB2           // FOR READ
#define SEL3IO      TRISBbits.TRISB2		// FOR INPUT OUTPUT
#define SEL3LAT     LATBbits.LATB2			// FOR WRITE 

#define SEL4        PORTBbits.RB4           // FOR READ
#define SEL4IO      TRISBbits.TRISB4		// FOR INPUT OUTPUT
#define SEL4LAT     LATBbits.LATB4			// FOR WRITE 

#define SEL6        PORTAbits.RA7           // FOR READ
#define SEL6IO      TRISAbits.TRISA7		// FOR INPUT OUTPUT
#define SEL6LAT     LATAbits.LATA7			// FOR WRITE 

#define SEL7        PORTAbits.RA6           // FOR READ
#define SEL7IO      TRISAbits.TRISA6		// FOR INPUT OUTPUT
#define SEL7LAT     LATAbits.LATA6			// FOR WRITE 

#define SEL5        PORTCbits.RC1           // FOR READ
#define SEL5IO      TRISCbits.TRISC1		// FOR INPUT OUTPUT
#define SEL5LAT     LATCbits.LATC1			// FOR WRITE 

/*
#define SEL5        PORTAbits.RA7           // FOR READ
#define SEL5IO      TRISAbits.TRISA7		// FOR INPUT OUTPUT
#define SEL5LAT     LATAbits.LATA7			// FOR WRITE 

#define SEL6        PORTAbits.RA6           // FOR READ
#define SEL6IO      TRISAbits.TRISA6		// FOR INPUT OUTPUT
#define SEL6LAT     LATAbits.LATA6			// FOR WRITE 

#define SEL7        PORTCbits.RC1           // FOR READ
#define SEL7IO      TRISCbits.TRISC1		// FOR INPUT OUTPUT
#define SEL7LAT     LATCbits.LATC1			// FOR WRITE 
*/

#define SEL8        PORTAbits.RA3           // FOR READ
#define SEL8IO      TRISAbits.TRISA3		// FOR INPUT OUTPUT
#define SEL8LAT     LATAbits.LATA3			// FOR WRITE 

/*
//FOR ENCODER

#define ARCFORCE		PORTEbits.RE0           // FOR READ
#define ARCFORCEIO 		TRISEbits.TRISE0		// FOR INPUT OUTPUT
#define ARCFORCELAT		LATEbits.LATE0			// FOR WRITE

#define HOTSTART		PORTEbits.RE1           // FOR READ
#define HOTSTARTIO 		TRISEbits.TRISE1		// FOR INPUT OUTPUT
#define HOTSTARTLAT		LATEbits.LATE1			// FOR WRITE

#define SETCURRENT    	PORTAbits.RA4			// FOR READ
#define SETCURRENTIO 	TRISAbits.TRISA4        // FOR INPUT OUTPUT
#define SETCURRENTLAT	LATAbits.LATA4          // FOR WRITE
*/

//FOR TACT SWITCH

#define MMA_TIG_SWITCH      PORTCbits.RC0        // FOR READ
#define MMA_TIG_SWITCHIO    TRISCbits.TRISC0     // FOR INPUT OUTPUT
#define MMA_TIG_SWITCHLAT   LATCbits.LATC0       // FOR WRITE

#define Battery_LED        PORTAbits.RA5        // FOR READ
#define Battery_LEDIO    TRISAbits.TRISA5     // FOR INPUT OUTPUT
#define Battery_LEDLAT    LATAbits.LATA5       // FOR WRITE

#define VRD_SWITCH          PORTBbits.RB3			// FOR READ
#define VRD_SWITCHIO        TRISBbits.TRISB3        // FOR INPUT OUTPUT
#define VRD_SWITCHLAT       LATBbits.LATB3          // FOR WRITE

#define VRD_LED        PORTEbits.RE2			// FOR READ
#define VRD_LEDIO      TRISEbits.TRISE2         // FOR INPUT OUTPUT
#define VRD_LEDLAT     LATEbits.LATE2           // FOR WRITE

//#define TRIP_LED           PORTCbits.RC5			// FOR READ
//#define TRIP_LEDIO         TRISCbits.TRISC5         // FOR INPUT OUTPUT
//#define TRIP_LEDLAT        LATCbits.LATC5           // FOR WRITE

//#define ARCFORCE_LED        PORTBbits.RB3			// FOR READ
//#define ARCFORCE_LEDIO      TRISBbits.TRISB3        // FOR INPUT OUTPUT
//#define ARCFORCE_LEDLAT     LATBbits.LATB3          // FOR WRITE

 //FOR DAC


#define SCL      	PORTCbits.RC3        // FOR READ
#define SCLIO    	TRISCbits.TRISC3     // FOR INPUT OUTPUT
#define SCLLAT 		LATCbits.LATC3       // FOR WRITE

#define SDA	      	PORTCbits.RC4        // FOR READ
#define SDAIO	   	TRISCbits.TRISC4     // FOR INPUT OUTPUT
#define SDALAT	  	LATCbits.LATC4       // FOR WRITE

#define TX          PORTCbits.RC6
#define TXIO        TRISCbits.TRISC6
#define TXLAT       LATCbits.LATC6

#define RX          PORTCbits.RC7
#define RXIO        TRISCbits.TRISC7
#define RXLAT       LATCbits.LATC7

#define HOT_START_TIME  150  // xx*10
#define HOT_START_SETCURR_LIMIT  200


#define ARCFORCE_SETCURR_LIMIT_1    10
#define ARCFORCE_SETCURR_LIMIT_2    200
#define ARCFORCE_VTG_LIMIT       300.0

#define ENCODER_SHORT_PRESS     20
#define ENCODER_LONG_PRESS      3000
#define ENCODER_VERY_LONG_PRESS 6000

#define SWITCH_SHORT_PRESS       20
#define SWITCH_LONG_PRESS        5000

#define ANTISTICK_CURR          5
#define ANTISTICK_LEAVE_TIME    150 // xxx*10

#define WELDMODE_ADDR               1
#define SETCURRENT_ADDR             3
#define ARCFORCE_ADDR               5
#define HOTSTART_ADDR               7
#define SWITCH_SELECTION_ADDR       9
#define ARCON_RESET_ADDR            11
#define ARCONTIME_SEC_ADDR          30  //13
#define ARCONTIME_MIN_ADDR          33  //14
#define ARCONTIME_HR_ADDR           36  //15
#define REMOTE_OFFSETMIN_ADDR       17
#define REMOTE_OFFSETMAX_ADDR       19
#define VRD_MODE_TIME_ADDR          21
#define MODEL_SELECTION_ADDR        40
#define MODEL_CURRENT_ADDR          25
#define VRD_COUNT_ADDR              48
#define MAX_CURR_OFFSET             46
#define MIN_CURR_OFFSET             50
#define DISP_FB_OFFSET              52

#define WELDON_START_CURR       9//7//10  //5

#define ANTISTICK_VTG_LIMIT     100.0
#define ER_DEBOUNCE_TIME  2//5 

#define REMOTE_CURR_LIMIT   400     //CHANGE ACCORDING TO THE CURR LIMIT OF THE MACHINE

#define MMACCSLOPE250  5.8
#define MMACCOFFSET250 365

#define MMACCSLOPE400  5.6 //5.5
#define MMACCOFFSET400 346.15           //346.15        old Value



#define MMACCSLOPE600  4.2
#define MMACCOFFSET600 365

#define UV_1    2390   
#define UV_2    3300    //3100

#define OV_1    2300
#define OV_2    4500

#define TH_1    3700
#define TH_2    4000

#define NO_CN9_CONNECTOR_1    0
#define NO_CN9_CONNECTOR_2    200//500,100


#define SHDN        PORTCbits.RC2       // FOR READ
#define SHDNIO      TRISCbits.TRISC2     // FOR INPUT OUTPUT
#define SHDNLAT     LATCbits.LATC2       // FOR WRITE

#define SETCURRENT_MENUCNT      5    

#define HOT_START_SETCURR_CHAMP600_LIMIT_1  300
#define HOT_START_SETCURR_CHAMP600_LIMIT    450
#define ARCFORCE_SETCURR_CHAMP600_LIMIT_2   500

#define ARCFORCE_VTG_CHAMP600_LIMIT         350.0



#define ARCFORCE_SETCURR_CHAMP600_LIMIT_1   201
#define ARCFORCE_SETCURR_CHAMP600_LIMIT_2   500

#define ARC_VOLTAGE     350.0

//#define VRD_TIME_MAX    180
//#define VRD_TIME_MIN    0

#define OFFSET_MID      50

#define DIGITALRXMONITORCNT     5

#define OFFSET_MID_400  0
#define OFFSET_MID_600  70

#define OFFSET_MID_400_MIN     50//50
#define OFFSET_MID_600_MIN     50
//#define SLOPE_MID_400   50