/******************************************************************************
*@file  : hal_rcc.h
*@brief : Header file of RCC HAL module.
******************************************************************************/

#ifndef __HAL_RCC_H__
#define __HAL_RCC_H__

#include "acm32h5xx_hal_conf.h"
    

/**
  * @brief  RCC PLL configuration structure definition
  */
typedef struct
{
    uint32_t    PLL;            /*!< The new state of the PLL.
                                     This parameter can be a value of @ref FunctionalState                      */

    uint32_t    Source;         /*!< RCC_PLLSource: PLL entry clock source.
                                     This parameter must be a value of @ref RCC_PLL_Source                      */

    uint32_t    PLLQCLK;
    
    uint32_t    PLLPCLK;
    
    uint32_t    PLLQ;           /*!< PLLM: Output frequency division control field.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 15     */

    uint32_t    PLLP;           /*!< PLLN: the frequency division factor of the reference frequency.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 3      */                        

    uint32_t    PLLN;           /*!< PLLP:  the frequency multiplication factor of the reference frequency..
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 63     */                       

    uint32_t    PLLF;           /*!< PLLP:  the frequency multiplication factor of the reference frequency..
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 511    */

    uint32_t    SSC;
    
    uint32_t    SSCMode;
    
    uint32_t    SSCSpectrum;
    
    uint32_t    SSCStep;
    

}RCC_PLLInitTypeDef;

/**
  * @brief  RCC Internal/External Oscillator (RCH, RCL, XTH, and XTL) or PLL 
  *         configuration structure definition
  */

typedef struct
{
    uint32_t    OscType;            /*!< The oscillators or PLL to be configured.
                                         This parameter can be a value of @ref RCC_Oscillator_Type      */
    
    uint32_t    RCH;              /*!< The new state of the RCH.
                                         This parameter can be a value of @ref FunctionalState          */
    
    uint32_t    RCHDiv16;         /*!< If the system clock is RCH, the system clock will change 
                                     to 1/16 of the original after this position is ENABLE.
                                         This parameter can be a value of @ref FunctionalState          */
    
    uint32_t    RCL;              /*!< The new state of the RCL.
                                         This parameter can be a value of @ref FunctionalState          */
    
    uint32_t    XTH;                /*!< The new state of the XTH.
                                         This parameter can be a value of @ref FunctionalState          */
    
    uint32_t    XTHBypass;          /*!< XTH oscillator bypass
                                         This parameter can be a value of @ref FunctionalState          */
    
    uint32_t    XTL;                /*!< The new state of the XTL.
                                         This parameter can be a value of @ref FunctionalState          */
    
    uint32_t    XTLBypass;          /*!< XTL oscillator bypass
                                         This parameter can be a value of @ref FunctionalState          */
    
    RCC_PLLInitTypeDef  PLL1;       /*!< PLL1 structure parameters                                     */
    
    RCC_PLLInitTypeDef  PLL2;       /*!< PLL2 structure parameters                                     */
    
    RCC_PLLInitTypeDef  PLL3;       /*!< PLL3 structure parameters                                     */
    
}RCC_OscInitTypeDef;


/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
    uint32_t    ClockType;      /*!< The system clock source.
                                     This parameter can be a value of @ref RCC_Clock_Type        */

    uint32_t    SYSCLKSource;   /*!< The system clock source.
                                     This parameter can be a value of @ref RCC_Sysclk_Source        */

    uint32_t    SYSCLKDiv0;     /*!< First level frequency division of system clock.
                                     This parameter can be a value of @ref RCC_Sysclk_DIV0          */

    uint32_t    SYSCLKDiv1;     /*!< Second level frequency division of system clock.
                                     This parameter can be a value of @ref RCC_Sysclk_DIV1          */

    uint32_t    PCLK1Div;       /*!< PCLK1 (the APB1 clock) divider.
                                     This parameter can be a value of @ref RCC_PCLK1_DIV            */
    
    uint32_t    PCLK2Div;       /*!< PCLK2 (the APB2 clock) divider.
                                     This parameter can be a value of @ref RCC_PCLK2_DIV            */
    
    uint32_t    PCLK3Div;       /*!< PCLK2 (the APB2 clock) divider.
                                     This parameter can be a value of @ref RCC_PCLK2_DIV            */
    
    uint32_t    PCLK4Div;       /*!< PCLK2 (the APB2 clock) divider.
                                     This parameter can be a value of @ref RCC_PCLK2_DIV            */
    
}RCC_ClkInitTypeDef;

/**
  * @brief  RCC MCO configuration structure definition
  */

typedef struct
{
    uint32_t    MCO;                /*!< MCO output select.
                                         This parameter can be a value of @ref RCC_MCO_Output                       */
    
    uint32_t    MCO1;             /*!< The new state of the MCO1.
                                         This parameter can be a value of @ref FunctionalState                      */
    
    uint32_t    MCO1Div;          /*!< MCO11 clock divider.
                                         This parameter must be a number between Min_Data = 0 and Max_Data = 65535  */
    
    uint32_t    MCO1RevPol;       /*!< The new state of the MCO1 clock reverse polarity.
                                         This parameter can be a value of @ref FunctionalState                      */
    
    uint32_t    MCO2;            /*!< The new state of the MCO1.
                                         This parameter can be a value of @ref FunctionalState                      */
    
    uint32_t    MCO2Div;         /*!< MCO11 clock divider.
                                         This parameter must be a number between Min_Data = 0 and Max_Data = 65535  */
    
    uint32_t    MCO2RevPol;      /*!< The new state of the MCO1 clock reverse polarity.
                                         This parameter can be a value of @ref FunctionalState                      */
    
}RCC_MCOInitTypeDef;


/** @defgroup RCC_Oscillator_Type
  * @{
  */

#define RCC_OSC_TYPE_RCH                        ( 0x01U )
#define RCC_OSC_TYPE_RCL                        ( 0x02U )
#define RCC_OSC_TYPE_XTH                        ( 0x04U )
#define RCC_OSC_TYPE_XTL                        ( 0x08U )
#define RCC_OSC_TYPE_PLL1                       ( 0x10U )
#define RCC_OSC_TYPE_PLL2                       ( 0x20U )
#define RCC_OSC_TYPE_PLL3                       ( 0x40U )

/**
  * @}
  */
  
/** @brief  Oscillator type mask for assert test
  * @{
  */

#define RCC_OSC_TYPE_MASK                       ( RCC_OSC_TYPE_RCH | RCC_OSC_TYPE_RCL | RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_XTL | \
                                                  RCC_OSC_TYPE_PLL1 | RCC_OSC_TYPE_PLL2 | RCC_OSC_TYPE_PLL3 )

/**
  * @}
  */
  
/** @defgroup 
  * @{
  */

#define RCC_IT_RCL_READY                        ( BIT0 )
#define RCC_IT_XTL_READY                        ( BIT1 )
#define RCC_IT_RCH_READY                        ( BIT2 )
#define RCC_IT_XTH_READY                        ( BIT3 )
#define RCC_IT_PLL1_READY                       ( BIT4 )
#define RCC_IT_PLL2_READY                       ( BIT5 )
#define RCC_IT_PLL3_READY                       ( BIT6 )
#define RCC_IT_XTH_STOP                         ( BIT27 )
#define RCC_IT_XTL_STOP                         ( BIT31 )
/**
  * @}
  */
  
#define RCC_IT_MASK                             ( RCC_IT_RCL_READY | RCC_IT_XTL_READY | RCC_IT_RCH_READY | \
                                                  RCC_IT_XTH_READY | RCC_IT_PLL1_READY | RCC_IT_PLL2_READY | \
                                                  RCC_IT_PLL3_READY | RCC_IT_XTH_STOP | RCC_IT_XTL_STOP )
#define RCC_IT_READY_MASK                       ( RCC_IT_RCL_READY | RCC_IT_XTL_READY | RCC_IT_RCH_READY | RCC_IT_XTH_READY | \
                                                  RCC_IT_PLL1_READY | RCC_IT_PLL2_READY | RCC_IT_PLL3_READY )
#define RCC_IT_STOP_MASK                        ( RCC_IT_XTH_STOP | RCC_IT_XTL_STOP )

#define RCC_IT_CLEAR_FLAG_MASK                  ( (RCC_IT_READY_MASK << 16) | (RCC_IT_STOP_MASK >> 2) )

/** @defgroup 
  * @{
  */

#define RCC_FLAG_RCL_RDY                        ( BIT0 )
#define RCC_FLAG_XTL_RDY                        ( BIT1 )
#define RCC_FLAG_RCH_RDY                        ( BIT2 )
#define RCC_FLAG_XTH_RDY                        ( BIT3 )
#define RCC_FLAG_PLL1_RDY                       ( BIT4 )
#define RCC_FLAG_PLL2_RDY                       ( BIT5 )
#define RCC_FLAG_PLL3_RDY                       ( BIT6 )
#define RCC_FLAG_XTH_STOP                       ( BIT27 )
#define RCC_FLAG_XTL_STOP                       ( BIT31 )
/**
  * @}
  */
  
#define RCC_FLAG_MASK                           ( RCC_FLAG_RCL_RDY | RCC_FLAG_XTL_RDY | RCC_FLAG_RCH_RDY | \
                                                  RCC_FLAG_XTH_RDY | RCC_FLAG_PLL1_RDY | RCC_FLAG_PLL2_RDY | \
                                                  RCC_FLAG_PLL3_RDY | RCC_FLAG_XTH_STOP | RCC_FLAG_XTL_STOP )

/** @defgroup RCC_XTL_Drive_Capacity
  * @{
  */

#define RCC_XTL_DRIVE_NORMAL_LEVEL0             ( 0U )
#define RCC_XTL_DRIVE_NORMAL_LEVEL1             ( 1U )
#define RCC_XTL_DRIVE_NORMAL_LEVEL2             ( 2U )
#define RCC_XTL_DRIVE_NORMAL_LEVEL3             ( 3U )
#define RCC_XTL_DRIVE_LOWPOWER_LEVEL0           ( 4U )
#define RCC_XTL_DRIVE_LOWPOWER_LEVEL1           ( 5U )
#define RCC_XTL_DRIVE_LOWPOWER_LEVEL2           ( 6U )
#define RCC_XTL_DRIVE_LOWPOWER_LEVEL3           ( 7U )
#define RCC_XTL_DRIVE_MAX                       ( 8U )

