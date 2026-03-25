/******************************************************************************
*@file  : hal_dma2d.h
*@brief : GPIO HAL module driver.
******************************************************************************/

#ifndef __HAL_DMA2D_H__
#define __HAL_DMA2D_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "hal.h" 


/* Exported types ------------------------------------------------------------*/
/** @defgroup DMA2D_Exported_Types DMA2D Exported Types
  * @{
  */
#define MAX_DMA2D_LAYER  2U  /*!< DMA2D maximum number of layers */


/********************  Bit definition for DMA2D_CR register  ******************/
#define DMA2D_CR_START_Pos         (0U)
#define DMA2D_CR_START_Msk         (0x1UL << DMA2D_CR_START_Pos)               /*!< 0x00000001 */
#define DMA2D_CR_START             DMA2D_CR_START_Msk                          /*!< Start transfer                          */
#define DMA2D_CR_SUSP_Pos          (1U)
#define DMA2D_CR_SUSP_Msk          (0x1UL << DMA2D_CR_SUSP_Pos)                /*!< 0x00000002 */
#define DMA2D_CR_SUSP              DMA2D_CR_SUSP_Msk                           /*!< Suspend transfer                        */
#define DMA2D_CR_ABORT_Pos         (2U)
#define DMA2D_CR_ABORT_Msk         (0x1UL << DMA2D_CR_ABORT_Pos)               /*!< 0x00000004 */
#define DMA2D_CR_ABORT             DMA2D_CR_ABORT_Msk                          /*!< Abort transfer                          */
#define DMA2D_CR_TEIE_Pos          (8U)
#define DMA2D_CR_TEIE_Msk          (0x1UL << DMA2D_CR_TEIE_Pos)                /*!< 0x00000100 */
#define DMA2D_CR_TEIE              DMA2D_CR_TEIE_Msk                           /*!< Transfer Error Interrupt Enable         */
#define DMA2D_CR_TCIE_Pos          (9U)
#define DMA2D_CR_TCIE_Msk          (0x1UL << DMA2D_CR_TCIE_Pos)                /*!< 0x00000200 */
#define DMA2D_CR_TCIE              DMA2D_CR_TCIE_Msk                           /*!< Transfer Complete Interrupt Enable      */
#define DMA2D_CR_TWIE_Pos          (10U)
#define DMA2D_CR_TWIE_Msk          (0x1UL << DMA2D_CR_TWIE_Pos)                /*!< 0x00000400 */
#define DMA2D_CR_TWIE              DMA2D_CR_TWIE_Msk                           /*!< Transfer Watermark Interrupt Enable     */
#define DMA2D_CR_CAEIE_Pos         (11U)
#define DMA2D_CR_CAEIE_Msk         (0x1UL << DMA2D_CR_CAEIE_Pos)               /*!< 0x00000800 */
#define DMA2D_CR_CAEIE             DMA2D_CR_CAEIE_Msk                          /*!< CLUT Access Error Interrupt Enable      */
#define DMA2D_CR_CTCIE_Pos         (12U)
#define DMA2D_CR_CTCIE_Msk         (0x1UL << DMA2D_CR_CTCIE_Pos)               /*!< 0x00001000 */
#define DMA2D_CR_CTCIE             DMA2D_CR_CTCIE_Msk                          /*!< CLUT Transfer Complete Interrupt Enable */
#define DMA2D_CR_CEIE_Pos          (13U)
#define DMA2D_CR_CEIE_Msk          (0x1UL << DMA2D_CR_CEIE_Pos)                /*!< 0x00002000 */
#define DMA2D_CR_CEIE              DMA2D_CR_CEIE_Msk                           /*!< Configuration Error Interrupt Enable    */
#define DMA2D_CR_MODE_Pos          (16U)
#define DMA2D_CR_MODE_Msk          (0x3UL << DMA2D_CR_MODE_Pos)                /*!< 0x00030000 */
#define DMA2D_CR_MODE              DMA2D_CR_MODE_Msk                           /*!< DMA2D Mode[1:0]                         */
#define DMA2D_CR_MODE_0            (0x1UL << DMA2D_CR_MODE_Pos)                 /*!< 0x00010000 */
#define DMA2D_CR_MODE_1            (0x2UL << DMA2D_CR_MODE_Pos)                 /*!< 0x00020000 */
#define DMA2D_CR_AHB_LOCK_Pos      (18U)
#define DMA2D_CR_AHB_LOCK_Msk      (0x1UL << DMA2D_CR_AHB_LOCK_Pos)             /*!< 0x00040000 */
#define DMA2D_CR_AHB_LOCK          DMA2D_CR_AHB_LOCK_Msk                        /*!< AHB lock Enable */


/********************  Bit definition for DMA2D_ISR register  *****************/
#define DMA2D_ISR_TEIF_Pos         (0U)
#define DMA2D_ISR_TEIF_Msk         (0x1UL << DMA2D_ISR_TEIF_Pos)               /*!< 0x00000001 */
#define DMA2D_ISR_TEIF             DMA2D_ISR_TEIF_Msk                          /*!< Transfer Error Interrupt Flag         */
#define DMA2D_ISR_TCIF_Pos         (1U)
#define DMA2D_ISR_TCIF_Msk         (0x1UL << DMA2D_ISR_TCIF_Pos)               /*!< 0x00000002 */
#define DMA2D_ISR_TCIF             DMA2D_ISR_TCIF_Msk                          /*!< Transfer Complete Interrupt Flag      */
#define DMA2D_ISR_TWIF_Pos         (2U)
#define DMA2D_ISR_TWIF_Msk         (0x1UL << DMA2D_ISR_TWIF_Pos)               /*!< 0x00000004 */
#define DMA2D_ISR_TWIF             DMA2D_ISR_TWIF_Msk                          /*!< Transfer Watermark Interrupt Flag     */
#define DMA2D_ISR_CAEIF_Pos        (3U)
#define DMA2D_ISR_CAEIF_Msk        (0x1UL << DMA2D_ISR_CAEIF_Pos)              /*!< 0x00000008 */
#define DMA2D_ISR_CAEIF            DMA2D_ISR_CAEIF_Msk                         /*!< CLUT Access Error Interrupt Flag      */
#define DMA2D_ISR_CTCIF_Pos        (4U)
#define DMA2D_ISR_CTCIF_Msk        (0x1UL << DMA2D_ISR_CTCIF_Pos)              /*!< 0x00000010 */
#define DMA2D_ISR_CTCIF            DMA2D_ISR_CTCIF_Msk                         /*!< CLUT Transfer Complete Interrupt Flag */
#define DMA2D_ISR_CEIF_Pos         (5U)
#define DMA2D_ISR_CEIF_Msk         (0x1UL << DMA2D_ISR_CEIF_Pos)               /*!< 0x00000020 */
#define DMA2D_ISR_CEIF             DMA2D_ISR_CEIF_Msk                          /*!< Configuration Error Interrupt Flag    */

