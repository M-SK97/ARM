#include "stm32f10x.h"
#include "delay.h"
#include "shift595.h"



void main()
{
	shift_init();

	shift(0);

	while(1)
	{
		uint8_t i = 1;

		while(i<=0b00010000)
		{
			shift(i);

			i = i*2;

			_delay_ms(100);
		}

		i = 0b00001000;

		while(i>0b00000001)
		{
			shift(i);

			i = i/2;

			_delay_ms(100);
		}
	}
}
