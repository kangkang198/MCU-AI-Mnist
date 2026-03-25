
/******************************************************************************
*@file  : hal_iwdt.h
*@brief : Header file of IWDT HAL module.
******************************************************************************/

#ifndef __HAL_IWDT_H__
#define __HAL_IWDT_H__

#include "hal.h"


/**
  * @brief   IWDT Init structure definition
  */
  
typedef struct
{
    uint32_t Prescaler;     /*!< Select the prescaler of the IWDT.
                                 This parameter can be any value of @ref IWDT_Clock_Prescaler */
    
    uint32_t Reload;        /*!< Specifies the IWDT down-counter reload value.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 0x0FFF */
    
    uint32_t Window;        /*!< Specifies the window value to be compared to the down-counter.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 0x0FFF */
    
    uint32_t Wakeup;        /*!< Specifies the wakeup value to be compared to the down-counter.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 0x0FFF */
    
    uint32_t WakeupMode;    /*!< Configure the wake-up mode of IWDT.
                                 This parameter can be any value of @ref IWDT_Wakeup_Mode */
    
} IWDT_InitTypeDef;

/**
  * @brief   IWDT Handle Structure definition
  */
  
typedef struct
{
    IWDT_TypeDef        *Instance;  /*!< Register base address    */
    
    IWDT_InitTypeDef    Init;       /*!< IWDT required parameters */
    
} IWDT_HandleTypeDef;


/** @defgroup IWDT_Cmd
  * @{
  */

#define IWDT_CMD_ENABLE                 ( 0xCCCCU )
#define IWDT_CMD_WRITE_ENABLE           ( 0x5555U )
#define IWDT_CMD_WAKEUP_ENABLE          ( 0x6666U )
#define IWDT_CMD_WAKEUP_DISABLE         ( 0x9999U )
#define IWDT_CMD_RELOAD                 ( 0xAAAAU )
#define IWDT_CMD_DISABLE                ( 0xEF01ABCDU )

/**
  * @}
  */
/** @defgroup IWDT_Clock_Prescaler
  * @{
  */

#define IWDT_CLOCK_PRESCALER_4          ( 0U )
#define IWDT_CLOCK_PRESCALER_8          ( 1U )
#define IWDT_CLOCK_PRESCALER_16         ( 2U )
#define IWDT_CLOCK_PRESCALER_32         ( 3U )
#define IWDT_CLOCK_PRESCALER_64         ( 4U )
#define IWDT_CLOCK_PRESCALER_128        ( 5U )
#define IWDT_CLOCK_PRESCALER_256        ( 6U )
#define IWDT_CLOCK_PRESCALER_256_1      ( 7U )

/**
  * @}
  */
  
/** @defgroup IWDT_Wakeup_Mode
  * @{
  */

#define  IWDT_WAKEUP_MODE_IT            ( EXTI_MODE_IT_RISING )
#define  IWDT_WAKEUP_MODE_EVENT         ( EXTI_MODE_EVT_RISING )

/**
  * @}
  */
  
/** @defgroup IWDT_Flag
  * @{
  */

#define  IWDT_FLAG_PVU                  ( IWDT_SR_PVU )
#define  IWDT_FLAG_RVU                  ( IWDT_SR_RVU )
#define  IWDT_FLAG_WVU                  ( IWDT_SR_WVU )
#define  IWDT_FLAG_WTU                  ( IWDT_SR_WTU )
#define  IWDT_FLAG_RLF                  ( IWDT_SR_RLF )

/**
  * @}
  */
  
/**
  * @brief   IWDT EXTI Line number
  */
  
#define  IWDT_EXTI_LINE                 ( EXTI_LINE_IWDT )

/**
  * @brief   IWDT down-counter reload max value
  */
  
#define IWDT_RELOAD_MAX_VALUE           ( 0x0FFFU )


/** @defgroup IWDT_TIMEOUT
  * @{
  */
  
#define IWDT_PVU_TIMEOUT                ( 30U )
#define IWDT_RVU_TIMEOUT                ( 30U )
#define IWDT_WVU_TIMEOUT                ( 30U )
#define IWDT_WTU_TIMEOUT                ( 30U )
#define IWDT_RLF_TIMEOUT                ( 30U )

/**
  * @}
  */
  

/** @defgroup  IWDT Private Macros
  * @{
  */
  
#define IS_IWDT_HANDLE(__HANDLE__)              ((__HANDLE__) != NULL)
#define IS_IWDT_ALL_INSTANCE(__INSTANCE__)      ((__INSTANCE__) == IWDT)

#define IS_IWDT_PRESCALER(__PRESCALER__)        (((__PRESCALER__) == IWDT_CLOCK_PRESCALER_4)  || \
                                                 ((__PRESCALER__) == IWDT_CLOCK_PRESCALER_8)  || \
                                                 ((__PRESCALER__) == IWDT_CLOCK_PRESCALER_16) || \
                                                 ((__PRESCALER__) == IWDT_CLOCK_PRESCALER_32) || \
                                                 ((__PRESCALER__) == IWDT_CLOCK_PRESCALER_64) || \
                                                 ((__PRESCALER__) == IWDT_CLOCK_PRESCALER_128)|| \
                                                 ((__PRESCALER__) == IWDT_CLOCK_PRESCALER_256)|| \
                                                 ((__PRESCALER__) == IWDT_CLOCK_PRESCALER_256_1))

#define IS_IWDT_WAKEUPMODE(__MODE__)            (((__MODE__) == IWDT_WAKEUP_MODE_IT)  || \
                                                 ((__MODE__) == IWDT_WAKEUP_MODE_EVENT))

#define IS_IWDT_RELOAD(__RELOAD__)              ((__RELOAD__) <= IWDT_RELOAD_MAX_VALUE)

#define IS_IWDT_WINDOW(__WINDOW__)              ((__WINDOW__) <= IWDT_RELOAD_MAX_VALUE)

#define IS_IWDT_WAKEUP(__WAKEUP__)              ((__WAKEUP__) <= IWDT_RELOAD_MAX_VALUE)

/**
  * @}
  */
  
/* Exported functions --------------------------------------------------------*/

void HAL_IWDT_IRQHandler(IWDT_HandleTypeDef *hiwdt);

void HAL_IWDT_Callback(IWDT_HandleTypeDef *hiwdt);

HAL_StatusTypeDef HAL_IWDT_Init(IWDT_HandleTypeDef * hidt);

void HAL_IWDT_MspInit(IWDT_HandleTypeDef * hiwdt);

HAL_StatusTypeDef HAL_IWDT_Refresh(IWDT_HandleTypeDef *hiwdt);

FlagStatus HAL_IWDT_GetPending(void);

void HAL_IWDT_ClearPending(void);



#endif
