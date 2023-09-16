/*	
	S1	|	 S2 |	  S3|
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
	L-EN1	-CURRENTENCODER/parameter encoder


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
		return 0;
	}
	else if(ROW2==1)
	{
		return 1;
	}
	else if(ROW3==1)
	{
		return 2;
	}
	else if(ROW4==1)
	{
		if(ChkForAnotherfg == 0)// to check the two key press
		{
			return 3;
		}
		else {
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
	
	if((weldmode == 'P') || (weldmode == 'G'))
	{
			
		if((keypressed=='A') && (cMacMenufg == 1))
		{
				
			if(iSNocursor >= 1)
			{
				iSNocursor--;	
			}
			if(iSNocursor < 1)
			{
				iSNocursor = 1;
			}				
		}
		if((keypressed=='C') && (cMacMenufg == 1))	
		{			
			if(iSNocursor <= 4)
			{
				iSNocursor++;	
			}
			if(iSNocursor > 4)
			{
				iSNocursor = 4;
			}				
		}	
		
		
		if((keypressed=='B') && (cEnterOTPfg == 0) && (cMacMenufg == 0))
		{
			
			if(cPMainMenufg == 0)
			{
				cPMainMenufg = 1;
				MainMenuScreen();			
			}
			else
			{
				cPMainMenufg = 0;
				cMainScreenfg = 1;				
			}
		}
		if((keypressed=='A') && (cEnterOTPfg == 1))
		{
			//cTempfg = 1;
			iOTPCursor--;
			if(iOTPCursor <= 1)
			{
				iOTPCursor = 1;
			}
			cOTParray[iOTPCursor] = 0;	
		}			
		if((keypressed=='C') && (cEnterOTPfg == 1))
		{
			iOTPCursor++;
			if(iOTPCursor >= 4)
			{
				iOTPCursor = 4;
			}	
			cOTParray[iOTPCursor] = 0;			
		}
		/*if(keypressed=='A')
		{
			open_file("1245.CSV");
			delay1(1000);
			Insert_Header_of_File();
			delay1(100);
			cFileopenfg = 1;
		}
		if(keypressed=='C')
		{
			cFileopenfg = 0;
			delay1(100);			
			close_file("1245.CSV");
		}*/				
	}
	
	if((keypressed=='A') || (keypressed=='B') || (keypressed=='C'))	
	{		
		
		if(weldmode=='M')
		{
			update_MMA_syn_data(keypressed);	
		}		
		else if(weldmode=='T')
		{
			update_TIG_syn_data(keypressed);	
		}
		else if((weldmode=='G')&&(setlcdweldparameter == 0)&&(cMacMenufg == 0))
		{
/*
			if(keypressed=='A' && mig_ocv_check_f==1)
			{
				
			  //OCVON_command=1;
			  
			  SHDNLAT=ON;     //ocv on
			  TypeDP.DPGROUP[0]=0x00;
      		  Typedp.digitdp5		=1;
			  
			  diswin1[0]	='O';
	          diswin1[1]	='C';
	          diswin1[2]	='V';
 			  disp_hex_dec_volt(VOLTAGE); //ocv 99.9 on RHS display
 			  
			  //mig_ocv_check_f=0;
			  count_key_5000ms=0;
			  //Type.mma=1;
			
			}
			else
		    {
*/			    
				//update_MIG_syn_data(keypressed);
//				mig_ocv_check_f=0;
				//Type.mma=0;
				//SHDNLAT=0;
//			}	
		}
		else if((weldmode=='P')&&(setlcdweldparameter == 0)&&(cMacMenufg == 0))
		{			
/*
			if(keypressed=='A' && mig_ocv_check_f==1)
			{
				
			  //OCVON_command=1;
			  
			  SHDNLAT=ON;
			  
			  diswin1[0]	='O';
	          diswin1[1]	='C';
	          diswin1[2]	='V';
 			  disp_hex_dec_volt(VOLTAGE);
			  //mig_ocv_check_f=0;
			  count_key_5000ms=0;
			  //Type.mma=1;
			
			}
			else
		    {
*/		  
/*	
	TRANS1('A');
	TRANS1('D');
	TRANS1('O');
	TRANS1('R');	
*/			
			    //update_PMIG_syn_data(keypressed);
				mig_ocv_check_f=0;
				//Type.mma=0;
				SHDNLAT=0;
//			}
			//update_PMIG_syn_data(keypressed);
			//update_PMIG_pulse_para();
		}
		keychange1=1;
	}
	else if((keypressed=='D') && (setlcdweldparameter == 0) && (cMacMenufg == 0) && (weldmode=='M'))
	{
		iHots_Arcf_cnt--;
		if(iHots_Arcf_cnt <= 0)
			iHots_Arcf_cnt = 0;
			
		if(iHots_Arcf_cnt == 0)
		{
			lcdput(4,0,ar13);
			lcd_disp_hex_dec(para.mmamode.arcforce);
			arcforceupdate();						
		}
		else if (iHots_Arcf_cnt == 1)
		{
			lcdput(4,0,ar131);
			lcd_disp_hex_dec(iHotstartper);
			arcforceupdate();				
			
		}						
	}
	else if((keypressed=='D') && (setlcdweldparameter == 0) && (cMacMenufg == 0))
	{
		iMacMenuCntr++;
		if(cKeyPressStartfg == 0)
		{
			cKeyPressStartfg = 1;			
			iKeyDoubleChkCntr = KEYDOUBLECHKCNT;
		}	
		if(iMacMenuCntr > MACMENUCNTR)
		{
			clrlcd();			
			lcdput(0,0,"--Machine Setting--"); 
			lcdput(2,5,"MACHINE SERIAL NO"); 									
			cMacMenufg = 1;
			cMacMenuNo = 1;
			cCursorOnfg = 1;
			cCursorPosition = 0;
			cLineNo = 2;
			prevSerialN0 = 0;
			iSNocursor = 1;
			iMacMenuCntr = 0; 				
	 	}		
	}
	else if((keypressed=='D') && (cMacMenufg == 1))
	{
		
			
		// here up down menu 			
	}			
	else if((keypressed=='D' && setlcdweldparameter!=0)	&&(cMacMenufg == 0) && ((weldmode=='G') || (weldmode=='P'))	)		//@up keypressed
	{	
			if(lcdpage==1) 		
			{
				if(lcd_saverecall_ptr>=1)
				lcd_saverecall_ptr--;
				if(lcd_saverecall_ptr<=1)
				lcd_saverecall_ptr=1;
		
				
				lcdput(2,0,ar81);   				 //@Edit
				
				lcdput(3,0,ar86);    				//@mode
				pmig_auto_man_update();
				
				lcdput(4,0,ar87);   				//@Arc Time
				arcon_time_update();
				
				lcdput(5,0,ar82);  					//@save						    
				lcd_disp_hex_dec(save_location);
				save_update();   					//@print save location number
				
				lcdput(6,0,ar83);  					//@Recall  
				lcd_disp_hex_dec(Recall_location);                         
				recall_update();
				
			}
			else if(lcdpage==2 || lcdpage==3 ) 		//@ preflow settings
			{
				if(lcdmigpointer>=1)
					lcdmigpointer--;
				if(lcdmigpointer<=1)
					lcdmigpointer=1;
						
				if(lcdmigpointer<7)
				{
					lcdpage=2;
					if(lcdmigpointer==6) //
					{
					clrlcd();
					if(weldmode=='G')       
					lcdput_bold(0,0,ar34);   //ar34[]="MIG-PARAMETERS";
					else if(weldmode=='P')
					lcdput_bold(0,0,ar44);   //"PMIG-PARAMETERS";
					}
				}
				else
				{
					lcdpage=3;
					if(cDefaultLoadfg == 0)
					{
						if(weldmode=='P')
						{
							iLoadBlockCnt = PMIGMINPROGRAMLOAD;
						}
						else
						{
							iLoadBlockCnt = MIGMINPROGRAMLOAD;
						}
					}
					
				}
			}
				
			if(lcdpage==2)//@1
			{	
					lcdput(2,0,ar35);  //ar35[]="PREFLOWXXX:XXXXXXSEC";
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.preflow*10);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.preflow*10);
					preflowupdate();
					
					lcdput(3,0,ar36);  //ar36[]="BURNBACKXX:XXXXXXSEC";
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.burnback);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.burnback);
					burnbackupdate();
								
					lcdput(4,0,ar37);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.postflow*10);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.postflow*10);
					postflowupdate();
					
					lcdput(5,0,ar55);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.creepspeedrate);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pcreepspeedrate);
					Gcreepspeedupdate();
					
					lcdput(6,0,ar38);
					if(weldmode=='G')
					lcd_disp_hex_dec(G_crater_current);
					if(weldmode=='P')
					lcd_disp_hex_dec(P_crater_current);
					cratercurrentupdate();
					
					lcdput(7,0,ar39);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.cratervoltage);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.cratervoltage);
					cratervoltageupdate();
					
					selectpage(2);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(3);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(4);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(6);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(7);
					selectcolumn1(0);	  
					data(&character[0][0],8);
			}
			else if((lcdpage==3))
			{	
				if(weldmode=='P')
				{
					lcdput(2,0,ar51);
					lcd_disp_hex_dec(para.pulseweldmode);
					pulseweldmodeupdate();
										
					lcdput(3,0,ar52);
					lcd_disp_hex_dec(para.twinpulsefreq);
					twinpulsefrequpdate();
					
					lcdput(4,0,ar53);
					lcd_disp_hex_dec(para.twinpulseduty);
					twinpulsedutyupdate();
								
					lcdput(5,0,ar54);
					lcd_disp_hex_dec(para.twinpulseratio);
					twinpulseratioupdate();
					
					lcdput(6,0,ar57);
					NumberUpdate(6,72,iFileNo);					
					
					lcdput(7,0,ar58);
					welddatalatchstatus();
				}
				else if(weldmode=='G')
				{
					lcdput(2,0,ar57);
					NumberUpdate(2,72,iFileNo);	
					
					lcdput(3,0,ar58);
					welddatalatchstatus();						
				}		
					
										

	//					lcdput(6,0,ar56);
	//					lcd_disp_hex_dec(para.currentlow);
	//					twinpulseratioupdate();	
					
					selectpage(2);
					selectcolumn1(0);	  
					data(&character[0][0],8);
			
					selectpage(3);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(4);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(5);
					selectcolumn1(0);	  
					data(&character[0][0],8);
						
					selectpage(7);
					selectcolumn1(0);	  
					data(&character[0][0],8);
			 }	 	
	}
	else if((keypressed=='E') && (setlcdweldparameter==0) && (weldmode=='M'))				//@ down keypressed
	{
		iHots_Arcf_cnt++;
		if(iHots_Arcf_cnt >= 1)
			iHots_Arcf_cnt = 1;
			
		if(iHots_Arcf_cnt == 0)
		{
			lcdput(4,0,ar13);
			lcd_disp_hex_dec(para.mmamode.arcforce);
			arcforceupdate();						
		}
		else if (iHots_Arcf_cnt == 1)
		{
			lcdput(4,0,ar131);
			lcd_disp_hex_dec(iHotstartper);
			arcforceupdate();					
		}			
	}		
	else if((keypressed=='E') && (setlcdweldparameter!=0) && ((weldmode=='G') || (weldmode=='P')))				//@ down keypressed
	{
		if(lcdpage==1) 		
		{
		
		lcd_saverecall_ptr++;
		
		if(lcd_saverecall_ptr>5)
		lcd_saverecall_ptr=5;
		
		lcdput(2,0,ar81);   				 //@Edit
		
		lcdput(3,0,ar86);    				//@mode
		pmig_auto_man_update();
		
		lcdput(4,0,ar87);   				//@Arc Time
		arcon_time_update();
		
		lcdput(5,0,ar82);  					//@save						    
		lcd_disp_hex_dec(save_location);
		save_update();   					//@print save location number
		
		lcdput(6,0,ar83);  					//@Recall  
		lcd_disp_hex_dec(Recall_location);                         
		recall_update();
	
		}
		else //do not put this condition here else lcdpage wont change := if(lcdpage==1) 		
		{
		lcdmigpointer++;
		if(lcdmigpointer>=max_lcd_cnt)//10) //5
		lcdmigpointer=max_lcd_cnt;//10;     //5;
		
		if(lcdmigpointer<7)
		{
			lcdpage=2;
		}
		else
		{
			lcdpage=3;
			if(lcdmigpointer==7)
			{
				clrlcd();
				if(weldmode=='G')
				lcdput_bold(0,0,ar34);
				else if(weldmode=='P')
				lcdput_bold(0,0,ar44);
			}	
		}	
		
			if(lcdpage==2)
				{	
					lcdput(2,0,ar35);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.preflow*10);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.preflow*10);
					preflowupdate();
					
					lcdput(3,0,ar36);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.burnback);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.burnback);
					burnbackupdate();
								
					lcdput(4,0,ar37);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.postflow*10);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.postflow*10);
					postflowupdate();
					
					lcdput(5,0,ar55);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.creepspeedrate);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pcreepspeedrate);
					Gcreepspeedupdate();
					
					lcdput(6,0,ar38);
					if(weldmode=='G')
					lcd_disp_hex_dec(G_crater_current);
					if(weldmode=='P')
					lcd_disp_hex_dec(P_crater_current);
					cratercurrentupdate();
							 
					
					lcdput(7,0,ar39);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.cratervoltage);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.cratervoltage);
					cratervoltageupdate();
					
					selectpage(2);
					selectcolumn1(0);	  
					data(&character[0][0],8);
			
					selectpage(3);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(4);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(6);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(7);
					selectcolumn1(0);	  
					data(&character[0][0],8);
				}
				else if((lcdpage==3))
				{
					if(weldmode=='P')
					{
						lcdput(2,0,ar51);
						lcd_disp_hex_dec(para.pulseweldmode);
						pulseweldmodeupdate();
											
						lcdput(3,0,ar52);
						lcd_disp_hex_dec(para.twinpulsefreq);
						twinpulsefrequpdate();
						
						lcdput(4,0,ar53);
						lcd_disp_hex_dec(para.twinpulseduty);
						twinpulsedutyupdate();
									
						lcdput(5,0,ar54);
						lcd_disp_hex_dec(para.twinpulseratio);
						twinpulseratioupdate();
						
						lcdput(6,0,ar57);
						NumberUpdate(6,72,iFileNo);	
						
						lcdput(7,0,ar58);
						welddatalatchstatus();
						
					}
					else if(weldmode=='G')
					{
						lcdput(2,0,ar57);
						NumberUpdate(2,72,iFileNo);	
										
						lcdput(3,0,ar58);										
						welddatalatchstatus();						
					}		
						
					

//					lcdput(6,0,ar56);
//					lcd_disp_hex_dec(para.currentlow);
//					twinpulseratioupdate();	
				 
					selectpage(2);
					selectcolumn1(0);	  
					data(&character[0][0],8);
			
					selectpage(3);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(4);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(5);
					selectcolumn1(0);	  
					data(&character[0][0],8);
					
					selectpage(7);
					selectcolumn1(0);	  
					data(&character[0][0],8);
				}
		}		
	}
	else if(keypressed=='L')				//PARAMETER ENCODER keypressed 
	{
		if(weldmode=='M' || weldmode=='T')
		{
			if(OCVON_command==0)    //ocv ON
			OCVON_command=1;
			else
			OCVON_command=0;
		}
		if(weldmode=='G' || weldmode=='P')
		{
			if(cEnterOTPfg == 1)
			{
				cEnterOTPfg = 0;
				

				

					clrlcd();					
					lcdput_bold(3,5,ar411);					
					Update_File_Name(iFileNo);
					
					Read_whole_file(cFullFileName);//"READ2.TXT");//"READ5.TXT");////open_file("lomesh.csv");
					delay1(2000);
															
					Seperate_Out_Parameters1();
					cReadWholeFilefg = 0;	
				
				if(iabc <= 500)
				{
					lcdput(3,10,ar4167);						
					delay1(2000);						
				}
				else
				{	
					check_OTP();					
					if(cOTPMatchfg == 1)
					{
						cOTPMatchfg = 0;
						
						clrlcd();
						if((iUSBData[1][1] == 0) && (iUSBData[1][2] == 0) && (iUSBData[1][3] == 0))
						{					
							lcdput(3,10,ar4166);						
							delay1(2000);
						}
						else
						{
							lcdput(3,10,ar412);					
							lcdput(4,35,ar414);	
							delay1(2000);						
						}		
						
						write_USB_data_in_external_memory(iFileNo);
						
						cOTParray[0] = 0;
						cOTParray[1] = 0;
						cOTParray[2] = 0;
						cOTParray[3] = 0;															
					}
					else
					{
						clrlcd();					
						lcdput_bold(3,5,ar416);					
						delay1(3500);					
					}
				}
					cMainScreenfg = 1;
					iDefaultLoadCntr = 0;						
	
									
			}	
			else if(cPMainMenufg == 1)
			{
				setlcdweldparameter=0;
				lcd_saverecall_ptr=0;
				lcdpage=0;
				lcdmigpointer=0;
				
				if(cNoProgramfg == 0)
				{
					iPreviousProg = iProgramLoadLoc;		
				}
				read_from_external_memory(iPreviousProg);
				load_pulse_parameter();
				Load_Initial_Constant(para.pmigmode.setwspeed);
				keychange1=1;
				pmigsetwirespeed = 0;
				
				if(weldmode=='P')
				{
					cE2p[0] = iProgramLoadLoc;
					cE2p[1] = iProgramLoadLoc >> 8;
					I2C_Write1(PMIG_PROGRAM_ADDR,2);								
				}
				else if(weldmode=='G')
				{
					cE2p[0] = iProgramLoadLoc;
					cE2p[1] = iProgramLoadLoc >> 8;
					I2C_Write1(MIG_PROGRAM_ADDR,2);								
				}				
				
								
				cPMainMenufg = 0;
				cMainScreenfg = 1;
			}
			else if(cMacMenufg == 1)
			{		
				//EEPROM_Erase_Write((E2P_SERIALPORTTASK_ADDR),cSerialPortTask);
				//cCursorOfffg = 1;
								
				setlcdweldparameter=0;
				lcd_saverecall_ptr=0;
				lcdpage=0;
				lcdmigpointer=0;
								
				clrlcd();
				save_parameter_into_ROM();
										
				cMacMenufg = 0;
				cCursorOnfg = 0;
				cMainScreenfg = 1;
			}else if(setlcdweldparameter==0 && (weldmode=='G' || weldmode=='P') ) 
			//1st Press @Enter into 'Save Recall Exit' menu
			{
				    iTwinSetVolt = 0; 
					setlcdweldparameter=1;
					lcd_saverecall_ptr=1;
					lcdpage=1;
					lcdmigpointer=0;  //@ dummy write to avoid any true conditions of 	lcdmigpointer==1
					arc_on_reset_count=0;
					clrlcd();
									
					if(weldmode=='G')
					lcdput_bold(0,0,ar34);
					else if(weldmode=='P')
					lcdput_bold(0,0,ar44);
					
					
					lcdput(2,0,ar81);   				 //@Edit
					
					lcdput(3,0,ar86);    				//@mode
					pmig_auto_man_update();
					
					lcdput(4,0,ar87);   				//@Arc Time
					arcon_time_update();
					
					lcdput(5,0,ar82);  					//@save						    
					lcd_disp_hex_dec(save_location);
					save_update();   					//@print save location number
					
					lcdput(6,0,ar83);  					//@Recall  
					lcd_disp_hex_dec(Recall_location);                         
					recall_update();			
			}
			else if(setlcdweldparameter==1 && lcd_saverecall_ptr==1)  
			//2nd Press Enter into preflow page if 'Edit' is selected , @preflow page of settings
			{
					
				setlcdweldparameter=2;
							
				if(lcdpage==1)
				lcdpage=2;
				
				lcdmigpointer=1;
				clrlcd();
	
				if(weldmode=='G')
				lcdput_bold(0,0,ar34);
				else if(weldmode=='P')
				lcdput_bold(0,0,ar44);
				
				if(lcdpage==2)
				{	
					lcdput(2,0,ar35);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.preflow*10);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.preflow*10);
					preflowupdate();
					
					lcdput(3,0,ar36);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.burnback);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.burnback);
					burnbackupdate();
								
					lcdput(4,0,ar37);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.postflow*10);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.postflow*10);
					postflowupdate();
					
					lcdput(5,0,ar55);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.creepspeedrate);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pcreepspeedrate);
					Gcreepspeedupdate();
					
					lcdput(6,0,ar38);
					if(weldmode=='G')
					lcd_disp_hex_dec(G_crater_current);
					if(weldmode=='P')
					lcd_disp_hex_dec(P_crater_current);
					cratercurrentupdate();
											
				 
					
					lcdput(7,0,ar39);
					if(weldmode=='G')
					lcd_disp_hex_dec(para.migmode.cratervoltage);
					if(weldmode=='P')
					lcd_disp_hex_dec(para.pmigmode.cratervoltage);
					cratervoltageupdate();
				}
				
				else if((lcdpage==3)&&(weldmode=='P'))    //Third Page
				{	
						if(weldmode=='P')
						{
							lcdput(2,0,ar51);
							lcd_disp_hex_dec(para.pulseweldmode);
							pulseweldmodeupdate();
												
							lcdput(3,0,ar52);
							lcd_disp_hex_dec(para.twinpulsefreq);
							twinpulsefrequpdate();
							
							lcdput(4,0,ar53);
							lcd_disp_hex_dec(para.twinpulseduty);
							twinpulsedutyupdate();
										
							lcdput(5,0,ar54);
							lcd_disp_hex_dec(para.twinpulseratio);
							twinpulseratioupdate();
							
							lcdput(6,0,ar57);
							NumberUpdate(6,72,iFileNo);
							
							lcdput(7,0,ar58);					
							welddatalatchstatus();
						}
						else if(weldmode=='G')
						{
							lcdput(2,0,ar57);
							NumberUpdate(2,72,iFileNo);							
						
							lcdput(3,0,ar58);
							welddatalatchstatus();
						}										

//					lcdput(6,0,ar56);
//					lcd_disp_hex_dec(para.currentlow);
//					twinpulseratioupdate();					
					 
				}
				clearlcdf=1;
				updatelcdf=1;
			}
			else if(setlcdweldparameter==1 && lcd_saverecall_ptr==3)  
			//2nd Press Enter into preflow page if 'ARC on' is selected ,  
			{
				arc_on_reset_count++;
				if(arc_on_reset_count>=ARC_ON_RESET_COUNT_LIMIT)
				{
				arc_on_reset_count=ARC_ON_RESET_COUNT_LIMIT;
				arcontime.min=0;
				arcontime.sec=0;
				arcontime.hr=0;
				}
				Prevkey=0;
			}	
			else if(setlcdweldparameter==1 && lcd_saverecall_ptr==4)  
				//SAVE current Data
				{
					clrlcd();
					lcdput(3,0,ar84);  //"SAVING DATA";
					write_mode_mem(save_location); //save_location==> FROM MAIN.C==> updatemigparameter
	    			for(j=0;j<2000;j++)
	    			delay_pmig();					
//					write_mode_mem(save_location);
//					write_mode_mem(save_location);									   
				    		    
				   		    
				if((cDefaultLoadfg == 1) && (weldmode=='P'))
				{
				   iMSActVoltOffset = save_location;
					cE2p[0] = iMSActVoltOffset;
					I2C_Write1(MSVOLTAGEOFFSETADDR,1);				   
				   
				}  	
					    
				//++++++++EXIT+PROCESS+++++++++++++++++//
				setlcdweldparameter=0;
				lcd_saverecall_ptr=0;
				lcdpage=0;
				lcdmigpointer=0;
				cMainScreenfg = 1;
/*				
				if(weldmode=='G')
				{
				clrlcd();
				lcdput_bold(0,0,ar31);
				lcdput(2,0,ar32);
				lcdput(4,0,ar33);
				LCD_mig_syn_data_write();
				//lcdput(7,0,ar40);
				lcd_disp_hex_dec(dispautocurrent);
				currupdate();
				lcd_disp_hex_dec(program_number);
				programupdate();
				lcd_disp_hex_dec(para.migmode.setvoltage);
				voltupdate();
				}
				if(weldmode=='P')
				{
					clrlcd();
					lcdput_bold(0,0,ar41);
					lcdput(2,0,ar42);
					lcdput(4,0,ar43);
					LCD_pulsemig_syn_data_write();
					//lcdput(7,0,ar50);
					lcd_disp_hex_dec(dispautocurrent);
					currupdate();
					lcd_disp_hex_dec(program_number);
					programupdate();
					lcd_disp_hex_dec(para.pmigmode.setvoltage);
					voltupdate();
				 
				}
				
	*/			
				
				//++++++++EXIT+PROCESS+++++++++++++++++//
				
				}
				else if(setlcdweldparameter==1 && lcd_saverecall_ptr==5)  
				//RECALL DATA FROM LOCAION
				{
					clrlcd();
					lcdput(3,0,ar85);
					recall_mode_mem(Recall_location); //"RECALLING DATA";
					
					read_from_external_memory(iProgramLoadLoc);
					
//					recall_mode_mem(Recall_location); //"RECALLING DATA";
//					recall_mode_mem(Recall_location); //"RECALLING DATA";
										
							
				    setlcdweldparameter=2;
				    
				//++++++++EXIT+PROCESS+++++++++++++++++//
				setlcdweldparameter=0;
				lcd_saverecall_ptr=0;
				lcdpage=0;
				lcdmigpointer=0;
				cMainScreenfg = 1;
				}
				else if((setlcdweldparameter == 2) && (((weldmode == 'P') && (lcdmigpointer==11)) || ((weldmode == 'G') && (lcdmigpointer==7))))
				{
					setlcdweldparameter=0;
					lcd_saverecall_ptr=0;
					lcdpage=0;
					lcdmigpointer=0;
					//cMainScreenfg = 1;
					
					cEnterOTPfg = 1;
					iOTPCursor = 1;
					clrlcd();
					lcdput_bold(3,10,ar415);
					cOTParray[0] = 0;
					cOTParray[1] = 0;
					cOTParray[2] = 0;
					cOTParray[3] = 0;											
					/*
					clrlcd();					
					lcdput_bold(3,20,ar411);					
					Update_File_Name(iFileNo);
					
					Read_whole_file(cFullFileName);//"READ2.TXT");////open_file("lomesh.csv");
					delay1(3500);
					
					clrlcd();
										
					lcdput(3,10,ar412);					
					lcdput(4,35,ar414);	
					delay1(3500);
															
					Seperate_Out_Parameters1();
					cReadWholeFilefg = 0;	
					
					write_USB_data_in_external_memory(iFileNo);
					
					cMainScreenfg = 1;*/															
					
				}
				else if((setlcdweldparameter == 2) && (((weldmode == 'P') && (lcdmigpointer==12)) || ((weldmode == 'G') && (lcdmigpointer==8))))
				{
						//Weld latch function		
						if(cWeldLatchData == 0)
						{
							
							clrlcd();
							lcdput(2,0,ar15b);							
							
							
							read_parameter_from_ROM();
						
							iCreatFilecntr++;
							
							save_parameter_into_ROM();
														
							file_name_creation();
							cWeldDataLogfg = 1;
							cHrMinSec[2] = ':';
							cHrMinSec[5] = ':';	

							iHrStart = 0;
							iMinStart = 0;
							
							open_file(cfilename1);//"1245.CSV");  //"12345678.CSV");//
							delay1(1000);
							Insert_Header_of_File();
							delay1(100);							
							cWeldLatchData = 1;	
							iWeldJointCntr = 0;		
							
							iFileReopenCntr = FILE_SAVE_OPEN_DLY;			
						}
						else
						{
							clrlcd();
							lcdput(2,0,ar15c);					
							delay1(1000);
							
							cWeldDataLogfg = 0;
							cWeldLatchData = 0;
							closefilewithAOT();												
						}	
						//++++++++EXIT+PROCESS+++++++++++++++++//
						setlcdweldparameter=0;
						lcd_saverecall_ptr=0;
						lcdpage=0;
						lcdmigpointer=0;
						cMainScreenfg = 1;
				}		
			else if(setlcdweldparameter==2 && ((weldmode=='P') || (weldmode=='G')))		//#3rd Press @exit weld parameter
			{
				
				setlcdweldparameter=0;
				lcd_saverecall_ptr=0;
				lcdmigpointer=0;
				lcdpage=0;			
				cCursorOfffg = 1;
				
				cMainScreenfg = 1;
				/*
				clrlcd();
				lcdput_bold(0,0,ar41);
				lcdput(2,0,ar42);
				lcdput(4,0,ar43);
				LCD_pulsemig_syn_data_write();
				//lcdput(7,0,ar50);
				lcd_disp_hex_dec(dispautocurrent);
				currupdate();
				lcd_disp_hex_dec(program_number);
				programupdate();
				lcd_disp_hex_dec(parcbasevtg);
				voltupdate();
				if(psstatus.twinpulseon==1)
				{	
					twinpulseperiod=10000.0/para.twinpulsefreq;   //ms range =10 to 100				
			    	twinpulseonperiod=twinpulseperiod*para.twinpulseduty/100.0;
					twinpulseoffperiod=twinpulseperiod-twinpulseonperiod;	
				}
				*/
			}				 		
			clearlcdf=0;
			keychange1=1;
		}
	}
	else if(keypressed=='K')                //S9 voltage/arclength
	{
		//disparclen=~disparclen;
		if(disparclen==0)
		{
			//lcdput(7,90,gasco2);
			disparclen=1;
			dispupdatef=1;
			iALtoVoltShiftCNT = ARCLENGTH_DWN_CNT;
		}	
		else if(disparclen==1)
		{	
			///lcdput(7,90,gasarco2);
			disparclen=0;
			dispupdatef=1;
		}
		keychange2=1;
	}
	
	else if(keypressed=='H')                //S7 ws/current
	{
		//dispwirespeed=~dispwirespeed;
		if(weldmode=='G')
		{
			if(displedptr1==dispws)
			   displedptr1=dispamp;
			else if(displedptr1==dispamp)
			   displedptr1=dispws;
			//else if(displedptr1==dispthickness)
			//   displedptr1=dispws;
		}
		else if(weldmode=='P')
		{
			if(displedptr1==dispws)
			   displedptr1=dispamp;
			else if(displedptr1==dispamp)
			   displedptr1=dispthickness;
			else if(displedptr1==dispthickness)
			   displedptr1=dispws;
		}
	//	else if(displedptr1==dispjob)
	//	displedptr1=dispws;
	
	//below line was commented @ asn 25aug to avoid change in display vtg when s7 is pressed 
	keychange1=1;	
	}
	else if((keypressed=='G') && (cPMainMenufg == 0) && (cEnterOTPfg == 0))                //S6 program key
	{
		if(weldmode=='M')
		{
			weldmode='T';
			TypeU.LEDGROUP[0]=0x00;
			Type.current		=1;
			Type.voltage		=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.tig				=1;
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
		}
		else if(weldmode=='T')
		{
			weldmode='G';
			TypeU.LEDGROUP[0]=0x00;
			Type.wirespeed		=1;
			Type.voltage		=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.mig			=1;
			Type.twot			=1;
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
			cMainScreenfg = 1;
			iFileNo = 250;
		}
		else if(weldmode=='G')
		{
			weldmode='P';
			TypeU.LEDGROUP[0]=0x00;
			Type.wirespeed		=1;
			Type.voltage		=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.pulsemig		=1;
			Type.twot			=1;
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
			cMainScreenfg = 1;
			iFileNo = 50;
		}
		else if(weldmode=='P')
		{
			weldmode='M';
			TypeU.LEDGROUP[0]=0x00;
			Type.current	=1;
			Type.arcforce	=1;
			TypeU.LEDGROUP[1]=0x00;
			Type.mma		=1;
			TypeU.LEDGROUP[2]=0x00;
			TypeU.LEDGROUP[3]=0x00;
		}
		modechangef=1;
		setlcdweldparameter=0;
		clearlcdf=0;
		TypeDP.DPGROUP[0]=0x00;
		
		
		
	}
	
	else if(keypressed=='F')
	{
		if(setupmode==0)
		{
	    	/*
			uppeakamp	=500.0;
			peakamp		=400.0;
			stepamp		=100.0;//100.0;
			baseamp		=20.0;//50.0;
			
			pulsetm		=20.0;	//20*50usec=1000usec;
			steptm		=40.0;	//10*50usec=500usec
			basetm		=50.0;	//50*50usec=2500usec
			
			startpulsetm=3.0;  	//2*50usec=100usec
			pulserisetm	=6.0;  	//6*50usec=300usec 
			pulsedecaytm=30.0;  //30*50sec=1500usec
			stepdecaytm	=3.0;   //3*50usec=150usec
			
			pdaccount	=310.0+(peakamp*7.22);
			sdaccount	=310.0+(stepamp*7.22);
			bdaccount	=310.0+(baseamp*7.22);
			uppdaccount =310.0+(uppeakamp*7.22);
			upstep		=(uppdaccount-bdaccount)/pulserisetm;
		   */
		    //upcnt=bdaccount;		
			setupmode=1;
			//weldcycleon=1;
			//pulsecycle	=pulseriseop;
			setpeakf=0;
			setstepf=0;
			setbasef=0;
			setfreqf=0;
			setptimef=0;
			setstimef=0;
			setparaBkpf=0;
			setparaBkif=0;
			setparaBkdf=0;
			setparaPkpf=0;
			setparaPkif=0;
			setparaPkdf=0;
			TypeDP.DPGROUP[0]=0x00;
		}
		else if(setupmode==1)
		{
			setupmode=0;
			//weldcycleon=0;
			//MAHESH=0;
			setpeakf=0;
			setstepf=0;
			setbasef=0;
			setfreqf=0;
			setptimef=0;
			setstimef=0;
			setparaBkpf=0;
			setparaBkif=0;
			setparaBkdf=0;
			setparaPkpf=0;
			setparaPkif=0;
			setparaPkdf=0;
		}
	}

	else if(keypressed=='I')
	{ 
		if(setupmode==1)
		{
			
			if(setpeakf==0  && setstepf==0 && setbasef==0 && setfreqf==0 && setptimef==0 && setstimef==0
			   && setparaBkpf==0 && setparaBkif==0 && setparaBkdf==0 && setparaPkpf==0 && setparaPkif==0 
			   && setparaPkdf==0)

			{
				setpeakf=1;
			}
			else if(setpeakf==1)
			{
				setpeakf=0;
				setstepf=1;
			}
			else if(setstepf==1)
			{
				setstepf=0;
				setbasef=1;
			}
			else if(setbasef==1)
			{
				setbasef=0;
				setfreqf=1;
			}
			else if(setfreqf==1)
			{
				setfreqf=0;
				setptimef=1;	
			}
			
			else if(setptimef==1)
			{
				setptimef=0;
				setstimef=1;
			}
			else if(setstimef==1)
			{
				setstimef=0;
				setparaBkpf=1;	
			}
			else if(setparaBkpf==1)
			{
				setparaBkpf=0;
				setparaBkif=1;	
			}	
			else if(setparaBkif==1)
			{
				setparaBkif=0;
				setparaBkdf=1;	
			}
			else if(setparaBkdf==1)
			{
				setparaBkdf=0;
				setparaPkpf=1;	
			}
			else if(setparaPkpf==1)
			{
				setparaPkpf=0;
				setparaPkif=1;	
			}
			else if(setparaPkif==1)
			{
				setparaPkif=0;
				setparaPkdf=1;	
			}
			
			else if(setparaPkdf==1)
			{
				setpeakf=0;
				setstepf=0;
				setbasef=0;
				setfreqf=0;
				setptimef=0;
				setstimef=0;
				setparaBkpf=0;
				setparaBkif=0;
				setparaBkdf=0;
				setparaPkpf=0;
				setparaPkif=0;
				setparaPkdf=0;
				setupmode=0;
			}
		}

	}
	else if(keypressed=='J')
	{
		if( (weldmode=='G') || (weldmode=='P') )
		{
			if(cPMainMenufg == 0)
			{
			 	if(Type.twot==0)
			 	{
			 	 
			 	Type.twot=1;
				Type.fourt=0;
			 	}
			 	else if(Type.twot==1)
			 	{
			 	Type.twot=0;
				Type.fourt=1;				
			 	}
			 	cEditfg = 1;										
			}			
		}
	}
	/*else if(keypressed=='G' && keypressed=='A')
	{
		
		OCVON_command=1;
	
	}*/
	
	 
}
/* END keypad */

