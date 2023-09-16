 
void check_torch_action()
{ 
	//TRANS1(torchonstatus);
	//TRANS1(weldcyclestrt);
	if(torchonstatus =='T' || weldcyclestrt==1) //torch function scan status.torchonstatus
	{
	   if(weldmode=='G' && universal_error_flag==0)
	   torchaction();
	   else if(weldmode=='P' && universal_error_flag==0)
	   torchaction_Pmig();   
	   
	   pstowfstr.psstatusbyte=psstatusu.psstatusbyte[0];
	   pstowfstr.wfstatusbyte=wfstatusu.wfstatusbyte[0];
	   if(prevwfcyclestatus!=pstowfstr.wfstatusbyte)
	   {
			//count_1sec=0;//800;
			//transmit2f=1;//1;
			emg_sendf=1;//
	   } 
	   prevwfcyclestatus=pstowfstr.wfstatusbyte;
	  // TRANS1('Y');
	}
	else 
	{
		cvoffsetref=0;
		voltageref=0;
		genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
	}

}

void torchaction()
{
      dummytorch=torchonstatus;
      if(weldcyclestrt==0)
      {
		oper=pre;
		psstatus.craterspeedon=0;
		cSoftDonefg = 0;
	  }

      if(wfstatus.twotfourtmode1==0) //@2T mode
      {
         switch(oper)
         {
            case pre:
            {
               if(weldcyclestrt==0)
               {
				error_4_check4t=0;
				cntsecond_er4=0;
				
				strttmr=1;
				timerval=0;
				cntsecond=0;
				cvrefon=0;
				psstatus.gasoncommand=1;                       //GASONLAT=1;
				psstatus.motoroncommand=0;			   //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=1;
				weldcyclestrt=1;
				oper=pre;
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
               }
               if(cntsecond >=(para.migmode.preflow*10))
               {
				strttmr=0;
				cntsecond=0;
				timerval=0;
				cvoffsetref=CVOFFSET;
				voltageref=para.migmode.setvoltage;
// changed on 22092020 by sachin				
// commented to adjust the delay of frame transmission;
// genrate the reference after few delay;
				cLoadReffg = 1;
				iLoadRefCntr = LOADREFCNT;				
//				genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 

				cvrefon=0;
				pulsestrtf=1;
				psstatus.weldoncyclestrt=1;		
				psstatus.gasoncommand=1;				  //GASONLAT=1;
				psstatus.motoroncommand=1;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
										
				oper=weld;
//--------------------				
iFreqError = 0;
//--------------------				
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
				
				cvoffsetref=CVOFFSET;
				voltageref=para.migmode.setvoltage;
				genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
				psstatus.gasoncommand=1;                       //GASONLAT=1;
				psstatus.motoroncommand=1;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=1;
				
				if(dummytorch!='T')
				{
				strttmr=1;
				cntsecond=0;
				timerval=0;
				psstatus.gasoncommand=1;                       //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=1;
				//ARCONLAT=1;
				pulsestrtf=0;
				cvrefon=1;
				oper=burn;
				cvoffsetref=CVOFFSET;
				fttrefvolt=190;
				voltageref=fttrefvolt;				
//				genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
// changed on 21102020 by sachin				
				cEndPulsefg = 1;
				cEndPulseCnt = ENPULSECNT;
				ENPULSECURR = LoadPeakCurrentasperDia();				
//				ARCONOKLAT = 1;													
				 error_4_check4t=0;
				}
           	break;
            }
            case burn:
            {
	            
	             
	             if(cntsecond >=(para.migmode.burnback))//already burnbacktime is stored in integer so not multiply by 10
	             {
					psstatus.gasoncommand=1;                       //GASONLAT=1;
					psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
					psstatus.weldoncyclestrt=1;
					strttmr=1;
					timerval=0;
					cntsecond=0;
					pulsestrtf=0;
					cvrefon=1;
					cvoffsetref=0;
					voltageref=0;
					genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
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
               if(cntsecond >=(para.migmode.postflow*10))
		    	{
				psstatus.gasoncommand=0;                       //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=1;
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref); 
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
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref); 
				psstatus.gasoncommand=0;                       //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=0;
				cntsecond=0;
				timerval=0;
				strttmr=0;
				weldcyclestrt=0;
				pulsestrtf=0;
				cvrefon=0;		
                break;
            }
      	}//endnig of switch case
      }//end of 2T if else
      else if(wfstatus.twotfourtmode1==1)
      {
         switch(oper)
         {
            case pre:
            {
               if(weldcyclestrt==0)
               {
	           	error_4_check4t=0;
				cntsecond_er4=0;    
	               
				strttmr=1;
				timerval=0;
				cntsecond=0;
				psstatus.gasoncommand=1;                       //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=1;
				pulsestrtf=0;
				cvrefon=0;	
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref); 	
				weldcyclestrt=1;
				oper=pre;
			   }
               else if(cntsecond >=(para.migmode.preflow*10))
               {
				error_4_check4t=0;
				cntsecond_er4=0;
				
				strttmr=0;
				cntsecond=0;
				timerval=0;
				pulsestrtf=1;
				cvrefon=0;
				cvoffsetref=CVOFFSET;
				voltageref= 0 ;//
//				genpwmcvref(cvoffsetref,voltageref); 
// changed on 22092020 by sachin				
// commented to adjust the delay of frame transmission;
// genrate the reference after few delay;
				cLoadReffg = 1;
				iLoadRefCntr = LOADREFCNT;				
//				genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
				psstatus.weldoncyclestrt=1;		
				psstatus.gasoncommand=1;				  //GASONLAT=1;
				psstatus.motoroncommand=0;				 //@not sure is this correct                  
				oper=weld;
			    
			    error_4_check4t=1;
				cntsecond_er4=0;
			    }
            break;
            }

            case weld:
            {
                oper=weld;
		        {
                if(dummytorch!='T' && torchrelease==0)            //VOLTAGE ON, WIRESPEED START AFTER RELEASE TORCH
                {
					torchrelease=1;
					oper=weld;
					pulsestrtf=1;
					cvrefon=0;
					cvoffsetref=CVOFFSET ;// 60; // ....+60 added on 07102019
					voltageref=para.migmode.setvoltage;
					genpwmcvref(cvoffsetref,voltageref); 
					psstatus.weldoncyclestrt=1;		
					psstatus.gasoncommand=1;				  //GASONLAT=1;
					psstatus.motoroncommand=1;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				}
                 else if(dummytorch!='T' && torchrelease==1 && cratersetup==0)         //VOLTAGE ON, WIRESPEED ON
                 {
					torchrelease=1;
					oper=weld;
					pulsestrtf=1;
					cvrefon=0;
					cvoffsetref=CVOFFSET;
					voltageref=para.migmode.setvoltage;
					genpwmcvref(cvoffsetref,voltageref); 
					psstatus.weldoncyclestrt=1;		
					psstatus.gasoncommand=1;				  //GASONLAT=1;
					psstatus.motoroncommand=1;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				}
                  else if(dummytorch=='T' && torchrelease==1 && cratersetup==0)// && Type.crateron==0)//TORCH PRESSED AGAIN CRATER FUNCTION
                  {
					oper=weld;
					pulsestrtf=1;
					cvrefon=0;	
					cvoffsetref=CVOFFSET;
					//para.migmode.cratervoltage=200.0;
					voltageref=para.migmode.cratervoltage;
					genpwmcvref(cvoffsetref,voltageref); 
					psstatus.weldoncyclestrt=1;		
					psstatus.gasoncommand=1;				  //GASONLAT=1;
					psstatus.motoroncommand=1;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
					if((para.migmode.craterspeed <= 20) && (cratersetup==0))      //changed on 23092020
					{
						strttmr=1; 		//changed on 23092020
						cntsecond=0;	//changed on 23092020
						timerval=0;		//changed on 23092020
						
						psstatus.motoroncommand=0;				
						voltageref=190;
						psstatus.craterspeedon=0;
						psstatus.gasoncommand=1; 	//changed on 23092020
						cratersetup=0;					
						oper=burn;     //changed on 23092020					
// changed on 21102020 by sachin				
				cEndPulsefg = 1;
				cEndPulseCnt = ENPULSECNT;
				ENPULSECURR = LoadPeakCurrentasperDia();										
						//oper=exiti;
					}
					else
					{
						psstatus.craterspeedon=1;
						cratersetup=1;											
					}	
					//TRANS1('E');
                  }
                  //else if((dummytorch==0 && torchrelease==1 && cratersetup==1 && Type.crateron==0) ||(dummytorch==1 && torchrelease==1 && cratersetup==1 && Type.crateron==1))
                 else if((dummytorch!='T' && torchrelease==1 && cratersetup==1 && crateron==0) ||(dummytorch=='T' && torchrelease==1 && cratersetup==1 && crateron==1))
                 {
					strttmr=1;
					cntsecond=0;
					timerval=0;
					pulsestrtf=0;
					cvrefon=1;
					cvoffsetref=CVOFFSET;
					voltageref=140.0;
//					genpwmcvref(cvoffsetref,voltageref); 
					psstatus.weldoncyclestrt=1;		
					psstatus.gasoncommand=1;				  //GASONLAT=1;
					psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
					oper=burn;
// changed on 21102020 by sachin				
				cEndPulsefg = 1;
				cEndPulseCnt = ENPULSECNT;
				ENPULSECURR = LoadPeakCurrentasperDia();				
//				ARCONOKLAT = 1;									
					error_4_check4t=0;
					cntsecond_er4=0;
				 }
               }
             break;
            }
            case burn:
            {
                                          //already burnbacktime is stored in integer so not multiply by 10
               if(cntsecond>=(para.migmode.burnback))
               {
					pulsestrtf=0;
					cvrefon=1;
					cvoffsetref=0;
					voltageref=0;
					genpwmcvref(cvoffsetref,voltageref); 
					psstatus.weldoncyclestrt=1;		
					psstatus.gasoncommand=1;				  //GASONLAT=1;
					psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
					
					strttmr=1;
					timerval=0;
					cntsecond=0;
				
					oper=post;
					
					error_4_check4t=0;
					cntsecond_er4=0;
				}
               if(dummytorch!='T' && torchval==0)         //&& Type.crater==1))// || (dummytorch==0 && torchval==0 && Type.crater==0))
               {
                  torchval=1;
               }
               else if(dummytorch=='T' && torchval==1)
               {
                  oper=exiti;
 			 //transoff.weldmodestatus=oper;
               }
               break;
            }
            case post:
            {
               if(cntsecond >=(para.migmode.postflow*10))
               {
				pulsestrtf=0;
				cvrefon=0;
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref); 
				psstatus.weldoncyclestrt=1;		
				psstatus.gasoncommand=0;				  //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				cntsecond=0;
				timerval=0;
				strttmr=0;
				oper=exiti;
				}
               if(dummytorch!='T' && torchval==0 )//&& Type.crater==1)// || (dummytorch==1 && torchval==0 && Type.crater==0))
               {
                  torchval=1;
               }
               else if(dummytorch=='T' && torchval==1)
               {
                  oper=exiti;
			 //transoff.weldmodestatus=oper;
               }
              break;
            }
            case exiti:
            {
				error_4_check4t=0;
				cntsecond_er4=0;
				
               if(dummytorch!='T')// && torchenable==1)
               {
				pulsestrtf=0;
				cvrefon=0;
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref); 
				psstatus.weldoncyclestrt=0;		
				psstatus.gasoncommand=0;				  //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				cntsecond=0;
				timerval=0;
				strttmr=0;
				weldcyclestrt=0;
				torchenable=0;
				torchrelease=0;
				
				torchval=0;
				fastexit=0;
			
				cratersetup=0;				
			   }
               else  //mahesh
               {
                  oper=exiti;
			   }
               break;
            }
      }//ending switch case
      }// end of else if 4t mode
} //function end


