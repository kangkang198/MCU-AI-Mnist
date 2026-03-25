/*
  ******************************************************************************
  * @file    HAL_RTC.h
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of RTC HAL module.
  ******************************************************************************
*/

#ifndef __HAL_RTC_H__
#define __HAL_RTC_H__

#include "hal.h"






/**
  * @brief  RTC Configuration Structure definition
  */
typedef struct
{
    uint32_t ClockSource;           /*!< The RTC Clock Source to be configured.*/

    uint32_t Compensation;          /*!< The RTC Clock Compensation to be configured.*/

    uint32_t CompensationValue;     /*!< The RTC Clock Compensation Value to be configured.*/
}RTC_ConfigTypeDef;


/**
  * @brief  RTC Date structure definition
  */
typedef struct
{
    uint8_t Year;     /*!< Specifies the RTC Date Year.
                              This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x99 */

    uint8_t Month;    /*!< Specifies the RTC Date Month (in BCD format).*/

    uint8_t Date;     /*!< Specifies the RTC Date.
                              This parameter must be a number between Min_Data = 0x01 and Max_Data = 0x31 */

    uint8_t WeekDay;  /*!< Specifies the RTC Date WeekDay.*/
}RTC_DateTypeDef;
/* Attention: Year、Month、Date、Week use BCD code */


/**
  * @brief  RTC Time structure definition
  */
typedef struct
{
    uint8_t Hour;       /*!< Specifies the RTC Time Hour.
                                 This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x23 */

    uint8_t Minute;     /*!< Specifies the RTC Time Minute.
                                 This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x59 */

    uint8_t Second;     /*!< Specifies the RTC Time Seconds.
                                 This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x59 */
}RTC_TimeTypeDef;
/* Attention: Hour、Minute、Second use BCD code */


/**
  * @brief  RTC Time structure definition
  */
typedef struct
{
    uint32_t u32_AlarmMode;         /*!< Specifies the RTC alarm Mode.*/

    uint32_t u32_AlarmInterrupt;    /*!< Specifies the RTC alarm interrupt Enable or Disable.*/

    uint32_t u32_DayMask;           /*!< Specifies the RTC alarm Day/Week Mask.*/
    
    uint32_t u32_HourMask;          /*!< Specifies the RTC alarm Hour Mask.*/
    
    uint32_t u32_MinMask;           /*!< Specifies the RTC alarm Min Mask.*/
    
    uint32_t u32_AlarmWeek;         /*!< Specifies the RTC alarm week select(Select WeekMode this parameter is valid).*/
    
    uint32_t u32_AlarmDay;          /*!< Specifies the RTC alarm day  select(Select DayMode this parameter is valid).
                                         This parameter must be a number between Min_Data = 0x01 and Max_Data = 0x31 */
    
    uint32_t u32_Hours;             /*!< Specifies the RTC alarm Hour.
                                         This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x23 */

    uint32_t u32_Minutes;           /*!< Specifies the RTC alarm Minute.
                                         This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x59 */

    uint32_t u32_Seconds;           /*!< Specifies the RTC alarm Seconds.
                                         This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x59 */
}RTC_AlarmTypeDef;


/**
  * @brief  RTC Temper structure definition
  */
typedef struct 
{
    uint32_t u32_TemperEdge;    /*!< Specifies the RTC Temper edge select. */

    uint32_t u32_InterruptEN;   /*!< Specifies the RTC Temper interrupt enable.*/

    uint32_t u32_ClearBackup;   /*!< Specifies the RTC Temper clear backup register. */
                                       
    uint32_t u32_FilterClk;     /*!< Specifies the RTC Temper Filter Clock select. */

    uint32_t u32_Filter;        /*!< Specifies the RTC Temper Filter select.*/
    
    uint32_t u32_FilterEn;      /*!< Specifies the RTC Temper Filter enable.*/
}RTC_TemperTypeDef;


/**
  * @brief  RTC Wakeup Timer structure definition
  */
typedef struct 
{
    uint32_t u32_WuckSel;          /*!< The RTC WUCKSEL Value to be configured. 
                                             This parameter can be a value of @ref WUCKSEL_1Hz */

    uint32_t u32_InterruptEN;      /*!< Specifies the RTC Temper interrupt enable.
                                       This parameter can be a value of @ref RTC_WUTIMER Interrupt */
    uint32_t WakeUpCounter;

}RTC_WUTimerTypeDef;

