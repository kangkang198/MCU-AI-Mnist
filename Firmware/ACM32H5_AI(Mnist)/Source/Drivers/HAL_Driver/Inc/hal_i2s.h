
/******************************************************************************
*@file  : hal_i2s.h
*@brief : Header file of I2S HAL module.
******************************************************************************/

#ifndef __HAL_I2S_H__
#define __HAL_I2S_H__

#include "hal.h"

/**
  * @brief I2S Init structure definition
  */
  
typedef struct
{
    uint32_t Mode;                          /*!< Specifies the I2S operating mode.
                                                  This parameter can be a value of @ref I2S_Mode            */
    
    uint32_t Standard;                      /*!< Specifies the standard used for the I2S communication.
                                                  This parameter can be a value of @ref I2S_Standard        */
    
    uint32_t DataFormat;                    /*!< Specifies the data format for the I2S communication.
                                                  This parameter can be a value of @ref I2S_DataFormat      */
    
    uint32_t MCLKOutput;                    /*!< Specifies whether the I2S MCLK output is enabled or not.
                                                  This parameter can be a value of @ref I2S_MCLK_Output     */

    uint32_t ClockPolarity;                 /*!< Specifies the idle state of the I2S clock.
                                                  This parameter can be a value of @ref I2S_ClockPolarity   */

    uint32_t IOSwitch;                      /*!< Specifies the idle state of the I2S clock.
                                                  This parameter can be a value of @ref I2S_IOSwitch   */

    uint32_t AudioFreq;                    /*!< Specifies the frequency selected for the I2S communication. */
    
}I2S_InitTypeDef;



/**
  * @brief I2S handle Structure definition
  */
typedef struct __I2S_HandleTypeDef
{
    I2S_TypeDef *Instance;                                              /*!< I2S registers base address             */
    I2S_InitTypeDef Init;                                               /*!< I2S communication parameters           */
    
    DMA_HandleTypeDef *hdmactx;                                         /*!< Tx DMA Handle parameters               */
    DMA_HandleTypeDef *hdmacrx;                                         /*!< Rx DMA Handle parameters               */

    uint32_t State;                                                     /*!< Tx state                               */
    uint32_t Error;                                                     /*!< Tx Error                               */
    uint32_t Abort;                                                     /*!< Tx abort flag in blocking mode         */
    uint32_t *pTxBuf;                                                   /*!< Tx buffer pointer                      */
    uint32_t TxCount;                                                   /*!< Tx size not transfer                   */
    uint32_t *pRxBuf;                                                   /*!< Rx buffer pointer                      */
    uint32_t RxCount;                                                   /*!< Rx size not transfer                   */
    
 	uint32_t (*TxCpltCallback)(struct __I2S_HandleTypeDef *);           /* send complete callback                   */
 	uint32_t (*RxCpltCallback)(struct __I2S_HandleTypeDef *);           /* send complete callback                   */
 	uint32_t (*TxEmptyCallback)(struct __I2S_HandleTypeDef *);          /* send complete callback                   */
 	uint32_t (*MsuspCallback)(struct __I2S_HandleTypeDef *);            /* send complete callback                   */
 	uint32_t (*SvtcCallback)(struct __I2S_HandleTypeDef *);             /* send complete callback                   */
 	uint32_t (*DMATxCpltCallback)(struct __I2S_HandleTypeDef *);        /* send complete callback                   */
 	uint32_t (*DMATxHalfCpltCallback)(struct __I2S_HandleTypeDef *);    /* send half complete callback in DMA mode  */
    uint32_t (*DMARxCpltCallback)(struct __I2S_HandleTypeDef *);        /* recv complete callback                   */
    uint32_t (*DMARxHalfCpltCallback)(struct __I2S_HandleTypeDef *);    /* recv half complete callback in DMA mode  */
    uint32_t (*ErrorCallback)(struct __I2S_HandleTypeDef *);            /* error callback                           */
    
}I2S_HandleTypeDef;


/**
  * @brief  HAL I2S Callback pointer definition
  */

typedef uint32_t (*pI2S_CallbackTypeDef)(I2S_HandleTypeDef *hlpuart);  /*!< pointer to the I2S callback function */


/** @defgroup I2S_Mode
  * @{
  */
  
#define I2S_MODE_MASTER                     ( I2S_CR_MODE )
#define I2S_MODE_SLAVE                      ( 0U )

/**
  * @}
  */


/** @defgroup I2S_Standard
  * @{
  */
  
