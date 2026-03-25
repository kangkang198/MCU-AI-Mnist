/******************************************************************************
*@file  : hal_tkey.h
*@brief : Header file of TKEY HAL module.
******************************************************************************/
#ifndef __HAL_TKEY_H__
#define __HAL_TKEY_H__

#include "hal.h"



  
/** @defgroup TKEY_Mode
  * @{
  */
#define TKEY_MODE_CSD                               (0U)
#define TKEY_MODE_CSA                               (TKEY_CR_TKMS)
#define IS_TKEY_MODE(__MODE__)                      (((__MODE__) == TKEY_MODE_CSD)  || \
                                                    ((__MODE__) == TKEY_MODE_CSA))
/**
  * @}
  */
  
/** @defgroup TKEY_Work_Mode
  * @{
  */
#define TKEY_WORK_MODE_NORMAL                       (0U)
#define TKEY_WORK_MODE_AUTO                         (TKEY_CR_AUTO)
#define IS_TKEY_WORK_MODE(__WORKMODE__)             (((__WORKMODE__) == TKEY_WORK_MODE_NORMAL)  || \
                                                    ((__WORKMODE__) == TKEY_WORK_MODE_AUTO))
/**
  * @}
  */
  
/** @defgroup TKEY_Scan_Mode
  * @{
  */
#define TKEY_SCAN_MODE_SINGLE                       (0U)
#define TKEY_SCAN_MODE_CONT                         (TKEY_CR_CONT)
#define IS_TKEY_SCAN_MODE(__SCANMODE__)             (((__SCANMODE__) == TKEY_SCAN_MODE_SINGLE)  || \
                                                    ((__SCANMODE__) == TKEY_SCAN_MODE_CONT))
/**
  * @}
  */
   
/** @defgroup TKEY_Shield_State
  * @{
  */
#define TKEY_SHIELD_DISABLE                         (0U)
#define TKEY_SHIELD_ENABLE                          (TKEY_CR_SHIELDEN)
#define IS_TKEY_SHIELD(__SHIELD__)                  (((__SHIELD__) == TKEY_SHIELD_DISABLE)  || \
                                                    ((__SHIELD__) == TKEY_SHIELD_ENABLE))
/**
  * @}
  */


/** @defgroup TKEY_Filter_Num
  * @{
  */
#define TKEY_FILTER_NONE                            (0U)
#define TKEY_FILTER_1                               (TKEY_CFGR1_FLTSEL_0)
#define TKEY_FILTER_2                               (TKEY_CFGR1_FLTSEL_1)
#define TKEY_FILTER_3                               (TKEY_CFGR1_FLTSEL_0 | TKEY_CFGR1_FLTSEL_1)
#define TKEY_FILTER_4                               (TKEY_CFGR1_FLTSEL_2)
#define TKEY_FILTER_5                               (TKEY_CFGR1_FLTSEL_2 | TKEY_CFGR1_FLTSEL_0)
#define TKEY_FILTER_6                               (TKEY_CFGR1_FLTSEL_2 | TKEY_CFGR1_FLTSEL_1)
#define TKEY_FILTER_7                               (TKEY_CFGR1_FLTSEL_2 | TKEY_CFGR1_FLTSEL_1 | TKEY_CFGR1_FLTSEL_0)
#define IS_TKEY_FILTER(__FILTER__)                  (((__FILTER__) == TKEY_FILTER_NONE)  || \
                                                    ((__FILTER__) == TKEY_FILTER_1)      || \
                                                    ((__FILTER__) == TKEY_FILTER_2)      || \
                                                    ((__FILTER__) == TKEY_FILTER_3)      || \
                                                    ((__FILTER__) == TKEY_FILTER_4)      || \
                                                    ((__FILTER__) == TKEY_FILTER_5)      || \
                                                    ((__FILTER__) == TKEY_FILTER_6)      || \
                                                    ((__FILTER__) == TKEY_FILTER_7))
/**
  * @}
  */ 

/** @defgroup TKEY_Sample_Num
  * @{
  */
#define TKEY_SMAPLE_1                               (0U)
#define TKEY_SMAPLE_3                               (TKEY_CFGR1_SMPSEL_0)
#define TKEY_SMAPLE_6                               (TKEY_CFGR1_SMPSEL_1)
#define TKEY_SMAPLE_10                              (TKEY_CFGR1_SMPSEL_0 | TKEY_CFGR1_SMPSEL_1)
#define IS_TKEY_SMAPLE(__SAMPLE__)                  (((__SAMPLE__) == TKEY_SMAPLE_1)    || \
                                                    ((__SAMPLE__) == TKEY_SMAPLE_3)     || \
                                                    ((__SAMPLE__) == TKEY_SMAPLE_6)     || \
                                                    ((__SAMPLE__) == TKEY_SMAPLE_10))
/**
  * @}
  */ 

/** @defgroup TKEY_VLDO
  * @{
  */
