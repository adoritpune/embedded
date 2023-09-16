# MPLAB IDE generated this makefile for use with GNU make.
# Project: PULSEMIG500.mcp
# Date: Tue Aug 29 11:24:44 2023

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

PULSEMIG500.hex : PULSEMIG500.cof
	$(HX) "PULSEMIG500.cof"

PULSEMIG500.cof : MAIN.o
	$(CC) -mcpu=30F6014A "MAIN.o" -o"PULSEMIG500.cof" -Wl,--script="linkerscriptnew.gld",--defsym=__MPLAB_BUILD=1,-Map="PULSEMIG500.map",--report-mem

MAIN.o : p30f6014A.h USB.C p30f6014A.h I2C.C TORCHCYCLE.C PULSEMIG.C MIG.C TIG.C MMA.C KEYPAD.C ENCODER.C DISPLAY.C LCD.C ISR2.C PULSEMIGCONTROL.C NEWCONTROL.C ADORLOGO.C FONT1.C FONT.C TESTEEPROM.C PMIGSYNDATA.C SYNERGICDATA.C LCDARRAY.C FUNCTION.C VARIABLE.C STRUCTURE.C DEFINE.C c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdlib.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/float.h pid.c c:/program\ files\ (x86)/microchip/mplab\ c30/include/math.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdlib.h c:/program\ files\ (x86)/microchip/mplab\ c30/support/h/dsp.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/math.h p30f6014A.h c:/program\ files\ (x86)/microchip/mplab\ c30/support/h/libpic30.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/yvals.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdio.h MAIN.C
	$(CC) -mcpu=30F6014A -x c -c "MAIN.C" -o"MAIN.o" -g -Wall

clean : 
	$(RM) "MAIN.o" "PULSEMIG500.cof" "PULSEMIG500.hex"

