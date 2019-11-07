#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx_hal.h"

#define LED_RED_ENABLE()   __GPIOH_CLK_ENABLE()
#define LED_RED_PORT       GPIOH 
#define LED_RED_PIN        GPIO_PIN_10 


int led_init(void);

int led_red_ctrl(unsigned char onoff);

#endif


