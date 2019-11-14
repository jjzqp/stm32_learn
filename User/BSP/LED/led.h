#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx_hal.h"

#define ON   0
#define OFF  1

#define LED_RED_ENABLE()     __GPIOH_CLK_ENABLE()
#define LED_RED_PORT         GPIOH 
#define LED_RED_PIN          GPIO_PIN_10 
#define LED_GREEN_ENABLE()   __GPIOH_CLK_ENABLE()
#define LED_GREEN_PORT       GPIOH 
#define LED_GREEN_PIN        GPIO_PIN_11 
#define LED_BLUE_ENABLE()    __GPIOH_CLK_ENABLE()
#define LED_BLUE_PORT        GPIOH 
#define LED_BLUE_PIN         GPIO_PIN_12 


int led_init(void);

int led_red_ctrl(unsigned char onoff);
int led_green_ctrl(unsigned char onoff);
int led_blue_ctrl(unsigned char onoff);

#define LED_OFF()        \
        do { \
            led_red_ctrl(0); \
            led_green_ctrl(0); \
            led_blue_ctrl(0); \
        }while(0)

#define LED_RED()        \
        do { \
            led_red_ctrl(1); \
            led_green_ctrl(0); \
            led_blue_ctrl(0); \
        }while(0)

#define LED_GREEN()        \
        do { \
            led_red_ctrl(0); \
            led_green_ctrl(1); \
            led_blue_ctrl(0); \
        }while(0)

#define LED_BLUE()        \
        do { \
            led_red_ctrl(0); \
            led_green_ctrl(0); \
            led_blue_ctrl(1); \
        }while(0)

#define LED_YELLOW()        \
        do { \
            led_red_ctrl(1); \
            led_green_ctrl(1); \
            led_blue_ctrl(0); \
        }while(0)

#define LED_PURPLE()        \
        do { \
            led_red_ctrl(1); \
            led_green_ctrl(0); \
            led_blue_ctrl(1); \
        }while(0)

//青
#define LED_CYAN()        \
        do { \
            led_red_ctrl(0); \
            led_green_ctrl(1); \
            led_blue_ctrl(1); \
        }while(0)

#define LED_WHITE()        \
        do { \
            led_red_ctrl(1); \
            led_green_ctrl(1); \
            led_blue_ctrl(1); \
        }while(0)
#endif


