#include <EEPROM52.h>

void LongToStr(unsigned int num,unsigned char *str)
{
	unsigned char dat[5];
	char i;
	for(i=0;i<3;i++)
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
	TR0=0;
	IAP_ADDRL = addrs;
	IAP_ADDRH = (addrs >> 8);
	IAP_CONTR = 0x03;
	IAP_CONTR |= 0x80;
	IAP_CMD = 0x03;
	IAP_TRIG = 0x5A;
	IAP_TRIG = 0xA5;
	_nop_();
	IAPIdle();
	TR0=1;
}

unsigned char eeprom_read(unsigned int addrs)
{
	unsigned char dat;
	TR0 = 0;
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
	TR0 = 1;
	return dat;
}

void eeprom_write(unsigned int addrs,unsigned char dat)
{
	TR0 = 0;
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
	TR0 = 1;
}
