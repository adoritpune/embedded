/*	
A-GAS CHECK
B-GAS SELECTION
C-RECALL
D-ENCODER 2 
E-OCV CHECK
F-MATERIAL SELECTION
G-SAVE KEY
H-MENU KEY
I-INCHING
J-DIAMETER SELECTION.
K-MODE SELECTION
L-AUTO
M-CURRENT MULTIPLIER SETTING
N-MMA/MIG/TIG
O-ENCODER 1 
P-EXTERNAL INCHING
Q-PASSWORD LOCK
R- RESET  
S- ARC ON TIME RESET
*/
const unsigned char keyeqv[4][4]=	
						{	{'A','B','C','O'},
							{'E','F','G','H'},
							{'I','J','K','L'},
							{'N','D','P','Q'}
						};
unsigned char keypad_read()
{
	unsigned char temp;
	allcolumnlogic1();
	ans=key_press();
	if(ans==1)			//any key is pressed.
	{
		ans=0;
		temp=getkey();
		debounce_delay();
	}
	else
	{
		temp='Z';//LEDLAT=0;
	}
	return(temp);
}

inline void init_portpin()
{
	ROW0IO=1;
	ROW1IO=1;
	ROW2IO=1;
	ROW3IO=1;
	COLUMN0IO=0;
	COLUMN1IO=0;
	COLUMN2IO=0;
	COLUMN3IO=0;
}

inline void allrowlogic0()
{
	//ROW0LAT=0;
	//ROW1LAT=0;
	//ROW2LAT=0;
}

inline void allcolumnlogic1()
{
	COLUMN0LAT=1;
	COLUMN1LAT=1;
	COLUMN2LAT=1;
	COLUMN3LAT=1;
}

inline unsigned char scanrow()
{
	if(ROW0==1)
	{		
		return 0;
	}
	else if(ROW1==1)
	{
		return 1;
	}
	else if(ROW2==1)
	{
		return 2;
	}
	else if(ROW3==1)
	{
		return 3;
	}
	else 
	{
		return (0xff);
	}
}

inline unsigned char keyrelease()
{
	unsigned char result;
	allcolumnlogic1();
	delay();
	if(ROW0 == 0 && ROW1 == 0 && ROW2== 0 && ROW3== 0)
	{
		result=1;
	}
	else
	{
		result=0;
	}
	return(result);
}

inline unsigned char key_press()
{
	if(scanrow()!= 0xFF)
	return 1;

	else
	return 0;
}
	
inline unsigned char getkey()
{
	unsigned char row,column,keypad;	
    init_portpin();
	for(column=0;column<4;column++)
	{
		row=columnnum1(column);
		if(row != 0xFF)
		break;
	}
	if(column==4)
	{
		keypad='X';//0xff;
		return(keypad);
	}
	keypad=keyeqv[row][column];
	return(keypad);
}

inline unsigned char columnnum1(unsigned char rowno)
{
	switch(rowno)
	{
		case 0:
			all0exceptcolumn1();
			break;
		case 1:
			all0exceptcolumn2();
			break;
		case 2:
			all0exceptcolumn3();
			break;
		case 3:
			all0exceptcolumn4();
			break;
	}
	delay();
	return scanrow();
}
inline void all0exceptcolumn1()
{
	COLUMN0LAT=1;
	COLUMN1LAT=0;
	COLUMN2LAT=0;
	COLUMN3LAT=0;
}
inline void all0exceptcolumn2()
{
	COLUMN0LAT=0;
	COLUMN1LAT=1;
	COLUMN2LAT=0;
	COLUMN3LAT=0;
}
inline void all0exceptcolumn3()
{
	COLUMN0LAT=0;
	COLUMN1LAT=0;
	COLUMN2LAT=1;
	COLUMN3LAT=0;
}
inline void all0exceptcolumn4()
{
	COLUMN0LAT=0;
	COLUMN1LAT=0;
	COLUMN2LAT=0;
	COLUMN3LAT=1;
}

inline void delay()
{
	unsigned int i;
	for(i=0;i<=1500;i++);//200
}

inline void debounce_delay()
{
	delay();
	delay();
	delay();
	delay();
	delay();
	delay();
}

/* END keypad */