#define I2S_STANDARD_PHILIPS                ( 0U )
#define I2S_STANDARD_MSB                    ( I2S_CR_STD_0 )
#define I2S_STANDARD_LSB                    ( I2S_CR_STD_1 )
#define I2S_STANDARD_PCM_SHORT              ( I2S_CR_STD_1 | I2S_CR_STD_0 )
#define I2S_STANDARD_PCM_LONG               ( I2S_CR_PCMMODE | I2S_CR_STD_1 | I2S_CR_STD_0 )

/**
  * @}
  */


/** @defgroup I2S_DataFormat
  * @{
  */
  
#define I2S_DATA_FORMAT_16B_EXTENDED_TO_16B  ( 0U )
#define I2S_DATA_FORMAT_16B_EXTENDED_TO_32B  ( I2S_CR_CHLEN )
#define I2S_DATA_FORMAT_24B_EXTENDED_TO_32B  ( I2S_CR_CHLEN | I2S_CR_DLEN_0 )
#define I2S_DATA_FORMAT_32B_EXTENDED_TO_32B  ( I2S_CR_CHLEN | I2S_CR_DLEN_1 )
/**
  * @}
  */


/** @defgroup I2S_MCLKOut
  * @{
  */
#define I2S_MCLKOUT_ENABLE                  ( I2S_PR_MCKOE )
#define I2S_MCLKOUT_DISABLE                 ( 0U )
/**
  * @}
  */


/** @defgroup I2S_ClockPolarity
  * @{
  */
  
#define I2S_CLOCK_POLARITY_LOW              ( 0U )
#define I2S_CLOCK_POLARITY_HIGH             ( I2S_CR_CKPL )

/**
  * @}
  */


/** @defgroup I2S_IOSwitch
  * @{
  */
  
#define I2S_IO_SWITCH_ENABLE                 ( I2S_CR_IOSWP )
#define I2S_IO_SWITCH_DISABLE                ( 0U )

/**
  * @}
  */

/** @defgroup I2S_CallbackID
  * @{
  */
  
#define I2S_CALLBACKID_TX_CPLT              ( 0U )
#define I2S_CALLBACKID_RX_CPLT              ( 1U )
#define I2S_CALLBACKID_TX_EMPTY             ( 2U )
#define I2S_CALLBACKID_MSUSP                ( 3U )
#define I2S_CALLBACKID_SVTC                 ( 4U )
#define I2S_CALLBACKID_DMA_TX_CPLT          ( 5U )
#define I2S_CALLBACKID_DMA_TX_HALF_CPLT     ( 6U )
#define I2S_CALLBACKID_DMA_RX_CPLT          ( 7U )
#define I2S_CALLBACKID_DMA_RX_HALF_CPLT     ( 8U )
#define I2S_CALLBACKID_ERROR                ( 9U )
#define I2S_CALLBACKID_MAX                  ( 10U )

/**
  * @}
  */

/** @defgroup I2S_IT
  * @{
  */
#define I2S_IT_TXE                          ( I2S_DIER_TXEIE )
#define I2S_IT_RXNE                         ( I2S_DIER_RXNEIE )
#define I2S_IT_ERR                          ( I2S_DIER_ERRIE )
#define I2S_IT_MSUSP                        ( I2S_DIER_MSUSPIE )
#define I2S_IT_SVTC                         ( I2S_DIER_SVTCIE )

/**
  * @}
  */

/** 
  * @brief  
  */

#define I2S_IT_MASK                         ( I2S_IT_TXE | I2S_IT_RXNE | I2S_IT_ERR | I2S_IT_MSUSP | I2S_IT_SVTC )

/** @defgroup I2S_Flags
  * @{
  */
  
#define I2S_FLAG_SVTC                       ( I2S_SR_SVTC )
#define I2S_FLAG_MSUSP                      ( I2S_SR_MSUSP )
#define I2S_FLAG_FE                         ( I2S_SR_FE )
#define I2S_FLAG_OVR                        ( I2S_SR_OVR )
#define I2S_FLAG_UDR                        ( I2S_SR_UDR )
#define I2S_FLAG_CH                         ( I2S_SR_CH )
#define I2S_FLAG_TXE                        ( I2S_SR_TXE )
#define I2S_FLAG_RXNE                       ( I2S_SR_RXNE )

/**
  * @}
  */

/** 
  * @brief  
  */

#define I2S_FLAG_MASK                       ( I2S_FLAG_SVTC | I2S_FLAG_MSUSP | I2S_FLAG_FE | I2S_FLAG_OVR | \
                                              I2S_FLAG_UDR | I2S_FLAG_CH | I2S_FLAG_TXE | I2S_FLAG_RXNE )

      
/** 
  * @brief  I2S_State
  */
                 
