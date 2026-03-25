
/******************************************************************************
*@file  : hal_nfm.h
*@brief : Header file for NFM module.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __HAL_NFM_H__
#define __HAL_NFM_H__

#include "hal.h"

/** @defgroup  GPIO PORT
  * @{
  */

/*Data Ports*/
#define FMC_D0_GPIO_PORT        GPIOD
#define FMC_D0_GPIO_PIN         GPIO_PIN_14

#define FMC_D1_GPIO_PORT        GPIOD
#define FMC_D1_GPIO_PIN         GPIO_PIN_15

#define FMC_D2_GPIO_PORT        GPIOD
#define FMC_D2_GPIO_PIN         GPIO_PIN_0

#define FMC_D3_GPIO_PORT        GPIOD
#define FMC_D3_GPIO_PIN         GPIO_PIN_1

#define FMC_D4_GPIO_PORT        GPIOE
#define FMC_D4_GPIO_PIN         GPIO_PIN_7

#define FMC_D5_GPIO_PORT        GPIOE
#define FMC_D5_GPIO_PIN         GPIO_PIN_8

#define FMC_D6_GPIO_PORT        GPIOE
#define FMC_D6_GPIO_PIN         GPIO_PIN_9

#define FMC_D7_GPIO_PORT        GPIOE
#define FMC_D7_GPIO_PIN         GPIO_PIN_10

/*Control Ports*/  
#define FMC_CEN_GPIO_PORT       GPIOG
#define FMC_CEN_GPIO_PIN        GPIO_PIN_9

#define FMC_WEN_GPIO_PORT       GPIOD
#define FMC_WEN_GPIO_PIN        GPIO_PIN_5

#define FMC_REN_GPIO_PORT       GPIOD
#define FMC_REN_GPIO_PIN        GPIO_PIN_4

#define FMC_CLE_GPIO_PORT       GPIOD              
#define FMC_CLE_GPIO_PIN        GPIO_PIN_11

#define FMC_ALE_GPIO_PORT       GPIOD              
#define FMC_ALE_GPIO_PIN        GPIO_PIN_12

#define FMC_RBN_GPIO_PORT       GPIOG
#define FMC_RBN_GPIO_PIN        GPIO_PIN_7
/**
  * @}
  */  
  
/** @defgroup  NFM CMD
  * @{
  */

#define NFM_CMD_READ1                0x00
#define NFM_CMD_READ2                0x30
#define NFM_CMD_ID                   0x90
#define NFM_CMD_STATUS               0x70
#define NFM_CMD_RESET                0xFF
#define NFM_CMD_PROGRAM1             0x80
#define NFM_CMD_PROGRAM2             0x10
#define NFM_CMD_ERASE1               0x60
#define NFM_CMD_ERASE2               0xD0
#define NFM_CMD_RANDOMINPUT          0x85
#define NFM_CMD_RANDOMOUTPUT1        0x05
#define NFM_CMD_RANDOMOUTPUT2        0xE0
#define NFM_CMD_FEATURE              0xEF
/**
  * @}
  */  

/** @defgroup  NFM Private Macros
  * @{
  */
  
#define IS_NFM_ALL_INSTANCE(__INSTANCE__)              ((__INSTANCE__) == NFM)
                                           
/**
  * @}
  */                                           

/** @defgroup NFM EDO_EN
  * @{
  */ 
 #define NFM_EDO_EN                         (0x00000080U)    /*!< EDO Enable */
 #define NFM_EDO_DIS                        (0x00000000U)    /*!< EDO Disable */
 #define IS_NFM_EDO_EN(EN)                  (((EN) == NFM_EDO_EN    || \
                                             ((EN) <= NFM_EDO_DIS)))
/**
  * @}
  */

/** @defgroup NFM RBN_INT EN
  * @{
  */ 
 #define NFM_RBN_INT_EN                     (0x00000040U)    /*!< RBN INT Enable */
 #define NFM_RBN_INT_DIS                    (0x00000000U)    /*!< RBN INT Disable */
 #define IS_NFM_RBNINT_EN(EN)               (((EN) == NFM_RBN_INT_EN    || \
                                             ((EN) <= NFM_RBN_INT_DIS)))
/**
  * @}
  */
  
/** @defgroup NFM ENDIAN
  * @{
  */ 
 #define NFM_ENDIAN_BIG                     (0x00000020U)    /*!< Big Endian */
 #define NFM_ENDIAN_LITTLE                  (0x00000000U)    /*!< Little Endian */
 #define IS_NFM_ENDIAN_EN(ENDIAN)           (((ENDIAN) == NFM_ENDIAN_BIG    || \
                                             ((ENDIAN) <= NFM_ENDIAN_LITTLE)))