#define TKEY_LDO_1V6                                (0U)
#define TKEY_LDO_2V0                                (TKEY_CFGR1_VCHRSEL_0)
#define TKEY_LDO_2V4                                (TKEY_CFGR1_VCHRSEL_1)
#define TKEY_LDO_VDD33                              (TKEY_CFGR1_VCHRSEL_0 | TKEY_CFGR1_VCHRSEL_1)
#define IS_TKEY_VLDO(__VLDO__)                      (((__VLDO__) == TKEY_LDO_1V6)       || \
                                                    ((__VLDO__) == TKEY_LDO_2V0)        || \
                                                    ((__VLDO__) == TKEY_LDO_2V4)        || \
                                                    ((__VLDO__) == TKEY_LDO_VDD33))
/**
  * @}
  */ 

/** @defgroup TKEY_VREF
  * @{
  */
#define TKEY_VREF_QUARTER_VLDO                      (0U)
#define TKEY_VREF_HALF_VLDO                         (TKEY_CFGR1_VCMPSEL_0)
#define TKEY_VREF_THREE_QUARTER_VLDO                (TKEY_CFGR1_VCMPSEL_1)
#define TKEY_VREF_VBG                               (TKEY_CFGR1_VCMPSEL_0 | TKEY_CFGR1_VCMPSEL_1)
#define IS_TKEY_VREF(__VREF__)                      (((__VREF__) == TKEY_VREF_QUARTER_VLDO)         || \
                                                    ((__VREF__) == TKEY_VREF_HALF_VLDO)             || \
                                                    ((__VREF__) == TKEY_VREF_THREE_QUARTER_VLDO)    || \
                                                    ((__VREF__) == TKEY_VREF_VBG))
/**
  * @}
  */ 

/** @defgroup TKEY_Spread_State
  * @{
  */
#define TKEY_SPREAD_DISABLE                         (0U)
#define TKEY_SPREAD_ENABLE                          (TKEY_CR_SPREAD)
#define IS_TKEY_SPREAD(__SPREAD__)                  (((__SPREAD__) == TKEY_SPREAD_DISABLE)  || \
                                                    ((__SPREAD__) == TKEY_SPREAD_ENABLE))
/**
  * @}
  */

/** @defgroup TKEY_Random_Jitter
  * @{
  */
#define TKEY_RADOM_JITTER_1                         (0U)
#define TKEY_RADOM_JITTER_1_2                       (TKEY_CR_RANDM_0)
#define TKEY_RADOM_JITTER_1_2_3                     (TKEY_CR_RANDM_1)
#define TKEY_RADOM_JITTER_1_2_3_4                   (TKEY_CR_RANDM_0 | TKEY_CR_RANDM_1)
#define IS_TKEY_RADOM_JITTER(__JITTER__)            (((__JITTER__) == TKEY_VREF_QUARTER_VLDO)       || \
                                                    ((__JITTER__) == TKEY_VREF_HALF_VLDO)           || \
                                                    ((__JITTER__) == TKEY_VREF_THREE_QUARTER_VLDO)  || \
                                                    ((__JITTER__) == TKEY_VREF_VBG))
/**
  * @}
  */

/** @defgroup TKEY_Scan_Interval
  * @{
  */
#define IS_TKEY_SCAN_INTERVAL(__INTERVAL__)         ((__INTERVAL__) <= 0xffffU)           
/**
  * @}
  */

/** @defgroup TKEY_ScanClk_Source
  * @{
  */
#define TKEY_SCAN_CLK_SRC_PCLK                      (0U)
#define TKEY_SCAN_CLK_SRC_RC4M                      (1U)
#define TKEY_SCAN_CLK_SRC_RC64M                     (2U)
#define IS_TKEY_SCAN_CLK_SOURCE(__SRC__)            (((__SRC__) == TKEY_SCAN_CLK_SRC_PCLK)  || \
                                                    ((__SRC__) == TKEY_SCAN_CLK_SRC_RC4M)   || \
                                                    ((__SRC__) == TKEY_SCAN_CLK_SRC_RC64M))           
/**
  * @}
  */
  
/** @defgroup TKEY_CtrlClk_Source
  * @{
  */
#define TKEY_CTRL_CLK_SRC_RC32K                     (0U)
#define TKEY_CTRL_CLK_SRC_XTL                       (1U)
#define IS_TKEY_CTRL_CLK_SOURCE(__SRC__)            (((__SRC__) == TKEY_CTRL_CLK_SRC_RC32K)  || \
                                                    ((__SRC__) == TKEY_CTRL_CLK_SRC_XTL))           
/**
  * @}
  */

/** @defgroup TKEY_Scan_Clk_Prescale
  * @{
  */
#define IS_TKEY_SCAN_CLK_PRESCALE(__PRESCALE__)     ((__PRESCALE__) <= 0xffU)           
/**
  * @}
  */


/** @defgroup TKEY_Scan_Clk_SW1HSW2L
  * @{
  */
#define IS_TKEY_SCAN_CLK_SW1HSW2L(__SW1HSW2L__)     ((__SW1HSW2L__) <= 0xffU)           
/**
  * @}
  */  


