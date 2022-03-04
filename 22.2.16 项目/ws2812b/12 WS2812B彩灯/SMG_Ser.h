#ifndef SMG_Ser					//���û���ҵ������ǩ		
#define SMG_Ser					//��ô�ʹ�һ�������ǩ

u8 xdata SMG_Write_Buffer[8];	//��λ����ܵ��Դ�
u8 code SMG_Duan_Buffer[18]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xff,~0X40};
u8 code SMG_Wei_Buffer[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void SMG_Display_Ser()			//�������ʾˢ�º���
{
	static u8 count=0;			//countȡֵ��Χ��0~7��ÿ����ʾһλ�����
	switch(count)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		HC595_Write_Buffer[0]=SMG_Duan_Buffer[SMG_Write_Buffer[count]];
		//ͨ���������ʾ����0~7��ֵ�����������duan���ֵ������74HC595���Դ�0������0#595оƬ
		HC595_Write_Buffer[1]=SMG_Wei_Buffer[count];
		//ͨ��count�����������wei���ֵ������74HC595���Դ�1������1#595оƬ
		HC595_Write_Data_Drive();//ִ��595���ݵķ���
		break;
	}
	count++;
	count=count%8;//����count��ֵ��ȡֵ��Χ��0~7��	
}
#endif 