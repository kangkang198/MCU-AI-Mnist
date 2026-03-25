
/******************************************************************************
*@file  : hal_lpuart.h
*@brief : Header file of LPUART HAL module.
******************************************************************************/

#ifndef __HAL_LPUART_H__
#define __HAL_LPUART_H__

#include "hal.h"

/** 
  * @brief  LPUART Init structure definition
  */
typedef struct
{
    uint32_t    BaudRate;           /*!< This member configures the UART communication baud rate.
                                         This parameter can be a value of @ref LPUART_BaudRate. */

    uint32_t    WordLength;         /*!< Specifies the number of data bits transmitted or received in a frame.
                                         This parameter can be a value of @ref LPUART_WordLength. */
          
    uint32_t    StopBits;           /*!< Specifies the number of stop bits transmitted.
                                         This parameter can be a value of @ref LPUART_StopBits. */

    uint32_t    Parity;             /*!< Specifies the parity mode.
                                         This parameter can be a value of @ref LPUART_Parity*/

    uint32_t    Mode;               /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                         This parameter can be a value of @ref LPUART_Mode. */

    uint32_t    ClockSource;        /*!< Specifies the clock source of LPUART.
                                         This parameter can be a value of @ref LPUART_ClockSource. */

    uint32_t    WakeupMode;         /*!< Specifies the wakeup Mode.
                                         This parameter can be a value of @ref LPUART_WakeupMode. */

    uint32_t    WakeupAddr;         /*!< Specifies the address of the wakeup matching.
                                         This parameter can be a value of @ref LPUART_WakeupAddr. */

} LPUART_InitTypeDef;


/** 
  * @brief  LPUART  handle structure definition
  */

typedef struct __LPUART_HandleTypeDef
{
    LPUART_TypeDef      *Instance;                                  /*!< Register base address      */
    LPUART_InitTypeDef  Init;                                       /*!< communication parameters   */
    DMA_HandleTypeDef   *hdmatx;                                    /*!< Tx DMA Handle parameters   */
    DMA_HandleTypeDef   *hdmarx;                                    /*!< Rx DMA Handle parameters   */
    
    uint32_t            TxState;                                    /*!< Tx state                   */
    uint32_t            TxError;                                    /*!< Tx Error flag              */
    uint8_t             *pTxBuf;                                    /*!< Tx buffer pointer          */
    uint32_t            TxCount;                                    /*!< Tx size not transfer       */
    uint32_t            TxAbort;                                    /*!< Tx abort flag in block mode*/
    
    uint32_t            RxState;                                    /*!< Rx state                   */
    uint32_t            RxError;                                    /*!< Rx Error flag              */
    uint8_t             *pRxBuf;                                    /*!< Rx buffer pointer          */
    uint32_t            RxCount;                                    /*!< Rx size not transfer       */
    uint32_t            RxAbort;                                    /*!< Rx abort flag in block mode*/
    
 	void (*TxCpltCallback)(struct __LPUART_HandleTypeDef *);        /* tx complete callback         */
 	void (*TxHalfCpltCallback)(struct __LPUART_HandleTypeDef *);        /* tx complete callback         */
    void (*TxErrorCallback)(struct __LPUART_HandleTypeDef *);         /* error callback               */
    void (*RxCpltCallback)(struct __LPUART_HandleTypeDef *);        /* rx recv complete callback    */
    void (*RxHalfCpltCallback)(struct __LPUART_HandleTypeDef *);        /* rx recv complete callback    */
    void (*RxErrorCallback)(struct __LPUART_HandleTypeDef *);         /* error callback               */
    void (*WakeupCallback)(struct __LPUART_HandleTypeDef *);        /* wakeup callback              */
    void (*BcntCallback)(struct __LPUART_HandleTypeDef *);        /* bit count callback              */
    void (*IdleCallback)(struct __LPUART_HandleTypeDef *);        /* idle callback              */
   
}LPUART_HandleTypeDef;


/**
  * @brief  HAL LPUART Callback pointer definition
  */

typedef void (*pLPUART_CallbackTypeDef)(LPUART_HandleTypeDef *hlpuart);  /*!< pointer to the LPUART callback function */

/******************************************************************************
*@brief : LPUART receive mode enum
*         
*@note : the enum is used in receive function: HAL_LPUART_Receive_To_Idle_BCNT
******************************************************************************/
typedef enum
{
    LPUART_RECEIVE_TOIDLE,                 /*!< end of receiving data by idle line checked */
    LPUART_RECEIVE_TOBCNT,                 /*!< end of receiving data by bit count value reached */
}LPUART_Receive_Mode_Enum;