/** @defgroup TKEY_Scan_Clk_SW1LSW2H
  * @{
  */
#define IS_TKEY_SCAN_CLK_SW1LSW2H(__SW1LSW2H__)     ((__SW1LSW2H__) <= 0xffU)           
/**
  * @}
  */

/** @defgroup TKEY_ScanTimeout_PwmCycle
  * @{
  */
#define IS_TKEY_SCAN_TIMEOUT_PWM_CYCLE(__VALUE__)   ((__VALUE__) <= 0xfffU)           
/**
  * @}
  */  


/** @defgroup TKEY_IT_Flag 
  * @{
  */  
#define TKEY_IT_FLAG_EOC                            (1 << 0)
#define TKEY_IT_FLAG_YESTOUCH                       (1 << 1)
#define TKEY_IT_FLAG_TIMEOUT                        (1 << 2)
#define TKEY_IT_FLAG_BUSY                           (1 << 3) 
#define TKEY_IT_FLAG_DONE                           (1 << 8) 
#define TKEY_IT_FLAG_CHG                            (1 << 9)  
#define TKEY_IT_FLAG_CHGDONE                        (1 << 10)
#define TKEY_IT_FLAG_MEOC                           (1 << 11)
#define TKEY_IT_FLAG_ALL                            (0xffff)
#define IS_TKEY_IT_FLAG(__SEL__)                    (((__SEL__) == TKEY_IT_FLAG_EOC)        || \
                                                    ((__SEL__) == TKEY_IT_FLAG_YESTOUCH)    || \
                                                    ((__SEL__) == TKEY_IT_FLAG_TIMEOUT)     || \
                                                    ((__SEL__) == TKEY_IT_FLAG_BUSY)        || \
                                                    ((__SEL__) == TKEY_IT_FLAG_DONE)        || \
                                                    ((__SEL__) == TKEY_IT_FLAG_CHG)         || \
                                                    ((__SEL__) == TKEY_IT_FLAG_CHGDONE)     || \
                                                    ((__SEL__) == TKEY_IT_FLAG_MEOC)        || \
                                                    ((__SEL__) <= TKEY_IT_FLAG_ALL))   
/**
  * @}
  */   


/** @defgroup TKEY_Channel_Number 
* @{
*/
#define TKEY_CHANNEL_0                              (0U)    
#define TKEY_CHANNEL_1                              (1U)    
#define TKEY_CHANNEL_2                              (2U)    
#define TKEY_CHANNEL_3                              (3U)    
#define TKEY_CHANNEL_4                              (4U)    
#define TKEY_CHANNEL_5                              (5U)    
#define TKEY_CHANNEL_6                              (6U)    
#define TKEY_CHANNEL_7                              (7U)    
#define TKEY_CHANNEL_8                              (8U)    
#define TKEY_CHANNEL_9                              (9U)    
#define TKEY_CHANNEL_10                             (10U)    
#define TKEY_CHANNEL_11                             (11U)    
#define TKEY_CHANNEL_12                             (12U)    
#define TKEY_CHANNEL_13                             (13U)    
#define TKEY_CHANNEL_14                             (14U)    
#define TKEY_CHANNEL_15                             (15U)         
#define IS_TKEY_CHANNEL(__CHANNEL__)                (((__CHANNEL__) == TKEY_CHANNEL_0)  || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_1)   || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_2)   || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_3)   || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_4)   || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_5)   || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_6)   || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_7)   || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_8)   || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_9)   || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_10)  || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_11)  || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_12)  || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_13)  || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_14)  || \
                                                    ((__CHANNEL__) == TKEY_CHANNEL_15))

/** @defgroup TKEY_Channel_State 
* @{
*/  
#define TKEY_CHANNEL_0_EN                           (TKEY_CXENR_CX0EN)    
#define TKEY_CHANNEL_1_EN                           (TKEY_CXENR_CX1EN)    
#define TKEY_CHANNEL_2_EN                           (TKEY_CXENR_CX2EN)    
#define TKEY_CHANNEL_3_EN                           (TKEY_CXENR_CX3EN)    
#define TKEY_CHANNEL_4_EN                           (TKEY_CXENR_CX4EN)    
#define TKEY_CHANNEL_5_EN                           (TKEY_CXENR_CX5EN)    
#define TKEY_CHANNEL_6_EN                           (TKEY_CXENR_CX6EN)    
#define TKEY_CHANNEL_7_EN                           (TKEY_CXENR_CX7EN)    
#define TKEY_CHANNEL_8_EN                           (TKEY_CXENR_CX8EN)    
#define TKEY_CHANNEL_9_EN                           (TKEY_CXENR_CX9EN)    
#define TKEY_CHANNEL_10_EN                          (TKEY_CXENR_CX10EN)    
#define TKEY_CHANNEL_11_EN                          (TKEY_CXENR_CX11EN)    
#define TKEY_CHANNEL_12_EN                          (TKEY_CXENR_CX12EN)    
#define TKEY_CHANNEL_13_EN                          (TKEY_CXENR_CX13EN)    
#define TKEY_CHANNEL_14_EN                          (TKEY_CXENR_CX14EN)    
#define TKEY_CHANNEL_15_EN                          (TKEY_CXENR_CX15EN)
#define TKEY_CHANNEL_ALL_EN                         (0xffffU)
#define TKEY_CHANNEL_ALL_DISABLE                    (0U)         
#define IS_TKEY_CHANNEL_STATE(__STATE__)            ((__STATE__) <= 0xffffU)  
                                                    
 
/** @defgroup TKEY_ChargeNumDone_State
  * @{
  */
