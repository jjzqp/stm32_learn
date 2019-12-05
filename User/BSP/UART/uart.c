#include "bsp_cfg.h"
#include "uart.h"
#include "uart_dma.h"

static UART_HandleTypeDef uart;


uint8_t get_uart_it_flag(void)
{
    if(__HAL_UART_GET_FLAG(&uart,UART_FLAG_RXNE) != RESET){
        return 1;
    }
    return 0;
}

uint8_t read_uart_dr_reg(void)
{
    return READ_REG(uart.Instance->DR) ; //读取过程会清UART_FLAG_RXNE标识位
}
void write_uart_dr_reg(uint8_t ch)
{
    WRITE_REG(uart.Instance->DR,ch);//回显
}
#ifndef UART_DMA_DEBUG
int usart_init(void)
{
    
    uart.Instance = DEBUG_UART;
    uart.Init.BaudRate = DEBUG_UART_BAUDRATE; //波特率
    uart.Init.WordLength = UART_WORDLENGTH_8B; //8位
    uart.Init.StopBits = UART_STOPBITS_1; //一个停止位
    uart.Init.Parity = UART_PARITY_NONE; //无奇偶校验
    uart.Init.Mode = UART_MODE_TX_RX; //收发模式
    HAL_UART_Init(&uart);
    __HAL_UART_ENABLE_IT(&uart,UART_IT_RXNE); //使能接收中断
    return 0;
}

//外部定义usart硬件相关函数
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

	
    GPIO_InitTypeDef _uart_io;
	
		DEBUG_UART_CLK_ENABLE();   
    DEBUG_UART_IO_CLK_ENABLE();
    // TX
    _uart_io.Pin = DEBUG_UART_TX_IO_PIN;  
    _uart_io.Pull = GPIO_PULLUP;   //上拉
    _uart_io.Mode = GPIO_MODE_AF_PP; //复用推挽输出
    _uart_io.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    _uart_io.Alternate = DEBUG_UART_AF;  //复用为usart1
    HAL_GPIO_Init(DEBUG_UART_TX_IO_PORT,&_uart_io);

    // RX
    _uart_io.Pin = DEBUG_UART_RX_IO_PIN;  
    _uart_io.Alternate = DEBUG_UART_AF;  //复用为usart1
    HAL_GPIO_Init(DEBUG_UART_RX_IO_PORT,&_uart_io);

    //抢占优先级0 子优先级1
    HAL_NVIC_SetPriority(DEBUG_UART_IRQ,0,1);
    HAL_NVIC_EnableIRQ(DEBUG_UART_IRQ);

}

void usart_send(uint8_t *str)
{
    int i = 0;
    for(i = 0; *(str+i) != '\0';i++) {
       HAL_UART_Transmit(&uart,(uint8_t*)(str+i),1,1000); 
    }
}

//重定向c库printf
int fputc(int c,FILE *f)
{
    HAL_UART_Transmit(&uart,(uint8_t*)&c,1,0xFFFF); 
    return c;
}
//重定向c库scanf
int fgetc(FILE *f)
{
    int c;
    while(__HAL_UART_GET_FLAG(&uart,UART_FLAG_RXNE) == RESET);
    HAL_UART_Receive(&uart,(uint8_t *)&c,1,0xFFFF);
    return c;
}
#endif
