void encoder_init()
{
	ENCODERAIO=1;
	ENCODERBIO=1;
    ENCODERSWIO=1;
}

inline unsigned char scanencoder()
{
  unsigned char result=0;
	if(enc_port() == 1)
	{
		if(firstpulse==0 && secondpulse==0)
		{
			if(new==0x02)    //10
			{
				firstpulse=1;
				secondpulse=0;
				plus=1;
				result='$';
			}
			if(new==0x01)     //01
			{
				firstpulse=1;
				secondpulse=0;
                minus=1;
				result='$';
			}
		}
		else if(firstpulse==1 && secondpulse==0)
		{        
			if(new==0x03) //&& firstpulse1==0)//03
			{
				firstpulse=1;
				secondpulse=1;
				result='$';
			}
		}
		else if(firstpulse==1 && secondpulse==1)
		{
			if(new==0x01 && plus==1)// && firstpulse1==0)//03
			{
				firstpulse=0;
				plus=0;
				result='+';
			}
			if(new==0x02 && minus==1)// && firstpulse1==0)//03
			{
				firstpulse=0;
				minus=0;
				result='-';
			}
			firstpulse=0;
     		secondpulse=0;
		}
		else
		{
			plus=0;
			minus=0;
			firstpulse=0;
     		secondpulse=0;
			result='$';
        }
	}
 return(result);
}


inline unsigned char enc_port()
{
	portvalue=0X0000;
	portvalue=ENCODER;
	portvalue=(portvalue & 0X0003);
	new=portvalue;
	temp=new;
	if((temp ^ old) !=0)                //XOR ing
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