/** @defgroup LPUART_WordLength
  * @{
  */
  
#define LPUART_WORDLENGTH_7B                ( LPUART_LCR_WLEN )
#define LPUART_WORDLENGTH_8B                ( 0U )

/**
  * @}
  */

/** @defgroup LPUART_StopBits
  * @{
  */
  
#define LPUART_STOPBITS_1B                  ( 0U )
#define LPUART_STOPBITS_2B                  ( LPUART_LCR_STP2 )

/**
  * @}
  */
  
/** @defgroup LPUART_Parity
  * @{
  */
  
#define LPUART_PARITY_NONE                  ( 0U )
#define LPUART_PARITY_ODD                   ( LPUART_LCR_PEN )
#define LPUART_PARITY_EVEN                  ( LPUART_LCR_PEN | LPUART_LCR_EPS )
#define LPUART_PARITY_0                     ( LPUART_LCR_PEN | LPUART_LCR_SPS | LPUART_LCR_EPS)
#define LPUART_PARITY_1                     ( LPUART_LCR_PEN | LPUART_LCR_SPS )

/**
  * @}
  */
  
/** @defgroup LPUART_ClockSource
  * @{
  */
  
#define LPUART_CLOCKSOURCE_RCL            ( RCC_LPUART1_CLK_SOURCE_RCL )
#define LPUART_CLOCKSOURCE_XTL              ( RCC_LPUART1_CLK_SOURCE_XTL )
#define LPUART_CLOCKSOURCE_PCLK_DIV4        ( RCC_LPUART1_CLK_SOURCE_PCLK1_DIV4)
#define LPUART_CLOCKSOURCE_PCLK_DIV8        ( RCC_LPUART1_CLK_SOURCE_PCLK1_DIV8)
#define LPUART_CLOCKSOURCE_PCLK_DIV16       ( RCC_LPUART1_CLK_SOURCE_PCLK1_DIV16)
#define LPUART_CLOCKSOURCE_PCLK_DIV32       ( RCC_LPUART1_CLK_SOURCE_PCLK1_DIV32)

/**
  * @}
  */

/** @defgroup LPUART_Mode
  * @{
  */
  
#define LPUART_MODE_TX                      ( LPUART_CR_TX_EN )
#define LPUART_MODE_RX                      ( LPUART_CR_RX_EN )
#define LPUART_MODE_TXRX                    ( LPUART_CR_TX_EN | LPUART_CR_RX_EN )

/**
  * @}
  */

/** @defgroup LPUART_WakeupMode
  * @{
  */
  
#define LPUART_WAKEUPMODE_NONE              ( LPUART_LCR_RXWKS )
#define LPUART_WAKEUPMODE_STARTBIT          ( 0U )
#define LPUART_WAKEUPMODE_ONEBYTENOCHECK    ( LPUART_LCR_RXWKS_0 )
#define LPUART_WAKEUPMODE_ONEBYTECHECK      ( LPUART_LCR_RXWKS_0 | LPUART_LCR_WKCK )
#define LPUART_WAKEUPMODE_ADDRNOCHECK       ( LPUART_LCR_RXWKS_1 )
#define LPUART_WAKEUPMODE_ADDRCHECK         ( LPUART_LCR_RXWKS_1 | LPUART_LCR_WKCK)

/**
  * @}
  */

/** @defgroup LPUART_CallbackID
  * @{
  */
  
#define LPUART_CALLBACKID_TXCPLT            ( 0U )
#define LPUART_CALLBACKID_TXHALFCPLT        ( 1U )
#define LPUART_CALLBACKID_TXERROR           ( 2U )
#define LPUART_CALLBACKID_RXCPLT            ( 3U )
#define LPUART_CALLBACKID_RXHALFCPLT        ( 4U )
#define LPUART_CALLBACKID_RXERROR           ( 5U )
#define LPUART_CALLBACKID_WAKEUP            ( 6U )
#define LPUART_CALLBACKID_BCNT           	( 7U )
#define LPUART_CALLBACKID_IDLE				( 8U )

/**
  * @}
  */

/** @defgroup LPUART_IT
  * @{
  */
  
#define LPUART_IT_START                     ( LPUART_IE_STARTIE )
#define LPUART_IT_MATCH                     ( LPUART_IE_MATCHIE )
#define LPUART_IT_RXOV                      ( LPUART_IE_RXOVIE )
#define LPUART_IT_FE                        ( LPUART_IE_FEIE )
#define LPUART_IT_PE                        ( LPUART_IE_PEIE )
#define LPUART_IT_TXE                       ( LPUART_IE_TXEIE )
#define LPUART_IT_TC                        ( LPUART_IE_TCIE )
#define LPUART_IT_RX                        ( LPUART_IE_RXIE )
#define LPUART_IT_IDLE						( LPUART_IE_IDLEIE )
#define LPUART_IT_BCNT						( LPUART_IE_BCNTIE )
/**
  * @}
  */

