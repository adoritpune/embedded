void TIGWELD(void)
{
unsigned char temp_tig_weld=0;	
			if(modechangef==1)
			{
				clrlcd();
				lcdput_bold(0,0,ar21);
				lcdput(2,0,ar22);
				lcdput(4,0,ar23);
				//lcdput(7,0,ar30);
				//tmat=tss;
				//tdia=toneptsix;
				//tjoint=butt;
				diswin1[0]='T';
				diswin1[1]='I';
				diswin1[2]='G';
				diswin2[0]='M';
				diswin2[1]='O';
				diswin2[2]='D';
				for(j=0;j<200;j++)
				for(i=0;i<10000;i++);
				modechangef=0;
				dispupdatef=1;
				keychange1=0;   		//@as per versa
				//SHDNLAT=1;			//OCV ON
				SHDNLAT=0;				//OCV OFF
				OCVON_command=0;
				lcdput_bold(6,0,ar14);
				memoryzone='X';
				eedata=weldmode;//3456;	//0x0003;
				EEPROM_Erase_Write((0*2),eedata);
				
				weldmode='T';
				read_current_status();
				check_eeprom_values();
				keychange1=0;
				
				if(power_on_in_tig==1)
				{
				OCVON_command=1;
				power_on_in_tig=0;
				}
				else
				OCVON_command=0;
				
			/*	memoryzone='T';
				
				para.tigmode.setcurrent=EEPROM_Read(3*2);
				if(para.tigmode.setcurrent>500)
				para.tigmode.setcurrent=500;
				read_tsetcurrent=para.tigmode.setcurrent;
				
										
				para.tigmode.tmaterial=EEPROM_Read(5*2);
				if(para.tigmode.tmaterial>1)
				para.tigmode.tmaterial=0;
				read_tmaterial=para.tigmode.tmaterial;
				tmat=para.tigmode.tmaterial;
				
				para.tigmode.tplatesize=EEPROM_Read(6*2);
				if(para.tigmode.tplatesize>5)
				para.tigmode.tplatesize=0;
				read_tplatesize=para.tigmode.tplatesize;
				tdia=para.tigmode.tplatesize;
				
				para.tigmode.tjointtype=EEPROM_Read(7*2);
				if(para.tigmode.tjointtype>3)
				para.tigmode.tjointtype=0;
				read_tjointtype=para.tigmode.tjointtype;
				tjoint=para.tigmode.tjointtype;	
			 */
			 
				if(tmat==tss)
					lcdput(7,0,tmatss);
				else if(tmat==tdcu)	
					lcdput(7,0,tmatdcu);
				{
					if(tdia==toneptsix)
					lcdput(7,48,tdiaoneptsix);
					
					else if(tdia==ttwoptfour)
					lcdput(7,48,tdiatwoptfour);
					
					else if(tdia==tthreepttwo)
					lcdput(7,48,tdiathreepttwo);
					
					else if(tdia==tfourpteight)
					lcdput(7,48,tdiafourpteight);
					
					else if(tdia==tsixptfour)
					lcdput(7,48,tdiasixptfour);
					
					else if(tdia==ttwelvepteight)
					lcdput(7,48,tdiatwelvepteight);
				}
				{
					if(tjoint==butt)
					lcdput(7,82,tbutt);
					
					else if(tjoint==lap)
					lcdput(7,82,tlap);
					
					else if(tjoint==corner)
					lcdput(7,82,tcorner);
					
					else if(tjoint==fillet)
					lcdput(7,82,tfillet);	
				}	
				
				
				//@versa	
				program_number=mat_dia_joint[tmat][tdia][tjoint];//@versa imp
				
				if(program_number<=24) //SS
				{
					if(para.tigmode.setcurrent<=100)
					tungsten_size=16;
					else if((para.tigmode.setcurrent>100) && (para.tigmode.setcurrent<=200))
					tungsten_size=24;
					else if((para.tigmode.setcurrent>200) && (para.tigmode.setcurrent<350))
					tungsten_size=32;
				}
				else
				{
					if(para.tigmode.setcurrent<=150)
					tungsten_size=16;
					else if((para.tigmode.setcurrent>150) && (para.tigmode.setcurrent<=200))
					tungsten_size=24;
					else if((para.tigmode.setcurrent>200) && (para.tigmode.setcurrent<=250))
					tungsten_size=32;
					else if((para.tigmode.setcurrent>250) && (para.tigmode.setcurrent<=400))
					tungsten_size=48;
				}
							
				lcd_disp_hex_dec(program_number);
				programupdate();
				lcd_disp_hex_dec(tungsten_size);
				tigtunstenupdate();		
			}
		//	GASRELAYLAT	=OFF;						//TO CONTROL THE GAS SOLENOID VALVE
		//	HFRELAYLAT	=OFF;						//TO CONTROL THE HF RELAY
			CCCVCTRLLAT	=CCMODE;					//CCCV CONTROL  INPUT TO PWM CARD.
			ARCONLAT	=OFF;						//ARCON CONTROL SIGNAL INPUT TO PWM CARD
			OC2RS		=0;

			if(prev_OCVON_command!=OCVON_command)
			{
				if(OCVON_command==1)
				{
					SHDNLAT=1;			//OCV ON
					lcdput(6,0,ar15);
				}	
				else
				{
					SHDNLAT=0;			//OCV OFF
					lcdput_bold(6,0,ar14);
				}
			}		
			prev_OCVON_command=OCVON_command;
			
			if(keychange1==1)// || (dispupdatef==1))
			{
				
				keychange1=0;
				current1=findmatindex3();//(wirespeed);
				para.tigmode.setcurrent=current1;
				lcd_disp_hex_dec(program_number);
				programupdate();
				lcd_disp_hex_dec(tungsten_size);
				tigtunstenupdate();
			}	
			if(encod3!='$' || encod2 !='$')
			{
				updatetccparameter(encod3,encod2);	
				encod3='$';
				encod2='$';	
			}
			
			if(weldonf==0)// || dispupdatef==1)
			{
				TypeDP.DPGROUP[0]=0x00;
      			Typedp.digitdp5		=1;
				TypeU.LEDGROUP[0]=0x00;
				Type.current		=1;
				Type.voltage		=1;
				
				if(T_weldingonf==1)//@AFTER COMPLETING OF WELDING
				{
					
					T_weldingonf=0;
				 
					weldmode='T';
					write_current_status();
				}			
				
				
				if((ptigsetcurrent!=para.tigmode.setcurrent) || (dispupdatef==1)) 
				{
					disp_hex_dec_curr(para.tigmode.setcurrent);
					//disp_hex_dec_volt(VOLTAGE);	
					dispupdatef=0;
					weldingdone=0;
					if(SPI2STATbits.SPITBF==0)
					{
						DACCSLAT	=0;
						daccount=(para.tigmode.setcurrent*CCSLOPENEW)-CCOFFSETNEW;
						SPI2BUF		=28672+daccount;     //850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
					}
					lcd_disp_hex_dec(para.tigmode.setcurrent);
					tigcurrupdate();
				}
				ptigsetcurrent=para.tigmode.setcurrent;
				dispupdatef=0;
				disp_hex_dec_volt(VOLTAGE);	
			}
			else if(weldonf==1)
			{	
				TypeDP.DPGROUP[0]=0x00;
      			Typedp.digitdp5		=1;
				TypeU.LEDGROUP[0]=0x00;
				Type.current		=1;
				Type.voltage		=1;
				disp_hex_dec_curr(CURRENT);
				disp_hex_dec_volt(VOLTAGE);
				weldingdone=1;
			
				T_weldingonf=1;
				
				
				if(SPI2STATbits.SPITBF==0)
				{
					DACCSLAT	=0;
					daccount=(para.tigmode.setcurrent*CCSLOPENEW)-CCOFFSETNEW;
					SPI2BUF		=28672+daccount;     //850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
				}	
				dispupdatef=1;
			}
}

