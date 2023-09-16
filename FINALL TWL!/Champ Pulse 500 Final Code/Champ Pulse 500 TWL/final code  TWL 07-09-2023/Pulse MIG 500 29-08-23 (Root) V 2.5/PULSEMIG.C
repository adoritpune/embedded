void PULSEWELD(void)
{
	if(modechangef==1)
	{
		transmitonf=0;
		clrlcd();	
		
		iProgramLoadLoc = I2C_Read1(PMIG_PROGRAM_ADDR+1);
		iProgramLoadLoc = iProgramLoadLoc << 8;
		iProgramLoadLoc |= I2C_Read1(PMIG_PROGRAM_ADDR);		
		iPreviousProg = prevProgramLoadLoc = iProgramLoadLoc;
		
		read_from_external_memory(iProgramLoadLoc);//iProgramLoadLoc);					
		
		lcdput_bold(0,0,ar41);  //@print Pulsemig mode, current, voltage on GLCD
		lcdput(2,0,ar42);
		lcdput(4,0,ar43);
	//@	lcdput(7,0,ar50);       //@avoid displaying MIG 1.2 MS 
				
		diswin1[0]='P';          //@ 7-segment init with PMIG MOD
		diswin1[1]='M';
		diswin1[2]='G';
		diswin2[0]='M';
		diswin2[1]='O';
		diswin2[2]='D';
		//pmig_para_init();
		SHDNLAT=0;			      //OCV OFF
		for(j=0;j<200;j++)
		for(i=0;i<10000;i++);
		modechangef=0;
		displedptr1=dispamp;   //dispws;@sbm
		//pmat=pms;
		//pdia=ponepttwo;
		//pgas=parco2;
		//program_number=19;
		//para.pmigmode.arclength=10;
										//update_PMIG_pulse_para();
		//load_pulse_parameter();
		dispupdatef=1;         
		disparclen=0;           //1;@sbm
		CCCVCTRLLAT	=CCMODE;		  //CCCV CONTROL  INPUT TO PWM CARD.

		iLoadBlockCnt = PMIGMINPROGRAMLOAD;		
		
		memoryzone='X';
		weldmode='P'; 
		eedata=weldmode;//3456;							//0x0003;
		EEPROM_Erase_Write((0*2),eedata);
		
		read_current_status();
		check_eeprom_values();
		
		prev_weldmode=weldmode;
		read_ppreflow=para.pmigmode.preflow;
		read_psetwspeed=para.pmigmode.setwspeed;
		read_psetvoltage=para.pmigmode.setvoltage;
		read_parclength=para.pmigmode.arclength;
		read_pburnback=para.pmigmode.burnback;
		read_ppostflow=para.pmigmode.postflow;
		
		read_pmaterial=para.pmigmode.pmaterial;
	
//		pmat=para.pmigmode.pmaterial;
		
		read_pdiameter=para.pmigmode.pdiameter;
//		pdia=para.pmigmode.pdiameter;
		
		read_pgas=para.pmigmode.pgas;
//		pgas=para.pmigmode.pgas;
		
		read_ppulseweldmode=para.pulseweldmode;
		read_ptwinpulsefreq=para.twinpulsefreq;
		read_ptwinpulseduty=para.twinpulseduty;
		read_ptwinpulseratio=para.twinpulseratio;
		twinpulseratio=para.twinpulseratio;
	
	    pstowfstr.arclength=para.pmigmode.arclength;
/*************************crater parameter start*************************/				
		pstowfstr.crater_speed=para.pmigmode.craterspeed; 
		pstowfstr.creep_speed=para.pcreepspeedrate;
		
		ftemp=para.pmigmode.craterspeed;
		fwirespeed=ftemp*0.101;
		
		wirespeed=fwirespeed;
		current1=iPSetCurrent[wirespeed];//newfindmatindex4(wirespeed);
		current2=iPSetCurrent[wirespeed+1];//newfindmatindex4((wirespeed+1));
		P_crater_current=current1+((fwirespeed-wirespeed)*(current2-current1));

		Tbasevoltage1=iPSetBaseVoltage[wirespeed];//newfindmatindex7(wirespeed);
		Tbasevoltage2=iPSetBaseVoltage[wirespeed+1];//newfindmatindex7((wirespeed+1));
		Tbasevoltage=Tbasevoltage1+((fwirespeed-wirespeed)*(Tbasevoltage2-Tbasevoltage1));
		calculate_arcbasevtg(Tbasevoltage);
		
 /*************************crater parameter end*************************/	
 			
			program_number=iPProgramNo;//newpmmmatgas[pdia][pmat][pgas];
			
			lcd_disp_hex_dec(para.pmigmode.setcurrent);
			currupdate();
			
			lcd_disp_hex_dec(para.pmigmode.setvoltage);			
			voltupdate();
			
			parcbasevtg=para.pmigmode.setvoltage;
			Tbasevoltage=parcbasevtg;
				
			current1=iPSetCurrent[wirespeed];//newfindmatindex4(para.pmigmode.setwspeed);  //PROGRAM NUMBER WILL BE UPLOADED
			load_pulse_parameter();
			transmitonf=1;
			Load_Initial_Constant(para.pmigmode.setwspeed);
			weld_p_para_latch=1;

			if(cSerialPortTask)
			{
				/*SendDataToIOTGateway(JSON_WELDPROCESS,1);
				SendDataToIOTGateway(JSON_WIRESPEED,para.pmigmode.setwspeed);
				SendDataToIOTGateway(JSON_SETCURRENT,para.pmigmode.setcurrent);
				SendDataToIOTGateway(JSON_SETVOLTAGE,Tbasevoltage);
				SendDataToIOTGateway(JSON_MATERIAL,1);
				SendDataToIOTGateway(JSON_DIAMETER,1);
				SendDataToIOTGateway(JSON_GAS,1);
				SendDataToIOTGateway(JSON_WELDMODE,1);
				*/					
			}
	}
	
//	arcon_time_update();
    if(encod3!='$' && setlcdweldparameter==0 && password_protection_enabled==0)  //@ take input==>wirespeed from user,password disabled
		{
			
	     	max_Pws=max_Pwire_speed[program_number];
	     	para.pmigmode.setwspeed=updatedata(para.pmigmode.setwspeed,mini.pmigmode.setwspeed,iMaxWSLimit,encod3);	//		changed on 29/01/2021 
			//para.pmigmode.setwspeed=updatedata(para.pmigmode.setwspeed,mini.pmigmode.setwspeed,max_Pws,encod3);
			encod3='$';
		}
		else if((encod1!='$') && (setlcdweldparameter!=0) && (password_protection_enabled==0) && (cPMainMenufg == 0)) //@ take inpu from  user for pulse settings
		{
			updatepmigparameter(encod1);	
			encod1='$';
		}
		else if((encod1!='$') && (setlcdweldparameter==0) && (cPMainMenufg == 1))
		{
			iProgramLoadLoc = updatedata(iProgramLoadLoc,2,200,encod1);
			encod1='$';
		}
		
		
		if(prevProgramLoadLoc != iProgramLoadLoc)
		{
			NumberUpdate(2,80,iProgramLoadLoc);
			program_check_from_mem(iProgramLoadLoc);
			prevProgramLoadLoc = iProgramLoadLoc;
		}
		
        if( (read_psetwspeed != para.pmigmode.setwspeed) )
		{
		 write_current_status();
		}
	
	if((setupmode==0)&&(cMacMenufg == 0))
	{
		
		
		if(weldcyclestrt!=1 )//|| weld_para_latch==0) //@ welding is in not process
		{
			if(weldingonf==1)
			{
				weldingonf=0;
			memoryzone='X';			 
				para.pmigmode.pdiameter=pdia;
				para.pmigmode.pgas=pgas;
				para.pmigmode.pmaterial=pmat;	
						
				write_current_status();
			}
			
			if(mig_ocv_check_f!=1) 
			{
					
				SHDNLAT			=0;			//OCV OFF
			}
			
			inchcntr		=0;
			psstatus.creepspeedon=1;				 
			openloopnew		=0;
			firsttimef		=0;
			loadpara1		=0;
			openloopf   	=1;
			inchcntr		=0;
			mbase1f 		=0;
			mbase2f 		=0;
			shiftbvtgf		=0;
			sendoncef		=0;
			changestatusf	=0;
			pulsestartcnt	=0;
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	
			if((setlcdweldparameter==0)&&(cMacMenufg == 0))
			{
				if((ppmigsetwirespeed!=para.pmigmode.setwspeed) || (dispupdatef==1) || (keychange1==1))
				{
					wfchangef=1;
									
					pstowfstr.setwspeed=para.pmigmode.setwspeed;
									
					ftemp=para.pmigmode.setwspeed;
					fwirespeed=ftemp*0.101;
					
					wirespeed=fwirespeed;
					current1=iPSetCurrent[wirespeed];//newfindmatindex4(wirespeed);
					current2=iPSetCurrent[wirespeed+1];//newfindmatindex4((wirespeed+1));
					dispautocurrent=current1+((fwirespeed-wirespeed)*(current2-current1));
					pstowfstr.Lo_setcurrent=dispautocurrent;
					pstowfstr.Hi_setcurrent=dispautocurrent >> 8;
			        ;
			        
			        //not useful
			     //   voltage1=newfindmatindex5(wirespeed);
				//	voltage2=newfindmatindex5((wirespeed+1));
				//	para.pmigmode.setvoltage=voltage1+((fwirespeed-wirespeed)*(voltage2-voltage1));
				
				//5.02	pstowfstr.Lo_setvoltage=para.pmigmode.setvoltage;
				//5.02	pstowfstr.Hi_setvoltage=para.pmigmode.setvoltage >> 8;
			        // para.pmigmode.setvoltage=dispautovoltage;
			      	;
			      	thickness1=iPThickness[wirespeed];//newfindmatindex6(wirespeed);
					thickness2=iPThickness[wirespeed+1];//newfindmatindex6((wirespeed+1));
					para.pmigmode.thickness=thickness1+((fwirespeed-wirespeed)*(thickness2-thickness1));
			        ;
			        
			        
			        if(ppmigsetwirespeed!=para.pmigmode.setwspeed && pmig_auto0_man1==0) //@in auto mode
			        {
			        
						    Tbasevoltage1=iPSetBaseVoltage[wirespeed];//newfindmatindex7(wirespeed);
							Tbasevoltage2=iPSetBaseVoltage[wirespeed+1];//newfindmatindex7((wirespeed+1));			
							Tbasevoltage=Tbasevoltage1+((fwirespeed-wirespeed)*(Tbasevoltage2-Tbasevoltage1));
							SetPulseVoltage=Tbasevoltage;
							//Tbasevoltage=Tbasevoltage-30;
							Tbasevoltage=Tbasevoltage;
					      /*if(cDisplayDia==0)
							{
							Tbasevoltage1=iPSetBaseVoltage[wirespeed];//newfindmatindex7(wirespeed);
							Tbasevoltage2=iPSetBaseVoltage[wirespeed+1];//newfindmatindex7((wirespeed+1));			
							Tbasevoltage=Tbasevoltage1+((fwirespeed-wirespeed)*(Tbasevoltage2-Tbasevoltage1));
							SetPulseVoltage=Tbasevoltage;
							//Tbasevoltage=Tbasevoltage-30;
							Tbasevoltage=Tbasevoltage;
							}
							else if(cSoftwireDetfg == 1)
							{
								Tbasevoltage1=iPSetBaseVoltage[wirespeed];//newfindmatindex7(wirespeed);
								Tbasevoltage2=iPSetBaseVoltage[wirespeed+1];//newfindmatindex7((wirespeed+1));			
								Tbasevoltage=Tbasevoltage1+((fwirespeed-wirespeed)*(Tbasevoltage2-Tbasevoltage1));
								SetPulseVoltage=Tbasevoltage;
								Tbasevoltage=Tbasevoltage+20;
								
							}	
							else
							{
								Tbasevoltage1=iPSetBaseVoltage[wirespeed];//newfindmatindex7(wirespeed);
								Tbasevoltage2=iPSetBaseVoltage[wirespeed+1];//newfindmatindex7((wirespeed+1));			
								Tbasevoltage=Tbasevoltage1+((fwirespeed-wirespeed)*(Tbasevoltage2-Tbasevoltage1));
								SetPulseVoltage=Tbasevoltage;
								Tbasevoltage=Tbasevoltage+10;	
								
							}*/
					
					calculate_arcbasevtg(Tbasevoltage);
			   		}
			   		;
					lcd_disp_hex_dec(dispautocurrent);//sumdaccount);//dispautocurrent);//para.pmigmode.setvoltage);//dispautocurrent);
					currupdate();
					;
									
					//lcd_disp_hex_dec(dispautovoltage);
					//voltupdate();
					
					;				
					lcd_disp_hex_dec(program_number);
					programupdate();
				    ;
				    if(1)
				    {
						//update_PMIG_pulse_para();
						load_pulse_parameter();
				    }
				    //calculate_arcbasevtg();
				    ;
				    if(displedptr1==dispws)//(if(dispwirespeed==1)
					{
						//TypeU.LEDGROUP[0]	=0x00;
						Type.wirespeed		=1;
						Type.current		=0;
						Type.thickness		=0;
						//Type.voltage		=1;
						TypeDP.DPGROUP[0]	= TypeDP.DPGROUP[0] & 0xF8;
						Typedp.digitdp2		=1;
						//Typedp.digitdp5		=1;
						if(ocvonfg == 0)//(mig_ocv_check_f!=1)
						{
						disp_hex_dec_curr(para.pmigmode.setwspeed);
						}
					}
					else if(displedptr1==dispamp)
					{
						//TypeU.LEDGROUP[0]	=0x00;
						Type.wirespeed		=0;
						Type.current		=1;
						Type.thickness		=0;
						//Type.voltage		=1;
						TypeDP.DPGROUP[0]	= TypeDP.DPGROUP[0] & 0xF8;
    					Typedp.digitdp2		=0;
						//Typedp.digitdp5		=1;
						
						if(ocvonfg == 0)//(mig_ocv_check_f!=1)
						{
						disp_hex_dec_curr(dispautocurrent);//psetcurrent);
						}
					}
					else if(displedptr1==dispthickness)
					{
						Type.wirespeed		=0;
						Type.current		=0;
  						Type.thickness		=1;
						//Type.voltage		=1;
						TypeDP.DPGROUP[0]	= TypeDP.DPGROUP[0] & 0xF8;
						Typedp.digitdp2		=1;
						//Typedp.digitdp5		=1;
						disp_hex_dec_curr(para.pmigmode.thickness);//psetcurrent);
					}
					count_1sec=0;//800;
					transmit2f=1;//1;
					//newpeakamp=refpeakamp+(para.pmigmode.setwspeed/5.0);
				}
			ppmigsetwirespeed=para.pmigmode.setwspeed;
			//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
			{
			  if(disparclen==1)
				{
					if(encod2!='$' && password_protection_enabled==0)// && (disparclen==1)) ,password disabled
					{
						para.pmigmode.arclength=updatedata1(para.pmigmode.arclength,mini.pmigmode.arclength,maxi.pmigmode.arclength,encod2);
						encod2='$';
	    				//calculate_arcbasevtg();
					}
					if((parclength!=para.pmigmode.arclength) || (dispupdatef==1) || (keychange1==1))
					{
						Type.voltage		=0;
						Type.arclength		=1;
						Typedp.digitdp5		=0;
						if(ocvonfg == 0)//(mig_ocv_check_f!=1)
						{
						disp_hex_dec_arclength2(para.pmigmode.arclength);
						}
						pstowfstr.arclength=para.pmigmode.arclength;
					//@	calculate_arcbasevtg(Tbasevoltage);
						count_1sec=0;//800;
						transmit2f=1;//1;
					}
					parclength=para.pmigmode.arclength;
				}
				else
				{
					if((encod2!='$') && (disparclen==0) &&(password_protection_enabled==0))
					{							
						Tbasevoltage=updatedata1(Tbasevoltage,mini.pmigmode.setvoltage,maxi.pmigmode.setvoltage,encod2);
						para.pmigmode.setvoltage = Tbasevoltage;
			    		calculate_arcbasevtg(Tbasevoltage);							
						encod2='$';											
					}	
					if(password_protection_enabled==0)
					{					
						if(cWfVChangefg == 1)// voltage change from wire feeder then do not over write to para.pmigmode.setvoltage // chnage done on 13092019
						{
							Tbasevoltage = para.pmigmode.setvoltage = iRxwfVoltage;
							cWfVChangefg = 0;
							iRxwfVoltage = 0;
				    		calculate_arcbasevtg(Tbasevoltage);							
						}					
					}
					if((ppmigsetvoltage!=para.pmigmode.setvoltage) || (dispupdatef==1) || (keychange1==1))
					{	
						Type.voltage		=1;
						Type.arclength		=0;
						Typedp.digitdp5		=1;
						
						if(ocvonfg == 0)//(mig_ocv_check_f!=1)
						{
						para.pmigmode.setvoltage=SetPulseVoltage;	
						disp_hex_dec_volt(para.pmigmode.setvoltage);//para.pmigmode.setvoltage);
						}
						pstowfstr.Lo_setvoltage=para.pmigmode.setvoltage;
						pstowfstr.Hi_setvoltage=para.pmigmode.setvoltage >> 8;
						count_1sec=0;//800;
						transmit2f=1;//1;
					    calculate_arcbasevtg(Tbasevoltage);
				     }
				     ppmigsetvoltage=para.pmigmode.setvoltage;
				}
			}
		}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
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
				else if(setlcdweldparameter==2) //@ in preflow 
				{
						if(lcdmigpointer==1)
						{						
							if((prevpreflow!=para.pmigmode.preflow) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.pmigmode.preflow*10);
								preflowupdate();
							}
							prevpreflow=para.pmigmode.preflow;

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
							 if((prevburnback!=para.pmigmode.burnback) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.pmigmode.burnback);
								burnbackupdate();
							}
							prevburnback=para.pmigmode.burnback;

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

							if((prevpostflow!=para.pmigmode.postflow) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.pmigmode.postflow*10);
								postflowupdate();
							}
							prevpostflow=para.pmigmode.postflow;
							
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
							if((prev_pcreepspeedrate!=para.pcreepspeedrate) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.pcreepspeedrate);
								Gcreepspeedupdate();
								pstowfstr.creep_speed=para.pcreepspeedrate;
							}
							prev_pcreepspeedrate=para.pcreepspeedrate;
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
							if((prevcraterspeed!=para.pmigmode.craterspeed) || updatelcdf==1)
							{
								pstowfstr.crater_speed=para.pmigmode.craterspeed;
							
								
								ftemp=para.pmigmode.craterspeed;
								fwirespeed=ftemp*0.101;
								
								wirespeed=fwirespeed;
								current1=iPSetCurrent[wirespeed];//newfindmatindex4(wirespeed);
								current2=iPSetCurrent[wirespeed+1];//newfindmatindex4((wirespeed+1));
								P_crater_current=current1+((fwirespeed-wirespeed)*(current2-current1));
								
								lcd_disp_hex_dec(P_crater_current);
								cratercurrentupdate();
							}
							prevcraterspeed=para.pmigmode.craterspeed;

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
							if((prevcratervoltage!=para.pmigmode.cratervoltage) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.pmigmode.cratervoltage);
								cratervoltageupdate();
							}
							prevcratervoltage=para.pmigmode.cratervoltage;
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
//##############################################################################################################
						else if(lcdmigpointer==7)
						{						
							if((prevpulseweldmode!=para.pulseweldmode) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.pulseweldmode);
								pulseweldmodeupdate();
								if(para.pulseweldmode==0)
									psstatus.twinpulseon=0;
								else
									psstatus.twinpulseon=1;
							}
							prevpulseweldmode=para.pulseweldmode;
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
							 if((prevtwinpulsefreq!=para.twinpulsefreq) || updatelcdf==1)
							 {
								lcd_disp_hex_dec(para.twinpulsefreq);
								twinpulsefrequpdate();
							 	twinpulseperiod=10000.0/para.twinpulsefreq;   //ms range =10 to 100
							 }
							 prevtwinpulsefreq=para.twinpulsefreq;
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
							if((prevtwinpulseduty!=para.twinpulseduty) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.twinpulseduty);
								twinpulsedutyupdate();
								twinpulseonperiod=twinpulseperiod*para.twinpulseduty/100.0;
								twinpulseoffperiod=twinpulseperiod-twinpulseonperiod;
							}
							prevtwinpulseduty=para.twinpulseduty;
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
							if((prevtwinpulseratio!=para.twinpulseratio) || updatelcdf==1)
							{
								lcd_disp_hex_dec(para.twinpulseratio);
								twinpulseratioupdate();
								twinpulseratio=para.twinpulseratio;
							}
							prevtwinpulseratio=para.twinpulseratio;
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
							if((prevfileno!=iFileNo) || updatelcdf==1)
							{
								NumberUpdate(6,72,iFileNo);
								//check_OTP();
							}
							prevfileno = iFileNo;
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
						else if(lcdmigpointer==12)
						{
							/*if((prevfileno!=iFileNo) || updatelcdf==1)
							{
								NumberUpdate(6,72,iFileNo);
								//check_OTP();
							}
							prevfileno = iFileNo;*/
							
							if((prevWeldLatchData != cWeldLatchData) || updatelcdf==1)
							{
								welddatalatchstatus();
							}
							prevWeldLatchData = cWeldLatchData;	
							
							welddatalatchstatus();
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
						
//###############################################################################################################						
						
						updatelcdf=0;
					}
					
											
					

		 
			
			dispupdatef=0;
			keychange1=0;
			//OC2RS=0;
			if(weldmodeoff==0)
			{
				if(SPI2STATbits.SPITBF==0)
  				{
					DACCSLAT=0;
					SPI2BUF=28672+0;//MAHESH;//DACREF;//1300;//102A 600
  				}
				weldmodeoff=1;
			}	
		//	GASRELAYLAT		=OFF;						//TO CONTROL THE GAS SOLENOID VALVE
		//	HFRELAYLAT		=OFF;						//TO CONTROL THE HF RELAY
			ARCONLAT		=OFF;						//ARCON CONTROL SIGNAL INPUT TO PWM CARD
			pulsecyclestrt	=0;//OFF;
			cout_100us		=0;
			//dispupdatef	=0;
			softstartcnt	=0;
			softstartf		=0;
			scaled_val1		=0;
			weldonstartbcnt	=0;
			weldonstartfcnt	=0;
			setrefparaf		=0;
			setrefparaf_crater=0;
			pulsestrtf		=0;
			Aweldon_detectf =0;
			count_weldonms  =0;
			Aweldonf        =0;
			firstpulsef     =0;
			//INCHTESTIPIO=0;
			//INCHTESTIPLAT=0;
			weldonf=0;
			INTCON2bits.INT2EP=1;      //1 Negative EDGE
			startbmeasuref=0;
			endbmeasuref=0;
			pulseweldonf=0;
		 
		}
		else if(weldcyclestrt==1 )//&& torchonstatus=='T' && weld_para_latch==1) //else if(torchonstatus=='T') 
		{
			weldingonf=1;
			
			
			if( (encod3!='$' || encod2 !='$') )
			  {
					updatepccparameter(encod3,encod2);  	//@user input current and voltage	
					encod3='$';
					encod2='$';
					 if(ppmigsetvoltage!=para.pmigmode.setvoltage) 
					{
					
						lcd_disp_hex_dec(para.pmigmode.setvoltage);
						voltupdate();
											
						cWfVChangefg = 0;
						transmit2f=1;
						
					}
					ppmigsetvoltage =para.migmode.setvoltage; 
					
					if( (ppmigsetwirespeed!=para.pmigmode.setwspeed) || (keychange1==1)) // CurrentSet Parameter
					{
					
				
						wfchangef=1;
										
						pstowfstr.setwspeed=para.pmigmode.setwspeed;
										
						ftemp=para.pmigmode.setwspeed;
						fwirespeed=ftemp*0.101;
						
						wirespeed=fwirespeed;
						current1=iPSetCurrent[wirespeed];//newfindmatindex4(wirespeed);
						current2=iPSetCurrent[wirespeed+1];//newfindmatindex4((wirespeed+1));
						dispautocurrent=current1+((fwirespeed-wirespeed)*(current2-current1));
						pstowfstr.Lo_setcurrent=dispautocurrent;
						pstowfstr.Hi_setcurrent=dispautocurrent >> 8;
						
						lcd_disp_hex_dec(dispautocurrent);
						currupdate();
						
						
						
					}	
					ppmigsetwirespeed=para.pmigmode.setwspeed	;
					
					 
		
		
			  }
			
			if(cForcefullyOFFOCVfg == 0)
			{
				SHDNLAT=1;			//OCV OFF
			}	
		
			
			if(setrefparaf==0)
			{
				Load_Initial_Constant(para.pmigmode.setwspeed);
				setrefparaf=1;
			}
			else if(setrefparaf_crater==1)
			{
			Load_Initial_Constant(para.pmigmode.craterspeed);
			pstowfstr.crater_speed=para.pmigmode.craterspeed;
//			para.pmigmode.cratervoltage=parcbasevtg;  // commented on 24072020 by sachin for testing	
			setrefparaf_crater=2;						
			}
			
			
			dispupdatef=1;
			weldmodeoff=0;
			//openloopf=0;
			pulsecyclestrt		=1;//0;//ON;
		    //pulsestrtf		=0;
			TypeDP.DPGROUP[0]	=0x00;
			Typedp.digitdp5		=1;
			TypeU.LEDGROUP[0]	=0x00;
			Type.current		=1;
			Type.voltage		=1;
			
			
			disp_hex_dec_volt(VOLTAGE);//PID_bdaccount);//VOLTAGE);	
			
			disp_hex_dec_curr(CURRENT);//sumdaccount);//CURRENT);
 
		}
	}//setup==0
	else if(setupmode==11)//@disabled this setting
	{
		pulsecyclestrt=0;
	//	GASRELAYLAT	=OFF;							//TO CONTROL THE GAS SOLENOID VALVE
	//	HFRELAYLAT		=OFF;						//TO CONTROL THE HF RELAY
		ARCONLAT		=OFF;						//ARCON CONTROL SIGNAL INPUT TO PWM CARD
	//	OC2RS=0;
	/*	if(SPI2STATbits.SPITBF==0)
		{
			DACCSLAT	=0;
			SPI2BUF		=28672+0;     //850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
		}	
	*/	
		if(setpeakf==0 && setstepf==0 && setbasef==0 && setfreqf==0 && setptimef==0 &&	setstimef==0			 
		   			   && setparaBkpf==0 && setparaBkif==0 && setparaBkdf==0 && setparaPkpf==0 && setparaPkif==0 && setparaPkdf==0)
		{
				diswin1[0]='S';
				diswin1[1]='E';
				diswin1[2]='T';
				diswin2[0]='M';
				diswin2[1]='O';
				diswin2[2]='D';
		}
        else if(setpeakf==1)
		{
			diswin1[0]='P';
			diswin1[1]='I';
			diswin1[2]='K';
			if(encod2 !='$')
			{
				peakamp=updatedata(peakamp,0,500,encod2 );
				encod2='$';
			}
			disp_hex_dec_volt(peakamp);
		}
		else if(setstepf==1)
		{
			diswin1[0]='S';
			diswin1[1]='T';
			diswin1[2]='P';
			if(encod2 !='$')
			{
				stepamp=updatedata(stepamp,0,500,encod2 );
				encod2='$';
			}
			disp_hex_dec_volt(stepamp);
			maxbaseamp=stepamp;
		}
		else if(setbasef==1)
		{
			diswin1[0]='B';
			diswin1[1]='A';
			diswin1[2]='S';
			if(encod2 !='$')
			{
				baseamp=updatedata(baseamp,0,500,encod2 );
				encod2='$';
			}
			disp_hex_dec_volt(baseamp);
			minbaseamp=baseamp;
		}
		else if(setfreqf==1)
		{
			diswin1[0]='F';
			diswin1[1]='R';
			diswin1[2]='Q';
			if(encod2!='$')
			{
				//pulsefreq=updatedata(pulsefreq,0,400,encod2 );
				twinpulsefreq=updatedata(twinpulsefreq,1,10,encod2 );
				encod2='$';
			}
			disp_hex_dec_volt(twinpulsefreq);//pulsefreq);
			twinpulseperiod=1000/twinpulsefreq;   //ms
		}
		else if(setptimef==1)
		{
			diswin1[0]='D';
			diswin1[1]='U';
			diswin1[2]='T';
			if(encod2!='$')
			{
				//peaktime=updatedata(peaktime,0,200,encod2 );
				twinpulseduty=updatedata(twinpulseduty,20,80,encod2 );
				encod2='$';
			}
			disp_hex_dec_volt(twinpulseduty);
			twinpulseonperiod=twinpulseperiod*twinpulseduty/100.0;
			twinpulseoffperiod=twinpulseperiod-twinpulseonperiod;
		}
		else if(setstimef==1)
		{
			diswin1[0]='W';
			diswin1[1]='F';
			diswin1[2]='R';
			if(encod2 !='$')
			{
				//steptime=updatedata(steptime,0,200,encod2 );
				twinpulseratio=updatedata(twinpulseratio,10,50,encod2 );
				encod2='$';
			}
			disp_hex_dec_volt(twinpulseratio);
		}
		//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
		else if(setparaBkpf==1) //kp replaced by kp2
		{
			diswin1[0]='F';//B';
			diswin1[1]='K';
			diswin1[2]='P';
			if(encod2 !='$')
			{
				pidParams2.Kp2=updatedata(pidParams2.Kp2,0,200,encod2);//paraA
				encod2='$';
			}
			disp_hex_dec_volt(pidParams2.Kp2);//minbasetime);//paraA);
		}
		else if(setparaBkif==1)
		{
			diswin1[0]='F';//B';
			diswin1[1]='K';
			diswin1[2]='I';
			if(encod2 !='$')
			{
				pidParams2.Ki2=updatedata(pidParams2.Ki2,0,200,encod2 );
				encod2='$';
			}
			disp_hex_dec_volt(pidParams2.Ki2);//paraB);//maxbasetime);//paraB);
		}
		else if(setparaBkdf==1)
		{
			diswin1[0]='F';//'B';
			diswin1[1]='K';
			diswin1[2]='D';
			if(encod2 !='$')
			{
				pidParams2.Kd2=updatedata(pidParams2.Kd2,0,200,encod2 );
				encod2='$';
			}
			disp_hex_dec_volt(pidParams2.Kd2);
		}
		//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
		else if(setparaPkpf==1)
		{
			diswin1[0]='B';
			diswin1[1]='K';
			diswin1[2]='P';
			if(encod2 !='$')
			{
				pidParams.Kp=updatedata(pidParams.Kp,0,500,encod2 );//paraA
				encod2='$';
			}
			disp_hex_dec_volt(pidParams.Kp);//minbasetime);//paraA);
			//intkp=pidParams1.Kp1;
		}
		else if(setparaPkif==1)
		{
			diswin1[0]='B';
			diswin1[1]='K';
			diswin1[2]='I';
			if(encod2 !='$')
			{
				pidParams.Ki=updatedata(pidParams.Ki,0,100,encod2 );
				encod2='$';
			}
			disp_hex_dec_volt(pidParams.Ki);//paraB);//maxbasetime);//paraB);
			//intki=pidParams1.Ki1;
		}
		else if(setparaPkdf==1)
		{
				diswin1[0]='B';//P';
				diswin1[1]='K';
				diswin1[2]='D';
				if(encod2 !='$')
				{
					pidParams.Kd=updatedata(pidParams.Kd,0,500,encod2 );
					encod2='$';
				}
				disp_hex_dec_volt(pidParams.Kd);//paraC);//outputpulsebase);//refpulsebase);//paraC);
				//intkd=pidParams1.Kd1;
				//pmig_para_init();   			 		
				dispupdatef=1;
			}
	}

}
void no_frequency_update_pid()//15.02.2016
{
	pulsebase=pulsebase;
}


