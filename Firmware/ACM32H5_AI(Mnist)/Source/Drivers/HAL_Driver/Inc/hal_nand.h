
/******************************************************************************
*@file  : hal_nand.h
*@brief : Header file for Nand module.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __HAL_NAND_H__
#define __HAL_NAND_H__

#include "hal.h"

/** @defgroup  GPIO PORT
  * @{
  */

/*Data Ports*/
#define FMC_NAND_D0_GPIO_PORT        GPIOD
#define FMC_NAND_D0_GPIO_PIN         GPIO_PIN_14

#define FMC_NAND_D1_GPIO_PORT        GPIOD
#define FMC_NAND_D1_GPIO_PIN         GPIO_PIN_15

#define FMC_NAND_D2_GPIO_PORT        GPIOD
#define FMC_NAND_D2_GPIO_PIN         GPIO_PIN_0

#define FMC_NAND_D3_GPIO_PORT        GPIOD
#define FMC_NAND_D3_GPIO_PIN         GPIO_PIN_1

#define FMC_NAND_D4_GPIO_PORT        GPIOE
#define FMC_NAND_D4_GPIO_PIN         GPIO_PIN_7

#define FMC_NAND_D5_GPIO_PORT        GPIOE
#define FMC_NAND_D5_GPIO_PIN         GPIO_PIN_8

#define FMC_NAND_D6_GPIO_PORT        GPIOE
#define FMC_NAND_D6_GPIO_PIN         GPIO_PIN_9

#define FMC_NAND_D7_GPIO_PORT        GPIOE
#define FMC_NAND_D7_GPIO_PIN         GPIO_PIN_10

/*Control Ports*/  
#define FMC_NAND_CEN_GPIO_PORT       GPIOG
#define FMC_NAND_CEN_GPIO_PIN        GPIO_PIN_9

#define FMC_NAND_WEN_GPIO_PORT       GPIOD
#define FMC_NAND_WEN_GPIO_PIN        GPIO_PIN_5

#define FMC_NAND_REN_GPIO_PORT       GPIOD
#define FMC_NAND_REN_GPIO_PIN        GPIO_PIN_4

#define FMC_NAND_CLE_GPIO_PORT       GPIOD              
#define FMC_NAND_CLE_GPIO_PIN        GPIO_PIN_11

#define FMC_NAND_ALE_GPIO_PORT       GPIOD              
#define FMC_NAND_ALE_GPIO_PIN        GPIO_PIN_12

#define FMC_NAND_RBN_GPIO_PORT       GPIOG
#define FMC_NAND_RBN_GPIO_PIN        GPIO_PIN_7
/**
  * @}
  */  
  
/** @defgroup  FMC_NAND CMD
  * @{
  */

#define FMC_NAND_CMD_READ1                0x00
#define FMC_NAND_CMD_READ2                0x30
#define FMC_NAND_CMD_ID                   0x90
#define FMC_NAND_CMD_STATUS               0x70
#define FMC_NAND_CMD_RESET                0xFF
#define FMC_NAND_CMD_PROGRAM1             0x80
#define FMC_NAND_CMD_PROGRAM2             0x10
#define FMC_NAND_CMD_ERASE1               0x60
#define FMC_NAND_CMD_ERASE2               0xD0
#define FMC_NAND_CMD_RANDOMINPUT          0x85
#define FMC_NAND_CMD_RANDOMOUTPUT1        0x05
#define FMC_NAND_CMD_RANDOMOUTPUT2        0xE0
#define FMC_NAND_CMD_FEATURE              0xEF
/**
  * @}
  */  

/** @defgroup  FMC_NAND Private Macros
  * @{
  */
  
#define IS_FMC_NAND_ALL_INSTANCE(__INSTANCE__)              ((__INSTANCE__) == FMC_NAND)
                                           
/**
  * @}
  */                                           

/** @defgroup FMC_NAND EDO_EN
  * @{
  */ 
 #define FMC_NAND_EDO_EN                         (0x00000080U)    /*!< EDO Enable */
 #define FMC_NAND_EDO_DIS                        (0x00000000U)    /*!< EDO Disable */
 #define IS_FMC_NAND_EDO_EN(EN)                  (((EN) == FMC_NAND_EDO_EN    || \
                                                  ((EN) <= FMC_NAND_EDO_DIS)))