void update_TIG_syn_data(unsigned char synkey)
{
	if(synkey=='A')
	{
		if(tmat==tss)
		{
			tmat=tdcu;
			tdia=toneptsix;
			tjoint=butt;
			lcdput(7,0,tmatdcu);
			lcdput(7,48,tdiaoneptsix);
			lcdput(7,82,tbutt);
		}	
		else if(tmat==tdcu)
		{
			tmat=tss;
			tdia=toneptsix;
			tjoint=butt;
			lcdput(7,0,tmatss);
			lcdput(7,48,tdiaoneptsix);
			lcdput(7,82,tbutt);
		}
	}
	else if(synkey=='B')
	{
		if(tdia==toneptsix)
		{
			tdia=ttwoptfour;
			lcdput(7,48,tdiatwoptfour);
		}	
		else if(tdia==ttwoptfour)
		{
			tdia=tthreepttwo;
			lcdput(7,48,tdiathreepttwo);
		}	
		else if(tdia==tthreepttwo)
		{
			tdia=tfourpteight;
			lcdput(7,48,tdiafourpteight);
		}
		else if(tdia==tfourpteight)
		{
			tdia=tsixptfour;
			lcdput(7,48,tdiasixptfour);
		}
		else if(tdia==tsixptfour)
		{
			tdia=ttwelvepteight;
			lcdput(7,48,tdiatwelvepteight);
		}
		else if(tdia==ttwelvepteight)
		{
			tdia=toneptsix;
			lcdput(7,48,tdiaoneptsix);
		}
	}
	else if(synkey=='C')
	{
		if(tjoint==butt)
		{
			tjoint=lap;
			lcdput(7,82,tlap);
		}	
		else if(tjoint==lap)
		{
			tjoint=corner;
			lcdput(7,82,tcorner);
		}
		else if(tjoint==corner)
		{
			tjoint=fillet;
			lcdput(7,82,tfillet);
		}
		else if(tjoint==fillet)
		{
			tjoint=butt;
			lcdput(7,82,tbutt);
		}
		
	}
}


