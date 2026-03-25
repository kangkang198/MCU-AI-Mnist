/******************************************************************************
* @file    hal_uart.h

* @brief   Header file of UART HAL module.
* @version V1.0.0
* @date    2020
******************************************************************************/
#ifndef __HAL_DCMI_H__
#define __HAL_DCMI_H__

#include "acm32h5xx_hal_conf.h"
/** @addtogroup DCMI DCMI
  * @brief DCMI HAL module driver
  * @{
  */
#define DCMI_POSITION_ESCR_LSC     (uint32_t)DCMI_ESCR_LSC_Pos     /*!< Required left shift to set line start delimiter */
#define DCMI_POSITION_ESCR_LEC     (uint32_t)DCMI_ESCR_LEC_Pos     /*!< Required left shift to set line end delimiter   */
#define DCMI_POSITION_ESCR_FEC     (uint32_t)DCMI_ESCR_FEC_Pos     /*!< Required left shift to set frame end delimiter  */

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
/******************************************************************************/
/*                                                                            */
/*                                    DCMI                                    */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for DCMI_CR register  ******************/
#define DCMI_CR_CAPTURE_Pos        (0U)                                        
#define DCMI_CR_CAPTURE_Msk        (0x1U << DCMI_CR_CAPTURE_Pos)               /*!< 0x00000001 */
#define DCMI_CR_CAPTURE            DCMI_CR_CAPTURE_Msk                         
#define DCMI_CR_CM_Pos             (1U)                                        
#define DCMI_CR_CM_Msk             (0x1U << DCMI_CR_CM_Pos)                    /*!< 0x00000002 */
#define DCMI_CR_CM                 DCMI_CR_CM_Msk                              
#define DCMI_CR_CROP_Pos           (2U)                                        
#define DCMI_CR_CROP_Msk           (0x1U << DCMI_CR_CROP_Pos)                  /*!< 0x00000004 */
#define DCMI_CR_CROP               DCMI_CR_CROP_Msk                            
#define DCMI_CR_JPEG_Pos           (3U)                                        
#define DCMI_CR_JPEG_Msk           (0x1U << DCMI_CR_JPEG_Pos)                  /*!< 0x00000008 */
#define DCMI_CR_JPEG               DCMI_CR_JPEG_Msk                            
#define DCMI_CR_ESS_Pos            (4U)                                        
#define DCMI_CR_ESS_Msk            (0x1U << DCMI_CR_ESS_Pos)                   /*!< 0x00000010 */
#define DCMI_CR_ESS                DCMI_CR_ESS_Msk                             
#define DCMI_CR_PCKPOL_Pos         (5U)                                        
#define DCMI_CR_PCKPOL_Msk         (0x1U << DCMI_CR_PCKPOL_Pos)                /*!< 0x00000020 */
#define DCMI_CR_PCKPOL             DCMI_CR_PCKPOL_Msk                          
#define DCMI_CR_HSPOL_Pos          (6U)                                        
#define DCMI_CR_HSPOL_Msk          (0x1U << DCMI_CR_HSPOL_Pos)                 /*!< 0x00000040 */
#define DCMI_CR_HSPOL              DCMI_CR_HSPOL_Msk                           
#define DCMI_CR_VSPOL_Pos          (7U)                                        
#define DCMI_CR_VSPOL_Msk          (0x1U << DCMI_CR_VSPOL_Pos)                 /*!< 0x00000080 */
#define DCMI_CR_VSPOL              DCMI_CR_VSPOL_Msk                           
#define DCMI_CR_FCRC_0             0x00000100U                                 
#define DCMI_CR_FCRC_1             0x00000200U                                 
#define DCMI_CR_EDM_0              0x00000400U                                 
#define DCMI_CR_EDM_1              0x00000800U                                 
//#define DCMI_CR_CRE_Pos            (12U)                                       
//#define DCMI_CR_CRE_Msk            (0x1U << DCMI_CR_CRE_Pos)                   /*!< 0x00001000 */
//#define DCMI_CR_CRE                DCMI_CR_CRE_Msk                             
#define DCMI_CR_ENABLE_Pos         (14U)                                       
#define DCMI_CR_ENABLE_Msk         (0x1U << DCMI_CR_ENABLE_Pos)                /*!< 0x00004000 */
#define DCMI_CR_ENABLE             DCMI_CR_ENABLE_Msk                          

/********************  Bits definition for DCMI_SR register  ******************/
#define DCMI_SR_HSYNC_Pos          (0U)                                        
#define DCMI_SR_HSYNC_Msk          (0x1U << DCMI_SR_HSYNC_Pos)                 /*!< 0x00000001 */
#define DCMI_SR_HSYNC              DCMI_SR_HSYNC_Msk                           
#define DCMI_SR_VSYNC_Pos          (1U)                                        
#define DCMI_SR_VSYNC_Msk          (0x1U << DCMI_SR_VSYNC_Pos)                 /*!< 0x00000002 */
#define DCMI_SR_VSYNC              DCMI_SR_VSYNC_Msk                           
#define DCMI_SR_FNE_Pos            (2U)                                        
#define DCMI_SR_FNE_Msk            (0x1U << DCMI_SR_FNE_Pos)                   /*!< 0x00000004 */
#define DCMI_SR_FNE                DCMI_SR_FNE_Msk                             

