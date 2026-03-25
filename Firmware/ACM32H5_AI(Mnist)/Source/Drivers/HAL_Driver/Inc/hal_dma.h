/******************************************************************************
*@file  : hal_dma.h
*@brief : Header file of DMA HAL module.
******************************************************************************/

#ifndef __HAL_DMA_H__
#define __HAL_DMA_H__

#include "hal.h"


/**
  * @brief  DMA Configuration Structure definition
  */
  
typedef struct 
{
    uint32_t Mode;              /*!< Specifies the operation mode of the DMA.
                                     This parameter can be a value of @ref DMA_Mode
                                     @note The circular buffer mode cannot be used if the memory-to-memory
                                           data transfer is configured on the selected channel                          */
    uint32_t Lock;

    uint32_t DataFlow;          /*!< Specifies if the data will be transferred from memory to peripheral,
                                     from memory to memory or from peripheral to memory.
                                     This parameter can be a value of @ref DMA_DataFlow                                 */

    uint32_t ReqID;             /*!< The request number of the source peripheral and the destination peripheral. 
                                     This value is invalid when the memory to memory data transfer is configured 
                                     on the selected channel. 
                                     This parameter can be a value of @ref DMA1_ReqID or DMA2_ReqID                     */
    
    uint32_t SrcIncDec;         /*!< Specifies whether the source address register should be incremented or not.
                                     This parameter can be a value of @ref DMA_SrcIncDec                                */

    uint32_t DestIncDec;        /*!< Specifies whether the destination address register should be incremented or not.
                                     This parameter can be a value of @ref DMA_DestIncDec                               */
    
    uint32_t SrcWidth;          /*!< Specifies whether the source data width.
                                     This parameter can be a value of @ref DMA_SrcWidth                                 */

    uint32_t DestWidth;         /*!< Specifies whether the destination data width.
                                     This parameter can be a value of @ref DMA_DestWidth                                */

    uint32_t SrcBurst;          /*!< Specifies the Burst transfer configuration for the source transfers.
                                     It specifies the amount of data to be transferred in a single non interruptible
                                     transaction. This parameter can be a value of @ref DMA_SrcBurst.                   */
                                     
    uint32_t DestBurst;         /*!< Specifies the Burst transfer configuration for the destination transfers.
                                     It specifies the amount of data to be transferred in a single non interruptible
                                     transaction. This parameter can be a value of @ref DMA_DestBurst.                  */
    
    uint32_t SrcMaster;         /*!< Specifies the source master.
                                     This parameter can be a value of @ref DMA_SrcMaster                                */

    uint32_t DestMaster;        /*!< Specifies the destination master.
                                     This parameter can be a value of @ref DMA_DestMaster                               */
    
    uint32_t NextMaster;        /*!< Specifies the next master.Valid only in Circular mode.
                                     This parameter can be a value of @ref DMA_NextMaster                                */
                                     
}DMA_InitTypeDef;

/**
  * @brief  DMA Link List Item Structure
  */

typedef struct __DMA_NextLink
{
    uint32_t    SrcAddr;        /*!< source address                 */

    uint32_t    DestAddr;       /*!< desination address             */
    
    uint32_t    Next;           /*!< Next Node pointer              */

    uint32_t    Ctrl;           /*!< Ctrol                          */
    
}DMA_LinkTypeDef;

/**
  * @brief  DMA handle Structure definition
  */
typedef struct __DMA_HandleTypeDef
{
    DMA_Channel_TypeDef *Instance;                                      /*!< Register base address              */

    DMA_InitTypeDef Init;                                               /*!< DMA communication parameters       */

    void *Parent;                                                       /*!< Parent object state                */
	
    void (*XferCpltCallback)(struct __DMA_HandleTypeDef * hdma);        /*!< DMA transfer complete callback     */
    
    void (*XferHalfCpltCallback)(struct __DMA_HandleTypeDef * hdma);    /* DMA transfer half complete callback  */
    
    void (*XferErrorCallback)(struct __DMA_HandleTypeDef * hdma);        /* DMA transfer error callback          */
    
    void (*XferAbortCallback)(struct __DMA_HandleTypeDef * hdma);        /* DMA transfer abort callback          */
    
    DMA_TypeDef *DMA;                                                   /*!< DMA channel Base Address           */
    
    uint32_t Channel;                                                   /*!< DMA channel                        */ 
                               
    DMA_LinkTypeDef Link;                                               /*!< DMA Link                           */ 
    
}DMA_HandleTypeDef;

/**
  * @brief  DMA Link Init Structure
  */

typedef struct __DMA_LinkInitTypeDef
{
    uint32_t SrcAddr;           /* source address                                                                       */

    uint32_t DestAddr;          /* desination address                                                                   */

    uint32_t TransferSize;      /* The length of data to be transferred from source to destination.                     */
    
    uint32_t Next;              /* Next Node pointer                                                                    */

    uint32_t NextMaster;        /*!< Specifies the next master.Valid only if LLI is valid.
                                     This parameter can be a value of @ref DMA_NextMaster                                */
                                     
    uint32_t RawInt ;           /*!< Raw interrupt enable.
                                     This parameter can be a value of @ref DMA_RawInt                                   */

    uint32_t SrcIncDec;         /*!< Specifies whether the source address register should be incremented or not.
                                     This parameter can be a value of @ref DMA_SrcIncDec                                */

    uint32_t DestIncDec;        /*!< Specifies whether the destination address register should be incremented or not.
                                     This parameter can be a value of @ref DMA_DestIncDec                               */
    
    uint32_t SrcWidth;          /*!< Specifies whether the source data width.
                                     This parameter can be a value of @ref DMA_SrcWidth                                 */

    uint32_t DestWidth;         /*!< Specifies whether the destination data width.
                                     This parameter can be a value of @ref DMA_DestWidth                                */

    uint32_t SrcBurst;          /*!< Specifies the Burst transfer configuration for the source transfers.
                                     It specifies the amount of data to be transferred in a single non interruptible
                                     transaction. This parameter can be a value of @ref DMA_SrcBurst.                   */
                                     
    uint32_t DestBurst;         /*!< Specifies the Burst transfer configuration for the destination transfers.
                                     It specifies the amount of data to be transferred in a single non interruptible
                                     transaction. This parameter can be a value of @ref DMA_DestBurst.                  */

}DMA_LinkInitTypeDef;




