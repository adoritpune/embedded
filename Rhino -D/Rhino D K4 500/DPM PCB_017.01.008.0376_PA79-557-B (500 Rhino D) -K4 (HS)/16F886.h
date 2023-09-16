//////// Standard Header file for the PIC16F886 device ////////////////
#device PIC16F886
#nolist
//////// Program memory: 8192x14  Data RAM: 271  Stack: 8
//////// I/O: 25   Analog Pins: 14
//////// Data EEPROM: 256
//////// C Scratch area: 77   ID Location: 2000
//////// Fuses: LP,XT,HS,EC_IO,INTRC_IO,INTRC,RC_IO,RC,NOWDT,WDT,NOPWRT,PWRT
//////// Fuses: NOMCLR,MCLR,NOCP,CP,NOCPD,CPD,NOBOR,BOREN,NOBOR_SLEEP
//////// Fuses: BOR_PCON,NOIESO,IESO,NOFCMEN,FCMEN,NOLVP,LVP,NODEBUG,DEBUG
//////// Fuses: BOR4VBROWNOUT_SL,BOR2V,WRT2,WRT1,WRT0,NOWRT
//////// 
////////////////////////////////////////////////////////////////// I/O
// Discrete I/O Functions: SET_TRIS_x(), OUTPUT_x(), INPUT_x(),
//                         PORT_x_PULLUPS(), INPUT(),
//                         OUTPUT_LOW(), OUTPUT_HIGH(),
//                         OUTPUT_FLOAT(), OUTPUT_BIT()
// Constants used to identify pins in the above are:

#define PIN_A0  40
#define PIN_A1  41
#define PIN_A2  42
#define PIN_A3  43
#define PIN_A4  44
#define PIN_A5  45
#define PIN_A6  46
#define PIN_A7  47

#define PIN_B0  48
#define PIN_B1  49
#define PIN_B2  50
#define PIN_B3  51
#define PIN_B4  52
#define PIN_B5  53
#define PIN_B6  54
#define PIN_B7  55

#define PIN_C0  56
#define PIN_C1  57
#define PIN_C2  58
#define PIN_C3  59
#define PIN_C4  60
#define PIN_C5  61
#define PIN_C6  62
#define PIN_C7  63

#define PIN_E3  75

////////////////////////////////////////////////////////////////// Useful defines
#define FALSE 0
#define TRUE 1

#define BYTE int
#define BOOLEAN short int

#define getc getch
#define fgetc getch
#define getchar getch
#define putc putchar
#define fputc putchar
#define fgets gets
#define fputs puts

////////////////////////////////////////////////////////////////// Control
// Control Functions:  RESET_CPU(), SLEEP(), RESTART_CAUSE()
// Constants returned from RESTART_CAUSE() are:
#define WDT_FROM_SLEEP  3     
#define WDT_TIMEOUT     11    
#define MCLR_FROM_SLEEP 19    
#define MCLR_FROM_RUN   27    
#define NORMAL_POWER_UP 24    
#define BROWNOUT_RESTART 26   


////////////////////////////////////////////////////////////////// Timer 0
// Timer 0 (AKA RTCC)Functions: SETUP_COUNTERS() or SETUP_TIMER_0(),
//                              SET_TIMER0() or SET_RTCC(),
//                              GET_TIMER0() or GET_RTCC()
// Constants used for SETUP_TIMER_0() are:
#define RTCC_INTERNAL   0
#define RTCC_EXT_L_TO_H 32
#define RTCC_EXT_H_TO_L 48

#define RTCC_DIV_1      8
#define RTCC_DIV_2      0
#define RTCC_DIV_4      1
#define RTCC_DIV_8      2
#define RTCC_DIV_16     3
#define RTCC_DIV_32     4
#define RTCC_DIV_64     5
#define RTCC_DIV_128    6
#define RTCC_DIV_256    7


#define RTCC_8_BIT      0     

// Constants used for SETUP_COUNTERS() are the above
// constants for the 1st param and the following for
// the 2nd param:

////////////////////////////////////////////////////////////////// WDT
// Watch Dog Timer Functions: SETUP_WDT() or SETUP_COUNTERS() (see above)
//                            RESTART_WDT()
//
#define WDT_ON          1
#define WDT_OFF         0

