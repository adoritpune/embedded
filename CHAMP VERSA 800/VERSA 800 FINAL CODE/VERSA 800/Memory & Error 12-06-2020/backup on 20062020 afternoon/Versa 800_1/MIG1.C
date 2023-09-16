
void mig()
{
	
	if(welding_flag == 1)
		genref(rsetvoltage);
	if(mig_flag==0)
	{
		trans_flag=0;              //data transmission to wf
		TypeDP.DPGROUP[0]=0x00;
		CURR[0]='M';
		CURR[1]='I';
		CURR[2]='G';
		CURR[3]=91;          //-
		VOLT[0]='M';
		VOLT[1]='O';
		VOLT[2]='D';
		VOLT[3]='E';
		for(j=0;j<200;j++)
		for(i=0;i<10000;i++);
		mma_flag=0;
		saw_flag=0;
		mig_flag=1;
		
		//WS_SPEED_LEDLAT=0;         //ws led on
//		CURR_LEDLAT=0;             //current led// changed by sachin
		
		mma_init=0;
		CCCVLAT=CVMODE;				//CCCV MODE SELECTION IN PWM CARD 
		//migmodeon=1;
		//MMALEDLAT=0;              //TEMP
		//SAWLEDLAT=1;
		count_10ms=0;
		count_100ms=0;
		ARCONLAT=0;					//ARCON OUTPUT SIGNAL TO PWM PCB
		OCV_FLAGLAT=0;
		GASRELAYIO=0;
		GASRELAYLAT=0;
		Disp_updatef=1;
		disp_calf=0;
		trans_flag=1;              //data transmission to wf
/*
		memdata=EEPROM_Read(5*2);
		rset_wirespeed=memdata;		
		memdata=EEPROM_Read(7*2);
		if(memdata<=140 || memdata>=440)
		{
		
		    memdata=140;
		}
		rsetvoltage=memdata;
		//set_v = rsetvoltage;
		*/// changed by sachin
	}
	else if(trip_flag==0 && mig_flag==1)// &&  mma_init==1)
	{
		if(cyclestrt==0)									//Welding off
		{
			
			WS_SPEED_LEDLAT=0;
     		CURR_LEDLAT=1; //// changed by sachin
			psstatus.weldon=0;       //weld off sayali 07/05
			//SEGDPLAT=1;
			TypeDP.DPGROUP[0]=0x00;
			Typedp.digitdp3		=1;
			Typedp.digitdp7		=1;
			if((prset_wirespeed!=rset_wirespeed)|| (communication.setwspeed!=rset_wirespeed) || Disp_updatef==1)                    
			{
				if((cpidmode==0) && (ERROR_4_errorf==0))
				{
					disp_hex_dec_curr(rset_wirespeed);    //04032020
				}
				//disp_hex_dec_curr(rsetcurrent);
				//prsetcurrent=rsetcurrent;
				prset_wirespeed=rset_wirespeed;
				//transmit_parameter.set_wire_speed=rset_wirespeed;
				communication.setwspeed=rset_wirespeed; 
				//
				
				//transmit_parameter.lo_set_current=rset_wirespeed;
				//transmit_parameter.hi_set_current=rset_wirespeed>>8;
			}
			
			if((prsetvoltage!=rsetvoltage) || Disp_updatef==1)
			{
				if((cpidmode==0)&&(ERROR_4_errorf==0))
				{
					disp_hex_dec_volt(rsetvoltage);
					//disp_hex_dec_volt(iTest);//
				}
				prsetvoltage=rsetvoltage;//set_v; //rsetvoltage;
				set_v = rsetvoltage;
				communication.Lo_setvoltage=set_v;//receive_parameter.Hi_setvoltage;
				set_v>>=8;
				communication.Hi_setvoltage=set_v; //receive_parameter.Lo_setvoltage;
				//	
				
			}
			/*******************************************************/
			if(welding_flag==1)
			{
				WriteLastWeldData();
				welding_flag=0;   
				//write_mode_mem(1);
				
			}
			
			/*******************************************************/
			//welding_flag=0;
			GASRELAYLAT=0;
			OCV_FLAGLAT=0;             	// OCV OFF
			ARCONLAT=0;			   	//ARCON OUTPUT SIGNAL TO PWM PCB
			CCCVLAT=CVMODE;		//CV MODE SELECTION IN PWM CARD 
			motorerrcnt=0;
			//comm_flag=0;
			OC1RS=0;                      	//REFERENCE ZERO AT NO WELDING
			//genref(rsetvoltage);
			//Disp_updatef=0;
			prsetcurrent=0x1FFF;			//8191
			prsetvoltage=0x1FFF;			//8191
			MIGweldon_detectf=0;
			sf_accumulator=0;
			psstatus.creepspeedon=1;
			//migdaccount1=0;
			//migdaccount2=0;
			
		}
		else if(cyclestrt==1) //&&(oper > pre))
		{
			welding_flag=1;                 //saurabh
			psstatus.weldon=1;
			WS_SPEED_LEDLAT=1;
		    CURR_LEDLAT=0;// changed by sachin 24012020
			TypeDP.DPGROUP[0]=0x00;
      		Typedp.digitdp7		=1;
			if(((pdispweldcurrent != dispweldcurrent)  && disp_flag==1))	// || Disp_updatef==1)		//AFTER EVERY 1 SEC
			{
				//disp_hex_dec_curr(dispweldcurrent);               //DISPLAY ARC CURRENT
				//pdispweldcurrent = dispweldcurrent;
				//transmit_parameter.lo_actual_current=dispweldcurrent;     //for data transmission
				//transmit_parameter.hi_actual_current=dispweldcurrent>>8;
				//communication.Lo_actualcurrent=32;//weldcurrent;//dispweldcurrent;  
				//communication.Hi_actualcurrent=0;//weldcurrent>>8;//dispweldcurrent
				
			}   
			//disp_hex_dec_volt(mvoltage);  
			if((pweldvoltage != weldvoltage) && disp_flag==1)     //AFTER EVERY 1 SEC
			{
				//disp_hex_dec_volt(weldvoltage);                   //DISPLAY ARC VOLTAGE
				//disp_hex_dec_volt(migdaccount);
				//pweldvoltage = weldvoltage;
				//transmit_parameter.lo_actual_voltage=weldvoltage;
				//transmit_parameter.hi_actual_voltage=weldvoltage>>8;
				//communication.Lo_actualvoltage=weldvoltage;
				//communication.Hi_actualvoltage=weldvoltage>>8;
				
			}
	 		
	 		
			communication.Lo_actualcurrent=dispweldcurrent;//weldcurrent;//dispweldcurrent;  
			communication.Hi_actualcurrent=dispweldcurrent>>8;//weldcurrent>>8;//dispweldcurrent
			communication.Lo_actualvoltage=weldvoltage;
			communication.Hi_actualvoltage=weldvoltage>>8;
			disp_flag=0;
			
		}
		
	}

	else if(trip_flag==1)
	{
		TypeDP.DPGROUP[0]=0x00;
		GASRELAYLAT=0;
		OCV_FLAGLAT=0;             	// OCV OFF
		ARCONLAT=0;			   	//ARCON OUTPUT SIGNAL TO PWM PCB
		CCCVLAT=CVMODE;		   	//CV MODE SELECTION IN PWM CARD 
		comm_flag=0;
		//data_head();                	//TRANSMIT DATA TO HEAD
		OC1RS=0;                      	//REFERENCE ZERO AT NO WELDING
		OC2RS=0;
		motoronf=0;
		//TRIPLEDLAT=1;          //TEMP
		phsetcurrent=0;
		phsetvoltage=0;
		if(imtrip_flag==1)
        {
          		while(imtrip_flag==1); 
        
        }
		
		
	}
	trans_chk_f=0;     //only for checking


}

