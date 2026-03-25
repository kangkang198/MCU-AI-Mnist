/******************************************************************************
* @file    hal_usart.h

* @brief   Header file of USART HAL module.
* @version V1.0.0
* @date    2020
******************************************************************************/
#ifndef __HAL_USART_H__
#define __HAL_USART_H__

#include "acm32h5xx_hal_conf.h"


/** @defgroup USARTEx_Word_Length USARTEx Word Length
  * @{
  */
#define USART_WORDLENGTH_5B                  (0x00000000U)                          /*!< 5-bit Word Length */
#define USART_WORDLENGTH_6B                  (USART_CR3_WLEN_0)                     /*!< 6-bit Word Length */
#define USART_WORDLENGTH_7B                  (USART_CR3_WLEN_1)                     /*!< 7-bit Word Length */
#define USART_WORDLENGTH_8B                  (USART_CR3_WLEN_0 | USART_CR3_WLEN_1)  /*!< 8-bit Word Length */
#define USART_WORDLENGTH_9B                  (USART_CR3_WLEN_2)                     /*!< 9-bit Word Length */
/**
  * @}
  */


/** @defgroup USART_Parity  USART Parity
  * @{
  */
#define USART_PARITY_NONE                    (0x00000000U)                      /*!< No parity   */
#define USART_PARITY_EVEN                    (USART_CR3_PEN | USART_CR3_EPS)    /*!< Even parity */
#define USART_PARITY_ODD                     (USART_CR3_PEN)                    /*!< Odd parity  */
#define USART_PARITY_0                       (USART_CR3_SPS | USART_CR3_PEN | USART_CR3_EPS)    /*!< 0 parity  */
#define USART_PARITY_1                       (USART_CR3_SPS | USART_CR3_PEN)                    /*!< 1 parity  */
/**
  * @}
  */


/** @defgroup USART_Stop_Bits   USART Number of Stop Bits
  * @{
  */
#define USART_STOPBITS_1                     (0x00000000U)          /*!< USART frame with 1 stop bit    */
#define USART_STOPBITS_2                     (USART_CR3_STP2)       /*!< USART frame with 2 stop bits   */
/**
  * @}
  */

#if 0
/** @defgroup USART_Hardware_Flow_Control USART Hardware Flow Control
  * @{
  */
#define USART_HWCONTROL_NONE                  (0x00000000U)        /*!< No hardware control       */
#define USART_HWCONTROL_CTS                   (0x00008000U)        /*!< Clear To Send             */
#define USART_HWCONTROL_RTS                   (0x00004000U)        /*!< Request To Send           */
#define USART_HWCONTROL_CTS_RTS               (USART_HWCONTROL_CTS | USART_HWCONTROL_RTS)    /*!< Request and Clear To Send */
/**
  * @}
  */
#endif

/** @defgroup USART_Mode USART Transfer Mode
  * @{
  */
#define USART_MODE_RX                        (USART_CR1_RXE)                        /*!< RX mode        */
#define USART_MODE_TX                        (USART_CR1_TXE)                        /*!< TX mode        */
#define USART_MODE_TX_RX                     (USART_CR1_TXE | USART_CR1_RXE)        /*!< RX and TX mode */
/**
  * @}
  */

/** @defgroup USART_Clock USART Clock
  * @{
  */
#define USART_CLOCK_DISABLE          (0x00000000U)
#define USART_CLOCK_ENABLE           (USART_CR2_CLKEN)  /*! 0x00000080 */
/**
  * @}
  */

/** @defgroup USART_Clock_Polarity USART Clock Polarity
  * @{
  */
#define USART_POLARITY_LOW           (0x00000000U)
#define USART_POLARITY_HIGH          (USART_CR2_CPOL)   /*! 0x00000400 */
/**
  * @}
  */

/** @defgroup USART_Clock_Phase USART Clock Phase
  * @{
  */
#define USART_PHASE_1EDGE            (0x00000000U)
#define USART_PHASE_2EDGE            (USART_CR2_CPHA)   /*! 0x00000200 */
/**
  * @}
  */

/** @defgroup USART_Last_Bit USART Last Bit
  * @{
  */
