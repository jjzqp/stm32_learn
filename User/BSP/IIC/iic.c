
#include "iic.h"
#include "uart.h"

I2C_HandleTypeDef iic_handle;

/**
  * @brief I2C MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{

    GPIO_InitTypeDef _iic_gpio;
    //使能IIC GPIO时钟
    I2Cx_SCL_GPIO_CLK_ENABLE();
    I2Cx_SDA_GPIO_CLK_ENABLE();
    //使能IIC 时钟
    I2Cx_CLK_ENABLE();

    //配置引脚 scl
    _iic_gpio.Pin = I2Cx_SCL_PIN;
    _iic_gpio.Mode = GPIO_MODE_AF_OD;
    _iic_gpio.Pull = GPIO_PULLUP;
    _iic_gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    _iic_gpio.Alternate = I2Cx_SCL_AF;
    HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT,&_iic_gpio);

    //配置引脚 sda
    _iic_gpio.Pin = I2Cx_SDA_PIN;
    _iic_gpio.Mode = GPIO_MODE_AF_OD;
    _iic_gpio.Pull = GPIO_PULLUP;
    _iic_gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    _iic_gpio.Alternate = I2Cx_SDA_AF;
    HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT,&_iic_gpio);

    //强制复位iic时钟
    I2Cx_FORCE_RESET();

    //释放iic时钟复位
    I2Cx_RELEASE_RESET();
    
}

int iic_init(void)
{
    iic_handle.Instance = I2Cx;
    iic_handle.Init.ClockSpeed = 400000;
    iic_handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
    iic_handle.Init.OwnAddress1 = I2Cx_ADDRESS;  //指定主机地址
    iic_handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    iic_handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    iic_handle.Init.OwnAddress2 = 0;
    iic_handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    iic_handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    //初始化iic
    HAL_I2C_Init(&iic_handle);

    return 0;
}


int iic_send_one_byte(uint16_t slave_address,uint16_t write_address,uint8_t *data)
{
    HAL_StatusTypeDef status = HAL_ERROR;
    status = HAL_I2C_Mem_Write(&iic_handle,slave_address, write_address, I2C_MEMADD_SIZE_8BIT, data, 1, 1000);
    if(status != HAL_OK) {
        //Callback
    }
    while(HAL_I2C_GetState(&iic_handle) != HAL_I2C_STATE_READY);
    while(HAL_I2C_IsDeviceReady(&iic_handle,slave_address,300,300) == HAL_TIMEOUT);
    while(HAL_I2C_GetState(&iic_handle) != HAL_I2C_STATE_READY);

    return status;
}

int iic_send_buf(uint16_t slave_address,uint16_t write_address,uint8_t *data,uint16_t data_size)
{
    HAL_StatusTypeDef status = HAL_ERROR;
    status = HAL_I2C_Mem_Write(&iic_handle,slave_address, write_address, I2C_MEMADD_SIZE_8BIT, data, data_size , 100);
    if(status != HAL_OK) {
        //Callback
    }
		
    while(HAL_I2C_GetState(&iic_handle) != HAL_I2C_STATE_READY);
		
    while(HAL_I2C_IsDeviceReady(&iic_handle,slave_address,300,300) == HAL_TIMEOUT);
		
    while(HAL_I2C_GetState(&iic_handle) != HAL_I2C_STATE_READY);

    return status;
}
int iic_read_buf(uint16_t slave_address,uint16_t read_address,uint8_t *data,uint16_t data_size)
{
    HAL_StatusTypeDef status = HAL_ERROR;
    status = HAL_I2C_Mem_Read(&iic_handle,slave_address, read_address, I2C_MEMADD_SIZE_8BIT, (uint8_t*)data, data_size , 1000);
    if(status != HAL_OK) {
        //Callback
    }

    return status;
}

#define EEPROM_PAGESIZE   8
#define EEPROM_ADDRESS        0xA0
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

  Addr = WriteAddr % EEPROM_PAGESIZE;
  count = EEPROM_PAGESIZE - Addr;
  NumOfPage =  NumByteToWrite / EEPROM_PAGESIZE;
  NumOfSingle = NumByteToWrite % EEPROM_PAGESIZE;
 
  /* If WriteAddr is I2C_PageSize aligned  */
  if(Addr == 0) 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage == 0) 
    {
      iic_send_buf(EEPROM_ADDRESS, WriteAddr,pBuffer, NumOfSingle);
    }
    /* If NumByteToWrite > I2C_PageSize */
    else  
    {
      while(NumOfPage--)
      {
				iic_send_buf(EEPROM_ADDRESS, WriteAddr,pBuffer, EEPROM_PAGESIZE);
        WriteAddr +=  EEPROM_PAGESIZE;
        pBuffer += EEPROM_PAGESIZE;
      }

      if(NumOfSingle!=0)
      {
				iic_send_buf(EEPROM_ADDRESS, WriteAddr,pBuffer, NumOfSingle);
      }
    }
  }
  /* If WriteAddr is not I2C_PageSize aligned  */
  else 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage== 0) 
    {
      iic_send_buf(EEPROM_ADDRESS, WriteAddr,pBuffer, NumOfSingle);
    }
    /* If NumByteToWrite > I2C_PageSize */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / EEPROM_PAGESIZE;
      NumOfSingle = NumByteToWrite % EEPROM_PAGESIZE;	
      
      if(count != 0)
      {  
				iic_send_buf(EEPROM_ADDRESS, WriteAddr,pBuffer,count);
        WriteAddr += count;
        pBuffer += count;
      } 
      
      while(NumOfPage--)
      {
				iic_send_buf(EEPROM_ADDRESS, WriteAddr,pBuffer,EEPROM_PAGESIZE);
        WriteAddr +=  EEPROM_PAGESIZE;
        pBuffer += EEPROM_PAGESIZE;  
      }
      if(NumOfSingle != 0)
      {
				iic_send_buf(EEPROM_ADDRESS, WriteAddr,pBuffer,NumOfSingle);
      }
    }
  }  
}

#define DATA_LEN    100
uint8_t write_buf[DATA_LEN];
uint8_t read_buf[DATA_LEN];
void iic_test(void)
{
	 int i = 0 ;
	 iic_init();
	 for(i=0;i<DATA_LEN;i++){
			write_buf[i] = i*2;
	 }
	 
	 I2C_EE_BufferWrite(write_buf,0x10,DATA_LEN);
	 printf("write buf: \n");
	 for(i=0;i<DATA_LEN;i++){
			printf("0x%x  ",write_buf[i]);
		  if(i%16 == 15){
				printf("\n");
			}
	 }
	 iic_read_buf(EEPROM_ADDRESS,0x10,read_buf,DATA_LEN);
	 printf("\nread buf: \n");
	 for(i=0;i<DATA_LEN;i++){
			printf("0x%x  ",read_buf[i]);
		 	if(read_buf[i] != write_buf[i])
			{
				printf("0x%02X ", read_buf[i]);
				printf("I2C EEPROM Data err\n");
				return;
			}
			if(i%16 == 15){
				printf("\n");
			}
	 }
}