/**
  * @}
  */
  
/** @defgroup NFM FWP
  * @{
  */ 
 #define NFM_FWP_EN                         (0x00000000U)    /*!< FWP Enable */
 #define NFM_FWP_DIS                        (0x00000010U)    /*!< FWP Disable */
 #define IS_NFM_FWP_EN(FWP)                 (((FWP) == NFM_FWP_EN    || \
                                             ((FWP) <= NFM_FWP_DIS)))
/**
  * @}
  */
 
/** @defgroup NFM FCE
  * @{
  */ 
 #define NFM_FCE_EN                         (0x0000000eU)    /*!< FCE Enable */
 #define NFM_FCE_DIS                        (0x0000000fU)    /*!< FCE Disable */
 #define IS_NFM_FCE_EN(FCE)                 (((FCE) == NFM_FCE_EN    || \
                                             ((FCE) <= NFM_FCE_DIS)))
/**
  * @}
  */
  
/** @defgroup tADL_Clock
  * @{
  */
#define NFM_TADL_NONE                           (0U)
#define NFM_TADL_1CLOCK                         (NFM_NFMWST_TADL_0)
#define NFM_TADL_2CLOCK                         (NFM_NFMWST_TADL_1)
#define NFM_TADL_3CLOCK                         (NFM_NFMWST_TADL_0 | NFM_NFMWST_TADL_1)
#define NFM_TADL_4CLOCK                         (NFM_NFMWST_TADL_2)
#define NFM_TADL_5CLOCK                         (NFM_NFMWST_TADL_0 | NFM_NFMWST_TADL_2)
#define NFM_TADL_6CLOCK                         (NFM_NFMWST_TADL_1 | NFM_NFMWST_TADL_2)
#define NFM_TADL_7CLOCK                         (NFM_NFMWST_TADL_0 | NFM_NFMWST_TADL_1 | NFM_NFMWST_TADL_2)
#define NFM_TADL_8CLOCK                         (NFM_NFMWST_TADL_3)
#define NFM_TADL_9CLOCK                         (NFM_NFMWST_TADL_0 | NFM_NFMWST_TADL_3)
#define NFM_TADL_10CLOCK                        (NFM_NFMWST_TADL_1 | NFM_NFMWST_TADL_3)
#define NFM_TADL_11CLOCK                        (NFM_NFMWST_TADL_0 | NFM_NFMWST_TADL_1 | NFM_NFMWST_TADL_3)
#define NFM_TADL_12CLOCK                        (NFM_NFMWST_TADL_2 | NFM_NFMWST_TADL_3)
#define NFM_TADL_13CLOCK                        (NFM_NFMWST_TADL_0 | NFM_NFMWST_TADL_2 | NFM_NFMWST_TADL_3)
#define NFM_TADL_14CLOCK                        (NFM_NFMWST_TADL_1 | NFM_NFMWST_TADL_2 | NFM_NFMWST_TADL_3)
#define NFM_TADL_15CLOCK                        (NFM_NFMWST_TADL_0 | NFM_NFMWST_TADL_1 | NFM_NFMWST_TADL_2 | NFM_NFMWST_TADL_3)

#define IS_NFM_TADL_CLOCK(CLOCK)                (((CLOCK) == NFM_TADL_NONE    || \
                                                ((CLOCK) == NFM_TADL_1CLOCK)  || \
                                                ((CLOCK) == NFM_TADL_2CLOCK)  || \
                                                ((CLOCK) == NFM_TADL_3CLOCK)  || \
                                                ((CLOCK) == NFM_TADL_4CLOCK)  || \
                                                ((CLOCK) == NFM_TADL_5CLOCK)  || \
                                                ((CLOCK) == NFM_TADL_6CLOCK)  || \
                                                ((CLOCK) == NFM_TADL_7CLOCK)  || \
                                                ((CLOCK) == NFM_TADL_8CLOCK)  || \
                                                ((CLOCK) == NFM_TADL_9CLOCK)  || \
                                                ((CLOCK) == NFM_TADL_10CLOCK) || \
                                                ((CLOCK) == NFM_TADL_11CLOCK) || \
                                                ((CLOCK) == NFM_TADL_12CLOCK) || \
                                                ((CLOCK) == NFM_TADL_13CLOCK) || \
                                                ((CLOCK) == NFM_TADL_14CLOCK) || \
                                                ((CLOCK) <= NFM_TADL_15CLOCK)))
