/******************************************************************************
*@file  : hal.h
*@brief : 
******************************************************************************/

#ifndef __HAL_H
#define __HAL_H

#include "acm32h5xx_hal_conf.h"

typedef struct
{
   uint32_t clktickLatest;   
   uint32_t mstickLatest;
   uint32_t clkCount;     
   uint32_t msCount;       
} HAL_DelayHandleTypeDef;

typedef struct
{
    uint32_t intPrio;        //中断优先级
    uint32_t freq;           //定时器频率，单位 Hz
    uint32_t period;         //定时器周期 
    uint32_t clkPerUs;       //每微秒的CLK数
    uint32_t clkPerMs;       //每毫秒的CLK数  
    uint32_t msPeriod;       //每个周期的微秒数
    uint32_t usPer65536Clk;  //65536 clk的微秒数    
} HAL_SysTickHandleTypeDef;

extern HAL_SysTickHandleTypeDef g_systickHandle;

HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t intPrio, uint32_t msPeriod);
void HAL_IncTick(void);
uint32_t HAL_GetTick(void);
HAL_StatusTypeDef HAL_SetTickMsPeriod(int msPeriod);
uint32_t HAL_GetTickMsPeriod(void);
void HAL_Delay(uint32_t msDelay);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
void HAL_DelayClks(uint32_t clks);
void HAL_DelayUs(uint32_t us);
void HAL_DelayMs(uint32_t ms);
void HAL_SimpleDelay(volatile uint32_t delay);
void HAL_StartDelay(HAL_DelayHandleTypeDef *hdelay);
void HAL_UpdateDelay(HAL_DelayHandleTypeDef *hdelay);
uint32_t HAL_GetClkDelay(HAL_DelayHandleTypeDef *hdelay);
uint32_t HAL_GetUsDelay(HAL_DelayHandleTypeDef *hdelay);
uint32_t HAL_GetMsDelay(HAL_DelayHandleTypeDef *hdelay);
void HAL_GetUID(uint32_t *UID);

#endif
