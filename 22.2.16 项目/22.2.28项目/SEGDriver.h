#ifndef __SEGDRIVER_H
#define __SEGDRIVER_H

#include "reg52.h"
#include "intrins.h"
#define SEG P2
sbit SEG0 = P3^0;
sbit SEG1 = P3^1;
sbit SEG2 = P3^2;

void SEGShowNum(unsigned int num);

#endif