void load_pulse_parameter()
{
   			 
	for(piii=0;piii<10;piii++)
	pulsepararr[piii]=iPulseParameter[piii];
	pulsetmfactor= iPulsetmfactor;//0.25;
	pulsecurfactor= iPulsecurfactor;//0.25;
	ARCLFACTOR=	0.025;		
//---------------------------------------------------------------------------------------
// For Al Material
	if(cSoftwireDetfg == 1)
	{ 	
		cAlDia = ALDIA;	 // as per dia selected;
		iIndex = (para.pmigmode.setwspeed / 10);
		if(iIndex >= 12)
		{
			iIndex = 12;
		}		
		iSubIndex = para.pmigmode.setwspeed % 10;
		
	 	if(iSubIndex != 0)
		{
			if(iALUParaPeakCurr[cAlDia][iIndex + 1] >= iALUParaPeakCurr[cAlDia][iIndex ])
			{
				iStepPeakCurr = (iALUParaPeakCurr[cAlDia][iIndex + 1] - iALUParaPeakCurr[cAlDia][iIndex]);		
			}
			else
			{
				iStepPeakCurr = (iALUParaPeakCurr[cAlDia][iIndex] - iALUParaPeakCurr[cAlDia][iIndex+1]);		
			}
			iStepPeakCurr = (iStepPeakCurr / 10);			
			iStepPeakCurr = (iStepPeakCurr * iSubIndex);
	
			if(iALUParaBaseCurr[cAlDia][iIndex + 1] >= iALUParaBaseCurr[cAlDia][iIndex ])
			{
				iStepBaseCurr = (iALUParaBaseCurr[cAlDia][iIndex + 1] - iALUParaBaseCurr[cAlDia][iIndex]);		
			}
			else
			{
				iStepBaseCurr = (iALUParaBaseCurr[cAlDia][iIndex] - iALUParaBaseCurr[cAlDia][iIndex+1]);		
			}
	
			iStepBaseCurr = (iStepBaseCurr / 10);			
			iStepBaseCurr = (iStepBaseCurr * iSubIndex);		
	
			if(iALUParaPulseTm[cAlDia][iIndex + 1] >= iALUParaPulseTm[cAlDia][iIndex ])
			{
				iStepPulseTime = (iALUParaPulseTm[cAlDia][iIndex + 1] - iALUParaPulseTm[cAlDia][iIndex]);		
			}
			else
			{
				iStepPulseTime = (iALUParaPulseTm[cAlDia][iIndex] - iALUParaPulseTm[cAlDia][iIndex+1]);		
			}
			iStepPulseTime = (iStepPulseTime / 10);			
			iStepPulseTime = (iStepPulseTime * iSubIndex);		
		}
		else
		{
			iStepPeakCurr = iStepBaseCurr = iStepPulseTime =  0;
		}	 
		
	 	if(para.pmigmode.setwspeed <= 120)
	 	{	
		 	peakamp			= iALUParaPeakCurr[cAlDia][iIndex] + iStepPeakCurr - 15;
			stepamp			= iALUParaBaseCurr[cAlDia][iIndex] + iStepBaseCurr + 20;	
			baseamp			= iALUParaBaseCurr[cAlDia][iIndex] + iStepBaseCurr;
			peaktime		= iALUParaPulseTm[cAlDia][iIndex] + iStepPulseTime;//pulsepararr[5];				
	 	}
	 	else
	 	{
		 	peakamp			= iALUParaPeakCurr[cAlDia][iIndex] + iStepPeakCurr -15 ;
			stepamp			= iALUParaBaseCurr[cAlDia][iIndex] + iStepBaseCurr + 20;	
			baseamp			= iALUParaBaseCurr[cAlDia][iIndex] + iStepBaseCurr;
			peaktime		= iALUParaPulseTm[cAlDia][iIndex] + iStepPulseTime;//pulsepararr[5];		 	
	 	}  	 	
		if(baseamp <= 20)
		{
			baseamp = 20;
		}
		if(stepamp < 20)
		{
			stepamp = 20;
		}
//		baseamp = save_location;	
	//---------------------------------------------------------
	    /*iStepAmpTime = pulserisetime / 20;
	    if(iStepAmpTime <= 0)
	    {
	    	iStepAmpTime = 1;
	    }
	    iStepRiseAmp = peakamp - baseamp;
	    iStepRiseAmp = iStepRiseAmp / iStepAmpTime; */
		//newpeakamp=refpeakamp+(para.pmigmode.setwspeed/5.0);
	}
	else
	{
		peakamp			=pulsepararr[0];
	    stepamp			=pulsepararr[1];
		baseamp			=pulsepararr[2];
		pulserisetime	=pulsepararr[3];
		startpulsetime	=pulsepararr[4];
		peaktime		=pulsepararr[5];
		
		
	    pulsefalltime	=pulsepararr[6];
	    steptime		=pulsepararr[7];
	    target_bvtg		=pulsepararr[9];
	    
		refpeakamp		=peakamp;
	    refpeaktm		=peaktime;
	    refstepamp		=stepamp;
	    
	    pdaccount	 	=(peakamp*CCSLOPENEW)-CCOFFSETNEW;
		sdaccount	 	=(stepamp*CCSLOPENEW)-CCOFFSETNEW;
		bdaccount	 	=(baseamp*CCSLOPENEW)-CCOFFSETNEW;
     
	} 
	
	


	if(peakamp > 500)
	{
		iPeakCurrLimit = 500 * CCSLOPENEW - CCOFFSETNEW ;	
	}else
	{
		
		iPeakCurrLimit = (peakamp+100) * CCSLOPENEW - CCOFFSETNEW ;	
	}	
	
	total_pulse_tm=pulserisetime+startpulsetime+peaktime+pulsefalltime; //decaytime=100;	
	/*else
	{
	 	peakamp			= save_location * 10;//pulsepararr[0];
		stepamp			=pulsepararr[1];
		baseamp			=pulsepararr[2];
		pulserisetime	=pulsepararr[3];
		startpulsetime	=pulsepararr[4];
		peaktime		= 10 + Recall_location ;//pulsepararr[5];
	    
	}

	pulserisetime	= pulsepararr[3];
	startpulsetime	=pulsepararr[4];

	pulsefalltime	=pulsepararr[6];
    steptime		=pulsepararr[7];
    target_bvtg		=pulsepararr[9];

	refpeakamp		=peakamp;
    refpeaktm		=peaktime;
    refstepamp		=stepamp;
    
    pdaccount	 	=(peakamp*CCSLOPENEW)-CCOFFSETNEW;
	sdaccount	 	=(stepamp*CCSLOPENEW)-CCOFFSETNEW;
	bdaccount	 	=(baseamp*CCSLOPENEW)-CCOFFSETNEW;

	if(peakamp > 500)
	{
		iPeakCurrLimit = 500 * CCSLOPENEW - CCOFFSETNEW ;	
	}else
	{
		iPeakCurrLimit = (peakamp+100) * CCSLOPENEW - CCOFFSETNEW ;	
	}	
	
	total_pulse_tm=pulserisetime+startpulsetime+peaktime+pulsefalltime;*/ //decaytime=100;		

	if(iPSetCurrent[0]>20)
	{
	//	lcd_disp_hex_dec(peakamp);    //to check the proper peak current MAHESH PHARANDE
		peakampupdate();
	}
	else
	{
		noprogramupdate();	
	}				

}
//35307302085