/**
  * @brief  RTC Temper index definition
  */
typedef enum
{
    RTC_TEMPER_1,
    RTC_TEMPER_2,
}RTC_Temper_t;

/** @defgroup RTC write enable command 
  * @{
  */
#define RTC_WRITE_PROTECT_DISABLE                   (0xCA53CA53)
#define RTC_WRITE_PROTECT_ENABLE                    (0x00000000)

/** @defgroup ClockSource
  * @{
  */
#define RTC_CLOCK_RC32K                             (0x00000000)
#define RTC_CLOCK_XTL                               (0x00000004)
#define IS_RTC_CLOCKSRC(__CLOCKSRC__)               (((__CLOCKSRC__) == RTC_CLOCK_RC32K) || \
                                                    ((__CLOCKSRC__) == RTC_CLOCK_XTL))

/** @defgroup Clock Compensation 
  * @{
  */
#define COMPENSATION_INCREASE                       (0x00000000)
#define COMPENSATION_DECREASE                       (0x00000200)
#define IS_RTC_COMPENSATION(__COMPENSATION__)       (((__COMPENSATION__) == COMPENSATION_INCREASE) || \
                                                    ((__COMPENSATION__) == COMPENSATION_DECREASE))

/** @defgroup Clock Compensation Value
  * @{
  */
#define IS_RTC_COMPENSATION_VALUE(__VALUE__)        ((__VALUE__) <= 0x1ff)   

/** @defgroup RTC Date Definitions 
  * @{
  */
#define RTC_MONTH_JANUARY                           (0x01)
#define RTC_MONTH_FEBRUARY                          (0x02)
#define RTC_MONTH_MARCH                             (0x03)
#define RTC_MONTH_APRIL                             (0x04)
#define RTC_MONTH_MAY                               (0x05)
#define RTC_MONTH_JUNE                              (0x06)
#define RTC_MONTH_JULY                              (0x07)
#define RTC_MONTH_AUGUST                            (0x08)
#define RTC_MONTH_SEPTEMBER                         (0x09)
#define RTC_MONTH_OCTOBER                           (0x10)
#define RTC_MONTH_NOVEMBER                          (0x11)
#define RTC_MONTH_DECEMBER                          (0x12)

#define RTC_WEEKDAY_MONDAY                          (0x01)
#define RTC_WEEKDAY_TUESDAY                         (0x02)
#define RTC_WEEKDAY_WEDNESDAY                       (0x03)
#define RTC_WEEKDAY_THURSDAY                        (0x04)
#define RTC_WEEKDAY_FRIDAY                          (0x05)
#define RTC_WEEKDAY_SATURDAY                        (0x06)
#define RTC_WEEKDAY_SUNDAY                          (0x07)

#define IS_RTC_YEAR(YEAR)                           (((YEAR) >= 0x00) && ((YEAR) <= 0x99))
#define IS_RTC_MONTH(MONTH)                         (((MONTH) > 0x00) && ((MONTH) <= 0x12))
#define IS_RTC_DAY(DAY)                             (((DAY) > 0x00) && ((DAY) <= 0x31))
#define IS_RTC_WEEKDAY(WEEKDAY)                     (((WEEKDAY) > 0x00) && ((WEEKDAY) <= 0x07))  


/** @defgroup RTC_AlarmInterrupt Definitions
  * @{
  */
#define RTC_ALARM_INT_ENABLE                        (0x00000000)
#define RTC_ALARM_INT_DISABLE                       (0x00000001)
#define IS_RTC_ALARM_INT(__INT__)                   (((__INT__) == RTC_ALARM_INT_ENABLE) || \
                                                    ((__INT__) == RTC_ALARM_INT_DISABLE))


/** @defgroup RTC_DayMask Definitions
  * @{
  */
#define RTC_ALARM_DAY_MASK_ENABLE                   RTC_CR_ALM_MSKD
#define RTC_ALARM_DAY_MASK_DISABLE                  (0x00000000)
#define IS_RTC_ALARM_DAY_MASK(__MASKD__)            (((__MASKD__) == RTC_ALARM_DAY_MASK_ENABLE) || \
                                                    ((__MASKD__) == RTC_ALARM_DAY_MASK_DISABLE))