/**
  * @}
  */

/** @defgroup FMC_NAND RBN_INT EN
  * @{
  */ 
 #define FMC_NAND_RBN_INT_EN                     (0x00000040U)    /*!< RBN INT Enable */
 #define FMC_NAND_RBN_INT_DIS                    (0x00000000U)    /*!< RBN INT Disable */
 #define IS_FMC_NAND_RBNINT_EN(EN)               (((EN) == FMC_NAND_RBN_INT_EN    || \
                                                  ((EN) <= FMC_NAND_RBN_INT_DIS)))
/**
  * @}
  */
  
/** @defgroup FMC_NAND ENDIAN
  * @{
  */ 
 #define FMC_NAND_ENDIAN_BIG                     (0x00000020U)    /*!< Big Endian */
 #define FMC_NAND_ENDIAN_LITTLE                  (0x00000000U)    /*!< Little Endian */
 #define IS_FMC_NAND_ENDIAN_EN(ENDIAN)           (((ENDIAN) == FMC_NAND_ENDIAN_BIG    || \
                                                  ((ENDIAN) <= FMC_NAND_ENDIAN_LITTLE)))
/**
  * @}
  */
  
/** @defgroup FMC_NAND FWP
  * @{
  */ 
 #define FMC_NAND_FWP_EN                         (0x00000000U)    /*!< FWP Enable */
 #define FMC_NAND_FWP_DIS                        (0x00000010U)    /*!< FWP Disable */
 #define IS_FMC_NAND_FWP_EN(FWP)                 (((FWP) == FMC_NAND_FWP_EN    || \
                                                  ((FWP) <= FMC_NAND_FWP_DIS)))
/**
  * @}
  */
 
/** @defgroup FMC_NAND FCE
  * @{
  */ 
 #define FMC_NAND_FCE_EN                         (0x0000000eU)    /*!< FCE Enable */
 #define FMC_NAND_FCE_DIS                        (0x0000000fU)    /*!< FCE Disable */
 #define IS_FMC_NAND_FCE_EN(FCE)                 (((FCE) == FMC_NAND_FCE_EN    || \
                                                  ((FCE) <= FMC_NAND_FCE_DIS)))
/**
  * @}
  */
  
/** @defgroup tADL_Clock
  * @{
  */
#define FMC_NAND_TADL_NONE                           (0U)
#define FMC_NAND_TADL_1CLOCK                         (FMC_NAND_WST_TADL_0)
#define FMC_NAND_TADL_2CLOCK                         (FMC_NAND_WST_TADL_1)
#define FMC_NAND_TADL_3CLOCK                         (FMC_NAND_WST_TADL_0 | FMC_NAND_WST_TADL_1)
#define FMC_NAND_TADL_4CLOCK                         (FMC_NAND_WST_TADL_2)
#define FMC_NAND_TADL_5CLOCK                         (FMC_NAND_WST_TADL_0 | FMC_NAND_WST_TADL2)
#define FMC_NAND_TADL_6CLOCK                         (FMC_NAND_WST_TADL_1 | FMC_NAND_WST_TADL2)
#define FMC_NAND_TADL_7CLOCK                         (FMC_NAND_WST_TADL_0 | FMC_NAND_WST_TADL1 | FMC_NAND_WST_TADL2)
#define FMC_NAND_TADL_8CLOCK                         (FMC_NAND_WST_TADL_3)
#define FMC_NAND_TADL_9CLOCK                         (FMC_NAND_WST_TADL_0 | FMC_NAND_WST_TADL_3)
#define FMC_NAND_TADL_10CLOCK                        (FMC_NAND_WST_TADL_1 | FMC_NAND_WST_TADL_3)
#define FMC_NAND_TADL_11CLOCK                        (FMC_NAND_WST_TADL_0 | FMC_NAND_WST_TADL_1 | FMC_NAND_WST_TADL_3)
#define FMC_NAND_TADL_12CLOCK                        (FMC_NAND_WST_TADL_2 | FMC_NAND_WST_TADL_3)
#define FMC_NAND_TADL_13CLOCK                        (FMC_NAND_WST_TADL_0 | FMC_NAND_WST_TADL_2 | FMC_NAND_WST_TADL_3)
#define FMC_NAND_TADL_14CLOCK                        (FMC_NAND_WST_TADL_1 | FMC_NAND_WST_TADL_2 | FMC_NAND_WST_TADL_3)
#define FMC_NAND_TADL_15CLOCK                        (FMC_NAND_WST_TADL_0 | FMC_NAND_WST_TADL_1 | FMC_NAND_WST_TADL_2 | FMC_NAND_WST_TADL_3)

