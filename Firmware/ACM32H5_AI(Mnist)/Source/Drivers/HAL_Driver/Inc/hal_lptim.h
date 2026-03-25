/*
  ******************************************************************************
  * @file    hal_lptim.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of LPTIM HAL module.
  ******************************************************************************
*/

#ifndef __HAL_LPTIM_H__
#define __HAL_LPTIM_H__ 

#include "hal.h"

/**
  * @brief  LPTIM Initialization Structure definition
  */

typedef struct
{
    uint32_t                        ClockSource;            /*!< Selects the clock source.
                                                                 This parameter can be a value of @ref LPTIM_ClockSource         */

    uint32_t                        ClockPrescaler;         /*!< Specifies the counter clock Prescaler.
                                                                 Note: This parameter is invalid when the internal clock source is 
                                                                       selected and the external input1 is selected as the count signal.
                                                                 Note: This parameter is invalid when encoder mode is selected.
                                                                 This parameter can be a value of @ref LPTIM_ClockPrescaler      */

    
    uint32_t                        TriggerSource;          /*!< Selects the Trigger source.
                                                                 This parameter can be a value of @ref LPTIM_TriggerSource */

    
    uint32_t                        TriggerFilter;          /*!< Selects the trigger sampling time to configure the clock glitch filter.
                                                                 Note: This parameter is used only when the internal clock source is 
                                                                       selected and an external trigger is used.
                                                                 This parameter can be a value of @ref LPTIM_TriggerFilter  */
    
    
    uint32_t                        TriggerPolarity;        /*!< Selects the Trigger active edge.
                                                                 Note: This parameter is used only when the internal clock source is 
                                                                       selected and an external trigger is used.
                                                                 This parameter can be a value of @ref LPTIM_TriggerPolarity */

    uint32_t                        CounterSource;          /*!< Specifies whether the counter is incremented each internal event
                                                                 or each external event.
                                                                 Note: When external clock source is selected, this parameter is invalid, 
                                                                       and external events are forced to be selected
                                                                 This parameter can be a value of @ref LPTIM_CounterSource */

    uint32_t                        CounterFilter;          /*!< Selects the clock sampling time to configure the clock glitch filter.
                                                                 Note: This parameter is only used when the internal clock source is 
                                                                       selected and the external input1 is selected as the count signal.
                                                                 This parameter can be a value of @ref LPTIM_CounterFilter */

    
    uint32_t                        CounterPolarity;        /*!< Selects the polarity of the active edge for the counter unit
                                                                 if the external input1 is selected.
                                                                 Note: This parameter is used in two cases: one is to select an internal 
                                                                       clock source and external input1 as the count signal, and the  
                                                                       other is to select an external clock source. The 'both edge' is 
                                                                       only available in the first case.
                                                                 This parameter can be a value of @ref LPTIM_CounterPolarity */

    uint32_t                        Input1Source;           /*!< Specifies source selected for input1.
                                                                 This parameter can be a value of @ref LPTIM_Input1Source */

    uint32_t                        Input2Source;           /*!< Specifies source selected for input2.
                                                                 Note: This parameter is used only for encoder feature.
                                                                 This parameter can be a value of @ref LPTIM_Input2Source */

    uint32_t                        UpdateMode;             /*!< Specifies whether the update of the autoreload and the compare values and 
                                                                 repetition counter values is done immediately or after the end of current period.
                                                                 This parameter can be a value of @ref LPTIM_UpdatingMode */

    uint32_t                        WaveformPolarity;       /*!< Specifies the Output polarity.
                                                                 This parameter can be a value of @ref LPTIM_WaveformPolarity */

} LPTIM_InitTypeDef;



/**
  * @brief  LPTIM handle Structure definition
  */

typedef struct __LPTIM_HandleTypeDef
{
    LPTIM_TypeDef               *Instance;                                      /*!< Register base address     */
	uint32_t                    WakeUpLine;
    LPTIM_InitTypeDef           Init;                                           /*!< LPTIM required parameters */

    void (* CompareMatchCallback)(struct __LPTIM_HandleTypeDef *hlptim);        /*!< Compare match Callback                       */
    void (* AutoReloadMatchCallback)(struct __LPTIM_HandleTypeDef *hlptim);     /*!< Auto-reload match Callback                   */
    void (* TriggerCallback)(struct __LPTIM_HandleTypeDef *hlptim);             /*!< External trigger event detection Callback    */
    void (* CompareWriteCallback)(struct __LPTIM_HandleTypeDef *hlptim);        /*!< Compare register write complete Callback     */
    void (* AutoReloadWriteCallback)(struct __LPTIM_HandleTypeDef *hlptim);     /*!< Auto-reload register write complete Callback */
    void (* DirectionUpCallback)(struct __LPTIM_HandleTypeDef *hlptim);         /*!< Up-counting direction change Callback        */
    void (* DirectionDownCallback)(struct __LPTIM_HandleTypeDef *hlptim);       /*!< Down-counting direction change Callback      */
    void (* RepetitionUpdateCallback)(struct __LPTIM_HandleTypeDef *hlptim);    /*!< Repetition counter Update event occurs Callback    */
    void (* RepetitionWriteCallback)(struct __LPTIM_HandleTypeDef *hlptim);     /*!< Repetition counter register write complete Callback    */

    uint32_t                    RepetitionCounter;
    uint32_t                    AutoReload;
    uint32_t                    Compare;
} LPTIM_HandleTypeDef;

/**
  * @defgroup  LPTIM_CallbackID
  * @{
  */

