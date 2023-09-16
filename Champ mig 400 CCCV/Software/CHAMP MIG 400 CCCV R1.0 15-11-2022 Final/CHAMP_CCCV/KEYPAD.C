/*	
	S1	|	S2  |   S3 |
	----------------------
	S4	|	S5	|	EN3	|
	----------------------
	S6	|	S7	|	EN2	|					
	----------------------
	S8	|	S9	|	EN1	|					
	----------------------
	A-S1	-MATERIAL/OCV
	B-S2	-DIAMETER/INCH
	C-S3	-GAS FLOW 
	D-S4	-UP KEY
	E-S5	-DOWN KEY
	F-EN3	-CURRENT ENCODER
	G-S6	-WELDMODE
	H-S7	-DISPLAY1
	I-EN2	-VOLTAGE ENCODER
	J-S8	-2T/4T SELECTION.
	K-S9	-DISPLAY2.
	L-EN1	-PARA ENCODER


#define 		ROWSIZE		4
#define			COLUMNSIZE	3

const unsigned char keyeqv[ROWSIZE][COLUMNSIZE]=	
														{	{'A','B','C'},
															{'D','E','F'},
															{'G','H','I'},
															{'J','K','L'}
														};
*/
unsigned char keypad_read()
{
	//unsigned char temp=0;
	init_keyportpin();
	allcolumnlogic1();
	ans=key_press();
	if(ans==1)			//any key is pressed.
	{
		ans=0;
		tempkey=getkey();
		debounce_delay();
	}
	else
	{
		tempkey='Z';//LEDLAT=0;
	}
	return(tempkey);
}

inline void init_keyportpin()
{
	ROW1IO=1;
	ROW2IO=1;
	ROW3IO=1;
	ROW4IO=1;
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
	COLUMN1LAT=1;
	COLUMN2LAT=1;
	COLUMN3LAT=1;
}

inline unsigned char scanrow()
{
	if(ROW1==1)
	{		
		if(cSwitchPressfg == 0)
		{
			return 0;
		}
		else 
		{
			return(0Xff);
		}
	}
	else if(ROW2==1)
	{
		if(cSwitchPressfg == 0)
		{
			return 1;
		}
		else 
		{
			return(0Xff);
		}
	}
	else if(ROW3==1)
	{
		if(cSwitchPressfg == 0)
		{
			return 2;
		}
		else 
		{
			return(0Xff);
		}
	}
	else if(ROW4==1)
	{
		if(cSwitchPressfg == 0)
		{
			return 3;
		}
		else 
		{
			return(0Xff);
		}		
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
	keydelay();
	if(ROW1 == 0 && ROW2== 0 && ROW3== 0 && ROW4== 0 )
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
	//unsigned char row,column,keypad;	
    init_keyportpin();
	for(keycolumn=0;keycolumn<COLUMNSIZE;keycolumn++)
	{
		keyrow=columnnum1(keycolumn);
		if(keyrow != 0xFF)
		break;
	}
	if(keycolumn==COLUMNSIZE)
	{
		keypad='X';
		return(keypad);
	}
	keypad=keyeqv[keyrow][keycolumn];
	return(keypad);
}

inline unsigned char columnnum1(unsigned char columnno)
{
	switch(columnno)
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
	}
	keydelay();
	return scanrow();
}
inline void all0exceptcolumn1()
{
	COLUMN1LAT=1;
	COLUMN2LAT=0;
	COLUMN3LAT=0;
}
inline void all0exceptcolumn2()
{
	COLUMN1LAT=0;
	COLUMN2LAT=1;
	COLUMN3LAT=0;
}
inline void all0exceptcolumn3()
{
	COLUMN1LAT=0;
	COLUMN2LAT=0;
	COLUMN3LAT=1;
}

inline void keydelay()
{
	unsigned int i;
	for(i=0;i<=1500;i++);//200
}

inline void debounce_delay()
{
	keydelay();
	keydelay();
	keydelay();
	keydelay();
	keydelay();
	keydelay();
}


