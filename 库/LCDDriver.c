#include <LCDDriver.h>

void LCDRWReady(void)
{
	uchar Busy;
	LCD_RW = 1;
	LCD_RS = 0;
	LCD_DB = 0x00;
	do {
		LCD_E = 1;
		Busy = (LCD_DB & 0x80);
		LCD_E = 0;
	}while(Busy);
}
void LCDWriteCmd(uchar cmd)
{
	LCDRWReady();
	LCD_RW = 0;
	LCD_RS = 0;
	LCD_DB = cmd;
	delay(1);
	LCD_E = 1;
	delay(1);
	LCD_E = 0;
}
void LCDWriteDat(uchar dat)
{
	LCDRWReady();
	LCD_RW = 0;
	LCD_RS = 1;
	LCD_DB = dat;
	delay(1);
	LCD_E = 1;
	delay(1);
	LCD_E = 0;
	
	
}
void LCD_Init(void)
{
	#if LCD_12864 
	LCD_PSB = 1;
	LCDWriteCmd(0x34);
	LCDWriteCmd(0x30);
	LCDWriteCmd(0x0C);
	LCDWriteCmd(0x01);
	#else 
	LCDWriteCmd(0x0C);
	LCDWriteCmd(0x06);
	LCDWriteCmd(0x38);
	#endif
}
void LCDShowStr(uchar x,uchar y,uchar *str)
{
	LCDXYConfig(x,y);
	while(*str != '\0')
	LCDWriteDat(*str++);
}

void LCDXYConfig(uchar x,uchar y)
{
	uchar xy;
	#if LCD_12864 
	switch(y)
	{
		case 0:xy = 0x00+x;break;
		case 1:xy = 0x10+x;break;
		case 2:xy = 0x08+x;break;
		case 3:xy = 0x18+x;break;
		default:break;
	}
	LCDWriteCmd(xy+0x80);
	#else
	switch(y)
	{
		case 0:xy = 0x00+x;break;
		case 1:xy = 0x40+x;break;
		default:break;
	}
	LCDWriteCmd(xy+0x80);
	#endif
}
void delay(unsigned int ms)
{
	unsigned char i;
	while(ms--)
	{
		for(i=0;i<250;i++)
		{
			_nop_();
			_nop_();
			_nop_();
			_nop_();
		}
	}
}