#define WDT_DIV_32      1
#define WDT_DIV_64      3
#define WDT_DIV_128     5
#define WDT_DIV_256     7
#define WDT_DIV_512     9
#define WDT_DIV_1024    11
#define WDT_DIV_2048    13
#define WDT_DIV_4096    15
#define WDT_DIV_8192    17
#define WDT_DIV_16394   19
#define WDT_DIV_32768   21
#define WDT_DIV_65536   23

////////////////////////////////////////////////////////////////// Timer 1
// Timer 1 Functions: SETUP_TIMER_1, GET_TIMER1, SET_TIMER1
// Constants used for SETUP_TIMER_1() are:
//      (or (via |) together constants from each group)
#define T1_DISABLED         0
#define T1_INTERNAL         0x85
#define T1_EXTERNAL         0x87
#define T1_EXTERNAL_SYNC    0x83

#define T1_CLK_OUT          8

#define T1_DIV_BY_1         0
#define T1_DIV_BY_2         0x10
#define T1_DIV_BY_4         0x20
#define T1_DIV_BY_8         0x30

////////////////////////////////////////////////////////////////// Timer 2
// Timer 2 Functions: SETUP_TIMER_2, GET_TIMER2, SET_TIMER2
// Constants used for SETUP_TIMER_2() are:
#define T2_DISABLED         0
#define T2_DIV_BY_1         4
#define T2_DIV_BY_4         5
#define T2_DIV_BY_16        6

////////////////////////////////////////////////////////////////// CCP
// CCP Functions: SETUP_CCPx, SET_PWMx_DUTY
// CCP Variables: CCP_x, CCP_x_LOW, CCP_x_HIGH
// Constants used for SETUP_CCPx() are:
#define CCP_OFF                         0
#define CCP_CAPTURE_FE                  4
#define CCP_CAPTURE_RE                  5
#define CCP_CAPTURE_DIV_4               6
#define CCP_CAPTURE_DIV_16              7
#define CCP_COMPARE_SET_ON_MATCH        8
#define CCP_COMPARE_CLR_ON_MATCH        9
#define CCP_COMPARE_INT                 0xA
#define CCP_COMPARE_RESET_TIMER         0xB
#define CCP_PWM                         0xC
#define CCP_PWM_PLUS_1                  0x1c
#define CCP_PWM_PLUS_2                  0x2c
#define CCP_PWM_PLUS_3                  0x3c
long CCP_1;
#byte   CCP_1    =                      0x15          
#byte   CCP_1_LOW=                      0x15          
#byte   CCP_1_HIGH=                     0x16          
// The following should be used with the ECCP unit only (or these in)
#define CCP_PWM_H_H                     0x0c
#define CCP_PWM_H_L                     0x0d
#define CCP_PWM_L_H                     0x0e
#define CCP_PWM_L_L                     0x0f

#define CCP_PWM_FULL_BRIDGE             0x40
#define CCP_PWM_FULL_BRIDGE_REV         0xC0
#define CCP_PWM_HALF_BRIDGE             0x80

#define CCP_SHUTDOWN_ON_COMP1           0x100000
#define CCP_SHUTDOWN_ON_COMP2           0x200000
#define CCP_SHUTDOWN_ON_COMP            0x300000
#define CCP_SHUTDOWN_ON_INT0            0x400000
#define CCP_SHUTDOWN_ON_COMP1_INT0      0x500000
#define CCP_SHUTDOWN_ON_COMP2_INT0      0x600000
#define CCP_SHUTDOWN_ON_COMP_INT0       0x700000

#define CCP_SHUTDOWN_AC_L               0x000000
#define CCP_SHUTDOWN_AC_H               0x040000
#define CCP_SHUTDOWN_AC_F               0x080000

#define CCP_SHUTDOWN_BD_L               0x000000
#define CCP_SHUTDOWN_BD_H               0x010000
#define CCP_SHUTDOWN_BD_F               0x020000

#define CCP_SHUTDOWN_RESTART            0x80000000
#define CCP_DELAY                       0x1000000  // Multiply this by the delay count