void key_application(unsigned char keypressed)//@called in main.c ==> while(1){ }
{
	if(keypressed =='A') 
	{
		if(weldmode == 'M')  //PPC
		{
			if(cMMAMenuMode==1)
			{
				if(iOffset >= 1)
				{
					iOffset = iOffset - 1;		
				}
					
			}
			/*if(cMMAMenuMode==2)
			{
				if(iSlope >= 1)
				{
					iSlope = iSlope - 1;		
				}	
			}
			if(cMMAMenuMode==3)
			{
				if(mma_vrd_time >= 1)
				{
					mma_vrd_time = mma_vrd_time - 5;		
				}	
			}		*/				
			cMMAparaupdatefg = 1;	
		}

		else if(weldmode=='G') 
		{
			if(cVoltoffMenuMode==1)
			{
				if(vOffset >= 1)
				{
					vOffset = vOffset - 1;		
				}
					
			}
			if(cMIGMenuMode==1)
			{
				if(mig_preflow >= 1)
				{
					mig_preflow = mig_preflow - 1;	
				}
			}
			if(cMIGMenuMode==2)
			{
				if(mig_burnback >= 1)
				{
					mig_burnback = mig_burnback - 1;	
				}
			}
			if(cMIGMenuMode==3)
			{
				if(mig_postflow >= 1)
				{
					mig_postflow = mig_postflow - 1;	
				}	
			}
			if(cMIGMenuMode==4)
			{
				if(mig_creepspeedrate >= 1)
				{
					mig_creepspeedrate = mig_creepspeedrate - 5;	
				}	
			}
			if(cMIGMenuMode==5)
			{
				if(mig_creepspeedtime >= 1)
				{
					mig_creepspeedtime = mig_creepspeedtime - 1;	
				}	
			}
			if(cMIGMenuMode==6)
			{			
				if(mig_Kp >= 1)
				{
					mig_Kp = mig_Kp - 1;
				}		
			}		
			if(cMIGMenuMode==7)
			{
				if(mig_Ki >= 1)
				{
					mig_Ki = mig_Ki - 1;
				}	
			}
			if(cMIGMenuMode==8)
			{
				if(mig_Kd >= 1)
				{
					mig_Kd = mig_Kd - 1;
				}	
			}
			if(cMIGMenuMode==9)
			{
				if(mig_Ka >= 1)
				{
					mig_Ka = mig_Ka - 1;
				}	
			}
			if(cMIGMenuMode==10)
			{
				if(mig_Kb >= 1)
				{
					mig_Kb = mig_Kb - 5;
				}	
			}
			if(cMIGMenuMode==11)
			{
				if(mig_Kc >= 1)
				{
					mig_Kc = mig_Kc - 1;//5;  //PPC
				}	
			}
												
			cMigWeldparaupdatefg=1;							
		}	
			
		//if((cMIGParaMenufg == 0) && (cGaSMenufg == 0) && (cVRDMenufg == 0))// && (cModeSelectDonefg == 0)) 
		if((cMIGParaMenufg == 0) && (cGaSMenufg == 0) && (cModeSelectDonefg == 0)&& (cVRDMenufg == 0))//PPC
		{
			if(weldmode=='M')
			{
				weldmode='T';  //@versa400
				
				TypeU.LEDGROUP[0]=0x00;
				Type.current		=1;
				Type.voltage		=1;
				TypeU.LEDGROUP[1]=0x00;
				Type.tig			=1;
				TypeU.LEDGROUP[2]=0x00;
				TypeU.LEDGROUP[3]=0x00; 

			}
			else if(weldmode=='T') //@versa400
			{
				weldmode='G';
				TypeU.LEDGROUP[0]=0x00;
				Type.wirespeed		=1;
				Type.voltage		=1;
				TypeU.LEDGROUP[1]=0x00;
				Type.mig			=1;
				Type.twot			=1;        //24-7-19
				TypeU.LEDGROUP[2]=0x00;
				TypeU.LEDGROUP[3]=0x00;
			}
			else if(weldmode=='G')
			{
				weldmode='M';
				TypeU.LEDGROUP[0]=0x00;
				Type.current	=1;
				Type.voltage	=1;
				TypeU.LEDGROUP[1]=0x00;
				Type.mma		=1;
				TypeU.LEDGROUP[2]=0x00;
				TypeU.LEDGROUP[3]=0x00;
				cDispSetCurrUpdatefg=1;
			}
			modechangef=1;
			TypeDP.DPGROUP[0]=0x00;
		}	
	}
		
	else if(keypressed == 'B') 
	{  	
		if(weldmode == 'G')
		{
			if(cMIGParaMenufg == 1)
			{					
			   cMIGMenumodelockfg=1;	    
			   cMIGMenuMode++;
			   cMenucnt++;
			   cMigWeldparaupdatefg=1;
			   if(cMIGMenuMode >= 5) //6//12)
			   {			  
			       cMIGMenuMode = 0;		       
			       cMIGParaMenufg=0;
				   cMIGMenumodelockfg = 0;
				   cMigWeldparaupdatefg=0;
				   iGasChkMenuModecnt=0;
				   cGasChkMenufg=0;	
			   }
			   cMIGMenu();							
			}
			if(cVoltageoffsetfg == 1)
			{
			   cMIGMenumodelockfg=1;	    
			   cVoltoffMenuMode++;
			   cMigWeldparaupdatefg=1;
               cMIGParaMenufg=1;
			   if(cVoltoffMenuMode >= 2)
			   {			  
			       cVoltoffMenuMode = 0;		       
			       cVoltageoffsetfg=0;
				   cMIGMenumodelockfg = 0;
				   cMigWeldparaupdatefg=0;
				   cEEPROMSavefg = 0;
				   iGasChkMenuModecnt=0;
				   cGasChkMenufg=0;	
                   cMIGParaMenufg=0;
			   }
			   cVoltageoffsetMenu();
			}
				
		}
	
		else if(weldmode == 'M')  //PPC
		{	
			if(cVRDMenufg == 1 && weldonf==1)
			{
			   cMMAmenumodelockfg=1;	    
			   cMMAMenuMode++;
			   cMMAparaupdatefg=1;
			   
			   if(cMMAMenuMode >= 2)//4 //PPC
			   {			  
			       cMMAMenuMode = 0;		       
			       cVRDMenufg=0;
				   cMMAmenumodelockfg = 0;
				   cMMAparaupdatefg=0;	
				   cEEPROMSavefg = 0;
							   
			   }
			 			   
			   MMAVRDMenu();				
			}
				
		}		
	}


	else if((keypressed =='D'))// && (weldmode=='G')) 
	{
		if(weldmode == 'M') //PPC
		{
			if(cMMAMenuMode==1)
			{
				iOffset = iOffset + 1;  //PPC
						
			}
			/*if(cMMAMenuMode==2)
			{
				iSlope = iSlope + 1;		
			}
			if(cMMAMenuMode==3)
			{
				mma_vrd_time = mma_vrd_time + 5;		
			}*/						
			cMMAparaupdatefg = 1;	
		}	
		else if(weldmode=='G') 
		{
			if(cVoltoffMenuMode==1)
			{
				vOffset = vOffset + 1;  //PPC
						
			}
			if(cMIGMenuMode==1)
			{
				mig_preflow = mig_preflow + 1;
			}
			if(cMIGMenuMode==2)
			{
				mig_burnback = mig_burnback + 1;	
			}
			if(cMIGMenuMode==3)
			{
				mig_postflow = mig_postflow + 1;	
			}
			if(cMIGMenuMode==4)
			{
				mig_creepspeedrate = mig_creepspeedrate + 5;	
			}			
			if(cMIGMenuMode==5)
			{
				mig_creepspeedtime = mig_creepspeedtime + 1;	
			}
			if(cMIGMenuMode==6)
			{
				mig_Kp = mig_Kp + 1;
			}		
			if(cMIGMenuMode==7)
			{
				mig_Ki = mig_Ki + 1;	
			}
			if(cMIGMenuMode==8)
			{
				mig_Kd = mig_Kd + 1;	
			}
			if(cMIGMenuMode==9)
			{
				mig_Ka = mig_Ka + 1;	
			}
			if(cMIGMenuMode==10)
			{
				mig_Kb = mig_Kb + 5;	
			}								
			if(cMIGMenuMode==11)
			{
				mig_Kc = mig_Kc + 1; //5; PPC	
			}			
			cMigWeldparaupdatefg=1;				
		}
		
		//if((cMIGParaMenufg == 0) && (cGaSMenufg == 0) && (cVRDMenufg == 0)) 
		if(weldmode=='G') 
		{
			if((cMIGParaMenufg == 0) && (cGaSMenufg == 0))
			{
			 	if(Type.twot==0)
			 	{		 	 
				 	Type.twot=1;
					Type.fourt=0;
					//MPWM = 0;	
			 	}
			 	else if(Type.twot==1)
			 	{
			 		Type.twot=0;
					Type.fourt=1;
					//MPWM = 1;	
			 	}		 			 	
			}
		}	
	}
}

/* END keypad */







