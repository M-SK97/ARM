#include "stm32f10x.h"
#include "delay.h"

/*
12=SER
13=Clock
14=latch
*/

void set();
void reset();
void latch();

void main()
{
	RCC ->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB ->CRH &= ~(GPIO_CRH_CNF12 | GPIO_CRH_CNF13 | GPIO_CRH_CNF14 | GPIO_CRH_MODE12 | GPIO_CRH_MODE13 | GPIO_CRH_MODE14);
	GPIOB ->CRH |= GPIO_CRH_MODE12_0 | GPIO_CRH_MODE13_0 | GPIO_CRH_MODE14_0;



	while(1)
	{
		set();
		set();
		latch();
		_delay_ms(1000);

		reset();
		reset();
		reset();
		reset();
		reset();
		reset();
		reset();
		reset();
		latch();
		_delay_ms(1000);
	}
}

void set()
{
	GPIOB ->BRR = GPIO_BRR_BR13;

	GPIOB ->BSRR = GPIO_BSRR_BS12;

	GPIOB ->BSRR = GPIO_BSRR_BS13;
}

void reset()
{
	GPIOB ->BRR = GPIO_BRR_BR13;

	GPIOB ->BSRR = GPIO_BSRR_BR12;

	GPIOB ->BSRR = GPIO_BSRR_BS13;
}

void latch()
{
	GPIOB ->BRR = GPIO_BRR_BR14;
	GPIOB ->BSRR = GPIO_BSRR_BS14;
	GPIOB ->BRR = GPIO_BRR_BR14;
}
