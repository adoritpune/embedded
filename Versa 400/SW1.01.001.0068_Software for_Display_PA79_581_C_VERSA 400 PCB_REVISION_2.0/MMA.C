void MMAWELD(void)
{
	if(modechangef==1)
	{	
		Typedp.digitdp2=0;
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

		SHDNLAT = 1;//0; OCV ON
		VRvtg = 0;
		IRcurr = 0;
		weldmode='M';
		memoryzone='X';
		eedata=weldmode;//3456;							//0x0003;
		EEPROM_Erase_Write((0*2),eedata);
		
		eedata=EEPROM_Read(4*2); //PPC
		if((eedata <= 0)|| (eedata >= 500))
		{
			eedata = 350;
		}	
		iOffset = eedata;
		
		
		weldmode='M';
		read_current_status();
		check_eeprom_values();
	
		prev_weldmode=weldmode; //PPC
		prev_eeprom_mig_struct=EEPROM_struct_mig.EEPROM_struct_u;
		read_iOffset=iOffset;

		TypeDP.DPGROUP[0]=0x00;
    	Typedp.digitdp5		=1;
		TypeU.LEDGROUP[0]=0x00;
		Type.current		=1;
		Type.voltage		=1;
		Type.mma = 1;						
	}
	if((weldonf==0)&& (cVRDMenufg==0))// PPC && (cModeSelectDonefg == 0))//@welding not in process
	//if((weldonf == 0) && ((cVRDMenufg == 0) || (cMMAMenuMode == 0)) && (cModeSelectDonefg == 0))
	//if(weldonf == 0)
	{	
		Typedp.digitdp5	= 1;		
		if(M_weldingonf==1)	//@AFTER COMPLETING OF WELDING
		{			
			M_weldingonf=0;
		 
			if(weldmode!='M')					
		    	weldmode='M';
			write_current_status();
		}	

		if(((cDispSetCurrUpdatefg == 1) || (cRemoteEnDCurrUpdatefg == 1)) || (dispupdatef == 1))
		{	
			disp_hex_dec_curr(iSetcurrent);
		}

		if((cVtgFBUpdatefg == 1) || (dispupdatef==1))
		{
			disp_hex_dec_volt(VOLTAGE);
		}

		daccount = MMACCLookup(iSetcurrent);
		cDacoutfg = 1;
		cHotfg=1;
		cDispSetCurrUpdatefg = 0;
		cVtgFBUpdatefg = 0;
		dispupdatef=0;
		cRemoteEnDCurrUpdatefg=0;
	}
	else if(weldonf==1)
	{	
		Typedp.digitdp5	= 1;
		M_weldingonf=1;	
		
		if((cCurrFBUpdatefg == 1) || (dispupdatef==1))
		{
			disp_hex_dec_curr(CURRENT);
		}
		if((cVtgFBUpdatefg == 1) || (dispupdatef==1))
		{
			disp_hex_dec_volt(VOLTAGE);
		}

		cCurrFBUpdatefg = 0;
		cVtgFBUpdatefg = 0;
		dispupdatef = 0;							
	}

	if(cMMAparaupdatefg == 1) //PPC
	{
		/*if(cMMAMenuMode == 3) 
		{
			if(mma_vrd_time <= 0)
			{
				mma_vrd_time = 0;
			}
			else if(mma_vrd_time >= 50)
			{
				mma_vrd_time = 50;
			}
			disp_hex_dec_volt(mma_vrd_time);
			
			
			if(cEEPROMSavefg == 0)
			{
				EEPROM_Erase_Write((4*2),mma_vrd_time);
				cEEPROMSavefg = 1;
			}
			//VRD_TIME_MAX = mma_vrd_time*10;	
		}
		if(cMMAMenuMode == 2) 
		{			
			if(iSlope <= 0)
			{
				iSlope = 0;
			}
			else if(iSlope >= 900)
			{
				iSlope = 900;
			}
			disp_hex_dec_volt(iSlope);
		}*/
		if(cMMAMenuMode == 1) 
		{
			if(iOffset <= 100)
			{
				iOffset = 100;
			}
			else if(iOffset >= 900)
			{
				iOffset = 900;
			}
			disp_hex_dec_volt(iOffset);
			
			if(cEEPROMSavefg == 0)
			{
				EEPROM_Erase_Write((4*2),iOffset);
				cEEPROMSavefg = 1;
			}
		}		
		cMMAparaupdatefg = 0;		
 	}   

//---------------------------ARCFORCE------------------------------------
	
	if(cArcforcefg == 1)
	{
	    if((cFastUpdateFBvtg == 1) && (iArcforce != 0))
	    {
			if((ARCFORCEVOLTAGE > ANTISTICK_VTG_LIMIT) && (ARCFORCEVOLTAGE <= ARCFORCE_VTG_LIMIT))
			{                                         
				iArcforceCurrent = (int)iSetcurrent + ((((300.0 - ARCFORCEVOLTAGE)/300.0)*(125.0*iArcforce))/100.0); 
			
				if(iSetcurrent <= ARCFORCE_SETCURR_LIMIT_2)
				{
					daccount = MMACCLookup(iArcforceCurrent);
					cDacoutfg = 1; 
				}
				iArcForceTimeCnt = 0;
			}
			else if((ARCFORCEVOLTAGE > ARCFORCE_VTG_LIMIT) && (cHotfg == 0))
			{	
				iArcForceTimeCnt++;
	            if(iArcForceTimeCnt >= 1)
	            {         
	                iArcForceTimeCnt = 0; 
	                cEnDCurrUpdatefg = 1;   
	            }             
			}
			cFastUpdateFBvtg = 0;
	    }
	    cArcforcefg=0;
 	}   
       
//----------------------------HOTSTART----------------------------------------------------------
    
	if((cRemoteEnDCurrUpdatefg == 1) || (cEnDCurrUpdatefg == 1))
    {            
        if(cHotfg == 1)
        {
        	if(iSetcurrent <= HOT_START_SETCURR_LIMIT) 
           	{                   
            	iHotstartCurrent = iSetcurrent+((iSetcurrent*iHotstart)/100.0);
               	if(iHotstartCurrent >= 270)
               	{
                	iHotstartCurrent = 270;
               	}
               	daccount=MMACCLookup(iHotstartCurrent);
           	}
           	else
           	{
               	daccount = MMACCLookup(iSetcurrent);
           	}         
        }
        else if((cHotfg == 0) && (cAntistickfg == 0))
        {
            daccount = MMACCLookup(iSetcurrent);
        }

        cDacoutfg = 1;            
        cEnDCurrUpdatefg = 0;
        cRemoteEnDCurrUpdatefg = 0;
    }

//--------------------------------------------------------------------------------
	if(cDacoutfg == 1)
	{
		cDacoutfg = 0;

		if(SPI2STATbits.SPITBF==0)
		{
			DACCSLAT	=0;	
					
			if(daccount >= 4095)
				daccount = 4095;
				
			SPI2BUF	= 28672+daccount;
		}
	}
}

