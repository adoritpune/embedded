//###############################################################################################################
void OLD_frequency_update_pid()
{
    static unsigned int scalefactor1=20,maxmpwm1=500;
    PID_sParams1.ReferenceSetpoint1	=(para.pmigmode.setvoltage);//mfreq;  //setwsfreq;		//pidsetarcvoltage;			//Setarcvtg;				//(setvoltage<<1);					//setvoltage;
    PID_sParams1.feedback1			=(BVOLTAGE);//VOLTAGE;//setwsfreq;		//mfreq;						//Arcvtg;					//(actualweldvtg<<1);               Arcvtg                 //weldvoltage;
    PID_sParams1.error1 			= PID_sParams1.feedback1-PID_sParams1.ReferenceSetpoint1;
    PID_sParams1.absolute_error1	= abs(PID_sParams1.error1);
    //PID_sParams1.a1=0.3;//0.2;//0.3;
    //PID_sParams1.b1=0.02;//0.01;	
    //PID_sParams1.c1=0.01;//0;//0.01;//0.05;		
    //PID_sParams.d=1000;
    PID_sParams1.outmax1=10000;
    scalefactor1=PID_sParams1.outmax1/maxmpwm1;//maxbasetime;
    PID_sParams1.derivitive1 = PID_sParams1.error1 - PID_sParams1.previous_error1;
    //if(pidParams.absolute_error>10.0)
    {
        PID_sParams1.output1=PID_sParams1.output1 +((PID_sParams1.a1*PID_sParams1.error1))+ (PID_sParams1.b1*PID_sParams1.previous_error1) + (PID_sParams1.c1*PID_sParams1.pprevious_error1);
        if(PID_sParams1.output1 <= 0)
        {
            PID_sParams1.output1=0;
        }
        else if(PID_sParams1.output1>PID_sParams1.outmax1)
        {
            PID_sParams1.output1=PID_sParams1.outmax1;
        }
	  	scaled_output1=(PID_sParams1.output1/scalefactor1);
    }
		
		if (scaled_output1>500)
   		{
       		scaled_output1=500;
   		}
   		//if(scaled_output1>20 && scaled_output1<=500)
		if(scaled_output1 >= minbasetime && scaled_output1 <= maxbasetime)
	   	{
			pulsebase=scaled_output1;
   		}
		PID_sParams1.pprevious_error1=	PID_sParams1.previous_error1;
		PID_sParams1.previous_error1 = 	PID_sParams1.error1;
		//*************************************************
		//reference_area=4000.0;
		/*baseamp=2400.0/pulsebase;//24000.0
		if(baseamp<=40)
		{
			baseamp=40;
		}
		else if(baseamp>=60)//curwirespeed)
		{
			baseamp=60;
		}
		bdaccount=(CCOFFSET+(baseamp*CCSLOPE)) + (ERRCCOFFSET+(baseamp*ERRCCSLOPE));
		*/
		//**********************************************
		/*if(scaled_output1>50 && scaled_output1<=300)
   		{
   		    pulsebase=scaled_output1;
   		}
   		pulsebase=refpulsebase;
   		
		PID_sParams1.pprevious_error1=PID_sParams1.previous_error1;
		PID_sParams1.previous_error1 = PID_sParams1.error1;
		
		//reference_area=24000.0;
		baseamp=2400.0/pulsebase;//24000.0
		if(baseamp<=30)
		{
			baseamp=30;
		}
		else if(baseamp>=60)//curwirespeed)
		{
			baseamp=60;
		}
		baseamp=30.0;
		bdaccount=(CCOFFSET+(baseamp*CCSLOPE)) + (ERRCCOFFSET+(baseamp*ERRCCSLOPE));
		//bdaccount=CCOFFSET+(baseamp*4.70);
		*/		
}