/********************  Bits definition for DCMI_RIS register  *****************/
#define DCMI_RIS_FRAME_RIS_Pos     (0U)                                        
#define DCMI_RIS_FRAME_RIS_Msk     (0x1U << DCMI_RIS_FRAME_RIS_Pos)            /*!< 0x00000001 */
#define DCMI_RIS_FRAME_RIS         DCMI_RIS_FRAME_RIS_Msk                      
#define DCMI_RIS_OVR_RIS_Pos       (1U)                                        
#define DCMI_RIS_OVR_RIS_Msk       (0x1U << DCMI_RIS_OVR_RIS_Pos)              /*!< 0x00000002 */
#define DCMI_RIS_OVR_RIS           DCMI_RIS_OVR_RIS_Msk                        
#define DCMI_RIS_ERR_RIS_Pos       (2U)                                        
#define DCMI_RIS_ERR_RIS_Msk       (0x1U << DCMI_RIS_ERR_RIS_Pos)              /*!< 0x00000004 */
#define DCMI_RIS_ERR_RIS           DCMI_RIS_ERR_RIS_Msk                        
#define DCMI_RIS_VSYNC_RIS_Pos     (3U)                                        
#define DCMI_RIS_VSYNC_RIS_Msk     (0x1U << DCMI_RIS_VSYNC_RIS_Pos)            /*!< 0x00000008 */
#define DCMI_RIS_VSYNC_RIS         DCMI_RIS_VSYNC_RIS_Msk                      
#define DCMI_RIS_LINE_RIS_Pos      (4U)                                        
#define DCMI_RIS_LINE_RIS_Msk      (0x1U << DCMI_RIS_LINE_RIS_Pos)             /*!< 0x00000010 */
#define DCMI_RIS_LINE_RIS          DCMI_RIS_LINE_RIS_Msk                       
/* Legacy defines */
#define DCMI_RISR_FRAME_RIS                  DCMI_RIS_FRAME_RIS
#define DCMI_RISR_OVR_RIS                    DCMI_RIS_OVR_RIS
#define DCMI_RISR_ERR_RIS                    DCMI_RIS_ERR_RIS
#define DCMI_RISR_VSYNC_RIS                  DCMI_RIS_VSYNC_RIS
#define DCMI_RISR_LINE_RIS                   DCMI_RIS_LINE_RIS
#define DCMI_RISR_OVF_RIS                    DCMI_RIS_OVR_RIS

/********************  Bits definition for DCMI_IER register  *****************/
#define DCMI_IER_FRAME_IE_Pos      (0U)                                        
#define DCMI_IER_FRAME_IE_Msk      (0x1U << DCMI_IER_FRAME_IE_Pos)             /*!< 0x00000001 */
#define DCMI_IER_FRAME_IE          DCMI_IER_FRAME_IE_Msk                       
#define DCMI_IER_OVR_IE_Pos        (1U)                                        
#define DCMI_IER_OVR_IE_Msk        (0x1U << DCMI_IER_OVR_IE_Pos)               /*!< 0x00000002 */
#define DCMI_IER_OVR_IE            DCMI_IER_OVR_IE_Msk                         
#define DCMI_IER_ERR_IE_Pos        (2U)                                        
#define DCMI_IER_ERR_IE_Msk        (0x1U << DCMI_IER_ERR_IE_Pos)               /*!< 0x00000004 */
#define DCMI_IER_ERR_IE            DCMI_IER_ERR_IE_Msk                         
#define DCMI_IER_VSYNC_IE_Pos      (3U)                                        
#define DCMI_IER_VSYNC_IE_Msk      (0x1U << DCMI_IER_VSYNC_IE_Pos)             /*!< 0x00000008 */
#define DCMI_IER_VSYNC_IE          DCMI_IER_VSYNC_IE_Msk                       
#define DCMI_IER_LINE_IE_Pos       (4U)                                        
#define DCMI_IER_LINE_IE_Msk       (0x1U << DCMI_IER_LINE_IE_Pos)              /*!< 0x00000010 */
#define DCMI_IER_LINE_IE           DCMI_IER_LINE_IE_Msk                        
/* Legacy defines */
#define DCMI_IER_OVF_IE                      DCMI_IER_OVR_IE

/********************  Bits definition for DCMI_MIS register  *****************/
#define DCMI_MIS_FRAME_MIS_Pos     (0U)                                        
#define DCMI_MIS_FRAME_MIS_Msk     (0x1U << DCMI_MIS_FRAME_MIS_Pos)            /*!< 0x00000001 */
#define DCMI_MIS_FRAME_MIS         DCMI_MIS_FRAME_MIS_Msk                      
#define DCMI_MIS_OVR_MIS_Pos       (1U)                                        
#define DCMI_MIS_OVR_MIS_Msk       (0x1U << DCMI_MIS_OVR_MIS_Pos)              /*!< 0x00000002 */
#define DCMI_MIS_OVR_MIS           DCMI_MIS_OVR_MIS_Msk                        
#define DCMI_MIS_ERR_MIS_Pos       (2U)                                        
#define DCMI_MIS_ERR_MIS_Msk       (0x1U << DCMI_MIS_ERR_MIS_Pos)              /*!< 0x00000004 */
#define DCMI_MIS_ERR_MIS           DCMI_MIS_ERR_MIS_Msk                        
#define DCMI_MIS_VSYNC_MIS_Pos     (3U)                                        
#define DCMI_MIS_VSYNC_MIS_Msk     (0x1U << DCMI_MIS_VSYNC_MIS_Pos)            /*!< 0x00000008 */
#define DCMI_MIS_VSYNC_MIS         DCMI_MIS_VSYNC_MIS_Msk                      
#define DCMI_MIS_LINE_MIS_Pos      (4U)                                        
#define DCMI_MIS_LINE_MIS_Msk      (0x1U << DCMI_MIS_LINE_MIS_Pos)             /*!< 0x00000010 */
#define DCMI_MIS_LINE_MIS          DCMI_MIS_LINE_MIS_Msk                       

