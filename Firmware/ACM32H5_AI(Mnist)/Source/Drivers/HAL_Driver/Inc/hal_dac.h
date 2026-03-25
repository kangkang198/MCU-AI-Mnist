/*
  ******************************************************************************
  * @file    HAL_DAC.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of DAC HAL module.
  ******************************************************************************
*/
#ifndef __HAL_DAC_H__
#define __HAL_DAC_H__

#include "acm32h5xx_hal_conf.h"


/**
  * @brief   DAC Configuration sample and hold Channel structure definition
  */
typedef struct
{
    uint32_t DAC_SampleTime ;          /*!< Specifies the Sample time for the selected channel.
                                          This parameter applies when DAC_SampleAndHold is DAC_SAMPLEANDHOLD_ENABLE.
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 1023 */

    uint32_t DAC_HoldTime ;            /*!< Specifies the hold time for the selected channel
                                          This parameter applies when DAC_SampleAndHold is DAC_SAMPLEANDHOLD_ENABLE.
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 1023 */

    uint32_t DAC_RefreshTime ;         /*!< Specifies the refresh time for the selected channel
                                          This parameter applies when DAC_SampleAndHold is DAC_SAMPLEANDHOLD_ENABLE.
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 255 */
}DAC_SampleAndHoldConfTypeDef;


typedef struct
{
    uint32_t DAC_Calibration ;          /*!< Specifies the Sample time for the selected channel.
                                          This parameter can be a value of @ref DAC_Calibration */

    uint32_t DAC_Calibration_TRIM ;            /*!< Specifies the hold time for the selected channel
                                          This parameter applies when DAC_SampleAndHold is DAC_SAMPLEANDHOLD_ENABLE.
                                          This parameter must be a number between Min_Data = 0 and Max_Data = 1023 */
}DAC_CalibrationConfTypeDef;

/**
  * @brief   DAC Configuration regular Channel structure definition
  */
typedef struct
{
    FunctionalState DAC_DMADoubleDataMode; /*!< Specifies if DMA double data mode should be enabled or not for the selected channel.
                                              This parameter can be ENABLE or DISABLE */

    FunctionalState DAC_SignedFormat;      /*!< Specifies if signed format should be used or not for the selected channel.
                                              This parameter can be ENABLE or DISABLE */  

    uint32_t DAC_SampleAndHold;            /*!< Specifies whether the DAC mode.
                                              This parameter can be a value of @ref DAC_SampleAndHold */
    
    union{
        uint32_t DAC_Trigger;              /*!< DAC normal trigger */ 
        uint32_t SawtoothResetTrigger;     /*!< DAC SawTooth wave reset trigger */ 
    };
    
    uint32_t SawtoothStepTrigger;          /*!< DAC SawTooth wave step trigger */ 

    uint32_t DAC_OutputBuffer;             /*!< Specifies whether the DAC channel output buffer is enabled or disabled.
                                               This parameter can be a value of @ref DAC_output_buffer */


    uint32_t DAC_ConnectOnChipPeripheral ; /*!< Specifies whether the DAC output is connected or not to on chip peripheral .
                                              This parameter can be a value of @ref DAC_ConnectOnChipPeripheral */

    uint32_t DAC_UserTrimming;             /*!< Specifies the trimming mode
                                              This parameter must be a value of @ref DAC_UserTrimming
                                              DAC_UserTrimming is either factory or user trimming */

    uint32_t DAC_TrimmingValue;             /*!< Specifies the offset trimming value
                                               i.e. when DAC_SampleAndHold is DAC_TRIMMING_USER.
                                               This parameter must be a number between Min_Data = 1 and Max_Data = 31 */

    DAC_SampleAndHoldConfTypeDef  DAC_SampleAndHoldConfig;  /*!< Sample and Hold settings */

}DAC_ChannelConfTypeDef;

/**
  * @brief  CAN handle Structure definition
  */
typedef struct 
{
    DAC_TypeDef                 *Instance;     /*!< Register base address             */

#ifdef HAL_DMA_MODULE_ENABLED    
    DMA_HandleTypeDef           *DMA_Handle1;  /*!< Pointer DMA handler for channel 1 */

    DMA_HandleTypeDef           *DMA_Handle2;  /*!< Pointer DMA handler for channel 2 */
#endif

}DAC_HandleTypeDef;


#define IS_DAC_INSTANCE(INSTANCE)                   (((INSTANCE) == DAC1) || ((INSTANCE) == DAC2))