unsigned int MMACCLookup(unsigned int iMMACurrent)
{
	unsigned int iDacref;
    //iMMASlope = iSlope/10;
    //iDacref = ((iMMACurrent*MMACCSLOPE400)) +  (MMACCOFFSET400);
	if(cModel_Select == 1)
	{
		//iDacref = ((iMMACurrent*iMMASlope)) +  (iOffset);
	}
	else if(cModel_Select == 2)
	{
		//iDacref = ((iMMACurrent*MMACCSLOPE400)) +  (MMACCOFFSET400);
		iDacref = ((iMMACurrent*MMACCSLOPE400)) +  (iOffset); //PPC
	}
	else if(cModel_Select == 3)
	{
		//iDacref = ((iMMACurrent*iMMASlope)) +  (iOffset);
	}		
	iDacref = ((iMMACurrent*MMACCSLOPE400)) +  (iOffset); //PPC
    return(iDacref);
}

void MMAVRDMenu(void)  //PPC
{
	Typedp.digitdp5	= 0;
	Typedp.digitdp2	= 0;
	
	if(cMMAMenuMode == 1)
	{		
		diswin1[0]='O';
		diswin1[1]='F';
		diswin1[2]='T';
	}
/*	if(cMMAMenuMode == 2)
	{
		diswin1[0]='S';
		diswin1[1]='L';
		diswin1[2]='P';
	}
	if(cMMAMenuMode == 3)
	{
		diswin1[0]='V';
		diswin1[1]='R';
		diswin1[2]='D';
	}	*/	
	Typedp.digitdp5	= 1;	
}

