# MPLAB IDE generated this makefile for use with GNU make.
# Project: WF_DT.mcp
# Date: Thu Jul 20 10:01:06 2023

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

WF_DT.hex : WF_DT.cof
	$(HX) "WF_DT.cof"

WF_DT.cof : main.o
	$(CC) -mcpu=30F4013 "main.o" -o"WF_DT.cof" -Wl,-Tp30F4013.gld,--defsym=__MPLAB_BUILD=1,-Map="WF_DT.map",--report-mem

main.o : ENCODER.C Isr.c variable.c DISPLAY.c STRUCTURE.c function.c DELAY.C define.c c:/program\ files\ (x86)/microchip/mplab\ c30/include/string.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdlib.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stddef.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/yvals.h c:/program\ files\ (x86)/microchip/mplab\ c30/include/stdio.h c:/program\ files\ (x86)/microchip/mplab\ c30/support/h/p30f4013.h main.c
	$(CC) -mcpu=30F4013 -x c -c "main.c" -o"main.o" -g -Wall

clean : 
	$(RM) "main.o" "WF_DT.cof" "WF_DT.hex"