/**
  * @}
  */
  
/** @defgroup RCC_PLL_Source
  * @{
  */

#define RCC_PLL_SOURCE_RCH_DIV16                ( 0U )
#define RCC_PLL_SOURCE_XTH                      ( 1U )
#define RCC_PLL_SOURCE_MAX                      ( 2U )

#define RCC_PLL_SSC_MODE_CENTER                 ( 0 )
#define RCC_PLL_SSC_MODE_DOWN                   ( RCC_PLL1SCR_PLL1SSCMD )

/** @defgroup RCC_Clock_Type
  * @{
  */

#define RCC_CLOCK_TYPE_SYSCLK                   ( 0x01U )
#define RCC_CLOCK_TYPE_SYSDIV0                  ( 0x02U )
#define RCC_CLOCK_TYPE_SYSDIV1                  ( 0x04U )
#define RCC_CLOCK_TYPE_PCLK1                    ( 0x08U )
#define RCC_CLOCK_TYPE_PCLK2                    ( 0x10U )
#define RCC_CLOCK_TYPE_PCLK3                    ( 0x20U )
#define RCC_CLOCK_TYPE_PCLK4                    ( 0x40U )

/**
  * @}
  */
/** @brief  System Clock type mask for assert test
  * @{
  */

#define RCC_CLOCK_TYPE_MASK                     ( RCC_CLOCK_TYPE_SYSCLK | RCC_CLOCK_TYPE_SYSDIV0 | RCC_CLOCK_TYPE_SYSDIV1 | \
                                                  RCC_CLOCK_TYPE_PCLK1 | RCC_CLOCK_TYPE_PCLK2 | RCC_CLOCK_TYPE_PCLK3 | RCC_CLOCK_TYPE_PCLK4)

/**
  * @}
  */
  
/** @defgroup RCC_Sysclk_Source
  * @{
  */

#define RCC_SYSCLK_SOURCE_RCH                   ( 0U )
#define RCC_SYSCLK_SOURCE_XTH                   ( 1U )
#define RCC_SYSCLK_SOURCE_PLL1PCLK              ( 2U )
#define RCC_SYSCLK_SOURCE_MAX                   ( 3U )

/**
  * @}
  */
  

/** @defgroup RCC_FLT_CLK_Source
  * @{
  */

#define RCC_FLT_CLK_SOURCE_PCLK1_DIV32          ( 0U )
#define RCC_FLT_CLK_SOURCE_RCL                  ( 1U )
#define RCC_FLT_CLK_SOURCE_MAX                  ( 2U )

/**
  * @}
  */
  
/** @defgroup RCC_LPUART1_CLK_Source
  * @{
  */

#define RCC_LPUART1_CLK_SOURCE_RCL              ( 0U )
#define RCC_LPUART1_CLK_SOURCE_XTL              ( 1U )
#define RCC_LPUART1_CLK_SOURCE_PCLK1_DIV4       ( 2U )
#define RCC_LPUART1_CLK_SOURCE_PCLK1_DIV8       ( 3U )
#define RCC_LPUART1_CLK_SOURCE_PCLK1_DIV16      ( 4U )
#define RCC_LPUART1_CLK_SOURCE_PCLK1_DIV32      ( 5U )
#define RCC_LPUART1_CLK_SOURCE_MAX              ( 6U )

/**
  * @}
  */

/** @defgroup RCC_LPTIM1_CLK_Source
  * @{
  */

#define RCC_LPTIM1_CLK_SOURCE_PCLK1             ( 0U )
#define RCC_LPTIM1_CLK_SOURCE_RCL               ( 1U )
#define RCC_LPTIM1_CLK_SOURCE_RCH               ( 2U )
#define RCC_LPTIM1_CLK_SOURCE_XTL               ( 3U )
#define RCC_LPTIM1_CLK_SOURCE_MAX               ( 4U )

/**
  * @}
  */

/** @defgroup RCC_LPTIM2_CLK_Source
  * @{
  */

#define RCC_LPTIM2_CLK_SOURCE_PCLK1             ( 0U )
#define RCC_LPTIM2_CLK_SOURCE_RCL               ( 1U )
#define RCC_LPTIM2_CLK_SOURCE_RCH               ( 2U )
#define RCC_LPTIM2_CLK_SOURCE_XTL               ( 3U )
#define RCC_LPTIM2_CLK_SOURCE_MAX               ( 4U )

/**
  * @}
  */

/** @defgroup RCC_LPTIM3_CLK_Source
  * @{
  */

#define RCC_LPTIM3_CLK_SOURCE_PCLK3             ( 0U )
#define RCC_LPTIM3_CLK_SOURCE_RCL               ( 1U )
#define RCC_LPTIM3_CLK_SOURCE_RCH               ( 2U )
#define RCC_LPTIM3_CLK_SOURCE_XTL               ( 3U )
#define RCC_LPTIM3_CLK_SOURCE_MAX               ( 4U )

/**
  * @}
  */

/** @defgroup RCC_LPTIM345_CLK_Source
  * @{
  */

#define RCC_LPTIM4_CLK_SOURCE_PCLK3             ( 0U )
#define RCC_LPTIM4_CLK_SOURCE_RCL               ( 1U )
#define RCC_LPTIM4_CLK_SOURCE_RCH               ( 2U )
#define RCC_LPTIM4_CLK_SOURCE_XTL               ( 3U )
#define RCC_LPTIM4_CLK_SOURCE_MAX               ( 4U )

/**
  * @}
  */

/** @defgroup RCC_LPTIM345_CLK_Source
  * @{
  */

#define RCC_LPTIM5_CLK_SOURCE_PCLK3             ( 0U )
#define RCC_LPTIM5_CLK_SOURCE_RCL               ( 1U )
#define RCC_LPTIM5_CLK_SOURCE_RCH               ( 2U )
#define RCC_LPTIM5_CLK_SOURCE_XTL               ( 3U )
#define RCC_LPTIM5_CLK_SOURCE_MAX               ( 4U )

/**
  * @}
  */

/** @defgroup RCC_LPTIM6_CLK_Source
  * @{
  */

#define RCC_LPTIM6_CLK_SOURCE_PCLK3             ( 0U )
#define RCC_LPTIM6_CLK_SOURCE_RCL               ( 1U )
#define RCC_LPTIM6_CLK_SOURCE_RCH               ( 2U )
#define RCC_LPTIM6_CLK_SOURCE_XTL               ( 3U )
#define RCC_LPTIM6_CLK_SOURCE_MAX               ( 4U )

/**
  * @}
  */

/** @defgroup RCC_SDMMC_CLK_Source
  * @{
  */

#define RCC_SDMMC_CLK_SOURCE_SYSCLK             ( 0U )
#define RCC_SDMMC_CLK_SOURCE_PLL2PCLK           ( 1U )
#define RCC_SDMMC_CLK_SOURCE_MAX                ( 2U )

/**
  * @}
  */

/** @defgroup RCC_SDMMC_SCLK_Source
  * @{
  */

#define RCC_SDMMC_SCLK_SOURCE_SDMMC_CLK_DELAY       ( 0U )
#define RCC_SDMMC_SCLK_SOURCE_SDMMC1_CKIN           ( 1U )
#define RCC_SDMMC_SCLK_SOURCE_SDMMC2_CKIN           ( 2U )
#define RCC_SDMMC_SCLK_SOURCE_SDMMC_CLK_NO_DELAY    ( 3U )
#define RCC_SDMMC_SCLK_SOURCE_MAX                   ( 4U )

/**
  * @}
  */

/** @defgroup RCC_RTC_CLK_Source
  * @{
  */

#define RCC_RTC_CLK_SOURCE_RCL                  ( 0U )
#define RCC_RTC_CLK_SOURCE_XTL                  ( 1U )
#define RCC_RTC_CLK_SOURCE_MAX                  ( 2U )

/**
  * @}
  */

/** @defgroup RCC_MCO_Output
  * @{
  */

#define RCC_MCO_HCLK                            ( 0U )
#define RCC_MCO_RCH                             ( 1U )
#define RCC_MCO_RCL                             ( 2U )
#define RCC_MCO_XTH                             ( 3U )
#define RCC_MCO_XTL                             ( 4U )
#define RCC_MCO_PLL1PCLK                        ( 5U )
#define RCC_MCO_PLL2PCLK                        ( 6U )
#define RCC_MCO_PLL2QCLK                        ( 7U )
#define RCC_MCO_PLL3PCLK                        ( 8U )
#define RCC_MCO_PLL3QCLK                        ( 9U )
#define RCC_MCO_SYSCLK                          ( 10U )
#define RCC_MCO_LPUART1_CLK                     ( 11U )
#define RCC_MCO_FCLK_DIV8                       ( 12U )
#define RCC_MCO_USB1_48M                        ( 13U )
#define RCC_MCO_USB2_48M                        ( 14U )
#define RCC_MCO_RTC_PCLK                        ( 15U )
#define RCC_MCO_SDMMC_SAMPLE_CLK                ( 16U )
#define RCC_MCO_SDMMC_DRIVE_CLK                 ( 17U )
#define RCC_MCO_MAX                             ( 18U )

/**
  * @}
  */

/** @defgroup  RCC_Reset_Source RCC Reset Source
  * @{
  */

#define RCC_RESET_SOURCE_PWR                    ( RCC_RSR_PWRRSTF )
#define RCC_RESET_SOURCE_POR12                  ( RCC_RSR_POR12RSTF )
#define RCC_RESET_SOURCE_SRST                   ( RCC_RSR_SRSTF )
#define RCC_RESET_SOURCE_RSTN                   ( RCC_RSR_RSTNF )
#define RCC_RESET_SOURCE_SYSREQ                 ( RCC_RSR_SYSREQRSTF )
#define RCC_RESET_SOURCE_LOCKUP                 ( RCC_RSR_LOCKUPRSTF )
#define RCC_RESET_SOURCE_IWDT                   ( RCC_RSR_IWDTRSTF )
#define RCC_RESET_SOURCE_WDT                    ( RCC_RSR_WDTRSTF )
#define RCC_RESET_SOURCE_LVD                    ( RCC_RSR_LVDRSTF )