/** 
  * @brief  
  */

#define LPUART_IT_MASK                      ( LPUART_IT_START | LPUART_IT_MATCH | \
                                              LPUART_IT_RXOV | LPUART_IT_FE | \
                                              LPUART_IT_PE | LPUART_IT_TXE | \
                                              LPUART_IT_TC | LPUART_IT_RX | \
											  LPUART_IE_BCNTIE | LPUART_IE_IDLEIE)

/** @defgroup LPUART_Flags
  * @{
  */
  
#define LPUART_FLAG_TXE                     ( LPUART_SR_TXE )
#define LPUART_FLAG_STARTIF                 ( LPUART_SR_STARTIF )
#define LPUART_FLAG_MATCHIF                 ( LPUART_SR_MATCHIF )
#define LPUART_FLAG_TXOVF                   ( LPUART_SR_TXOVF )
#define LPUART_FLAG_RXF                     ( LPUART_SR_RXF )
#define LPUART_FLAG_RXOVIF                 ( LPUART_SR_RXOVIF )
#define LPUART_FLAG_FEIF                    ( LPUART_SR_FEIF )
#define LPUART_FLAG_PEIF                    ( LPUART_SR_PEIF )
#define LPUART_FLAG_TXEIF                   ( LPUART_SR_TXEIF )
#define LPUART_FLAG_TCIF                    ( LPUART_SR_TCIF )
#define LPUART_FLAG_RXIF                    ( LPUART_SR_RXIF )
#define LPUART_FLAG_IDLEIF					( LPUART_SR_IDLEIF )
#define LPUART_FLAG_BCNTIF					( LPUART_SR_BCNTIF )
/**
  * @}
  */

/** 
  * @brief  
  */

#define LPUART_IT_FLAG_MASK                 ( LPUART_FLAG_STARTIF | LPUART_FLAG_MATCHIF | \
                                              LPUART_FLAG_RXOVIF | LPUART_FLAG_FEIF | \
                                              LPUART_FLAG_PEIF | LPUART_FLAG_TXEIF | \
                                              LPUART_FLAG_TCIF | LPUART_FLAG_RXIF |\
											  LPUART_FLAG_IDLEIF | LPUART_FLAG_BCNTIF)

#define LPUART_FLAG_MASK                    ( LPUART_FLAG_TXE | LPUART_FLAG_TXOVF | \
                                              LPUART_FLAG_RXF | LPUART_IT_FLAG_MASK)

#define LPUART_CLEAR_FLAG_MASK              ( LPUART_FLAG_STARTIF | LPUART_FLAG_MATCHIF | \
                                              LPUART_FLAG_TXOVF | LPUART_FLAG_RXOVIF | \
                                              LPUART_FLAG_FEIF | LPUART_FLAG_PEIF | \
                                              LPUART_FLAG_TCIF | LPUART_FLAG_RXIF |\
											  LPUART_FLAG_IDLEIF | LPUART_FLAG_BCNTIF)
         
/** 
  * @brief  LPUART_State
  */
                 
#define LPUART_STATE_READY                  ( 0U )
#define LPUART_STATE_BUSY                   ( 1U )
#define LPUART_STATE_BUSY_IT                ( 2U )
#define LPUART_STATE_BUSY_DMA               ( 3U )
   
/** 
  * @brief  LPUART DMA error
  */
        
#define LPUART_DMA_TX_ERROR                 ( 1U << 31 )
#define LPUART_DMA_RX_ERROR                 ( 1U << 31 )




/** @defgroup  LPUART Private Macros
  * @{
  */
  
#define __HAL_LPUART_WRITE_TXDATA(__HANDLE__, __TXDATA__)               ((__HANDLE__)->Instance->TXDR = __TXDATA__)

#define __HAL_LPUART_READ_RXDATA(__HANDLE__, __RXDATA__)                ((__HANDLE__)->Instance->RXDR)

#define __HAL_LPUART_ENABLE_DMA(__HANDLE__)                             ((__HANDLE__)->Instance->CR |= LPUART_CR_DMA_EN)

#define __HAL_LPUART_DISABLE_DMA(__HANDLE__)                            ((__HANDLE__)->Instance->CR &= ~LPUART_CR_DMA_EN)

#define __HAL_LPUART_ENABLE_TX(__HANDLE__)                             ((__HANDLE__)->Instance->CR |= LPUART_CR_TX_EN)