void local_pid()
{
   		pidParams.Kp=70;//50;//20;
    	pidParams.Ki=0;//5;//2;//10
		pidParams.Kd=0;//40;//20 //5
	   	pidParams.ReferenceSetpoint=(para.pmigmode.setvoltage);
    	pidParams.feedback=(BVOLTAGE);
    	//pidParams.error = pidParams.feedback - pidParams.ReferenceSetpoint;
    	pidParams.error = pidParams.ReferenceSetpoint - pidParams.feedback;
    	pidParams.absolute_error=abs(pidParams.error);
    	pidParams.outmax=50000;
    	scalefactor=100;//250;  
	   	if((pidParams.error > 0.5) || (pidParams.error < -0.5))
    	{
			pidParams.integral = pidParams.integral+pidParams.error;
			if(pidParams.integral >= pidParams.outmax)
			{
				pidParams.integral=pidParams.outmax;
			}
			if(pidParams.integral <= 0)
			{
				pidParams.integral=0;
			}
			pidParams.derivitive = pidParams.error - pidParams.previous_error;
			pidParams.pidoutput =	((pidParams.Kp * pidParams.error)
		                  +(pidParams.Ki * pidParams.integral)
		                  +(pidParams.Kd * pidParams.derivitive));
			
			if(pidParams.output >= pidParams.outmax)
			{
				pidParams.output = pidParams.outmax;
			}
	    }
   		//scaled_val1=(pidParams.output/scalefactor);
   		scaled_val1=(pidParams.pidoutput/scalefactor);
   		if(scaled_val1>20 && scaled_val1<=500)
		//if(scaled_output1>minbasetime && scaled_output1<=maxbasetime)
	   	{
			pulsebase=scaled_output1;
   		}
   		pidParams.previous_error = pidParams.error;
   		
   	/*	if (scaled_val1>200)
   		{
       		scaled_val1=200;
       	}
   		if(scaled_val1>40 && scaled_val1<=200)
   		{
			if(scaled_val1<70)
				sdaccount=CCOFFSET+(70.0*4.70);
			else
				sdaccount=CCOFFSET+(scaled_val1*4.70);
				
			bdaccount=CCOFFSET+(scaled_val1*4.70);
			baseamp=scaled_val1;
		
			//if(baseamp > refbaseamp)
			//{
			// 	pulsebase=refpulsebase-(baseamp/10.0);
		    //}   
		    
		}
		scaled_val2=scaled_val1/2;
   		if(scaled_val2>0 && scaled_val2<=100)
   		{
   		    pulsebase=refpulsebase+scaled_val2;
   		}
   		
   		//refpulsebase=pulsebase;
   		//else
		//{
		//newpeakamp=scaled_output1;
		//if(newpeakamp<=400)
		//newpeakamp=400;	
		//pdaccount=CCOFFSET+(newpeakamp*4.70);
		//}
		pidParams.previous_error = pidParams.error;
    }

	kp_prev=pidParams.Kp;
	kd_prev=pidParams.Kd;
	ki_prev=pidParams.Ki;*/
	//new_gain_update();
}

void frequency_update_pid1()
{
    static unsigned int scalefactor1=20,maxmpwm1=500;
    PID_sParams1.ReferenceSetpoint1	=(para.pmigmode.setvoltage);//mfreq;  //setwsfreq;		//pidsetarcvoltage;			//Setarcvtg;				//(setvoltage<<1);					//setvoltage;
    PID_sParams1.feedback1			=(BVOLTAGE);//setwsfreq;		//mfreq;						//Arcvtg;					//(actualweldvtg<<1);               Arcvtg                 //weldvoltage;
    PID_sParams1.error1 			=PID_sParams1.feedback1-PID_sParams1.ReferenceSetpoint1;
    PID_sParams1.absolute_error1	 =abs(PID_sParams1.error1);
    PID_sParams1.a1=0.2;//0.2;
    PID_sParams1.b1=0.1;//0.2	
    PID_sParams1.c1=0.05;//0.05;		
    //PID_sParams.d=1000;
    PID_sParams1.outmax1=10000;
    scalefactor1=PID_sParams1.outmax1/maxmpwm1;//maxbasetime;
    PID_sParams1.derivitive1 = PID_sParams1.error1 - PID_sParams1.previous_error1;
    //if(pidParams.absolute_error>10.0)
    {
        PID_sParams1.output1=PID_sParams1.output1 +((PID_sParams1.a1*PID_sParams1.error1))+ (PID_sParams1.b1*PID_sParams1.previous_error1) + (PID_sParams1.c1*PID_sParams1.pprevious_error1);
        if(PID_sParams1.output1 <= 0)
        {
            PID_sParams1.output1=0;
        }
        else if(PID_sParams1.output1>PID_sParams1.outmax1)
        {
            PID_sParams1.output1=PID_sParams1.outmax1;
        }
	  	scaled_output1=(PID_sParams1.output1/scalefactor1);
    }
		if(scaled_output1>50 && scaled_output1<=300)
   		{
   		    pulsebase=scaled_output1;
   		}
   		pulsebase=refpulsebase;
   		
		PID_sParams1.pprevious_error1=PID_sParams1.previous_error1;
		PID_sParams1.previous_error1 = PID_sParams1.error1;
		
		//reference_area=24000.0;
		baseamp=2400.0/pulsebase;//24000.0
		if(baseamp<=30)
		{
			baseamp=30;
		}
		else if(baseamp>=60)//curwirespeed)
		{
			baseamp=60;
		}
		baseamp=30.0;
		bdaccount=CCOFFSET+(baseamp*4.70);		
}



