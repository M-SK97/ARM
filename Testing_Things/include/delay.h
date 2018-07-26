#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void DelayInit(void);
void _delay_us(uint32_t us);
void _delay_ms(uint32_t ms);


void _delay_us(uint32_t us)
{
	volatile unsigned int i = 1.137*us;
	while(i--);
}

void _delay_ms(uint32_t ms)
{
	_delay_us(ms*1000);
}
#endif