#define LPTIM_CALLBACKID_COMPARE_MATCH                      ( 0U )              /*!< Compare match Callback ID                        */
#define LPTIM_CALLBACKID_AUTORELOAD_MATCH                   ( 1U )              /*!< Auto-reload match Callback ID                    */
#define LPTIM_CALLBACKID_TRIGGER                            ( 2U )              /*!< External trigger event detection Callback ID     */
#define LPTIM_CALLBACKID_COMPARE_WRITE                      ( 3U )              /*!< Compare register write complete Callback ID      */
#define LPTIM_CALLBACKID_AUTORELOAD_WRITE                   ( 4U )              /*!< Auto-reload register write complete Callback ID  */
#define LPTIM_CALLBACKID_DIRECTION_UP                       ( 5U )              /*!< Up-counting direction change Callback ID         */
#define LPTIM_CALLBACKID_DIRECTION_DOWN                     ( 6U )              /*!< Down-counting direction change Callback ID       */
#define LPTIM_CALLBACKID_REPETITION_UPDATE                  ( 7U )              /*!< Update event occurs Callback ID                  */
#define LPTIM_CALLBACKID_REPETITION_WRITE                   ( 8U )              /*!< Repeat register write complete Callback ID       */

/**
  * @}
  */

/**
  * @brief  HAL TIM Callback pointer definition
  */

typedef  void (*pLPTIM_CallbackTypeDef)(LPTIM_HandleTypeDef *hlptim);  /*!< pointer to the LPTIM callback function */


/**
  * @defgroup  LPTIM_State
  * @{
  */
  
#define HAL_LPTIM_STATE_READY                               ( 0U )
#define HAL_LPTIM_STATE_BUSY                                ( 1U )

/**
  * @}
  */





/** @defgroup LPTIM_ClockSource
  * @{
  */
  
#define LPTIM_CLOCKSOURCE_INTERNAL_PCLK                         ( 0 )
#define LPTIM_CLOCKSOURCE_INTERNAL_RCL                        ( 1 )
#define LPTIM_CLOCKSOURCE_INTERNAL_RCH                        ( 2 )
#define LPTIM_CLOCKSOURCE_INTERNAL_XTL                          ( 3 )
#define LPTIM_CLOCKSOURCE_EXTERNAL_INPUT1                       ( 4 )

/**
  * @}
  */

/** @defgroup LPTIM_ClockPrescaler
  * @{
  */
  
#define LPTIM_CLOCKPRESCALER_DIV1                               ( 0U )
#define LPTIM_CLOCKPRESCALER_DIV2                               ( LPTIM_CFGR1_PRESC_0 )
#define LPTIM_CLOCKPRESCALER_DIV4                               ( LPTIM_CFGR1_PRESC_1 )
#define LPTIM_CLOCKPRESCALER_DIV8                               ( LPTIM_CFGR1_PRESC_0 | LPTIM_CFGR1_PRESC_1 )
#define LPTIM_CLOCKPRESCALER_DIV16                              ( LPTIM_CFGR1_PRESC_2 )
#define LPTIM_CLOCKPRESCALER_DIV32                              ( LPTIM_CFGR1_PRESC_0 | LPTIM_CFGR1_PRESC_2 )
#define LPTIM_CLOCKPRESCALER_DIV64                              ( LPTIM_CFGR1_PRESC_1 | LPTIM_CFGR1_PRESC_2 )
#define LPTIM_CLOCKPRESCALER_DIV128                             ( LPTIM_CFGR1_PRESC )

/**
  * @}
  */

/** @defgroup LPTIM_CounterPolarity
  * @{
  */
  
#define LPTIM_COUNTERPOLARITY_RISING                              ( 0U )
#define LPTIM_COUNTERPOLARITY_FALLING                             ( LPTIM_CFGR1_CKPOL_0 )
#define LPTIM_COUNTERPOLARITY_RISING_FALLING                      ( LPTIM_CFGR1_CKPOL_1 )

/**
  * @}
  */

/** @defgroup LPTIM_CounterFilter
  * @{
  */
  
#define LPTIM_COUNTERFILTER_DISABLE                               ( 0U )
#define LPTIM_COUNTERFILTER_CLK2                                  ( LPTIM_CFGR1_CKFLT_0 )
#define LPTIM_COUNTERFILTER_CLK4                                  ( LPTIM_CFGR1_CKFLT_1 )
#define LPTIM_COUNTERFILTER_CLK8                                  ( LPTIM_CFGR1_CKFLT )

/**
  * @}
  */

/** @defgroup LPTIM_TriggerSource
  * @{
  */
  
#define LPTIM_TRIGSOURCE_SOFTWARE                               ( 0x0000FFFFU )
#define LPTIM_TRIGSOURCE_0                                      ( 0U )
#define LPTIM_TRIGSOURCE_1                                      ( LPTIM_CFGR1_TRIGSEL_0 )
#define LPTIM_TRIGSOURCE_2                                      ( LPTIM_CFGR1_TRIGSEL_1 )
#define LPTIM_TRIGSOURCE_3                                      ( LPTIM_CFGR1_TRIGSEL_1 | LPTIM_CFGR1_TRIGSEL_0 )