/* Legacy defines */
#define DCMI_MISR_FRAME_MIS                  DCMI_MIS_FRAME_MIS
#define DCMI_MISR_OVF_MIS                    DCMI_MIS_OVR_MIS
#define DCMI_MISR_ERR_MIS                    DCMI_MIS_ERR_MIS
#define DCMI_MISR_VSYNC_MIS                  DCMI_MIS_VSYNC_MIS
#define DCMI_MISR_LINE_MIS                   DCMI_MIS_LINE_MIS

/********************  Bits definition for DCMI_ICR register  *****************/
#define DCMI_ICR_FRAME_ISC_Pos     (0U)                                        
#define DCMI_ICR_FRAME_ISC_Msk     (0x1U << DCMI_ICR_FRAME_ISC_Pos)            /*!< 0x00000001 */
#define DCMI_ICR_FRAME_ISC         DCMI_ICR_FRAME_ISC_Msk                      
#define DCMI_ICR_OVR_ISC_Pos       (1U)                                        
#define DCMI_ICR_OVR_ISC_Msk       (0x1U << DCMI_ICR_OVR_ISC_Pos)              /*!< 0x00000002 */
#define DCMI_ICR_OVR_ISC           DCMI_ICR_OVR_ISC_Msk                        
#define DCMI_ICR_ERR_ISC_Pos       (2U)                                        
#define DCMI_ICR_ERR_ISC_Msk       (0x1U << DCMI_ICR_ERR_ISC_Pos)              /*!< 0x00000004 */
#define DCMI_ICR_ERR_ISC           DCMI_ICR_ERR_ISC_Msk                        
#define DCMI_ICR_VSYNC_ISC_Pos     (3U)                                        
#define DCMI_ICR_VSYNC_ISC_Msk     (0x1U << DCMI_ICR_VSYNC_ISC_Pos)            /*!< 0x00000008 */
#define DCMI_ICR_VSYNC_ISC         DCMI_ICR_VSYNC_ISC_Msk                      
#define DCMI_ICR_LINE_ISC_Pos      (4U)                                        
#define DCMI_ICR_LINE_ISC_Msk      (0x1U << DCMI_ICR_LINE_ISC_Pos)             /*!< 0x00000010 */
#define DCMI_ICR_LINE_ISC          DCMI_ICR_LINE_ISC_Msk                       

/* Legacy defines */
#define DCMI_ICR_OVF_ISC                     DCMI_ICR_OVR_ISC

/********************  Bits definition for DCMI_ESCR register  ******************/
#define DCMI_ESCR_FSC_Pos          (0U)                                        
#define DCMI_ESCR_FSC_Msk          (0xFFU << DCMI_ESCR_FSC_Pos)                /*!< 0x000000FF */
#define DCMI_ESCR_FSC              DCMI_ESCR_FSC_Msk                           
#define DCMI_ESCR_LSC_Pos          (8U)                                        
#define DCMI_ESCR_LSC_Msk          (0xFFU << DCMI_ESCR_LSC_Pos)                /*!< 0x0000FF00 */
#define DCMI_ESCR_LSC              DCMI_ESCR_LSC_Msk                           
#define DCMI_ESCR_LEC_Pos          (16U)                                       
#define DCMI_ESCR_LEC_Msk          (0xFFU << DCMI_ESCR_LEC_Pos)                /*!< 0x00FF0000 */
#define DCMI_ESCR_LEC              DCMI_ESCR_LEC_Msk                           
#define DCMI_ESCR_FEC_Pos          (24U)                                       
#define DCMI_ESCR_FEC_Msk          (0xFFU << DCMI_ESCR_FEC_Pos)                /*!< 0xFF000000 */
#define DCMI_ESCR_FEC              DCMI_ESCR_FEC_Msk                           

/********************  Bits definition for DCMI_ESUR register  ******************/
#define DCMI_ESUR_FSU_Pos          (0U)                                        
#define DCMI_ESUR_FSU_Msk          (0xFFU << DCMI_ESUR_FSU_Pos)                /*!< 0x000000FF */
#define DCMI_ESUR_FSU              DCMI_ESUR_FSU_Msk                           
#define DCMI_ESUR_LSU_Pos          (8U)                                        
#define DCMI_ESUR_LSU_Msk          (0xFFU << DCMI_ESUR_LSU_Pos)                /*!< 0x0000FF00 */
#define DCMI_ESUR_LSU              DCMI_ESUR_LSU_Msk                           
#define DCMI_ESUR_LEU_Pos          (16U)                                       
#define DCMI_ESUR_LEU_Msk          (0xFFU << DCMI_ESUR_LEU_Pos)                /*!< 0x00FF0000 */
#define DCMI_ESUR_LEU              DCMI_ESUR_LEU_Msk                           
#define DCMI_ESUR_FEU_Pos          (24U)                                       
#define DCMI_ESUR_FEU_Msk          (0xFFU << DCMI_ESUR_FEU_Pos)                /*!< 0xFF000000 */
#define DCMI_ESUR_FEU              DCMI_ESUR_FEU_Msk                           

