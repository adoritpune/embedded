void TIGWELD(void)
{				
	if(modechangef==1)
	{
		Typedp.digitdp2=0;
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
		VRvtg = 0;
		IRcurr = 0;
		SHDNLAT = 1;	// OCV ON
		iArcforce = 0;      // Acrfore Mode is OFF
		cHotfg = 0;         // Hot Start Start Flag is OFF
		iHotstart = 0;      // Hot Start Mode Flag is OFF
	
		memoryzone='X';
		eedata=weldmode;//3456;							//0x0003;
		EEPROM_Erase_Write((0*2),eedata);
		
		weldmode='T';
		read_current_status();
		check_eeprom_values();				
						
		prev_weldmode=weldmode;
		prev_eeprom_tig_struct=EEPROM_struct_tig.EEPROM_struct_ut;

		TypeDP.DPGROUP[0]=0x00;
    	Typedp.digitdp5		=1;
		TypeU.LEDGROUP[0]=0x00;
		Type.current		=1;
		Type.voltage		=1;
		Type.tig = 1;

	}
	////////////////////////////////////////////Weldding Mode is OFF//////////////////////////////////////////////////////////////////
	if(weldonf==0)
	{	
		if(T_weldingonf==1)//@AFTER COMPLETING OF WELDING
		{						
			T_weldingonf=0;  						
			if(weldmode!='T')					
		    	weldmode='T';						
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

		daccount = TIGCCLookup(iSetcurrent);
		cDacoutfg = 1;

		cDispSetCurrUpdatefg = 0;
		cVtgFBUpdatefg = 0;
		dispupdatef=0;  
		cRemoteEnDCurrUpdatefg = 0; 
	}
///////////////////////////////////////////Weldding Mode is ON////////////////////////////////////////////////////////////						 
	else if(weldonf==1)
	{	
		T_weldingonf=1;			
		
		if((cCurrFBUpdatefg == 1) || (dispupdatef==1))
		{
			disp_hex_dec_curr(CURRENT);
		}
		if((cVtgFBUpdatefg == 1) || (dispupdatef==1))
		{
			disp_hex_dec_volt(VOLTAGE);
		}
		daccount = TIGCCLookup(iSetcurrent);
		cDacoutfg = 1;
		
		cCurrFBUpdatefg = 0;
		cVtgFBUpdatefg = 0;
		dispupdatef = 0;					
	}	
/////////////////////////////////////////DAC Count///////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int TIGCCLookup(unsigned int iTigCurrent)
{
	float fTemp1, fTemp2,fTemp3,fTemp4,fSLOPE1;
	unsigned int iDacref;
	
	if(cModel_Select == 1)
	{
    	fSLOPE1 =(float)iOffset/100;
	    fTemp1=(float)iTigCurrent;
	    fTemp2=fSLOPE1*fTemp1;
	    fTemp3=(float)TIGCCOFFSET400;
	    fTemp4=(fTemp2+fTemp3);
	    iDacref =(int)fTemp4;
	}
	else if(cModel_Select == 2)
	{
				
	    fSLOPE1 =(float)iOffset/100;
	    fTemp1=(float)iTigCurrent;
	    fTemp2=fSLOPE1*fTemp1;
	    fTemp3=(float)TIGCCOFFSET400;
	    fTemp4=(fTemp2+fTemp3);
	    iDacref =(int)fTemp4;
	    
	}
	else if(cModel_Select == 3)
	{
		fSLOPE1 =(float)iOffset/100;
	    fTemp1=(float)iTigCurrent;
	    fTemp2=fSLOPE1*fTemp1;
	    fTemp3=(float)TIGCCOFFSET400;
	    fTemp4=(fTemp2+fTemp3);
	    iDacref =(int)fTemp4;
	}		

    return(iDacref);
}

