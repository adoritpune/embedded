# MPLAB IDE generated this makefile for use with GNU make.
# Project: wirefeeder1.mcp
# Date: Fri Nov 29 15:05:20 2013

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

wirefeeder1.hex : wirefeeder1.cof
	$(HX) "wirefeeder1.cof"

wirefeeder1.cof : wf1main.o
	$(CC) -mcpu=30F5011 "wf1main.o" -o"wirefeeder1.cof" -Wl,-L"C:\Program Files\Microchip\MPLAB C30\lib",--script="..\..\..\..\p30f5011.gld",--defsym=__MPLAB_BUILD=1,-Map="wirefeeder1.map",--report-mem

wf1main.o : autodata.c display1.c eeprom1.c interrupt1.c encoder21.c keypad1.c define1.h structure.c variable1.h c:/program\ files\ (x86)/microchip/mplab\ c30/support/generic/h/libpic30.h c:/program\ files\ (x86)/microchip/mplab\ c30/support/dsPIC30F/h/p30f5011.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/math.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdarg.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stddef.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdio.h wf1main.c
	$(CC) -mcpu=30F5011 -x c -c "wf1main.c" -o"wf1main.o" -g -Wall

clean : 
	$(RM) "wf1main.o" "wirefeeder1.cof" "wirefeeder1.hex"

