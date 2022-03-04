#include "BSP_ws2812.h"

uchar RGB_BUF[24];

void send_A_bit (uchar VAL) 
{
	if(VAL==1)
	{
		P55=1;
		_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();
		P55=0;
	}
	else
	{
		P55=1;
		_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();
		_nop_();_nop_();
		P55=0;
	}
}

void send_24_Bit (struct RGB RGB_VAL){     // 给ws2812发送 24 位数据
	uchar i=0;
	TR0 = 0;
	while(i!=8){
		RGB_BUF[i]= (RGB_VAL.G_VAL>>i&0x01);
		i++;
	}
	while(i!=16){
		RGB_BUF[i]= (RGB_VAL.R_VAL>>(i-8)&0x01);
		i++;
	}
	while(i!=24){
		RGB_BUF[i]= (RGB_VAL.B_VAL>>(i-16)&0x01);
		i++;
	}
	i=0;
	while(i!=24){
		send_A_bit(RGB_BUF[i]);
		i++;
	}
	TR0 = 1;
}

