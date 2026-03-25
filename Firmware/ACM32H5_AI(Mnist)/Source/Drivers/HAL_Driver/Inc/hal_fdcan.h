#ifndef __HAL_FDCAN_H__
#define __HAL_FDCAN_H__

/* Define to prevent recursive inclusion -------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "acm32h5xx_hal_conf.h"

typedef enum
{
  HAL_FDCAN_STATE_RESET      = 0x00U, /*!< FDCAN not yet initialized or disabled */
  HAL_FDCAN_STATE_READY      = 0x01U, /*!< FDCAN initialized and ready for use   */
  HAL_FDCAN_STATE_BUSY       = 0x02U, /*!< FDCAN process is ongoing              */
  HAL_FDCAN_STATE_ERROR      = 0x03U  /*!< FDCAN error state                     */
} HAL_FDCAN_StateTypeDef;

/**
  * @brief FDCAN Init structure definition
  */
typedef struct
{
    uint32_t Mode;                         /*!< Specifies the FDCAN mode.
                                              This parameter can be a value of @ref FDCAN_operating_mode   */
    
    uint32_t FrameISOType;                 /*!< Specifies the FDCAN frame ISO Type.
                                              This parameter can be a value of @ref FDCAN_frame_ISOType     */

    uint32_t RxBufOverFlowMode;            /*!< Specifies the FDCAN Receive buffer Overflow Mode.
                                              This parameter can be a value of @ref FDCAN_Rx_FIFO_operation_mode.   */
    FunctionalState AutoRetransmission;    /*!< Enable or disable the automatic retransmission mode.
                                              This parameter can be set to ENABLE or DISABLE               */

    uint32_t NominalPrescaler;             /*!< Specifies the value by which the oscillator frequency is
                                              divided for generating the nominal bit time quanta. */

    uint32_t NominalSyncJumpWidth;         /*!< Specifies the maximum number of time quanta the FDCAN
                                              hardware is allowed to lengthen or shorten a bit to perform
                                              resynchronization. */

    uint32_t NominalTimeSeg1;              /*!< Specifies the number of time quanta in Bit Segment 1.  */

    uint32_t NominalTimeSeg2;              /*!< Specifies the number of time quanta in Bit Segment 2.  */

    uint32_t DataPrescaler;                /*!< Specifies the value by which the oscillator frequency is
                                              divided for generating the data bit time quanta.     */

    uint32_t DataSyncJumpWidth;            /*!< Specifies the maximum number of time quanta the FDCAN
                                              hardware is allowed to lengthen or shorten a data bit to
                                              perform resynchronization.              */

    uint32_t DataTimeSeg1;                 /*!< Specifies the number of time quanta in Data Bit Segment 1.    */

    uint32_t DataTimeSeg2;                 /*!< Specifies the number of time quanta in Data Bit Segment 2. */

} FDCAN_InitTypeDef;


/**
  * @brief  FDCAN filter structure definition
  */
typedef struct
{
    uint32_t IdType;           /*!< Specifies the identifier type.
                                  This parameter can be a value of @ref FDCAN_id_type       */
    uint32_t FilterIndex;      /*!< Specifies the filter which will be initialized.
                                  This parameter must be a number less than NR_OF_ACF - 1 */    
    uint32_t FilerMask;
    
    uint32_t FilerCode;

    uint32_t FilterType;       /*!< Specifies the filter type.
                                  This parameter can be a value of @ref FDCAN_filter_type.
                                  The value FDCAN_EXT_FILTER_RANGE_NO_EIDM is permitted
                                  only when IdType is FDCAN_EXTENDED_ID.
                                  This parameter is ignored if FilterConfig is set to
                                  FDCAN_FILTER_TO_RXBUFFER                                  */
} FDCAN_FilterTypeDef;


typedef enum
{
    FDCAN_FILTER_TYPE0 = 0,
    FDCAN_FILTER_TYPE1,
    FDCAN_FILTER_TYPE2,
    FDCAN_FILTER_TYPE3,
}FDCAN_Filter_enum;

typedef union
{
    struct
    {
        uint32_t r0:1;
        uint32_t RTR:1;
        uint32_t IDE:1;
        uint32_t EXTID0_17:18;
        uint32_t id:11;
    }b;
    
    struct
    {
        uint32_t r0:1;
        uint32_t RTR:1;
        uint32_t IDE:1;
        uint32_t id:29;
    }ext;
    
    uint32_t w;
}FDCAN_Filter32_Map_u;

typedef union
{
    struct
    {
        uint16_t EXTID15_17:3;
        uint16_t IDE:1;
        uint16_t RTR:1;
        uint16_t id:11;
    }b;
    uint16_t hw;
}FDCAN_Filter16_Map_u;

typedef union
{
    struct
    {
        FDCAN_Filter32_Map_u code32;    //acode;
        FDCAN_Filter32_Map_u mask32;    //amask;
    }type0;
    
    struct
    {
        FDCAN_Filter32_Map_u code32;
        FDCAN_Filter32_Map_u code32_2;
    }type1;
    
    struct
    {
        FDCAN_Filter16_Map_u code16;
        FDCAN_Filter16_Map_u mask16;        
        FDCAN_Filter16_Map_u code16_2;
        FDCAN_Filter16_Map_u mask16_2;
    }type2;
    
    struct
    {
        FDCAN_Filter16_Map_u code16;
        FDCAN_Filter16_Map_u code16_2;        
        FDCAN_Filter16_Map_u code16_3;
        FDCAN_Filter16_Map_u code16_4;
    }type3;
    
}FDCAN_Filter_u;

typedef struct 
{
    uint32_t            FilterIndex;
    FDCAN_Filter_enum   FilterType;
    FDCAN_Filter_u      Filter;
    
}FDCAN_NewFilterTypeDef;


typedef union
{
    struct{
        __IO uint32_t ID:29;
        __IO uint32_t RSV:2;
        __IO uint32_t TTSEN:1;
    }b;
    __IO uint32_t w;
}FDCAN_TX_ID_u;

typedef union
{
    struct{
        __IO uint32_t DLC:4;
        __IO uint32_t BRS:1;
        __IO uint32_t FDF:1;
        __IO uint32_t RTR:1;
        __IO uint32_t IDE:1;
        __IO uint32_t RSV0:8;
        __IO uint32_t RSV1:8;
        __IO uint32_t RSV2:8;
        
    }b;
    __IO uint32_t w;
}FDCAN_TX_FrameInfo_u;


typedef union
{
    struct{
        __IO uint32_t ID:29;
        __IO uint32_t RSV:2;
        __IO uint32_t ESI:1;    //error state indicator
    }b;
    __IO uint32_t w;
}FDCAN_RX_ID_u;


