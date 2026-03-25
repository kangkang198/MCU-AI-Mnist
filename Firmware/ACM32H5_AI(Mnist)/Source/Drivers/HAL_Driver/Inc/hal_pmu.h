/*
  ******************************************************************************
  * @file    HAL_PMU.h
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of PMU HAL module.
  ******************************************************************************
*/

#ifndef __HAL_PMU_H__
#define __HAL_PMU_H__

#include "hal.h"







/**
  * @brief  IO wake-up source
  */
typedef enum
{
    PMU_WAKEUP1  = 0x00000001,      //PA0 
    PMU_WAKEUP2  = 0x00000002,      //PA2  
    PMU_WAKEUP3  = 0x00000004,      //PI8  
    PMU_WAKEUP4  = 0x00000008,      //PC13
    PMU_WAKEUP5  = 0x00000010,      //PI11     
}PMU_WakeUpIo_t;

/**
  * @brief  RTC wake-up source
  */
typedef enum
{
    STANDBY_WAKEUP_WUTIE  = RTC_IE_WUTIE,
    STANDBY_WAKEUP_STAMP2 = (RTC_IE_STP2RIE | RTC_IE_STP2FIE),
    STANDBY_WAKEUP_STAMP1 = (RTC_IE_STP1RIE | RTC_IE_STP1FIE),
    STANDBY_WAKEUP_32S    = RTC_IE_ADJ32_IE,
    STANDBY_WAKEUP_ALARM  = RTC_IE_ALM_IE,
    STANDBY_WAKEUP_1KHZ   = RTC_IE_1KHZ_IE,
    STANDBY_WAKEUP_256HZ  = RTC_IE_256HZ_IE,
    STANDBY_WAKEUP_64HZ   = RTC_IE_64HZ_IE ,
    STANDBY_WAKEUP_16HZ   = RTC_IE_16HZ_IE ,
    STANDBY_WAKEUP_8HZ    = RTC_IE_8HZ_IE ,
    STANDBY_WAKEUP_4HZ    = RTC_IE_4HZ_IE ,
    STANDBY_WAKEUP_2HZ    = RTC_IE_2HZ_IE ,   
    STANDBY_WAKEUP_SEC    = RTC_IE_SEC_IE ,
    STANDBY_WAKEUP_MIN    = RTC_IE_MIN_IE ,
    STANDBY_WAKEUP_HOUR   = RTC_IE_HOUR_IE ,
    STANDBY_WAKEUP_DATE   = RTC_IE_DATE_IE ,
}PMU_WakeUpRtc_t;  


/**
  * @brief  Wakeup Polarity Configuration
  */
typedef enum
{
    PMU_WAKEUP_HIGH  = 0x00000000,      
    PMU_WAKEUP_LOW   = 0x00000001,         
}PMU_WakeUpPolarity_t;


/**
  * @brief  Wakeup flag
  */
#define PMU_FLAG_WAKEUP1                    ( PMU_SR_WUPFX_0 )
#define PMU_FLAG_WAKEUP2                    ( PMU_SR_WUPFX_1 )
#define PMU_FLAG_WAKEUP3                    ( PMU_SR_WUPFX_2 )
#define PMU_FLAG_WAKEUP4                    ( PMU_SR_WUPFX_3 )
#define PMU_FLAG_WAKEUP5                    ( PMU_SR_WUPFX_4 )
//#define PMU_FLAG_WAKEUP6                    ( PMU_SR_WUPFX_5 )
#define PMU_FLAG_STANDBY                    ( PMU_SR_SBF )
#define PMU_FLAG_RTC                        ( PMU_SR_RTCWUF )
#define PMU_FLAG_RSET                       ( PMU_SR_RSTWUF )
#define PMU_FLAG_IWDT                       ( PMU_SR_IWDTWUF )
#define PMU_FLAG_BOR                        ( PMU_SR_BORWUF )



/**
  * @brief  Wait for an interrupt or event
  */

#define WAIT_FOR_INT                        0x00000000  
#define WAIT_FOR_EVENT                      0x00000001

/**
  * @brief  Lowpower mode
  */
#define PMU_CTRL0_LPMS_STOP                  ( 0x0U << PMU_CTRL0_LPMS_Pos )  
#define PMU_CTRL0_LPMS_STANDBY               ( 0x1U << PMU_CTRL0_LPMS_Pos )  

/**
  * @brief  LVD Voltage
  */
