#include "p30f6014A.h"

void open_file(unsigned char*);
void open_file_data_time(unsigned int);
void close_file(unsigned char*);
void write_into_file(unsigned char*,unsigned char);
void delete_file();
void SCS_Selection();
void IDD();
void make_sub_directory();
void change_directory();
void Read_Whole_File();
void DIR(unsigned char*);
void SEK();
void Insert_Header_of_File();
void Rename_File(unsigned char*,unsigned char*);




void delay1(unsigned int icnt)
{
	idel = 0;
	while(idel < icnt)
	{
		
	}
}


void open_file(unsigned char *string)
{
	unsigned int temp;
	
	TRANS1(0x09);
	TRANS1(0x20);
	
	while(*string != '\0')
	{
		TRANS1(*string);
		string++;
	}
	
	
	TRANS1(0x0D);
}

void write_into_file(unsigned char *cString,unsigned char iNoOfByte)
{
	unsigned int i;
	unsigned char iNo = 0,*cTemp;
	cTemp = cString;
	
	/*while(*cTemp != "\0")
	{
		iStringcnt++;
		cTemp++;
	}*/
	
	
	TRANS1(0x08);
	TRANS1(0x20);
	TRANS1(0x00);
	TRANS1(0x00);
	TRANS1(0x00);
	TRANS1(iNoOfByte);
	TRANS1(0x0D);
	
	for(i=0;i<iNoOfByte;i++)
	{
		TRANS1(*cString);
		cString++;
	}	
}

void enter()
{
	TRANS1(0x08);
	TRANS1(0x20);
	TRANS1(0x00);
	TRANS1(0x00);
	TRANS1(0x00);
	TRANS1(0x01);
	TRANS1(0x0D);
	
	TRANS1(13);
		
}

void close_file(unsigned char *string)
{
	TRANS1(0x0A);
	TRANS1(0x20);	
	
	while(*string != '\0')
	{
		TRANS1(*string);
		string++;
	}	
	
	TRANS1(0x0D);	
}

void SCS_Selection()
{
	TRANS1(0x10);
	TRANS1(0x0D);
}

void IDD()
{
	TRANS1(0x0F);
	TRANS1(0x0D);
}

void make_sub_directory()
{
	TRANS1(0x06);
	TRANS1(0x20);
	
	TRANS1('X');
	TRANS1('Y');
	TRANS1('Z');
	
	TRANS1(0x0D);
	
}

void change_directory()
{
	TRANS1(0x02);
	TRANS1(0x20);
	
	TRANS1('X');
	TRANS1('Y');
	TRANS1('Z');
	
	TRANS1(0x0D);
		
}

/*void Read_Whole_File()
{
	TRANS1(0x04);
	TRANS1(0x20);
	
	TRANS1(0x02);
	TRANS1(0x02);
	
	TRANS1(0x0D);					
}*/

void DIR(unsigned char *string)
{
	TRANS1(0x01);
	TRANS1(0x20);
	
	
	while(*string != '\0')
	{
		TRANS1(*string);
		string++;
	}	
	/*TRANS1('A');
	TRANS1('B');
	TRANS1('C');
	TRANS1('D');
	TRANS1('E');
	TRANS1('F');
	TRANS1('G');
	TRANS1('k');	
	TRANS1('.');
	TRANS1('c');
	TRANS1('s');
	TRANS1('v');*/
	
	TRANS1(0x0D);
	
	cReadFileSizefg = 1;
}

void SEK()
{
	TRANS1(0x28);
	TRANS1(0x20);
	
	TRANS1(0x00);
	TRANS1(0x00);
	TRANS1(0x00);
	TRANS1(0x00 + iSekPtr);
	
	TRANS1(0x0D );
	
	iSekPtr++;	
}

void Insert_Header_of_File()
{
	write_into_file("Program No:",11);
	delay1(100);
	write_into_file(",",1);
	delay1(100);
	lcd_disp_hex_dec(iProgramLoadLoc);
	write_into_file(disp_data_arr,3);			
	delay1(100);
	enter();	
	delay1(100);	
	write_into_file("TIME:",5);
	delay1(100);
	write_into_file(",",1);
	delay1(100);
	write_into_file("CURRENT:",8);			
	delay1(100);
	write_into_file(",",1);
	delay1(100);
	write_into_file("VOLTAGE:",8);
	delay1(100);
	write_into_file(",",1);
	delay1(100);
	write_into_file("WELD JOINT:",11);
	delay1(100);
	write_into_file(",",1);
	delay1(100);
	write_into_file("ARC MISSING",11);
	delay1(100);
	enter();
	
}

