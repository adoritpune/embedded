/************************************************************************/
/*              Header for Input Capture module library functions       */
/************************************************************************/

#if defined(__dsPIC30F__)
#include <p30fxxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include <p24Hxxxx.h>
#endif

#ifndef __INCAP_H
#define __INCAP_H

/* List of SFRs for Input Capture modules */
/* This list contains the SFRs with default (POR) values to be used for configuring Input capture modules */
/* The user can modify this based on the requirement */
#define IC1CON_VALUE            0x0000
#define IC1BUF_VALUE            0x0000
#define IC2CON_VALUE            0x0000
#define IC2BUF_VALUE            0x0000

#ifdef _IC3IF
#define IC3CON_VALUE            0x0000
#define IC3BUF_VALUE            0x0000
#endif

#ifdef _IC4IF
#define IC4CON_VALUE            0x0000
#define IC4BUF_VALUE            0x0000
#endif

#ifdef _IC5IF
#define IC5CON_VALUE            0x0000
#define IC5BUF_VALUE            0x0000
#endif

#ifdef _IC6IF
#define IC6CON_VALUE            0x0000
#define IC6BUF_VALUE            0x0000
#endif

#ifdef _IC7IF
#define IC7CON_VALUE            0x0000
#define IC7BUF_VALUE            0x0000
#endif

#ifdef _IC8IF
#define IC8CON_VALUE            0x0000
#define IC8BUF_VALUE            0x0000
#endif

/* Input Capture Config (ICxCON Reg) Bit defines */

#define IC_IDLE_CON             0xdfff  /* IC operate in sleep mode */
#define IC_IDLE_STOP            0xffff  /* IC stop in sleep mode */

#define IC_TIMER2_SRC           0xffff  /* Timer2 is the clock source for Capture */
#define IC_TIMER3_SRC           0xff7f  /* Timer3 is the clock source for Capture */

#define IC_INT_4CAPTURE         0xffff  /* Interrupt on fourth Capture*/
#define IC_INT_3CAPTURE         0xffdf  /* Interrupt on third Capture */
#define IC_INT_2CAPTURE         0xffbf  /* Interrupt on second Capture*/
#define IC_INT_1CAPTURE         0xff9f  /* Interrupt on first Capture */

#define IC_INTERRUPT            0xffff  /* Interrupt pin only in CPU sleep and idle mode */

#define IC_EVERY_16_RISE_EDGE   0xfffd  /* Every 16th rising edge */
#define IC_EVERY_4_RISE_EDGE    0xfffc  /* Every 4th rising edge  */
#define IC_EVERY_RISE_EDGE      0xfffb  /* Every rising edge      */
#define IC_EVERY_FALL_EDGE      0xfffa  /* Every falling edge      */
#define IC_EVERY_EDGE           0xfff9  /* Every rising/falling edge */
#define IC_INPUTCAP_OFF         0xfff8  /* Input Capture Off      */

/* defines for IC interrupts */
#define IC_INT_ON               0xffff  /* Input Capture Enable  */
#define IC_INT_OFF              0xfff7  /* Input Capture Disable */

#define IC_INT_PRIOR_0          0xfff8  /* Input Capture PriorityLevel 0 */
#define IC_INT_PRIOR_1          0xfff9  /* Input Capture PriorityLevel 1 */
#define IC_INT_PRIOR_2          0xfffa  /* Input Capture PriorityLevel 2 */
#define IC_INT_PRIOR_3          0xfffb  /* Input Capture PriorityLevel 3 */
#define IC_INT_PRIOR_4          0xfffc  /* Input Capture PriorityLevel 4 */
#define IC_INT_PRIOR_5          0xfffd  /* Input Capture PriorityLevel 5 */
#define IC_INT_PRIOR_6          0xfffe  /* Input Capture PriorityLevel 6 */
#define IC_INT_PRIOR_7          0xffff  /* Input Capture PriorityLevel 7 */
 
#ifdef _IC1IF

#define EnableIntIC1                    _IC1IE = 1
#define DisableIntIC1                   _IC1IE = 0
#define SetPriorityIntIC1(priority)     _IC1IP = priority

/* CloseCapture 1 */
void CloseCapture1() __attribute__ ((section(".libperi")));

/* ConfigIntCapture1 */
void ConfigIntCapture1(unsigned int ) __attribute__ ((section (".libperi")));

/* OpenCapture1 */
void OpenCapture1(unsigned int  ) __attribute__ ((section (".libperi")));

/* ReadCapture1 */
void ReadCapture1(unsigned int * buffer) __attribute__ ((section (".libperi")));

#endif

#ifdef _IC2IF

#define EnableIntIC2                    _IC2IE = 1
#define DisableIntIC2                   _IC2IE = 0
#define SetPriorityIntIC2(priority)     _IC2IP = priority