/********************  Bit definition for DMA2D_IFCR register  ****************/
#define DMA2D_IFCR_CTEIF_Pos       (0U)
#define DMA2D_IFCR_CTEIF_Msk       (0x1UL << DMA2D_IFCR_CTEIF_Pos)             /*!< 0x00000001 */
#define DMA2D_IFCR_CTEIF           DMA2D_IFCR_CTEIF_Msk                        /*!< Clears Transfer Error Interrupt Flag         */
#define DMA2D_IFCR_CTCIF_Pos       (1U)
#define DMA2D_IFCR_CTCIF_Msk       (0x1UL << DMA2D_IFCR_CTCIF_Pos)             /*!< 0x00000002 */
#define DMA2D_IFCR_CTCIF           DMA2D_IFCR_CTCIF_Msk                        /*!< Clears Transfer Complete Interrupt Flag      */
#define DMA2D_IFCR_CTWIF_Pos       (2U)
#define DMA2D_IFCR_CTWIF_Msk       (0x1UL << DMA2D_IFCR_CTWIF_Pos)             /*!< 0x00000004 */
#define DMA2D_IFCR_CTWIF           DMA2D_IFCR_CTWIF_Msk                        /*!< Clears Transfer Watermark Interrupt Flag     */
#define DMA2D_IFCR_CAECIF_Pos      (3U)
#define DMA2D_IFCR_CAECIF_Msk      (0x1UL << DMA2D_IFCR_CAECIF_Pos)            /*!< 0x00000008 */
#define DMA2D_IFCR_CAECIF          DMA2D_IFCR_CAECIF_Msk                       /*!< Clears CLUT Access Error Interrupt Flag      */
#define DMA2D_IFCR_CCTCIF_Pos      (4U)
#define DMA2D_IFCR_CCTCIF_Msk      (0x1UL << DMA2D_IFCR_CCTCIF_Pos)            /*!< 0x00000010 */
#define DMA2D_IFCR_CCTCIF          DMA2D_IFCR_CCTCIF_Msk                       /*!< Clears CLUT Transfer Complete Interrupt Flag */
#define DMA2D_IFCR_CCEIF_Pos       (5U)
#define DMA2D_IFCR_CCEIF_Msk       (0x1UL << DMA2D_IFCR_CCEIF_Pos)             /*!< 0x00000020 */
#define DMA2D_IFCR_CCEIF           DMA2D_IFCR_CCEIF_Msk                        /*!< Clears Configuration Error Interrupt Flag    */

/********************  Bit definition for DMA2D_FGMAR register  ***************/
#define DMA2D_FGMAR_MA_Pos         (0U)
#define DMA2D_FGMAR_MA_Msk         (0xFFFFFFFFUL << DMA2D_FGMAR_MA_Pos)        /*!< 0xFFFFFFFF */
#define DMA2D_FGMAR_MA             DMA2D_FGMAR_MA_Msk                          /*!< Foreground Memory Address */

/********************  Bit definition for DMA2D_FGOR register  ****************/
#define DMA2D_FGOR_LO_Pos          (0U)
#define DMA2D_FGOR_LO_Msk          (0x3FFFUL << DMA2D_FGOR_LO_Pos)             /*!< 0x00003FFF */
#define DMA2D_FGOR_LO              DMA2D_FGOR_LO_Msk                           /*!< Line Offset */

/********************  Bit definition for DMA2D_BGMAR register  ***************/
#define DMA2D_BGMAR_MA_Pos         (0U)
#define DMA2D_BGMAR_MA_Msk         (0xFFFFFFFFUL << DMA2D_BGMAR_MA_Pos)        /*!< 0xFFFFFFFF */
#define DMA2D_BGMAR_MA             DMA2D_BGMAR_MA_Msk                          /*!< Background Memory Address */

/********************  Bit definition for DMA2D_BGOR register  ****************/
#define DMA2D_BGOR_LO_Pos          (0U)
#define DMA2D_BGOR_LO_Msk          (0x3FFFUL << DMA2D_BGOR_LO_Pos)             /*!< 0x00003FFF */
#define DMA2D_BGOR_LO              DMA2D_BGOR_LO_Msk                           /*!< Line Offset */

/********************  Bit definition for DMA2D_FGPFCCR register  *************/
#define DMA2D_FGPFCCR_CM_Pos       (0U)
#define DMA2D_FGPFCCR_CM_Msk       (0xFUL << DMA2D_FGPFCCR_CM_Pos)             /*!< 0x0000000F */
#define DMA2D_FGPFCCR_CM           DMA2D_FGPFCCR_CM_Msk                        /*!< Input color mode CM[3:0] */
#define DMA2D_FGPFCCR_CM_0         (0x1UL << DMA2D_FGPFCCR_CM_Pos)              /*!< 0x00000001 */
#define DMA2D_FGPFCCR_CM_1         (0x2UL << DMA2D_FGPFCCR_CM_Pos)              /*!< 0x00000002 */
#define DMA2D_FGPFCCR_CM_2         (0x4UL << DMA2D_FGPFCCR_CM_Pos)              /*!< 0x00000004 */
#define DMA2D_FGPFCCR_CM_3         (0x8UL << DMA2D_FGPFCCR_CM_Pos)              /*!< 0x00000008 */
#define DMA2D_FGPFCCR_CCM_Pos      (4U)
#define DMA2D_FGPFCCR_CCM_Msk      (0x1UL << DMA2D_FGPFCCR_CCM_Pos)            /*!< 0x00000010 */
#define DMA2D_FGPFCCR_CCM          DMA2D_FGPFCCR_CCM_Msk                       /*!< CLUT Color mode */
#define DMA2D_FGPFCCR_START_Pos    (5U)
#define DMA2D_FGPFCCR_START_Msk    (0x1UL << DMA2D_FGPFCCR_START_Pos)          /*!< 0x00000020 */
#define DMA2D_FGPFCCR_START        DMA2D_FGPFCCR_START_Msk                     /*!< Start */
#define DMA2D_FGPFCCR_CS_Pos       (8U)
#define DMA2D_FGPFCCR_CS_Msk       (0xFFUL << DMA2D_FGPFCCR_CS_Pos)            /*!< 0x0000FF00 */
#define DMA2D_FGPFCCR_CS           DMA2D_FGPFCCR_CS_Msk                        /*!< CLUT size */
#define DMA2D_FGPFCCR_AM_Pos       (16U)
#define DMA2D_FGPFCCR_AM_Msk       (0x3UL << DMA2D_FGPFCCR_AM_Pos)             /*!< 0x00030000 */
#define DMA2D_FGPFCCR_AM           DMA2D_FGPFCCR_AM_Msk                        /*!< Alpha mode AM[1:0] */
#define DMA2D_FGPFCCR_AM_0         (0x1UL << DMA2D_FGPFCCR_AM_Pos)              /*!< 0x00010000 */
#define DMA2D_FGPFCCR_AM_1         (0x2UL << DMA2D_FGPFCCR_AM_Pos)              /*!< 0x00020000 */
#define DMA2D_FGPFCCR_CSS_Pos      (18U)
#define DMA2D_FGPFCCR_CSS_Msk      (0x3UL << DMA2D_FGPFCCR_CSS_Pos)            /*!< 0x000C0000 */
#define DMA2D_FGPFCCR_CSS          DMA2D_FGPFCCR_CSS_Msk                       /* !< Chroma Sub-Sampling */
#define DMA2D_FGPFCCR_CSS_0        (0x1UL << DMA2D_FGPFCCR_CSS_Pos)             /*!< 0x00040000 */
#define DMA2D_FGPFCCR_CSS_1        (0x2UL << DMA2D_FGPFCCR_CSS_Pos)             /*!< 0x00080000 */
#define DMA2D_FGPFCCR_AI_Pos       (20U)
#define DMA2D_FGPFCCR_AI_Msk       (0x1UL << DMA2D_FGPFCCR_AI_Pos)             /*!< 0x00100000 */
#define DMA2D_FGPFCCR_AI           DMA2D_FGPFCCR_AI_Msk                        /*!< Foreground Input Alpha Inverted */
#define DMA2D_FGPFCCR_RBS_Pos      (21U)
#define DMA2D_FGPFCCR_RBS_Msk      (0x1UL << DMA2D_FGPFCCR_RBS_Pos)            /*!< 0x00200000 */
#define DMA2D_FGPFCCR_RBS          DMA2D_FGPFCCR_RBS_Msk                       /*!< Foreground Input Red Blue Swap */
#define DMA2D_FGPFCCR_ALPHA_Pos    (24U)
#define DMA2D_FGPFCCR_ALPHA_Msk    (0xFFUL << DMA2D_FGPFCCR_ALPHA_Pos)         /*!< 0xFF000000 */
#define DMA2D_FGPFCCR_ALPHA        DMA2D_FGPFCCR_ALPHA_Msk                     /*!< Alpha value */