#define TKEY_CHGNUMDONE_DISABLE                     (0U)
#define TKEY_CHGNUMDONE_ENABLE                      (TKEY_CR_CHGDONEEN)
#define IS_TKEY_CHGNUMDONE(__STATE__)               (((__STATE__) == TKEY_CHGNUMDONE_ENABLE)  || \
                                                    ((__STATE__) == TKEY_CHGNUMDONE_DISABLE))
/**
  * @}
  */


/** @defgroup TKEY_ChargeEachDone_State
  * @{
  */
#define TKEY_CHGEACHDONE_DISABLE                    (0U)
#define TKEY_CHGEACHDONE_ENABLE                     (TKEY_CR_CHGEN)
#define IS_TKEY_CHGEACHDONE(__STATE__)              (((__STATE__) == TKEY_CHGEACHDONE_ENABLE)  || \
                                                    ((__STATE__) == TKEY_CHGEACHDONE_DISABLE))
/**
  * @}
  */

/** @defgroup TKEY_Cs_DisChargeTimeOrCMPWaitTime
  * @{
  */
#define IS_TKEY_CSDISCHARGETIME_CMPWAITTIME(__VALUE__)          ((__VALUE__) <= 0xfU)           
/**
  * @}
  */

/** @defgroup TKEY_CompFilter_Num
  * @{
  */
#define IS_TKEY_COMPFILTERNUM(__VALUE__)            ((__VALUE__) <= 0xfU)           
/**
  * @}
  */

/** @defgroup TKEY_CompFilter_State
  * @{
  */
#define TKEY_COMPFILTER_DISABLE                     (0U)
#define TKEY_COMPFILTER_ENABLE                      (TKEY_CFLTR_CFLTEN)
#define IS_TKEY_COMPFILTER(__STATE__)               (((__STATE__) == TKEY_COMPFILTER_ENABLE)  || \
                                                    ((__STATE__) == TKEY_COMPFILTER_DISABLE))
/**
  * @}
  */  
  
/** @defgroup TKEY_ChargeNumber
  * @{
  */
#define IS_TKEY_CHARGENUM(__VALUE__)                ((__VALUE__) <= 0xffffU)           
/**
  * @}
  */ 

/** @defgroup TKEY_ChargeDoneWaitTime
  * @{
  */
#define IS_TKEY_CHARGEDONEWAITTIME(__VALUE__)       ((__VALUE__) <= 0xffffU)           
/**
  * @}
  */
  
/** @defgroup TKEY_MutualDelay
  * @{
  */
#define IS_TKEY_MUTUAL_DELAY_TIME(__TIME__)         ((__TIME__) <= 0xffU)           
/**
  * @}
  */

/** @defgroup TKEY_MutualDelay_State
  * @{
  */
#define TKEY_MUTUAL_DELAY_DISABLE                   (0U)
#define TKEY_MUTUAL_DELAY_ENABLE                    (TKEY_MUTUALR_MTXDLYEN)
#define IS_TKEY_MUTUAL_DELAY_STATE(__STATE__)       (((__STATE__) == TKEY_MUTUAL_DELAY_DISABLE)  || \
                                                    ((__STATE__) == TKEY_MUTUAL_DELAY_ENABLE))
/**
  * @}
  */ 

/** @defgroup TKEY_MutualReset_State
  * @{
  */
#define TKEY_MUTUAL_RESET_DISABLE                   (0U)
#define TKEY_MUTUAL_RESET_ENABLE                    (TKEY_MUTUALR_MTXRST)
#define IS_TKEY_MUTUAL_RESET(__STATE__)             (((__STATE__) == TKEY_MUTUAL_RESET_DISABLE)  || \
                                                    ((__STATE__) == TKEY_MUTUAL_RESET_ENABLE))
/**
  * @}
  */ 
  