#define __HAL_LPUART_DISABLE_TX(__HANDLE__)                            ((__HANDLE__)->Instance->CR &= ~LPUART_CR_TX_EN)

#define __HAL_LPUART_ENABLE_RX(__HANDLE__)                             ((__HANDLE__)->Instance->CR |= LPUART_CR_RX_EN)

#define __HAL_LPUART_DISABLE_RX(__HANDLE__)                            ((__HANDLE__)->Instance->CR &= ~LPUART_CR_RX_EN)

#define __HAL_LPUART_ENABLE_IT(__HANDLE__, __INTERRUPT__)               ((__HANDLE__)->Instance->IE |= (__INTERRUPT__) & LPUART_IT_MASK)

#define __HAL_LPUART_DISABLE_IT(__HANDLE__, __INTERRUPT__)              ((__HANDLE__)->Instance->IE &= ~((__INTERRUPT__) & LPUART_IT_MASK))

#define __HAL_LPUART_GET_FLAG(__HANDLE__, __FLAG__)                     ((__HANDLE__)->Instance->SR & ((__FLAG__) & LPUART_FLAG_MASK))

#define __HAL_LPUART_GET_IT_FLAG(__HANDLE__, __FLAG__)                  ((__HANDLE__)->Instance->SR & ((__FLAG__) & LPUART_IT_FLAG_MASK))

#define __HAL_LPUART_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)           ((__HANDLE__)->Instance->IE & ((__INTERRUPT__) & LPUART_IT_MASK))

#define __HAL_LPUART_CLEAR_FLAG(__HANDLE__, __FLAG__)                   ((__HANDLE__)->Instance->SR = ((__FLAG__) & LPUART_CLEAR_FLAG_MASK))


/** @defgroup  LPUART Private Macros
  * @{
  */
  
#define IS_LPUART_HANDLE(__HANDLE__)                    ((__HANDLE__) != NULL)

#define IS_LPUART_INSTANCE(__INSTANCE__)                ((__INSTANCE__) == LPUART1)

#define IS_LPUART_WORDLENGTH(__WORDLENGTH__)            (((__WORDLENGTH__) == LPUART_WORDLENGTH_7B)   ||\
                                                         ((__WORDLENGTH__) == LPUART_WORDLENGTH_8B))

#define IS_LPUART_STOPBITS(__STOPBITS__)                (((__STOPBITS__) == LPUART_STOPBITS_1B)   ||\
                                                         ((__STOPBITS__) == LPUART_STOPBITS_2B))

#define IS_LPUART_PARITY(__PARITY__)                    (((__PARITY__) == LPUART_PARITY_NONE)   ||\
                                                         ((__PARITY__) == LPUART_PARITY_ODD)   ||\
                                                         ((__PARITY__) == LPUART_PARITY_EVEN)   ||\
                                                         ((__PARITY__) == LPUART_PARITY_0)   ||\
                                                         ((__PARITY__) == LPUART_PARITY_1))

#define IS_LPUART_MODE(__MODE__)                        (((__MODE__) == LPUART_MODE_TX)   ||\
                                                         ((__MODE__) == LPUART_MODE_RX)   ||\
                                                         ((__MODE__) == LPUART_MODE_TXRX))

#define IS_LPUART_WAKEUPMODE(__WAKEUPMODE__)            (((__WAKEUPMODE__) == LPUART_WAKEUPMODE_NONE)   ||\
                                                         ((__WAKEUPMODE__) == LPUART_WAKEUPMODE_STARTBIT)   ||\
                                                         ((__WAKEUPMODE__) == LPUART_WAKEUPMODE_ONEBYTENOCHECK)   ||\
                                                         ((__WAKEUPMODE__) == LPUART_WAKEUPMODE_ONEBYTECHECK)   ||\
                                                         ((__WAKEUPMODE__) == LPUART_WAKEUPMODE_ADDRNOCHECK)   ||\
                                                         ((__WAKEUPMODE__) == LPUART_WAKEUPMODE_ADDRCHECK))

#define IS_LPUART_CALLBACKID(__CALLBACKID__)            (((__CALLBACKID__) == LPUART_CALLBACKID_TXCPLT)     ||\
                                                         ((__CALLBACKID__) == LPUART_CALLBACKID_TXHALFCPLT) ||\
                                                         ((__CALLBACKID__) == LPUART_CALLBACKID_TXERROR)    ||\
                                                         ((__CALLBACKID__) == LPUART_CALLBACKID_RXCPLT)     ||\
                                                         ((__CALLBACKID__) == LPUART_CALLBACKID_RXHALFCPLT) ||\
                                                         ((__CALLBACKID__) == LPUART_CALLBACKID_RXERROR)    ||\
                                                         ((__CALLBACKID__) == LPUART_CALLBACKID_WAKEUP)		||\
														 ((__CALLBACKID__) == LPUART_CALLBACKID_BCNT)		||\
														 ((__CALLBACKID__) == LPUART_CALLBACKID_IDLE))

