/******************************************************************************
*@file  : hal_exti.h
*@brief : Header file of EXTI HAL module.
******************************************************************************/

#ifndef __HAL_EXTI_H__
#define __HAL_EXTI_H__

#include "hal.h"
#include "hal_gpio.h"


/** @defgroup EXTI_Line
  * @brief    When line is 0-15, its definition is the same as GPIO_pins
  * @{
  */

#define EXTI_LINE_0				                ( 0U )
#define EXTI_LINE_1				                ( 1U )
#define EXTI_LINE_2				                ( 2U )
#define EXTI_LINE_3				                ( 3U )
#define EXTI_LINE_4				                ( 4U )
#define EXTI_LINE_5				                ( 5U )
#define EXTI_LINE_6				                ( 6U )
#define EXTI_LINE_7				                ( 7U )
#define EXTI_LINE_8				                ( 8U )
#define EXTI_LINE_9				                ( 9U )
#define EXTI_LINE_10				            ( 10U )
#define EXTI_LINE_11				            ( 11U )
#define EXTI_LINE_12				            ( 12U )
#define EXTI_LINE_13				            ( 13U )
#define EXTI_LINE_14				            ( 14U )
#define EXTI_LINE_15				            ( 15U )
#define EXTI_LINE_LVD				            ( 16U )
#define EXTI_LINE_RTC				            ( 17U )
#define EXTI_LINE_IWDT				            ( 18U )
#define EXTI_LINE_COMP1				            ( 19U )
#define EXTI_LINE_COMP2				            ( 20U )
#define EXTI_LINE_COMP3				            ( 21U )
#define EXTI_LINE_COMP4				            ( 22U )
#define EXTI_LINE_USB1   	                    ( 23U )
#define EXTI_LINE_USB2				            ( 24U )
#define EXTI_LINE_LPTIM1                        ( 25U )
#define EXTI_LINE_LPTIM2                        ( 26U )
#define EXTI_LINE_LPTIM3                        ( 27U )
#define EXTI_LINE_LPTIM4                        ( 28U )
#define EXTI_LINE_LPTIM5                        ( 29U )
#define EXTI_LINE_LPTIM6                        ( 30U )
#define EXTI_LINE_LPUART1                       ( 31U )
#define EXTI_LINE_LPUART2                       ( 32U )
#define EXTI_LINE_ETH_WAKEUP                    ( 33U )
#define EXTI_LINE_TKEY				            ( 34U )


/**
  * @}
  */

/** @brief  PIN mask for assert test
  */

#define EXTI_ALL_LINE_MASK                      ( 0x003FFFFFU )     /* PIN mask for assert test */
#define EXTI_GPIO_LINE_MASK                     ( 0x0000FFFFU )     /* PIN mask */
#define EXTI_GPIOA_LINE_MASK                    ( 0x0000FF3FU )     /* PIN mask for assert test */
#define EXTI_GPIOB_LINE_MASK                    ( 0x000000FFU )     /* PIN mask for assert test */
#define EXTI_GPIOC_LINE_MASK                    ( 0x0000E1FFU )     /* PIN mask for assert test */

/** @defgroup EXTI_Mode
  * @brief    its definition is the same as that of GPIO_MODE_IT_RISING、GPIO_MODE_IT_FALLING、
  *           GPIO_MODE_IT_RISING_FALLING、GPIO_MODE_EVT_RISING、GPIO_MODE_EVT_RISING、
  *           GPIO_MODE_EVT_RISING in GPIO_Mode
  * @{
  */

#define  EXTI_MODE_IT_RISING                    ( 0x10110000U )     /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  EXTI_MODE_IT_FALLING                   ( 0x10210000U )     /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  EXTI_MODE_IT_RISING_FALLING            ( 0x10310000U )     /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
#define  EXTI_MODE_EVT_RISING                   ( 0x10120000U )     /*!< External Event Mode with Rising edge trigger detection              */
#define  EXTI_MODE_EVT_FALLING                  ( 0x10220000U )     /*!< External Event Mode with Falling edge trigger detection             */
#define  EXTI_MODE_EVT_RISING_FALLING           ( 0x10320000U )     /*!< External Event Mode with Rising/Falling edge trigger detection      */

