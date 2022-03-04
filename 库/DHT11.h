#ifndef __DHT11_H
#define __DHT11_H

#include <reg52.h>
#include <intrins.h>
#include <LCDDriver.h>
sbit DHT11_DATA = P1^0;

void delayms(unsigned int ms);
void delayus(unsigned char us);
unsigned char DHT11_byte();
void DHT11_Start();
void DHT11_Read(unsigned char *str);


#endif