#include "stm32f10x.h"
#include "delay.h"
#include "LCD595.h"



void main()
{
	LCD_Init();


	while(1)
	{
		LCD_Test();
	}
}
