#define disp1      PIN_B0
#define disp2      PIN_B1
#define disp3      PIN_B2
#define disp4      PIN_B3
#define disp5      PIN_A4
#define disp6      PIN_A7
#define disp7      PIN_A6
#define disp8      PIN_B5

#define segmenta   PIN_c0
#define segmentb   PIN_c1
#define segmentc   PIN_c2
#define segmentd   PIN_c3
#define segmente   PIN_c4
#define segmentf   PIN_c5
#define segmentg   PIN_c6
#define segmentdp  PIN_c7

#define ARCONKEY    PIN_B7
#define ARCONRST    PIN_B6
#define ESDIN       PIN_B4
//#define sw1        PIN_A3
//#define sw2        PIN_A4
//#define sw3        PIN_A5
#define TIGSW      PIN_B5
//#define offset     PIN_B4

#define adcavg      256
#define leftshift   8
#define adcavg1     64
#define leftshift1   6 //8

//---------------------------------------------------------------------
unsigned char digitcnt=0,hexvalue=0,readadcf=0,jj=0,setdp1=0,setdp=0,setarcdp=0;//mma=0,hibyte=0,lowbyte=0; //,pinout=0,,readswitch1=0
static unsigned char digit[8],offsetokf=0,model=0,range=0,weldon=0;//,band=0;
unsigned int32 current=0,value=0,voltage=0,cur=0,prevcur=0,curoffset=0,offcnt=0,prevoff=0;//,offset2=0;
unsigned int32 calcur=0,maxadc=675,maxshunt=400,voltage1=0,blinkcnt=0;
unsigned int16 refoffset=9,vtg=0,vtgref=0,tripvolt=0,timecnt=0,arconrstcnt=0;//100;//7;//20;//123;//130;//123; //102;
unsigned int16 prevref=0,ref=0,offset1=0,ref2=0,errorp=0,constant=120,offset=0,prevvtg=1000,rstcnt=0,iPrevWeldRef;
unsigned char uverrf=0,overrf=0,therrf=0,errorf=0,arconf=0,dispvalf=0,arconkeyf=0,arcrstkeyf=0,ocverrf=0;
unsigned char prevhr=0,prevmin=0,arconrstf=0,esdonf=0,setdp2=0,tempf=0,dispcnt=0,prevsec=0,arcrstf=0,blink=0;
volatile unsigned char min=0,sec=0,hr=0;
unsigned char noocvf=0,count3=0,cnt4sec=0,cDisplayPrevCurrFG;
//unsigned int16 i=0,num=1900,
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void initialise(void);
void display(void);
void short_del(void);
void inttochar1(unsigned int16);
void adc_init(void);
void inttochar(unsigned int16);
void readadc(void);
void dispmodel(void);
unsigned char readswitch();
unsigned char chk_band(unsigned int16,unsigned int16);
void write_memory();
void read_memory();
void debounce();
void readmem();
//void inttochar2(unsigned int16 hour,unsigned int16 min);
void inttochar2(unsigned char hour,unsigned char min);

//------------------------------------------------------------------------------
const unsigned char lookup_table[40] = {
                                       0x3F, //0    // Position - 0x00
                                       0x06, //1    // Position - 0x01
                                       0x5B, //2    // Position - 0x02
                                       0x4F, //3    // Position - 0x03
                                       0x66, //4    // Position - 0x04
                                       0x6D, //5    // Position - 0x05
                                       0x7D, //6    // Position - 0x06
                                       0x07, //7    // Position - 0x07
                                       0x7F, //8    // Position - 0x08
                                       0x6F, //9    // Position - 0x09
                                       0x80, //DP   // Position - 0x0A
                                       0x77, //A    // Position - 0x0B
                                       0x7C, //B    // Position - 0x0C
                                       0x39, //c    // Position - 0x0D
                                       0x5E, //D    // Position - 0x0E
                                       0x79, //E    // Position - 0x0F
                                       0x71, //F    // Position - 0x10
                                       0x3D  //0x7D, //G    // Position - 0x11
                                       0x76, //H    // Position - 0x12
                                       0x06, //I    // Position - 0x13
                                       0x1E, //J    // Position - 0x14
                                       0x70, //K    // Position - 0x15
                                       0x38, //L    // Position - 0x16
                                       0x55, //M    // Position - 0x17
                                       0x54, //N    // Position - 0x18
                                       0x3F, //O    // Position - 0x19
                                       0x73, //P    // Position - 0x1A
                                       0x67, //Q    // Position - 0x1B
                                       0x50, //R    // Position - 0x1C
                                       0x6D, //S    // Position - 0x1D
                                       0x78, //T    // Position - 0x1E
                                       0x1C, //3E, //U    // Position - 0x1F
                                       0x3E, //1C, //1C   //V    // Position - 0x20
                                       0x6A, //7E,  //W    // Position - 0x21
                                       0x68, //X    // Position - 0x22
                                       0x6E, //Y    // Position - 0x23
                                       0x89, //Z    // Position - 0x24
                                       0x00, //all seg ON  // Position - 0x25
                                       0x40, //-         // Position - 0x26
                                       0xFF, //o         // Position - 0x27
};

const unsigned char lookup_table1[40] = {
                                       0x3F, //0    // Position - 0x00
                                       0x06, //1    // Position - 0x01
                                       0x9B, //2    // Position - 0x02
                                       0x8F, //3    // Position - 0x03
                                       0xA6, //4    // Position - 0x04
                                       0xAD, //5    // Position - 0x05
                                       0xBD, //6    // Position - 0x06
                                       0x07, //7    // Position - 0x07
                                       0xBF, //8    // Position - 0x08
                                       0xAF, //9    // Position - 0x09
                                       0x40, //DP   // Position - 0x0A
                                       0xB7, //A    // Position - 0x0B
                                       0xBC, //B    // Position - 0x0C
                                       0x39, //c    // Position - 0x0D
                                       0x9E, //D    // Position - 0x0E
                                       0xB9, //E    // Position - 0x0F
                                       0xB1, //F    // Position - 0x10
                                       0x3D  //0x7D, //G    // Position - 0x11
                                       0xB6, //H    // Position - 0x12
                                       0x06, //I    // Position - 0x13
                                       0x1E, //J    // Position - 0x14
                                       0xB0, //K    // Position - 0x15
                                       0x38, //L    // Position - 0x16
                                       0x95, //M    // Position - 0x17
                                       0x94, //N    // Position - 0x18
                                       0x3F, //O    // Position - 0x19
                                       0xB3, //P    // Position - 0x1A
                                       0xA7, //Q    // Position - 0x1B
                                       0x90, //R    // Position - 0x1C
                                       0xAD, //S    // Position - 0x1D
                                       0xB8, //T    // Position - 0x1E
                                       0x1C, //3E, //U    // Position - 0x1F
                                       0x3E, //1C, //1C   //V    // Position - 0x20
                                       0xAA, //7E,  //W    // Position - 0x21
                                       0xA8, //X    // Position - 0x22
                                       0xAE, //Y    // Position - 0x23
                                       0x49, //Z    // Position - 0x24
                                       0x00, //all seg ON  // Position - 0x25
                                       0x80, //-         // Position - 0x26
                                       0xFF, //o         // Position - 0x27
};

