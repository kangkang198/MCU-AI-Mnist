/******************************************************************************
*@file  : acm32h5xx_hal_conf.c
*@brief : HAL configuration file
******************************************************************************/

#ifndef __ACM32H5XX_HAL_CONF_H
#define __ACM32H5XX_HAL_CONF_H

#include "hal_def.h"
#include "acm32h5xx.h"
#include "hal.h"

/******* enable printf in debug stage ****************************************/
#define DEBUG

#ifdef DEBUG
    #define printfS      printf
#else
    #define printfS(fmt, ...)         
#endif

/******* enable assert in debug stage ****************************************/
// #define USE_FULL_ASSERT

#ifdef USE_FULL_ASSERT
  void assert_failed(uint8_t* file, uint32_t line);
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
#else
  #define assert_param(expr) ((void)0U)
#endif

/******* config data if or not in extern sram *******************************/  
#define PSRAM_SECTION __attribute__((section (".psram")))

#define DATA_IN_ExtSRAM

/* Configure the Vector Table location add offset address ------------------*/
  
//#define VECT_TAB_IROM
//#define VECT_TAB_SRAM
#define VECT_TAB_SPI_FLASH
  
#define VECT_TAB_OFFSET         ( 0 )
  
#ifdef  VECT_TAB_IROM
  #define VECT_TAB_ADDR     ( 0 + VECT_TAB_OFFSET )
#elif defined ( VECT_TAB_SRAM )
  #define VECT_TAB_ADDR     ( SRAM1_BASE_ADDR + 0x00002000 + VECT_TAB_OFFSET )
#elif defined ( VECT_TAB_SPI_FLASH )
  #define VECT_TAB_ADDR     ( SPI7_MEM_BASE_ADDR + 0x00002000 + VECT_TAB_OFFSET )
#else
  #warning vector table definition error.
#endif

/******* config extern high speed osc freq and low osc freq in Hz ************/
#define XTH_VALUE                   ( 12000000U )
#define XTL_VALUE                   ( 32768U )


/******* SysTick interrupt priority  *****************************************/
#define TICK_INT_PRIORITY           ((1<<__NVIC_PRIO_BITS)-1)  

/******* SysTick ms period set ,1ms or 10ms **********************************/
#define TICK_PERIOD_1MS             (1U)
#define TICK_PERIOD_10MS            (10U)
#define TICK_PERIOD_MS              (TICK_PERIOD_1MS)  


/******* instruction and data accelerate enable ******************************/
#define INS_ACCELERATE_ENABLE       (1U)    //instruction accelerate enable 
#define DATA_ACCELERATE_ENABLE      (1U)    //data accelerate enable

/******* module selection ****************************************************/

#define HAL_CORTEX_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_DWT_MODULE_ENABLED 
#define HAL_WDT_MODULE_ENABLED 
#define HAL_IWDT_MODULE_ENABLED
#define HAL_PMU_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED
//#define HAL_TIMER_MODULE_ENABLED
//#define HAL_LPTIM_MODULE_ENABLED    
//#define HAL_FSUSB_MODULE_ENABLED
//#define HAL_PUF_MODULE_ENABLED 
//#define HAL_CDE_MODULE_ENABLED 
//#define HAL_NORFLASH_MODULE_ENABLED
//#define HAL_CRC_MODULE_ENABLED 
//#define HAL_DIVIDER_MODULE_ENABLED 
//#define HAL_AES_MODULE_ENABLED  
//#define HAL_HRNG_MODULE_ENABLED  
//#define HAL_ECC_MODULE_ENABLED 
//#define HAL_RSA_MODULE_ENABLED 
//#define HAL_DRBG_MODULE_ENABLED  
//#define HAL_ECDSA_MODULE_ENABLED
//#define HAL_HASH_SHA1_MODULE_ENABLED
//#define HAL_HASH_SHA256_MODULE_ENABLED
//#define HAL_HASH_SHA384_MODULE_ENABLED
//#define HAL_HMAC_MODULE_ENABLED
//#define HAL_FMC_MODULE_ENABLED
//#define HAL_LPTIM_MODULE_ENABLED
//#define HAL_RTC_MODULE_ENABLED
#define HAL_EFUSE_MODULE_ENABLED
#define HAL_LTDC_MODULE_ENABLED
#define HAL_OSPI_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED
/******* include modules header file *****************************************/

    
#if ((INS_ACCELERATE_ENABLE==1) ||  (DATA_ACCELERATE_ENABLE==1))
    #include "system_accelerate.h"