void RealTime()
{
	if(iHrMinSeccnt >= 1000)
	{
		if(cHrMinSec[7] <= 8)
		{
			cHrMinSec[7]++;	
		}
		else
		{
			cHrMinSec[7] = 0;
			if(cHrMinSec[6] <= 4)
			{
				cHrMinSec[6]++;
			}
			else
			{
				cHrMinSec[6] = 0;
				if(cHrMinSec[4] <= 8)
				{
					cHrMinSec[4]++;
				}
				else
				{
					cHrMinSec[4] = 0;
					if(cHrMinSec[3] <= 4)
					{
						cHrMinSec[3]++;	
					}
					else
					{
						cHrMinSec[3] = 0;
						if(cHrMinSec[1] <= 3)
						{
							cHrMinSec[1]++;	
						}
						else
						{
							cHrMinSec[1] = 0;
							if(cHrMinSec[0] <= 1)
							{
								cHrMinSec[4]++;
							}
							else
							{
								cHrMinSec[0] = 0;
								cHrMinSec[1] = 0;
								cHrMinSec[3] = 0;
								cHrMinSec[4] = 0;
								cHrMinSec[6] = 0;
								cHrMinSec[7] = 0;																																									
							}		
						}			
					}
								
				}			
			}			
		}			
		
		iHrMinSeccnt = 0;
	}		
}	

void logwelddata()
{

	lcd_disp_hex_dec(iseconds);
		
	cWeldDataLOGarray[7] = cHrMinSec[7] = disp_data_arr[2];
	cWeldDataLOGarray[6] = cHrMinSec[6] = disp_data_arr[1];
	cWeldDataLOGarray[5] = cHrMinSec[5] = ':';
	
	lcd_disp_hex_dec(iMinutes);
	
	cWeldDataLOGarray[4] = cHrMinSec[4] = disp_data_arr[2];
	cWeldDataLOGarray[3] = cHrMinSec[3] = disp_data_arr[1];
	cWeldDataLOGarray[2] = cHrMinSec[2] = ':';

	lcd_disp_hex_dec(iHours);
	
	cWeldDataLOGarray[1] = cHrMinSec[1] = disp_data_arr[2];
	cWeldDataLOGarray[0] = cHrMinSec[0] = disp_data_arr[1]; 	
	
	//write_into_file(cHrMinSec,8);//"12:34:56"
	//delay1(50);
	cWeldDataLOGarray[8] = ',';
	//write_into_file(",",1);
	//delay1(50);
		
	//CURRENT = 123;//para.pmigmode.setcurrent;
	lcd_disp_hex_dec(CURRENT);
	cWeldDataLOGarray[9] = disp_data_arr[0];
	cWeldDataLOGarray[10] = disp_data_arr[1];
	cWeldDataLOGarray[11] = disp_data_arr[2];
	//write_into_file(disp_data_arr,3);
	//delay1(50);
	cWeldDataLOGarray[12] = ',';
	//write_into_file(",",1);	
	//delay1(50);

	//CURRENT = 321;//para.pmigmode.setcurrent;
	lcd_disp_hex_dec(VOLTAGE);
	cWeldDataLOGarray[13] = disp_data_arr[0];
	cWeldDataLOGarray[14] = disp_data_arr[1];
	cWeldDataLOGarray[15] = '.';	
	cWeldDataLOGarray[16] = disp_data_arr[2];	
	//write_into_file(disp_data_arr,3);
	//delay1(50);
	cWeldDataLOGarray[17] = ',';
	//write_into_file(",",1);
	//delay1(50);
	
	
	lcd_disp_hex_dec(iWeldJointCntr);
	cWeldDataLOGarray[18] = disp_data_arr[0];
	cWeldDataLOGarray[19] = disp_data_arr[1];
	cWeldDataLOGarray[20] = disp_data_arr[2];		
	//write_into_file(disp_data_arr,3);					//Weld Joint Count......
	//delay1(50);
	cWeldDataLOGarray[21] = ',';
	//write_into_file(",",1);
	//delay1(50);
		
	
	if((CURRENT < 20) && (iArcMissCnt <= 0))
	{
		iArcMissingcnt++;
	}		
	lcd_disp_hex_dec(iArcMissingcnt);
	cWeldDataLOGarray[22] = disp_data_arr[0];
	cWeldDataLOGarray[23] = disp_data_arr[1];
	cWeldDataLOGarray[24] = disp_data_arr[2];	
//	write_into_file(disp_data_arr,3);					//Arc Missing......
	//delay1(50);
	cWeldDataLOGarray[25] = ',';
	write_into_file(cWeldDataLOGarray,26);	
	//write_into_file(",",1);	
	delay1(5);
	enter();	


}	

