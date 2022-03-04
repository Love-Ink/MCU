#ifndef HC595_Drive					//���û���ҵ������ǩ
#define HC595_Drive					//��ô�ʹ�һ�������ǩ
sbit HC595_DS=P2^2;					//74HC595�����ݽ�
sbit HC595_ST=P2^3;					//74HC595����ʾ���ƽ�
sbit HC595_SH=P2^4;					//74HC595��ʱ�ӽ�

unsigned char HC595_Write_Buffer[2];//74HC595оƬ�����ݻ���

void HC595_Init()					//74HC595��ʼ��IO��			
{
	HC595_DS=0;						
	HC595_ST=0;
	HC595_SH=0;
}

void HC595_Write_Data_Drive()		//74HC595 ���ݷ��ͺ���
{
	u8 i;							//����i ������λ
	for(i=0;i<8;i++)
	{
		HC595_SH=0;  				//ʱ������
		HC595_DS=HC595_Write_Buffer[1]&0x80;//�������λ����
		HC595_Write_Buffer[1]<<=1;	//��������
		HC595_SH=1;					//ʱ������
	}
	for(i=0;i<8;i++)
	{
		HC595_SH=0;  				//ʱ������
		HC595_DS=HC595_Write_Buffer[0]&0x80;//�������λ����
		HC595_Write_Buffer[0]<<=1;	//��������
		HC595_SH=1;					//ʱ������
	}
	HC595_ST=1;						//��ʾ���ƽ����� ��ʾ���
	HC595_DS=0;						//���ݽŹ�0
	HC595_ST=0;						//���ƽŹ�0
	HC595_SH=0;						//ʱ�ӽŹ�0
}
#endif