#define I2S_STATE_READY                     ( 0U )
#define I2S_STATE_BUSY                      ( 1U )
#define I2S_STATE_BUSY_IT                   ( 2U )
#define I2S_STATE_BUSY_DMA                  ( 3U )
#define I2S_STATE_BUSY_DMA_LINK             ( 4U )
   
/** 
  * @brief  I2S DMA error
  */
        
#define I2S_DMA_ERROR                       ( 1U << 31 )
#define I2S_DMA_TX_ERROR                    ( 1U << 31 )
#define I2S_DMA_RX_ERROR                    ( 1U << 31 )




/* Exported macros -----------------------------------------------------------*/
/** @defgroup I2S_Exported_Macros
  * @{
  */

/**
  * @brief  Enable the I2S peripheral.
  * @param  __HANDLE__ I2S handle
  * @retval None
  */
  
#define __HAL_I2S_ENABLE(__HANDLE__)                                    ((__HANDLE__)->Instance->CR |= I2S_CR_EN)

/**
  * @brief  Disable the I2S peripheral.
  * @param  __HANDLE__ I2S handle
  * @retval None
  */
  
#define __HAL_I2S_DISABLE(__HANDLE__)                                   ((__HANDLE__)->Instance->CR &= ~(I2S_CR_EN))

#define __HAL_I2S_TX_RX_ENABLE(__HANDLE__)                              ((__HANDLE__)->Instance->CR |= I2S_CR_TEN | I2S_CR_REN)

#define __HAL_I2S_TX_RX_DISABLE(__HANDLE__)                             ((__HANDLE__)->Instance->CR &= ~(I2S_CR_TEN | I2S_CR_REN))

#define __HAL_I2S_TX_ENABLE(__HANDLE__)                                 ((__HANDLE__)->Instance->CR |= I2S_CR_TEN)

#define __HAL_I2S_TX_DISABLE(__HANDLE__)                                ((__HANDLE__)->Instance->CR &= ~(I2S_CR_TEN))

#define __HAL_I2S_RX_ENABLE(__HANDLE__)                                 ((__HANDLE__)->Instance->CR |= I2S_CR_REN)

#define __HAL_I2S_RX_DISABLE(__HANDLE__)                                ((__HANDLE__)->Instance->CR &= ~(I2S_CR_REN))

#define __HAL_I2S_START_ENABLE(__HANDLE__)                              ((__HANDLE__)->Instance->CR |= I2S_CR_START)

#define __HAL_I2S_START_DISABLE(__HANDLE__)                             ((__HANDLE__)->Instance->CR &= ~(I2S_CR_START))

#define __HAL_I2S_STOP_ENABLE(__HANDLE__)                               ((__HANDLE__)->Instance->CR |= I2S_CR_STOP)

#define __HAL_I2S_STOP_DISABLE(__HANDLE__)                              ((__HANDLE__)->Instance->CR &= ~(I2S_CR_STOP))

#define __HAL_I2S_WRITE_DATA(__HANDLE__, __DATA__)                      ((__HANDLE__)->Instance->TXDR = (__DATA__))

#define __HAL_I2S_READ_DATA(__HANDLE__)                                 ((__HANDLE__)->Instance->RXDR)

/**
  * @brief  Enable the TX DMA.
  * @param  __HANDLE__ I2S handle
  * @retval None
  */
  
#define __HAL_I2S_TX_DMA_ENABLE(__HANDLE__)                             ((__HANDLE__)->Instance->CR |= I2S_CR_TXDMAEN)

/**
  * @brief  Disable the TX DMA.
  * @param  __HANDLE__ I2S handle
  * @retval None
  */
  
#define __HAL_I2S_TX_DMA_DISABLE(__HANDLE__)                            ((__HANDLE__)->Instance->CR &= ~(I2S_CR_TXDMAEN))


/**
  * @brief  Enable the RX DMA.
  * @param  __HANDLE__ I2S handle
  * @retval None
  */

#define __HAL_I2S_RX_DMA_ENABLE(__HANDLE__)                             ((__HANDLE__)->Instance->CR |= I2S_CR_RXDMAEN)

/**
  * @brief  Disable the RX DMA.
  * @param  __HANDLE__ I2S handle
  * @retval None
  */
  
#define __HAL_I2S_RX_DMA_DISABLE(__HANDLE__)                            ((__HANDLE__)->Instance->CR &= ~(I2S_CR_RXDMAEN))

/**
  * @brief  Enable the TX RX DMA.
  * @param  __HANDLE__ I2S handle
  * @retval None
  */
  
#define __HAL_I2S_TX_RX_DMA_ENABLE(__HANDLE__)                          ((__HANDLE__)->Instance->CR |= I2S_CR_TXDMAEN | I2S_CR_RXDMAEN)