long CCP_2;
#byte   CCP_2    =                      0x1B        
#byte   CCP_2_LOW=                      0x1B        
#byte   CCP_2_HIGH=                     0x1C        
////////////////////////////////////////////////////////////////// SPI
// SPI Functions: SETUP_SPI, SPI_WRITE, SPI_READ, SPI_DATA_IN
// Constants used in SETUP_SPI() are:
#define SPI_MASTER       0x20
#define SPI_SLAVE        0x24
#define SPI_L_TO_H       0
#define SPI_H_TO_L       0x10
#define SPI_CLK_DIV_4    0
#define SPI_CLK_DIV_16   1
#define SPI_CLK_DIV_64   2
#define SPI_CLK_T2       3
#define SPI_SS_DISABLED  1

#define SPI_SAMPLE_AT_END 0x8000
#define SPI_XMIT_L_TO_H  0x4000

////////////////////////////////////////////////////////////////// UART
// Constants used in setup_uart() are:
// FALSE - Turn UART off
// TRUE  - Turn UART on
#define UART_ADDRESS           2
#define UART_DATA              4
#define UART_AUTODETECT        8
#define UART_AUTODETECT_NOWAIT 9
#define UART_WAKEUP_ON_RDA     10
////////////////////////////////////////////////////////////////// COMP
// Comparator Variables: C1OUT, C2OUT
// Constants used in setup_comparator() are:
#define A0_A3_A1_A2  0xfff04
#define A0_A2_A1_A2  0x7ff03
#define NC_NC_A1_A2  0x6ff05
#define NC_NC_NC_NC  0x0ff07
#define A0_VR_A1_VR  0x3ff02
#define A3_VR_A2_VR  0xcff0A
#define A0_A2_A1_A2_OUT_ON_A3_A4 0x7e706
#define A3_A2_A1_A2  0xeff09

#bit C1OUT = 0x1f.6  
#bit C2OUT = 0x1f.7  



////////////////////////////////////////////////////////////////// ADC
// ADC Functions: SETUP_ADC(), SETUP_ADC_PORTS() (aka SETUP_PORT_A),
//                SET_ADC_CHANNEL(), READ_ADC()
// Constants used for SETUP_ADC() are:
#define ADC_OFF                0          // ADC Off
#define ADC_CLOCK_DIV_2    0x100
#define ADC_CLOCK_DIV_8     0x40
#define ADC_CLOCK_DIV_32    0x80
#define ADC_CLOCK_INTERNAL  0xc0          // Internal 2-6us


// Constants used in SETUP_ADC_PORTS() are:
#define sAN0                   1         //| A0
#define sAN1                   2         //| A1
#define sAN2                   4         //| A2
#define sAN3                   8         //| A3
#define sAN4                  16         //| B0
#define sAN5                  32         //| B1
#define sAN6                  64         //| B2
#define sAN7                  128        //| B3
#define NO_ANALOGS             0         // None
#define ALL_ANALOG            255        // A0 A1 A2 A3 B0 B1 B2 B3

// The following may be OR'ed in with the above using |
#define VSS_VDD              0x0000  // Range 0-Vdd
#define VSS_VREF             0x1000  // Range 0-Vref1
#define VSS_VR               0x2000  // Range 0-Vr
#define VSS_VDAC             0x3000  // Range 0-Vdac



// Constants used in READ_ADC() are:
#define ADC_START_AND_READ     7   // This is the default if nothing is specified
#define ADC_START_ONLY         1
#define ADC_READ_ONLY          6



////////////////////////////////////////////////////////////////// INT
// Interrupt Functions: ENABLE_INTERRUPTS(), DISABLE_INTERRUPTS(),
//                      EXT_INT_EDGE()
//
// Constants used in EXT_INT_EDGE() are:
#define L_TO_H              0x40
#define H_TO_L                 0
// Constants used in ENABLE/DISABLE_INTERRUPTS() are:
#define GLOBAL                    0x0BC0
#define INT_RTCC                  0x0B20
#define INT_RB                    0xFF0B08
#define INT_EXT                   0x0B10
#define INT_AD                    0x8C40
#define INT_TBE                   0x8C10
#define INT_RDA                   0x8C20
#define INT_TIMER1                0x8C01
#define INT_TIMER2                0x8C02
#define INT_CCP1                  0x8C04
#define INT_CCP2                  0x8D01
#define INT_SSP                   0x8C08
#define INT_BUSCOL                0x8D08
#define INT_EEPROM                0x8D10
#define INT_TIMER0                0x0B20
#define INT_OSC_FAIL              0x8D80
#define INT_COMP                  0x8D20
#define INT_COMP2                 0x8D40

#list
