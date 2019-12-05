#ifndef __UART_H__
#define __UART_H__

#include "stm32f4xx_hal.h"
#include "bsp_cfg.h"


#ifdef UART_DMA_DEBUG  /* UART DMA 使能 */

#define DEBUG_DMA_UART            USART1
#define DEBUG_DMA_UART_BAUDRATE   115200

#define DEBUG_DMA_UART_CLK_ENABLE      __USART1_CLK_ENABLE
#define DEBUG_DMA_UART_IO_CLK_ENABLE   __GPIOA_CLK_ENABLE 

#define DEBUG_DMA_UART_TX_IO_PORT    GPIOA
#define DEBUG_DMA_UART_TX_IO_PIN     GPIO_PIN_9
#define DEBUG_DMA_UART_RX_IO_PORT    GPIOA
#define DEBUG_DMA_UART_RX_IO_PIN     GPIO_PIN_10

#define DEBUG_DMA_UART_AF            GPIO_AF7_USART1 

#define DEBUG_DMA_UART_IRQ           USART1_IRQn
#define DEBUG_DMA_UART_IRQ_Handler   USART1_IRQHandler

// DMA 配置 (查表可知USART1对应DMA2的数据流7通道4)
#define DEBUG_DMA_UART_STREAM          DMA2_Stream7  //存储器到uart外设
#define DEBUG_DMA_UART_CHANNEL         DMA_CHANNEL_4

#define DUBUG_DMA_UART_ENABLE()        __DMA2_CLK_ENABLE()

int usart_dma_init(void);
int usart_dma_config(void);
void uart_dma_send(uint8_t *buf,int size);
#endif

#endif


