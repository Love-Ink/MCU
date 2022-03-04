#include "STC8G.H"
#include "intrins.h"
#include "BSP_ws2812.h"

sbit KEY_IN = P5^4;

#define uchar unsigned char 

unsigned long pow (int a,int b);

void Delay10ms();
void Delay2ms();

void Demo ();
int readPwmTime ();

uchar KEYBuff=0,KEYBufBack=0;
uchar flag = 1;
uchar x=0,j=0;
bit mode = 0;
unsigned long LEDBuff=0xffffffff;

int main(void) {
	uchar i;
	
	struct RGB BLACK,RED,GREEN;

	BLACK.G_VAL = 0x00;  //黑色色彩结构体
	BLACK.R_VAL = 0x00;
	BLACK.B_VAL = 0x00;

	GREEN.G_VAL = 0xFF;	//绿色色彩结构体
	GREEN.R_VAL = 0x00;
	GREEN.B_VAL = 0x00;

	RED.G_VAL = 0x00;		//红色色彩结构体
	RED.R_VAL = 0x5F;
	RED.B_VAL = 0x00;
	
	P5M0 = 0x00;				//配置P5 为输入输出双向模式
	P5M1 = 0x00;				//配置P5 为输入输出双向模式
	
	TMOD = 0x11;				//配置计数器 TR0,TR1为模式1  16位计数器
	TH0 = 0x0B;					//TR0 高位 初始值
  TL0 = 0xDC;					//TR0 低位 初始值
  TH1 = 0x00;					//TR1 高位 初始值
  TL1 = 0x00;					//TR1 低位 初始值
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	
	while(1){
		Demo();
		while(i!=32){         //连续对三十二个灯写入数据
			if((LEDBuff>>i)&0x01==1){
				send_24_Bit(RED);
			}else{
				send_24_Bit(BLACK);
			}
			i++;
		}
		i=0;
		P55 = 0;
		if (flag!=4){
			Delay10ms();       //加速堆叠效果
		}else{
			Delay2ms();
		}
	}
}

void interruptTime0 () interrupt 1{
	static uchar count25ms = 0;
	TH0 = 0x0B;
  TL0 = 0xDC;
	if(count25ms >= 20){
		count25ms=0;
		if(readPwmTime() > 0x0EA6){    //检测PWM信号高电平宽度是否大于 1.5ms
				KEYBuff = 1;
		}else {
				KEYBuff = 0;
		}
	}
	
	if(KEYBuff != KEYBufBack){
		mode = !mode;
		KEYBufBack = KEYBuff;
	}
	
	count25ms++;
	
}




void Demo (){ // 流水灯位移计算
	
	if(mode==1){
	if(flag == 1){
			LEDBuff >>= 1;
			if(LEDBuff == 0x001){
					flag = 2;
			}
	}else if(flag == 2){
		LEDBuff = ((LEDBuff&0x80000000)>>9)|((LEDBuff<<1)&0xffffffff);
		if(LEDBuff == 0x80000000)
			flag = 3;
	}	else if (flag == 3){
		LEDBuff = ((LEDBuff&0x001)<<9)|((LEDBuff>>1)&0xffffffff);
		if (LEDBuff == 0x001)
			flag = 4;
	}else if(flag == 4) {
		LEDBuff -= 2147483648/(pow(2,j));
		j++;
		if(j == (31-x)){
				j = 0;
				x++;
			}
		if(x==31){
			flag = 5;x=0;}
	}else if(flag == 5){
		LEDBuff <<= 1;
		if((LEDBuff&0xffffffff) == 0x80000000){
			flag = 6;LEDBuff=0xC0000000;}
	}else if(flag == 6){
		LEDBuff >>= 1;
		LEDBuff += 0x80000000;
		if((LEDBuff&0xffffffff) == 0xffffffff){
			 flag=1;
			mode = 0;
		}
	}
	}else{
		LEDBuff = 0xffffffff;
    flag = 1;
    x=0;
    j = 0;
	}
	LEDBuff &= 0xffffffff;
	
}
unsigned long pow (int a,int b){
	unsigned long pow=a;
	if(b==0){
		return 1;
	} else if (b==1) {
		return a;
	}
	for(;b>1;b--){
		pow *= a;
	}
	return pow;
}

void Delay10ms(){     //10ms延时
	unsigned char i, j, k;

	i = 2;
	j = 134;
	k = 152;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay2ms()	{    //2ms延时
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 78;
	j = 233;
	do
	{
		while (--j);
	} while (--i);
}

int readPwmTime (){
		int PwmTime;
			while(KEY_IN == 1);
			while(KEY_IN == 0);
			TR1 = 1;
			while(KEY_IN == 1);
			TR1 = 0;
			PwmTime = (TH1 << 8)|TL1;
			TH1 = 0x00;
			TL1 = 0x00;
		return PwmTime;
}