#define LPTIM_TRIGSOURCE_4                                      ( LPTIM_CFGR1_TRIGSEL_2 )
#define LPTIM_TRIGSOURCE_5                                      ( LPTIM_CFGR1_TRIGSEL_2 | LPTIM_CFGR1_TRIGSEL_0 )
#define LPTIM_TRIGSOURCE_6                                      ( LPTIM_CFGR1_TRIGSEL_2 | LPTIM_CFGR1_TRIGSEL_1 )
#define LPTIM_TRIGSOURCE_7                                      ( LPTIM_CFGR1_TRIGSEL_2 | LPTIM_CFGR1_TRIGSEL_1 | LPTIM_CFGR1_TRIGSEL_0 )

#define LPTIM_TRIGSOURCE_8                                      ( LPTIM_CFGR1_TRIGSEL_3 )
#define LPTIM_TRIGSOURCE_9                                      ( LPTIM_CFGR1_TRIGSEL_3 | LPTIM_CFGR1_TRIGSEL_0 )
#define LPTIM_TRIGSOURCE_10                                     ( LPTIM_CFGR1_TRIGSEL_3 | LPTIM_CFGR1_TRIGSEL_1 )
#define LPTIM_TRIGSOURCE_11                                     ( LPTIM_CFGR1_TRIGSEL_3 | LPTIM_CFGR1_TRIGSEL_1 | LPTIM_CFGR1_TRIGSEL_0 )
#define LPTIM_TRIGSOURCE_12                                     ( LPTIM_CFGR1_TRIGSEL_3 | LPTIM_CFGR1_TRIGSEL_2 )
#define LPTIM_TRIGSOURCE_13                                     ( LPTIM_CFGR1_TRIGSEL_3 | LPTIM_CFGR1_TRIGSEL_2 |LPTIM_CFGR1_TRIGSEL_0)
#define LPTIM_TRIGSOURCE_14                                     ( LPTIM_CFGR1_TRIGSEL_3 | LPTIM_CFGR1_TRIGSEL_2 |LPTIM_CFGR1_TRIGSEL_1)
#define LPTIM_TRIGSOURCE_15                                     ( LPTIM_CFGR1_TRIGSEL_3 | LPTIM_CFGR1_TRIGSEL_2 |LPTIM_CFGR1_TRIGSEL_1|LPTIM_CFGR1_TRIGSEL_0)


/**
  * @}
  */

/** @defgroup LPTIM_TriggerPolarity
  * @{
  */
  
#define LPTIM_TRIGPOLARITY_RISING                               ( LPTIM_CFGR1_TRIGEN_0 )
#define LPTIM_TRIGPOLARITY_FALLING                              ( LPTIM_CFGR1_TRIGEN_1 )
#define LPTIM_TRIGPOLARITY_RISING_FALLING                       ( LPTIM_CFGR1_TRIGEN_1 | LPTIM_CFGR1_TRIGEN_0 )

/**
  * @}
  */

/** @defgroup LPTIM_TriggerFilter
  * @{
  */
  
#define LPTIM_TRIGFILTER_DISABLE                                ( 0U )
#define LPTIM_TRIGFILTER_2CLK                                   ( LPTIM_CFGR1_TRGFLT_0 )
#define LPTIM_TRIGFILTER_4CLK                                   ( LPTIM_CFGR1_TRGFLT_1 )
#define LPTIM_TRIGFILTER_8CLK                                   ( LPTIM_CFGR1_TRGFLT_1 | LPTIM_CFGR1_TRGFLT_0 )

/**
  * @}
  */


/** @defgroup LPTIM_WaveformPolarity
  * @{
  */

#define LPTIM_WAVEFORMPOLARITY_HIGH                             ( 0U )
#define LPTIM_WAVEFORMPOLARITY_LOW                              ( LPTIM_CFGR1_WAVPOL )

/**
  * @}
  */

/** @defgroup LPTIM_UpdatingMode
  * @{
  */

#define LPTIM_UPDATE_IMMEDIATE                                  ( 0U )
#define LPTIM_UPDATE_ENDOFPERIOD                                ( LPTIM_CFGR1_PRELOAD )

/**
  * @}
  */

/** @defgroup LPTIM_CounterSource
  * @{
  */

#define LPTIM_COUNTERSOURCE_INTERNAL                            ( 0U )
#define LPTIM_COUNTERSOURCE_EXTERNAL                            ( LPTIM_CFGR1_COUNTMODE )

/**
  * @}
  */

/** @defgroup LPTIM_Input1_Source LPTIM Input1 Source
  * @{
  */

#define LPTIM_INPUT1SOURCE_0                                    ( 0U )
#define LPTIM_INPUT1SOURCE_1                                    ( LPTIM_CFGR2_IN1SEL_0 )
#define LPTIM_INPUT1SOURCE_2                                    ( LPTIM_CFGR2_IN1SEL_1 )
#define LPTIM_INPUT1SOURCE_3                                    ( LPTIM_CFGR2_IN1SEL_1 | LPTIM_CFGR2_IN1SEL_0 )

#define LPTIM_INPUT1SOURCE_4                                    ( LPTIM_CFGR2_IN1SEL_2 )
#define LPTIM_INPUT1SOURCE_5                                    ( LPTIM_CFGR2_IN1SEL_2 | LPTIM_CFGR2_IN1SEL_0 )
#define LPTIM_INPUT1SOURCE_6                                    ( LPTIM_CFGR2_IN1SEL_2 | LPTIM_CFGR2_IN1SEL_1 )
#define LPTIM_INPUT1SOURCE_7                                    ( LPTIM_CFGR2_IN1SEL_2 | LPTIM_CFGR2_IN1SEL_1 | LPTIM_CFGR2_IN1SEL_0 )