/** @defgroup RTC_HourMask Definitions
  * @{
  */
#define RTC_ALARM_HOUR_MASK_ENABLE                  RTC_CR_ALM_MSKH
#define RTC_ALARM_HOUR_MASK_DISABLE                 (0x00000000)
#define IS_RTC_ALARM_HOUR_MASK(__MASKH__)           (((__MASKH__) == RTC_ALARM_HOUR_MASK_ENABLE) || \
                                                    ((__MASKH__) == RTC_ALARM_HOUR_MASK_DISABLE))

/** @defgroup RTC_MinMask Definitions
  * @{
  */
#define RTC_ALARM_MIN_MASK_ENABLE                   RTC_CR_ALM_MSKM
#define RTC_ALARM_MIN_MASK_DISABLE                  (0x00000000)
#define IS_RTC_ALARM_MIN_MASK(__MASKM__)            (((__MASKM__) == RTC_ALARM_MIN_MASK_ENABLE) || \
                                                    ((__MASKM__) == RTC_ALARM_MIN_MASK_DISABLE))
                                              
                                              
/** @defgroup RTC_Alarm_WeekSelect Definitions
  * @{
  */
#define RTC_ALARM_WEEK_SUNDAY                       (0x01000000)
#define RTC_ALARM_WEEK_MONDAY                       (0x02000000)
#define RTC_ALARM_WEEK_TUESDAY                      (0x04000000)
#define RTC_ALARM_WEEK_WEDNESDAY                    (0x08000000)
#define RTC_ALARM_WEEK_THURSDAY                     (0x10000000)
#define RTC_ALARM_WEEK_FRIDAY                       (0x20000000)
#define RTC_ALARM_WEEK_SATURDAY                     (0x40000000)
#define IS_RTC_ALARM_WEEKDAY(__WEEKDAY__)           (((__WEEKDAY__) == RTC_ALARM_WEEK_SUNDAY)    || \
                                                    ((__WEEKDAY__) == RTC_ALARM_WEEK_MONDAY)    || \
                                                    ((__WEEKDAY__) == RTC_ALARM_WEEK_TUESDAY)   || \
                                                    ((__WEEKDAY__) == RTC_ALARM_WEEK_WEDNESDAY) || \
                                                    ((__WEEKDAY__) == RTC_ALARM_WEEK_THURSDAY)  || \
                                                    ((__WEEKDAY__) == RTC_ALARM_WEEK_FRIDAY)    || \
                                                    ((__WEEKDAY__) == RTC_ALARM_WEEK_SATURDAY)  || \
                                                    ((__WEEKDAY__) >= 0x01000000 && (__WEEKDAY__) <= 0x7F000000))

/** @defgroup RTC_Temper_edge Definitions
  * @{
  */
#define RTC_TEMP_EDGE_RISING                        (0x00000000)
#define RTC_TEMP_EDGE_FALLING                       (0x00000001)
#define IS_RTC_TEMP_EDGE(__EDGE__)                  (((__EDGE__) == RTC_TEMP_EDGE_RISING) || \
                                                    ((__EDGE__) == RTC_TEMP_EDGE_FALLING))



/** @defgroup RTC_TemperInterrupt Definitions
  * @{
  */
#define RTC_TEMP_INT_DISABLE                        (0x00000000)
#define RTC_TEMP_INT_ENABLE                         (0x00000001)
#define IS_RTC_TEMP_INT(__INT__)                    (((__INT__) == RTC_TEMP_INT_ENABLE) || \
                                                    ((__INT__) == RTC_TEMP_INT_DISABLE))



/** @defgroup RTC_ClearBackup Definitions
  * @{
  */
#define RTC_TEMP_CLEAR_DISABLE                      (0x00000000)
#define RTC_TEMP_CLEAR_ENABLE                       (0x00000001)
#define IS_RTC_TEMP_CLEAR_BACKUP(__CLEAR__)         (((__CLEAR__) == RTC_TEMP_CLEAR_DISABLE) || \
                                                    ((__CLEAR__) == RTC_TEMP_CLEAR_ENABLE))



/** @defgroup RTC_TemperFilter Clock Definitions
  * @{
  */
