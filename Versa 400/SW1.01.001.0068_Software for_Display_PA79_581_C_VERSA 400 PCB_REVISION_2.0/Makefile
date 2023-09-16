# MPLAB IDE generated this makefile for use with GNU make.
# Project: PULSEMIG.mcp
# Date: Sat Aug 20 14:14:15 2022

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

PULSEMIG.hex : PULSEMIG.cof
	$(HX) "PULSEMIG.cof"

PULSEMIG.cof : MAIN.o
	$(CC) -mcpu=30F6014A "MAIN.o" -o"PULSEMIG.cof" -Wl,-L"C:\Program Files (x86)\Microchip\MPLAB C30\lib",--script="linkerscriptnew.gld",--defsym=__MPLAB_BUILD=1,-Map="PULSEMIG.map",--report-mem

MAIN.o : TORCHCYCLE.C MIG.C TIG.C MMA.C KEYPAD.C DISPLAY.C ISR2.C TESTEEPROM.C LCDARRAY.C FUNCTION.C VARIABLE.C STRUCTURE400.C DEFINE.C c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdlib.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/float.h pid.c c:/program\ files\ (x86)/microchip/mplab\ c30/include/math.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdlib.h c:/program\ files\ (x86)/microchip/mplab\ c30/support/h/dsp.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/math.h p30f6014A.h c:/program\ files\ (x86)/microchip/mplab\ c30/support/h/libpic30.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/yvals.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdio.h MAIN.C
	$(CC) -mcpu=30F6014A -x c -c "MAIN.C" -o"MAIN.o" -g -Wall

clean : 
	$(RM) "MAIN.o" "PULSEMIG.cof" "PULSEMIG.hex"