/**
  * @}
  */
  
/** @defgroup tRHW_Clock
  * @{
  */
#define NFM_TRHW_NONE                           (0U)
#define NFM_TRHW_1CLOCK                         (NFM_NFMWST_TRHW_0)
#define NFM_TRHW_2CLOCK                         (NFM_NFMWST_TRHW_1)
#define NFM_TRHW_3CLOCK                         (NFM_NFMWST_TRHW_0 | NFM_NFMWST_TRHW_1)
#define NFM_TRHW_4CLOCK                         (NFM_NFMWST_TRHW_2)
#define NFM_TRHW_5CLOCK                         (NFM_NFMWST_TRHW_0 | NFM_NFMWST_TRHW_2)
#define NFM_TRHW_6CLOCK                         (NFM_NFMWST_TRHW_1 | NFM_NFMWST_TRHW_2)
#define NFM_TRHW_7CLOCK                         (NFM_NFMWST_TRHW_0 | NFM_NFMWST_TRHW_1 | NFM_NFMWST_TRHW_2)
#define NFM_TRHW_8CLOCK                         (NFM_NFMWST_TRHW_3)
#define NFM_TRHW_9CLOCK                         (NFM_NFMWST_TRHW_0 | NFM_NFMWST_TRHW_3)
#define NFM_TRHW_10CLOCK                        (NFM_NFMWST_TRHW_1 | NFM_NFMWST_TRHW_3)
#define NFM_TRHW_11CLOCK                        (NFM_NFMWST_TRHW_0 | NFM_NFMWST_TRHW_1 | NFM_NFMWST_TRHW_3)
#define NFM_TRHW_12CLOCK                        (NFM_NFMWST_TRHW_2 | NFM_NFMWST_TRHW_3)
#define NFM_TRHW_13CLOCK                        (NFM_NFMWST_TRHW_0 | NFM_NFMWST_TRHW_2 | NFM_NFMWST_TRHW_3)
#define NFM_TRHW_14CLOCK                        (NFM_NFMWST_TRHW_1 | NFM_NFMWST_TRHW_2 | NFM_NFMWST_TRHW_3)
#define NFM_TRHW_15CLOCK                        (NFM_NFMWST_TRHW_0 | NFM_NFMWST_TRHW_1 | NFM_NFMWST_TRHW_2 | NFM_NFMWST_TRHW_3)

#define IS_NFM_TRHW_CLOCK(CLOCK)                (((CLOCK) == NFM_TRHW_NONE    || \
                                                ((CLOCK) == NFM_TRHW_1CLOCK)  || \
                                                ((CLOCK) == NFM_TRHW_2CLOCK)  || \
                                                ((CLOCK) == NFM_TRHW_3CLOCK)  || \
                                                ((CLOCK) == NFM_TRHW_4CLOCK)  || \
                                                ((CLOCK) == NFM_TRHW_5CLOCK)  || \
                                                ((CLOCK) == NFM_TRHW_6CLOCK)  || \
                                                ((CLOCK) == NFM_TRHW_7CLOCK)  || \
                                                ((CLOCK) == NFM_TRHW_8CLOCK)  || \
                                                ((CLOCK) == NFM_TRHW_9CLOCK)  || \
                                                ((CLOCK) == NFM_TRHW_10CLOCK) || \
                                                ((CLOCK) == NFM_TRHW_11CLOCK) || \
                                                ((CLOCK) == NFM_TRHW_12CLOCK) || \
                                                ((CLOCK) == NFM_TRHW_13CLOCK) || \
                                                ((CLOCK) == NFM_TRHW_14CLOCK) || \
                                                ((CLOCK) <= NFM_TRHW_15CLOCK)))
/**
  * @}
  */

/** @defgroup tWHR_Clock
  * @{
  */