/** @defgroup DAC_SampleAndHold DAC power mode
  * @{
  */
#define IS_DAC_SAMPLETIME(TIME)                     ((TIME) <= 0x000003FFU)
#define IS_DAC_HOLDTIME(TIME)                       ((TIME) <= 0x000003FFU)
#define IS_DAC_REFRESHTIME(TIME)                    ((TIME) <= 0x000000FFU)


/** @defgroup DAC_CHANNEL 
  * @{
  */

#define DAC_CHANNEL_1                           0x00000000U
#define DAC_CHANNEL_2                           0x00000010U
#define DAC_CHANNEL_Dual                        0x00000020U
#define IS_DAC_CHANNEL(CHANNEL)                 (((CHANNEL) == DAC_CHANNEL_1) || \
                                                ((CHANNEL) == DAC_CHANNEL_2) || \
                                                ((CHANNEL) == DAC_CHANNEL_Dual))
/**
  * @}
  */


#define DAC_CR_WAVE_DISABLE     (0U)
#define DAC_CR_WAVE_NOISE        (DAC_CR_WAVE1_0)
#define DAC_CR_WAVE_TRIANGLE    (DAC_CR_WAVE1_1)
#define DAC_CR_WAVE_SAWTOOTH    (DAC_CR_WAVE1_0 | DAC_CR_WAVE1_1)


/** @defgroup DACEx_SawtoothPolarityMode DAC Sawtooth polarity mode
  * @{
  */
#define DAC_SAWTOOTH_POLARITY_DECREMENT         0x00000000U             /*!< Sawtooth wave generation, polarity is decrement */
#define DAC_SAWTOOTH_POLARITY_INCREMENT         (DAC_STR1_STDIR1)       /*!< Sawtooth wave generation, polarity is increment */
#define IS_DAC_SAWTOOTH_POLARITY(POLARITY)      ((POLARITY == DAC_SAWTOOTH_POLARITY_DECREMENT) || \
                                                (POLARITY == DAC_SAWTOOTH_POLARITY_INCREMENT))         

/**
  * @}
  */
  /** @defgroup DAC_trigger 
  * @{
  */     
#define DAC_TRIGGER_NONE            0x00000000U                    /*!< conversion is automatic once the DAC_DHRxxxx register has been loaded, and not by external trigger */
#define DAC_TRIGGER_SOFTWARE        (0x00000000U | DAC_CR_TEN1)    /*!< conversion started by software trigger for DAC channel */
#define DAC_TRIGGER_T1_TRGO         (DAC_CR_TSEL1_0 | DAC_CR_TEN1) /*!< TIM1 TRGO selected as external conversion trigger for DAC channel. Refer to device datasheet for DACx availability. */
#define DAC_TRIGGER_T2_TRGO         (DAC_CR_TSEL1_1 | DAC_CR_TEN1) /*!< TIM2 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T4_TRGO         (DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0 | DAC_CR_TEN1) /*!< TIM4 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T5_TRGO         (DAC_CR_TSEL1_2 | DAC_CR_TEN1) /*!< TIM5 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T6_TRGO         (DAC_CR_TSEL1_2 | DAC_CR_TSEL1_0 | DAC_CR_TEN1) /*!< TIM6 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T7_TRGO         (DAC_CR_TSEL1_2 | DAC_CR_TSEL1_1 | DAC_CR_TEN1) /*!< TIM7 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T8_TRGO         (DAC_CR_TSEL1_2 | DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0 | DAC_CR_TEN1) /*!< TIM8 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_T15_TRGO        (DAC_CR_TSEL1_3 | DAC_CR_TEN1)  /*!< TIM15 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_LPT1_TRGO       (DAC_CR_TSEL1_3 | DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0 | DAC_CR_TEN1) /*!< LPTIM1 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_LPT2_TRGO       (DAC_CR_TSEL1_3 | DAC_CR_TSEL1_2 | DAC_CR_TEN1) /*!< LPTIM2 TRGO selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_EXTI9           (DAC_CR_TSEL1_3 | DAC_CR_TSEL1_2 | DAC_CR_TSEL1_0 | DAC_CR_TEN1) /*!< EXTI Line9 event selected as external conversion trigger for DAC channel */
#define DAC_TRIGGER_EXTI10          (DAC_CR_TSEL1_3 | DAC_CR_TSEL1_2 | DAC_CR_TSEL1_0 | DAC_CR_TEN1) /*!< EXTI Line9 event selected as external conversion trigger for DAC channel */