#define IS_FMC_NAND_TADL_CLOCK(CLOCK)                (((CLOCK) == FMC_NAND_TADL_NONE    || \
                                                      ((CLOCK) == FMC_NAND_TADL_1CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TADL_2CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TADL_3CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TADL_4CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TADL_5CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TADL_6CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TADL_7CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TADL_8CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TADL_9CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TADL_10CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TADL_11CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TADL_12CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TADL_13CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TADL_14CLOCK) || \
                                                      ((CLOCK) <= FMC_NAND_TADL_15CLOCK)))
/**
  * @}
  */
  
/** @defgroup tRHW_Clock
  * @{
  */
#define FMC_NAND_TRHW_NONE                           (0U)
#define FMC_NAND_TRHW_1CLOCK                         (FMC_NAND_WST_TRHW_0)
#define FMC_NAND_TRHW_2CLOCK                         (FMC_NAND_WST_TRHW_1)
#define FMC_NAND_TRHW_3CLOCK                         (FMC_NAND_WST_TRHW_0 | FMC_NAND_WST_TRHW_1)
#define FMC_NAND_TRHW_4CLOCK                         (FMC_NAND_WST_TRHW_2)
#define FMC_NAND_TRHW_5CLOCK                         (FMC_NAND_WST_TRHW_0 | FMC_NAND_WST_TRHW_2)
#define FMC_NAND_TRHW_6CLOCK                         (FMC_NAND_WST_TRHW_1 | FMC_NAND_WST_TRHW_2)
#define FMC_NAND_TRHW_7CLOCK                         (FMC_NAND_WST_TRHW_0 | FMC_NAND_WST_TRHW_1 | FMC_NAND_WST_TRHW_2)
#define FMC_NAND_TRHW_8CLOCK                         (FMC_NAND_WST_TRHW_3)
#define FMC_NAND_TRHW_9CLOCK                         (FMC_NAND_WST_TRHW_0 | FMC_NAND_WST_TRHW_3)
#define FMC_NAND_TRHW_10CLOCK                        (FMC_NAND_WST_TRHW_1 | FMC_NAND_WST_TRHW_3)
#define FMC_NAND_TRHW_11CLOCK                        (FMC_NAND_WST_TRHW_0 | FMC_NAND_WST_TRHW_1 | FMC_NAND_WST_TRHW_3)
#define FMC_NAND_TRHW_12CLOCK                        (FMC_NAND_WST_TRHW_2 | FMC_NAND_WST_TRHW_3)
#define FMC_NAND_TRHW_13CLOCK                        (FMC_NAND_WST_TRHW_0 | FMC_NAND_WST_TRHW_2 | FMC_NAND_WST_TRHW_3)
#define FMC_NAND_TRHW_14CLOCK                        (FMC_NAND_WST_TRHW_1 | FMC_NAND_WST_TRHW_2 | FMC_NAND_WST_TRHW_3)
#define FMC_NAND_TRHW_15CLOCK                        (FMC_NAND_WST_TRHW_0 | FMC_NAND_WST_TRHW_1 | FMC_NAND_WST_TRHW_2 | FMC_NAND_WST_TRHW_3)