void Load_Initial_Constant(unsigned int pulsesetws)
{

	
	
		switch(cDisplayDia)
		{
			case 0:
				weldwiredia=0.8;				
				break;
			case 1:
				weldwiredia=1.0;				
				break;
			case 2:
				weldwiredia=1.2;				
				break;
			case 3:
				weldwiredia=1.60;				
				break;											
		}	
		
		pulsetmfactor=iPulsetmfactor;//0;//0.25; //fix 800usec
		pulsetmfactor = pulsetmfactor/100;
		pulsecurfactor=iPulsecurfactor;//0.50;//0;//0.50;//0.70;//0.90; // ref pulse current 410A
		pulsecurfactor = pulsecurfactor/100;
		
		//target_bvtg=280.0;
       	peakamp=refpeakamp+(pulsesetws*pulsecurfactor);//0.3)
		peaktime=refpeaktm+(pulsesetws*pulsetmfactor);//refpulsebase=newbasetime;
	
		//pulsefreq=(para.pmigmode.setwspeed*10.0*1.2)/6.0;//100*10*1.2/6=200 ACTUAL FREQ =
		sf_outputmax = (iSfOutputMax * 100);//32000;//prev:19200,changed at indina grtng:32000;//150*128;//25600;
	    constpeakamp=peakamp;
	    
	    if(0)//program_number == 6)
	    {
			pulsefreqfactor = save_location;//iPulseFreqFact); 
		}
		else
		{
			pulsefreqfactor = iPulseFreqFact; 	
		}	 
		    
	    
	    pulsefreqfactor = pulsefreqfactor/10;
	    // // For Al material--------------------------------------------
	
		if(cSoftwireDetfg == 1)
		{	
			cAlDia = ALDIA;
			iIndex = para.pmigmode.setwspeed / 10;
			iSubIndex = para.pmigmode.setwspeed % 10;
			
			if(iSubIndex != 0)
			{
				iStepFreq = (iALUParaFreq[cAlDia][iIndex + 1] - iALUParaFreq[cAlDia][iIndex]);
				iStepFreq = (iStepFreq / 10);			
				iStepFreq = (iStepFreq * iSubIndex);
			}
			else
			{
				iStepFreq = 0;
			}	
			
			
			if(para.pmigmode.setwspeed <= 120)
			{
				pulsefreq = iALUParaFreq[cAlDia][iIndex] + iStepFreq;
			}
			else
			{
				pulsefreq=(pulsesetws*10.0*weldwiredia)/pulsefreqfactor;		
			}
				
		 
											  
			  
		}
		else
		{
			pulsefreq=(pulsesetws*10.0*weldwiredia)/pulsefreqfactor;
		}	    
	
	
	 
		//pulsefreq=(pulsesetws*10.0*weldwiredia)/pulsefreqfactor;//prev by asn:10.0*weldwiredia)/12.0;  prev by mjp:100*10*1.2/6.0=200 ACTUAL FREQ =
//	    pstowfstr.pulse_freq=para.twinpulsefreq;	//???? commented by sachin on 16/12/2020
	    	
//		rel_wirespeed=twinpulseratio * (0.5);  // commented on 01102020 by sachin 		
//------------------------------------------------------------------------------------------------	    
//twin pulse calculation start
//------------------------------------------------------------------------------------------------
		if(twinpulseratio >= 100)
		{
			rel_wirespeed = ((twinpulseratio - 100) * para.pmigmode.setwspeed) / 100;
			pstowfstr.pulse_freq = '+';	
			
			iTwinSetVolt =  rel_wirespeed;//Tbasevoltage - iTwinSetVolt;		
			
			iCalHiFreq = ((para.pmigmode.setwspeed + rel_wirespeed)*10.0*weldwiredia)/pulsefreqfactor;	
			iCalHiFreq = iCalHiFreq - (iCalHiFreq * Recall_location) / 100;						
		}
		else
		{
			rel_wirespeed = ((100 - twinpulseratio) * para.pmigmode.setwspeed) / 100;
			pstowfstr.pulse_freq = '-';	
			
			iTwinSetVolt =  rel_wirespeed;
						
			iCalHiFreq = ((para.pmigmode.setwspeed - rel_wirespeed)*10.0*weldwiredia)/pulsefreqfactor;	
			iCalHiFreq = iCalHiFreq - (iCalHiFreq * Recall_location) / 100;	
								
		}		
		if(rel_wirespeed >= 200)
		{
			rel_wirespeed = 200;
		}		
		pstowfstr.rel_wirespeed=rel_wirespeed;
//twinpulseduty
// here 	iTwinwirespeed is used for just calculation purpose only	    		
/*
		iTwinwirespeed = para.pmigmode.setwspeed - rel_wirespeed;	
		if(iTwinwirespeed <= 20)
		{
			iTwinwirespeed = 20;
		}	
*/	
		iCalLowFreq = (para.pmigmode.setwspeed*10.0*weldwiredia)/pulsefreqfactor; 
		iCalLowFreq = iCalLowFreq - (iCalLowFreq * save_location) / 100;		
/*
		ftemp=iTwinwirespeed;
		fwirespeed=ftemp*0.101;
		wirespeed=fwirespeed;
		iTwinSetVolt=newfindmatindex7(wirespeed);
		iTwinSetVolt2=newfindmatindex7((wirespeed+1));
		iTwinSetVolt=iTwinSetVolt+((fwirespeed-wirespeed)*(iTwinSetVolt2-iTwinSetVolt));
		iTwinSetVolt =  Tbasevoltage - iTwinSetVolt;		
*/										
//-------------------------------------------------------------------------------------------------
//twinpulseratio ;//* save_location / 10;  

	    Hi_pulsefreq=iCalHiFreq;//ALEN_pulsefreq+ (iCalFreq * 10) / 10;
		
/*
		if(ALEN_pulsefreq>twinpulseratio) // commented by sachin 05102020
		Lo_pulsefreq= ALEN_pulsefreq- (iCalFreq * Recall_location)/10;
		else
		Lo_pulsefreq=MIN_FREQ;
*/		
		Lo_pulsefreq= iCalLowFreq;
		min_freq=Lo_pulsefreq;
		max_freq=Hi_pulsefreq;
		
		step_freq=(max_freq-min_freq)/5;
//twin pulse calculation end

//		cTestfg = 1;  
//		iTest = Hi_pulsefreq + Lo_pulsefreq ;//rel_wirespeed;   
	  	
	    if(peakamp>=600)//500)
		peakamp=600;//500;
		
		uppeakamp=peakamp+50;//disabled for sine wave reference.
		
		if(uppeakamp>600)//500)
		uppeakamp=600;//500;
	    //pulserisetime=105;//65;//65+15=80;// modified by mahesh for sinewave reference
		
		/*For Twin Pulse Srart here*/
		if(para.pulseweldmode==1) 
		{
	/*
		Hi_pulsefreq=pulsefreq+(iCalFreq * 28) / 10;//twinpulseratio ;// * save_location / 10;//Recall_location
		
		if(pulsefreq>twinpulseratio)
		Lo_pulsefreq=pulsefreq-(iCalFreq * Recall_location) / 10;//twinpulseratio ;// * Recall_location / 10;	
		else
		Lo_pulsefreq=20;
		
		if(Lo_pulsefreq<=20)
		Lo_pulsefreq=20;
	*/
		twn_rmp_down_offst_tm= twinpulseperiod/12; //For 8% 8/100==> 1/12 
		base_ramp_down_flag=0;
		
		twinpulsecnt=0;
		psstatus.Hi_speedon=0;
	//	pulsefreq=Lo_pulsefreq;
		base_amp_twin_pulse=min_base_amp;
		}
		/*For Twin Pulse End here*/
		
		
		OPEN_pulsetm	 	=peaktime>>1;///5;//20;	//20*50usec=1000usec;
		OPEN_steptm		 	=steptime>>1;///5;//40;	//10*50usec=500usec
		OPEN_basetm		 	=basetime>>1;///5;//50;	//50*50usec=2500usec
		OPEN_pulserisetm 	=pulserisetime>>1;///5;//6;  	//6*50usec=300usec 
		OPEN_pulsefalltm 	=pulsefalltime>>1;///5;//20;	//20*50usec=1000usec;
		OPEN_startpulsetm	=startpulsetime>>1;///5;//3;  	//3*50usec=150usec
		OPEN_uppdaccount  	=(uppeakamp*CCSLOPENEW)-CCOFFSETNEW;
		OPEN_pdaccount	 	=(peakamp*CCSLOPENEW)  -CCOFFSETNEW;
		OPEN_sdaccount	 	=(stepamp*CCSLOPENEW)  -CCOFFSETNEW;
		//OPEN_bdaccount	 	=CCOFFSET+(baseamp*CCSLOPE);
		OPEN_bdaccount	 	=(pidminbaseamp*CCSLOPENEW)-CCOFFSETNEW;
		OPEN_newupstep		=(OPEN_uppdaccount-OPEN_bdaccount)/OPEN_pulserisetm;
		OPEN_newdownstep	=(OPEN_pdaccount-OPEN_sdaccount)/OPEN_pulsefalltm;
		//constpeakamp=450;
		
		if(constpeakamp>500)
		constpeakamp=500;
		const_arc_strike_pdaccount=(constpeakamp*CCSLOPENEW)  -CCOFFSETNEW;;//CCOFFSET+(constpeakamp*CCSLOPE);

		
	}	
