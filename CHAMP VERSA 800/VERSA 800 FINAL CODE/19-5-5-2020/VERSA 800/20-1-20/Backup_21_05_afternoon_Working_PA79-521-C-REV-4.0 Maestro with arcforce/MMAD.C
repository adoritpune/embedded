void mma()
{   
        if(mma_flag==0)
	  {
		TypeDP.DPGROUP[0]=0x00;
		CURR[0]='M';
		CURR[1]='M';
		CURR[2]='A';
		CURR[3]=91;
		VOLT[0]='M';
		VOLT[1]='O';
		VOLT[2]='D';
		VOLT[3]='E';
		MMALEDLAT=1;            //MMA LED ON
		SAWLEDLAT=0;            //SAW LED OFF
		OCV_FLAGLAT=1;          //OCV ON
		ARCONLAT=0;				//ARCON OUTPUT SIGNAL TO PWM PCB
		CCCVLAT=1;				//CCCV MODE SELECTION IN PWM CARD 
		mma_flag=1;             //MMA ENTERED
		saw_flag=0;             //SAW LEFT
		mig_flag=0;
		mma_init=0;                  
		comm_flag=0;
		count_10ms=0;
		count_100ms=0;
		phsetvoltage=0;
		phsetcurrent=0;
		Disp_updatef=1;
		memdata=EEPROM_Read(1*2);
		if(memdata >= 1200)
		memdata=1200;
		setcurrent=memdata;
		memdata=EEPROM_Read(3*2);
		if(memdata >= 100)
		memdata=100;
		arcforce=memdata;
         }
         if((trip_flag==0)&&(imtrip_flag==0))          //IF TRIP OFF
         {
			MMALEDLAT=1;            //MMA LED ON
			SAWLEDLAT=0;            //SAW LED OFF
			OCV_FLAGLAT=1;          //OCV ON
			ARCONLAT=0;				//ARCON OUTPUT SIGNAL TO PWM PCB
			CCCVLAT=1;				//CCCV MODE SELECTION IN PWM CARD  cc mode
	           	if((scalmode==0))				//WELDING IS OFF
		  	{  
               	//	if(mma_init==1)         	//MMA INITIALISATION OVER
               		{
					TypeDP.DPGROUP[0]=0x00;
      			
					if(arcforcemodef==0 && dispcalmodef==0)
					{
						Typedp.digitdp7	=1;
						
						if(weldon==0)
						{
						if((psetcurrent!= setcurrent) || Disp_updatef==1)                             
						{
						        disp_hex_dec_curr(setcurrent);			      			//DISPLAY SET CURRENT
					        	psetcurrent = setcurrent;
						}
						if(((pweldvoltage != weldvoltage)  && disp_flag==1) || Disp_updatef==1)                   
						{
							disp_hex_dec_volt(weldvoltage);		            			//DISPLAY VOLTAGE
					    		pweldvoltage = weldvoltage;
						}
							cali_on1=0;
							Disp_updatef=0;
							disp_flag=0;
						}	
				   	}
			        else if(arcforcemodef==1 && dispcalmodef==0 && weldon==0)
					{
						Typedp.digitdp7	=0;
						CURR[0]='A';
						CURR[1]='R';
						CURR[2]='C';
						CURR[3]='F'; 
						disp_hex_dec_volt(arcforce);
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

				}
				
				
				
				
				hotstartcount=0;
				hotf=0;
		  	 
		  	 
		  	 
		  	 
		  	 
		  	 
		  	 
		  	 
		  	 
		  	 
		  	 
		  	 }
	    	 	if((0))					                                    				//WELDING IS ON
	    	  	{
	    	  		TypeDP.DPGROUP[0]=0x00;
      				Typedp.digitdp7		=1;
				//if(psetcurrent!= setcurrent) 
	      		{
					fweldvoltage=weldvoltage;
					farcforce=arcforce;
					fsetcurrent=setcurrent;
					if(fweldvoltage<=600.0)
						fnewcurrent=fsetcurrent+(fsetcurrent*((600.0-fweldvoltage)/600.0)*(farcforce/100.0));
					else
						fnewcurrent=fsetcurrent;

					if(hotf==0)
					{
						fnewcurrent=fsetcurrent+100.0;
						if(fnewcurrent>=1200.0)
						fnewcurrent=1200.0;
						hotstartcount++;
						if(hotstartcount>=200)
						{
							hotf=1;
							hotstartcount=0;
						}
					}

					newcurrent=fnewcurrent;
					if(newcurrent>=1200)
					newcurrent=1200;
					//PWMcount=427.0+(setcurrent*2.072);	   //modified for maestro 1200
					PWMcount=427.0+(newcurrent*2.072);	   //modified for maestro 1200
					if(PWMcount >= 2940)
					PWMcount=2940;
					OC1RS= PWMcount;	
			    		psetcurrent = setcurrent;	
	      		}







				if((pdispweldcurrent != dispweldcurrent) && disp_flag==1)  //AFTER EVERY 1 SEC
				{
						disp_hex_dec_curr(dispweldcurrent);     //DISPLAY ARC CURRENT
	         				pdispweldcurrent = dispweldcurrent;
	    	  		}   
	    			if((pweldvoltage != weldvoltage) && disp_flag==1)  //AFTER EVERY 1 SEC
	    	  		{
	    				disp_hex_dec_volt(weldvoltage);      //DISPLAY ARC VOLTAGE
	        			pweldvoltage = weldvoltage;
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
		      		}



					if(shuntcal1f==1)
					{
					CURR[0]='C';
					CURR[1]='A';
					CURR[2]='L';
					CURR[3]='1'; 
					disp_hex_dec_volt(dispshfb1);
					
					}
					if(shuntcal2f==1)
					{
					CURR[0]='C';
					CURR[1]='A';
					CURR[2]='L';
					CURR[3]='2'; 
					disp_hex_dec_volt(dispshfb2);
					
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
          		TRIPLEDLAT=1;                       //TRIP LED ON
        	}
        	
        if(imtrip_flag==1)
        {
        		TypeDP.DPGROUP[0]=0x00;
			    OC1RS=0;                        	//REFERENCE ZERO
          		OCV_FLAGLAT=0;                     	//OCV ZERO
          		TRIPLEDLAT=1;
          		while(imtrip_flag==1); 
        
        }
        	
}