void closefilewithAOT()
{
	char ctemp[3];
	
	enter();
	enter();	
	write_into_file(",",1);
	write_into_file(",",1);
	
	write_into_file("ARC ON TIME",11);
	
		
	write_into_file(",",1);
	
	lcd_disp_hex_dec(iHrStart);	
	write_into_file(disp_data_arr,3);	
	write_into_file(":",1);	
	lcd_disp_hex_dec(iMinStart);
	ctemp[1] = disp_data_arr[2];
	ctemp[0] = disp_data_arr[1];
	write_into_file(ctemp,2);
		
	
	enter();	
	delay1(100);			
	close_file(cfilename1);//"1245.CSV");  //"12345678.CSV");//			
}	

void Rename_File(unsigned char *cSource,unsigned char *cTarget)
{
	TRANS1(0x0C);
	TRANS1(0x20);

	while(*cSource != '\0')
	{
		TRANS1(*cSource);
		cSource++;
	}	
	
	TRANS1(0x20);
	
	while(*cTarget != '\0')
	{
		TRANS1(*cTarget);
		cTarget++;
	}
	
	TRANS1(0x0D);
			
}

void Read_whole_file(unsigned char *string)
{
	TRANS1(0x04);
	TRANS1(0x20);
	
	while(*string != '\0')
	{
		TRANS1(*string);
		string++;
	}	
	
	TRANS1(0x0D);
	
	cReadWholeFilefg = 1;
	iabc = 0;
	//DIR("555.CSV");	
}

/*void Seperate_Out_Parameters()
{
	int i = 0,itemp,iws=0,iEntercnt = 0;
	char ctemp;
	
	for(i=0;i<468;)
	{
		if(cReadWholeFile[i] == 0x0D)
		{
			iEntercnt++;
			iws = 0;
			i++;											
		}
		
		if(cReadWholeFile[i] == 0x0A)
		{
			i++;
		}
		else
		{
			if(cReadWholeFile[i] == ',')
			{
				i++;
				iws++;
			}
			else
			{
				if(iEntercnt <= 4)
				{
					iUSBData[iEntercnt][iws] = (cReadWholeFile[i] - 0x30)*100 + (cReadWholeFile[i+1] - 0x30)*10 +
															 (cReadWholeFile[i+2] - 0x30);
					i = i+3;
				}
				else
				{
					cUSBdata[iws] = cReadWholeFile[i];
					i++;
				}	 						
			}	
		}
	}
}*/

void Seperate_Out_Parameters1()
{
	int i = 0,itemp,iws=0,iEntercnt = 0,temp1,ii;
	char ctemp,cXYZ;
	
	for(i=0;i<iabc;)
	{
		if(cReadWholeFile[i] == 0x0D)
		{
			iEntercnt++;
			iws = 0;
			i++;											
		}
		
		if((cReadWholeFile[i] == 0x0A) || (cReadWholeFile[i] == 0x22) || (cReadWholeFile[i] == 0x20))
		{
			i++;
		}
		else
		{
			if(cReadWholeFile[i] == ',')
			{
				i++;
				iws++;
			}
			else
			{
				if(iEntercnt <= 4)
				{
					iUSBData[iEntercnt][iws] = (cReadWholeFile[i] - 0x30)*100 + (cReadWholeFile[i+1] - 0x30)*10 +
															 (cReadWholeFile[i+2] - 0x30);
					i = i+3;
				}
				else
				{
					cUSBdata[iws] = cReadWholeFile[i];
					i++;
				}	 						
			}	
		}
	}
	cUSBdata[0] = cReadWholeFile[556];//456];
		
	
		
	/*ctemp = (cUSBdata[8] - 0x30);
	ctempo1 = ctemp;
	ctemp = (ctemp << 4);
	ctemp = (ctemp & 0xf0);
	cUSBGasDia = (cUSBdata[9] - 0x30);
	ctempo2 = cUSBGasDia;
	cUSBGasDia = (ctemp || cUSBGasDia);*/
	
	update_mat_dia_gas(cUSBdata[9]-0x30,cUSBdata[8]-0x30);
	
	
	temp1 = cUSBdata[10] - 0x30;
	iPulseFreqFact = temp1*10;
	iPulseFreqFact +=  (cUSBdata[11] - 0x30);
	
	temp1 = cUSBdata[12] - 0x30;
	iPulsetmfactor = temp1*10;
	iPulsetmfactor +=  (cUSBdata[13] - 0x30);
	
	temp1 = cUSBdata[14] - 0x30;
	iPulsecurfactor = temp1*10;
	iPulsecurfactor +=  (cUSBdata[15] - 0x30);	
	
	temp1 = cUSBdata[16] - 0x30;
	iUSBFileNo = temp1*100;
	temp1 = (cUSBdata[17] - 0x30);			
	iUSBFileNo += temp1*10;	
	iUSBFileNo += (cUSBdata[18] - 0x30);	

	temp1 = cUSBdata[19] - 0x30;
	iUSBsfConst = temp1*100;
	temp1 = (cUSBdata[20] - 0x30);			
	iUSBsfConst += temp1*10;	
	iUSBsfConst += (cUSBdata[21] - 0x30);


	for(ii=0;ii<1000;ii++)
	{
		cReadWholeFile[ii] == 0;	
	}
	//iabc = 0;	
}