typedef union
{
    struct{
        __IO uint32_t DLC:4;
        __IO uint32_t BRS:1;
        __IO uint32_t FDF:1;
        __IO uint32_t RTR:1;
        __IO uint32_t IDE:1;
        __IO uint32_t RSV0:4;
        __IO uint32_t TX:1;
        __IO uint32_t KOER:3;
        __IO uint32_t CycleTime:16;              
    }b;
    __IO uint32_t w;
}FDCAN_RX_FrameInfo_u;


typedef fdcan_ecc_u FDCAN_ErrorInfo_u;

/**
  * @brief  FDCAN Tx header structure definition
  */
typedef struct
{
    FDCAN_TX_ID_u ID;
    
    FDCAN_TX_FrameInfo_u FrameInfo;

} FDCAN_TxHeaderTypeDef;

/**
  * @brief  FDCAN Rx header structure definition
  */
typedef struct
{
    FDCAN_RX_ID_u ID;            
    
    FDCAN_RX_FrameInfo_u FrameInfo;
        
    uint32_t RxTimestampLow;
    
    uint32_t RxTimestampHigh;

} FDCAN_RxHeaderTypeDef;


typedef struct{
    uint32_t tts_h;
    uint32_t tts_l;    
}FDCAN_TTSTypeDef;

/**
  * @brief  FDCAN Trigger structure definition
  */
typedef struct
{
//  uint32_t TriggerIndex;  /*!< Specifies the trigger which will be configured.
//                               This parameter must be a number between 0 and 63                                 */

    uint32_t TimeMark;      /*!< Specifies the cycle time for which the trigger becomes active.
                               This parameter must be a number between 0 and 0xFFFF                             */

    uint32_t RepeatFactor;  /*!< Specifies the trigger repeat factor.
                               This parameter can be a value of @ref FDCAN_TT_Repeat_Factor                     */

    uint32_t StartCycle;    /*!< Specifies the index of the first cycle in which the trigger becomes active.
                               This parameter is ignored if RepeatFactor is set to FDCAN_TT_REPEAT_EVERY_CYCLE.
                               This parameter must be a number between 0 and RepeatFactor                       */

    uint32_t TriggerType;   /*!< Specifies the trigger type.
                               This parameter can be a value of @ref FDCAN_TT_Trigger_Type                      */

    uint32_t TTPtr;           /*!< Specifies the index of the Tx buffer for which the trigger is valid.
                               This parameter can be a value of @ref FDCAN_Tx_location.
                               This parameter is taken in consideration only if the trigger is configured for
                               transmission.                                                                    */

    uint32_t FilterIndex;   /*!< Specifies the filter for which the trigger is valid.
                               This parameter is taken in consideration only if the trigger is configured for
                               reception.
                               This parameter must be a number between:
                                - 0 and 127, if FilterType is FDCAN_STANDARD_ID
                                - 0 and 63, if FilterType is FDCAN_EXTENDED_ID                                  */
                                
    uint32_t TxEnWindow;    /* transmit enalbe window */

} FDCAN_TriggerTypeDef;


/**
  * @brief  FDCAN handle structure definition
  */