/********************  Bits definition for DCMI_CWSTRT register  ******************/
#define DCMI_CWSTRT_HOFFCNT_Pos    (0U)                                        
#define DCMI_CWSTRT_HOFFCNT_Msk    (0x3FFFU << DCMI_CWSTRT_HOFFCNT_Pos)        /*!< 0x00003FFF */
#define DCMI_CWSTRT_HOFFCNT        DCMI_CWSTRT_HOFFCNT_Msk                     
#define DCMI_CWSTRT_VST_Pos        (16U)                                       
#define DCMI_CWSTRT_VST_Msk        (0x1FFFU << DCMI_CWSTRT_VST_Pos)            /*!< 0x1FFF0000 */
#define DCMI_CWSTRT_VST            DCMI_CWSTRT_VST_Msk                         

/********************  Bits definition for DCMI_CWSIZE register  ******************/
#define DCMI_CWSIZE_CAPCNT_Pos     (0U)                                        
#define DCMI_CWSIZE_CAPCNT_Msk     (0x3FFFU << DCMI_CWSIZE_CAPCNT_Pos)         /*!< 0x00003FFF */
#define DCMI_CWSIZE_CAPCNT         DCMI_CWSIZE_CAPCNT_Msk                      
#define DCMI_CWSIZE_VLINE_Pos      (16U)                                       
#define DCMI_CWSIZE_VLINE_Msk      (0x3FFFU << DCMI_CWSIZE_VLINE_Pos)          /*!< 0x3FFF0000 */
#define DCMI_CWSIZE_VLINE          DCMI_CWSIZE_VLINE_Msk                       

/********************  Bits definition for DCMI_DR register  *********************/
#define DCMI_DR_BYTE0_Pos          (0U)                                        
#define DCMI_DR_BYTE0_Msk          (0xFFU << DCMI_DR_BYTE0_Pos)                /*!< 0x000000FF */
#define DCMI_DR_BYTE0              DCMI_DR_BYTE0_Msk                           
#define DCMI_DR_BYTE1_Pos          (8U)                                        
#define DCMI_DR_BYTE1_Msk          (0xFFU << DCMI_DR_BYTE1_Pos)                /*!< 0x0000FF00 */
#define DCMI_DR_BYTE1              DCMI_DR_BYTE1_Msk                           
#define DCMI_DR_BYTE2_Pos          (16U)                                       
#define DCMI_DR_BYTE2_Msk          (0xFFU << DCMI_DR_BYTE2_Pos)                /*!< 0x00FF0000 */
#define DCMI_DR_BYTE2              DCMI_DR_BYTE2_Msk                           
#define DCMI_DR_BYTE3_Pos          (24U)                                       
#define DCMI_DR_BYTE3_Msk          (0xFFU << DCMI_DR_BYTE3_Pos)                /*!< 0xFF000000 */
#define DCMI_DR_BYTE3              DCMI_DR_BYTE3_Msk                           
/* Exported types ------------------------------------------------------------*/
/** @defgroup DCMI_Exported_Types DCMI Exported Types
  * @{
  */
/**
  * @brief  HAL DCMI State structures definition
  */ 
typedef enum
{
  HAL_DCMI_STATE_RESET             = 0x00U,  /*!< DCMI not yet initialized or disabled  */
  HAL_DCMI_STATE_READY             = 0x01U,  /*!< DCMI initialized and ready for use    */
  HAL_DCMI_STATE_BUSY              = 0x02U,  /*!< DCMI internal processing is ongoing   */
  HAL_DCMI_STATE_TIMEOUT           = 0x03U,  /*!< DCMI timeout state                    */
  HAL_DCMI_STATE_ERROR             = 0x04U,  /*!< DCMI error state                      */
  HAL_DCMI_STATE_SUSPENDED         = 0x05U   /*!< DCMI suspend state                    */
}HAL_DCMI_StateTypeDef;

/** 
  * @brief   DCMIEx Embedded Synchronisation CODE Init structure definition
  */ 
typedef struct
{
  uint8_t FrameStartCode; /*!< Specifies the code of the frame start delimiter. */
  uint8_t LineStartCode;  /*!< Specifies the code of the line start delimiter.  */
  uint8_t LineEndCode;    /*!< Specifies the code of the line end delimiter.    */
  uint8_t FrameEndCode;   /*!< Specifies the code of the frame end delimiter.   */
}DCMI_CodesInitTypeDef;

/** 
  * @brief   DCMI Init structure definition
  */  
/** 
  * @brief   DCMI Init structure definition
  */  
typedef struct
{
  uint32_t  SynchroMode;                /*!< Specifies the Synchronization Mode: Hardware or Embedded.
                                             This parameter can be a value of @ref DCMI_Synchronization_Mode   */

  uint32_t  PCKPolarity;                /*!< Specifies the Pixel clock polarity: Falling or Rising.
                                             This parameter can be a value of @ref DCMI_PIXCK_Polarity         */

  uint32_t  VSPolarity;                 /*!< Specifies the Vertical synchronization polarity: High or Low.
                                             This parameter can be a value of @ref DCMI_VSYNC_Polarity         */

  uint32_t  HSPolarity;                 /*!< Specifies the Horizontal synchronization polarity: High or Low.
                                             This parameter can be a value of @ref DCMI_HSYNC_Polarity         */

  uint32_t  CaptureRate;                /*!< Specifies the frequency of frame capture: All, 1/2 or 1/4.
                                             This parameter can be a value of @ref DCMI_Capture_Rate           */

  uint32_t  ExtendedDataMode;           /*!< Specifies the data width: 8-bit, 10-bit, 12-bit or 14-bit.
                                             This parameter can be a value of @ref DCMI_Extended_Data_Mode     */

  DCMI_CodesInitTypeDef SyncroCode;     /*!< Specifies the code of the frame start delimiter.                  */

  uint32_t JPEGMode;                    /*!< Enable or Disable the JPEG mode
                                             This parameter can be a value of @ref DCMI_MODE_JPEG              */
}DCMI_InitTypeDef;

