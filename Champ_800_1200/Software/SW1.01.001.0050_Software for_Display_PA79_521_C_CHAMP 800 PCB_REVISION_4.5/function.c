void timer1_init();
void timer4_init();
void adc_init();
void display_int();
void pwm_init();
void encoder_init();
void display_data();
void latchdata(unsigned char);
inline unsigned char scanencoder(void);
void disp_hex_dec_curr(unsigned int );
void disp_hex_dec_volt(unsigned int);
void setparameter(unsigned char);
inline unsigned char enc_port(void);
void uart_init(void);
void trans_head(unsigned char);
void data_head(void);
void mma(void);
void saw(void);
void trip(void);
void delay(unsigned int);
void power_on(void);
void system_init(void);
void Portpin_init(void);
unsigned char Read_Encodersw(void);
unsigned char Read_Torchsw(void);
void trans(unsigned char data);  //Transmit data to saw head in SAW mode
unsigned int EEPROM_Read(unsigned int);
unsigned int EEPROM_Erase_Write(unsigned int,unsigned int);
unsigned int model_select(void);
void Read_portpin();
void genref(unsigned int);
void drivemotor(unsigned int);
void torchaction(void);
void second_order_pid(void);
void Check_cal_mode(void);
void powerONflash();