#define IS_FMC_NAND_TRHW_CLOCK(CLOCK)                (((CLOCK) == FMC_NAND_TRHW_NONE    || \
                                                      ((CLOCK) == FMC_NAND_TRHW_1CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRHW_2CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRHW_3CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRHW_4CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRHW_5CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRHW_6CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRHW_7CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRHW_8CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRHW_9CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRHW_10CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TRHW_11CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TRHW_12CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TRHW_13CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TRHW_14CLOCK) || \
                                                      ((CLOCK) <= FMC_NAND_TRHW_15CLOCK)))
/**
  * @}
  */

/** @defgroup tWHR_Clock
  * @{
  */
#define FMC_NAND_TWHR_NONE                           (0U)
#define FMC_NAND_TWHR_1CLOCK                         (FMC_NAND_WST_TWHR_0)
#define FMC_NAND_TWHR_2CLOCK                         (FMC_NAND_WST_TWHR_1)
#define FMC_NAND_TWHR_3CLOCK                         (FMC_NAND_WST_TWHR_0 | FMC_NAND_WST_TWHR_1)
#define FMC_NAND_TWHR_4CLOCK                         (FMC_NAND_WST_TWHR_2)
#define FMC_NAND_TWHR_5CLOCK                         (FMC_NAND_WST_TWHR_0 | FMC_NAND_WST_TWHR_2)
#define FMC_NAND_TWHR_6CLOCK                         (FMC_NAND_WST_TWHR_1 | FMC_NAND_WST_TWHR_2)
#define FMC_NAND_TWHR_7CLOCK                         (FMC_NAND_WST_TWHR_0 | FMC_NAND_WST_TWHR_1 | FMC_NAND_WST_TWHR_2)
#define FMC_NAND_TWHR_8CLOCK                         (FMC_NAND_WST_TWHR_3)
#define FMC_NAND_TWHR_9CLOCK                         (FMC_NAND_WST_TWHR_0 | FMC_NAND_WST_TWHR_3)
#define FMC_NAND_TWHR_10CLOCK                        (FMC_NAND_WST_TWHR_1 | FMC_NAND_WST_TWHR_3)
#define FMC_NAND_TWHR_11CLOCK                        (FMC_NAND_WST_TWHR_0 | FMC_NAND_WST_TWHR_1 | FMC_NAND_WST_TWHR_3)
#define FMC_NAND_TWHR_12CLOCK                        (FMC_NAND_WST_TWHR_2 | FMC_NAND_WST_TWHR_3)
#define FMC_NAND_TWHR_13CLOCK                        (FMC_NAND_WST_TWHR_0 | FMC_NAND_WST_TWHR_2 | FMC_NAND_WST_TWHR_3)
#define FMC_NAND_TWHR_14CLOCK                        (FMC_NAND_WST_TWHR_1 | FMC_NAND_WST_TWHR_2 | FMC_NAND_WST_TWHR_3)
#define FMC_NAND_TWHR_15CLOCK                        (FMC_NAND_WST_TWHR_0 | FMC_NAND_WST_TWHR_1 | FMC_NAND_WST_TWHR_2 | FMC_NAND_WST_TWHR_3)

#define IS_FMC_NAND_TWHR_CLOCK(CLOCK)                (((CLOCK) == FMC_NAND_TWHR_NONE    || \
                                                      ((CLOCK) == FMC_NAND_TWHR_1CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWHR_2CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWHR_3CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWHR_4CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWHR_5CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWHR_6CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWHR_7CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWHR_8CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWHR_9CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWHR_10CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWHR_11CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWHR_12CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWHR_13CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWHR_14CLOCK) || \
                                                      ((CLOCK) <= FMC_NAND_TWHR_15CLOCK)))
/**
  * @}
  */


/** @defgroup tREH_Clock
  * @{
  */
