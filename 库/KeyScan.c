#include <KeyScan.h>

unsigned char pdata KeySta[4][4]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
unsigned int code KeyCodeMap[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};

void KeyAction(unsigned int Code)
{
	if(Code == 1)
	{
		led = 0;
	}
	else if (Code == 2)
	{
		led = 1;
	}
	else
	{;}
}
void KeyDrive()
{
	unsigned char i,j;
	static unsigned  char pdata Keybackup[4][4]={
	{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
	
	
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(Keybackup[i][j]!=KeySta[i][j])
			{
				if(Keybackup[i][j] != 0)
				{
					KeyAction(KeyCodeMap[i][j]);
				}
				Keybackup[i][j] = KeySta[i][j];
			}
		}
}
void KeyScan()
{
	static unsigned char keyin = 0;
	unsigned char i;
	static unsigned char keybuf[4][4]={
	{0xFF,0xFF,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF},};
	
	keybuf[keyin][0]=(keybuf[keyin][0]<< 1) | KEY_OUT_1;
	keybuf[keyin][1]=(keybuf[keyin][1]<< 1) | KEY_OUT_2;
	keybuf[keyin][2]=(keybuf[keyin][2]<< 1) | KEY_OUT_3;
	keybuf[keyin][3]=(keybuf[keyin][3]<< 1) | KEY_OUT_4;
	
	for(i=0;i<4;i++)
	{
		if((keybuf[keyin][i] & 0x0F) == 0x00)
		{
			KeySta[keyin][i] = 0;
		}
		else if((keybuf[keyin][i] & 0x0F) == 0x0F)
		{
			KeySta[keyin][i] = 1;
		}
	}
	
	keyin++;
	keyin &= 0x03;
	
	switch(keyin)
	{
		case 0:KEY_IN_4 = 1;KEY_IN_1 = 0;break;
		case 1:KEY_IN_1 = 1;KEY_IN_2 = 0;break;
		case 2:KEY_IN_2 = 1;KEY_IN_3 = 0;break;
		case 3:KEY_IN_3 = 1;KEY_IN_4 = 0;break;
	}
}