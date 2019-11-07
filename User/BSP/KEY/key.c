
#include "key.h"


int key_init(void)
{
    //gpio clock open 
    KEY_1_ENABLE();
    KEY_2_ENABLE();
    
    //init gpio
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Pin = KEY_1_PIN;
    HAL_GPIO_Init(KEY_1_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.Pin = KEY_2_PIN;
    HAL_GPIO_Init(KEY_2_PORT, &GPIO_InitStructure);
    return 0;
}

GPIO_PinState key_1_read(void)
{
    return HAL_GPIO_ReadPin(KEY_1_PORT,KEY_1_PIN);
}

GPIO_PinState key_2_read(void)
{
    return HAL_GPIO_ReadPin(KEY_2_PORT,KEY_2_PIN);
}