inline void key_application(unsigned char key)
{	
		if(setmemloc==1)
		{
			if(key != 'G')
			{
				key='V';	//for no action
			}	
		}
		if(setrecall==1)
		{
			if(key != 'C')
			{
				key='V';	//for no action
			}	
		}
		if(key== 'N')		//cc/cv selection key
		{
			key=0;
			offallkeyf=1;
			INTCON2bits.DISI=0;
			DISICNTbits.DISICNT=0x3FFF;
			INTCON2bits.DISI=1;
			if(Type.fcaw==0)	// mma mode
			{
				Type.mma=0;
				Type.mig=1;
				Type.tig=1;
				Type.fcaw=1;
				memdata=EEPROM_Read(23*2);
				memdata=((memdata & 0xFF7F)| 0x0080);
				EEPROM_Erase_Write((23*2),memdata);				//FCAW LED OFF LD24
				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);    //TIG & MIG LED OFF
				memdata=EEPROM_Read(22*2);
				memdata=(memdata & 0xEFFF);
				EEPROM_Erase_Write((22*2),memdata);				//MMA LED ON LD24 HIGH
				;
				WeldMode=0x01;	
      			EEPROM_Erase_Write((36*2),WeldMode); 
				;
				readmematstrt();
				TypeU.LEDGROUP[0]=0xFF; 
				TypeU.LEDGROUP[1]=0xFF;
				TypeU.LEDGROUP[2]=0xFF;		
				TypeU.LEDGROUP[3]=0xFF;
				TypeU.LEDGROUP[4]=0xFF;
				Type.mma=0;
				Type.mig=1;
				Type.tig=1;
				Type.fcaw=1;
				VRDRELAYLAT=0;		//tig mode disable
				CCCVCTRLLAT=1;
				Type.amp=0;
			
                		for(ijk=0;ijk<=1000;ijk++)	
                		for(abc=0;abc<100;abc++);
               		genref(para.pwmtime1);
			}
                 
                 else if(Type.mma==0) //&& (mc_model !='A' || mc_model !='B'))	// Tig mode
			{
				Type.mma=1;
				Type.mig=1;
				Type.tig=0;
				Type.fcaw=1;

				memdata=EEPROM_Read(22*2);
				memdata=((memdata & 0xEFFF) | 0x1000); 
				EEPROM_Erase_Write((22*2),memdata);				//MMA LED OFF LD24 HIGH

				memdata=EEPROM_Read(23*2);
				memdata=((memdata & 0xFF7F)| 0x0080);  			//FCAW LED OFF LD24 HIGH
				EEPROM_Erase_Write((23*2),memdata);

				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);	//TIG LED ON & MIG LED OFF
				WeldMode=0x02;	
      			EEPROM_Erase_Write((36*2),WeldMode);    
				readmematstrt();
				TypeU.LEDGROUP[0]=0xFF; 
				TypeU.LEDGROUP[1]=0xFF;
				TypeU.LEDGROUP[2]=0xFF;		
				TypeU.LEDGROUP[3]=0xFF;
				TypeU.LEDGROUP[4]=0xFF;
				Type.mma=1;
				Type.mig=1;
				Type.tig=0;
				Type.fcaw=1;
				Type.amp=0;
				CCCVCTRLLAT=1;
				cccvmode=1;
				VRDRELAYLAT=1;		//tig mode enable
							
				for(ijk=0;ijk<=1000;ijk++)	
                		for(abc=0;abc<100;abc++);
				genref(para.pwmtime1);
			}
			else if(Type.tig==0)		//mig mode
			{
				tempdata=para.migws;
				para.weld.wfs=tempdata;
				Type.mma=1;
				Type.mig=0;
				Type.tig=1;
				Type.fcaw=1;
				memdata=EEPROM_Read(22*2);
				memdata=((memdata & 0xEFFF) | 0x1000); 
				EEPROM_Erase_Write((22*2),memdata);				//MMA LED OFF LD24 HIGH

				memdata=EEPROM_Read(23*2);
				memdata=((memdata & 0xFF7F)| 0x0080);  			//FCAW LED OFF LD24 HIGH
				EEPROM_Erase_Write((23*2),memdata);

				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);	//TIG LED OFF & MIG LED ON
				

				WeldMode=0x03;	
      			EEPROM_Erase_Write((36*2),WeldMode);  
				readmematstrt();
				CCCVCTRLLAT=0;
				cccvmode=0;
				VRDRELAYLAT=1;		//tig mode disable
			
				for(ijk=0;ijk<=1000;ijk++)	
                		for(abc=0;abc<100;abc++);
			}
			else if(Type.mig==0)		//fcaw mode
			{
				tempdata=para.migws;
				para.weld.wfs=tempdata;
				Type.mma=1;
				Type.mig=1;
				Type.tig=1;
				Type.fcaw=0;
				
				memdata=EEPROM_Read(22*2);
				memdata=((memdata & 0xEFFF) | 0x1000);
				EEPROM_Erase_Write((22*2),memdata);				//MMA LED OFF LD24 HIGH

				memdata=EEPROM_Read(23*2);
				memdata=(memdata & 0xFF7F);  						//FCAW LED ON LD24 HIGH
				EEPROM_Erase_Write((23*2),memdata);

				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);	//TIG LED OFF & MIG LED OFF

				WeldMode=0x04;	
      			EEPROM_Erase_Write((36*2),WeldMode); 
				readmematstrt();
				Type.mma=1;
				Type.mig=1;
				Type.tig=1;
				Type.fcaw=0;
				CCCVCTRLLAT=0;
				cccvmode=0;
				VRDRELAYLAT=1;		//tig mode disable
								 
				for(ijk=0;ijk<=1000;ijk++)	
                		for(abc=0;abc<100;abc++);
			}
			modechangef=1;
		}
		else if(key == 'H') //menu key
		{
			key=0;
			if(Type.mig==0 || Type.fcaw==0 )//working in mig mode
			{
				if(Type.multispot==1 && Type.spot==1 && Type.fourt==1)				//twot mode only 
				{
					if(Type.weld==0 && modeset==0)
					{
					TypeU.LEDGROUP[1]=0XFF;
					Type.preflow=0;
					modeset=1;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.time=0;
					win2dpcnt=float_to_ascii_str(&win2[0],para.preflow.time);
					win1[0]='P';
					win1[1]='R';
					win1[2]='E';
					win1dpcnt=3;
				}
				else if(Type.preflow==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.weld=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.amp=0;
					Type.voltage=0;
					win1dpcnt=float_to_ascii_str(&win1[0],fbvtg);
					win2dpcnt=float_to_ascii_str(&win2[0],para.pwmtime);
					win2[2]='0';	
				}
				else if(Type.weld==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.burnback=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.time=0;
					//
					para.spottimef=0;
					para.pausetimef=0;
					para.burnbackf=1;
					para.postflowf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
					win1[0]='B';
					win1[1]='R';
					win1[2]='N';
					win1dpcnt=3;
					//win2[2]=0;
				}
				else if(Type.burnback==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.postflow=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.time=0;
					//
					para.spottimef=0;
					para.pausetimef=0;
					para.burnbackf=0;
					para.postflowf=1;
					win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
					win1[0]='P';
					win1[1]='S';
					win1[2]='T';
					win1dpcnt=3;
					//win2[2]=0;
				}
				else if(Type.postflow==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.preflow=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.time=0;
					win2dpcnt=float_to_ascii_str(&win2[0],para.preflow.time);
					win1[0]='P';
					win1[1]='R';
					win1[2]='E';
					win1dpcnt=3;
				}
			}
			//*******
			else if(Type.fourt==0)				//fourt mode only 
			{
				if(Type.weld==0 && modeset==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.preflow=0;
					modeset=1;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.time=0;
					win2dpcnt=float_to_ascii_str(&win2[0],para.preflow.time);
					win1[0]='P';
					win1[1]='R';
					win1[2]='E';
					win1dpcnt=3;
				}
				else if(Type.preflow==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.weld=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.amp=0;
					Type.voltage=0;
					win1dpcnt=float_to_ascii_str(&win1[0],fbvtg);
					win2dpcnt=float_to_ascii_str(&win2[0],para.pwmtime);
					win2[2]='0';	
				}
				else if(Type.weld==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.crater=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.cratcurr=0;
					Type.cratvolt=0;
					win1dpcnt=float_to_ascii_str(&win1[0],para.crater.wfs);
					win2dpcnt=float_to_ascii_str(&win2[0],para.crater.volts);
				}
				else if(Type.crater==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.burnback=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.time=0;
					//
					para.spottimef=0;
					para.pausetimef=0;
					para.burnbackf=1;
					para.postflowf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
					win1[0]='B';
					win1[1]='R';
					win1[2]='N';
					win1dpcnt=3;
					//win2[2]=0;
				}
				else if(Type.burnback==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.postflow=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.time=0;
					//
					para.spottimef=0;
					para.pausetimef=0;
					para.burnbackf=0;
					para.postflowf=1;
					win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
					win1[0]='P';
					win1[1]='S';
					win1[2]='T';
					win1dpcnt=3;
					//win2[2]=0;
				}
				else if(Type.postflow==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.preflow=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.time=0;
					win2dpcnt=float_to_ascii_str(&win2[0],para.preflow.time);
					win1[0]='P';
					win1[1]='R';
					win1[2]='E';
					win1dpcnt=3;
				}
			}
			//*******
			else
			{
				if(Type.postflow==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.weld=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.amp=0;
					Type.voltage=0;
					win1dpcnt=float_to_ascii_str(&win1[0],fbvtg);
					win2dpcnt=float_to_ascii_str(&win2[0],para.pwmtime);
					win2[2]='0';	
				}
				
				else if(Type.weld==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.burnback=0;
					para.spottimef=0;
					para.pausetimef=0;
					para.burnbackf=1;
					para.postflowf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
					win1[0]='B';
					win1[1]='R';
					win1[2]='N';
					win1dpcnt=3;
					//win2[2]=0;	
				}
				else if(Type.burnback==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					//Type.burnback=1;
					Type.postflow=0;
					para.spottimef=0;
					para.pausetimef=0;
					para.burnbackf=0;
					para.postflowf=1;
					win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
					win1[0]='P';
					win1[1]='S';
					win1[2]='T';
					win1dpcnt=3;
					//win2[2]=0;
				}	
			}
		 }//
		/*else if(Type.mig==1 && Type.tig==0)//working in mig mode
		{
			if(Type.twot==0)
			{
				if(Type.weld==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.burnback=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.time=0;
					//
					para.spottimef=0;
					para.pausetimef=0;
					para.burnbackf=1;
					para.postflowf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
					win1[0]='B';
					win1[1]='R';
					win1[2]='N';
					win1dpcnt=3;
					//win2[2]=0;
				}
				else if(Type.burnback==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.weld=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.amp=0;
					Type.voltage=0;
					win1dpcnt=float_to_ascii_str(&win1[0],fbvtg);
					win2dpcnt=float_to_ascii_str(&win2[0],para.pwmtime);
					win2[2]='0';	
				}
			}
			else if(Type.fourt==0)
			{
				if(Type.weld==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.crater=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.cratcurr=0;
					Type.cratvolt=0;
					win1dpcnt=float_to_ascii_str(&win1[0],para.crater.wfs);
					win2dpcnt=float_to_ascii_str(&win2[0],para.crater.volts);
				}
				else if(Type.crater==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.burnback=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.time=0;
					//
					para.spottimef=0;
					para.pausetimef=0;
					para.burnbackf=1;
					para.postflowf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
					win1[0]='B';
					win1[1]='R';
					win1[2]='N';
					win1dpcnt=3;
					//win2[2]=0;
				}
				else if(Type.burnback==0)
				{
					TypeU.LEDGROUP[1]=0XFF;
					Type.weld=0;
					//;
					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
					Type.amp=0;
					Type.voltage=0;
					win1dpcnt=float_to_ascii_str(&win1[0],fbvtg);
					win2dpcnt=float_to_ascii_str(&win2[0],para.pwmtime);
					win2[2]='0';	
				}
			}
		}*/
		}//end of Menu key
		else if(key == 'F')
		{
			key=0;
			if(WeldMode==0x03)
			{
				if(Type.fe==0)
				{
					Type.fe=1;
					Type.nic=0;
					Type.zeropteight=0;
					Type.oneptzero=1;
					Type.onepttwo=1;
					Type.oneptsix=1;
					
					Type.arco2=0;
					Type.co2=1;
					Type.ar=1;
					Type.aro2=1;
				}
				else if((Type.nic==0) && (mc_model!='C'))
				{
					Type.nic=1;
					Type.alu=0;
					Type.zeropteight=1;
					Type.oneptzero=1;
					Type.onepttwo=0;
					Type.oneptsix=1;
					Type.arco2=1;
					Type.co2=1;
					Type.ar=0;
					Type.aro2=1;
				}	
				else if((Type.nic==0) && (mc_model=='C'))
				{
					Type.nic=1;
					//Type.alu=0;
					Type.fe=0;
					Type.zeropteight=0;
					Type.oneptzero=1;
					Type.onepttwo=1;
					Type.oneptsix=1;
					Type.arco2=0;
					Type.co2=1;
					Type.ar=1;
					Type.aro2=1;
				}	

				else if(Type.alu==0)
				{
					Type.alu=1;
					//Type.tig=1;
					Type.fe=0;
					Type.zeropteight=0;
					Type.oneptzero=1;
					Type.onepttwo=1;
					Type.oneptsix=1;
					Type.arco2=0;
					Type.co2=1;
					Type.ar=1;
					Type.aro2=1;
				}
			}
		}//end of material key

		else if(key == 'J')
		{
			key=0;
			if(WeldMode==0x03)
			{
				if(Type.fe==0)
				{
					if(Type.zeropteight==0)
					{
						Type.zeropteight=1;
						Type.oneptzero=0;
					}
					else if(Type.oneptzero==0)
					{
						Type.oneptzero=1;
						Type.onepttwo=0;
					}	
					else if((Type.onepttwo==0) && (mc_model !='C'))
					{
						Type.onepttwo=1;
						Type.oneptsix=0;
					}
					else if((Type.onepttwo==0) && (mc_model =='C'))
					{
						Type.onepttwo=1;
						Type.zeropteight=0;
					}
					else if((Type.oneptsix==0) && (mc_model!='C'))
					{
						Type.oneptsix=1;
						Type.zeropteight=0;
					}
				}
				else if(Type.nic==0)
				{
					if(Type.zeropteight==0)
					{
						Type.zeropteight=1;
						Type.onepttwo=0;
					}
					else if(Type.onepttwo==0) 
					{
						Type.onepttwo=1;
						Type.oneptsix=0;
						//Type.zeropteight=0;
					}
					else if(Type.oneptsix==0)   //SS 1.6 data addition
					{
						Type.oneptsix=1;
						Type.zeropteight=0;
					
					
					}	
				}
				else if(Type.alu==0)
				{
						Type.zeropteight=1;
						Type.oneptzero=1;
						Type.onepttwo=0;
						Type.oneptsix=1;
				}
			}
			else if (WeldMode==0x04)
			{
				if(Type.fe==0)
				{
					if((Type.onepttwo==0) && (mc_model !='C'))
					{
						Type.onepttwo=1;
						Type.oneptsix=0;
					}
					else if((Type.oneptsix==0) && (mc_model !='C'))
					{
						Type.oneptsix=1;
						Type.onepttwo=0;
					}
					else
					{
						Type.onepttwo=0;
						Type.oneptsix=1;
					}
				   
				}
			}

		}//end of mm key
		else if(key == 'B')
		{
			key=0;
			if(WeldMode==0x03)
			{
				if(Type.fe==0)
				{
					if(Type.arco2==0)
					{
						Type.arco2=1;
						Type.co2=0;
					}
					else if(Type.co2==0)
					{
						Type.co2=1;
						Type.arco2=0;
					}	
				}
				else if((Type.nic==0) && (mc_model!='C'))
				{
					if(Type.arco2==0)
					{
						Type.arco2=1;
						Type.aro2=0;
					}
					else if(Type.aro2==0)
					{
						Type.aro2=1;
						Type.arco2=0;
					}	
				}
				else if((Type.nic==0) && (mc_model=='C'))		//for Champ multi 400
				{
					if(Type.arco2==0)
					{
						Type.arco2=1;
						Type.ar=0;
					}
					else if(Type.ar==0)
					{
						Type.ar=1;
						Type.arco2=0;
					}	
				}	




				else if(Type.alu==0)
				{
						Type.arco2=1;
						Type.co2=1;
						Type.ar=0;
						Type.aro2=1;
				}
			}
			else if(WeldMode==0x04)
			{
				if(Type.fe==0)
				{
					 if(Type.co2==0)
					{
						Type.arco2=1;
						Type.co2=0;
						Type.ar=1;
						Type.aro2=1;
					}	
				}
			}
		}//end of gas key
		
		else if(key=='K')
		{
			key=0;
			modeset=0;
			if(Type.multispot==0)
			{
				Type.multispot=1;
				Type.spot=0;
				Type.crateron=1;					//crater is enabled only in fourt mode
			
				TypeU.LEDGROUP[1]=0XFF;
				Type.weld=0;
				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
				Type.speed=0;
				Type.voltage=0;
				
				para.spottimef=0;
				para.pausetimef=0;
				para.burnbackf=0;
				para.postflowf=0;
				
				Type.automan=1;
			}
			else if(Type.spot==0)
			{
				Type.spot=1;
				Type.fourt=0;
				Type.crateron=1;					//crater is enabled only in fourt mode
				
				TypeU.LEDGROUP[1]=0XFF;
				Type.weld=0;
				
				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
				Type.amp=0;
				Type.voltage=0;
			
				para.spottimef=0;
				para.pausetimef=0;
				para.burnbackf=0;
				para.postflowf=0;
			}	
			else if(Type.fourt==0)
			{
				Type.fourt=1;
				Type.twot=0;
				Type.crateron=1;					//crater is enabled only in fourt mode
				TypeU.LEDGROUP[1]=0XFF;
				Type.weld=0;
				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
				Type.amp=0;
				Type.voltage=0;
				para.spottimef=0;
				para.pausetimef=0;
				para.burnbackf=0;
				para.postflowf=0;
			}
			else if(Type.twot==0)
			{
				Type.twot=1;
				//if(Type.tig==0)
				//Type.fourt=0;
		       	//else if(Type.mig==0 || Type.fcaw==0 )
				Type.multispot=0;
				Type.crateron=1;					//crater is enabled only in fourt mode
				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
				Type.speed=0;//1;
				Type.voltage=0;//1;
				TypeU.LEDGROUP[1]=0XFF;
				Type.weld=0;//1;
				para.spottimef=0;//1;
				para.pausetimef=0;
				para.burnbackf=0;
				para.postflowf=0;
				Type.automan=1;
			}
		}//end of scan mode key 
		
		else if(key=='L')
		{
			key=0;
			if(Type.automan==0)
			{
				Type.automan=1;		//manual mode enable
			}	
			else
			{
					autooffset=0;		//clear offset
					preweldvtg=0;
					if(Type.twot==0 || Type.fourt==0)
					{
						Type.automan=0;		//auto mode enable
					}
			}
		}
		else if(key=='D')
		{
			key=0;
			modeset=0;
			
			/*if(setupmode==1)
			{
				if(Type.mma==1 && Type.mig==0 && Type.tig==1)
				{
					if(setpt1==1 && setpt2==0 && slopept1==0 && slopept2==0)
					{
						setpt1=0;  //use for setting multiplier in current setting.
						setpt2=1;
						slopept1=0;
						slopept2=0;
					}
					else if(setpt1==0 && setpt2==1 && slopept1==0 && slopept2==0)
					{
						setpt1=0;  //use for setting multiplier in current setting.
						setpt2=0;
						slopept1=1;
						slopept2=0;
						pwmtime1=400;
					}
					else if(setpt1==0 && setpt2==0 && slopept1==1 && slopept2==0)
					{
						setpt1=0;  //use for setting multiplier in current setting.
						setpt2=0;
						slopept1=0;
						slopept2=1;
						pwmtime1=500;
					}
				}
				else if(Type.mma==0 && Type.mig==1 && Type.tig==1)
				{
					if(slopept1==1 && slopept2==0)
					{
						slopept1=0;
						slopept2=1;
						pwmtime1=400;
					}
				}
			}*/
		  	if(Type.mma == 0)
			{
				Type.arcforce=~Type.arcforce;
			}
			else if(Type.twot==0 || Type.fourt==0)
			{
				if(passprotect==0 && setpasswordf==0 && enblpasskey==0)
				{
					win1[0]='L';
					win1[1]='C';
					win1[2]='K';
					win1dpcnt=3;
					win2dpcnt=float_to_ascii_str(&win2[0],password);//-=1;
					setpasswordf=1;
				}
				else if(passprotect==1 && enblpasskey==0)
				{
					win1[0]='P';
					win1[1]='A';
					win1[2]='S';
					win1dpcnt=3;
					passtemp=0;
					win2dpcnt=float_to_ascii_str(&win2[0],passtemp);
					setpasswordf=1;
				}
				else if(setpasswordf==1 && enblpasskey==0)//setup for password saving
				{
					mesgsvd=1;
					count_1ms=0;
					count_10ms=0;
					count_100ms=0;
					count_1sec=0;
				}
				else if(enblpasskey==1)
				{
					chkpass=1;
					count_1ms=0;
					count_10ms=0;
					count_100ms=0;
					count_1sec=0;
				}
			}
			else if(Type.multispot ==0 && Type.burnback==0)
			{
				if(para.spottimef==1)
				{
					para.spottimef=0;
					para.pausetimef=1;
					para.burnbackf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],para.pausetime);
					win1[0]='P';
					win1[1]='T';
					win1[2]='M';
					win1dpcnt=3;
				}
				else if(para.pausetimef==1)
				{
					para.spottimef=0;
					para.pausetimef=0;
					para.burnbackf=1;
					win2dpcnt=float_to_ascii_str(&win2[0],para.burnback.time);
					win1[0]='B';
					win1[1]='R';
					win1[2]='N';
					win1dpcnt=3;
				}
				else if(para.burnbackf==1)
				{
					para.spottimef=1;
					para.pausetimef=0;
					para.burnbackf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],para.spottime);
					win1[0]='S';
					win1[1]='T';
					win1[2]='M';
					win1dpcnt=3;
				}
			}
			else if(Type.multispot ==0 && Type.postflow==0)
			{
				if(para.spottimef==1)
				{
					para.spottimef=0;
					para.pausetimef=1;
					para.postflowf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],para.pausetime);
					win1[0]='P';
					win1[1]='T';
					win1[2]='M';
					win1dpcnt=3;	
				}
				else if(para.pausetimef==1)
				{
					para.spottimef=0;
					para.pausetimef=0;
					para.postflowf=1;
					win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
					win1[0]='P';
					win1[1]='S';
					win1[2]='T';
					win1dpcnt=3;
				}
				else if(para.postflowf==1)
				{
					para.spottimef=1;
					para.pausetimef=0;
					para.postflowf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],para.spottime);
					win1[0]='S';
					win1[1]='T';
					win1[2]='M';
					win1dpcnt=3;
				}
			}
			else if(Type.spot ==0 && Type.burnback==0)
			{
				if(para.spottimef==1)
				{
					para.spottimef=0;
					para.pausetimef=0;
					para.burnbackf=1;
					win2dpcnt=float_to_ascii_str(&win2[0],para.burnback.time);
					win1[0]='B';
					win1[1]='R';
					win1[2]='N';
					win1dpcnt=3;
				}
				else if(para.burnbackf==1)
				{
					para.spottimef=1;
					para.pausetimef=0;
					para.burnbackf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],para.spottime);
					win1[0]='S';
					win1[1]='T';
					win1[2]='M';
					win1dpcnt=3;
				}
			}
			else if(Type.spot ==0 && Type.postflow==0)
			{
				if(para.spottimef==1)
				{
					para.spottimef=0;
					para.pausetimef=0;
					para.postflowf=1;
					win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
					win1[0]='P';
					win1[1]='S';
					win1[2]='T';
					win1dpcnt=3;
				}
				else if(para.postflowf==1)
				{
					para.spottimef=1;
					para.pausetimef=0;
					para.postflowf=0;
					win2dpcnt=float_to_ascii_str(&win2[0],para.spottime);
					win1[0]='S';
					win1[1]='T';
					win1[2]='M';
					win1dpcnt=3;
				}
			}
			//Type.extra=~(Type.extra);	
		}	 	 
		
		else if(key=='G')
		{
			key=0;
			/*if(setupmode==0 && setpasswordf==1)//setup for password saving
			{
				
					mesgsvd=1;
					count_1ms=0;
					count_10ms=0;
					count_100ms=0;
					count_1sec=0;
			}
			else*/ 
                if(setmemloc==0 && Type.automan==1)
			{
					win2dpcnt=float_to_ascii_str(&win2[0],memlocation);
					win1[0]='L';
					win1[1]='O';
					win1[2]='C';
					win1dpcnt=3;
					setmemloc=1;
					displprev=0;
					Type.save=0;
			}
			else if(setmemloc==1)
			{
					win1dpcnt=float_to_ascii_str(&win1[0],fwirespeed);
					win2dpcnt=float_to_ascii_str(&win2[0],fpwmtime);
					//win2dpcnt=float_to_ascii_str(&win2[0],fbvtg);
					if(win1dpcnt==1)
					{
						win1[2]='/';					//for display empty display
					}
					if(win2dpcnt==1)
					{
						win2[2]='/';
					}
					displprev=1;
					count_1ms=0;
					count_10ms=0;
					count_100ms=0;
					count_1sec=0;
			}
			
		}
		else if(key=='C')
		{
			key=0;
			if(setrecall==0 && Type.automan==1)
				{
					win2dpcnt=float_to_ascii_str(&win2[0],memlocation);
					win1[0]='L';
					win1[1]='O';
					win1[2]='C';
					win1dpcnt=3;
					setrecall=1;
					displprev=0;
					Type.recall=0;
				}
			else if(setrecall==1)
			{
					memlocation=updatedata(memlocation,1,10,encres);
					win2dpcnt=float_to_ascii_str(&win2[0],memlocation);
					if(win2dpcnt==1)
					{
						win2[2]='/';		//for disply empty display
					}
					win1[0]='R';
					win1[1]='C';
					win1[2]='L';
					win1dpcnt=3;
					count_1ms=0;
					count_10ms=0;
					count_100ms=0;
					count_1sec=0;
					disprcl=1;
			}
		
		}
		else if(key=='M')
		{
					//trans('P');
					if(Type.mig==0)
					{
					//	multi1=para.currmult;
					//	multi2=para.currmult;
						setpt1=1;
						setpt2=0;
					//	win2dpcnt=float_to_ascii_str(&win2[0],para.currmult);
						win1[0]='C';
						win1[1]='U';
						win1[2]='R';
						win1dpcnt=3;
						setupmode=1;
						ARCONLAT=1;				//torch high signal
						///******CONTACTORLAT=1;
				    }  
				   else if(Type.mma==0)
				   {
						pwmtime1=190;
						slopept1=1;
						slopept2=0;
						win1[0]='C';
						win1[1]='U';
						win1[2]='R';
						win1dpcnt=3;
						setupmode=1;
				   }
		}
		else if(key=='Q')
		{
			if(passprotect==0)
			{
				win1[0]='L';
				win1[1]='C';
				win1[2]='K';
				win1dpcnt=3;
				win2dpcnt=float_to_ascii_str(&win2[0],password);//-=1;
				setpasswordf=1;
			}
			else
			{
				win1[0]='P';
				win1[1]='A';
				win1[2]='S';
				win1dpcnt=3;
				passtemp=0;
				win2dpcnt=float_to_ascii_str(&win2[0],passtemp);
				setpasswordf=1;
			}
		}
	
		else if(key=='O')			// 'O' encoder 2 switch
		{
			if(cyclestrt==0)
			{
				if(Type.fourt==0)
				{	
					Type.crateron=~Type.crateron;			
				}
	            	if(Type.mig==0 || Type.fcaw==0)
				{
					if(mesgdispf==0)
					{
						mesgdispf=1;
						count_1ms=0;
					  	count_10ms=0;
					   	count_100ms=0;
					   	count_1sec=0;
					}
				}
			}
			
		}		
		else if(key=='R')
		{
				
			for (memcntr=0;memcntr<=512;memcntr++)		//496 512 clear all eeprom memory. last 16 location are used for factory setting from 7fffe0 t0 =7fffff
				{
						EE_Addr=(memcntr*2);						
						EE_Data=0xFFFF;	
						EEPROM_Erase_Write(EE_Addr,EE_Data);
				}
			//********************************************************
					//para.password=0x0000;
				/*	para.passprotect=0x0000;
					//		EEPROM_Erase_Write((25*2),para.password);
							EEPROM_Erase_Write((26*2),para.passprotect);
							for(cntpass=1;cntpass<=10;cntpass++)
							{
								EE_Addr=(40*cntpass*2)+(25*2);
				 //				EE_Data=para.password;
								EEPROM_Erase_Write(EE_Addr,EE_Data);
								EE_Addr=(40*cntpass*2)+(26*2);
								EE_Data=para.passprotect;
								EEPROM_Erase_Write(EE_Addr,EE_Data);
							}//
			//
			//	para.currmult= EEPROM_Read(2*511);		//read last location
				for(resnum1=1;resnum1<=11;resnum1++)	//write again in current multiplier location
				{
					EE_Addr=resnum2 + (32*2*resnum1);				//storing data at 0031 memory location
			//		EE_Data=para.currmult;
					EEPROM_Erase_Write(EE_Addr,EE_Data);
					resnum2=resnum2 + 16;
				}

				resnum2=0;
				//;
				cvslope= EEPROM_Read(2*509);		//read last location
				ccslope= EEPROM_Read(2*508);		//read last location
				EEPROM_Erase_Write((34*2),cvslope);
				EEPROM_Erase_Write((35*2),ccslope);
				*/

				win1[0]='R';
				win1[1]='S';
				win1[2]='T';
				win1dpcnt=3;
				win2[0]='R';
				win2[1]='S';
				win2[2]='T';
				win2dpcnt=3;
				readmematstrt();
				for(i=0;i<2000;i++)//5000 200
				delay();
		}

		else if(key=='S')
		{
			/*arconsec=0;
			arconmin=0;
			arconhr=0;
			EEPROM_Erase_Write((39*2),arconsec);
			EEPROM_Erase_Write((38*2),arconmin);
			EEPROM_Erase_Write((37*2),arconhr);
			win1[0]='A';
			win1[1]='R';
			win1[2]='C';
			win1dpcnt=3;
			win2[0]='R';
			win2[1]='S';
			win2[2]='T';
			win2dpcnt=3;
			for(i=0;i<2000;i++)//5000 200
			delay();*/
		}
}