//void OPEN_pulse_para(unsigned int pulsesetws)
//{
//	if(program_number ==02)//   //MS 0.8 ARCO2
//	{
//		baseamp=(pulsesetws*0.30);//0.50);
//		if(baseamp<20)
//		baseamp=20;
//		
//		pidParams1.Ki1=pulsesetws*0.01;//0.02 for 1.0. 1.2 mm;
//		minoutputfreq=5;//  15 for 1.0 ;//20 for 1.2;
//		addrippleamp=0.5;
//		pulsetmfactor=0.20;
//		pulsecurfactor=0.25;
//		pulsefreq=20.0+(pulsesetws*1.30);//20+(A31*13)
//		constpeakamp=400;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//	}	
//	else if(program_number ==06)//   //MS 1.0 ARCO2
//	{
//		baseamp=(pulsesetws*0.50);
//		if(baseamp<20)
//		baseamp=20;
//		
//		pidParams1.Ki1=pulsesetws*0.02;// for 1.0. 1.2 mm;
//		minoutputfreq=5;//15;// for 1.0 ;//20 for 1.2;
//		addrippleamp=1.0;
//		pulsetmfactor=0.25;
//		pulsecurfactor=0.25;
//		pulsefreq=10.0+(pulsesetws*1.60);//10+(A31*10*1.6)
//		constpeakamp=460;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//	}
//   	else if(program_number ==13)//   //MS 1.2 ARCO2
//	{
//		
//		
//		/*baseamp=(pulsesetws*0.50);
//		if(baseamp<20)
//		baseamp=20;
//		pidParams1.Ki1=pulsesetws*0.02;// for 1.0. 1.2 mm;
//		minoutputfreq=5;//20;//  15 for 1.0 ;//20 for 1.2;
//		addrippleamp=1.5;
//		pulsetmfactor=0.25;
//		pulsecurfactor=0.25; //0.5
//	    pulsefreq=30.0+(pulsesetws*1.70);//
//		constpeakamp=510;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//		*/
//		pulsetmfactor=0.25; //fix 800usec
//		pulsecurfactor=0.25; // ref pulse current 410A
//		Totalpulsepower=65000.0;//650.0;
//		Steppowerconstant=10000.0;//100.0;
//		peakamp=refpeakamp+(pulsesetws*pulsecurfactor);//0.3)
//		peaktime=refpeaktm+(pulsesetws*pulsetmfactor);//refpulsebase=newbasetime;
//		Peakpowerconstant=peakamp*peaktime;
//		Basepowerconstant=Totalpulsepower-(Peakpowerconstant+Steppowerconstant);
//		pidminbaseamp=para.pmigmode.setwspeed*0.6;
//		pidmaxbaseamp=para.pmigmode.setwspeed*1.4;
//		
//	
//		
//		
//		OPEN_pulsetm	 	=peaktime/5;//20;	//20*50usec=1000usec;
//		OPEN_steptm		 	=steptime/5;//40;	//10*50usec=500usec
//		OPEN_basetm		 	=basetime/5;//50;	//50*50usec=2500usec
//		OPEN_pulserisetm 	=pulserisetime/5;//6;  	//6*50usec=300usec 
//		OPEN_pulsefalltm 	=pulsefalltime/5;//20;	//20*50usec=1000usec;
//		OPEN_startpulsetm	=startpulsetime/5;//3;  	//3*50usec=150usec
//		OPEN_uppdaccount  	=CCOFFSET+(uppeakamp*CCSLOPE);
//		OPEN_pdaccount	 	=CCOFFSET+(peakamp*CCSLOPE);
//		OPEN_sdaccount	 	=CCOFFSET+(stepamp*CCSLOPE);
//		OPEN_bdaccount	 	=CCOFFSET+(baseamp*CCSLOPE);
//		OPEN_newupstep		=(OPEN_uppdaccount-OPEN_bdaccount)/OPEN_pulserisetm;
//		OPEN_newdownstep	=(OPEN_pdaccount-OPEN_sdaccount)/OPEN_pulsefalltm;
//		
//		
//		
//		
//	}
//	else if(program_number ==28)//   //MS 1.6 ARCO2
//	{
//		baseamp=(pulsesetws*1.0);//50);
//		if(baseamp<20)
//		baseamp=20;
//		
//		pidParams1.Ki1=pulsesetws*0.02;//4;// for 1.0. 1.2 mm;
//		minoutputfreq=20;//  15 for 1.0 ;//20 for 1.2;
//		addrippleamp=2.0;		//20
//		pulsetmfactor=0.25;
//		pulsecurfactor=0.5;
//		pulsefreq=25.0+(pulsesetws*1.90);//25+A3*19
//		constpeakamp=600;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//	}
//	else if((program_number ==3) || (program_number ==4))//   //SS 0.8 ARO2
//	{
//		baseamp=(pulsesetws*0.30);//0.50);
//		if(baseamp<15)
//		baseamp=15;
//		
//		pidParams1.Ki1=pulsesetws*0.01;//0.02 for 1.0. 1.2 mm;
//		minoutputfreq=5;//  15 for 1.0 ;//20 for 1.2;
//		addrippleamp=0.5;
//		pulsetmfactor=0.20;
//		pulsecurfactor=0.25;
//		pulsefreq=20.0+(pulsesetws*1.20);//20+(A31*13)
//		constpeakamp=350;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//	}	
//	else if((program_number ==7) || (program_number ==8))//   //SS 1.0 ARO2
//	{
//		baseamp=(pulsesetws*0.50);
//		if(baseamp<20)
//		baseamp=20;
//		
//		pidParams1.Ki1=pulsesetws*0.02;// for 1.0. 1.2 mm;
//		minoutputfreq=10;//15;// for 1.0 ;//20 for 1.2;
//		addrippleamp=1.0;
//		pulsetmfactor=0.25;
//		pulsecurfactor=0.25;
//		pulsefreq=20.0+(pulsesetws*1.60);//10+(A31*10*1.6)
//		constpeakamp=360;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//	}
//	else if((program_number ==18)|| (program_number ==19))//   //SS 1.2 ARO2
//	{
//		baseamp=(pulsesetws*0.5);//50);
//		if(baseamp<20)
//		baseamp=20;
//		pidParams1.Ki1=pulsesetws*0.02;//4;// for 1.0. 1.2 mm;
//		minoutputfreq=20;//  15 for 1.0 ;//20 for 1.2;
//		addrippleamp=2.0;		//20
//		pulsetmfactor=0.25;
//		pulsecurfactor=0.5;
//		pulsefreq=20.0+(pulsesetws*1.70);//=20+(A5*17)
//		constpeakamp=450;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//	}
//	
//	else if((program_number ==33) || (program_number ==34))//   //SS 1.6 ARo2
//	{
//		baseamp=(pulsesetws*1.0);//50);
//		if(baseamp<20)
//		baseamp=20;
//		
//		pidParams1.Ki1=pulsesetws*0.02;//4;// for 1.0. 1.2 mm;
//		minoutputfreq=20;//  15 for 1.0 ;//20 for 1.2;
//		addrippleamp=2.0;		//20
//		pulsetmfactor=0.25;
//		pulsecurfactor=0.5;
//		pulsefreq=25.0+(pulsesetws*1.90);//25+A3*19
//		constpeakamp=600;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//	}
//	
//	else if(program_number ==20)//   //ALU+SI 1.2 AR
//	{
//		//baseamp=(pulsesetws*0.5);//50); //48+(10.3*A2)
//		//baseamp=48.0+(1.3*pulsesetws);
//		stepamp=baseamp;
//		
//		//DISABLED FOR EDIT PEAK CURRENT
//		//pidParams1.Ki1=pulsesetws*0.02;//4;// for 1.0. 1.2 mm;
//		minoutputfreq=20;//  15 for 1.0 ;//20 for 1.2;
//		addrippleamp=0;//2.0;		//20
//		pulsetmfactor=0.0;//0.25;
//		pulsecurfactor=1.8;//0.5;
//		//pulsefreq=20.0+(pulsesetws*1.20);//70);//=20+(A5*17)
//		//pulsefreq=40.0+(pulsesetws*1.90);//70);//=20+(A5*17) // 40+(19*A2) 30+(A5*17.4)
//		pulsefreq=30.0+(pulsesetws*1.74);
//		constpeakamp=410;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//	}
//
//
//	else if(program_number ==21)//   //ALU+MG 1.2 AR
//	{
//		//baseamp=(pulsesetws*0.5);//50); //48+(10.3*A2)
//		//baseamp=48.0+(1.3*pulsesetws);
//		stepamp=baseamp;
//		//DISABLED FOR EDIT PEAK CURRENT
//		//pidParams1.Ki1=pulsesetws*0.02;//4;// for 1.0. 1.2 mm;
//		minoutputfreq=20;//  15 for 1.0 ;//20 for 1.2;
//		addrippleamp=1.0;		//10
//		pulsetmfactor=0.0;//0.25;
//		pulsecurfactor=0.61;//1.8;//0.5;
//		//pulsefreq=20.0+(pulsesetws*1.20);//70);//=20+(A5*17)
//		//pulsefreq=40.0+(pulsesetws*1.90);//70);//=20+(A5*17) // 40+(19*A2) 30+(A5*17.4)
//		//pulsefreq=3.4+(pulsesetws*1.916);//30.0+(pulsesetws*1.74);
//		pulsefreq=22.0+(pulsesetws*1.6);//30.0+(pulsesetws*1.74);
//		constpeakamp=450;//600;//450;//410;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//	}
//	else if((program_number ==35) || (program_number ==36))//   //ALU 1.6 AR
//	{
//		//baseamp=(pulsesetws*1.0);//50);
//		//if(baseamp<20)
//		//baseamp=20;
//		stepamp=baseamp;
//		
//		//pidParams1.Ki1=pulsesetws*0.02;//4;// for 1.0. 1.2 mm;
//		minoutputfreq=20;//  15 for 1.0 ;//20 for 1.2;
//		addrippleamp=0;//2.0;		//20
//		pulsetmfactor=0;//0.25;
//		pulsecurfactor=1.62;//0.5;
//		pulsefreq=(pulsesetws*4.314)-30.54;//43.14*A2-30.54
//		constpeakamp=500;
//		constpdaccount=CCOFFSET+(constpeakamp*CCSLOPE);
//	}
//
//	
//	
//	
//	
//	
//	//@
//    //pulsefreq=((pulsesetws*100.0)/(1.2*60.0));  //for 1.2 wire
//	//pulsefreq=((pulsesetws*100.0)/(1.60*60.0));	  //for 1.0 wire
//	//pulsetmfactor=0.25;
//	//pulsecurfactor=0.25;
//	//pulsefreq=30.0+(pulsesetws*1.70);//
//	
//	
//	if(pulsefreq >=300.0)
//	pulsefreq=300.0;
//	
//	
//	//DISABLED FOR EDIT PEAK CURRENT
//	peaktime=refpeaktm+(pulsesetws*pulsetmfactor);//refpulsebase=newbasetime;
//
//	tpulsetime=pulserisetime+peaktime+steptime+pulsefalltime;
//	if(pulsefreq>0.0)
//	 	pulseduty=100000.0/pulsefreq;
//	else
//	 	pulseduty=10000;
//	 	
//	if(pulseduty >=tpulsetime)
//	{
//		basetime=pulseduty-tpulsetime;
//	 	steptime=steptime;
//	}
//	else
//	{
//		basetime=1;
//		pulseontime=(pulserisetime+peaktime+pulsefalltime);
//		if(pulseduty>=pulseontime)
//			steptime=(pulseduty-pulseontime);//-peaktime;
//		else
//			steptime=30;
//		
//		if(steptime<=30)
//		   steptime=30;
//		//disptemp=newsteptime;
//	}
//	//DISABLED FOR EDIT PEAK CURRENT
//	peakamp=refpeakamp+(pulsesetws*pulsecurfactor);//0.3);
//	
//	//for aluminium 1.2 wire
//	//peakamp=refpeakamp+(pulsesetws*1.8);//pulsecurfactor);//0.3);  //132+(18*A2)
//	
//	
//	if(peakamp>=600)
//	peakamp=600;
//	uppeakamp=peakamp+100;//
//		
//	if(uppeakamp>600)
//	uppeakamp=600;
//	
//	
//   	OPEN_pulsetm	 	=peaktime/5;//20;	//20*50usec=1000usec;
//	OPEN_steptm		 	=steptime/5;//40;	//10*50usec=500usec
//	OPEN_basetm		 	=basetime/5;//50;	//50*50usec=2500usec
//	OPEN_pulserisetm 	=pulserisetime/5;//6;  	//6*50usec=300usec 
//	OPEN_pulsefalltm 	=pulsefalltime/5;//20;	//20*50usec=1000usec;
//	OPEN_startpulsetm	=startpulsetime/5;//3;  	//3*50usec=150usec
//	OPEN_uppdaccount  	=CCOFFSET+(uppeakamp*CCSLOPE);
//	OPEN_pdaccount	 	=CCOFFSET+(peakamp*CCSLOPE);
//	OPEN_sdaccount	 	=CCOFFSET+(stepamp*CCSLOPE);
//	OPEN_bdaccount	 	=CCOFFSET+(baseamp*CCSLOPE);
//	OPEN_newupstep		=(OPEN_uppdaccount-OPEN_bdaccount)/OPEN_pulserisetm;
//	OPEN_newdownstep	=(OPEN_pdaccount-OPEN_sdaccount)/OPEN_pulsefalltm;
//	
//	
//	//OPEN_refbasetm		= basetime;
//
//    pidParams1.pidoutput1 =0;
//    pidParams1.Kiterm1=0;
//    pidParams1.error1=0;
//    scalefactor1=280;//140;
//    //scaled_val1=(pidParams1.pidoutput1/scalefactor1); //50000
//    //newpulsefreq=178+scaled_val1;//refpulsefreq+scaled_val1;
//    OPEN_scaled_val1=pulsefreq-178;
//    OPEN_pidoutput1=OPEN_scaled_val1*scalefactor1;
//    if(wfchangef==1)
//    {
//    	integral_old=OPEN_pidoutput1;//-41440;//OPEN_pidoutput1;//*pidParams1.Ki1;
//    	wfchangef=0;
//    }
//    //pidParams1.integral1=0;//OPEN_pidoutput1/pidParams1.Ki1;
//    
//   
//}



