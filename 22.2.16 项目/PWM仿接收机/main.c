#include "reg52.h"
#include "intrins.h"
sbit PwmOut = P1^0;
sbit Button = P1^1;
bit ledBuff=0;
unsigned char halfMsCount=0;
unsigned char PwmDownTime=0;
void delay(int ms);
int main(void) {
	TMOD = 0x01;
	TH0 = 0xFE;
	TL0 = 0x0C;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	while(1){
		if(Button == 0){
			delay(10);
			if(Button == 0) {
				while(Button);
				ledBuff =~ledBuff;
			}
		}
		if(ledBuff) {
			PwmDownTime = 37;
		} else {
			PwmDownTime = 38;
		}
	}
	
}
void delay(int ms){
	unsigned char i=0;
	while(ms--){
		for(i=0;i<200;i++) {
			_nop_();_nop_();_nop_();_nop_();_nop_();
		}
	}
}
void interruptTime0 () interrupt 1 {
	TH0 = 0xFE;
	TL0 = 0x0C;
	
	if(halfMsCount <= PwmDownTime) {
		PwmOut = 0;
	} else {
		PwmOut = 1;
	}
	if(halfMsCount == 40){
		halfMsCount = 0;
	} else {
		halfMsCount++;
	}
	
	
}