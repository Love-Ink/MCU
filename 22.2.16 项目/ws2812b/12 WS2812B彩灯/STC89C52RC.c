//************************************************************************************
// WS2812Bȫ��ʵ����Զ���ɫ+�������ʾ��������
//************************************************************************************
#include "STC89.H"	//ͷ�ļ�����
#include <intrins.h>				//ͷ�ļ�����
typedef unsigned char u8;			//���¶�������������
typedef unsigned short u16;			//���¶�������������
typedef unsigned long u32;			//���¶�������������	
#include <HC595.H>					//����74HC595�ĵײ������ļ�������д���
#include <SMG_Ser.H>				//��������ܵ��ļ�������д���
#include <WS2812B.H>				

void SMG_Allot()					//����ܵ����ݷ���
{
	static u16 xdata count;			//��̬����		
	count++;				
	if(count>1000)					//ÿ200�ν���ִ��һ��
	{
		count=0;
		SMG_Write_Buffer[0]=WS2812_Write_Buffer[1]/16;	//��1λ�������ʾ����
		SMG_Write_Buffer[1]=WS2812_Write_Buffer[1]%16;	//��2λ�������ʾ����
		SMG_Write_Buffer[2]=16;							//��3λ�������ʾ����
		SMG_Write_Buffer[3]=WS2812_Write_Buffer[2]/16;	//��4λ�������ʾ����
		SMG_Write_Buffer[4]=WS2812_Write_Buffer[2]%16;	//��5λ�������ʾ����
		SMG_Write_Buffer[5]=16;	//��6λ�������ʾ����
		SMG_Write_Buffer[6]=WS2812_Write_Buffer[3]/16;	//��7λ�������ʾ����
		SMG_Write_Buffer[7]=WS2812_Write_Buffer[3]%16;	//��8λ�������ʾ����
	}
	SMG_Display_Ser();				//ִ���������ʾ����
}
//****************************************************************************
// ����״̬��״̬����Ƶ���ݸ�WS2812�Ļ������顣��ִ��WS2812�����ݷ���
//****************************************************************************
void WS2812_Allot()
{
	static u8 xdata blue_pwm,red_pwm,green_pwm,change_mode=0;
	static u16 i=0,count=0;
	if(count>80)				//count���ٶȿ��ơ�
	{
		count=0;
		switch(change_mode)
		{
			case 0:	red_pwm++;				//��ƽ�������
					green_pwm=0;
					blue_pwm=0;
					if(red_pwm==255)		
					{
						change_mode=1;		//��������ˣ�����1
					}
					break;
			case 1:	red_pwm--;				//��ƽ������
					green_pwm=0;
					blue_pwm=0;
					if(red_pwm==0)
					{
						change_mode=2;		//��ƺ��ˣ�����2	
					}
					break;
			case 2:	red_pwm=0;				
					green_pwm++;			//�̵ƽ�������
					blue_pwm=0;
					if(green_pwm==255)
					{
						change_mode=3;		//�̵������ˣ�����3
					}
					break;
			case 3:	red_pwm=0;
					green_pwm--;			//�̵ƽ������
					blue_pwm=0;
					if(green_pwm==0)
					{
						change_mode=4;		//�̵ƺ��ˣ�����4
					}
					break;	
			case 4:	red_pwm=0;
					green_pwm=0;
					blue_pwm++;				//���ƽ�������
					if(blue_pwm==255)
					{
						change_mode=5;		//���������ˣ�����5
					}
					break;
			case 5:	red_pwm=0;
					green_pwm=0;
					blue_pwm--;				//���ƽ������
					if(blue_pwm==0)
					{
						change_mode=0;		//���ƺ��ˣ����ص�0
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
void main()							//������
{
	//HC595_Init();					//��ʼ��74HC595�ܽ�
	while(1)						//��������ѭ��
	{
		//SMG_Allot();				//ѭ��������������ݷ��亯��
		WS2812_Allot();
	}
}