/**
  * @}
  */
  
/** @defgroup  RCC_Reset_Source RCC Reset Source
  * @{
  */

#define RCC_RESET_SOURCE_MASK                   ( RCC_RESET_SOURCE_PWR | RCC_RESET_SOURCE_POR12 | RCC_RESET_SOURCE_SRST | \
                                                  RCC_RESET_SOURCE_RSTN | RCC_RESET_SOURCE_SYSREQ | RCC_RESET_SOURCE_LOCKUP | \
                                                  RCC_RESET_SOURCE_IWDT | RCC_RESET_SOURCE_WDT | RCC_RESET_SOURCE_LVD)

/**
  * @}
  */
#define __HAL_RCC_RTC_ENABLE()                  ( RCC->STDBYCTRL |= RCC_STDBYCTRL_RTCEN )
#define __HAL_RCC_RTC_DISABLE()                 ( RCC->STDBYCTRL &= ~RCC_STDBYCTRL_RTCEN )

#define __HAL_RCC_XTH_STOP_ENABLE()             ( RCC->XTHCR |= RCC_XTHCR_XTHSDEN )
#define __HAL_RCC_XTH_STOP_DISABLE()            ( RCC->XTHCR &= ~RCC_XTHCR_XTHSDEN )

#define __HAL_RCC_XTL_STOP_ENABLE()             ( RCC->STDBYCTRL |= RCC_STDBYCTRL_XTLSDEN )
#define __HAL_RCC_XTL_STOP_DISABLE()            ( RCC->STDBYCTRL &= ~RCC_STDBYCTRL_XTLSDEN )

#define RCC_RCH_READY_TIMEOUT                   ( 0xFFFFU )
#define RCC_RCH_UNREADY_TIMEOUT                 ( 0xFFFFU )
#define RCC_RCHP_READY_TIMEOUT                  ( 0xFFFFU )
#define RCC_RCHP_UNREADY_TIMEOUT                ( 0xFFFFU )
#define RCC_RCL_READY_TIMEOUT                   ( 0xFFFFU )
#define RCC_RCL_UNREADY_TIMEOUT                 ( 0xFFFFU )
#define RCC_XTH_READY_TIMEOUT                   ( 0xFFFFFU )
#define RCC_XTH_UNREADY_TIMEOUT                 ( 0xFFFFFU )
#define RCC_XTL_READY_TIMEOUT                   ( 0xFFFFFU )
#define RCC_XTL_UNREADY_TIMEOUT                 ( 0xFFFFU )
#define RCC_PLL1_READY_TIMEOUT                  ( 0xFFFFU )
#define RCC_PLL2_READY_TIMEOUT                  ( 0xFFFFU )
#define RCC_PLL3_READY_TIMEOUT                  ( 0xFFFFU )



#define __HAL_RCC_FDCAN2_RESET()                do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_FDCAN2RST;  \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_FDCAN2RST;   \
                                                }while (0)
                                                
#define __HAL_RCC_FDCAN1_RESET()                do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_FDCAN1RST;  \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_FDCAN1RST;   \
                                                }while (0)
                                                
#define __HAL_RCC_USB2_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_USB2CRST;  \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_USB2CRST;   \
                                                }while (0)
                                                
#define __HAL_RCC_USB1_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_USB1CRST;   \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_USB1CRST;    \
                                                }while (0)
                                                
#define __HAL_RCC_SPI6_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_SPI6RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_SPI6RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_SPI5_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_SPI5RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_SPI5RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_SPI4_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_SPI4RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_SPI4RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_SPI3_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_SPI3RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_SPI3RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_SPI2_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_SPI2RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_SPI2RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_SPI1_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_SPI1RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_SPI1RST;      \
                                                }while (0)
                                                
                                                
#define __HAL_RCC_DMA2D_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_DMA2DRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_DMA2DRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_ETH_RESET()                   do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_ETHRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_ETHRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_CRC_RESET()                   do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_CRCRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_CRCRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_DMA2_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_DMA2RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_DMA2RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_DMA1_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB1RSTR &= ~RCC_AHB1RSTR_DMA1RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB1RSTR |= RCC_AHB1RSTR_DMA1RST;      \
                                                }while (0)
                                                
/** @brief  the AHB2 peripheral reset.
  */
                   
#define __HAL_RCC_THM_RESET()                   do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_THMRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_THMRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_FDCAN3_RESET()                do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_FDCAN3RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_FDCAN3RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_UAC_RESET()                   do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_UACRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_UACRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_DCMI_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_DCMIRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_DCMIRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_DAC2_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_DAC2RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_DAC2RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_DAC1_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_DAC1RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_DAC1RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_ADC3_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_ADC3RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_ADC3RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_ADC12_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_ADC12RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_ADC12RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOQ_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOQRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOQRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOP_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOPRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOPRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOO_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOORST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOORST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPION_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIONRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIONRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOM_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOMRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOMRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOL_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOLRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOLRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOK_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOKRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOKRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOJ_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOJRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOJRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOI_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOIRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOIRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOH_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOHRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOHRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOG_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOGRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOGRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOF_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOFRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOFRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOE_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOERST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOERST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOD_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIODRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIODRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOC_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOCRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOCRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOB_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOBRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOBRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_GPIOA_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOARST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOARST;      \
                                                }while (0)
             
/** @brief  the AHB3 peripheral reset.
  */
              
#define __HAL_RCC_FMC_RESET()                   do                                              \
                                                {                                               \
                                                    RCC->AHB3RSTR &= ~RCC_AHB3RSTR_FMCRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB3RSTR |= RCC_AHB3RSTR_FMCRST;      \
                                                }while (0)
                                                
#define __HAL_RCC_OSPI2_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB3RSTR &= ~RCC_AHB3RSTR_OSPI2RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB3RSTR |= RCC_AHB3RSTR_OSPI2RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_OSPI1_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->AHB3RSTR &= ~RCC_AHB3RSTR_OSPI1RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB3RSTR |= RCC_AHB3RSTR_OSPI1RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_SDIO_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB3RSTR &= ~RCC_AHB3RSTR_SDIORST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB3RSTR |= RCC_AHB3RSTR_SDIORST;      \
                                                }while (0)

#define __HAL_RCC_SPI8_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB3RSTR &= ~RCC_AHB3RSTR_SPI8RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB3RSTR |= RCC_AHB3RSTR_SPI8RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_SPI7_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->AHB3RSTR &= ~RCC_AHB3RSTR_SPI7RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->AHB3RSTR |= RCC_AHB3RSTR_SPI7RST;      \
                                                }while (0)
                                                
/** @brief  the APB1 peripheral reset.
  */
                        
#define __HAL_RCC_LPUART1_RESET()               do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_LPUART1RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_LPUART1RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_LPTIM1_RESET()                do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_LPTIM1RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_LPTIM1RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_PMU_RESET()                   do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_PMURST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_PMURST;       \
                                                }while (0)
                                                
#define __HAL_RCC_I2C4_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2C4RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2C4RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_I2C3_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2C3RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2C3RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_I2C2_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2C2RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2C2RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_I2C1_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2C1RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2C1RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_USART5_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_USART5RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_USART5RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_USART4_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_USART4RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_USART4RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_USART3_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_USART3RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_USART3RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_USART2_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_USART2RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_USART2RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_I2S3_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2S3RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2S3RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_I2S2_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2S2RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2S2RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_I2S1_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2S1RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2S1RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_WDT_RESET()                   do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_WDTRST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_WDTRST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM14_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM14RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM14RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM13_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM13RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM13RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM12_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM12RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM12RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM7_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM7RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM7RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM6_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM6RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM6RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM5_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM5RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM5RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM4_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM4RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM4RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM3_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM3RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM3RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM2_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_TIM2RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR1 |= RCC_APB1RSTR1_TIM2RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_EFUSE2_RESET()                do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR2 &= ~RCC_APB1RSTR2_EFUSE2RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR2 |= RCC_APB1RSTR2_EFUSE2RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_EFUSE1_RESET()                do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR2 &= ~RCC_APB1RSTR2_EFUSE1RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR2 |= RCC_APB1RSTR2_EFUSE1RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM26_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR2 &= ~RCC_APB1RSTR2_TIM26RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR2 |= RCC_APB1RSTR2_TIM26RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_TIM25_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR2 &= ~RCC_APB1RSTR2_TIM25RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR2 |= RCC_APB1RSTR2_TIM25RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_USART8_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR2 &= ~RCC_APB1RSTR2_USART8RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR2 |= RCC_APB1RSTR2_USART8RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_USART7_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR2 &= ~RCC_APB1RSTR2_USART7RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR2 |= RCC_APB1RSTR2_USART7RST;       \
                                                }while (0)
                                                
#define __HAL_RCC_LPTIM2_RESET()                do                                              \
                                                {                                               \
                                                    RCC->APB1RSTR2 &= ~RCC_APB1RSTR2_LPTIM2RST;      \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB1RSTR2 |= RCC_APB1RSTR2_LPTIM2RST;       \
                                                }while (0)

/** @brief  the APB2 peripheral reset.
  */

#define __HAL_RCC_USART10_RESET()                do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART10RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_USART10RST;      \
                                                }while (0)

#define __HAL_RCC_USART9_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART9RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_USART9RST;      \
                                                }while (0)

#define __HAL_RCC_TIM24_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM24RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM24RST;      \
                                                }while (0)

#define __HAL_RCC_TIM23_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM23RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM23RST;      \
                                                }while (0)

#define __HAL_RCC_TIM22_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM22RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM22RST;      \
                                                }while (0)

#define __HAL_RCC_TIM21_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM21RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM21RST;      \
                                                }while (0)

#define __HAL_RCC_TIM19_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM19RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM19RST;      \
                                                }while (0)

#define __HAL_RCC_TIM18_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM18RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM18RST;      \
                                                }while (0)

