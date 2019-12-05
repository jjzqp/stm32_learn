#ifndef __UART_H__
#define __UART_H__

#include "stm32f4xx_hal.h"
#include "bsp_cfg.h"



#define DEBUG_UART            USART1
#define DEBUG_UART_BAUDRATE   115200

#define DEBUG_UART_CLK_ENABLE      __USART1_CLK_ENABLE
#define DEBUG_UART_IO_CLK_ENABLE   __GPIOA_CLK_ENABLE 

#define DEBUG_UART_TX_IO_PORT    GPIOA
#define DEBUG_UART_TX_IO_PIN     GPIO_PIN_9
#define DEBUG_UART_RX_IO_PORT    GPIOA
#define DEBUG_UART_RX_IO_PIN     GPIO_PIN_10

#define DEBUG_UART_AF            GPIO_AF7_USART1 

#define DEBUG_UART_IRQ           USART1_IRQn
#define DEBUG_UART_IRQ_Handler   USART1_IRQHandler

#ifndef UART_DMA_DEBUG
int usart_init(void);
void usart_send(uint8_t *str);
#endif
uint8_t get_uart_it_flag(void);
uint8_t read_uart_dr_reg(void);
void write_uart_dr_reg(uint8_t ch);




#endif



