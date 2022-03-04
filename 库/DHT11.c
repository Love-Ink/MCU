#include "DHT11.h"

void delayms(unsigned int z)
{
	unsigned char i,j;
	for(i=z;i>0;i--)
		for(j=250;j>0;j--)
		{
			_nop_();
			_nop_();
			_nop_();
			_nop_();
		}
}
void delayus(unsigned char us)
{
	while(--us);
}
unsigned char DHT11_byte()
{
	unsigned char Data=0,i;
	for(i=0;i<8;i++)
	{
		while(!DHT11_DATA);
		delayus(100);
		Data <<=1;
		if(DHT11_DATA == 1)
             	Data += 1;
		while(DHT11_DATA);
	}
	return Data;
}
void DHT11_Start()
{
	DHT11_DATA = 1;
	delayus(30);
	DHT11_DATA = 0;
	delayms(45);
	DHT11_DATA = 1;
	delayus(360);
}
void DHT11_Read(unsigned char *str)
{
	unsigned char R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise;
	static unsigned int num = 0;
	DHT11_Start();
	
	if(DHT11_DATA == 0)
	{
		
		while(DHT11_DATA == 0);
		delayus(500);
		R_H = DHT11_byte();
		R_L = DHT11_byte();
		T_H = DHT11_byte();
		T_L = DHT11_byte();
		revise = DHT11_byte();
		
		delayus(300);
		
		if((R_H+R_L+T_H+T_L) == revise)
		{
			RH = R_H;
			RL = R_L;
			TH = T_H;
			TL = T_L;
		}
		num ++;
		*str++ =RH/10+'0';
        *str++ =(RH%10)+'0';
		*str++ ='%';
        *str++ ='R';
        *str++ ='H';
        *str++ =' ';
		*str++ =' ';
        *str++ =(TH/10)+'0';
        *str++ =(TH%10)+'0';
		*str++ ='^';
        *str++ ='C';
		*str++ = ' ';
		*str++ = num/100 + '0';
		*str++ = (num/10)%10 + '0';
		*str++ = num%10 + '0';
		*str ='\0';
		
		LCDShowStr(14,1,"OK!");	
		//LCDShowStr(x,y,rec_dat);
	}
	
}