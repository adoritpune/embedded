
void Decode_querry(void)
{
	unsigned int i;
	unsigned char cData;
	unsigned int idata2,iData;
	unsigned int *BuffAddr;
 	if(cByte_cntr < 3)
 	{
		cByte_cntr = 3;
	}
	iCrc_querry_word = cReceive_buffer[cByte_cntr];
	iCrc_querry_word = (iCrc_querry_word << 8);
	iCrc_querry_word |= cReceive_buffer[cByte_cntr - 1];

	Calculate_CRC(cReceive_buffer,(cByte_cntr - 1));
	cSlave_addr = cReceive_buffer[0];
	
//	cPort_addr = SLAVEADDRESS; // if required for EEPROM read;
//------------------------------	
/*
	iCrc_querry_word = sCRC_response_word = 11;
	cSlave_addr = 1;
	cReceive_buffer[1] = 0x03;
	cReceive_buffer[2] = 0x00;		
	cReceive_buffer[3] = 0x00;	
	cReceive_buffer[4] = 0x00;	
	cReceive_buffer[5] = 0x01;	
*/
//----------------------	
	if((iCrc_querry_word == sCRC_response_word)&&(cSlave_addr == SLAVEADDRESS))
	{ 
		cFunction_code = cReceive_buffer[1];
	
		iInput_reg_addr = cReceive_buffer[2];
		iInput_reg_addr = ((iInput_reg_addr << 8) + cReceive_buffer[3]);	
			
		cNo_of_byte = cReceive_buffer[4];
		cNo_of_byte = ((cNo_of_byte << 8) + cReceive_buffer[5]); 

		Response_array[0] = cSlave_addr;
		Response_array[1] = cFunction_code;
		Response_array[2] = cNo_of_byte * 2;	
		
		BuffAddr = (unsigned int )(STARTADDRESS + iInput_reg_addr * 2);
		cData = 0X00;		
		switch(cFunction_code)
		{
			case 0x01:
					Response_array[0] = cSlave_addr;
					Response_array[1] = cFunction_code;
					Response_array[2] = cNo_of_byte;
					if(iInput_reg_addr == 0)
					{
						if((weldmode == 'G')||(weldmode == 'P'))
						{
							if(wfstatus.twotfourtmode1 == 0)
							{
								cData = 0;
							}
							else
							{
								cData = 1;
							}		
						}							
					}						 
					Response_array[3] |= cData;
					cByte_cntr = 4;
				break;
			case 0x03:
//-------------------------------------	
					Response_array[0] = cSlave_addr;
					Response_array[1] = cFunction_code;		
//		iTest2 = BuffAddr;
				for(i = 0; i < cNo_of_byte; ++i )
				{
					iData = *BuffAddr;
					Response_array[i * 2 + 3] = (iData >> 8);	
					Response_array[i * 2 + 4] = (iData & 0x00FF);	
					BuffAddr = BuffAddr + 1;						
				}
				cByte_cntr = cNo_of_byte*2+3;
//-------------------------------------			
				/*
				switch(cNo_of_byte)
				{
					case 0x01:
						Response_array[3] = (iInput_data >> 8);				
						Response_array[4] = (iInput_data & 0x000000FF);
						cByte_cntr = 2+3;
						break;
					case 0x02:
						Response_array[3] = (iInput_data >> 8);				
						Response_array[4] = (iInput_data & 0x000000FF);
		
						Response_array[5] = (idata2 >> 8);				
						Response_array[6] = (idata2 & 0x000000FF);
						cByte_cntr = 4+3;
						break;
					case 0x03:
						Response_array[3] = (iInput_data >> 8);				
						Response_array[4] = (iInput_data & 0x000000FF);
		
						Response_array[5] = (0 >> 8);				
						Response_array[6] = (0 & 0x000000FF);
		
						Response_array[7] = (0 >> 8);				
						Response_array[8] = (0 & 0x000000FF);
						cByte_cntr = 6+3;
						break;
					case 0x10:
						Response_array[3] = (iInput_data >> 8);				
						Response_array[4] = (iInput_data & 0x000000FF);
						
						for(i = 2; i < cNo_of_byte*2; ++i )
						{
							Response_array[i+3] = 0x00;	
						}
						cByte_cntr = i+3;
						break;
					default:
						break;
				}	
				*/		
				break;
			case 0x05:

					Response_array[0] = cSlave_addr;
					Response_array[1] = cFunction_code;

					Response_array[2] = cReceive_buffer[2];
					Response_array[3] = cReceive_buffer[3];

					Response_array[4] = cReceive_buffer[4];
					Response_array[5] = cReceive_buffer[5];

					cByte_cntr = 6;

					iPara_addr = cReceive_buffer[2];
					iPara_addr = ( ( iPara_addr << 8 ) + cReceive_buffer[3] );
				
					iPara_update = cReceive_buffer[4];
					iPara_update = ( ( iPara_update << 8 ) + cReceive_buffer[5] );
//					cParaUpdatefg = 1;					
//					UpdatePara();
				break;
			case 0x06:

					Response_array[0] = cSlave_addr;
					Response_array[1] = cFunction_code;

					Response_array[2] = cReceive_buffer[2];
					Response_array[3] = cReceive_buffer[3];

					Response_array[4] = cReceive_buffer[4];
					Response_array[5] = cReceive_buffer[5];

					cByte_cntr = 6;

					iPara_addr = cReceive_buffer[2];
					iPara_addr = ( ( iPara_addr << 8 ) + cReceive_buffer[3] );
					iPara_addr |= 0x00000000;//Holding REGISTER
				
					iPara_update = cReceive_buffer[4];
					iPara_update = ( ( iPara_update << 8 ) + cReceive_buffer[5] );
					cParaUpdatefg = 1;					
					UpdateParaFromHMI();

					
				break;				
			default:
				break;
		}	
			Calculate_CRC(Response_array,cByte_cntr);															
			Response_array[cByte_cntr] = sCRC_response_word;		
			Response_array[cByte_cntr+1] = (sCRC_response_word >> 8);
			cByte_cntr = cByte_cntr + 2;					
			
			for(i = 0; i < cByte_cntr; ++i)
			{
// here we will send data to on serial Buffer
				TRANS1(Response_array[i]);
				String_received_fg = 0;
			}
	}
	else
	{
		String_received_fg = 0;
	}
}

