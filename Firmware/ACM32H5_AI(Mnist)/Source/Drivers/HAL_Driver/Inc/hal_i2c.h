/******************************************************************************
*@file  : hal_i2c.h
*@brief : Header file of I2C HAL module.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __HAL_I2C_H__
#define __HAL_I2C_H__

#include "acm32h5xx_hal_conf.h"

/** @defgroup I2C_MODE
 *  @{
 */
#define    I2C_MODE_SLAVE     (0U)
#define    I2C_MODE_MASTER    (1U)
/**
  * @}
  */

/** @defgroup CLOCK_SPEED
 *  @{
 */
#define    CLOCK_SPEED_STANDARD     (100000U)
#define    CLOCK_SPEED_FAST         (400000U)
#define    CLOCK_SPEED_FAST_PLUS    (1000000U)
/**
  * @}
  */


/** @defgroup TX_AUTO_EN
 *  @{
 */
#define    TX_AUTO_DISABLE    (0U)
#define    TX_AUTO_ENABLE     (1U)
/**
  * @}
  */


/** @defgroup STRETCH_MODE
 *  @{
 */
#define    STRETCH_MODE_ENABLE      (0U)
#define    STRETCH_MODE_DISABLE    (1U)
/**
  * @}
  */
  
/** @defgroup FILTER_ALGO_ENABLE     
 *  @{
 */
#define    FILTER_ALGO_DISABLE      (0U)
#define    FILTER_ALGO_ENABLE       (1U)   
/**
  * @}
  */

/** @defgroup SLAVE State machine
 *  @{
 */
#define    I2C_STATE_IDLE       (0U)
#define    I2C_STATE_TX_DATA    (1U)
#define    I2C_STATE_RX_DATA    (2U)    
#define    I2C_STATE_REQ_ADDR   (3U)
#define    I2C_STATE_RX_ADDR    (4U)
/**
  * @}
  */
  
 /** @defgroup I2C_Memory_Address_Size I2C Memory Address Size
  * @{
  */
#define I2C_MEMADD_SIZE_8BIT            (0U)
#define I2C_MEMADD_SIZE_16BIT           (1U)
/**
  * @}
  */
 

/* Private macros ------------------------------------------------------------*/
/** @defgroup I2C_Private_Macros I2C Private Macros
  * @{
  */
#define I2C_MEM_ADD_MSB(__ADDRESS__)                       ((uint8_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)0xFF00)) >> 8)))
#define I2C_MEM_ADD_LSB(__ADDRESS__)                       ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)0x00FF)))
 
/**
  * @brief  I2C Configuration Structure definition
  */
  
#define __HAL_I2C_GET_FLAG(__HANDLE__, __FLAG__)   (((((__HANDLE__)->Instance->SR) & (__FLAG__))  == (__FLAG__) ) ? 1 : 0) 


typedef struct
{
    uint32_t  I2C_Mode;               /* This parameter can be a value of @ref I2C_MODE */
    
    uint32_t  Tx_Auto_En;             /* This parameter can be a value of @ref TX_AUTO_EN */
    
    uint32_t  Stretch_Mode;           /* This parameter can be a value of @ref STRETCH_MODE */
    
    uint32_t  Own_Address;            /* This parameter can be a 7-bit address */
    
    uint32_t  Clock_Speed;            /* This parameter can be a value of @ref CLOCK_SPEED */ 
    
    uint32_t  filter_enable;          /* This parameter can be a value of @ref FILTER_ALGO_DISABLE */  
} I2C_InitTypeDef;

/******************************** Check I2C Parameter *******************************/
#define IS_I2C_ALL_INSTANCE(INSTANCE)      (((INSTANCE) == I2C1) || \
                                            ((INSTANCE) == I2C2) || \
                                            ((INSTANCE) == I2C3) || \
                                            ((INSTANCE) == I2C4) ) 

#define IS_I2C_ALL_MODE(I2C_MODE)    (((I2C_MODE) == I2C_MODE_SLAVE) || \
                                      ((I2C_MODE) == I2C_MODE_MASTER))

#define IS_I2C_CLOCK_SPEED(CLOCK_SPEED)    (((CLOCK_SPEED) > 0U) && ((CLOCK_SPEED) <=1000000U))

#define IS_I2C_TX_AUTO_EN(TX_AUTO_EN)      (((TX_AUTO_EN) == TX_AUTO_DISABLE) || \
                                            ((TX_AUTO_EN) == TX_AUTO_ENABLE))

#define IS_I2C_STRETCH_EN(STRETCH_EN)    (((STRETCH_EN) == STRETCH_MODE_ENABLE) || \
                                          ((STRETCH_EN) == STRETCH_MODE_DISABLE))

/**
  * @brief  I2C handle Structure definition
  */
typedef struct _I2C_HandleTypeDef
{
    I2C_TypeDef         *Instance;         /* I2C registers base address */

    I2C_InitTypeDef      Init;             /* I2C communication parameters */
    
    volatile uint32_t    state;            /* the I2C state machine */
    
    uint8_t             *Rx_Buffer;        /* I2C Rx Buffer */
    uint8_t             *Tx_Buffer;        /* I2C Tx Buffer */
    
    uint32_t             Rx_Size;          /* I2C Rx Size */
    uint32_t             Tx_Size;          /* I2C Tx Size */
    
    uint32_t             Rx_Count;         /* I2C Rx Count */
    uint32_t             Tx_Count;         /* I2C Tx Count */
#ifdef HAL_DMA_MODULE_ENABLED
    DMA_HandleTypeDef   *HDMA_Rx;          /* I2C Rx DMA handle parameters */
    DMA_HandleTypeDef   *HDMA_Tx;          /* I2C Tx DMA handle parameters */
#endif
    void (*I2C_STOPF_Callback)(struct _I2C_HandleTypeDef* hi2c);      /* I2C STOP flag interrupt callback */

}I2C_HandleTypeDef;

/* Function : HAL_I2C_IRQHandler */
void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c);

/* Function : HAL_I2C_MspInit */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);

/* Function : HAL_I2C_MspDeInit */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);

/* Function : HAL_I2C_Init */
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);

/* Function : HAL_I2C_DeInit */
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);

/* Function : HAL_I2C_Master_Transmit */
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/* Function : HAL_I2C_Master_Receive */
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/* Function : HAL_I2C_Slave_Transmit */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size, uint32_t Timeout);

/* Function : HAL_I2C_Slave_Receive */
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size, uint32_t Timeout);
 
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size);


/* Function : HAL_I2C_Slave_Receive_IT */
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);

#ifdef HAL_DMA_MODULE_ENABLED
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size);
#endif

/* Function : HAL_I2C_Mem_Write */
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/* Function : HAL_I2C_Mem_Read */
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/* Function : HAL_I2C_GetSlaveRxState */
uint8_t HAL_I2C_GetSlaveRxState(I2C_HandleTypeDef *hi2c);

/* Function : HAL_I2C_GetSlaveTxState */
uint8_t HAL_I2C_GetSlaveTxState(I2C_HandleTypeDef *hi2c);

#endif