/** @defgroup TKEY_Mutual_Channel_State 
* @{
*/  
#define TKEY_MUTUAL_CHANNEL0_EN                     (TKEY_TXENR1_TX0EN)    
#define TKEY_MUTUAL_CHANNEL1_EN                     (TKEY_TXENR1_TX1EN)    
#define TKEY_MUTUAL_CHANNEL2_EN                     (TKEY_TXENR1_TX2EN)    
#define TKEY_MUTUAL_CHANNEL3_EN                     (TKEY_TXENR1_TX3EN)    
#define TKEY_MUTUAL_CHANNEL4_EN                     (TKEY_TXENR1_TX4EN)    
#define TKEY_MUTUAL_CHANNEL5_EN                     (TKEY_TXENR1_TX5EN)    
#define TKEY_MUTUAL_CHANNEL6_EN                     (TKEY_TXENR1_TX6EN)    
#define TKEY_MUTUAL_CHANNEL7_EN                     (TKEY_TXENR1_TX7EN)    
#define TKEY_MUTUAL_CHANNEL8_EN                     (TKEY_TXENR1_TX8EN)    
#define TKEY_MUTUAL_CHANNEL9_EN                     (TKEY_TXENR1_TX9EN)    
#define TKEY_MUTUAL_CHANNEL10_EN                    (TKEY_TXENR1_TX10EN)    
#define TKEY_MUTUAL_CHANNEL11_EN                    (TKEY_TXENR1_TX11EN)    
#define TKEY_MUTUAL_CHANNEL12_EN                    (TKEY_TXENR1_TX12EN)    
#define TKEY_MUTUAL_CHANNEL13_EN                    (TKEY_TXENR1_TX13EN)    
#define TKEY_MUTUAL_CHANNEL14_EN                    (TKEY_TXENR1_TX14EN)    
#define TKEY_MUTUAL_CHANNEL15_EN                    (TKEY_TXENR1_TX15EN)
#define TKEY_MUTUAL_CHANNEL16_EN                    (TKEY_TXENR2_TX16EN)
#define TKEY_MUTUAL_CHANNEL17_EN                    (TKEY_TXENR2_TX17EN)
#define TKEY_MUTUAL_CHANNEL18_EN                    (TKEY_TXENR2_TX18EN)
#define TKEY_MUTUAL_CHANNEL19_EN                    (TKEY_TXENR2_TX19EN)
#define TKEY_MUTUAL_CHANNEL20_EN                    (TKEY_TXENR2_TX20EN)
#define TKEY_MUTUAL_CHANNEL21_EN                    (TKEY_TXENR2_TX21EN)
#define TKEY_MUTUAL_CHANNEL22_EN                    (TKEY_TXENR2_TX22EN)
#define TKEY_MUTUAL_CHANNEL23_EN                    (TKEY_TXENR2_TX23EN)
#define TKEY_MUTUAL_CHANNEL24_EN                    (TKEY_TXENR2_TX24EN)
#define TKEY_MUTUAL_CHANNEL25_EN                    (TKEY_TXENR2_TX25EN)
#define TKEY_MUTUAL_CHANNEL_ALL_EN                  (0x03ffffffU)
#define TKEY_MUTUAL_CHANNEL_ALL_DISABLE             (0U)         
#define IS_TKEY_MUTUAL_CHANNEL_STATE(__STATE__)     ((__STATE__) <= 0x03ffffffU)    

/** @defgroup TKEY_DisChargeMode
  * @{
  */ 
#define TKEY_DISMS_DISCHAG_RES                      (0U)
#define TKEY_DISMS_DISCHAG_CURRENT                  (TKEY_CR_DISMS_0)
#define TKEY_DISMS_DISCHAG_RES_PAY_CURRENT          (TKEY_CR_DISMS_1)
#define TKEY_DISMS_DISCHAG_CURRENT_PAY_RES          (TKEY_CR_DISMS_0 | TKEY_CR_DISMS_1)
#define TKEY_DISMS_DISCHAG_RES_CURRENT              (TKEY_CR_DISMS_2)
#define IS_TKEY_DISMS(__MODE__)                     (((__MODE__) == TKEY_DISMS_DISCHAG_RES)             || \
                                                    ((__MODE__) == TKEY_DISMS_DISCHAG_CURRENT)          || \
                                                    ((__MODE__) == TKEY_DISMS_DISCHAG_RES_PAY_CURRENT)  || \
                                                    ((__MODE__) == TKEY_DISMS_DISCHAG_CURRENT_PAY_RES)  || \
                                                    ((__MODE__) == TKEY_DISMS_DISCHAG_RES_CURRENT))
/**
  * @}
  */  
  

/** @defgroup TKEY_Precharge_State
  * @{
  */
#define TKEY_PRECHARGE_DISABLE                      (0U)
#define TKEY_PRECHARGE_ENABLE                       (TKEY_CR_PCEN)
#define IS_TKEY_PRECHARGE(__STATE__)                (((__STATE__) == TKEY_PRECHARGE_ENABLE)  || \
                                                    ((__STATE__) == TKEY_PRECHARGE_DISABLE))
/**
  * @}
  */  

/** @defgroup TKEY_DischargeCurrent
  * @{
  */
#define IS_TKEY_DISCHARGECURRENT(__VALUE__)         ((__VALUE__) <= 0xffU)           
/**
  * @}
  */

/** @defgroup TKEY_DischargeRes
  * @{
  */
