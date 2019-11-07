
#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f4xx_hal.h"

#define KEY_1_ENABLE()   __GPIOA_CLK_ENABLE()
#define KEY_1_PORT       GPIOA 
#define KEY_1_PIN        GPIO_PIN_0 

#define KEY_2_ENABLE()   __GPIOC_CLK_ENABLE()
#define KEY_2_PORT       GPIOC 
#define KEY_2_PIN        GPIO_PIN_13 

int key_init(void);

GPIO_PinState key_1_read(void);

GPIO_PinState key_2_read(void);

#endif


