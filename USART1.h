#ifndef __USART1_H
#define __USART1_H

#include "stm32f10x.h"

void USART1_SendChar (uint8_t ch);
uint8_t USART1_RecieveChar(void);
void SendString(const char string[]);
void USART1_init(void);

void USART1_init(void)
{	//Enable the clock of PORTA.
	RCC ->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//Set GPIOA9 to Alternative output push-pull and GPIOA10 to input floating point.
	GPIOA ->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_1;
	GPIOA ->CRH |= GPIO_CRH_CNF10_0;
	//Enable clock for USART1.
	RCC ->APB2ENR |= RCC_APB2ENR_USART1EN;
	//Set baudrate fck/baud.
	USART1 ->BRR = 8000000/9600;
	//Enable USART1, TX and RX.
	USART1 ->CR1 |= USART_CR1_UE;
	USART1 ->CR1 |= USART_CR1_TE | USART_CR1_RE;
}

void USART1_SendChar (uint8_t ch)
{
	USART1->DR = (ch & 0xFF);
	//wait until bit is set.
	while(!(USART1 ->SR & USART_SR_TXE));
}

uint8_t USART1_RecieveChar()
{
	//wait until bit is set.
	while(!(USART1 ->SR & USART_SR_RXNE));
	
	return (0xFF & USART1 ->DR);
}

void SendString(const char string[])
{
	uint8_t i=0;
	while(string[i])
	{
		USART1_SendChar(string[i]);
		i++;
	}
}

#endif
