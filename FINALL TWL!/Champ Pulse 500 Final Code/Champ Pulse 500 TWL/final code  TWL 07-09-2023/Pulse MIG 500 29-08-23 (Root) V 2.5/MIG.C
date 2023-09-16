void MIGWELD(void)
{
			if(modechangef==1)
			{
				transmitonf=0;
				clrlcd();												


				iProgramLoadLoc = I2C_Read1(MIG_PROGRAM_ADDR+1);
				iProgramLoadLoc = iProgramLoadLoc << 8;
				iProgramLoadLoc |= I2C_Read1(MIG_PROGRAM_ADDR);				
				iPreviousProg = prevProgramLoadLoc = iProgramLoadLoc;
				
				read_from_external_memory(iProgramLoadLoc);//iProgramLoadLoc);	
                
                //lcdput_bold(0,0,ar31);
				if(pidParams2.migweldmode == 1)
				{
				    	
					
					lcdput_bold(0,0,"M-NORMAL MODE");
					
				}
				else
				{
					
				    
					lcdput_bold(0,0,"MIG ROOT MODE");	
				}
				lcdput(2,0,ar32);
				lcdput(4,0,ar33);
				//lcdput(7,0,ar40);
				
				
				
				diswin1[0]='M';
				diswin1[1]='I';
				diswin1[2]='G';
				diswin2[0]='M';
				diswin2[1]='O';
				diswin2[2]='D';
				for(j=0;j<200;j++)
				for(i=0;i<10000;i++);
				modechangef=0;
				displedptr1=dispamp;//dispws; //@sbm
				//mat=ms;
				//dia=onepttwo;
				//gas=co2;
				dispupdatef=1;
				disparclen=0;
				SHDNLAT=0;			//OCV OFF
				memoryzone='X';
				eedata=weldmode;//3456;							//0x0003;
				EEPROM_Erase_Write((0*2),eedata);


				iLoadBlockCnt = MIGMINPROGRAMLOAD;
				
				read_current_status();
				check_eeprom_values();
				
				prev_weldmode=weldmode;
				prev_eeprom_mig_struct=EEPROM_struct_mig.EEPROM_struct_u;
				read_gpreflow=para.migmode.preflow;   				//2
				read_gsetcurrent=para.migmode.setcurrent;			//3
			    read_gsetvoltage=para.migmode.setvoltage;			//4
			    read_gcratercurrent=para.migmode.craterspeed;		//5
			    read_gcratervoltage=para.migmode.cratervoltage;		//6
			    read_gburnback=para.migmode.burnback;				//7
			    read_gsetwspeed=para.migmode.setwspeed;				//8
			    read_gmaterial=para.migmode.gmaterial;				//9
			    read_gpostflow=para.migmode.postflow;				//10
			    read_inductance=para.migmode.inductance;			//11
			    prevcreepspeedrate=para.creepspeedrate;				//12
			    read_gthickness=para.migmode.thickness;				//13
				read_pmig_auto0_man1=pmig_auto0_man1;
				pstowfstr.arclength=para.migmode.inductance;
				read_mig_mode=pidParams2.migweldmode;
				
				
				
/*************************crater parameter start*************************/				
				pstowfstr.crater_speed=para.migmode.craterspeed; 
				pstowfstr.creep_speed=para.creepspeedrate;
				
				ftemp=para.pmigmode.craterspeed;
				fwirespeed=ftemp*0.101;
				
				wirespeed=fwirespeed;
				current1=iPSetCurrent[wirespeed];//findmatindex(wirespeed);
				current2=iPSetCurrent[wirespeed+1];//findmatindex((wirespeed+1));
				G_crater_current=current1+((fwirespeed-wirespeed)*(current2-current1));

				voltage1=iPSetBaseVoltage[wirespeed];//findmatindex1(wirespeed);
				voltage2=iPSetBaseVoltage[wirespeed+1];//findmatindex1((wirespeed+1));											
				dispautovoltage=voltage1+((fwirespeed-wirespeed)*(voltage2-voltage1));
				para.migmode.setvoltage=dispautovoltage;
				pmigsetwirespeed = 0;

				
				lcd_disp_hex_dec(para.migmode.setcurrent);
				currupdate();
				dispautocurrent=para.migmode.setcurrent;
				
				lcd_disp_hex_dec(para.migmode.setvoltage);
				voltupdate();
						
		
				if(para.migmode.inductance>=40) //20
				para.migmode.inductance=0;

				
				//pidParams2.Kp2=30-(para.migmode.inductance / 3);// changed on 23092019
            	//pidParams2.Ki2=1 +(para.migmode.inductance / 15);// changed on 23092019 
            	//pidParams2.Kd2=0;				
            
				
				pidParams1.Kp1=pidParams2.Kp2;
				pidParams1.Ki1=pidParams2.Ki2;
				pidParams1.Kd1=pidParams2.Kd2;//intkd;
				transmitonf=1;
			}
			//CCCVCTRLLAT	=CVMODE;					//CCCV CONTROL  INPUT TO PWM CARD.
			
		    para.migmode.setcurrent=dispautocurrent;  //@ to load the value of temp reg to structure variable , used in eeprom writing
						
			if( (encod3!='$' || encod2 !='$')  && setlcdweldparameter==0 && password_protection_enabled==0)
			{
				updategcvparameter(encod3,encod2);  	//@user input current and voltage	
				encod3='$';
				encod2='$';
			}
			else if((encod1!='$') && setlcdweldparameter!=0  && password_protection_enabled==0 )
			{
				updatemigparameter(encod1);	  			//@user input arc length
				encod1='$';
			}
			else if((encod1!='$') && (setlcdweldparameter==0) && (cPMainMenufg == 1))
			{
				if(pidParams2.migweldmode == 1)
				{
					//NORMAL MODE
					iProgramLoadLoc = updatedata(iProgramLoadLoc,201,300,encod1);
					encod1='$';
				}
				else
				{
				    //ROOT
					iProgramLoadLoc = updatedata(iProgramLoadLoc,301,400,encod1);
					encod1='$';	
				}
			}
			if(read_mig_mode != pidParams2.migweldmode)
			{
				 write_current_status();
			}	
			
		    
			if((prevProgramLoadLoc != iProgramLoadLoc ))
			{
				if((migUpdateProgfg==1 || migUpdateProgfg==2) && (iProgramLoadLoc==201 || iProgramLoadLoc==301) )
				{
					
						migUpdateProgfg=0;
						program_check_from_mem(iProgramLoadLoc);
						prevProgramLoadLoc = iProgramLoadLoc;
				}
				else if(migUpdateProgfg==0)
				{
					    NumberUpdate(2,80,iProgramLoadLoc);
						program_check_from_mem(iProgramLoadLoc);
						prevProgramLoadLoc = iProgramLoadLoc;
				}		
						
			}
			if( read_gsetwspeed !=  para.migmode.setwspeed )
			{
				 write_current_status();
			}
			
    		while(inch=='I')
			{
				diswin1[0]='I';
				diswin1[1]='N';
				diswin1[2]='C';
				TypeDP.DPGROUP[0]=0x00;
      			Typedp.digitdp5		=1;
				TypeU.LEDGROUP[0]=0x00;
				Type.wirespeed		=1;
				disp_hex_dec_volt(inchcntr*10.0);	
				OC2RS=(inchcntr*10.0*10.0);			//100%=64V=2949  60%=38V=1769 
				for(i=0;i<20;i++)
				for(j=0;j<40000;j++);
				inchcntr++;
				if(inchcntr>=10)
				inchcntr=10;
			}
			//if(torch=='X' && inch=='X')
		     //if((torch!='T' && weldcyclestrt!=1) && inch!='I')
			if((weldcyclestrt!=1) &&(cMacMenufg == 0))
			{
				float temp=0.0,fwirespeed=0.0;
				unsigned int wirespeed=0,current1=0,current2=0,voltage1=0,voltage2=0,inchcntr=0;
			    //if((pmigsetwirespeed!=para.migmode.setwspeed) || (dispupdatef==1) || (keychange1==1))
				if(setlcdweldparameter==0)
				{
					
					
					if((pmigsetwirespeed!=para.migmode.setwspeed) || (keychange1==1)) // CurrentSet Parameter
					{
						pstowfstr.setwspeed=para.migmode.setwspeed;
						temp=para.migmode.setwspeed;
						fwirespeed=temp*0.101; //0.060;//0.070;//0.049;//50.5;//0.101;
						//keychange1=0;
						wirespeed=fwirespeed;
						current1=iPSetCurrent[wirespeed];
						current2=iPSetCurrent[wirespeed+1];
						dispautocurrent=current1+((fwirespeed-wirespeed)*(current2-current1));
						pstowfstr.Lo_setcurrent=dispautocurrent;
						pstowfstr.Hi_setcurrent=dispautocurrent >> 8;//8;
						
						
						if(dispautocurrent>=215 && pidParams2.migweldmode==0) //root mode
						{
					      			      
					      maxwirespeedrootfg=1;
					     					    	
						}
						else{
						  
						   maxwirespeedrootfg=0;	
						}	
																
					
						if(pmigsetwirespeed!=para.migmode.setwspeed && pmig_auto0_man1==0)
						{
						voltage1=iPSetBaseVoltage[wirespeed];
						voltage2=iPSetBaseVoltage[wirespeed+1];						
//-------------------------------------	 for testing 18092019
						//voltage1 = (14 + (current1 * 0.05)) * 10;
						//voltage2 = (14 + (current2 * 0.05)) * 10;						
//-------------------------------------								
						dispautovoltage=voltage1+((fwirespeed-wirespeed)*(voltage2-voltage1));
						para.migmode.setvoltage=dispautovoltage;
						}
												
						pstowfstr.Lo_setvoltage=para.migmode.setvoltage;
						pstowfstr.Hi_setvoltage=para.migmode.setvoltage >>8;
						
						 lcd_disp_hex_dec(dispautocurrent);
						 currupdate();
						
									
						lcd_disp_hex_dec(iProgramLoadLoc);
						programupdate();
						count_1sec=0;
						transmit2f=1;//1;
					}	
					if((pmigsetwirespeed!=para.migmode.setwspeed) || (dispupdatef==1) || (keychange1==1))
					{
						if(displedptr1==dispws) //;dispwirespeed==1)
						{
							TypeU.LEDGROUP[0]	=0x00;
							Type.wirespeed		=1;
							
							TypeDP.DPGROUP[0]	=0x00;
	    					Typedp.digitdp2		=1;
							//Typedp.digitdp5		=1;
							
							if(disparclen==0)
							{
								Type.voltage	=1;
								Typedp.digitdp5	=1;
							}
							else
							{
								Type.arclength		=1;
							}
							//TypeDP.DPGROUP[0]	=0x00;
			    			//Typedp.digitdp2		=1;
							//Typedp.digitdp5		=1;
							if(mig_ocv_check_f!=1)    //when ocv check is off @sbm
							{
							disp_hex_dec_curr(para.migmode.setwspeed);
							}
						}
						else if(displedptr1==dispamp)  //current display not ws
						{
							TypeU.LEDGROUP[0]	=0x00;
							Type.current		=1;
							//Type.voltage		=1;
							//Type.arclength	=0;
							TypeDP.DPGROUP[0]	=0x00;
	    					Typedp.digitdp2		=0;
							//Typedp.digitdp5		=1;
							if(disparclen==0)
							{
								Type.voltage	=1;
								Typedp.digitdp5	=1;
							}
							else
							{
								Type.arclength	=1;
							}
							if(mig_ocv_check_f!=1)
							{
							disp_hex_dec_curr(dispautocurrent);//(para.pmigmode.setwspeed);
							}
						}
					}
					pmigsetwirespeed=para.migmode.setwspeed;
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$				
					{
						if(disparclen==1)
						{
							if((pinductance!=para.migmode.inductance)|| (dispupdatef==1) || (keychange2==1))
							{
								Type.voltage		=0;
								Type.arclength		=1;
								Typedp.digitdp5		=0;
								if(mig_ocv_check_f!=1)
								{
									disp_hex_dec_volt(para.migmode.inductance);
								}
				//				intkp=85-(para.migmode.inductance);// changed on 18092019
				//            	intki=2.5+(para.migmode.inductance/8);   //1+    //4+(para.migmode.inductance/4);
				//            	intkd=0;// changed on 18092019
				
								/*pidParams2.Kp2= 30-(para.migmode.inductance / 3);// changed on 23092019
				            	pidParams2.Ki2= 1 +(para.migmode.inductance / 15);// changed on 23092019 				
				            	pidParams2.Kd2= 0; // changed on 23092019  */				
								pstowfstr.arclength=para.migmode.inductance;
							}
							pinductance=para.migmode.inductance;
						}
						else
						{
							if((pmigsetvoltage!=para.migmode.setvoltage) || (dispupdatef==1) || (keychange2==1))
							{
								Type.voltage		=1;
								Type.arclength		=0;
								Typedp.digitdp5		=1;
								if(mig_ocv_check_f!=1)
								{
								disp_hex_dec_volt(para.migmode.setvoltage);
								}
								lcd_disp_hex_dec(para.migmode.setvoltage);
								voltupdate();
							
								pstowfstr.Lo_setvoltage=para.migmode.setvoltage;
								pstowfstr.Hi_setvoltage=para.migmode.setvoltage >> 8;
								count_1sec=0;
								transmit2f=1;//1;
								//IEC1bits.U2RXIE=0;
								//transmittowf();
								cvoffsetref=0;
								voltageref=0;
								genpwmcvref(cvoffsetref,voltageref); 
							}
							pmigsetvoltage=para.migmode.setvoltage;
						}
					}		
						clearlcdf=0;
		
					/*OC2RS=0;
					if(SPI2STATbits.SPITBF==0)
					{
						DACCSLAT	=0;
						SPI2BUF		=28672+0;     //850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
					}*/
				}  //end of setlcd parameter.
				else if(setlcdweldparameter==1) //@ 1st page 
				{
					if(lcd_saverecall_ptr==1) 	   //@Edit
					{						
						if(lcdscan_flag==1)
						{
						selectpage(2);
						selectcolumn1(0);	  
						data(&character[127][0],8);
						}
						else
						{
						selectpage(2);
						selectcolumn1(0);	  
						data(&character[0][0],8);
						}	
					} 
					else if(lcd_saverecall_ptr==2) //@Mode
					{						
						if(prev_pmig_auto0_man1!=pmig_auto0_man1 || updatelcdf==1)
						{
						pmig_auto_man_update();
						}
						prev_pmig_auto0_man1=pmig_auto0_man1;
						
						if(lcdscan_flag==1)
						{
						selectpage(3);
						selectcolumn1(0);	  
						data(&character[127][0],8);
						}
						else
						{
						selectpage(3);
						selectcolumn1(0);	  
						data(&character[0][0],8);
						}	
					} 
					else if(lcd_saverecall_ptr==3) //@Arc Time  arcontime.min
					{						
						if((prev_arcontimehr!= arcontime.hr) || (prev_arcontimemin!= arcontime.min) || updatelcdf==1) 
						{
						 arcon_time_update();
						}
						prev_arcontimehr= arcontime.hr;
						prev_arcontimemin= arcontime.min;
						
						if(lcdscan_flag==1)
						{
						selectpage(4);
						selectcolumn1(0);	  
						data(&character[127][0],8);
						}
						else
						{
						selectpage(4);
						selectcolumn1(0);	  
						data(&character[0][0],8);
						}	
					}
					else if(lcd_saverecall_ptr==4) //@Save
					{
						if((prev_save_location!= save_location) || updatelcdf==1)
						{
						lcd_disp_hex_dec(save_location);
						save_update();
						}
						prev_save_location=save_location;
						
						if(lcdscan_flag==1)
						{
						selectpage(5);
						selectcolumn1(0);	  
						data(&character[127][0],8);
						}
						else
						{
						selectpage(5);
						selectcolumn1(0);	  
						data(&character[0][0],8);
						}	
					}
					else if(lcd_saverecall_ptr==5) //@recall
					{
						if((prev_Recall_location!= Recall_location) || updatelcdf==1)
						{
						lcd_disp_hex_dec(Recall_location);
						recall_update(); 
						}
						prev_Recall_location= Recall_location;
						if(lcdscan_flag==1)
						{
						selectpage(6);
						selectcolumn1(0);	  
						data(&character[127][0],8);
						}
						else
						{
						selectpage(6);
						selectcolumn1(0);	  
						data(&character[0][0],8);
						}	
					}	
				
			   }	
				else if(setlcdweldparameter==2)
				{
						
						
						if(lcdmigpointer==1)
						{						
							if((prevpreflow!=para.migmode.preflow) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.migmode.preflow*10);
								preflowupdate();
							}
							prevpreflow=para.migmode.preflow;

							if(lcdscan_flag==1)
							{
								selectpage(2);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(2);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						else if(lcdmigpointer==2)
						{
							 if((prevburnback!=para.migmode.burnback) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.migmode.burnback);
								burnbackupdate();
							}
							prevburnback=para.migmode.burnback;

							if(lcdscan_flag==1)
							{
								selectpage(3);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(3);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						else if(lcdmigpointer==3)
						{
							if((prevpostflow!=para.migmode.postflow) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.migmode.postflow*10);
								postflowupdate();
							}
							prevpostflow=para.migmode.postflow;
							if(lcdscan_flag==1)
							{
								selectpage(4);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(4);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						else if(lcdmigpointer==4)
						{
							if((prevgcreepspeedrate!=para.creepspeedrate) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.creepspeedrate);
								Gcreepspeedupdate();
								pstowfstr.creep_speed=para.creepspeedrate;
							}
							prevgcreepspeedrate=para.creepspeedrate;
							if(lcdscan_flag==1)
							{
								selectpage(5);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(5);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						else if(lcdmigpointer==5)
						{
							
							if( (prevgcraterspeed!=para.migmode.craterspeed) || updatelcdf==1 )
							{
								pstowfstr.crater_speed=para.migmode.craterspeed;
							
								
								ftemp=para.migmode.craterspeed;
								fwirespeed=ftemp*0.101;
								
								wirespeed=fwirespeed;
								current1=iPSetCurrent[wirespeed];//findmatindex(wirespeed);
								current2=iPSetCurrent[wirespeed+1];//findmatindex((wirespeed+1));
								G_crater_current=current1+((fwirespeed-wirespeed)*(current2-current1));
								
								lcd_disp_hex_dec(G_crater_current);
								cratercurrentupdate();
							}
							prevgcraterspeed=para.migmode.craterspeed;			
							
							if(lcdscan_flag==1)
							{
								selectpage(6);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(6);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						else if(lcdmigpointer==6)
						{
							if((prevcratervoltage!=para.migmode.cratervoltage) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.migmode.cratervoltage);
								cratervoltageupdate();
							}
							prevcratervoltage=para.migmode.cratervoltage;
							if(lcdscan_flag==1)
							{
								selectpage(7);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(7);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						else if(lcdmigpointer==7)
						{
							if((prevfileno!=iFileNo) || updatelcdf==1)
							{
								NumberUpdate(2,72,iFileNo);
							}
							prevfileno = iFileNo;
							if(lcdscan_flag==1)
							{
								selectpage(2);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(2);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						else if(lcdmigpointer==8)
						{
							/*if((prevfileno!=iFileNo) || updatelcdf==1)
							{
								//NumberUpdate(2,72,iFileNo);
							}
							prevfileno = iFileNo;*/
							if((prevWeldLatchData != cWeldLatchData) || updatelcdf==1)
							{
								welddatalatchstatus();
							}
							prevWeldLatchData = cWeldLatchData;	
							if(lcdscan_flag==1)
							{
								selectpage(3);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(3);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}												
			        else if(lcdmigpointer==9)
						{						
							if((prevmigweldmode!=pidParams2.migweldmode) || updatelcdf==1)
							{
								lcd_disp_hex_dec(pidParams2.migweldmode);
								weldMode_update();
														
								/*if(pidParams2.migweldmode==0)
									//psstatus.twinpulseon=0;
									migscreenUpdate();
								else
									migscreenUpdate();*/
							}
							prevmigweldmode=pidParams2.migweldmode;
																
							if(lcdscan_flag==1)
							{
								selectpage(4);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(4);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						else if(lcdmigpointer==10)
						{
							if((prekp!=pidParams2.Kp2) || updatelcdf==1)
							{
								lcd_disp_hex_dec(pidParams2.Kp2);
								kpupdate();
								
							}
							prekp=pidParams2.Kp2;
							//intkp=prekp;
							if(lcdscan_flag==1)
							{
								selectpage(5);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(5);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						
						else if(lcdmigpointer==11)
						{
							if((preki!=pidParams2.Ki2) || updatelcdf==1)
							{
								lcd_disp_hex_dec(pidParams2.Ki2);
								kiupdate();
								
							}
							preki=pidParams2.Ki2;
							//intki=preki;
							if(lcdscan_flag==1)
							{
								selectpage(6);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(6);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						
						else if((lcdmigpointer==12) || (updatelcdf==1))
						{
							if(prekd != pidParams2.Kd2 )
							{
								lcd_disp_hex_dec(pidParams2.Kd2);
							    kdupdate();
								
							}
						
							prekd=pidParams2.Kp2;
							//intkd=prekd;
							if(lcdscan_flag==1)
							{
								selectpage(7);
								selectcolumn1(0);	  
								data(&character[127][0],8);
							}
							else
							{
								selectpage(7);
								selectcolumn1(0);	  
								data(&character[0][0],8);
							}	
						}
						
						updatelcdf=0;
				
				}
				/*else if(setlcdweldparameter == 3) //@ in File Operation 
				{
					if(iFouthPagePtr == 1)
					{
						if((prevfileno!=iFileNo) || updatelcdf==1)
						{
							NumberUpdate(2,72,iFileNo);
						}
						prevfileno = iFileNo;
						if(lcdscan_flag==1)
						{
							selectpage(2);
							selectcolumn1(0);	  
							data(&character[127][0],8);
						}
						else
						{
							selectpage(2);
							selectcolumn1(0);	  
							data(&character[0][0],8);
						}	
					}						
				
				}*/
				
									
			//	GASRELAYLAT		=OFF;						//TO CONTROL THE GAS SOLENOID VALVE
			//	HFRELAYLAT		=OFF;						//TO CONTROL THE HF RELAY
				ARCONLAT		=OFF;						//ARCON CONTROL SIGNAL INPUT TO PWM CARD
				CCCVCTRLLAT		=CCMODE;//CVMODE;					//CCCV CONTROL  INPUT TO PWM CARD.
				//SHDNLAT			=OFF;//0;			//OCV OFF @SBM
				psstatus.creepspeedon=1;  // for starting purpose

				softstartcnt	=0;
				softstartf		=0;
				dispupdatef		=0;
				keychange1		=0;
				keychange2		=0;
				cvopenloopcnt	=0;
				MIGweldon_detectf=0;
				INT_sckpidParams.INT_sckintegral_old =0;
				sf_accumulator=0;
				
				if(weldingonf==1)//@AFTER COMPLETING OF WELDING
				{				
					weldingonf=0;
					memoryzone='X';
					para.migmode.gmaterial	=mat;
					para.migmode.gdiameter	=dia;
					para.migmode.ggas		=gas;	
					 write_current_status();
					
					/*if(pmig_auto0_man1==1)
					{
					   para.migmode.setvoltage=pmigsetvoltage;	
					  
					}
					else
					{
					   write_current_status();
					}*/	
				}	
			}
			//else if(torch=='T' || weldcyclestrt==1)
			else if(weldcyclestrt==1)	//@5.2.19				//welding started
			{
					
				
				dispupdatef=1;
				weldingonf=1;
				//psstatus.creepspeedon=0;  // for starting purpose
					if( (encod3!='$' || encod2 !='$') )
				  {
					updategcvparameter(encod3,encod2);  	//@user input current and voltage	
					encod3='$';
					encod2='$';
					 if(pmigsetvoltage!=para.migmode.setvoltage) 
					{
						
						lcd_disp_hex_dec(para.migmode.setvoltage);
						voltupdate();
					}
					pmigsetvoltage =para.migmode.setvoltage;  
					
					
					if((pmigsetwirespeed!=para.migmode.setwspeed) || (keychange1==1)) // CurrentSet Parameter
					{
						pstowfstr.setwspeed=para.migmode.setwspeed;
						temp=para.migmode.setwspeed;
						fwirespeed=temp*0.101; //0.060;//0.070;//0.049;//50.5;//0.101;
						//keychange1=0;
						wirespeed=fwirespeed;
						current1=iPSetCurrent[wirespeed];
						current2=iPSetCurrent[wirespeed+1];
						dispautocurrent=current1+((fwirespeed-wirespeed)*(current2-current1));
						
						para.migmode.setcurrent=dispautocurrent;
						pstowfstr.Lo_setcurrent=dispautocurrent;
						pstowfstr.Hi_setcurrent=dispautocurrent >> 8;//8;
						
						lcd_disp_hex_dec(dispautocurrent);
						currupdate();
						
						uiFristP=(((0.369*para.migmode.setcurrent)+178.2)*1.12);
						uiFristDW=((((0.369*para.migmode.setcurrent)+178.2)/2)*1.12)+25;
						uiSecondP	=((0.4836*para.migmode.setcurrent)+195.5)*1.12;
						
					}	
					pmigsetwirespeed = para.migmode.setwspeed	;
				
				}
				
				
				
				
				if(oper==pre)
				{
					
					TypeDP.DPGROUP[0]=0x00;
	      			Typedp.digitdp5		=1;
					TypeU.LEDGROUP[0] =0x00;
					///Type.current		=1;
					Type.time		=1;
					diswin1[0]='P';
					diswin1[1]='R';
					diswin1[2]='E';
					disp_hex_dec_volt(para.migmode.preflow*10.0);
					cvoffsetref=0;
					voltageref=0;
					disparclen=0;
					genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
				}
				else if(oper==weld)
				{
					//SHDNLAT=1;			//OCV ON
					if(disparclen==0)
					{
						TypeDP.DPGROUP[0]=0x00;
      					Typedp.digitdp5		=1;
						TypeU.LEDGROUP[0] =0x00;
						Type.current		=1;
						Type.voltage		=1;
						disp_hex_dec_curr(CURRENT);//migdaccount);//CURRENT);//para.migmode.setwspeed);//CURRENT);//disp_newbaseamp);//CURRENT);
						disp_hex_dec_volt(VOLTAGE);//para.migmode.setvoltage);//VOLTAGE);
						
										
					
					}
				    /*else if(disparclen==1)
					{
						if((pinductance!=para.migmode.inductance)|| (dispupdatef==1) || (keychange2==1))
						{
			//				intkp=85-(para.migmode.inductance);// changed on 18092019
			//            	intki=2.5+(para.migmode.inductance/8);   //1+    //4+(para.migmode.inductance/4);
			//            	intkd=0;// changed on 18092019

							pidParams2.Kp2=30-(para.migmode.inductance / 3);// changed on 23092019
			            	pidParams2.Ki2=1 +(para.migmode.inductance / 15);// changed on 23092019 				
			            	pidParams2.Kd2=0; // changed on 23092019  
          				}
						pinductance=para.migmode.inductance;
						
						TypeDP.DPGROUP[0]   =0x00;
      					Typedp.digitdp5		=0;//1;
						TypeU.LEDGROUP[0]   =0x00;
						Type.current		=1;
						Type.arclength		=1;
						disp_hex_dec_curr(CURRENT);//para.migmode.setwspeed);//CURRENT);//disp_newbaseamp);//CURRENT);
						disp_hex_dec_volt(para.migmode.inductance);//para.migmode.setvoltage);//VOLTAGE);
					}*/
				
			
					if(wfstatus.twotfourtmode1==0)    //2T MODE
					{
						cvoffsetref=CVOFFSET;
						voltageref=para.migmode.setvoltage;
						genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1);
					}
					else
					{
						if(torchrelease==1 && cratersetup==0)
						{
							cvoffsetref=CVOFFSET;
							voltageref=para.migmode.setvoltage;
							genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1);
						}
						else if(torchrelease==1 && cratersetup==1)
						{
							cvoffsetref=CVOFFSET;
							voltageref=para.migmode.cratervoltage;
							genpwmcvref(cvoffsetref,voltageref); 
						}
					}
				
					
					   
				}
				else if(oper==burn)
				{
					TypeDP.DPGROUP[0]=0x00;
	      			Typedp.digitdp5		=1;
					TypeU.LEDGROUP[0] =0x00;
					///Type.current		=1;
					Type.time		=1;
					diswin1[0]='B';
					diswin1[1]='R';
					diswin1[2]='N';
					disp_hex_dec_volt(para.migmode.burnback);
					cvoffsetref=CVOFFSET;
					fttrefvolt=140;
					voltageref=fttrefvolt;
				    genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1);     

				}
				else if(oper==post)
				{
					TypeDP.DPGROUP[0]=0x00;
	      			Typedp.digitdp5		=1;
					TypeU.LEDGROUP[0] =0x00;
					///Type.current		=1;
					Type.time			=1;
					diswin1[0]='P';
					diswin1[1]='S';
					diswin1[2]='T';
					disp_hex_dec_volt(para.migmode.postflow*10.0);
					cvoffsetref=0;
					voltageref=0;
					genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1);     
		
				}
			}			
}

/*
void genpwmocvref(unsigned int refvoltage)  //((para.pwmtime1*0.75));               //FTT FUNCTION.
{
	CCCVCTRLLAT	=CVMODE;					//CCCV CONTROL  INPUT TO PWM CARD.
	SHDNLAT		=ON;			//OCV ON
	ARCONLAT		=ON;						//ARCON CONTROL SIGNAL INPUT TO PWM CARD
	
	if(SPI2STATbits.SPITBF==0)
	{
		DACCSLAT		=0;
		daccount	=CVOFFSET+(refvoltage*6.30);
		daccount	=0;
		SPI2BUF		=28672+daccount;     		//850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
	}
}
*/

//@ arguments are not used in this function
void genpwmcvref(unsigned int refcvoffset, unsigned int refvoltage)  //((para.pwmtime1*0.75));               //FTT FUNCTION. refcvoffset=CVOFFSET
{
	if((weldmode=='G'))
	{
		if(refvoltage!=0)
		{
			if((cEndPulsefg == 0)&&(cStartPulsefg == 0))
			{
				CCCVCTRLLAT		=CCMODE;//CVMODE					//CCCV CONTROL  INPUT TO PWM CARD.
				if(cWeldStartfg == 0)
				{
					SHDNLAT			=ON;								
				}		
				ARCONLAT		=OFF;   //ON						//ARCON CONTROL SIGNAL INPUT TO PWM CARD
		    	if(SPI2STATbits.SPITBF==0)
				{
					DACCSLAT	=0;
					//daccount	=  //(refvoltage*CVSLOPE)-refcvoffset;
					//daccount	=sckdaccount;
					daccount   =(migdaccount*CCSLOPENEW)-CCOFFSETNEW;	 							
					SPI2BUF		=28672+daccount;     		//850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
				}				
			}			
			else if((cEndPulsefg == 1)&&(cWaitToStopMtrfg == 0) && (cStartPulsefg == 0))
			{
				CCCVCTRLLAT		=CCMODE;
				SHDNLAT			=ON;								
				ARCONLAT		=OFF;  					
		    	if(SPI2STATbits.SPITBF==0)
				{
					DACCSLAT	=0;
					daccount   =(ENPULSECURR*CCSLOPENEW)-CCOFFSETNEW;
					SPI2BUF		=28672+daccount;
				}				
			}		
			else if(cStartPulsefg == 1)
			{
				CCCVCTRLLAT		=CCMODE;
				if(cWeldStartfg == 0)
				{
					SHDNLAT			=ON;								
				}								
				ARCONLAT		=OFF;  					
		    	if(SPI2STATbits.SPITBF==0)
				{
					DACCSLAT	=0;
					daccount   =(iStartCurr *CCSLOPENEW)-CCOFFSETNEW;		//dispautocurrent
					SPI2BUF		=28672+daccount;
				}				
			}				
		}
		else
		{
			CCCVCTRLLAT		=CCMODE;//CVMODE;				        //CCCV CONTROL  INPUT TO PWM CARD.
			if(mig_ocv_check_f!=1)                          //ocv off when display is not in ocv check mode@sbm
			{
				SHDNLAT	=OFF;							//OCV ON//@SBM						
		    }    						    
			ARCONLAT		=OFF;//ON;						//ARCON CONTROL SIGNAL INPUT TO PWM CARD
	    	if(SPI2STATbits.SPITBF==0)
			{
				DACCSLAT	=0;
				daccount	=10;//(refvoltage*CVSLOPE)-refcvoffset;
				SPI2BUF		=28672+daccount;     		//850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
			}					
		}
	
	}	
}

void genpwmccref(unsigned int refcurrent)   //((para.pwmtime1*0.75));               //FTT FUNCTION.
{
	CCCVCTRLLAT	=CCMODE;					//CCCV CONTROL  INPUT TO PWM CARD.
//	SHDNLAT		=ON;						//OCV ON
	ARCONLAT	=OFF;						//ARCON CONTROL SIGNAL INPUT TO PWM CARD
	if(SPI2STATbits.SPITBF==0)
	{
		DACCSLAT	=0;
		daccount	=(refcurrent*CCSLOPENEW)-CCOFFSETNEW;
		SPI2BUF		=28672+daccount;     		//850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
	}

}

void update_MIG_syn_data(unsigned char synkey)
{
	if(synkey=='A')
	{
		if(mat==ms)
		{
			mat=ss;
			dia=onepttwo;
			gas=aro2;
//			lcdput(7,0,matss);
//			lcdput(7,48,diaonepttwo);
//			lcdput(7,90,gasaro2);
		}	
		else if(mat==ss)
		{
			mat=alu;
			dia=onepttwo;
			gas=ar;
//			lcdput(7,0,matalu);
//			lcdput(7,48,diaonepttwo);
//			lcdput(7,90,gasar);
			
		}
		else if(mat==alu)
		{
			mat=msfcaw;
			dia=onepttwo;
			gas=co2;
//			lcdput(7,0,matms);
//			lcdput(7,48,diaonepttwo);
//			lcdput(7,90,gasco2);
		}
		else if(mat==msfcaw)
		{
			mat=ssfcaw;
			dia=onepttwo;
			gas=co2;
//			lcdput(7,0,matms);
//			lcdput(7,48,diaonepttwo);
//			lcdput(7,90,gasco2);
		}
		else if(mat==ssfcaw)
		{
			mat=ms;
			dia=onepttwo;
			gas=co2;
//			lcdput(7,0,matms);
//			lcdput(7,48,diaonepttwo);
//			lcdput(7,90,gasco2);
		}	
		lcdput(6,0,cMatMigTxt[mat]);		
		lcdput(6,48,cDiaTxt[dia]);					
		lcdput(6,88,cGasTxt[gas]);		
		lcdput(7,80,cGasPercent[gas]);			
	}
	else if(synkey=='B')
	{
			if(mat==ms)
			{
				if(dia==zeropteight)
				{
					dia=oneptzero;
//					lcdput(7,48,diaoneptzero);
				}	
				else if(dia==oneptzero)
				{
					dia=onepttwo;
//					lcdput(7,48,diaonepttwo);
				}
				
				else if(dia==onepttwo)
				{
					dia=oneptsix;
//					lcdput(7,48,diaoneptsix);
				}
				else if(dia==oneptsix)
				{
					dia=zeropteight;
//					lcdput(7,48,diazeropteight);
				}
			}
			if(mat==ss)
			{
				if(dia==onepttwo)
				{
					dia=zeropteight;
//					lcdput(7,48,diazeropteight);
				}
				else if(dia==zeropteight)
				{
					dia=onepttwo;
//					lcdput(7,48,diaonepttwo);
				}
			}
			if(mat==alu)
			{
				dia=onepttwo;
//				lcdput(7,48,diaonepttwo);
				
			}
			if((mat==msfcaw)||(mat==ssfcaw))
			{
				dia=onepttwo;
//				lcdput(7,48,diaonepttwo);
				
			}			
			lcdput(6,48,cDiaTxt[dia]);			
	}
	else if(synkey=='C')
	{
		if((mat==ms) ||(mat==msfcaw)||(mat==ssfcaw))
		{
			if(gas==arco2)
			{
				gas=co2;
//				lcdput(7,90,gasco2);
			}	
			else if(gas==co2)
			{
				gas=arco2;
//				lcdput(7,90,gasarco2);
			}
		}
		else if(mat==ss)
		{
			if(gas==arco2)
			{
				gas=aro2;
//				lcdput(7,90,gasaro2);
			}	
			else if(gas==aro2)
			{
				gas=arco2;
//				lcdput(7,90,gasarco2);
			}
		}	
		else if(mat==alu)
		{
			gas=ar;
//			lcdput(7,90,gasar);
		}
		lcdput(6,88,cGasTxt[gas]);		
		lcdput(7,80,cGasPercent[gas]);		
	}
}

void LCD_mig_syn_data_write()
{
	{
		/*
					if(mat==ms)
						lcdput(7,0,matms);
					else if(mat==ss)
						lcdput(7,0,matss);
					else if(mat==alu)
						lcdput(7,0,matalu);
						*/
				lcdput(6,0,cMatMigTxt[mat]);						
	}
	{
		/*
					if(dia==zeropteight)
						lcdput(7,48,diazeropteight);
					else if(dia==oneptzero)
						lcdput(7,48,diaoneptzero);
					else if(dia==onepttwo)
						lcdput(7,48,diaonepttwo);
					else if(dia==oneptsix)
						lcdput(7,48,diaoneptsix);
		*/
			lcdput(6,48,cDiaTxt[dia]);						
	}
	{
/*
					if(gas==arco2)
						lcdput(7,90,gasarco2);
					else if(gas==co2)
						lcdput(7,90,gasco2);
					else if(gas==ar)
						lcdput(7,90,gasar);	
					else if(gas==aro2)
						lcdput(7,90,gasaro2);	
*/
		lcdput(6,88,cGasTxt[gas]);		
		lcdput(7,80,cGasPercent[gas]);							
	}
}
//-------------------------------------------------------
unsigned int LoadPeakCurrentasperDia(void)
{
	unsigned int iCurrent;
	if(mat != 2 )
	{
		if(dia == 0)
		{
			iCurrent = 250;
		}
		else if(dia == 1)
		{
			iCurrent = 300;		
		}
		else if(dia == 2)
		{
			iCurrent = 350;		
		}	
		else if(dia == 3)
		{
			iCurrent = 400;		
		}		
		else
		{
			iCurrent = 300;	 // default 300A
		}	
	}
	else
	{
		if(dia == 0)
		{
			iCurrent = 200;
		}
		else if(dia == 1)
		{
			iCurrent = 250;		
		}
		else if(dia == 2)
		{
			iCurrent = 300;		
		}	
		else if(dia == 3)
		{
			iCurrent = 350;		
		}
		else
		{
			iCurrent = 300;	 // default 300A
		}			
	}			
	return(iCurrent);		
}	
//-------------------------------------------------------


	