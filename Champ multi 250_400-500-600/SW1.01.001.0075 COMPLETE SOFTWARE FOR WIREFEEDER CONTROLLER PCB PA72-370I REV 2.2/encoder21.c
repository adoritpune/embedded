inline unsigned char scanencoder()
{
	unsigned char result=0;
	if(read_eport() == 1)
	{
		if(firstpulse==0 && secondpulse==0)
		{
			if(new==0x02)// && firstpulse1==0)//03
			{
				firstpulse=1;
				secondpulse=0;
				plus222=1;
				result='*';
			}
			if(new==0x01)// && firstpulse1==0)//03
			{
				firstpulse=1;
				secondpulse=0;
                minus222=1;
				result='*';
			}
		}
		else if(firstpulse==1 && secondpulse==0)
		{        
			if(new==0x03) //&& firstpulse1==0)//03
			{
				firstpulse=1;
				secondpulse=1;
				result='*';
			}
		}
		else if(firstpulse==1 && secondpulse==1)
		{
			if(new==0x01 && plus222==1)// && firstpulse1==0)//03
			{
				firstpulse=0;
				plus222=0;
				result='+';
			}
			if(new==0x02 && minus222==1)// && firstpulse1==0)//03
			{
				firstpulse=0;
				minus222=0;
				result='-';
			}
			firstpulse=0;
     		secondpulse=0;
		}
		else
		{
			plus222=0;
			minus222=0;
			firstpulse=0;
     		secondpulse=0;
			result='*';
    	}
	}	
       /*if(new==0x03 && firstpulse==0)
		{
			firstpulse=1;
			result='*';
		}
		else if(firstpulse==1 && new==0x02)
		{
			result='-';//'+';
			firstpulse=0;
		}

		else if(firstpulse==1 && new==0x01)
		{
			result='+';//'-';
			firstpulse=0;
		}
		else
		{
			result='*';
			firstpulse=0;
		}
	}
	else 
	{
		result='*';
	}*/
		if(passprotect==0x0001 && setpasswordf==0)
		{result='*';}	
        return(result);
}

inline unsigned char read_eport()
{
	portvalue=0x0000;
	portvalue=ENCODER;
	portvalue=(portvalue & 0x0300);
	portvalue=(portvalue >> 8);
	new=portvalue;
	temp=new;
	if((temp ^ old) !=0)
	{
		old=new;
		return 1;
	}
	else
	{
		old=new;
		return 0;
	}
}


//****************scan remote only******************************
/*inline unsigned char scanremote()
{
	unsigned char result=0;
	if(read_fport() == 1)
	{
		if((newr==0x01 || newr==0x02) && firstpulser==0)
		{
			if(newr==0x01)
			{
				plusr=1;
			}
			else if(newr==0x02)
			{
				minusr=1;
			}
			firstpulser=1;
			secondpulser=0;	
			result='*';
		}
		else if(newr==0x03 && firstpulser==1 && secondpulser==0)
		{
			secondpulser=1;
			result='*';
		}
		else if(newr==0x02 && secondpulser==1 && plusr==1)
		{
			result='+';
			firstpulser=0;
			plusr=0;
			minusr=0;
			secondpulser=0;
		}
		else if(newr==0x01 && secondpulser==1 && minusr==1)
		{
			result='-';
			firstpulser=0;
			plusr=0;
			minusr=0;
			secondpulser=0;
		}
		else
		{
			result='*';
			firstpulser=0;
			secondpulser=0;
			plusr=0;
			minusr=0;
		}
	}*/
		//******************************
	/*	if(newr==0x03 && firstpulser==0)
		{
			firstpulser=1;
			result='*';
		}
		else if(firstpulser==1 && newr==0x02)
		{
			result='+';
			firstpulser=0;
		}

		else if(firstpulser==1 && newr==0x01)
		{
			result='-';
			firstpulser=0;
		}
		else
		{
			result='*';
			firstpulser=0;
		}
	}*/
	/*else 
	{
		result='*';
	}
		return(result);
}

inline unsigned char read_fport()
{
	portvalue=0x0000;
	portvalue=REMOTEENC;
	//SENDSERIAL(portvalue);
	portvalue=(portvalue & 0x0030);//0x0300);
	portvalue=(portvalue >> 4);//8);
	newr=portvalue;
	temp=newr;
	//trans(new);
	if((temp ^ oldr) !=0)
	{
		oldr=newr;
		//trans(newr);
		return 1;
	}
	else
	{
		oldr=newr;
		return 0;
	}
}*/

