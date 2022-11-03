#include "LCD1601.h"

/**********    æ���    **************/
void LCDRWReady()
{
	unsigned char addr;
	LCD_DB = 0xFF;
	LCD_RS = 0;
	LCD_RW = 1;
	
	do {
		LCD_E = 1;
		addr = LCD_DB;
		LCD_E = 0;
	}while(addr & 0x80);
}
/**************************************/
/**********    д����     **************/
void LCDWriteDat(unsigned char dats)
{
	LCDRWReady();
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DB = dats;
	LCD_E = 1;
	LCD_E = 0;
}
/**************************************/
/***********    дָ��    **************/
void LCDWriteCmd(unsigned char cmd)
{
	LCDRWReady();
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DB = cmd;
	LCD_E = 1;
	LCD_E = 0;
}
/**************************************/
/*********     XY��������    ***********/
void LCDXYConfig(unsigned char x ,unsigned char y)
{
	unsigned char addr;
	if(y == 0)
	{
		addr = 0x00 + x;
	}
	else 
	{
		addr = 0x40 + x;
	}
	
	LCDWriteCmd(addr | 0x80);
}
/**************************************/
/**********    ��ʾ�ַ�    ************/
void LCDShowStr (unsigned char x, unsigned char y, unsigned char *str)
{
	unsigned char i=x;
	LCDXYConfig(x,y);
	while(*str != '\0')
	{
		if(i>=8)	
		{
			LCDXYConfig(i-8,1);
			i=0;
		}				
		LCDWriteDat (*str++);
		i++;
	}
}
/**************************************/
/***********    ��ʼ��    *************/
void LCDInit()
{
	LCDWriteCmd(0x38);
	LCDWriteCmd(0x0C);
	LCDWriteCmd(0x06);
	LCDWriteCmd(0x01);
}