/**
  * @}
  */
/** 
  * @brief  DCMI handle Structure definition
  */
typedef struct
{
  DCMI_TypeDef                  *Instance;           /*!< DCMI Register base address   */

  DCMI_InitTypeDef              Init;                /*!< DCMI parameters              */

  HAL_LockTypeDef               Lock;                /*!< DCMI locking object          */

  __IO HAL_DCMI_StateTypeDef    State;               /*!< DCMI state                   */

  __IO uint32_t                 XferCount;           /*!< DMA transfer counter         */

  __IO uint32_t                 XferSize;            /*!< DMA transfer size            */

  uint32_t                      XferTransferNumber;  /*!< DMA transfer number          */

  uint32_t                      pBuffPtr;            /*!< Pointer to DMA output buffer */

  DMA_HandleTypeDef             *DMA_Handle;         /*!< Pointer to the DMA handler   */

  __IO uint32_t                 ErrorCode;           /*!< DCMI Error code              */

}DCMI_HandleTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DCMI_Exported_Constants DCMI Exported Constants
  * @{
  */

/** @defgroup DCMI_Error_Code DCMI Error Code
  * @{
  */
#define HAL_DCMI_ERROR_NONE      0x00000000U    /*!< No error              */
#define HAL_DCMI_ERROR_OVR       0x00000001U    /*!< Overrun error         */
#define HAL_DCMI_ERROR_SYNC      0x00000002U    /*!< Synchronization error */
#define HAL_DCMI_ERROR_TIMEOUT   0x00000020U    /*!< Timeout error         */
#define HAL_DCMI_ERROR_DMA       0x00000040U    /*!< DMA error             */
/**
  * @}
  */

/** @defgroup DCMI_Capture_Mode DCMI Capture Mode
  * @{
  */ 
#define DCMI_MODE_CONTINUOUS         0x00000000U               /*!< The received data are transferred continuously
                                                                    into the destination memory through the DMA             */
#define DCMI_MODE_SNAPSHOT             ((uint32_t)DCMI_CR_CM)  /*!< Once activated, the interface waits for the start of
                                                                    frame and then transfers a single frame through the DMA */
/**
  * @}
  */

/** @defgroup DCMI_Synchronization_Mode DCMI Synchronization Mode
  * @{
  */
#define DCMI_SYNCHRO_HARDWARE        0x00000000U               /*!< Hardware synchronization data capture (frame/line start/stop)
                                                                    is synchronized with the HSYNC/VSYNC signals                  */
#define DCMI_SYNCHRO_EMBEDDED        ((uint32_t)DCMI_CR_ESS)   /*!< Embedded synchronization data capture is synchronized with
                                                                    synchronization codes embedded in the data flow               */

/**
  * @}
  */

/** @defgroup DCMI_PIXCK_Polarity DCMI PIXCK Polarity
  * @{
  */
#define DCMI_PCKPOLARITY_FALLING     0x00000000U                 /*!< Pixel clock active on Falling edge */
#define DCMI_PCKPOLARITY_RISING      ((uint32_t)DCMI_CR_PCKPOL)  /*!< Pixel clock active on Rising edge  */

/**
  * @}
  */

/** @defgroup DCMI_VSYNC_Polarity DCMI VSYNC Polarity
  * @{
  */
#define DCMI_VSPOLARITY_LOW          0x00000000U                /*!< Vertical synchronization active Low  */
#define DCMI_VSPOLARITY_HIGH         ((uint32_t)DCMI_CR_VSPOL)  /*!< Vertical synchronization active High */

/**
  * @}
  */

/** @defgroup DCMI_HSYNC_Polarity DCMI HSYNC Polarity
  * @{
  */ 
#define DCMI_HSPOLARITY_LOW          0x00000000U                /*!< Horizontal synchronization active Low  */
#define DCMI_HSPOLARITY_HIGH         ((uint32_t)DCMI_CR_HSPOL)  /*!< Horizontal synchronization active High */

/**
  * @}
  */

/** @defgroup DCMI_MODE_JPEG DCMI MODE JPEG
  * @{
  */
#define DCMI_JPEG_DISABLE            0x00000000U               /*!< Mode JPEG Disabled  */
#define DCMI_JPEG_ENABLE             ((uint32_t)DCMI_CR_JPEG)  /*!< Mode JPEG Enabled   */

/**
  * @}
  */

/** @defgroup DCMI_Capture_Rate DCMI Capture Rate
  * @{
  */
#define DCMI_CR_ALL_FRAME            0x00000000U                 /*!< All frames are captured        */
#define DCMI_CR_ALTERNATE_2_FRAME    ((uint32_t)DCMI_CR_FCRC_0)  /*!< Every alternate frame captured */
#define DCMI_CR_ALTERNATE_4_FRAME    ((uint32_t)DCMI_CR_FCRC_1)  /*!< One frame in 4 frames captured */

/**
  * @}
  */

/** @defgroup DCMI_Extended_Data_Mode DCMI Extended Data Mode
  * @{
  */
#define DCMI_EXTEND_DATA_8B     0x00000000U                                  /*!< Interface captures 8-bit data on every pixel clock  */
#define DCMI_EXTEND_DATA_10B    ((uint32_t)DCMI_CR_EDM_0)                    /*!< Interface captures 10-bit data on every pixel clock */
#define DCMI_EXTEND_DATA_12B    ((uint32_t)DCMI_CR_EDM_1)                    /*!< Interface captures 12-bit data on every pixel clock */
#define DCMI_EXTEND_DATA_14B    ((uint32_t)(DCMI_CR_EDM_0 | DCMI_CR_EDM_1))  /*!< Interface captures 14-bit data on every pixel clock */

/**
  * @}
  */

/** @defgroup DCMI_Window_Coordinate DCMI Window Coordinate
  * @{
  */
#define DCMI_WINDOW_COORDINATE    0x3FFFU   /*!< Window coordinate */

/**
  * @}
  */

/** @defgroup DCMI_Window_Height DCMI Window Height
  * @{
  */ 
#define DCMI_WINDOW_HEIGHT        0x1FFFU   /*!< Window Height */

/**
  * @}
  */

/** @defgroup DCMI_Window_Vertical_Line DCMI Window Vertical Line
  * @{
  */
#define DCMI_POSITION_CWSIZE_VLINE         (uint32_t)DCMI_CWSIZE_VLINE_Pos /*!< Required left shift to set crop window vertical line count       */
#define DCMI_POSITION_CWSTRT_VST           (uint32_t)DCMI_CWSTRT_VST_Pos   /*!< Required left shift to set crop window vertical start line count */

/**
  * @}
  */

/** @defgroup DCMI_interrupt_sources  DCMI interrupt sources
  * @{
  */
#define DCMI_IT_FRAME    ((uint32_t)DCMI_IER_FRAME_IE)    /*!< Capture complete interrupt      */
#define DCMI_IT_OVR      ((uint32_t)DCMI_IER_OVR_IE)      /*!< Overrun interrupt               */
#define DCMI_IT_ERR      ((uint32_t)DCMI_IER_ERR_IE)      /*!< Synchronization error interrupt */
#define DCMI_IT_VSYNC    ((uint32_t)DCMI_IER_VSYNC_IE)    /*!< VSYNC interrupt                 */
#define DCMI_IT_LINE     ((uint32_t)DCMI_IER_LINE_IE)     /*!< Line interrupt                  */
/**
  * @}
  */

/** @defgroup DCMI_Flags DCMI Flags
  * @{
  */

/** 
  * @brief   DCMI SR register
  */
#define DCMI_FLAG_HSYNC     ((uint32_t)DCMI_SR_INDEX|DCMI_SR_HSYNC) /*!< HSYNC pin state (active line / synchronization between lines)   */
#define DCMI_FLAG_VSYNC     ((uint32_t)DCMI_SR_INDEX|DCMI_SR_VSYNC) /*!< VSYNC pin state (active frame / synchronization between frames) */
#define DCMI_FLAG_FNE       ((uint32_t)DCMI_SR_INDEX|DCMI_SR_FNE)   /*!< FIFO not empty flag                                             */
/** 
  * @brief   DCMI RIS register
  */ 
#define DCMI_FLAG_FRAMERI    ((uint32_t)DCMI_RISR_FRAME_RIS)  /*!< Frame capture complete interrupt flag */
#define DCMI_FLAG_OVRRI      ((uint32_t)DCMI_RISR_OVR_RIS)    /*!< Overrun interrupt flag                */
#define DCMI_FLAG_ERRRI      ((uint32_t)DCMI_RISR_ERR_RIS)    /*!< Synchronization error interrupt flag  */
#define DCMI_FLAG_VSYNCRI    ((uint32_t)DCMI_RISR_VSYNC_RIS)  /*!< VSYNC interrupt flag                  */
#define DCMI_FLAG_LINERI     ((uint32_t)DCMI_RISR_LINE_RIS)   /*!< Line interrupt flag                   */
/** 
  * @brief   DCMI MIS register
  */ 
#define DCMI_FLAG_FRAMEMI    ((uint32_t)DCMI_MIS_INDEX|DCMI_MIS_FRAME_MIS)  /*!< DCMI Frame capture complete masked interrupt status */
#define DCMI_FLAG_OVRMI      ((uint32_t)DCMI_MIS_INDEX|DCMI_MIS_OVR_MIS  )  /*!< DCMI Overrun masked interrupt status                */
#define DCMI_FLAG_ERRMI      ((uint32_t)DCMI_MIS_INDEX|DCMI_MIS_ERR_MIS  )  /*!< DCMI Synchronization error masked interrupt status  */
#define DCMI_FLAG_VSYNCMI    ((uint32_t)DCMI_MIS_INDEX|DCMI_MIS_VSYNC_MIS)  /*!< DCMI VSYNC masked interrupt status                  */
#define DCMI_FLAG_LINEMI     ((uint32_t)DCMI_MIS_INDEX|DCMI_MIS_LINE_MIS )  /*!< DCMI Line masked interrupt status                   */
/**
  * @}
  */

/**
  * @}
  */
 
/* Exported macro ------------------------------------------------------------*/
/** @defgroup DCMI_Exported_Macros DCMI Exported Macros
  * @{
  */
  
/** @brief Reset DCMI handle state
  * @param  __HANDLE__ specifies the DCMI handle.
  * @retval None
  */
#define __HAL_DCMI_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DCMI_STATE_RESET)

/**
  * @brief  Enable the DCMI.
  * @param  __HANDLE__ DCMI handle
  * @retval None
  */
#define __HAL_DCMI_ENABLE(__HANDLE__)    ((__HANDLE__)->Instance->CR |= DCMI_CR_ENABLE)

/**
  * @brief  Disable the DCMI.
  * @param  __HANDLE__ DCMI handle
  * @retval None
  */
#define __HAL_DCMI_DISABLE(__HANDLE__)   ((__HANDLE__)->Instance->CR &= ~(DCMI_CR_ENABLE))

/* Interrupt & Flag management */
/**
  * @brief  Get the DCMI pending flag.
  * @param  __HANDLE__ DCMI handle
  * @param  __FLAG__ Get the specified flag.
  *         This parameter can be one of the following values (no combination allowed)
  *            @arg DCMI_FLAG_HSYNC: HSYNC pin state (active line / synchronization between lines)
  *            @arg DCMI_FLAG_VSYNC: VSYNC pin state (active frame / synchronization between frames)
  *            @arg DCMI_FLAG_FNE: FIFO empty flag
  *            @arg DCMI_FLAG_FRAMERI: Frame capture complete flag mask
  *            @arg DCMI_FLAG_OVRRI: Overrun flag mask
  *            @arg DCMI_FLAG_ERRRI: Synchronization error flag mask
  *            @arg DCMI_FLAG_VSYNCRI: VSYNC flag mask
  *            @arg DCMI_FLAG_LINERI: Line flag mask
  *            @arg DCMI_FLAG_FRAMEMI: DCMI Capture complete masked interrupt status
  *            @arg DCMI_FLAG_OVRMI: DCMI Overrun masked interrupt status
  *            @arg DCMI_FLAG_ERRMI: DCMI Synchronization error masked interrupt status
  *            @arg DCMI_FLAG_VSYNCMI: DCMI VSYNC masked interrupt status
  *            @arg DCMI_FLAG_LINEMI: DCMI Line masked interrupt status
  * @retval The state of FLAG.
  */
#define __HAL_DCMI_GET_FLAG(__HANDLE__, __FLAG__)\
((((__FLAG__) & (DCMI_SR_INDEX|DCMI_MIS_INDEX)) == 0x0U)? ((__HANDLE__)->Instance->RISR & (__FLAG__)) :\
 (((__FLAG__) & DCMI_SR_INDEX) == 0x0U)? ((__HANDLE__)->Instance->MISR & (__FLAG__)) : ((__HANDLE__)->Instance->SR & (__FLAG__)))

/**
  * @brief  Clear the DCMI pending flags.
  * @param  __HANDLE__ DCMI handle
  * @param  __FLAG__ specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *            @arg DCMI_FLAG_FRAMERI: Frame capture complete flag mask
  *            @arg DCMI_FLAG_OVRRI: Overrun flag mask
  *            @arg DCMI_FLAG_ERRRI: Synchronization error flag mask
  *            @arg DCMI_FLAG_VSYNCRI: VSYNC flag mask
  *            @arg DCMI_FLAG_LINERI: Line flag mask
  * @retval None
  */
#define __HAL_DCMI_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = (__FLAG__))

/**
  * @brief  Enable the specified DCMI interrupts.
  * @param  __HANDLE__    DCMI handle
  * @param  __INTERRUPT__ specifies the DCMI interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg DCMI_IT_FRAME: Frame capture complete interrupt mask
  *            @arg DCMI_IT_OVR: Overrun interrupt mask
  *            @arg DCMI_IT_ERR: Synchronization error interrupt mask
  *            @arg DCMI_IT_VSYNC: VSYNC interrupt mask
  *            @arg DCMI_IT_LINE: Line interrupt mask
  * @retval None
  */
#define __HAL_DCMI_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER |= (__INTERRUPT__))

/**
  * @brief  Disable the specified DCMI interrupts.
  * @param  __HANDLE__ DCMI handle
  * @param  __INTERRUPT__ specifies the DCMI interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg DCMI_IT_FRAME: Frame capture complete interrupt mask
  *            @arg DCMI_IT_OVR: Overrun interrupt mask
  *            @arg DCMI_IT_ERR: Synchronization error interrupt mask
  *            @arg DCMI_IT_VSYNC: VSYNC interrupt mask
  *            @arg DCMI_IT_LINE: Line interrupt mask
  * @retval None
  */
#define __HAL_DCMI_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified DCMI interrupt has occurred or not.
  * @param  __HANDLE__ DCMI handle
  * @param  __INTERRUPT__ specifies the DCMI interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg DCMI_IT_FRAME: Frame capture complete interrupt mask
  *            @arg DCMI_IT_OVR: Overrun interrupt mask
  *            @arg DCMI_IT_ERR: Synchronization error interrupt mask
  *            @arg DCMI_IT_VSYNC: VSYNC interrupt mask
  *            @arg DCMI_IT_LINE: Line interrupt mask
  * @retval The state of INTERRUPT.
  */
#define __HAL_DCMI_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->MISR & (__INTERRUPT__))

/**
  * @}
  */
  
/* Exported functions --------------------------------------------------------*/
/** @addtogroup DCMI_Exported_Functions DCMI Exported Functions
  * @{
  */

/** @addtogroup DCMI_Exported_Functions_Group1 Initialization and Configuration functions
 * @{
 */
/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_DCMI_Init(DCMI_HandleTypeDef *hdcmi);
HAL_StatusTypeDef HAL_DCMI_DeInit(DCMI_HandleTypeDef *hdcmi);
void              HAL_DCMI_MspInit(DCMI_HandleTypeDef* hdcmi);
void              HAL_DCMI_MspDeInit(DCMI_HandleTypeDef* hdcmi);
/**
  * @}
  */

/** @addtogroup DCMI_Exported_Functions_Group2 IO operation functions
 * @{
 */
/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_DCMI_Start_DMA(DCMI_HandleTypeDef* hdcmi, uint32_t DCMI_Mode, uint32_t pData, uint32_t Length);
HAL_StatusTypeDef HAL_DCMI_Stop(DCMI_HandleTypeDef* hdcmi);
HAL_StatusTypeDef HAL_DCMI_Suspend(DCMI_HandleTypeDef* hdcmi);
HAL_StatusTypeDef HAL_DCMI_Resume(DCMI_HandleTypeDef* hdcmi);
void              HAL_DCMI_ErrorCallback(DCMI_HandleTypeDef *hdcmi);
void              HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi);
void              HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi);
void              HAL_DCMI_VsyncEventCallback(DCMI_HandleTypeDef *hdcmi);
void              HAL_DCMI_VsyncCallback(DCMI_HandleTypeDef *hdcmi);
void              HAL_DCMI_HsyncCallback(DCMI_HandleTypeDef *hdcmi);
void              HAL_DCMI_IRQHandler(DCMI_HandleTypeDef *hdcmi);
/**
  * @}
  */
  