/********************  Bit definition for DMA2D_FGCOLR register  **************/
#define DMA2D_FGCOLR_BLUE_Pos      (0U)
#define DMA2D_FGCOLR_BLUE_Msk      (0xFFUL << DMA2D_FGCOLR_BLUE_Pos)           /*!< 0x000000FF */
#define DMA2D_FGCOLR_BLUE          DMA2D_FGCOLR_BLUE_Msk                       /*!< Foreground Blue Value */
#define DMA2D_FGCOLR_GREEN_Pos     (8U)
#define DMA2D_FGCOLR_GREEN_Msk     (0xFFUL << DMA2D_FGCOLR_GREEN_Pos)          /*!< 0x0000FF00 */
#define DMA2D_FGCOLR_GREEN         DMA2D_FGCOLR_GREEN_Msk                      /*!< Foreground Green Value */
#define DMA2D_FGCOLR_RED_Pos       (16U)
#define DMA2D_FGCOLR_RED_Msk       (0xFFUL << DMA2D_FGCOLR_RED_Pos)            /*!< 0x00FF0000 */
#define DMA2D_FGCOLR_RED           DMA2D_FGCOLR_RED_Msk                        /*!< Foreground Red Value */

/********************  Bit definition for DMA2D_BGPFCCR register  *************/
#define DMA2D_BGPFCCR_CM_Pos       (0U)
#define DMA2D_BGPFCCR_CM_Msk       (0xFUL << DMA2D_BGPFCCR_CM_Pos)             /*!< 0x0000000F */
#define DMA2D_BGPFCCR_CM           DMA2D_BGPFCCR_CM_Msk                        /*!< Input color mode CM[3:0] */
#define DMA2D_BGPFCCR_CM_0         (0x1UL << DMA2D_BGPFCCR_CM_Pos)              /*!< 0x00000001 */
#define DMA2D_BGPFCCR_CM_1         (0x2UL << DMA2D_BGPFCCR_CM_Pos)              /*!< 0x00000002 */
#define DMA2D_BGPFCCR_CM_2         (0x4UL << DMA2D_BGPFCCR_CM_Pos)              /*!< 0x00000004 */
#define DMA2D_BGPFCCR_CM_3         (0x8UL << DMA2D_BGPFCCR_CM_Pos)              /*!< 0x00000008 */
#define DMA2D_BGPFCCR_CCM_Pos      (4U)
#define DMA2D_BGPFCCR_CCM_Msk      (0x1UL << DMA2D_BGPFCCR_CCM_Pos)            /*!< 0x00000010 */
#define DMA2D_BGPFCCR_CCM          DMA2D_BGPFCCR_CCM_Msk                       /*!< CLUT Color mode */
#define DMA2D_BGPFCCR_START_Pos    (5U)
#define DMA2D_BGPFCCR_START_Msk    (0x1UL << DMA2D_BGPFCCR_START_Pos)          /*!< 0x00000020 */
#define DMA2D_BGPFCCR_START        DMA2D_BGPFCCR_START_Msk                     /*!< Start */
#define DMA2D_BGPFCCR_CS_Pos       (8U)
#define DMA2D_BGPFCCR_CS_Msk       (0xFFUL << DMA2D_BGPFCCR_CS_Pos)            /*!< 0x0000FF00 */
#define DMA2D_BGPFCCR_CS           DMA2D_BGPFCCR_CS_Msk                        /*!< CLUT size */
#define DMA2D_BGPFCCR_AM_Pos       (16U)
#define DMA2D_BGPFCCR_AM_Msk       (0x3UL << DMA2D_BGPFCCR_AM_Pos)             /*!< 0x00030000 */
#define DMA2D_BGPFCCR_AM           DMA2D_BGPFCCR_AM_Msk                        /*!< Alpha mode AM[1:0] */
#define DMA2D_BGPFCCR_AM_0         (0x1UL << DMA2D_BGPFCCR_AM_Pos)              /*!< 0x00010000 */
#define DMA2D_BGPFCCR_AM_1         (0x2UL << DMA2D_BGPFCCR_AM_Pos)              /*!< 0x00020000 */
#define DMA2D_BGPFCCR_AI_Pos       (20U)
#define DMA2D_BGPFCCR_AI_Msk       (0x1UL << DMA2D_BGPFCCR_AI_Pos)             /*!< 0x00100000 */
#define DMA2D_BGPFCCR_AI           DMA2D_BGPFCCR_AI_Msk                        /*!< background Input Alpha Inverted */
#define DMA2D_BGPFCCR_RBS_Pos      (21U)
#define DMA2D_BGPFCCR_RBS_Msk      (0x1UL << DMA2D_BGPFCCR_RBS_Pos)            /*!< 0x00200000 */
#define DMA2D_BGPFCCR_RBS          DMA2D_BGPFCCR_RBS_Msk                       /*!< Background Input Red Blue Swap */
#define DMA2D_BGPFCCR_ALPHA_Pos    (24U)
#define DMA2D_BGPFCCR_ALPHA_Msk    (0xFFUL << DMA2D_BGPFCCR_ALPHA_Pos)         /*!< 0xFF000000 */
#define DMA2D_BGPFCCR_ALPHA        DMA2D_BGPFCCR_ALPHA_Msk                     /*!< background Input Alpha value */

/********************  Bit definition for DMA2D_BGCOLR register  **************/
#define DMA2D_BGCOLR_BLUE_Pos      (0U)
#define DMA2D_BGCOLR_BLUE_Msk      (0xFFUL << DMA2D_BGCOLR_BLUE_Pos)           /*!< 0x000000FF */
#define DMA2D_BGCOLR_BLUE          DMA2D_BGCOLR_BLUE_Msk                       /*!< Background Blue Value */
#define DMA2D_BGCOLR_GREEN_Pos     (8U)
#define DMA2D_BGCOLR_GREEN_Msk     (0xFFUL << DMA2D_BGCOLR_GREEN_Pos)          /*!< 0x0000FF00 */
#define DMA2D_BGCOLR_GREEN         DMA2D_BGCOLR_GREEN_Msk                      /*!< Background Green Value */
#define DMA2D_BGCOLR_RED_Pos       (16U)
#define DMA2D_BGCOLR_RED_Msk       (0xFFUL << DMA2D_BGCOLR_RED_Pos)            /*!< 0x00FF0000 */
#define DMA2D_BGCOLR_RED           DMA2D_BGCOLR_RED_Msk                        /*!< Background Red Value */

