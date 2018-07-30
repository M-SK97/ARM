#ifndef __SHIFT595_H
#define __SHIFT595_H

#include "stm32f10x.h"

void set();
void reset();
void latch();
void shift(uint8_t data);
void shift_init();

/*
PB12 = SER
PB13 = Clock
PB14 = latch
*/

#define controlPort		GPIOB
#define serialHigh		GPIO_BSRR_BS12
#define serialLow		GPIO_BSRR_BR12
#define clockHigh		GPIO_BSRR_BS13
#define clockLow		GPIO_BSRR_BR13
#define latchHigh		GPIO_BSRR_BS14
#define latchLow		GPIO_BSRR_BR14

void shift_init()
{
	RCC ->APB2ENR |= RCC_APB2ENR_IOPBEN;
	controlPort ->CRH &= ~(GPIO_CRH_CNF12 | GPIO_CRH_CNF13 | GPIO_CRH_CNF14 | GPIO_CRH_MODE12 | GPIO_CRH_MODE13 | GPIO_CRH_MODE14);
	controlPort ->CRH |= GPIO_CRH_MODE12_0 | GPIO_CRH_MODE13_0 | GPIO_CRH_MODE14_0;

}

void set()
{
	controlPort ->BSRR = clockLow;
	controlPort ->BSRR = serialHigh;
	controlPort ->BSRR = clockHigh;
	controlPort ->BSRR = clockLow;
}

void reset()
{
	controlPort ->BSRR = clockLow;
	controlPort ->BSRR = serialLow;
	controlPort ->BSRR = clockHigh;
	controlPort ->BSRR = clockLow;
}

void latch()
{
	controlPort ->BSRR = latchLow;
	controlPort ->BSRR = latchHigh;
	controlPort ->BSRR = latchLow;
}

void shift(uint8_t data)
{
	uint8_t i=0x80; //128 "bin = 1000 0000"
	while(i>=1)
	{
		if(data & i)
		{
			set();
		}
		else
		{
			reset();
		}
		i = i/2;
	}
	latch();
}

#endif
