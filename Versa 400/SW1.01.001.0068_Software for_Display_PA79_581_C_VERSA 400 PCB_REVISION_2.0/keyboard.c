void keypad_int()
{
	COLUMN0IO=1;
	COLUMN1IO=1;
	COLUMN2IO=1;
	COLUMN3IO=1;
	ROW0IO=0;
	ROW1IO=0;
	ROW2IO=0;
}	

char keyscan(void)
{
	temp=keypress();
	if(temp=='1')
	{
		key=keydetect();
	    debounce_delay();		
		key1=key;
	}
	else
	{		
		key= '0';
		key1= '0';
	}		
  return(key);	
}

char keypress()
{
	ROW0LAT=0;
	ROW1LAT=0;
	ROW2LAT=0;
	    if(COLUMN0==0 && COLUMN1==1 && COLUMN2==1 && COLUMN3==1)
		return('1');
		else if(COLUMN0==1 && COLUMN1==0 && COLUMN2==1 && COLUMN3==1)
		return('1');
		else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==0 && COLUMN3==1)
		return('1');
		else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==1 && COLUMN3==0)
		return('1');
		else //if(COLUMN0==1 && COLUMN1==1 && COLUMN2==1 && COLUMN3==1)*/
		return('0');
}	

char keydetect(void)
{
	ROW0LAT=1;
	ROW1LAT=1;
	ROW2LAT=0;
	{
		if(COLUMN0==0 && COLUMN1==1 && COLUMN2==1 && COLUMN3==1)
		{	 	 
			return('9');
		}
		else if(COLUMN0==1 && COLUMN1==0 && COLUMN2==1 && COLUMN3==1)
		{			
			return('A');
		}
		else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==0 && COLUMN3==1)
		{			
			return('B');
		}
		else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==1 && COLUMN3==0)
		{			
			return('C');
		}
	}
	
	ROW0LAT=1;
	ROW1LAT=0;
	ROW2LAT=1;
	{
		if(COLUMN0==0 && COLUMN1==1 && COLUMN2==1 && COLUMN3==1)
		{			
			return('5');
		}
		else if(COLUMN0==1 && COLUMN1==0 && COLUMN2==1 && COLUMN3==1)
		{			
			return('6');
		}
		else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==0 && COLUMN3==1)
		{			
			return('7');
		}
		else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==1 && COLUMN3==0)
		{		
			return('8');
		}
	}	
	
	ROW0LAT=0;
	ROW1LAT=1;
	ROW2LAT=1;
	{
		if(COLUMN0==0 && COLUMN1==1 && COLUMN2==1 && COLUMN3==1)
		{		
			return('1');
		}
		else if(COLUMN0==1 && COLUMN1==0 && COLUMN2==1 && COLUMN3==1)
		{			
			return('2');
		}
		else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==0 && COLUMN3==1)
		{			
			return('3');
		}
		else if(COLUMN0==1 && COLUMN1==1 && COLUMN2==1 && COLUMN3==0)
		{			
			return('4');
		}
	}		
	return('0');
}

void debouncedelay(void)
	{
		  for(i=0;i<50000;i++);  
          
	}

 void delay3()
{
	unsigned int i;
	for(i=0;i<=1500;i++);//200
}

void debounce_delay()
{
	delay3();
	delay3();
	delay3();
	delay3();
	delay3();
	//delay3();
    
}