#define USART_LASTBIT_DISABLE        (0x00000000U)
#define USART_LASTBIT_ENABLE         (USART_CR2_LBCL)   /*! 0x00000100 */
/**
  * @}
  */

/** @defgroup USART_NACK_State USART NACK State
  * @{
  */
#define USART_NACK_ENABLE            (USART_CR2_NACK)   /*! 0x00000040 */
#define USART_NACK_DISABLE           (0x00000000U)
/**
  * @}
  */

/** @defgroup FIFO interrupt Config
  * @{
  */
#define USART_TX_FIFO_1_16             (USART_CR3_TXIFLSEL_2 | USART_CR3_TXIFLSEL_0)    /*!< Transfer 1 Data  */
#define USART_TX_FIFO_1_8              (0x00000000)                                     /*!< Transfer 2 Data  */
#define USART_TX_FIFO_1_4              (USART_CR3_TXIFLSEL_0)                           /*!< Transfer 4 Data  */
#define USART_TX_FIFO_1_2              (USART_CR3_TXIFLSEL_1)                           /*!< Transfer 8 Data  */
#define USART_TX_FIFO_3_4              (USART_CR3_TXIFLSEL_1 | USART_CR3_TXIFLSEL_0)    /*!< Transfer 12 Data */
#define USART_TX_FIFO_7_8              (USART_CR3_TXIFLSEL_2)                           /*!< Transfer 14 Data */
                                       
#define USART_RX_FIFO_1_16             (USART_CR3_RXIFLSEL_2 | USART_CR3_RXIFLSEL_0)    /*!< Receive  1 Data  */
#define USART_RX_FIFO_1_8              (0x00000000)                                     /*!< Receive  2 Data  */
#define USART_RX_FIFO_1_4              (USART_CR3_RXIFLSEL_0)                           /*!< Receive  4 Data  */
#define USART_RX_FIFO_1_2              (USART_CR3_RXIFLSEL_1)                           /*!< Receive  8 Data  */
#define USART_RX_FIFO_3_4              (USART_CR3_RXIFLSEL_1 | USART_CR3_RXIFLSEL_0)    /*!< Receive  12 Data */
#define USART_RX_FIFO_7_8              (USART_CR3_RXIFLSEL_2)                           /*!< Receive  14 Data */
/**
  * @}
  */

/** @defgroup USART_Error_Code USART Error Code
  * @{
  */
#define HAL_USART_ERROR_NONE              0x00000000U   /*!< No error            */
#define HAL_USART_ERROR_PE                0x00000001U   /*!< Parity error        */
#define HAL_USART_ERROR_NE                0x00000002U   /*!< Noise error         */
#define HAL_USART_ERROR_FE                0x00000004U   /*!< Frame error         */
#define HAL_USART_ERROR_ORE               0x00000008U   /*!< Overrun error       */
#define HAL_USART_ERROR_DMA               0x00000010U   /*!< DMA transfer error  */
/**
  * @}
  */


/*
 * @brief USART Init Structure definition
 */
typedef struct
{
    uint32_t BaudRate;                  /*!< This member configures the USART communication baud rate. */

    uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                             This parameter can be a value of @ref USARTEx_Word_Length. */

    uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                             This parameter can be a value of @ref USART_Stop_Bits. */

    uint32_t Parity;                    /*!< Specifies the parity mode. 
                                             This parameter can be a value of @ref USART_Parity. */

    uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                             This parameter can be a value of @ref USART_Mode. */
#if 0
    uint32_t HwFlowCtl;                 /*!< Specifies whether the hardware flow control mode is enabled or disabled.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control. */
#endif    
    uint32_t CLKPolarity;               /*!< Specifies the steady state of the serial clock.
                                           This parameter can be a value of @ref USART_Clock_Polarity. */

    uint32_t CLKPhase;                  /*!< Specifies the clock transition on which the bit capture is made.
                                           This parameter can be a value of @ref USART_Clock_Phase. */

    uint32_t CLKLastBit;                /*!< Specifies whether the clock pulse corresponding to the last transmitted
                                           data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                                           This parameter can be a value of @ref USART_Last_Bit. */
//ljg checkhere
#if 0
    uint32_t ClockPrescaler;            /*!< Specifies the prescaler value used to divide the USART clock source.
                                           This parameter can be a value of @ref USART_ClockPrescaler. */
#endif
}USART_InitTypeDef;

