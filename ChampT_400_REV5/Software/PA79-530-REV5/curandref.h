#include <16F883.h>
#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz)
#FUSES NOMCLR                   //Master Clear pin enabled
#FUSES NOCPD                    //No EE protection
#FUSES NOBROWNOUT               //No brownout reset
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES LVP                      //Low Voltage Programming on B3(PIC16) or B5(PIC18)
#FUSES NODEBUG                  //No Debug mode for ICD
//#FUSES NIWRTC
#FUSES NOWRT                    //Program memory not write protected
#FUSES INTRC
#use delay(clock=8000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

