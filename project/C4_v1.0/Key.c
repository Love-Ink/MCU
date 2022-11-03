#include "Key.h"

sbit DebugLED = P1^0;


unsigned char pdata KeySta[4][3]={
																	{1,1,1},						//按键当前状态  1 弹起   0 按下
																	{1,1,1},
																	{1,1,1},
																	{1,1,1}};

unsigned char code KeyCodeMap[4][3]={
																		{'1','2','3'},
																		{'4','5','6'},		//按键地图
																		{'7','8','9'},
																		{0x0D,'0',0x0B}};																		
/**************按键扫描******************/
void KeyScan()
{
	unsigned char i;
	static unsigned char keyin=0;
	static unsigned char Keybuf[4][3]={
					{0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF},			
					{0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF}};
	
	Keybuf[keyin][0] = (Keybuf[keyin][0] << 1) 	|KEY_OUT_1;
	Keybuf[keyin][1] = (Keybuf[keyin][1] << 1) 	|KEY_OUT_2;
	Keybuf[keyin][2] = (Keybuf[keyin][2] << 1) 	|KEY_OUT_3;
	
	for(i=0;i<3;i++)
	{
		if((Keybuf[keyin][i] & 0x0F) == 0x00)
		{
			KeySta[keyin][i] = 0;
		}
		else if((Keybuf[keyin][i] & 0x0F) == 0x0F)
		{
			KeySta[keyin][i] = 1;
		}
	}
	
	keyin++;
	keyin &= 0x03;
	
	switch (keyin)
	{
		case 0: KEY_IN_4 = 1;KEY_IN_1 = 0;break;
		case 1: KEY_IN_1 = 1;KEY_IN_2 = 0;break;
		case 2: KEY_IN_2 = 1;KEY_IN_3 = 0;break;
		case 3: KEY_IN_3 = 1;KEY_IN_4 = 0;break;
		default:break;
	}
}
/**************************************/

