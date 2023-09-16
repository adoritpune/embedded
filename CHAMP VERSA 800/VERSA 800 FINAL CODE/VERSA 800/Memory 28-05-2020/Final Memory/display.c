void display_int()
{
	//CATHODE1IO=0;
	//CATHODE2IO=0;
	//CATHODE3IO=0;
	//CATHODE4IO=0;
	//CATHODE5IO=0;
	//CATHODE6IO=0;
	//CATHODE7IO=0;
	//CATHODE8IO=0;
	//TRIPLEDIO=0;
	//MMALEDIO=0;
	//SAWLEDIO=0;
	MIGONIO=1;                  //input pin to read whether wirefeerder is connected or not
	CURR_LEDIO=0;               //output pin for an indication LED
	WS_SPEED_LEDIO=0;           //output pin for an indication LED
	
	//DECODER SECTION OUTPUT CONFIGURED
	DECODEAIO=0;      //LSB
	DECODEBIO =0;
	DECODECIO =0;     //MSB
	DECODEENIO=0;     //DECODER ENABLE PIN
	
	SEGAIO=0;
	SEGBIO=0;
	SEGCIO=0;
	SEGDIO=0;
	SEGEIO=0;
	SEGFIO=0;
	SEGGIO=0;
	SEGDPIO=0;
	
    OCV_FLAGIO=0;
}

const unsigned int lookup_table[46][8]=
							{ //{a,b,c,d,e,f,g,d}
								{0,0,0,0,0,0,0,0},		//null character forword slash '/'
								{1,1,1,1,1,1,0,0},		//0
								{0,1,1,0,0,0,0,0},		//1
								{1,1,0,1,1,0,1,0},		//2
								{1,1,1,1,0,0,1,0},		//3
								{0,1,1,0,0,1,1,0},		//4
								{1,0,1,1,0,1,1,0},		//5
								{1,0,1,1,1,1,1,0},		//6	
								{1,1,1,0,0,0,0,0},		//7
								{1,1,1,1,1,1,1,0},		//8
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
								{0,0,1,0,0,0,0,0},		//I
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
								{0,1,1,1,1,1,0,0},		//V
								{0,1,0,1,0,1,1,0},		//W
								{0,0,1,0,0,0,0,0},		//X
								{0,1,1,1,0,1,1,0},		//Y
								{1,0,0,1,0,0,1,0},		//Z
                                			{0,0,0,0,0,0,1,0},		//-
                                			{1,1,1,1,1,1,1,1},
							};

void display_data()
{
	if(disdigit == 1)
	{	
		if(Typedp.digitdp1==1)
			setdp=1;
		else
			setdp=0;
		//CATHODE8LAT=0;
		latchdata(CURR[0]);
		//CATHODE1LAT=1;
		disdigit++;
	}
	else if(disdigit == 2)
	{	
		if(Typedp.digitdp2==1)
			setdp=1;
		else
			setdp=0;
		//CATHODE1LAT=0;
		latchdata(CURR[1]);
		//CATHODE2LAT=1;
		disdigit++;
	}
	
	else if(disdigit == 3)
	{	
		if(Typedp.digitdp3==1)
			setdp=1;
		else
			setdp=0;
		//CATHODE2LAT=0;
		latchdata(CURR[2]);
		//CATHODE3LAT=1;
		disdigit++;
	}
	
	else if(disdigit == 4)
	{	
		if(Typedp.digitdp4==1)
			setdp=1;
		else
			setdp=0;
		//CATHODE3LAT=0;
		//if(eswitch==1 && process_flag==1)
		//setdp=1;
		latchdata(CURR[3]);
		//CATHODE4LAT=1;
		disdigit++;
	}
	
	else if(disdigit == 5)
	{	
		if(Typedp.digitdp5==1)
			setdp=1;
		else
			setdp=0;
		//CATHODE4LAT=0;
		latchdata(VOLT[0]);
		//CATHODE5LAT=1;
		disdigit++;
	}
	
	else if(disdigit == 6)
	{	
		if(Typedp.digitdp6==1)
			setdp=1;
		else
			setdp=0;
		//CATHODE5LAT=0;
		latchdata(VOLT[1]);
		//CATHODE6LAT=1; 
		disdigit++;
	}
	
	else if(disdigit == 7)
	{	
		if(Typedp.digitdp7==1)
			setdp=1;
		else
			setdp=0;
		//CATHODE6LAT=0;
		latchdata(VOLT[2]);
		//CATHODE7LAT=1;
		disdigit++;
	}
	else if(disdigit == 8)
	{	
		if(Typedp.digitdp8==1)
			setdp=1;
		else
			setdp=0;
		//CATHODE7LAT=0;
		latchdata(VOLT[3]);
		//CATHODE8LAT=1;
		disdigit=1;
	}  
}