/**
  * @brief  Disable the TX RX DMA.
  * @param  __HANDLE__ I2S handle
  * @retval None
  */
  
#define __HAL_I2S_TX_RX_DMA_DISABLE(__HANDLE__)                         ((__HANDLE__)->Instance->CR &= ~(I2S_CR_TXDMAEN | I2S_CR_RXDMAEN))


/**
  * @brief  Enable the specified I2S interrupt.
  * @param  __HANDLE__ I2S handle.
  * @param  __INTERRUPT__ I2S interrupt to set.
  *            This parameter can be a combination of:
  *            @arg I2S_IT_TXE  : Tx buffer empty Interrupt.
  *            @arg I2S_IT_RXNE : Rx buffer non empty Interrupt.
  *            @arg I2S_IT_ERR  : Error Interrupt.
  * @retval None.
  */
  
#define __HAL_I2S_IT_ENABLE(__HANDLE__, __INTERRUPT__)                  ((__HANDLE__)->Instance->DIER  |= (__INTERRUPT__))

/**
  * @brief  Disable the specified I2S interrupt.
  * @param  __HANDLE__ I2S handle.
  * @param  __INTERRUPT__ I2S interrupt to set.
  *            This parameter can be a combination of:
  *            @arg I2S_IT_TXE  : Tx buffer empty Interrupt.
  *            @arg I2S_IT_RXNE : Rx buffer non empty Interrupt.
  *            @arg I2S_IT_ERR  : Error Interrupt.
  * @retval None.
  */
  
#define __HAL_I2S_IT_DISABLE(__HANDLE__, __INTERRUPT__)                 ((__HANDLE__)->Instance->DIER  &= (~(__INTERRUPT__)))

/**
  * @brief  Check whether the specified I2S flag is set or not.
  * @param  __HANDLE__ I2S handle
  * @param  __FLAG__ I2S flag to check
  *            This parameter can be a value of:
  *            @arg I2S_FLAG_FE    : frame error flag.
  *            @arg I2S_FLAG_BUSY  : busy flag.
  *            @arg I2S_FLAG_RXOVE : rx buffer overflow flag.
  *            @arg I2S_FLAG_TXUDE : rx buffer uderflow flag.
  *            @arg I2S_FLAG_CHF   : which channel data is the next data.
  *            @arg I2S_FLAGR_TXE  : tx buffer empty flag.
  *            @arg I2S_FLAG_RXNE  : rx buffer non empty flag.
  * @retval The state of the specified flag (SET or RESET).
  */
  
#define __HAL_I2S_GET_FLAG(__HANDLE__, __FLAG__)                        ((__HANDLE__)->Instance->SR & (__FLAG__))


#define __HAL_I2S_CLEAR_FLAG(__HANDLE__, __FLAG__)                      ((__HANDLE__)->Instance->SR = 0xffffffff & ~(__FLAG__))


/**
  * @brief  Check whether the specified I2S interrupt source is enabled or not.
  * @param  __HANDLE__ I2S handle.
  * @param  __INTERRUPT__ I2S interrupt to check.
  *            This parameter can be a value of:
  *            @arg I2S_IT_TXE  : Tx buffer empty Interrupt.
  *            @arg I2S_IT_RXNE : Rx buffer non empty Interrupt.
  *            @arg I2S_IT_ERR  : Error Interrupt.
  * @retval Interrupt status.
  */

#define __HAL_I2S_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)              ((__HANDLE__)->Instance->DIER & (__INTERRUPT__))

/**
  * @}
  */


/** @defgroup  I2S Private Macros
  * @{
  */
  
#define IS_I2S_HANDLE(__HANDLE__)                                       ((__HANDLE__) != NULL)
  
#define IS_I2S_INSTANCE(__INSTANCE__)                                   (((__INSTANCE__) == I2S1)   || \
                                                                         ((__INSTANCE__) == I2S2)   || \
                                                                         ((__INSTANCE__) == I2S3))

#define IS_I2S_MODE(__MODE__)                                           (((__MODE__) == I2S_MODE_MASTER)     || \
                                                                         ((__MODE__) == I2S_MODE_SLAVE))

#define IS_I2S_STANDARD(__STANDARD__)                                   (((__STANDARD__) == I2S_STANDARD_PHILIPS)   || \
                                                                         ((__STANDARD__) == I2S_STANDARD_MSB)       || \
                                                                         ((__STANDARD__) == I2S_STANDARD_LSB)       || \
                                                                         ((__STANDARD__) == I2S_STANDARD_PCM_SHORT) || \
                                                                         ((__STANDARD__) == I2S_STANDARD_PCM_LONG))