//void change_pulse_para(unsigned int pulsesetws)
//{
//	pulsefreq=((pulsesetws*100.0)/(1.2*60.0));
//	pulsetmfactor=0.25;
//	pulsecurfactor=0.25;
//	peaktime=refpeaktm+(pulsesetws*pulsetmfactor);//refpulsebase=newbasetime;
//	tpulsetime=pulserisetime+peaktime+steptime+pulsefalltime;
////####################################################################################
//	if(pulsefreq>0.0)
//	 	pulseduty=100000.0/pulsefreq;
//	else
//	 	pulseduty=10000;
//	 	
//	if(pulseduty >=tpulsetime)
//	{
//		basetime=pulseduty-tpulsetime;
//	 	steptime=steptime;
//	}
//	else
//	{
//		basetime=1;
//		pulseontime=(pulserisetime+peaktime+pulsefalltime);
//		if(pulseduty>=pulseontime)
//			steptime=(pulseduty-pulseontime);//-peaktime;
//		else
//			steptime=30;
//		
//		if(steptime<=30)
//		   steptime=30;
//		//disptemp=newsteptime;
//	}
//	PID_basetm		=basetime/5;
//	PID_steptm		=steptime/5;
//
////####################################################################################	
///*	
//	if(pulsefreq>0.0)
//		pulseduty=100000.0/pulsefreq;
//	else
//		pulseduty=10000;
//		
//	if(pulseduty >=(peaktime+steptime))
//	{
//		basetime=pulseduty-(peaktime+steptime);
//		steptime=steptime;
//	}
//	else
//	{
//		basetime=1;
//		steptime=pulseduty-peaktime;
//	} 		 
//*/	
//	//peaktime=refpeaktm+(pulsesetws*pulsetmfactor);//refpulsebase=newbasetime;
//		 
//	if(peaktime>0)
//		pulsetm		=peaktime/5;//20;	//20*50usec=1000usec;
//	else
//		pulsetm=0;
//		
//	if(steptime>0)
//		steptm		=steptime/5;//40;	//10*50usec=500usec
//	else
//		steptm=0;
//	
//	if(basetime>0)	
//		basetm		=basetime/5;//50;	//50*50usec=2500usec
//	else
//		basetm=0;
//	
//	pulserisetm		=pulserisetime/5;//6;  	//6*50usec=300usec 
//	pulsefalltm		=pulsefalltime/5;//20;	//20*50usec=1000usec;
//	startpulsetm	=startpulsetime/5;//3;  	//3*50usec=150usec
//	
//	//refstepamp=stepamp;
//	//tpulsetime=pulserisetime+peaktime+steptime+pulsefalltime;
//		
//				
//	peakamp=refpeakamp+(pulsesetws*pulsecurfactor);//0.3);
//	if(peakamp>=600)
//	peakamp=600;
//	uppeakamp=peakamp+100;//
//	if(uppeakamp>600)
//	uppeakamp=600;
//	
//	
//	uppdaccount  =CCOFFSET+(uppeakamp*CCSLOPE);
//	pdaccount	 =CCOFFSET+(peakamp*CCSLOPE);
//	sdaccount	 =CCOFFSET+(stepamp*CCSLOPE);
//	bdaccount	 =CCOFFSET+(baseamp*CCSLOPE);
//		
//	newupstep		=(uppdaccount-bdaccount)/pulserisetm;
//	newdownstep	    =(pdaccount-sdaccount)/pulsefalltm;
//	refbasetm		=basetime;
///*
//bdaccount=PID_bdaccount;
//sdaccount=PID_sdaccount;
//newupstep=PID_newupstep;
//newdownstep=PID_newdownstep;
//basetm=PID_basetm;
//steptm=PID_steptm;
//*/	
//	
//	
//	
//}
//