/********************  Bit definition for DMA2D_FGCMAR register  **************/
#define DMA2D_FGCMAR_MA_Pos        (0U)
#define DMA2D_FGCMAR_MA_Msk        (0xFFFFFFFFUL << DMA2D_FGCMAR_MA_Pos)       /*!< 0xFFFFFFFF */
#define DMA2D_FGCMAR_MA            DMA2D_FGCMAR_MA_Msk                         /*!< Foreground CLUT Memory Address */

/********************  Bit definition for DMA2D_BGCMAR register  **************/
#define DMA2D_BGCMAR_MA_Pos        (0U)
#define DMA2D_BGCMAR_MA_Msk        (0xFFFFFFFFUL << DMA2D_BGCMAR_MA_Pos)       /*!< 0xFFFFFFFF */
#define DMA2D_BGCMAR_MA            DMA2D_BGCMAR_MA_Msk                         /*!< Background CLUT Memory Address */

/********************  Bit definition for DMA2D_OPFCCR register  **************/
#define DMA2D_OPFCCR_CM_Pos        (0U)
#define DMA2D_OPFCCR_CM_Msk        (0x7UL << DMA2D_OPFCCR_CM_Pos)              /*!< 0x00000007 */
#define DMA2D_OPFCCR_CM            DMA2D_OPFCCR_CM_Msk                         /*!< Output Color mode CM[2:0] */
#define DMA2D_OPFCCR_CM_0          (0x1UL << DMA2D_OPFCCR_CM_Pos)               /*!< 0x00000001 */
#define DMA2D_OPFCCR_CM_1          (0x2UL << DMA2D_OPFCCR_CM_Pos)               /*!< 0x00000002 */
#define DMA2D_OPFCCR_CM_2          (0x4UL << DMA2D_OPFCCR_CM_Pos)               /*!< 0x00000004 */
#define DMA2D_OPFCCR_AI_Pos        (20U)
#define DMA2D_OPFCCR_AI_Msk        (0x1UL << DMA2D_OPFCCR_AI_Pos)              /*!< 0x00100000 */
#define DMA2D_OPFCCR_AI            DMA2D_OPFCCR_AI_Msk                         /*!< Output Alpha Inverted */
#define DMA2D_OPFCCR_RBS_Pos       (21U)
#define DMA2D_OPFCCR_RBS_Msk       (0x1UL << DMA2D_OPFCCR_RBS_Pos)             /*!< 0x00200000 */
#define DMA2D_OPFCCR_RBS           DMA2D_OPFCCR_RBS_Msk                        /*!< Output Red Blue Swap */

/********************  Bit definition for DMA2D_OCOLR register  ***************/
/*!<Mode_ARGB8888/RGB888 */
#define DMA2D_OCOLR_BLUE_1         ((uint32_t)0x000000FFU)                     /*!< Output BLUE Value */
#define DMA2D_OCOLR_GREEN_1        ((uint32_t)0x0000FF00U)                     /*!< Output GREEN Value  */
#define DMA2D_OCOLR_RED_1          ((uint32_t)0x00FF0000U)                     /*!< Output Red Value */
#define DMA2D_OCOLR_ALPHA_1        ((uint32_t)0xFF000000U)                     /*!< Output Alpha Channel Value */

/*!<Mode_RGB565 */
#define DMA2D_OCOLR_BLUE_2         ((uint32_t)0x0000001FU)                     /*!< Output BLUE Value */
#define DMA2D_OCOLR_GREEN_2        ((uint32_t)0x000007E0U)                     /*!< Output GREEN Value  */
#define DMA2D_OCOLR_RED_2          ((uint32_t)0x0000F800U)                     /*!< Output Red Value */

/*!<Mode_ARGB1555 */
#define DMA2D_OCOLR_BLUE_3         ((uint32_t)0x0000001FU)                     /*!< Output BLUE Value */
#define DMA2D_OCOLR_GREEN_3        ((uint32_t)0x000003E0U)                     /*!< Output GREEN Value  */
#define DMA2D_OCOLR_RED_3          ((uint32_t)0x00007C00U)                     /*!< Output Red Value */
#define DMA2D_OCOLR_ALPHA_3        ((uint32_t)0x00008000U)                     /*!< Output Alpha Channel Value */

/*!<Mode_ARGB4444 */
#define DMA2D_OCOLR_BLUE_4         ((uint32_t)0x0000000FU)                     /*!< Output BLUE Value */
#define DMA2D_OCOLR_GREEN_4        ((uint32_t)0x000000F0U)                     /*!< Output GREEN Value  */
#define DMA2D_OCOLR_RED_4          ((uint32_t)0x00000F00U)                     /*!< Output Red Value */
#define DMA2D_OCOLR_ALPHA_4        ((uint32_t)0x0000F000U)                     /*!< Output Alpha Channel Value */

/********************  Bit definition for DMA2D_OMAR register  ****************/
#define DMA2D_OMAR_MA_Pos          (0U)
#define DMA2D_OMAR_MA_Msk          (0xFFFFFFFFUL << DMA2D_OMAR_MA_Pos)         /*!< 0xFFFFFFFF */
#define DMA2D_OMAR_MA              DMA2D_OMAR_MA_Msk                           /*!< Output Memory Address */

/********************  Bit definition for DMA2D_OOR register  *****************/
#define DMA2D_OOR_LO_Pos           (0U)
#define DMA2D_OOR_LO_Msk           (0x3FFFUL << DMA2D_OOR_LO_Pos)              /*!< 0x00003FFF */
#define DMA2D_OOR_LO               DMA2D_OOR_LO_Msk                            /*!< Output Line Offset */

/********************  Bit definition for DMA2D_NLR register  *****************/
#define DMA2D_NLR_NL_Pos           (0U)
#define DMA2D_NLR_NL_Msk           (0xFFFFUL << DMA2D_NLR_NL_Pos)              /*!< 0x0000FFFF */
#define DMA2D_NLR_NL               DMA2D_NLR_NL_Msk                            /*!< Number of Lines */
#define DMA2D_NLR_PL_Pos           (16U)
#define DMA2D_NLR_PL_Msk           (0x3FFFUL << DMA2D_NLR_PL_Pos)              /*!< 0x3FFF0000 */
#define DMA2D_NLR_PL               DMA2D_NLR_PL_Msk                            /*!< Pixel per Lines */

/********************  Bit definition for DMA2D_LWR register  *****************/
#define DMA2D_LWR_LW_Pos           (0U)
#define DMA2D_LWR_LW_Msk           (0xFFFFUL << DMA2D_LWR_LW_Pos)              /*!< 0x0000FFFF */
#define DMA2D_LWR_LW               DMA2D_LWR_LW_Msk                            /*!< Line Watermark */