#define __HAL_RCC_TIM11_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM11RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM11RST;      \
                                                }while (0)

#define __HAL_RCC_TIM10_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM10RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM10RST;      \
                                                }while (0)

#define __HAL_RCC_TIM9_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM9RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM9RST;      \
                                                }while (0)

#define __HAL_RCC_LTDC_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_LTDCRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_LTDCRST;      \
                                                }while (0)

#define __HAL_RCC_TKEY_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TKEYRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TKEYRST;      \
                                                }while (0)

#define __HAL_RCC_TIM20_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM20RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM20RST;      \
                                                }while (0)

#define __HAL_RCC_TIM17_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM17RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM17RST;      \
                                                }while (0)

#define __HAL_RCC_TIM16_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM16RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM16RST;      \
                                                }while (0)

#define __HAL_RCC_TIM15_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM15RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM15RST;      \
                                                }while (0)

#define __HAL_RCC_USART6_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART6RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_USART6RST;      \
                                                }while (0)

#define __HAL_RCC_USART1_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;      \
                                                }while (0)

#define __HAL_RCC_TIM8_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM8RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM8RST;      \
                                                }while (0)

#define __HAL_RCC_TIM1_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM1RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_TIM1RST;      \
                                                }while (0)

#define __HAL_RCC_EXTI_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_EXTIRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_EXTIRST;      \
                                                }while (0)

#define __HAL_RCC_CMP1_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_CMP1RST_A;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_CMP1RST_A;      \
                                                }while (0)

#define __HAL_RCC_SYSCFG_RESET()                do                                              \
                                                {                                               \
                                                    RCC->APB2RSTR &= ~RCC_APB2RSTR_SYSCFGRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB2RSTR |= RCC_APB2RSTR_SYSCFGRST;      \
                                                }while (0)

/** @brief  the APB3 peripheral reset.
  */
                                             
#define __HAL_RCC_LPTIM6_RESET()                do                                              \
                                                {                                               \
                                                    RCC->APB3RSTR &= ~RCC_APB3RSTR_LPTIM6RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB3RSTR |= RCC_APB3RSTR_LPTIM6RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_LPTIM5_RESET()                do                                              \
                                                {                                               \
                                                    RCC->APB3RSTR &= ~RCC_APB3RSTR_LPTIM5RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB3RSTR |= RCC_APB3RSTR_LPTIM5RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_LPTIM4_RESET()                do                                              \
                                                {                                               \
                                                    RCC->APB3RSTR &= ~RCC_APB3RSTR_LPTIM4RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB3RSTR |= RCC_APB3RSTR_LPTIM4RST;      \
                                                }while (0)
                                                
#define __HAL_RCC_LPTIM3_RESET()                do                                              \
                                                {                                               \
                                                    RCC->APB3RSTR &= ~RCC_APB3RSTR_LPTIM3RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB3RSTR |= RCC_APB3RSTR_LPTIM3RST;      \
                                                }while (0)
                                                
/** @brief  the APB4 peripheral reset.
  */
                                                
#define __HAL_RCC_DPWM6_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_DPWM6RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_DPWM6RST;      \
                                                }while (0)

#define __HAL_RCC_DPWM5_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_DPWM5RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_DPWM5RST;      \
                                                }while (0)

#define __HAL_RCC_SPWM6_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_SPWM6RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_SPWM6RST;      \
                                                }while (0)

#define __HAL_RCC_SPWM5_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_SPWM5RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_SPWM5RST;      \
                                                }while (0)

#define __HAL_RCC_SPWM4_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_SPWM4RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_SPWM4RST;      \
                                                }while (0)

#define __HAL_RCC_SPWM3_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_SPWM3RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_SPWM3RST;      \
                                                }while (0)

#define __HAL_RCC_MDAC_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_MDACRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_MDACRST;      \
                                                }while (0)

#define __HAL_RCC_LPT_RESET()                   do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_LPTRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_LPTRST;      \
                                                }while (0)

#define __HAL_RCC_PNDL_RESET()                  do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_PNDLRST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_PNDLRST;      \
                                                }while (0)

#define __HAL_RCC_DPWM4_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_DPWM4RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_DPWM4RST;      \
                                                }while (0)

#define __HAL_RCC_DPWM3_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_DPWM3RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_DPWM3RST;      \
                                                }while (0)

#define __HAL_RCC_DPWM2_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_DPWM2RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_DPWM2RST;      \
                                                }while (0)

#define __HAL_RCC_DPWM1_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_DPWM1RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_DPWM1RST;      \
                                                }while (0)

#define __HAL_RCC_SPWM2_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_SPWM2RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_SPWM2RST;      \
                                                }while (0)

#define __HAL_RCC_SPWM1_RESET()                 do                                              \
                                                {                                               \
                                                    RCC->APB4RSTR &= ~RCC_APB4RSTR_SPWM1RST;     \
                                                    __NOP();__NOP();__NOP();                    \
                                                    RCC->APB4RSTR |= RCC_APB4RSTR_SPWM1RST;      \
                                                }while (0)

/** @brief  Enable or Disable the AHB1 peripheral clock.
  */

#define __HAL_RCC_SRAM2_CLK_ENABLE()            ( RCC->AHB1CKENR |= RCC_AHB1CKENR_SRAM2CKEN )
#define __HAL_RCC_SRAM2_CLK_DISABLE()           ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_SRAM2CKEN )
#define __HAL_RCC_SRAM1_CLK_ENABLE()            ( RCC->AHB1CKENR |= RCC_AHB1CKENR_SRAM1CKEN )
#define __HAL_RCC_SRAM1_CLK_DISABLE()           ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_SRAM1CKEN )
#define __HAL_RCC_ROM_CLK_ENABLE()              ( RCC->AHB1CKENR |= RCC_AHB1CKENR_ROMCKEN )
#define __HAL_RCC_ROM_CLK_DISABLE()             ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_ROMCKEN )
#define __HAL_RCC_BKPSRAM_CLK_ENABLE()          ( RCC->AHB1CKENR |= RCC_AHB1CKENR_BKPSRAMCKEN )
#define __HAL_RCC_BKPSRAM_CLK_DISABLE()         ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_BKPSRAMCKEN )
#define __HAL_RCC_FDCAN2_CLK_ENABLE()           ( RCC->AHB1CKENR |= RCC_AHB1CKENR_FDCAN2CKEN )
#define __HAL_RCC_FDCAN2_CLK_DISABLE()          ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_FDCAN2CKEN )
#define __HAL_RCC_FDCAN1_CLK_ENABLE()           ( RCC->AHB1CKENR |= RCC_AHB1CKENR_FDCAN1CKEN )
#define __HAL_RCC_FDCAN1_CLK_DISABLE()          ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_FDCAN1CKEN )
#define __HAL_RCC_USB2_CLK_ENABLE()             ( RCC->AHB1CKENR |= RCC_AHB1CKENR_USB2CCKEN )
#define __HAL_RCC_USB2_CLK_DISABLE()            ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_USB2CCKEN )
#define __HAL_RCC_USB1_CLK_ENABLE()             ( RCC->AHB1CKENR |= RCC_AHB1CKENR_USB1CCKEN )
#define __HAL_RCC_USB1_CLK_DISABLE()            ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_USB1CCKEN )
#define __HAL_RCC_SPI6_CLK_ENABLE()             ( RCC->AHB1CKENR |= RCC_AHB1CKENR_SPI6CKEN )
#define __HAL_RCC_SPI6_CLK_DISABLE()            ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_SPI6CKEN )
#define __HAL_RCC_SPI5_CLK_ENABLE()             ( RCC->AHB1CKENR |= RCC_AHB1CKENR_SPI5CKEN )
#define __HAL_RCC_SPI5_CLK_DISABLE()            ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_SPI5CKEN )
#define __HAL_RCC_SPI4_CLK_ENABLE()             ( RCC->AHB1CKENR |= RCC_AHB1CKENR_SPI4CKEN )
#define __HAL_RCC_SPI4_CLK_DISABLE()            ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_SPI4CKEN )
#define __HAL_RCC_SPI3_CLK_ENABLE()             ( RCC->AHB1CKENR |= RCC_AHB1CKENR_SPI3CKEN )
#define __HAL_RCC_SPI3_CLK_DISABLE()            ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_SPI3CKEN )
#define __HAL_RCC_SPI2_CLK_ENABLE()             ( RCC->AHB1CKENR |= RCC_AHB1CKENR_SPI2CKEN )
#define __HAL_RCC_SPI2_CLK_DISABLE()            ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_SPI2CKEN )
#define __HAL_RCC_SPI1_CLK_ENABLE()             ( RCC->AHB1CKENR |= RCC_AHB1CKENR_SPI1CKEN )
#define __HAL_RCC_SPI1_CLK_DISABLE()            ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_SPI1CKEN )
#define __HAL_RCC_DMA2D_CLK_ENABLE()            ( RCC->AHB1CKENR |= RCC_AHB1CKENR_DMA2DCKEN )
#define __HAL_RCC_DMA2D_CLK_DISABLE()           ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_DMA2DCKEN )
#define __HAL_RCC_ETHRX_CLK_ENABLE()            ( RCC->AHB1CKENR |= RCC_AHB1CKENR_ETHRXCKEN )
#define __HAL_RCC_ETHRX_CLK_DISABLE()           ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_ETHRXCKEN )
#define __HAL_RCC_ETHTX_CLK_ENABLE()            ( RCC->AHB1CKENR |= RCC_AHB1CKENR_ETHTXCKEN )
#define __HAL_RCC_ETHTX_CLK_DISABLE()           ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_ETHTXCKEN )
#define __HAL_RCC_ETHMAC_CLK_ENABLE()           ( RCC->AHB1CKENR |= RCC_AHB1CKENR_ETHMACCKEN )
#define __HAL_RCC_ETHMAC_CLK_DISABLE()          ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_ETHMACCKEN )
#define __HAL_RCC_CRC_CLK_ENABLE()              ( RCC->AHB1CKENR |= RCC_AHB1CKENR_CRCCKEN )
#define __HAL_RCC_CRC_CLK_DISABLE()             ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_CRCCKEN )
#define __HAL_RCC_DMA2_CLK_ENABLE()            ( RCC->AHB1CKENR |= RCC_AHB1CKENR_DMA2CKEN )
#define __HAL_RCC_DMA2_CLK_DISABLE()           ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_DMA2CKEN )
#define __HAL_RCC_DMA1_CLK_ENABLE()            ( RCC->AHB1CKENR |= RCC_AHB1CKENR_DMA1CKEN )
#define __HAL_RCC_DMA1_CLK_DISABLE()           ( RCC->AHB1CKENR &= ~RCC_AHB1CKENR_DMA1CKEN )

