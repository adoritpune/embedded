void SYSTEM_INIT(void);
void PORTPIN_INIT(void);
void TIMER1_INIT(void );
void TIMER2_INIT(void);
void TIMER3_INIT(void);
void TIMER4_INIT(void);	
void TIMER5_INIT(void);
void PWM_INIT(void);
void ADC_INIT(void);
void UART1_INIT(void);
void UART2_INIT(void);	
void TRANS1(unsigned char data);
void TRANS2(unsigned char data);
void TRANSNUM(unsigned int num);
void ENCODER_INIT(void);
void SPI_INIT(void);
inline unsigned char SCANENCODER1();
inline unsigned char SCANENCODER2();
inline unsigned char SCANENCODER3();
unsigned char enc1_port();
unsigned char enc2_port();
unsigned char enc3_port();
void READ_PORTPIN(void);
//void INPUT_CAPTURE_INIT(void);
//void ReadCapture1(unsigned int * buffer);
void second_order_pid();
void second_order_pid1();
void disp_hex_dec_arclength2(unsigned int);
void calculate_arcbasevtg(unsigned int);
void change_pulse_para(unsigned int);
void load_pulse_parameter(void);
void DSP_PID(void);
//function related with keypad
inline unsigned char getkey();
inline unsigned char key_press();
inline unsigned char getkey();
inline unsigned char columnnum1(unsigned char rowno);
inline void all0exceptcolumn1();
inline void all0exceptcolumn2();
inline void all0exceptcolumn3();
inline void all0exceptcolumn4();
inline void debounce_delay();
unsigned char keyrelease();
inline void allcolumnlogic1();
inline void keydelay();
inline void init_keyportpin();
void key_application(unsigned char key);
unsigned char keypad_read();
inline unsigned char scanrow();
void Load_Initial_Constant(unsigned int);
void LCD_pulsemig_syn_data_write();
void LCD_mig_syn_data_write();

void Gcreepspeedupdate(void);
void update_digit(unsigned char col_position); //@versa
//void MIG_PID(void);

void Flash_Error(unsigned char cErrorNo);

void ADC_Reference(void);
void PID_Mig(void);
void model_selection(void);
void ModelMenu(void);
void CheckPinShort(void);









//void _ISR _IC3Interrupt(void);

void latdata(unsigned char num);
void display_data();
void display_start(unsigned char data);
void update_PMIG_pulse_para(void);
void ador_logo(void);
void clrlcd(void);
void ctrloff(void);
void displayon(void);
void displayoff(void);
void lcdscan();
void selectpage(unsigned char);
void selectcolumn1(unsigned char);
void selectcolumn2(unsigned char);
void data(unsigned char*,unsigned char);
void lcddatalat(unsigned char);
void delay(unsigned int);
void delayy(unsigned int);   
void lcdput(unsigned char,unsigned char,const unsigned char*);
void lcdput_bold(unsigned char,unsigned char,const unsigned char*);
void lcd_disp_hex_dec(unsigned int);    //CONVERTION FROM HEX TO DEC VALUE FOR DISPLAY
void datafordebug(unsigned int);

//unsigned int findmatindex2(void);
//unsigned int findmatindex3(void);
//unsigned int findmatindex4(void);
unsigned int newindmatindex4(unsigned int);
unsigned int newfindmatindex5(unsigned int);
unsigned int newfindmatindex6(unsigned int);
unsigned int newfindmatindex7(unsigned int);

void INT12_INIT(void);

void currupdate(void);
void wirespeedupdate(void);
void voltupdate(void);
void Matupdate(void);
void Diaupdate(void);
void speedupdate(void);
void timeupdate(void);
void memlocupdate(void);
void reclocupdate(void);
void wireupdate(void);  
void modelupdate(void); //not used	
void programupdate(void);
void arcforceupdate(void);
void tigcurrupdate(void);
void tigtunstenupdate(void);
void preflowupdate(void);
void burnbackupdate(void);
void postflowupdate(void);
void cratercurrentupdate(void);
void cratervoltageupdate(void);
void Reload_pulse_para();
void OPEN_pulse_para(unsigned int pulsesetws);
void INT0_INIT(void);
void cVoltageoffsetMenu(void);

