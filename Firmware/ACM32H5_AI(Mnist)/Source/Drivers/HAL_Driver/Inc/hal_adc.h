/******************************************************************************
*@file  : hal_adc.h
*@brief : Header file of ADC HAL module.
******************************************************************************/
#ifndef __HAL_ADC_H__
#define __HAL_ADC_H__


#include "hal.h"


/** 
  * @brief  ADC ExTigger structure definition
  */
typedef struct
{
    uint32_t ExTrigSel;                     /*!< Configures the regular channel trig mode. */
    
    uint32_t JExTrigSel;                    /*!< Configures the inject channel trig mode. */
    
}ADC_ExTrigTypeDef;

/** 
  * @brief  ADC group regular oversampling structure definition
  */
typedef struct
{
    uint32_t Ratio;                         /*!< Configures the oversampling ratio. */

    uint32_t RightBitShift;                 /*!< Configures the division coefficient for the Oversampler. */

    uint32_t TriggeredMode;                 /*!< Selects the regular triggered oversampling mode. */
    
}ADC_OversamplingTypeDef;




/**
  * @brief  ADC Configuration Structure definition
  */
typedef struct
{
    uint32_t ClockSource;                   /*!< Specify the ADC clock source. */
    
    uint32_t ClockPrescaler;                /*!< Specify the ADC clock div from the PCLK. */

    uint32_t Resolution;                    /*!< Configure the ADC resolution. */

    uint32_t DataAlign;                     /*!< Specify ADC data alignment in conversion data register (right or left). */
    
    FunctionalState ConConvMode;            /*!< Specify whether the conversion is performed in single mode (one conversion) or continuous mode for 
                                              ADC group regular,after the first ADC conversion start trigger occurred (software start or external trigger). */	
    FunctionalState DiscontinuousConvMode;  /*!< Specifies whether the conversions sequence of regular group is performed in Complete-sequence/Discontinuous-sequence 
                                              (main sequence subdivided in successive parts).Discontinuous mode is used only if sequencer is enabled 
                                              (parameter 'ScanConvMode'). If sequencer is disabled, this parameter is discarded.Discontinuous mode can be enabled only 
                                              if continuous mode is disabled. If continuous mode is enabled, this parameter setting is discarded. */
    uint32_t NbrOfDiscConversion;           /*!< Regular channel intermittent mode channel count. */
                                               
    uint32_t ExternalTrigConv;              /*!< Selects the external event used to trigger the conversion start of regular group.
                                              If set to ADC_SOFTWARE_START, external triggers are disabled.
                                              If set to external trigger source, triggering is on event rising edge by default. */
    uint32_t ExternalTrigConvEdge;          /*!< Selects the external trigger edge of regular group.
                                              If trigger is set to ADC_SOFTWARE_START, this parameter is discarded. */

    uint32_t ChannelEn;                     /*!< Specify the enable ADC channels. */

                                                                                                
    uint32_t DMAMode;                       /*!< Specify whether the DMA requests are performed in one shot mode (DMA transfer stops when number of conversions is reached)
                                              or in continuous mode (DMA transfer unlimited, whatever number of conversions). */
    uint32_t OverMode;                      /*!<  ADC_OVERMODE_DISABLE,ADC_OVERMODE_ENABLE */

    uint32_t OverSampMode;                  /*!< Specify whether the oversampling feature is enabled or disabled. */
    
    ADC_OversamplingTypeDef Oversampling;   /*!< Specify ADC group regular oversampling structure. */

    uint32_t AnalogWDGEn;
	
											  
	 
}ADC_InitTypeDef;


typedef struct
{
    uint32_t Channel;                       /*!< Specify the channel to configure into ADC regular group. */

    uint32_t Sq;                            /*!< Add or remove the channel from ADC regular group sequencer and specify its conversion rank. */

    uint32_t Smp;                           /*!< Sampling time value to be set for the selected channel. */
    
    uint32_t Diff;                          /*!< Select differential input.In differential mode: Differential measurement is carried out 
                                              between the selected channel 'i' (positive input) and channel 'i+1' (negative input).
                                              Only channel 'i' has to be configured,  channel 'i+1' is configured automatically. */
    uint32_t OffsetNumber;                  /*!< Select the offset number. */

    uint32_t Offset;                        /*!< Define the offset to be applied on the raw converted data.
                                              Offset value must be a positive number. */

    uint32_t OffsetCalculate;               /*!< Define if the offset should be substracted (negative sign) 
                                              or added (positive sign) from or to the raw converted data. */
    uint32_t Offsetsign;                    /*!< Define if the offset should be saturated upon under or over flow. */
    
}ADC_ChannelConfTypeDef;

typedef struct
{
    uint32_t WatchdogMode;                  /*!< Configure the ADC analog watchdog mode: single/all/none channels. For Analog Watchdog 1: 
                                              Configure the ADC analog watchdog mode: single channel or all channels, ADC group regular.
                                              For Analog Watchdog 2 and 3: Several channels can be monitored by applying successively the AWD init structure. */

    uint32_t RegularChannel;                /*!< Select the analog watchdog regular channe */
    
    uint32_t InjectChannel;                /*!< Select the analog watchdog inject channe */

    uint32_t ITMode;                        /*!< Specify whether the analog watchdog is configured in interrupt or polling mode. */

    uint32_t HighThreshold;                 /*!< Configure the ADC analog watchdog High threshold value. */

    uint32_t LowThreshold;                  /*!< Configures the ADC analog watchdog Low threshold value. */

    uint32_t Diff;                          /*!< Select differential input. */
    
}ADC_AnalogWDGConfTypeDef;

/**
  * @brief  ADC Injected Conversion Oversampling structure definition
  */
typedef struct
{
    uint32_t Ratio;                         /*!< Configures the oversampling ratio. */

    uint32_t RightBitShift;                 /*!< Configures the division coefficient for the Oversampler. */
    
} ADC_InjOversamplingTypeDef;