#define NFM_TWHR_NONE                           (0U)
#define NFM_TWHR_1CLOCK                         (NFM_NFMWST_TWHR_0)
#define NFM_TWHR_2CLOCK                         (NFM_NFMWST_TWHR_1)
#define NFM_TWHR_3CLOCK                         (NFM_NFMWST_TWHR_0 | NFM_NFMWST_TWHR_1)
#define NFM_TWHR_4CLOCK                         (NFM_NFMWST_TWHR_2)
#define NFM_TWHR_5CLOCK                         (NFM_NFMWST_TWHR_0 | NFM_NFMWST_TWHR_2)
#define NFM_TWHR_6CLOCK                         (NFM_NFMWST_TWHR_1 | NFM_NFMWST_TWHR_2)
#define NFM_TWHR_7CLOCK                         (NFM_NFMWST_TWHR_0 | NFM_NFMWST_TWHR_1 | NFM_NFMWST_TWHR_2)
#define NFM_TWHR_8CLOCK                         (NFM_NFMWST_TWHR_3)
#define NFM_TWHR_9CLOCK                         (NFM_NFMWST_TWHR_0 | NFM_NFMWST_TWHR_3)
#define NFM_TWHR_10CLOCK                        (NFM_NFMWST_TWHR_1 | NFM_NFMWST_TWHR_3)
#define NFM_TWHR_11CLOCK                        (NFM_NFMWST_TWHR_0 | NFM_NFMWST_TWHR_1 | NFM_NFMWST_TWHR_3)
#define NFM_TWHR_12CLOCK                        (NFM_NFMWST_TWHR_2 | NFM_NFMWST_TWHR_3)
#define NFM_TWHR_13CLOCK                        (NFM_NFMWST_TWHR_0 | NFM_NFMWST_TWHR_2 | NFM_NFMWST_TWHR_3)
#define NFM_TWHR_14CLOCK                        (NFM_NFMWST_TWHR_1 | NFM_NFMWST_TWHR_2 | NFM_NFMWST_TWHR_3)
#define NFM_TWHR_15CLOCK                        (NFM_NFMWST_TWHR_0 | NFM_NFMWST_TWHR_1 | NFM_NFMWST_TWHR_2 | NFM_NFMWST_TWHR_3)

#define IS_NFM_TWHR_CLOCK(CLOCK)                (((CLOCK) == NFM_TWHR_NONE    || \
                                                ((CLOCK) == NFM_TWHR_1CLOCK)  || \
                                                ((CLOCK) == NFM_TWHR_2CLOCK)  || \
                                                ((CLOCK) == NFM_TWHR_3CLOCK)  || \
                                                ((CLOCK) == NFM_TWHR_4CLOCK)  || \
                                                ((CLOCK) == NFM_TWHR_5CLOCK)  || \
                                                ((CLOCK) == NFM_TWHR_6CLOCK)  || \
                                                ((CLOCK) == NFM_TWHR_7CLOCK)  || \
                                                ((CLOCK) == NFM_TWHR_8CLOCK)  || \
                                                ((CLOCK) == NFM_TWHR_9CLOCK)  || \
                                                ((CLOCK) == NFM_TWHR_10CLOCK) || \
                                                ((CLOCK) == NFM_TWHR_11CLOCK) || \
                                                ((CLOCK) == NFM_TWHR_12CLOCK) || \
                                                ((CLOCK) == NFM_TWHR_13CLOCK) || \
                                                ((CLOCK) == NFM_TWHR_14CLOCK) || \
                                                ((CLOCK) <= NFM_TWHR_15CLOCK)))
/**
  * @}
  */


/** @defgroup tREH_Clock
  * @{
  */
#define NFM_TREH_NONE                           (0U)
#define NFM_TREH_1CLOCK                         (NFM_NFMWST_TREH_0)
#define NFM_TREH_2CLOCK                         (NFM_NFMWST_TREH_1)
#define NFM_TREH_3CLOCK                         (NFM_NFMWST_TREH_0 | NFM_NFMWST_TREH_1)
#define NFM_TREH_4CLOCK                         (NFM_NFMWST_TREH_2)
#define NFM_TREH_5CLOCK                         (NFM_NFMWST_TREH_0 | NFM_NFMWST_TREH_2)
#define NFM_TREH_6CLOCK                         (NFM_NFMWST_TREH_1 | NFM_NFMWST_TREH_2)
#define NFM_TREH_7CLOCK                         (NFM_NFMWST_TREH_0 | NFM_NFMWST_TREH_1 | NFM_NFMWST_TREH_2)
#define NFM_TREH_8CLOCK                         (NFM_NFMWST_TREH_3)
#define NFM_TREH_9CLOCK                         (NFM_NFMWST_TREH_0 | NFM_NFMWST_TREH_3)
#define NFM_TREH_10CLOCK                        (NFM_NFMWST_TREH_1 | NFM_NFMWST_TREH_3)
#define NFM_TREH_11CLOCK                        (NFM_NFMWST_TREH_0 | NFM_NFMWST_TREH_1 | NFM_NFMWST_TREH_3)
#define NFM_TREH_12CLOCK                        (NFM_NFMWST_TREH_2 | NFM_NFMWST_TREH_3)
#define NFM_TREH_13CLOCK                        (NFM_NFMWST_TREH_0 | NFM_NFMWST_TREH_2 | NFM_NFMWST_TREH_3)
#define NFM_TREH_14CLOCK                        (NFM_NFMWST_TREH_1 | NFM_NFMWST_TREH_2 | NFM_NFMWST_TREH_3)
#define NFM_TREH_15CLOCK                        (NFM_NFMWST_TREH_0 | NFM_NFMWST_TREH_1 | NFM_NFMWST_TREH_2 | NFM_NFMWST_TREH_3)

