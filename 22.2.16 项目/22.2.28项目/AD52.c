#include "AD52.h"

void AD_Init()
{
	P1ASF = 0x01;
	ADC_CONTR = ADC_POWER|ADC_SPEEDLL|ADC_START|ADC_CH;
			
	AUXR1 = 0x04;
	EADC = 1;
}
/*  内部AD初始化 
void interruptADC() interrupt 5 
{
	unsigned  ADC_num;
	ADC_CONTR &= !ADC_FLAG;
	ADC_num = (ADC_RES<<8)|ADC_RESL;
	
	ADC_Vin = (unsigned int)(((float)ADC_num * 506)/1024);
	ADC_CONTR = ADC_POWER|ADC_SPEEDLL|ADC_START|ADC_CH;
}
*/
