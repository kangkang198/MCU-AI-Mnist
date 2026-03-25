/******************************************************************************
*@file  : hal_spi.h
*@brief : Header file of SPI HAL module.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __HAL_SPI_H__
#define __HAL_SPI_H__

#include  "hal.h" 


/** @defgroup SLAVE State machine
 *  @{
 */
#define    SPI_RX_STATE_IDLE         (0U)
#define    SPI_RX_STATE_RECEIVING    (1U)
#define    SPI_TX_STATE_IDLE         (0U)
#define    SPI_TX_STATE_SENDING      (1U)
/**
  * @}
  */


/** @defgroup SPI_MODE
 *  @{
 */
#define    SPI_MODE_SLAVE     (0U)
#define    SPI_MODE_MASTER    (1U)
/**
  * @}
  */


/** @defgroup SPI_WORK_MODE
  * @{
  */
#define SPI_WORK_MODE_0    (0x00000000)
#define SPI_WORK_MODE_1    (0x00000004)
#define SPI_WORK_MODE_2    (0x00000008)
#define SPI_WORK_MODE_3    (0x0000000C)
/**
  * @}
  */


/** @defgroup SPI_CLOCK_PHASE SPI Clock Phase
  * @{
  */
#define SPI_PHASE_1EDGE    (0U)
#define SPI_PHASE_2EDGE    (1U)
/**
  * @}
  */


/** @defgroup X_MODE SPI Clock Phase
  * @{
  */
#define SPI_1X_MODE    (0x00000000)
#define SPI_2X_MODE    (0x00000020)
#define SPI_4X_MODE    (0x00000040)
/**
  * @}
  */


/** @defgroup SPI_MSB_LSB_FIRST
  * @{
  */
#define SPI_FIRSTBIT_MSB    (0U)
#define SPI_FIRSTBIT_LSB    (1U)
/**
  * @}
  */


/** @defgroup BAUDRATE_PRESCALER
  * @{
  */
#define SPI_BAUDRATE_PRESCALER_2      (2U)  
#define SPI_BAUDRATE_PRESCALER_4      (4U)
#define SPI_BAUDRATE_PRESCALER_8      (8U)
#define SPI_BAUDRATE_PRESCALER_16     (16U)
#define SPI_BAUDRATE_PRESCALER_32     (32U)
#define SPI_BAUDRATE_PRESCALER_64     (64U)
#define SPI_BAUDRATE_PRESCALER_128    (128U)
#define SPI_BAUDRATE_PRESCALER_254    (254U)
/**
  * @}
  */

/** @defgroup MASTER_SSHIFT
  * @{
  */
#define SPI_MASTER_SSHIFT_NONE      (00000000U)  
#define SPI_MASTER_SSHIFT_1_HCLK    (SPI_RX_CTL_SSHIFT_0)
#define SPI_MASTER_SSHIFT_2_HCLK    (SPI_RX_CTL_SSHIFT_1)
#define SPI_MASTER_SSHIFT_3_HCLK    (SPI_RX_CTL_SSHIFT_1 | SPI_RX_CTL_SSHIFT_0)
/**
  * @}
  */
  
/** @defgroup SPI_SLAVE_SOFT_CS
  * @{
  */
#define SPI_SLAVE_SOFT_CS_DISABLE          (0U)
#define SPI_SLAVE_SOFT_CS_ENABLE           (1U)
/**
  * @}
  */

/** @defgroup SPI Memory map mode(XIP) defitions
  * @{
  */  
#define CMD_MODE_x1	        (0)
#define CMD_MODE_x2	        (1)
#define CMD_MODE_x4	        (2)

#define ADDR_MODE_x1	    (0)
#define ADDR_MODE_x2	    (1)
#define ADDR_MODE_x4	    (2)

#define DATA_MODE_x1	    (0)
#define DATA_MODE_x2	    (1)
#define DATA_MODE_x4	    (2)

#define ALTER_BYTE_MODE_x1	(0)
#define ALTER_BYTE_MODE_x2	(1)
#define ALTER_BYTE_MODE_x4	(2)

#define ADDR_SIZE_8	        (0)
#define ADDR_SIZE_16	    (1)
#define ADDR_SIZE_24	    (2)
#define ADDR_SIZE_32	    (3)

#define ALTER_BYTE_SIZE_8	(0)
#define ALTER_BYTE_SIZE_16	(1)
#define ALTER_BYTE_SIZE_24	(2)
#define ALTER_BYTE_SIZE_32	(3)  

