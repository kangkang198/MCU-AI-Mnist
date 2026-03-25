#include "delay.h"
/**
  * @brief  启动延时定时器
  * @param  t: 延时时间(us)
  * @retval None
  */
void delay_us(uint32_t t)
{
    uint32_t ticks;
	uint32_t told, tnow, tcnt = 0;
	uint32_t reload = SysTick->LOAD; // LOAD的值
	ticks = t * (g_systickHandle.freq / 1000000UL);	// 需要的节拍数
	told = SysTick->VAL;			 // 刚进入时的计数器值

	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if (tnow < told)
				tcnt += told - tnow;
			else
				tcnt += reload - tnow + told;
			told = tnow;
			if (tcnt >= ticks) // 时间大于等于要延迟的时间,就退出
				break;
		}
	}
}

/**
  * @brief  启动延时定时器
  * @param  t: 延时时间(ms)
  * @retval None
  */
void delay_ms(uint32_t t)
{
	while(t--)
	{
		delay_us(1000);
	}
}

/*!
    \brief    HAL_Delay(重写HAL_Delay,不使用定时中断)
    \param[in]  msDelay: 
    \param[out] none
    \retval     none
*/
void HAL_Delay(uint32_t msDelay)
{
  delay_ms(msDelay);
}