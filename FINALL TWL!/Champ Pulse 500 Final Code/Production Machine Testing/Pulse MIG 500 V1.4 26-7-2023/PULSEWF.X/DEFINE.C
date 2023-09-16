#define PA603_A //PA603
//#define PA603

#ifndef _DEFINE_C_
#define _DEFINE_C_

/*#define SEGA             PORTBbits.RB0
#define SEGB             PORTBbits.RB1
#define SEGC             PORTBbits.RB2
#define SEGD             PORTBbits.RB3
#define SEGE             PORTBbits.RB4
#define SEGF             PORTBbits.RB5
#define SEGG             PORTBbits.RB6
#define SEGDP            PORTBbits.RB7
*/

#define SEGDP           LATBbits.LATB7


#define DECODE_B        LATAbits.LATA6
#define DECODE_C        LATAbits.LATA7
#define DECODE_EN       LATCbits.LATC0

#define MPULSE          PORTCbits.RC1
#define GAS_RLY         PORTCbits.RC3

#define TORCHIN         PORTCbits.RC5

#define TRISMPULSE      TRISCbits.TRISC1
#define TRISGAS_RLY     TRISCbits.TRISC3

#define TRISTORCHIN     TRISCbits.TRISC5

#define ENCODER1A       PORTAbits.RA3
#define ENCODER1B       PORTAbits.RA4
#define ENCODER2A       PORTAbits.RA1
#define ENCODER2B       PORTAbits.RA2

#define TRISEN1A        TRISAbits.TRISA1
#define TRISEN1B        TRISAbits.TRISA2
#define TRISEN2A        TRISAbits.TRISA3
#define TRISEN2B        TRISAbits.TRISA4

#define PORTBSTATUS     PORTB
#define OUTPORTB        LATB

#define MTRFB           PORTAbits.RA0
#define TRISMTRFB       TRISAbits.TRISA0

//#define MTR_FREQ_CONSTANT  3.25   //3.25//2.7//3.58  //3.58 //modified for pulse proto to coimbtore
//#define MTR_VTG_CONSTANT 2.7//3.2//3.65  //3.4
#define MTR_FREQ_CONSTANT  3.4//4//6.5//2.5
#define MTR_VTG_CONSTANT 3.4//2.8//3.4//2.8//1.2//1.4//    changed on 230919
#define MAX_P_FB_FREQ 999//999



#define RECEIVE_STRING_LENGTH 22


#ifdef PA603_A
    #define DECODE_A            LATCbits.LATC4
    #define MOTOR_TRIP11        PORTAbits.RA5
    #define TRISMOTOR_TRIP11    TRISAbits.TRISA5
#else
    #define DECODE_A        LATAbits.LATA5
    #define TRISMOTOR_TRIP11    TRISCbits.TRISC4
    #define MOTOR_TRIP11        PORTCbits.RC4
#endif


#endif