#define IS_I2S_DATAFORMAT(__DATAFORMAT__)                               (((__DATAFORMAT__) == I2S_DATA_FORMAT_16B_EXTENDED_TO_16B) || \
                                                                         ((__DATAFORMAT__) == I2S_DATA_FORMAT_16B_EXTENDED_TO_32B) || \
                                                                         ((__DATAFORMAT__) == I2S_DATA_FORMAT_24B_EXTENDED_TO_32B) || \
                                                                         ((__DATAFORMAT__) == I2S_DATA_FORMAT_32B_EXTENDED_TO_32B))


#define IS_I2S_MCLKOUTPUT(__OUTPUT__)                                   (((__OUTPUT__) == I2S_MCLKOUT_ENABLE)            || \
                                                                         ((__OUTPUT__) == I2S_MCLKOUT_DISABLE))

#define IS_I2S_CLOCKPOLARITY(__POLARITY__)                              (((__POLARITY__) == I2S_CLOCK_POLARITY_LOW)          || \
                                                                         ((__POLARITY__) == I2S_CLOCK_POLARITY_HIGH))

#define IS_I2S_IOSWITCH(__SWITCH__)                                     (((__SWITCH__) == I2S_IO_SWITCH_ENABLE)              || \
                                                                         ((__SWITCH__) == I2S_IO_SWITCH_DISABLE))


#define IS_I2S_CALLBACKID(__CALLBACKID__)                               ((__CALLBACKID__) < I2S_CALLBACKID_MAX)

  
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

void HAL_I2S_IRQHander(I2S_HandleTypeDef *hi2s);
HAL_StatusTypeDef HAL_I2S_Init(I2S_HandleTypeDef *hi2s);
HAL_StatusTypeDef HAL_I2S_DeInit(I2S_HandleTypeDef *hi2s);
void HAL_I2S_MspInit(I2S_HandleTypeDef *hi2s);
void HAL_I2S_MspDeInit(I2S_HandleTypeDef *hi2s);
HAL_StatusTypeDef HAL_I2S_RegisterCallback(I2S_HandleTypeDef *hi2s, uint32_t id, pI2S_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_I2S_UnRegisterCallback(I2S_HandleTypeDef *hi2s, uint32_t id);

HAL_StatusTypeDef HAL_I2S_TxData(I2S_HandleTypeDef *hi2s, uint32_t Data);
HAL_StatusTypeDef HAL_I2S_RxData(I2S_HandleTypeDef *hi2s, uint32_t *pdata);

HAL_StatusTypeDef HAL_I2S_Transmit(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint32_t size, uint32_t timeout);
HAL_StatusTypeDef HAL_I2S_Receive(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint32_t size, uint32_t timeout);
HAL_StatusTypeDef HAL_I2S_Transmit_Receive(I2S_HandleTypeDef *hi2s, uint32_t *prxdata, uint32_t *ptxdata, uint32_t size, uint32_t timeout);

HAL_StatusTypeDef HAL_I2S_Transmit_IT(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint32_t size);
HAL_StatusTypeDef HAL_I2S_Receive_IT(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint32_t size);
HAL_StatusTypeDef HAL_I2S_Transmit_Receive_IT(I2S_HandleTypeDef *hi2s, uint32_t *prxdata, uint32_t *ptxdata, uint32_t size);

HAL_StatusTypeDef HAL_I2S_Transmit_DMA(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint16_t size);
HAL_StatusTypeDef HAL_I2S_Receive_DMA(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint16_t size);
HAL_StatusTypeDef HAL_I2S_Transmit_Receive_DMA(I2S_HandleTypeDef *hi2s, uint32_t *prxdata, uint32_t *ptxdata, uint16_t size);

HAL_StatusTypeDef HAL_I2S_Abort(I2S_HandleTypeDef *hi2s);
uint32_t HAL_I2S_GetState(I2S_HandleTypeDef *hi2s);

void HAL_I2S_TxEmptyCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_TxCompleteCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_MsuspCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_SvtcCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_RxNonEmptyCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s);

void HAL_I2S_DMATxCpltCallback(DMA_HandleTypeDef *hdmac);
void HAL_I2S_DMATxHalfCpltCallback(DMA_HandleTypeDef *hdmac);
void HAL_I2S_DMARxCpltCallback(DMA_HandleTypeDef *hdmac);
void HAL_I2S_DMARxHalfCpltCallback(DMA_HandleTypeDef *hdmac);
void HAL_I2S_DMAErrorCallback(DMA_HandleTypeDef *hdmac);
    



#endif