#define FMC_NAND_TREH_NONE                           (0U)
#define FMC_NAND_TREH_1CLOCK                         (FMC_NAND_WST_TREH_0)
#define FMC_NAND_TREH_2CLOCK                         (FMC_NAND_WST_TREH_1)
#define FMC_NAND_TREH_3CLOCK                         (FMC_NAND_WST_TREH_0 | FMC_NAND_WST_TREH_1)
#define FMC_NAND_TREH_4CLOCK                         (FMC_NAND_WST_TREH_2)
#define FMC_NAND_TREH_5CLOCK                         (FMC_NAND_WST_TREH_0 | FMC_NAND_WST_TREH_2)
#define FMC_NAND_TREH_6CLOCK                         (FMC_NAND_WST_TREH_1 | FMC_NAND_WST_TREH_2)
#define FMC_NAND_TREH_7CLOCK                         (FMC_NAND_WST_TREH_0 | FMC_NAND_WST_TREH_1 | FMC_NAND_WST_TREH_2)
#define FMC_NAND_TREH_8CLOCK                         (FMC_NAND_WST_TREH_3)
#define FMC_NAND_TREH_9CLOCK                         (FMC_NAND_WST_TREH_0 | FMC_NAND_WST_TREH_3)
#define FMC_NAND_TREH_10CLOCK                        (FMC_NAND_WST_TREH_1 | FMC_NAND_WST_TREH_3)
#define FMC_NAND_TREH_11CLOCK                        (FMC_NAND_WST_TREH_0 | FMC_NAND_WST_TREH_1 | FMC_NAND_WST_TREH_3)
#define FMC_NAND_TREH_12CLOCK                        (FMC_NAND_WST_TREH_2 | FMC_NAND_WST_TREH_3)
#define FMC_NAND_TREH_13CLOCK                        (FMC_NAND_WST_TREH_0 | FMC_NAND_WST_TREH_2 | FMC_NAND_WST_TREH_3)
#define FMC_NAND_TREH_14CLOCK                        (FMC_NAND_WST_TREH_1 | FMC_NAND_WST_TREH_2 | FMC_NAND_WST_TREH_3)
#define FMC_NAND_TREH_15CLOCK                        (FMC_NAND_WST_TREH_0 | FMC_NAND_WST_TREH_1 | FMC_NAND_WST_TREH_2 | FMC_NAND_WST_TREH_3)

#define IS_FMC_NAND_TREH_CLOCK(CLOCK)                (((CLOCK) == FMC_NAND_TREH_NONE    || \
                                                      ((CLOCK) == FMC_NAND_TREH_1CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TREH_2CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TREH_3CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TREH_4CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TREH_5CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TREH_6CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TREH_7CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TREH_8CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TREH_9CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TREH_10CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TREH_11CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TREH_12CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TREH_13CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TREH_14CLOCK) || \
                                                      ((CLOCK) <= FMC_NAND_TREH_15CLOCK)))
/**
  * @}
  */
  

/** @defgroup tRP_Clock
  * @{
  */
#define FMC_NAND_TRP_NONE                            (0U)
#define FMC_NAND_TRP_1CLOCK                          (FMC_NAND_WST_TRP_0)
#define FMC_NAND_TRP_2CLOCK                          (FMC_NAND_WST_TRP_1)
#define FMC_NAND_TRP_3CLOCK                          (FMC_NAND_WST_TRP_0 | FMC_NAND_WST_TRP_1)
#define FMC_NAND_TRP_4CLOCK                          (FMC_NAND_WST_TRP_2)
#define FMC_NAND_TRP_5CLOCK                          (FMC_NAND_WST_TRP_0 | FMC_NAND_WST_TRP_2)
#define FMC_NAND_TRP_6CLOCK                          (FMC_NAND_WST_TRP_1 | FMC_NAND_WST_TRP_2)
#define FMC_NAND_TRP_7CLOCK                          (FMC_NAND_WST_TRP_0 | FMC_NAND_WST_TRP_1 | FMC_NAND_WST_TRP_2)
#define FMC_NAND_TRP_8CLOCK                          (FMC_NAND_WST_TRP_3)
#define FMC_NAND_TRP_9CLOCK                          (FMC_NAND_WST_TRP_0 | FMC_NAND_WST_TRP_3)
#define FMC_NAND_TRP_10CLOCK                         (FMC_NAND_WST_TRP_1 | FMC_NAND_WST_TRP_3)
#define FMC_NAND_TRP_11CLOCK                         (FMC_NAND_WST_TRP_0 | FMC_NAND_WST_TRP_1 | FMC_NAND_WST_TRP_3)
#define FMC_NAND_TRP_12CLOCK                         (FMC_NAND_WST_TRP_2 | FMC_NAND_WST_TRP_3)
#define FMC_NAND_TRP_13CLOCK                         (FMC_NAND_WST_TRP_0 | FMC_NAND_WST_TRP_2 | FMC_NAND_WST_TRP_3)
#define FMC_NAND_TRP_14CLOCK                         (FMC_NAND_WST_TRP_1 | FMC_NAND_WST_TRP_2 | FMC_NAND_WST_TRP_3)
#define FMC_NAND_TRP_15CLOCK                         (FMC_NAND_WST_TRP_0 | FMC_NAND_WST_TRP_1 | FMC_NAND_WST_TRP_2 | FMC_NAND_WST_TRP_3)

