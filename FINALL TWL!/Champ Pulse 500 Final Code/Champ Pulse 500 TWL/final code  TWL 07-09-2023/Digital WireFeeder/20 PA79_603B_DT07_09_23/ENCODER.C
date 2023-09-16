void ENCODER_INIT()
{
	ENCODER1AIO=1;
	ENCODER1BIO=1;
	ENCODER2AIO=1;
	ENCODER2BIO=1;
}


unsigned char SCANENCODER1()
{
  	unsigned char result=0;
	if(enc1_port() == 1)
	{
		if(firstpulse1==0 && secondpulse1==0)
		{
			if(new1==0x02)    //10
			{
				firstpulse1=1;
				secondpulse1=0;
				plus111=1;
				result='$';
			}
			if(new1==0x01)     //01
			{
				firstpulse1=1;
				secondpulse1=0;
                minus111=1;
				result='$';
			}
		}
		else if(firstpulse1==1 && secondpulse1==0)
		{        
			if(new1==0x03)
			{
				firstpulse1=1;
				secondpulse1=1;
				result='$';
			}
		}
		else if(firstpulse1==1 && secondpulse1==1)
		{
			if(new1==0x01 && plus111==1)
			{
				firstpulse1=1;
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
			result='$';
        }
	}
 return(result);
}

unsigned char enc1_port()
{
	unsigned int portvalue=0x0000;
	portvalue=0x0000;
	portvalue=ENCODER1B;
	portvalue=portvalue<<1;
	portvalue=portvalue|ENCODER1A;
	portvalue=(portvalue & 0X0003);
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

unsigned char SCANENCODER2()
{
  	unsigned char result=0;
	if(enc2_port() == 1)
	{
		if(firstpulse2==0 && secondpulse2==0)
		{
			if(new2==0x02)    //10
			{
				firstpulse2=1;
				secondpulse2=0;
				plus222=1;
				result='$';
			}
			if(new2==0x01)     //01
			{
				firstpulse2=1;
				secondpulse2=0;
                minus222=1;
				result='$';
			}
		}
		else if(firstpulse2==1 && secondpulse2==0)
		{        
			if(new2==0x03) //&& firstpulse1==0)//03
			{
				firstpulse2=1;
				secondpulse2=1;
				result='$';
			}
		}
		else if(firstpulse2==1 && secondpulse2==1)
		{
			if(new2==0x01 && plus222==1)// && firstpulse1==0)//03
			{
				firstpulse2	=0;
				plus222		=0;
				result		='+';
			}
			if(new2==0x02 && minus222==1)// && firstpulse1==0)//03
			{
				firstpulse2	=0;
				minus222	=0;
				result		='-';
			}
			firstpulse2=0;
     			secondpulse2=0;
		}
		else
		{
			plus222=0;
			minus222=0;
			firstpulse2=0;
     		secondpulse2=0;
			result='$';
           }
	}
 return(result);
}

unsigned char enc2_port()
{
	unsigned int portvalue=0x0000;
	portvalue=0x0000;
	portvalue=ENCODER2B;
	portvalue=portvalue<<1;
	portvalue=portvalue|ENCODER2A;
	portvalue=(portvalue & 0X0003);
    new2=portvalue;
	temp=new2;
	if((temp ^ old2) !=0)
	{
		old2=new2;
		return 1;
	}
	else
	{
		old2=new2;
		return 0;
	}
}







