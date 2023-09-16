struct pidParameters2
{
	float Kp2;
	float Ki2;
	float Kd2;
	float Kf2;
	
	signed long error2;
    signed long output2;
    signed long previous_output2;
    float Kp2new;
	float Ki2new;
	float Kd2new;
	float kpgain2;
	float kigain2;
	float kdgain2;
	//float plant_output;
    	//float plant_previous_output;
    	//float plant_pre_previous_output;
	signed long outmax2;
	signed long ReferenceSetpoint2;
	signed long feedback2;
	signed long integral2;
	signed long derivitive2;
	signed long previous_error2;
    unsigned long absolute_error2;
	signed long saturated2;
	signed long pidoutput2;
	signed long Kpterm2;
	signed long Kiterm2;
	signed long kdterm2;
} 	pidParams2;

void Adaptive_base_pid()
{
        //unsigned int scalefactor2=0,minfmspeed=50,scaled_baseval2=0,maxfmspeed=750;//2800;
//    if(1)//
//    {
        pidParams2.Kp2=42; //2;
        pidParams2.Ki2=2; //0.5;
        pidParams2.Kd2=20;//0.50;//0.5;//2;
/*
    }
    else // changed for testing 16092019
    {
        pidParams2.Kp2=4.0;
        pidParams2.Ki2=0.5;
        pidParams2.Kd2=0;//0.50;//0.5;//2;
    }
     */
        pidParams2.ReferenceSetpoint2=setpfreq;//pfreq;//hysetvtg;//hylowsetvtg;//hysetvtg;//setvoltage;//(para.pmigmode.setvoltage);;//psetcurrent;//440.0;//(para.pmigmode.setvoltage);
        pidParams2.feedback2=Fltpfreq;//pfreq;//setpfreq;;//actualweldvtg;//CVOLTAGE;//(BVOLTAGE);//psetcurrent;//PVOLTAGE;//(BVOLTAGE);
        disp1term=pidParams2.ReferenceSetpoint2;//500+pidParams2.error2;
        disp2term=pidParams2.feedback2;//500+pidParams2.error2;

        pidParams2.error2 = pidParams2.ReferenceSetpoint2 - pidParams2.feedback2;
        pidParams2.feedback2=0;
        pidParams2.outmax2=50000;
        scalefactor2=66.0;//pidParams2.outmax2/(maxfmspeed-minfmspeed);//71.00;//2800;//(stepamp-baseamp);
        //if((pidParams.error > 0.5) || (pidParams.error < -0.5))
    	//if((((pidParams2.error2 > 100) || (pidParams2.error2 < -100)) && fixintervalf==1) || (capintervalf==1))
        {
                    error_new =pidParams2.error2;
                    integral_new = integral_old + pidParams2.Ki2*(error_new + error_old)*Tsampling/2; // Area of the trapezoid

                    if((integral_new > pidParams2.outmax2) || (integral_new < minoutmax)) //-pidParams1.outmax1))// This is anti wind up protect
                    integral_new = integral_old;

                    controller_out = pidParams2.Kp2*error_new + pidParams2.Kd2*(error_new-error_old)/Tsampling + integral_new;
                    integral_old = integral_new;
                    error_old = error_new;
                    pidParams2.pidoutput2=controller_out;
                   

                        if(pidParams2.pidoutput2<=0)
                            pidParams2.pidoutput2=0;
                        else if(pidParams2.pidoutput2>pidParams2.outmax2)
                            pidParams2.pidoutput2=pidParams2.outmax2;

                        //disp1term=pidParams2.pidoutput2/50.0;//pidParams2.ReferenceSetpoint2;//500+pidParams2.error2;

                        disp4term=pidParams2.pidoutput2;
       					scaled_baseval2=(pidParams2.pidoutput2/scalefactor2);//1250.0);

                        if(scaled_baseval2>maxfmspeed)//baseamp)//200)
   						{
                            scaled_baseval2=maxfmspeed;//stepamp;//baseamp;//MAHESH200;
       					}
                        else if(scaled_baseval2<minfmspeed)//baseamp)//200)
   						{
       			    		scaled_baseval2=minfmspeed;//stepamp;//baseamp;//MAHESH200;
       					}
                        if(cyclestrtf==1 && closeloopf==1)
                        {
                            if(newsetwirespeed >= 35)
                            {
                                Update_PWM(scaled_baseval2);
                            }
                           else
                            {
                                Update_PWM(newsetwirespeed*MTR_FREQ_CONSTANT);
                            }
//                            Update_PWM(newsetwirespeed*MTR_FREQ_CONSTANT);
//                            pstowfstr.Hi_data1 =  scaled_baseval2 >> 8;
//                            pstowfstr.Lo_data1 =  scaled_baseval2;
                        }
                        else if(cyclestrtf==0)
                        {
                             Update_PWM(scaled_baseval2*0);
                        }
		}
                pidParams2.previous_error2 = pidParams2.error2;
}
