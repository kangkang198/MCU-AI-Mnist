
/******************************************************************************
*@file  : hal_wdt.h
*@brief : Header file of WDT HAL module.
******************************************************************************/

#ifndef __HAL_WDT_H__
#define __HAL_WDT_H__

#include "hal.h"


/**
  * @brief   WDT Init structure definition
  */
  
typedef struct
{
    uint32_t Prescaler;         /*!< Select the prescaler of the WDT.
                                     This parameter can be any value of @ref WDT_Clock_Prescaler */
    
    uint32_t Mode;              /*!< Specifies whether WDT mode is reset or interrupted.
                                     This parameter can be any value of @ref WDT_Mode */
    
    uint32_t Load;              /*!< Specifies the WDT reload values.
                                     This parameter must be a number between Min_Data = 0x00000000 
                                     and Max_Data = 0xFFFFFFFF */
    
    uint32_t IntClrTime;        /*!< Specifies the wakeup value to be compared to the down-counter.
                                     This parameter must be a number between Min_Data = 0x0000 
                                     and Max_Data = 0xFFFF */
    
} WDT_InitTypeDef;

/**
  * @brief   WDT Handle Structure definition
  */
  
typedef struct
{
    WDT_TypeDef         *Instance;  /*!< Register base address    */
    
    WDT_InitTypeDef     Init;       /*!< WDT required parameters */
    
} WDT_HandleTypeDef;


/** @defgroup WDT_Cmd
  * @{
  */

#define WDT_CMD_FEED_WATCHDOG                 ( 0xAA55A55AU )

/**
  * @}
  */
/** @defgroup WDT_Clock_Prescaler
  * @{
  */

#define WDT_CLOCK_PRESCALER_1          ( 0U )
#define WDT_CLOCK_PRESCALER_2          ( WDT_CTRL_DIVISOR_0 )
#define WDT_CLOCK_PRESCALER_4          ( WDT_CTRL_DIVISOR_1 )
#define WDT_CLOCK_PRESCALER_8          ( WDT_CTRL_DIVISOR_1 | WDT_CTRL_DIVISOR_0 )
#define WDT_CLOCK_PRESCALER_16         ( WDT_CTRL_DIVISOR_2 )
#define WDT_CLOCK_PRESCALER_32         ( WDT_CTRL_DIVISOR_2 | WDT_CTRL_DIVISOR_0 )
#define WDT_CLOCK_PRESCALER_64         ( WDT_CTRL_DIVISOR_2 | WDT_CTRL_DIVISOR_1 )
#define WDT_CLOCK_PRESCALER_128        ( WDT_CTRL_DIVISOR_2 | WDT_CTRL_DIVISOR_1 | WDT_CTRL_DIVISOR_0 )

/**
  * @}
  */
  
/** @defgroup WDT_Mode
  * @{
  */

#define  WDT_MODE_RESET                 ( 0U )
#define  WDT_MODE_INTERRUPT             ( WDT_CTRL_MODE )

/**
  * @}
  */
  

/**
  * @brief   
  */
  
#define  WDT_GET_IT_ENABLE(__HWDT__)        ( (__HWDT__)->Instance->CTRL |= WDT_CTRL_INTEN )
  
#define  WDT_GET_IT_DISABLE(__HWDT__)       ( (__HWDT__)->Instance->CTRL &= ~WDT_CTRL_INTEN )
  
#define  WDT_GET_RIS(__HWDT__)              ( ((__HWDT__)->Instance->RIS & WDT_RIS_WDTRIS) ? SET : RESET )
  
  
  
/** @defgroup  EXTI Private Macros
  * @{
  */
  
#define IS_WDT_ALL_INSTANCE(__INSTANCE__)   ((__INSTANCE__) == WDT)

#define IS_WDT_PRESCALER(__PRESCALER__)     (((__PRESCALER__) == WDT_CLOCK_PRESCALER_1)  || \
                                             ((__PRESCALER__) == WDT_CLOCK_PRESCALER_2)  || \
                                             ((__PRESCALER__) == WDT_CLOCK_PRESCALER_4) || \
                                             ((__PRESCALER__) == WDT_CLOCK_PRESCALER_8) || \
                                             ((__PRESCALER__) == WDT_CLOCK_PRESCALER_16) || \
                                             ((__PRESCALER__) == WDT_CLOCK_PRESCALER_32)|| \
                                             ((__PRESCALER__) == WDT_CLOCK_PRESCALER_64)|| \
                                             ((__PRESCALER__) == WDT_CLOCK_PRESCALER_128))

#define IS_WDT_MODE(__MODE__)               (((__MODE__) == WDT_MODE_RESET)  || \
                                             ((__MODE__) == WDT_MODE_INTERRUPT))

#define IS_WDT_INTCLRTIME(__TIME__)          ((__TIME__) <= 0xFFFFU)

/**
  * @}
  */
  
/* Exported functions --------------------------------------------------------*/

void HAL_WDT_IRQHandler(WDT_HandleTypeDef *hiwdt);

void HAL_WDT_Callback(WDT_HandleTypeDef *hiwdt);

HAL_StatusTypeDef HAL_WDT_Init(WDT_HandleTypeDef * hidt);

void HAL_WDT_MspInit(WDT_HandleTypeDef * hiwdt);

HAL_StatusTypeDef HAL_WDT_Refresh(WDT_HandleTypeDef *hiwdt);

FlagStatus HAL_WDT_GetPending(void);

void HAL_WDT_ClearPending(void);



#endif
