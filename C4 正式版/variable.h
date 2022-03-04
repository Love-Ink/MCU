#ifndef __VARIABLE_H_
#define __VARIABLE_H_

sbit Buzz = P1^5;
sbit LED1 = P1^3;										
sbit LED2 = P1^4;

sbit PlaceKey = P3^1;   						 //�ƽ���Կ���    ����͵�ƽ

unsigned char T0RH = 0;              //TH0
unsigned char T0RL = 0;							 //TL0
unsigned char step = 0;							 //����     0����ʼ����  1���ƽ�����   2��CT���   3��T���   
unsigned long password1 = 0;				 //��ʼ����
unsigned long password2 = 0;				 //�ƽ�����
unsigned char PassWord1Str[8];			 //��ʼ��������    ������ʾ�ƽ����
unsigned long Count = 1;						 //ը����ʱ��
unsigned char Place = 0;						 //���ƽ�λ��
unsigned int Placems = 0; 					 //�ƽ���������Ҫ������
unsigned int Spa = 4615;             //ը��������ε������ʱ��


unsigned char LongToString(unsigned char *str,unsigned long num);
void InitTime(unsigned int ms);
void KeyDrive ();
void delay(int ms);

#endif