/** @defgroup DMA_RawInt
 *  @{
 */
 
#define DMA_RAWINT_DISABLE                      ( 0U )
#define DMA_RAWINT_ENABLE                       ( DMA_CXCTRL_RITEN )
/**
  * @}
  */

/** @defgroup DMA_SrcInc
 *  @{
 */
 
#define DMA_SRCINCDEC_DISABLE                   ( 0U )
#define DMA_SRCINCDEC_INC                       ( DMA_CXCTRL_SIORSD_0 )
#define DMA_SRCINCDEC_DEC                       ( DMA_CXCTRL_SIORSD_1 )
#define DMA_SRCINCDEC_DISABLE_1                 ( DMA_CXCTRL_SIORSD_1 | DMA_CXCTRL_SIORSD_0 )
/**
  * @}
  */


/** @defgroup DMA_DestInc
 *  @{
 */
 
#define DMA_DESTINCDEC_DISABLE                  ( 0U )
#define DMA_DESTINCDEC_INC                      ( DMA_CXCTRL_DIORDD_0 )
#define DMA_DESTINCDEC_DEC                      ( DMA_CXCTRL_DIORDD_1 )
#define DMA_DESTINCDEC_DISABLE_1                ( DMA_CXCTRL_DIORDD_1 | DMA_CXCTRL_DIORDD_0 )

/**
  * @}
  */

/** @defgroup DMA_SrcWidth
 *  @{
 */
#define DMA_SRCWIDTH_BYTE                       ( 0U )                          /*  8bit */
#define DMA_SRCWIDTH_HALFWORD                   ( DMA_CXCTRL_SWIDTH_0 )         /* 16bit */
#define DMA_SRCWIDTH_WORD                       ( DMA_CXCTRL_SWIDTH_1 )         /* 32bit */
/**
  * @}
  */

/** @defgroup DMA_DestWidth
 *  @{
 */
#define DMA_DESTWIDTH_BYTE                      ( 0U )                             /*  8bit */
#define DMA_DESTWIDTH_HALFWORD                  ( DMA_CXCTRL_DWIDTH_0 )            /* 16bit */
#define DMA_DESTWIDTH_WORD                      ( DMA_CXCTRL_DWIDTH_1 )            /* 32bit */

/**
  * @}
  */
  
 /** @defgroup DMA_Mode
 *  @{
 */
#define DMA_MODE_NORMAL                         ( 0U )                          /*!< Normal mode    */
#define DMA_MODE_CIRCULAR                       ( 1U )                          /*!< Circular mode  */

/**
  * @}
  */

/**
  * @brief  DMA_SrcBurst
  */
  
#define DMA_SRCBURST_1                          ( 0U )
#define DMA_SRCBURST_4                          ( DMA_CXCTRL_SBSIZE_0 )
#define DMA_SRCBURST_8                          ( DMA_CXCTRL_SBSIZE_1 )
#define DMA_SRCBURST_16                         ( DMA_CXCTRL_SBSIZE_1 | DMA_CXCTRL_SBSIZE_0 )
#define DMA_SRCBURST_32                         ( DMA_CXCTRL_SBSIZE_2 )
#define DMA_SRCBURST_64                         ( DMA_CXCTRL_SBSIZE_2 | DMA_CXCTRL_SBSIZE_0 )
#define DMA_SRCBURST_128                        ( DMA_CXCTRL_SBSIZE_2 | DMA_CXCTRL_SBSIZE_1 )
#define DMA_SRCBURST_256                        ( DMA_CXCTRL_SBSIZE_2 | DMA_CXCTRL_SBSIZE_1 | DMA_CXCTRL_SBSIZE_0 )

/**
  * @}
  */

/**
  * @brief  DMA_DestBurst
  */
  
#define DMA_DESTBURST_1                         ( 0U )
#define DMA_DESTBURST_4                         ( DMA_CXCTRL_DBSIZE_0 )
#define DMA_DESTBURST_8                         ( DMA_CXCTRL_DBSIZE_1 )
#define DMA_DESTBURST_16                        ( DMA_CXCTRL_DBSIZE_1 | DMA_CXCTRL_DBSIZE_0 )
#define DMA_DESTBURST_32                        ( DMA_CXCTRL_DBSIZE_2 )
#define DMA_DESTBURST_64                        ( DMA_CXCTRL_DBSIZE_2 | DMA_CXCTRL_DBSIZE_0 )
#define DMA_DESTBURST_128                       ( DMA_CXCTRL_DBSIZE_2 | DMA_CXCTRL_DBSIZE_1 )
#define DMA_DESTBURST_256                       ( DMA_CXCTRL_DBSIZE_2 | DMA_CXCTRL_DBSIZE_1 | DMA_CXCTRL_DBSIZE_0 )

/**
  * @}
  */

/**
  * @brief  DMA_SrcMaster
  */
  
#define DMA_SRCMASTER_1                         ( 0U )
#define DMA_SRCMASTER_2                         ( DMA_CXCONFIG_S )

/**
  * @}
  */

/**
  * @brief  DMA_DestMaster
  */
  
#define DMA_DESTMASTER_1                        ( 0U )
#define DMA_DESTMASTER_2                        ( DMA_CXCONFIG_D )

/**
  * @}
  */

/**
  * @brief  DMA_Master1Endian
  */
  
#define DMA_MASTER1_ENDIAN_LITTLE               ( 0U )
#define DMA_MASTER1_ENDIAN_BIG                  ( DMA_CONFIG_M1ENDIAN )

/**
  * @}
  */

/**
  * @brief  DMA_Master2Endian
  */
  
#define DMA_MASTER2_ENDIAN_LITTLE               ( 0U )
#define DMA_MASTER2_ENDIAN_BIG                  ( DMA_CONFIG_M2ENDIAN )

/**
  * @}
  */

/**
  * @brief  DMA_NextMaster
  */
  
#define DMA_NEXTMASTER_1                        ( 0U )
#define DMA_NEXTMASTER_2                        ( DMA_CXLLI_LM )

/**
  * @}
  */

