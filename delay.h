#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

void DelayInit(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);


void DelayUs(uint32_t us)
{
	int i = 1.988862371*us;
	while(i--);
}

void DelayMs(uint32_t ms)
{
	DelayUs(ms*1000);
}
#endif