#endif
    
#ifdef HAL_CORTEX_MODULE_ENABLED
    #include "hal_cortex.h"
#endif

#ifdef HAL_RCC_MODULE_ENABLED
    #include "hal_rcc.h"
#endif

#ifdef HAL_GPIO_MODULE_ENABLED
    #include "hal_gpio.h"
#endif

#ifdef HAL_EXTI_MODULE_ENABLED
    #include "hal_exti.h"
#endif

#ifdef HAL_DMA_MODULE_ENABLED
    #include "hal_dma.h"
#endif

#ifdef HAL_DWT_MODULE_ENABLED
    #include "hal_dwt.h"
#endif

#ifdef HAL_WDT_MODULE_ENABLED
    #include "hal_wdt.h"
#endif

#ifdef HAL_IWDT_MODULE_ENABLED
    #include "hal_iwdt.h"
#endif

#ifdef HAL_PMU_MODULE_ENABLED
	#include "hal_pmu.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED
    #include "hal_usart.h"
    #include "hal_uart.h"
    #include "hal_uart_ex.h"
#endif

#ifdef HAL_SPI_MODULE_ENABLED
    #include "hal_spi.h"
#endif

#ifdef HAL_TIMER_MODULE_ENABLED
    #include "hal_timer.h"  
    #include "hal_timer_ex.h"
#endif

#ifdef HAL_LPTIM_MODULE_ENABLED        
    #include "hal_lptim.h"                            
#endif

#ifdef HAL_FSUSB_MODULE_ENABLED
    #include "hal_fsusb.h"
#endif

#ifdef HAL_PUF_MODULE_ENABLED            
    #include "hal_puf.h"                            
#endif

#ifdef HAL_CDE_MODULE_ENABLED
    #include "hal_cde.h"
#endif

#ifdef HAL_NORFLASH_MODULE_ENABLED
    #include "hal_norflash.h"
#endif

#ifdef HAL_CRC_MODULE_ENABLED  
    #include  "hal_crc.h"
#endif

#ifdef HAL_DIVIDER_MODULE_ENABLED  
    #include  "hal_divider.h"
#endif

#ifdef  HAL_AES_MODULE_ENABLED
    #include  "hal_aes.h"  
#endif

#ifdef HAL_HRNG_MODULE_ENABLED     
    #include "hal_hrng.h"    
#endif

#ifdef HAL_ECC_MODULE_ENABLED        
    #include "hal_ecc.h"
    #include "hal_binary_ecc.h"   
#endif

#ifdef HAL_RSA_MODULE_ENABLED    
    #include "hal_rsa_keygen.h"
#endif         

#ifdef HAL_DRBG_MODULE_ENABLED        
    #include "hal_ctr_drbg.h" 
#endif 

#ifdef HAL_ECDSA_MODULE_ENABLED  
    #include "hal_ecdsa.h"
#endif

#ifdef HAL_HASH_SHA1_MODULE_ENABLED 
    #include "hal_sha1.h"  
#endif  

#ifdef HAL_HASH_SHA256_MODULE_ENABLED 
    #include "hal_sha224_256.h"
#endif  

#ifdef HAL_HASH_SHA384_MODULE_ENABLED 
    #include "hal_sha384_512.h"  
#endif  

#ifdef HAL_HMAC_MODULE_ENABLED
    #include "hal_hmac.h"
#endif   

#ifdef HAL_FMC_MODULE_ENABLED
    #include "hal_fmc.h"
#endif

#ifdef HAL_LPTIM_MODULE_ENABLED
    #include "hal_lptim.h"
#endif

#ifdef HAL_RTC_MODULE_ENABLED
    #include "hal_rtc.h"
#endif

#ifdef HAL_EFUSE_MODULE_ENABLED
    #include "hal_efuse.h"
#endif

#ifdef HAL_LTDC_MODULE_ENABLED
    #include "hal_ltdc.h"
#endif

#ifdef HAL_OSPI_MODULE_ENABLED
    #include "hal_ospi.h"
#endif

#ifdef HAL_I2C_MODULE_ENABLED
    #include "hal_i2c.h"
#endif

#endif /* __ACM32H5XX_HAL_CONF_H  */

  