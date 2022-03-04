#include <EEPROM52.h>

void LongToStr(unsigned int num,unsigned char *str)
{
	unsigned char dat[5];
	char i;
	for(i=0;i<4;i++)
	{
		dat[i] = num%10;
		num /= 10;
	}
	i--;
	for(;i>=0;i--)
	{
		*str++ = dat[i] + '0';
	}
	*str = '\0';
}

void IAPIdle(void)
{
	IAP_CONTR = 0;
	IAP_CMD = 0;
	IAP_TRIG = 0;
	IAP_ADDRH = 0x80;
	IAP_ADDRL = 0;
	IAP_DATA = 0;
}


void eeprom_eares(unsigned int addrs)
{
	IAP_ADDRL = addrs;
	IAP_ADDRH = (addrs >> 8);
	IAP_CONTR = 0x03;
	IAP_CONTR |= 0x80;
	IAP_CMD = 0x03;
	IAP_TRIG = 0x5A;
	IAP_TRIG = 0xA5;
	_nop_();
	IAPIdle();
}

unsigned char eeprom_read(unsigned int addrs)
{
	unsigned char dat;
	IAP_ADDRL = addrs;
	IAP_ADDRH = (addrs >> 8);
	IAP_CONTR = 0x03;
	IAP_CONTR |= 0x80;
	IAP_CMD = 0x01;
	IAP_TRIG = 0x5A;
	IAP_TRIG = 0xA5;
	_nop_();
	dat = IAP_DATA;
	IAPIdle();
	return dat;
}

void eeprom_write(unsigned int addrs,unsigned char dat)
{
	eeprom_eares(addrs);
	IAP_DATA = dat;
	IAP_ADDRL = addrs;
	IAP_ADDRH = addrs >> 8;
	IAP_CONTR = 0x03;
	IAP_CONTR |= 0x80;
	IAP_CMD = 0x02;
	IAP_TRIG = 0x5A;
	IAP_TRIG = 0xA5;
	_nop_();
	IAPIdle();
}

void eeprom_init (void)
{
	unsigned char a;
	a = eeprom_read(0x200);
	if(a != 1)
	{
		eeprom_eares(0x000);
		eeprom_eares(0x200);
		eeprom_write(0x000,0x01);
		eeprom_write(0x200,0x01);
	}
	
}