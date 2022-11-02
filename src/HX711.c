#include <HX711.h>
#include <LCDDriver.h>
void LongToStr(unsigned int num,unsigned char *str)
{
	unsigned char dat[5];
	char i;
	for(i=0;i<4;i++)
	{
		dat[i] = num%10;
		num /= 10;
	}
	i--;
	for(;i>=0;i--)
	{
		*str++ = dat[i] + '0';
	}
	*str = '\0';
}
void HX711_delay(void)
{
	_nop_();
	_nop_();
}
void HX711_Read(unsigned char *str)
{
	/*unsigned char i;
	unsigned long AD_dat = 0;
	unsigned int Weight_dat;
	
	HX711_DT = 1;
	HX711_delay(2);
	HX711_SCK = 0;
	while(HX711_DT);
	LCDShowStr(0,3,"OK!");
	for(i=0;i<24;i++)
	{
		HX711_SCK = 1;
		AD_dat = (AD_dat<<1)|HX711_DT;
		HX711_delay(2);
		HX711_SCK = 0;
		HX711_delay(2);
	}
	HX711_SCK = 1;
	delay(1);
	HX711_SCK = 0;
	
	Weight_dat =(unsigned int)((float)(AD_dat * 10)/5.0);
	LongToStr(Weight_dat,str);*/
	
	unsigned long count;
	unsigned int Weight_dat;
	unsigned char i;
	HX711_DOUT = 1;
	HX711_delay();
	HX711_SCK = 0;
	count = 0;
	while(HX711_DOUT);
	LCDShowStr(0,3,"OK!");
	for(i=0;i<24;i++)
	{
		HX711_SCK = 1;
		count = count<<1;
		HX711_SCK = 0;
		if(HX711_DOUT)
			count++;
	}
	HX711_SCK = 1;
	count = count ^ 0x800000;
	HX711_delay();
	HX711_SCK = 0;
	Weight_dat =(unsigned int)((float)(count * 10)/9000);
	LongToStr(Weight_dat,str);
}