//**********************************************

inline unsigned char scanencoder1()
{
	unsigned char result=0;
	if(read_bport() == 1)
	{
		if(firstpulse1==0 && secondpulse1==0)
		{
			if(new1==0x02)// && firstpulse1==0)//03
			{
				firstpulse1=1;
				secondpulse1=0;
				plus111=1;
				result='*';
			}
			if(new1==0x01)// && firstpulse1==0)//03
			{
				firstpulse1=1;
				secondpulse1=0;
                minus111=1;
				result='*';
			}
		}
		else if(firstpulse1==1 && secondpulse1==0)
		{        
			if(new1==0x03) //&& firstpulse1==0)//03
			{
				firstpulse1=1;
				secondpulse1=1;
				result='*';
			}
		}
		else if(firstpulse1==1 && secondpulse1==1)
		{
			if(new1==0x01 && plus111==1)// && firstpulse1==0)//03
			{
				firstpulse1=0;
				plus111=0;
				result='+';
			}
			if(new1==0x02 && minus111==1)// && firstpulse1==0)//03
			{
				firstpulse1=0;
				minus111=0;
				result='-';
			}
			firstpulse1=0;
     		secondpulse1=0;
		}
		else
		{
			plus111=0;
			minus111=0;
			firstpulse1=0;
     		secondpulse1=0;
			result='*';
    	}
	}	
			/*
		if(new1==0x03 && firstpulse1==0)
		{
			firstpulse1=1;
			result='*';
		}
		else if(firstpulse1==1 && new1==0x02)
		{
			result='-';//'+';
	//		trans(result);
			firstpulse1=0;
		}

		else if(firstpulse1==1 && new1==0x01)
		{
			result='+';//'-';
		//	trans(result);
			firstpulse1=0;
		}
		else
		{
			result='*';
			firstpulse1=0;
		}
	}
	else 
	{
		result='*';
	}*/
		if(passprotect==0x0001 && setpasswordf==0)
		{result='*';}		
		return(result);
}

inline unsigned char read_bport()
{
	portvalue=0x0000;
	portvalue=ENCODER1;
	portvalue=(portvalue & 0x00C0);
	portvalue=(portvalue >> 6);
	new1=portvalue;
	temp=new1;
	if((temp ^ old1) !=0)
	{
		old1=new1;
		return 1;
	}
	else
	{
		old1=new1;
		return 0;
	}
}
//******************************
//********scan remote encoder 2 voltage and current reference**************************************

//****************scan remote only******************************
/*inline unsigned char scanremote1()
{
	unsigned char result=0;
	if(read_dport() == 1)
	{
		if((newr1==0x01 || newr1==0x02) && firstpulse11==0)
		{
			if(newr1==0x01)
			{
				plus1=1;
			}
			else if(newr1==0x02)
			{
				minus1=1;
			}
			firstpulse11=1;
			secondpulse11=0;	
			result='*';
		}
		else if(newr1==0x03 && firstpulse11==1 && secondpulse11==0)
		{
			secondpulse11=1;
			result='*';
		}
		else if(newr1==0x02 && secondpulse11==1 && plus1==1)
		{
			result='+';
			firstpulse11=0;
			plus1=0;
			minus1=0;
			secondpulse11=0;
		}
		else if(newr1==0x01 && secondpulse11==1 && minus1==1)
		{
			result='-';
			firstpulse11=0;
			plus1=0;
			minus1=0;
			secondpulse11=0;
		}
		else
		{
			result='*';
			firstpulse11=0;
			secondpulse11=0;
			plus1=0;
			minus1=0;
		}
	}
	else 
	{
		result='*';
	}
		return(result);
}

inline unsigned char read_dport()
{
	REMOTE1AIO=1;
	REMOTE1BIO=1;
	portvalue=0x0000;
	portvalue=ENCODER;//REMOTEENC1;
	//SENDSERIAL(portvalue);
	portvalue=(portvalue & 0x0C00);//0x0300);
	portvalue=(portvalue >> 10);//8);
	newr1=portvalue;
	//trans(newr1);
	if((newr1 ^ oldr1) !=0)
	{
		oldr1=newr1;
		//trans(newr1);
		return 1;
	}
	else
	{
		oldr1=newr1;
		return 0;
	}
}*/

//**********************************************