#define PMU_LVD_1V71                        ( 0x0U << PMU_CTRL1_LVDSEL_Pos)
#define PMU_LVD_2V01                        ( 0x1U << PMU_CTRL1_LVDSEL_Pos)  
#define PMU_LVD_2V23                        ( 0x2U << PMU_CTRL1_LVDSEL_Pos)
#define PMU_LVD_2V43                        ( 0x3U << PMU_CTRL1_LVDSEL_Pos)
#define PMU_LVD_2V51                        ( 0x4U << PMU_CTRL1_LVDSEL_Pos)
#define PMU_LVD_2V73                        ( 0x5U << PMU_CTRL1_LVDSEL_Pos)  
#define PMU_LVD_2V80                        ( 0x6U << PMU_CTRL1_LVDSEL_Pos)
#define PMU_LVD_2V90                        ( 0x7U << PMU_CTRL1_LVDSEL_Pos)
#define IS_PMU_LVD_VOLTAGE(VOLTAGE)         (((VOLTAGE) == PMU_LVD_1V71) || ((VOLTAGE) == PMU_LVD_2V01)|| \
                                            ((VOLTAGE) == PMU_LVD_2V23) || ((VOLTAGE) == PMU_LVD_2V43)|| \
                                            ((VOLTAGE) == PMU_LVD_2V51) || ((VOLTAGE) == PMU_LVD_2V73)|| \
                                            ((VOLTAGE) == PMU_LVD_2V80) || ((VOLTAGE) == PMU_LVD_2V90))

/**
  * @brief  LVD Filter
  */
#define PMU_LVD_FILTER_1                    ( 0x0U << PMU_CTRL1_FLTTIME_Pos)
#define PMU_LVD_FILTER_2                    ( 0x1U << PMU_CTRL1_FLTTIME_Pos)
#define PMU_LVD_FILTER_4                    ( 0x2U << PMU_CTRL1_FLTTIME_Pos)
#define PMU_LVD_FILTER_16                   ( 0x3U << PMU_CTRL1_FLTTIME_Pos)
#define PMU_LVD_FILTER_64                   ( 0x4U << PMU_CTRL1_FLTTIME_Pos)
#define PMU_LVD_FILTER_256                  ( 0x5U << PMU_CTRL1_FLTTIME_Pos)
#define PMU_LVD_FILTER_1024                 ( 0x6U << PMU_CTRL1_FLTTIME_Pos)
#define PMU_LVD_FILTER_4095                 ( 0x7U << PMU_CTRL1_FLTTIME_Pos)
#define IS_PMU_LVD_FILTER(FILTER)           (((FILTER) == PMU_LVD_FILTER_1) || \
                                            ((FILTER) == PMU_LVD_FILTER_2) || \
                                            ((FILTER) == PMU_LVD_FILTER_4) || \
                                            ((FILTER) == PMU_LVD_FILTER_16) || \
                                            ((FILTER) == PMU_LVD_FILTER_64) || \
                                            ((FILTER) == PMU_LVD_FILTER_256) || \
                                            ((FILTER) == PMU_LVD_FILTER_1024) || \
                                            ((FILTER) == PMU_LVD_FILTER_4095))
                                                
/**
  * @brief  BOR Voltage
  */
#define PMU_BOR_2V0_2V1                     ( 0x0U << PMU_CTRL2_BORCFG_Pos)
#define PMU_BOR_2V2_2V3                     ( 0x1U << PMU_CTRL2_BORCFG_Pos)
#define PMU_BOR_2V49_2V61                   ( 0x2U << PMU_CTRL2_BORCFG_Pos)
#define PMU_BOR_2V77_2V90                   ( 0x3U << PMU_CTRL2_BORCFG_Pos)
#define IS_PMU_BOR_VOLTAGE(VOLTAGE)         (((VOLTAGE) == PMU_BOR_2V0_2V1)     || \
                                            ((VOLTAGE) == PMU_BOR_2V2_2V3)      || \
                                            ((VOLTAGE) == PMU_BOR_2V49_2V61)    || \
                                            ((VOLTAGE) == PMU_BOR_2V77_2V90))

/** @defgroup STANDBY mode wake-up waiting time
  * @{
  */                        
#define IS_PMU_STANDBY_WAKE_WAIT(WAIT)          ((WAIT) <= 0xFU)

                                                
/** @defgroup PMU STOP wakeup wait time 
  * @{
  */ 
#define IS_PMU_STOP_WAKE_WAIT(WAIT)             ((WAIT) <= 0xFFFU)


/** @defgroup STANDBY domain IO  
  * @{
  */