#define IS_NFM_TREH_CLOCK(CLOCK)                (((CLOCK) == NFM_TREH_NONE    || \
                                                ((CLOCK) == NFM_TREH_1CLOCK)  || \
                                                ((CLOCK) == NFM_TREH_2CLOCK)  || \
                                                ((CLOCK) == NFM_TREH_3CLOCK)  || \
                                                ((CLOCK) == NFM_TREH_4CLOCK)  || \
                                                ((CLOCK) == NFM_TREH_5CLOCK)  || \
                                                ((CLOCK) == NFM_TREH_6CLOCK)  || \
                                                ((CLOCK) == NFM_TREH_7CLOCK)  || \
                                                ((CLOCK) == NFM_TREH_8CLOCK)  || \
                                                ((CLOCK) == NFM_TREH_9CLOCK)  || \
                                                ((CLOCK) == NFM_TREH_10CLOCK) || \
                                                ((CLOCK) == NFM_TREH_11CLOCK) || \
                                                ((CLOCK) == NFM_TREH_12CLOCK) || \
                                                ((CLOCK) == NFM_TREH_13CLOCK) || \
                                                ((CLOCK) == NFM_TREH_14CLOCK) || \
                                                ((CLOCK) <= NFM_TREH_15CLOCK)))
/**
  * @}
  */
  

/** @defgroup tRP_Clock
  * @{
  */
#define NFM_TRP_NONE                            (0U)
#define NFM_TRP_1CLOCK                          (NFM_NFMWST_TRP_0)
#define NFM_TRP_2CLOCK                          (NFM_NFMWST_TRP_1)
#define NFM_TRP_3CLOCK                          (NFM_NFMWST_TRP_0 | NFM_NFMWST_TRP_1)
#define NFM_TRP_4CLOCK                          (NFM_NFMWST_TRP_2)
#define NFM_TRP_5CLOCK                          (NFM_NFMWST_TRP_0 | NFM_NFMWST_TRP_2)
#define NFM_TRP_6CLOCK                          (NFM_NFMWST_TRP_1 | NFM_NFMWST_TRP_2)
#define NFM_TRP_7CLOCK                          (NFM_NFMWST_TRP_0 | NFM_NFMWST_TRP_1 | NFM_NFMWST_TRP_2)
#define NFM_TRP_8CLOCK                          (NFM_NFMWST_TRP_3)
#define NFM_TRP_9CLOCK                          (NFM_NFMWST_TRP_0 | NFM_NFMWST_TRP_3)
#define NFM_TRP_10CLOCK                         (NFM_NFMWST_TRP_1 | NFM_NFMWST_TRP_3)
#define NFM_TRP_11CLOCK                         (NFM_NFMWST_TRP_0 | NFM_NFMWST_TRP_1 | NFM_NFMWST_TRP_3)
#define NFM_TRP_12CLOCK                         (NFM_NFMWST_TRP_2 | NFM_NFMWST_TRP_3)
#define NFM_TRP_13CLOCK                         (NFM_NFMWST_TRP_0 | NFM_NFMWST_TRP_2 | NFM_NFMWST_TRP_3)
#define NFM_TRP_14CLOCK                         (NFM_NFMWST_TRP_1 | NFM_NFMWST_TRP_2 | NFM_NFMWST_TRP_3)
#define NFM_TRP_15CLOCK                         (NFM_NFMWST_TRP_0 | NFM_NFMWST_TRP_1 | NFM_NFMWST_TRP_2 | NFM_NFMWST_TRP_3)

