
#include "uart.h"


UART_HandleTypeDef uart;

int usart_init(void)
{
    
    uart.Instance = USART1;
    uart.Init.BaudRate = 115200;
    uart.Init.WordLength = UART_WORDLENGTH_8B; //8位
    uart.Init.StopBits = UART_STOPBITS_1; //一个停止位
    uart.Init.Parity = UART_PARITY_NONE; //无奇偶校验
    uart.Init.Mode = UART_MODE_TX_RX; //收发模式
    HAL_UART_Init(&uart);
    __HAL_UART_ENABLE_IT(&uart,UART_IT_RXNE); //使能接收中断
    return 0;
}

//外部定义usart 相关函数
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

    GPIO_InitTypeDef _uart_io;
	__USART1_CLK_ENABLE();   
    __GPIOA_CLK_ENABLE();
    // TX
    _uart_io.Pin = GPIO_PIN_9;  
    _uart_io.Pull = GPIO_PULLUP;
    _uart_io.Mode = GPIO_MODE_AF_PP; //复用推挽输出
    _uart_io.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    _uart_io.Alternate = GPIO_AF7_USART1;  //复用为usart1
    HAL_GPIO_Init(GPIOA,&_uart_io);

    // RX
    _uart_io.Pin = GPIO_PIN_10;  
    _uart_io.Pull = GPIO_NOPULL;
    _uart_io.Mode = GPIO_MODE_INPUT; 
    _uart_io.Alternate = GPIO_AF7_USART1;  //复用为usart1
    HAL_GPIO_Init(GPIOA,&_uart_io);

    //抢占优先级0 子优先级1
    HAL_NVIC_SetPriority(USART1_IRQn,0,1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

}

void usart_send(uint8_t *str)
{
    int i = 0;
    for(i = 0; *(str+i) != '\0';i++) {
       HAL_UART_Transmit(&uart,(uint8_t*)(str+i),1,1000); 
    }
}

