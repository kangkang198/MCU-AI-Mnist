/******************************************************************************
*@file  : hal.c
*@brief : This is the common part of the HAL initialization
******************************************************************************/

#include "hal.h"  

static __IO uint32_t g_msTick = 0;
HAL_SysTickHandleTypeDef g_systickHandle;

/******************************************************************************
*@brief : init hal library
*@param : none
*@return: none
******************************************************************************/
HAL_StatusTypeDef HAL_Init(void)
{
    /* Init the low level hardware */
	HAL_MspInit();
    
	/* Set Interrupt Group Priority */
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    
    __HAL_RCC_EFUSE1_CLK_ENABLE();
    
    HAL_RCC_GetSysCoreClockFreq();
     
	/* Use systick as time base source and configure 1ms tick (default clock after Reset is RCH) */
    HAL_InitTick(TICK_INT_PRIORITY, TICK_PERIOD_MS);  
    
    #if (DATA_ACCELERATE_ENABLE == 1)
		System_EnableDAccelerate();
	#endif    

	/* Return function status */
	return HAL_OK;
}


/******************************************************************************
*@brief : deinit hal library
*@param : none
*@return: none
******************************************************************************/
HAL_StatusTypeDef HAL_DeInit(void)
{
  /* Reset of all peripherals */

  /* De-Init the low level hardware */
  HAL_MspDeInit();
    
  /* Return function status */
  return HAL_OK;
}


/******************************************************************************
*@brief : Initialize the MSP
*@param : none
*@return: none
******************************************************************************/
__attribute__((weak)) void HAL_MspInit(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_MspInit could be implemented in the user file
   */
}


/******************************************************************************
*@brief : DeInitializes the MSP
*@param : none
*@return: none
******************************************************************************/
__attribute__((weak)) void HAL_MspDeInit(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_MspDeInit could be implemented in the user file
   */ 
}