//function for P-MIG
void torchaction_Pmig()
{
      dummytorch=torchonstatus;
      if(weldcyclestrt==0)
      {
		oper=pre;
	  }

      if(wfstatus.twotfourtmode1==0) //@2T mode
      {
         switch(oper)
         {
            case pre:
            {
               if(weldcyclestrt==0)
               {
				error_4_check4t=0;
				cntsecond_er4=0;   
				
				strttmr=1;
				timerval=0;
				cntsecond=0;
				cvrefon=0;
				psstatus.gasoncommand=1;                       //GASONLAT=1;
				psstatus.motoroncommand=0;			   //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=1;
				weldcyclestrt=1;
				oper=pre;
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
               }
               if(cntsecond >=(para.pmigmode.preflow*10))
               {
				strttmr=0;
				cntsecond=0;
				timerval=0;
				cvoffsetref=CVOFFSET;
				voltageref= 0;//para.migmode.setvoltage;
				genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
				cvrefon=0;
				pulsestrtf=1;
				psstatus.weldoncyclestrt=1;		
				psstatus.gasoncommand=1;				  //GASONLAT=1;
//12.02.2019		psstatus.motoroncommand=1;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.motoroncommand=1;		// changed by sachin on 21102020 starting arc problem										
				oper=weld;
				
				error_4_check4t=1;
				cntsecond_er4=0;
			   }
               if(dummytorch!='T')
               {
                     oper=exiti;
			   }
		        break;
            }

            case weld:
            {
				oper=weld;
				cvrefon=0;
				pulsestrtf=1;
				
				cvoffsetref=CVOFFSET;
				voltageref=para.migmode.setvoltage;
				genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
				psstatus.gasoncommand=1;                       //GASONLAT=1;
				psstatus.motoroncommand=1;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=1;
				
				if(dummytorch!='T')
				{
				strttmr=1;
				cntsecond=0;
				timerval=0;
				psstatus.gasoncommand=1;                       //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=1;
				//ARCONLAT=1;
				pulsestrtf=0;
				cvrefon=1;
				oper=burn;
				cvoffsetref=CVOFFSET;
				fttrefvolt=190;
				voltageref=fttrefvolt;
				genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
				
				error_4_check4t=0;
				cntsecond_er4=0;				
// changed on 22102020 by sachin				
				cEndPulsefg = 1;
				cEndPulseCnt = ENPULSECNT;								
				ENPULSECURR = LoadPeakCurrentasperDia();				
				}
           	break;
            }
            case burn:
            {
	             if(cntsecond >=(para.pmigmode.burnback))//already burnbacktime is stored in integer so not multiply by 10
	             {
					psstatus.gasoncommand=1;                       //GASONLAT=1;
					psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
					psstatus.weldoncyclestrt=1;
					strttmr=1;
					timerval=0;
					cntsecond=0;
					pulsestrtf=0;
					cvrefon=1;
					cvoffsetref=0;
					voltageref=0;
					genpwmcvref(cvoffsetref,voltageref);   //genref(para.pwmtime1); 
					oper=post;
					
					error_4_check4t=0;
					cntsecond_er4=0;
			     }
               if(dummytorch=='T')
               {
                     oper=exiti;
			   }
               break;
            }
            case post:
            {
                error_4_check4t=0;
				cntsecond_er4=0;
                             
               if(cntsecond >=(para.pmigmode.postflow*10))
		    	{
				psstatus.gasoncommand=0;                       //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=1;
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref); 
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
				cntsecond_er4=0;
				
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref); 
				psstatus.gasoncommand=0;                       //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=0;
				cntsecond=0;
				timerval=0;
				strttmr=0;
				weldcyclestrt=0;
				pulsestrtf=0;
				cvrefon=0;		
                break;
            }
      	}//endnig of switch case
      }//end of 2T if else
      else if(wfstatus.twotfourtmode1==1)
      {
         switch(oper)
         {
            case pre:
            {
               if(weldcyclestrt==0)
               {
				error_4_check4t=0;
				cntsecond_er4=0;			
				
				strttmr=1;
				timerval=0;
				cntsecond=0;
				psstatus.gasoncommand=1;                       //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				psstatus.weldoncyclestrt=1;
				
				
				
				pulsestrtf=0;
				cvrefon=0;	
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref); 	
				weldcyclestrt=1;
				oper=pre;
			   }
               else if(cntsecond >=(para.pmigmode.preflow*10))
               {
				strttmr=0;
				cntsecond=0;
				timerval=0;
				pulsestrtf=1;
				cvrefon=0;
				cvoffsetref=CVOFFSET;
				voltageref=0;//para.migmode.setvoltage;
				genpwmcvref(cvoffsetref,voltageref); 
				psstatus.weldoncyclestrt=1;		
				psstatus.gasoncommand=1;				  //GASONLAT=1;
//				psstatus.motoroncommand=0;				 //@not sure is this correct                  
				psstatus.motoroncommand=1;		// changed by sachin on 21102020 starting arc problem
				oper=weld;
				
				error_4_check4t=1;
				cntsecond_er4=0;
			    }
            break;
            }

            case weld:
            {
                oper=weld;
		        {
                if(dummytorch!='T' && torchrelease==0)            //VOLTAGE ON, WIRESPEED START AFTER RELEASE TORCH
                {
					torchrelease=1;
					oper=weld;
					pulsestrtf=1;
					cvrefon=0;
					cvoffsetref=CVOFFSET;
					voltageref=para.migmode.setvoltage;
					genpwmcvref(cvoffsetref,voltageref); 
					psstatus.weldoncyclestrt=1;		
					psstatus.gasoncommand=1;				  //GASONLAT=1;
					psstatus.motoroncommand=1;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				}
                 else if(dummytorch!='T' && torchrelease==1 && cratersetup==0)         //VOLTAGE ON, WIRESPEED ON
                 {
					torchrelease=1;
					oper=weld;
					pulsestrtf=1;
					cvrefon=0;
					cvoffsetref=CVOFFSET;
					voltageref=para.migmode.setvoltage;
					genpwmcvref(cvoffsetref,voltageref); 
					psstatus.weldoncyclestrt=1;		
					psstatus.gasoncommand=1;				  //GASONLAT=1;
					psstatus.motoroncommand=1;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				}
                  else if(dummytorch=='T' && torchrelease==1 && cratersetup==0)// && Type.crateron==0)//TORCH PRESSED AGAIN CRATER FUNCTION
                  {
					oper=weld;
					pulsestrtf=1;
					cvrefon=0;	
					cvoffsetref=CVOFFSET;
					//para.migmode.cratervoltage=200.0;
					voltageref=para.pmigmode.cratervoltage;
					setrefparaf_crater=1;
					
					
					genpwmcvref(cvoffsetref,voltageref); 
					psstatus.weldoncyclestrt=1;		
					psstatus.gasoncommand=1;				  //GASONLAT=1;
					psstatus.motoroncommand=1;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
					
					if(para.pmigmode.craterspeed <= 20)
					{
						psstatus.motoroncommand=0;				
						voltageref=0;
						psstatus.craterspeedon=0;
						cratersetup=0;					
						setrefparaf_crater=0;						
// changed on 22102020 by sachin				
						cEndPulsefg = 1;
						cEndPulseCnt = ENPULSECNT;	
						ENPULSECURR = LoadPeakCurrentasperDia();												
					}
					else
					{
						cratersetup=1;					
						setrefparaf_crater=1;
						psstatus.craterspeedon=1;						
					}							
					//TRANS1('E');
                  }
                  //else if((dummytorch==0 && torchrelease==1 && cratersetup==1 && Type.crateron==0) ||(dummytorch==1 && torchrelease==1 && cratersetup==1 && Type.crateron==1))
                 else if((dummytorch!='T' && torchrelease==1 && cratersetup==1 && crateron==0) ||(dummytorch=='T' && torchrelease==1 && cratersetup==1 && crateron==1))
                 {
					strttmr=1;
					cntsecond=0;
					timerval=0;
					pulsestrtf=0;
					cvrefon=1;
					cvoffsetref=CVOFFSET;
					voltageref=para.pmigmode.cratervoltage;//140.0;
					
				    psstatus.craterspeedon=0;
					
					genpwmcvref(cvoffsetref,voltageref); 
					psstatus.weldoncyclestrt=1;		
					psstatus.gasoncommand=1;				  //GASONLAT=1;
					psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
					oper=burn;
				 
					error_4_check4t=0;
					cntsecond_er4=0;				
// changed on 22102020 by sachin				
					cEndPulsefg = 1;
					cEndPulseCnt = ENPULSECNT;
					ENPULSECURR = LoadPeakCurrentasperDia();
				 }
               }
             break;
            }
            case burn:
            {
                                          //already burnbacktime is stored in integer so not multiply by 10
               if(cntsecond>=(para.pmigmode.burnback))
               {
					pulsestrtf=0;
					cvrefon=1;
					cvoffsetref=0;
					voltageref=0;
					genpwmcvref(cvoffsetref,voltageref); 
					psstatus.weldoncyclestrt=1;		
					psstatus.gasoncommand=1;				  //GASONLAT=1;
					psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
					
					strttmr=1;
					timerval=0;
					cntsecond=0;
				
					oper=post;
					
					error_4_check4t=0;
					cntsecond_er4=0;
				}
               if(dummytorch!='T' && torchval==0)         //&& Type.crater==1))// || (dummytorch==0 && torchval==0 && Type.crater==0))
               {
                  torchval=1;
               }
               else if(dummytorch=='T' && torchval==1)
               {
                  oper=exiti;
 			 //transoff.weldmodestatus=oper;
               }
               break;
            }
            case post:
            {
               if(cntsecond >=(para.pmigmode.postflow*10))
               {
				pulsestrtf=0;
				cvrefon=0;
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref); 
				psstatus.weldoncyclestrt=1;		
				psstatus.gasoncommand=0;				  //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				cntsecond=0;
				timerval=0;
				strttmr=0;
				oper=exiti;
				
				error_4_check4t=0;
				cntsecond_er4=0;
				}
               if(dummytorch!='T' && torchval==0 )//&& Type.crater==1)// || (dummytorch==1 && torchval==0 && Type.crater==0))
               {
                  torchval=1;
               }
               else if(dummytorch=='T' && torchval==1)
               {
                  oper=exiti;
			 //transoff.weldmodestatus=oper;
               }
              break;
            }
            case exiti:
            {
                error_4_check4t=0;
				cntsecond_er4=0;
               
               if(dummytorch!='T')// && torchenable==1)
               {
				pulsestrtf=0;
				cvrefon=0;
				cvoffsetref=0;
				voltageref=0;
				genpwmcvref(cvoffsetref,voltageref); 
				psstatus.weldoncyclestrt=0;		
				psstatus.gasoncommand=0;				  //GASONLAT=1;
				psstatus.motoroncommand=0;				  //softstart_motor(para.pwmtime);                  //drive_motor(para.pwmtime);
				cntsecond=0;
				timerval=0;
				strttmr=0;
				weldcyclestrt=0;
				torchenable=0;
				torchrelease=0;
				
				torchval=0;
				fastexit=0;
			
				cratersetup=0;
			   }
               else  //mahesh
               {
                  oper=exiti;
			   }
               break;
            }
      }//ending switch case
      }// end of else if 4t mode
} //function end