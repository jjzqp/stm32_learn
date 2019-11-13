#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx_hal.h"



int usart_init(void);

void usart_send(uint8_t *str);

#endif