/******************************************************************************
*@brief : This function configures the source of the time base.
*         The time source is configured  to have 1ms time base with a dedicated Tick interrupt priority.       
*@note  : This function is called  automatically at the beginning of program after
*         reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig().
*@note  : In the default implementation, SysTick timer is the source of time base. 
*           It is used to generate interrupts at regular time intervals. 
*           Care must be taken if HAL_Delay() is called from a peripheral ISR process, 
*           The SysTick interrupt must have higher priority (numerically lower)
*           than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
*           The function is declared as __weak  to be overwritten  in case of other
*           implementation  in user file.
*@param : TickPriority: Tick interrupt priority.
*@retval: HAL status
******************************************************************************/
__attribute__((weak)) HAL_StatusTypeDef HAL_InitTick(uint32_t intPrio, uint32_t msPeriod)
{
    /* Configure the SysTick to have interrupt in 1ms time basis*/
    g_systickHandle.freq = SystemCoreClock;   
    if (HAL_SYSTICK_Config(g_systickHandle.freq / (1000U / msPeriod)) > 0U)
    {
        return HAL_ERROR;
    }
    
    g_systickHandle.period = SysTick->LOAD;  
    g_systickHandle.clkPerUs = g_systickHandle.freq / 1000000;
    g_systickHandle.clkPerMs = g_systickHandle.freq / 1000;    
    g_systickHandle.msPeriod = msPeriod; 
    g_systickHandle.usPer65536Clk = 65536 / g_systickHandle.clkPerUs;  

    /* Configure the SysTick IRQ priority */
    if (intPrio >= (1UL << __NVIC_PRIO_BITS))
        intPrio = (1UL << __NVIC_PRIO_BITS) - 1;

    HAL_NVIC_SetPriority(SysTick_IRQn, intPrio, 0U);
    g_systickHandle.intPrio = intPrio;

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : This function is called to increment  a global variable "g_msTick"
*           In the default implementation, this variable is incremented each 1ms in SysTick ISR.
*           This function is declared as __weak to be overwritten in case of other implementations in user file.
*@param : none
*@return: none
******************************************************************************/
__attribute__((weak)) void HAL_IncTick(void)
{
	g_msTick += g_systickHandle.msPeriod;
}


/******************************************************************************
*@brief : Provides a tick value in millisecond
*         This function is declared as __weak to be overwritten in case of other implementations in user file.
*@return: none
******************************************************************************/
__attribute__((weak)) uint32_t HAL_GetTick(void)
{
    return (g_msTick);
}


/******************************************************************************
*@brief : Set new SysTick period in ms
*@return: Status
******************************************************************************/
HAL_StatusTypeDef HAL_SetTickMsPeriod(int msPeriod)
{
    if (g_systickHandle.msPeriod == msPeriod)
        return (HAL_OK);

    return (HAL_InitTick(g_systickHandle.intPrio, g_systickHandle.msPeriod));
}

/******************************************************************************
*@brief : Return SysTick period
*@return: SysTick period in ms
******************************************************************************/
uint32_t HAL_GetTickMsPeriod(void)
{
    return g_systickHandle.msPeriod;
}


/******************************************************************************
*@brief : This function provides minimum delay (in milliseconds) based on variable incremented
*           This function is declared as __weak to be overwritten in case of other implementations in user file.
*@param : Delay: specifies the delay time length, in milliseconds.
*@return: none
******************************************************************************/
__attribute__((weak)) void HAL_Delay(uint32_t msDelay)
{
    uint32_t tickstart = HAL_GetTick();
    uint32_t wait = msDelay;

    /* Add a freq to guarantee minimum wait */
    if (wait < (HAL_MAX_DELAY- (uint32_t)(g_systickHandle.msPeriod)))
    {
        wait += (uint32_t)(g_systickHandle.msPeriod);
    }

    while((HAL_GetTick() - tickstart) < wait)
    {
    }
}

/******************************************************************************
*@brief : Suspend Tick increment
*@param : none
*@return: none
******************************************************************************/
__attribute__((weak)) void HAL_SuspendTick(void)  
{
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk;
}

/******************************************************************************
*@brief : Resume Tick increment
*@param : none
*@return: none
******************************************************************************/
__attribute__((weak)) void HAL_ResumeTick(void)  
{
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;   
}


/******************************************************************************
*@brief : SysTick时钟延时。定时中断关闭也可计时。100MHz时钟时，最大延时32秒，其他时钟以此类推。
*@param : clks: 延时的clks
*@ret   : 无
******************************************************************************/
void HAL_DelayClks(uint32_t clks)
{
    uint32_t clktickStart, clktickNow;
    uint32_t count;

    clktickStart = SysTick->VAL;
    count = 0;
    while(1)
    {
        clktickNow = SysTick->VAL;
        
        if(clktickNow <= clktickStart)
            count += clktickStart - clktickNow;
        else
            count += clktickStart + g_systickHandle.period - clktickNow;
        
        if(count >= clks)
            return;
        clktickStart = clktickNow;
    }
}

/******************************************************************************
*@brief : 微秒延时。定时中断关闭也可计时。最大延时70分钟左右。
*@param : us: 延时的微秒数
*@ret   : 无
******************************************************************************/
void HAL_DelayUs(uint32_t us)
{
    while(us > 1000000)
    {
        HAL_DelayClks(g_systickHandle.freq);
        us -= 1000000;
    }
    HAL_DelayClks(g_systickHandle.clkPerUs * us);
}

/******************************************************************************
*@brief : 毫秒延时。定时中断关闭也可计时。最大延时49天左右。
*@param : ms: 延时的毫秒数
*@ret   : 无
******************************************************************************/
void HAL_DelayMs(uint32_t ms)
{
    while(ms > 1000)
    {
        HAL_DelayClks(g_systickHandle.freq);
        ms -= 1000;
    }
    HAL_DelayClks(g_systickHandle.clkPerMs * ms);
}

/******************************************************************************
*@brief : 通过while循环简单延时。
*@param : delay: while循环次数
*@ret   : 无
******************************************************************************/
void HAL_SimpleDelay(volatile uint32_t delay)  
{
    while(delay--)
    {
        ;
    }
}


/******************************************************************************
*@brief : 启动delay事务。获取当前tick，初始化delay handle参数。
*@param : hdelay: delay handle
*@ret   : 无
******************************************************************************/
void HAL_StartDelay(HAL_DelayHandleTypeDef *hdelay)
{
    do 
    {
        hdelay->mstickLatest = g_msTick;
        hdelay->clktickLatest = SysTick->VAL;
    } 
    while(g_msTick != hdelay->mstickLatest);
    
    hdelay->clkCount = 0;  
    hdelay->msCount = 0;  
}

/******************************************************************************
*@brief : 更新delay事务。
*@param : hdelay: delay handle
*@ret   : 无
******************************************************************************/
void HAL_UpdateDelay(HAL_DelayHandleTypeDef *hdelay)
{
    uint32_t clktickNow, mstickNow,mstickNext;
    
    do 
    {
        mstickNow = g_msTick;
        clktickNow = SysTick->VAL;
    } 
    while(g_msTick != mstickNow);
    
    mstickNext = hdelay->mstickLatest + g_systickHandle.msPeriod;
    
    if(mstickNow < mstickNext)
    {
        if(clktickNow <= hdelay->clktickLatest)
        {
            hdelay->clkCount += hdelay->clktickLatest - clktickNow;
        }
        else
        {
            hdelay->clkCount += hdelay->clktickLatest + g_systickHandle.period - clktickNow;
        }
    }
    else
    {
        hdelay->clkCount += hdelay->clktickLatest + g_systickHandle.period - clktickNow;
        hdelay->msCount += mstickNow - mstickNext;
    }
    
    hdelay->clktickLatest = clktickNow;   
    hdelay->mstickLatest = mstickNow;    
    
    if(hdelay->clkCount >= g_systickHandle.period)
    {
        hdelay->clkCount -= g_systickHandle.period;
        hdelay->msCount += g_systickHandle.msPeriod;
    }
}


/******************************************************************************
*@brief : 从启动delay事务开始，到当前时间的clk延迟。最大计时70分钟左右。定时器中断关闭后也可使用。
*         如果定时器中断关闭，则每个定时器周期需要调用HAL_UpdateDelay函数或者本函数1次以上，
*           否则会导致返回的延时时间比实际时间偏小。
*         如果定时器中断开启，则没有以上限制。
*@param : hdelay: delay handle
*@ret   : 微秒延迟
******************************************************************************/
uint32_t HAL_GetClkDelay(HAL_DelayHandleTypeDef *hdelay)
{
    HAL_UpdateDelay(hdelay);
    
    return hdelay->clkCount +  hdelay->msCount * g_systickHandle.clkPerMs;
}

/******************************************************************************
*@brief : 从启动delay事务开始，到当前时间的微秒延迟。最大计时70分钟左右。定时器中断关闭后也可使用。
*         如果定时器中断关闭，则每个定时器周期需要调用HAL_UpdateDelay函数或者本函数1次以上，
*           否则会导致返回的延时时间比实际时间偏小。
*         如果定时器中断开启，则没有以上限制。
*@param : hdelay: delay handle
*@ret   : 微秒延迟
******************************************************************************/
uint32_t HAL_GetUsDelay(HAL_DelayHandleTypeDef *hdelay)
{
    uint32_t us;
    HAL_UpdateDelay(hdelay);
    
    us = (hdelay->clkCount * g_systickHandle.usPer65536Clk ) >> 16;
    us += hdelay->msCount * 1000;    
    return us;
}

/******************************************************************************
*@brief : 从启动delay事务开始，到当前时间的毫秒延迟。定时器中断关闭后也可使用。
*         如果定时器中断关闭，则每个定时器周期需要调用HAL_UpdateDelay函数或者本函数1次以上，
*           否则会导致返回的延时时间比实际时间偏小。
*         如果定时器中断开启，则没有以上限制。
*@param : hdelay: delay handle
*@ret   : 毫秒延迟
******************************************************************************/
uint32_t HAL_GetMsDelay(HAL_DelayHandleTypeDef *hdelay)
{
    HAL_UpdateDelay(hdelay);
    
    return hdelay->msCount; 
}


/******************************************************************************
*@brief : Returns the unique device identifier (UID based on 128 bits)
*@param : UID: buffer of uid
*@return: none
******************************************************************************/
void HAL_GetUID(uint32_t *UID)
{
    ;
}


 