#define IS_NFM_TRP_CLOCK(CLOCK)                 (((CLOCK) == NFM_TRP_NONE    || \
                                                ((CLOCK) == NFM_TRP_1CLOCK)  || \
                                                ((CLOCK) == NFM_TRP_2CLOCK)  || \
                                                ((CLOCK) == NFM_TRP_3CLOCK)  || \
                                                ((CLOCK) == NFM_TRP_4CLOCK)  || \
                                                ((CLOCK) == NFM_TRP_5CLOCK)  || \
                                                ((CLOCK) == NFM_TRP_6CLOCK)  || \
                                                ((CLOCK) == NFM_TRP_7CLOCK)  || \
                                                ((CLOCK) == NFM_TRP_8CLOCK)  || \
                                                ((CLOCK) == NFM_TRP_9CLOCK)  || \
                                                ((CLOCK) == NFM_TRP_10CLOCK) || \
                                                ((CLOCK) == NFM_TRP_11CLOCK) || \
                                                ((CLOCK) == NFM_TRP_12CLOCK) || \
                                                ((CLOCK) == NFM_TRP_13CLOCK) || \
                                                ((CLOCK) == NFM_TRP_14CLOCK) || \
                                                ((CLOCK) <= NFM_TRP_15CLOCK)))
/**
  * @}
  */
 
/** @defgroup tWH_Clock
  * @{
  */
#define NFM_TWH_NONE                            (0U)
#define NFM_TWH_1CLOCK                          (NFM_NFMWST_TWH_0)
#define NFM_TWH_2CLOCK                          (NFM_NFMWST_TWH_1)
#define NFM_TWH_3CLOCK                          (NFM_NFMWST_TWH_0 | NFM_NFMWST_TWH_1)
#define NFM_TWH_4CLOCK                          (NFM_NFMWST_TWH_2)
#define NFM_TWH_5CLOCK                          (NFM_NFMWST_TWH_0 | NFM_NFMWST_TWH_2)
#define NFM_TWH_6CLOCK                          (NFM_NFMWST_TWH_1 | NFM_NFMWST_TWH_2)
#define NFM_TWH_7CLOCK                          (NFM_NFMWST_TWH_0 | NFM_NFMWST_TWH_1 | NFM_NFMWST_TWH_2)
#define NFM_TWH_8CLOCK                          (NFM_NFMWST_TWH_3)
#define NFM_TWH_9CLOCK                          (NFM_NFMWST_TWH_0 | NFM_NFMWST_TWH_3)
#define NFM_TWH_10CLOCK                         (NFM_NFMWST_TWH_1 | NFM_NFMWST_TWH_3)
#define NFM_TWH_11CLOCK                         (NFM_NFMWST_TWH_0 | NFM_NFMWST_TWH_1 | NFM_NFMWST_TWH_3)
#define NFM_TWH_12CLOCK                         (NFM_NFMWST_TWH_2 | NFM_NFMWST_TWH_3)
#define NFM_TWH_13CLOCK                         (NFM_NFMWST_TWH_0 | NFM_NFMWST_TWH_2 | NFM_NFMWST_TWH_3)
#define NFM_TWH_14CLOCK                         (NFM_NFMWST_TWH_1 | NFM_NFMWST_TWH_2 | NFM_NFMWST_TWH_3)
#define NFM_TWH_15CLOCK                         (NFM_NFMWST_TWH_0 | NFM_NFMWST_TWH_1 | NFM_NFMWST_TWH_2 | NFM_NFMWST_TWH_3)

#define IS_NFM_TWH_CLOCK(CLOCK)                 (((CLOCK) == NFM_TWH_NONE    || \
                                                ((CLOCK) == NFM_TWH_1CLOCK)  || \
                                                ((CLOCK) == NFM_TWH_2CLOCK)  || \
                                                ((CLOCK) == NFM_TWH_3CLOCK)  || \
                                                ((CLOCK) == NFM_TWH_4CLOCK)  || \
                                                ((CLOCK) == NFM_TWH_5CLOCK)  || \
                                                ((CLOCK) == NFM_TWH_6CLOCK)  || \
                                                ((CLOCK) == NFM_TWH_7CLOCK)  || \
                                                ((CLOCK) == NFM_TWH_8CLOCK)  || \
                                                ((CLOCK) == NFM_TWH_9CLOCK)  || \
                                                ((CLOCK) == NFM_TWH_10CLOCK) || \
                                                ((CLOCK) == NFM_TWH_11CLOCK) || \
                                                ((CLOCK) == NFM_TWH_12CLOCK) || \
                                                ((CLOCK) == NFM_TWH_13CLOCK) || \
                                                ((CLOCK) == NFM_TWH_14CLOCK) || \
                                                ((CLOCK) <= NFM_TWH_15CLOCK)))
