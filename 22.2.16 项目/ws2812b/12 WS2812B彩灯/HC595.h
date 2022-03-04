#ifndef HC595_Drive					//如果没有找到这个标签
#define HC595_Drive					//那么就打一个这个标签
sbit HC595_DS=P2^2;					//74HC595的数据脚
sbit HC595_ST=P2^3;					//74HC595的显示控制脚
sbit HC595_SH=P2^4;					//74HC595的时钟脚

unsigned char HC595_Write_Buffer[2];//74HC595芯片的数据缓存

void HC595_Init()					//74HC595初始化IO口			
{
	HC595_DS=0;						
	HC595_ST=0;
	HC595_SH=0;
}

void HC595_Write_Data_Drive()		//74HC595 数据发送函数
{
	u8 i;							//变量i 用于移位
	for(i=0;i<8;i++)
	{
		HC595_SH=0;  				//时钟拉低
		HC595_DS=HC595_Write_Buffer[1]&0x80;//数据最高位拷贝
		HC595_Write_Buffer[1]<<=1;	//数据左移
		HC595_SH=1;					//时钟拉低
	}
	for(i=0;i<8;i++)
	{
		HC595_SH=0;  				//时钟拉低
		HC595_DS=HC595_Write_Buffer[0]&0x80;//数据最高位拷贝
		HC595_Write_Buffer[0]<<=1;	//数据左移
		HC595_SH=1;					//时钟拉低
	}
	HC595_ST=1;						//显示控制脚拉高 显示输出
	HC595_DS=0;						//数据脚归0
	HC595_ST=0;						//控制脚归0
	HC595_SH=0;						//时钟脚归0
}
#endif