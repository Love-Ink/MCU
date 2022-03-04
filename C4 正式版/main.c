#include <reg52.h>
#include <intrins.h>

#include "LCD1601.h"
#include "Key.h"
#include "variable.h"




void main()
{
	unsigned char i;
	EA = 1;
	LCDInit();
	InitTime(50);
	
	LED2 = 0;						//绿色小灯
	
	LCDShowStr(4,0,"*******");
	
	for(i=0;i<2;i++)
	{
			Buzz = 0;
			delay(100);     //开机响两下
			Buzz = 1;
			delay(500);
	}
	
	
	while(1)
	{
			KeyDrive();
		
			if (step == 1)
			{
				if((Place != 0)&&(KeySta[3][2] != 0))
				{
					Place = 0;
					LCDShowStr(4,0,"*******");   //松掉破解按键   清空破解进度
				}
			}
			else if (step == 2)
			{
				step = 4;
				LCDWriteCmd(0x01);
				LCDShowStr(5,0,"CT WIN");							//结局2:CT胜利
				LED2 = 0;
			}
			else if (step == 3)
			{
				step = 4;
				LCDWriteCmd(0x01);
				LCDShowStr(5,0," T WIN");							//结局3:T胜利
				LED1 = 0;
			}
			if(PlaceKey == 1)
			{
				Placems = 4000;
			}
			else 
			{
				Placems = 2000;
			}
			
			
	}
	
}

/**************************************/
void delay(int ms)
{
	unsigned char i;
	while(ms--)
		for(i=0;i<250;i++)
		{
			_nop_();
			_nop_();
			_nop_();
			_nop_();
		}
}
/**************************************/

/**************************************/
/**************中断设置****************/
void InitTime(unsigned int ms)
{
	unsigned long tmr;
	TMOD &= 0xF0;
	TMOD |= 0x02;
	
	tmr = 11059200/12;
	tmr = (ms * tmr) / 1000;
	tmr = 65536 - tmr;
	tmr = tmr + 30;
	
	T0RH = (unsigned char)(tmr >> 8);
	T0RL = (unsigned char)tmr;
	
	TH0 = T0RH;
	TL0 = T0RL;
	
	ET0 = 1;
	TR0 = 1;
}
/**************************************/
/************数字转字符*****************/
unsigned char LongToString(unsigned char *str,unsigned long num)
{
	signed char i = 0;
	unsigned char len = 0;
	unsigned char buf[8];
	
	do {
		buf[i++] = num%10;
		num = num / 10;
	}while(num > 0);
	
	len = i;
	
	while (i-- > 0)
	{
		*str++ = buf[i] + '0';
	}
	
	*str = '\0';
	
	return len;
}
/**************************************/
/*************验证检测*****************/
void Confirm(signed long num)
{
			if(num >= 1000000)
			{
						if(step == 0)              //当输入七位数时进入第一阶段（破解密码）
						{
							LongToString(PassWord1Str,password1);

							Buzz = 0;
							LED1 = 0;
							LED2 = 1;
							delay(1500);
							Buzz = 1;
							LED1 = 1;
							LED2 = 1;
							LCDShowStr(4,0,"*******");
							
							step = 1;
						}
						else if (step == 1)				//手动输入第二次的密码后判断
						{
										
										if(password1 == password2)
										{
											step = 2;
										}
										else 							//清空第二次密码  
										{
											password2 = 0;
											delay(500);
											LCDShowStr(4,0,"*******");
										}
						}
			}
}
/**************************************/
/************密码保存与显示*************/
void PwAction(unsigned char num)
{
	unsigned char len;
	unsigned char str[8];
	if(step == 0)											//第一次输入(初始密码)
	{
		password1 = password1 * 10 + num;
		len = LongToString(str,password1);
		
		LCDShowStr(11-len,0,str);
		
		Confirm(password1);
	}
	else if(step == 1)									//第二次输入
	{
		password2 = password2 * 10 + num;
		len = LongToString(str,password2);
		
		LCDShowStr(11-len,0,str);
		
		Confirm(password2);
	}
	
}
/**************************************/
/**************按键功能****************/
void KeyAction(unsigned char keycode)
{
		if(step == 0)
		{
			Buzz = 0;
			LED1 = 0;
			delay(40);														//按下按键滴滴声  =w=
			Buzz = 1;
			LED1 = 1;
		}
	
	if((keycode >= '0') && (keycode <= '9'))		//按下按键为数字键
	{
		PwAction(keycode - '0');
	}
	else if (keycode == 0x0D)										//清0按键
	{
		if(step == 0)
		{
			password1 = 0;
			LCDShowStr(4,0,"*******");
		}
		else if(step == 1) 
		{
			password2 = 0;
			LCDShowStr(4,0,"*******");
		}
		else if(step == 4)
		{
			step = 0;
			password1 = 0;
			password2 = 0;                        //游戏结束后按0全清
			Count = 1;
			Place = 0;
			Spa = 4615;
			LCDShowStr(4,0,"*******");
		}
	}
	else {}
}

/**********    按键驱动    ***********/
void KeyDrive ()
{
	static unsigned char pdata backup[4][3]={{1,1,1},{1,1,1},{1,1,1},{1,1,1}};
	unsigned char i,j;
	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
	{
		if(backup[i][j] != KeySta[i][j])				//
		{
			if(backup[i][j] != 0)
			{
				KeyAction(KeyCodeMap[i][j]);
			}
			backup[i][j] = KeySta[i][j];
		}
	}
}
/**************************************/
/**************************************/	

void interruptTime0 () interrupt 1
{

	
	TH0 = T0RH;
	TL0 = T0RL;
	if (step == 1)
	{
				/********************长按破译功能******************/
				
				
				if(KeySta[3][2] == 0)										
				{
					
					if((Count % Placems) == 0)
					{
						if((4+Place)<8)
							LCDXYConfig(4+Place,0);
						else
							LCDXYConfig(Place-4,1);
						LCDWriteDat(PassWord1Str[Place]); 				//破解进度
						Place++;
						if(Place >= 8)
						{
							step = 2;														//破解成功:结局2
						}
					}
				}
				/************************************************/
				
				if((Count % Spa) == 0)
				{
					Buzz = 0;
					LED1 = 0;
					delay(40);												//蜂鸣器与小灯闪烁
					Buzz = 1;
					LED1 = 1;
					if((Spa - 65) > 0)
					Spa -= 65;
				}
				
				if(Count >= 85000)
				{
					step = 3;												//时间到：结局3
				}
				Count ++; 
	}
	
	KeyScan();
}