/**
  * @}
  */

/** @defgroup EXTI_GPIOSel  EXTI GPIOSel
  * @brief
  * @{
  */
  
#define EXTI_GPIOA                              ( 0U )
#define EXTI_GPIOB                              ( 1U )
#define EXTI_GPIOC                              ( 2U )
#define EXTI_GPIOD                              ( 3U )
#define EXTI_GPIOE                              ( 4U )
#define EXTI_GPIOF                              ( 5U ) 
#define EXTI_GPIOG                              ( 6U ) 
#define EXTI_GPIOH                              ( 7U ) 
#define EXTI_GPIOI                              ( 8U ) 
#define EXTI_GPIOJ                              ( 9U ) 
#define EXTI_GPIOK                              ( 10U ) 
#define EXTI_GPIOL                              ( 11U ) 
#define EXTI_GPIOM                              ( 12U )  
#define EXTI_GPION                              ( 13U ) 
#define EXTI_GPIOO                              ( 14U ) 
#define EXTI_GPIOP                              ( 15U ) 
#define EXTI_GPIOQ                              ( 16U )

/**
  * @}
  */




/** @defgroup  EXTI Private Macros
  * @{
  */
  
#define IS_EXTI_GPIO(__GPIO__)                                  (((__GPIO__) == GPIOA) || ((__GPIO__) == GPIOB) || \
                                                                 ((__GPIO__) == GPIOC) || ((__GPIO__) == GPIOD) || \
                                                                 ((__GPIO__) == GPIOE) || ((__GPIO__) == GPIOF) || \
                                                                 ((__GPIO__) == GPIOG) || ((__GPIO__) == GPIOH) || \
                                                                 ((__GPIO__) == GPIOI) || ((__GPIO__) == GPIOJ) || \
                                                                 ((__GPIO__) == GPIOK) || ((__GPIO__) == GPIOL) || \
                                                                 ((__GPIO__) == GPIOM) || ((__GPIO__) == GPION) || \
                                                                 ((__GPIO__) == GPIOO) || ((__GPIO__) == GPIOP) || \
                                                                 ((__GPIO__) == GPIOQ))

#define IS_EXTI_SINGLE_GPIO_LINE(__LINE__)                      ((__LINE__) <= EXTI_LINE_15)

#define IS_EXTI_SINGLE_LINE(__LINE__)                           ((__LINE__) <= EXTI_LINE_TKEY)
                                                                
#define IS_EXTI_MODE(__MODE__)		                            (((__MODE__) == EXTI_MODE_IT_RISING)            || \
                                                                 ((__MODE__) == EXTI_MODE_IT_FALLING)           || \
                                                                 ((__MODE__) == EXTI_MODE_IT_RISING_FALLING)    || \
                                                                 ((__MODE__) == EXTI_MODE_EVT_RISING)           || \
                                                                 ((__MODE__) == EXTI_MODE_EVT_FALLING)          || \
                                                                 ((__MODE__) == EXTI_MODE_EVT_RISING_FALLING))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

void HAL_EXTI_IRQHandler(uint32_t Line);
void HAL_EXTI_LineCallback(uint32_t Line);
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(GPIO_TypeDef *GPIOx, uint32_t Line, uint32_t Mode);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(uint32_t Line);
FunctionalState HAL_EXTI_IsConfigLine(GPIO_TypeDef *GPIOx, uint32_t Line);
void HAL_EXTI_GenerateSWI(uint32_t Line);
FlagStatus HAL_EXTI_GetPending(uint32_t Line);
void HAL_EXTI_ClearPending(uint32_t Line);
void HAL_EXTI_ClearAllPending(void);



#endif