/** @addtogroup DCMI_Exported_Functions_Group3 Peripheral Control functions
 * @{
 */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_DCMI_ConfigCrop(DCMI_HandleTypeDef *hdcmi, uint32_t X0, uint32_t Y0, uint32_t XSize, uint32_t YSize);
HAL_StatusTypeDef HAL_DCMI_EnableCrop(DCMI_HandleTypeDef *hdcmi);
HAL_StatusTypeDef HAL_DCMI_DisableCrop(DCMI_HandleTypeDef *hdcmi);
/**
  * @}
  */
  
/** @addtogroup DCMI_Exported_Functions_Group4 Peripheral State functions
 * @{
 */
/* Peripheral State functions *************************************************/
HAL_DCMI_StateTypeDef HAL_DCMI_GetState(DCMI_HandleTypeDef *hdcmi);
uint32_t              HAL_DCMI_GetError(DCMI_HandleTypeDef *hdcmi);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup DCMI_Private_Constants DCMI Private Constants
  * @{
  */
#define DCMI_MIS_INDEX        0x1000U /*!< DCMI MIS register index */
#define DCMI_SR_INDEX         0x2000U /*!< DCMI SR register index  */
/**
  * @}
  */   
/* Private macro -------------------------------------------------------------*/
/** @defgroup DCMI_Private_Macros DCMI Private Macros
  * @{
  */
#define IS_DCMI_CAPTURE_MODE(MODE)(((MODE) == DCMI_MODE_CONTINUOUS) || \
                                   ((MODE) == DCMI_MODE_SNAPSHOT))