/** @brief  Enable or Disable the AHB2 peripheral clock.
  */
  
#define __HAL_RCC_THM_CLK_ENABLE()              ( RCC->AHB2CKENR |= RCC_AHB2CKENR_THMCKEN )
#define __HAL_RCC_THM_CLK_DISABLE()             ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_THMCKEN )
#define __HAL_RCC_FDCAN3_CLK_ENABLE()           ( RCC->AHB2CKENR |= RCC_AHB2CKENR_FDCAN3CKEN )
#define __HAL_RCC_FDCAN3_CLK_DISABLE()          ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_FDCAN3CKEN )
#define __HAL_RCC_CORDIC_CLK_ENABLE()           ( RCC->AHB2CKENR |= RCC_AHB2CKENR_CORDICCKEN )
#define __HAL_RCC_CORDIC_CLK_DISABLE()          ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_CORDICCKEN )
#define __HAL_RCC_HRNG_CLK_ENABLE()             ( RCC->AHB2CKENR |= RCC_AHB2CKENR_HRNGCKEN )
#define __HAL_RCC_HRNG_CLK_DISABLE()            ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_HRNGCKEN )
#define __HAL_RCC_AES_CLK_ENABLE()              ( RCC->AHB2CKENR |= RCC_AHB2CKENR_AESCKEN )
#define __HAL_RCC_AES_CLK_DISABLE()             ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_AESCKEN )
#define __HAL_RCC_AES_SPI1_CLK_ENABLE()         ( RCC->AHB2CKENR |= RCC_AHB2CKENR_AESSPI1CKEN )
#define __HAL_RCC_AES_SPI1_CLK_DISABLE()        ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_AESSPI1CKEN )
#define __HAL_RCC_DCMI_CLK_ENABLE()             ( RCC->AHB2CKENR |= RCC_AHB2CKENR_DCMICKEN )
#define __HAL_RCC_DCMI_CLK_DISABLE()            ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_DCMICKEN )
#define __HAL_RCC_DAC2_CLK_ENABLE()             ( RCC->AHB2CKENR |= RCC_AHB2CKENR_DAC2CKEN )
#define __HAL_RCC_DAC2_CLK_DISABLE()            ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_DAC2CKEN )
#define __HAL_RCC_DAC1_CLK_ENABLE()             ( RCC->AHB2CKENR |= RCC_AHB2CKENR_DAC1CKEN )
#define __HAL_RCC_DAC1_CLK_DISABLE()            ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_DAC1CKEN )
#define __HAL_RCC_ADC3_CLK_ENABLE()             ( RCC->AHB2CKENR |= RCC_AHB2CKENR_ADC3CKEN )
#define __HAL_RCC_ADC3_CLK_DISABLE()            ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_ADC3CKEN )
#define __HAL_RCC_ADC12_CLK_ENABLE()            ( RCC->AHB2CKENR |= RCC_AHB2CKENR_ADC12CKEN )
#define __HAL_RCC_ADC12_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_ADC12CKEN )
#define __HAL_RCC_GPIOQ_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOQCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOQ_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOQCKEN )
#define __HAL_RCC_GPIOP_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOPCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOP_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOPCKEN )
#define __HAL_RCC_GPIOO_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOOCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOO_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOOCKEN )
#define __HAL_RCC_GPION_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIONCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPION_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIONCKEN )
#define __HAL_RCC_GPIOM_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOMCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOM_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOMCKEN )
#define __HAL_RCC_GPIOL_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOLCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOL_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOLCKEN )
#define __HAL_RCC_GPIOK_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOKCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOK_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOKCKEN )
#define __HAL_RCC_GPIOJ_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOJCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOJ_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOJCKEN )
#define __HAL_RCC_GPIOI_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOICKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOI_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOICKEN )
#define __HAL_RCC_GPIOH_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOHCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOH_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOHCKEN )
#define __HAL_RCC_GPIOG_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOGCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOG_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOGCKEN )
#define __HAL_RCC_GPIOF_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOFCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOF_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOFCKEN )
#define __HAL_RCC_GPIOE_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOECKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOE_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOECKEN )
#define __HAL_RCC_GPIOD_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIODCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOD_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIODCKEN )
#define __HAL_RCC_GPIOC_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOCCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOC_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOCCKEN )
#define __HAL_RCC_GPIOB_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOBCKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOB_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOBCKEN )
#define __HAL_RCC_GPIOA_CLK_ENABLE()            do                                                      \
                                                {                                                       \
                                                    RCC->AHB2CKENR |= RCC_AHB2CKENR_GPIOACKEN;    \
                                                    RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN;     \
                                                } while (0)
#define __HAL_RCC_GPIOA_CLK_DISABLE()           ( RCC->AHB2CKENR &= ~RCC_AHB2CKENR_GPIOACKEN )
        
/** @brief  Enable or Disable the AHB3 peripheral clock.
  */
              
#define __HAL_RCC_FMC_CLK_ENABLE()              ( RCC->AHB3CKENR |= RCC_AHB3CKENR_FMCCKEN )
#define __HAL_RCC_FMC_CLK_DISABLE()             ( RCC->AHB3CKENR &= ~RCC_AHB3CKENR_FMCCKEN )
#define __HAL_RCC_OSPI2_CLK_ENABLE()            ( RCC->AHB3CKENR |= RCC_AHB3CKENR_OSPI2CKEN )
#define __HAL_RCC_OSPI2_CLK_DISABLE()           ( RCC->AHB3CKENR &= ~RCC_AHB3CKENR_OSPI2CKEN )
#define __HAL_RCC_OSPI1_CLK_ENABLE()            ( RCC->AHB3CKENR |= RCC_AHB3CKENR_OSPI1CKEN )
#define __HAL_RCC_OSPI1_CLK_DISABLE()           ( RCC->AHB3CKENR &= ~RCC_AHB3CKENR_OSPI1CKEN )
#define __HAL_RCC_SDMMC_CLK_ENABLE()            ( RCC->AHB3CKENR |= RCC_AHB3CKENR_SDMMCCKEN )
#define __HAL_RCC_SDMMC_CLK_DISABLE()           ( RCC->AHB3CKENR &= ~RCC_AHB3CKENR_SDMMCCKEN )
#define __HAL_RCC_SPI7_CLK_ENABLE()             ( RCC->AHB3CKENR |= RCC_AHB3CKENR_SPI7CKEN)
#define __HAL_RCC_SPI7_CLK_DISABLE()            ( RCC->AHB3CKENR &= ~RCC_AHB3CKENR_SPI7CKEN)
#define __HAL_RCC_SPI8_CLK_ENABLE()             ( RCC->AHB3CKENR |= RCC_AHB3CKENR_SPI8CKEN)
#define __HAL_RCC_SPI8_CLK_DISABLE()            ( RCC->AHB3CKENR &= ~RCC_AHB3CKENR_SPI8CKEN)

/** @brief  Enable or Disable the APB1 peripheral clock.
  */