#define IS_DAC_TRIGGER(TRIGGER)     (((TRIGGER) == DAC_TRIGGER_NONE)    || \
                                    ((TRIGGER) == DAC_TRIGGER_SOFTWARE) || \
                                    ((TRIGGER) == DAC_TRIGGER_T1_TRGO)  || \
                                    ((TRIGGER) == DAC_TRIGGER_T2_TRGO)  || \
                                    ((TRIGGER) == DAC_TRIGGER_T4_TRGO)  || \
                                    ((TRIGGER) == DAC_TRIGGER_T5_TRGO)  || \
                                    ((TRIGGER) == DAC_TRIGGER_T6_TRGO)  || \
                                    ((TRIGGER) == DAC_TRIGGER_T7_TRGO)  || \
                                    ((TRIGGER) == DAC_TRIGGER_T8_TRGO)  || \
                                    ((TRIGGER) == DAC_TRIGGER_T15_TRGO) || \
                                    ((TRIGGER) == DAC_TRIGGER_LPT1_TRGO)|| \
                                    ((TRIGGER) == DAC_TRIGGER_LPT2_TRGO)|| \
                                    ((TRIGGER) == DAC_TRIGGER_EXTI9))
/**
  * @}
  */
  
/** @defgroup DAC_wave_generation 
  * @{
  */

#define DAC_WaveGeneration_None                 0x00000000U
#define DAC_WaveGeneration_Noise                0x00000001U
#define DAC_WaveGeneration_Triangle             0x00000002U
#define IS_DAC_GENERATE_WAVE(WAVE)              (((WAVE) == DAC_WaveGeneration_None) || \
                                                ((WAVE) == DAC_WaveGeneration_Noise) || \
                                                ((WAVE) == DAC_WaveGeneration_Triangle))
/**
  * @}
  */
/** @defgroup DAC_lfsrunmask_triangleamplitude
  * @{
  */
#define DAC_LFSRUNMASK_BIT0                     0x00000000U /*!< Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUNMASK_BITS1_0                  (DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS2_0                  (DAC_CR_MAMP1_1) /*!< Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS3_0                  (DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS4_0                  (DAC_CR_MAMP1_2) /*!< Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS5_0                  (DAC_CR_MAMP1_2| DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS6_0                  (DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1) /*!< Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS7_0                  (DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[7:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS8_0                  (DAC_CR_MAMP1_3) /*!< Unmask DAC channel LFSR bit[8:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS9_0                  (DAC_CR_MAMP1_3 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[9:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS10_0                 (DAC_CR_MAMP1_3 | DAC_CR_MAMP1_1) /*!< Unmask DAC channel LFSR bit[10:0] for noise wave generation */
#define DAC_LFSRUNMASK_BITS11_0                 (DAC_CR_MAMP1_3 | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Unmask DAC channel LFSR bit[11:0] for noise wave generation */
#define DAC_TRIANGLEAMPLITUDE_1                 0x00000000U /*!< Select max triangle amplitude of 1 */
#define DAC_TRIANGLEAMPLITUDE_3                 (DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 3 */
#define DAC_TRIANGLEAMPLITUDE_7                 (DAC_CR_MAMP1_1) /*!< Select max triangle amplitude of 7 */
#define DAC_TRIANGLEAMPLITUDE_15                (DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 15 */
#define DAC_TRIANGLEAMPLITUDE_31                (DAC_CR_MAMP1_2) /*!< Select max triangle amplitude of 31 */
#define DAC_TRIANGLEAMPLITUDE_63                (DAC_CR_MAMP1_2 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 63 */
#define DAC_TRIANGLEAMPLITUDE_127               (DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1) /*!< Select max triangle amplitude of 127 */
#define DAC_TRIANGLEAMPLITUDE_255               (DAC_CR_MAMP1_2 | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 255 */
#define DAC_TRIANGLEAMPLITUDE_511               (DAC_CR_MAMP1_3) /*!< Select max triangle amplitude of 511 */
#define DAC_TRIANGLEAMPLITUDE_1023              (DAC_CR_MAMP1_3 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 1023 */
#define DAC_TRIANGLEAMPLITUDE_2047              (DAC_CR_MAMP1_3 | DAC_CR_MAMP1_1) /*!< Select max triangle amplitude of 2047 */
#define DAC_TRIANGLEAMPLITUDE_4095              (DAC_CR_MAMP1_3 | DAC_CR_MAMP1_1 | DAC_CR_MAMP1_0) /*!< Select max triangle amplitude of 4095 */

