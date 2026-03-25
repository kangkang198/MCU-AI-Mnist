/******************************************************************************
*@file  : hal_dwt.h
*@brief : header file
******************************************************************************/
#ifndef __HAL_DWT_H__
#define __HAL_DWT_H__

#include "hal.h"

extern uint32_t HAL_DWT_clkPerUs, HAL_DWT_clkPerMs;

#define _HAL_DWT_GET_CLK_TICK()                  (DWT->CYCCNT)
#define _HAL_DWT_GET_CLK_DELAY(startClkTick)     (DWT->CYCCNT - (startClkTick))
#define _HAL_DWT_DELAY_CLKS(startClkTick,clks)    while(DWT->CYCCNT - (startClkTick) < (clks))

void HAL_DWT_Init(void);


__STATIC_FORCEINLINE uint32_t HAL_DWT_GetClkTick(void)
{
    return DWT->CYCCNT; 
}

uint32_t HAL_DWT_GetClkDelay(uint32_t startClkTick);

uint32_t HAL_DWT_GetUsDelay(uint32_t startClkTick);

uint32_t HAL_DWT_GetMsDelay(uint32_t startClkTick);

void HAL_DWT_DelayClks(uint32_t clks);

void HAL_DWT_DelayUs(uint32_t us);

void HAL_DWT_DelayMs(uint32_t ms);

#endif