/**
  * @}
  */ 
  
/** @defgroup tWP_Clock
  * @{
  */
#define NFM_TWP_NONE                            (0U)
#define NFM_TWP_1CLOCK                          (NFM_NFMWST_TWP_0)
#define NFM_TWP_2CLOCK                          (NFM_NFMWST_TWP_1)
#define NFM_TWP_3CLOCK                          (NFM_NFMWST_TWP_0 | NFM_NFMWST_TWP_1)
#define NFM_TWP_4CLOCK                          (NFM_NFMWST_TWP_2)
#define NFM_TWP_5CLOCK                          (NFM_NFMWST_TWP_0 | NFM_NFMWST_TWP_2)
#define NFM_TWP_6CLOCK                          (NFM_NFMWST_TWP_1 | NFM_NFMWST_TWP_2)
#define NFM_TWP_7CLOCK                          (NFM_NFMWST_TWP_0 | NFM_NFMWST_TWP_1 | NFM_NFMWST_TWP_2)
#define NFM_TWP_8CLOCK                          (NFM_NFMWST_TWP_3)
#define NFM_TWP_9CLOCK                          (NFM_NFMWST_TWP_0 | NFM_NFMWST_TWP_3)
#define NFM_TWP_10CLOCK                         (NFM_NFMWST_TWP_1 | NFM_NFMWST_TWP_3)
#define NFM_TWP_11CLOCK                         (NFM_NFMWST_TWP_0 | NFM_NFMWST_TWP_1 | NFM_NFMWST_TWP_3)
#define NFM_TWP_12CLOCK                         (NFM_NFMWST_TWP_2 | NFM_NFMWST_TWP_3)
#define NFM_TWP_13CLOCK                         (NFM_NFMWST_TWP_0 | NFM_NFMWST_TWP_2 | NFM_NFMWST_TWP_3)
#define NFM_TWP_14CLOCK                         (NFM_NFMWST_TWP_1 | NFM_NFMWST_TWP_2 | NFM_NFMWST_TWP_3)
#define NFM_TWP_15CLOCK                         (NFM_NFMWST_TWP_0 | NFM_NFMWST_TWP_1 | NFM_NFMWST_TWP_2 | NFM_NFMWST_TWP_3)

#define IS_NFM_TWP_CLOCK(CLOCK)                 (((CLOCK) == NFM_TWP_NONE    || \
                                                ((CLOCK) == NFM_TWP_1CLOCK)  || \
                                                ((CLOCK) == NFM_TWP_2CLOCK)  || \
                                                ((CLOCK) == NFM_TWP_3CLOCK)  || \
                                                ((CLOCK) == NFM_TWP_4CLOCK)  || \
                                                ((CLOCK) == NFM_TWP_5CLOCK)  || \
                                                ((CLOCK) == NFM_TWP_6CLOCK)  || \
                                                ((CLOCK) == NFM_TWP_7CLOCK)  || \
                                                ((CLOCK) == NFM_TWP_8CLOCK)  || \
                                                ((CLOCK) == NFM_TWP_9CLOCK)  || \
                                                ((CLOCK) == NFM_TWP_10CLOCK) || \
                                                ((CLOCK) == NFM_TWP_11CLOCK) || \
                                                ((CLOCK) == NFM_TWP_12CLOCK) || \
                                                ((CLOCK) == NFM_TWP_13CLOCK) || \
                                                ((CLOCK) == NFM_TWP_14CLOCK) || \
                                                ((CLOCK) <= NFM_TWP_15CLOCK)))
/**
  * @}
  */ 
  
/** @defgroup  NFM CMD
  * @{
  */

#define NFM_CMD_READ1                0x00
#define NFM_CMD_READ2                0x30
#define NFM_CMD_ID                   0x90
#define NFM_CMD_STATUS               0x70
#define NFM_CMD_RESET                0xFF
#define NFM_CMD_PROGRAM1             0x80
#define NFM_CMD_PROGRAM2             0x10
#define NFM_CMD_ERASE1               0x60
#define NFM_CMD_ERASE2               0xD0
#define NFM_CMD_RANDOMINPUT          0x85
#define NFM_CMD_RANDOMOUTPUT1        0x05
#define NFM_CMD_RANDOMOUTPUT2        0xE0
#define NFM_CMD_FEATURE              0xEF

/**
  * @}
  */ 

  
/** @defgroup BCH DATA LEN
  * @{
  */ 
  
