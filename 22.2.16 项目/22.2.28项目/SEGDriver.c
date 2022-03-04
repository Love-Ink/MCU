#include "SEGDriver.h"

unsigned char SEG_Str[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};



void SEGShowNum(unsigned int num){
	static unsigned char i=0;
	SEG = 0xFF;

	switch (i)
	{
			case 0: SEG2=1; SEG1=1; SEG0=0; i=0; SEG=~(SEG_Str[num%10]); break;
			case 1: SEG2=1; SEG1=0; SEG0=1; i++; SEG=~(SEG_Str[num/10%10]); break;
			case 2: SEG2=0; SEG1=1; SEG0=1; i=0; SEG=~(SEG_Str[num/100]); break;
			default: break;
	}
	
}