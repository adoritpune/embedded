
void mig()
{
	if(mig_flag==0)
	{
		TypeDP.DPGROUP[0]=0x00;
		CURR[0]='M';
		CURR[1]='I';
		CURR[2]='G';
		CURR[3]=91;          //-
		VOLT[0]='M';
		VOLT[1]='O';
		VOLT[2]='D';
		VOLT[3]='E';
		mma_flag=0;
		saw_flag=0;
		mig_flag=1;
		mma_init=0;
		CCCVLAT=CVMODE;				//CCCV MODE SELECTION IN PWM CARD 
		MMALEDLAT=0;
		SAWLEDLAT=1;
		count_10ms=0;
		count_100ms=0;
		ARCONLAT=0;					//ARCON OUTPUT SIGNAL TO PWM PCB
		OCV_FLAGLAT=0;
		GASRELAYIO=0;
		GASRELAYLAT=0;
		Disp_updatef=1;
		disp_calf=0;
	}
	else if(trip_flag==0 && mig_flag==1 &&  mma_init==1)
	{
		if(cyclestrt==0)									//Welding off
		{
			TypeDP.DPGROUP[0]=0x00;
      		Typedp.digitdp3		=1;
			Typedp.digitdp7		=1;
			if((prsetcurrent!=rsetcurrent) || Disp_updatef==1)                    
			{
				disp_hex_dec_curr(rsetcurrent);
				prsetcurrent=rsetcurrent;
			}
			if((prsetvoltage!=rsetvoltage) || Disp_updatef==1)
			{
				disp_hex_dec_volt(rsetvoltage);
				prsetvoltage=rsetvoltage;
			}
			welding_flag=0;
			GASRELAYLAT=0;
			OCV_FLAGLAT=0;             	// OCV OFF
			ARCONLAT=0;			   	//ARCON OUTPUT SIGNAL TO PWM PCB
			CCCVLAT=CVMODE;		//CV MODE SELECTION IN PWM CARD 
			motorerrcnt=0;
			//comm_flag=0;
			OC1RS=0;                      	//REFERENCE ZERO AT NO WELDING
			//Disp_updatef=0;
			prsetcurrent=0x1FFF;			//8191
			prsetvoltage=0x1FFF;			//8191			
		}
		else if(cyclestrt==1)
		{
			TypeDP.DPGROUP[0]=0x00;
      		Typedp.digitdp7		=1;
			if(((pdispweldcurrent != dispweldcurrent)  && disp_flag==1))	// || Disp_updatef==1)		//AFTER EVERY 1 SEC
			{
				disp_hex_dec_curr(dispweldcurrent);               //DISPLAY ARC CURRENT
				pdispweldcurrent = dispweldcurrent;
			}   
			//disp_hex_dec_volt(mvoltage);  
			if((pweldvoltage != weldvoltage) && disp_flag==1)     //AFTER EVERY 1 SEC
			{
				disp_hex_dec_volt(weldvoltage);                   //DISPLAY ARC VOLTAGE
				pweldvoltage = weldvoltage;
			}
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
		TRIPLEDLAT=1;
		phsetcurrent=0;
		phsetvoltage=0;
		 if(imtrip_flag==1)
        {
          		while(imtrip_flag==1); 
        
        }
		
		
	}
	
}

void torchaction()
{
		if(cyclestrt==0)
		{
			oper=pre;
		}
		if(Torchmode=='2')
		{
			switch(oper)
			{
				case pre:
				{
					if(cyclestrt==0)
					{
						cyclestrt	=1;
						GASRELAYLAT	=1;				//GAS ON RELAY.
						OCV_FLAGLAT	=1;          	//OCV ON
						ARCONLAT	=1;				//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;		//CV MODE SELECTION IN PWM CARD
						genref(rsetvoltage);		//generate reference
						drivemotor(rsetcurrent);
						motoronf	=1;
						motorerrcnt=0;
						oper=weld;
					}
					break;
				}		
				case weld:
				{
					oper=weld;
					if(Torchkey=='R')
					{
						motoronf		=0;
						OC2RS			=0;			//drivemotor(0);
						burnbackcnt		=0;
						oper			=burn;
					}
					else 
					{
						genref(rsetvoltage);			//generate reference
						drivemotor(rsetcurrent);
					}
					break;
				}
				case burn:
				{
					if(burnbackcnt >=20)
					{
						GASRELAYLAT	=0;			//GAS ON RELAY.
						OCV_FLAGLAT	=0;          	// OCV OFF
						ARCONLAT		=0;			//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;	//CV MODE SELECTION IN PWM CARD
						genref(0);					//generate reference
						oper=exit1;
					}
					else
					{
						OC2RS=0;					//drivemotor(0);drivemotor(0);
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
					motortrip		=0;
					//trans('E');
					genref(0);					//generate reference
					OC2RS=0;					//drivemotor(0);drivemotor(0);
					oper=pre;
					motoronf		=0;
					break;
				}
			}//end ig switch
		}//2T mode

		else if(Torchmode=='4')
		{
			switch(oper)
			{
				case pre:
				{
					if(cyclestrt==0)
					{
						cyclestrt		=1;
						GASRELAYLAT	=1;				//GAS ON RELAY.
						OCV_FLAGLAT	=1;          		//OCV ON
						ARCONLAT		=1;				//ARCON OUTPUT SIGNAL TO PWM PCB
						CCCVLAT		=CVMODE;		//CV MODE SELECTION IN PWM CARD
						torchrelease		=0;
						crateron		=0;
						genref(rsetvoltage);			//generate reference
						OC2RS=0;	
						oper=weld;
						motorerrcnt=0;
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
							genref(rsetvoltage);							//generate reference
							drivemotor(rsetcurrent);
						}
						else if(Torchkey=='R' && torchrelease==1 && crateron==0)		//VOLTAGE ON, WIRESPEED ON
						{
							oper=weld;
							genref(rsetvoltage);							//generate reference
							drivemotor(rsetcurrent);						//generate reference
						}
						else if(Torchkey=='P' && torchrelease==1 && crateron==0)		// && Type.crateron==0)//TORCH PRESSED AGAIN CRATER FUNCTION
						{
							oper=weld;
							genref(rsetvoltage*0.75);							//generate reference
							motoronf	=0;
							OC2RS		=0;									//drivemotor(rsetcurrent*0.75);	
							burnbackcnt	=0;
							crateron=1;	
						}	
						else if(Torchkey=='R' && torchrelease==1 && crateron==1)		// && Type.crateron==0)//TORCH PRESSED AGAIN CRATER FUNCTION
						{
							oper		=burn;
							genref(0);									//rsetvoltage*0.75);							//generate reference
							OC2RS=0;	
							burnbackcnt	=0;
							oper		=burn;
						}
						break;
					}
					case burn:
					{
						if(burnbackcnt >=20)
						{
							GASRELAYLAT	=0;			//GAS ON RELAY.
							OCV_FLAGLAT	=0;          	// OCV OFF
							ARCONLAT		=0;			//ARCON OUTPUT SIGNAL TO PWM PCB
							CCCVLAT		=CVMODE;	//CV MODE SELECTION IN PWM CARD
							genref(0);					//generate reference
							OC2RS			=0;
							oper			=exit1;
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
						break;
					}
			}
		}		
}			
void genref(unsigned int setvtg)
{
	PWMcount=20.88 + (setvtg *5.22) ;
	if(PWMcount >= 2940)
	PWMcount=2940;
	OC1RS= PWMcount;	
}
void drivemotor(unsigned int wspeed)
{
	//PWMcount1=wspeed*9.0;
	//if(PWMcount1 >= 2940)
	//PWMcount1=2940;
	//OC2RS= PWMcount1;
	refmotorvtg=(wspeed * 2.11);//wspeed

	//if(wspeed>0)
	//OC2RS=newpwm;					//para.migmode.setwspeed*10.0;	
	//else
	//OC2RS=0;	
}

void second_order_pid()
{
    static unsigned int scalefactor=0,scaled_output=0;	//,maxmpwm=2500;
    PID_sParams.ReferenceSetpoint=mvoltage;				//mfreq;
    PID_sParams.feedback=refmotorvtg;					//rsetcurrent * 2.11;//setwsfreq;
    PID_sParams.error = PID_sParams.feedback - PID_sParams.ReferenceSetpoint ;
    PID_sParams.absolute_error=abs(PID_sParams.error);
    PID_sParams.a=2.0;//5;
    PID_sParams.b=1.0;//0.1;
    PID_sParams.c=1.0;//0.5;
    //PID_sParams.d=1000;
    PID_sParams.outmax=10000;
    scalefactor=4.0;		//PID_sParams.outmax/maxmpwm;
    PID_sParams.derivitive = PID_sParams.error - PID_sParams.previous_error;
    if((PID_sParams.error > 0.5) || (PID_sParams.error < -0.5))
    {
        PID_sParams.output=PID_sParams.output +((PID_sParams.a*PID_sParams.error))+ (PID_sParams.b*PID_sParams.previous_error) + (PID_sParams.c*PID_sParams.pprevious_error);
  	  if(PID_sParams.output <= 0)
        {
            PID_sParams.output=0;
        }
        else if(PID_sParams.output>PID_sParams.outmax)
        {
            PID_sParams.output=PID_sParams.outmax;
        }
    }
      PID_sParams.pprevious_error=PID_sParams.previous_error;
	PID_sParams.previous_error = PID_sParams.error;
	scaled_output=(PID_sParams.output/scalefactor);
	newpwm=scaled_output;
	OC2RS=newpwm;
	//PWMcount1=rsetcurrent*14.0;
	//if(PWMcount1 >= 2940)
	//PWMcount1=2940;
	//OC2RS=PWMcount1;
}   