/**
  * @brief  DMA transfer max number
  */

#define DMA_TRANSFER_SIZE                       ( 0xFFFFU )


/** @defgroup DMA_DataFlow
 *  @{
 */
 
#define DMA_DATAFLOW_M2M                        ( 0U )
#define DMA_DATAFLOW_M2P                        ( DMA_CXCONFIG_FLOWCTRL_0 )
#define DMA_DATAFLOW_P2M                        ( DMA_CXCONFIG_FLOWCTRL_1 )

/**
  * @}
  */


/** @defgroup DMA1_ReqID
 *  @{
 */
 
#define DMA1_REQ_M2M                           ( 0U )
#define DMA1_REQ_ADC1                          ( 0U )
#define DMA1_REQ_SPI1_TX                       ( 1U )
#define DMA1_REQ_SPI1_RX                       ( 2U )
#define DMA1_REQ_SPI2_TX                       ( 3U )
#define DMA1_REQ_SPI2_RX                       ( 4U )
#define DMA1_REQ_USART1_TX                     ( 5U )
#define DMA1_REQ_USART1_RX                     ( 6U )
#define DMA1_REQ_USART2_TX                     ( 7U )
#define DMA1_REQ_USART2_RX                     ( 8U )
#define DMA1_REQ_I2C1_TX                       ( 9U )
#define DMA1_REQ_I2C1_RX                       ( 10U )
#define DMA1_REQ_I2C2_TX                       ( 11U )
#define DMA1_REQ_I2C2_RX                       ( 12U )
#define DMA1_REQ_TIM1_CH1                      ( 13U )
#define DMA1_REQ_TIM1_CH2                      ( 14U )
#define DMA1_REQ_TIM1_CH3                      ( 15U )
#define DMA1_REQ_TIM1_CH4                      ( 16U )
#define DMA1_REQ_TIM1_UP                       ( 17U )
#define DMA1_REQ_TIM1_TRIG                     ( 18U )
#define DMA1_REQ_TIM1_COM                      ( 19U )
#define DMA1_REQ_TIM2_CH1                      ( 20U )
#define DMA1_REQ_TIM2_CH2                      ( 21U )
#define DMA1_REQ_TIM2_CH3                      ( 22U )
#define DMA1_REQ_TIM2_CH4                      ( 23U )
#define DMA1_REQ_TIM2_UP                       ( 24U )
#define DMA1_REQ_TIM2_TRIG                     ( 25U )
#define DMA1_REQ_ADC2                          ( 26U )
#define DMA1_REQ_ADC3                          ( 27U )
#define DMA1_REQ_USART3_TX                     ( 28U )
#define DMA1_REQ_USART3_RX                     ( 29U )
#define DMA1_REQ_LPUART_TX                     ( 30U )
#define DMA1_REQ_LPUART_RX                     ( 31U )
#define DMA1_REQ_TIM15_CH1                     ( 32U )
#define DMA1_REQ_TIM15_CH2                     ( 33U )
#define DMA1_REQ_TIM15_UP                      ( 34U )
#define DMA1_REQ_TIM15_TRIG                    ( 35U )
#define DMA1_REQ_TIM15_COM                     ( 36U )
#define DMA1_REQ_I2S1_TX                       ( 37U )
#define DMA1_REQ_I2S1_RX                       ( 38U )
#define DMA1_REQ_DAC1_CH1                      ( 39U )
#define DMA1_REQ_DAC1_CH2                      ( 40U )
#define DMA1_REQ_I2S2_TX                       ( 41U )
#define DMA1_REQ_I2S2_RX                       ( 42U )
#define DMA1_REQ_I2S3_TX                       ( 43U )
#define DMA1_REQ_I2S3_RX                       ( 44U )
#define DMA1_REQ_USART4_TX                     ( 45U )
#define DMA1_REQ_USART4_RX                     ( 46U )
#define DMA1_REQ_SPI3_TX                       ( 47U )
#define DMA1_REQ_SPI3_RX                       ( 48U )
#define DMA1_REQ_TIM4_CH1                      ( 49U )
#define DMA1_REQ_TIM4_CH2                      ( 50U )
#define DMA1_REQ_TIM4_CH3                      ( 51U )
#define DMA1_REQ_TIM4_CH4                      ( 52U )
#define DMA1_REQ_TIM4_UP                       ( 53U )
#define DMA1_REQ_TIM4_TRIG                     ( 54U )
#define DMA1_REQ_NDL                           ( 55U )
#define DMA1_REQ_STM1_PWM                      ( 56U )
#define DMA1_REQ_STM2_PWM                      ( 57U )
#define DMA1_REQ_DCMI                          ( 58U )
#define DMA1_REQ_SPI7_RX                       ( 59U )
#define DMA1_REQ_SPI7_TX                       ( 60U )
#define DMA1_REQ_SPI8_RX                       ( 61U )
#define DMA1_REQ_SPI8_TX                       ( 62U )
#define DMA1_REQ_STM3_PWM                      ( 63U )
#define DMA1_REQ_STM4_PWM                      ( 64U )
#define DMA1_REQ_STM5_PWM                      ( 65U )
#define DMA1_REQ_STM6_PWM                      ( 66U )
#define DMA1_REQ_LPT                           ( 67U )
#define DMA1_REQ_TIM5_UP                       ( 68U )
#define DMA1_REQ_TIM5_CH1                      ( 69U )
#define DMA1_REQ_TIM5_CH2                      ( 70U )
#define DMA1_REQ_TIM5_CH3                      ( 71U )
#define DMA1_REQ_TIM5_CH4                      ( 72U )    
#define DMA1_REQ_TIM5_TRIG                     ( 73U ) 
#define DMA1_REQ_TIM5_COM                      ( 74U )    
#define DMA1_REQ_TIM25_UP                      ( 75U ) 
#define DMA1_REQ_TIM25_CH1                     ( 76U )    
#define DMA1_REQ_TIM25_CH2                     ( 77U )  
#define DMA1_REQ_TIM25_TRIG                    ( 78U ) 
#define DMA1_REQ_TIM25_COM                     ( 79U )    
#define DMA1_REQ_TIM20_UP                      ( 80U )   
#define DMA1_REQ_TIM20_CH1                     ( 81U )   
#define DMA1_REQ_TIM20_CH2                     ( 82U )  
#define DMA1_REQ_TIM20_CH3                     ( 83U )   
#define DMA1_REQ_TIM20_CH4                     ( 84U )      
#define DMA1_REQ_TIM20_CH5                     ( 85U )      
#define DMA1_REQ_TIM20_CH6                     ( 86U )   
#define DMA1_REQ_TIM20_TRIG                    ( 87U ) 
#define DMA1_REQ_TIM20_COM                     ( 88U )   
#define DMA1_REQ_TIM18_UP                      ( 89U )   
#define DMA1_REQ_TIM18_CH1                     ( 90U )   
#define DMA1_REQ_TIM18_TRIG                    ( 91U )   
#define DMA1_REQ_TIM18_COM                     ( 92U )  
#define DMA1_REQ_TIM19_UP                      ( 93U )     
#define DMA1_REQ_TIM19_CH1                     ( 94U )     
#define DMA1_REQ_TIM19_TRIG                    ( 95U )     
#define DMA1_REQ_TIM19_COM                     ( 96U )  
#define DMA1_REQ_TIM21_UP                      ( 97U )     
#define DMA1_REQ_TIM22_UP                      ( 98U )    
#define DMA1_REQ_TIM23_UP                      ( 99U )   
#define DMA1_REQ_TIM23_CH1                     ( 100U )   
#define DMA1_REQ_TIM23_CH2                     ( 101U )  
#define DMA1_REQ_TIM23_CH3                     ( 102U )  
#define DMA1_REQ_TIM23_CH4                     ( 103U )  
#define DMA1_REQ_TIM23_TRIG                    ( 104U ) 
#define DMA1_REQ_TIM23_COM                     ( 105U )    
#define DMA1_REQ_TIM24_UP                      ( 106U )    
#define DMA1_REQ_TIM24_CH1                     ( 107U )   
#define DMA1_REQ_TIM24_CH2                     ( 108U )  
#define DMA1_REQ_TIM24_CH3                     ( 109U )  
#define DMA1_REQ_TIM24_CH4                     ( 110U )    
#define DMA1_REQ_TIM24_TRIG                    ( 111U ) 
#define DMA1_REQ_TIM24_COM                     ( 112U ) 
#define DMA1_REQ_SPI4_RX                       ( 113U )
#define DMA1_REQ_SPI4_TX                       ( 114U )
#define DMA1_REQ_SPI5_RX                       ( 115U )
#define DMA1_REQ_SPI5_TX                       ( 116U )
#define DMA1_REQ_DAC2_CH1                      ( 117U )
#define DMA1_REQ_DAC2_CH2                      ( 118U )
#define DMA1_REQ_OSPI1_RX                      ( 119U )
#define DMA1_REQ_OSPI1_TX                      ( 120U )
#define DMA1_REQ_OSPI2_RX                      ( 121U )
#define DMA1_REQ_OSPI2_TX                      ( 122U )
#define DMA1_REQ_I2C3_TX                       ( 123U )
#define DMA1_REQ_I2C3_RX                       ( 124U )
#define DMA1_REQ_I2C4_TX                       ( 125U )
#define DMA1_REQ_I2C4_RX                       ( 126U )
#define DMA1_REQ_USART5_TX                     ( 127U )
#define DMA1_REQ_USART5_RX                     ( 128U )
#define DMA1_REQ_USART6_TX                     ( 129U )
#define DMA1_REQ_USART6_RX                     ( 130U )
#define DMA1_REQ_USART7_TX                     ( 131U )
#define DMA1_REQ_USART7_RX                     ( 132U )
#define DMA1_REQ_USART8_TX                     ( 133U )
#define DMA1_REQ_USART8_RX                     ( 134U )
#define DMA1_REQ_USART9_TX                     ( 135U )
#define DMA1_REQ_USART9_RX                     ( 136U )
#define DMA1_REQ_USART10_TX                    ( 137U )
#define DMA1_REQ_USART10_RX                    ( 138U )
#define DMA1_REQ_FDCAN1_TX                     ( 139U )
#define DMA1_REQ_FDCAN1_RX                     ( 140U )
#define DMA1_REQ_FDCAN2_TX                     ( 141U )
#define DMA1_REQ_FDCAN2_RX                     ( 142U )
#define DMA1_REQ_FDCAN3_TX                     ( 143U )
#define DMA1_REQ_FDCAN3_RX                     ( 144U )
#define DMA1_REQ_SPI6_RX                       ( 145U )
#define DMA1_REQ_SPI6_TX                       ( 146U )
#define DMA1_REQ_MAX                           ( 147U )

