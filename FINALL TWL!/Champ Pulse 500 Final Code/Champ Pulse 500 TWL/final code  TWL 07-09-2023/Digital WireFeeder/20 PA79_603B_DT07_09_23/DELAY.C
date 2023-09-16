#define FACTMS  7500
#define FACTUS  4

void Delay_ms(unsigned int ms)
{
	unsigned int i;
	for(;ms!=0;ms--)
	{
		for(i=FACTMS;i!=0;i--);
	}
}

void Delay_us(unsigned int us)
{
	unsigned int i;
	for(;us!=0;us--)
	{
		for(i=FACTUS;i!=0;i--);	
	}
}