#define IS_TKEY_DISCHARGERES(__VALUE__)             ((__VALUE__) <= 0xffU)           
/**
  * @}
  */

/** @defgroup TKEY_SampleBitClkDiv
  * @{
  */
#define IS_TKEY_SAMPLEBITCLKDIV(__VALUE__)          ((__VALUE__) <= 0xffU)           
/**
  * @}
  */  

/** @defgroup TKEY_ResCompensate
  * @{
  */
#define TKEY_RESCOMPENSTATE_0_1K                    (0U)
#define TKEY_RESCOMPENSTATE_2K                      (1U)
#define TKEY_RESCOMPENSTATE_4K                      (2U)
#define TKEY_RESCOMPENSTATE_8K                      (3U)
#define IS_TKEY_RESCOMPENSTATE(__VALUE__)           (((__VALUE__) == TKEY_RESCOMPENSTATE_0_1K)  || \
                                                    ((__VALUE__) == TKEY_RESCOMPENSTATE_2K)     || \
                                                    ((__VALUE__) == TKEY_RESCOMPENSTATE_4K)     || \
                                                    ((__VALUE__) == TKEY_RESCOMPENSTATE_8K))           
/**
  * @}
  */

/** @defgroup TKEY_CapCompensate
  * @{
  */
#define TKEY_CAPCOMPENSTATE_0PF                     (0U)
#define TKEY_CAPCOMPENSTATE_2PF                     (1U)
#define TKEY_CAPCOMPENSTATE_4PF                     (2U)
#define TKEY_CAPCOMPENSTATE_6PF                     (3U)
#define TKEY_CAPCOMPENSTATE_8PF                     (4U)
#define TKEY_CAPCOMPENSTATE_10PF                    (5U)
#define TKEY_CAPCOMPENSTATE_12PF                    (6U)
#define TKEY_CAPCOMPENSTATE_14PF                    (7U)
#define IS_TKEY_CAPCOMPENSTATE(__VALUE__)           (((__VALUE__) == TKEY_CAPCOMPENSTATE_0PF)   || \
                                                    ((__VALUE__) == TKEY_CAPCOMPENSTATE_2PF)    || \
                                                    ((__VALUE__) == TKEY_CAPCOMPENSTATE_4PF)    || \
                                                    ((__VALUE__) == TKEY_CAPCOMPENSTATE_6PF)    || \
                                                    ((__VALUE__) == TKEY_CAPCOMPENSTATE_8PF)    || \
                                                    ((__VALUE__) == TKEY_CAPCOMPENSTATE_10PF)   || \
                                                    ((__VALUE__) == TKEY_CAPCOMPENSTATE_12PF)   || \
                                                    ((__VALUE__) == TKEY_CAPCOMPENSTATE_14PF))           
/**
  * @}
  */

/** @defgroup TKEY_Auto_Baseline
  * @{
  */
#define IS_TKEY_AUTO_BASELINE(__VALUE__)            ((__VALUE__) <= 0xffffU)           
/**
  * @}
  */
  
/** @defgroup TKEY_Auto_Threshold
  * @{
  */
#define IS_TKEY_AUTO_THRESHOLD(__VALUE__)            ((__VALUE__) <= 0xffU)           
/**
  * @}
  */

  
  
/**
  * @brief  TKEY Init Structure definition
  */
typedef struct
{
    uint32_t                    Mode;                           /*!< TKEY mode selection. 
                                                                    This parameter can be a value of @ref TKEY_Mode */        
    uint32_t                    WorkMode;                       /*!< Working mode. 
                                                                    This parameter can be a value of @ref TKEY_Work_Mode */  
    uint32_t                    ScanMode;                       /*!< Scan mode. 
                                                                    This parameter can be a value of @ref TKEY_Scan_Mode */     
    uint32_t                    ShieldEn;                       /*!< Shield channel enable control. 
                                                                    This parameter can be a value of @ref TKEY_Shield_State */ 
    uint32_t                    FilterNum;                      /*!< Hardware filtering frequency selection. 
                                                                    This parameter can be a value of @ref TKEY_Filter_Num */         
    uint32_t                    Vldo;                           /*!< Charging voltage VLDO selection. 
                                                                    This parameter can be a value of @ref TKEY_VLDO */     
    uint32_t                    Vref;                           /*!< Comparator voltage VREF selection. 
                                                                    This parameter can be a value of @ref TKEY_VREF */     
    uint32_t                    SpreadEn;                       /*!< Scan clock spread spectrum enable. 
                                                                    This parameter can be a value of @ref TKEY_Spread_State */ 
    uint32_t                    SampleNum;                      /*!< Sampling frequency selection. 
                                                                    This parameter can be a value of @ref TKEY_Sample_Num */
    uint32_t                    ChannelEn;                      /*!< Specify the enable TKEY channels. 
                                                                    This parameter can be a value of @ref TKEY_Channel_State */                                                                      
}TKEY_InitTypeDef;
/**
  * @}
  */

/**
  * @brief  TKEY Timing parameters structure definition
  */
