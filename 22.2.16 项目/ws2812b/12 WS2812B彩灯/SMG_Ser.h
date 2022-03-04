#ifndef SMG_Ser					//如果没有找到这个标签		
#define SMG_Ser					//那么就打一个这个标签

u8 xdata SMG_Write_Buffer[8];	//八位数码管的显存
u8 code SMG_Duan_Buffer[18]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xff,~0X40};
u8 code SMG_Wei_Buffer[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void SMG_Display_Ser()			//数码管显示刷新函数
{
	static u8 count=0;			//count取值范围是0~7，每次显示一位数码管
	switch(count)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		HC595_Write_Buffer[0]=SMG_Duan_Buffer[SMG_Write_Buffer[count]];
		//通过数码管显示缓存0~7的值，查找数码管duan码的值，送人74HC595的显存0，送入0#595芯片
		HC595_Write_Buffer[1]=SMG_Wei_Buffer[count];
		//通过count，查找数码管wei码的值，送人74HC595的显存1，送入1#595芯片
		HC595_Write_Data_Drive();//执行595数据的发送
		break;
	}
	count++;
	count=count%8;//限制count的值，取值范围是0~7；	
}
#endif 