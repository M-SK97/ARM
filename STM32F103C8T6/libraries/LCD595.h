#ifndef __LCD595_H
#define __LCD595_H

#include "stm32f10x.h"
#include "delay.h"
#include "shift595.h"
#include <stdio.h>

#define LCDPort				Reg
#define Enable				3
#define ReadWrite			2
#define RegisterSelect			1

void LCD_Init (void);
void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
void LCD_print(const char myString[]);
void LCD_clear(void);
void LCD_shift_to_left(int steps, int Time);
void LCD_shift_to_right(int steps, int Time);
void cursor_shift_to_left(int steps, int Time);
void cursor_shift_to_right(int steps, int Time);
void Delay_ms(int Time);
void LCD_home(void);
void cursor_entry_shift_to_left(int steps);
void cursor_entry_shift_to_right(int steps);
void LCD_entry_shift_to_left(int steps);
void LCD_entry_shift_to_right(int steps);
void LCD_set_DDRAM_address(int pos);
void LCD_first_line(void);
void LCD_second_line(void);
void LCD_go_to_location(uint8_t x, uint8_t y);
void LCD_print_ToLocation(uint8_t x, uint8_t y, const char myString[]);
void LCD_printInt_toLocation(uint8_t x, uint8_t y, int value, int nOfDigits, bool spacing, char base);
void LCD_printDouble_toLocation(uint8_t x, uint8_t y, float value, int nOfDigits, int prec, bool spacing);
void LCD_Test();

void LCD_Init ()  /* LCD Initialize function */
{
	shift_init();
	shift(0);

	_delay_ms(20);		/* LCD Power ON delay always >15ms */

	LCD_Command(0x01); // clear the LCD.
	_delay_ms(2);

	LCD_Command(0x33);
	LCD_Command(0b00110010);	/* Send for 4 bit initialization of LCD  */
	LCD_Command(0b00101000);	/* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0b00001100);	/* Display on cursor off */
	LCD_Command(0x06);	/* Increment cursor (shift cursor to right) */
	LCD_Command(0x01); // clear the LCD.
	_delay_ms(2);
}

void LCD_Command( unsigned char cmnd )
{
		//      1110 1010

		shift((LCDPort & 0x0F) | (cmnd & 0xF0));

		shift(LCDPort & ~(1<<RegisterSelect)); //not RS
		shift(LCDPort | 1<<Enable);
		_delay_us(1);
		shift(LCDPort & ~(1<<Enable));
		//_delay_ms(200);

		shift((LCDPort & 0x0F) | (cmnd << 4));


		shift(LCDPort | 1<<Enable);
		_delay_us(1);
		shift(LCDPort & ~(1<<Enable));
		_delay_us(2);
}

void LCD_Char(unsigned char data)
{
	//0b00000000
	shift((LCDPort & 0x0F) | (data & 0xF0));

	shift(LCDPort | 1<<RegisterSelect); // RS
	shift(LCDPort | 1<<Enable);
	_delay_us(1);
	shift(LCDPort & ~(1<<Enable));
	//_delay_us(200);

	shift((LCDPort & 0x0F) | (data << 4));


	shift(LCDPort | 1<<Enable);
	_delay_us(1);
	shift(LCDPort & ~(1<<Enable));
	_delay_us(2);
}

void LCD_print(const char myString[])
{
	uint8_t i = 0;

	while(myString[i])
	{
		LCD_Char(myString[i]);
		//_delay_us(40);

		i++;
	}
}

void LCD_clear()
{
	LCD_Command(0x01);
	_delay_ms(2);
}

void LCD_shift_to_left(int steps, int Time)
{
	for(int i=0;i<steps;i++)
	{
		LCD_Command(0b00011000);
		Delay_ms(Time);
	}
}

void Delay_ms(int Time)
{
	for (int i=0;i<Time;i++)
	{
		_delay_ms(1);
	}
}

void LCD_shift_to_right(int steps, int Time)
{
	for(int i=0;i<steps;i++)
	{
		LCD_Command(0b00011100);
		Delay_ms(Time);
	}
}

void cursor_shift_to_left(int steps, int Time)
{
	for(int i=0;i<steps;i++)
	{
		LCD_Command(0b00010000);
		_delay_us(40);
		Delay_ms(Time);
	}
}

void cursor_shift_to_right(int steps, int Time)
{
	for(int i=0;i<steps;i++)
	{
		LCD_Command(0b00010100);
		Delay_ms(Time);
	}
}

void LCD_home()
{
	LCD_Command(0b00000010);
	_delay_ms(2);
}

void cursor_entry_shift_to_left(int steps)
{
	for(int i=0;i<steps;i++)
	{
		LCD_Command(0b00000100);
		_delay_us(40);
	}
}

void cursor_entry_shift_to_right()
{
	LCD_Command(0b00000110);
	_delay_us(40);
}

void LCD_entry_shift_to_left()
{
	LCD_Command(0b00000101);
	_delay_us(40);
}

void LCD_entry_shift_to_right()
{
	LCD_Command(0b00000111);
	_delay_us(40);
}

void LCD_set_DDRAM_address(int pos)
{
	pos += 0b10000000;

	LCD_Command(pos);
	_delay_us(40);
}

void LCD_first_line()
{
	LCD_set_DDRAM_address(0);
}

void LCD_second_line(void)
{
	LCD_set_DDRAM_address(64);
}

void LCD_go_to_location(uint8_t x, uint8_t y)
{
	int numberOfRows[2] = {0,64};

	LCD_set_DDRAM_address(numberOfRows[y] + (x));
}

void LCD_print_ToLocation(uint8_t x, uint8_t y, const char myString[])
{
	LCD_go_to_location(x, y);
	LCD_print(myString);
}

void LCD_printInt_toLocation(uint8_t x, uint8_t y, int value, int nOfDigits, bool spacing, char base)
{
	char nToString[nOfDigits];
	//itoa(value, nToString, base);
	sprintf(nToString,"%d",value);
	LCD_print_ToLocation(x, y, nToString);

	if(spacing == true)
	LCD_print(" ");

}

void LCD_printDouble_toLocation(uint8_t x, uint8_t y, float value, int nOfDigits, int prec, bool spacing)
{
	int intVal = value;
	double precVal = value - intVal;
	int intPrecVal = precVal*prec;

	char iToString[nOfDigits];
	char dToString[nOfDigits];

	sprintf(iToString,"%d",intVal);
	LCD_print_ToLocation(x, y, iToString);
	LCD_print(".");
	sprintf(dToString,"%d",intPrecVal);
	LCD_print(dToString);


	if(spacing == true)
	LCD_print(" ");
}

void LCD_Test()
{
	double i=8900;

	LCD_print("Testing...");
			_delay_ms(1000);
			LCD_print_ToLocation(0, 1, "9999999");
			_delay_ms(2000);
			LCD_clear();
			LCD_Command(0b00001101);
			_delay_ms(1000);
			LCD_Command(0b00001100);

			while(i<=9001)
			{
				LCD_printDouble_toLocation(0, 0, i, 1, 100, 0);
				i = i + 0.010001;

				if(i>=9000)
				{
					LCD_print(" > 9000");

					LCD_go_to_location(0, 1);
					LCD_print("It's over NINE THOUSAAAAAAAAAAAND!!!");
					LCD_shift_to_left(1, 200);
				}
			}

			i = 0;
			_delay_ms(2000);
			LCD_clear();
			LCD_Command(0b00001101);
			_delay_ms(1000);
			LCD_Command(0b00001100);
}

#endif