#define __HAL_RCC_LPUART1_CLK_ENABLE()          ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_LPUART1CKEN )
#define __HAL_RCC_LPUART1_CLK_DISABLE()         ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_LPUART1CKEN )
#define __HAL_RCC_LPTIM1_CLK_ENABLE()           ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_LPTIM1CKEN )
#define __HAL_RCC_LPTIM1_CLK_DISABLE()          ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_LPTIM1CKEN )
#define __HAL_RCC_PMU_CLK_ENABLE()              ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_PMUCKEN )
#define __HAL_RCC_PMU_CLK_DISABLE()             ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_PMUCKEN )
#define __HAL_RCC_I2C4_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_I2C4CKEN )
#define __HAL_RCC_I2C4_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_I2C4CKEN )
#define __HAL_RCC_I2C3_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_I2C3CKEN )
#define __HAL_RCC_I2C3_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_I2C3CKEN )
#define __HAL_RCC_I2C2_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_I2C2CKEN )
#define __HAL_RCC_I2C2_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_I2C2CKEN )
#define __HAL_RCC_I2C1_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_I2C1CKEN )
#define __HAL_RCC_I2C1_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_I2C1CKEN )
#define __HAL_RCC_USART5_CLK_ENABLE()           ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_USART5CKEN )
#define __HAL_RCC_USART5_CLK_DISABLE()          ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_USART5CKEN )
#define __HAL_RCC_USART4_CLK_ENABLE()           ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_USART4CKEN )
#define __HAL_RCC_USART4_CLK_DISABLE()          ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_USART4CKEN )
#define __HAL_RCC_USART3_CLK_ENABLE()           ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_USART3CKEN )
#define __HAL_RCC_USART3_CLK_DISABLE()          ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_USART3CKEN )
#define __HAL_RCC_USART2_CLK_ENABLE()           ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_USART2CKEN )
#define __HAL_RCC_USART2_CLK_DISABLE()          ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_USART2CKEN )
#define __HAL_RCC_I2S3_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_I2S3CKEN )
#define __HAL_RCC_I2S3_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_I2S3CKEN )
#define __HAL_RCC_I2S2_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_I2S2CKEN )
#define __HAL_RCC_I2S2_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_I2S2CKEN )
#define __HAL_RCC_I2S1_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_I2S1CKEN )
#define __HAL_RCC_I2S1_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_I2S1CKEN )
#define __HAL_RCC_WDT_CLK_ENABLE()              ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_WDTCKEN )
#define __HAL_RCC_WDT_CLK_DISABLE()             ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_WDTCKEN )
#define __HAL_RCC_RTC_CLK_ENABLE()              ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_RTCCKEN )
#define __HAL_RCC_RTC_CLK_DISABLE()             ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_RTCCKEN )
#define __HAL_RCC_TIM14_CLK_ENABLE()            ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_TIM14CKEN )
#define __HAL_RCC_TIM14_CLK_DISABLE()           ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_TIM14CKEN )
#define __HAL_RCC_TIM13_CLK_ENABLE()            ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_TIM13CKEN )
#define __HAL_RCC_TIM13_CLK_DISABLE()           ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_TIM13CKEN )
#define __HAL_RCC_TIM12_CLK_ENABLE()            ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_TIM12CKEN )
#define __HAL_RCC_TIM12_CLK_DISABLE()           ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_TIM12CKEN )
#define __HAL_RCC_TIM7_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_TIM7CKEN )
#define __HAL_RCC_TIM7_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_TIM7CKEN )
#define __HAL_RCC_TIM6_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_TIM6CKEN )
#define __HAL_RCC_TIM6_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_TIM6CKEN )
#define __HAL_RCC_TIM5_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_TIM5CKEN )
#define __HAL_RCC_TIM5_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_TIM5CKEN )
#define __HAL_RCC_TIM4_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_TIM4CKEN )
#define __HAL_RCC_TIM4_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_TIM4CKEN )
#define __HAL_RCC_TIM3_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_TIM3CKEN )
#define __HAL_RCC_TIM3_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_TIM3CKEN )
#define __HAL_RCC_TIM2_CLK_ENABLE()             ( RCC->APB1CKENR1 |= RCC_APB1CKENR1_TIM2CKEN )
#define __HAL_RCC_TIM2_CLK_DISABLE()            ( RCC->APB1CKENR1 &= ~RCC_APB1CKENR1_TIM2CKEN )
#define __HAL_RCC_EFUSE2_CLK_ENABLE()           ( RCC->APB1CKENR2 |= RCC_APB1CKENR2_EFUSE2CKEN )
#define __HAL_RCC_EFUSE2_CLK_DISABLE()          ( RCC->APB1CKENR2 &= ~RCC_APB1CKENR2_EFUSE2CKEN )
#define __HAL_RCC_EFUSE1_CLK_ENABLE()           ( RCC->APB1CKENR2 |= RCC_APB1CKENR2_EFUSE1CKEN )
#define __HAL_RCC_EFUSE1_CLK_DISABLE()          ( RCC->APB1CKENR2 &= ~RCC_APB1CKENR2_EFUSE1CKEN )
#define __HAL_RCC_TIM26_CLK_ENABLE()            ( RCC->APB1CKENR2 |= RCC_APB1CKENR2_TIM26CKEN )
#define __HAL_RCC_TIM26_CLK_DISABLE()           ( RCC->APB1CKENR2 &= ~RCC_APB1CKENR2_TIM26CKEN )
#define __HAL_RCC_TIM25_CLK_ENABLE()            ( RCC->APB1CKENR2 |= RCC_APB1CKENR2_TIM25CKEN )
#define __HAL_RCC_TIM25_CLK_DISABLE()           ( RCC->APB1CKENR2 &= ~RCC_APB1CKENR2_TIM25CKEN )
#define __HAL_RCC_USART8_CLK_ENABLE()           ( RCC->APB1CKENR2 |= RCC_APB1CKENR2_USART8CKEN )
#define __HAL_RCC_USART8_CLK_DISABLE()          ( RCC->APB1CKENR2 &= ~RCC_APB1CKENR2_USART8CKEN )
#define __HAL_RCC_USART7_CLK_ENABLE()           ( RCC->APB1CKENR2 |= RCC_APB1CKENR2_USART7CKEN )
#define __HAL_RCC_USART7_CLK_DISABLE()          ( RCC->APB1CKENR2 &= ~RCC_APB1CKENR2_USART7CKEN )
#define __HAL_RCC_LPTIM2_CLK_ENABLE()           ( RCC->APB1CKENR2 |= RCC_APB1CKENR2_LPTIM2CKEN )
#define __HAL_RCC_LPTIM2_CLK_DISABLE()          ( RCC->APB1CKENR2 &= ~RCC_APB1CKENR2_LPTIM2CKEN )

/** @brief  Enable or Disable the APB2 peripheral clock.
  */

#define __HAL_RCC_USART10_CLK_ENABLE()          ( RCC->APB2CKENR |= RCC_APB2CKENR_USART10CKEN )
#define __HAL_RCC_USART10_CLK_DISABLE()         ( RCC->APB2CKENR &= ~RCC_APB2CKENR_USART10CKEN )
#define __HAL_RCC_USART9_CLK_ENABLE()           ( RCC->APB2CKENR |= RCC_APB2CKENR_USART9CKEN )
#define __HAL_RCC_USART9_CLK_DISABLE()          ( RCC->APB2CKENR &= ~RCC_APB2CKENR_USART9CKEN )
#define __HAL_RCC_TIM24_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM24CKEN )
#define __HAL_RCC_TIM24_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM24CKEN )
#define __HAL_RCC_TIM23_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM23CKEN )
#define __HAL_RCC_TIM23_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM23CKEN )
#define __HAL_RCC_TIM22_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM22CKEN )
#define __HAL_RCC_TIM22_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM22CKEN )
#define __HAL_RCC_TIM21_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM21CKEN )
#define __HAL_RCC_TIM21_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM21CKEN )
#define __HAL_RCC_TIM19_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM19CKEN )
#define __HAL_RCC_TIM19_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM19CKEN )
#define __HAL_RCC_TIM18_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM18CKEN )
#define __HAL_RCC_TIM18_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM18CKEN )
#define __HAL_RCC_TIM11_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM11CKEN )
#define __HAL_RCC_TIM11_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM11CKEN )
#define __HAL_RCC_TIM10_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM10CKEN )
#define __HAL_RCC_TIM10_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM10CKEN )
#define __HAL_RCC_TIM9_CLK_ENABLE()             ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM9CKEN )
#define __HAL_RCC_TIM9_CLK_DISABLE()            ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM9CKEN )
#define __HAL_RCC_LTDC_CLK_ENABLE()             ( RCC->APB2CKENR |= RCC_APB2CKENR_LTDCCKEN )
#define __HAL_RCC_LTDC_CLK_DISABLE()            ( RCC->APB2CKENR &= ~RCC_APB2CKENR_LTDCCKEN )
#define __HAL_RCC_TKEY_CLK_ENABLE()             ( RCC->APB2CKENR |= RCC_APB2CKENR_TKEYCKEN )
#define __HAL_RCC_TKEY_CLK_DISABLE()            ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TKEYCKEN )
#define __HAL_RCC_TIM20_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM20CKEN )
#define __HAL_RCC_TIM20_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM20CKEN )
#define __HAL_RCC_TIM17_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM17CKEN )
#define __HAL_RCC_TIM17_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM17CKEN )
#define __HAL_RCC_TIM16_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM16CKEN )
#define __HAL_RCC_TIM16_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM16CKEN )
#define __HAL_RCC_TIM15_CLK_ENABLE()            ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM15CKEN )
#define __HAL_RCC_TIM15_CLK_DISABLE()           ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM15CKEN )
#define __HAL_RCC_USART6_CLK_ENABLE()           ( RCC->APB2CKENR |= RCC_APB2CKENR_USART6CKEN )
#define __HAL_RCC_USART6_CLK_DISABLE()          ( RCC->APB2CKENR &= ~RCC_APB2CKENR_USART6CKEN )
#define __HAL_RCC_USART1_CLK_ENABLE()           ( RCC->APB2CKENR |= RCC_APB2CKENR_USART1CKEN )
#define __HAL_RCC_USART1_CLK_DISABLE()          ( RCC->APB2CKENR &= ~RCC_APB2CKENR_USART1CKEN )
#define __HAL_RCC_TIM8_CLK_ENABLE()             ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM8CKEN )
#define __HAL_RCC_TIM8_CLK_DISABLE()            ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM8CKEN )
#define __HAL_RCC_TIM1_CLK_ENABLE()             ( RCC->APB2CKENR |= RCC_APB2CKENR_TIM1CKEN )
#define __HAL_RCC_TIM1_CLK_DISABLE()            ( RCC->APB2CKENR &= ~RCC_APB2CKENR_TIM1CKEN )
#define __HAL_RCC_EXTI_CLK_ENABLE()             ( RCC->APB2CKENR |= RCC_APB2CKENR_EXTICKEN )
#define __HAL_RCC_EXTI_CLK_DISABLE()            ( RCC->APB2CKENR &= ~RCC_APB2CKENR_EXTICKEN )
#define __HAL_RCC_CMP1_CLK_ENABLE()             ( RCC->APB2CKENR |= RCC_APB2CKENR_CMP1CKEN_A )
#define __HAL_RCC_CMP1_CLK_DISABLE()            ( RCC->APB2CKENR &= ~RCC_APB2CKENR_CMP1CKEN_A )
#define __HAL_RCC_SYSCFG_CLK_ENABLE()           ( RCC->APB2CKENR |= RCC_APB2CKENR_SYSCFGCKEN )
#define __HAL_RCC_SYSCFG_CLK_DISABLE()          ( RCC->APB2CKENR &= ~RCC_APB2CKENR_SYSCFGCKEN )

/** @brief  Enable or Disable the APB3 peripheral clock.
  */

#define __HAL_RCC_LPTIM6_CLK_ENABLE()           ( RCC->APB3CKENR |= RCC_APB3CKENR_LPTIM6CKEN )
#define __HAL_RCC_LPTIM6_CLK_DISABLE()          ( RCC->APB3CKENR &= ~RCC_APB3CKENR_LPTIM6CKEN )
#define __HAL_RCC_LPTIM5_CLK_ENABLE()           ( RCC->APB3CKENR |= RCC_APB3CKENR_LPTIM5CKEN )
#define __HAL_RCC_LPTIM5_CLK_DISABLE()          ( RCC->APB3CKENR &= ~RCC_APB3CKENR_LPTIM5CKEN )
#define __HAL_RCC_LPTIM4_CLK_ENABLE()           ( RCC->APB3CKENR |= RCC_APB3CKENR_LPTIM4CKEN )
#define __HAL_RCC_LPTIM4_CLK_DISABLE()          ( RCC->APB3CKENR &= ~RCC_APB3CKENR_LPTIM4CKEN )
#define __HAL_RCC_LPTIM3_CLK_ENABLE()           ( RCC->APB3CKENR |= RCC_APB3CKENR_LPTIM3CKEN )
#define __HAL_RCC_LPTIM3_CLK_DISABLE()          ( RCC->APB3CKENR &= ~RCC_APB3CKENR_LPTIM3CKEN )

