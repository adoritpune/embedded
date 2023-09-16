
unsigned int iArcMissCntr;
unsigned char arcMissingfg;
//@ Ensure Correct baud rate setting in UART1(2400) init and USB drive file
void decimal_to_ascii(unsigned int hex_data)    //CONVERTION FROM decimal to ascii
{
     disp_data_arr[3]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     disp_data_arr[2]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     disp_data_arr[1]= 0x30 + (hex_data % 10);
     hex_data /= 10;
     disp_data_arr[0]= 0x30 + hex_data;
}


void send_string(unsigned char data[])
{
    unsigned char index=0;
	while(data[index]!=0)
	{
	TRANS1(data[index]);
	index++;
	}

}

char create_file(unsigned char file_name[])
{
unsigned char name_array[15];

 	decimal_to_ascii(first_digits);
	name_array[0] = disp_data_arr[2];
	name_array[1] = disp_data_arr[3];
	
	decimal_to_ascii(second_digits);
	name_array[2] = disp_data_arr[2];
	name_array[3] = disp_data_arr[3];
	
	decimal_to_ascii(third_digits);
	name_array[4] = disp_data_arr[2];
	name_array[5] = disp_data_arr[3];
	
	decimal_to_ascii(fourth_digits);
	name_array[6] = disp_data_arr[2];
	name_array[7] = disp_data_arr[3];
	name_array[8] = '.';
	name_array[9] = 'c';
	name_array[10] = 's';
	name_array[11] = 'v';
	name_array[12] = 0x00;

	send_string("CREATE");  //@command  //1
    TRANS1(' '); 			//@space //2

	send_string(name_array); //@file name  //3
 /*
 	decimal_to_ascii(first_digits);
	TRANS1(disp_data_arr[2]);
	TRANS1(disp_data_arr[3]);
	
	decimal_to_ascii(second_digits);
	TRANS1(disp_data_arr[2]);
	TRANS1(disp_data_arr[3]);
	
	decimal_to_ascii(third_digits);
	TRANS1(disp_data_arr[2]);
	TRANS1(disp_data_arr[3]);
	
	decimal_to_ascii(fourth_digits);
	TRANS1(disp_data_arr[2]);
	TRANS1(disp_data_arr[3]);
	send_string(".csv");    //@file extension //4
	*/
	for(j=0;j<100;j++)
	for(i=0;i<20000;i++); //50000
	
	TRANS1(13);  //send enter //5
}

char write_decimalto_file(unsigned int decimal)
{
	decimal_to_ascii(decimal);
	TRANS1(disp_data_arr[0]);
	TRANS1(disp_data_arr[1]);
	TRANS1(disp_data_arr[2]);
	TRANS1(disp_data_arr[3]);
}