/**
  * @}
  */
  
/** @defgroup DMA2_ReqID
 *  @{
 */
 
#define DMA2_REQ_M2M                           ( 0U )
#define DMA2_REQ_ADC1                          ( 0U )
#define DMA2_REQ_SPI1_TX                       ( 1U )
#define DMA2_REQ_SPI1_RX                       ( 2U )
#define DMA2_REQ_SPI2_TX                       ( 3U )
#define DMA2_REQ_SPI2_RX                       ( 4U )
#define DMA2_REQ_USART1_TX                     ( 5U )
#define DMA2_REQ_USART1_RX                     ( 6U )
#define DMA2_REQ_USART2_TX                     ( 7U )
#define DMA2_REQ_USART2_RX                     ( 8U )
#define DMA2_REQ_I2C1_TX                       ( 9U )
#define DMA2_REQ_I2C1_RX                       ( 10U )
#define DMA2_REQ_I2C2_TX                       ( 11U )
#define DMA2_REQ_I2C2_RX                       ( 12U )
#define DMA2_REQ_TIM8_CH1                      ( 13U )
#define DMA2_REQ_TIM8_CH2                      ( 14U )
#define DMA2_REQ_TIM8_CH3                      ( 15U )
#define DMA2_REQ_TIM8_CH4                      ( 16U )
#define DMA2_REQ_TIM8_UP                       ( 17U )
#define DMA2_REQ_TIM8_TRIG                     ( 18U )
#define DMA2_REQ_TIM8_COM                      ( 19U )
#define DMA2_REQ_TIM3_CH1                      ( 20U )
#define DMA2_REQ_TIM3_CH2                      ( 21U )
#define DMA2_REQ_TIM3_CH3                      ( 22U )
#define DMA2_REQ_TIM3_CH4                      ( 23U )
#define DMA2_REQ_TIM3_UP                       ( 24U )
#define DMA2_REQ_TIM3_TRIG                     ( 25U )
#define DMA2_REQ_ADC2                          ( 26U )
#define DMA2_REQ_ADC3                          ( 27U )
#define DMA2_REQ_USART3_TX                     ( 28U )
#define DMA2_REQ_USART3_RX                     ( 29U )
#define DMA2_REQ_LPUART_TX                     ( 30U )
#define DMA2_REQ_LPUART_RX                     ( 31U )
#define DMA2_REQ_TIM16_CH1                     ( 32U )
#define DMA2_REQ_TIM16_UP                      ( 33U )
#define DMA2_REQ_TIM17_CH1                     ( 34U )
#define DMA2_REQ_TIM17_UP                      ( 35U )
#define DMA2_REQ_TIM6_UP                       ( 36U )
#define DMA2_REQ_I2S1_TX                       ( 37U )
#define DMA2_REQ_I2S1_RX                       ( 38U )
#define DMA2_REQ_DAC1_CH1                      ( 39U )
#define DMA2_REQ_DAC1_CH2                      ( 40U )
#define DMA2_REQ_I2S2_TX                       ( 41U )
#define DMA2_REQ_I2S2_RX                       ( 42U )
#define DMA2_REQ_I2S3_TX                       ( 43U )
#define DMA2_REQ_I2S3_RX                       ( 44U )
#define DMA2_REQ_USART4_TX                     ( 45U )
#define DMA2_REQ_USART4_RX                     ( 46U )
#define DMA2_REQ_SPI3_TX                       ( 47U )
#define DMA2_REQ_SPI3_RX                       ( 48U )
#define DMA2_REQ_TIM7_UP                       ( 49U )
#define DMA2_REQ_NDL                           ( 55U )
#define DMA2_REQ_STM1_PWM                      ( 56U )
#define DMA2_REQ_STM2_PWM                      ( 57U )
#define DMA2_REQ_DCMI                          ( 58U )
#define DMA2_REQ_SPI7_RX                       ( 59U )
#define DMA2_REQ_SPI7_TX                       ( 60U )
#define DMA2_REQ_SPI8_RX                       ( 61U )
#define DMA2_REQ_SPI8_TX                       ( 62U )
#define DMA2_REQ_STM3_PWM                      ( 63U )
#define DMA2_REQ_STM4_PWM                      ( 64U )
#define DMA2_REQ_STM5_PWM                      ( 65U )
#define DMA2_REQ_STM6_PWM                      ( 66U )
#define DMA2_REQ_LPT                           ( 67U )
#define DMA2_REQ_TIM5_UP                       ( 68U )
#define DMA2_REQ_TIM5_CH1                      ( 69U )
#define DMA2_REQ_TIM5_CH2                      ( 70U )
#define DMA2_REQ_TIM5_CH3                      ( 71U )
#define DMA2_REQ_TIM5_CH4                      ( 72U )    
#define DMA2_REQ_TIM5_TRIG                     ( 73U ) 
#define DMA2_REQ_TIM5_COM                      ( 74U )     
#define DMA2_REQ_TIM25_UP                      ( 75U ) 
#define DMA2_REQ_TIM25_CH1                     ( 76U )    
#define DMA2_REQ_TIM25_CH2                     ( 77U )  
#define DMA2_REQ_TIM25_TRIG                    ( 78U ) 
#define DMA2_REQ_TIM25_COM                     ( 79U )    
#define DMA2_REQ_TIM20_UP                      ( 80U )   
#define DMA2_REQ_TIM20_CH1                     ( 81U )   
#define DMA2_REQ_TIM20_CH2                     ( 82U )  
#define DMA2_REQ_TIM20_CH3                     ( 83U )   
#define DMA2_REQ_TIM20_CH4                     ( 84U )      
#define DMA2_REQ_TIM20_CH5                     ( 85U )      
#define DMA2_REQ_TIM20_CH6                     ( 86U )   
#define DMA2_REQ_TIM20_TRIG                    ( 87U ) 
#define DMA2_REQ_TIM20_COM                     ( 88U )   
#define DMA2_REQ_TIM18_UP                      ( 89U )   
#define DMA2_REQ_TIM18_CH1                     ( 90U )   
#define DMA2_REQ_TIM18_TRIG                    ( 91U )   
#define DMA2_REQ_TIM18_COM                     ( 92U )  
#define DMA2_REQ_TIM19_UP                      ( 93U )     
#define DMA2_REQ_TIM19_CH1                     ( 94U )     
#define DMA2_REQ_TIM19_TRIG                    ( 95U )     
#define DMA2_REQ_TIM19_COM                     ( 96U )  
#define DMA2_REQ_TIM21_UP                      ( 97U )     
#define DMA2_REQ_TIM22_UP                      ( 98U )    
#define DMA2_REQ_TIM23_UP                      ( 99U )   
#define DMA2_REQ_TIM23_CH1                     ( 100U )   
#define DMA2_REQ_TIM23_CH2                     ( 101U )  
#define DMA2_REQ_TIM23_CH3                     ( 102U )  
#define DMA2_REQ_TIM23_CH4                     ( 103U )  
#define DMA2_REQ_TIM23_TRIG                    ( 104U ) 
#define DMA2_REQ_TIM23_COM                     ( 105U )    
#define DMA2_REQ_TIM24_UP                      ( 106U )    
#define DMA2_REQ_TIM24_CH1                     ( 107U )   
#define DMA2_REQ_TIM24_CH2                     ( 108U )  
#define DMA2_REQ_TIM24_CH3                     ( 109U )  
#define DMA2_REQ_TIM24_CH4                     ( 110U )    
#define DMA2_REQ_TIM24_TRIG                    ( 111U ) 
#define DMA2_REQ_TIM24_COM                     ( 112U ) 
#define DMA2_REQ_SPI4_RX                       ( 113U )
#define DMA2_REQ_SPI4_TX                       ( 114U )
#define DMA2_REQ_SPI5_RX                       ( 115U )
#define DMA2_REQ_SPI5_TX                       ( 116U )
#define DMA2_REQ_DAC2_CH1                      ( 117U )
#define DMA2_REQ_DAC2_CH2                      ( 118U )
#define DMA2_REQ_OSPI1_RX                      ( 119U )
#define DMA2_REQ_OSPI1_TX                      ( 120U )
#define DMA2_REQ_OSPI2_RX                      ( 121U )
#define DMA2_REQ_OSPI2_TX                      ( 122U )
#define DMA2_REQ_I2C3_TX                       ( 123U )
#define DMA2_REQ_I2C3_RX                       ( 124U )
#define DMA2_REQ_I2C4_TX                       ( 125U )
#define DMA2_REQ_I2C4_RX                       ( 126U )
#define DMA2_REQ_USART5_TX                     ( 127U )
#define DMA2_REQ_USART5_RX                     ( 128U )
#define DMA2_REQ_USART6_TX                     ( 129U )
#define DMA2_REQ_USART6_RX                     ( 130U )
#define DMA2_REQ_USART7_TX                     ( 131U )
#define DMA2_REQ_USART7_RX                     ( 132U )
#define DMA2_REQ_USART8_TX                     ( 133U )
#define DMA2_REQ_USART8_RX                     ( 134U )
#define DMA2_REQ_USART9_TX                     ( 135U )
#define DMA2_REQ_USART9_RX                     ( 136U )
#define DMA2_REQ_USART10_TX                    ( 137U )
#define DMA2_REQ_USART10_RX                    ( 138U ) 
#define DMA2_REQ_FDCAN1_TX                     ( 139U )
#define DMA2_REQ_FDCAN1_RX                     ( 140U )
#define DMA2_REQ_FDCAN2_TX                     ( 141U )
#define DMA2_REQ_FDCAN2_RX                     ( 142U )
#define DMA2_REQ_FDCAN3_TX                     ( 143U )
#define DMA2_REQ_FDCAN3_RX                     ( 144U )
#define DMA2_REQ_SPI6_RX                       ( 145U )
#define DMA2_REQ_SPI6_TX                       ( 146U )
#define DMA2_REQ_MAX                           ( 147U )

