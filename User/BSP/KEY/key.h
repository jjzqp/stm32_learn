
#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f4xx_hal.h"

#define KEY_1_ENABLE()   __GPIOA_CLK_ENABLE()
#define KEY_1_PORT       GPIOA 
#define KEY_1_PIN        GPIO_PIN_0 
#define KEY_1_INT_EXTI_IRQ  EXTI0_IRQn
#define KEY_1_IRQHandler    EXTI0_IRQHandler

#define KEY_2_ENABLE()   __GPIOC_CLK_ENABLE()
#define KEY_2_PORT       GPIOC 
#define KEY_2_PIN        GPIO_PIN_13 
#define KEY_2_INT_EXTI_IRQ  EXTI15_10_IRQn
#define KEY_2_IRQHandler    EXTI15_10_IRQHandler

int key_init(void);

void key_exit_config(void);

GPIO_PinState key_1_read(void);

GPIO_PinState key_2_read(void);

#endif