void calculate_arcbasevtg_original(unsigned int psetvolt)
{
	if(para.pmigmode.arclength >= 40) //10)
	{
		tempmjp=para.pmigmode.arclength-40;//10;
		parcbasevtg=psetvolt+(psetvolt*tempmjp*0.0050);//ARCLFACTOR);  //ARCLFACTOR=0.025
	}
	if(para.pmigmode.arclength < 40) //10)
	{
		tempmjp=40-para.pmigmode.arclength;
		parcbasevtg=psetvolt-(psetvolt*tempmjp*0.0050);//*ARCLFACTOR);
		if(parcbasevtg<120) //140
		parcbasevtg=120; //40;
	}
	lcd_disp_hex_dec(parcbasevtg);
	voltupdate();
}

void calculate_arcbasevtg(unsigned int psetvolt)
{

     	parcbasevtg=psetvolt;
		SetPulseVoltage=psetvolt;
		lcd_disp_hex_dec(SetPulseVoltage);//33
		voltupdate();

	/*if(cDisplayDia==0)
	{
		parcbasevtg=psetvolt;
		SetPulseVoltage=psetvolt;
		lcd_disp_hex_dec(SetPulseVoltage);//33
		voltupdate();
	}
	else if(cSoftwireDetfg == 1)
	{
		parcbasevtg=psetvolt;
		SetPulseVoltage=psetvolt-20;
		lcd_disp_hex_dec(SetPulseVoltage);//33
		voltupdate();
		
	}	
	else{
		parcbasevtg=psetvolt;
		SetPulseVoltage=psetvolt-10;
		lcd_disp_hex_dec(SetPulseVoltage);//33
		voltupdate();
	}	*/	
	
}