#define LPTIM_INPUT1SOURCE_8                                    ( LPTIM_CFGR2_IN1SEL_3 )
#define LPTIM_INPUT1SOURCE_9                                    ( LPTIM_CFGR2_IN1SEL_3 | LPTIM_CFGR2_IN1SEL_0 )
#define LPTIM_INPUT1SOURCE_10                                    ( LPTIM_CFGR2_IN1SEL_3 | LPTIM_CFGR2_IN1SEL_1 )
#define LPTIM_INPUT1SOURCE_11                                    ( LPTIM_CFGR2_IN1SEL_3 | LPTIM_CFGR2_IN1SEL_1 | LPTIM_CFGR2_IN1SEL_0 )
#define LPTIM_INPUT1SOURCE_12                                    ( LPTIM_CFGR2_IN1SEL_3 | LPTIM_CFGR2_IN1SEL_2 )
#define LPTIM_INPUT1SOURCE_13                                    ( LPTIM_CFGR2_IN1SEL_3 | LPTIM_CFGR2_IN1SEL_2 | LPTIM_CFGR2_IN1SEL_0 )
#define LPTIM_INPUT1SOURCE_14                                    ( LPTIM_CFGR2_IN1SEL_3 | LPTIM_CFGR2_IN1SEL_2 | LPTIM_CFGR2_IN1SEL_1 )
#define LPTIM_INPUT1SOURCE_15                                    ( LPTIM_CFGR2_IN1SEL_3 | LPTIM_CFGR2_IN1SEL_2 | LPTIM_CFGR2_IN1SEL_1 | LPTIM_CFGR2_IN1SEL_0 )

/**
  * @}
  */

/** @defgroup LPTIM_Input2_Source LPTIM Input2 Source
  * @{
  */

#define LPTIM_INPUT2SOURCE_0                                    ( 0U )
#define LPTIM_INPUT2SOURCE_1                                    ( LPTIM_CFGR2_IN2SEL_0 )
#define LPTIM_INPUT2SOURCE_2                                    ( LPTIM_CFGR2_IN2SEL_1 )
#define LPTIM_INPUT2SOURCE_3                                    ( LPTIM_CFGR2_IN2SEL_1 | LPTIM_CFGR2_IN2SEL_0 )

#define LPTIM_INPUT2SOURCE_4                                    ( LPTIM_CFGR2_IN2SEL_2 )
#define LPTIM_INPUT2SOURCE_5                                    ( LPTIM_CFGR2_IN2SEL_2 | LPTIM_CFGR2_IN2SEL_0 )
#define LPTIM_INPUT2SOURCE_6                                    ( LPTIM_CFGR2_IN2SEL_2 | LPTIM_CFGR2_IN2SEL_1 )
#define LPTIM_INPUT2SOURCE_7                                    ( LPTIM_CFGR2_IN2SEL_2 | LPTIM_CFGR2_IN2SEL_1 | LPTIM_CFGR2_IN2SEL_0 )

#define LPTIM_INPUT2SOURCE_8                                    ( LPTIM_CFGR2_IN2SEL_3 )
#define LPTIM_INPUT2SOURCE_9                                    ( LPTIM_CFGR2_IN2SEL_3 | LPTIM_CFGR2_IN2SEL_0 )
#define LPTIM_INPUT2SOURCE_10                                    ( LPTIM_CFGR2_IN2SEL_3 | LPTIM_CFGR2_IN2SEL_1 )
#define LPTIM_INPUT2SOURCE_11                                    ( LPTIM_CFGR2_IN2SEL_3 | LPTIM_CFGR2_IN2SEL_1 | LPTIM_CFGR2_IN2SEL_0 )
#define LPTIM_INPUT2SOURCE_12                                    ( LPTIM_CFGR2_IN2SEL_3 | LPTIM_CFGR2_IN2SEL_2 )
#define LPTIM_INPUT2SOURCE_13                                    ( LPTIM_CFGR2_IN2SEL_3 | LPTIM_CFGR2_IN2SEL_2 | LPTIM_CFGR2_IN2SEL_0 )
#define LPTIM_INPUT2SOURCE_14                                    ( LPTIM_CFGR2_IN2SEL_3 | LPTIM_CFGR2_IN2SEL_2 | LPTIM_CFGR2_IN2SEL_1 )
#define LPTIM_INPUT2SOURCE_15                                    ( LPTIM_CFGR2_IN2SEL_3 | LPTIM_CFGR2_IN2SEL_2 | LPTIM_CFGR2_IN2SEL_1 | LPTIM_CFGR2_IN2SEL_0 )


/**
  * @}
  */


/** @defgroup LPTIM_Flags
  * @{
  */

#define LPTIM_FLAG_REPOK                                        ( LPTIM_ISR_REPOK )
#define LPTIM_FLAG_REPUE                                        ( LPTIM_ISR_REPUE )
#define LPTIM_FLAG_DOWN                                         ( LPTIM_ISR_DOWN )
#define LPTIM_FLAG_UP                                           ( LPTIM_ISR_UP )
#define LPTIM_FLAG_ARROK                                        ( LPTIM_ISR_ARROK )
#define LPTIM_FLAG_CMPOK                                        ( LPTIM_ISR_CMPOK )
#define LPTIM_FLAG_EXTTRIG                                      ( LPTIM_ISR_EXTTRIG )
#define LPTIM_FLAG_ARRM                                         ( LPTIM_ISR_ARRM )
#define LPTIM_FLAG_CMPM                                         ( LPTIM_ISR_CMPM )

/**
  * @}
  */

/** @defgroup LPTIM_IT
  * @{
  */
  