//#############################################################################################################
void keyfun(unsigned char keyget)
{
	//if(tigweldingon==1)
	{
		 /*if((keyget==COOLSELKEY) && (calibratnmodef==0))// (keyget==COOLSELKEY))
		 {
			tempcnt++;
			if(tempcnt>=5)
			{
				tempcnt=0;
				calibratnmodef=1;
				sprintf(lcdbuffer1, "%s","CALIBRATION ON");
				sprintf(lcdbuffer2, "%s","                    ");
				delay2();
				delay2();
				lcddisplyf=1;			
			}
		 }*/
		 if((keyget==MODESELKEY)&&(calibratnmodef==1) )//TIGMODESELKEY
		 {
			EEPROM_Erase_Write(0x40,para.pwmslope);
			calibratnmodef=0;
			sprintf(lcdbuffer1, "%s","CALIBRATION OFF");
			sprintf(lcdbuffer2, "%s","                    ");
			lcd (lcdbuffer1,lcdbuffer2,0XC0);
			delay2();
			delay2();
			delay2();
			delay2();
			lcddisplyf=1;
			tempcnt=0;
			weldcycle=0;
			displcdmmaf=1;
		 }
	}
	if(tigweldingon==0 && mmaweldon==0)
	{	
	 	 if(keyget==PROGKEY)
     	 {	
			if(Type.mma==1 && Type.tig==0)
		 	{
				if(tigcntf==0)
				{
					 //mig2tig();
					 TypeU.LEDGROUP[0]=ledgp[0];
					 TypeU.LEDGROUP[1]=ledgp[1];
					 TypeU.LEDGROUP[2]=ledgp[2];
					 TypeU.LEDGROUP[3]=ledgp[3];					 				
				}
				 //read_memory();
				 Type.mma=0;
				 Type.tig=1;
				 //tigcnt=0;	
				 igbtdrivef=1;	
				 lcddisplyf=1;
				 mmaocvon=0;
				 peakcurf=1;
				 sprintf(lcdbuffer1, "%s","      TIG MODE");					
				 sprintf(lcdbuffer2, "%s","                    ");
			     lcd (lcdbuffer1,lcdbuffer2,0XC0);	
				 delay2();
				 delay2();
				 //delay2();
				 //delay2();		 
		 	} 
			else if(Type.mma==0 && Type.tig==1)
		 	{			
				  ledgp[0]=TypeU.LEDGROUP[0];
				  ledgp[1]=TypeU.LEDGROUP[1];
				  ledgp[2]=TypeU.LEDGROUP[2];
				  ledgp[3]=TypeU.LEDGROUP[3];
				  //tig2mig();
				  //write_memory();	
				  Type.tig=0;
				  Type.mma=1;
				  mmacnt=1;
				  igbtdrivef=1;	 
				  lcddisplyf=1;	
				  displcdmmaf=1;
				  peakcurf=1;		 
		 	}	
			keychangef=1;	
			writememcnt=0;
  	 	 }			 
		 else if((keyget==SAVEKEY)&& (Type.tig==1))
		 {
		 	Type.save=1;
			Type.recall=0;					
			if(savedsetup==0)
			{
				savedsetup=1;
			}
			else
			{
				savedsetup=2;
			}
								
			OCVONLAT=1;	
			lcddisplyf=1;				 
	     } 
		 else if((keyget==RECALLKEY)&& (Type.tig==1))
		 { 			 
			Type.recall=1;	
			Type.save=0;
			if(readdataf==0)
				readdataf=1;
			else
				readdataf=2;
			OCVONLAT=0;  
			lcddisplyf=1;
	     }
         if(Type.tig==1)
  		 { 
             if(tigcntf==1) //0
			 { 
               Type.dcptv =0;
			   Type.dcntv =0;
	           Type.gascooled=1;
    		   Type.pulse=1; 
		  	   //Type.ac = 1;  
               Type.twot=1;
			   //Type.preflow	=1;
  				Type.dcptv =1;
			   tigcntf=0;
			 }         

  		 	 if(keyget==COOLSELKEY)
			 { 				  
				 if(Type.gascooled==1 && Type.watercooled==0)
				 {
					 Type.gascooled=0;
					 Type.watercooled=1;					 
				 } 
				 else if(Type.gascooled==0 && Type.watercooled==1)
				 {
					 Type.watercooled=0;
					 Type.gascooled=1;					 
			 
				 } 
				 keychangef=1;
				 writememcnt=0;
			 } 		
			 if(keyget==GASCHKKEY)
			 {			 
			 	Type.gascheck=1;
				GASCHKRELAYLAT=1;							 
			 }  	 	 
			 else if(keyget==TIGPROGKEY)
			 {				 
				if(Type.dcptv ==1 && Type.ac ==0)
				 {
					 Type.dcptv =0;
					 Type.dcntv =0;
					 Type.ac =1;
					 acdutyon=0;
					 account=0;
					 //account1=0;
					 igbtdrivef=1;
					if(Type.cycle==1)
					{
						Type.cycle=0;
						Type.twot=1;
					}	
					lcddisplyf=1;
					peakcurf=1;
					//min.peakcurrent=20;
				 }
				 else if(Type.dcptv ==0 && Type.ac ==1)
				 {
					 Type.dcntv =0;
					 Type.ac =0;
					 Type.dcptv =1;
					 igbtdrivef=1;	
					 lcddisplyf=1;
					 peakcurf=1;
					 //min.peakcurrent=10;
				 }
				 keychangef=1;
				 writememcnt=0;
			   
	 		}			
    	    else if(keyget==REVERSEKEY)
	    	{
     		   if()
     		   {
     		   		revkey_flag=1;
					//keycnt--;
					setupcnt1=0;
					lcddisplyf=1;
					//setupcnt++;
					//if(setupcnt>18)
					{
					//	setupcnt=0;
					//	setupf=1;
					//	dispmesgf=0;
					//	savedsetup=0;
					}
				}
				else
				{
					
				}
		    }
   	        else if(keyget==FORWARDKEY)
	        {
	   	       nextkey_flag=1;
				setupcnt=0;
				lcddisplyf=1;
				//setupcnt1++;
				/*if(setupcnt1>25)
				{
					setupcnt1=0;
					setupf=0;
					//savedsetup=1;
				}*/
              //keycnt++;
	        }         
            else if((keyget==TIGMODESELKEY)&& (Type.spot==0)&& (calibratnmodef==0)&&(norftsw==0))
	        {
	        	if(Type.pulse==1 && Type.normal==0)
		        {
		  	      Type.pulse=0;
			      Type.normal=1;			      
		        } 
		        else if(Type.pulse==0 && Type.normal==1)
	   	        {
		  		  Type.normal=0;
			 	  Type.pulse=1;					  	 
		 	    } 
				lcddisplyf=1;
				keychangef=1;
				writememcnt=0;
	        } 
    		else if((keyget==MODESELKEY) && (norftsw==0))
   		    {
				if(Type.ac==1)
				{					
	  		   		if(Type.twot==1 && Type.fourt==0 && Type.spot==0)
	     			{ 
	      			   Type.twot=0;
	                   Type.fourt=1; 
				       Type.spot=0;				      
		            }
	               else if(Type.twot==0 && Type.fourt==1 && Type.spot==0)
	               { 
	                  Type.twot=0;
	                  Type.fourt=0; 
			   	      Type.spot=1;				     
		           }
	      		   else if(Type.twot==0 && Type.fourt==0 && Type.spot==1)
	     		   { 
		           	   Type.twot=1;
		           	   Type.fourt=0; 
					   Type.spot=0;					   
		  		   }
					peakcurf=1;				   		     	   			
				}
				else
				{
	  		   		if(Type.twot==1 && Type.fourt==0 && Type.spot==0 && Type.cycle==0)
	     			{ 
	      				Type.twot=0;
	                   	Type.fourt=1; 
				       	Type.spot=0;
				       	Type.cycle=0;
		            }
	                else if(Type.twot==0 && Type.fourt==1 && Type.spot==0 && Type.cycle==0)
	                { 
	                  	Type.twot=0;
	                  	Type.fourt=0; 
			   	      	Type.spot=1;
				      	Type.cycle=0;
		            }
	      		    else if(Type.twot==0 && Type.fourt==0 && Type.spot==1 && Type.cycle==0)
	     		    { 
		           	   	Type.twot=0;
		           	   	Type.fourt=0; 
					   	Type.spot=0;
					   	Type.cycle=1;
		  		    }
		     	    else if(Type.twot==0 && Type.fourt==0 && Type.spot==0 && Type.cycle==1)
		   		    { 
		       	      	Type.twot=1;
		              	Type.fourt=0; 
			          	Type.spot=0;
				      	Type.cycle=0;
		           }
					peakcurf=1;
			   }
			   lcddisplyf=1;
			   keychangef=1;
			   writememcnt=0;
     		}
			
			if(Type.spot==1)	
			{
					Type.pulse=0;			//pulsing is not in spot mode
					Type.normal=1;						
			}
			//#####################################################################################
			/*if(norftsw==1)
			{
				Type.twot=1;
              	Type.fourt=0; 
	          	Type.spot=0;
		      	Type.cycle=0;
				Type.pulse=0;			//pulsing is not in spot mode
				Type.normal=1;	
			}
			else
			{
					
				disp_hex_dec1(222);
			}*/
			if(peakcurf==1)
			{
				peakcurf=0;
				if(norftsw==0)
				{
					if(((Type.twot==1) && (Type.ac==1))&&((Type.normal==1)||(Type.pulse==1)))	
					{
						keycnt=5;
					}
					else if(((Type.fourt==1) && (Type.ac==1))&&((Type.normal==1) ||(Type.pulse==1)))
					{
						keycnt=6;	
					}
					else if((Type.spot==1) && (Type.normal==1) && (Type.ac==1))
					{
						keycnt=5;
					}
					else if((Type.twot==1) && (Type.dcptv ==1 || Type.dcntv ==1) && (Type.normal==1 || Type.pulse==1 ))  
					{
						keycnt=2;
					}
					else if((Type.fourt==1) && (Type.dcptv ==1 || Type.dcntv ==1) && (Type.normal==1 || Type.pulse==1))
					{
						keycnt=3;
					}
					else if((Type.spot==1 && Type.normal==1) && (Type.dcptv ==1 || Type.dcntv ==1))
					{
						keycnt=2;
					}
					else if((Type.cycle==1) && (Type.dcptv ==1 || Type.dcntv ==1) && (Type.normal==1 || Type.pulse==1))
					{
						keycnt=4;
					}
				}			
			}	
					
	    	//#####################################################################################
			//if(setupf==1)
			//{ 
				if(norftsw==1)//((Type.twot==1) && (Type.normal==1) && (Type.ac==1))				//################# AC 2T NORMAL ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>3)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=2)
		 		    {
		  		       keycnt=2;
		   			}	

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;					
						case 1:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;						
						case 2:
								TypeU.LEDGROUP[1]=0;			//Post Flow			 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
					
				}
				else if((Type.twot==1) && (Type.normal==1) && (Type.ac==1))				//################# AC 2T NORMAL ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>8)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=7)
		 		    {
		  		       keycnt=7;
		   			}	

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=16;			//cleanup		 
						 		TypeU.LEDGROUP[2]=0;
								break;
						case 3:
								TypeU.LEDGROUP[1]=32;			//ac offset		 
						 		TypeU.LEDGROUP[2]=0;	
								break;
						case 4:
								TypeU.LEDGROUP[1]=64;			//AC Frequency		 
						 		TypeU.LEDGROUP[2]=0;
								break;		
						case 5:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 6:
								TypeU.LEDGROUP[1]=0;			//Downslope			 
								TypeU.LEDGROUP[2]=16;
								break;
						case 7:
								TypeU.LEDGROUP[1]=0;			//Post Flow			 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
				}
				else if((Type.twot==1) && (Type.pulse==1) && (Type.ac==1))			//################# AC 2T PULSE ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>11)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=10)
		 		    {
		  		       keycnt=10;
		   			}				

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=16;			//cleanup		 
						 		TypeU.LEDGROUP[2]=0;
								break;
						case 3:
								TypeU.LEDGROUP[1]=32;			//ac offset		 
						 		TypeU.LEDGROUP[2]=0;	
								break;
						case 4:
								TypeU.LEDGROUP[1]=64;			//AC Frequency		 
						 		TypeU.LEDGROUP[2]=0;
								break;		
						case 5:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 6:
								TypeU.LEDGROUP[1]=0;		   //pulse duty			 
								TypeU.LEDGROUP[2]=2;			
								break;
						case 7:
								TypeU.LEDGROUP[1]=0;			//base current		 
								TypeU.LEDGROUP[2]=8;
								break;
						case 8:
								TypeU.LEDGROUP[1]=0;			//pulse Frequency
								TypeU.LEDGROUP[2]=4;
								break;
						case 9:
								TypeU.LEDGROUP[1]=0;			//Down slope		 
								TypeU.LEDGROUP[2]=16;
								break;
						case 10:
								TypeU.LEDGROUP[1]=0;			//Post Flow		 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
							
				}
				else if((Type.fourt==1) && (Type.normal==1) && (Type.ac==1))			//################# AC 4T NORMAL ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>10)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=9)
		 		    {
		  		       keycnt=9;
		   			}	

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=2;			//initial current		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 3:
								TypeU.LEDGROUP[1]=16;			//cleanup		 
						 		TypeU.LEDGROUP[2]=0;
								break;
						case 4:
								TypeU.LEDGROUP[1]=32;			//ac offset		 
						 		TypeU.LEDGROUP[2]=0;	
								break;
						case 5:
								TypeU.LEDGROUP[1]=64;			//AC Frequency		 
						 		TypeU.LEDGROUP[2]=0;
								break;		
						case 6:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 7:
								TypeU.LEDGROUP[1]=0;			//downslope		 
								TypeU.LEDGROUP[2]=16;
								break;
					    case 8:
								TypeU.LEDGROUP[1]=0;			//crater current	 
								TypeU.LEDGROUP[2]=32;
								break;
						case 9:
								TypeU.LEDGROUP[1]=0;			//postflow		 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
				}
				else if((Type.fourt==1 && Type.pulse==1) && (Type.ac==1))			//################# AC 4T PULSE ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>13)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=12)
		 		    {
		  		       keycnt=12;
		   			}				

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=2;			//initial current		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 3:
								TypeU.LEDGROUP[1]=16;			//cleanup		 
						 		TypeU.LEDGROUP[2]=0;
								break;
						case 4:
								TypeU.LEDGROUP[1]=32;			//ac offset		 
						 		TypeU.LEDGROUP[2]=0;	
								break;
						case 5:
								TypeU.LEDGROUP[1]=64;			//AC Frequency		 
						 		TypeU.LEDGROUP[2]=0;
								break;
						case 6:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 7:
								TypeU.LEDGROUP[1]=0;		   			 
								TypeU.LEDGROUP[2]=2;			//pulse duty
								break;
						case 8:
								TypeU.LEDGROUP[1]=0;			//base current		 
								TypeU.LEDGROUP[2]=8;
								break;
						case 9:
								TypeU.LEDGROUP[1]=0;			//pulse Frequency
								TypeU.LEDGROUP[2]=4;
								break;
						case 10:
								TypeU.LEDGROUP[1]=0;			//Down slope		 
								TypeU.LEDGROUP[2]=16;
								break;
						case 11:
								TypeU.LEDGROUP[1]=0;			//crater current	 
								TypeU.LEDGROUP[2]=32;
								break;
						case 12:
								TypeU.LEDGROUP[1]=0;			//pulse duty		 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
							
				}
				else if((Type.spot==1) && (Type.normal==1) && (Type.ac==1))					//################# AC SPOT NORMAL ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>9)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=8)
		 		    {
		  		       keycnt=8;
		   			}	

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=16;			//cleanup		 
						 		TypeU.LEDGROUP[2]=0;
								break;
						case 3:
								TypeU.LEDGROUP[1]=32;			//ac offset		 
						 		TypeU.LEDGROUP[2]=0;	
								break;
						case 4:
								TypeU.LEDGROUP[1]=64;			//AC Frequency		 
						 		TypeU.LEDGROUP[2]=0;
								break;		
						case 5:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 6:
								TypeU.LEDGROUP[1]=0;			//duty used as a spot time		 
								TypeU.LEDGROUP[2]=2;	
								break;
						case 7:
								TypeU.LEDGROUP[1]=0;			//Downslope		 
								TypeU.LEDGROUP[2]=16;
								break;
						case 8:
								TypeU.LEDGROUP[1]=0;			//postflow
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
				}
				else if((Type.twot==1 && Type.normal==1) && (Type.dcptv ==1 || Type.dcntv ==1) )       //################# DC 2T NORMAL ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>5)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=4)
		 		    {
		  		       keycnt=4;
		   			}	

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 3:
								TypeU.LEDGROUP[1]=0;		 //Downslope			 
								TypeU.LEDGROUP[2]=16;
								break;
						case 4:
								TypeU.LEDGROUP[1]=0;			//Post Flow		 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
				}
				else if((Type.twot==1 && Type.pulse==1) && (Type.dcptv ==1 || Type.dcntv ==1))			//################# DC 2T PULSE ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>8)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=7)
		 		    {
		  		       keycnt=7;
		   			}				

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 3:
								TypeU.LEDGROUP[1]=0;		   //pulse duty			 
								TypeU.LEDGROUP[2]=2;			
								break;
						case 4:
								TypeU.LEDGROUP[1]=0;			//base current		 
								TypeU.LEDGROUP[2]=8;
								break;
						case 5:
								TypeU.LEDGROUP[1]=0;			//pulse Frequency
								TypeU.LEDGROUP[2]=4;
								break;
						case 6:
								TypeU.LEDGROUP[1]=0;			//Down slope		 
								TypeU.LEDGROUP[2]=16;
								break;
						case 7:
								TypeU.LEDGROUP[1]=0;			//Post Flow		 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
							
				}
				else if((Type.fourt==1 && Type.normal==1) && (Type.dcptv ==1 || Type.dcntv ==1) )		//################# DC 4T NORMAL ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>7)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=6)
		 		    {
		  		       keycnt=6;
		   			}	

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=2;			//initial current		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 3:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 4:
								TypeU.LEDGROUP[1]=0;			//downslope		 
								TypeU.LEDGROUP[2]=16;
								break;
					    case 5:
								TypeU.LEDGROUP[1]=0;			//crater current	 
								TypeU.LEDGROUP[2]=32;
								break;
						case 6:
								TypeU.LEDGROUP[1]=0;			//postflow		 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
				}
				else if((Type.fourt==1 && Type.pulse==1) && (Type.dcptv ==1 || Type.dcntv ==1))			//################# DC 4T PULSE ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>10)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=9)
		 		    {
		  		       keycnt=9;
		   			}				

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=2;			//initial current		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 3:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 4:
								TypeU.LEDGROUP[1]=0;		   			 
								TypeU.LEDGROUP[2]=2;			//pulse duty
								break;
						case 5:
								TypeU.LEDGROUP[1]=0;			//base current		 
								TypeU.LEDGROUP[2]=8;
								break;
						case 6:
								TypeU.LEDGROUP[1]=0;			//pulse Frequency
								TypeU.LEDGROUP[2]=4;
								break;
						case 7:
								TypeU.LEDGROUP[1]=0;			//Down slope		 
								TypeU.LEDGROUP[2]=16;
								break;
						case 8:
								TypeU.LEDGROUP[1]=0;			//crater current	 
								TypeU.LEDGROUP[2]=32;
								break;
						case 9:
								TypeU.LEDGROUP[1]=0;			//pulse duty		 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
							
				}
				else if((Type.spot==1 && Type.normal==1) && (Type.dcptv ==1 || Type.dcntv ==1))		//################# DC SPOT NORMAL ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>6)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=5)
		 		    {
		  		       keycnt=5;
		   			}	

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 3:
								TypeU.LEDGROUP[1]=0;			//duty used as a spot time		 
								TypeU.LEDGROUP[2]=2;	
								break;
						case 4:
								TypeU.LEDGROUP[1]=0;			//Downslope		 
								TypeU.LEDGROUP[2]=16;
								break;
						case 5:
								TypeU.LEDGROUP[1]=0;			//postflow
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
				}
				else if((Type.cycle==1 && Type.normal==1) && (Type.dcptv ==1 || Type.dcntv ==1) )				//################# DC CYCLE NORMAL ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>8)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=7)
		 		    {
		  		       keycnt=7;
		   			}	

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=2;			//initial current		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 3:
								TypeU.LEDGROUP[1]=8;			//AC Frequency(temp used for cycle current )		 
							    TypeU.LEDGROUP[2]=0;
								break;
						case 4:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 5:
								TypeU.LEDGROUP[1]=0;			//downslope		 
								TypeU.LEDGROUP[2]=16;
								break;
					    case 6:
								TypeU.LEDGROUP[1]=0;			//crater current	 
								TypeU.LEDGROUP[2]=32;
								break;
						case 7:
								TypeU.LEDGROUP[1]=0;			//postflow		 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
				}
				else if((Type.cycle==1 && Type.pulse==1) && (Type.dcptv ==1 || Type.dcntv ==1))		//################# DC CYCLE PULSE ###################
				{
					if(revkey_flag==1)
					{
					  keycnt--;
					  revkey_flag=0;
					}
		  			if(nextkey_flag==1)
					{
					  keycnt++;
					  nextkey_flag=0;
					}
	     		    if(keycnt<=0 || keycnt>11)
		  		    {
				       keycnt=0;
		   			}
		  		 	if(keycnt>=10)
		 		    {
		  		       keycnt=10;
		   			}				

					switch(keycnt)
					{
						case 0:
								TypeU.LEDGROUP[1]=1;			//preflow		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 1:
								TypeU.LEDGROUP[1]=2;			//initial current		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 2:
								TypeU.LEDGROUP[1]=4;			//upslope		 
								TypeU.LEDGROUP[2]=0;								
								break;
						case 3:
								TypeU.LEDGROUP[1]=8;			//AC Frequency(temp used for cycle current )		 
							    TypeU.LEDGROUP[2]=0;
								break;
						case 4:
								TypeU.LEDGROUP[1]=0;			//peakcurrent		 
								TypeU.LEDGROUP[2]=1;	
								break;
						case 5:
								TypeU.LEDGROUP[1]=0;		   			 
								TypeU.LEDGROUP[2]=2;			//pulse duty
								break;
						case 6:
								TypeU.LEDGROUP[1]=0;			//base current		 
								TypeU.LEDGROUP[2]=8;
								break;
						case 7:
								TypeU.LEDGROUP[1]=0;			//pulse Frequency
								TypeU.LEDGROUP[2]=4;
								break;
						case 8:
								TypeU.LEDGROUP[1]=0;			//Down slope		 
								TypeU.LEDGROUP[2]=16;
								break;
						case 9:
								TypeU.LEDGROUP[1]=0;			//crater current	 
								TypeU.LEDGROUP[2]=32;
								break;
						case 10:
								TypeU.LEDGROUP[1]=0;			//pulse duty		 
								TypeU.LEDGROUP[2]=64;
								break;
						default:break;
					}
							
				}

	
   		 }    
   	  	 if(Type.mma==1)				//################# MMA MODE ###################
   		 {
	        if(mmacnt==1)
			{		 
				TypeU.LEDGROUP[0]=16;
				TypeU.LEDGROUP[1]=0;
				TypeU.LEDGROUP[2]=0;
				TypeU.LEDGROUP[3]=1;
				mmacnt=0;
		    }
	        if(keyget=='3')
		    {
			   if(Type.dcptv ==1 && Type.dcntv ==0)
			   {
				 Type.dcptv =0;				 
				 Type.dcntv =1;	
				 igbtdrivef=1;				 			 
			   }
			   else if(Type.dcptv ==0 && Type.dcntv ==1) 
			   {
				 Type.dcptv =1;
				 Type.dcntv =0;
				 igbtdrivef=1;					 	
			   } 
			   lcddisplyf=1; 
			   keychangef=1;
			   writememcnt=0;
	        }
	        else if(keyget==MODESELKEY)
   		    {
	   		    mmaocvon=1;
	   		} 
	
   		 } 
	}	

}
