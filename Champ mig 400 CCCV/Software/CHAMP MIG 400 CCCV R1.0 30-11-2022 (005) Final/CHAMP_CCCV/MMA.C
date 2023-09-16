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

		SHDNLAT = 1; //OSV ON Mode
		VRvtg = 0;
		IRcurr = 0;
/////////////////////////////////////////////EEPROM Read Start///////////////////////////////////////////////////////////////		
		weldmode='M';
		memoryzone='X';
		eedata=weldmode;//3456;							//0x0003;
		EEPROM_Erase_Write((0*2),eedata);
				
		weldmode='M';
		read_current_status();
		check_eeprom_values();
	
		prev_weldmode=weldmode; 
		prev_eeprom_mig_struct=EEPROM_struct_mig.EEPROM_struct_u;
		read_iOffset=iOffset;
/////////////////////////////////////////////EEPROM Read End///////////////////////////////////////////////////////////////
		TypeDP.DPGROUP[0]=0x00;
    	Typedp.digitdp5		=1;
		TypeU.LEDGROUP[0]=0x00;
		Type.current		=1;
		Type.voltage		=1;
		Type.mma = 1;						
	}
/////////////////////////////////////////Weldding Mode is Off/////////////////////////////////////////////////////////////	
	
	if((weldonf==0)&& (cVRDMenufg==0))
	{	
		Typedp.digitdp5	= 1;		
		if(M_weldingonf==1)	//@AFTER COMPLETING OF WELDING
		{			
			M_weldingonf=0;
		 
			if(weldmode!='M')					
		    	weldmode='M';
			write_current_status();
			cMMAparaupdatefg=0;
		}	

		if(((cDispSetCurrUpdatefg == 1) || (cRemoteEnDCurrUpdatefg == 1)) || (dispupdatef == 1))
		{	
			disp_hex_dec_curr(iSetcurrent);
		}

		if((cVtgFBUpdatefg == 1) || (dispupdatef==1))
		{
			disp_hex_dec_volt(VOLTAGE);
		}
        cMMAparaupdatefg=0; 
		daccount = MMACCLookup(iSetcurrent);
		cDacoutfg = 1;
		cHotfg=1;
		cDispSetCurrUpdatefg = 0;
		cVtgFBUpdatefg = 0;
		dispupdatef=0;
		cRemoteEnDCurrUpdatefg=0;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
/////////////////////////////////////////Weldding Mode is ON/////////////////////////////////////////////////////////////		
	else if(weldonf==1)
	{	
		Typedp.digitdp5	= 1;
		M_weldingonf=1;	
	
		if(cMMAparaupdatefg==0)
		{
			if((cCurrFBUpdatefg == 1) || (dispupdatef==1))
			{
				disp_hex_dec_curr(CURRENT);
			}
			if((cVtgFBUpdatefg == 1) || (dispupdatef==1))
			{
				disp_hex_dec_volt(VOLTAGE);
			}
		}
			
        
		cCurrFBUpdatefg = 0;
		cVtgFBUpdatefg = 0;
		dispupdatef = 0;									
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(cMMAparaupdatefg == 1) // Slope flag Set
	{
	
		if(cMMAMenuMode == 1) 
		{
			if(iOffset <= 550)
			{
				iOffset = 550;
				
			}
			else if(iOffset >= 700)
			{
				iOffset = 700;
			}
		
			disp_hex_dec_volt(iOffset);
			
		}			
			
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

//-------------------------------DAC Count-------------------------------------------------
	if(cDacoutfg == 1)
	{
		cDacoutfg = 0;

		if(SPI2STATbits.SPITBF==0)
		{
			DACCSLAT	=0;	
					
			if(daccount >= 4095)  // DAC count 4096 means 5vdc ouput 
				daccount = 4095;
				
			SPI2BUF	= 28672+daccount;
		}
	}
}

unsigned int MMACCLookup(unsigned int iMMACurrent)
{
	
    //iDacref = ((iMMACurrent*MMACCSLOPE400)) +  (MMACCOFFSET400);
	float fTemp1, fTemp2,fTemp3,fTemp4,fSLOPE1;
	unsigned int iDacref;
	if(cModel_Select == 1)
	{
	    fSLOPE1 =(float)iOffset/100;
	    fTemp1=(float)iMMACurrent;
	    fTemp2=fSLOPE1*fTemp1;
	    fTemp3=(float)MMACCOFFSET400;
	    fTemp4=(fTemp2+fTemp3);
	    iDacref =(int)fTemp4;
	}
	else if(cModel_Select == 2)
	{
			
		
	    fSLOPE1 =(float)iOffset/100;
	    fTemp1=(float)iMMACurrent;
	    fTemp2=fSLOPE1*fTemp1;
	    fTemp3=(float)MMACCOFFSET400;
	    fTemp4=(fTemp2+fTemp3);
	    iDacref =(int)fTemp4;
	    
	}
	else if(cModel_Select == 3)  // y=mx+c
	{
		fSLOPE1 =(float)iOffset/100; // setable cuurent
	    fTemp1=(float)iMMACurrent; // (ACT)display cuurent
	    fTemp2=fSLOPE1*fTemp1;
	    fTemp3=(float)MMACCOFFSET400; //fix value
	    fTemp4=(fTemp2+fTemp3);
	    iDacref =(int)fTemp4;
	}		
	
    return(iDacref);
}

void MMAVRDMenu(void)  
{
	Typedp.digitdp5	= 0;
	Typedp.digitdp2	= 0;
	
	if(cMMAMenuMode == 1)
	{		
		diswin1[0]='S';
		diswin1[1]='L';
		diswin1[2]='P';
	}

	Typedp.digitdp5	= 1;	
}