#define BCH_SECTOR_SIZE		         0x200
#define BCH_INF_SIZE		         0x3
#define BCH_ECC_SIZE		         0xD 

/**
  * @}
  */  
  
/** @defgroup BCH ECC MODE
  * @{
  */ 
  
#define BCH_ECC_MODE_EN		         0x1
#define BCH_ECC_MODE_DIS	         0x0

/**
  * @}
  */ 


/*
 * @brief UART Init Structure definition
 */
typedef struct
{
    uint32_t EDO_EN;                    /*!< This member controls the EDO mode. */
    
    uint32_t RBN_INTEN;                 /*!< This member controls the RBN INT. */

    uint32_t ENDIAN;                    /*!< This member controls Big/Little endian. */
 
    uint32_t FWP;                       /*!< This member controls the FWP mode. */ 
    
    uint32_t FCE;                       /*!< This member controls the FCE mode. */
    
    uint32_t TADL;                      /*!< Specifies the tADL value*/
    
    uint32_t TRHW;                      /*!< Specifies the tRHW value*/
                                             
    uint32_t TWHR;                      /*!< Specifies the tWHR value*/
    
    uint32_t TREH;                      /*!< Specifies the tREH value*/
    
    uint32_t TRP;                       /*!< Specifies the tRP value*/
    
    uint32_t TWH;                       /*!< Specifies the tTWH value*/
    
    uint32_t TWP;                       /*!< Specifies the tWP value*/

}NFM_InitTypeDef;

/*
 * @brief  UART handle Structure definition
 */
typedef struct
{
    FMC_NAND_TypeDef           *Instance;                /*!< NFM registers base address  */

    NFM_InitTypeDef        Init;                    /*!< NFM parameters  */
	
    void* NFM_Data_Buff;                            /*!< NFM databuff base address */
	
    uint32_t NFM_Data_Len;                          /*!< amount of CRC data to be calculated */
    
}NFM_HandleTypeDef;  
  
/******************************************************************************
*@brief : Initialize the NFM MSP: CLK, GPIO, NVIC
*         
*@param : hnfm: nfm handle with NFM parameters.
*@return: None
******************************************************************************/
void HAL_NFM_MspInit(NFM_HandleTypeDef *hnfm);

/******************************************************************************
*@brief : Initialize the NFM according to the specified parameters in hnfm.
*         
*@param : hnfm: nfm handle with NFM parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_NFM_Init(NFM_HandleTypeDef *hnfm);

/******************************************************************************
*@brief : Reset Nand Flash
*         
*@param : hnfm: nfm handle with NFM parameters.
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_NFM_FlashReset(NFM_HandleTypeDef *hnfm);

/******************************************************************************
*@brief : Read ID from Nand Flash
*         
*@param : hnfm: nfm handle with NFM parameters.
*@param : rdata: start address to store ID
*@param : lenth: ID length
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_NFM_FlashGetID(NFM_HandleTypeDef *hnfm, uint8_t rdata[], uint8_t lenth);

/******************************************************************************
*@brief : Erase a block
*         
*@param : hnfm: nfm handle with NFM parameters.
*@param : BlockAddr: start address of the block to erase
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_NFM_FlashErase(NFM_HandleTypeDef *hnfm, uint32_t PageAddr);

/******************************************************************************
*@brief : Program one sector(512 bytes) 
*
*@param : hnfm: nfm handle with NFM parameters.
*@param : RowAddr: row start address
*@param : ColumnAddr: column start address
*@param : wdata: start address of data to program
*@param : ecc_en:select the mode of program 
          BCH_ECC_MODE_EN : program with ecc mode
          BCH_ECC_MODE_DIS: progran with no ecc mode
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_NFM_Flash_Program(NFM_HandleTypeDef *hnfm, uint32_t RowAddr, uint16_t ColumnAddr, uint8_t wdata[], uint8_t ecc_en);

/******************************************************************************
*@brief : Read one sector(512 bytes) 
*         
*@param : hnfm: nfm handle with NFM parameters.
*@param : RowAddr: row start address
*@param : ColumnAddr: column start address
*@param : rdata: start address of read data
*@param : ecc_en:select the mode of read 
          BCH_ECC_MODE_EN : read with ecc mode
          BCH_ECC_MODE_DIS: read with no ecc mode
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_NFM_FlashRead(NFM_HandleTypeDef *hnfm, uint32_t RowAddr, uint16_t ColumnAddr, uint8_t rdata[], uint8_t ecc_en);


#endif