#define RTC_TEMP_FILTER_RTCCLK                      (0x00000000)
#define RTC_TEMP_FILTER_512_RTCCLK                  (RTC_CR_TAMPFLTCLK)
#define IS_RTC_TEMP_FILTER_CLK(__CLK__)             (((__CLK__) == RTC_TEMP_FILTER_RTCCLK)   || \
                                                    ((__CLK__) == RTC_TEMP_FILTER_512_RTCCLK))
/** @defgroup RTC_TemperFilter Definitions
  * @{
  */
#define RTC_TEMP_FILTER_1_RTCCLK                    (0x00000000)
#define RTC_TEMP_FILTER_2_RTCCLK                    (0x00000001)
#define RTC_TEMP_FILTER_4_RTCCLK                    (0x00000002)
#define RTC_TEMP_FILTER_8_RTCCLK                    (0x00000003)
#define IS_RTC_TEMP_FILTER(__FILTER__)              (((__FILTER__) == RTC_TEMP_FILTER_1_RTCCLK)   || \
                                                    ((__FILTER__) == RTC_TEMP_FILTER_2_RTCCLK)    || \
                                                    ((__FILTER__) == RTC_TEMP_FILTER_4_RTCCLK)    || \
                                                    ((__FILTER__) == RTC_TEMP_FILTER_8_RTCCLK))
/** @defgroup Alarm clock week/day selection

  * @{
  */
#define RTC_ALM_ALM_WDS_DAY                         (0x80000000)     
#define RTC_ALM_ALM_WDS_WEEK                        (0x00000000)
#define IS_RTC_ALARM_MODE(__MODE__)                 (((__MODE__) == RTC_ALM_ALM_WDS_WEEK) ||\
                                                    ((__MODE__) == RTC_ALM_ALM_WDS_DAY))

/** @defgroup RTC Time Definitions 
  * @{
  */                                                 
#define IS_RTC_HOUR(HOUR)                           (((HOUR) >= 0) && ((HOUR) <= 0x23))
#define IS_RTC_MINUTES(MINUTES)                     (((MINUTES) >= 0) && ((MINUTES) <= 0x59))
#define IS_RTC_SECONDS(SECONDS)                     (((SECONDS) >= 0) && ((SECONDS) <= 0x59))  


/** @defgroup RTC_Backup_Registers_Definitions 
* @{
*/
#define RTC_BKP_DR0                                 (0)
#define RTC_BKP_DR1                                 (1)
#define RTC_BKP_DR2                                 (2)
#define RTC_BKP_DR3                                 (3)
#define RTC_BKP_DR4                                 (4)
#define RTC_BKP_DR5                                 (5)
#define RTC_BKP_DR6                                 (6)
#define RTC_BKP_DR7                                 (7)
#define RTC_BKP_DR8                                 (8)
#define RTC_BKP_DR9                                 (9)
#define RTC_BKP_DR10                                (10)
#define RTC_BKP_DR11                                (11)
#define RTC_BKP_DR12                                (12)
#define RTC_BKP_DR13                                (13)
#define RTC_BKP_DR14                                (14)
#define RTC_BKP_DR15                                (15)
#define IS_RTC_BKP(BKP)                             (((BKP) == RTC_BKP_DR0) || \
                                                    ((BKP) == RTC_BKP_DR1)  || \
                                                    ((BKP) == RTC_BKP_DR2)  || \
                                                    ((BKP) == RTC_BKP_DR3)  || \
                                                    ((BKP) == RTC_BKP_DR4)  || \
                                                    ((BKP) == RTC_BKP_DR5)  || \
                                                    ((BKP) == RTC_BKP_DR6)  || \
                                                    ((BKP) == RTC_BKP_DR7)  || \
                                                    ((BKP) == RTC_BKP_DR8)  || \
                                                    ((BKP) == RTC_BKP_DR9)  || \
                                                    ((BKP) == RTC_BKP_DR10) || \
                                                    ((BKP) == RTC_BKP_DR11) || \
                                                    ((BKP) == RTC_BKP_DR12) || \
                                                    ((BKP) == RTC_BKP_DR13) || \
                                                    ((BKP) == RTC_BKP_DR14) || \
                                                    ((BKP) == RTC_BKP_DR15))
                                                    
                                                    /** @defgroup RTC Wakeup Timer Definitions 
  * @{
  */ 
