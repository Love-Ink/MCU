#include "reg52.h"
#include "intrins.h"
#include "AD52.h"
#include "LCDDriver.h"
#include "EEPROM52.h"
#include "SEGDriver.h"

#define count 7
sbit IN = P1^1;

unsigned int ADC_Vin;
unsigned char ADC_Str[5];
unsigned char num_str[4];
unsigned char demo=0;
void main(){
	//unsigned int sum;
	AD_Init();
	LCD_Init();
	
	TMOD = 0x01;
	TH0 = 0xEE;
	TL0 = 0x00;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	
	eeprom_write(0x000,count&0xff);
	eeprom_write(0x200,count>>8);

//	sum = eeprom_read(0x200)<<8|eeprom_read(0x000);
//	LongToStr(sum,num_str);
	
	LCDShowStr(13,0,"ADC");
	while(1){
		LCDShowStr(0,0,"ADDRS:0x000");
		LCDShowStr(0,1,"READ:");
		LongToStr(eeprom_read(0x000),num_str);
		LCDShowStr(6,1,num_str);
		if(IN){LCDShowStr(10,1,"1");}else {LCDShowStr(10,1,"0");}
		LongToStr(ADC_Vin,num_str);
		LCDShowStr(13,1,num_str);
		demo ++;
		delay(500);
		LCDShowStr(0,0,"ADDRS:0x200");
		LCDShowStr(0,1,"READ:");
		LongToStr(eeprom_read(0x200),num_str);
		LCDShowStr(6,1,num_str);
		if(IN){LCDShowStr(10,1,"1");}else {LCDShowStr(10,1,"0");}
		LongToStr(ADC_Vin,num_str);
		LCDShowStr(13,1,num_str);
		demo ++;
		delay(500);
		
		
	}
}
void interruptTime0 () interrupt 1
{
	TH0 = 0xEE;
	TL0 = 0x00;
	if(demo>9)demo = 0;
	SEGShowNum(demo);
}

void interruptADC() interrupt 5 
{
	unsigned  ADC_num;
	ADC_CONTR &= !ADC_FLAG;
	ADC_num = (ADC_RES<<8)|ADC_RESL;
	
	ADC_Vin = (unsigned int)(((float)ADC_num * 506)/1024);
	ADC_CONTR = ADC_POWER|ADC_SPEEDLL|ADC_START|ADC_CH;
}
