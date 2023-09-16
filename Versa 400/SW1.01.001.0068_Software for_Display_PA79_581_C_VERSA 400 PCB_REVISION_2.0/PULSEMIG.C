void PULSEWELD(void)
{
 
}

void no_frequency_update_pid()//15.02.2016
{
	pulsebase=pulsebase;
}



 

void load_pulse_parameter()
{
 	

}
//35307302085

void Load_Initial_Constant(unsigned int pulsesetws)
{
  
}	
 



 

void calculate_arcbasevtg_original(unsigned int psetvolt)
{
 
}

void calculate_arcbasevtg(unsigned int psetvolt)
{
 
}

void update_PMIG_syn_data(unsigned char synkey)
{
	if(synkey=='A')
	{
		if(pmat==pms)
		{
			pmat=p71t1;
			pdia=ponepttwo;
			pgas=parco2;
			lcdput(7,0,pmat71t1);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasarco2);
		}	
		else if(pmat==p71t1)
		{
			pmat=p180r;
			pdia=ponepttwo;
			pgas=parco2;
			lcdput(7,0,pmat180r);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasarco2);
		}	
		else if(pmat==p180r)
		{
			pmat=pss18;
			pdia=ponepttwo;
			pgas=paro2;
			lcdput(7,0,pmatss18);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasaro2);
		}	
		else if(pmat==pss18)
		{
			pmat=pss19;
			pdia=ponepttwo;
			pgas=paro2;
			lcdput(7,0,pmatss19);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasaro2);
		}
		else if(pmat==pss19)
		{
			pmat=palu4043;
			pdia=ponepttwo;
			pgas=par;
			lcdput(7,0,pmatalu4043);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasar);
		}
		else if(pmat==palu4043)
		{
			pmat=palu5356;
			pdia=ponepttwo;
			pgas=par;
			lcdput(7,0,pmatalu5356);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasar);
		}
		else if(pmat==palu5356)
		{
			pmat=palu99;
			pdia=ponepttwo;
			pgas=par;
			lcdput(7,0,pmatalu99);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasar);
		}
		else if(pmat==palu99)
		{
			pmat=pms;
			pdia=ponepttwo;
			pgas=parco2;
			lcdput(7,0,pmatms);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasarco2);
		}
		
		
		
	/*	if(pmat==pms)
		{
			pmat=pss;
			pdia=ponepttwo;
			pgas=parco2;
			lcdput(7,0,matss);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasarco2);
		}	
		else if(pmat==pss)
		{
			pmat=palu;
			pdia=ponepttwo;
			pgas=par;
			lcdput(7,0,matalu);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasar);
			
		}
		else if(pmat==palu)
		{
			pmat=pms;
			pdia=ponepttwo;
			pgas=parco2;
			lcdput(7,0,matms);
			lcdput(7,48,diaonepttwo);
			lcdput(7,90,gasarco2);
		}*/
	}
	else if(synkey=='B')
	{
			if((pmat==pms) || (pmat==pss18) ||(pmat==pss19)|| (pmat==palu4043)|| (pmat==palu5356))
			{
				if(pdia==pzeropteight)
				{
					pdia=poneptzero;
					lcdput(7,48,diaoneptzero);
				}	
				else if(pdia==poneptzero)
				{
					pdia=ponepttwo;
					lcdput(7,48,diaonepttwo);
				}
				
				else if(pdia==ponepttwo)
				{
					pdia=poneptsix;
					lcdput(7,48,diaoneptsix);
				}
				else if(pdia==poneptsix)
				{
					pdia=pzeropteight;
					lcdput(7,48,diazeropteight);
				}
			}
			
			
			
			
			
			/*if(pmat==pss)
			{
				if(pdia==ponepttwo)
				{
					pdia=pzeropteight;
					lcdput(7,48,diazeropteight);
				}
				else if(pdia==pzeropteight)
				{
					pdia=ponepttwo;
					lcdput(7,48,diaonepttwo);
				}
			}*/
			//pms,p71t1,p180r,pss18,pss19,palu4043,palu5356,palu99}pmat;
			if((pmat==palu99) || (pmat==p71t1)|| (pmat==p180r))
			{
				if(pdia==ponepttwo)
				{
					pdia=poneptsix;
					lcdput(7,48,diaoneptsix);
				}
				else if(pdia==poneptsix)
				{
					pdia=ponepttwo;
					lcdput(7,48,diaonepttwo);
				}	
			}	
					
			/*{
				pdia=ponepttwo;
				lcdput(7,48,diaonepttwo);
			}*/
	}
	else if(synkey=='C')
	{
		if(pmat==pms)
		{
			//if(pgas==parco2)
			{
				pgas=parco2;
				lcdput(7,90,gasarco2);
			}	
		}
		else if((pmat==pss18) || (pmat==pss19))
		{
			//if(pgas==parco2)
			{
				pgas=paro2;
				lcdput(7,90,gasaro2);
			}	
			//else if(pgas==paro2)
			//{
			//	pgas=parco2;
			//	lcdput(7,90,gasarco2);
			//}
		}	
		else if((pmat==palu4043) || (pmat==palu5356) || (pmat==palu99))
		{
			pgas=par;
			lcdput(7,90,gasar);
		}
	}
	//To limit the wire speed when program no change and to calculate voltage
	ppmigsetwirespeed=0;
	program_number=newpmmmatgas[pdia][pmat][pgas];
	
	max_Pws=max_Pwire_speed[program_number];
	
	if(para.pmigmode.setwspeed>max_Pws)
	{
		
		para.pmigmode.setwspeed=max_Pws;
	}	
}

void LCD_pulsemig_syn_data_write()
{
	{
			if(pmat==pms)
			lcdput(7,0,pmatms);
			else if(pmat==p71t1)
			lcdput(7,0,pmat71t1);
			else if(pmat==p180r)
			lcdput(7,0,pmat180r);
			else if(pmat==pss18)
			lcdput(7,0,pmatss18);
			else if(pmat==pss19)
			lcdput(7,0,pmatss19);
			else if(pmat==palu4043)
			lcdput(7,0,pmatalu4043);
			else if(pmat==palu5356)
			lcdput(7,0,pmatalu5356);
			else if(pmat==palu99)
			lcdput(7,0,pmatalu99);
			
	}
	{
			if(pdia==pzeropteight)
			lcdput(7,48,diazeropteight);
			else if(pdia==poneptzero)
			lcdput(7,48,diaoneptzero);
			else if(pdia==ponepttwo)
			lcdput(7,48,diaonepttwo);
			else if(pdia==poneptsix)
			lcdput(7,48,diaoneptsix);
	}
	{
			if(pgas==parco2)
			lcdput(7,90,gasarco2);
			else if(pgas==par)
			lcdput(7,90,gasar);	
			else if(pgas==paro2)
			lcdput(7,90,gasaro2);	
		}	
}	