#define LPTIM_IT_REPOK                                          ( LPTIM_IER_REPOKIE )
#define LPTIM_IT_REPUE                                          ( LPTIM_IER_REPUEIE )
#define LPTIM_IT_DOWN                                           ( LPTIM_IER_DOWNIE )
#define LPTIM_IT_UP                                             ( LPTIM_IER_UPIE )
#define LPTIM_IT_ARROK                                          ( LPTIM_IER_ARROKIE )
#define LPTIM_IT_CMPOK                                          ( LPTIM_IER_CMPOKIE )
#define LPTIM_IT_EXTTRIG                                        ( LPTIM_IER_EXTTRIGIE )
#define LPTIM_IT_ARRM                                           ( LPTIM_IER_ARRMIE )
#define LPTIM_IT_CMPM                                           ( LPTIM_IER_CMPMIE )

/**
  * @}
  */

/** @brief  IT mask for assert test
  */
#define LPTIM_IT_MASK                                           ( LPTIM_IT_REPOK | LPTIM_IT_REPUE | LPTIM_IT_DOWN | \
                                                                  LPTIM_IT_UP | LPTIM_IT_ARROK | LPTIM_IT_CMPOK   | \
                                                                  LPTIM_IT_EXTTRIG | LPTIM_IT_ARRM | LPTIM_IT_CMPM )
                                                                  
                                                                  

/* Exported macros -----------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Macros LPTIM Exported Macros
  * @{
  */

/**
  * @brief  Enable the LPTIM peripheral.
  * @param  __HANDLE__ LPTIM handle
  * @retval None
  */
  
#define __HAL_LPTIM_ENABLE(__HANDLE__)                                  ((__HANDLE__)->Instance->CR |= (LPTIM_CR_ENABLE))

/**
  * @brief  Disable the LPTIM peripheral.
  * @param  __HANDLE__ LPTIM handle.
  * @retval None
  */
  
#define __HAL_LPTIM_DISABLE(__HANDLE__)                                 LPTIM_Disable(__HANDLE__)

/**
  * @brief  Start the LPTIM peripheral in Continuous mode.
  * @param  __HANDLE__ LPTIM handle
  * @retval None
  */
  
#define __HAL_LPTIM_START_CONTINUOUS(__HANDLE__)                        ((__HANDLE__)->Instance->CR |=  LPTIM_CR_CNTSTRT)

/**
  * @brief  Start the LPTIM peripheral in single mode.
  * @param  __HANDLE__ LPTIM handle
  * @retval None
  */
  
#define __HAL_LPTIM_START_SINGLE(__HANDLE__)                            ((__HANDLE__)->Instance->CR |=  LPTIM_CR_SNGSTRT)

/**
  * @brief  Reset the LPTIM Counter register in synchronous mode.
  * @param  __HANDLE__ LPTIM handle
  * @retval None
  */
  
#define __HAL_LPTIM_RESET_COUNTER(__HANDLE__)                           ((__HANDLE__)->Instance->CR |=  LPTIM_CR_COUNTRST)

/**
  * @brief  Enable Reset after read of the LPTIM Counter register in asynchronous mode.
  * @param  __HANDLE__ LPTIM handle
  * @retval None
  */
  
#define __HAL_LPTIM_RESET_COUNTER_AFTER_READ_ENABLE(__HANDLE__)         ((__HANDLE__)->Instance->CR |=  LPTIM_CR_RSTARE)
 
/**
  * @brief  Disable Reset after read of the LPTIM Counter register in asynchronous mode.
  * @param  __HANDLE__ LPTIM handle
  * @retval None
  */
  
#define __HAL_LPTIM_RESET_COUNTER_AFTER_READ_DISABLE(__HANDLE__)        ((__HANDLE__)->Instance->CR &=  ~LPTIM_CR_RSTARE)

/**
  * @brief  Return the current Autoreload (Period) value.
  * @param  __HANDLE__ LPTIM handle
  * @retval Autoreload value
  */
  
#define __HAL_LPTIM_GET_AUTORELOAD(__HANDLE__)                          ((__HANDLE__)->Instance->ARR)

/**
  * @brief  Write the passed parameter in the Autoreload register.
  * @param  __HANDLE__ LPTIM handle
  * @param  __VALUE__ Autoreload value
  * @retval None
  * @note   The ARR register can only be modified when the LPTIM instance is enabled.
  */
  
#define __HAL_LPTIM_SET_AUTORELOAD(__HANDLE__ , __VALUE__)              ((__HANDLE__)->Instance->ARR =  (__VALUE__))

/**
  * @brief  Return the current Compare (Pulse/Timeout) value.
  * @param  __HANDLE__ LPTIM handle
  * @retval Compare value
  * @note   The CMP register can only be modified when the LPTIM instance is enabled.
  */
  
#define __HAL_LPTIM_GET_COMPARE(__HANDLE__)                             ((__HANDLE__)->Instance->CMP)

/**
  * @brief  Write the passed parameter in the Compare register.
  * @param  __HANDLE__ LPTIM handle
  * @param  __VALUE__ Compare value
  * @retval None
  * @note   The CMP register can only be modified when the LPTIM instance is enabled.
  */
  
#define __HAL_LPTIM_SET_COMPARE(__HANDLE__ , __VALUE__)                 ((__HANDLE__)->Instance->CMP =  (__VALUE__))

/**
  * @brief  Return the current Repetition Counter value.
  * @param  __HANDLE__ LPTIM handle
  * @retval Repetition Counter value
  */
  