typedef struct __FDCAN_HandleTypeDef
{
  FDCAN_GlobalTypeDef               *Instance;        /*!< Register base address     */

//  TTCAN_TypeDef               *ttcan;           /*!< TT register base address  */

  FDCAN_InitTypeDef           Init;             /*!< FDCAN required parameters */

//  FDCAN_MsgRamAddressTypeDef  msgRam;           /*!< FDCAN Message RAM blocks  */

  uint32_t                    LatestTxFifoQRequest; /*!< FDCAN Tx buffer index
                                               of latest Tx FIFO/Queue request */

  __IO HAL_FDCAN_StateTypeDef State;            /*!< FDCAN communication state */

  HAL_LockTypeDef             Lock;             /*!< FDCAN locking object      */

  __IO uint32_t               ErrorCode;        /*!< FDCAN Error code          */
    
    __IO FDCAN_ErrorInfo_u    CANErrorInfo;

#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
  void (* ClockCalibrationCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t ClkCalibrationITs);         /*!< FDCAN Clock Calibration callback          */
  void (* TxEventFifoCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t TxEventFifoITs);                 /*!< FDCAN Tx Event Fifo callback              */
  void (* RxFifo0Callback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);                         /*!< FDCAN Rx Fifo 0 callback                  */
  void (* RxFifo1Callback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs);                         /*!< FDCAN Rx Fifo 1 callback                  */
  void (* TxFifoEmptyCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                          /*!< FDCAN Tx Fifo Empty callback              */
  void (* TxBufferCompleteCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes);             /*!< FDCAN Tx Buffer complete callback         */
  void (* TxBufferAbortCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes);                /*!< FDCAN Tx Buffer abort callback            */
  void (* RxBufferNewMessageCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                   /*!< FDCAN Rx Buffer New Message callback      */
  void (* HighPriorityMessageCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                  /*!< FDCAN High priority message callback      */
  void (* TimestampWraparoundCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                  /*!< FDCAN Timestamp wraparound callback       */
  void (* TimeoutOccurredCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                      /*!< FDCAN Timeout occurred callback           */
  void (* ErrorCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                                /*!< FDCAN Error callback                      */
  void (* ErrorStatusCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs);                 /*!< FDCAN Error status callback               */
  void (* TT_ScheduleSyncCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t TTSchedSyncITs);             /*!< FDCAN T Schedule Synchronization callback */
  void (* TT_TimeMarkCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t TTTimeMarkITs);                  /*!< FDCAN TT Time Mark callback               */
  void (* TT_StopWatchCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t SWTime, uint32_t SWCycleCount); /*!< FDCAN TT Stop Watch callback              */
  void (* TT_GlobalTimeCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t TTGlobTimeITs);                /*!< FDCAN TT Global Time callback             */

  void (* MspInitCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                              /*!< FDCAN Msp Init callback                   */
  void (* MspDeInitCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                            /*!< FDCAN Msp DeInit callback                 */
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

#ifdef HAL_DMA_MODULE_ENABLED   
    DMA_HandleTypeDef   *HDMA_Rx;          /* SPI Rx DMA handle parameters */
    DMA_HandleTypeDef   *HDMA_Tx;          /* SPI Tx DMA handle parameters */
#endif

} FDCAN_HandleTypeDef;


/* Transmition buffer type enum */
typedef enum {
    FDCAN_TRANSMIT_PTB = 0,        
    FDCAN_TRANSMIT_STB_ONE = 1,
    FDCAN_TRANSMIT_STB_ALL = 2
}TransmitType_enum;

typedef enum {
    FDCAN_ABORT_PTB = 0,        
    FDCAN_ABORT_STB = 1,
}TransmitAbortType_enum;


typedef enum {
    FDCAN_RXBUF_EMPTY = 0,
    FDCAN_RXBUF_LESS_AFWL = 1,
    FDCAN_RXBUF_AFWL = 2,
    FDCAN_RXBUF_FULL = 3,
    FDCAN_RXBUF_OV,
}FDCAN_RXBUF_FILL_STATE_enum;

typedef enum {
    FDCAN_TXBUF_EMPTY = 0,
    FDCAN_TXBUF_HALF_LESSHF = 1,
    FDCAN_TXBUF_MORE_HALF = 2,
    FDCAN_TXBUF_FULL = 3,
}FDCAN_TXBUF_FILL_STATE_enum;

typedef enum
{
    FDCAN_MAC_NONE_ERR = 0,
    FDCAN_MAC_BIT_ERR,
    FDCAN_MAC_FORM_ERR,
    FDCAN_MAC_STUFF_ERR,
    FDCAN_MAC_ACK_ERR,
    FDCAN_MAC_CRC_ERR,
    FDCAN_MAC_OTHER_ERRS
}FDCAN_MAC_ERR_enum;


#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
/**
  * @brief  HAL FDCAN common Callback ID enumeration definition
  */
typedef enum
{
  HAL_FDCAN_TX_FIFO_EMPTY_CB_ID        = 0x00U, /*!< FDCAN Tx Fifo Empty callback ID         */
  HAL_FDCAN_RX_BUFFER_NEW_MSG_CB_ID    = 0x01U, /*!< FDCAN Rx buffer new message callback ID */
  HAL_FDCAN_HIGH_PRIO_MESSAGE_CB_ID    = 0x02U, /*!< FDCAN High priority message callback ID */
  HAL_FDCAN_TIMESTAMP_WRAPAROUND_CB_ID = 0x03U, /*!< FDCAN Timestamp wraparound callback ID  */
  HAL_FDCAN_TIMEOUT_OCCURRED_CB_ID     = 0x04U, /*!< FDCAN Timeout occurred callback ID      */
  HAL_FDCAN_ERROR_CALLBACK_CB_ID       = 0x05U, /*!< FDCAN Error callback ID                 */

  HAL_FDCAN_MSPINIT_CB_ID              = 0x06U, /*!< FDCAN MspInit callback ID               */
  HAL_FDCAN_MSPDEINIT_CB_ID            = 0x07U, /*!< FDCAN MspDeInit callback ID             */

} HAL_FDCAN_CallbackIDTypeDef;

/**
  * @brief  HAL FDCAN Callback pointer definition
  */
typedef  void (*pFDCAN_CallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan);                                                     /*!< pointer to a common FDCAN callback function                    */
typedef  void (*pFDCAN_ClockCalibrationCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t ClkCalibrationITs);         /*!< pointer to Clock Calibration FDCAN callback function           */
typedef  void (*pFDCAN_TxEventFifoCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t TxEventFifoITs);                 /*!< pointer to Tx event Fifo FDCAN callback function               */
typedef  void (*pFDCAN_RxFifo0CallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);                         /*!< pointer to Rx Fifo 0 FDCAN callback function                   */
typedef  void (*pFDCAN_RxFifo1CallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs);                         /*!< pointer to Rx Fifo 1 FDCAN callback function                   */
typedef  void (*pFDCAN_TxBufferCompleteCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes);             /*!< pointer to Tx Buffer complete FDCAN callback function          */
typedef  void (*pFDCAN_TxBufferAbortCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes);                /*!< pointer to Tx Buffer abort FDCAN callback function             */
typedef  void (*pFDCAN_ErrorStatusCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs);                 /*!< pointer to Error Status callback function                      */
typedef  void (*pFDCAN_TT_ScheduleSyncCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t TTSchedSyncITs);             /*!< pointer to TT Schedule Synchronization FDCAN callback function */
typedef  void (*pFDCAN_TT_TimeMarkCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t TTTimeMarkITs);                  /*!< pointer to TT Time Mark FDCAN callback function                */
typedef  void (*pFDCAN_TT_StopWatchCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t SWTime, uint32_t SWCycleCount); /*!< pointer to TT Stop Watch FDCAN callback function               */
typedef  void (*pFDCAN_TT_GlobalTimeCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t TTGlobTimeITs);                /*!< pointer to TT Global Time FDCAN callback function              */
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Constants FDCAN Exported Constants
  * @{
  */
  
#define NR_OF_ACF   (16)

/** @defgroup HAL_FDCAN_Error_Code HAL FDCAN Error Code
  * @{
  */
#define ERR_FDCAN_NONE                  ((uint32_t)0x00000000U) /*!< No error                                                               */
#define HAL_FDCAN_ERROR_TIMEOUT         ((uint32_t)0x00000001U) /*!< Timeout error                                                          */
#define HAL_FDCAN_ERROR_NOT_INITIALIZED ((uint32_t)0x00000002U) /*!< Peripheral not initialized                                             */
#define HAL_FDCAN_ERROR_NOT_READY       ((uint32_t)0x00000004U) /*!< Peripheral not ready                                                   */
#define HAL_FDCAN_ERROR_NOT_STARTED     ((uint32_t)0x00000008U) /*!< Peripheral not started                                                 */
#define HAL_FDCAN_ERROR_NOT_SUPPORTED   ((uint32_t)0x00000010U) /*!< Mode not supported                                                     */
#define HAL_FDCAN_ERROR_PARAM           ((uint32_t)0x00000020U) /*!< Parameter error                                                        */
#define HAL_FDCAN_ERROR_PENDING         ((uint32_t)0x00000040U) /*!< Pending operation                                                      */
#define HAL_FDCAN_ERROR_RAM_ACCESS      ((uint32_t)0x00000080U) /*!< Message RAM Access Failure                                             */
#define ERR_FDCAN_RXBUF_EMPTY          ((uint32_t)0x00000100U) /*!< Put element in full FIFO                                               */
#define ERR_FDCAN_TXBUF_FULL           ((uint32_t)0x00000200U) /*!< Get element from empty FIFO                                            */
#define ERR_FDCAN_TBSLOT_FULL           ((uint32_t)0x00000200U) /*!< Get element from empty FIFO                                            */
#define ERR_FDCAN_PTB_LOCKED            ((uint32_t)0x00000400U)
#define HAL_FDCAN_ERROR_LOG_OVERFLOW    FDCAN_IR_ELO            /*!< Overflow of CAN Error Logging Counter                                  */
#define HAL_FDCAN_ERROR_RAM_WDG         FDCAN_IR_WDI            /*!< Message RAM Watchdog event occurred                                    */
#define HAL_FDCAN_ERROR_PROTOCOL_ARBT   FDCAN_IR_PEA            /*!< Protocol Error in Arbitration Phase (Nominal Bit Time is used)         */
#define HAL_FDCAN_ERROR_PROTOCOL_DATA   FDCAN_IR_PED            /*!< Protocol Error in Data Phase (Data Bit Time is used)                   */
#define HAL_FDCAN_ERROR_RESERVED_AREA   FDCAN_IR_ARA            /*!< Access to Reserved Address                                             */
#define HAL_FDCAN_ERROR_TT_GLOBAL_TIME  FDCAN_TTIR_GTE          /*!< Global Time Error : Synchronization deviation exceeded limit           */
#define HAL_FDCAN_ERROR_TT_TX_UNDERFLOW FDCAN_TTIR_TXU          /*!< Tx Count Underflow : Less Tx trigger than expected in one matrix cycle */
#define HAL_FDCAN_ERROR_TT_TX_OVERFLOW  FDCAN_TTIR_TXO          /*!< Tx Count Overflow : More Tx trigger than expected in one matrix cycle  */
#define HAL_FDCAN_ERROR_TT_SCHEDULE1    FDCAN_TTIR_SE1          /*!< Scheduling error 1                                                     */
#define HAL_FDCAN_ERROR_TT_SCHEDULE2    FDCAN_TTIR_SE2          /*!< Scheduling error 2                                                     */
#define HAL_FDCAN_ERROR_TT_NO_INIT_REF  FDCAN_TTIR_IWT          /*!< No system startup due to missing reference message                     */
#define HAL_FDCAN_ERROR_TT_NO_REF       FDCAN_TTIR_WT           /*!< Missing reference message                                              */
#define HAL_FDCAN_ERROR_TT_APPL_WDG     FDCAN_TTIR_AW           /*!< Application watchdog not served in time                                */
#define HAL_FDCAN_ERROR_TT_CONFIG       FDCAN_TTIR_CER          /*!< Error found in trigger list                                            */

#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
#define HAL_FDCAN_ERROR_INVALID_CALLBACK ((uint32_t)0x00000100U) /*!< Invalid Callback error                                                */
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup FDCAN_frame_format FDCAN Frame Format
  * @{
  */
#define FDCAN_FRAME_CLASSIC   ((uint32_t)0x00000000U)                         /*!< Classic mode                      */
#define FDCAN_FRAME_FD_NO_BRS ((uint32_t)FDCAN_CCCR_FDOE)                     /*!< FD mode without BitRate Switching */
#define FDCAN_FRAME_FD_BRS    ((uint32_t)(FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE)) /*!< FD mode with BitRate Switching    */
/**
  * @}
  */
  
/** @defgroup FDCAN_frame_ISOType FDCAN Frame ISO Type
  * @{
  */  
#define FDCAN_FRAME_ISO     (FDCAN_CR_FD_ISO)
#define FDCAN_FRAME_NONISO  (0)
/**
  * @}
  */

#define FDCAN_TIMESTAMP_DISABLE     (0)
#define FDCAN_TIMESTAMP_ENABLE      (1)


/** @defgroup FDCAN_operating_mode FDCAN Operating Mode
  * @{
  */

#define FDCAN_MODE_NORMAL                   (0)             /*!< Normal mode */
#define FDCAN_MODE_LOM                      (FDCAN_CR_LOM)  /*!< Listen only Mode. same as bus monitoring mode  */
#define FDCAN_MODE_LBMI                     (FDCAN_CR_LBMI) /*!< LoopBack mode internal */
#define FDCAN_MODE_LBME                     (FDCAN_CR_LBME) /*!< LoopBack mode External */
#define FDCAN_MODE_LBME_SACK                (FDCAN_CR_LBME | FDCAN_CR_SACK)         /*!< LoopBack mode External with self-ACK */
#define FDCAN_MODE_LOM_LBME                 (FDCAN_CR_LOM | FDCAN_CR_LBME)          /*!< Listen only mode combined LBME */
#define FDCAN_MODE_LOM_LBME_SACK            (FDCAN_CR_LOM | FDCAN_MODE_LBME_SACK)   /*!< Listen only mode combined LBME with self-ACK */


/**
  * @}
  */


/** @defgroup FDCAN_id_type FDCAN ID Type
  * @{
  */
#define FDCAN_STANDARD_ID ((uint32_t)0) /*!< Standard ID element */
#define FDCAN_EXTENDED_ID ((uint32_t)1) /*!< Extended ID element */
#define FDCAN_BOTH_ID     ((uint32_t)2) /*!< Extended ID element */
/**
  * @}
  */

/** @defgroup FDCAN_frame_type FDCAN Frame Type
  * @{
  */
#define FDCAN_DATA_FRAME   ((uint32_t)0x00000000U)  /*!< Data frame   */
#define FDCAN_REMOTE_FRAME ((uint32_t)0x20000000U)  /*!< Remote frame */
/**
  * @}
  */

/** @defgroup FDCAN_data_length_code FDCAN Data Length Code
  * @{
  */
#define FDCAN_DLC_BYTES_0  (0x0) /*!< 0 bytes data field  */
#define FDCAN_DLC_BYTES_1  (0x1) /*!< 1 bytes data field  */
#define FDCAN_DLC_BYTES_2  (0x2) /*!< 2 bytes data field  */
#define FDCAN_DLC_BYTES_3  (0x3) /*!< 3 bytes data field  */
#define FDCAN_DLC_BYTES_4  (0x4) /*!< 4 bytes data field  */
#define FDCAN_DLC_BYTES_5  (0x5) /*!< 5 bytes data field  */
#define FDCAN_DLC_BYTES_6  (0x6) /*!< 6 bytes data field  */
#define FDCAN_DLC_BYTES_7  (0x7) /*!< 7 bytes data field  */
#define FDCAN_DLC_BYTES_8  (0x8) /*!< 8 bytes data field  */
#define FDCAN_DLC_BYTES_12 (0x9) /*!< 12 bytes data field */
#define FDCAN_DLC_BYTES_16 (0xA) /*!< 16 bytes data field */
#define FDCAN_DLC_BYTES_20 (0xB) /*!< 20 bytes data field */
#define FDCAN_DLC_BYTES_24 (0xC) /*!< 24 bytes data field */
#define FDCAN_DLC_BYTES_32 (0xD) /*!< 32 bytes data field */
#define FDCAN_DLC_BYTES_48 (0xE) /*!< 48 bytes data field */
#define FDCAN_DLC_BYTES_64 (0xF) /*!< 64 bytes data field */
/**
  * @}
  */

/** @defgroup FDCAN_error_state_indicator FDCAN Error State Indicator
  * @{
  */
#define FDCAN_ESI_ACTIVE  ((uint32_t)0x00000000U) /*!< Transmitting node is error active  */
#define FDCAN_ESI_PASSIVE ((uint32_t)0x80000000U) /*!< Transmitting node is error passive */
/**
  * @}
  */


/** @defgroup FDCAN_protocol_error_code FDCAN protocol error code
  * @{
  */
#define FDCAN_PROTOCOL_ERROR_NONE      ((uint32_t)0x00000000U) /*!< No error occurred         */
#define FDCAN_PROTOCOL_ERROR_STUFF     ((uint32_t)0x00000001U) /*!< Stuff error               */
#define FDCAN_PROTOCOL_ERROR_FORM      ((uint32_t)0x00000002U) /*!< Form error                */
#define FDCAN_PROTOCOL_ERROR_ACK       ((uint32_t)0x00000003U) /*!< Acknowledge error         */
#define FDCAN_PROTOCOL_ERROR_BIT1      ((uint32_t)0x00000004U) /*!< Bit 1 (recessive) error   */
#define FDCAN_PROTOCOL_ERROR_BIT0      ((uint32_t)0x00000005U) /*!< Bit 0 (dominant) error    */
#define FDCAN_PROTOCOL_ERROR_CRC       ((uint32_t)0x00000006U) /*!< CRC check sum error       */
#define FDCAN_PROTOCOL_ERROR_NO_CHANGE ((uint32_t)0x00000007U) /*!< No change since last read */
/**
  * @}
  */

/** @defgroup FDCAN_communication_state FDCAN communication state
  * @{
  */
#define FDCAN_BUS_IDLE      ((uint32_t)0x00000000U) /*!< Node is synchronizing on CAN communication */
#define FDCAN_BUS_RACTIVE   ((uint32_t)0x00000004U) /*!< Node is neither receiver nor transmitter   */
#define FDCAN_BUS_TACTIVE   ((uint32_t)0x00000002U) /*!< Node is operating as receiver              */
#define FDCAN_BUS_OFF       ((uint32_t)0x00000001U) /*!< Node is operating as transmitter           */
/**
  * @}
  */


/** @defgroup FDCAN_Rx_FIFO_operation_mode FDCAN FIFO operation mode
  * @{
  */
#define FDCAN_RX_BUF_BLOCKING  ((uint32_t)0x00000000U) /*!< Rx FIFO blocking mode  */
#define FDCAN_RX_BUF_OVERWRITE ((uint32_t)0x80000000U) /*!< Rx FIFO overwrite mode */
/**
  * @}
  */
  
  
/** @defgroup tt_presc_selection TTCAN Timer PRESCaler
  * @{
  */
#define FDCAN_TT_TPRESC_1           ((uint32_t)0x00000000U) 
#define FDCAN_TT_TPRESC_2           ((uint32_t)0x00000001U) 
#define FDCAN_TT_TPRESC_4           ((uint32_t)0x00000002U) 
#define FDCAN_TT_TPRESC_8           ((uint32_t)0x00000003U)
#define IS_FDCAN_TT_TPRESC(PRESC)   (((PRESC) == FDCAN_TT_TPRESC_1) || \
                                     ((PRESC) == FDCAN_TT_TPRESC_2) || \
                                     ((PRESC) == FDCAN_TT_TPRESC_4) || \
                                     ((PRESC) == FDCAN_TT_TPRESC_8)) 

#define FDCAN_TT_TX_IMMEDIATE_TRIGGER       ((uint32_t)0x00000000U) /*!< For immediate transmission             */
#define FDCAN_TT_RX_TIME_TRIGGER            ((uint32_t)0x00000001U) /*!< For receive triggers                   */
#define FDCAN_TT_TX_TRIGGER_SINGLE          ((uint32_t)0x00000002U) /*!< For exclusive time windows             */
#define FDCAN_TT_TX_TRIGGER_MERGED_START    ((uint32_t)0x00000003U) /*!< For merged arbitrating time windows    */
#define FDCAN_TT_TX_TRIGGER_MERGED_STOP     ((uint32_t)0x00000004U) /*!< For merged arbitrating time windows    */
#define FDCAN_TT_TRIGGER_NOCATION           ((uint32_t)0x00000005U) /*!< For merged arbitrating time windows    */
//#define FDCAN_TT_END_OF_LIST                ((uint32_t)0x0000000AU) /*!< Illegal trigger, to be assigned to the unused triggers after a FDCAN_TT_WATCH_TRIGGER or FDCAN_TT_WATCH_TRIGGER_GAP */
#define IS_FDCAN_TT_TRIGGER_TYPE(TYPE) (((TYPE) == FDCAN_TT_TX_IMMEDIATE_TRIGGER        ) || \
                                        ((TYPE) == FDCAN_TT_RX_TIME_TRIGGER    ) || \
                                        ((TYPE) == FDCAN_TT_TX_TRIGGER_SINGLE     ) || \
                                        ((TYPE) == FDCAN_TT_TX_TRIGGER_MERGED_START ) || \
                                        ((TYPE) == FDCAN_TT_TX_TRIGGER_MERGED_STOP))
                                        
#define FDCAN_TIMESTAMP_SOF 0
#define FDCAN_TIMESTAMP_EOF 1
#define IS_FDCAN_TIMESTAMP_POSITION(pos)    ((pos) == FDCAN_TIMESTAMP_SOF) || ((pos) == FDCAN_TIMESTAMP_EOF)

#define FDCAN_IR_MASK (0x2A00FE)     /*!< FDCAN interrupts mask */
#define FDCAN_ERR_IR_MASK (0x2A) /*!< FDCAN error interrupts mask */

#define FDCAN_FLAG_RX_BUFFER_NEW_MESSAGE    (FDCAN_IR_RIF   )             /*!< At least one received message stored into a Rx Buffer */
#define FDCAN_FLAG_RX_BUFFER_OVERRUN        (FDCAN_IR_ROIF  )              /*!< At least one received message stored into a Rx Buffer */
#define FDCAN_FLAG_RX_BUFFER_FULL           (FDCAN_IR_RFIF  )   
#define FDCAN_FLAG_RX_BUFFER_ALMOSTFULL     (FDCAN_IR_RAFIF )   
#define FDCAN_FLAG_TX_PTB_COMPLETE          (FDCAN_IR_TPIF  )   
#define FDCAN_FLAG_TX_STB_COMPLETE          (FDCAN_IR_TSIF  )   
#define FDCAN_FLAG_ERROR                    (FDCAN_IR_EIF   )   
#define FDCAN_FLAG_TX_ABORT_COMPLETE        (FDCAN_IR_AIF   )                                                            
#define FDCAN_FLAG_BUS_ERROR                (FDCAN_IR_BEIF  )
#define FDCAN_FLAG_ARBITRATION_LOST         (FDCAN_IR_ALIF  )
#define FDCAN_FLAG_ERROR_PASSIVE            (FDCAN_IR_EPIF  )
#define FDCAN_FLAG_ERRPASSMD_ACTIVE         (FDCAN_IR_EPASS )
#define FDCAN_FLAG_ERRWARN_LIMIT            (FDCAN_IR_EWARN )

#define FDCAN_IE_RX_BUFFER_NEW_MESSAGE      (FDCAN_IR_RIE   )        /*!< At least one received message stored into a Rx Buffer */
#define FDCAN_IE_RX_BUFFER_OVERRUN          (FDCAN_IR_ROIE  )         /*!< At least one received message stored into a Rx Buffer */
#define FDCAN_IE_RX_BUFFER_FULL             (FDCAN_IR_RFIE  )
#define FDCAN_IE_RX_BUFFER_ALMOSTFULL       (FDCAN_IR_RAFIE )
#define FDCAN_IE_TX_PTB_COMPLETE            (FDCAN_IR_TPIE  )
#define FDCAN_IE_TX_STB_COMPLETE            (FDCAN_IR_TSIE  )
#define FDCAN_IE_ERROR                      (FDCAN_IR_EIE   )
#define FDCAN_IE_BUS_ERROR                  (FDCAN_IR_BEIE  )
#define FDCAN_IE_ARBITRATION_LOST           (FDCAN_IR_ALIE  )
#define FDCAN_IE_ERROR_PASSIVE              (FDCAN_IR_EPIE  )


#define __HAL_FDCAN_ENTER_RESET_STATE(__HANDLE__)   SET_BIT((__HANDLE__)->Instance->CR, FDCAN_CR_RESET)
#define __HAL_FDCAN_EXIT_RESET_STATE(__HANDLE__)    CLEAR_BIT((__HANDLE__)->Instance->CR, FDCAN_CR_RESET)

#define __HAL_FDCAN_DLC2LEN(DLC)    ( DLC < 9 ? DLC : DLC < 13 ? 8 + (DLC - 8) * 4 : 32 + (DLC - 13) * 16 )
#define __HAL_FDCAN_LEN2DLC(LEN)    ( LEN < 9 ? LEN : LEN < 32 ? 8 + (LEN - 8) / 4 : 13 + (LEN - 32) / 16 )


#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
#define __HAL_FDCAN_RESET_HANDLE_STATE(__HANDLE__) do{                                                \
                                                      (__HANDLE__)->State = HAL_FDCAN_STATE_RESET;    \
                                                      (__HANDLE__)->MspInitCallback = NULL;           \
                                                      (__HANDLE__)->MspDeInitCallback = NULL;         \
                                                     } while(0)
#else
#define __HAL_FDCAN_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_FDCAN_STATE_RESET)
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

#define __HAL_FDCAN_ENABLE_IT(__HANDLE__, __INTERRUPT__) (__HANDLE__)->Instance->IR = ((__HANDLE__)->Instance->IR & FDCAN_IR_MASK ) | (__INTERRUPT__)
#define __HAL_FDCAN_ENABLE_IT_ALL(__HANDLE__) ((__HANDLE__)->Instance->IR = FDCAN_IR_MASK)

#define __HAL_FDCAN_DISABLE_IT(__HANDLE__, __INTERRUPT__) (__HANDLE__)->Instance->IR &= ~((__INTERRUPT__) & FDCAN_IR_MASK)
#define __HAL_FDCAN_DISABLE_IT_ALL(__HANDLE__) ((__HANDLE__)->Instance->IR = 0)

#define __HAL_FDCAN_GET_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->IR & (__FLAG__))
#define __HAL_FDCAN_CLEAR_FLAG(__HANDLE__, __FLAG__)             \
do{                                                              \
    ((__HANDLE__)->Instance->IR) = (((__HANDLE__)->Instance->IR) & (FDCAN_IR_MASK) ) | (__FLAG__); \
  }while(0)

#define __HAL_FDCAN_TT_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->TTCFG) = (((__HANDLE__)->Instance->TTCFG) & ~0x16800) | (__INTERRUPT__))
#define __HAL_FDCAN_TT_DISABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->TTCFG) = (((__HANDLE__)->Instance->TTCFG) & ~0x16800) & (~__INTERRUPT__))

#define __HAL_FDCAN_TT_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->TTCFG) & (__FLAG__))
#define __HAL_FDCAN_TT_CLEAR_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->TTCFG) = ((__HANDLE__)->Instance->TTCFG & ~0x16800) | (__FLAG__))

#define __HAL_FDCAN_DISABLE_ALL_FILTERS(__HANDLE__) ((__HANDLE__)->Instance->ACFCR.b.AE = 0)  


HAL_StatusTypeDef HAL_FDCAN_Init(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_DeInit(FDCAN_HandleTypeDef *hfdcan);
void              HAL_FDCAN_MspInit(FDCAN_HandleTypeDef *hfdcan);
void              HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef *hfdcan);
//HAL_StatusTypeDef HAL_FDCAN_EnterPowerDownMode(FDCAN_HandleTypeDef *hfdcan);
//HAL_StatusTypeDef HAL_FDCAN_ExitPowerDownMode(FDCAN_HandleTypeDef *hfdcan);

#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
/* Callbacks Register/UnRegister functions  ***********************************/
HAL_StatusTypeDef HAL_FDCAN_RegisterCallback(FDCAN_HandleTypeDef *hfdcan, HAL_FDCAN_CallbackIDTypeDef CallbackID, pFDCAN_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterCallback(FDCAN_HandleTypeDef *hfdcan, HAL_FDCAN_CallbackIDTypeDef CallbackID);
HAL_StatusTypeDef HAL_FDCAN_RegisterClockCalibrationCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_ClockCalibrationCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterClockCalibrationCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterTxEventFifoCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_TxEventFifoCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterTxEventFifoCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterRxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_RxFifo0CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterRxFifo0Callback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterRxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_RxFifo1CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterRxFifo1Callback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterTxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_TxBufferCompleteCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterTxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterTxBufferAbortCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_TxBufferAbortCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterTxBufferAbortCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_ErrorStatusCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterTTScheduleSyncCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_TT_ScheduleSyncCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterTTScheduleSyncCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterTTTimeMarkCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_TT_TimeMarkCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterTTTimeMarkCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterTTStopWatchCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_TT_StopWatchCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterTTStopWatchCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterTTGlobalTimeCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_TT_GlobalTimeCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterTTGlobalTimeCallback(FDCAN_HandleTypeDef *hfdcan);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

HAL_StatusTypeDef HAL_FDCAN_ConfigFilter(FDCAN_HandleTypeDef *hfdcan, FDCAN_FilterTypeDef *sFilterConfig);
HAL_StatusTypeDef HAL_FDCAN_NewConfigFilter(FDCAN_HandleTypeDef *hfdcan, FDCAN_NewFilterTypeDef *sFilterConfig);

HAL_StatusTypeDef HAL_FDCAN_ConfigRxBufOverwriteMode(FDCAN_HandleTypeDef *hfdcan, uint32_t OverwriteMode);
HAL_StatusTypeDef HAL_FDCAN_TransceiverEnterSTBY(FDCAN_HandleTypeDef *hfdcan);

HAL_StatusTypeDef HAL_FDCAN_EnableTimestamp(FDCAN_HandleTypeDef *hfdcan, uint32_t ts_position);
HAL_StatusTypeDef HAL_FDCAN_DisableTimestamp(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_GetTTS(FDCAN_HandleTypeDef *hfdcan, FDCAN_TTSTypeDef *tts);

HAL_StatusTypeDef HAL_FDCAN_TT_EnableWatchTrigger(FDCAN_HandleTypeDef *hfdcan, uint32_t cycle_time);
HAL_StatusTypeDef HAL_FDCAN_TT_DisableWatchTrigger(FDCAN_HandleTypeDef *hfdcan);

uint16_t          HAL_FDCAN_GetTimestampCounter(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_ResetTimestampCounter(FDCAN_HandleTypeDef *hfdcan);

HAL_StatusTypeDef HAL_FDCAN_Start(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_Stop(FDCAN_HandleTypeDef *hfdcan);

HAL_StatusTypeDef HAL_FDCAN_EnableTxBufferRequest(FDCAN_HandleTypeDef *hfdcan, TransmitType_enum type);
HAL_StatusTypeDef HAL_FDCAN_AbortTxRequest(FDCAN_HandleTypeDef *hfdcan, TransmitAbortType_enum type);

HAL_StatusTypeDef HAL_FDCAN_GetRxMessage(FDCAN_HandleTypeDef *hfdcan, FDCAN_RxHeaderTypeDef *pRxHeader, uint8_t *pRxData);


bool HAL_FDCAN_GetTxReqCompleted(FDCAN_HandleTypeDef *hfdcan, TransmitType_enum type);
HAL_StatusTypeDef HAL_FDCAN_WaitTxCompleted(FDCAN_HandleTypeDef *hfdcan, TransmitType_enum type, uint32_t timeout);
uint32_t HAL_FDCAN_GetBusStatus(FDCAN_HandleTypeDef *hfdcan);

HAL_StatusTypeDef HAL_FDCAN_ClearEntireSTB(FDCAN_HandleTypeDef *hfdcan);

void HAL_FDCAN_PTBTranmistSingleShot(FDCAN_HandleTypeDef *hfdcan, FunctionalState state);
void HAL_FDCAN_STBTranmistSingleShot(FDCAN_HandleTypeDef *hfdcan, FunctionalState state);


FDCAN_RXBUF_FILL_STATE_enum HAL_FDCAN_GetRxBufFillState(FDCAN_HandleTypeDef *hfdcan);
FDCAN_TXBUF_FILL_STATE_enum HAL_FDCAN_GetTxBufFillState(FDCAN_HandleTypeDef *hfdcan);

HAL_StatusTypeDef HAL_FDCAN_AddMessageToSTB(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData);
HAL_StatusTypeDef HAL_FDCAN_AddMessageToPTB(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData);

HAL_StatusTypeDef HAL_FDCAN_EnableSTBPriorityMode(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_DisableSTBPriorityMode(FDCAN_HandleTypeDef *hfdcan);

HAL_StatusTypeDef HAL_FDCAN_TransmitMessageBySTB(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData);
HAL_StatusTypeDef HAL_FDCAN_TransmitMessageByPTB(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData);


HAL_StatusTypeDef HAL_FDCAN_ConfigRxBufWarnningLimit(FDCAN_HandleTypeDef *hfdcan, uint8_t afwl);
uint8_t HAL_FDCAN_GetRxBufWarnningLimit(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_ConfigErrCntWarnningLimit(FDCAN_HandleTypeDef *hfdcan, uint8_t ecnt);
uint8_t HAL_FDCAN_GetErrCntWarnningLimit(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_GetErrorInfo(FDCAN_HandleTypeDef *hfdcan, FDCAN_ErrorInfo_u *errinfo);
void HAL_FDCAN_IRQHandler(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TxFifoEmptyCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes);
void HAL_FDCAN_TxBufferAbortCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes);
void HAL_FDCAN_RxBufferNewMessageCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_RxBufferAFCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_RxBufferFullCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_RxBufferOVCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TXPTBCompletedCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TXSTBCompletedCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TxAbortCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_BusErrorCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_ErrorPassiveCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_ArbitrationLostCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TimestampWraparoundCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TimeoutOccurredCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs);
void HAL_FDCAN_TT_ScheduleSyncCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TTSchedSyncITs);


void HAL_FDCAN_TT_TimeMarkCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TTTimeMarkITs);
void HAL_FDCAN_TT_TimerTriggerCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_TT_Config(FDCAN_HandleTypeDef *hfdcan, uint32_t TT_Presc);
HAL_StatusTypeDef HAL_FDCAN_TT_ConfigReferenceMessage(FDCAN_HandleTypeDef *hfdcan, uint32_t IdType, uint32_t Identifier, uint32_t Payload);
HAL_StatusTypeDef HAL_FDCAN_TT_ConfigTrigger(FDCAN_HandleTypeDef *hfdcan, FDCAN_TriggerTypeDef *sTriggerConfig);
void              HAL_FDCAN_TT_ImmediateTrigger(FDCAN_HandleTypeDef *hfdcan, uint8_t TTPtr);
HAL_StatusTypeDef HAL_FDCAN_TT_SetNextIsGap(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_TT_SetEndOfGap(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_TT_ConfigExternalSyncPhase(FDCAN_HandleTypeDef *hfdcan, uint32_t TargetPhase);
HAL_StatusTypeDef HAL_FDCAN_TT_EnableExternalSynchronization(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_TT_DisableExternalSynchronization(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_TT_AddMessageByTBPtr(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData, uint8_t TBPtr);
HAL_StatusTypeDef HAL_FDCAN_TT_AddMessageByTBPtr_NOTBF(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData, uint8_t TBPtr);


/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group7
  * @{
  */
/* Peripheral State functions *************************************************/
uint32_t HAL_FDCAN_GetError(FDCAN_HandleTypeDef *hfdcan);
HAL_FDCAN_StateTypeDef HAL_FDCAN_GetState(FDCAN_HandleTypeDef *hfdcan);
/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup FDCAN_Private_Macros FDCAN Private Macros
  * @{
  */
#define STB_SLOTS_NUM                       (16)
#define IS_FDCAN_STB_SLOTS_INDEX(INDEX)     ((INDEX) > 0 && INDEX <= STB_SLOTS_NUM)
#define IS_FDCAN_TT_SLOTS_INDEX(INDEX)      ((INDEX) <= STB_SLOTS_NUM)

#define IS_FDCAN_ALL_INSTANCE(__INSTANCE__) (((__INSTANCE__) == FDCAN1) || \
                                             ((__INSTANCE__) == FDCAN2) || \
                                             ((__INSTANCE__) == FDCAN3))
                                             
#define IS_FDCAN_AFWL(AWFL)                 ((AWFL) < STB_SLOTS_NUM)
                                             
#define IS_FDCAN_TT_INSTANCE(__INSTANCE__)  (((__INSTANCE__) == FDCAN1) || \
                                             ((__INSTANCE__) == FDCAN2) || \
                                             ((__INSTANCE__) == FDCAN3))                                    
  
#define IS_FDCAN_FRAME_FORMAT(FORMAT) (((FORMAT) == FDCAN_FRAME_CLASSIC  ) || \
                                       ((FORMAT) == FDCAN_FRAME_FD_NO_BRS) || \
                                       ((FORMAT) == FDCAN_FRAME_FD_BRS   ))
                                       
#define IS_FDCAN_MODE(MODE) (((MODE) == FDCAN_MODE_NORMAL              ) || \
                             ((MODE) == FDCAN_MODE_RESTRICTED_OPERATION) || \
                             ((MODE) == FDCAN_MODE_BUS_MONITORING      ) || \
                             ((MODE) == FDCAN_MODE_INTERNAL_LOOPBACK   ) || \
                             ((MODE) == FDCAN_MODE_EXTERNAL_LOOPBACK   ))

#define IS_FDCAN_NOMINAL_PRESCALER(PRESCALER) (((PRESCALER) >= 1U) && ((PRESCALER) <= 512U))
#define IS_FDCAN_NOMINAL_SJW(SJW) (((SJW) >= 1U) && ((SJW) <= 128U))
#define IS_FDCAN_NOMINAL_TSEG1(TSEG1) (((TSEG1) >= 1U) && ((TSEG1) <= 256U))
#define IS_FDCAN_NOMINAL_TSEG2(TSEG2) (((TSEG2) >= 1U) && ((TSEG2) <= 128U))
#define IS_FDCAN_DATA_PRESCALER(PRESCALER) (((PRESCALER) >= 1U) && ((PRESCALER) <= 32U))
#define IS_FDCAN_DATA_SJW(SJW) (((SJW) >= 1U) && ((SJW) <= 16U))
#define IS_FDCAN_DATA_TSEG1(TSEG1) (((TSEG1) >= 1U) && ((TSEG1) <= 32U))
#define IS_FDCAN_DATA_TSEG2(TSEG2) (((TSEG2) >= 1U) && ((TSEG2) <= 16U))
#define IS_FDCAN_MAX_VALUE(VALUE, MAX) ((VALUE) <= (MAX))
#define IS_FDCAN_MIN_VALUE(VALUE, MIN) ((VALUE) >= (MIN))
#define IS_FDCAN_DATA_SIZE(SIZE) (((SIZE) == FDCAN_DATA_BYTES_8 ) || \
                                  ((SIZE) == FDCAN_DATA_BYTES_12) || \
                                  ((SIZE) == FDCAN_DATA_BYTES_16) || \
                                  ((SIZE) == FDCAN_DATA_BYTES_20) || \
                                  ((SIZE) == FDCAN_DATA_BYTES_24) || \
                                  ((SIZE) == FDCAN_DATA_BYTES_32) || \
                                  ((SIZE) == FDCAN_DATA_BYTES_48) || \
                                  ((SIZE) == FDCAN_DATA_BYTES_64))

#define IS_FDCAN_ID_TYPE(ID_TYPE) (((ID_TYPE) == FDCAN_STANDARD_ID) || \
                                   ((ID_TYPE) == FDCAN_EXTENDED_ID))
                                   
#define IS_FILTER_ID_TYPE(ID_TYPE) (((ID_TYPE) == FDCAN_STANDARD_ID) || \
                                   ((ID_TYPE) == FDCAN_EXTENDED_ID) || \
                                   ((ID_TYPE) == FDCAN_BOTH_ID))
                                   
#define IS_VALID_FILTER_INDEX(FILTER_INDEX) ((FILTER_INDEX) < (NR_OF_ACF) )

#define IS_FDCAN_RX_BUF_MODE(MODE) (((MODE) == FDCAN_RX_BUF_BLOCKING ) || \
                                     ((MODE) == FDCAN_RX_BUF_OVERWRITE))

#define IS_FDCAN_FRAME_TYPE(TYPE) (((TYPE) == FDCAN_DATA_FRAME  ) || \
                                   ((TYPE) == FDCAN_REMOTE_FRAME))
                                   
#define IS_FDCAN_TRANSMIT_TYPE(TYPE)    (((TYPE) == FDCAN_TRANSMIT_PTB  )   || \
                                        ((TYPE) == FDCAN_TRANSMIT_STB_ONE ) || \
                                        ((TYPE) == FDCAN_TRANSMIT_STB_ALL))
                                   
#define IS_FDCAN_ABORT_TYPE(TYPE)   (((TYPE) == FDCAN_ABORT_PTB  ) || \
                                   ((TYPE) == FDCAN_ABORT_STB))
                                   
#define IS_FDCAN_DLC(DLC) (((DLC) == FDCAN_DLC_BYTES_0 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_1 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_2 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_3 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_4 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_5 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_6 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_7 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_8 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_12) || \
                           ((DLC) == FDCAN_DLC_BYTES_16) || \
                           ((DLC) == FDCAN_DLC_BYTES_20) || \
                           ((DLC) == FDCAN_DLC_BYTES_24) || \
                           ((DLC) == FDCAN_DLC_BYTES_32) || \
                           ((DLC) == FDCAN_DLC_BYTES_48) || \
                           ((DLC) == FDCAN_DLC_BYTES_64))

#ifdef __cplusplus
}
#endif


#endif /* __HAL_FDCAN_H__ */