void torchaction()
{
		if(cyclestrt==0)
		{
			oper=pre;
		}
	   if(Torchmode=='2')    //2T mode
		{
			switch(oper)
			{
				case pre:
				{				
					
				   /* 	
					if(cyclestrt==0)
					{
						TypeDP.DPGROUP[0]=0x00;
						cyclestrt=1;
						count_preflow=0;
						GASRELAYLAT	=1;
						//CURR[0]='p';
    					//CURR[1]='R';
					    //CURR[2]='E';
					    //CURR[3]='R';
					    //VOLT[0]='F';
					    //VOLT[1]='L';
					    //VOLT[2]='O';
					    //VOLT[3]='W';
					
					}
					
					else if(OCV_FLAGLAT==0)//(count_preflow>=receive_parameter.preflow_time && OCV_FLAGLAT==0)
					{
						
						OCV_FLAGLAT	=1;          	//OCV ON
						ARCONLAT	=1;				//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;		//CV MODE SELECTION IN PWM CARD
						genref(0);//rsetvoltage);		//generate reference// 24012020
						drivemotor(0);//(rsetcurrent);
						motoronf	=1;
						motorerrcnt=0;
		                oper=weld;
					
					}
					*/
					if(cyclestrt==0) //&& (count_preflow>=PREF)) 
					{
						//CURR[0]='P';
    					//CURR[1]='R';
					    //CURR[2]='E';
					    //CURR[3]='F';
					    //VOLT[0]='F';
					    //VOLT[1]='L';
					    //VOLT[2]='O';
					    //VOLT[3]='W';
					    error_4_check4t=0;
					    //cntsecond_er4=0;
					    mig_parameters=1;
					    TypeDP.DPGROUP[0]=0x00;
					    count_preflow=0;
						cyclestrt	=1;
						GASRELAYLAT	=1;				//GAS ON RELAY.
						OCV_FLAGLAT	=1;          	//OCV ON
						ARCONLAT	=1;				//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;		//CV MODE SELECTION IN PWM CARD
						genref(0);  //rsetvoltage);		//generate reference// 24012020
						//genref(rsetvoltage);
						drivemotor(0); //(rsetcurrent);
						motoronf	=1;
						motorerrcnt=0;
						parametercnt=0;
						psstatus.motoron=0;
						psstatus.gasoncommand=1;
						psstatus.weldon=1;
						
						//oper=pre;													
						oper=weld;
					}
				/*	
					if(count_preflow >= 0)//(cyclestrt == 1)//(count_preflow >= PREF)
					{
			
						TypeDP.DPGROUP[0]=0x00;
						mig_parameters=0;
					    count_preflow=0;
						cyclestrt	=1;
						GASRELAYLAT	=1;				//GAS ON RELAY.
						OCV_FLAGLAT	=1;          	//OCV ON
						ARCONLAT	=1;				//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;		//CV MODE SELECTION IN PWM CARD
						genref(rsetvoltage);		//generate reference// 24012020
						drivemotor(0); //(rsetcurrent);
						motoronf	=1;
						motorerrcnt=0;

						psstatus.motoron=0;
						psstatus.gasoncommand=1;
						psstatus.weldon=1;
						parametercnt=0;
						GASCHKSWLAT = 0;
						oper=weld;
				*/
						/*
						if(error_4_check4t==0)
						{
							error_4_check4t=1;
							cntsecond_er4=ERROR4_DEBOUNCE_TIME;	
							ERROR_4_errorf=0;							
						}
						*/							
												
				//	}
						
					if(Torchkey=='R')
					{
					   //cyclestrt=0;
					   //GASRELAYLAT	=0;				//GAS ON RELAY.
					   //OCV_FLAGLAT	=0;          	//OCV ON
					   psstatus.weldon=0; 
					   
					   psstatus.motoron=0;
					   psstatus.gasoncommand=0;
						error_4_check4t=0;
						cErrorChkoverfg = 0; 
					   oper=exit1;
					   //oper=burn;
					   //oper=post;
					   
					}
					break;
				}		
				case weld:
				{					
					//CURR[0]='P';
    				//CURR[1]='P';
					//CURR[2]='P';
					oper=weld;
					if(Torchkey=='R')
					{
						//cyclestrt	=0;
						//psstatus.motoron=0;
						//psstatus.gasoncommand=0;
						psstatus.weldon=0;   
						motoronf		=0;
						OC2RS			=0;			//drivemotor(0);
						burnbackcnt		=0;
						count_postflow  =0;
						error_4_check4t=0;
						cErrorChkoverfg = 0;						
						//cntsecond_er4=0;
						//oper			=burn;
						oper            =exit1;
					}
					else
					{
					//	disp_hex_dec_curr(dispweldcurrent);  // commented 0n 28012020
						//disp_hex_dec_volt(1234); //(weldvoltage); // chnaged by sachin
						//error_4_check4t=1;
						//cntsecond_er4=0;
						if((error_4_check4t==0)&&(cErrorChkoverfg == 0))
						{
							error_4_check4t=1;
							cntsecond_er4=0;//ERROR4_DEBOUNCE_TIME;	
							ERROR_4_errorf=0;							
						}
								
						if((cpidmode==0) && (ERROR_4_errorf==0)) 
						{
							//error_4_check4t=1;
							
							if(dispweldcurrent <=45)
							{
								dispweldcurrent = 0;
							}	 
							disp_hex_dec_curr(dispweldcurrent); 
							disp_hex_dec_volt(weldvoltage);
						}
						genref(rsetvoltage);			//generate reference
						drivemotor(rsetcurrent);
						if(cErrorChkoverfg == 0)
						{
							psstatus.motoron=1;
							psstatus.gasoncommand=1;
							psstatus.weldon=1;
						}	
						//oper=weld; //burn;
					}					
					break;
				}
				
				case burn:
				{
					
					if(burnbackcnt >= 0) //BURN)   //    0) //(communication.burnback_time*10))
					{

						GASRELAYLAT	=0;			//GAS ON RELAY.
						OCV_FLAGLAT	=0;          	// OCV OFF
						ARCONLAT		=0;			//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;	//CV MODE SELECTION IN PWM CARD
						genref(0);					//generate reference
						//oper=exit1;
						burnbackcnt=0;
						parametercnt=0;
						mig_parameters=1;
						psstatus.motoron=0;
						psstatus.gasoncommand=1;
						psstatus.weldon=1;
						error_4_check4t=0;
						//cntsecond_er4=0;
						oper=post;
					}
					
					if(Torchkey=='R') //else
					{
						//CURR[0]='B';
    					//CURR[1]='U';
					    //CURR[2]='R';
					    //CURR[3]='N';
					    //VOLT[0]='B';
					    //VOLT[1]='A';
					    //VOLT[2]='C';
					    //VOLT[3]='K';	
						OC2RS=0;					//drivemotor(0);drivemotor(0);
						//burnbackcnt++;
						//oper=burn;
						//oper=exit1;
						oper=post;
					}
					break;
					
				}
				
				case post:
				{
					if(count_postflow >= 0)
					{
						//CURR[0]='P';
    					//CURR[1]='O';
					    //CURR[2]='S';
					    //CURR[3]='T';
					    //VOLT[0]='F';
					    //VOLT[1]='L';
					    //VOLT[2]='O';
					    //VOLT[3]='W';
						GASRELAYLAT	=0;			//GAS ON RELAY.
						OCV_FLAGLAT	=0;          	// OCV OFF
						ARCONLAT		=0;			//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;	//CV MODE SELECTION IN PWM CARD
						cyclestrt		=0;
						motortrip		=0;
						psstatus.weldon=1; 
						psstatus.motoron=0;
						psstatus.gasoncommand=1;
						count_postflow=0;
						parametercnt=0;
						mig_parameters=0;
						genref(0);
						oper=exit1;
					}
					/*
					if(Torchkey=='R')
					{
						CURR[0]='P';
    					CURR[1]='O';
					    CURR[2]='S';
					    CURR[3]='T';
					    VOLT[0]='F';
					    VOLT[1]='L';
					    VOLT[2]='O';
					    VOLT[3]='W';	
						OC2RS=0;				
						//oper=burn;
						oper=exit1;
						//oper=post;
					}
					*/
						break;
					
				}
						
				case exit1:
				{
					GASRELAYLAT	=0;			//GAS ON RELAY.
					OCV_FLAGLAT	=0;          	// OCV OFF
					ARCONLAT		=0;			//ARCON OUTPUT SIGNAL TO PWM PCB
					CCCVLAT		=CVMODE;	//CV MODE SELECTION IN PWM CARD
					cyclestrt		=0;
					motortrip		=0;
					psstatus.weldon=0;  
					parametercnt=0;
					psstatus.motoron=0;
					psstatus.gasoncommand=0;
					mig_parameters=0;
					error_4_check4t=0;
					//cntsecond_er4=0;
					//trans('E');
					genref(0);					//generate reference
					OC2RS=0;					//drivemotor(0);drivemotor(0);
					//oper=pre;
					motoronf		=0;
					count_preflow=0;
					burnbackcnt=0;
					parametercnt=0;
					count_postflow=0;
					cErrorChkoverfg = 0;
					break;
				}
			}//end mig switch
		}//2T mode

		//else if(0)//(Torchmode=='4')
		else if(Torchmode=='4')
		{
			switch(oper)
			{
				case pre:
				{
					if(cyclestrt==0)
					{
						cyclestrt=1;
						GASRELAYLAT	=1;				//GAS ON RELAY.
						OCV_FLAGLAT	=1;          		//OCV ON
						ARCONLAT=1;				//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;		//CV MODE SELECTION IN PWM CARD
						torchrelease=0;
						crateron		=0;
						genref(0);//rsetvoltage);			//generate reference //// 24012020
						OC2RS=0;
						error_4_check4t=0;
						//cntsecond_er4=0;
						oper=weld;
						count_preflow=0;
						motorerrcnt=0;
						psstatus.motoron=0;
						psstatus.gasoncommand=1;
						psstatus.weldon=1;
					}
					/*
					if(cyclestrt==0)
					{
						cyclestrt=1;
						count_preflow=0;
						GASRELAYLAT	=1;
						//CURR[0]='p';
    					//CURR[1]='R';
					    //CURR[2]='E';
					    //CURR[3]='R';
					    //VOLT[0]='F';
					    //VOLT[1]='L';
					    //VOLT[2]='O';
					    //VOLT[3]='W';
					
					}
					*/
					//if(count_preflow>=receive_parameter.preflow_time && OCV_FLAGLAT==0)
					if(count_preflow>=100 && OCV_FLAGLAT==0)
					{
						OCV_FLAGLAT	=1;          		//OCV ON
						ARCONLAT	=1;				//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;		//CV MODE SELECTION IN PWM CARD
						torchrelease=0;
						crateron		=0;
						genref(rsetvoltage);//generate reference// 24012020
						error_4_check4t=1;
						//cntsecond_er4=0;
						//drivemotor(rsetcurrent);
						OC2RS=0;	
						oper=weld;
						motorerrcnt=0;
		               	psstatus.motoron=0;
						psstatus.gasoncommand=1;
						psstatus.weldon=1; 
					
					}
					break;
				}	
				case weld:
				{
						if(Torchkey=='R' && torchrelease==0 && crateron==0)				//VOLTAGE ON, WIRESPEED START AFTER RELEASE TORCH
						{
							torchrelease	=1;
							oper		=weld;
							motoronf	=1;
							psstatus.motoron=1;
							genref(rsetvoltage);							//generate reference
							drivemotor(rsetcurrent);
							psstatus.motoron=1;
						    psstatus.gasoncommand=1;
						    psstatus.weldon=1;
						}
						else if(Torchkey=='R' && torchrelease==1 && crateron==0)		//VOLTAGE ON, WIRESPEED ON
						{
							oper=weld;
							genref(rsetvoltage);							//generate reference
							drivemotor(rsetcurrent);						//generate reference
							psstatus.motoron=1;
						    psstatus.gasoncommand=1;
						    psstatus.weldon=1;						
						}
						else if(Torchkey=='P' && torchrelease==1 && crateron==0)		// && Type.crateron==0)//TORCH PRESSED AGAIN CRATER FUNCTION
						{
							oper=weld;
							genref(rsetvoltage*0.75);							//generate reference
							motoronf	=0;
							OC2RS		=0;									//drivemotor(rsetcurrent*0.75);	
							burnbackcnt	=0;
							crateron=1;	
							psstatus.motoron=1;
						    psstatus.gasoncommand=1;
						    psstatus.weldon=1;						
						}	
						else if(Torchkey=='R' && torchrelease==1 && crateron==1)		// && Type.crateron==0)//TORCH PRESSED AGAIN CRATER FUNCTION
						{
							psstatus.motoron=0;
							oper		=burn;
							genref(0);									//rsetvoltage*0.75);							//generate reference
							OC2RS=0;	
							burnbackcnt	=0;
							psstatus.motoron=1;
						    psstatus.gasoncommand=1;
						    psstatus.weldon=1;
						}
						break;
					}
					case burn:
					{
						
						//if(burnbackcnt >=receive_parameter.burnback_time)
						if(burnbackcnt >=0)
						{
							GASRELAYLAT	=0;			//GAS ON RELAY.
							OCV_FLAGLAT	=0;          	// OCV OFF
							ARCONLAT		=0;			//ARCON OUTPUT SIGNAL TO PWM PCB
							CCCVLAT		=CVMODE;	//CV MODE SELECTION IN PWM CARD
							genref(0);					//generate reference
							//burnbackcnt=0;
							OC2RS			=0;
							oper			=exit1;
						    psstatus.motoron=0;
						    psstatus.gasoncommand=1;
						    psstatus.weldon=1;	
						}
						else
						{
							OC2RS=0;	
							burnbackcnt++;
							oper=burn;
						}
						break;
					}	
					case exit1:
					{
						GASRELAYLAT	=0;			//GAS ON RELAY.
						OCV_FLAGLAT	=0;          	// OCV OFF
						ARCONLAT		=0;			//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;	//CV MODE SELECTION IN PWM CARD
						cyclestrt		=0;
						torchrelease		=0;
						crateron		=0;
						genref(0);					//generate reference
						OC2RS			=0;	
						motortrip		=0;
						oper			=pre;
						psstatus.motoron=0;
					    psstatus.gasoncommand=0;
					    psstatus.weldon=0;
						break;
					}
			}
		}	
			
       
}			
void genref(unsigned int setvtg)
{
	
	if(adcread_overf == 1)
	{
		adcread_overf = 0;
		superfast_pid();		
	}			
	
	if(setvtg != 0)
	{ 
		if((SPI2STATbits.SPITBF==0)) //&& (setvtg >= weldvoltage))     //for versa 800
		{
			DACCSLAT=0;
			if(MIGweldon_detectf==0)			//(daccountfg==1)
			{
				dac_counts=((migdaccount1*iMul) / 10) +  iMigOffset;//MIGCCOFFSET;	//original//	MIGCCSLOPE
//				if(dac_counts>=2950)
//				dac_counts=2950;
				SPI2BUF=28672+dac_counts;//dac_counts;   //ORing 28672;//+

			}
			else if(MIGweldon_detectf==1) 				//(daccountfg==0)
			{
		
				dac_counts = iMigOffset + ((migdaccount2*iMul) / 10);
				//dac_counts_new=dac_counts-imfvalue;
				SPI2BUF=28672+dac_counts;
				
				/*
				else if(sf_error>=0)
				{
					dac_counts = ((migdaccount2*iMul) / 10) - iMigOffset;
					SPI2BUF=28672+dac_counts;//dac_counts;   //ORing 28672;//+
				}
				*/
				/*
				if(sf_error>=0)
				{					
					dac_counts = iMigOffset - (((sf_error*iMul) / 10)  + iLowpidvalue);
					SPI2BUF=28672+dac_counts;
				}
				else if(sf_error<0)
				{					
					dac_counts = iMigOffset + (((sf_error*iMul) / 10)  + iLowpidvalue);
					SPI2BUF=28672+dac_counts;
				}
				*/
			}
				
		}		
	}
	else
	{
		if(SPI2STATbits.SPITBF==0)      //for versa 800
		{
			DACCSLAT=0;
			dac_counts = 0;	
			SPI2BUF=28672+dac_counts;//dac_counts;   //ORing 28672;//+
		}		
	}		
	
	//PWMcount=1450;
	//OC1RS= PWMcount;
/*	
	if(setvtg>=weldvoltage)
	{
	   PWMcount=100.65+((setvtg-weldvoltage) *5.22);//20.88 + ((setvtg-weldvoltage) *5.22) ;
	   if(PWMcount >= 2940)
	   PWMcount=2940;
	   OC1RS= PWMcount;
	
	}
	else
	{
		err1=weldvoltage-setvtg;
		err2=setvtg-err1;
		
	    PWMcount=100.65 + ((setvtg-err2) *5.22) ;
	    if(PWMcount >= 2940)
	    PWMcount=2940;		
	}
*/	
	/*if(abs(p_setvtg-setvtg)>=5)
	{
		PWMcount=1300+(setvtg *3);//20.88 + (setvtg *5.22) ;
		if(PWMcount >= 2940)
		PWMcount=2940;
		OC1RS= PWMcount;
	}
	else
	{
		PWMcount=1300+(p_setvtg *3);//20.88 + (setvtg *5.22) ;
		if(PWMcount >= 2940)
		PWMcount=2940;
		OC1RS= PWMcount;
	
	}
	p_setvtg=setvtg;*/
	
	
	
	
	
}
void drivemotor(unsigned int wspeed)
{
	
	refmotorvtg=(wspeed * 2.11);//wspeed
    
    
	
}