void MainMenuScreen()
{
	clrlcd();	
	if(weldmode=='P')
	{
		lcdput_bold(0,0,ar341);
	}
	else if(weldmode=='G')
	{
		lcdput_bold(0,0,ar342);	
	}

	lcdput(2,0,ar811);
	//lcdput(3,0,ar391);
	NumberUpdate(2,80,iProgramLoadLoc);
	program_check_from_mem(iProgramLoadLoc);		
}

void MainScreenShow(void) 
{
	prevProgramLoadLoc = iProgramLoadLoc = iPreviousProg;
	if(weldmode=='G')
	{
		
		clrlcd();
		lcdput_bold(0,0,ar31);
		lcdput(2,0,ar32);
		lcdput(4,0,ar33);
	     
	    
		lcd_disp_hex_dec(dispautocurrent);
		currupdate();
		
		if( iProgramLoadLoc == 212 )
		{
		   cSoftwireMIGALUfg = 1;	
		}
		else
		{
		   cSoftwireMIGALUfg = 0;	
		}
		
		lcd_disp_hex_dec(iProgramLoadLoc);//program_number);
		programupdate();
		lcd_disp_hex_dec(para.migmode.setvoltage);
		voltupdate();		
	}	
	else if(weldmode=='P')
	{
		clrlcd();
		lcdput_bold(0,0,ar41);
		lcdput(2,0,ar42);
		lcdput(4,0,ar43);
		//LCD_pulsemig_syn_data_write();
		//lcdput(7,0,ar50);	
				
		program_number=iPProgramNo;	
		
		if( program_number==20 || program_number== 21 || program_number== 9 || program_number== 10  || program_number== 11 || program_number== 35 || program_number== 36  || program_number== 37  )
		{
		   cSoftwireDetfg = 1;	
		}
		else
		{
		   cSoftwireDetfg = 0;	
		}		
		
		lcd_disp_hex_dec(dispautocurrent);
		currupdate();
		lcd_disp_hex_dec(program_number);
		programupdate();
		lcd_disp_hex_dec(para.pmigmode.setvoltage);
		voltupdate();
		if(psstatus.twinpulseon==1)
		{	
			twinpulseperiod=10000.0/para.twinpulsefreq;   //ms range =10 to 100				
	    	twinpulseonperiod=twinpulseperiod*para.twinpulseduty/100.0;
			twinpulseoffperiod=twinpulseperiod-twinpulseonperiod;	
		}
		
	}
	else if(weldmode=='M')
	{
		
		clrlcd();
		lcdput_bold(0,0,ar11);
		lcdput(2,0,ar12);
		lcdput(4,0,ar13);		
		
		lcd_disp_hex_dec(program_number);
		programupdate();
		
		lcd_disp_hex_dec(para.mmamode.arcforce);
		arcforceupdate();	
		
		lcd_disp_hex_dec(para.mmamode.setcurrent);
		currupdate();			
				
		if(mmat==mms)
		{
			lcdput(7,0,mmatms);
			{
				if(mdia==twoptfive)
					lcdput(7,48,mdiatwoptfive);
				else if(mdia==threepttwo)
					lcdput(7,48,mdiathreepttwo);
				else if(mdia==fourptzero)
					lcdput(7,48,mdiafourptzero);
				else if(mdia==fiveptzero)
					lcdput(7,48,mdiafiveptzero);
			}
			{
				if(melectrode==sevenzero)
				lcdput(7,82,msevenzero);
				else if(melectrode==sixzero)
				lcdput(7,82,msixzero);
				else if(melectrode==celwel)
				lcdput(7,82,mcelwel);
			}
		}
		
		else if(mmat==mss)
		{
			lcdput(7,0,mmatss);
			{
				if(mdia==twoptfive)
					lcdput(7,48,mdiatwoptfive);
				else if(mdia==threepttwo)
					lcdput(7,48,mdiathreepttwo);
				else if(mdia==fourptzero)
					lcdput(7,48,mdiafourptzero);
				else if(mdia==fiveptzero)
					lcdput(7,48,mdiafiveptzero);
			}
			lcdput(7,82,mthreezero);
		}	
		
		else if(mmat==mci)
		{
			lcdput(7,0,mmatci);
			{
				if(mdia==twoptfive)
					lcdput(7,48,mdiatwoptfive);
				else if(mdia==threepttwo)
					lcdput(7,48,mdiathreepttwo);
				else if(mdia==fourptzero)
					lcdput(7,48,mdiafourptzero);
				else if(mdia==fiveptzero)
					lcdput(7,48,mdiafiveptzero);
			}
			lcdput(7,82,mnicl);
		}	
		lcdput_bold(6,0,ar15a);				
	}	
		
	if((weldmode=='G'))
	{
		lcdput(6,0,cDisplayMat);
		lcdput(6,88,cGasTxt[cDisplayGas]);
		lcdput(6,48,cDiaTxt[cDisplayDia]);	
		if(iProgramLoadLoc==203 || iProgramLoadLoc==207 || iProgramLoadLoc==210 )
		{
			lcdput(7,80,cGasPercent[2]);
		}
		else
		{
		    lcdput(7,80,cGasPercent[pgas]);	 	
		}
				
	}
	else if(weldmode=='P')
	{
		
		lcdput(6,0,cDisplayMat);		
		lcdput(6,48,cDiaTxt[cDisplayDia]);
		lcdput(6,88,cGasTxt[cDisplayGas]);		
		lcdput(7,80,cGasPercent[cDisplayGas]);	
		
		
	}
	setlcdweldparameter=0;
	lcd_saverecall_ptr=0;
	lcdpage=0;
	lcdmigpointer=0;
	cPMainMenufg = 0;		
}	
//-----------------------------------------------------------------------------------------------------------
void CursorBlink(unsigned char cPosition, unsigned char cLine_no)
{			
	if(cCursorBlinkfg == 1)
	{
		selectpage(cLine_no);
		selectcolumn1(cPosition);	  
		data(&character[127][0],8);
		cCursorBlinkfg = 0;
	}
	else
	{
		selectpage(cLine_no);
		selectcolumn1(cPosition);	  
		data(&character[0][0],8);
		cCursorBlinkfg = 1;
		if(cCursorOfffg == 1)
		{
			//cCursorOnfg = 0;
			cCursorOfffg = 0;
		}	
	}		
}

