
#include "dma.h"
#include "uart.h"

DMA_HandleTypeDef DMA_Handle;

int dma_config(void)
{
    //dma clock open 
    DMA_CLK_ENABLE();
    
    //init dma
    DMA_Handle.Instance = DMA_CFG_STREAM;
    DMA_Handle.Init.Channel = DMA_CFG_CHANNEL;
    DMA_Handle.Init.Direction = DMA_MEMORY_TO_MEMORY;//存储器到存储器传输
    DMA_Handle.Init.PeriphInc = DMA_PINC_ENABLE;//使能自动递增
    DMA_Handle.Init.MemInc    = DMA_MINC_ENABLE;//使能自动递增
    DMA_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;//32位对齐
    DMA_Handle.Init.MemDataAlignment  = DMA_MDATAALIGN_WORD;//32位对齐
    DMA_Handle.Init.Mode = DMA_NORMAL;  //单次模式 (存储器到存储器模式不能使用循环模式)
    DMA_Handle.Init.Priority = DMA_PRIORITY_HIGH;//高优先级

    DMA_Handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;//禁用FIFO模式
    DMA_Handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;

    DMA_Handle.Init.MemBurst = DMA_MBURST_SINGLE ;//存储器传输单次模式 
    DMA_Handle.Init.PeriphBurst = DMA_PBURST_SINGLE;//外设传输单次模式
    HAL_DMA_Init(&DMA_Handle);


    return 0;
}

int dma_start(void)
{
   HAL_StatusTypeDef DMA_Status = HAL_ERROR;
   DMA_Status = HAL_DMA_Start(&DMA_Handle,(uint32_t)src_buf,(uint32_t)dst_buf,BUF_SIZE);
   if(DMA_Status != HAL_OK){
        printf("DMA Transfer err!!!\n");
        return -1;
   }
   return 0;
}

uint8_t buffer_cmp(const uint32_t* buf0,uint32_t* buf1,uint32_t buf_size)
{
    while(buf_size--){    
        if(*buf0 != *buf1){
            return 0;
        }
       buf0++;
       buf1++; 
    }
    return 1;
}
int dma_test()
{
    int ret = 0;
    dma_config(); 
    ret = dma_start();
    if(ret){
        return -1;
    }
    while(__HAL_DMA_GET_FLAG(&DMA_Handle,DMA_FLAG_TCIF0_4) == RESET); //等待DMA传输完成
    ret = buffer_cmp(src_buf,dst_buf,BUF_SIZE);
    if(ret){
        printf("Buf Transfer succ\n" );
    } else {
        printf("Buf Transfer faild!!!\n");
				return -1;
    }
		
		return 0;
}

