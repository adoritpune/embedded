//FOR DISPLAY
void latdata(unsigned char);
void display(void);
void hex_to_dec_curr(unsigned int);
void hex_to_dec_volt(unsigned int);
void hex_to_dec_time(unsigned int Hour, unsigned int Min);

//FOR ENCODER
//unsigned char scanencoder(void);
//unsigned char enc_port(void);

//FOR SPDT SWITCH
//void Read_SPDT_SW();

//FOR MAIN FUNCTIONS
void Delay100uSec(void);
void system_init();
void Modelcalibration(void);
void Delay(unsigned int iCnt, unsigned char cUnit);
//unsigned int updatedata(unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int MMACCLookup(unsigned int iCurrent);
//unsigned int MMACCLookupArcforce(unsigned int iCurrent);
//unsigned int MMACCLookupHotStart(unsigned int iCurrent);
void Model_Menu(void);
void Model_Selection(void);

//FOR DAC
void I2C_init(void);
void startBitGen(void);
void stopBitGen(void);
void ACK(void);
void NOACK(void);
void clock_high();
void clock_low();
void delayI2C(void);
void SendACK(void);
void I2C_Write(unsigned int data_out);
void bytewrite(unsigned char data);

//FOR SWITCH
void Read_TactileSwitch(void);
void Read_RockerSwitch(void);
void Read_Switch_Selection(void);
void ResetMode(void);
void ArcOnAndResetMode(void);
void Read_VRD_Switch(void);

//FOR MEMORY
void Write_EEPROM(unsigned int,unsigned int);
unsigned int Read_EEPROM(unsigned int);
void delayms();

//FOR TRIP
void Trip_detect(unsigned int trip_vtg);
void Trip_detect_OV(unsigned int trip_vtge);

//-----------------------
void Write_byte(unsigned int data,unsigned int adrs);
unsigned char Read_byte(unsigned int adrs);
//-----------------------

unsigned char EUART1_Read(void);
void EUART1_Write(unsigned char txData);

void ModelSelection(void);
void CheckPinShort(void);

//void TransmiToRemote(unsigned int,unsigned int,unsigned int);
void TransmiToRemote(unsigned int txdata1,unsigned int txdata2,unsigned int txdata3,unsigned int txdata4,unsigned int txdata5);
void DigitalRemoteFrameDecode(void);
void trans(unsigned char);
void TRANS1(unsigned char data);
void send_string_u1(char *s);

void USART2_initialize(void);
void TRANS2(unsigned char data);
void send_string_u2(char *s);