void local_pid1()
{
   {
    	pidParams.ReferenceSetpoint=(para.pmigmode.setvoltage);
    	pidParams.feedback=(BVOLTAGE);
    	//pidParams.error = pidParams.feedback - pidParams.ReferenceSetpoint;
    	pidParams.error = pidParams.ReferenceSetpoint - pidParams.feedback;
    	pidParams.absolute_error=abs(pidParams.error);
    	pidParams.outmax=50000;
    	scalefactor=250;  

    	if((pidParams.error > 0.5) || (pidParams.error < -0.5))
    	{
			pidParams.integral = pidParams.integral+pidParams.error;
			if(pidParams.integral >= pidParams.outmax)
			{
				pidParams.integral=pidParams.outmax;
			}
			if(pidParams.integral <= 0)
			{
				pidParams.integral=0;
			}
			pidParams.derivitive = pidParams.error - pidParams.previous_error;
		
			pidParams.pidoutput =	((pidParams.Kp * pidParams.error)
		                  +(pidParams.Ki * pidParams.integral)
		                  +(pidParams.Kd * pidParams.derivitive));
			
			if(pidParams.output >= pidParams.outmax)
			{
				pidParams.output = pidParams.outmax;
			}
			
			/*if(pidParams.pidoutput>=50000)
			{
				pidParams.pidoutput=50000;
			}
			pidParams.output=30+(pidParams.pidoutput);
			if(pidParams.output >= pidParams.outmax)
			{
				pidParams.output = pidParams.outmax;
			}
			else if (pidParams.output <= 30)
			{
				pidParams.output=30;
			}*/
        }
   		//scaled_val1=(pidParams.output/scalefactor);
   		scaled_val1=(pidParams.pidoutput/scalefactor);
   		if (scaled_val1>200)
   		{
       		scaled_val1=200;
       	}
   		if(scaled_val1>40 && scaled_val1<=200)
   		{
			if(scaled_val1<70)
				sdaccount=CCOFFSET+(70.0*4.70);
			else
				sdaccount=CCOFFSET+(scaled_val1*4.70);
				
			bdaccount=CCOFFSET+(scaled_val1*4.70);
			baseamp=scaled_val1;
		
			/*if(baseamp > refbaseamp)
			{
			 	pulsebase=refpulsebase-(baseamp/10.0);
		    }*/   
		    
		}
		scaled_val2=scaled_val1/2;
   		if(scaled_val2>0 && scaled_val2<=100)
   		{
   		    pulsebase=refpulsebase+scaled_val2;
   		}
   		
   		//refpulsebase=pulsebase;
   		/*else
		{
		//newpeakamp=scaled_output1;
		//if(newpeakamp<=400)
		//newpeakamp=400;	
		//pdaccount=CCOFFSET+(newpeakamp*4.70);
		}*/
		pidParams.previous_error = pidParams.error;
    }

	kp_prev=pidParams.Kp;
	kd_prev=pidParams.Kd;
	ki_prev=pidParams.Ki;
	//new_gain_update();
}

void new_gain_update()
{
    gamma1=5;
    gamma2=5;
    gamma3=5;
    if((pidParams.error > 0.1) || (pidParams.error < -0.1))
    {
      if(abs(pidParams.error) > abs(pidParams.previous_error) && (pidParams.error !=0))
      {
        pidParams.Kp=kp_prev+(gamma1*pidParams.error*pidParams.error);
        pidParams.Kd=kd_prev+(gamma2*pidParams.error*pidParams.derivitive);
        pidParams.Ki=ki_prev+(gamma3*pidParams.error*pidParams.integral);
        if(pidParams.Ki>100)
        {
            pidParams.Ki=100;
        }
        else if(pidParams.Ki<=0)
        {
            pidParams.Ki=1;
        }
        if(pidParams.Kp>100)
        {
            pidParams.Kp=100;
        }
        else if(pidParams.Kp<=0)
        {
            pidParams.Kp=1;
        }
        if(pidParams.Kd>100)
        {
            pidParams.Kd=100;
        }
        else if(pidParams.Kd<=0)
        {
            pidParams.Kd=1;
        }
      }
     }
     else
    {
        pidParams.Kp=kp_prev;
        pidParams.Kd=kd_prev;
        pidParams.Ki=ki_prev;
    }
}