#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE)        (((VALUE) == DAC_LFSRUNMASK_BIT0)   || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS1_0) || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS2_0) || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS3_0) || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS4_0) || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS5_0) || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS6_0) || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS7_0) || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS8_0) || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS9_0) || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS10_0) || \
                                                            ((VALUE) == DAC_LFSRUNMASK_BITS11_0) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_1) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_3) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_7) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_15) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_31) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_63) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_127) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_255) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_511) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_1023) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_2047) || \
                                                            ((VALUE) == DAC_TRIANGLEAMPLITUDE_4095))
/**
  * @}
  */
  
  /** @defgroup DAC_MODE
  * @{
  */

#define DAC_Mode_Normal_BufferEnable_OutPAD                         0x00000000U
#define DAC_Mode_Normal_BufferEnable_OutPAD_OutInternal             0x00000001U
#define DAC_Mode_Normal_BufferDisable_OutPAD                        0x00000002U
#define DAC_Mode_Normal_BufferDisable_OutPAD_OutInternal            0x00000003U

#define DAC_Mode_SampleAndHold_BufferEnable_OutPAD                  0x00000004U
#define DAC_Mode_SampleAndHold_BufferEnable_OutPAD_OutInternal      0x00000005U
#define DAC_Mode_SampleAndHold_BufferDisable_OutPAD_OutInternal     0x00000006U
#define DAC_Mode_SampleAndHold_BufferDisable_OutInternal            0x00000007U
#define IS_DAC_MODE(MODE)               (((MODE) == DAC_Mode_Normal_BufferEnable_OutPAD) || \
                                        ((MODE) == DAC_Mode_Normal_BufferEnable_OutPAD_OutInternal) || \
                                        ((MODE) == DAC_Mode_Normal_BufferDisable_OutPAD)|| \
                                        ((MODE) == DAC_Mode_Normal_BufferDisable_OutPAD_OutInternal)|| \
                                        ((MODE) == DAC_Mode_SampleAndHold_BufferEnable_OutPAD)|| \
                                        ((MODE) == DAC_Mode_SampleAndHold_BufferEnable_OutPAD_OutInternal)|| \
                                        ((MODE) == DAC_Mode_SampleAndHold_BufferDisable_OutPAD_OutInternal)|| \
                                        ((MODE) == DAC_Mode_SampleAndHold_BufferDisable_OutInternal))
/**
  * @}
  */
  
  /** @defgroup DAC_SampleAndHold DAC power mode
  * @{
  */
#define DAC_SAMPLEANDHOLD_DISABLE       0x00000000U
#define DAC_SAMPLEANDHOLD_ENABLE        (DAC_MCR_MODE1_2)
#define IS_DAC_SAMPLEANDHOLD(MODE)      (((MODE) == DAC_SAMPLEANDHOLD_DISABLE) || \
                                        ((MODE) == DAC_SAMPLEANDHOLD_ENABLE))
/**
  * @}
  */

                                    
  /** @defgroup DAC_UserTrimming DAC User Trimming
* @{
*/

#define DAC_TRIMMING_FACTORY                0x00000000U           /*!< Factory trimming */
#define DAC_TRIMMING_USER                   0x00000001U           /*!< User trimming */
#define IS_DAC_TRIMMING(TRIMMING)           (((TRIMMING) == DAC_TRIMMING_FACTORY) || \
                                            ((TRIMMING) == DAC_TRIMMING_USER))
#define IS_DAC_TRIMMINGVALUE(TRIMMINGVALUE) ((TRIMMINGVALUE) <= 0x1FU)
/**
  * @}
  */
  
  /** @defgroup DAC_Calibration 
  * @{
  */

#define DAC_Calibration_Disable             0x00000000U
#define DAC_Calibration_Enable              0x00000001U
#define IS_DAC_Calibration(Calibration)     (((Calibration) == DAC_Calibration_Disable) || \
                                            ((Calibration) == DAC_Calibration_Enable))
                                    
#define IS_DAC_Calibration_TRIM(TRIM)       ((TRIM) <= 0x1FU)                                  
/**
  * @}
  */
  /** @defgroup DAC_output_buffer DAC output buffer
  * @{
  */
