
/******************************************************************************
*@file  : acm32h5xx.h
*@brief : Device Peripheral Access Layer Header File
*           This file contains:
*           - Data structures and the address mapping for all peripherals
*           - peripherals registers declarations and bits definition
*           - Macros to access peripheral¡¯s registers hardware
******************************************************************************/

#ifndef __ACM32H5XX_H__
#define __ACM32H5XX_H__

    
/* -------  Interrupt Number Definition  ---------------------------------- */

typedef enum IRQn
{
/* ----------------------------------  Cortex-M33 Processor Exceptions Numbers ----------------------------------- */
    Reset_IRQn                      = -15,       /* -15 Reset Vector, invoked on Power up and warm reset                 */
    NonMaskableInt_IRQn             = -14,       /* -14 Non Maskable Interrupt */
    HardFault_IRQn                  = -13,       /* -13 HardFault Interrupt */
    MemoryManagement_IRQn           = -12,       /* -12 Memory Management, MPU mismatch, including Access Violation
                                                  and No Match                                                     */
    BusFault_IRQn                   = -11,       /* -11 Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                  related Fault                                                    */
    UsageFault_IRQn                 = -10,       /* -10 Usage Fault, i.e. Undef Instruction, Illegal State Transition    */

    SVCall_IRQn                     = -5,        /* -5 SV Call Interrupt */
    DebugMonitor_IRQn               = -4,        /* -4 Debug Monitor                                                    */
    PendSV_IRQn                     = -2,        /* -2 Pend SV Interrupt */
    SysTick_IRQn                    = -1,        /* -1 System Tick Interrupt */

    /* ----------------------  Chip Specific Interrupt Numbers  --------------------- */
    WDT_IRQn                        = 0,
    LVD_IRQn                        = 1,
    RTC_XTLSD_IRQn                  = 2,
    RSV3_IRQn                       = 3,
    RSV4_IRQn                       = 4,
    RSV5_IRQn                       = 5,
    CLKRDY_IRQn                     = 6,
    EXTI0_IRQn                      = 7,
    EXTI1_IRQn                      = 8,
    EXTI2_IRQn                      = 9,
    EXTI3_IRQn                      = 10,
    EXTI4_IRQn                      = 11,
    RSV12_IRQn                      = 12,
    RSV13_IRQn                      = 13,
    ADC12_IRQn                      = 14,
    ADC3_IRQn                       = 15,
    DAC1_IRQn                       = 16,
    COMP1_IRQn                      = 17,
    USBOTG1_IRQn                    = 18,
    FDCAN1_IRQn                      = 19,
    FDCAN2_IRQn                      = 20,
    EXTI9_5_IRQn                    = 21,
    TIM1_BRK_UP_TRG_COM_IRQn        = 22,
    TIM1_CC_IRQn                    = 23,
    TIM2_IRQn                       = 24,
    TIM3_IRQn                       = 25,
    TIM6_IRQn                       = 26,
    TIM7_IRQn                       = 27,
    TIM8_BRK_UP_TRG_COM_IRQn        = 28,
    TIM8_CC_IRQn                    = 29,
    TIM15_IRQn                      = 30,
    TIM16_IRQn                      = 31,
    TIM17_IRQn                      = 32,
    I2C1_IRQn                       = 33,
    I2C2_IRQn                       = 34,
    SPI1_IRQn                       = 35,
    SPI2_IRQn                       = 36,
    SPI3_IRQn                       = 37,
    I2S1_IRQn                       = 38,
    I2S2_IRQn                       = 39,
    USART1_IRQn                     = 40,
    USART2_IRQn                     = 41,
    USART3_IRQn                     = 42,
    USART4_IRQn                     = 43,
    EXTI15_10_IRQn                  = 44,
    USBOTG1_WKUP_IRQn               = 45,
    LPUART1_IRQn                    = 46,
    LPTIM1_IRQn                     = 47,
    USBOTG2_WKUP_IRQn               = 48,  
    AES_IRQn                        = 49,  
    FPU_IRQn                        = 50,  
    USBOTG2_IRQn                    = 51,    
    DCMI_IRQn                       = 52,    
    TIM4_IRQn                       = 53,    
    RSV54_IRQn                      = 54,    
    IWDT_WKUP_IRQn                  = 55,    
    LTDC_IRQn                   = 56,    
    LTDC_ERR_IRQn                   = 57,    
    DMA2D_IRQn                      = 58,    
    LPTIM2_IRQn                     = 59,   
    LPTIM3_IRQn                     = 60,    
    LPTIM4_IRQn                     = 61,    
    LPTIM5_IRQn                     = 62,    
    LPTIM6_IRQn                     = 63,    
    AES_SPI1_IRQn                   = 64,    
    I2S3_IRQn                       = 65,    
    SPI4_IRQn                       = 66,    
    SPI5_IRQn                       = 67,    
    SPI6_IRQn                       = 68,    
    I2C3_IRQn                       = 69,    
    I2C4_IRQn                       = 70,     
    FDCAN3_IRQn                     = 71,     
    RSV72_IRQn                      = 72,     
    ETH_IRQn                        = 73,     
    ETH_WKUP_IRQn                   = 74,     
    SDMMC_IRQn                      = 75,     
    USART5_IRQn                     = 76,     
    USART6_IRQn                     = 77,     
    USART7_IRQn                     = 78,     
    USART8_IRQn                     = 79,     
    USART9_IRQn                     = 80,     
    USART10_IRQn                    = 81,     
    DAC2_IRQn                       = 82,     
    TIM5_IRQn                       = 83,     
    TIM9_IRQn                       = 84,     
    TIM10_IRQn                      = 85,     
    TIM11_IRQn                      = 86,     
    TIM12_IRQn                      = 87,     
    TIM13_IRQn                      = 88,     
    TIM14_IRQn                      = 89,     
    TIM18_IRQn                      = 90,      
    TIM19_IRQn                      = 91,      
    TIM20_BRK_UP_TRG_COM_IRQn       = 92,      
    TIM20_CC_IRQn                   = 93,      
    TIM21_IRQn                      = 94,      
    TIM22_IRQn                      = 95,      
    TIM23_IRQn                      = 96,      
    TIM24_IRQn                      = 97,      
    TIM25_IRQn                      = 98,      
    TIM26_IRQn                      = 99,      
    SPI7_IRQn                       = 100,      
    SPI8_IRQn                       = 101,      
    OSPI1_IRQn                      = 102,      
    OSPI2_IRQn                      = 103,      
    RSV104_IRQn                     = 104,      
    TKEY_IRQn                       = 105,      
    LPT_IRQn                        = 106,      
    RSV107_IRQn                     = 107,      
    OTG1_HS_EP_OUT_IRQn             = 108,      
    OTG1_HS_EP_IN_IRQn              = 109,      
    OTG2_HS_EP_OUT_IRQn             = 110,       
    OTG2_HS_EP_IN_IRQn              = 111,       
    NDL_IRQn                        = 112,       
    THM_IRQn                        = 113,       
    STM1_PWM_IRQn                   = 114,       
    STM2_PWM_IRQn                   = 115,       
    DCM1_PWM_IRQn                   = 116,       
    DCM2_PWM_IRQn                   = 117,       
    DCM3_PWM_IRQn                   = 118,       
    DCM4_PWM_IRQn                   = 119,       
    STM3_PWM_IRQn                   = 120,        
    STM4_PWM_IRQn                   = 121,        
    STM5_PWM_IRQn                   = 122,        
    STM6_PWM_IRQn                   = 123,        
    DCM5_PWM_IRQn                   = 124,        
    DCM6_PWM_IRQn                   = 125,
    NAND_IRQn                       = 126,
    BCH_IRQn                        = 127,
    SDRAM_IRQn                      = 128, 
    DMA1_CH0_IRQn                   = 129,
    DMA1_CH1_IRQn                   = 130,
    DMA1_CH2_IRQn                   = 131,
    DMA1_CH3_IRQn                   = 132,
    DMA1_CH4_IRQn                   = 133,
    DMA1_CH5_IRQn                   = 134,
    DMA1_CH6_IRQn                   = 135,
    DMA1_CH7_IRQn                   = 136,
    DMA2_CH0_IRQn                   = 137,
    DMA2_CH1_IRQn                   = 138,
    DMA2_CH2_IRQn                   = 139,
    DMA2_CH3_IRQn                   = 140,
    DMA2_CH4_IRQn                   = 141,
    DMA2_CH5_IRQn                   = 142,
    DMA2_CH6_IRQn                   = 143,
    DMA2_CH7_IRQn                   = 144,
    SRAM1_SEC_IRQn                  = 145,
    SRAM1_DED_IRQn                  = 146,
    SRAM3_SEC_IRQn                  = 147,
    SRAM3_DED_IRQn                  = 148,
    BKPSRAM_SEC_IRQn                = 149,
    BKPSRAM_DED_IRQn                = 150,
} IRQn_Type;

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
#pragma push
#pragma anon_unions
#elif defined (__ICCARM__)
#pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning 586
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif



/* Configuration of the Cortex-M4 Processor and Core Peripherals */
#define __MPU_PRESENT           1       /*!< cm4ikmcu does not provide a MPU present or not       */
#define __NVIC_PRIO_BITS        4       /*!< cm4ikmcu Supports 2 Bits for the Priority Levels     */
#define __Vendor_SysTickConfig  0       /*!< Set to 1 if different SysTick Config is used                 */

#define   ARM_MATH_CM4          1 
#define __TARGET_FPU_VFP        1 
#define __FPU_PRESENT           1 
#define __DSP_PRESENT           1 
#define __ARM_COMPAT_H          1 

#include "core_cm33.h"                       /* Processor and core peripherals */
#include "system_acm32h5xx.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
#pragma pop
#elif defined (__ICCARM__)
/* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic pop
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning restore
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif

/*-------------------Bit Opertions------------------------*/
#define BIT0                            ( 1U << 0 )
#define BIT1                            ( 1U << 1 )
#define BIT2                            ( 1U << 2 )
#define BIT3                            ( 1U << 3 )
#define BIT4                            ( 1U << 4 )
#define BIT5                            ( 1U << 5 )
#define BIT6                            ( 1U << 6 )
#define BIT7                            ( 1U << 7 )
#define BIT8                            ( 1U << 8 )
#define BIT9                            ( 1U << 9 )
#define BIT10                           ( 1U << 10 )
#define BIT11                           ( 1U << 11 )
#define BIT12                           ( 1U << 12 )
#define BIT13                           ( 1U << 13 )
#define BIT14                           ( 1U << 14 )
#define BIT15                           ( 1U << 15 )
#define BIT16                           ( 1U << 16 )
#define BIT17                           ( 1U << 17 )
#define BIT18                           ( 1U << 18 )
#define BIT19                           ( 1U << 19 )
#define BIT20                           ( 1U << 20 )
#define BIT21                           ( 1U << 21 )
#define BIT22                           ( 1U << 22 )
#define BIT23                           ( 1U << 23 )
#define BIT24                           ( 1U << 24 )
#define BIT25                           ( 1U << 25 )
#define BIT26                           ( 1U << 26 )
#define BIT27                           ( 1U << 27 )
#define BIT28                           ( 1U << 28 )
#define BIT29                           ( 1U << 29 )
#define BIT30                           ( 1U << 30 )
#define BIT31                           ( 1U << 31 ) 


/*--------------------------  ITCM memory map  -------------------------*/

#define ITCM_CR                         (*(volatile uint32_t *)(0xE001E010) )
#define ITCM_CR_SZ_Pos                  ( 3U )
#define ITCM_CR_SZ_Msk                  ( 0x0FUL << ITCM_CR_SZ_Pos )
#define ITCM_CR_SZ                      ( ITCM_CR_SZ_Msk )
#define ITCM_CR_EN_Pos                  ( 0U )
#define ITCM_CR_EN_Msk                  ( 0x1UL << ITCM_CR_EN_Pos )
#define ITCM_CR_EN                      ( ITCM_CR_EN_Msk )

/*--------------------------  DTCM memory map  -------------------------*/

#define DTCM_CR                         (*(volatile uint32_t *)(0xE001E014) )
#define DTCM_CR_SZ_Pos                  ( 3U )
#define DTCM_CR_SZ_Msk                  ( 0x0FUL << DTCM_CR_SZ_Pos )
#define DTCM_CR_SZ                      ( DTCM_CR_SZ_Msk )
#define DTCM_CR_EN_Pos                  ( 0U )
#define DTCM_CR_EN_Msk                  ( 0x1UL << DTCM_CR_EN_Pos )
#define DTCM_CR_EN                      ( DTCM_CR_EN_Msk )

/*--------------------------  Peripheral memory map  -------------------------*/

#define SPI7_MEM_BASE_ADDR              ( 0x08000000UL )
#define SPI8_MEM_BASE_ADDR              ( 0x10000000UL )
#define IROM_BASE_ADDR                  ( 0x1FF00000UL )

#define SRAM_BASE_ADDR                  ( 0x20000000UL )  
#define DTCM_BASE_ADDR                  ( SRAM_BASE_ADDR + 0x00000000UL )
#define SRAM1_BASE_ADDR                 ( SRAM_BASE_ADDR + 0x00008000UL )
#define SRAM2_BASE_ADDR                 ( SRAM_BASE_ADDR + 0x00038000UL )
#define SRAM3_BASE_ADDR                 ( SRAM_BASE_ADDR + 0x00058000UL )

#define PERIPH_BASE_ADDR                ( 0x40000000UL)

#define APB1PERIPH_BASE_ADDR            ( PERIPH_BASE_ADDR + 0x00000000UL )
#define APB2PERIPH_BASE_ADDR            ( PERIPH_BASE_ADDR + 0x00010000UL )
#define APB3PERIPH_BASE_ADDR            ( PERIPH_BASE_ADDR + 0x11000000UL )
#define APB4PERIPH_BASE_ADDR            ( PERIPH_BASE_ADDR + 0x13000000UL )
#define AHB1PERIPH_BASE_ADDR            ( PERIPH_BASE_ADDR + 0x00020000UL )
#define AHB2PERIPH_BASE_ADDR            ( PERIPH_BASE_ADDR + 0x08000000UL )
#define AHB3PERIPH_BASE_ADDR            ( PERIPH_BASE_ADDR + 0x12000000UL )

/*----------------------------  APB1 peripherals  ----------------------------*/

#define TIM2_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00000000UL )
#define TIM3_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00000400UL )
#define TIM4_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00000800UL )
#define TIM5_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00000C00UL )
#define TIM6_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00001000UL )
#define TIM7_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00001400UL )
#define TIM12_BASE_ADDR                 ( APB1PERIPH_BASE_ADDR + 0x00001800UL )
#define TIM13_BASE_ADDR                 ( APB1PERIPH_BASE_ADDR + 0x00001C00UL )
#define TIM14_BASE_ADDR                 ( APB1PERIPH_BASE_ADDR + 0x00002000UL )
#define RTC_BASE_ADDR                   ( APB1PERIPH_BASE_ADDR + 0x00002800UL )
#define WDT_BASE_ADDR                   ( APB1PERIPH_BASE_ADDR + 0x00002C00UL )
#define IWDT_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00003000UL )
#define I2S1_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00003400UL )
#define I2S2_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00003800UL )
#define I2S3_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00003C00UL )
#define USART2_BASE_ADDR                ( APB1PERIPH_BASE_ADDR + 0x00004400UL )
#define USART3_BASE_ADDR                ( APB1PERIPH_BASE_ADDR + 0x00004800UL )
#define USART4_BASE_ADDR                ( APB1PERIPH_BASE_ADDR + 0x00004C00UL )
#define USART5_BASE_ADDR                ( APB1PERIPH_BASE_ADDR + 0x00005000UL )
#define I2C1_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00005400UL )
#define I2C2_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00005800UL )
#define I2C3_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00005C00UL )
#define I2C4_BASE_ADDR                  ( APB1PERIPH_BASE_ADDR + 0x00006000UL )
#define PMU_BASE_ADDR                   ( APB1PERIPH_BASE_ADDR + 0x00007000UL )
#define LPTIM1_BASE_ADDR                ( APB1PERIPH_BASE_ADDR + 0x00007C00UL )
#define LPUART1_BASE_ADDR               ( APB1PERIPH_BASE_ADDR + 0x00008000UL )
#define LPTIM2_BASE_ADDR                ( APB1PERIPH_BASE_ADDR + 0x00009400UL )
#define USART7_BASE_ADDR                ( APB1PERIPH_BASE_ADDR + 0x00009800UL )
#define USART8_BASE_ADDR                ( APB1PERIPH_BASE_ADDR + 0x00009C00UL )
#define TIM25_BASE_ADDR                 ( APB1PERIPH_BASE_ADDR + 0x0000A000UL )
#define TIM26_BASE_ADDR                 ( APB1PERIPH_BASE_ADDR + 0x0000A400UL )
#define EFUSE1_BASE_ADDR                ( APB1PERIPH_BASE_ADDR + 0x0000E000UL )
#define EFUSE2_BASE_ADDR                ( APB1PERIPH_BASE_ADDR + 0x0000E800UL )

/*----------------------------  APB2 peripherals  ----------------------------*/

#define SYSCFG_BASE_ADDR                ( APB2PERIPH_BASE_ADDR + 0x00000000UL )
#define COMP1_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x00000200UL )
#define EXTI_BASE_ADDR                  ( APB2PERIPH_BASE_ADDR + 0x00000400UL )
#define TIM1_BASE_ADDR                  ( APB2PERIPH_BASE_ADDR + 0x00002C00UL )
#define TIM8_BASE_ADDR                  ( APB2PERIPH_BASE_ADDR + 0x00003400UL )
#define USART1_BASE_ADDR                ( APB2PERIPH_BASE_ADDR + 0x00003800UL )
#define USART6_BASE_ADDR                ( APB2PERIPH_BASE_ADDR + 0x00003C00UL )
#define TIM15_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x00004000UL )
#define TIM16_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x00004400UL )
#define TIM17_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x00004800UL )
#define TIM20_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x00005000UL )
#define TKEY_BASE_ADDR				    ( APB2PERIPH_BASE_ADDR + 0x00006400UL )
#define LTDC_BASE_ADDR                  ( APB2PERIPH_BASE_ADDR + 0x00006800UL )
#define TIM9_BASE_ADDR                  ( APB2PERIPH_BASE_ADDR + 0x00008000UL )
#define TIM10_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x00008400UL )
#define TIM11_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x00008800UL )
#define TIM18_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x00009000UL )
#define TIM19_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x00009400UL )
#define TIM21_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x00009C00UL )
#define TIM22_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x0000A000UL )
#define TIM23_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x0000A400UL )
#define TIM24_BASE_ADDR                 ( APB2PERIPH_BASE_ADDR + 0x0000A800UL )
#define USART9_BASE_ADDR                ( APB2PERIPH_BASE_ADDR + 0x0000B000UL )
#define USART10_BASE_ADDR               ( APB2PERIPH_BASE_ADDR + 0x0000B400UL )

/*----------------------------  APB3 peripherals  ----------------------------*/

#define LPTIM3_BASE_ADDR                ( APB3PERIPH_BASE_ADDR + 0x00000000UL )
#define LPTIM4_BASE_ADDR                ( APB3PERIPH_BASE_ADDR + 0x00000400UL )
#define LPTIM5_BASE_ADDR                ( APB3PERIPH_BASE_ADDR + 0x00000800UL )
#define LPTIM6_BASE_ADDR                ( APB3PERIPH_BASE_ADDR + 0x00000C00UL )

/*----------------------------  APB4 peripherals  ----------------------------*/

#define STM1_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00000000UL )
#define STM2_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00000400UL )
#define DCM1_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00000800UL )
#define DCM2_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00000C00UL )
#define DCM3_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00001000UL )
#define DCM4_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00001400UL )
#define NDL_BASE_ADDR                   ( APB4PERIPH_BASE_ADDR + 0x00001800UL )
#define MDAC_BASE_ADDR                  ( APB4PERIPH_BASE_ADDR + 0x00001C00UL )
#define STM3_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00002000UL )
#define STM4_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00002400UL )
#define STM5_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00002800UL )
#define STM6_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00002C00UL )
#define DCM5_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00003000UL )
#define DCM6_PWM_BASE_ADDR              ( APB4PERIPH_BASE_ADDR + 0x00003400UL )
#define LPT_BASE_ADDR                   ( APB4PERIPH_BASE_ADDR + 0x00003800UL )

#define DCMPWM1_AREA1_ADDR              (DCM1_PWM_BASE_ADDR+0x00)
#define DCMPWM2_AREA1_ADDR              (DCM2_PWM_BASE_ADDR+0x00)
#define DCMPWM3_AREA1_ADDR              (DCM3_PWM_BASE_ADDR+0x00)
#define DCMPWM4_AREA1_ADDR              (DCM4_PWM_BASE_ADDR+0x00)
#define DCMPWM5_AREA1_ADDR              (DCM5_PWM_BASE_ADDR+0x00)
#define DCMPWM6_AREA1_ADDR              (DCM6_PWM_BASE_ADDR+0x00)

#define DCMPWM1_AREA2_ADDR              (DCM1_PWM_BASE_ADDR+0x0C)
#define DCMPWM2_AREA2_ADDR              (DCM2_PWM_BASE_ADDR+0x0C)
#define DCMPWM3_AREA2_ADDR              (DCM3_PWM_BASE_ADDR+0x0C)
#define DCMPWM4_AREA2_ADDR              (DCM4_PWM_BASE_ADDR+0x0C)
// DCM5,DCM6Îª¾«¼ò°æ£¬ÎÞAREA2¼Ä´æÆ÷

#define DCMPWM1_AREA3_ADDR              (DCM1_PWM_BASE_ADDR+0x38)
#define DCMPWM2_AREA3_ADDR              (DCM2_PWM_BASE_ADDR+0x38)
#define DCMPWM3_AREA3_ADDR              (DCM3_PWM_BASE_ADDR+0x38)
#define DCMPWM4_AREA3_ADDR              (DCM4_PWM_BASE_ADDR+0x38)
#define DCMPWM5_AREA3_ADDR              (DCM5_PWM_BASE_ADDR+0x0C)
#define DCMPWM6_AREA3_ADDR              (DCM6_PWM_BASE_ADDR+0x0C)

/*----------------------------  AHB1 peripherals  ----------------------------*/

#define DMA1_BASE_ADDR                  ( AHB1PERIPH_BASE_ADDR + 0x00000000UL )
#define DMA1_CHANNEL0_BASE_ADDR         ( DMA1_BASE_ADDR + 0x00000100UL )
#define DMA1_CHANNEL1_BASE_ADDR         ( DMA1_BASE_ADDR + 0x00000120UL )
#define DMA1_CHANNEL2_BASE_ADDR         ( DMA1_BASE_ADDR + 0x00000140UL )
#define DMA1_CHANNEL3_BASE_ADDR         ( DMA1_BASE_ADDR + 0x00000160UL )
#define DMA1_CHANNEL4_BASE_ADDR         ( DMA1_BASE_ADDR + 0x00000180UL )
#define DMA1_CHANNEL5_BASE_ADDR         ( DMA1_BASE_ADDR + 0x000001A0UL )
#define DMA1_CHANNEL6_BASE_ADDR         ( DMA1_BASE_ADDR + 0x000001C0UL )
#define DMA1_CHANNEL7_BASE_ADDR         ( DMA1_BASE_ADDR + 0x000001E0UL )
#define DMA2_BASE_ADDR                  ( AHB1PERIPH_BASE_ADDR + 0x00000400UL )
#define DMA2_CHANNEL0_BASE_ADDR         ( DMA2_BASE_ADDR + 0x00000100UL )
#define DMA2_CHANNEL1_BASE_ADDR         ( DMA2_BASE_ADDR + 0x00000120UL )
#define DMA2_CHANNEL2_BASE_ADDR         ( DMA2_BASE_ADDR + 0x00000140UL )
#define DMA2_CHANNEL3_BASE_ADDR         ( DMA2_BASE_ADDR + 0x00000160UL )
#define DMA2_CHANNEL4_BASE_ADDR         ( DMA2_BASE_ADDR + 0x00000180UL )
#define DMA2_CHANNEL5_BASE_ADDR         ( DMA2_BASE_ADDR + 0x000001A0UL )
#define DMA2_CHANNEL6_BASE_ADDR         ( DMA2_BASE_ADDR + 0x000001C0UL )
#define DMA2_CHANNEL7_BASE_ADDR         ( DMA2_BASE_ADDR + 0x000001E0UL )
#define RCC_BASE_ADDR                   ( AHB1PERIPH_BASE_ADDR + 0x00001000UL )
#define FDCAN1_BASE_ADDR                ( AHB1PERIPH_BASE_ADDR + 0x00002000UL )
#define FDCAN2_BASE_ADDR                ( AHB1PERIPH_BASE_ADDR + 0x00002400UL )
#define CRC_BASE_ADDR                   ( AHB1PERIPH_BASE_ADDR + 0x00003000UL )
#define ETHMAC_BASE_ADDR                ( AHB1PERIPH_BASE_ADDR + 0x00008000UL )
#define DMA2D_BASE_ADDR                 ( AHB1PERIPH_BASE_ADDR + 0x0000B000UL )
#define SPI1_BASE_ADDR                  ( AHB1PERIPH_BASE_ADDR + 0x00010000UL )
#define SPI2_BASE_ADDR                  ( AHB1PERIPH_BASE_ADDR + 0x00010400UL )
#define SPI3_BASE_ADDR                  ( AHB1PERIPH_BASE_ADDR + 0x00010800UL )
#define SPI4_BASE_ADDR                  ( AHB1PERIPH_BASE_ADDR + 0x00010C00UL )
#define SPI5_BASE_ADDR                  ( AHB1PERIPH_BASE_ADDR + 0x00011000UL )
#define SPI6_BASE_ADDR                  ( AHB1PERIPH_BASE_ADDR + 0x00011400UL )
#define BKPSRAM_BASE_ADDR               ( AHB1PERIPH_BASE_ADDR + 0x00016400UL )
#define USBOTG_HS1_BASE_ADDR            ( AHB1PERIPH_BASE_ADDR + 0x00020000UL )
#define USBOTG_HS2_BASE_ADDR            ( AHB1PERIPH_BASE_ADDR + 0x00060000UL )
#define USBOTG1_PHYC_BASE_ADDR          ( AHB1PERIPH_BASE_ADDR + 0x000A0000UL )
#define USBOTG2_PHYC_BASE_ADDR          ( AHB1PERIPH_BASE_ADDR + 0x000A0400UL )

/*----------------------------  AHB2 peripherals  ----------------------------*/

#define GPIOA_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00000000UL )
#define GPIOB_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00000400UL )
#define GPIOC_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00000800UL )
#define GPIOD_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00000C00UL )
#define GPIOE_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00001000UL )
#define GPIOF_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00001400UL )
#define GPIOG_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00001800UL )
#define GPIOH_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00001C00UL )
#define GPIOI_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00002000UL )
#define GPIOJ_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00002400UL )
#define GPIOK_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00002800UL )
#define GPIOL_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00002C00UL )
#define GPIOM_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00003000UL )
#define GPION_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00003400UL )
#define GPIOO_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00003800UL )
#define GPIOP_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00003C00UL )
#define GPIOQ_BASE_ADDR                 ( AHB2PERIPH_BASE_ADDR + 0x00004000UL )
#define ADC1_2_BASE_ADDR                ( AHB2PERIPH_BASE_ADDR + 0x08000000UL )
#define ADC1_BASE_ADDR                  ( AHB2PERIPH_BASE_ADDR + 0x08000000UL )
#define ADC2_BASE_ADDR                  ( AHB2PERIPH_BASE_ADDR + 0x08000100UL )
#define ADC3_BASE_ADDR                  ( AHB2PERIPH_BASE_ADDR + 0x08000400UL )
#define DAC1_BASE_ADDR                  ( AHB2PERIPH_BASE_ADDR + 0x08000800UL )
#define DAC2_BASE_ADDR                  ( AHB2PERIPH_BASE_ADDR + 0x08000C00UL )
#define FDCAN3_BASE_ADDR                ( AHB2PERIPH_BASE_ADDR + 0x08001400UL )
#define DCMI_BASE_ADDR                  ( AHB2PERIPH_BASE_ADDR + 0x08050000UL )
#define AES_BASE_ADDR                   ( AHB2PERIPH_BASE_ADDR + 0x08060000UL )
#define CORDIC_BASE_ADDR                ( AHB2PERIPH_BASE_ADDR + 0x08060400UL )
#define HRNG_BASE_ADDR                  ( AHB2PERIPH_BASE_ADDR + 0x08060800UL )
#define HASH_BASE_ADDR                  ( AHB2PERIPH_BASE_ADDR + 0x08060C00UL )
#define AES_SPI1_BASE_ADDR              ( AHB2PERIPH_BASE_ADDR + 0x08061000UL )

#define THM_BASE_ADDR                   ( AHB2PERIPH_BASE_ADDR + 0x08080000UL )
#define HEAD_BASE_ADDR			        (THM_BASE_ADDR	+ 0x00)
#define LUT_BASE_ADDR			 	    (THM_BASE_ADDR	+ 0x200)
#define DOT1_BASE_ADDR			        (THM_BASE_ADDR	+ 0x400)
#define DOT2_BASE_ADDR			        (THM_BASE_ADDR	+ 0x800)
#define DOT3_BASE_ADDR			        (THM_BASE_ADDR	+ 0xc00)
#define LCFG_BASE_ADDR			        (THM_BASE_ADDR	+ 0x2000)

/*----------------------------  AHB3 peripherals  ----------------------------*/

#define SPI7_BASE_ADDR                  ( AHB3PERIPH_BASE_ADDR + 0x00005000UL )
#define SPI8_BASE_ADDR                  ( AHB3PERIPH_BASE_ADDR + 0x00005400UL )
#define USB1_DLYB_REG_BASE_ADDR         ( AHB3PERIPH_BASE_ADDR + 0x00006800UL )
#define ETH_DLYB_REG_BASE_ADDR          ( AHB3PERIPH_BASE_ADDR + 0x00006C00UL )
#define SDIO_BASE_ADDR                  ( AHB3PERIPH_BASE_ADDR + 0x000C8000UL )
#define SDIO_DLYBS_REG_BASE_ADDR        ( AHB3PERIPH_BASE_ADDR + 0x000CA000UL )
#define SDIO_DLYBD_REG_BASE_ADDR        ( AHB3PERIPH_BASE_ADDR + 0x000CA800UL )
#define OSPI1_BASE_ADDR                 ( AHB3PERIPH_BASE_ADDR + 0x000D1400UL )
#define OSPI2_BASE_ADDR                 ( AHB3PERIPH_BASE_ADDR + 0x000D1800UL )
#define OSPI1_DLYB_REG_BASE_ADDR        ( AHB3PERIPH_BASE_ADDR + 0x000D2000UL )
#define OSPI2_DLYB_REG_BASE_ADDR        ( AHB3PERIPH_BASE_ADDR + 0x000D2400UL )

/*----------------------------  External Memory   ----------------------------*/

#define FMC_NORSRAM_BASE_ADDR           ( 0x60000000UL )
#define SDRAM1_SDRAM2_BASE_ADDR         ( 0x70000000UL )
#define OSPI1_MEM_BASE_ADDR             ( 0x80000000UL )
#define OSPI2_MEM_BASE_ADDR             ( 0x88000000UL )
#define SPI4_MEM_BASE_ADDR              ( 0x90000000UL )

/*--------------------------  External peripherals  --------------------------*/

#define FMC_REG_BASE_ADDR               ( 0xA0000000UL )
#define SDRAM1_NORSRAM_BASE_ADDR        ( 0xC0000000UL )
#define SDRAM2_BASE_ADDR                ( 0xD0000000UL )

/*---------------------  Peripheral_registers_structures  --------------------*/

/*---------------------------------  SYSCFG  ---------------------------------*/

typedef struct
{
    __IO uint32_t SYSCR;
    __IO uint32_t WMR;
    __IO uint32_t VER;
    __IO uint32_t RSV0C[1];
    __IO uint32_t PHYCFG;
    __IO uint32_t RSV14[1];
    __IO uint32_t RAMECCIR;    
    __IO uint32_t RAMECCSR;  
    __IO uint32_t RAMECCICR;     
    __IO uint32_t GPIO5VOCR1; 
    __IO uint32_t GPIO5VOCR2; 
    __IO uint32_t DFTCR; 
    __IO uint32_t JTAGCR; 
    __IO uint32_t IPDISR;
    __IO uint32_t BUSLOCK;

} SYSCFG_TypeDef; 

typedef struct
{
    __IO uint32_t RCR;
    __IO uint32_t RSR;
    __IO uint32_t AHB1RSTR;
    __IO uint32_t AHB2RSTR;
    __IO uint32_t AHB3RSTR;
    __IO uint32_t APB1RSTR1;
    __IO uint32_t APB1RSTR2;
    __IO uint32_t APB2RSTR;
    __IO uint32_t APB3RSTR;
    __IO uint32_t APB4RSTR;
    __IO uint32_t CCR1;
    __IO uint32_t CCR2;
    __IO uint32_t PERCFGR;
    __IO uint32_t CIR;
    __IO uint32_t AHB1CKENR;
    __IO uint32_t AHB2CKENR;
    __IO uint32_t AHB3CKENR;
    __IO uint32_t APB1CKENR1;
    __IO uint32_t APB1CKENR2;
    __IO uint32_t APB2CKENR;
    __IO uint32_t APB3CKENR;
    __IO uint32_t APB4CKENR;
    __IO uint32_t RCHCR;
    __IO uint32_t XTHCR;
    __IO uint32_t PLL1CR;
    __IO uint32_t PLL1CFR;
    __IO uint32_t PLL1SCR;
    __IO uint32_t PLL2CR;
    __IO uint32_t PLL2CFR;
    __IO uint32_t PLL2SCR;
    __IO uint32_t PLL3CR;
    __IO uint32_t PLL3CFR;
    __IO uint32_t RSV80;
    __IO uint32_t CLKOCR;
    __IO uint32_t DCKCFG;
    __IO uint32_t STDBYCTRL;

} RCC_TypeDef;

typedef struct
{
    __IO uint32_t MD;
    __IO uint32_t OTYP;
    __IO uint32_t PUPD;
    __IO uint32_t IDATA;
    __IO uint32_t ODATA;
    __IO uint32_t BSC;
    __IO uint32_t AF0;
    __IO uint32_t AF1;
    __IO uint32_t DS0;
    __IO uint32_t DS1;
    __IO uint32_t SMIT;
    __IO uint32_t LOCK;
    __IO uint32_t AIEN;

} GPIO_TypeDef;

typedef struct
{
    __IO uint32_t IENR1;
    __IO uint32_t IENR2;
    __IO uint32_t EENR1;
    __IO uint32_t EENR2;
    __IO uint32_t RTENR1;
    __IO uint32_t RTENR2;
    __IO uint32_t FTENR1;
    __IO uint32_t FTENR2;
    __IO uint32_t SWIER1;
    __IO uint32_t SWIER2;
    __IO uint32_t PDR1;
    __IO uint32_t PDR2;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t CR3;

} EXTI_TypeDef;; 

typedef struct
{
    __IO uint32_t INTSTATUS;
    __IO uint32_t INTTCSTATUS;
    __IO uint32_t INTTCCLR;
    __IO uint32_t INTERRSTATUS;
    __IO uint32_t INTERRCLR;
    __IO uint32_t RAWINTTCSTATUS;
    __IO uint32_t RAWINTERRSTATUS;
    __IO uint32_t ENCHSTATUS;
    __IO uint32_t RSV0[4];
    __IO uint32_t CONFIG;
    __IO uint32_t SYNCLO;
    __IO uint32_t SYNCHI;
    
} DMA_TypeDef;  


typedef struct
{
    __IO uint32_t CXSRCADDR;
    __IO uint32_t CXDESTADDR;
    __IO uint32_t CXLLI;
    __IO uint32_t CXCTRL;
    __IO uint32_t CXCONFIG;
    
} DMA_Channel_TypeDef;

typedef struct
{
    __IO uint32_t DR;
    __IO uint32_t FR;
    __IO uint32_t BRR;
    __IO uint32_t IE;
    __IO uint32_t ISR;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t CR3;
    __IO uint32_t GTPR;
    __IO uint32_t BCNT;

} USART_TypeDef;  

/*------------------- SPI  ----------------------*/
typedef struct _SPI_MEMO_ACC
{
__IO uint32_t	acc_en:1;
     uint32_t   cs_tout_en:1;
	 uint32_t	rsv4:1;
	 uint32_t	crm_en:1;
	 uint32_t	instr_once:1;
	 uint32_t	wr_ab_en:1;
	 uint32_t	rd_ab_en:1;
	 uint32_t	alter_byte_size:2;
	 uint32_t	rsv3:1;
	 uint32_t	wr_db_en:1;
	 uint32_t	rd_db_en:1;
	 uint32_t	dummy_cycle:3;
	 uint32_t	rsv2:2;
	 uint32_t   addr_size:2;
	 uint32_t	instr_mode:2;
	 uint32_t	addr_mode:2;
	 uint32_t	alter_byte_mode:2;
	 uint32_t	data_mode:2;
     uint32_t   instr_once_clr:1;
	 uint32_t   rsv1:4;
	
} SPI_MEMO_ACC_t;

typedef struct _SPI_MEM_CMD
{
	__IO uint32_t rd_cmd:8;
	__IO uint32_t wr_cmd:8;
	__IO uint32_t rsv:16;
} SPI_MEM_CMD_t;

typedef struct
{
    __IO uint32_t DAT;      //0x00
    __IO uint32_t BAUD;     //0x04
    __IO uint32_t CTL;      //0x08
    __IO uint32_t TX_CTL;   //0x0C
    __IO uint32_t RX_CTL;   //0x10
    __IO uint32_t IE;       //0x14
    __IO uint32_t STATUS;   //0x18
    __IO uint32_t TX_DELAY; //0x1C
    __IO uint32_t BATCH;    //0x20
    __IO uint32_t CS;       //0x24
    __IO uint32_t OUT_EN;   //0x28
    SPI_MEMO_ACC_t MEMO_ACC;  //2C
    SPI_MEM_CMD_t CMD;        //30
    __IO uint32_t ALTER_BYTE; //34
    __IO uint32_t CS_TOUT_VAL;//38
} SPI_TypeDef;

/*------------------- I2C  ----------------------*/
typedef struct
{
    __IO uint32_t SLAVE_ADDR1;      //0x00
    __IO uint32_t CLK_DIV;          //0x04
    __IO uint32_t CR;               //0x08
    __IO uint32_t SR;               //0x0C
    __IO uint32_t DR;               //0x10
    __IO uint32_t SLAVE_ADDR2_3;    //0x14
    __IO uint32_t DET;              //0x18
    __IO uint32_t FILTER;           //0x1C
    __IO uint32_t RSV1;             //0x20
    __IO uint32_t TIMEOUT;          //0x24
} I2C_TypeDef;


///////////////////////////////////////////////////////////////////////////////////
/* FDCAN timming */
typedef union
{
    struct{
        __IO uint32_t SEG1:8;
        __IO uint32_t SEG2:8;
        __IO uint32_t SJW:8;
        __IO uint32_t PRESC:8;
    }b;
    __IO uint32_t w;
}fdcan_btr_u;

/* FDCAN error cnt */
typedef union
{
    struct{
        __IO uint32_t ALC:5;     
        __IO uint32_t KOER:3;
        __IO uint32_t RSV:8;
        __IO uint32_t RECNT:8;
        __IO uint32_t TECNT:8;
    }b;
    __IO uint32_t w;
}fdcan_ecc_u;

typedef union
{
    struct{
        __IO uint32_t ACFADR:4;
        __IO uint32_t RSV:1;
        __IO uint32_t SELMASK:1;
        __IO uint32_t RSV1:10;
        __IO uint32_t AE:16;
    }b;
    __IO uint32_t w;
}fdcan_acfctrl_u;

typedef union
{
    struct{
        __IO uint32_t ACM:29;   //Acceptance Code or Mask
        __IO uint32_t AIDE:1;
        __IO uint32_t AIDEE:1;
        __IO uint32_t RSV:1;
    }b;
    __IO uint32_t w;
}fdcan_acodr_u;



typedef union
{
    struct{
         uint32_t REF_ID:29;
         uint32_t RSV:2;
         uint32_t REF_IDE:1;
    }b;
    __IO uint32_t w;
}ttcan_refmsg_u;

typedef union
{
    struct{
        __IO uint32_t TRIGCFG0:8;
        __IO uint32_t TRIGCFG1:8;
        __IO uint32_t TRIG0:8;
        __IO uint32_t TRIG1:8;
    }b;
    __IO uint32_t w;
}ttcan_trig_ctrl_u;


typedef union
{
    struct{
        __IO uint32_t TTPTR:6;
        __IO uint32_t RSV:2;
        __IO uint32_t TTYPE:3;
        __IO uint32_t RSV1:1;
        __IO uint32_t TEW:4;
        __IO uint32_t RSV2:16;
    }b;
    __IO uint32_t w;
}ttcan_trig_cfg_u;

typedef union
{
    struct{
        __IO uint32_t WTRIG0:8;
        __IO uint32_t WTRIG1:8;
        __IO uint32_t RSV:16;
    }b;
    __IO uint32_t w;
}ttcan_wtrig_u;


typedef struct
{
    __IO uint32_t           RBUF[20]; 
    __IO uint32_t           TBUF[18];   //50
    __IO uint32_t           TTSL;       //98
    __IO uint32_t           TTSH;       //9C
    __IO uint32_t           CR;         //A0
    __IO uint32_t           IR;         //A4
    __IO uint32_t           LIMIT;      //A8
    __IO fdcan_btr_u        SBTR;       //AC
    __IO fdcan_btr_u        FBTR;       //B0
    __IO uint32_t           TDC;        //B4
    __IO fdcan_ecc_u        ECC;        //B8
    __IO fdcan_acfctrl_u    ACFCR;      //BC
    __IO uint32_t           ACFMODE;    //C0
    __IO uint32_t           ACODR;      //C4
    __IO uint32_t           TIMECFG;    //C8
    __IO uint32_t           TTCFG;      //CC
    __IO ttcan_refmsg_u     TTREFMSG;   //D0
    __IO ttcan_trig_cfg_u   TTTRIGCFG;  //D4
    __IO uint32_t           TTTRIG;     //D8
    __IO ttcan_wtrig_u      TTWTRIGR;   //DC
    
}FDCAN_GlobalTypeDef;

///*------------------- LPUART Registers ----------------------*/
typedef struct
{
    __IO uint32_t RXDR;     // 0x00
    __IO uint32_t TXDR;     // 0x04
    __IO uint32_t LCR;      // 0x08
    __IO uint32_t CR;       // 0x0C
    __IO uint32_t IBAUD;    // 0x10
    __IO uint32_t FBAUD;    // 0x14
    __IO uint32_t IE;       // 0x18
    __IO uint32_t SR;       // 0x1C
    __IO uint32_t ADDR;     // 0x20
} LPUART_TypeDef;

typedef struct
{
    __IO uint32_t TXDR;
    __IO uint32_t RXDR;
    __IO uint32_t CR;
    __IO uint32_t PR;
    __IO uint32_t DIER;
    __IO uint32_t SR;
    __IO uint32_t RSV18;
    __IO uint32_t RSIZE;

} I2S_TypeDef;  

typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t CFGR;

} DLYB_TypeDef;  

typedef struct
{
    __IO uint32_t MACCR;
    __IO uint32_t MACFFR;
    __IO uint32_t MACHTHR;
    __IO uint32_t MACHTLR;
    __IO uint32_t MACMIIAR;
    __IO uint32_t MACMIIDR;
    __IO uint32_t MACFCR;
    __IO uint32_t MACVLANTR;
    __IO uint32_t RSV0020[1];
    __IO uint32_t MACDBGR;
    __IO uint32_t MACRWUFF;
    __IO uint32_t MACPMTCSR;
    __IO uint32_t MACLPICSR;
    __IO uint32_t MACLPITCR;
    __IO uint32_t MACISR;
    __IO uint32_t MACIMR;
    __IO uint32_t MACA0HR;
    __IO uint32_t MACA0LR;
    __IO uint32_t MACA1HR;
    __IO uint32_t MACA1LR;
    __IO uint32_t MACA2HR;
    __IO uint32_t MACA2LR;
    __IO uint32_t MACA3HR;
    __IO uint32_t MACA3LR;
    __IO uint32_t RSV0060[31];
    __IO uint32_t MACWTR;
    __IO uint32_t RSV00E0[8];
    __IO uint32_t MMCCR;
    __IO uint32_t MMCRIR;
    __IO uint32_t MMCTIR;
    __IO uint32_t MMCRIMR;
    __IO uint32_t MMCTIMR;
    __IO uint32_t RSV0114[14];
    __IO uint32_t MMCTGFSCCR;
    __IO uint32_t MMCTGFMCCR;
    __IO uint32_t RSV0154[5];
    __IO uint32_t MMCTGFCR;
    __IO uint32_t RSV016C[10];
    __IO uint32_t MMCRFCECR;
    __IO uint32_t MMCRFAECR;
    __IO uint32_t RSV019C[10];
    __IO uint32_t MMCRGUFCR;
    __IO uint32_t RSV01C8[142];
    __IO uint32_t MACL3L4C0R;
    __IO uint32_t MACL4A0R;
    __IO uint32_t RSV0408[2];
    __IO uint32_t MACL3A00R;
    __IO uint32_t MACL3A10R;
    __IO uint32_t MACL3A20R;
    __IO uint32_t MACL3A30R;
    __IO uint32_t RSV0420[4];
    __IO uint32_t MACL3L4C1R;
    __IO uint32_t MACL4A1R;
    __IO uint32_t RSV0438[2];
    __IO uint32_t MACL3A01R;
    __IO uint32_t MACL3A11R;
    __IO uint32_t MACL3A21R;
    __IO uint32_t MACL3A31R;
    __IO uint32_t RSV0450[77];
    __IO uint32_t MACVTIRR;
    __IO uint32_t MACVHTR;
    __IO uint32_t RSV058C[93];
    __IO uint32_t PTPTSCR;
    __IO uint32_t PTPSSIR;
    __IO uint32_t PTPTSHR;
    __IO uint32_t PTPTSLR;
    __IO uint32_t PTPTSHUR;
    __IO uint32_t PTPTSLUR;
    __IO uint32_t PTPTSAR;
    __IO uint32_t PTPTTHR;
    __IO uint32_t PTPTTLR;
    __IO uint32_t RSV0724[1];
    __IO uint32_t PTPTSSR;
    __IO uint32_t PTPPPSCR;
    __IO uint32_t PTPATSNR;
    __IO uint32_t PTPATSSR;
    __IO uint32_t RSV0738[10];
    __IO uint32_t PTPPPSIR;
    __IO uint32_t PTPPPSWR;
    __IO uint32_t RSV0768[550];
    __IO uint32_t DMABMR;
    __IO uint32_t DMATPDR;
    __IO uint32_t DMARPDR;
    __IO uint32_t DMARDLAR;
    __IO uint32_t DMATDLAR;
    __IO uint32_t DMASR;
    __IO uint32_t DMAOMR;
    __IO uint32_t DMAIER;
    __IO uint32_t DMAMFBOCR;
    __IO uint32_t DMARIWTR;
    __IO uint32_t RSV1028[8];
    __IO uint32_t DMACHTDR;
    __IO uint32_t DMACHRDR;
    __IO uint32_t DMACHTBAR;
    __IO uint32_t DMACHRBAR;

} ETH_TypeDef;  

///*------------------- PMU  ----------------------*/
typedef struct
{
    __IO uint32_t CTRL0;
    __IO uint32_t CTRL1;
    __IO uint32_t CTRL2;
    __IO uint32_t CTRL3;
    __IO uint32_t SR;
    __IO uint32_t STCLR;
    __IO uint32_t IOSEL;
    __IO uint32_t RSV0[41];
    __IO uint32_t TEST_ANATEST_SR;
    __IO uint32_t TEST_LDOCAL;
    __IO uint32_t TEST_LDOCR;

} PMU_TypeDef; 

///*------------------- RTC  ----------------------*/
typedef struct
{
    __IO uint32_t WP;
    __IO uint32_t IE;
    __IO uint32_t SR;
    __IO uint32_t SEC;
    __IO uint32_t MIN;
    __IO uint32_t HOUR;
    __IO uint32_t DAY;
    __IO uint32_t WEEK;
    __IO uint32_t MONTH;
    __IO uint32_t YEAR;
    __IO uint32_t ALM;
    __IO uint32_t CR;
    __IO uint32_t ADJUST;
    __IO uint32_t RSV0[2];
    __IO uint32_t MSECCNT;
    __IO uint32_t RSV1[1];
    __IO uint32_t CLKSTAMP1;
    __IO uint32_t CALSTAMP1;
    __IO uint32_t CLKSTAMP2;
    __IO uint32_t CALSTAMP2;
    __IO uint32_t WUTR;
    __IO uint32_t RSV2[6];
    __IO uint32_t BAKUP[16];
} RTC_TypeDef; 

///*------------------- WDT  ----------------------*/
typedef struct
{
    __IO uint32_t LOAD;
    __IO uint32_t COUNT;
    __IO uint32_t CTRL;
    __IO uint32_t FEED;
    __IO uint32_t INTCLRTIME;
    __IO uint32_t RIS;

} WDT_TypeDef; 

///*------------------- IWDT  ----------------------*/
typedef struct
{
    __IO uint32_t CMDR;
    __IO uint32_t PR;
    __IO uint32_t RLR;
    __IO uint32_t SR;
    __IO uint32_t WINR;
    __IO uint32_t WUTR;

} IWDT_TypeDef; 

///*------------------- ADC  ----------------------*/
typedef struct
{
    __IO uint32_t SR;
    __IO uint32_t IE;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SMPR1;
    __IO uint32_t SMPR2;
    __IO uint32_t SMPR3;
    __IO uint32_t HTR;
    __IO uint32_t LTR;
    __IO uint32_t SQR1;
    __IO uint32_t SQR2;
    __IO uint32_t SQR3;
    __IO uint32_t JSQR;
    __IO uint32_t JDR[4];
    __IO uint32_t RSV0[1];
    __IO uint32_t DR;
    __IO uint32_t DIFSEL;
    __IO uint32_t RSV1[4];
    __IO uint32_t OFR[4];
    __IO uint32_t RSV2[5];
    __IO uint32_t CALFACT;
    __IO uint32_t CHDR[9];
    __IO uint32_t TEST_DATA[10];
} ADC_TypeDef; 

typedef struct
{
    __IO uint32_t CSR;       
    __IO uint32_t CCR;       
    __IO uint32_t CDR;        
    __IO uint32_t CVRB;     
} ADC_Common_TypeDef;

///*------------------- DAC  ----------------------*/
typedef struct
{
    __IO uint32_t CR;       //0x00
    __IO uint32_t SWTRIGR;  //0x04
    __IO uint32_t DHR12R1;  //0x08
    __IO uint32_t DHR12L1;  //0x0C
    __IO uint32_t DHR8R1;   //0x10
    __IO uint32_t DHR12R2;  //0x14
    __IO uint32_t DHR12L2;  //0x18
    __IO uint32_t DHR8R2;   //0x1C
    __IO uint32_t DHR12RD;  //0x20
    __IO uint32_t DHR12LD;  //0x24
    __IO uint32_t DHR8RD;   //0x28
    __IO uint32_t DOR1;     //0x2C
    __IO uint32_t DOR2;     //0x30
    __IO uint32_t SR;       //0x34
    __IO uint32_t CCR;      //0x38
    __IO uint32_t MCR;      //0x3C
    __IO uint32_t SHSR1;    //0x40
    __IO uint32_t SHSR2;    //0x44
    __IO uint32_t SHHR;     //0x48
    __IO uint32_t SHRR;     //0x4C
    __IO uint32_t RSV[2];   //0x50~0x54
    __IO uint32_t STR1;     //0x58
    __IO uint32_t STR2;     //0x5C
    __IO uint32_t STMODR;   //0x60
} DAC_TypeDef; 

///*------------------- MDAC  ----------------------*/
typedef struct{    
    __IO uint32_t VDACx_CTRL[12];   //0x00~0x2c
    __IO uint32_t IDACx_CTRL[4];    //0x30~0x3c
    __IO uint32_t DACx_DOR[16];     //0x40~0x7c    
} MDAC_TypeDef;
 

///*------------------- TKEY  ----------------------*/
typedef struct
{
    __IO uint32_t SR;
    __IO uint32_t IER;
    __IO uint32_t CR;
    __IO uint32_t CFGR1;
    __IO uint32_t CFGR2;
    __IO uint32_t INTVLR;
    __IO uint32_t DIVR;
    __IO uint32_t SCCR;
    __IO uint32_t TSETR;
    __IO uint32_t CXENR;
    __IO uint32_t DR;
    __IO uint32_t TH[16];
    __IO uint32_t CH[16];
    __IO uint32_t CFLTR;
    __IO uint32_t NSETR;
    __IO uint32_t TWAITR;
    __IO uint32_t MUTUALR;
    __IO uint32_t TXENR[2];

} TKEY_TypeDef;  

///*------------------- OSPI  ----------------------*/
typedef struct
{
    __IO uint32_t DAT;      
    __IO uint32_t BAUD;     
    __IO uint32_t CTL;     
    __IO uint32_t TX_CTL;   
    __IO uint32_t RX_CTL;   
    __IO uint32_t IE;       
    __IO uint32_t STATUS;   
    __IO uint32_t TX_DELAY; 
    __IO uint32_t BATCH;    
    __IO uint32_t CS;       
    __IO uint32_t OUT_EN;
    __IO uint32_t MEMO_ACC1;
    __IO uint32_t CMD;       
    __IO uint32_t ALTER_BYTE; 
    __IO uint32_t CS_TIMEOUT_VAL;  
    __IO uint32_t MEMO_ACC2;
} OSPI_TypeDef; 

///*------------------- FMC  ----------------------*/      
typedef struct
{
    __IO uint32_t SNCTLCFG[8];
    __IO uint32_t RSV0[57];
    __IO uint32_t SNWTCFG[7];

} FMC_NORSRAM_TypeDef;

typedef struct
{
    __IO uint32_t SDRCR[2];
    __IO uint32_t SDRTR[2];
    __IO uint32_t SDRCMD;
    __IO uint32_t SDRART;
    __IO uint32_t SDRSR;
    __IO uint32_t SDRSMA1;
    __IO uint32_t SDRSMA2;

} FMC_SDRAM_TypeDef;    


typedef struct
{
    __IO uint32_t CR1;      // 0x00
    __IO uint32_t CR2;      // 0x04
    __IO uint32_t SMCR;     // 0x08
    __IO uint32_t DIER;     // 0x0C
    __IO uint32_t SR;       // 0x10
    __IO uint32_t EGR;      // 0x14
    __IO uint32_t CCMR1;    // 0x18
    __IO uint32_t CCMR2;    // 0x1C
    __IO uint32_t CCER;     // 0x20
    __IO uint32_t CNT;      // 0x24
    __IO uint32_t PSC;      // 0x28
    __IO uint32_t ARR;      // 0x2C
    __IO uint32_t RCR;      // 0x30
    __IO uint32_t CCR1;     // 0x34
    __IO uint32_t CCR2;     // 0x38
    __IO uint32_t CCR3;     // 0x3C
    __IO uint32_t CCR4;     // 0x40
    __IO uint32_t BDTR;     // 0x44
    __IO uint32_t DCR;      // 0x48
    __IO uint32_t DMAR;     // 0x4C
    __IO uint32_t OR1;      // 0x50
    __IO uint32_t CCMR3;    // 0x54
    __IO uint32_t CCR5;     // 0x58
    __IO uint32_t CCR6;     // 0x5C
    __IO uint32_t AF1;      // 0x60
    __IO uint32_t AF2;      // 0x64
    __IO uint32_t TISEL;    // 0x68
    __IO uint32_t DBER;     // 0x6C
} TIM_TypeDef;

typedef struct
{
    __IO uint32_t CTRL;      // 0x00
    __IO uint32_t SR;        // 0x04  
    __IO uint32_t ARR_LOW;   // 0x08 
    __IO uint32_t ARR_HIGH;  // 0x0c   
    __IO uint32_t CNT_LOW;   // 0x10 
    __IO uint32_t CNT_HIGH;  // 0x14  
} TIM_64BIT_TypeDef;  


typedef struct
{
 __IO uint32_t  GOTGCTL;               /*!< USB_OTG Control and Status Register          000h */
  __IO uint32_t GOTGINT;              /*!< USB_OTG Interrupt Register                   004h */
  __IO uint32_t GAHBCFG;              /*!< Core AHB Configuration Register              008h */
  __IO uint32_t GUSBCFG;              /*!< Core USB Configuration Register              00Ch */
  __IO uint32_t GRSTCTL;              /*!< Core Reset Register                          010h */
  __IO uint32_t GINTSTS;              /*!< Core Interrupt Register                      014h */
  __IO uint32_t GINTMSK;              /*!< Core Interrupt Mask Register                 018h */
  __IO uint32_t GRXSTSR;              /*!< Receive Sts Q Read Register                  01Ch */
  __IO uint32_t GRXSTSP;              /*!< Receive Sts Q Read & POP Register            020h */
  __IO uint32_t GRXFSIZ;              /*!< Receive FIFO Size Register                   024h */
  __IO uint32_t DIEPTXF0_HNPTXFSIZ;   /*!< EP0 / Non Periodic Tx FIFO Size Register     028h */
  __IO uint32_t HNPTXSTS;             /*!< Non Periodic Tx FIFO/Queue Sts reg           02Ch */
  uint32_t Reserved30[2];             /*!< Reserved                                     030h */
  __IO uint32_t GGPIO;                /*!< General Purpose IO Register                  038h */
  __IO uint32_t CID;                  /*!< User ID Register                             03Ch */
  uint32_t  Reserved5[3];             /*!< Reserved                                040h-048h */
  __IO uint32_t GHWCFG3;              /*!< User HW config3                              04Ch */
  uint32_t  Reserved6;                /*!< Reserved                                     050h */
  __IO uint32_t GLPMCFG;              /*!< LPM Register                                 054h */
  uint32_t  Reserved7;                /*!< Reserved                                     058h */
  __IO uint32_t GDFIFOCFG;            /*!< DFIFO Software Config Register               05Ch */
  uint32_t  Reserved43[40];           /*!< Reserved                                 60h-0FFh */
  
  __IO uint32_t HPTXFSIZ;             /*!< Host Periodic Tx FIFO Size Reg               100h */
  __IO uint32_t DIEPTXF[0x0F];        /*!< dev Periodic Transmit FIFO              104h-13Ch */
} USB_OTG_GlobalTypeDef;


typedef struct
{
    __IO uint32_t TR0;       //00 
    __IO uint32_t TR1;       //04      
    __IO uint32_t TR2;       //08     
    __IO uint32_t TR3;       //0C  
    __IO uint32_t TR4;       //10
    __IO uint32_t TR5;       //14    
    __IO uint32_t TR6;       //18  
    __IO uint32_t TR7;       //1C
    __IO uint32_t RSV0[2];   //20
    __IO uint32_t TR8;       //28
    __IO uint32_t TR9;       //2C    
    __IO uint32_t RSV1[20];  //30      
    __IO uint32_t CR;        //80   
} USB_HS_PHYC_GlobalTypeDef;

typedef struct
{
  __IO uint32_t DCFG;            /*!< dev Configuration Register   800h */
  __IO uint32_t DCTL;            /*!< dev Control Register         804h */
  __IO uint32_t DSTS;            /*!< dev Status Register (RO)     808h */
  uint32_t Reserved0C;           /*!< Reserved                     80Ch */
  __IO uint32_t DIEPMSK;         /*!< dev IN Endpoint Mask         810h */
  __IO uint32_t DOEPMSK;         /*!< dev OUT Endpoint Mask        814h */
  __IO uint32_t DAINT;           /*!< dev All Endpoints Itr Reg    818h */
  __IO uint32_t DAINTMSK;        /*!< dev All Endpoints Itr Mask   81Ch */
  uint32_t  Reserved20;          /*!< Reserved                     820h */
  uint32_t Reserved9;            /*!< Reserved                     824h */
  __IO uint32_t DVBUSDIS;        /*!< dev VBUS discharge Register  828h */
  __IO uint32_t DVBUSPULSE;      /*!< dev VBUS Pulse Register      82Ch */
  __IO uint32_t DTHRCTL;         /*!< dev threshold                830h */
  __IO uint32_t DIEPEMPMSK;      /*!< dev empty msk                834h */
  __IO uint32_t DEACHINT;        /*!< dedicated EP interrupt       838h */
  __IO uint32_t DEACHMSK;        /*!< dedicated EP msk             83Ch */
  __IO uint32_t DINEP0MSK;           /*!< dedicated EP mask            840h */
  __IO uint32_t DINEP1MSK;       /*!< dedicated EP mask            844h */
  uint32_t  Reserved44[15];      /*!< Reserved                 844-87Ch */
  __IO uint32_t DOUTEP1MSK;      /*!< dedicated EP msk             884h */
} USB_OTG_DeviceTypeDef;

typedef struct
{
  __IO uint32_t DIEPCTL;           /*!< dev IN Endpoint Control Reg    900h + (ep_num * 20h) + 00h */
  uint32_t Reserved04;             /*!< Reserved                       900h + (ep_num * 20h) + 04h */
  __IO uint32_t DIEPINT;           /*!< dev IN Endpoint Itr Reg        900h + (ep_num * 20h) + 08h */
  uint32_t Reserved0C;             /*!< Reserved                       900h + (ep_num * 20h) + 0Ch */
  __IO uint32_t DIEPTSIZ;          /*!< IN Endpoint Txfer Size         900h + (ep_num * 20h) + 10h */
  __IO uint32_t DIEPDMA;           /*!< IN Endpoint DMA Address Reg    900h + (ep_num * 20h) + 14h */
  __IO uint32_t DTXFSTS;           /*!< IN Endpoint Tx FIFO Status Reg 900h + (ep_num * 20h) + 18h */
  uint32_t Reserved18;             /*!< Reserved  900h+(ep_num*20h)+1Ch-900h+ (ep_num * 20h) + 1Ch */
} USB_OTG_INEndpointTypeDef;

typedef struct
{
  __IO uint32_t DOEPCTL;       /*!< dev OUT Endpoint Control Reg           B00h + (ep_num * 20h) + 00h */
  uint32_t Reserved04;         /*!< Reserved                               B00h + (ep_num * 20h) + 04h */
  __IO uint32_t DOEPINT;       /*!< dev OUT Endpoint Itr Reg               B00h + (ep_num * 20h) + 08h */
  uint32_t Reserved0C;         /*!< Reserved                               B00h + (ep_num * 20h) + 0Ch */
  __IO uint32_t DOEPTSIZ;      /*!< dev OUT Endpoint Txfer Size            B00h + (ep_num * 20h) + 10h */
  __IO uint32_t DOEPDMA;       /*!< dev OUT Endpoint DMA Address           B00h + (ep_num * 20h) + 14h */
  uint32_t Reserved18[2];      /*!< Reserved B00h + (ep_num * 20h) + 18h - B00h + (ep_num * 20h) + 1Ch */
} USB_OTG_OUTEndpointTypeDef;

typedef struct
{
  __IO uint32_t HCFG;             /*!< Host Configuration Register          400h */
  __IO uint32_t HFIR;             /*!< Host Frame Interval Register         404h */
  __IO uint32_t HFNUM;            /*!< Host Frame Nbr/Frame Remaining       408h */
  uint32_t Reserved40C;           /*!< Reserved                             40Ch */
  __IO uint32_t HPTXSTS;          /*!< Host Periodic Tx FIFO/ Queue Status  410h */
  __IO uint32_t HAINT;            /*!< Host All Channels Interrupt Register 414h */
  __IO uint32_t HAINTMSK;         /*!< Host All Channels Interrupt Mask     418h */
} USB_OTG_HostTypeDef;

typedef struct
{
  __IO uint32_t HCCHAR;           /*!< Host Channel Characteristics Register    500h */
  __IO uint32_t HCSPLT;           /*!< Host Channel Split Control Register      504h */
  __IO uint32_t HCINT;            /*!< Host Channel Interrupt Register          508h */
  __IO uint32_t HCINTMSK;         /*!< Host Channel Interrupt Mask Register     50Ch */
  __IO uint32_t HCTSIZ;           /*!< Host Channel Transfer Size Register      510h */
  __IO uint32_t HCDMA;            /*!< Host Channel DMA Address Register        514h */
  uint32_t Reserved[2];           /*!< Reserved                                      */
} USB_OTG_HostChannelTypeDef; 

typedef struct
{
    __IO uint32_t ISR;
    __IO uint32_t ICR;
    __IO uint32_t IER;
    __IO uint32_t CFGR1;
    __IO uint32_t CR;
    __IO uint32_t CMP;
    __IO uint32_t ARR;
    __IO uint32_t CNT;
    __IO uint32_t RSV0[1];
    __IO uint32_t CFGR2;
    __IO uint32_t RCR;

} LPTIM_TypeDef;  

typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t SR;
    __IO uint32_t RIS;
    __IO uint32_t IER;
    __IO uint32_t MIS;
    __IO uint32_t ICR;
    __IO uint32_t ESCR;
    __IO uint32_t ESUR;
    __IO uint32_t CWSTRT;
    __IO uint32_t CWSIZE;
    __IO uint32_t DR;

} DCMI_TypeDef; 

///*------------------- LTDC  ----------------------*/
typedef struct
{
    __IO uint32_t RSV1[2];
    __IO uint32_t SSCR;
    __IO uint32_t BPCR;
    __IO uint32_t AWCR;		//0x10
    __IO uint32_t TWCR;
	__IO uint32_t GCR;
	__IO uint32_t RSV2[2];
	__IO uint32_t SRCR;
	__IO uint32_t RSV3;
	__IO uint32_t BCCR;
	__IO uint32_t RSV4;		//0x30
	__IO uint32_t IER;
	__IO uint32_t ISR;
	__IO uint32_t ICR;
	__IO uint32_t LIPCR;	//0x40
	__IO uint32_t CPSR;
	__IO uint32_t CDSR;	
} LTDC_TypeDef;

typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t WHPCR;
	__IO uint32_t WVPCR;
	__IO uint32_t CKCR;		//0x90
	__IO uint32_t PFCR;
	__IO uint32_t CACR;
	__IO uint32_t DCCR;
	__IO uint32_t BFCR;		//0xA0
	__IO uint32_t RSV1[2];
	__IO uint32_t CFBAR;
	__IO uint32_t CFBLR;	//0xB0
	__IO uint32_t CFBLNR;
	__IO uint32_t RSV2[3];
	__IO uint32_t CLUTWR;
} LTDC_Layer_TypeDef;

///*------------------- CRC  ----------------------*/
typedef struct
{
    __IO uint32_t DATA;     
    __IO uint32_t CTRL;     
    __IO uint32_t INIT;     
    __IO uint32_t RSV0;     
    __IO uint32_t OUTXOR;   
    __IO uint32_t POLY;     
    __IO uint32_t FDATA;    
} CRC_TypeDef;

///*------------------- FMC_NAND ----------------------*/
typedef union
{
	uint8_t   FMC_NAND_BCHCODE_CH8;
	uint16_t  FMC_NAND_BCHCODE_CH16;
	uint32_t  FMC_NAND_BCHCODE_CH32;	
} FMC_NAND_BCH_CODE_t;

typedef union
{
	uint8_t   FMC_NAND_ECCDATA_CH8;
	uint16_t  FMC_NAND_ECCDATA_CH16;
	uint32_t  FMC_NAND_ECCDATA_CH32;	
} FMC_NAND_ECCDATA_t;

typedef union
{
	uint8_t   FMC_NAND_NECCDATA_CH8;
	uint16_t  FMC_NAND_NECCDATA_CH16;
	uint32_t  FMC_NAND_NECCDATA_CH32;	
} FMC_NAND_NECCDATA_t;

typedef struct
{
    __IO uint32_t  CTRL;     //0x00 
    __IO uint32_t  WST;      //0x04
    __IO uint32_t  STATUS;   //0x08
    __IO uint32_t  RSV0;         //0x0c
    __IO uint32_t  BCH_CFG;      //0x10
    __IO uint32_t  BCH_CTRL;     //0x14
    __IO uint32_t  BCH_STATUS;   //0x18
    FMC_NAND_BCH_CODE_t BCH_CODE;     //0x1c
    __IO uint32_t  BCH_ERRADR;   //0x20
    __IO uint32_t  BCH_ERRVEC;   //0x24
    __IO uint32_t  BCH_BASEADDR; //0x28
    __IO uint32_t  BCH_CODEPTR;  
    __IO uint32_t  BCH_ERRADDRPTR;
    __IO uint32_t  BCH_ERRVECPTR;
    __IO uint32_t  BCH_PAGENUM;
    __IO uint32_t  BCH_ADDRLATCH;
    __IO uint32_t  CMD;
    __IO uint32_t  ADDR;
	FMC_NAND_ECCDATA_t  FMC_NAND_ECCDATA;
	FMC_NAND_NECCDATA_t FMC_NAND_NECCDATA;

} FMC_NAND_TypeDef; 

///*------------------- DMA2D  ----------------------*/
typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t ISR;
	__IO uint32_t IFCR;
	__IO uint32_t FGMAR;
	__IO uint32_t FGOR;	//0x10
	__IO uint32_t BGMAR;
	__IO uint32_t BGOR;
	__IO uint32_t FGPFCCR;
	__IO uint32_t FGCOLR;	//0x20
	__IO uint32_t BGPFCCR;
	__IO uint32_t BGCOLR;
	__IO uint32_t FGCMAR;
	__IO uint32_t BGCMAR;	//0x30
	__IO uint32_t OPFCCR;
	__IO uint32_t OCOLR;
	__IO uint32_t OMAR;
	__IO uint32_t OOR;	//0x40
	__IO uint32_t NLR;
	__IO uint32_t LWR;
	__IO uint32_t AMTCR;
} DMA2D_TypeDef;

typedef struct
{
    __IO uint32_t CR;                   //0x0
    __IO uint32_t SR;                   //0x4

}COMP_TypeDef;  

typedef struct
{
    __IO uint32_t WP;                   //0x0
    __IO uint32_t CTRL;                 //0x4
    __IO uint32_t AR;                   //0x8
    __IO uint32_t DWR;                  //0xc
    __IO uint32_t SR;                   //0x10
    __IO uint32_t CLR;                  //0x14
    __IO uint32_t DR;                   //0x18
    __IO uint32_t DSDP;                 //0x1c
    __IO uint32_t BYTEWP;               //0x20
    __IO uint32_t PGCFG;                //0x24
    __IO uint32_t RSV0[246];            //0x28
    __IO uint32_t DSR[16];                 //0x400

}EFUSE_TypeDef;

typedef struct
{
	__IO uint32_t DATAIN;      //0x00
	__IO uint32_t KEYIN;       //0x04
	__IO uint32_t IVIN;        //0x08
	__IO uint32_t CTRL;        //0x0C
	__IO uint32_t STATE;       //0x10
	__IO uint32_t DATAOUT;     //0x14 
	__IO uint32_t STARTADDR;        //0x18	
	__IO uint32_t ENDADDR;     //0x1C
	__IO uint32_t INIDATA;     //0x20
	__IO uint32_t ADDR;        //0x24 
	
}AES_TypeDef;

typedef struct
{
    __IO uint32_t CTRL;             //0x00
    __IO uint32_t STAUTS;           //0x04
    __IO uint32_t X_DATAIN;         //0x08  
    __IO uint32_t Y_DATAIN;         //0x0c	
    __IO uint32_t RESULT1;          //0x10  
    __IO uint32_t RESULT2;          //0x14  
}CORDIC_TypeDef;


typedef struct
{
	__IO uint32_t DATAIN;       //0x00
	__IO uint32_t KEYIN;        //0x04
	__IO uint32_t OTFDEC_CTRL;  //0x08
	__IO uint32_t CTRL;         //0x0C
	__IO uint32_t STATE;        //0x10
	__IO uint32_t DATAOUT;      //0x14 
	__IO uint32_t RSV0;         //0x18	
	__IO uint32_t ENDADDR;      //0x1C
	__IO uint32_t INIDATA;      //0x20
	__IO uint32_t ADDR;         //0x24 
	__IO uint32_t UID;          //0x28 
	__IO uint32_t RSV1;         //0x2C 
	__IO uint32_t RSV2;         //0x30 
	__IO uint32_t RSV3;  
    __IO uint32_t OTFDEC_SPI_CTRL; 
	__IO uint32_t ENDADDR2;     //0x3c
	__IO uint32_t ENDADDR3;     //0x40
	__IO uint32_t RSV4;         //0x44
	__IO uint32_t RSV5;         //0x48
    __IO uint32_t KEYIN1;       //0x4c 	
	__IO uint32_t KEYIN2;       //0x50 	
	__IO uint32_t KEYIN3;       //0x54	
	__IO uint32_t ADDR1;        //0x58
	__IO uint32_t DATAOUT1;     //0x5C	
}AES_SPI_TypeDef;


///*------------------- SDMMC Registers ----------------------*/
typedef struct 
{
	__IO uint32_t SDMMC_CTRL;           	//00H
	__IO uint32_t SDMMC_PWREN;          	//04H
	__IO uint32_t SDMMC_CLKDIV;				//08H
	__IO uint32_t SDMMC_CLKSRC;         	//0CH
	__IO uint32_t SDMMC_CLKENA;           	//10H
	__IO uint32_t SDMMC_TMOUT;           	//14H
	__IO uint32_t SDMMC_CTYPE;           	//18H
	__IO uint32_t SDMMC_BLKSIZ;           	//1CH
	__IO uint32_t SDMMC_BYTCNT;           	//20H
	__IO uint32_t SDMMC_INTMASK;           	//24H
	__IO uint32_t SDMMC_CMDARG;           	//28H
	__IO uint32_t SDMMC_CMD;           		//2CH
	__IO uint32_t SDMMC_RESP0;           	//30H
	__IO uint32_t SDMMC_RESP1;           	//34H
	__IO uint32_t SDMMC_RESP2;           	//38H
	__IO uint32_t SDMMC_RESP3;           	//3CH
	__IO uint32_t SDMMC_MINTSTS;           	//40H
	__IO uint32_t SDMMC_RINTSTS;           	//44H
	__IO uint32_t SDMMC_STATUS;           	//48H
	__IO uint32_t SDMMC_FIFOTH;           	//4CH
	__IO uint32_t SDMMC_CDETECT;           	//50H
	__IO uint32_t SDMMC_WRTPRT;           	//54H
	__IO uint32_t SDMMC_GPIO;           	//58H
	__IO uint32_t SDMMC_TCBCNT;           	//5CH
	__IO uint32_t SDMMC_TBBCNT;           	//60H
	__IO uint32_t SDMMC_DEBNCE;           	//64H
	__IO uint32_t SDMMC_RSV0[3];           	//68H
	__IO uint32_t SDMMC_UHS_REG;           	//74H
	__IO uint32_t SDMMC_RSTN;           	//78H
	__IO uint32_t SDMMC_RSV1;           	//7CH
	__IO uint32_t SDMMC_BMOD;           	//80H
	__IO uint32_t SDMMC_PLDMND;           	//84H
	__IO uint32_t SDMMC_DBADDR;           	//88H
	__IO uint32_t SDMMC_IDSTS;           	//8CH
	__IO uint32_t SDMMC_IDINTEN;           	//90H
	__IO uint32_t SDMMC_DSCADDR;           	//94H
	__IO uint32_t SDMMC_BUFADDR;           	//98H
	__IO uint32_t SDMMC_RSV2[25];           //9CH
	__IO uint32_t SDMMC_CTHCTL;           	//100H
	__IO uint32_t SDMMC_BKDPWR;           	//104H
	__IO uint32_t SDMMC_UHS_EXT;           	//108H
	__IO uint32_t SDMMC_EMMC_DDR;           //10CH
	__IO uint32_t SDMMC_ENA_SHIFT;          //110H
	__IO uint32_t SDMMC_RSV3[59];           //114H
	__IO uint32_t SDMMC_DATA;          		//200H
} SDMMC_TypeDef;


///*----------------------- HDL registers ------------------------*/

typedef struct
{
	__IO uint32_t NDL_CTR;		    //0x000
	__IO uint32_t NDL_EN;			//0x004
	__IO uint32_t NDL_CLKDIV;	    //0x008
	__IO uint32_t INT_MASK;		    //0x00c
	__IO uint32_t INT_MIS;		    //0x010
	__IO uint32_t INT_CLR;		    //0x014
	__IO uint32_t WG_CTR;		    //0x018
	__IO uint32_t WG_PRD;		    //0x01c
	__IO uint32_t HPSA_FLT;		    //0x020
	__IO uint32_t RAS_CNT_CTREN;    //0x024
	__IO uint32_t RAS_CNT_CTR;      //0x028
	__IO uint32_t RAS_CNT_VAL;      //0x02c
	__IO uint32_t RAS_SPEED;	    //0x030
	__IO uint32_t RAS_HSYNC;	    //0x034
	__IO uint32_t CORR_CNT;		    //0x038
	__IO uint32_t HPSA_CNT;		    //0x03c
	__IO uint32_t FINE_STEP_PREC;   //0x040
	__IO uint32_t FINE_STEP_CNT;    //0x044
	__IO uint32_t PRINT_DELAY;		//0x048
	__IO uint32_t PRINT_CTR;	    //0x04c
	__IO uint32_t PRINT_START_POS;  //0x050
	__IO uint32_t PRINT_INIT_POS[24]; //0x054~0x0b0
	__IO uint32_t PRINT_REQ_NUM;    //0x0b4
	__IO uint32_t PRINT_DPI_SET;    //0x0b8	
	__IO uint32_t PRINT_DATA;       //0x0bc	
	__IO uint32_t DMA_BUF_CTR;		//0x0c0	
	__IO uint32_t SPEED_UP_CNT;		//0x0c4	
	__IO uint32_t ADO_MODE_CTR;		//0x0c8	
	__IO uint32_t WAVE_TFG[24];		//0x0cc~0x128	
	__IO uint32_t WAVE_TGHIJ;	    //0x12C	
	__IO uint32_t SURGE_TGKL;	    //0x130	
	__IO uint32_t RSV0;			    //0x133	
	__IO uint32_t PROT_TFMN;	    //0x138	
	__IO uint32_t PROT_EN;		    //0x13C	
	__IO uint32_t PIN_CFG[24];		//0x140~0x19c
	__IO uint32_t RSV1[24];		    //0x1a0~0x1fc	
	__IO uint32_t DOT_CNT_VAL[24];  //0x200~0x25c	
	__IO uint32_t MS_CTR;		    //0x260	
	__IO uint32_t MS_TGHIJ;	    //0x264, MS_TGHIJ_CHJ	
	__IO uint32_t MS_TGN;		    //0x268	
	__IO uint32_t MS_TGQR;		    //0x26c	
	__IO uint32_t MS_ON_OFF;		//0x270	
	__IO uint32_t MS_PROT_TFMN;		//0x274	
	__IO uint32_t MS_PROT_EN;		//0x278	
	__IO uint32_t INT_RIS;		    //0x27c	
	__IO uint32_t DMA_DATA_STA;		//0x280	
	__IO uint32_t SURGE_CFG[24];	//0x284~0x2e0	
	__IO uint32_t CLK_TFG;		    //0x2e4	
	__IO uint32_t FEED_CTL;		    //0x2e8	
}NDL_TypeDef;


///*----------------------- HEAD registers ------------------------*/
typedef struct
{
	__IO uint32_t PRINT_DATA;	    //0x000         ´òÓ¡Êý¾Ý¼Ä´æÆ÷
	__IO uint32_t PRINT_DIV;	    //0x004         ´òÓ¡·ÖÆµ¼Ä´æÆ÷
	__IO uint32_t PRINT_CFG1;	    //0x008         ´òÓ¡ÅäÖÃ¼Ä´æÆ÷1
	__IO uint32_t PRINT_CFG2;	    //0x00c         ´òÓ¡ÅäÖÃ¼Ä´æÆ÷2
	__IO uint32_t PRINT_CFG3;	    //0x010         ´òÓ¡ÅäÖÃ¼Ä´æÆ÷3
	__IO uint32_t PRINT_TRIGR;      //0x014         ´òÓ¡´¥·¢Ñ¡Ôñ¼Ä´æÆ÷
	__IO uint32_t PRINT_CR;		    //0x018         ´òÓ¡¿ØÖÆ¼Ä´æÆ÷
	__IO uint32_t PRINT_ERR;	    //0x01c         ´òÓ¡´íÎó¼Ä´æÆ÷
	__IO uint32_t PRINT_SR;		    //0x020         ´òÓ¡×´Ì¬¼Ä´æÆ÷
	__IO uint32_t PRINT_IE;		    //0x024         ´òÓ¡ÖÐ¶ÏÊ¹ÄÜ¼Ä´æÆ÷
	
	__IO uint32_t PRINT_ERR_IE;     //0x028        ´òÓ¡´íÎó×´Ì¬´¥·¢¼Ä´æÆ÷     // 2023/12/12 
	__IO uint32_t RSV0[1];		    //0x2c
	
	__IO uint32_t DATA_BASE[16];    //0x030~0x6c  Êý¾ÝÏßnµÄÆðÊ¼µØÖ·¼Ä´æÆ÷
	__IO uint32_t PRINT_SUBDATA;	//0x070     ´òÓ¡¼õÊý¼Ä´æÆ÷ 
	
	__IO uint32_t CYC1_CFG;         //0x74          // 2023/2/14 YZR
	__IO uint32_t TIMERCR;          //0x78          // 2023/6/6  YZR
	__IO uint32_t DELAY;            //0x7c          // 2023/6/6  YZR
	
	__IO uint32_t DROP;				//0x080          DROP
	__IO uint32_t DROP_MAX;		    //0x084
	__IO uint32_t DROP_B;			//0x088          
	
	__IO uint32_t DROP_IGN;         //0x08c          // 2023/2/14 YZR	
	__IO uint32_t RSV2[4];		    //0x090~0x9c
	
	__IO uint32_t S_COR;			//0x0a0
	__IO uint32_t Z_COR;			//0x0a4
	__IO uint32_t M_COR;			//0x0a8
	__IO uint32_t Z_ADD;			//0x0ac
	__IO uint32_t N_ADD;			//0x0b0
	__IO uint32_t Z_RAD;			//0x0b4
	__IO uint32_t M_ADD;			//0x0b8
	__IO uint32_t MAIN;				//0x0bc
	__IO uint32_t M_RAD;			//0x0c0
	__IO uint32_t P_ADD;			//0x0c4
	__IO uint32_t S_COR_MAX;	    //0x0c8
	__IO uint32_t Z_ADD1;			//0x0cc
	__IO uint32_t MAX_OT;			//0x0d0
	__IO uint32_t M_ADD1;			//0x0d4
	__IO uint32_t MAX_OT_ZEN;	    //0x0d8
	__IO uint32_t MAX_OT_MEM;	    //0x0dc
	
	__IO uint32_t PREHEAT_CFG1;	    //0x0e0   Ô¤ÈÈÅäÖÃ¼Ä´æÆ÷1
	__IO uint32_t PREHEAT_CFG2;	    //0x0e4
	__IO uint32_t PREHEAT_CFG3;	    //0x0e8
	__IO uint32_t PREHEAT_CR;		//0x0ec	
	__IO uint32_t RSV3[4];		    //0x0f0~0xfc	
	__IO uint32_t DOT_CFG;		    //0x100
	__IO uint32_t IBF_DATA;		    //0x104	
	__IO uint32_t RSV4[6];		    //0x108~11c
	__IO uint32_t DOT_RST[8];	    //0x120~13c
	
	__IO uint32_t YMC_THRSLD;	    //0x140		
	__IO uint32_t YMC_OT;			//0x144		
	__IO uint32_t YMC_ZEN;		    //0x148		
	__IO uint32_t YMC_MEM;		    //0x14c		
	__IO uint32_t ZEN_RDATA;	    //0x150		
	__IO uint32_t MEM_RDATA;	    //0x154		
	__IO uint32_t LUTSUM_CUR;	    //0x158		
	__IO uint32_t LUTSUM_LATCH;     //0x15c		
	__IO uint32_t OTSUM_CUR;		//0x160		
	__IO uint32_t OTSUM_LATCH;	    //0x164
	
	__IO uint32_t RSV5[6];			//0x168~0x17c
	__IO uint32_t DATA_BASE2[16];   //0x180~0x1bc
	__IO uint32_t DATA_BASE3[16];   //0x1c0~0x1fc
}HEAD_TypeDef; 

typedef struct
{
	__IO uint32_t LUT_n[128];		//0x200~3fc
}LUT_TypeDef;

typedef struct
{
	__IO uint32_t FLT0;             // ×Ô¶¨ÒåµãÕón¹ýÂË¼Ä´æÆ÷0
	__IO uint32_t FLT1;
	__IO uint32_t FLT2;
	__IO uint32_t MASK0;            // ×Ô¶¨ÒåµãÕónÆÁ±Î¼Ä´æÆ÷0
	__IO uint32_t MASK1;
	__IO uint32_t MASK2;    
}UDF_TypeDef;

typedef struct
{
	__IO uint32_t DOT_DATA;	        //0x400       µãÂÄÀúxÊý¾Ý¼Ä´æÆ÷
	__IO uint32_t WRITE_MODE;	    //0x404
	__IO uint32_t BUFF_RDATA;	    //0x408       £¨Ö»¶Á£©µãÂÄÀúBUFFxÁÐ¶Á³ö¼Ä´æÆ÷
	__IO uint32_t RSV0;	            //0x40c
	__IO uint32_t FIXCMP_EN[14];    //0x410~444   ¹Ì¶¨µãÕó±È½ÏÊ¹ÄÜ¼Ä´æÆ÷
	__IO uint32_t RSV1[2];	        //0x448~44c
	__IO uint32_t FIX_RSTSEL[107];  //0x450~5f8
	__IO uint32_t RSV2[21];	        //0x5fc~0x64c
	__IO uint32_t UDFCMP_EN;        //0x650       ×Ô¶¨ÒåµãÕó±È½ÏÊ¹ÄÜ¼Ä´æÆ÷	
	__IO uint32_t UDF_RSTSEL0;      //0x654	
	__IO uint32_t UDF_RSTSEL1;      //0x658
	__IO uint32_t RSV3;	            //0x65c
	UDF_TypeDef UDF_P[8];           //0x660	
}DOT_TypeDef;

typedef struct
{
	__IO uint32_t PRTH_CFG1;        //0xa00     // PRTHn_CFG1  ´òÓ¡½×nÅäÖÃ¼Ä´æÆ÷1
	__IO uint32_t PRTH_CFG2;        //0xa04
	__IO uint32_t PRTH_CFG3;        //0xa08
	__IO uint32_t PRTH_CFG4;        //0xa0c
	__IO uint32_t PRTH_CFG5;        //0xa10
	__IO uint32_t PRTH_CFG6;        //0xa14
	__IO uint32_t RSV0[2]; 	        //0xa18 a1c
}HCFG_TypeDef; 

#define PRT_HCFG_LEN  256
typedef struct
{
	HCFG_TypeDef PRT_HCFG[PRT_HCFG_LEN] ;   // ´òÓ¡²¨ÐÎ½×ÉèÖÃ£¬¹²256½×
}LCFG_TypeDef;


///*----------------------- STM_PWM registers ------------------------*/

typedef struct
{
    // all registers are valid for stmpwm12
    // 0~0X24 registers are valid for stmpwm3456  
	__IO uint32_t CTL;          //0x00, PWM Control Register
	__IO uint32_t CSR;          //0x04, PWM Current Status Register
	__IO uint32_t MSK_ISR;      //0x08, PWM Masked Interrupt Status Register
	__IO uint32_t ICLR;         //0x0C, PWM Interrupt Clear Register
	__IO uint32_t IENR;         //0x10, PWM Interrupt Enable Register
	__IO uint32_t CCR;          //0x14, PWM Clock Control Register
	__IO uint32_t LWR;          //0x18, PWM Low Level Width Register  
	__IO uint32_t OPR;          //0x1C, PWM Original Period Register
	__IO uint32_t CNT;          //0x20, PWM Counter Register
	__IO uint32_t UMK_ISR;      //0x24, PWM Unmasked Interrupt Status Register
    
	__IO uint32_t FINE_PH_CTL;  //0x28, PWM FINE PH Control Register
	__IO uint32_t FINEA_OPR;    //0x2C, PWM FINEA Original Period Register
	//----------------------------------------------------------------------------------	
	__IO uint32_t CNTX_CTL;     //0x30, PWM Counter X Control Register
	__IO uint32_t CNT1_TH;      //0x34, PWM Counter 1 Threshold Register
	__IO uint32_t CNT1;         //0x38, PWM Counter 1 Register
	__IO uint32_t CNT2_TH;      //0x3C, PWM Counter 2 Threshold Register
	__IO uint32_t CNT2;         //0x40, PWM Counter 2 Register
	__IO uint32_t CNT3_TH;      //0x44, PWM Counter 3Threshold Register
	__IO uint32_t CNT3;         //0x48, PWM Counter 3 Register
	//----------------------------------------------------------------------------------
	__IO uint32_t CNTY_CTL;     //0x4C, PWM Counter Y Control Register
	__IO uint32_t CNTA_TH;      //0x50, PWM Counter A Threshold Register
	__IO uint32_t CNTA;         //0x54, PWM Counter A Register
	__IO uint32_t CNTB_TH;      //0x58, PWM Counter B Threshold Register	
	__IO uint32_t CNTB;         //0x5C, PWM Counter B Register
	__IO uint32_t CNTC_TH;      //0x60, PWM Counter C Threshold Register	
	__IO uint32_t CNTC;         //0x64, PWM Counter C Register
	//----------------------------------------------------------------------------------
	__IO uint32_t PWM1;         //0x68, PWM PWMx Register
	__IO uint32_t PWM2;         //0x6C
	__IO uint32_t PWM3;         //0x70
	__IO uint32_t PWM4;         //0x74
	__IO uint32_t PWM5;         //0x78
	__IO uint32_t PWM6;         //0x7C
	__IO uint32_t PWM7;         //0x80
	__IO uint32_t PWM8;         //0x84
	__IO uint32_t PWM9;         //0x88
	__IO uint32_t PWM10;        //0x8C
	__IO uint32_t PWM11;        //0x90
	__IO uint32_t PWM12;        //0x94
	__IO uint32_t PWM13;        //0x98
	__IO uint32_t PWM14;        //0x9C
	__IO uint32_t PWM15;        //0xA0
	__IO uint32_t PWM16;        //0xA4
}STMPWM_TypeDef;

///*----------------------- DCM_PWM registers ------------------------*/

typedef struct
{
	//----------------------------------------------AREA1
	__IO uint32_t REG_DCM_PWM_CCR;  //0x00
	__IO uint32_t REG_DCM_PWM_CFG;  //0x04
	__IO uint32_t REG_DCM_PWM_SR;   //0x08
	//----------------------------------------------AREA2
	__IO uint32_t REG_ENC_IN_CFG;   //0x0C
	__IO uint32_t REG_ENC_CNT;      //0x10
	__IO uint32_t REG_ENC_CNT_CMP;  //0x14
	__IO uint32_t REG_ENC_FLT_CFG;  //0x18
	__IO uint32_t REG_SNS1_FLT_CFG; //0x1C
	__IO uint32_t REG_SNS2_FLT_CFG; //0x20
	__IO uint32_t REG_SNS3_FLT_CFG; //0x24
	__IO uint32_t REG_TIMA_SET_VAL; //0x28
	__IO uint32_t REG_TIMA_LATCH;   //0x2C
	__IO uint32_t REG_TIMB_SET_VAL; //0x30
	__IO uint32_t REG_TIMB_LATCH;   //0x34
	//----------------------------------------------AREA3
	__IO uint32_t REG_PWM_CYC_S1_S3;//0x38
	__IO uint32_t REG_PWM_CYC_TL_S2;//0x3C
	__IO uint32_t REG_PWM_NUM_S1;   //0x40
	__IO uint32_t REG_PWM_NUM_S2;   //0x44
	__IO uint32_t REG_PWM_NUM_S3;   //0x48
	__IO uint32_t REG_PWM_DIR;      //0x4C
	__IO uint32_t REG_DCM_PWM_IENR; //0x50
	__IO uint32_t REG_DCM_PWM_UMK_ISR;//0x54
	__IO uint32_t REG_DCM_PWM_MSK_ISR;//0x58	
	__IO uint32_t REG_DCM_PWM_ICLR; //0x5C
	__IO uint32_t REG_DCM_PWM_CNT;  //0x60	
}DCM_PWM_TypeDef; // ÍêÕû°æ



typedef struct
{
	//----------------------------------------------AREA1
	__IO uint32_t REG_DCM_PWM_CCR;  //0x00
	__IO uint32_t REG_DCM_PWM_CFG;  //0x04
	__IO uint32_t REG_DCM_PWM_SR;   //0x08
//	//----------------------------------------------AREA2
//	__IO uint32_t REG_ENC_IN_CFG;
//	__IO uint32_t REG_ENC_CNT;
//	__IO uint32_t REG_ENC_CNT_CMP;
//	__IO uint32_t REG_ENC_FLT_CFG;
//	__IO uint32_t REG_SNS1_FLT_CFG;
//	__IO uint32_t REG_SNS2_FLT_CFG;
//	__IO uint32_t REG_SNS3_FLT_CFG;
//	__IO uint32_t REG_TIMA_SET_VAL;
//	__IO uint32_t REG_TIMA_LATCH;
//	__IO uint32_t REG_TIMB_SET_VAL;
//	__IO uint32_t REG_TIMB_LATCH;
	//----------------------------------------------AREA3
	__IO uint32_t REG_PWM_CYC_S1_S3;//0x0C
	__IO uint32_t REG_PWM_CYC_TL_S2;//0x10
	__IO uint32_t REG_PWM_NUM_S1;   //0x14
	__IO uint32_t REG_PWM_NUM_S2;   //0x18
	__IO uint32_t REG_PWM_NUM_S3;   //0x1C
	__IO uint32_t REG_PWM_DIR;      //0x20
	__IO uint32_t REG_DCM_PWM_IENR; //0x24
	__IO uint32_t REG_DCM_PWM_UMK_ISR;//0x28
	__IO uint32_t REG_DCM_PWM_MSK_ISR;//0x2C	
	__IO uint32_t REG_DCM_PWM_ICLR; //0x30
	__IO uint32_t REG_DCM_PWM_CNT;  //0x34
}DCM_PWM_SE_TypeDef; // ¾«¼ò°æ


//  °ÑÔ­¼Ä´æÆ÷½á¹¹Ìå·Ö3Çø´¦Àí£¬¼õÉÙ´óÁ¿ÖØ¸´´úÂë

typedef struct
{
	__IO uint32_t REG_DCM_PWM_CCR;
	__IO uint32_t REG_DCM_PWM_CFG;
	__IO uint32_t REG_DCM_PWM_SR;
}DCM_PWM_AREA1_TypeDef; 


typedef struct
{
	__IO uint32_t REG_ENC_IN_CFG;
	__IO uint32_t REG_ENC_CNT;
	__IO uint32_t REG_ENC_CNT_CMP;
	__IO uint32_t REG_ENC_FLT_CFG;
	__IO uint32_t REG_SNS1_FLT_CFG;
	__IO uint32_t REG_SNS2_FLT_CFG;
	__IO uint32_t REG_SNS3_FLT_CFG;
	__IO uint32_t REG_TIMA_SET_VAL;
	__IO uint32_t REG_TIMA_LATCH;
	__IO uint32_t REG_TIMB_SET_VAL;
	__IO uint32_t REG_TIMB_LATCH;
}DCM_PWM_AREA2_TypeDef; 


typedef struct
{
	__IO uint32_t REG_PWM_CYC_S1_S3;
	__IO uint32_t REG_PWM_CYC_TL_S2;
	__IO uint32_t REG_PWM_NUM_S1;
	__IO uint32_t REG_PWM_NUM_S2;
	__IO uint32_t REG_PWM_NUM_S3;
	__IO uint32_t REG_PWM_DIR;
	__IO uint32_t REG_DCM_PWM_IENR;
	__IO uint32_t REG_DCM_PWM_UMK_ISR;
	__IO uint32_t REG_DCM_PWM_MSK_ISR;
	__IO uint32_t REG_DCM_PWM_ICLR;
	__IO uint32_t REG_DCM_PWM_CNT;
}DCM_PWM_AREA3_TypeDef; 


///*----------------------- LPT registers ------------------------*/

typedef struct
{
    __IO uint32_t PARIF_MMR;    //0x00	Parallel-Interface  Master Mode Register
    __IO uint32_t PARIF_DINR;   //0x04	Parallel-Interface  Data Input Register
    __IO uint32_t PARIF_HMR;    //0x08	Parallel-Interface  Handshake Mode Register
    __IO uint32_t RES;		    //0x0c	±£Áô
    __IO uint32_t PARIF_TBAR;   //0x10 Parallel-Interface  Trigger Busy/Ack# Register
    __IO uint32_t PARIF_CINR;   //0x14 Parallel-Interface  Control Input Register
    __IO uint32_t PARIF_COUTR;  //0x18 Parallel-Interface  Control Output Register
    __IO uint32_t PARIF_FCR;    //0x1c  Parallel-Interface  Filter Configuration Register
    __IO uint32_t PARIF_DATR;   //0x20 Parallel-Interface  Data Transparent Register
    __IO uint32_t PARIF_NIBDR;  //0x24 Parallel-Interface  Nibble Data Register
    __IO uint32_t PARIF_HMR2;   //0x28	Parallel-Interface  Handshake Mode Register2
    __IO uint32_t PARIF_ALR;    //0x2c	Parallel-Interface  Ack# Load Register
    __IO uint32_t PARIF_AWR;    //0x30 	Parallel-Interface  Ack# Width Register
    __IO uint32_t PARIF_BWR;    //0x34	Parallel-Interface  Busy Width Register
    __IO uint32_t PARIF_ISR;    //0x38	Parallel-Interface  Interrupt Status Register
    __IO uint32_t PARIF_IDBR;   //0x3c	Parallel-Interface  ID Data Register
    __IO uint32_t PARIF_RDBR;   //0x40	Parallel-Interface  Reverse Data Register
    __IO uint32_t PARIF_NCR;    //0x44	Parallel-Interface  Nibble Mode Configure Register
    __IO uint32_t PARIF_EXDBR;  //0x48 Parallel-Interface  Extra Data Register
    __IO uint32_t PARIF_DTR;    //0x4c	Parallel-Interface Delay Timer1 Register
    __IO uint32_t PARIF_DTR2;   //0x50	Parallel-Interface Delay Timer2 Register
    __IO uint32_t PARIF_RSTR;   //0x54	Parallel-Interface Reset Register
    __IO uint32_t PARIF_FRQR;   //0x58	Parallel-Interface Data Request Enable Register
    __IO uint32_t PARIF_FDR;    //0x5c	Parallel-Interface Data FIFO Deep Register
    __IO uint32_t PARIF_TOR;    //0x60	Parallel-Interface Data Request Timer Out Register
    __IO uint32_t PARIF_DCNTR;  //0x64 Parallel-Interface Data Counter Register
    __IO uint32_t PARIF_NIBDR2; //0x68 Parallel-Interface  Nibble Data Register2
    __IO uint32_t PARIF_EXR;    //0x6c	Parallel-Interface Extra Respond Register
    __IO uint32_t PARIF_FCR2;   //0x70	Parallel-Interface  Filter Configuration Register2
    __IO uint32_t PARIF_PCKFR;  //0x74 Parallel-Interface PCLK Frequency Register
    __IO uint32_t PARIF_CK19DR; //0x78 Parallel-Interface  CLK19 Divider Register
    __IO uint32_t PARIF_FCR3;   //0x7c Parallel-Interface  Filter Configuration Register3
    __IO uint32_t PARIF_FCR4;   //0x80 Parallel-Interface  Filter Configuration Register4
    __IO uint32_t PARIF_DTR3;   //0x84 Parallel-Interface Delay Timer3 Register
}LPT_TypeDef;


/*-------------------------  USB OTG  defined  -------------------------*/

#define USB_OTG_GLOBAL_BASE                  0x0000UL
#define USB_OTG_DEVICE_BASE                  0x0800UL
#define USB_OTG_IN_ENDPOINT_BASE             0x0900UL
#define USB_OTG_OUT_ENDPOINT_BASE            0x0B00UL
#define USB_OTG_EP_REG_SIZE                  0x0020UL
#define USB_OTG_HOST_BASE                    0x0400UL
#define USB_OTG_HOST_PORT_BASE               0x0440UL
#define USB_OTG_HOST_CHANNEL_BASE            0x0500UL
#define USB_OTG_HOST_CHANNEL_SIZE            0x0020UL
#define USB_OTG_PCGCCTL_BASE                 0x0E00UL
#define USB_OTG_FIFO_BASE                    0x1000UL
#define USB_OTG_FIFO_SIZE                    0x1000UL 

/*-------------------------  Peripheral declatation  -------------------------*/


#define SYSCFG                          ( (SYSCFG_TypeDef *)SYSCFG_BASE_ADDR )
#define RCC                             ( (RCC_TypeDef *)RCC_BASE_ADDR )
#define GPIOA                           ( (GPIO_TypeDef *)GPIOA_BASE_ADDR )
#define GPIOB                           ( (GPIO_TypeDef *)GPIOB_BASE_ADDR )
#define GPIOC                           ( (GPIO_TypeDef *)GPIOC_BASE_ADDR )
#define GPIOD                           ( (GPIO_TypeDef *)GPIOD_BASE_ADDR )
#define GPIOE                           ( (GPIO_TypeDef *)GPIOE_BASE_ADDR )
#define GPIOF                           ( (GPIO_TypeDef *)GPIOF_BASE_ADDR )
#define GPIOG                           ( (GPIO_TypeDef *)GPIOG_BASE_ADDR )
#define GPIOH                           ( (GPIO_TypeDef *)GPIOH_BASE_ADDR )
#define GPIOI                           ( (GPIO_TypeDef *)GPIOI_BASE_ADDR )
#define GPIOJ                           ( (GPIO_TypeDef *)GPIOJ_BASE_ADDR )
#define GPIOK                           ( (GPIO_TypeDef *)GPIOK_BASE_ADDR )
#define GPIOL                           ( (GPIO_TypeDef *)GPIOL_BASE_ADDR )
#define GPIOM                           ( (GPIO_TypeDef *)GPIOM_BASE_ADDR )
#define GPION                           ( (GPIO_TypeDef *)GPION_BASE_ADDR )
#define GPIOO                           ( (GPIO_TypeDef *)GPIOO_BASE_ADDR )
#define GPIOP                           ( (GPIO_TypeDef *)GPIOP_BASE_ADDR )
#define GPIOQ                           ( (GPIO_TypeDef *)GPIOQ_BASE_ADDR )
#define EXTI                            ( (EXTI_TypeDef *)EXTI_BASE_ADDR )
#define DMA1                            ( (DMA_TypeDef *)DMA1_BASE_ADDR )
#define DMA1_Channel0                   ( (DMA_Channel_TypeDef *)DMA1_CHANNEL0_BASE_ADDR )
#define DMA1_Channel1                   ( (DMA_Channel_TypeDef *)DMA1_CHANNEL1_BASE_ADDR )
#define DMA1_Channel2                   ( (DMA_Channel_TypeDef *)DMA1_CHANNEL2_BASE_ADDR )
#define DMA1_Channel3                   ( (DMA_Channel_TypeDef *)DMA1_CHANNEL3_BASE_ADDR )
#define DMA1_Channel4                   ( (DMA_Channel_TypeDef *)DMA1_CHANNEL4_BASE_ADDR )
#define DMA1_Channel5                   ( (DMA_Channel_TypeDef *)DMA1_CHANNEL5_BASE_ADDR )
#define DMA1_Channel6                   ( (DMA_Channel_TypeDef *)DMA1_CHANNEL6_BASE_ADDR )
#define DMA1_Channel7                   ( (DMA_Channel_TypeDef *)DMA1_CHANNEL7_BASE_ADDR )
#define DMA2                            ( (DMA_TypeDef *)DMA2_BASE_ADDR )
#define DMA2_Channel0                   ( (DMA_Channel_TypeDef *)DMA2_CHANNEL0_BASE_ADDR )
#define DMA2_Channel1                   ( (DMA_Channel_TypeDef *)DMA2_CHANNEL1_BASE_ADDR )
#define DMA2_Channel2                   ( (DMA_Channel_TypeDef *)DMA2_CHANNEL2_BASE_ADDR )
#define DMA2_Channel3                   ( (DMA_Channel_TypeDef *)DMA2_CHANNEL3_BASE_ADDR )
#define DMA2_Channel4                   ( (DMA_Channel_TypeDef *)DMA2_CHANNEL4_BASE_ADDR )
#define DMA2_Channel5                   ( (DMA_Channel_TypeDef *)DMA2_CHANNEL5_BASE_ADDR )
#define DMA2_Channel6                   ( (DMA_Channel_TypeDef *)DMA2_CHANNEL6_BASE_ADDR )
#define DMA2_Channel7                   ( (DMA_Channel_TypeDef *)DMA2_CHANNEL7_BASE_ADDR )
#define TIM1                            ( (TIM_TypeDef *)TIM1_BASE_ADDR )
#define TIM2                            ( (TIM_TypeDef *)TIM2_BASE_ADDR )
#define TIM3                            ( (TIM_TypeDef *)TIM3_BASE_ADDR )
#define TIM4                            ( (TIM_TypeDef *)TIM4_BASE_ADDR )
#define TIM5                            ( (TIM_TypeDef *)TIM5_BASE_ADDR )
#define TIM6                            ( (TIM_TypeDef *)TIM6_BASE_ADDR )
#define TIM7                            ( (TIM_TypeDef *)TIM7_BASE_ADDR )
#define TIM8                            ( (TIM_TypeDef *)TIM8_BASE_ADDR )
#define TIM9                            ( (TIM_TypeDef *)TIM9_BASE_ADDR )
#define TIM10                           ( (TIM_TypeDef *)TIM10_BASE_ADDR )
#define TIM11                           ( (TIM_TypeDef *)TIM11_BASE_ADDR )
#define TIM12                           ( (TIM_TypeDef *)TIM12_BASE_ADDR )
#define TIM13                           ( (TIM_TypeDef *)TIM13_BASE_ADDR )
#define TIM14                           ( (TIM_TypeDef *)TIM14_BASE_ADDR )
#define TIM15                           ( (TIM_TypeDef *)TIM15_BASE_ADDR )
#define TIM16                           ( (TIM_TypeDef *)TIM16_BASE_ADDR )
#define TIM17                           ( (TIM_TypeDef *)TIM17_BASE_ADDR )
#define TIM18                           ( (TIM_TypeDef *)TIM18_BASE_ADDR )
#define TIM19                           ( (TIM_TypeDef *)TIM19_BASE_ADDR )
#define TIM20                           ( (TIM_TypeDef *)TIM20_BASE_ADDR )
#define TIM21                           ( (TIM_TypeDef *)TIM21_BASE_ADDR )
#define TIM22                           ( (TIM_TypeDef *)TIM22_BASE_ADDR )
#define TIM23                           ( (TIM_TypeDef *)TIM23_BASE_ADDR )
#define TIM24                           ( (TIM_TypeDef *)TIM24_BASE_ADDR )
#define TIM25                           ( (TIM_TypeDef *)TIM25_BASE_ADDR )
#define TIM26                           ( (TIM_64BIT_TypeDef *)TIM26_BASE_ADDR )
#define RTC                             ( (RTC_TypeDef *)RTC_BASE_ADDR )
#define PMU                             ( (PMU_TypeDef *)PMU_BASE_ADDR )
#define WDT                             ( (WDT_TypeDef *)WDT_BASE_ADDR )
#define IWDT                            ( (IWDT_TypeDef *)IWDT_BASE_ADDR )
#define I2S1                            ( (I2S_TypeDef *)I2S1_BASE_ADDR )
#define I2S2                            ( (I2S_TypeDef *)I2S2_BASE_ADDR )
#define I2S3                            ( (I2S_TypeDef *)I2S3_BASE_ADDR )
#define I2C1                            ( (I2C_TypeDef *)I2C1_BASE_ADDR )
#define I2C2                            ( (I2C_TypeDef *)I2C2_BASE_ADDR )
#define I2C3                            ( (I2C_TypeDef *)I2C3_BASE_ADDR )
#define I2C4                            ( (I2C_TypeDef *)I2C4_BASE_ADDR )
#define USART1                          ( (USART_TypeDef *)USART1_BASE_ADDR )
#define USART2                          ( (USART_TypeDef *)USART2_BASE_ADDR )
#define USART3                          ( (USART_TypeDef *)USART3_BASE_ADDR )
#define USART4                          ( (USART_TypeDef *)USART4_BASE_ADDR )
#define USART5                          ( (USART_TypeDef *)USART5_BASE_ADDR )
#define USART6                          ( (USART_TypeDef *)USART6_BASE_ADDR )
#define USART7                          ( (USART_TypeDef *)USART7_BASE_ADDR )
#define USART8                          ( (USART_TypeDef *)USART8_BASE_ADDR )
#define USART9                          ( (USART_TypeDef *)USART9_BASE_ADDR )
#define USART10                         ( (USART_TypeDef *)USART10_BASE_ADDR )
#define FDCAN1                          ( (FDCAN_GlobalTypeDef *)FDCAN1_BASE_ADDR )
#define FDCAN2                          ( (FDCAN_GlobalTypeDef *)FDCAN2_BASE_ADDR )
#define FDCAN3                          ( (FDCAN_GlobalTypeDef *)FDCAN3_BASE_ADDR )
#define LPTIM1                          ( (LPTIM_TypeDef *)LPTIM1_BASE_ADDR )
#define LPTIM2                          ( (LPTIM_TypeDef *)LPTIM2_BASE_ADDR )
#define LPTIM3                          ( (LPTIM_TypeDef *)LPTIM3_BASE_ADDR )
#define LPTIM4                          ( (LPTIM_TypeDef *)LPTIM4_BASE_ADDR )
#define LPTIM5                          ( (LPTIM_TypeDef *)LPTIM5_BASE_ADDR )
#define LPTIM6                          ( (LPTIM_TypeDef *)LPTIM6_BASE_ADDR )
#define LPUART1                         ( (LPUART_TypeDef *)LPUART1_BASE_ADDR )
#define EFUSE1                          ( (EFUSE_TypeDef *)EFUSE1_BASE_ADDR )
#define EFUSE2                          ( (EFUSE_TypeDef *)EFUSE2_BASE_ADDR )
#define COMP1                           ( (COMP_TypeDef *)COMP1_BASE_ADDR )
#define TKEY                            ( (TKEY_TypeDef *)TKEY_BASE_ADDR )
#define LTDC                            ( (LTDC_TypeDef *)LTDC_BASE_ADDR )
#define MDAC                            ( (MDAC_TypeDef *)MDAC_BASE_ADDR )


#define CRC                             ( (CRC_TypeDef *)CRC_BASE_ADDR )
#define ETH                             ( (ETH_TypeDef *)ETHMAC_BASE_ADDR )
#define DMA2D                           ( (DMA2D_TypeDef *)DMA2D_BASE_ADDR )
#define SPI1                            ( (SPI_TypeDef *)SPI1_BASE_ADDR )
#define SPI2                            ( (SPI_TypeDef *)SPI2_BASE_ADDR )
#define SPI3                            ( (SPI_TypeDef *)SPI3_BASE_ADDR )
#define SPI4                            ( (SPI_TypeDef *)SPI4_BASE_ADDR )
#define SPI5                            ( (SPI_TypeDef *)SPI5_BASE_ADDR )
#define SPI6                            ( (SPI_TypeDef *)SPI6_BASE_ADDR )
#define SPI7                            ( (SPI_TypeDef *)SPI7_BASE_ADDR )
#define SPI8                            ( (SPI_TypeDef *)SPI8_BASE_ADDR )
#define USB_OTG_HS1                     ( (USB_OTG_GlobalTypeDef *) USBOTG_HS1_BASE_ADDR )     
#define USB_OTG_HS2                     ( (USB_OTG_GlobalTypeDef *) USBOTG_HS2_BASE_ADDR )    
#define USBOTG_PHY1                     ( (USBOTG_PHY_TypeDef *)USBOTG_PHY1_BASE_ADDR )
#define USBOTG_PHY2                     ( (USBOTG_PHY_TypeDef *)USBOTG_PHY2_BASE_ADDR )
#define ADC1                            ( (ADC_TypeDef *)ADC1_BASE_ADDR )
#define ADC2                            ( (ADC_TypeDef *)ADC2_BASE_ADDR )
#define ADC12_COMMON                    ( (ADC_Common_TypeDef *)(ADC1_BASE_ADDR + 0x0300UL) )
#define ADC3                            ( (ADC_TypeDef *)ADC3_BASE_ADDR )
#define ADC3_COMMON                     ( (ADC_Common_TypeDef *)(ADC3_BASE_ADDR + 0x0300UL) )
#define DAC1                            ( (DAC_TypeDef *)DAC1_BASE_ADDR )
#define DAC2                            ( (DAC_TypeDef *)DAC2_BASE_ADDR )
#define DCMI                            ( (DCMI_TypeDef *)DCMI_BASE_ADDR )
#define AES                             ( (AES_TypeDef *)AES_BASE_ADDR )
#define CORDIC                          ( (CORDIC_TypeDef *)CORDIC_BASE_ADDR )
#define HRNG                            ( (HRNG_TypeDef *)HRNG_BASE_ADDR )
#define HASH                            ( (HASH_TypeDef *)HASH_BASE_ADDR )

#define FMC_NORSRAM                     ( (FMC_NORSRAM_TypeDef *)FMC_REG_BASE_ADDR )
#define FMC_SDRAM						( (FMC_SDRAM_TypeDef *)(FMC_REG_BASE_ADDR + 0x0140UL) )
#define FMC_NAND                        ( (FMC_NAND_TypeDef *)(FMC_REG_BASE_ADDR + 0x0200UL) )
#define OSPI1                           ( (OSPI_TypeDef *) OSPI1_BASE_ADDR )  
#define OSPI2                           ( (OSPI_TypeDef *) OSPI2_BASE_ADDR ) 

#define USB1_DLYB                       ( (DLYB_TypeDef *) USB1_DLYB_REG_BASE_ADDR ) 
#define ETH_DLYB                        ( (DLYB_TypeDef *) ETH_DLYB_REG_BASE_ADDR ) 
#define SDMMC_DLYBS                     ( (DLYB_TypeDef *) SDIO_DLYBS_REG_BASE_ADDR ) 
#define SDMMC_DLYBD                     ( (DLYB_TypeDef *) SDIO_DLYBD_REG_BASE_ADDR ) 
#define OSPI1_DLYB                      ( (DLYB_TypeDef *) OSPI1_DLYB_REG_BASE_ADDR ) 
#define OSPI2_DLYB                      ( (DLYB_TypeDef *) OSPI2_DLYB_REG_BASE_ADDR ) 
#define SDMMC_SAMPLE_DLYB               ( (DLYB_TypeDef *)SDIO_DLYBS_REG_BASE_ADDR )
#define SDMMC_DRIVE_DLYB                ( (DLYB_TypeDef *)SDIO_DLYBD_REG_BASE_ADDR )
#define AES_SPI1                        ( (AES_SPI_TypeDef *)AES_SPI1_BASE_ADDR ) 
#define SDMMC							( (SDMMC_TypeDef *)SDIO_BASE_ADDR )
#define USBOTG1_PHYC                    ( (USB_HS_PHYC_GlobalTypeDef *)USBOTG1_PHYC_BASE_ADDR ) 
#define USBOTG2_PHYC                    ( (USB_HS_PHYC_GlobalTypeDef *)USBOTG2_PHYC_BASE_ADDR ) 

///*-------------------------  printer Peripheral declatation  -------------------------*/
#define NDL                             ( (NDL_TypeDef *)NDL_BASE_ADDR )

#define HEAD                            ( (HEAD_TypeDef *)HEAD_BASE_ADDR)
#define LUT						        ( (LUT_TypeDef *)LUT_BASE_ADDR)
#define DOT1					        ( (DOT_TypeDef *)DOT1_BASE_ADDR)
#define DOT2							( (DOT_TypeDef *)DOT2_BASE_ADDR)
#define DOT3						    ( (DOT_TypeDef *)DOT3_BASE_ADDR)
#define LCFG						    ( (LCFG_TypeDef *)LCFG_BASE_ADDR)

#define STMPWM1                         ( (STMPWM_TypeDef *)STM1_PWM_BASE_ADDR )
#define STMPWM2                         ( (STMPWM_TypeDef *)STM2_PWM_BASE_ADDR )
#define STMPWM3                         ( (STMPWM_TypeDef *)STM3_PWM_BASE_ADDR ) // ¼ò»¯°æ£¬Ö»ÓÐ0x00~0x24¼Ä´æÆ÷
#define STMPWM4                         ( (STMPWM_TypeDef *)STM4_PWM_BASE_ADDR ) // ¼ò»¯°æ£¬Ö»ÓÐ0x00~0x24¼Ä´æÆ÷
#define STMPWM5                         ( (STMPWM_TypeDef *)STM5_PWM_BASE_ADDR ) // ¼ò»¯°æ£¬Ö»ÓÐ0x00~0x24¼Ä´æÆ÷
#define STMPWM6                         ( (STMPWM_TypeDef *)STM6_PWM_BASE_ADDR ) // ¼ò»¯°æ£¬Ö»ÓÐ0x00~0x24¼Ä´æÆ÷

#define DCMPWM1                         ( (DCM_PWM_TypeDef *)DCM1_PWM_BASE_ADDR )
#define DCMPWM2                         ( (DCM_PWM_TypeDef *)DCM2_PWM_BASE_ADDR )
#define DCMPWM3                         ( (DCM_PWM_TypeDef *)DCM3_PWM_BASE_ADDR )
#define DCMPWM4                         ( (DCM_PWM_TypeDef *)DCM4_PWM_BASE_ADDR )
#define DCMPWM5                         ( (DCM_PWM_SE_TypeDef *)DCM5_PWM_BASE_ADDR )
#define DCMPWM6                         ( (DCM_PWM_SE_TypeDef *)DCM6_PWM_BASE_ADDR )

#define DCMPWM1_AREA1				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM1_AREA1_ADDR)
#define DCMPWM2_AREA1				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM2_AREA1_ADDR)
#define DCMPWM3_AREA1				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM3_AREA1_ADDR)
#define DCMPWM4_AREA1				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM4_AREA1_ADDR)
#define DCMPWM5_AREA1				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM5_AREA1_ADDR)
#define DCMPWM6_AREA1				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM6_AREA1_ADDR)

#define DCMPWM1_AREA2				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM1_AREA2_ADDR)
#define DCMPWM2_AREA2				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM2_AREA2_ADDR)
#define DCMPWM3_AREA2				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM3_AREA2_ADDR)
#define DCMPWM4_AREA2				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM4_AREA2_ADDR)

#define DCMPWM1_AREA3				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM1_AREA3_ADDR)
#define DCMPWM2_AREA3				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM2_AREA3_ADDR)
#define DCMPWM3_AREA3				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM3_AREA3_ADDR)
#define DCMPWM4_AREA3				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM4_AREA3_ADDR)
#define DCMPWM5_AREA3				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM5_AREA3_ADDR)
#define DCMPWM6_AREA3				    ( (DCM_PWM_AREA1_TypeDef *)DCMPWM6_AREA3_ADDR)
#define LPT                             ( (LPT_TypeDef *)LPT_BASE_ADDR )

/*------------------  Peripheral_Registers_Bits_Definition  ------------------*/

/***************  Bits definition for SYSCFG_SYSCR  **********************/

#define SYSCFG_SYSCR_ETHMAC_RX_DLYSEL_Pos                   ( 20U )
#define SYSCFG_SYSCR_ETHMAC_RX_DLYSEL_Msk                   ( 0x1UL << SYSCFG_SYSCR_ETHMAC_RX_DLYSEL_Pos )
#define SYSCFG_SYSCR_ETHMAC_RX_DLYSEL                       ( SYSCFG_SYSCR_ETHMAC_RX_DLYSEL_Msk )

#define SYSCFG_SYSCR_BOOT_PUN_Pos                           ( 19U )
#define SYSCFG_SYSCR_BOOT_PUN_Msk                           ( 0x1UL << SYSCFG_SYSCR_BOOT_PUN_Pos )
#define SYSCFG_SYSCR_BOOT_PUN                               ( SYSCFG_SYSCR_BOOT_PUN_Msk )

#define SYSCFG_SYSCR_IR_MODE_Pos                            ( 17U )
#define SYSCFG_SYSCR_IR_MODE_Msk                            ( 0x3UL << SYSCFG_SYSCR_IR_MODE_Pos )
#define SYSCFG_SYSCR_IR_MODE                                ( SYSCFG_SYSCR_IR_MODE_Msk )
#define SYSCFG_SYSCR_IR_MODE_0                              ( 0x1UL << SYSCFG_SYSCR_IR_MODE_Pos )
#define SYSCFG_SYSCR_IR_MODE_1                              ( 0x2UL << SYSCFG_SYSCR_IR_MODE_Pos )

#define SYSCFG_SYSCR_IR_POL_Pos                             ( 16U )
#define SYSCFG_SYSCR_IR_POL_Msk                             ( 0x1UL << SYSCFG_SYSCR_IR_POL_Pos )
#define SYSCFG_SYSCR_IR_POL                                 ( SYSCFG_SYSCR_IR_POL_Msk )

#define SYSCFG_SYSCR_EPIS_Pos                               ( 13U )
#define SYSCFG_SYSCR_EPIS_Msk                               ( 0x7UL << SYSCFG_SYSCR_EPIS_Pos )
#define SYSCFG_SYSCR_EPIS                                   ( SYSCFG_SYSCR_EPIS_Msk )
#define SYSCFG_SYSCR_EPIS_0                                 ( 0x1UL << SYSCFG_SYSCR_EPIS_Pos )
#define SYSCFG_SYSCR_EPIS_1                                 ( 0x2UL << SYSCFG_SYSCR_EPIS_Pos )
#define SYSCFG_SYSCR_EPIS_2                                 ( 0x4UL << SYSCFG_SYSCR_EPIS_Pos )

#define SYSCFG_SYSCR_ETHMAC_TX_CLKGE_Pos                    ( 12U )
#define SYSCFG_SYSCR_ETHMAC_TX_CLKGE_Msk                    ( 0x1UL << SYSCFG_SYSCR_ETHMAC_TX_CLKGE_Pos )
#define SYSCFG_SYSCR_ETHMAC_TX_CLKGE                        ( SYSCFG_SYSCR_ETHMAC_TX_CLKGE_Msk )

#define SYSCFG_SYSCR_BKPSRAM_LOCK_Pos                       ( 11U )
#define SYSCFG_SYSCR_BKPSRAM_LOCK_Msk                       ( 0x1UL << SYSCFG_SYSCR_BKPSRAM_LOCK_Pos )
#define SYSCFG_SYSCR_BKPSRAM_LOCK                           ( SYSCFG_SYSCR_BKPSRAM_LOCK_Msk )

#define SYSCFG_SYSCR_SRAM3_LOCK_Pos                         ( 10U )
#define SYSCFG_SYSCR_SRAM3_LOCK_Msk                         ( 0x1UL << SYSCFG_SYSCR_SRAM3_LOCK_Pos )
#define SYSCFG_SYSCR_SRAM3_LOCK                             ( SYSCFG_SYSCR_SRAM3_LOCK_Msk )

#define SYSCFG_SYSCR_SRAM1_LOCK_Pos                         ( 9U )
#define SYSCFG_SYSCR_SRAM1_LOCK_Msk                         ( 0x1UL << SYSCFG_SYSCR_SRAM1_LOCK_Pos )
#define SYSCFG_SYSCR_SRAM1_LOCK                             ( SYSCFG_SYSCR_SRAM1_LOCK_Msk )

#define SYSCFG_SYSCR_SDRAM_IO_SWP_Pos                       ( 7U )
#define SYSCFG_SYSCR_SDRAM_IO_SWP_Msk                       ( 0x1UL << SYSCFG_SYSCR_SDRAM_IO_SWP_Pos )
#define SYSCFG_SYSCR_SDRAM_IO_SWP                           ( SYSCFG_SYSCR_SDRAM_IO_SWP_Msk )

#define SYSCFG_SYSCR_FMC_SWP_Pos                            ( 4U )
#define SYSCFG_SYSCR_FMC_SWP_Msk                            ( 0x3UL << SYSCFG_SYSCR_FMC_SWP_Pos )
#define SYSCFG_SYSCR_FMC_SWP                                ( SYSCFG_SYSCR_FMC_SWP_Msk )
#define SYSCFG_SYSCR_FMC_SWP_0                              ( 0x1UL << SYSCFG_SYSCR_FMC_SWP_Pos )
#define SYSCFG_SYSCR_FMC_SWP_1                              ( 0x2UL << SYSCFG_SYSCR_FMC_SWP_Pos )

#define SYSCFG_SYSCR_LVD_LOCK_Pos                           ( 2U )
#define SYSCFG_SYSCR_LVD_LOCK_Msk                           ( 0x1UL << SYSCFG_SYSCR_LVD_LOCK_Pos )
#define SYSCFG_SYSCR_LVD_LOCK                               ( SYSCFG_SYSCR_LVD_LOCK_Msk )

#define SYSCFG_SYSCR_LOCKUP_LOCK_Pos                        ( 0U )
#define SYSCFG_SYSCR_LOCKUP_LOCK_Msk                        ( 0x1UL << SYSCFG_SYSCR_LOCKUP_LOCK_Pos )
#define SYSCFG_SYSCR_LOCKUP_LOCK                            ( SYSCFG_SYSCR_LOCKUP_LOCK_Msk )


/***************  Bits definition for SYSCFG_WMR  **********************/

#define SYSCFG_WMR_BOOTDEVICE_Pos                           ( 8U )
#define SYSCFG_WMR_BOOTDEVICE_Msk                           ( 0x3UL << SYSCFG_WMR_RTC_READY_Pos )
#define SYSCFG_WMR_BOOTDEVICE                               ( SYSCFG_WMR_RTC_READY_Msk )

#define SYSCFG_WMR_RTCREADY_Pos                             ( 6U )
#define SYSCFG_WMR_RTCREADY_Msk                             ( 0x1UL << SYSCFG_WMR_RTCREADY_Pos )
#define SYSCFG_WMR_RTCREADY                                 ( SYSCFG_WMR_RTCREADY_Msk )

#define SYSCFG_WMR_BOOTMODE_Pos                             ( 3U )
#define SYSCFG_WMR_BOOTMODE_Msk                             ( 0x1UL << SYSCFG_WMR_BOOTMODE_Pos )
#define SYSCFG_WMR_BOOTMODE                                 ( SYSCFG_WMR_BOOTMODE_Msk )


/***************  Bits definition for SYSCFG_VER  **********************/

#define SYSCFG_VER_VERSION_Pos                              ( 0U )
#define SYSCFG_VER_VERSION_Msk                              ( 0xffffffffUL << SYSCFG_VER_VERSION_Pos )
#define SYSCFG_VER_VERSION                                  ( SYSCFG_VER_VERSION_Msk )


/***************  Bits definition for SYSCFG_PHYCFG  **********************/

#define SYSCFG_PHYCFG_USB1_ULPI_DLYSEL_Pos                  ( 8U )
#define SYSCFG_PHYCFG_USB1_ULPI_DLYSEL_Msk                  ( 0x1UL << SYSCFG_PHYCFG_USB1_ULPI_DLYSEL_Pos )
#define SYSCFG_PHYCFG_USB1_ULPI_DLYSEL                      ( SYSCFG_PHYCFG_USB1_ULPI_DLYSEL_Msk )

#define SYSCFG_PHYCFG_USB2_PHY_RSTN_Pos                     ( 4U )
#define SYSCFG_PHYCFG_USB2_PHY_RSTN_Msk                     ( 0x1UL << SYSCFG_PHYCFG_USB2_PHY_RSTN_Pos )
#define SYSCFG_PHYCFG_USB2_PHY_RSTN                         ( SYSCFG_PHYCFG_USB2_PHY_RSTN_Msk )

#define SYSCFG_PHYCFG_USB1_PHY_RSTN_Pos                     ( 0U )
#define SYSCFG_PHYCFG_USB1_PHY_RSTN_Msk                     ( 0x1UL << SYSCFG_PHYCFG_USB1_PHY_RSTN_Pos )
#define SYSCFG_PHYCFG_USB1_PHY_RSTN                         ( SYSCFG_PHYCFG_USB1_PHY_RSTN_Msk )

/***************  Bits definition for SYSCFG_RAMECCIR  **********************/

#define SYSCFG_RAMECCIR_BKPSRAM_DED_IE_Pos                  ( 9U )
#define SYSCFG_RAMECCIR_BKPSRAM_DED_IE_Msk                  ( 0x1UL << SYSCFG_RAMECCIR_BKPSRAM_DED_IE_Pos )
#define SYSCFG_RAMECCIR_BKPSRAM_DED_IE                      ( SYSCFG_RAMECCIR_BKPSRAM_DED_IE_Msk )

#define SYSCFG_RAMECCIR_BKPSRAM_SEC_IE_Pos                  ( 8U )
#define SYSCFG_RAMECCIR_BKPSRAM_SEC_IE_Msk                  ( 0x1UL << SYSCFG_RAMECCIR_BKPSRAM_SEC_IE_Pos )
#define SYSCFG_RAMECCIR_BKPSRAM_SEC_IE                      ( SYSCFG_RAMECCIR_BKPSRAM_SEC_IE_Msk )

#define SYSCFG_RAMECCIR_SRAM3_DED_IE_Pos                    ( 5U )
#define SYSCFG_RAMECCIR_SRAM3_DED_IE_Msk                    ( 0x1UL << SYSCFG_RAMECCIR_SRAM3_DED_IE_Pos )
#define SYSCFG_RAMECCIR_SRAM3_DED_IE                        ( SYSCFG_RAMECCIR_SRAM3_DED_IE_Msk )

#define SYSCFG_RAMECCIR_SRAM3_SEC_IE_Pos                    ( 4U )
#define SYSCFG_RAMECCIR_SRAM3_SEC_IE_Msk                    ( 0x1UL << SYSCFG_RAMECCIR_SRAM3_SEC_IE_Pos )
#define SYSCFG_RAMECCIR_SRAM3_SEC_IE                        ( SYSCFG_RAMECCIR_SRAM3_SEC_IE_Msk )

#define SYSCFG_RAMECCIR_SRAM1_DED_IE_Pos                    ( 1U )
#define SYSCFG_RAMECCIR_SRAM1_DED_IE_Msk                    ( 0x1UL << SYSCFG_RAMECCIR_SRAM1_DED_IE_Pos )
#define SYSCFG_RAMECCIR_SRAM1_DED_IE                        ( SYSCFG_RAMECCIR_SRAM1_DED_IE_Msk )

#define SYSCFG_RAMECCIR_SRAM1_SEC_IE_Pos                    ( 0U )
#define SYSCFG_RAMECCIR_SRAM1_SEC_IE_Msk                    ( 0x1UL << SYSCFG_RAMECCIR_SRAM1_SEC_IE_Pos )
#define SYSCFG_RAMECCIR_SRAM1_SEC_IE                        ( SYSCFG_RAMECCIR_SRAM1_SEC_IE_Msk )


/***************  Bits definition for SYSCFG_RAMECCSR  **********************/

#define SYSCFG_RAMECCSR_BKPSRAM_DED_IF_Pos                  ( 9U )
#define SYSCFG_RAMECCSR_BKPSRAM_DED_IF_Msk                  ( 0x1UL << SYSCFG_RAMECCSR_BKPSRAM_DED_IF_Pos )
#define SYSCFG_RAMECCSR_BKPSRAM_DED_IF                      ( SYSCFG_RAMECCSR_BKPSRAM_DED_IF_Msk )

#define SYSCFG_RAMECCSR_BKPSRAM_SEC_IF_Pos                  ( 8U )
#define SYSCFG_RAMECCSR_BKPSRAM_SEC_IF_Msk                  ( 0x1UL << SYSCFG_RAMECCSR_BKPSRAM_SEC_IF_Pos )
#define SYSCFG_RAMECCSR_BKPSRAM_SEC_IF                      ( SYSCFG_RAMECCSR_BKPSRAM_SEC_IF_Msk )

#define SYSCFG_RAMECCSR_SRAM3_DED_IF_Pos                    ( 5U )
#define SYSCFG_RAMECCSR_SRAM3_DED_IF_Msk                    ( 0x1UL << SYSCFG_RAMECCSR_SRAM3_DED_IF_Pos )
#define SYSCFG_RAMECCSR_SRAM3_DED_IF                        ( SYSCFG_RAMECCSR_SRAM3_DED_IF_Msk )

#define SYSCFG_RAMECCSR_SRAM3_SEC_IF_Pos                    ( 4U )
#define SYSCFG_RAMECCSR_SRAM3_SEC_IF_Msk                    ( 0x1UL << SYSCFG_RAMECCSR_SRAM3_SEC_IF_Pos )
#define SYSCFG_RAMECCSR_SRAM3_SEC_IF                        ( SYSCFG_RAMECCSR_SRAM3_SEC_IF_Msk )

#define SYSCFG_RAMECCSR_SRAM1_DED_IF_Pos                    ( 1U )
#define SYSCFG_RAMECCSR_SRAM1_DED_IF_Msk                    ( 0x1UL << SYSCFG_RAMECCSR_SRAM1_DED_IF_Pos )
#define SYSCFG_RAMECCSR_SRAM1_DED_IF                        ( SYSCFG_RAMECCSR_SRAM1_DED_IF_Msk )

#define SYSCFG_RAMECCSR_SRAM1_SEC_IF_Pos                    ( 0U )
#define SYSCFG_RAMECCSR_SRAM1_SEC_IF_Msk                    ( 0x1UL << SYSCFG_RAMECCSR_SRAM1_SEC_IF_Pos )
#define SYSCFG_RAMECCSR_SRAM1_SEC_IF                        ( SYSCFG_RAMECCSR_SRAM1_SEC_IF_Msk )


/***************  Bits definition for SYSCFG_RAMECCICR  **********************/

#define SYSCFG_RAMECCICR_BKPSRAM_DED_IC_Pos                  ( 9U )
#define SYSCFG_RAMECCICR_BKPSRAM_DED_IC_Msk                  ( 0x1UL << SYSCFG_RAMECCICR_BKPSRAM_DED_IC_Pos )
#define SYSCFG_RAMECCICR_BKPSRAM_DED_IC                      ( SYSCFG_RAMECCICR_BKPSRAM_DED_IC_Msk )

#define SYSCFG_RAMECCICR_BKPSRAM_SEC_IC_Pos                  ( 8U )
#define SYSCFG_RAMECCICR_BKPSRAM_SEC_IC_Msk                  ( 0x1UL << SYSCFG_RAMECCICR_BKPSRAM_SEC_IC_Pos )
#define SYSCFG_RAMECCICR_BKPSRAM_SEC_IC                      ( SYSCFG_RAMECCICR_BKPSRAM_SEC_IC_Msk )

#define SYSCFG_RAMECCICR_SRAM3_DED_IC_Pos                    ( 5U )
#define SYSCFG_RAMECCICR_SRAM3_DED_IC_Msk                    ( 0x1UL << SYSCFG_RAMECCICR_SRAM3_DED_IC_Pos )
#define SYSCFG_RAMECCICR_SRAM3_DED_IC                        ( SYSCFG_RAMECCICR_SRAM3_DED_IC_Msk )

#define SYSCFG_RAMECCICR_SRAM3_SEC_IC_Pos                    ( 4U )
#define SYSCFG_RAMECCICR_SRAM3_SEC_IC_Msk                    ( 0x1UL << SYSCFG_RAMECCICR_SRAM3_SEC_IC_Pos )
#define SYSCFG_RAMECCICR_SRAM3_SEC_IC                        ( SYSCFG_RAMECCICR_SRAM3_SEC_IC_Msk )

#define SYSCFG_RAMECCICR_SRAM1_DED_IC_Pos                    ( 1U )
#define SYSCFG_RAMECCICR_SRAM1_DED_IC_Msk                    ( 0x1UL << SYSCFG_RAMECCICR_SRAM1_DED_IC_Pos )
#define SYSCFG_RAMECCICR_SRAM1_DED_IC                        ( SYSCFG_RAMECCICR_SRAM1_DED_IC_Msk )

#define SYSCFG_RAMECCICR_SRAM1_SEC_IC_Pos                    ( 0U )
#define SYSCFG_RAMECCICR_SRAM1_SEC_IC_Msk                    ( 0x1UL << SYSCFG_RAMECCICR_SRAM1_SEC_IC_Pos )
#define SYSCFG_RAMECCICR_SRAM1_SEC_IC                        ( SYSCFG_RAMECCICR_SRAM1_SEC_IC_Msk )


/***************  Bits definition for SYSCFG_GPIO5VOCR1  **********************/

#define SYSCFG_GPIO5VOCR1_PK13OE5V_Pos                      ( 31U )
#define SYSCFG_GPIO5VOCR1_PK13OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK13OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK13OE5V                          ( SYSCFG_GPIO5VOCR1_PK13OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK12OE5V_Pos                      ( 30U )
#define SYSCFG_GPIO5VOCR1_PK12OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK12OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK12OE5V                          ( SYSCFG_GPIO5VOCR1_PK12OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK11OE5V_Pos                      ( 29U )
#define SYSCFG_GPIO5VOCR1_PK11OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK11OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK11OE5V                          ( SYSCFG_GPIO5VOCR1_PK11OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK10OE5V_Pos                      ( 28U )
#define SYSCFG_GPIO5VOCR1_PK10OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK10OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK10OE5V                          ( SYSCFG_GPIO5VOCR1_PK10OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK9OE5V_Pos                      ( 27U )
#define SYSCFG_GPIO5VOCR1_PK9OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK9OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK9OE5V                          ( SYSCFG_GPIO5VOCR1_PK9OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK8OE5V_Pos                      ( 26U )
#define SYSCFG_GPIO5VOCR1_PK8OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK8OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK8OE5V                          ( SYSCFG_GPIO5VOCR1_PK8OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK7OE5V_Pos                      ( 25U )
#define SYSCFG_GPIO5VOCR1_PK7OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK7OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK7OE5V                          ( SYSCFG_GPIO5VOCR1_PK7OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK6OE5V_Pos                      ( 24U )
#define SYSCFG_GPIO5VOCR1_PK6OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK6OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK6OE5V                          ( SYSCFG_GPIO5VOCR1_PK6OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK5OE5V_Pos                      ( 23U )
#define SYSCFG_GPIO5VOCR1_PK5OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK5OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK5OE5V                          ( SYSCFG_GPIO5VOCR1_PK5OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK4OE5V_Pos                      ( 22U )
#define SYSCFG_GPIO5VOCR1_PK4OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK4OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK4OE5V                          ( SYSCFG_GPIO5VOCR1_PK4OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK3OE5V_Pos                      ( 21U )
#define SYSCFG_GPIO5VOCR1_PK3OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK3OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK3OE5V                          ( SYSCFG_GPIO5VOCR1_PK3OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK2OE5V_Pos                      ( 20U )
#define SYSCFG_GPIO5VOCR1_PK2OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK2OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK2OE5V                          ( SYSCFG_GPIO5VOCR1_PK2OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK1OE5V_Pos                      ( 19U )
#define SYSCFG_GPIO5VOCR1_PK1OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK1OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK1OE5V                          ( SYSCFG_GPIO5VOCR1_PK1OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PK0OE5V_Pos                      ( 18U )
#define SYSCFG_GPIO5VOCR1_PK0OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PK0OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PK0OE5V                          ( SYSCFG_GPIO5VOCR1_PK0OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PJ15OE5V_Pos                      ( 17U )
#define SYSCFG_GPIO5VOCR1_PJ15OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PJ15OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PJ15OE5V                          ( SYSCFG_GPIO5VOCR1_PJ15OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PJ14OE5V_Pos                      ( 16U )
#define SYSCFG_GPIO5VOCR1_PJ14OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PJ14OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PJ14OE5V                          ( SYSCFG_GPIO5VOCR1_PJ14OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PJ13OE5V_Pos                      ( 15U )
#define SYSCFG_GPIO5VOCR1_PJ13OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PJ13OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PJ13OE5V                          ( SYSCFG_GPIO5VOCR1_PJ13OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PJ12OE5V_Pos                      ( 14U )
#define SYSCFG_GPIO5VOCR1_PJ12OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PJ12OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PJ12OE5V                          ( SYSCFG_GPIO5VOCR1_PJ12OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PJ11OE5V_Pos                      ( 13U )
#define SYSCFG_GPIO5VOCR1_PJ11OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PJ11OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PJ11OE5V                          ( SYSCFG_GPIO5VOCR1_PJ11OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PJ10OE5V_Pos                      ( 12U )
#define SYSCFG_GPIO5VOCR1_PJ10OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PJ10OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PJ10OE5V                          ( SYSCFG_GPIO5VOCR1_PJ10OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PJ9OE5V_Pos                      ( 11U )
#define SYSCFG_GPIO5VOCR1_PJ9OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PJ9OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PJ9OE5V                          ( SYSCFG_GPIO5VOCR1_PJ9OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PJ8OE5V_Pos                      ( 10U )
#define SYSCFG_GPIO5VOCR1_PJ8OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PJ8OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PJ8OE5V                          ( SYSCFG_GPIO5VOCR1_PJ8OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PJ7OE5V_Pos                      ( 9U )
#define SYSCFG_GPIO5VOCR1_PJ7OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PJ7OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PJ7OE5V                          ( SYSCFG_GPIO5VOCR1_PJ7OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PJ6OE5V_Pos                      ( 8U )
#define SYSCFG_GPIO5VOCR1_PJ6OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PJ6OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PJ6OE5V                          ( SYSCFG_GPIO5VOCR1_PJ6OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PI14OE5V_Pos                      ( 7U )
#define SYSCFG_GPIO5VOCR1_PI14OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PI14OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PI14OE5V                          ( SYSCFG_GPIO5VOCR1_PI14OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PH12OE5V_Pos                      ( 6U )
#define SYSCFG_GPIO5VOCR1_PH12OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PH12OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PH12OE5V                          ( SYSCFG_GPIO5VOCR1_PH12OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PH11OE5V_Pos                      ( 5U )
#define SYSCFG_GPIO5VOCR1_PH11OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PH11OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PH11OE5V                          ( SYSCFG_GPIO5VOCR1_PH11OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PH10OE5V_Pos                      ( 4U )
#define SYSCFG_GPIO5VOCR1_PH10OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PH10OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PH10OE5V                          ( SYSCFG_GPIO5VOCR1_PH10OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PH9OE5V_Pos                      ( 3U )
#define SYSCFG_GPIO5VOCR1_PH9OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PH9OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PH9OE5V                          ( SYSCFG_GPIO5VOCR1_PH9OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PH8OE5V_Pos                      ( 2U )
#define SYSCFG_GPIO5VOCR1_PH8OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PH8OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PH8OE5V                          ( SYSCFG_GPIO5VOCR1_PH8OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PH7OE5V_Pos                      ( 1U )
#define SYSCFG_GPIO5VOCR1_PH7OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PH7OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PH7OE5V                          ( SYSCFG_GPIO5VOCR1_PH7OE5V_Msk )

#define SYSCFG_GPIO5VOCR1_PH6OE5V_Pos                      ( 0U )
#define SYSCFG_GPIO5VOCR1_PH6OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR1_PH6OE5V_Pos )
#define SYSCFG_GPIO5VOCR1_PH6OE5V                          ( SYSCFG_GPIO5VOCR1_PH6OE5V_Msk )


/***************  Bits definition for SYSCFG_GPIO5VOCR2  **********************/

#define SYSCFG_GPIO5VOCR2_PP15OE5V_Pos                      ( 17U )
#define SYSCFG_GPIO5VOCR2_PP15OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PP15OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PP15OE5V                          ( SYSCFG_GPIO5VOCR2_PP15OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PP14OE5V_Pos                      ( 16U )
#define SYSCFG_GPIO5VOCR2_PP14OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PP14OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PP14OE5V                          ( SYSCFG_GPIO5VOCR2_PP14OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PP13OE5V_Pos                      ( 15U )
#define SYSCFG_GPIO5VOCR2_PP13OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PP13OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PP13OE5V                          ( SYSCFG_GPIO5VOCR2_PP13OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PP12OE5V_Pos                      ( 14U )
#define SYSCFG_GPIO5VOCR2_PP12OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PP12OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PP12OE5V                          ( SYSCFG_GPIO5VOCR2_PP12OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PP11OE5V_Pos                      ( 13U )
#define SYSCFG_GPIO5VOCR2_PP11OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PP11OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PP11OE5V                          ( SYSCFG_GPIO5VOCR2_PP11OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PP10OE5V_Pos                      ( 12U )
#define SYSCFG_GPIO5VOCR2_PP10OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PP10OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PP10OE5V                          ( SYSCFG_GPIO5VOCR2_PP10OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PO15OE5V_Pos                      ( 11U )
#define SYSCFG_GPIO5VOCR2_PO15OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PO15OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PO15OE5V                          ( SYSCFG_GPIO5VOCR2_PO15OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PO14OE5V_Pos                      ( 10U )
#define SYSCFG_GPIO5VOCR2_PO14OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PO14OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PO14OE5V                          ( SYSCFG_GPIO5VOCR2_PO14OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PO13OE5V_Pos                      ( 9U )
#define SYSCFG_GPIO5VOCR2_PO13OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PO13OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PO13OE5V                          ( SYSCFG_GPIO5VOCR2_PO13OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PO12OE5V_Pos                      ( 8U )
#define SYSCFG_GPIO5VOCR2_PO12OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PO12OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PO12OE5V                          ( SYSCFG_GPIO5VOCR2_PO12OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PO3OE5V_Pos                      ( 7U )
#define SYSCFG_GPIO5VOCR2_PO3OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PO3OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PO3OE5V                          ( SYSCFG_GPIO5VOCR2_PO3OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PO2OE5V_Pos                      ( 6U )
#define SYSCFG_GPIO5VOCR2_PO2OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PO2OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PO2OE5V                          ( SYSCFG_GPIO5VOCR2_PO2OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PO1OE5V_Pos                      ( 5U )
#define SYSCFG_GPIO5VOCR2_PO1OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PO1OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PO1OE5V                          ( SYSCFG_GPIO5VOCR2_PO1OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PO0OE5V_Pos                      ( 4U )
#define SYSCFG_GPIO5VOCR2_PO0OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PO0OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PO0OE5V                          ( SYSCFG_GPIO5VOCR2_PO0OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PM13OE5V_Pos                      ( 3U )
#define SYSCFG_GPIO5VOCR2_PM13OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PM13OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PM13OE5V                          ( SYSCFG_GPIO5VOCR2_PM13OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PM12OE5V_Pos                      ( 2U )
#define SYSCFG_GPIO5VOCR2_PM12OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PM12OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PM12OE5V                          ( SYSCFG_GPIO5VOCR2_PM12OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PM11OE5V_Pos                      ( 1U )
#define SYSCFG_GPIO5VOCR2_PM11OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PM11OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PM11OE5V                          ( SYSCFG_GPIO5VOCR2_PM11OE5V_Msk )

#define SYSCFG_GPIO5VOCR2_PM10OE5V_Pos                      ( 0U )
#define SYSCFG_GPIO5VOCR2_PM10OE5V_Msk                      ( 0x1UL << SYSCFG_GPIO5VOCR2_PM10OE5V_Pos )
#define SYSCFG_GPIO5VOCR2_PM10OE5V                          ( SYSCFG_GPIO5VOCR2_PM10OE5V_Msk )


/***************  Bits definition for RCC_RCR  **********************/

#define RCC_RCR_SRST_MAP_Pos                                ( 31U )
#define RCC_RCR_SRST_MAP_Msk                                ( 0x1UL << RCC_RCR_SRST_MAP_Pos )
#define RCC_RCR_SRST_MAP                                    ( RCC_RCR_SRST_MAP_Msk )

#define RCC_RCR_IWDTRST_DIS_Pos                             ( 8U )
#define RCC_RCR_IWDTRST_DIS_Msk                             ( 0xFFUL << RCC_RCR_IWDTRST_DIS_Pos )
#define RCC_RCR_IWDTRST_DIS                                 ( RCC_RCR_IWDTRST_DIS_Msk )

#define RCC_RCR_LOCKRST_EN_Pos                              ( 3U )
#define RCC_RCR_LOCKRST_EN_Msk                              ( 0x1UL << RCC_RCR_LOCKRST_EN_Pos )
#define RCC_RCR_LOCKRST_EN                                  ( RCC_RCR_LOCKRST_EN_Msk )

#define RCC_RCR_IWDTRST_EN_Pos                              ( 2U )
#define RCC_RCR_IWDTRST_EN_Msk                              ( 0x1UL << RCC_RCR_IWDTRST_EN_Pos )
#define RCC_RCR_IWDTRST_EN                                  ( RCC_RCR_IWDTRST_EN_Msk )

#define RCC_RCR_WDTRST_EN_Pos                               ( 1U )
#define RCC_RCR_WDTRST_EN_Msk                               ( 0x1UL << RCC_RCR_WDTRST_EN_Pos )
#define RCC_RCR_WDTRST_EN                                   ( RCC_RCR_WDTRST_EN_Msk )

#define RCC_RCR_LVDRST_EN_Pos                               ( 0U )
#define RCC_RCR_LVDRST_EN_Msk                               ( 0x1UL << RCC_RCR_LVDRST_EN_Pos )
#define RCC_RCR_LVDRST_EN                                   ( RCC_RCR_LVDRST_EN_Msk )


/***************  Bits definition for RCC_RSR  **********************/

#define RCC_RSR_RSTFLAGCLR_Pos                             ( 16U )
#define RCC_RSR_RSTFLAGCLR_Msk                             ( 0x1UL << RCC_RSR_RSTFLAGCLR_Pos )
#define RCC_RSR_RSTFLAGCLR                                 ( RCC_RSR_RSTFLAGCLR_Msk )

#define RCC_RSR_PWRRSTF_Pos                                ( 10U )
#define RCC_RSR_PWRRSTF_Msk                                ( 0x1UL << RCC_RSR_PWRRSTF_Pos )
#define RCC_RSR_PWRRSTF                                    ( RCC_RSR_PWRRSTF_Msk )

#define RCC_RSR_POR12RSTF_Pos                              ( 9U )
#define RCC_RSR_POR12RSTF_Msk                              ( 0x1UL << RCC_RSR_POR12RSTF_Pos )
#define RCC_RSR_POR12RSTF                                  ( RCC_RSR_POR12RSTF_Msk )

#define RCC_RSR_SRSTF_Pos                                  ( 8U )
#define RCC_RSR_SRSTF_Msk                                  ( 0x1UL << RCC_RSR_SRSTF_Pos )
#define RCC_RSR_SRSTF                                      ( RCC_RSR_SRSTF_Msk )

#define RCC_RSR_RSTNF_Pos                                  ( 5U )
#define RCC_RSR_RSTNF_Msk                                  ( 0x1UL << RCC_RSR_RSTNF_Pos )
#define RCC_RSR_RSTNF                                      ( RCC_RSR_RSTNF_Msk )

#define RCC_RSR_SYSREQRSTF_Pos                             ( 4U )
#define RCC_RSR_SYSREQRSTF_Msk                             ( 0x1UL << RCC_RSR_SYSREQRSTF_Pos )
#define RCC_RSR_SYSREQRSTF                                 ( RCC_RSR_SYSREQRSTF_Msk )

#define RCC_RSR_LOCKUPRSTF_Pos                             ( 3U )
#define RCC_RSR_LOCKUPRSTF_Msk                             ( 0x1UL << RCC_RSR_LOCKUPRSTF_Pos )
#define RCC_RSR_LOCKUPRSTF                                 ( RCC_RSR_LOCKUPRSTF_Msk )

#define RCC_RSR_IWDTRSTF_Pos                               ( 2U )
#define RCC_RSR_IWDTRSTF_Msk                               ( 0x1UL << RCC_RSR_IWDTRSTF_Pos )
#define RCC_RSR_IWDTRSTF                                   ( RCC_RSR_IWDTRSTF_Msk )

#define RCC_RSR_WDTRSTF_Pos                                ( 1U )
#define RCC_RSR_WDTRSTF_Msk                                ( 0x1UL << RCC_RSR_WDTRSTF_Pos )
#define RCC_RSR_WDTRSTF                                    ( RCC_RSR_WDTRSTF_Msk )

#define RCC_RSR_LVDRSTF_Pos                                ( 0U )
#define RCC_RSR_LVDRSTF_Msk                                ( 0x1UL << RCC_RSR_LVDRSTF_Pos )
#define RCC_RSR_LVDRSTF                                    ( RCC_RSR_LVDRSTF_Msk )


/***************  Bits definition for RCC_AHB1RSTR  **********************/

#define RCC_AHB1RSTR_FDCAN2RST_Pos                      ( 23U )
#define RCC_AHB1RSTR_FDCAN2RST_Msk                      ( 0x1UL << RCC_AHB1RSTR_FDCAN2RST_Pos )
#define RCC_AHB1RSTR_FDCAN2RST                          ( RCC_AHB1RSTR_FDCAN2RST_Msk )

#define RCC_AHB1RSTR_FDCAN1RST_Pos                      ( 22U )
#define RCC_AHB1RSTR_FDCAN1RST_Msk                      ( 0x1UL << RCC_AHB1RSTR_FDCAN1RST_Pos )
#define RCC_AHB1RSTR_FDCAN1RST                          ( RCC_AHB1RSTR_FDCAN1RST_Msk )

#define RCC_AHB1RSTR_USB2CRST_Pos                        ( 21U )
#define RCC_AHB1RSTR_USB2CRST_Msk                        ( 0x1UL << RCC_AHB1RSTR_USB2CRST_Pos )
#define RCC_AHB1RSTR_USB2CRST                            ( RCC_AHB1RSTR_USB2CRST_Msk )

#define RCC_AHB1RSTR_USB1CRST_Pos                        ( 20U )
#define RCC_AHB1RSTR_USB1CRST_Msk                        ( 0x1UL << RCC_AHB1RSTR_USB1CRST_Pos )
#define RCC_AHB1RSTR_USB1CRST                            ( RCC_AHB1RSTR_USB1CRST_Msk )

#define RCC_AHB1RSTR_SPI6RST_Pos                         ( 15U )
#define RCC_AHB1RSTR_SPI6RST_Msk                         ( 0x1UL << RCC_AHB1RSTR_SPI6RST_Pos )
#define RCC_AHB1RSTR_SPI6RST                             ( RCC_AHB1RSTR_SPI6RST_Msk )

#define RCC_AHB1RSTR_SPI5RST_Pos                         ( 14U )
#define RCC_AHB1RSTR_SPI5RST_Msk                         ( 0x1UL << RCC_AHB1RSTR_SPI5RST_Pos )
#define RCC_AHB1RSTR_SPI5RST                             ( RCC_AHB1RSTR_SPI5RST_Msk )

#define RCC_AHB1RSTR_SPI4RST_Pos                         ( 13U )
#define RCC_AHB1RSTR_SPI4RST_Msk                         ( 0x1UL << RCC_AHB1RSTR_SPI4RST_Pos )
#define RCC_AHB1RSTR_SPI4RST                             ( RCC_AHB1RSTR_SPI4RST_Msk )

#define RCC_AHB1RSTR_SPI3RST_Pos                         ( 12U )
#define RCC_AHB1RSTR_SPI3RST_Msk                         ( 0x1UL << RCC_AHB1RSTR_SPI3RST_Pos )
#define RCC_AHB1RSTR_SPI3RST                             ( RCC_AHB1RSTR_SPI3RST_Msk )

#define RCC_AHB1RSTR_SPI2RST_Pos                         ( 11U )
#define RCC_AHB1RSTR_SPI2RST_Msk                         ( 0x1UL << RCC_AHB1RSTR_SPI2RST_Pos )
#define RCC_AHB1RSTR_SPI2RST                             ( RCC_AHB1RSTR_SPI2RST_Msk )

#define RCC_AHB1RSTR_SPI1RST_Pos                         ( 10U )
#define RCC_AHB1RSTR_SPI1RST_Msk                         ( 0x1UL << RCC_AHB1RSTR_SPI1RST_Pos )
#define RCC_AHB1RSTR_SPI1RST                             ( RCC_AHB1RSTR_SPI1RST_Msk )

#define RCC_AHB1RSTR_DMA2DRST_Pos                        ( 9U )
#define RCC_AHB1RSTR_DMA2DRST_Msk                        ( 0x1UL << RCC_AHB1RSTR_DMA2DRST_Pos )
#define RCC_AHB1RSTR_DMA2DRST                            ( RCC_AHB1RSTR_DMA2DRST_Msk )

#define RCC_AHB1RSTR_ETHRST_Pos                          ( 6U )
#define RCC_AHB1RSTR_ETHRST_Msk                          ( 0x1UL << RCC_AHB1RSTR_ETHRST_Pos )
#define RCC_AHB1RSTR_ETHRST                              ( RCC_AHB1RSTR_ETHRST_Msk )

#define RCC_AHB1RSTR_CRCRST_Pos                          ( 5U )
#define RCC_AHB1RSTR_CRCRST_Msk                          ( 0x1UL << RCC_AHB1RSTR_CRCRST_Pos )
#define RCC_AHB1RSTR_CRCRST                              ( RCC_AHB1RSTR_CRCRST_Msk )

#define RCC_AHB1RSTR_DMA2RST_Pos                         ( 1U )
#define RCC_AHB1RSTR_DMA2RST_Msk                         ( 0x1UL << RCC_AHB1RSTR_DMA2RST_Pos )
#define RCC_AHB1RSTR_DMA2RST                             ( RCC_AHB1RSTR_DMA2RST_Msk )

#define RCC_AHB1RSTR_DMA1RST_Pos                         ( 0U )
#define RCC_AHB1RSTR_DMA1RST_Msk                         ( 0x1UL << RCC_AHB1RSTR_DMA1RST_Pos )
#define RCC_AHB1RSTR_DMA1RST                             ( RCC_AHB1RSTR_DMA1RST_Msk )


/***************  Bits definition for RCC_AHB2RSTR  **********************/

#define RCC_AHB2RSTR_THMRST_Pos                          ( 31U )
#define RCC_AHB2RSTR_THMRST_Msk                          ( 0x1UL << RCC_AHB2RSTR_THMRST_Pos )
#define RCC_AHB2RSTR_THMRST                              ( RCC_AHB2RSTR_THMRST_Msk )

#define RCC_AHB2RSTR_FDCAN3RST_Pos                       ( 28U )
#define RCC_AHB2RSTR_FDCAN3RST_Msk                       ( 0x1UL << RCC_AHB2RSTR_FDCAN3RST_Pos )
#define RCC_AHB2RSTR_FDCAN3RST                           ( RCC_AHB2RSTR_FDCAN3RST_Msk )

#define RCC_AHB2RSTR_UACRST_Pos                          ( 27U )
#define RCC_AHB2RSTR_UACRST_Msk                          ( 0x1UL << RCC_AHB2RSTR_UACRST_Pos )
#define RCC_AHB2RSTR_UACRST                              ( RCC_AHB2RSTR_UACRST_Msk )

#define RCC_AHB2RSTR_DCMIRST_Pos                         ( 23U )
#define RCC_AHB2RSTR_DCMIRST_Msk                         ( 0x1UL << RCC_AHB2RSTR_DCMIRST_Pos )
#define RCC_AHB2RSTR_DCMIRST                             ( RCC_AHB2RSTR_DCMIRST_Msk )

#define RCC_AHB2RSTR_DAC2RST_Pos                         ( 20U )
#define RCC_AHB2RSTR_DAC2RST_Msk                         ( 0x1UL << RCC_AHB2RSTR_DAC2RST_Pos )
#define RCC_AHB2RSTR_DAC2RST                             ( RCC_AHB2RSTR_DAC2RST_Msk )

#define RCC_AHB2RSTR_DAC1RST_Pos                         ( 19U )
#define RCC_AHB2RSTR_DAC1RST_Msk                         ( 0x1UL << RCC_AHB2RSTR_DAC1RST_Pos )
#define RCC_AHB2RSTR_DAC1RST                             ( RCC_AHB2RSTR_DAC1RST_Msk )

#define RCC_AHB2RSTR_ADC3RST_Pos                         ( 18U )
#define RCC_AHB2RSTR_ADC3RST_Msk                         ( 0x1UL << RCC_AHB2RSTR_ADC3RST_Pos )
#define RCC_AHB2RSTR_ADC3RST                             ( RCC_AHB2RSTR_ADC3RST_Msk )

#define RCC_AHB2RSTR_ADC12RST_Pos                        ( 17U )
#define RCC_AHB2RSTR_ADC12RST_Msk                        ( 0x1UL << RCC_AHB2RSTR_ADC12RST_Pos )
#define RCC_AHB2RSTR_ADC12RST                            ( RCC_AHB2RSTR_ADC12RST_Msk )

#define RCC_AHB2RSTR_GPIOQRST_Pos                        ( 16U )
#define RCC_AHB2RSTR_GPIOQRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOQRST_Pos )
#define RCC_AHB2RSTR_GPIOQRST                            ( RCC_AHB2RSTR_GPIOQRST_Msk )

#define RCC_AHB2RSTR_GPIOPRST_Pos                        ( 15U )
#define RCC_AHB2RSTR_GPIOPRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOPRST_Pos )
#define RCC_AHB2RSTR_GPIOPRST                            ( RCC_AHB2RSTR_GPIOPRST_Msk )

#define RCC_AHB2RSTR_GPIOORST_Pos                        ( 14U )
#define RCC_AHB2RSTR_GPIOORST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOORST_Pos )
#define RCC_AHB2RSTR_GPIOORST                            ( RCC_AHB2RSTR_GPIOORST_Msk )

#define RCC_AHB2RSTR_GPIONRST_Pos                        ( 13U )
#define RCC_AHB2RSTR_GPIONRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIONRST_Pos )
#define RCC_AHB2RSTR_GPIONRST                            ( RCC_AHB2RSTR_GPIONRST_Msk )

#define RCC_AHB2RSTR_GPIOMRST_Pos                        ( 12U )
#define RCC_AHB2RSTR_GPIOMRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOMRST_Pos )
#define RCC_AHB2RSTR_GPIOMRST                            ( RCC_AHB2RSTR_GPIOMRST_Msk )

#define RCC_AHB2RSTR_GPIOLRST_Pos                        ( 11U )
#define RCC_AHB2RSTR_GPIOLRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOLRST_Pos )
#define RCC_AHB2RSTR_GPIOLRST                            ( RCC_AHB2RSTR_GPIOLRST_Msk )

#define RCC_AHB2RSTR_GPIOKRST_Pos                        ( 10U )
#define RCC_AHB2RSTR_GPIOKRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOKRST_Pos )
#define RCC_AHB2RSTR_GPIOKRST                            ( RCC_AHB2RSTR_GPIOKRST_Msk )

#define RCC_AHB2RSTR_GPIOJRST_Pos                        ( 9U )
#define RCC_AHB2RSTR_GPIOJRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOJRST_Pos )
#define RCC_AHB2RSTR_GPIOJRST                            ( RCC_AHB2RSTR_GPIOJRST_Msk )

#define RCC_AHB2RSTR_GPIOIRST_Pos                        ( 8U )
#define RCC_AHB2RSTR_GPIOIRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOIRST_Pos )
#define RCC_AHB2RSTR_GPIOIRST                            ( RCC_AHB2RSTR_GPIOIRST_Msk )

#define RCC_AHB2RSTR_GPIOHRST_Pos                        ( 7U )
#define RCC_AHB2RSTR_GPIOHRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOHRST_Pos )
#define RCC_AHB2RSTR_GPIOHRST                            ( RCC_AHB2RSTR_GPIOHRST_Msk )

#define RCC_AHB2RSTR_GPIOGRST_Pos                        ( 6U )
#define RCC_AHB2RSTR_GPIOGRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOGRST_Pos )
#define RCC_AHB2RSTR_GPIOGRST                            ( RCC_AHB2RSTR_GPIOGRST_Msk )

#define RCC_AHB2RSTR_GPIOFRST_Pos                        ( 5U )
#define RCC_AHB2RSTR_GPIOFRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOFRST_Pos )
#define RCC_AHB2RSTR_GPIOFRST                            ( RCC_AHB2RSTR_GPIOFRST_Msk )

#define RCC_AHB2RSTR_GPIOERST_Pos                        ( 4U )
#define RCC_AHB2RSTR_GPIOERST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOERST_Pos )
#define RCC_AHB2RSTR_GPIOERST                            ( RCC_AHB2RSTR_GPIOERST_Msk )

#define RCC_AHB2RSTR_GPIODRST_Pos                        ( 3U )
#define RCC_AHB2RSTR_GPIODRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIODRST_Pos )
#define RCC_AHB2RSTR_GPIODRST                            ( RCC_AHB2RSTR_GPIODRST_Msk )

#define RCC_AHB2RSTR_GPIOCRST_Pos                        ( 2U )
#define RCC_AHB2RSTR_GPIOCRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOCRST_Pos )
#define RCC_AHB2RSTR_GPIOCRST                            ( RCC_AHB2RSTR_GPIOCRST_Msk )

#define RCC_AHB2RSTR_GPIOBRST_Pos                        ( 1U )
#define RCC_AHB2RSTR_GPIOBRST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOBRST_Pos )
#define RCC_AHB2RSTR_GPIOBRST                            ( RCC_AHB2RSTR_GPIOBRST_Msk )

#define RCC_AHB2RSTR_GPIOARST_Pos                        ( 0U )
#define RCC_AHB2RSTR_GPIOARST_Msk                        ( 0x1UL << RCC_AHB2RSTR_GPIOARST_Pos )
#define RCC_AHB2RSTR_GPIOARST                            ( RCC_AHB2RSTR_GPIOARST_Msk )


/***************  Bits definition for RCC_AHB3RSTR  **********************/

#define RCC_AHB3RSTR_FMCRST_Pos                          ( 12U )
#define RCC_AHB3RSTR_FMCRST_Msk                          ( 0x1UL << RCC_AHB3RSTR_FMCRST_Pos )
#define RCC_AHB3RSTR_FMCRST                              ( RCC_AHB3RSTR_FMCRST_Msk )

#define RCC_AHB3RSTR_OSPI2RST_Pos                        ( 9U )
#define RCC_AHB3RSTR_OSPI2RST_Msk                        ( 0x1UL << RCC_AHB3RSTR_OSPI2RST_Pos )
#define RCC_AHB3RSTR_OSPI2RST                            ( RCC_AHB3RSTR_OSPI2RST_Msk )

#define RCC_AHB3RSTR_OSPI1RST_Pos                        ( 8U )
#define RCC_AHB3RSTR_OSPI1RST_Msk                        ( 0x1UL << RCC_AHB3RSTR_OSPI1RST_Pos )
#define RCC_AHB3RSTR_OSPI1RST                            ( RCC_AHB3RSTR_OSPI1RST_Msk )

#define RCC_AHB3RSTR_SDMMCRST_Pos                        ( 4U )
#define RCC_AHB3RSTR_SDMMCRST_Msk                        ( 0x1UL << RCC_AHB3RSTR_SDMMCRST_Pos )
#define RCC_AHB3RSTR_SDMMCRST                            ( RCC_AHB3RSTR_SDMMCRST_Msk )

#define RCC_AHB3RSTR_SPI8RST_Pos                         ( 1U )
#define RCC_AHB3RSTR_SPI8RST_Msk                         ( 0x1UL << RCC_AHB3RSTR_SPI8RST_Pos )
#define RCC_AHB3RSTR_SPI8RST                             ( RCC_AHB3RSTR_SPI8RST_Msk )

#define RCC_AHB3RSTR_SPI7RST_Pos                         ( 0U )
#define RCC_AHB3RSTR_SPI7RST_Msk                         ( 0x1UL << RCC_AHB3RSTR_SPI7RST_Pos )
#define RCC_AHB3RSTR_SPI7RST                             ( RCC_AHB3RSTR_SPI7RST_Msk )


/***************  Bits definition for RCC_APB1RSTR1  **********************/

#define RCC_APB1RSTR1_LPUART1RST_Pos                     ( 31U )
#define RCC_APB1RSTR1_LPUART1RST_Msk                     ( 0x1UL << RCC_APB1RSTR1_LPUART1RST_Pos )
#define RCC_APB1RSTR1_LPUART1RST                         ( RCC_APB1RSTR1_LPUART1RST_Msk )

#define RCC_APB1RSTR1_LPTIM1RST_Pos                      ( 30U )
#define RCC_APB1RSTR1_LPTIM1RST_Msk                      ( 0x1UL << RCC_APB1RSTR1_LPTIM1RST_Pos )
#define RCC_APB1RSTR1_LPTIM1RST                          ( RCC_APB1RSTR1_LPTIM1RST_Msk )

#define RCC_APB1RSTR1_PMURST_Pos                         ( 27U )
#define RCC_APB1RSTR1_PMURST_Msk                         ( 0x1UL << RCC_APB1RSTR1_PMURST_Pos )
#define RCC_APB1RSTR1_PMURST                             ( RCC_APB1RSTR1_PMURST_Msk )

#define RCC_APB1RSTR1_I2C4RST_Pos                        ( 24U )
#define RCC_APB1RSTR1_I2C4RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_I2C4RST_Pos )
#define RCC_APB1RSTR1_I2C4RST                            ( RCC_APB1RSTR1_I2C4RST_Msk )

#define RCC_APB1RSTR1_I2C3RST_Pos                        ( 23U )
#define RCC_APB1RSTR1_I2C3RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_I2C3RST_Pos )
#define RCC_APB1RSTR1_I2C3RST                            ( RCC_APB1RSTR1_I2C3RST_Msk )

#define RCC_APB1RSTR1_I2C2RST_Pos                        ( 22U )
#define RCC_APB1RSTR1_I2C2RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_I2C2RST_Pos )
#define RCC_APB1RSTR1_I2C2RST                            ( RCC_APB1RSTR1_I2C2RST_Msk )

#define RCC_APB1RSTR1_I2C1RST_Pos                        ( 21U )
#define RCC_APB1RSTR1_I2C1RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_I2C1RST_Pos )
#define RCC_APB1RSTR1_I2C1RST                            ( RCC_APB1RSTR1_I2C1RST_Msk )

#define RCC_APB1RSTR1_USART5RST_Pos                       ( 20U )
#define RCC_APB1RSTR1_USART5RST_Msk                       ( 0x1UL << RCC_APB1RSTR1_USART5RST_Pos )
#define RCC_APB1RSTR1_USART5RST                           ( RCC_APB1RSTR1_USART5RST_Msk )

#define RCC_APB1RSTR1_USART4RST_Pos                       ( 19U )
#define RCC_APB1RSTR1_USART4RST_Msk                       ( 0x1UL << RCC_APB1RSTR1_USART4RST_Pos )
#define RCC_APB1RSTR1_USART4RST                           ( RCC_APB1RSTR1_USART4RST_Msk )

#define RCC_APB1RSTR1_USART3RST_Pos                       ( 18U )
#define RCC_APB1RSTR1_USART3RST_Msk                       ( 0x1UL << RCC_APB1RSTR1_USART3RST_Pos )
#define RCC_APB1RSTR1_USART3RST                           ( RCC_APB1RSTR1_USART3RST_Msk )

#define RCC_APB1RSTR1_USART2RST_Pos                       ( 17U )
#define RCC_APB1RSTR1_USART2RST_Msk                       ( 0x1UL << RCC_APB1RSTR1_USART2RST_Pos )
#define RCC_APB1RSTR1_USART2RST                           ( RCC_APB1RSTR1_USART2RST_Msk )

#define RCC_APB1RSTR1_I2S3RST_Pos                        ( 16U )
#define RCC_APB1RSTR1_I2S3RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_I2S3RST_Pos )
#define RCC_APB1RSTR1_I2S3RST                            ( RCC_APB1RSTR1_I2S3RST_Msk )

#define RCC_APB1RSTR1_I2S2RST_Pos                        ( 15U )
#define RCC_APB1RSTR1_I2S2RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_I2S2RST_Pos )
#define RCC_APB1RSTR1_I2S2RST                            ( RCC_APB1RSTR1_I2S2RST_Msk )

#define RCC_APB1RSTR1_I2S1RST_Pos                        ( 14U )
#define RCC_APB1RSTR1_I2S1RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_I2S1RST_Pos )
#define RCC_APB1RSTR1_I2S1RST                            ( RCC_APB1RSTR1_I2S1RST_Msk )

#define RCC_APB1RSTR1_WDTRST_Pos                         ( 11U )
#define RCC_APB1RSTR1_WDTRST_Msk                         ( 0x1UL << RCC_APB1RSTR1_WDTRST_Pos )
#define RCC_APB1RSTR1_WDTRST                             ( RCC_APB1RSTR1_WDTRST_Msk )

#define RCC_APB1RSTR1_TIM14RST_Pos                       ( 8U )
#define RCC_APB1RSTR1_TIM14RST_Msk                       ( 0x1UL << RCC_APB1RSTR1_TIM14RST_Pos )
#define RCC_APB1RSTR1_TIM14RST                           ( RCC_APB1RSTR1_TIM14RST_Msk )

#define RCC_APB1RSTR1_TIM13RST_Pos                       ( 7U )
#define RCC_APB1RSTR1_TIM13RST_Msk                       ( 0x1UL << RCC_APB1RSTR1_TIM13RST_Pos )
#define RCC_APB1RSTR1_TIM13RST                           ( RCC_APB1RSTR1_TIM13RST_Msk )

#define RCC_APB1RSTR1_TIM12RST_Pos                       ( 6U )
#define RCC_APB1RSTR1_TIM12RST_Msk                       ( 0x1UL << RCC_APB1RSTR1_TIM12RST_Pos )
#define RCC_APB1RSTR1_TIM12RST                           ( RCC_APB1RSTR1_TIM12RST_Msk )

#define RCC_APB1RSTR1_TIM7RST_Pos                        ( 5U )
#define RCC_APB1RSTR1_TIM7RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_TIM7RST_Pos )
#define RCC_APB1RSTR1_TIM7RST                            ( RCC_APB1RSTR1_TIM7RST_Msk )

#define RCC_APB1RSTR1_TIM6RST_Pos                        ( 4U )
#define RCC_APB1RSTR1_TIM6RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_TIM6RST_Pos )
#define RCC_APB1RSTR1_TIM6RST                            ( RCC_APB1RSTR1_TIM6RST_Msk )

#define RCC_APB1RSTR1_TIM5RST_Pos                        ( 3U )
#define RCC_APB1RSTR1_TIM5RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_TIM5RST_Pos )
#define RCC_APB1RSTR1_TIM5RST                            ( RCC_APB1RSTR1_TIM5RST_Msk )

#define RCC_APB1RSTR1_TIM4RST_Pos                        ( 2U )
#define RCC_APB1RSTR1_TIM4RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_TIM4RST_Pos )
#define RCC_APB1RSTR1_TIM4RST                            ( RCC_APB1RSTR1_TIM4RST_Msk )

#define RCC_APB1RSTR1_TIM3RST_Pos                        ( 1U )
#define RCC_APB1RSTR1_TIM3RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_TIM3RST_Pos )
#define RCC_APB1RSTR1_TIM3RST                            ( RCC_APB1RSTR1_TIM3RST_Msk )

#define RCC_APB1RSTR1_TIM2RST_Pos                        ( 0U )
#define RCC_APB1RSTR1_TIM2RST_Msk                        ( 0x1UL << RCC_APB1RSTR1_TIM2RST_Pos )
#define RCC_APB1RSTR1_TIM2RST                            ( RCC_APB1RSTR1_TIM2RST_Msk )


/***************  Bits definition for RCC_APB1RSTR2  **********************/

#define RCC_APB1RSTR2_EFUSE2RST_Pos                      ( 7U )
#define RCC_APB1RSTR2_EFUSE2RST_Msk                      ( 0x1UL << RCC_APB1RSTR2_EFUSE2RST_Pos )
#define RCC_APB1RSTR2_EFUSE2RST                          ( RCC_APB1RSTR2_EFUSE2RST_Msk )

#define RCC_APB1RSTR2_EFUSE1RST_Pos                      ( 6U )
#define RCC_APB1RSTR2_EFUSE1RST_Msk                      ( 0x1UL << RCC_APB1RSTR2_EFUSE1RST_Pos )
#define RCC_APB1RSTR2_EFUSE1RST                          ( RCC_APB1RSTR2_EFUSE1RST_Msk )

#define RCC_APB1RSTR2_TIM26RST_Pos                       ( 5U )
#define RCC_APB1RSTR2_TIM26RST_Msk                       ( 0x1UL << RCC_APB1RSTR2_TIM26RST_Pos )
#define RCC_APB1RSTR2_TIM26RST                           ( RCC_APB1RSTR2_TIM26RST_Msk )

#define RCC_APB1RSTR2_TIM25RST_Pos                       ( 4U )
#define RCC_APB1RSTR2_TIM25RST_Msk                       ( 0x1UL << RCC_APB1RSTR2_TIM25RST_Pos )
#define RCC_APB1RSTR2_TIM25RST                           ( RCC_APB1RSTR2_TIM25RST_Msk )

#define RCC_APB1RSTR2_USART8RST_Pos                       ( 3U )
#define RCC_APB1RSTR2_USART8RST_Msk                       ( 0x1UL << RCC_APB1RSTR2_USART8RST_Pos )
#define RCC_APB1RSTR2_USART8RST                           ( RCC_APB1RSTR2_USART8RST_Msk )

#define RCC_APB1RSTR2_USART7RST_Pos                       ( 2U )
#define RCC_APB1RSTR2_USART7RST_Msk                       ( 0x1UL << RCC_APB1RSTR2_USART7RST_Pos )
#define RCC_APB1RSTR2_USART7RST                           ( RCC_APB1RSTR2_USART7RST_Msk )

#define RCC_APB1RSTR2_LPTIM2RST_Pos                      ( 1U )
#define RCC_APB1RSTR2_LPTIM2RST_Msk                      ( 0x1UL << RCC_APB1RSTR2_LPTIM2RST_Pos )
#define RCC_APB1RSTR2_LPTIM2RST                          ( RCC_APB1RSTR2_LPTIM2RST_Msk )


/***************  Bits definition for RCC_APB2RSTR  **********************/

#define RCC_APB2RSTR_USART10RST_Pos                       ( 31U )
#define RCC_APB2RSTR_USART10RST_Msk                       ( 0x1UL << RCC_APB2RSTR_USART10RST_Pos )
#define RCC_APB2RSTR_USART10RST                           ( RCC_APB2RSTR_USART10RST_Msk )

#define RCC_APB2RSTR_USART9RST_Pos                        ( 30U )
#define RCC_APB2RSTR_USART9RST_Msk                        ( 0x1UL << RCC_APB2RSTR_USART9RST_Pos )
#define RCC_APB2RSTR_USART9RST                            ( RCC_APB2RSTR_USART9RST_Msk )

#define RCC_APB2RSTR_TIM24RST_Pos                        ( 29U )
#define RCC_APB2RSTR_TIM24RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM24RST_Pos )
#define RCC_APB2RSTR_TIM24RST                            ( RCC_APB2RSTR_TIM24RST_Msk )

#define RCC_APB2RSTR_TIM23RST_Pos                        ( 28U )
#define RCC_APB2RSTR_TIM23RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM23RST_Pos )
#define RCC_APB2RSTR_TIM23RST                            ( RCC_APB2RSTR_TIM23RST_Msk )

#define RCC_APB2RSTR_TIM22RST_Pos                        ( 27U )
#define RCC_APB2RSTR_TIM22RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM22RST_Pos )
#define RCC_APB2RSTR_TIM22RST                            ( RCC_APB2RSTR_TIM22RST_Msk )

#define RCC_APB2RSTR_TIM21RST_Pos                        ( 26U )
#define RCC_APB2RSTR_TIM21RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM21RST_Pos )
#define RCC_APB2RSTR_TIM21RST                            ( RCC_APB2RSTR_TIM21RST_Msk )

#define RCC_APB2RSTR_TIM19RST_Pos                        ( 25U )
#define RCC_APB2RSTR_TIM19RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM19RST_Pos )
#define RCC_APB2RSTR_TIM19RST                            ( RCC_APB2RSTR_TIM19RST_Msk )

#define RCC_APB2RSTR_TIM18RST_Pos                        ( 24U )
#define RCC_APB2RSTR_TIM18RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM18RST_Pos )
#define RCC_APB2RSTR_TIM18RST                            ( RCC_APB2RSTR_TIM18RST_Msk )

#define RCC_APB2RSTR_TIM11RST_Pos                        ( 23U )
#define RCC_APB2RSTR_TIM11RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM11RST_Pos )
#define RCC_APB2RSTR_TIM11RST                            ( RCC_APB2RSTR_TIM11RST_Msk )

#define RCC_APB2RSTR_TIM10RST_Pos                        ( 22U )
#define RCC_APB2RSTR_TIM10RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM10RST_Pos )
#define RCC_APB2RSTR_TIM10RST                            ( RCC_APB2RSTR_TIM10RST_Msk )

#define RCC_APB2RSTR_TIM9RST_Pos                         ( 21U )
#define RCC_APB2RSTR_TIM9RST_Msk                         ( 0x1UL << RCC_APB2RSTR_TIM9RST_Pos )
#define RCC_APB2RSTR_TIM9RST                             ( RCC_APB2RSTR_TIM9RST_Msk )

#define RCC_APB2RSTR_LTDCRST_Pos                         ( 19U )
#define RCC_APB2RSTR_LTDCRST_Msk                         ( 0x1UL << RCC_APB2RSTR_LTDCRST_Pos )
#define RCC_APB2RSTR_LTDCRST                             ( RCC_APB2RSTR_LTDCRST_Msk )

#define RCC_APB2RSTR_TKEYRST_Pos                         ( 18U )
#define RCC_APB2RSTR_TKEYRST_Msk                         ( 0x1UL << RCC_APB2RSTR_TKEYRST_Pos )
#define RCC_APB2RSTR_TKEYRST                             ( RCC_APB2RSTR_TKEYRST_Msk )

#define RCC_APB2RSTR_TIM20RST_Pos                        ( 15U )
#define RCC_APB2RSTR_TIM20RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM20RST_Pos )
#define RCC_APB2RSTR_TIM20RST                            ( RCC_APB2RSTR_TIM20RST_Msk )

#define RCC_APB2RSTR_TIM17RST_Pos                        ( 13U )
#define RCC_APB2RSTR_TIM17RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM17RST_Pos )
#define RCC_APB2RSTR_TIM17RST                            ( RCC_APB2RSTR_TIM17RST_Msk )

#define RCC_APB2RSTR_TIM16RST_Pos                        ( 12U )
#define RCC_APB2RSTR_TIM16RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM16RST_Pos )
#define RCC_APB2RSTR_TIM16RST                            ( RCC_APB2RSTR_TIM16RST_Msk )

#define RCC_APB2RSTR_TIM15RST_Pos                        ( 11U )
#define RCC_APB2RSTR_TIM15RST_Msk                        ( 0x1UL << RCC_APB2RSTR_TIM15RST_Pos )
#define RCC_APB2RSTR_TIM15RST                            ( RCC_APB2RSTR_TIM15RST_Msk )

#define RCC_APB2RSTR_USART6RST_Pos                       ( 10U )
#define RCC_APB2RSTR_USART6RST_Msk                       ( 0x1UL << RCC_APB2RSTR_USART6RST_Pos )
#define RCC_APB2RSTR_USART6RST                           ( RCC_APB2RSTR_USART6RST_Msk )

#define RCC_APB2RSTR_USART1RST_Pos                       ( 9U )
#define RCC_APB2RSTR_USART1RST_Msk                       ( 0x1UL << RCC_APB2RSTR_USART1RST_Pos )
#define RCC_APB2RSTR_USART1RST                           ( RCC_APB2RSTR_USART1RST_Msk )

#define RCC_APB2RSTR_TIM8RST_Pos                         ( 8U )
#define RCC_APB2RSTR_TIM8RST_Msk                         ( 0x1UL << RCC_APB2RSTR_TIM8RST_Pos )
#define RCC_APB2RSTR_TIM8RST                             ( RCC_APB2RSTR_TIM8RST_Msk )

#define RCC_APB2RSTR_TIM1RST_Pos                         ( 6U )
#define RCC_APB2RSTR_TIM1RST_Msk                         ( 0x1UL << RCC_APB2RSTR_TIM1RST_Pos )
#define RCC_APB2RSTR_TIM1RST                             ( RCC_APB2RSTR_TIM1RST_Msk )

#define RCC_APB2RSTR_EXTIRST_Pos                         ( 4U )
#define RCC_APB2RSTR_EXTIRST_Msk                         ( 0x1UL << RCC_APB2RSTR_EXTIRST_Pos )
#define RCC_APB2RSTR_EXTIRST                             ( RCC_APB2RSTR_EXTIRST_Msk )

#define RCC_APB2RSTR_CMP1RST_A_Pos                       ( 2U )
#define RCC_APB2RSTR_CMP1RST_A_Msk                       ( 0x1UL << RCC_APB2RSTR_CMP1RST_A_Pos )
#define RCC_APB2RSTR_CMP1RST_A                           ( RCC_APB2RSTR_CMP1RST_A_Msk )

#define RCC_APB2RSTR_SYSCFGRST_Pos                       ( 0U )
#define RCC_APB2RSTR_SYSCFGRST_Msk                       ( 0x1UL << RCC_APB2RSTR_SYSCFGRST_Pos )
#define RCC_APB2RSTR_SYSCFGRST                           ( RCC_APB2RSTR_SYSCFGRST_Msk )


/***************  Bits definition for RCC_APB3RSTR  **********************/

#define RCC_APB3RSTR_LPTIM6RST_Pos                       ( 3U )
#define RCC_APB3RSTR_LPTIM6RST_Msk                       ( 0x1UL << RCC_APB3RSTR_LPTIM6RST_Pos )
#define RCC_APB3RSTR_LPTIM6RST                           ( RCC_APB3RSTR_LPTIM6RST_Msk )

#define RCC_APB3RSTR_LPTIM5RST_Pos                       ( 2U )
#define RCC_APB3RSTR_LPTIM5RST_Msk                       ( 0x1UL << RCC_APB3RSTR_LPTIM5RST_Pos )
#define RCC_APB3RSTR_LPTIM5RST                           ( RCC_APB3RSTR_LPTIM5RST_Msk )

#define RCC_APB3RSTR_LPTIM4RST_Pos                       ( 1U )
#define RCC_APB3RSTR_LPTIM4RST_Msk                       ( 0x1UL << RCC_APB3RSTR_LPTIM4RST_Pos )
#define RCC_APB3RSTR_LPTIM4RST                           ( RCC_APB3RSTR_LPTIM4RST_Msk )

#define RCC_APB3RSTR_LPTIM3RST_Pos                       ( 0U )
#define RCC_APB3RSTR_LPTIM3RST_Msk                       ( 0x1UL << RCC_APB3RSTR_LPTIM3RST_Pos )
#define RCC_APB3RSTR_LPTIM3RST                           ( RCC_APB3RSTR_LPTIM3RST_Msk )


/***************  Bits definition for RCC_APB4RSTR  **********************/

#define RCC_APB4RSTR_DPWM6RST_Pos                        ( 17U )
#define RCC_APB4RSTR_DPWM6RST_Msk                        ( 0x1UL << RCC_APB4RSTR_DPWM6RST_Pos )
#define RCC_APB4RSTR_DPWM6RST                            ( RCC_APB4RSTR_DPWM6RST_Msk )

#define RCC_APB4RSTR_DPWM5RST_Pos                        ( 16U )
#define RCC_APB4RSTR_DPWM5RST_Msk                        ( 0x1UL << RCC_APB4RSTR_DPWM5RST_Pos )
#define RCC_APB4RSTR_DPWM5RST                            ( RCC_APB4RSTR_DPWM5RST_Msk )

#define RCC_APB4RSTR_SPWM6RST_Pos                        ( 15U )
#define RCC_APB4RSTR_SPWM6RST_Msk                        ( 0x1UL << RCC_APB4RSTR_SPWM6RST_Pos )
#define RCC_APB4RSTR_SPWM6RST                            ( RCC_APB4RSTR_SPWM6RST_Msk )

#define RCC_APB4RSTR_SPWM5RST_Pos                        ( 14U )
#define RCC_APB4RSTR_SPWM5RST_Msk                        ( 0x1UL << RCC_APB4RSTR_SPWM5RST_Pos )
#define RCC_APB4RSTR_SPWM5RST                            ( RCC_APB4RSTR_SPWM5RST_Msk )

#define RCC_APB4RSTR_SPWM4RST_Pos                        ( 13U )
#define RCC_APB4RSTR_SPWM4RST_Msk                        ( 0x1UL << RCC_APB4RSTR_SPWM4RST_Pos )
#define RCC_APB4RSTR_SPWM4RST                            ( RCC_APB4RSTR_SPWM4RST_Msk )

#define RCC_APB4RSTR_SPWM3RST_Pos                        ( 12U )
#define RCC_APB4RSTR_SPWM3RST_Msk                        ( 0x1UL << RCC_APB4RSTR_SPWM3RST_Pos )
#define RCC_APB4RSTR_SPWM3RST                            ( RCC_APB4RSTR_SPWM3RST_Msk )

#define RCC_APB4RSTR_MDACRST_Pos                         ( 8U )
#define RCC_APB4RSTR_MDACRST_Msk                         ( 0x1UL << RCC_APB4RSTR_MDACRST_Pos )
#define RCC_APB4RSTR_MDACRST                             ( RCC_APB4RSTR_MDACRST_Msk )

#define RCC_APB4RSTR_LPTRST_Pos                          ( 7U )
#define RCC_APB4RSTR_LPTRST_Msk                          ( 0x1UL << RCC_APB4RSTR_LPTRST_Pos )
#define RCC_APB4RSTR_LPTRST                              ( RCC_APB4RSTR_LPTRST_Msk )

#define RCC_APB4RSTR_PNDLRST_Pos                         ( 6U )
#define RCC_APB4RSTR_PNDLRST_Msk                         ( 0x1UL << RCC_APB4RSTR_PNDLRST_Pos )
#define RCC_APB4RSTR_PNDLRST                             ( RCC_APB4RSTR_PNDLRST_Msk )

#define RCC_APB4RSTR_DPWM4RST_Pos                        ( 5U )
#define RCC_APB4RSTR_DPWM4RST_Msk                        ( 0x1UL << RCC_APB4RSTR_DPWM4RST_Pos )
#define RCC_APB4RSTR_DPWM4RST                            ( RCC_APB4RSTR_DPWM4RST_Msk )

#define RCC_APB4RSTR_DPWM3RST_Pos                        ( 4U )
#define RCC_APB4RSTR_DPWM3RST_Msk                        ( 0x1UL << RCC_APB4RSTR_DPWM3RST_Pos )
#define RCC_APB4RSTR_DPWM3RST                            ( RCC_APB4RSTR_DPWM3RST_Msk )

#define RCC_APB4RSTR_DPWM2RST_Pos                        ( 3U )
#define RCC_APB4RSTR_DPWM2RST_Msk                        ( 0x1UL << RCC_APB4RSTR_DPWM2RST_Pos )
#define RCC_APB4RSTR_DPWM2RST                            ( RCC_APB4RSTR_DPWM2RST_Msk )

#define RCC_APB4RSTR_DPWM1RST_Pos                        ( 2U )
#define RCC_APB4RSTR_DPWM1RST_Msk                        ( 0x1UL << RCC_APB4RSTR_DPWM1RST_Pos )
#define RCC_APB4RSTR_DPWM1RST                            ( RCC_APB4RSTR_DPWM1RST_Msk )

#define RCC_APB4RSTR_SPWM2RST_Pos                        ( 1U )
#define RCC_APB4RSTR_SPWM2RST_Msk                        ( 0x1UL << RCC_APB4RSTR_SPWM2RST_Pos )
#define RCC_APB4RSTR_SPWM2RST                            ( RCC_APB4RSTR_SPWM2RST_Msk )

#define RCC_APB4RSTR_SPWM1RST_Pos                        ( 0U )
#define RCC_APB4RSTR_SPWM1RST_Msk                        ( 0x1UL << RCC_APB4RSTR_SPWM1RST_Pos )
#define RCC_APB4RSTR_SPWM1RST                            ( RCC_APB4RSTR_SPWM1RST_Msk )


/***************  Bits definition for RCC_CCR1  **********************/

#define RCC_CCR1_SYSCLKSEL_Pos                              ( 0U )
#define RCC_CCR1_SYSCLKSEL_Msk                              ( 0x3UL << RCC_CCR1_SYSCLKSEL_Pos )
#define RCC_CCR1_SYSCLKSEL                                  ( RCC_CCR1_SYSCLKSEL_Msk )
#define RCC_CCR1_SYSCLKSEL_0                                ( 0x1UL << RCC_CCR1_SYSCLKSEL_Pos )
#define RCC_CCR1_SYSCLKSEL_1                                ( 0x2UL << RCC_CCR1_SYSCLKSEL_Pos )


/***************  Bits definition for RCC_CCR2  **********************/

#define RCC_CCR2_DIVDONE_Pos                                ( 31U )
#define RCC_CCR2_DIVDONE_Msk                                ( 0x1UL << RCC_CCR2_DIVDONE_Pos )
#define RCC_CCR2_DIVDONE                                    ( RCC_CCR2_DIVDONE_Msk )

#define RCC_CCR2_HRNGSDIV_Pos                               ( 24U )
#define RCC_CCR2_HRNGSDIV_Msk                               ( 0x7FUL << RCC_CCR2_HRNGSDIV_Pos )
#define RCC_CCR2_HRNGSDIV                                   ( RCC_CCR2_HRNGSDIV_Msk )
#define RCC_CCR2_HRNGSDIV_0                                 ( 0x01UL << RCC_CCR2_HRNGSDIV_Pos )
#define RCC_CCR2_HRNGSDIV_1                                 ( 0x02UL << RCC_CCR2_HRNGSDIV_Pos )
#define RCC_CCR2_HRNGSDIV_2                                 ( 0x04UL << RCC_CCR2_HRNGSDIV_Pos )
#define RCC_CCR2_HRNGSDIV_3                                 ( 0x08UL << RCC_CCR2_HRNGSDIV_Pos )
#define RCC_CCR2_HRNGSDIV_4                                 ( 0x10UL << RCC_CCR2_HRNGSDIV_Pos )
#define RCC_CCR2_HRNGSDIV_5                                 ( 0x20UL << RCC_CCR2_HRNGSDIV_Pos )
#define RCC_CCR2_HRNGSDIV_6                                 ( 0x40UL << RCC_CCR2_HRNGSDIV_Pos )

#define RCC_CCR2_FLTCLKSEL_Pos                              ( 20U )
#define RCC_CCR2_FLTCLKSEL_Msk                              ( 0x1UL << RCC_CCR2_FLTCLKSEL_Pos )
#define RCC_CCR2_FLTCLKSEL                                  ( RCC_CCR2_FLTCLKSEL_Msk )

#define RCC_CCR2_PCLK4DIV_Pos                               ( 17U )
#define RCC_CCR2_PCLK4DIV_Msk                               ( 0x7UL << RCC_CCR2_PCLK4DIV_Pos )
#define RCC_CCR2_PCLK4DIV                                   ( RCC_CCR2_PCLK4DIV_Msk )
#define RCC_CCR2_PCLK4DIV_0                                 ( 0x1UL << RCC_CCR2_PCLK4DIV_Pos )
#define RCC_CCR2_PCLK4DIV_1                                 ( 0x2UL << RCC_CCR2_PCLK4DIV_Pos )
#define RCC_CCR2_PCLK4DIV_2                                 ( 0x4UL << RCC_CCR2_PCLK4DIV_Pos )

#define RCC_CCR2_PCLK3DIV_Pos                               ( 14U )
#define RCC_CCR2_PCLK3DIV_Msk                               ( 0x7UL << RCC_CCR2_PCLK3DIV_Pos )
#define RCC_CCR2_PCLK3DIV                                   ( RCC_CCR2_PCLK3DIV_Msk )
#define RCC_CCR2_PCLK3DIV_0                                 ( 0x1UL << RCC_CCR2_PCLK3DIV_Pos )
#define RCC_CCR2_PCLK3DIV_1                                 ( 0x2UL << RCC_CCR2_PCLK3DIV_Pos )
#define RCC_CCR2_PCLK3DIV_2                                 ( 0x4UL << RCC_CCR2_PCLK3DIV_Pos )

#define RCC_CCR2_PCLK2DIV_Pos                               ( 11U )
#define RCC_CCR2_PCLK2DIV_Msk                               ( 0x7UL << RCC_CCR2_PCLK2DIV_Pos )
#define RCC_CCR2_PCLK2DIV                                   ( RCC_CCR2_PCLK2DIV_Msk )
#define RCC_CCR2_PCLK2DIV_0                                 ( 0x1UL << RCC_CCR2_PCLK2DIV_Pos )
#define RCC_CCR2_PCLK2DIV_1                                 ( 0x2UL << RCC_CCR2_PCLK2DIV_Pos )
#define RCC_CCR2_PCLK2DIV_2                                 ( 0x4UL << RCC_CCR2_PCLK2DIV_Pos )

#define RCC_CCR2_PCLK1DIV_Pos                               ( 8U )
#define RCC_CCR2_PCLK1DIV_Msk                               ( 0x7UL << RCC_CCR2_PCLK1DIV_Pos )
#define RCC_CCR2_PCLK1DIV                                   ( RCC_CCR2_PCLK1DIV_Msk )
#define RCC_CCR2_PCLK1DIV_0                                 ( 0x1UL << RCC_CCR2_PCLK1DIV_Pos )
#define RCC_CCR2_PCLK1DIV_1                                 ( 0x2UL << RCC_CCR2_PCLK1DIV_Pos )
#define RCC_CCR2_PCLK1DIV_2                                 ( 0x4UL << RCC_CCR2_PCLK1DIV_Pos )

#define RCC_CCR2_SYSDIV1_Pos                                ( 4U )
#define RCC_CCR2_SYSDIV1_Msk                                ( 0xFUL << RCC_CCR2_SYSDIV1_Pos )
#define RCC_CCR2_SYSDIV1                                    ( RCC_CCR2_SYSDIV1_Msk )
#define RCC_CCR2_SYSDIV1_0                                  ( 0x1UL << RCC_CCR2_SYSDIV1_Pos )
#define RCC_CCR2_SYSDIV1_1                                  ( 0x2UL << RCC_CCR2_SYSDIV1_Pos )
#define RCC_CCR2_SYSDIV1_2                                  ( 0x4UL << RCC_CCR2_SYSDIV1_Pos )
#define RCC_CCR2_SYSDIV1_3                                  ( 0x8UL << RCC_CCR2_SYSDIV1_Pos )

#define RCC_CCR2_SYSDIV0_Pos                                ( 0U )
#define RCC_CCR2_SYSDIV0_Msk                                ( 0xFUL << RCC_CCR2_SYSDIV0_Pos )
#define RCC_CCR2_SYSDIV0                                    ( RCC_CCR2_SYSDIV0_Msk )
#define RCC_CCR2_SYSDIV0_0                                  ( 0x1UL << RCC_CCR2_SYSDIV0_Pos )
#define RCC_CCR2_SYSDIV0_1                                  ( 0x2UL << RCC_CCR2_SYSDIV0_Pos )
#define RCC_CCR2_SYSDIV0_2                                  ( 0x4UL << RCC_CCR2_SYSDIV0_Pos )
#define RCC_CCR2_SYSDIV0_3                                  ( 0x8UL << RCC_CCR2_SYSDIV0_Pos )


/***************  Bits definition for RCC_PERCFGR  **********************/

#define RCC_PERCFGR_LPUART1CKS_Pos                         ( 26U )
#define RCC_PERCFGR_LPUART1CKS_Msk                         ( 0x3UL << RCC_PERCFGR_LPUART1CKS_Pos )
#define RCC_PERCFGR_LPUART1CKS                             ( RCC_PERCFGR_LPUART1CKS_Msk )
#define RCC_PERCFGR_LPUART1CKS_0                           ( 0x1UL << RCC_PERCFGR_LPUART1CKS_Pos )
#define RCC_PERCFGR_LPUART1CKS_1                           ( 0x2UL << RCC_PERCFGR_LPUART1CKS_Pos )

#define RCC_PERCFGR_LPUART1DIV_Pos                         ( 24U )
#define RCC_PERCFGR_LPUART1DIV_Msk                         ( 0x3UL << RCC_PERCFGR_LPUART1DIV_Pos )
#define RCC_PERCFGR_LPUART1DIV                             ( RCC_PERCFGR_LPUART1DIV_Msk )
#define RCC_PERCFGR_LPUART1DIV_0                           ( 0x1UL << RCC_PERCFGR_LPUART1DIV_Pos )
#define RCC_PERCFGR_LPUART1DIV_1                           ( 0x2UL << RCC_PERCFGR_LPUART1DIV_Pos )

#define RCC_PERCFGR_LPTIM6CKS_Pos                          ( 22U )
#define RCC_PERCFGR_LPTIM6CKS_Msk                          ( 0x3UL << RCC_PERCFGR_LPTIM6CKS_Pos )
#define RCC_PERCFGR_LPTIM6CKS                              ( RCC_PERCFGR_LPTIM6CKS_Msk )
#define RCC_PERCFGR_LPTIM6CKS_0                            ( 0x1UL << RCC_PERCFGR_LPTIM6CKS_Pos )
#define RCC_PERCFGR_LPTIM6CKS_1                            ( 0x2UL << RCC_PERCFGR_LPTIM6CKS_Pos )

#define RCC_PERCFGR_LPTIM345CKS_Pos                        ( 20U )
#define RCC_PERCFGR_LPTIM345CKS_Msk                        ( 0x3UL << RCC_PERCFGR_LPTIM345CKS_Pos )
#define RCC_PERCFGR_LPTIM345CKS                            ( RCC_PERCFGR_LPTIM345CKS_Msk )
#define RCC_PERCFGR_LPTIM345CKS_0                          ( 0x1UL << RCC_PERCFGR_LPTIM345CKS_Pos )
#define RCC_PERCFGR_LPTIM345CKS_1                          ( 0x2UL << RCC_PERCFGR_LPTIM345CKS_Pos )

#define RCC_PERCFGR_LPTIM2CKS_Pos                          ( 18U )
#define RCC_PERCFGR_LPTIM2CKS_Msk                          ( 0x3UL << RCC_PERCFGR_LPTIM2CKS_Pos )
#define RCC_PERCFGR_LPTIM2CKS                              ( RCC_PERCFGR_LPTIM2CKS_Msk )
#define RCC_PERCFGR_LPTIM2CKS_0                            ( 0x1UL << RCC_PERCFGR_LPTIM2CKS_Pos )
#define RCC_PERCFGR_LPTIM2CKS_1                            ( 0x2UL << RCC_PERCFGR_LPTIM2CKS_Pos )

#define RCC_PERCFGR_LPTIM1CKS_Pos                          ( 16U )
#define RCC_PERCFGR_LPTIM1CKS_Msk                          ( 0x3UL << RCC_PERCFGR_LPTIM1CKS_Pos )
#define RCC_PERCFGR_LPTIM1CKS                              ( RCC_PERCFGR_LPTIM1CKS_Msk )
#define RCC_PERCFGR_LPTIM1CKS_0                            ( 0x1UL << RCC_PERCFGR_LPTIM1CKS_Pos )
#define RCC_PERCFGR_LPTIM1CKS_1                            ( 0x2UL << RCC_PERCFGR_LPTIM1CKS_Pos )

#define RCC_PERCFGR_SDMMCCKS_Pos                           ( 11U )
#define RCC_PERCFGR_SDMMCCKS_Msk                           ( 0x1UL << RCC_PERCFGR_SDMMCCKS_Pos )
#define RCC_PERCFGR_SDMMCCKS                               ( RCC_PERCFGR_SDMMCCKS_Msk )

#define RCC_PERCFGR_SDMMCSCKS_Pos                          ( 8U )
#define RCC_PERCFGR_SDMMCSCKS_Msk                          ( 0x3UL << RCC_PERCFGR_SDMMCSCKS_Pos )
#define RCC_PERCFGR_SDMMCSCKS                              ( RCC_PERCFGR_SDMMCSCKS_Msk )
#define RCC_PERCFGR_SDMMCSCKS_0                            ( 0x1UL << RCC_PERCFGR_SDMMCSCKS_Pos )
#define RCC_PERCFGR_SDMMCSCKS_1                            ( 0x2UL << RCC_PERCFGR_SDMMCSCKS_Pos )

/***************  Bits definition for RCC_CIR  **********************/

#define RCC_CIR_XTLSDF_Pos                                  ( 31U )
#define RCC_CIR_XTLSDF_Msk                                  ( 0x1UL << RCC_CIR_XTLSDF_Pos )
#define RCC_CIR_XTLSDF                                      ( RCC_CIR_XTLSDF_Msk )

#define RCC_CIR_XTLSDIC_Pos                                 ( 29U )
#define RCC_CIR_XTLSDIC_Msk                                 ( 0x1UL << RCC_CIR_XTLSDIC_Pos )
#define RCC_CIR_XTLSDIC                                     ( RCC_CIR_XTLSDIC_Msk )

#define RCC_CIR_XTLSDIE_Pos                                 ( 28U )
#define RCC_CIR_XTLSDIE_Msk                                 ( 0x1UL << RCC_CIR_XTLSDIE_Pos )
#define RCC_CIR_XTLSDIE                                     ( RCC_CIR_XTLSDIE_Msk )

#define RCC_CIR_XTHSDF_Pos                                  ( 27U )
#define RCC_CIR_XTHSDF_Msk                                  ( 0x1UL << RCC_CIR_XTHSDF_Pos )
#define RCC_CIR_XTHSDF                                      ( RCC_CIR_XTHSDF_Msk )

#define RCC_CIR_XTHSDIC_Pos                                 ( 25U )
#define RCC_CIR_XTHSDIC_Msk                                 ( 0x1UL << RCC_CIR_XTHSDIC_Pos )
#define RCC_CIR_XTHSDIC                                     ( RCC_CIR_XTHSDIC_Msk )

#define RCC_CIR_XTHSDIE_Pos                                 ( 24U )
#define RCC_CIR_XTHSDIE_Msk                                 ( 0x1UL << RCC_CIR_XTHSDIE_Pos )
#define RCC_CIR_XTHSDIE                                     ( RCC_CIR_XTHSDIE_Msk )

#define RCC_CIR_PLL3LOCKIC_Pos                              ( 22U )
#define RCC_CIR_PLL3LOCKIC_Msk                              ( 0x1UL << RCC_CIR_PLL3LOCKIC_Pos )
#define RCC_CIR_PLL3LOCKIC                                  ( RCC_CIR_PLL3LOCKIC_Msk )

#define RCC_CIR_PLL2LOCKIC_Pos                              ( 21U )
#define RCC_CIR_PLL2LOCKIC_Msk                              ( 0x1UL << RCC_CIR_PLL2LOCKIC_Pos )
#define RCC_CIR_PLL2LOCKIC                                  ( RCC_CIR_PLL2LOCKIC_Msk )

#define RCC_CIR_PLL1LOCKIC_Pos                              ( 20U )
#define RCC_CIR_PLL1LOCKIC_Msk                              ( 0x1UL << RCC_CIR_PLL1LOCKIC_Pos )
#define RCC_CIR_PLL1LOCKIC                                  ( RCC_CIR_PLL1LOCKIC_Msk )

#define RCC_CIR_XTHRDYIC_Pos                                ( 19U )
#define RCC_CIR_XTHRDYIC_Msk                                ( 0x1UL << RCC_CIR_XTHRDYIC_Pos )
#define RCC_CIR_XTHRDYIC                                    ( RCC_CIR_XTHRDYIC_Msk )

#define RCC_CIR_RCHRDYIC_Pos                                ( 18U )
#define RCC_CIR_RCHRDYIC_Msk                                ( 0x1UL << RCC_CIR_RCHRDYIC_Pos )
#define RCC_CIR_RCHRDYIC                                    ( RCC_CIR_RCHRDYIC_Msk )

#define RCC_CIR_XTLRDYIC_Pos                                ( 17U )
#define RCC_CIR_XTLRDYIC_Msk                                ( 0x1UL << RCC_CIR_XTLRDYIC_Pos )
#define RCC_CIR_XTLRDYIC                                    ( RCC_CIR_XTLRDYIC_Msk )

#define RCC_CIR_RCLRDYIC_Pos                                ( 16U )
#define RCC_CIR_RCLRDYIC_Msk                                ( 0x1UL << RCC_CIR_RCLRDYIC_Pos )
#define RCC_CIR_RCLRDYIC                                    ( RCC_CIR_RCLRDYIC_Msk )

#define RCC_CIR_PLL3LOCKIE_Pos                              ( 14U )
#define RCC_CIR_PLL3LOCKIE_Msk                              ( 0x1UL << RCC_CIR_PLL3LOCKIE_Pos )
#define RCC_CIR_PLL3LOCKIE                                  ( RCC_CIR_PLL3LOCKIE_Msk )

#define RCC_CIR_PLL2LOCKIE_Pos                              ( 13U )
#define RCC_CIR_PLL2LOCKIE_Msk                              ( 0x1UL << RCC_CIR_PLL2LOCKIE_Pos )
#define RCC_CIR_PLL2LOCKIE                                  ( RCC_CIR_PLL2LOCKIE_Msk )

#define RCC_CIR_PLL1LOCKIE_Pos                              ( 12U )
#define RCC_CIR_PLL1LOCKIE_Msk                              ( 0x1UL << RCC_CIR_PLL1LOCKIE_Pos )
#define RCC_CIR_PLL1LOCKIE                                  ( RCC_CIR_PLL1LOCKIE_Msk )

#define RCC_CIR_XTHRDYIE_Pos                                ( 11U )
#define RCC_CIR_XTHRDYIE_Msk                                ( 0x1UL << RCC_CIR_XTHRDYIE_Pos )
#define RCC_CIR_XTHRDYIE                                    ( RCC_CIR_XTHRDYIE_Msk )

#define RCC_CIR_RCHRDYIE_Pos                                ( 10U )
#define RCC_CIR_RCHRDYIE_Msk                                ( 0x1UL << RCC_CIR_RCHRDYIE_Pos )
#define RCC_CIR_RCHRDYIE                                    ( RCC_CIR_RCHRDYIE_Msk )

#define RCC_CIR_XTLRDYIE_Pos                                ( 9U )
#define RCC_CIR_XTLRDYIE_Msk                                ( 0x1UL << RCC_CIR_XTLRDYIE_Pos )
#define RCC_CIR_XTLRDYIE                                    ( RCC_CIR_XTLRDYIE_Msk )

#define RCC_CIR_RCLRDYIE_Pos                                ( 8U )
#define RCC_CIR_RCLRDYIE_Msk                                ( 0x1UL << RCC_CIR_RCLRDYIE_Pos )
#define RCC_CIR_RCLRDYIE                                    ( RCC_CIR_RCLRDYIE_Msk )

#define RCC_CIR_PLL3LOCKIF_Pos                              ( 6U )
#define RCC_CIR_PLL3LOCKIF_Msk                              ( 0x1UL << RCC_CIR_PLL3LOCKIF_Pos )
#define RCC_CIR_PLL3LOCKIF                                  ( RCC_CIR_PLL3LOCKIF_Msk )

#define RCC_CIR_PLL2LOCKIF_Pos                              ( 5U )
#define RCC_CIR_PLL2LOCKIF_Msk                              ( 0x1UL << RCC_CIR_PLL2LOCKIF_Pos )
#define RCC_CIR_PLL2LOCKIF                                  ( RCC_CIR_PLL2LOCKIF_Msk )

#define RCC_CIR_PLL1LOCKIF_Pos                              ( 4U )
#define RCC_CIR_PLL1LOCKIF_Msk                              ( 0x1UL << RCC_CIR_PLL1LOCKIF_Pos )
#define RCC_CIR_PLL1LOCKIF                                  ( RCC_CIR_PLL1LOCKIF_Msk )

#define RCC_CIR_XTHRDYIF_Pos                                ( 3U )
#define RCC_CIR_XTHRDYIF_Msk                                ( 0x1UL << RCC_CIR_XTHRDYIF_Pos )
#define RCC_CIR_XTHRDYIF                                    ( RCC_CIR_XTHRDYIF_Msk )

#define RCC_CIR_RCHRDYIF_Pos                                ( 2U )
#define RCC_CIR_RCHRDYIF_Msk                                ( 0x1UL << RCC_CIR_RCHRDYIF_Pos )
#define RCC_CIR_RCHRDYIF                                    ( RCC_CIR_RCHRDYIF_Msk )

#define RCC_CIR_XTLRDYIF_Pos                                ( 1U )
#define RCC_CIR_XTLRDYIF_Msk                                ( 0x1UL << RCC_CIR_XTLRDYIF_Pos )
#define RCC_CIR_XTLRDYIF                                    ( RCC_CIR_XTLRDYIF_Msk )

#define RCC_CIR_RCLRDYIF_Pos                                ( 0U )
#define RCC_CIR_RCLRDYIF_Msk                                ( 0x1UL << RCC_CIR_RCLRDYIF_Pos )
#define RCC_CIR_RCLRDYIF                                    ( RCC_CIR_RCLRDYIF_Msk )


/***************  Bits definition for RCC_AHB1CKENR  **********************/

#define RCC_AHB1CKENR_SRAM3CKEN_Pos                      ( 31U )
#define RCC_AHB1CKENR_SRAM3CKEN_Msk                      ( 0x1UL << RCC_AHB1CKENR_SRAM3CKEN_Pos )
#define RCC_AHB1CKENR_SRAM3CKEN                          ( RCC_AHB1CKENR_SRAM3CKEN_Msk )

#define RCC_AHB1CKENR_SRAM2CKEN_Pos                      ( 30U )
#define RCC_AHB1CKENR_SRAM2CKEN_Msk                      ( 0x1UL << RCC_AHB1CKENR_SRAM2CKEN_Pos )
#define RCC_AHB1CKENR_SRAM2CKEN                          ( RCC_AHB1CKENR_SRAM2CKEN_Msk )

#define RCC_AHB1CKENR_SRAM1CKEN_Pos                      ( 29U )
#define RCC_AHB1CKENR_SRAM1CKEN_Msk                      ( 0x1UL << RCC_AHB1CKENR_SRAM1CKEN_Pos )
#define RCC_AHB1CKENR_SRAM1CKEN                          ( RCC_AHB1CKENR_SRAM1CKEN_Msk )

#define RCC_AHB1CKENR_ROMCKEN_Pos                        ( 28U )
#define RCC_AHB1CKENR_ROMCKEN_Msk                        ( 0x1UL << RCC_AHB1CKENR_ROMCKEN_Pos )
#define RCC_AHB1CKENR_ROMCKEN                            ( RCC_AHB1CKENR_ROMCKEN_Msk )

#define RCC_AHB1CKENR_BKPSRAMCKEN_Pos                    ( 27U )
#define RCC_AHB1CKENR_BKPSRAMCKEN_Msk                    ( 0x1UL << RCC_AHB1CKENR_BKPSRAMCKEN_Pos )
#define RCC_AHB1CKENR_BKPSRAMCKEN                        ( RCC_AHB1CKENR_BKPSRAMCKEN_Msk )

#define RCC_AHB1CKENR_FDCAN2CKEN_Pos                     ( 23U )
#define RCC_AHB1CKENR_FDCAN2CKEN_Msk                     ( 0x1UL << RCC_AHB1CKENR_FDCAN2CKEN_Pos )
#define RCC_AHB1CKENR_FDCAN2CKEN                         ( RCC_AHB1CKENR_FDCAN2CKEN_Msk )

#define RCC_AHB1CKENR_FDCAN1CKEN_Pos                     ( 22U )
#define RCC_AHB1CKENR_FDCAN1CKEN_Msk                     ( 0x1UL << RCC_AHB1CKENR_FDCAN1CKEN_Pos )
#define RCC_AHB1CKENR_FDCAN1CKEN                         ( RCC_AHB1CKENR_FDCAN1CKEN_Msk )

#define RCC_AHB1CKENR_USB2CCKEN_Pos                      ( 21U )
#define RCC_AHB1CKENR_USB2CCKEN_Msk                      ( 0x1UL << RCC_AHB1CKENR_USB2CCKEN_Pos )
#define RCC_AHB1CKENR_USB2CCKEN                          ( RCC_AHB1CKENR_USB2CCKEN_Msk )

#define RCC_AHB1CKENR_USB1CCKEN_Pos                      ( 20U )
#define RCC_AHB1CKENR_USB1CCKEN_Msk                      ( 0x1UL << RCC_AHB1CKENR_USB1CCKEN_Pos )
#define RCC_AHB1CKENR_USB1CCKEN                          ( RCC_AHB1CKENR_USB1CCKEN_Msk )

#define RCC_AHB1CKENR_SPI6CKEN_Pos                       ( 15U )
#define RCC_AHB1CKENR_SPI6CKEN_Msk                       ( 0x1UL << RCC_AHB1CKENR_SPI6CKEN_Pos )
#define RCC_AHB1CKENR_SPI6CKEN                           ( RCC_AHB1CKENR_SPI6CKEN_Msk )

#define RCC_AHB1CKENR_SPI5CKEN_Pos                       ( 14U )
#define RCC_AHB1CKENR_SPI5CKEN_Msk                       ( 0x1UL << RCC_AHB1CKENR_SPI5CKEN_Pos )
#define RCC_AHB1CKENR_SPI5CKEN                           ( RCC_AHB1CKENR_SPI5CKEN_Msk )

#define RCC_AHB1CKENR_SPI4CKEN_Pos                       ( 13U )
#define RCC_AHB1CKENR_SPI4CKEN_Msk                       ( 0x1UL << RCC_AHB1CKENR_SPI4CKEN_Pos )
#define RCC_AHB1CKENR_SPI4CKEN                           ( RCC_AHB1CKENR_SPI4CKEN_Msk )

#define RCC_AHB1CKENR_SPI3CKEN_Pos                       ( 12U )
#define RCC_AHB1CKENR_SPI3CKEN_Msk                       ( 0x1UL << RCC_AHB1CKENR_SPI3CKEN_Pos )
#define RCC_AHB1CKENR_SPI3CKEN                           ( RCC_AHB1CKENR_SPI3CKEN_Msk )

#define RCC_AHB1CKENR_SPI2CKEN_Pos                       ( 11U )
#define RCC_AHB1CKENR_SPI2CKEN_Msk                       ( 0x1UL << RCC_AHB1CKENR_SPI2CKEN_Pos )
#define RCC_AHB1CKENR_SPI2CKEN                           ( RCC_AHB1CKENR_SPI2CKEN_Msk )

#define RCC_AHB1CKENR_SPI1CKEN_Pos                       ( 10U )
#define RCC_AHB1CKENR_SPI1CKEN_Msk                       ( 0x1UL << RCC_AHB1CKENR_SPI1CKEN_Pos )
#define RCC_AHB1CKENR_SPI1CKEN                           ( RCC_AHB1CKENR_SPI1CKEN_Msk )

#define RCC_AHB1CKENR_DMA2DCKEN_Pos                      ( 9U )
#define RCC_AHB1CKENR_DMA2DCKEN_Msk                      ( 0x1UL << RCC_AHB1CKENR_DMA2DCKEN_Pos )
#define RCC_AHB1CKENR_DMA2DCKEN                          ( RCC_AHB1CKENR_DMA2DCKEN_Msk )

#define RCC_AHB1CKENR_ETHRXCKEN_Pos                      ( 8U )
#define RCC_AHB1CKENR_ETHRXCKEN_Msk                      ( 0x1UL << RCC_AHB1CKENR_ETHRXCKEN_Pos )
#define RCC_AHB1CKENR_ETHRXCKEN                          ( RCC_AHB1CKENR_ETHRXCKEN_Msk )

#define RCC_AHB1CKENR_ETHTXCKEN_Pos                      ( 7U )
#define RCC_AHB1CKENR_ETHTXCKEN_Msk                      ( 0x1UL << RCC_AHB1CKENR_ETHTXCKEN_Pos )
#define RCC_AHB1CKENR_ETHTXCKEN                          ( RCC_AHB1CKENR_ETHTXCKEN_Msk )

#define RCC_AHB1CKENR_ETHMACCKEN_Pos                     ( 6U )
#define RCC_AHB1CKENR_ETHMACCKEN_Msk                     ( 0x1UL << RCC_AHB1CKENR_ETHMACCKEN_Pos )
#define RCC_AHB1CKENR_ETHMACCKEN                         ( RCC_AHB1CKENR_ETHMACCKEN_Msk )

#define RCC_AHB1CKENR_CRCCKEN_Pos                        ( 5U )
#define RCC_AHB1CKENR_CRCCKEN_Msk                        ( 0x1UL << RCC_AHB1CKENR_CRCCKEN_Pos )
#define RCC_AHB1CKENR_CRCCKEN                            ( RCC_AHB1CKENR_CRCCKEN_Msk )

#define RCC_AHB1CKENR_DMA2CKEN_Pos                       ( 1U )
#define RCC_AHB1CKENR_DMA2CKEN_Msk                       ( 0x1UL << RCC_AHB1CKENR_DMA2CKEN_Pos )
#define RCC_AHB1CKENR_DMA2CKEN                           ( RCC_AHB1CKENR_DMA2CKEN_Msk )

#define RCC_AHB1CKENR_DMA1CKEN_Pos                       ( 0U )
#define RCC_AHB1CKENR_DMA1CKEN_Msk                       ( 0x1UL << RCC_AHB1CKENR_DMA1CKEN_Pos )
#define RCC_AHB1CKENR_DMA1CKEN                           ( RCC_AHB1CKENR_DMA1CKEN_Msk )


/***************  Bits definition for RCC_AHB2CKENR  **********************/

#define RCC_AHB2CKENR_THMCKEN_Pos                        ( 31U )
#define RCC_AHB2CKENR_THMCKEN_Msk                        ( 0x1UL << RCC_AHB2CKENR_THMCKEN_Pos )
#define RCC_AHB2CKENR_THMCKEN                            ( RCC_AHB2CKENR_THMCKEN_Msk )

#define RCC_AHB2CKENR_FDCAN3CKEN_Pos                     ( 28U )
#define RCC_AHB2CKENR_FDCAN3CKEN_Msk                     ( 0x1UL << RCC_AHB2CKENR_FDCAN3CKEN_Pos )
#define RCC_AHB2CKENR_FDCAN3CKEN                         ( RCC_AHB2CKENR_FDCAN3CKEN_Msk )

#define RCC_AHB2CKENR_CORDICCKEN_Pos                     ( 27U )
#define RCC_AHB2CKENR_CORDICCKEN_Msk                     ( 0x1UL << RCC_AHB2CKENR_CORDICCKEN_Pos )
#define RCC_AHB2CKENR_CORDICCKEN                         ( RCC_AHB2CKENR_CORDICCKEN_Msk )

#define RCC_AHB2CKENR_HRNGCKEN_Pos                       ( 26U )
#define RCC_AHB2CKENR_HRNGCKEN_Msk                       ( 0x1UL << RCC_AHB2CKENR_HRNGCKEN_Pos )
#define RCC_AHB2CKENR_HRNGCKEN                           ( RCC_AHB2CKENR_HRNGCKEN_Msk )

#define RCC_AHB2CKENR_AESCKEN_Pos                        ( 25U )
#define RCC_AHB2CKENR_AESCKEN_Msk                        ( 0x1UL << RCC_AHB2CKENR_AESCKEN_Pos )
#define RCC_AHB2CKENR_AESCKEN                            ( RCC_AHB2CKENR_AESCKEN_Msk )

#define RCC_AHB2CKENR_AESSPI1CKEN_Pos                    ( 24U )
#define RCC_AHB2CKENR_AESSPI1CKEN_Msk                    ( 0x1UL << RCC_AHB2CKENR_AESSPI1CKEN_Pos )
#define RCC_AHB2CKENR_AESSPI1CKEN                        ( RCC_AHB2CKENR_AESSPI1CKEN_Msk )

#define RCC_AHB2CKENR_DCMICKEN_Pos                       ( 23U )
#define RCC_AHB2CKENR_DCMICKEN_Msk                       ( 0x1UL << RCC_AHB2CKENR_DCMICKEN_Pos )
#define RCC_AHB2CKENR_DCMICKEN                           ( RCC_AHB2CKENR_DCMICKEN_Msk )

#define RCC_AHB2CKENR_DAC2CKEN_Pos                       ( 20U )
#define RCC_AHB2CKENR_DAC2CKEN_Msk                       ( 0x1UL << RCC_AHB2CKENR_DAC2CKEN_Pos )
#define RCC_AHB2CKENR_DAC2CKEN                           ( RCC_AHB2CKENR_DAC2CKEN_Msk )

#define RCC_AHB2CKENR_DAC1CKEN_Pos                       ( 19U )
#define RCC_AHB2CKENR_DAC1CKEN_Msk                       ( 0x1UL << RCC_AHB2CKENR_DAC1CKEN_Pos )
#define RCC_AHB2CKENR_DAC1CKEN                           ( RCC_AHB2CKENR_DAC1CKEN_Msk )

#define RCC_AHB2CKENR_ADC3CKEN_Pos                       ( 18U )
#define RCC_AHB2CKENR_ADC3CKEN_Msk                       ( 0x1UL << RCC_AHB2CKENR_ADC3CKEN_Pos )
#define RCC_AHB2CKENR_ADC3CKEN                           ( RCC_AHB2CKENR_ADC3CKEN_Msk )

#define RCC_AHB2CKENR_ADC12CKEN_Pos                      ( 17U )
#define RCC_AHB2CKENR_ADC12CKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_ADC12CKEN_Pos )
#define RCC_AHB2CKENR_ADC12CKEN                          ( RCC_AHB2CKENR_ADC12CKEN_Msk )

#define RCC_AHB2CKENR_GPIOQCKEN_Pos                      ( 16U )
#define RCC_AHB2CKENR_GPIOQCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOQCKEN_Pos )
#define RCC_AHB2CKENR_GPIOQCKEN                          ( RCC_AHB2CKENR_GPIOQCKEN_Msk )

#define RCC_AHB2CKENR_GPIOPCKEN_Pos                      ( 15U )
#define RCC_AHB2CKENR_GPIOPCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOPCKEN_Pos )
#define RCC_AHB2CKENR_GPIOPCKEN                          ( RCC_AHB2CKENR_GPIOPCKEN_Msk )

#define RCC_AHB2CKENR_GPIOOCKEN_Pos                      ( 14U )
#define RCC_AHB2CKENR_GPIOOCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOOCKEN_Pos )
#define RCC_AHB2CKENR_GPIOOCKEN                          ( RCC_AHB2CKENR_GPIOOCKEN_Msk )

#define RCC_AHB2CKENR_GPIONCKEN_Pos                      ( 13U )
#define RCC_AHB2CKENR_GPIONCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIONCKEN_Pos )
#define RCC_AHB2CKENR_GPIONCKEN                          ( RCC_AHB2CKENR_GPIONCKEN_Msk )

#define RCC_AHB2CKENR_GPIOMCKEN_Pos                      ( 12U )
#define RCC_AHB2CKENR_GPIOMCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOMCKEN_Pos )
#define RCC_AHB2CKENR_GPIOMCKEN                          ( RCC_AHB2CKENR_GPIOMCKEN_Msk )

#define RCC_AHB2CKENR_GPIOLCKEN_Pos                      ( 11U )
#define RCC_AHB2CKENR_GPIOLCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOLCKEN_Pos )
#define RCC_AHB2CKENR_GPIOLCKEN                          ( RCC_AHB2CKENR_GPIOLCKEN_Msk )

#define RCC_AHB2CKENR_GPIOKCKEN_Pos                      ( 10U )
#define RCC_AHB2CKENR_GPIOKCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOKCKEN_Pos )
#define RCC_AHB2CKENR_GPIOKCKEN                          ( RCC_AHB2CKENR_GPIOKCKEN_Msk )

#define RCC_AHB2CKENR_GPIOJCKEN_Pos                      ( 9U )
#define RCC_AHB2CKENR_GPIOJCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOJCKEN_Pos )
#define RCC_AHB2CKENR_GPIOJCKEN                          ( RCC_AHB2CKENR_GPIOJCKEN_Msk )

#define RCC_AHB2CKENR_GPIOICKEN_Pos                      ( 8U )
#define RCC_AHB2CKENR_GPIOICKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOICKEN_Pos )
#define RCC_AHB2CKENR_GPIOICKEN                          ( RCC_AHB2CKENR_GPIOICKEN_Msk )

#define RCC_AHB2CKENR_GPIOHCKEN_Pos                      ( 7U )
#define RCC_AHB2CKENR_GPIOHCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOHCKEN_Pos )
#define RCC_AHB2CKENR_GPIOHCKEN                          ( RCC_AHB2CKENR_GPIOHCKEN_Msk )

#define RCC_AHB2CKENR_GPIOGCKEN_Pos                      ( 6U )
#define RCC_AHB2CKENR_GPIOGCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOGCKEN_Pos )
#define RCC_AHB2CKENR_GPIOGCKEN                          ( RCC_AHB2CKENR_GPIOGCKEN_Msk )

#define RCC_AHB2CKENR_GPIOFCKEN_Pos                      ( 5U )
#define RCC_AHB2CKENR_GPIOFCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOFCKEN_Pos )
#define RCC_AHB2CKENR_GPIOFCKEN                          ( RCC_AHB2CKENR_GPIOFCKEN_Msk )

#define RCC_AHB2CKENR_GPIOECKEN_Pos                      ( 4U )
#define RCC_AHB2CKENR_GPIOECKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOECKEN_Pos )
#define RCC_AHB2CKENR_GPIOECKEN                          ( RCC_AHB2CKENR_GPIOECKEN_Msk )

#define RCC_AHB2CKENR_GPIODCKEN_Pos                      ( 3U )
#define RCC_AHB2CKENR_GPIODCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIODCKEN_Pos )
#define RCC_AHB2CKENR_GPIODCKEN                          ( RCC_AHB2CKENR_GPIODCKEN_Msk )

#define RCC_AHB2CKENR_GPIOCCKEN_Pos                      ( 2U )
#define RCC_AHB2CKENR_GPIOCCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOCCKEN_Pos )
#define RCC_AHB2CKENR_GPIOCCKEN                          ( RCC_AHB2CKENR_GPIOCCKEN_Msk )

#define RCC_AHB2CKENR_GPIOBCKEN_Pos                      ( 1U )
#define RCC_AHB2CKENR_GPIOBCKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOBCKEN_Pos )
#define RCC_AHB2CKENR_GPIOBCKEN                          ( RCC_AHB2CKENR_GPIOBCKEN_Msk )

#define RCC_AHB2CKENR_GPIOACKEN_Pos                      ( 0U )
#define RCC_AHB2CKENR_GPIOACKEN_Msk                      ( 0x1UL << RCC_AHB2CKENR_GPIOACKEN_Pos )
#define RCC_AHB2CKENR_GPIOACKEN                          ( RCC_AHB2CKENR_GPIOACKEN_Msk )


/***************  Bits definition for RCC_AHB3CKENR  **********************/

#define RCC_AHB3CKENR_FMCCKEN_Pos                        ( 12U )
#define RCC_AHB3CKENR_FMCCKEN_Msk                        ( 0x1UL << RCC_AHB3CKENR_FMCCKEN_Pos )
#define RCC_AHB3CKENR_FMCCKEN                            ( RCC_AHB3CKENR_FMCCKEN_Msk )

#define RCC_AHB3CKENR_OSPI2CKEN_Pos                      ( 9U )
#define RCC_AHB3CKENR_OSPI2CKEN_Msk                      ( 0x1UL << RCC_AHB3CKENR_OSPI2CKEN_Pos )
#define RCC_AHB3CKENR_OSPI2CKEN                          ( RCC_AHB3CKENR_OSPI2CKEN_Msk )

#define RCC_AHB3CKENR_OSPI1CKEN_Pos                      ( 8U )
#define RCC_AHB3CKENR_OSPI1CKEN_Msk                      ( 0x1UL << RCC_AHB3CKENR_OSPI1CKEN_Pos )
#define RCC_AHB3CKENR_OSPI1CKEN                          ( RCC_AHB3CKENR_OSPI1CKEN_Msk )

#define RCC_AHB3CKENR_SDMMCCKEN_Pos                      ( 4U )
#define RCC_AHB3CKENR_SDMMCCKEN_Msk                      ( 0x1UL << RCC_AHB3CKENR_SDMMCCKEN_Pos )
#define RCC_AHB3CKENR_SDMMCCKEN                          ( RCC_AHB3CKENR_SDMMCCKEN_Msk )

#define RCC_AHB3CKENR_SPI8CKEN_Pos                       ( 1U )
#define RCC_AHB3CKENR_SPI8CKEN_Msk                       ( 0x1UL << RCC_AHB3CKENR_SPI8CKEN_Pos )
#define RCC_AHB3CKENR_SPI8CKEN                           ( RCC_AHB3CKENR_SPI8CKEN_Msk )

#define RCC_AHB3CKENR_SPI7CKEN_Pos                       ( 0U )
#define RCC_AHB3CKENR_SPI7CKEN_Msk                       ( 0x1UL << RCC_AHB3CKENR_SPI7CKEN_Pos )
#define RCC_AHB3CKENR_SPI7CKEN                           ( RCC_AHB3CKENR_SPI7CKEN_Msk )


/***************  Bits definition for RCC_APB1CKENR1  **********************/

#define RCC_APB1CKENR1_LPUART1CKEN_Pos                   ( 31U )
#define RCC_APB1CKENR1_LPUART1CKEN_Msk                   ( 0x1UL << RCC_APB1CKENR1_LPUART1CKEN_Pos )
#define RCC_APB1CKENR1_LPUART1CKEN                       ( RCC_APB1CKENR1_LPUART1CKEN_Msk )

#define RCC_APB1CKENR1_LPTIM1CKEN_Pos                    ( 30U )
#define RCC_APB1CKENR1_LPTIM1CKEN_Msk                    ( 0x1UL << RCC_APB1CKENR1_LPTIM1CKEN_Pos )
#define RCC_APB1CKENR1_LPTIM1CKEN                        ( RCC_APB1CKENR1_LPTIM1CKEN_Msk )

#define RCC_APB1CKENR1_PMUCKEN_Pos                       ( 27U )
#define RCC_APB1CKENR1_PMUCKEN_Msk                       ( 0x1UL << RCC_APB1CKENR1_PMUCKEN_Pos )
#define RCC_APB1CKENR1_PMUCKEN                           ( RCC_APB1CKENR1_PMUCKEN_Msk )

#define RCC_APB1CKENR1_I2C4CKEN_Pos                      ( 24U )
#define RCC_APB1CKENR1_I2C4CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_I2C4CKEN_Pos )
#define RCC_APB1CKENR1_I2C4CKEN                          ( RCC_APB1CKENR1_I2C4CKEN_Msk )

#define RCC_APB1CKENR1_I2C3CKEN_Pos                      ( 23U )
#define RCC_APB1CKENR1_I2C3CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_I2C3CKEN_Pos )
#define RCC_APB1CKENR1_I2C3CKEN                          ( RCC_APB1CKENR1_I2C3CKEN_Msk )

#define RCC_APB1CKENR1_I2C2CKEN_Pos                      ( 22U )
#define RCC_APB1CKENR1_I2C2CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_I2C2CKEN_Pos )
#define RCC_APB1CKENR1_I2C2CKEN                          ( RCC_APB1CKENR1_I2C2CKEN_Msk )

#define RCC_APB1CKENR1_I2C1CKEN_Pos                      ( 21U )
#define RCC_APB1CKENR1_I2C1CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_I2C1CKEN_Pos )
#define RCC_APB1CKENR1_I2C1CKEN                          ( RCC_APB1CKENR1_I2C1CKEN_Msk )

#define RCC_APB1CKENR1_USART5CKEN_Pos                     ( 20U )
#define RCC_APB1CKENR1_USART5CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR1_USART5CKEN_Pos )
#define RCC_APB1CKENR1_USART5CKEN                         ( RCC_APB1CKENR1_USART5CKEN_Msk )

#define RCC_APB1CKENR1_USART4CKEN_Pos                     ( 19U )
#define RCC_APB1CKENR1_USART4CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR1_USART4CKEN_Pos )
#define RCC_APB1CKENR1_USART4CKEN                         ( RCC_APB1CKENR1_USART4CKEN_Msk )

#define RCC_APB1CKENR1_USART3CKEN_Pos                     ( 18U )
#define RCC_APB1CKENR1_USART3CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR1_USART3CKEN_Pos )
#define RCC_APB1CKENR1_USART3CKEN                         ( RCC_APB1CKENR1_USART3CKEN_Msk )

#define RCC_APB1CKENR1_USART2CKEN_Pos                     ( 17U )
#define RCC_APB1CKENR1_USART2CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR1_USART2CKEN_Pos )
#define RCC_APB1CKENR1_USART2CKEN                         ( RCC_APB1CKENR1_USART2CKEN_Msk )

#define RCC_APB1CKENR1_I2S3CKEN_Pos                      ( 16U )
#define RCC_APB1CKENR1_I2S3CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_I2S3CKEN_Pos )
#define RCC_APB1CKENR1_I2S3CKEN                          ( RCC_APB1CKENR1_I2S3CKEN_Msk )

#define RCC_APB1CKENR1_I2S2CKEN_Pos                      ( 15U )
#define RCC_APB1CKENR1_I2S2CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_I2S2CKEN_Pos )
#define RCC_APB1CKENR1_I2S2CKEN                          ( RCC_APB1CKENR1_I2S2CKEN_Msk )

#define RCC_APB1CKENR1_I2S1CKEN_Pos                      ( 14U )
#define RCC_APB1CKENR1_I2S1CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_I2S1CKEN_Pos )
#define RCC_APB1CKENR1_I2S1CKEN                          ( RCC_APB1CKENR1_I2S1CKEN_Msk )

#define RCC_APB1CKENR1_WDTCKEN_Pos                       ( 11U )
#define RCC_APB1CKENR1_WDTCKEN_Msk                       ( 0x1UL << RCC_APB1CKENR1_WDTCKEN_Pos )
#define RCC_APB1CKENR1_WDTCKEN                           ( RCC_APB1CKENR1_WDTCKEN_Msk )

#define RCC_APB1CKENR1_RTCCKEN_Pos                       ( 10U )
#define RCC_APB1CKENR1_RTCCKEN_Msk                       ( 0x1UL << RCC_APB1CKENR1_RTCCKEN_Pos )
#define RCC_APB1CKENR1_RTCCKEN                           ( RCC_APB1CKENR1_RTCCKEN_Msk )

#define RCC_APB1CKENR1_TIM14CKEN_Pos                     ( 8U )
#define RCC_APB1CKENR1_TIM14CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR1_TIM14CKEN_Pos )
#define RCC_APB1CKENR1_TIM14CKEN                         ( RCC_APB1CKENR1_TIM14CKEN_Msk )

#define RCC_APB1CKENR1_TIM13CKEN_Pos                     ( 7U )
#define RCC_APB1CKENR1_TIM13CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR1_TIM13CKEN_Pos )
#define RCC_APB1CKENR1_TIM13CKEN                         ( RCC_APB1CKENR1_TIM13CKEN_Msk )

#define RCC_APB1CKENR1_TIM12CKEN_Pos                     ( 6U )
#define RCC_APB1CKENR1_TIM12CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR1_TIM12CKEN_Pos )
#define RCC_APB1CKENR1_TIM12CKEN                         ( RCC_APB1CKENR1_TIM12CKEN_Msk )

#define RCC_APB1CKENR1_TIM7CKEN_Pos                      ( 5U )
#define RCC_APB1CKENR1_TIM7CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_TIM7CKEN_Pos )
#define RCC_APB1CKENR1_TIM7CKEN                          ( RCC_APB1CKENR1_TIM7CKEN_Msk )

#define RCC_APB1CKENR1_TIM6CKEN_Pos                      ( 4U )
#define RCC_APB1CKENR1_TIM6CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_TIM6CKEN_Pos )
#define RCC_APB1CKENR1_TIM6CKEN                          ( RCC_APB1CKENR1_TIM6CKEN_Msk )

#define RCC_APB1CKENR1_TIM5CKEN_Pos                      ( 3U )
#define RCC_APB1CKENR1_TIM5CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_TIM5CKEN_Pos )
#define RCC_APB1CKENR1_TIM5CKEN                          ( RCC_APB1CKENR1_TIM5CKEN_Msk )

#define RCC_APB1CKENR1_TIM4CKEN_Pos                      ( 2U )
#define RCC_APB1CKENR1_TIM4CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_TIM4CKEN_Pos )
#define RCC_APB1CKENR1_TIM4CKEN                          ( RCC_APB1CKENR1_TIM4CKEN_Msk )

#define RCC_APB1CKENR1_TIM3CKEN_Pos                      ( 1U )
#define RCC_APB1CKENR1_TIM3CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_TIM3CKEN_Pos )
#define RCC_APB1CKENR1_TIM3CKEN                          ( RCC_APB1CKENR1_TIM3CKEN_Msk )

#define RCC_APB1CKENR1_TIM2CKEN_Pos                      ( 0U )
#define RCC_APB1CKENR1_TIM2CKEN_Msk                      ( 0x1UL << RCC_APB1CKENR1_TIM2CKEN_Pos )
#define RCC_APB1CKENR1_TIM2CKEN                          ( RCC_APB1CKENR1_TIM2CKEN_Msk )


/***************  Bits definition for RCC_APB1CKENR2  **********************/

#define RCC_APB1CKENR2_EFUSE2CKEN_Pos                    ( 7U )
#define RCC_APB1CKENR2_EFUSE2CKEN_Msk                    ( 0x1UL << RCC_APB1CKENR2_EFUSE2CKEN_Pos )
#define RCC_APB1CKENR2_EFUSE2CKEN                        ( RCC_APB1CKENR2_EFUSE2CKEN_Msk )

#define RCC_APB1CKENR2_EFUSE1CKEN_Pos                    ( 6U )
#define RCC_APB1CKENR2_EFUSE1CKEN_Msk                    ( 0x1UL << RCC_APB1CKENR2_EFUSE1CKEN_Pos )
#define RCC_APB1CKENR2_EFUSE1CKEN                        ( RCC_APB1CKENR2_EFUSE1CKEN_Msk )

#define RCC_APB1CKENR2_TIM26CKEN_Pos                     ( 5U )
#define RCC_APB1CKENR2_TIM26CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR2_TIM26CKEN_Pos )
#define RCC_APB1CKENR2_TIM26CKEN                         ( RCC_APB1CKENR2_TIM26CKEN_Msk )

#define RCC_APB1CKENR2_TIM25CKEN_Pos                     ( 4U )
#define RCC_APB1CKENR2_TIM25CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR2_TIM25CKEN_Pos )
#define RCC_APB1CKENR2_TIM25CKEN                         ( RCC_APB1CKENR2_TIM25CKEN_Msk )

#define RCC_APB1CKENR2_USART8CKEN_Pos                     ( 3U )
#define RCC_APB1CKENR2_USART8CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR2_USART8CKEN_Pos )
#define RCC_APB1CKENR2_USART8CKEN                         ( RCC_APB1CKENR2_USART8CKEN_Msk )

#define RCC_APB1CKENR2_USART7CKEN_Pos                     ( 2U )
#define RCC_APB1CKENR2_USART7CKEN_Msk                     ( 0x1UL << RCC_APB1CKENR2_USART7CKEN_Pos )
#define RCC_APB1CKENR2_USART7CKEN                         ( RCC_APB1CKENR2_USART7CKEN_Msk )

#define RCC_APB1CKENR2_LPTIM2CKEN_Pos                    ( 1U )
#define RCC_APB1CKENR2_LPTIM2CKEN_Msk                    ( 0x1UL << RCC_APB1CKENR2_LPTIM2CKEN_Pos )
#define RCC_APB1CKENR2_LPTIM2CKEN                        ( RCC_APB1CKENR2_LPTIM2CKEN_Msk )


/***************  Bits definition for RCC_APB2CKENR  **********************/

#define RCC_APB2CKENR_USART10CKEN_Pos                     ( 31U )
#define RCC_APB2CKENR_USART10CKEN_Msk                     ( 0x1UL << RCC_APB2CKENR_USART10CKEN_Pos )
#define RCC_APB2CKENR_USART10CKEN                         ( RCC_APB2CKENR_USART10CKEN_Msk )

#define RCC_APB2CKENR_USART9CKEN_Pos                      ( 30U )
#define RCC_APB2CKENR_USART9CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_USART9CKEN_Pos )
#define RCC_APB2CKENR_USART9CKEN                          ( RCC_APB2CKENR_USART9CKEN_Msk )

#define RCC_APB2CKENR_TIM24CKEN_Pos                      ( 29U )
#define RCC_APB2CKENR_TIM24CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM24CKEN_Pos )
#define RCC_APB2CKENR_TIM24CKEN                          ( RCC_APB2CKENR_TIM24CKEN_Msk )

#define RCC_APB2CKENR_TIM23CKEN_Pos                      ( 28U )
#define RCC_APB2CKENR_TIM23CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM23CKEN_Pos )
#define RCC_APB2CKENR_TIM23CKEN                          ( RCC_APB2CKENR_TIM23CKEN_Msk )

#define RCC_APB2CKENR_TIM22CKEN_Pos                      ( 27U )
#define RCC_APB2CKENR_TIM22CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM22CKEN_Pos )
#define RCC_APB2CKENR_TIM22CKEN                          ( RCC_APB2CKENR_TIM22CKEN_Msk )

#define RCC_APB2CKENR_TIM21CKEN_Pos                      ( 26U )
#define RCC_APB2CKENR_TIM21CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM21CKEN_Pos )
#define RCC_APB2CKENR_TIM21CKEN                          ( RCC_APB2CKENR_TIM21CKEN_Msk )

#define RCC_APB2CKENR_TIM19CKEN_Pos                      ( 25U )
#define RCC_APB2CKENR_TIM19CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM19CKEN_Pos )
#define RCC_APB2CKENR_TIM19CKEN                          ( RCC_APB2CKENR_TIM19CKEN_Msk )

#define RCC_APB2CKENR_TIM18CKEN_Pos                      ( 24U )
#define RCC_APB2CKENR_TIM18CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM18CKEN_Pos )
#define RCC_APB2CKENR_TIM18CKEN                          ( RCC_APB2CKENR_TIM18CKEN_Msk )

#define RCC_APB2CKENR_TIM11CKEN_Pos                      ( 23U )
#define RCC_APB2CKENR_TIM11CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM11CKEN_Pos )
#define RCC_APB2CKENR_TIM11CKEN                          ( RCC_APB2CKENR_TIM11CKEN_Msk )

#define RCC_APB2CKENR_TIM10CKEN_Pos                      ( 22U )
#define RCC_APB2CKENR_TIM10CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM10CKEN_Pos )
#define RCC_APB2CKENR_TIM10CKEN                          ( RCC_APB2CKENR_TIM10CKEN_Msk )

#define RCC_APB2CKENR_TIM9CKEN_Pos                       ( 21U )
#define RCC_APB2CKENR_TIM9CKEN_Msk                       ( 0x1UL << RCC_APB2CKENR_TIM9CKEN_Pos )
#define RCC_APB2CKENR_TIM9CKEN                           ( RCC_APB2CKENR_TIM9CKEN_Msk )

#define RCC_APB2CKENR_LTDCCKEN_Pos                       ( 19U )
#define RCC_APB2CKENR_LTDCCKEN_Msk                       ( 0x1UL << RCC_APB2CKENR_LTDCCKEN_Pos )
#define RCC_APB2CKENR_LTDCCKEN                           ( RCC_APB2CKENR_LTDCCKEN_Msk )

#define RCC_APB2CKENR_TKEYCKEN_Pos                       ( 18U )
#define RCC_APB2CKENR_TKEYCKEN_Msk                       ( 0x1UL << RCC_APB2CKENR_TKEYCKEN_Pos )
#define RCC_APB2CKENR_TKEYCKEN                           ( RCC_APB2CKENR_TKEYCKEN_Msk )

#define RCC_APB2CKENR_TIM20CKEN_Pos                      ( 15U )
#define RCC_APB2CKENR_TIM20CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM20CKEN_Pos )
#define RCC_APB2CKENR_TIM20CKEN                          ( RCC_APB2CKENR_TIM20CKEN_Msk )

#define RCC_APB2CKENR_TIM17CKEN_Pos                      ( 13U )
#define RCC_APB2CKENR_TIM17CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM17CKEN_Pos )
#define RCC_APB2CKENR_TIM17CKEN                          ( RCC_APB2CKENR_TIM17CKEN_Msk )

#define RCC_APB2CKENR_TIM16CKEN_Pos                      ( 12U )
#define RCC_APB2CKENR_TIM16CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM16CKEN_Pos )
#define RCC_APB2CKENR_TIM16CKEN                          ( RCC_APB2CKENR_TIM16CKEN_Msk )

#define RCC_APB2CKENR_TIM15CKEN_Pos                      ( 11U )
#define RCC_APB2CKENR_TIM15CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_TIM15CKEN_Pos )
#define RCC_APB2CKENR_TIM15CKEN                          ( RCC_APB2CKENR_TIM15CKEN_Msk )

#define RCC_APB2CKENR_USART6CKEN_Pos                      ( 10U )
#define RCC_APB2CKENR_USART6CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_USART6CKEN_Pos )
#define RCC_APB2CKENR_USART6CKEN                          ( RCC_APB2CKENR_USART6CKEN_Msk )

#define RCC_APB2CKENR_USART1CKEN_Pos                      ( 9U )
#define RCC_APB2CKENR_USART1CKEN_Msk                      ( 0x1UL << RCC_APB2CKENR_USART1CKEN_Pos )
#define RCC_APB2CKENR_USART1CKEN                          ( RCC_APB2CKENR_USART1CKEN_Msk )

#define RCC_APB2CKENR_TIM8CKEN_Pos                       ( 8U )
#define RCC_APB2CKENR_TIM8CKEN_Msk                       ( 0x1UL << RCC_APB2CKENR_TIM8CKEN_Pos )
#define RCC_APB2CKENR_TIM8CKEN                           ( RCC_APB2CKENR_TIM8CKEN_Msk )

#define RCC_APB2CKENR_TIM1CKEN_Pos                       ( 6U )
#define RCC_APB2CKENR_TIM1CKEN_Msk                       ( 0x1UL << RCC_APB2CKENR_TIM1CKEN_Pos )
#define RCC_APB2CKENR_TIM1CKEN                           ( RCC_APB2CKENR_TIM1CKEN_Msk )

#define RCC_APB2CKENR_EXTICKEN_Pos                       ( 4U )
#define RCC_APB2CKENR_EXTICKEN_Msk                       ( 0x1UL << RCC_APB2CKENR_EXTICKEN_Pos )
#define RCC_APB2CKENR_EXTICKEN                           ( RCC_APB2CKENR_EXTICKEN_Msk )

#define RCC_APB2CKENR_CMP1CKEN_A_Pos                     ( 2U )
#define RCC_APB2CKENR_CMP1CKEN_A_Msk                     ( 0x1UL << RCC_APB2CKENR_CMP1CKEN_A_Pos )
#define RCC_APB2CKENR_CMP1CKEN_A                         ( RCC_APB2CKENR_CMP1CKEN_A_Msk )

#define RCC_APB2CKENR_SYSCFGCKEN_Pos                     ( 0U )
#define RCC_APB2CKENR_SYSCFGCKEN_Msk                     ( 0x1UL << RCC_APB2CKENR_SYSCFGCKEN_Pos )
#define RCC_APB2CKENR_SYSCFGCKEN                         ( RCC_APB2CKENR_SYSCFGCKEN_Msk )


/***************  Bits definition for RCC_APB3CKENR  **********************/

#define RCC_APB3CKENR_LPTIM6CKEN_Pos                     ( 3U )
#define RCC_APB3CKENR_LPTIM6CKEN_Msk                     ( 0x1UL << RCC_APB3CKENR_LPTIM6CKEN_Pos )
#define RCC_APB3CKENR_LPTIM6CKEN                         ( RCC_APB3CKENR_LPTIM6CKEN_Msk )

#define RCC_APB3CKENR_LPTIM5CKEN_Pos                     ( 2U )
#define RCC_APB3CKENR_LPTIM5CKEN_Msk                     ( 0x1UL << RCC_APB3CKENR_LPTIM5CKEN_Pos )
#define RCC_APB3CKENR_LPTIM5CKEN                         ( RCC_APB3CKENR_LPTIM5CKEN_Msk )

#define RCC_APB3CKENR_LPTIM4CKEN_Pos                     ( 1U )
#define RCC_APB3CKENR_LPTIM4CKEN_Msk                     ( 0x1UL << RCC_APB3CKENR_LPTIM4CKEN_Pos )
#define RCC_APB3CKENR_LPTIM4CKEN                         ( RCC_APB3CKENR_LPTIM4CKEN_Msk )

#define RCC_APB3CKENR_LPTIM3CKEN_Pos                     ( 0U )
#define RCC_APB3CKENR_LPTIM3CKEN_Msk                     ( 0x1UL << RCC_APB3CKENR_LPTIM3CKEN_Pos )
#define RCC_APB3CKENR_LPTIM3CKEN                         ( RCC_APB3CKENR_LPTIM3CKEN_Msk )

/***************  Bits definition for RCC_APB4CKENR  **********************/

#define RCC_APB4CKENR_DPWM6CKEN_Pos                      ( 17U )
#define RCC_APB4CKENR_DPWM6CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_DPWM6CKEN_Pos )
#define RCC_APB4CKENR_DPWM6CKEN                          ( RCC_APB4CKENR_DPWM6CKEN_Msk )

#define RCC_APB4CKENR_DPWM5CKEN_Pos                      ( 16U )
#define RCC_APB4CKENR_DPWM5CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_DPWM5CKEN_Pos )
#define RCC_APB4CKENR_DPWM5CKEN                          ( RCC_APB4CKENR_DPWM5CKEN_Msk )

#define RCC_APB4CKENR_SPWM6CKEN_Pos                      ( 15U )
#define RCC_APB4CKENR_SPWM6CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_SPWM6CKEN_Pos )
#define RCC_APB4CKENR_SPWM6CKEN                          ( RCC_APB4CKENR_SPWM6CKEN_Msk )

#define RCC_APB4CKENR_SPWM5CKEN_Pos                      ( 14U )
#define RCC_APB4CKENR_SPWM5CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_SPWM5CKEN_Pos )
#define RCC_APB4CKENR_SPWM5CKEN                          ( RCC_APB4CKENR_SPWM5CKEN_Msk )

#define RCC_APB4CKENR_SPWM4CKEN_Pos                      ( 13U )
#define RCC_APB4CKENR_SPWM4CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_SPWM4CKEN_Pos )
#define RCC_APB4CKENR_SPWM4CKEN                          ( RCC_APB4CKENR_SPWM4CKEN_Msk )

#define RCC_APB4CKENR_SPWM3CKEN_Pos                      ( 12U )
#define RCC_APB4CKENR_SPWM3CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_SPWM3CKEN_Pos )
#define RCC_APB4CKENR_SPWM3CKEN                          ( RCC_APB4CKENR_SPWM3CKEN_Msk )

#define RCC_APB4CKENR_MDACCKEN_Pos                       ( 8U )
#define RCC_APB4CKENR_MDACCKEN_Msk                       ( 0x1UL << RCC_APB4CKENR_MDACCKEN_Pos )
#define RCC_APB4CKENR_MDACCKEN                           ( RCC_APB4CKENR_MDACCKEN_Msk )

#define RCC_APB4CKENR_LPTCKEN_Pos                        ( 7U )
#define RCC_APB4CKENR_LPTCKEN_Msk                        ( 0x1UL << RCC_APB4CKENR_LPTCKEN_Pos )
#define RCC_APB4CKENR_LPTCKEN                            ( RCC_APB4CKENR_LPTCKEN_Msk )

#define RCC_APB4CKENR_PNDLCKEN_Pos                       ( 6U )
#define RCC_APB4CKENR_PNDLCKEN_Msk                       ( 0x1UL << RCC_APB4CKENR_PNDLCKEN_Pos )
#define RCC_APB4CKENR_PNDLCKEN                           ( RCC_APB4CKENR_PNDLCKEN_Msk )

#define RCC_APB4CKENR_DPWM4CKEN_Pos                      ( 5U )
#define RCC_APB4CKENR_DPWM4CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_DPWM4CKEN_Pos )
#define RCC_APB4CKENR_DPWM4CKEN                          ( RCC_APB4CKENR_DPWM4CKEN_Msk )

#define RCC_APB4CKENR_DPWM3CKEN_Pos                      ( 4U )
#define RCC_APB4CKENR_DPWM3CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_DPWM3CKEN_Pos )
#define RCC_APB4CKENR_DPWM3CKEN                          ( RCC_APB4CKENR_DPWM3CKEN_Msk )

#define RCC_APB4CKENR_DPWM2CKEN_Pos                      ( 3U )
#define RCC_APB4CKENR_DPWM2CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_DPWM2CKEN_Pos )
#define RCC_APB4CKENR_DPWM2CKEN                          ( RCC_APB4CKENR_DPWM2CKEN_Msk )

#define RCC_APB4CKENR_DPWM1CKEN_Pos                      ( 2U )
#define RCC_APB4CKENR_DPWM1CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_DPWM1CKEN_Pos )
#define RCC_APB4CKENR_DPWM1CKEN                          ( RCC_APB4CKENR_DPWM1CKEN_Msk )

#define RCC_APB4CKENR_SPWM2CKEN_Pos                      ( 1U )
#define RCC_APB4CKENR_SPWM2CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_SPWM2CKEN_Pos )
#define RCC_APB4CKENR_SPWM2CKEN                          ( RCC_APB4CKENR_SPWM2CKEN_Msk )

#define RCC_APB4CKENR_SPWM1CKEN_Pos                      ( 0U )
#define RCC_APB4CKENR_SPWM1CKEN_Msk                      ( 0x1UL << RCC_APB4CKENR_SPWM1CKEN_Pos )
#define RCC_APB4CKENR_SPWM1CKEN                          ( RCC_APB4CKENR_SPWM1CKEN_Msk )


/***************  Bits definition for RCC_RCHCR  **********************/

#define RCC_RCHCR_RCHPRDY_Pos                           ( 24U )
#define RCC_RCHCR_RCHPRDY_Msk                           ( 0x1UL << RCC_RCHCR_RCHPRDY_Pos )
#define RCC_RCHCR_RCHPRDY                               ( RCC_RCHCR_RCHPRDY_Msk )

#define RCC_RCHCR_RCHSEL_Pos                            ( 21U )
#define RCC_RCHCR_RCHSEL_Msk                            ( 0x1UL << RCC_RCHCR_RCHSEL_Pos )
#define RCC_RCHCR_RCHSEL                                ( RCC_RCHCR_RCHSEL_Msk )

#define RCC_RCHCR_RCHPEN_Pos                            ( 20U )
#define RCC_RCHCR_RCHPEN_Msk                            ( 0x1UL << RCC_RCHCR_RCHPEN_Pos )
#define RCC_RCHCR_RCHPEN                                ( RCC_RCHCR_RCHPEN_Msk )

#define RCC_RCHCR_RCHTRIMH_Pos                          ( 15U )
#define RCC_RCHCR_RCHTRIMH_Msk                          ( 0x3UL << RCC_RCHCR_RCHTRIMH_Pos )
#define RCC_RCHCR_RCHTRIMH                              ( RCC_RCHCR_RCHTRIMH_Msk )

#define RCC_RCHCR_RCHTRIML_Pos                          ( 8U )
#define RCC_RCHCR_RCHTRIML_Msk                          ( 0x7FUL << RCC_RCHCR_RCHTRIML_Pos )
#define RCC_RCHCR_RCHTRIML                              ( RCC_RCHCR_RCHTRIML_Msk )

#define RCC_RCHCR_RCHRDY_Pos                            ( 4U )
#define RCC_RCHCR_RCHRDY_Msk                            ( 0x1UL << RCC_RCHCR_RCHRDY_Pos )
#define RCC_RCHCR_RCHRDY                                ( RCC_RCHCR_RCHRDY_Msk )

#define RCC_RCHCR_RCHDIV_Pos                           ( 3U )
#define RCC_RCHCR_RCHDIV_Msk                           ( 0x1UL << RCC_RCHCR_RCHDIV_Pos )
#define RCC_RCHCR_RCHDIV                               ( RCC_RCHCR_RCHDIV_Msk )

#define RCC_RCHCR_RCHEN_Pos                            ( 0U )
#define RCC_RCHCR_RCHEN_Msk                            ( 0x1UL << RCC_RCHCR_RCHEN_Pos )
#define RCC_RCHCR_RCHEN                                ( RCC_RCHCR_RCHEN_Msk )


/***************  Bits definition for RCC_XTHCR  **********************/

#define RCC_XTHCR_XTHSDEN_Pos                               ( 8U )
#define RCC_XTHCR_XTHSDEN_Msk                               ( 0x1UL << RCC_XTHCR_XTHSDEN_Pos )
#define RCC_XTHCR_XTHSDEN                                   ( RCC_XTHCR_XTHSDEN_Msk )

#define RCC_XTHCR_XTHRDY_Pos                                ( 4U )
#define RCC_XTHCR_XTHRDY_Msk                                ( 0x1UL << RCC_XTHCR_XTHRDY_Pos )
#define RCC_XTHCR_XTHRDY                                    ( RCC_XTHCR_XTHRDY_Msk )

#define RCC_XTHCR_XTHRDYTIME_Pos                           ( 2U )
#define RCC_XTHCR_XTHRDYTIME_Msk                           ( 0x3UL << RCC_XTHCR_XTHRDYTIME_Pos )
#define RCC_XTHCR_XTHRDYTIME                               ( RCC_XTHCR_XTHRDYTIME_Msk )
#define RCC_XTHCR_XTHRDYTIME_0                             ( 0x1UL << RCC_XTHCR_XTHRDYTIME_Pos )
#define RCC_XTHCR_XTHRDYTIME_1                             ( 0x2UL << RCC_XTHCR_XTHRDYTIME_Pos )

#define RCC_XTHCR_XTHBYP_Pos                               ( 1U )
#define RCC_XTHCR_XTHBYP_Msk                               ( 0x1UL << RCC_XTHCR_XTHBYP_Pos )
#define RCC_XTHCR_XTHBYP                                   ( RCC_XTHCR_XTHBYP_Msk )

#define RCC_XTHCR_XTHEN_Pos                                ( 0U )
#define RCC_XTHCR_XTHEN_Msk                                ( 0x1UL << RCC_XTHCR_XTHEN_Pos )
#define RCC_XTHCR_XTHEN                                    ( RCC_XTHCR_XTHEN_Msk )


/***************  Bits definition for RCC_PLL1CR  **********************/

#define RCC_PLL1CR_PLL1LOCKSEL_Pos                         ( 31U )
#define RCC_PLL1CR_PLL1LOCKSEL_Msk                         ( 0x1UL << RCC_PLL1CR_PLL1LOCKSEL_Pos )
#define RCC_PLL1CR_PLL1LOCKSEL                             ( RCC_PLL1CR_PLL1LOCKSEL_Msk )

#define RCC_PLL1CR_PLL1FREERUN_Pos                         ( 30U )
#define RCC_PLL1CR_PLL1FREERUN_Msk                         ( 0x1UL << RCC_PLL1CR_PLL1FREERUN_Pos )
#define RCC_PLL1CR_PLL1FREERUN                             ( RCC_PLL1CR_PLL1FREERUN_Msk )

#define RCC_PLL1CR_PLL1LOCK_Pos                             ( 29U )
#define RCC_PLL1CR_PLL1LOCK_Msk                             ( 0x1UL << RCC_PLL1CR_PLL1LOCK_Pos )
#define RCC_PLL1CR_PLL1LOCK                                 ( RCC_PLL1CR_PLL1LOCK_Msk )

#define RCC_PLL1CR_PLL1LOCKDLY_Pos                         ( 23U )
#define RCC_PLL1CR_PLL1LOCKDLY_Msk                         ( 0x3FUL << RCC_PLL1CR_PLL1LOCKDLY_Pos )
#define RCC_PLL1CR_PLL1LOCKDLY                             ( RCC_PLL1CR_PLL1LOCKDLY_Msk )
#define RCC_PLL1CR_PLL1LOCKDLY_0                           ( 0x1UL << RCC_PLL1CR_PLL1LOCKDLY_Pos )
#define RCC_PLL1CR_PLL1LOCKDLY_1                           ( 0x2UL << RCC_PLL1CR_PLL1LOCKDLY_Pos )
#define RCC_PLL1CR_PLL1LOCKDLY_2                           ( 0x4UL << RCC_PLL1CR_PLL1LOCKDLY_Pos )
#define RCC_PLL1CR_PLL1LOCKDLY_3                           ( 0x8UL << RCC_PLL1CR_PLL1LOCKDLY_Pos )
#define RCC_PLL1CR_PLL1LOCKDLY_4                           ( 0x10UL << RCC_PLL1CR_PLL1LOCKDLY_Pos )
#define RCC_PLL1CR_PLL1LOCKDLY_5                           ( 0x20UL << RCC_PLL1CR_PLL1LOCKDLY_Pos )

#define RCC_PLL1CR_PLL1UPDATEEN_Pos                        ( 22U )
#define RCC_PLL1CR_PLL1UPDATEEN_Msk                        ( 0x1UL << RCC_PLL1CR_PLL1UPDATEEN_Pos )
#define RCC_PLL1CR_PLL1UPDATEEN                            ( RCC_PLL1CR_PLL1UPDATEEN_Msk )

#define RCC_PLL1CR_PLL1SLEEP_Pos                            ( 21U )
#define RCC_PLL1CR_PLL1SLEEP_Msk                            ( 0x1UL << RCC_PLL1CR_PLL1SLEEP_Pos )
#define RCC_PLL1CR_PLL1SLEEP                                ( RCC_PLL1CR_PLL1SLEEP_Msk )

#define RCC_PLL1CR_PLL1QCLKEN_Pos                          ( 5U )
#define RCC_PLL1CR_PLL1QCLKEN_Msk                          ( 0x1UL << RCC_PLL1CR_PLL1QCLKEN_Pos )
#define RCC_PLL1CR_PLL1QCLKEN                              ( RCC_PLL1CR_PLL1QCLKEN_Msk )

#define RCC_PLL1CR_PLL1PCLKEN_Pos                          ( 4U )
#define RCC_PLL1CR_PLL1PCLKEN_Msk                          ( 0x1UL << RCC_PLL1CR_PLL1PCLKEN_Pos )
#define RCC_PLL1CR_PLL1PCLKEN                              ( RCC_PLL1CR_PLL1PCLKEN_Msk )

#define RCC_PLL1CR_PLL1SRCSEL_Pos                          ( 1U )
#define RCC_PLL1CR_PLL1SRCSEL_Msk                          ( 0x1UL << RCC_PLL1CR_PLL1SRCSEL_Pos )
#define RCC_PLL1CR_PLL1SRCSEL                              ( RCC_PLL1CR_PLL1SRCSEL_Msk )

#define RCC_PLL1CR_PLL1EN_Pos                               ( 0U )
#define RCC_PLL1CR_PLL1EN_Msk                               ( 0x1UL << RCC_PLL1CR_PLL1EN_Pos )
#define RCC_PLL1CR_PLL1EN                                   ( RCC_PLL1CR_PLL1EN_Msk )


/***************  Bits definition for RCC_PLL1CFR  **********************/

#define RCC_PLL1CFR_PLL1Q_Pos                               ( 24U )
#define RCC_PLL1CFR_PLL1Q_Msk                               ( 0xfUL << RCC_PLL1CFR_PLL1Q_Pos )
#define RCC_PLL1CFR_PLL1Q                                   ( RCC_PLL1CFR_PLL1Q_Msk )
#define RCC_PLL1CFR_PLL1Q_0                                 ( 0x1UL << RCC_PLL1CFR_PLL1Q_Pos )
#define RCC_PLL1CFR_PLL1Q_1                                 ( 0x2UL << RCC_PLL1CFR_PLL1Q_Pos )
#define RCC_PLL1CFR_PLL1Q_2                                 ( 0x4UL << RCC_PLL1CFR_PLL1Q_Pos )
#define RCC_PLL1CFR_PLL1Q_3                                 ( 0x8UL << RCC_PLL1CFR_PLL1Q_Pos )

#define RCC_PLL1CFR_PLL1P_Pos                               ( 20U )
#define RCC_PLL1CFR_PLL1P_Msk                               ( 0x3UL << RCC_PLL1CFR_PLL1P_Pos )
#define RCC_PLL1CFR_PLL1P                                   ( RCC_PLL1CFR_PLL1P_Msk )
#define RCC_PLL1CFR_PLL1P_0                                 ( 0x1UL << RCC_PLL1CFR_PLL1P_Pos )
#define RCC_PLL1CFR_PLL1P_1                                 ( 0x2UL << RCC_PLL1CFR_PLL1P_Pos )

#define RCC_PLL1CFR_PLL1N_Pos                               ( 12U )
#define RCC_PLL1CFR_PLL1N_Msk                               ( 0x3fUL << RCC_PLL1CFR_PLL1N_Pos )
#define RCC_PLL1CFR_PLL1N                                   ( RCC_PLL1CFR_PLL1N_Msk )
#define RCC_PLL1CFR_PLL1N_0                                 ( 0x1UL << RCC_PLL1CFR_PLL1N_Pos )
#define RCC_PLL1CFR_PLL1N_1                                 ( 0x2UL << RCC_PLL1CFR_PLL1N_Pos )
#define RCC_PLL1CFR_PLL1N_2                                 ( 0x4UL << RCC_PLL1CFR_PLL1N_Pos )
#define RCC_PLL1CFR_PLL1N_3                                 ( 0x8UL << RCC_PLL1CFR_PLL1N_Pos )
#define RCC_PLL1CFR_PLL1N_4                                 ( 0x10UL << RCC_PLL1CFR_PLL1N_Pos )
#define RCC_PLL1CFR_PLL1N_5                                 ( 0x20UL << RCC_PLL1CFR_PLL1N_Pos )

#define RCC_PLL1CFR_PLL1F_Pos                               ( 0U )
#define RCC_PLL1CFR_PLL1F_Msk                               ( 0x1ffUL << RCC_PLL1CFR_PLL1F_Pos )
#define RCC_PLL1CFR_PLL1F                                   ( RCC_PLL1CFR_PLL1F_Msk )


/***************  Bits definition for RCC_PLL1SCR  **********************/

#define RCC_PLL1SCR_PLL1SSCSTP_Pos                             ( 17U )
#define RCC_PLL1SCR_PLL1SSCSTP_Msk                             ( 0x7fffUL << RCC_PLL1SCR_PLL1SSCSTP_Pos )
#define RCC_PLL1SCR_PLL1SSCSTP                                 ( RCC_PLL1SCR_PLL1SSCSTP_Msk )

#define RCC_PLL1SCR_PLL1SSCPER_Pos                             ( 4U )
#define RCC_PLL1SCR_PLL1SSCPER_Msk                             ( 0x1fffUL << RCC_PLL1SCR_PLL1SSCPER_Pos )
#define RCC_PLL1SCR_PLL1SSCPER                                 ( RCC_PLL1SCR_PLL1SSCPER_Msk )

#define RCC_PLL1SCR_PLL1SSCMD_Pos                              ( 1U )
#define RCC_PLL1SCR_PLL1SSCMD_Msk                              ( 0x1UL << RCC_PLL1SCR_PLL1SSCMD_Pos )
#define RCC_PLL1SCR_PLL1SSCMD                                  ( RCC_PLL1SCR_PLL1SSCMD_Msk )

#define RCC_PLL1SCR_PLL1SSCEN_Pos                              ( 0U )
#define RCC_PLL1SCR_PLL1SSCEN_Msk                              ( 0x1UL << RCC_PLL1SCR_PLL1SSCEN_Pos )
#define RCC_PLL1SCR_PLL1SSCEN                                  ( RCC_PLL1SCR_PLL1SSCEN_Msk )


/***************  Bits definition for RCC_PLL2CR  **********************/

#define RCC_PLL2CR_PLL2LOCKSEL_Pos                         ( 31U )
#define RCC_PLL2CR_PLL2LOCKSEL_Msk                         ( 0x1UL << RCC_PLL2CR_PLL2LOCKSEL_Pos )
#define RCC_PLL2CR_PLL2LOCKSEL                             ( RCC_PLL2CR_PLL2LOCKSEL_Msk )

#define RCC_PLL2CR_PLL2FREERUN_Pos                         ( 30U )
#define RCC_PLL2CR_PLL2FREERUN_Msk                         ( 0x1UL << RCC_PLL2CR_PLL2FREERUN_Pos )
#define RCC_PLL2CR_PLL2FREERUN                             ( RCC_PLL2CR_PLL2FREERUN_Msk )

#define RCC_PLL2CR_PLL2LOCK_Pos                             ( 29U )
#define RCC_PLL2CR_PLL2LOCK_Msk                             ( 0x1UL << RCC_PLL2CR_PLL2LOCK_Pos )
#define RCC_PLL2CR_PLL2LOCK                                 ( RCC_PLL2CR_PLL2LOCK_Msk )

#define RCC_PLL2CR_PLL2LOCKDLY_Pos                         ( 23U )
#define RCC_PLL2CR_PLL2LOCKDLY_Msk                         ( 0x3fUL << RCC_PLL2CR_PLL2LOCKDLY_Pos )
#define RCC_PLL2CR_PLL2LOCKDLY                             ( RCC_PLL2CR_PLL2LOCKDLY_Msk )
#define RCC_PLL2CR_PLL2LOCKDLY_0                           ( 0x1UL << RCC_PLL2CR_PLL2LOCKDLY_Pos )
#define RCC_PLL2CR_PLL2LOCKDLY_1                           ( 0x2UL << RCC_PLL2CR_PLL2LOCKDLY_Pos )
#define RCC_PLL2CR_PLL2LOCKDLY_2                           ( 0x4UL << RCC_PLL2CR_PLL2LOCKDLY_Pos )
#define RCC_PLL2CR_PLL2LOCKDLY_3                           ( 0x8UL << RCC_PLL2CR_PLL2LOCKDLY_Pos )
#define RCC_PLL2CR_PLL2LOCKDLY_4                           ( 0x10UL << RCC_PLL2CR_PLL2LOCKDLY_Pos )
#define RCC_PLL2CR_PLL2LOCKDLY_5                           ( 0x20UL << RCC_PLL2CR_PLL2LOCKDLY_Pos )

#define RCC_PLL2CR_PLL2UPDATEEN_Pos                        ( 22U )
#define RCC_PLL2CR_PLL2UPDATEEN_Msk                        ( 0x1UL << RCC_PLL2CR_PLL2UPDATEEN_Pos )
#define RCC_PLL2CR_PLL2UPDATEEN                            ( RCC_PLL2CR_PLL2UPDATEEN_Msk )

#define RCC_PLL2CR_PLL2SLEEP_Pos                            ( 21U )
#define RCC_PLL2CR_PLL2SLEEP_Msk                            ( 0x1UL << RCC_PLL2CR_PLL2SLEEP_Pos )
#define RCC_PLL2CR_PLL2SLEEP                                ( RCC_PLL2CR_PLL2SLEEP_Msk )

#define RCC_PLL2CR_PLL2QCLKEN_Pos                          ( 5U )
#define RCC_PLL2CR_PLL2QCLKEN_Msk                          ( 0x1UL << RCC_PLL2CR_PLL2QCLKEN_Pos )
#define RCC_PLL2CR_PLL2QCLKEN                              ( RCC_PLL2CR_PLL2QCLKEN_Msk )

#define RCC_PLL2CR_PLL2PCLKEN_Pos                          ( 4U )
#define RCC_PLL2CR_PLL2PCLKEN_Msk                          ( 0x1UL << RCC_PLL2CR_PLL2PCLKEN_Pos )
#define RCC_PLL2CR_PLL2PCLKEN                              ( RCC_PLL2CR_PLL2PCLKEN_Msk )

#define RCC_PLL2CR_PLL2SRCSEL_Pos                          ( 1U )
#define RCC_PLL2CR_PLL2SRCSEL_Msk                          ( 0x1UL << RCC_PLL2CR_PLL2SRCSEL_Pos )
#define RCC_PLL2CR_PLL2SRCSEL                              ( RCC_PLL2CR_PLL2SRCSEL_Msk )

#define RCC_PLL2CR_PLL2EN_Pos                               ( 0U )
#define RCC_PLL2CR_PLL2EN_Msk                               ( 0x1UL << RCC_PLL2CR_PLL2EN_Pos )
#define RCC_PLL2CR_PLL2EN                                   ( RCC_PLL2CR_PLL2EN_Msk )


/***************  Bits definition for RCC_PLL2CFR  **********************/

#define RCC_PLL2CFR_PLL2Q_Pos                               ( 24U )
#define RCC_PLL2CFR_PLL2Q_Msk                               ( 0xfUL << RCC_PLL2CFR_PLL2Q_Pos )
#define RCC_PLL2CFR_PLL2Q                                   ( RCC_PLL2CFR_PLL2Q_Msk )
#define RCC_PLL2CFR_PLL2Q_0                                 ( 0x1UL << RCC_PLL2CFR_PLL2Q_Pos )
#define RCC_PLL2CFR_PLL2Q_1                                 ( 0x2UL << RCC_PLL2CFR_PLL2Q_Pos )
#define RCC_PLL2CFR_PLL2Q_2                                 ( 0x4UL << RCC_PLL2CFR_PLL2Q_Pos )
#define RCC_PLL2CFR_PLL2Q_3                                 ( 0x8UL << RCC_PLL2CFR_PLL2Q_Pos )

#define RCC_PLL2CFR_PLL2P_Pos                               ( 20U )
#define RCC_PLL2CFR_PLL2P_Msk                               ( 0x3UL << RCC_PLL2CFR_PLL2P_Pos )
#define RCC_PLL2CFR_PLL2P                                   ( RCC_PLL2CFR_PLL2P_Msk )
#define RCC_PLL2CFR_PLL2P_0                                 ( 0x1UL << RCC_PLL2CFR_PLL2P_Pos )
#define RCC_PLL2CFR_PLL2P_1                                 ( 0x2UL << RCC_PLL2CFR_PLL2P_Pos )

#define RCC_PLL2CFR_PLL2N_Pos                               ( 12U )
#define RCC_PLL2CFR_PLL2N_Msk                               ( 0x3fUL << RCC_PLL2CFR_PLL2N_Pos )
#define RCC_PLL2CFR_PLL2N                                   ( RCC_PLL2CFR_PLL2N_Msk )
#define RCC_PLL2CFR_PLL2N_0                                 ( 0x1UL << RCC_PLL2CFR_PLL2N_Pos )
#define RCC_PLL2CFR_PLL2N_1                                 ( 0x2UL << RCC_PLL2CFR_PLL2N_Pos )
#define RCC_PLL2CFR_PLL2N_2                                 ( 0x4UL << RCC_PLL2CFR_PLL2N_Pos )
#define RCC_PLL2CFR_PLL2N_3                                 ( 0x8UL << RCC_PLL2CFR_PLL2N_Pos )
#define RCC_PLL2CFR_PLL2N_4                                 ( 0x10UL << RCC_PLL2CFR_PLL2N_Pos )
#define RCC_PLL2CFR_PLL2N_5                                 ( 0x20UL << RCC_PLL2CFR_PLL2N_Pos )

#define RCC_PLL2CFR_PLL2F_Pos                               ( 0U )
#define RCC_PLL2CFR_PLL2F_Msk                               ( 0x1ffUL << RCC_PLL2CFR_PLL2F_Pos )
#define RCC_PLL2CFR_PLL2F                                   ( RCC_PLL2CFR_PLL2F_Msk )


/***************  Bits definition for RCC_PLL2SCR  **********************/

#define RCC_PLL2SCR_PLL2SSCSTP_Pos                             ( 17U )
#define RCC_PLL2SCR_PLL2SSCSTP_Msk                             ( 0x7fffUL << RCC_PLL2SCR_PLL2SSCSTP_Pos )
#define RCC_PLL2SCR_PLL2SSCSTP                                 ( RCC_PLL2SCR_PLL2SSCSTP_Msk )

#define RCC_PLL2SCR_PLL2SSCPER_Pos                             ( 4U )
#define RCC_PLL2SCR_PLL2SSCPER_Msk                             ( 0x1fffUL << RCC_PLL2SCR_PLL2SSCPER_Pos )
#define RCC_PLL2SCR_PLL2SSCPER                                 ( RCC_PLL2SCR_PLL2SSCPER_Msk )

#define RCC_PLL2SCR_PLL2SSCMD_Pos                              ( 1U )
#define RCC_PLL2SCR_PLL2SSCMD_Msk                              ( 0x1UL << RCC_PLL2SCR_PLL2SSCMD_Pos )
#define RCC_PLL2SCR_PLL2SSCMD                                  ( RCC_PLL2SCR_PLL2SSCMD_Msk )

#define RCC_PLL2SCR_PLL2SSCEN_Pos                              ( 0U )
#define RCC_PLL2SCR_PLL2SSCEN_Msk                              ( 0x1UL << RCC_PLL2SCR_PLL2SSCEN_Pos )
#define RCC_PLL2SCR_PLL2SSCEN                                  ( RCC_PLL2SCR_PLL2SSCEN_Msk )


/***************  Bits definition for RCC_PLL3CR  **********************/

#define RCC_PLL3CR_PLL3LOCKSEL_Pos                         ( 31U )
#define RCC_PLL3CR_PLL3LOCKSEL_Msk                         ( 0x1UL << RCC_PLL3CR_PLL3LOCKSEL_Pos )
#define RCC_PLL3CR_PLL3LOCKSEL                             ( RCC_PLL3CR_PLL3LOCKSEL_Msk )

#define RCC_PLL3CR_PLL3FREERUN_Pos                         ( 30U )
#define RCC_PLL3CR_PLL3FREERUN_Msk                         ( 0x1UL << RCC_PLL3CR_PLL3FREERUN_Pos )
#define RCC_PLL3CR_PLL3FREERUN                             ( RCC_PLL3CR_PLL3FREERUN_Msk )

#define RCC_PLL3CR_PLL3LOCK_Pos                             ( 29U )
#define RCC_PLL3CR_PLL3LOCK_Msk                             ( 0x1UL << RCC_PLL3CR_PLL3LOCK_Pos )
#define RCC_PLL3CR_PLL3LOCK                                 ( RCC_PLL3CR_PLL3LOCK_Msk )

#define RCC_PLL3CR_PLL3LOCKDLY_Pos                         ( 23U )
#define RCC_PLL3CR_PLL3LOCKDLY_Msk                         ( 0x3fUL << RCC_PLL3CR_PLL3LOCKDLY_Pos )
#define RCC_PLL3CR_PLL3LOCKDLY                             ( RCC_PLL3CR_PLL3LOCKDLY_Msk )
#define RCC_PLL3CR_PLL3LOCKDLY_0                           ( 0x1UL << RCC_PLL3CR_PLL3LOCKDLY_Pos )
#define RCC_PLL3CR_PLL3LOCKDLY_1                           ( 0x2UL << RCC_PLL3CR_PLL3LOCKDLY_Pos )
#define RCC_PLL3CR_PLL3LOCKDLY_2                           ( 0x4UL << RCC_PLL3CR_PLL3LOCKDLY_Pos )
#define RCC_PLL3CR_PLL3LOCKDLY_3                           ( 0x8UL << RCC_PLL3CR_PLL3LOCKDLY_Pos )
#define RCC_PLL3CR_PLL3LOCKDLY_4                           ( 0x10UL << RCC_PLL3CR_PLL3LOCKDLY_Pos )
#define RCC_PLL3CR_PLL3LOCKDLY_5                           ( 0x20UL << RCC_PLL3CR_PLL3LOCKDLY_Pos )

#define RCC_PLL3CR_PLL3UPDATEEN_Pos                        ( 22U )
#define RCC_PLL3CR_PLL3UPDATEEN_Msk                        ( 0x1UL << RCC_PLL3CR_PLL3UPDATEEN_Pos )
#define RCC_PLL3CR_PLL3UPDATEEN                            ( RCC_PLL3CR_PLL3UPDATEEN_Msk )

#define RCC_PLL3CR_PLL3SLEEP_Pos                            ( 21U )
#define RCC_PLL3CR_PLL3SLEEP_Msk                            ( 0x1UL << RCC_PLL3CR_PLL3SLEEP_Pos )
#define RCC_PLL3CR_PLL3SLEEP                                ( RCC_PLL3CR_PLL3SLEEP_Msk )

#define RCC_PLL3CR_PLL3QCLKEN_Pos                          ( 5U )
#define RCC_PLL3CR_PLL3QCLKEN_Msk                          ( 0x1UL << RCC_PLL3CR_PLL3QCLKEN_Pos )
#define RCC_PLL3CR_PLL3QCLKEN                              ( RCC_PLL3CR_PLL3QCLKEN_Msk )

#define RCC_PLL3CR_PLL3PCLKEN_Pos                          ( 4U )
#define RCC_PLL3CR_PLL3PCLKEN_Msk                          ( 0x1UL << RCC_PLL3CR_PLL3PCLKEN_Pos )
#define RCC_PLL3CR_PLL3PCLKEN                              ( RCC_PLL3CR_PLL3PCLKEN_Msk )

#define RCC_PLL3CR_PLL3SRCSEL_Pos                          ( 1U )
#define RCC_PLL3CR_PLL3SRCSEL_Msk                          ( 0x1UL << RCC_PLL3CR_PLL3SRCSEL_Pos )
#define RCC_PLL3CR_PLL3SRCSEL                              ( RCC_PLL3CR_PLL3SRCSEL_Msk )

#define RCC_PLL3CR_PLL3EN_Pos                               ( 0U )
#define RCC_PLL3CR_PLL3EN_Msk                               ( 0x1UL << RCC_PLL3CR_PLL3EN_Pos )
#define RCC_PLL3CR_PLL3EN                                   ( RCC_PLL3CR_PLL3EN_Msk )


/***************  Bits definition for RCC_PLL3CFR  **********************/

#define RCC_PLL3CFR_PLL3Q_Pos                               ( 24U )
#define RCC_PLL3CFR_PLL3Q_Msk                               ( 0x3UL << RCC_PLL3CFR_PLL3Q_Pos )
#define RCC_PLL3CFR_PLL3Q                                   ( RCC_PLL3CFR_PLL3Q_Msk )
#define RCC_PLL3CFR_PLL3Q_0                                 ( 0x1UL << RCC_PLL3CFR_PLL3Q_Pos )
#define RCC_PLL3CFR_PLL3Q_1                                 ( 0x2UL << RCC_PLL3CFR_PLL3Q_Pos )

#define RCC_PLL3CFR_PLL3P_Pos                               ( 20U )
#define RCC_PLL3CFR_PLL3P_Msk                               ( 0x3UL << RCC_PLL3CFR_PLL3P_Pos )
#define RCC_PLL3CFR_PLL3P                                   ( RCC_PLL3CFR_PLL3P_Msk )
#define RCC_PLL3CFR_PLL3P_0                                 ( 0x1UL << RCC_PLL3CFR_PLL3P_Pos )
#define RCC_PLL3CFR_PLL3P_1                                 ( 0x2UL << RCC_PLL3CFR_PLL3P_Pos )

#define RCC_PLL3CFR_PLL3N_Pos                               ( 12U )
#define RCC_PLL3CFR_PLL3N_Msk                               ( 0x3fUL << RCC_PLL3CFR_PLL3N_Pos )
#define RCC_PLL3CFR_PLL3N                                   ( RCC_PLL3CFR_PLL3N_Msk )
#define RCC_PLL3CFR_PLL3N_0                                 ( 0x1UL << RCC_PLL3CFR_PLL3N_Pos )
#define RCC_PLL3CFR_PLL3N_1                                 ( 0x2UL << RCC_PLL3CFR_PLL3N_Pos )

#define RCC_PLL3CFR_PLL3F_Pos                               ( 0U )
#define RCC_PLL3CFR_PLL3F_Msk                               ( 0x7fUL << RCC_PLL3CFR_PLL3F_Pos )
#define RCC_PLL3CFR_PLL3F                                   ( RCC_PLL3CFR_PLL3F_Msk )
#define RCC_PLL3CFR_PLL3F_0                                 ( 0x01UL << RCC_PLL3CFR_PLL3F_Pos )
#define RCC_PLL3CFR_PLL3F_1                                 ( 0x02UL << RCC_PLL3CFR_PLL3F_Pos )
#define RCC_PLL3CFR_PLL3F_2                                 ( 0x04UL << RCC_PLL3CFR_PLL3F_Pos )
#define RCC_PLL3CFR_PLL3F_3                                 ( 0x08UL << RCC_PLL3CFR_PLL3F_Pos )
#define RCC_PLL3CFR_PLL3F_4                                 ( 0x10UL << RCC_PLL3CFR_PLL3F_Pos )
#define RCC_PLL3CFR_PLL3F_5                                 ( 0x20UL << RCC_PLL3CFR_PLL3F_Pos )
#define RCC_PLL3CFR_PLL3F_6                                 ( 0x40UL << RCC_PLL3CFR_PLL3F_Pos )

/***************  Bits definition for RCC_CLKOCR  **********************/

#define RCC_CLKOCR_MCO2EN_Pos                           ( 31U )
#define RCC_CLKOCR_MCO2EN_Msk                           ( 0x1UL << RCC_CLKOCR_MCO2EN_Pos )
#define RCC_CLKOCR_MCO2EN                               ( RCC_CLKOCR_MCO2EN_Msk )

#define RCC_CLKOCR_MCO2POL_Pos                          ( 30U )
#define RCC_CLKOCR_MCO2POL_Msk                          ( 0x1UL << RCC_CLKOCR_MCO2POL_Pos )
#define RCC_CLKOCR_MCO2POL                              ( RCC_CLKOCR_MCO2POL_Msk )

#define RCC_CLKOCR_MCO2DIV_Pos                          ( 24U )
#define RCC_CLKOCR_MCO2DIV_Msk                          ( 0x3fUL << RCC_CLKOCR_MCO2DIV_Pos )
#define RCC_CLKOCR_MCO2DIV                              ( RCC_CLKOCR_MCO2DIV_Msk )
#define RCC_CLKOCR_MCO2DIV_0                            ( 0x1UL << RCC_CLKOCR_MCO2DIV_Pos )
#define RCC_CLKOCR_MCO2DIV_1                            ( 0x2UL << RCC_CLKOCR_MCO2DIV_Pos )
#define RCC_CLKOCR_MCO2DIV_2                            ( 0x4UL << RCC_CLKOCR_MCO2DIV_Pos )
#define RCC_CLKOCR_MCO2DIV_3                            ( 0x8UL << RCC_CLKOCR_MCO2DIV_Pos )
#define RCC_CLKOCR_MCO2DIV_4                            ( 0x10UL << RCC_CLKOCR_MCO2DIV_Pos )
#define RCC_CLKOCR_MCO2DIV_5                            ( 0x20UL << RCC_CLKOCR_MCO2DIV_Pos )

#define RCC_CLKOCR_MCO1EN_Pos                           ( 23U )
#define RCC_CLKOCR_MCO1EN_Msk                           ( 0x1UL << RCC_CLKOCR_MCO1EN_Pos )
#define RCC_CLKOCR_MCO1EN                               ( RCC_CLKOCR_MCO1EN_Msk )

#define RCC_CLKOCR_MCO1POL_Pos                          ( 22U )
#define RCC_CLKOCR_MCO1POL_Msk                          ( 0x1UL << RCC_CLKOCR_MCO1POL_Pos )
#define RCC_CLKOCR_MCO1POL                              ( RCC_CLKOCR_MCO1POL_Msk )

#define RCC_CLKOCR_MCO1DIV_Pos                          ( 6U )
#define RCC_CLKOCR_MCO1DIV_Msk                          ( 0xffffUL << RCC_CLKOCR_MCO1DIV_Pos )
#define RCC_CLKOCR_MCO1DIV                              ( RCC_CLKOCR_MCO1DIV_Msk )

#define RCC_CLKOCR_MCO1SEL_Pos                          ( 5U )
#define RCC_CLKOCR_MCO1SEL_Msk                          ( 0x1UL << RCC_CLKOCR_MCO1SEL_Pos )
#define RCC_CLKOCR_MCO1SEL                              ( RCC_CLKOCR_MCO1SEL_Msk )

#define RCC_CLKOCR_MCOCLKS_Pos                          ( 0U )
#define RCC_CLKOCR_MCOCLKS_Msk                          ( 0x1fUL << RCC_CLKOCR_MCOCLKS_Pos )
#define RCC_CLKOCR_MCOCLKS                              ( RCC_CLKOCR_MCOCLKS_Msk )
#define RCC_CLKOCR_MCOCLKS_0                            ( 0x01UL << RCC_CLKOCR_MCOCLKS_Pos )
#define RCC_CLKOCR_MCOCLKS_1                            ( 0x02UL << RCC_CLKOCR_MCOCLKS_Pos )
#define RCC_CLKOCR_MCOCLKS_2                            ( 0x04UL << RCC_CLKOCR_MCOCLKS_Pos )
#define RCC_CLKOCR_MCOCLKS_3                            ( 0x08UL << RCC_CLKOCR_MCOCLKS_Pos )
#define RCC_CLKOCR_MCOCLKS_4                            ( 0x10UL << RCC_CLKOCR_MCOCLKS_Pos )


/***************  Bits definition for RCC_DCKCFG  **********************/

#define RCC_DCKCFG_LCDDIV_Pos                              ( 0U )
#define RCC_DCKCFG_LCDDIV_Msk                              ( 0x3UL << RCC_DCKCFG_LCDDIV_Pos )
#define RCC_DCKCFG_LCDDIV                                  ( RCC_DCKCFG_LCDDIV_Msk )
#define RCC_DCKCFG_LCDDIV_0                                ( 0x1UL << RCC_DCKCFG_LCDDIV_Pos )
#define RCC_DCKCFG_LCDDIV_1                                ( 0x2UL << RCC_DCKCFG_LCDDIV_Pos )


/***************  Bits definition for RCC_STDBYCTRL  **********************/

#define RCC_STDBYCTRL_STDBYRST_Pos                         ( 23U )
#define RCC_STDBYCTRL_STDBYRST_Msk                         ( 0x1UL << RCC_STDBYCTRL_STDBYRST_Pos )
#define RCC_STDBYCTRL_STDBYRST                             ( RCC_STDBYCTRL_STDBYRST_Msk )

#define RCC_STDBYCTRL_RTCEN_Pos                            ( 22U )
#define RCC_STDBYCTRL_RTCEN_Msk                            ( 0x1UL << RCC_STDBYCTRL_RTCEN_Pos )
#define RCC_STDBYCTRL_RTCEN                                ( RCC_STDBYCTRL_RTCEN_Msk )

#define RCC_STDBYCTRL_RTCSEL_Pos                           ( 20U )
#define RCC_STDBYCTRL_RTCSEL_Msk                           ( 0x3UL << RCC_STDBYCTRL_RTCSEL_Pos )
#define RCC_STDBYCTRL_RTCSEL                               ( RCC_STDBYCTRL_RTCSEL_Msk )
#define RCC_STDBYCTRL_RTCSEL_0                             ( 0x1UL << RCC_STDBYCTRL_RTCSEL_Pos )
#define RCC_STDBYCTRL_RTCSEL_1                             ( 0x2UL << RCC_STDBYCTRL_RTCSEL_Pos )

#define RCC_STDBYCTRL_RCLDIS_Pos                         ( 16U )
#define RCC_STDBYCTRL_RCLDIS_Msk                         ( 0xFUL << RCC_STDBYCTRL_RCLDIS_Pos )
#define RCC_STDBYCTRL_RCLDIS                             ( RCC_STDBYCTRL_RCLDIS_Msk )
#define RCC_STDBYCTRL_RCLDIS_0                           ( 0x1UL << RCC_STDBYCTRL_RCLDIS_Pos )
#define RCC_STDBYCTRL_RCLDIS_1                           ( 0x2UL << RCC_STDBYCTRL_RCLDIS_Pos )
#define RCC_STDBYCTRL_RCLDIS_2                           ( 0x4UL << RCC_STDBYCTRL_RCLDIS_Pos )
#define RCC_STDBYCTRL_RCLDIS_3                           ( 0x8UL << RCC_STDBYCTRL_RCLDIS_Pos )

#define RCC_STDBYCTRL_RCLTRIM_Pos                       ( 10U )
#define RCC_STDBYCTRL_RCLTRIM_Msk                       ( 0x3fUL << RCC_STDBYCTRL_RCLTRIM_Pos )
#define RCC_STDBYCTRL_RCLTRIM                           ( RCC_STDBYCTRL_RCLTRIM_Msk )
#define RCC_STDBYCTRL_RCLTRIM_0                         ( 0x1UL << RCC_STDBYCTRL_RCLTRIM_Pos )
#define RCC_STDBYCTRL_RCLTRIM_1                         ( 0x2UL << RCC_STDBYCTRL_RCLTRIM_Pos )
#define RCC_STDBYCTRL_RCLTRIM_2                         ( 0x4UL << RCC_STDBYCTRL_RCLTRIM_Pos )
#define RCC_STDBYCTRL_RCLTRIM_3                         ( 0x8UL << RCC_STDBYCTRL_RCLTRIM_Pos )
#define RCC_STDBYCTRL_RCLTRIM_4                         ( 0x10UL << RCC_STDBYCTRL_RCLTRIM_Pos )
#define RCC_STDBYCTRL_RCLTRIM_5                         ( 0x20UL << RCC_STDBYCTRL_RCLTRIM_Pos )

#define RCC_STDBYCTRL_RCLRDY_Pos                         ( 9U )
#define RCC_STDBYCTRL_RCLRDY_Msk                         ( 0x1UL << RCC_STDBYCTRL_RCLRDY_Pos )
#define RCC_STDBYCTRL_RCLRDY                             ( RCC_STDBYCTRL_RCLRDY_Msk )

#define RCC_STDBYCTRL_RCLEN_Pos                           ( 8U )
#define RCC_STDBYCTRL_RCLEN_Msk                           ( 0x1UL << RCC_STDBYCTRL_RCLEN_Pos )
#define RCC_STDBYCTRL_RCLEN                               ( RCC_STDBYCTRL_RCLEN_Msk )

#define RCC_STDBYCTRL_XTLSDEN_Pos                          ( 6U )
#define RCC_STDBYCTRL_XTLSDEN_Msk                          ( 0x1UL << RCC_STDBYCTRL_XTLSDEN_Pos )
#define RCC_STDBYCTRL_XTLSDEN                              ( RCC_STDBYCTRL_XTLSDEN_Msk )

#define RCC_STDBYCTRL_XTLDRV_Pos                           ( 3U )
#define RCC_STDBYCTRL_XTLDRV_Msk                           ( 0x7UL << RCC_STDBYCTRL_XTLDRV_Pos )
#define RCC_STDBYCTRL_XTLDRV                               ( RCC_STDBYCTRL_XTLDRV_Msk )
#define RCC_STDBYCTRL_XTLDRV_0                             ( 0x1UL << RCC_STDBYCTRL_XTLDRV_Pos )
#define RCC_STDBYCTRL_XTLDRV_1                             ( 0x2UL << RCC_STDBYCTRL_XTLDRV_Pos )
#define RCC_STDBYCTRL_XTLDRV_2                             ( 0x4UL << RCC_STDBYCTRL_XTLDRV_Pos )

#define RCC_STDBYCTRL_XTLBYP_Pos                           ( 2U )
#define RCC_STDBYCTRL_XTLBYP_Msk                           ( 0x1UL << RCC_STDBYCTRL_XTLBYP_Pos )
#define RCC_STDBYCTRL_XTLBYP                               ( RCC_STDBYCTRL_XTLBYP_Msk )

#define RCC_STDBYCTRL_XTLRDY_Pos                           ( 1U )
#define RCC_STDBYCTRL_XTLRDY_Msk                           ( 0x1UL << RCC_STDBYCTRL_XTLRDY_Pos )
#define RCC_STDBYCTRL_XTLRDY                               ( RCC_STDBYCTRL_XTLRDY_Msk )

#define RCC_STDBYCTRL_XTLEN_Pos                            ( 0U )
#define RCC_STDBYCTRL_XTLEN_Msk                            ( 0x1UL << RCC_STDBYCTRL_XTLEN_Pos )
#define RCC_STDBYCTRL_XTLEN                                ( RCC_STDBYCTRL_XTLEN_Msk )


/***************  Bits definition for GPIO_MD  **********************/

#define GPIO_MD_MD_15_Pos                                   ( 30U )
#define GPIO_MD_MD_15_Msk                                   ( 0x3UL << GPIO_MD_MD_15_Pos )
#define GPIO_MD_MD_15                                       ( GPIO_MD_MD_15_Msk )
#define GPIO_MD_MD_15_0                                     ( 0x1UL << GPIO_MD_MD_15_Pos )
#define GPIO_MD_MD_15_1                                     ( 0x2UL << GPIO_MD_MD_15_Pos )

#define GPIO_MD_MD_14_Pos                                   ( 28U )
#define GPIO_MD_MD_14_Msk                                   ( 0x3UL << GPIO_MD_MD_14_Pos )
#define GPIO_MD_MD_14                                       ( GPIO_MD_MD_14_Msk )
#define GPIO_MD_MD_14_0                                     ( 0x1UL << GPIO_MD_MD_14_Pos )
#define GPIO_MD_MD_14_1                                     ( 0x2UL << GPIO_MD_MD_14_Pos )

#define GPIO_MD_MD_13_Pos                                   ( 26U )
#define GPIO_MD_MD_13_Msk                                   ( 0x3UL << GPIO_MD_MD_13_Pos )
#define GPIO_MD_MD_13                                       ( GPIO_MD_MD_13_Msk )
#define GPIO_MD_MD_13_0                                     ( 0x1UL << GPIO_MD_MD_13_Pos )
#define GPIO_MD_MD_13_1                                     ( 0x2UL << GPIO_MD_MD_13_Pos )

#define GPIO_MD_MD_12_Pos                                   ( 24U )
#define GPIO_MD_MD_12_Msk                                   ( 0x3UL << GPIO_MD_MD_12_Pos )
#define GPIO_MD_MD_12                                       ( GPIO_MD_MD_12_Msk )
#define GPIO_MD_MD_12_0                                     ( 0x1UL << GPIO_MD_MD_12_Pos )
#define GPIO_MD_MD_12_1                                     ( 0x2UL << GPIO_MD_MD_12_Pos )

#define GPIO_MD_MD_11_Pos                                   ( 22U )
#define GPIO_MD_MD_11_Msk                                   ( 0x3UL << GPIO_MD_MD_11_Pos )
#define GPIO_MD_MD_11                                       ( GPIO_MD_MD_11_Msk )
#define GPIO_MD_MD_11_0                                     ( 0x1UL << GPIO_MD_MD_11_Pos )
#define GPIO_MD_MD_11_1                                     ( 0x2UL << GPIO_MD_MD_11_Pos )

#define GPIO_MD_MD_10_Pos                                   ( 20U )
#define GPIO_MD_MD_10_Msk                                   ( 0x3UL << GPIO_MD_MD_10_Pos )
#define GPIO_MD_MD_10                                       ( GPIO_MD_MD_10_Msk )
#define GPIO_MD_MD_10_0                                     ( 0x1UL << GPIO_MD_MD_10_Pos )
#define GPIO_MD_MD_10_1                                     ( 0x2UL << GPIO_MD_MD_10_Pos )

#define GPIO_MD_MD_9_Pos                                    ( 18U )
#define GPIO_MD_MD_9_Msk                                    ( 0x3UL << GPIO_MD_MD_9_Pos )
#define GPIO_MD_MD_9                                        ( GPIO_MD_MD_9_Msk )
#define GPIO_MD_MD_9_0                                      ( 0x1UL << GPIO_MD_MD_9_Pos )
#define GPIO_MD_MD_9_1                                      ( 0x2UL << GPIO_MD_MD_9_Pos )

#define GPIO_MD_MD_8_Pos                                    ( 16U )
#define GPIO_MD_MD_8_Msk                                    ( 0x3UL << GPIO_MD_MD_8_Pos )
#define GPIO_MD_MD_8                                        ( GPIO_MD_MD_8_Msk )
#define GPIO_MD_MD_8_0                                      ( 0x1UL << GPIO_MD_MD_8_Pos )
#define GPIO_MD_MD_8_1                                      ( 0x2UL << GPIO_MD_MD_8_Pos )

#define GPIO_MD_MD_7_Pos                                    ( 14U )
#define GPIO_MD_MD_7_Msk                                    ( 0x3UL << GPIO_MD_MD_7_Pos )
#define GPIO_MD_MD_7                                        ( GPIO_MD_MD_7_Msk )
#define GPIO_MD_MD_7_0                                      ( 0x1UL << GPIO_MD_MD_7_Pos )
#define GPIO_MD_MD_7_1                                      ( 0x2UL << GPIO_MD_MD_7_Pos )

#define GPIO_MD_MD_6_Pos                                    ( 12U )
#define GPIO_MD_MD_6_Msk                                    ( 0x3UL << GPIO_MD_MD_6_Pos )
#define GPIO_MD_MD_6                                        ( GPIO_MD_MD_6_Msk )
#define GPIO_MD_MD_6_0                                      ( 0x1UL << GPIO_MD_MD_6_Pos )
#define GPIO_MD_MD_6_1                                      ( 0x2UL << GPIO_MD_MD_6_Pos )

#define GPIO_MD_MD_5_Pos                                    ( 10U )
#define GPIO_MD_MD_5_Msk                                    ( 0x3UL << GPIO_MD_MD_5_Pos )
#define GPIO_MD_MD_5                                        ( GPIO_MD_MD_5_Msk )
#define GPIO_MD_MD_5_0                                      ( 0x1UL << GPIO_MD_MD_5_Pos )
#define GPIO_MD_MD_5_1                                      ( 0x2UL << GPIO_MD_MD_5_Pos )

#define GPIO_MD_MD_4_Pos                                    ( 8U )
#define GPIO_MD_MD_4_Msk                                    ( 0x3UL << GPIO_MD_MD_4_Pos )
#define GPIO_MD_MD_4                                        ( GPIO_MD_MD_4_Msk )
#define GPIO_MD_MD_4_0                                      ( 0x1UL << GPIO_MD_MD_4_Pos )
#define GPIO_MD_MD_4_1                                      ( 0x2UL << GPIO_MD_MD_4_Pos )

#define GPIO_MD_MD_3_Pos                                    ( 6U )
#define GPIO_MD_MD_3_Msk                                    ( 0x3UL << GPIO_MD_MD_3_Pos )
#define GPIO_MD_MD_3                                        ( GPIO_MD_MD_3_Msk )
#define GPIO_MD_MD_3_0                                      ( 0x1UL << GPIO_MD_MD_3_Pos )
#define GPIO_MD_MD_3_1                                      ( 0x2UL << GPIO_MD_MD_3_Pos )

#define GPIO_MD_MD_2_Pos                                    ( 4U )
#define GPIO_MD_MD_2_Msk                                    ( 0x3UL << GPIO_MD_MD_2_Pos )
#define GPIO_MD_MD_2                                        ( GPIO_MD_MD_2_Msk )
#define GPIO_MD_MD_2_0                                      ( 0x1UL << GPIO_MD_MD_2_Pos )
#define GPIO_MD_MD_2_1                                      ( 0x2UL << GPIO_MD_MD_2_Pos )

#define GPIO_MD_MD_1_Pos                                    ( 2U )
#define GPIO_MD_MD_1_Msk                                    ( 0x3UL << GPIO_MD_MD_1_Pos )
#define GPIO_MD_MD_1                                        ( GPIO_MD_MD_1_Msk )
#define GPIO_MD_MD_1_0                                      ( 0x1UL << GPIO_MD_MD_1_Pos )
#define GPIO_MD_MD_1_1                                      ( 0x2UL << GPIO_MD_MD_1_Pos )

#define GPIO_MD_MD_0_Pos                                    ( 0U )
#define GPIO_MD_MD_0_Msk                                    ( 0x3UL << GPIO_MD_MD_0_Pos )
#define GPIO_MD_MD_0                                        ( GPIO_MD_MD_0_Msk )
#define GPIO_MD_MD_0_0                                      ( 0x1UL << GPIO_MD_MD_0_Pos )
#define GPIO_MD_MD_0_1                                      ( 0x2UL << GPIO_MD_MD_0_Pos )


/***************  Bits definition for GPIO_OTYP  **********************/

#define GPIO_OTYP_OTYP15_Pos                                ( 15U )
#define GPIO_OTYP_OTYP15_Msk                                ( 0x1UL << GPIO_OTYP_OTYP15_Pos )
#define GPIO_OTYP_OTYP15                                    ( GPIO_OTYP_OTYP15_Msk )


#define GPIO_OTYP_OTYP14_Pos                                ( 14U )
#define GPIO_OTYP_OTYP14_Msk                                ( 0x1UL << GPIO_OTYP_OTYP14_Pos )
#define GPIO_OTYP_OTYP14                                    ( GPIO_OTYP_OTYP14_Msk )


#define GPIO_OTYP_OTYP13_Pos                                ( 13U )
#define GPIO_OTYP_OTYP13_Msk                                ( 0x1UL << GPIO_OTYP_OTYP13_Pos )
#define GPIO_OTYP_OTYP13                                    ( GPIO_OTYP_OTYP13_Msk )


#define GPIO_OTYP_OTYP12_Pos                                ( 12U )
#define GPIO_OTYP_OTYP12_Msk                                ( 0x1UL << GPIO_OTYP_OTYP12_Pos )
#define GPIO_OTYP_OTYP12                                    ( GPIO_OTYP_OTYP12_Msk )


#define GPIO_OTYP_OTYP11_Pos                                ( 11U )
#define GPIO_OTYP_OTYP11_Msk                                ( 0x1UL << GPIO_OTYP_OTYP11_Pos )
#define GPIO_OTYP_OTYP11                                    ( GPIO_OTYP_OTYP11_Msk )


#define GPIO_OTYP_OTYP10_Pos                                ( 10U )
#define GPIO_OTYP_OTYP10_Msk                                ( 0x1UL << GPIO_OTYP_OTYP10_Pos )
#define GPIO_OTYP_OTYP10                                    ( GPIO_OTYP_OTYP10_Msk )


#define GPIO_OTYP_OTYP9_Pos                                 ( 9U )
#define GPIO_OTYP_OTYP9_Msk                                 ( 0x1UL << GPIO_OTYP_OTYP9_Pos )
#define GPIO_OTYP_OTYP9                                     ( GPIO_OTYP_OTYP9_Msk )


#define GPIO_OTYP_OTYP8_Pos                                 ( 8U )
#define GPIO_OTYP_OTYP8_Msk                                 ( 0x1UL << GPIO_OTYP_OTYP8_Pos )
#define GPIO_OTYP_OTYP8                                     ( GPIO_OTYP_OTYP8_Msk )


#define GPIO_OTYP_OTYP7_Pos                                 ( 7U )
#define GPIO_OTYP_OTYP7_Msk                                 ( 0x1UL << GPIO_OTYP_OTYP7_Pos )
#define GPIO_OTYP_OTYP7                                     ( GPIO_OTYP_OTYP7_Msk )


#define GPIO_OTYP_OTYP6_Pos                                 ( 6U )
#define GPIO_OTYP_OTYP6_Msk                                 ( 0x1UL << GPIO_OTYP_OTYP6_Pos )
#define GPIO_OTYP_OTYP6                                     ( GPIO_OTYP_OTYP6_Msk )


#define GPIO_OTYP_OTYP5_Pos                                 ( 5U )
#define GPIO_OTYP_OTYP5_Msk                                 ( 0x1UL << GPIO_OTYP_OTYP5_Pos )
#define GPIO_OTYP_OTYP5                                     ( GPIO_OTYP_OTYP5_Msk )


#define GPIO_OTYP_OTYP4_Pos                                 ( 4U )
#define GPIO_OTYP_OTYP4_Msk                                 ( 0x1UL << GPIO_OTYP_OTYP4_Pos )
#define GPIO_OTYP_OTYP4                                     ( GPIO_OTYP_OTYP4_Msk )


#define GPIO_OTYP_OTYP3_Pos                                 ( 3U )
#define GPIO_OTYP_OTYP3_Msk                                 ( 0x1UL << GPIO_OTYP_OTYP3_Pos )
#define GPIO_OTYP_OTYP3                                     ( GPIO_OTYP_OTYP3_Msk )


#define GPIO_OTYP_OTYP2_Pos                                 ( 2U )
#define GPIO_OTYP_OTYP2_Msk                                 ( 0x1UL << GPIO_OTYP_OTYP2_Pos )
#define GPIO_OTYP_OTYP2                                     ( GPIO_OTYP_OTYP2_Msk )


#define GPIO_OTYP_OTYP1_Pos                                 ( 1U )
#define GPIO_OTYP_OTYP1_Msk                                 ( 0x1UL << GPIO_OTYP_OTYP1_Pos )
#define GPIO_OTYP_OTYP1                                     ( GPIO_OTYP_OTYP1_Msk )


#define GPIO_OTYP_OTYP0_Pos                                 ( 0U )
#define GPIO_OTYP_OTYP0_Msk                                 ( 0x1UL << GPIO_OTYP_OTYP0_Pos )
#define GPIO_OTYP_OTYP0                                     ( GPIO_OTYP_OTYP0_Msk )



/***************  Bits definition for GPIO_PUPD  **********************/

#define GPIO_PUPD_PUPD_15_Pos                               ( 30U )
#define GPIO_PUPD_PUPD_15_Msk                               ( 0x3UL << GPIO_PUPD_PUPD_15_Pos )
#define GPIO_PUPD_PUPD_15                                   ( GPIO_PUPD_PUPD_15_Msk )
#define GPIO_PUPD_PUPD_15_0                                 ( 0x1UL << GPIO_PUPD_PUPD_15_Pos )
#define GPIO_PUPD_PUPD_15_1                                 ( 0x2UL << GPIO_PUPD_PUPD_15_Pos )

#define GPIO_PUPD_PUPD_14_Pos                               ( 28U )
#define GPIO_PUPD_PUPD_14_Msk                               ( 0x3UL << GPIO_PUPD_PUPD_14_Pos )
#define GPIO_PUPD_PUPD_14                                   ( GPIO_PUPD_PUPD_14_Msk )
#define GPIO_PUPD_PUPD_14_0                                 ( 0x1UL << GPIO_PUPD_PUPD_14_Pos )
#define GPIO_PUPD_PUPD_14_1                                 ( 0x2UL << GPIO_PUPD_PUPD_14_Pos )

#define GPIO_PUPD_PUPD_13_Pos                               ( 26U )
#define GPIO_PUPD_PUPD_13_Msk                               ( 0x3UL << GPIO_PUPD_PUPD_13_Pos )
#define GPIO_PUPD_PUPD_13                                   ( GPIO_PUPD_PUPD_13_Msk )
#define GPIO_PUPD_PUPD_13_0                                 ( 0x1UL << GPIO_PUPD_PUPD_13_Pos )
#define GPIO_PUPD_PUPD_13_1                                 ( 0x2UL << GPIO_PUPD_PUPD_13_Pos )

#define GPIO_PUPD_PUPD_12_Pos                               ( 24U )
#define GPIO_PUPD_PUPD_12_Msk                               ( 0x3UL << GPIO_PUPD_PUPD_12_Pos )
#define GPIO_PUPD_PUPD_12                                   ( GPIO_PUPD_PUPD_12_Msk )
#define GPIO_PUPD_PUPD_12_0                                 ( 0x1UL << GPIO_PUPD_PUPD_12_Pos )
#define GPIO_PUPD_PUPD_12_1                                 ( 0x2UL << GPIO_PUPD_PUPD_12_Pos )

#define GPIO_PUPD_PUPD_11_Pos                               ( 22U )
#define GPIO_PUPD_PUPD_11_Msk                               ( 0x3UL << GPIO_PUPD_PUPD_11_Pos )
#define GPIO_PUPD_PUPD_11                                   ( GPIO_PUPD_PUPD_11_Msk )
#define GPIO_PUPD_PUPD_11_0                                 ( 0x1UL << GPIO_PUPD_PUPD_11_Pos )
#define GPIO_PUPD_PUPD_11_1                                 ( 0x2UL << GPIO_PUPD_PUPD_11_Pos )

#define GPIO_PUPD_PUPD_10_Pos                               ( 20U )
#define GPIO_PUPD_PUPD_10_Msk                               ( 0x3UL << GPIO_PUPD_PUPD_10_Pos )
#define GPIO_PUPD_PUPD_10                                   ( GPIO_PUPD_PUPD_10_Msk )
#define GPIO_PUPD_PUPD_10_0                                 ( 0x1UL << GPIO_PUPD_PUPD_10_Pos )
#define GPIO_PUPD_PUPD_10_1                                 ( 0x2UL << GPIO_PUPD_PUPD_10_Pos )

#define GPIO_PUPD_PUPD_9_Pos                                ( 18U )
#define GPIO_PUPD_PUPD_9_Msk                                ( 0x3UL << GPIO_PUPD_PUPD_9_Pos )
#define GPIO_PUPD_PUPD_9                                    ( GPIO_PUPD_PUPD_9_Msk )
#define GPIO_PUPD_PUPD_9_0                                  ( 0x1UL << GPIO_PUPD_PUPD_9_Pos )
#define GPIO_PUPD_PUPD_9_1                                  ( 0x2UL << GPIO_PUPD_PUPD_9_Pos )

#define GPIO_PUPD_PUPD_8_Pos                                ( 16U )
#define GPIO_PUPD_PUPD_8_Msk                                ( 0x3UL << GPIO_PUPD_PUPD_8_Pos )
#define GPIO_PUPD_PUPD_8                                    ( GPIO_PUPD_PUPD_8_Msk )
#define GPIO_PUPD_PUPD_8_0                                  ( 0x1UL << GPIO_PUPD_PUPD_8_Pos )
#define GPIO_PUPD_PUPD_8_1                                  ( 0x2UL << GPIO_PUPD_PUPD_8_Pos )

#define GPIO_PUPD_PUPD_7_Pos                                ( 14U )
#define GPIO_PUPD_PUPD_7_Msk                                ( 0x3UL << GPIO_PUPD_PUPD_7_Pos )
#define GPIO_PUPD_PUPD_7                                    ( GPIO_PUPD_PUPD_7_Msk )
#define GPIO_PUPD_PUPD_7_0                                  ( 0x1UL << GPIO_PUPD_PUPD_7_Pos )
#define GPIO_PUPD_PUPD_7_1                                  ( 0x2UL << GPIO_PUPD_PUPD_7_Pos )

#define GPIO_PUPD_PUPD_6_Pos                                ( 12U )
#define GPIO_PUPD_PUPD_6_Msk                                ( 0x3UL << GPIO_PUPD_PUPD_6_Pos )
#define GPIO_PUPD_PUPD_6                                    ( GPIO_PUPD_PUPD_6_Msk )
#define GPIO_PUPD_PUPD_6_0                                  ( 0x1UL << GPIO_PUPD_PUPD_6_Pos )
#define GPIO_PUPD_PUPD_6_1                                  ( 0x2UL << GPIO_PUPD_PUPD_6_Pos )

#define GPIO_PUPD_PUPD_5_Pos                                ( 10U )
#define GPIO_PUPD_PUPD_5_Msk                                ( 0x3UL << GPIO_PUPD_PUPD_5_Pos )
#define GPIO_PUPD_PUPD_5                                    ( GPIO_PUPD_PUPD_5_Msk )
#define GPIO_PUPD_PUPD_5_0                                  ( 0x1UL << GPIO_PUPD_PUPD_5_Pos )
#define GPIO_PUPD_PUPD_5_1                                  ( 0x2UL << GPIO_PUPD_PUPD_5_Pos )

#define GPIO_PUPD_PUPD_4_Pos                                ( 8U )
#define GPIO_PUPD_PUPD_4_Msk                                ( 0x3UL << GPIO_PUPD_PUPD_4_Pos )
#define GPIO_PUPD_PUPD_4                                    ( GPIO_PUPD_PUPD_4_Msk )
#define GPIO_PUPD_PUPD_4_0                                  ( 0x1UL << GPIO_PUPD_PUPD_4_Pos )
#define GPIO_PUPD_PUPD_4_1                                  ( 0x2UL << GPIO_PUPD_PUPD_4_Pos )

#define GPIO_PUPD_PUPD_3_Pos                                ( 6U )
#define GPIO_PUPD_PUPD_3_Msk                                ( 0x3UL << GPIO_PUPD_PUPD_3_Pos )
#define GPIO_PUPD_PUPD_3                                    ( GPIO_PUPD_PUPD_3_Msk )
#define GPIO_PUPD_PUPD_3_0                                  ( 0x1UL << GPIO_PUPD_PUPD_3_Pos )
#define GPIO_PUPD_PUPD_3_1                                  ( 0x2UL << GPIO_PUPD_PUPD_3_Pos )

#define GPIO_PUPD_PUPD_2_Pos                                ( 4U )
#define GPIO_PUPD_PUPD_2_Msk                                ( 0x3UL << GPIO_PUPD_PUPD_2_Pos )
#define GPIO_PUPD_PUPD_2                                    ( GPIO_PUPD_PUPD_2_Msk )
#define GPIO_PUPD_PUPD_2_0                                  ( 0x1UL << GPIO_PUPD_PUPD_2_Pos )
#define GPIO_PUPD_PUPD_2_1                                  ( 0x2UL << GPIO_PUPD_PUPD_2_Pos )

#define GPIO_PUPD_PUPD_1_Pos                                ( 2U )
#define GPIO_PUPD_PUPD_1_Msk                                ( 0x3UL << GPIO_PUPD_PUPD_1_Pos )
#define GPIO_PUPD_PUPD_1                                    ( GPIO_PUPD_PUPD_1_Msk )
#define GPIO_PUPD_PUPD_1_0                                  ( 0x1UL << GPIO_PUPD_PUPD_1_Pos )
#define GPIO_PUPD_PUPD_1_1                                  ( 0x2UL << GPIO_PUPD_PUPD_1_Pos )

#define GPIO_PUPD_PUPD_0_Pos                                ( 0U )
#define GPIO_PUPD_PUPD_0_Msk                                ( 0x3UL << GPIO_PUPD_PUPD_0_Pos )
#define GPIO_PUPD_PUPD_0                                    ( GPIO_PUPD_PUPD_0_Msk )
#define GPIO_PUPD_PUPD_0_0                                  ( 0x1UL << GPIO_PUPD_PUPD_0_Pos )
#define GPIO_PUPD_PUPD_0_1                                  ( 0x2UL << GPIO_PUPD_PUPD_0_Pos )


/***************  Bits definition for GPIO_IDATA  **********************/

#define GPIO_IDATA_GPIO_IDATA15_Pos                         ( 15U )
#define GPIO_IDATA_GPIO_IDATA15_Msk                         ( 0x1UL << GPIO_IDATA_GPIO_IDATA15_Pos )
#define GPIO_IDATA_GPIO_IDATA15                             ( GPIO_IDATA_GPIO_IDATA15_Msk )


#define GPIO_IDATA_GPIO_IDATA14_Pos                         ( 14U )
#define GPIO_IDATA_GPIO_IDATA14_Msk                         ( 0x1UL << GPIO_IDATA_GPIO_IDATA14_Pos )
#define GPIO_IDATA_GPIO_IDATA14                             ( GPIO_IDATA_GPIO_IDATA14_Msk )


#define GPIO_IDATA_GPIO_IDATA13_Pos                         ( 13U )
#define GPIO_IDATA_GPIO_IDATA13_Msk                         ( 0x1UL << GPIO_IDATA_GPIO_IDATA13_Pos )
#define GPIO_IDATA_GPIO_IDATA13                             ( GPIO_IDATA_GPIO_IDATA13_Msk )


#define GPIO_IDATA_GPIO_IDATA12_Pos                         ( 12U )
#define GPIO_IDATA_GPIO_IDATA12_Msk                         ( 0x1UL << GPIO_IDATA_GPIO_IDATA12_Pos )
#define GPIO_IDATA_GPIO_IDATA12                             ( GPIO_IDATA_GPIO_IDATA12_Msk )


#define GPIO_IDATA_GPIO_IDATA11_Pos                         ( 11U )
#define GPIO_IDATA_GPIO_IDATA11_Msk                         ( 0x1UL << GPIO_IDATA_GPIO_IDATA11_Pos )
#define GPIO_IDATA_GPIO_IDATA11                             ( GPIO_IDATA_GPIO_IDATA11_Msk )


#define GPIO_IDATA_GPIO_IDATA10_Pos                         ( 10U )
#define GPIO_IDATA_GPIO_IDATA10_Msk                         ( 0x1UL << GPIO_IDATA_GPIO_IDATA10_Pos )
#define GPIO_IDATA_GPIO_IDATA10                             ( GPIO_IDATA_GPIO_IDATA10_Msk )


#define GPIO_IDATA_GPIO_IDATA9_Pos                          ( 9U )
#define GPIO_IDATA_GPIO_IDATA9_Msk                          ( 0x1UL << GPIO_IDATA_GPIO_IDATA9_Pos )
#define GPIO_IDATA_GPIO_IDATA9                              ( GPIO_IDATA_GPIO_IDATA9_Msk )


#define GPIO_IDATA_GPIO_IDATA8_Pos                          ( 8U )
#define GPIO_IDATA_GPIO_IDATA8_Msk                          ( 0x1UL << GPIO_IDATA_GPIO_IDATA8_Pos )
#define GPIO_IDATA_GPIO_IDATA8                              ( GPIO_IDATA_GPIO_IDATA8_Msk )


#define GPIO_IDATA_GPIO_IDATA7_Pos                          ( 7U )
#define GPIO_IDATA_GPIO_IDATA7_Msk                          ( 0x1UL << GPIO_IDATA_GPIO_IDATA7_Pos )
#define GPIO_IDATA_GPIO_IDATA7                              ( GPIO_IDATA_GPIO_IDATA7_Msk )


#define GPIO_IDATA_GPIO_IDATA6_Pos                          ( 6U )
#define GPIO_IDATA_GPIO_IDATA6_Msk                          ( 0x1UL << GPIO_IDATA_GPIO_IDATA6_Pos )
#define GPIO_IDATA_GPIO_IDATA6                              ( GPIO_IDATA_GPIO_IDATA6_Msk )


#define GPIO_IDATA_GPIO_IDATA5_Pos                          ( 5U )
#define GPIO_IDATA_GPIO_IDATA5_Msk                          ( 0x1UL << GPIO_IDATA_GPIO_IDATA5_Pos )
#define GPIO_IDATA_GPIO_IDATA5                              ( GPIO_IDATA_GPIO_IDATA5_Msk )


#define GPIO_IDATA_GPIO_IDATA4_Pos                          ( 4U )
#define GPIO_IDATA_GPIO_IDATA4_Msk                          ( 0x1UL << GPIO_IDATA_GPIO_IDATA4_Pos )
#define GPIO_IDATA_GPIO_IDATA4                              ( GPIO_IDATA_GPIO_IDATA4_Msk )


#define GPIO_IDATA_GPIO_IDATA3_Pos                          ( 3U )
#define GPIO_IDATA_GPIO_IDATA3_Msk                          ( 0x1UL << GPIO_IDATA_GPIO_IDATA3_Pos )
#define GPIO_IDATA_GPIO_IDATA3                              ( GPIO_IDATA_GPIO_IDATA3_Msk )


#define GPIO_IDATA_GPIO_IDATA2_Pos                          ( 2U )
#define GPIO_IDATA_GPIO_IDATA2_Msk                          ( 0x1UL << GPIO_IDATA_GPIO_IDATA2_Pos )
#define GPIO_IDATA_GPIO_IDATA2                              ( GPIO_IDATA_GPIO_IDATA2_Msk )


#define GPIO_IDATA_GPIO_IDATA1_Pos                          ( 1U )
#define GPIO_IDATA_GPIO_IDATA1_Msk                          ( 0x1UL << GPIO_IDATA_GPIO_IDATA1_Pos )
#define GPIO_IDATA_GPIO_IDATA1                              ( GPIO_IDATA_GPIO_IDATA1_Msk )


#define GPIO_IDATA_GPIO_IDATA0_Pos                          ( 0U )
#define GPIO_IDATA_GPIO_IDATA0_Msk                          ( 0x1UL << GPIO_IDATA_GPIO_IDATA0_Pos )
#define GPIO_IDATA_GPIO_IDATA0                              ( GPIO_IDATA_GPIO_IDATA0_Msk )



/***************  Bits definition for GPIO_ODATA  **********************/

#define GPIO_ODATA_GPIO_ODATA15_Pos                         ( 15U )
#define GPIO_ODATA_GPIO_ODATA15_Msk                         ( 0x1UL << GPIO_ODATA_GPIO_ODATA15_Pos )
#define GPIO_ODATA_GPIO_ODATA15                             ( GPIO_ODATA_GPIO_ODATA15_Msk )


#define GPIO_ODATA_GPIO_ODATA14_Pos                         ( 14U )
#define GPIO_ODATA_GPIO_ODATA14_Msk                         ( 0x1UL << GPIO_ODATA_GPIO_ODATA14_Pos )
#define GPIO_ODATA_GPIO_ODATA14                             ( GPIO_ODATA_GPIO_ODATA14_Msk )


#define GPIO_ODATA_GPIO_ODATA13_Pos                         ( 13U )
#define GPIO_ODATA_GPIO_ODATA13_Msk                         ( 0x1UL << GPIO_ODATA_GPIO_ODATA13_Pos )
#define GPIO_ODATA_GPIO_ODATA13                             ( GPIO_ODATA_GPIO_ODATA13_Msk )


#define GPIO_ODATA_GPIO_ODATA12_Pos                         ( 12U )
#define GPIO_ODATA_GPIO_ODATA12_Msk                         ( 0x1UL << GPIO_ODATA_GPIO_ODATA12_Pos )
#define GPIO_ODATA_GPIO_ODATA12                             ( GPIO_ODATA_GPIO_ODATA12_Msk )


#define GPIO_ODATA_GPIO_ODATA11_Pos                         ( 11U )
#define GPIO_ODATA_GPIO_ODATA11_Msk                         ( 0x1UL << GPIO_ODATA_GPIO_ODATA11_Pos )
#define GPIO_ODATA_GPIO_ODATA11                             ( GPIO_ODATA_GPIO_ODATA11_Msk )


#define GPIO_ODATA_GPIO_ODATA10_Pos                         ( 10U )
#define GPIO_ODATA_GPIO_ODATA10_Msk                         ( 0x1UL << GPIO_ODATA_GPIO_ODATA10_Pos )
#define GPIO_ODATA_GPIO_ODATA10                             ( GPIO_ODATA_GPIO_ODATA10_Msk )


#define GPIO_ODATA_GPIO_ODATA9_Pos                          ( 9U )
#define GPIO_ODATA_GPIO_ODATA9_Msk                          ( 0x1UL << GPIO_ODATA_GPIO_ODATA9_Pos )
#define GPIO_ODATA_GPIO_ODATA9                              ( GPIO_ODATA_GPIO_ODATA9_Msk )


#define GPIO_ODATA_GPIO_ODATA8_Pos                          ( 8U )
#define GPIO_ODATA_GPIO_ODATA8_Msk                          ( 0x1UL << GPIO_ODATA_GPIO_ODATA8_Pos )
#define GPIO_ODATA_GPIO_ODATA8                              ( GPIO_ODATA_GPIO_ODATA8_Msk )


#define GPIO_ODATA_GPIO_ODATA7_Pos                          ( 7U )
#define GPIO_ODATA_GPIO_ODATA7_Msk                          ( 0x1UL << GPIO_ODATA_GPIO_ODATA7_Pos )
#define GPIO_ODATA_GPIO_ODATA7                              ( GPIO_ODATA_GPIO_ODATA7_Msk )


#define GPIO_ODATA_GPIO_ODATA6_Pos                          ( 6U )
#define GPIO_ODATA_GPIO_ODATA6_Msk                          ( 0x1UL << GPIO_ODATA_GPIO_ODATA6_Pos )
#define GPIO_ODATA_GPIO_ODATA6                              ( GPIO_ODATA_GPIO_ODATA6_Msk )


#define GPIO_ODATA_GPIO_ODATA5_Pos                          ( 5U )
#define GPIO_ODATA_GPIO_ODATA5_Msk                          ( 0x1UL << GPIO_ODATA_GPIO_ODATA5_Pos )
#define GPIO_ODATA_GPIO_ODATA5                              ( GPIO_ODATA_GPIO_ODATA5_Msk )


#define GPIO_ODATA_GPIO_ODATA4_Pos                          ( 4U )
#define GPIO_ODATA_GPIO_ODATA4_Msk                          ( 0x1UL << GPIO_ODATA_GPIO_ODATA4_Pos )
#define GPIO_ODATA_GPIO_ODATA4                              ( GPIO_ODATA_GPIO_ODATA4_Msk )


#define GPIO_ODATA_GPIO_ODATA3_Pos                          ( 3U )
#define GPIO_ODATA_GPIO_ODATA3_Msk                          ( 0x1UL << GPIO_ODATA_GPIO_ODATA3_Pos )
#define GPIO_ODATA_GPIO_ODATA3                              ( GPIO_ODATA_GPIO_ODATA3_Msk )


#define GPIO_ODATA_GPIO_ODATA2_Pos                          ( 2U )
#define GPIO_ODATA_GPIO_ODATA2_Msk                          ( 0x1UL << GPIO_ODATA_GPIO_ODATA2_Pos )
#define GPIO_ODATA_GPIO_ODATA2                              ( GPIO_ODATA_GPIO_ODATA2_Msk )


#define GPIO_ODATA_GPIO_ODATA1_Pos                          ( 1U )
#define GPIO_ODATA_GPIO_ODATA1_Msk                          ( 0x1UL << GPIO_ODATA_GPIO_ODATA1_Pos )
#define GPIO_ODATA_GPIO_ODATA1                              ( GPIO_ODATA_GPIO_ODATA1_Msk )


#define GPIO_ODATA_GPIO_ODATA0_Pos                          ( 0U )
#define GPIO_ODATA_GPIO_ODATA0_Msk                          ( 0x1UL << GPIO_ODATA_GPIO_ODATA0_Pos )
#define GPIO_ODATA_GPIO_ODATA0                              ( GPIO_ODATA_GPIO_ODATA0_Msk )



/***************  Bits definition for GPIO_BSC  **********************/

#define GPIO_BSC_GPIO_CLR15_Pos                             ( 31U )
#define GPIO_BSC_GPIO_CLR15_Msk                             ( 0x1UL << GPIO_BSC_GPIO_CLR15_Pos )
#define GPIO_BSC_GPIO_CLR15                                 ( GPIO_BSC_GPIO_CLR15_Msk )


#define GPIO_BSC_GPIO_CLR14_Pos                             ( 30U )
#define GPIO_BSC_GPIO_CLR14_Msk                             ( 0x1UL << GPIO_BSC_GPIO_CLR14_Pos )
#define GPIO_BSC_GPIO_CLR14                                 ( GPIO_BSC_GPIO_CLR14_Msk )


#define GPIO_BSC_GPIO_CLR13_Pos                             ( 29U )
#define GPIO_BSC_GPIO_CLR13_Msk                             ( 0x1UL << GPIO_BSC_GPIO_CLR13_Pos )
#define GPIO_BSC_GPIO_CLR13                                 ( GPIO_BSC_GPIO_CLR13_Msk )


#define GPIO_BSC_GPIO_CLR12_Pos                             ( 28U )
#define GPIO_BSC_GPIO_CLR12_Msk                             ( 0x1UL << GPIO_BSC_GPIO_CLR12_Pos )
#define GPIO_BSC_GPIO_CLR12                                 ( GPIO_BSC_GPIO_CLR12_Msk )


#define GPIO_BSC_GPIO_CLR11_Pos                             ( 27U )
#define GPIO_BSC_GPIO_CLR11_Msk                             ( 0x1UL << GPIO_BSC_GPIO_CLR11_Pos )
#define GPIO_BSC_GPIO_CLR11                                 ( GPIO_BSC_GPIO_CLR11_Msk )


#define GPIO_BSC_GPIO_CLR10_Pos                             ( 26U )
#define GPIO_BSC_GPIO_CLR10_Msk                             ( 0x1UL << GPIO_BSC_GPIO_CLR10_Pos )
#define GPIO_BSC_GPIO_CLR10                                 ( GPIO_BSC_GPIO_CLR10_Msk )


#define GPIO_BSC_GPIO_CLR9_Pos                              ( 25U )
#define GPIO_BSC_GPIO_CLR9_Msk                              ( 0x1UL << GPIO_BSC_GPIO_CLR9_Pos )
#define GPIO_BSC_GPIO_CLR9                                  ( GPIO_BSC_GPIO_CLR9_Msk )


#define GPIO_BSC_GPIO_CLR8_Pos                              ( 24U )
#define GPIO_BSC_GPIO_CLR8_Msk                              ( 0x1UL << GPIO_BSC_GPIO_CLR8_Pos )
#define GPIO_BSC_GPIO_CLR8                                  ( GPIO_BSC_GPIO_CLR8_Msk )


#define GPIO_BSC_GPIO_CLR7_Pos                              ( 23U )
#define GPIO_BSC_GPIO_CLR7_Msk                              ( 0x1UL << GPIO_BSC_GPIO_CLR7_Pos )
#define GPIO_BSC_GPIO_CLR7                                  ( GPIO_BSC_GPIO_CLR7_Msk )


#define GPIO_BSC_GPIO_CLR6_Pos                              ( 22U )
#define GPIO_BSC_GPIO_CLR6_Msk                              ( 0x1UL << GPIO_BSC_GPIO_CLR6_Pos )
#define GPIO_BSC_GPIO_CLR6                                  ( GPIO_BSC_GPIO_CLR6_Msk )


#define GPIO_BSC_GPIO_CLR5_Pos                              ( 21U )
#define GPIO_BSC_GPIO_CLR5_Msk                              ( 0x1UL << GPIO_BSC_GPIO_CLR5_Pos )
#define GPIO_BSC_GPIO_CLR5                                  ( GPIO_BSC_GPIO_CLR5_Msk )


#define GPIO_BSC_GPIO_CLR4_Pos                              ( 20U )
#define GPIO_BSC_GPIO_CLR4_Msk                              ( 0x1UL << GPIO_BSC_GPIO_CLR4_Pos )
#define GPIO_BSC_GPIO_CLR4                                  ( GPIO_BSC_GPIO_CLR4_Msk )


#define GPIO_BSC_GPIO_CLR3_Pos                              ( 19U )
#define GPIO_BSC_GPIO_CLR3_Msk                              ( 0x1UL << GPIO_BSC_GPIO_CLR3_Pos )
#define GPIO_BSC_GPIO_CLR3                                  ( GPIO_BSC_GPIO_CLR3_Msk )


#define GPIO_BSC_GPIO_CLR2_Pos                              ( 18U )
#define GPIO_BSC_GPIO_CLR2_Msk                              ( 0x1UL << GPIO_BSC_GPIO_CLR2_Pos )
#define GPIO_BSC_GPIO_CLR2                                  ( GPIO_BSC_GPIO_CLR2_Msk )


#define GPIO_BSC_GPIO_CLR1_Pos                              ( 17U )
#define GPIO_BSC_GPIO_CLR1_Msk                              ( 0x1UL << GPIO_BSC_GPIO_CLR1_Pos )
#define GPIO_BSC_GPIO_CLR1                                  ( GPIO_BSC_GPIO_CLR1_Msk )


#define GPIO_BSC_GPIO_CLR0_Pos                              ( 16U )
#define GPIO_BSC_GPIO_CLR0_Msk                              ( 0x1UL << GPIO_BSC_GPIO_CLR0_Pos )
#define GPIO_BSC_GPIO_CLR0                                  ( GPIO_BSC_GPIO_CLR0_Msk )


#define GPIO_BSC_GPIO_SET15_Pos                             ( 15U )
#define GPIO_BSC_GPIO_SET15_Msk                             ( 0x1UL << GPIO_BSC_GPIO_SET15_Pos )
#define GPIO_BSC_GPIO_SET15                                 ( GPIO_BSC_GPIO_SET15_Msk )


#define GPIO_BSC_GPIO_SET14_Pos                             ( 14U )
#define GPIO_BSC_GPIO_SET14_Msk                             ( 0x1UL << GPIO_BSC_GPIO_SET14_Pos )
#define GPIO_BSC_GPIO_SET14                                 ( GPIO_BSC_GPIO_SET14_Msk )


#define GPIO_BSC_GPIO_SET13_Pos                             ( 13U )
#define GPIO_BSC_GPIO_SET13_Msk                             ( 0x1UL << GPIO_BSC_GPIO_SET13_Pos )
#define GPIO_BSC_GPIO_SET13                                 ( GPIO_BSC_GPIO_SET13_Msk )


#define GPIO_BSC_GPIO_SET12_Pos                             ( 12U )
#define GPIO_BSC_GPIO_SET12_Msk                             ( 0x1UL << GPIO_BSC_GPIO_SET12_Pos )
#define GPIO_BSC_GPIO_SET12                                 ( GPIO_BSC_GPIO_SET12_Msk )


#define GPIO_BSC_GPIO_SET11_Pos                             ( 11U )
#define GPIO_BSC_GPIO_SET11_Msk                             ( 0x1UL << GPIO_BSC_GPIO_SET11_Pos )
#define GPIO_BSC_GPIO_SET11                                 ( GPIO_BSC_GPIO_SET11_Msk )


#define GPIO_BSC_GPIO_SET10_Pos                             ( 10U )
#define GPIO_BSC_GPIO_SET10_Msk                             ( 0x1UL << GPIO_BSC_GPIO_SET10_Pos )
#define GPIO_BSC_GPIO_SET10                                 ( GPIO_BSC_GPIO_SET10_Msk )


#define GPIO_BSC_GPIO_SET9_Pos                              ( 9U )
#define GPIO_BSC_GPIO_SET9_Msk                              ( 0x1UL << GPIO_BSC_GPIO_SET9_Pos )
#define GPIO_BSC_GPIO_SET9                                  ( GPIO_BSC_GPIO_SET9_Msk )


#define GPIO_BSC_GPIO_SET8_Pos                              ( 8U )
#define GPIO_BSC_GPIO_SET8_Msk                              ( 0x1UL << GPIO_BSC_GPIO_SET8_Pos )
#define GPIO_BSC_GPIO_SET8                                  ( GPIO_BSC_GPIO_SET8_Msk )


#define GPIO_BSC_GPIO_SET7_Pos                              ( 7U )
#define GPIO_BSC_GPIO_SET7_Msk                              ( 0x1UL << GPIO_BSC_GPIO_SET7_Pos )
#define GPIO_BSC_GPIO_SET7                                  ( GPIO_BSC_GPIO_SET7_Msk )


#define GPIO_BSC_GPIO_SET6_Pos                              ( 6U )
#define GPIO_BSC_GPIO_SET6_Msk                              ( 0x1UL << GPIO_BSC_GPIO_SET6_Pos )
#define GPIO_BSC_GPIO_SET6                                  ( GPIO_BSC_GPIO_SET6_Msk )


#define GPIO_BSC_GPIO_SET5_Pos                              ( 5U )
#define GPIO_BSC_GPIO_SET5_Msk                              ( 0x1UL << GPIO_BSC_GPIO_SET5_Pos )
#define GPIO_BSC_GPIO_SET5                                  ( GPIO_BSC_GPIO_SET5_Msk )


#define GPIO_BSC_GPIO_SET4_Pos                              ( 4U )
#define GPIO_BSC_GPIO_SET4_Msk                              ( 0x1UL << GPIO_BSC_GPIO_SET4_Pos )
#define GPIO_BSC_GPIO_SET4                                  ( GPIO_BSC_GPIO_SET4_Msk )


#define GPIO_BSC_GPIO_SET3_Pos                              ( 3U )
#define GPIO_BSC_GPIO_SET3_Msk                              ( 0x1UL << GPIO_BSC_GPIO_SET3_Pos )
#define GPIO_BSC_GPIO_SET3                                  ( GPIO_BSC_GPIO_SET3_Msk )


#define GPIO_BSC_GPIO_SET2_Pos                              ( 2U )
#define GPIO_BSC_GPIO_SET2_Msk                              ( 0x1UL << GPIO_BSC_GPIO_SET2_Pos )
#define GPIO_BSC_GPIO_SET2                                  ( GPIO_BSC_GPIO_SET2_Msk )


#define GPIO_BSC_GPIO_SET1_Pos                              ( 1U )
#define GPIO_BSC_GPIO_SET1_Msk                              ( 0x1UL << GPIO_BSC_GPIO_SET1_Pos )
#define GPIO_BSC_GPIO_SET1                                  ( GPIO_BSC_GPIO_SET1_Msk )


#define GPIO_BSC_GPIO_SET0_Pos                              ( 0U )
#define GPIO_BSC_GPIO_SET0_Msk                              ( 0x1UL << GPIO_BSC_GPIO_SET0_Pos )
#define GPIO_BSC_GPIO_SET0                                  ( GPIO_BSC_GPIO_SET0_Msk )



/***************  Bits definition for GPIO_AF0  **********************/

#define GPIO_AF0_GPIO_AFSEL0_7_Pos                          ( 28U )
#define GPIO_AF0_GPIO_AFSEL0_7_Msk                          ( 0xfUL << GPIO_AF0_GPIO_AFSEL0_7_Pos )
#define GPIO_AF0_GPIO_AFSEL0_7                              ( GPIO_AF0_GPIO_AFSEL0_7_Msk )
#define GPIO_AF0_GPIO_AFSEL0_7_0                            ( 0x1UL << GPIO_AF0_GPIO_AFSEL0_7_Pos )
#define GPIO_AF0_GPIO_AFSEL0_7_1                            ( 0x2UL << GPIO_AF0_GPIO_AFSEL0_7_Pos )
#define GPIO_AF0_GPIO_AFSEL0_7_2                            ( 0x4UL << GPIO_AF0_GPIO_AFSEL0_7_Pos )
#define GPIO_AF0_GPIO_AFSEL0_7_3                            ( 0x8UL << GPIO_AF0_GPIO_AFSEL0_7_Pos )

#define GPIO_AF0_GPIO_AFSEL0_6_Pos                          ( 24U )
#define GPIO_AF0_GPIO_AFSEL0_6_Msk                          ( 0xfUL << GPIO_AF0_GPIO_AFSEL0_6_Pos )
#define GPIO_AF0_GPIO_AFSEL0_6                              ( GPIO_AF0_GPIO_AFSEL0_6_Msk )
#define GPIO_AF0_GPIO_AFSEL0_6_0                            ( 0x1UL << GPIO_AF0_GPIO_AFSEL0_6_Pos )
#define GPIO_AF0_GPIO_AFSEL0_6_1                            ( 0x2UL << GPIO_AF0_GPIO_AFSEL0_6_Pos )
#define GPIO_AF0_GPIO_AFSEL0_6_2                            ( 0x4UL << GPIO_AF0_GPIO_AFSEL0_6_Pos )
#define GPIO_AF0_GPIO_AFSEL0_6_3                            ( 0x8UL << GPIO_AF0_GPIO_AFSEL0_6_Pos )

#define GPIO_AF0_GPIO_AFSEL0_5_Pos                          ( 20U )
#define GPIO_AF0_GPIO_AFSEL0_5_Msk                          ( 0xfUL << GPIO_AF0_GPIO_AFSEL0_5_Pos )
#define GPIO_AF0_GPIO_AFSEL0_5                              ( GPIO_AF0_GPIO_AFSEL0_5_Msk )
#define GPIO_AF0_GPIO_AFSEL0_5_0                            ( 0x1UL << GPIO_AF0_GPIO_AFSEL0_5_Pos )
#define GPIO_AF0_GPIO_AFSEL0_5_1                            ( 0x2UL << GPIO_AF0_GPIO_AFSEL0_5_Pos )
#define GPIO_AF0_GPIO_AFSEL0_5_2                            ( 0x4UL << GPIO_AF0_GPIO_AFSEL0_5_Pos )
#define GPIO_AF0_GPIO_AFSEL0_5_3                            ( 0x8UL << GPIO_AF0_GPIO_AFSEL0_5_Pos )

#define GPIO_AF0_GPIO_AFSEL0_4_Pos                          ( 16U )
#define GPIO_AF0_GPIO_AFSEL0_4_Msk                          ( 0xfUL << GPIO_AF0_GPIO_AFSEL0_4_Pos )
#define GPIO_AF0_GPIO_AFSEL0_4                              ( GPIO_AF0_GPIO_AFSEL0_4_Msk )
#define GPIO_AF0_GPIO_AFSEL0_4_0                            ( 0x1UL << GPIO_AF0_GPIO_AFSEL0_4_Pos )
#define GPIO_AF0_GPIO_AFSEL0_4_1                            ( 0x2UL << GPIO_AF0_GPIO_AFSEL0_4_Pos )
#define GPIO_AF0_GPIO_AFSEL0_4_2                            ( 0x4UL << GPIO_AF0_GPIO_AFSEL0_4_Pos )
#define GPIO_AF0_GPIO_AFSEL0_4_3                            ( 0x8UL << GPIO_AF0_GPIO_AFSEL0_4_Pos )

#define GPIO_AF0_GPIO_AFSEL0_3_Pos                          ( 12U )
#define GPIO_AF0_GPIO_AFSEL0_3_Msk                          ( 0xfUL << GPIO_AF0_GPIO_AFSEL0_3_Pos )
#define GPIO_AF0_GPIO_AFSEL0_3                              ( GPIO_AF0_GPIO_AFSEL0_3_Msk )
#define GPIO_AF0_GPIO_AFSEL0_3_0                            ( 0x1UL << GPIO_AF0_GPIO_AFSEL0_3_Pos )
#define GPIO_AF0_GPIO_AFSEL0_3_1                            ( 0x2UL << GPIO_AF0_GPIO_AFSEL0_3_Pos )
#define GPIO_AF0_GPIO_AFSEL0_3_2                            ( 0x4UL << GPIO_AF0_GPIO_AFSEL0_3_Pos )
#define GPIO_AF0_GPIO_AFSEL0_3_3                            ( 0x8UL << GPIO_AF0_GPIO_AFSEL0_3_Pos )

#define GPIO_AF0_GPIO_AFSEL0_2_Pos                          ( 8U )
#define GPIO_AF0_GPIO_AFSEL0_2_Msk                          ( 0xfUL << GPIO_AF0_GPIO_AFSEL0_2_Pos )
#define GPIO_AF0_GPIO_AFSEL0_2                              ( GPIO_AF0_GPIO_AFSEL0_2_Msk )
#define GPIO_AF0_GPIO_AFSEL0_2_0                            ( 0x1UL << GPIO_AF0_GPIO_AFSEL0_2_Pos )
#define GPIO_AF0_GPIO_AFSEL0_2_1                            ( 0x2UL << GPIO_AF0_GPIO_AFSEL0_2_Pos )
#define GPIO_AF0_GPIO_AFSEL0_2_2                            ( 0x4UL << GPIO_AF0_GPIO_AFSEL0_2_Pos )
#define GPIO_AF0_GPIO_AFSEL0_2_3                            ( 0x8UL << GPIO_AF0_GPIO_AFSEL0_2_Pos )

#define GPIO_AF0_GPIO_AFSEL0_1_Pos                          ( 4U )
#define GPIO_AF0_GPIO_AFSEL0_1_Msk                          ( 0xfUL << GPIO_AF0_GPIO_AFSEL0_1_Pos )
#define GPIO_AF0_GPIO_AFSEL0_1                              ( GPIO_AF0_GPIO_AFSEL0_1_Msk )
#define GPIO_AF0_GPIO_AFSEL0_1_0                            ( 0x1UL << GPIO_AF0_GPIO_AFSEL0_1_Pos )
#define GPIO_AF0_GPIO_AFSEL0_1_1                            ( 0x2UL << GPIO_AF0_GPIO_AFSEL0_1_Pos )
#define GPIO_AF0_GPIO_AFSEL0_1_2                            ( 0x4UL << GPIO_AF0_GPIO_AFSEL0_1_Pos )
#define GPIO_AF0_GPIO_AFSEL0_1_3                            ( 0x8UL << GPIO_AF0_GPIO_AFSEL0_1_Pos )

#define GPIO_AF0_GPIO_AFSEL0_0_Pos                          ( 0U )
#define GPIO_AF0_GPIO_AFSEL0_0_Msk                          ( 0xfUL << GPIO_AF0_GPIO_AFSEL0_0_Pos )
#define GPIO_AF0_GPIO_AFSEL0_0                              ( GPIO_AF0_GPIO_AFSEL0_0_Msk )
#define GPIO_AF0_GPIO_AFSEL0_0_0                            ( 0x1UL << GPIO_AF0_GPIO_AFSEL0_0_Pos )
#define GPIO_AF0_GPIO_AFSEL0_0_1                            ( 0x2UL << GPIO_AF0_GPIO_AFSEL0_0_Pos )
#define GPIO_AF0_GPIO_AFSEL0_0_2                            ( 0x4UL << GPIO_AF0_GPIO_AFSEL0_0_Pos )
#define GPIO_AF0_GPIO_AFSEL0_0_3                            ( 0x8UL << GPIO_AF0_GPIO_AFSEL0_0_Pos )


/***************  Bits definition for GPIO_AF1  **********************/

#define GPIO_AF1_GPIO_AFSEL1_15_Pos                         ( 28U )
#define GPIO_AF1_GPIO_AFSEL1_15_Msk                         ( 0xfUL << GPIO_AF1_GPIO_AFSEL1_15_Pos )
#define GPIO_AF1_GPIO_AFSEL1_15                             ( GPIO_AF1_GPIO_AFSEL1_15_Msk )
#define GPIO_AF1_GPIO_AFSEL1_15_0                           ( 0x1UL << GPIO_AF1_GPIO_AFSEL1_15_Pos )
#define GPIO_AF1_GPIO_AFSEL1_15_1                           ( 0x2UL << GPIO_AF1_GPIO_AFSEL1_15_Pos )
#define GPIO_AF1_GPIO_AFSEL1_15_2                           ( 0x4UL << GPIO_AF1_GPIO_AFSEL1_15_Pos )
#define GPIO_AF1_GPIO_AFSEL1_15_3                           ( 0x8UL << GPIO_AF1_GPIO_AFSEL1_15_Pos )

#define GPIO_AF1_GPIO_AFSEL1_14_Pos                         ( 24U )
#define GPIO_AF1_GPIO_AFSEL1_14_Msk                         ( 0xfUL << GPIO_AF1_GPIO_AFSEL1_14_Pos )
#define GPIO_AF1_GPIO_AFSEL1_14                             ( GPIO_AF1_GPIO_AFSEL1_14_Msk )
#define GPIO_AF1_GPIO_AFSEL1_14_0                           ( 0x1UL << GPIO_AF1_GPIO_AFSEL1_14_Pos )
#define GPIO_AF1_GPIO_AFSEL1_14_1                           ( 0x2UL << GPIO_AF1_GPIO_AFSEL1_14_Pos )
#define GPIO_AF1_GPIO_AFSEL1_14_2                           ( 0x4UL << GPIO_AF1_GPIO_AFSEL1_14_Pos )
#define GPIO_AF1_GPIO_AFSEL1_14_3                           ( 0x8UL << GPIO_AF1_GPIO_AFSEL1_14_Pos )

#define GPIO_AF1_GPIO_AFSEL1_13_Pos                         ( 20U )
#define GPIO_AF1_GPIO_AFSEL1_13_Msk                         ( 0xfUL << GPIO_AF1_GPIO_AFSEL1_13_Pos )
#define GPIO_AF1_GPIO_AFSEL1_13                             ( GPIO_AF1_GPIO_AFSEL1_13_Msk )
#define GPIO_AF1_GPIO_AFSEL1_13_0                           ( 0x1UL << GPIO_AF1_GPIO_AFSEL1_13_Pos )
#define GPIO_AF1_GPIO_AFSEL1_13_1                           ( 0x2UL << GPIO_AF1_GPIO_AFSEL1_13_Pos )
#define GPIO_AF1_GPIO_AFSEL1_13_2                           ( 0x4UL << GPIO_AF1_GPIO_AFSEL1_13_Pos )
#define GPIO_AF1_GPIO_AFSEL1_13_3                           ( 0x8UL << GPIO_AF1_GPIO_AFSEL1_13_Pos )

#define GPIO_AF1_GPIO_AFSEL1_12_Pos                         ( 16U )
#define GPIO_AF1_GPIO_AFSEL1_12_Msk                         ( 0xfUL << GPIO_AF1_GPIO_AFSEL1_12_Pos )
#define GPIO_AF1_GPIO_AFSEL1_12                             ( GPIO_AF1_GPIO_AFSEL1_12_Msk )
#define GPIO_AF1_GPIO_AFSEL1_12_0                           ( 0x1UL << GPIO_AF1_GPIO_AFSEL1_12_Pos )
#define GPIO_AF1_GPIO_AFSEL1_12_1                           ( 0x2UL << GPIO_AF1_GPIO_AFSEL1_12_Pos )
#define GPIO_AF1_GPIO_AFSEL1_12_2                           ( 0x4UL << GPIO_AF1_GPIO_AFSEL1_12_Pos )
#define GPIO_AF1_GPIO_AFSEL1_12_3                           ( 0x8UL << GPIO_AF1_GPIO_AFSEL1_12_Pos )

#define GPIO_AF1_GPIO_AFSEL1_11_Pos                         ( 12U )
#define GPIO_AF1_GPIO_AFSEL1_11_Msk                         ( 0xfUL << GPIO_AF1_GPIO_AFSEL1_11_Pos )
#define GPIO_AF1_GPIO_AFSEL1_11                             ( GPIO_AF1_GPIO_AFSEL1_11_Msk )
#define GPIO_AF1_GPIO_AFSEL1_11_0                           ( 0x1UL << GPIO_AF1_GPIO_AFSEL1_11_Pos )
#define GPIO_AF1_GPIO_AFSEL1_11_1                           ( 0x2UL << GPIO_AF1_GPIO_AFSEL1_11_Pos )
#define GPIO_AF1_GPIO_AFSEL1_11_2                           ( 0x4UL << GPIO_AF1_GPIO_AFSEL1_11_Pos )
#define GPIO_AF1_GPIO_AFSEL1_11_3                           ( 0x8UL << GPIO_AF1_GPIO_AFSEL1_11_Pos )

#define GPIO_AF1_GPIO_AFSEL1_10_Pos                         ( 8U )
#define GPIO_AF1_GPIO_AFSEL1_10_Msk                         ( 0xfUL << GPIO_AF1_GPIO_AFSEL1_10_Pos )
#define GPIO_AF1_GPIO_AFSEL1_10                             ( GPIO_AF1_GPIO_AFSEL1_10_Msk )
#define GPIO_AF1_GPIO_AFSEL1_10_0                           ( 0x1UL << GPIO_AF1_GPIO_AFSEL1_10_Pos )
#define GPIO_AF1_GPIO_AFSEL1_10_1                           ( 0x2UL << GPIO_AF1_GPIO_AFSEL1_10_Pos )
#define GPIO_AF1_GPIO_AFSEL1_10_2                           ( 0x4UL << GPIO_AF1_GPIO_AFSEL1_10_Pos )
#define GPIO_AF1_GPIO_AFSEL1_10_3                           ( 0x8UL << GPIO_AF1_GPIO_AFSEL1_10_Pos )

#define GPIO_AF1_GPIO_AFSEL1_9_Pos                          ( 4U )
#define GPIO_AF1_GPIO_AFSEL1_9_Msk                          ( 0xfUL << GPIO_AF1_GPIO_AFSEL1_9_Pos )
#define GPIO_AF1_GPIO_AFSEL1_9                              ( GPIO_AF1_GPIO_AFSEL1_9_Msk )
#define GPIO_AF1_GPIO_AFSEL1_9_0                            ( 0x1UL << GPIO_AF1_GPIO_AFSEL1_9_Pos )
#define GPIO_AF1_GPIO_AFSEL1_9_1                            ( 0x2UL << GPIO_AF1_GPIO_AFSEL1_9_Pos )
#define GPIO_AF1_GPIO_AFSEL1_9_2                            ( 0x4UL << GPIO_AF1_GPIO_AFSEL1_9_Pos )
#define GPIO_AF1_GPIO_AFSEL1_9_3                            ( 0x8UL << GPIO_AF1_GPIO_AFSEL1_9_Pos )

#define GPIO_AF1_GPIO_AFSEL1_8_Pos                          ( 0U )
#define GPIO_AF1_GPIO_AFSEL1_8_Msk                          ( 0xfUL << GPIO_AF1_GPIO_AFSEL1_8_Pos )
#define GPIO_AF1_GPIO_AFSEL1_8                              ( GPIO_AF1_GPIO_AFSEL1_8_Msk )
#define GPIO_AF1_GPIO_AFSEL1_8_0                            ( 0x1UL << GPIO_AF1_GPIO_AFSEL1_8_Pos )
#define GPIO_AF1_GPIO_AFSEL1_8_1                            ( 0x2UL << GPIO_AF1_GPIO_AFSEL1_8_Pos )
#define GPIO_AF1_GPIO_AFSEL1_8_2                            ( 0x4UL << GPIO_AF1_GPIO_AFSEL1_8_Pos )
#define GPIO_AF1_GPIO_AFSEL1_8_3                            ( 0x8UL << GPIO_AF1_GPIO_AFSEL1_8_Pos )


/***************  Bits definition for GPIO_DS0  **********************/

#define GPIO_DS0_GPIO_DS0_7_Pos                             ( 28U )
#define GPIO_DS0_GPIO_DS0_7_Msk                             ( 0xfUL << GPIO_DS0_GPIO_DS0_7_Pos )
#define GPIO_DS0_GPIO_DS0_7                                 ( GPIO_DS0_GPIO_DS0_7_Msk )
#define GPIO_DS0_GPIO_DS0_7_0                               ( 0x1UL << GPIO_DS0_GPIO_DS0_7_Pos )
#define GPIO_DS0_GPIO_DS0_7_1                               ( 0x2UL << GPIO_DS0_GPIO_DS0_7_Pos )
#define GPIO_DS0_GPIO_DS0_7_2                               ( 0x4UL << GPIO_DS0_GPIO_DS0_7_Pos )
#define GPIO_DS0_GPIO_DS0_7_3                               ( 0x8UL << GPIO_DS0_GPIO_DS0_7_Pos )

#define GPIO_DS0_GPIO_DS0_6_Pos                             ( 24U )
#define GPIO_DS0_GPIO_DS0_6_Msk                             ( 0xfUL << GPIO_DS0_GPIO_DS0_6_Pos )
#define GPIO_DS0_GPIO_DS0_6                                 ( GPIO_DS0_GPIO_DS0_6_Msk )
#define GPIO_DS0_GPIO_DS0_6_0                               ( 0x1UL << GPIO_DS0_GPIO_DS0_6_Pos )
#define GPIO_DS0_GPIO_DS0_6_1                               ( 0x2UL << GPIO_DS0_GPIO_DS0_6_Pos )
#define GPIO_DS0_GPIO_DS0_6_2                               ( 0x4UL << GPIO_DS0_GPIO_DS0_6_Pos )
#define GPIO_DS0_GPIO_DS0_6_3                               ( 0x8UL << GPIO_DS0_GPIO_DS0_6_Pos )

#define GPIO_DS0_GPIO_DS0_5_Pos                             ( 20U )
#define GPIO_DS0_GPIO_DS0_5_Msk                             ( 0xfUL << GPIO_DS0_GPIO_DS0_5_Pos )
#define GPIO_DS0_GPIO_DS0_5                                 ( GPIO_DS0_GPIO_DS0_5_Msk )
#define GPIO_DS0_GPIO_DS0_5_0                               ( 0x1UL << GPIO_DS0_GPIO_DS0_5_Pos )
#define GPIO_DS0_GPIO_DS0_5_1                               ( 0x2UL << GPIO_DS0_GPIO_DS0_5_Pos )
#define GPIO_DS0_GPIO_DS0_5_2                               ( 0x4UL << GPIO_DS0_GPIO_DS0_5_Pos )
#define GPIO_DS0_GPIO_DS0_5_3                               ( 0x8UL << GPIO_DS0_GPIO_DS0_5_Pos )

#define GPIO_DS0_GPIO_DS0_4_Pos                             ( 16U )
#define GPIO_DS0_GPIO_DS0_4_Msk                             ( 0xfUL << GPIO_DS0_GPIO_DS0_4_Pos )
#define GPIO_DS0_GPIO_DS0_4                                 ( GPIO_DS0_GPIO_DS0_4_Msk )
#define GPIO_DS0_GPIO_DS0_4_0                               ( 0x1UL << GPIO_DS0_GPIO_DS0_4_Pos )
#define GPIO_DS0_GPIO_DS0_4_1                               ( 0x2UL << GPIO_DS0_GPIO_DS0_4_Pos )
#define GPIO_DS0_GPIO_DS0_4_2                               ( 0x4UL << GPIO_DS0_GPIO_DS0_4_Pos )
#define GPIO_DS0_GPIO_DS0_4_3                               ( 0x8UL << GPIO_DS0_GPIO_DS0_4_Pos )

#define GPIO_DS0_GPIO_DS0_3_Pos                             ( 12U )
#define GPIO_DS0_GPIO_DS0_3_Msk                             ( 0xfUL << GPIO_DS0_GPIO_DS0_3_Pos )
#define GPIO_DS0_GPIO_DS0_3                                 ( GPIO_DS0_GPIO_DS0_3_Msk )
#define GPIO_DS0_GPIO_DS0_3_0                               ( 0x1UL << GPIO_DS0_GPIO_DS0_3_Pos )
#define GPIO_DS0_GPIO_DS0_3_1                               ( 0x2UL << GPIO_DS0_GPIO_DS0_3_Pos )
#define GPIO_DS0_GPIO_DS0_3_2                               ( 0x4UL << GPIO_DS0_GPIO_DS0_3_Pos )
#define GPIO_DS0_GPIO_DS0_3_3                               ( 0x8UL << GPIO_DS0_GPIO_DS0_3_Pos )

#define GPIO_DS0_GPIO_DS0_2_Pos                             ( 8U )
#define GPIO_DS0_GPIO_DS0_2_Msk                             ( 0xfUL << GPIO_DS0_GPIO_DS0_2_Pos )
#define GPIO_DS0_GPIO_DS0_2                                 ( GPIO_DS0_GPIO_DS0_2_Msk )
#define GPIO_DS0_GPIO_DS0_2_0                               ( 0x1UL << GPIO_DS0_GPIO_DS0_2_Pos )
#define GPIO_DS0_GPIO_DS0_2_1                               ( 0x2UL << GPIO_DS0_GPIO_DS0_2_Pos )
#define GPIO_DS0_GPIO_DS0_2_2                               ( 0x4UL << GPIO_DS0_GPIO_DS0_2_Pos )
#define GPIO_DS0_GPIO_DS0_2_3                               ( 0x8UL << GPIO_DS0_GPIO_DS0_2_Pos )

#define GPIO_DS0_GPIO_DS0_1_Pos                             ( 4U )
#define GPIO_DS0_GPIO_DS0_1_Msk                             ( 0xfUL << GPIO_DS0_GPIO_DS0_1_Pos )
#define GPIO_DS0_GPIO_DS0_1                                 ( GPIO_DS0_GPIO_DS0_1_Msk )
#define GPIO_DS0_GPIO_DS0_1_0                               ( 0x1UL << GPIO_DS0_GPIO_DS0_1_Pos )
#define GPIO_DS0_GPIO_DS0_1_1                               ( 0x2UL << GPIO_DS0_GPIO_DS0_1_Pos )
#define GPIO_DS0_GPIO_DS0_1_2                               ( 0x4UL << GPIO_DS0_GPIO_DS0_1_Pos )
#define GPIO_DS0_GPIO_DS0_1_3                               ( 0x8UL << GPIO_DS0_GPIO_DS0_1_Pos )

#define GPIO_DS0_GPIO_DS0_0_Pos                             ( 0U )
#define GPIO_DS0_GPIO_DS0_0_Msk                             ( 0xfUL << GPIO_DS0_GPIO_DS0_0_Pos )
#define GPIO_DS0_GPIO_DS0_0                                 ( GPIO_DS0_GPIO_DS0_0_Msk )
#define GPIO_DS0_GPIO_DS0_0_0                               ( 0x1UL << GPIO_DS0_GPIO_DS0_0_Pos )
#define GPIO_DS0_GPIO_DS0_0_1                               ( 0x2UL << GPIO_DS0_GPIO_DS0_0_Pos )
#define GPIO_DS0_GPIO_DS0_0_2                               ( 0x4UL << GPIO_DS0_GPIO_DS0_0_Pos )
#define GPIO_DS0_GPIO_DS0_0_3                               ( 0x8UL << GPIO_DS0_GPIO_DS0_0_Pos )


/***************  Bits definition for GPIO_DS1  **********************/

#define GPIO_DS1_GPIO_DS1_15_Pos                            ( 28U )
#define GPIO_DS1_GPIO_DS1_15_Msk                            ( 0xfUL << GPIO_DS1_GPIO_DS1_15_Pos )
#define GPIO_DS1_GPIO_DS1_15                                ( GPIO_DS1_GPIO_DS1_15_Msk )
#define GPIO_DS1_GPIO_DS1_15_0                              ( 0x1UL << GPIO_DS1_GPIO_DS1_15_Pos )
#define GPIO_DS1_GPIO_DS1_15_1                              ( 0x2UL << GPIO_DS1_GPIO_DS1_15_Pos )
#define GPIO_DS1_GPIO_DS1_15_2                              ( 0x4UL << GPIO_DS1_GPIO_DS1_15_Pos )
#define GPIO_DS1_GPIO_DS1_15_3                              ( 0x8UL << GPIO_DS1_GPIO_DS1_15_Pos )

#define GPIO_DS1_GPIO_DS1_14_Pos                            ( 24U )
#define GPIO_DS1_GPIO_DS1_14_Msk                            ( 0xfUL << GPIO_DS1_GPIO_DS1_14_Pos )
#define GPIO_DS1_GPIO_DS1_14                                ( GPIO_DS1_GPIO_DS1_14_Msk )
#define GPIO_DS1_GPIO_DS1_14_0                              ( 0x1UL << GPIO_DS1_GPIO_DS1_14_Pos )
#define GPIO_DS1_GPIO_DS1_14_1                              ( 0x2UL << GPIO_DS1_GPIO_DS1_14_Pos )
#define GPIO_DS1_GPIO_DS1_14_2                              ( 0x4UL << GPIO_DS1_GPIO_DS1_14_Pos )
#define GPIO_DS1_GPIO_DS1_14_3                              ( 0x8UL << GPIO_DS1_GPIO_DS1_14_Pos )

#define GPIO_DS1_GPIO_DS1_13_Pos                            ( 20U )
#define GPIO_DS1_GPIO_DS1_13_Msk                            ( 0xfUL << GPIO_DS1_GPIO_DS1_13_Pos )
#define GPIO_DS1_GPIO_DS1_13                                ( GPIO_DS1_GPIO_DS1_13_Msk )
#define GPIO_DS1_GPIO_DS1_13_0                              ( 0x1UL << GPIO_DS1_GPIO_DS1_13_Pos )
#define GPIO_DS1_GPIO_DS1_13_1                              ( 0x2UL << GPIO_DS1_GPIO_DS1_13_Pos )
#define GPIO_DS1_GPIO_DS1_13_2                              ( 0x4UL << GPIO_DS1_GPIO_DS1_13_Pos )
#define GPIO_DS1_GPIO_DS1_13_3                              ( 0x8UL << GPIO_DS1_GPIO_DS1_13_Pos )

#define GPIO_DS1_GPIO_DS1_12_Pos                            ( 16U )
#define GPIO_DS1_GPIO_DS1_12_Msk                            ( 0xfUL << GPIO_DS1_GPIO_DS1_12_Pos )
#define GPIO_DS1_GPIO_DS1_12                                ( GPIO_DS1_GPIO_DS1_12_Msk )
#define GPIO_DS1_GPIO_DS1_12_0                              ( 0x1UL << GPIO_DS1_GPIO_DS1_12_Pos )
#define GPIO_DS1_GPIO_DS1_12_1                              ( 0x2UL << GPIO_DS1_GPIO_DS1_12_Pos )
#define GPIO_DS1_GPIO_DS1_12_2                              ( 0x4UL << GPIO_DS1_GPIO_DS1_12_Pos )
#define GPIO_DS1_GPIO_DS1_12_3                              ( 0x8UL << GPIO_DS1_GPIO_DS1_12_Pos )

#define GPIO_DS1_GPIO_DS1_11_Pos                            ( 12U )
#define GPIO_DS1_GPIO_DS1_11_Msk                            ( 0xfUL << GPIO_DS1_GPIO_DS1_11_Pos )
#define GPIO_DS1_GPIO_DS1_11                                ( GPIO_DS1_GPIO_DS1_11_Msk )
#define GPIO_DS1_GPIO_DS1_11_0                              ( 0x1UL << GPIO_DS1_GPIO_DS1_11_Pos )
#define GPIO_DS1_GPIO_DS1_11_1                              ( 0x2UL << GPIO_DS1_GPIO_DS1_11_Pos )
#define GPIO_DS1_GPIO_DS1_11_2                              ( 0x4UL << GPIO_DS1_GPIO_DS1_11_Pos )
#define GPIO_DS1_GPIO_DS1_11_3                              ( 0x8UL << GPIO_DS1_GPIO_DS1_11_Pos )

#define GPIO_DS1_GPIO_DS1_10_Pos                            ( 8U )
#define GPIO_DS1_GPIO_DS1_10_Msk                            ( 0xfUL << GPIO_DS1_GPIO_DS1_10_Pos )
#define GPIO_DS1_GPIO_DS1_10                                ( GPIO_DS1_GPIO_DS1_10_Msk )
#define GPIO_DS1_GPIO_DS1_10_0                              ( 0x1UL << GPIO_DS1_GPIO_DS1_10_Pos )
#define GPIO_DS1_GPIO_DS1_10_1                              ( 0x2UL << GPIO_DS1_GPIO_DS1_10_Pos )
#define GPIO_DS1_GPIO_DS1_10_2                              ( 0x4UL << GPIO_DS1_GPIO_DS1_10_Pos )
#define GPIO_DS1_GPIO_DS1_10_3                              ( 0x8UL << GPIO_DS1_GPIO_DS1_10_Pos )

#define GPIO_DS1_GPIO_DS1_9_Pos                             ( 4U )
#define GPIO_DS1_GPIO_DS1_9_Msk                             ( 0xfUL << GPIO_DS1_GPIO_DS1_9_Pos )
#define GPIO_DS1_GPIO_DS1_9                                 ( GPIO_DS1_GPIO_DS1_9_Msk )
#define GPIO_DS1_GPIO_DS1_9_0                               ( 0x1UL << GPIO_DS1_GPIO_DS1_9_Pos )
#define GPIO_DS1_GPIO_DS1_9_1                               ( 0x2UL << GPIO_DS1_GPIO_DS1_9_Pos )
#define GPIO_DS1_GPIO_DS1_9_2                               ( 0x4UL << GPIO_DS1_GPIO_DS1_9_Pos )
#define GPIO_DS1_GPIO_DS1_9_3                               ( 0x8UL << GPIO_DS1_GPIO_DS1_9_Pos )

#define GPIO_DS1_GPIO_DS1_8_Pos                             ( 0U )
#define GPIO_DS1_GPIO_DS1_8_Msk                             ( 0xfUL << GPIO_DS1_GPIO_DS1_8_Pos )
#define GPIO_DS1_GPIO_DS1_8                                 ( GPIO_DS1_GPIO_DS1_8_Msk )
#define GPIO_DS1_GPIO_DS1_8_0                               ( 0x1UL << GPIO_DS1_GPIO_DS1_8_Pos )
#define GPIO_DS1_GPIO_DS1_8_1                               ( 0x2UL << GPIO_DS1_GPIO_DS1_8_Pos )
#define GPIO_DS1_GPIO_DS1_8_2                               ( 0x4UL << GPIO_DS1_GPIO_DS1_8_Pos )
#define GPIO_DS1_GPIO_DS1_8_3                               ( 0x8UL << GPIO_DS1_GPIO_DS1_8_Pos )


/***************  Bits definition for GPIO_SMIT  **********************/

#define GPIO_SMIT_GPIO_SMTEN15_Pos                          ( 15U )
#define GPIO_SMIT_GPIO_SMTEN15_Msk                          ( 0x1UL << GPIO_SMIT_GPIO_SMTEN15_Pos )
#define GPIO_SMIT_GPIO_SMTEN15                              ( GPIO_SMIT_GPIO_SMTEN15_Msk )


#define GPIO_SMIT_GPIO_SMTEN14_Pos                          ( 14U )
#define GPIO_SMIT_GPIO_SMTEN14_Msk                          ( 0x1UL << GPIO_SMIT_GPIO_SMTEN14_Pos )
#define GPIO_SMIT_GPIO_SMTEN14                              ( GPIO_SMIT_GPIO_SMTEN14_Msk )


#define GPIO_SMIT_GPIO_SMTEN13_Pos                          ( 13U )
#define GPIO_SMIT_GPIO_SMTEN13_Msk                          ( 0x1UL << GPIO_SMIT_GPIO_SMTEN13_Pos )
#define GPIO_SMIT_GPIO_SMTEN13                              ( GPIO_SMIT_GPIO_SMTEN13_Msk )


#define GPIO_SMIT_GPIO_SMTEN12_Pos                          ( 12U )
#define GPIO_SMIT_GPIO_SMTEN12_Msk                          ( 0x1UL << GPIO_SMIT_GPIO_SMTEN12_Pos )
#define GPIO_SMIT_GPIO_SMTEN12                              ( GPIO_SMIT_GPIO_SMTEN12_Msk )


#define GPIO_SMIT_GPIO_SMTEN11_Pos                          ( 11U )
#define GPIO_SMIT_GPIO_SMTEN11_Msk                          ( 0x1UL << GPIO_SMIT_GPIO_SMTEN11_Pos )
#define GPIO_SMIT_GPIO_SMTEN11                              ( GPIO_SMIT_GPIO_SMTEN11_Msk )


#define GPIO_SMIT_GPIO_SMTEN10_Pos                          ( 10U )
#define GPIO_SMIT_GPIO_SMTEN10_Msk                          ( 0x1UL << GPIO_SMIT_GPIO_SMTEN10_Pos )
#define GPIO_SMIT_GPIO_SMTEN10                              ( GPIO_SMIT_GPIO_SMTEN10_Msk )


#define GPIO_SMIT_GPIO_SMTEN9_Pos                           ( 9U )
#define GPIO_SMIT_GPIO_SMTEN9_Msk                           ( 0x1UL << GPIO_SMIT_GPIO_SMTEN9_Pos )
#define GPIO_SMIT_GPIO_SMTEN9                               ( GPIO_SMIT_GPIO_SMTEN9_Msk )


#define GPIO_SMIT_GPIO_SMTEN8_Pos                           ( 8U )
#define GPIO_SMIT_GPIO_SMTEN8_Msk                           ( 0x1UL << GPIO_SMIT_GPIO_SMTEN8_Pos )
#define GPIO_SMIT_GPIO_SMTEN8                               ( GPIO_SMIT_GPIO_SMTEN8_Msk )


#define GPIO_SMIT_GPIO_SMTEN7_Pos                           ( 7U )
#define GPIO_SMIT_GPIO_SMTEN7_Msk                           ( 0x1UL << GPIO_SMIT_GPIO_SMTEN7_Pos )
#define GPIO_SMIT_GPIO_SMTEN7                               ( GPIO_SMIT_GPIO_SMTEN7_Msk )


#define GPIO_SMIT_GPIO_SMTEN6_Pos                           ( 6U )
#define GPIO_SMIT_GPIO_SMTEN6_Msk                           ( 0x1UL << GPIO_SMIT_GPIO_SMTEN6_Pos )
#define GPIO_SMIT_GPIO_SMTEN6                               ( GPIO_SMIT_GPIO_SMTEN6_Msk )


#define GPIO_SMIT_GPIO_SMTEN5_Pos                           ( 5U )
#define GPIO_SMIT_GPIO_SMTEN5_Msk                           ( 0x1UL << GPIO_SMIT_GPIO_SMTEN5_Pos )
#define GPIO_SMIT_GPIO_SMTEN5                               ( GPIO_SMIT_GPIO_SMTEN5_Msk )


#define GPIO_SMIT_GPIO_SMTEN4_Pos                           ( 4U )
#define GPIO_SMIT_GPIO_SMTEN4_Msk                           ( 0x1UL << GPIO_SMIT_GPIO_SMTEN4_Pos )
#define GPIO_SMIT_GPIO_SMTEN4                               ( GPIO_SMIT_GPIO_SMTEN4_Msk )


#define GPIO_SMIT_GPIO_SMTEN3_Pos                           ( 3U )
#define GPIO_SMIT_GPIO_SMTEN3_Msk                           ( 0x1UL << GPIO_SMIT_GPIO_SMTEN3_Pos )
#define GPIO_SMIT_GPIO_SMTEN3                               ( GPIO_SMIT_GPIO_SMTEN3_Msk )


#define GPIO_SMIT_GPIO_SMTEN2_Pos                           ( 2U )
#define GPIO_SMIT_GPIO_SMTEN2_Msk                           ( 0x1UL << GPIO_SMIT_GPIO_SMTEN2_Pos )
#define GPIO_SMIT_GPIO_SMTEN2                               ( GPIO_SMIT_GPIO_SMTEN2_Msk )


#define GPIO_SMIT_GPIO_SMTEN1_Pos                           ( 1U )
#define GPIO_SMIT_GPIO_SMTEN1_Msk                           ( 0x1UL << GPIO_SMIT_GPIO_SMTEN1_Pos )
#define GPIO_SMIT_GPIO_SMTEN1                               ( GPIO_SMIT_GPIO_SMTEN1_Msk )


#define GPIO_SMIT_GPIO_SMTEN0_Pos                           ( 0U )
#define GPIO_SMIT_GPIO_SMTEN0_Msk                           ( 0x1UL << GPIO_SMIT_GPIO_SMTEN0_Pos )
#define GPIO_SMIT_GPIO_SMTEN0                               ( GPIO_SMIT_GPIO_SMTEN0_Msk )



/***************  Bits definition for GPIO_LOCK  **********************/

#define GPIO_LOCK_LOCK_KEY_Pos                              ( 16U )
#define GPIO_LOCK_LOCK_KEY_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_KEY_Pos )
#define GPIO_LOCK_LOCK_KEY                                  ( GPIO_LOCK_LOCK_KEY_Msk )

#define GPIO_LOCK_LOCK_EN15_Pos                             ( 15U )
#define GPIO_LOCK_LOCK_EN15_Msk                             ( 0x1UL << GPIO_LOCK_LOCK_EN15_Pos )
#define GPIO_LOCK_LOCK_EN15                                 ( GPIO_LOCK_LOCK_EN15_Msk )


#define GPIO_LOCK_LOCK_EN14_Pos                             ( 14U )
#define GPIO_LOCK_LOCK_EN14_Msk                             ( 0x1UL << GPIO_LOCK_LOCK_EN14_Pos )
#define GPIO_LOCK_LOCK_EN14                                 ( GPIO_LOCK_LOCK_EN14_Msk )


#define GPIO_LOCK_LOCK_EN13_Pos                             ( 13U )
#define GPIO_LOCK_LOCK_EN13_Msk                             ( 0x1UL << GPIO_LOCK_LOCK_EN13_Pos )
#define GPIO_LOCK_LOCK_EN13                                 ( GPIO_LOCK_LOCK_EN13_Msk )


#define GPIO_LOCK_LOCK_EN12_Pos                             ( 12U )
#define GPIO_LOCK_LOCK_EN12_Msk                             ( 0x1UL << GPIO_LOCK_LOCK_EN12_Pos )
#define GPIO_LOCK_LOCK_EN12                                 ( GPIO_LOCK_LOCK_EN12_Msk )


#define GPIO_LOCK_LOCK_EN11_Pos                             ( 11U )
#define GPIO_LOCK_LOCK_EN11_Msk                             ( 0x1UL << GPIO_LOCK_LOCK_EN11_Pos )
#define GPIO_LOCK_LOCK_EN11                                 ( GPIO_LOCK_LOCK_EN11_Msk )


#define GPIO_LOCK_LOCK_EN10_Pos                             ( 10U )
#define GPIO_LOCK_LOCK_EN10_Msk                             ( 0x1UL << GPIO_LOCK_LOCK_EN10_Pos )
#define GPIO_LOCK_LOCK_EN10                                 ( GPIO_LOCK_LOCK_EN10_Msk )


#define GPIO_LOCK_LOCK_EN9_Pos                              ( 9U )
#define GPIO_LOCK_LOCK_EN9_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_EN9_Pos )
#define GPIO_LOCK_LOCK_EN9                                  ( GPIO_LOCK_LOCK_EN9_Msk )


#define GPIO_LOCK_LOCK_EN8_Pos                              ( 8U )
#define GPIO_LOCK_LOCK_EN8_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_EN8_Pos )
#define GPIO_LOCK_LOCK_EN8                                  ( GPIO_LOCK_LOCK_EN8_Msk )


#define GPIO_LOCK_LOCK_EN7_Pos                              ( 7U )
#define GPIO_LOCK_LOCK_EN7_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_EN7_Pos )
#define GPIO_LOCK_LOCK_EN7                                  ( GPIO_LOCK_LOCK_EN7_Msk )


#define GPIO_LOCK_LOCK_EN6_Pos                              ( 6U )
#define GPIO_LOCK_LOCK_EN6_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_EN6_Pos )
#define GPIO_LOCK_LOCK_EN6                                  ( GPIO_LOCK_LOCK_EN6_Msk )


#define GPIO_LOCK_LOCK_EN5_Pos                              ( 5U )
#define GPIO_LOCK_LOCK_EN5_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_EN5_Pos )
#define GPIO_LOCK_LOCK_EN5                                  ( GPIO_LOCK_LOCK_EN5_Msk )


#define GPIO_LOCK_LOCK_EN4_Pos                              ( 4U )
#define GPIO_LOCK_LOCK_EN4_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_EN4_Pos )
#define GPIO_LOCK_LOCK_EN4                                  ( GPIO_LOCK_LOCK_EN4_Msk )


#define GPIO_LOCK_LOCK_EN3_Pos                              ( 3U )
#define GPIO_LOCK_LOCK_EN3_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_EN3_Pos )
#define GPIO_LOCK_LOCK_EN3                                  ( GPIO_LOCK_LOCK_EN3_Msk )


#define GPIO_LOCK_LOCK_EN2_Pos                              ( 2U )
#define GPIO_LOCK_LOCK_EN2_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_EN2_Pos )
#define GPIO_LOCK_LOCK_EN2                                  ( GPIO_LOCK_LOCK_EN2_Msk )


#define GPIO_LOCK_LOCK_EN1_Pos                              ( 1U )
#define GPIO_LOCK_LOCK_EN1_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_EN1_Pos )
#define GPIO_LOCK_LOCK_EN1                                  ( GPIO_LOCK_LOCK_EN1_Msk )


#define GPIO_LOCK_LOCK_EN0_Pos                              ( 0U )
#define GPIO_LOCK_LOCK_EN0_Msk                              ( 0x1UL << GPIO_LOCK_LOCK_EN0_Pos )
#define GPIO_LOCK_LOCK_EN0                                  ( GPIO_LOCK_LOCK_EN0_Msk )



/***************  Bits definition for GPIO_AIEN  **********************/

#define GPIO_AIEN_GPIO_AIEN15_Pos                           ( 15U )
#define GPIO_AIEN_GPIO_AIEN15_Msk                           ( 0x1UL << GPIO_AIEN_GPIO_AIEN15_Pos )
#define GPIO_AIEN_GPIO_AIEN15                               ( GPIO_AIEN_GPIO_AIEN15_Msk )


#define GPIO_AIEN_GPIO_AIEN14_Pos                           ( 14U )
#define GPIO_AIEN_GPIO_AIEN14_Msk                           ( 0x1UL << GPIO_AIEN_GPIO_AIEN14_Pos )
#define GPIO_AIEN_GPIO_AIEN14                               ( GPIO_AIEN_GPIO_AIEN14_Msk )


#define GPIO_AIEN_GPIO_AIEN13_Pos                           ( 13U )
#define GPIO_AIEN_GPIO_AIEN13_Msk                           ( 0x1UL << GPIO_AIEN_GPIO_AIEN13_Pos )
#define GPIO_AIEN_GPIO_AIEN13                               ( GPIO_AIEN_GPIO_AIEN13_Msk )


#define GPIO_AIEN_GPIO_AIEN12_Pos                           ( 12U )
#define GPIO_AIEN_GPIO_AIEN12_Msk                           ( 0x1UL << GPIO_AIEN_GPIO_AIEN12_Pos )
#define GPIO_AIEN_GPIO_AIEN12                               ( GPIO_AIEN_GPIO_AIEN12_Msk )


#define GPIO_AIEN_GPIO_AIEN11_Pos                           ( 11U )
#define GPIO_AIEN_GPIO_AIEN11_Msk                           ( 0x1UL << GPIO_AIEN_GPIO_AIEN11_Pos )
#define GPIO_AIEN_GPIO_AIEN11                               ( GPIO_AIEN_GPIO_AIEN11_Msk )


#define GPIO_AIEN_GPIO_AIEN10_Pos                           ( 10U )
#define GPIO_AIEN_GPIO_AIEN10_Msk                           ( 0x1UL << GPIO_AIEN_GPIO_AIEN10_Pos )
#define GPIO_AIEN_GPIO_AIEN10                               ( GPIO_AIEN_GPIO_AIEN10_Msk )


#define GPIO_AIEN_GPIO_AIEN9_Pos                            ( 9U )
#define GPIO_AIEN_GPIO_AIEN9_Msk                            ( 0x1UL << GPIO_AIEN_GPIO_AIEN9_Pos )
#define GPIO_AIEN_GPIO_AIEN9                                ( GPIO_AIEN_GPIO_AIEN9_Msk )


#define GPIO_AIEN_GPIO_AIEN8_Pos                            ( 8U )
#define GPIO_AIEN_GPIO_AIEN8_Msk                            ( 0x1UL << GPIO_AIEN_GPIO_AIEN8_Pos )
#define GPIO_AIEN_GPIO_AIEN8                                ( GPIO_AIEN_GPIO_AIEN8_Msk )


#define GPIO_AIEN_GPIO_AIEN7_Pos                            ( 7U )
#define GPIO_AIEN_GPIO_AIEN7_Msk                            ( 0x1UL << GPIO_AIEN_GPIO_AIEN7_Pos )
#define GPIO_AIEN_GPIO_AIEN7                                ( GPIO_AIEN_GPIO_AIEN7_Msk )


#define GPIO_AIEN_GPIO_AIEN6_Pos                            ( 6U )
#define GPIO_AIEN_GPIO_AIEN6_Msk                            ( 0x1UL << GPIO_AIEN_GPIO_AIEN6_Pos )
#define GPIO_AIEN_GPIO_AIEN6                                ( GPIO_AIEN_GPIO_AIEN6_Msk )


#define GPIO_AIEN_GPIO_AIEN5_Pos                            ( 5U )
#define GPIO_AIEN_GPIO_AIEN5_Msk                            ( 0x1UL << GPIO_AIEN_GPIO_AIEN5_Pos )
#define GPIO_AIEN_GPIO_AIEN5                                ( GPIO_AIEN_GPIO_AIEN5_Msk )


#define GPIO_AIEN_GPIO_AIEN4_Pos                            ( 4U )
#define GPIO_AIEN_GPIO_AIEN4_Msk                            ( 0x1UL << GPIO_AIEN_GPIO_AIEN4_Pos )
#define GPIO_AIEN_GPIO_AIEN4                                ( GPIO_AIEN_GPIO_AIEN4_Msk )


#define GPIO_AIEN_GPIO_AIEN3_Pos                            ( 3U )
#define GPIO_AIEN_GPIO_AIEN3_Msk                            ( 0x1UL << GPIO_AIEN_GPIO_AIEN3_Pos )
#define GPIO_AIEN_GPIO_AIEN3                                ( GPIO_AIEN_GPIO_AIEN3_Msk )


#define GPIO_AIEN_GPIO_AIEN2_Pos                            ( 2U )
#define GPIO_AIEN_GPIO_AIEN2_Msk                            ( 0x1UL << GPIO_AIEN_GPIO_AIEN2_Pos )
#define GPIO_AIEN_GPIO_AIEN2                                ( GPIO_AIEN_GPIO_AIEN2_Msk )


#define GPIO_AIEN_GPIO_AIEN1_Pos                            ( 1U )
#define GPIO_AIEN_GPIO_AIEN1_Msk                            ( 0x1UL << GPIO_AIEN_GPIO_AIEN1_Pos )
#define GPIO_AIEN_GPIO_AIEN1                                ( GPIO_AIEN_GPIO_AIEN1_Msk )


#define GPIO_AIEN_GPIO_AIEN0_Pos                            ( 0U )
#define GPIO_AIEN_GPIO_AIEN0_Msk                            ( 0x1UL << GPIO_AIEN_GPIO_AIEN0_Pos )
#define GPIO_AIEN_GPIO_AIEN0                                ( GPIO_AIEN_GPIO_AIEN0_Msk )


/***************  Bits definition for EXTI_IENR1  **********************/

#define EXTI_IENR1_INTEN31_Pos                              ( 31U )
#define EXTI_IENR1_INTEN31_Msk                              ( 0x1UL << EXTI_IENR1_INTEN31_Pos )
#define EXTI_IENR1_INTEN31                                  ( EXTI_IENR1_INTEN31_Msk )


#define EXTI_IENR1_INTEN30_Pos                              ( 30U )
#define EXTI_IENR1_INTEN30_Msk                              ( 0x1UL << EXTI_IENR1_INTEN30_Pos )
#define EXTI_IENR1_INTEN30                                  ( EXTI_IENR1_INTEN30_Msk )


#define EXTI_IENR1_INTEN29_Pos                              ( 29U )
#define EXTI_IENR1_INTEN29_Msk                              ( 0x1UL << EXTI_IENR1_INTEN29_Pos )
#define EXTI_IENR1_INTEN29                                  ( EXTI_IENR1_INTEN29_Msk )


#define EXTI_IENR1_INTEN28_Pos                              ( 28U )
#define EXTI_IENR1_INTEN28_Msk                              ( 0x1UL << EXTI_IENR1_INTEN28_Pos )
#define EXTI_IENR1_INTEN28                                  ( EXTI_IENR1_INTEN28_Msk )


#define EXTI_IENR1_INTEN27_Pos                              ( 27U )
#define EXTI_IENR1_INTEN27_Msk                              ( 0x1UL << EXTI_IENR1_INTEN27_Pos )
#define EXTI_IENR1_INTEN27                                  ( EXTI_IENR1_INTEN27_Msk )


#define EXTI_IENR1_INTEN26_Pos                              ( 26U )
#define EXTI_IENR1_INTEN26_Msk                              ( 0x1UL << EXTI_IENR1_INTEN26_Pos )
#define EXTI_IENR1_INTEN26                                  ( EXTI_IENR1_INTEN26_Msk )


#define EXTI_IENR1_INTEN25_Pos                              ( 25U )
#define EXTI_IENR1_INTEN25_Msk                              ( 0x1UL << EXTI_IENR1_INTEN25_Pos )
#define EXTI_IENR1_INTEN25                                  ( EXTI_IENR1_INTEN25_Msk )


#define EXTI_IENR1_INTEN24_Pos                              ( 24U )
#define EXTI_IENR1_INTEN24_Msk                              ( 0x1UL << EXTI_IENR1_INTEN24_Pos )
#define EXTI_IENR1_INTEN24                                  ( EXTI_IENR1_INTEN24_Msk )


#define EXTI_IENR1_INTEN23_Pos                              ( 23U )
#define EXTI_IENR1_INTEN23_Msk                              ( 0x1UL << EXTI_IENR1_INTEN23_Pos )
#define EXTI_IENR1_INTEN23                                  ( EXTI_IENR1_INTEN23_Msk )


#define EXTI_IENR1_INTEN22_Pos                              ( 22U )
#define EXTI_IENR1_INTEN22_Msk                              ( 0x1UL << EXTI_IENR1_INTEN22_Pos )
#define EXTI_IENR1_INTEN22                                  ( EXTI_IENR1_INTEN22_Msk )


#define EXTI_IENR1_INTEN21_Pos                              ( 21U )
#define EXTI_IENR1_INTEN21_Msk                              ( 0x1UL << EXTI_IENR1_INTEN21_Pos )
#define EXTI_IENR1_INTEN21                                  ( EXTI_IENR1_INTEN21_Msk )


#define EXTI_IENR1_INTEN20_Pos                              ( 20U )
#define EXTI_IENR1_INTEN20_Msk                              ( 0x1UL << EXTI_IENR1_INTEN20_Pos )
#define EXTI_IENR1_INTEN20                                  ( EXTI_IENR1_INTEN20_Msk )


#define EXTI_IENR1_INTEN19_Pos                              ( 19U )
#define EXTI_IENR1_INTEN19_Msk                              ( 0x1UL << EXTI_IENR1_INTEN19_Pos )
#define EXTI_IENR1_INTEN19                                  ( EXTI_IENR1_INTEN19_Msk )


#define EXTI_IENR1_INTEN18_Pos                              ( 18U )
#define EXTI_IENR1_INTEN18_Msk                              ( 0x1UL << EXTI_IENR1_INTEN18_Pos )
#define EXTI_IENR1_INTEN18                                  ( EXTI_IENR1_INTEN18_Msk )


#define EXTI_IENR1_INTEN17_Pos                              ( 17U )
#define EXTI_IENR1_INTEN17_Msk                              ( 0x1UL << EXTI_IENR1_INTEN17_Pos )
#define EXTI_IENR1_INTEN17                                  ( EXTI_IENR1_INTEN17_Msk )


#define EXTI_IENR1_INTEN16_Pos                              ( 16U )
#define EXTI_IENR1_INTEN16_Msk                              ( 0x1UL << EXTI_IENR1_INTEN16_Pos )
#define EXTI_IENR1_INTEN16                                  ( EXTI_IENR1_INTEN16_Msk )


#define EXTI_IENR1_INTEN15_Pos                              ( 15U )
#define EXTI_IENR1_INTEN15_Msk                              ( 0x1UL << EXTI_IENR1_INTEN15_Pos )
#define EXTI_IENR1_INTEN15                                  ( EXTI_IENR1_INTEN15_Msk )


#define EXTI_IENR1_INTEN14_Pos                              ( 14U )
#define EXTI_IENR1_INTEN14_Msk                              ( 0x1UL << EXTI_IENR1_INTEN14_Pos )
#define EXTI_IENR1_INTEN14                                  ( EXTI_IENR1_INTEN14_Msk )


#define EXTI_IENR1_INTEN13_Pos                              ( 13U )
#define EXTI_IENR1_INTEN13_Msk                              ( 0x1UL << EXTI_IENR1_INTEN13_Pos )
#define EXTI_IENR1_INTEN13                                  ( EXTI_IENR1_INTEN13_Msk )


#define EXTI_IENR1_INTEN12_Pos                              ( 12U )
#define EXTI_IENR1_INTEN12_Msk                              ( 0x1UL << EXTI_IENR1_INTEN12_Pos )
#define EXTI_IENR1_INTEN12                                  ( EXTI_IENR1_INTEN12_Msk )


#define EXTI_IENR1_INTEN11_Pos                              ( 11U )
#define EXTI_IENR1_INTEN11_Msk                              ( 0x1UL << EXTI_IENR1_INTEN11_Pos )
#define EXTI_IENR1_INTEN11                                  ( EXTI_IENR1_INTEN11_Msk )


#define EXTI_IENR1_INTEN10_Pos                              ( 10U )
#define EXTI_IENR1_INTEN10_Msk                              ( 0x1UL << EXTI_IENR1_INTEN10_Pos )
#define EXTI_IENR1_INTEN10                                  ( EXTI_IENR1_INTEN10_Msk )


#define EXTI_IENR1_INTEN9_Pos                               ( 9U )
#define EXTI_IENR1_INTEN9_Msk                               ( 0x1UL << EXTI_IENR1_INTEN9_Pos )
#define EXTI_IENR1_INTEN9                                   ( EXTI_IENR1_INTEN9_Msk )


#define EXTI_IENR1_INTEN8_Pos                               ( 8U )
#define EXTI_IENR1_INTEN8_Msk                               ( 0x1UL << EXTI_IENR1_INTEN8_Pos )
#define EXTI_IENR1_INTEN8                                   ( EXTI_IENR1_INTEN8_Msk )


#define EXTI_IENR1_INTEN7_Pos                               ( 7U )
#define EXTI_IENR1_INTEN7_Msk                               ( 0x1UL << EXTI_IENR1_INTEN7_Pos )
#define EXTI_IENR1_INTEN7                                   ( EXTI_IENR1_INTEN7_Msk )


#define EXTI_IENR1_INTEN6_Pos                               ( 6U )
#define EXTI_IENR1_INTEN6_Msk                               ( 0x1UL << EXTI_IENR1_INTEN6_Pos )
#define EXTI_IENR1_INTEN6                                   ( EXTI_IENR1_INTEN6_Msk )


#define EXTI_IENR1_INTEN5_Pos                               ( 5U )
#define EXTI_IENR1_INTEN5_Msk                               ( 0x1UL << EXTI_IENR1_INTEN5_Pos )
#define EXTI_IENR1_INTEN5                                   ( EXTI_IENR1_INTEN5_Msk )


#define EXTI_IENR1_INTEN4_Pos                               ( 4U )
#define EXTI_IENR1_INTEN4_Msk                               ( 0x1UL << EXTI_IENR1_INTEN4_Pos )
#define EXTI_IENR1_INTEN4                                   ( EXTI_IENR1_INTEN4_Msk )


#define EXTI_IENR1_INTEN3_Pos                               ( 3U )
#define EXTI_IENR1_INTEN3_Msk                               ( 0x1UL << EXTI_IENR1_INTEN3_Pos )
#define EXTI_IENR1_INTEN3                                   ( EXTI_IENR1_INTEN3_Msk )


#define EXTI_IENR1_INTEN2_Pos                               ( 2U )
#define EXTI_IENR1_INTEN2_Msk                               ( 0x1UL << EXTI_IENR1_INTEN2_Pos )
#define EXTI_IENR1_INTEN2                                   ( EXTI_IENR1_INTEN2_Msk )


#define EXTI_IENR1_INTEN1_Pos                               ( 1U )
#define EXTI_IENR1_INTEN1_Msk                               ( 0x1UL << EXTI_IENR1_INTEN1_Pos )
#define EXTI_IENR1_INTEN1                                   ( EXTI_IENR1_INTEN1_Msk )


#define EXTI_IENR1_INTEN0_Pos                               ( 0U )
#define EXTI_IENR1_INTEN0_Msk                               ( 0x1UL << EXTI_IENR1_INTEN0_Pos )
#define EXTI_IENR1_INTEN0                                   ( EXTI_IENR1_INTEN0_Msk )



/***************  Bits definition for EXTI_IENR2  **********************/

#define EXTI_IENR2_INTEN34_Pos                              ( 2U )
#define EXTI_IENR2_INTEN34_Msk                              ( 0x1UL << EXTI_IENR2_INTEN34_Pos )
#define EXTI_IENR2_INTEN34                                  ( EXTI_IENR2_INTEN34_Msk )


#define EXTI_IENR2_INTEN33_Pos                              ( 1U )
#define EXTI_IENR2_INTEN33_Msk                              ( 0x1UL << EXTI_IENR2_INTEN33_Pos )
#define EXTI_IENR2_INTEN33                                  ( EXTI_IENR2_INTEN33_Msk )


#define EXTI_IENR2_INTEN32_Pos                              ( 0U )
#define EXTI_IENR2_INTEN32_Msk                              ( 0x1UL << EXTI_IENR2_INTEN32_Pos )
#define EXTI_IENR2_INTEN32                                  ( EXTI_IENR2_INTEN32_Msk )



/***************  Bits definition for EXTI_EENR1  **********************/

#define EXTI_EENR1_EVEN31_Pos                               ( 31U )
#define EXTI_EENR1_EVEN31_Msk                               ( 0x1UL << EXTI_EENR1_EVEN31_Pos )
#define EXTI_EENR1_EVEN31                                   ( EXTI_EENR1_EVEN31_Msk )


#define EXTI_EENR1_EVEN30_Pos                               ( 30U )
#define EXTI_EENR1_EVEN30_Msk                               ( 0x1UL << EXTI_EENR1_EVEN30_Pos )
#define EXTI_EENR1_EVEN30                                   ( EXTI_EENR1_EVEN30_Msk )


#define EXTI_EENR1_EVEN29_Pos                               ( 29U )
#define EXTI_EENR1_EVEN29_Msk                               ( 0x1UL << EXTI_EENR1_EVEN29_Pos )
#define EXTI_EENR1_EVEN29                                   ( EXTI_EENR1_EVEN29_Msk )


#define EXTI_EENR1_EVEN28_Pos                               ( 28U )
#define EXTI_EENR1_EVEN28_Msk                               ( 0x1UL << EXTI_EENR1_EVEN28_Pos )
#define EXTI_EENR1_EVEN28                                   ( EXTI_EENR1_EVEN28_Msk )


#define EXTI_EENR1_EVEN27_Pos                               ( 27U )
#define EXTI_EENR1_EVEN27_Msk                               ( 0x1UL << EXTI_EENR1_EVEN27_Pos )
#define EXTI_EENR1_EVEN27                                   ( EXTI_EENR1_EVEN27_Msk )


#define EXTI_EENR1_EVEN26_Pos                               ( 26U )
#define EXTI_EENR1_EVEN26_Msk                               ( 0x1UL << EXTI_EENR1_EVEN26_Pos )
#define EXTI_EENR1_EVEN26                                   ( EXTI_EENR1_EVEN26_Msk )


#define EXTI_EENR1_EVEN25_Pos                               ( 25U )
#define EXTI_EENR1_EVEN25_Msk                               ( 0x1UL << EXTI_EENR1_EVEN25_Pos )
#define EXTI_EENR1_EVEN25                                   ( EXTI_EENR1_EVEN25_Msk )


#define EXTI_EENR1_EVEN24_Pos                               ( 24U )
#define EXTI_EENR1_EVEN24_Msk                               ( 0x1UL << EXTI_EENR1_EVEN24_Pos )
#define EXTI_EENR1_EVEN24                                   ( EXTI_EENR1_EVEN24_Msk )


#define EXTI_EENR1_EVEN23_Pos                               ( 23U )
#define EXTI_EENR1_EVEN23_Msk                               ( 0x1UL << EXTI_EENR1_EVEN23_Pos )
#define EXTI_EENR1_EVEN23                                   ( EXTI_EENR1_EVEN23_Msk )


#define EXTI_EENR1_EVEN22_Pos                               ( 22U )
#define EXTI_EENR1_EVEN22_Msk                               ( 0x1UL << EXTI_EENR1_EVEN22_Pos )
#define EXTI_EENR1_EVEN22                                   ( EXTI_EENR1_EVEN22_Msk )


#define EXTI_EENR1_EVEN21_Pos                               ( 21U )
#define EXTI_EENR1_EVEN21_Msk                               ( 0x1UL << EXTI_EENR1_EVEN21_Pos )
#define EXTI_EENR1_EVEN21                                   ( EXTI_EENR1_EVEN21_Msk )


#define EXTI_EENR1_EVEN20_Pos                               ( 20U )
#define EXTI_EENR1_EVEN20_Msk                               ( 0x1UL << EXTI_EENR1_EVEN20_Pos )
#define EXTI_EENR1_EVEN20                                   ( EXTI_EENR1_EVEN20_Msk )


#define EXTI_EENR1_EVEN19_Pos                               ( 19U )
#define EXTI_EENR1_EVEN19_Msk                               ( 0x1UL << EXTI_EENR1_EVEN19_Pos )
#define EXTI_EENR1_EVEN19                                   ( EXTI_EENR1_EVEN19_Msk )


#define EXTI_EENR1_EVEN18_Pos                               ( 18U )
#define EXTI_EENR1_EVEN18_Msk                               ( 0x1UL << EXTI_EENR1_EVEN18_Pos )
#define EXTI_EENR1_EVEN18                                   ( EXTI_EENR1_EVEN18_Msk )


#define EXTI_EENR1_EVEN17_Pos                               ( 17U )
#define EXTI_EENR1_EVEN17_Msk                               ( 0x1UL << EXTI_EENR1_EVEN17_Pos )
#define EXTI_EENR1_EVEN17                                   ( EXTI_EENR1_EVEN17_Msk )


#define EXTI_EENR1_EVEN16_Pos                               ( 16U )
#define EXTI_EENR1_EVEN16_Msk                               ( 0x1UL << EXTI_EENR1_EVEN16_Pos )
#define EXTI_EENR1_EVEN16                                   ( EXTI_EENR1_EVEN16_Msk )


#define EXTI_EENR1_EVEN15_Pos                               ( 15U )
#define EXTI_EENR1_EVEN15_Msk                               ( 0x1UL << EXTI_EENR1_EVEN15_Pos )
#define EXTI_EENR1_EVEN15                                   ( EXTI_EENR1_EVEN15_Msk )


#define EXTI_EENR1_EVEN14_Pos                               ( 14U )
#define EXTI_EENR1_EVEN14_Msk                               ( 0x1UL << EXTI_EENR1_EVEN14_Pos )
#define EXTI_EENR1_EVEN14                                   ( EXTI_EENR1_EVEN14_Msk )


#define EXTI_EENR1_EVEN13_Pos                               ( 13U )
#define EXTI_EENR1_EVEN13_Msk                               ( 0x1UL << EXTI_EENR1_EVEN13_Pos )
#define EXTI_EENR1_EVEN13                                   ( EXTI_EENR1_EVEN13_Msk )


#define EXTI_EENR1_EVEN12_Pos                               ( 12U )
#define EXTI_EENR1_EVEN12_Msk                               ( 0x1UL << EXTI_EENR1_EVEN12_Pos )
#define EXTI_EENR1_EVEN12                                   ( EXTI_EENR1_EVEN12_Msk )


#define EXTI_EENR1_EVEN11_Pos                               ( 11U )
#define EXTI_EENR1_EVEN11_Msk                               ( 0x1UL << EXTI_EENR1_EVEN11_Pos )
#define EXTI_EENR1_EVEN11                                   ( EXTI_EENR1_EVEN11_Msk )


#define EXTI_EENR1_EVEN10_Pos                               ( 10U )
#define EXTI_EENR1_EVEN10_Msk                               ( 0x1UL << EXTI_EENR1_EVEN10_Pos )
#define EXTI_EENR1_EVEN10                                   ( EXTI_EENR1_EVEN10_Msk )


#define EXTI_EENR1_EVEN9_Pos                                ( 9U )
#define EXTI_EENR1_EVEN9_Msk                                ( 0x1UL << EXTI_EENR1_EVEN9_Pos )
#define EXTI_EENR1_EVEN9                                    ( EXTI_EENR1_EVEN9_Msk )


#define EXTI_EENR1_EVEN8_Pos                                ( 8U )
#define EXTI_EENR1_EVEN8_Msk                                ( 0x1UL << EXTI_EENR1_EVEN8_Pos )
#define EXTI_EENR1_EVEN8                                    ( EXTI_EENR1_EVEN8_Msk )


#define EXTI_EENR1_EVEN7_Pos                                ( 7U )
#define EXTI_EENR1_EVEN7_Msk                                ( 0x1UL << EXTI_EENR1_EVEN7_Pos )
#define EXTI_EENR1_EVEN7                                    ( EXTI_EENR1_EVEN7_Msk )


#define EXTI_EENR1_EVEN6_Pos                                ( 6U )
#define EXTI_EENR1_EVEN6_Msk                                ( 0x1UL << EXTI_EENR1_EVEN6_Pos )
#define EXTI_EENR1_EVEN6                                    ( EXTI_EENR1_EVEN6_Msk )


#define EXTI_EENR1_EVEN5_Pos                                ( 5U )
#define EXTI_EENR1_EVEN5_Msk                                ( 0x1UL << EXTI_EENR1_EVEN5_Pos )
#define EXTI_EENR1_EVEN5                                    ( EXTI_EENR1_EVEN5_Msk )


#define EXTI_EENR1_EVEN4_Pos                                ( 4U )
#define EXTI_EENR1_EVEN4_Msk                                ( 0x1UL << EXTI_EENR1_EVEN4_Pos )
#define EXTI_EENR1_EVEN4                                    ( EXTI_EENR1_EVEN4_Msk )


#define EXTI_EENR1_EVEN3_Pos                                ( 3U )
#define EXTI_EENR1_EVEN3_Msk                                ( 0x1UL << EXTI_EENR1_EVEN3_Pos )
#define EXTI_EENR1_EVEN3                                    ( EXTI_EENR1_EVEN3_Msk )


#define EXTI_EENR1_EVEN2_Pos                                ( 2U )
#define EXTI_EENR1_EVEN2_Msk                                ( 0x1UL << EXTI_EENR1_EVEN2_Pos )
#define EXTI_EENR1_EVEN2                                    ( EXTI_EENR1_EVEN2_Msk )


#define EXTI_EENR1_EVEN1_Pos                                ( 1U )
#define EXTI_EENR1_EVEN1_Msk                                ( 0x1UL << EXTI_EENR1_EVEN1_Pos )
#define EXTI_EENR1_EVEN1                                    ( EXTI_EENR1_EVEN1_Msk )


#define EXTI_EENR1_EVEN0_Pos                                ( 0U )
#define EXTI_EENR1_EVEN0_Msk                                ( 0x1UL << EXTI_EENR1_EVEN0_Pos )
#define EXTI_EENR1_EVEN0                                    ( EXTI_EENR1_EVEN0_Msk )



/***************  Bits definition for EXTI_EENR2  **********************/

#define EXTI_EENR2_EVEN34_Pos                               ( 2U )
#define EXTI_EENR2_EVEN34_Msk                               ( 0x1UL << EXTI_EENR2_EVEN34_Pos )
#define EXTI_EENR2_EVEN34                                   ( EXTI_EENR2_EVEN34_Msk )


#define EXTI_EENR2_EVEN33_Pos                               ( 1U )
#define EXTI_EENR2_EVEN33_Msk                               ( 0x1UL << EXTI_EENR2_EVEN33_Pos )
#define EXTI_EENR2_EVEN33                                   ( EXTI_EENR2_EVEN33_Msk )


#define EXTI_EENR2_EVEN32_Pos                               ( 0U )
#define EXTI_EENR2_EVEN32_Msk                               ( 0x1UL << EXTI_EENR2_EVEN32_Pos )
#define EXTI_EENR2_EVEN32                                   ( EXTI_EENR2_EVEN32_Msk )



/***************  Bits definition for EXTI_RTENR1  **********************/

#define EXTI_RTENR1_RTEN31_Pos                              ( 31U )
#define EXTI_RTENR1_RTEN31_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN31_Pos )
#define EXTI_RTENR1_RTEN31                                  ( EXTI_RTENR1_RTEN31_Msk )


#define EXTI_RTENR1_RTEN30_Pos                              ( 30U )
#define EXTI_RTENR1_RTEN30_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN30_Pos )
#define EXTI_RTENR1_RTEN30                                  ( EXTI_RTENR1_RTEN30_Msk )


#define EXTI_RTENR1_RTEN29_Pos                              ( 29U )
#define EXTI_RTENR1_RTEN29_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN29_Pos )
#define EXTI_RTENR1_RTEN29                                  ( EXTI_RTENR1_RTEN29_Msk )


#define EXTI_RTENR1_RTEN28_Pos                              ( 28U )
#define EXTI_RTENR1_RTEN28_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN28_Pos )
#define EXTI_RTENR1_RTEN28                                  ( EXTI_RTENR1_RTEN28_Msk )


#define EXTI_RTENR1_RTEN27_Pos                              ( 27U )
#define EXTI_RTENR1_RTEN27_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN27_Pos )
#define EXTI_RTENR1_RTEN27                                  ( EXTI_RTENR1_RTEN27_Msk )


#define EXTI_RTENR1_RTEN26_Pos                              ( 26U )
#define EXTI_RTENR1_RTEN26_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN26_Pos )
#define EXTI_RTENR1_RTEN26                                  ( EXTI_RTENR1_RTEN26_Msk )


#define EXTI_RTENR1_RTEN25_Pos                              ( 25U )
#define EXTI_RTENR1_RTEN25_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN25_Pos )
#define EXTI_RTENR1_RTEN25                                  ( EXTI_RTENR1_RTEN25_Msk )


#define EXTI_RTENR1_RTEN24_Pos                              ( 24U )
#define EXTI_RTENR1_RTEN24_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN24_Pos )
#define EXTI_RTENR1_RTEN24                                  ( EXTI_RTENR1_RTEN24_Msk )


#define EXTI_RTENR1_RTEN23_Pos                              ( 23U )
#define EXTI_RTENR1_RTEN23_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN23_Pos )
#define EXTI_RTENR1_RTEN23                                  ( EXTI_RTENR1_RTEN23_Msk )


#define EXTI_RTENR1_RTEN22_Pos                              ( 22U )
#define EXTI_RTENR1_RTEN22_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN22_Pos )
#define EXTI_RTENR1_RTEN22                                  ( EXTI_RTENR1_RTEN22_Msk )


#define EXTI_RTENR1_RTEN21_Pos                              ( 21U )
#define EXTI_RTENR1_RTEN21_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN21_Pos )
#define EXTI_RTENR1_RTEN21                                  ( EXTI_RTENR1_RTEN21_Msk )


#define EXTI_RTENR1_RTEN20_Pos                              ( 20U )
#define EXTI_RTENR1_RTEN20_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN20_Pos )
#define EXTI_RTENR1_RTEN20                                  ( EXTI_RTENR1_RTEN20_Msk )


#define EXTI_RTENR1_RTEN19_Pos                              ( 19U )
#define EXTI_RTENR1_RTEN19_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN19_Pos )
#define EXTI_RTENR1_RTEN19                                  ( EXTI_RTENR1_RTEN19_Msk )


#define EXTI_RTENR1_RTEN18_Pos                              ( 18U )
#define EXTI_RTENR1_RTEN18_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN18_Pos )
#define EXTI_RTENR1_RTEN18                                  ( EXTI_RTENR1_RTEN18_Msk )


#define EXTI_RTENR1_RTEN17_Pos                              ( 17U )
#define EXTI_RTENR1_RTEN17_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN17_Pos )
#define EXTI_RTENR1_RTEN17                                  ( EXTI_RTENR1_RTEN17_Msk )


#define EXTI_RTENR1_RTEN16_Pos                              ( 16U )
#define EXTI_RTENR1_RTEN16_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN16_Pos )
#define EXTI_RTENR1_RTEN16                                  ( EXTI_RTENR1_RTEN16_Msk )


#define EXTI_RTENR1_RTEN15_Pos                              ( 15U )
#define EXTI_RTENR1_RTEN15_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN15_Pos )
#define EXTI_RTENR1_RTEN15                                  ( EXTI_RTENR1_RTEN15_Msk )


#define EXTI_RTENR1_RTEN14_Pos                              ( 14U )
#define EXTI_RTENR1_RTEN14_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN14_Pos )
#define EXTI_RTENR1_RTEN14                                  ( EXTI_RTENR1_RTEN14_Msk )


#define EXTI_RTENR1_RTEN13_Pos                              ( 13U )
#define EXTI_RTENR1_RTEN13_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN13_Pos )
#define EXTI_RTENR1_RTEN13                                  ( EXTI_RTENR1_RTEN13_Msk )


#define EXTI_RTENR1_RTEN12_Pos                              ( 12U )
#define EXTI_RTENR1_RTEN12_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN12_Pos )
#define EXTI_RTENR1_RTEN12                                  ( EXTI_RTENR1_RTEN12_Msk )


#define EXTI_RTENR1_RTEN11_Pos                              ( 11U )
#define EXTI_RTENR1_RTEN11_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN11_Pos )
#define EXTI_RTENR1_RTEN11                                  ( EXTI_RTENR1_RTEN11_Msk )


#define EXTI_RTENR1_RTEN10_Pos                              ( 10U )
#define EXTI_RTENR1_RTEN10_Msk                              ( 0x1UL << EXTI_RTENR1_RTEN10_Pos )
#define EXTI_RTENR1_RTEN10                                  ( EXTI_RTENR1_RTEN10_Msk )


#define EXTI_RTENR1_RTEN9_Pos                               ( 9U )
#define EXTI_RTENR1_RTEN9_Msk                               ( 0x1UL << EXTI_RTENR1_RTEN9_Pos )
#define EXTI_RTENR1_RTEN9                                   ( EXTI_RTENR1_RTEN9_Msk )


#define EXTI_RTENR1_RTEN8_Pos                               ( 8U )
#define EXTI_RTENR1_RTEN8_Msk                               ( 0x1UL << EXTI_RTENR1_RTEN8_Pos )
#define EXTI_RTENR1_RTEN8                                   ( EXTI_RTENR1_RTEN8_Msk )


#define EXTI_RTENR1_RTEN7_Pos                               ( 7U )
#define EXTI_RTENR1_RTEN7_Msk                               ( 0x1UL << EXTI_RTENR1_RTEN7_Pos )
#define EXTI_RTENR1_RTEN7                                   ( EXTI_RTENR1_RTEN7_Msk )


#define EXTI_RTENR1_RTEN6_Pos                               ( 6U )
#define EXTI_RTENR1_RTEN6_Msk                               ( 0x1UL << EXTI_RTENR1_RTEN6_Pos )
#define EXTI_RTENR1_RTEN6                                   ( EXTI_RTENR1_RTEN6_Msk )


#define EXTI_RTENR1_RTEN5_Pos                               ( 5U )
#define EXTI_RTENR1_RTEN5_Msk                               ( 0x1UL << EXTI_RTENR1_RTEN5_Pos )
#define EXTI_RTENR1_RTEN5                                   ( EXTI_RTENR1_RTEN5_Msk )


#define EXTI_RTENR1_RTEN4_Pos                               ( 4U )
#define EXTI_RTENR1_RTEN4_Msk                               ( 0x1UL << EXTI_RTENR1_RTEN4_Pos )
#define EXTI_RTENR1_RTEN4                                   ( EXTI_RTENR1_RTEN4_Msk )


#define EXTI_RTENR1_RTEN3_Pos                               ( 3U )
#define EXTI_RTENR1_RTEN3_Msk                               ( 0x1UL << EXTI_RTENR1_RTEN3_Pos )
#define EXTI_RTENR1_RTEN3                                   ( EXTI_RTENR1_RTEN3_Msk )


#define EXTI_RTENR1_RTEN2_Pos                               ( 2U )
#define EXTI_RTENR1_RTEN2_Msk                               ( 0x1UL << EXTI_RTENR1_RTEN2_Pos )
#define EXTI_RTENR1_RTEN2                                   ( EXTI_RTENR1_RTEN2_Msk )


#define EXTI_RTENR1_RTEN1_Pos                               ( 1U )
#define EXTI_RTENR1_RTEN1_Msk                               ( 0x1UL << EXTI_RTENR1_RTEN1_Pos )
#define EXTI_RTENR1_RTEN1                                   ( EXTI_RTENR1_RTEN1_Msk )


#define EXTI_RTENR1_RTEN0_Pos                               ( 0U )
#define EXTI_RTENR1_RTEN0_Msk                               ( 0x1UL << EXTI_RTENR1_RTEN0_Pos )
#define EXTI_RTENR1_RTEN0                                   ( EXTI_RTENR1_RTEN0_Msk )



/***************  Bits definition for EXTI_RTENR2  **********************/

#define EXTI_RTENR2_RTEN34_Pos                              ( 2U )
#define EXTI_RTENR2_RTEN34_Msk                              ( 0x1UL << EXTI_RTENR2_RTEN34_Pos )
#define EXTI_RTENR2_RTEN34                                  ( EXTI_RTENR2_RTEN34_Msk )


#define EXTI_RTENR2_RTEN33_Pos                              ( 1U )
#define EXTI_RTENR2_RTEN33_Msk                              ( 0x1UL << EXTI_RTENR2_RTEN33_Pos )
#define EXTI_RTENR2_RTEN33                                  ( EXTI_RTENR2_RTEN33_Msk )


#define EXTI_RTENR2_RTEN32_Pos                              ( 0U )
#define EXTI_RTENR2_RTEN32_Msk                              ( 0x1UL << EXTI_RTENR2_RTEN32_Pos )
#define EXTI_RTENR2_RTEN32                                  ( EXTI_RTENR2_RTEN32_Msk )



/***************  Bits definition for EXTI_FTENR1  **********************/

#define EXTI_FTENR1_FTEN31_Pos                              ( 31U )
#define EXTI_FTENR1_FTEN31_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN31_Pos )
#define EXTI_FTENR1_FTEN31                                  ( EXTI_FTENR1_FTEN31_Msk )


#define EXTI_FTENR1_FTEN30_Pos                              ( 30U )
#define EXTI_FTENR1_FTEN30_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN30_Pos )
#define EXTI_FTENR1_FTEN30                                  ( EXTI_FTENR1_FTEN30_Msk )


#define EXTI_FTENR1_FTEN29_Pos                              ( 29U )
#define EXTI_FTENR1_FTEN29_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN29_Pos )
#define EXTI_FTENR1_FTEN29                                  ( EXTI_FTENR1_FTEN29_Msk )


#define EXTI_FTENR1_FTEN28_Pos                              ( 28U )
#define EXTI_FTENR1_FTEN28_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN28_Pos )
#define EXTI_FTENR1_FTEN28                                  ( EXTI_FTENR1_FTEN28_Msk )


#define EXTI_FTENR1_FTEN27_Pos                              ( 27U )
#define EXTI_FTENR1_FTEN27_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN27_Pos )
#define EXTI_FTENR1_FTEN27                                  ( EXTI_FTENR1_FTEN27_Msk )


#define EXTI_FTENR1_FTEN26_Pos                              ( 26U )
#define EXTI_FTENR1_FTEN26_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN26_Pos )
#define EXTI_FTENR1_FTEN26                                  ( EXTI_FTENR1_FTEN26_Msk )


#define EXTI_FTENR1_FTEN25_Pos                              ( 25U )
#define EXTI_FTENR1_FTEN25_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN25_Pos )
#define EXTI_FTENR1_FTEN25                                  ( EXTI_FTENR1_FTEN25_Msk )


#define EXTI_FTENR1_FTEN24_Pos                              ( 24U )
#define EXTI_FTENR1_FTEN24_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN24_Pos )
#define EXTI_FTENR1_FTEN24                                  ( EXTI_FTENR1_FTEN24_Msk )


#define EXTI_FTENR1_FTEN23_Pos                              ( 23U )
#define EXTI_FTENR1_FTEN23_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN23_Pos )
#define EXTI_FTENR1_FTEN23                                  ( EXTI_FTENR1_FTEN23_Msk )


#define EXTI_FTENR1_FTEN22_Pos                              ( 22U )
#define EXTI_FTENR1_FTEN22_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN22_Pos )
#define EXTI_FTENR1_FTEN22                                  ( EXTI_FTENR1_FTEN22_Msk )


#define EXTI_FTENR1_FTEN21_Pos                              ( 21U )
#define EXTI_FTENR1_FTEN21_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN21_Pos )
#define EXTI_FTENR1_FTEN21                                  ( EXTI_FTENR1_FTEN21_Msk )


#define EXTI_FTENR1_FTEN20_Pos                              ( 20U )
#define EXTI_FTENR1_FTEN20_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN20_Pos )
#define EXTI_FTENR1_FTEN20                                  ( EXTI_FTENR1_FTEN20_Msk )


#define EXTI_FTENR1_FTEN19_Pos                              ( 19U )
#define EXTI_FTENR1_FTEN19_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN19_Pos )
#define EXTI_FTENR1_FTEN19                                  ( EXTI_FTENR1_FTEN19_Msk )


#define EXTI_FTENR1_FTEN18_Pos                              ( 18U )
#define EXTI_FTENR1_FTEN18_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN18_Pos )
#define EXTI_FTENR1_FTEN18                                  ( EXTI_FTENR1_FTEN18_Msk )


#define EXTI_FTENR1_FTEN17_Pos                              ( 17U )
#define EXTI_FTENR1_FTEN17_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN17_Pos )
#define EXTI_FTENR1_FTEN17                                  ( EXTI_FTENR1_FTEN17_Msk )


#define EXTI_FTENR1_FTEN16_Pos                              ( 16U )
#define EXTI_FTENR1_FTEN16_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN16_Pos )
#define EXTI_FTENR1_FTEN16                                  ( EXTI_FTENR1_FTEN16_Msk )


#define EXTI_FTENR1_FTEN15_Pos                              ( 15U )
#define EXTI_FTENR1_FTEN15_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN15_Pos )
#define EXTI_FTENR1_FTEN15                                  ( EXTI_FTENR1_FTEN15_Msk )


#define EXTI_FTENR1_FTEN14_Pos                              ( 14U )
#define EXTI_FTENR1_FTEN14_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN14_Pos )
#define EXTI_FTENR1_FTEN14                                  ( EXTI_FTENR1_FTEN14_Msk )


#define EXTI_FTENR1_FTEN13_Pos                              ( 13U )
#define EXTI_FTENR1_FTEN13_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN13_Pos )
#define EXTI_FTENR1_FTEN13                                  ( EXTI_FTENR1_FTEN13_Msk )


#define EXTI_FTENR1_FTEN12_Pos                              ( 12U )
#define EXTI_FTENR1_FTEN12_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN12_Pos )
#define EXTI_FTENR1_FTEN12                                  ( EXTI_FTENR1_FTEN12_Msk )


#define EXTI_FTENR1_FTEN11_Pos                              ( 11U )
#define EXTI_FTENR1_FTEN11_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN11_Pos )
#define EXTI_FTENR1_FTEN11                                  ( EXTI_FTENR1_FTEN11_Msk )


#define EXTI_FTENR1_FTEN10_Pos                              ( 10U )
#define EXTI_FTENR1_FTEN10_Msk                              ( 0x1UL << EXTI_FTENR1_FTEN10_Pos )
#define EXTI_FTENR1_FTEN10                                  ( EXTI_FTENR1_FTEN10_Msk )


#define EXTI_FTENR1_FTEN9_Pos                               ( 9U )
#define EXTI_FTENR1_FTEN9_Msk                               ( 0x1UL << EXTI_FTENR1_FTEN9_Pos )
#define EXTI_FTENR1_FTEN9                                   ( EXTI_FTENR1_FTEN9_Msk )


#define EXTI_FTENR1_FTEN8_Pos                               ( 8U )
#define EXTI_FTENR1_FTEN8_Msk                               ( 0x1UL << EXTI_FTENR1_FTEN8_Pos )
#define EXTI_FTENR1_FTEN8                                   ( EXTI_FTENR1_FTEN8_Msk )


#define EXTI_FTENR1_FTEN7_Pos                               ( 7U )
#define EXTI_FTENR1_FTEN7_Msk                               ( 0x1UL << EXTI_FTENR1_FTEN7_Pos )
#define EXTI_FTENR1_FTEN7                                   ( EXTI_FTENR1_FTEN7_Msk )


#define EXTI_FTENR1_FTEN6_Pos                               ( 6U )
#define EXTI_FTENR1_FTEN6_Msk                               ( 0x1UL << EXTI_FTENR1_FTEN6_Pos )
#define EXTI_FTENR1_FTEN6                                   ( EXTI_FTENR1_FTEN6_Msk )


#define EXTI_FTENR1_FTEN5_Pos                               ( 5U )
#define EXTI_FTENR1_FTEN5_Msk                               ( 0x1UL << EXTI_FTENR1_FTEN5_Pos )
#define EXTI_FTENR1_FTEN5                                   ( EXTI_FTENR1_FTEN5_Msk )


#define EXTI_FTENR1_FTEN4_Pos                               ( 4U )
#define EXTI_FTENR1_FTEN4_Msk                               ( 0x1UL << EXTI_FTENR1_FTEN4_Pos )
#define EXTI_FTENR1_FTEN4                                   ( EXTI_FTENR1_FTEN4_Msk )


#define EXTI_FTENR1_FTEN3_Pos                               ( 3U )
#define EXTI_FTENR1_FTEN3_Msk                               ( 0x1UL << EXTI_FTENR1_FTEN3_Pos )
#define EXTI_FTENR1_FTEN3                                   ( EXTI_FTENR1_FTEN3_Msk )


#define EXTI_FTENR1_FTEN2_Pos                               ( 2U )
#define EXTI_FTENR1_FTEN2_Msk                               ( 0x1UL << EXTI_FTENR1_FTEN2_Pos )
#define EXTI_FTENR1_FTEN2                                   ( EXTI_FTENR1_FTEN2_Msk )


#define EXTI_FTENR1_FTEN1_Pos                               ( 1U )
#define EXTI_FTENR1_FTEN1_Msk                               ( 0x1UL << EXTI_FTENR1_FTEN1_Pos )
#define EXTI_FTENR1_FTEN1                                   ( EXTI_FTENR1_FTEN1_Msk )


#define EXTI_FTENR1_FTEN0_Pos                               ( 0U )
#define EXTI_FTENR1_FTEN0_Msk                               ( 0x1UL << EXTI_FTENR1_FTEN0_Pos )
#define EXTI_FTENR1_FTEN0                                   ( EXTI_FTENR1_FTEN0_Msk )



/***************  Bits definition for EXTI_FTENR2  **********************/

#define EXTI_FTENR2_FTEN34_Pos                              ( 2U )
#define EXTI_FTENR2_FTEN34_Msk                              ( 0x1UL << EXTI_FTENR2_FTEN34_Pos )
#define EXTI_FTENR2_FTEN34                                  ( EXTI_FTENR2_FTEN34_Msk )


#define EXTI_FTENR2_FTEN33_Pos                              ( 1U )
#define EXTI_FTENR2_FTEN33_Msk                              ( 0x1UL << EXTI_FTENR2_FTEN33_Pos )
#define EXTI_FTENR2_FTEN33                                  ( EXTI_FTENR2_FTEN33_Msk )


#define EXTI_FTENR2_FTEN32_Pos                              ( 0U )
#define EXTI_FTENR2_FTEN32_Msk                              ( 0x1UL << EXTI_FTENR2_FTEN32_Pos )
#define EXTI_FTENR2_FTEN32                                  ( EXTI_FTENR2_FTEN32_Msk )



/***************  Bits definition for EXTI_SWIER1  **********************/

#define EXTI_SWIER1_SWIE31_Pos                              ( 31U )
#define EXTI_SWIER1_SWIE31_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE31_Pos )
#define EXTI_SWIER1_SWIE31                                  ( EXTI_SWIER1_SWIE31_Msk )


#define EXTI_SWIER1_SWIE30_Pos                              ( 30U )
#define EXTI_SWIER1_SWIE30_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE30_Pos )
#define EXTI_SWIER1_SWIE30                                  ( EXTI_SWIER1_SWIE30_Msk )


#define EXTI_SWIER1_SWIE29_Pos                              ( 29U )
#define EXTI_SWIER1_SWIE29_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE29_Pos )
#define EXTI_SWIER1_SWIE29                                  ( EXTI_SWIER1_SWIE29_Msk )


#define EXTI_SWIER1_SWIE28_Pos                              ( 28U )
#define EXTI_SWIER1_SWIE28_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE28_Pos )
#define EXTI_SWIER1_SWIE28                                  ( EXTI_SWIER1_SWIE28_Msk )


#define EXTI_SWIER1_SWIE27_Pos                              ( 27U )
#define EXTI_SWIER1_SWIE27_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE27_Pos )
#define EXTI_SWIER1_SWIE27                                  ( EXTI_SWIER1_SWIE27_Msk )


#define EXTI_SWIER1_SWIE26_Pos                              ( 26U )
#define EXTI_SWIER1_SWIE26_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE26_Pos )
#define EXTI_SWIER1_SWIE26                                  ( EXTI_SWIER1_SWIE26_Msk )


#define EXTI_SWIER1_SWIE25_Pos                              ( 25U )
#define EXTI_SWIER1_SWIE25_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE25_Pos )
#define EXTI_SWIER1_SWIE25                                  ( EXTI_SWIER1_SWIE25_Msk )


#define EXTI_SWIER1_SWIE24_Pos                              ( 24U )
#define EXTI_SWIER1_SWIE24_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE24_Pos )
#define EXTI_SWIER1_SWIE24                                  ( EXTI_SWIER1_SWIE24_Msk )


#define EXTI_SWIER1_SWIE23_Pos                              ( 23U )
#define EXTI_SWIER1_SWIE23_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE23_Pos )
#define EXTI_SWIER1_SWIE23                                  ( EXTI_SWIER1_SWIE23_Msk )


#define EXTI_SWIER1_SWIE22_Pos                              ( 22U )
#define EXTI_SWIER1_SWIE22_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE22_Pos )
#define EXTI_SWIER1_SWIE22                                  ( EXTI_SWIER1_SWIE22_Msk )


#define EXTI_SWIER1_SWIE21_Pos                              ( 21U )
#define EXTI_SWIER1_SWIE21_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE21_Pos )
#define EXTI_SWIER1_SWIE21                                  ( EXTI_SWIER1_SWIE21_Msk )


#define EXTI_SWIER1_SWIE20_Pos                              ( 20U )
#define EXTI_SWIER1_SWIE20_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE20_Pos )
#define EXTI_SWIER1_SWIE20                                  ( EXTI_SWIER1_SWIE20_Msk )


#define EXTI_SWIER1_SWIE19_Pos                              ( 19U )
#define EXTI_SWIER1_SWIE19_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE19_Pos )
#define EXTI_SWIER1_SWIE19                                  ( EXTI_SWIER1_SWIE19_Msk )


#define EXTI_SWIER1_SWIE18_Pos                              ( 18U )
#define EXTI_SWIER1_SWIE18_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE18_Pos )
#define EXTI_SWIER1_SWIE18                                  ( EXTI_SWIER1_SWIE18_Msk )


#define EXTI_SWIER1_SWIE17_Pos                              ( 17U )
#define EXTI_SWIER1_SWIE17_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE17_Pos )
#define EXTI_SWIER1_SWIE17                                  ( EXTI_SWIER1_SWIE17_Msk )


#define EXTI_SWIER1_SWIE16_Pos                              ( 16U )
#define EXTI_SWIER1_SWIE16_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE16_Pos )
#define EXTI_SWIER1_SWIE16                                  ( EXTI_SWIER1_SWIE16_Msk )


#define EXTI_SWIER1_SWIE15_Pos                              ( 15U )
#define EXTI_SWIER1_SWIE15_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE15_Pos )
#define EXTI_SWIER1_SWIE15                                  ( EXTI_SWIER1_SWIE15_Msk )


#define EXTI_SWIER1_SWIE14_Pos                              ( 14U )
#define EXTI_SWIER1_SWIE14_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE14_Pos )
#define EXTI_SWIER1_SWIE14                                  ( EXTI_SWIER1_SWIE14_Msk )


#define EXTI_SWIER1_SWIE13_Pos                              ( 13U )
#define EXTI_SWIER1_SWIE13_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE13_Pos )
#define EXTI_SWIER1_SWIE13                                  ( EXTI_SWIER1_SWIE13_Msk )


#define EXTI_SWIER1_SWIE12_Pos                              ( 12U )
#define EXTI_SWIER1_SWIE12_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE12_Pos )
#define EXTI_SWIER1_SWIE12                                  ( EXTI_SWIER1_SWIE12_Msk )


#define EXTI_SWIER1_SWIE11_Pos                              ( 11U )
#define EXTI_SWIER1_SWIE11_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE11_Pos )
#define EXTI_SWIER1_SWIE11                                  ( EXTI_SWIER1_SWIE11_Msk )


#define EXTI_SWIER1_SWIE10_Pos                              ( 10U )
#define EXTI_SWIER1_SWIE10_Msk                              ( 0x1UL << EXTI_SWIER1_SWIE10_Pos )
#define EXTI_SWIER1_SWIE10                                  ( EXTI_SWIER1_SWIE10_Msk )


#define EXTI_SWIER1_SWIE9_Pos                               ( 9U )
#define EXTI_SWIER1_SWIE9_Msk                               ( 0x1UL << EXTI_SWIER1_SWIE9_Pos )
#define EXTI_SWIER1_SWIE9                                   ( EXTI_SWIER1_SWIE9_Msk )


#define EXTI_SWIER1_SWIE8_Pos                               ( 8U )
#define EXTI_SWIER1_SWIE8_Msk                               ( 0x1UL << EXTI_SWIER1_SWIE8_Pos )
#define EXTI_SWIER1_SWIE8                                   ( EXTI_SWIER1_SWIE8_Msk )


#define EXTI_SWIER1_SWIE7_Pos                               ( 7U )
#define EXTI_SWIER1_SWIE7_Msk                               ( 0x1UL << EXTI_SWIER1_SWIE7_Pos )
#define EXTI_SWIER1_SWIE7                                   ( EXTI_SWIER1_SWIE7_Msk )


#define EXTI_SWIER1_SWIE6_Pos                               ( 6U )
#define EXTI_SWIER1_SWIE6_Msk                               ( 0x1UL << EXTI_SWIER1_SWIE6_Pos )
#define EXTI_SWIER1_SWIE6                                   ( EXTI_SWIER1_SWIE6_Msk )


#define EXTI_SWIER1_SWIE5_Pos                               ( 5U )
#define EXTI_SWIER1_SWIE5_Msk                               ( 0x1UL << EXTI_SWIER1_SWIE5_Pos )
#define EXTI_SWIER1_SWIE5                                   ( EXTI_SWIER1_SWIE5_Msk )


#define EXTI_SWIER1_SWIE4_Pos                               ( 4U )
#define EXTI_SWIER1_SWIE4_Msk                               ( 0x1UL << EXTI_SWIER1_SWIE4_Pos )
#define EXTI_SWIER1_SWIE4                                   ( EXTI_SWIER1_SWIE4_Msk )


#define EXTI_SWIER1_SWIE3_Pos                               ( 3U )
#define EXTI_SWIER1_SWIE3_Msk                               ( 0x1UL << EXTI_SWIER1_SWIE3_Pos )
#define EXTI_SWIER1_SWIE3                                   ( EXTI_SWIER1_SWIE3_Msk )


#define EXTI_SWIER1_SWIE2_Pos                               ( 2U )
#define EXTI_SWIER1_SWIE2_Msk                               ( 0x1UL << EXTI_SWIER1_SWIE2_Pos )
#define EXTI_SWIER1_SWIE2                                   ( EXTI_SWIER1_SWIE2_Msk )


#define EXTI_SWIER1_SWIE1_Pos                               ( 1U )
#define EXTI_SWIER1_SWIE1_Msk                               ( 0x1UL << EXTI_SWIER1_SWIE1_Pos )
#define EXTI_SWIER1_SWIE1                                   ( EXTI_SWIER1_SWIE1_Msk )


#define EXTI_SWIER1_SWIE0_Pos                               ( 0U )
#define EXTI_SWIER1_SWIE0_Msk                               ( 0x1UL << EXTI_SWIER1_SWIE0_Pos )
#define EXTI_SWIER1_SWIE0                                   ( EXTI_SWIER1_SWIE0_Msk )



/***************  Bits definition for EXTI_SWIER2  **********************/

#define EXTI_SWIER2_SWIE34_Pos                              ( 2U )
#define EXTI_SWIER2_SWIE34_Msk                              ( 0x1UL << EXTI_SWIER2_SWIE34_Pos )
#define EXTI_SWIER2_SWIE34                                  ( EXTI_SWIER2_SWIE34_Msk )


#define EXTI_SWIER2_SWIE33_Pos                              ( 1U )
#define EXTI_SWIER2_SWIE33_Msk                              ( 0x1UL << EXTI_SWIER2_SWIE33_Pos )
#define EXTI_SWIER2_SWIE33                                  ( EXTI_SWIER2_SWIE33_Msk )


#define EXTI_SWIER2_SWIE32_Pos                              ( 0U )
#define EXTI_SWIER2_SWIE32_Msk                              ( 0x1UL << EXTI_SWIER2_SWIE32_Pos )
#define EXTI_SWIER2_SWIE32                                  ( EXTI_SWIER2_SWIE32_Msk )



/***************  Bits definition for EXTI_PDR1  **********************/

#define EXTI_PDR1_PD31_Pos                                  ( 31U )
#define EXTI_PDR1_PD31_Msk                                  ( 0x1UL << EXTI_PDR1_PD31_Pos )
#define EXTI_PDR1_PD31                                      ( EXTI_PDR1_PD31_Msk )


#define EXTI_PDR1_PD30_Pos                                  ( 30U )
#define EXTI_PDR1_PD30_Msk                                  ( 0x1UL << EXTI_PDR1_PD30_Pos )
#define EXTI_PDR1_PD30                                      ( EXTI_PDR1_PD30_Msk )


#define EXTI_PDR1_PD29_Pos                                  ( 29U )
#define EXTI_PDR1_PD29_Msk                                  ( 0x1UL << EXTI_PDR1_PD29_Pos )
#define EXTI_PDR1_PD29                                      ( EXTI_PDR1_PD29_Msk )


#define EXTI_PDR1_PD28_Pos                                  ( 28U )
#define EXTI_PDR1_PD28_Msk                                  ( 0x1UL << EXTI_PDR1_PD28_Pos )
#define EXTI_PDR1_PD28                                      ( EXTI_PDR1_PD28_Msk )


#define EXTI_PDR1_PD27_Pos                                  ( 27U )
#define EXTI_PDR1_PD27_Msk                                  ( 0x1UL << EXTI_PDR1_PD27_Pos )
#define EXTI_PDR1_PD27                                      ( EXTI_PDR1_PD27_Msk )


#define EXTI_PDR1_PD26_Pos                                  ( 26U )
#define EXTI_PDR1_PD26_Msk                                  ( 0x1UL << EXTI_PDR1_PD26_Pos )
#define EXTI_PDR1_PD26                                      ( EXTI_PDR1_PD26_Msk )


#define EXTI_PDR1_PD25_Pos                                  ( 25U )
#define EXTI_PDR1_PD25_Msk                                  ( 0x1UL << EXTI_PDR1_PD25_Pos )
#define EXTI_PDR1_PD25                                      ( EXTI_PDR1_PD25_Msk )


#define EXTI_PDR1_PD24_Pos                                  ( 24U )
#define EXTI_PDR1_PD24_Msk                                  ( 0x1UL << EXTI_PDR1_PD24_Pos )
#define EXTI_PDR1_PD24                                      ( EXTI_PDR1_PD24_Msk )


#define EXTI_PDR1_PD23_Pos                                  ( 23U )
#define EXTI_PDR1_PD23_Msk                                  ( 0x1UL << EXTI_PDR1_PD23_Pos )
#define EXTI_PDR1_PD23                                      ( EXTI_PDR1_PD23_Msk )


#define EXTI_PDR1_PD22_Pos                                  ( 22U )
#define EXTI_PDR1_PD22_Msk                                  ( 0x1UL << EXTI_PDR1_PD22_Pos )
#define EXTI_PDR1_PD22                                      ( EXTI_PDR1_PD22_Msk )


#define EXTI_PDR1_PD21_Pos                                  ( 21U )
#define EXTI_PDR1_PD21_Msk                                  ( 0x1UL << EXTI_PDR1_PD21_Pos )
#define EXTI_PDR1_PD21                                      ( EXTI_PDR1_PD21_Msk )


#define EXTI_PDR1_PD20_Pos                                  ( 20U )
#define EXTI_PDR1_PD20_Msk                                  ( 0x1UL << EXTI_PDR1_PD20_Pos )
#define EXTI_PDR1_PD20                                      ( EXTI_PDR1_PD20_Msk )


#define EXTI_PDR1_PD19_Pos                                  ( 19U )
#define EXTI_PDR1_PD19_Msk                                  ( 0x1UL << EXTI_PDR1_PD19_Pos )
#define EXTI_PDR1_PD19                                      ( EXTI_PDR1_PD19_Msk )


#define EXTI_PDR1_PD18_Pos                                  ( 18U )
#define EXTI_PDR1_PD18_Msk                                  ( 0x1UL << EXTI_PDR1_PD18_Pos )
#define EXTI_PDR1_PD18                                      ( EXTI_PDR1_PD18_Msk )


#define EXTI_PDR1_PD17_Pos                                  ( 17U )
#define EXTI_PDR1_PD17_Msk                                  ( 0x1UL << EXTI_PDR1_PD17_Pos )
#define EXTI_PDR1_PD17                                      ( EXTI_PDR1_PD17_Msk )


#define EXTI_PDR1_PD16_Pos                                  ( 16U )
#define EXTI_PDR1_PD16_Msk                                  ( 0x1UL << EXTI_PDR1_PD16_Pos )
#define EXTI_PDR1_PD16                                      ( EXTI_PDR1_PD16_Msk )


#define EXTI_PDR1_PD15_Pos                                  ( 15U )
#define EXTI_PDR1_PD15_Msk                                  ( 0x1UL << EXTI_PDR1_PD15_Pos )
#define EXTI_PDR1_PD15                                      ( EXTI_PDR1_PD15_Msk )


#define EXTI_PDR1_PD14_Pos                                  ( 14U )
#define EXTI_PDR1_PD14_Msk                                  ( 0x1UL << EXTI_PDR1_PD14_Pos )
#define EXTI_PDR1_PD14                                      ( EXTI_PDR1_PD14_Msk )


#define EXTI_PDR1_PD13_Pos                                  ( 13U )
#define EXTI_PDR1_PD13_Msk                                  ( 0x1UL << EXTI_PDR1_PD13_Pos )
#define EXTI_PDR1_PD13                                      ( EXTI_PDR1_PD13_Msk )


#define EXTI_PDR1_PD12_Pos                                  ( 12U )
#define EXTI_PDR1_PD12_Msk                                  ( 0x1UL << EXTI_PDR1_PD12_Pos )
#define EXTI_PDR1_PD12                                      ( EXTI_PDR1_PD12_Msk )


#define EXTI_PDR1_PD11_Pos                                  ( 11U )
#define EXTI_PDR1_PD11_Msk                                  ( 0x1UL << EXTI_PDR1_PD11_Pos )
#define EXTI_PDR1_PD11                                      ( EXTI_PDR1_PD11_Msk )


#define EXTI_PDR1_PD10_Pos                                  ( 10U )
#define EXTI_PDR1_PD10_Msk                                  ( 0x1UL << EXTI_PDR1_PD10_Pos )
#define EXTI_PDR1_PD10                                      ( EXTI_PDR1_PD10_Msk )


#define EXTI_PDR1_PD9_Pos                                   ( 9U )
#define EXTI_PDR1_PD9_Msk                                   ( 0x1UL << EXTI_PDR1_PD9_Pos )
#define EXTI_PDR1_PD9                                       ( EXTI_PDR1_PD9_Msk )


#define EXTI_PDR1_PD8_Pos                                   ( 8U )
#define EXTI_PDR1_PD8_Msk                                   ( 0x1UL << EXTI_PDR1_PD8_Pos )
#define EXTI_PDR1_PD8                                       ( EXTI_PDR1_PD8_Msk )


#define EXTI_PDR1_PD7_Pos                                   ( 7U )
#define EXTI_PDR1_PD7_Msk                                   ( 0x1UL << EXTI_PDR1_PD7_Pos )
#define EXTI_PDR1_PD7                                       ( EXTI_PDR1_PD7_Msk )


#define EXTI_PDR1_PD6_Pos                                   ( 6U )
#define EXTI_PDR1_PD6_Msk                                   ( 0x1UL << EXTI_PDR1_PD6_Pos )
#define EXTI_PDR1_PD6                                       ( EXTI_PDR1_PD6_Msk )


#define EXTI_PDR1_PD5_Pos                                   ( 5U )
#define EXTI_PDR1_PD5_Msk                                   ( 0x1UL << EXTI_PDR1_PD5_Pos )
#define EXTI_PDR1_PD5                                       ( EXTI_PDR1_PD5_Msk )


#define EXTI_PDR1_PD4_Pos                                   ( 4U )
#define EXTI_PDR1_PD4_Msk                                   ( 0x1UL << EXTI_PDR1_PD4_Pos )
#define EXTI_PDR1_PD4                                       ( EXTI_PDR1_PD4_Msk )


#define EXTI_PDR1_PD3_Pos                                   ( 3U )
#define EXTI_PDR1_PD3_Msk                                   ( 0x1UL << EXTI_PDR1_PD3_Pos )
#define EXTI_PDR1_PD3                                       ( EXTI_PDR1_PD3_Msk )


#define EXTI_PDR1_PD2_Pos                                   ( 2U )
#define EXTI_PDR1_PD2_Msk                                   ( 0x1UL << EXTI_PDR1_PD2_Pos )
#define EXTI_PDR1_PD2                                       ( EXTI_PDR1_PD2_Msk )


#define EXTI_PDR1_PD1_Pos                                   ( 1U )
#define EXTI_PDR1_PD1_Msk                                   ( 0x1UL << EXTI_PDR1_PD1_Pos )
#define EXTI_PDR1_PD1                                       ( EXTI_PDR1_PD1_Msk )


#define EXTI_PDR1_PD0_Pos                                   ( 0U )
#define EXTI_PDR1_PD0_Msk                                   ( 0x1UL << EXTI_PDR1_PD0_Pos )
#define EXTI_PDR1_PD0                                       ( EXTI_PDR1_PD0_Msk )



/***************  Bits definition for EXTI_PDR2  **********************/

#define EXTI_PDR2_PD34_Pos                                  ( 2U )
#define EXTI_PDR2_PD34_Msk                                  ( 0x1UL << EXTI_PDR2_PD34_Pos )
#define EXTI_PDR2_PD34                                      ( EXTI_PDR2_PD34_Msk )


#define EXTI_PDR2_PD33_Pos                                  ( 1U )
#define EXTI_PDR2_PD33_Msk                                  ( 0x1UL << EXTI_PDR2_PD33_Pos )
#define EXTI_PDR2_PD33                                      ( EXTI_PDR2_PD33_Msk )


#define EXTI_PDR2_PD32_Pos                                  ( 0U )
#define EXTI_PDR2_PD32_Msk                                  ( 0x1UL << EXTI_PDR2_PD32_Pos )
#define EXTI_PDR2_PD32                                      ( EXTI_PDR2_PD32_Msk )



/***************  Bits definition for EXTI_CR1  **********************/

#define EXTI_CR1_EXTI_5_Pos                                 ( 25U )
#define EXTI_CR1_EXTI_5_Msk                                 ( 0x1FUL << EXTI_CR1_EXTI_5_Pos )
#define EXTI_CR1_EXTI_5                                     ( EXTI_CR1_EXTI_5_Msk )
#define EXTI_CR1_EXTI_5_0                                   ( 0x01UL << EXTI_CR1_EXTI_5_Pos )
#define EXTI_CR1_EXTI_5_1                                   ( 0x02UL << EXTI_CR1_EXTI_5_Pos )
#define EXTI_CR1_EXTI_5_2                                   ( 0x04UL << EXTI_CR1_EXTI_5_Pos )
#define EXTI_CR1_EXTI_5_3                                   ( 0x08UL << EXTI_CR1_EXTI_5_Pos )
#define EXTI_CR1_EXTI_5_4                                   ( 0x10UL << EXTI_CR1_EXTI_5_Pos )

#define EXTI_CR1_EXTI_4_Pos                                 ( 20U )
#define EXTI_CR1_EXTI_4_Msk                                 ( 0x1FUL << EXTI_CR1_EXTI_4_Pos )
#define EXTI_CR1_EXTI_4                                     ( EXTI_CR1_EXTI_4_Msk )
#define EXTI_CR1_EXTI_4_0                                   ( 0x01UL << EXTI_CR1_EXTI_4_Pos )
#define EXTI_CR1_EXTI_4_1                                   ( 0x02UL << EXTI_CR1_EXTI_4_Pos )
#define EXTI_CR1_EXTI_4_2                                   ( 0x04UL << EXTI_CR1_EXTI_4_Pos )
#define EXTI_CR1_EXTI_4_3                                   ( 0x08UL << EXTI_CR1_EXTI_4_Pos )
#define EXTI_CR1_EXTI_4_4                                   ( 0x10UL << EXTI_CR1_EXTI_4_Pos )

#define EXTI_CR1_EXTI_3_Pos                                 ( 15U )
#define EXTI_CR1_EXTI_3_Msk                                 ( 0x1FUL << EXTI_CR1_EXTI_3_Pos )
#define EXTI_CR1_EXTI_3                                     ( EXTI_CR1_EXTI_3_Msk )
#define EXTI_CR1_EXTI_3_0                                   ( 0x01UL << EXTI_CR1_EXTI_3_Pos )
#define EXTI_CR1_EXTI_3_1                                   ( 0x02UL << EXTI_CR1_EXTI_3_Pos )
#define EXTI_CR1_EXTI_3_2                                   ( 0x04UL << EXTI_CR1_EXTI_3_Pos )
#define EXTI_CR1_EXTI_3_3                                   ( 0x08UL << EXTI_CR1_EXTI_3_Pos )
#define EXTI_CR1_EXTI_3_4                                   ( 0x10UL << EXTI_CR1_EXTI_3_Pos )

#define EXTI_CR1_EXTI_2_Pos                                 ( 10U )
#define EXTI_CR1_EXTI_2_Msk                                 ( 0x1FUL << EXTI_CR1_EXTI_2_Pos )
#define EXTI_CR1_EXTI_2                                     ( EXTI_CR1_EXTI_2_Msk )
#define EXTI_CR1_EXTI_2_0                                   ( 0x01UL << EXTI_CR1_EXTI_2_Pos )
#define EXTI_CR1_EXTI_2_1                                   ( 0x02UL << EXTI_CR1_EXTI_2_Pos )
#define EXTI_CR1_EXTI_2_2                                   ( 0x04UL << EXTI_CR1_EXTI_2_Pos )
#define EXTI_CR1_EXTI_2_3                                   ( 0x08UL << EXTI_CR1_EXTI_2_Pos )
#define EXTI_CR1_EXTI_2_4                                   ( 0x10UL << EXTI_CR1_EXTI_2_Pos )

#define EXTI_CR1_EXTI_1_Pos                                 ( 5U )
#define EXTI_CR1_EXTI_1_Msk                                 ( 0x1FUL << EXTI_CR1_EXTI_1_Pos )
#define EXTI_CR1_EXTI_1                                     ( EXTI_CR1_EXTI_1_Msk )
#define EXTI_CR1_EXTI_1_0                                   ( 0x01UL << EXTI_CR1_EXTI_1_Pos )
#define EXTI_CR1_EXTI_1_1                                   ( 0x02UL << EXTI_CR1_EXTI_1_Pos )
#define EXTI_CR1_EXTI_1_2                                   ( 0x04UL << EXTI_CR1_EXTI_1_Pos )
#define EXTI_CR1_EXTI_1_3                                   ( 0x08UL << EXTI_CR1_EXTI_1_Pos )
#define EXTI_CR1_EXTI_1_4                                   ( 0x10UL << EXTI_CR1_EXTI_1_Pos )

#define EXTI_CR1_EXTI_0_Pos                                 ( 0U )
#define EXTI_CR1_EXTI_0_Msk                                 ( 0x1FUL << EXTI_CR1_EXTI_0_Pos )
#define EXTI_CR1_EXTI_0                                     ( EXTI_CR1_EXTI_0_Msk )
#define EXTI_CR1_EXTI_0_0                                   ( 0x01UL << EXTI_CR1_EXTI_0_Pos )
#define EXTI_CR1_EXTI_0_1                                   ( 0x02UL << EXTI_CR1_EXTI_0_Pos )
#define EXTI_CR1_EXTI_0_2                                   ( 0x04UL << EXTI_CR1_EXTI_0_Pos )
#define EXTI_CR1_EXTI_0_3                                   ( 0x08UL << EXTI_CR1_EXTI_0_Pos )
#define EXTI_CR1_EXTI_0_4                                   ( 0x10UL << EXTI_CR1_EXTI_0_Pos )

/***************  Bits definition for EXTI_CR2  **********************/

#define EXTI_CR2_EXTI_11_Pos                                ( 25U )
#define EXTI_CR2_EXTI_11_Msk                                 ( 0x1FUL << EXTI_CR2_EXTI_11_Pos )
#define EXTI_CR2_EXTI_11                                    ( EXTI_CR2_EXTI_11_Msk )
#define EXTI_CR2_EXTI_11_0                                  ( 0x01UL << EXTI_CR2_EXTI_11_Pos )
#define EXTI_CR2_EXTI_11_1                                  ( 0x02UL << EXTI_CR2_EXTI_11_Pos )
#define EXTI_CR2_EXTI_11_2                                  ( 0x04UL << EXTI_CR2_EXTI_11_Pos )
#define EXTI_CR2_EXTI_11_3                                  ( 0x08UL << EXTI_CR2_EXTI_11_Pos )
#define EXTI_CR2_EXTI_11_4                                  ( 0x10UL << EXTI_CR2_EXTI_11_Pos )

#define EXTI_CR2_EXTI_10_Pos                                ( 20U )
#define EXTI_CR2_EXTI_10_Msk                                ( 0x1FUL << EXTI_CR2_EXTI_10_Pos )
#define EXTI_CR2_EXTI_10                                    ( EXTI_CR2_EXTI_10_Msk )
#define EXTI_CR2_EXTI_10_0                                  ( 0x01UL << EXTI_CR2_EXTI_10_Pos )
#define EXTI_CR2_EXTI_10_1                                  ( 0x02UL << EXTI_CR2_EXTI_10_Pos )
#define EXTI_CR2_EXTI_10_2                                  ( 0x04UL << EXTI_CR2_EXTI_10_Pos )
#define EXTI_CR2_EXTI_10_3                                  ( 0x08UL << EXTI_CR2_EXTI_10_Pos )
#define EXTI_CR2_EXTI_10_4                                  ( 0x10UL << EXTI_CR2_EXTI_10_Pos )

#define EXTI_CR2_EXTI_9_Pos                                 ( 15U )
#define EXTI_CR2_EXTI_9_Msk                                 ( 0x1FUL << EXTI_CR2_EXTI_9_Pos )
#define EXTI_CR2_EXTI_9                                     ( EXTI_CR2_EXTI_9_Msk )
#define EXTI_CR2_EXTI_9_0                                   ( 0x01UL << EXTI_CR2_EXTI_9_Pos )
#define EXTI_CR2_EXTI_9_1                                   ( 0x02UL << EXTI_CR2_EXTI_9_Pos )
#define EXTI_CR2_EXTI_9_2                                   ( 0x04UL << EXTI_CR2_EXTI_9_Pos )
#define EXTI_CR2_EXTI_9_3                                   ( 0x08UL << EXTI_CR2_EXTI_9_Pos )
#define EXTI_CR2_EXTI_9_4                                   ( 0x10UL << EXTI_CR2_EXTI_9_Pos )

#define EXTI_CR2_EXTI_8_Pos                                 ( 10U )
#define EXTI_CR2_EXTI_8_Msk                                 ( 0x1FUL << EXTI_CR2_EXTI_8_Pos )
#define EXTI_CR2_EXTI_8                                     ( EXTI_CR2_EXTI_8_Msk )
#define EXTI_CR2_EXTI_8_0                                   ( 0x01UL << EXTI_CR2_EXTI_8_Pos )
#define EXTI_CR2_EXTI_8_1                                   ( 0x02UL << EXTI_CR2_EXTI_8_Pos )
#define EXTI_CR2_EXTI_8_2                                   ( 0x04UL << EXTI_CR2_EXTI_8_Pos )
#define EXTI_CR2_EXTI_8_3                                   ( 0x08UL << EXTI_CR2_EXTI_8_Pos )
#define EXTI_CR2_EXTI_8_4                                   ( 0x10UL << EXTI_CR2_EXTI_8_Pos )

#define EXTI_CR2_EXTI_7_Pos                                 ( 5U )
#define EXTI_CR2_EXTI_7_Msk                                 ( 0x1FUL << EXTI_CR2_EXTI_7_Pos )
#define EXTI_CR2_EXTI_7                                     ( EXTI_CR2_EXTI_7_Msk )
#define EXTI_CR2_EXTI_7_0                                   ( 0x01UL << EXTI_CR2_EXTI_7_Pos )
#define EXTI_CR2_EXTI_7_1                                   ( 0x02UL << EXTI_CR2_EXTI_7_Pos )
#define EXTI_CR2_EXTI_7_2                                   ( 0x04UL << EXTI_CR2_EXTI_7_Pos )
#define EXTI_CR2_EXTI_7_3                                   ( 0x08UL << EXTI_CR2_EXTI_7_Pos )
#define EXTI_CR2_EXTI_7_4                                   ( 0x10UL << EXTI_CR2_EXTI_7_Pos )

#define EXTI_CR2_EXTI_6_Pos                                 ( 0U )
#define EXTI_CR2_EXTI_6_Msk                                 ( 0x1FUL << EXTI_CR2_EXTI_6_Pos )
#define EXTI_CR2_EXTI_6                                     ( EXTI_CR2_EXTI_6_Msk )
#define EXTI_CR2_EXTI_6_0                                   ( 0x01UL << EXTI_CR2_EXTI_6_Pos )
#define EXTI_CR2_EXTI_6_1                                   ( 0x02UL << EXTI_CR2_EXTI_6_Pos )
#define EXTI_CR2_EXTI_6_2                                   ( 0x04UL << EXTI_CR2_EXTI_6_Pos )
#define EXTI_CR2_EXTI_6_3                                   ( 0x08UL << EXTI_CR2_EXTI_6_Pos )
#define EXTI_CR2_EXTI_6_4                                   ( 0x10UL << EXTI_CR2_EXTI_6_Pos )

/***************  Bits definition for EXTI_CR3  **********************/

#define EXTI_CR3_EXTI_15_Pos                                ( 15U )
#define EXTI_CR3_EXTI_15_Msk                                ( 0x1FUL << EXTI_CR3_EXTI_15_Pos )
#define EXTI_CR3_EXTI_15                                    ( EXTI_CR3_EXTI_15_Msk )
#define EXTI_CR3_EXTI_15_0                                  ( 0x01UL << EXTI_CR3_EXTI_15_Pos )
#define EXTI_CR3_EXTI_15_1                                  ( 0x02UL << EXTI_CR3_EXTI_15_Pos )
#define EXTI_CR3_EXTI_15_2                                  ( 0x04UL << EXTI_CR3_EXTI_15_Pos )
#define EXTI_CR3_EXTI_15_3                                  ( 0x08UL << EXTI_CR3_EXTI_15_Pos )
#define EXTI_CR3_EXTI_15_4                                  ( 0x10UL << EXTI_CR3_EXTI_15_Pos )

#define EXTI_CR3_EXTI_14_Pos                                ( 10U )
#define EXTI_CR3_EXTI_14_Msk                                ( 0x1FUL << EXTI_CR3_EXTI_14_Pos )
#define EXTI_CR3_EXTI_14                                    ( EXTI_CR3_EXTI_14_Msk )
#define EXTI_CR3_EXTI_14_0                                  ( 0x01UL << EXTI_CR3_EXTI_14_Pos )
#define EXTI_CR3_EXTI_14_1                                  ( 0x02UL << EXTI_CR3_EXTI_14_Pos )
#define EXTI_CR3_EXTI_14_2                                  ( 0x04UL << EXTI_CR3_EXTI_14_Pos )
#define EXTI_CR3_EXTI_14_3                                  ( 0x08UL << EXTI_CR3_EXTI_14_Pos )
#define EXTI_CR3_EXTI_14_4                                  ( 0x10UL << EXTI_CR3_EXTI_14_Pos )

#define EXTI_CR3_EXTI_13_Pos                                ( 5U )
#define EXTI_CR3_EXTI_13_Msk                                ( 0x1FUL << EXTI_CR3_EXTI_13_Pos )
#define EXTI_CR3_EXTI_13                                    ( EXTI_CR3_EXTI_13_Msk )
#define EXTI_CR3_EXTI_13_0                                  ( 0x01UL << EXTI_CR3_EXTI_13_Pos )
#define EXTI_CR3_EXTI_13_1                                  ( 0x02UL << EXTI_CR3_EXTI_13_Pos )
#define EXTI_CR3_EXTI_13_2                                  ( 0x04UL << EXTI_CR3_EXTI_13_Pos )
#define EXTI_CR3_EXTI_13_3                                  ( 0x08UL << EXTI_CR3_EXTI_13_Pos )
#define EXTI_CR3_EXTI_13_4                                  ( 0x10UL << EXTI_CR3_EXTI_13_Pos )

#define EXTI_CR3_EXTI_12_Pos                                ( 0U )
#define EXTI_CR3_EXTI_12_Msk                                ( 0x1FUL << EXTI_CR3_EXTI_12_Pos )
#define EXTI_CR3_EXTI_12                                    ( EXTI_CR3_EXTI_12_Msk )
#define EXTI_CR3_EXTI_12_0                                  ( 0x01UL << EXTI_CR3_EXTI_12_Pos )
#define EXTI_CR3_EXTI_12_1                                  ( 0x02UL << EXTI_CR3_EXTI_12_Pos )
#define EXTI_CR3_EXTI_12_2                                  ( 0x04UL << EXTI_CR3_EXTI_12_Pos )
#define EXTI_CR3_EXTI_12_3                                  ( 0x08UL << EXTI_CR3_EXTI_12_Pos )
#define EXTI_CR3_EXTI_12_4                                  ( 0x10UL << EXTI_CR3_EXTI_12_Pos )

/***************  Bits definition for DMA_IntStatus  **********************/

#define DMA_INTSTATUS_INTSTATUS7_Pos                        ( 7U )
#define DMA_INTSTATUS_INTSTATUS7_Msk                        ( 0x1UL << DMA_INTSTATUS_INTSTATUS7_Pos )
#define DMA_INTSTATUS_INTSTATUS7                            ( DMA_INTSTATUS_INTSTATUS7_Msk )


#define DMA_INTSTATUS_INTSTATUS6_Pos                        ( 6U )
#define DMA_INTSTATUS_INTSTATUS6_Msk                        ( 0x1UL << DMA_INTSTATUS_INTSTATUS6_Pos )
#define DMA_INTSTATUS_INTSTATUS6                            ( DMA_INTSTATUS_INTSTATUS6_Msk )


#define DMA_INTSTATUS_INTSTATUS5_Pos                        ( 5U )
#define DMA_INTSTATUS_INTSTATUS5_Msk                        ( 0x1UL << DMA_INTSTATUS_INTSTATUS5_Pos )
#define DMA_INTSTATUS_INTSTATUS5                            ( DMA_INTSTATUS_INTSTATUS5_Msk )


#define DMA_INTSTATUS_INTSTATUS4_Pos                        ( 4U )
#define DMA_INTSTATUS_INTSTATUS4_Msk                        ( 0x1UL << DMA_INTSTATUS_INTSTATUS4_Pos )
#define DMA_INTSTATUS_INTSTATUS4                            ( DMA_INTSTATUS_INTSTATUS4_Msk )


#define DMA_INTSTATUS_INTSTATUS3_Pos                        ( 3U )
#define DMA_INTSTATUS_INTSTATUS3_Msk                        ( 0x1UL << DMA_INTSTATUS_INTSTATUS3_Pos )
#define DMA_INTSTATUS_INTSTATUS3                            ( DMA_INTSTATUS_INTSTATUS3_Msk )


#define DMA_INTSTATUS_INTSTATUS2_Pos                        ( 2U )
#define DMA_INTSTATUS_INTSTATUS2_Msk                        ( 0x1UL << DMA_INTSTATUS_INTSTATUS2_Pos )
#define DMA_INTSTATUS_INTSTATUS2                            ( DMA_INTSTATUS_INTSTATUS2_Msk )


#define DMA_INTSTATUS_INTSTATUS1_Pos                        ( 1U )
#define DMA_INTSTATUS_INTSTATUS1_Msk                        ( 0x1UL << DMA_INTSTATUS_INTSTATUS1_Pos )
#define DMA_INTSTATUS_INTSTATUS1                            ( DMA_INTSTATUS_INTSTATUS1_Msk )


#define DMA_INTSTATUS_INTSTATUS0_Pos                        ( 0U )
#define DMA_INTSTATUS_INTSTATUS0_Msk                        ( 0x1UL << DMA_INTSTATUS_INTSTATUS0_Pos )
#define DMA_INTSTATUS_INTSTATUS0                            ( DMA_INTSTATUS_INTSTATUS0_Msk )



/***************  Bits definition for DMA_IntTCStatus  **********************/

#define DMA_INTTCSTATUS_INTHFTCSTATUS7_Pos                  ( 15U )
#define DMA_INTTCSTATUS_INTHFTCSTATUS7_Msk                  ( 0x1UL << DMA_INTTCSTATUS_INTHFTCSTATUS7_Pos )
#define DMA_INTTCSTATUS_INTHFTCSTATUS7                      ( DMA_INTTCSTATUS_INTHFTCSTATUS7_Msk )


#define DMA_INTTCSTATUS_INTHFTCSTATUS6_Pos                  ( 14U )
#define DMA_INTTCSTATUS_INTHFTCSTATUS6_Msk                  ( 0x1UL << DMA_INTTCSTATUS_INTHFTCSTATUS6_Pos )
#define DMA_INTTCSTATUS_INTHFTCSTATUS6                      ( DMA_INTTCSTATUS_INTHFTCSTATUS6_Msk )


#define DMA_INTTCSTATUS_INTHFTCSTATUS5_Pos                  ( 13U )
#define DMA_INTTCSTATUS_INTHFTCSTATUS5_Msk                  ( 0x1UL << DMA_INTTCSTATUS_INTHFTCSTATUS5_Pos )
#define DMA_INTTCSTATUS_INTHFTCSTATUS5                      ( DMA_INTTCSTATUS_INTHFTCSTATUS5_Msk )


#define DMA_INTTCSTATUS_INTHFTCSTATUS4_Pos                  ( 12U )
#define DMA_INTTCSTATUS_INTHFTCSTATUS4_Msk                  ( 0x1UL << DMA_INTTCSTATUS_INTHFTCSTATUS4_Pos )
#define DMA_INTTCSTATUS_INTHFTCSTATUS4                      ( DMA_INTTCSTATUS_INTHFTCSTATUS4_Msk )


#define DMA_INTTCSTATUS_INTHFTCSTATUS3_Pos                  ( 11U )
#define DMA_INTTCSTATUS_INTHFTCSTATUS3_Msk                  ( 0x1UL << DMA_INTTCSTATUS_INTHFTCSTATUS3_Pos )
#define DMA_INTTCSTATUS_INTHFTCSTATUS3                      ( DMA_INTTCSTATUS_INTHFTCSTATUS3_Msk )


#define DMA_INTTCSTATUS_INTHFTCSTATUS2_Pos                  ( 10U )
#define DMA_INTTCSTATUS_INTHFTCSTATUS2_Msk                  ( 0x1UL << DMA_INTTCSTATUS_INTHFTCSTATUS2_Pos )
#define DMA_INTTCSTATUS_INTHFTCSTATUS2                      ( DMA_INTTCSTATUS_INTHFTCSTATUS2_Msk )


#define DMA_INTTCSTATUS_INTHFTCSTATUS1_Pos                  ( 9U )
#define DMA_INTTCSTATUS_INTHFTCSTATUS1_Msk                  ( 0x1UL << DMA_INTTCSTATUS_INTHFTCSTATUS1_Pos )
#define DMA_INTTCSTATUS_INTHFTCSTATUS1                      ( DMA_INTTCSTATUS_INTHFTCSTATUS1_Msk )


#define DMA_INTTCSTATUS_INTHFTCSTATUS0_Pos                  ( 8U )
#define DMA_INTTCSTATUS_INTHFTCSTATUS0_Msk                  ( 0x1UL << DMA_INTTCSTATUS_INTHFTCSTATUS0_Pos )
#define DMA_INTTCSTATUS_INTHFTCSTATUS0                      ( DMA_INTTCSTATUS_INTHFTCSTATUS0_Msk )


#define DMA_INTTCSTATUS_INTTCSTATUS7_Pos                    ( 7U )
#define DMA_INTTCSTATUS_INTTCSTATUS7_Msk                    ( 0x1UL << DMA_INTTCSTATUS_INTTCSTATUS7_Pos )
#define DMA_INTTCSTATUS_INTTCSTATUS7                        ( DMA_INTTCSTATUS_INTTCSTATUS7_Msk )


#define DMA_INTTCSTATUS_INTTCSTATUS6_Pos                    ( 6U )
#define DMA_INTTCSTATUS_INTTCSTATUS6_Msk                    ( 0x1UL << DMA_INTTCSTATUS_INTTCSTATUS6_Pos )
#define DMA_INTTCSTATUS_INTTCSTATUS6                        ( DMA_INTTCSTATUS_INTTCSTATUS6_Msk )


#define DMA_INTTCSTATUS_INTTCSTATUS5_Pos                    ( 5U )
#define DMA_INTTCSTATUS_INTTCSTATUS5_Msk                    ( 0x1UL << DMA_INTTCSTATUS_INTTCSTATUS5_Pos )
#define DMA_INTTCSTATUS_INTTCSTATUS5                        ( DMA_INTTCSTATUS_INTTCSTATUS5_Msk )


#define DMA_INTTCSTATUS_INTTCSTATUS4_Pos                    ( 4U )
#define DMA_INTTCSTATUS_INTTCSTATUS4_Msk                    ( 0x1UL << DMA_INTTCSTATUS_INTTCSTATUS4_Pos )
#define DMA_INTTCSTATUS_INTTCSTATUS4                        ( DMA_INTTCSTATUS_INTTCSTATUS4_Msk )


#define DMA_INTTCSTATUS_INTTCSTATUS3_Pos                    ( 3U )
#define DMA_INTTCSTATUS_INTTCSTATUS3_Msk                    ( 0x1UL << DMA_INTTCSTATUS_INTTCSTATUS3_Pos )
#define DMA_INTTCSTATUS_INTTCSTATUS3                        ( DMA_INTTCSTATUS_INTTCSTATUS3_Msk )


#define DMA_INTTCSTATUS_INTTCSTATUS2_Pos                    ( 2U )
#define DMA_INTTCSTATUS_INTTCSTATUS2_Msk                    ( 0x1UL << DMA_INTTCSTATUS_INTTCSTATUS2_Pos )
#define DMA_INTTCSTATUS_INTTCSTATUS2                        ( DMA_INTTCSTATUS_INTTCSTATUS2_Msk )


#define DMA_INTTCSTATUS_INTTCSTATUS1_Pos                    ( 1U )
#define DMA_INTTCSTATUS_INTTCSTATUS1_Msk                    ( 0x1UL << DMA_INTTCSTATUS_INTTCSTATUS1_Pos )
#define DMA_INTTCSTATUS_INTTCSTATUS1                        ( DMA_INTTCSTATUS_INTTCSTATUS1_Msk )


#define DMA_INTTCSTATUS_INTTCSTATUS0_Pos                    ( 0U )
#define DMA_INTTCSTATUS_INTTCSTATUS0_Msk                    ( 0x1UL << DMA_INTTCSTATUS_INTTCSTATUS0_Pos )
#define DMA_INTTCSTATUS_INTTCSTATUS0                        ( DMA_INTTCSTATUS_INTTCSTATUS0_Msk )



/***************  Bits definition for DMA_IntTCClr  **********************/

#define DMA_INTTCCLR_INTHFTCCLR7_Pos                        ( 15U )
#define DMA_INTTCCLR_INTHFTCCLR7_Msk                        ( 0x1UL << DMA_INTTCCLR_INTHFTCCLR7_Pos )
#define DMA_INTTCCLR_INTHFTCCLR7                            ( DMA_INTTCCLR_INTHFTCCLR7_Msk )


#define DMA_INTTCCLR_INTHFTCCLR6_Pos                        ( 14U )
#define DMA_INTTCCLR_INTHFTCCLR6_Msk                        ( 0x1UL << DMA_INTTCCLR_INTHFTCCLR6_Pos )
#define DMA_INTTCCLR_INTHFTCCLR6                            ( DMA_INTTCCLR_INTHFTCCLR6_Msk )


#define DMA_INTTCCLR_INTHFTCCLR5_Pos                        ( 13U )
#define DMA_INTTCCLR_INTHFTCCLR5_Msk                        ( 0x1UL << DMA_INTTCCLR_INTHFTCCLR5_Pos )
#define DMA_INTTCCLR_INTHFTCCLR5                            ( DMA_INTTCCLR_INTHFTCCLR5_Msk )


#define DMA_INTTCCLR_INTHFTCCLR4_Pos                        ( 12U )
#define DMA_INTTCCLR_INTHFTCCLR4_Msk                        ( 0x1UL << DMA_INTTCCLR_INTHFTCCLR4_Pos )
#define DMA_INTTCCLR_INTHFTCCLR4                            ( DMA_INTTCCLR_INTHFTCCLR4_Msk )


#define DMA_INTTCCLR_INTHFTCCLR3_Pos                        ( 11U )
#define DMA_INTTCCLR_INTHFTCCLR3_Msk                        ( 0x1UL << DMA_INTTCCLR_INTHFTCCLR3_Pos )
#define DMA_INTTCCLR_INTHFTCCLR3                            ( DMA_INTTCCLR_INTHFTCCLR3_Msk )


#define DMA_INTTCCLR_INTHFTCCLR2_Pos                        ( 10U )
#define DMA_INTTCCLR_INTHFTCCLR2_Msk                        ( 0x1UL << DMA_INTTCCLR_INTHFTCCLR2_Pos )
#define DMA_INTTCCLR_INTHFTCCLR2                            ( DMA_INTTCCLR_INTHFTCCLR2_Msk )


#define DMA_INTTCCLR_INTHFTCCLR1_Pos                        ( 9U )
#define DMA_INTTCCLR_INTHFTCCLR1_Msk                        ( 0x1UL << DMA_INTTCCLR_INTHFTCCLR1_Pos )
#define DMA_INTTCCLR_INTHFTCCLR1                            ( DMA_INTTCCLR_INTHFTCCLR1_Msk )


#define DMA_INTTCCLR_INTHFTCCLR0_Pos                        ( 8U )
#define DMA_INTTCCLR_INTHFTCCLR0_Msk                        ( 0x1UL << DMA_INTTCCLR_INTHFTCCLR0_Pos )
#define DMA_INTTCCLR_INTHFTCCLR0                            ( DMA_INTTCCLR_INTHFTCCLR0_Msk )


#define DMA_INTTCCLR_INTTCCLR7_Pos                          ( 7U )
#define DMA_INTTCCLR_INTTCCLR7_Msk                          ( 0x1UL << DMA_INTTCCLR_INTTCCLR7_Pos )
#define DMA_INTTCCLR_INTTCCLR7                              ( DMA_INTTCCLR_INTTCCLR7_Msk )


#define DMA_INTTCCLR_INTTCCLR6_Pos                          ( 6U )
#define DMA_INTTCCLR_INTTCCLR6_Msk                          ( 0x1UL << DMA_INTTCCLR_INTTCCLR6_Pos )
#define DMA_INTTCCLR_INTTCCLR6                              ( DMA_INTTCCLR_INTTCCLR6_Msk )


#define DMA_INTTCCLR_INTTCCLR5_Pos                          ( 5U )
#define DMA_INTTCCLR_INTTCCLR5_Msk                          ( 0x1UL << DMA_INTTCCLR_INTTCCLR5_Pos )
#define DMA_INTTCCLR_INTTCCLR5                              ( DMA_INTTCCLR_INTTCCLR5_Msk )


#define DMA_INTTCCLR_INTTCCLR4_Pos                          ( 4U )
#define DMA_INTTCCLR_INTTCCLR4_Msk                          ( 0x1UL << DMA_INTTCCLR_INTTCCLR4_Pos )
#define DMA_INTTCCLR_INTTCCLR4                              ( DMA_INTTCCLR_INTTCCLR4_Msk )


#define DMA_INTTCCLR_INTTCCLR3_Pos                          ( 3U )
#define DMA_INTTCCLR_INTTCCLR3_Msk                          ( 0x1UL << DMA_INTTCCLR_INTTCCLR3_Pos )
#define DMA_INTTCCLR_INTTCCLR3                              ( DMA_INTTCCLR_INTTCCLR3_Msk )


#define DMA_INTTCCLR_INTTCCLR2_Pos                          ( 2U )
#define DMA_INTTCCLR_INTTCCLR2_Msk                          ( 0x1UL << DMA_INTTCCLR_INTTCCLR2_Pos )
#define DMA_INTTCCLR_INTTCCLR2                              ( DMA_INTTCCLR_INTTCCLR2_Msk )


#define DMA_INTTCCLR_INTTCCLR1_Pos                          ( 1U )
#define DMA_INTTCCLR_INTTCCLR1_Msk                          ( 0x1UL << DMA_INTTCCLR_INTTCCLR1_Pos )
#define DMA_INTTCCLR_INTTCCLR1                              ( DMA_INTTCCLR_INTTCCLR1_Msk )


#define DMA_INTTCCLR_INTTCCLR0_Pos                          ( 0U )
#define DMA_INTTCCLR_INTTCCLR0_Msk                          ( 0x1UL << DMA_INTTCCLR_INTTCCLR0_Pos )
#define DMA_INTTCCLR_INTTCCLR0                              ( DMA_INTTCCLR_INTTCCLR0_Msk )



/***************  Bits definition for DMA_IntErrStatus  **********************/

#define DMA_INTERRSTATUS_INTERRSTATUS7_Pos                  ( 7U )
#define DMA_INTERRSTATUS_INTERRSTATUS7_Msk                  ( 0x1UL << DMA_INTERRSTATUS_INTERRSTATUS7_Pos )
#define DMA_INTERRSTATUS_INTERRSTATUS7                      ( DMA_INTERRSTATUS_INTERRSTATUS7_Msk )


#define DMA_INTERRSTATUS_INTERRSTATUS6_Pos                  ( 6U )
#define DMA_INTERRSTATUS_INTERRSTATUS6_Msk                  ( 0x1UL << DMA_INTERRSTATUS_INTERRSTATUS6_Pos )
#define DMA_INTERRSTATUS_INTERRSTATUS6                      ( DMA_INTERRSTATUS_INTERRSTATUS6_Msk )


#define DMA_INTERRSTATUS_INTERRSTATUS5_Pos                  ( 5U )
#define DMA_INTERRSTATUS_INTERRSTATUS5_Msk                  ( 0x1UL << DMA_INTERRSTATUS_INTERRSTATUS5_Pos )
#define DMA_INTERRSTATUS_INTERRSTATUS5                      ( DMA_INTERRSTATUS_INTERRSTATUS5_Msk )


#define DMA_INTERRSTATUS_INTERRSTATUS4_Pos                  ( 4U )
#define DMA_INTERRSTATUS_INTERRSTATUS4_Msk                  ( 0x1UL << DMA_INTERRSTATUS_INTERRSTATUS4_Pos )
#define DMA_INTERRSTATUS_INTERRSTATUS4                      ( DMA_INTERRSTATUS_INTERRSTATUS4_Msk )


#define DMA_INTERRSTATUS_INTERRSTATUS3_Pos                  ( 3U )
#define DMA_INTERRSTATUS_INTERRSTATUS3_Msk                  ( 0x1UL << DMA_INTERRSTATUS_INTERRSTATUS3_Pos )
#define DMA_INTERRSTATUS_INTERRSTATUS3                      ( DMA_INTERRSTATUS_INTERRSTATUS3_Msk )


#define DMA_INTERRSTATUS_INTERRSTATUS2_Pos                  ( 2U )
#define DMA_INTERRSTATUS_INTERRSTATUS2_Msk                  ( 0x1UL << DMA_INTERRSTATUS_INTERRSTATUS2_Pos )
#define DMA_INTERRSTATUS_INTERRSTATUS2                      ( DMA_INTERRSTATUS_INTERRSTATUS2_Msk )


#define DMA_INTERRSTATUS_INTERRSTATUS1_Pos                  ( 1U )
#define DMA_INTERRSTATUS_INTERRSTATUS1_Msk                  ( 0x1UL << DMA_INTERRSTATUS_INTERRSTATUS1_Pos )
#define DMA_INTERRSTATUS_INTERRSTATUS1                      ( DMA_INTERRSTATUS_INTERRSTATUS1_Msk )


#define DMA_INTERRSTATUS_INTERRSTATUS0_Pos                  ( 0U )
#define DMA_INTERRSTATUS_INTERRSTATUS0_Msk                  ( 0x1UL << DMA_INTERRSTATUS_INTERRSTATUS0_Pos )
#define DMA_INTERRSTATUS_INTERRSTATUS0                      ( DMA_INTERRSTATUS_INTERRSTATUS0_Msk )



/***************  Bits definition for DMA_IntErrClr  **********************/

#define DMA_INTERRCLR_INTERRCLR7_Pos                        ( 7U )
#define DMA_INTERRCLR_INTERRCLR7_Msk                        ( 0x1UL << DMA_INTERRCLR_INTERRCLR7_Pos )
#define DMA_INTERRCLR_INTERRCLR7                            ( DMA_INTERRCLR_INTERRCLR7_Msk )


#define DMA_INTERRCLR_INTERRCLR6_Pos                        ( 6U )
#define DMA_INTERRCLR_INTERRCLR6_Msk                        ( 0x1UL << DMA_INTERRCLR_INTERRCLR6_Pos )
#define DMA_INTERRCLR_INTERRCLR6                            ( DMA_INTERRCLR_INTERRCLR6_Msk )


#define DMA_INTERRCLR_INTERRCLR5_Pos                        ( 5U )
#define DMA_INTERRCLR_INTERRCLR5_Msk                        ( 0x1UL << DMA_INTERRCLR_INTERRCLR5_Pos )
#define DMA_INTERRCLR_INTERRCLR5                            ( DMA_INTERRCLR_INTERRCLR5_Msk )


#define DMA_INTERRCLR_INTERRCLR4_Pos                        ( 4U )
#define DMA_INTERRCLR_INTERRCLR4_Msk                        ( 0x1UL << DMA_INTERRCLR_INTERRCLR4_Pos )
#define DMA_INTERRCLR_INTERRCLR4                            ( DMA_INTERRCLR_INTERRCLR4_Msk )


#define DMA_INTERRCLR_INTERRCLR3_Pos                        ( 3U )
#define DMA_INTERRCLR_INTERRCLR3_Msk                        ( 0x1UL << DMA_INTERRCLR_INTERRCLR3_Pos )
#define DMA_INTERRCLR_INTERRCLR3                            ( DMA_INTERRCLR_INTERRCLR3_Msk )


#define DMA_INTERRCLR_INTERRCLR2_Pos                        ( 2U )
#define DMA_INTERRCLR_INTERRCLR2_Msk                        ( 0x1UL << DMA_INTERRCLR_INTERRCLR2_Pos )
#define DMA_INTERRCLR_INTERRCLR2                            ( DMA_INTERRCLR_INTERRCLR2_Msk )


#define DMA_INTERRCLR_INTERRCLR1_Pos                        ( 1U )
#define DMA_INTERRCLR_INTERRCLR1_Msk                        ( 0x1UL << DMA_INTERRCLR_INTERRCLR1_Pos )
#define DMA_INTERRCLR_INTERRCLR1                            ( DMA_INTERRCLR_INTERRCLR1_Msk )


#define DMA_INTERRCLR_INTERRCLR0_Pos                        ( 0U )
#define DMA_INTERRCLR_INTERRCLR0_Msk                        ( 0x1UL << DMA_INTERRCLR_INTERRCLR0_Pos )
#define DMA_INTERRCLR_INTERRCLR0                            ( DMA_INTERRCLR_INTERRCLR0_Msk )



/***************  Bits definition for DMA_RawIntTCStatus  **********************/

#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS7_Pos            ( 15U )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS7_Msk            ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS7_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS7                ( DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS7_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS6_Pos            ( 14U )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS6_Msk            ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS6_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS6                ( DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS6_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS5_Pos            ( 13U )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS5_Msk            ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS5_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS5                ( DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS5_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS4_Pos            ( 12U )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS4_Msk            ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS4_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS4                ( DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS4_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS3_Pos            ( 11U )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS3_Msk            ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS3_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS3                ( DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS3_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS2_Pos            ( 10U )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS2_Msk            ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS2_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS2                ( DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS2_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS1_Pos            ( 9U )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS1_Msk            ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS1_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS1                ( DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS1_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS0_Pos            ( 8U )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS0_Msk            ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS0_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS0                ( DMA_RAWINTTCSTATUS_RAWINTHFTCSTATUS0_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS7_Pos              ( 7U )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS7_Msk              ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTTCSTATUS7_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS7                  ( DMA_RAWINTTCSTATUS_RAWINTTCSTATUS7_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS6_Pos              ( 6U )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS6_Msk              ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTTCSTATUS6_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS6                  ( DMA_RAWINTTCSTATUS_RAWINTTCSTATUS6_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS5_Pos              ( 5U )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS5_Msk              ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTTCSTATUS5_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS5                  ( DMA_RAWINTTCSTATUS_RAWINTTCSTATUS5_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS4_Pos              ( 4U )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS4_Msk              ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTTCSTATUS4_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS4                  ( DMA_RAWINTTCSTATUS_RAWINTTCSTATUS4_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS3_Pos              ( 3U )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS3_Msk              ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTTCSTATUS3_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS3                  ( DMA_RAWINTTCSTATUS_RAWINTTCSTATUS3_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS2_Pos              ( 2U )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS2_Msk              ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTTCSTATUS2_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS2                  ( DMA_RAWINTTCSTATUS_RAWINTTCSTATUS2_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS1_Pos              ( 1U )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS1_Msk              ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTTCSTATUS1_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS1                  ( DMA_RAWINTTCSTATUS_RAWINTTCSTATUS1_Msk )


#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS0_Pos              ( 0U )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS0_Msk              ( 0x1UL << DMA_RAWINTTCSTATUS_RAWINTTCSTATUS0_Pos )
#define DMA_RAWINTTCSTATUS_RAWINTTCSTATUS0                  ( DMA_RAWINTTCSTATUS_RAWINTTCSTATUS0_Msk )



/***************  Bits definition for DMA_RawIntErrStatus  **********************/

#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS7_Pos            ( 7U )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS7_Msk            ( 0x1UL << DMA_RAWINTERRSTATUS_RAWINTERRSTATUS7_Pos )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS7                ( DMA_RAWINTERRSTATUS_RAWINTERRSTATUS7_Msk )


#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS6_Pos            ( 6U )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS6_Msk            ( 0x1UL << DMA_RAWINTERRSTATUS_RAWINTERRSTATUS6_Pos )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS6                ( DMA_RAWINTERRSTATUS_RAWINTERRSTATUS6_Msk )


#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS5_Pos            ( 5U )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS5_Msk            ( 0x1UL << DMA_RAWINTERRSTATUS_RAWINTERRSTATUS5_Pos )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS5                ( DMA_RAWINTERRSTATUS_RAWINTERRSTATUS5_Msk )


#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS4_Pos            ( 4U )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS4_Msk            ( 0x1UL << DMA_RAWINTERRSTATUS_RAWINTERRSTATUS4_Pos )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS4                ( DMA_RAWINTERRSTATUS_RAWINTERRSTATUS4_Msk )


#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS3_Pos            ( 3U )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS3_Msk            ( 0x1UL << DMA_RAWINTERRSTATUS_RAWINTERRSTATUS3_Pos )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS3                ( DMA_RAWINTERRSTATUS_RAWINTERRSTATUS3_Msk )


#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS2_Pos            ( 2U )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS2_Msk            ( 0x1UL << DMA_RAWINTERRSTATUS_RAWINTERRSTATUS2_Pos )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS2                ( DMA_RAWINTERRSTATUS_RAWINTERRSTATUS2_Msk )


#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS1_Pos            ( 1U )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS1_Msk            ( 0x1UL << DMA_RAWINTERRSTATUS_RAWINTERRSTATUS1_Pos )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS1                ( DMA_RAWINTERRSTATUS_RAWINTERRSTATUS1_Msk )


#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS0_Pos            ( 0U )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS0_Msk            ( 0x1UL << DMA_RAWINTERRSTATUS_RAWINTERRSTATUS0_Pos )
#define DMA_RAWINTERRSTATUS_RAWINTERRSTATUS0                ( DMA_RAWINTERRSTATUS_RAWINTERRSTATUS0_Msk )



/***************  Bits definition for DMA_EnChStatus  **********************/

#define DMA_ENCHSTATUS_ENCHSTAT7_Pos                        ( 7U )
#define DMA_ENCHSTATUS_ENCHSTAT7_Msk                        ( 0x1UL << DMA_ENCHSTATUS_ENCHSTAT7_Pos )
#define DMA_ENCHSTATUS_ENCHSTAT7                            ( DMA_ENCHSTATUS_ENCHSTAT7_Msk )


#define DMA_ENCHSTATUS_ENCHSTAT6_Pos                        ( 6U )
#define DMA_ENCHSTATUS_ENCHSTAT6_Msk                        ( 0x1UL << DMA_ENCHSTATUS_ENCHSTAT6_Pos )
#define DMA_ENCHSTATUS_ENCHSTAT6                            ( DMA_ENCHSTATUS_ENCHSTAT6_Msk )


#define DMA_ENCHSTATUS_ENCHSTAT5_Pos                        ( 5U )
#define DMA_ENCHSTATUS_ENCHSTAT5_Msk                        ( 0x1UL << DMA_ENCHSTATUS_ENCHSTAT5_Pos )
#define DMA_ENCHSTATUS_ENCHSTAT5                            ( DMA_ENCHSTATUS_ENCHSTAT5_Msk )


#define DMA_ENCHSTATUS_ENCHSTAT4_Pos                        ( 4U )
#define DMA_ENCHSTATUS_ENCHSTAT4_Msk                        ( 0x1UL << DMA_ENCHSTATUS_ENCHSTAT4_Pos )
#define DMA_ENCHSTATUS_ENCHSTAT4                            ( DMA_ENCHSTATUS_ENCHSTAT4_Msk )


#define DMA_ENCHSTATUS_ENCHSTAT3_Pos                        ( 3U )
#define DMA_ENCHSTATUS_ENCHSTAT3_Msk                        ( 0x1UL << DMA_ENCHSTATUS_ENCHSTAT3_Pos )
#define DMA_ENCHSTATUS_ENCHSTAT3                            ( DMA_ENCHSTATUS_ENCHSTAT3_Msk )


#define DMA_ENCHSTATUS_ENCHSTAT2_Pos                        ( 2U )
#define DMA_ENCHSTATUS_ENCHSTAT2_Msk                        ( 0x1UL << DMA_ENCHSTATUS_ENCHSTAT2_Pos )
#define DMA_ENCHSTATUS_ENCHSTAT2                            ( DMA_ENCHSTATUS_ENCHSTAT2_Msk )


#define DMA_ENCHSTATUS_ENCHSTAT1_Pos                        ( 1U )
#define DMA_ENCHSTATUS_ENCHSTAT1_Msk                        ( 0x1UL << DMA_ENCHSTATUS_ENCHSTAT1_Pos )
#define DMA_ENCHSTATUS_ENCHSTAT1                            ( DMA_ENCHSTATUS_ENCHSTAT1_Msk )


#define DMA_ENCHSTATUS_ENCHSTAT0_Pos                        ( 0U )
#define DMA_ENCHSTATUS_ENCHSTAT0_Msk                        ( 0x1UL << DMA_ENCHSTATUS_ENCHSTAT0_Pos )
#define DMA_ENCHSTATUS_ENCHSTAT0                            ( DMA_ENCHSTATUS_ENCHSTAT0_Msk )



/***************  Bits definition for DMA_Config  **********************/

#define DMA_CONFIG_M2ENDIAN_Pos                             ( 2U )
#define DMA_CONFIG_M2ENDIAN_Msk                             ( 0x1UL << DMA_CONFIG_M2ENDIAN_Pos )
#define DMA_CONFIG_M2ENDIAN                                 ( DMA_CONFIG_M2ENDIAN_Msk )

#define DMA_CONFIG_M1ENDIAN_Pos                             ( 1U )
#define DMA_CONFIG_M1ENDIAN_Msk                             ( 0x1UL << DMA_CONFIG_M1ENDIAN_Pos )
#define DMA_CONFIG_M1ENDIAN                                 ( DMA_CONFIG_M1ENDIAN_Msk )

#define DMA_CONFIG_EN_Pos                                   ( 0U )
#define DMA_CONFIG_EN_Msk                                   ( 0x1UL << DMA_CONFIG_EN_Pos )
#define DMA_CONFIG_EN                                       ( DMA_CONFIG_EN_Msk )


/***************  Bits definition for DMA_SyncLo  **********************/

#define DMA_SYNCLO_SYNCLO_Pos                               ( 0U )
#define DMA_SYNCLO_SYNCLO_Msk                               ( 0xffffffffUL << DMA_SYNCLO_SYNCLO_Pos )
#define DMA_SYNCLO_SYNCLO                                   ( DMA_SYNCLO_SYNCLO_Msk )


/***************  Bits definition for DMA_SyncHi  **********************/

#define DMA_SYNCHI_SYNCHI_Pos                               ( 0U )
#define DMA_SYNCHI_SYNCHI_Msk                               ( 0xffffffffUL << DMA_SYNCHI_SYNCHI_Pos )
#define DMA_SYNCHI_SYNCHI                                   ( DMA_SYNCHI_SYNCHI_Msk )


/***************  Bits definition for DMA_CxSrcAddr  **********************/

#define DMA_CXSRCADDR_DMA_CXSRCADDR_Pos                     ( 0U )
#define DMA_CXSRCADDR_DMA_CXSRCADDR_Msk                     ( 0xffffffffUL << DMA_CXSRCADDR_DMA_CXSRCADDR_Pos )
#define DMA_CXSRCADDR_DMA_CXSRCADDR                         ( DMA_CXSRCADDR_DMA_CXSRCADDR_Msk )


/***************  Bits definition for DMA_CxDestAddr  **********************/
 
#define DMA_CXDESTADDR_DMA_CXDESTADDR_Pos                   ( 0U )
#define DMA_CXDESTADDR_DMA_CXDESTADDR_Msk                   ( 0xffffffffUL << DMA_CXDESTADDR_DMA_CXDESTADDR_Pos )
#define DMA_CXDESTADDR_DMA_CXDESTADDR                       ( DMA_CXDESTADDR_DMA_CXDESTADDR_Msk )


/***************  Bits definition for DMA_CxLLI  **********************/

#define DMA_CXLLI_LLI_Pos                                   ( 2U )
#define DMA_CXLLI_LLI_Msk                                   ( 0x3fffffffUL << DMA_CXLLI_LLI_Pos )
#define DMA_CXLLI_LLI                                       ( DMA_CXLLI_LLI_Msk )

#define DMA_CXLLI_LM_Pos                                    ( 0U )
#define DMA_CXLLI_LM_Msk                                    ( 0x1UL << DMA_CXLLI_LM_Pos )
#define DMA_CXLLI_LM                                        ( DMA_CXLLI_LM_Msk )


/***************  Bits definition for DMA_CxCtrl  **********************/
 
#define DMA_CXCTRL_RITEN_Pos                                ( 31U )
#define DMA_CXCTRL_RITEN_Msk                                ( 0x1UL << DMA_CXCTRL_RITEN_Pos )
#define DMA_CXCTRL_RITEN                                    ( DMA_CXCTRL_RITEN_Msk )

#define DMA_CXCTRL_DIORDD_Pos                               ( 28U )
#define DMA_CXCTRL_DIORDD_Msk                               ( 0x3UL << DMA_CXCTRL_DIORDD_Pos )
#define DMA_CXCTRL_DIORDD                                   ( DMA_CXCTRL_DIORDD_Msk )
#define DMA_CXCTRL_DIORDD_0                                 ( 0x1UL << DMA_CXCTRL_DIORDD_Pos )
#define DMA_CXCTRL_DIORDD_1                                 ( 0x2UL << DMA_CXCTRL_DIORDD_Pos )

#define DMA_CXCTRL_SIORSD_Pos                               ( 26U )
#define DMA_CXCTRL_SIORSD_Msk                               ( 0x3UL << DMA_CXCTRL_SIORSD_Pos )
#define DMA_CXCTRL_SIORSD                                   ( DMA_CXCTRL_SIORSD_Msk )
#define DMA_CXCTRL_SIORSD_0                                 ( 0x1UL << DMA_CXCTRL_SIORSD_Pos )
#define DMA_CXCTRL_SIORSD_1                                 ( 0x2UL << DMA_CXCTRL_SIORSD_Pos )

#define DMA_CXCTRL_DWIDTH_Pos                               ( 24U )
#define DMA_CXCTRL_DWIDTH_Msk                               ( 0x3UL << DMA_CXCTRL_DWIDTH_Pos )
#define DMA_CXCTRL_DWIDTH                                   ( DMA_CXCTRL_DWIDTH_Msk )
#define DMA_CXCTRL_DWIDTH_0                                 ( 0x1UL << DMA_CXCTRL_DWIDTH_Pos )
#define DMA_CXCTRL_DWIDTH_1                                 ( 0x2UL << DMA_CXCTRL_DWIDTH_Pos )

#define DMA_CXCTRL_SWIDTH_Pos                               ( 22U )
#define DMA_CXCTRL_SWIDTH_Msk                               ( 0x3UL << DMA_CXCTRL_SWIDTH_Pos )
#define DMA_CXCTRL_SWIDTH                                   ( DMA_CXCTRL_SWIDTH_Msk )
#define DMA_CXCTRL_SWIDTH_0                                 ( 0x1UL << DMA_CXCTRL_SWIDTH_Pos )
#define DMA_CXCTRL_SWIDTH_1                                 ( 0x2UL << DMA_CXCTRL_SWIDTH_Pos )

#define DMA_CXCTRL_DBSIZE_Pos                               ( 19U )
#define DMA_CXCTRL_DBSIZE_Msk                               ( 0x7UL << DMA_CXCTRL_DBSIZE_Pos )
#define DMA_CXCTRL_DBSIZE                                   ( DMA_CXCTRL_DBSIZE_Msk )
#define DMA_CXCTRL_DBSIZE_0                                 ( 0x1UL << DMA_CXCTRL_DBSIZE_Pos )
#define DMA_CXCTRL_DBSIZE_1                                 ( 0x2UL << DMA_CXCTRL_DBSIZE_Pos )
#define DMA_CXCTRL_DBSIZE_2                                 ( 0x4UL << DMA_CXCTRL_DBSIZE_Pos )

#define DMA_CXCTRL_SBSIZE_Pos                               ( 16U )
#define DMA_CXCTRL_SBSIZE_Msk                               ( 0x7UL << DMA_CXCTRL_SBSIZE_Pos )
#define DMA_CXCTRL_SBSIZE                                   ( DMA_CXCTRL_SBSIZE_Msk )
#define DMA_CXCTRL_SBSIZE_0                                 ( 0x1UL << DMA_CXCTRL_SBSIZE_Pos )
#define DMA_CXCTRL_SBSIZE_1                                 ( 0x2UL << DMA_CXCTRL_SBSIZE_Pos )
#define DMA_CXCTRL_SBSIZE_2                                 ( 0x4UL << DMA_CXCTRL_SBSIZE_Pos )

#define DMA_CXCTRL_TRANSFERSIZE_Pos                         ( 0U )
#define DMA_CXCTRL_TRANSFERSIZE_Msk                         ( 0xffffUL << DMA_CXCTRL_TRANSFERSIZE_Pos )
#define DMA_CXCTRL_TRANSFERSIZE                             ( DMA_CXCTRL_TRANSFERSIZE_Msk )


/***************  Bits definition for DMA_CxConfig  **********************/

#define DMA_CXCONFIG_SRCPERIPH_Pos                          ( 24U )
#define DMA_CXCONFIG_SRCPERIPH_Msk                          ( 0xffUL << DMA_CXCONFIG_SRCPERIPH_Pos )
#define DMA_CXCONFIG_SRCPERIPH                              ( DMA_CXCONFIG_SRCPERIPH_Msk )
#define DMA_CXCONFIG_SRCPERIPH_0                            ( 0x1UL << DMA_CXCONFIG_SRCPERIPH_Pos )
#define DMA_CXCONFIG_SRCPERIPH_1                            ( 0x2UL << DMA_CXCONFIG_SRCPERIPH_Pos )
#define DMA_CXCONFIG_SRCPERIPH_2                            ( 0x4UL << DMA_CXCONFIG_SRCPERIPH_Pos )
#define DMA_CXCONFIG_SRCPERIPH_3                            ( 0x8UL << DMA_CXCONFIG_SRCPERIPH_Pos )
#define DMA_CXCONFIG_SRCPERIPH_4                            ( 0x10UL << DMA_CXCONFIG_SRCPERIPH_Pos )
#define DMA_CXCONFIG_SRCPERIPH_5                            ( 0x20UL << DMA_CXCONFIG_SRCPERIPH_Pos )
#define DMA_CXCONFIG_SRCPERIPH_6                            ( 0x40UL << DMA_CXCONFIG_SRCPERIPH_Pos )
#define DMA_CXCONFIG_SRCPERIPH_7                            ( 0x80UL << DMA_CXCONFIG_SRCPERIPH_Pos )

#define DMA_CXCONFIG_DESTPERIPH_Pos                         ( 16U )
#define DMA_CXCONFIG_DESTPERIPH_Msk                         ( 0xffUL << DMA_CXCONFIG_DESTPERIPH_Pos )
#define DMA_CXCONFIG_DESTPERIPH                             ( DMA_CXCONFIG_DESTPERIPH_Msk )
#define DMA_CXCONFIG_DESTPERIPH_0                           ( 0x1UL << DMA_CXCONFIG_DESTPERIPH_Pos )
#define DMA_CXCONFIG_DESTPERIPH_1                           ( 0x2UL << DMA_CXCONFIG_DESTPERIPH_Pos )
#define DMA_CXCONFIG_DESTPERIPH_2                           ( 0x4UL << DMA_CXCONFIG_DESTPERIPH_Pos )
#define DMA_CXCONFIG_DESTPERIPH_3                           ( 0x8UL << DMA_CXCONFIG_DESTPERIPH_Pos )
#define DMA_CXCONFIG_DESTPERIPH_4                           ( 0x10UL << DMA_CXCONFIG_DESTPERIPH_Pos )
#define DMA_CXCONFIG_DESTPERIPH_5                           ( 0x20UL << DMA_CXCONFIG_DESTPERIPH_Pos )
#define DMA_CXCONFIG_DESTPERIPH_6                           ( 0x40UL << DMA_CXCONFIG_DESTPERIPH_Pos )
#define DMA_CXCONFIG_DESTPERIPH_7                           ( 0x80UL << DMA_CXCONFIG_DESTPERIPH_Pos )

#define DMA_CXCONFIG_LOCK_Pos                               ( 11U )
#define DMA_CXCONFIG_LOCK_Msk                               ( 0x1UL << DMA_CXCONFIG_LOCK_Pos )
#define DMA_CXCONFIG_LOCK                                   ( DMA_CXCONFIG_LOCK_Msk )

#define DMA_CXCONFIG_D_Pos                                  ( 10U )
#define DMA_CXCONFIG_D_Msk                                  ( 0x1UL << DMA_CXCONFIG_D_Pos )
#define DMA_CXCONFIG_D                                      ( DMA_CXCONFIG_D_Msk )

#define DMA_CXCONFIG_S_Pos                                  ( 9U )
#define DMA_CXCONFIG_S_Msk                                  ( 0x1UL << DMA_CXCONFIG_S_Pos )
#define DMA_CXCONFIG_S                                      ( DMA_CXCONFIG_S_Msk )

#define DMA_CXCONFIG_HALT_Pos                               ( 8U )
#define DMA_CXCONFIG_HALT_Msk                               ( 0x1UL << DMA_CXCONFIG_HALT_Pos )
#define DMA_CXCONFIG_HALT                                   ( DMA_CXCONFIG_HALT_Msk )

#define DMA_CXCONFIG_ACTIVE_Pos                             ( 7U )
#define DMA_CXCONFIG_ACTIVE_Msk                             ( 0x1UL << DMA_CXCONFIG_ACTIVE_Pos )
#define DMA_CXCONFIG_ACTIVE                                 ( DMA_CXCONFIG_ACTIVE_Msk )

#define DMA_CXCONFIG_IHFTC_Pos                              ( 6U )
#define DMA_CXCONFIG_IHFTC_Msk                              ( 0x1UL << DMA_CXCONFIG_IHFTC_Pos )
#define DMA_CXCONFIG_IHFTC                                  ( DMA_CXCONFIG_IHFTC_Msk )

#define DMA_CXCONFIG_ITC_Pos                                ( 5U )
#define DMA_CXCONFIG_ITC_Msk                                ( 0x1UL << DMA_CXCONFIG_ITC_Pos )
#define DMA_CXCONFIG_ITC                                    ( DMA_CXCONFIG_ITC_Msk )

#define DMA_CXCONFIG_IE_Pos                                 ( 4U )
#define DMA_CXCONFIG_IE_Msk                                 ( 0x1UL << DMA_CXCONFIG_IE_Pos )
#define DMA_CXCONFIG_IE                                     ( DMA_CXCONFIG_IE_Msk )

#define DMA_CXCONFIG_FLOWCTRL_Pos                           ( 1U )
#define DMA_CXCONFIG_FLOWCTRL_Msk                           ( 0x7UL << DMA_CXCONFIG_FLOWCTRL_Pos )
#define DMA_CXCONFIG_FLOWCTRL                               ( DMA_CXCONFIG_FLOWCTRL_Msk )
#define DMA_CXCONFIG_FLOWCTRL_0                             ( 0x1UL << DMA_CXCONFIG_FLOWCTRL_Pos )
#define DMA_CXCONFIG_FLOWCTRL_1                             ( 0x2UL << DMA_CXCONFIG_FLOWCTRL_Pos )
#define DMA_CXCONFIG_FLOWCTRL_2                             ( 0x4UL << DMA_CXCONFIG_FLOWCTRL_Pos )

#define DMA_CXCONFIG_EN_Pos                                 ( 0U )
#define DMA_CXCONFIG_EN_Msk                                 ( 0x1UL << DMA_CXCONFIG_EN_Pos )
#define DMA_CXCONFIG_EN                                     ( DMA_CXCONFIG_EN_Msk )


/***************  Bits definition for USART_DR  **********************/

#define USART_DR_OE_Pos                                      ( 12U )
#define USART_DR_OE_Msk                                      ( 0x1UL << USART_DR_OE_Pos )
#define USART_DR_OE                                          ( USART_DR_OE_Msk )

#define USART_DR_BE_Pos                                      ( 11U )
#define USART_DR_BE_Msk                                      ( 0x1UL << USART_DR_BE_Pos )
#define USART_DR_BE                                          ( USART_DR_BE_Msk )

#define USART_DR_PE_Pos                                      ( 10U )
#define USART_DR_PE_Msk                                      ( 0x1UL << USART_DR_PE_Pos )
#define USART_DR_PE                                          ( USART_DR_PE_Msk )

#define USART_DR_FE_Pos                                      ( 9U )
#define USART_DR_FE_Msk                                      ( 0x1UL << USART_DR_FE_Pos )
#define USART_DR_FE                                          ( USART_DR_FE_Msk )

#define USART_DR_DATA_Pos                                    ( 0U )
#define USART_DR_DATA_Msk                                    ( 0x1ffUL << USART_DR_DATA_Pos )
#define USART_DR_DATA                                        ( USART_DR_DATA_Msk )


/***************  Bits definition for USART_FR  **********************/

#define USART_FR_BUSY_Pos                                    ( 9U )
#define USART_FR_BUSY_Msk                                    ( 0x1UL << USART_FR_BUSY_Pos )
#define USART_FR_BUSY                                        ( USART_FR_BUSY_Msk )

#define USART_FR_CTS_Pos                                     ( 8U )
#define USART_FR_CTS_Msk                                     ( 0x1UL << USART_FR_CTS_Pos )
#define USART_FR_CTS                                         ( USART_FR_CTS_Msk )

#define USART_FR_TXFE_Pos                                    ( 7U )
#define USART_FR_TXFE_Msk                                    ( 0x1UL << USART_FR_TXFE_Pos )
#define USART_FR_TXFE                                        ( USART_FR_TXFE_Msk )

#define USART_FR_RXFF_Pos                                    ( 6U )
#define USART_FR_RXFF_Msk                                    ( 0x1UL << USART_FR_RXFF_Pos )
#define USART_FR_RXFF                                        ( USART_FR_RXFF_Msk )

#define USART_FR_TXFF_Pos                                    ( 5U )
#define USART_FR_TXFF_Msk                                    ( 0x1UL << USART_FR_TXFF_Pos )
#define USART_FR_TXFF                                        ( USART_FR_TXFF_Msk )

#define USART_FR_RXFE_Pos                                    ( 4U )
#define USART_FR_RXFE_Msk                                    ( 0x1UL << USART_FR_RXFE_Pos )
#define USART_FR_RXFE                                        ( USART_FR_RXFE_Msk )

#define USART_FR_OE_Pos                                      ( 3U )
#define USART_FR_OE_Msk                                      ( 0x1UL << USART_FR_OE_Pos )
#define USART_FR_OE                                          ( USART_FR_OE_Msk )

#define USART_FR_BE_Pos                                      ( 2U )
#define USART_FR_BE_Msk                                      ( 0x1UL << USART_FR_BE_Pos )
#define USART_FR_BE                                          ( USART_FR_BE_Msk )

#define USART_FR_PE_Pos                                      ( 1U )
#define USART_FR_PE_Msk                                      ( 0x1UL << USART_FR_PE_Pos )
#define USART_FR_PE                                          ( USART_FR_PE_Msk )

#define USART_FR_FE_Pos                                      ( 0U )
#define USART_FR_FE_Msk                                      ( 0x1UL << USART_FR_FE_Pos )
#define USART_FR_FE                                          ( USART_FR_FE_Msk )


/***************  Bits definition for USART_BRR  **********************/

#define USART_BRR_IBAUD_Pos                             ( 6U )
#define USART_BRR_IBAUD_Msk                             ( 0xffffUL << USART_BRR_IBAUD_Pos )
#define USART_BRR_IBAUD                                 ( USART_BRR_IBAUD_Msk )

#define USART_BRR_FBAUD_Pos                             ( 0U )
#define USART_BRR_FBAUD_Msk                             ( 0x3fUL << USART_BRR_FBAUD_Pos )
#define USART_BRR_FBAUD                                 ( USART_BRR_FBAUD_Msk )
#define USART_BRR_FBAUD_0                               ( 0x1UL << USART_BRR_FBAUD_Pos )
#define USART_BRR_FBAUD_1                               ( 0x2UL << USART_BRR_FBAUD_Pos )
#define USART_BRR_FBAUD_2                               ( 0x4UL << USART_BRR_FBAUD_Pos )
#define USART_BRR_FBAUD_3                               ( 0x8UL << USART_BRR_FBAUD_Pos )
#define USART_BRR_FBAUD_4                               ( 0x10UL << USART_BRR_FBAUD_Pos )
#define USART_BRR_FBAUD_5                               ( 0x20UL << USART_BRR_FBAUD_Pos )


/***************  Bits definition for USART_IE  **********************/

#define USART_IE_TCI_Pos                                     ( 15U )
#define USART_IE_TCI_Msk                                     ( 0x1UL << USART_IE_TCI_Pos )
#define USART_IE_TCI                                         ( USART_IE_TCI_Msk )

#define USART_IE_ABRI_Pos                                    ( 14U )
#define USART_IE_ABRI_Msk                                    ( 0x1UL << USART_IE_ABRI_Pos )
#define USART_IE_ABRI                                        ( USART_IE_ABRI_Msk )

#define USART_IE_IDLEI_Pos                                   ( 13U )
#define USART_IE_IDLEI_Msk                                   ( 0x1UL << USART_IE_IDLEI_Pos )
#define USART_IE_IDLEI                                       ( USART_IE_IDLEI_Msk )

#define USART_IE_BCNTI_Pos                                   ( 12U )
#define USART_IE_BCNTI_Msk                                   ( 0x1UL << USART_IE_BCNTI_Pos )
#define USART_IE_BCNTI                                       ( USART_IE_BCNTI_Msk )

#define USART_IE_LBDI_Pos                                    ( 11U )
#define USART_IE_LBDI_Msk                                    ( 0x1UL << USART_IE_LBDI_Pos )
#define USART_IE_LBDI                                        ( USART_IE_LBDI_Msk )

#define USART_IE_OEI_Pos                                     ( 10U )
#define USART_IE_OEI_Msk                                     ( 0x1UL << USART_IE_OEI_Pos )
#define USART_IE_OEI                                         ( USART_IE_OEI_Msk )

#define USART_IE_BEI_Pos                                     ( 9U )
#define USART_IE_BEI_Msk                                     ( 0x1UL << USART_IE_BEI_Pos )
#define USART_IE_BEI                                         ( USART_IE_BEI_Msk )

#define USART_IE_PEI_Pos                                     ( 8U )
#define USART_IE_PEI_Msk                                     ( 0x1UL << USART_IE_PEI_Pos )
#define USART_IE_PEI                                         ( USART_IE_PEI_Msk )

#define USART_IE_FEI_Pos                                     ( 7U )
#define USART_IE_FEI_Msk                                     ( 0x1UL << USART_IE_FEI_Pos )
#define USART_IE_FEI                                         ( USART_IE_FEI_Msk )

#define USART_IE_TXI_Pos                                     ( 5U )
#define USART_IE_TXI_Msk                                     ( 0x1UL << USART_IE_TXI_Pos )
#define USART_IE_TXI                                         ( USART_IE_TXI_Msk )

#define USART_IE_RXI_Pos                                     ( 4U )
#define USART_IE_RXI_Msk                                     ( 0x1UL << USART_IE_RXI_Pos )
#define USART_IE_RXI                                         ( USART_IE_RXI_Msk )


/***************  Bits definition for USART_ISR  **********************/

#define USART_ISR_TCI_Pos                                   ( 15U )
#define USART_ISR_TCI_Msk                                   ( 0x1UL << USART_ISR_TCI_Pos )
#define USART_ISR_TCI                                       ( USART_ISR_TCI_Msk )

#define USART_ISR_ABRI_Pos                                   ( 14U )
#define USART_ISR_ABRI_Msk                                   ( 0x1UL << USART_ISR_ABRI_Pos )
#define USART_ISR_ABRI                                       ( USART_ISR_ABRI_Msk )

#define USART_ISR_IDLEI_Pos                                  ( 13U )
#define USART_ISR_IDLEI_Msk                                  ( 0x1UL << USART_ISR_IDLEI_Pos )
#define USART_ISR_IDLEI                                      ( USART_ISR_IDLEI_Msk )

#define USART_ISR_BCNTI_Pos                                  ( 12U )
#define USART_ISR_BCNTI_Msk                                  ( 0x1UL << USART_ISR_BCNTI_Pos )
#define USART_ISR_BCNTI                                      ( USART_ISR_BCNTI_Msk )

#define USART_ISR_LBDI_Pos                                   ( 11U )
#define USART_ISR_LBDI_Msk                                   ( 0x1UL << USART_ISR_LBDI_Pos )
#define USART_ISR_LBDI                                       ( USART_ISR_LBDI_Msk )

#define USART_ISR_OEI_Pos                                    ( 10U )
#define USART_ISR_OEI_Msk                                    ( 0x1UL << USART_ISR_OEI_Pos )
#define USART_ISR_OEI                                        ( USART_ISR_OEI_Msk )

#define USART_ISR_BEI_Pos                                    ( 9U )
#define USART_ISR_BEI_Msk                                    ( 0x1UL << USART_ISR_BEI_Pos )
#define USART_ISR_BEI                                        ( USART_ISR_BEI_Msk )

#define USART_ISR_PEI_Pos                                    ( 8U )
#define USART_ISR_PEI_Msk                                    ( 0x1UL << USART_ISR_PEI_Pos )
#define USART_ISR_PEI                                        ( USART_ISR_PEI_Msk )

#define USART_ISR_FEI_Pos                                    ( 7U )
#define USART_ISR_FEI_Msk                                    ( 0x1UL << USART_ISR_FEI_Pos )
#define USART_ISR_FEI                                        ( USART_ISR_FEI_Msk )

#define USART_ISR_TXI_Pos                                    ( 5U )
#define USART_ISR_TXI_Msk                                    ( 0x1UL << USART_ISR_TXI_Pos )
#define USART_ISR_TXI                                        ( USART_ISR_TXI_Msk )

#define USART_ISR_RXI_Pos                                    ( 4U )
#define USART_ISR_RXI_Msk                                    ( 0x1UL << USART_ISR_RXI_Pos )
#define USART_ISR_RXI                                        ( USART_ISR_RXI_Msk )


/***************  Bits definition for USART_CR1  **********************/

#define USART_CR1_CTSEN_Pos                                  ( 15U )
#define USART_CR1_CTSEN_Msk                                  ( 0x1UL << USART_CR1_CTSEN_Pos )
#define USART_CR1_CTSEN                                      ( USART_CR1_CTSEN_Msk )

#define USART_CR1_RTSEN_Pos                                  ( 14U )
#define USART_CR1_RTSEN_Msk                                  ( 0x1UL << USART_CR1_RTSEN_Pos )
#define USART_CR1_RTSEN                                      ( USART_CR1_RTSEN_Msk )

#define USART_CR1_RTS_Pos                                    ( 11U )
#define USART_CR1_RTS_Msk                                    ( 0x1UL << USART_CR1_RTS_Pos )
#define USART_CR1_RTS                                        ( USART_CR1_RTS_Msk )

#define USART_CR1_RXE_Pos                                    ( 9U )
#define USART_CR1_RXE_Msk                                    ( 0x1UL << USART_CR1_RXE_Pos )
#define USART_CR1_RXE                                        ( USART_CR1_RXE_Msk )

#define USART_CR1_TXE_Pos                                    ( 8U )
#define USART_CR1_TXE_Msk                                    ( 0x1UL << USART_CR1_TXE_Pos )
#define USART_CR1_TXE                                        ( USART_CR1_TXE_Msk )

#define USART_CR1_DMAONERR_Pos                               ( 5U )
#define USART_CR1_DMAONERR_Msk                               ( 0x1UL << USART_CR1_DMAONERR_Pos )
#define USART_CR1_DMAONERR                                   ( USART_CR1_DMAONERR_Msk )

#define USART_CR1_TXDMAE_Pos                                 ( 4U )
#define USART_CR1_TXDMAE_Msk                                 ( 0x1UL << USART_CR1_TXDMAE_Pos )
#define USART_CR1_TXDMAE                                     ( USART_CR1_TXDMAE_Msk )

#define USART_CR1_RXDMAE_Pos                                 ( 3U )
#define USART_CR1_RXDMAE_Msk                                 ( 0x1UL << USART_CR1_RXDMAE_Pos )
#define USART_CR1_RXDMAE                                     ( USART_CR1_RXDMAE_Msk )

#define USART_CR1_SIRLP_Pos                                  ( 2U )
#define USART_CR1_SIRLP_Msk                                  ( 0x1UL << USART_CR1_SIRLP_Pos )
#define USART_CR1_SIRLP                                      ( USART_CR1_SIRLP_Msk )

#define USART_CR1_SIREN_Pos                                  ( 1U )
#define USART_CR1_SIREN_Msk                                  ( 0x1UL << USART_CR1_SIREN_Pos )
#define USART_CR1_SIREN                                      ( USART_CR1_SIREN_Msk )

#define USART_CR1_USARTEN_Pos                                 ( 0U )
#define USART_CR1_USARTEN_Msk                                 ( 0x1UL << USART_CR1_USARTEN_Pos )
#define USART_CR1_USARTEN                                     ( USART_CR1_USARTEN_Msk )


/***************  Bits definition for USART_CR2  **********************/

#define USART_CR2_ADDM7_Pos                                  ( 18U )
#define USART_CR2_ADDM7_Msk                                  ( 0x1UL << USART_CR2_ADDM7_Pos )
#define USART_CR2_ADDM7                                      ( USART_CR2_ADDM7_Msk )

#define USART_CR2_ADDR_Pos                                   ( 11U )
#define USART_CR2_ADDR_Msk                                   ( 0x7fUL << USART_CR2_ADDR_Pos )
#define USART_CR2_ADDR                                       ( USART_CR2_ADDR_Msk )
#define USART_CR2_ADDR_0                                     ( 0x1UL << USART_CR2_ADDR_Pos )
#define USART_CR2_ADDR_1                                     ( 0x2UL << USART_CR2_ADDR_Pos )
#define USART_CR2_ADDR_2                                     ( 0x4UL << USART_CR2_ADDR_Pos )
#define USART_CR2_ADDR_3                                     ( 0x8UL << USART_CR2_ADDR_Pos )
#define USART_CR2_ADDR_4                                     ( 0x10UL << USART_CR2_ADDR_Pos )
#define USART_CR2_ADDR_5                                     ( 0x20UL << USART_CR2_ADDR_Pos )
#define USART_CR2_ADDR_6                                     ( 0x40UL << USART_CR2_ADDR_Pos )

#define USART_CR2_CPOL_Pos                                   ( 10U )
#define USART_CR2_CPOL_Msk                                   ( 0x1UL << USART_CR2_CPOL_Pos )
#define USART_CR2_CPOL                                       ( USART_CR2_CPOL_Msk )

#define USART_CR2_CPHA_Pos                                   ( 9U )
#define USART_CR2_CPHA_Msk                                   ( 0x1UL << USART_CR2_CPHA_Pos )
#define USART_CR2_CPHA                                       ( USART_CR2_CPHA_Msk )

#define USART_CR2_LBCL_Pos                                   ( 8U )
#define USART_CR2_LBCL_Msk                                   ( 0x1UL << USART_CR2_LBCL_Pos )
#define USART_CR2_LBCL                                       ( USART_CR2_LBCL_Msk )

#define USART_CR2_CLKEN_Pos                                  ( 7U )
#define USART_CR2_CLKEN_Msk                                  ( 0x1UL << USART_CR2_CLKEN_Pos )
#define USART_CR2_CLKEN                                      ( USART_CR2_CLKEN_Msk )

#define USART_CR2_NACK_Pos                                   ( 6U )
#define USART_CR2_NACK_Msk                                   ( 0x1UL << USART_CR2_NACK_Pos )
#define USART_CR2_NACK                                       ( USART_CR2_NACK_Msk )

#define USART_CR2_SCEN_Pos                                   ( 5U )
#define USART_CR2_SCEN_Msk                                   ( 0x1UL << USART_CR2_SCEN_Pos )
#define USART_CR2_SCEN                                       ( USART_CR2_SCEN_Msk )

#define USART_CR2_ABREN_Pos                                  ( 4U )
#define USART_CR2_ABREN_Msk                                  ( 0x1UL << USART_CR2_ABREN_Pos )
#define USART_CR2_ABREN                                      ( USART_CR2_ABREN_Msk )

#define USART_CR2_WAKE_Pos                                   ( 3U )
#define USART_CR2_WAKE_Msk                                   ( 0x1UL << USART_CR2_WAKE_Pos )
#define USART_CR2_WAKE                                       ( USART_CR2_WAKE_Msk )

#define USART_CR2_RWU_Pos                                    ( 2U )
#define USART_CR2_RWU_Msk                                    ( 0x1UL << USART_CR2_RWU_Pos )
#define USART_CR2_RWU                                        ( USART_CR2_RWU_Msk )

#define USART_CR2_HDSEL_Pos                                  ( 0U )
#define USART_CR2_HDSEL_Msk                                  ( 0x1UL << USART_CR2_HDSEL_Pos )
#define USART_CR2_HDSEL                                      ( USART_CR2_HDSEL_Msk )


/***************  Bits definition for USART_CR3  **********************/

#define USART_CR3_RXIFLSEL_Pos                               ( 13U )
#define USART_CR3_RXIFLSEL_Msk                               ( 0x7UL << USART_CR3_RXIFLSEL_Pos )
#define USART_CR3_RXIFLSEL                                   ( USART_CR3_RXIFLSEL_Msk )
#define USART_CR3_RXIFLSEL_0                                 ( 0x1UL << USART_CR3_RXIFLSEL_Pos )
#define USART_CR3_RXIFLSEL_1                                 ( 0x2UL << USART_CR3_RXIFLSEL_Pos )
#define USART_CR3_RXIFLSEL_2                                 ( 0x4UL << USART_CR3_RXIFLSEL_Pos )

#define USART_CR3_TXIFLSEL_Pos                               ( 10U )
#define USART_CR3_TXIFLSEL_Msk                               ( 0x7UL << USART_CR3_TXIFLSEL_Pos )
#define USART_CR3_TXIFLSEL                                   ( USART_CR3_TXIFLSEL_Msk )
#define USART_CR3_TXIFLSEL_0                                 ( 0x1UL << USART_CR3_TXIFLSEL_Pos )
#define USART_CR3_TXIFLSEL_1                                 ( 0x2UL << USART_CR3_TXIFLSEL_Pos )
#define USART_CR3_TXIFLSEL_2                                 ( 0x4UL << USART_CR3_TXIFLSEL_Pos )

#define USART_CR3_SPS_Pos                                    ( 9U )
#define USART_CR3_SPS_Msk                                    ( 0x1UL << USART_CR3_SPS_Pos )
#define USART_CR3_SPS                                        ( USART_CR3_SPS_Msk )

#define USART_CR3_WLEN_Pos                                   ( 6U )
#define USART_CR3_WLEN_Msk                                   ( 0x7UL << USART_CR3_WLEN_Pos )
#define USART_CR3_WLEN                                       ( USART_CR3_WLEN_Msk )
#define USART_CR3_WLEN_0                                     ( 0x1UL << USART_CR3_WLEN_Pos )
#define USART_CR3_WLEN_1                                     ( 0x2UL << USART_CR3_WLEN_Pos )
#define USART_CR3_WLEN_2                                     ( 0x4UL << USART_CR3_WLEN_Pos )

#define USART_CR3_FEN_Pos                                    ( 5U )
#define USART_CR3_FEN_Msk                                    ( 0x1UL << USART_CR3_FEN_Pos )
#define USART_CR3_FEN                                        ( USART_CR3_FEN_Msk )

#define USART_CR3_STP2_Pos                                   ( 3U )
#define USART_CR3_STP2_Msk                                   ( 0x1UL << USART_CR3_STP2_Pos )
#define USART_CR3_STP2                                       ( USART_CR3_STP2_Msk )

#define USART_CR3_EPS_Pos                                    ( 2U )
#define USART_CR3_EPS_Msk                                    ( 0x1UL << USART_CR3_EPS_Pos )
#define USART_CR3_EPS                                        ( USART_CR3_EPS_Msk )

#define USART_CR3_PEN_Pos                                    ( 1U )
#define USART_CR3_PEN_Msk                                    ( 0x1UL << USART_CR3_PEN_Pos )
#define USART_CR3_PEN                                        ( USART_CR3_PEN_Msk )

#define USART_CR3_BRK_Pos                                    ( 0U )
#define USART_CR3_BRK_Msk                                    ( 0x1UL << USART_CR3_BRK_Pos )
#define USART_CR3_BRK                                        ( USART_CR3_BRK_Msk )


/***************  Bits definition for USART_GTPR  **********************/

#define USART_GTPR_GT_Pos                                    ( 8U )
#define USART_GTPR_GT_Msk                                    ( 0xfUL << USART_GTPR_GT_Pos )
#define USART_GTPR_GT                                        ( USART_GTPR_GT_Msk )
#define USART_GTPR_GT_0                                      ( 0x1UL << USART_GTPR_GT_Pos )
#define USART_GTPR_GT_1                                      ( 0x2UL << USART_GTPR_GT_Pos )
#define USART_GTPR_GT_2                                      ( 0x4UL << USART_GTPR_GT_Pos )
#define USART_GTPR_GT_3                                      ( 0x8UL << USART_GTPR_GT_Pos )

#define USART_GTPR_PSC_Pos                                   ( 0U )
#define USART_GTPR_PSC_Msk                                   ( 0xffUL << USART_GTPR_PSC_Pos )
#define USART_GTPR_PSC                                       ( USART_GTPR_PSC_Msk )
#define USART_GTPR_PSC_0                                     ( 0x1UL << USART_GTPR_PSC_Pos )
#define USART_GTPR_PSC_1                                     ( 0x2UL << USART_GTPR_PSC_Pos )
#define USART_GTPR_PSC_2                                     ( 0x4UL << USART_GTPR_PSC_Pos )
#define USART_GTPR_PSC_3                                     ( 0x8UL << USART_GTPR_PSC_Pos )
#define USART_GTPR_PSC_4                                     ( 0x10UL << USART_GTPR_PSC_Pos )
#define USART_GTPR_PSC_5                                     ( 0x20UL << USART_GTPR_PSC_Pos )
#define USART_GTPR_PSC_6                                     ( 0x40UL << USART_GTPR_PSC_Pos )
#define USART_GTPR_PSC_7                                     ( 0x80UL << USART_GTPR_PSC_Pos )


/***************  Bits definition for USART_BCNT  **********************/

#define USART_BCNT_DEM_Pos                                   ( 27U )
#define USART_BCNT_DEM_Msk                                   ( 0x1UL << USART_BCNT_DEM_Pos )
#define USART_BCNT_DEM                                       ( USART_BCNT_DEM_Msk )

#define USART_BCNT_DEP_Pos                                   ( 26U )
#define USART_BCNT_DEP_Msk                                   ( 0x1UL << USART_BCNT_DEP_Pos )
#define USART_BCNT_DEP                                       ( USART_BCNT_DEP_Msk )

#define USART_BCNT_AUTO_START_EN_Pos                         ( 25U )
#define USART_BCNT_AUTO_START_EN_Msk                         ( 0x1UL << USART_BCNT_AUTO_START_EN_Pos )
#define USART_BCNT_AUTO_START_EN                             ( USART_BCNT_AUTO_START_EN_Msk )

#define USART_BCNT_BCNTSTART_Pos                            ( 24U )
#define USART_BCNT_BCNTSTART_Msk                            ( 0x1UL << USART_BCNT_BCNTSTART_Pos )
#define USART_BCNT_BCNTSTART                                ( USART_BCNT_BCNTSTART_Msk )

#define USART_BCNT_BCNTVALUE_Pos                            ( 0U )
#define USART_BCNT_BCNTVALUE_Msk                            ( 0xffffffUL << USART_BCNT_BCNTVALUE_Pos )
#define USART_BCNT_BCNTVALUE                                ( USART_BCNT_BCNTVALUE_Msk )

#define USART_BCNT_DEAT_Pos                      ( 4U )
#define USART_BCNT_DEAT_Msk                      ( 0xFUL << USART_BCNT_DEAT_Pos )
#define USART_BCNT_DEAT                          ( USART_BCNT_DEAT_Msk )

#define USART_BCNT_DEDT_Pos                      ( 0U )
#define USART_BCNT_DEDT_Msk                      ( 0xFUL << USART_BCNT_DEDT_Pos )
#define USART_BCNT_DEDT                          ( USART_BCNT_DEDT_Msk )


/***************  Bits definition for SPI_TX_RX_DAT  **********************/

#define SPI_TX_RX_DAT_DAT_Pos                               ( 0U )
#define SPI_TX_RX_DAT_DAT_Msk                               ( 0xffUL << SPI_TX_RX_DAT_DAT_Pos )
#define SPI_TX_RX_DAT_DAT                                   ( SPI_TX_RX_DAT_DAT_Msk )
#define SPI_TX_RX_DAT_DAT_0                                 ( 0x1UL << SPI_TX_RX_DAT_DAT_Pos )
#define SPI_TX_RX_DAT_DAT_1                                 ( 0x2UL << SPI_TX_RX_DAT_DAT_Pos )
#define SPI_TX_RX_DAT_DAT_2                                 ( 0x4UL << SPI_TX_RX_DAT_DAT_Pos )
#define SPI_TX_RX_DAT_DAT_3                                 ( 0x8UL << SPI_TX_RX_DAT_DAT_Pos )
#define SPI_TX_RX_DAT_DAT_4                                 ( 0x10UL << SPI_TX_RX_DAT_DAT_Pos )
#define SPI_TX_RX_DAT_DAT_5                                 ( 0x20UL << SPI_TX_RX_DAT_DAT_Pos )
#define SPI_TX_RX_DAT_DAT_6                                 ( 0x40UL << SPI_TX_RX_DAT_DAT_Pos )
#define SPI_TX_RX_DAT_DAT_7                                 ( 0x80UL << SPI_TX_RX_DAT_DAT_Pos )


/***************  Bits definition for SPI_BAUD  **********************/

#define SPI_BAUD_DIV2_Pos                                   ( 8U )
#define SPI_BAUD_DIV2_Msk                                   ( 0xffUL << SPI_BAUD_DIV2_Pos )
#define SPI_BAUD_DIV2                                       ( SPI_BAUD_DIV2_Msk )
#define SPI_BAUD_DIV2_0                                     ( 0x1UL << SPI_BAUD_DIV2_Pos )
#define SPI_BAUD_DIV2_1                                     ( 0x2UL << SPI_BAUD_DIV2_Pos )
#define SPI_BAUD_DIV2_2                                     ( 0x4UL << SPI_BAUD_DIV2_Pos )
#define SPI_BAUD_DIV2_3                                     ( 0x8UL << SPI_BAUD_DIV2_Pos )
#define SPI_BAUD_DIV2_4                                     ( 0x10UL << SPI_BAUD_DIV2_Pos )
#define SPI_BAUD_DIV2_5                                     ( 0x20UL << SPI_BAUD_DIV2_Pos )
#define SPI_BAUD_DIV2_6                                     ( 0x40UL << SPI_BAUD_DIV2_Pos )
#define SPI_BAUD_DIV2_7                                     ( 0x80UL << SPI_BAUD_DIV2_Pos )

#define SPI_BAUD_DIV1_Pos                                   ( 0U )
#define SPI_BAUD_DIV1_Msk                                   ( 0xffUL << SPI_BAUD_DIV1_Pos )
#define SPI_BAUD_DIV1                                       ( SPI_BAUD_DIV1_Msk )
#define SPI_BAUD_DIV1_0                                     ( 0x1UL << SPI_BAUD_DIV1_Pos )
#define SPI_BAUD_DIV1_1                                     ( 0x2UL << SPI_BAUD_DIV1_Pos )
#define SPI_BAUD_DIV1_2                                     ( 0x4UL << SPI_BAUD_DIV1_Pos )
#define SPI_BAUD_DIV1_3                                     ( 0x8UL << SPI_BAUD_DIV1_Pos )
#define SPI_BAUD_DIV1_4                                     ( 0x10UL << SPI_BAUD_DIV1_Pos )
#define SPI_BAUD_DIV1_5                                     ( 0x20UL << SPI_BAUD_DIV1_Pos )
#define SPI_BAUD_DIV1_6                                     ( 0x40UL << SPI_BAUD_DIV1_Pos )
#define SPI_BAUD_DIV1_7                                     ( 0x80UL << SPI_BAUD_DIV1_Pos )


/***************  Bits definition for SPI_CTL  **********************/

#define SPI_CTL_SWCS_EN_Pos                                 ( 21U )
#define SPI_CTL_SWCS_EN_Msk                                 ( 0x1UL << SPI_CTL_SWCS_EN_Pos )
#define SPI_CTL_SWCS_EN                                     ( SPI_CTL_SWCS_EN_Msk )

#define SPI_CTL_SWCS_Pos                                    ( 20U )
#define SPI_CTL_SWCS_Msk                                    ( 0x1UL << SPI_CTL_SWCS_Pos )
#define SPI_CTL_SWCS                                        ( SPI_CTL_SWCS_Msk )

#define SPI_CTL_CS_TIME_Pos                                 ( 11U )
#define SPI_CTL_CS_TIME_Msk                                 ( 0xffUL << SPI_CTL_CS_TIME_Pos )
#define SPI_CTL_CS_TIME                                     ( SPI_CTL_CS_TIME_Msk )
#define SPI_CTL_CS_TIME_0                                   ( 0x1UL << SPI_CTL_CS_TIME_Pos )
#define SPI_CTL_CS_TIME_1                                   ( 0x2UL << SPI_CTL_CS_TIME_Pos )
#define SPI_CTL_CS_TIME_2                                   ( 0x4UL << SPI_CTL_CS_TIME_Pos )
#define SPI_CTL_CS_TIME_3                                   ( 0x8UL << SPI_CTL_CS_TIME_Pos )
#define SPI_CTL_CS_TIME_4                                   ( 0x10UL << SPI_CTL_CS_TIME_Pos )
#define SPI_CTL_CS_TIME_5                                   ( 0x20UL << SPI_CTL_CS_TIME_Pos )
#define SPI_CTL_CS_TIME_6                                   ( 0x40UL << SPI_CTL_CS_TIME_Pos )
#define SPI_CTL_CS_TIME_7                                   ( 0x80UL << SPI_CTL_CS_TIME_Pos )

#define SPI_CTL_CS_FILTER_Pos                               ( 10U )
#define SPI_CTL_CS_FILTER_Msk                               ( 0x1UL << SPI_CTL_CS_FILTER_Pos )
#define SPI_CTL_CS_FILTER                                   ( SPI_CTL_CS_FILTER_Msk )

#define SPI_CTL_CS_RST_Pos                                  ( 9U )
#define SPI_CTL_CS_RST_Msk                                  ( 0x1UL << SPI_CTL_CS_RST_Pos )
#define SPI_CTL_CS_RST                                      ( SPI_CTL_CS_RST_Msk )

#define SPI_CTL_SLAVE_EN_Pos                                ( 8U )
#define SPI_CTL_SLAVE_EN_Msk                                ( 0x1UL << SPI_CTL_SLAVE_EN_Pos )
#define SPI_CTL_SLAVE_EN                                    ( SPI_CTL_SLAVE_EN_Msk )

#define SPI_CTL_IO_MODE_Pos                                 ( 7U )
#define SPI_CTL_IO_MODE_Msk                                 ( 0x1UL << SPI_CTL_IO_MODE_Pos )
#define SPI_CTL_IO_MODE                                     ( SPI_CTL_IO_MODE_Msk )

#define SPI_CTL_X_MODE_Pos                                  ( 5U )
#define SPI_CTL_X_MODE_Msk                                  ( 0x3UL << SPI_CTL_X_MODE_Pos )
#define SPI_CTL_X_MODE                                      ( SPI_CTL_X_MODE_Msk )
#define SPI_CTL_X_MODE_0                                    ( 0x1UL << SPI_CTL_X_MODE_Pos )
#define SPI_CTL_X_MODE_1                                    ( 0x2UL << SPI_CTL_X_MODE_Pos )

#define SPI_CTL_LSB_FIRST_Pos                               ( 4U )
#define SPI_CTL_LSB_FIRST_Msk                               ( 0x1UL << SPI_CTL_LSB_FIRST_Pos )
#define SPI_CTL_LSB_FIRST                                   ( SPI_CTL_LSB_FIRST_Msk )

#define SPI_CTL_CPOL_Pos                                    ( 3U )
#define SPI_CTL_CPOL_Msk                                    ( 0x1UL << SPI_CTL_CPOL_Pos )
#define SPI_CTL_CPOL                                        ( SPI_CTL_CPOL_Msk )

#define SPI_CTL_CPHA_Pos                                    ( 2U )
#define SPI_CTL_CPHA_Msk                                    ( 0x1UL << SPI_CTL_CPHA_Pos )
#define SPI_CTL_CPHA                                        ( SPI_CTL_CPHA_Msk )

#define SPI_CTL_SFILTER_Pos                                 ( 1U )
#define SPI_CTL_SFILTER_Msk                                 ( 0x1UL << SPI_CTL_SFILTER_Pos )
#define SPI_CTL_SFILTER                                     ( SPI_CTL_SFILTER_Msk )

#define SPI_CTL_MST_MODE_Pos                                ( 0U )
#define SPI_CTL_MST_MODE_Msk                                ( 0x1UL << SPI_CTL_MST_MODE_Pos )
#define SPI_CTL_MST_MODE                                    ( SPI_CTL_MST_MODE_Msk )


/***************  Bits definition for SPI_TX_CTL  **********************/

#define SPI_TX_CTL_DUMMY_Pos                                ( 8U )
#define SPI_TX_CTL_DUMMY_Msk                                ( 0xffUL << SPI_TX_CTL_DUMMY_Pos )
#define SPI_TX_CTL_DUMMY                                    ( SPI_TX_CTL_DUMMY_Msk )
#define SPI_TX_CTL_DUMMY_0                                  ( 0x1UL << SPI_TX_CTL_DUMMY_Pos )
#define SPI_TX_CTL_DUMMY_1                                  ( 0x2UL << SPI_TX_CTL_DUMMY_Pos )
#define SPI_TX_CTL_DUMMY_2                                  ( 0x4UL << SPI_TX_CTL_DUMMY_Pos )
#define SPI_TX_CTL_DUMMY_3                                  ( 0x8UL << SPI_TX_CTL_DUMMY_Pos )
#define SPI_TX_CTL_DUMMY_4                                  ( 0x10UL << SPI_TX_CTL_DUMMY_Pos )
#define SPI_TX_CTL_DUMMY_5                                  ( 0x20UL << SPI_TX_CTL_DUMMY_Pos )
#define SPI_TX_CTL_DUMMY_6                                  ( 0x40UL << SPI_TX_CTL_DUMMY_Pos )
#define SPI_TX_CTL_DUMMY_7                                  ( 0x80UL << SPI_TX_CTL_DUMMY_Pos )

#define SPI_TX_CTL_DMA_LEVEL_Pos                         ( 4U )
#define SPI_TX_CTL_DMA_LEVEL_Msk                         ( 0xfUL << SPI_TX_CTL_DMA_LEVEL_Pos )
#define SPI_TX_CTL_DMA_LEVEL                             ( SPI_TX_CTL_DMA_LEVEL_Msk )
#define SPI_TX_CTL_DMA_LEVEL_0                           ( 0x1UL << SPI_TX_CTL_DMA_LEVEL_Pos )
#define SPI_TX_CTL_DMA_LEVEL_1                           ( 0x2UL << SPI_TX_CTL_DMA_LEVEL_Pos )
#define SPI_TX_CTL_DMA_LEVEL_2                           ( 0x4UL << SPI_TX_CTL_DMA_LEVEL_Pos )
#define SPI_TX_CTL_DMA_LEVEL_3                           ( 0x8UL << SPI_TX_CTL_DMA_LEVEL_Pos )

#define SPI_TX_CTL_DMA_REQ_EN_Pos                        ( 3U )
#define SPI_TX_CTL_DMA_REQ_EN_Msk                        ( 0x1UL << SPI_TX_CTL_DMA_REQ_EN_Pos )
#define SPI_TX_CTL_DMA_REQ_EN                            ( SPI_TX_CTL_DMA_REQ_EN_Msk )

#define SPI_TX_CTL_MODE_Pos                              ( 2U )
#define SPI_TX_CTL_MODE_Msk                              ( 0x1UL << SPI_TX_CTL_MODE_Pos )
#define SPI_TX_CTL_MODE                                  ( SPI_TX_CTL_MODE_Msk )

#define SPI_TX_CTL_FIFO_RESET_Pos                        ( 1U )
#define SPI_TX_CTL_FIFO_RESET_Msk                        ( 0x1UL << SPI_TX_CTL_FIFO_RESET_Pos )
#define SPI_TX_CTL_FIFO_RESET                            ( SPI_TX_CTL_FIFO_RESET_Msk )

#define SPI_TX_CTL_EN_Pos                                ( 0U )
#define SPI_TX_CTL_EN_Msk                                ( 0x1UL << SPI_TX_CTL_EN_Pos )
#define SPI_TX_CTL_EN                                    ( SPI_TX_CTL_EN_Msk )


/***************  Bits definition for SPI_RX_CTL  **********************/

#define SPI_RX_CTL_SSHIFT_Pos                               ( 8U )
#define SPI_RX_CTL_SSHIFT_Msk                               ( 0x3UL << SPI_RX_CTL_SSHIFT_Pos )
#define SPI_RX_CTL_SSHIFT                                   ( SPI_RX_CTL_SSHIFT_Msk )
#define SPI_RX_CTL_SSHIFT_0                                 ( 0x1UL << SPI_RX_CTL_SSHIFT_Pos )
#define SPI_RX_CTL_SSHIFT_1                                 ( 0x2UL << SPI_RX_CTL_SSHIFT_Pos )

#define SPI_RX_CTL_DMA_LEVEL_Pos                            ( 4U )
#define SPI_RX_CTL_DMA_LEVEL_Msk                            ( 0xfUL << SPI_RX_CTL_DMA_LEVEL_Pos )
#define SPI_RX_CTL_DMA_LEVEL                                ( SPI_RX_CTL_DMA_LEVEL_Msk )
#define SPI_RX_CTL_DMA_LEVEL_0                              ( 0x1UL << SPI_RX_CTL_DMA_LEVEL_Pos )
#define SPI_RX_CTL_DMA_LEVEL_1                              ( 0x2UL << SPI_RX_CTL_DMA_LEVEL_Pos )
#define SPI_RX_CTL_DMA_LEVEL_2                              ( 0x4UL << SPI_RX_CTL_DMA_LEVEL_Pos )
#define SPI_RX_CTL_DMA_LEVEL_3                              ( 0x8UL << SPI_RX_CTL_DMA_LEVEL_Pos )

#define SPI_RX_CTL_DMA_REQ_EN_Pos                           ( 3U )
#define SPI_RX_CTL_DMA_REQ_EN_Msk                           ( 0x1UL << SPI_RX_CTL_DMA_REQ_EN_Pos )
#define SPI_RX_CTL_DMA_REQ_EN                               ( SPI_RX_CTL_DMA_REQ_EN_Msk )

#define SPI_RX_CTL_FIFO_RESET_Pos                           ( 1U )
#define SPI_RX_CTL_FIFO_RESET_Msk                           ( 0x1UL << SPI_RX_CTL_FIFO_RESET_Pos )
#define SPI_RX_CTL_FIFO_RESET                               ( SPI_RX_CTL_FIFO_RESET_Msk )

#define SPI_RX_CTL_EN_Pos                                   ( 0U )
#define SPI_RX_CTL_EN_Msk                                   ( 0x1UL << SPI_RX_CTL_EN_Pos )
#define SPI_RX_CTL_EN                                       ( SPI_RX_CTL_EN_Msk )


/***************  Bits definition for SPI_IE  **********************/

#define SPI_IE_RX_BATCH_DONE_EN_Pos                         ( 15U )
#define SPI_IE_RX_BATCH_DONE_EN_Msk                         ( 0x1UL << SPI_IE_RX_BATCH_DONE_EN_Pos )
#define SPI_IE_RX_BATCH_DONE_EN                             ( SPI_IE_RX_BATCH_DONE_EN_Msk )

#define SPI_IE_TX_BATCH_DONE_EN_Pos                         ( 14U )
#define SPI_IE_TX_BATCH_DONE_EN_Msk                         ( 0x1UL << SPI_IE_TX_BATCH_DONE_EN_Pos )
#define SPI_IE_TX_BATCH_DONE_EN                             ( SPI_IE_TX_BATCH_DONE_EN_Msk )

#define SPI_IE_RX_FIFO_FULL_OVERFLOW_EN_Pos                 ( 13U )
#define SPI_IE_RX_FIFO_FULL_OVERFLOW_EN_Msk                 ( 0x1UL << SPI_IE_RX_FIFO_FULL_OVERFLOW_EN_Pos )
#define SPI_IE_RX_FIFO_FULL_OVERFLOW_EN                     ( SPI_IE_RX_FIFO_FULL_OVERFLOW_EN_Msk )

#define SPI_IE_RX_FIFO_EMPTY_OVERFLOW_EN_Pos                ( 12U )
#define SPI_IE_RX_FIFO_EMPTY_OVERFLOW_EN_Msk                ( 0x1UL << SPI_IE_RX_FIFO_EMPTY_OVERFLOW_EN_Pos )
#define SPI_IE_RX_FIFO_EMPTY_OVERFLOW_EN                    ( SPI_IE_RX_FIFO_EMPTY_OVERFLOW_EN_Msk )

#define SPI_IE_RX_FIFO_NOT_EMPTY_EN_Pos                     ( 11U )
#define SPI_IE_RX_FIFO_NOT_EMPTY_EN_Msk                     ( 0x1UL << SPI_IE_RX_FIFO_NOT_EMPTY_EN_Pos )
#define SPI_IE_RX_FIFO_NOT_EMPTY_EN                         ( SPI_IE_RX_FIFO_NOT_EMPTY_EN_Msk )

#define SPI_IE_CS_POS_EN_Pos                                ( 10U )
#define SPI_IE_CS_POS_EN_Msk                                ( 0x1UL << SPI_IE_CS_POS_EN_Pos )
#define SPI_IE_CS_POS_EN                                    ( SPI_IE_CS_POS_EN_Msk )

#define SPI_IE_RX_FIFO_HALF_FULL_EN_Pos                     ( 9U )
#define SPI_IE_RX_FIFO_HALF_FULL_EN_Msk                     ( 0x1UL << SPI_IE_RX_FIFO_HALF_FULL_EN_Pos )
#define SPI_IE_RX_FIFO_HALF_FULL_EN                         ( SPI_IE_RX_FIFO_HALF_FULL_EN_Msk )

#define SPI_IE_RX_FIFO_HALF_EMPTY_EN_Pos                    ( 8U )
#define SPI_IE_RX_FIFO_HALF_EMPTY_EN_Msk                    ( 0x1UL << SPI_IE_RX_FIFO_HALF_EMPTY_EN_Pos )
#define SPI_IE_RX_FIFO_HALF_EMPTY_EN                        ( SPI_IE_RX_FIFO_HALF_EMPTY_EN_Msk )

#define SPI_IE_TX_FIFO_HALF_FULL_EN_Pos                     ( 7U )
#define SPI_IE_TX_FIFO_HALF_FULL_EN_Msk                     ( 0x1UL << SPI_IE_TX_FIFO_HALF_FULL_EN_Pos )
#define SPI_IE_TX_FIFO_HALF_FULL_EN                         ( SPI_IE_TX_FIFO_HALF_FULL_EN_Msk )

#define SPI_IE_TX_FIFO_HALF_EMPTY_EN_Pos                    ( 6U )
#define SPI_IE_TX_FIFO_HALF_EMPTY_EN_Msk                    ( 0x1UL << SPI_IE_TX_FIFO_HALF_EMPTY_EN_Pos )
#define SPI_IE_TX_FIFO_HALF_EMPTY_EN                        ( SPI_IE_TX_FIFO_HALF_EMPTY_EN_Msk )

#define SPI_IE_RX_FIFO_FULL_EN_Pos                          ( 5U )
#define SPI_IE_RX_FIFO_FULL_EN_Msk                          ( 0x1UL << SPI_IE_RX_FIFO_FULL_EN_Pos )
#define SPI_IE_RX_FIFO_FULL_EN                              ( SPI_IE_RX_FIFO_FULL_EN_Msk )

#define SPI_IE_RX_FIFO_EMPTY_EN_Pos                         ( 4U )
#define SPI_IE_RX_FIFO_EMPTY_EN_Msk                         ( 0x1UL << SPI_IE_RX_FIFO_EMPTY_EN_Pos )
#define SPI_IE_RX_FIFO_EMPTY_EN                             ( SPI_IE_RX_FIFO_EMPTY_EN_Msk )

#define SPI_IE_TX_FIFO_FULL_EN_Pos                          ( 3U )
#define SPI_IE_TX_FIFO_FULL_EN_Msk                          ( 0x1UL << SPI_IE_TX_FIFO_FULL_EN_Pos )
#define SPI_IE_TX_FIFO_FULL_EN                              ( SPI_IE_TX_FIFO_FULL_EN_Msk )

#define SPI_IE_TX_FIFO_EMPTY_EN_Pos                         ( 2U )
#define SPI_IE_TX_FIFO_EMPTY_EN_Msk                         ( 0x1UL << SPI_IE_TX_FIFO_EMPTY_EN_Pos )
#define SPI_IE_TX_FIFO_EMPTY_EN                             ( SPI_IE_TX_FIFO_EMPTY_EN_Msk )

#define SPI_IE_BATCH_DONE_EN_Pos                            ( 1U )
#define SPI_IE_BATCH_DONE_EN_Msk                            ( 0x1UL << SPI_IE_BATCH_DONE_EN_Pos )
#define SPI_IE_BATCH_DONE_EN                                ( SPI_IE_BATCH_DONE_EN_Msk )


/***************  Bits definition for SPI_STATUS  **********************/

#define SPI_STATUS_RX_BATCH_DONE_Pos                        ( 15U )
#define SPI_STATUS_RX_BATCH_DONE_Msk                        ( 0x1UL << SPI_STATUS_RX_BATCH_DONE_Pos )
#define SPI_STATUS_RX_BATCH_DONE                            ( SPI_STATUS_RX_BATCH_DONE_Msk )

#define SPI_STATUS_TX_BATCH_DONE_Pos                        ( 14U )
#define SPI_STATUS_TX_BATCH_DONE_Msk                        ( 0x1UL << SPI_STATUS_TX_BATCH_DONE_Pos )
#define SPI_STATUS_TX_BATCH_DONE                            ( SPI_STATUS_TX_BATCH_DONE_Msk )

#define SPI_STATUS_RX_FIFO_FULL_OVERFLOW_Pos                ( 13U )
#define SPI_STATUS_RX_FIFO_FULL_OVERFLOW_Msk                ( 0x1UL << SPI_STATUS_RX_FIFO_FULL_OVERFLOW_Pos )
#define SPI_STATUS_RX_FIFO_FULL_OVERFLOW                    ( SPI_STATUS_RX_FIFO_FULL_OVERFLOW_Msk )

#define SPI_STATUS_RX_FIFO_EMPTY_OVERFLOW_Pos               ( 12U )
#define SPI_STATUS_RX_FIFO_EMPTY_OVERFLOW_Msk               ( 0x1UL << SPI_STATUS_RX_FIFO_EMPTY_OVERFLOW_Pos )
#define SPI_STATUS_RX_FIFO_EMPTY_OVERFLOW                   ( SPI_STATUS_RX_FIFO_EMPTY_OVERFLOW_Msk )

#define SPI_STATUS_RX_FIFO_NOT_EMPTY_Pos                    ( 11U )
#define SPI_STATUS_RX_FIFO_NOT_EMPTY_Msk                    ( 0x1UL << SPI_STATUS_RX_FIFO_NOT_EMPTY_Pos )
#define SPI_STATUS_RX_FIFO_NOT_EMPTY                        ( SPI_STATUS_RX_FIFO_NOT_EMPTY_Msk )

#define SPI_STATUS_CS_POS_FLG_Pos                           ( 10U )
#define SPI_STATUS_CS_POS_FLG_Msk                           ( 0x1UL << SPI_STATUS_CS_POS_FLG_Pos )
#define SPI_STATUS_CS_POS_FLG                               ( SPI_STATUS_CS_POS_FLG_Msk )

#define SPI_STATUS_RX_FIFO_HALF_FULL_Pos                    ( 9U )
#define SPI_STATUS_RX_FIFO_HALF_FULL_Msk                    ( 0x1UL << SPI_STATUS_RX_FIFO_HALF_FULL_Pos )
#define SPI_STATUS_RX_FIFO_HALF_FULL                        ( SPI_STATUS_RX_FIFO_HALF_FULL_Msk )

#define SPI_STATUS_RX_FIFO_HALF_EMPTY_Pos                   ( 8U )
#define SPI_STATUS_RX_FIFO_HALF_EMPTY_Msk                   ( 0x1UL << SPI_STATUS_RX_FIFO_HALF_EMPTY_Pos )
#define SPI_STATUS_RX_FIFO_HALF_EMPTY                       ( SPI_STATUS_RX_FIFO_HALF_EMPTY_Msk )

#define SPI_STATUS_TX_FIFO_HALF_FULL_Pos                    ( 7U )
#define SPI_STATUS_TX_FIFO_HALF_FULL_Msk                    ( 0x1UL << SPI_STATUS_TX_FIFO_HALF_FULL_Pos )
#define SPI_STATUS_TX_FIFO_HALF_FULL                        ( SPI_STATUS_TX_FIFO_HALF_FULL_Msk )

#define SPI_STATUS_TX_FIFO_HALF_EMPTY_Pos                   ( 6U )
#define SPI_STATUS_TX_FIFO_HALF_EMPTY_Msk                   ( 0x1UL << SPI_STATUS_TX_FIFO_HALF_EMPTY_Pos )
#define SPI_STATUS_TX_FIFO_HALF_EMPTY                       ( SPI_STATUS_TX_FIFO_HALF_EMPTY_Msk )

#define SPI_STATUS_RX_FIFO_FULL_Pos                         ( 5U )
#define SPI_STATUS_RX_FIFO_FULL_Msk                         ( 0x1UL << SPI_STATUS_RX_FIFO_FULL_Pos )
#define SPI_STATUS_RX_FIFO_FULL                             ( SPI_STATUS_RX_FIFO_FULL_Msk )

#define SPI_STATUS_RX_FIFO_EMPTY_Pos                        ( 4U )
#define SPI_STATUS_RX_FIFO_EMPTY_Msk                        ( 0x1UL << SPI_STATUS_RX_FIFO_EMPTY_Pos )
#define SPI_STATUS_RX_FIFO_EMPTY                            ( SPI_STATUS_RX_FIFO_EMPTY_Msk )

#define SPI_STATUS_TX_FIFO_FULL_Pos                         ( 3U )
#define SPI_STATUS_TX_FIFO_FULL_Msk                         ( 0x1UL << SPI_STATUS_TX_FIFO_FULL_Pos )
#define SPI_STATUS_TX_FIFO_FULL                             ( SPI_STATUS_TX_FIFO_FULL_Msk )

#define SPI_STATUS_TX_FIFO_EMPTY_Pos                        ( 2U )
#define SPI_STATUS_TX_FIFO_EMPTY_Msk                        ( 0x1UL << SPI_STATUS_TX_FIFO_EMPTY_Pos )
#define SPI_STATUS_TX_FIFO_EMPTY                            ( SPI_STATUS_TX_FIFO_EMPTY_Msk )

#define SPI_STATUS_BATCH_DONE_Pos                           ( 1U )
#define SPI_STATUS_BATCH_DONE_Msk                           ( 0x1UL << SPI_STATUS_BATCH_DONE_Pos )
#define SPI_STATUS_BATCH_DONE                               ( SPI_STATUS_BATCH_DONE_Msk )

#define SPI_STATUS_TX_BUSY_Pos                              ( 0U )
#define SPI_STATUS_TX_BUSY_Msk                              ( 0x1UL << SPI_STATUS_TX_BUSY_Pos )
#define SPI_STATUS_TX_BUSY                                  ( SPI_STATUS_TX_BUSY_Msk )


/***************  Bits definition for SPI_TXDelay  **********************/

#define SPI_TXDELAY_SPI_TDY_Pos                             ( 0U )
#define SPI_TXDELAY_SPI_TDY_Msk                             ( 0xffffffffUL << SPI_TXDELAY_SPI_TDY_Pos )
#define SPI_TXDELAY_SPI_TDY                                 ( SPI_TXDELAY_SPI_TDY_Msk )


/***************  Bits definition for SPI_BATCH  **********************/

#define SPI_BATCH_BATCH_NUMBER_Pos                          ( 0U )
#define SPI_BATCH_BATCH_NUMBER_Msk                          ( 0xffffffffUL << SPI_BATCH_BATCH_NUMBER_Pos )
#define SPI_BATCH_BATCH_NUMBER                              ( SPI_BATCH_BATCH_NUMBER_Msk )


/***************  Bits definition for SPI_CS  **********************/

#define SPI_CS_Pos                                          ( 0U )
#define SPI_CS_Msk                                          ( 0x1FUL << SPI_CS_Pos )
#define SPI_CS                                              ( SPI_CS_Msk )
#define SPI_CS_CS0                                          ( 0x1UL << SPI_CS_Pos )
#define SPI_CS_CS1                                          ( 0x2UL << SPI_CS_Pos )
#define SPI_CS_CS2                                          ( 0x4UL << SPI_CS_Pos )
#define SPI_CS_CS3                                          ( 0x8UL << SPI_CS_Pos )
#define SPI_CS_CS4                                          ( 0x10UL << SPI_CS_Pos )

#define SPI_CSMAP_EN_Pos                                   (8)
#define SPI_CSMAP_EN_Msk                                   (0x1UL << SPI_CSMAP_EN_Pos)
#define SPI_CSMAP_EN                                       (SPI_CSMAP_EN_Msk)

/***************  Bits definition for SPI_OUT_EN  **********************/

#define SPI_OUT_EN_SPI_HOLD_EN_Pos                          ( 3U )
#define SPI_OUT_EN_SPI_HOLD_EN_Msk                          ( 0x1UL << SPI_OUT_EN_SPI_HOLD_EN_Pos )
#define SPI_OUT_EN_SPI_HOLD_EN                              ( SPI_OUT_EN_SPI_HOLD_EN_Msk )

#define SPI_OUT_EN_SPI_WP_EN_Pos                            ( 2U )
#define SPI_OUT_EN_SPI_WP_EN_Msk                            ( 0x1UL << SPI_OUT_EN_SPI_WP_EN_Pos )
#define SPI_OUT_EN_SPI_WP_EN                                ( SPI_OUT_EN_SPI_WP_EN_Msk )

#define SPI_OUT_EN_SPI_MISO_EN_Pos                          ( 1U )
#define SPI_OUT_EN_SPI_MISO_EN_Msk                          ( 0x1UL << SPI_OUT_EN_SPI_MISO_EN_Pos )
#define SPI_OUT_EN_SPI_MISO_EN                              ( SPI_OUT_EN_SPI_MISO_EN_Msk )


/***************  Bits definition for SPI_MEMO_ACC  **********************/

#define SPI_MEMO_ACC_DATA_MODE_Pos                          ( 25U )
#define SPI_MEMO_ACC_DATA_MODE_Msk                          ( 0x3UL << SPI_MEMO_ACC_DATA_MODE_Pos )
#define SPI_MEMO_ACC_DATA_MODE                              ( SPI_MEMO_ACC_DATA_MODE_Msk )
#define SPI_MEMO_ACC_DATA_MODE_0                            ( 0x1UL << SPI_MEMO_ACC_DATA_MODE_Pos )
#define SPI_MEMO_ACC_DATA_MODE_1                            ( 0x2UL << SPI_MEMO_ACC_DATA_MODE_Pos )

#define SPI_MEMO_ACC_ALTER_BYTE_MODE_Pos                    ( 23U )
#define SPI_MEMO_ACC_ALTER_BYTE_MODE_Msk                    ( 0x3UL << SPI_MEMO_ACC_ALTER_BYTE_MODE_Pos )
#define SPI_MEMO_ACC_ALTER_BYTE_MODE                        ( SPI_MEMO_ACC_ALTER_BYTE_MODE_Msk )
#define SPI_MEMO_ACC_ALTER_BYTE_MODE_0                      ( 0x1UL << SPI_MEMO_ACC_ALTER_BYTE_MODE_Pos )
#define SPI_MEMO_ACC_ALTER_BYTE_MODE_1                      ( 0x2UL << SPI_MEMO_ACC_ALTER_BYTE_MODE_Pos )

#define SPI_MEMO_ACC_ADDR_MODE_Pos                          ( 21U )
#define SPI_MEMO_ACC_ADDR_MODE_Msk                          ( 0x3UL << SPI_MEMO_ACC_ADDR_MODE_Pos )
#define SPI_MEMO_ACC_ADDR_MODE                              ( SPI_MEMO_ACC_ADDR_MODE_Msk )
#define SPI_MEMO_ACC_ADDR_MODE_0                            ( 0x1UL << SPI_MEMO_ACC_ADDR_MODE_Pos )
#define SPI_MEMO_ACC_ADDR_MODE_1                            ( 0x2UL << SPI_MEMO_ACC_ADDR_MODE_Pos )

#define SPI_MEMO_ACC_INSTR_MODE_Pos                         ( 19U )
#define SPI_MEMO_ACC_INSTR_MODE_Msk                         ( 0x3UL << SPI_MEMO_ACC_INSTR_MODE_Pos )
#define SPI_MEMO_ACC_INSTR_MODE                             ( SPI_MEMO_ACC_INSTR_MODE_Msk )
#define SPI_MEMO_ACC_INSTR_MODE_0                           ( 0x1UL << SPI_MEMO_ACC_INSTR_MODE_Pos )
#define SPI_MEMO_ACC_INSTR_MODE_1                           ( 0x2UL << SPI_MEMO_ACC_INSTR_MODE_Pos )

#define SPI_MEMO_ACC_ADDR_WIDTH_Pos                         ( 17U )
#define SPI_MEMO_ACC_ADDR_WIDTH_Msk                         ( 0x3UL << SPI_MEMO_ACC_ADDR_WIDTH_Pos )
#define SPI_MEMO_ACC_ADDR_WIDTH                             ( SPI_MEMO_ACC_ADDR_WIDTH_Msk )
#define SPI_MEMO_ACC_ADDR_WIDTH_0                           ( 0x1UL << SPI_MEMO_ACC_ADDR_WIDTH_Pos )
#define SPI_MEMO_ACC_ADDR_WIDTH_1                           ( 0x2UL << SPI_MEMO_ACC_ADDR_WIDTH_Pos )

#define SPI_MEMO_ACC_DUMMY_BYTE_SIZE_Pos                    ( 12U )
#define SPI_MEMO_ACC_DUMMY_BYTE_SIZE_Msk                    ( 0x3UL << SPI_MEMO_ACC_DUMMY_BYTE_SIZE_Pos )
#define SPI_MEMO_ACC_DUMMY_BYTE_SIZE                        ( SPI_MEMO_ACC_DUMMY_BYTE_SIZE_Msk )
#define SPI_MEMO_ACC_DUMMY_BYTE_SIZE_0                      ( 0x1UL << SPI_MEMO_ACC_DUMMY_BYTE_SIZE_Pos )
#define SPI_MEMO_ACC_DUMMY_BYTE_SIZE_1                      ( 0x2UL << SPI_MEMO_ACC_DUMMY_BYTE_SIZE_Pos )

#define SPI_MEMO_ACC_RD_DB_EN_Pos                           ( 11U )
#define SPI_MEMO_ACC_RD_DB_EN_Msk                           ( 0x1UL << SPI_MEMO_ACC_RD_DB_EN_Pos )
#define SPI_MEMO_ACC_RD_DB_EN                               ( SPI_MEMO_ACC_RD_DB_EN_Msk )

#define SPI_MEMO_ACC_WR_DB_EN_Pos                           ( 10U )
#define SPI_MEMO_ACC_WR_DB_EN_Msk                           ( 0x1UL << SPI_MEMO_ACC_WR_DB_EN_Pos )
#define SPI_MEMO_ACC_WR_DB_EN                               ( SPI_MEMO_ACC_WR_DB_EN_Msk )

#define SPI_MEMO_ACC_ALTER_BYTE_SIZE_Pos                    ( 7U )
#define SPI_MEMO_ACC_ALTER_BYTE_SIZE_Msk                    ( 0x3UL << SPI_MEMO_ACC_ALTER_BYTE_SIZE_Pos )
#define SPI_MEMO_ACC_ALTER_BYTE_SIZE                        ( SPI_MEMO_ACC_ALTER_BYTE_SIZE_Msk )
#define SPI_MEMO_ACC_ALTER_BYTE_SIZE_0                      ( 0x1UL << SPI_MEMO_ACC_ALTER_BYTE_SIZE_Pos )
#define SPI_MEMO_ACC_ALTER_BYTE_SIZE_1                      ( 0x2UL << SPI_MEMO_ACC_ALTER_BYTE_SIZE_Pos )

#define SPI_MEMO_ACC_RD_AB_EN_Pos                           ( 6U )
#define SPI_MEMO_ACC_RD_AB_EN_Msk                           ( 0x1UL << SPI_MEMO_ACC_RD_AB_EN_Pos )
#define SPI_MEMO_ACC_RD_AB_EN                               ( SPI_MEMO_ACC_RD_AB_EN_Msk )

#define SPI_MEMO_ACC_WR_AB_EN_Pos                           ( 5U )
#define SPI_MEMO_ACC_WR_AB_EN_Msk                           ( 0x1UL << SPI_MEMO_ACC_WR_AB_EN_Pos )
#define SPI_MEMO_ACC_WR_AB_EN                               ( SPI_MEMO_ACC_WR_AB_EN_Msk )

#define SPI_MEMO_ACC_DISABLE_CMD_Pos                        ( 4U )
#define SPI_MEMO_ACC_DISABLE_CMD_Msk                        ( 0x1UL << SPI_MEMO_ACC_DISABLE_CMD_Pos )
#define SPI_MEMO_ACC_DISABLE_CMD                            ( SPI_MEMO_ACC_DISABLE_CMD_Msk )

#define SPI_MEMO_ACC_CON_MODE_EN_Pos                        ( 3U )
#define SPI_MEMO_ACC_CON_MODE_EN_Msk                        ( 0x1UL << SPI_MEMO_ACC_CON_MODE_EN_Pos )
#define SPI_MEMO_ACC_CON_MODE_EN                            ( SPI_MEMO_ACC_CON_MODE_EN_Msk )

#define SPI_MEMO_ACC_CON_CS_WAIT_EN_Pos                     ( 1U )
#define SPI_MEMO_ACC_CON_CS_WAIT_EN_Msk                     ( 0x1UL << SPI_MEMO_ACC_CON_CS_WAIT_EN_Pos )
#define SPI_MEMO_ACC_CON_CS_WAIT_EN                         ( SPI_MEMO_ACC_CON_CS_WAIT_EN_Msk )

#define SPI_MEMO_ACC_SPI_ACC_EN_Pos                         ( 0U )
#define SPI_MEMO_ACC_SPI_ACC_EN_Msk                         ( 0x1UL << SPI_MEMO_ACC_SPI_ACC_EN_Pos )
#define SPI_MEMO_ACC_SPI_ACC_EN                             ( SPI_MEMO_ACC_SPI_ACC_EN_Msk )


/***************  Bits definition for SPI_CMD  **********************/

#define SPI_CMD_WR_CMD_Pos                                  ( 8U )
#define SPI_CMD_WR_CMD_Msk                                  ( 0xffUL << SPI_CMD_WR_CMD_Pos )
#define SPI_CMD_WR_CMD                                      ( SPI_CMD_WR_CMD_Msk )
#define SPI_CMD_WR_CMD_0                                    ( 0x1UL << SPI_CMD_WR_CMD_Pos )
#define SPI_CMD_WR_CMD_1                                    ( 0x2UL << SPI_CMD_WR_CMD_Pos )
#define SPI_CMD_WR_CMD_2                                    ( 0x4UL << SPI_CMD_WR_CMD_Pos )
#define SPI_CMD_WR_CMD_3                                    ( 0x8UL << SPI_CMD_WR_CMD_Pos )
#define SPI_CMD_WR_CMD_4                                    ( 0x10UL << SPI_CMD_WR_CMD_Pos )
#define SPI_CMD_WR_CMD_5                                    ( 0x20UL << SPI_CMD_WR_CMD_Pos )
#define SPI_CMD_WR_CMD_6                                    ( 0x40UL << SPI_CMD_WR_CMD_Pos )
#define SPI_CMD_WR_CMD_7                                    ( 0x80UL << SPI_CMD_WR_CMD_Pos )

#define SPI_CMD_RD_CMD_Pos                                  ( 0U )
#define SPI_CMD_RD_CMD_Msk                                  ( 0xffUL << SPI_CMD_RD_CMD_Pos )
#define SPI_CMD_RD_CMD                                      ( SPI_CMD_RD_CMD_Msk )
#define SPI_CMD_RD_CMD_0                                    ( 0x1UL << SPI_CMD_RD_CMD_Pos )
#define SPI_CMD_RD_CMD_1                                    ( 0x2UL << SPI_CMD_RD_CMD_Pos )
#define SPI_CMD_RD_CMD_2                                    ( 0x4UL << SPI_CMD_RD_CMD_Pos )
#define SPI_CMD_RD_CMD_3                                    ( 0x8UL << SPI_CMD_RD_CMD_Pos )
#define SPI_CMD_RD_CMD_4                                    ( 0x10UL << SPI_CMD_RD_CMD_Pos )
#define SPI_CMD_RD_CMD_5                                    ( 0x20UL << SPI_CMD_RD_CMD_Pos )
#define SPI_CMD_RD_CMD_6                                    ( 0x40UL << SPI_CMD_RD_CMD_Pos )
#define SPI_CMD_RD_CMD_7                                    ( 0x80UL << SPI_CMD_RD_CMD_Pos )


/***************  Bits definition for SPI_ALTER_BYTE  **********************/

#define SPI_ALTER_BYTE_ALTER_BYTE_Pos                       ( 0U )
#define SPI_ALTER_BYTE_ALTER_BYTE_Msk                       ( 0xffffffffUL << SPI_ALTER_BYTE_ALTER_BYTE_Pos )
#define SPI_ALTER_BYTE_ALTER_BYTE                           ( SPI_ALTER_BYTE_ALTER_BYTE_Msk )


/***************  Bits definition for SPI_CS_WAIT_VAL  **********************/

#define SPI_CS_WAIT_VAL_CON_CS_WAIT_VAL_Pos                 ( 0U )
#define SPI_CS_WAIT_VAL_CON_CS_WAIT_VAL_Msk                 ( 0xffffUL << SPI_CS_WAIT_VAL_CON_CS_WAIT_VAL_Pos )
#define SPI_CS_WAIT_VAL_CON_CS_WAIT_VAL                     ( SPI_CS_WAIT_VAL_CON_CS_WAIT_VAL_Msk )


/***************  Bits definition for I2C_SLAVE_ADDR1  **********************/

#define I2C_SLAVE_ADDR1_ADDR17_Pos                          ( 7U )
#define I2C_SLAVE_ADDR1_ADDR17_Msk                          ( 0x1UL << I2C_SLAVE_ADDR1_ADDR17_Pos )
#define I2C_SLAVE_ADDR1_ADDR17                              ( I2C_SLAVE_ADDR1_ADDR17_Msk )


#define I2C_SLAVE_ADDR1_ADDR16_Pos                          ( 6U )
#define I2C_SLAVE_ADDR1_ADDR16_Msk                          ( 0x1UL << I2C_SLAVE_ADDR1_ADDR16_Pos )
#define I2C_SLAVE_ADDR1_ADDR16                              ( I2C_SLAVE_ADDR1_ADDR16_Msk )


#define I2C_SLAVE_ADDR1_ADDR15_Pos                          ( 5U )
#define I2C_SLAVE_ADDR1_ADDR15_Msk                          ( 0x1UL << I2C_SLAVE_ADDR1_ADDR15_Pos )
#define I2C_SLAVE_ADDR1_ADDR15                              ( I2C_SLAVE_ADDR1_ADDR15_Msk )


#define I2C_SLAVE_ADDR1_ADDR14_Pos                          ( 4U )
#define I2C_SLAVE_ADDR1_ADDR14_Msk                          ( 0x1UL << I2C_SLAVE_ADDR1_ADDR14_Pos )
#define I2C_SLAVE_ADDR1_ADDR14                              ( I2C_SLAVE_ADDR1_ADDR14_Msk )


#define I2C_SLAVE_ADDR1_ADDR13_Pos                          ( 3U )
#define I2C_SLAVE_ADDR1_ADDR13_Msk                          ( 0x1UL << I2C_SLAVE_ADDR1_ADDR13_Pos )
#define I2C_SLAVE_ADDR1_ADDR13                              ( I2C_SLAVE_ADDR1_ADDR13_Msk )


#define I2C_SLAVE_ADDR1_ADDR12_Pos                          ( 2U )
#define I2C_SLAVE_ADDR1_ADDR12_Msk                          ( 0x1UL << I2C_SLAVE_ADDR1_ADDR12_Pos )
#define I2C_SLAVE_ADDR1_ADDR12                              ( I2C_SLAVE_ADDR1_ADDR12_Msk )


#define I2C_SLAVE_ADDR1_ADDR11_Pos                          ( 1U )
#define I2C_SLAVE_ADDR1_ADDR11_Msk                          ( 0x1UL << I2C_SLAVE_ADDR1_ADDR11_Pos )
#define I2C_SLAVE_ADDR1_ADDR11                              ( I2C_SLAVE_ADDR1_ADDR11_Msk )



/***************  Bits definition for I2C_CLK_DIV  **********************/

#define I2C_CLK_DIV_I2C_CLK_DIV_Pos                         ( 0U )
#define I2C_CLK_DIV_I2C_CLK_DIV_Msk                         ( 0xfffUL << I2C_CLK_DIV_I2C_CLK_DIV_Pos )
#define I2C_CLK_DIV_I2C_CLK_DIV                             ( I2C_CLK_DIV_I2C_CLK_DIV_Msk )


/***************  Bits definition for I2C_CR  **********************/

#define I2C_CR_SU_HD_FIXEN_Pos                              ( 24U )
#define I2C_CR_SU_HD_FIXEN_Msk                              ( 0x1UL << I2C_CR_SU_HD_FIXEN_Pos )
#define I2C_CR_SU_HD_FIXEN                                  ( I2C_CR_SU_HD_FIXEN_Msk )

#define I2C_CR_MARLO_SEL_Pos                                ( 23U )
#define I2C_CR_MARLO_SEL_Msk                                ( 0x1UL << I2C_CR_MARLO_SEL_Pos )
#define I2C_CR_MARLO_SEL                                    ( I2C_CR_MARLO_SEL_Msk )

#define I2C_CR_TX_RX_FLAG_INTEN_Pos                         ( 22U )
#define I2C_CR_TX_RX_FLAG_INTEN_Msk                         ( 0x1UL << I2C_CR_TX_RX_FLAG_INTEN_Pos )
#define I2C_CR_TX_RX_FLAG_INTEN                             ( I2C_CR_TX_RX_FLAG_INTEN_Msk )

#define I2C_CR_NACKF_INTEN_Pos                              ( 21U )
#define I2C_CR_NACKF_INTEN_Msk                              ( 0x1UL << I2C_CR_NACKF_INTEN_Pos )
#define I2C_CR_NACKF_INTEN                                  ( I2C_CR_NACKF_INTEN_Msk )

#define I2C_CR_STOPF_INTEN_Pos                              ( 20U )
#define I2C_CR_STOPF_INTEN_Msk                              ( 0x1UL << I2C_CR_STOPF_INTEN_Pos )
#define I2C_CR_STOPF_INTEN                                  ( I2C_CR_STOPF_INTEN_Msk )

#define I2C_CR_RX_ADDR3_INTEN_Pos                           ( 19U )
#define I2C_CR_RX_ADDR3_INTEN_Msk                           ( 0x1UL << I2C_CR_RX_ADDR3_INTEN_Pos )
#define I2C_CR_RX_ADDR3_INTEN                               ( I2C_CR_RX_ADDR3_INTEN_Msk )

#define I2C_CR_DMA_EN_Pos                                   ( 18U )
#define I2C_CR_DMA_EN_Msk                                   ( 0x1UL << I2C_CR_DMA_EN_Pos )
#define I2C_CR_DMA_EN                                       ( I2C_CR_DMA_EN_Msk )

#define I2C_CR_TXE_SEL_Pos                                  ( 17U )
#define I2C_CR_TXE_SEL_Msk                                  ( 0x1UL << I2C_CR_TXE_SEL_Pos )
#define I2C_CR_TXE_SEL                                      ( I2C_CR_TXE_SEL_Msk )

#define I2C_CR_MARLO_INTEN_Pos                              ( 16U )
#define I2C_CR_MARLO_INTEN_Msk                              ( 0x1UL << I2C_CR_MARLO_INTEN_Pos )
#define I2C_CR_MARLO_INTEN                                  ( I2C_CR_MARLO_INTEN_Msk )

#define I2C_CR_TX_AUTO_EN_Pos                               ( 15U )
#define I2C_CR_TX_AUTO_EN_Msk                               ( 0x1UL << I2C_CR_TX_AUTO_EN_Pos )
#define I2C_CR_TX_AUTO_EN                                   ( I2C_CR_TX_AUTO_EN_Msk )

#define I2C_CR_OD_MODE_Pos                                  ( 14U )
#define I2C_CR_OD_MODE_Msk                                  ( 0x1UL << I2C_CR_OD_MODE_Pos )
#define I2C_CR_OD_MODE                                      ( I2C_CR_OD_MODE_Msk )

#define I2C_CR_DETR_INT_EN_Pos                              ( 13U )
#define I2C_CR_DETR_INT_EN_Msk                              ( 0x1UL << I2C_CR_DETR_INT_EN_Pos )
#define I2C_CR_DETR_INT_EN                                  ( I2C_CR_DETR_INT_EN_Msk )

#define I2C_CR_RX_ADDR2_INT_EN_Pos                          ( 12U )
#define I2C_CR_RX_ADDR2_INT_EN_Msk                          ( 0x1UL << I2C_CR_RX_ADDR2_INT_EN_Pos )
#define I2C_CR_RX_ADDR2_INT_EN                              ( I2C_CR_RX_ADDR2_INT_EN_Msk )

#define I2C_CR_OVR_INT_EN_Pos                               ( 11U )
#define I2C_CR_OVR_INT_EN_Msk                               ( 0x1UL << I2C_CR_OVR_INT_EN_Pos )
#define I2C_CR_OVR_INT_EN                                   ( I2C_CR_OVR_INT_EN_Msk )

#define I2C_CR_RXNE_INT_EN_Pos                              ( 10U )
#define I2C_CR_RXNE_INT_EN_Msk                              ( 0x1UL << I2C_CR_RXNE_INT_EN_Pos )
#define I2C_CR_RXNE_INT_EN                                  ( I2C_CR_RXNE_INT_EN_Msk )

#define I2C_CR_TXE_INT_EN_Pos                               ( 9U )
#define I2C_CR_TXE_INT_EN_Msk                               ( 0x1UL << I2C_CR_TXE_INT_EN_Pos )
#define I2C_CR_TXE_INT_EN                                   ( I2C_CR_TXE_INT_EN_Msk )

#define I2C_CR_RX_ADDR1_INT_EN_Pos                          ( 8U )
#define I2C_CR_RX_ADDR1_INT_EN_Msk                          ( 0x1UL << I2C_CR_RX_ADDR1_INT_EN_Pos )
#define I2C_CR_RX_ADDR1_INT_EN                              ( I2C_CR_RX_ADDR1_INT_EN_Msk )

#define I2C_CR_MTF_INT_EN_Pos                               ( 7U )
#define I2C_CR_MTF_INT_EN_Msk                               ( 0x1UL << I2C_CR_MTF_INT_EN_Pos )
#define I2C_CR_MTF_INT_EN                                   ( I2C_CR_MTF_INT_EN_Msk )

#define I2C_CR_TACK_Pos                                     ( 6U )
#define I2C_CR_TACK_Msk                                     ( 0x1UL << I2C_CR_TACK_Pos )
#define I2C_CR_TACK                                         ( I2C_CR_TACK_Msk )

#define I2C_CR_STOP_Pos                                     ( 5U )
#define I2C_CR_STOP_Msk                                     ( 0x1UL << I2C_CR_STOP_Pos )
#define I2C_CR_STOP                                         ( I2C_CR_STOP_Msk )

#define I2C_CR_START_Pos                                    ( 4U )
#define I2C_CR_START_Msk                                    ( 0x1UL << I2C_CR_START_Pos )
#define I2C_CR_START                                        ( I2C_CR_START_Msk )

#define I2C_CR_TX_Pos                                       ( 3U )
#define I2C_CR_TX_Msk                                       ( 0x1UL << I2C_CR_TX_Pos )
#define I2C_CR_TX                                           ( I2C_CR_TX_Msk )

#define I2C_CR_MASTER_Pos                                   ( 2U )
#define I2C_CR_MASTER_Msk                                   ( 0x1UL << I2C_CR_MASTER_Pos )
#define I2C_CR_MASTER                                       ( I2C_CR_MASTER_Msk )

#define I2C_CR_NOSTRETCH_Pos                                ( 1U )
#define I2C_CR_NOSTRETCH_Msk                                ( 0x1UL << I2C_CR_NOSTRETCH_Pos )
#define I2C_CR_NOSTRETCH                                    ( I2C_CR_NOSTRETCH_Msk )

#define I2C_CR_MEN_Pos                                      ( 0U )
#define I2C_CR_MEN_Msk                                      ( 0x1UL << I2C_CR_MEN_Pos )
#define I2C_CR_MEN                                          ( I2C_CR_MEN_Msk )


/***************  Bits definition for I2C_SR  **********************/

#define I2C_SR_NACKF_Pos                                    ( 17U )
#define I2C_SR_NACKF_Msk                                    ( 0x1UL << I2C_SR_NACKF_Pos )
#define I2C_SR_NACKF                                        ( I2C_SR_NACKF_Msk )

#define I2C_SR_TIMEOUTBF_Pos                                ( 16U )
#define I2C_SR_TIMEOUTBF_Msk                                ( 0x1UL << I2C_SR_TIMEOUTBF_Pos )
#define I2C_SR_TIMEOUTBF                                    ( I2C_SR_TIMEOUTBF_Msk )

#define I2C_SR_TIMEOUTAF_Pos                                ( 15U )
#define I2C_SR_TIMEOUTAF_Msk                                ( 0x1UL << I2C_SR_TIMEOUTAF_Pos )
#define I2C_SR_TIMEOUTAF                                    ( I2C_SR_TIMEOUTAF_Msk )

#define I2C_SR_RX_ADDR3_Pos                                 ( 14U )
#define I2C_SR_RX_ADDR3_Msk                                 ( 0x1UL << I2C_SR_RX_ADDR3_Pos )
#define I2C_SR_RX_ADDR3                                     ( I2C_SR_RX_ADDR3_Msk )

#define I2C_SR_DETR_Pos                                     ( 13U )
#define I2C_SR_DETR_Msk                                     ( 0x1UL << I2C_SR_DETR_Pos )
#define I2C_SR_DETR                                         ( I2C_SR_DETR_Msk )

#define I2C_SR_RX_ADDR2_Pos                                 ( 12U )
#define I2C_SR_RX_ADDR2_Msk                                 ( 0x1UL << I2C_SR_RX_ADDR2_Pos )
#define I2C_SR_RX_ADDR2                                     ( I2C_SR_RX_ADDR2_Msk )

#define I2C_SR_OVR_Pos                                      ( 11U )
#define I2C_SR_OVR_Msk                                      ( 0x1UL << I2C_SR_OVR_Pos )
#define I2C_SR_OVR                                          ( I2C_SR_OVR_Msk )

#define I2C_SR_RXNE_Pos                                     ( 10U )
#define I2C_SR_RXNE_Msk                                     ( 0x1UL << I2C_SR_RXNE_Pos )
#define I2C_SR_RXNE                                         ( I2C_SR_RXNE_Msk )

#define I2C_SR_TXE_Pos                                      ( 9U )
#define I2C_SR_TXE_Msk                                      ( 0x1UL << I2C_SR_TXE_Pos )
#define I2C_SR_TXE                                          ( I2C_SR_TXE_Msk )

#define I2C_SR_RX_ADDR1_Pos                                 ( 8U )
#define I2C_SR_RX_ADDR1_Msk                                 ( 0x1UL << I2C_SR_RX_ADDR1_Pos )
#define I2C_SR_RX_ADDR1                                     ( I2C_SR_RX_ADDR1_Msk )

#define I2C_SR_MTF_Pos                                      ( 7U )
#define I2C_SR_MTF_Msk                                      ( 0x1UL << I2C_SR_MTF_Pos )
#define I2C_SR_MTF                                          ( I2C_SR_MTF_Msk )

#define I2C_SR_MARLO_Pos                                    ( 6U )
#define I2C_SR_MARLO_Msk                                    ( 0x1UL << I2C_SR_MARLO_Pos )
#define I2C_SR_MARLO                                        ( I2C_SR_MARLO_Msk )

#define I2C_SR_TX_RX_FLAG_Pos                               ( 5U )
#define I2C_SR_TX_RX_FLAG_Msk                               ( 0x1UL << I2C_SR_TX_RX_FLAG_Pos )
#define I2C_SR_TX_RX_FLAG                                   ( I2C_SR_TX_RX_FLAG_Msk )

#define I2C_SR_BUS_BUSY_Pos                                 ( 4U )
#define I2C_SR_BUS_BUSY_Msk                                 ( 0x1UL << I2C_SR_BUS_BUSY_Pos )
#define I2C_SR_BUS_BUSY                                     ( I2C_SR_BUS_BUSY_Msk )

#define I2C_SR_SRW_Pos                                      ( 3U )
#define I2C_SR_SRW_Msk                                      ( 0x1UL << I2C_SR_SRW_Pos )
#define I2C_SR_SRW                                          ( I2C_SR_SRW_Msk )

#define I2C_SR_STOPF_Pos                                    ( 2U )
#define I2C_SR_STOPF_Msk                                    ( 0x1UL << I2C_SR_STOPF_Pos )
#define I2C_SR_STOPF                                        ( I2C_SR_STOPF_Msk )

#define I2C_SR_STARTF_Pos                                   ( 1U )
#define I2C_SR_STARTF_Msk                                   ( 0x1UL << I2C_SR_STARTF_Pos )
#define I2C_SR_STARTF                                       ( I2C_SR_STARTF_Msk )

#define I2C_SR_RACK_Pos                                     ( 0U )
#define I2C_SR_RACK_Msk                                     ( 0x1UL << I2C_SR_RACK_Pos )
#define I2C_SR_RACK                                         ( I2C_SR_RACK_Msk )


/***************  Bits definition for I2C_DR  **********************/

#define I2C_DR_I2CDR_Pos                                    ( 0U )
#define I2C_DR_I2CDR_Msk                                    ( 0xffUL << I2C_DR_I2CDR_Pos )
#define I2C_DR_I2CDR                                        ( I2C_DR_I2CDR_Msk )
#define I2C_DR_I2CDR_0                                      ( 0x1UL << I2C_DR_I2CDR_Pos )
#define I2C_DR_I2CDR_1                                      ( 0x2UL << I2C_DR_I2CDR_Pos )
#define I2C_DR_I2CDR_2                                      ( 0x4UL << I2C_DR_I2CDR_Pos )
#define I2C_DR_I2CDR_3                                      ( 0x8UL << I2C_DR_I2CDR_Pos )
#define I2C_DR_I2CDR_4                                      ( 0x10UL << I2C_DR_I2CDR_Pos )
#define I2C_DR_I2CDR_5                                      ( 0x20UL << I2C_DR_I2CDR_Pos )
#define I2C_DR_I2CDR_6                                      ( 0x40UL << I2C_DR_I2CDR_Pos )
#define I2C_DR_I2CDR_7                                      ( 0x80UL << I2C_DR_I2CDR_Pos )


/***************  Bits definition for I2C_SLAVE_ADDR2_3  **********************/
#define I2C_SLAVE_ADDR3_Pos                        ( 9U )
#define I2C_SLAVE_ADDR3_Msk                        ( 0x7fUL << I2C_SLAVE_ADDR3_Pos )
#define I2C_SLAVE_ADDR3                            ( I2C_SLAVE__ADDR3_Msk )


#define I2C_SLAVE_ADDR3_EN_Pos                      ( 8U )
#define I2C_SLAVE_ADDR3_EN_Msk                      ( 0x1UL << I2C_SLAVE_ADDR3_EN_Pos )
#define I2C_SLAVE_ADDR3_EN                          ( I2C_SLAVE_ADDR3_EN_Msk )


#define I2C_SLAVE_ADDR2_Pos                        ( 1U )
#define I2C_SLAVE_ADDR2_Msk                        ( 0x7fUL << I2C_SLAVE_ADDR2_Pos )
#define I2C_SLAVE_ADDR2                            ( I2C_SLAVE_ADDR2_Msk )


#define I2C_SLAVE_ADDR2_EN_Pos                      ( 0U )
#define I2C_SLAVE_ADDR2_EN_Msk                      ( 0x1UL << I2C_SLAVE_ADDR2_EN_Pos )
#define I2C_SLAVE_ADDR2_EN                          ( I2C_SLAVE_ADDR2_EN_Msk )


/***************  Bits definition for I2C_DET  **********************/

#define I2C_DET_DETCNT_Pos                                  ( 0U )
#define I2C_DET_DETCNT_Msk                                  ( 0xffffUL << I2C_DET_DETCNT_Pos )
#define I2C_DET_DETCNT                                      ( I2C_DET_DETCNT_Msk )


/***************  Bits definition for I2C_FITER  **********************/

#define I2C_FITER_SDA_IN_DELAY_Pos                          ( 8U )
#define I2C_FITER_SDA_IN_DELAY_Msk                          ( 0x1FUL << I2C_FITER_SDA_IN_DELAY_Pos )
#define I2C_FITER_SDA_IN_DELAY                              ( I2C_FITER_SDA_IN_DELAY_Msk )
#define I2C_FITER_SDA_IN_DELAY_0                            ( 0x1UL << I2C_FITER_SDA_IN_DELAY_Pos )
#define I2C_FITER_SDA_IN_DELAY_1                            ( 0x2UL << I2C_FITER_SDA_IN_DELAY_Pos )
#define I2C_FITER_SDA_IN_DELAY_2                            ( 0x4UL << I2C_FITER_SDA_IN_DELAY_Pos )
#define I2C_FITER_SDA_IN_DELAY_3                            ( 0x8UL << I2C_FITER_SDA_IN_DELAY_Pos )
#define I2C_FITER_SDA_IN_DELAY_4                            ( 0x10UL << I2C_FITER_SDA_IN_DELAY_Pos )

#define I2C_FITER_SCL_FITER_Pos                             ( 0U )
#define I2C_FITER_SCL_FITER_Msk                             ( 0x1FUL << I2C_FITER_SCL_FITER_Pos )
#define I2C_FITER_SCL_FITER                                 ( I2C_FITER_SCL_FITER_Msk )
#define I2C_FITER_SCL_FITER_0                               ( 0x1UL << I2C_FITER_SCL_FITER_Pos )
#define I2C_FITER_SCL_FITER_1                               ( 0x2UL << I2C_FITER_SCL_FITER_Pos )
#define I2C_FITER_SCL_FITER_2                               ( 0x4UL << I2C_FITER_SCL_FITER_Pos )
#define I2C_FITER_SCL_FITER_3                               ( 0x8UL << I2C_FITER_SCL_FITER_Pos )
#define I2C_FITER_SCL_FITER_4                               ( 0x10UL << I2C_FITER_SCL_FITER_Pos )


/***************  Bits definition for I2C_Timeout  **********************/

#define I2C_TIMEOUT_EXTEN_Pos                               ( 31U )
#define I2C_TIMEOUT_EXTEN_Msk                               ( 0x1UL << I2C_TIMEOUT_EXTEN_Pos )
#define I2C_TIMEOUT_EXTEN                                   ( I2C_TIMEOUT_EXTEN_Msk )

#define I2C_TIMEOUTB_INTEN_Pos                         ( 30U )
#define I2C_TIMEOUTB_INTEN_Msk                         ( 0x1UL << I2C_TIMEOUT_TOUTB_INTEN_Pos )
#define I2C_TIMEOUTB_INTEN                             ( I2C_TIMEOUT_TOUTB_INTEN_Msk )

#define I2C_TIMEOUT_EXT_MODE_Pos                            ( 29U )
#define I2C_TIMEOUT_EXT_MODE_Msk                            ( 0x1UL << I2C_TIMEOUT_EXT_MODE_Pos )
#define I2C_TIMEOUT_EXT_MODE                                ( I2C_TIMEOUT_EXT_MODE_Msk )

#define I2C_TIMEOUTB_Pos                            ( 16U )
#define I2C_TIMEOUTB_Msk                            ( 0xfffUL << I2C_TIMEOUT_TIMEOUTB_Pos )
#define I2C_TIMEOUTB                                ( I2C_TIMEOUT_TIMEOUTB_Msk )

#define I2C_TIMOUTEN_Pos                            ( 15U )
#define I2C_TIMOUTEN_Msk                            ( 0x1UL << I2C_TIMEOUT_TIMOUTEN_Pos )
#define I2C_TIMOUTEN                                ( I2C_TIMEOUT_TIMOUTEN_Msk )

#define I2C_TIMEOUTA_INTEN_Pos                         ( 14U )
#define I2C_TIMEOUTA_INTEN_Msk                         ( 0x1UL << I2C_TIMEOUT_TOUTA_INTEN_Pos )
#define I2C_TIMEOUTA_INTEN                             ( I2C_TIMEOUT_TOUTA_INTEN_Msk )

#define I2C_TIMEOUTA_Pos                            ( 0U )
#define I2C_TIMEOUTA_Msk                            ( 0xfffUL << I2C_TIMEOUT_TIMEOUTA_Pos )
#define I2C_TIMEOUTA                                ( I2C_TIMEOUT_TIMEOUTA_Msk )


/***************  Bits definition for FDCAN_RBUFx  **********************/

#define FDCAN_RBUFX_RBUFX_Pos                              ( 0U )
#define FDCAN_RBUFX_RBUFX_Msk                              ( 0xffffffffUL << FDCAN_RBUFX_RBUFX_Pos )
#define FDCAN_RBUFX_RBUFX                                  ( FDCAN_RBUFX_RBUFX_Msk )


/***************  Bits definition for FDCAN_TBUFx  **********************/

#define FDCAN_TBUFX_TBUFX_Pos                              ( 0U )
#define FDCAN_TBUFX_TBUFX_Msk                              ( 0xffffffffUL << FDCAN_TBUFX_TBUFX_Pos )
#define FDCAN_TBUFX_TBUFX                                  ( FDCAN_TBUFX_TBUFX_Msk )


/***************  Bits definition for FDCAN_TTSL  **********************/

#define FDCAN_TTSL_TTS_Pos                                 ( 0U )
#define FDCAN_TTSL_TTS_Msk                                 ( 0xffffffffUL << FDCAN_TTSL_TTS_Pos )
#define FDCAN_TTSL_TTS                                     ( FDCAN_TTSL_TTS_Msk )


/***************  Bits definition for FDCAN_TTSH  **********************/

#define FDCAN_TTSH_TTS_Pos                                 ( 0U )
#define FDCAN_TTSH_TTS_Msk                                 ( 0xffffffffUL << FDCAN_TTSH_TTS_Pos )
#define FDCAN_TTSH_TTS                                     ( FDCAN_TTSH_TTS_Msk )


/***************  Bits definition for FDCAN_CR  **********************/

#define FDCAN_CR_SACK_Pos                                  ( 31U )
#define FDCAN_CR_SACK_Msk                                  ( 0x1UL << FDCAN_CR_SACK_Pos )
#define FDCAN_CR_SACK                                      ( FDCAN_CR_SACK_Msk )

#define FDCAN_CR_ROM_Pos                                   ( 30U )
#define FDCAN_CR_ROM_Msk                                   ( 0x1UL << FDCAN_CR_ROM_Pos )
#define FDCAN_CR_ROM                                       ( FDCAN_CR_ROM_Msk )

#define FDCAN_CR_ROV_Pos                                   ( 29U )
#define FDCAN_CR_ROV_Msk                                   ( 0x1UL << FDCAN_CR_ROV_Pos )
#define FDCAN_CR_ROV                                       ( FDCAN_CR_ROV_Msk )

#define FDCAN_CR_RREL_Pos                                  ( 28U )
#define FDCAN_CR_RREL_Msk                                  ( 0x1UL << FDCAN_CR_RREL_Pos )
#define FDCAN_CR_RREL                                      ( FDCAN_CR_RREL_Msk )

#define FDCAN_CR_RBALL_Pos                                 ( 27U )
#define FDCAN_CR_RBALL_Msk                                 ( 0x1UL << FDCAN_CR_RBALL_Pos )
#define FDCAN_CR_RBALL                                     ( FDCAN_CR_RBALL_Msk )

#define FDCAN_CR_RSTAT_Pos                                 ( 24U )
#define FDCAN_CR_RSTAT_Msk                                 ( 0x3UL << FDCAN_CR_RSTAT_Pos )
#define FDCAN_CR_RSTAT                                     ( FDCAN_CR_RSTAT_Msk )
#define FDCAN_CR_RSTAT_0                                   ( 0x1UL << FDCAN_CR_RSTAT_Pos )
#define FDCAN_CR_RSTAT_1                                   ( 0x2UL << FDCAN_CR_RSTAT_Pos )

#define FDCAN_CR_FD_ISO_Pos                                ( 23U )
#define FDCAN_CR_FD_ISO_Msk                                ( 0x1UL << FDCAN_CR_FD_ISO_Pos )
#define FDCAN_CR_FD_ISO                                    ( FDCAN_CR_FD_ISO_Msk )

#define FDCAN_CR_TSNEXT_Pos                                ( 22U )
#define FDCAN_CR_TSNEXT_Msk                                ( 0x1UL << FDCAN_CR_TSNEXT_Pos )
#define FDCAN_CR_TSNEXT                                    ( FDCAN_CR_TSNEXT_Msk )

#define FDCAN_CR_TSMODE_Pos                                ( 21U )
#define FDCAN_CR_TSMODE_Msk                                ( 0x1UL << FDCAN_CR_TSMODE_Pos )
#define FDCAN_CR_TSMODE                                    ( FDCAN_CR_TSMODE_Msk )

#define FDCAN_CR_TTTBM_Pos                                 ( 20U )
#define FDCAN_CR_TTTBM_Msk                                 ( 0x1UL << FDCAN_CR_TTTBM_Pos )
#define FDCAN_CR_TTTBM                                     ( FDCAN_CR_TTTBM_Msk )

#define FDCAN_CR_TSSTAT_Pos                                ( 16U )
#define FDCAN_CR_TSSTAT_Msk                                ( 0x3UL << FDCAN_CR_TSSTAT_Pos )
#define FDCAN_CR_TSSTAT                                    ( FDCAN_CR_TSSTAT_Msk )
#define FDCAN_CR_TSSTAT_0                                  ( 0x1UL << FDCAN_CR_TSSTAT_Pos )
#define FDCAN_CR_TSSTAT_1                                  ( 0x2UL << FDCAN_CR_TSSTAT_Pos )

#define FDCAN_CR_TBSEL_Pos                                 ( 15U )
#define FDCAN_CR_TBSEL_Msk                                 ( 0x1UL << FDCAN_CR_TBSEL_Pos )
#define FDCAN_CR_TBSEL                                     ( FDCAN_CR_TBSEL_Msk )

#define FDCAN_CR_LOM_Pos                                   ( 14U )
#define FDCAN_CR_LOM_Msk                                   ( 0x1UL << FDCAN_CR_LOM_Pos )
#define FDCAN_CR_LOM                                       ( FDCAN_CR_LOM_Msk )

#define FDCAN_CR_STBY_Pos                                  ( 13U )
#define FDCAN_CR_STBY_Msk                                  ( 0x1UL << FDCAN_CR_STBY_Pos )
#define FDCAN_CR_STBY                                      ( FDCAN_CR_STBY_Msk )

#define FDCAN_CR_TPE_Pos                                   ( 12U )
#define FDCAN_CR_TPE_Msk                                   ( 0x1UL << FDCAN_CR_TPE_Pos )
#define FDCAN_CR_TPE                                       ( FDCAN_CR_TPE_Msk )

#define FDCAN_CR_TPA_Pos                                   ( 11U )
#define FDCAN_CR_TPA_Msk                                   ( 0x1UL << FDCAN_CR_TPA_Pos )
#define FDCAN_CR_TPA                                       ( FDCAN_CR_TPA_Msk )

#define FDCAN_CR_TSONE_Pos                                 ( 10U )
#define FDCAN_CR_TSONE_Msk                                 ( 0x1UL << FDCAN_CR_TSONE_Pos )
#define FDCAN_CR_TSONE                                     ( FDCAN_CR_TSONE_Msk )

#define FDCAN_CR_TSALL_Pos                                 ( 9U )
#define FDCAN_CR_TSALL_Msk                                 ( 0x1UL << FDCAN_CR_TSALL_Pos )
#define FDCAN_CR_TSALL                                     ( FDCAN_CR_TSALL_Msk )

#define FDCAN_CR_TSA_Pos                                   ( 8U )
#define FDCAN_CR_TSA_Msk                                   ( 0x1UL << FDCAN_CR_TSA_Pos )
#define FDCAN_CR_TSA                                       ( FDCAN_CR_TSA_Msk )

#define FDCAN_CR_RESET_Pos                                 ( 7U )
#define FDCAN_CR_RESET_Msk                                 ( 0x1UL << FDCAN_CR_RESET_Pos )
#define FDCAN_CR_RESET                                     ( FDCAN_CR_RESET_Msk )

#define FDCAN_CR_LBME_Pos                                  ( 6U )
#define FDCAN_CR_LBME_Msk                                  ( 0x1UL << FDCAN_CR_LBME_Pos )
#define FDCAN_CR_LBME                                      ( FDCAN_CR_LBME_Msk )

#define FDCAN_CR_LBMI_Pos                                  ( 5U )
#define FDCAN_CR_LBMI_Msk                                  ( 0x1UL << FDCAN_CR_LBMI_Pos )
#define FDCAN_CR_LBMI                                      ( FDCAN_CR_LBMI_Msk )

#define FDCAN_CR_TPSS_Pos                                  ( 4U )
#define FDCAN_CR_TPSS_Msk                                  ( 0x1UL << FDCAN_CR_TPSS_Pos )
#define FDCAN_CR_TPSS                                      ( FDCAN_CR_TPSS_Msk )

#define FDCAN_CR_TSSS_Pos                                  ( 3U )
#define FDCAN_CR_TSSS_Msk                                  ( 0x1UL << FDCAN_CR_TSSS_Pos )
#define FDCAN_CR_TSSS                                      ( FDCAN_CR_TSSS_Msk )

#define FDCAN_CR_RACTIVE_Pos                               ( 2U )
#define FDCAN_CR_RACTIVE_Msk                               ( 0x1UL << FDCAN_CR_RACTIVE_Pos )
#define FDCAN_CR_RACTIVE                                   ( FDCAN_CR_RACTIVE_Msk )

#define FDCAN_CR_TACTIVE_Pos                               ( 1U )
#define FDCAN_CR_TACTIVE_Msk                               ( 0x1UL << FDCAN_CR_TACTIVE_Pos )
#define FDCAN_CR_TACTIVE                                   ( FDCAN_CR_TACTIVE_Msk )

#define FDCAN_CR_BUSOFF_Pos                                ( 0U )
#define FDCAN_CR_BUSOFF_Msk                                ( 0x1UL << FDCAN_CR_BUSOFF_Pos )
#define FDCAN_CR_BUSOFF                                    ( FDCAN_CR_BUSOFF_Msk )


/***************  Bits definition for FDCAN_IR  **********************/

#define FDCAN_IR_EWARN_Pos                                 ( 23U )
#define FDCAN_IR_EWARN_Msk                                 ( 0x1UL << FDCAN_IR_EWARN_Pos )
#define FDCAN_IR_EWARN                                     ( FDCAN_IR_EWARN_Msk )

#define FDCAN_IR_EPASS_Pos                                 ( 22U )
#define FDCAN_IR_EPASS_Msk                                 ( 0x1UL << FDCAN_IR_EPASS_Pos )
#define FDCAN_IR_EPASS                                     ( FDCAN_IR_EPASS_Msk )

#define FDCAN_IR_EPIE_Pos                                  ( 21U )
#define FDCAN_IR_EPIE_Msk                                  ( 0x1UL << FDCAN_IR_EPIE_Pos )
#define FDCAN_IR_EPIE                                      ( FDCAN_IR_EPIE_Msk )

#define FDCAN_IR_EPIF_Pos                                  ( 20U )
#define FDCAN_IR_EPIF_Msk                                  ( 0x1UL << FDCAN_IR_EPIF_Pos )
#define FDCAN_IR_EPIF                                      ( FDCAN_IR_EPIF_Msk )

#define FDCAN_IR_ALIE_Pos                                  ( 19U )
#define FDCAN_IR_ALIE_Msk                                  ( 0x1UL << FDCAN_IR_ALIE_Pos )
#define FDCAN_IR_ALIE                                      ( FDCAN_IR_ALIE_Msk )

#define FDCAN_IR_ALIF_Pos                                  ( 18U )
#define FDCAN_IR_ALIF_Msk                                  ( 0x1UL << FDCAN_IR_ALIF_Pos )
#define FDCAN_IR_ALIF                                      ( FDCAN_IR_ALIF_Msk )

#define FDCAN_IR_BEIE_Pos                                  ( 17U )
#define FDCAN_IR_BEIE_Msk                                  ( 0x1UL << FDCAN_IR_BEIE_Pos )
#define FDCAN_IR_BEIE                                      ( FDCAN_IR_BEIE_Msk )

#define FDCAN_IR_BEIF_Pos                                  ( 16U )
#define FDCAN_IR_BEIF_Msk                                  ( 0x1UL << FDCAN_IR_BEIF_Pos )
#define FDCAN_IR_BEIF                                      ( FDCAN_IR_BEIF_Msk )

#define FDCAN_IR_RIF_Pos                                   ( 15U )
#define FDCAN_IR_RIF_Msk                                   ( 0x1UL << FDCAN_IR_RIF_Pos )
#define FDCAN_IR_RIF                                       ( FDCAN_IR_RIF_Msk )

#define FDCAN_IR_ROIF_Pos                                  ( 14U )
#define FDCAN_IR_ROIF_Msk                                  ( 0x1UL << FDCAN_IR_ROIF_Pos )
#define FDCAN_IR_ROIF                                      ( FDCAN_IR_ROIF_Msk )

#define FDCAN_IR_RFIF_Pos                                  ( 13U )
#define FDCAN_IR_RFIF_Msk                                  ( 0x1UL << FDCAN_IR_RFIF_Pos )
#define FDCAN_IR_RFIF                                      ( FDCAN_IR_RFIF_Msk )

#define FDCAN_IR_RAFIF_Pos                                 ( 12U )
#define FDCAN_IR_RAFIF_Msk                                 ( 0x1UL << FDCAN_IR_RAFIF_Pos )
#define FDCAN_IR_RAFIF                                     ( FDCAN_IR_RAFIF_Msk )

#define FDCAN_IR_TPIF_Pos                                  ( 11U )
#define FDCAN_IR_TPIF_Msk                                  ( 0x1UL << FDCAN_IR_TPIF_Pos )
#define FDCAN_IR_TPIF                                      ( FDCAN_IR_TPIF_Msk )

#define FDCAN_IR_TSIF_Pos                                  ( 10U )
#define FDCAN_IR_TSIF_Msk                                  ( 0x1UL << FDCAN_IR_TSIF_Pos )
#define FDCAN_IR_TSIF                                      ( FDCAN_IR_TSIF_Msk )

#define FDCAN_IR_EIF_Pos                                   ( 9U )
#define FDCAN_IR_EIF_Msk                                   ( 0x1UL << FDCAN_IR_EIF_Pos )
#define FDCAN_IR_EIF                                       ( FDCAN_IR_EIF_Msk )

#define FDCAN_IR_AIF_Pos                                   ( 8U )
#define FDCAN_IR_AIF_Msk                                   ( 0x1UL << FDCAN_IR_AIF_Pos )
#define FDCAN_IR_AIF                                       ( FDCAN_IR_AIF_Msk )

#define FDCAN_IR_RIE_Pos                                   ( 7U )
#define FDCAN_IR_RIE_Msk                                   ( 0x1UL << FDCAN_IR_RIE_Pos )
#define FDCAN_IR_RIE                                       ( FDCAN_IR_RIE_Msk )

#define FDCAN_IR_ROIE_Pos                                  ( 6U )
#define FDCAN_IR_ROIE_Msk                                  ( 0x1UL << FDCAN_IR_ROIE_Pos )
#define FDCAN_IR_ROIE                                      ( FDCAN_IR_ROIE_Msk )

#define FDCAN_IR_RFIE_Pos                                  ( 5U )
#define FDCAN_IR_RFIE_Msk                                  ( 0x1UL << FDCAN_IR_RFIE_Pos )
#define FDCAN_IR_RFIE                                      ( FDCAN_IR_RFIE_Msk )

#define FDCAN_IR_RAFIE_Pos                                 ( 4U )
#define FDCAN_IR_RAFIE_Msk                                 ( 0x1UL << FDCAN_IR_RAFIE_Pos )
#define FDCAN_IR_RAFIE                                     ( FDCAN_IR_RAFIE_Msk )

#define FDCAN_IR_TPIE_Pos                                  ( 3U )
#define FDCAN_IR_TPIE_Msk                                  ( 0x1UL << FDCAN_IR_TPIE_Pos )
#define FDCAN_IR_TPIE                                      ( FDCAN_IR_TPIE_Msk )

#define FDCAN_IR_TSIE_Pos                                  ( 2U )
#define FDCAN_IR_TSIE_Msk                                  ( 0x1UL << FDCAN_IR_TSIE_Pos )
#define FDCAN_IR_TSIE                                      ( FDCAN_IR_TSIE_Msk )

#define FDCAN_IR_EIE_Pos                                   ( 1U )
#define FDCAN_IR_EIE_Msk                                   ( 0x1UL << FDCAN_IR_EIE_Pos )
#define FDCAN_IR_EIE                                       ( FDCAN_IR_EIE_Msk )

#define FDCAN_IR_TSFF_Pos                                  ( 0U )
#define FDCAN_IR_TSFF_Msk                                  ( 0x1UL << FDCAN_IR_TSFF_Pos )
#define FDCAN_IR_TSFF                                      ( FDCAN_IR_TSFF_Msk )


/***************  Bits definition for FDCAN_LIMIT  **********************/

#define FDCAN_LIMIT_AFWL_Pos                               ( 4U )
#define FDCAN_LIMIT_AFWL_Msk                               ( 0xfUL << FDCAN_LIMIT_AFWL_Pos )
#define FDCAN_LIMIT_AFWL                                   ( FDCAN_LIMIT_AFWL_Msk )
#define FDCAN_LIMIT_AFWL_0                                 ( 0x1UL << FDCAN_LIMIT_AFWL_Pos )
#define FDCAN_LIMIT_AFWL_1                                 ( 0x2UL << FDCAN_LIMIT_AFWL_Pos )
#define FDCAN_LIMIT_AFWL_2                                 ( 0x4UL << FDCAN_LIMIT_AFWL_Pos )
#define FDCAN_LIMIT_AFWL_3                                 ( 0x8UL << FDCAN_LIMIT_AFWL_Pos )

#define FDCAN_LIMIT_EWL_Pos                                ( 0U )
#define FDCAN_LIMIT_EWL_Msk                                ( 0xfUL << FDCAN_LIMIT_EWL_Pos )
#define FDCAN_LIMIT_EWL                                    ( FDCAN_LIMIT_EWL_Msk )
#define FDCAN_LIMIT_EWL_0                                  ( 0x1UL << FDCAN_LIMIT_EWL_Pos )
#define FDCAN_LIMIT_EWL_1                                  ( 0x2UL << FDCAN_LIMIT_EWL_Pos )
#define FDCAN_LIMIT_EWL_2                                  ( 0x4UL << FDCAN_LIMIT_EWL_Pos )
#define FDCAN_LIMIT_EWL_3                                  ( 0x8UL << FDCAN_LIMIT_EWL_Pos )


/***************  Bits definition for FDCAN_SBTR  **********************/

#define FDCAN_SBTR_S_PRESC_Pos                             ( 24U )
#define FDCAN_SBTR_S_PRESC_Msk                             ( 0xffUL << FDCAN_SBTR_S_PRESC_Pos )
#define FDCAN_SBTR_S_PRESC                                 ( FDCAN_SBTR_S_PRESC_Msk )
#define FDCAN_SBTR_S_PRESC_0                               ( 0x1UL << FDCAN_SBTR_S_PRESC_Pos )
#define FDCAN_SBTR_S_PRESC_1                               ( 0x2UL << FDCAN_SBTR_S_PRESC_Pos )
#define FDCAN_SBTR_S_PRESC_2                               ( 0x4UL << FDCAN_SBTR_S_PRESC_Pos )
#define FDCAN_SBTR_S_PRESC_3                               ( 0x8UL << FDCAN_SBTR_S_PRESC_Pos )
#define FDCAN_SBTR_S_PRESC_4                               ( 0x10UL << FDCAN_SBTR_S_PRESC_Pos )
#define FDCAN_SBTR_S_PRESC_5                               ( 0x20UL << FDCAN_SBTR_S_PRESC_Pos )
#define FDCAN_SBTR_S_PRESC_6                               ( 0x40UL << FDCAN_SBTR_S_PRESC_Pos )
#define FDCAN_SBTR_S_PRESC_7                               ( 0x80UL << FDCAN_SBTR_S_PRESC_Pos )

#define FDCAN_SBTR_S_SJW_Pos                               ( 16U )
#define FDCAN_SBTR_S_SJW_Msk                               ( 0x7fUL << FDCAN_SBTR_S_SJW_Pos )
#define FDCAN_SBTR_S_SJW                                   ( FDCAN_SBTR_S_SJW_Msk )
#define FDCAN_SBTR_S_SJW_0                                 ( 0x1UL << FDCAN_SBTR_S_SJW_Pos )
#define FDCAN_SBTR_S_SJW_1                                 ( 0x2UL << FDCAN_SBTR_S_SJW_Pos )
#define FDCAN_SBTR_S_SJW_2                                 ( 0x4UL << FDCAN_SBTR_S_SJW_Pos )
#define FDCAN_SBTR_S_SJW_3                                 ( 0x8UL << FDCAN_SBTR_S_SJW_Pos )
#define FDCAN_SBTR_S_SJW_4                                 ( 0x10UL << FDCAN_SBTR_S_SJW_Pos )
#define FDCAN_SBTR_S_SJW_5                                 ( 0x20UL << FDCAN_SBTR_S_SJW_Pos )
#define FDCAN_SBTR_S_SJW_6                                 ( 0x40UL << FDCAN_SBTR_S_SJW_Pos )

#define FDCAN_SBTR_S_SEG_2_Pos                             ( 8U )
#define FDCAN_SBTR_S_SEG_2_Msk                             ( 0x7fUL << FDCAN_SBTR_S_SEG_2_Pos )
#define FDCAN_SBTR_S_SEG_2                                 ( FDCAN_SBTR_S_SEG_2_Msk )
#define FDCAN_SBTR_S_SEG_2_0                               ( 0x1UL << FDCAN_SBTR_S_SEG_2_Pos )
#define FDCAN_SBTR_S_SEG_2_1                               ( 0x2UL << FDCAN_SBTR_S_SEG_2_Pos )
#define FDCAN_SBTR_S_SEG_2_2                               ( 0x4UL << FDCAN_SBTR_S_SEG_2_Pos )
#define FDCAN_SBTR_S_SEG_2_3                               ( 0x8UL << FDCAN_SBTR_S_SEG_2_Pos )
#define FDCAN_SBTR_S_SEG_2_4                               ( 0x10UL << FDCAN_SBTR_S_SEG_2_Pos )
#define FDCAN_SBTR_S_SEG_2_5                               ( 0x20UL << FDCAN_SBTR_S_SEG_2_Pos )
#define FDCAN_SBTR_S_SEG_2_6                               ( 0x40UL << FDCAN_SBTR_S_SEG_2_Pos )

#define FDCAN_SBTR_S_SEG_1_Pos                             ( 0U )
#define FDCAN_SBTR_S_SEG_1_Msk                             ( 0xffUL << FDCAN_SBTR_S_SEG_1_Pos )
#define FDCAN_SBTR_S_SEG_1                                 ( FDCAN_SBTR_S_SEG_1_Msk )
#define FDCAN_SBTR_S_SEG_1_0                               ( 0x1UL << FDCAN_SBTR_S_SEG_1_Pos )
#define FDCAN_SBTR_S_SEG_1_1                               ( 0x2UL << FDCAN_SBTR_S_SEG_1_Pos )
#define FDCAN_SBTR_S_SEG_1_2                               ( 0x4UL << FDCAN_SBTR_S_SEG_1_Pos )
#define FDCAN_SBTR_S_SEG_1_3                               ( 0x8UL << FDCAN_SBTR_S_SEG_1_Pos )
#define FDCAN_SBTR_S_SEG_1_4                               ( 0x10UL << FDCAN_SBTR_S_SEG_1_Pos )
#define FDCAN_SBTR_S_SEG_1_5                               ( 0x20UL << FDCAN_SBTR_S_SEG_1_Pos )
#define FDCAN_SBTR_S_SEG_1_6                               ( 0x40UL << FDCAN_SBTR_S_SEG_1_Pos )
#define FDCAN_SBTR_S_SEG_1_7                               ( 0x80UL << FDCAN_SBTR_S_SEG_1_Pos )


/***************  Bits definition for FDCAN_FBTR  **********************/

#define FDCAN_FBTR_F_PRESC_Pos                             ( 24U )
#define FDCAN_FBTR_F_PRESC_Msk                             ( 0xffUL << FDCAN_FBTR_F_PRESC_Pos )
#define FDCAN_FBTR_F_PRESC                                 ( FDCAN_FBTR_F_PRESC_Msk )
#define FDCAN_FBTR_F_PRESC_0                               ( 0x1UL << FDCAN_FBTR_F_PRESC_Pos )
#define FDCAN_FBTR_F_PRESC_1                               ( 0x2UL << FDCAN_FBTR_F_PRESC_Pos )
#define FDCAN_FBTR_F_PRESC_2                               ( 0x4UL << FDCAN_FBTR_F_PRESC_Pos )
#define FDCAN_FBTR_F_PRESC_3                               ( 0x8UL << FDCAN_FBTR_F_PRESC_Pos )
#define FDCAN_FBTR_F_PRESC_4                               ( 0x10UL << FDCAN_FBTR_F_PRESC_Pos )
#define FDCAN_FBTR_F_PRESC_5                               ( 0x20UL << FDCAN_FBTR_F_PRESC_Pos )
#define FDCAN_FBTR_F_PRESC_6                               ( 0x40UL << FDCAN_FBTR_F_PRESC_Pos )
#define FDCAN_FBTR_F_PRESC_7                               ( 0x80UL << FDCAN_FBTR_F_PRESC_Pos )

#define FDCAN_FBTR_F_SJW_Pos                               ( 16U )
#define FDCAN_FBTR_F_SJW_Msk                               ( 0xfUL << FDCAN_FBTR_F_SJW_Pos )
#define FDCAN_FBTR_F_SJW                                   ( FDCAN_FBTR_F_SJW_Msk )
#define FDCAN_FBTR_F_SJW_0                                 ( 0x1UL << FDCAN_FBTR_F_SJW_Pos )
#define FDCAN_FBTR_F_SJW_1                                 ( 0x2UL << FDCAN_FBTR_F_SJW_Pos )
#define FDCAN_FBTR_F_SJW_2                                 ( 0x4UL << FDCAN_FBTR_F_SJW_Pos )
#define FDCAN_FBTR_F_SJW_3                                 ( 0x8UL << FDCAN_FBTR_F_SJW_Pos )

#define FDCAN_FBTR_F_SEG_2_Pos                             ( 8U )
#define FDCAN_FBTR_F_SEG_2_Msk                             ( 0xfUL << FDCAN_FBTR_F_SEG_2_Pos )
#define FDCAN_FBTR_F_SEG_2                                 ( FDCAN_FBTR_F_SEG_2_Msk )
#define FDCAN_FBTR_F_SEG_2_0                               ( 0x1UL << FDCAN_FBTR_F_SEG_2_Pos )
#define FDCAN_FBTR_F_SEG_2_1                               ( 0x2UL << FDCAN_FBTR_F_SEG_2_Pos )
#define FDCAN_FBTR_F_SEG_2_2                               ( 0x4UL << FDCAN_FBTR_F_SEG_2_Pos )
#define FDCAN_FBTR_F_SEG_2_3                               ( 0x8UL << FDCAN_FBTR_F_SEG_2_Pos )

#define FDCAN_FBTR_F_SEG_1_Pos                             ( 0U )
#define FDCAN_FBTR_F_SEG_1_Msk                             ( 0x1fUL << FDCAN_FBTR_F_SEG_1_Pos )
#define FDCAN_FBTR_F_SEG_1                                 ( FDCAN_FBTR_F_SEG_1_Msk )
#define FDCAN_FBTR_F_SEG_1_0                               ( 0x1UL << FDCAN_FBTR_F_SEG_1_Pos )
#define FDCAN_FBTR_F_SEG_1_1                               ( 0x2UL << FDCAN_FBTR_F_SEG_1_Pos )
#define FDCAN_FBTR_F_SEG_1_2                               ( 0x4UL << FDCAN_FBTR_F_SEG_1_Pos )
#define FDCAN_FBTR_F_SEG_1_3                               ( 0x8UL << FDCAN_FBTR_F_SEG_1_Pos )
#define FDCAN_FBTR_F_SEG_1_4                               ( 0x10UL << FDCAN_FBTR_F_SEG_1_Pos )


/***************  Bits definition for FDCAN_TDC  **********************/

#define FDCAN_TDC_TDCEN_Pos                                ( 7U )
#define FDCAN_TDC_TDCEN_Msk                                ( 0x1UL << FDCAN_TDC_TDCEN_Pos )
#define FDCAN_TDC_TDCEN                                    ( FDCAN_TDC_TDCEN_Msk )

#define FDCAN_TDC_SSPOFF_Pos                               ( 0U )
#define FDCAN_TDC_SSPOFF_Msk                               ( 0x7fUL << FDCAN_TDC_SSPOFF_Pos )
#define FDCAN_TDC_SSPOFF                                   ( FDCAN_TDC_SSPOFF_Msk )
#define FDCAN_TDC_SSPOFF_0                                 ( 0x1UL << FDCAN_TDC_SSPOFF_Pos )
#define FDCAN_TDC_SSPOFF_1                                 ( 0x2UL << FDCAN_TDC_SSPOFF_Pos )
#define FDCAN_TDC_SSPOFF_2                                 ( 0x4UL << FDCAN_TDC_SSPOFF_Pos )
#define FDCAN_TDC_SSPOFF_3                                 ( 0x8UL << FDCAN_TDC_SSPOFF_Pos )
#define FDCAN_TDC_SSPOFF_4                                 ( 0x10UL << FDCAN_TDC_SSPOFF_Pos )
#define FDCAN_TDC_SSPOFF_5                                 ( 0x20UL << FDCAN_TDC_SSPOFF_Pos )
#define FDCAN_TDC_SSPOFF_6                                 ( 0x40UL << FDCAN_TDC_SSPOFF_Pos )


/***************  Bits definition for FDCAN_ECC  **********************/

#define FDCAN_ECC_TECNT_Pos                                ( 24U )
#define FDCAN_ECC_TECNT_Msk                                ( 0xffUL << FDCAN_ECC_TECNT_Pos )
#define FDCAN_ECC_TECNT                                    ( FDCAN_ECC_TECNT_Msk )
#define FDCAN_ECC_TECNT_0                                  ( 0x1UL << FDCAN_ECC_TECNT_Pos )
#define FDCAN_ECC_TECNT_1                                  ( 0x2UL << FDCAN_ECC_TECNT_Pos )
#define FDCAN_ECC_TECNT_2                                  ( 0x4UL << FDCAN_ECC_TECNT_Pos )
#define FDCAN_ECC_TECNT_3                                  ( 0x8UL << FDCAN_ECC_TECNT_Pos )
#define FDCAN_ECC_TECNT_4                                  ( 0x10UL << FDCAN_ECC_TECNT_Pos )
#define FDCAN_ECC_TECNT_5                                  ( 0x20UL << FDCAN_ECC_TECNT_Pos )
#define FDCAN_ECC_TECNT_6                                  ( 0x40UL << FDCAN_ECC_TECNT_Pos )
#define FDCAN_ECC_TECNT_7                                  ( 0x80UL << FDCAN_ECC_TECNT_Pos )

#define FDCAN_ECC_RECNT_Pos                                ( 16U )
#define FDCAN_ECC_RECNT_Msk                                ( 0xffUL << FDCAN_ECC_RECNT_Pos )
#define FDCAN_ECC_RECNT                                    ( FDCAN_ECC_RECNT_Msk )
#define FDCAN_ECC_RECNT_0                                  ( 0x1UL << FDCAN_ECC_RECNT_Pos )
#define FDCAN_ECC_RECNT_1                                  ( 0x2UL << FDCAN_ECC_RECNT_Pos )
#define FDCAN_ECC_RECNT_2                                  ( 0x4UL << FDCAN_ECC_RECNT_Pos )
#define FDCAN_ECC_RECNT_3                                  ( 0x8UL << FDCAN_ECC_RECNT_Pos )
#define FDCAN_ECC_RECNT_4                                  ( 0x10UL << FDCAN_ECC_RECNT_Pos )
#define FDCAN_ECC_RECNT_5                                  ( 0x20UL << FDCAN_ECC_RECNT_Pos )
#define FDCAN_ECC_RECNT_6                                  ( 0x40UL << FDCAN_ECC_RECNT_Pos )
#define FDCAN_ECC_RECNT_7                                  ( 0x80UL << FDCAN_ECC_RECNT_Pos )

#define FDCAN_ECC_KOER_Pos                                 ( 5U )
#define FDCAN_ECC_KOER_Msk                                 ( 0x7UL << FDCAN_ECC_KOER_Pos )
#define FDCAN_ECC_KOER                                     ( FDCAN_ECC_KOER_Msk )
#define FDCAN_ECC_KOER_0                                   ( 0x1UL << FDCAN_ECC_KOER_Pos )
#define FDCAN_ECC_KOER_1                                   ( 0x2UL << FDCAN_ECC_KOER_Pos )
#define FDCAN_ECC_KOER_2                                   ( 0x4UL << FDCAN_ECC_KOER_Pos )

#define FDCAN_ECC_ALC_Pos                                  ( 0U )
#define FDCAN_ECC_ALC_Msk                                  ( 0x1fUL << FDCAN_ECC_ALC_Pos )
#define FDCAN_ECC_ALC                                      ( FDCAN_ECC_ALC_Msk )
#define FDCAN_ECC_ALC_0                                    ( 0x1UL << FDCAN_ECC_ALC_Pos )
#define FDCAN_ECC_ALC_1                                    ( 0x2UL << FDCAN_ECC_ALC_Pos )
#define FDCAN_ECC_ALC_2                                    ( 0x4UL << FDCAN_ECC_ALC_Pos )
#define FDCAN_ECC_ALC_3                                    ( 0x8UL << FDCAN_ECC_ALC_Pos )
#define FDCAN_ECC_ALC_4                                    ( 0x10UL << FDCAN_ECC_ALC_Pos )


/***************  Bits definition for FDCAN_ACFCR  **********************/

#define FDCAN_ACFCR_AE_Pos                                 ( 16U )
#define FDCAN_ACFCR_AE_Msk                                 ( 0xffffUL << FDCAN_ACFCR_AE_Pos )
#define FDCAN_ACFCR_AE                                     ( FDCAN_ACFCR_AE_Msk )

#define FDCAN_ACFCR_SELMASK_Pos                            ( 5U )
#define FDCAN_ACFCR_SELMASK_Msk                            ( 0x1UL << FDCAN_ACFCR_SELMASK_Pos )
#define FDCAN_ACFCR_SELMASK                                ( FDCAN_ACFCR_SELMASK_Msk )

#define FDCAN_ACFCR_ACFADR_Pos                             ( 0U )
#define FDCAN_ACFCR_ACFADR_Msk                             ( 0xfUL << FDCAN_ACFCR_ACFADR_Pos )
#define FDCAN_ACFCR_ACFADR                                 ( FDCAN_ACFCR_ACFADR_Msk )
#define FDCAN_ACFCR_ACFADR_0                               ( 0x1UL << FDCAN_ACFCR_ACFADR_Pos )
#define FDCAN_ACFCR_ACFADR_1                               ( 0x2UL << FDCAN_ACFCR_ACFADR_Pos )
#define FDCAN_ACFCR_ACFADR_2                               ( 0x4UL << FDCAN_ACFCR_ACFADR_Pos )
#define FDCAN_ACFCR_ACFADR_3                               ( 0x8UL << FDCAN_ACFCR_ACFADR_Pos )


/***************  Bits definition for FDCAN_ACODR  **********************/

#define FDCAN_ACODR_AIDEE_Pos                              ( 30U )
#define FDCAN_ACODR_AIDEE_Msk                              ( 0x1UL << FDCAN_ACODR_AIDEE_Pos )
#define FDCAN_ACODR_AIDEE                                  ( FDCAN_ACODR_AIDEE_Msk )

#define FDCAN_ACODR_AIDE_Pos                               ( 29U )
#define FDCAN_ACODR_AIDE_Msk                               ( 0x1UL << FDCAN_ACODR_AIDE_Pos )
#define FDCAN_ACODR_AIDE                                   ( FDCAN_ACODR_AIDE_Msk )

#define FDCAN_ACODR_ACODE_AMASK_Pos                        ( 0U )
#define FDCAN_ACODR_ACODE_AMASK_Msk                        ( 0x1fffffffUL << FDCAN_ACODR_ACODE_AMASK_Pos )
#define FDCAN_ACODR_ACODE_AMASK                            ( FDCAN_ACODR_ACODE_AMASK_Msk )


/***************  Bits definition for FDCAN_TIMCFG  **********************/

#define FDCAN_TIMCFG_TIMEPOS_Pos                           ( 1U )
#define FDCAN_TIMCFG_TIMEPOS_Msk                           ( 0x1UL << FDCAN_TIMCFG_TIMEPOS_Pos )
#define FDCAN_TIMCFG_TIMEPOS                               ( FDCAN_TIMCFG_TIMEPOS_Msk )

#define FDCAN_TIMCFG_TIMEEN_Pos                            ( 0U )
#define FDCAN_TIMCFG_TIMEEN_Msk                            ( 0x1UL << FDCAN_TIMCFG_TIMEEN_Pos )
#define FDCAN_TIMCFG_TIMEEN                                ( FDCAN_TIMCFG_TIMEEN_Msk )


/***************  Bits definition for FDCAN_VER  **********************/

#define FDCAN_VER_VER_Pos                                  ( 0U )
#define FDCAN_VER_VER_Msk                                  ( 0xffffUL << FDCAN_VER_VER_Pos )
#define FDCAN_VER_VER                                      ( FDCAN_VER_VER_Msk )


/***************  Bits definition for FDCAN_TTCFG  **********************/

#define FDCAN_TTCFG_REFMSGIE_Pos                           ( 17U )
#define FDCAN_TTCFG_REFMSGIE_Msk                           ( 0x1UL << FDCAN_TTCFG_REFMSGIE_Pos )
#define FDCAN_TTCFG_REFMSGIE                               ( FDCAN_TTCFG_REFMSGIE_Msk )

#define FDCAN_TTCFG_REFMSGIF_Pos                           ( 16U )
#define FDCAN_TTCFG_REFMSGIF_Msk                           ( 0x1UL << FDCAN_TTCFG_REFMSGIF_Pos )
#define FDCAN_TTCFG_REFMSGIF                               ( FDCAN_TTCFG_REFMSGIF_Msk )

#define FDCAN_TTCFG_WTIE_Pos                               ( 15U )
#define FDCAN_TTCFG_WTIE_Msk                               ( 0x1UL << FDCAN_TTCFG_WTIE_Pos )
#define FDCAN_TTCFG_WTIE                                   ( FDCAN_TTCFG_WTIE_Msk )

#define FDCAN_TTCFG_WTIF_Pos                               ( 14U )
#define FDCAN_TTCFG_WTIF_Msk                               ( 0x1UL << FDCAN_TTCFG_WTIF_Pos )
#define FDCAN_TTCFG_WTIF                                   ( FDCAN_TTCFG_WTIF_Msk )

#define FDCAN_TTCFG_TEIF_Pos                               ( 13U )
#define FDCAN_TTCFG_TEIF_Msk                               ( 0x1UL << FDCAN_TTCFG_TEIF_Pos )
#define FDCAN_TTCFG_TEIF                                   ( FDCAN_TTCFG_TEIF_Msk )

#define FDCAN_TTCFG_TTIE_Pos                               ( 12U )
#define FDCAN_TTCFG_TTIE_Msk                               ( 0x1UL << FDCAN_TTCFG_TTIE_Pos )
#define FDCAN_TTCFG_TTIE                                   ( FDCAN_TTCFG_TTIE_Msk )

#define FDCAN_TTCFG_TTIF_Pos                               ( 11U )
#define FDCAN_TTCFG_TTIF_Msk                               ( 0x1UL << FDCAN_TTCFG_TTIF_Pos )
#define FDCAN_TTCFG_TTIF                                   ( FDCAN_TTCFG_TTIF_Msk )

#define FDCAN_TTCFG_T_PRESC_Pos                            ( 9U )
#define FDCAN_TTCFG_T_PRESC_Msk                            ( 0x3UL << FDCAN_TTCFG_T_PRESC_Pos )
#define FDCAN_TTCFG_T_PRESC                                ( FDCAN_TTCFG_T_PRESC_Msk )
#define FDCAN_TTCFG_T_PRESC_0                              ( 0x1UL << FDCAN_TTCFG_T_PRESC_Pos )
#define FDCAN_TTCFG_T_PRESC_1                              ( 0x2UL << FDCAN_TTCFG_T_PRESC_Pos )

#define FDCAN_TTCFG_TTEN_Pos                               ( 8U )
#define FDCAN_TTCFG_TTEN_Msk                               ( 0x1UL << FDCAN_TTCFG_TTEN_Pos )
#define FDCAN_TTCFG_TTEN                                   ( FDCAN_TTCFG_TTEN_Msk )

#define FDCAN_TTCFG_TBE_Pos                                ( 7U )
#define FDCAN_TTCFG_TBE_Msk                                ( 0x1UL << FDCAN_TTCFG_TBE_Pos )
#define FDCAN_TTCFG_TBE                                    ( FDCAN_TTCFG_TBE_Msk )

#define FDCAN_TTCFG_TBF_Pos                                ( 6U )
#define FDCAN_TTCFG_TBF_Msk                                ( 0x1UL << FDCAN_TTCFG_TBF_Pos )
#define FDCAN_TTCFG_TBF                                    ( FDCAN_TTCFG_TBF_Msk )

#define FDCAN_TTCFG_TBPTR_Pos                              ( 0U )
#define FDCAN_TTCFG_TBPTR_Msk                              ( 0x3fUL << FDCAN_TTCFG_TBPTR_Pos )
#define FDCAN_TTCFG_TBPTR                                  ( FDCAN_TTCFG_TBPTR_Msk )
#define FDCAN_TTCFG_TBPTR_0                                ( 0x1UL << FDCAN_TTCFG_TBPTR_Pos )
#define FDCAN_TTCFG_TBPTR_1                                ( 0x2UL << FDCAN_TTCFG_TBPTR_Pos )
#define FDCAN_TTCFG_TBPTR_2                                ( 0x4UL << FDCAN_TTCFG_TBPTR_Pos )
#define FDCAN_TTCFG_TBPTR_3                                ( 0x8UL << FDCAN_TTCFG_TBPTR_Pos )
#define FDCAN_TTCFG_TBPTR_4                                ( 0x10UL << FDCAN_TTCFG_TBPTR_Pos )
#define FDCAN_TTCFG_TBPTR_5                                ( 0x20UL << FDCAN_TTCFG_TBPTR_Pos )


/***************  Bits definition for FDCAN_REFMSG  **********************/

#define FDCAN_REFMSG_REF_IDE_Pos                           ( 31U )
#define FDCAN_REFMSG_REF_IDE_Msk                           ( 0x1UL << FDCAN_REFMSG_REF_IDE_Pos )
#define FDCAN_REFMSG_REF_IDE                               ( FDCAN_REFMSG_REF_IDE_Msk )

#define FDCAN_REFMSG_REF_ID_Pos                            ( 0U )
#define FDCAN_REFMSG_REF_ID_Msk                            ( 0x1fffffffUL << FDCAN_REFMSG_REF_ID_Pos )
#define FDCAN_REFMSG_REF_ID                                ( FDCAN_REFMSG_REF_ID_Msk )


/***************  Bits definition for FDCAN_TTTRIGR  **********************/

#define FDCAN_TTTRIGR_TT_TRIG_Pos                          ( 16U )
#define FDCAN_TTTRIGR_TT_TRIG_Msk                          ( 0xffffUL << FDCAN_TTTRIGR_TT_TRIG_Pos )
#define FDCAN_TTTRIGR_TT_TRIG                              ( FDCAN_TTTRIGR_TT_TRIG_Msk )

#define FDCAN_TTTRIGR_TEW_Pos                              ( 12U )
#define FDCAN_TTTRIGR_TEW_Msk                              ( 0xfUL << FDCAN_TTTRIGR_TEW_Pos )
#define FDCAN_TTTRIGR_TEW                                  ( FDCAN_TTTRIGR_TEW_Msk )
#define FDCAN_TTTRIGR_TEW_0                                ( 0x1UL << FDCAN_TTTRIGR_TEW_Pos )
#define FDCAN_TTTRIGR_TEW_1                                ( 0x2UL << FDCAN_TTTRIGR_TEW_Pos )
#define FDCAN_TTTRIGR_TEW_2                                ( 0x4UL << FDCAN_TTTRIGR_TEW_Pos )
#define FDCAN_TTTRIGR_TEW_3                                ( 0x8UL << FDCAN_TTTRIGR_TEW_Pos )

#define FDCAN_TTTRIGR_TTYPE_Pos                            ( 8U )
#define FDCAN_TTTRIGR_TTYPE_Msk                            ( 0x7UL << FDCAN_TTTRIGR_TTYPE_Pos )
#define FDCAN_TTTRIGR_TTYPE                                ( FDCAN_TTTRIGR_TTYPE_Msk )
#define FDCAN_TTTRIGR_TTYPE_0                              ( 0x1UL << FDCAN_TTTRIGR_TTYPE_Pos )
#define FDCAN_TTTRIGR_TTYPE_1                              ( 0x2UL << FDCAN_TTTRIGR_TTYPE_Pos )
#define FDCAN_TTTRIGR_TTYPE_2                              ( 0x4UL << FDCAN_TTTRIGR_TTYPE_Pos )

#define FDCAN_TTTRIGR_TTPTR_Pos                            ( 0U )
#define FDCAN_TTTRIGR_TTPTR_Msk                            ( 0x3fUL << FDCAN_TTTRIGR_TTPTR_Pos )
#define FDCAN_TTTRIGR_TTPTR                                ( FDCAN_TTTRIGR_TTPTR_Msk )
#define FDCAN_TTTRIGR_TTPTR_0                              ( 0x1UL << FDCAN_TTTRIGR_TTPTR_Pos )
#define FDCAN_TTTRIGR_TTPTR_1                              ( 0x2UL << FDCAN_TTTRIGR_TTPTR_Pos )
#define FDCAN_TTTRIGR_TTPTR_2                              ( 0x4UL << FDCAN_TTTRIGR_TTPTR_Pos )
#define FDCAN_TTTRIGR_TTPTR_3                              ( 0x8UL << FDCAN_TTTRIGR_TTPTR_Pos )
#define FDCAN_TTTRIGR_TTPTR_4                              ( 0x10UL << FDCAN_TTTRIGR_TTPTR_Pos )
#define FDCAN_TTTRIGR_TTPTR_5                              ( 0x20UL << FDCAN_TTTRIGR_TTPTR_Pos )


/***************  Bits definition for FDCAN_WTRIGR  **********************/

#define FDCAN_WTRIGR_TT_WTRIG_Pos                          ( 0U )
#define FDCAN_WTRIGR_TT_WTRIG_Msk                          ( 0xffffUL << FDCAN_WTRIGR_TT_WTRIG_Pos )
#define FDCAN_WTRIGR_TT_WTRIG                              ( FDCAN_WTRIGR_TT_WTRIG_Msk )


/***************  Bits definition for LPUART_RXDR  **********************/

#define LPUART_RXDR_RXDATA_Pos                              ( 0U )
#define LPUART_RXDR_RXDATA_Msk                              ( 0xffUL << LPUART_RXDR_RXDATA_Pos )
#define LPUART_RXDR_RXDATA                                  ( LPUART_RXDR_RXDATA_Msk )
#define LPUART_RXDR_RXDATA_0                                ( 0x1UL << LPUART_RXDR_RXDATA_Pos )
#define LPUART_RXDR_RXDATA_1                                ( 0x2UL << LPUART_RXDR_RXDATA_Pos )
#define LPUART_RXDR_RXDATA_2                                ( 0x4UL << LPUART_RXDR_RXDATA_Pos )
#define LPUART_RXDR_RXDATA_3                                ( 0x8UL << LPUART_RXDR_RXDATA_Pos )
#define LPUART_RXDR_RXDATA_4                                ( 0x10UL << LPUART_RXDR_RXDATA_Pos )
#define LPUART_RXDR_RXDATA_5                                ( 0x20UL << LPUART_RXDR_RXDATA_Pos )
#define LPUART_RXDR_RXDATA_6                                ( 0x40UL << LPUART_RXDR_RXDATA_Pos )
#define LPUART_RXDR_RXDATA_7                                ( 0x80UL << LPUART_RXDR_RXDATA_Pos )


/***************  Bits definition for LPUART_TXDR  **********************/

#define LPUART_TXDR_TXDATA_Pos                              ( 0U )
#define LPUART_TXDR_TXDATA_Msk                              ( 0xffUL << LPUART_TXDR_TXDATA_Pos )
#define LPUART_TXDR_TXDATA                                  ( LPUART_TXDR_TXDATA_Msk )
#define LPUART_TXDR_TXDATA_0                                ( 0x1UL << LPUART_TXDR_TXDATA_Pos )
#define LPUART_TXDR_TXDATA_1                                ( 0x2UL << LPUART_TXDR_TXDATA_Pos )
#define LPUART_TXDR_TXDATA_2                                ( 0x4UL << LPUART_TXDR_TXDATA_Pos )
#define LPUART_TXDR_TXDATA_3                                ( 0x8UL << LPUART_TXDR_TXDATA_Pos )
#define LPUART_TXDR_TXDATA_4                                ( 0x10UL << LPUART_TXDR_TXDATA_Pos )
#define LPUART_TXDR_TXDATA_5                                ( 0x20UL << LPUART_TXDR_TXDATA_Pos )
#define LPUART_TXDR_TXDATA_6                                ( 0x40UL << LPUART_TXDR_TXDATA_Pos )
#define LPUART_TXDR_TXDATA_7                                ( 0x80UL << LPUART_TXDR_TXDATA_Pos )


/***************  Bits definition for LPUART_LCR  **********************/

#define LPUART_LCR_BCNT_VALUE_Pos                           ( 16U )
#define LPUART_LCR_BCNT_VALUE_Msk                           ( 0xffffUL << LPUART_LCR_BCNT_VALUE_Pos )
#define LPUART_LCR_BCNT_VALUE                               ( LPUART_LCR_BCNT_VALUE_Msk )

#define LPUART_LCR_AUTO_START_EN_Pos                        ( 15U )
#define LPUART_LCR_AUTO_START_EN_Msk                        ( 0x1UL << LPUART_LCR_AUTO_START_EN_Pos )
#define LPUART_LCR_AUTO_START_EN                            ( LPUART_LCR_AUTO_START_EN_Msk )

#define LPUART_LCR_TXPOL_Pos                                ( 9U )
#define LPUART_LCR_TXPOL_Msk                                ( 0x1UL << LPUART_LCR_TXPOL_Pos )
#define LPUART_LCR_TXPOL                                    ( LPUART_LCR_TXPOL_Msk )

#define LPUART_LCR_RXPOL_Pos                                ( 8U )
#define LPUART_LCR_RXPOL_Msk                                ( 0x1UL << LPUART_LCR_RXPOL_Pos )
#define LPUART_LCR_RXPOL                                    ( LPUART_LCR_RXPOL_Msk )

#define LPUART_LCR_WKCK_Pos                                 ( 7U )
#define LPUART_LCR_WKCK_Msk                                 ( 0x1UL << LPUART_LCR_WKCK_Pos )
#define LPUART_LCR_WKCK                                     ( LPUART_LCR_WKCK_Msk )

#define LPUART_LCR_RXWKS_Pos                                ( 5U )
#define LPUART_LCR_RXWKS_Msk                                ( 0x3UL << LPUART_LCR_RXWKS_Pos )
#define LPUART_LCR_RXWKS                                    ( LPUART_LCR_RXWKS_Msk )
#define LPUART_LCR_RXWKS_0                                  ( 0x1UL << LPUART_LCR_RXWKS_Pos )
#define LPUART_LCR_RXWKS_1                                  ( 0x2UL << LPUART_LCR_RXWKS_Pos )

#define LPUART_LCR_WLEN_Pos                                 ( 4U )
#define LPUART_LCR_WLEN_Msk                                 ( 0x1UL << LPUART_LCR_WLEN_Pos )
#define LPUART_LCR_WLEN                                     ( LPUART_LCR_WLEN_Msk )

#define LPUART_LCR_STP2_Pos                                 ( 3U )
#define LPUART_LCR_STP2_Msk                                 ( 0x1UL << LPUART_LCR_STP2_Pos )
#define LPUART_LCR_STP2                                     ( LPUART_LCR_STP2_Msk )

#define LPUART_LCR_EPS_Pos                                  ( 2U )
#define LPUART_LCR_EPS_Msk                                  ( 0x1UL << LPUART_LCR_EPS_Pos )
#define LPUART_LCR_EPS                                      ( LPUART_LCR_EPS_Msk )

#define LPUART_LCR_SPS_Pos                                  ( 1U )
#define LPUART_LCR_SPS_Msk                                  ( 0x1UL << LPUART_LCR_SPS_Pos )
#define LPUART_LCR_SPS                                      ( LPUART_LCR_SPS_Msk )

#define LPUART_LCR_PEN_Pos                                  ( 0U )
#define LPUART_LCR_PEN_Msk                                  ( 0x1UL << LPUART_LCR_PEN_Pos )
#define LPUART_LCR_PEN                                      ( LPUART_LCR_PEN_Msk )


/***************  Bits definition for LPUART_CR  **********************/

#define LPUART_CR_DMA_EN_Pos                                ( 2U )
#define LPUART_CR_DMA_EN_Msk                                ( 0x1UL << LPUART_CR_DMA_EN_Pos )
#define LPUART_CR_DMA_EN                                    ( LPUART_CR_DMA_EN_Msk )

#define LPUART_CR_TX_EN_Pos                                 ( 1U )
#define LPUART_CR_TX_EN_Msk                                 ( 0x1UL << LPUART_CR_TX_EN_Pos )
#define LPUART_CR_TX_EN                                     ( LPUART_CR_TX_EN_Msk )

#define LPUART_CR_RX_EN_Pos                                 ( 0U )
#define LPUART_CR_RX_EN_Msk                                 ( 0x1UL << LPUART_CR_RX_EN_Pos )
#define LPUART_CR_RX_EN                                     ( LPUART_CR_RX_EN_Msk )


/***************  Bits definition for LPUART_IBAUD  **********************/

#define LPUART_IBAUD_RXSAM_Pos                              ( 8U )
#define LPUART_IBAUD_RXSAM_Msk                              ( 0xffUL << LPUART_IBAUD_RXSAM_Pos )
#define LPUART_IBAUD_RXSAM                                  ( LPUART_IBAUD_RXSAM_Msk )
#define LPUART_IBAUD_RXSAM_0                                ( 0x1UL << LPUART_IBAUD_RXSAM_Pos )
#define LPUART_IBAUD_RXSAM_1                                ( 0x2UL << LPUART_IBAUD_RXSAM_Pos )
#define LPUART_IBAUD_RXSAM_2                                ( 0x4UL << LPUART_IBAUD_RXSAM_Pos )
#define LPUART_IBAUD_RXSAM_3                                ( 0x8UL << LPUART_IBAUD_RXSAM_Pos )
#define LPUART_IBAUD_RXSAM_4                                ( 0x10UL << LPUART_IBAUD_RXSAM_Pos )
#define LPUART_IBAUD_RXSAM_5                                ( 0x20UL << LPUART_IBAUD_RXSAM_Pos )
#define LPUART_IBAUD_RXSAM_6                                ( 0x40UL << LPUART_IBAUD_RXSAM_Pos )
#define LPUART_IBAUD_RXSAM_7                                ( 0x80UL << LPUART_IBAUD_RXSAM_Pos )

#define LPUART_IBAUD_IBAUD_Pos                              ( 0U )
#define LPUART_IBAUD_IBAUD_Msk                              ( 0xffUL << LPUART_IBAUD_IBAUD_Pos )
#define LPUART_IBAUD_IBAUD                                  ( LPUART_IBAUD_IBAUD_Msk )
#define LPUART_IBAUD_IBAUD_0                                ( 0x1UL << LPUART_IBAUD_IBAUD_Pos )
#define LPUART_IBAUD_IBAUD_1                                ( 0x2UL << LPUART_IBAUD_IBAUD_Pos )
#define LPUART_IBAUD_IBAUD_2                                ( 0x4UL << LPUART_IBAUD_IBAUD_Pos )
#define LPUART_IBAUD_IBAUD_3                                ( 0x8UL << LPUART_IBAUD_IBAUD_Pos )
#define LPUART_IBAUD_IBAUD_4                                ( 0x10UL << LPUART_IBAUD_IBAUD_Pos )
#define LPUART_IBAUD_IBAUD_5                                ( 0x20UL << LPUART_IBAUD_IBAUD_Pos )
#define LPUART_IBAUD_IBAUD_6                                ( 0x40UL << LPUART_IBAUD_IBAUD_Pos )
#define LPUART_IBAUD_IBAUD_7                                ( 0x80UL << LPUART_IBAUD_IBAUD_Pos )


/***************  Bits definition for LPUART_FBAUD  **********************/

#define LPUART_FBAUD_FBAUD_Pos                              ( 0U )
#define LPUART_FBAUD_FBAUD_Msk                              ( 0xfffUL << LPUART_FBAUD_FBAUD_Pos )
#define LPUART_FBAUD_FBAUD                                  ( LPUART_FBAUD_FBAUD_Msk )


/***************  Bits definition for LPUART_IE  **********************/

#define LPUART_IE_IDLEIE_Pos                                ( 17U )
#define LPUART_IE_IDLEIE_Msk                                ( 0x1UL << LPUART_IE_IDLEIE_Pos )
#define LPUART_IE_IDLEIE                                    ( LPUART_IE_IDLEIE_Msk )

#define LPUART_IE_BCNTIE_Pos                                ( 16U )
#define LPUART_IE_BCNTIE_Msk                                ( 0x1UL << LPUART_IE_BCNTIE_Pos )
#define LPUART_IE_BCNTIE                                    ( LPUART_IE_BCNTIE_Msk )

#define LPUART_IE_STARTIE_Pos                               ( 9U )
#define LPUART_IE_STARTIE_Msk                               ( 0x1UL << LPUART_IE_STARTIE_Pos )
#define LPUART_IE_STARTIE                                   ( LPUART_IE_STARTIE_Msk )

#define LPUART_IE_MATCHIE_Pos                               ( 8U )
#define LPUART_IE_MATCHIE_Msk                               ( 0x1UL << LPUART_IE_MATCHIE_Pos )
#define LPUART_IE_MATCHIE                                   ( LPUART_IE_MATCHIE_Msk )

#define LPUART_IE_RXOVIE_Pos                                ( 5U )
#define LPUART_IE_RXOVIE_Msk                                ( 0x1UL << LPUART_IE_RXOVIE_Pos )
#define LPUART_IE_RXOVIE                                    ( LPUART_IE_RXOVIE_Msk )

#define LPUART_IE_FEIE_Pos                                  ( 4U )
#define LPUART_IE_FEIE_Msk                                  ( 0x1UL << LPUART_IE_FEIE_Pos )
#define LPUART_IE_FEIE                                      ( LPUART_IE_FEIE_Msk )

#define LPUART_IE_PEIE_Pos                                  ( 3U )
#define LPUART_IE_PEIE_Msk                                  ( 0x1UL << LPUART_IE_PEIE_Pos )
#define LPUART_IE_PEIE                                      ( LPUART_IE_PEIE_Msk )

#define LPUART_IE_TXEIE_Pos                                 ( 2U )
#define LPUART_IE_TXEIE_Msk                                 ( 0x1UL << LPUART_IE_TXEIE_Pos )
#define LPUART_IE_TXEIE                                     ( LPUART_IE_TXEIE_Msk )

#define LPUART_IE_TCIE_Pos                                  ( 1U )
#define LPUART_IE_TCIE_Msk                                  ( 0x1UL << LPUART_IE_TCIE_Pos )
#define LPUART_IE_TCIE                                      ( LPUART_IE_TCIE_Msk )

#define LPUART_IE_RXIE_Pos                                  ( 0U )
#define LPUART_IE_RXIE_Msk                                  ( 0x1UL << LPUART_IE_RXIE_Pos )
#define LPUART_IE_RXIE                                      ( LPUART_IE_RXIE_Msk )


/***************  Bits definition for LPUART_SR  **********************/

#define LPUART_SR_IDLEIF_Pos                                ( 17U )
#define LPUART_SR_IDLEIF_Msk                                ( 0x1UL << LPUART_SR_IDLEIF_Pos )
#define LPUART_SR_IDLEIF                                    ( LPUART_SR_IDLEIF_Msk )

#define LPUART_SR_BCNTIF_Pos                                ( 16U )
#define LPUART_SR_BCNTIF_Msk                                ( 0x1UL << LPUART_SR_BCNTIF_Pos )
#define LPUART_SR_BCNTIF                                    ( LPUART_SR_BCNTIF_Msk )

#define LPUART_SR_TXE_Pos                                   ( 10U )
#define LPUART_SR_TXE_Msk                                   ( 0x1UL << LPUART_SR_TXE_Pos )
#define LPUART_SR_TXE                                       ( LPUART_SR_TXE_Msk )

#define LPUART_SR_STARTIF_Pos                               ( 9U )
#define LPUART_SR_STARTIF_Msk                               ( 0x1UL << LPUART_SR_STARTIF_Pos )
#define LPUART_SR_STARTIF                                   ( LPUART_SR_STARTIF_Msk )

#define LPUART_SR_MATCHIF_Pos                               ( 8U )
#define LPUART_SR_MATCHIF_Msk                               ( 0x1UL << LPUART_SR_MATCHIF_Pos )
#define LPUART_SR_MATCHIF                                   ( LPUART_SR_MATCHIF_Msk )

#define LPUART_SR_TXOVF_Pos                                 ( 7U )
#define LPUART_SR_TXOVF_Msk                                 ( 0x1UL << LPUART_SR_TXOVF_Pos )
#define LPUART_SR_TXOVF                                     ( LPUART_SR_TXOVF_Msk )

#define LPUART_SR_RXF_Pos                                   ( 6U )
#define LPUART_SR_RXF_Msk                                   ( 0x1UL << LPUART_SR_RXF_Pos )
#define LPUART_SR_RXF                                       ( LPUART_SR_RXF_Msk )

#define LPUART_SR_RXOVIF_Pos                                ( 5U )
#define LPUART_SR_RXOVIF_Msk                                ( 0x1UL << LPUART_SR_RXOVIF_Pos )
#define LPUART_SR_RXOVIF                                    ( LPUART_SR_RXOVIF_Msk )

#define LPUART_SR_FEIF_Pos                                  ( 4U )
#define LPUART_SR_FEIF_Msk                                  ( 0x1UL << LPUART_SR_FEIF_Pos )
#define LPUART_SR_FEIF                                      ( LPUART_SR_FEIF_Msk )

#define LPUART_SR_PEIF_Pos                                  ( 3U )
#define LPUART_SR_PEIF_Msk                                  ( 0x1UL << LPUART_SR_PEIF_Pos )
#define LPUART_SR_PEIF                                      ( LPUART_SR_PEIF_Msk )

#define LPUART_SR_TXEIF_Pos                                 ( 2U )
#define LPUART_SR_TXEIF_Msk                                 ( 0x1UL << LPUART_SR_TXEIF_Pos )
#define LPUART_SR_TXEIF                                     ( LPUART_SR_TXEIF_Msk )

#define LPUART_SR_TCIF_Pos                                  ( 1U )
#define LPUART_SR_TCIF_Msk                                  ( 0x1UL << LPUART_SR_TCIF_Pos )
#define LPUART_SR_TCIF                                      ( LPUART_SR_TCIF_Msk )

#define LPUART_SR_RXIF_Pos                                  ( 0U )
#define LPUART_SR_RXIF_Msk                                  ( 0x1UL << LPUART_SR_RXIF_Pos )
#define LPUART_SR_RXIF                                      ( LPUART_SR_RXIF_Msk )


/***************  Bits definition for LPUART_ADDR  **********************/

#define LPUART_ADDR_ADDR_Pos                                ( 0U )
#define LPUART_ADDR_ADDR_Msk                                ( 0xffUL << LPUART_ADDR_ADDR_Pos )
#define LPUART_ADDR_ADDR                                    ( LPUART_ADDR_ADDR_Msk )
#define LPUART_ADDR_ADDR_0                                  ( 0x1UL << LPUART_ADDR_ADDR_Pos )
#define LPUART_ADDR_ADDR_1                                  ( 0x2UL << LPUART_ADDR_ADDR_Pos )
#define LPUART_ADDR_ADDR_2                                  ( 0x4UL << LPUART_ADDR_ADDR_Pos )
#define LPUART_ADDR_ADDR_3                                  ( 0x8UL << LPUART_ADDR_ADDR_Pos )
#define LPUART_ADDR_ADDR_4                                  ( 0x10UL << LPUART_ADDR_ADDR_Pos )
#define LPUART_ADDR_ADDR_5                                  ( 0x20UL << LPUART_ADDR_ADDR_Pos )
#define LPUART_ADDR_ADDR_6                                  ( 0x40UL << LPUART_ADDR_ADDR_Pos )
#define LPUART_ADDR_ADDR_7                                  ( 0x80UL << LPUART_ADDR_ADDR_Pos )


/***************  Bits definition for I2S_TXDR  **********************/

#define I2S_TXDR_TXDR_Pos                                   ( 0 )
#define I2S_TXDR_TXDR_Msk                                   ( 0xFFFFFFFFUL << I2S_TXDR_TXDR_Pos )
#define I2S_TXDR_TXDR                                       ( I2S_TXDR_TXDR_Msk )

/***************  Bits definition for I2S_RXDR  **********************/

#define I2S_RXDR_RXDR_Pos                                   ( 0U )
#define I2S_RXDR_RXDR_Msk                                   ( 0xFFFFFFFFUL << I2S_RXDR_RXDR_Pos )
#define I2S_RXDR_RXDR                                       ( I2S_RXDR_RXDR_Msk )

/***************  Bits definition for I2S_CR  **********************/

#define I2S_CR_TXDMAEN_Pos                                  ( 16U )
#define I2S_CR_TXDMAEN_Msk                                  ( 0x1UL << I2S_CR_TXDMAEN_Pos )
#define I2S_CR_TXDMAEN                                      ( I2S_CR_TXDMAEN_Msk )

#define I2S_CR_RXDMAEN_Pos                                  ( 15U )
#define I2S_CR_RXDMAEN_Msk                                  ( 0x1UL << I2S_CR_RXDMAEN_Pos )
#define I2S_CR_RXDMAEN                                      ( I2S_CR_RXDMAEN_Msk )

#define I2S_CR_STOP_Pos                                     ( 14U )
#define I2S_CR_STOP_Msk                                     ( 0x1UL << I2S_CR_STOP_Pos )
#define I2S_CR_STOP                                         ( I2S_CR_STOP_Msk )

#define I2S_CR_START_Pos                                    ( 13U )
#define I2S_CR_START_Msk                                    ( 0x1UL << I2S_CR_START_Pos )
#define I2S_CR_START                                        ( I2S_CR_START_Msk )

#define I2S_CR_IOSWP_Pos                                    ( 12U )
#define I2S_CR_IOSWP_Msk                                    ( 0x1UL << I2S_CR_IOSWP_Pos )
#define I2S_CR_IOSWP                                        ( I2S_CR_IOSWP_Msk )

#define I2S_CR_EN_Pos                                       ( 11U )
#define I2S_CR_EN_Msk                                       ( 0x1UL << I2S_CR_EN_Pos )
#define I2S_CR_EN                                           ( I2S_CR_EN_Msk )

#define I2S_CR_REN_Pos                                      ( 10U )
#define I2S_CR_REN_Msk                                      ( 0x1UL << I2S_CR_REN_Pos )
#define I2S_CR_REN                                          ( I2S_CR_REN_Msk )

#define I2S_CR_TEN_Pos                                      ( 9U )
#define I2S_CR_TEN_Msk                                      ( 0x1UL << I2S_CR_TEN_Pos )
#define I2S_CR_TEN                                          ( I2S_CR_TEN_Msk )

#define I2S_CR_MODE_Pos                                     ( 8U )
#define I2S_CR_MODE_Msk                                     ( 0x1UL << I2S_CR_MODE_Pos )
#define I2S_CR_MODE                                         ( I2S_CR_MODE_Msk )

#define I2S_CR_PCMMODE_Pos                                  ( 7U )
#define I2S_CR_PCMMODE_Msk                                  ( 0x1UL << I2S_CR_PCMMODE_Pos )
#define I2S_CR_PCMMODE                                      ( I2S_CR_PCMMODE_Msk )

#define I2S_CR_STD_Pos                                      ( 4U )
#define I2S_CR_STD_Msk                                      ( 0x3UL << I2S_CR_STD_Pos )
#define I2S_CR_STD                                          ( I2S_CR_STD_Msk )
#define I2S_CR_STD_0                                        ( 0x1UL << I2S_CR_STD_Pos )
#define I2S_CR_STD_1                                        ( 0x2UL << I2S_CR_STD_Pos )

#define I2S_CR_CKPL_Pos                                     ( 3U )
#define I2S_CR_CKPL_Msk                                     ( 0x1UL << I2S_CR_CKPL_Pos )
#define I2S_CR_CKPL                                         ( I2S_CR_CKPL_Msk )

#define I2S_CR_DLEN_Pos                                     ( 1U )
#define I2S_CR_DLEN_Msk                                     ( 0x3UL << I2S_CR_DLEN_Pos )
#define I2S_CR_DLEN                                         ( I2S_CR_DLEN_Msk )
#define I2S_CR_DLEN_0                                       ( 0x1UL << I2S_CR_DLEN_Pos )
#define I2S_CR_DLEN_1                                       ( 0x2UL << I2S_CR_DLEN_Pos )

#define I2S_CR_CHLEN_Pos                                    ( 0U )
#define I2S_CR_CHLEN_Msk                                    ( 0x1UL << I2S_CR_CHLEN_Pos )
#define I2S_CR_CHLEN                                        ( I2S_CR_CHLEN_Msk )


/***************  Bits definition for I2S_PR  **********************/

#define I2S_PR_MCKOE_Pos                                    ( 10U )
#define I2S_PR_MCKOE_Msk                                    ( 0x1UL << I2S_PR_MCKOE_Pos )
#define I2S_PR_MCKOE                                        ( I2S_PR_MCKOE_Msk )

#define I2S_PR_OF_Pos                                       ( 9U )
#define I2S_PR_OF_Msk                                       ( 0x1UL << I2S_PR_OF_Pos )
#define I2S_PR_OF                                           ( I2S_PR_OF_Msk )

#define I2S_PR_DIV_Pos                                      ( 0U )
#define I2S_PR_DIV_Msk                                      ( 0x1FFUL << I2S_PR_DIV_Pos )
#define I2S_PR_DIV                                          ( I2S_PR_DIV_Msk )


/***************  Bits definition for I2S_DIER  **********************/

#define I2S_DIER_SVTCIE_Pos                                 ( 10U )
#define I2S_DIER_SVTCIE_Msk                                 ( 0x1UL << I2S_DIER_SVTCIE_Pos )
#define I2S_DIER_SVTCIE                                     ( I2S_DIER_SVTCIE_Msk )

#define I2S_DIER_MSUSPIE_Pos                                ( 9U )
#define I2S_DIER_MSUSPIE_Msk                                ( 0x1UL << I2S_DIER_MSUSPIE_Pos )
#define I2S_DIER_MSUSPIE                                    ( I2S_DIER_MSUSPIE_Msk )

#define I2S_DIER_ERRIE_Pos                                  ( 5U )
#define I2S_DIER_ERRIE_Msk                                  ( 0x1UL << I2S_DIER_ERRIE_Pos )
#define I2S_DIER_ERRIE                                      ( I2S_DIER_ERRIE_Msk )

#define I2S_DIER_TXEIE_Pos                                  ( 1U )
#define I2S_DIER_TXEIE_Msk                                  ( 0x1UL << I2S_DIER_TXEIE_Pos )
#define I2S_DIER_TXEIE                                      ( I2S_DIER_TXEIE_Msk )

#define I2S_DIER_RXNEIE_Pos                                 ( 0U )
#define I2S_DIER_RXNEIE_Msk                                 ( 0x1UL << I2S_DIER_RXNEIE_Pos )
#define I2S_DIER_RXNEIE                                     ( I2S_DIER_RXNEIE_Msk )


/***************  Bits definition for I2S_SR  **********************/

#define I2S_SR_SVTC_Pos                                     ( 10U )
#define I2S_SR_SVTC_Msk                                     ( 0x1UL << I2S_SR_SVTC_Pos )
#define I2S_SR_SVTC                                         ( I2S_SR_SVTC_Msk )

#define I2S_SR_MSUSP_Pos                                    ( 9U )
#define I2S_SR_MSUSP_Msk                                    ( 0x1UL << I2S_SR_MSUSP_Pos )
#define I2S_SR_MSUSP                                        ( I2S_SR_MSUSP_Msk )

#define I2S_SR_FE_Pos                                       ( 5U )
#define I2S_SR_FE_Msk                                       ( 0x1UL << I2S_SR_FE_Pos )
#define I2S_SR_FE                                           ( I2S_SR_FE_Msk )

#define I2S_SR_OVR_Pos                                      ( 4U )
#define I2S_SR_OVR_Msk                                      ( 0x1UL << I2S_SR_OVR_Pos )
#define I2S_SR_OVR                                          ( I2S_SR_OVR_Msk )

#define I2S_SR_UDR_Pos                                      ( 3U )
#define I2S_SR_UDR_Msk                                      ( 0x1UL << I2S_SR_UDR_Pos )
#define I2S_SR_UDR                                          ( I2S_SR_UDR_Msk )

#define I2S_SR_CH_Pos                                       ( 2U )
#define I2S_SR_CH_Msk                                       ( 0x1UL << I2S_SR_CH_Pos )
#define I2S_SR_CH                                           ( I2S_SR_CH_Msk )

#define I2S_SR_TXE_Pos                                      ( 1U )
#define I2S_SR_TXE_Msk                                      ( 0x1UL << I2S_SR_TXE_Pos )
#define I2S_SR_TXE                                          ( I2S_SR_TXE_Msk )

#define I2S_SR_RXNE_Pos                                     ( 0U )
#define I2S_SR_RXNE_Msk                                     ( 0x1UL << I2S_SR_RXNE_Pos )
#define I2S_SR_RXNE                                         ( I2S_SR_RXNE_Msk )


/***************  Bits definition for I2S_RSIZE  **********************/

#define I2S_RSIZE_RSIZE_Pos                                 ( 0U )
#define I2S_RSIZE_RSIZE_Msk                                 ( 0xFFFFUL << I2S_RSIZE_RSIZE_Pos )
#define I2S_RSIZE_RSIZE                                     ( I2S_RSIZE_RSIZE_Msk )


/***************  Bits definition for ETH_MACCR  **********************/

#define ETH_MACCR_SARC_Pos                                  ( 28U )
#define ETH_MACCR_SARC_Msk                                  ( 0x7UL << ETH_MACCR_SARC_Pos )
#define ETH_MACCR_SARC                                      ( ETH_MACCR_SARC_Msk )
#define ETH_MACCR_SARC_0                                    ( 0x1UL << ETH_MACCR_SARC_Pos )
#define ETH_MACCR_SARC_1                                    ( 0x2UL << ETH_MACCR_SARC_Pos )
#define ETH_MACCR_SARC_2                                    ( 0x4UL << ETH_MACCR_SARC_Pos )

#define ETH_MACCR_S2KP_Pos                                  ( 27U )
#define ETH_MACCR_S2KP_Msk                                  ( 0x1UL << ETH_MACCR_S2KP_Pos )
#define ETH_MACCR_S2KP                                      ( ETH_MACCR_S2KP_Msk )

#define ETH_MACCR_CSTF_Pos                                  ( 25U )
#define ETH_MACCR_CSTF_Msk                                  ( 0x1UL << ETH_MACCR_CSTF_Pos )
#define ETH_MACCR_CSTF                                      ( ETH_MACCR_CSTF_Msk )

#define ETH_MACCR_WD_Pos                                    ( 23U )
#define ETH_MACCR_WD_Msk                                    ( 0x1UL << ETH_MACCR_WD_Pos )
#define ETH_MACCR_WD                                        ( ETH_MACCR_WD_Msk )

#define ETH_MACCR_JD_Pos                                    ( 22U )
#define ETH_MACCR_JD_Msk                                    ( 0x1UL << ETH_MACCR_JD_Pos )
#define ETH_MACCR_JD                                        ( ETH_MACCR_JD_Msk )

#define ETH_MACCR_JE_Pos                                    ( 20U )
#define ETH_MACCR_JE_Msk                                    ( 0x1UL << ETH_MACCR_JE_Pos )
#define ETH_MACCR_JE                                        ( ETH_MACCR_JE_Msk )

#define ETH_MACCR_IFG_Pos                                   ( 17U )
#define ETH_MACCR_IFG_Msk                                   ( 0x7UL << ETH_MACCR_IFG_Pos )
#define ETH_MACCR_IFG                                       ( ETH_MACCR_IFG_Msk )
#define ETH_MACCR_IFG_0                                     ( 0x1UL << ETH_MACCR_IFG_Pos )
#define ETH_MACCR_IFG_1                                     ( 0x2UL << ETH_MACCR_IFG_Pos )
#define ETH_MACCR_IFG_2                                     ( 0x4UL << ETH_MACCR_IFG_Pos )

#define ETH_MACCR_CSD_Pos                                   ( 16U )
#define ETH_MACCR_CSD_Msk                                   ( 0x1UL << ETH_MACCR_CSD_Pos )
#define ETH_MACCR_CSD                                       ( ETH_MACCR_CSD_Msk )

#define ETH_MACCR_FES_Pos                                   ( 14U )
#define ETH_MACCR_FES_Msk                                   ( 0x1UL << ETH_MACCR_FES_Pos )
#define ETH_MACCR_FES                                       ( ETH_MACCR_FES_Msk )

#define ETH_MACCR_ROD_Pos                                   ( 13U )
#define ETH_MACCR_ROD_Msk                                   ( 0x1UL << ETH_MACCR_ROD_Pos )
#define ETH_MACCR_ROD                                       ( ETH_MACCR_ROD_Msk )

#define ETH_MACCR_LM_Pos                                    ( 12U )
#define ETH_MACCR_LM_Msk                                    ( 0x1UL << ETH_MACCR_LM_Pos )
#define ETH_MACCR_LM                                        ( ETH_MACCR_LM_Msk )

#define ETH_MACCR_DM_Pos                                    ( 11U )
#define ETH_MACCR_DM_Msk                                    ( 0x1UL << ETH_MACCR_DM_Pos )
#define ETH_MACCR_DM                                        ( ETH_MACCR_DM_Msk )

#define ETH_MACCR_IPCO_Pos                                  ( 10U )
#define ETH_MACCR_IPCO_Msk                                  ( 0x1UL << ETH_MACCR_IPCO_Pos )
#define ETH_MACCR_IPCO                                      ( ETH_MACCR_IPCO_Msk )

#define ETH_MACCR_DR_Pos                                    ( 9U )
#define ETH_MACCR_DR_Msk                                    ( 0x1UL << ETH_MACCR_DR_Pos )
#define ETH_MACCR_DR                                        ( ETH_MACCR_DR_Msk )

#define ETH_MACCR_APCS_Pos                                  ( 7U )
#define ETH_MACCR_APCS_Msk                                  ( 0x1UL << ETH_MACCR_APCS_Pos )
#define ETH_MACCR_APCS                                      ( ETH_MACCR_APCS_Msk )

#define ETH_MACCR_BL_Pos                                    ( 5U )
#define ETH_MACCR_BL_Msk                                    ( 0x3UL << ETH_MACCR_BL_Pos )
#define ETH_MACCR_BL                                        ( ETH_MACCR_BL_Msk )
#define ETH_MACCR_BL_0                                      ( 0x1UL << ETH_MACCR_BL_Pos )
#define ETH_MACCR_BL_1                                      ( 0x2UL << ETH_MACCR_BL_Pos )

#define ETH_MACCR_DC_Pos                                    ( 4U )
#define ETH_MACCR_DC_Msk                                    ( 0x1UL << ETH_MACCR_DC_Pos )
#define ETH_MACCR_DC                                        ( ETH_MACCR_DC_Msk )

#define ETH_MACCR_TE_Pos                                    ( 3U )
#define ETH_MACCR_TE_Msk                                    ( 0x1UL << ETH_MACCR_TE_Pos )
#define ETH_MACCR_TE                                        ( ETH_MACCR_TE_Msk )

#define ETH_MACCR_RE_Pos                                    ( 2U )
#define ETH_MACCR_RE_Msk                                    ( 0x1UL << ETH_MACCR_RE_Pos )
#define ETH_MACCR_RE                                        ( ETH_MACCR_RE_Msk )

#define ETH_MACCR_PRELEN_Pos                                ( 0U )
#define ETH_MACCR_PRELEN_Msk                                ( 0x3UL << ETH_MACCR_PRELEN_Pos )
#define ETH_MACCR_PRELEN                                    ( ETH_MACCR_PRELEN_Msk )
#define ETH_MACCR_PRELEN_0                                  ( 0x1UL << ETH_MACCR_PRELEN_Pos )
#define ETH_MACCR_PRELEN_1                                  ( 0x2UL << ETH_MACCR_PRELEN_Pos )


/***************  Bits definition for ETH_MACFFR  **********************/

#define ETH_MACFFR_RA_Pos                                   ( 31U )
#define ETH_MACFFR_RA_Msk                                   ( 0x1UL << ETH_MACFFR_RA_Pos )
#define ETH_MACFFR_RA                                       ( ETH_MACFFR_RA_Msk )

#define ETH_MACFFR_DNTU_Pos                                 ( 21U )
#define ETH_MACFFR_DNTU_Msk                                 ( 0x1UL << ETH_MACFFR_DNTU_Pos )
#define ETH_MACFFR_DNTU                                     ( ETH_MACFFR_DNTU_Msk )

#define ETH_MACFFR_IPFE_Pos                                 ( 20U )
#define ETH_MACFFR_IPFE_Msk                                 ( 0x1UL << ETH_MACFFR_IPFE_Pos )
#define ETH_MACFFR_IPFE                                     ( ETH_MACFFR_IPFE_Msk )

#define ETH_MACFFR_VTFE_Pos                                 ( 16U )
#define ETH_MACFFR_VTFE_Msk                                 ( 0x1UL << ETH_MACFFR_VTFE_Pos )
#define ETH_MACFFR_VTFE                                     ( ETH_MACFFR_VTFE_Msk )

#define ETH_MACFFR_HPF_Pos                                  ( 10U )
#define ETH_MACFFR_HPF_Msk                                  ( 0x1UL << ETH_MACFFR_HPF_Pos )
#define ETH_MACFFR_HPF                                      ( ETH_MACFFR_HPF_Msk )

#define ETH_MACFFR_SAF_Pos                                  ( 9U )
#define ETH_MACFFR_SAF_Msk                                  ( 0x1UL << ETH_MACFFR_SAF_Pos )
#define ETH_MACFFR_SAF                                      ( ETH_MACFFR_SAF_Msk )

#define ETH_MACFFR_SAIF_Pos                                 ( 8U )
#define ETH_MACFFR_SAIF_Msk                                 ( 0x1UL << ETH_MACFFR_SAIF_Pos )
#define ETH_MACFFR_SAIF                                     ( ETH_MACFFR_SAIF_Msk )

#define ETH_MACFFR_PCF_Pos                                  ( 6U )
#define ETH_MACFFR_PCF_Msk                                  ( 0x3UL << ETH_MACFFR_PCF_Pos )
#define ETH_MACFFR_PCF                                      ( ETH_MACFFR_PCF_Msk )
#define ETH_MACFFR_PCF_0                                    ( 0x1UL << ETH_MACFFR_PCF_Pos )
#define ETH_MACFFR_PCF_1                                    ( 0x2UL << ETH_MACFFR_PCF_Pos )

#define ETH_MACFFR_DBF_Pos                                  ( 5U )
#define ETH_MACFFR_DBF_Msk                                  ( 0x1UL << ETH_MACFFR_DBF_Pos )
#define ETH_MACFFR_DBF                                      ( ETH_MACFFR_DBF_Msk )

#define ETH_MACFFR_PAM_Pos                                  ( 4U )
#define ETH_MACFFR_PAM_Msk                                  ( 0x1UL << ETH_MACFFR_PAM_Pos )
#define ETH_MACFFR_PAM                                      ( ETH_MACFFR_PAM_Msk )

#define ETH_MACFFR_DAIF_Pos                                 ( 3U )
#define ETH_MACFFR_DAIF_Msk                                 ( 0x1UL << ETH_MACFFR_DAIF_Pos )
#define ETH_MACFFR_DAIF                                     ( ETH_MACFFR_DAIF_Msk )

#define ETH_MACFFR_HMC_Pos                                  ( 2U )
#define ETH_MACFFR_HMC_Msk                                  ( 0x1UL << ETH_MACFFR_HMC_Pos )
#define ETH_MACFFR_HMC                                      ( ETH_MACFFR_HMC_Msk )

#define ETH_MACFFR_HUC_Pos                                  ( 1U )
#define ETH_MACFFR_HUC_Msk                                  ( 0x1UL << ETH_MACFFR_HUC_Pos )
#define ETH_MACFFR_HUC                                      ( ETH_MACFFR_HUC_Msk )

#define ETH_MACFFR_PR_Pos                                   ( 0U )
#define ETH_MACFFR_PR_Msk                                   ( 0x1UL << ETH_MACFFR_PR_Pos )
#define ETH_MACFFR_PR                                       ( ETH_MACFFR_PR_Msk )


/***************  Bits definition for ETH_MACHTHR  **********************/

#define ETH_MACHTHR_HTH_Pos                                 ( 0U )
#define ETH_MACHTHR_HTH_Msk                                 ( 0xffffffffUL << ETH_MACHTHR_HTH_Pos )
#define ETH_MACHTHR_HTH                                     ( ETH_MACHTHR_HTH_Msk )


/***************  Bits definition for ETH_MACHTLR  **********************/

#define ETH_MACHTLR_HTL_Pos                                 ( 0U )
#define ETH_MACHTLR_HTL_Msk                                 ( 0xffffffffUL << ETH_MACHTLR_HTL_Pos )
#define ETH_MACHTLR_HTL                                     ( ETH_MACHTLR_HTL_Msk )


/***************  Bits definition for ETH_MACMIIAR  **********************/

#define ETH_MACMIIAR_PA_Pos                                 ( 11U )
#define ETH_MACMIIAR_PA_Msk                                 ( 0x1fUL << ETH_MACMIIAR_PA_Pos )
#define ETH_MACMIIAR_PA                                     ( ETH_MACMIIAR_PA_Msk )
#define ETH_MACMIIAR_PA_0                                   ( 0x1UL << ETH_MACMIIAR_PA_Pos )
#define ETH_MACMIIAR_PA_1                                   ( 0x2UL << ETH_MACMIIAR_PA_Pos )
#define ETH_MACMIIAR_PA_2                                   ( 0x4UL << ETH_MACMIIAR_PA_Pos )
#define ETH_MACMIIAR_PA_3                                   ( 0x8UL << ETH_MACMIIAR_PA_Pos )
#define ETH_MACMIIAR_PA_4                                   ( 0x10UL << ETH_MACMIIAR_PA_Pos )

#define ETH_MACMIIAR_MR_Pos                                 ( 6U )
#define ETH_MACMIIAR_MR_Msk                                 ( 0x1fUL << ETH_MACMIIAR_MR_Pos )
#define ETH_MACMIIAR_MR                                     ( ETH_MACMIIAR_MR_Msk )
#define ETH_MACMIIAR_MR_0                                   ( 0x1UL << ETH_MACMIIAR_MR_Pos )
#define ETH_MACMIIAR_MR_1                                   ( 0x2UL << ETH_MACMIIAR_MR_Pos )
#define ETH_MACMIIAR_MR_2                                   ( 0x4UL << ETH_MACMIIAR_MR_Pos )
#define ETH_MACMIIAR_MR_3                                   ( 0x8UL << ETH_MACMIIAR_MR_Pos )
#define ETH_MACMIIAR_MR_4                                   ( 0x10UL << ETH_MACMIIAR_MR_Pos )

#define ETH_MACMIIAR_CR_Pos                                 ( 2U )
#define ETH_MACMIIAR_CR_Msk                                 ( 0xfUL << ETH_MACMIIAR_CR_Pos )
#define ETH_MACMIIAR_CR                                     ( ETH_MACMIIAR_CR_Msk )
#define ETH_MACMIIAR_CR_0                                   ( 0x1UL << ETH_MACMIIAR_CR_Pos )
#define ETH_MACMIIAR_CR_1                                   ( 0x2UL << ETH_MACMIIAR_CR_Pos )
#define ETH_MACMIIAR_CR_2                                   ( 0x4UL << ETH_MACMIIAR_CR_Pos )
#define ETH_MACMIIAR_CR_3                                   ( 0x8UL << ETH_MACMIIAR_CR_Pos )

#define ETH_MACMIIAR_MW_Pos                                 ( 1U )
#define ETH_MACMIIAR_MW_Msk                                 ( 0x1UL << ETH_MACMIIAR_MW_Pos )
#define ETH_MACMIIAR_MW                                     ( ETH_MACMIIAR_MW_Msk )

#define ETH_MACMIIAR_MB_Pos                                 ( 0U )
#define ETH_MACMIIAR_MB_Msk                                 ( 0x1UL << ETH_MACMIIAR_MB_Pos )
#define ETH_MACMIIAR_MB                                     ( ETH_MACMIIAR_MB_Msk )


/***************  Bits definition for ETH_MACMIIDR  **********************/

#define ETH_MACMIIDR_MD_Pos                                 ( 0U )
#define ETH_MACMIIDR_MD_Msk                                 ( 0xffffUL << ETH_MACMIIDR_MD_Pos )
#define ETH_MACMIIDR_MD                                     ( ETH_MACMIIDR_MD_Msk )


/***************  Bits definition for ETH_MACFCR  **********************/

#define ETH_MACFCR_PT_Pos                                   ( 16U )
#define ETH_MACFCR_PT_Msk                                   ( 0xffffUL << ETH_MACFCR_PT_Pos )
#define ETH_MACFCR_PT                                       ( ETH_MACFCR_PT_Msk )

#define ETH_MACFCR_DZQP_Pos                                 ( 7U )
#define ETH_MACFCR_DZQP_Msk                                 ( 0x1UL << ETH_MACFCR_DZQP_Pos )
#define ETH_MACFCR_DZQP                                     ( ETH_MACFCR_DZQP_Msk )

#define ETH_MACFCR_PLT_Pos                                  ( 4U )
#define ETH_MACFCR_PLT_Msk                                  ( 0x3UL << ETH_MACFCR_PLT_Pos )
#define ETH_MACFCR_PLT                                      ( ETH_MACFCR_PLT_Msk )
#define ETH_MACFCR_PLT_0                                    ( 0x1UL << ETH_MACFCR_PLT_Pos )
#define ETH_MACFCR_PLT_1                                    ( 0x2UL << ETH_MACFCR_PLT_Pos )

#define ETH_MACFCR_UPFD_Pos                                 ( 3U )
#define ETH_MACFCR_UPFD_Msk                                 ( 0x1UL << ETH_MACFCR_UPFD_Pos )
#define ETH_MACFCR_UPFD                                     ( ETH_MACFCR_UPFD_Msk )

#define ETH_MACFCR_RFCE_Pos                                 ( 2U )
#define ETH_MACFCR_RFCE_Msk                                 ( 0x1UL << ETH_MACFCR_RFCE_Pos )
#define ETH_MACFCR_RFCE                                     ( ETH_MACFCR_RFCE_Msk )

#define ETH_MACFCR_TFCE_Pos                                 ( 1U )
#define ETH_MACFCR_TFCE_Msk                                 ( 0x1UL << ETH_MACFCR_TFCE_Pos )
#define ETH_MACFCR_TFCE                                     ( ETH_MACFCR_TFCE_Msk )

#define ETH_MACFCR_FCB_BPA_Pos                              ( 0U )
#define ETH_MACFCR_FCB_BPA_Msk                              ( 0x1UL << ETH_MACFCR_FCB_BPA_Pos )
#define ETH_MACFCR_FCB_BPA                                  ( ETH_MACFCR_FCB_BPA_Msk )


/***************  Bits definition for ETH_MACVLANTR  **********************/

#define ETH_MACVLANTR_VTHM_Pos                              ( 19U )
#define ETH_MACVLANTR_VTHM_Msk                              ( 0x1UL << ETH_MACVLANTR_VTHM_Pos )
#define ETH_MACVLANTR_VTHM                                  ( ETH_MACVLANTR_VTHM_Msk )

#define ETH_MACVLANTR_ESVL_Pos                              ( 18U )
#define ETH_MACVLANTR_ESVL_Msk                              ( 0x1UL << ETH_MACVLANTR_ESVL_Pos )
#define ETH_MACVLANTR_ESVL                                  ( ETH_MACVLANTR_ESVL_Msk )

#define ETH_MACVLANTR_VTIM_Pos                              ( 17U )
#define ETH_MACVLANTR_VTIM_Msk                              ( 0x1UL << ETH_MACVLANTR_VTIM_Pos )
#define ETH_MACVLANTR_VTIM                                  ( ETH_MACVLANTR_VTIM_Msk )

#define ETH_MACVLANTR_ETV_Pos                               ( 16U )
#define ETH_MACVLANTR_ETV_Msk                               ( 0x1UL << ETH_MACVLANTR_ETV_Pos )
#define ETH_MACVLANTR_ETV                                   ( ETH_MACVLANTR_ETV_Msk )

#define ETH_MACVLANTR_VL_Pos                                ( 0U )
#define ETH_MACVLANTR_VL_Msk                                ( 0xffffUL << ETH_MACVLANTR_VL_Pos )
#define ETH_MACVLANTR_VL                                    ( ETH_MACVLANTR_VL_Msk )


/***************  Bits definition for ETH_MACDBGR  **********************/

#define ETH_MACDBGR_TFF_Pos                                 ( 25U )
#define ETH_MACDBGR_TFF_Msk                                 ( 0x1UL << ETH_MACDBGR_TFF_Pos )
#define ETH_MACDBGR_TFF                                     ( ETH_MACDBGR_TFF_Msk )

#define ETH_MACDBGR_TFNE_Pos                                ( 24U )
#define ETH_MACDBGR_TFNE_Msk                                ( 0x1UL << ETH_MACDBGR_TFNE_Pos )
#define ETH_MACDBGR_TFNE                                    ( ETH_MACDBGR_TFNE_Msk )

#define ETH_MACDBGR_TFWA_Pos                                ( 22U )
#define ETH_MACDBGR_TFWA_Msk                                ( 0x1UL << ETH_MACDBGR_TFWA_Pos )
#define ETH_MACDBGR_TFWA                                    ( ETH_MACDBGR_TFWA_Msk )

#define ETH_MACDBGR_TFRS_Pos                                ( 20U )
#define ETH_MACDBGR_TFRS_Msk                                ( 0x3UL << ETH_MACDBGR_TFRS_Pos )
#define ETH_MACDBGR_TFRS                                    ( ETH_MACDBGR_TFRS_Msk )
#define ETH_MACDBGR_TFRS_0                                  ( 0x1UL << ETH_MACDBGR_TFRS_Pos )
#define ETH_MACDBGR_TFRS_1                                  ( 0x2UL << ETH_MACDBGR_TFRS_Pos )

#define ETH_MACDBGR_MTP_Pos                                 ( 19U )
#define ETH_MACDBGR_MTP_Msk                                 ( 0x1UL << ETH_MACDBGR_MTP_Pos )
#define ETH_MACDBGR_MTP                                     ( ETH_MACDBGR_MTP_Msk )

#define ETH_MACDBGR_MTFCS_Pos                               ( 17U )
#define ETH_MACDBGR_MTFCS_Msk                               ( 0x3UL << ETH_MACDBGR_MTFCS_Pos )
#define ETH_MACDBGR_MTFCS                                   ( ETH_MACDBGR_MTFCS_Msk )
#define ETH_MACDBGR_MTFCS_0                                 ( 0x1UL << ETH_MACDBGR_MTFCS_Pos )
#define ETH_MACDBGR_MTFCS_1                                 ( 0x2UL << ETH_MACDBGR_MTFCS_Pos )

#define ETH_MACDBGR_MMTEA_Pos                               ( 16U )
#define ETH_MACDBGR_MMTEA_Msk                               ( 0x1UL << ETH_MACDBGR_MMTEA_Pos )
#define ETH_MACDBGR_MMTEA                                   ( ETH_MACDBGR_MMTEA_Msk )

#define ETH_MACDBGR_RFFL_Pos                                ( 8U )
#define ETH_MACDBGR_RFFL_Msk                                ( 0x3UL << ETH_MACDBGR_RFFL_Pos )
#define ETH_MACDBGR_RFFL                                    ( ETH_MACDBGR_RFFL_Msk )
#define ETH_MACDBGR_RFFL_0                                  ( 0x1UL << ETH_MACDBGR_RFFL_Pos )
#define ETH_MACDBGR_RFFL_1                                  ( 0x2UL << ETH_MACDBGR_RFFL_Pos )

#define ETH_MACDBGR_RFRCS_Pos                               ( 5U )
#define ETH_MACDBGR_RFRCS_Msk                               ( 0x3UL << ETH_MACDBGR_RFRCS_Pos )
#define ETH_MACDBGR_RFRCS                                   ( ETH_MACDBGR_RFRCS_Msk )
#define ETH_MACDBGR_RFRCS_0                                 ( 0x1UL << ETH_MACDBGR_RFRCS_Pos )
#define ETH_MACDBGR_RFRCS_1                                 ( 0x2UL << ETH_MACDBGR_RFRCS_Pos )

#define ETH_MACDBGR_RFWCS_Pos                               ( 4U )
#define ETH_MACDBGR_RFWCS_Msk                               ( 0x1UL << ETH_MACDBGR_RFWCS_Pos )
#define ETH_MACDBGR_RFWCS                                   ( ETH_MACDBGR_RFWCS_Msk )

#define ETH_MACDBGR_MRFFCS_Pos                              ( 1U )
#define ETH_MACDBGR_MRFFCS_Msk                              ( 0x3UL << ETH_MACDBGR_MRFFCS_Pos )
#define ETH_MACDBGR_MRFFCS                                  ( ETH_MACDBGR_MRFFCS_Msk )
#define ETH_MACDBGR_MRFFCS_0                                ( 0x1UL << ETH_MACDBGR_MRFFCS_Pos )
#define ETH_MACDBGR_MRFFCS_1                                ( 0x2UL << ETH_MACDBGR_MRFFCS_Pos )

#define ETH_MACDBGR_MMRPES_Pos                              ( 0U )
#define ETH_MACDBGR_MMRPES_Msk                              ( 0x1UL << ETH_MACDBGR_MMRPES_Pos )
#define ETH_MACDBGR_MMRPES                                  ( ETH_MACDBGR_MMRPES_Msk )


/***************  Bits definition for ETH_MACRWUFF  **********************/

#define ETH_MACRWUFF_MACRWUFF_Pos                           ( 0U )
#define ETH_MACRWUFF_MACRWUFF_Msk                           ( 0xffffffffUL << ETH_MACRWUFF_MACRWUFF_Pos )
#define ETH_MACRWUFF_MACRWUFF                               ( ETH_MACRWUFF_MACRWUFF_Msk )


/***************  Bits definition for ETH_MACPMTCSR  **********************/

#define ETH_MACPMTCSR_RWFFPR_Pos                            ( 31U )
#define ETH_MACPMTCSR_RWFFPR_Msk                            ( 0x1UL << ETH_MACPMTCSR_RWFFPR_Pos )
#define ETH_MACPMTCSR_RWFFPR                                ( ETH_MACPMTCSR_RWFFPR_Msk )

#define ETH_MACPMTCSR_RWFP_Pos                              ( 24U )
#define ETH_MACPMTCSR_RWFP_Msk                              ( 0x3UL << ETH_MACPMTCSR_GU_Pos )
#define ETH_MACPMTCSR_RWFP                                  ( ETH_MACPMTCSR_GU_Msk )
#define ETH_MACPMTCSR_RWFP_0                                ( 0x1UL << ETH_MACPMTCSR_GU_Pos )
#define ETH_MACPMTCSR_RWFP_1                                ( 0x2UL << ETH_MACPMTCSR_GU_Pos )

#define ETH_MACPMTCSR_GU_Pos                                ( 9U )
#define ETH_MACPMTCSR_GU_Msk                                ( 0x1UL << ETH_MACPMTCSR_GU_Pos )
#define ETH_MACPMTCSR_GU                                    ( ETH_MACPMTCSR_GU_Msk )

#define ETH_MACPMTCSR_WFR_Pos                               ( 6U )
#define ETH_MACPMTCSR_WFR_Msk                               ( 0x1UL << ETH_MACPMTCSR_WFR_Pos )
#define ETH_MACPMTCSR_WFR                                   ( ETH_MACPMTCSR_WFR_Msk )

#define ETH_MACPMTCSR_MPR_Pos                               ( 5U )
#define ETH_MACPMTCSR_MPR_Msk                               ( 0x1UL << ETH_MACPMTCSR_MPR_Pos )
#define ETH_MACPMTCSR_MPR                                   ( ETH_MACPMTCSR_MPR_Msk )

#define ETH_MACPMTCSR_WFE_Pos                               ( 2U )
#define ETH_MACPMTCSR_WFE_Msk                               ( 0x1UL << ETH_MACPMTCSR_WFE_Pos )
#define ETH_MACPMTCSR_WFE                                   ( ETH_MACPMTCSR_WFE_Msk )

#define ETH_MACPMTCSR_MPE_Pos                               ( 1U )
#define ETH_MACPMTCSR_MPE_Msk                               ( 0x1UL << ETH_MACPMTCSR_MPE_Pos )
#define ETH_MACPMTCSR_MPE                                   ( ETH_MACPMTCSR_MPE_Msk )

#define ETH_MACPMTCSR_PD_Pos                                ( 0U )
#define ETH_MACPMTCSR_PD_Msk                                ( 0x1UL << ETH_MACPMTCSR_PD_Pos )
#define ETH_MACPMTCSR_PD                                    ( ETH_MACPMTCSR_PD_Msk )


/***************  Bits definition for ETH_MACLPICSR  **********************/

#define ETH_MACLPICSR_LPITXA_Pos                            ( 19U )
#define ETH_MACLPICSR_LPITXA_Msk                            ( 0x1UL << ETH_MACLPICSR_LPITXA_Pos )
#define ETH_MACLPICSR_LPITXA                                ( ETH_MACLPICSR_LPITXA_Msk )

#define ETH_MACLPICSR_PLSEN_Pos                             ( 18U )
#define ETH_MACLPICSR_PLSEN_Msk                             ( 0x1UL << ETH_MACLPICSR_PLSEN_Pos )
#define ETH_MACLPICSR_PLSEN                                 ( ETH_MACLPICSR_PLSEN_Msk )

#define ETH_MACLPICSR_PLS_Pos                               ( 17U )
#define ETH_MACLPICSR_PLS_Msk                               ( 0x1UL << ETH_MACLPICSR_PLS_Pos )
#define ETH_MACLPICSR_PLS                                   ( ETH_MACLPICSR_PLS_Msk )

#define ETH_MACLPICSR_LPIEN_Pos                             ( 16U )
#define ETH_MACLPICSR_LPIEN_Msk                             ( 0x1UL << ETH_MACLPICSR_LPIEN_Pos )
#define ETH_MACLPICSR_LPIEN                                 ( ETH_MACLPICSR_LPIEN_Msk )

#define ETH_MACLPICSR_RLPIST_Pos                            ( 9U )
#define ETH_MACLPICSR_RLPIST_Msk                            ( 0x1UL << ETH_MACLPICSR_RLPIST_Pos )
#define ETH_MACLPICSR_RLPIST                                ( ETH_MACLPICSR_RLPIST_Msk )

#define ETH_MACLPICSR_TLPIST_Pos                            ( 8U )
#define ETH_MACLPICSR_TLPIST_Msk                            ( 0x1UL << ETH_MACLPICSR_TLPIST_Pos )
#define ETH_MACLPICSR_TLPIST                                ( ETH_MACLPICSR_TLPIST_Msk )

#define ETH_MACLPICSR_RLPIEX_Pos                            ( 3U )
#define ETH_MACLPICSR_RLPIEX_Msk                            ( 0x1UL << ETH_MACLPICSR_RLPIEX_Pos )
#define ETH_MACLPICSR_RLPIEX                                ( ETH_MACLPICSR_RLPIEX_Msk )

#define ETH_MACLPICSR_RLPIEN_Pos                            ( 2U )
#define ETH_MACLPICSR_RLPIEN_Msk                            ( 0x1UL << ETH_MACLPICSR_RLPIEN_Pos )
#define ETH_MACLPICSR_RLPIEN                                ( ETH_MACLPICSR_RLPIEN_Msk )

#define ETH_MACLPICSR_TLPIEX_Pos                            ( 1U )
#define ETH_MACLPICSR_TLPIEX_Msk                            ( 0x1UL << ETH_MACLPICSR_TLPIEX_Pos )
#define ETH_MACLPICSR_TLPIEX                                ( ETH_MACLPICSR_TLPIEX_Msk )

#define ETH_MACLPICSR_TLPIEN_Pos                            ( 0U )
#define ETH_MACLPICSR_TLPIEN_Msk                            ( 0x1UL << ETH_MACLPICSR_TLPIEN_Pos )
#define ETH_MACLPICSR_TLPIEN                                ( ETH_MACLPICSR_TLPIEN_Msk )


/***************  Bits definition for ETH_MACLPITCR  **********************/

#define ETH_MACLPITCR_LST_Pos                               ( 16U )
#define ETH_MACLPITCR_LST_Msk                               ( 0x3FFUL << ETH_MACLPITCR_LST_Pos )
#define ETH_MACLPITCR_LST                                   ( ETH_MACLPITCR_LST_Msk )

#define ETH_MACLPITCR_TWT_Pos                               ( 0U )
#define ETH_MACLPITCR_TWT_Msk                               ( 0xFFFFUL << ETH_MACLPITCR_TWT_Pos )
#define ETH_MACLPITCR_TWT                                   ( ETH_MACLPITCR_TWT_Msk )


/***************  Bits definition for ETH_MACISR  **********************/

#define ETH_MACISR_LPIIS_Pos                                ( 10U )
#define ETH_MACISR_LPIIS_Msk                                ( 0x1UL << ETH_MACISR_LPIIS_Pos )
#define ETH_MACISR_LPIIS                                    ( ETH_MACISR_LPIIS_Msk )

#define ETH_MACISR_TIS_Pos                                  ( 9U )
#define ETH_MACISR_TIS_Msk                                  ( 0x1UL << ETH_MACISR_TIS_Pos )
#define ETH_MACISR_TIS                                      ( ETH_MACISR_TIS_Msk )

#define ETH_MACISR_MMCTIS_Pos                               ( 6U )
#define ETH_MACISR_MMCTIS_Msk                               ( 0x1UL << ETH_MACISR_MMCTIS_Pos )
#define ETH_MACISR_MMCTIS                                   ( ETH_MACISR_MMCTIS_Msk )

#define ETH_MACISR_MMCRIS_Pos                               ( 5U )
#define ETH_MACISR_MMCRIS_Msk                               ( 0x1UL << ETH_MACISR_MMCRIS_Pos )
#define ETH_MACISR_MMCRIS                                   ( ETH_MACISR_MMCRIS_Msk )

#define ETH_MACISR_MMCIS_Pos                                ( 4U )
#define ETH_MACISR_MMCIS_Msk                                ( 0x1UL << ETH_MACISR_MMCIS_Pos )
#define ETH_MACISR_MMCIS                                    ( ETH_MACISR_MMCIS_Msk )

#define ETH_MACISR_PMTS_Pos                                 ( 3U )
#define ETH_MACISR_PMTS_Msk                                 ( 0x1UL << ETH_MACISR_PMTS_Pos )
#define ETH_MACISR_PMTS                                     ( ETH_MACISR_PMTS_Msk )


/***************  Bits definition for ETH_MACIMR  **********************/

#define ETH_MACIMR_LPIIM_Pos                                ( 10U )
#define ETH_MACIMR_LPIIM_Msk                                ( 0x1UL << ETH_MACIMR_LPIIM_Pos )
#define ETH_MACIMR_LPIIM                                    ( ETH_MACIMR_LPIIM_Msk )

#define ETH_MACIMR_TIM_Pos                                  ( 9U )
#define ETH_MACIMR_TIM_Msk                                  ( 0x1UL << ETH_MACIMR_TIM_Pos )
#define ETH_MACIMR_TIM                                      ( ETH_MACIMR_TIM_Msk )

#define ETH_MACIMR_PIM_Pos                                  ( 3U )
#define ETH_MACIMR_PIM_Msk                                  ( 0x1UL << ETH_MACIMR_PIM_Pos )
#define ETH_MACIMR_PIM                                      ( ETH_MACIMR_PIM_Msk )


/***************  Bits definition for ETH_MACA0HR  **********************/

#define ETH_MACA0HR_AE_Pos                                  ( 31U )
#define ETH_MACA0HR_AE_Msk                                  ( 0x1UL << ETH_MACA0HR_AE_Pos )
#define ETH_MACA0HR_AE                                      ( ETH_MACA0HR_AE_Msk )

#define ETH_MACA0HR_MACA0H_Pos                              ( 0U )
#define ETH_MACA0HR_MACA0H_Msk                              ( 0xffffUL << ETH_MACA0HR_MACA0H_Pos )
#define ETH_MACA0HR_MACA0H                                  ( ETH_MACA0HR_MACA0H_Msk )


/***************  Bits definition for ETH_MACA0LR  **********************/

#define ETH_MACA0LR_MACA0L_Pos                              ( 0U )
#define ETH_MACA0LR_MACA0L_Msk                              ( 0xffffffffUL << ETH_MACA0LR_MACA0L_Pos )
#define ETH_MACA0LR_MACA0L                                  ( ETH_MACA0LR_MACA0L_Msk )


/***************  Bits definition for ETH_MACA1HR  **********************/

#define ETH_MACA1HR_AE_Pos                                  ( 31U )
#define ETH_MACA1HR_AE_Msk                                  ( 0x1UL << ETH_MACA1HR_AE_Pos )
#define ETH_MACA1HR_AE                                      ( ETH_MACA1HR_AE_Msk )

#define ETH_MACA1HR_SA_Pos                                  ( 30U )
#define ETH_MACA1HR_SA_Msk                                  ( 0x1UL << ETH_MACA1HR_SA_Pos )
#define ETH_MACA1HR_SA                                      ( ETH_MACA1HR_SA_Msk )

#define ETH_MACA1HR_MBC_Pos                                 ( 24U )
#define ETH_MACA1HR_MBC_Msk                                 ( 0x3fUL << ETH_MACA1HR_MBC_Pos )
#define ETH_MACA1HR_MBC                                     ( ETH_MACA1HR_MBC_Msk )
#define ETH_MACA1HR_MBC_0                                   ( 0x1UL << ETH_MACA1HR_MBC_Pos )
#define ETH_MACA1HR_MBC_1                                   ( 0x2UL << ETH_MACA1HR_MBC_Pos )
#define ETH_MACA1HR_MBC_2                                   ( 0x4UL << ETH_MACA1HR_MBC_Pos )
#define ETH_MACA1HR_MBC_3                                   ( 0x8UL << ETH_MACA1HR_MBC_Pos )
#define ETH_MACA1HR_MBC_4                                   ( 0x10UL << ETH_MACA1HR_MBC_Pos )
#define ETH_MACA1HR_MBC_5                                   ( 0x20UL << ETH_MACA1HR_MBC_Pos )

#define ETH_MACA1HR_MACA1H_Pos                              ( 0U )
#define ETH_MACA1HR_MACA1H_Msk                              ( 0xffffUL << ETH_MACA1HR_MACA1H_Pos )
#define ETH_MACA1HR_MACA1H                                  ( ETH_MACA1HR_MACA1H_Msk )


/***************  Bits definition for ETH_MACA1LR  **********************/

#define ETH_MACA1LR_MACA1L_Pos                              ( 0U )
#define ETH_MACA1LR_MACA1L_Msk                              ( 0xffffffffUL << ETH_MACA1LR_MACA1L_Pos )
#define ETH_MACA1LR_MACA1L                                  ( ETH_MACA1LR_MACA1L_Msk )


/***************  Bits definition for ETH_MACA2HR  **********************/

#define ETH_MACA2HR_AE_Pos                                  ( 31U )
#define ETH_MACA2HR_AE_Msk                                  ( 0x1UL << ETH_MACA2HR_AE_Pos )
#define ETH_MACA2HR_AE                                      ( ETH_MACA2HR_AE_Msk )

#define ETH_MACA2HR_SA_Pos                                  ( 30U )
#define ETH_MACA2HR_SA_Msk                                  ( 0x1UL << ETH_MACA2HR_SA_Pos )
#define ETH_MACA2HR_SA                                      ( ETH_MACA2HR_SA_Msk )

#define ETH_MACA2HR_MBC_Pos                                 ( 24U )
#define ETH_MACA2HR_MBC_Msk                                 ( 0x3fUL << ETH_MACA2HR_MBC_Pos )
#define ETH_MACA2HR_MBC                                     ( ETH_MACA2HR_MBC_Msk )
#define ETH_MACA2HR_MBC_0                                   ( 0x1UL << ETH_MACA2HR_MBC_Pos )
#define ETH_MACA2HR_MBC_1                                   ( 0x2UL << ETH_MACA2HR_MBC_Pos )
#define ETH_MACA2HR_MBC_2                                   ( 0x4UL << ETH_MACA2HR_MBC_Pos )
#define ETH_MACA2HR_MBC_3                                   ( 0x8UL << ETH_MACA2HR_MBC_Pos )
#define ETH_MACA2HR_MBC_4                                   ( 0x10UL << ETH_MACA2HR_MBC_Pos )
#define ETH_MACA2HR_MBC_5                                   ( 0x20UL << ETH_MACA2HR_MBC_Pos )

#define ETH_MACA2HR_MACA2H_Pos                              ( 0U )
#define ETH_MACA2HR_MACA2H_Msk                              ( 0xffffUL << ETH_MACA2HR_MACA2H_Pos )
#define ETH_MACA2HR_MACA2H                                  ( ETH_MACA2HR_MACA2H_Msk )


/***************  Bits definition for ETH_MACA2LR  **********************/

#define ETH_MACA2LR_MACA2L_Pos                              ( 0U )
#define ETH_MACA2LR_MACA2L_Msk                              ( 0xffffffffUL << ETH_MACA2LR_MACA2L_Pos )
#define ETH_MACA2LR_MACA2L                                  ( ETH_MACA2LR_MACA2L_Msk )


/***************  Bits definition for ETH_MACA3HR  **********************/

#define ETH_MACA3HR_AE_Pos                                  ( 31U )
#define ETH_MACA3HR_AE_Msk                                  ( 0x1UL << ETH_MACA3HR_AE_Pos )
#define ETH_MACA3HR_AE                                      ( ETH_MACA3HR_AE_Msk )

#define ETH_MACA3HR_SA_Pos                                  ( 30U )
#define ETH_MACA3HR_SA_Msk                                  ( 0x1UL << ETH_MACA3HR_SA_Pos )
#define ETH_MACA3HR_SA                                      ( ETH_MACA3HR_SA_Msk )

#define ETH_MACA3HR_MBC_Pos                                 ( 24U )
#define ETH_MACA3HR_MBC_Msk                                 ( 0x3fUL << ETH_MACA3HR_MBC_Pos )
#define ETH_MACA3HR_MBC                                     ( ETH_MACA3HR_MBC_Msk )
#define ETH_MACA3HR_MBC_0                                   ( 0x1UL << ETH_MACA3HR_MBC_Pos )
#define ETH_MACA3HR_MBC_1                                   ( 0x2UL << ETH_MACA3HR_MBC_Pos )
#define ETH_MACA3HR_MBC_2                                   ( 0x4UL << ETH_MACA3HR_MBC_Pos )
#define ETH_MACA3HR_MBC_3                                   ( 0x8UL << ETH_MACA3HR_MBC_Pos )
#define ETH_MACA3HR_MBC_4                                   ( 0x10UL << ETH_MACA3HR_MBC_Pos )
#define ETH_MACA3HR_MBC_5                                   ( 0x20UL << ETH_MACA3HR_MBC_Pos )

#define ETH_MACA3HR_MACA3H_Pos                              ( 0U )
#define ETH_MACA3HR_MACA3H_Msk                              ( 0xffffUL << ETH_MACA3HR_MACA3H_Pos )
#define ETH_MACA3HR_MACA3H                                  ( ETH_MACA3HR_MACA3H_Msk )


/***************  Bits definition for ETH_MACA3LR  **********************/

#define ETH_MACA3LR_MACA3L_Pos                              ( 0U )
#define ETH_MACA3LR_MACA3L_Msk                              ( 0xffffffffUL << ETH_MACA3LR_MACA3L_Pos )
#define ETH_MACA3LR_MACA3L                                  ( ETH_MACA3LR_MACA3L_Msk )


/***************  Bits definition for ETH_MACWTR  **********************/

#define ETH_MACWTR_PWE_Pos                                  ( 16U )
#define ETH_MACWTR_PWE_Msk                                  ( 0x1UL << ETH_MACWTR_PWE_Pos )
#define ETH_MACWTR_PWE                                      ( ETH_MACWTR_PWE_Msk )

#define ETH_MACWTR_WTO_Pos                                  ( 0U )
#define ETH_MACWTR_WTO_Msk                                  ( 0x3FFFUL << ETH_MACWTR_WTO_Pos )
#define ETH_MACWTR_WTO                                      ( ETH_MACWTR_WTO_Msk )


/***************  Bits definition for ETH_MMCCR  **********************/

#define ETH_MMCCR_UCDBC_Pos                                 ( 8U )
#define ETH_MMCCR_UCDBC_Msk                                 ( 0x1UL << ETH_MMCCR_UCDBC_Pos )
#define ETH_MMCCR_UCDBC                                     ( ETH_MMCCR_UCDBC_Msk )

#define ETH_MMCCR_CNTPRSTLVL_Pos                            ( 5U )
#define ETH_MMCCR_CNTPRSTLVL_Msk                            ( 0x1UL << ETH_MMCCR_CNTPRSTLVL_Pos )
#define ETH_MMCCR_CNTPRSTLVL                                ( ETH_MMCCR_CNTPRSTLVL_Msk )

#define ETH_MMCCR_CNTPRST_Pos                               ( 4U )
#define ETH_MMCCR_CNTPRST_Msk                               ( 0x1UL << ETH_MMCCR_CNTPRST_Pos )
#define ETH_MMCCR_CNTPRST                                   ( ETH_MMCCR_CNTPRST_Msk )

#define ETH_MMCCR_CNTFREEZ_Pos                              ( 3U )
#define ETH_MMCCR_CNTFREEZ_Msk                              ( 0x1UL << ETH_MMCCR_CNTFREEZ_Pos )
#define ETH_MMCCR_CNTFREEZ                                  ( ETH_MMCCR_CNTFREEZ_Msk )

#define ETH_MMCCR_RSTONRD_Pos                               ( 2U )
#define ETH_MMCCR_RSTONRD_Msk                               ( 0x1UL << ETH_MMCCR_RSTONRD_Pos )
#define ETH_MMCCR_RSTONRD                                   ( ETH_MMCCR_RSTONRD_Msk )

#define ETH_MMCCR_CNTSTOPRO_Pos                             ( 1U )
#define ETH_MMCCR_CNTSTOPRO_Msk                             ( 0x1UL << ETH_MMCCR_CNTSTOPRO_Pos )
#define ETH_MMCCR_CNTSTOPRO                                 ( ETH_MMCCR_CNTSTOPRO_Msk )

#define ETH_MMCCR_CNTRST_Pos                                ( 0U )
#define ETH_MMCCR_CNTRST_Msk                                ( 0x1UL << ETH_MMCCR_CNTRST_Pos )
#define ETH_MMCCR_CNTRST                                    ( ETH_MMCCR_CNTRST_Msk )


/***************  Bits definition for ETH_MMCRIR  **********************/

#define ETH_MMCRIR_RGUFIS_Pos                               ( 17U )
#define ETH_MMCRIR_RGUFIS_Msk                               ( 0x1UL << ETH_MMCRIR_RGUFIS_Pos )
#define ETH_MMCRIR_RGUFIS                                   ( ETH_MMCRIR_RGUFIS_Msk )

#define ETH_MMCRIR_RFAEIS_Pos                               ( 6U )
#define ETH_MMCRIR_RFAEIS_Msk                               ( 0x1UL << ETH_MMCRIR_RFAEIS_Pos )
#define ETH_MMCRIR_RFAEIS                                   ( ETH_MMCRIR_RFAEIS_Msk )

#define ETH_MMCRIR_RFCEIS_Pos                               ( 5U )
#define ETH_MMCRIR_RFCEIS_Msk                               ( 0x1UL << ETH_MMCRIR_RFCEIS_Pos )
#define ETH_MMCRIR_RFCEIS                                   ( ETH_MMCRIR_RFCEIS_Msk )


/***************  Bits definition for ETH_MMCTIR  **********************/

#define ETH_MMCTIR_TGFIS_Pos                                ( 21U )
#define ETH_MMCTIR_TGFIS_Msk                                ( 0x1UL << ETH_MMCTIR_TGFIS_Pos )
#define ETH_MMCTIR_TGFIS                                    ( ETH_MMCTIR_TGFIS_Msk )

#define ETH_MMCTIR_TMCGFCIS_Pos                             ( 15U )
#define ETH_MMCTIR_TMCGFCIS_Msk                             ( 0x1UL << ETH_MMCTIR_TMCGFCIS_Pos )
#define ETH_MMCTIR_TMCGFCIS                                 ( ETH_MMCTIR_TMCGFCIS_Msk )

#define ETH_MMCTIR_TSCGFCIS_Pos                             ( 14U )
#define ETH_MMCTIR_TSCGFCIS_Msk                             ( 0x1UL << ETH_MMCTIR_TSCGFCIS_Pos )
#define ETH_MMCTIR_TSCGFCIS                                 ( ETH_MMCTIR_TSCGFCIS_Msk )


/***************  Bits definition for ETH_MMCRIMR  **********************/

#define ETH_MMCRIMR_RGUFIM_Pos                              ( 17U )
#define ETH_MMCRIMR_RGUFIM_Msk                              ( 0x1UL << ETH_MMCRIMR_RGUFIM_Pos )
#define ETH_MMCRIMR_RGUFIM                                  ( ETH_MMCRIMR_RGUFIM_Msk )

#define ETH_MMCRIMR_RFAEIM_Pos                              ( 6U )
#define ETH_MMCRIMR_RFAEIM_Msk                              ( 0x1UL << ETH_MMCRIMR_RFAEIM_Pos )
#define ETH_MMCRIMR_RFAEIM                                  ( ETH_MMCRIMR_RFAEIM_Msk )

#define ETH_MMCRIMR_RFCEIM_Pos                              ( 5U )
#define ETH_MMCRIMR_RFCEIM_Msk                              ( 0x1UL << ETH_MMCRIMR_RFCEIM_Pos )
#define ETH_MMCRIMR_RFCEIM                                  ( ETH_MMCRIMR_RFCEIM_Msk )


/***************  Bits definition for ETH_MMCTIMR  **********************/

#define ETH_MMCTIMR_TGFIM_Pos                               ( 21U )
#define ETH_MMCTIMR_TGFIM_Msk                               ( 0x1UL << ETH_MMCTIMR_TGFIM_Pos )
#define ETH_MMCTIMR_TGFIM                                   ( ETH_MMCTIMR_TGFIM_Msk )

#define ETH_MMCTIMR_TMCGFCIM_Pos                            ( 15U )
#define ETH_MMCTIMR_TMCGFCIM_Msk                            ( 0x1UL << ETH_MMCTIMR_TMCGFCIM_Pos )
#define ETH_MMCTIMR_TMCGFCIM                                ( ETH_MMCTIMR_TMCGFCIM_Msk )

#define ETH_MMCTIMR_TSCGFCIM_Pos                            ( 14U )
#define ETH_MMCTIMR_TSCGFCIM_Msk                            ( 0x1UL << ETH_MMCTIMR_TSCGFCIM_Pos )
#define ETH_MMCTIMR_TSCGFCIM                                ( ETH_MMCTIMR_TSCGFCIM_Msk )


/***************  Bits definition for ETH_MMCTGFSCCR  **********************/

#define ETH_MMCTGFSCCR_TGFSCC_Pos                           ( 0U )
#define ETH_MMCTGFSCCR_TGFSCC_Msk                           ( 0xffffffffUL << ETH_MMCTGFSCCR_TGFSCC_Pos )
#define ETH_MMCTGFSCCR_TGFSCC                               ( ETH_MMCTGFSCCR_TGFSCC_Msk )


/***************  Bits definition for ETH_MMCTGFMCCR  **********************/

#define ETH_MMCTGFMCCR_TGFMCC_Pos                           ( 0U )
#define ETH_MMCTGFMCCR_TGFMCC_Msk                           ( 0xffffffffUL << ETH_MMCTGFMCCR_TGFMCC_Pos )
#define ETH_MMCTGFMCCR_TGFMCC                               ( ETH_MMCTGFMCCR_TGFMCC_Msk )


/***************  Bits definition for ETH_MMCTGFCR  **********************/

#define ETH_MMCTGFCR_TGFC_Pos                               ( 0U )
#define ETH_MMCTGFCR_TGFC_Msk                               ( 0xffffffffUL << ETH_MMCTGFCR_TGFC_Pos )
#define ETH_MMCTGFCR_TGFC                                   ( ETH_MMCTGFCR_TGFC_Msk )


/***************  Bits definition for ETH_MMCRFCECR  **********************/

#define ETH_MMCRFCECR_RFCEC_Pos                             ( 0U )
#define ETH_MMCRFCECR_RFCEC_Msk                             ( 0xffffffffUL << ETH_MMCRFCECR_RFCEC_Pos )
#define ETH_MMCRFCECR_RFCEC                                 ( ETH_MMCRFCECR_RFCEC_Msk )


/***************  Bits definition for ETH_MMCRFAECR  **********************/

#define ETH_MMCRFAECR_RFAEC_Pos                             ( 0U )
#define ETH_MMCRFAECR_RFAEC_Msk                             ( 0xffffffffUL << ETH_MMCRFAECR_RFAEC_Pos )
#define ETH_MMCRFAECR_RFAEC                                 ( ETH_MMCRFAECR_RFAEC_Msk )


/***************  Bits definition for ETH_MMCRGUFCR  **********************/

#define ETH_MMCRGUFCR_RGUFC_Pos                             ( 0U )
#define ETH_MMCRGUFCR_RGUFC_Msk                             ( 0xffffffffUL << ETH_MMCRGUFCR_RGUFC_Pos )
#define ETH_MMCRGUFCR_RGUFC                                 ( ETH_MMCRGUFCR_RGUFC_Msk )


/***************  Bits definition for ETH_MACL3L4C0R  **********************/

#define ETH_MACL3L4C0R_L4DPIM0_Pos                          ( 21U )
#define ETH_MACL3L4C0R_L4DPIM0_Msk                          ( 0x1UL << ETH_MACL3L4C0R_L4DPIM0_Pos )
#define ETH_MACL3L4C0R_L4DPIM0                              ( ETH_MACL3L4C0R_L4DPIM0_Msk )

#define ETH_MACL3L4C0R_L4DPM0_Pos                           ( 20U )
#define ETH_MACL3L4C0R_L4DPM0_Msk                           ( 0x1UL << ETH_MACL3L4C0R_L4DPM0_Pos )
#define ETH_MACL3L4C0R_L4DPM0                               ( ETH_MACL3L4C0R_L4DPM0_Msk )

#define ETH_MACL3L4C0R_L4SPIM0_Pos                          ( 19U )
#define ETH_MACL3L4C0R_L4SPIM0_Msk                          ( 0x1UL << ETH_MACL3L4C0R_L4SPIM0_Pos )
#define ETH_MACL3L4C0R_L4SPIM0                              ( ETH_MACL3L4C0R_L4SPIM0_Msk )

#define ETH_MACL3L4C0R_L4SPM0_Pos                           ( 18U )
#define ETH_MACL3L4C0R_L4SPM0_Msk                           ( 0x1UL << ETH_MACL3L4C0R_L4SPM0_Pos )
#define ETH_MACL3L4C0R_L4SPM0                               ( ETH_MACL3L4C0R_L4SPM0_Msk )

#define ETH_MACL3L4C0R_L4PEN0_Pos                           ( 16U )
#define ETH_MACL3L4C0R_L4PEN0_Msk                           ( 0x1UL << ETH_MACL3L4C0R_L4PEN0_Pos )
#define ETH_MACL3L4C0R_L4PEN0                               ( ETH_MACL3L4C0R_L4PEN0_Msk )

#define ETH_MACL3L4C0R_L3HDBM0_Pos                          ( 11U )
#define ETH_MACL3L4C0R_L3HDBM0_Msk                          ( 0x1FUL << ETH_MACL3L4C0R_L3HDBM0_Pos )
#define ETH_MACL3L4C0R_L3HDBM0                              ( ETH_MACL3L4C0R_L3HDBM0_Msk )
#define ETH_MACL3L4C0R_L3HDBM0_0                            ( 0x01UL << ETH_MACL3L4C0R_L3HDBM0_Pos )
#define ETH_MACL3L4C0R_L3HDBM0_1                            ( 0x02UL << ETH_MACL3L4C0R_L3HDBM0_Pos )
#define ETH_MACL3L4C0R_L3HDBM0_2                            ( 0x04UL << ETH_MACL3L4C0R_L3HDBM0_Pos )
#define ETH_MACL3L4C0R_L3HDBM0_3                            ( 0x08UL << ETH_MACL3L4C0R_L3HDBM0_Pos )
#define ETH_MACL3L4C0R_L3HDBM0_4                            ( 0x10UL << ETH_MACL3L4C0R_L3HDBM0_Pos )

#define ETH_MACL3L4C0R_L3HSBM0_Pos                          ( 6U )
#define ETH_MACL3L4C0R_L3HSBM0_Msk                          ( 0x1FUL << ETH_MACL3L4C0R_L3HSBM0_Pos )
#define ETH_MACL3L4C0R_L3HSBM0                              ( ETH_MACL3L4C0R_L3HSBM0_Msk )
#define ETH_MACL3L4C0R_L3HSBM0_0                            ( 0x01UL << ETH_MACL3L4C0R_L3HSBM0_Pos )
#define ETH_MACL3L4C0R_L3HSBM0_1                            ( 0x02UL << ETH_MACL3L4C0R_L3HSBM0_Pos )
#define ETH_MACL3L4C0R_L3HSBM0_2                            ( 0x04UL << ETH_MACL3L4C0R_L3HSBM0_Pos )
#define ETH_MACL3L4C0R_L3HSBM0_3                            ( 0x08UL << ETH_MACL3L4C0R_L3HSBM0_Pos )
#define ETH_MACL3L4C0R_L3HSBM0_4                            ( 0x10UL << ETH_MACL3L4C0R_L3HSBM0_Pos )

#define ETH_MACL3L4C0R_L3DAIM0_Pos                          ( 5U )
#define ETH_MACL3L4C0R_L3DAIM0_Msk                          ( 0x1UL << ETH_MACL3L4C0R_L3DAIM0_Pos )
#define ETH_MACL3L4C0R_L3DAIM0                              ( ETH_MACL3L4C0R_L3DAIM0_Msk )

#define ETH_MACL3L4C0R_L3DAM0_Pos                           ( 4U )
#define ETH_MACL3L4C0R_L3DAM0_Msk                           ( 0x1UL << ETH_MACL3L4C0R_L3DAM0_Pos )
#define ETH_MACL3L4C0R_L3DAM0                               ( ETH_MACL3L4C0R_L3DAM0_Msk )

#define ETH_MACL3L4C0R_L3SAIM0_Pos                          ( 3U )
#define ETH_MACL3L4C0R_L3SAIM0_Msk                          ( 0x1UL << ETH_MACL3L4C0R_L3SAIM0_Pos )
#define ETH_MACL3L4C0R_L3SAIM0                              ( ETH_MACL3L4C0R_L3SAIM0_Msk )

#define ETH_MACL3L4C0R_L3SAM0_Pos                           ( 2U )
#define ETH_MACL3L4C0R_L3SAM0_Msk                           ( 0x1UL << ETH_MACL3L4C0R_L3SAM0_Pos )
#define ETH_MACL3L4C0R_L3SAM0                               ( ETH_MACL3L4C0R_L3SAM0_Msk )

#define ETH_MACL3L4C0R_L3PEN0_Pos                           ( 0U )
#define ETH_MACL3L4C0R_L3PEN0_Msk                           ( 0x1UL << ETH_MACL3L4C0R_L3PEN0_Pos )
#define ETH_MACL3L4C0R_L3PEN0                               ( ETH_MACL3L4C0R_L3PEN0_Msk )


/***************  Bits definition for ETH_MACL4A0R  **********************/

#define ETH_MACL4A0R_L4DP0_Pos                              ( 16U )
#define ETH_MACL4A0R_L4DP0_Msk                              ( 0xFFFFUL << ETH_MACL4A0R_L4DP0_Pos )
#define ETH_MACL4A0R_L4DP0                                  ( ETH_MACL4A0R_L4DP0_Msk )

#define ETH_MACL4A0R_L4SP0_Pos                              ( 0U )
#define ETH_MACL4A0R_L4SP0_Msk                              ( 0xFFFFUL << ETH_MACL4A0R_L4SP0_Pos )
#define ETH_MACL4A0R_L4SP0                                  ( ETH_MACL4A0R_L4SP0_Msk )


/***************  Bits definition for ETH_MACL3A00R  **********************/

#define ETH_MACL3A00R_L3A00_Pos                             ( 0U )
#define ETH_MACL3A00R_L3A00_Msk                             ( 0xFFFFFFFFUL << ETH_MACL3A00R_L3A00_Pos )
#define ETH_MACL3A00R_L3A00                                 ( ETH_MACL3A00R_L3A00_Msk )


/***************  Bits definition for ETH_MACL3A10R  **********************/

#define ETH_MACL3A10R_L3A10_Pos                             ( 0U )
#define ETH_MACL3A10R_L3A10_Msk                             ( 0xFFFFFFFFUL << ETH_MACL3A10R_L3A10_Pos )
#define ETH_MACL3A10R_L3A10                                 ( ETH_MACL3A10R_L3A10_Msk )


/***************  Bits definition for ETH_MACL3A20R  **********************/

#define ETH_MACL3A20R_L3A20_Pos                             ( 0U )
#define ETH_MACL3A20R_L3A20_Msk                             ( 0xFFFFFFFFUL << ETH_MACL3A20R_L3A20_Pos )
#define ETH_MACL3A20R_L3A20                                 ( ETH_MACL3A20R_L3A20_Msk )


/***************  Bits definition for ETH_MACL3A30R  **********************/

#define ETH_MACL3A30R_L3A30_Pos                             ( 0U )
#define ETH_MACL3A30R_L3A30_Msk                             ( 0xFFFFFFFFUL << ETH_MACL3A30R_L3A30_Pos )
#define ETH_MACL3A30R_L3A30                                 ( ETH_MACL3A30R_L3A30_Msk )


/***************  Bits definition for ETH_MACL3L4C1R  **********************/

#define ETH_MACL3L4C1R_L4DPIM1_Pos                          ( 21U )
#define ETH_MACL3L4C1R_L4DPIM1_Msk                          ( 0x1UL << ETH_MACL3L4C1R_L4DPIM1_Pos )
#define ETH_MACL3L4C1R_L4DPIM1                              ( ETH_MACL3L4C1R_L4DPIM1_Msk )

#define ETH_MACL3L4C1R_L4DPM1_Pos                           ( 20U )
#define ETH_MACL3L4C1R_L4DPM1_Msk                           ( 0x1UL << ETH_MACL3L4C1R_L4DPM1_Pos )
#define ETH_MACL3L4C1R_L4DPM1                               ( ETH_MACL3L4C1R_L4DPM1_Msk )

#define ETH_MACL3L4C1R_L4SPIM1_Pos                          ( 19U )
#define ETH_MACL3L4C1R_L4SPIM1_Msk                          ( 0x1UL << ETH_MACL3L4C1R_L4SPIM1_Pos )
#define ETH_MACL3L4C1R_L4SPIM1                              ( ETH_MACL3L4C1R_L4SPIM1_Msk )

#define ETH_MACL3L4C1R_L4SPM1_Pos                           ( 18U )
#define ETH_MACL3L4C1R_L4SPM1_Msk                           ( 0x1UL << ETH_MACL3L4C1R_L4SPM1_Pos )
#define ETH_MACL3L4C1R_L4SPM1                               ( ETH_MACL3L4C1R_L4SPM1_Msk )

#define ETH_MACL3L4C1R_L4PEN1_Pos                           ( 16U )
#define ETH_MACL3L4C1R_L4PEN1_Msk                           ( 0x1UL << ETH_MACL3L4C1R_L4PEN1_Pos )
#define ETH_MACL3L4C1R_L4PEN1                               ( ETH_MACL3L4C1R_L4PEN1_Msk )

#define ETH_MACL3L4C1R_L3HDBM1_Pos                          ( 11U )
#define ETH_MACL3L4C1R_L3HDBM1_Msk                          ( 0x1FUL << ETH_MACL3L4C1R_L3HDBM1_Pos )
#define ETH_MACL3L4C1R_L3HDBM1                              ( ETH_MACL3L4C1R_L3HDBM1_Msk )
#define ETH_MACL3L4C1R_L3HDBM1_0                            ( 0x01UL << ETH_MACL3L4C1R_L3HDBM1_Pos )
#define ETH_MACL3L4C1R_L3HDBM1_1                            ( 0x02UL << ETH_MACL3L4C1R_L3HDBM1_Pos )
#define ETH_MACL3L4C1R_L3HDBM1_2                            ( 0x04UL << ETH_MACL3L4C1R_L3HDBM1_Pos )
#define ETH_MACL3L4C1R_L3HDBM1_3                            ( 0x08UL << ETH_MACL3L4C1R_L3HDBM1_Pos )
#define ETH_MACL3L4C1R_L3HDBM1_4                            ( 0x10UL << ETH_MACL3L4C1R_L3HDBM1_Pos )

#define ETH_MACL3L4C1R_L3HSBM1_Pos                          ( 6U )
#define ETH_MACL3L4C1R_L3HSBM1_Msk                          ( 0x1FUL << ETH_MACL3L4C1R_L3HSBM1_Pos )
#define ETH_MACL3L4C1R_L3HSBM1                              ( ETH_MACL3L4C1R_L3HSBM1_Msk )
#define ETH_MACL3L4C1R_L3HSBM1_0                            ( 0x01UL << ETH_MACL3L4C1R_L3HSBM1_Pos )
#define ETH_MACL3L4C1R_L3HSBM1_1                            ( 0x02UL << ETH_MACL3L4C1R_L3HSBM1_Pos )
#define ETH_MACL3L4C1R_L3HSBM1_2                            ( 0x04UL << ETH_MACL3L4C1R_L3HSBM1_Pos )
#define ETH_MACL3L4C1R_L3HSBM1_3                            ( 0x08UL << ETH_MACL3L4C1R_L3HSBM1_Pos )
#define ETH_MACL3L4C1R_L3HSBM1_4                            ( 0x10UL << ETH_MACL3L4C1R_L3HSBM1_Pos )

#define ETH_MACL3L4C1R_L3DAIM1_Pos                          ( 5U )
#define ETH_MACL3L4C1R_L3DAIM1_Msk                          ( 0x1UL << ETH_MACL3L4C1R_L3DAIM1_Pos )
#define ETH_MACL3L4C1R_L3DAIM1                              ( ETH_MACL3L4C1R_L3DAIM1_Msk )

#define ETH_MACL3L4C1R_L3DAM1_Pos                           ( 4U )
#define ETH_MACL3L4C1R_L3DAM1_Msk                           ( 0x1UL << ETH_MACL3L4C1R_L3DAM1_Pos )
#define ETH_MACL3L4C1R_L3DAM1                               ( ETH_MACL3L4C1R_L3DAM1_Msk )

#define ETH_MACL3L4C1R_L3SAIM1_Pos                          ( 3U )
#define ETH_MACL3L4C1R_L3SAIM1_Msk                          ( 0x1UL << ETH_MACL3L4C1R_L3SAIM1_Pos )
#define ETH_MACL3L4C1R_L3SAIM1                              ( ETH_MACL3L4C1R_L3SAIM1_Msk )

#define ETH_MACL3L4C1R_L3SAM1_Pos                           ( 2U )
#define ETH_MACL3L4C1R_L3SAM1_Msk                           ( 0x1UL << ETH_MACL3L4C1R_L3SAM1_Pos )
#define ETH_MACL3L4C1R_L3SAM1                               ( ETH_MACL3L4C1R_L3SAM1_Msk )

#define ETH_MACL3L4C1R_L3PEN1_Pos                           ( 0U )
#define ETH_MACL3L4C1R_L3PEN1_Msk                           ( 0x1UL << ETH_MACL3L4C1R_L3PEN1_Pos )
#define ETH_MACL3L4C1R_L3PEN1                               ( ETH_MACL3L4C1R_L3PEN1_Msk )


/***************  Bits definition for ETH_MACL4A1R  **********************/

#define ETH_MACL4A1R_L4DP1_Pos                              ( 16U )
#define ETH_MACL4A1R_L4DP1_Msk                              ( 0xFFFFUL << ETH_MACL4A1R_L4DP1_Pos )
#define ETH_MACL4A1R_L4DP1                                  ( ETH_MACL4A1R_L4DP1_Msk )

#define ETH_MACL4A1R_L4SP1_Pos                              ( 0U )
#define ETH_MACL4A1R_L4SP1_Msk                              ( 0xFFFFUL << ETH_MACL4A1R_L4SP1_Pos )
#define ETH_MACL4A1R_L4SP1                                  ( ETH_MACL4A1R_L4SP1_Msk )


/***************  Bits definition for ETH_MACL3A01R  **********************/

#define ETH_MACL3A01R_L3A01_Pos                             ( 0U )
#define ETH_MACL3A01R_L3A01_Msk                             ( 0xFFFFFFFFUL << ETH_MACL3A01R_L3A01_Pos )
#define ETH_MACL3A01R_L3A01                                 ( ETH_MACL3A01R_L3A01_Msk )


/***************  Bits definition for ETH_MACL3A11R  **********************/

#define ETH_MACL3A11R_L3A11_Pos                             ( 0U )
#define ETH_MACL3A11R_L3A11_Msk                             ( 0xFFFFFFFFUL << ETH_MACL3A11R_L3A11_Pos )
#define ETH_MACL3A11R_L3A11                                 ( ETH_MACL3A11R_L3A11_Msk )


/***************  Bits definition for ETH_MACL3A21R  **********************/

#define ETH_MACL3A21R_L3A21_Pos                             ( 0U )
#define ETH_MACL3A21R_L3A21_Msk                             ( 0xFFFFFFFFUL << ETH_MACL3A21R_L3A21_Pos )
#define ETH_MACL3A21R_L3A21                                 ( ETH_MACL3A21R_L3A21_Msk )


/***************  Bits definition for ETH_MACL3A31R  **********************/

#define ETH_MACL3A31R_L3A31_Pos                             ( 0U )
#define ETH_MACL3A31R_L3A31_Msk                             ( 0xFFFFFFFFUL << ETH_MACL3A31R_L3A31_Pos )
#define ETH_MACL3A31R_L3A31                                 ( ETH_MACL3A31R_L3A31_Msk )


/***************  Bits definition for ETH_MACVTIRR  **********************/

#define ETH_MACVTIRR_CSVL_Pos                               ( 19U )
#define ETH_MACVTIRR_CSVL_Msk                               ( 0x1UL << ETH_MACVTIRR_CSVL_Pos )
#define ETH_MACVTIRR_CSVL                                   ( ETH_MACVTIRR_CSVL_Msk )

#define ETH_MACVTIRR_VLP_Pos                                ( 18U )
#define ETH_MACVTIRR_VLP_Msk                                ( 0x1UL << ETH_MACVTIRR_VLP_Pos )
#define ETH_MACVTIRR_VLP                                    ( ETH_MACVTIRR_VLP_Msk )

#define ETH_MACVTIRR_VLC_Pos                                ( 16U )
#define ETH_MACVTIRR_VLC_Msk                                ( 0x3UL << ETH_MACVTIRR_VLC_Pos )
#define ETH_MACVTIRR_VLC                                    ( ETH_MACVTIRR_VLC_Msk )
#define ETH_MACVTIRR_VLC_0                                  ( 0x1UL << ETH_MACVTIRR_VLC_Pos )
#define ETH_MACVTIRR_VLC_1                                  ( 0x2UL << ETH_MACVTIRR_VLC_Pos )

#define ETH_MACVTIRR_VLT_Pos                                ( 0U )
#define ETH_MACVTIRR_VLT_Msk                                ( 0xFFFFUL << ETH_MACVTIRR_VLT_Pos )
#define ETH_MACVTIRR_VLT                                    ( ETH_MACVTIRR_VLT_Msk )


/***************  Bits definition for ETH_MACVHTR  **********************/

#define ETH_MACVHTR_CSVL_Pos                                ( 0U )
#define ETH_MACVHTR_CSVL_Msk                                ( 0xFFFFUL << ETH_MACVHTR_CSVL_Pos )
#define ETH_MACVHTR_CSVL                                    ( ETH_MACVHTR_CSVL_Msk )


/***************  Bits definition for ETH_PTPTSCR  **********************/

#define ETH_PTPTSCR_ASEN3_Pos                               ( 28U )
#define ETH_PTPTSCR_ASEN3_Msk                               ( 0x1UL << ETH_PTPTSCR_ASEN3_Pos )
#define ETH_PTPTSCR_ASEN3                                   ( ETH_PTPTSCR_ASEN3_Msk )

#define ETH_PTPTSCR_ASEN2_Pos                               ( 27U )
#define ETH_PTPTSCR_ASEN2_Msk                               ( 0x1UL << ETH_PTPTSCR_ASEN2_Pos )
#define ETH_PTPTSCR_ASEN2                                   ( ETH_PTPTSCR_ASEN2_Msk )

#define ETH_PTPTSCR_ASEN1_Pos                               ( 26U )
#define ETH_PTPTSCR_ASEN1_Msk                               ( 0x1UL << ETH_PTPTSCR_ASEN1_Pos )
#define ETH_PTPTSCR_ASEN1                                   ( ETH_PTPTSCR_ASEN1_Msk )

#define ETH_PTPTSCR_ASEN0_Pos                               ( 25U )
#define ETH_PTPTSCR_ASEN0_Msk                               ( 0x1UL << ETH_PTPTSCR_ASEN0_Pos )
#define ETH_PTPTSCR_ASEN0                                   ( ETH_PTPTSCR_ASEN0_Msk )

#define ETH_PTPTSCR_ASFC_Pos                                ( 24U )
#define ETH_PTPTSCR_ASFC_Msk                                ( 0x1UL << ETH_PTPTSCR_ASFC_Pos )
#define ETH_PTPTSCR_ASFC                                    ( ETH_PTPTSCR_ASFC_Msk )

#define ETH_PTPTSCR_EMAFPFF_Pos                             ( 18U )
#define ETH_PTPTSCR_EMAFPFF_Msk                             ( 0x1UL << ETH_PTPTSCR_EMAFPFF_Pos )
#define ETH_PTPTSCR_EMAFPFF                                 ( ETH_PTPTSCR_EMAFPFF_Msk )

#define ETH_PTPTSCR_SPPFTS_Pos                              ( 16U )
#define ETH_PTPTSCR_SPPFTS_Msk                              ( 0x3UL << ETH_PTPTSCR_SPPFTS_Pos )
#define ETH_PTPTSCR_SPPFTS                                  ( ETH_PTPTSCR_SPPFTS_Msk )
#define ETH_PTPTSCR_SPPFTS_0                                ( 0x1UL << ETH_PTPTSCR_SPPFTS_Pos )
#define ETH_PTPTSCR_SPPFTS_1                                ( 0x2UL << ETH_PTPTSCR_SPPFTS_Pos )

#define ETH_PTPTSCR_ESFMRTM_Pos                             ( 15U )
#define ETH_PTPTSCR_ESFMRTM_Msk                             ( 0x1UL << ETH_PTPTSCR_ESFMRTM_Pos )
#define ETH_PTPTSCR_ESFMRTM                                 ( ETH_PTPTSCR_ESFMRTM_Msk )

#define ETH_PTPTSCR_ETSFEM_Pos                              ( 14U )
#define ETH_PTPTSCR_ETSFEM_Msk                              ( 0x1UL << ETH_PTPTSCR_ETSFEM_Pos )
#define ETH_PTPTSCR_ETSFEM                                  ( ETH_PTPTSCR_ETSFEM_Msk )

#define ETH_PTPTSCR_EPPFSIP4U_Pos                           ( 13U )
#define ETH_PTPTSCR_EPPFSIP4U_Msk                           ( 0x1UL << ETH_PTPTSCR_EPPFSIP4U_Pos )
#define ETH_PTPTSCR_EPPFSIP4U                               ( ETH_PTPTSCR_EPPFSIP4U_Msk )

#define ETH_PTPTSCR_EPPFSIP6U_Pos                           ( 12U )
#define ETH_PTPTSCR_EPPFSIP6U_Msk                           ( 0x1UL << ETH_PTPTSCR_EPPFSIP6U_Pos )
#define ETH_PTPTSCR_EPPFSIP6U                               ( ETH_PTPTSCR_EPPFSIP6U_Msk )

#define ETH_PTPTSCR_EPPEF_Pos                               ( 11U )
#define ETH_PTPTSCR_EPPEF_Msk                               ( 0x1UL << ETH_PTPTSCR_EPPEF_Pos )
#define ETH_PTPTSCR_EPPEF                                   ( ETH_PTPTSCR_EPPEF_Msk )

#define ETH_PTPTSCR_TSPTPPSV2E_Pos                          ( 10U )
#define ETH_PTPTSCR_TSPTPPSV2E_Msk                          ( 0x1UL << ETH_PTPTSCR_TSPTPPSV2E_Pos )
#define ETH_PTPTSCR_TSPTPPSV2E                              ( ETH_PTPTSCR_TSPTPPSV2E_Msk )

#define ETH_PTPTSCR_TSR_Pos                                 ( 9U )
#define ETH_PTPTSCR_TSR_Msk                                 ( 0x1UL << ETH_PTPTSCR_TSR_Pos )
#define ETH_PTPTSCR_TSR                                     ( ETH_PTPTSCR_TSR_Msk )

#define ETH_PTPTSCR_TSARFE_Pos                              ( 8U )
#define ETH_PTPTSCR_TSARFE_Msk                              ( 0x1UL << ETH_PTPTSCR_TSARFE_Pos )
#define ETH_PTPTSCR_TSARFE                                  ( ETH_PTPTSCR_TSARFE_Msk )

#define ETH_PTPTSCR_TARU_Pos                                ( 5U )
#define ETH_PTPTSCR_TARU_Msk                                ( 0x1UL << ETH_PTPTSCR_TARU_Pos )
#define ETH_PTPTSCR_TARU                                    ( ETH_PTPTSCR_TARU_Msk )

#define ETH_PTPTSCR_TITE_Pos                                ( 4U )
#define ETH_PTPTSCR_TITE_Msk                                ( 0x1UL << ETH_PTPTSCR_TITE_Pos )
#define ETH_PTPTSCR_TITE                                    ( ETH_PTPTSCR_TITE_Msk )

#define ETH_PTPTSCR_TU_Pos                                  ( 3U )
#define ETH_PTPTSCR_TU_Msk                                  ( 0x1UL << ETH_PTPTSCR_TU_Pos )
#define ETH_PTPTSCR_TU                                      ( ETH_PTPTSCR_TU_Msk )

#define ETH_PTPTSCR_TI_Pos                                  ( 2U )
#define ETH_PTPTSCR_TI_Msk                                  ( 0x1UL << ETH_PTPTSCR_TI_Pos )
#define ETH_PTPTSCR_TI                                      ( ETH_PTPTSCR_TI_Msk )

#define ETH_PTPTSCR_TFCU_Pos                                ( 1U )
#define ETH_PTPTSCR_TFCU_Msk                                ( 0x1UL << ETH_PTPTSCR_TFCU_Pos )
#define ETH_PTPTSCR_TFCU                                    ( ETH_PTPTSCR_TFCU_Msk )

#define ETH_PTPTSCR_TE_Pos                                  ( 0U )
#define ETH_PTPTSCR_TE_Msk                                  ( 0x1UL << ETH_PTPTSCR_TE_Pos )
#define ETH_PTPTSCR_TE                                      ( ETH_PTPTSCR_TE_Msk )


/***************  Bits definition for ETH_PTPSSIR  **********************/

#define ETH_PTPSSIR_SSIV_Pos                                ( 0U )
#define ETH_PTPSSIR_SSIV_Msk                                ( 0xffUL << ETH_PTPSSIR_SSIV_Pos )
#define ETH_PTPSSIR_SSIV                                    ( ETH_PTPSSIR_SSIV_Msk )
#define ETH_PTPSSIR_SSIV_0                                  ( 0x1UL << ETH_PTPSSIR_SSIV_Pos )
#define ETH_PTPSSIR_SSIV_1                                  ( 0x2UL << ETH_PTPSSIR_SSIV_Pos )
#define ETH_PTPSSIR_SSIV_2                                  ( 0x4UL << ETH_PTPSSIR_SSIV_Pos )
#define ETH_PTPSSIR_SSIV_3                                  ( 0x8UL << ETH_PTPSSIR_SSIV_Pos )
#define ETH_PTPSSIR_SSIV_4                                  ( 0x10UL << ETH_PTPSSIR_SSIV_Pos )
#define ETH_PTPSSIR_SSIV_5                                  ( 0x20UL << ETH_PTPSSIR_SSIV_Pos )
#define ETH_PTPSSIR_SSIV_6                                  ( 0x40UL << ETH_PTPSSIR_SSIV_Pos )
#define ETH_PTPSSIR_SSIV_7                                  ( 0x80UL << ETH_PTPSSIR_SSIV_Pos )


/***************  Bits definition for ETH_PTPTSHR  **********************/

#define ETH_PTPTSHR_TS_Pos                                  ( 0U )
#define ETH_PTPTSHR_TS_Msk                                  ( 0xffffffffUL << ETH_PTPTSHR_TS_Pos )
#define ETH_PTPTSHR_TS                                      ( ETH_PTPTSHR_TS_Msk )


/***************  Bits definition for ETH_PTPTSLR  **********************/

#define ETH_PTPTSLR_TSS_Pos                                 ( 0U )
#define ETH_PTPTSLR_TSS_Msk                                 ( 0x7fffffffUL << ETH_PTPTSLR_TSS_Pos )
#define ETH_PTPTSLR_TSS                                     ( ETH_PTPTSLR_TSS_Msk )


/***************  Bits definition for ETH_PTPTSHUR  **********************/

#define ETH_PTPTSHUR_TSU_Pos                                ( 0U )
#define ETH_PTPTSHUR_TSU_Msk                                ( 0xffffffffUL << ETH_PTPTSHUR_TSU_Pos )
#define ETH_PTPTSHUR_TSU                                    ( ETH_PTPTSHUR_TSU_Msk )


/***************  Bits definition for ETH_PTPTSLUR  **********************/

#define ETH_PTPTSLUR_AST_Pos                                ( 31U )
#define ETH_PTPTSLUR_AST_Msk                                ( 0x1UL << ETH_PTPTSLUR_AST_Pos )
#define ETH_PTPTSLUR_AST                                    ( ETH_PTPTSLUR_AST_Msk )

#define ETH_PTPTSLUR_TSSU_Pos                               ( 0U )
#define ETH_PTPTSLUR_TSSU_Msk                               ( 0x7fffffffUL << ETH_PTPTSLUR_TSSU_Pos )
#define ETH_PTPTSLUR_TSSU                                   ( ETH_PTPTSLUR_TSSU_Msk )


/***************  Bits definition for ETH_PTPTSAR  **********************/

#define ETH_PTPTSAR_TAR_Pos                                 ( 0U )
#define ETH_PTPTSAR_TAR_Msk                                 ( 0xffffffffUL << ETH_PTPTSAR_TAR_Pos )
#define ETH_PTPTSAR_TAR                                     ( ETH_PTPTSAR_TAR_Msk )


/***************  Bits definition for ETH_PTPTTHR  **********************/

#define ETH_PTPTTHR_TTSR_Pos                                ( 0U )
#define ETH_PTPTTHR_TTSR_Msk                                ( 0xffffffffUL << ETH_PTPTTHR_TTSR_Pos )
#define ETH_PTPTTHR_TTSR                                    ( ETH_PTPTTHR_TTSR_Msk )


/***************  Bits definition for ETH_PTPTTLR  **********************/

#define ETH_PTPTTLR_TTRB_Pos                                ( 31U )
#define ETH_PTPTTLR_TTRB_Msk                                ( 0x1UL << ETH_PTPTTLR_TTRB_Pos )
#define ETH_PTPTTLR_TTRB                                    ( ETH_PTPTTLR_TTRB_Msk )

#define ETH_PTPTTLR_TTLR_Pos                                ( 0U )
#define ETH_PTPTTLR_TTLR_Msk                                ( 0x7fffffffUL << ETH_PTPTTLR_TTLR_Pos )
#define ETH_PTPTTLR_TTLR                                    ( ETH_PTPTTLR_TTLR_Msk )


/***************  Bits definition for ETH_PTPTSSR  **********************/

#define ETH_PTPTSSR_ATSNS_Pos                               ( 25U )
#define ETH_PTPTSSR_ATSNS_Msk                               ( 0x7UL << ETH_PTPTSSR_ATSNS_Pos )
#define ETH_PTPTSSR_ATSNS                                   ( ETH_PTPTSSR_ATSNS_Msk )

#define ETH_PTPTSSR_ATSTM_Pos                               ( 24U )
#define ETH_PTPTSSR_ATSTM_Msk                               ( 0x1UL << ETH_PTPTSSR_ATSTM_Pos )
#define ETH_PTPTSSR_ATSTM                                   ( ETH_PTPTSSR_ATSTM_Msk )

#define ETH_PTPTSSR_ATSTI_Pos                               ( 16U )
#define ETH_PTPTSSR_ATSTI_Msk                               ( 0xFUL << ETH_PTPTSSR_ATSTI_Pos )
#define ETH_PTPTSSR_ATSTI                                   ( ETH_PTPTSSR_ATSTI_Msk )
#define ETH_PTPTSSR_ATSTI_0                                 ( 0x1UL << ETH_PTPTSSR_ATSTI_Pos )
#define ETH_PTPTSSR_ATSTI_1                                 ( 0x2UL << ETH_PTPTSSR_ATSTI_Pos )
#define ETH_PTPTSSR_ATSTI_2                                 ( 0x4UL << ETH_PTPTSSR_ATSTI_Pos )
#define ETH_PTPTSSR_ATSTI_3                                 ( 0x8UL << ETH_PTPTSSR_ATSTI_Pos )

#define ETH_PTPTSSR_TTTE_Pos                                ( 3U )
#define ETH_PTPTSSR_TTTE_Msk                                ( 0x1UL << ETH_PTPTSSR_TTTE_Pos )
#define ETH_PTPTSSR_TTTE                                    ( ETH_PTPTSSR_TTTE_Msk )

#define ETH_PTPTSSR_ATTS_Pos                                ( 2U )
#define ETH_PTPTSSR_ATTS_Msk                                ( 0x1UL << ETH_PTPTSSR_ATTS_Pos )
#define ETH_PTPTSSR_ATTS                                    ( ETH_PTPTSSR_ATTS_Msk )

#define ETH_PTPTSSR_TTTR_Pos                                ( 1U )
#define ETH_PTPTSSR_TTTR_Msk                                ( 0x1UL << ETH_PTPTSSR_TTTR_Pos )
#define ETH_PTPTSSR_TTTR                                    ( ETH_PTPTSSR_TTTR_Msk )

#define ETH_PTPTSSR_TSO_Pos                                 ( 0U )
#define ETH_PTPTSSR_TSO_Msk                                 ( 0x1UL << ETH_PTPTSSR_TSO_Pos )
#define ETH_PTPTSSR_TSO                                     ( ETH_PTPTSSR_TSO_Msk )


/***************  Bits definition for ETH_PTPPPSCR  **********************/

#define ETH_PTPPPSCR_TRGTMODSEL_Pos                         ( 5U )
#define ETH_PTPPPSCR_TRGTMODSEL_Msk                         ( 0x3UL << ETH_PTPPPSCR_TRGTMODSEL_Pos )
#define ETH_PTPPPSCR_TRGTMODSEL                             ( ETH_PTPPPSCR_TRGTMODSEL_Msk )
#define ETH_PTPPPSCR_TRGTMODSEL_0                           ( 0x1UL << ETH_PTPPPSCR_TRGTMODSEL_Pos )
#define ETH_PTPPPSCR_TRGTMODSEL_1                           ( 0x2UL << ETH_PTPPPSCR_TRGTMODSEL_Pos )

#define ETH_PTPPPSCR_PPSEN_Pos                              ( 4U )
#define ETH_PTPPPSCR_PPSEN_Msk                              ( 0x1UL << ETH_PTPPPSCR_PPSEN_Pos )
#define ETH_PTPPPSCR_PPSEN                                  ( ETH_PTPPPSCR_PPSEN_Msk )

#define ETH_PTPPPSCR_PPSCTRL_Pos                            ( 0U )
#define ETH_PTPPPSCR_PPSCTRL_Msk                            ( 0xfUL << ETH_PTPPPSCR_PPSCTRL_Pos )
#define ETH_PTPPPSCR_PPSCTRL                                ( ETH_PTPPPSCR_PPSCTRL_Msk )
#define ETH_PTPPPSCR_PPSCTRL_0                              ( 0x1UL << ETH_PTPPPSCR_PPSCTRL_Pos )
#define ETH_PTPPPSCR_PPSCTRL_1                              ( 0x2UL << ETH_PTPPPSCR_PPSCTRL_Pos )
#define ETH_PTPPPSCR_PPSCTRL_2                              ( 0x4UL << ETH_PTPPPSCR_PPSCTRL_Pos )
#define ETH_PTPPPSCR_PPSCTRL_3                              ( 0x8UL << ETH_PTPPPSCR_PPSCTRL_Pos )

#define ETH_PTPPPSCR_PPSCMD_Pos                             ( 0U )
#define ETH_PTPPPSCR_PPSCMD_Msk                             ( 0xfUL << ETH_PTPPPSCR_PPSCMD_Pos )
#define ETH_PTPPPSCR_PPSCMD                                 ( ETH_PTPPPSCR_PPSCMD_Msk )
#define ETH_PTPPPSCR_PPSCMD_0                               ( 0x1UL << ETH_PTPPPSCR_PPSCMD_Pos )
#define ETH_PTPPPSCR_PPSCMD_1                               ( 0x2UL << ETH_PTPPPSCR_PPSCMD_Pos )
#define ETH_PTPPPSCR_PPSCMD_2                               ( 0x4UL << ETH_PTPPPSCR_PPSCMD_Pos )
#define ETH_PTPPPSCR_PPSCMD_3                               ( 0x8UL << ETH_PTPPPSCR_PPSCMD_Pos )


/***************  Bits definition for ETH_PTPATSNR  **********************/

#define ETH_PTPATSNR_AUSTSLO_Pos                            ( 0U )
#define ETH_PTPATSNR_AUSTSLO_Msk                            ( 0x7fffffffUL << ETH_PTPATSNR_AUSTSLO_Pos )
#define ETH_PTPATSNR_AUSTSLO                                ( ETH_PTPATSNR_AUSTSLO_Msk )


/***************  Bits definition for ETH_PTPATSSR  **********************/

#define ETH_PTPATSSR_AUSTSHI_Pos                            ( 0U )
#define ETH_PTPATSSR_AUSTSHI_Msk                            ( 0x7fffffffUL << ETH_PTPATSSR_AUSTSHI_Pos )
#define ETH_PTPATSSR_AUSTSHI                                ( ETH_PTPATSSR_AUSTSHI_Msk )


/***************  Bits definition for ETH_PTPPPSIR  **********************/

#define ETH_PTPPPSIR_PPSINT_Pos                             ( 0U )
#define ETH_PTPPPSIR_PPSINT_Msk                             ( 0xffffffffUL << ETH_PTPPPSIR_PPSINT_Pos )
#define ETH_PTPPPSIR_PPSINT                                 ( ETH_PTPPPSIR_PPSINT_Msk )


/***************  Bits definition for ETH_PTPPPSWR  **********************/

#define ETH_PTPPPSWR_PPSWIDTH_Pos                           ( 0U )
#define ETH_PTPPPSWR_PPSWIDTH_Msk                           ( 0xffffffffUL << ETH_PTPPPSWR_PPSWIDTH_Pos )
#define ETH_PTPPPSWR_PPSWIDTH                               ( ETH_PTPPPSWR_PPSWIDTH_Msk )


/***************  Bits definition for ETH_DMABMR  **********************/

#define ETH_DMABMR_RIB_Pos                                  ( 31U )
#define ETH_DMABMR_RIB_Msk                                  ( 0x1UL << ETH_DMABMR_RIB_Pos )
#define ETH_DMABMR_RIB                                      ( ETH_DMABMR_RIB_Msk )

#define ETH_DMABMR_TXPR_Pos                                 ( 27U )
#define ETH_DMABMR_TXPR_Msk                                 ( 0x1UL << ETH_DMABMR_TXPR_Pos )
#define ETH_DMABMR_TXPR                                     ( ETH_DMABMR_TXPR_Msk )

#define ETH_DMABMR_MB_Pos                                   ( 26U )
#define ETH_DMABMR_MB_Msk                                   ( 0x1UL << ETH_DMABMR_MB_Pos )
#define ETH_DMABMR_MB                                       ( ETH_DMABMR_MB_Msk )

#define ETH_DMABMR_AAB_Pos                                  ( 25U )
#define ETH_DMABMR_AAB_Msk                                  ( 0x1UL << ETH_DMABMR_AAB_Pos )
#define ETH_DMABMR_AAB                                      ( ETH_DMABMR_AAB_Msk )

#define ETH_DMABMR_EPM_Pos                                  ( 24U )
#define ETH_DMABMR_EPM_Msk                                  ( 0x1UL << ETH_DMABMR_EPM_Pos )
#define ETH_DMABMR_EPM                                      ( ETH_DMABMR_EPM_Msk )

#define ETH_DMABMR_USP_Pos                                  ( 23U )
#define ETH_DMABMR_USP_Msk                                  ( 0x1UL << ETH_DMABMR_USP_Pos )
#define ETH_DMABMR_USP                                      ( ETH_DMABMR_USP_Msk )

#define ETH_DMABMR_RDP_Pos                                  ( 17U )
#define ETH_DMABMR_RDP_Msk                                  ( 0x3fUL << ETH_DMABMR_RDP_Pos )
#define ETH_DMABMR_RDP                                      ( ETH_DMABMR_RDP_Msk )
#define ETH_DMABMR_RDP_0                                    ( 0x1UL << ETH_DMABMR_RDP_Pos )
#define ETH_DMABMR_RDP_1                                    ( 0x2UL << ETH_DMABMR_RDP_Pos )
#define ETH_DMABMR_RDP_2                                    ( 0x4UL << ETH_DMABMR_RDP_Pos )
#define ETH_DMABMR_RDP_3                                    ( 0x8UL << ETH_DMABMR_RDP_Pos )
#define ETH_DMABMR_RDP_4                                    ( 0x10UL << ETH_DMABMR_RDP_Pos )
#define ETH_DMABMR_RDP_5                                    ( 0x20UL << ETH_DMABMR_RDP_Pos )

#define ETH_DMABMR_FB_Pos                                   ( 16U )
#define ETH_DMABMR_FB_Msk                                   ( 0x1UL << ETH_DMABMR_FB_Pos )
#define ETH_DMABMR_FB                                       ( ETH_DMABMR_FB_Msk )

#define ETH_DMABMR_PM_Pos                                   ( 14U )
#define ETH_DMABMR_PM_Msk                                   ( 0x3UL << ETH_DMABMR_PM_Pos )
#define ETH_DMABMR_PM                                       ( ETH_DMABMR_PM_Msk )
#define ETH_DMABMR_PM_0                                     ( 0x1UL << ETH_DMABMR_PM_Pos )
#define ETH_DMABMR_PM_1                                     ( 0x2UL << ETH_DMABMR_PM_Pos )

#define ETH_DMABMR_PBL_Pos                                  ( 8U )
#define ETH_DMABMR_PBL_Msk                                  ( 0x3fUL << ETH_DMABMR_PBL_Pos )
#define ETH_DMABMR_PBL                                      ( ETH_DMABMR_PBL_Msk )
#define ETH_DMABMR_PBL_0                                    ( 0x1UL << ETH_DMABMR_PBL_Pos )
#define ETH_DMABMR_PBL_1                                    ( 0x2UL << ETH_DMABMR_PBL_Pos )
#define ETH_DMABMR_PBL_2                                    ( 0x4UL << ETH_DMABMR_PBL_Pos )
#define ETH_DMABMR_PBL_3                                    ( 0x8UL << ETH_DMABMR_PBL_Pos )
#define ETH_DMABMR_PBL_4                                    ( 0x10UL << ETH_DMABMR_PBL_Pos )
#define ETH_DMABMR_PBL_5                                    ( 0x20UL << ETH_DMABMR_PBL_Pos )

#define ETH_DMABMR_EDFE_Pos                                 ( 7U )
#define ETH_DMABMR_EDFE_Msk                                 ( 0x1UL << ETH_DMABMR_EDFE_Pos )
#define ETH_DMABMR_EDFE                                     ( ETH_DMABMR_EDFE_Msk )

#define ETH_DMABMR_DSL_Pos                                  ( 2U )
#define ETH_DMABMR_DSL_Msk                                  ( 0x1fUL << ETH_DMABMR_DSL_Pos )
#define ETH_DMABMR_DSL                                      ( ETH_DMABMR_DSL_Msk )
#define ETH_DMABMR_DSL_0                                    ( 0x1UL << ETH_DMABMR_DSL_Pos )
#define ETH_DMABMR_DSL_1                                    ( 0x2UL << ETH_DMABMR_DSL_Pos )
#define ETH_DMABMR_DSL_2                                    ( 0x4UL << ETH_DMABMR_DSL_Pos )
#define ETH_DMABMR_DSL_3                                    ( 0x8UL << ETH_DMABMR_DSL_Pos )
#define ETH_DMABMR_DSL_4                                    ( 0x10UL << ETH_DMABMR_DSL_Pos )

#define ETH_DMABMR_DA_Pos                                   ( 1U )
#define ETH_DMABMR_DA_Msk                                   ( 0x1UL << ETH_DMABMR_DA_Pos )
#define ETH_DMABMR_DA                                       ( ETH_DMABMR_DA_Msk )

#define ETH_DMABMR_SWR_Pos                                  ( 0U )
#define ETH_DMABMR_SWR_Msk                                  ( 0x1UL << ETH_DMABMR_SWR_Pos )
#define ETH_DMABMR_SWR                                      ( ETH_DMABMR_SWR_Msk )


/***************  Bits definition for ETH_DMATPDR  **********************/

#define ETH_DMATPDR_TPD_Pos                                 ( 0U )
#define ETH_DMATPDR_TPD_Msk                                 ( 0xffffffffUL << ETH_DMATPDR_TPD_Pos )
#define ETH_DMATPDR_TPD                                     ( ETH_DMATPDR_TPD_Msk )


/***************  Bits definition for ETH_DMARPDR  **********************/

#define ETH_DMARPDR_RPD_Pos                                 ( 0U )
#define ETH_DMARPDR_RPD_Msk                                 ( 0xffffffffUL << ETH_DMARPDR_RPD_Pos )
#define ETH_DMARPDR_RPD                                     ( ETH_DMARPDR_RPD_Msk )


/***************  Bits definition for ETH_DMARDLAR  **********************/

#define ETH_DMARDLAR_SRL_Pos                                ( 0U )
#define ETH_DMARDLAR_SRL_Msk                                ( 0xffffffffUL << ETH_DMARDLAR_SRL_Pos )
#define ETH_DMARDLAR_SRL                                    ( ETH_DMARDLAR_SRL_Msk )


/***************  Bits definition for ETH_DMATDLAR  **********************/

#define ETH_DMATDLAR_STL_Pos                                ( 0U )
#define ETH_DMATDLAR_STL_Msk                                ( 0xffffffffUL << ETH_DMATDLAR_STL_Pos )
#define ETH_DMATDLAR_STL                                    ( ETH_DMATDLAR_STL_Msk )


/***************  Bits definition for ETH_DMASR  **********************/

#define ETH_DMASR_LPIS_Pos                                  ( 30U )
#define ETH_DMASR_LPIS_Msk                                  ( 0x1UL << ETH_DMASR_LPIS_Pos )
#define ETH_DMASR_LPIS                                      ( ETH_DMASR_LPIS_Msk )

#define ETH_DMASR_TSTS_Pos                                  ( 29U )
#define ETH_DMASR_TSTS_Msk                                  ( 0x1UL << ETH_DMASR_TSTS_Pos )
#define ETH_DMASR_TSTS                                      ( ETH_DMASR_TSTS_Msk )

#define ETH_DMASR_PMTS_Pos                                  ( 28U )
#define ETH_DMASR_PMTS_Msk                                  ( 0x1UL << ETH_DMASR_PMTS_Pos )
#define ETH_DMASR_PMTS                                      ( ETH_DMASR_PMTS_Msk )

#define ETH_DMASR_MMCS_Pos                                  ( 27U )
#define ETH_DMASR_MMCS_Msk                                  ( 0x1UL << ETH_DMASR_MMCS_Pos )
#define ETH_DMASR_MMCS                                      ( ETH_DMASR_MMCS_Msk )

#define ETH_DMASR_EBS_Pos                                   ( 23U )
#define ETH_DMASR_EBS_Msk                                   ( 0x7UL << ETH_DMASR_EBS_Pos )
#define ETH_DMASR_EBS                                       ( ETH_DMASR_EBS_Msk )
#define ETH_DMASR_EBS_0                                     ( 0x1UL << ETH_DMASR_EBS_Pos )
#define ETH_DMASR_EBS_1                                     ( 0x2UL << ETH_DMASR_EBS_Pos )
#define ETH_DMASR_EBS_2                                     ( 0x4UL << ETH_DMASR_EBS_Pos )

#define ETH_DMASR_TPS_Pos                                   ( 20U )
#define ETH_DMASR_TPS_Msk                                   ( 0x7UL << ETH_DMASR_TPS_Pos )
#define ETH_DMASR_TPS                                       ( ETH_DMASR_TPS_Msk )
#define ETH_DMASR_TPS_0                                     ( 0x1UL << ETH_DMASR_TPS_Pos )
#define ETH_DMASR_TPS_1                                     ( 0x2UL << ETH_DMASR_TPS_Pos )
#define ETH_DMASR_TPS_2                                     ( 0x4UL << ETH_DMASR_TPS_Pos )

#define ETH_DMASR_RPS_Pos                                   ( 17U )
#define ETH_DMASR_RPS_Msk                                   ( 0x7UL << ETH_DMASR_RPS_Pos )
#define ETH_DMASR_RPS                                       ( ETH_DMASR_RPS_Msk )
#define ETH_DMASR_RPS_0                                     ( 0x1UL << ETH_DMASR_RPS_Pos )
#define ETH_DMASR_RPS_1                                     ( 0x2UL << ETH_DMASR_RPS_Pos )
#define ETH_DMASR_RPS_2                                     ( 0x4UL << ETH_DMASR_RPS_Pos )

#define ETH_DMASR_NIS_Pos                                   ( 16U )
#define ETH_DMASR_NIS_Msk                                   ( 0x1UL << ETH_DMASR_NIS_Pos )
#define ETH_DMASR_NIS                                       ( ETH_DMASR_NIS_Msk )

#define ETH_DMASR_AIS_Pos                                   ( 15U )
#define ETH_DMASR_AIS_Msk                                   ( 0x1UL << ETH_DMASR_AIS_Pos )
#define ETH_DMASR_AIS                                       ( ETH_DMASR_AIS_Msk )

#define ETH_DMASR_ERS_Pos                                   ( 14U )
#define ETH_DMASR_ERS_Msk                                   ( 0x1UL << ETH_DMASR_ERS_Pos )
#define ETH_DMASR_ERS                                       ( ETH_DMASR_ERS_Msk )

#define ETH_DMASR_FBES_Pos                                  ( 13U )
#define ETH_DMASR_FBES_Msk                                  ( 0x1UL << ETH_DMASR_FBES_Pos )
#define ETH_DMASR_FBES                                      ( ETH_DMASR_FBES_Msk )

#define ETH_DMASR_ETS_Pos                                   ( 10U )
#define ETH_DMASR_ETS_Msk                                   ( 0x1UL << ETH_DMASR_ETS_Pos )
#define ETH_DMASR_ETS                                       ( ETH_DMASR_ETS_Msk )

#define ETH_DMASR_RWTS_Pos                                  ( 9U )
#define ETH_DMASR_RWTS_Msk                                  ( 0x1UL << ETH_DMASR_RWTS_Pos )
#define ETH_DMASR_RWTS                                      ( ETH_DMASR_RWTS_Msk )

#define ETH_DMASR_RPSS_Pos                                  ( 8U )
#define ETH_DMASR_RPSS_Msk                                  ( 0x1UL << ETH_DMASR_RPSS_Pos )
#define ETH_DMASR_RPSS                                      ( ETH_DMASR_RPSS_Msk )

#define ETH_DMASR_RBUS_Pos                                  ( 7U )
#define ETH_DMASR_RBUS_Msk                                  ( 0x1UL << ETH_DMASR_RBUS_Pos )
#define ETH_DMASR_RBUS                                      ( ETH_DMASR_RBUS_Msk )

#define ETH_DMASR_RS_Pos                                    ( 6U )
#define ETH_DMASR_RS_Msk                                    ( 0x1UL << ETH_DMASR_RS_Pos )
#define ETH_DMASR_RS                                        ( ETH_DMASR_RS_Msk )

#define ETH_DMASR_TUS_Pos                                   ( 5U )
#define ETH_DMASR_TUS_Msk                                   ( 0x1UL << ETH_DMASR_TUS_Pos )
#define ETH_DMASR_TUS                                       ( ETH_DMASR_TUS_Msk )

#define ETH_DMASR_ROS_Pos                                   ( 4U )
#define ETH_DMASR_ROS_Msk                                   ( 0x1UL << ETH_DMASR_ROS_Pos )
#define ETH_DMASR_ROS                                       ( ETH_DMASR_ROS_Msk )

#define ETH_DMASR_TJTS_Pos                                  ( 3U )
#define ETH_DMASR_TJTS_Msk                                  ( 0x1UL << ETH_DMASR_TJTS_Pos )
#define ETH_DMASR_TJTS                                      ( ETH_DMASR_TJTS_Msk )

#define ETH_DMASR_TBUS_Pos                                  ( 2U )
#define ETH_DMASR_TBUS_Msk                                  ( 0x1UL << ETH_DMASR_TBUS_Pos )
#define ETH_DMASR_TBUS                                      ( ETH_DMASR_TBUS_Msk )

#define ETH_DMASR_TPSS_Pos                                  ( 1U )
#define ETH_DMASR_TPSS_Msk                                  ( 0x1UL << ETH_DMASR_TPSS_Pos )
#define ETH_DMASR_TPSS                                      ( ETH_DMASR_TPSS_Msk )

#define ETH_DMASR_TS_Pos                                    ( 0U )
#define ETH_DMASR_TS_Msk                                    ( 0x1UL << ETH_DMASR_TS_Pos )
#define ETH_DMASR_TS                                        ( ETH_DMASR_TS_Msk )


/***************  Bits definition for ETH_DMAOMR  **********************/

#define ETH_DMAOMR_DTCEFD_Pos                               ( 26U )
#define ETH_DMAOMR_DTCEFD_Msk                               ( 0x1UL << ETH_DMAOMR_DTCEFD_Pos )
#define ETH_DMAOMR_DTCEFD                                   ( ETH_DMAOMR_DTCEFD_Msk )

#define ETH_DMAOMR_RSF_Pos                                  ( 25U )
#define ETH_DMAOMR_RSF_Msk                                  ( 0x1UL << ETH_DMAOMR_RSF_Pos )
#define ETH_DMAOMR_RSF                                      ( ETH_DMAOMR_RSF_Msk )

#define ETH_DMAOMR_DFRF_Pos                                 ( 24U )
#define ETH_DMAOMR_DFRF_Msk                                 ( 0x1UL << ETH_DMAOMR_DFRF_Pos )
#define ETH_DMAOMR_DFRF                                     ( ETH_DMAOMR_DFRF_Msk )

#define ETH_DMAOMR_TSF_Pos                                  ( 21U )
#define ETH_DMAOMR_TSF_Msk                                  ( 0x1UL << ETH_DMAOMR_TSF_Pos )
#define ETH_DMAOMR_TSF                                      ( ETH_DMAOMR_TSF_Msk )

#define ETH_DMAOMR_FTF_Pos                                  ( 20U )
#define ETH_DMAOMR_FTF_Msk                                  ( 0x1UL << ETH_DMAOMR_FTF_Pos )
#define ETH_DMAOMR_FTF                                      ( ETH_DMAOMR_FTF_Msk )

#define ETH_DMAOMR_TTC_Pos                                  ( 14U )
#define ETH_DMAOMR_TTC_Msk                                  ( 0x7UL << ETH_DMAOMR_TTC_Pos )
#define ETH_DMAOMR_TTC                                      ( ETH_DMAOMR_TTC_Msk )
#define ETH_DMAOMR_TTC_0                                    ( 0x1UL << ETH_DMAOMR_TTC_Pos )
#define ETH_DMAOMR_TTC_1                                    ( 0x2UL << ETH_DMAOMR_TTC_Pos )
#define ETH_DMAOMR_TTC_2                                    ( 0x4UL << ETH_DMAOMR_TTC_Pos )

#define ETH_DMAOMR_ST_Pos                                   ( 13U )
#define ETH_DMAOMR_ST_Msk                                   ( 0x1UL << ETH_DMAOMR_ST_Pos )
#define ETH_DMAOMR_ST                                       ( ETH_DMAOMR_ST_Msk )

#define ETH_DMAOMR_FEF_Pos                                  ( 7U )
#define ETH_DMAOMR_FEF_Msk                                  ( 0x1UL << ETH_DMAOMR_FEF_Pos )
#define ETH_DMAOMR_FEF                                      ( ETH_DMAOMR_FEF_Msk )

#define ETH_DMAOMR_FUGF_Pos                                 ( 6U )
#define ETH_DMAOMR_FUGF_Msk                                 ( 0x1UL << ETH_DMAOMR_FUGF_Pos )
#define ETH_DMAOMR_FUGF                                     ( ETH_DMAOMR_FUGF_Msk )

#define ETH_DMAOMR_DGF_Pos                                  ( 5U )
#define ETH_DMAOMR_DGF_Msk                                  ( 0x1UL << ETH_DMAOMR_DGF_Pos )
#define ETH_DMAOMR_DGF                                      ( ETH_DMAOMR_DGF_Msk )

#define ETH_DMAOMR_RTC_Pos                                  ( 3U )
#define ETH_DMAOMR_RTC_Msk                                  ( 0x3UL << ETH_DMAOMR_RTC_Pos )
#define ETH_DMAOMR_RTC                                      ( ETH_DMAOMR_RTC_Msk )
#define ETH_DMAOMR_RTC_0                                    ( 0x1UL << ETH_DMAOMR_RTC_Pos )
#define ETH_DMAOMR_RTC_1                                    ( 0x2UL << ETH_DMAOMR_RTC_Pos )

#define ETH_DMAOMR_OSF_Pos                                  ( 2U )
#define ETH_DMAOMR_OSF_Msk                                  ( 0x1UL << ETH_DMAOMR_OSF_Pos )
#define ETH_DMAOMR_OSF                                      ( ETH_DMAOMR_OSF_Msk )

#define ETH_DMAOMR_SR_Pos                                   ( 1U )
#define ETH_DMAOMR_SR_Msk                                   ( 0x1UL << ETH_DMAOMR_SR_Pos )
#define ETH_DMAOMR_SR                                       ( ETH_DMAOMR_SR_Msk )


/***************  Bits definition for ETH_DMAIER  **********************/

#define ETH_DMAIER_NISE_Pos                                 ( 16U )
#define ETH_DMAIER_NISE_Msk                                 ( 0x1UL << ETH_DMAIER_NISE_Pos )
#define ETH_DMAIER_NISE                                     ( ETH_DMAIER_NISE_Msk )

#define ETH_DMAIER_AISE_Pos                                 ( 15U )
#define ETH_DMAIER_AISE_Msk                                 ( 0x1UL << ETH_DMAIER_AISE_Pos )
#define ETH_DMAIER_AISE                                     ( ETH_DMAIER_AISE_Msk )

#define ETH_DMAIER_ERIE_Pos                                 ( 14U )
#define ETH_DMAIER_ERIE_Msk                                 ( 0x1UL << ETH_DMAIER_ERIE_Pos )
#define ETH_DMAIER_ERIE                                     ( ETH_DMAIER_ERIE_Msk )

#define ETH_DMAIER_FBEIE_Pos                                ( 13U )
#define ETH_DMAIER_FBEIE_Msk                                ( 0x1UL << ETH_DMAIER_FBEIE_Pos )
#define ETH_DMAIER_FBEIE                                    ( ETH_DMAIER_FBEIE_Msk )

#define ETH_DMAIER_ETIE_Pos                                 ( 10U )
#define ETH_DMAIER_ETIE_Msk                                 ( 0x1UL << ETH_DMAIER_ETIE_Pos )
#define ETH_DMAIER_ETIE                                     ( ETH_DMAIER_ETIE_Msk )

#define ETH_DMAIER_RWTIE_Pos                                ( 9U )
#define ETH_DMAIER_RWTIE_Msk                                ( 0x1UL << ETH_DMAIER_RWTIE_Pos )
#define ETH_DMAIER_RWTIE                                    ( ETH_DMAIER_RWTIE_Msk )

#define ETH_DMAIER_RPSIE_Pos                                ( 8U )
#define ETH_DMAIER_RPSIE_Msk                                ( 0x1UL << ETH_DMAIER_RPSIE_Pos )
#define ETH_DMAIER_RPSIE                                    ( ETH_DMAIER_RPSIE_Msk )

#define ETH_DMAIER_RBUIE_Pos                                ( 7U )
#define ETH_DMAIER_RBUIE_Msk                                ( 0x1UL << ETH_DMAIER_RBUIE_Pos )
#define ETH_DMAIER_RBUIE                                    ( ETH_DMAIER_RBUIE_Msk )

#define ETH_DMAIER_RIE_Pos                                  ( 6U )
#define ETH_DMAIER_RIE_Msk                                  ( 0x1UL << ETH_DMAIER_RIE_Pos )
#define ETH_DMAIER_RIE                                      ( ETH_DMAIER_RIE_Msk )

#define ETH_DMAIER_TUIE_Pos                                 ( 5U )
#define ETH_DMAIER_TUIE_Msk                                 ( 0x1UL << ETH_DMAIER_TUIE_Pos )
#define ETH_DMAIER_TUIE                                     ( ETH_DMAIER_TUIE_Msk )

#define ETH_DMAIER_ROIE_Pos                                 ( 4U )
#define ETH_DMAIER_ROIE_Msk                                 ( 0x1UL << ETH_DMAIER_ROIE_Pos )
#define ETH_DMAIER_ROIE                                     ( ETH_DMAIER_ROIE_Msk )

#define ETH_DMAIER_TJTIE_Pos                                ( 3U )
#define ETH_DMAIER_TJTIE_Msk                                ( 0x1UL << ETH_DMAIER_TJTIE_Pos )
#define ETH_DMAIER_TJTIE                                    ( ETH_DMAIER_TJTIE_Msk )

#define ETH_DMAIER_TBUIE_Pos                                ( 2U )
#define ETH_DMAIER_TBUIE_Msk                                ( 0x1UL << ETH_DMAIER_TBUIE_Pos )
#define ETH_DMAIER_TBUIE                                    ( ETH_DMAIER_TBUIE_Msk )

#define ETH_DMAIER_TPSIE_Pos                                ( 1U )
#define ETH_DMAIER_TPSIE_Msk                                ( 0x1UL << ETH_DMAIER_TPSIE_Pos )
#define ETH_DMAIER_TPSIE                                    ( ETH_DMAIER_TPSIE_Msk )

#define ETH_DMAIER_TIE_Pos                                  ( 0U )
#define ETH_DMAIER_TIE_Msk                                  ( 0x1UL << ETH_DMAIER_TIE_Pos )
#define ETH_DMAIER_TIE                                      ( ETH_DMAIER_TIE_Msk )


/***************  Bits definition for ETH_DMAMFBOCR  **********************/

#define ETH_DMAMFBOCR_OBFOC_Pos                             ( 28U )
#define ETH_DMAMFBOCR_OBFOC_Msk                             ( 0x1UL << ETH_DMAMFBOCR_OBFOC_Pos )
#define ETH_DMAMFBOCR_OBFOC                                 ( ETH_DMAMFBOCR_OBFOC_Msk )

#define ETH_DMAMFBOCR_OFC_Pos                               ( 17U )
#define ETH_DMAMFBOCR_OFC_Msk                               ( 0x7ffUL << ETH_DMAMFBOCR_OFC_Pos )
#define ETH_DMAMFBOCR_OFC                                   ( ETH_DMAMFBOCR_OFC_Msk )

#define ETH_DMAMFBOCR_OBMFC_Pos                             ( 16U )
#define ETH_DMAMFBOCR_OBMFC_Msk                             ( 0x1UL << ETH_DMAMFBOCR_OBMFC_Pos )
#define ETH_DMAMFBOCR_OBMFC                                 ( ETH_DMAMFBOCR_OBMFC_Msk )

#define ETH_DMAMFBOCR_MFC_Pos                               ( 0U )
#define ETH_DMAMFBOCR_MFC_Msk                               ( 0xffffUL << ETH_DMAMFBOCR_MFC_Pos )
#define ETH_DMAMFBOCR_MFC                                   ( ETH_DMAMFBOCR_MFC_Msk )


/***************  Bits definition for ETH_DMARIWTR  **********************/

#define ETH_DMARIWTR_RIWTC_Pos                              ( 0U )
#define ETH_DMARIWTR_RIWTC_Msk                              ( 0xffUL << ETH_DMARIWTR_RIWTC_Pos )
#define ETH_DMARIWTR_RIWTC                                  ( ETH_DMARIWTR_RIWTC_Msk )


/***************  Bits definition for ETH_DMACHTDR  **********************/

#define ETH_DMACHTDR_HTDAP_Pos                              ( 0U )
#define ETH_DMACHTDR_HTDAP_Msk                              ( 0xffffffffUL << ETH_DMACHTDR_HTDAP_Pos )
#define ETH_DMACHTDR_HTDAP                                  ( ETH_DMACHTDR_HTDAP_Msk )


/***************  Bits definition for ETH_DMACHRDR  **********************/

#define ETH_DMACHRDR_HRDAP_Pos                              ( 0U )
#define ETH_DMACHRDR_HRDAP_Msk                              ( 0xffffffffUL << ETH_DMACHRDR_HRDAP_Pos )
#define ETH_DMACHRDR_HRDAP                                  ( ETH_DMACHRDR_HRDAP_Msk )


/***************  Bits definition for ETH_DMACHTBAR  **********************/

#define ETH_DMACHTBAR_HTBAP_Pos                             ( 0U )
#define ETH_DMACHTBAR_HTBAP_Msk                             ( 0xffffffffUL << ETH_DMACHTBAR_HTBAP_Pos )
#define ETH_DMACHTBAR_HTBAP                                 ( ETH_DMACHTBAR_HTBAP_Msk )


/***************  Bits definition for ETH_DMACHRBAR  **********************/

#define ETH_DMACHRBAR_HRBAP_Pos                             ( 0U )
#define ETH_DMACHRBAR_HRBAP_Msk                             ( 0xffffffffUL << ETH_DMACHRBAR_HRBAP_Pos )
#define ETH_DMACHRBAR_HRBAP                                 ( ETH_DMACHRBAR_HRBAP_Msk )


/***************  Bits definition for PMU_CTRL0  **********************/

#define PMU_CTRL0_BKPRAMREN_Pos                             ( 31U )
#define PMU_CTRL0_BKPRAMREN_Msk                             ( 0x1UL << PMU_CTRL0_BKPRAMREN_Pos )
#define PMU_CTRL0_BKPRAMREN                                 ( PMU_CTRL0_BKPRAMREN_Msk )

#define PMU_CTRL0_BKPRAMSEN_Pos                             ( 30U )
#define PMU_CTRL0_BKPRAMSEN_Msk                             ( 0x1UL << PMU_CTRL0_BKPRAMSEN_Pos )
#define PMU_CTRL0_BKPRAMSEN                                 ( PMU_CTRL0_BKPRAMSEN_Msk )

#define PMU_CTRL0_STOPWPT_Pos                               ( 16U )
#define PMU_CTRL0_STOPWPT_Msk                               ( 0xfffUL << PMU_CTRL0_STOPWPT_Pos )
#define PMU_CTRL0_STOPWPT                                   ( PMU_CTRL0_STOPWPT_Msk )

#define PMU_CTRL0_LPLDO12_Pos                               ( 12U )
#define PMU_CTRL0_LPLDO12_Msk                               ( 0x7UL << PMU_CTRL0_LPLDO12_Pos )
#define PMU_CTRL0_LPLDO12                                   ( PMU_CTRL0_LPLDO12_Msk )
#define PMU_CTRL0_LPLDO12_0                                 ( 0x1UL << PMU_CTRL0_LPLDO12_Pos )
#define PMU_CTRL0_LPLDO12_1                                 ( 0x2UL << PMU_CTRL0_LPLDO12_Pos )
#define PMU_CTRL0_LPLDO12_2                                 ( 0x4UL << PMU_CTRL0_LPLDO12_Pos )

#define PMU_CTRL0_MLDO12_Pos                                ( 8U )
#define PMU_CTRL0_MLDO12_Msk                                ( 0x3UL << PMU_CTRL0_MLDO12_Pos )
#define PMU_CTRL0_MLDO12                                    ( PMU_CTRL0_MLDO12_Msk )
#define PMU_CTRL0_MLDO12_0                                  ( 0x1UL << PMU_CTRL0_MLDO12_Pos )
#define PMU_CTRL0_MLDO12_1                                  ( 0x2UL << PMU_CTRL0_MLDO12_Pos )

#define PMU_CTRL0_RTCWE_Pos                                 ( 7U )
#define PMU_CTRL0_RTCWE_Msk                                 ( 0x1UL << PMU_CTRL0_RTCWE_Pos )
#define PMU_CTRL0_RTCWE                                     ( PMU_CTRL0_RTCWE_Msk )

#define PMU_CTRL0_RCHDIV_Pos                                ( 5U )
#define PMU_CTRL0_RCHDIV_Msk                                ( 0x1UL << PMU_CTRL0_RCHDIV_Pos )
#define PMU_CTRL0_RCHDIV                                    ( PMU_CTRL0_RCHDIV_Msk )

#define PMU_CTRL0_RCHPDEN_Pos                               ( 4U )
#define PMU_CTRL0_RCHPDEN_Msk                               ( 0x1UL << PMU_CTRL0_RCHPDEN_Pos )
#define PMU_CTRL0_RCHPDEN                                   ( PMU_CTRL0_RCHPDEN_Msk )

#define PMU_CTRL0_LPMS_Pos                                  ( 0U )
#define PMU_CTRL0_LPMS_Msk                                  ( 0x1UL << PMU_CTRL0_LPMS_Pos )
#define PMU_CTRL0_LPMS                                      ( PMU_CTRL0_LPMS_Msk )


/***************  Bits definition for PMU_CTRL1  **********************/

#define PMU_CTRL1_LVDVALUE_Pos                              ( 15U )
#define PMU_CTRL1_LVDVALUE_Msk                              ( 0x1UL << PMU_CTRL1_LVDVALUE_Pos )
#define PMU_CTRL1_LVDVALUE                                  ( PMU_CTRL1_LVDVALUE_Msk )

#define PMU_CTRL1_LVDFILTER_Pos                             ( 14U )
#define PMU_CTRL1_LVDFILTER_Msk                             ( 0x1UL << PMU_CTRL1_LVDFILTER_Pos )
#define PMU_CTRL1_LVDFILTER                                 ( PMU_CTRL1_LVDFILTER_Msk )

#define PMU_CTRL1_FLTTIME_Pos                               ( 9U )
#define PMU_CTRL1_FLTTIME_Msk                               ( 0x7UL << PMU_CTRL1_FLTTIME_Pos )
#define PMU_CTRL1_FLTTIME                                   ( PMU_CTRL1_FLTTIME_Msk )
#define PMU_CTRL1_FLTTIME_0                                 ( 0x1UL << PMU_CTRL1_FLTTIME_Pos )
#define PMU_CTRL1_FLTTIME_1                                 ( 0x2UL << PMU_CTRL1_FLTTIME_Pos )
#define PMU_CTRL1_FLTTIME_2                                 ( 0x4UL << PMU_CTRL1_FLTTIME_Pos )

#define PMU_CTRL1_LVDFLTEN_Pos                              ( 8U )
#define PMU_CTRL1_LVDFLTEN_Msk                              ( 0x1UL << PMU_CTRL1_LVDFLTEN_Pos )
#define PMU_CTRL1_LVDFLTEN                                  ( PMU_CTRL1_LVDFLTEN_Msk )

#define PMU_CTRL1_LVDSEL_Pos                                ( 1U )
#define PMU_CTRL1_LVDSEL_Msk                                ( 0x7UL << PMU_CTRL1_LVDSEL_Pos )
#define PMU_CTRL1_LVDSEL                                    ( PMU_CTRL1_LVDSEL_Msk )
#define PMU_CTRL1_LVDSEL_0                                  ( 0x1UL << PMU_CTRL1_LVDSEL_Pos )
#define PMU_CTRL1_LVDSEL_1                                  ( 0x2UL << PMU_CTRL1_LVDSEL_Pos )
#define PMU_CTRL1_LVDSEL_2                                  ( 0x4UL << PMU_CTRL1_LVDSEL_Pos )

#define PMU_CTRL1_LVDEN_Pos                                 ( 0U )
#define PMU_CTRL1_LVDEN_Msk                                 ( 0x1UL << PMU_CTRL1_LVDEN_Pos )
#define PMU_CTRL1_LVDEN                                     ( PMU_CTRL1_LVDEN_Msk )


/***************  Bits definition for PMU_CTRL2  **********************/

#define PMU_CTRL2_BORCFG_Pos                                ( 26U )
#define PMU_CTRL2_BORCFG_Msk                                ( 0x3UL << PMU_CTRL2_BORCFG_Pos )
#define PMU_CTRL2_BORCFG                                    ( PMU_CTRL2_BORCFG_Msk )
#define PMU_CTRL2_BORCFG_0                                  ( 0x1UL << PMU_CTRL2_BORCFG_Pos )
#define PMU_CTRL2_BORCFG_1                                  ( 0x2UL << PMU_CTRL2_BORCFG_Pos )

#define PMU_CTRL2_BOREN_Pos                                 ( 24U )
#define PMU_CTRL2_BOREN_Msk                                 ( 0x1UL << PMU_CTRL2_BOREN_Pos )
#define PMU_CTRL2_BOREN                                     ( PMU_CTRL2_BOREN_Msk )

#define PMU_CTRL2_BORRSTEN_Pos                              ( 20U )
#define PMU_CTRL2_BORRSTEN_Msk                              ( 0x1UL << PMU_CTRL2_BORRSTEN_Pos )
#define PMU_CTRL2_BORRSTEN                                  ( PMU_CTRL2_BORRSTEN_Msk )

#define PMU_CTRL2_STDBYWPT_Pos                              ( 16U )
#define PMU_CTRL2_STDBYWPT_Msk                              ( 0xfUL << PMU_CTRL2_STDBYWPT_Pos )
#define PMU_CTRL2_STDBYWPT                                  ( PMU_CTRL2_STDBYWPT_Msk )
#define PMU_CTRL2_STDBYWPT_0                                ( 0x1UL << PMU_CTRL2_STDBYWPT_Pos )
#define PMU_CTRL2_STDBYWPT_1                                ( 0x2UL << PMU_CTRL2_STDBYWPT_Pos )
#define PMU_CTRL2_STDBYWPT_2                                ( 0x4UL << PMU_CTRL2_STDBYWPT_Pos )

#define PMU_CTRL2_WUXFILEN_Pos                              ( 8U )
#define PMU_CTRL2_WUXFILEN_Msk                              ( 0x1fUL << PMU_CTRL2_WUXFILEN_Pos )
#define PMU_CTRL2_WUXFILEN                                  ( PMU_CTRL2_WUXFILEN_Msk )
#define PMU_CTRL2_WUXFILEN_0                                ( 0x1UL << PMU_CTRL2_WUXFILEN_Pos )
#define PMU_CTRL2_WUXFILEN_1                                ( 0x2UL << PMU_CTRL2_WUXFILEN_Pos )
#define PMU_CTRL2_WUXFILEN_2                                ( 0x4UL << PMU_CTRL2_WUXFILEN_Pos )
#define PMU_CTRL2_WUXFILEN_3                                ( 0x8UL << PMU_CTRL2_WUXFILEN_Pos )
#define PMU_CTRL2_WUXFILEN_4                                ( 0x10UL << PMU_CTRL2_WUXFILEN_Pos )

#define PMU_CTRL2_EWUPX_Pos                                 ( 0U )
#define PMU_CTRL2_EWUPX_Msk                                 ( 0x1fUL << PMU_CTRL2_EWUPX_Pos )
#define PMU_CTRL2_EWUPX                                     ( PMU_CTRL2_EWUPX_Msk )
#define PMU_CTRL2_EWUPX_0                                   ( 0x1UL << PMU_CTRL2_EWUPX_Pos )
#define PMU_CTRL2_EWUPX_1                                   ( 0x2UL << PMU_CTRL2_EWUPX_Pos )
#define PMU_CTRL2_EWUPX_2                                   ( 0x4UL << PMU_CTRL2_EWUPX_Pos )
#define PMU_CTRL2_EWUPX_3                                   ( 0x8UL << PMU_CTRL2_EWUPX_Pos )
#define PMU_CTRL2_EWUPX_4                                   ( 0x10UL << PMU_CTRL2_EWUPX_Pos )


/***************  Bits definition for PMU_CTRL3  **********************/

#define PMU_CTRL3_WUPOLX_Pos                                ( 0U )
#define PMU_CTRL3_WUPOLX_Msk                                ( 0x1fUL << PMU_CTRL3_WUPOLX_Pos )
#define PMU_CTRL3_WUPOLX                                    ( PMU_CTRL3_WUPOLX_Msk )
#define PMU_CTRL3_WUPOLX_0                                  ( 0x1UL << PMU_CTRL3_WUPOLX_Pos )
#define PMU_CTRL3_WUPOLX_1                                  ( 0x2UL << PMU_CTRL3_WUPOLX_Pos )
#define PMU_CTRL3_WUPOLX_2                                  ( 0x4UL << PMU_CTRL3_WUPOLX_Pos )
#define PMU_CTRL3_WUPOLX_3                                  ( 0x8UL << PMU_CTRL3_WUPOLX_Pos )
#define PMU_CTRL3_WUPOLX_4                                  ( 0x10UL << PMU_CTRL3_WUPOLX_Pos )


/***************  Bits definition for PMU_ST  **********************/

#define PMU_SR_BORN_Pos                                     ( 16U )
#define PMU_SR_BORN_Msk                                     ( 0x1UL << PMU_SR_BORN_Pos )
#define PMU_SR_BORN                                         ( PMU_SR_BORN_Msk )

#define PMU_SR_BORWUF_Pos                                   ( 15U )
#define PMU_SR_BORWUF_Msk                                   ( 0x1UL << PMU_SR_BORWUF_Pos )
#define PMU_SR_BORWUF                                       ( PMU_SR_BORWUF_Msk )

#define PMU_SR_IWDTWUF_Pos                                  ( 14U )
#define PMU_SR_IWDTWUF_Msk                                  ( 0x1UL << PMU_SR_IWDTWUF_Pos )
#define PMU_SR_IWDTWUF                                      ( PMU_SR_IWDTWUF_Msk )

#define PMU_SR_RSTWUF_Pos                                   ( 13U )
#define PMU_SR_RSTWUF_Msk                                   ( 0x1UL << PMU_SR_RSTWUF_Pos )
#define PMU_SR_RSTWUF                                       ( PMU_SR_RSTWUF_Msk )

#define PMU_SR_RTCWUF_Pos                                   ( 12U )
#define PMU_SR_RTCWUF_Msk                                   ( 0x1UL << PMU_SR_RTCWUF_Pos )
#define PMU_SR_RTCWUF                                       ( PMU_SR_RTCWUF_Msk )

#define PMU_SR_SBF_Pos                                      ( 8U )
#define PMU_SR_SBF_Msk                                      ( 0x1UL << PMU_SR_SBF_Pos )
#define PMU_SR_SBF                                          ( PMU_SR_SBF_Msk )

#define PMU_SR_WUPFX_Pos                                    ( 0U )
#define PMU_SR_WUPFX_Msk                                    ( 0x1fUL << PMU_SR_WUPFX_Pos )
#define PMU_SR_WUPFX                                        ( PMU_SR_WUPFX_Msk )
#define PMU_SR_WUPFX_0                                      ( 0x1UL << PMU_SR_WUPFX_Pos )
#define PMU_SR_WUPFX_1                                      ( 0x2UL << PMU_SR_WUPFX_Pos )
#define PMU_SR_WUPFX_2                                      ( 0x4UL << PMU_SR_WUPFX_Pos )
#define PMU_SR_WUPFX_3                                      ( 0x8UL << PMU_SR_WUPFX_Pos )
#define PMU_SR_WUPFX_4                                      ( 0x10UL << PMU_SR_WUPFX_Pos )


/***************  Bits definition for PMU_STCLR  **********************/

#define PMU_STCLR_CBORWUF_Pos                               ( 15U )
#define PMU_STCLR_CBORWUF_Msk                               ( 0x1UL << PMU_STCLR_CBORWUF_Pos )
#define PMU_STCLR_CBORWUF                                   ( PMU_STCLR_CBORWUF_Msk )

#define PMU_STCLR_CIWDTWUF_Pos                              ( 14U )
#define PMU_STCLR_CIWDTWUF_Msk                              ( 0x1UL << PMU_STCLR_CIWDTWUF_Pos )
#define PMU_STCLR_CIWDTWUF                                  ( PMU_STCLR_CIWDTWUF_Msk )

#define PMU_STCLR_CRSTWUF_Pos                               ( 13U )
#define PMU_STCLR_CRSTWUF_Msk                               ( 0x1UL << PMU_STCLR_CRSTWUF_Pos )
#define PMU_STCLR_CRSTWUF                                   ( PMU_STCLR_CRSTWUF_Msk )

#define PMU_STCLR_CRTCWUF_Pos                               ( 12U )
#define PMU_STCLR_CRTCWUF_Msk                               ( 0x1UL << PMU_STCLR_CRTCWUF_Pos )
#define PMU_STCLR_CRTCWUF                                   ( PMU_STCLR_CRTCWUF_Msk )

#define PMU_STCLR_CSBF_Pos                                  ( 8U )
#define PMU_STCLR_CSBF_Msk                                  ( 0x1UL << PMU_STCLR_CSBF_Pos )
#define PMU_STCLR_CSBF                                      ( PMU_STCLR_CSBF_Msk )

#define PMU_STCLR_CWUFX_Pos                                 ( 0U )
#define PMU_STCLR_CWUFX_Msk                                 ( 0x1fUL << PMU_STCLR_CWUFX_Pos )
#define PMU_STCLR_CWUFX                                     ( PMU_STCLR_CWUFX_Msk )
#define PMU_STCLR_CWUFX_0                                   ( 0x1UL << PMU_STCLR_CWUFX_Pos )
#define PMU_STCLR_CWUFX_1                                   ( 0x2UL << PMU_STCLR_CWUFX_Pos )
#define PMU_STCLR_CWUFX_2                                   ( 0x4UL << PMU_STCLR_CWUFX_Pos )
#define PMU_STCLR_CWUFX_3                                   ( 0x8UL << PMU_STCLR_CWUFX_Pos )
#define PMU_STCLR_CWUFX_4                                   ( 0x10UL << PMU_STCLR_CWUFX_Pos )


/***************  Bits definition for PMU_IOSEL  **********************/

#define PMU_IOSEL_PI8VALUE_Pos                              ( 11U )
#define PMU_IOSEL_PI8VALUE_Msk                              ( 0x1UL << PMU_IOSEL_PI8VALUE_Pos )
#define PMU_IOSEL_PI8VALUE                                  ( PMU_IOSEL_PI8VALUE_Msk )

#define PMU_IOSEL_PC15VALUE_Pos                             ( 10U )
#define PMU_IOSEL_PC15VALUE_Msk                             ( 0x1UL << PMU_IOSEL_PC15VALUE_Pos )
#define PMU_IOSEL_PC15VALUE                                 ( PMU_IOSEL_PC15VALUE_Msk )

#define PMU_IOSEL_PC14VALUE_Pos                             ( 9U )
#define PMU_IOSEL_PC14VALUE_Msk                             ( 0x1UL << PMU_IOSEL_PC14VALUE_Pos )
#define PMU_IOSEL_PC14VALUE                                 ( PMU_IOSEL_PC14VALUE_Msk )

#define PMU_IOSEL_PC13VALUE_Pos                             ( 8U )
#define PMU_IOSEL_PC13VALUE_Msk                             ( 0x1UL << PMU_IOSEL_PC13VALUE_Pos )
#define PMU_IOSEL_PC13VALUE                                 ( PMU_IOSEL_PC13VALUE_Msk )

#define PMU_IOSEL_PI8SEL_Pos                                ( 6U )
#define PMU_IOSEL_PI8SEL_Msk                                ( 0x3UL << PMU_IOSEL_PI8SEL_Pos )
#define PMU_IOSEL_PI8SEL                                    ( PMU_IOSEL_PI8SEL_Msk )
#define PMU_IOSEL_PI8SEL_0                                  ( 0x1UL << PMU_IOSEL_PI8SEL_Pos )
#define PMU_IOSEL_PI8SEL_1                                  ( 0x2UL << PMU_IOSEL_PI8SEL_Pos )

#define PMU_IOSEL_PC15SEL_Pos                               ( 4U )
#define PMU_IOSEL_PC15SEL_Msk                               ( 0x3UL << PMU_IOSEL_PC15SEL_Pos )
#define PMU_IOSEL_PC15SEL                                   ( PMU_IOSEL_PC15SEL_Msk )
#define PMU_IOSEL_PC15SEL_0                                 ( 0x1UL << PMU_IOSEL_PC15SEL_Pos )
#define PMU_IOSEL_PC15SEL_1                                 ( 0x2UL << PMU_IOSEL_PC15SEL_Pos )

#define PMU_IOSEL_PC14SEL_Pos                               ( 2U )
#define PMU_IOSEL_PC14SEL_Msk                               ( 0x3UL << PMU_IOSEL_PC14SEL_Pos )
#define PMU_IOSEL_PC14SEL                                   ( PMU_IOSEL_PC14SEL_Msk )
#define PMU_IOSEL_PC14SEL_0                                 ( 0x1UL << PMU_IOSEL_PC14SEL_Pos )
#define PMU_IOSEL_PC14SEL_1                                 ( 0x2UL << PMU_IOSEL_PC14SEL_Pos )

#define PMU_IOSEL_PC13SEL_Pos                               ( 0U )
#define PMU_IOSEL_PC13SEL_Msk                               ( 0x3UL << PMU_IOSEL_PC13SEL_Pos )
#define PMU_IOSEL_PC13SEL                                   ( PMU_IOSEL_PC13SEL_Msk )
#define PMU_IOSEL_PC13SEL_0                                 ( 0x1UL << PMU_IOSEL_PC13SEL_Pos )
#define PMU_IOSEL_PC13SEL_1                                 ( 0x2UL << PMU_IOSEL_PC13SEL_Pos )


/***************  Bits definition for PMU_TEST_ANATEST_SR  **********************/

#define PMU_TEST_ANATEST_SR_ANATESTSEL_Pos                  ( 0U )
#define PMU_TEST_ANATEST_SR_ANATESTSEL_Msk                  ( 0x7UL << PMU_TEST_ANATEST_SR_ANATESTSEL_Pos )
#define PMU_TEST_ANATEST_SR_ANATESTSEL                      ( PMU_TEST_ANATEST_SR_ANATESTSEL_Msk )
#define PMU_TEST_ANATEST_SR_ANATESTSEL_0                    ( 0x1UL << PMU_TEST_ANATEST_SR_ANATESTSEL_Pos )
#define PMU_TEST_ANATEST_SR_ANATESTSEL_1                    ( 0x2UL << PMU_TEST_ANATEST_SR_ANATESTSEL_Pos )
#define PMU_TEST_ANATEST_SR_ANATESTSEL_2                    ( 0x4UL << PMU_TEST_ANATEST_SR_ANATESTSEL_Pos )


/***************  Bits definition for PMU_TEST_LDOCAL  **********************/

#define PMU_TEST_LDOCAL_LPLDO12TRIM_Pos                     ( 12U )
#define PMU_TEST_LDOCAL_LPLDO12TRIM_Msk                     ( 0x7UL << PMU_TEST_LDOCAL_LPLDO12TRIM_Pos )
#define PMU_TEST_LDOCAL_LPLDO12TRIM                         ( PMU_TEST_LDOCAL_LPLDO12TRIM_Msk )
#define PMU_TEST_LDOCAL_LPLDO12TRIM_0                       ( 0x1UL << PMU_TEST_LDOCAL_LPLDO12TRIM_Pos )
#define PMU_TEST_LDOCAL_LPLDO12TRIM_1                       ( 0x2UL << PMU_TEST_LDOCAL_LPLDO12TRIM_Pos )
#define PMU_TEST_LDOCAL_LPLDO12TRIM_2                       ( 0x4UL << PMU_TEST_LDOCAL_LPLDO12TRIM_Pos )

#define PMU_TEST_LDOCAL_MLDO12TRIM_Pos                      ( 8U )
#define PMU_TEST_LDOCAL_MLDO12TRIM_Msk                      ( 0xfUL << PMU_TEST_LDOCAL_MLDO12TRIM_Pos )
#define PMU_TEST_LDOCAL_MLDO12TRIM                          ( PMU_TEST_LDOCAL_MLDO12TRIM_Msk )
#define PMU_TEST_LDOCAL_MLDO12TRIM_0                        ( 0x1UL << PMU_TEST_LDOCAL_MLDO12TRIM_Pos )
#define PMU_TEST_LDOCAL_MLDO12TRIM_1                        ( 0x2UL << PMU_TEST_LDOCAL_MLDO12TRIM_Pos )
#define PMU_TEST_LDOCAL_MLDO12TRIM_2                        ( 0x4UL << PMU_TEST_LDOCAL_MLDO12TRIM_Pos )
#define PMU_TEST_LDOCAL_MLDO12TRIM_3                        ( 0x8UL << PMU_TEST_LDOCAL_MLDO12TRIM_Pos )

#define PMU_TEST_LDOCAL_LPBGRTRIM_Pos                       ( 4U )
#define PMU_TEST_LDOCAL_LPBGRTRIM_Msk                       ( 0x7UL << PMU_TEST_LDOCAL_LPBGRTRIM_Pos )
#define PMU_TEST_LDOCAL_LPBGRTRIM                           ( PMU_TEST_LDOCAL_LPBGRTRIM_Msk )
#define PMU_TEST_LDOCAL_LPBGRTRIM_0                         ( 0x1UL << PMU_TEST_LDOCAL_LPBGRTRIM_Pos )
#define PMU_TEST_LDOCAL_LPBGRTRIM_1                         ( 0x2UL << PMU_TEST_LDOCAL_LPBGRTRIM_Pos )
#define PMU_TEST_LDOCAL_LPBGRTRIM_2                         ( 0x4UL << PMU_TEST_LDOCAL_LPBGRTRIM_Pos )

#define PMU_TEST_LDOCAL_VREFTRIM_Pos                        ( 0U )
#define PMU_TEST_LDOCAL_VREFTRIM_Msk                        ( 0x7UL << PMU_TEST_LDOCAL_VREFTRIM_Pos )
#define PMU_TEST_LDOCAL_VREFTRIM                            ( PMU_TEST_LDOCAL_VREFTRIM_Msk )
#define PMU_TEST_LDOCAL_VREFTRIM_0                          ( 0x1UL << PMU_TEST_LDOCAL_VREFTRIM_Pos )
#define PMU_TEST_LDOCAL_VREFTRIM_1                          ( 0x2UL << PMU_TEST_LDOCAL_VREFTRIM_Pos )
#define PMU_TEST_LDOCAL_VREFTRIM_2                          ( 0x4UL << PMU_TEST_LDOCAL_VREFTRIM_Pos )


/***************  Bits definition for PMU_TEST_LDOCR  **********************/

#define PMU_TEST_LDOCR_TEST_LPLDO12EN_Pos                   ( 9U )
#define PMU_TEST_LDOCR_TEST_LPLDO12EN_Msk                   ( 0x1UL << PMU_TEST_LDOCR_TEST_LPLDO12EN_Pos )
#define PMU_TEST_LDOCR_TEST_LPLDO12EN                       ( PMU_TEST_LDOCR_TEST_LPLDO12EN_Msk )

#define PMU_TEST_LDOCR_TEST_MLDO12LV_Pos                    ( 4U )
#define PMU_TEST_LDOCR_TEST_MLDO12LV_Msk                    ( 0x3UL << PMU_TEST_LDOCR_TEST_MLDO12LV_Pos )
#define PMU_TEST_LDOCR_TEST_MLDO12LV                        ( PMU_TEST_LDOCR_TEST_MLDO12LV_Msk )
#define PMU_TEST_LDOCR_TEST_MLDO12LV_0                      ( 0x1UL << PMU_TEST_LDOCR_TEST_MLDO12LV_Pos )
#define PMU_TEST_LDOCR_TEST_MLDO12LV_1                      ( 0x2UL << PMU_TEST_LDOCR_TEST_MLDO12LV_Pos )

#define PMU_TEST_LDOCR_LDO_TESTEN_Pos                       ( 0U )
#define PMU_TEST_LDOCR_LDO_TESTEN_Msk                       ( 0x1UL << PMU_TEST_LDOCR_LDO_TESTEN_Pos )
#define PMU_TEST_LDOCR_LDO_TESTEN                           ( PMU_TEST_LDOCR_LDO_TESTEN_Msk )


/***************  Bits definition for RTC_WP  **********************/

#define RTC_WP_WE_Pos                                       ( 0U )
#define RTC_WP_WE_Msk                                       ( 0x1UL << RTC_WP_WE_Pos )
#define RTC_WP_WE                                           ( RTC_WP_WE_Msk )


/***************  Bits definition for RTC_IE  **********************/

#define RTC_IE_WUTIE_Pos                                    ( 17U )
#define RTC_IE_WUTIE_Msk                                    ( 0x1UL << RTC_IE_WUTIE_Pos )
#define RTC_IE_WUTIE                                        ( RTC_IE_WUTIE_Msk )

#define RTC_IE_STP2RIE_Pos                                  ( 16U )
#define RTC_IE_STP2RIE_Msk                                  ( 0x1UL << RTC_IE_STP2RIE_Pos )
#define RTC_IE_STP2RIE                                      ( RTC_IE_STP2RIE_Msk )

#define RTC_IE_STP2FIE_Pos                                  ( 15U )
#define RTC_IE_STP2FIE_Msk                                  ( 0x1UL << RTC_IE_STP2FIE_Pos )
#define RTC_IE_STP2FIE                                      ( RTC_IE_STP2FIE_Msk )

#define RTC_IE_STP1RIE_Pos                                  ( 14U )
#define RTC_IE_STP1RIE_Msk                                  ( 0x1UL << RTC_IE_STP1RIE_Pos )
#define RTC_IE_STP1RIE                                      ( RTC_IE_STP1RIE_Msk )

#define RTC_IE_STP1FIE_Pos                                  ( 13U )
#define RTC_IE_STP1FIE_Msk                                  ( 0x1UL << RTC_IE_STP1FIE_Pos )
#define RTC_IE_STP1FIE                                      ( RTC_IE_STP1FIE_Msk )

#define RTC_IE_ADJ32_IE_Pos                                 ( 12U )
#define RTC_IE_ADJ32_IE_Msk                                 ( 0x1UL << RTC_IE_ADJ32_IE_Pos )
#define RTC_IE_ADJ32_IE                                     ( RTC_IE_ADJ32_IE_Msk )

#define RTC_IE_ALM_IE_Pos                                   ( 11U )
#define RTC_IE_ALM_IE_Msk                                   ( 0x1UL << RTC_IE_ALM_IE_Pos )
#define RTC_IE_ALM_IE                                       ( RTC_IE_ALM_IE_Msk )

#define RTC_IE_1KHZ_IE_Pos                                  ( 10U )
#define RTC_IE_1KHZ_IE_Msk                                  ( 0x1UL << RTC_IE_1KHZ_IE_Pos )
#define RTC_IE_1KHZ_IE                                      ( RTC_IE_1KHZ_IE_Msk )

#define RTC_IE_256HZ_IE_Pos                                 ( 9U )
#define RTC_IE_256HZ_IE_Msk                                 ( 0x1UL << RTC_IE_256HZ_IE_Pos )
#define RTC_IE_256HZ_IE                                     ( RTC_IE_256HZ_IE_Msk )

#define RTC_IE_64HZ_IE_Pos                                  ( 8U )
#define RTC_IE_64HZ_IE_Msk                                  ( 0x1UL << RTC_IE_64HZ_IE_Pos )
#define RTC_IE_64HZ_IE                                      ( RTC_IE_64HZ_IE_Msk )

#define RTC_IE_16HZ_IE_Pos                                  ( 7U )
#define RTC_IE_16HZ_IE_Msk                                  ( 0x1UL << RTC_IE_16HZ_IE_Pos )
#define RTC_IE_16HZ_IE                                      ( RTC_IE_16HZ_IE_Msk )

#define RTC_IE_8HZ_IE_Pos                                   ( 6U )
#define RTC_IE_8HZ_IE_Msk                                   ( 0x1UL << RTC_IE_8HZ_IE_Pos )
#define RTC_IE_8HZ_IE                                       ( RTC_IE_8HZ_IE_Msk )

#define RTC_IE_4HZ_IE_Pos                                   ( 5U )
#define RTC_IE_4HZ_IE_Msk                                   ( 0x1UL << RTC_IE_4HZ_IE_Pos )
#define RTC_IE_4HZ_IE                                       ( RTC_IE_4HZ_IE_Msk )

#define RTC_IE_2HZ_IE_Pos                                   ( 4U )
#define RTC_IE_2HZ_IE_Msk                                   ( 0x1UL << RTC_IE_2HZ_IE_Pos )
#define RTC_IE_2HZ_IE                                       ( RTC_IE_2HZ_IE_Msk )

#define RTC_IE_SEC_IE_Pos                                   ( 3U )
#define RTC_IE_SEC_IE_Msk                                   ( 0x1UL << RTC_IE_SEC_IE_Pos )
#define RTC_IE_SEC_IE                                       ( RTC_IE_SEC_IE_Msk )

#define RTC_IE_MIN_IE_Pos                                   ( 2U )
#define RTC_IE_MIN_IE_Msk                                   ( 0x1UL << RTC_IE_MIN_IE_Pos )
#define RTC_IE_MIN_IE                                       ( RTC_IE_MIN_IE_Msk )

#define RTC_IE_HOUR_IE_Pos                                  ( 1U )
#define RTC_IE_HOUR_IE_Msk                                  ( 0x1UL << RTC_IE_HOUR_IE_Pos )
#define RTC_IE_HOUR_IE                                      ( RTC_IE_HOUR_IE_Msk )

#define RTC_IE_DATE_IE_Pos                                  ( 0U )
#define RTC_IE_DATE_IE_Msk                                  ( 0x1UL << RTC_IE_DATE_IE_Pos )
#define RTC_IE_DATE_IE                                      ( RTC_IE_DATE_IE_Msk )


/***************  Bits definition for RTC_SR  **********************/

#define RTC_SR_WUTWF_Pos                                    ( 24U )
#define RTC_SR_WUTWF_Msk                                    ( 0x1UL << RTC_SR_WUTWF_Pos )
#define RTC_SR_WUTWF                                        ( RTC_SR_WUTWF_Msk )

#define RTC_SR_WUTF_Pos                                     ( 17U )
#define RTC_SR_WUTF_Msk                                     ( 0x1UL << RTC_SR_WUTF_Pos )
#define RTC_SR_WUTF                                         ( RTC_SR_WUTF_Msk )

#define RTC_SR_STP2RIF_Pos                                  ( 16U )
#define RTC_SR_STP2RIF_Msk                                  ( 0x1UL << RTC_SR_STP2RIF_Pos )
#define RTC_SR_STP2RIF                                      ( RTC_SR_STP2RIF_Msk )

#define RTC_SR_STP2FIF_Pos                                  ( 15U )
#define RTC_SR_STP2FIF_Msk                                  ( 0x1UL << RTC_SR_STP2FIF_Pos )
#define RTC_SR_STP2FIF                                      ( RTC_SR_STP2FIF_Msk )

#define RTC_SR_STP1RIF_Pos                                  ( 14U )
#define RTC_SR_STP1RIF_Msk                                  ( 0x1UL << RTC_SR_STP1RIF_Pos )
#define RTC_SR_STP1RIF                                      ( RTC_SR_STP1RIF_Msk )

#define RTC_SR_STP1FIF_Pos                                  ( 13U )
#define RTC_SR_STP1FIF_Msk                                  ( 0x1UL << RTC_SR_STP1FIF_Pos )
#define RTC_SR_STP1FIF                                      ( RTC_SR_STP1FIF_Msk )

#define RTC_SR_ADJ32_IF_Pos                                 ( 12U )
#define RTC_SR_ADJ32_IF_Msk                                 ( 0x1UL << RTC_SR_ADJ32_IF_Pos )
#define RTC_SR_ADJ32_IF                                     ( RTC_SR_ADJ32_IF_Msk )

#define RTC_SR_ALM_IF_Pos                                   ( 11U )
#define RTC_SR_ALM_IF_Msk                                   ( 0x1UL << RTC_SR_ALM_IF_Pos )
#define RTC_SR_ALM_IF                                       ( RTC_SR_ALM_IF_Msk )

#define RTC_SR_1KHZ_IF_Pos                                  ( 10U )
#define RTC_SR_1KHZ_IF_Msk                                  ( 0x1UL << RTC_SR_1KHZ_IF_Pos )
#define RTC_SR_1KHZ_IF                                      ( RTC_SR_1KHZ_IF_Msk )

#define RTC_SR_256HZ_IF_Pos                                 ( 9U )
#define RTC_SR_256HZ_IF_Msk                                 ( 0x1UL << RTC_SR_256HZ_IF_Pos )
#define RTC_SR_256HZ_IF                                     ( RTC_SR_256HZ_IF_Msk )

#define RTC_SR_64HZ_IF_Pos                                  ( 8U )
#define RTC_SR_64HZ_IF_Msk                                  ( 0x1UL << RTC_SR_64HZ_IF_Pos )
#define RTC_SR_64HZ_IF                                      ( RTC_SR_64HZ_IF_Msk )

#define RTC_SR_16HZ_IF_Pos                                  ( 7U )
#define RTC_SR_16HZ_IF_Msk                                  ( 0x1UL << RTC_SR_16HZ_IF_Pos )
#define RTC_SR_16HZ_IF                                      ( RTC_SR_16HZ_IF_Msk )

#define RTC_SR_8HZ_IF_Pos                                   ( 6U )
#define RTC_SR_8HZ_IF_Msk                                   ( 0x1UL << RTC_SR_8HZ_IF_Pos )
#define RTC_SR_8HZ_IF                                       ( RTC_SR_8HZ_IF_Msk )

#define RTC_SR_4HZ_IF_Pos                                   ( 5U )
#define RTC_SR_4HZ_IF_Msk                                   ( 0x1UL << RTC_SR_4HZ_IF_Pos )
#define RTC_SR_4HZ_IF                                       ( RTC_SR_4HZ_IF_Msk )

#define RTC_SR_2HZ_IF_Pos                                   ( 4U )
#define RTC_SR_2HZ_IF_Msk                                   ( 0x1UL << RTC_SR_2HZ_IF_Pos )
#define RTC_SR_2HZ_IF                                       ( RTC_SR_2HZ_IF_Msk )

#define RTC_SR_SEC_IF_Pos                                   ( 3U )
#define RTC_SR_SEC_IF_Msk                                   ( 0x1UL << RTC_SR_SEC_IF_Pos )
#define RTC_SR_SEC_IF                                       ( RTC_SR_SEC_IF_Msk )

#define RTC_SR_MIN_IF_Pos                                   ( 2U )
#define RTC_SR_MIN_IF_Msk                                   ( 0x1UL << RTC_SR_MIN_IF_Pos )
#define RTC_SR_MIN_IF                                       ( RTC_SR_MIN_IF_Msk )

#define RTC_SR_HOUR_IF_Pos                                  ( 1U )
#define RTC_SR_HOUR_IF_Msk                                  ( 0x1UL << RTC_SR_HOUR_IF_Pos )
#define RTC_SR_HOUR_IF                                      ( RTC_SR_HOUR_IF_Msk )

#define RTC_SR_DATE_IF_Pos                                  ( 0U )
#define RTC_SR_DATE_IF_Msk                                  ( 0x1UL << RTC_SR_DATE_IF_Pos )
#define RTC_SR_DATE_IF                                      ( RTC_SR_DATE_IF_Msk )


/***************  Bits definition for RTC_SEC  **********************/

#define RTC_SEC_BCDSEC_Pos                                  ( 0U )
#define RTC_SEC_BCDSEC_Msk                                  ( 0x7fUL << RTC_SEC_BCDSEC_Pos )
#define RTC_SEC_BCDSEC                                      ( RTC_SEC_BCDSEC_Msk )
#define RTC_SEC_BCDSEC_0                                    ( 0x1UL << RTC_SEC_BCDSEC_Pos )
#define RTC_SEC_BCDSEC_1                                    ( 0x2UL << RTC_SEC_BCDSEC_Pos )
#define RTC_SEC_BCDSEC_2                                    ( 0x4UL << RTC_SEC_BCDSEC_Pos )
#define RTC_SEC_BCDSEC_3                                    ( 0x8UL << RTC_SEC_BCDSEC_Pos )
#define RTC_SEC_BCDSEC_4                                    ( 0x10UL << RTC_SEC_BCDSEC_Pos )
#define RTC_SEC_BCDSEC_5                                    ( 0x20UL << RTC_SEC_BCDSEC_Pos )
#define RTC_SEC_BCDSEC_6                                    ( 0x40UL << RTC_SEC_BCDSEC_Pos )


/***************  Bits definition for RTC_MIN  **********************/

#define RTC_MIN_BCDMIN_Pos                                  ( 0U )
#define RTC_MIN_BCDMIN_Msk                                  ( 0x7fUL << RTC_MIN_BCDMIN_Pos )
#define RTC_MIN_BCDMIN                                      ( RTC_MIN_BCDMIN_Msk )
#define RTC_MIN_BCDMIN_0                                    ( 0x1UL << RTC_MIN_BCDMIN_Pos )
#define RTC_MIN_BCDMIN_1                                    ( 0x2UL << RTC_MIN_BCDMIN_Pos )
#define RTC_MIN_BCDMIN_2                                    ( 0x4UL << RTC_MIN_BCDMIN_Pos )
#define RTC_MIN_BCDMIN_3                                    ( 0x8UL << RTC_MIN_BCDMIN_Pos )
#define RTC_MIN_BCDMIN_4                                    ( 0x10UL << RTC_MIN_BCDMIN_Pos )
#define RTC_MIN_BCDMIN_5                                    ( 0x20UL << RTC_MIN_BCDMIN_Pos )
#define RTC_MIN_BCDMIN_6                                    ( 0x40UL << RTC_MIN_BCDMIN_Pos )


/***************  Bits definition for RTC_HOUR  **********************/

#define RTC_HOUR_BCDHOUR_Pos                                ( 0U )
#define RTC_HOUR_BCDHOUR_Msk                                ( 0x3fUL << RTC_HOUR_BCDHOUR_Pos )
#define RTC_HOUR_BCDHOUR                                    ( RTC_HOUR_BCDHOUR_Msk )
#define RTC_HOUR_BCDHOUR_0                                  ( 0x1UL << RTC_HOUR_BCDHOUR_Pos )
#define RTC_HOUR_BCDHOUR_1                                  ( 0x2UL << RTC_HOUR_BCDHOUR_Pos )
#define RTC_HOUR_BCDHOUR_2                                  ( 0x4UL << RTC_HOUR_BCDHOUR_Pos )
#define RTC_HOUR_BCDHOUR_3                                  ( 0x8UL << RTC_HOUR_BCDHOUR_Pos )
#define RTC_HOUR_BCDHOUR_4                                  ( 0x10UL << RTC_HOUR_BCDHOUR_Pos )
#define RTC_HOUR_BCDHOUR_5                                  ( 0x20UL << RTC_HOUR_BCDHOUR_Pos )


/***************  Bits definition for RTC_DAY  **********************/

#define RTC_DAY_BCDDATE_Pos                                 ( 0U )
#define RTC_DAY_BCDDATE_Msk                                 ( 0x3fUL << RTC_DAY_BCDDATE_Pos )
#define RTC_DAY_BCDDATE                                     ( RTC_DAY_BCDDATE_Msk )
#define RTC_DAY_BCDDATE_0                                   ( 0x1UL << RTC_DAY_BCDDATE_Pos )
#define RTC_DAY_BCDDATE_1                                   ( 0x2UL << RTC_DAY_BCDDATE_Pos )
#define RTC_DAY_BCDDATE_2                                   ( 0x4UL << RTC_DAY_BCDDATE_Pos )
#define RTC_DAY_BCDDATE_3                                   ( 0x8UL << RTC_DAY_BCDDATE_Pos )
#define RTC_DAY_BCDDATE_4                                   ( 0x10UL << RTC_DAY_BCDDATE_Pos )
#define RTC_DAY_BCDDATE_5                                   ( 0x20UL << RTC_DAY_BCDDATE_Pos )


/***************  Bits definition for RTC_WEEK  **********************/

#define RTC_WEEK_BCDWEEK_Pos                                ( 0U )
#define RTC_WEEK_BCDWEEK_Msk                                ( 0x7UL << RTC_WEEK_BCDWEEK_Pos )
#define RTC_WEEK_BCDWEEK                                    ( RTC_WEEK_BCDWEEK_Msk )
#define RTC_WEEK_BCDWEEK_0                                  ( 0x1UL << RTC_WEEK_BCDWEEK_Pos )
#define RTC_WEEK_BCDWEEK_1                                  ( 0x2UL << RTC_WEEK_BCDWEEK_Pos )
#define RTC_WEEK_BCDWEEK_2                                  ( 0x4UL << RTC_WEEK_BCDWEEK_Pos )


/***************  Bits definition for RTC_MONTH  **********************/

#define RTC_MONTH_BCDMONTH_Pos                              ( 0U )
#define RTC_MONTH_BCDMONTH_Msk                              ( 0x1fUL << RTC_MONTH_BCDMONTH_Pos )
#define RTC_MONTH_BCDMONTH                                  ( RTC_MONTH_BCDMONTH_Msk )
#define RTC_MONTH_BCDMONTH_0                                ( 0x1UL << RTC_MONTH_BCDMONTH_Pos )
#define RTC_MONTH_BCDMONTH_1                                ( 0x2UL << RTC_MONTH_BCDMONTH_Pos )
#define RTC_MONTH_BCDMONTH_2                                ( 0x4UL << RTC_MONTH_BCDMONTH_Pos )
#define RTC_MONTH_BCDMONTH_3                                ( 0x8UL << RTC_MONTH_BCDMONTH_Pos )
#define RTC_MONTH_BCDMONTH_4                                ( 0x10UL << RTC_MONTH_BCDMONTH_Pos )


/***************  Bits definition for RTC_YEAR  **********************/

#define RTC_YEAR_BCDYEAR_Pos                                ( 0U )
#define RTC_YEAR_BCDYEAR_Msk                                ( 0xffUL << RTC_YEAR_BCDYEAR_Pos )
#define RTC_YEAR_BCDYEAR                                    ( RTC_YEAR_BCDYEAR_Msk )
#define RTC_YEAR_BCDYEAR_0                                  ( 0x1UL << RTC_YEAR_BCDYEAR_Pos )
#define RTC_YEAR_BCDYEAR_1                                  ( 0x2UL << RTC_YEAR_BCDYEAR_Pos )
#define RTC_YEAR_BCDYEAR_2                                  ( 0x4UL << RTC_YEAR_BCDYEAR_Pos )
#define RTC_YEAR_BCDYEAR_3                                  ( 0x8UL << RTC_YEAR_BCDYEAR_Pos )
#define RTC_YEAR_BCDYEAR_4                                  ( 0x10UL << RTC_YEAR_BCDYEAR_Pos )
#define RTC_YEAR_BCDYEAR_5                                  ( 0x20UL << RTC_YEAR_BCDYEAR_Pos )
#define RTC_YEAR_BCDYEAR_6                                  ( 0x40UL << RTC_YEAR_BCDYEAR_Pos )
#define RTC_YEAR_BCDYEAR_7                                  ( 0x80UL << RTC_YEAR_BCDYEAR_Pos )


/***************  Bits definition for RTC_ALM  **********************/

#define RTC_ALM_ALM_WDS_Pos                                 ( 31U )
#define RTC_ALM_ALM_WDS_Msk                                 ( 0x1UL << RTC_ALM_ALM_WDS_Pos )
#define RTC_ALM_ALM_WDS                                     ( RTC_ALM_ALM_WDS_Msk )

#define RTC_ALM_ALMWEEK_ALMDAY_Pos                          ( 24U )
#define RTC_ALM_ALMWEEK_ALMDAY_Msk                          ( 0x7fUL << RTC_ALM_ALMWEEK_ALMDAY_Pos )
#define RTC_ALM_ALMWEEK_ALMDAY                              ( RTC_ALM_ALMWEEK_ALMDAY_Msk )
#define RTC_ALM_ALMWEEK_ALMDAY_0                            ( 0x1UL << RTC_ALM_ALMWEEK_ALMDAY_Pos )
#define RTC_ALM_ALMWEEK_ALMDAY_1                            ( 0x2UL << RTC_ALM_ALMWEEK_ALMDAY_Pos )
#define RTC_ALM_ALMWEEK_ALMDAY_2                            ( 0x4UL << RTC_ALM_ALMWEEK_ALMDAY_Pos )
#define RTC_ALM_ALMWEEK_ALMDAY_3                            ( 0x8UL << RTC_ALM_ALMWEEK_ALMDAY_Pos )
#define RTC_ALM_ALMWEEK_ALMDAY_4                            ( 0x10UL << RTC_ALM_ALMWEEK_ALMDAY_Pos )
#define RTC_ALM_ALMWEEK_ALMDAY_5                            ( 0x20UL << RTC_ALM_ALMWEEK_ALMDAY_Pos )
#define RTC_ALM_ALMWEEK_ALMDAY_6                            ( 0x40UL << RTC_ALM_ALMWEEK_ALMDAY_Pos )

#define RTC_ALM_ALMHOUR_Pos                                 ( 16U )
#define RTC_ALM_ALMHOUR_Msk                                 ( 0x3fUL << RTC_ALM_ALMHOUR_Pos )
#define RTC_ALM_ALMHOUR                                     ( RTC_ALM_ALMHOUR_Msk )
#define RTC_ALM_ALMHOUR_0                                   ( 0x1UL << RTC_ALM_ALMHOUR_Pos )
#define RTC_ALM_ALMHOUR_1                                   ( 0x2UL << RTC_ALM_ALMHOUR_Pos )
#define RTC_ALM_ALMHOUR_2                                   ( 0x4UL << RTC_ALM_ALMHOUR_Pos )
#define RTC_ALM_ALMHOUR_3                                   ( 0x8UL << RTC_ALM_ALMHOUR_Pos )
#define RTC_ALM_ALMHOUR_4                                   ( 0x10UL << RTC_ALM_ALMHOUR_Pos )
#define RTC_ALM_ALMHOUR_5                                   ( 0x20UL << RTC_ALM_ALMHOUR_Pos )

#define RTC_ALM_ALMMIN_Pos                                  ( 8U )
#define RTC_ALM_ALMMIN_Msk                                  ( 0x7fUL << RTC_ALM_ALMMIN_Pos )
#define RTC_ALM_ALMMIN                                      ( RTC_ALM_ALMMIN_Msk )
#define RTC_ALM_ALMMIN_0                                    ( 0x1UL << RTC_ALM_ALMMIN_Pos )
#define RTC_ALM_ALMMIN_1                                    ( 0x2UL << RTC_ALM_ALMMIN_Pos )
#define RTC_ALM_ALMMIN_2                                    ( 0x4UL << RTC_ALM_ALMMIN_Pos )
#define RTC_ALM_ALMMIN_3                                    ( 0x8UL << RTC_ALM_ALMMIN_Pos )
#define RTC_ALM_ALMMIN_4                                    ( 0x10UL << RTC_ALM_ALMMIN_Pos )
#define RTC_ALM_ALMMIN_5                                    ( 0x20UL << RTC_ALM_ALMMIN_Pos )
#define RTC_ALM_ALMMIN_6                                    ( 0x40UL << RTC_ALM_ALMMIN_Pos )

#define RTC_ALM_ALMSEC_Pos                                  ( 0U )
#define RTC_ALM_ALMSEC_Msk                                  ( 0x7fUL << RTC_ALM_ALMSEC_Pos )
#define RTC_ALM_ALMSEC                                      ( RTC_ALM_ALMSEC_Msk )
#define RTC_ALM_ALMSEC_0                                    ( 0x1UL << RTC_ALM_ALMSEC_Pos )
#define RTC_ALM_ALMSEC_1                                    ( 0x2UL << RTC_ALM_ALMSEC_Pos )
#define RTC_ALM_ALMSEC_2                                    ( 0x4UL << RTC_ALM_ALMSEC_Pos )
#define RTC_ALM_ALMSEC_3                                    ( 0x8UL << RTC_ALM_ALMSEC_Pos )
#define RTC_ALM_ALMSEC_4                                    ( 0x10UL << RTC_ALM_ALMSEC_Pos )
#define RTC_ALM_ALMSEC_5                                    ( 0x20UL << RTC_ALM_ALMSEC_Pos )
#define RTC_ALM_ALMSEC_6                                    ( 0x40UL << RTC_ALM_ALMSEC_Pos )


/***************  Bits definition for RTC_CR  **********************/

#define RTC_CR_WUCKSEL_Pos                                  ( 24U )
#define RTC_CR_WUCKSEL_Msk                                  ( 0x7UL << RTC_CR_WUCKSEL_Pos )
#define RTC_CR_WUCKSEL                                      ( RTC_CR_WUCKSEL_Msk )
#define RTC_CR_WUCKSEL_0                                    ( 0x1UL << RTC_CR_WUCKSEL_Pos )
#define RTC_CR_WUCKSEL_1                                    ( 0x2UL << RTC_CR_WUCKSEL_Pos )
#define RTC_CR_WUCKSEL_2                                    ( 0x4UL << RTC_CR_WUCKSEL_Pos )

#define RTC_CR_WUTE_Pos                                     ( 23U )
#define RTC_CR_WUTE_Msk                                     ( 0x1UL << RTC_CR_WUTE_Pos )
#define RTC_CR_WUTE                                         ( RTC_CR_WUTE_Msk )

#define RTC_CR_TAMPFLTCLK_Pos                               ( 22U )
#define RTC_CR_TAMPFLTCLK_Msk                               ( 0x1UL << RTC_CR_TAMPFLTCLK_Pos )
#define RTC_CR_TAMPFLTCLK                                   ( RTC_CR_TAMPFLTCLK_Msk )

#define RTC_CR_TS2EDGE_Pos                                  ( 21U )
#define RTC_CR_TS2EDGE_Msk                                  ( 0x1UL << RTC_CR_TS2EDGE_Pos )
#define RTC_CR_TS2EDGE                                      ( RTC_CR_TS2EDGE_Msk )

#define RTC_CR_TAMP2FLT_Pos                                 ( 19U )
#define RTC_CR_TAMP2FLT_Msk                                 ( 0x3UL << RTC_CR_TAMP2FLT_Pos )
#define RTC_CR_TAMP2FLT                                     ( RTC_CR_TAMP2FLT_Msk )
#define RTC_CR_TAMP2FLT_0                                   ( 0x1UL << RTC_CR_TAMP2FLT_Pos )
#define RTC_CR_TAMP2FLT_1                                   ( 0x2UL << RTC_CR_TAMP2FLT_Pos )

#define RTC_CR_TAMP2FLTEN_Pos                               ( 18U )
#define RTC_CR_TAMP2FLTEN_Msk                               ( 0x1UL << RTC_CR_TAMP2FLTEN_Pos )
#define RTC_CR_TAMP2FLTEN                                   ( RTC_CR_TAMP2FLTEN_Msk )

#define RTC_CR_TAMP2FCLR_Pos                                ( 17U )
#define RTC_CR_TAMP2FCLR_Msk                                ( 0x1UL << RTC_CR_TAMP2FCLR_Pos )
#define RTC_CR_TAMP2FCLR                                    ( RTC_CR_TAMP2FCLR_Msk )

#define RTC_CR_TAMP2RCLR_Pos                                ( 16U )
#define RTC_CR_TAMP2RCLR_Msk                                ( 0x1UL << RTC_CR_TAMP2RCLR_Pos )
#define RTC_CR_TAMP2RCLR                                    ( RTC_CR_TAMP2RCLR_Msk )

#define RTC_CR_TS1EDGE_Pos                                  ( 15U )
#define RTC_CR_TS1EDGE_Msk                                  ( 0x1UL << RTC_CR_TS1EDGE_Pos )
#define RTC_CR_TS1EDGE                                      ( RTC_CR_TS1EDGE_Msk )

#define RTC_CR_TAMP1FLT_Pos                                 ( 13U )
#define RTC_CR_TAMP1FLT_Msk                                 ( 0x3UL << RTC_CR_TAMP1FLT_Pos )
#define RTC_CR_TAMP1FLT                                     ( RTC_CR_TAMP1FLT_Msk )
#define RTC_CR_TAMP1FLT_0                                   ( 0x1UL << RTC_CR_TAMP1FLT_Pos )
#define RTC_CR_TAMP1FLT_1                                   ( 0x2UL << RTC_CR_TAMP1FLT_Pos )

#define RTC_CR_TAMP1FLTEN_Pos                               ( 12U )
#define RTC_CR_TAMP1FLTEN_Msk                               ( 0x1UL << RTC_CR_TAMP1FLTEN_Pos )
#define RTC_CR_TAMP1FLTEN                                   ( RTC_CR_TAMP1FLTEN_Msk )

#define RTC_CR_ALM_MSKD_Pos                                 ( 11U )
#define RTC_CR_ALM_MSKD_Msk                                 ( 0x1UL << RTC_CR_ALM_MSKD_Pos )
#define RTC_CR_ALM_MSKD                                     ( RTC_CR_ALM_MSKD_Msk )

#define RTC_CR_ALM_MSKH_Pos                                 ( 10U )
#define RTC_CR_ALM_MSKH_Msk                                 ( 0x1UL << RTC_CR_ALM_MSKH_Pos )
#define RTC_CR_ALM_MSKH                                     ( RTC_CR_ALM_MSKH_Msk )

#define RTC_CR_ALM_MSKM_Pos                                 ( 9U )
#define RTC_CR_ALM_MSKM_Msk                                 ( 0x1UL << RTC_CR_ALM_MSKM_Pos )
#define RTC_CR_ALM_MSKM                                     ( RTC_CR_ALM_MSKM_Msk )

#define RTC_CR_TAMP1FCLR_Pos                                ( 8U )
#define RTC_CR_TAMP1FCLR_Msk                                ( 0x1UL << RTC_CR_TAMP1FCLR_Pos )
#define RTC_CR_TAMP1FCLR                                    ( RTC_CR_TAMP1FCLR_Msk )

#define RTC_CR_TAMP1RCLR_Pos                                ( 7U )
#define RTC_CR_TAMP1RCLR_Msk                                ( 0x1UL << RTC_CR_TAMP1RCLR_Pos )
#define RTC_CR_TAMP1RCLR                                    ( RTC_CR_TAMP1RCLR_Msk )

#define RTC_CR_TAMP2EN_Pos                                  ( 6U )
#define RTC_CR_TAMP2EN_Msk                                  ( 0x1UL << RTC_CR_TAMP2EN_Pos )
#define RTC_CR_TAMP2EN                                      ( RTC_CR_TAMP2EN_Msk )

#define RTC_CR_TAMP1EN_Pos                                  ( 5U )
#define RTC_CR_TAMP1EN_Msk                                  ( 0x1UL << RTC_CR_TAMP1EN_Pos )
#define RTC_CR_TAMP1EN                                      ( RTC_CR_TAMP1EN_Msk )

#define RTC_CR_ALM_EN_Pos                                   ( 4U )
#define RTC_CR_ALM_EN_Msk                                   ( 0x1UL << RTC_CR_ALM_EN_Pos )
#define RTC_CR_ALM_EN                                       ( RTC_CR_ALM_EN_Msk )

#define RTC_CR_FSEL_Pos                                     ( 0U )
#define RTC_CR_FSEL_Msk                                     ( 0xfUL << RTC_CR_FSEL_Pos )
#define RTC_CR_FSEL                                         ( RTC_CR_FSEL_Msk )
#define RTC_CR_FSEL_0                                       ( 0x1UL << RTC_CR_FSEL_Pos )
#define RTC_CR_FSEL_1                                       ( 0x2UL << RTC_CR_FSEL_Pos )
#define RTC_CR_FSEL_2                                       ( 0x4UL << RTC_CR_FSEL_Pos )
#define RTC_CR_FSEL_3                                       ( 0x8UL << RTC_CR_FSEL_Pos )


/***************  Bits definition for RTC_ADJUST  **********************/

#define RTC_ADJUST_ADJSIGN_Pos                              ( 9U )
#define RTC_ADJUST_ADJSIGN_Msk                              ( 0x1UL << RTC_ADJUST_ADJSIGN_Pos )
#define RTC_ADJUST_ADJSIGN                                  ( RTC_ADJUST_ADJSIGN_Msk )

#define RTC_ADJUST_ADJVALUE_Pos                             ( 0U )
#define RTC_ADJUST_ADJVALUE_Msk                             ( 0x1ffUL << RTC_ADJUST_ADJVALUE_Pos )
#define RTC_ADJUST_ADJVALUE                                 ( RTC_ADJUST_ADJVALUE_Msk )


/***************  Bits definition for RTC_MSECCNT  **********************/

#define RTC_MSECCNT_MSCNT_Pos                               ( 0U )
#define RTC_MSECCNT_MSCNT_Msk                               ( 0x3fUL << RTC_MSECCNT_MSCNT_Pos )
#define RTC_MSECCNT_MSCNT                                   ( RTC_MSECCNT_MSCNT_Msk )
#define RTC_MSECCNT_MSCNT_0                                 ( 0x1UL << RTC_MSECCNT_MSCNT_Pos )
#define RTC_MSECCNT_MSCNT_1                                 ( 0x2UL << RTC_MSECCNT_MSCNT_Pos )
#define RTC_MSECCNT_MSCNT_2                                 ( 0x4UL << RTC_MSECCNT_MSCNT_Pos )
#define RTC_MSECCNT_MSCNT_3                                 ( 0x8UL << RTC_MSECCNT_MSCNT_Pos )
#define RTC_MSECCNT_MSCNT_4                                 ( 0x10UL << RTC_MSECCNT_MSCNT_Pos )
#define RTC_MSECCNT_MSCNT_5                                 ( 0x20UL << RTC_MSECCNT_MSCNT_Pos )


/***************  Bits definition for RTC_CLKSTAMP1  **********************/

#define RTC_CLKSTAMP1_HRSTP1_Pos                            ( 16U )
#define RTC_CLKSTAMP1_HRSTP1_Msk                            ( 0x3fUL << RTC_CLKSTAMP1_HRSTP1_Pos )
#define RTC_CLKSTAMP1_HRSTP1                                ( RTC_CLKSTAMP1_HRSTP1_Msk )
#define RTC_CLKSTAMP1_HRSTP1_0                              ( 0x1UL << RTC_CLKSTAMP1_HRSTP1_Pos )
#define RTC_CLKSTAMP1_HRSTP1_1                              ( 0x2UL << RTC_CLKSTAMP1_HRSTP1_Pos )
#define RTC_CLKSTAMP1_HRSTP1_2                              ( 0x4UL << RTC_CLKSTAMP1_HRSTP1_Pos )
#define RTC_CLKSTAMP1_HRSTP1_3                              ( 0x8UL << RTC_CLKSTAMP1_HRSTP1_Pos )
#define RTC_CLKSTAMP1_HRSTP1_4                              ( 0x10UL << RTC_CLKSTAMP1_HRSTP1_Pos )
#define RTC_CLKSTAMP1_HRSTP1_5                              ( 0x20UL << RTC_CLKSTAMP1_HRSTP1_Pos )

#define RTC_CLKSTAMP1_MINSTP1_Pos                           ( 8U )
#define RTC_CLKSTAMP1_MINSTP1_Msk                           ( 0x7fUL << RTC_CLKSTAMP1_MINSTP1_Pos )
#define RTC_CLKSTAMP1_MINSTP1                               ( RTC_CLKSTAMP1_MINSTP1_Msk )
#define RTC_CLKSTAMP1_MINSTP1_0                             ( 0x1UL << RTC_CLKSTAMP1_MINSTP1_Pos )
#define RTC_CLKSTAMP1_MINSTP1_1                             ( 0x2UL << RTC_CLKSTAMP1_MINSTP1_Pos )
#define RTC_CLKSTAMP1_MINSTP1_2                             ( 0x4UL << RTC_CLKSTAMP1_MINSTP1_Pos )
#define RTC_CLKSTAMP1_MINSTP1_3                             ( 0x8UL << RTC_CLKSTAMP1_MINSTP1_Pos )
#define RTC_CLKSTAMP1_MINSTP1_4                             ( 0x10UL << RTC_CLKSTAMP1_MINSTP1_Pos )
#define RTC_CLKSTAMP1_MINSTP1_5                             ( 0x20UL << RTC_CLKSTAMP1_MINSTP1_Pos )
#define RTC_CLKSTAMP1_MINSTP1_6                             ( 0x40UL << RTC_CLKSTAMP1_MINSTP1_Pos )

#define RTC_CLKSTAMP1_SECSTP1_Pos                           ( 0U )
#define RTC_CLKSTAMP1_SECSTP1_Msk                           ( 0x7fUL << RTC_CLKSTAMP1_SECSTP1_Pos )
#define RTC_CLKSTAMP1_SECSTP1                               ( RTC_CLKSTAMP1_SECSTP1_Msk )
#define RTC_CLKSTAMP1_SECSTP1_0                             ( 0x1UL << RTC_CLKSTAMP1_SECSTP1_Pos )
#define RTC_CLKSTAMP1_SECSTP1_1                             ( 0x2UL << RTC_CLKSTAMP1_SECSTP1_Pos )
#define RTC_CLKSTAMP1_SECSTP1_2                             ( 0x4UL << RTC_CLKSTAMP1_SECSTP1_Pos )
#define RTC_CLKSTAMP1_SECSTP1_3                             ( 0x8UL << RTC_CLKSTAMP1_SECSTP1_Pos )
#define RTC_CLKSTAMP1_SECSTP1_4                             ( 0x10UL << RTC_CLKSTAMP1_SECSTP1_Pos )
#define RTC_CLKSTAMP1_SECSTP1_5                             ( 0x20UL << RTC_CLKSTAMP1_SECSTP1_Pos )
#define RTC_CLKSTAMP1_SECSTP1_6                             ( 0x40UL << RTC_CLKSTAMP1_SECSTP1_Pos )


/***************  Bits definition for RTC_CALSTAMP1  **********************/

#define RTC_CALSTAMP1_YEARSTP1_Pos                          ( 24U )
#define RTC_CALSTAMP1_YEARSTP1_Msk                          ( 0xffUL << RTC_CALSTAMP1_YEARSTP1_Pos )
#define RTC_CALSTAMP1_YEARSTP1                              ( RTC_CALSTAMP1_YEARSTP1_Msk )
#define RTC_CALSTAMP1_YEARSTP1_0                            ( 0x1UL << RTC_CALSTAMP1_YEARSTP1_Pos )
#define RTC_CALSTAMP1_YEARSTP1_1                            ( 0x2UL << RTC_CALSTAMP1_YEARSTP1_Pos )
#define RTC_CALSTAMP1_YEARSTP1_2                            ( 0x4UL << RTC_CALSTAMP1_YEARSTP1_Pos )
#define RTC_CALSTAMP1_YEARSTP1_3                            ( 0x8UL << RTC_CALSTAMP1_YEARSTP1_Pos )
#define RTC_CALSTAMP1_YEARSTP1_4                            ( 0x10UL << RTC_CALSTAMP1_YEARSTP1_Pos )
#define RTC_CALSTAMP1_YEARSTP1_5                            ( 0x20UL << RTC_CALSTAMP1_YEARSTP1_Pos )
#define RTC_CALSTAMP1_YEARSTP1_6                            ( 0x40UL << RTC_CALSTAMP1_YEARSTP1_Pos )
#define RTC_CALSTAMP1_YEARSTP1_7                            ( 0x80UL << RTC_CALSTAMP1_YEARSTP1_Pos )

#define RTC_CALSTAMP1_MONSTP1_Pos                           ( 16U )
#define RTC_CALSTAMP1_MONSTP1_Msk                           ( 0x1fUL << RTC_CALSTAMP1_MONSTP1_Pos )
#define RTC_CALSTAMP1_MONSTP1                               ( RTC_CALSTAMP1_MONSTP1_Msk )
#define RTC_CALSTAMP1_MONSTP1_0                             ( 0x1UL << RTC_CALSTAMP1_MONSTP1_Pos )
#define RTC_CALSTAMP1_MONSTP1_1                             ( 0x2UL << RTC_CALSTAMP1_MONSTP1_Pos )
#define RTC_CALSTAMP1_MONSTP1_2                             ( 0x4UL << RTC_CALSTAMP1_MONSTP1_Pos )
#define RTC_CALSTAMP1_MONSTP1_3                             ( 0x8UL << RTC_CALSTAMP1_MONSTP1_Pos )
#define RTC_CALSTAMP1_MONSTP1_4                             ( 0x10UL << RTC_CALSTAMP1_MONSTP1_Pos )

#define RTC_CALSTAMP1_WKSTP1_Pos                            ( 8U )
#define RTC_CALSTAMP1_WKSTP1_Msk                            ( 0x7UL << RTC_CALSTAMP1_WKSTP1_Pos )
#define RTC_CALSTAMP1_WKSTP1                                ( RTC_CALSTAMP1_WKSTP1_Msk )
#define RTC_CALSTAMP1_WKSTP1_0                              ( 0x1UL << RTC_CALSTAMP1_WKSTP1_Pos )
#define RTC_CALSTAMP1_WKSTP1_1                              ( 0x2UL << RTC_CALSTAMP1_WKSTP1_Pos )
#define RTC_CALSTAMP1_WKSTP1_2                              ( 0x4UL << RTC_CALSTAMP1_WKSTP1_Pos )

#define RTC_CALSTAMP1_DAYSTP1_Pos                           ( 0U )
#define RTC_CALSTAMP1_DAYSTP1_Msk                           ( 0x3fUL << RTC_CALSTAMP1_DAYSTP1_Pos )
#define RTC_CALSTAMP1_DAYSTP1                               ( RTC_CALSTAMP1_DAYSTP1_Msk )
#define RTC_CALSTAMP1_DAYSTP1_0                             ( 0x1UL << RTC_CALSTAMP1_DAYSTP1_Pos )
#define RTC_CALSTAMP1_DAYSTP1_1                             ( 0x2UL << RTC_CALSTAMP1_DAYSTP1_Pos )
#define RTC_CALSTAMP1_DAYSTP1_2                             ( 0x4UL << RTC_CALSTAMP1_DAYSTP1_Pos )
#define RTC_CALSTAMP1_DAYSTP1_3                             ( 0x8UL << RTC_CALSTAMP1_DAYSTP1_Pos )
#define RTC_CALSTAMP1_DAYSTP1_4                             ( 0x10UL << RTC_CALSTAMP1_DAYSTP1_Pos )
#define RTC_CALSTAMP1_DAYSTP1_5                             ( 0x20UL << RTC_CALSTAMP1_DAYSTP1_Pos )


/***************  Bits definition for RTC_CLKSTAMP2  **********************/

#define RTC_CLKSTAMP2_HRSTP2_Pos                            ( 16U )
#define RTC_CLKSTAMP2_HRSTP2_Msk                            ( 0x3fUL << RTC_CLKSTAMP2_HRSTP2_Pos )
#define RTC_CLKSTAMP2_HRSTP2                                ( RTC_CLKSTAMP2_HRSTP2_Msk )
#define RTC_CLKSTAMP2_HRSTP2_0                              ( 0x1UL << RTC_CLKSTAMP2_HRSTP2_Pos )
#define RTC_CLKSTAMP2_HRSTP2_1                              ( 0x2UL << RTC_CLKSTAMP2_HRSTP2_Pos )
#define RTC_CLKSTAMP2_HRSTP2_2                              ( 0x4UL << RTC_CLKSTAMP2_HRSTP2_Pos )
#define RTC_CLKSTAMP2_HRSTP2_3                              ( 0x8UL << RTC_CLKSTAMP2_HRSTP2_Pos )
#define RTC_CLKSTAMP2_HRSTP2_4                              ( 0x10UL << RTC_CLKSTAMP2_HRSTP2_Pos )
#define RTC_CLKSTAMP2_HRSTP2_5                              ( 0x20UL << RTC_CLKSTAMP2_HRSTP2_Pos )

#define RTC_CLKSTAMP2_MINSTP2_Pos                           ( 8U )
#define RTC_CLKSTAMP2_MINSTP2_Msk                           ( 0x7fUL << RTC_CLKSTAMP2_MINSTP2_Pos )
#define RTC_CLKSTAMP2_MINSTP2                               ( RTC_CLKSTAMP2_MINSTP2_Msk )
#define RTC_CLKSTAMP2_MINSTP2_0                             ( 0x1UL << RTC_CLKSTAMP2_MINSTP2_Pos )
#define RTC_CLKSTAMP2_MINSTP2_1                             ( 0x2UL << RTC_CLKSTAMP2_MINSTP2_Pos )
#define RTC_CLKSTAMP2_MINSTP2_2                             ( 0x4UL << RTC_CLKSTAMP2_MINSTP2_Pos )
#define RTC_CLKSTAMP2_MINSTP2_3                             ( 0x8UL << RTC_CLKSTAMP2_MINSTP2_Pos )
#define RTC_CLKSTAMP2_MINSTP2_4                             ( 0x10UL << RTC_CLKSTAMP2_MINSTP2_Pos )
#define RTC_CLKSTAMP2_MINSTP2_5                             ( 0x20UL << RTC_CLKSTAMP2_MINSTP2_Pos )
#define RTC_CLKSTAMP2_MINSTP2_6                             ( 0x40UL << RTC_CLKSTAMP2_MINSTP2_Pos )

#define RTC_CLKSTAMP2_SECSTP2_Pos                           ( 0U )
#define RTC_CLKSTAMP2_SECSTP2_Msk                           ( 0x7fUL << RTC_CLKSTAMP2_SECSTP2_Pos )
#define RTC_CLKSTAMP2_SECSTP2                               ( RTC_CLKSTAMP2_SECSTP2_Msk )
#define RTC_CLKSTAMP2_SECSTP2_0                             ( 0x1UL << RTC_CLKSTAMP2_SECSTP2_Pos )
#define RTC_CLKSTAMP2_SECSTP2_1                             ( 0x2UL << RTC_CLKSTAMP2_SECSTP2_Pos )
#define RTC_CLKSTAMP2_SECSTP2_2                             ( 0x4UL << RTC_CLKSTAMP2_SECSTP2_Pos )
#define RTC_CLKSTAMP2_SECSTP2_3                             ( 0x8UL << RTC_CLKSTAMP2_SECSTP2_Pos )
#define RTC_CLKSTAMP2_SECSTP2_4                             ( 0x10UL << RTC_CLKSTAMP2_SECSTP2_Pos )
#define RTC_CLKSTAMP2_SECSTP2_5                             ( 0x20UL << RTC_CLKSTAMP2_SECSTP2_Pos )
#define RTC_CLKSTAMP2_SECSTP2_6                             ( 0x40UL << RTC_CLKSTAMP2_SECSTP2_Pos )


/***************  Bits definition for RTC_CALSTAMP2  **********************/

#define RTC_CALSTAMP2_YEARSTP2_Pos                          ( 24U )
#define RTC_CALSTAMP2_YEARSTP2_Msk                          ( 0xffUL << RTC_CALSTAMP2_YEARSTP2_Pos )
#define RTC_CALSTAMP2_YEARSTP2                              ( RTC_CALSTAMP2_YEARSTP2_Msk )
#define RTC_CALSTAMP2_YEARSTP2_0                            ( 0x1UL << RTC_CALSTAMP2_YEARSTP2_Pos )
#define RTC_CALSTAMP2_YEARSTP2_1                            ( 0x2UL << RTC_CALSTAMP2_YEARSTP2_Pos )
#define RTC_CALSTAMP2_YEARSTP2_2                            ( 0x4UL << RTC_CALSTAMP2_YEARSTP2_Pos )
#define RTC_CALSTAMP2_YEARSTP2_3                            ( 0x8UL << RTC_CALSTAMP2_YEARSTP2_Pos )
#define RTC_CALSTAMP2_YEARSTP2_4                            ( 0x10UL << RTC_CALSTAMP2_YEARSTP2_Pos )
#define RTC_CALSTAMP2_YEARSTP2_5                            ( 0x20UL << RTC_CALSTAMP2_YEARSTP2_Pos )
#define RTC_CALSTAMP2_YEARSTP2_6                            ( 0x40UL << RTC_CALSTAMP2_YEARSTP2_Pos )
#define RTC_CALSTAMP2_YEARSTP2_7                            ( 0x80UL << RTC_CALSTAMP2_YEARSTP2_Pos )

#define RTC_CALSTAMP2_MONSTP2_Pos                           ( 16U )
#define RTC_CALSTAMP2_MONSTP2_Msk                           ( 0x1fUL << RTC_CALSTAMP2_MONSTP2_Pos )
#define RTC_CALSTAMP2_MONSTP2                               ( RTC_CALSTAMP2_MONSTP2_Msk )
#define RTC_CALSTAMP2_MONSTP2_0                             ( 0x1UL << RTC_CALSTAMP2_MONSTP2_Pos )
#define RTC_CALSTAMP2_MONSTP2_1                             ( 0x2UL << RTC_CALSTAMP2_MONSTP2_Pos )
#define RTC_CALSTAMP2_MONSTP2_2                             ( 0x4UL << RTC_CALSTAMP2_MONSTP2_Pos )
#define RTC_CALSTAMP2_MONSTP2_3                             ( 0x8UL << RTC_CALSTAMP2_MONSTP2_Pos )
#define RTC_CALSTAMP2_MONSTP2_4                             ( 0x10UL << RTC_CALSTAMP2_MONSTP2_Pos )

#define RTC_CALSTAMP2_WKSTP2_Pos                            ( 8U )
#define RTC_CALSTAMP2_WKSTP2_Msk                            ( 0x7UL << RTC_CALSTAMP2_WKSTP2_Pos )
#define RTC_CALSTAMP2_WKSTP2                                ( RTC_CALSTAMP2_WKSTP2_Msk )
#define RTC_CALSTAMP2_WKSTP2_0                              ( 0x1UL << RTC_CALSTAMP2_WKSTP2_Pos )
#define RTC_CALSTAMP2_WKSTP2_1                              ( 0x2UL << RTC_CALSTAMP2_WKSTP2_Pos )
#define RTC_CALSTAMP2_WKSTP2_2                              ( 0x4UL << RTC_CALSTAMP2_WKSTP2_Pos )

#define RTC_CALSTAMP2_DAYSTP2_Pos                           ( 0U )
#define RTC_CALSTAMP2_DAYSTP2_Msk                           ( 0x3fUL << RTC_CALSTAMP2_DAYSTP2_Pos )
#define RTC_CALSTAMP2_DAYSTP2                               ( RTC_CALSTAMP2_DAYSTP2_Msk )
#define RTC_CALSTAMP2_DAYSTP2_0                             ( 0x1UL << RTC_CALSTAMP2_DAYSTP2_Pos )
#define RTC_CALSTAMP2_DAYSTP2_1                             ( 0x2UL << RTC_CALSTAMP2_DAYSTP2_Pos )
#define RTC_CALSTAMP2_DAYSTP2_2                             ( 0x4UL << RTC_CALSTAMP2_DAYSTP2_Pos )
#define RTC_CALSTAMP2_DAYSTP2_3                             ( 0x8UL << RTC_CALSTAMP2_DAYSTP2_Pos )
#define RTC_CALSTAMP2_DAYSTP2_4                             ( 0x10UL << RTC_CALSTAMP2_DAYSTP2_Pos )
#define RTC_CALSTAMP2_DAYSTP2_5                             ( 0x20UL << RTC_CALSTAMP2_DAYSTP2_Pos )


/***************  Bits definition for RTC_WUTR  **********************/

#define RTC_WUTR_WUT_Pos                                    ( 0U )
#define RTC_WUTR_WUT_Msk                                    ( 0xffffUL << RTC_WUTR_WUT_Pos )
#define RTC_WUTR_WUT                                        ( RTC_WUTR_WUT_Msk )


/***************  Bits definition for RTC_BAKUPx  **********************/

#define RTC_BAKUPX_BAKUP_Pos                                ( 0U )
#define RTC_BAKUPX_BAKUP_Msk                                ( 0xffffffffUL << RTC_BAKUPX_BAKUP_Pos )
#define RTC_BAKUPX_BAKUP                                    ( RTC_BAKUPX_BAKUP_Msk )


/***************  Bits definition for WDT_LOAD  **********************/

#define WDT_LOAD_LOAD_Pos                                   ( 0U )
#define WDT_LOAD_LOAD_Msk                                   ( 0xffffffffUL << WDT_LOAD_LOAD_Pos )
#define WDT_LOAD_LOAD                                       ( WDT_LOAD_LOAD_Msk )


/***************  Bits definition for WDT_COUNT  **********************/

#define WDT_COUNT_COUNT_Pos                                 ( 0U )
#define WDT_COUNT_COUNT_Msk                                 ( 0xffffffffUL << WDT_COUNT_COUNT_Pos )
#define WDT_COUNT_COUNT                                     ( WDT_COUNT_COUNT_Msk )


/***************  Bits definition for WDT_CTRL  **********************/

#define WDT_CTRL_EN_Pos                                     ( 7U )
#define WDT_CTRL_EN_Msk                                     ( 0x1UL << WDT_CTRL_EN_Pos )
#define WDT_CTRL_EN                                         ( WDT_CTRL_EN_Msk )

#define WDT_CTRL_MODE_Pos                                   ( 6U )
#define WDT_CTRL_MODE_Msk                                   ( 0x1UL << WDT_CTRL_MODE_Pos )
#define WDT_CTRL_MODE                                       ( WDT_CTRL_MODE_Msk )

#define WDT_CTRL_INTEN_Pos                                  ( 4U )
#define WDT_CTRL_INTEN_Msk                                  ( 0x1UL << WDT_CTRL_INTEN_Pos )
#define WDT_CTRL_INTEN                                      ( WDT_CTRL_INTEN_Msk )

#define WDT_CTRL_DIVISOR_Pos                                ( 0U )
#define WDT_CTRL_DIVISOR_Msk                                ( 0x7UL << WDT_CTRL_DIVISOR_Pos )
#define WDT_CTRL_DIVISOR                                    ( WDT_CTRL_DIVISOR_Msk )
#define WDT_CTRL_DIVISOR_0                                  ( 0x1UL << WDT_CTRL_DIVISOR_Pos )
#define WDT_CTRL_DIVISOR_1                                  ( 0x2UL << WDT_CTRL_DIVISOR_Pos )
#define WDT_CTRL_DIVISOR_2                                  ( 0x4UL << WDT_CTRL_DIVISOR_Pos )


/***************  Bits definition for WDT_FEED  **********************/

#define WDT_FEED_FEED_Pos                                   ( 0U )
#define WDT_FEED_FEED_Msk                                   ( 0xffffffffUL << WDT_FEED_FEED_Pos )
#define WDT_FEED_FEED                                       ( WDT_FEED_FEED_Msk )


/***************  Bits definition for WDT_INTCLRTIME  **********************/

#define WDT_INTCLRTIME_INTCLRT_Pos                          ( 0U )
#define WDT_INTCLRTIME_INTCLRT_Msk                          ( 0xffffUL << WDT_INTCLRTIME_INTCLRT_Pos )
#define WDT_INTCLRTIME_INTCLRT                              ( WDT_INTCLRTIME_INTCLRT_Msk )


/***************  Bits definition for WDT_RIS  **********************/

#define WDT_RIS_WDT_RIS_Pos                                 ( 0U )
#define WDT_RIS_WDT_RIS_Msk                                 ( 0x1UL << WDT_RIS_WDT_RIS_Pos )
#define WDT_RIS_WDT_RIS                                     ( WDT_RIS_WDT_RIS_Msk )


/***************  Bits definition for IWDT_CMDR  **********************/

#define IWDT_CMDR_CMD_Pos                                   ( 0U )
#define IWDT_CMDR_CMD_Msk                                   ( 0xffffUL << IWDT_CMDR_CMD_Pos )
#define IWDT_CMDR_CMD                                       ( IWDT_CMDR_CMD_Msk )


/***************  Bits definition for IWDT_PR  **********************/

#define IWDT_PR_PR_Pos                                      ( 0U )
#define IWDT_PR_PR_Msk                                      ( 0x7UL << IWDT_PR_PR_Pos )
#define IWDT_PR_PR                                          ( IWDT_PR_PR_Msk )
#define IWDT_PR_PR_0                                        ( 0x1UL << IWDT_PR_PR_Pos )
#define IWDT_PR_PR_1                                        ( 0x2UL << IWDT_PR_PR_Pos )
#define IWDT_PR_PR_2                                        ( 0x4UL << IWDT_PR_PR_Pos )


/***************  Bits definition for IWDT_RLR  **********************/

#define IWDT_RLR_PL_Pos                                     ( 0U )
#define IWDT_RLR_PL_Msk                                     ( 0xfffUL << IWDT_RLR_PL_Pos )
#define IWDT_RLR_PL                                         ( IWDT_RLR_PL_Msk )


/***************  Bits definition for IWDT_SR  **********************/

#define IWDT_SR_RLF_Pos                                     ( 4U )
#define IWDT_SR_RLF_Msk                                     ( 0x1UL << IWDT_SR_RLF_Pos )
#define IWDT_SR_RLF                                         ( IWDT_SR_RLF_Msk )

#define IWDT_SR_WTU_Pos                                     ( 3U )
#define IWDT_SR_WTU_Msk                                     ( 0x1UL << IWDT_SR_WTU_Pos )
#define IWDT_SR_WTU                                         ( IWDT_SR_WTU_Msk )

#define IWDT_SR_WVU_Pos                                     ( 2U )
#define IWDT_SR_WVU_Msk                                     ( 0x1UL << IWDT_SR_WVU_Pos )
#define IWDT_SR_WVU                                         ( IWDT_SR_WVU_Msk )

#define IWDT_SR_RVU_Pos                                     ( 1U )
#define IWDT_SR_RVU_Msk                                     ( 0x1UL << IWDT_SR_RVU_Pos )
#define IWDT_SR_RVU                                         ( IWDT_SR_RVU_Msk )

#define IWDT_SR_PVU_Pos                                     ( 0U )
#define IWDT_SR_PVU_Msk                                     ( 0x1UL << IWDT_SR_PVU_Pos )
#define IWDT_SR_PVU                                         ( IWDT_SR_PVU_Msk )


/***************  Bits definition for IWDT_WINR  **********************/

#define IWDT_WINR_WIN_Pos                                   ( 0U )
#define IWDT_WINR_WIN_Msk                                   ( 0xfffUL << IWDT_WINR_WIN_Pos )
#define IWDT_WINR_WIN                                       ( IWDT_WINR_WIN_Msk )


/***************  Bits definition for IWDT_WUTR  **********************/

#define IWDT_WUTR_WUT_Pos                                   ( 0U )
#define IWDT_WUTR_WUT_Msk                                   ( 0xfffUL << IWDT_WUTR_WUT_Pos )
#define IWDT_WUTR_WUT                                       ( IWDT_WUTR_WUT_Msk )


/***************  Bits definition for ADC_SR  **********************/

#define ADC_SR_AFE_EOC_Pos                                  ( 8U )
#define ADC_SR_AFE_EOC_Msk                                  ( 0x1UL << ADC_SR_AFE_EOC_Pos )
#define ADC_SR_AFE_EOC                                      ( ADC_SR_AFE_EOC_Msk )

#define ADC_SR_AWD_Pos                                      ( 7U )
#define ADC_SR_AWD_Msk                                      ( 0x1UL << ADC_SR_AWD_Pos )
#define ADC_SR_AWD                                          ( ADC_SR_AWD_Msk )

#define ADC_SR_JEOG_Pos                                     ( 6U )
#define ADC_SR_JEOG_Msk                                     ( 0x1UL << ADC_SR_JEOG_Pos )
#define ADC_SR_JEOG                                         ( ADC_SR_JEOG_Msk )

#define ADC_SR_JEOC_Pos                                     ( 5U )
#define ADC_SR_JEOC_Msk                                     ( 0x1UL << ADC_SR_JEOC_Pos )
#define ADC_SR_JEOC                                         ( ADC_SR_JEOC_Msk )

#define ADC_SR_OVERF_Pos                                    ( 4U )
#define ADC_SR_OVERF_Msk                                    ( 0x1UL << ADC_SR_OVERF_Pos )
#define ADC_SR_OVERF                                        ( ADC_SR_OVERF_Msk )

#define ADC_SR_EOG_Pos                                      ( 3U )
#define ADC_SR_EOG_Msk                                      ( 0x1UL << ADC_SR_EOG_Pos )
#define ADC_SR_EOG                                          ( ADC_SR_EOG_Msk )

#define ADC_SR_EOC_Pos                                      ( 2U )
#define ADC_SR_EOC_Msk                                      ( 0x1UL << ADC_SR_EOC_Pos )
#define ADC_SR_EOC                                          ( ADC_SR_EOC_Msk )

#define ADC_SR_EOSMP_Pos                                    ( 1U )
#define ADC_SR_EOSMP_Msk                                    ( 0x1UL << ADC_SR_EOSMP_Pos )
#define ADC_SR_EOSMP                                        ( ADC_SR_EOSMP_Msk )

#define ADC_SR_ADRDY_Pos                                    ( 0U )
#define ADC_SR_ADRDY_Msk                                    ( 0x1UL << ADC_SR_ADRDY_Pos )
#define ADC_SR_ADRDY                                        ( ADC_SR_ADRDY_Msk )


/***************  Bits definition for ADC_IE  **********************/

#define ADC_IE_AWDIE_Pos                                    ( 7U )
#define ADC_IE_AWDIE_Msk                                    ( 0x1UL << ADC_IE_AWDIE_Pos )
#define ADC_IE_AWDIE                                        ( ADC_IE_AWDIE_Msk )

#define ADC_IE_JEOGIE_Pos                                   ( 6U )
#define ADC_IE_JEOGIE_Msk                                   ( 0x1UL << ADC_IE_JEOGIE_Pos )
#define ADC_IE_JEOGIE                                       ( ADC_IE_JEOGIE_Msk )

#define ADC_IE_JEOCIE_Pos                                   ( 5U )
#define ADC_IE_JEOCIE_Msk                                   ( 0x1UL << ADC_IE_JEOCIE_Pos )
#define ADC_IE_JEOCIE                                       ( ADC_IE_JEOCIE_Msk )

#define ADC_IE_OVERFIE_Pos                                  ( 4U )
#define ADC_IE_OVERFIE_Msk                                  ( 0x1UL << ADC_IE_OVERFIE_Pos )
#define ADC_IE_OVERFIE                                      ( ADC_IE_OVERFIE_Msk )

#define ADC_IE_EOGIE_Pos                                    ( 3U )
#define ADC_IE_EOGIE_Msk                                    ( 0x1UL << ADC_IE_EOGIE_Pos )
#define ADC_IE_EOGIE                                        ( ADC_IE_EOGIE_Msk )

#define ADC_IE_EOCIE_Pos                                    ( 2U )
#define ADC_IE_EOCIE_Msk                                    ( 0x1UL << ADC_IE_EOCIE_Pos )
#define ADC_IE_EOCIE                                        ( ADC_IE_EOCIE_Msk )

#define ADC_IE_EOSMPIE_Pos                                  ( 1U )
#define ADC_IE_EOSMPIE_Msk                                  ( 0x1UL << ADC_IE_EOSMPIE_Pos )
#define ADC_IE_EOSMPIE                                      ( ADC_IE_EOSMPIE_Msk )


/***************  Bits definition for ADC_CR1  **********************/

#define ADC_CR1_DISCNUM_Pos                                 ( 28U )
#define ADC_CR1_DISCNUM_Msk                                 ( 0x7UL << ADC_CR1_DISCNUM_Pos )
#define ADC_CR1_DISCNUM                                     ( ADC_CR1_DISCNUM_Msk )
#define ADC_CR1_DISCNUM_0                                   ( 0x1UL << ADC_CR1_DISCNUM_Pos )
#define ADC_CR1_DISCNUM_1                                   ( 0x2UL << ADC_CR1_DISCNUM_Pos )
#define ADC_CR1_DISCNUM_2                                   ( 0x4UL << ADC_CR1_DISCNUM_Pos )

#define ADC_CR1_JDISCEN_Pos                                 ( 27U )
#define ADC_CR1_JDISCEN_Msk                                 ( 0x1UL << ADC_CR1_JDISCEN_Pos )
#define ADC_CR1_JDISCEN                                     ( ADC_CR1_JDISCEN_Msk )

#define ADC_CR1_DISCEN_Pos                                  ( 26U )
#define ADC_CR1_DISCEN_Msk                                  ( 0x1UL << ADC_CR1_DISCEN_Pos )
#define ADC_CR1_DISCEN                                      ( ADC_CR1_DISCEN_Msk )

#define ADC_CR1_JAUTO_Pos                                   ( 25U )
#define ADC_CR1_JAUTO_Msk                                   ( 0x1UL << ADC_CR1_JAUTO_Pos )
#define ADC_CR1_JAUTO                                       ( ADC_CR1_JAUTO_Msk )

#define ADC_CR1_CONT_Pos                                    ( 24U )
#define ADC_CR1_CONT_Msk                                    ( 0x1UL << ADC_CR1_CONT_Pos )
#define ADC_CR1_CONT                                        ( ADC_CR1_CONT_Msk )

#define ADC_CR1_SWSTART_Pos                                 ( 23U )
#define ADC_CR1_SWSTART_Msk                                 ( 0x1UL << ADC_CR1_SWSTART_Pos )
#define ADC_CR1_SWSTART                                     ( ADC_CR1_SWSTART_Msk )

#define ADC_CR1_JSWSTART_Pos                                ( 22U )
#define ADC_CR1_JSWSTART_Msk                                ( 0x1UL << ADC_CR1_JSWSTART_Pos )
#define ADC_CR1_JSWSTART                                    ( ADC_CR1_JSWSTART_Msk )

#define ADC_CR1_EXTSEL_Pos                                  ( 16U )
#define ADC_CR1_EXTSEL_Msk                                  ( 0x1fUL << ADC_CR1_EXTSEL_Pos )
#define ADC_CR1_EXTSEL                                      ( ADC_CR1_EXTSEL_Msk )
#define ADC_CR1_EXTSEL_0                                    ( 0x1UL << ADC_CR1_EXTSEL_Pos )
#define ADC_CR1_EXTSEL_1                                    ( 0x2UL << ADC_CR1_EXTSEL_Pos )
#define ADC_CR1_EXTSEL_2                                    ( 0x4UL << ADC_CR1_EXTSEL_Pos )
#define ADC_CR1_EXTSEL_3                                    ( 0x8UL << ADC_CR1_EXTSEL_Pos )
#define ADC_CR1_EXTSEL_4                                    ( 0x10UL << ADC_CR1_EXTSEL_Pos )

#define ADC_CR1_EXTEN_Pos                                   ( 14U )
#define ADC_CR1_EXTEN_Msk                                   ( 0x3UL << ADC_CR1_EXTEN_Pos )
#define ADC_CR1_EXTEN                                       ( ADC_CR1_EXTEN_Msk )
#define ADC_CR1_EXTEN_0                                     ( 0x1UL << ADC_CR1_EXTEN_Pos )
#define ADC_CR1_EXTEN_1                                     ( 0x2UL << ADC_CR1_EXTEN_Pos )

#define ADC_CR1_DMA_Pos                                     ( 13U )
#define ADC_CR1_DMA_Msk                                     ( 0x1UL << ADC_CR1_DMA_Pos )
#define ADC_CR1_DMA                                         ( ADC_CR1_DMA_Msk )

#define ADC_CR1_AWDEN_Pos                                   ( 12U )
#define ADC_CR1_AWDEN_Msk                                   ( 0x1UL << ADC_CR1_AWDEN_Pos )
#define ADC_CR1_AWDEN                                       ( ADC_CR1_AWDEN_Msk )

#define ADC_CR1_JAWDEN_Pos                                  ( 11U )
#define ADC_CR1_JAWDEN_Msk                                  ( 0x1UL << ADC_CR1_JAWDEN_Pos )
#define ADC_CR1_JAWDEN                                      ( ADC_CR1_JAWDEN_Msk )

#define ADC_CR1_AWDSGL_Pos                                  ( 10U )
#define ADC_CR1_AWDSGL_Msk                                  ( 0x1UL << ADC_CR1_AWDSGL_Pos )
#define ADC_CR1_AWDSGL                                      ( ADC_CR1_AWDSGL_Msk )

#define ADC_CR1_AWDJCH_Pos                                  ( 5U )
#define ADC_CR1_AWDJCH_Msk                                  ( 0x1fUL << ADC_CR1_AWDJCH_Pos )
#define ADC_CR1_AWDJCH                                      ( ADC_CR1_AWDJCH_Msk )
#define ADC_CR1_AWDJCH_0                                    ( 0x1UL << ADC_CR1_AWDJCH_Pos )
#define ADC_CR1_AWDJCH_1                                    ( 0x2UL << ADC_CR1_AWDJCH_Pos )
#define ADC_CR1_AWDJCH_2                                    ( 0x4UL << ADC_CR1_AWDJCH_Pos )
#define ADC_CR1_AWDJCH_3                                    ( 0x8UL << ADC_CR1_AWDJCH_Pos )
#define ADC_CR1_AWDJCH_4                                    ( 0x10UL << ADC_CR1_AWDJCH_Pos )

#define ADC_CR1_AWDCH_Pos                                   ( 0U )
#define ADC_CR1_AWDCH_Msk                                   ( 0x1fUL << ADC_CR1_AWDCH_Pos )
#define ADC_CR1_AWDCH                                       ( ADC_CR1_AWDCH_Msk )
#define ADC_CR1_AWDCH_0                                     ( 0x1UL << ADC_CR1_AWDCH_Pos )
#define ADC_CR1_AWDCH_1                                     ( 0x2UL << ADC_CR1_AWDCH_Pos )
#define ADC_CR1_AWDCH_2                                     ( 0x4UL << ADC_CR1_AWDCH_Pos )
#define ADC_CR1_AWDCH_3                                     ( 0x8UL << ADC_CR1_AWDCH_Pos )
#define ADC_CR1_AWDCH_4                                     ( 0x10UL << ADC_CR1_AWDCH_Pos )


/***************  Bits definition for ADC_CR2  **********************/

#define ADC_CR2_ADCCAL_Pos                                  ( 31U )
#define ADC_CR2_ADCCAL_Msk                                  ( 0x1UL << ADC_CR2_ADCCAL_Pos )
#define ADC_CR2_ADCCAL                                      ( ADC_CR2_ADCCAL_Msk )

#define ADC_CR2_ADCCALDIF_Pos                               ( 30U )
#define ADC_CR2_ADCCALDIF_Msk                               ( 0x1UL << ADC_CR2_ADCCALDIF_Pos )
#define ADC_CR2_ADCCALDIF                                   ( ADC_CR2_ADCCALDIF_Msk )

#define ADC_CR2_ADCRSTN_Pos                                 ( 29U )
#define ADC_CR2_ADCRSTN_Msk                                 ( 0x1UL << ADC_CR2_ADCRSTN_Pos )
#define ADC_CR2_ADCRSTN                                     ( ADC_CR2_ADCRSTN_Msk )

#define ADC_CR2_ADCVREGEN_Pos                               ( 28U )
#define ADC_CR2_ADCVREGEN_Msk                               ( 0x1UL << ADC_CR2_ADCVREGEN_Pos )
#define ADC_CR2_ADCVREGEN                                   ( ADC_CR2_ADCVREGEN_Msk )

#define ADC_CR2_JOVSE_Pos                                   ( 25U )
#define ADC_CR2_JOVSE_Msk                                   ( 0x1UL << ADC_CR2_JOVSE_Pos )
#define ADC_CR2_JOVSE                                       ( ADC_CR2_JOVSE_Msk )

#define ADC_CR2_TROVS_Pos                                   ( 24U )
#define ADC_CR2_TROVS_Msk                                   ( 0x1UL << ADC_CR2_TROVS_Pos )
#define ADC_CR2_TROVS                                       ( ADC_CR2_TROVS_Msk )

#define ADC_CR2_OVSS_Pos                                    ( 20U )
#define ADC_CR2_OVSS_Msk                                    ( 0xfUL << ADC_CR2_OVSS_Pos )
#define ADC_CR2_OVSS                                        ( ADC_CR2_OVSS_Msk )
#define ADC_CR2_OVSS_0                                      ( 0x1UL << ADC_CR2_OVSS_Pos )
#define ADC_CR2_OVSS_1                                      ( 0x2UL << ADC_CR2_OVSS_Pos )
#define ADC_CR2_OVSS_2                                      ( 0x4UL << ADC_CR2_OVSS_Pos )
#define ADC_CR2_OVSS_3                                      ( 0x8UL << ADC_CR2_OVSS_Pos )

#define ADC_CR2_OVSR_Pos                                    ( 17U )
#define ADC_CR2_OVSR_Msk                                    ( 0x7UL << ADC_CR2_OVSR_Pos )
#define ADC_CR2_OVSR                                        ( ADC_CR2_OVSR_Msk )
#define ADC_CR2_OVSR_0                                      ( 0x1UL << ADC_CR2_OVSR_Pos )
#define ADC_CR2_OVSR_1                                      ( 0x2UL << ADC_CR2_OVSR_Pos )
#define ADC_CR2_OVSR_2                                      ( 0x4UL << ADC_CR2_OVSR_Pos )

#define ADC_CR2_OVSE_Pos                                    ( 16U )
#define ADC_CR2_OVSE_Msk                                    ( 0x1UL << ADC_CR2_OVSE_Pos )
#define ADC_CR2_OVSE                                        ( ADC_CR2_OVSE_Msk )

#define ADC_CR2_TRIMLDO12_Pos                               ( 6U )
#define ADC_CR2_TRIMLDO12_Msk                               ( 0xfUL << ADC_CR2_TRIMLDO12_Pos )
#define ADC_CR2_TRIMLDO12                                   ( ADC_CR2_TRIMLDO12_Msk )
#define ADC_CR2_TRIMLDO12_0                                 ( 0x1UL << ADC_CR2_TRIMLDO12_Pos )
#define ADC_CR2_TRIMLDO12_1                                 ( 0x2UL << ADC_CR2_TRIMLDO12_Pos )
#define ADC_CR2_TRIMLDO12_2                                 ( 0x4UL << ADC_CR2_TRIMLDO12_Pos )
#define ADC_CR2_TRIMLDO12_3                                 ( 0x8UL << ADC_CR2_TRIMLDO12_Pos )

#define ADC_CR2_RES_Pos                                     ( 4U )
#define ADC_CR2_RES_Msk                                     ( 0x3UL << ADC_CR2_RES_Pos )
#define ADC_CR2_RES                                         ( ADC_CR2_RES_Msk )
#define ADC_CR2_RES_0                                       ( 0x1UL << ADC_CR2_RES_Pos )
#define ADC_CR2_RES_1                                       ( 0x2UL << ADC_CR2_RES_Pos )

#define ADC_CR2_ALIGN_Pos                                   ( 3U )
#define ADC_CR2_ALIGN_Msk                                   ( 0x1UL << ADC_CR2_ALIGN_Pos )
#define ADC_CR2_ALIGN                                       ( ADC_CR2_ALIGN_Msk )

#define ADC_CR2_STP_Pos                                     ( 2U )
#define ADC_CR2_STP_Msk                                     ( 0x1UL << ADC_CR2_STP_Pos )
#define ADC_CR2_STP                                         ( ADC_CR2_STP_Msk )

#define ADC_CR2_OVRMOD_Pos                                  ( 1U )
#define ADC_CR2_OVRMOD_Msk                                  ( 0x1UL << ADC_CR2_OVRMOD_Pos )
#define ADC_CR2_OVRMOD                                      ( ADC_CR2_OVRMOD_Msk )

#define ADC_CR2_EN_Pos                                      ( 0U )
#define ADC_CR2_EN_Msk                                      ( 0x1UL << ADC_CR2_EN_Pos )
#define ADC_CR2_EN                                          ( ADC_CR2_EN_Msk )


/***************  Bits definition for ADC_SMPR1  **********************/

#define ADC_SMPR1_SMP7_Pos                                  ( 28U )
#define ADC_SMPR1_SMP7_Msk                                  ( 0xfUL << ADC_SMPR1_SMP7_Pos )
#define ADC_SMPR1_SMP7                                      ( ADC_SMPR1_SMP7_Msk )
#define ADC_SMPR1_SMP7_0                                    ( 0x1UL << ADC_SMPR1_SMP7_Pos )
#define ADC_SMPR1_SMP7_1                                    ( 0x2UL << ADC_SMPR1_SMP7_Pos )
#define ADC_SMPR1_SMP7_2                                    ( 0x4UL << ADC_SMPR1_SMP7_Pos )
#define ADC_SMPR1_SMP7_3                                    ( 0x8UL << ADC_SMPR1_SMP7_Pos )

#define ADC_SMPR1_SMP6_Pos                                  ( 24U )
#define ADC_SMPR1_SMP6_Msk                                  ( 0xfUL << ADC_SMPR1_SMP6_Pos )
#define ADC_SMPR1_SMP6                                      ( ADC_SMPR1_SMP6_Msk )
#define ADC_SMPR1_SMP6_0                                    ( 0x1UL << ADC_SMPR1_SMP6_Pos )
#define ADC_SMPR1_SMP6_1                                    ( 0x2UL << ADC_SMPR1_SMP6_Pos )
#define ADC_SMPR1_SMP6_2                                    ( 0x4UL << ADC_SMPR1_SMP6_Pos )
#define ADC_SMPR1_SMP6_3                                    ( 0x8UL << ADC_SMPR1_SMP6_Pos )

#define ADC_SMPR1_SMP5_Pos                                  ( 20U )
#define ADC_SMPR1_SMP5_Msk                                  ( 0xfUL << ADC_SMPR1_SMP5_Pos )
#define ADC_SMPR1_SMP5                                      ( ADC_SMPR1_SMP5_Msk )
#define ADC_SMPR1_SMP5_0                                    ( 0x1UL << ADC_SMPR1_SMP5_Pos )
#define ADC_SMPR1_SMP5_1                                    ( 0x2UL << ADC_SMPR1_SMP5_Pos )
#define ADC_SMPR1_SMP5_2                                    ( 0x4UL << ADC_SMPR1_SMP5_Pos )
#define ADC_SMPR1_SMP5_3                                    ( 0x8UL << ADC_SMPR1_SMP5_Pos )

#define ADC_SMPR1_SMP4_Pos                                  ( 16U )
#define ADC_SMPR1_SMP4_Msk                                  ( 0xfUL << ADC_SMPR1_SMP4_Pos )
#define ADC_SMPR1_SMP4                                      ( ADC_SMPR1_SMP4_Msk )
#define ADC_SMPR1_SMP4_0                                    ( 0x1UL << ADC_SMPR1_SMP4_Pos )
#define ADC_SMPR1_SMP4_1                                    ( 0x2UL << ADC_SMPR1_SMP4_Pos )
#define ADC_SMPR1_SMP4_2                                    ( 0x4UL << ADC_SMPR1_SMP4_Pos )
#define ADC_SMPR1_SMP4_3                                    ( 0x8UL << ADC_SMPR1_SMP4_Pos )

#define ADC_SMPR1_SMP3_Pos                                  ( 12U )
#define ADC_SMPR1_SMP3_Msk                                  ( 0xfUL << ADC_SMPR1_SMP3_Pos )
#define ADC_SMPR1_SMP3                                      ( ADC_SMPR1_SMP3_Msk )
#define ADC_SMPR1_SMP3_0                                    ( 0x1UL << ADC_SMPR1_SMP3_Pos )
#define ADC_SMPR1_SMP3_1                                    ( 0x2UL << ADC_SMPR1_SMP3_Pos )
#define ADC_SMPR1_SMP3_2                                    ( 0x4UL << ADC_SMPR1_SMP3_Pos )
#define ADC_SMPR1_SMP3_3                                    ( 0x8UL << ADC_SMPR1_SMP3_Pos )

#define ADC_SMPR1_SMP2_Pos                                  ( 8U )
#define ADC_SMPR1_SMP2_Msk                                  ( 0xfUL << ADC_SMPR1_SMP2_Pos )
#define ADC_SMPR1_SMP2                                      ( ADC_SMPR1_SMP2_Msk )
#define ADC_SMPR1_SMP2_0                                    ( 0x1UL << ADC_SMPR1_SMP2_Pos )
#define ADC_SMPR1_SMP2_1                                    ( 0x2UL << ADC_SMPR1_SMP2_Pos )
#define ADC_SMPR1_SMP2_2                                    ( 0x4UL << ADC_SMPR1_SMP2_Pos )
#define ADC_SMPR1_SMP2_3                                    ( 0x8UL << ADC_SMPR1_SMP2_Pos )

#define ADC_SMPR1_SMP1_Pos                                  ( 4U )
#define ADC_SMPR1_SMP1_Msk                                  ( 0xfUL << ADC_SMPR1_SMP1_Pos )
#define ADC_SMPR1_SMP1                                      ( ADC_SMPR1_SMP1_Msk )
#define ADC_SMPR1_SMP1_0                                    ( 0x1UL << ADC_SMPR1_SMP1_Pos )
#define ADC_SMPR1_SMP1_1                                    ( 0x2UL << ADC_SMPR1_SMP1_Pos )
#define ADC_SMPR1_SMP1_2                                    ( 0x4UL << ADC_SMPR1_SMP1_Pos )
#define ADC_SMPR1_SMP1_3                                    ( 0x8UL << ADC_SMPR1_SMP1_Pos )

#define ADC_SMPR1_SMP0_Pos                                  ( 0U )
#define ADC_SMPR1_SMP0_Msk                                  ( 0xfUL << ADC_SMPR1_SMP0_Pos )
#define ADC_SMPR1_SMP0                                      ( ADC_SMPR1_SMP0_Msk )
#define ADC_SMPR1_SMP0_0                                    ( 0x1UL << ADC_SMPR1_SMP0_Pos )
#define ADC_SMPR1_SMP0_1                                    ( 0x2UL << ADC_SMPR1_SMP0_Pos )
#define ADC_SMPR1_SMP0_2                                    ( 0x4UL << ADC_SMPR1_SMP0_Pos )
#define ADC_SMPR1_SMP0_3                                    ( 0x8UL << ADC_SMPR1_SMP0_Pos )


/***************  Bits definition for ADC_SMPR2  **********************/

#define ADC_SMPR2_SMP15_Pos                                 ( 28U )
#define ADC_SMPR2_SMP15_Msk                                 ( 0xfUL << ADC_SMPR2_SMP15_Pos )
#define ADC_SMPR2_SMP15                                     ( ADC_SMPR2_SMP15_Msk )
#define ADC_SMPR2_SMP15_0                                   ( 0x1UL << ADC_SMPR2_SMP15_Pos )
#define ADC_SMPR2_SMP15_1                                   ( 0x2UL << ADC_SMPR2_SMP15_Pos )
#define ADC_SMPR2_SMP15_2                                   ( 0x4UL << ADC_SMPR2_SMP15_Pos )
#define ADC_SMPR2_SMP15_3                                   ( 0x8UL << ADC_SMPR2_SMP15_Pos )

#define ADC_SMPR2_SMP14_Pos                                 ( 24U )
#define ADC_SMPR2_SMP14_Msk                                 ( 0xfUL << ADC_SMPR2_SMP14_Pos )
#define ADC_SMPR2_SMP14                                     ( ADC_SMPR2_SMP14_Msk )
#define ADC_SMPR2_SMP14_0                                   ( 0x1UL << ADC_SMPR2_SMP14_Pos )
#define ADC_SMPR2_SMP14_1                                   ( 0x2UL << ADC_SMPR2_SMP14_Pos )
#define ADC_SMPR2_SMP14_2                                   ( 0x4UL << ADC_SMPR2_SMP14_Pos )
#define ADC_SMPR2_SMP14_3                                   ( 0x8UL << ADC_SMPR2_SMP14_Pos )

#define ADC_SMPR2_SMP13_Pos                                 ( 20U )
#define ADC_SMPR2_SMP13_Msk                                 ( 0xfUL << ADC_SMPR2_SMP13_Pos )
#define ADC_SMPR2_SMP13                                     ( ADC_SMPR2_SMP13_Msk )
#define ADC_SMPR2_SMP13_0                                   ( 0x1UL << ADC_SMPR2_SMP13_Pos )
#define ADC_SMPR2_SMP13_1                                   ( 0x2UL << ADC_SMPR2_SMP13_Pos )
#define ADC_SMPR2_SMP13_2                                   ( 0x4UL << ADC_SMPR2_SMP13_Pos )
#define ADC_SMPR2_SMP13_3                                   ( 0x8UL << ADC_SMPR2_SMP13_Pos )

#define ADC_SMPR2_SMP12_Pos                                 ( 16U )
#define ADC_SMPR2_SMP12_Msk                                 ( 0xfUL << ADC_SMPR2_SMP12_Pos )
#define ADC_SMPR2_SMP12                                     ( ADC_SMPR2_SMP12_Msk )
#define ADC_SMPR2_SMP12_0                                   ( 0x1UL << ADC_SMPR2_SMP12_Pos )
#define ADC_SMPR2_SMP12_1                                   ( 0x2UL << ADC_SMPR2_SMP12_Pos )
#define ADC_SMPR2_SMP12_2                                   ( 0x4UL << ADC_SMPR2_SMP12_Pos )
#define ADC_SMPR2_SMP12_3                                   ( 0x8UL << ADC_SMPR2_SMP12_Pos )

#define ADC_SMPR2_SMP11_Pos                                 ( 12U )
#define ADC_SMPR2_SMP11_Msk                                 ( 0xfUL << ADC_SMPR2_SMP11_Pos )
#define ADC_SMPR2_SMP11                                     ( ADC_SMPR2_SMP11_Msk )
#define ADC_SMPR2_SMP11_0                                   ( 0x1UL << ADC_SMPR2_SMP11_Pos )
#define ADC_SMPR2_SMP11_1                                   ( 0x2UL << ADC_SMPR2_SMP11_Pos )
#define ADC_SMPR2_SMP11_2                                   ( 0x4UL << ADC_SMPR2_SMP11_Pos )
#define ADC_SMPR2_SMP11_3                                   ( 0x8UL << ADC_SMPR2_SMP11_Pos )

#define ADC_SMPR2_SMP10_Pos                                 ( 8U )
#define ADC_SMPR2_SMP10_Msk                                 ( 0xfUL << ADC_SMPR2_SMP10_Pos )
#define ADC_SMPR2_SMP10                                     ( ADC_SMPR2_SMP10_Msk )
#define ADC_SMPR2_SMP10_0                                   ( 0x1UL << ADC_SMPR2_SMP10_Pos )
#define ADC_SMPR2_SMP10_1                                   ( 0x2UL << ADC_SMPR2_SMP10_Pos )
#define ADC_SMPR2_SMP10_2                                   ( 0x4UL << ADC_SMPR2_SMP10_Pos )
#define ADC_SMPR2_SMP10_3                                   ( 0x8UL << ADC_SMPR2_SMP10_Pos )

#define ADC_SMPR2_SMP9_Pos                                  ( 4U )
#define ADC_SMPR2_SMP9_Msk                                  ( 0xfUL << ADC_SMPR2_SMP9_Pos )
#define ADC_SMPR2_SMP9                                      ( ADC_SMPR2_SMP9_Msk )
#define ADC_SMPR2_SMP9_0                                    ( 0x1UL << ADC_SMPR2_SMP9_Pos )
#define ADC_SMPR2_SMP9_1                                    ( 0x2UL << ADC_SMPR2_SMP9_Pos )
#define ADC_SMPR2_SMP9_2                                    ( 0x4UL << ADC_SMPR2_SMP9_Pos )
#define ADC_SMPR2_SMP9_3                                    ( 0x8UL << ADC_SMPR2_SMP9_Pos )

#define ADC_SMPR2_SMP8_Pos                                  ( 0U )
#define ADC_SMPR2_SMP8_Msk                                  ( 0xfUL << ADC_SMPR2_SMP8_Pos )
#define ADC_SMPR2_SMP8                                      ( ADC_SMPR2_SMP8_Msk )
#define ADC_SMPR2_SMP8_0                                    ( 0x1UL << ADC_SMPR2_SMP8_Pos )
#define ADC_SMPR2_SMP8_1                                    ( 0x2UL << ADC_SMPR2_SMP8_Pos )
#define ADC_SMPR2_SMP8_2                                    ( 0x4UL << ADC_SMPR2_SMP8_Pos )
#define ADC_SMPR2_SMP8_3                                    ( 0x8UL << ADC_SMPR2_SMP8_Pos )


/***************  Bits definition for ADC_SMPR3  **********************/

#define ADC_SMPR3_CONV_PLUS_Pos                             ( 20U )
#define ADC_SMPR3_CONV_PLUS_Msk                             ( 0x3UL << ADC_SMPR3_CONV_PLUS_Pos )
#define ADC_SMPR3_CONV_PLUS                                 ( ADC_SMPR3_CONV_PLUS_Msk )
#define ADC_SMPR3_CONV_PLUS_0                               ( 0x1UL << ADC_SMPR3_CONV_PLUS_Pos )
#define ADC_SMPR3_CONV_PLUS_1                               ( 0x2UL << ADC_SMPR3_CONV_PLUS_Pos )

#define ADC_SMPR3_SMP20_Pos                                 ( 16U )
#define ADC_SMPR3_SMP20_Msk                                 ( 0xfUL << ADC_SMPR3_SMP20_Pos )
#define ADC_SMPR3_SMP20                                     ( ADC_SMPR3_SMP20_Msk )
#define ADC_SMPR3_SMP20_0                                   ( 0x1UL << ADC_SMPR3_SMP20_Pos )
#define ADC_SMPR3_SMP20_1                                   ( 0x2UL << ADC_SMPR3_SMP20_Pos )
#define ADC_SMPR3_SMP20_2                                   ( 0x4UL << ADC_SMPR3_SMP20_Pos )
#define ADC_SMPR3_SMP20_3                                   ( 0x8UL << ADC_SMPR3_SMP20_Pos )

#define ADC_SMPR3_SMP19_Pos                                 ( 12U )
#define ADC_SMPR3_SMP19_Msk                                 ( 0xfUL << ADC_SMPR3_SMP19_Pos )
#define ADC_SMPR3_SMP19                                     ( ADC_SMPR3_SMP19_Msk )
#define ADC_SMPR3_SMP19_0                                   ( 0x1UL << ADC_SMPR3_SMP19_Pos )
#define ADC_SMPR3_SMP19_1                                   ( 0x2UL << ADC_SMPR3_SMP19_Pos )
#define ADC_SMPR3_SMP19_2                                   ( 0x4UL << ADC_SMPR3_SMP19_Pos )
#define ADC_SMPR3_SMP19_3                                   ( 0x8UL << ADC_SMPR3_SMP19_Pos )

#define ADC_SMPR3_SMP18_Pos                                 ( 8U )
#define ADC_SMPR3_SMP18_Msk                                 ( 0xfUL << ADC_SMPR3_SMP18_Pos )
#define ADC_SMPR3_SMP18                                     ( ADC_SMPR3_SMP18_Msk )
#define ADC_SMPR3_SMP18_0                                   ( 0x1UL << ADC_SMPR3_SMP18_Pos )
#define ADC_SMPR3_SMP18_1                                   ( 0x2UL << ADC_SMPR3_SMP18_Pos )
#define ADC_SMPR3_SMP18_2                                   ( 0x4UL << ADC_SMPR3_SMP18_Pos )
#define ADC_SMPR3_SMP18_3                                   ( 0x8UL << ADC_SMPR3_SMP18_Pos )

#define ADC_SMPR3_SMP17_Pos                                 ( 4U )
#define ADC_SMPR3_SMP17_Msk                                 ( 0xfUL << ADC_SMPR3_SMP17_Pos )
#define ADC_SMPR3_SMP17                                     ( ADC_SMPR3_SMP17_Msk )
#define ADC_SMPR3_SMP17_0                                   ( 0x1UL << ADC_SMPR3_SMP17_Pos )
#define ADC_SMPR3_SMP17_1                                   ( 0x2UL << ADC_SMPR3_SMP17_Pos )
#define ADC_SMPR3_SMP17_2                                   ( 0x4UL << ADC_SMPR3_SMP17_Pos )
#define ADC_SMPR3_SMP17_3                                   ( 0x8UL << ADC_SMPR3_SMP17_Pos )

#define ADC_SMPR3_SMP16_Pos                                 ( 0U )
#define ADC_SMPR3_SMP16_Msk                                 ( 0xfUL << ADC_SMPR3_SMP16_Pos )
#define ADC_SMPR3_SMP16                                     ( ADC_SMPR3_SMP16_Msk )
#define ADC_SMPR3_SMP16_0                                   ( 0x1UL << ADC_SMPR3_SMP16_Pos )
#define ADC_SMPR3_SMP16_1                                   ( 0x2UL << ADC_SMPR3_SMP16_Pos )
#define ADC_SMPR3_SMP16_2                                   ( 0x4UL << ADC_SMPR3_SMP16_Pos )
#define ADC_SMPR3_SMP16_3                                   ( 0x8UL << ADC_SMPR3_SMP16_Pos )


/***************  Bits definition for ADC_HTR  **********************/

#define ADC_HTR_HT_Pos                                      ( 0U )
#define ADC_HTR_HT_Msk                                      ( 0xfffUL << ADC_HTR_HT_Pos )
#define ADC_HTR_HT                                          ( ADC_HTR_HT_Msk )


/***************  Bits definition for ADC_LTR  **********************/

#define ADC_LTR_LT_Pos                                      ( 0U )
#define ADC_LTR_LT_Msk                                      ( 0xfffUL << ADC_LTR_LT_Pos )
#define ADC_LTR_LT                                          ( ADC_LTR_LT_Msk )


/***************  Bits definition for ADC_SQR1  **********************/

#define ADC_SQR1_SQ5_Pos                                    ( 25U )
#define ADC_SQR1_SQ5_Msk                                    ( 0x1fUL << ADC_SQR1_SQ5_Pos )
#define ADC_SQR1_SQ5                                        ( ADC_SQR1_SQ5_Msk )
#define ADC_SQR1_SQ5_0                                      ( 0x1UL << ADC_SQR1_SQ5_Pos )
#define ADC_SQR1_SQ5_1                                      ( 0x2UL << ADC_SQR1_SQ5_Pos )
#define ADC_SQR1_SQ5_2                                      ( 0x4UL << ADC_SQR1_SQ5_Pos )
#define ADC_SQR1_SQ5_3                                      ( 0x8UL << ADC_SQR1_SQ5_Pos )
#define ADC_SQR1_SQ5_4                                      ( 0x10UL << ADC_SQR1_SQ5_Pos )

#define ADC_SQR1_SQ4_Pos                                    ( 20U )
#define ADC_SQR1_SQ4_Msk                                    ( 0x1fUL << ADC_SQR1_SQ4_Pos )
#define ADC_SQR1_SQ4                                        ( ADC_SQR1_SQ4_Msk )
#define ADC_SQR1_SQ4_0                                      ( 0x1UL << ADC_SQR1_SQ4_Pos )
#define ADC_SQR1_SQ4_1                                      ( 0x2UL << ADC_SQR1_SQ4_Pos )
#define ADC_SQR1_SQ4_2                                      ( 0x4UL << ADC_SQR1_SQ4_Pos )
#define ADC_SQR1_SQ4_3                                      ( 0x8UL << ADC_SQR1_SQ4_Pos )
#define ADC_SQR1_SQ4_4                                      ( 0x10UL << ADC_SQR1_SQ4_Pos )

#define ADC_SQR1_SQ3_Pos                                    ( 15U )
#define ADC_SQR1_SQ3_Msk                                    ( 0x1fUL << ADC_SQR1_SQ3_Pos )
#define ADC_SQR1_SQ3                                        ( ADC_SQR1_SQ3_Msk )
#define ADC_SQR1_SQ3_0                                      ( 0x1UL << ADC_SQR1_SQ3_Pos )
#define ADC_SQR1_SQ3_1                                      ( 0x2UL << ADC_SQR1_SQ3_Pos )
#define ADC_SQR1_SQ3_2                                      ( 0x4UL << ADC_SQR1_SQ3_Pos )
#define ADC_SQR1_SQ3_3                                      ( 0x8UL << ADC_SQR1_SQ3_Pos )
#define ADC_SQR1_SQ3_4                                      ( 0x10UL << ADC_SQR1_SQ3_Pos )

#define ADC_SQR1_SQ2_Pos                                    ( 10U )
#define ADC_SQR1_SQ2_Msk                                    ( 0x1fUL << ADC_SQR1_SQ2_Pos )
#define ADC_SQR1_SQ2                                        ( ADC_SQR1_SQ2_Msk )
#define ADC_SQR1_SQ2_0                                      ( 0x1UL << ADC_SQR1_SQ2_Pos )
#define ADC_SQR1_SQ2_1                                      ( 0x2UL << ADC_SQR1_SQ2_Pos )
#define ADC_SQR1_SQ2_2                                      ( 0x4UL << ADC_SQR1_SQ2_Pos )
#define ADC_SQR1_SQ2_3                                      ( 0x8UL << ADC_SQR1_SQ2_Pos )
#define ADC_SQR1_SQ2_4                                      ( 0x10UL << ADC_SQR1_SQ2_Pos )

#define ADC_SQR1_SQ1_Pos                                    ( 5U )
#define ADC_SQR1_SQ1_Msk                                    ( 0x1fUL << ADC_SQR1_SQ1_Pos )
#define ADC_SQR1_SQ1                                        ( ADC_SQR1_SQ1_Msk )
#define ADC_SQR1_SQ1_0                                      ( 0x1UL << ADC_SQR1_SQ1_Pos )
#define ADC_SQR1_SQ1_1                                      ( 0x2UL << ADC_SQR1_SQ1_Pos )
#define ADC_SQR1_SQ1_2                                      ( 0x4UL << ADC_SQR1_SQ1_Pos )
#define ADC_SQR1_SQ1_3                                      ( 0x8UL << ADC_SQR1_SQ1_Pos )
#define ADC_SQR1_SQ1_4                                      ( 0x10UL << ADC_SQR1_SQ1_Pos )

#define ADC_SQR1_L_Pos                                      ( 0U )
#define ADC_SQR1_L_Msk                                      ( 0xfUL << ADC_SQR1_L_Pos )
#define ADC_SQR1_L                                          ( ADC_SQR1_L_Msk )
#define ADC_SQR1_L_0                                        ( 0x1UL << ADC_SQR1_L_Pos )
#define ADC_SQR1_L_1                                        ( 0x2UL << ADC_SQR1_L_Pos )
#define ADC_SQR1_L_2                                        ( 0x4UL << ADC_SQR1_L_Pos )
#define ADC_SQR1_L_3                                        ( 0x8UL << ADC_SQR1_L_Pos )


/***************  Bits definition for ADC_SQR2  **********************/

#define ADC_SQR2_SQ11_Pos                                   ( 25U )
#define ADC_SQR2_SQ11_Msk                                   ( 0x1fUL << ADC_SQR2_SQ11_Pos )
#define ADC_SQR2_SQ11                                       ( ADC_SQR2_SQ11_Msk )
#define ADC_SQR2_SQ11_0                                     ( 0x1UL << ADC_SQR2_SQ11_Pos )
#define ADC_SQR2_SQ11_1                                     ( 0x2UL << ADC_SQR2_SQ11_Pos )
#define ADC_SQR2_SQ11_2                                     ( 0x4UL << ADC_SQR2_SQ11_Pos )
#define ADC_SQR2_SQ11_3                                     ( 0x8UL << ADC_SQR2_SQ11_Pos )
#define ADC_SQR2_SQ11_4                                     ( 0x10UL << ADC_SQR2_SQ11_Pos )

#define ADC_SQR2_SQ10_Pos                                   ( 20U )
#define ADC_SQR2_SQ10_Msk                                   ( 0x1fUL << ADC_SQR2_SQ10_Pos )
#define ADC_SQR2_SQ10                                       ( ADC_SQR2_SQ10_Msk )
#define ADC_SQR2_SQ10_0                                     ( 0x1UL << ADC_SQR2_SQ10_Pos )
#define ADC_SQR2_SQ10_1                                     ( 0x2UL << ADC_SQR2_SQ10_Pos )
#define ADC_SQR2_SQ10_2                                     ( 0x4UL << ADC_SQR2_SQ10_Pos )
#define ADC_SQR2_SQ10_3                                     ( 0x8UL << ADC_SQR2_SQ10_Pos )
#define ADC_SQR2_SQ10_4                                     ( 0x10UL << ADC_SQR2_SQ10_Pos )

#define ADC_SQR2_SQ9_Pos                                    ( 15U )
#define ADC_SQR2_SQ9_Msk                                    ( 0x1fUL << ADC_SQR2_SQ9_Pos )
#define ADC_SQR2_SQ9                                        ( ADC_SQR2_SQ9_Msk )
#define ADC_SQR2_SQ9_0                                      ( 0x1UL << ADC_SQR2_SQ9_Pos )
#define ADC_SQR2_SQ9_1                                      ( 0x2UL << ADC_SQR2_SQ9_Pos )
#define ADC_SQR2_SQ9_2                                      ( 0x4UL << ADC_SQR2_SQ9_Pos )
#define ADC_SQR2_SQ9_3                                      ( 0x8UL << ADC_SQR2_SQ9_Pos )
#define ADC_SQR2_SQ9_4                                      ( 0x10UL << ADC_SQR2_SQ9_Pos )

#define ADC_SQR2_SQ8_Pos                                    ( 10U )
#define ADC_SQR2_SQ8_Msk                                    ( 0x1fUL << ADC_SQR2_SQ8_Pos )
#define ADC_SQR2_SQ8                                        ( ADC_SQR2_SQ8_Msk )
#define ADC_SQR2_SQ8_0                                      ( 0x1UL << ADC_SQR2_SQ8_Pos )
#define ADC_SQR2_SQ8_1                                      ( 0x2UL << ADC_SQR2_SQ8_Pos )
#define ADC_SQR2_SQ8_2                                      ( 0x4UL << ADC_SQR2_SQ8_Pos )
#define ADC_SQR2_SQ8_3                                      ( 0x8UL << ADC_SQR2_SQ8_Pos )
#define ADC_SQR2_SQ8_4                                      ( 0x10UL << ADC_SQR2_SQ8_Pos )

#define ADC_SQR2_SQ7_Pos                                    ( 5U )
#define ADC_SQR2_SQ7_Msk                                    ( 0x1fUL << ADC_SQR2_SQ7_Pos )
#define ADC_SQR2_SQ7                                        ( ADC_SQR2_SQ7_Msk )
#define ADC_SQR2_SQ7_0                                      ( 0x1UL << ADC_SQR2_SQ7_Pos )
#define ADC_SQR2_SQ7_1                                      ( 0x2UL << ADC_SQR2_SQ7_Pos )
#define ADC_SQR2_SQ7_2                                      ( 0x4UL << ADC_SQR2_SQ7_Pos )
#define ADC_SQR2_SQ7_3                                      ( 0x8UL << ADC_SQR2_SQ7_Pos )
#define ADC_SQR2_SQ7_4                                      ( 0x10UL << ADC_SQR2_SQ7_Pos )

#define ADC_SQR2_SQ6_Pos                                    ( 0U )
#define ADC_SQR2_SQ6_Msk                                    ( 0x1fUL << ADC_SQR2_SQ6_Pos )
#define ADC_SQR2_SQ6                                        ( ADC_SQR2_SQ6_Msk )
#define ADC_SQR2_SQ6_0                                      ( 0x1UL << ADC_SQR2_SQ6_Pos )
#define ADC_SQR2_SQ6_1                                      ( 0x2UL << ADC_SQR2_SQ6_Pos )
#define ADC_SQR2_SQ6_2                                      ( 0x4UL << ADC_SQR2_SQ6_Pos )
#define ADC_SQR2_SQ6_3                                      ( 0x8UL << ADC_SQR2_SQ6_Pos )
#define ADC_SQR2_SQ6_4                                      ( 0x10UL << ADC_SQR2_SQ6_Pos )


/***************  Bits definition for ADC_SQR3  **********************/

#define ADC_SQR3_SQ16_Pos                                   ( 20U )
#define ADC_SQR3_SQ16_Msk                                   ( 0x1fUL << ADC_SQR3_SQ16_Pos )
#define ADC_SQR3_SQ16                                       ( ADC_SQR3_SQ16_Msk )
#define ADC_SQR3_SQ16_0                                     ( 0x1UL << ADC_SQR3_SQ16_Pos )
#define ADC_SQR3_SQ16_1                                     ( 0x2UL << ADC_SQR3_SQ16_Pos )
#define ADC_SQR3_SQ16_2                                     ( 0x4UL << ADC_SQR3_SQ16_Pos )
#define ADC_SQR3_SQ16_3                                     ( 0x8UL << ADC_SQR3_SQ16_Pos )
#define ADC_SQR3_SQ16_4                                     ( 0x10UL << ADC_SQR3_SQ16_Pos )

#define ADC_SQR3_SQ15_Pos                                   ( 15U )
#define ADC_SQR3_SQ15_Msk                                   ( 0x1fUL << ADC_SQR3_SQ15_Pos )
#define ADC_SQR3_SQ15                                       ( ADC_SQR3_SQ15_Msk )
#define ADC_SQR3_SQ15_0                                     ( 0x1UL << ADC_SQR3_SQ15_Pos )
#define ADC_SQR3_SQ15_1                                     ( 0x2UL << ADC_SQR3_SQ15_Pos )
#define ADC_SQR3_SQ15_2                                     ( 0x4UL << ADC_SQR3_SQ15_Pos )
#define ADC_SQR3_SQ15_3                                     ( 0x8UL << ADC_SQR3_SQ15_Pos )
#define ADC_SQR3_SQ15_4                                     ( 0x10UL << ADC_SQR3_SQ15_Pos )

#define ADC_SQR3_SQ14_Pos                                   ( 10U )
#define ADC_SQR3_SQ14_Msk                                   ( 0x1fUL << ADC_SQR3_SQ14_Pos )
#define ADC_SQR3_SQ14                                       ( ADC_SQR3_SQ14_Msk )
#define ADC_SQR3_SQ14_0                                     ( 0x1UL << ADC_SQR3_SQ14_Pos )
#define ADC_SQR3_SQ14_1                                     ( 0x2UL << ADC_SQR3_SQ14_Pos )
#define ADC_SQR3_SQ14_2                                     ( 0x4UL << ADC_SQR3_SQ14_Pos )
#define ADC_SQR3_SQ14_3                                     ( 0x8UL << ADC_SQR3_SQ14_Pos )
#define ADC_SQR3_SQ14_4                                     ( 0x10UL << ADC_SQR3_SQ14_Pos )

#define ADC_SQR3_SQ13_Pos                                   ( 5U )
#define ADC_SQR3_SQ13_Msk                                   ( 0x1fUL << ADC_SQR3_SQ13_Pos )
#define ADC_SQR3_SQ13                                       ( ADC_SQR3_SQ13_Msk )
#define ADC_SQR3_SQ13_0                                     ( 0x1UL << ADC_SQR3_SQ13_Pos )
#define ADC_SQR3_SQ13_1                                     ( 0x2UL << ADC_SQR3_SQ13_Pos )
#define ADC_SQR3_SQ13_2                                     ( 0x4UL << ADC_SQR3_SQ13_Pos )
#define ADC_SQR3_SQ13_3                                     ( 0x8UL << ADC_SQR3_SQ13_Pos )
#define ADC_SQR3_SQ13_4                                     ( 0x10UL << ADC_SQR3_SQ13_Pos )

#define ADC_SQR3_SQ12_Pos                                   ( 0U )
#define ADC_SQR3_SQ12_Msk                                   ( 0x1fUL << ADC_SQR3_SQ12_Pos )
#define ADC_SQR3_SQ12                                       ( ADC_SQR3_SQ12_Msk )
#define ADC_SQR3_SQ12_0                                     ( 0x1UL << ADC_SQR3_SQ12_Pos )
#define ADC_SQR3_SQ12_1                                     ( 0x2UL << ADC_SQR3_SQ12_Pos )
#define ADC_SQR3_SQ12_2                                     ( 0x4UL << ADC_SQR3_SQ12_Pos )
#define ADC_SQR3_SQ12_3                                     ( 0x8UL << ADC_SQR3_SQ12_Pos )
#define ADC_SQR3_SQ12_4                                     ( 0x10UL << ADC_SQR3_SQ12_Pos )


/***************  Bits definition for ADC_JSQR  **********************/

#define ADC_JSQR_JEXTSEL_Pos                                ( 27U )
#define ADC_JSQR_JEXTSEL_Msk                                ( 0x1fUL << ADC_JSQR_JEXTSEL_Pos )
#define ADC_JSQR_JEXTSEL                                    ( ADC_JSQR_JEXTSEL_Msk )
#define ADC_JSQR_JEXTSEL_0                                  ( 0x1UL << ADC_JSQR_JEXTSEL_Pos )
#define ADC_JSQR_JEXTSEL_1                                  ( 0x2UL << ADC_JSQR_JEXTSEL_Pos )
#define ADC_JSQR_JEXTSEL_2                                  ( 0x4UL << ADC_JSQR_JEXTSEL_Pos )
#define ADC_JSQR_JEXTSEL_3                                  ( 0x8UL << ADC_JSQR_JEXTSEL_Pos )
#define ADC_JSQR_JEXTSEL_4                                  ( 0x10UL << ADC_JSQR_JEXTSEL_Pos )

#define ADC_JSQR_JEXTEN_Pos                                 ( 25U )
#define ADC_JSQR_JEXTEN_Msk                                 ( 0x3UL << ADC_JSQR_JEXTEN_Pos )
#define ADC_JSQR_JEXTEN                                     ( ADC_JSQR_JEXTEN_Msk )
#define ADC_JSQR_JEXTEN_0                                   ( 0x1UL << ADC_JSQR_JEXTEN_Pos )
#define ADC_JSQR_JEXTEN_1                                   ( 0x2UL << ADC_JSQR_JEXTEN_Pos )

#define ADC_JSQR_JSQ4_Pos                                   ( 20U )
#define ADC_JSQR_JSQ4_Msk                                   ( 0x1fUL << ADC_JSQR_JSQ4_Pos )
#define ADC_JSQR_JSQ4                                       ( ADC_JSQR_JSQ4_Msk )
#define ADC_JSQR_JSQ4_0                                     ( 0x1UL << ADC_JSQR_JSQ4_Pos )
#define ADC_JSQR_JSQ4_1                                     ( 0x2UL << ADC_JSQR_JSQ4_Pos )
#define ADC_JSQR_JSQ4_2                                     ( 0x4UL << ADC_JSQR_JSQ4_Pos )
#define ADC_JSQR_JSQ4_3                                     ( 0x8UL << ADC_JSQR_JSQ4_Pos )
#define ADC_JSQR_JSQ4_4                                     ( 0x10UL << ADC_JSQR_JSQ4_Pos )

#define ADC_JSQR_JSQ3_Pos                                   ( 15U )
#define ADC_JSQR_JSQ3_Msk                                   ( 0x1fUL << ADC_JSQR_JSQ3_Pos )
#define ADC_JSQR_JSQ3                                       ( ADC_JSQR_JSQ3_Msk )
#define ADC_JSQR_JSQ3_0                                     ( 0x1UL << ADC_JSQR_JSQ3_Pos )
#define ADC_JSQR_JSQ3_1                                     ( 0x2UL << ADC_JSQR_JSQ3_Pos )
#define ADC_JSQR_JSQ3_2                                     ( 0x4UL << ADC_JSQR_JSQ3_Pos )
#define ADC_JSQR_JSQ3_3                                     ( 0x8UL << ADC_JSQR_JSQ3_Pos )
#define ADC_JSQR_JSQ3_4                                     ( 0x10UL << ADC_JSQR_JSQ3_Pos )

#define ADC_JSQR_JSQ2_Pos                                   ( 10U )
#define ADC_JSQR_JSQ2_Msk                                   ( 0x1fUL << ADC_JSQR_JSQ2_Pos )
#define ADC_JSQR_JSQ2                                       ( ADC_JSQR_JSQ2_Msk )
#define ADC_JSQR_JSQ2_0                                     ( 0x1UL << ADC_JSQR_JSQ2_Pos )
#define ADC_JSQR_JSQ2_1                                     ( 0x2UL << ADC_JSQR_JSQ2_Pos )
#define ADC_JSQR_JSQ2_2                                     ( 0x4UL << ADC_JSQR_JSQ2_Pos )
#define ADC_JSQR_JSQ2_3                                     ( 0x8UL << ADC_JSQR_JSQ2_Pos )
#define ADC_JSQR_JSQ2_4                                     ( 0x10UL << ADC_JSQR_JSQ2_Pos )

#define ADC_JSQR_JSQ1_Pos                                   ( 5U )
#define ADC_JSQR_JSQ1_Msk                                   ( 0x1fUL << ADC_JSQR_JSQ1_Pos )
#define ADC_JSQR_JSQ1                                       ( ADC_JSQR_JSQ1_Msk )
#define ADC_JSQR_JSQ1_0                                     ( 0x1UL << ADC_JSQR_JSQ1_Pos )
#define ADC_JSQR_JSQ1_1                                     ( 0x2UL << ADC_JSQR_JSQ1_Pos )
#define ADC_JSQR_JSQ1_2                                     ( 0x4UL << ADC_JSQR_JSQ1_Pos )
#define ADC_JSQR_JSQ1_3                                     ( 0x8UL << ADC_JSQR_JSQ1_Pos )
#define ADC_JSQR_JSQ1_4                                     ( 0x10UL << ADC_JSQR_JSQ1_Pos )

#define ADC_JSQR_JL_Pos                                     ( 0U )
#define ADC_JSQR_JL_Msk                                     ( 0x3UL << ADC_JSQR_JL_Pos )
#define ADC_JSQR_JL                                         ( ADC_JSQR_JL_Msk )
#define ADC_JSQR_JL_0                                       ( 0x1UL << ADC_JSQR_JL_Pos )
#define ADC_JSQR_JL_1                                       ( 0x2UL << ADC_JSQR_JL_Pos )


/***************  Bits definition for ADC_JDRx  **********************/

#define ADC_JDRX_JCH_Pos                                    ( 16U )
#define ADC_JDRX_JCH_Msk                                    ( 0x1fUL << ADC_JDRX_JCH_Pos )
#define ADC_JDRX_JCH                                        ( ADC_JDRX_JCH_Msk )
#define ADC_JDRX_JCH_0                                      ( 0x1UL << ADC_JDRX_JCH_Pos )
#define ADC_JDRX_JCH_1                                      ( 0x2UL << ADC_JDRX_JCH_Pos )
#define ADC_JDRX_JCH_2                                      ( 0x4UL << ADC_JDRX_JCH_Pos )
#define ADC_JDRX_JCH_3                                      ( 0x8UL << ADC_JDRX_JCH_Pos )
#define ADC_JDRX_JCH_4                                      ( 0x10UL << ADC_JDRX_JCH_Pos )

#define ADC_JDRX_JDATA_Pos                                  ( 0U )
#define ADC_JDRX_JDATA_Msk                                  ( 0xffffUL << ADC_JDRX_JDATA_Pos )
#define ADC_JDRX_JDATA                                      ( ADC_JDRX_JDATA_Msk )


/***************  Bits definition for ADC_DR  **********************/

#define ADC_DR_CH_Pos                                       ( 16U )
#define ADC_DR_CH_Msk                                       ( 0x1fUL << ADC_DR_CH_Pos )
#define ADC_DR_CH                                           ( ADC_DR_CH_Msk )
#define ADC_DR_CH_0                                         ( 0x1UL << ADC_DR_CH_Pos )
#define ADC_DR_CH_1                                         ( 0x2UL << ADC_DR_CH_Pos )
#define ADC_DR_CH_2                                         ( 0x4UL << ADC_DR_CH_Pos )
#define ADC_DR_CH_3                                         ( 0x8UL << ADC_DR_CH_Pos )
#define ADC_DR_CH_4                                         ( 0x10UL << ADC_DR_CH_Pos )

#define ADC_DR_DATA_Pos                                     ( 0U )
#define ADC_DR_DATA_Msk                                     ( 0xffffUL << ADC_DR_DATA_Pos )
#define ADC_DR_DATA                                         ( ADC_DR_DATA_Msk )


/***************  Bits definition for ADC_DIFSEL  **********************/

#define ADC_DIFSEL_DIFSEL_Pos                               ( 0U )
#define ADC_DIFSEL_DIFSEL_Msk                               ( 0x7ffffUL << ADC_DIFSEL_DIFSEL_Pos )
#define ADC_DIFSEL_DIFSEL                                   ( ADC_DIFSEL_DIFSEL_Msk )


/***************  Bits definition for ADC_OFRx  **********************/

#define ADC_OFRX_OFFSETY_EN_Pos                             ( 31U )
#define ADC_OFRX_OFFSETY_EN_Msk                             ( 0x1UL << ADC_OFRX_OFFSETY_EN_Pos )
#define ADC_OFRX_OFFSETY_EN                                 ( ADC_OFRX_OFFSETY_EN_Msk )

#define ADC_OFRX_OFFSETY_CH_Pos                             ( 26U )
#define ADC_OFRX_OFFSETY_CH_Msk                             ( 0x1fUL << ADC_OFRX_OFFSETY_CH_Pos )
#define ADC_OFRX_OFFSETY_CH                                 ( ADC_OFRX_OFFSETY_CH_Msk )
#define ADC_OFRX_OFFSETY_CH_0                               ( 0x1UL << ADC_OFRX_OFFSETY_CH_Pos )
#define ADC_OFRX_OFFSETY_CH_1                               ( 0x2UL << ADC_OFRX_OFFSETY_CH_Pos )
#define ADC_OFRX_OFFSETY_CH_2                               ( 0x4UL << ADC_OFRX_OFFSETY_CH_Pos )
#define ADC_OFRX_OFFSETY_CH_3                               ( 0x8UL << ADC_OFRX_OFFSETY_CH_Pos )
#define ADC_OFRX_OFFSETY_CH_4                               ( 0x10UL << ADC_OFRX_OFFSETY_CH_Pos )

#define ADC_OFRX_OFFSETY_SAT_Pos                            ( 25U )
#define ADC_OFRX_OFFSETY_SAT_Msk                            ( 0x1UL << ADC_OFRX_OFFSETY_SAT_Pos )
#define ADC_OFRX_OFFSETY_SAT                                ( ADC_OFRX_OFFSETY_SAT_Msk )

#define ADC_OFRX_OFFSETY_POS_Pos                            ( 24U )
#define ADC_OFRX_OFFSETY_POS_Msk                            ( 0x1UL << ADC_OFRX_OFFSETY_POS_Pos )
#define ADC_OFRX_OFFSETY_POS                                ( ADC_OFRX_OFFSETY_POS_Msk )

#define ADC_OFRX_OFFSETY_Pos                                ( 0U )
#define ADC_OFRX_OFFSETY_Msk                                ( 0xfffUL << ADC_OFRX_OFFSETY_Pos )
#define ADC_OFRX_OFFSETY                                    ( ADC_OFRX_OFFSETY_Msk )


/***************  Bits definition for ADC_CALFACT  **********************/

#define ADC_CALFACT_CALFACT_D_Pos                           ( 16U )
#define ADC_CALFACT_CALFACT_D_Msk                           ( 0x7fUL << ADC_CALFACT_CALFACT_D_Pos )
#define ADC_CALFACT_CALFACT_D                               ( ADC_CALFACT_CALFACT_D_Msk )
#define ADC_CALFACT_CALFACT_D_0                             ( 0x1UL << ADC_CALFACT_CALFACT_D_Pos )
#define ADC_CALFACT_CALFACT_D_1                             ( 0x2UL << ADC_CALFACT_CALFACT_D_Pos )
#define ADC_CALFACT_CALFACT_D_2                             ( 0x4UL << ADC_CALFACT_CALFACT_D_Pos )
#define ADC_CALFACT_CALFACT_D_3                             ( 0x8UL << ADC_CALFACT_CALFACT_D_Pos )
#define ADC_CALFACT_CALFACT_D_4                             ( 0x10UL << ADC_CALFACT_CALFACT_D_Pos )
#define ADC_CALFACT_CALFACT_D_5                             ( 0x20UL << ADC_CALFACT_CALFACT_D_Pos )
#define ADC_CALFACT_CALFACT_D_6                             ( 0x40UL << ADC_CALFACT_CALFACT_D_Pos )

#define ADC_CALFACT_CALFACT_S_Pos                           ( 0U )
#define ADC_CALFACT_CALFACT_S_Msk                           ( 0x7fUL << ADC_CALFACT_CALFACT_S_Pos )
#define ADC_CALFACT_CALFACT_S                               ( ADC_CALFACT_CALFACT_S_Msk )
#define ADC_CALFACT_CALFACT_S_0                             ( 0x1UL << ADC_CALFACT_CALFACT_S_Pos )
#define ADC_CALFACT_CALFACT_S_1                             ( 0x2UL << ADC_CALFACT_CALFACT_S_Pos )
#define ADC_CALFACT_CALFACT_S_2                             ( 0x4UL << ADC_CALFACT_CALFACT_S_Pos )
#define ADC_CALFACT_CALFACT_S_3                             ( 0x8UL << ADC_CALFACT_CALFACT_S_Pos )
#define ADC_CALFACT_CALFACT_S_4                             ( 0x10UL << ADC_CALFACT_CALFACT_S_Pos )
#define ADC_CALFACT_CALFACT_S_5                             ( 0x20UL << ADC_CALFACT_CALFACT_S_Pos )
#define ADC_CALFACT_CALFACT_S_6                             ( 0x40UL << ADC_CALFACT_CALFACT_S_Pos )


/***************  Bits definition for ADC_CSR  **********************/

#define ADC_CSR_AWD_SLV_Pos                                 ( 23U )
#define ADC_CSR_AWD_SLV_Msk                                 ( 0x1UL << ADC_CSR_AWD_SLV_Pos )
#define ADC_CSR_AWD_SLV                                     ( ADC_CSR_AWD_SLV_Msk )

#define ADC_CSR_JEOG_SLV_Pos                                ( 22U )
#define ADC_CSR_JEOG_SLV_Msk                                ( 0x1UL << ADC_CSR_JEOG_SLV_Pos )
#define ADC_CSR_JEOG_SLV                                    ( ADC_CSR_JEOG_SLV_Msk )

#define ADC_CSR_JEOC_SLV_Pos                                ( 21U )
#define ADC_CSR_JEOC_SLV_Msk                                ( 0x1UL << ADC_CSR_JEOC_SLV_Pos )
#define ADC_CSR_JEOC_SLV                                    ( ADC_CSR_JEOC_SLV_Msk )

#define ADC_CSR_OVERF_SLV_Pos                               ( 20U )
#define ADC_CSR_OVERF_SLV_Msk                               ( 0x1UL << ADC_CSR_OVERF_SLV_Pos )
#define ADC_CSR_OVERF_SLV                                   ( ADC_CSR_OVERF_SLV_Msk )

#define ADC_CSR_EOG_SLV_Pos                                 ( 19U )
#define ADC_CSR_EOG_SLV_Msk                                 ( 0x1UL << ADC_CSR_EOG_SLV_Pos )
#define ADC_CSR_EOG_SLV                                     ( ADC_CSR_EOG_SLV_Msk )

#define ADC_CSR_EOC_SLV_Pos                                 ( 18U )
#define ADC_CSR_EOC_SLV_Msk                                 ( 0x1UL << ADC_CSR_EOC_SLV_Pos )
#define ADC_CSR_EOC_SLV                                     ( ADC_CSR_EOC_SLV_Msk )

#define ADC_CSR_EOSMP_SLV_Pos                               ( 17U )
#define ADC_CSR_EOSMP_SLV_Msk                               ( 0x1UL << ADC_CSR_EOSMP_SLV_Pos )
#define ADC_CSR_EOSMP_SLV                                   ( ADC_CSR_EOSMP_SLV_Msk )

#define ADC_CSR_ADRDY_SLV_Pos                               ( 16U )
#define ADC_CSR_ADRDY_SLV_Msk                               ( 0x1UL << ADC_CSR_ADRDY_SLV_Pos )
#define ADC_CSR_ADRDY_SLV                                   ( ADC_CSR_ADRDY_SLV_Msk )

#define ADC_CSR_AWD_MST_Pos                                 ( 7U )
#define ADC_CSR_AWD_MST_Msk                                 ( 0x1UL << ADC_CSR_AWD_MST_Pos )
#define ADC_CSR_AWD_MST                                     ( ADC_CSR_AWD_MST_Msk )

#define ADC_CSR_JEOG_MST_Pos                                ( 6U )
#define ADC_CSR_JEOG_MST_Msk                                ( 0x1UL << ADC_CSR_JEOG_MST_Pos )
#define ADC_CSR_JEOG_MST                                    ( ADC_CSR_JEOG_MST_Msk )

#define ADC_CSR_JEOC_MST_Pos                                ( 5U )
#define ADC_CSR_JEOC_MST_Msk                                ( 0x1UL << ADC_CSR_JEOC_MST_Pos )
#define ADC_CSR_JEOC_MST                                    ( ADC_CSR_JEOC_MST_Msk )

#define ADC_CSR_OVERF_MST_Pos                               ( 4U )
#define ADC_CSR_OVERF_MST_Msk                               ( 0x1UL << ADC_CSR_OVERF_MST_Pos )
#define ADC_CSR_OVERF_MST                                   ( ADC_CSR_OVERF_MST_Msk )

#define ADC_CSR_EOG_MST_Pos                                 ( 3U )
#define ADC_CSR_EOG_MST_Msk                                 ( 0x1UL << ADC_CSR_EOG_MST_Pos )
#define ADC_CSR_EOG_MST                                     ( ADC_CSR_EOG_MST_Msk )

#define ADC_CSR_EOC_MST_Pos                                 ( 2U )
#define ADC_CSR_EOC_MST_Msk                                 ( 0x1UL << ADC_CSR_EOC_MST_Pos )
#define ADC_CSR_EOC_MST                                     ( ADC_CSR_EOC_MST_Msk )

#define ADC_CSR_EOSMP_MST_Pos                               ( 1U )
#define ADC_CSR_EOSMP_MST_Msk                               ( 0x1UL << ADC_CSR_EOSMP_MST_Pos )
#define ADC_CSR_EOSMP_MST                                   ( ADC_CSR_EOSMP_MST_Msk )

#define ADC_CSR_ADRDY_MST_Pos                               ( 0U )
#define ADC_CSR_ADRDY_MST_Msk                               ( 0x1UL << ADC_CSR_ADRDY_MST_Pos )
#define ADC_CSR_ADRDY_MST                                   ( ADC_CSR_ADRDY_MST_Msk )


/***************  Bits definition for ADC_CCR  **********************/

#define ADC_CCR_VBATEN_Pos                                  ( 24U )
#define ADC_CCR_VBATEN_Msk                                  ( 0x01UL << ADC_CCR_VBATEN_Pos )
#define ADC_CCR_VBATEN                                      ( ADC_CCR_VBATEN_Msk )

#define ADC_CCR_VREFINTEN_Pos                               ( 23U )
#define ADC_CCR_VREFINTEN_Msk                               ( 0x01UL << ADC_CCR_VREFINTEN_Pos )
#define ADC_CCR_VREFINTEN                                   ( ADC_CCR_VREFINTEN_Msk )

#define ADC_CCR_TSEN_Pos                                    ( 22U )
#define ADC_CCR_TSEN_Msk                                    ( 0x01UL << ADC_CCR_TSEN_Pos )
#define ADC_CCR_TSEN                                        ( ADC_CCR_TSEN_Msk )

#define ADC_CCR_ADCDIV_Pos                                  ( 16U )
#define ADC_CCR_ADCDIV_Msk                                  ( 0x3fUL << ADC_CCR_ADCDIV_Pos )
#define ADC_CCR_ADCDIV                                      ( ADC_CCR_ADCDIV_Msk )
#define ADC_CCR_ADCDIV_0                                    ( 0x1UL << ADC_CCR_ADCDIV_Pos )
#define ADC_CCR_ADCDIV_1                                    ( 0x2UL << ADC_CCR_ADCDIV_Pos )
#define ADC_CCR_ADCDIV_2                                    ( 0x4UL << ADC_CCR_ADCDIV_Pos )
#define ADC_CCR_ADCDIV_3                                    ( 0x8UL << ADC_CCR_ADCDIV_Pos )
#define ADC_CCR_ADCDIV_4                                    ( 0x10UL << ADC_CCR_ADCDIV_Pos )
#define ADC_CCR_ADCDIV_5                                    ( 0x20UL << ADC_CCR_ADCDIV_Pos )

#define ADC_CCR_DMADUAL_Pos                                 ( 14U )
#define ADC_CCR_DMADUAL_Msk                                 ( 0x3UL << ADC_CCR_DMADUAL_Pos )
#define ADC_CCR_DMADUAL                                     ( ADC_CCR_DMADUAL_Msk )
#define ADC_CCR_DMADUAL_0                                   ( 0x1UL << ADC_CCR_DMADUAL_Pos )
#define ADC_CCR_DMADUAL_1                                   ( 0x2UL << ADC_CCR_DMADUAL_Pos )

#define ADC_CCR_CLKMODE_Pos                                 ( 13U )
#define ADC_CCR_CLKMODE_Msk                                 ( 0x1UL << ADC_CCR_CLKMODE_Pos )
#define ADC_CCR_CLKMODE                                     ( ADC_CCR_CLKMODE_Msk )

#define ADC_CCR_DELAY_Pos                                   ( 8U )
#define ADC_CCR_DELAY_Msk                                   ( 0xfUL << ADC_CCR_DELAY_Pos )
#define ADC_CCR_DELAY                                       ( ADC_CCR_DELAY_Msk )
#define ADC_CCR_DELAY_0                                     ( 0x1UL << ADC_CCR_DELAY_Pos )
#define ADC_CCR_DELAY_1                                     ( 0x2UL << ADC_CCR_DELAY_Pos )
#define ADC_CCR_DELAY_2                                     ( 0x4UL << ADC_CCR_DELAY_Pos )
#define ADC_CCR_DELAY_3                                     ( 0x8UL << ADC_CCR_DELAY_Pos )

#define ADC_CCR_DUALMOD_Pos                                 ( 0U )
#define ADC_CCR_DUALMOD_Msk                                 ( 0x1fUL << ADC_CCR_DUALMOD_Pos )
#define ADC_CCR_DUALMOD                                     ( ADC_CCR_DUALMOD_Msk )
#define ADC_CCR_DUALMOD_0                                   ( 0x1UL << ADC_CCR_DUALMOD_Pos )
#define ADC_CCR_DUALMOD_1                                   ( 0x2UL << ADC_CCR_DUALMOD_Pos )
#define ADC_CCR_DUALMOD_2                                   ( 0x4UL << ADC_CCR_DUALMOD_Pos )
#define ADC_CCR_DUALMOD_3                                   ( 0x8UL << ADC_CCR_DUALMOD_Pos )
#define ADC_CCR_DUALMOD_4                                   ( 0x10UL << ADC_CCR_DUALMOD_Pos )


/***************  Bits definition for ADC_CDR  **********************/

#define ADC_CDR_DATA2_Pos                                   ( 16U )
#define ADC_CDR_DATA2_Msk                                   ( 0xffffUL << ADC_CDR_DATA2_Pos )
#define ADC_CDR_DATA2                                       ( ADC_CDR_DATA2_Msk )

#define ADC_CDR_DATA1_Pos                                   ( 0U )
#define ADC_CDR_DATA1_Msk                                   ( 0xffffUL << ADC_CDR_DATA1_Pos )
#define ADC_CDR_DATA1                                       ( ADC_CDR_DATA1_Msk )


/***************  Bits definition for ADC_CVRB  **********************/

#define ADC_CVRB_VRBTRIM_Pos                                ( 4U )
#define ADC_CVRB_VRBTRIM_Msk                                ( 0x1fUL << ADC_CVRB_VRBTRIM_Pos )
#define ADC_CVRB_VRBTRIM                                    ( ADC_CVRB_VRBTRIM_Msk )
#define ADC_CVRB_VRBTRIM_0                                  ( 0x1UL << ADC_CVRB_VRBTRIM_Pos )
#define ADC_CVRB_VRBTRIM_1                                  ( 0x2UL << ADC_CVRB_VRBTRIM_Pos )
#define ADC_CVRB_VRBTRIM_2                                  ( 0x4UL << ADC_CVRB_VRBTRIM_Pos )
#define ADC_CVRB_VRBTRIM_3                                  ( 0x8UL << ADC_CVRB_VRBTRIM_Pos )
#define ADC_CVRB_VRBTRIM_4                                  ( 0x10UL << ADC_CVRB_VRBTRIM_Pos )

#define ADC_CVRB_VRS_Pos                                    ( 2U )
#define ADC_CVRB_VRS_Msk                                    ( 0x3UL << ADC_CVRB_VRS_Pos )
#define ADC_CVRB_VRS                                        ( ADC_CVRB_VRS_Msk )
#define ADC_CVRB_VRS_0                                      ( 0x1UL << ADC_CVRB_VRS_Pos )
#define ADC_CVRB_VRS_1                                      ( 0x2UL << ADC_CVRB_VRS_Pos )

#define ADC_CVRB_HIZ_Pos                                    ( 1U )
#define ADC_CVRB_HIZ_Msk                                    ( 0x1UL << ADC_CVRB_HIZ_Pos )
#define ADC_CVRB_HIZ                                        ( ADC_CVRB_HIZ_Msk )

#define ADC_CVRB_ENVR_Pos                                   ( 0U )
#define ADC_CVRB_ENVR_Msk                                   ( 0x1UL << ADC_CVRB_ENVR_Pos )
#define ADC_CVRB_ENVR                                       ( ADC_CVRB_ENVR_Msk )


/***************  Bits definition for DAC_CR register  ***********************/

#define DAC_CR_CEN2_Pos                         ( 30U )
#define DAC_CR_CEN2_Msk                         ( 0x1UL << DAC_CR_CEN2_Pos )
#define DAC_CR_CEN2                             ( DAC_CR_CEN2_Msk )

#define DAC_CR_DMAUDIE2_Pos                     ( 29U )
#define DAC_CR_DMAUDIE2_Msk                     ( 0x1UL << DAC_CR_DMAUDIE2_Pos )
#define DAC_CR_DMAUDIE2                         ( DAC_CR_DMAUDIE2_Msk )

#define DAC_CR_DMAEN2_Pos                       ( 28U )
#define DAC_CR_DMAEN2_Msk                       ( 0x1UL << DAC_CR_DMAEN2_Pos )
#define DAC_CR_DMAEN2                           ( DAC_CR_DMAEN2_Msk )

#define DAC_CR_MAMP2_Pos                        ( 24U )
#define DAC_CR_MAMP2_Msk                        ( 0xFUL << DAC_CR_MAMP2_Pos )
#define DAC_CR_MAMP2                            ( DAC_CR_MAMP2_Msk )
#define DAC_CR_MAMP2_0                          ( 0x1UL << DAC_CR_MAMP2_Pos )
#define DAC_CR_MAMP2_1                          ( 0x2UL << DAC_CR_MAMP2_Pos )
#define DAC_CR_MAMP2_2                          ( 0x4UL << DAC_CR_MAMP2_Pos )
#define DAC_CR_MAMP2_3                          ( 0x8UL << DAC_CR_MAMP2_Pos )

#define DAC_CR_WAVE2_Pos                        ( 22U )
#define DAC_CR_WAVE2_Msk                        ( 0x3UL << DAC_CR_WAVE2_Pos )
#define DAC_CR_WAVE2                            ( DAC_CR_WAVE2_Msk )
#define DAC_CR_WAVE2_0                          ( 0x1UL << DAC_CR_WAVE2_Pos )
#define DAC_CR_WAVE2_1                          ( 0x2UL << DAC_CR_WAVE2_Pos )

#define DAC_CR_TSEL2_Pos                        ( 18U )
#define DAC_CR_TSEL2_Msk                        ( 0xFUL << DAC_CR_TSEL2_Pos )
#define DAC_CR_TSEL2                            ( DAC_CR_TSEL2_Msk )
#define DAC_CR_TSEL2_0                          ( 0x1UL << DAC_CR_TSEL2_Pos )
#define DAC_CR_TSEL2_1                          ( 0x2UL << DAC_CR_TSEL2_Pos )
#define DAC_CR_TSEL2_2                          ( 0x4UL << DAC_CR_TSEL2_Pos )
#define DAC_CR_TSEL2_3                          ( 0x8UL << DAC_CR_TSEL2_Pos )

#define DAC_CR_TEN2_Pos                         ( 17U )
#define DAC_CR_TEN2_Msk                         ( 0x1UL << DAC_CR_TEN2_Pos )
#define DAC_CR_TEN2                             ( DAC_CR_TEN2_Msk )

#define DAC_CR_EN2_Pos                          ( 16U )
#define DAC_CR_EN2_Msk                          ( 0x1UL << DAC_CR_EN2_Pos )
#define DAC_CR_EN2                              ( DAC_CR_EN2_Msk )

#define DAC_CR_CEN1_Pos                         ( 14U )
#define DAC_CR_CEN1_Msk                         ( 0x1UL << DAC_CR_CEN1_Pos )
#define DAC_CR_CEN1                             ( DAC_CR_CEN1_Msk )

#define DAC_CR_DMAUDIE1_Pos                     ( 13U )
#define DAC_CR_DMAUDIE1_Msk                     ( 0x1UL << DAC_CR_DMAUDIE1_Pos )
#define DAC_CR_DMAUDIE1                         ( DAC_CR_DMAUDIE1_Msk )

#define DAC_CR_DMAEN1_Pos                       ( 12U )
#define DAC_CR_DMAEN1_Msk                       ( 0x1UL << DAC_CR_DMAEN1_Pos )
#define DAC_CR_DMAEN1                           ( DAC_CR_DMAEN1_Msk )

#define DAC_CR_MAMP1_Pos                        ( 8U )
#define DAC_CR_MAMP1_Msk                        ( 0xFUL << DAC_CR_MAMP1_Pos )
#define DAC_CR_MAMP1                            ( DAC_CR_MAMP1_Msk )
#define DAC_CR_MAMP1_0                          ( 0x1UL << DAC_CR_MAMP1_Pos )
#define DAC_CR_MAMP1_1                          ( 0x2UL << DAC_CR_MAMP1_Pos )
#define DAC_CR_MAMP1_2                          ( 0x4UL << DAC_CR_MAMP1_Pos )
#define DAC_CR_MAMP1_3                          ( 0x8UL << DAC_CR_MAMP1_Pos )

#define DAC_CR_WAVE1_Pos                        ( 6U )
#define DAC_CR_WAVE1_Msk                        ( 0x3UL << DAC_CR_WAVE1_Pos )
#define DAC_CR_WAVE1                            ( DAC_CR_WAVE1_Msk )
#define DAC_CR_WAVE1_0                          ( 0x1UL << DAC_CR_WAVE1_Pos )
#define DAC_CR_WAVE1_1                          ( 0x2UL << DAC_CR_WAVE1_Pos )

#define DAC_CR_TSEL1_Pos                        ( 2U )
#define DAC_CR_TSEL1_Msk                        ( 0xFUL << DAC_CR_TSEL1_Pos )
#define DAC_CR_TSEL1                            ( DAC_CR_TSEL1_Msk )
#define DAC_CR_TSEL1_0                          ( 0x1UL << DAC_CR_TSEL1_Pos )
#define DAC_CR_TSEL1_1                          ( 0x2UL << DAC_CR_TSEL1_Pos )
#define DAC_CR_TSEL1_2                          ( 0x4UL << DAC_CR_TSEL1_Pos )
#define DAC_CR_TSEL1_3                          ( 0x8UL << DAC_CR_TSEL1_Pos )

#define DAC_CR_TEN1_Pos                         ( 1U )
#define DAC_CR_TEN1_Msk                         ( 0x1UL << DAC_CR_TEN1_Pos )
#define DAC_CR_TEN1                             ( DAC_CR_TEN1_Msk )

#define DAC_CR_EN1_Pos                          ( 0U )
#define DAC_CR_EN1_Msk                          ( 0x1UL << DAC_CR_EN1_Pos )
#define DAC_CR_EN1                              ( DAC_CR_EN1_Msk )

/***************  Bits definition for DAC_SWTRIGR register  ******************/

#define DAC_SWTRIGR_SWTRIGB2_Pos                ( 17U )
#define DAC_SWTRIGR_SWTRIGB2_Msk                ( 0x1UL << DAC_SWTRIGR_SWTRIGB2_Pos )
#define DAC_SWTRIGR_SWTRIGB2                    ( DAC_SWTRIGR_SWTRIGB2_Msk )

#define DAC_SWTRIGR_SWTRIGB1_Pos                ( 16U )
#define DAC_SWTRIGR_SWTRIGB1_Msk                ( 0x1UL << DAC_SWTRIGR_SWTRIGB1_Pos )
#define DAC_SWTRIGR_SWTRIGB1                    ( DAC_SWTRIGR_SWTRIGB1_Msk )

#define DAC_SWTRIGR_SWTRIG2_Pos                 ( 1U )
#define DAC_SWTRIGR_SWTRIG2_Msk                 ( 0x1UL << DAC_SWTRIGR_SWTRIG2_Pos )
#define DAC_SWTRIGR_SWTRIG2                     ( DAC_SWTRIGR_SWTRIG2_Msk )

#define DAC_SWTRIGR_SWTRIG1_Pos                 ( 0U )
#define DAC_SWTRIGR_SWTRIG1_Msk                 ( 0x1UL << DAC_SWTRIGR_SWTRIG1_Pos )
#define DAC_SWTRIGR_SWTRIG1                     ( DAC_SWTRIGR_SWTRIG1_Msk )


/***************  Bits definition for DAC_DHR12R1 register  ******************/

#define DAC_DHR12R1_DACC1DHRB_Pos               ( 16U )
#define DAC_DHR12R1_DACC1DHRB_Msk               ( 0xFFFUL << DAC_DHR12R1_DACC1DHRB_Pos )
#define DAC_DHR12R1_DACC1DHRB                   ( DAC_DHR12R1_DACC1DHRB_Msk )

#define DAC_DHR12R1_DACC1DHR_Pos                ( 0U )
#define DAC_DHR12R1_DACC1DHR_Msk                ( 0xFFFUL << DAC_DHR12R1_DACC1DHR_Pos )
#define DAC_DHR12R1_DACC1DHR                    ( DAC_DHR12R1_DACC1DHR_Msk )


/***************  Bits definition for DAC_DHR12L1 register  ******************/

#define DAC_DHR12L1_DACC1DHRB_Pos               ( 20U )
#define DAC_DHR12L1_DACC1DHRB_Msk               ( 0xFFFUL << DAC_DHR12L1_DACC1DHRB_Pos )
#define DAC_DHR12L1_DACC1DHRB                   ( DAC_DHR12L1_DACC1DHRB_Msk )

#define DAC_DHR12L1_DACC1DHR_Pos                ( 4U )
#define DAC_DHR12L1_DACC1DHR_Msk                ( 0xFFFUL << DAC_DHR12L1_DACC1DHR_Pos )
#define DAC_DHR12L1_DACC1DHR                    ( DAC_DHR12L1_DACC1DHR_Msk )


/***************  Bits definition for DAC_DHR8R1 register  *******************/

#define DAC_DHR8R1_DACC1DHRB_Pos                ( 8U )
#define DAC_DHR8R1_DACC1DHRB_Msk                ( 0xFFUL << DAC_DHR8R1_DACC1DHRB_Pos )
#define DAC_DHR8R1_DACC1DHRB                    ( DAC_DHR8R1_DACC1DHRB_Msk )

#define DAC_DHR8R1_DACC1DHR_Pos                 ( 0U )
#define DAC_DHR8R1_DACC1DHR_Msk                 ( 0xFFUL << DAC_DHR8R1_DACC1DHR_Pos )
#define DAC_DHR8R1_DACC1DHR                     ( DAC_DHR8R1_DACC1DHR_Msk )


/***************  Bits definition for DAC_DHR12R2 register  ******************/

#define DAC_DHR12R2_DACC2DHRB_Pos               ( 16U )
#define DAC_DHR12R2_DACC2DHRB_Msk               ( 0xFFFUL << DAC_DHR12R2_DACC2DHRB_Pos )
#define DAC_DHR12R2_DACC2DHRB                   ( DAC_DHR12R2_DACC2DHRB_Msk )

#define DAC_DHR12R2_DACC2DHR_Pos                ( 0U )
#define DAC_DHR12R2_DACC2DHR_Msk                ( 0xFFFUL << DAC_DHR12R2_DACC2DHR_Pos )
#define DAC_DHR12R2_DACC2DHR                    ( DAC_DHR12R2_DACC2DHR_Msk )


/***************  Bits definition for DAC_DHR12L2 register  ******************/

#define DAC_DHR12L2_DACC2DHRB_Pos               ( 20U )
#define DAC_DHR12L2_DACC2DHRB_Msk               ( 0xFFFUL << DAC_DHR12L2_DACC2DHRB_Pos )
#define DAC_DHR12L2_DACC2DHRB                   ( DAC_DHR12L2_DACC2DHRB_Msk )

#define DAC_DHR12L2_DACC2DHR_Pos                ( 4U )
#define DAC_DHR12L2_DACC2DHR_Msk                ( 0xFFFUL << DAC_DHR12L2_DACC2DHR_Pos )
#define DAC_DHR12L2_DACC2DHR                    ( DAC_DHR12L2_DACC2DHR_Msk )


/***************  Bits definition for DAC_DHR8R2 register  *******************/

#define DAC_DHR8R2_DACC2DHRB_Pos                ( 8U )
#define DAC_DHR8R2_DACC2DHRB_Msk                ( 0xFFUL << DAC_DHR8R2_DACC2DHRB_Pos )
#define DAC_DHR8R2_DACC2DHRB                    ( DAC_DHR8R2_DACC2DHRB_Msk )

#define DAC_DHR8R2_DACC2DHR_Pos                 ( 0U )
#define DAC_DHR8R2_DACC2DHR_Msk                 ( 0xFFUL << DAC_DHR8R2_DACC2DHR_Pos )
#define DAC_DHR8R2_DACC2DHR                     ( DAC_DHR8R2_DACC2DHR_Msk )


/***************  Bits definition for DAC_DHR12RD register  ******************/

#define DAC_DHR12RD_DACC2DHR_Pos                ( 16U )
#define DAC_DHR12RD_DACC2DHR_Msk                ( 0xFFFUL << DAC_DHR12RD_DACC2DHR_Pos )
#define DAC_DHR12RD_DACC2DHR                    ( DAC_DHR12RD_DACC2DHR_Msk )

#define DAC_DHR12RD_DACC1DHR_Pos                ( 0U )
#define DAC_DHR12RD_DACC1DHR_Msk                ( 0xFFFUL << DAC_DHR12RD_DACC1DHR_Pos )
#define DAC_DHR12RD_DACC1DHR                    ( DAC_DHR12RD_DACC1DHR_Msk )


/***************  Bits definition for DAC_DHR12LD register  ******************/

#define DAC_DHR12LD_DACC2DHR_Pos                ( 20U )
#define DAC_DHR12LD_DACC2DHR_Msk                ( 0xFFFUL << DAC_DHR12LD_DACC2DHR_Pos )
#define DAC_DHR12LD_DACC2DHR                    ( DAC_DHR12LD_DACC2DHR_Msk )

#define DAC_DHR12LD_DACC1DHR_Pos                ( 4U )
#define DAC_DHR12LD_DACC1DHR_Msk                ( 0xFFFUL << DAC_DHR12LD_DACC1DHR_Pos )
#define DAC_DHR12LD_DACC1DHR                    ( DAC_DHR12LD_DACC1DHR_Msk )


/***************  Bits definition for DAC_DHR8RD register  *******************/

#define DAC_DHR8RD_DACC2DHR_Pos                 ( 16U )
#define DAC_DHR8RD_DACC2DHR_Msk                 ( 0xFFUL << DAC_DHR8RD_DACC2DHR_Pos )
#define DAC_DHR8RD_DACC2DHR                     ( DAC_DHR8RD_DACC2DHR_Msk )

#define DAC_DHR8RD_DACC1DHR_Pos                 ( 0U )
#define DAC_DHR8RD_DACC1DHR_Msk                 ( 0xFFUL << DAC_DHR8RD_DACC1DHR_Pos )
#define DAC_DHR8RD_DACC1DHR                     ( DAC_DHR8RD_DACC1DHR_Msk )


/***************  Bits definition for DAC_DOR1 register  *********************/

#define DAC_DOR1_DACC1DORB_Pos                  ( 16U )
#define DAC_DOR1_DACC1DORB_Msk                  ( 0xFFFUL << DAC_DOR1_DACC1DORB_Pos )
#define DAC_DOR1_DACC1DORB                      ( DAC_DOR1_DACC1DORB_Msk )

#define DAC_DOR1_DACC1DOR_Pos                   ( 0U )
#define DAC_DOR1_DACC1DOR_Msk                   ( 0xFFFUL << DAC_DOR1_DACC1DOR_Pos )
#define DAC_DOR1_DACC1DOR                       ( DAC_DOR1_DACC1DOR_Msk )


/***************  Bits definition for DAC_DOR2 register  *********************/

#define DAC_DOR2_DACC2DORB_Pos                  ( 16U )
#define DAC_DOR2_DACC2DORB_Msk                  ( 0xFFFUL << DAC_DOR2_DACC2DORB_Pos )
#define DAC_DOR2_DACC2DORB                      ( DAC_DOR2_DACC2DORB_Msk )

#define DAC_DOR2_DACC2DOR_Pos                   ( 0U )
#define DAC_DOR2_DACC2DOR_Msk                   ( 0xFFFUL << DAC_DOR2_DACC2DOR_Pos )
#define DAC_DOR2_DACC2DOR                       ( DAC_DOR2_DACC2DOR_Msk )


/***************  Bits definition for DAC_SR register  ***********************/

#define DAC_SR_CALFLAG2_Pos                     ( 30U )
#define DAC_SR_CALFLAG2_Msk                     ( 0x1UL << DAC_SR_CALFLAG2_Pos )
#define DAC_SR_CALFLAG2                         ( DAC_SR_CALFLAG2_Msk )

#define DAC_SR_DMAUDR2_Pos                      ( 29U )
#define DAC_SR_DMAUDR2_Msk                      ( 0x1UL << DAC_SR_DMAUDR2_Pos )
#define DAC_SR_DMAUDR2                          ( DAC_SR_DMAUDR2_Msk )

#define DAC_SR_DORSTAT2_Pos                     ( 28U )
#define DAC_SR_DORSTAT2_Msk                     ( 0x1UL << DAC_SR_DORSTAT2_Pos )
#define DAC_SR_DORSTAT2                         ( DAC_SR_DORSTAT2_Msk )

#define DAC_SR_SAMOV2_Pos                       ( 24U )
#define DAC_SR_SAMOV2_Msk                       ( 0x1UL << DAC_SR_SAMOV2_Pos )
#define DAC_SR_SAMOV2                           ( DAC_SR_SAMOV2_Msk )

#define DAC_SR_CALFLAG1_Pos                     ( 14U )
#define DAC_SR_CALFLAG1_Msk                     ( 0x1UL << DAC_SR_CALFLAG1_Pos )
#define DAC_SR_CALFLAG1                         ( DAC_SR_CALFLAG1_Msk )

#define DAC_SR_DMAUDR1_Pos                      ( 13U )
#define DAC_SR_DMAUDR1_Msk                      ( 0x1UL << DAC_SR_DMAUDR1_Pos )
#define DAC_SR_DMAUDR1                          ( DAC_SR_DMAUDR1_Msk )

#define DAC_SR_DORSTAT1_Pos                     ( 12U )
#define DAC_SR_DORSTAT1_Msk                     ( 0x1UL << DAC_SR_DORSTAT1_Pos )
#define DAC_SR_DORSTAT1                         ( DAC_SR_DORSTAT1_Msk )

#define DAC_SR_SAMOV1_Pos                       ( 8U )
#define DAC_SR_SAMOV1_Msk                       ( 0x1UL << DAC_SR_SAMOV1_Pos )
#define DAC_SR_SAMOV1                           ( DAC_SR_SAMOV1_Msk )


/***************  Bits definition for DAC_CCR register  **********************/

#define DAC_CCR_OTRIM2_Pos                      ( 16U )
#define DAC_CCR_OTRIM2_Msk                      ( 0x1FUL << DAC_CCR_OTRIM2_Pos )
#define DAC_CCR_OTRIM2                          ( DAC_CCR_OTRIM2_Msk )
#define DAC_CCR_OTRIM2_0                        ( 0x1UL << DAC_CCR_OTRIM2_Pos )
#define DAC_CCR_OTRIM2_1                        ( 0x2UL << DAC_CCR_OTRIM2_Pos )
#define DAC_CCR_OTRIM2_2                        ( 0x4UL << DAC_CCR_OTRIM2_Pos )
#define DAC_CCR_OTRIM2_3                        ( 0x8UL << DAC_CCR_OTRIM2_Pos )
#define DAC_CCR_OTRIM2_4                        ( 0x10UL << DAC_CCR_OTRIM2_Pos )

#define DAC_CCR_OTRIM1_Pos                      ( 0U )
#define DAC_CCR_OTRIM1_Msk                      ( 0x1FUL << DAC_CCR_OTRIM1_Pos )
#define DAC_CCR_OTRIM1                          ( DAC_CCR_OTRIM1_Msk )
#define DAC_CCR_OTRIM1_0                        ( 0x1UL << DAC_CCR_OTRIM1_Pos )
#define DAC_CCR_OTRIM1_1                        ( 0x2UL << DAC_CCR_OTRIM1_Pos )
#define DAC_CCR_OTRIM1_2                        ( 0x4UL << DAC_CCR_OTRIM1_Pos )
#define DAC_CCR_OTRIM1_3                        ( 0x8UL << DAC_CCR_OTRIM1_Pos )
#define DAC_CCR_OTRIM1_4                        ( 0x10UL << DAC_CCR_OTRIM1_Pos )


/***************  Bits definition for DAC_MCR register  **********************/

#define DAC_MCR_SINFORMAT2_Pos                  ( 25U )
#define DAC_MCR_SINFORMAT2_Msk                  ( 0x1UL << DAC_MCR_SINFORMAT2_Pos )
#define DAC_MCR_SINFORMAT2                      ( DAC_MCR_SINFORMAT2_Msk )

#define DAC_MCR_DMADOUBLE2_Pos                  ( 24U )
#define DAC_MCR_DMADOUBLE2_Msk                  ( 0x1UL << DAC_MCR_DMADOUBLE2_Pos )
#define DAC_MCR_DMADOUBLE2                      ( DAC_MCR_DMADOUBLE2_Msk )

#define DAC_MCR_MODE2_Pos                       ( 16U )
#define DAC_MCR_MODE2_Msk                       ( 0x7UL << DAC_MCR_MODE2_Pos )
#define DAC_MCR_MODE2                           ( DAC_MCR_MODE2_Msk )
#define DAC_MCR_MODE2_0                         ( 0x1UL << DAC_MCR_MODE2_Pos )
#define DAC_MCR_MODE2_1                         ( 0x2UL << DAC_MCR_MODE2_Pos )
#define DAC_MCR_MODE2_2                         ( 0x4UL << DAC_MCR_MODE2_Pos )

#define DAC_MCR_SINFORMAT1_Pos                  ( 9U )
#define DAC_MCR_SINFORMAT1_Msk                  ( 0x1UL << DAC_MCR_SINFORMAT1_Pos )
#define DAC_MCR_SINFORMAT1                      ( DAC_MCR_SINFORMAT1_Msk )

#define DAC_MCR_DMADOUBLE1_Pos                  ( 8U )
#define DAC_MCR_DMADOUBLE1_Msk                  ( 0x1UL << DAC_MCR_DMADOUBLE1_Pos )
#define DAC_MCR_DMADOUBLE1                      ( DAC_MCR_DMADOUBLE1_Msk )

#define DAC_MCR_MODE1_Pos                       ( 0U )
#define DAC_MCR_MODE1_Msk                       ( 0x7UL << DAC_MCR_MODE1_Pos )
#define DAC_MCR_MODE1                           ( DAC_MCR_MODE1_Msk )
#define DAC_MCR_MODE1_0                         ( 0x1UL << DAC_MCR_MODE1_Pos )
#define DAC_MCR_MODE1_1                         ( 0x2UL << DAC_MCR_MODE1_Pos )
#define DAC_MCR_MODE1_2                         ( 0x4UL << DAC_MCR_MODE1_Pos )


/***************  Bits definition for DAC_SHSR1 register  ********************/

#define DAC_SHSR1_TSAMPLE1_Pos                  ( 0U )
#define DAC_SHSR1_TSAMPLE1_Msk                  ( 0x3FFUL << DAC_SHSR1_TSAMPLE1_Pos )
#define DAC_SHSR1_TSAMPLE1                      ( DAC_SHSR1_TSAMPLE1_Msk )


/***************  Bits definition for DAC_SHSR2 register  ********************/

#define DAC_SHSR2_TSAMPLE2_Pos                  ( 0U )
#define DAC_SHSR2_TSAMPLE2_Msk                  ( 0x3FFUL << DAC_SHSR2_TSAMPLE2_Pos )
#define DAC_SHSR2_TSAMPLE2                      ( DAC_SHSR2_TSAMPLE2_Msk )


/***************  Bits definition for DAC_SHHR register  *********************/

#define DAC_SHHR_THOLD2_Pos                     ( 16U )
#define DAC_SHHR_THOLD2_Msk                     ( 0x3FFUL << DAC_SHHR_THOLD2_Pos )
#define DAC_SHHR_THOLD2                         ( DAC_SHHR_THOLD2_Msk )

#define DAC_SHHR_THOLD1_Pos                     ( 0U )
#define DAC_SHHR_THOLD1_Msk                     ( 0x3FFUL << DAC_SHHR_THOLD1_Pos )
#define DAC_SHHR_THOLD1                         ( DAC_SHHR_THOLD1_Msk )


/***************  Bits definition for DAC_SHRR register  *********************/

#define DAC_SHRR_TREFRESH2_Pos                  ( 16U )
#define DAC_SHRR_TREFRESH2_Msk                  ( 0xFFUL << DAC_SHRR_TREFRESH2_Pos )
#define DAC_SHRR_TREFRESH2                      ( DAC_SHRR_TREFRESH2_Msk )

#define DAC_SHRR_TREFRESH1_Pos                  ( 0U )
#define DAC_SHRR_TREFRESH1_Msk                  ( 0xFFUL << DAC_SHRR_TREFRESH1_Pos )
#define DAC_SHRR_TREFRESH1                      ( DAC_SHRR_TREFRESH1_Msk )


/***************  Bits definition for DAC_STR1 register  *********************/

#define DAC_STR1_STINCDATA1_Pos                 ( 16U )
#define DAC_STR1_STINCDATA1_Msk                 ( 0xFFFFUL << DAC_STR1_STINCDATA1_Pos )
#define DAC_STR1_STINCDATA1                     ( DAC_STR1_STINCDATA1_Msk )

#define DAC_STR1_STDIR1_Pos                     ( 12U )
#define DAC_STR1_STDIR1_Msk                     ( 0x1UL << DAC_STR1_STDIR1_Pos )
#define DAC_STR1_STDIR1                         ( DAC_STR1_STDIR1_Msk )

#define DAC_STR1_STRSTDATA1_Pos                 ( 0U )
#define DAC_STR1_STRSTDATA1_Msk                 ( 0xFFFUL << DAC_STR1_STRSTDATA1_Pos )
#define DAC_STR1_STRSTDATA1                     ( DAC_STR1_STRSTDATA1_Msk )


/***************  Bits definition for DAC_STR2 register  *********************/

#define DAC_STR2_STINCDATA2_Pos                 ( 16U )
#define DAC_STR2_STINCDATA2_Msk                 ( 0xFFFFUL << DAC_STR2_STINCDATA2_Pos )
#define DAC_STR2_STINCDATA2                     ( DAC_STR2_STINCDATA2_Msk )

#define DAC_STR2_STDIR2_Pos                     ( 12U )
#define DAC_STR2_STDIR2_Msk                     ( 0x1UL << DAC_STR2_STDIR2_Pos )
#define DAC_STR2_STDIR2                         ( DAC_STR2_STDIR2_Msk )

#define DAC_STR2_STRSTDATA2_Pos                 ( 0U )
#define DAC_STR2_STRSTDATA2_Msk                 ( 0xFFFUL << DAC_STR2_STRSTDATA2_Pos )
#define DAC_STR2_STRSTDATA2                     ( DAC_STR2_STRSTDATA2_Msk )


/***************  Bits definition for DAC_STMODR register  *******************/

#define DAC_STMODR_STINCTRIGSEL2_Pos            ( 24U )
#define DAC_STMODR_STINCTRIGSEL2_Msk            ( 0xFUL << DAC_STMODR_STINCTRIGSEL2_Pos )
#define DAC_STMODR_STINCTRIGSEL2                ( DAC_STMODR_STINCTRIGSEL2_Msk )
#define DAC_STMODR_STINCTRIGSEL2_0              ( 0x1UL << DAC_STMODR_STINCTRIGSEL2_Pos )
#define DAC_STMODR_STINCTRIGSEL2_1              ( 0x2UL << DAC_STMODR_STINCTRIGSEL2_Pos )
#define DAC_STMODR_STINCTRIGSEL2_2              ( 0x4UL << DAC_STMODR_STINCTRIGSEL2_Pos )
#define DAC_STMODR_STINCTRIGSEL2_3              ( 0x8UL << DAC_STMODR_STINCTRIGSEL2_Pos )

#define DAC_STMODR_STRSTTRIGSEL2_Pos            ( 16U )
#define DAC_STMODR_STRSTTRIGSEL2_Msk            ( 0xFUL << DAC_STMODR_STRSTTRIGSEL2_Pos )
#define DAC_STMODR_STRSTTRIGSEL2                ( DAC_STMODR_STRSTTRIGSEL2_Msk )
#define DAC_STMODR_STRSTTRIGSEL2_0              ( 0x1UL << DAC_STMODR_STRSTTRIGSEL2_Pos )
#define DAC_STMODR_STRSTTRIGSEL2_1              ( 0x2UL << DAC_STMODR_STRSTTRIGSEL2_Pos )
#define DAC_STMODR_STRSTTRIGSEL2_2              ( 0x4UL << DAC_STMODR_STRSTTRIGSEL2_Pos )
#define DAC_STMODR_STRSTTRIGSEL2_3              ( 0x8UL << DAC_STMODR_STRSTTRIGSEL2_Pos )

#define DAC_STMODR_STINCTRIGSEL1_Pos            ( 8U )
#define DAC_STMODR_STINCTRIGSEL1_Msk            ( 0xFUL << DAC_STMODR_STINCTRIGSEL1_Pos )
#define DAC_STMODR_STINCTRIGSEL1                ( DAC_STMODR_STINCTRIGSEL1_Msk )
#define DAC_STMODR_STINCTRIGSEL1_0              ( 0x1UL << DAC_STMODR_STINCTRIGSEL1_Pos )
#define DAC_STMODR_STINCTRIGSEL1_1              ( 0x2UL << DAC_STMODR_STINCTRIGSEL1_Pos )
#define DAC_STMODR_STINCTRIGSEL1_2              ( 0x4UL << DAC_STMODR_STINCTRIGSEL1_Pos )
#define DAC_STMODR_STINCTRIGSEL1_3              ( 0x8UL << DAC_STMODR_STINCTRIGSEL1_Pos )

#define DAC_STMODR_STRSTTRIGSEL1_Pos            ( 0U )
#define DAC_STMODR_STRSTTRIGSEL1_Msk            ( 0xFUL << DAC_STMODR_STRSTTRIGSEL1_Pos )
#define DAC_STMODR_STRSTTRIGSEL1                ( DAC_STMODR_STRSTTRIGSEL1_Msk )
#define DAC_STMODR_STRSTTRIGSEL1_0              ( 0x1UL << DAC_STMODR_STRSTTRIGSEL1_Pos )
#define DAC_STMODR_STRSTTRIGSEL1_1              ( 0x2UL << DAC_STMODR_STRSTTRIGSEL1_Pos )
#define DAC_STMODR_STRSTTRIGSEL1_2              ( 0x4UL << DAC_STMODR_STRSTTRIGSEL1_Pos )
#define DAC_STMODR_STRSTTRIGSEL1_3              ( 0x8UL << DAC_STMODR_STRSTTRIGSEL1_Pos )

/***************  Bits definition for MDAC_VDACx_CR  **********************/

#define MDAC_VDACX_CR_CAL_FLAG_Pos                          ( 16U )
#define MDAC_VDACX_CR_CAL_FLAG_Msk                          ( 0x1UL << MDAC_VDACX_CR_CAL_FLAG_Pos )
#define MDAC_VDACX_CR_CAL_FLAG                              ( MDAC_VDACX_CR_CAL_FLAG_Msk )

#define MDAC_VDACX_CR_SAMPLE_EN_Pos                         ( 10U )
#define MDAC_VDACX_CR_SAMPLE_EN_Msk                         ( 0x1UL << MDAC_VDACX_CR_SAMPLE_EN_Pos )
#define MDAC_VDACX_CR_SAMPLE_EN                             ( MDAC_VDACX_CR_SAMPLE_EN_Msk )

#define MDAC_VDACX_CR_OTRIM_Pos                            ( 5U )
#define MDAC_VDACX_CR_OTRIM_Msk                            ( 0x1FL << MDAC_VDACX_CR_OTRIM_Pos )
#define MDAC_VDACX_CR_OTRIM                                ( MDAC_VDACX_CR_OTRIM_Msk )

#define MDAC_VDACX_CR_OTRIM4_Pos                            ( 9U )
#define MDAC_VDACX_CR_OTRIM4_Msk                            ( 0x1UL << MDAC_VDACX_CR_OTRIM4_Pos )
#define MDAC_VDACX_CR_OTRIM4                                ( MDAC_VDACX_CR_OTRIM4_Msk )


#define MDAC_VDACX_CR_OTRIM3_Pos                            ( 8U )
#define MDAC_VDACX_CR_OTRIM3_Msk                            ( 0x1UL << MDAC_VDACX_CR_OTRIM3_Pos )
#define MDAC_VDACX_CR_OTRIM3                                ( MDAC_VDACX_CR_OTRIM3_Msk )


#define MDAC_VDACX_CR_OTRIM2_Pos                            ( 7U )
#define MDAC_VDACX_CR_OTRIM2_Msk                            ( 0x1UL << MDAC_VDACX_CR_OTRIM2_Pos )
#define MDAC_VDACX_CR_OTRIM2                                ( MDAC_VDACX_CR_OTRIM2_Msk )


#define MDAC_VDACX_CR_OTRIM1_Pos                            ( 6U )
#define MDAC_VDACX_CR_OTRIM1_Msk                            ( 0x1UL << MDAC_VDACX_CR_OTRIM1_Pos )
#define MDAC_VDACX_CR_OTRIM1                                ( MDAC_VDACX_CR_OTRIM1_Msk )


#define MDAC_VDACX_CR_OTRIM0_Pos                            ( 5U )
#define MDAC_VDACX_CR_OTRIM0_Msk                            ( 0x1UL << MDAC_VDACX_CR_OTRIM0_Pos )
#define MDAC_VDACX_CR_OTRIM0                                ( MDAC_VDACX_CR_OTRIM0_Msk )


#define MDAC_VDACX_CR_CEN_Pos                               ( 4U )
#define MDAC_VDACX_CR_CEN_Msk                               ( 0x1UL << MDAC_VDACX_CR_CEN_Pos )
#define MDAC_VDACX_CR_CEN                                   ( MDAC_VDACX_CR_CEN_Msk )

#define MDAC_VDACX_CR_MODE_Pos                             ( 1U )
#define MDAC_VDACX_CR_MODE_Msk                             ( 0x7UL << MDAC_VDACX_CR_MODE_Pos )
#define MDAC_VDACX_CR_MODE                                 ( MDAC_VDACX_CR_MODE_Msk )

#define MDAC_VDACX_CR_MODE2_Pos                             ( 3U )
#define MDAC_VDACX_CR_MODE2_Msk                             ( 0x1UL << MDAC_VDACX_CR_MODE2_Pos )
#define MDAC_VDACX_CR_MODE2                                 ( MDAC_VDACX_CR_MODE2_Msk )


#define MDAC_VDACX_CR_MODE1_Pos                             ( 2U )
#define MDAC_VDACX_CR_MODE1_Msk                             ( 0x1UL << MDAC_VDACX_CR_MODE1_Pos )
#define MDAC_VDACX_CR_MODE1                                 ( MDAC_VDACX_CR_MODE1_Msk )


#define MDAC_VDACX_CR_MODE0_Pos                             ( 1U )
#define MDAC_VDACX_CR_MODE0_Msk                             ( 0x1UL << MDAC_VDACX_CR_MODE0_Pos )
#define MDAC_VDACX_CR_MODE0                                 ( MDAC_VDACX_CR_MODE0_Msk )


#define MDAC_VDACX_CR_EN_Pos                                ( 0U )
#define MDAC_VDACX_CR_EN_Msk                                ( 0x1UL << MDAC_VDACX_CR_EN_Pos )
#define MDAC_VDACX_CR_EN                                    ( MDAC_VDACX_CR_EN_Msk )


/***************  Bits definition for MDAC_IDACx_CR  **********************/

#define MDAC_IDACX_CR_ITURE_Pos                            ( 1U )
#define MDAC_IDACX_CR_ITURE_Msk                            ( 0x1FUL << MDAC_IDACX_CR_ITURE_Pos )
#define MDAC_IDACX_CR_ITURE                                ( MDAC_IDACX_CR_ITURE_Msk )

#define MDAC_IDACX_CR_ITURE4_Pos                            ( 5U )
#define MDAC_IDACX_CR_ITURE4_Msk                            ( 0x1UL << MDAC_IDACX_CR_ITURE4_Pos )
#define MDAC_IDACX_CR_ITURE4                                ( MDAC_IDACX_CR_ITURE4_Msk )


#define MDAC_IDACX_CR_ITURE3_Pos                            ( 4U )
#define MDAC_IDACX_CR_ITURE3_Msk                            ( 0x1UL << MDAC_IDACX_CR_ITURE3_Pos )
#define MDAC_IDACX_CR_ITURE3                                ( MDAC_IDACX_CR_ITURE3_Msk )


#define MDAC_IDACX_CR_ITURE2_Pos                            ( 3U )
#define MDAC_IDACX_CR_ITURE2_Msk                            ( 0x1UL << MDAC_IDACX_CR_ITURE2_Pos )
#define MDAC_IDACX_CR_ITURE2                                ( MDAC_IDACX_CR_ITURE2_Msk )


#define MDAC_IDACX_CR_ITURE1_Pos                            ( 2U )
#define MDAC_IDACX_CR_ITURE1_Msk                            ( 0x1UL << MDAC_IDACX_CR_ITURE1_Pos )
#define MDAC_IDACX_CR_ITURE1                                ( MDAC_IDACX_CR_ITURE1_Msk )


#define MDAC_IDACX_CR_ITURE0_Pos                            ( 1U )
#define MDAC_IDACX_CR_ITURE0_Msk                            ( 0x1UL << MDAC_IDACX_CR_ITURE0_Pos )
#define MDAC_IDACX_CR_ITURE0                                ( MDAC_IDACX_CR_ITURE0_Msk )


#define MDAC_IDACX_CR_EN_Pos                                ( 0U )
#define MDAC_IDACX_CR_EN_Msk                                ( 0x1UL << MDAC_IDACX_CR_EN_Pos )
#define MDAC_IDACX_CR_EN                                    ( MDAC_IDACX_CR_EN_Msk )


/***************  Bits definition for MDAC_DACx_DOR  **********************/

#define MDAC_DACX_DOR_DACDOR11_Pos                          ( 11U )
#define MDAC_DACX_DOR_DACDOR11_Msk                          ( 0x1UL << MDAC_DACX_DOR_DACDOR11_Pos )
#define MDAC_DACX_DOR_DACDOR11                              ( MDAC_DACX_DOR_DACDOR11_Msk )


#define MDAC_DACX_DOR_DACDOR10_Pos                          ( 10U )
#define MDAC_DACX_DOR_DACDOR10_Msk                          ( 0x1UL << MDAC_DACX_DOR_DACDOR10_Pos )
#define MDAC_DACX_DOR_DACDOR10                              ( MDAC_DACX_DOR_DACDOR10_Msk )


#define MDAC_DACX_DOR_DACDOR9_Pos                           ( 9U )
#define MDAC_DACX_DOR_DACDOR9_Msk                           ( 0x1UL << MDAC_DACX_DOR_DACDOR9_Pos )
#define MDAC_DACX_DOR_DACDOR9                               ( MDAC_DACX_DOR_DACDOR9_Msk )


#define MDAC_DACX_DOR_DACDOR8_Pos                           ( 8U )
#define MDAC_DACX_DOR_DACDOR8_Msk                           ( 0x1UL << MDAC_DACX_DOR_DACDOR8_Pos )
#define MDAC_DACX_DOR_DACDOR8                               ( MDAC_DACX_DOR_DACDOR8_Msk )


#define MDAC_DACX_DOR_DACDOR7_Pos                           ( 7U )
#define MDAC_DACX_DOR_DACDOR7_Msk                           ( 0x1UL << MDAC_DACX_DOR_DACDOR7_Pos )
#define MDAC_DACX_DOR_DACDOR7                               ( MDAC_DACX_DOR_DACDOR7_Msk )


#define MDAC_DACX_DOR_DACDOR6_Pos                           ( 6U )
#define MDAC_DACX_DOR_DACDOR6_Msk                           ( 0x1UL << MDAC_DACX_DOR_DACDOR6_Pos )
#define MDAC_DACX_DOR_DACDOR6                               ( MDAC_DACX_DOR_DACDOR6_Msk )


#define MDAC_DACX_DOR_DACDOR5_Pos                           ( 5U )
#define MDAC_DACX_DOR_DACDOR5_Msk                           ( 0x1UL << MDAC_DACX_DOR_DACDOR5_Pos )
#define MDAC_DACX_DOR_DACDOR5                               ( MDAC_DACX_DOR_DACDOR5_Msk )


#define MDAC_DACX_DOR_DACDOR4_Pos                           ( 4U )
#define MDAC_DACX_DOR_DACDOR4_Msk                           ( 0x1UL << MDAC_DACX_DOR_DACDOR4_Pos )
#define MDAC_DACX_DOR_DACDOR4                               ( MDAC_DACX_DOR_DACDOR4_Msk )


#define MDAC_DACX_DOR_DACDOR3_Pos                           ( 3U )
#define MDAC_DACX_DOR_DACDOR3_Msk                           ( 0x1UL << MDAC_DACX_DOR_DACDOR3_Pos )
#define MDAC_DACX_DOR_DACDOR3                               ( MDAC_DACX_DOR_DACDOR3_Msk )


#define MDAC_DACX_DOR_DACDOR2_Pos                           ( 2U )
#define MDAC_DACX_DOR_DACDOR2_Msk                           ( 0x1UL << MDAC_DACX_DOR_DACDOR2_Pos )
#define MDAC_DACX_DOR_DACDOR2                               ( MDAC_DACX_DOR_DACDOR2_Msk )


#define MDAC_DACX_DOR_DACDOR1_Pos                           ( 1U )
#define MDAC_DACX_DOR_DACDOR1_Msk                           ( 0x1UL << MDAC_DACX_DOR_DACDOR1_Pos )
#define MDAC_DACX_DOR_DACDOR1                               ( MDAC_DACX_DOR_DACDOR1_Msk )


#define MDAC_DACX_DOR_DACDOR0_Pos                           ( 0U )
#define MDAC_DACX_DOR_DACDOR0_Msk                           ( 0x1UL << MDAC_DACX_DOR_DACDOR0_Pos )
#define MDAC_DACX_DOR_DACDOR0                               ( MDAC_DACX_DOR_DACDOR0_Msk )

/***************  Bits definition for TKEY_SR  **********************/

#define TKEY_SR_MEOC_Pos                                    ( 11U )
#define TKEY_SR_MEOC_Msk                                    ( 0x1UL << TKEY_SR_MEOC_Pos )
#define TKEY_SR_MEOC                                        ( TKEY_SR_MEOC_Msk )

#define TKEY_SR_CHGDONE_Pos                                 ( 10U )
#define TKEY_SR_CHGDONE_Msk                                 ( 0x1UL << TKEY_SR_CHGDONE_Pos )
#define TKEY_SR_CHGDONE                                     ( TKEY_SR_CHGDONE_Msk )

#define TKEY_SR_CHG_Pos                                     ( 9U )
#define TKEY_SR_CHG_Msk                                     ( 0x1UL << TKEY_SR_CHG_Pos )
#define TKEY_SR_CHG                                         ( TKEY_SR_CHG_Msk )

#define TKEY_SR_DONE_Pos                                    ( 8U )
#define TKEY_SR_DONE_Msk                                    ( 0x1UL << TKEY_SR_DONE_Pos )
#define TKEY_SR_DONE                                        ( TKEY_SR_DONE_Msk )

#define TKEY_SR_CHNUM_Pos                                   ( 4U )
#define TKEY_SR_CHNUM_Msk                                   ( 0xfUL << TKEY_SR_CHNUM_Pos )
#define TKEY_SR_CHNUM                                       ( TKEY_SR_CHNUM_Msk )
#define TKEY_SR_CHNUM_0                                     ( 0x1UL << TKEY_SR_CHNUM_Pos )
#define TKEY_SR_CHNUM_1                                     ( 0x2UL << TKEY_SR_CHNUM_Pos )
#define TKEY_SR_CHNUM_2                                     ( 0x4UL << TKEY_SR_CHNUM_Pos )
#define TKEY_SR_CHNUM_3                                     ( 0x8UL << TKEY_SR_CHNUM_Pos )

#define TKEY_SR_BUSY_Pos                                    ( 3U )
#define TKEY_SR_BUSY_Msk                                    ( 0x1UL << TKEY_SR_BUSY_Pos )
#define TKEY_SR_BUSY                                        ( TKEY_SR_BUSY_Msk )

#define TKEY_SR_TIMEOUT_Pos                                 ( 2U )
#define TKEY_SR_TIMEOUT_Msk                                 ( 0x1UL << TKEY_SR_TIMEOUT_Pos )
#define TKEY_SR_TIMEOUT                                     ( TKEY_SR_TIMEOUT_Msk )

#define TKEY_SR_YESTOUCH_Pos                                ( 1U )
#define TKEY_SR_YESTOUCH_Msk                                ( 0x1UL << TKEY_SR_YESTOUCH_Pos )
#define TKEY_SR_YESTOUCH                                    ( TKEY_SR_YESTOUCH_Msk )

#define TKEY_SR_EOC_Pos                                     ( 0U )
#define TKEY_SR_EOC_Msk                                     ( 0x1UL << TKEY_SR_EOC_Pos )
#define TKEY_SR_EOC                                         ( TKEY_SR_EOC_Msk )


/***************  Bits definition for TKEY_IER  **********************/

#define TKEY_IER_MEOCIE_Pos                                 ( 11U )
#define TKEY_IER_MEOCIE_Msk                                 ( 0x1UL << TKEY_IER_MEOCIE_Pos )
#define TKEY_IER_MEOCIE                                     ( TKEY_IER_MEOCIE_Msk )

#define TKEY_IER_CHGDONEIE_Pos                              ( 10U )
#define TKEY_IER_CHGDONEIE_Msk                              ( 0x1UL << TKEY_IER_CHGDONEIE_Pos )
#define TKEY_IER_CHGDONEIE                                  ( TKEY_IESR_CHGDONEIE_Msk )

#define TKEY_IER_CHIE_Pos                                   ( 9U )
#define TKEY_IER_CHIE_Msk                                   ( 0x1UL << TKEY_IER_CHIE_Pos )
#define TKEY_IER_CHIE                                       ( TKEY_IER_CHIE_Msk )

#define TKEY_IER_DONEIE_Pos                                 ( 8U )
#define TKEY_IER_DONEIE_Msk                                 ( 0x1UL << TKEY_IER_DONEIE_Pos )
#define TKEY_IER_DONEIE                                     ( TKEY_IER_DONEIE_Msk )

#define TKEY_IER_TIMEOUTIE_Pos                              ( 2U )
#define TKEY_IER_TIMEOUTIE_Msk                              ( 0x1UL << TKEY_IER_TIMEOUTIE_Pos )
#define TKEY_IER_TIMEOUTIE                                  ( TKEY_IER_TIMEOUTIE_Msk )

#define TKEY_IER_YESTOUCHIE_Pos                             ( 1U )
#define TKEY_IER_YESTOUCHIE_Msk                             ( 0x1UL << TKEY_IER_YESTOUCHIE_Pos )
#define TKEY_IER_YESTOUCHIE                                 ( TKEY_IER_YESTOUCHIE_Msk )

#define TKEY_IER_EOCIE_Pos                                  ( 0U )
#define TKEY_IER_EOCIE_Msk                                  ( 0x1UL << TKEY_IER_EOCIE_Pos )
#define TKEY_IER_EOCIE                                      ( TKEY_IER_EOCIE_Msk )


/***************  Bits definition for TKEY_CR  **********************/

#define TKEY_CR_CHGDONEEN_Pos                               ( 15U )
#define TKEY_CR_CHGDONEEN_Msk                               ( 0x1UL << TKEY_CR_CHGDONEEN_Pos )
#define TKEY_CR_CHGDONEEN                                   ( TKEY_CR_CHGDONEEN_Msk )

#define TKEY_CR_CHGEN_Pos                                   ( 14U )
#define TKEY_CR_CHGEN_Msk                                   ( 0x1UL << TKEY_CR_CHGEN_Pos )
#define TKEY_CR_CHGEN                                       ( TKEY_CR_CHGEN_Msk )

#define TKEY_CR_DISMS_Pos                                   ( 11U )
#define TKEY_CR_DISMS_Msk                                   ( 0x7UL << TKEY_CR_DISMS_Pos )
#define TKEY_CR_DISMS                                       ( TKEY_CR_DISMS_Msk )
#define TKEY_CR_DISMS_0                                     ( 0x1UL << TKEY_CR_DISMS_Pos )
#define TKEY_CR_DISMS_1                                     ( 0x2UL << TKEY_CR_DISMS_Pos )
#define TKEY_CR_DISMS_2                                     ( 0x4UL << TKEY_CR_DISMS_Pos )

#define TKEY_CR_RANDM_Pos                                   ( 9U )
#define TKEY_CR_RANDM_Msk                                   ( 0x3UL << TKEY_CR_RANDM_Pos )
#define TKEY_CR_RANDM                                       ( TKEY_CR_RANDM_Msk )
#define TKEY_CR_RANDM_0                                     ( 0x1UL << TKEY_CR_RANDM_Pos )
#define TKEY_CR_RANDM_1                                     ( 0x2UL << TKEY_CR_RANDM_Pos )

#define TKEY_CR_AUTO_Pos                                    ( 8U )
#define TKEY_CR_AUTO_Msk                                    ( 0x1UL << TKEY_CR_AUTO_Pos )
#define TKEY_CR_AUTO                                        ( TKEY_CR_AUTO_Msk )

#define TKEY_CR_SPREAD_Pos                                  ( 7U )
#define TKEY_CR_SPREAD_Msk                                  ( 0x1UL << TKEY_CR_SPREAD_Pos )
#define TKEY_CR_SPREAD                                      ( TKEY_CR_SPREAD_Msk )

#define TKEY_CR_CONT_Pos                                    ( 6U )
#define TKEY_CR_CONT_Msk                                    ( 0x1UL << TKEY_CR_CONT_Pos )
#define TKEY_CR_CONT                                        ( TKEY_CR_CONT_Msk )

#define TKEY_CR_SHIELDEN_Pos                                ( 5U )
#define TKEY_CR_SHIELDEN_Msk                                ( 0x1UL << TKEY_CR_SHIELDEN_Pos )
#define TKEY_CR_SHIELDEN                                    ( TKEY_CR_SHIELDEN_Msk )

#define TKEY_CR_PCEN_Pos                                    ( 4U )
#define TKEY_CR_PCEN_Msk                                    ( 0x1UL << TKEY_CR_PCEN_Pos )
#define TKEY_CR_PCEN                                        ( TKEY_CR_PCEN_Msk )

#define TKEY_CR_CHEN_Pos                                    ( 3U )
#define TKEY_CR_CHEN_Msk                                    ( 0x1UL << TKEY_CR_CHEN_Pos )
#define TKEY_CR_CHEN                                        ( TKEY_CR_CHEN_Msk )

#define TKEY_CR_START_Pos                                   ( 2U )
#define TKEY_CR_START_Msk                                   ( 0x1UL << TKEY_CR_START_Pos )
#define TKEY_CR_START                                       ( TKEY_CR_START_Msk )

#define TKEY_CR_TKMS_Pos                                    ( 1U )
#define TKEY_CR_TKMS_Msk                                    ( 0x1UL << TKEY_CR_TKMS_Pos )
#define TKEY_CR_TKMS                                        ( TKEY_CR_TKMS_Msk )

#define TKEY_CR_TKEN_Pos                                    ( 0U )
#define TKEY_CR_TKEN_Msk                                    ( 0x1UL << TKEY_CR_TKEN_Pos )
#define TKEY_CR_TKEN                                        ( TKEY_CR_TKEN_Msk )


/***************  Bits definition for TKEY_CFGR1  **********************/

#define TKEY_CFGR1_FLTSEL_Pos                               ( 11U )
#define TKEY_CFGR1_FLTSEL_Msk                               ( 0x7UL << TKEY_CFGR1_FLTSEL_Pos )
#define TKEY_CFGR1_FLTSEL                                   ( TKEY_CFGR1_FLTSEL_Msk )
#define TKEY_CFGR1_FLTSEL_0                                 ( 0x1UL << TKEY_CFGR1_FLTSEL_Pos )
#define TKEY_CFGR1_FLTSEL_1                                 ( 0x2UL << TKEY_CFGR1_FLTSEL_Pos )
#define TKEY_CFGR1_FLTSEL_2                                 ( 0x4UL << TKEY_CFGR1_FLTSEL_Pos )

#define TKEY_CFGR1_SMPSEL_Pos                               ( 9U )
#define TKEY_CFGR1_SMPSEL_Msk                               ( 0x3UL << TKEY_CFGR1_SMPSEL_Pos )
#define TKEY_CFGR1_SMPSEL                                   ( TKEY_CFGR1_SMPSEL_Msk )
#define TKEY_CFGR1_SMPSEL_0                                 ( 0x1UL << TKEY_CFGR1_SMPSEL_Pos )
#define TKEY_CFGR1_SMPSEL_1                                 ( 0x2UL << TKEY_CFGR1_SMPSEL_Pos )

#define TKEY_CFGR1_CCPSEL_Pos                               ( 6U )
#define TKEY_CFGR1_CCPSEL_Msk                               ( 0x7UL << TKEY_CFGR1_CCPSEL_Pos )
#define TKEY_CFGR1_CCPSEL                                   ( TKEY_CFGR1_CCPSEL_Msk )
#define TKEY_CFGR1_CCPSEL_0                                 ( 0x1UL << TKEY_CFGR1_CCPSEL_Pos )
#define TKEY_CFGR1_CCPSEL_1                                 ( 0x2UL << TKEY_CFGR1_CCPSEL_Pos )
#define TKEY_CFGR1_CCPSEL_2                                 ( 0x4UL << TKEY_CFGR1_CCPSEL_Pos )

#define TKEY_CFGR1_RCPSEL_Pos                               ( 4U )
#define TKEY_CFGR1_RCPSEL_Msk                               ( 0x3UL << TKEY_CFGR1_RCPSEL_Pos )
#define TKEY_CFGR1_RCPSEL                                   ( TKEY_CFGR1_RCPSEL_Msk )
#define TKEY_CFGR1_RCPSEL_0                                 ( 0x1UL << TKEY_CFGR1_RCPSEL_Pos )
#define TKEY_CFGR1_RCPSEL_1                                 ( 0x2UL << TKEY_CFGR1_RCPSEL_Pos )

#define TKEY_CFGR1_VCHRSEL_Pos                              ( 2U )
#define TKEY_CFGR1_VCHRSEL_Msk                              ( 0x3UL << TKEY_CFGR1_VCHRSEL_Pos )
#define TKEY_CFGR1_VCHRSEL                                  ( TKEY_CFGR1_VCHRSEL_Msk )
#define TKEY_CFGR1_VCHRSEL_0                                ( 0x1UL << TKEY_CFGR1_VCHRSEL_Pos )
#define TKEY_CFGR1_VCHRSEL_1                                ( 0x2UL << TKEY_CFGR1_VCHRSEL_Pos )

#define TKEY_CFGR1_VCMPSEL_Pos                              ( 0U )
#define TKEY_CFGR1_VCMPSEL_Msk                              ( 0x3UL << TKEY_CFGR1_VCMPSEL_Pos )
#define TKEY_CFGR1_VCMPSEL                                  ( TKEY_CFGR1_VCMPSEL_Msk )
#define TKEY_CFGR1_VCMPSEL_0                                ( 0x1UL << TKEY_CFGR1_VCMPSEL_Pos )
#define TKEY_CFGR1_VCMPSEL_1                                ( 0x2UL << TKEY_CFGR1_VCMPSEL_Pos )


/***************  Bits definition for TKEY_CFGR2  **********************/

#define TKEY_CFGR2_IDISSEL_Pos                              ( 8U )
#define TKEY_CFGR2_IDISSEL_Msk                              ( 0xffUL << TKEY_CFGR2_IDISSEL_Pos )
#define TKEY_CFGR2_IDISSEL                                  ( TKEY_CFGR2_IDISSEL_Msk )
#define TKEY_CFGR2_IDISSEL_0                                ( 0x1UL << TKEY_CFGR2_IDISSEL_Pos )
#define TKEY_CFGR2_IDISSEL_1                                ( 0x2UL << TKEY_CFGR2_IDISSEL_Pos )
#define TKEY_CFGR2_IDISSEL_2                                ( 0x4UL << TKEY_CFGR2_IDISSEL_Pos )
#define TKEY_CFGR2_IDISSEL_3                                ( 0x8UL << TKEY_CFGR2_IDISSEL_Pos )
#define TKEY_CFGR2_IDISSEL_4                                ( 0x10UL << TKEY_CFGR2_IDISSEL_Pos )
#define TKEY_CFGR2_IDISSEL_5                                ( 0x20UL << TKEY_CFGR2_IDISSEL_Pos )
#define TKEY_CFGR2_IDISSEL_6                                ( 0x40UL << TKEY_CFGR2_IDISSEL_Pos )
#define TKEY_CFGR2_IDISSEL_7                                ( 0x80UL << TKEY_CFGR2_IDISSEL_Pos )

#define TKEY_CFGR2_RDISSEL_Pos                              ( 0U )
#define TKEY_CFGR2_RDISSEL_Msk                              ( 0xffUL << TKEY_CFGR2_RDISSEL_Pos )
#define TKEY_CFGR2_RDISSEL                                  ( TKEY_CFGR2_RDISSEL_Msk )
#define TKEY_CFGR2_RDISSEL_0                                ( 0x1UL << TKEY_CFGR2_RDISSEL_Pos )
#define TKEY_CFGR2_RDISSEL_1                                ( 0x2UL << TKEY_CFGR2_RDISSEL_Pos )
#define TKEY_CFGR2_RDISSEL_2                                ( 0x4UL << TKEY_CFGR2_RDISSEL_Pos )
#define TKEY_CFGR2_RDISSEL_3                                ( 0x8UL << TKEY_CFGR2_RDISSEL_Pos )
#define TKEY_CFGR2_RDISSEL_4                                ( 0x10UL << TKEY_CFGR2_RDISSEL_Pos )
#define TKEY_CFGR2_RDISSEL_5                                ( 0x20UL << TKEY_CFGR2_RDISSEL_Pos )
#define TKEY_CFGR2_RDISSEL_6                                ( 0x40UL << TKEY_CFGR2_RDISSEL_Pos )
#define TKEY_CFGR2_RDISSEL_7                                ( 0x80UL << TKEY_CFGR2_RDISSEL_Pos )


/***************  Bits definition for TKEY_SMPCR  **********************/

#define TKEY_INTVLR_INTERVAL_Pos                            ( 0U )
#define TKEY_INTVLR_INTERVAL_Msk                            ( 0xffffUL << TKEY_SMPCR_GAP_Pos )
#define TKEY_INTVLR_INTERVAL                                ( TKEY_SMPCR_GAP_Msk )

/***************  Bits definition for TKEY_CCR  **********************/

#define TKEY_DIVR_SCANCLKDIV_Pos                            ( 8U )
#define TKEY_DIVR_SCANCLKDIV_Msk                            ( 0xffUL << TKEY_DIVR_SCANCLKDIV_Pos )
#define TKEY_DIVR_SCANCLKDIV                                ( TKEY_DIVR_SCANCLKDIV_Msk )
#define TKEY_DIVR_SCANCLKDIV_0                              ( 0x1UL << TKEY_DIVR_SCANCLKDIV_Pos )
#define TKEY_DIVR_SCANCLKDIV_1                              ( 0x2UL << TKEY_DIVR_SCANCLKDIV_Pos )
#define TKEY_DIVR_SCANCLKDIV_2                              ( 0x4UL << TKEY_DIVR_SCANCLKDIV_Pos )
#define TKEY_DIVR_SCANCLKDIV_3                              ( 0x8UL << TKEY_DIVR_SCANCLKDIV_Pos )
#define TKEY_DIVR_SCANCLKDIV_4                              ( 0x10UL << TKEY_DIVR_SCANCLKDIV_Pos )
#define TKEY_DIVR_SCANCLKDIV_5                              ( 0x20UL << TKEY_DIVR_SCANCLKDIV_Pos )
#define TKEY_DIVR_SCANCLKDIV_6                              ( 0x40UL << TKEY_DIVR_SCANCLKDIV_Pos )
#define TKEY_DIVR_SCANCLKDIV_7                              ( 0x80UL << TKEY_DIVR_SCANCLKDIV_Pos )

#define TKEY_DIVR_SMPCLKDIV_Pos                             ( 0U )
#define TKEY_DIVR_SMPCLKDIV_Msk                             ( 0xffUL << TKEY_DIVR_SMPCLKDIV_Pos )
#define TKEY_DIVR_SMPCLKDIV                                 ( TKEY_DIVR_SMPCLKDIV_Msk )
#define TKEY_DIVR_SMPCLKDIV_0                               ( 0x1UL << TKEY_DIVR_SMPCLKDIV_Pos )
#define TKEY_DIVR_SMPCLKDIV_1                               ( 0x2UL << TKEY_DIVR_SMPCLKDIV_Pos )
#define TKEY_DIVR_SMPCLKDIV_2                               ( 0x4UL << TKEY_DIVR_SMPCLKDIV_Pos )
#define TKEY_DIVR_SMPCLKDIV_3                               ( 0x8UL << TKEY_DIVR_SMPCLKDIV_Pos )
#define TKEY_DIVR_SMPCLKDIV_4                               ( 0x10UL << TKEY_DIVR_SMPCLKDIV_Pos )
#define TKEY_DIVR_SMPCLKDIV_5                               ( 0x20UL << TKEY_DIVR_SMPCLKDIV_Pos )
#define TKEY_DIVR_SMPCLKDIV_6                               ( 0x40UL << TKEY_DIVR_SMPCLKDIV_Pos )
#define TKEY_DIVR_SMPCLKDIV_7                               ( 0x80UL << TKEY_DIVR_SMPCLKDIV_Pos )


/***************  Bits definition for TKEY_SCCR  **********************/

#define TKEY_SCCR_SW1H_Pos                                  ( 8U )
#define TKEY_SCCR_SW1H_Msk                                  ( 0xffUL << TKEY_SCCR_SW1H_Pos )
#define TKEY_SCCR_SW1H                                      ( TKEY_SCCR_SW1H_Msk )
#define TKEY_SCCR_SW1H_0                                    ( 0x1UL << TKEY_SCCR_SW1H_Pos )
#define TKEY_SCCR_SW1H_1                                    ( 0x2UL << TKEY_SCCR_SW1H_Pos )
#define TKEY_SCCR_SW1H_2                                    ( 0x4UL << TKEY_SCCR_SW1H_Pos )
#define TKEY_SCCR_SW1H_3                                    ( 0x8UL << TKEY_SCCR_SW1H_Pos )
#define TKEY_SCCR_SW1H_4                                    ( 0x10UL << TKEY_SCCR_SW1H_Pos )
#define TKEY_SCCR_SW1H_5                                    ( 0x20UL << TKEY_SCCR_SW1H_Pos )
#define TKEY_SCCR_SW1H_6                                    ( 0x40UL << TKEY_SCCR_SW1H_Pos )
#define TKEY_SCCR_SW1H_7                                    ( 0x80UL << TKEY_SCCR_SW1H_Pos )

#define TKEY_SCCR_SW1L_Pos                                  ( 0U )
#define TKEY_SCCR_SW1L_Msk                                  ( 0xffUL << TKEY_SCCR_SW1L_Pos )
#define TKEY_SCCR_SW1L                                      ( TKEY_SCCR_SW1L_Msk )
#define TKEY_SCCR_SW1L_0                                    ( 0x1UL << TKEY_SCCR_SW1L_Pos )
#define TKEY_SCCR_SW1L_1                                    ( 0x2UL << TKEY_SCCR_SW1L_Pos )
#define TKEY_SCCR_SW1L_2                                    ( 0x4UL << TKEY_SCCR_SW1L_Pos )
#define TKEY_SCCR_SW1L_3                                    ( 0x8UL << TKEY_SCCR_SW1L_Pos )
#define TKEY_SCCR_SW1L_4                                    ( 0x10UL << TKEY_SCCR_SW1L_Pos )
#define TKEY_SCCR_SW1L_5                                    ( 0x20UL << TKEY_SCCR_SW1L_Pos )
#define TKEY_SCCR_SW1L_6                                    ( 0x40UL << TKEY_SCCR_SW1L_Pos )
#define TKEY_SCCR_SW1L_7                                    ( 0x80UL << TKEY_SCCR_SW1L_Pos )


/***************  Bits definition for TKEY_TSETR  **********************/

#define TKEY_TSETR_TEST_Pos                                 ( 4U )
#define TKEY_TSETR_TEST_Msk                                 ( 0xfffUL << TKEY_TSETR_TEST_Pos )
#define TKEY_TSETR_TEST                                     ( TKEY_TSETR_TEST_Msk )
#define TKEY_TSETR_TEST_0                                   ( 0x1UL << TKEY_TSETR_TEST_Pos )
#define TKEY_TSETR_TEST_1                                   ( 0x2UL << TKEY_TSETR_TEST_Pos )
#define TKEY_TSETR_TEST_2                                   ( 0x4UL << TKEY_TSETR_TEST_Pos )
#define TKEY_TSETR_TEST_3                                   ( 0x8UL << TKEY_TSETR_TEST_Pos )
#define TKEY_TSETR_TEST_4                                   ( 0x10UL << TKEY_TSETR_TEST_Pos )
#define TKEY_TSETR_TEST_5                                   ( 0x20UL << TKEY_TSETR_TEST_Pos )
#define TKEY_TSETR_TEST_6                                   ( 0x40UL << TKEY_TSETR_TEST_Pos )
#define TKEY_TSETR_TEST_7                                   ( 0x80UL << TKEY_TSETR_TEST_Pos )

#define TKEY_TSETR_CST_Pos                                  ( 0U )
#define TKEY_TSETR_CST_Msk                                  ( 0xfUL << TKEY_TSETR_CST_Pos )
#define TKEY_TSETR_CST                                      ( TKEY_TSETR_CST_Msk )
#define TKEY_TSETR_CST_0                                    ( 0x1UL << TKEY_TSETR_CST_Pos )
#define TKEY_TSETR_CST_1                                    ( 0x2UL << TKEY_TSETR_CST_Pos )
#define TKEY_TSETR_CST_2                                    ( 0x4UL << TKEY_TSETR_CST_Pos )
#define TKEY_TSETR_CST_3                                    ( 0x8UL << TKEY_TSETR_CST_Pos )


/***************  Bits definition for TKEY_CXENR  **********************/

#define TKEY_CXENR_CX15EN_Pos                               ( 15U )
#define TKEY_CXENR_CX15EN_Msk                               ( 0x1UL << TKEY_CXENR_CX15EN_Pos )
#define TKEY_CXENR_CX15EN                                   ( TKEY_CXENR_CX15EN_Msk )

#define TKEY_CXENR_CX14EN_Pos                               ( 14U )
#define TKEY_CXENR_CX14EN_Msk                               ( 0x1UL << TKEY_CXENR_CX14EN_Pos )
#define TKEY_CXENR_CX14EN                                   ( TKEY_CXENR_CX14EN_Msk )

#define TKEY_CXENR_CX13EN_Pos                               ( 13U )
#define TKEY_CXENR_CX13EN_Msk                               ( 0x1UL << TKEY_CXENR_CX13EN_Pos )
#define TKEY_CXENR_CX13EN                                   ( TKEY_CXENR_CX13EN_Msk )

#define TKEY_CXENR_CX12EN_Pos                               ( 12U )
#define TKEY_CXENR_CX12EN_Msk                               ( 0x1UL << TKEY_CXENR_CX12EN_Pos )
#define TKEY_CXENR_CX12EN                                   ( TKEY_CXENR_CX12EN_Msk )

#define TKEY_CXENR_CX11EN_Pos                               ( 11U )
#define TKEY_CXENR_CX11EN_Msk                               ( 0x1UL << TKEY_CXENR_CX11EN_Pos )
#define TKEY_CXENR_CX11EN                                   ( TKEY_CXENR_CX11EN_Msk )

#define TKEY_CXENR_CX10EN_Pos                               ( 10U )
#define TKEY_CXENR_CX10EN_Msk                               ( 0x1UL << TKEY_CXENR_CX10EN_Pos )
#define TKEY_CXENR_CX10EN                                   ( TKEY_CXENR_CX10EN_Msk )

#define TKEY_CXENR_CX9EN_Pos                                ( 9U )
#define TKEY_CXENR_CX9EN_Msk                                ( 0x1UL << TKEY_CXENR_CX9EN_Pos )
#define TKEY_CXENR_CX9EN                                    ( TKEY_CXENR_CX9EN_Msk )

#define TKEY_CXENR_CX8EN_Pos                                ( 8U )
#define TKEY_CXENR_CX8EN_Msk                                ( 0x1UL << TKEY_CXENR_CX8EN_Pos )
#define TKEY_CXENR_CX8EN                                    ( TKEY_CXENR_CX8EN_Msk )

#define TKEY_CXENR_CX7EN_Pos                                ( 7U )
#define TKEY_CXENR_CX7EN_Msk                                ( 0x1UL << TKEY_CXENR_CX7EN_Pos )
#define TKEY_CXENR_CX7EN                                    ( TKEY_CXENR_CX7EN_Msk )

#define TKEY_CXENR_CX6EN_Pos                                ( 6U )
#define TKEY_CXENR_CX6EN_Msk                                ( 0x1UL << TKEY_CXENR_CX6EN_Pos )
#define TKEY_CXENR_CX6EN                                    ( TKEY_CXENR_CX6EN_Msk )

#define TKEY_CXENR_CX5EN_Pos                                ( 5U )
#define TKEY_CXENR_CX5EN_Msk                                ( 0x1UL << TKEY_CXENR_CX5EN_Pos )
#define TKEY_CXENR_CX5EN                                    ( TKEY_CXENR_CX5EN_Msk )

#define TKEY_CXENR_CX4EN_Pos                                ( 4U )
#define TKEY_CXENR_CX4EN_Msk                                ( 0x1UL << TKEY_CXENR_CX4EN_Pos )
#define TKEY_CXENR_CX4EN                                    ( TKEY_CXENR_CX4EN_Msk )

#define TKEY_CXENR_CX3EN_Pos                                ( 3U )
#define TKEY_CXENR_CX3EN_Msk                                ( 0x1UL << TKEY_CXENR_CX3EN_Pos )
#define TKEY_CXENR_CX3EN                                    ( TKEY_CXENR_CX3EN_Msk )

#define TKEY_CXENR_CX2EN_Pos                                ( 2U )
#define TKEY_CXENR_CX2EN_Msk                                ( 0x1UL << TKEY_CXENR_CX2EN_Pos )
#define TKEY_CXENR_CX2EN                                    ( TKEY_CXENR_CX2EN_Msk )

#define TKEY_CXENR_CX1EN_Pos                                ( 1U )
#define TKEY_CXENR_CX1EN_Msk                                ( 0x1UL << TKEY_CXENR_CX1EN_Pos )
#define TKEY_CXENR_CX1EN                                    ( TKEY_CXENR_CX1EN_Msk )

#define TKEY_CXENR_CX0EN_Pos                                ( 0U )
#define TKEY_CXENR_CX0EN_Msk                                ( 0x1UL << TKEY_CXENR_CX0EN_Pos )
#define TKEY_CXENR_CX0EN                                    ( TKEY_CXENR_CX0EN_Msk )


/***************  Bits definition for TKEY_DR  **********************/

#define TKEY_DR_DATA_Pos                                    ( 0U )
#define TKEY_DR_DATA_Msk                                    ( 0xffffUL << TKEY_DR_DATA_Pos )
#define TKEY_DR_DATA                                        ( TKEY_DR_DATA_Msk )


/***************  Bits definition for TKEY_THx  **********************/

#define TKEY_THX_DNX_Pos                                    ( 0U )
#define TKEY_THX_DNX_Msk                                    ( 0xffUL << TKEY_THX_DNX_Pos )
#define TKEY_THX_DNX                                        ( TKEY_THX_DNX_Msk )


/***************  Bits definition for TKEY_CHx  **********************/

#define TKEY_CHX_CNTX_Pos                                   ( 0U )
#define TKEY_CHX_CNTX_Msk                                   ( 0xffffUL << TKEY_CHX_CNTX_Pos )
#define TKEY_CHX_CNTX                                       ( TKEY_CHX_CNTX_Msk )


/***************  Bits definition for TKEY_CFLTR  **********************/

#define TKEY_CFLTR_CFLTNUM_Pos                              ( 1U )
#define TKEY_CFLTR_CFLTNUM_Msk                              ( 0xfUL << TKEY_CFLTR_CFLTNUM_Pos )
#define TKEY_CFLTR_CFLTNUM                                  ( TKEY_CFLTR_CFLTNUM_Msk )
#define TKEY_CFLTR_CFLTNUM_0                                ( 0x1UL << TKEY_CFLTR_CFLTNUM_Pos )
#define TKEY_CFLTR_CFLTNUM_1                                ( 0x2UL << TKEY_CFLTR_CFLTNUM_Pos )
#define TKEY_CFLTR_CFLTNUM_2                                ( 0x4UL << TKEY_CFLTR_CFLTNUM_Pos )
#define TKEY_CFLTR_CFLTNUM_3                                ( 0x8UL << TKEY_CFLTR_CFLTNUM_Pos )

#define TKEY_CFLTR_CFLTEN_Pos                               ( 0U )
#define TKEY_CFLTR_CFLTEN_Msk                               ( 0x1UL << TKEY_CFLTR_CFLTEN_Pos )
#define TKEY_CFLTR_CFLTEN                                   ( TKEY_CFLTR_CFLTEN_Msk )


/***************  Bits definition for TKEY_NSETR  **********************/

#define TKEY_NSETR_CHGNUM_Pos                               ( 0U )
#define TKEY_NSETR_CHGNUM_Msk                               ( 0xffffUL << TKEY_NSETR_CHGNUM_Pos )
#define TKEY_NSETR_CHGNUM                                   ( TKEY_NSETR_CHGNUM_Msk )


/***************  Bits definition for TKEY_TWAITR  **********************/

#define TKEY_TWAITR_WAITTIME_Pos                            ( 0U )
#define TKEY_TWAITR_WAITTIME_Msk                            ( 0xffffUL << TKEY_TWAITR_WAITTIME_Pos )
#define TKEY_TWAITR_WAITTIME                                ( TKEY_TWAITR_WAITTIME_Msk )


/***************  Bits definition for TKEY_MUTUALR  **********************/

#define TKEY_MUTUALR_TXNUM_Pos                              ( 11U )
#define TKEY_MUTUALR_TXNUM_Msk                              ( 0x1fUL << TKEY_MUTUALR_TXNUM_Pos )
#define TKEY_MUTUALR_TXNUM                                  ( TKEY_MUTUALR_TXNUM_Msk )

#define TKEY_MUTUALR_MTXDLY_Pos                             ( 3U )
#define TKEY_MUTUALR_MTXDLY_Msk                             ( 0xffUL << TKEY_MUTUALR_MTXDLY_Pos )
#define TKEY_MUTUALR_MTXDLY                                 ( TKEY_MUTUALR_MTXDLY_Msk )

#define TKEY_MUTUALR_MTXDLYEN_Pos                           ( 2U )
#define TKEY_MUTUALR_MTXDLYEN_Msk                           ( 0x1UL << TKEY_MUTUALR_MTXDLYEN_Pos )
#define TKEY_MUTUALR_MTXDLYEN                               ( TKEY_MUTUALR_MTXDLYEN_Msk )

#define TKEY_MUTUALR_MTXRST_Pos                             ( 1U )
#define TKEY_MUTUALR_MTXRST_Msk                             ( 0x1UL << TKEY_MUTUALR_MTXRST_Pos )
#define TKEY_MUTUALR_MTXRST                                 ( TKEY_MUTUALR_MTXRST_Msk )

#define TKEY_MUTUALR_MUTUALEN_Pos                           ( 0U )
#define TKEY_MUTUALR_MUTUALEN_Msk                           ( 0x1UL << TKEY_MUTUALR_MUTUALEN_Pos )
#define TKEY_MUTUALR_MUTUALEN                               ( TKEY_MUTUALR_MUTUALEN_Msk )


/***************  Bits definition for TKEY_TXENR1  **********************/

#define TKEY_TXENR1_TX15EN_Pos                              ( 15U )
#define TKEY_TXENR1_TX15EN_Msk                              ( 0x1UL << TKEY_TXENR1_TX15EN_Pos )
#define TKEY_TXENR1_TX15EN                                  ( TKEY_TXENR1_TX15EN_Msk )

#define TKEY_TXENR1_TX14EN_Pos                              ( 14U )
#define TKEY_TXENR1_TX14EN_Msk                              ( 0x1UL << TKEY_TXENR1_TX14EN_Pos )
#define TKEY_TXENR1_TX14EN                                  ( TKEY_TXENR1_TX14EN_Msk )

#define TKEY_TXENR1_TX13EN_Pos                              ( 13U )
#define TKEY_TXENR1_TX13EN_Msk                              ( 0x1UL << TKEY_TXENR1_TX13EN_Pos )
#define TKEY_TXENR1_TX13EN                                  ( TKEY_TXENR1_TX13EN_Msk )

#define TKEY_TXENR1_TX12EN_Pos                              ( 12U )
#define TKEY_TXENR1_TX12EN_Msk                              ( 0x1UL << TKEY_TXENR1_TX12EN_Pos )
#define TKEY_TXENR1_TX12EN                                  ( TKEY_TXENR1_TX12EN_Msk )

#define TKEY_TXENR1_TX11EN_Pos                              ( 11U )
#define TKEY_TXENR1_TX11EN_Msk                              ( 0x1UL << TKEY_TXENR1_TX11EN_Pos )
#define TKEY_TXENR1_TX11EN                                  ( TKEY_TXENR1_TX11EN_Msk )

#define TKEY_TXENR1_TX10EN_Pos                              ( 10U )
#define TKEY_TXENR1_TX10EN_Msk                              ( 0x1UL << TKEY_TXENR1_TX10EN_Pos )
#define TKEY_TXENR1_TX10EN                                  ( TKEY_TXENR1_TX10EN_Msk )

#define TKEY_TXENR1_TX9EN_Pos                               ( 9U )
#define TKEY_TXENR1_TX9EN_Msk                               ( 0x1UL << TKEY_TXENR1_TX9EN_Pos )
#define TKEY_TXENR1_TX9EN                                   ( TKEY_TXENR1_TX9EN_Msk )

#define TKEY_TXENR1_TX8EN_Pos                               ( 8U )
#define TKEY_TXENR1_TX8EN_Msk                               ( 0x1UL << TKEY_TXENR1_TX8EN_Pos )
#define TKEY_TXENR1_TX8EN                                   ( TKEY_TXENR1_TX8EN_Msk )

#define TKEY_TXENR1_TX7EN_Pos                               ( 7U )
#define TKEY_TXENR1_TX7EN_Msk                               ( 0x1UL << TKEY_TXENR1_TX7EN_Pos )
#define TKEY_TXENR1_TX7EN                                   ( TKEY_TXENR1_TX7EN_Msk )

#define TKEY_TXENR1_TX6EN_Pos                               ( 6U )
#define TKEY_TXENR1_TX6EN_Msk                               ( 0x1UL << TKEY_TXENR1_TX6EN_Pos )
#define TKEY_TXENR1_TX6EN                                   ( TKEY_TXENR1_TX6EN_Msk )

#define TKEY_TXENR1_TX5EN_Pos                               ( 5U )
#define TKEY_TXENR1_TX5EN_Msk                               ( 0x1UL << TKEY_TXENR1_TX5EN_Pos )
#define TKEY_TXENR1_TX5EN                                   ( TKEY_TXENR1_TX5EN_Msk )

#define TKEY_TXENR1_TX4EN_Pos                               ( 4U )
#define TKEY_TXENR1_TX4EN_Msk                               ( 0x1UL << TKEY_TXENR1_TX4EN_Pos )
#define TKEY_TXENR1_TX4EN                                   ( TKEY_TXENR1_TX4EN_Msk )

#define TKEY_TXENR1_TX3EN_Pos                               ( 3U )
#define TKEY_TXENR1_TX3EN_Msk                               ( 0x1UL << TKEY_TXENR1_TX3EN_Pos )
#define TKEY_TXENR1_TX3EN                                   ( TKEY_TXENR1_TX3EN_Msk )

#define TKEY_TXENR1_TX2EN_Pos                               ( 2U )
#define TKEY_TXENR1_TX2EN_Msk                               ( 0x1UL << TKEY_TXENR1_TX2EN_Pos )
#define TKEY_TXENR1_TX2EN                                   ( TKEY_TXENR1_TX2EN_Msk )

#define TKEY_TXENR1_TX1EN_Pos                               ( 1U )
#define TKEY_TXENR1_TX1EN_Msk                               ( 0x1UL << TKEY_TXENR1_TX1EN_Pos )
#define TKEY_TXENR1_TX1EN                                   ( TKEY_TXENR1_TX1EN_Msk )

#define TKEY_TXENR1_TX0EN_Pos                               ( 0U )
#define TKEY_TXENR1_TX0EN_Msk                               ( 0x1UL << TKEY_TXENR1_TX0EN_Pos )
#define TKEY_TXENR1_TX0EN                                   ( TKEY_TXENR1_TX0EN_Msk )


/***************  Bits definition for TKEY_TXENR1  **********************/


#define TKEY_TXENR2_TX27EN_Pos                              ( 11U )
#define TKEY_TXENR2_TX27EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX27EN_Pos )
#define TKEY_TXENR2_TX27EN                                  ( TKEY_TXENR2_TX27EN_Msk )

#define TKEY_TXENR2_TX26EN_Pos                              ( 10U )
#define TKEY_TXENR2_TX26EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX26EN_Pos )
#define TKEY_TXENR2_TX26EN                                  ( TKEY_TXENR1_TX26EN_Msk )

#define TKEY_TXENR2_TX25EN_Pos                              ( 9U )
#define TKEY_TXENR2_TX25EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX25EN_Pos )
#define TKEY_TXENR2_TX25EN                                  ( TKEY_TXENR2_TX25EN_Msk )

#define TKEY_TXENR2_TX24EN_Pos                              ( 8U )
#define TKEY_TXENR2_TX24EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX24EN_Pos )
#define TKEY_TXENR2_TX24EN                                  ( TKEY_TXENR2_TX24EN_Msk )

#define TKEY_TXENR2_TX23EN_Pos                              ( 7U )
#define TKEY_TXENR2_TX23EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX23EN_Pos )
#define TKEY_TXENR2_TX23EN                                  ( TKEY_TXENR2_TX23EN_Msk )

#define TKEY_TXENR2_TX22EN_Pos                              ( 6U )
#define TKEY_TXENR2_TX22EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX22EN_Pos )
#define TKEY_TXENR2_TX22EN                                  ( TKEY_TXENR2_TX22EN_Msk )

#define TKEY_TXENR2_TX21EN_Pos                              ( 5U )
#define TKEY_TXENR2_TX21EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX21EN_Pos )
#define TKEY_TXENR2_TX21EN                                  ( TKEY_TXENR2_TX21EN_Msk )

#define TKEY_TXENR2_TX20EN_Pos                              ( 4U )
#define TKEY_TXENR2_TX20EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX20EN_Pos )
#define TKEY_TXENR2_TX20EN                                    TKEY_TXENR2_TX20EN_Msk )

#define TKEY_TXENR2_TX19EN_Pos                              ( 3U )
#define TKEY_TXENR2_TX19EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX19EN_Pos )
#define TKEY_TXENR2_TX19EN                                  ( TKEY_TXENR2_TX19EN_Msk )

#define TKEY_TXENR2_TX18EN_Pos                              ( 2U )
#define TKEY_TXENR2_TX18EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX18EN_Pos )
#define TKEY_TXENR2_TX18EN                                  ( TKEY_TXENR2_TX18EN_Msk )

#define TKEY_TXENR2_TX17EN_Pos                              ( 1U )
#define TKEY_TXENR2_TX17EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX17EN_Pos )
#define TKEY_TXENR2_TX17EN                                  ( TKEY_TXENR2_TX17EN_Msk )

#define TKEY_TXENR2_TX16EN_Pos                              ( 0U )
#define TKEY_TXENR2_TX16EN_Msk                              ( 0x1UL << TKEY_TXENR2_TX16EN_Pos )
#define TKEY_TXENR2_TX16EN                                  ( TKEY_TXENR2_TX16EN_Msk )


/***************  Bits definition for OSPI_DAT  **********************/

#define OSPI_TX_DAT_TX_DAT2_Pos                             ( 8U )
#define OSPI_TX_DAT_TX_DAT2_Msk                             ( 0xffffffUL << OSPI_TX_DAT_TX_DAT2_Pos )
#define OSPI_TX_DAT_TX_DAT2                                 ( OSPI_TX_DAT_TX_DAT2_Msk )

#define OSPI_TX_RX_DAT_Pos                                  ( 0U )
#define OSPI_TX_RX_DAT_Msk                                  ( 0xffUL << OSPI_TX_DAT_TX_DAT1_Pos )
#define OSPI_TX_RX_DAT                                      ( OSPI_TX_DAT_TX_DAT1_Msk )


/***************  Bits definition for OSPI_BAUD  **********************/

#define OSPI_BAUD_DIV2_Pos                                  ( 8U )
#define OSPI_BAUD_DIV2_Msk                                  ( 0xffUL << OSPI_BAUD_DIV2_Pos )
#define OSPI_BAUD_DIV2                                      ( OSPI_BAUD_DIV2_Msk )
#define OSPI_BAUD_DIV2_0                                    ( 0x1UL << OSPI_BAUD_DIV2_Pos )
#define OSPI_BAUD_DIV2_1                                    ( 0x2UL << OSPI_BAUD_DIV2_Pos )
#define OSPI_BAUD_DIV2_2                                    ( 0x4UL << OSPI_BAUD_DIV2_Pos )
#define OSPI_BAUD_DIV2_3                                    ( 0x8UL << OSPI_BAUD_DIV2_Pos )
#define OSPI_BAUD_DIV2_4                                    ( 0x10UL << OSPI_BAUD_DIV2_Pos )
#define OSPI_BAUD_DIV2_5                                    ( 0x20UL << OSPI_BAUD_DIV2_Pos )
#define OSPI_BAUD_DIV2_6                                    ( 0x40UL << OSPI_BAUD_DIV2_Pos )
#define OSPI_BAUD_DIV2_7                                    ( 0x80UL << OSPI_BAUD_DIV2_Pos )

#define OSPI_BAUD_DIV1_Pos                                  ( 0U )
#define OSPI_BAUD_DIV1_Msk                                  ( 0xffUL << OSPI_BAUD_DIV1_Pos )
#define OSPI_BAUD_DIV1                                      ( OSPI_BAUD_DIV1_Msk )
#define OSPI_BAUD_DIV1_0                                    ( 0x1UL << OSPI_BAUD_DIV1_Pos )
#define OSPI_BAUD_DIV1_1                                    ( 0x2UL << OSPI_BAUD_DIV1_Pos )
#define OSPI_BAUD_DIV1_2                                    ( 0x4UL << OSPI_BAUD_DIV1_Pos )
#define OSPI_BAUD_DIV1_3                                    ( 0x8UL << OSPI_BAUD_DIV1_Pos )
#define OSPI_BAUD_DIV1_4                                    ( 0x10UL << OSPI_BAUD_DIV1_Pos )
#define OSPI_BAUD_DIV1_5                                    ( 0x20UL << OSPI_BAUD_DIV1_Pos )
#define OSPI_BAUD_DIV1_6                                    ( 0x40UL << OSPI_BAUD_DIV1_Pos )
#define OSPI_BAUD_DIV1_7                                    ( 0x80UL << OSPI_BAUD_DIV1_Pos )


/***************  Bits definition for OSPI_CTL  **********************/

#define OSPI_CTL_FR_MODE_Pos                                ( 30U )
#define OSPI_CTL_FR_MODE_Msk                                ( 0x3UL << OSPI_CTL_FR_MODE_Pos )
#define OSPI_CTL_FR_MODE                                    ( OSPI_CTL_FR_MODE_Msk )
#define OSPI_CTL_FR_MODE_0                                  ( 0x1UL << OSPI_CTL_FR_MODE_Pos )
#define OSPI_CTL_FR_MODE_1                                  ( 0x2UL << OSPI_CTL_FR_MODE_Pos )

#define OSPI_CTL_FW_MODE_Pos                                ( 28U )
#define OSPI_CTL_FW_MODE_Msk                                ( 0x3UL << OSPI_CTL_FW_MODE_Pos )
#define OSPI_CTL_FW_MODE                                    ( OSPI_CTL_FW_MODE_Msk )
#define OSPI_CTL_FW_MODE_0                                  ( 0x1UL << OSPI_CTL_FW_MODE_Pos )
#define OSPI_CTL_FW_MODE_1                                  ( 0x2UL << OSPI_CTL_FW_MODE_Pos )

#define OSPI_CTL_DMCTRL_Pos                                 ( 27U )
#define OSPI_CTL_DMCTRL_Msk                                 ( 0x1UL << OSPI_CTL_DMCTRL_Pos )
#define OSPI_CTL_DMCTRL                                     ( OSPI_CTL_DMCTRL_Msk )

#define OSPI_CTL_DM_EN_Pos                                  ( 26U )
#define OSPI_CTL_DM_EN_Msk                                  ( 0x1UL << OSPI_CTL_DM_EN_Pos )
#define OSPI_CTL_DM_EN                                      ( OSPI_CTL_DM_EN_Msk )

#define OSPI_CTL_APMD_CLK_Pos                               ( 23U )
#define OSPI_CTL_APMD_CLK_Msk                               ( 0x7UL << OSPI_CTL_APMD_CLK_Pos )
#define OSPI_CTL_APMD_CLK                                   ( OSPI_CTL_APMD_CLK_Msk )
#define OSPI_CTL_APMD_CLK_0                                 ( 0x1UL << OSPI_CTL_APMD_CLK_Pos )
#define OSPI_CTL_APMD_CLK_1                                 ( 0x2UL << OSPI_CTL_APMD_CLK_Pos )
#define OSPI_CTL_APMD_CLK_2                                 ( 0x4UL << OSPI_CTL_APMD_CLK_Pos )

#define OSPI_CTL_MEM_MODE_Pos                               ( 21U )
#define OSPI_CTL_MEM_MODE_Msk                               ( 0x3UL << OSPI_CTL_MEM_MODE_Pos )
#define OSPI_CTL_MEM_MODE                                   ( OSPI_CTL_MEM_MODE_Msk )
#define OSPI_CTL_MEM_MODE_0                                 ( 0x1UL << OSPI_CTL_MEM_MODE_Pos )
#define OSPI_CTL_MEM_MODE_1                                 ( 0x2UL << OSPI_CTL_MEM_MODE_Pos )

#define OSPI_CTL_CS_TIME_Pos                                ( 11U )
#define OSPI_CTL_CS_TIME_Msk                                ( 0xffUL << OSPI_CTL_CS_TIME_Pos )
#define OSPI_CTL_CS_TIME                                    ( OSPI_CTL_CS_TIME_Msk )
#define OSPI_CTL_CS_TIME_0                                  ( 0x1UL << OSPI_CTL_CS_TIME_Pos )
#define OSPI_CTL_CS_TIME_1                                  ( 0x2UL << OSPI_CTL_CS_TIME_Pos )
#define OSPI_CTL_CS_TIME_2                                  ( 0x4UL << OSPI_CTL_CS_TIME_Pos )
#define OSPI_CTL_CS_TIME_3                                  ( 0x8UL << OSPI_CTL_CS_TIME_Pos )
#define OSPI_CTL_CS_TIME_4                                  ( 0x10UL << OSPI_CTL_CS_TIME_Pos )
#define OSPI_CTL_CS_TIME_5                                  ( 0x20UL << OSPI_CTL_CS_TIME_Pos )
#define OSPI_CTL_CS_TIME_6                                  ( 0x40UL << OSPI_CTL_CS_TIME_Pos )
#define OSPI_CTL_CS_TIME_7                                  ( 0x80UL << OSPI_CTL_CS_TIME_Pos )

#define OSPI_CTL_DQSOE_Pos                                  ( 9U )
#define OSPI_CTL_DQSOE_Msk                                  ( 0x1UL << OSPI_CTL_DQSOE_Pos )
#define OSPI_CTL_DQSOE                                      ( OSPI_CTL_DQSOE_Msk )

#define OSPI_CTL_DTRM_Pos                                   ( 8U )
#define OSPI_CTL_DTRM_Msk                                   ( 0x1UL << OSPI_CTL_DTRM_Pos )
#define OSPI_CTL_DTRM                                       ( OSPI_CTL_DTRM_Msk )

#define OSPI_CTL_IO_MODE_Pos                                ( 7U )
#define OSPI_CTL_IO_MODE_Msk                                ( 0x1UL << OSPI_CTL_IO_MODE_Pos )
#define OSPI_CTL_IO_MODE                                    ( OSPI_CTL_IO_MODE_Msk )

#define OSPI_CTL_X_MODE_Pos                                 ( 5U )
#define OSPI_CTL_X_MODE_Msk                                 ( 0x3UL << OSPI_CTL_X_MODE_Pos )
#define OSPI_CTL_X_MODE                                     ( OSPI_CTL_X_MODE_Msk )
#define OSPI_CTL_X_MODE_0                                   ( 0x1UL << OSPI_CTL_X_MODE_Pos )
#define OSPI_CTL_X_MODE_1                                   ( 0x2UL << OSPI_CTL_X_MODE_Pos )

#define OSPI_CTL_LSB_FIRST_Pos                              ( 4U )
#define OSPI_CTL_LSB_FIRST_Msk                              ( 0x1UL << OSPI_CTL_LSB_FIRST_Pos )
#define OSPI_CTL_LSB_FIRST                                  ( OSPI_CTL_LSB_FIRST_Msk )

#define OSPI_CTL_CPOL_Pos                                   ( 3U )
#define OSPI_CTL_CPOL_Msk                                   ( 0x1UL << OSPI_CTL_CPOL_Pos )
#define OSPI_CTL_CPOL                                       ( OSPI_CTL_CPOL_Msk )

#define OSPI_CTL_CPHA_Pos                                   ( 2U )
#define OSPI_CTL_CPHA_Msk                                   ( 0x1UL << OSPI_CTL_CPHA_Pos )
#define OSPI_CTL_CPHA                                       ( OSPI_CTL_CPHA_Msk )

#define OSPI_CTL_MST_MODE_Pos                               ( 0U )
#define OSPI_CTL_MST_MODE_Msk                               ( 0x1UL << OSPI_CTL_MST_MODE_Pos )
#define OSPI_CTL_MST_MODE                                   ( OSPI_CTL_MST_MODE_Msk )


/***************  Bits definition for OSPI_TX_CTL  **********************/

#define OSPI_TX_CTL_OUTDLY_Pos                              ( 16U )
#define OSPI_TX_CTL_OUTDLY_Msk                              ( 0x3UL << OSPI_TX_CTL_OUTDLY_Pos )
#define OSPI_TX_CTL_OUTDLY                                  ( OSPI_TX_CTL_OUTDLY_Msk )
#define OSPI_TX_CTL_OUTDLY_0                                ( 0x1UL << OSPI_TX_CTL_OUTDLY_Pos )
#define OSPI_TX_CTL_OUTDLY_1                                ( 0x2UL << OSPI_TX_CTL_OUTDLY_Pos )

#define OSPI_TX_CTL_DUMMY_Pos                               ( 8U )
#define OSPI_TX_CTL_DUMMY_Msk                               ( 0xffUL << OSPI_TX_CTL_DUMMY_Pos )
#define OSPI_TX_CTL_DUMMY                                   ( OSPI_TX_CTL_DUMMY_Msk )
#define OSPI_TX_CTL_DUMMY_0                                 ( 0x1UL << OSPI_TX_CTL_DUMMY_Pos )
#define OSPI_TX_CTL_DUMMY_1                                 ( 0x2UL << OSPI_TX_CTL_DUMMY_Pos )
#define OSPI_TX_CTL_DUMMY_2                                 ( 0x4UL << OSPI_TX_CTL_DUMMY_Pos )
#define OSPI_TX_CTL_DUMMY_3                                 ( 0x8UL << OSPI_TX_CTL_DUMMY_Pos )
#define OSPI_TX_CTL_DUMMY_4                                 ( 0x10UL << OSPI_TX_CTL_DUMMY_Pos )
#define OSPI_TX_CTL_DUMMY_5                                 ( 0x20UL << OSPI_TX_CTL_DUMMY_Pos )
#define OSPI_TX_CTL_DUMMY_6                                 ( 0x40UL << OSPI_TX_CTL_DUMMY_Pos )
#define OSPI_TX_CTL_DUMMY_7                                 ( 0x80UL << OSPI_TX_CTL_DUMMY_Pos )

#define OSPI_TX_CTL_TX_DMA_LEVEL_Pos                        ( 4U )
#define OSPI_TX_CTL_TX_DMA_LEVEL_Msk                        ( 0xfUL << OSPI_TX_CTL_TX_DMA_LEVEL_Pos )
#define OSPI_TX_CTL_TX_DMA_LEVEL                            ( OSPI_TX_CTL_TX_DMA_LEVEL_Msk )
#define OSPI_TX_CTL_TX_DMA_LEVEL_0                          ( 0x1UL << OSPI_TX_CTL_TX_DMA_LEVEL_Pos )
#define OSPI_TX_CTL_TX_DMA_LEVEL_1                          ( 0x2UL << OSPI_TX_CTL_TX_DMA_LEVEL_Pos )
#define OSPI_TX_CTL_TX_DMA_LEVEL_2                          ( 0x4UL << OSPI_TX_CTL_TX_DMA_LEVEL_Pos )
#define OSPI_TX_CTL_TX_DMA_LEVEL_3                          ( 0x8UL << OSPI_TX_CTL_TX_DMA_LEVEL_Pos )

#define OSPI_TX_CTL_TX_DMA_REQ_EN_Pos                       ( 3U )
#define OSPI_TX_CTL_TX_DMA_REQ_EN_Msk                       ( 0x1UL << OSPI_TX_CTL_TX_DMA_REQ_EN_Pos )
#define OSPI_TX_CTL_TX_DMA_REQ_EN                           ( OSPI_TX_CTL_TX_DMA_REQ_EN_Msk )

#define OSPI_TX_CTL_TX_FIFO_RESET_Pos                       ( 1U )
#define OSPI_TX_CTL_TX_FIFO_RESET_Msk                       ( 0x1UL << OSPI_TX_CTL_TX_FIFO_RESET_Pos )
#define OSPI_TX_CTL_TX_FIFO_RESET                           ( OSPI_TX_CTL_TX_FIFO_RESET_Msk )

#define OSPI_TX_CTL_TX_EN_Pos                               ( 0U )
#define OSPI_TX_CTL_TX_EN_Msk                               ( 0x1UL << OSPI_TX_CTL_TX_EN_Pos )
#define OSPI_TX_CTL_TX_EN                                   ( OSPI_TX_CTL_TX_EN_Msk )


/***************  Bits definition for OSPI_RX_CTL  **********************/

#define OSPI_RX_CTL_SSHIFT_Pos                              ( 28U )
#define OSPI_RX_CTL_SSHIFT_Msk                              ( 0xfUL << OSPI_RX_CTL_SSHIFT_Pos )
#define OSPI_RX_CTL_SSHIFT                                  ( OSPI_RX_CTL_SSHIFT_Msk )
#define OSPI_RX_CTL_SSHIFT_0                                ( 0x1UL << OSPI_RX_CTL_SSHIFT_Pos )
#define OSPI_RX_CTL_SSHIFT_1                                ( 0x2UL << OSPI_RX_CTL_SSHIFT_Pos )
#define OSPI_RX_CTL_SSHIFT_2                                ( 0x4UL << OSPI_RX_CTL_SSHIFT_Pos )
#define OSPI_RX_CTL_SSHIFT_3                                ( 0x8UL << OSPI_RX_CTL_SSHIFT_Pos )

#define OSPI_RX_CTL_MSDHA_X7_Pos                            ( 26U )
#define OSPI_RX_CTL_MSDHA_X7_Msk                            ( 0x1UL << OSPI_RX_CTL_MSDHA_X7_Pos )
#define OSPI_RX_CTL_MSDHA_X7                                ( OSPI_RX_CTL_MSDHA_X7_Msk )

#define OSPI_RX_CTL_MSDHA_X6_Pos                            ( 25U )
#define OSPI_RX_CTL_MSDHA_X6_Msk                            ( 0x1UL << OSPI_RX_CTL_MSDHA_X6_Pos )
#define OSPI_RX_CTL_MSDHA_X6                                ( OSPI_RX_CTL_MSDHA_X6_Msk )

#define OSPI_RX_CTL_MSDHA_X5_Pos                            ( 24U )
#define OSPI_RX_CTL_MSDHA_X5_Msk                            ( 0x1UL << OSPI_RX_CTL_MSDHA_X5_Pos )
#define OSPI_RX_CTL_MSDHA_X5                                ( OSPI_RX_CTL_MSDHA_X5_Msk )

#define OSPI_RX_CTL_MSDHA_X4_Pos                            ( 23U )
#define OSPI_RX_CTL_MSDHA_X4_Msk                            ( 0x1UL << OSPI_RX_CTL_MSDHA_X4_Pos )
#define OSPI_RX_CTL_MSDHA_X4                                ( OSPI_RX_CTL_MSDHA_X4_Msk )

#define OSPI_RX_CTL_MSDHA_X3_Pos                            ( 22U )
#define OSPI_RX_CTL_MSDHA_X3_Msk                            ( 0x1UL << OSPI_RX_CTL_MSDHA_X3_Pos )
#define OSPI_RX_CTL_MSDHA_X3                                ( OSPI_RX_CTL_MSDHA_X3_Msk )

#define OSPI_RX_CTL_MSDHA_X2_Pos                            ( 21U )
#define OSPI_RX_CTL_MSDHA_X2_Msk                            ( 0x1UL << OSPI_RX_CTL_MSDHA_X2_Pos )
#define OSPI_RX_CTL_MSDHA_X2                                ( OSPI_RX_CTL_MSDHA_X2_Msk )

#define OSPI_RX_CTL_MSDHA_X1_Pos                            ( 20U )
#define OSPI_RX_CTL_MSDHA_X1_Msk                            ( 0x1UL << OSPI_RX_CTL_MSDHA_X1_Pos )
#define OSPI_RX_CTL_MSDHA_X1                                ( OSPI_RX_CTL_MSDHA_X1_Msk )

#define OSPI_RX_CTL_MSDHA_X0_Pos                            ( 19U )
#define OSPI_RX_CTL_MSDHA_X0_Msk                            ( 0x1UL << OSPI_RX_CTL_MSDHA_X0_Pos )
#define OSPI_RX_CTL_MSDHA_X0                                ( OSPI_RX_CTL_MSDHA_X0_Msk )

#define OSPI_RX_CTL_MSDA_X7_Pos                             ( 18U )
#define OSPI_RX_CTL_MSDA_X7_Msk                             ( 0x1UL << OSPI_RX_CTL_MSDA_X7_Pos )
#define OSPI_RX_CTL_MSDA_X7                                 ( OSPI_RX_CTL_MSDA_X7_Msk )

#define OSPI_RX_CTL_MSDA_X6_Pos                             ( 17U )
#define OSPI_RX_CTL_MSDA_X6_Msk                             ( 0x1UL << OSPI_RX_CTL_MSDA_X6_Pos )
#define OSPI_RX_CTL_MSDA_X6                                 ( OSPI_RX_CTL_MSDA_X6_Msk )

#define OSPI_RX_CTL_MSDA_X5_Pos                             ( 16U )
#define OSPI_RX_CTL_MSDA_X5_Msk                             ( 0x1UL << OSPI_RX_CTL_MSDA_X5_Pos )
#define OSPI_RX_CTL_MSDA_X5                                 ( OSPI_RX_CTL_MSDA_X5_Msk )

#define OSPI_RX_CTL_MSDA_X4_Pos                             ( 15U )
#define OSPI_RX_CTL_MSDA_X4_Msk                             ( 0x1UL << OSPI_RX_CTL_MSDA_X4_Pos )
#define OSPI_RX_CTL_MSDA_X4                                 ( OSPI_RX_CTL_MSDA_X4_Msk )

#define OSPI_RX_CTL_MSDA_X3_Pos                             ( 14U )
#define OSPI_RX_CTL_MSDA_X3_Msk                             ( 0x1UL << OSPI_RX_CTL_MSDA_X3_Pos )
#define OSPI_RX_CTL_MSDA_X3                                 ( OSPI_RX_CTL_MSDA_X3_Msk )

#define OSPI_RX_CTL_MSDA_X2_Pos                             ( 13U )
#define OSPI_RX_CTL_MSDA_X2_Msk                             ( 0x1UL << OSPI_RX_CTL_MSDA_X2_Pos )
#define OSPI_RX_CTL_MSDA_X2                                 ( OSPI_RX_CTL_MSDA_X2_Msk )

#define OSPI_RX_CTL_MSDA_X1_Pos                             ( 12U )
#define OSPI_RX_CTL_MSDA_X1_Msk                             ( 0x1UL << OSPI_RX_CTL_MSDA_X1_Pos )
#define OSPI_RX_CTL_MSDA_X1                                 ( OSPI_RX_CTL_MSDA_X1_Msk )

#define OSPI_RX_CTL_MSDA_X0_Pos                             ( 11U )
#define OSPI_RX_CTL_MSDA_X0_Msk                             ( 0x1UL << OSPI_RX_CTL_MSDA_X0_Pos )
#define OSPI_RX_CTL_MSDA_X0                                 ( OSPI_RX_CTL_MSDA_X0_Msk )

#define OSPI_RX_CTL_MSDA_EN_Pos                             ( 10U )
#define OSPI_RX_CTL_MSDA_EN_Msk                             ( 0x1UL << OSPI_RX_CTL_MSDA_EN_Pos )
#define OSPI_RX_CTL_MSDA_EN                                 ( OSPI_RX_CTL_MSDA_EN_Msk )

#define OSPI_RX_CTL_DQS_SAMP_EN_Pos                         ( 8U )
#define OSPI_RX_CTL_DQS_SAMP_EN_Msk                         ( 0x1UL << OSPI_RX_CTL_DQS_SAMP_EN_Pos )
#define OSPI_RX_CTL_DQS_SAMP_EN                             ( OSPI_RX_CTL_DQS_SAMP_EN_Msk )

#define OSPI_RX_CTL_RX_DMA_LEVEL_Pos                        ( 4U )
#define OSPI_RX_CTL_RX_DMA_LEVEL_Msk                        ( 0xfUL << OSPI_RX_CTL_RX_DMA_LEVEL_Pos )
#define OSPI_RX_CTL_RX_DMA_LEVEL                            ( OSPI_RX_CTL_RX_DMA_LEVEL_Msk )
#define OSPI_RX_CTL_RX_DMA_LEVEL_0                          ( 0x1UL << OSPI_RX_CTL_RX_DMA_LEVEL_Pos )
#define OSPI_RX_CTL_RX_DMA_LEVEL_1                          ( 0x2UL << OSPI_RX_CTL_RX_DMA_LEVEL_Pos )
#define OSPI_RX_CTL_RX_DMA_LEVEL_2                          ( 0x4UL << OSPI_RX_CTL_RX_DMA_LEVEL_Pos )
#define OSPI_RX_CTL_RX_DMA_LEVEL_3                          ( 0x8UL << OSPI_RX_CTL_RX_DMA_LEVEL_Pos )

#define OSPI_RX_CTL_RX_DMA_REQ_EN_Pos                       ( 3U )
#define OSPI_RX_CTL_RX_DMA_REQ_EN_Msk                       ( 0x1UL << OSPI_RX_CTL_RX_DMA_REQ_EN_Pos )
#define OSPI_RX_CTL_RX_DMA_REQ_EN                           ( OSPI_RX_CTL_RX_DMA_REQ_EN_Msk )

#define OSPI_RX_CTL_RX_FIFO_RESET_Pos                       ( 1U )
#define OSPI_RX_CTL_RX_FIFO_RESET_Msk                       ( 0x1UL << OSPI_RX_CTL_RX_FIFO_RESET_Pos )
#define OSPI_RX_CTL_RX_FIFO_RESET                           ( OSPI_RX_CTL_RX_FIFO_RESET_Msk )

#define OSPI_RX_CTL_RX_EN_Pos                               ( 0U )
#define OSPI_RX_CTL_RX_EN_Msk                               ( 0x1UL << OSPI_RX_CTL_RX_EN_Pos )
#define OSPI_RX_CTL_RX_EN                                   ( OSPI_RX_CTL_RX_EN_Msk )


/***************  Bits definition for OSPI_IE  **********************/

#define OSPI_IE_RX_BATCH_DONE_EN_Pos                        ( 15U )
#define OSPI_IE_RX_BATCH_DONE_EN_Msk                        ( 0x1UL << OSPI_IE_RX_BATCH_DONE_EN_Pos )
#define OSPI_IE_RX_BATCH_DONE_EN                            ( OSPI_IE_RX_BATCH_DONE_EN_Msk )

#define OSPI_IE_TX_BATCH_DONE_EN_Pos                        ( 14U )
#define OSPI_IE_TX_BATCH_DONE_EN_Msk                        ( 0x1UL << OSPI_IE_TX_BATCH_DONE_EN_Pos )
#define OSPI_IE_TX_BATCH_DONE_EN                            ( OSPI_IE_TX_BATCH_DONE_EN_Msk )

#define OSPI_IE_RX_FIFO_NOT_EMPTY_EN_Pos                    ( 11U )
#define OSPI_IE_RX_FIFO_NOT_EMPTY_EN_Msk                    ( 0x1UL << OSPI_IE_RX_FIFO_NOT_EMPTY_EN_Pos )
#define OSPI_IE_RX_FIFO_NOT_EMPTY_EN                        ( OSPI_IE_RX_FIFO_NOT_EMPTY_EN_Msk )

#define OSPI_IE_RX_FIFO_HALF_FULL_EN_Pos                    ( 9U )
#define OSPI_IE_RX_FIFO_HALF_FULL_EN_Msk                    ( 0x1UL << OSPI_IE_RX_FIFO_HALF_FULL_EN_Pos )
#define OSPI_IE_RX_FIFO_HALF_FULL_EN                        ( OSPI_IE_RX_FIFO_HALF_FULL_EN_Msk )

#define OSPI_IE_RX_FIFO_HALF_EMPTY_EN_Pos                   ( 8U )
#define OSPI_IE_RX_FIFO_HALF_EMPTY_EN_Msk                   ( 0x1UL << OSPI_IE_RX_FIFO_HALF_EMPTY_EN_Pos )
#define OSPI_IE_RX_FIFO_HALF_EMPTY_EN                       ( OSPI_IE_RX_FIFO_HALF_EMPTY_EN_Msk )

#define OSPI_IE_TX_FIFO_HALF_FULL_EN_Pos                    ( 7U )
#define OSPI_IE_TX_FIFO_HALF_FULL_EN_Msk                    ( 0x1UL << OSPI_IE_TX_FIFO_HALF_FULL_EN_Pos )
#define OSPI_IE_TX_FIFO_HALF_FULL_EN                        ( OSPI_IE_TX_FIFO_HALF_FULL_EN_Msk )

#define OSPI_IE_TX_FIFO_HALF_EMPTY_EN_Pos                   ( 6U )
#define OSPI_IE_TX_FIFO_HALF_EMPTY_EN_Msk                   ( 0x1UL << OSPI_IE_TX_FIFO_HALF_EMPTY_EN_Pos )
#define OSPI_IE_TX_FIFO_HALF_EMPTY_EN                       ( OSPI_IE_TX_FIFO_HALF_EMPTY_EN_Msk )

#define OSPI_IE_RX_FIFO_FULL_EN_Pos                         ( 5U )
#define OSPI_IE_RX_FIFO_FULL_EN_Msk                         ( 0x1UL << OSPI_IE_RX_FIFO_FULL_EN_Pos )
#define OSPI_IE_RX_FIFO_FULL_EN                             ( OSPI_IE_RX_FIFO_FULL_EN_Msk )

#define OSPI_IE_RX_FIFO_EMPTY_EN_Pos                        ( 4U )
#define OSPI_IE_RX_FIFO_EMPTY_EN_Msk                        ( 0x1UL << OSPI_IE_RX_FIFO_EMPTY_EN_Pos )
#define OSPI_IE_RX_FIFO_EMPTY_EN                            ( OSPI_IE_RX_FIFO_EMPTY_EN_Msk )

#define OSPI_IE_TX_FIFO_FULL_EN_Pos                         ( 3U )
#define OSPI_IE_TX_FIFO_FULL_EN_Msk                         ( 0x1UL << OSPI_IE_TX_FIFO_FULL_EN_Pos )
#define OSPI_IE_TX_FIFO_FULL_EN                             ( OSPI_IE_TX_FIFO_FULL_EN_Msk )

#define OSPI_IE_TX_FIFO_EMPTY_EN_Pos                        ( 2U )
#define OSPI_IE_TX_FIFO_EMPTY_EN_Msk                        ( 0x1UL << OSPI_IE_TX_FIFO_EMPTY_EN_Pos )
#define OSPI_IE_TX_FIFO_EMPTY_EN                            ( OSPI_IE_TX_FIFO_EMPTY_EN_Msk )

#define OSPI_IE_BATCH_DONE_EN_Pos                           ( 1U )
#define OSPI_IE_BATCH_DONE_EN_Msk                           ( 0x1UL << OSPI_IE_BATCH_DONE_EN_Pos )
#define OSPI_IE_BATCH_DONE_EN                               ( OSPI_IE_BATCH_DONE_EN_Msk )


/***************  Bits definition for OSPI_STATUS  **********************/


#define OSPI_STATUS_INSTR_SEND_DONE_Pos                     ( 18U )
#define OSPI_STATUS_INSTR_SEND_DONE_Msk                     ( 0x1UL << OSPI_STATUS_INSTR_SEND_DONE_Pos )
#define OSPI_STATUS_INSTR_SEND_DONE                         ( OSPI_STATUS_INSTR_SEND_DONE_Msk )

#define OSPI_STATUS_RWDS_Pos                                ( 17U )
#define OSPI_STATUS_RWDS_Msk                                ( 0x1UL << OSPI_STATUS_RWDS_Pos )
#define OSPI_STATUS_RWDS                                    ( OSPI_STATUS_RWDS_Msk )

#define OSPI_STATUS_APM_DUMY_DONE_Pos                       ( 16U )
#define OSPI_STATUS_APM_DUMY_DONE_Msk                       ( 0x1UL << OSPI_STATUS_APM_DUMY_DONE_Pos )
#define OSPI_STATUS_APM_DUMY_DONE                           ( OSPI_STATUS_APM_DUMY_DONE_Msk )

#define OSPI_STATUS_RX_BATCH_DONE_Pos                       ( 15U )
#define OSPI_STATUS_RX_BATCH_DONE_Msk                       ( 0x1UL << OSPI_STATUS_RX_BATCH_DONE_Pos )
#define OSPI_STATUS_RX_BATCH_DONE                           ( OSPI_STATUS_RX_BATCH_DONE_Msk )

#define OSPI_STATUS_TX_BATCH_DONE_Pos                       ( 14U )
#define OSPI_STATUS_TX_BATCH_DONE_Msk                       ( 0x1UL << OSPI_STATUS_TX_BATCH_DONE_Pos )
#define OSPI_STATUS_TX_BATCH_DONE                           ( OSPI_STATUS_TX_BATCH_DONE_Msk )

#define OSPI_STATUS_RX_FIFO_NOT_EMPTY_Pos                   ( 11U )
#define OSPI_STATUS_RX_FIFO_NOT_EMPTY_Msk                   ( 0x1UL << OSPI_STATUS_RX_FIFO_NOT_EMPTY_Pos )
#define OSPI_STATUS_RX_FIFO_NOT_EMPTY                       ( OSPI_STATUS_RX_FIFO_NOT_EMPTY_Msk )

#define OSPI_STATUS_RX_FIFO_HALF_FULL_Pos                   ( 9U )
#define OSPI_STATUS_RX_FIFO_HALF_FULL_Msk                   ( 0x1UL << OSPI_STATUS_RX_FIFO_HALF_FULL_Pos )
#define OSPI_STATUS_RX_FIFO_HALF_FULL                       ( OSPI_STATUS_RX_FIFO_HALF_FULL_Msk )

#define OSPI_STATUS_RX_FIFO_HALF_EMPTY_Pos                  ( 8U )
#define OSPI_STATUS_RX_FIFO_HALF_EMPTY_Msk                  ( 0x1UL << OSPI_STATUS_RX_FIFO_HALF_EMPTY_Pos )
#define OSPI_STATUS_RX_FIFO_HALF_EMPTY                      ( OSPI_STATUS_RX_FIFO_HALF_EMPTY_Msk )

#define OSPI_STATUS_TX_FIFO_HALF_FULL_Pos                   ( 7U )
#define OSPI_STATUS_TX_FIFO_HALF_FULL_Msk                   ( 0x1UL << OSPI_STATUS_TX_FIFO_HALF_FULL_Pos )
#define OSPI_STATUS_TX_FIFO_HALF_FULL                       ( OSPI_STATUS_TX_FIFO_HALF_FULL_Msk )

#define OSPI_STATUS_TX_FIFO_HALF_EMPTY_Pos                  ( 6U )
#define OSPI_STATUS_TX_FIFO_HALF_EMPTY_Msk                  ( 0x1UL << OSPI_STATUS_TX_FIFO_HALF_EMPTY_Pos )
#define OSPI_STATUS_TX_FIFO_HALF_EMPTY                      ( OSPI_STATUS_TX_FIFO_HALF_EMPTY_Msk )

#define OSPI_STATUS_RX_FIFO_FULL_Pos                        ( 5U )
#define OSPI_STATUS_RX_FIFO_FULL_Msk                        ( 0x1UL << OSPI_STATUS_RX_FIFO_FULL_Pos )
#define OSPI_STATUS_RX_FIFO_FULL                            ( OSPI_STATUS_RX_FIFO_FULL_Msk )

#define OSPI_STATUS_RX_FIFO_EMPTY_Pos                       ( 4U )
#define OSPI_STATUS_RX_FIFO_EMPTY_Msk                       ( 0x1UL << OSPI_STATUS_RX_FIFO_EMPTY_Pos )
#define OSPI_STATUS_RX_FIFO_EMPTY                           ( OSPI_STATUS_RX_FIFO_EMPTY_Msk )

#define OSPI_STATUS_TX_FIFO_FULL_Pos                        ( 3U )
#define OSPI_STATUS_TX_FIFO_FULL_Msk                        ( 0x1UL << OSPI_STATUS_TX_FIFO_FULL_Pos )
#define OSPI_STATUS_TX_FIFO_FULL                            ( OSPI_STATUS_TX_FIFO_FULL_Msk )

#define OSPI_STATUS_TX_FIFO_EMPTY_Pos                       ( 2U )
#define OSPI_STATUS_TX_FIFO_EMPTY_Msk                       ( 0x1UL << OSPI_STATUS_TX_FIFO_EMPTY_Pos )
#define OSPI_STATUS_TX_FIFO_EMPTY                           ( OSPI_STATUS_TX_FIFO_EMPTY_Msk )

#define OSPI_STATUS_BATCH_DONE_Pos                          ( 1U )
#define OSPI_STATUS_BATCH_DONE_Msk                          ( 0x1UL << OSPI_STATUS_BATCH_DONE_Pos )
#define OSPI_STATUS_BATCH_DONE                              ( OSPI_STATUS_BATCH_DONE_Msk )

#define OSPI_STATUS_TX_BUSY_Pos                             ( 0U )
#define OSPI_STATUS_TX_BUSY_Msk                             ( 0x1UL << OSPI_STATUS_TX_BUSY_Pos )
#define OSPI_STATUS_TX_BUSY                                 ( OSPI_STATUS_TX_BUSY_Msk )


/***************  Bits definition for OSPI_TXDelay  **********************/

#define OSPI_TXDELAY_TDY_Pos                                ( 0U )
#define OSPI_TXDELAY_TDY_Msk                                ( 0xffffffffUL << OSPI_TXDELAY_TDY_Pos )
#define OSPI_TXDELAY_TDY                                    ( OSPI_TXDELAY_TDY_Msk )


/***************  Bits definition for OSPI_BATCH  **********************/

#define OSPI_BATCH_BATCH_NUMBER_Pos                         ( 0U )
#define OSPI_BATCH_BATCH_NUMBER_Msk                         ( 0xffffffffUL << OSPI_BATCH_BATCH_NUMBER_Pos )
#define OSPI_BATCH_BATCH_NUMBER                             ( OSPI_BATCH_BATCH_NUMBER_Msk )


/***************  Bits definition for OSPI_CS  **********************/

#define OSPI_CS_CSMAP_EN_Pos                                ( 3U )
#define OSPI_CS_CSMAP_EN_Msk                                ( 0x1UL << OSPI_CS_CSMAP_EN_Pos )
#define OSPI_CS_CSMAP_EN                                    ( OSPI_CS_CSMAP_EN_Msk )

#define OSPI_CS_CS_Pos                                      ( 0U )
#define OSPI_CS_CS_Msk                                      ( 0x7UL << OSPI_CS_CS_Pos )
#define OSPI_CS_CS                                          ( OSPI_CS_CS_Msk )
#define OSPI_CS_CS_0                                        ( 0x1UL << OSPI_CS_CS_Pos )
#define OSPI_CS_CS_1                                        ( 0x2UL << OSPI_CS_CS_Pos )
#define OSPI_CS_CS_2                                        ( 0x4UL << OSPI_CS_CS_Pos )


/***************  Bits definition for OSPI_OUT_EN  **********************/

#define OSPI_OUT_EN_IO7_EN_Pos                              ( 7U )
#define OSPI_OUT_EN_IO7_EN_Msk                              ( 0x1UL << OSPI_OUT_EN_IO7_EN_Pos )
#define OSPI_OUT_EN_IO7_EN                                  ( OSPI_OUT_EN_IO7_EN_Msk )

#define OSPI_OUT_EN_IO6_EN_Pos                              ( 6U )
#define OSPI_OUT_EN_IO6_EN_Msk                              ( 0x1UL << OSPI_OUT_EN_IO6_EN_Pos )
#define OSPI_OUT_EN_IO6_EN                                  ( OSPI_OUT_EN_IO6_EN_Msk )

#define OSPI_OUT_EN_IO5_EN_Pos                              ( 5U )
#define OSPI_OUT_EN_IO5_EN_Msk                              ( 0x1UL << OSPI_OUT_EN_IO5_EN_Pos )
#define OSPI_OUT_EN_IO5_EN                                  ( OSPI_OUT_EN_IO5_EN_Msk )

#define OSPI_OUT_EN_IO4_EN_Pos                              ( 4U )
#define OSPI_OUT_EN_IO4_EN_Msk                              ( 0x1UL << OSPI_OUT_EN_IO4_EN_Pos )
#define OSPI_OUT_EN_IO4_EN                                  ( OSPI_OUT_EN_IO4_EN_Msk )

#define OSPI_OUT_EN_HOLD_EN_Pos                             ( 3U )
#define OSPI_OUT_EN_HOLD_EN_Msk                             ( 0x1UL << OSPI_OUT_EN_HOLD_EN_Pos )
#define OSPI_OUT_EN_HOLD_EN                                 ( OSPI_OUT_EN_HOLD_EN_Msk )

#define OSPI_OUT_EN_WP_EN_Pos                               ( 2U )
#define OSPI_OUT_EN_WP_EN_Msk                               ( 0x1UL << OSPI_OUT_EN_WP_EN_Pos )
#define OSPI_OUT_EN_WP_EN                                   ( OSPI_OUT_EN_WP_EN_Msk )

#define OSPI_OUT_EN_MISO_EN_Pos                             ( 1U )
#define OSPI_OUT_EN_MISO_EN_Msk                             ( 0x1UL << OSPI_OUT_EN_MISO_EN_Pos )
#define OSPI_OUT_EN_MISO_EN                                 ( OSPI_OUT_EN_MISO_EN_Msk )

#define OSPI_OUT_EN_MOSI_EN_Pos                             ( 0U )
#define OSPI_OUT_EN_MOSI_EN_Msk                             ( 0x1UL << OSPI_OUT_EN_MOSI_EN_Pos )
#define OSPI_OUT_EN_MOSI_EN                                 ( OSPI_OUT_EN_MOSI_EN_Msk )


/***************  Bits definition for OSPI_MEMO_ACC1  **********************/


#define OSPI_MEMO_ACC1_HYPER_BT_Pos                         ( 27U )
#define OSPI_MEMO_ACC1_HYPER_BT_Msk                         ( 0x1UL << OSPI_MEMO_ACC1_HYPER_BT_Pos )
#define OSPI_MEMO_ACC1_HYPER_BT                             ( OSPI_MEMO_ACC1_HYPER_BT_Msk )

#define OSPI_MEMO_ACC1_DATA_MODE_Pos                        ( 25U )
#define OSPI_MEMO_ACC1_DATA_MODE_Msk                        ( 0x3UL << OSPI_MEMO_ACC1_DATA_MODE_Pos )
#define OSPI_MEMO_ACC1_DATA_MODE                            ( OSPI_MEMO_ACC1_DATA_MODE_Msk )
#define OSPI_MEMO_ACC1_DATA_MODE_0                          ( 0x1UL << OSPI_MEMO_ACC1_DATA_MODE_Pos )
#define OSPI_MEMO_ACC1_DATA_MODE_1                          ( 0x2UL << OSPI_MEMO_ACC1_DATA_MODE_Pos )

#define OSPI_MEMO_ACC1_ALTER_BYTE_MODE_Pos                  ( 23U )
#define OSPI_MEMO_ACC1_ALTER_BYTE_MODE_Msk                  ( 0x3UL << OSPI_MEMO_ACC1_ALTER_BYTE_MODE_Pos )
#define OSPI_MEMO_ACC1_ALTER_BYTE_MODE                      ( OSPI_MEMO_ACC1_ALTER_BYTE_MODE_Msk )
#define OSPI_MEMO_ACC1_ALTER_BYTE_MODE_0                    ( 0x1UL << OSPI_MEMO_ACC1_ALTER_BYTE_MODE_Pos )
#define OSPI_MEMO_ACC1_ALTER_BYTE_MODE_1                    ( 0x2UL << OSPI_MEMO_ACC1_ALTER_BYTE_MODE_Pos )

#define OSPI_MEMO_ACC1_ADDR_MODE_Pos                        ( 21U )
#define OSPI_MEMO_ACC1_ADDR_MODE_Msk                        ( 0x3UL << OSPI_MEMO_ACC1_ADDR_MODE_Pos )
#define OSPI_MEMO_ACC1_ADDR_MODE                            ( OSPI_MEMO_ACC1_ADDR_MODE_Msk )
#define OSPI_MEMO_ACC1_ADDR_MODE_0                          ( 0x1UL << OSPI_MEMO_ACC1_ADDR_MODE_Pos )
#define OSPI_MEMO_ACC1_ADDR_MODE_1                          ( 0x2UL << OSPI_MEMO_ACC1_ADDR_MODE_Pos )

#define OSPI_MEMO_ACC1_INSTR_MODE_Pos                       ( 19U )
#define OSPI_MEMO_ACC1_INSTR_MODE_Msk                       ( 0x3UL << OSPI_MEMO_ACC1_INSTR_MODE_Pos )
#define OSPI_MEMO_ACC1_INSTR_MODE                           ( OSPI_MEMO_ACC1_INSTR_MODE_Msk )
#define OSPI_MEMO_ACC1_INSTR_MODE_0                         ( 0x1UL << OSPI_MEMO_ACC1_INSTR_MODE_Pos )
#define OSPI_MEMO_ACC1_INSTR_MODE_1                         ( 0x2UL << OSPI_MEMO_ACC1_INSTR_MODE_Pos )

#define OSPI_MEMO_ACC1_ADDR_WIDTH_Pos                       ( 17U )
#define OSPI_MEMO_ACC1_ADDR_WIDTH_Msk                       ( 0x3UL << OSPI_MEMO_ACC1_ADDR_WIDTH_Pos )
#define OSPI_MEMO_ACC1_ADDR_WIDTH                           ( OSPI_MEMO_ACC1_ADDR_WIDTH_Msk )
#define OSPI_MEMO_ACC1_ADDR_WIDTH_0                         ( 0x1UL << OSPI_MEMO_ACC1_ADDR_WIDTH_Pos )
#define OSPI_MEMO_ACC1_ADDR_WIDTH_1                         ( 0x2UL << OSPI_MEMO_ACC1_ADDR_WIDTH_Pos )

#define OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_Pos                 ( 12U )
#define OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_Msk                 ( 0x1fUL << OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_Pos )
#define OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE                     ( OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_Msk )
#define OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_0                   ( 0x1UL << OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_Pos )
#define OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_1                   ( 0x2UL << OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_Pos )
#define OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_2                   ( 0x4UL << OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_Pos )
#define OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_3                   ( 0x8UL << OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_Pos )
#define OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_4                   ( 0x10UL << OSPI_MEMO_ACC1_DUMMY_CYCLE_SIZE_Pos )

#define OSPI_MEMO_ACC1_RD_DB_EN_Pos                         ( 11U )
#define OSPI_MEMO_ACC1_RD_DB_EN_Msk                         ( 0x1UL << OSPI_MEMO_ACC1_RD_DB_EN_Pos )
#define OSPI_MEMO_ACC1_RD_DB_EN                             ( OSPI_MEMO_ACC1_RD_DB_EN_Msk )

#define OSPI_MEMO_ACC1_WR_DB_EN_Pos                         ( 10U )
#define OSPI_MEMO_ACC1_WR_DB_EN_Msk                         ( 0x1UL << OSPI_MEMO_ACC1_WR_DB_EN_Pos )
#define OSPI_MEMO_ACC1_WR_DB_EN                             ( OSPI_MEMO_ACC1_WR_DB_EN_Msk )

#define OSPI_MEMO_ACC1_ALTER_BYTE_SIZE_Pos                  ( 7U )
#define OSPI_MEMO_ACC1_ALTER_BYTE_SIZE_Msk                  ( 0x3UL << OSPI_MEMO_ACC1_ALTER_BYTE_SIZE_Pos )
#define OSPI_MEMO_ACC1_ALTER_BYTE_SIZE                      ( OSPI_MEMO_ACC1_ALTER_BYTE_SIZE_Msk )
#define OSPI_MEMO_ACC1_ALTER_BYTE_SIZE_0                    ( 0x1UL << OSPI_MEMO_ACC1_ALTER_BYTE_SIZE_Pos )
#define OSPI_MEMO_ACC1_ALTER_BYTE_SIZE_1                    ( 0x2UL << OSPI_MEMO_ACC1_ALTER_BYTE_SIZE_Pos )

#define OSPI_MEMO_ACC1_RD_AB_EN_Pos                         ( 6U )
#define OSPI_MEMO_ACC1_RD_AB_EN_Msk                         ( 0x1UL << OSPI_MEMO_ACC1_RD_AB_EN_Pos )
#define OSPI_MEMO_ACC1_RD_AB_EN                             ( OSPI_MEMO_ACC1_RD_AB_EN_Msk )

#define OSPI_MEMO_ACC1_WR_AB_EN_Pos                         ( 5U )
#define OSPI_MEMO_ACC1_WR_AB_EN_Msk                         ( 0x1UL << OSPI_MEMO_ACC1_WR_AB_EN_Pos )
#define OSPI_MEMO_ACC1_WR_AB_EN                             ( OSPI_MEMO_ACC1_WR_AB_EN_Msk )

#define OSPI_MEMO_ACC1_SEND_INSTR_ONCE_EN_Pos               ( 4U )
#define OSPI_MEMO_ACC1_SEND_INSTR_ONCE_EN_CMD_Msk           ( 0x1UL << OSPI_MEMO_ACC1_SEND_INSTR_ONCE_EN_Pos )
#define OSPI_MEMO_ACC1_SEND_INSTR_ONCE_EN                   ( OSPI_MEMO_ACC1_SEND_INSTR_ONCE_EN_CMD_Msk )

#define OSPI_MEMO_ACC1_CON_MODE_EN_Pos                      ( 3U )
#define OSPI_MEMO_ACC1_CON_MODE_EN_Msk                      ( 0x1UL << OSPI_MEMO_ACC1_CON_MODE_EN_Pos )
#define OSPI_MEMO_ACC1_CON_MODE_EN                          ( OSPI_MEMO_ACC1_CON_MODE_EN_Msk )

#define OSPI_MEMO_ACC1_CS_TIMEOUT_EN_Pos                    ( 1U )
#define OSPI_MEMO_ACC1_CS_TIMEOUT_EN_Msk                    ( 0x1UL << OSPI_MEMO_ACC1_CS_TIMEOUT_EN_Pos )
#define OSPI_MEMO_ACC1_CS_TIMEOUT_EN                        ( OSPI_MEMO_ACC1_CS_TIMEOUT_EN_Msk )

#define OSPI_MEMO_ACC1_ACC_EN_Pos                           ( 0U )
#define OSPI_MEMO_ACC1_ACC_EN_Msk                           ( 0x1UL << OSPI_MEMO_ACC1_ACC_EN_Pos )
#define OSPI_MEMO_ACC1_ACC_EN                               ( OSPI_MEMO_ACC1_ACC_EN_Msk )


/***************  Bits definition for OSPI_CMD  **********************/

#define OSPI_CMD_WR_CMD_Pos                                 ( 8U )
#define OSPI_CMD_WR_CMD_Msk                                 ( 0xffUL << OSPI_CMD_WR_CMD_Pos )
#define OSPI_CMD_WR_CMD                                     ( OSPI_CMD_WR_CMD_Msk )
#define OSPI_CMD_WR_CMD_0                                   ( 0x1UL << OSPI_CMD_WR_CMD_Pos )
#define OSPI_CMD_WR_CMD_1                                   ( 0x2UL << OSPI_CMD_WR_CMD_Pos )
#define OSPI_CMD_WR_CMD_2                                   ( 0x4UL << OSPI_CMD_WR_CMD_Pos )
#define OSPI_CMD_WR_CMD_3                                   ( 0x8UL << OSPI_CMD_WR_CMD_Pos )
#define OSPI_CMD_WR_CMD_4                                   ( 0x10UL << OSPI_CMD_WR_CMD_Pos )
#define OSPI_CMD_WR_CMD_5                                   ( 0x20UL << OSPI_CMD_WR_CMD_Pos )
#define OSPI_CMD_WR_CMD_6                                   ( 0x40UL << OSPI_CMD_WR_CMD_Pos )
#define OSPI_CMD_WR_CMD_7                                   ( 0x80UL << OSPI_CMD_WR_CMD_Pos )

#define OSPI_CMD_RD_CMD_Pos                                 ( 0U )
#define OSPI_CMD_RD_CMD_Msk                                 ( 0xffUL << OSPI_CMD_RD_CMD_Pos )
#define OSPI_CMD_RD_CMD                                     ( OSPI_CMD_RD_CMD_Msk )
#define OSPI_CMD_RD_CMD_0                                   ( 0x1UL << OSPI_CMD_RD_CMD_Pos )
#define OSPI_CMD_RD_CMD_1                                   ( 0x2UL << OSPI_CMD_RD_CMD_Pos )
#define OSPI_CMD_RD_CMD_2                                   ( 0x4UL << OSPI_CMD_RD_CMD_Pos )
#define OSPI_CMD_RD_CMD_3                                   ( 0x8UL << OSPI_CMD_RD_CMD_Pos )
#define OSPI_CMD_RD_CMD_4                                   ( 0x10UL << OSPI_CMD_RD_CMD_Pos )
#define OSPI_CMD_RD_CMD_5                                   ( 0x20UL << OSPI_CMD_RD_CMD_Pos )
#define OSPI_CMD_RD_CMD_6                                   ( 0x40UL << OSPI_CMD_RD_CMD_Pos )
#define OSPI_CMD_RD_CMD_7                                   ( 0x80UL << OSPI_CMD_RD_CMD_Pos )


/***************  Bits definition for OSPI_ALTER_BYTE  **********************/

#define OSPI_ALTER_BYTE_Pos                                 ( 0U )
#define OSPI_ALTER_BYTE_Msk                                 ( 0xffffffffUL << OSPI_ALTER_BYTE_Pos )
#define OSPI_ALTER_BYTE                                     ( OSPI_ALTER_BYTE_Msk )


/***************  Bits definition for OSPI_CS_TOUT_VAL  **********************/

#define OSPI_CS_TIMEOUT_VAL_Pos                             ( 0U )
#define OSPI_CS_TIMEOUT_VAL_Msk                             ( 0xffffUL << OSPI_CS_TIMEOUT_VAL_Pos )
#define OSPI_CS_TIMEOUT_VAL                                 ( OSPI_CS_TIMEOUT_VAL_Msk )


/***************  Bits definition for OSPI_MEMO_ACC2  **********************/

#define OSPI_MEMO_ACC2_WRPS_Pos                             ( 12U )
#define OSPI_MEMO_ACC2_WRPS_Msk                             ( 0xfUL << OSPI_MEMO_ACC2_WRPS_Pos )
#define OSPI_MEMO_ACC2_WRPS                                 ( OSPI_MEMO_ACC2_WRPS_Msk )
#define OSPI_MEMO_ACC2_WRPS_0                               ( 0x1UL << OSPI_MEMO_ACC2_WRPS_Pos )
#define OSPI_MEMO_ACC2_WRPS_1                               ( 0x2UL << OSPI_MEMO_ACC2_WRPS_Pos )
#define OSPI_MEMO_ACC2_WRPS_2                               ( 0x4UL << OSPI_MEMO_ACC2_WRPS_Pos )

#define OSPI_MEMO_ACC2_BL_Pos                               ( 8U )
#define OSPI_MEMO_ACC2_BL_Msk                               ( 0xfUL << OSPI_MEMO_ACC2_BL_Pos )
#define OSPI_MEMO_ACC2_BL                                   ( OSPI_MEMO_ACC2_BL_Msk )
#define OSPI_MEMO_ACC2_BL_0                                 ( 0x1UL << OSPI_MEMO_ACC2_BL_Pos )
#define OSPI_MEMO_ACC2_BL_1                                 ( 0x2UL << OSPI_MEMO_ACC2_BL_Pos )
#define OSPI_MEMO_ACC2_BL_2                                 ( 0x4UL << OSPI_MEMO_ACC2_BL_Pos )

#define OSPI_MEMO_ACC2_HXLC1_Pos                            ( 4U )
#define OSPI_MEMO_ACC2_HXLC1_Msk                            ( 0xfUL << OSPI_MEMO_ACC2_HXLC1_Pos )
#define OSPI_MEMO_ACC2_HXLC1                                ( OSPI_MEMO_ACC2_HXLC1_Msk )
#define OSPI_MEMO_ACC2_HXLC1_0                              ( 0x1UL << OSPI_MEMO_ACC2_HXLC1_Pos )
#define OSPI_MEMO_ACC2_HXLC1_1                              ( 0x2UL << OSPI_MEMO_ACC2_HXLC1_Pos )
#define OSPI_MEMO_ACC2_HXLC1_2                              ( 0x4UL << OSPI_MEMO_ACC2_HXLC1_Pos )
#define OSPI_MEMO_ACC2_HXLC1_3                              ( 0x8UL << OSPI_MEMO_ACC2_HXLC1_Pos )

#define OSPI_MEMO_ACC2_HXLC0_Pos                            ( 0U )
#define OSPI_MEMO_ACC2_HXLC0_Msk                            ( 0xfUL << OSPI_MEMO_ACC2_HXLC0_Pos )
#define OSPI_MEMO_ACC2_HXLC0                                ( OSPI_MEMO_ACC2_HXLC0_Msk )
#define OSPI_MEMO_ACC2_HXLC0_0                              ( 0x1UL << OSPI_MEMO_ACC2_HXLC0_Pos )
#define OSPI_MEMO_ACC2_HXLC0_1                              ( 0x2UL << OSPI_MEMO_ACC2_HXLC0_Pos )
#define OSPI_MEMO_ACC2_HXLC0_2                              ( 0x4UL << OSPI_MEMO_ACC2_HXLC0_Pos )
#define OSPI_MEMO_ACC2_HXLC0_3                              ( 0x8UL << OSPI_MEMO_ACC2_HXLC0_Pos )




/***************  Bits definition for FMC_SNCTLx  **********************/

#define FMC_SNCTLX_SYNCWR_Pos                               ( 19U )
#define FMC_SNCTLX_SYNCWR_Msk                               ( 0x1UL << FMC_SNCTLX_SYNCWR_Pos )
#define FMC_SNCTLX_SYNCWR                                   ( FMC_SNCTLX_SYNCWR_Msk )

#define FMC_SNCTLX_CPS_Pos                                  ( 16U )
#define FMC_SNCTLX_CPS_Msk                                  ( 0x7UL << FMC_SNCTLX_CPS_Pos )
#define FMC_SNCTLX_CPS                                      ( FMC_SNCTLX_CPS_Msk )
#define FMC_SNCTLX_CPS_0                                    ( 0x1UL << FMC_SNCTLX_CPS_Pos )
#define FMC_SNCTLX_CPS_1                                    ( 0x2UL << FMC_SNCTLX_CPS_Pos )
#define FMC_SNCTLX_CPS_2                                    ( 0x4UL << FMC_SNCTLX_CPS_Pos )

#define FMC_SNCTLX_ASYNCWAIT_Pos                            ( 15U )
#define FMC_SNCTLX_ASYNCWAIT_Msk                            ( 0x1UL << FMC_SNCTLX_ASYNCWAIT_Pos )
#define FMC_SNCTLX_ASYNCWAIT                                ( FMC_SNCTLX_ASYNCWAIT_Msk )

#define FMC_SNCTLX_EXMODEN_Pos                              ( 14U )
#define FMC_SNCTLX_EXMODEN_Msk                              ( 0x1UL << FMC_SNCTLX_EXMODEN_Pos )
#define FMC_SNCTLX_EXMODEN                                  ( FMC_SNCTLX_EXMODEN_Msk )

#define FMC_SNCTLX_NRWTEN_Pos                               ( 13U )
#define FMC_SNCTLX_NRWTEN_Msk                               ( 0x1UL << FMC_SNCTLX_NRWTEN_Pos )
#define FMC_SNCTLX_NRWTEN                                   ( FMC_SNCTLX_NRWTEN_Msk )

#define FMC_SNCTLX_WREN_Pos                                 ( 12U )
#define FMC_SNCTLX_WREN_Msk                                 ( 0x1UL << FMC_SNCTLX_WREN_Pos )
#define FMC_SNCTLX_WREN                                     ( FMC_SNCTLX_WREN_Msk )

#define FMC_SNCTLX_NRWTCFG_Pos                              ( 11U )
#define FMC_SNCTLX_NRWTCFG_Msk                              ( 0x1UL << FMC_SNCTLX_NRWTCFG_Pos )
#define FMC_SNCTLX_NRWTCFG                                  ( FMC_SNCTLX_NRWTCFG_Msk )

#define FMC_SNCTLX_WRAPEN_Pos                               ( 10U )
#define FMC_SNCTLX_WRAPEN_Msk                               ( 0x1UL << FMC_SNCTLX_WRAPEN_Pos )
#define FMC_SNCTLX_WRAPEN                                   ( FMC_SNCTLX_WRAPEN_Msk )

#define FMC_SNCTLX_NRWTPOL_Pos                              ( 9U )
#define FMC_SNCTLX_NRWTPOL_Msk                              ( 0x1UL << FMC_SNCTLX_NRWTPOL_Pos )
#define FMC_SNCTLX_NRWTPOL                                  ( FMC_SNCTLX_NRWTPOL_Msk )

#define FMC_SNCTLX_SBRSTEN_Pos                              ( 8U )
#define FMC_SNCTLX_SBRSTEN_Msk                              ( 0x1UL << FMC_SNCTLX_SBRSTEN_Pos )
#define FMC_SNCTLX_SBRSTEN                                  ( FMC_SNCTLX_SBRSTEN_Msk )

#define FMC_SNCTLX_NREN_Pos                                 ( 6U )
#define FMC_SNCTLX_NREN_Msk                                 ( 0x1UL << FMC_SNCTLX_NREN_Pos )
#define FMC_SNCTLX_NREN                                     ( FMC_SNCTLX_NREN_Msk )

#define FMC_SNCTLX_NRW_Pos                                  ( 4U )
#define FMC_SNCTLX_NRW_Msk                                  ( 0x3UL << FMC_SNCTLX_NRW_Pos )
#define FMC_SNCTLX_NRW                                      ( FMC_SNCTLX_NRW_Msk )
#define FMC_SNCTLX_NRW_0                                    ( 0x1UL << FMC_SNCTLX_NRW_Pos )
#define FMC_SNCTLX_NRW_1                                    ( 0x2UL << FMC_SNCTLX_NRW_Pos )

#define FMC_SNCTLX_NRTP_Pos                                 ( 2U )
#define FMC_SNCTLX_NRTP_Msk                                 ( 0x3UL << FMC_SNCTLX_NRTP_Pos )
#define FMC_SNCTLX_NRTP                                     ( FMC_SNCTLX_NRTP_Msk )
#define FMC_SNCTLX_NRTP_0                                   ( 0x1UL << FMC_SNCTLX_NRTP_Pos )
#define FMC_SNCTLX_NRTP_1                                   ( 0x2UL << FMC_SNCTLX_NRTP_Pos )

#define FMC_SNCTLX_NRMUX_Pos                                ( 1U )
#define FMC_SNCTLX_NRMUX_Msk                                ( 0x1UL << FMC_SNCTLX_NRMUX_Pos )
#define FMC_SNCTLX_NRMUX                                    ( FMC_SNCTLX_NRMUX_Msk )

#define FMC_SNCTLX_NRBKEN_Pos                               ( 0U )
#define FMC_SNCTLX_NRBKEN_Msk                               ( 0x1UL << FMC_SNCTLX_NRBKEN_Pos )
#define FMC_SNCTLX_NRBKEN                                   ( FMC_SNCTLX_NRBKEN_Msk )


/***************  Bits definition for FMC_SNTCFGx  **********************/

#define FMC_SNTCFGX_ASYNCMOD_Pos                            ( 28U )
#define FMC_SNTCFGX_ASYNCMOD_Msk                            ( 0x3UL << FMC_SNTCFGX_ASYNCMOD_Pos )
#define FMC_SNTCFGX_ASYNCMOD                                ( FMC_SNTCFGX_ASYNCMOD_Msk )
#define FMC_SNTCFGX_ASYNCMOD_0                              ( 0x1UL << FMC_SNTCFGX_ASYNCMOD_Pos )
#define FMC_SNTCFGX_ASYNCMOD_1                              ( 0x2UL << FMC_SNTCFGX_ASYNCMOD_Pos )

#define FMC_SNTCFGX_DLAT_Pos                                ( 24U )
#define FMC_SNTCFGX_DLAT_Msk                                ( 0xfUL << FMC_SNTCFGX_DLAT_Pos )
#define FMC_SNTCFGX_DLAT                                    ( FMC_SNTCFGX_DLAT_Msk )
#define FMC_SNTCFGX_DLAT_0                                  ( 0x1UL << FMC_SNTCFGX_DLAT_Pos )
#define FMC_SNTCFGX_DLAT_1                                  ( 0x2UL << FMC_SNTCFGX_DLAT_Pos )
#define FMC_SNTCFGX_DLAT_2                                  ( 0x4UL << FMC_SNTCFGX_DLAT_Pos )
#define FMC_SNTCFGX_DLAT_3                                  ( 0x8UL << FMC_SNTCFGX_DLAT_Pos )

#define FMC_SNTCFGX_CKDIV_Pos                               ( 20U )
#define FMC_SNTCFGX_CKDIV_Msk                               ( 0xfUL << FMC_SNTCFGX_CKDIV_Pos )
#define FMC_SNTCFGX_CKDIV                                   ( FMC_SNTCFGX_CKDIV_Msk )
#define FMC_SNTCFGX_CKDIV_0                                 ( 0x1UL << FMC_SNTCFGX_CKDIV_Pos )
#define FMC_SNTCFGX_CKDIV_1                                 ( 0x2UL << FMC_SNTCFGX_CKDIV_Pos )
#define FMC_SNTCFGX_CKDIV_2                                 ( 0x4UL << FMC_SNTCFGX_CKDIV_Pos )
#define FMC_SNTCFGX_CKDIV_3                                 ( 0x8UL << FMC_SNTCFGX_CKDIV_Pos )

#define FMC_SNTCFGX_BUSLAT_Pos                              ( 16U )
#define FMC_SNTCFGX_BUSLAT_Msk                              ( 0xfUL << FMC_SNTCFGX_BUSLAT_Pos )
#define FMC_SNTCFGX_BUSLAT                                  ( FMC_SNTCFGX_BUSLAT_Msk )
#define FMC_SNTCFGX_BUSLAT_0                                ( 0x1UL << FMC_SNTCFGX_BUSLAT_Pos )
#define FMC_SNTCFGX_BUSLAT_1                                ( 0x2UL << FMC_SNTCFGX_BUSLAT_Pos )
#define FMC_SNTCFGX_BUSLAT_2                                ( 0x4UL << FMC_SNTCFGX_BUSLAT_Pos )
#define FMC_SNTCFGX_BUSLAT_3                                ( 0x8UL << FMC_SNTCFGX_BUSLAT_Pos )

#define FMC_SNTCFGX_DSET_Pos                                ( 8U )
#define FMC_SNTCFGX_DSET_Msk                                ( 0xffUL << FMC_SNTCFGX_DSET_Pos )
#define FMC_SNTCFGX_DSET                                    ( FMC_SNTCFGX_DSET_Msk )
#define FMC_SNTCFGX_DSET_0                                  ( 0x1UL << FMC_SNTCFGX_DSET_Pos )
#define FMC_SNTCFGX_DSET_1                                  ( 0x2UL << FMC_SNTCFGX_DSET_Pos )
#define FMC_SNTCFGX_DSET_2                                  ( 0x4UL << FMC_SNTCFGX_DSET_Pos )
#define FMC_SNTCFGX_DSET_3                                  ( 0x8UL << FMC_SNTCFGX_DSET_Pos )
#define FMC_SNTCFGX_DSET_4                                  ( 0x10UL << FMC_SNTCFGX_DSET_Pos )
#define FMC_SNTCFGX_DSET_5                                  ( 0x20UL << FMC_SNTCFGX_DSET_Pos )
#define FMC_SNTCFGX_DSET_6                                  ( 0x40UL << FMC_SNTCFGX_DSET_Pos )
#define FMC_SNTCFGX_DSET_7                                  ( 0x80UL << FMC_SNTCFGX_DSET_Pos )

#define FMC_SNTCFGX_AHLD_Pos                                ( 4U )
#define FMC_SNTCFGX_AHLD_Msk                                ( 0xfUL << FMC_SNTCFGX_AHLD_Pos )
#define FMC_SNTCFGX_AHLD                                    ( FMC_SNTCFGX_AHLD_Msk )
#define FMC_SNTCFGX_AHLD_0                                  ( 0x1UL << FMC_SNTCFGX_AHLD_Pos )
#define FMC_SNTCFGX_AHLD_1                                  ( 0x2UL << FMC_SNTCFGX_AHLD_Pos )
#define FMC_SNTCFGX_AHLD_2                                  ( 0x4UL << FMC_SNTCFGX_AHLD_Pos )
#define FMC_SNTCFGX_AHLD_3                                  ( 0x8UL << FMC_SNTCFGX_AHLD_Pos )

#define FMC_SNTCFGX_ASET_Pos                                ( 0U )
#define FMC_SNTCFGX_ASET_Msk                                ( 0xfUL << FMC_SNTCFGX_ASET_Pos )
#define FMC_SNTCFGX_ASET                                    ( FMC_SNTCFGX_ASET_Msk )
#define FMC_SNTCFGX_ASET_0                                  ( 0x1UL << FMC_SNTCFGX_ASET_Pos )
#define FMC_SNTCFGX_ASET_1                                  ( 0x2UL << FMC_SNTCFGX_ASET_Pos )
#define FMC_SNTCFGX_ASET_2                                  ( 0x4UL << FMC_SNTCFGX_ASET_Pos )
#define FMC_SNTCFGX_ASET_3                                  ( 0x8UL << FMC_SNTCFGX_ASET_Pos )


/***************  Bits definition for FMC_SNWTCFGx  **********************/

#define FMC_SNWTCFGX_WASYNCMOD_Pos                          ( 28U )
#define FMC_SNWTCFGX_WASYNCMOD_Msk                          ( 0x3UL << FMC_SNWTCFGX_WASYNCMOD_Pos )
#define FMC_SNWTCFGX_WASYNCMOD                              ( FMC_SNWTCFGX_WASYNCMOD_Msk )
#define FMC_SNWTCFGX_WASYNCMOD_0                            ( 0x1UL << FMC_SNWTCFGX_WASYNCMOD_Pos )
#define FMC_SNWTCFGX_WASYNCMOD_1                            ( 0x2UL << FMC_SNWTCFGX_WASYNCMOD_Pos )

#define FMC_SNWTCFGX_DLAT_Pos                               ( 24U )
#define FMC_SNWTCFGX_DLAT_Msk                               ( 0xfUL << FMC_SNWTCFGX_DLAT_Pos )
#define FMC_SNWTCFGX_DLAT                                   ( FMC_SNWTCFGX_DLAT_Msk )
#define FMC_SNWTCFGX_DLAT_0                                 ( 0x1UL << FMC_SNWTCFGX_DLAT_Pos )
#define FMC_SNWTCFGX_DLAT_1                                 ( 0x2UL << FMC_SNWTCFGX_DLAT_Pos )
#define FMC_SNWTCFGX_DLAT_2                                 ( 0x4UL << FMC_SNWTCFGX_DLAT_Pos )
#define FMC_SNWTCFGX_DLAT_3                                 ( 0x8UL << FMC_SNWTCFGX_DLAT_Pos )

#define FMC_SNWTCFGX_WBUSLAT_Pos                            ( 16U )
#define FMC_SNWTCFGX_WBUSLAT_Msk                            ( 0xfUL << FMC_SNWTCFGX_WBUSLAT_Pos )
#define FMC_SNWTCFGX_WBUSLAT                                ( FMC_SNWTCFGX_WBUSLAT_Msk )
#define FMC_SNWTCFGX_WBUSLAT_0                              ( 0x1UL << FMC_SNWTCFGX_WBUSLAT_Pos )
#define FMC_SNWTCFGX_WBUSLAT_1                              ( 0x2UL << FMC_SNWTCFGX_WBUSLAT_Pos )
#define FMC_SNWTCFGX_WBUSLAT_2                              ( 0x4UL << FMC_SNWTCFGX_WBUSLAT_Pos )
#define FMC_SNWTCFGX_WBUSLAT_3                              ( 0x8UL << FMC_SNWTCFGX_WBUSLAT_Pos )

#define FMC_SNWTCFGX_WDSET_Pos                              ( 8U )
#define FMC_SNWTCFGX_WDSET_Msk                              ( 0xffUL << FMC_SNWTCFGX_WDSET_Pos )
#define FMC_SNWTCFGX_WDSET                                  ( FMC_SNWTCFGX_WDSET_Msk )
#define FMC_SNWTCFGX_WDSET_0                                ( 0x1UL << FMC_SNWTCFGX_WDSET_Pos )
#define FMC_SNWTCFGX_WDSET_1                                ( 0x2UL << FMC_SNWTCFGX_WDSET_Pos )
#define FMC_SNWTCFGX_WDSET_2                                ( 0x4UL << FMC_SNWTCFGX_WDSET_Pos )
#define FMC_SNWTCFGX_WDSET_3                                ( 0x8UL << FMC_SNWTCFGX_WDSET_Pos )
#define FMC_SNWTCFGX_WDSET_4                                ( 0x10UL << FMC_SNWTCFGX_WDSET_Pos )
#define FMC_SNWTCFGX_WDSET_5                                ( 0x20UL << FMC_SNWTCFGX_WDSET_Pos )
#define FMC_SNWTCFGX_WDSET_6                                ( 0x40UL << FMC_SNWTCFGX_WDSET_Pos )
#define FMC_SNWTCFGX_WDSET_7                                ( 0x80UL << FMC_SNWTCFGX_WDSET_Pos )

#define FMC_SNWTCFGX_WAHLD_Pos                              ( 4U )
#define FMC_SNWTCFGX_WAHLD_Msk                              ( 0xfUL << FMC_SNWTCFGX_WAHLD_Pos )
#define FMC_SNWTCFGX_WAHLD                                  ( FMC_SNWTCFGX_WAHLD_Msk )
#define FMC_SNWTCFGX_WAHLD_0                                ( 0x1UL << FMC_SNWTCFGX_WAHLD_Pos )
#define FMC_SNWTCFGX_WAHLD_1                                ( 0x2UL << FMC_SNWTCFGX_WAHLD_Pos )
#define FMC_SNWTCFGX_WAHLD_2                                ( 0x4UL << FMC_SNWTCFGX_WAHLD_Pos )
#define FMC_SNWTCFGX_WAHLD_3                                ( 0x8UL << FMC_SNWTCFGX_WAHLD_Pos )

#define FMC_SNWTCFGX_WASET_Pos                              ( 0U )
#define FMC_SNWTCFGX_WASET_Msk                              ( 0xfUL << FMC_SNWTCFGX_WASET_Pos )
#define FMC_SNWTCFGX_WASET                                  ( FMC_SNWTCFGX_WASET_Msk )
#define FMC_SNWTCFGX_WASET_0                                ( 0x1UL << FMC_SNWTCFGX_WASET_Pos )
#define FMC_SNWTCFGX_WASET_1                                ( 0x2UL << FMC_SNWTCFGX_WASET_Pos )
#define FMC_SNWTCFGX_WASET_2                                ( 0x4UL << FMC_SNWTCFGX_WASET_Pos )
#define FMC_SNWTCFGX_WASET_3                                ( 0x8UL << FMC_SNWTCFGX_WASET_Pos )

/***************  Bits definition for FMC_SDRCR  **********************/

#define FMC_SDRCR_WBUSRLS_Pos                               ( 20U )
#define FMC_SDRCR_WBUSRLS_Msk                               ( 0x1UL << FMC_SDRCR_WBUSRLS_Pos )
#define FMC_SDRCR_WBUSRLS                                   ( FMC_SDRCR_WBUSRLS_Msk )

#define FMC_SDRCR_RBUSRLS_Pos                               ( 19U )
#define FMC_SDRCR_RBUSRLS_Msk                               ( 0x1UL << FMC_SDRCR_RBUSRLS_Pos )
#define FMC_SDRCR_RBUSRLS                                   ( FMC_SDRCR_RBUSRLS_Msk )

#define FMC_SDRCR_BDEPTH_Pos                                ( 16U )
#define FMC_SDRCR_BDEPTH_Msk                                ( 0x7UL << FMC_SDRCR_BDEPTH_Pos )
#define FMC_SDRCR_BDEPTH_0                                  ( 0x1UL << FMC_SDRCR_BDEPTH_Pos )
#define FMC_SDRCR_BDEPTH_1                                  ( 0x2UL << FMC_SDRCR_BDEPTH_Pos )
#define FMC_SDRCR_BDEPTH_2                                  ( 0x4UL << FMC_SDRCR_BDEPTH_Pos )

#define FMC_SDRCR_W2RDLY_Pos                                ( 15U )
#define FMC_SDRCR_W2RDLY_Msk                                ( 0x1UL << FMC_SDRCR_W2RDLY_Pos )
#define FMC_SDRCR_W2RDLY                                    ( FMC_SDRCR_W2RDLY_Msk )

#define FMC_SDRCR_RPIPE_Pos                                 ( 13U )
#define FMC_SDRCR_RPIPE_Msk                                 ( 0x3UL << FMC_SDRCR_RPIPE_Pos )
#define FMC_SDRCR_RPIPE                                     ( FMC_SDRCR_RPIPE_Msk )
#define FMC_SDRCR_RPIPE_0                                   ( 0x1UL << FMC_SDRCR_RPIPE_Pos )
#define FMC_SDRCR_RPIPE_1                                   ( 0x2UL << FMC_SDRCR_RPIPE_Pos )

#define FMC_SDRCR_RBURST_Pos                                ( 12U )
#define FMC_SDRCR_RBURST_Msk                                ( 0x1UL << FMC_SDRCR_RBURST_Pos )
#define FMC_SDRCR_RBURST                                    ( FMC_SDRCR_RBURST_Msk )

#define FMC_SDRCR_CLKDIV_Pos                                ( 10U )
#define FMC_SDRCR_CLKDIV_Msk                                ( 0x3UL << FMC_SDRCR_CLKDIV_Pos )
#define FMC_SDRCR_CLKDIV                                    ( FMC_SDRCR_CLKDIV_Msk )
#define FMC_SDRCR_CLKDIV_0                                  ( 0x1UL << FMC_SDRCR_CLKDIV_Pos )
#define FMC_SDRCR_CLKDIV_1                                  ( 0x2UL << FMC_SDRCR_CLKDIV_Pos )

#define FMC_SDRCR_WP_Pos                                    ( 9U )
#define FMC_SDRCR_WP_Msk                                    ( 0x1UL << FMC_SDRCR_WP_Pos )
#define FMC_SDRCR_WP                                        ( FMC_SDRCR_WP_Msk )

#define FMC_SDRCR_CAS_Pos                                   ( 7U )
#define FMC_SDRCR_CAS_Msk                                   ( 0x3UL << FMC_SDRCR_CAS_Pos )
#define FMC_SDRCR_CAS                                       ( FMC_SDRCR_CAS_Msk )
#define FMC_SDRCR_CAS_0                                     ( 0x1UL << FMC_SDRCR_CAS_Pos )
#define FMC_SDRCR_CAS_1                                     ( 0x2UL << FMC_SDRCR_CAS_Pos )

#define FMC_SDRCR_NB_Pos                                    ( 6U )
#define FMC_SDRCR_NB_Msk                                    ( 0x1UL << FMC_SDRCR_NB_Pos )
#define FMC_SDRCR_NB                                        ( FMC_SDRCR_NB_Msk )

#define FMC_SDRCR_MWID_Pos                                  ( 4U )
#define FMC_SDRCR_MWID_Msk                                  ( 0x3UL << FMC_SDRCR_MWID_Pos )
#define FMC_SDRCR_MWID                                      ( FMC_SDRCR_MWID_Msk )
#define FMC_SDRCR_MWID_0                                    ( 0x1UL << FMC_SDRCR_MWID_Pos )
#define FMC_SDRCR_MWID_1                                    ( 0x2UL << FMC_SDRCR_MWID_Pos )

#define FMC_SDRCR_NRA_Pos                                   ( 2U )
#define FMC_SDRCR_NRA_Msk                                   ( 0x3UL << FMC_SDRCR_NRA_Pos )
#define FMC_SDRCR_NRA                                       ( FMC_SDRCR_NRA_Msk )
#define FMC_SDRCR_NRA_0                                     ( 0x1UL << FMC_SDRCR_NRA_Pos )
#define FMC_SDRCR_NRA_1                                     ( 0x2UL << FMC_SDRCR_NRA_Pos )

#define FMC_SDRCR_NCA_Pos                                   ( 0U )
#define FMC_SDRCR_NCA_Msk                                   ( 0x3UL << FMC_SDRCR_NCA_Pos )
#define FMC_SDRCR_NCA                                       ( FMC_SDRCR_NCA_Msk )
#define FMC_SDRCR_NCA_0                                     ( 0x1UL << FMC_SDRCR_NCA_Pos )
#define FMC_SDRCR_NCA_1                                     ( 0x2UL << FMC_SDRCR_NCA_Pos )


/***************  Bits definition for FMC_SDRTR  **********************/

#define FMC_SDRTR_TRCD_Pos                                  ( 24U )
#define FMC_SDRTR_TRCD_Msk                                  ( 0xfUL << FMC_SDRTR_TRCD_Pos )
#define FMC_SDRTR_TRCD                                      ( FMC_SDRTR_TRCD_Msk )
#define FMC_SDRTR_TRCD_0                                    ( 0x1UL << FMC_SDRTR_TRCD_Pos )
#define FMC_SDRTR_TRCD_1                                    ( 0x2UL << FMC_SDRTR_TRCD_Pos )
#define FMC_SDRTR_TRCD_2                                    ( 0x4UL << FMC_SDRTR_TRCD_Pos )
#define FMC_SDRTR_TRCD_3                                    ( 0x8UL << FMC_SDRTR_TRCD_Pos )

#define FMC_SDRTR_TRP_Pos                                   ( 20U )
#define FMC_SDRTR_TRP_Msk                                   ( 0xfUL << FMC_SDRTR_TRP_Pos )
#define FMC_SDRTR_TRP                                       ( FMC_SDRTR_TRP_Msk )
#define FMC_SDRTR_TRP_0                                     ( 0x1UL << FMC_SDRTR_TRP_Pos )
#define FMC_SDRTR_TRP_1                                     ( 0x2UL << FMC_SDRTR_TRP_Pos )
#define FMC_SDRTR_TRP_2                                     ( 0x4UL << FMC_SDRTR_TRP_Pos )
#define FMC_SDRTR_TRP_3                                     ( 0x8UL << FMC_SDRTR_TRP_Pos )

#define FMC_SDRTR_TWR_Pos                                   ( 16U )
#define FMC_SDRTR_TWR_Msk                                   ( 0xfUL << FMC_SDRTR_TWR_Pos )
#define FMC_SDRTR_TWR                                       ( FMC_SDRTR_TWR_Msk )
#define FMC_SDRTR_TWR_0                                     ( 0x1UL << FMC_SDRTR_TWR_Pos )
#define FMC_SDRTR_TWR_1                                     ( 0x2UL << FMC_SDRTR_TWR_Pos )
#define FMC_SDRTR_TWR_2                                     ( 0x4UL << FMC_SDRTR_TWR_Pos )
#define FMC_SDRTR_TWR_3                                     ( 0x8UL << FMC_SDRTR_TWR_Pos )

#define FMC_SDRTR_TRC_Pos                                   ( 12U )
#define FMC_SDRTR_TRC_Msk                                   ( 0xfUL << FMC_SDRTR_TRC_Pos )
#define FMC_SDRTR_TRC                                       ( FMC_SDRTR_TRC_Msk )
#define FMC_SDRTR_TRC_0                                     ( 0x1UL << FMC_SDRTR_TRC_Pos )
#define FMC_SDRTR_TRC_1                                     ( 0x2UL << FMC_SDRTR_TRC_Pos )
#define FMC_SDRTR_TRC_2                                     ( 0x4UL << FMC_SDRTR_TRC_Pos )
#define FMC_SDRTR_TRC_3                                     ( 0x8UL << FMC_SDRTR_TRC_Pos )

#define FMC_SDRTR_TRAS_Pos                                  ( 8U )
#define FMC_SDRTR_TRAS_Msk                                  ( 0xfUL << FMC_SDRTR_TRAS_Pos )
#define FMC_SDRTR_TRAS                                      ( FMC_SDRTR_TRAS_Msk )
#define FMC_SDRTR_TRAS_0                                    ( 0x1UL << FMC_SDRTR_TRAS_Pos )
#define FMC_SDRTR_TRAS_1                                    ( 0x2UL << FMC_SDRTR_TRAS_Pos )
#define FMC_SDRTR_TRAS_2                                    ( 0x4UL << FMC_SDRTR_TRAS_Pos )
#define FMC_SDRTR_TRAS_3                                    ( 0x8UL << FMC_SDRTR_TRAS_Pos )

#define FMC_SDRTR_TXSR_Pos                                  ( 4U )
#define FMC_SDRTR_TXSR_Msk                                  ( 0xfUL << FMC_SDRTR_TXSR_Pos )
#define FMC_SDRTR_TXSR                                      ( FMC_SDRTR_TXSR_Msk )
#define FMC_SDRTR_TXSR_0                                    ( 0x1UL << FMC_SDRTR_TXSR_Pos )
#define FMC_SDRTR_TXSR_1                                    ( 0x2UL << FMC_SDRTR_TXSR_Pos )
#define FMC_SDRTR_TXSR_2                                    ( 0x4UL << FMC_SDRTR_TXSR_Pos )
#define FMC_SDRTR_TXSR_3                                    ( 0x8UL << FMC_SDRTR_TXSR_Pos )

#define FMC_SDRTR_TMRD_Pos                                  ( 0U )
#define FMC_SDRTR_TMRD_Msk                                  ( 0xfUL << FMC_SDRTR_TMRD_Pos )
#define FMC_SDRTR_TMRD                                      ( FMC_SDRTR_TMRD_Msk )
#define FMC_SDRTR_TMRD_0                                    ( 0x1UL << FMC_SDRTR_TMRD_Pos )
#define FMC_SDRTR_TMRD_1                                    ( 0x2UL << FMC_SDRTR_TMRD_Pos )
#define FMC_SDRTR_TMRD_2                                    ( 0x4UL << FMC_SDRTR_TMRD_Pos )
#define FMC_SDRTR_TMRD_3                                    ( 0x8UL << FMC_SDRTR_TMRD_Pos )


/***************  Bits definition for FMC_SDRCMD  **********************/

#define FMC_SDRCMD_MRD_Pos                                  ( 9U )
#define FMC_SDRCMD_MRD_Msk                                  ( 0x1fffUL << FMC_SDRCMD_MRD_Pos )
#define FMC_SDRCMD_MRD                                      ( FMC_SDRCMD_MRD_Msk )

#define FMC_SDRCMD_NARF_Pos                                 ( 5U )
#define FMC_SDRCMD_NARF_Msk                                 ( 0xfUL << FMC_SDRCMD_NARF_Pos )
#define FMC_SDRCMD_NARF                                     ( FMC_SDRCMD_NARF_Msk )
#define FMC_SDRCMD_NARF_0                                   ( 0x1UL << FMC_SDRCMD_NARF_Pos )
#define FMC_SDRCMD_NARF_1                                   ( 0x2UL << FMC_SDRCMD_NARF_Pos )
#define FMC_SDRCMD_NARF_2                                   ( 0x4UL << FMC_SDRCMD_NARF_Pos )
#define FMC_SDRCMD_NARF_3                                   ( 0x8UL << FMC_SDRCMD_NARF_Pos )

#define FMC_SDRCMD_CTD1_Pos                                 ( 4U )
#define FMC_SDRCMD_CTD1_Msk                                 ( 0x1UL << FMC_SDRCMD_CTD1_Pos )
#define FMC_SDRCMD_CTD1                                     ( FMC_SDRCMD_CTD1_Msk )

#define FMC_SDRCMD_CTD2_Pos                                 ( 3U )
#define FMC_SDRCMD_CTD2_Msk                                 ( 0x1UL << FMC_SDRCMD_CTD2_Pos )
#define FMC_SDRCMD_CTD2                                     ( FMC_SDRCMD_CTD2_Msk )

#define FMC_SDRCMD_CMD_Pos                                  ( 0U )
#define FMC_SDRCMD_CMD_Msk                                  ( 0x7UL << FMC_SDRCMD_CMD_Pos )
#define FMC_SDRCMD_CMD                                      ( FMC_SDRCMD_CMD_Msk )
#define FMC_SDRCMD_CMD_0                                    ( 0x1UL << FMC_SDRCMD_CMD_Pos )
#define FMC_SDRCMD_CMD_1                                    ( 0x2UL << FMC_SDRCMD_CMD_Pos )
#define FMC_SDRCMD_CMD_2                                    ( 0x4UL << FMC_SDRCMD_CMD_Pos )


/***************  Bits definition for FMC_SDRART  **********************/

#define FMC_SDRART_RFEIE_Pos                                ( 14U )
#define FMC_SDRART_RFEIE_Msk                                ( 0x1UL << FMC_SDRART_RFEIE_Pos )
#define FMC_SDRART_RFEIE                                    ( FMC_SDRART_RFEIE_Msk )

#define FMC_SDRART_COUNT_Pos                                ( 1U )
#define FMC_SDRART_COUNT_Msk                                ( 0x1fffUL << FMC_SDRART_COUNT_Pos )
#define FMC_SDRART_COUNT                                    ( FMC_SDRART_COUNT_Msk )

#define FMC_SDRART_CRFE_Pos                                 ( 0U )
#define FMC_SDRART_CRFE_Msk                                 ( 0x1UL << FMC_SDRART_CRFE_Pos )
#define FMC_SDRART_CRFE                                     ( FMC_SDRART_CRFE_Msk )


/***************  Bits definition for FMC_SDRSR  **********************/

#define FMC_SDRSR_BUSY_Pos                                  ( 5U )
#define FMC_SDRSR_BUSY_Msk                                  ( 0x1UL << FMC_SDRSR_BUSY_Pos )
#define FMC_SDRSR_BUSY                                      ( FMC_SDRSR_BUSY_Msk )

#define FMC_SDRSR_STA2_Pos                                  ( 3U )
#define FMC_SDRSR_STA2_Msk                                  ( 0x3UL << FMC_SDRSR_STA2_Pos )
#define FMC_SDRSR_STA2                                      ( FMC_SDRSR_STA2_Msk )
#define FMC_SDRSR_STA2_0                                    ( 0x1UL << FMC_SDRSR_STA2_Pos )
#define FMC_SDRSR_STA2_1                                    ( 0x2UL << FMC_SDRSR_STA2_Pos )

#define FMC_SDRSR_STA1_Pos                                  ( 1U )
#define FMC_SDRSR_STA1_Msk                                  ( 0x3UL << FMC_SDRSR_STA1_Pos )
#define FMC_SDRSR_STA1                                      ( FMC_SDRSR_STA1_Msk )
#define FMC_SDRSR_STA1_0                                    ( 0x1UL << FMC_SDRSR_STA1_Pos )
#define FMC_SDRSR_STA1_1                                    ( 0x2UL << FMC_SDRSR_STA1_Pos )

#define FMC_SDRSR_RFE_Pos                                   ( 0U )
#define FMC_SDRSR_RFE_Msk                                   ( 0x1UL << FMC_SDRSR_RFE_Pos )
#define FMC_SDRSR_RFE                                       ( FMC_SDRSR_RFE_Msk )


/***************  Bits definition for FMC_SDRSMA1  **********************/

#define FMC_SDRSMA_SMA1_Pos                                 ( 0U )
#define FMC_SDRSMA_SMA1_Msk                                 ( 0xffffffffUL << FMC_SDRSMA_SMA1_Pos )
#define FMC_SDRSMA_SMA1                                     ( FMC_SDRSMA_SMA1_Msk )

/***************  Bits definition for FMC_SDRSMA2  **********************/

#define FMC_SDRSMA_SMA2_Pos                                 ( 0U )
#define FMC_SDRSMA_SMA2_Msk                                 ( 0xffffffffUL << FMC_SDRSMA_SMA2_Pos )
#define FMC_SDRSMA_SMA2                                     ( FMC_SDRSMA_SMA2_Msk )

/***************  Bits definition for LPTIM_ISR  **********************/

#define LPTIM_ISR_REPOK_Pos                                 ( 8U )
#define LPTIM_ISR_REPOK_Msk                                 ( 0x1UL << LPTIM_ISR_REPOK_Pos )
#define LPTIM_ISR_REPOK                                     ( LPTIM_ISR_REPOK_Msk )

#define LPTIM_ISR_REPUE_Pos                                 ( 7U )
#define LPTIM_ISR_REPUE_Msk                                 ( 0x1UL << LPTIM_ISR_REPUE_Pos )
#define LPTIM_ISR_REPUE                                     ( LPTIM_ISR_REPUE_Msk )

#define LPTIM_ISR_DOWN_Pos                                  ( 6U )
#define LPTIM_ISR_DOWN_Msk                                  ( 0x1UL << LPTIM_ISR_DOWN_Pos )
#define LPTIM_ISR_DOWN                                      ( LPTIM_ISR_DOWN_Msk )

#define LPTIM_ISR_UP_Pos                                    ( 5U )
#define LPTIM_ISR_UP_Msk                                    ( 0x1UL << LPTIM_ISR_UP_Pos )
#define LPTIM_ISR_UP                                        ( LPTIM_ISR_UP_Msk )

#define LPTIM_ISR_ARROK_Pos                                 ( 4U )
#define LPTIM_ISR_ARROK_Msk                                 ( 0x1UL << LPTIM_ISR_ARROK_Pos )
#define LPTIM_ISR_ARROK                                     ( LPTIM_ISR_ARROK_Msk )

#define LPTIM_ISR_CMPOK_Pos                                 ( 3U )
#define LPTIM_ISR_CMPOK_Msk                                 ( 0x1UL << LPTIM_ISR_CMPOK_Pos )
#define LPTIM_ISR_CMPOK                                     ( LPTIM_ISR_CMPOK_Msk )

#define LPTIM_ISR_EXTTRIG_Pos                               ( 2U )
#define LPTIM_ISR_EXTTRIG_Msk                               ( 0x1UL << LPTIM_ISR_EXTTRIG_Pos )
#define LPTIM_ISR_EXTTRIG                                   ( LPTIM_ISR_EXTTRIG_Msk )

#define LPTIM_ISR_ARRM_Pos                                  ( 1U )
#define LPTIM_ISR_ARRM_Msk                                  ( 0x1UL << LPTIM_ISR_ARRM_Pos )
#define LPTIM_ISR_ARRM                                      ( LPTIM_ISR_ARRM_Msk )

#define LPTIM_ISR_CMPM_Pos                                  ( 0U )
#define LPTIM_ISR_CMPM_Msk                                  ( 0x1UL << LPTIM_ISR_CMPM_Pos )
#define LPTIM_ISR_CMPM                                      ( LPTIM_ISR_CMPM_Msk )


/***************  Bits definition for LPTIM_ICR  **********************/

#define LPTIM_ICR_REPOKCF_Pos                               ( 8U )
#define LPTIM_ICR_REPOKCF_Msk                               ( 0x1UL << LPTIM_ICR_REPOKCF_Pos )
#define LPTIM_ICR_REPOKCF                                   ( LPTIM_ICR_REPOKCF_Msk )

#define LPTIM_ICR_REPUECF_Pos                               ( 7U )
#define LPTIM_ICR_REPUECF_Msk                               ( 0x1UL << LPTIM_ICR_REPUECF_Pos )
#define LPTIM_ICR_REPUECF                                   ( LPTIM_ICR_REPUECF_Msk )

#define LPTIM_ICR_DOWNCF_Pos                                ( 6U )
#define LPTIM_ICR_DOWNCF_Msk                                ( 0x1UL << LPTIM_ICR_DOWNCF_Pos )
#define LPTIM_ICR_DOWNCF                                    ( LPTIM_ICR_DOWNCF_Msk )

#define LPTIM_ICR_UPCF_Pos                                  ( 5U )
#define LPTIM_ICR_UPCF_Msk                                  ( 0x1UL << LPTIM_ICR_UPCF_Pos )
#define LPTIM_ICR_UPCF                                      ( LPTIM_ICR_UPCF_Msk )

#define LPTIM_ICR_ARROKCF_Pos                               ( 4U )
#define LPTIM_ICR_ARROKCF_Msk                               ( 0x1UL << LPTIM_ICR_ARROKCF_Pos )
#define LPTIM_ICR_ARROKCF                                   ( LPTIM_ICR_ARROKCF_Msk )

#define LPTIM_ICR_CMPOKCF_Pos                               ( 3U )
#define LPTIM_ICR_CMPOKCF_Msk                               ( 0x1UL << LPTIM_ICR_CMPOKCF_Pos )
#define LPTIM_ICR_CMPOKCF                                   ( LPTIM_ICR_CMPOKCF_Msk )

#define LPTIM_ICR_EXTTRIGCF_Pos                             ( 2U )
#define LPTIM_ICR_EXTTRIGCF_Msk                             ( 0x1UL << LPTIM_ICR_EXTTRIGCF_Pos )
#define LPTIM_ICR_EXTTRIGCF                                 ( LPTIM_ICR_EXTTRIGCF_Msk )

#define LPTIM_ICR_ARRMCF_Pos                                ( 1U )
#define LPTIM_ICR_ARRMCF_Msk                                ( 0x1UL << LPTIM_ICR_ARRMCF_Pos )
#define LPTIM_ICR_ARRMCF                                    ( LPTIM_ICR_ARRMCF_Msk )

#define LPTIM_ICR_CMPMCF_Pos                                ( 0U )
#define LPTIM_ICR_CMPMCF_Msk                                ( 0x1UL << LPTIM_ICR_CMPMCF_Pos )
#define LPTIM_ICR_CMPMCF                                    ( LPTIM_ICR_CMPMCF_Msk )


/***************  Bits definition for LPTIM_IER  **********************/

#define LPTIM_IER_REPOKIE_Pos                               ( 8U )
#define LPTIM_IER_REPOKIE_Msk                               ( 0x1UL << LPTIM_IER_REPOKIE_Pos )
#define LPTIM_IER_REPOKIE                                   ( LPTIM_IER_REPOKIE_Msk )

#define LPTIM_IER_REPUEIE_Pos                               ( 7U )
#define LPTIM_IER_REPUEIE_Msk                               ( 0x1UL << LPTIM_IER_REPUEIE_Pos )
#define LPTIM_IER_REPUEIE                                   ( LPTIM_IER_REPUEIE_Msk )

#define LPTIM_IER_DOWNIE_Pos                                ( 6U )
#define LPTIM_IER_DOWNIE_Msk                                ( 0x1UL << LPTIM_IER_DOWNIE_Pos )
#define LPTIM_IER_DOWNIE                                    ( LPTIM_IER_DOWNIE_Msk )

#define LPTIM_IER_UPIE_Pos                                  ( 5U )
#define LPTIM_IER_UPIE_Msk                                  ( 0x1UL << LPTIM_IER_UPIE_Pos )
#define LPTIM_IER_UPIE                                      ( LPTIM_IER_UPIE_Msk )

#define LPTIM_IER_ARROKIE_Pos                               ( 4U )
#define LPTIM_IER_ARROKIE_Msk                               ( 0x1UL << LPTIM_IER_ARROKIE_Pos )
#define LPTIM_IER_ARROKIE                                   ( LPTIM_IER_ARROKIE_Msk )

#define LPTIM_IER_CMPOKIE_Pos                               ( 3U )
#define LPTIM_IER_CMPOKIE_Msk                               ( 0x1UL << LPTIM_IER_CMPOKIE_Pos )
#define LPTIM_IER_CMPOKIE                                   ( LPTIM_IER_CMPOKIE_Msk )

#define LPTIM_IER_EXTTRIGIE_Pos                             ( 2U )
#define LPTIM_IER_EXTTRIGIE_Msk                             ( 0x1UL << LPTIM_IER_EXTTRIGIE_Pos )
#define LPTIM_IER_EXTTRIGIE                                 ( LPTIM_IER_EXTTRIGIE_Msk )

#define LPTIM_IER_ARRMIE_Pos                                ( 1U )
#define LPTIM_IER_ARRMIE_Msk                                ( 0x1UL << LPTIM_IER_ARRMIE_Pos )
#define LPTIM_IER_ARRMIE                                    ( LPTIM_IER_ARRMIE_Msk )

#define LPTIM_IER_CMPMIE_Pos                                ( 0U )
#define LPTIM_IER_CMPMIE_Msk                                ( 0x1UL << LPTIM_IER_CMPMIE_Pos )
#define LPTIM_IER_CMPMIE                                    ( LPTIM_IER_CMPMIE_Msk )


/***************  Bits definition for LPTIM_CFGR1  **********************/

#define LPTIM_CFGR1_REP_LODMOD_Pos                          ( 25U )
#define LPTIM_CFGR1_REP_LODMOD_Msk                          ( 0x1UL << LPTIM_CFGR1_REP_LODMOD_Pos )
#define LPTIM_CFGR1_REP_LODMOD                              ( LPTIM_CFGR1_REP_LODMOD_Msk )

#define LPTIM_CFGR1_ENC_Pos                                 ( 24U )
#define LPTIM_CFGR1_ENC_Msk                                 ( 0x1UL << LPTIM_CFGR1_ENC_Pos )
#define LPTIM_CFGR1_ENC                                     ( LPTIM_CFGR1_ENC_Msk )

#define LPTIM_CFGR1_COUNTMODE_Pos                           ( 23U )
#define LPTIM_CFGR1_COUNTMODE_Msk                           ( 0x1UL << LPTIM_CFGR1_COUNTMODE_Pos )
#define LPTIM_CFGR1_COUNTMODE                               ( LPTIM_CFGR1_COUNTMODE_Msk )

#define LPTIM_CFGR1_PRELOAD_Pos                             ( 22U )
#define LPTIM_CFGR1_PRELOAD_Msk                             ( 0x1UL << LPTIM_CFGR1_PRELOAD_Pos )
#define LPTIM_CFGR1_PRELOAD                                 ( LPTIM_CFGR1_PRELOAD_Msk )

#define LPTIM_CFGR1_WAVPOL_Pos                              ( 21U )
#define LPTIM_CFGR1_WAVPOL_Msk                              ( 0x1UL << LPTIM_CFGR1_WAVPOL_Pos )
#define LPTIM_CFGR1_WAVPOL                                  ( LPTIM_CFGR1_WAVPOL_Msk )

#define LPTIM_CFGR1_WAVE_Pos                                ( 20U )
#define LPTIM_CFGR1_WAVE_Msk                                ( 0x1UL << LPTIM_CFGR1_WAVE_Pos )
#define LPTIM_CFGR1_WAVE                                    ( LPTIM_CFGR1_WAVE_Msk )

#define LPTIM_CFGR1_TIMEOUT_Pos                             ( 19U )
#define LPTIM_CFGR1_TIMEOUT_Msk                             ( 0x1UL << LPTIM_CFGR1_TIMEOUT_Pos )
#define LPTIM_CFGR1_TIMEOUT                                 ( LPTIM_CFGR1_TIMEOUT_Msk )

#define LPTIM_CFGR1_TRIGEN_Pos                              ( 17U )
#define LPTIM_CFGR1_TRIGEN_Msk                              ( 0x3UL << LPTIM_CFGR1_TRIGEN_Pos )
#define LPTIM_CFGR1_TRIGEN                                  ( LPTIM_CFGR1_TRIGEN_Msk )
#define LPTIM_CFGR1_TRIGEN_0                                ( 0x1UL << LPTIM_CFGR1_TRIGEN_Pos )
#define LPTIM_CFGR1_TRIGEN_1                                ( 0x2UL << LPTIM_CFGR1_TRIGEN_Pos )

#define LPTIM_CFGR1_TRIGSEL_Pos                             ( 13U )
#define LPTIM_CFGR1_TRIGSEL_Msk                             ( 0xfUL << LPTIM_CFGR1_TRIGSEL_Pos )
#define LPTIM_CFGR1_TRIGSEL                                 ( LPTIM_CFGR1_TRIGSEL_Msk )
#define LPTIM_CFGR1_TRIGSEL_0                               ( 0x1UL << LPTIM_CFGR1_TRIGSEL_Pos )
#define LPTIM_CFGR1_TRIGSEL_1                               ( 0x2UL << LPTIM_CFGR1_TRIGSEL_Pos )
#define LPTIM_CFGR1_TRIGSEL_2                               ( 0x4UL << LPTIM_CFGR1_TRIGSEL_Pos )
#define LPTIM_CFGR1_TRIGSEL_3                               ( 0x8UL << LPTIM_CFGR1_TRIGSEL_Pos )

#define LPTIM_CFGR1_PRESC_Pos                               ( 9U )
#define LPTIM_CFGR1_PRESC_Msk                               ( 0x7UL << LPTIM_CFGR1_PRESC_Pos )
#define LPTIM_CFGR1_PRESC                                   ( LPTIM_CFGR1_PRESC_Msk )
#define LPTIM_CFGR1_PRESC_0                                 ( 0x1UL << LPTIM_CFGR1_PRESC_Pos )
#define LPTIM_CFGR1_PRESC_1                                 ( 0x2UL << LPTIM_CFGR1_PRESC_Pos )
#define LPTIM_CFGR1_PRESC_2                                 ( 0x4UL << LPTIM_CFGR1_PRESC_Pos )

#define LPTIM_CFGR1_TRGFLT_Pos                              ( 6U )
#define LPTIM_CFGR1_TRGFLT_Msk                              ( 0x3UL << LPTIM_CFGR1_TRGFLT_Pos )
#define LPTIM_CFGR1_TRGFLT                                  ( LPTIM_CFGR1_TRGFLT_Msk )
#define LPTIM_CFGR1_TRGFLT_0                                ( 0x1UL << LPTIM_CFGR1_TRGFLT_Pos )
#define LPTIM_CFGR1_TRGFLT_1                                ( 0x2UL << LPTIM_CFGR1_TRGFLT_Pos )

#define LPTIM_CFGR1_CKFLT_Pos                               ( 3U )
#define LPTIM_CFGR1_CKFLT_Msk                               ( 0x3UL << LPTIM_CFGR1_CKFLT_Pos )
#define LPTIM_CFGR1_CKFLT                                   ( LPTIM_CFGR1_CKFLT_Msk )
#define LPTIM_CFGR1_CKFLT_0                                 ( 0x1UL << LPTIM_CFGR1_CKFLT_Pos )
#define LPTIM_CFGR1_CKFLT_1                                 ( 0x2UL << LPTIM_CFGR1_CKFLT_Pos )

#define LPTIM_CFGR1_CKPOL_Pos                               ( 1U )
#define LPTIM_CFGR1_CKPOL_Msk                               ( 0x3UL << LPTIM_CFGR1_CKPOL_Pos )
#define LPTIM_CFGR1_CKPOL                                   ( LPTIM_CFGR1_CKPOL_Msk )
#define LPTIM_CFGR1_CKPOL_0                                 ( 0x1UL << LPTIM_CFGR1_CKPOL_Pos )
#define LPTIM_CFGR1_CKPOL_1                                 ( 0x2UL << LPTIM_CFGR1_CKPOL_Pos )

#define LPTIM_CFGR1_CKSEL_Pos                               ( 0U )
#define LPTIM_CFGR1_CKSEL_Msk                               ( 0x1UL << LPTIM_CFGR1_CKSEL_Pos )
#define LPTIM_CFGR1_CKSEL                                   ( LPTIM_CFGR1_CKSEL_Msk )


/***************  Bits definition for LPTIM_CR  **********************/

#define LPTIM_CR_RSTARE_Pos                                 ( 4U )
#define LPTIM_CR_RSTARE_Msk                                 ( 0x1UL << LPTIM_CR_RSTARE_Pos )
#define LPTIM_CR_RSTARE                                     ( LPTIM_CR_RSTARE_Msk )

#define LPTIM_CR_COUNTRST_Pos                               ( 3U )
#define LPTIM_CR_COUNTRST_Msk                               ( 0x1UL << LPTIM_CR_COUNTRST_Pos )
#define LPTIM_CR_COUNTRST                                   ( LPTIM_CR_COUNTRST_Msk )

#define LPTIM_CR_CNTSTRT_Pos                                ( 2U )
#define LPTIM_CR_CNTSTRT_Msk                                ( 0x1UL << LPTIM_CR_CNTSTRT_Pos )
#define LPTIM_CR_CNTSTRT                                    ( LPTIM_CR_CNTSTRT_Msk )

#define LPTIM_CR_SNGSTRT_Pos                                ( 1U )
#define LPTIM_CR_SNGSTRT_Msk                                ( 0x1UL << LPTIM_CR_SNGSTRT_Pos )
#define LPTIM_CR_SNGSTRT                                    ( LPTIM_CR_SNGSTRT_Msk )

#define LPTIM_CR_ENABLE_Pos                                 ( 0U )
#define LPTIM_CR_ENABLE_Msk                                 ( 0x1UL << LPTIM_CR_ENABLE_Pos )
#define LPTIM_CR_ENABLE                                     ( LPTIM_CR_ENABLE_Msk )


/***************  Bits definition for LPTIM_CMP  **********************/

#define LPTIM_CMP_CMP_Pos                                   ( 0U )
#define LPTIM_CMP_CMP_Msk                                   ( 0xffffUL << LPTIM_CMP_CMP_Pos )
#define LPTIM_CMP_CMP                                       ( LPTIM_CMP_CMP_Msk )


/***************  Bits definition for LPTIM_ARR  **********************/

#define LPTIM_ARR_ARR_Pos                                   ( 0U )
#define LPTIM_ARR_ARR_Msk                                   ( 0xffffUL << LPTIM_ARR_ARR_Pos )
#define LPTIM_ARR_ARR                                       ( LPTIM_ARR_ARR_Msk )


/***************  Bits definition for LPTIM_CNT  **********************/

#define LPTIM_CNT_CNT_Pos                                   ( 0U )
#define LPTIM_CNT_CNT_Msk                                   ( 0xffffUL << LPTIM_CNT_CNT_Pos )
#define LPTIM_CNT_CNT                                       ( LPTIM_CNT_CNT_Msk )


/***************  Bits definition for LPTIM_CFGR2  **********************/

#define LPTIM_CFGR2_IN2SEL_Pos                              ( 4U )
#define LPTIM_CFGR2_IN2SEL_Msk                              ( 0xfUL << LPTIM_CFGR2_IN2SEL_Pos )
#define LPTIM_CFGR2_IN2SEL                                  ( LPTIM_CFGR2_IN2SEL_Msk )
#define LPTIM_CFGR2_IN2SEL_0                                ( 0x1UL << LPTIM_CFGR2_IN2SEL_Pos )
#define LPTIM_CFGR2_IN2SEL_1                                ( 0x2UL << LPTIM_CFGR2_IN2SEL_Pos )
#define LPTIM_CFGR2_IN2SEL_2                                ( 0x4UL << LPTIM_CFGR2_IN2SEL_Pos )
#define LPTIM_CFGR2_IN2SEL_3                                ( 0x8UL << LPTIM_CFGR2_IN2SEL_Pos )

#define LPTIM_CFGR2_IN1SEL_Pos                              ( 0U )
#define LPTIM_CFGR2_IN1SEL_Msk                              ( 0xfUL << LPTIM_CFGR2_IN1SEL_Pos )
#define LPTIM_CFGR2_IN1SEL                                  ( LPTIM_CFGR2_IN1SEL_Msk )
#define LPTIM_CFGR2_IN1SEL_0                                ( 0x1UL << LPTIM_CFGR2_IN1SEL_Pos )
#define LPTIM_CFGR2_IN1SEL_1                                ( 0x2UL << LPTIM_CFGR2_IN1SEL_Pos )
#define LPTIM_CFGR2_IN1SEL_2                                ( 0x4UL << LPTIM_CFGR2_IN1SEL_Pos )
#define LPTIM_CFGR2_IN1SEL_3                                ( 0x8UL << LPTIM_CFGR2_IN1SEL_Pos )


/***************  Bits definition for LPTIM_RCR  **********************/

#define LPTIM_RCR_REP_Pos                                   ( 0U )
#define LPTIM_RCR_REP_Msk                                   ( 0xffUL << LPTIM_RCR_REP_Pos )
#define LPTIM_RCR_REP                                       ( LPTIM_RCR_REP_Msk )
#define LPTIM_RCR_REP_0                                     ( 0x1UL << LPTIM_RCR_REP_Pos )
#define LPTIM_RCR_REP_1                                     ( 0x2UL << LPTIM_RCR_REP_Pos )
#define LPTIM_RCR_REP_2                                     ( 0x4UL << LPTIM_RCR_REP_Pos )
#define LPTIM_RCR_REP_3                                     ( 0x8UL << LPTIM_RCR_REP_Pos )
#define LPTIM_RCR_REP_4                                     ( 0x10UL << LPTIM_RCR_REP_Pos )
#define LPTIM_RCR_REP_5                                     ( 0x20UL << LPTIM_RCR_REP_Pos )
#define LPTIM_RCR_REP_6                                     ( 0x40UL << LPTIM_RCR_REP_Pos )
#define LPTIM_RCR_REP_7                                     ( 0x80UL << LPTIM_RCR_REP_Pos )


/***************  Bits definition for OPA_CSR  **********************/

#define OPA_CSR_LOCK_Pos                                    ( 31U )
#define OPA_CSR_LOCK_Msk                                    ( 0x1UL << OPA_CSR_LOCK_Pos )
#define OPA_CSR_LOCK                                        ( OPA_CSR_LOCK_Msk )

#define OPA_CSR_REV_Pos                                     ( 29U )
#define OPA_CSR_REV_Msk                                     ( 0x3UL << OPA_CSR_REV_Pos )
#define OPA_CSR_REV                                         ( OPA_CSR_REV_Msk )
#define OPA_CSR_REV_0                                       ( 0x1UL << OPA_CSR_REV_Pos )
#define OPA_CSR_REV_1                                       ( 0x2UL << OPA_CSR_REV_Pos )

#define OPA_CSR_HSM_Pos                                     ( 28U )
#define OPA_CSR_HSM_Msk                                     ( 0x1UL << OPA_CSR_HSM_Pos )
#define OPA_CSR_HSM                                         ( OPA_CSR_HSM_Msk )

#define OPA_CSR_GAIN_SEL_Pos                                ( 23U )
#define OPA_CSR_GAIN_SEL_Msk                                ( 0x1fUL << OPA_CSR_GAIN_SEL_Pos )
#define OPA_CSR_GAIN_SEL                                    ( OPA_CSR_GAIN_SEL_Msk )
#define OPA_CSR_GAIN_SEL_0                                  ( 0x1UL << OPA_CSR_GAIN_SEL_Pos )
#define OPA_CSR_GAIN_SEL_1                                  ( 0x2UL << OPA_CSR_GAIN_SEL_Pos )
#define OPA_CSR_GAIN_SEL_2                                  ( 0x4UL << OPA_CSR_GAIN_SEL_Pos )
#define OPA_CSR_GAIN_SEL_3                                  ( 0x8UL << OPA_CSR_GAIN_SEL_Pos )
#define OPA_CSR_GAIN_SEL_4                                  ( 0x10UL << OPA_CSR_GAIN_SEL_Pos )

#define OPA_CSR_POL_SEL_Pos                                 ( 21U )
#define OPA_CSR_POL_SEL_Msk                                 ( 0x3UL << OPA_CSR_POL_SEL_Pos )
#define OPA_CSR_POL_SEL                                     ( OPA_CSR_POL_SEL_Msk )
#define OPA_CSR_POL_SEL_0                                   ( 0x1UL << OPA_CSR_POL_SEL_Pos )
#define OPA_CSR_POL_SEL_1                                   ( 0x2UL << OPA_CSR_POL_SEL_Pos )

#define OPA_CSR_VINM0_EN_Pos                                ( 20U )
#define OPA_CSR_VINM0_EN_Msk                                ( 0x1UL << OPA_CSR_VINM0_EN_Pos )
#define OPA_CSR_VINM0_EN                                    ( OPA_CSR_VINM0_EN_Msk )

#define OPA_CSR_MODE_SEL_Pos                                ( 18U )
#define OPA_CSR_MODE_SEL_Msk                                ( 0x3UL << OPA_CSR_MODE_SEL_Pos )
#define OPA_CSR_MODE_SEL                                    ( OPA_CSR_MODE_SEL_Msk )
#define OPA_CSR_MODE_SEL_0                                  ( 0x1UL << OPA_CSR_MODE_SEL_Pos )
#define OPA_CSR_MODE_SEL_1                                  ( 0x2UL << OPA_CSR_MODE_SEL_Pos )

#define OPA_CSR_VINP_SEL_Pos                                ( 16U )
#define OPA_CSR_VINP_SEL_Msk                                ( 0x3UL << OPA_CSR_VINP_SEL_Pos )
#define OPA_CSR_VINP_SEL                                    ( OPA_CSR_VINP_SEL_Msk )
#define OPA_CSR_VINP_SEL_0                                  ( 0x1UL << OPA_CSR_VINP_SEL_Pos )
#define OPA_CSR_VINP_SEL_1                                  ( 0x2UL << OPA_CSR_VINP_SEL_Pos )

#define OPA_CSR_OUT_SEL_Pos                                 ( 14U )
#define OPA_CSR_OUT_SEL_Msk                                 ( 0x3UL << OPA_CSR_OUT_SEL_Pos )
#define OPA_CSR_OUT_SEL                                     ( OPA_CSR_OUT_SEL_Msk )
#define OPA_CSR_OUT_SEL_0                                   ( 0x1UL << OPA_CSR_OUT_SEL_Pos )
#define OPA_CSR_OUT_SEL_1                                   ( 0x2UL << OPA_CSR_OUT_SEL_Pos )

#define OPA_CSR_TRIM_OSN_Pos                                ( 9U )
#define OPA_CSR_TRIM_OSN_Msk                                ( 0x1fUL << OPA_CSR_TRIM_OSN_Pos )
#define OPA_CSR_TRIM_OSN                                    ( OPA_CSR_TRIM_OSN_Msk )
#define OPA_CSR_TRIM_OSN_0                                  ( 0x1UL << OPA_CSR_TRIM_OSN_Pos )
#define OPA_CSR_TRIM_OSN_1                                  ( 0x2UL << OPA_CSR_TRIM_OSN_Pos )
#define OPA_CSR_TRIM_OSN_2                                  ( 0x4UL << OPA_CSR_TRIM_OSN_Pos )
#define OPA_CSR_TRIM_OSN_3                                  ( 0x8UL << OPA_CSR_TRIM_OSN_Pos )
#define OPA_CSR_TRIM_OSN_4                                  ( 0x10UL << OPA_CSR_TRIM_OSN_Pos )

#define OPA_CSR_TRIM_OSP_Pos                                ( 4U )
#define OPA_CSR_TRIM_OSP_Msk                                ( 0x1fUL << OPA_CSR_TRIM_OSP_Pos )
#define OPA_CSR_TRIM_OSP                                    ( OPA_CSR_TRIM_OSP_Msk )
#define OPA_CSR_TRIM_OSP_0                                  ( 0x1UL << OPA_CSR_TRIM_OSP_Pos )
#define OPA_CSR_TRIM_OSP_1                                  ( 0x2UL << OPA_CSR_TRIM_OSP_Pos )
#define OPA_CSR_TRIM_OSP_2                                  ( 0x4UL << OPA_CSR_TRIM_OSP_Pos )
#define OPA_CSR_TRIM_OSP_3                                  ( 0x8UL << OPA_CSR_TRIM_OSP_Pos )
#define OPA_CSR_TRIM_OSP_4                                  ( 0x10UL << OPA_CSR_TRIM_OSP_Pos )

#define OPA_CSR_CAL_OUT_Pos                                 ( 3U )
#define OPA_CSR_CAL_OUT_Msk                                 ( 0x1UL << OPA_CSR_CAL_OUT_Pos )
#define OPA_CSR_CAL_OUT                                     ( OPA_CSR_CAL_OUT_Msk )

#define OPA_CSR_CAL_NEN_Pos                                 ( 2U )
#define OPA_CSR_CAL_NEN_Msk                                 ( 0x1UL << OPA_CSR_CAL_NEN_Pos )
#define OPA_CSR_CAL_NEN                                     ( OPA_CSR_CAL_NEN_Msk )

#define OPA_CSR_CAL_PEN_Pos                                 ( 1U )
#define OPA_CSR_CAL_PEN_Msk                                 ( 0x1UL << OPA_CSR_CAL_PEN_Pos )
#define OPA_CSR_CAL_PEN                                     ( OPA_CSR_CAL_PEN_Msk )

#define OPA_CSR_EN_Pos                                      ( 0U )
#define OPA_CSR_EN_Msk                                      ( 0x1UL << OPA_CSR_EN_Pos )
#define OPA_CSR_EN                                          ( OPA_CSR_EN_Msk )

/***************  Bits definition for FMC_NAND_CTRL  **********************/

#define FMC_NAND_CTRL_EDO_EN_Pos                              ( 7U )
#define FMC_NAND_CTRL_EDO_EN_Msk                              ( 0x1UL << FMC_NAND_CTRL_EDO_EN_Pos )
#define FMC_NAND_CTRL_EDO_EN                                  ( FMC_NAND_CTRL_EDO_EN_Msk )

#define FMC_NAND_CTRL_RBNINT_EN_Pos                           ( 6U )
#define FMC_NAND_CTRL_RBNINT_EN_Msk                           ( 0x1UL << FMC_NAND_CTRL_RBNINTEN_Pos )
#define FMC_NAND_CTRL_RBNINT_EN                               ( FMC_NAND_CTRL_RBNINTEN_Msk )

#define FMC_NAND_CTRL_ENDIAN_EN_Pos                           ( 5U )
#define FMC_NAND_CTRL_ENDIAN_EN_Msk                           ( 0x1UL << FMC_NAND_CTRL_ENDIAN_Pos )
#define FMC_NAND_CTRL_ENDIAN_EN                               ( FMC_NAND_CTRL_ENDIAN_Msk )

#define FMC_NAND_CTRL_FWP_Pos                                 ( 4U )
#define FMC_NAND_CTRL_FWP_Msk                                 ( 0x1UL << FMC_NAND_CTRL_FWP_Pos )
#define FMC_NAND_CTRL_FWP                                     ( FMC_NAND_CTRL_FWP_Msk )

#define FMC_NAND_CTRL_FCE_Pos                                 ( 0U )
#define FMC_NAND_CTRL_FCE_Msk                                 ( 0xfUL << FMC_NAND_CTRL_FCE_Pos )
#define FMC_NAND_CTRL_FCE                                     ( FMC_NAND_CTRL_FCE_Msk )
#define FMC_NAND_CTRL_FCE_0                                   ( 0x1UL << FMC_NAND_CTRL_FCE_Pos )
#define FMC_NAND_CTRL_FCE_1                                   ( 0x2UL << FMC_NAND_CTRL_FCE_Pos )
#define FMC_NAND_CTRL_FCE_2                                   ( 0x4UL << FMC_NAND_CTRL_FCE_Pos )
#define FMC_NAND_CTRL_FCE_3                                   ( 0x8UL << FMC_NAND_CTRL_FCE_Pos )

/***************  Bits definition for FMC_NAND_WST  **********************/

#define FMC_NAND_WST_TADL_Pos                                 ( 24U )
#define FMC_NAND_WST_TADL_Msk                                 ( 0xfUL << FMC_NAND_WST_TADL_Pos )
#define FMC_NAND_WST_TADL                                     ( FMC_NAND_WST_TADL_Msk )
#define FMC_NAND_WST_TADL_0                                   ( 0x1UL << FMC_NAND_WST_TADL_Pos )
#define FMC_NAND_WST_TADL_1                                   ( 0x2UL << FMC_NAND_WST_TADL_Pos )
#define FMC_NAND_WST_TADL_2                                   ( 0x4UL << FMC_NAND_WST_TADL_Pos )
#define FMC_NAND_WST_TADL_3                                   ( 0x8UL << FMC_NAND_WST_TADL_Pos )

#define FMC_NAND_WST_TRHW_Pos                                 ( 20U )
#define FMC_NAND_WST_TRHW_Msk                                 ( 0xfUL << FMC_NAND_WST_TRHW_Pos )
#define FMC_NAND_WST_TRHW                                     ( FMC_NAND_WST_TRHW_Msk )
#define FMC_NAND_WST_TRHW_0                                   ( 0x1UL << FMC_NAND_WST_TRHW_Pos )
#define FMC_NAND_WST_TRHW_1                                   ( 0x2UL << FMC_NAND_WST_TRHW_Pos )
#define FMC_NAND_WST_TRHW_2                                   ( 0x4UL << FMC_NAND_WST_TRHW_Pos )
#define FMC_NAND_WST_TRHW_3                                   ( 0x8UL << FMC_NAND_WST_TRHW_Pos )

#define FMC_NAND_WST_TWHR_Pos                                 ( 16U )
#define FMC_NAND_WST_TWHR_Msk                                 ( 0xfUL << FMC_NAND_WST_TWHR_Pos )
#define FMC_NAND_WST_TWHR                                     ( FMC_NAND_WST_TWHR_Msk )
#define FMC_NAND_WST_TWHR_0                                   ( 0x1UL << FMC_NAND_WST_TWHR_Pos )
#define FMC_NAND_WST_TWHR_1                                   ( 0x2UL << FMC_NAND_WST_TWHR_Pos )
#define FMC_NAND_WST_TWHR_2                                   ( 0x4UL << FMC_NAND_WST_TWHR_Pos )
#define FMC_NAND_WST_TWHR_3                                   ( 0x8UL << FMC_NAND_WST_TWHR_Pos )

#define FMC_NAND_WST_TREH_Pos                                 ( 12U )
#define FMC_NAND_WST_TREH_Msk                                 ( 0xfUL << FMC_NAND_WST_TREH_Pos )
#define FMC_NAND_WST_TREH                                     ( FMC_NAND_WST_TREH_Msk )
#define FMC_NAND_WST_TREH_0                                   ( 0x1UL << FMC_NAND_WST_TREH_Pos )
#define FMC_NAND_WST_TREH_1                                   ( 0x2UL << FMC_NAND_WST_TREH_Pos )
#define FMC_NAND_WST_TREH_2                                   ( 0x4UL << FMC_NAND_WST_TREH_Pos )
#define FMC_NAND_WST_TREH_3                                   ( 0x8UL << FMC_NAND_WST_TREH_Pos )


#define FMC_NAND_WST_TRP_Pos                                  ( 8U )
#define FMC_NAND_WST_TRP_Msk                                  ( 0xfUL << FMC_NAND_WST_TRP_Pos )
#define FMC_NAND_WST_TRP                                      ( FMC_NAND_WST_TRP_Msk )
#define FMC_NAND_WST_TRP_0                                    ( 0x1UL << FMC_NAND_WST_TRP_Pos )
#define FMC_NAND_WST_TRP_1                                    ( 0x2UL << FMC_NAND_WST_TRP_Pos )
#define FMC_NAND_WST_TRP_2                                    ( 0x4UL << FMC_NAND_WST_TRP_Pos )
#define FMC_NAND_WST_TRP_3                                    ( 0x8UL << FMC_NAND_WST_TRP_Pos )

#define FMC_NAND_WST_TWH_Pos                                  ( 4U )
#define FMC_NAND_WST_TWH_Msk                                  ( 0xfUL << FMC_NAND_WST_TWH_Pos )
#define FMC_NAND_WST_TWH                                      ( FMC_NAND_WST_TWH_Msk )
#define FMC_NAND_WST_TWH_0                                    ( 0x1UL << FMC_NAND_WST_TWH_Pos )
#define FMC_NAND_WST_TWH_1                                    ( 0x2UL << FMC_NAND_WST_TWH_Pos )
#define FMC_NAND_WST_TWH_2                                    ( 0x4UL << FMC_NAND_WST_TWH_Pos )
#define FMC_NAND_WST_TWH_3                                    ( 0x8UL << FMC_NAND_WST_TWH_Pos )

#define FMC_NAND_WST_TWP_Pos                                  ( 0U )
#define FMC_NAND_WST_TWP_Msk                                  ( 0xfUL << FMC_NAND_WST_TWP_Pos )
#define FMC_NAND_WST_TWP                                      ( FMC_NAND_WST_TWP_Msk )
#define FMC_NAND_WST_TWP_0                                    ( 0x1UL << FMC_NAND_WST_TWP_Pos )
#define FMC_NAND_WST_TWP_1                                    ( 0x2UL << FMC_NAND_WST_TWP_Pos )
#define FMC_NAND_WST_TWP_2                                    ( 0x4UL << FMC_NAND_WST_TWP_Pos )
#define FMC_NAND_WST_TWP_3                                    ( 0x8UL << FMC_NAND_WST_TWP_Pos )

/***************  Bits definition for FMC_NAND_STATUS  **********************/

#define FMC_NAND_STATUS_POS_RBN_Pos                           ( 4U )
#define FMC_NAND_STATUS_POS_RBN_Msk                           ( 0xfUL << FMC_NAND_STATUS_POS_RBN_Pos )
#define FMC_NAND_STATUS_POS_RBN                               ( FMC_NAND_STATUS_POS_RBN_Msk )
#define FMC_NAND_STATUS_POS_RBN_0                             ( 0x1UL << FMC_NAND_STATUS_POS_RBN_Pos )
#define FMC_NAND_STATUS_POS_RBN_1                             ( 0x2UL << FMC_NAND_STATUS_POS_RBN_Pos )
#define FMC_NAND_STATUS_POS_RBN_2                             ( 0x4UL << FMC_NAND_STATUS_POS_RBN_Pos )
#define FMC_NAND_STATUS_POS_RBN_3                             ( 0x8UL << FMC_NAND_STATUS_POS_RBN_Pos )

#define FMC_NAND_STATUS_RBN_Pos                               ( 0U )
#define FMC_NAND_STATUS_RBN_Msk                               ( 0xfUL << FMC_NAND_STATUS_RBN_Pos )
#define FMC_NAND_STATUS_RBN                                   ( FMC_NAND_STATUS_RBN_Msk )
#define FMC_NAND_STATUS_RBN_0                                 ( 0x1UL << FMC_NAND_STATUS_RBN_Pos )
#define FMC_NAND_STATUS_RBN_1                                 ( 0x2UL << FMC_NAND_STATUS_RBN_Pos )
#define FMC_NAND_STATUS_RBN_2                                 ( 0x4UL << FMC_NAND_STATUS_RBN_Pos )
#define FMC_NAND_STATUS_RBN_3                                 ( 0x8UL << FMC_NAND_STATUS_RBN_Pos )

/***************  Bits definition for FMC_NAND_BCH_CONFIG  **********************/

#define FMC_NAND_BCH_CONFIG_BCH_TYPE_Pos                         ( 0U )
#define FMC_NAND_BCH_CONFIG_BCH_TYPE_Msk                         ( 0x7UL << FMC_NAND_BCH_CONFIG_BCH_TYPE_Pos )
#define FMC_NAND_BCH_CONFIG_BCH_TYPE                             ( FMC_NAND_BCH_CONFIG_BCH_TYPE_Msk )
#define FMC_NAND_BCH_CONFIG_BCH_TYPE_0                           ( 0x1UL << FMC_NAND_BCH_CONFIG_BCH_TYPE_Pos )
#define FMC_NAND_BCH_CONFIG_BCH_TYPE_1                           ( 0x2UL << FMC_NAND_BCH_CONFIG_BCH_TYPE_Pos )
#define FMC_NAND_BCH_CONFIG_BCH_TYPE_2                           ( 0x4UL << FMC_NAND_BCH_CONFIG_BCH_TYPE_Pos )

/***************  Bits definition for FMC_NAND_BCH_CTRL  **********************/

#define FMC_NAND_BCH_CTRL_AUTO_CORRECT_Pos                       ( 5U )
#define FMC_NAND_BCH_CTRL_AUTO_CORRECT_Msk                       ( 0x1UL << FMC_NAND_BCH_CTRL_AUTO_CORRECT_Pos )
#define FMC_NAND_BCH_CTRL_AUTO_CORRECT                           ( FMC_NAND_BCH_CTRL_AUTO_CORRECT_Msk )

#define FMC_NAND_BCH_CTRL_DECODE_INT_ENABLE_Pos                  ( 4U )
#define FMC_NAND_BCH_CTRL_DECODE_INT_ENABLE_Msk                  ( 0x1UL << FMC_NAND_BCH_CTRL_DECODE_INT_ENABLE_Pos )
#define FMC_NAND_BCH_CTRL_DECODE_INT_ENABLE                      ( FMC_NAND_BCH_CTRL_DECODE_INT_ENABLE_Msk )

#define FMC_NAND_BCH_CTRL_RESET_CHANNEL_Pos                      ( 3U )
#define FMC_NAND_BCH_CTRL_RESET_CHANNEL_Msk                      ( 0x1UL << FMC_NAND_BCH_CTRL_RESET_CHANNEL_Pos )
#define FMC_NAND_BCH_CTRL_RESET_CHANNEL                          ( FMC_NAND_BCH_CTRL_RESET_CHANNEL_Msk )

#define FMC_NAND_BCH_CTRL_IGALL1_Pos                             ( 1U )
#define FMC_NAND_BCH_CTRL_IGALL1_Msk                             ( 0x1UL << FMC_NAND_BCH_CTRL_IGALL1_Pos )
#define FMC_NAND_BCH_CTRL_IGALL1                                 ( FMC_NAND_BCH_CTRL_IGALL1_Msk )

#define FMC_NAND_BCH_CTRL_MODE_Pos                               ( 0U )
#define FMC_NAND_BCH_CTRL_MODE_Msk                               ( 0x1UL << FMC_NAND_BCH_CTRL_MODE_Pos )
#define FMC_NAND_BCH_CTRL_MODE                                   ( FMC_NAND_BCH_CTRL_MODE_Msk )

/***************  Bits definition for FMC_NAND_BCH_STATUS  **********************/

#define FMC_NAND_BCH_STATUS_CEN_Pos                              ( 24U )
#define FMC_NAND_BCH_STATUS_CEN_Msk                              ( 0xffUL << FMC_NAND_BCH_STATUS_CEN_Pos )
#define FMC_NAND_BCH_STATUS_CEN                                  ( FMC_NAND_BCH_STATUS_CEN_Msk )

#define FMC_NAND_BCH_STATUS_DEN_Pos                              ( 16U )
#define FMC_NAND_BCH_STATUS_DEN_Msk                              ( 0xffUL << FMC_NAND_BCH_STATUS_DEN_Pos )
#define FMC_NAND_BCH_STATUS_DEN                                  ( FMC_NAND_BCH_STATUS_DEN_Msk )

#define FMC_NAND_BCH_STATUS_ERN_Pos                              ( 8U )
#define FMC_NAND_BCH_STATUS_ERN_Msk                              ( 0xffUL << FMC_NAND_BCH_STATUS_ERN_Pos )
#define FMC_NAND_BCH_STATUS_ERN                                  ( FMC_NAND_BCH_STATUS_ERN_Msk )

#define FMC_NAND_BCH_STATUS_DATA_ALL0_Pos                        ( 6U )
#define FMC_NAND_BCH_STATUS_DATA_ALL0_Msk                        ( 0x1UL << FMC_NAND_BCH_STATUS_DATA_ALL0_Pos )
#define FMC_NAND_BCH_STATUS_DATA_ALL0                            ( FMC_NAND_BCH_STATUS_DATA_ALL0_Msk )

#define FMC_NAND_BCH_STATUS_DATA_ALL1_Pos                        ( 5U )
#define FMC_NAND_BCH_STATUS_DATA_ALL1_Msk                        ( 0x1UL << FMC_NAND_BCH_STATUS_DATA_ALL1_Pos )
#define FMC_NAND_BCH_STATUS_DATA_ALL1                            ( FMC_NAND_BCH_STATUS_DATA_ALL1_Msk )

#define FMC_NAND_BCH_STATUS_BCH_FAIL_Pos                         ( 4U )
#define FMC_NAND_BCH_STATUS_BCH_FAIL_Msk                         ( 0x1UL << FMC_NAND_BCH_STATUS_BCH_FAIL_Pos )
#define FMC_NAND_BCH_STATUS_BCH_FAIL                             ( FMC_NAND_BCH_STATUS_BCH_FAIL_Msk )

#define FMC_NAND_BCH_STATUS_CORRECT_DONE_Pos                     ( 3U )
#define FMC_NAND_BCH_STATUS_CORRECT_DONE_Msk                     ( 0x1UL << FMC_NAND_BCH_STATUS_CORRECT_DONE_Pos )
#define FMC_NAND_BCH_STATUS_CORRECT_DONE                         ( FMC_NAND_BCH_STATUS_CORRECT_DONE_Msk )

#define FMC_NAND_BCH_STATUS_BM_DONE_Pos                          ( 2U )
#define FMC_NAND_BCH_STATUS_BM_DONE_Msk                          ( 0x1UL << FMC_NAND_BCH_STATUS_BM_DONE_Pos )
#define FMC_NAND_BCH_STATUS_BM_DONE                              ( FMC_NAND_BCH_STATUS_BM_DONE_Msk )

#define FMC_NAND_BCH_STATUS_SNYDROME_DONE_Pos                    ( 1U )
#define FMC_NAND_BCH_STATUS_SNYDROME_DONE_Msk                    ( 0x1UL << FMC_NAND_BCH_STATUS_SNYDROME_DONE_Pos )
#define FMC_NAND_BCH_STATUS_SNYDROME_DONE                        ( FMC_NAND_BCH_STATUS_SNYDROME_DONE_Msk )

#define FMC_NAND_BCH_STATUS_ENCODE_CLR_Pos                       ( 0U )
#define FMC_NAND_BCH_STATUS_ENCODE_CLR_Msk                       ( 0x1UL << FMC_NAND_BCH_STATUS_ENCODE_CLR_Pos )
#define FMC_NAND_BCH_STATUS_ENCODE_CLR                           ( FMC_NAND_BCH_STATUS_ENCODE_CLR_Msk )

/***************  Bits definition for COMP_CR  **********************/

#define COMP_CR_LOCK_Pos                                    ( 31U )
#define COMP_CR_LOCK_Msk                                    ( 0x1UL << COMP_CR_LOCK_Pos )
#define COMP_CR_LOCK                                        ( COMP_CR_LOCK_Msk )

#define COMP_CR_CRV_CFG_Pos                                 ( 25U )
#define COMP_CR_CRV_CFG_Msk                                 ( 0xfUL << COMP_CR_CRV_CFG_Pos )
#define COMP_CR_CRV_CFG                                     ( COMP_CR_CRV_CFG_Msk )
#define COMP_CR_CRV_CFG_0                                   ( 0x1UL << COMP_CR_CRV_CFG_Pos )
#define COMP_CR_CRV_CFG_1                                   ( 0x2UL << COMP_CR_CRV_CFG_Pos )
#define COMP_CR_CRV_CFG_2                                   ( 0x4UL << COMP_CR_CRV_CFG_Pos )
#define COMP_CR_CRV_CFG_3                                   ( 0x8UL << COMP_CR_CRV_CFG_Pos )

#define COMP_CR_CRV_SEL_Pos                                 ( 24U )
#define COMP_CR_CRV_SEL_Msk                                 ( 0x1UL << COMP_CR_CRV_SEL_Pos )
#define COMP_CR_CRV_SEL                                     ( COMP_CR_CRV_SEL_Msk )

#define COMP_CR_CRV_EN_Pos                                  ( 23U )
#define COMP_CR_CRV_EN_Msk                                  ( 0x1UL << COMP_CR_CRV_EN_Pos )
#define COMP_CR_CRV_EN                                      ( COMP_CR_CRV_EN_Msk )

#define COMP_CR_POLARITY_Pos                                ( 20U )
#define COMP_CR_POLARITY_Msk                                ( 0x1UL << COMP_CR_POLARITY_Pos )
#define COMP_CR_POLARITY                                    ( COMP_CR_POLARITY_Msk )

#define COMP_CR_FLTEN_Pos                                   ( 19U )
#define COMP_CR_FLTEN_Msk                                   ( 0x1UL << COMP_CR_FLTEN_Pos )
#define COMP_CR_FLTEN                                       ( COMP_CR_FLTEN_Msk )

#define COMP_CR_FLTTIME_Pos                                 ( 16U )
#define COMP_CR_FLTTIME_Msk                                 ( 0x7UL << COMP_CR_FLTTIME_Pos )
#define COMP_CR_FLTTIME                                     ( COMP_CR_FLTTIME_Msk )
#define COMP_CR_FLTTIME_0                                   ( 0x1UL << COMP_CR_FLTTIME_Pos )
#define COMP_CR_FLTTIME_1                                   ( 0x2UL << COMP_CR_FLTTIME_Pos )
#define COMP_CR_FLTTIME_2                                   ( 0x4UL << COMP_CR_FLTTIME_Pos )

#define COMP_CR_BLANKSEL_Pos                                ( 12U )
#define COMP_CR_BLANKSEL_Msk                                ( 0x7UL << COMP_CR_BLANKSEL_Pos )
#define COMP_CR_BLANKSEL                                    ( COMP_CR_BLANKSEL_Msk )
#define COMP_CR_BLANKSEL_0                                  ( 0x1UL << COMP_CR_BLANKSEL_Pos )
#define COMP_CR_BLANKSEL_1                                  ( 0x2UL << COMP_CR_BLANKSEL_Pos )
#define COMP_CR_BLANKSEL_2                                  ( 0x4UL << COMP_CR_BLANKSEL_Pos )

#define COMP_CR_INPSEL_Pos                                  ( 8U )
#define COMP_CR_INPSEL_Msk                                  ( 0xfUL << COMP_CR_INPSEL_Pos )
#define COMP_CR_INPSEL                                      ( COMP_CR_INPSEL_Msk )
#define COMP_CR_INPSEL_0                                    ( 0x1UL << COMP_CR_INPSEL_Pos )
#define COMP_CR_INPSEL_1                                    ( 0x2UL << COMP_CR_INPSEL_Pos )
#define COMP_CR_INPSEL_2                                    ( 0x4UL << COMP_CR_INPSEL_Pos )
#define COMP_CR_INPSEL_3                                    ( 0x8UL << COMP_CR_INPSEL_Pos )

#define COMP_CR_INMSEL_Pos                                  ( 4U )
#define COMP_CR_INMSEL_Msk                                  ( 0xfUL << COMP_CR_INMSEL_Pos )
#define COMP_CR_INMSEL                                      ( COMP_CR_INMSEL_Msk )
#define COMP_CR_INMSEL_0                                    ( 0x1UL << COMP_CR_INMSEL_Pos )
#define COMP_CR_INMSEL_1                                    ( 0x2UL << COMP_CR_INMSEL_Pos )
#define COMP_CR_INMSEL_2                                    ( 0x4UL << COMP_CR_INMSEL_Pos )
#define COMP_CR_INMSEL_3                                    ( 0x8UL << COMP_CR_INMSEL_Pos )

#define COMP_CR_HYS_Pos                                     ( 1U )
#define COMP_CR_HYS_Msk                                     ( 0x7UL << COMP_CR_HYS_Pos )
#define COMP_CR_HYS                                         ( COMP_CR_HYS_Msk )
#define COMP_CR_HYS_0                                       ( 0x1UL << COMP_CR_HYS_Pos )
#define COMP_CR_HYS_1                                       ( 0x2UL << COMP_CR_HYS_Pos )
#define COMP_CR_HYS_2                                       ( 0x4UL << COMP_CR_HYS_Pos )

#define COMP_CR_EN_Pos                                      ( 0U )
#define COMP_CR_EN_Msk                                      ( 0x1UL << COMP_CR_EN_Pos )
#define COMP_CR_EN                                          ( COMP_CR_EN_Msk )


/***************  Bits definition for COMP_SR  **********************/

#define COMP_SR_VCOUT1_ORG_Pos                              ( 4U )
#define COMP_SR_VCOUT1_ORG_Msk                              ( 0x1UL << COMP_SR_VCOUT1_ORG_Pos )
#define COMP_SR_VCOUT1_ORG                                  ( COMP_SR_VCOUT1_ORG_Msk )

#define COMP_SR_VCOUT1_Pos                                  ( 0U )
#define COMP_SR_VCOUT1_Msk                                  ( 0x1UL << COMP_SR_VCOUT1_Pos )
#define COMP_SR_VCOUT1                                      ( COMP_SR_VCOUT1_Msk )

/***************  Bits definition for EFUSE_WP  **********************/

#define EFUSE_WP_WP_Pos                                     ( 0U )
#define EFUSE_WP_WP_Msk                                     ( 0xffffffffUL << EFUSE_WP_WP_Pos )
#define EFUSE_WP_WP                                         ( EFUSE_WP_WP_Msk )


/***************  Bits definition for EFUSE_CTRL  **********************/

#define EFUSE_CTRL_MODE_Pos                                 ( 4U )
#define EFUSE_CTRL_MODE_Msk                                 ( 0x1UL << EFUSE_CTRL_MODE_Pos )
#define EFUSE_CTRL_MODE                                     ( EFUSE_CTRL_MODE_Msk )

#define EFUSE_CTRL_TRIG_Pos                                 ( 0U )
#define EFUSE_CTRL_TRIG_Msk                                 ( 0x1UL << EFUSE_CTRL_TRIG_Pos )
#define EFUSE_CTRL_TRIG                                     ( EFUSE_CTRL_TRIG_Msk )


/***************  Bits definition for EFUSE_AR  **********************/

#define EFUSE_AR_ADDR_Pos                                   ( 0U )
#define EFUSE_AR_ADDR_Msk                                   ( 0x7ffUL << EFUSE_AR_ADDR_Pos )
#define EFUSE_AR_ADDR                                       ( EFUSE_AR_ADDR_Msk )


/***************  Bits definition for EFUSE_DWR  **********************/

#define EFUSE_DWR_WDATA_Pos                                 ( 0U )
#define EFUSE_DWR_WDATA_Msk                                 ( 0xffUL << EFUSE_DWR_WDATA_Pos )
#define EFUSE_DWR_WDATA                                     ( EFUSE_DWR_WDATA_Msk )
#define EFUSE_DWR_WDATA_0                                   ( 0x1UL << EFUSE_DWR_WDATA_Pos )
#define EFUSE_DWR_WDATA_1                                   ( 0x2UL << EFUSE_DWR_WDATA_Pos )
#define EFUSE_DWR_WDATA_2                                   ( 0x4UL << EFUSE_DWR_WDATA_Pos )
#define EFUSE_DWR_WDATA_3                                   ( 0x8UL << EFUSE_DWR_WDATA_Pos )
#define EFUSE_DWR_WDATA_4                                   ( 0x10UL << EFUSE_DWR_WDATA_Pos )
#define EFUSE_DWR_WDATA_5                                   ( 0x20UL << EFUSE_DWR_WDATA_Pos )
#define EFUSE_DWR_WDATA_6                                   ( 0x40UL << EFUSE_DWR_WDATA_Pos )
#define EFUSE_DWR_WDATA_7                                   ( 0x80UL << EFUSE_DWR_WDATA_Pos )


/***************  Bits definition for EFUSE_SR  **********************/

#define EFUSE_SR_PREREAD_DONE_Pos                           ( 31U )
#define EFUSE_SR_PREREAD_DONE_Msk                           ( 0x1UL << EFUSE_SR_PREREAD_DONE_Pos )
#define EFUSE_SR_PREREAD_DONE                               ( EFUSE_SR_PREREAD_DONE_Msk )

#define EFUSE_SR_UNPG_Pos                                   ( 1U )
#define EFUSE_SR_UNPG_Msk                                   ( 0x1UL << EFUSE_SR_UNPG_Pos )
#define EFUSE_SR_UNPG                                       ( EFUSE_SR_UNPG_Msk )

#define EFUSE_SR_DONE_Pos                                   ( 0U )
#define EFUSE_SR_DONE_Msk                                   ( 0x1UL << EFUSE_SR_DONE_Pos )
#define EFUSE_SR_DONE                                       ( EFUSE_SR_DONE_Msk )


/***************  Bits definition for EFUSE_CLR  **********************/

#define EFUSE_CLR_CUNPG_Pos                                 ( 1U )
#define EFUSE_CLR_CUNPG_Msk                                 ( 0x1UL << EFUSE_CLR_CUNPG_Pos )
#define EFUSE_CLR_CUNPG                                     ( EFUSE_CLR_CUNPG_Msk )

#define EFUSE_CLR_CDONE_Pos                                 ( 0U )
#define EFUSE_CLR_CDONE_Msk                                 ( 0x1UL << EFUSE_CLR_CDONE_Pos )
#define EFUSE_CLR_CDONE                                     ( EFUSE_CLR_CDONE_Msk )


/***************  Bits definition for EFUSE_DR  **********************/

#define EFUSE_DR_DATA_Pos                                   ( 0U )
#define EFUSE_DR_DATA_Msk                                   ( 0xffUL << EFUSE_DR_DATA_Pos )
#define EFUSE_DR_DATA                                       ( EFUSE_DR_DATA_Msk )
#define EFUSE_DR_DATA_0                                     ( 0x1UL << EFUSE_DR_DATA_Pos )
#define EFUSE_DR_DATA_1                                     ( 0x2UL << EFUSE_DR_DATA_Pos )
#define EFUSE_DR_DATA_2                                     ( 0x4UL << EFUSE_DR_DATA_Pos )
#define EFUSE_DR_DATA_3                                     ( 0x8UL << EFUSE_DR_DATA_Pos )
#define EFUSE_DR_DATA_4                                     ( 0x10UL << EFUSE_DR_DATA_Pos )
#define EFUSE_DR_DATA_5                                     ( 0x20UL << EFUSE_DR_DATA_Pos )
#define EFUSE_DR_DATA_6                                     ( 0x40UL << EFUSE_DR_DATA_Pos )
#define EFUSE_DR_DATA_7                                     ( 0x80UL << EFUSE_DR_DATA_Pos )


/***************  Bits definition for EFUSE_DSDP  **********************/

#define EFUSE_DSDP_DP_Pos                                   ( 0U )
#define EFUSE_DSDP_DP_Msk                                   ( 0xffffffffUL << EFUSE_DSDP_DP_Pos )
#define EFUSE_DSDP_DP                                       ( EFUSE_DSDP_DP_Msk )


/***************  Bits definition for EFUSE_BYTEWP  **********************/

#define EFUSE_BYTEWP_BYTEWP_Pos                             ( 0U )
#define EFUSE_BYTEWP_BYTEWP_Msk                             ( 0xffffffffUL << EFUSE_BYTEWP_BYTEWP_Pos )
#define EFUSE_BYTEWP_BYTEWP                                 ( EFUSE_BYTEWP_BYTEWP_Msk )


/***************  Bits definition for EFUSE_PGCFG  **********************/

#define EFUSE_PGCFG_AVDD_SP_Pos                             ( 24U )
#define EFUSE_PGCFG_AVDD_SP_Msk                             ( 0xffUL << EFUSE_PGCFG_AVDD_SP_Pos )
#define EFUSE_PGCFG_AVDD_SP                                 ( EFUSE_PGCFG_AVDD_SP_Msk )
#define EFUSE_PGCFG_AVDD_SP_0                               ( 0x1UL << EFUSE_PGCFG_AVDD_SP_Pos )
#define EFUSE_PGCFG_AVDD_SP_1                               ( 0x2UL << EFUSE_PGCFG_AVDD_SP_Pos )
#define EFUSE_PGCFG_AVDD_SP_2                               ( 0x4UL << EFUSE_PGCFG_AVDD_SP_Pos )
#define EFUSE_PGCFG_AVDD_SP_3                               ( 0x8UL << EFUSE_PGCFG_AVDD_SP_Pos )
#define EFUSE_PGCFG_AVDD_SP_4                               ( 0x10UL << EFUSE_PGCFG_AVDD_SP_Pos )
#define EFUSE_PGCFG_AVDD_SP_5                               ( 0x20UL << EFUSE_PGCFG_AVDD_SP_Pos )
#define EFUSE_PGCFG_AVDD_SP_6                               ( 0x40UL << EFUSE_PGCFG_AVDD_SP_Pos )
#define EFUSE_PGCFG_AVDD_SP_7                               ( 0x80UL << EFUSE_PGCFG_AVDD_SP_Pos )

#define EFUSE_PGCFG_AVDD_HD_Pos                             ( 16U )
#define EFUSE_PGCFG_AVDD_HD_Msk                             ( 0xffUL << EFUSE_PGCFG_AVDD_HD_Pos )
#define EFUSE_PGCFG_AVDD_HD                                 ( EFUSE_PGCFG_AVDD_HD_Msk )
#define EFUSE_PGCFG_AVDD_HD_0                               ( 0x1UL << EFUSE_PGCFG_AVDD_HD_Pos )
#define EFUSE_PGCFG_AVDD_HD_1                               ( 0x2UL << EFUSE_PGCFG_AVDD_HD_Pos )
#define EFUSE_PGCFG_AVDD_HD_2                               ( 0x4UL << EFUSE_PGCFG_AVDD_HD_Pos )
#define EFUSE_PGCFG_AVDD_HD_3                               ( 0x8UL << EFUSE_PGCFG_AVDD_HD_Pos )
#define EFUSE_PGCFG_AVDD_HD_4                               ( 0x10UL << EFUSE_PGCFG_AVDD_HD_Pos )
#define EFUSE_PGCFG_AVDD_HD_5                               ( 0x20UL << EFUSE_PGCFG_AVDD_HD_Pos )
#define EFUSE_PGCFG_AVDD_HD_6                               ( 0x40UL << EFUSE_PGCFG_AVDD_HD_Pos )
#define EFUSE_PGCFG_AVDD_HD_7                               ( 0x80UL << EFUSE_PGCFG_AVDD_HD_Pos )

#define EFUSE_PGCFG_PGWT_Pos                                ( 8U )
#define EFUSE_PGCFG_PGWT_Msk                                ( 0xffUL << EFUSE_PGCFG_PGWT_Pos )
#define EFUSE_PGCFG_PGWT                                    ( EFUSE_PGCFG_PGWT_Msk )
#define EFUSE_PGCFG_PGWT_0                                  ( 0x1UL << EFUSE_PGCFG_PGWT_Pos )
#define EFUSE_PGCFG_PGWT_1                                  ( 0x2UL << EFUSE_PGCFG_PGWT_Pos )
#define EFUSE_PGCFG_PGWT_2                                  ( 0x4UL << EFUSE_PGCFG_PGWT_Pos )
#define EFUSE_PGCFG_PGWT_3                                  ( 0x8UL << EFUSE_PGCFG_PGWT_Pos )
#define EFUSE_PGCFG_PGWT_4                                  ( 0x10UL << EFUSE_PGCFG_PGWT_Pos )
#define EFUSE_PGCFG_PGWT_5                                  ( 0x20UL << EFUSE_PGCFG_PGWT_Pos )
#define EFUSE_PGCFG_PGWT_6                                  ( 0x40UL << EFUSE_PGCFG_PGWT_Pos )
#define EFUSE_PGCFG_PGWT_7                                  ( 0x80UL << EFUSE_PGCFG_PGWT_Pos )

#define EFUSE_PGCFG_PGT_Pos                                 ( 0U )
#define EFUSE_PGCFG_PGT_Msk                                 ( 0xffUL << EFUSE_PGCFG_PGT_Pos )
#define EFUSE_PGCFG_PGT                                     ( EFUSE_PGCFG_PGT_Msk )
#define EFUSE_PGCFG_PGT_0                                   ( 0x1UL << EFUSE_PGCFG_PGT_Pos )
#define EFUSE_PGCFG_PGT_1                                   ( 0x2UL << EFUSE_PGCFG_PGT_Pos )
#define EFUSE_PGCFG_PGT_2                                   ( 0x4UL << EFUSE_PGCFG_PGT_Pos )
#define EFUSE_PGCFG_PGT_3                                   ( 0x8UL << EFUSE_PGCFG_PGT_Pos )
#define EFUSE_PGCFG_PGT_4                                   ( 0x10UL << EFUSE_PGCFG_PGT_Pos )
#define EFUSE_PGCFG_PGT_5                                   ( 0x20UL << EFUSE_PGCFG_PGT_Pos )
#define EFUSE_PGCFG_PGT_6                                   ( 0x40UL << EFUSE_PGCFG_PGT_Pos )
#define EFUSE_PGCFG_PGT_7                                   ( 0x80UL << EFUSE_PGCFG_PGT_Pos )


/***************  Bits definition for EFUSE_DSRx  **********************/

#define EFUSE_DSRX_DATA_Pos                                 ( 0U )
#define EFUSE_DSRX_DATA_Msk                                 ( 0xffUL << EFUSE_DSRX_DATA_Pos )
#define EFUSE_DSRX_DATA                                     ( EFUSE_DSRX_DATA_Msk )
#define EFUSE_DSRX_DATA_0                                   ( 0x1UL << EFUSE_DSRX_DATA_Pos )
#define EFUSE_DSRX_DATA_1                                   ( 0x2UL << EFUSE_DSRX_DATA_Pos )
#define EFUSE_DSRX_DATA_2                                   ( 0x4UL << EFUSE_DSRX_DATA_Pos )
#define EFUSE_DSRX_DATA_3                                   ( 0x8UL << EFUSE_DSRX_DATA_Pos )
#define EFUSE_DSRX_DATA_4                                   ( 0x10UL << EFUSE_DSRX_DATA_Pos )
#define EFUSE_DSRX_DATA_5                                   ( 0x20UL << EFUSE_DSRX_DATA_Pos )
#define EFUSE_DSRX_DATA_6                                   ( 0x40UL << EFUSE_DSRX_DATA_Pos )
#define EFUSE_DSRX_DATA_7                                   ( 0x80UL << EFUSE_DSRX_DATA_Pos )




/*******************  Bit definition for DLYB_CR register  ********************/

#define DLYB_CR_SEN_Pos                                     ( 1U )
#define DLYB_CR_SEN_Msk                                     ( 0x1UL << DLYB_CR_SEN_Pos )              
#define DLYB_CR_SEN                                         ( DLYB_CR_SEN_Msk )  

#define DLYB_CR_DEN_Pos                                     ( 0U )
#define DLYB_CR_DEN_Msk                                     ( 0x1UL << DLYB_CR_DEN_Pos )             
#define DLYB_CR_DEN                                         ( DLYB_CR_DEN_Msk ) 
                      
                       
/*******************  Bit definition for DLYB_CFGR register  ********************/
    
#define DLYB_CFGR_LENF_Pos                                  ( 31U)
#define DLYB_CFGR_LENF_Msk                                  ( 0x1UL << DLYB_CFGR_LENF_Pos )
#define DLYB_CFGR_LENF                                      ( DLYB_CFGR_LENF_Msk )

#define DLYB_CFGR_LEN_Pos                                   ( 16U )
#define DLYB_CFGR_LEN_Msk                                   ( 0xFFFUL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN                                       ( DLYB_CFGR_LEN_Msk )
#define DLYB_CFGR_LEN_0                                     ( 0x001UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_1                                     ( 0x002UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_2                                     ( 0x004UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_3                                     ( 0x008UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_4                                     ( 0x010UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_5                                     ( 0x020UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_6                                     ( 0x040UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_7                                     ( 0x080UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_8                                     ( 0x100UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_9                                     ( 0x200UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_10                                    ( 0x400UL << DLYB_CFGR_LEN_Pos )
#define DLYB_CFGR_LEN_11                                    ( 0x800UL << DLYB_CFGR_LEN_Pos )

#define DLYB_CFGR_UNIT_Pos                                  ( 8U )
#define DLYB_CFGR_UNIT_Msk                                  ( 0x7FUL << DLYB_CFGR_UNIT_Pos )        
#define DLYB_CFGR_UNIT                                      ( DLYB_CFGR_UNIT_Msk )                    
#define DLYB_CFGR_UNIT_0                                    ( 0x01UL << DLYB_CFGR_UNIT_Pos )         
#define DLYB_CFGR_UNIT_1                                    ( 0x02UL << DLYB_CFGR_UNIT_Pos )         
#define DLYB_CFGR_UNIT_2                                    ( 0x04UL << DLYB_CFGR_UNIT_Pos )          
#define DLYB_CFGR_UNIT_3                                    ( 0x08UL << DLYB_CFGR_UNIT_Pos )          
#define DLYB_CFGR_UNIT_4                                    ( 0x10UL << DLYB_CFGR_UNIT_Pos )          
#define DLYB_CFGR_UNIT_5                                    ( 0x20UL << DLYB_CFGR_UNIT_Pos )          
#define DLYB_CFGR_UNIT_6                                    ( 0x40UL << DLYB_CFGR_UNIT_Pos ) 

#define DLYB_CFGR_SEL_Pos                                   ( 0U )
#define DLYB_CFGR_SEL_Msk                                   ( 0xFUL << DLYB_CFGR_SEL_Pos )            
#define DLYB_CFGR_SEL                                       ( DLYB_CFGR_SEL_Msk )                       
#define DLYB_CFGR_SEL_0                                     ( 0x1UL << DLYB_CFGR_SEL_Pos )           
#define DLYB_CFGR_SEL_1                                     ( 0x2UL << DLYB_CFGR_SEL_Pos )           
#define DLYB_CFGR_SEL_2                                     ( 0x3UL << DLYB_CFGR_SEL_Pos )           
#define DLYB_CFGR_SEL_3                                     ( 0x8UL << DLYB_CFGR_SEL_Pos )    

///*-----------  Peripheral_Registers_Bits_Definition END  -----------------*/

#if (USE_RTOS == 1U)
  #error "USE_RTOS should be 0 in the current HAL release"
#else
  #define __HAL_LOCK(__HANDLE__)                                           \
                                do{                                        \
                                    if((__HANDLE__)->Lock == HAL_LOCKED)   \
                                    {                                      \
                                       return HAL_BUSY;                    \
                                    }                                      \
                                    else                                   \
                                    {                                      \
                                       (__HANDLE__)->Lock = HAL_LOCKED;    \
                                    }                                      \
                                  }while (0U)
  #define __HAL_UNLOCK(__HANDLE__)                                          \
                                  do{                                       \
                                      (__HANDLE__)->Lock = HAL_UNLOCKED;    \
                                    }while (0U)
#endif /* USE_RTOS */  


typedef unsigned           char UINT8;
typedef unsigned short     int  UINT16;
typedef unsigned           int  UINT32;  


#define SET_BIT(REG, BIT)      ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)    ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)     ((REG) & (BIT))
#define CLEAR_REG(REG)         ((REG) = (0x0))
#define WRITE_REG(REG, VAL)    ((REG) = (VAL))
#define READ_REG(REG)          ((REG))
#define MODIFY_REG(REG,MASK,BITS) ((REG) = (((REG)&(~(MASK)))|((BITS)&(MASK))))
#define POSITION_VAL(VAL)      (__CLZ(__RBIT(VAL)))


#endif  /* __ACM32H5XX_H__ */
