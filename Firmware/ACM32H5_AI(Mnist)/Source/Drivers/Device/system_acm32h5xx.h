
/******************************************************************************
*@file  : system_acm32h5xx.h
*@brief : CMSIS Cortex-M33 Device Peripheral Access Layer System Source File
******************************************************************************/

#ifndef __SYSTEM_ACM32H5XX_H
#define __SYSTEM_ACM32H5XX_H

#include "acm32h5xx_hal_conf.h"
    
typedef enum 
{
    SYSCLK_220M_SRC_RCH = 0,
    SYSCLK_200M_SRC_RCH,
    SYSCLK_180M_SRC_RCH,
    SYSCLK_160M_SRC_RCH,
    SYSCLK_100M_SRC_RCH,
    SYSCLK_80M_SRC_RCH,
    SYSCLK_64M_SRC_RCH,
    SYSCLK_32M_SRC_RCH,
    SYSCLK_16M_SRC_RCH,
    SYSCLK_8M_SRC_RCH,
    SYSCLK_4M_SRC_RCH,
    
    SYSCLK_220M_SRC_XTH_12M,
    SYSCLK_210M_SRC_XTH_12M,
    SYSCLK_200M_SRC_XTH_12M,
    SYSCLK_190M_SRC_XTH_12M,
    SYSCLK_180M_SRC_XTH_12M,
    SYSCLK_170M_SRC_XTH_12M,
    SYSCLK_160M_SRC_XTH_12M,
    SYSCLK_150M_SRC_XTH_12M,
    SYSCLK_140M_SRC_XTH_12M,
    SYSCLK_130M_SRC_XTH_12M,
    SYSCLK_120M_SRC_XTH_12M,
    SYSCLK_110M_SRC_XTH_12M,
    SYSCLK_100M_SRC_XTH_12M,
    SYSCLK_90M_SRC_XTH_12M,
    SYSCLK_80M_SRC_XTH_12M,
    SYSCLK_70M_SRC_XTH_12M,
    SYSCLK_64M_SRC_XTH_12M,
    SYSCLK_60M_SRC_XTH_12M,
    SYSCLK_50M_SRC_XTH_12M,
    SYSCLK_48M_SRC_XTH_12M,
    SYSCLK_40M_SRC_XTH_12M,
    SYSCLK_30M_SRC_XTH_12M,
    SYSCLK_24M_SRC_XTH_12M,
    SYSCLK_12M_SRC_XTH_12M,
    SYSCLK_8M_SRC_XTH_12M,
    SYSCLK_4M_SRC_XTH_12M,
    
    SYSCLK_64M_RCH,
    SYSCLK_32M_RCH,
    SYSCLK_16M_RCH,
    SYSCLK_8M_RCH,
    SYSCLK_4M_RCH,

    SYSCLK_12M_XTH_12M,
    SYSCLK_6M_XTH_12M,
    SYSCLK_4M_XTH_12M,
    
    SYSCLK_MAX,

}SYSCLK_SelectTypeDef;

/****** system core clock select, uesr config ***********/
#define SYSCLK_SELECT       SYSCLK_220M_SRC_XTH_12M 

/******************************************************************************
*@brief : PCLK1_DIV_SELECT: pclk1 div select, uesr config
*           @arg 1, 2, 4, 8, 16
******************************************************************************/
#define PCLK1_DIV_SELECT    2

/******************************************************************************
*@brief : PCLK2_DIV_SELECT: pclk2 div select, uesr config
*           @arg 1, 2, 4, 8, 16
******************************************************************************/
#define PCLK2_DIV_SELECT    2


/******************************************************************************
*@brief : PCLK3_DIV_SELECT: pclk3 div select, uesr config
*           @arg 1, 2, 4, 8, 16
******************************************************************************/
#define PCLK3_DIV_SELECT    2


/******************************************************************************
*@brief : PCLK4_DIV_SELECT: pclk4 div select, uesr config
*           @arg 1, 2, 4, 8, 16
******************************************************************************/
#define PCLK4_DIV_SELECT    2

/******************************************************************************
*@note  : SystemCoreClock variable is updated in three ways:
*           1) by calling CMSIS function SystemCoreClockUpdate()
*           2) by calling HAL API function HAL_RCC_GetSysClkFreq()
*           3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency 
*               If you use this function to configure the system clock; then there
*               is no need to call the 2 first functions listed above, since SystemCoreClock
*               variable is updated automatically.
******************************************************************************/
extern volatile uint32_t SystemCoreClock; /*!< System Clock Frequency (Core Clock) */

void SystemInit(void);
void SystemCoreClockUpdate(void);
HAL_StatusTypeDef SystemClock_Config(uint32_t sysclkSel, uint32_t pclk1Div, \
                                     uint32_t pclk2Div, uint32_t pclk3Div, uint32_t pclk4Div);

#endif /* __SYSTEM_ACM32H5XX_H */
