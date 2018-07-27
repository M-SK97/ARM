#include "stm32f10x.h"
#include "delay.h"
#include "LCD16x2_4bit.h"


void main()
{

	LCD_Init();

	while(1)
	{
		LCD_Test();
	}
}
