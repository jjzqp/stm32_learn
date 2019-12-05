
#include "uart_dma.h"

#ifdef UART_DMA_DEBUG  /* UART DMA 使能 */

static UART_HandleTypeDef uart_dma;
static DMA_HandleTypeDef dma_handle;

/**** 初始化 usart ****/
int usart_dma_init(void)
{
    uart_dma.Instance = DEBUG_DMA_UART;
    uart_dma.Init.BaudRate = DEBUG_DMA_UART_BAUDRATE; //波特率
    uart_dma.Init.WordLength = UART_WORDLENGTH_8B; //8位
    uart_dma.Init.StopBits = UART_STOPBITS_1; //一个停止位
    uart_dma.Init.Parity = UART_PARITY_NONE; //无奇偶校验
    uart_dma.Init.Mode = UART_MODE_TX_RX; //收发模式
    HAL_UART_Init(&uart_dma);
    __HAL_UART_ENABLE_IT(&uart_dma,UART_IT_RXNE); //使能接收中断
	
		usart_dma_config();
    return 0;
}
//外部定义usart硬件相关函数
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

    GPIO_InitTypeDef _uart_io;
		DEBUG_DMA_UART_CLK_ENABLE();   
    DEBUG_DMA_UART_IO_CLK_ENABLE();
    // TX
    _uart_io.Pin = DEBUG_DMA_UART_TX_IO_PIN;  
    _uart_io.Pull = GPIO_PULLUP;   //上拉
    _uart_io.Mode = GPIO_MODE_AF_PP; //复用推挽输出
    _uart_io.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    _uart_io.Alternate = DEBUG_DMA_UART_AF;  //复用为usart1
    HAL_GPIO_Init(DEBUG_DMA_UART_TX_IO_PORT,&_uart_io);

    // RX
    _uart_io.Pin = DEBUG_DMA_UART_RX_IO_PIN;  
    _uart_io.Alternate = DEBUG_DMA_UART_AF;  //复用为usart1
    HAL_GPIO_Init(DEBUG_DMA_UART_RX_IO_PORT,&_uart_io);

    //抢占优先级0 子优先级1
    HAL_NVIC_SetPriority(DEBUG_DMA_UART_IRQ,0,1);
    HAL_NVIC_EnableIRQ(DEBUG_DMA_UART_IRQ);

}

/**** 关联dma  ****/
int usart_dma_config(void)
{
   DUBUG_DMA_ENABLE();
   //指定uart1 tx数据流7 通道4
   dma_handle.Instance = DEBUG_DMA_UART_STREAM;
   dma_handle.Init.Channel = DEBUG_DMA_UART_CHANNEL;
   dma_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;//存储器到外设
   dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;//外设地址不递增
   dma_handle.Init.MemInc = DMA_MINC_ENABLE; //使能内存地址递增
   dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;//字节对齐
   dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;//字节对齐(8 bit)
   dma_handle.Init.Mode = DMA_NORMAL; // 单次传输
   dma_handle.Init.Priority = DMA_PRIORITY_MEDIUM;//中等优先级
   dma_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;//禁用FIFO
   dma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
   dma_handle.Init.MemBurst = DMA_MBURST_SINGLE;//
   dma_handle.Init.PeriphBurst = DMA_PBURST_SINGLE;//

   //DMA 初始化默认值
   HAL_DMA_DeInit(&dma_handle);
   //配置DMA
   HAL_DMA_Init(&dma_handle);

   //链接dma和usar tx外设
   __HAL_LINKDMA(&uart_dma,hdmatx,dma_handle);

   return 0; 
}

void uart_dma_send(uint8_t *buf,int size)
{
    HAL_UART_Transmit_DMA(&uart_dma,(uint8_t*)(buf),size); 
}
//重定向c库printf
int fputc(int c,FILE *f)
{
    HAL_UART_Transmit(&uart_dma,(uint8_t*)&c,1,1000); 
    return c;
}
#define BUFF_LEN     50
char buf[BUFF_LEN];
int uart_dma_test()
{
	usart_dma_init();
	


	///for(int i=0;i<BUFF_LEN;i++){
	///	buf[i] = 'c';
	///}
  ///uart_dma_send((uint8_t*)buf,BUFF_LEN);
	
	return 0;
}
#endif

