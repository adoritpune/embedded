void MIGWELD(void)
{
	if(modechangef==1)
	{
		Typedp.digitdp2=0;
		diswin1[0]='M';
		diswin1[1]='I';
		diswin1[2]='G';
		diswin2[0]='M';
		diswin2[1]='O';
		diswin2[2]='D';
				
		for(j=0;j<200;j++)
		for(i=0;i<10000;i++);
		Type.mig=1;
		modechangef=0;
		
		dispupdatef=1;
		GAS_RELAYLAT	= 0;
		SHDNLAT=0;//1;			//OCV OFF
		
		memoryzone='X';
		eedata=weldmode;//3456;							
		EEPROM_Erase_Write((0*2),eedata);

        eedata=EEPROM_Read(5*2); //PPC
		if((eedata <= 0)|| (eedata >= 100))
		{
			eedata = 10;
		}	
		vOffset = eedata;        
				
		TypeDP.DPGROUP[0]=0x00;
		Typedp.digitdp5		= 1;
		Typedp.digitdp2		= 1;
		TypeU.LEDGROUP[0] =0x00;
		Type.wirespeed      = 1;
		Type.current		= 0;
		Type.voltage        = 1;
		Type.mig 			= 1;
		Type.twot			= 1;  
				
		read_current_status();
		check_eeprom_values();
						
		
		prev_weldmode=weldmode;
		prev_eeprom_mig_struct=EEPROM_struct_mig.EEPROM_struct_u;

		read_gpreflow=mig_preflow;   				//2
		read_gburnback=mig_burnback;				//7
		read_gpostflow=mig_postflow;				//10
		prevcreepspeedrate=mig_creepspeedrate;		//12
		read_gcreepspeedtime=mig_creepspeedtime;	//14

	}
//--------------------------------------------------------------------------------------------------------
    if(gaschkfg == 1)
    {
        disp_hex_dec_volt(igascntr);
    } 		
						
	if(weldcyclestrt == 0)
	{		
		INCHIO = 1;
		if(INCH == 0) //INCH
		{
			diswin1[0]='I';
			diswin1[1]='N';
			diswin1[2]='C';
			
			Typedp.digitdp5		=1;
			Typedp.digitdp2		=0;
			
			cInchLatchfg=1;
			disp_hex_dec_volt(inchcntr*10.0);
					
			inch_motor(inchcntr*10.0);
			
			for(i=0;i<50;i++)
			for(j=0;j<40000;j++);
			inchcntr++;
			
			if(inchcntr>=10)	//(IRcurr/10)) //10					
			inchcntr=10;		//(IRcurr/10);	 //10				
		}
		else if(INCH == 1)
		{	
			if(cInchLatchfg == 1)
			{			
				inchcntr=0;
				inch_motor(0);
				cInchLatchfg=0;
			}		
		}
	}
//--------------------------------------------------------------------------------------------------------
	if((weldcyclestrt == 0) && (cMIGParaMenufg == 0) && (cGaSMenufg == 0)&& (cVoltageoffsetfg==0))// && (cModeSelectDonefg == 0))// && (universal_error_flag == 0))// && (cMotorTripfg == 0))  
	{
		GAS_RELAYLAT	= 0;			//TO CONTROL THE GAS SOLENOID VALVE
		SHDNLAT			= 0;//1;			//OCV OFF @SBM
		
		softstartcnt	= 0;
		softstartf		= 0;
		dispupdatef		= 0;
		Typedp.digitdp5	= 1;
		Typedp.digitdp2	= 1;
	
		MIGweldon_detectf=0;
		sf_accumulator_new = 0;		
		sf_accumulator=0;
		motor_integral_acc=0;
	
		if(weldingonf==1)//@AFTER COMPLETING OF WELDING
		{
			
			weldingonf=0;
			memoryzone='G';	
			
			write_current_status();
		}
	
		if(((cMigVtgUpdatefg == 1) || (dispupdatef==1)) && (cCraterdispfg == 0))
		{	
			//iVoltage=150;
			//disp_hex_dec_volt(iInductance);
			disp_hex_dec_volt(iVoltage);//iInductance);//iVoltage); //iWireSpeed);//iVoltage);
		}
		if(((cMIGWSUpdatefg == 1) || (dispupdatef==1))&&(cCraterdispfg == 0))
		{
			//sf_kpgain =(mig_Kp*10) - ((iInductance - 50)/2); 					
			//disp_hex_dec_curr(sf_kpgain);
			disp_hex_dec_curr(iWireSpeed);//IRcurr);//iWireSpeed);//iWireSpeed);
		}
		//Added to display Crater WS & voltage
		if((cCraterdispfg == 1) && (Type.fourt==1))
        {
            disp_hex_dec_volt(iCraterVtg);      //crater voltage
            disp_hex_dec_curr(iCraterWS);     //crater current
           // setdp=1;
           // setdp1=4;
            if(iCraterdisptime>=2000)
            {
            	cCraterdispfg=0;
            }
        }
		cMigVtgUpdatefg = 0;
		cMIGWSUpdatefg = 0;
		dispupdatef = 0;
	}
//--------------------------------------------------------------------------------------------------------	
	if(cMigWeldparaupdatefg == 1)
	{	
		if(cVoltoffMenuMode == 1) 
		{
			if(vOffset <= 4)
			{
				vOffset = 4;
			}
			else if(vOffset >= 20)
			{
				vOffset = 20;
			}
			disp_hex_dec_volt(vOffset);
			
			//if(cEEPROMSavefg == 0)
			//{
				EEPROM_Erase_Write((5*2),vOffset);
				cEEPROMSavefg = 1;
			//}
		
	
		if(cVoltoffMenuMode == 2) 
		 {
			if(vOffsetmax <= 390)
			{
				vOffsetmax = 390;
			}
			else if(vOffsetmax >= 415)
			{
				vOffset = 415;
			}
			disp_hex_dec_volt(vOffsetmax);
			
			//if(cEEPROMSavefg == 0)
			//{
				EEPROM_Erase_Write((5*2),vOffsetmax);
				cEEPROMSavefg = 1;
			//}
		  }
	    
	 
		if(cMIGMenuMode == 1) 
		{
			if(mig_preflow <= 0)
			{
				mig_preflow = 0;
			}
			else if(mig_preflow >= 10)
			{
				mig_preflow = 10;
			}
			disp_hex_dec_volt(mig_preflow);
		}
		if(cMIGMenuMode == 2) 
		{			
			if(mig_burnback <= 0)
			{
				mig_burnback = 0;
			}
			else if(mig_burnback >= 200)
			{
				mig_burnback = 200;
			}
			disp_hex_dec_volt(mig_burnback);
		}
		if(cMIGMenuMode == 3) 
		{
			if(mig_postflow <= 0)
			{
				mig_postflow = 0;
			}
			else if(mig_postflow >= 10)
			{
				mig_postflow = 10;
			}
			disp_hex_dec_volt(mig_postflow);
		}
		if(cMIGMenuMode == 4) 
		{	
			if(mig_creepspeedrate <= 10)
			{
				mig_creepspeedrate = 10;
			}
			else if(mig_creepspeedrate >= 100)
			{
				mig_creepspeedrate = 100;
			}
			disp_hex_dec_volt(mig_creepspeedrate);
		}
		if(cMIGMenuMode == 5) 
		{
			if(mig_creepspeedtime <= 1)
			{
				mig_creepspeedtime = 1;
			}
			else if(mig_creepspeedtime >= 100)
			{
				mig_creepspeedtime = 100;
			}
			disp_hex_dec_volt(mig_creepspeedtime);	
		}
		if(cMIGMenuMode == 6) 
		{
			if(mig_Kp <= 1)
			{
				mig_Kp = 1;
			}
			else if(mig_Kp >= 900)
			{
				mig_Kp = 900;
			}
			disp_hex_dec_volt(mig_Kp);
		}		
		if(cMIGMenuMode == 7) 
		{
			if(mig_Ki <= 1)
			{
				mig_Ki = 1;
			}
			else if(mig_Ki >= 100)
			{
				mig_Ki = 100;
			}
			disp_hex_dec_volt(mig_Ki);
		}
		if(cMIGMenuMode == 8) 
		{
			if(mig_Kd <= 1)
			{
				mig_Kd = 1;
			}
			else if(mig_Kd >= 300)
			{
				mig_Kd = 300;
			}
			disp_hex_dec_volt(mig_Kd);
		}
		if(cMIGMenuMode == 9) 
		{
			if(mig_Ka<= 1)
			{
				mig_Ka = 1;
			}
			else if(mig_Ka >= 900)
			{
				mig_Ka = 900;
			}
			disp_hex_dec_volt(mig_Ka);
		}
		if(cMIGMenuMode == 10) 
		{
			if(mig_Kb <= 1)
			{
				mig_Kb = 1;
			}
			else if(mig_Kb >= 900)
			{
				mig_Kb = 900;
			}
			disp_hex_dec_volt(mig_Kb);
		}		
		if(cMIGMenuMode == 11) 
		{
			if(mig_Kc <= 0)
			{
				mig_Kc = 0;
			}
			else if(mig_Kc >= 100)
			{
				mig_Kc = 100;
			}
			disp_hex_dec_volt(mig_Kc);
		}										
		cMigWeldparaupdatefg = 0;
	}
//--------------------------------------------------------------------------------------------------------
	if((TORCH_SW =='T') || (weldcyclestrt == 1))		//welding started
	{
		dispupdatef=1;
		weldingonf=1;
		
		Type.wirespeed 	= 0;
		Type.current	= 1;
		
		Typedp.digitdp2	= 0;
		
		if(cGaSMenufg == 1)
		{
			igascntr = 0;
			cGaSMenufg = 0;
			oper = pre;	
		}		
		
		if((oper==pre) && (igascntr == 0))
		{
			SHDNLAT=0;//1;	

			Typedp.digitdp5	= 0;
			diswin1[0]='P';
			diswin1[1]='R';
			diswin1[2]='E';
			disp_hex_dec_volt(mig_preflow);	
			
			if(0)//(iCreepSpeedDowncnt == 0) && (cCreepEndfg == 1) && (cMotorStopfg == 0) && (cCreepKifg == 1))
			{
				cCreepKifg = 0;	
				//Generate_Reference(IRcurr);	
				//Generate_Reference_for_4T(IRcurr);
			}			
		}
		else if(oper==weld)
		{
			SHDNLAT=1;//0;			
	
			Typedp.digitdp5	= 1;
 
//			disp_hex_dec_curr(iRefmvtg);
			disp_hex_dec_curr(CURRENT);//);
//			disp_hex_dec_curr(iTest1);
			disp_hex_dec_volt(VOLTAGE);
		
			if(Type.twot==1)    //2T MODE
			{
				SHDNLAT=1;//0;
				if((cMIGWSUpdatefg == 1) && (cMotorStopfg == 0) && (cCreepLatchfg == 0))
				{								
					Generate_Reference(iWireSpeed);
				}				
				cMIGWSUpdatefg=0;								
			}
			else
			{
				if(torchrelease==1 && cratersetup==0)
				{
					if((cMIGWSUpdatefg == 1) && (cMotorStopfg == 0) && (cCreepLatchfg == 0))
					{								
						Generate_Reference(iWireSpeed);
					}				
					cMIGWSUpdatefg=0;					
				}
				else if(torchrelease==1 && cratersetup==1)
				{
					if(cCraterWSUpdatefg == 1)
					{
						Generate_Reference(iCraterWS);
					}
					if(cCraterVtgUpdatefg == 1)
					{
						iVoltage=iCraterVtg;
						Generate_DAC_Reference(iVoltage);	 	
					}						
					cCraterVtgUpdatefg = 0;					
					cCraterWSUpdatefg 	= 0;
				}	
			}   
		}
		else if(oper==burn)
		{
			Typedp.digitdp4	= 1;
			diswin1[0]='B';
			diswin1[1]='R';
			diswin1[2]='N';
			disp_hex_dec_volt(mig_burnback);	        

		}
		else if(oper==post)
		{
			SHDNLAT=0;//1;
				
			Typedp.digitdp4	= 0;
			Typedp.digitdp5	= 0;	
			Typedp.digitdp2	= 0;
			diswin1[0]='P';
			diswin1[1]='S';
			diswin1[2]='T';
			disp_hex_dec_volt(mig_postflow);			   
		}
	}			
}

void cMIGGasMenu(void)
{
	Typedp.digitdp5	= 0;
	Typedp.digitdp2	= 0;
	
	diswin1[0]='G';
	diswin1[1]='A';
	diswin1[2]='S';

	disp_hex_dec_volt(igascntr);
    GAS_RELAYLAT = 1;
    dispupdatef  = 1;
}

void cVoltageoffsetMenu(void)
{
	Typedp.digitdp5	= 0;
	Typedp.digitdp2	= 0;
	
	diswin1[0]='O';
	diswin1[1]='F';
	diswin1[2]='F';

	disp_hex_dec_volt(vOffset);    
    dispupdatef  = 1;
    /*if(cMMAMenuMode == 1)
	{		
		diswin1[0]='O';
		diswin1[1]='F';
		diswin1[2]='T';
	}*/
}

void cMIGMenu(void)
{
	Typedp.digitdp5	= 0;
	Typedp.digitdp2	= 0;

	if(cMIGMenuMode==1)
	{
		diswin1[0]='P';
		diswin1[1]='R';
		diswin1[2]='E';	
	}
	if(cMIGMenuMode==2) 
	{
		Typedp.digitdp4	= 1;
		diswin1[0]='B';
		diswin1[1]='R';
		diswin1[2]='N'; 	
	}
	if(cMIGMenuMode==3) 
	{	
		Typedp.digitdp4	= 0;
		diswin1[0]='P';
		diswin1[1]='S';
		diswin1[2]='T';	
	}
    if(cMIGMenuMode==4) 
    {
	    Typedp.digitdp4	= 0;
		diswin1[0]='C';
		diswin1[1]='R';
		diswin1[2]='S';	
    }
    if(cMIGMenuMode==5) 
    {
		Typedp.digitdp5	= 0;
		Typedp.digitdp2	= 0;
	    Typedp.digitdp4	= 0;
		diswin1[0]='C';
		diswin1[1]='R';
		diswin1[2]='T';	
    }
	if(cMIGMenuMode==6) 
	{	
		Typedp.digitdp4	= 0;	
		diswin1[0]='M';
		diswin1[1]='K';
		diswin1[2]='P';
	}    
	if(cMIGMenuMode==7) 
	{	
		Typedp.digitdp4	= 0;	
		diswin1[0]='M';
		diswin1[1]='K';
		diswin1[2]='I';
	}	
    if(cMIGMenuMode==8) 
    {	   
	    Typedp.digitdp4	= 0; 
		diswin1[0]='M';
		diswin1[1]='K';
		diswin1[2]='D';
    }  
    if(cMIGMenuMode==9) 
    {	   
	    Typedp.digitdp4	= 0; 
		diswin1[0]='M';
		diswin1[1]='K';
		diswin1[2]='A';
    }  
    if(cMIGMenuMode==10) 
    {	   
	    Typedp.digitdp4	= 0; 
		diswin1[0]='M';
		diswin1[1]='K';
		diswin1[2]='B';
    }          	
    if(cMIGMenuMode==11) 
    {	   
	    Typedp.digitdp4	= 0; 
		diswin1[0]='M';
		diswin1[1]='K';
		diswin1[2]='C';
    }    
}

/*
void Generate_DAC_Reference(unsigned int iReference)
{												
	if(iReference != 0)
	{	
		SHDNLAT			=0;								//OCV ON @SBM
		if(cStartPulsefg == 1)
		{												
	    	if(SPI2STATbits.SPITBF==0)
			{
				DACCSLAT	=0;
				//MIGCVSLOPE400=mig_Kd/10;		
				daccount   =(iStartCurr*MIGCVSLOPE400)-MIGCVOFFSET400;	
				if(daccount >= 4095)
					daccount = 4095;
				//daccount   =(iStartCurr*MIGCVSLOPE400) - mig_Kb;//MIGCVOFFSET400;		  								
				SPI2BUF		=28672+daccount;
			}				
		}
		else if(cEndPulsefg == 1)
		{  					
	    	if(SPI2STATbits.SPITBF==0)
			{
				DACCSLAT	=0;
				//MIGCVSLOPE400=mig_Kd/10;
				daccount   =(iEndPulseCurr*MIGCVSLOPE400)-MIGCVOFFSET400;
				if(daccount >= 4095)
					daccount = 4095;				
				//daccount   =(iEndPulseCurr*MIGCVSLOPE400) - mig_Kb;//MIGCVOFFSET400;		  								
				SPI2BUF		=28672+daccount;
			}				
		}				
    	else if((cStartPulsefg == 0) && (cEndPulsefg == 0))
    	{
	    	if(SPI2STATbits.SPITBF==0)
			{
				DACCSLAT	=0;
				//MIGCVSLOPE400=mig_Kd/10;
				daccount   =(migdaccount*MIGCVSLOPE400) - MIGCVOFFSET400;
				if(daccount >= 4095)
					daccount = 4095;						  								
				//daccount   =(migdaccount*MIGCVSLOPE400) - mig_Kb;//MIGCVOFFSET400;		  								
				if(1)//cLockDACreffg == 1)
				{		  				
					SPI2BUF		=28672+daccount;     	
				}
			}	
		}
	}
	else
	{
		SHDNLAT	= 1;												
	       						    
    	if(SPI2STATbits.SPITBF == 0)
		{
			DACCSLAT	= 0;
			daccount	= 10;
			if(1)//cLockDACreffg == 1)
			{
				SPI2BUF	= 28672+daccount;     		
			}	
		}						
	}	
}
*/

/*void Generate_Reference(unsigned int iGenerate_ref_pwm)
{
	unsigned int iRef_pwm_new_result=0;	
	if(cCraterLatchfg == 0) 
	{
		iTest1 = iGenerate_ref_pwm;
		
		if(cMotorStopfg == 1) 
		{
			iRef_pwm_new_result = 0;
		}
		else
		{
			iRef_pwm_new_result = (iGenerate_ref_pwm * MTR_PWM_SLOPE) + MTR_PWM_OFFSET;
		}
			
		iRefmvtg = iRef_pwm_new_result;			
		
		if(1)//cPWMLockfg == 1)
		{
			OC4RS = iRefmvtg;
		}							
	}
	else
	{									
		iRef_pwm_new_result = (iGenerate_ref_pwm * MTR_PWM_SLOPE) + MTR_PWM_OFFSET;
		if(cMotorStopfg == 1) 
		{
			iRef_pwm_new_result = 0;
		}
		iRefmvtg = iRef_pwm_new_result;							
		if(1)//cPWMLockfg == 1)
		{
			OC4RS = iRefmvtg;
		}			
	}
iTest1 = iRefmvtg;
}
*/

void Generate_Reference(unsigned int iGenerate_ref_pwm)
{
	  unsigned int iRef_pwm_new_result=0;	
    //iRef_pwm_new_result = (iGenerate_ref_pwm * MTR_PWM_SLOPE) + MTR_PWM_OFFSET;
    //iRefmvtg = iRef_pwm_new_result;	

	if(cCraterLatchfg == 0) 
	{
		iTest1 = iGenerate_ref_pwm;
		
		if(cMotorStopfg == 1) 
		{
			iRef_pwm_new_result = 0;
		}
		else
		{
			if(iGenerate_ref_pwm <=28)
			{
				
			    iRef_pwm_new_result = (iGenerate_ref_pwm * 8.4) + 1;	
			}
			else if( iGenerate_ref_pwm >=28 && iGenerate_ref_pwm <=75)
			{
				
			    iRef_pwm_new_result = (iGenerate_ref_pwm * 8.0) + 1;	
			}
			else if( iGenerate_ref_pwm >=76 && iGenerate_ref_pwm <=110)
			{
				
			    iRef_pwm_new_result = (iGenerate_ref_pwm * 5.8) + 1;	
			}
			else
			{
				iRef_pwm_new_result = (iGenerate_ref_pwm * MTR_PWM_SLOPE) + MTR_PWM_OFFSET;
			}
		}
			
		iRefmvtg = iRef_pwm_new_result;			
		
		if(1)//cPWMLockfg == 1)
		{
			OC4RS = iRefmvtg;
		}							
	}
	else
	{									
	    	if(iGenerate_ref_pwm <=28)
			{
				
			    iRef_pwm_new_result = (iGenerate_ref_pwm * 8.4) + 1;	
			}
			else if( iGenerate_ref_pwm >=28 && iGenerate_ref_pwm <=75)
			{
				
			    iRef_pwm_new_result = (iGenerate_ref_pwm * 8.0) + 1;	
			}
			else if( iGenerate_ref_pwm >=76 && iGenerate_ref_pwm <=110)
			{
				
			    iRef_pwm_new_result = (iGenerate_ref_pwm * 5.8) + 1;	
			}
			else
			{
				iRef_pwm_new_result = (iGenerate_ref_pwm * MTR_PWM_SLOPE) + MTR_PWM_OFFSET;
			}
		
		
		if(cMotorStopfg == 1) 
		{
			iRef_pwm_new_result = 0;
		}
		iRefmvtg = iRef_pwm_new_result;							
		if(1)//cPWMLockfg == 1)
		{
			OC4RS = iRefmvtg;
		}			
	}
    iTest1 = iRefmvtg;
}


void inch_motor(unsigned int inch_pwm)
{	
	if(inch_pwm == 0)	
	{
		OC4RS = 0;
	}
	else
	{
		OC4RS = (inch_pwm * MTR_PWM_SLOPE) + MTR_PWM_OFFSET;
	}			
}	


void motor_control_pid(void)               //Motor control PID loop
 {
	
	signed int iPterm,iIterm,iDterm;
	
	Kp=1;
	Ki=1;
	Kd=1;
		
	//iFBmvtg=(iFBMotorvtg/MTR_FB_SLOPE) + MTR_FB_OFFSET;
	
	
	float iMigKp;
	unsigned int iMototFBvtg;
	iMigKp = MTR_FB_SLOPE;
	iMigKp = iMigKp/100;
	iMigKp = iFBMotorvtg / iMigKp;
	iMototFBvtg = (unsigned int) iMigKp;
	iFBmvtg = iMototFBvtg + MTR_FB_OFFSET;
	
	ReferenceSetpoint = iRefmvtg;
	FeedbackSetpoint  = iFBmvtg;
		
	error1 = iRefmvtg - iFBmvtg;
		
	outmax = 30000;
	outmin = -30000;
		
	motor_integral_acc+=error1;
			
	if(motor_integral_acc >= outmax)
	{
		motor_integral_acc = outmax;
	}
	else if(motor_integral_acc <= outmin)
	{
		motor_integral_acc = outmin;
	}
	
	iPterm = Kp*error1;	
	
	iIterm = motor_integral_acc;
	
	iDterm = Kd*(error1-error_old);
	
	error_old = error1;
		
	pidoutput = iPterm + iIterm + iDterm;
		  
		
	scalefactor = 10;
	scaled_val=pidoutput;
	scaled_val=(scaled_val/scalefactor);
	
	if(scaled_val <= -900)
		scaled_val = -900;
	if(scaled_val >= 900)
		scaled_val = 900; 
		
	OC4RS = iRefmvtg + scaled_val;
	
	if(OC4RS >= 2400)
		OC4RS = 2400;
		
//For PMDC motor set 18v for 10 mtr/min and for print set 19v for 18mtr/min		
}

/*
void MIG_superfast_PID(void)
{
 	sf_outputmax=64000;	
 	   
	if((cCreepKifg == 1) && (cCreepSpeedDowncntfg == 1))
	{
		sf_kpgain = MIG_Kp;//mig_Kp; 
		sf_kigain = MIG_Ki;//mig_Ki;
		sf_kdgain = MIG_Kd;//mig_Ka;
	}
	else if((cInductanceUpdatefg == 1) && (cCreepKifg == 0)) 
	{
		if((iInductance >= 0) && (iInductance < 50))
		{
			//TRIP_LEDLAT=1;
			sf_kpgain =	MIG_Kp - ((iInductance - 50)/ 2);
			sf_kigain = MIG_Ki;										
			sf_kdgain = MIG_Kd;										
		}
		else if((iInductance > 50) && (iInductance <= 100))
		{
			//TRIP_LEDLAT=1;
			sf_kpgain =	MIG_Kp + ((50 - iInductance) / 2);
			sf_kigain = MIG_Ki;		
			sf_kdgain = MIG_Kd;
		}
		else if(iInductance == 50)
		{
			//TRIP_LEDLAT=0;
			sf_kpgain =	MIG_Kp; 			//30
			sf_kigain = MIG_Ki;			 	//1.3
			sf_kdgain = MIG_Kd;      		//1
		}	
		cInductanceUpdatefg=0;		
	}
		
	sf_setpoint = iVoltage;
 	sf_feedback = ACT_CVOLTAGE + 40;
 	
	sf_error=sf_setpoint-sf_feedback;

if(0)//iWireSpeed <= 45)
{
	sf_pterm=sf_kpgain*sf_error/10;
	
	sf_accumulator+=sf_error*sf_kigain/10;	

	if(sf_accumulator>=sf_outputmax)
		sf_accumulator=sf_outputmax;
	else if(sf_accumulator<=sf_outputmin)
		sf_accumulator=sf_outputmin;
	
	sf_iterm = sf_accumulator;
 
	sf_dterm=sf_kdgain*(sf_error-sf_preverror);
	
	sf_preverror=sf_error;
	
	sf_pid=sf_pterm+sf_iterm+sf_dterm;
	
	if(sf_pid>=sf_outputmax)
		sf_pid=sf_outputmax;
	else if(sf_pid<=sf_outputmin)
		sf_pid=sf_outputmin;
		
	sf_pidoutput=sf_pid>>sf_mig_scalefactor;   //	//2
	//sf_pidoutput=sf_pid/6;	//sf_mig_scalefactor
	
	if(sf_pidoutput<=20)
	sf_pidoutput=20;
	if(sf_pidoutput>=500)
	sf_pidoutput=500; 
}
else
{
	 sf_pterm=sf_kpgain*sf_error;
	 
	 sf_accumulator+=sf_error;
	 
	 if(sf_accumulator>=sf_outputmax)
	 	sf_accumulator=sf_outputmax;
	 else if(sf_accumulator<=sf_outputmin)
	 	sf_accumulator=sf_outputmin;
	 
	 sf_iterm = sf_accumulator*sf_kigain;
	 
	 sf_dterm=(sf_error-sf_preverror)*sf_kdgain;
	 sf_preverror=sf_error;
	 ;
	 
	 sf_pid=sf_pterm+sf_iterm+sf_dterm;
	 
	 if(sf_pid>=sf_outputmax)
	 	sf_pid=sf_outputmax;
	 else if(sf_pid<=sf_outputmin)
	 	sf_pid=sf_outputmin;
	 ;
	 sf_pidoutput=sf_pid>>sf_mig_scalefactor;
	 	 
	 if(sf_pidoutput<=100)
	 	sf_pidoutput=100;
	 if(sf_pidoutput>=500)
	 	sf_pidoutput=500;	 
}	 
	
	if(MIGweldon_detectf==0)
	{
		if(cStartPulsefg == 0)
		{
			migdaccount = 200;
		}	
	}	  
	else
	{
		migdaccount = sf_pidoutput;		  			  			
	}	  	
	  
	Generate_DAC_Reference(iVoltage);
}
*/

void MIG_superfast_PID(void)
{
 	sf_outputmax=64000;	
 	
 	//int sf_mig_scalefactor = mig_Ka;
 	//long sf_errormin=-1,sf_errormax=60;
 	   
	if((cCreepKifg == 1) && (cCreepSpeedDowncntfg == 1))
	{
		sf_kpgain =	mig_Kp;			
		sf_kigain = mig_Ki;
		sf_kdgain = mig_Ka;
	}
	else if((cInductanceUpdatefg == 1) && (cCreepKifg == 0)) 
	{
		if((iInductance >= 0) && (iInductance < 50))
		{
			//TRIP_LEDLAT=1;
			sf_kpgain =	mig_Kp - (50 - iInductance);	//mig_Kp + ((iInductance - 50) / 1);	
			sf_kigain = mig_Ki;										
			sf_kdgain = mig_Ka;										
		}
		else if((iInductance > 50) && (iInductance <= 100))
		{
			//TRIP_LEDLAT=1;
			sf_kpgain =	mig_Kp + (iInductance - 50);				
			sf_kigain = mig_Ki;		
			sf_kdgain = mig_Ka;
		}
		else if(iInductance == 50)
		{
			//TRIP_LEDLAT=0;
			sf_kpgain =	mig_Kp; 			//30
			sf_kigain = mig_Ki;			 	//1.3
			sf_kdgain = mig_Ka;      			//1
		}	
		cInductanceUpdatefg=0;		
	}
//60 1 90 35 180 150
//60 1 85 35 165 150	01072022

	sf_setpoint = iVoltage;

	/*	
	if(0)//iWireSpeed >= 100)
	{	
		//mult_factor   = iWireSpeed*5/10;
 		//sf_feedback   = ACT_CVOLTAGE + mult_factor - mig_Ka;   	
 	}
 	else
 	{
	 	sf_feedback = ACT_CVOLTAGE;
	}
	*/
	/*if(iWireSpeed > 50)  //PPC
	{	
		//mult_factor   = iWireSpeed*5/10;
 		//sf_feedback   = ACT_CVOLTAGE + mult_factor - mig_Ka; 
 		sf_feedback = ACT_CVOLTAGE - mig_Kc ;  	
 	}
 	else
 	{
	 	sf_feedback = ACT_CVOLTAGE + mig_Kc;
	}*/
			
 	sf_feedback = ACT_CVOLTAGE - mig_Kc ;  //PPC

	sf_error=sf_setpoint-sf_feedback;

if(0)//iWireSpeed <= 45)
{
	sf_pterm=sf_kpgain*sf_error/10;
	
	sf_accumulator+=sf_error*sf_kigain/10;	

	if(sf_accumulator>=sf_outputmax)
		sf_accumulator=sf_outputmax;
	else if(sf_accumulator<=sf_outputmin)
		sf_accumulator=sf_outputmin;
	
	sf_iterm = sf_accumulator;
 
	sf_dterm=sf_kdgain*(sf_error-sf_preverror);
	
	sf_preverror=sf_error;
	
	sf_pid=sf_pterm+sf_iterm+sf_dterm;
	
	if(sf_pid>=sf_outputmax)
		sf_pid=sf_outputmax;
	else if(sf_pid<=sf_outputmin)
		sf_pid=sf_outputmin;
		
	sf_pidoutput=sf_pid>>sf_mig_scalefactor;   //	//2
	//sf_pidoutput=sf_pid/6;	//sf_mig_scalefactor
	
	if(sf_pidoutput<=20)
	sf_pidoutput=20;
	if(sf_pidoutput>=500)
	sf_pidoutput=500; 
}
else
{
	 sf_pterm=sf_kpgain*sf_error;
	 
	 sf_accumulator+=sf_error;
	 
	 if(sf_accumulator>=sf_outputmax)
	 	sf_accumulator=sf_outputmax;
	 else if(sf_accumulator<=sf_outputmin)
	 	sf_accumulator=sf_outputmin;
	 
	 sf_iterm = sf_accumulator*sf_kigain;
	 
	 sf_dterm=(sf_error-sf_preverror)*sf_kdgain;
	 sf_preverror=sf_error;
	 ;
	 
	 sf_pid=sf_pterm+sf_iterm+sf_dterm;
	 
	 if(sf_pid>=sf_outputmax)
	 	sf_pid=sf_outputmax;
	 else if(sf_pid<=sf_outputmin)
	 	sf_pid=sf_outputmin;
	 ;
	 sf_pidoutput=sf_pid>>sf_mig_scalefactor;
	 	 
	 if(sf_pidoutput<=100)	//50)
	 	sf_pidoutput=100;
	 if(sf_pidoutput>=500)
	 	sf_pidoutput=500;	 
}	 
	
	if(MIGweldon_detectf==0)
	{
		if(cStartPulsefg == 0)
		{
			migdaccount = 200;
		}	
	}	  
	else
	{
		migdaccount = sf_pidoutput;		  			  			
	}	  	
	  
	Generate_DAC_Reference(iVoltage);
}



void Generate_DAC_Reference(unsigned int iReference)
{												
	if(iReference != 0)
	{	
		SHDNLAT			=1;//0;								//OCV ON @SBM
		if(cStartPulsefg == 1)
		{												
	    	if(SPI2STATbits.SPITBF==0)
			{
				DACCSLAT	=0;
				MIGCVSLOPE400=mig_Kd/10;		
				//daccount   =(iStartCurr*MIGCVSLOPE400)-MIGC
				400;	
				daccount   =(iStartCurr*MIGCVSLOPE400) - mig_Kb;//MIGCVOFFSET400;	//+	
				if(daccount >= 4095)
					daccount = 4095;					  								
				SPI2BUF		=28672+daccount;
			}				
		}
		else if(cEndPulsefg == 1)
		{  					
	    	if(SPI2STATbits.SPITBF==0)
			{
				DACCSLAT	=0;
				MIGCVSLOPE400=mig_Kd/10;
				//daccount   =(iEndPulseCurr*MIGCVSLOPE400)-MIGCVOFFSET400;
				daccount   =(iEndPulseCurr*MIGCVSLOPE400) - mig_Kb;//MIGCVOFFSET400;	//-
				if(daccount >= 4095)
					daccount = 4095;						  								
				SPI2BUF		=28672+daccount;
			}				
		}				
    	else if((cStartPulsefg == 0) && (cEndPulsefg == 0))
    	{
	    	if(SPI2STATbits.SPITBF==0)
			{
				DACCSLAT	=0;
				MIGCVSLOPE400=mig_Kd/10;
				//daccount   =(migdaccount*MIGCVSLOPE400) - MIGCVOFFSET400;		  								
				daccount   =(migdaccount*MIGCVSLOPE400) - mig_Kb;//MIGCVOFFSET400;	//-
				if(daccount >= 4095)
					daccount = 4095;					  								
				if(1)//cLockDACreffg == 1)
				{		  				
					SPI2BUF		=28672+daccount;     	
				}
			}	
		}
	}
	else
	{
		SHDNLAT	= 0;//1;												
	       						    
    	if(SPI2STATbits.SPITBF == 0)
		{
			DACCSLAT	= 0;
			daccount	= 10;
			if(1)//cLockDACreffg == 1)
			{
				SPI2BUF	= 28672+daccount;     		
			}	
		}						
	}	
}