/********************  Bit definition for DMA2D_AMTCR register  ***************/
#define DMA2D_AMTCR_EN_Pos         (0U)
#define DMA2D_AMTCR_EN_Msk         (0x1UL << DMA2D_AMTCR_EN_Pos)               /*!< 0x00000001 */
#define DMA2D_AMTCR_EN             DMA2D_AMTCR_EN_Msk                          /*!< Enable */
#define DMA2D_AMTCR_DT_Pos         (8U)
#define DMA2D_AMTCR_DT_Msk         (0xFFUL << DMA2D_AMTCR_DT_Pos)              /*!< 0x0000FF00 */
#define DMA2D_AMTCR_DT             DMA2D_AMTCR_DT_Msk                          /*!< Dead Time */



/** 
  * @brief DMA2D color Structure definition
  */
typedef struct
{
  uint32_t Blue;               /*!< Configures the blue value.
                                    This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint32_t Green;              /*!< Configures the green value.
                                    This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint32_t Red;                /*!< Configures the red value.
                                    This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */
} DMA2D_ColorTypeDef;

/** 
  * @brief DMA2D CLUT Structure definition
  */
typedef struct
{
  uint32_t *pCLUT;                  /*!< Configures the DMA2D CLUT memory address.*/

  uint32_t CLUTColorMode;           /*!< Configures the DMA2D CLUT color mode.
                                         This parameter can be one value of @ref DMA2D_CLUT_CM. */

  uint32_t Size;                    /*!< Configures the DMA2D CLUT size. 
                                         This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.*/
} DMA2D_CLUTCfgTypeDef;

/** 
  * @brief DMA2D Init structure definition
  */
typedef struct
{
  uint32_t             Mode;               /*!< Configures the DMA2D transfer mode.
                                                This parameter can be one value of @ref DMA2D_Mode. */

  uint32_t             ColorMode;          /*!< Configures the color format of the output image.
                                                This parameter can be one value of @ref DMA2D_Output_Color_Mode. */

  uint32_t             OutputOffset;       /*!< Specifies the Offset value. 
                                                This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0x3FFF. */
  uint32_t             AlphaInverted;     /*!< Select regular or inverted alpha value for the output pixel format converter.
                                               This parameter can be one value of @ref DMA2D_Alpha_Inverted */

  uint32_t             RedBlueSwap;       /*!< Select regular mode (RGB or ARGB) or swap mode (BGR or ABGR)
                                               for the output pixel format converter.
                                               This parameter can be one value of @ref DMA2D_RB_Swap. */
  
} DMA2D_InitTypeDef;


/** 
  * @brief DMA2D Layer structure definition
  */
typedef struct
{
  uint32_t             InputOffset;       /*!< Configures the DMA2D foreground or background offset.
                                               This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0x3FFF. */

  uint32_t             InputColorMode;    /*!< Configures the DMA2D foreground or background color mode. 
                                               This parameter can be one value of @ref DMA2D_Input_Color_Mode. */

  uint32_t             AlphaMode;         /*!< Configures the DMA2D foreground or background alpha mode. 
                                               This parameter can be one value of @ref DMA2D_Alpha_Mode. */

  uint32_t             InputAlpha;        /*!< Specifies the DMA2D foreground or background alpha value and color value in case of A8 or A4 color mode. 
                                               This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF except for the color modes detailed below.
                                               @note In case of A8 or A4 color mode (ARGB), this parameter must be a number between 
                                               Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF where 
                                               - InputAlpha[24:31] is the alpha value ALPHA[0:7]
                                               - InputAlpha[16:23] is the red value RED[0:7]
                                               - InputAlpha[8:15] is the green value GREEN[0:7]
                                               - InputAlpha[0:7] is the blue value BLUE[0:7]. */

  uint32_t             AlphaInverted;     /*!< Select regular or inverted alpha value.
                                               This parameter can be one value of @ref DMA2D_Alpha_Inverted.*/

  uint32_t             RedBlueSwap;       /*!< Select regular mode (RGB or ARGB) or swap mode (BGR or ABGR).
                                               This parameter can be one value of @ref DMA2D_RB_Swap. */  
  
  uint32_t             ChromaSubSampling; /*!< Configure the chroma sub-sampling mode for the YCbCr color mode
                                               This parameter can be one value of @ref DMA2D_Chroma_Sub_Sampling */
} DMA2D_LayerCfgTypeDef;

/** 
  * @brief  HAL DMA2D State structures definition
  */
typedef enum
{
  HAL_DMA2D_STATE_RESET             = 0x00U,    /*!< DMA2D not yet initialized or disabled       */
  HAL_DMA2D_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_DMA2D_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_DMA2D_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_DMA2D_STATE_ERROR             = 0x04U,    /*!< DMA2D state error                           */
  HAL_DMA2D_STATE_SUSPEND           = 0x05U     /*!< DMA2D process is suspended                  */
}HAL_DMA2D_StateTypeDef;

/** 
  * @brief  DMA2D handle Structure definition
  */
