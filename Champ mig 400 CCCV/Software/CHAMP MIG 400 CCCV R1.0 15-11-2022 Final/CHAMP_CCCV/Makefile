# MPLAB IDE generated this makefile for use with GNU make.
# Project: CHAMP_CCCV_400.mcp
# Date: Fri Feb 10 14:37:28 2023

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

CHAMP_CCCV_400.hex : CHAMP_CCCV_400.cof
	$(HX) "CHAMP_CCCV_400.cof"

CHAMP_CCCV_400.cof : MAIN.o
	"C:\Program Files (x86)\Microchip\MPLAB C30\bin\pic30-coff-gcc.exe" -mcpu=30F6014A "MAIN.o" -o"CHAMP_CCCV_400.cof" -Wl,--script="p30f6014A.gld",--defsym=__MPLAB_BUILD=1,-Map="CHAMP_CCCV_400.map",--report-mem

MAIN.o : TORCHCYCLE.C MIG.C TIG.C MMA.C KEYPAD.C DISPLAY.C ISR.C EEPROM.C LCDARRAY.C FUNCTION.C VARIABLE.C STRUCTURE400.C DEFINE.C c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdlib.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/float.h pid.c c:/program\ files\ (x86)/microchip/mplab\ c30/include/math.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdlib.h c:/program\ files\ (x86)/microchip/mplab\ c30/support/h/dsp.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/math.h p30f6014A.h c:/program\ files\ (x86)/microchip/mplab\ c30/support/h/libpic30.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/yvals.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdio.h MAIN.c
	"C:\Program Files (x86)\Microchip\MPLAB C30\bin\pic30-coff-gcc.exe" -mcpu=30F6014A -x c -c   "MAIN.c" -o"MAIN.o" -g -Wall

clean : 
	$(RM) "MAIN.o" "CHAMP_CCCV_400.cof" "CHAMP_CCCV_400.hex"