void refresh_display()
{
	
	if(disdigit == 1)
	{
		DECODEENLAT=0;
		if(Typedp.digitdp1==1)
			setdp=1;
		else
			setdp=0;
	    //COM1 SELECTED		
	    DECODEALAT=0;
	    DECODEBLAT=0;
	    DECODECLAT=0;
	    
	    latchdata(CURR[0]);
		
		//disdigit++;
	
	}
	else if(disdigit == 2)
	{
	    if(Typedp.digitdp2==1)
			setdp=1;
		else
			setdp=0;
	    //COM2 SELECTED		
	    DECODEALAT=1;     //lsb
	    DECODEBLAT=0;
	    DECODECLAT=0;     //msb
	    
	    latchdata(CURR[1]);
		
		//disdigit++;
	
	}
	else if(disdigit == 3)
	{
	    if(Typedp.digitdp3==1)
			setdp=1;
		else
			setdp=0;
	    //COM3 SELECTED		
	    DECODEALAT=0;
	    DECODEBLAT=1;
	    DECODECLAT=0;
	    
	    latchdata(CURR[2]);
		
		//disdigit++;
	
	}
	else if(disdigit == 4)
	{
	    if(Typedp.digitdp4==1)
			setdp=1;
		else
			setdp=0;
	    //COM4 SELECTED		
	    DECODEALAT=1;
	    DECODEBLAT=1;
	    DECODECLAT=0;
	    
	    latchdata(CURR[3]);
		
		//disdigit++;
	
	}
	else if(disdigit == 5)
	{
	    if(Typedp.digitdp5==1)
			setdp=1;
		else
			setdp=0;
	    //COM5 SELECTED		
	    DECODEALAT=0;
	    DECODEBLAT=0;
	    DECODECLAT=1;
	    
	    latchdata(CURR[4]);
		
		//disdigit++;
	
	}
	else if(disdigit == 6)
	{
	    if(Typedp.digitdp6==1)
			setdp=1;
		else
			setdp=0;
	    //COM6 SELECTED		
	    DECODEALAT=1;
	    DECODEBLAT=0;
	    DECODECLAT=1;
	    
	    latchdata(CURR[5]);
		
		//disdigit++;
	
	}
	else if(disdigit == 7)
	{
	    if(Typedp.digitdp7==1)
			setdp=1;
		else
			setdp=0;
	    //COM7 SELECTED		
	    DECODEALAT=0;
	    DECODEBLAT=1;
	    DECODECLAT=1;
	    
	    latchdata(CURR[6]);
		
		//disdigit++;
	
	}
	else if(disdigit == 8)
	{
	    if(Typedp.digitdp8==1)
			setdp=1;
		else
			setdp=0;
	    //COM8 SELECTED		
	    DECODEALAT=1;
	    DECODEBLAT=1;
	    DECODECLAT=1;
	    
	    latchdata(CURR[7]);
		
		//disdigit++;
	
	}
	else if(disdigit == 9 && (trip_flag==1 || imtrip_flag==1))  //only for checking communication trans_chk_f==1//(trip_flag==1 || imtrip_flag==1))  //trip led
	{
		DECODEENLAT=1;
	    
	    //COM9 SELECTED		
	    DECODEALAT=0;
	    DECODEBLAT=0;
	    DECODECLAT=0;
	    
	    //latchdata(CURR[7]);
		
		//disdigit++;
	
	}
	else if(disdigit == 10 && mma_flag==1)   //mma led
	{
		DECODEENLAT=1;
	    
	    //COM10 SELECTED		
	    DECODEALAT=1;
	    DECODEBLAT=0;
	    DECODECLAT=0;
	    
	    //latchdata(CURR[7]);
		
		//disdigit++;
	
	}
	else if(disdigit == 11 && mig_flag==1)    //mig led
	{
		DECODEENLAT=1;
	    
	    //COM11 SELECTED		
	    DECODEALAT=0;          //lsb
	    DECODEBLAT=1;
	    DECODECLAT=0;          //msb
	    
	    //latchdata(CURR[7]);
		
		//disdigit++;
	
	}
	else if(disdigit == 12 && remote_flag==1)  //remote led
	{
		DECODEENLAT=1;
	    
	    //COM12 SELECTED		
	    DECODEALAT=1;        //lsb
	    DECODEBLAT=1;
	    DECODECLAT=0;        //msb
	    
	    //latchdata(CURR[7]);
		
		//disdigit++;
	
	}
	else if(disdigit == 13)  //led not used
	{
		DECODEENLAT=1;
	    
	    //COM13 SELECTED		
	    DECODEALAT=1;        //lsb
	    DECODEBLAT=0;
	    DECODECLAT=1;        //msb
	    
	    //latchdata(CURR[7]);
		
		//disdigit++;
	
	}
	
	disdigit++;
	if(disdigit>=14)
	{
	
	    disdigit=1;
	
	}
	
	

}
void latchdata(unsigned char num)
{   
	num=(num - 0x2F);
	for(abc=0;abc<8;abc++)
	{
		arr[abc]=lookup_table[num][abc];
	}	
	if(setdp==1)  // && mma_init==1 && trip_flag==0 && comm_flag==0 && cali_flag==0)||poweron_flag==1) //DECIMAL POINT CONDITIONS 
	arr[7]=1;

	SEGALAT=arr[0];
	SEGBLAT=arr[1];
	SEGCLAT=arr[2];
	SEGDLAT=arr[3];
	SEGELAT=arr[4];
	SEGFLAT=arr[5];
	SEGGLAT=arr[6];
	SEGDPLAT=arr[7];
	//TypeDP.DPGROUP[0]=arr[7];
}

void disp_hex_dec_curr(unsigned int hex_data)    //CONVERsION FROM HEX TO DEC VALUE FOR DISPLAY
{
     CURR[3]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     CURR[2]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     CURR[1]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     CURR[0]= 0x30 + hex_data;
}

void disp_hex_dec_volt(unsigned int hex_data)    //CONVERSION FROM HEX TO DEC VALUE FOR DISPLAY
{
     VOLT[3]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     VOLT[2]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     VOLT[1]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     VOLT[0]= 0x30 + hex_data;
}