typedef struct __DMA2D_HandleTypeDef
{
  DMA2D_TypeDef               *Instance;                                                    /*!< DMA2D register base address.               */
                                                                                                                                          
  DMA2D_InitTypeDef           Init;                                                         /*!< DMA2D communication parameters.            */

  void                        (* XferCpltCallback)(struct __DMA2D_HandleTypeDef * hdma2d);  /*!< DMA2D transfer complete callback.          */
                                                                                                                                           
  void                        (* XferErrorCallback)(struct __DMA2D_HandleTypeDef * hdma2d); /*!< DMA2D transfer error callback.             */                                                                                                                                             

  void                        (* LineEvtCallback)(struct __DMA2D_HandleTypeDef * hdma2d); /*!< DMA2D line event callback.             */

  DMA2D_LayerCfgTypeDef       LayerCfg[MAX_DMA2D_LAYER];                                    /*!< DMA2D Layers parameters           */  

  HAL_LockTypeDef             Lock;                                                         /*!< DMA2D lock.                                */  
                                                                                                                                           
  __IO HAL_DMA2D_StateTypeDef State;                                                        /*!< DMA2D transfer state.                      */
                                                                                                                                           
  __IO uint32_t               ErrorCode;                                                    /*!< DMA2D error code.                          */  
} DMA2D_HandleTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DMA2D_Exported_Constants DMA2D Exported Constants
  * @{
  */

/** @defgroup DMA2D_Error_Code DMA2D Error Code
  * @{
  */
#define HAL_DMA2D_ERROR_NONE        ((uint32_t)0x00000000U)  /*!< No error             */
#define HAL_DMA2D_ERROR_TE          ((uint32_t)0x00000001U)  /*!< Transfer error       */
#define HAL_DMA2D_ERROR_CE          ((uint32_t)0x00000002U)  /*!< Configuration error  */
#define HAL_DMA2D_ERROR_CAE         ((uint32_t)0x00000004U)  /*!< CLUT access error    */
#define HAL_DMA2D_ERROR_TIMEOUT     ((uint32_t)0x00000020U)  /*!< Timeout error        */
/**
  * @}
  */

/** @defgroup DMA2D_Mode DMA2D Mode 
  * @{
  */
#define DMA2D_M2M                   ((uint32_t)0x00000000U)  /*!< DMA2D memory to memory transfer mode */
#define DMA2D_M2M_PFC               DMA2D_CR_MODE_0          /*!< DMA2D memory to memory with pixel format conversion transfer mode */
#define DMA2D_M2M_BLEND             DMA2D_CR_MODE_1          /*!< DMA2D memory to memory with blending transfer mode */
#define DMA2D_R2M                   DMA2D_CR_MODE            /*!< DMA2D register to memory transfer mode */
/**
  * @}
  */

/** @defgroup DMA2D_Output_Color_Mode DMA2D Output Color Mode 
  * @{
  */
#define DMA2D_OUTPUT_ARGB8888       ((uint32_t)0x00000000U)               /*!< ARGB8888 DMA2D color mode */
#define DMA2D_OUTPUT_RGB888         DMA2D_OPFCCR_CM_0                     /*!< RGB888 DMA2D color mode   */
#define DMA2D_OUTPUT_RGB565         DMA2D_OPFCCR_CM_1                     /*!< RGB565 DMA2D color mode   */
#define DMA2D_OUTPUT_ARGB1555       (DMA2D_OPFCCR_CM_0|DMA2D_OPFCCR_CM_1) /*!< ARGB1555 DMA2D color mode */
#define DMA2D_OUTPUT_ARGB4444       DMA2D_OPFCCR_CM_2                     /*!< ARGB4444 DMA2D color mode */
/**
  * @}
  */

/** @defgroup DMA2D_Input_Color_Mode DMA2D Input Color Mode
  * @{
  */
#define DMA2D_INPUT_ARGB8888        ((uint32_t)0x00000000U)  /*!< ARGB8888 color mode */
#define DMA2D_INPUT_RGB888          ((uint32_t)0x00000001U)  /*!< RGB888 color mode   */
#define DMA2D_INPUT_RGB565          ((uint32_t)0x00000002U)  /*!< RGB565 color mode   */
#define DMA2D_INPUT_ARGB1555        ((uint32_t)0x00000003U)  /*!< ARGB1555 color mode */
#define DMA2D_INPUT_ARGB4444        ((uint32_t)0x00000004U)  /*!< ARGB4444 color mode */
#define DMA2D_INPUT_L8              ((uint32_t)0x00000005U)  /*!< L8 color mode       */
#define DMA2D_INPUT_AL44            ((uint32_t)0x00000006U)  /*!< AL44 color mode     */
#define DMA2D_INPUT_AL88            ((uint32_t)0x00000007U)  /*!< AL88 color mode     */
#define DMA2D_INPUT_L4              ((uint32_t)0x00000008U)  /*!< L4 color mode       */
#define DMA2D_INPUT_A8              ((uint32_t)0x00000009U)  /*!< A8 color mode       */
#define DMA2D_INPUT_A4              ((uint32_t)0x0000000AU)  /*!< A4 color mode       */
//#define DMA2D_INPUT_YCBCR           ((uint32_t)0x0000000BU)   /*!< YCbCr color mode */
/**
  * @}
  */

/** @defgroup DMA2D_Alpha_Mode DMA2D Alpha Mode
  * @{
  */
#define DMA2D_NO_MODIF_ALPHA        ((uint32_t)0x00000000U)  /*!< No modification of the alpha channel value */
#define DMA2D_REPLACE_ALPHA         ((uint32_t)0x00000001U)  /*!< Replace original alpha channel value by programmed alpha value */
#define DMA2D_COMBINE_ALPHA         ((uint32_t)0x00000002U)  /*!< Replace original alpha channel value by programmed alpha value
                                                                with original alpha channel value                              */
/**
  * @}
  */    

  
/** @defgroup DMA2D_Alpha_Inverted DMA2D ALPHA Inversion
  * @{
  */
#define DMA2D_REGULAR_ALPHA         ((uint32_t)0x00000000U)  /*!< No modification of the alpha channel value */
#define DMA2D_INVERTED_ALPHA        ((uint32_t)0x00000001U)  /*!< Invert the alpha channel value */                                  
/**
  * @}
  */

 
/** @defgroup DMA2D_RB_Swap DMA2D Red and Blue Swap
  * @{
  */
#define DMA2D_RB_REGULAR            ((uint32_t)0x00000000U)  /*!< Select regular mode (RGB or ARGB) */
#define DMA2D_RB_SWAP               ((uint32_t)0x00000001U)  /*!< Select swap mode (BGR or ABGR) */
/**
  * @}
  */

/** @defgroup DMA2D_Chroma_Sub_Sampling DMA2D Chroma Sub Sampling
  * @{
  */  
#define DMA2D_NO_CSS               ((uint32_t)0x00000000)  /*!< No chroma sub-sampling 4:4:4 */
#define DMA2D_CSS_422              ((uint32_t)0x00000001)  /*!< chroma sub-sampling 4:2:2 */
#define DMA2D_CSS_420              ((uint32_t)0x00000002)  /*!< chroma sub-sampling 4:2:0 */  
/**
  * @}
  */


/** @defgroup DMA2D_CLUT_CM DMA2D CLUT Color Mode
  * @{
  */
#define DMA2D_CCM_ARGB8888          ((uint32_t)0x00000000U)  /*!< ARGB8888 DMA2D CLUT color mode */
#define DMA2D_CCM_RGB888            ((uint32_t)0x00000001U)  /*!< RGB888 DMA2D CLUT color mode   */
/**
  * @}
  */


/** @defgroup DMA2D_Interrupts DMA2D Interrupts 
  * @{
  */
#define DMA2D_IT_CE                 DMA2D_CR_CEIE            /*!< Configuration Error Interrupt */
#define DMA2D_IT_CTC                DMA2D_CR_CTCIE           /*!< CLUT Transfer Complete Interrupt */
#define DMA2D_IT_CAE                DMA2D_CR_CAEIE           /*!< CLUT Access Error Interrupt */
#define DMA2D_IT_TW                 DMA2D_CR_TWIE            /*!< Transfer Watermark Interrupt */
#define DMA2D_IT_TC                 DMA2D_CR_TCIE            /*!< Transfer Complete Interrupt */
#define DMA2D_IT_TE                 DMA2D_CR_TEIE            /*!< Transfer Error Interrupt */
/**                                                         
  * @}                                                      
  */                                                        
                                                            
/** @defgroup DMA2D_Flags DMA2D Flags                       
  * @{                                                      
  */                                                        
#define DMA2D_FLAG_CE               DMA2D_ISR_CEIF           /*!< Configuration Error Interrupt Flag */
#define DMA2D_FLAG_CTC              DMA2D_ISR_CTCIF          /*!< CLUT Transfer Complete Interrupt Flag */
#define DMA2D_FLAG_CAE              DMA2D_ISR_CAEIF          /*!< CLUT Access Error Interrupt Flag */
#define DMA2D_FLAG_TW               DMA2D_ISR_TWIF           /*!< Transfer Watermark Interrupt Flag */
#define DMA2D_FLAG_TC               DMA2D_ISR_TCIF           /*!< Transfer Complete Interrupt Flag */
#define DMA2D_FLAG_TE               DMA2D_ISR_TEIF           /*!< Transfer Error Interrupt Flag */
/**
  * @}
  */
  
/** @defgroup DMA2D_Aliases DMA2D API Aliases
  * @{
  */
#define HAL_DMA2D_DisableCLUT       HAL_DMA2D_CLUTLoading_Abort    /*!< Aliased to HAL_DMA2D_CLUTLoading_Abort for compatibility with legacy code */
/**
  * @}
  */
  
  
/**
  * @}
  */
/* Exported macros ------------------------------------------------------------*/
/** @defgroup DMA2D_Exported_Macros DMA2D Exported Macros
  * @{
  */

/** @brief Reset DMA2D handle state
  * @param  __HANDLE__: specifies the DMA2D handle.
  * @retval None
  */
#define __HAL_DMA2D_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DMA2D_STATE_RESET)

/**
  * @brief  Enable the DMA2D.
  * @param  __HANDLE__: DMA2D handle
  * @retval None.
  */
#define __HAL_DMA2D_ENABLE(__HANDLE__)        ((__HANDLE__)->Instance->CR |= DMA2D_CR_START)


/* Interrupt & Flag management */
/**
  * @brief  Get the DMA2D pending flags.
  * @param  __HANDLE__: DMA2D handle
  * @param  __FLAG__: flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg DMA2D_FLAG_CE:  Configuration error flag
  *            @arg DMA2D_FLAG_CTC: CLUT transfer complete flag
  *            @arg DMA2D_FLAG_CAE: CLUT access error flag
  *            @arg DMA2D_FLAG_TW:  Transfer Watermark flag
  *            @arg DMA2D_FLAG_TC:  Transfer complete flag
  *            @arg DMA2D_FLAG_TE:  Transfer error flag   
  * @retval The state of FLAG.
  */
#define __HAL_DMA2D_GET_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ISR & (__FLAG__))

/**
  * @brief  Clear the DMA2D pending flags.
  * @param  __HANDLE__: DMA2D handle
  * @param  __FLAG__: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA2D_FLAG_CE:  Configuration error flag
  *            @arg DMA2D_FLAG_CTC: CLUT transfer complete flag
  *            @arg DMA2D_FLAG_CAE: CLUT access error flag
  *            @arg DMA2D_FLAG_TW:  Transfer Watermark flag
  *            @arg DMA2D_FLAG_TC:  Transfer complete flag
  *            @arg DMA2D_FLAG_TE:  Transfer error flag    
  * @retval None
  */
#define __HAL_DMA2D_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->IFCR = (__FLAG__))

/**
  * @brief  Enable the specified DMA2D interrupts.
  * @param  __HANDLE__: DMA2D handle
  * @param __INTERRUPT__: specifies the DMA2D interrupt sources to be enabled. 
  *          This parameter can be any combination of the following values:
  *            @arg DMA2D_IT_CE:  Configuration error interrupt mask
  *            @arg DMA2D_IT_CTC: CLUT transfer complete interrupt mask
  *            @arg DMA2D_IT_CAE: CLUT access error interrupt mask
  *            @arg DMA2D_IT_TW:  Transfer Watermark interrupt mask
  *            @arg DMA2D_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA2D_IT_TE:  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA2D_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->CR |= (__INTERRUPT__))

/**
  * @brief  Disable the specified DMA2D interrupts.
  * @param  __HANDLE__: DMA2D handle
  * @param __INTERRUPT__: specifies the DMA2D interrupt sources to be disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg DMA2D_IT_CE:  Configuration error interrupt mask
  *            @arg DMA2D_IT_CTC: CLUT transfer complete interrupt mask
  *            @arg DMA2D_IT_CAE: CLUT access error interrupt mask
  *            @arg DMA2D_IT_TW:  Transfer Watermark interrupt mask
  *            @arg DMA2D_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA2D_IT_TE:  Transfer error interrupt mask
  * @retval None
  */
#define __HAL_DMA2D_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->CR &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified DMA2D interrupt source is enabled or not.
  * @param  __HANDLE__: DMA2D handle
  * @param  __INTERRUPT__: specifies the DMA2D interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg DMA2D_IT_CE:  Configuration error interrupt mask
  *            @arg DMA2D_IT_CTC: CLUT transfer complete interrupt mask
  *            @arg DMA2D_IT_CAE: CLUT access error interrupt mask
  *            @arg DMA2D_IT_TW:  Transfer Watermark interrupt mask
  *            @arg DMA2D_IT_TC:  Transfer complete interrupt mask
  *            @arg DMA2D_IT_TE:  Transfer error interrupt mask
  * @retval The state of INTERRUPT source.
  */
#define __HAL_DMA2D_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->CR & (__INTERRUPT__))
     
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/  
/** @addtogroup DMA2D_Exported_Functions DMA2D Exported Functions
  * @{
  */

/** @addtogroup DMA2D_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */  
  
/* Initialization and de-initialization functions *******************************/
HAL_StatusTypeDef HAL_DMA2D_Init(DMA2D_HandleTypeDef *hdma2d); 
HAL_StatusTypeDef HAL_DMA2D_DeInit (DMA2D_HandleTypeDef *hdma2d);
void              HAL_DMA2D_MspInit(DMA2D_HandleTypeDef* hdma2d);
void              HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef* hdma2d);