#define IS_FMC_NAND_TRP_CLOCK(CLOCK)                 (((CLOCK) == FMC_NAND_TRP_NONE    || \
                                                      ((CLOCK) == FMC_NAND_TRP_1CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRP_2CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRP_3CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRP_4CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRP_5CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRP_6CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRP_7CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRP_8CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRP_9CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TRP_10CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TRP_11CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TRP_12CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TRP_13CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TRP_14CLOCK) || \
                                                      ((CLOCK) <= FMC_NAND_TRP_15CLOCK)))
/**
  * @}
  */
 
/** @defgroup tWH_Clock
  * @{
  */
#define FMC_NAND_TWH_NONE                            (0U)
#define FMC_NAND_TWH_1CLOCK                          (FMC_NAND_WST_TWH_0)
#define FMC_NAND_TWH_2CLOCK                          (FMC_NAND_WST_TWH_1)
#define FMC_NAND_TWH_3CLOCK                          (FMC_NAND_WST_TWH_0 | FMC_NAND_WST_TWH_1)
#define FMC_NAND_TWH_4CLOCK                          (FMC_NAND_WST_TWH_2)
#define FMC_NAND_TWH_5CLOCK                          (FMC_NAND_WST_TWH_0 | FMC_NAND_WST_TWH_2)
#define FMC_NAND_TWH_6CLOCK                          (FMC_NAND_WST_TWH_1 | FMC_NAND_WST_TWH_2)
#define FMC_NAND_TWH_7CLOCK                          (FMC_NAND_WST_TWH_0 | FMC_NAND_WST_TWH_1 | FMC_NAND_WST_TWH_2)
#define FMC_NAND_TWH_8CLOCK                          (FMC_NAND_WST_TWH_3)
#define FMC_NAND_TWH_9CLOCK                          (FMC_NAND_WST_TWH_0 | FMC_NAND_WST_TWH_3)
#define FMC_NAND_TWH_10CLOCK                         (FMC_NAND_WST_TWH_1 | FMC_NAND_WST_TWH_3)
#define FMC_NAND_TWH_11CLOCK                         (FMC_NAND_WST_TWH_0 | FMC_NAND_WST_TWH_1 | FMC_NAND_WST_TWH_3)
#define FMC_NAND_TWH_12CLOCK                         (FMC_NAND_WST_TWH_2 | FMC_NAND_WST_TWH_3)
#define FMC_NAND_TWH_13CLOCK                         (FMC_NAND_WST_TWH_0 | FMC_NAND_WST_TWH_2 | FMC_NAND_WST_TWH_3)
#define FMC_NAND_TWH_14CLOCK                         (FMC_NAND_WST_TWH_1 | FMC_NAND_WST_TWH_2 | FMC_NAND_WST_TWH_3)
#define FMC_NAND_TWH_15CLOCK                         (FMC_NAND_WST_TWH_0 | FMC_NAND_WST_TWH_1 | FMC_NAND_WST_TWH_2 | FMC_NAND_WST_TWH_3)

#define IS_FMC_NAND_TWH_CLOCK(CLOCK)                 (((CLOCK) == FMC_NAND_TWH_NONE    || \
                                                      ((CLOCK) == FMC_NAND_TWH_1CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWH_2CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWH_3CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWH_4CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWH_5CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWH_6CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWH_7CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWH_8CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWH_9CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWH_10CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWH_11CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWH_12CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWH_13CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWH_14CLOCK) || \
                                                      ((CLOCK) <= FMC_NAND_TWH_15CLOCK)))