void saveNclose_file()
{
	unsigned char cTemp_array[15];
	TRANS1(13);  //send enter
	send_string("ARC ON TIME:,");
	decimal_to_ascii(arcontime.hr);
	cTemp_array[0] = disp_data_arr[1];
	cTemp_array[1] = disp_data_arr[2];
	cTemp_array[2] = disp_data_arr[3];
	cTemp_array[3] = ':';
	decimal_to_ascii(arcontime.min);
	cTemp_array[4] = disp_data_arr[2];
	cTemp_array[5] = disp_data_arr[3];
	cTemp_array[6] = ':';
	decimal_to_ascii(arcontime.sec);
	cTemp_array[7] = disp_data_arr[2];
	cTemp_array[8] = disp_data_arr[3];	
	cTemp_array[9] = 0;
	send_string(cTemp_array);  
	TRANS1(',');
	TRANS1(26);  //Ctrl+Z
	
	arcontime.hr = arcontime.min = arcontime.sec = 0;
	write_current_status();
//	send_string("EXIT");	
}
void power_ontime()
{
	pontime.sec++;
	if(pontime.sec>=60)
	{
		pontime.sec=0;
		pontime.min++;
	}
	if(pontime.min>=60)
	{
		pontime.min=0;
		pontime.sec=0;
		pontime.hr++;
	}
	if(pontime.hr>=999)
	{
		pontime.min=0;
		pontime.sec=0;
		pontime.hr=0;
	}
}
void pon_create_file()
{

	unsigned char name_array[15];
	unsigned int iFileNo;

	decimal_to_ascii(third_digits);
	name_array[0] = disp_data_arr[2];
	name_array[1] = disp_data_arr[3];

	decimal_to_ascii(fourth_digits);
	name_array[2] = disp_data_arr[2];
	name_array[3] = disp_data_arr[3];
	
	iFileNo = EEPROM_Read(202);
	iFileNo = iFileNo & 0x00FF;
	iFileNo = iFileNo << 8;
	iFileNo |= EEPROM_Read(204);
	                
	decimal_to_ascii(iFileNo & 0x00FF);
	name_array[6] = disp_data_arr[2];
	name_array[7] = disp_data_arr[3];
	
	decimal_to_ascii(iFileNo >> 8);
	name_array[4] = disp_data_arr[2];
	name_array[5] = disp_data_arr[3]; 
	
	name_array[8] = '.';
	name_array[9] = 'c';
	name_array[10] = 's';
	name_array[11] = 'v';
	name_array[12] = 0x00;

	iFileNo++;
	if(iFileNo > 9999)
	{
		iFileNo = 0;
	}
	
	EEPROM_Erase_Write((204),(iFileNo & 0x00FF));
	EEPROM_Erase_Write((202),(iFileNo >> 8));

//	TRANS1(26);  //Ctrl+Z
	send_string("CREATE");  //@command  //1
    TRANS1(' '); 			//@space //2
    
	send_string(name_array); //@file name  //3
//    TRANS1(13);  //send enter	
//    TRANS1(13);  //send enter
//    TRANS1(13);  //send enter        
	for(j=0;j<100;j++)
	for(i=0;i<1000;i++); //50000
	TRANS1(13);  //send enter
}

char header_usb()
{
unsigned char cTime_array[11],cTemp_array[4];	
		
    	TRANS1(13);  //send enter
    	send_string("PROGRAM NUMBER:,");
		decimal_to_ascii(program_number);
		cTemp_array[0] = disp_data_arr[2];
		cTemp_array[1] = disp_data_arr[3];		
		cTemp_array[2] = 0;
		send_string(cTemp_array);    	
    	TRANS1(13);  //send enter    	
    	send_string("TIME:,");send_string("CURRENT:,");send_string("VOLTAGE:,");send_string("Weld Joint Count:,");send_string("ARC MISSING:,");
		TRANS1(13);  //send enter
		iWeldcount = 1;
		iArcMissCntr = 0;
}
	
char write_file_usb()
{
unsigned char cTime_array[11],cTemp_array[4];
unsigned int  i;

	decimal_to_ascii(pontime.hr);
	cTime_array[0] = disp_data_arr[2];
	cTime_array[1] = disp_data_arr[3];
	decimal_to_ascii(pontime.min);
	cTime_array[2] = ':';
	cTime_array[3] = disp_data_arr[2];
	cTime_array[4] = disp_data_arr[3];
	decimal_to_ascii(pontime.sec);
	cTime_array[5] = ':';
	cTime_array[6] = disp_data_arr[2];
	cTime_array[7] = disp_data_arr[3];
	cTime_array[8] = 0;
	send_string(cTime_array);  
	TRANS1(',');

	switch(weldmode)
	{
		case 'M':
		    if(CURRENT <= 20)
		    {
				arcMissingfg = 1;
		    }
		break;
		case 'T':
		    if(CURRENT <= 5)
		    {
				arcMissingfg = 1;
		    }
		break;
		case 'G':
		    if(CURRENT <= 5)
		    {
				arcMissingfg = 1;
		    }
		break;
		default:
		break;
	}

	decimal_to_ascii(CURRENT);
	for(i = 0; i < 3; ++i)
	{
		cTemp_array[i] = disp_data_arr[i+1];
	}
	cTemp_array[i] = 0;
	send_string(cTemp_array);
  	TRANS1(',');
	decimal_to_ascii(VOLTAGE);
	for(i = 0; i < 3; ++i)
	{
		cTemp_array[i] = disp_data_arr[i+1];
	}
	cTemp_array[i] = cTemp_array[i-1];
	cTemp_array[i-1] = '.';
	cTemp_array[i+1] = 0;
	send_string(cTemp_array); 
	TRANS1(',');  
	decimal_to_ascii(iWeldcount);
	for(i = 0; i < 3; ++i)
	{
		cTemp_array[i] = disp_data_arr[i+1];
	}
	cTemp_array[i] = 0;
	send_string(cTemp_array);  
	TRANS1(',');

    if(arcMissingfg)
    {
		iArcMissCntr++;
		decimal_to_ascii(iArcMissCntr);
		for(i = 0; i < 3; ++i)
		{
			cTemp_array[i] = disp_data_arr[i+1];
		}
		cTemp_array[i] = 0;
		send_string(cTemp_array);
		arcMissingfg = 0;                              
    }
    else
    {
		TRANS1(',');  //send enter
    }
	TRANS1(13);  //send enter
//	saveNclose_file();
	return 1;
}	
	 