#define DUMMY_CYCLE_1	    (0)
#define DUMMY_CYCLE_2	    (1)
#define DUMMY_CYCLE_3	    (2)
#define DUMMY_CYCLE_4	    (3)
#define DUMMY_CYCLE_5	    (4)
#define DUMMY_CYCLE_6	    (5)
#define DUMMY_CYCLE_7	    (6)
#define DUMMY_CYCLE_8	    (7)
/**
  * @}
  */
  
/**
  * @brief  SPI Configuration Structure definition
  */
typedef struct
{
    uint32_t  SPI_Mode;              /* This parameter can be a value of @ref SPI_MODE */
    
    uint32_t  SPI_Work_Mode;         /* This parameter can be a value of @ref SPI_WORK_MODE */
    
    uint32_t  X_Mode;                /* This parameter can be a value of @ref X_MODE */
    
    uint32_t  First_Bit;             /* This parameter can be a value of @ref SPI_MSB_LSB_FIRST */
    
    uint32_t  Slave_SofteCs_En;      /* SPI Slave Soft CS Select management. This parameter can be a value of @ref SPI_SLAVE_SOFT_CS */
    
    uint32_t  BaudRate_Prescaler;    /* This parameter can be a value of @ref BAUDRATE_PRESCALER */   
    
    uint32_t  Master_SShift;         /* The master delay n hclk to sample data. This parameter can be a value of @ref MASTER_SSHIFT */ 

}SPI_InitTypeDef;

typedef struct
{
    
    SPI_MEM_CMD_t MemCMD;
    SPI_MEMO_ACC_t MemACC;    
    uint32_t MemAlterByte;
    uint32_t MemCSTimeout;
    
}SPI_MemACCInitTypeDef;

/******************************** Check SPI Parameter *******************************/
/******************************** SPI Instances *******************************/
#define IS_SPI_ALL_INSTANCE(INSTANCE)     (((INSTANCE) == SPI1) || \
                                           ((INSTANCE) == SPI2) || \
                                           ((INSTANCE) == SPI3) || \
                                           ((INSTANCE) == SPI4) || \
                                           ((INSTANCE) == SPI5) || \
                                           ((INSTANCE) == SPI6) || \
                                           ((INSTANCE) == SPI7) || \
                                           ((INSTANCE) == SPI8))  

#define IS_SPI_ALL_MODE(SPI_Mode)          (((SPI_Mode) == SPI_MODE_SLAVE) || \
                                            ((SPI_Mode) == SPI_MODE_MASTER))

#define IS_SPI_WORK_MODE(WORK_MODE)        (((WORK_MODE) == SPI_WORK_MODE_0) || \
                                            ((WORK_MODE) == SPI_WORK_MODE_1) || \
                                            ((WORK_MODE) == SPI_WORK_MODE_2) || \
                                            ((WORK_MODE) == SPI_WORK_MODE_3))

#define IS_SPI_X_MODE(X_MODE)              (((X_MODE) == SPI_1X_MODE) || \
                                            ((X_MODE) == SPI_2X_MODE) || \
                                            ((X_MODE) == SPI_4X_MODE))

#define IS_SPI_INSTANCE_4X_MODE(INSTANCE) (((INSTANCE) == SPI1) || \
                                           ((INSTANCE) == SPI2) || \
                                           ((INSTANCE) == SPI3) || \
                                           ((INSTANCE) == SPI4) || \
                                           ((INSTANCE) == SPI5) || \
                                           ((INSTANCE) == SPI6) || \
                                           ((INSTANCE) == SPI7) || \
                                           ((INSTANCE) == SPI8))

#define IS_SPI_INSTANCE_SLAVE_MODE(INSTANCE)  (((INSTANCE) == SPI1) || \
                                               ((INSTANCE) == SPI2) || \
                                               ((INSTANCE) == SPI3) || \
                                               ((INSTANCE) == SPI4) || \
											   ((INSTANCE) == SPI5) || \
											   ((INSTANCE) == SPI6) || \
                                               ((INSTANCE) == SPI7) || \
                                               ((INSTANCE) == SPI8))  
                                               
#define IS_SPI_MEM_INSTANCE(INSTANCE)         (((INSTANCE) == SPI4) || \
                                               ((INSTANCE) == SPI7) || \
                                               ((INSTANCE) == SPI8))                                                 

#define IS_SPI_FIRST_BIT(FIRST_BIT)        (((FIRST_BIT) == SPI_FIRSTBIT_MSB) || \
                                            ((FIRST_BIT) == SPI_FIRSTBIT_LSB))