typedef struct
{
//    uint32_t                    ScanClkSrc;                     /*!< TKEY module scanning clock source. 
//                                                                    This parameter can be a value of @ref TKEY_ScanClk_Source */   
//    uint32_t                    CtrlClkSrc;                     /*!< TK module controls clock source. 
//                                                                    This parameter can be a value of @ref TKEY_CtrlClk_Source */   
    uint32_t                    RandomJitterNum;                /*!< Scan clock random jitter value. 
                                                                    This parameter can be a value of @ref TKEY_Random_Jitter */   
    uint32_t                    ScanInterval;                   /*!< The interval time between two sets of scans. 
                                                                    This parameter can be a value of @ref TKEY_Scan_Interval */       
    uint32_t                    ScanClkPrescale;                /*!< Scanning clock division. 
                                                                    This parameter can be a value of @ref TKEY_Scan_Clk_Prescale */   
    uint32_t                    ScanClkSW1HSW2L;                /*!< Scan clock SW1 high level (SW2 low level) time.
                                                                    This parameter can be a value of @ref TKEY_Scan_Clk_SW1HSW2L */       
    uint32_t                    ScanClkSW1LSW2H;                /*!< Scan clock SW1 low level (SW2 high level) time. 
                                                                    This parameter can be a value of @ref TKEY_Scan_Clk_SW1LSW2H */   
    uint32_t                    TimeoutOrPwmCycle;              /*!< Set scan timeout or PWM cycle length. 
                                                                    This parameter can be a value of @ref TKEY_ScanTimeout_PwmCycle */       
    uint32_t                    DischargeTimeOrCMPWaitTime;     /*!< Set Cs capacitor discharge time or comparer wait time. 
                                                                    This parameter can be a value of @ref TKEY_Cs_DisChargeTime */       
}TKEY_TimingInitTypeDef;
/**
  * @}
  */

/**
  * @brief  TKEY handle Structure definition
  */
typedef struct
{
    TKEY_InitTypeDef            Init;                           /*!< TKEY init parameters */
    TKEY_TimingInitTypeDef      Timing;                         /*!< TKEY Timing parameters */                
} TKEY_HandleTypeDef;
/**
  * @}
  */

/**
  * @brief  TKEY CSA parameters structure definition
  */
typedef struct
{
    uint32_t                    ChargeNumDoneEn;                /*!< The charging frequency reaches the set number of times, 
                                                                    and the function is enabled or disabled. 
                                                                    This parameter can be a value of @ref TKEY_ChargeNumDone_State */   
    uint32_t                    ChargeEachDoneEN;               /*!< Enable or disable each charging completion function. 
                                                                    This parameter can be a value of @ref TKEY_ChargeEachDone_State */       
    uint32_t                    DischargeTime;                  /*!< Cs capacitor discharge time. 
                                                                    This parameter can be a value of @ref TKEY_Cs_DisChargeTime */   
    uint32_t                    ComparerFilterNum;              /*!< Comparator filtering value.
                                                                    This parameter can be a value of @ref TKEY_CompFilter_Num */       
    uint32_t                    ComparerFilterEN;               /*!< Comparator filtering enable or disable. 
                                                                    This parameter can be a value of @ref TKEY_CompFilter_State */   
    uint32_t                    ChargeNum;                      /*!< charging numbers. 
                                                                    This parameter can be a value of @ref TKEY_ChargeNumber */ 
    uint32_t                    ChargeDoneWaitTime;             /*!< Waiting time after reaching the set number of charges. 
                                                                    This parameter can be a value of @ref TKEY_ChargeDoneWaitTime */ 
                                                                    
}TKEY_CSAConfigTypeDef;
/**
  * @}
  */

/**
  * @brief  TKEY CSD parameters structure definition
  */
typedef struct
{    
    uint32_t                    DischargeMode;                  /*!< Discharge mode selection. 
                                                                    This parameter can be a value of @ref TKEY_DisChargeMode */   
    uint32_t                    PrechargeEn;                    /*!< Precharge enable or disable.
                                                                    This parameter can be a value of @ref TKEY_Precharge_State */       
    uint32_t                    DischargeCurrent;               /*!< Selection of discharge current for constant current source. 
                                                                    This parameter can be a value of @ref TKEY_DischargeCurrent */   
    uint32_t                    DischargeRes;                   /*!< Resistance discharge resistance selection. 
                                                                    This parameter can be a value of @ref TKEY_DischargeRes */ 
    uint32_t                    SampleBitClkDiv;                /*!<Clock division for sampling bit streams. 
                                                                    This parameter can be a value of @ref TKEY_SampleBitClkDiv */                                                                   
}TKEY_CSDConfigTypeDef;
/**
  * @}
  */

/**
  * @brief  TKEY Mutual parameters structure definition
  */