/**
  * @}
  */

/**
  * @brief  DMA_XfeCallbackID
  */
  
#define DMA_CALLBACKID_CPLT                     ( 0U )
#define DMA_CALLBACKID_HALFCPLT                 ( 1U )
#define DMA_CALLBACKID_ERROR                    ( 2U )
#define DMA_CALLBACKID_ABORT                    ( 3U )
#define DMA_CALLBACKID_MAX                      ( 4U )

/**
  * @}
  */

/** @defgroup  DMA_Flag
  * @{
  */
#define DMA_FLAG_TC						        ( 0x01U )   /*!< Flag, indicating transmission completion interrupt occur	*/
#define DMA_FLAG_HTC					        ( 0x02U )   /*!< Flag, indicating half transmission completion interrupt occur	*/
#define DMA_FLAG_ERR					        ( 0x04U )   /*!< Flag, indicating error interrupt occur	*/
#define DMA_FLAG_RTC					        ( 0x08U )   /*!< Flag, indicating raw transmission completion interrupt occur */
#define DMA_FLAG_RHTC					        ( 0x10U )   /*!< Flag, indicating raw half transmission completion interrupt occur */
#define DMA_FLAG_RERR					        ( 0x20U )   /*!< Flag, indicating raw error interrupt occur */

/**
  * @}
  */