typedef struct 
{
    uint32_t InjectedChannel;                       /*!< Selection of ADC channel to configure */
    
    uint32_t InjectedRank;                          /*!< Rank in the injected group sequencer */
    
    uint32_t InjectedSamplingTime;                  /*!< Sampling time value to be set for the selected channel. */
    
    uint32_t InjectedDiff;                          /*!< Selection of differential input. */

    uint32_t InjectedOffsetNumber;                  /*!< Selects the offset number. */

    uint32_t InjectedOffset;                        /*!< Defines the offset to be applied on the raw converted data. */

    uint32_t InjectedOffsetCalculate;               /*!< Define if the offset should be substracted (negative sign) or added (positive sign) from or to the raw converted data. */
    
    uint32_t InjectedOffsetSign;                    /*!< Define if the offset should be saturated upon under or over flow. */
                                                     
    uint32_t InjectedNbrOfConversion;               /*!< Specifies the number of ranks that will be converted within the injected group sequencer. */
    
    FunctionalState InjectedDiscontinuousConvMode;  /*!< Specifies whether the conversions sequence of injected group is performed in Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
                                                      Discontinuous mode is used only if sequencer is enabled (parameter 'ScanConvMode'). If sequencer is disabled, this parameter is discarded.
                                                      Discontinuous mode can be enabled only if continuous mode is disabled. If continuous mode is enabled, this parameter setting is discarded. */
    FunctionalState AutoInjectedConv;               /*!< Enables or disables the selected ADC automatic injected group conversion after regular one */
    
    uint32_t ExternalTrigInjecConv;                 /*!< Selects the external event used to trigger the conversion start of injected group.
                                                      If set to ADC_INJECTED_SOFTWARE_START, external triggers are disabled.
                                                      If set to external trigger source, triggering is on event rising edge. */
    uint32_t ExternalTrigInjecConvEdge;             /*!< Selects the external trigger edge of injected group. */
                                                               
    FunctionalState InjecOversamplingMode;          /*!< Specifies whether the oversampling feature is enabled or disabled. */

    ADC_InjOversamplingTypeDef  InjecOversampling;  /*!< Specifies the Oversampling parameters. */															   
															  
}ADC_InjectionConfTypeDef; 

/** 
  * @brief ADC Configuration multi-mode structure definition  
  */ 
typedef struct
{
    uint32_t Mode;              /*!< Configures the ADC to operate in independent or multi mode. */
    
    uint32_t DMAAccessMode;     /*!< Configures the Direct memory access mode for multi ADC mode. */
    
    uint32_t TwoSamplingDelay;  /*!< Configures the Delay between 2 sampling phases. */
    
}ADC_MultiModeTypeDef;

/**
  * @brief  ADC handle Structure definition
  */
typedef struct __ADC_HandleTypeDef
{
    ADC_TypeDef                     *Instance;                                  /*!< Register base address */
    
    ADC_InitTypeDef                 Init;                                       /*!< ADC initialization parameters and regular conversions setting */
#ifdef HAL_DMA_MODULE_ENABLED    
    DMA_HandleTypeDef              *DMA_Handle;                                /*!< Pointer DMA Handler */
#endif    
    uint32_t                        ChannelNum;                                 /*!< Total enable regular group channel number*/
    
    uint32_t                        *AdcResults;                                /*!< Point to the convert results*/
    
    void (*ConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);                 /*!< ADC conversion complete callback */
    
    void (*GroupCpltCallback)(struct __ADC_HandleTypeDef *hadc);                /*!< ADC regular group conversion complete callback */
    
    void (*InjectedConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);         /*!< ADC injected conversion complete callback */
    
    void (*InjectedGroupConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);    /*!< ADC injected Group conversion complete callback */
    
    void (*LevelOutOfWindowCallback)(struct __ADC_HandleTypeDef *hadc);         /*!< ADC analog watchdog callback */
    
}ADC_HandleTypeDef;


/** @defgroup ADC1/ADC2/ADC3
  * @{
  */   
#define IS_ADC_INSTANCE(INSTANCE)                   (((INSTANCE) == ADC1) || ((INSTANCE) == ADC2) || ((INSTANCE) == ADC3))
/**
  * @}
  */

/** @defgroup ADC Trig source define
  * @{
  */ 
/*  |     Trig Source           |      Regular           |        Inject           | * 
 *  |     ADC_EXTERNAL_TIG0     |     TIM1_CC1           |      TIM1_TRGO          | *
 *  |     ADC_EXTERNAL_TIG1     |     TIM1_CC2           |      TIM1_CC4           | *
 *  |     ADC_EXTERNAL_TIG2     |     TIM1_CC3           |      TIM2_TRGO          | *
 *  |     ADC_EXTERNAL_TIG3     |     TIM2_CC2           |      TIM2_CC1           | *
 *  |     ADC_EXTERNAL_TIG4     |     TIM3_TRGO          |      TIM3_CC4           | *
 *  |     ADC_EXTERNAL_TIG5     |     TIM4_CC4           |      TIM4_TRGO          | *
 *  |     ADC_EXTERNAL_TIG6     |     EXTI Line 11       |      EXTI Line 15       | *
 *  |     ADC_EXTERNAL_TIG7     |     TIM8_TRGO          |      TIM8_CC4           | *
 *  |     ADC_EXTERNAL_TIG8     |     TIM8_TRGO2         |      TIM1_TRGO2          | *
 *  |     ADC_EXTERNAL_TIG9     |     TIM1_TRGO          |      TIM8_TRGO          | *
 *  |     ADC_EXTERNAL_TIG10    |     TIM1_TRGO2         |      TIM8_TRGO2         | *
 *  |     ADC_EXTERNAL_TIG11    |     TIM2_TRGO          |      TIM3_CC3           | *
 *  |     ADC_EXTERNAL_TIG12    |     TIM4_TRGO          |      TIM3_TRGO          | *
 *  |     ADC_EXTERNAL_TIG13    |     TIM6_TRGO          |      TIM3_CC1           | *
 *  |     ADC_EXTERNAL_TIG14    |     TIM15_TRGO         |      TIM6_TRGO          | *
 *  |     ADC_EXTERNAL_TIG15    |     TIM3_CC4           |      TIM15_TRGO         | *
 *  |     ADC_EXTERNAL_TIG16    |                        |                         | *
 *  |     ADC_EXTERNAL_TIG17    |                        |                         | *
 *  |     ADC_EXTERNAL_TIG18    |     LPTIM1_OUT         |      LPTIM1_OUT         | * 
 *  |     ADC_EXTERNAL_TIG19    |     LPTIM2_OUT         |      LPTIM2_OUT         | * 
 *  |     ADC_EXTERNAL_TIG20    |     LPTIM3_OUT         |      LPTIM3_OUT         | */
