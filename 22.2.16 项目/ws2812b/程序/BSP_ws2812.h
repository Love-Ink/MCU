#ifndef __BSP_WS2812_H
#define __BSP_WS2812_H

#include "STC8G.h"
#include "intrins.h"
#define uchar unsigned char 

sbit Send_Dat = P5^5;
struct RGB{
	uchar G_VAL;
	uchar R_VAL;
	uchar B_VAL;
};

void send_24_Bit (struct RGB RGB_VAL);
void send_A_bit (uchar VAL);
void ws2812_Init();

#endif