char load_machine_serial_number()
{
	unsigned char digit_position=1;
	
	clrlcd();
	lcdput_bold(0,0,"M/C SERIAL No. ");
	
	selectpage(5);
	selectcolumn1(20);
	data(&character[27][0],8);
	lcdput(5,30,"DOWN");
	
	selectpage(5);
	selectcolumn2(64);
	data(&character[26][0],8);
	lcdput(5,75,"UP");
	
	lcdput(6,0,"PRESS PARAMETER KNOB");
	lcdput(7,0,"To Save and Exit");
	
	setlcdweldparameter=1; //@dummy write to blink LCD clear this flag while exiting thid function
	
	
	while(1)
	{
		
	if(keyreadf==1)	
	{
	key=keypad_read();
	keyreadf=0;
	}
	
	if(key=='L')
	{
	EEPROM_Erase_Write((180),first_digits);	
	EEPROM_Erase_Write((182),second_digits);		
	EEPROM_Erase_Write((184),third_digits);	
	EEPROM_Erase_Write((186),fourth_digits);		
	break;
	}
	
 	if(Prevkey!=key)
	{
		if(key=='D')  //upkey
		{
		digit_position++;
			if(digit_position>=4)
			{
				digit_position=4;
			}
		}
		else if(key=='E')  //downkey
		{
		digit_position--;
			if(digit_position<=1)
			{
			digit_position=1;
			}
		}
	Prevkey=key;
	}
	
	switch(digit_position)
	{
	case 1 : first_digits=updatedata(first_digits,0,99,encod1); 	
			 encod1='$';
			 selectpage(4);
			 selectcolumn1(10);
	break;
	
	case 2 : second_digits=updatedata(second_digits,0,99,encod1); 	
			 encod1='$';
			 selectpage(4);
			 selectcolumn1(40);
	break;
	
	case 3 : third_digits=updatedata(third_digits,0,99,encod1); 	
			 encod1='$';
			 selectpage(4);
			selectcolumn2(70);
	break;
	
	case 4 : fourth_digits=updatedata(fourth_digits,0,99,encod1); 	
			 encod1='$';
			 selectpage(4);
			selectcolumn2(100);
	break;
	}
	
/********START****for placing blinking cursor at next line(page/below serial number)*********/
		if(lcdscan_flag==1)
		{
			
			data(&character[24][0],8);
		}
		else
		{
		lcdput(4,0,ar15);
		}
 /********ENDs****for placing blinking cursor at next line(page/below serial number)*********/    
    
    lcd_disp_hex_dec(first_digits);
	update_digit(10);            
		      	 
	lcd_disp_hex_dec(second_digits); 
	update_digit(40);            
    
	lcd_disp_hex_dec(third_digits);
	update_digit(70);            
		
	lcd_disp_hex_dec(fourth_digits);
	update_digit(100);            
  	} 
  	  
	setlcdweldparameter=0;
}