#define PMU_PIN_PC13                            (0x00U)
#define PMU_PIN_PC14                            (0x01U)
#define PMU_PIN_PC15                            (0x02U)
#define PMU_PIN_PI8                             (0x03U)
#define IS_PMU_PIN(PIN)                         (((PIN) == PMU_PIN_PC13) || ((PIN) == PMU_PIN_PC14) || \
                                                ((PIN) == PMU_PIN_PC15) || ((PIN) == PMU_PIN_PI8))

/** @defgroup STANDBY domain IO function selection  
  * @{
  */
#define PMU_PIN_FUNCTION_GPIO                   (0U)
#define PMU_PIN_FUNCTION_PC14_VALUE             (1U)
#define PMU_PIN_FUNCTION_PC15_VALUE             (1U)
#define PMU_PIN_FUNCTION_PI8_VALUE              (1U)
#define PMU_PIN_FUNCTION_PC13_RTC_SIGNAL        (1U)
#define PMU_PIN_FUNCTION_TAMPER                 (2U)
#define PMU_PIN_FUNCTION_PC13_VALUE             (3U)
#define IS_PMU_PIN_FUNCTION(__FUNC__)           (((__FUNC__) == PMU_PIN_FUNCTION_GPIO)              || \
                                                ((__FUNC__) == PMU_PIN_FUNCTION_PC14_VALUE)         || \
                                                ((__FUNC__) == PMU_PIN_FUNCTION_PC15_VALUE)         || \
                                                ((__FUNC__) == PMU_PIN_FUNCTION_PI8_VALUE)          || \
                                                ((__FUNC__) == PMU_PIN_FUNCTION_PC13_RTC_SIGNAL)    || \
                                                ((__FUNC__) == PMU_PIN_FUNCTION_TAMPER)             || \
                                                ((__FUNC__) == PMU_PIN_FUNCTION_PC13_VALUE))
/**
  * @}
  */

/** @defgroup STANDBY domain IO Pin Value 
  * @{
  */
#define PMU_PIN_VALUE_0                         (0x00U)
#define PMU_PIN_VALUE_1                         (0x01U)
#define IS_PMU_PIN_VALUE(VALUE)                 (((VALUE) == PMU_PIN_VALUE_0) || ((VALUE) == PMU_PIN_VALUE_1))


/** @defgroup PMU domain IO Pin (PC13) output mode 
  * @{
  */
#define PMU_PIN_PC13_OD                         (0U)
#define PMU_PIN_PC13_PP                         (1U)
#define IS_PMU_PIN_PC13_OUTPUT(__MODE__)        (((__MODE__) == PMU_PIN_PC13_OD) || \
                                                ((__MODE__) == PMU_PIN_PC13_PP))
/**
  * @}
  */
  
  
/**
  * @brief  Clear all wake-up status
  */
#define ALL_WANKEUP_STATUS                      (0xFFFFFFFF) 


/**
  * @brief  RTC module write enable or diasble
  */
#define __HAL_PMU_RTC_WRITE_ENABLE              (PMU->CTRL0 |= PMU_CTRL0_RTC_WE)
#define __HAL_PMU_RTC_WRITE_DISABLE             (PMU->CTRL0 &= ~PMU_CTRL0_RTC_WE)

/**
  * @brief  Tamper Pin 
  */
#define PMU_IOSEL_PC13_SEL_RTC_TAMPER           (0x2U)
#define PMU_IOSEL_PI8_SEL_RTC_TAMPER            (0x2U)

/** @brief  PC13 function select 
  * @param  __FUNC__: PC13 function select.
  *         This parameter can be 0: GPIO£¬1£ºRTC Fout£¬2£ºRTC tamper 3£ºPC13 Value
  */
#define __HAL_PMU_PC13_SEL(__FUNC__)            (PMU->IOSEL |= (PMU->IOSEL & ~(PMU_IOSEL_PC13SEL_Msk)) | (__FUNC__ << PMU_IOSEL_PC13SEL_Pos))

/** @brief  PC14 function select 
  * @param  __FUNC__: PC14 function select.
  *         This parameter can be 0: GPIO£¬1£ºPC14 Value
  */
#define __HAL_PMU_PC14_SEL(__FUNC__)            (PMU->IOSEL |= (PMU->IOSEL & ~(PMU_IOSEL_PC14SEL_Msk)) | (__FUNC__ << PMU_IOSEL_PC14SEL_Pos))