#define IS_LPUART_CLOCKSOURCE(__CLOCKSOURCE__)         (((__CLOCKSOURCE__) == LPUART_CLOCKSOURCE_XTL)	 || \
														((__CLOCKSOURCE__) == LPUART_CLOCKSOURCE_RCL)		 || \
														((__CLOCKSOURCE__) == LPUART_CLOCKSOURCE_PCLK_DIV4)	 || \
														((__CLOCKSOURCE__) == LPUART_CLOCKSOURCE_PCLK_DIV8)	 || \
														((__CLOCKSOURCE__) == LPUART_CLOCKSOURCE_PCLK_DIV16)	 || \
														((__CLOCKSOURCE__) == LPUART_CLOCKSOURCE_PCLK_DIV32))

														
												
#define IS_LPUART_WAKEUPADDR(__WAKEUPADDR__)            ((__WAKEUPADDR__) <= 0xFFU)

#define IS_LPUART_DMASIZE(__DMASIZE__)                  ((__DMASIZE__) <= 0xFFFFU)

#define IS_LPUART_BAUDRATE(__BAUDRATE__)                (((__BAUDRATE__) >= 2U) && ((__BAUDRATE__) <= 254U))


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

void HAL_LPUART_IRQHander(LPUART_HandleTypeDef *hlpuart);
HAL_StatusTypeDef HAL_LPUART_Init(LPUART_HandleTypeDef *hlpuart);
HAL_StatusTypeDef HAL_LPUART_DeInit(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_MspInit(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_MspDeInit(LPUART_HandleTypeDef *hlpuart);
HAL_StatusTypeDef HAL_LPUART_SetBaudRate(LPUART_HandleTypeDef *hlpuart, uint32_t baudRate);
HAL_StatusTypeDef HAL_LPUART_RegisterCallback(LPUART_HandleTypeDef *hlpuart, uint32_t id, pLPUART_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_LPUART_UnRegisterCallback(LPUART_HandleTypeDef *hlpuart, uint32_t id);
HAL_StatusTypeDef HAL_LPUART_Transmit(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size, uint32_t timeout);
HAL_StatusTypeDef HAL_LPUART_Receive(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size, uint32_t timeout);
HAL_StatusTypeDef HAL_LPUART_Transmit_IT(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size);
HAL_StatusTypeDef HAL_LPUART_Receive_IT(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size);
HAL_StatusTypeDef HAL_LPUART_Transmit_DMA(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size);
HAL_StatusTypeDef HAL_LPUART_Receive_DMA(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size);
HAL_StatusTypeDef HAL_LPUART_AbortTransmit(LPUART_HandleTypeDef *hlpuart);
HAL_StatusTypeDef HAL_LPUART_AbortReceive(LPUART_HandleTypeDef *hlpuart);
uint32_t HAL_LPUART_GetTxState(LPUART_HandleTypeDef *hlpuart);
uint32_t HAL_LPUART_GetRxState(LPUART_HandleTypeDef *hlpuart);
HAL_StatusTypeDef HAL_LPUART_Receive_To_IDLEorBCNT(LPUART_HandleTypeDef *hlpuart, uint8_t *buf, uint32_t size, 
                                                LPUART_Receive_Mode_Enum rece_mode, uint32_t timeout);


void HAL_LPUART_TxEmptyCallback(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_TxCompleteCallback(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_RxCompleteCallback(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_WakeupCallback(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_DMATxCpltCallback(DMA_HandleTypeDef *hdma);
void HAL_LPUART_DMATxHalfCpltCallback(DMA_HandleTypeDef *hdma);
void HAL_LPUART_DMATxErrorCallback(DMA_HandleTypeDef *hdma);
void HAL_LPUART_DMARxCpltCallback(DMA_HandleTypeDef *hdma);
void HAL_LPUART_DMARxHalfCpltCallback(DMA_HandleTypeDef *hdma);
void HAL_LPUART_DMARxErrorCallback(DMA_HandleTypeDef *hdma);
void HAL_LPUART_IdleCallback(LPUART_HandleTypeDef *hlpuart);
void HAL_LPUART_BcntCallback(LPUART_HandleTypeDef *hlpuart);

#endif
