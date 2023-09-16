void mma()
{   
       if(mma_flag==0)
	  {
		TypeDP.DPGROUP[0]=0x00;
		//Typedp.digitdp3		=1;
//		Typedp.digitdp7		=0;
		CURR[0]='M';
		CURR[1]='M';
		CURR[2]='A';
		CURR[3]=91;
		VOLT[0]='M';
		VOLT[1]='O';
		VOLT[2]='D';
		VOLT[3]='E';
		for(j=0;j<200;j++)
		for(i=0;i<10000;i++);
		OCV_FLAGLAT=1;          //OCV ON
		ARCONLAT=0;				//ARCON OUTPUT SIGNAL TO PWM PCB
		CCCVLAT=1;				//CCCV MODE SELECTION IN PWM CARD 
		mma_flag=1;             //MMA ENTERED
		saw_flag=0;             //SAW LEFT
		mig_flag=0;
		
		WS_SPEED_LEDLAT=0;
		CURR_LEDLAT=0;
		
		mma_init=0;                  
		comm_flag=0;
		hotf=1;
		count_10ms=0;
		count_100ms=0;
		phsetvoltage=0;
		phsetcurrent=0;
		Disp_updatef=1;
		
		//reading set current from memory
		memdata=EEPROM_Read(1*2);
		if(memdata >= 800)
		{
		   memdata=800;
		}   
		setcurrent=memdata;
		//reading arcforce from memory
		memdata=EEPROM_Read(3*2);
		if(memdata >= 100)
		memdata=100;
		arcforce=memdata;
        }
        
        if((trip_flag==0)&&(imtrip_flag==0))          //IF TRIP OFF
         {
			
			OCV_FLAGLAT=1;          //OCV ON
			ARCONLAT=0;				//ARCON OUTPUT SIGNAL TO PWM PCB
			CCCVLAT=1;				//CCCV MODE SELECTION IN PWM CARD  cc mode
	        if((scalmode==0))				//WELDING IS OFF
		  		{  
              // if(mma_init==1)         	//MMA INITIALISATION OVER
               	 {
					    TypeDP.DPGROUP[0]=0x00;
      			
						if(arcforcemodef==0 && dispcalmodef==0)  //@Display set current
						{
						Typedp.digitdp7	=1;
						
						if(weldon==0)
						{
							//Typedp.digitdp7		=0;            //for removing dp from OCV
							if( ((psetcurrent!= setcurrent) || (Disp_updatef==1))   )                             
							{
								disp_hex_dec_curr(setcurrent);		//DISPLAY SET CURRENT
						        psetcurrent = setcurrent;
						        EEPROM_Erase_Write(1*2,setcurrent);  //writing setcurrent to memory
							}
							
							
							if(((pweldvoltage != weldvoltage)  && disp_flag==1) || Disp_updatef==1)                   
							{
							   	 disp_hex_dec_volt(weldvoltage);	 //DISPLAY VOLTAGE
						    //	disp_hex_dec_volt(iTest); //(recdata_arr1[0]);
						    	 pweldvoltage = weldvoltage;
							}
							
							disp_flag=0;
							Disp_updatef=0;
							cali_on1=0;
						}
						
				     		
		            	}
				        else if(arcforcemodef==1 && dispcalmodef==0 && weldon==0) //@Display set Arcforce
						{
							Typedp.digitdp7	=0;
							CURR[0]='A';
							CURR[1]='R';
							CURR[2]='C';
							CURR[3]='F'; 
							disp_hex_dec_volt(arcforce);
							EEPROM_Erase_Write(3*2,arcforce);  //writing arcforce to memory
						}
						else if(arcforcemodef==0  && dispcalmodef==1 && weldon==0)
						{
							CURR[0]='C';
							CURR[1]='A';
							CURR[2]='L';
							CURR[3]='/';
							VOLT[0]='M';
							VOLT[1]='O';
							VOLT[2]='D';
							VOLT[3]='E';	
	 						//disp_hex_dec_volt(arcforce);
						}

				}  //@ unused bracket
				
				
				fweldvoltage=mma_weldvoltage;         //vertical gouging
				farcforce=arcforce;
				fsetcurrent=setcurrent;
			
				if(hotf==1)
			   	{
								   	
					if(fsetcurrent<550)                 //hotstart
					{
					fnewcurrent=fsetcurrent+(fsetcurrent*HOTSTRT_PERCNT_1)/100.0;  	//15
					}
					else
					{	
					 fnewcurrent=fsetcurrent+100.0;  
					} 
					 NC1LAT =1; 
							 	
				}
				else if(fweldvoltage<=600.0)         //Arc detection
				{
					if(setcurrent<=200)
					{
						fnewcurrent=fsetcurrent+(fsetcurrent*((600.0-fweldvoltage)/600.0)*(farcforce/100.0));
				 	}
				 	else
				 	{
					 	fnewcurrent=fsetcurrent;
					 }	
				 	
				 	NC1LAT =0;                   //motor overloading signal
			 	}					   		
				else                                 //no hotstart needed
				{
				    fnewcurrent=fsetcurrent;
				}
							
			    if(fnewcurrent>=800.0)
				fnewcurrent=800.0;
				
				PWMcount=330.0+(fnewcurrent*1.65);	//modified for maestro 1200	
				//PWMcount=427.0+(fnewcurrent*2.072);	//modified for maestro 1200
				//PWMcount=427+(fsetcurrent*2.072);      //427.0+(fnewcurrent*3.016);//for versa 800 MMA reference
				if(PWMcount >= 2940)
				PWMcount=2940;
				OC1RS= PWMcount;
//---------------------------------------
		if(SPI2STATbits.SPITBF==0)      //for versa 800
		{
			DACCSLAT=0;
			dac_counts=MMACCLookup(fnewcurrent);//*MMACCSLOPE) +  MMACCOFFSET;	//
			SPI2BUF=28672+dac_counts;
				
		}
//---------------------------------------			 
			 
			 if(weldon==1)             //welding started
			 {
				
				
				if((pdispweldcurrent != dispweldcurrent) && disp_flag==1  )  //AFTER EVERY 1 SEC
				{
						disp_hex_dec_curr(dispweldcurrent);     //DISPLAY ARC CURRENT
						//disp_hex_dec_curr(shfb1curr);
	         			pdispweldcurrent = dispweldcurrent;
	   			} 	  	   
	    		
    			if((pweldvoltage != weldvoltage) && disp_flag==1)  //AFTER EVERY 1 SEC
    	  		{
    				disp_hex_dec_volt(weldvoltage);      //weldvoltage //DISPLAY ARC VOLTAGE	
        			pweldvoltage = weldvoltage;
    	  		}
    	  		/*
       			if(cTestfg == 1)
       			{
       				disp_hex_dec_volt(dispshfb1);//shfb1curr);
       				CURR_LEDLAT = 1;
        		}
        		else
        		{	
       				disp_hex_dec_volt(dispshfb2);//shfb2curr);
       				CURR_LEDLAT = 0;
       			}
       			*/    	  				
				disp_flag=0;
				Disp_updatef=1;
			 } 
				
			}
			if(0)//(weldon==1)&&(scalmode==0))					                                    				//WELDING IS ON
				{
				TypeDP.DPGROUP[0]=0x00;
				Typedp.digitdp7		=1;
				//if(psetcurrent!= setcurrent) 
				{
				
				fweldvoltage=mma_weldvoltage;
				farcforce=arcforce;
				fsetcurrent=setcurrent;
				if(fweldvoltage<=600.0)
				fnewcurrent=fsetcurrent+(fsetcurrent*((600.0-fweldvoltage)/600.0)*(farcforce/100.0));
				else
				fnewcurrent=fsetcurrent;
				
				if(hotf==0)
				{
				fnewcurrent=fsetcurrent+100.0;
				if(fnewcurrent>=800.0)
				fnewcurrent=800.0;
				hotstartcount++;
				if(hotstartcount>=200)
				{
				hotf=1;
				hotstartcount=0;
				}
				}
				
				newcurrent=fnewcurrent;
				if(newcurrent>=800)
				newcurrent=800;
				//PWMcount=427.0+(setcurrent*2.072);	   //modified for maestro 1200 // commented on 21012020 shifted to shunt
			//	PWMcount=271.0+(newcurrent*1.688);	   //modified for maestro 1200
				PWMcount=427.0+(newcurrent*2.072);	   //modified for maestro 1200			
				if(PWMcount >= 2940)
				PWMcount=2940;
				OC1RS= PWMcount;	                   //pwm count is given to OC1RS
				psetcurrent = setcurrent;

//---------------------------------------
		if(SPI2STATbits.SPITBF==0)      //for versa 800
		{
			DACCSLAT=0;
			dac_counts=MMACCLookup(newcurrent);//*MMACCSLOPE) +  MMACCOFFSET;	//
			SPI2BUF=28672+dac_counts;
		}
//---------------------------------------			 					
				}
				
				
				if((pdispweldcurrent != dispweldcurrent) && disp_flag==1)  //AFTER EVERY 1 SEC
				{
				disp_hex_dec_curr(dispweldcurrent);     //DISPLAY ARC CURRENT
				pdispweldcurrent = dispweldcurrent;
				} 	  	   
				
				if((pweldvoltage != weldvoltage) && disp_flag==1)  //AFTER EVERY 1 SEC
				{
				disp_hex_dec_volt(mma_weldvoltage);      //weldvoltage //DISPLAY ARC VOLTAGE
				pweldvoltage = mma_weldvoltage;
				}
				disp_flag=0;
				Disp_updatef=1; 
				}
		  	else if(scalmode==1)
		  		{
		  			TypeDP.DPGROUP[0]=0x00;
      				Typedp.digitdp7	=0;
					if(psetcurrent!= setcurrent) 
		      		{
					
					PWMcount=427.0+(setcurrent*2.072);	   //modified for maestro 1200
					if(PWMcount >= 2940)
					PWMcount=2940;
					OC1RS= PWMcount;	
			    		psetcurrent = setcurrent;
//---------------------------------------
		if(SPI2STATbits.SPITBF==0)      //for versa 800
		{
			DACCSLAT=0;
			dac_counts=MMACCLookup(setcurrent);	//
			SPI2BUF=28672+dac_counts;
		}
//---------------------------------------			 			    			
		      		}



					if(shuntcal1f==1)
					{
					CURR[0]='C';
					CURR[1]='A';
					CURR[2]='L';
					CURR[3]='1'; 
					disp_hex_dec_volt(dispshfb1);   //fb on adc pin from shunt fb pcb(TP2)
					
					}
					if(shuntcal2f==1)
					{
					CURR[0]='C';
					CURR[1]='A';
					CURR[2]='L';
					CURR[3]='2'; 
					disp_hex_dec_volt(dispshfb2);   ////fb on adc pin from shunt fb pcb(TP4)
					
					}
	    			  disp_flag=1;
				      Disp_updatef=1;
		  		
		  		}
				   
	   	    }
       	else                                     	//MACHINE IN TRIP CONDITION
        {
          		TypeDP.DPGROUP[0]=0x00;
			    OC1RS=0;                        	//REFERENCE ZERO
          		OCV_FLAGLAT=0;                     	//OCV ZERO
          		
   //---------------------------------------
		if(SPI2STATbits.SPITBF==0)      //for versa 800
		{
			DACCSLAT=0;
			dac_counts=0;	//
			SPI2BUF=28672+dac_counts;
		}
//---------------------------------------       		
          		
          		
          	//	TRIPLEDLAT=1;                       //TRIP LED ON   TEMP
        }
        	
        if(imtrip_flag==1)
        {
        		TypeDP.DPGROUP[0]=0x00;
			    OC1RS=0;                        	//REFERENCE ZERO
          		OCV_FLAGLAT=0;                     	//OCV ZERO
          		
//---------------------------------------
		if(SPI2STATbits.SPITBF==0)      //for versa 800
		{
			DACCSLAT=0;
			dac_counts=0;	//
			SPI2BUF=28672+dac_counts;
		}
//---------------------------------------          		
          		
          		
          		//TRIPLEDLAT=1;                     //TEMP
          		while(imtrip_flag==1); 
        
        }
        	
}

//-----------------------------------------------
unsigned int MMACCLookup(unsigned int iCurrent)
{
	unsigned int iDacref;
	
	if(iCurrent <= CURRENT100)
	{
		iDacref = iCurrent*MMACCSLOPE100 +  MMACCOFFSET;	
	}
	/*else if(iCurrent <= CURRENT200)
	{
		iDacref = iCurrent*MMACCSLOPE200 +  MMACCOFFSET;	
	} else if(iCurrent <= CURRENT400)
	{
		iDacref = iCurrent*MMACCSLOPE400 +  MMACCOFFSET;
	} else if(iCurrent <= CURRENT600)		
	{
		iDacref = iCurrent*MMACCSLOPE600 +  MMACCOFFSET;
	}
 	*/
 	
 	else if((iCurrent >= CURRENT700)&&(iCurrent <= CURRENT800))		
	{
		iDacref = iCurrent*MMACCSLOPE700 +  MMACCOFFSET;
	}
	else
	{
		iDacref = iCurrent*MMACCSLOPE +  MMACCOFFSET;		
	}				
				
return(iDacref);
}	
//-----------------------------------------------