/*
 * @brief  USART handle Structure definition
 */
typedef struct
{
    USART_TypeDef            *Instance;                /*!< USART registers base address        */

    USART_InitTypeDef         Init;                    /*!< USART communication parameters      */

    uint32_t                 TxSize;                  /*!< USART Transmit parameters in interrupt  */
    __IO uint32_t            TxCount;
    uint8_t                 *TxData;
    
    uint32_t                 RxSize;                  /*!< USART Receive parameters in interrupt  */
    __IO uint32_t            RxCount; 
    uint8_t                 *RxData;  
    
    
    __IO uint8_t             TxBusy;  
    __IO uint8_t             RxBusy;  
#ifdef HAL_DMA_MODULE_ENABLED    
    DMA_HandleTypeDef       *HDMA_Tx;                 /*!< USART Tx DMA handle parameters */
    DMA_HandleTypeDef       *HDMA_Rx;                 /*!< USART Rx DMA handle parameters */ 
#endif
	__IO uint32_t           ErrorCode;                /*!<USART Error Code */

}USART_HandleTypeDef;


/** @defgroup  USART_Private_Macros
  * @{
  */
#define IS_USART_ALL_INSTANCE(INSTANCE)    (((INSTANCE) == USART1) || \
                                            ((INSTANCE) == USART2) || \
                                            ((INSTANCE) == USART3) || \
                                           ((INSTANCE) == USART4) )  

#define IS_USART_NACK_STATE(NACK)    (((NACK) == USART_NACK_ENABLE) || \
                                      ((NACK) == USART_NACK_DISABLE))

#define IS_USART_LASTBIT(LASTBIT)    (((LASTBIT) == USART_LASTBIT_DISABLE) || \
                                      ((LASTBIT) == USART_LASTBIT_ENABLE))

#define IS_USART_PHASE(CPHA)         (((CPHA) == USART_PHASE_1EDGE) || \
                                      ((CPHA) == USART_PHASE_2EDGE))

#define IS_USART_POLARITY(CPOL)      (((CPOL) == USART_POLARITY_LOW) || \
                                      ((CPOL) == USART_POLARITY_HIGH))

#define IS_USART_CLOCK(CLOCK)        (((CLOCK) == USART_CLOCK_DISABLE) || \
                                      ((CLOCK) == USART_CLOCK_ENABLE))
 

#define IS_USART_WORDLENGTH(__WORDLENGTH__)    (((__WORDLENGTH__) == USART_WORDLENGTH_5B) || \
                                               ((__WORDLENGTH__) == USART_WORDLENGTH_6B) || \
                                               ((__WORDLENGTH__) == USART_WORDLENGTH_7B) || \
                                               ((__WORDLENGTH__) == USART_WORDLENGTH_8B) || \
                                               ((__WORDLENGTH__) == USART_WORDLENGTH_9B))

#define IS_USART_STOPBITS(__STOPBITS__)    (((__STOPBITS__) == USART_STOPBITS_1) || \
                                           ((__STOPBITS__) == USART_STOPBITS_2))

#define IS_USART_PARITY(__PARITY__)        (((__PARITY__) == USART_PARITY_NONE) || \
                                           ((__PARITY__) == USART_PARITY_EVEN) || \
                                           ((__PARITY__) == USART_PARITY_ODD))


#define IS_USART_MODE(MODE)          ((((MODE) & (~((uint32_t)USART_MODE_TX_RX))) == 0x00U) && ((MODE) != 0x00U))

//ljg checkhere
#define IS_USART_BAUDRATE(BAUDRATE)  ((BAUDRATE) <= 12500000U)
/*
//ljg
//#define IS_USART_MODE(__MODE__)            (((__MODE__) == USART_MODE_RX)          || \
//                                           ((__MODE__) == USART_MODE_TX)          || \
//                                           ((__MODE__) == USART_MODE_TX_RX)       || \
//                                           ((__MODE__) == USART_MODE_HALF_DUPLEX))
                                           
//#define IS_USART_HARDWARE_FLOW_CONTROL(__CONTROL__)    (((__CONTROL__) == USART_HWCONTROL_NONE) || \
//                                                       ((__CONTROL__) == USART_HWCONTROL_RTS)  || \
//                                                       ((__CONTROL__) == USART_HWCONTROL_CTS)  || \
//                                                       ((__CONTROL__) == USART_HWCONTROL_CTS_RTS))
                                                       
//#define USART_7BIT_ADDR_MSK                  £¨0x80£©
//#define IS_USART_7BIT_ADDR_MODE(addr)        ((addr & 0x80) == 0x80)
*/                                                   
                                                       