void base_current_pid()
{
		pidParams.ReferenceSetpoint=(para.pmigmode.setvoltage);
    	pidParams.feedback=(BVOLTAGE);
    	pidParams.error = pidParams.ReferenceSetpoint-pidParams.feedback;
    	pidParams.absolute_error=abs(pidParams.error);
    	pidParams.outmax=50000;
    	scalefactor=100;
    	pidParams.outmax1=50000;
    	scalefactor2=100;
    	pidParams.outmin1=0;//-50000;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    	if(pidParams.absolute_error<=10.0)
    	{
			pidParams.integral = pidParams.integral+pidParams.error;
			if(pidParams.integral >= pidParams.outmax)
			{
				pidParams.integral=pidParams.outmax;
			}
			if(pidParams.integral <= 0)
			{
				pidParams.integral=0;
			}
			pidParams.derivitive = pidParams.error - pidParams.previous_error;
		
			pidParams.pidoutput =	((pidParams.Kp * pidParams.error)
		                  +(pidParams.Ki * pidParams.integral)
		                  +(pidParams.Kd * pidParams.derivitive));
			
			if(pidParams.output >= pidParams.outmax)
			{
				pidParams.output = pidParams.outmax;
			}
			
        
   			scaled_val1=(pidParams.pidoutput/scalefactor);
   			if (scaled_val1>200)
   			{
       		scaled_val1=200;
       		}
   			if(scaled_val1>40 && scaled_val1<=200)
   			{
	   			
			if(scaled_val1<70)
				sdaccount=CCOFFSET+(70.0*4.70);
			else
				sdaccount=CCOFFSET+(scaled_val1*4.70);
				
			bdaccount=CCOFFSET+(scaled_val1*4.70);
			baseamp=scaled_val1;  
		    
			}	
			pidParams.previous_error = pidParams.error;
		}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        


}



void combined_pid()
{
		pidParams.ReferenceSetpoint=(para.pmigmode.setvoltage);
    	pidParams.feedback=(BVOLTAGE);
    	pidParams.error = pidParams.ReferenceSetpoint-pidParams.feedback;
    	pidParams.absolute_error=abs(pidParams.error);
    	pidParams.outmax=50000;
    	scalefactor=250;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    	if(pidParams.absolute_error<=10.0)
    	{
			pidParams.integral = pidParams.integral+pidParams.error;
			if(pidParams.integral >= pidParams.outmax)
			{
				pidParams.integral=pidParams.outmax;
			}
			if(pidParams.integral <= 0)
			{
				pidParams.integral=0;
			}
			pidParams.derivitive = pidParams.error - pidParams.previous_error;
			pidParams.pidoutput =	((pidParams.Kp * pidParams.error)
		                  +(pidParams.Ki * pidParams.integral)
		                  +(pidParams.Kd * pidParams.derivitive));
			
			if(pidParams.output >= pidParams.outmax)
			{
				pidParams.output = pidParams.outmax;
			}
			
        
   			scaled_val1=(pidParams.pidoutput/scalefactor);
   			if (scaled_val1>200)
   			{
       		scaled_val1=200;
       		}
       		if (scaled_val1<=0)
   			{
       		scaled_val1=0;
       		}
   			if(scaled_val1>40 && scaled_val1<=200)
   			{
	   			
			if(scaled_val1<70)
				sdaccount=CCOFFSET+(70.0*4.70);
			else
				sdaccount=CCOFFSET+(scaled_val1*4.70);
				
			bdaccount=CCOFFSET+(scaled_val1*4.70);
			baseamp=scaled_val1;  
		    
			}
			if(scaled_output1>30 && scaled_output1<=200)
   			{
   		    pulsebase=200-scaled_val1;
   			}	
			pidParams.previous_error = pidParams.error;
		}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        


}