//-----------------------------------------------------------------------------------------------------------	
void UpdateMacMenuScreenDataField(unsigned char cEncodStatus)
{
	switch(cMacMenuNo)
	{
		case 1:		
			switch(cLineNo)
			{
				case 2:
						cSerialNo[iSNocursor - 1] = updatedata(cSerialNo[iSNocursor - 1],0,9,encod1);
						encod1='$';																
				break;
				default:		
				break;				
			}	
			break;
		default:		
		break;
	}
	
}	
void EnterSerialNumber(unsigned int cPosition, unsigned char cLine_no)
{
	char temp,i;	
	temp = 48 + cSerialNo[iSNocursor-1];
	
	if(prevSerialN0 != cSerialNo[iSNocursor - 1])
	{
		prevSerialN0 = cSerialNo[iSNocursor - 1];		

		temp = 48 + cSerialNo[0];
		selectpage(4);
		selectcolumn1(20);	  
		data(&character[temp][0],8);		

		temp = 48 + cSerialNo[1];
		selectpage(4);
		selectcolumn1(28);	  
		data(&character[temp][0],8);
		
		temp = 48 + cSerialNo[2];
		selectpage(4);
		selectcolumn1(36);	  
		data(&character[temp][0],8);
		
		temp = 48 + cSerialNo[3];
		selectpage(4);
		selectcolumn1(44);	  
		data(&character[temp][0],8);				
		
		//lcdput(3,60,cSerialNo);
		count200Msec = 0;			
	}
	else
	{		
		if(cBlinkletterfg == 1)
		{	
			selectpage(cLine_no-1);
			selectcolumn1(cPosition);	  
			data(&character[temp][0],8);
			cBlinkletterfg = 0;
		}	
		else
		{
			selectpage(cLine_no-1);
			selectcolumn1(cPosition);	  
			data(&character[32][0],8);
			cBlinkletterfg = 1;		
		}	
	}			
}	

