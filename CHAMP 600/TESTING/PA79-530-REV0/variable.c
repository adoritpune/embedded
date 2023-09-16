#define disp1      PIN_B0
#define disp2      PIN_B1
#define disp3      PIN_B2
#define disp4      PIN_B3

#define segmenta   PIN_c0
#define segmentb   PIN_c1
#define segmentc   PIN_c2
#define segmentd   PIN_c3
#define segmente   PIN_c4
#define segmentf   PIN_c5
#define segmentg   PIN_c6
#define segmentdp  PIN_c7

#define sw1        PIN_A3
#define sw2        PIN_A4
#define sw3        PIN_A5
#define TIGSW      PIN_B5
//#define offset     PIN_B4

//---------------------------------------------------------------------
unsigned char digitcnt=0,hexvalue=0,pinout=0,readadcf=0,readswitch1=0,jj=0,mma=0,hibyte=0,lowbyte=0;
static unsigned char digit[4],offsetokf=0,model=0,range=0,weldon=0,band=0;
unsigned int32 current=0,value=0,voltage=0,cur=0,prevcur=0,curoffset=0,offcnt=0,prevoff=0,offset2=0;
unsigned int32 calcur=0,maxadc=675,maxshunt=400;
unsigned int16 refoffset=9;//100;//7;//20;//123;//130;//123; //102;
unsigned int16 prevref=0,ref=0,offset1=0,ref2=0,errorp=0,constant=120,offset=0;
//---------------------------------------------------------------------
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
void mmatigsw();
void debounce();
void readmem();


//------------------------------------------------------------------------------