void second_order_pid()
{
    static unsigned int scalefactor=0,scaled_output=0;	//,maxmpwm=2500;
    PID_sParams.ReferenceSetpoint=rsetvoltage;//mvoltage;				//mfreq;
    PID_sParams.feedback=actual_voltage;//refmotorvtg;					//rsetcurrent * 2.11;//setwsfreq;
    PID_sParams.error = PID_sParams.feedback - PID_sParams.ReferenceSetpoint ;
    PID_sParams.absolute_error=abs(PID_sParams.error);
    PID_sParams.a=iKp; //180.0; //2.0;//5;
    PID_sParams.b=iKi; //20.0;//0.1;
    PID_sParams.c=iKd; //2.0;//0.5;
    //PID_sParams.d=1000;
    PID_sParams.outmax=32000; //10000;
    scalefactor=6.0; //4.0;		//PID_sParams.outmax/maxmpwm;
    PID_sParams.derivitive = PID_sParams.error - PID_sParams.previous_error;
    
    if(PID_sParams.feedback<=80)
    {
    //if((PID_sParams.error > 2.0) || (PID_sParams.error < -2.0))
    
        //PID_sParams.output=PID_sParams.output +((PID_sParams.a*PID_sParams.error))+ (PID_sParams.b*PID_sParams.previous_error) + (PID_sParams.c*PID_sParams.pprevious_error);
  	  
  	  //PID_pterm = (PID_sParams.a*PID_sParams.error) / 10;
  	  //PID_iterm+= (PID_sParams.b*PID_sParams.error) /10;
  	  /*
  	  if(PID_iterm<=0)
  	  {
	  	  PID_iterm=0;
	  }
	  else if(PID_iterm>=PID_sParams.outmax)
	  {
		  PID_iterm=PID_sParams.outmax;
	  }
  	  */
  	  
  	  //PID_dterm = (PID_sParams.c*(PID_sParams.error-PID_sParams.previous_error)) /10;
  	  
  	  PID_pterm = (PID_sParams.a*PID_sParams.error) / 10;
  	  PID_iterm+= (PID_sParams.b*PID_sParams.previous_error) /10;
  	  
  	  if(PID_iterm<=0)
  	  {
	  	  PID_iterm=0;
	  }
	  else if(PID_iterm>=PID_sParams.outmax)
	  {
		  PID_iterm=PID_sParams.outmax;
	  }
	  
  	  PID_dterm = (PID_sParams.c*(PID_sParams.previous_error-PID_sParams.pprevious_error)) /10;
  	  
  	  PID_sParams.output = PID_pterm+PID_iterm+PID_dterm;
  	  
  	 }
  	  
  	  if(PID_sParams.output <= 0)
        {
            PID_sParams.output=0;
        }
        else if(PID_sParams.output>=PID_sParams.outmax)
        {
            PID_sParams.output=PID_sParams.outmax;
        }
    
    
    PID_sParams.pprevious_error=PID_sParams.previous_error;
	PID_sParams.previous_error = PID_sParams.error;
	
	scaled_output=(PID_sParams.output>>imfvalue);
	newpwm=scaled_output;
	//OC2RS=newpwm;
	//PWMcount1=rsetcurrent*14.0;
	//if(PWMcount1 >= 2940)
	//PWMcount1=2940;
	//OC2RS=PWMcount1;
	
	if((MIGweldon_detectf==0) && (PID_sParams.error<0))
	{
    	newpwm=200;
	}	  
	else
	{
		if(1)//sf_error>=0)  
	    {
		    if(newpwm<=iLowpidvalue) //20) 
			newpwm=iLowpidvalue; //20;
			if(newpwm>=500)
			newpwm=500;
	    	migdaccount2=newpwm;
	    }
	}
	
} 

