#ifndef __HX711_H
#define __HX711_H

#include <reg52.h>
#include <intrins.h>

sbit HX711_SCK = P1^3;
sbit HX711_DOUT = P1^2;

void HX711_Read(unsigned char *str);
void LongToStr(unsigned int num,unsigned char *str);
void HX711_delay(void);
#endif