/**
  * @brief  DMA FLAG mask for assert test
  */
  
#define DMA_FLAG_MASK                           ( DMA_FLAG_TC | DMA_FLAG_HTC | DMA_FLAG_ERR | DMA_FLAG_RTC | DMA_FLAG_RHTC | DMA_FLAG_RERR )


/** @defgroup  DMA_IT
  * @{
  */
#define DMA_IT_TC						        ( DMA_CXCONFIG_ITC )    /*!< transmission completion interrupt */
#define DMA_IT_HTC						        ( DMA_CXCONFIG_IHFTC )  /*!< indicating half transmission completion interrupt */
#define DMA_IT_ERR					            ( DMA_CXCONFIG_IE )     /*!< error interrupt */

/**
  * @}
  */

/**
  * @brief  DMA IT mask for assert test
  */
  
#define DMA_IT_MASK                             ( DMA_IT_TC | DMA_IT_HTC | DMA_IT_ERR )

/**
  * @brief  DMA TIMEOUT
  */
  
#define DMA_ABORT_TIMEOUT                       ( 0xFFFFU )


/* Exported functions --------------------------------------------------------*/

#define __HAL_LINK_DMA(_HANDLE_, _DMA_LINK_, _DMA_HANDLE_)          (_HANDLE_._DMA_LINK_ = &_DMA_HANDLE_)

#define __HAL_DMA_ENABLE(__HANDLE__)                                ((__HANDLE__)->DMA->CONFIG |= DMA_CONFIG_EN)

#define __HAL_DMA_DISABLE(__HANDLE__)                               ((__HANDLE__)->DMA->CONFIG &= ~DMA_CONFIG_EN)

#define __HAL_DMA_MASTER1_BIG_ENDIAN(__HANDLE__)                    ((__HANDLE__)->DMA->CONFIG |= DMA_CONFIG_M1ENDIAN)

#define __HAL_DMA_MASTER1_LITTLE_ENDIAN(__HANDLE__)                 ((__HANDLE__)->DMA->CONFIG &= ~DMA_CONFIG_M1ENDIAN)

#define __HAL_DMA_MASTER2_BIG_ENDIAN(__HANDLE__)                    ((__HANDLE__)->DMA->CONFIG |= DMA_CONFIG_M2ENDIAN)

#define __HAL_DMA_MASTER2_LITTLE_ENDIAN(__HANDLE__)                 ((__HANDLE__)->DMA->CONFIG &= ~DMA_CONFIG_M2ENDIAN)

#define __HAL_DMA_RAWINT_ENABLE(__HANDLE__)                         ((__HANDLE__)->Instance->CXCTRL |= DMA_CXCTRL_RITEN)