void superfast_pid()
{
	unsigned int i_factor=1;

	sf_scalefactor=6;
 	sf_outputmax=64000; //32000;
	sf_kpgain=iKp;  //25; //150;//25;//75;//64;
	sf_kigain=iKi;  //10; //2
	sf_kdgain=iKd; //10; //8
	
	//mult_factor=10; //20;
    sf_setpoint=rsetvoltage;
	sf_feedback=actual_voltage; //weldvoltage;
	
	sf_error=(sf_setpoint-sf_feedback);
	
	if(sf_feedback <= 150) 
		sf_pterm=(sf_kpgain*sf_error)/10;//*imfvalue
	else	
		sf_pterm=(sf_kpgain*sf_error)/10;
		
	
	if(pidfg==1)
	{
		pidfg=0;
		MPWMLAT = 1;
	}
	else
	{
		pidfg=1;
		MPWMLAT = 0;		
	}
	
	sf_accumulator+=((sf_error*sf_kigain)/10);

	
	if(sf_accumulator>= sf_outputmax)
	{
		sf_accumulator= sf_outputmax;
	}
	else if(sf_accumulator <= sf_outputmin)
	{
		sf_accumulator= sf_outputmin; 
	}
	
	sf_iterm=sf_accumulator;
				
	sf_dterm=(((sf_error-sf_preverror)*sf_kdgain)/10);
	sf_preverror=sf_error;
    sf_pid=sf_pterm+sf_iterm+sf_dterm;
    	
	if(sf_pid>=sf_outputmax)
	{
	   sf_pid=sf_outputmax;	
	}
	else if(sf_pid<=sf_outputmin)
	{
	   sf_pid=sf_outputmin;
	}
	
	if(sf_feedback <= 150) 
	{
		sf_pid =(sf_pid*imfvalue/10);
//		sf_prevpid=sf_pid;
	}
	else
	{	
		sf_pid =(sf_pid);  //sf_pid =(sf_pid)
	}
	sf_pidoutput=sf_pid>>sf_scalefactor;    //sf_pidoutput is used in isr
	
	if(MIGweldon_detectf==0)
	{
    	migdaccount1=200;
	}	  
	else
	{	
		if(1)
	    {
		    if(sf_pidoutput<=iLowpidvalue) //20) 
			sf_pidoutput=iLowpidvalue; //20;    //iLowpidvalue
			if(sf_pidoutput>=500)
			sf_pidoutput=500;
    		migdaccount2=sf_pidoutput;
		}  
	}
}