#define ADC_EXTERNAL_TIG0                           (0U)
#define ADC_EXTERNAL_TIG1                           (1U)
#define ADC_EXTERNAL_TIG2                           (2U)
#define ADC_EXTERNAL_TIG3                           (3U)
#define ADC_EXTERNAL_TIG4                           (4U)
#define ADC_EXTERNAL_TIG5                           (5U)
#define ADC_EXTERNAL_TIG6                           (6U)
#define ADC_EXTERNAL_TIG7                           (7U)
#define ADC_EXTERNAL_TIG8                           (8U)
#define ADC_EXTERNAL_TIG9                           (9U)
#define ADC_EXTERNAL_TIG10                          (10U)
#define ADC_EXTERNAL_TIG11                          (11U)
#define ADC_EXTERNAL_TIG12                          (12U)
#define ADC_EXTERNAL_TIG13                          (13U)
#define ADC_EXTERNAL_TIG14                          (14U)
#define ADC_EXTERNAL_TIG15                          (15U)
#define ADC_EXTERNAL_TIG16                          (16U)
#define ADC_EXTERNAL_TIG17                          (17U)
#define ADC_EXTERNAL_TIG18                          (18U)
#define ADC_EXTERNAL_TIG19                          (19U)
#define ADC_EXTERNAL_TIG20                          (20U)
#define ADC_SOFTWARE_START                          (32U)
#define IS_ADC_EXT_TRIG(REGTRIG)                    (((REGTRIG) == ADC_EXTERNAL_TIG0) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG1) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG2) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG3) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG4) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG5) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG6) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG7) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG8) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG9) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG10) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG11) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG12) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG13) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG14) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG15) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG16) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG17) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG18) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG19) || \
                                                    ((REGTRIG) == ADC_EXTERNAL_TIG20) || \
                                                    ((REGTRIG) == ADC_SOFTWARE_START))  
                                                
/**
  * @}
  */                                                 
                                                
/**
  * @}
  */
   
/** @defgroup ADC External Trigger Edge 
  * @{
  */ 
#define ADC_EXTERNALTRIGCONVEDGE_NONE               (0U)
#define ADC_EXTERNALTRIGCONVEDGE_RISING             (1U)
#define ADC_EXTERNALTRIGCONVEDGE_FALLING            (2U)
#define ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING      (3U)
#define IS_ADC_EXT_TRIG_EDGE(EDGE)                  (((EDGE) == ADC_EXTERNALTRIGCONVEDGE_NONE) || \
                                                    ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISING) || \
                                                    ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_FALLING) || \
                                                    ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING))
/**
  * @}
  */
  
/** @defgroup ADC Data Align
* @{
*/ 
#define ADC_DATAALIGN_RIGHT                         (0x00U)
#define ADC_DATAALIGN_LEFT                          ((uint32_t)ADC_CR2_ALIGN)
#define IS_ADC_DATA_ALIGN(ALIGN)                    (((ALIGN) == ADC_DATAALIGN_RIGHT) || ((ALIGN) == ADC_DATAALIGN_LEFT))
/**
  * @}
  */ 

/** @defgroup ADC Continuous
* @{
*/ 
#define ADC_CONT_DISABLE                            (0x00U)
#define ADC_CONT_ENABLE                             ((uint32_t)ADC_CR1_CONT)
#define IS_ADC_CONT(CONT)                           (((CONT) == ADC_CONT_DISABLE) || ((CONT) == ADC_CONT_ENABLE))
/**
  * @}
  */    
  
/** @defgroup ADC Resolution
  * @{
  */
#define ADC_RESOLUTION_12B                          (0x00U)   /*!< ADC resolution 12 bits */
#define ADC_RESOLUTION_10B                          (ADC_CR2_RES_0)   /*!< ADC resolution 10 bits */
#define ADC_RESOLUTION_8B                           (ADC_CR2_RES_1)   /*!< ADC resolution  8 bits */
#define ADC_RESOLUTION_6B                           (ADC_CR2_RES_0 | ADC_CR2_RES_1)   /*!< ADC resolution  6 bits */
#define IS_ADC_RESOLUTION(RESOLUTION)               (((RESOLUTION) == ADC_RESOLUTION_12B) || \
                                                    ((RESOLUTION) == ADC_RESOLUTION_10B) || \
                                                    ((RESOLUTION) == ADC_RESOLUTION_8B) || \
                                                    ((RESOLUTION) == ADC_RESOLUTION_6B))
/**
  * @}
  */
    
/** @defgroup ADC ClockPrescale 
  * @{
  */ 
#define IS_ADC_CLOCKDIV(CLOCKDIV)                   (((CLOCKDIV) >= 0x01) && ((CLOCKDIV) <= 0x40))
                                             
/**
  * @}
  */
  
/** @defgroup ADC ClockSource 
  * @{
  */ 
#define ADC_CLOCKSOURCE_HCLK                        (0x00U)
#define ADC_CLOCKSOURCE_PLL3PCLK                    ((uint32_t)ADC_CCR_CLKMODE)
#define IS_ADC_CLOCKSOURCE(SOURCE)                  (((SOURCE) == ADC_CLOCKSOURCE_HCLK) || ((SOURCE) == ADC_CLOCKSOURCE_PLL3PCLK))
                                             
/**
  * @}
  */
  
/** @defgroup  Multimode
  * @{
  */
