
void MIG_superfast_PID(void)
{ht

	sf_outputmax=51200;// 64000;// 128*500=64000 51200;  //128*400amp
 
 	sf_mig_scalefactor =6;
 	sf_outputmax=32000;// 64000;// 128*500=64000 51200;  //128*400amp
  	if((program_number==2)||(program_number>=55)||(program_number<=60))    // MS (0.8)
  	{
	  	if(para.migmode.setwspeed < 110)
	  	{
	 		sf_kpgain = 100; //80; //save_location*2;   40  wirespeed above 11 / below 11 60/75
			sf_kigain = 12;  //18; //22; //22; //Recall_location; 12
			sf_kdgain = 20; //10; //35; //para.migmode.burnback; 20
			pidvalue  = 20; //20; 20
			mult_factor = 20; //10
		}
		else if (para.migmode.setwspeed >= 110)
		{
			sf_kpgain = 40; //80; //save_location*2;   40  wirespeed above 11 / below 11 60/75
			sf_kigain = 12;  //18; //22; //22; //Recall_location; 12
			sf_kdgain = 20; //10; //35; //para.migmode.burnback; 20
			pidvalue  = 20; //20; 20
			mult_factor = 10;
		}		
	}
	
	else if (program_number==1) // MS (1.0)
		{
			
			sf_kpgain = save_location*2; //90; //25; //save_location*2; //90(45*2);//150; //save_location*2; //10 + (para.migmode.setwspeed / 2);
			sf_kigain = Recall_location; //10; //10; //Recall_location; //22; 26; //Recall_location;
			sf_kdgain = para.migmode.inductance; //20; //10; //para.migmode.inductance; //10; //46; //para.migmode.inductance; //para.migmode.burnback;
			pidvalue  = 20;
			mult_factor = 10; //para.migmode.burnback; //80;
		}		
 	
 	else if ((program_number==14) || (program_number==13)) // MS (1.2)
 	{
	 		
			sf_kpgain = 90; //120; //150;   //10 + (para.migmode.setwspeed / 2);
			sf_kigain = 10; //18; //22; //Recall_location;
			sf_kdgain = 20; //5; //para.migmode.burnback;
			mult_factor = 10; //18;
			pidvalue  = 20;
		 	
	}
	else if ((program_number==25) || (program_number==26))  // MS (1.2)
	{
			sf_kpgain = 90; //190; //save_location*2;//40; //save_location*2;   //40
			sf_kigain = 10; //22; //Recall_location; //10; //Recall_location;  //15
			sf_kdgain = 20; //5; //para.migmode.burnback; //10; //para.migmode.burnback; //5
			mult_factor = 10; //para.migmode.inductance;  //20
			pidvalue  = 20;
			
	}
	else if ((program_number==37) || (program_number==38))   // MS (1.6)
	{
			sf_kpgain = 90; //40; //save_location*2; //40; //   
			sf_kigain = 10; //Recall_location; //10; //
			sf_kdgain = 20; //para.migmode.inductance; //para.migmode.burnback; //0; 
			mult_factor = 10; //para.migmode.inductance;
			pidvalue  = 20;
	}	
	
	else if ((program_number==8) || (program_number==20) || (program_number==32) || (program_number==44)) // SS (0.8/1/1.2/1.6)
	{
			sf_kpgain = 90; //180; //save_location*2; //40; //   
			sf_kigain = 10; //26; //Recall_location; //10; //
			sf_kdgain = 20; //5; //para.migmode.inductance; //para.migmode.burnback; //0; 
			mult_factor = 10;
			pidvalue  = 20;
	}
	else if ((program_number==35) || (program_number==47) || (program_number==33) || (program_number==34)) // Alu (1.2/1.6)
	{
			sf_kpgain = 90;//save_location*2; //90; //180; //save_location*2; //40; //   
			sf_kigain = 10;//Recall_location; //10; //26; //Recall_location; //10; //
			sf_kdgain = 20;//para.migmode.burnback; //20; //5; //para.migmode.inductance; //para.migmode.burnback; //0; 
			mult_factor = 10;//para.migmode.inductance; //10;
			pidvalue  = 20;
	}
	else if ((program_number==49) || (program_number==50) || (program_number==53) || (program_number==54))  // MSFCAW (1.2/1.6)
	{
			sf_kpgain = 90; //save_location*2; //90; //180; //save_location*2; //40; //   
			sf_kigain = 10; //Recall_location; //10; //26; //Recall_location; //10; //
			sf_kdgain = 20; //para.migmode.inductance; //20; //5; //para.migmode.inductance; //para.migmode.burnback; //0; 
			mult_factor = 10; //para.migmode.burnback; //10;
			pidvalue  = 20;
	}
	else if ((program_number==51) || (program_number==52)) // SSFACW (1.2)
	{
			sf_kpgain = 90; //save_location*2; //90; //180; //save_location*2; //40; //   
			sf_kigain = 10; //Recall_location; //10; //26; //Recall_location; //10; //
			sf_kdgain = 20; //para.migmode.inductance; //20; //5; //para.migmode.inductance; //para.migmode.burnback; //0; 
			mult_factor = 10; //para.migmode.burnback; //10;
			pidvalue  = 20;
	}
	else
	{
			sf_kpgain = save_location*2;//40; //80; //save_location*2;   40  wirespeed above 11 / below 11 60/75
			sf_kigain = Recall_location;//12;  //18; //22; //22; //Recall_location; 12
			sf_kdgain = para.migmode.inductance; //20; //10; //35; //para.migmode.burnback; 20
			pidvalue  = 20; //20; 20
			mult_factor = 10;
	}

			
	sf_setpoint=voltageref;
	sf_feedback=ACT_CVOLTAGE;//ACT_CVOLTAGE;
	
	sf_error=sf_setpoint-sf_feedback;
	
	if(sf_feedback <= 80)
		sf_pterm=(sf_kpgain*sf_error*mult_factor)/10;
	else		
		sf_pterm=sf_kpgain*sf_error;
	
	if((program_number==1) || (program_number==2)) //(program_number==02) 
	{	
		sf_accumulator+=((sf_error*sf_kigain)/10);
		
		if(sf_accumulator>=sf_outputmax)
 		{
	 		sf_accumulator=(sf_outputmax);
		}
		else if((sf_accumulator <= sf_outputmin))
		{
 			sf_accumulator= sf_outputmin; 
		}
			
		sf_dterm=(((sf_error-sf_preverror)*sf_kdgain)/10);
		sf_preverror=sf_error;			
		
		sf_pid=sf_pterm+sf_accumulator+sf_dterm;
	}
	else
	{
		sf_accumulator+=sf_error;
		
		if(sf_accumulator>=sf_outputmax)
		{
			sf_accumulator=(sf_outputmax);
		}
		else if((sf_accumulator <= sf_outputmin))
		{
			sf_accumulator= sf_outputmin; 
		}
		
		sf_iterm=((sf_accumulator*sf_kigain)/10);
	
		sf_dterm=(((sf_error-sf_preverror)*sf_kdgain)/10);
		sf_preverror=sf_error;
	
		sf_pid=sf_pterm+sf_iterm+sf_dterm;			
  	}	
	
	if(sf_pid>=sf_outputmax)
	sf_pid=sf_outputmax;
	else if(sf_pid<=sf_outputmin)
	sf_pid=sf_outputmin;
	
	sf_pidoutput=sf_pid>>sf_mig_scalefactor;
	if(sf_pidoutput<=pidvalue) 
	sf_pidoutput=pidvalue;
	if(sf_pidoutput>=500)
	sf_pidoutput=500;
	
	if(MIGweldon_detectf==0)
	{
	migdaccount=200;
	}	  
	else
	{
	migdaccount=sf_pidoutput;
	}	  	

}