/**
  * @}
  */ 
  
/** @defgroup tWP_Clock
  * @{
  */
#define FMC_NAND_TWP_NONE                            (0U)
#define FMC_NAND_TWP_1CLOCK                          (FMC_NAND_WST_TWP_0)
#define FMC_NAND_TWP_2CLOCK                          (FMC_NAND_WST_TWP_1)
#define FMC_NAND_TWP_3CLOCK                          (FMC_NAND_WST_TWP_0 | FMC_NAND_WST_TWP_1)
#define FMC_NAND_TWP_4CLOCK                          (FMC_NAND_WST_TWP_2)
#define FMC_NAND_TWP_5CLOCK                          (FMC_NAND_WST_TWP_0 | FMC_NAND_WST_TWP_2)
#define FMC_NAND_TWP_6CLOCK                          (FMC_NAND_WST_TWP_1 | FMC_NAND_WST_TWP_2)
#define FMC_NAND_TWP_7CLOCK                          (FMC_NAND_WST_TWP_0 | FMC_NAND_WST_TWP_1 | FMC_NAND_WST_TWP_2)
#define FMC_NAND_TWP_8CLOCK                          (FMC_NAND_WST_TWP_3)
#define FMC_NAND_TWP_9CLOCK                          (FMC_NAND_WST_TWP_0 | FMC_NAND_WST_TWP_3)
#define FMC_NAND_TWP_10CLOCK                         (FMC_NAND_WST_TWP_1 | FMC_NAND_WST_TWP_3)
#define FMC_NAND_TWP_11CLOCK                         (FMC_NAND_WST_TWP_0 | FMC_NAND_WST_TWP_1 | FMC_NAND_WST_TWP_3)
#define FMC_NAND_TWP_12CLOCK                         (FMC_NAND_WST_TWP_2 | FMC_NAND_WST_TWP_3)
#define FMC_NAND_TWP_13CLOCK                         (FMC_NAND_WST_TWP_0 | FMC_NAND_WST_TWP_2 | FMC_NAND_WST_TWP_3)
#define FMC_NAND_TWP_14CLOCK                         (FMC_NAND_WST_TWP_1 | FMC_NAND_WST_TWP_2 | FMC_NAND_WST_TWP_3)
#define FMC_NAND_TWP_15CLOCK                         (FMC_NAND_WST_TWP_0 | FMC_NAND_WST_TWP_1 | FMC_NAND_WST_TWP_2 | FMC_NAND_WST_TWP_3)

#define IS_FMC_NAND_TWP_CLOCK(CLOCK)                 (((CLOCK) == FMC_NAND_TWP_NONE    || \
                                                      ((CLOCK) == FMC_NAND_TWP_1CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWP_2CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWP_3CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWP_4CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWP_5CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWP_6CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWP_7CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWP_8CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWP_9CLOCK)  || \
                                                      ((CLOCK) == FMC_NAND_TWP_10CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWP_11CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWP_12CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWP_13CLOCK) || \
                                                      ((CLOCK) == FMC_NAND_TWP_14CLOCK) || \
                                                      ((CLOCK) <= FMC_NAND_TWP_15CLOCK)))
/**
  * @}
  */ 
  
/** @defgroup  FMC_NAND CMD
  * @{
  */

#define FMC_NAND_CMD_READ1                0x00
#define FMC_NAND_CMD_READ2                0x30
#define FMC_NAND_CMD_ID                   0x90
#define FMC_NAND_CMD_STATUS               0x70
#define FMC_NAND_CMD_RESET                0xFF
#define FMC_NAND_CMD_PROGRAM1             0x80
#define FMC_NAND_CMD_PROGRAM2             0x10
#define FMC_NAND_CMD_ERASE1               0x60
#define FMC_NAND_CMD_ERASE2               0xD0
#define FMC_NAND_CMD_RANDOMINPUT          0x85
#define FMC_NAND_CMD_RANDOMOUTPUT1        0x05
#define FMC_NAND_CMD_RANDOMOUTPUT2        0xE0
#define FMC_NAND_CMD_FEATURE              0xEF

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
  