/** @brief  Enable or Disable the APB4 peripheral clock.
  */

#define __HAL_RCC_DPWM6_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_DPWM6CKEN )
#define __HAL_RCC_DPWM6_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_DPWM6CKEN )
#define __HAL_RCC_DPWM5_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_DPWM5CKEN )
#define __HAL_RCC_DPWM5_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_DPWM5CKEN )
#define __HAL_RCC_SPWM6_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_SPWM6CKEN )
#define __HAL_RCC_SPWM6_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_SPWM6CKEN )
#define __HAL_RCC_SPWM5_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_SPWM5CKEN )
#define __HAL_RCC_SPWM5_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_SPWM5CKEN )
#define __HAL_RCC_SPWM4_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_SPWM4CKEN )
#define __HAL_RCC_SPWM4_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_SPWM4CKEN )
#define __HAL_RCC_SPWM3_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_SPWM3CKEN )
#define __HAL_RCC_SPWM3_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_SPWM3CKEN )
#define __HAL_RCC_MDAC_CLK_ENABLE()             ( RCC->APB4CKENR |= RCC_APB4CKENR_MDACCKEN )
#define __HAL_RCC_MDAC_CLK_DISABLE()            ( RCC->APB4CKENR &= ~RCC_APB4CKENR_MDACCKEN )
#define __HAL_RCC_PNDL_CLK_ENABLE()             ( RCC->APB4CKENR |= RCC_APB4CKENR_PNDLCKEN )
#define __HAL_RCC_PNDL_CLK_DISABLE()            ( RCC->APB4CKENR &= ~RCC_APB4CKENR_PNDLCKEN )
#define __HAL_RCC_DPWM4_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_DPWM4CKEN )
#define __HAL_RCC_DPWM4_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_DPWM4CKEN )
#define __HAL_RCC_DPWM3_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_DPWM3CKEN )
#define __HAL_RCC_DPWM3_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_DPWM3CKEN )
#define __HAL_RCC_DPWM2_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_DPWM2CKEN )
#define __HAL_RCC_DPWM2_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_DPWM2CKEN )
#define __HAL_RCC_DPWM1_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_DPWM1CKEN )
#define __HAL_RCC_DPWM1_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_DPWM1CKEN )
#define __HAL_RCC_SPWM2_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_SPWM2CKEN )
#define __HAL_RCC_SPWM2_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_SPWM2CKEN )
#define __HAL_RCC_SPWM1_CLK_ENABLE()            ( RCC->APB4CKENR |= RCC_APB4CKENR_SPWM1CKEN )
#define __HAL_RCC_SPWM1_CLK_DISABLE()           ( RCC->APB4CKENR &= ~RCC_APB4CKENR_SPWM1CKEN )

/******************************************************************************/

/** @defgroup  RCC Private Macros
  * @{
  */
  
#define IS_RCC_RESET_SOURCE(SOURCE)             ((((SOURCE) & RCC_RESET_SOURCE_MASK) != 0U) && \
                                                 (((SOURCE) & ~RCC_RESET_SOURCE_MASK) == 0U))

#define IS_RCC_OSC_TYPE(TYPE)                   ((((TYPE) & RCC_OSC_TYPE_MASK) != 0U) && \
                                                 (((TYPE) & ~RCC_OSC_TYPE_MASK) == 0U))

#define IS_RCC_OSC_XTL_DRIVE(DRIVE)             ((DRIVE) < RCC_XTL_DRIVE_MAX)

#define IS_RCC_IT(IT)                           ((((IT) & RCC_IT_MASK) != 0U) && \
                                                 (((IT) & ~RCC_IT_MASK) == 0U))

#define IS_RCC_IT_FLAG(FLAG)                    ((((FLAG) & RCC_FLAG_MASK) != 0U) && \
                                                 (((FLAG) & ~RCC_FLAG_MASK) == 0U))
                                                 
#define IS_RCC_PLL_CLOCK_SOURCE(SOURCE)         ((SOURCE) < RCC_PLL_SOURCE_MAX)

#define IS_RCC_PLL1_PLLQ(PLLQ)                  (((PLLQ) != 0) && ((PLLQ) <= 15))

#define IS_RCC_PLL1_PLLP(PLLP)                  (((PLLP) == 2U)   || \
                                                 ((PLLP) == 4U)   || \
                                                 ((PLLP) == 6U)   || \
                                                 ((PLLP) == 8U))

#define IS_RCC_PLL1_PLLN(PLLN)                  (((PLLN) != 0) && ((PLLN) <= 63U))

#define IS_RCC_PLL1_PLLF(PLLF)                  (((PLLF) >= 50U) && ((PLLF) <= 511U))

#define IS_RCC_PLL2_PLLQ(PLLQ)                  (((PLLQ) != 0) && ((PLLQ) <= 15))

#define IS_RCC_PLL2_PLLP(PLLP)                  (((PLLP) == 2U)   || \
                                                 ((PLLP) == 4U)   || \
                                                 ((PLLP) == 6U)   || \
                                                 ((PLLP) == 8U))

#define IS_RCC_PLL2_PLLN(PLLN)                  (((PLLN) != 0) && ((PLLN) <= 63U))

#define IS_RCC_PLL2_PLLF(PLLF)                  (((PLLF) >= 50U) && ((PLLF) <= 511U))

#define IS_RCC_PLL3_PLLQ(PLLQ)                  (((PLLQ) == 1U)   || \
                                                 ((PLLQ) == 2U)   || \
                                                 ((PLLQ) == 4U)   || \
                                                 ((PLLQ) == 8U))

#define IS_RCC_PLL3_PLLP(PLLP)                  (((PLLP) == 1U)   || \
                                                 ((PLLP) == 2U)   || \
                                                 ((PLLP) == 4U)   || \
                                                 ((PLLP) == 8U))

#define IS_RCC_PLL3_PLLN(PLLN)                  (((PLLN) != 0) && ((PLLN) <= 64U))

#define IS_RCC_PLL3_PLLF(PLLF)                  (((PLLF) != 0) && ((PLLF) <= 128U))

#define IS_RCC_CLOCK_TYPE(TYPE)                 ((((TYPE) & RCC_CLOCK_TYPE_MASK) != 0U) && \
                                                 (((TYPE) & ~RCC_CLOCK_TYPE_MASK) == 0U))

#define IS_RCC_SYSCLK_SOURCE(SOURCE)            ((SOURCE) < RCC_SYSCLK_SOURCE_MAX)

#define IS_RCC_SYSCLK_DIV(DIV)                  (((DIV) != 0) && ((DIV) <= 16U))

#define IS_RCC_SYSCLK_DIV(DIV)                  (((DIV) != 0) && ((DIV) <= 16U))

#define IS_RCC_PCLK_DIV(DIV)                    (((DIV) == 1)   || \
                                                 ((DIV) == 2)   || \
                                                 ((DIV) == 4)   || \
                                                 ((DIV) == 8)   || \
                                                 ((DIV) == 16))

#define IS_RCC_HRNGS_CLK_DIV(DIV)               (((DIV) != 0) && ((DIV) <= 128U))

#define IS_RCC_FLT_CLK_SOURCE(SOURCE)           ((SOURCE) < RCC_FLT_CLK_SOURCE_MAX)

#define IS_RCC_LPUART1_CLK_SOURCE(SOURCE)       ((SOURCE) < RCC_LPUART1_CLK_SOURCE_MAX)

#define IS_RCC_LPTIM1_CLK_SOURCE(SOURCE)        ((SOURCE) < RCC_LPTIM1_CLK_SOURCE_MAX)

#define IS_RCC_LPTIM2_CLK_SOURCE(SOURCE)        ((SOURCE) < RCC_LPTIM2_CLK_SOURCE_MAX)

#define IS_RCC_LPTIM3_CLK_SOURCE(SOURCE)        ((SOURCE) < RCC_LPTIM3_CLK_SOURCE_MAX)

#define IS_RCC_LPTIM4_CLK_SOURCE(SOURCE)        ((SOURCE) < RCC_LPTIM4_CLK_SOURCE_MAX)

#define IS_RCC_LPTIM5_CLK_SOURCE(SOURCE)        ((SOURCE) < RCC_LPTIM5_CLK_SOURCE_MAX)

#define IS_RCC_LPTIM6_CLK_SOURCE(SOURCE)        ((SOURCE) < RCC_LPTIM6_CLK_SOURCE_MAX)

#define IS_RCC_SDMMC_CLK_SOURCE(SOURCE)         ((SOURCE) < RCC_SDMMC_CLK_SOURCE_MAX)

#define IS_RCC_SDMMC_SCLK_SOURCE(SOURCE)         ((SOURCE) < RCC_SDMMC_SCLK_SOURCE_MAX)

#define IS_RCC_LCD_CLK_DIV(DIV)                 (((DIV) == 2)   || \
                                                 ((DIV) == 4)   || \
                                                 ((DIV) == 8)   || \
                                                 ((DIV) == 16))

#define IS_RCC_RTC_CLK_SOURCE(SOURCE)           ((SOURCE) < RCC_RTC_CLK_SOURCE_MAX)

#define IS_RCC_MCO(MCO)                         ((MCO) < RCC_MCO_MAX)

#define IS_RCC_MCO1_DIV(DIV)                    (((DIV) != 0) && ((DIV) <= 65536U))

#define IS_RCC_MCO2_DIV(DIV)                    (((DIV) != 0) && ((DIV) <= 64U))

                                           
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

void HAL_RCC_ReadyIRQHandler(void);
void HAL_RCC_XTHStopIRQHandler(void);
void HAL_RCC_XTLStopIRQHandler(void);
void HAL_RCC_RCHReadyCallback(void);
void HAL_RCC_RCLReadyCallback(void);
void HAL_RCC_XTHReadyCallback(void);
void HAL_RCC_XTLReadyCallback(void);
void HAL_RCC_PLL1ReadyCallback(void);;
void HAL_RCC_PLL2ReadyCallback(void);
void HAL_RCC_PLL3ReadyCallback(void);
void HAL_RCC_XTHStopCallback(void);
void HAL_RCC_XTLStopCallback(void);

HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInit);

HAL_StatusTypeDef HAL_RCC_RCHConfig(FunctionalState RCH, FunctionalState Div16);
HAL_StatusTypeDef HAL_RCC_RCLConfig(FunctionalState RCL);
HAL_StatusTypeDef HAL_RCC_XTHConfig(FunctionalState XTH, FunctionalState Bypass);
HAL_StatusTypeDef HAL_RCC_XTLConfig(FunctionalState XTL, FunctionalState Bypass);
HAL_StatusTypeDef HAL_RCC_PLL1Config(FunctionalState PLL1, uint32_t ClockSource, \
                                     uint32_t PLLN, uint32_t PLLF, uint32_t PLLP, uint32_t PLLQ);
HAL_StatusTypeDef HAL_RCC_PLL1SSCConfig(FunctionalState PLL1, uint32_t ClockSource, \
                                     uint32_t PLLN, uint32_t PLLF, uint32_t PLLP, uint32_t PLLQ, \
                                     FunctionalState SSC, uint32_t Mode, uint32_t Spectrum, uint32_t Step);
HAL_StatusTypeDef HAL_RCC_PLL1PCLKConfig(FunctionalState PLL1PCLK);
HAL_StatusTypeDef HAL_RCC_PLL1QCLKConfig(FunctionalState PLL1QCLK);
HAL_StatusTypeDef HAL_RCC_PLL2Config(FunctionalState PLL2, uint32_t PLLSource, \
                                     uint32_t PLLN, uint32_t PLLF, uint32_t PLLP, uint32_t PLLQ);
HAL_StatusTypeDef HAL_RCC_PLL2SSCConfig(FunctionalState PLL2, uint32_t ClockSource, \
                            uint32_t PLLN, uint32_t PLLF, uint32_t PLLP, uint32_t PLLQ, \
                            FunctionalState SSC, uint32_t Mode, uint32_t Spectrum, uint32_t Step);
HAL_StatusTypeDef HAL_RCC_PLL2PCLKConfig(FunctionalState PLL1PCLK);
HAL_StatusTypeDef HAL_RCC_PLL2QCLKConfig(FunctionalState PLL1QCLK);
HAL_StatusTypeDef HAL_RCC_PLL3Config(FunctionalState PLL3, uint32_t ClockSource, \
                                     uint32_t PLLN, uint32_t PLLF, uint32_t PLLP, uint32_t PLLQ);
HAL_StatusTypeDef HAL_RCC_PLL3PCLKConfig(FunctionalState PLL1PCLK);
HAL_StatusTypeDef HAL_RCC_PLL3QCLKConfig(FunctionalState PLL1QCLK);

HAL_StatusTypeDef HAL_RCC_ITConfig(uint32_t IT, FunctionalState NewStatus);
uint32_t HAL_RCC_GetITFlag(uint32_t IT);
HAL_StatusTypeDef HAL_RCC_ClearITFlag(uint32_t IT);

HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInit);
HAL_StatusTypeDef HAL_RCC_SYSCLKSourceConfig(uint32_t ClockSource);
HAL_StatusTypeDef HAL_RCC_SYSCLKDiv0Config(uint32_t Div);
HAL_StatusTypeDef HAL_RCC_SYSCLKDiv1Config(uint32_t Div);
HAL_StatusTypeDef HAL_RCC_PCLK1DivConfig(uint32_t Div);
HAL_StatusTypeDef HAL_RCC_PCLK2DivConfig(uint32_t Div);
HAL_StatusTypeDef HAL_RCC_PCLK3DivConfig(uint32_t Div);
HAL_StatusTypeDef HAL_RCC_PCLK4DivConfig(uint32_t Div);
HAL_StatusTypeDef HAL_RCC_HRNGSClockDivConfig(uint32_t Div);
HAL_StatusTypeDef HAL_RCC_FLTClockSourceConfig(uint32_t ClockSource);
HAL_StatusTypeDef HAL_RCC_LPUART1ClockSourceConfig(uint32_t ClockSource);
HAL_StatusTypeDef HAL_RCC_LPTIM1ClockSourceConfig(uint32_t ClockSource);
HAL_StatusTypeDef HAL_RCC_LPTIM2ClockSourceConfig(uint32_t ClockSource);
HAL_StatusTypeDef HAL_RCC_LPTIM3ClockSourceConfig(uint32_t ClockSource);
HAL_StatusTypeDef HAL_RCC_LPTIM4ClockSourceConfig(uint32_t ClockSource);
HAL_StatusTypeDef HAL_RCC_LPTIM5ClockSourceConfig(uint32_t ClockSource);
HAL_StatusTypeDef HAL_RCC_LPTIM6ClockSourceConfig(uint32_t ClockSource);
HAL_StatusTypeDef HAL_RCC_SDMMCClockSourceConfig(uint32_t ClockSource);
HAL_StatusTypeDef HAL_RCC_SDMMCSampleClockSourceConfig(uint32_t SampleClockSource);
HAL_StatusTypeDef HAL_RCC_LCDPiexlClockDivConfig(uint32_t Div);
HAL_StatusTypeDef HAL_RCC_RTCClockSourceConfig(uint32_t ClockSource);

HAL_StatusTypeDef HAL_RCC_GetClock(RCC_ClkInitTypeDef  *RCC_ClkInit);
HAL_StatusTypeDef HAL_RCC_GetSYSCLKSource(uint32_t *pClockSource);
HAL_StatusTypeDef HAL_RCC_GetHRNGSlowClockDiv(uint32_t *pClockDiv);
HAL_StatusTypeDef HAL_RCC_GetFLTClockSource(uint32_t *pClockSource);
HAL_StatusTypeDef HAL_RCC_GetLPUART1ClockSource(uint32_t *pClockSource);
HAL_StatusTypeDef HAL_RCC_GetLPTIM1ClockSource(uint32_t *pClockSource);
HAL_StatusTypeDef HAL_RCC_GetLPTIM2ClockSource(uint32_t *pClockSource);
HAL_StatusTypeDef HAL_RCC_GetLPTIM3ClockSource(uint32_t *pClockSource);
HAL_StatusTypeDef HAL_RCC_GetLPTIM4ClockSource(uint32_t *pClockSource);
HAL_StatusTypeDef HAL_RCC_GetLPTIM5ClockSource(uint32_t *pClockSource);
HAL_StatusTypeDef HAL_RCC_GetLPTIM6ClockSource(uint32_t *pClockSource);
HAL_StatusTypeDef HAL_RCC_GetSDMMCSampleClockSource(uint32_t *pClockSource);
HAL_StatusTypeDef HAL_RCC_GetRTCClockSource(uint32_t *pClockSource);

uint32_t HAL_RCC_GetRCHTrimFreq(void);
uint32_t HAL_RCC_GetRCLTrimFreq(void);
uint32_t HAL_RCC_GetRCHFreq(void);
uint32_t HAL_RCC_GetRCLFreq(void);
uint32_t HAL_RCC_GetXTHFreq(void);
uint32_t HAL_RCC_GetXTLFreq(void);
uint32_t HAL_RCC_GetPLL1Freq(void);
uint32_t HAL_RCC_GetPLL1PFreq(void);
uint32_t HAL_RCC_GetPLL2Freq(void);
uint32_t HAL_RCC_GetPLL2QFreq(void);
uint32_t HAL_RCC_GetPLL2PFreq(void);
uint32_t HAL_RCC_GetPLL3Freq(void);
uint32_t HAL_RCC_GetPLL3QFreq(void);
uint32_t HAL_RCC_GetPLL3PFreq(void);
uint32_t HAL_RCC_GetSYSCLKFreq(void);
uint32_t HAL_RCC_GetSysCoreClockFreq(void);
uint32_t HAL_RCC_GetFCLKFreq(void);
uint32_t HAL_RCC_GetHCLKFreq(void);
uint32_t HAL_RCC_GetPCLK1Freq(void);
uint32_t HAL_RCC_GetPCLK2Freq(void);
uint32_t HAL_RCC_GetPCLK3Freq(void);
uint32_t HAL_RCC_GetPCLK4Freq(void);
uint32_t HAL_RCC_GetHRNGSClockFreq(void);
uint32_t HAL_RCC_GetFLTClockFreq(void);
uint32_t HAL_RCC_GetLPUART1ClockFreq(void);
uint32_t HAL_RCC_GetLPTIM1ClockFreq(void);
uint32_t HAL_RCC_GetLPTIM2ClockFreq(void);
uint32_t HAL_RCC_GetLPTIM3ClockFreq(void);
uint32_t HAL_RCC_GetLPTIM4ClockFreq(void);
uint32_t HAL_RCC_GetLPTIM5ClockFreq(void);
uint32_t HAL_RCC_GetLPTIM6ClockFreq(void);
uint32_t HAL_RCC_GetSDMMCClockFreq(void);
uint32_t HAL_RCC_GetLCDPiexlClockFreq(void);
uint32_t HAL_RCC_GetRTCClockFreq(void);

uint32_t HAL_RCC_MCOConfig(RCC_MCOInitTypeDef *MCO_InitStruct);
uint32_t HAL_RCC_MCO1Config(uint32_t MCO, uint32_t NewStatus, uint32_t Div);
uint32_t HAL_RCC_MCO2Config(uint32_t MCO, uint32_t NewStatus, uint32_t Div);

void HAL_RCC_SoftwareReset(void);
void HAL_RCC_StandbyReset(void);

void HAL_RCC_LockupResetConfig(FunctionalState NewState);
void HAL_RCC_IWDTResetConfig(FunctionalState NewState);
void HAL_RCC_WDTResetConfig(FunctionalState NewState);
void HAL_RCC_LVDResetConfig(FunctionalState NewState);

uint32_t HAL_RCC_GetResetSource(void);
void HAL_RCC_ClearAllResetSource(void);


#endif


