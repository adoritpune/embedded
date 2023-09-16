void MMAWELD(void)
{
	    if (modechangef==1)
			{
				clrlcd();
				lcdput_bold(0,0,ar11);
				lcdput(2,0,ar12);
				lcdput(4,0,ar13);
				//lcdput(7,0,ar20);
				//mmat=mms;
				//mdia=twoptfive;
				//melectrode=sevenzero;
				diswin1[0]='M';
				diswin1[1]='M';
				diswin1[2]='A';
				diswin2[0]='M';
				diswin2[1]='O';
				diswin2[2]='D';
				for(j=0;j<200;j++)
				for(i=0;i<10000;i++);
				modechangef=0;
				dispupdatef=1;
				keychange1=1;
				//SHDNLAT=1;			//OCV ON
				SHDNLAT=0;			//OCV OFF
				
				if(power_on_in_mma==1)
				{
				OCVON_command=1;
				power_on_in_mma=0;
				}
				else
				OCVON_command=0;
				
				
				lcdput_bold(6,0,ar14);
				//lcdput(6,0,ar14);
				//weldmode='X';
				weldmode='M';
				memoryzone='X';
				eedata=weldmode;//3456;							//0x0003;
				EEPROM_Erase_Write((0*2),eedata);
				
				weldmode='M';
				read_current_status();
				check_eeprom_values();
				keychange1=0;
				
			/*	memoryzone='M';
				para.mmamode.hotstart=EEPROM_Read(0*2);
				if(para.mmamode.hotstart>=100)
				para.mmamode.hotstart=100;
				read_mhotstart=para.mmamode.hotstart;
				
				para.mmamode.setcurrent=EEPROM_Read(1*2);
				if(para.mmamode.setcurrent>=500)
				para.mmamode.setcurrent=500;
				read_msetcurrent=para.mmamode.setcurrent;
				
				para.mmamode.arcforce=EEPROM_Read(2*2);
				if(para.mmamode.arcforce>=100)
				para.mmamode.arcforce=100;
				read_marcforce=para.mmamode.arcforce;
				
				para.mmamode.mmaterial=EEPROM_Read(3*2);
				if(para.mmamode.mmaterial>2)
				para.mmamode.mmaterial=0;
				read_mmaterial=para.mmamode.mmaterial;
				mmat=para.mmamode.mmaterial;
			 
				
				para.mmamode.melectrodesize=EEPROM_Read(4*2);
				if(para.mmamode.melectrodesize>3)
				para.mmamode.melectrodesize=0;
				read_melectrodesize=para.mmamode.melectrodesize;
				mdia=para.mmamode.melectrodesize;
				
				para.mmamode.melectrotype=EEPROM_Read(5*2);
				if(para.mmamode.melectrotype>4)
				para.mmamode.melectrotype=0;
				read_melectrotype=para.mmamode.melectrotype;
				melectrode=para.mmamode.melectrotype;
			*/	
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
			}
				
			//TypeU.LEDGROUP[0]=0x00;
			//Type.current		=1;
			//Type.voltage		=1;
		//	GASRELAYLAT		=OFF;						//TO CONTROL THE GAS SOLENOID VALVE
		//	HFRELAYLAT		=OFF;						//TO CONTROL THE HF RELAY
			CCCVCTRLLAT		=CCMODE;					//CCCV CONTROL  INPUT TO PWM CARD.
			ARCONLAT		=OFF;						//ARCON CONTROL SIGNAL INPUT TO PWM CARD
			OC2RS			=0;
			
			
			
/*************************************OCV KEY FUNCTIONALITY******************************************/			
			
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
			
/*************************************OCV KEY FUNCTIONALITY******************************************/			
			
			
			if(encod3!='$' || encod2 !='$')
			{
				updatemccparameter(encod3,encod2);	
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
				
				
				
				if(M_weldingonf==1)//@AFTER COMPLETING OF WELDING
				{
					
					M_weldingonf=0;
				 
					weldmode='M';
					write_current_status();
				}	
				
				
				if(keychange1==1)     // || (dispupdatef==1))
				{
					keychange1=0;
					current1=findmatindex2();//(wirespeed);
					para.mmamode.setcurrent=current1;
					lcd_disp_hex_dec(program_number);
					programupdate();
				}
				if((presetcurrent!=para.mmamode.setcurrent) || (dispupdatef==1))
				{
					
					if(keychange1==1)// || (dispupdatef==1))
					{
						keychange1=0;
						current1=findmatindex2();//(wirespeed);
						para.mmamode.setcurrent=current1;
						lcd_disp_hex_dec(program_number);
						programupdate();
					}
					
					disp_hex_dec_curr(para.mmamode.setcurrent);
					//disp_hex_dec_volt(para.mmamode.arcforce);	
					//dispupdatef=0;
					weldingdone=0;
					if(SPI2STATbits.SPITBF==0 && antistick_f!=1)//normal reference is given only when antistick is off
					{
						DACCSLAT	=0;
						//daccount	=CCOFFSET + (para.mmamode.setcurrent*CCSLOPE);//8.0;//CCSLOPE);//5.20);//490);//4.60);//4.70);
						
						daccount	=(para.mmamode.setcurrent*CCSLOPENEW)-CCOFFSETNEW ;//8.0;//CCSLOPE);//5.20);//490);//4.60);//4.70);
						
						if(daccount>=4095)
						daccount=4095;
						SPI2BUF		=28672+daccount;
					}
					dispnum1=daccount>>2;
					lcd_disp_hex_dec(para.mmamode.setcurrent);
					currupdate();
				}
				presetcurrent=para.mmamode.setcurrent;	
				
				
				if((parcforce !=para.mmamode.arcforce) || (dispupdatef==1))
				{
					lcd_disp_hex_dec(para.mmamode.arcforce);
					arcforceupdate();
				}
				parcforce =para.mmamode.arcforce;
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
				dispupdatef=1;
				
				M_weldingonf=1;
				
				//if(presetcurrent!=para.mmamode.setcurrent)
				{
					if(SPI2STATbits.SPITBF==0)
					{
						DACCSLAT	=0;
						/*
							if(para.mmamode.setcurrent >=100)
								daccount=CCOFFSET+(para.mmamode.setcurrent*4.70);
							else
							{
								if(para.mmamode.setcurrent >= 6.0)
									daccount=CCOFFSET+((para.mmamode.setcurrent - 6.0)*4.70);
								else
									daccount=CCOFFSET+(para.mmamode.setcurrent*4.70);
							}
						
						daccount	=CCOFFSET+(para.mmamode.setcurrent*CCSLOPE);//5.20);//490);//4.70);	
						errdaccount	=ERRCCOFFSET+(para.mmamode.setcurrent*ERRCCSLOPE);//5.20);//490);//4.70);	
						SPI2BUF		=28672+daccount+errdaccount;     					 //850;//1000=50A, 850=30A , 900=40A;//+(2*arclength);// 40A  400;//Refbasecnt;
						*/
						//daccount	=CCOFFSET+ (para.mmamode.setcurrent*CCSLOPE);//para.mmamode.setcurrent*8.0;//CCSLOPE);//5.20);//490);//4.60);//4.70);
						
						
						if(VOLTAGE<100)      //For MMA antistick operation //@sbm
						{
						   antistick_f=1;    //flag set
						  
						   sum_setcurrent=30; //Default value 30A(can not be kept less than 20-> weldoff)
						   daccount	=(sum_setcurrent*CCSLOPENEW)-CCOFFSETNEW ;//8.0;//CCSLOPE);//5.20);//490);//4.60);//4.70);
						   if(daccount>=4095)
						   daccount=4095;
						   SPI2BUF		=28672+daccount;
						
						}
						
						
						
						else
						{
							antistick_f=0;
							
							sum_setcurrent=para.mmamode.setcurrent+sck_current_ref;
						    if(sum_setcurrent>=500)
						    sum_setcurrent=500;
						    
							daccount	=(sum_setcurrent*CCSLOPENEW)-CCOFFSETNEW ;//8.0;//CCSLOPE);//5.20);//490);//4.60);//4.70);
							if(daccount>=4095)
							daccount=4095;
							SPI2BUF		=28672+daccount;
						}
						
						if(presetcurrent!=para.mmamode.setcurrent)
						{
							lcd_disp_hex_dec(para.mmamode.setcurrent);
					    	currupdate();
					    } 
					    presetcurrent=para.mmamode.setcurrent;  
					    if(parcforce !=para.mmamode.arcforce) 
						{
							lcd_disp_hex_dec(para.mmamode.arcforce);
							arcforceupdate();
						}
						parcforce =para.mmamode.arcforce;
				
					}
				    presetcurrent=para.mmamode.setcurrent;
				}	
			}

}

