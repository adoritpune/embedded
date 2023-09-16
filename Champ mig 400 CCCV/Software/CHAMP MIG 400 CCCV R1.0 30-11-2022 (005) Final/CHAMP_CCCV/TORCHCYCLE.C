void check_torch_action()
{  
	if(TORCH_SW == 'T' || weldcyclestrt==1) 
	{
	   if(weldmode=='G' && universal_error_flag==0)
		{
	   		torchaction(); 
		}
	}
	else if(universal_error_flag == 1)
	{
		Generate_Reference(0);		
	}	     
}

void torchaction()
{
      dummytorch=TORCH_SW;
      if(weldcyclestrt==0)
      {
		oper=pre;
		cSoftDonefg = 0;
	  }	
      if(Type.twot==1) //@2T mode
      {
         switch(oper)
         {
            case pre:
            {
	            cForcefullyOFFOCVfg=0;
				if(weldcyclestrt==0)
				{
					error_4_check4t=0;
					cntsecond_er4=0;
					GAS_RELAYLAT = 1;
					strttmr=1;
					timerval=0;
					cntsecond=0;
					cvrefon=0;
					weldcyclestrt=1;
					oper=pre;
					cPWMLockfg=1;
					cTestWSLockfg=1;
					cTestVtgLockfg=1;
					iPWMClosecnt=PWM_CLOSE_CNT;
					cLockDACreffg=1;
					cMotorStopfg = 1;																				
				}
				if(cntsecond >= mig_preflow*10)
				{
					strttmr=0;
					cntsecond=0;
					timerval=0;
					GAS_RELAYLAT = 1;
					cvrefon=0;
					pulsestrtf=1;
					cCreepDetectafterPreflowfg=1;
					cTorchPressFoundfg = 1;
					if(cMotorStopfg == 1)
					{
						cMotorStopfg = 0;
					}
					oper=weld;		
				}
				if(dummytorch!='T')
				{
					oper=exiti;
				}
		        break;
            }

            case weld:
            {
				error_4_check4t=1;
	
				oper=weld;
				cvrefon=0;
				pulsestrtf=1;
				
				cLockDACreffg=0;
				
				if(dummytorch!='T')
				{
					strttmr=1;
					cntsecond=0;
					timerval=0;
					pulsestrtf=0;
					cvrefon=1;
					oper=burn; 
					cMotorStopForENDPulsefg=1;
					iWaitToStopMtrCnt = WAITTOSTOPCNT;
				 	error_4_check4t=0;
				}
           		break;
            }
            case burn:
            {	          	             
	             if(cntsecond >=mig_burnback)
	             {
					strttmr=1;
					timerval=0;
					cntsecond=0;
					pulsestrtf=0;
					cvrefon=1; 
					oper=post; 	 	
					error_4_check4t=0;
			     }
                 if(dummytorch=='T')
                 {
                     oper=exiti;
			     }
                 break;
            }
            case post:
            {
				cForcefullyOFFOCVfg=1;
				cMotorStopfg = 1;
				if(cntsecond >= mig_postflow*10)
				{
					GAS_RELAYLAT = 0;  	 	
					cntsecond=0;
					timerval=0;
					strttmr=0;
					pulsestrtf=0;
					cvrefon=0;					//used for pulse mode only
					oper=exiti;
				}
				if(dummytorch=='T')
				{
					oper=exiti;
				}
		       	break;
            }
            case exiti:
            {
				error_4_check4t=0;
				cCreepEndfg=0;
				if(cMotorStopfg == 1)
				{
					//cMotorStopfg=0;	 
				}
				inch_motor(0); //-----------------
				cntsecond=0;
				timerval=0;
				strttmr=0;
				weldcyclestrt=0;
				pulsestrtf=0;
				cvrefon=0;
				cTestWSLockfg=0;
				cTestVtgLockfg=0;
				//MPWM=0;	

                break;
            }
      	}//endnig of switch case
      }//end of 2T if else
      else if(Type.fourt==1)
      {
         switch(oper)
         {
            case pre:
            {
	           cForcefullyOFFOCVfg=0;
               if(weldcyclestrt==0)
               {
					error_4_check4t=0;
					cntsecond_er4=0;
					GAS_RELAYLAT = 1;
					strttmr=1;
					timerval=0;
					cntsecond=0;
					cvrefon=0;
					weldcyclestrt=1;
					oper=pre;
					cPWMLockfg=1;
					cTestWSLockfg=1;
					cTestVtgLockfg=1;
					iPWMClosecnt=PWM_CLOSE_CNT;
					cLockDACreffg=1;
					//cMotorStopfg = 1;	
											
               }
               else if((cntsecond >= mig_preflow*10) && (dummytorch=='X'))
               {
					strttmr=0;
					cntsecond=0;
					timerval=0;
					GAS_RELAYLAT = 1;
					cvrefon=0;
					pulsestrtf=1;
					cTorchPressFoundfg = 1;
					if(cMotorStopfg == 1)
					{
						cMotorStopfg = 0;
					}
					//cMotorStopfg = 1;										

					//MPWM=0;	
					cCreepKifg=1;
					cCreepLatchfg=1;						
					IRCreepcurr = iWireSpeed*mig_creepspeedrate*0.01;
					iCreepSpeedDowncnt=mig_creepspeedtime*10;//CREEP_SPEED_DOWN_CNT;
					Generate_Reference(IRCreepcurr);															
					oper=weld;
			    }
            	break;
            }

            case weld:
            {
	            error_4_check4t=1;
                oper=weld;
		        {
					if((dummytorch=='T' && torchrelease==0))
					{
						cForcefullyOFFOCVfg = 1;									
					}				        
	                else if(dummytorch=='X' && torchrelease==0)            //VOLTAGE ON, WIRESPEED START AFTER RELEASE TORCH
	                {
						cForcefullyOFFOCVfg = 0;																					
						torchrelease=1;
						oper=weld;										
					}				
					else if(dummytorch=='X' && torchrelease==1 && cratersetup==0)         //VOLTAGE ON, WIRESPEED ON
					{											
						torchrelease=1;
						oper=weld;												
					}	
					else if(dummytorch=='T' && torchrelease==1 && cratersetup==0)		//TORCH PRESSED AGAIN CRATER FUNCTION
					{
						oper=weld;												
						cCraterLatchfg = 1;
						cratersetup=1;																														
					}																                         
					else if((dummytorch=='X' && torchrelease==1 && cratersetup==1))
					{
						strttmr=1;
						
						cntsecond=0;
						timerval=0;
						pulsestrtf=0;						
						cvrefon=1;
						oper=burn;					
						cMotorStopForENDPulsefg=1;
						iWaitToStopMtrCnt = WAITTOSTOPCNT;				
						cntsecond_er4=0;
						//error_4_check4t=0;
						cCraterLatchfg = 0;						
					}		
              	}
             	break;
            }
            case burn:
            {
				if(cntsecond >= mig_burnback)
				{
					pulsestrtf=0;
					cvrefon=1;
					cvoffsetref=0;
					voltageref=0;
					
					strttmr=1;
					timerval=0;
					cntsecond=0;
					//MPWM=1;					
					cratersetup=0;	            
		            iCraterWS=0;
		            //Generate_Reference(iCraterWS);

					oper=post;					
					//error_4_check4t=0;
					//cntsecond_er4=0;
				}
				if(dummytorch!='T' && torchval==0)         //&& Type.crater==1))// || (dummytorch==0 && torchval==0 && Type.crater==0))
				{
					torchval=1;
				}
				else if(dummytorch=='T' && torchval==1)
				{
					oper=exiti;
					//error_4_check4t=0;
					//cntsecond_er4=0;
				}
				break;
            }
            case post:
            {
	            cForcefullyOFFOCVfg=1; 
	            cMotorStopfg = 1;         	
			   
				if(cntsecond >= mig_postflow*10)
				{
					iCraterWS=0;
					cMotorStopfg = 1;         	
					//Generate_Reference(iCraterWS);
					GAS_RELAYLAT = 0;  	 	
					pulsestrtf=0;
					cvrefon=0;
					cvoffsetref=0;
					voltageref=0;
					cntsecond=0;
					timerval=0;
					strttmr=0;
					//MPWM=0;
	
					oper=exiti;
				}
				if(dummytorch!='T' && torchval==0)//&& Type.crater==1)// || (dummytorch==1 && torchval==0 && Type.crater==0))
				{
					torchval=1;
				}
				else if(dummytorch=='T' && torchval==1)
				{
					oper=exiti;
					//error_4_check4t=0;
					//cntsecond_er4=0;
				}
               
              break;
            }
            case exiti:
            {	            

	
               if(dummytorch!='T')
               {
					pulsestrtf=0;
					cvrefon=0;
					cvoffsetref=0;
					voltageref=0;
					cCreepEndfg=0;
					if(cMotorStopfg == 1)
					{
//						cMotorStopfg=0;	 
					}	
					cntsecond=0;
					timerval=0;
					strttmr=0;
					weldcyclestrt=0;
					torchenable=0;
					torchrelease=0;
					inch_motor(0); //----------------
					torchval=0;
					fastexit=0;
					error_4_check4t=0;
					cTestVtgLockfg = 0;
					error4_flag=0;
					ERROR_4_errorf=0;
					cratersetup=0;				
			   }
               else  
               {
                  oper=exiti;
			   }				   
               break;
            }
      }//ending switch case
      }// end of else if 4t mode
} //function end