#define __HAL_DMA_RAWINT_DISABLE(__HANDLE__)                        ((__HANDLE__)->Instance->CXCTRL &= ~DMA_CXCTRL_RITEN)

#define __HAL_DMA_LOCK_ENABLE(__HANDLE__)                           ((__HANDLE__)->Instance->CXCONFIG |= DMA_CXCONFIG_LOCK)

#define __HAL_DMA_LOCK_DISABLE(__HANDLE__)                          ((__HANDLE__)->Instance->CXCONFIG &= ~DMA_CXCONFIG_LOCK)

#define __HAL_DMA_GET_HFTC_IT_SOURCE(__HANDLE__) 					((__HANDLE__)->Instance->CXCONFIG & DMA_CXCONFIG_IHFTC)

#define __HAL_DMA_GET_TC_IT_SOURCE(__HANDLE__) 				        ((__HANDLE__)->Instance->CXCONFIG & DMA_CXCONFIG_ITC)

#define __HAL_DMA_GET_ERR_IT_SOURCE(__HANDLE__) 					((__HANDLE__)->Instance->CXCONFIG & DMA_CXCONFIG_IE)

#define __HAL_DMA_GET_TRANSFER_SIZE(__HANDLE__)                     ((__HANDLE__)->Instance->CXCTRL & 0xFFFFU)

#define __HAL_DMA_GET_LINK(__HANDLE__) 						        ((__HANDLE__)->Instance->CXLLI & DMA_CXLLI_LLI)



/** @defgroup  DMA Private Macros
  * @{
  */
#define IS_DMA_HANDLE(__HANDLE__)                                   ((__HANDLE__) != NULL)

#define IS_DMA_ALL_INSTANCE(__INSTANCE__)                           (((__INSTANCE__) == DMA1_Channel0)  || \
                                                                     ((__INSTANCE__) == DMA1_Channel1)  || \
                                                                     ((__INSTANCE__) == DMA1_Channel2)  || \
                                                                     ((__INSTANCE__) == DMA1_Channel3)  || \
                                                                     ((__INSTANCE__) == DMA1_Channel4)  || \
                                                                     ((__INSTANCE__) == DMA1_Channel5)  || \
                                                                     ((__INSTANCE__) == DMA1_Channel6)  || \
                                                                     ((__INSTANCE__) == DMA1_Channel7)  || \
                                                                     ((__INSTANCE__) == DMA2_Channel0)  || \
                                                                     ((__INSTANCE__) == DMA2_Channel1)  || \
                                                                     ((__INSTANCE__) == DMA2_Channel2)  || \
                                                                     ((__INSTANCE__) == DMA2_Channel3)  || \
                                                                     ((__INSTANCE__) == DMA2_Channel4)  || \
                                                                     ((__INSTANCE__) == DMA2_Channel5)  || \
                                                                     ((__INSTANCE__) == DMA2_Channel6)  || \
                                                                     ((__INSTANCE__) == DMA2_Channel7))                                          

#define IS_DMA_MODE(__MODE__)                                       (((__MODE__) == DMA_MODE_NORMAL )   || \
                                                                     ((__MODE__) == DMA_MODE_CIRCULAR)) 
                                             
#define IS_DMA_DATAFLOW(__DATAFLOW__)                               (((__DATAFLOW__) == DMA_DATAFLOW_M2M)   || \
                                                                     ((__DATAFLOW__) == DMA_DATAFLOW_M2P)   || \
                                                                     ((__DATAFLOW__) == DMA_DATAFLOW_P2M))

#define IS_DMA_REQ1ID(__DATAFLOW__, __REQID__)                      ((__DATAFLOW__ == DMA_DATAFLOW_M2M) ? SET : \
                                                                    ((__REQID__) < DMA1_REQ_MAX))

#define IS_DMA_REQ2ID(__DATAFLOW__, __REQID__)                      ((__DATAFLOW__ == DMA_DATAFLOW_M2M) ? SET : \
                                                                    ((__REQID__) < DMA2_REQ_MAX))
                                                                     
#define IS_DMA_SRCINCDEC(__INCDEC__)                                (((__INCDEC__) == DMA_SRCINCDEC_DISABLE )   || \
                                                                     ((__INCDEC__) == DMA_SRCINCDEC_INC)        || \
                                                                     ((__INCDEC__) == DMA_SRCINCDEC_DEC)) 
                                             
#define IS_DMA_DESTINCDEC(__INCDEC__)                               (((__INCDEC__) == DMA_DESTINCDEC_DISABLE )  || \
                                                                     ((__INCDEC__) == DMA_DESTINCDEC_INC)       || \
                                                                     ((__INCDEC__) == DMA_DESTINCDEC_DEC)) 
                                             
#define IS_DMA_SRCWIDTH(__WIDTH__)                                  (((__WIDTH__) == DMA_SRCWIDTH_BYTE)         || \
                                                                     ((__WIDTH__) == DMA_SRCWIDTH_HALFWORD)     || \
                                                                     ((__WIDTH__) == DMA_SRCWIDTH_WORD))

#define IS_DMA_DESTWIDTH(__WIDTH__)                                 (((__WIDTH__) == DMA_DESTWIDTH_BYTE)        || \
                                                                     ((__WIDTH__) == DMA_DESTWIDTH_HALFWORD)    || \
                                                                     ((__WIDTH__) == DMA_DESTWIDTH_WORD))

#define IS_DMA_SRCBURST(__BURST__)                                  (((__BURST__) == DMA_SRCBURST_1)   || \
                                                                     ((__BURST__) == DMA_SRCBURST_4)   || \
                                                                     ((__BURST__) == DMA_SRCBURST_8)   || \
                                                                     ((__BURST__) == DMA_SRCBURST_16)  || \
                                                                     ((__BURST__) == DMA_SRCBURST_32)  || \
                                                                     ((__BURST__) == DMA_SRCBURST_64)  || \
                                                                     ((__BURST__) == DMA_SRCBURST_128) || \
                                                                     ((__BURST__) == DMA_SRCBURST_256))

