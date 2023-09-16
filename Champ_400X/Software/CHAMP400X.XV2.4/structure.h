struct Type_D
{
    unsigned char digitdp1 : 1;
    unsigned char digitdp2 : 1;
    unsigned char digitdp3 : 1;
    unsigned char digitdp4 : 1;
    unsigned char digitdp5 : 1;
    unsigned char digitdp6 : 1;
    unsigned char digitdp7 : 1;
    unsigned char digitdp8 : 1;
    
};

union Type_DP
{
    struct Type_D TypeD;
    unsigned char DPGROUP[1];
};

union Type_DP TypeDP;
#define Typedp TypeDP.TypeD