/* CloseCapture 2 */
void CloseCapture2() __attribute__ ((section(".libperi")));

/* ConfigIntCapture2 */
void ConfigIntCapture2(unsigned int ) __attribute__ ((section (".libperi")));

/* OpenCapture2 */
void OpenCapture2(unsigned int  ) __attribute__ ((section (".libperi")));

/* ReadCapture2 */ 
void ReadCapture2(unsigned int * buffer) __attribute__ ((section (".libperi")));

#endif

#ifdef _IC3IF

#define EnableIntIC3                    _IC3IE = 1
#define DisableIntIC3                   _IC3IE = 0
#define SetPriorityIntIC3(priority)     _IC3IP = priority

/* CloseCapture 3 */
void CloseCapture3() __attribute__ ((section(".libperi")));

/* ConfigIntCapture3 */
void ConfigIntCapture3(unsigned int ) __attribute__ ((section (".libperi")));

/* OpenCapture3 */
void OpenCapture3(unsigned int  )  __attribute__ ((section (".libperi")));

/* ReadCapture3 */ 
void ReadCapture3(unsigned int * buffer) __attribute__ ((section (".libperi")));

#endif

#ifdef _IC4IF

#define EnableIntIC4                    _IC4IE = 1
#define DisableIntIC4                   _IC4IE = 0
#define SetPriorityIntIC4(priority)     _IC4IP = priority

/* CloseCapture 4 */
void CloseCapture4() __attribute__ ((section(".libperi")));

/* ConfigIntCapture4 */
void ConfigIntCapture4(unsigned int ) __attribute__ ((section (".libperi")));

/* OpenCapture4 */
void OpenCapture4(unsigned int  )  __attribute__ ((section (".libperi")));

/* ReadCapture4 */
void ReadCapture4(unsigned int * buffer) __attribute__ ((section (".libperi")));

#endif

#ifdef _IC5IF

#define EnableIntIC5                    _IC5IE = 1
#define DisableIntIC5                   _IC5IE = 0
#define SetPriorityIntIC5(priority)     _IC5IP = priority

/* CloseCapture 5 */
void CloseCapture5() __attribute__ ((section (".libperi")));

/* ConfigIntCapture5 */
void ConfigIntCapture5(unsigned int )  __attribute__ ((section (".libperi")));

/* OpenCapture5 */
void OpenCapture5(unsigned int  ) __attribute__ ((section (".libperi")));

/* ReadCapture5 */
void ReadCapture5(unsigned int * buffer) __attribute__ ((section (".libperi")));

#endif

#ifdef _IC6IF

#define EnableIntIC6                    _IC6IE = 1
#define DisableIntIC6                   _IC6IE = 0
#define SetPriorityIntIC6(priority)     _IC6IP = priority

/* CloseCapture 6 */
void CloseCapture6() __attribute__ ((section (".libperi")));

/* ConfigIntCapture6 */
void ConfigIntCapture6(unsigned int ) __attribute__ ((section (".libperi")));

/* OpenCapture6 */
void OpenCapture6(unsigned int  ) __attribute__ ((section (".libperi")));

/* ReadCapture6 */
void ReadCapture6(unsigned int * buffer) __attribute__ ((section (".libperi")));

#endif

#ifdef _IC7IF

#define EnableIntIC7                     _IC7IE = 1
#define DisableIntIC7                    _IC7IE = 0
#define SetPriorityIntIC7(priority)      _IC7IP = priority

/* CloseCapture 7 */
void CloseCapture7() __attribute__ ((section (".libperi"))); 

/* ConfigIntCapture7 */
void ConfigIntCapture7(unsigned int ) __attribute__ ((section (".libperi")));

/* OpenCapture7 */
void OpenCapture7(unsigned int  ) __attribute__ ((section (".libperi")));

/* ReadCapture7 */
void ReadCapture7(unsigned int * buffer) __attribute__ ((section (".libperi")));

#endif

#ifdef _IC8IF

#define EnableIntIC8                     _IC8IE = 1
#define DisableIntIC8                    _IC8IE = 0
#define SetPriorityIntIC8(priority)      _IC8IP = priority

/* CloseCapture 8 */
void CloseCapture8() __attribute__ ((section (".libperi")));

/* ConfigIntCapture8 */
void ConfigIntCapture8(unsigned int ) __attribute__ ((section (".libperi")));

/* OpenCapture8 */
void OpenCapture8(unsigned int  ) __attribute__ ((section (".libperi")));

/* ReadCapture8 */
void ReadCapture8(unsigned int * buffer) __attribute__ ((section (".libperi")));

#endif

#endif  /*__INCAP_H  */