/**
  * @}
  */


/** @addtogroup DMA2D_Exported_Functions_Group2 IO operation functions
  * @{
  */
  
/* IO operation functions *******************************************************/
HAL_StatusTypeDef HAL_DMA2D_Start(DMA2D_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress, uint32_t Width, uint32_t Height);
HAL_StatusTypeDef HAL_DMA2D_BlendingStart(DMA2D_HandleTypeDef *hdma2d, uint32_t SrcAddress1, uint32_t SrcAddress2, uint32_t DstAddress, uint32_t Width,  uint32_t Height);
HAL_StatusTypeDef HAL_DMA2D_Start_IT(DMA2D_HandleTypeDef *hdma2d, uint32_t pdata, uint32_t DstAddress, uint32_t Width, uint32_t Height);
HAL_StatusTypeDef HAL_DMA2D_BlendingStart_IT(DMA2D_HandleTypeDef *hdma2d, uint32_t SrcAddress1, uint32_t SrcAddress2, uint32_t DstAddress, uint32_t Width, uint32_t Height);
HAL_StatusTypeDef HAL_DMA2D_Suspend(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_Resume(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_Abort(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_EnableCLUT(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTLoad(DMA2D_HandleTypeDef *hdma2d, DMA2D_CLUTCfgTypeDef CLUTCfg, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTLoad_IT(DMA2D_HandleTypeDef *hdma2d, DMA2D_CLUTCfgTypeDef CLUTCfg, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTLoading_Abort(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTLoading_Suspend(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_CLUTLoading_Resume(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_PollForTransfer(DMA2D_HandleTypeDef *hdma2d, uint32_t Timeout);
void              HAL_DMA2D_IRQHandler(DMA2D_HandleTypeDef *hdma2d);
void              HAL_DMA2D_LineEventCallback(DMA2D_HandleTypeDef *hdma2d);
void              HAL_DMA2D_CLUTLoadingCpltCallback(DMA2D_HandleTypeDef *hdma2d);

/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */

/* Peripheral Control functions *************************************************/
HAL_StatusTypeDef HAL_DMA2D_ConfigLayer(DMA2D_HandleTypeDef *hdma2d, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_ConfigCLUT(DMA2D_HandleTypeDef *hdma2d, DMA2D_CLUTCfgTypeDef CLUTCfg, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_DMA2D_ProgramLineEvent(DMA2D_HandleTypeDef *hdma2d, uint32_t Line);
HAL_StatusTypeDef HAL_DMA2D_EnableDeadTime(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_DisableDeadTime(DMA2D_HandleTypeDef *hdma2d);
HAL_StatusTypeDef HAL_DMA2D_ConfigDeadTime(DMA2D_HandleTypeDef *hdma2d, uint8_t DeadTime);

/**
  * @}
  */

/** @addtogroup DMA2D_Exported_Functions_Group4 Peripheral State and Error functions
  * @{
  */

/* Peripheral State functions ***************************************************/
HAL_DMA2D_StateTypeDef HAL_DMA2D_GetState(DMA2D_HandleTypeDef *hdma2d);
uint32_t               HAL_DMA2D_GetError(DMA2D_HandleTypeDef *hdma2d);

/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/  
  
/** @addtogroup DMA2D_Private_Constants DMA2D Private Constants
  * @{
  */                         

/** @defgroup DMA2D_Maximum_Line_WaterMark DMA2D Maximum Line Watermark 
  * @{
  */
#define DMA2D_LINE_WATERMARK_MAX            DMA2D_LWR_LW       /*!< DMA2D maximum line watermark */
/**
  * @}
  */
  
/** @defgroup DMA2D_Color_Value DMA2D Color Value
  * @{
  */
#define DMA2D_COLOR_VALUE                 ((uint32_t)0x000000FFU)  /*!< Color value mask */
/**
  * @}
  */      

/** @defgroup DMA2D_Offset DMA2D Offset 
  * @{
  */
#define DMA2D_OFFSET                DMA2D_FGOR_LO            /*!< maximum Line Offset */
/**
  * @}
  */ 
  
/** @defgroup DMA2D_Size DMA2D Size 
  * @{
  */
#define DMA2D_PIXEL                 (DMA2D_NLR_PL >> 16U)    /*!< DMA2D maximum number of pixels per line */
#define DMA2D_LINE                  DMA2D_NLR_NL             /*!< DMA2D maximum number of lines           */
/**
  * @}
  */    
  
/** @defgroup DMA2D_CLUT_Size DMA2D CLUT Size
  * @{
  */
#define DMA2D_CLUT_SIZE             (DMA2D_FGPFCCR_CS >> 8)  /*!< DMA2D maximum CLUT size */
/**
  * @}
  */   
    
/**
  * @}
  */ 


/* Private macros ------------------------------------------------------------*/
/** @defgroup DMA2D_Private_Macros DMA2D Private Macros
  * @{
  */
#define IS_DMA2D_ALL_INSTANCE(__INSTANCE__)   ((__INSTANCE__) == DMA2D)
#define IS_DMA2D_LAYER(LAYER)                 ((LAYER) <= MAX_DMA2D_LAYER)
#define IS_DMA2D_MODE(MODE)                   (((MODE) == DMA2D_M2M)       || ((MODE) == DMA2D_M2M_PFC) || \
                                               ((MODE) == DMA2D_M2M_BLEND) || ((MODE) == DMA2D_R2M))
#define IS_DMA2D_CMODE(MODE_ARGB)             (((MODE_ARGB) == DMA2D_OUTPUT_ARGB8888) || ((MODE_ARGB) == DMA2D_OUTPUT_RGB888)   || \
                                               ((MODE_ARGB) == DMA2D_OUTPUT_RGB565)   || ((MODE_ARGB) == DMA2D_OUTPUT_ARGB1555) || \
                                               ((MODE_ARGB) == DMA2D_OUTPUT_ARGB4444))
#define IS_DMA2D_COLOR(COLOR)                 ((COLOR) <= DMA2D_COLOR_VALUE)
#define IS_DMA2D_LINE(LINE)                   ((LINE) <= DMA2D_LINE)
#define IS_DMA2D_PIXEL(PIXEL)                 ((PIXEL) <= DMA2D_PIXEL)
#define IS_DMA2D_OFFSET(OOFFSET)              ((OOFFSET) <= DMA2D_OFFSET)
#define IS_DMA2D_INPUT_COLOR_MODE(INPUT_CM)   (((INPUT_CM) == DMA2D_INPUT_ARGB8888) || ((INPUT_CM) == DMA2D_INPUT_RGB888)   || \
                                               ((INPUT_CM) == DMA2D_INPUT_RGB565)   || ((INPUT_CM) == DMA2D_INPUT_ARGB1555) || \
                                               ((INPUT_CM) == DMA2D_INPUT_ARGB4444) || ((INPUT_CM) == DMA2D_INPUT_L8)       || \
                                               ((INPUT_CM) == DMA2D_INPUT_AL44)     || ((INPUT_CM) == DMA2D_INPUT_AL88)     || \
                                               ((INPUT_CM) == DMA2D_INPUT_L4)       || ((INPUT_CM) == DMA2D_INPUT_A8)       || \
                                               ((INPUT_CM) == DMA2D_INPUT_A4))
#define IS_DMA2D_ALPHA_MODE(AlphaMode)        (((AlphaMode) == DMA2D_NO_MODIF_ALPHA) || \
                                               ((AlphaMode) == DMA2D_REPLACE_ALPHA)  || \
                                               ((AlphaMode) == DMA2D_COMBINE_ALPHA))

#define IS_DMA2D_ALPHA_INVERTED(Alpha_Inverted) (((Alpha_Inverted) == DMA2D_REGULAR_ALPHA) || \
                                                 ((Alpha_Inverted) == DMA2D_INVERTED_ALPHA))

#define IS_DMA2D_RB_SWAP(RB_Swap) (((RB_Swap) == DMA2D_RB_REGULAR) || \
                                   ((RB_Swap) == DMA2D_RB_SWAP))

#define IS_DMA2D_CHROMA_SUB_SAMPLING (CSS) (((CSS) == DMA2D_NO_CSS) || \
                                            ((CSS) == DMA2D_CSS_422) || \
                                            ((CSS) == DMA2D_CSS_420))

#define IS_DMA2D_CLUT_CM(CLUT_CM)             (((CLUT_CM) == DMA2D_CCM_ARGB8888) || ((CLUT_CM) == DMA2D_CCM_RGB888))
#define IS_DMA2D_CLUT_SIZE(CLUT_SIZE)         ((CLUT_SIZE) <= DMA2D_CLUT_SIZE)
#define IS_DMA2D_LINEWATERMARK(LineWatermark) ((LineWatermark) <= DMA2D_LINE_WATERMARK_MAX)
#define IS_DMA2D_IT(IT)                       (((IT) == DMA2D_IT_CTC) || ((IT) == DMA2D_IT_CAE) || \
                                               ((IT) == DMA2D_IT_TW) || ((IT) == DMA2D_IT_TC) || \
                                               ((IT) == DMA2D_IT_TE) || ((IT) == DMA2D_IT_CE))
#define IS_DMA2D_GET_FLAG(FLAG)               (((FLAG) == DMA2D_FLAG_CTC) || ((FLAG) == DMA2D_FLAG_CAE) || \
                                               ((FLAG) == DMA2D_FLAG_TW)   || ((FLAG) == DMA2D_FLAG_TC)  || \
                                               ((FLAG) == DMA2D_FLAG_TE)   || ((FLAG) == DMA2D_FLAG_CE))
/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif	//#ifdef __HAL_DMA2D_H__