void update_MMA_syn_data(unsigned char synkey)
{
	if(synkey=='A')
	{
		if(mmat==mms)
		{
			mmat=mss;
			mdia=twoptfive;
			melectrode=threezero;
			lcdput(7,0,mmatss);
			lcdput(7,48,mdiatwoptfive);
			lcdput(7,82,mthreezero);
		}	
		else if(mmat==mss)
		{
			mmat=mci;
			mdia=twoptfive;
			melectrode=nicl;
			lcdput(7,0,mmatci);
			lcdput(7,48,mdiatwoptfive);
			lcdput(7,82,mnicl);
		}
		else if(mmat==mci)
		{
			mmat=mms;
			mdia=twoptfive;
			melectrode=sevenzero;
			lcdput(7,0,mmatms);
			lcdput(7,48,mdiatwoptfive);
			lcdput(7,82,msevenzero);
		}
	}
	else if(synkey=='B')
	{
		if(mdia==twoptfive)
		{
			mdia=threepttwo;
			lcdput(7,48,mdiathreepttwo);
		}
		else if(mdia==threepttwo)
		{
			mdia=fourptzero;
			lcdput(7,48,mdiafourptzero);
		}
		else if(mdia==fourptzero)
		{
			mdia=fiveptzero;
			lcdput(7,48,mdiafiveptzero);
		}
		else if(mdia==fiveptzero)
		{
			mdia=twoptfive;
			lcdput(7,48,mdiatwoptfive);
		}
	}
	else if(synkey=='C')
	{
		if(mmat==mms)
		{
			if(melectrode==sevenzero)
			{
				melectrode=sixzero;
				lcdput(7,82,msixzero);
			}	
			else if(melectrode==sixzero)
			{
				melectrode=celwel;
				lcdput(7,82,mcelwel);
			}
			else if(melectrode==celwel)
			{
				melectrode=sevenzero;
				lcdput(7,82,msevenzero);
			}
		}
		else if(mmat==mss)
		{
				melectrode=threezero;
				lcdput(7,82,mthreezero);
		
		}
		else if(mmat==mci)
		{
				melectrode=nicl;
				lcdput(7,82,mnicl);
		}
	}
}	