#define IS_DMA_DESTBURST(__BURST__)                                 (((__BURST__) == DMA_DESTBURST_1)   || \
                                                                     ((__BURST__) == DMA_DESTBURST_4)   || \
                                                                     ((__BURST__) == DMA_DESTBURST_8)   || \
                                                                     ((__BURST__) == DMA_DESTBURST_16)  || \
                                                                     ((__BURST__) == DMA_DESTBURST_32)  || \
                                                                     ((__BURST__) == DMA_DESTBURST_64)  || \
                                                                     ((__BURST__) == DMA_DESTBURST_128) || \
                                                                     ((__BURST__) == DMA_DESTBURST_256))

#define IS_DMA_SRCMASTER(__MASTER__)                                (((__MASTER__) == DMA_SRCMASTER_1)  || \
                                                                     ((__MASTER__) == DMA_SRCMASTER_2))

#define IS_DMA_DESTMASTER(__MASTER__)                               (((__MASTER__) == DMA_DESTMASTER_1) || \
                                                                     ((__MASTER__) == DMA_DESTMASTER_2))

#define IS_DMA_MASTER1_ENDIAN(__ENDIAN__)                           (((__ENDIAN__) == DMA_MASTER1_ENDIAN_LITTLE)    || \
                                                                     ((__ENDIAN__) == DMA_MASTER1_ENDIAN_BIG))

#define IS_DMA_MASTER2_ENDIAN(__ENDIAN__)                           (((__ENDIAN__) == DMA_MASTER2_ENDIAN_LITTLE)    || \
                                                                     ((__ENDIAN__) == DMA_MASTER2_ENDIAN_BIG))

#define IS_DMA_NEXTMASTER(__MASTER__)                               (((__MASTER__) == DMA_NEXTMASTER_1)     || \
                                                                     ((__MASTER__) == DMA_NEXTMASTER_2))

#define IS_DMA_CALLBACK(__CALLBACK__)                               ((__CALLBACK__) < DMA_CALLBACKID_MAX)
            
#define IS_DMA_RAWIT(__RAWIT__)                                     (((__RAWIT__) == DMA_RAWINT_DISABLE)    || \
                                                                     ((__RAWIT__) == DMA_RAWINT_ENABLE))
            
#define IS_DMA_SRCADDR(__ADDR__)                                    ( SET )
            
#define IS_DMA_DESTADDR(__ADDR__)                                   ( SET )
            
#define IS_DMA_NEXT(__NEXT__)                                       ((((uint32_t)(__NEXT__)) &  0x03U) == 0)
            
#define IS_DMA_TRANSFERSIZE(__SIZE__)                               (((__SIZE__) != 0) && ((__SIZE__) <= 0xFFFFU))

#define IS_DMA_STATE(__FLAG__)                                      (((__FLAG__) == DMA_FLAG_TC)   || \
                                                                     ((__FLAG__) == DMA_FLAG_HTC)  || \
                                                                     ((__FLAG__) == DMA_FLAG_ERR)  || \
                                                                     ((__FLAG__) == DMA_FLAG_RTC)  || \
                                                                     ((__FLAG__) == DMA_FLAG_RHTC) || \
                                                                     ((__FLAG__) == DMA_FLAG_RERR))

#define IS_DMA_FLAG(__FLAG__)                                       ((((uint32_t)(__FLAG__) &  DMA_FLAG_MASK) != 0) &&  \
                                                                     (((uint32_t)(__FLAG__) & ~DMA_FLAG_MASK) == 0))

#define IS_DMA_IT(__IT__)                                           ((((uint32_t)(__IT__) &  DMA_IT_MASK) != 0) &&  \
                                                                     (((uint32_t)(__IT__) & ~DMA_IT_MASK) == 0))
                                             
/**
  * @}
  */



/* Exported functions --------------------------------------------------------*/

/* This function handles DMA interrupt request. */
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);

/* Initialize the DMA according to the specified. */
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma);

/* DeInitializes the DMA peripheral. */
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma);

/* Initialize the DMA MSP. */
void HAL_DMA_MspInit(DMA_HandleTypeDef *hdma);

/* DeInitialize the DMA MSP. */
void HAL_DMA_MspDeInit(DMA_HandleTypeDef *hdma);

/* Register callbacks. */
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, uint32_t CallbackID, \
                                     void (* pCallback)(struct __DMA_HandleTypeDef * hdma));
                                     
/* UnRegister callbacks. */
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, uint32_t CallbackID);

/* Starts the DMA Transfer. */
HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t SrcAddr, uint32_t DestAddr, uint32_t TransferSize);

/* Start the DMA Transfer with interrupt enabled. */
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddr, uint32_t DestAddr, uint32_t TransferSize);
                                    
/* Initialize linked list. */
HAL_StatusTypeDef HAL_DMA_InitLink(DMA_LinkTypeDef *Link, DMA_LinkInitTypeDef *Link_Init);

/* Set the next node of the linked node. */
HAL_StatusTypeDef HAL_DMA_SetLinkNext(DMA_LinkTypeDef *Curr, DMA_LinkTypeDef *Next);

/* DMA link transfer start. */
HAL_StatusTypeDef HAL_DMA_Start_Link(DMA_HandleTypeDef *hdma, DMA_LinkTypeDef *Link);

/* DMA link transfer start with interrupt enabled. */
HAL_StatusTypeDef HAL_DMA_Start_Link_IT(DMA_HandleTypeDef *hdma, DMA_LinkTypeDef *Link);

/* Abort the DMA Transfer. */
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);

/* Get interrupt source. */
FunctionalState HAL_DMA_GetITSource(DMA_HandleTypeDef *hdma, uint32_t IT);

/* Enable interrupt. */
HAL_StatusTypeDef HAL_DMA_EnableIT(DMA_HandleTypeDef *hdma, uint32_t IT);

/* Disable interrupt. */
HAL_StatusTypeDef HAL_DMA_DisableIT(DMA_HandleTypeDef *hdma, uint32_t IT);

/* Clear the DMA flag. */
HAL_StatusTypeDef HAL_DMA_ClearFlag(DMA_HandleTypeDef *hdma, uint32_t Flag);

/* Returns the DMA flag. */
FlagStatus HAL_DMA_GetFlag(DMA_HandleTypeDef *hdma, uint32_t Flag);

#endif