#define __HAL_LPTIM_GET_REPETITION_COUNTER(__HANDLE__)                  ((__HANDLE__)->Instance->RCR)

/**
  * @brief  Write the passed parameter in the repetition counter register.
  * @param  __HANDLE__ LPTIM handle
  * @param  __VALUE__ Repetition counter value
  * @retval None
  * @note   The RCR register can only be modified when the LPTIM instance is enabled.
  */
  
#define __HAL_LPTIM_SET_REPETITION_COUNTER(__HANDLE__ , __VALUE__)      ((__HANDLE__)->Instance->RCR =  (__VALUE__))

/**
  * @brief  Return the current Counter value.
  * @param  __HANDLE__ LPTIM handle
  * @retval Counter value
  */
  
#define __HAL_LPTIM_GET_COUNTER(__HANDLE__)                             ((__HANDLE__)->Instance->RCR)

/**
  * @brief  Check whether the specified LPTIM flag is set or not.
  * @param  __HANDLE__ LPTIM handle
  * @param  __FLAG__ LPTIM flag to check
  *            This parameter can be a value of:
  *            @arg LPTIM_FLAG_REPOK   : Repeat register update OK up Flag.
  *            @arg LPTIM_FLAG_REPUE   : Update events occurs up Flag.
  *            @arg LPTIM_FLAG_DOWN    : Counter direction change up Flag.
  *            @arg LPTIM_FLAG_UP      : Counter direction change down to up Flag.
  *            @arg LPTIM_FLAG_ARROK   : Autoreload register update OK Flag.
  *            @arg LPTIM_FLAG_CMPOK   : Compare register update OK Flag.
  *            @arg LPTIM_FLAG_EXTTRIG : External trigger edge event Flag.
  *            @arg LPTIM_FLAG_ARRM    : Autoreload match Flag.
  *            @arg LPTIM_FLAG_CMPM    : Compare match Flag.
  * @retval The state of the specified flag (SET or RESET).
  */
  
#define __HAL_LPTIM_GET_FLAG(__HANDLE__, __FLAG__)                      ((__HANDLE__)->Instance->ISR &(__FLAG__))

/**
  * @brief  Clear the specified LPTIM flag.
  * @param  __HANDLE__ LPTIM handle.
  * @param  __FLAG__ LPTIM flag to clear.
  *            This parameter can be a combination of:
  *            @arg LPTIM_FLAG_REPOK   : Repeat register update OK up Flag.
  *            @arg LPTIM_FLAG_REPUE   : Update events occurs up Flag.
  *            @arg LPTIM_FLAG_DOWN    : Counter direction change up Flag.
  *            @arg LPTIM_FLAG_UP      : Counter direction change down to up Flag.
  *            @arg LPTIM_FLAG_ARROK   : Autoreload register update OK Flag.
  *            @arg LPTIM_FLAG_CMPOK   : Compare register update OK Flag.
  *            @arg LPTIM_FLAG_EXTTRIG : External trigger edge event Flag.
  *            @arg LPTIM_FLAG_ARRM    : Autoreload match Flag.
  *            @arg LPTIM_FLAG_CMPM    : Compare match Flag.
  * @retval None.
  */
  
#define __HAL_LPTIM_CLEAR_FLAG(__HANDLE__, __FLAG__)                    ((__HANDLE__)->Instance->ICR  = (__FLAG__))

/**
  * @brief  Enable the specified LPTIM interrupt.
  * @param  __HANDLE__ LPTIM handle.
  * @param  __INTERRUPT__ LPTIM interrupt to set.
  *            This parameter can be a combination of:
  *            @arg LPTIM_IT_REPOK   : Repeat register update OK up Interrupt.
  *            @arg LPTIM_IT_REPUE   : Update events occurs up Interrupt.
  *            @arg LPTIM_IT_DOWN    : Counter direction change up Interrupt.
  *            @arg LPTIM_IT_UP      : Counter direction change down to up Interrupt.
  *            @arg LPTIM_IT_ARROK   : Autoreload register update OK Interrupt.
  *            @arg LPTIM_IT_CMPOK   : Compare register update OK Interrupt.
  *            @arg LPTIM_IT_EXTTRIG : External trigger edge event Interrupt.
  *            @arg LPTIM_IT_ARRM    : Autoreload match Interrupt.
  *            @arg LPTIM_IT_CMPM    : Compare match Interrupt.
  * @retval None.
  * @note   The LPTIM interrupts can only be enabled when the LPTIM instance is disabled.
  */
  
#define __HAL_LPTIM_ENABLE_IT(__HANDLE__, __INTERRUPT__)                ((__HANDLE__)->Instance->IER  |= (__INTERRUPT__))

/**
  * @brief  Disable the specified LPTIM interrupt.
  * @param  __HANDLE__ LPTIM handle.
  * @param  __INTERRUPT__ LPTIM interrupt to set.
  *            This parameter can be a combination of:
  *            @arg LPTIM_IT_REPOK   : Repeat register update OK up Interrupt.
  *            @arg LPTIM_IT_REPUE   : Update events occurs up Interrupt.
  *            @arg LPTIM_IT_DOWN    : Counter direction change up Interrupt.
  *            @arg LPTIM_IT_UP      : Counter direction change down to up Interrupt.
  *            @arg LPTIM_IT_ARROK   : Autoreload register update OK Interrupt.
  *            @arg LPTIM_IT_CMPOK   : Compare register update OK Interrupt.
  *            @arg LPTIM_IT_EXTTRIG : External trigger edge event Interrupt.
  *            @arg LPTIM_IT_ARRM    : Autoreload match Interrupt.
  *            @arg LPTIM_IT_CMPM    : Compare match Interrupt.
  * @retval None.
  * @note   The LPTIM interrupts can only be disabled when the LPTIM instance is disabled.
  */
  
