#define PA603_A   //PA603
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

#define MTR_FREQ_CONSTANT 3.6//8//4.5   //4.5  //1.5//3.58
#define MTR_VTG_CONSTANT  2.8//1.4//3.9  //3.65 once ok //3.9//3.4 original//1.4 22=33V//
#define MTR_VTG_LOW_CONST   2.8//3.6//1.4//3.6//4.66
#define MTR_VTG_HIGH_CONST  1.4//1.4
#define MAX_P_FB_FREQ 999



#define RECEIVE_STRING_LENGTH 21


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




