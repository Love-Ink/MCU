#ifndef __LCD1601_H_
#define __LCD1602_H_

#include <reg52.h>

#define LCD_DB  P0

sbit LCD_RS = P1^0;
sbit LCD_RW = P1^1;
sbit LCD_E = P1^2;

void LCDInit();
void LCDWriteDat(unsigned char dats);
void LCDWriteCmd(unsigned char cmd);
void LCDXYConfig(unsigned char x ,unsigned char y);
void LCDShowStr (unsigned char x, unsigned char y, unsigned char *str);
#endif