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
  * @brief   DAC Configuration regular Channel structure definition
  */
typedef struct
{    
    FunctionalState SelfCalibrateEn;    
    
    FunctionalState SampleEn;           /*!< Specifies voltage DAC sample and hold mode.
                                              This parameter can be ENABLE or DISABLE */
//use the trimvalue in NVR    
//    uint32_t TrimValue;                 /*!< Specifies the offset trimming value
//                                               This parameter must be a number between Min_Data = 1 and Max_Data = 31 */
    
    uint32_t BufferMode;                /*!< Specifies if voltage DAC output buffer is enabled or not.
                                              This parameter can be MDAC_VDAC_BUFFER_ENABLE or MDAC_VDAC_BUFFER_DISABLE */         
    
}VDAC_ChannelConfigTypeDef;

/**
  * @brief   DAC Configuration regular Channel structure definition
  */
typedef struct
{       
    uint32_t ITurn;                      
    
}IDAC_ChannelConfigTypeDef;


/**
  * @brief  MDAC handle Structure definition
  */
typedef struct 
{
    MDAC_TypeDef                 *Instance;     /*!< Register base address             */
}MDAC_HandleTypeDef;


#define MDAC_VDAC_BUFFER_ENABLE                     (0)
#define MDAC_VDAC_BUFFER_DISABLE                    (2)

#define IS_MDAC_INSTANCE(INSTANCE)                  ((INSTANCE) == MDAC)

#define IS_VDAC_CHANNEL_NUM(CH)                     ((CH) < 12)

#define IS_VDAC_BUFFER_MODE(MODE)                   (((MODE) == MDAC_VDAC_BUFFER_ENABLE) || \
                                                    (MODE) == MDAC_VDAC_BUFFER_DISABLE)

#define IS_VDAC_TRIM_VALUE(VAL)                     ((VAL) < 31)

#define IS_IDAC_CHANNEL_NUM(CH)                     ((CH) < 4)

#define ITURN_FACTORY                               (32)

#define IS_IDAC_ITURN(T)                            ((T) <= ITURN_FACTORY)

#define MDAC_MAX_V_CHANNEL_NUM                      (12)
#define MDAC_MAX_I_CHANNEL_NUM                      (4)



                                    
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

/**
  * @}
  */
  
  
void HAL_MDAC_MspInit(MDAC_HandleTypeDef *hMDAC);
__weak void HAL_MDAC_MspDeInit(MDAC_HandleTypeDef* hMDAC);

HAL_StatusTypeDef HAL_MDAC_Init(MDAC_HandleTypeDef *hMDAC);
HAL_StatusTypeDef HAL_MDAC_DeInit(MDAC_HandleTypeDef *hMDAC);

HAL_StatusTypeDef HAL_MDAC_ConfigVoltageChannel(MDAC_HandleTypeDef* hmdac, uint32_t Channel, VDAC_ChannelConfigTypeDef* Config);
HAL_StatusTypeDef HAL_MDAC_SetVoltageValue(MDAC_HandleTypeDef *hMDAC, uint32_t Channel, uint32_t Data);
uint32_t HAL_MDAC_GetVoltageValue(MDAC_HandleTypeDef* hMDAC, uint32_t Channel);

HAL_StatusTypeDef HAL_MDAC_ConfigCurrentChannel(MDAC_HandleTypeDef* hmdac, uint32_t Channel, IDAC_ChannelConfigTypeDef* Config);
HAL_StatusTypeDef HAL_MDAC_SetCurrentValue(MDAC_HandleTypeDef *hMDAC, uint32_t Channel, uint32_t Data);
uint32_t HAL_MDAC_GetCurrentValue(MDAC_HandleTypeDef* hMDAC, uint32_t Channel);

HAL_StatusTypeDef HAL_MDAC_SetVoltageTrim(MDAC_HandleTypeDef *hmdac, uint32_t Channel, uint32_t TrimVal);
uint32_t HAL_MDAC_GetVoltageTrimValue(MDAC_HandleTypeDef *hmdac, uint32_t Channel);

HAL_StatusTypeDef HAL_MDAC_VoltageSelfcalibrate(MDAC_HandleTypeDef *hmdac, uint32_t Channel);
#endif
