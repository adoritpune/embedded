//void display_init()
//{
//	DECODEAIO=0;
//	DECODEBIO=0;
//	DECODECIO=0;
//	
//	LEDGP1IO =0;
//	LEDGP2IO =0;
//	LEDGP3IO =0;
//	LEDGP4IO =0;  
//
//	SEGAIO=0;
//	SEGBIO=0;
//	SEGCIO=0;
//	SEGDIO=0;
//	SEGEIO=0;
//	SEGFIO=0;
//	SEGGIO=0;
//	SEGDPIO=0;
//}


void latdata(unsigned char num)
{   
	if(disdigit <=6)
	{
		num=(num - 0x2F);
		for(ijk=0;ijk<8;ijk++)
		{
			arr[ijk]=lookup_table[num][ijk];
		}	
		if(setdp==1)
		arr[7]=1;
	}
	else
	{
		for(ijk=0;ijk<8;ijk++)
		{
			temp=num;
			temp=(temp >> ijk);
			temp= (temp & 0X01);
			if(temp==0)
			{
				temp=0;
			}
			else if(temp==1)
			{
				temp=1;
			}
			arr[ijk]=temp;
		}
	}
	SEGALAT=arr[0];
	SEGBLAT=arr[1];
	SEGCLAT=arr[2];
	SEGDLAT=arr[3];
	SEGELAT=arr[4];
	SEGFLAT=arr[5];
	SEGGLAT=arr[6];
	SEGDPLAT=arr[7];

}

void display_data()
{
	if(disdigit == 1)
	{	
		if(Typedp.digitdp1==1)
		setdp=1;
		else
		setdp=0;

		LEDGP4LAT =0;
		latdata(diswin1[0]);
		DECOD_ENLAT=1;
		DECODECLAT=0;
		DECODEBLAT=0;
        DECODEALAT=0;
		disdigit++;
	}
	
	else if(disdigit == 2)
	{	
		if(Typedp.digitdp2==1)
		setdp=1;
		else
		setdp=0;
		latdata(diswin1[1]);
		DECODECLAT=0;
		DECODEBLAT=0;
        DECODEALAT=1;
		disdigit++;
	}
	
	else if(disdigit == 3)
	{	
		if(Typedp.digitdp3==1)
		setdp=1;
		else
		setdp=0;
		latdata(diswin1[2]);
		DECODECLAT=0;
		DECODEBLAT=1;
        DECODEALAT=0;
		disdigit++;
	}
	
	else if(disdigit == 4)
	{	
		if(Typedp.digitdp4==1)
		setdp=1;
		else
		setdp=0;
		latdata(diswin2[0]);
		DECODECLAT=0;
		DECODEBLAT=1;
        DECODEALAT=1;
		disdigit++;
	}
	
	else if(disdigit == 5)
	{	
		if(Typedp.digitdp5==1)
		setdp=1;
		else
		setdp=0;
		latdata(diswin2[1]);
		DECODECLAT=1;
		DECODEBLAT=0;
        DECODEALAT=0;
		disdigit++;
	}
	
	else if(disdigit == 6)
	{	
		//if(dpinit_flag==1)
		//setdp=1;
		if(Typedp.digitdp6==1)
			setdp=1;
		else
			setdp=0;
		latdata(diswin2[2]);
		DECODECLAT=1;
		DECODEBLAT=0;
        DECODEALAT=1;
		disdigit++;
	}
   
   else if(disdigit == 7)
	{	
		latdata(TypeU.LEDGROUP[0]);//latdata(diswin2[2]);
		DECODECLAT=1;
		DECODEBLAT=1;
        DECODEALAT=0;
		disdigit++;
	}
  else if(disdigit == 8)
	{	
		//if(dpinit_flag==1)
		//setdp=1;
		latdata(TypeU.LEDGROUP[1]);//latdata(diswin3[0]);
		//setdp=0;
		DECODECLAT=1;
		DECODEBLAT=1;
        DECODEALAT=1;
		disdigit++;
	}
  else if(disdigit == 9)
	{	
		latdata(TypeU.LEDGROUP[2]);//latdata(diswin3[1]);
		DECOD_ENLAT=0;
		LEDGP3LAT=1;
		disdigit++;
	}
  else if(disdigit == 10)
	{	
		LEDGP3LAT=0;
		latdata(TypeU.LEDGROUP[3]);//latdata(diswin3[2]);
		LEDGP4LAT=1;
		disdigit=1;
    }
}

/*void inttobyte(unsigned int hex_data, unsigned char )
{




}*/

void lcd_disp_hex_dec(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
     disp_data_arr[2]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     disp_data_arr[1]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     disp_data_arr[0]= 0x30 + hex_data;
}

