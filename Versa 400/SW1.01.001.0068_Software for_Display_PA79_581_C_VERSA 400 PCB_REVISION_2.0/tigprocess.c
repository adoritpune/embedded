void Tig_Weld_Process()
{
  dummytigtorch=TORCH_SW;	
  
    
  
  if(weldcyclestrt==0)
  {
  	oper_tig=tig_pre;
  //	tig_torch_relse_4t=0;	
  }
 /**************************************FOOT Welding***********************************************/ 
  if(foot_1_normal_0==1)  //@versa edit					 				
  {
  	switch(oper_tig)
	{
		case tig_pre: //foot
		{			
			preflow();
			if(dummytigtorch=='X')
			{
				oper_tig=tig_end;							
			}
			break;
	    }		
		case tig_arcdet: //foot
		{		
			if(weldonf==1)    //
			{
				if( Time_ms>=2 && weldonf==1 )
				{
				 	//TIG_RELAY_1ON_0OFF=1;
					
					strttmr=1;  //
					timerval=0;
					time_100ms=0;
					Time_ms=0;	
								
					tig_weld_cycle_current=footref_I;
					oper_tig=tig_weld;
				}
			}
			else if(time_100ms>=20)
			{
				timerval=0;
				time_100ms=0;
				Time_ms=0;	
				
				//TIG_RELAY_1ON_0OFF=0;
				currerrf=1;	//@edit			
				oper_tig=tig_end;					
			}
			if(dummytigtorch=='X')
			{
				oper_tig=tig_end;							
			}
			break;
		}
	    case tig_upslpe: //foot
	    {			
			break;
	    }
		case tig_weld://foot
		{							
			if(dummytigtorch=='X')
			{			
				//TIG_RELAY_1ON_0OFF=1;	 	
				SHDNLAT=0;  			//@ocv off
				tig_weld_cycle_current=0;
				
				timerval=0;            //@reset timer
				time_100ms=0;
				Time_ms=0;
				
				oper_tig=tig_post;											
			}	
			else if(weldonf==1)
			{
				timerval=0;
				time_100ms=0;
				Time_ms=0;
				
				tig_weld_cycle_current=footref_I;
				//TIG_RELAY_1ON_0OFF=1;
			}
			else if(time_100ms>=20)
			{
				timerval=0;
				time_100ms=0;
				Time_ms=0;
				
				//TIG_RELAY_1ON_0OFF=0;
				tig_weld_cycle_current=0;
				currerrf=1;	//@edit			
				oper_tig=tig_end;
			}
			break;	
		}
		case tig_dwnslope: //foot
		{			
			break;
		}
		case tig_post:  //foot
		{				
			//TIG_RELAY_1ON_0OFF=1;	//@Gas Relay on		
			SHDNLAT=0;  			//@ocv off
			tig_weld_cycle_current=0;
			
			if(time_100ms>=para.tigpostflowtime)
			{
				strttmr=0;
			    timerval=0;
				time_100ms=0;
				 
				oper_tig=tig_end;
			}
			/*if(torch==1)//@edit think
			{
				oper=end;							
			}*/
			break;
		}
		case tig_end: //foot
		{		
			end1();
			if(dummytigtorch=='T')
			{
				oper_tig=tig_end;
				break;
			}			
			 
			weldcyclestrt=0;
		 
			currerrf=0;
		   dispupdatef=1;
			break;
		}	
	} //end switch
   }
  //***************************** 2T MODE **********************************************************************************************************//
  else if(foot_1_normal_0==0)
  {
	if(Type.twot==1) //2T MODE 
	{
		switch(oper_tig)
		{
			case tig_pre: //2T MODE 
			{			
				preflow();
				if(dummytigtorch=='X')
				{
					oper_tig=tig_end;							
				}
				break;
		    }		
			case tig_arcdet: //2T MODE 
			{		
			  if(weldonf==1)
			{
					if(Time_ms>=2 && weldonf==1)
					 {
						//TIG_RELAY_1ON_0OFF=1;  //@turn on the gas relay
						strttmr=1;   
						timerval=0;
						time_100ms=0;
						Time_ms=0;
						 
						if( (para.tigmode.upslopetime>0) && (para.tigmode.setcurrent>min_current) )
						{
							tig_weld_cycle_current=min_current;
						    
						    
							UP_Step=(float)((para.tigmode.setcurrent - min_current)/(para.tigmode.upslopetime*10.0));
							Upslope_cntr=para.tigmode.upslopetime*10; //@DOUBT
							Upcurrent=min_current;	
							pwmresult=Upcurrent;
							
							upslopef=1;
							msec10_cntr=0;
							timerval=0;
							timerval_1ms=0;
							
							oper_tig=tig_upslpe;		
						}
						else
						{
							tig_weld_cycle_current=para.tigmode.setcurrent;
						 
							oper_tig=tig_weld;
						}
									
					 }
									
				}
				else if(time_100ms>=150) //2T MODE                  //gas check for 10 sec when torch on and weloncycle=0
				{
					timerval=0;
					time_100ms=0;
					Time_ms=0;
					
					//TIG_RELAY_1ON_0OFF=0;
					//currerrf=1;	//@edit			
					tig_weld_cycle_current=0;
				    
				   //oper_tig=tig_end;
				}
				if(dummytigtorch=='X')
				{
					oper_tig=tig_end;							
				}
				break;
			}
		    case tig_upslpe: //2T MODE 
		    {
				//TIG_RELAY_1ON_0OFF=1;  //@turn on the gas relay
				
				if(upslopef==1)
                {
				tig_weld_cycle_current=pwmresult; //@Edit
				oper_tig=tig_upslpe;
				}
				else
				{
				    tig_weld_cycle_current=para.tigmode.setcurrent; //2T MODE 
					oper_tig=tig_weld;
				}
				
				if(dummytigtorch=='X')
				{
					oper_tig=tig_end;
					break;							
				}
				
				break;
		    }
			case tig_weld: //2T MODE 
			{		
				//TIG_RELAY_1ON_0OFF=1;  //@turn on the gas relay				
				if(dummytigtorch=='X')
				{				
					if( (para.tigmode.setcurrent>mini.tigmode.setcurrent) && (para.tigdownslopetime>0) )
					{
					oper_tig=tig_dwnslope;
					downslopef=1;
					
					Down_Step=(float)((para.tigmode.setcurrent - mini.tigmode.setcurrent)/(para.tigdownslopetime*10.0));   
					Downslope_cntr=para.tigdownslopetime*10;  
					Downcurrent=para.tigmode.setcurrent; 
					pwmresult=Downcurrent;
					
					msec10_cntr=0;  //@edit
					timerval=0;	   //@edit														
				 	} 
				 	else
				 	{
				 	oper_tig=tig_dwnslope;
					downslopef=0;
				 	}				
				}	
				else
				{
						
				    if(weldonf==1)
					{
						strttmr=1;  //
						timerval=0;
						time_100ms=0;
						Time_ms=0;
						tig_weld_cycle_current=para.tigmode.setcurrent;								
					}
					else if(time_100ms>=20)
					{
						strttmr=1;  //
						timerval=0;
						time_100ms=0;
						Time_ms=0;
						 	
						tig_weld_cycle_current=0;	
						//TIG_RELAY_1ON_0OFF=0;  //@turn off the gas relay
					
						currerrf=1;				
						oper_tig=tig_end;
					}
				}		
				break;	
			}
			case tig_dwnslope: //2T MODE 
			{	
				//TIG_RELAY_1ON_0OFF=1;	
				if(downslopef==1)
				{
					tig_weld_cycle_current=pwmresult;
					oper_tig=tig_dwnslope;     	
				}
				else
				{
					oper_tig=tig_post;
					strttmr=1;   
					timerval=0;
					time_100ms=0;
					Time_ms=0; 
				    tig_weld_cycle_current=0;	 
				}	
				break;
			}
			case tig_post: //2T MODE 
			{				
				tig_weld_cycle_current=0;	
				SHDNLAT=0;			  //@OCV OFF    
				//TIG_RELAY_1ON_0OFF=1;
				
				if((time_100ms>=para.tigpostflowtime) || (dummytigtorch=='T'))  ////MAHESH 17.03.2017 prev=if(time_100ms>=para.postflowtime)
				{
					strttmr=0;  //@stop timer
					timerval=0;
					time_100ms=0;
					Time_ms=0;
					oper_tig=tig_end;
				}
				//if(torch==1)
				//{
				//	oper=end;							
				//}
				break;
			}
			case tig_end: //2T MODE 
			{		
			 	end1();
			 
				if(dummytigtorch=='T' && currerrf==0)	 
				{
					oper_tig=tig_pre;//end;
					//break;
				}
				if(dummytigtorch=='T' &&  currerrf==1) //currerrf==1)
				{
					oper_tig=tig_end;
					break;
				}
				 
				weldcyclestrt=0;
				 
				currerrf=0;
				dispupdatef=1;
				break;
			}	
		} //end switch
	}		//end if 2T 	
	else if(Type.fourt==1)  //**************************** 4T ****************************** 
	{
		switch(oper_tig) //4T MODE 
		{
			case tig_pre:
			{			
				preflow();
				if(dummytigtorch=='X')
				{
					oper_tig=tig_end;							
				}
				break;
		    }	
			case tig_arcdet: //4T MODE 
			{
			 
				if(weldonf==1)
				{
					if(Time_ms>=2 && weldonf==1)
					{				  
						//TIG_RELAY_1ON_0OFF=1;
						strttmr=1;   
						timerval=0;
						time_100ms=0;
						Time_ms=0;	
						
						tig_weld_cycle_current=para.tigmode.startcurrent;
						
						oper_tig=tig_initI;
						
					 }	
				}
				else if(time_100ms>=20) //4T MODE 
				{
					timerval=0;
					time_100ms=0;
					Time_ms=0;
					
					//TIG_RELAY_1ON_0OFF=1;
					//currerrf=1;	//@edit			
					tig_weld_cycle_current=0;
					
					//oper_tig=tig_end;
										
				}
				
				else if(dummytigtorch=='X') //4T MODE 
				{
					oper_tig=tig_end;							
				}
				break;
			}
			case tig_initI: //4T MODE 
			{
			 	if(weldonf==1)
				{
					if(Time_ms>=2 && weldonf==1)
					{				  
						//TIG_RELAY_1ON_0OFF=1;
						strttmr=1;   
						timerval=0;
						time_100ms=0;
						Time_ms=0;	
						
						tig_weld_cycle_current=para.tigmode.startcurrent;
						
						oper_tig=tig_initI;
						
						if(dummytigtorch=='X') //4T MODE 
						{
							if( (para.tigmode.upslopetime>0) && (para.tigmode.setcurrent>para.tigmode.startcurrent) )
							{
							  
								UP_Step=(float)((para.tigmode.setcurrent - para.tigmode.startcurrent)/(para.tigmode.upslopetime*10.0));
								Upslope_cntr=para.tigmode.upslopetime*10;
								Upcurrent=para.tigmode.startcurrent;	
								pwmresult=Upcurrent;
								
								upslopef=1;
								msec10_cntr=0;
								timerval=0;
								oper_tig=tig_upslpe;
								 		
							}
							else
							{
							 	tig_weld_cycle_current=para.tigmode.setcurrent;
								oper_tig=tig_weld;
							}
						}
					}	
				}
				else if(time_100ms>=20) //4T MODE 
				{
					timerval=0;
					time_100ms=0;
					Time_ms=0;
					
					//TIG_RELAY_1ON_0OFF=1;
					currerrf=1;	//@edit			
					tig_weld_cycle_current=0;
					
					oper_tig=tig_end;
										
				}
				
				else if(dummytigtorch=='X') //4T MODE 
				{
					oper_tig=tig_end;							
				}
			  break;	
			}	
			case tig_upslpe: //4T MODE 
		    {		
				//TIG_RELAY_1ON_0OFF=1;
				if(upslopef==1)
				{
					tig_weld_cycle_current=pwmresult;
					oper_tig=tig_upslpe;
				}
				else
				{
				 	tig_weld_cycle_current=para.tigmode.setcurrent;
					oper_tig=tig_weld;
				}
				
				if(dummytigtorch=='T')
				{
				 
				//	tig_torch_relse_4t=1;	
					upslopef=0;	
					tig4tupslpbrkcurrent=tig_weld_cycle_current;	
					
					if( (para.tigdownslopetime>0)  && (tig4tupslpbrkcurrent>para.tigmode.endcurrent) )	
					{    
				    oper_tig=tig_dwnslope;
					downslopef=1;
					
					Down_Step=(float)((tig4tupslpbrkcurrent - para.tigmode.endcurrent)/(para.tigdownslopetime*10.0));
					Downslope_cntr=para.tigdownslopetime*10;
					Downcurrent=tig4tupslpbrkcurrent;
					pwmresult=Downcurrent;
					
					msec10_cntr=0;
					timerval=0;
					}	
					else
					{
						oper_tig=tig_endI;
						
						strttmr=1;  //
						timerval=0;
						time_100ms=0;
						Time_ms=0;
												 
						tig_weld_cycle_current=para.tigmode.endcurrent;
					}				
				}
								
				break;		    
			}
			case tig_weld: //4T MODE 
			{
				//TIG_RELAY_1ON_0OFF=1;
				if(dummytigtorch=='T')
				{		
					if( (para.tigdownslopetime>0) && (para.tigmode.setcurrent>para.tigmode.endcurrent) )	
					{
						oper_tig=tig_dwnslope;
						downslopef=1;
						
						Down_Step=(float)((para.tigmode.setcurrent - para.tigmode.endcurrent)/(para.tigdownslopetime*10.0));
						Downslope_cntr=para.tigdownslopetime*10;
						Downcurrent=para.tigmode.setcurrent;
						pwmresult=Downcurrent;
						
						msec10_cntr=0;
						timerval=0;
					}
					else
					{
						oper_tig=tig_endI;
						
						strttmr=1;  //
						timerval=0;
						time_100ms=0;
						Time_ms=0;
												 
						tig_weld_cycle_current=para.tigmode.endcurrent;
					}										
				}	
				else
				{			
					if(weldonf==1)
					{
						tig_weld_cycle_current=para.tigmode.setcurrent;									
					}
					else if(time_100ms>=20)
					{
						strttmr=1;  //
						timerval=0;
						time_100ms=0;
						Time_ms=0;
						 	
						tig_weld_cycle_current=0;	
						//TIG_RELAY_1ON_0OFF=0;  //@turn off the gas relay
					
						currerrf=1;				
						oper_tig=tig_end;
					}
				}		
				break;	
			}
			case tig_dwnslope: //4T MODE 
			{		
				//TIG_RELAY_1ON_0OFF=1;	
				if(downslopef==1)
                {
					tig_weld_cycle_current=pwmresult;
                    oper_tig=tig_dwnslope;     	
				}
				else
				{
						oper_tig=tig_endI;
						strttmr=1;  //
						timerval=0;
						time_100ms=0;
						Time_ms=0;
												 
						tig_weld_cycle_current=para.tigmode.endcurrent;
				}	
				break;
			}
			case tig_endI: //4T MODE 
			{
				//TIG_RELAY_1ON_0OFF=1;	
	     		tig_weld_cycle_current=para.tigmode.endcurrent;				
		
				if(dummytigtorch=='X')
				{
					oper_tig=tig_post;
					strttmr=1;  //
					timerval=0;
					time_100ms=0;
					Time_ms=0;	
 					tig_weld_cycle_current=0; //@add shut down below?
				}
			  break;
			}
			case tig_post: //4T MODE 
			{				
				tig_weld_cycle_current=0; //@add shut down below?
				SHDNLAT=0;			  //OCV OFF  
				
				//TIG_RELAY_1ON_0OFF=1;	
						
				if((time_100ms>=para.tigpostflowtime) || (dummytigtorch=='T'))    //MAHESH 4T
				{
					strttmr=0;  //@timer off
					timerval=0;
					time_100ms=0;
					Time_ms=0;
					oper_tig=tig_end;
				}
				dispupdatef=1;
			/*	if(torch==1)
				{
					oper=end;							
				}*/
				break;
			}
			case tig_end: //4T MODE 
			{	
				end1();
				
				if(dummytigtorch=='T' && currerrf==0)							
				{
					oper_tig=tig_pre;//end;
					//break;
				}
				if(dummytigtorch=='T' && (currerrf==1))  
				{
					oper_tig=tig_end;
					break;
				}
			 
				weldcyclestrt=0;
				 
				currerrf=0;
			 
				break;
			 }	
		 }//end switch 4T	
	  } 	//end if 4T  
	} //end non foot mode
}   //end funtion void

