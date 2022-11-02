#ifndef __EEPROM52_H
#define __EEPROM52_H

#include <reg52.h>
#include <intrins.h>

sfr IAP_DATA = 0xC2;
sfr IAP_ADDRH = 0xC3;
sfr IAP_ADDRL = 0xC4;
sfr IAP_CMD = 0xC5;
sfr IAP_TRIG = 0xC6;
sfr IAP_CONTR = 0xC7;

void IAPIdle(void);
void eeprom_init (void);
void eeprom_eares(unsigned int addrs);
unsigned char eeprom_read(unsigned int addrs);
void eeprom_write(unsigned int addrs,unsigned char dat);
void LongToStr(unsigned int num,unsigned char *str);

#endif
