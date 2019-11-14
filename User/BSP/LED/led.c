
#include "led.h"


int led_init(void)
{
    //gpio clock open 
    LED_RED_ENABLE();
    
    //init gpio
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 
    GPIO_InitStructure.Pull = GPIO_NOPULL; 
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; 
    GPIO_InitStructure.Pin = LED_RED_PIN;
    HAL_GPIO_Init(LED_RED_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.Pin = LED_GREEN_PIN;
    HAL_GPIO_Init(LED_RED_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.Pin = LED_BLUE_PIN;
    HAL_GPIO_Init(LED_RED_PORT, &GPIO_InitStructure);
    return 0;
}

int led_red_ctrl(unsigned char onoff)
{
    HAL_GPIO_WritePin(LED_RED_PORT,LED_RED_PIN,(GPIO_PinState) onoff);
    return 0; 
}
int led_green_ctrl(unsigned char onoff)
{
    HAL_GPIO_WritePin(LED_GREEN_PORT,LED_GREEN_PIN,(GPIO_PinState) onoff);
    return 0; 
}
int led_blue_ctrl(unsigned char onoff)
{
    HAL_GPIO_WritePin(LED_BLUE_PORT,LED_BLUE_PIN,(GPIO_PinState) onoff);
    return 0; 
}
