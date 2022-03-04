#include "reg52.h"
#include "intrins.h"
#define uint8_t unsigned char
sbit DS = P2^0;
sbit SH_CP = P2^1;
sbit ST_CP = P2^2;

sbit KEY_IN = P3^2;
uint8_t flag = 1;
bit LEDBuff = 0;
int goToReadTime=0;
sbit LED = P1^1;
void send595Bytes (unsigned long Bytes);
int main (void) {
    TMOD = 0x11;
    TH0 = 0xD8;
    TL0 = 0xF0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;

    while(1);
}
unsigned long pow (int a,int b){
	unsigned long pow=a;
	if(b==0){
		return 1;
	} else if (b==1) {
		return a;
	}
	for(;b>1;b--){
		pow *= a;
	}
	return pow;
}
void send595Bytes (unsigned long Bytes) {
    char i;
		SH_CP = 0;
    ST_CP = 0;
    for(i=0;i<32;i++) {
        DS = (Bytes & 0x01);
        _nop_();
        _nop_();
        SH_CP = 1;
        _nop_();
        _nop_();
        SH_CP = 0;
        Bytes = Bytes >> 1;
    }
    ST_CP = 1;
    _nop_();
    _nop_();
    ST_CP = 0;
}
void interruptTime1 () interrupt 1 {
    static uint8_t i=0,x=0,j=0;
    static unsigned long n=0xffffffff;
    TH0 = 0xD8;
    TL0 = 0XF0;
		send595Bytes(n);
    if(1){
			if(i%4==3){
				if(flag == 1){
					n >>= 1;
					if(n == 0x001){
							LED=0;
							flag = 2;
					}
				}
				else if(flag == 2){
					n = ((n&0x80000000)>>9)|((n<<1)&0xffffffff);
					if(n == 0x80000000)
						flag = 3;
				}	
				else if (flag == 3){
					n = ((n&0x001)<<9)|((n>>1)&0xffffffff);
					if (n == 0x001)
						flag = 4;
				}
				else if(flag == 4) {
					n -= 2147483648/(pow(2,j));
					j++;
					if(j == (31-x)){
							j = 0;
							x++;
						}
					if(x==31){
						flag = 5;x=0;}
				}
				else if(flag == 5){
					n <<= 1;
					if((n&0xffffffff) == 0x80000000){
						flag = 6;n=0xC0000000;}
				}
				else if(flag == 6){
					n >>= 1;
					n += 0x80000000;
					if((n&0xffffffff) == 0xffffffff){
						 flag=1;
						LEDBuff = 0;
					}
				}
				n &= 0xffffffff;
				i = 0;
      }
    }
    else{
						n = 0xffffffff;
						flag = 1;
						x=0;
						j = 0;
    }
    i++;
}