void Update_File_Name(unsigned int data)
{
	cFileName[2] = 0x30 + data%10;
	data = data/10;
	cFileName[1] = 0x30 + data%10;
	data = data/10;
	cFileName[0] = 0x30 + data%10;
	
	cFullFileName[11] 	= 'T';
	cFullFileName[10] 	= 'X';
	cFullFileName[9]  	= 'T';
	cFullFileName[8]  	= '.';
	cFullFileName[7]  	= cFileName[2];
	cFullFileName[6]  	= cFileName[1];
	cFullFileName[5]  	= cFileName[0];
	if(weldmode == 'P')
		cFullFileName[4]= 'P';
	else if(weldmode == 'G')
		cFullFileName[4]= 'G';
	cFullFileName[3]  	= 'R';
	cFullFileName[2] 	= 'O';
	cFullFileName[1]  	= 'D';
	cFullFileName[0]  	= 'A';		

	//cUSBGasDia = ((cUSBdata[8] << 4) || cUSBdata[9]);

}


void file_name_creation()
{
	lcd_disp_hex_dec4digit(iCreatFilecntr);

	cfilename1[11] = 'V';
	cfilename1[10] = 'S';
	cfilename1[9]  = 'C';
	cfilename1[8]  = '.';
	cfilename1[7]  = disp_data_arr[3];
	cfilename1[6]  = disp_data_arr[2];
	cfilename1[5]  = disp_data_arr[1];
	cfilename1[4]  = disp_data_arr[0];
	cfilename1[3]  = cSerialNo[3]+0x30;//'1';//
	cfilename1[2]  = cSerialNo[2]+0x30;//'2';//
	cfilename1[1]  = cSerialNo[1]+0x30;//'3';//
	cfilename1[0]  = cSerialNo[0]+0x30;//'4';//
		
}	


void update_mat_dia_gas(unsigned int temp1,unsigned int temp2)
{
	int i;
	/*for(i=0;i<8;i++)
	{
		cMatarray[i] = cMatTxt[iMatChk][i];
	}*/
	
	switch(temp1)
	{	
		case 0:
			switch(temp2)
			{
				case 0:
					cUSBGasDia = 0x00;
					break;
				case 1:
					cUSBGasDia = 0x10;								//0.8
					break;
				case 2:
					cUSBGasDia = 0x20;
					break;
				case 3:
					cUSBGasDia = 0x30;
					break;
				//default															
					
			}
			break;
		case 1:
			switch(temp2)
			{
				case 0:
					cUSBGasDia = 0x01;
					break;
				case 1:
					cUSBGasDia = 0x11;
					break;
				case 2:												//1.0
					cUSBGasDia = 0x21;
					break;
				case 3:
					cUSBGasDia = 0x31;
					break;
				//default														
					
			}
			break;
		case 2:
			switch(temp2)
			{
				case 0:
					cUSBGasDia = 0x02;
					break;
				case 1:
					cUSBGasDia = 0x12;
					break;
				case 2:
					cUSBGasDia = 0x22;
					break;												//1.2
				case 3:
					cUSBGasDia = 0x32;
					break;
				//default
			}
			break;
		case 3:
			switch(temp2)
			{
				case 0:
					cUSBGasDia = 0x03;
					break;
				case 1:
					cUSBGasDia = 0x13;
					break;
				case 2:
					cUSBGasDia = 0x23;
					break;
				case 3:													//1.6
					cUSBGasDia = 0x33;
					break;
				//default
			}
			break;									
		
	}
}