/** @brief  Enable USART
  * @param  __HANDLE__ specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_ENABLE(__HANDLE__)               ((__HANDLE__)->Instance->CR1 |=  USART_CR1_USARTEN)

/** @brief  Disable USART
  * @param  __HANDLE__ specifies the USART Handle.
  * @retval None
  */
#define __HAL_USART_DISABLE(__HANDLE__)              ((__HANDLE__)->Instance->CR1 &=  ~USART_CR1_USARTEN)


#define __HAL_USART_GET_FLAG(__HANDLE__, __FLAG__)      (((__HANDLE__)->Instance->ISR & (__FLAG__)) == (__FLAG__))



#define CLEAR_STATUS(reg, flag)     WRITE_REG(reg, flag)


#define __USART_TXI_FIFO_LEVEL_SET(fifo_level)      MODIFY_REG(husart->Instance->CR3, USART_CR3_TXIFLSEL_Msk, fifo_level); 

#define __USART_RXI_FIFO_LEVEL_SET(fifo_level)      MODIFY_REG(husart->Instance->CR3, USART_CR3_RXIFLSEL_Msk, fifo_level);  
/**
  * @}
  */

/* HAL_USART_IRQHandler */
void HAL_USART_IRQHandler(USART_HandleTypeDef *huart);

/* HAL_USART_MspInit */
void HAL_USART_MspInit(USART_HandleTypeDef *huart);

/* HAL_USART_Init */
HAL_StatusTypeDef HAL_USART_Init(USART_HandleTypeDef *huart);

/* HAL_USART_DeInit */
HAL_StatusTypeDef HAL_USART_DeInit(USART_HandleTypeDef *huart);

/* HAL_USART_GetState */
HAL_StatusTypeDef HAL_USART_GetState(USART_HandleTypeDef *huart);

/* HAL_USART_GetError*/
uint32_t HAL_USART_GetError(USART_HandleTypeDef *huart);

/* HAL_USART_Abort*/
HAL_StatusTypeDef HAL_USART_Abort(USART_HandleTypeDef *huart);

/* HAL_USART_DMAPause */
HAL_StatusTypeDef HAL_USART_DMAPause(USART_HandleTypeDef *huart);

/* HAL_USART_DMAResume */
HAL_StatusTypeDef HAL_USART_DMAResume(USART_HandleTypeDef *huart);


HAL_StatusTypeDef HAL_USART_DMAStop(USART_HandleTypeDef *huart);

/* HAL_USART_Transmit */
HAL_StatusTypeDef HAL_USART_Transmit(USART_HandleTypeDef *huart, uint8_t *buf, uint32_t size, uint32_t timeout);

/* HAL_USART_Receive */
HAL_StatusTypeDef HAL_USART_Receive(USART_HandleTypeDef *huart, uint8_t *buf, uint32_t size, uint32_t timeout);

/* HAL_USART_Transmit_IT */
HAL_StatusTypeDef HAL_USART_Transmit_IT(USART_HandleTypeDef *huart, uint8_t *buf, uint32_t size);

/* HAL_USART_Receive_IT */
HAL_StatusTypeDef HAL_USART_Receive_IT(USART_HandleTypeDef *huart, uint8_t *buf, uint32_t size);

/* HAL_USART_Transmit_DMA */
HAL_StatusTypeDef HAL_USART_Transmit_DMA(USART_HandleTypeDef *huart, uint8_t *buf, uint32_t size);

/* HAL_USART_Receive_DMA */
HAL_StatusTypeDef HAL_USART_Receive_DMA(USART_HandleTypeDef *huart, uint8_t *buf, uint32_t size);

void HAL_USART_SetDebugUart(USART_TypeDef *USARTx);

#endif
