#ifndef __KEY_H_
#define __KEY_H_

#include <reg52.h>

//sbit KEY_IN_1 = P2^0;
//sbit KEY_IN_2 = P2^1;
//sbit KEY_IN_3 = P2^2;
//sbit KEY_IN_4 = P2^3;

//sbit KEY_OUT_1 = P2^4;
//sbit KEY_OUT_2 = P2^5;
//sbit KEY_OUT_3 = P2^6;

sbit KEY_IN_1 = P2^5;
sbit KEY_IN_2 = P2^0;
sbit KEY_IN_3 = P2^1;
sbit KEY_IN_4 = P2^3;

sbit KEY_OUT_1 = P2^4;
sbit KEY_OUT_2 = P2^6;
sbit KEY_OUT_3 = P2^2;

extern unsigned char pdata KeySta[4][3];

extern unsigned char code KeyCodeMap[4][3];

void KeyScan();
	

#endif