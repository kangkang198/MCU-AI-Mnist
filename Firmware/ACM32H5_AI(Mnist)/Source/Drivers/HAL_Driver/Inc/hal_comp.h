
/******************************************************************************
*@file  : hal_comp.h
*@brief : COMP HAL module driver header file.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __HAL_COMP_H__
#define __HAL_COMP_H__

#include "acm32h5xx_hal_conf.h"


typedef struct
{
    uint32_t            InPSel;         //input plus select
    uint32_t            InMSel;         //input minus select
    uint32_t            Polarity;       //polarity 
    uint32_t            HYS;            //Hysteresis window
    uint32_t            BlankSel;       //blank source select
    uint32_t            FltEn;          //filt enable
    uint32_t            FltTime;        //filt time
    uint32_t            CrvEn;          //reference voltage divide enable 
    uint32_t            CrvSel;         //reference voltage source select
    uint32_t            CrvCfg;         //reference voltage divider factor config 
}COMP_InitTypeDef;


typedef struct
{
    COMP_TypeDef        *Instance;       // Register base address 
    COMP_InitTypeDef    Init;            // COMP required parameters 
    uint8_t             OutputLevelOrg;  // COMP OutputLevel original
    uint8_t             OutputLevel;     // COMP OutputLevel with filter
} COMP_HandleTypeDef;


#define COMP_CRVSEL_AVDD                    (0U)       
#define COMP_CRVSEL_VREF                    (COMP_CR_CRV_SEL)  

#define COMP_CRV_DISABLE                    (0U)       
#define COMP_CRV_ENABLE                     (COMP_CR_CRV_EN)   
 
#define COMP_POLARITY_NOINVERT              (0U)   
#define COMP_POLARITY_INVERT                (COMP_CR_POLARITY)   

#define COMP_FLT_DISABLE                    (0U)       
#define COMP_FLT_ENABLE                     (COMP_CR_FLTEN)   

#define COMP_FLTTIME_1CLK                   (0U)   
#define COMP_FLTTIME_2CLK                   (1U << COMP_CR_FLTTIME_Pos)   
#define COMP_FLTTIME_4CLK                   (2U << COMP_CR_FLTTIME_Pos)   
#define COMP_FLTTIME_16CLK                  (3U << COMP_CR_FLTTIME_Pos)   
#define COMP_FLTTIME_64CLK                  (4U << COMP_CR_FLTTIME_Pos)   
#define COMP_FLTTIME_256CLK                 (5U << COMP_CR_FLTTIME_Pos)   
#define COMP_FLTTIME_1024CLK                (6U << COMP_CR_FLTTIME_Pos)   
#define COMP_FLTTIME_4095CLK                (7U << COMP_CR_FLTTIME_Pos)   
   
#define COMP_BLANKSEL_NONE                  (0U)
#define COMP_BLANKSEL_S1                    (1U << COMP_CR_BLANKSEL_Pos)   
#define COMP_BLANKSEL_S2                    (2U << COMP_CR_BLANKSEL_Pos) 
#define COMP_BLANKSEL_S3                    (3U << COMP_CR_BLANKSEL_Pos) 
#define COMP_BLANKSEL_S4                    (4U << COMP_CR_BLANKSEL_Pos) 
#define COMP_BLANKSEL_S5                    (5U << COMP_CR_BLANKSEL_Pos) 
#define COMP_BLANKSEL_S6                    (6U << COMP_CR_BLANKSEL_Pos) 
#define COMP_BLANKSEL_S7                    (7U << COMP_CR_BLANKSEL_Pos) 

#define COMP1_BLANKSEL_NONE                 (0U)
#define COMP1_BLANKSEL_TIM1_OC5             (1U << COMP_CR_BLANKSEL_Pos)   
#define COMP1_BLANKSEL_TIM1_OC3             (2U << COMP_CR_BLANKSEL_Pos) 
#define COMP1_BLANKSEL_TIM3_OC3             (3U << COMP_CR_BLANKSEL_Pos) 
#define COMP1_BLANKSEL_TIM3_OC4             (4U << COMP_CR_BLANKSEL_Pos) 
#define COMP1_BLANKSEL_TIM8_OC5             (5U << COMP_CR_BLANKSEL_Pos) 
#define COMP1_BLANKSEL_TIM15_OC1            (6U << COMP_CR_BLANKSEL_Pos) 
#define COMP1_BLANKSEL_ALL                  (7U << COMP_CR_BLANKSEL_Pos) 

#define COMP_INPSEL_P0                      (0U)   
#define COMP_INPSEL_P1                      (1U << COMP_CR_INPSEL_Pos)

#define COMP_INMSEL_DACx                    (0U)   
#define COMP_INMSEL_P1                      (1U << COMP_CR_INMSEL_Pos)
#define COMP_INMSEL_P2                      (2U << COMP_CR_INMSEL_Pos)
#define COMP_INMSEL_VREF_AVDD               (3U << COMP_CR_INMSEL_Pos)

#define COMP1_INPSEL_PB0                    (0U)   
#define COMP1_INPSEL_PB2                    (1U << COMP_CR_INPSEL_Pos)   

#define COMP1_INMSEL_DAC1                   (0U)   
#define COMP1_INMSEL_PB1                    (1U << COMP_CR_INMSEL_Pos)   
#define COMP1_INMSEL_PC4                    (2U << COMP_CR_INMSEL_Pos)
#define COMP1_INMSEL_VREF_AVDD              (3U << COMP_CR_INMSEL_Pos)
 
#define COMP_HYS_NONE                       (0U) 
#define COMP_HYS_4                          (4U << COMP_CR_HYS_Pos) 
#define COMP_HYS_5                          (5U << COMP_CR_HYS_Pos) 
#define COMP_HYS_6                          (6U << COMP_CR_HYS_Pos) 
#define COMP_HYS_7                          (7U << COMP_CR_HYS_Pos) 


#define IS_COMP_INSTANCE(_INSTANCE_)        ((_INSTANCE_) == COMP1)


#define IS_COMP_CRVCFG(_CRVCFG_)            ((_CRVCFG_) <= 15U)

#define IS_COMP_CRVSEL(_CRVSEL_)            (((_CRVSEL_) == COMP_CRVSEL_AVDD) || \
                                             ((_CRVSEL_) == COMP_CRVSEL_VREF))
                                             
#define IS_COMP_CRVEN(_CRVEN_)              (((_CRVEN_) == COMP_CRV_DISABLE) || \
                                             ((_CRVEN_) == COMP_CRV_ENABLE))
                                           
#define IS_COMP_POLARITY(_POLARITY_)        (((_POLARITY_) == COMP_POLARITY_NOINVERT) || \
                                             ((_POLARITY_) == COMP_POLARITY_INVERT))

#define IS_COMP_FLTEN(_FLTEN_)              (((_FLTEN_) == COMP_FLT_DISABLE) || \
                                             ((_FLTEN_) == COMP_FLT_ENABLE))

#define IS_COMP_FLTTIME(_FLTTIME_)          (((_FLTTIME_) == COMP_FLTTIME_1CLK) || \
                                             ((_FLTTIME_) == COMP_FLTTIME_2CLK) || \
                                             ((_FLTTIME_) == COMP_FLTTIME_4CLK) || \
                                             ((_FLTTIME_) == COMP_FLTTIME_16CLK) || \
                                             ((_FLTTIME_) == COMP_FLTTIME_64CLK) || \
                                             ((_FLTTIME_) == COMP_FLTTIME_256CLK) || \
                                             ((_FLTTIME_) == COMP_FLTTIME_1024CLK) || \
                                             ((_FLTTIME_) == COMP_FLTTIME_4095CLK))

#define IS_COMP_BLANKSEL(_BLANKSEL_)        (((_BLANKSEL_) == COMP_BLANKSEL_NONE) || \
                                             ((_BLANKSEL_) == COMP_BLANKSEL_S1) || \
                                             ((_BLANKSEL_) == COMP_BLANKSEL_S2) || \
                                             ((_BLANKSEL_) == COMP_BLANKSEL_S3) || \
                                             ((_BLANKSEL_) == COMP_BLANKSEL_S4) || \
                                             ((_BLANKSEL_) == COMP_BLANKSEL_S5) || \
                                             ((_BLANKSEL_) == COMP_BLANKSEL_S6) || \
                                             ((_BLANKSEL_) == COMP_BLANKSEL_S7))

#define IS_COMP_INPSEL(_INPSEL_)            (((_INPSEL_) == COMP_INPSEL_P0) || \
                                             ((_INPSEL_) == COMP_INPSEL_P1))   

#define IS_COMP_INMSEL(_INMSEL_)            (((_INMSEL_) == COMP_INMSEL_DACx) || \
                                             ((_INMSEL_) == COMP_INMSEL_P1) || \
                                             ((_INMSEL_) == COMP_INMSEL_P2) || \
                                             ((_INMSEL_) == COMP_INMSEL_VREF_AVDD))

#define IS_COMP_HYS(_HYS_)                  (((_HYS_) == COMP_HYS_NONE) || \
                                             ((_HYS_) == COMP_HYS_4) || \
                                             ((_HYS_) == COMP_HYS_5) || \
                                             ((_HYS_) == COMP_HYS_6) || \
                                             ((_HYS_) == COMP_HYS_7))


void HAL_COMP_MspInit(COMP_HandleTypeDef* hcomp);
void HAL_COMP_MspDeInit(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_DeInit(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_Enable(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_Disable(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_GetOutputLevel(COMP_HandleTypeDef* hcomp);
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef* hcomp);

#endif