void disp_hex_dec_curr(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
     diswin1[2]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     diswin1[1]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     diswin1[0]= 0x30 + hex_data;
}
void disp_hex_dec_volt(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
     diswin2[2]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     diswin2[1]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     diswin2[0]= 0x30 + hex_data;
}
void disp_hex_dec_arclength2(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
{
     if(hex_data>= 40)//10)
     {
	     hex_data=hex_data-40;//10;
	     diswin2[2]= 0x30 + (hex_data % 10);
	     hex_data /= 10;
	     diswin2[1]= 0x30 + (hex_data % 10);
	     hex_data /= 10;
	     diswin2[0]= '['; //display Blank 
	 }
	 else
	 {
		 hex_data=40-hex_data;//10-hex_data;
	     diswin2[2]= 0x30 + (hex_data % 10);
	     hex_data /= 10;
	     diswin2[1]= 0x30 + (hex_data % 10);
	     hex_data /= 10;
	     //diswin2[0]= 0x30 + hex_data;
	     diswin2[0]= ']'; //display slash
	 }	 
}

//void disp_hex_dec_speed(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
//{
//     diswin3[2]= 0x30 + (hex_data % 10);
//     hex_data /= 10;
//     diswin3[1]= 0x30 + (hex_data % 10);
//     hex_data /= 10;
//     diswin3[0]= 0x30 + hex_data;
//}
//
//void disp_hex_dec_wirespeed(unsigned int hex_data)    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
//{
//     unsigned char temp[10];
//     unsigned int tempnum;
//	 tempnum=hex_data*10.0;
//     temp[2]= 0x30 + (tempnum % 10);
//     tempnum /= 10;
//     temp[1]= 0x30 + (tempnum % 10);
//     tempnum /= 10;
//     temp[0]= 0x30 + tempnum;
//	 ar6[10]=':';
//	 ar6[11]=temp[0];
//	 ar6[12]='.';
//     ar6[13]=temp[1];
//     ar6[14]=temp[2];
//}
//
 void display_start(unsigned char dispdata)
 {
	  diswin1[0]=dispdata;
	  diswin1[1]=dispdata;
	  diswin1[2]=dispdata;
	 
	  diswin2[0]=dispdata;
	  diswin2[1]=dispdata;
	  diswin2[2]=dispdata;
  }

//void Material_select_num_char(unsigned int hexdata)
//{
//     	if(material==1)
//     {	
//     		ar4[12]='M';
//     		ar4[13]='S';
//     		ar4[14]=' ';
//     		ar4[15]=' ';
//			mat=ms;
//  	}
//		else if(material==2)
// 		{	
//     		ar4[12]='S';
//     		ar4[13]='S';
//     		ar4[14]=' ';
//     		ar4[15]=' ';
//			mat=ss;
//  	}	
//}
//void Diameter_select_num_char(unsigned int hexdata)
//{
//	if(material==1)
// 	{
//		if(diameter==1)
//		{
//			ar5[10]=':';	
//			ar5[11]='2';
//     		      ar5[12]='.';
//			ar5[13]='0';
//     		      ar5[14]='0';
//			dia=twoptzero;
//		}
//		else if(diameter==2)
//		{
//			ar5[10]=':';	
//			ar5[11]='2';
//     			ar5[12]='.';
//			ar5[13]='4';
//     			ar5[14]='0';
//			dia=twoptfour;
//		}
//		else if(diameter==3)
//		{
//			ar5[10]=':';	
//			ar5[11]='3';
//     			ar5[12]='.';
//			ar5[13]='2';
//     			ar5[14]='0';	
//			dia=threepttwo;	
//		}
//		else if(diameter==4)
//		{
//			ar5[10]=':';	
//			ar5[11]='4';
//     			ar5[12]='.';
//			ar5[13]='0';
//     			ar5[14]='0';
//			dia=fourptzero;
//		}
//	}
//	else if(material==2)
// 	{
//		if(diameter==1)
//		{
//			ar5[10]=':';	
//			ar5[11]='2';
//     		      ar5[12]='.';
//			ar5[13]='0';
//     		      ar5[14]='0';
//			dia=twoptzero;
//		}
//		else if(diameter==2)
//		{
//			ar5[10]=':';	
//			ar5[11]='2';
//     			ar5[12]='.';
//			ar5[13]='4';
//     			ar5[14]='0';
//			dia=twoptfour;
//		}
//		else if(diameter==3)
//		{
//			ar5[10]=':';	
//			ar5[11]='3';
//     			ar5[12]='.';
//			ar5[13]='2';
//     			ar5[14]='0';	
//			dia=threepttwo;	
//		}
//		else if(diameter==4)
//		{
//			ar5[10]=':';	
//			ar5[11]='4';
//     			ar5[12]='.';
//			ar5[13]='0';
//     			ar5[14]='0';
//			dia=fourptzero;
//		}
//	}
//}
//
//void Model_select_num_char(unsigned int hexdata)
//{
//		if(Model==1)
//		{
//			ar12[10]=':';	
//			ar12[11]='A';
//     			ar12[12]=' ';
//			ar12[13]=' ';
//     			ar12[14]=' ';
//		}
//		else if(Model==2)
//		{
//			ar12[10]=':';	
//			ar12[11]='B';
//     			ar12[12]=' ';
//			ar12[13]=' ';
//     			ar12[14]=' ';
//		}
//		else if(Model==3)
//		{
//			ar12[10]=':';	
//			ar12[11]='C';
//     			ar12[12]=' ';
//			ar12[13]=' ';
//     			ar12[14]=' ';
//		}
//		else if(Model==4)
//		{
//			ar12[10]=':';	
//			ar12[11]='D';
//     			ar12[12]=' ';
//			ar12[13]=' ';
//     			ar12[14]=' ';
//		}
//}