void update_MMA_syn_data(unsigned char);
void update_TIG_syn_data(unsigned char);
void update_MIG_syn_data(unsigned char);
void update_PMIG_syn_data(unsigned char);


void voltage_const_pulse_freq_pid();
void Adaptive_freq_pid();
void Adaptive_base_pid();


unsigned int updatedata(unsigned int operator,unsigned int minimum,unsigned int maximum,unsigned char sign);

void updatemccparameter(unsigned char encres3, unsigned char encres2);
void updatetccparameter(unsigned char encres3, unsigned char encres2);

void updategcvparameter(unsigned char encres3, unsigned char encres2);
void updatepccparameter(unsigned char encres3, unsigned char encres2);
void updatemigparameter(unsigned char encres1);



void MMAWELD(void);
void TIGWELD(void);
void MIGWELD(void);
void PULSEWELD(void);
void base_current_pid(void);
void no_frequency_update_pid(void);//15.02.2016
			  
void local_pid(void);
void combined_pid(void);
void frequency_update_pid(void);

void new_gain_update(void);
void new_gain_update1(void);
void new_gain_update2(void);

unsigned int updatedata1(unsigned int operator1,unsigned int minimum,unsigned int maximum,unsigned char sign);
void transmittowf();
void pmig_para_init();
void Toggle_pin();

void torchaction_Pmig();
void torchaction();
void check_torch_action();
//void genpwmocvref(unsigned int refvoltage);
void genpwmccref(unsigned int refcurrent);
void genpwmcvref(unsigned int cvoffsetref,unsigned int voltageref); 

//SAVE RECALL LOCATION//

unsigned int EEPROM_Erase_Write1(unsigned int EE_Addr,unsigned int EE_Data,unsigned char cMemoryLocation);
unsigned int EEPROM_Erase_Write(unsigned int EE_Addr,unsigned int EE_Data);
unsigned int EEPROM_Read(unsigned long int EE_Addr);
void write_mode_mem(unsigned char cMemoryLocation);

void save_update(void);
void recall_update(void);

unsigned int EEPROM_Erase_Write_for_SaveRecall(unsigned int EE_Addr,unsigned int EE_Data);
unsigned int EEPROM_Read_for_SaveRecall(unsigned long int EE_Addr);
void read_current_status(void);
void write_current_status(void);
void check_eeprom_values(void);

void display_Ldata();

void updatepmigparameter(unsigned char encres1);

 

//**************************Error Functions*******************************//
void Detect_error(void);
void trip1_detection(unsigned int errvtg);
void trip_detection(unsigned int looperrorvtg);
void MMAVRDMenu(void);
void arcon_time_update(void);

inline void delay_pmig();
void LCD_tig_syn_data_write();
void updatetigparameter(unsigned char encres1);

void preflow();
void end1();
void Tig_Weld_Process();
void display_message();
void ADC_INIT_TIG(void);//@versa400
void mig_home_screen(); //@versa400
void tig_home_screen(); //@versa400

char header_usb();
char write_file_usb();
void power_ontime();
void saveNclose_file();
void analogRemoteFrameDecode(void);
void passwordupdate(unsigned int iHex);


void cMIGMenu(void);

//--------------MMA--------------------
unsigned int MMACCLookup(unsigned int iCurrent);

//--------------TIG--------------------
unsigned int TIGCCLookup(unsigned int iTigCurrent);
void cTIGMenu(void);

//--------------MIG-------------------
void Read_TorchSW();
inline void delay_mig_torch();
void Generate_SPI_Reference(unsigned int iReference);
void Generate_Reference(unsigned int iGenerate_ref_pwm);
void Generate_Reference_for_4T(unsigned int iRefmvtg);
void inch_motor(unsigned int inch_pwm);
void Read_motor_vtg();
void MIG_superfast_PID(void);
void cMIGGasMenu(void);
 void motor_control_pid(void);





