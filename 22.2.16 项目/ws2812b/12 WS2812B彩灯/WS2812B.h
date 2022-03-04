#ifndef WS2812B_Drive		//如果没有找到这个标签
#define WS2812B_Drive		//那么就打一个这个标签
sbit WS2812_GPIO=P2^0;
u8 data WS2812_Write_Buffer[25];
void WS2812_Write_Data(u8 *Point,u8 len)
{
	u8 data i,j,k;
	u8 bdata Value;
	for(i=0;i<len;i++)
	{
		for(j=0;j<3;j++)
		{
			switch(j)
			{
				case 0:Value=*(Point+1);break;
				case 1:Value=*(Point);break;
				case 2:Value=*(Point+2);break;			
			}
			k=0x80;
			while(k)
			{
				if(Value&k)
				{
					WS2812_GPIO=1;
				}
				WS2812_GPIO=1;
				WS2812_GPIO=0;
				k>>=1;
			}
		}
		Point+=3;
	}
}
void WS2812_Display_Ser()
{
	static xdata u8 count=0;
	if(count<100)
	{
		WS2812_GPIO=0;
		count++;
	}
	else
	{
		EA=0;
		WS2812_Write_Data(WS2812_Write_Buffer+1,8);
		EA=1;
		count=0;
	}
}
#endif