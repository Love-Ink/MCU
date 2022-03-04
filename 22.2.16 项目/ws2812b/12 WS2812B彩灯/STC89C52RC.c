//************************************************************************************
// WS2812B全真彩灯珠自动变色+数码管显示灯珠亮度
//************************************************************************************
#include "STC89.H"	//头文件包含
#include <intrins.h>				//头文件包含
typedef unsigned char u8;			//重新定义数据类型名
typedef unsigned short u16;			//重新定义数据类型名
typedef unsigned long u32;			//重新定义数据类型名	
#include <HC595.H>					//调用74HC595的底层驱动文件（必须写这里）
#include <SMG_Ser.H>				//调用数码管的文件（必须写这里）
#include <WS2812B.H>				

void SMG_Allot()					//数码管的数据分配
{
	static u16 xdata count;			//静态变量		
	count++;				
	if(count>1000)					//每200次进来执行一次
	{
		count=0;
		SMG_Write_Buffer[0]=WS2812_Write_Buffer[1]/16;	//第1位数码管显示内容
		SMG_Write_Buffer[1]=WS2812_Write_Buffer[1]%16;	//第2位数码管显示内容
		SMG_Write_Buffer[2]=16;							//第3位数码管显示内容
		SMG_Write_Buffer[3]=WS2812_Write_Buffer[2]/16;	//第4位数码管显示内容
		SMG_Write_Buffer[4]=WS2812_Write_Buffer[2]%16;	//第5位数码管显示内容
		SMG_Write_Buffer[5]=16;	//第6位数码管显示内容
		SMG_Write_Buffer[6]=WS2812_Write_Buffer[3]/16;	//第7位数码管显示内容
		SMG_Write_Buffer[7]=WS2812_Write_Buffer[3]%16;	//第8位数码管显示内容
	}
	SMG_Display_Ser();				//执行数码管显示函数
}
//****************************************************************************
// 根据状态机状态，分频数据给WS2812的缓存数组。并执行WS2812的数据发送
//****************************************************************************
void WS2812_Allot()
{
	static u8 xdata blue_pwm,red_pwm,green_pwm,change_mode=0;
	static u16 i=0,count=0;
	if(count>80)				//count是速度控制。
	{
		count=0;
		switch(change_mode)
		{
			case 0:	red_pwm++;				//红灯渐渐亮起
					green_pwm=0;
					blue_pwm=0;
					if(red_pwm==255)		
					{
						change_mode=1;		//红灯最亮了，进入1
					}
					break;
			case 1:	red_pwm--;				//红灯渐渐灭掉
					green_pwm=0;
					blue_pwm=0;
					if(red_pwm==0)
					{
						change_mode=2;		//红灯黑了，进入2	
					}
					break;
			case 2:	red_pwm=0;				
					green_pwm++;			//绿灯渐渐亮起
					blue_pwm=0;
					if(green_pwm==255)
					{
						change_mode=3;		//绿灯最亮了，进入3
					}
					break;
			case 3:	red_pwm=0;
					green_pwm--;			//绿灯渐渐灭掉
					blue_pwm=0;
					if(green_pwm==0)
					{
						change_mode=4;		//绿灯黑了，进入4
					}
					break;	
			case 4:	red_pwm=0;
					green_pwm=0;
					blue_pwm++;				//蓝灯渐渐亮起
					if(blue_pwm==255)
					{
						change_mode=5;		//蓝灯最亮了，进入5
					}
					break;
			case 5:	red_pwm=0;
					green_pwm=0;
					blue_pwm--;				//蓝灯渐渐灭掉
					if(blue_pwm==0)
					{
						change_mode=0;		//蓝灯黑了，返回到0
					}
					break;									
		}
	}
	count++;
	i=i%24;	
	WS2812_Write_Buffer[i+1]=red_pwm;
	WS2812_Write_Buffer[i+2]=green_pwm; 
	WS2812_Write_Buffer[i+3]=blue_pwm;
	i+=3;
	WS2812_Display_Ser();
}
void main()							//主函数
{
	//HC595_Init();					//初始化74HC595管脚
	while(1)						//主函数大循环
	{
		//SMG_Allot();				//循环调用数码管数据分配函数
		WS2812_Allot();
	}
}