#define ADC_MODE_INDEPENDENT                        (0x00U)                                          /*!< ADC dual mode disabled (ADC independent mode) */
#define ADC_DUALMODE_REGSIMULT_INJECSIMULT          (ADC_CCR_DUALMOD_0) /*!< ADC dual mode enabled: Combined group regular simultaneous + group injected simultaneous */
#define ADC_DUALMODE_REGSIMULT_ALTERTRIG            (ADC_CCR_DUALMOD_1) /*!< ADC dual mode enabled: Combined group regular simultaneous + group injected alternate trigger */
#define ADC_DUALMODE_REGINTERL_INJECSIMULT          (ADC_CCR_DUALMOD_0 | ADC_CCR_DUALMOD_1) /*!< ADC dual mode enabled: Combined group regular interleaved + group injected simultaneous */
#define ADC_DUALMODE_INJECSIMULT                    (ADC_CCR_DUALMOD_0 | ADC_CCR_DUALMOD_2) /*!< ADC dual mode enabled: group injected simultaneous */
#define ADC_DUALMODE_REGSIMULT                      (ADC_CCR_DUALMOD_1 | ADC_CCR_DUALMOD_2) /*!< ADC dual mode enabled: group regular simultaneous */
#define ADC_DUALMODE_INTERL                         (ADC_CCR_DUALMOD_0 | ADC_CCR_DUALMOD_1 | ADC_CCR_DUALMOD_2) /*!< ADC dual mode enabled: Combined group regular interleaved */
#define ADC_DUALMODE_ALTERTRIG                      (ADC_CCR_DUALMOD_0 | ADC_CCR_DUALMOD_3) /*!< ADC dual mode enabled: group injected alternate trigger. Works only with external triggers (not internal SW start) */
#define IS_ADC_MODE(MODE)                           (((MODE) == ADC_MODE_INDEPENDENT) || \
                                                    ((MODE) == ADC_DUALMODE_REGSIMULT_INJECSIMULT) || \
                                                    ((MODE) == ADC_DUALMODE_REGSIMULT_ALTERTRIG) || \
                                                    ((MODE) == ADC_DUALMODE_REGINTERL_INJECSIMULT) || \
                                                    ((MODE) == ADC_DUALMODE_INJECSIMULT) || \
                                                    ((MODE) == ADC_DUALMODE_REGSIMULT) || \
                                                    ((MODE) == ADC_DUALMODE_INTERL) || \
                                                    ((MODE) == ADC_DUALMODE_ALTERTRIG))
/**
  * @}
  */
  
/** @defgroup  DMA transfer mode depending on ADC resolution
  * @{
  */
#define ADC_DMAACCESSMODE_DISABLED                  (0x00U)     /*!< DMA multimode disabled: each ADC uses its own DMA channel */
#define ADC_DMAACCESSMODE_12_10_BITS                (ADC_CCR_DMADUAL_1)   /*!< DMA multimode enabled (one DMA channel for both ADC, DMA of ADC master) for 12 and 10 bits resolution */
#define ADC_DMAACCESSMODE_8_6_BITS                  (ADC_CCR_DMADUAL_0 | ADC_CCR_DMADUAL_1)     /*!< DMA multimode enabled (one DMA channel for both ADC, DMA of ADC master) for 8 and 6 bits resolution */
#define IS_ADC_DMA_ACCESS_MODE(MODE)                (((MODE) == ADC_DMAACCESSMODE_DISABLED) || \
                                                    ((MODE) == ADC_DMAACCESSMODE_12_10_BITS) || \
                                                    ((MODE) == ADC_DMAACCESSMODE_8_6_BITS))
/**
  * @}
  */
  
/** @defgroup  ADC Delay Between 2 Sampling Phases
  * @{
  */ 
#define ADC_TWOSAMPLINGDELAY_5CYCLES                (0x00U)
#define ADC_TWOSAMPLINGDELAY_6CYCLES                (ADC_CCR_DELAY_0)
#define ADC_TWOSAMPLINGDELAY_7CYCLES                (ADC_CCR_DELAY_1)
#define ADC_TWOSAMPLINGDELAY_8CYCLES                (ADC_CCR_DELAY_0 | ADC_CCR_DELAY_1)
#define ADC_TWOSAMPLINGDELAY_9CYCLES                (ADC_CCR_DELAY_2)
#define ADC_TWOSAMPLINGDELAY_10CYCLES               (ADC_CCR_DELAY_0 | ADC_CCR_DELAY_2)
#define ADC_TWOSAMPLINGDELAY_11CYCLES               (ADC_CCR_DELAY_1 | ADC_CCR_DELAY_2)
#define ADC_TWOSAMPLINGDELAY_12CYCLES               (ADC_CCR_DELAY_0 | ADC_CCR_DELAY_1 | ADC_CCR_DELAY_2)
#define ADC_TWOSAMPLINGDELAY_13CYCLES               (ADC_CCR_DELAY_3)
#define ADC_TWOSAMPLINGDELAY_14CYCLES               (ADC_CCR_DELAY_0 | ADC_CCR_DELAY_3)
#define ADC_TWOSAMPLINGDELAY_15CYCLES               (ADC_CCR_DELAY_1 | ADC_CCR_DELAY_3)
#define ADC_TWOSAMPLINGDELAY_16CYCLES               (ADC_CCR_DELAY_0 | ADC_CCR_DELAY_1 | ADC_CCR_DELAY_3)
#define ADC_TWOSAMPLINGDELAY_17CYCLES               (ADC_CCR_DELAY_2 | ADC_CCR_DELAY_3)
#define ADC_TWOSAMPLINGDELAY_18CYCLES               (ADC_CCR_DELAY_0 | ADC_CCR_DELAY_2 | ADC_CCR_DELAY_3)
#define ADC_TWOSAMPLINGDELAY_19CYCLES               (ADC_CCR_DELAY_1 | ADC_CCR_DELAY_2 | ADC_CCR_DELAY_3)
#define ADC_TWOSAMPLINGDELAY_20CYCLES               (ADC_CCR_DELAY_0 | ADC_CCR_DELAY_1 | ADC_CCR_DELAY_2 | ADC_CCR_DELAY_3)                                    
#define IS_ADC_SAMPLING_DELAY(DELAY)                (((DELAY) == ADC_TWOSAMPLINGDELAY_5CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_6CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_7CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_8CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_9CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_10CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_11CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_12CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_13CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_14CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_15CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_16CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_17CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_18CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_19CYCLES) || \
                                                    ((DELAY) == ADC_TWOSAMPLINGDELAY_20CYCLES))

