#ifndef __LCDDRIVER_H
#define __LCDDRIVER_H

#include <reg52.h>
#include <intrins.h>

#define LCD_12864 1   //用12864屏这里改 1  1602则改 0

#define uchar unsigned char
#define LCD_DB P0
sbit LCD_RS = P3^5;
sbit LCD_RW = P3^6;
sbit LCD_E = P3^4;
sbit LCD_PSB = P3^7;

void LCD_Init(void);
void LCDRWReady(void);
void LCDWriteCmd(uchar cmd);
void LCDWriteDat(uchar dat);
void delay(unsigned int ms);
void LCDXYConfig(uchar x,uchar y);
void LCDShowStr(uchar x,uchar y,uchar *str);


#endif
