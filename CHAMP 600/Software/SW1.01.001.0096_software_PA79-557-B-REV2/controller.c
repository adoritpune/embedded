//------------------------------------------------------------------------------
#byte MCU_STATUS = 0x003
#bit    MCU_C = MCU_STATUS.0
#bit    MCU_DC = MCU_STATUS.1
#bit    MCU_Z = MCU_STATUS.2
#bit    MCU_PD = MCU_STATUS.3
#bit    MCU_TO = MCU_STATUS.4
#bit    MCU_RP0 = MCU_STATUS.5
#bit    MCU_RP1 = MCU_STATUS.6
#bit    MCU_IRP = MCU_STATUS.7
#byte MCU_PORTA = 0x005
#byte MCU_PORTB = 0x006
#byte MCU_PORTC = 0x007
#byte MCU_PORTD = 0x008
#byte MCU_PORTE = 0x009
#bit    MCU_RE0 = MCU_PORTE.0
#bit    MCU_RE1 = MCU_PORTE.1
#bit    MCU_RE2 = MCU_PORTE.2
#byte MCU_INTCON = 0x00B
#bit    MCU_RBIF = MCU_INTCON.0
#bit    MCU_INTF = MCU_INTCON.1
#bit    MCU_T0IF = MCU_INTCON.2
#bit    MCU_RBIE = MCU_INTCON.3
#bit    MCU_INTE = MCU_INTCON.4
#bit    MCU_T0IE = MCU_INTCON.5
#bit    MCU_PEIE = MCU_INTCON.6
#bit    MCU_GIE = MCU_INTCON.7
#byte MCU_PIR1 = 0x00C
#bit    MCU_TMR1IF = MCU_PIR1.0
#bit    MCU_TMR2IF = MCU_PIR1.1
#bit    MCU_CCP1IF = MCU_PIR1.2
#bit    MCU_SSPIF = MCU_PIR1.3
#bit    MCU_TXIF = MCU_PIR1.4
#bit    MCU_RCIF = MCU_PIR1.5
#bit    MCU_ADIF = MCU_PIR1.6
#bit    MCU_PSPIF = MCU_PIR1.7
#byte MCU_OPTION_REG = 0x181
#bit    MCU_PS0 = MCU_OPTION_REG.0
#bit    MCU_PS1 = MCU_OPTION_REG.1
#bit    MCU_PS2 = MCU_OPTION_REG.2
#bit    MCU_PSA = MCU_OPTION_REG.3
#bit    MCU_T0SE = MCU_OPTION_REG.4
#bit    MCU_T0CS = MCU_OPTION_REG.5
#bit    MCU_INTEDG = MCU_OPTION_REG.6
#bit    MCU_RBPU = MCU_OPTION_REG.7
#byte MCU_ANSEL = 0x188
#bit    MCU_ANSELANSO = MCU_ANSEL.0
#bit    MCU_ANSELANS1 = MCU_ANSEL.1
#bit    MCU_ANSELANS2 = MCU_ANSEL.2
#bit    MCU_ANSELANS3 = MCU_ANSEL.3
#bit    MCU_ANSELANS4 = MCU_ANSEL.4
#bit    MCU_ANSELANS5 = MCU_ANSEL.5
#bit    MCU_ANSELANS6 = MCU_ANSEL.6
#bit    MCU_ANSELANS7 = MCU_ANSEL.7
#byte MCU_ANSELH = 0x189
#bit    MCU_ANSELHANS8 = MCU_ANSELH.0
#bit    MCU_ANSELHANS9 = MCU_ANSELH.1
#bit    MCU_ANSELHANS10 = MCU_ANSELH.2
#bit    MCU_ANSELHANS11 = MCU_ANSELH.3
#byte MCU_ADCON0 = 0x01F
#bit    MCU_ADON = MCU_ADCON0.0
//#bit    MCU_GO/DONE = MCU_ADCON0.1
#bit    MCU_CHS0 = MCU_ADCON0.2
#bit    MCU_CHS1 = MCU_ADCON0.3
#bit    MCU_CHS2 = MCU_ADCON0.4
#bit    MCU_CHS3 = MCU_ADCON0.5
#byte MCU_OSCCON = 0x08F
#byte MCU_OSCTUNE= 0x090


#fuses HS,NOWDT,NOLVP,INTRC_IO,NOWDT,NOMCLR
#use delay(clock=8000000)