void update_PMIG_syn_data(unsigned char synkey)
{
	if(synkey=='A')
	{
		if(pmat==pms)
		{
			pmat=p71t1;
			pdia=ponepttwo;
			pgas=parco2;
			lcdput(6,0,pmat71t1);
			lcdput(6,48,diaonepttwo);
//today			lcdput(7,90,gasarco2);
		}	
		else if(pmat==p71t1)
		{
			pmat=p180r;
			pdia=ponepttwo;
			pgas=parco2;
			lcdput(6,0,pmat180r);
			lcdput(6,48,diaonepttwo);
//today			lcdput(7,90,gasarco2);
		}	
		else if(pmat==p180r)
		{
			pmat=pss18;
			pdia=ponepttwo;
			pgas=paro2;
			lcdput(6,0,pmatss18);
			lcdput(6,48,diaonepttwo);
//today			lcdput(7,90,gasaro2);
		}	
		else if(pmat==pss18)
		{
			pmat=pss19;
			pdia=ponepttwo;
			pgas=paro2;
			lcdput(6,0,pmatss19);
			lcdput(6,48,diaonepttwo);
//today			lcdput(7,90,gasaro2);
		}
		else if(pmat==pss19)
		{
			pmat=ss_fcaw1;
			pdia=ponepttwo;
			pgas=pco2;
			lcdput(6,0,pmatssfcaw1);
			lcdput(6,48,diaonepttwo);
//today			lcdput(7,90,gasco2);
		}		
		else if(pmat==ss_fcaw1)
		{
			pmat=lafcaw;
			pdia=ponepttwo;
			pgas=pco2;
			lcdput(6,0,cMatTxt[pmat]);
			lcdput(6,48,diaonepttwo);

		}
		else if(pmat==lafcaw)
		{
			pmat=hffcaw;
			pdia=ponepttwo;
			pgas=pco2;
			lcdput(6,0,cMatTxt[pmat]);
			lcdput(6,48,diaonepttwo);

		}				
		else if(pmat==hffcaw)
		{
			pmat=palu4043;
			pdia=ponepttwo;
			pgas=par;
			lcdput(6,0,pmatalu4043);
			lcdput(6,48,diaonepttwo);
//today			lcdput(7,90,gasar);			
		}
		
		else if(pmat==palu4043)
		{
			pmat=palu5356;
			pdia=ponepttwo;
			pgas=par;
			lcdput(6,0,pmatalu5356);
			lcdput(6,48,diaonepttwo);
//today			lcdput(7,90,gasar);
		}
		else if(pmat==palu5356)
		{
			pmat=palu99;
			pdia=ponepttwo;
			pgas=par;
			lcdput(6,0,pmatalu99);
			lcdput(6,48,diaonepttwo);
//today			lcdput(7,90,gasar);
		}
		else if(pmat==palu99)
		{
			pmat=pms;
			pdia=ponepttwo;
			pgas=parco2;
			lcdput(6,0,pmatms);
			lcdput(6,48,diaonepttwo);
//today			lcdput(7,90,gasarco2);
		}
		lcdput(6,88,cGasTxt[pgas]);		
		lcdput(7,80,cGasPercent[pgas]);			
		
		
	/*	if(pmat==pms)
		{
			pmat=pss;
			pdia=ponepttwo;
			pgas=parco2;
			lcdput(7,0,matss);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasarco2);
		}	
		else if(pmat==pss)
		{
			pmat=palu;
			pdia=ponepttwo;
			pgas=par;
			lcdput(7,0,matalu);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasar);
			
		}
		else if(pmat==palu)
		{
			pmat=pms;
			pdia=ponepttwo;
			pgas=parco2;
			lcdput(7,0,matms);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasarco2);
		}*/
	}
	else if(synkey=='B')
	{
			if((pmat==pms) || (pmat==pss18) ||(pmat==pss19)|| (pmat==palu4043)|| (pmat==palu5356)/*|| (pmat==ss_fcaw1)
			|| (pmat==ss_fcaw2)*/)
			{
				if(pdia==pzeropteight)
				{
					pdia=poneptzero;
//05/09/2019					lcdput(6,48,diaoneptzero);
				}	
				else if(pdia==poneptzero)
				{
					pdia=ponepttwo;
//05/09/2019					lcdput(6,48,diaonepttwo);
				}
				
				else if(pdia==ponepttwo)
				{
					pdia=poneptsix;
//05/09/2019					lcdput(6,48,diaoneptsix);
				}
				else if(pdia==poneptsix)
				{
					pdia=pzeropteight;
//05/09/2019					lcdput(6,48,diazeropteight);
				}
			}
			
			
			
			
			
			/*if(pmat==pss)
			{
				if(pdia==ponepttwo)
				{
					pdia=pzeropteight;
					lcdput(7,48,diazeropteight);
				}
				else if(pdia==pzeropteight)
				{
					pdia=ponepttwo;
					lcdput(7,48,diaonepttwo);
				}
			}*/
			//pms,p71t1,p180r,pss18,pss19,palu4043,palu5356,palu99}pmat;
			if((pmat==palu99) || (pmat==p71t1)|| (pmat==p180r))
			{
				if(pdia==ponepttwo)
				{
					pdia=poneptsix;
//05/09/2019					lcdput(6,48,diaoneptsix);
				}
				else if(pdia==poneptsix)
				{
					pdia=ponepttwo;
//05/09/2019					lcdput(6,48,diaonepttwo);
				}	
			}
			if((pmat==ss_fcaw1) || (pmat==lafcaw))
			{
				if(pdia==ponepttwo)
				{
					pdia=poneptsix;
//05/09/2019					lcdput(6,48,diaoneptsix);
				}
				else if(pdia==poneptsix)
				{
					pdia=ponepttwo;
//05/09/2019					lcdput(6,48,diaonepttwo);
				}				
			}		
			lcdput(6,48,cDiaTxt[pdia]);
			
							
			/*{
				pdia=ponepttwo;
				lcdput(7,48,diaonepttwo);
			}*/
	}
	else if(synkey=='C')
	{
		if((pmat==pms)||(pmat == lafcaw) || (pmat == hffcaw))
		{
/*			//if(pgas==parco2)
			{
				pgas=parco2;
				lcdput(7,90,gasarco2);
			}
*/
				if(pgas == pco2)
				{
					pgas=parco2;
//today					lcdput(7,90,gasarco2);
				}
				else
				{
					pgas=pco2;
//today					lcdput(7,90,gasco2);					
				}
				
		}
		else if(pmat == p71t1)
		{
				if(pgas == pco2)
				{
					pgas=parco2;
//today					lcdput(7,90,gasarco2);
				}
				else
				{
					pgas=pco2;
//today					lcdput(7,90,gasco2);					
				}
		}	
		else if((pmat==pss18) || (pmat==pss19))
		{
			if(pgas==parco2)
			{
				pgas=paro2;
//today				lcdput(7,90,gasaro2);
			}else
			{
				if(pmat==pss18)
				{
					pgas=parco2;				
				}			
			}	
			//else if(pgas==paro2)
			//{
			//	pgas=parco2;
			//	lcdput(7,90,gasarco2);
			//}
		}
//-----------------------------------------
// on 01/08/2019
		else if(pmat == ss_fcaw1)	
		{
				if(pgas == pco2)
				{
					pgas=parco2;
//					lcdput(6,88,gasarco2);
				}
				else
				{
					pgas=pco2;
//					lcdput(6,88,gasco2);										
				}				
		}
//-----------------------------------------
		else if((pmat==palu4043) || (pmat==palu5356) || (pmat==palu99))
		{
			pgas=par;
//			lcdput(7,90,gasar);
		}
		lcdput(6,88,cGasTxt[pgas]);		
		lcdput(7,80,cGasPercent[pgas]);				
	}
	//To limit the wire speed when program no change and to calculate voltage
	ppmigsetwirespeed=0;
	program_number=iPProgramNo;//newpmmmatgas[pdia][pmat][pgas];
	
	max_Pws=max_Pwire_speed[program_number];
	
	if(para.pmigmode.setwspeed>max_Pws)
	{		
		para.pmigmode.setwspeed=max_Pws;
	}	
}