#define __HAL_LPTIM_DISABLE_IT(__HANDLE__, __INTERRUPT__)               ((__HANDLE__)->Instance->IER  &= (~(__INTERRUPT__)))

/**
  * @brief  Check whether the specified LPTIM interrupt source is enabled or not.
  * @param  __HANDLE__ LPTIM handle.
  * @param  __INTERRUPT__ LPTIM interrupt to check.
  *            This parameter can be a value of:
  *            @arg LPTIM_IT_REPOK   : Repeat register update OK up Interrupt.
  *            @arg LPTIM_IT_REPUE   : Update events occurs up Interrupt.
  *            @arg LPTIM_IT_DOWN    : Counter direction change up Interrupt.
  *            @arg LPTIM_IT_UP      : Counter direction change down to up Interrupt.
  *            @arg LPTIM_IT_ARROK   : Autoreload register update OK Interrupt.
  *            @arg LPTIM_IT_CMPOK   : Compare register update OK Interrupt.
  *            @arg LPTIM_IT_EXTTRIG : External trigger edge event Interrupt.
  *            @arg LPTIM_IT_ARRM    : Autoreload match Interrupt.
  *            @arg LPTIM_IT_CMPM    : Compare match Interrupt.
  * @retval Interrupt status.
  */

#define __HAL_LPTIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)            ((__HANDLE__)->Instance->IER & (__INTERRUPT__))

/**
  * @}
  */



/* Private macros ------------------------------------------------------------*/
/** @defgroup LPTIM_Private_Macros LPTIM Private Macros
  * @{
  */

#define IS_LPTIM_INSTANCE(__INSTANCE__)                         ((__INSTANCE__) == LPTIM1||\
																(__INSTANCE__) == LPTIM2||\
																(__INSTANCE__) == LPTIM3||\
																(__INSTANCE__) == LPTIM4||\
																(__INSTANCE__) == LPTIM5||\
																(__INSTANCE__) == LPTIM6)

#define IS_LPTIM_CLOCK_SOURCE(__SOURCE__)                       (((__SOURCE__) == LPTIM_CLOCKSOURCE_INTERNAL_PCLK) || \
                                                                 ((__SOURCE__) == LPTIM_CLOCKSOURCE_INTERNAL_RCL)  || \
                                                                 ((__SOURCE__) == LPTIM_CLOCKSOURCE_INTERNAL_RCH)  || \
                                                                 ((__SOURCE__) == LPTIM_CLOCKSOURCE_INTERNAL_XTL)  || \
                                                                 ((__SOURCE__) == LPTIM_CLOCKSOURCE_EXTERNAL_INPUT1))

#define IS_LPTIM_CLOCK_PRESCALER(__PRESCALER__)                 (((__PRESCALER__) ==  LPTIM_CLOCKPRESCALER_DIV1)  || \
                                                                 ((__PRESCALER__) ==  LPTIM_CLOCKPRESCALER_DIV2)  || \
                                                                 ((__PRESCALER__) ==  LPTIM_CLOCKPRESCALER_DIV4)  || \
                                                                 ((__PRESCALER__) ==  LPTIM_CLOCKPRESCALER_DIV8)  || \
                                                                 ((__PRESCALER__) ==  LPTIM_CLOCKPRESCALER_DIV16) || \
                                                                 ((__PRESCALER__) ==  LPTIM_CLOCKPRESCALER_DIV32) || \
                                                                 ((__PRESCALER__) ==  LPTIM_CLOCKPRESCALER_DIV64) || \
                                                                 ((__PRESCALER__) ==  LPTIM_CLOCKPRESCALER_DIV128))

#define IS_LPTIM_TRIG_SOURCE(__TRIG__)                          (((__TRIG__) == LPTIM_TRIGSOURCE_SOFTWARE) || \
                                                                 ((__TRIG__) >= LPTIM_TRIGSOURCE_0)        && \
                                                                 ((__TRIG__) <= LPTIM_TRIGSOURCE_15))

  
#define IS_LPTIM_TRIG_POLARITY(__POLARITY__)                    (((__POLARITY__) == LPTIM_TRIGPOLARITY_RISING)  || \
                                                                 ((__POLARITY__) == LPTIM_TRIGPOLARITY_FALLING) || \
                                                                 ((__POLARITY__) == LPTIM_TRIGPOLARITY_RISING_FALLING))
  
  
#define IS_LPTIM_TRIG_FILTER(__FILTER__)                        (((__FILTER__) == LPTIM_TRIGFILTER_DISABLE) || \
                                                                 ((__FILTER__) == LPTIM_TRIGFILTER_2CLK)    || \
                                                                 ((__FILTER__) == LPTIM_TRIGFILTER_4CLK)    || \
                                                                 ((__FILTER__) == LPTIM_TRIGFILTER_8CLK))
  
#define IS_LPTIM_COUNTER_SOURCE(__SOURCE__)                     (((__SOURCE__) == LPTIM_COUNTERSOURCE_INTERNAL) || \
                                                                 ((__SOURCE__) == LPTIM_COUNTERSOURCE_EXTERNAL))

  