#define IS_DCMI_SYNCHRO(MODE)(((MODE) == DCMI_SYNCHRO_HARDWARE) || \
                              ((MODE) == DCMI_SYNCHRO_EMBEDDED))
                              
#define IS_DCMI_PCKPOLARITY(POLARITY)(((POLARITY) == DCMI_PCKPOLARITY_FALLING) || \
                                      ((POLARITY) == DCMI_PCKPOLARITY_RISING))
                                      
#define IS_DCMI_VSPOLARITY(POLARITY)(((POLARITY) == DCMI_VSPOLARITY_LOW) || \
                                     ((POLARITY) == DCMI_VSPOLARITY_HIGH))
                                     
#define IS_DCMI_HSPOLARITY(POLARITY)(((POLARITY) == DCMI_HSPOLARITY_LOW) || \
                                     ((POLARITY) == DCMI_HSPOLARITY_HIGH))
                                     
#define IS_DCMI_MODE_JPEG(JPEG_MODE)(((JPEG_MODE) == DCMI_JPEG_DISABLE) || \
                                     ((JPEG_MODE) == DCMI_JPEG_ENABLE))
                                     
#define IS_DCMI_CAPTURE_RATE(RATE) (((RATE) == DCMI_CR_ALL_FRAME)         || \
                                    ((RATE) == DCMI_CR_ALTERNATE_2_FRAME) || \
                                    ((RATE) == DCMI_CR_ALTERNATE_4_FRAME))
                                    
#define IS_DCMI_EXTENDED_DATA(DATA)(((DATA) == DCMI_EXTEND_DATA_8B)  || \
                                    ((DATA) == DCMI_EXTEND_DATA_10B) || \
                                    ((DATA) == DCMI_EXTEND_DATA_12B) || \
                                    ((DATA) == DCMI_EXTEND_DATA_14B))
                                    
#define IS_DCMI_WINDOW_COORDINATE(COORDINATE) ((COORDINATE) <= DCMI_WINDOW_COORDINATE)

#define IS_DCMI_WINDOW_HEIGHT(HEIGHT) ((HEIGHT) <= DCMI_WINDOW_HEIGHT)
/******************************* DCMI Instances *******************************/
#define IS_DCMI_ALL_INSTANCE(INSTANCE) ((INSTANCE) == DCMI)
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup DCMI_Private_Functions DCMI Private Functions
  * @{
  */
  
/**
  * @}
  */

#endif /* __STM32F4xx_HAL_DCMI_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