#define DAC_OUTPUTBUFFER_ENABLE             0x00000000U
#define DAC_OUTPUTBUFFER_DISABLE            (DAC_MCR_MODE1_1)
#define IS_DAC_OUTPUT_BUFFER_STATE(STATE)   (((STATE) == DAC_OUTPUTBUFFER_ENABLE) || \
                                            ((STATE) == DAC_OUTPUTBUFFER_DISABLE))
/**
  * @}
  */
  
  
/** @defgroup DAC_ConnectOnChipPeripheral DAC ConnectOnChipPeripheral
  * @{
  */

#define DAC_CHIPCONNECT_EXTERNAL       (1UL << 0)
#define DAC_CHIPCONNECT_INTERNAL       (1UL << 1)
#define DAC_CHIPCONNECT_BOTH           (1UL << 2)

#define IS_DAC_CHIP_CONNECTION_BUFON(CONNECT) (((CONNECT) == DAC_CHIPCONNECT_EXTERNAL) || \
                                                     ((CONNECT) == DAC_CHIPCONNECT_BOTH))
                                                     
#define IS_DAC_CHIP_CONNECTION_NORMALMODE_BUFOFF(CONNECT) (((CONNECT) == DAC_CHIPCONNECT_EXTERNAL) || \
                                                    ((CONNECT) == DAC_CHIPCONNECT_INTERNAL))
                                         
#define IS_DAC_CHIP_CONNECTION_SHMODE_BUFOFF(CONNECT) (((CONNECT) == DAC_CHIPCONNECT_INTERNAL) || \
                                                ((CONNECT) == DAC_CHIPCONNECT_BOTH))
/**
  * @}
  */
                          
                                           
  /** @defgroup DAC_data_alignment DAC data alignment
  * @{
  */

#define DAC_DHR12R1_ALIGNMENT(__ALIGNMENT__)        (0x00000008U + (__ALIGNMENT__))
#define DAC_DHR12R2_ALIGNMENT(__ALIGNMENT__)        (0x00000014U + (__ALIGNMENT__))



#define DAC_DHR12RD_ALIGNMENT(__ALIGNMENT__)        (0x00000020U + (__ALIGNMENT__))

#define DAC_ALIGN_12B_R                     0x00000000U
#define DAC_ALIGN_12B_L                     0x00000004U
#define DAC_ALIGN_8B_R                      0x00000008U
#define IS_DAC_ALIGN(ALIGN)                 (((ALIGN) == DAC_ALIGN_12B_R) || \
                                            ((ALIGN) == DAC_ALIGN_12B_L) || \
                                            ((ALIGN) == DAC_ALIGN_8B_R))
/**
  * @}
  */
  
  
  
  
/* Initialization/de-initialization functions *********************************/
void HAL_DAC_IRQHandler(DAC_HandleTypeDef *hdac);
void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac);
void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac);
HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef *hdac);  
HAL_StatusTypeDef HAL_DAC_DeInit(DAC_HandleTypeDef* hdac); 
HAL_StatusTypeDef HAL_DAC_ConfigChannel(DAC_HandleTypeDef* hdac, DAC_ChannelConfTypeDef* sConfig, uint32_t Channel);

/* I/O operation functions ****************************************************/ 
HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef *hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef* hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t *pData, uint32_t Length, uint32_t Alignment);
HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef* hdac, uint32_t Channel);

/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data);
HAL_StatusTypeDef HAL_DACEx_DualSetValue(DAC_HandleTypeDef *hdac, uint32_t Alignment, uint32_t Data1, uint32_t Data2);
uint32_t HAL_DAC_GetValue(DAC_HandleTypeDef* hdac, uint32_t Channel);
uint32_t HAL_DACEx_DualGetValue(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude);
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude) ;
HAL_StatusTypeDef HAL_DACEx_SawtoothWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Polarity,uint32_t ResetData, uint32_t StepData);
HAL_StatusTypeDef HAL_DACEx_SawtoothWaveDataResetBySoftware(DAC_HandleTypeDef *hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DACEx_SawtoothWaveDataStep(DAC_HandleTypeDef *hdac, uint32_t Channel);
HAL_StatusTypeDef HAL_DACEx_SelfCalibrate(DAC_HandleTypeDef *hdac, DAC_ChannelConfTypeDef *sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_DACEx_SetUserTrimming(DAC_HandleTypeDef *hdac, DAC_ChannelConfTypeDef *sConfig, uint32_t Channel, uint32_t NewTrimmingValue);
uint32_t HAL_DACEx_GetTrimOffset(DAC_HandleTypeDef *hdac, uint32_t Channel);

 
#endif