void preflow()
{
	if(weldcyclestrt==0)
    {
		strttmr=1;  			//@ strt timer for preflow
		timerval=0;
		time_100ms=0;
		Time_ms=0;
		
		//TIG_RELAY_1ON_0OFF=1;  //@turn on the gas relay
		tig_weld_cycle_current=0;
					
		weldcyclestrt=1;
		oper_tig=tig_pre;
	}
	if( (time_100ms>=para.tigmode.preflow) )
	{	
		//TIG_RELAY_1ON_0OFF=1;
		SHDNLAT=1;			  //OCV ON             			
		tig_weld_cycle_current=1; //@to avoid shutdown from going low in tig.c while checking tig_weld_cycle_current<0
		
				
		if((Type.fourt==1))
		{
		  tig_weld_cycle_current=para.tigmode.startcurrent;
		}  
		else if( (Type.twot==1) && (foot_1_normal_0==0) )	
		{				
			if(para.tigmode.upslopetime>0)
				tig_weld_cycle_current=min_current;
			else
				tig_weld_cycle_current=para.tigmode.setcurrent;
		} 
		else if (foot_1_normal_0==1)
		{
		tig_weld_cycle_current=min_current;
		}
		
	    oper_tig=tig_arcdet;
	    
	    strttmr=1;  			//@ strt timer for preflow
	    timerval=0;
		time_100ms=0;
		Time_ms=0;
	    
	}
	else
	{
		//TIG_RELAY_1ON_0OFF=1;
		oper_tig=tig_pre;
	}
	
    

}

void end1()
{
	SHDNLAT=0;			  //@OCV OFF    						
 	tig_weld_cycle_current=0;	
 	//TIG_RELAY_1ON_0OFF=0; //@turn on the relay
	
	strttmr=0;  			//@Stop timer
	timerval=0;
	time_100ms=0;
	Time_ms=0;
  
    if(currerrf==1)
    //ERROR_4_errorf=1;
	 
	 
   dispupdatef=1;
}