/**
  * @}
  */


/** @defgroup ADC analog watchdog selection
  * @{
  */ 
#define ADC_ANALOGWATCHDOG_RCH_SINGLE               (ADC_CR1_AWDSGL | ADC_CR1_AWDEN)   //Single regular channel
#define ADC_ANALOGWATCHDOG_JCH_SINGLE               (ADC_CR1_AWDSGL | ADC_CR1_JAWDEN)   //Single Inject channel
#define ADC_ANALOGWATCHDOG_RCH_OR_JCH_SINGLE        (ADC_CR1_AWDSGL | ADC_CR1_AWDEN | ADC_CR1_JAWDEN)   //Regular or inject channel
#define ADC_ANALOGWATCHDOG_RCH_ALL                  (ADC_CR1_AWDEN)   //All regular channels
#define ADC_ANALOGWATCHDOG_JCH_ALL                  (ADC_CR1_JAWDEN)   //All inject channels
#define ADC_ANALOGWATCHDOG_RCH_AND_JCH_ALL          (ADC_CR1_AWDEN | ADC_CR1_JAWDEN)   //All regular and inject channels
#define ADC_ANALOGWATCHDOG_NONE                     (0x00U)
#define IS_ADC_ANALOG_WATCHDOG(WATCHDOG)            (((WATCHDOG) == ADC_ANALOGWATCHDOG_RCH_SINGLE) || \
                                                    ((WATCHDOG) == ADC_ANALOGWATCHDOG_JCH_SINGLE) || \
                                                    ((WATCHDOG) == ADC_ANALOGWATCHDOG_RCH_OR_JCH_SINGLE) || \
                                                    ((WATCHDOG) == ADC_ANALOGWATCHDOG_RCH_ALL) || \
                                                    ((WATCHDOG) == ADC_ANALOGWATCHDOG_JCH_ALL) || \
                                                    ((WATCHDOG) == ADC_ANALOGWATCHDOG_RCH_AND_JCH_ALL) || \
                                                    ((WATCHDOG) == ADC_ANALOGWATCHDOG_NONE))  
/**
  * @}
  */
  
/** @defgroup ADC analog watchdog thresholds 
  * @{
  */ 
#define IS_ADC_THRESHOLD(THRESHOLD)                 ((THRESHOLD) <= 0xFFF)
/**
  * @}
  */   
  
/** @defgroup ADC channel number 
* @{
*/
#define ADC_CHANNEL_0                               (0U)    
#define ADC_CHANNEL_1                               (1U)    
#define ADC_CHANNEL_2                               (2U)    
#define ADC_CHANNEL_3                               (3U)    
#define ADC_CHANNEL_4                               (4U)    
#define ADC_CHANNEL_5                               (5U)    
#define ADC_CHANNEL_6                               (6U)    
#define ADC_CHANNEL_7                               (7U)    
#define ADC_CHANNEL_8                               (8U)    
#define ADC_CHANNEL_9                               (9U)    
#define ADC_CHANNEL_10                              (10U)    
#define ADC_CHANNEL_11                              (11U)    
#define ADC_CHANNEL_12                              (12U)    
#define ADC_CHANNEL_13                              (13U)    
#define ADC_CHANNEL_14                              (14U)    
#define ADC_CHANNEL_15                              (15U)    
#define ADC_CHANNEL_16                              (16U) 
#define ADC_CHANNEL_17                              (17U)          
#define ADC_CHANNEL_18                              (18U) 
#define ADC_CHANNEL_19                              (19U) 
#define ADC_CHANNEL_VREF                            (13U)    
#define ADC_CHANNEL_VBAT                            (17U)
#define ADC_CHANNEL_TEMP                            (18U) 
#define ADC_CHANNEL_0_EN                            (1U << ADC_CHANNEL_0)    
#define ADC_CHANNEL_1_EN                            (1U << ADC_CHANNEL_1)  
#define ADC_CHANNEL_2_EN                            (1U << ADC_CHANNEL_2)
#define ADC_CHANNEL_3_EN                            (1U << ADC_CHANNEL_3)
#define ADC_CHANNEL_4_EN                            (1U << ADC_CHANNEL_4)
#define ADC_CHANNEL_5_EN                            (1U << ADC_CHANNEL_5)   
#define ADC_CHANNEL_6_EN                            (1U << ADC_CHANNEL_5)   
#define ADC_CHANNEL_7_EN                            (1U << ADC_CHANNEL_5) 
#define ADC_CHANNEL_8_EN                            (1U << ADC_CHANNEL_8) 
#define ADC_CHANNEL_9_EN                            (1U << ADC_CHANNEL_9)
#define ADC_CHANNEL_10_EN                           (1U << ADC_CHANNEL_10) 
#define ADC_CHANNEL_11_EN                           (1U << ADC_CHANNEL_11) 
#define ADC_CHANNEL_12_EN                           (1U << ADC_CHANNEL_12)
#define ADC_CHANNEL_13_EN                           (1U << ADC_CHANNEL_13)
#define ADC_CHANNEL_14_EN                           (1U << ADC_CHANNEL_14)  
#define ADC_CHANNEL_15_EN                           (1U << ADC_CHANNEL_15) 
#define ADC_CHANNEL_16_EN                           (1U << ADC_CHANNEL_16)
#define ADC_CHANNEL_17_EN                           (1U << ADC_CHANNEL_17)     
#define ADC_CHANNEL_18_EN                           (1U << ADC_CHANNEL_18)
#define ADC_CHANNEL_19_EN                           (1U << ADC_CHANNEL_19)
#define ADC_CHANNEL_VREF_EN                         (1U << ADC_CHANNEL_VREF)   
#define ADC_CHANNEL_VBAT_EN                         (1U << ADC_CHANNEL_VBAT)
#define ADC_CHANNEL_TEMP_EN                         (1U << ADC_CHANNEL_TEMP)     
#define IS_ADC_CHANNEL(CHANNEL)                     (((CHANNEL) == ADC_CHANNEL_0) || \
                                                    ((CHANNEL) == ADC_CHANNEL_1) || \
                                                    ((CHANNEL) == ADC_CHANNEL_2) || \
                                                    ((CHANNEL) == ADC_CHANNEL_3) || \
                                                    ((CHANNEL) == ADC_CHANNEL_4) || \
                                                    ((CHANNEL) == ADC_CHANNEL_5) || \
                                                    ((CHANNEL) == ADC_CHANNEL_6) || \
                                                    ((CHANNEL) == ADC_CHANNEL_7) || \
                                                    ((CHANNEL) == ADC_CHANNEL_8) || \
                                                    ((CHANNEL) == ADC_CHANNEL_9) || \
                                                    ((CHANNEL) == ADC_CHANNEL_10) || \
                                                    ((CHANNEL) == ADC_CHANNEL_11) || \
                                                    ((CHANNEL) == ADC_CHANNEL_12) || \
                                                    ((CHANNEL) == ADC_CHANNEL_13) || \
                                                    ((CHANNEL) == ADC_CHANNEL_14) || \
                                                    ((CHANNEL) == ADC_CHANNEL_15) || \
                                                    ((CHANNEL) == ADC_CHANNEL_16) || \
                                                    ((CHANNEL) == ADC_CHANNEL_17) || \
                                                    ((CHANNEL) == ADC_CHANNEL_18) || \
                                                    ((CHANNEL) == ADC_CHANNEL_19) || \
                                                    ((CHANNEL) < 32))
                                                    
