#ifndef __VARIABLE_H_
#define __VARIABLE_H_

sbit Buzz = P1^5;
sbit LED1 = P1^3;										
sbit LED2 = P1^4;

sbit PlaceKey = P3^1;   						 //破解密钥插口    请给低电平

unsigned char T0RH = 0;              //TH0
unsigned char T0RL = 0;							 //TL0
unsigned char step = 0;							 //环节     0：初始密码  1：破解密码   2：CT结局   3：T结局   
unsigned long password1 = 0;				 //初始密码
unsigned long password2 = 0;				 //破解密码
unsigned char PassWord1Str[8];			 //初始密码数组    用来显示破解进度
unsigned long Count = 1;						 //炸弹计时器
unsigned char Place = 0;						 //已破解位数
unsigned int Placems = 0; 					 //破解密码所需要的秒数
unsigned int Spa = 4615;             //炸弹启动后滴滴声间隔时间


unsigned char LongToString(unsigned char *str,unsigned long num);
void InitTime(unsigned int ms);
void KeyDrive ();
void delay(int ms);

#endif