void EnterOTP(unsigned char cPosition, unsigned char cLine_no)
{
	char temp,i;
	 temp = 48 + cOTParray[iOTPCursor-1];
	
	if(prevOTPdigit != cOTParray[iOTPCursor-1])
	{	
		selectpage(cLine_no-1);
		selectcolumn1(cPosition);	  
		data(&character[temp][0],8);
		
		iStarDisplaycnt = 0;
		cStarDisplayfg = 1;
		
		prevOTPdigit = cOTParray[iOTPCursor-1];
	}
	else if(cStarDisplayfg == 1)
	{
		if(iStarDisplaycnt >=1000)
		{
			for(i=0;i<4;i++)
			{
				cStarDisplayfg = 0;
				selectpage(cLine_no-1);
				selectcolumn1(20+(i*8));//cPosition);	  
				data(&character[42][0],8);			
			}	
		}	
	}		
	
	if(iCursorBlinkcnt >=600)
	{
		iCursorBlinkcnt = 0;
		if(cCursorBlinkfg == 1)
		{
			selectpage(cLine_no);
			selectcolumn1(cPosition);	  
			data(&character[94][0],8);
			cCursorBlinkfg = 0;
		}
		else
		{
			selectpage(cLine_no);
			selectcolumn1(cPosition);	  
			data(&character[0][0],8);
			cCursorBlinkfg = 1;
			if(cCursorOfffg == 1)
			{
				cCursorOnfg = 0;
				cCursorOfffg = 0;
			}	
		}
	}				
}