/**
  * @}
  */ 

/** @defgroup Sampling time
  * @{
  */
#define ADC_SMP_CLOCK_3                             (0U)
#define ADC_SMP_CLOCK_5                             (1U)
#define ADC_SMP_CLOCK_7                             (2U)
#define ADC_SMP_CLOCK_10                            (3U)
#define ADC_SMP_CLOCK_13                            (4U)
#define ADC_SMP_CLOCK_16                            (5U)
#define ADC_SMP_CLOCK_20                            (6U)
#define ADC_SMP_CLOCK_30                            (7U)
#define ADC_SMP_CLOCK_60                            (8U)
#define ADC_SMP_CLOCK_80                            (9U)
#define ADC_SMP_CLOCK_100                           (10U)
#define ADC_SMP_CLOCK_120                           (11U)
#define ADC_SMP_CLOCK_160                           (12U)
#define ADC_SMP_CLOCK_260                           (13U)
#define ADC_SMP_CLOCK_320                           (14U)
#define ADC_SMP_CLOCK_640                           (15U)
#define IS_ADC_SMPCLOCK(SMPCLOCK)                   (((SMPCLOCK) == ADC_SMP_CLOCK_3) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_5) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_7) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_10) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_13) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_16) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_20) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_30) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_60) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_80) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_100) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_120) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_160) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_260) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_320) || \
                                                    ((SMPCLOCK) == ADC_SMP_CLOCK_640))   
/**
  * @}
  */ 
  
/** @defgroup ADC sequence number
* @{
*/
#define ADC_SEQUENCE_SQ1                            (1U)
#define ADC_SEQUENCE_SQ2                            (2U)
#define ADC_SEQUENCE_SQ3                            (3U)
#define ADC_SEQUENCE_SQ4                            (4U)
#define ADC_SEQUENCE_SQ5                            (5U)
#define ADC_SEQUENCE_SQ6                            (6U)
#define ADC_SEQUENCE_SQ7                            (7U)
#define ADC_SEQUENCE_SQ8                            (8U)
#define ADC_SEQUENCE_SQ9                            (9U)
#define ADC_SEQUENCE_SQ10                           (10U)
#define ADC_SEQUENCE_SQ11                           (11U)
#define ADC_SEQUENCE_SQ12                           (12U)
#define ADC_SEQUENCE_SQ13                           (13U)
#define ADC_SEQUENCE_SQ14                           (14U)
#define ADC_SEQUENCE_SQ15                           (15U)
#define ADC_SEQUENCE_SQ16                           (16U)
#define IS_ADC_SEQUENCE(SEQUENCE)                   (((SEQUENCE) == ADC_SEQUENCE_SQ1) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ2) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ3) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ4) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ5) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ6) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ7) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ8) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ9) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ10) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ11) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ12) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ13) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ14) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ15) || \
                                                    ((SEQUENCE) == ADC_SEQUENCE_SQ16))
/**
  * @}
  */   

/** @defgroup ADC regular length 
  * @{
  */ 
#define IS_ADC_REGULAR_LENGTH(LENGTH)               (((LENGTH) >= 0x01) && ((LENGTH) <= 0x10))
/**
  * @}
  */ 
  
/** @defgroup ADC regular discontinuous mode number 
  * @{
  */ 
#define IS_ADC_REGULAR_DISC_NUMBER(NUMBER)          ((NUMBER) <= 0x8)
/**
  * @}
  */ 

/** @defgroup ADC injected rank 
  * @{
  */ 
#define ADC_INJECTED_RANK_1                         (1U)
#define ADC_INJECTED_RANK_2                         (2U)
#define ADC_INJECTED_RANK_3                         (3U)
#define ADC_INJECTED_RANK_4                         (4U)
#define IS_ADC_INJECTED_RANK(RANK)                  (((RANK) >= 0x1) && ((RANK) <= 0x4))
/**
  * @}
  */ 

/** @defgroup ADC injected length 
  * @{
  */ 
#define IS_ADC_INJECTED_LENGTH(LENGTH)              (((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))
/**
  * @}
  */  
  
/** @defgroup Offset Number 
  * @{
  */ 
