void display_init()
{
	DIGIT0IO=0;
	DIGIT1IO=0;
	DIGIT2IO=0;
	DIGIT3IO=0;
	DIGIT4IO=0;
	DIGIT5IO=0;
	DIGIT6IO=0;
	DIGIT7IO=0;
	DIGIT8IO=0;
	DIGIT9IO=0;
	DIGIT10IO=0;
	SEGAIO=0;
	SEGBIO=0;
	SEGCIO=0;
	SEGDIO=0;
	SEGEIO=0;
	SEGFIO=0;
	SEGGIO=0;
	SEGHIO=0;
}
const unsigned int lookup_table[44][8]=
							{ //{a,b,c,d,e,f,g,d}
								{0,0,0,0,0,0,0,0},		//null character forword slash '/'
								{1,1,1,1,1,1,0,0},		//1
								{0,1,1,0,0,0,0,0},		//0
								{1,1,0,1,1,0,1,0},		//2
								{1,1,1,1,0,0,1,0},		//3
								{0,1,1,0,0,1,1,0},		//4
								{1,0,1,1,0,1,1,0},		//5
								{1,0,1,1,1,1,1,0},		//6	
								{1,1,1,0,0,0,0,0},		//7
								{1,1,1,1,1,1,1,0},		//0
								{1,1,1,1,0,1,1,0},		//9
								{1,1,1,1,1,1,0,0},		//3A
								{0,1,1,0,0,0,0,0},		//3B
								{1,1,0,1,1,0,1,0},		//3C
								{1,1,1,1,0,0,1,0},		//3D
								{0,1,1,0,0,1,1,0},		//3E
								{1,0,1,1,0,1,1,0},		//3F
								{1,0,1,1,1,1,1,0},		//41
								{1,1,1,0,1,1,1,0},		//A
								{0,0,1,1,1,1,1,0},		//B
								{1,0,0,1,1,1,0,0},		//C
								{0,1,1,1,1,0,1,0},		//D
								{1,0,0,1,1,1,1,0},		//E
								{1,0,0,0,1,1,1,0},		//F
								{1,0,1,1,1,1,0,0},		//G
								{0,1,1,0,1,1,1,0},		//H
								{0,1,1,0,0,0,0,0},		//I
								{0,1,1,1,1,0,0,0},		//J
								{0,0,0,0,1,1,1,0},		//K
								{0,0,0,1,1,1,0,0},		//L
								{1,0,1,0,1,0,1,0},		//M
								{0,0,1,0,1,0,1,0},		//N
								{0,0,1,1,1,0,1,0},		//O	
								{1,1,0,0,1,1,1,0},		//P
								{1,1,1,0,0,1,1,0},		//Q
								{0,0,0,0,1,0,1,0},		//R
								{1,0,1,1,0,1,1,0},		//S
								{0,0,0,1,1,1,1,0},		//T	
								{0,1,1,1,1,1,0,0},		//U
								{0,0,1,1,1,0,0,0},		//V
								{0,1,0,1,0,1,1,0},		//W
								{0,0,1,0,0,0,0,0},		//X
								{0,1,1,1,0,1,1,0},		//Y
								{1,0,0,1,0,0,1,0},		//Z
							};

void display_data()
{
	if(disdigit == 1)
	{	
		DIGIT10LAT=0;
		DIGIT0LAT=0;
		if(disdigit==win1dpcnt)
		{
			setdp=1;
		}
		else
		{
			setdp=0;
		}
		latchdata(diswin1[0]);
		DIGIT10LAT=0;
		DIGIT0LAT=1;
		disdigit++;
	}
	else if(disdigit == 2)
	{
		DIGIT0LAT=0;
		DIGIT1LAT=0;
		if(disdigit==win1dpcnt)
		{
			setdp=1;
		}
		else
		{
			setdp=0;
		}
		latchdata(diswin1[1]);
		DIGIT0LAT=0;
		DIGIT1LAT=1;
		disdigit++;
	}
	else if(disdigit == 3)
	{
		DIGIT1LAT=0;
		DIGIT2LAT=0;
		setdp=0;
		latchdata(diswin1[2]);
		DIGIT1LAT=0;
		DIGIT2LAT=1;
		disdigit++;
	}
	else if(disdigit == 4)
	{
		DIGIT2LAT=0;
		DIGIT3LAT=0;
		if(disdigit==(win2dpcnt+3))
		{
			setdp=1;
		}
		else
		{
			setdp=0;
		}
		latchdata(diswin2[0]);
		DIGIT2LAT=0;
		DIGIT3LAT=1;
		disdigit++;
	}
	else if(disdigit == 5)
	{
		DIGIT3LAT=0;
		DIGIT4LAT=0;
		if(disdigit==(win2dpcnt + 3))
		{
			setdp=1;
		}
		else
		{
			setdp=0;
		}
		latchdata(diswin2[1]);
		DIGIT3LAT=0;
		DIGIT4LAT=1;
		disdigit++;
	}
	else if(disdigit == 6)
	{
		DIGIT4LAT=0;
		DIGIT5LAT=0;
		setdp=0;
		latchdata(diswin2[2]);
		DIGIT4LAT=0;
		DIGIT5LAT=1;
		disdigit++;
	}
	else if(disdigit == 7)
	{
		DIGIT5LAT=0;
		DIGIT6LAT=0;
		latchdata(TypeU.LEDGROUP[0]);
		DIGIT5LAT=0;
		DIGIT6LAT=1;
		disdigit++;
	}
	else if(disdigit == 8)
	{
		DIGIT6LAT=0;
		DIGIT7LAT=0;
		latchdata(TypeU.LEDGROUP[1]);
		DIGIT6LAT=0;
		DIGIT7LAT=1;
		disdigit++;
	}
	else if(disdigit == 9)
	{
		DIGIT7LAT=0;
		DIGIT8LAT=0;
		latchdata(TypeU.LEDGROUP[2]);
		DIGIT7LAT=0;
		DIGIT8LAT=1;
		disdigit++;
	}
	else if(disdigit == 10)
	{
		DIGIT8LAT=0;
		DIGIT9LAT=0;
		latchdata(TypeU.LEDGROUP[3]);
		DIGIT8LAT=0;
		DIGIT9LAT=1;
		disdigit++;
	}
	else if(disdigit==11)
	{
		DIGIT9LAT=0;
		DIGIT10LAT=0;
		latchdata(TypeU.LEDGROUP[4]);
		DIGIT9LAT=0;
		DIGIT10LAT=1;
		disdigit++;
		disdigit=1;
	}
}
void latchdata(unsigned char num)
{
	unsigned char temp, i;
	temp=num;
	if(disdigit < 7)
	{
		num=(num - 0x2F);//0x30);
		for(i=0;i<8;i++)
		{
			arr[i]=lookup_table[num][i];
		}	
		if(setdp==1)
		{
			arr[7]=1;//0;
		}
	}
	else
	{
		for(i=0;i<8;i++)
		{
			temp=num;
			temp=(temp >> i);
			temp= (temp & 0X01);
			if(temp==0)
			{
				temp=1;
			}
			else if(temp==1)
			{
				temp=0;
			}
			arr[i]=temp;
		}
		
	}
	SEGALAT=arr[0];
	SEGBLAT=arr[1];
	SEGCLAT=arr[2];
	SEGDLAT=arr[3];
	SEGELAT=arr[4];
	SEGFLAT=arr[5];
	SEGGLAT=arr[6];
	SEGHLAT=arr[7];
}