#define IS_LPTIM_COUNTER_POLARITY(__POLARITY__)                 (((__POLARITY__) == LPTIM_COUNTERPOLARITY_RISING) || \
                                                                 ((__POLARITY__) == LPTIM_COUNTERPOLARITY_FALLING)  || \
                                                                 ((__POLARITY__) == LPTIM_COUNTERPOLARITY_RISING_FALLING))
                                                                 
     

#define IS_LPTIM_COUNTER_FILTER(__FILTER__)                     (((__FILTER__) == LPTIM_COUNTERFILTER_DISABLE) || \
                                                                 ((__FILTER__) == LPTIM_COUNTERFILTER_CLK2)    || \
                                                                 ((__FILTER__) == LPTIM_COUNTERFILTER_CLK4)    || \
                                                                 ((__FILTER__) == LPTIM_COUNTERFILTER_CLK8))
  
#define IS_LPTIM_WAVEFORM_POLARITY(__POLARITY__)                (((__POLARITY__) == LPTIM_WAVEFORMPOLARITY_LOW) || \
                                                                 ((__POLARITY__) == LPTIM_WAVEFORMPOLARITY_HIGH))


#define IS_LPTIM_UPDATE_MODE(__MODE__)                          (((__MODE__) == LPTIM_UPDATE_IMMEDIATE) || \
                                                                 ((__MODE__) == LPTIM_UPDATE_ENDOFPERIOD))

#define IS_LPTIM_AUTORELOAD(__AUTORELOAD__)                     (((__AUTORELOAD__) <= 0x0000FFFFUL) && ((__AUTORELOAD__) != 0UL))

#define IS_LPTIM_COMPARE(__COMPARE__)                           ((__COMPARE__) < 0x0000FFFFUL)

#define IS_LPTIM_PERIOD(__PERIOD__)                             IS_LPTIM_AUTORELOAD(__PERIOD__)

#define IS_LPTIM_PULSE(__PULSE__)                               IS_LPTIM_COMPARE(__PULSE__)

#define IS_LPTIM_TIMEOUT(__TIMEOUT__)                           IS_LPTIM_COMPARE(__TIMEOUT__)

#define IS_LPTIM_REPETITION_COUNTER(__COUNTER__)                ((__COUNTER__) <= 0xFFUL)

#define IS_LPTIM_INPUT1_SOURCE(__SOURCE__)                      (((__SOURCE__) >= LPTIM_INPUT1SOURCE_0) || \
                                                                 ((__SOURCE__) <= LPTIM_INPUT1SOURCE_15))


#define IS_LPTIM_INPUT2_SOURCE(__SOURCE__)                      (((__SOURCE__) >= LPTIM_INPUT2SOURCE_0) && \
                                                                 ((__SOURCE__) <= LPTIM_INPUT2SOURCE_15))
                                                                 
#define IS_LPTIM_IT(__IT__)                                     ((((uint32_t)(__IT__) &  LPTIM_IT_MASK) != 0x00u) && \
                                                                 (((uint32_t)(__IT__) & ~LPTIM_IT_MASK) == 0x00u))
                                                                 
                                                                 
#define IS_LPTIM_CALLBACKID(__CALLBACKID__)                     (((__CALLBACKID__) == HAL_LPTIM_COMPARE_MATCH_CB_ID)     ||\
                                                                 ((__CALLBACKID__) == HAL_LPTIM_AUTORELOAD_MATCH_CB_ID)  ||\
                                                                 ((__CALLBACKID__) == HAL_LPTIM_TRIGGER_CB_ID)           ||\
                                                                 ((__CALLBACKID__) == HAL_LPTIM_COMPARE_WRITE_CB_ID)     ||\
                                                                 ((__CALLBACKID__) == HAL_LPTIM_AUTORELOAD_WRITE_CB_ID)  ||\
                                                                 ((__CALLBACKID__) == HAL_LPTIM_DIRECTION_UP_CB_ID)      ||\
                                                                 ((__CALLBACKID__) == HAL_LPTIM_DIRECTION_DOWN_CB_ID)    ||\
                                                                 ((__CALLBACKID__) == HAL_LPTIM_REPETITION_UPDATE_CB_ID) ||\
                                                                 ((__CALLBACKID__) == HAL_LPTIM_REPETITION_WRITE_CB_ID))


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

void HAL_LPTIM_IRQHandler(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Init(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_DeInit(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef *hlptim);
void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_ConfigCountValue(LPTIM_HandleTypeDef *hlptim, uint8_t RepetitionCounter, \
                                             uint16_t Period, uint16_t PulseOrTimeout);
HAL_StatusTypeDef HAL_LPTIM_EnableIT(LPTIM_HandleTypeDef *hlptim, uint32_t IT);
HAL_StatusTypeDef HAL_LPTIM_DisableIT(LPTIM_HandleTypeDef *hlptim, uint32_t IT);
HAL_StatusTypeDef HAL_LPTIM_PWM_Start(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_PWM_Stop(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Start(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Stop(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Start(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Stop(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Encoder_Start(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Encoder_Stop(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Timeout_Start(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Timeout_Stop(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Counter_Start(LPTIM_HandleTypeDef *hlptim);
HAL_StatusTypeDef HAL_LPTIM_Counter_Stop(LPTIM_HandleTypeDef *hlptim);

HAL_StatusTypeDef HAL_LPTIM_RegisterCallback(LPTIM_HandleTypeDef *hlptim,
                                             uint32_t CallbackID,
                                             pLPTIM_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_LPTIM_UnRegisterCallback(LPTIM_HandleTypeDef *hlptim,
                                               uint32_t CallbackID);


#endif // #ifndef __HAL_LPTIM_H__