/** @brief  PC15 function select 
  * @param  __FUNC__: PC15 function select.
  *         This parameter can be 0: GPIO£¬1£ºPC15 Value
  */
#define __HAL_PMU_PC15_SEL(__FUNC__)            (PMU->IOSEL |= (PMU->IOSEL & ~(PMU_IOSEL_PC15SEL_Msk)) | (__FUNC__ << PMU_IOSEL_PC15SEL_Pos))

/** @brief  PI8 function select 
  * @param  __FUNC__: PI8 function select.
  *         This parameter can be 0: GPIO£¬1£ºPI8 Value£¬2£ºRTC tamper 
  */
#define __HAL_PMU_PI8_SEL(__FUNC__)            (PMU->IOSEL |= (PMU->IOSEL & ~(PMU_IOSEL_PI8SEL_Msk)) | (__FUNC__ << PMU_IOSEL_PI8SEL_Pos))


/** @brief  PC13 Value set 
  * @param  __FUNC__: PC13 Value set.
  *         This parameter can be 0: set£¬1£ºclaer
  */
#define __HAL_PMU_PC13_VALUE(__VALUE__)         (PMU->IOSEL |= (PMU->IOSEL & ~(PMU_IOSEL_PC13VALUE_Msk)) | (__VALUE__ << PMU_IOSEL_PC13VALUE_Pos))

/** @brief  PC14 Value set 
  * @param  __FUNC__: PC14 Value set.
  *         This parameter can be 0: set£¬1£ºclaer
  */
#define __HAL_PMU_PC14_VALUE(__VALUE__)         (PMU->IOSEL |= (PMU->IOSEL & ~(PMU_IOSEL_PC14VALUE_Msk)) | (__VALUE__ << PMU_IOSEL_PC14VALUE_Pos))

/** @brief  PC15 Value set 
  * @param  __FUNC__: PC15 Value set.
  *         This parameter can be 0: set£¬1£ºclaer
  */
#define __HAL_PMU_PC15_VALUE(__VALUE__)         (PMU->IOSEL |= (PMU->IOSEL & ~(PMU_IOSEL_PC15VALUE_Msk)) | (__VALUE__ << PMU_IOSEL_PC15VALUE_Pos))

/** @brief  PI8 Value set 
  * @param  __FUNC__: PI8 Value set.
  *         This parameter can be 0: set£¬1£ºclaer
  */
#define __HAL_PMU_PI8_VALUE(__VALUE__)          (PMU->IOSEL |= (PMU->IOSEL & ~(PMU_IOSEL_PI8VALUE_Msk)) | (__VALUE__ << PMU_IOSEL_PI8VALUE_Pos))

void HAL_PMU_Init(void);

void HAL_PMU_EnterSleep(uint32_t mode);

void HAL_PMU_EnterStop(uint32_t mode);

void HAL_PMU_EnterStandbyMode(uint32_t mode);

void HAL_PMU_WakeupIOInit(PMU_WakeUpIo_t wakeup_io, PMU_WakeUpPolarity_t polarity);

void HAL_PMU_WakeupIODeInit(PMU_WakeUpIo_t wakeup_io);

void HAL_PMU_StandbyWakeupRTCConfig(PMU_WakeUpRtc_t wakeup_rtc);

void HAL_PMU_StandbyWakeupRTCRelease(PMU_WakeUpRtc_t wakeup_rtc);

bool HAL_PMU_CheckStandbyStatus(void);

bool HAL_PMU_CheckDeepSleepStatus(void);

uint32_t HAL_PMU_GetWakeupSource(void);

void HAL_PMU_ClearWakeupStatus(uint32_t status);

void HAL_PMU_LvdEnable(uint32_t voltage, uint32_t filter, uint32_t filter_en);

void HAL_PMU_LvdDisable(void);

void HAL_PMU_BorResetEnable(uint32_t voltage);

void HAL_PMU_BorResetDisable(void);

void HAL_PMU_BorIrqEnable(uint32_t voltage);

void HAL_PMU_BorIrqtDisable(void);

void HAL_PMU_StopWaitTime(uint32_t stopWaitTime);

void HAL_PMU_StandbypWaitTime(uint32_t standbyWaitTime);

void HAL_PMU_StandbyDomainPinConfig(uint32_t PMU_Pin, uint32_t PMU_Func);

void HAL_PMU_SetStandbyDomainPinValue(uint32_t PMU_Pin, uint32_t PMU_PinValue);

uint32_t HAL_PMU_GetStandbyDomainPinValue(uint32_t PMU_Pin);


#endif