#define IS_SPI_BAUDRATE_PRESCALER(BAUDRATE)    (((BAUDRATE) == SPI_BAUDRATE_PRESCALER_2)   || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_4)    || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_8)   || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_16)  || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_32)  || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_64)  || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_128) || \
                                                ((BAUDRATE) == SPI_BAUDRATE_PRESCALER_254))
                                                
                                                
#define IS_SPI_CS_SEL(CSx)                    (((CSx) == SPI_CS_CS0) || \
                                               ((CSx) == SPI_CS_CS1) || \
											   ((CSx) == SPI_CS_CS2) || \
											   ((CSx) == SPI_CS_CS3) || \
                                               ((CSx) == SPI_CS_CS4))
                                               
#define __SPI_CLEAR_FLAG(SPIx, FLAG)    (SPIx)->STATUS = (FLAG)

#define __SPI_RXFIFO_RESET(SPIx) do{ \
    SET_BIT((SPIx)->RX_CTL, SPI_RX_CTL_FIFO_RESET); \
    CLEAR_BIT((SPIx)->RX_CTL, SPI_RX_CTL_FIFO_RESET); \
}while(0);

#define __SPI_TXFIFO_RESET(SPIx) do{ \
    SET_BIT((SPIx)->TX_CTL, SPI_TX_CTL_FIFO_RESET); \
    CLEAR_BIT((SPIx)->TX_CTL, SPI_TX_CTL_FIFO_RESET); \
}while(0);


#define __HAL_SPI_TRANSSTART_CS_LOW(hspi)   (hspi)->Instance->CS |= (hspi)->CSx
#define __HAL_SPI_CS_RELEASE(hspi)          (hspi)->Instance->CS &= ~((hspi)->CSx)

#define  __SPI_MEMACC_ENABLE(SPIx)          (SPIx)->MEMO_ACC.acc_en = 1
#define  __SPI_MEMACC_DISABLE(SPIx)         (SPIx)->MEMO_ACC.acc_en = 0

#define __SPI_MEMACC_INSTRONCE_CLEAR(SPIx)  (SPIx)->MEMO_ACC.instr_once_clr = 1

/**
  * @brief  SPI handle Structure definition
  */
typedef struct
{
    SPI_TypeDef         *Instance;         /* SPI registers base address */

    SPI_InitTypeDef     Init;             /* SPI communication parameters */
    
    uint8_t             CSx;
    
    volatile uint32_t   RxState;          /* SPI state machine */
    volatile uint32_t   TxState;          /* SPI state machine */
    
    uint8_t             *Rx_Buffer;        /* SPI Rx Buffer */
    uint8_t             *Tx_Buffer;        /* SPI Tx Buffer */
    
    uint32_t            Rx_Size;          /* SPI Rx Size */
    uint32_t            Tx_Size;          /* SPI Tx Size */
    
    uint32_t            Rx_Count;         /* SPI RX Count */
    uint32_t            Tx_Count;         /* SPI TX Count */
    
    bool                KeepCS;           /* whether CS need kept at the end of transfer in IT mode. true for keeping */
#ifdef HAL_DMA_MODULE_ENABLED   
    DMA_HandleTypeDef   *HDMA_Rx;          /* SPI Rx DMA handle parameters */
    DMA_HandleTypeDef   *HDMA_Tx;          /* SPI Tx DMA handle parameters */
#endif
}SPI_HandleTypeDef;


void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi);

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);

HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi);

HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_SPI_TransmitKeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_ReceiveKeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size);

HAL_StatusTypeDef HAL_SPI_Transmit_IT_KeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_IT_KeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size);

#ifdef HAL_DMA_MODULE_ENABLED
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size);
#endif

HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_SPI_Wire_Config(SPI_HandleTypeDef *hspi, uint32_t X_Mode);

uint8_t HAL_SPI_GetTxState(SPI_HandleTypeDef *hspi);
uint8_t HAL_SPI_GetRxState(SPI_HandleTypeDef *hspi);

HAL_StatusTypeDef HAL_SPI_WaitTxTimeout(SPI_HandleTypeDef *hspi, uint32_t timeout);
HAL_StatusTypeDef HAL_SPI_WaitRxTimeout(SPI_HandleTypeDef *hspi, uint32_t timeout);
HAL_StatusTypeDef HAL_SPI_Switch_CS(SPI_HandleTypeDef *hspi, uint8_t CSx);

HAL_StatusTypeDef HAL_SPI_MEMACCInit(SPI_HandleTypeDef* hspi, SPI_MemACCInitTypeDef* MemACCParam);

HAL_StatusTypeDef HAL_SPI_TransmitNoneBatch(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_TransmitNoneBatchKeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_SPI_ReceiveNoneBatch(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_ReceiveNoneBatchKeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout);
#endif