void check_OTP()
{
	unsigned int iotp,itmp,tmp1,tmp2;
	unsigned char cFirstdigit,cSeconddigit,cThirddigit;
	unsigned int itmpp = 5098;
	itmp = iFileNo;
	
	/*cFirstdigit = 0x30+(itmp % 10);// & 0x00ff);
	itmp = itmp/10;
	cSeconddigit = 0x30+(itmp % 10);
	itmp = itmp/10;
	cThirddigit = 0x30+(itmp % 10);*/
	
	lcd_disp_hex_dec(iUSBFileNo);//iFileNo);	
	
	itmp = disp_data_arr[1] * disp_data_arr[2];
	itmp = itmp + (0x30  * disp_data_arr[0] );
	itmp = (9999 - itmp);
	
	iotp = ((cOTParray[0]*1000) + (cOTParray[1]*100) + (cOTParray[2]*10) + cOTParray[3]);
	
	//itmp = itmpp;
	
	//if(iUSBFileNo == iFileNo)
	{
		if(iotp == itmp)
		{
			cOTPMatchfg = 1;
		}
		else 
		{
			cOTPMatchfg = 0;
		}
	}
	iUSBFileNo = 0;			
}	


void CursorOff(unsigned char cPosition, unsigned char cLine_no)
{
	
		selectpage(cLine_no);
		selectcolumn1(cPosition);	  
		data(&character[0][0],8);		
}			
//-----------------------------------------------------------------------------------------------------------	
/*void UpdateMacMenuScreenDataField(unsigned char cEncodStatus)
{
	switch(cMacMenuNo)
	{
		case 1:		
			switch(cLineNo)
			{
				case 2:
					if(cEncodStatus == '+')
					{
						cSerialPortTask = 'H';
						lcdput(2,DATAPOSITION,"HMI");													
					}
					else if(cEncodStatus == '-')
					{
						cSerialPortTask = 'U';					
						lcdput(2,DATAPOSITION,"USB");						
					}		
				break;
				default:		
				break;				
			}	
		break;
		
		case 2:
		break;
		
		default:		
		break;
	}
	
}*/	
//-----------------------------------------------------------------------------------------------------------
//inline void key_application(unsigned char keypressed)
//{	
//		if(setmemloc==1)
//		{
//			if(keypressed != 'G')
//			{
//				keypressed='V';	//for no action
//			}	
//		}
//		if(setrecall==1)
//		{
//			if(keypressed != 'C')
//			{
//				keypressed='V';	//for no action
//			}	
//		}
//		if(keypressed== 'N')		//cc/cv selection keypressed
//		{
//			keypressed=0;
//			offallkeyf=1;
//			INTCON2bits.DISI=0;
//			DISICNTbits.DISICNT=0x3FFF;
//			INTCON2bits.DISI=1;
//			if(Type.fcaw==0)	// mma mode
//			{
//				Type.mma=0;
//				Type.mig=1;
//				Type.tig=1;
//				Type.fcaw=1;
//				memdata=EEPROM_Read(23*2);
//				memdata=((memdata & 0xFF7F)| 0x0080);
//				EEPROM_Erase_Write((23*2),memdata);				//FCAW LED OFF LD24
//				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);    //TIG & MIG LED OFF
//				memdata=EEPROM_Read(22*2);
//				memdata=(memdata & 0xEFFF);
//				EEPROM_Erase_Write((22*2),memdata);				//MMA LED ON LD24 HIGH
//				;
//				WeldMode=0x01;	
//      			EEPROM_Erase_Write((36*2),WeldMode); 
//				;
//				readmematstrt();
//				TypeU.LEDGROUP[0]=0xFF; 
//				TypeU.LEDGROUP[1]=0xFF;
//				TypeU.LEDGROUP[2]=0xFF;		
//				TypeU.LEDGROUP[3]=0xFF;
//				TypeU.LEDGROUP[4]=0xFF;
//				Type.mma=0;
//				Type.mig=1;
//				Type.tig=1;
//				Type.fcaw=1;
//				VRDRELAYLAT=0;		//tig mode disable
//				CCCVCTRLLAT=1;
//				Type.amp=0;
//				/*	cccvmode=1;
//				if(prevcccv!=cccvmode)
//				{
//					EEPROM_Erase_Write((33*2),cccvmode);
//					prevcccv=cccvmode;
//  				}   */
//                		for(ijk=0;ijk<=1000;ijk++)	
//                		for(abc=0;abc<100;abc++);
//               		genref(para.pwmtime1);
//			}
//                 
//                 else if(Type.mma==0) //&& (mc_model !='A' || mc_model !='B'))	// Tig mode
//			{
//				Type.mma=1;
//				Type.mig=1;
//				Type.tig=0;
//				Type.fcaw=1;
//
//				memdata=EEPROM_Read(22*2);
//				memdata=((memdata & 0xEFFF) | 0x1000); 
//				EEPROM_Erase_Write((22*2),memdata);				//MMA LED OFF LD24 HIGH
//
//				memdata=EEPROM_Read(23*2);
//				memdata=((memdata & 0xFF7F)| 0x0080);  			//FCAW LED OFF LD24 HIGH
//				EEPROM_Erase_Write((23*2),memdata);
//
//				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);	//TIG LED ON & MIG LED OFF
//				WeldMode=0x02;	
//      			EEPROM_Erase_Write((36*2),WeldMode);    
//				readmematstrt();
//				TypeU.LEDGROUP[0]=0xFF; 
//				TypeU.LEDGROUP[1]=0xFF;
//				TypeU.LEDGROUP[2]=0xFF;		
//				TypeU.LEDGROUP[3]=0xFF;
//				TypeU.LEDGROUP[4]=0xFF;
//				Type.mma=1;
//				Type.mig=1;
//				Type.tig=0;
//				Type.fcaw=1;
//				Type.amp=0;
//				CCCVCTRLLAT=1;
//				cccvmode=1;
//				VRDRELAYLAT=1;		//tig mode enable
//				/*if(prevcccv!=cccvmode)
//				{
//					EEPROM_Erase_Write((33*2),cccvmode);
//					prevcccv=cccvmode;
//  				} */ 
//			
//				for(ijk=0;ijk<=1000;ijk++)	
//                		for(abc=0;abc<100;abc++);
//				genref(para.pwmtime1);
//			}
//			else if(Type.tig==0)		//mig mode
//			{
//				tempdata=para.migws;
//				para.weld.wfs=tempdata;
//				Type.mma=1;
//				Type.mig=0;
//				Type.tig=1;
//				Type.fcaw=1;
//				/*memdata=EEPROM_Read(23*2);
//				memdata=((memdata & 0xFF7F)| 0x0080);
//				EEPROM_Erase_Write((23*2),memdata);
//				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);*/
//				memdata=EEPROM_Read(22*2);
//				memdata=((memdata & 0xEFFF) | 0x1000); 
//				EEPROM_Erase_Write((22*2),memdata);				//MMA LED OFF LD24 HIGH
//
//				memdata=EEPROM_Read(23*2);
//				memdata=((memdata & 0xFF7F)| 0x0080);  			//FCAW LED OFF LD24 HIGH
//				EEPROM_Erase_Write((23*2),memdata);
//
//				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);	//TIG LED OFF & MIG LED ON
//				
//
//				WeldMode=0x03;	
//      			EEPROM_Erase_Write((36*2),WeldMode);  
//				readmematstrt();
//				CCCVCTRLLAT=0;
//				cccvmode=0;
//				VRDRELAYLAT=1;		//tig mode disable
//				/*if(prevcccv!=cccvmode)
//				{
//					EEPROM_Erase_Write((33*2),cccvmode);
//					prevcccv=cccvmode;
//  				} */   
//			
//				for(ijk=0;ijk<=1000;ijk++)	
//                		for(abc=0;abc<100;abc++);
//			}
//			else if(Type.mig==0)		//fcaw mode
//			{
//				tempdata=para.migws;
//				para.weld.wfs=tempdata;
//				Type.mma=1;
//				Type.mig=1;
//				Type.tig=1;
//				Type.fcaw=0;
//				
//				memdata=EEPROM_Read(22*2);
//				memdata=((memdata & 0xEFFF) | 0x1000);
//				EEPROM_Erase_Write((22*2),memdata);				//MMA LED OFF LD24 HIGH
//
//				memdata=EEPROM_Read(23*2);
//				memdata=(memdata & 0xFF7F);  						//FCAW LED ON LD24 HIGH
//				EEPROM_Erase_Write((23*2),memdata);
//
//				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);	//TIG LED OFF & MIG LED OFF
//
//				/*memdata=EEPROM_Read(23*2);
//				memdata=((memdata & 0xFF7F)| 0x0080);
//				EEPROM_Erase_Write((23*2),memdata);
//				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);*/
//				WeldMode=0x04;	
//      			EEPROM_Erase_Write((36*2),WeldMode); 
//				readmematstrt();
//				Type.mma=1;
//				Type.mig=1;
//				Type.tig=1;
//				Type.fcaw=0;
//				CCCVCTRLLAT=0;
//				cccvmode=0;
//				VRDRELAYLAT=1;		//tig mode disable
//				/*if(prevcccv!=cccvmode)
//				{
//					EEPROM_Erase_Write((33*2),cccvmode);
//					prevcccv=cccvmode;
//  				}*/
//				 
//				for(ijk=0;ijk<=1000;ijk++)	
//                		for(abc=0;abc<100;abc++);
//			}
//
//		/*	if(Type.tig==0)	// cc mode
//			{
//				Type.mma=0;
//				Type.mig=1;
//				Type.tig=1;
//				memdata=EEPROM_Read(23*2);
//				memdata=((memdata & 0xFF7F)| 0x0080);
//				EEPROM_Erase_Write((23*2),memdata);
//				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);
//				readmematstrt();
//				TypeU.LEDGROUP[0]=0xFF; 
//				TypeU.LEDGROUP[1]=0xFF;
//				TypeU.LEDGROUP[2]=0xFF;		
//				TypeU.LEDGROUP[3]=0xFF;
//				TypeU.LEDGROUP[4]=0xFF;
//				Type.mma=0;
//				Type.mig=1;
//				Type.tig=1;
//				VRDRELAYLAT=0;		//tig mode disable
//				CCCVCTRLLAT=1;
//				cccvmode=1;
//				if(prevcccv!=cccvmode)
//				{
//					EEPROM_Erase_Write((33*2),cccvmode);
//					prevcccv=cccvmode;
//  				}   
//                		for(ijk=0;ijk<=1000;ijk++)	
//                		for(abc=0;abc<100;abc++);
//               		genref(para.pwmtime1);
//			}
//			//else if(Type.mma==0 && Type.mig==1 && Type.tig==1)		//cv mode
//
//
//			else if(Type.mma==0)		//cv mode
//			{
//				tempdata=para.migws;
//				para.weld.wfs=tempdata;
//				Type.mma=1;
//				Type.mig=0;
//				Type.tig=1;
//				memdata=EEPROM_Read(23*2);
//				memdata=((memdata & 0xFF7F)| 0x0080);
//				EEPROM_Erase_Write((23*2),memdata);
//				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);
//				readmematstrt();
//				CCCVCTRLLAT=0;
//				cccvmode=0;
//				VRDRELAYLAT=1;		//tig mode disable
//				if(prevcccv!=cccvmode)
//				{
//					EEPROM_Erase_Write((33*2),cccvmode);
//					prevcccv=cccvmode;
//  				}     
//				for(ijk=0;ijk<=1000;ijk++)	
//                		for(abc=0;abc<100;abc++);
//				
//			}
//		
//			else if(Type.mig==0 && (mc_model=='A' || mc_model=='B'))	// FCAW mode
//			{
//				Type.mma=1;
//				Type.mig=1;
//				Type.tig=0;
//				tempdata=para.fcawws;
//				para.weld.wfs=tempdata;
//				memdata=EEPROM_Read(23*2);
//				//memdata=((memdata & 0x0000)| 0x7E6E);
//				memdata=(memdata & 0xFF7F);//0000)| 0x7E6E);
//				EEPROM_Erase_Write((23*2),memdata);
//				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);
//				//readmematstrt();
//				;
//				TypeU.LEDGROUP[2]=0xFF;
//				Type.fe=0;
//				Type.zeropteight=0;
//				Type.tig=0;
//				TypeU.LEDGROUP[3]=0xFF;
//				Type.arco2=0;
//				Type.twot=0;
//				;
//				para.preflow.time=0;
//				para.postflow.time=0;
//				para.spottime=0;
//				para.pausetime=0;
//				TypeU.LEDGROUP[1]=0XFF;
//				Type.weld=0;
//				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//				Type.amp=0;
//				Type.voltage=0;
//				CCCVCTRLLAT=0;
//				cccvmode=0;
//				VRDRELAYLAT=1;		//tig mode disable
//				if(prevcccv!=cccvmode)
//				{
//					EEPROM_Erase_Write((33*2),cccvmode);
//					prevcccv=cccvmode;
//  				}     
//				for(ijk=0;ijk<=1000;ijk++)	
//                		for(abc=0;abc<100;abc++);
//			}
//		
//			else if(Type.mig==0 && (mc_model !='A' || mc_model !='B'))	// Tig mode
//			{
//				Type.mma=1;
//				Type.mig=1;
//				Type.tig=0;
//				memdata=EEPROM_Read(23*2);
//				memdata=((memdata & 0xFF7F)| 0x0000);
//				EEPROM_Erase_Write((23*2),memdata);
//				EEPROM_Erase_Write((24*2),TypeU.LEDGROUP[4]);
//				readmematstrt();
//				TypeU.LEDGROUP[0]=0xFF; 
//				TypeU.LEDGROUP[1]=0xFF;
//				TypeU.LEDGROUP[2]=0xFF;		
//				TypeU.LEDGROUP[3]=0xFF;
//				TypeU.LEDGROUP[4]=0xFF;
//				Type.mma=1;
//				Type.mig=1;
//				Type.tig=0;
//				CCCVCTRLLAT=1;
//				cccvmode=1;
//				VRDRELAYLAT=1;		//tig mode enable
//				if(prevcccv!=cccvmode)
//				{
//					EEPROM_Erase_Write((33*2),cccvmode);
//					prevcccv=cccvmode;
//  				}     
//				for(ijk=0;ijk<=1000;ijk++)	
//                		for(abc=0;abc<100;abc++);
//				genref(para.pwmtime1);
//			}*/
//			modechangef=1;
//		}
//
//
//
//
//		else if(keypressed == 'H') //menu keypressed
//		{
//			keypressed=0;
//			if(Type.mig==0 || Type.fcaw==0 )//working in mig mode
//			{
//				if(Type.multispot==1 && Type.spot==1 && Type.fourt==1)				//twot mode only 
//				{
//					if(Type.weld==0 && modeset==0)
//					{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.preflow=0;
//					modeset=1;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.time=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.preflow.time);
//					win1[0]='P';
//					win1[1]='R';
//					win1[2]='E';
//					win1dpcnt=3;
//				}
//				else if(Type.preflow==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.weld=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.amp=0;
//					Type.voltage=0;
//					win1dpcnt=float_to_ascii_str(&win1[0],fbvtg);
//					win2dpcnt=float_to_ascii_str(&win2[0],para.pwmtime);
//					win2[2]='0';	
//				}
//				else if(Type.weld==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.burnback=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.time=0;
//					//
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.burnbackf=1;
//					para.postflowf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
//					win1[0]='B';
//					win1[1]='R';
//					win1[2]='N';
//					win1dpcnt=3;
//					//win2[2]=0;
//				}
//				else if(Type.burnback==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.postflow=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.time=0;
//					//
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.burnbackf=0;
//					para.postflowf=1;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
//					win1[0]='P';
//					win1[1]='S';
//					win1[2]='T';
//					win1dpcnt=3;
//					//win2[2]=0;
//				}
//				else if(Type.postflow==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.preflow=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.time=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.preflow.time);
//					win1[0]='P';
//					win1[1]='R';
//					win1[2]='E';
//					win1dpcnt=3;
//				}
//			}
//			//*******
//			else if(Type.fourt==0)				//fourt mode only 
//			{
//				if(Type.weld==0 && modeset==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.preflow=0;
//					modeset=1;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.time=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.preflow.time);
//					win1[0]='P';
//					win1[1]='R';
//					win1[2]='E';
//					win1dpcnt=3;
//				}
//				else if(Type.preflow==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.weld=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.amp=0;
//					Type.voltage=0;
//					win1dpcnt=float_to_ascii_str(&win1[0],fbvtg);
//					win2dpcnt=float_to_ascii_str(&win2[0],para.pwmtime);
//					win2[2]='0';	
//				}
//				else if(Type.weld==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.crater=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.cratcurr=0;
//					Type.cratvolt=0;
//					win1dpcnt=float_to_ascii_str(&win1[0],para.crater.wfs);
//					win2dpcnt=float_to_ascii_str(&win2[0],para.crater.volts);
//				}
//				else if(Type.crater==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.burnback=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.time=0;
//					//
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.burnbackf=1;
//					para.postflowf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
//					win1[0]='B';
//					win1[1]='R';
//					win1[2]='N';
//					win1dpcnt=3;
//					//win2[2]=0;
//				}
//				else if(Type.burnback==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.postflow=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.time=0;
//					//
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.burnbackf=0;
//					para.postflowf=1;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
//					win1[0]='P';
//					win1[1]='S';
//					win1[2]='T';
//					win1dpcnt=3;
//					//win2[2]=0;
//				}
//				else if(Type.postflow==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.preflow=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.time=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.preflow.time);
//					win1[0]='P';
//					win1[1]='R';
//					win1[2]='E';
//					win1dpcnt=3;
//				}
//			}
//			//*******
//			else
//			{
//				if(Type.postflow==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.weld=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.amp=0;
//					Type.voltage=0;
//					win1dpcnt=float_to_ascii_str(&win1[0],fbvtg);
//					win2dpcnt=float_to_ascii_str(&win2[0],para.pwmtime);
//					win2[2]='0';	
//				}
//				
//				else if(Type.weld==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.burnback=0;
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.burnbackf=1;
//					para.postflowf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
//					win1[0]='B';
//					win1[1]='R';
//					win1[2]='N';
//					win1dpcnt=3;
//					//win2[2]=0;	
//				}
//				else if(Type.burnback==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					//Type.burnback=1;
//					Type.postflow=0;
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.burnbackf=0;
//					para.postflowf=1;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
//					win1[0]='P';
//					win1[1]='S';
//					win1[2]='T';
//					win1dpcnt=3;
//					//win2[2]=0;
//				}	
//			}
//		 }//
//		/*else if(Type.mig==1 && Type.tig==0)//working in mig mode
//		{
//			if(Type.twot==0)
//			{
//				if(Type.weld==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.burnback=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.time=0;
//					//
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.burnbackf=1;
//					para.postflowf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
//					win1[0]='B';
//					win1[1]='R';
//					win1[2]='N';
//					win1dpcnt=3;
//					//win2[2]=0;
//				}
//				else if(Type.burnback==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.weld=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.amp=0;
//					Type.voltage=0;
//					win1dpcnt=float_to_ascii_str(&win1[0],fbvtg);
//					win2dpcnt=float_to_ascii_str(&win2[0],para.pwmtime);
//					win2[2]='0';	
//				}
//			}
//			else if(Type.fourt==0)
//			{
//				if(Type.weld==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.crater=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.cratcurr=0;
//					Type.cratvolt=0;
//					win1dpcnt=float_to_ascii_str(&win1[0],para.crater.wfs);
//					win2dpcnt=float_to_ascii_str(&win2[0],para.crater.volts);
//				}
//				else if(Type.crater==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.burnback=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.time=0;
//					//
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.burnbackf=1;
//					para.postflowf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],fburnbacktime);
//					win1[0]='B';
//					win1[1]='R';
//					win1[2]='N';
//					win1dpcnt=3;
//					//win2[2]=0;
//				}
//				else if(Type.burnback==0)
//				{
//					TypeU.LEDGROUP[1]=0XFF;
//					Type.weld=0;
//					//;
//					TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//					Type.amp=0;
//					Type.voltage=0;
//					win1dpcnt=float_to_ascii_str(&win1[0],fbvtg);
//					win2dpcnt=float_to_ascii_str(&win2[0],para.pwmtime);
//					win2[2]='0';	
//				}
//			}
//		}*/
//		}//end of Menu keypressed
//		else if(keypressed == 'F')
//		{
//			keypressed=0;
//			if(WeldMode==0x03)
//			{
//				if(Type.fe==0)
//				{
//					Type.fe=1;
//					Type.nic=0;
//					Type.zeropteight=0;
//					Type.oneptzero=1;
//					Type.onepttwo=1;
//					Type.oneptsix=1;
//					
//					Type.arco2=0;
//					Type.co2=1;
//					Type.ar=1;
//					Type.aro2=1;
//				}
//				else if(Type.nic==0)
//				{
//					Type.nic=1;
//					Type.alu=0;
//					Type.zeropteight=1;
//					Type.oneptzero=1;
//					Type.onepttwo=0;
//					Type.oneptsix=1;
//					Type.arco2=1;
//					Type.co2=1;
//					Type.ar=0;
//					Type.aro2=1;
//				}	
//				else if(Type.alu==0)
//				{
//					Type.alu=1;
//					//Type.tig=1;
//					Type.fe=0;
//					Type.zeropteight=0;
//					Type.oneptzero=1;
//					Type.onepttwo=1;
//					Type.oneptsix=1;
//					Type.arco2=0;
//					Type.co2=1;
//					Type.ar=1;
//					Type.aro2=1;
//				}
//			}
//		}//end of material keypressed
//
//		else if(keypressed == 'J')
//		{
//			keypressed=0;
//			if(WeldMode==0x03)
//			{
//				if(Type.fe==0)
//				{
//					if(Type.zeropteight==0)
//					{
//						Type.zeropteight=1;
//						Type.oneptzero=0;
//					}
//					else if(Type.oneptzero==0)
//					{
//						Type.oneptzero=1;
//						Type.onepttwo=0;
//					}	
//					else if(Type.onepttwo==0)
//					{
//						Type.onepttwo=1;
//						Type.oneptsix=0;
//					}
//					else if(Type.oneptsix==0)
//					{
//						Type.oneptsix=1;
//						Type.zeropteight=0;
//					}
//					
//				}
//				else if(Type.nic==0)
//				{
//					if(Type.zeropteight==0)
//					{
//						Type.zeropteight=1;
//						Type.onepttwo=0;
//					}
//					else if(Type.onepttwo==0)
//					{
//						Type.onepttwo=1;
//						Type.zeropteight=0;
//					}	
//					
//				}
//				else if(Type.alu==0)
//				{
//						Type.zeropteight=1;
//						Type.oneptzero=1;
//						Type.onepttwo=0;
//						Type.oneptsix=1;
//				}
//			}
//			else if (WeldMode==0x04)
//			{
//				if(Type.fe==0)
//				{
//					if(Type.onepttwo==0)
//					{
//						Type.onepttwo=1;
//						Type.oneptsix=0;
//					}
//					else if(Type.oneptsix==0)
//					{
//						Type.oneptsix=1;
//						Type.onepttwo=0;
//					}
//				}
//			}
//
//		}//end of mm keypressed
//		else if(keypressed == 'B')
//		{
//			keypressed=0;
//			if(WeldMode==0x03)
//			{
//				if(Type.fe==0)
//				{
//					if(Type.arco2==0)
//					{
//						Type.arco2=1;
//						Type.co2=0;
//					}
//					else if(Type.co2==0)
//					{
//						Type.co2=1;
//						Type.arco2=0;
//					}	
//				}
//				else if(Type.nic==0)
//				{
//					if(Type.arco2==0)
//					{
//						Type.arco2=1;
//						Type.aro2=0;
//					}
//					else if(Type.aro2==0)
//					{
//						Type.aro2=1;
//						Type.arco2=0;
//					}	
//				}
//				else if(Type.alu==0)
//				{
//						Type.arco2=1;
//						Type.co2=1;
//						Type.ar=0;
//						Type.aro2=1;
//				}
//			}
//			else if(WeldMode==0x04)
//			{
//				if(Type.fe==0)
//				{
//					 if(Type.co2==0)
//					{
//						Type.arco2=1;
//						Type.co2=0;
//						Type.ar=1;
//						Type.aro2=1;
//					}	
//				}
//			}
//		}//end of gas keypressed
//		
//		else if(keypressed=='K')
//		{
//			keypressed=0;
//			modeset=0;
//			if(Type.multispot==0)
//			{
//				Type.multispot=1;
//				Type.spot=0;
//				Type.crateron=1;					//crater is enabled only in fourt mode
//			
//				TypeU.LEDGROUP[1]=0XFF;
//				Type.weld=0;
//				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//				Type.speed=0;
//				Type.voltage=0;
//				
//				para.spottimef=0;
//				para.pausetimef=0;
//				para.burnbackf=0;
//				para.postflowf=0;
//				
//				Type.automan=1;
//			}
//			else if(Type.spot==0)
//			{
//				Type.spot=1;
//				Type.fourt=0;
//				Type.crateron=1;					//crater is enabled only in fourt mode
//				
//				TypeU.LEDGROUP[1]=0XFF;
//				Type.weld=0;
//				
//				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//				Type.amp=0;
//				Type.voltage=0;
//			
//				para.spottimef=0;
//				para.pausetimef=0;
//				para.burnbackf=0;
//				para.postflowf=0;
//			}	
//			else if(Type.fourt==0)
//			{
//				Type.fourt=1;
//				Type.twot=0;
//				Type.crateron=1;					//crater is enabled only in fourt mode
//				TypeU.LEDGROUP[1]=0XFF;
//				Type.weld=0;
//				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//				Type.amp=0;
//				Type.voltage=0;
//				para.spottimef=0;
//				para.pausetimef=0;
//				para.burnbackf=0;
//				para.postflowf=0;
//			}
//			else if(Type.twot==0)
//			{
//				Type.twot=1;
//				//if(Type.tig==0)
//				//Type.fourt=0;
//		       	//else if(Type.mig==0 || Type.fcaw==0 )
//				Type.multispot=0;
//				Type.crateron=1;					//crater is enabled only in fourt mode
//				TypeU.LEDGROUP[0]=(TypeU.LEDGROUP[0] | 0XFB);
//				Type.speed=0;//1;
//				Type.voltage=0;//1;
//				TypeU.LEDGROUP[1]=0XFF;
//				Type.weld=0;//1;
//				para.spottimef=0;//1;
//				para.pausetimef=0;
//				para.burnbackf=0;
//				para.postflowf=0;
//				Type.automan=1;
//			}
//		}//end of scan mode keypressed 
//		
//		else if(keypressed=='L')
//		{
//			keypressed=0;
//			if(Type.automan==0)
//			{
//				Type.automan=1;		//manual mode enable
//				//PWMONLAT=1;
//			}	
//			else
//			{
//					autooffset=0;		//clear offset
//					preweldvtg=0;
//					//PWMONLAT=1;
//					if(Type.twot==0 || Type.fourt==0)
//					{
//						Type.automan=0;		//auto mode enable
//					}
//					//OC8RS=0x0000;
//					//debounce_delay();
//					//PWMONLAT=0;
//			}
//			//Type.automan=~(Type.automan);	
//		}
//		else if(keypressed=='D')//'D'
//		{
//			keypressed=0;
//			modeset=0;
//			
//			if(setupmode==1)
//			{
//				if(Type.mma==1 && Type.mig==0 && Type.tig==1)
//				{
//					if(setpt1==1 && setpt2==0 && slopept1==0 && slopept2==0)
//					{
//						setpt1=0;  //use for setting multiplier in current setting.
//						setpt2=1;
//						slopept1=0;
//						slopept2=0;
//					}
//					else if(setpt1==0 && setpt2==1 && slopept1==0 && slopept2==0)
//					{
//						setpt1=0;  //use for setting multiplier in current setting.
//						setpt2=0;
//						slopept1=1;
//						slopept2=0;
//						pwmtime1=400;
//					}
//					else if(setpt1==0 && setpt2==0 && slopept1==1 && slopept2==0)
//					{
//						setpt1=0;  //use for setting multiplier in current setting.
//						setpt2=0;
//						slopept1=0;
//						slopept2=1;
//						pwmtime1=500;
//					}
//				}
//				else if(Type.mma==0 && Type.mig==1 && Type.tig==1)
//				{
//					if(slopept1==1 && slopept2==0)
//					{
//						slopept1=0;
//						slopept2=1;
//						pwmtime1=400;
//					}
//				}
//			}
//		  	if(Type.mma == 0)
//			{
//				Type.arcforce=~Type.arcforce;
//			}
//			else if(Type.twot==0 || Type.fourt==0)
//			{
//				if(passprotect==0 && setpasswordf==0 && enblpasskey==0)
//				{
//					win1[0]='L';
//					win1[1]='C';
//					win1[2]='K';
//					win1dpcnt=3;
//					win2dpcnt=float_to_ascii_str(&win2[0],password);//-=1;
//					setpasswordf=1;
//				}
//				else if(passprotect==1 && enblpasskey==0)
//				{
//					win1[0]='P';
//					win1[1]='A';
//					win1[2]='S';
//					win1dpcnt=3;
//					passtemp=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],passtemp);
//					setpasswordf=1;
//				}
//				else if(setpasswordf==1 && enblpasskey==0)//setup for password saving
//				{
//					mesgsvd=1;
//					count_1ms=0;
//					count_10ms=0;
//					count_100ms=0;
//					count_1sec=0;
//				}
//				else if(enblpasskey==1)
//				{
//					chkpass=1;
//					count_1ms=0;
//					count_10ms=0;
//					count_100ms=0;
//					count_1sec=0;
//				}
//			}
//			else if(Type.multispot ==0 && Type.burnback==0)
//			{
//				if(para.spottimef==1)
//				{
//					para.spottimef=0;
//					para.pausetimef=1;
//					para.burnbackf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.pausetime);
//					win1[0]='P';
//					win1[1]='T';
//					win1[2]='M';
//					win1dpcnt=3;
//				}
//				else if(para.pausetimef==1)
//				{
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.burnbackf=1;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.burnback.time);
//					win1[0]='B';
//					win1[1]='R';
//					win1[2]='N';
//					win1dpcnt=3;
//				}
//				else if(para.burnbackf==1)
//				{
//					para.spottimef=1;
//					para.pausetimef=0;
//					para.burnbackf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.spottime);
//					win1[0]='S';
//					win1[1]='T';
//					win1[2]='M';
//					win1dpcnt=3;
//				}
//			}
//			else if(Type.multispot ==0 && Type.postflow==0)
//			{
//				if(para.spottimef==1)
//				{
//					para.spottimef=0;
//					para.pausetimef=1;
//					para.postflowf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.pausetime);
//					win1[0]='P';
//					win1[1]='T';
//					win1[2]='M';
//					win1dpcnt=3;	
//				}
//				else if(para.pausetimef==1)
//				{
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.postflowf=1;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
//					win1[0]='P';
//					win1[1]='S';
//					win1[2]='T';
//					win1dpcnt=3;
//				}
//				else if(para.postflowf==1)
//				{
//					para.spottimef=1;
//					para.pausetimef=0;
//					para.postflowf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.spottime);
//					win1[0]='S';
//					win1[1]='T';
//					win1[2]='M';
//					win1dpcnt=3;
//				}
//			}
//			else if(Type.spot ==0 && Type.burnback==0)
//			{
//				if(para.spottimef==1)
//				{
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.burnbackf=1;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.burnback.time);
//					win1[0]='B';
//					win1[1]='R';
//					win1[2]='N';
//					win1dpcnt=3;
//				}
//				else if(para.burnbackf==1)
//				{
//					para.spottimef=1;
//					para.pausetimef=0;
//					para.burnbackf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.spottime);
//					win1[0]='S';
//					win1[1]='T';
//					win1[2]='M';
//					win1dpcnt=3;
//				}
//			}
//			else if(Type.spot ==0 && Type.postflow==0)
//			{
//				if(para.spottimef==1)
//				{
//					para.spottimef=0;
//					para.pausetimef=0;
//					para.postflowf=1;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.postflow.time);
//					win1[0]='P';
//					win1[1]='S';
//					win1[2]='T';
//					win1dpcnt=3;
//				}
//				else if(para.postflowf==1)
//				{
//					para.spottimef=1;
//					para.pausetimef=0;
//					para.postflowf=0;
//					win2dpcnt=float_to_ascii_str(&win2[0],para.spottime);
//					win1[0]='S';
//					win1[1]='T';
//					win1[2]='M';
//					win1dpcnt=3;
//				}
//			}
//			//Type.extra=~(Type.extra);	
//		}	 	 
//		
//		else if(keypressed=='G')
//		{
//			keypressed=0;
//			/*if(setupmode==0 && setpasswordf==1)//setup for password saving
//			{
//				
//					mesgsvd=1;
//					count_1ms=0;
//					count_10ms=0;
//					count_100ms=0;
//					count_1sec=0;
//			}
//			else*/ 
//                if(setmemloc==0 && Type.automan==1)
//			{
//					win2dpcnt=float_to_ascii_str(&win2[0],memlocation);
//					win1[0]='L';
//					win1[1]='O';
//					win1[2]='C';
//					win1dpcnt=3;
//					setmemloc=1;
//					displprev=0;
//					Type.save=0;
//			}
//			else if(setmemloc==1)
//			{
//					win1dpcnt=float_to_ascii_str(&win1[0],fwirespeed);
//					win2dpcnt=float_to_ascii_str(&win2[0],fpwmtime);
//					//win2dpcnt=float_to_ascii_str(&win2[0],fbvtg);
//					if(win1dpcnt==1)
//					{
//						win1[2]='/';					//for display empty display
//					}
//					if(win2dpcnt==1)
//					{
//						win2[2]='/';
//					}
//					displprev=1;
//					count_1ms=0;
//					count_10ms=0;
//					count_100ms=0;
//					count_1sec=0;
//			}
//			
//		}
//		else if(keypressed=='C')
//		{
//			keypressed=0;
//			if(setrecall==0 && Type.automan==1)
//				{
//					win2dpcnt=float_to_ascii_str(&win2[0],memlocation);
//					win1[0]='L';
//					win1[1]='O';
//					win1[2]='C';
//					win1dpcnt=3;
//					setrecall=1;
//					displprev=0;
//					Type.recall=0;
//				}
//			else if(setrecall==1)
//			{
//					memlocation=updatedata(memlocation,1,10,encres);
//					win2dpcnt=float_to_ascii_str(&win2[0],memlocation);
//					if(win2dpcnt==1)
//					{
//						win2[2]='/';		//for disply empty display
//					}
//					win1[0]='R';
//					win1[1]='C';
//					win1[2]='L';
//					win1dpcnt=3;
//					count_1ms=0;
//					count_10ms=0;
//					count_100ms=0;
//					count_1sec=0;
//					disprcl=1;
//			}
//		
//		}
//		else if(keypressed=='M')
//		{
//					//trans('P');
//					if(Type.mig==0)
//					{
//					//	multi1=para.currmult;
//					//	multi2=para.currmult;
//						setpt1=1;
//						setpt2=0;
//					//	win2dpcnt=float_to_ascii_str(&win2[0],para.currmult);
//						win1[0]='C';
//						win1[1]='U';
//						win1[2]='R';
//						win1dpcnt=3;
//						setupmode=1;
//						ARCONLAT=1;				//torch high signal
//						///******CONTACTORLAT=1;
//				    }  
//				   else if(Type.mma==0)
//				   {
//						pwmtime1=190;
//						slopept1=1;
//						slopept2=0;
//						win1[0]='C';
//						win1[1]='U';
//						win1[2]='R';
//						win1dpcnt=3;
//						setupmode=1;
//				   }
//		}
//		else if(keypressed=='Q')
//		{
//			if(passprotect==0)
//			{
//				win1[0]='L';
//				win1[1]='C';
//				win1[2]='K';
//				win1dpcnt=3;
//				win2dpcnt=float_to_ascii_str(&win2[0],password);//-=1;
//				setpasswordf=1;
//			}
//			else
//			{
//				win1[0]='P';
//				win1[1]='A';
//				win1[2]='S';
//				win1dpcnt=3;
//				passtemp=0;
//				win2dpcnt=float_to_ascii_str(&win2[0],passtemp);
//				setpasswordf=1;
//			}
//		}
//	
//		else if(keypressed=='O')			// 'O' encoder 2 switch
//		{
//			if(Type.fourt==0)
//			{	
//				Type.crateron=~Type.crateron;			
//			}
//            	if(Type.mig==0 || Type.fcaw==0)
//			{
//				if(mesgdispf==0)
//				{
//					mesgdispf=1;
//					count_1ms=0;
//				  	count_10ms=0;
//				   	count_100ms=0;
//				   	count_1sec=0;
//				}
//			}
//		}		
//		else if(keypressed=='R')
//		{
//				
//			for (memcntr=0;memcntr<=512;memcntr++)		//496 512 clear all eeprom memory. last 16 location are used for factory setting from 7fffe0 t0 =7fffff
//				{
//						EE_Addr=(memcntr*2);						
//						EE_Data=0xFFFF;	
//						EEPROM_Erase_Write(EE_Addr,EE_Data);
//				}
//			//********************************************************
//					//para.password=0x0000;
//				/*	para.passprotect=0x0000;
//					//		EEPROM_Erase_Write((25*2),para.password);
//							EEPROM_Erase_Write((26*2),para.passprotect);
//							for(cntpass=1;cntpass<=10;cntpass++)
//							{
//								EE_Addr=(40*cntpass*2)+(25*2);
//				 //				EE_Data=para.password;
//								EEPROM_Erase_Write(EE_Addr,EE_Data);
//								EE_Addr=(40*cntpass*2)+(26*2);
//								EE_Data=para.passprotect;
//								EEPROM_Erase_Write(EE_Addr,EE_Data);
//							}//
//			//
//			//	para.currmult= EEPROM_Read(2*511);		//read last location
//				for(resnum1=1;resnum1<=11;resnum1++)	//write again in current multiplier location
//				{
//					EE_Addr=resnum2 + (32*2*resnum1);				//storing data at 0031 memory location
//			//		EE_Data=para.currmult;
//					EEPROM_Erase_Write(EE_Addr,EE_Data);
//					resnum2=resnum2 + 16;
//				}
//
//				resnum2=0;
//				//;
//				cvslope= EEPROM_Read(2*509);		//read last location
//				ccslope= EEPROM_Read(2*508);		//read last location
//				EEPROM_Erase_Write((34*2),cvslope);
//				EEPROM_Erase_Write((35*2),ccslope);
//				*/
//
//				win1[0]='R';
//				win1[1]='S';
//				win1[2]='T';
//				win1dpcnt=3;
//				win2[0]='R';
//				win2[1]='S';
//				win2[2]='T';
//				win2dpcnt=3;
//				readmematstrt();
//				for(i=0;i<2000;i++)//5000 200
//				delay();
//		}
//
//		else if(keypressed=='S')
//		{
//			/*arconsec=0;
//			arconmin=0;
//			arconhr=0;
//			EEPROM_Erase_Write((39*2),arconsec);
//			EEPROM_Erase_Write((38*2),arconmin);
//			EEPROM_Erase_Write((37*2),arconhr);
//			win1[0]='A';
//			win1[1]='R';
//			win1[2]='C';
//			win1dpcnt=3;
//			win2[0]='R';
//			win2[1]='S';
//			win2[2]='T';
//			win2dpcnt=3;
//			for(i=0;i<2000;i++)//5000 200
//			delay();*/
//		}
//}
//

