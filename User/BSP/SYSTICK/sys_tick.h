#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx_hal.h"



int sys_tick_init(void);
void sys_tick_deal(void);

void delay_10us(uint32_t time);


#endif