/** @defgroup BCH CHANNEL RST
  * @{
  */ 
  
#define BCH_CHANNEL_RST		         0x1

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

}FMC_NAND_InitTypeDef;

/*
 * @brief  UART handle Structure definition
 */
typedef struct
{
    FMC_NAND_TypeDef           *Instance;                /*!< FMA Nand registers base address  */

    FMC_NAND_InitTypeDef        Init;                    /*!< FMA Nand parameters  */
	
    void* FMC_NAND_Data_Buff;                            /*!< FMA Nand databuff base address */
	
    uint32_t FMC_NAND_Data_Len;                          /*!< amount of CRC data to be calculated */
    
}FMC_NAND_HandleTypeDef;  
  
/******************************************************************************
*@brief : Initialize nand MSP: CLK, GPIO, NVIC
*         
*@param : hnand: handle with nand parameters.
*@return: None
******************************************************************************/
void HAL_FMC_NAND_MspInit(FMC_NAND_HandleTypeDef *hnand);

/******************************************************************************
*@brief : Initialize nandaccording to the specified parameters in hnand.
*         
*@param : hnand: handle with nand parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_Init(FMC_NAND_HandleTypeDef *hnand);

/******************************************************************************
*@brief : Reset Nand Flash
*         
*@param : hnand: handle with nand Nand parameters.
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_FlashReset(FMC_NAND_HandleTypeDef *hnand);

/******************************************************************************
*@brief : Read ID from Nand Flash
*         
*@param : hnand: handle with nand parameters.
*@param : rdata: start address to store ID
*@param : lenth: ID length
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_FlashGetID(FMC_NAND_HandleTypeDef *hnand, uint8_t rdata[], uint8_t lenth);

/******************************************************************************
*@brief : Erase a block
*         
*@param : hnand: handle with nand parameters.
*@param : BlockAddr: start address of the block to erase
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_FlashErase(FMC_NAND_HandleTypeDef *hnand, uint32_t PageAddr);

/******************************************************************************
*@brief : Program one sector(512 bytes) 
*
*@param : hnand: handle with nand parameters.
*@param : RowAddr: row start address
*@param : ColumnAddr: column start address
*@param : wdata: start address of data to program
*@param : ecc_en:select the mode of program 
          BCH_ECC_MODE_EN : program with ecc mode
          BCH_ECC_MODE_DIS: progran with no ecc mode
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_Flash_Program(FMC_NAND_HandleTypeDef *hnand, uint32_t RowAddr, uint16_t ColumnAddr, uint8_t wdata[], uint8_t ecc_en);

/******************************************************************************
*@brief : Program one sector(512 bytes) using necc channel and ecc data
*
*@param : hnand: handle with nand parameters.
*@param : RowAddr: row start address
*@param : ColumnAddr: column start address
*@param : wdata: start address of data to program
*@param : pEccByte: input ecc data
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_Flash_Program_NECC_with_ECC_CODE(FMC_NAND_HandleTypeDef *hnand, uint32_t RowAddr, uint16_t ColumnAddr, uint8_t wdata[], uint8_t pEccByte[]);

/******************************************************************************
*@brief : Read one sector(512 bytes) 
*         
*@param : hnand: handle with nand parameters.
*@param : RowAddr: row start address
*@param : ColumnAddr: column start address
*@param : rdata: start address of read data
*@param : ecc_en:select the mode of read 
          BCH_ECC_MODE_EN : read with ecc mode
          BCH_ECC_MODE_DIS: read with no ecc mode
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_FlashRead(FMC_NAND_HandleTypeDef *hnand, uint32_t RowAddr, uint16_t ColumnAddr, uint8_t rdata[], uint8_t ecc_en);


/******************************************************************************
*@brief : Reset ECC Channel
*  
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_Reset_ECC_Channel(FMC_NAND_HandleTypeDef *hnand);
#endif