#define RTC_WAKEUPCLOCK_RTCCLK_DIV16                (0x00000000U)
#define RTC_WAKEUPCLOCK_RTCCLK_DIV8                 (0x01000000U)
#define RTC_WAKEUPCLOCK_RTCCLK_DIV4                 (0x02000000U)
#define RTC_WAKEUPCLOCK_RTCCLK_DIV2                 (0x03000000U)
#define RTC_WAKEUPCLOCK_1HZ                         (0x04000000U)
#define RTC_WAKEUPCLOCK_0_5HZ                       (0x05000000U)
#define RTC_WAKEUPCLOCK_2HZ                         (0x06000000U)
#define IS_RTC_WAKEUP_CLOCK(CLOCK)                  (((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV16) || \
                                                    ((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV8) || \
                                                    ((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV4) || \
                                                    ((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV2) || \
                                                    ((CLOCK) == RTC_WAKEUPCLOCK_1HZ) || \
                                                    ((CLOCK) == RTC_WAKEUPCLOCK_0_5HZ) || \
                                                    ((CLOCK) == RTC_WAKEUPCLOCK_2HZ))
#define IS_RTC_WAKEUP_COUNTER(COUNTER)              ((COUNTER) <= 0xFFFF)


/** @defgroup RTC Interrupts Definitions 
  * @{
  */ 
#define RTC_IT_FLAG_DATE                            (0x00000001UL)  
#define RTC_IT_FLAG_HOUR                            (0x00000002UL)  
#define RTC_IT_FLAG_MIN                             (0x00000004UL)  
#define RTC_IT_FLAG_SEC                             (0x00000008UL) 
#define RTC_IT_FLAG_2HZ                             (0x00000010UL) 
#define RTC_IT_FLAG_4HZ                             (0x00000020UL) 
#define RTC_IT_FLAG_8HZ                             (0x00000040UL)    
#define RTC_IT_FLAG_16HZ                            (0x00000080UL)  
#define RTC_IT_FLAG_64HZ                            (0x00000100UL)  
#define RTC_IT_FLAG_256HZ                           (0x00000200UL)  
#define RTC_IT_FLAG_1KHZ                            (0x00000400UL)  
#define RTC_IT_FLAG_ALM                             (0x00000800UL)  
#define RTC_IT_FLAG_32S                             (0x00001000UL)  
#define RTC_IT_FLAG_STP1F                           (0x00002000UL)  
#define RTC_IT_FLAG_STP1R                           (0x00004000UL)  
#define RTC_IT_FLAG_STP2F                           (0x00008000UL)  
#define RTC_IT_FLAG_STP2R                           (0x00010000UL)  
#define RTC_IT_FLAG_WUT                             (0x00020000UL)
#define IS_RTC_IT_FLAG(FLAG)                        (((FLAG) == RTC_IT_FLAG_DATE) || ((FLAG) == RTC_IT_FLAG_HOUR) || \
                                                    ((FLAG) == RTC_IT_FLAG_MIN)|| ((FLAG) == RTC_IT_FLAG_SEC) || \
                                                    ((FLAG) == RTC_IT_FLAG_2HZ)|| ((FLAG) == RTC_IT_FLAG_4HZ) || \
                                                    ((FLAG) == RTC_IT_FLAG_8HZ)|| ((FLAG) == RTC_IT_FLAG_16HZ) || \
                                                    ((FLAG) == RTC_IT_FLAG_64HZ)|| ((FLAG) == RTC_IT_FLAG_256HZ) || \
                                                    ((FLAG) == RTC_IT_FLAG_1KHZ)|| ((FLAG) == RTC_IT_FLAG_ALM) || \
                                                    ((FLAG) == RTC_IT_FLAG_32S)|| ((FLAG) == RTC_IT_FLAG_STP1F) || \
                                                    ((FLAG) == RTC_IT_FLAG_STP1R)|| ((FLAG) == RTC_IT_FLAG_STP2F) || \
                                                    ((FLAG) == RTC_IT_FLAG_STP2R)|| ((FLAG) == RTC_IT_FLAG_WUT))   
/**
  * @}
  */ 

                                         

/* RTC stamp1 interrupt enable、disable */
#define __HAL_RTC_ENABLE_STAMP1_IT                  (RTC->IE |= (RTC_IE_STP1RIE | RTC_IE_STP1FIE))
#define __HAL_RTC_DISABLE_STAMP1_IT                 (RTC->IE &= ~(RTC_IE_STP1RIE | RTC_IE_STP1FIE))

/* RTC stamp2 interrupt enable、disable */
#define __HAL_RTC_ENABLE_STAMP2_IT                  (RTC->IE |= (RTC_IE_STP2RIE | RTC_IE_STP2FIE))
#define __HAL_RTC_DISABLE_STAMP2_IT                 (RTC->IE &= ~(RTC_IE_STP2RIE | RTC_IE_STP2FIE))

/* RTC 32S interrupt enable、disable */
#define __HAL_RTC_ENABLE_32S_IT                     (RTC->IE |= RTC_IE_ADJ32_IE)
#define __HAL_RTC_DISABLE_32S_IT                    (RTC->IE &= ~RTC_IE_ADJ32_IE)

/* RTC alarm interrupt enable、disable */
#define __HAL_RTC_ENABLE_ALM_IT                     (RTC->IE |= RTC_IE_ALM_IE)
#define __HAL_RTC_DISABLE_ALM_IT                    (RTC->IE &= RTC_IE_ALM_IE)

/* RTC sec interrupt enable、disable */
#define __HAL_RTC_ENABLE_SEC_IT                     (RTC->IE |= RTC_IE_SEC_IE)
#define __HAL_RTC_DISABLE_SEC_IT                    (RTC->IE &= ~RTC_IE_SEC_IE)

/* RTC Minute interrupt enable、disable */
#define __HAL_RTC_ENABLE_MIN_IT                     (RTC->IE |= RTC_IE_MIN_IE)
#define __HAL_RTC_DISABLE_MIN_IT                    (RTC->IE &= ~RTC_IE_MIN_IE)

/* RTC Hour interrupt enable、disable */
#define __HAL_RTC_ENABLE_HOUR_IT                    (RTC->IE |= RTC_IE_HOUR_IE)
#define __HAL_RTC_DISABLE_HOUR_IT                   (RTC->IE &= ~RTC_IE_HOUR_IE)

/* RTC Date interrupt enable、disable */
#define __HAL_RTC_ENABLE_DATE_IT                    (RTC->IE |= RTC_IE_DATE_IE)
#define __HAL_RTC_DISABLE_DATE_IT                   (RTC->IE &= ~RTC_IE_DATE_IE)

/* RTC Timer Wakeup interrupt enable、disable */
#define __HAL_RTC_ENABLE_WUTIE_IT                   (RTC->IE |= RTC_IE_WUTIE)
#define __HAL_RTC_DISABLE_WUTIE_IT                  (RTC->IE &= ~RTC_IE_WUTIE)


HAL_StatusTypeDef HAL_RTC_Config(RTC_ConfigTypeDef *hrtc);

void HAL_RTC_SetTime(RTC_TimeTypeDef *fp_Time);

void HAL_RTC_GetTime(RTC_TimeTypeDef *fp_Time);

void HAL_RTC_SetDate(RTC_DateTypeDef *fp_Date);

void HAL_RTC_GetDate(RTC_DateTypeDef *fp_Date);

void HAL_RTC_AlarmConfig(RTC_AlarmTypeDef *fp_Alarm);

void HAL_RTC_AlarmEnable(void);

void HAL_RTC_AlarmDisable(void);

void HAL_RTC_Tamper(RTC_Temper_t fe_Temper, RTC_TemperTypeDef *fp_Temper);

void HAL_RTC_TamperEnable(RTC_Temper_t fe_Temper);

void HAL_RTC_TamperDisable(RTC_Temper_t fe_Temper);

void HAL_RTC_SetWakeUpTimer(RTC_WUTimerTypeDef *hrtc);

void HAL_RTC_WriteBackupRegister(uint32_t RTC_BKP_DR, uint32_t Data);

uint32_t HAL_RTC_ReadBackupRegister(uint32_t RTC_BKP_DR);

void HAL_RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState);

FlagStatus HAL_RTC_GetFlagStatus(uint32_t RTC_FLAG);

void HAL_RTC_ClearFlag(uint32_t RTC_FLAG);

ITStatus HAL_RTC_GetITStatus(uint32_t RTC_IT);

void HAL_RTC_ClearITPendingBit(uint32_t RTC_IT);

#endif
