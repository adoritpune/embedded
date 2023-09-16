void saw()
{
	if(calibrationf==1 && disp_calf==1)
	{
		TypeDP.DPGROUP[0]=0x00;
		CURR[0]='C';
		CURR[1]='A';
		CURR[2]='L';
		CURR[3]=91;          //-
		VOLT[0]='M';
		VOLT[1]='O';
		VOLT[2]='D';
		VOLT[3]='E';
		disp_calf=0;
		for(bbb=0;bbb<1000;bbb++);
		for(bbb=0;bbb<1000;bbb++);
	}
	else if(saw_flag==0)//|| (calibrationf==0 && disp_calf==1))
    {
          TypeDP.DPGROUP[0]=0x00;
	      CURR[0]='S';
          CURR[1]='A';
          CURR[2]='W';
          CURR[3]=91;          //-
          VOLT[0]='M';
          VOLT[1]='O';
          VOLT[2]='D';
          VOLT[3]='E';
          mma_flag=0;
          saw_flag=1;
	      mig_flag=0;
          mma_init=0;
		  CCCVLAT=0;							//CCCV MODE SELECTION IN PWM CARD 
          MMALEDLAT=0;
          SAWLEDLAT=1;
          count_10ms=0;
          count_100ms=0;
		  ARCONLAT=0;							//ARCON OUTPUT SIGNAL TO PWM PCB
          OCV_FLAGLAT=0;
		Disp_updatef=1;
		disp_calf=0;
		memdata=EEPROM_Read(2*2);
		if(memdata >= 1000)					//Max 100 ohm
		memdata=1000;
		resistance=memdata/10.0;
	}
      // if(trip_flag==0)               		//IF TRIP OFF
	else if(trip_flag==0 && saw_flag==1 &&  mma_init==1)
	{
		TypeDP.DPGROUP[0]=0x00;
      	Typedp.digitdp7	=1;
		if(pwelding_status != welding_status)
		{
			Disp_updatef=1;
			pwelding_status= welding_status;
		}
		if(welding_status=='F')  //Torch==0)
		{
				if((phsetcurrent!=hsetcurrent) || Disp_updatef==1)                    
                		{
    			  		disp_hex_dec_curr(hsetcurrent);
 	    		  		phsetcurrent=hsetcurrent;
    				}
	    		   	if((phsetvoltage!=hsetvoltage) || Disp_updatef==1)
	                	{
	    			  	disp_hex_dec_volt(hsetvoltage);
	 	    		  	phsetvoltage=hsetvoltage;
	    			}
    	    welding_flag=0;
    		OCV_FLAGLAT=0;         // OCV OFF
			ARCONLAT=0;			   //ARCON OUTPUT SIGNAL TO PWM PCB
         	CCCVLAT=0;			   //CV MODE SELECTION IN PWM CARD 
    		comm_flag=0;
            data_head();                  //TRANSMIT DATA TO HEAD
            OC1RS=0;                        //REFERENCE ZERO AT NO WELDING
            comm_count++;         //mjp  	//FOR COMMUNICATION ERROR
			Disp_updatef=0;
			start_cv=1;
			CCCVmodef=0;
			psetcurrent=0x1FFF;	
			pweldcurrent=0x1FFF;	
			pweldvoltage=0x1FFF;	
		}
		else if (welding_status=='O')		//welding on
		{
			TypeDP.DPGROUP[0]=0x00;
      		Typedp.digitdp7		=1;
			comm_count++; 
			OCV_FLAGLAT=1;          		// OCV ON
	    		if(((phsetvoltage!= hsetvoltage) || calibrationf==1 || Disp_updatef==1 || CCCVmodef==0) && sawweldmode=='V')
	      	{
				OCV_FLAGLAT=1;          		// OCV ON
				ARCONLAT=1;				//ARCON OUTPUT SIGNAL TO PWM PCB
	            CCCVLAT=CVMODE;				//CV MODE SELECTION IN PWM CARD
				//$$$$Addoffsetvtg=(resistance*hsetcurrent)/1000.0;               //(hsetcurrent*resistance)/100.0;
	            		//PWMcount=((hsetvoltage+Addoffsetvtg) + 4.0)*2.61;
				//if(PWMcount >= 1470)
				//PWMcount=1470;
				//$$$$PWMcount=20.88 + ((hsetvoltage+Addoffsetvtg) *5.22) ;
				PWMcount=20.88 + (hsetvoltage *5.22) ;
				if(PWMcount >= 2940)
				PWMcount=2940;
				OC1RS= PWMcount;					
		    		phsetvoltage = hsetvoltage;	
	      	}
			else if (((phsetcurrent!=hsetcurrent) || Disp_updatef==1 || start_cv==1 || CCCVmodef==0) && sawweldmode=='C')
			{
				if(start_cv==1)
				{
					start_cv=0;
					OCV_FLAGLAT=1;          		// OCV ON
					ARCONLAT=1;				//ARCON OUTPUT SIGNAL TO PWM PCB
					CCCVLAT=CVMODE;				//CC MODE SELECTION IN PWM CARD
					comm_count++;
				
					//if((psetvoltage!= setvoltage) || calibrationf==1 || Disp_updatef==1)
					{
						//$$$$Addoffsetvtg=(resistance*hsetcurrent)/1000.0;               //(hsetcurrent*resistance)/100.0;
						//PWMcount=((hsetvoltage+Addoffsetvtg) + 4.0)*2.61;
						//if(PWMcount >= 1470)
						//PWMcount=1470;
						//$$$$PWMcount=20.88 + ((hsetvoltage+Addoffsetvtg) *5.22) ;
						PWMcount=20.88 + (hsetvoltage *5.22) ;
						if(PWMcount >= 2940)
						PWMcount=2940;
						OC1RS= PWMcount;
					//	psetvoltage = setvoltage;
					}
					for(counter=0;counter<=7370000;counter++){}//3685000
				}	
				else
				{
					OCV_FLAGLAT=1;          				// OCV ON
					ARCONLAT=0;								//ARCON OUTPUT SIGNAL TO PWM PCB
		           	CCCVLAT=CCMODE;						//CV MODE SELECTION IN PWM CARD
					PWMcount=427.0+(hsetcurrent*2.072);		//modified for maestro 1200
					if(PWMcount >= 2940)
					PWMcount=2940;
					OC1RS= PWMcount;	
					phsetcurrent=hsetcurrent;
				}
			}

			if(((pdispweldcurrent != dispweldcurrent)  && disp_flag==1) || Disp_updatef==1)			// && disp_flag==1)        		//AFTER EVERY 1 SEC
			{
				disp_hex_dec_curr(dispweldcurrent);             //DISPLAY ARC CURRENT
	        		pdispweldcurrent = dispweldcurrent;
	   	  	}   
	   	  	/*if((pweldvoltage != weldvoltage) && disp_flag==1)     //AFTER EVERY 1 SEC
	    	  	{
	    			disp_hex_dec_volt(weldvoltage);               //DISPLAY ARC VOLTAGE
	        		pweldvoltage = weldvoltage;
	    	  	}*/
	    	  	
	    	  	//if((precweldvtg != recweldvtg) && disp_flag==1)  //AFTER EVERY 1 SEC
	    	  	{
	    			disp_hex_dec_volt(recweldvtg);       //DISPLAY ARC VOLTAGE
	        		precweldvtg = recweldvtg;
	    	  	}
	    	  	
	    	  	
	   	  		  	
	   	  	if(((precweldvtg != recweldvtg) && disp_flag==1) || Disp_updatef==1)	          		//AFTER EVERY 1 SEC
			{
	   			if(calibrationf==1 )
					disp_hex_dec_volt(offsetsetvtg);//recweldvtg);//weldvoltage);                    //DISPLAY ARC VOLTAGE
				else
					disp_hex_dec_volt(recweldvtg);//weldvoltage);                    //DISPLAY ARC VOLTAGE
	       		precweldvtg = recweldvtg;//weldvoltage;
	   	  	}
	   	  	disp_flag=0;
	   	  	Disp_updatef=0;
			data_head();                                  //TRANSMIT DATA TO HEAD
		}
		else if (welding_status==0)		//welding on
     	{
		      TypeDP.DPGROUP[0]=0x00;
      		  CURR[0]='E';
		      CURR[1]='R';
		      CURR[2]='R';
              CURR[3]=91;          //-
		      VOLT[0]='0';
		      VOLT[1]='0';
		      VOLT[2]='0';
		      VOLT[3]='8';
		      OC1RS=0;
		     data_head();
             OCV_FLAGLAT=0;
		     ARCONLAT=0;							//ARCON OUTPUT SIGNAL TO PWM PCB
             comm_flag=1;
             phsetcurrent=0;
             phsetvoltage=0;
		}
	}
	else if(trip_flag==1)
	{
		TypeDP.DPGROUP[0]=0x00;
      	OC1RS=0;
		data_head();
        OCV_FLAGLAT=0;
		ARCONLAT=0;							//ARCON OUTPUT SIGNAL TO PWM PCB
        TRIPLEDLAT=1;
        phsetcurrent=0;
        phsetvoltage=0;
         if(imtrip_flag==1)
        {
          		while(imtrip_flag==1); 
        
        }
        
        
        
	}
}
