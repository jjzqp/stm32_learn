
#include "sys_tick.h"

static uint32_t sys_tick_cnt = 0;

void delay_10us(uint32_t time)
{
	sys_tick_cnt = time;
	while(sys_tick_cnt != 0);
}

int sys_tick_init(void)
{
	 /* SystemFrequency / 1000     1ms     
  	* SystemFrequency / 100000   10us     
    * SystemFrequency / 1000000  1us 
  	*/ 
   if(HAL_SYSTICK_Config(SystemCoreClock / 100000)){
		 while(1);
	 }
    return 0;
}

void sys_tick_deal(void)
{
	if(sys_tick_cnt != 0) {
		 sys_tick_cnt--; 
	}
}