void LCD_pulsemig_syn_data_write()
{
		{
			/*
			if(pmat==pms)
			lcdput(6,0,pmatms);
			else if(pmat==p71t1)
			lcdput(6,0,pmat71t1);
			else if(pmat==p180r)
			lcdput(6,0,pmat180r);
			else if(pmat==pss18)
			lcdput(6,0,pmatss18);
			else if(pmat==pss19)
			lcdput(6,0,pmatss19);
			else if(pmat==palu4043)
			lcdput(6,0,pmatalu4043);
			else if(pmat==palu5356)
			lcdput(6,0,pmatalu5356);
			else if(pmat==palu99)
			lcdput(6,0,pmatalu99);
			else if(pmat == ss_fcaw1)
			lcdput(6,0,pmatssfcaw1);
			*/	
			lcdput(6,0,cMatTxt[pmat]);					
			
		}
		{   /*
			if(pdia==pzeropteight)
			lcdput(6,48,diazeropteight);
			else if(pdia==poneptzero)
			lcdput(6,48,diaoneptzero);
			else if(pdia==ponepttwo)
			lcdput(6,48,diaonepttwo);
			else if(pdia==poneptsix)
			lcdput(6,48,diaoneptsix);
			*/
			lcdput(6,48,cDiaTxt[pdia]);			
		}
		{
			/*
			if(pgas==parco2)
			lcdput(6,88,gasarco2);
			else if(pgas==par)
			lcdput(6,88,gasar);	
			else if(pgas==paro2)
			lcdput(6,88,gasaro2);
			else if(pgas==pco2)
			lcdput(6,88,gasco2);
			*/
		lcdput(6,88,cGasTxt[pgas]);		
		lcdput(7,80,cGasPercent[pgas]);								
		}	
}