#define ADC_OFR_1                                   (0U) /*!< ADC offset number 1: ADC_OFR1 */
#define ADC_OFR_2                                   (1U) /*!< ADC offset number 2: ADC_OFR2 */
#define ADC_OFR_3                                   (2U) /*!< ADC offset number 3: ADC_OFR3 */
#define ADC_OFR_4                                   (3U) /*!< ADC offset number 4: ADC_OFR4 */
#define ADC_OFR_NONE                                (4U) /*!< ADC offset disabled: no offset correction for the selected ADC channel */
#define IS_ADC_OFFSET_NUMBER(NUMBER)                (((NUMBER) < 0x5))
/**
  * @}
  */ 
  
/** @defgroup offset 
  * @{
  */ 
#define IS_ADC_OFFSET(OFFSET)                       ((OFFSET) <= 0xFFF)
/**
  * @}
  */ 

 /** @defgroup Offset Calculate
  * @{
  */
#define ADC_OFFSET_MINUS                            (0x00000000UL)  /*!< ADC conversion result minus offset */
#define ADC_OFFSET_PLUS                             (ADC_OFRX_OFFSETY_POS)   /*!< ADC conversion result plus offset */
#define IS_ADC_OFFSET_CALCULATE(CALCULATE)          (((CALCULATE) == ADC_OFFSET_MINUS) || ((CALCULATE) == ADC_OFFSET_PLUS))
/**
  * @}
  */
  

/** @defgroup Offset sign
  * @{
  */
#define ADC_OFFSET_SIGN_SIGNED                      (0x00000000UL)                  /*!< The calculation result is a signed number */
#define ADC_OFFSET_SIGN_UNSIGNED                    (ADC_OFRX_OFFSETY_SAT)           /*!< The calculation result is an unsigned number */
#define IS_ADC_OFFSET_SIGN(SIGN)                    (((SIGN) == ADC_OFFSET_SIGN_SIGNED) || ((SIGN) == ADC_OFFSET_SIGN_UNSIGNED))
/**
  * @}
  */ 

/** @defgroup JDR Number 
  * @{
  */ 
#define ADC_JDR_1                                   (0U) /*!< ADC JDR number 1: ADC_JDR1 */
#define ADC_JDR_2                                   (1U) /*!< ADC JDR number 2: ADC_JDR2 */
#define ADC_JDR_3                                   (2U) /*!< ADC JDR number 3: ADC_JDR3 */
#define ADC_JDR_4                                   (3U) /*!< ADC JDR number 4: ADC_JDR4 */
#define ADC_JDR_NONE                                (4U) /*!< none */
#define IS_ADC_JDR_NUMBER(NUMBER)                   ((NUMBER) < 0x5)
/**
  * @}
  */ 

/** @defgroup  Oversampling Data shift
  * @{
  */
#define ADC_RIGHTBITSHIFT_NONE                      (0U) /*!< ADC oversampling no shift (sum of the ADC conversions data is not divided */
#define ADC_RIGHTBITSHIFT_1                         (1U) /*!< ADC oversampling shift of 1 (sum of the ADC conversions data is divided by 2 */
#define ADC_RIGHTBITSHIFT_2                         (2U) /*!< ADC oversampling shift of 2 (sum of the ADC conversions data is divided by 4 */
#define ADC_RIGHTBITSHIFT_3                         (3U) /*!< ADC oversampling shift of 3 (sum of the ADC conversions data is divided by 8 */
#define ADC_RIGHTBITSHIFT_4                         (4U) /*!< ADC oversampling shift of 4 (sum of the ADC conversions data is divided by 16 */
#define ADC_RIGHTBITSHIFT_5                         (5U) /*!< ADC oversampling shift of 5 (sum of the ADC conversions data is divided by 32 */
#define ADC_RIGHTBITSHIFT_6                         (6U) /*!< ADC oversampling shift of 6 (sum of the ADC conversions data is divided by 64 */
#define ADC_RIGHTBITSHIFT_7                         (7U) /*!< ADC oversampling shift of 7 (sum of the ADC conversions data is divided by 128 */
#define ADC_RIGHTBITSHIFT_8                         (8U) /*!< ADC oversampling shift of 8 (sum of the ADC conversions data is divided by 256 */
#define IS_ADC_RIGHTBITSHIFT(SHIFT)                 (((SHIFT) == ADC_RIGHTBITSHIFT_NONE) || \
                                                    ((SHIFT) == ADC_RIGHTBITSHIFT_1) || \
                                                    ((SHIFT) == ADC_RIGHTBITSHIFT_2) || \
                                                    ((SHIFT) == ADC_RIGHTBITSHIFT_3) || \
                                                    ((SHIFT) == ADC_RIGHTBITSHIFT_4) || \
                                                    ((SHIFT) == ADC_RIGHTBITSHIFT_5) || \
                                                    ((SHIFT) == ADC_RIGHTBITSHIFT_6) || \
                                                    ((SHIFT) == ADC_RIGHTBITSHIFT_7) || \
                                                    ((SHIFT) == ADC_RIGHTBITSHIFT_8))
/**
  * @}
  */
  
/** @defgroup  Oversampling Ratio
  * @{
  */
#define ADC_OVERSAMPLING_RATIO_2                    (0U)  /*!< ADC oversampling ratio of 2 (2 ADC conversions are performed */
#define ADC_OVERSAMPLING_RATIO_4                    (1U)  /*!< ADC oversampling ratio of 4 (4 ADC conversions are performed */
#define ADC_OVERSAMPLING_RATIO_8                    (2U)  /*!< ADC oversampling ratio of 8 (8 ADC conversions are performed */
#define ADC_OVERSAMPLING_RATIO_16                   (3U)  /*!< ADC oversampling ratio of 16 (16 ADC conversions are performed */
#define ADC_OVERSAMPLING_RATIO_32                   (4U)  /*!< ADC oversampling ratio of 32 (32 ADC conversions are performed */
#define ADC_OVERSAMPLING_RATIO_64                   (5U)  /*!< ADC oversampling ratio of 64 (64 ADC conversions are performed */
#define ADC_OVERSAMPLING_RATIO_128                  (6U)  /*!< ADC oversampling ratio of 128 (128 ADC conversions are performed */
#define ADC_OVERSAMPLING_RATIO_256                  (7U)  /*!< ADC oversampling ratio of 256 (256 ADC conversions are performed */
#define IS_ADC_OVERSAMPLING_RATIO(RATIO)            (((RATIO) == ADC_OVERSAMPLING_RATIO_2) || \
                                                    ((RATIO) == ADC_OVERSAMPLING_RATIO_4)  || \
                                                    ((RATIO) == ADC_OVERSAMPLING_RATIO_8)  || \
                                                    ((RATIO) == ADC_OVERSAMPLING_RATIO_16) || \
                                                    ((RATIO) == ADC_OVERSAMPLING_RATIO_32) || \
                                                    ((RATIO) == ADC_OVERSAMPLING_RATIO_64) || \
                                                    ((RATIO) == ADC_OVERSAMPLING_RATIO_128) || \
                                                    ((RATIO) == ADC_OVERSAMPLING_RATIO_256))