//--------------------------------------------------------
void UpdateParaFromHMI(void)
{	
	
	switch(iPara_addr)
	{
		case HMI_CURRENT:
			iCurrent = iPara_update;			
			break;
		case HMI_VOLATGE:
			iVoltage = iPara_update;
			if(weldmode=='G')
			{
				para.migmode.setvoltage = iVoltage;				
			}
			else
			{
				Tbasevoltage = iVoltage;				
			}				
			break;			
		case HMI_WIRESPEED:
			iWireSpeed = iPara_update;
			if(weldmode=='G')
			{
				para.migmode.setwspeed = iWireSpeed;				
			}
			else
			{
				para.pmigmode.setwspeed = iWireSpeed;				
			}		 		
			break;
		case HMI_DIA:
			if(weldmode=='G')
			{
				iDiaNo = dia;				
			}
			else
			{
				iDiaNo = pdia;				
			}				
			break; 
		case HMI_GAS:
			if(weldmode=='G')
			{		
				iGasNo = gas;				
			}
			else
			{
				iGasNo = pgas;				
			}		
			break; 
		case HMI_MAT:
			if(weldmode=='G')
			{
				iMatNo = mat;				
			}
			else
			{
				iMatNo = pmat;
			}		
			break; 	
		case HMI_ARCLENGTH:
			if(weldmode=='G')
			{
				iArcLength = para.migmode.inductance;				
			}
			else
			{
				iArcLength = para.pmigmode.arclength;				
			}		
			break; 										
		 default:
			break;
	}	
	cParaUpdatefg = 0;	
	cTestfg = 1;
}	
//--------------------------------------------------------
void UpdateParaIntoHMI(void)
{
	if(weldmode=='G')
	{
		iCurrent = dispautocurrent;
		iVoltage = para.migmode.setvoltage;
		iWireSpeed = para.migmode.setwspeed;
		iDiaNo = dia;
		iGasNo = gas;
		iMatNo = mat;				
	}
	else
	{	
		iCurrent = dispautocurrent;
		iVoltage = Tbasevoltage;		
		iWireSpeed = para.pmigmode.setwspeed;
		iDiaNo = pdia;
		iGasNo = pgas;
		iMatNo = pmat;
		iArcLength = para.pmigmode.arclength;						
	}	
	iActualCurrent = CURRENT;
	iActualVoltage = VOLTAGE;
	
	
	
	
	
}	
//--------------------------------------------------------





