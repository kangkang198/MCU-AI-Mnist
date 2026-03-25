/******************************************************************************
*@file  : hal_dwt.c
*@brief : DataWatchpoint andTrace 
******************************************************************************/

#include "hal_dwt.h"

#ifdef HAL_DWT_MODULE_ENABLED

uint32_t HAL_DWT_clkPerUs, HAL_DWT_clkPerMs;


void HAL_DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;//先使能DWT外设，由内核调试寄存器DEM_CR的位24控制，写1使能
    DWT->CYCCNT = 0;  //使能CYCCNT寄存器之前，先清0。
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;//使能CYCCNT寄存器，由DWT_CTRL的位0控制，写1使能。
    HAL_DWT_clkPerUs = SystemCoreClock/1000000;
    HAL_DWT_clkPerMs = SystemCoreClock/1000;
}



uint32_t HAL_DWT_GetClkDelay(uint32_t startClkTick)
{
    return (DWT->CYCCNT - startClkTick);
}

uint32_t HAL_DWT_GetUsDelay(uint32_t startClkTick)
{
    return (DWT->CYCCNT - startClkTick)/HAL_DWT_clkPerUs;
}

uint32_t HAL_DWT_GetMsDelay(uint32_t startClkTick)
{
    return (DWT->CYCCNT - startClkTick)/HAL_DWT_clkPerMs;
}


void HAL_DWT_DelayClks(uint32_t clks)
{
    uint32_t startClkTick;
    
    startClkTick = DWT->CYCCNT;   
    while(DWT->CYCCNT - startClkTick < clks);
}

void HAL_DWT_DelayUs(uint32_t us)
{
    uint32_t clks,startClkTick;
    
    startClkTick = DWT->CYCCNT;
    clks = HAL_DWT_clkPerUs*us;    
    while(DWT->CYCCNT - startClkTick < clks);
}

void HAL_DWT_DelayMs(uint32_t ms)
{
    while(ms--)
    {
        HAL_DWT_DelayClks(HAL_DWT_clkPerMs); 
    }
}

#endif