/**
  * @}
  */  

/** @defgroup overflow mode
  * @{
  */
#define ADC_OVERFLOWMODE_LAST                       (0x00000000UL)  /*!< ADC keeps the last sampling data when overflow occurs */
#define ADC_OVERFLOWMODE_NEW                        (ADC_CR2_OVRMOD) /*!< ADC saves the new sampling data when overflow occurs */
#define IS_ADC_OVERFLOW_MODE(MODE)                  (((MODE) == ADC_OVERFLOWMODE_LAST) || ((MODE) == ADC_OVERFLOWMODE_NEW))
/**
  * @}
  */
  
/** @defgroup oversampling triger mode
  * @{
  */
#define ADC_OVERSAMPLING_TRIGER_MORE                (0x00000000UL)  /*!< One trigger for N ADC conversion */
#define ADC_OVERSAMPLING_TRIGER_ONCE                (ADC_CR2_TROVS) /*!< One trigger for ADC conversion */
#define IS_ADC_OVERSAMPLING_TRIGER(MODE)            (((MODE) == ADC_OVERSAMPLING_TRIGER_MORE) || ((MODE) == ADC_OVERSAMPLING_TRIGER_ONCE))
/**
  * @}
  */

/** @defgroup ADC interrupts and flag definition 
  * @{
  */ 
#define ADC_FLAG_ADRDY                              (ADC_SR_ADRDY)
#define ADC_IT_FLAG_EOSMP                           (ADC_SR_EOSMP)  
#define ADC_IT_FLAG_EOC                             (ADC_SR_EOC)  
#define ADC_IT_FLAG_EOG                             (ADC_SR_EOG)  
#define ADC_IT_FLAG_OVERF                           (ADC_SR_OVERF) 
#define ADC_IT_FLAG_JEOC                            (ADC_SR_JEOC) 
#define ADC_IT_FLAG_JEOG                            (ADC_SR_JEOG) 
#define ADC_IT_FLAG_AWD                             (ADC_SR_AWD)
#define ADC_IT_FLAG_ALL                             (0x000000FFUL)    
#define IS_ADC_IT_FLAG(FLAG)                        (((FLAG) == ADC_IT_FLAG_EOSMP) || ((FLAG) == ADC_IT_FLAG_EOC) || \
                                                    ((FLAG) == ADC_IT_FLAG_EOG)|| ((FLAG) == ADC_IT_FLAG_OVERF) || \
                                                    ((FLAG) == ADC_IT_FLAG_JEOC)|| ((FLAG) == ADC_IT_FLAG_JEOG) || \
                                                    ((FLAG) == ADC_IT_FLAG_AWD) || ((FLAG) <= ADC_IT_FLAG_ALL))   
#define IS_ADC_FLAG(FLAG)                           (((FLAG) == ADC_IT_FLAG_EOSMP) || ((FLAG) == ADC_IT_FLAG_EOC) || \
                                                    ((FLAG) == ADC_IT_FLAG_EOG)|| ((FLAG) == ADC_IT_FLAG_OVERF) || \
                                                    ((FLAG) == ADC_IT_FLAG_JEOC)|| ((FLAG) == ADC_IT_FLAG_JEOG) || \
                                                    ((FLAG) == ADC_IT_FLAG_AWD) || ((FLAG) <= ADC_IT_FLAG_ALL) || ((FLAG) == ADC_FLAG_ADRDY))                                                     
/**
  * @}
  */ 
  
/** @defgroup Single-ended or differential 
* @{
*/
#define ADC_DIFF_SINGLE                             (0U)   /*!< ADC channel ending set to single ended */
#define ADC_DIFF_DIFFERENTIAL                       (1U)   /*!< ADC channel ending set to differential */  
#define IS_ADC_DIFF(MODE)                           (((MODE) == ADC_DIFF_SINGLE) || ((MODE) == ADC_DIFF_DIFFERENTIAL))
/**
  * @}
  */ 
  

/** @defgroup Signed or unsigned number selection
* @{
*/
#define ADC_SIGN_UNSIGNED                           (0U)   /*!< The result is an unsigned number */
#define ADC_SIGN_SIGNED                             (1U)   /*!< The result is an signed number */  
#define IS_ADC_SIGN(MODE)                           (((MODE) == ADC_SIGN_SIGNED) || ((MODE) == ADC_SIGN_UNSIGNED))
/**
  * @}
  */ 


void HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig);

HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);

HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);

uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc);

HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef *hadc, uint32_t EventType, uint32_t Timeout);

HAL_StatusTypeDef HAL_ADC_InjectedStart_IT(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_InjectedStop_IT(ADC_HandleTypeDef* hadc);

uint32_t HAL_ADC_InjectedGetValue(ADC_HandleTypeDef *hadc);

HAL_StatusTypeDef HAL_ADC_Polling(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length, uint32_t Timeout);

HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc, ADC_InjectionConfTypeDef* sConfigInjected);

HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_InjectedStop(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_InjectedStart_IT(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_InjectedStop_IT(ADC_HandleTypeDef* hadc);

uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank);

HAL_StatusTypeDef HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef* hadc, ADC_MultiModeTypeDef* multimode);

HAL_StatusTypeDef HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);

FlagStatus HAL_ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);

void HAL_ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);

void HAL_ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);

ITStatus HAL_ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT);

void HAL_ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT);

#endif