typedef struct
{      
    uint32_t                    MutualDelayTime;                /*!< Specify the delay time for mutual inductance transmission signals.
                                                                    This parameter can be a value of @ref TKEY_MutualDelay */       
    uint32_t                    MutualDelayEn;                  /*!< Mutual inductance transmission signal delay enable or disable. 
                                                                    This parameter can be a value of @ref TKEY_MutualDelay_State */   
    uint32_t                    MutualResetEn;                  /*!< Mutual inductance transmission channel reset enable or disable. 
                                                                    This parameter can be a value of @ref TKEY_MutualReset_State */ 
    uint32_t                    MutualChannelEn;                /*!< Specify the enable TKEY mutual inductance transmission channel. 
                                                                    This parameter can be a value of @ref TKEY_Mutual_Channel_State */                                                                   
}TKEY_MutualConfigTypeDef;
/**
  * @}
  */

/**
  * @brief  TKEY Mutual parameters structure definition
  */
typedef struct
{  
    uint32_t                    Baseline[16];                   /*!< Specify channel baseline value in automatic mode.
                                                                    This parameter can be a value of @ref TKEY_Auto_Baseline */       
    uint32_t                    Threshold[16];                  /*!< Specify channel threshold value in automatic mode. 
                                                                    This parameter can be a value of @ref TKEY_Auto_Threshold */   
    uint32_t                    FilterNum;                      /*!< Specify the number of hardware filters in automatic mode. 
                                                                    This parameter can be a value of @ref TKEY_Filter_Num */ 
    uint32_t                    KeyNum;                         /*!< Specify the number of buttons in automatic mode. 
                                                                    This parameter can be a value of @ref TKEY_Auto_KeyNum */                                                                   
    uint32_t                    CountMode;                      /*!< Specify the filtering counting method in automatic mode. 
                                                                    This parameter can be a value of @ref TKEY_Auto_CountMode */                     
}TKEY_AutoConfigTypeDef;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/* HAL_TKEY_Init */
HAL_StatusTypeDef HAL_TKEY_Init(TKEY_HandleTypeDef* htkey);

/* HAL_TKEY_DeInit */
HAL_StatusTypeDef HAL_TKEY_DeInit(TKEY_HandleTypeDef* htkey);

/* HAL_TKEY_EnableDisable */
void HAL_TKEY_EnableDisable(uint32_t NewState);

/* HAL_TKEY_StartScan */
void HAL_TKEY_StartScan(void);

/* HAL_TKEY_StopScan */
void HAL_TKEY_StopScan(void);

/* HAL_TKEY_ReadChannelCount */
HAL_StatusTypeDef HAL_TKEY_ReadChannelCount(uint16_t *pScanCount);

/* HAL_TKEY_ReadLastChannelCount */
uint16_t HAL_TKEY_ReadLastChannelCount(void);

/* HAL_TKEY_GetSacnTimeoutAutoChannelNumber */
uint8_t HAL_TKEY_GetSacnTimeoutAutoChannelNumber(void);

/* HAL_TKEY_AutoConfig */
HAL_StatusTypeDef HAL_TKEY_AutoConfig(TKEY_AutoConfigTypeDef *hauto);

/* HAL_TKEY_CSAConfig */
HAL_StatusTypeDef HAL_TKEY_CSAConfig(TKEY_CSAConfigTypeDef* hcsa);

/* HAL_TKEY_CSDConfig */
HAL_StatusTypeDef HAL_TKEY_CSDConfig(TKEY_CSDConfigTypeDef* hcsd);

/* HAL_TKEY_MutualConfig */
HAL_StatusTypeDef HAL_TKEY_MutualConfig(TKEY_MutualConfigTypeDef* hmutual);

/* HAL_TKEY_MutualEnableDisable */
void HAL_TKEY_MutualEnableDisable(uint32_t NewState);

/* HAL_TKEY_AutoEnableDisable */
void HAL_TKEY_AutoEnableDisable(uint32_t NewState);

/* HAL_TKEY_ResCompensate */
void HAL_TKEY_ResCompensate(uint8_t res);

/* HAL_TKEY_CapCompensate */
void HAL_TKEY_CapCompensate(uint8_t cap);

/* HAL_TKEY_ScanIntervalConfig */
void HAL_TKEY_ScanIntervalConfig(uint16_t time);

/* HAL_TKEY_ReadScanInterval */
uint16_t HAL_TKEY_ReadScanInterval(void);

/* HAL_TKEY_ITConfig */
void HAL_TKEY_ITConfig(uint32_t irq, FunctionalState NewState);  

/* HAL_TKEY_GetFlagStatus */
FlagStatus HAL_TKEY_GetFlagStatus(uint32_t flag);

/* HAL_TKEY_ClearFlag */
void HAL_TKEY_ClearFlag(uint32_t flag);

/* HAL_TKEY_GetITStatus */
ITStatus HAL_TKEY_GetITStatus(uint32_t irq);

/* HAL_TKEY_ClearITPendingBit */
void HAL_TKEY_ClearITPendingBit(uint32_t irq);

/* HAL_TKEY_GetIT */
uint16_t HAL_TKEY_GetIT(void);

#endif





