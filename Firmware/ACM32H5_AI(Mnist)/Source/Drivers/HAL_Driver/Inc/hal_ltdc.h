/******************************************************************************
*@file  : hal_ltdc.h
*@brief : GPIO HAL module driver.
******************************************************************************/

#ifndef __HAL_LTDC_H__
#define __HAL_LTDC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "hal.h" 



/** @addtogroup LTDC LTDC
  * @brief LTDC HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup LTDC_Exported_Types LTDC Exported Types
  * @{
  */
#define MAX_LAYER  2U


/********************  Bit definition for LTDC_SSCR register  *****************/
#define LTDC_SSCR_VSH_Pos            (0U)
#define LTDC_SSCR_VSH_Msk            (0x7FFUL << LTDC_SSCR_VSH_Pos)            /*!< 0x000007FF */
#define LTDC_SSCR_VSH                LTDC_SSCR_VSH_Msk                         /*!< Vertical Synchronization Height  */
#define LTDC_SSCR_HSW_Pos            (16U)
#define LTDC_SSCR_HSW_Msk            (0xFFFUL << LTDC_SSCR_HSW_Pos)            /*!< 0x0FFF0000 */
#define LTDC_SSCR_HSW                LTDC_SSCR_HSW_Msk                         /*!< Horizontal Synchronization Width */

/********************  Bit definition for LTDC_BPCR register  *****************/
#define LTDC_BPCR_AVBP_Pos           (0U)
#define LTDC_BPCR_AVBP_Msk           (0x7FFUL << LTDC_BPCR_AVBP_Pos)           /*!< 0x000007FF */
#define LTDC_BPCR_AVBP               LTDC_BPCR_AVBP_Msk                        /*!< Accumulated Vertical Back Porch   */
#define LTDC_BPCR_AHBP_Pos           (16U)
#define LTDC_BPCR_AHBP_Msk           (0xFFFUL << LTDC_BPCR_AHBP_Pos)           /*!< 0x0FFF0000 */
#define LTDC_BPCR_AHBP               LTDC_BPCR_AHBP_Msk                        /*!< Accumulated Horizontal Back Porch */

/********************  Bit definition for LTDC_AWCR register  *****************/
#define LTDC_AWCR_AAH_Pos            (0U)
#define LTDC_AWCR_AAH_Msk            (0x7FFUL << LTDC_AWCR_AAH_Pos)            /*!< 0x000007FF */
#define LTDC_AWCR_AAH                LTDC_AWCR_AAH_Msk                         /*!< Accumulated Active heigh */
#define LTDC_AWCR_AAW_Pos            (16U)
#define LTDC_AWCR_AAW_Msk            (0xFFFUL << LTDC_AWCR_AAW_Pos)            /*!< 0x0FFF0000 */
#define LTDC_AWCR_AAW                LTDC_AWCR_AAW_Msk                         /*!< Accumulated Active Width */

/********************  Bit definition for LTDC_TWCR register  *****************/
#define LTDC_TWCR_TOTALH_Pos         (0U)
#define LTDC_TWCR_TOTALH_Msk         (0x7FFUL << LTDC_TWCR_TOTALH_Pos)         /*!< 0x000007FF */
#define LTDC_TWCR_TOTALH             LTDC_TWCR_TOTALH_Msk                      /*!< Total Heigh */
#define LTDC_TWCR_TOTALW_Pos         (16U)
#define LTDC_TWCR_TOTALW_Msk         (0xFFFUL << LTDC_TWCR_TOTALW_Pos)         /*!< 0x0FFF0000 */
#define LTDC_TWCR_TOTALW             LTDC_TWCR_TOTALW_Msk                      /*!< Total Width */

/********************  Bit definition for LTDC_GCR register  ******************/
#define LTDC_GCR_LTDCEN_Pos          (0U)
#define LTDC_GCR_LTDCEN_Msk          (0x1UL << LTDC_GCR_LTDCEN_Pos)            /*!< 0x00000001 */
#define LTDC_GCR_LTDCEN              LTDC_GCR_LTDCEN_Msk                       /*!< LCD-TFT controller enable bit       */
#define LTDC_GCR_DBW_Pos             (4U)
#define LTDC_GCR_DBW_Msk             (0x7UL << LTDC_GCR_DBW_Pos)               /*!< 0x00000070 */
#define LTDC_GCR_DBW                 LTDC_GCR_DBW_Msk                          /*!< Dither Blue Width                   */
#define LTDC_GCR_DGW_Pos             (8U)
#define LTDC_GCR_DGW_Msk             (0x7UL << LTDC_GCR_DGW_Pos)               /*!< 0x00000700 */
#define LTDC_GCR_DGW                 LTDC_GCR_DGW_Msk                          /*!< Dither Green Width                  */
#define LTDC_GCR_DRW_Pos             (12U)
#define LTDC_GCR_DRW_Msk             (0x7UL << LTDC_GCR_DRW_Pos)               /*!< 0x00007000 */
#define LTDC_GCR_DRW                 LTDC_GCR_DRW_Msk                          /*!< Dither Red Width                    */
#define LTDC_GCR_DEN_Pos             (16U)
#define LTDC_GCR_DEN_Msk             (0x1UL << LTDC_GCR_DEN_Pos)               /*!< 0x00010000 */
#define LTDC_GCR_DEN                 LTDC_GCR_DEN_Msk                          /*!< Dither Enable                       */
#define LTDC_GCR_AHB_LOCK_Pos        (17U)
#define LTDC_GCR_AHB_LOCK_Msk        (0x1UL << LTDC_GCR_AHB_LOCK_Pos)          /*!< 0x00020000 */
#define LTDC_GCR_AHB_LOCK            LTDC_GCR_AHB_LOCK_Msk                     /*!< AHB lock Enable                       */
#define LTDC_GCR_PCPOL_Pos           (28U)
#define LTDC_GCR_PCPOL_Msk           (0x1UL << LTDC_GCR_PCPOL_Pos)             /*!< 0x10000000 */
#define LTDC_GCR_PCPOL               LTDC_GCR_PCPOL_Msk                        /*!< Pixel Clock Polarity                */
#define LTDC_GCR_DEPOL_Pos           (29U)
#define LTDC_GCR_DEPOL_Msk           (0x1UL << LTDC_GCR_DEPOL_Pos)             /*!< 0x20000000 */
#define LTDC_GCR_DEPOL               LTDC_GCR_DEPOL_Msk                        /*!< Data Enable Polarity                */
#define LTDC_GCR_VSPOL_Pos           (30U)
#define LTDC_GCR_VSPOL_Msk           (0x1UL << LTDC_GCR_VSPOL_Pos)             /*!< 0x40000000 */
#define LTDC_GCR_VSPOL               LTDC_GCR_VSPOL_Msk                        /*!< Vertical Synchronization Polarity   */
#define LTDC_GCR_HSPOL_Pos           (31U)
#define LTDC_GCR_HSPOL_Msk           (0x1UL << LTDC_GCR_HSPOL_Pos)             /*!< 0x80000000 */
#define LTDC_GCR_HSPOL               LTDC_GCR_HSPOL_Msk                        /*!< Horizontal Synchronization Polarity */

/********************  Bit definition for LTDC_SRCR register  *****************/
#define LTDC_SRCR_IMR_Pos            (0U)
#define LTDC_SRCR_IMR_Msk            (0x1UL << LTDC_SRCR_IMR_Pos)              /*!< 0x00000001 */
#define LTDC_SRCR_IMR                LTDC_SRCR_IMR_Msk                         /*!< Immediate Reload         */
#define LTDC_SRCR_VBR_Pos            (1U)
#define LTDC_SRCR_VBR_Msk            (0x1UL << LTDC_SRCR_VBR_Pos)              /*!< 0x00000002 */
#define LTDC_SRCR_VBR                LTDC_SRCR_VBR_Msk                         /*!< Vertical Blanking Reload */

/********************  Bit definition for LTDC_BCCR register  *****************/
#define LTDC_BCCR_BCBLUE_Pos         (0U)
#define LTDC_BCCR_BCBLUE_Msk         (0xFFUL << LTDC_BCCR_BCBLUE_Pos)          /*!< 0x000000FF */
#define LTDC_BCCR_BCBLUE             LTDC_BCCR_BCBLUE_Msk                      /*!< Background Blue value  */
#define LTDC_BCCR_BCGREEN_Pos        (8U)
#define LTDC_BCCR_BCGREEN_Msk        (0xFFUL << LTDC_BCCR_BCGREEN_Pos)         /*!< 0x0000FF00 */
#define LTDC_BCCR_BCGREEN            LTDC_BCCR_BCGREEN_Msk                     /*!< Background Green value */
#define LTDC_BCCR_BCRED_Pos          (16U)
#define LTDC_BCCR_BCRED_Msk          (0xFFUL << LTDC_BCCR_BCRED_Pos)           /*!< 0x00FF0000 */
#define LTDC_BCCR_BCRED              LTDC_BCCR_BCRED_Msk                       /*!< Background Red value   */

/********************  Bit definition for LTDC_IER register  ******************/
#define LTDC_IER_LIE_Pos             (0U)
#define LTDC_IER_LIE_Msk             (0x1UL << LTDC_IER_LIE_Pos)               /*!< 0x00000001 */
#define LTDC_IER_LIE                 LTDC_IER_LIE_Msk                          /*!< Line Interrupt Enable            */
#define LTDC_IER_FUIE_Pos            (1U)
#define LTDC_IER_FUIE_Msk            (0x1UL << LTDC_IER_FUIE_Pos)              /*!< 0x00000002 */
#define LTDC_IER_FUIE                LTDC_IER_FUIE_Msk                         /*!< FIFO Underrun Interrupt Enable   */
#define LTDC_IER_TERRIE_Pos          (2U)
#define LTDC_IER_TERRIE_Msk          (0x1UL << LTDC_IER_TERRIE_Pos)            /*!< 0x00000004 */
#define LTDC_IER_TERRIE              LTDC_IER_TERRIE_Msk                       /*!< Transfer Error Interrupt Enable  */
#define LTDC_IER_RRIE_Pos            (3U)
#define LTDC_IER_RRIE_Msk            (0x1UL << LTDC_IER_RRIE_Pos)              /*!< 0x00000008 */
#define LTDC_IER_RRIE                LTDC_IER_RRIE_Msk                         /*!< Register Reload interrupt enable */

/********************  Bit definition for LTDC_ISR register  ******************/
#define LTDC_ISR_LIF_Pos             (0U)
#define LTDC_ISR_LIF_Msk             (0x1UL << LTDC_ISR_LIF_Pos)               /*!< 0x00000001 */
#define LTDC_ISR_LIF                 LTDC_ISR_LIF_Msk                          /*!< Line Interrupt Flag */
#define LTDC_ISR_FUIF_Pos            (1U)
#define LTDC_ISR_FUIF_Msk            (0x1UL << LTDC_ISR_FUIF_Pos)              /*!< 0x00000002 */
#define LTDC_ISR_FUIF                LTDC_ISR_FUIF_Msk                         /*!< FIFO Underrun Interrupt Flag */
#define LTDC_ISR_TERRIF_Pos          (2U)
#define LTDC_ISR_TERRIF_Msk          (0x1UL << LTDC_ISR_TERRIF_Pos)            /*!< 0x00000004 */
#define LTDC_ISR_TERRIF              LTDC_ISR_TERRIF_Msk                       /*!< Transfer Error Interrupt Flag */
#define LTDC_ISR_RRIF_Pos            (3U)
#define LTDC_ISR_RRIF_Msk            (0x1UL << LTDC_ISR_RRIF_Pos)              /*!< 0x00000008 */
#define LTDC_ISR_RRIF                LTDC_ISR_RRIF_Msk                         /*!< Register Reload interrupt Flag */

/********************  Bit definition for LTDC_ICR register  ******************/
#define LTDC_ICR_CLIF_Pos            (0U)
#define LTDC_ICR_CLIF_Msk            (0x1UL << LTDC_ICR_CLIF_Pos)              /*!< 0x00000001 */
#define LTDC_ICR_CLIF                LTDC_ICR_CLIF_Msk                         /*!< Clears the Line Interrupt Flag */
#define LTDC_ICR_CFUIF_Pos           (1U)
#define LTDC_ICR_CFUIF_Msk           (0x1UL << LTDC_ICR_CFUIF_Pos)             /*!< 0x00000002 */
#define LTDC_ICR_CFUIF               LTDC_ICR_CFUIF_Msk                        /*!< Clears the FIFO Underrun Interrupt Flag */
#define LTDC_ICR_CTERRIF_Pos         (2U)
#define LTDC_ICR_CTERRIF_Msk         (0x1UL << LTDC_ICR_CTERRIF_Pos)           /*!< 0x00000004 */
#define LTDC_ICR_CTERRIF             LTDC_ICR_CTERRIF_Msk                      /*!< Clears the Transfer Error Interrupt Flag */
#define LTDC_ICR_CRRIF_Pos           (3U)
#define LTDC_ICR_CRRIF_Msk           (0x1UL << LTDC_ICR_CRRIF_Pos)             /*!< 0x00000008 */
#define LTDC_ICR_CRRIF               LTDC_ICR_CRRIF_Msk                        /*!< Clears Register Reload interrupt Flag */

/********************  Bit definition for LTDC_LIPCR register  ****************/
#define LTDC_LIPCR_LIPOS_Pos         (0U)
#define LTDC_LIPCR_LIPOS_Msk         (0x7FFUL << LTDC_LIPCR_LIPOS_Pos)         /*!< 0x000007FF */
#define LTDC_LIPCR_LIPOS             LTDC_LIPCR_LIPOS_Msk                      /*!< Line Interrupt Position */

/********************  Bit definition for LTDC_CPSR register  *****************/
#define LTDC_CPSR_CYPOS_Pos          (0U)
#define LTDC_CPSR_CYPOS_Msk          (0xFFFFUL << LTDC_CPSR_CYPOS_Pos)         /*!< 0x0000FFFF */
#define LTDC_CPSR_CYPOS              LTDC_CPSR_CYPOS_Msk                       /*!< Current Y Position */
#define LTDC_CPSR_CXPOS_Pos          (16U)
#define LTDC_CPSR_CXPOS_Msk          (0xFFFFUL << LTDC_CPSR_CXPOS_Pos)         /*!< 0xFFFF0000 */
#define LTDC_CPSR_CXPOS              LTDC_CPSR_CXPOS_Msk                       /*!< Current X Position */

/********************  Bit definition for LTDC_CDSR register  *****************/
#define LTDC_CDSR_VDES_Pos           (0U)
#define LTDC_CDSR_VDES_Msk           (0x1UL << LTDC_CDSR_VDES_Pos)             /*!< 0x00000001 */
#define LTDC_CDSR_VDES               LTDC_CDSR_VDES_Msk                        /*!< Vertical Data Enable Status       */
#define LTDC_CDSR_HDES_Pos           (1U)
#define LTDC_CDSR_HDES_Msk           (0x1UL << LTDC_CDSR_HDES_Pos)             /*!< 0x00000002 */
#define LTDC_CDSR_HDES               LTDC_CDSR_HDES_Msk                        /*!< Horizontal Data Enable Status     */
#define LTDC_CDSR_VSYNCS_Pos         (2U)
#define LTDC_CDSR_VSYNCS_Msk         (0x1UL << LTDC_CDSR_VSYNCS_Pos)           /*!< 0x00000004 */
#define LTDC_CDSR_VSYNCS             LTDC_CDSR_VSYNCS_Msk                      /*!< Vertical Synchronization Status   */
#define LTDC_CDSR_HSYNCS_Pos         (3U)
#define LTDC_CDSR_HSYNCS_Msk         (0x1UL << LTDC_CDSR_HSYNCS_Pos)           /*!< 0x00000008 */
#define LTDC_CDSR_HSYNCS             LTDC_CDSR_HSYNCS_Msk                      /*!< Horizontal Synchronization Status */

/********************  Bit definition for LTDC_LxCR register  *****************/
#define LTDC_LxCR_LEN_Pos            (0U)
#define LTDC_LxCR_LEN_Msk            (0x1UL << LTDC_LxCR_LEN_Pos)              /*!< 0x00000001 */
#define LTDC_LxCR_LEN                LTDC_LxCR_LEN_Msk                         /*!< Layer Enable              */
#define LTDC_LxCR_COLKEN_Pos         (1U)
#define LTDC_LxCR_COLKEN_Msk         (0x1UL << LTDC_LxCR_COLKEN_Pos)           /*!< 0x00000002 */
#define LTDC_LxCR_COLKEN             LTDC_LxCR_COLKEN_Msk                      /*!< Color Keying Enable       */
#define LTDC_LxCR_CLUTEN_Pos         (4U)
#define LTDC_LxCR_CLUTEN_Msk         (0x1UL << LTDC_LxCR_CLUTEN_Pos)           /*!< 0x00000010 */
#define LTDC_LxCR_CLUTEN             LTDC_LxCR_CLUTEN_Msk                      /*!< Color Lockup Table Enable */

/********************  Bit definition for LTDC_LxWHPCR register  **************/
#define LTDC_LxWHPCR_WHSTPOS_Pos     (0U)
#define LTDC_LxWHPCR_WHSTPOS_Msk     (0xFFFUL << LTDC_LxWHPCR_WHSTPOS_Pos)     /*!< 0x00000FFF */
#define LTDC_LxWHPCR_WHSTPOS         LTDC_LxWHPCR_WHSTPOS_Msk                  /*!< Window Horizontal Start Position */
#define LTDC_LxWHPCR_WHSPPOS_Pos     (16U)
#define LTDC_LxWHPCR_WHSPPOS_Msk     (0xFFFFUL << LTDC_LxWHPCR_WHSPPOS_Pos)    /*!< 0xFFFF0000 */
#define LTDC_LxWHPCR_WHSPPOS         LTDC_LxWHPCR_WHSPPOS_Msk                  /*!< Window Horizontal Stop Position  */

/********************  Bit definition for LTDC_LxWVPCR register  **************/
#define LTDC_LxWVPCR_WVSTPOS_Pos     (0U)
#define LTDC_LxWVPCR_WVSTPOS_Msk     (0xFFFUL << LTDC_LxWVPCR_WVSTPOS_Pos)     /*!< 0x00000FFF */
#define LTDC_LxWVPCR_WVSTPOS         LTDC_LxWVPCR_WVSTPOS_Msk                  /*!< Window Vertical Start Position */
#define LTDC_LxWVPCR_WVSPPOS_Pos     (16U)
#define LTDC_LxWVPCR_WVSPPOS_Msk     (0xFFFFUL << LTDC_LxWVPCR_WVSPPOS_Pos)    /*!< 0xFFFF0000 */
#define LTDC_LxWVPCR_WVSPPOS         LTDC_LxWVPCR_WVSPPOS_Msk                  /*!< Window Vertical Stop Position  */

/********************  Bit definition for LTDC_LxCKCR register  ***************/
#define LTDC_LxCKCR_CKBLUE_Pos       (0U)
#define LTDC_LxCKCR_CKBLUE_Msk       (0xFFUL << LTDC_LxCKCR_CKBLUE_Pos)        /*!< 0x000000FF */
#define LTDC_LxCKCR_CKBLUE           LTDC_LxCKCR_CKBLUE_Msk                    /*!< Color Key Blue value  */
#define LTDC_LxCKCR_CKGREEN_Pos      (8U)
#define LTDC_LxCKCR_CKGREEN_Msk      (0xFFUL << LTDC_LxCKCR_CKGREEN_Pos)       /*!< 0x0000FF00 */
#define LTDC_LxCKCR_CKGREEN          LTDC_LxCKCR_CKGREEN_Msk                   /*!< Color Key Green value */
#define LTDC_LxCKCR_CKRED_Pos        (16U)
#define LTDC_LxCKCR_CKRED_Msk        (0xFFUL << LTDC_LxCKCR_CKRED_Pos)         /*!< 0x00FF0000 */
#define LTDC_LxCKCR_CKRED            LTDC_LxCKCR_CKRED_Msk                     /*!< Color Key Red value   */

/********************  Bit definition for LTDC_LxPFCR register  ***************/
#define LTDC_LxPFCR_PF_Pos           (0U)
#define LTDC_LxPFCR_PF_Msk           (0x7UL << LTDC_LxPFCR_PF_Pos)             /*!< 0x00000007 */
#define LTDC_LxPFCR_PF               LTDC_LxPFCR_PF_Msk                        /*!< Pixel Format */

/********************  Bit definition for LTDC_LxCACR register  ***************/
#define LTDC_LxCACR_CONSTA_Pos       (0U)
#define LTDC_LxCACR_CONSTA_Msk       (0xFFUL << LTDC_LxCACR_CONSTA_Pos)        /*!< 0x000000FF */
#define LTDC_LxCACR_CONSTA           LTDC_LxCACR_CONSTA_Msk                    /*!< Constant Alpha */

/********************  Bit definition for LTDC_LxDCCR register  ***************/
#define LTDC_LxDCCR_DCBLUE_Pos       (0U)
#define LTDC_LxDCCR_DCBLUE_Msk       (0xFFUL << LTDC_LxDCCR_DCBLUE_Pos)        /*!< 0x000000FF */
#define LTDC_LxDCCR_DCBLUE           LTDC_LxDCCR_DCBLUE_Msk                    /*!< Default Color Blue  */
#define LTDC_LxDCCR_DCGREEN_Pos      (8U)
#define LTDC_LxDCCR_DCGREEN_Msk      (0xFFUL << LTDC_LxDCCR_DCGREEN_Pos)       /*!< 0x0000FF00 */
#define LTDC_LxDCCR_DCGREEN          LTDC_LxDCCR_DCGREEN_Msk                   /*!< Default Color Green */
#define LTDC_LxDCCR_DCRED_Pos        (16U)
#define LTDC_LxDCCR_DCRED_Msk        (0xFFUL << LTDC_LxDCCR_DCRED_Pos)         /*!< 0x00FF0000 */
#define LTDC_LxDCCR_DCRED            LTDC_LxDCCR_DCRED_Msk                     /*!< Default Color Red   */
#define LTDC_LxDCCR_DCALPHA_Pos      (24U)
#define LTDC_LxDCCR_DCALPHA_Msk      (0xFFUL << LTDC_LxDCCR_DCALPHA_Pos)       /*!< 0xFF000000 */
#define LTDC_LxDCCR_DCALPHA          LTDC_LxDCCR_DCALPHA_Msk                   /*!< Default Color Alpha */

/********************  Bit definition for LTDC_LxBFCR register  ***************/
#define LTDC_LxBFCR_BF2_Pos          (0U)
#define LTDC_LxBFCR_BF2_Msk          (0x7UL << LTDC_LxBFCR_BF2_Pos)            /*!< 0x00000007 */
#define LTDC_LxBFCR_BF2              LTDC_LxBFCR_BF2_Msk                       /*!< Blending Factor 2 */
#define LTDC_LxBFCR_BF1_Pos          (8U)
#define LTDC_LxBFCR_BF1_Msk          (0x7UL << LTDC_LxBFCR_BF1_Pos)            /*!< 0x00000700 */
#define LTDC_LxBFCR_BF1              LTDC_LxBFCR_BF1_Msk                       /*!< Blending Factor 1 */

/********************  Bit definition for LTDC_LxCFBAR register  **************/
#define LTDC_LxCFBAR_CFBADD_Pos      (0U)
#define LTDC_LxCFBAR_CFBADD_Msk      (0xFFFFFFFFUL << LTDC_LxCFBAR_CFBADD_Pos) /*!< 0xFFFFFFFF */
#define LTDC_LxCFBAR_CFBADD          LTDC_LxCFBAR_CFBADD_Msk                   /*!< Color Frame Buffer Start Address */

/********************  Bit definition for LTDC_LxCFBLR register  **************/
#define LTDC_LxCFBLR_CFBLL_Pos       (0U)
#define LTDC_LxCFBLR_CFBLL_Msk       (0x1FFFUL << LTDC_LxCFBLR_CFBLL_Pos)      /*!< 0x00001FFF */
#define LTDC_LxCFBLR_CFBLL           LTDC_LxCFBLR_CFBLL_Msk                    /*!< Color Frame Buffer Line Length    */
#define LTDC_LxCFBLR_CFBP_Pos        (16U)
#define LTDC_LxCFBLR_CFBP_Msk        (0x1FFFUL << LTDC_LxCFBLR_CFBP_Pos)       /*!< 0x1FFF0000 */
#define LTDC_LxCFBLR_CFBP            LTDC_LxCFBLR_CFBP_Msk                     /*!< Color Frame Buffer Pitch in bytes */

/********************  Bit definition for LTDC_LxCFBLNR register  *************/
#define LTDC_LxCFBLNR_CFBLNBR_Pos    (0U)
#define LTDC_LxCFBLNR_CFBLNBR_Msk    (0x7FFUL << LTDC_LxCFBLNR_CFBLNBR_Pos)    /*!< 0x000007FF */
#define LTDC_LxCFBLNR_CFBLNBR        LTDC_LxCFBLNR_CFBLNBR_Msk                 /*!< Frame Buffer Line Number */

/********************  Bit definition for LTDC_LxCLUTWR register  *************/
#define LTDC_LxCLUTWR_BLUE_Pos       (0U)
#define LTDC_LxCLUTWR_BLUE_Msk       (0xFFUL << LTDC_LxCLUTWR_BLUE_Pos)        /*!< 0x000000FF */
#define LTDC_LxCLUTWR_BLUE           LTDC_LxCLUTWR_BLUE_Msk                    /*!< Blue value   */
#define LTDC_LxCLUTWR_GREEN_Pos      (8U)
#define LTDC_LxCLUTWR_GREEN_Msk      (0xFFUL << LTDC_LxCLUTWR_GREEN_Pos)       /*!< 0x0000FF00 */
#define LTDC_LxCLUTWR_GREEN          LTDC_LxCLUTWR_GREEN_Msk                   /*!< Green value  */
#define LTDC_LxCLUTWR_RED_Pos        (16U)
#define LTDC_LxCLUTWR_RED_Msk        (0xFFUL << LTDC_LxCLUTWR_RED_Pos)         /*!< 0x00FF0000 */
#define LTDC_LxCLUTWR_RED            LTDC_LxCLUTWR_RED_Msk                     /*!< Red value    */
#define LTDC_LxCLUTWR_CLUTADD_Pos    (24U)
#define LTDC_LxCLUTWR_CLUTADD_Msk    (0xFFUL << LTDC_LxCLUTWR_CLUTADD_Pos)     /*!< 0xFF000000 */
#define LTDC_LxCLUTWR_CLUTADD        LTDC_LxCLUTWR_CLUTADD_Msk                 /*!< CLUT address */


/********************  Bit definition for RCC_PLL2CFR register  *************/
#define RCC_PLL2CR_Q_DIV_1			 1
#define RCC_PLL2CR_Q_DIV_2			 2
#define RCC_PLL2CR_Q_DIV_3			 3
#define RCC_PLL2CR_Q_DIV_4			 4
#define RCC_PLL2CR_Q_DIV_5			 5
#define RCC_PLL2CR_Q_DIV_6			 6
#define RCC_PLL2CR_Q_DIV_7			 7
#define RCC_PLL2CR_Q_DIV_8			 8
#define RCC_PLL2CR_Q_DIV_9			 9
#define RCC_PLL2CR_Q_DIV_10			 10
#define RCC_PLL2CR_Q_DIV_11			 11
#define RCC_PLL2CR_Q_DIV_12			 12
#define RCC_PLL2CR_Q_DIV_13			 13
#define RCC_PLL2CR_Q_DIV_14			 14
#define RCC_PLL2CR_Q_DIV_15			 15


/********************  Bit definition for RCC_DCKCFG register  *************/
#define RCC_DCKCFG_DIV_2			 2
#define RCC_DCKCFG_DIV_4			 4
#define RCC_DCKCFG_DIV_8			 8
#define RCC_DCKCFG_DIV_16			 16



/** 
  * @brief  LTDC color structure definition
  */
typedef struct
{
  uint8_t Blue;                    /*!< Configures the blue value.
                                        This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint8_t Green;                   /*!< Configures the green value.
                                        This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint8_t Red;                     /*!< Configures the red value. 
                                        This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint8_t Reserved;                /*!< Reserved 0xFF */
} LTDC_ColorTypeDef;

/** 
  * @brief  LTDC Init structure definition
  */
typedef struct
{
  uint32_t            HSPolarity;                /*!< configures the horizontal synchronization polarity.
                                                      This parameter can be one value of @ref LTDC_HS_POLARITY */

  uint32_t            VSPolarity;                /*!< configures the vertical synchronization polarity.
                                                      This parameter can be one value of @ref LTDC_VS_POLARITY */

  uint32_t            DEPolarity;                /*!< configures the data enable polarity. 
                                                      This parameter can be one of value of @ref LTDC_DE_POLARITY */

  uint32_t            PCPolarity;                /*!< configures the pixel clock polarity. 
                                                      This parameter can be one of value of @ref LTDC_PC_POLARITY */

  uint32_t            HorizontalSync;            /*!< configures the number of Horizontal synchronization width.
                                                      This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */

  uint32_t            VerticalSync;              /*!< configures the number of Vertical synchronization height. 
                                                      This parameter must be a number between Min_Data = 0x000 and Max_Data = 0x7FF. */

  uint32_t            AccumulatedHBP;            /*!< configures the accumulated horizontal back porch width.
                                                      This parameter must be a number between Min_Data = LTDC_HorizontalSync and Max_Data = 0xFFF. */

  uint32_t            AccumulatedVBP;            /*!< configures the accumulated vertical back porch height.
                                                      This parameter must be a number between Min_Data = LTDC_VerticalSync and Max_Data = 0x7FF. */

  uint32_t            AccumulatedActiveW;        /*!< configures the accumulated active width. 
                                                      This parameter must be a number between Min_Data = LTDC_AccumulatedHBP and Max_Data = 0xFFF. */

  uint32_t            AccumulatedActiveH;        /*!< configures the accumulated active height.
                                                      This parameter must be a number between Min_Data = LTDC_AccumulatedVBP and Max_Data = 0x7FF. */

  uint32_t            TotalWidth;                /*!< configures the total width.
                                                      This parameter must be a number between Min_Data = LTDC_AccumulatedActiveW and Max_Data = 0xFFF. */

  uint32_t            TotalHeigh;                /*!< configures the total height.
                                                      This parameter must be a number between Min_Data = LTDC_AccumulatedActiveH and Max_Data = 0x7FF. */

  LTDC_ColorTypeDef   Backcolor;                 /*!< Configures the background color. */
} LTDC_InitTypeDef;

/** 
  * @brief  LTDC Layer structure definition
  */
typedef struct
{
  uint32_t WindowX0;                   /*!< Configures the Window Horizontal Start Position.
                                            This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */

  uint32_t WindowX1;                   /*!< Configures the Window Horizontal Stop Position.
                                            This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */

  uint32_t WindowY0;                   /*!< Configures the Window vertical Start Position.
                                            This parameter must be a number between Min_Data = 0x000 and Max_Data = 0x7FF. */

  uint32_t WindowY1;                   /*!< Configures the Window vertical Stop Position.
                                            This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0x7FF. */

  uint32_t PixelFormat;                /*!< Specifies the pixel format. 
                                            This parameter can be one of value of @ref LTDC_Pixelformat */

  uint32_t Alpha;                      /*!< Specifies the constant alpha used for blending.
                                            This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint32_t Alpha0;                     /*!< Configures the default alpha value.
                                            This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint32_t BlendingFactor1;            /*!< Select the blending factor 1. 
                                            This parameter can be one of value of @ref LTDC_BlendingFactor1 */

  uint32_t BlendingFactor2;            /*!< Select the blending factor 2. 
                                            This parameter can be one of value of @ref LTDC_BlendingFactor2 */

  uint32_t FBStartAdress;              /*!< Configures the color frame buffer address */

  uint32_t ImageWidth;                 /*!< Configures the color frame buffer line length. 
                                            This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0x1FFF. */

  uint32_t ImageHeight;                /*!< Specifies the number of line in frame buffer. 
                                            This parameter must be a number between Min_Data = 0x000 and Max_Data = 0x7FF. */

  LTDC_ColorTypeDef   Backcolor;       /*!< Configures the layer background color. */
} LTDC_LayerCfgTypeDef;

/** 
  * @brief  HAL LTDC State enumeration definition
  */
typedef enum
{
  HAL_LTDC_STATE_RESET             = 0x00U,    /*!< LTDC not yet initialized or disabled */
  HAL_LTDC_STATE_READY             = 0x01U,    /*!< LTDC initialized and ready for use   */
  HAL_LTDC_STATE_BUSY              = 0x02U,    /*!< LTDC internal process is ongoing     */
  HAL_LTDC_STATE_TIMEOUT           = 0x03U,    /*!< LTDC Timeout state                   */
  HAL_LTDC_STATE_ERROR             = 0x04U     /*!< LTDC state error                     */
}HAL_LTDC_StateTypeDef;

/** 
  * @brief  LTDC handle Structure definition
  */
typedef struct
{
  LTDC_TypeDef                *Instance;                /*!< LTDC Register base address                */

  LTDC_InitTypeDef            Init;                     /*!< LTDC parameters                           */

  LTDC_LayerCfgTypeDef        LayerCfg[MAX_LAYER];      /*!< LTDC Layers parameters                    */

  HAL_LockTypeDef             Lock;                     /*!< LTDC Lock                                 */

  __IO HAL_LTDC_StateTypeDef  State;                    /*!< LTDC state                                */

  __IO uint32_t               ErrorCode;                /*!< LTDC Error code                           */

} LTDC_HandleTypeDef;
/**
  * @}
  */

typedef struct
{
	GPIO_TypeDef *pGPIO_Port;
	uint16_t	GPIO_Pin;
	uint16_t	GPIO_Alt;
}GPIO_CfgDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup LTDC_Exported_Constants LTDC Exported Constants
  * @{
  */

/** @defgroup LTDC_Error_Code LTDC Error Code
  * @{
  */
#define HAL_LTDC_ERROR_NONE      (0x00000000U)    /*!< LTDC No error             */
#define HAL_LTDC_ERROR_TE        (0x00000001U)    /*!< LTDC Transfer error       */
#define HAL_LTDC_ERROR_FU        (0x00000002U)    /*!< LTDC FIFO Underrun        */
#define HAL_LTDC_ERROR_TIMEOUT   (0x00000020U)    /*!< LTDC Timeout error        */
/**
  * @}
  */

/** @defgroup LTDC_Layer LTDC Layer
  * @{
  */
#define LTDC_LAYER_1                      (0x00000000U)   /*!< LTDC Layer 1 */
#define LTDC_LAYER_2                      (0x00000001U)   /*!< LTDC Layer 2 */
/**
  * @}
  */


/** @defgroup LTDC_HS_POLARITY LTDC HS POLARITY
  * @{
  */
#define LTDC_HSPOLARITY_AL                (0x00000000U)                /*!< Horizontal Synchronization is active low. */
#define LTDC_HSPOLARITY_AH                LTDC_GCR_HSPOL               /*!< Horizontal Synchronization is active high. */
/**
  * @}
  */

/** @defgroup LTDC_VS_POLARITY LTDC VS POLARITY
  * @{
  */
#define LTDC_VSPOLARITY_AL                (0x00000000U)                /*!< Vertical Synchronization is active low. */
#define LTDC_VSPOLARITY_AH                LTDC_GCR_VSPOL               /*!< Vertical Synchronization is active high. */
/**
  * @}
  */
  
/** @defgroup LTDC_DE_POLARITY LTDC DE POLARITY
  * @{
  */
#define LTDC_DEPOLARITY_AL                (0x00000000U)                /*!< Data Enable, is active low. */
#define LTDC_DEPOLARITY_AH                LTDC_GCR_DEPOL               /*!< Data Enable, is active high. */
/**
  * @}
  */

/** @defgroup LTDC_PC_POLARITY LTDC PC POLARITY
  * @{
  */
#define LTDC_PCPOLARITY_IPC               (0x00000000U)                /*!< input pixel clock. */
#define LTDC_PCPOLARITY_IIPC              LTDC_GCR_PCPOL               /*!< inverted input pixel clock. */
/**
  * @}
  */

/** @defgroup LTDC_SYNC LTDC SYNC
  * @{
  */
#define LTDC_HORIZONTALSYNC               (LTDC_SSCR_HSW >> 16)                 /*!< Horizontal synchronization width. */ 
#define LTDC_VERTICALSYNC                 LTDC_SSCR_VSH                         /*!< Vertical synchronization height. */
/**
  * @}
  */

/** @defgroup LTDC_BACK_COLOR LTDC BACK COLOR
  * @{
  */
#define LTDC_COLOR                   (0x000000FFU)                     /*!< Color mask */ 
/**
  * @}
  */
      
/** @defgroup LTDC_BlendingFactor1 LTDC Blending Factor1
  * @{
  */
#define LTDC_BLENDING_FACTOR1_CA                       (0x00000400U)   /*!< Blending factor : Cte Alpha */
#define LTDC_BLENDING_FACTOR1_PAxCA                    (0x00000600U)   /*!< Blending factor : Cte Alpha x Pixel Alpha*/
/**
  * @}
  */

/** @defgroup LTDC_BlendingFactor2 LTDC Blending Factor2
  * @{
  */
#define LTDC_BLENDING_FACTOR2_CA                       (0x00000005U)   /*!< Blending factor : Cte Alpha */
#define LTDC_BLENDING_FACTOR2_PAxCA                    (0x00000007U)   /*!< Blending factor : Cte Alpha x Pixel Alpha*/
/**
  * @}
  */
      
/** @defgroup LTDC_Pixelformat LTDC Pixel format
  * @{
  */
#define LTDC_PIXEL_FORMAT_ARGB8888                  (0x00000000U)      /*!< ARGB8888 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_RGB888                    (0x00000001U)      /*!< RGB888 LTDC pixel format   */
#define LTDC_PIXEL_FORMAT_RGB565                    (0x00000002U)      /*!< RGB565 LTDC pixel format   */
#define LTDC_PIXEL_FORMAT_ARGB1555                  (0x00000003U)      /*!< ARGB1555 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_ARGB4444                  (0x00000004U)      /*!< ARGB4444 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_L8                        (0x00000005U)      /*!< L8 LTDC pixel format       */
#define LTDC_PIXEL_FORMAT_AL44                      (0x00000006U)      /*!< AL44 LTDC pixel format     */
#define LTDC_PIXEL_FORMAT_AL88                      (0x00000007U)      /*!< AL88 LTDC pixel format     */
/**
  * @}
  */

/** @defgroup LTDC_Alpha LTDC Alpha
  * @{
  */
#define LTDC_ALPHA               LTDC_LxCACR_CONSTA                    /*!< LTDC Cte Alpha mask */
/**
  * @}
  */

/** @defgroup LTDC_LAYER_Config LTDC LAYER Config
  * @{
  */
#define LTDC_STOPPOSITION                 (LTDC_LxWHPCR_WHSPPOS >> 16)          /*!< LTDC Layer stop position  */
#define LTDC_STARTPOSITION                LTDC_LxWHPCR_WHSTPOS                  /*!< LTDC Layer start position */

#define LTDC_COLOR_FRAME_BUFFER           LTDC_LxCFBLR_CFBLL                    /*!< LTDC Layer Line length    */ 
#define LTDC_LINE_NUMBER                  LTDC_LxCFBLNR_CFBLNBR                 /*!< LTDC Layer Line number    */
/**
  * @}
  */

/** @defgroup LTDC_Interrupts LTDC Interrupts
  * @{
  */
#define LTDC_IT_LI                      LTDC_IER_LIE
#define LTDC_IT_FU                      LTDC_IER_FUIE
#define LTDC_IT_TE                      LTDC_IER_TERRIE
#define LTDC_IT_RR                      LTDC_IER_RRIE
/**
  * @}
  */
      
/** @defgroup LTDC_Flags LTDC Flags
  * @{
  */
#define LTDC_FLAG_LI                     LTDC_ISR_LIF
#define LTDC_FLAG_FU                     LTDC_ISR_FUIF
#define LTDC_FLAG_TE                     LTDC_ISR_TERRIF
#define LTDC_FLAG_RR                     LTDC_ISR_RRIF
/**
  * @}
  */

/** @defgroup LTDC_Reload_Type LTDC Reload Type
  * @{
  */
#define LTDC_RELOAD_IMMEDIATE            LTDC_SRCR_IMR       /*!< Immediate Reload */
#define LTDC_RELOAD_VERTICAL_BLANKING    LTDC_SRCR_VBR       /*!< Vertical Blanking Reload */
/**
  * @}
  */

/**
  * @}
  */  

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LTDC_Exported_Macros LTDC Exported Macros
  * @{
  */

/** @brief Reset LTDC handle state.
  * @param  __HANDLE__  LTDC handle
  * @retval None
  */
#define __HAL_LTDC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_LTDC_STATE_RESET)

/**
  * @brief  Enable the LTDC.
  * @param  __HANDLE__: LTDC handle
  * @retval None.
  */
#define __HAL_LTDC_ENABLE(__HANDLE__)    ((__HANDLE__)->Instance->GCR |= LTDC_GCR_LTDCEN)

/**
  * @brief  Disable the LTDC.
  * @param  __HANDLE__: LTDC handle
  * @retval None.
  */
#define __HAL_LTDC_DISABLE(__HANDLE__)   ((__HANDLE__)->Instance->GCR &= ~(LTDC_GCR_LTDCEN))

/**
  * @brief  Enable the LTDC Layer.
  * @param  __HANDLE__  LTDC handle
  * @param  __LAYER__   Specify the layer to be enabled.
  *                     This parameter can be LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1).
  * @retval None.
  */
#define __HAL_LTDC_LAYER_ENABLE(__HANDLE__, __LAYER__)  ((LTDC_LAYER((__HANDLE__), (__LAYER__)))->CR |= (uint32_t)LTDC_LxCR_LEN)

/**
  * @brief  Disable the LTDC Layer.
  * @param  __HANDLE__  LTDC handle
  * @param  __LAYER__   Specify the layer to be disabled.
  *                     This parameter can be LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1).
  * @retval None.
  */
#define __HAL_LTDC_LAYER_DISABLE(__HANDLE__, __LAYER__) ((LTDC_LAYER((__HANDLE__), (__LAYER__)))->CR &= ~(uint32_t)LTDC_LxCR_LEN)

/**
  * @brief  Reload immediately all LTDC Layers.
  * @param  __HANDLE__  LTDC handle
  * @retval None.
  */
#define __HAL_LTDC_RELOAD_IMMEDIATE_CONFIG(__HANDLE__)  ((__HANDLE__)->Instance->SRCR |= LTDC_SRCR_IMR)

/**
  * @brief  Reload during vertical blanking period all LTDC Layers.
  * @param  __HANDLE__  LTDC handle
  * @retval None.
  */
#define __HAL_LTDC_VERTICAL_BLANKING_RELOAD_CONFIG(__HANDLE__)  ((__HANDLE__)->Instance->SRCR |= LTDC_SRCR_VBR)

/* Interrupt & Flag management */
/**
  * @brief  Get the LTDC pending flags.
  * @param  __HANDLE__: LTDC handle
  * @param  __FLAG__: Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_FLAG_LI: Line Interrupt flag 
  *            @arg LTDC_FLAG_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_FLAG_TE: Transfer Error interrupt flag
  *            @arg LTDC_FLAG_RR: Register Reload Interrupt Flag 
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_LTDC_GET_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ISR & (__FLAG__))

/**
  * @brief  Clears the LTDC pending flags.
  * @param  __HANDLE__: LTDC handle
  * @param  __FLAG__: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_FLAG_LI: Line Interrupt flag 
  *            @arg LTDC_FLAG_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_FLAG_TE: Transfer Error interrupt flag
  *            @arg LTDC_FLAG_RR: Register Reload Interrupt Flag 
  * @retval None
  */
#define __HAL_LTDC_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = (__FLAG__))

/**
  * @brief  Enables the specified LTDC interrupts.
  * @param  __HANDLE__: LTDC handle
  * @param __INTERRUPT__: specifies the LTDC interrupt sources to be enabled. 
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_IT_LI: Line Interrupt flag 
  *            @arg LTDC_IT_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_IT_TE: Transfer Error interrupt flag
  *            @arg LTDC_IT_RR: Register Reload Interrupt Flag
  * @retval None
  */
#define __HAL_LTDC_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER |= (__INTERRUPT__))

/**
  * @brief  Disables the specified LTDC interrupts.
  * @param  __HANDLE__: LTDC handle
  * @param __INTERRUPT__: specifies the LTDC interrupt sources to be disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg LTDC_IT_LI: Line Interrupt flag 
  *            @arg LTDC_IT_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_IT_TE: Transfer Error interrupt flag
  *            @arg LTDC_IT_RR: Register Reload Interrupt Flag
  * @retval None
  */
#define __HAL_LTDC_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER &= ~(__INTERRUPT__))

/**
  * @brief  Checks whether the specified LTDC interrupt has occurred or not.
  * @param  __HANDLE__: LTDC handle
  * @param  __INTERRUPT__: specifies the LTDC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg LTDC_IT_LI: Line Interrupt flag 
  *            @arg LTDC_IT_FU: FIFO Underrun Interrupt flag
  *            @arg LTDC_IT_TE: Transfer Error interrupt flag
  *            @arg LTDC_IT_RR: Register Reload Interrupt Flag
  * @retval The state of INTERRUPT (SET or RESET).
  */
#define __HAL_LTDC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER & (__INTERRUPT__))
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup LTDC_Exported_Functions
  * @{
  */
/** @addtogroup LTDC_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_LTDC_Clk_Div(uint8_t PLL2Q, uint8_t DckCfg);
HAL_StatusTypeDef HAL_LTDC_Init(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_DeInit(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc);
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc);
void HAL_LTDC_ErrorCallback(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_ReloadEventCallback(LTDC_HandleTypeDef *hltdc);
/**
  * @}
  */

/** @addtogroup LTDC_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/
void  HAL_LTDC_IRQHandler(LTDC_HandleTypeDef *hltdc);
void HAL_LTDC_ERR_IRQHandler(LTDC_HandleTypeDef *hltdc);
/**
  * @}
  */

/** @addtogroup LTDC_Exported_Functions_Group3
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_LTDC_ConfigLayer(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetWindowSize(LTDC_HandleTypeDef *hltdc, uint32_t XSize, uint32_t YSize, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetWindowPosition(LTDC_HandleTypeDef *hltdc, uint32_t X0, uint32_t Y0, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetPixelFormat(LTDC_HandleTypeDef *hltdc, uint32_t Pixelformat, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetAlpha(LTDC_HandleTypeDef *hltdc, uint32_t Alpha, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetAddress(LTDC_HandleTypeDef *hltdc, uint32_t Address, uint32_t LayerIdx, uint32_t ReloadType);
HAL_StatusTypeDef HAL_LTDC_SetPitch(LTDC_HandleTypeDef *hltdc, uint32_t LinePitchInPixels, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_ConfigColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t RGBValue, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_ConfigCLUT(LTDC_HandleTypeDef *hltdc, uint32_t *pCLUT, uint32_t CLUTSize, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_EnableColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_EnableCLUT(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableCLUT(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_ProgramLineEvent(LTDC_HandleTypeDef *hltdc, uint32_t Line);
HAL_StatusTypeDef HAL_LTDC_EnableDither(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_DisableDither(LTDC_HandleTypeDef *hltdc);
HAL_StatusTypeDef HAL_LTDC_Reload(LTDC_HandleTypeDef *hltdc, uint32_t ReloadType);
HAL_StatusTypeDef HAL_LTDC_ConfigLayer_NoReload(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetWindowSize_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t XSize, uint32_t YSize, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetWindowPosition_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t X0, uint32_t Y0, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetPixelFormat_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Pixelformat, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetAlpha_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Alpha, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetAddress_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Address, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_SetPitch_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LinePitchInPixels, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_ConfigColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t RGBValue, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_EnableColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_EnableCLUT_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);
HAL_StatusTypeDef HAL_LTDC_DisableCLUT_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx);

/**
  * @}
  */

/** @addtogroup LTDC_Exported_Functions_Group4
  * @{
  */
/* Peripheral State functions *************************************************/
HAL_LTDC_StateTypeDef HAL_LTDC_GetState(LTDC_HandleTypeDef *hltdc);
uint32_t              HAL_LTDC_GetError(LTDC_HandleTypeDef *hltdc);
/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/** @defgroup LTDC_Private_Types LTDC Private Types
  * @{
  */

/**
  * @}
  */ 

/* Private variables ---------------------------------------------------------*/
/** @defgroup LTDC_Private_Variables LTDC Private Variables
  * @{
  */

/**
  * @}
  */ 

/* Private constants ---------------------------------------------------------*/
/** @defgroup LTDC_Private_Constants LTDC Private Constants
  * @{
  */

/**
  * @}
  */ 

/* Private macros ------------------------------------------------------------*/
/** @defgroup LTDC_Private_Macros LTDC Private Macros
  * @{
  */
#define IS_LTDC_ALL_INSTANCE(INSTANCE)					((INSTANCE) == LTDC)
#define LTDC_LAYER(__HANDLE__, __LAYER__)              ((LTDC_Layer_TypeDef *)((uint32_t)(((uint32_t)((__HANDLE__)->Instance)) + 0x84 + (0x80*(__LAYER__)))))
#define IS_LTDC_LAYER(__LAYER__)                       ((__LAYER__) < MAX_LAYER)
#define IS_LTDC_HSPOL(__HSPOL__)                       (((__HSPOL__) == LTDC_HSPOLARITY_AL) || ((__HSPOL__) == LTDC_HSPOLARITY_AH))
#define IS_LTDC_VSPOL(__VSPOL__)                       (((__VSPOL__) == LTDC_VSPOLARITY_AL) || ((__VSPOL__) == LTDC_VSPOLARITY_AH))
#define IS_LTDC_DEPOL(__DEPOL__)                       (((__DEPOL__) == LTDC_DEPOLARITY_AL) || ((__DEPOL__) ==  LTDC_DEPOLARITY_AH))
#define IS_LTDC_PCPOL(__PCPOL__)                       (((__PCPOL__) == LTDC_PCPOLARITY_IPC) || ((__PCPOL__) ==  LTDC_PCPOLARITY_IIPC))
#define IS_LTDC_HSYNC(__HSYNC__)                       ((__HSYNC__)  <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_VSYNC(__VSYNC__)                       ((__VSYNC__)  <= LTDC_VERTICALSYNC)
#define IS_LTDC_AHBP(__AHBP__)                         ((__AHBP__)   <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_AVBP(__AVBP__)                         ((__AVBP__)   <= LTDC_VERTICALSYNC)
#define IS_LTDC_AAW(__AAW__)                           ((__AAW__)    <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_AAH(__AAH__)                           ((__AAH__)    <= LTDC_VERTICALSYNC)
#define IS_LTDC_TOTALW(__TOTALW__)                     ((__TOTALW__) <= LTDC_HORIZONTALSYNC)
#define IS_LTDC_TOTALH(__TOTALH__)                     ((__TOTALH__) <= LTDC_VERTICALSYNC)
#define IS_LTDC_BLUEVALUE(__BBLUE__)                   ((__BBLUE__)  <= LTDC_COLOR)
#define IS_LTDC_GREENVALUE(__BGREEN__)                 ((__BGREEN__) <= LTDC_COLOR)
#define IS_LTDC_REDVALUE(__BRED__)                     ((__BRED__)   <= LTDC_COLOR)
#define IS_LTDC_BLENDING_FACTOR1(__BLENDING_FACTOR1__) (((__BLENDING_FACTOR1__) == LTDC_BLENDING_FACTOR1_CA) || \
                                                        ((__BLENDING_FACTOR1__) == LTDC_BLENDING_FACTOR1_PAxCA))
#define IS_LTDC_BLENDING_FACTOR2(__BLENDING_FACTOR2__) (((__BLENDING_FACTOR2__) == LTDC_BLENDING_FACTOR2_CA) || \
                                                        ((__BLENDING_FACTOR2__) == LTDC_BLENDING_FACTOR2_PAxCA))

#define IS_LTDC_PIXEL_FORMAT(__PIXEL_FORMAT__)         (((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_ARGB8888) || ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_RGB888)   || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_RGB565)   || ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_ARGB1555) || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_ARGB4444) || ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_L8)       || \
                                                        ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_AL44)     || ((__PIXEL_FORMAT__) == LTDC_PIXEL_FORMAT_AL88))

#define IS_LTDC_ALPHA(__ALPHA__)                       ((__ALPHA__) <= LTDC_ALPHA)
#define IS_LTDC_HCONFIGST(__HCONFIGST__)               ((__HCONFIGST__) <= LTDC_STARTPOSITION)
#define IS_LTDC_HCONFIGSP(__HCONFIGSP__)               ((__HCONFIGSP__) <= LTDC_STOPPOSITION)
#define IS_LTDC_VCONFIGST(__VCONFIGST__)               ((__VCONFIGST__) <= LTDC_STARTPOSITION)
#define IS_LTDC_VCONFIGSP(__VCONFIGSP__)               ((__VCONFIGSP__) <= LTDC_STOPPOSITION)
#define IS_LTDC_CFBP(__CFBP__)                         ((__CFBP__) <= LTDC_COLOR_FRAME_BUFFER)
#define IS_LTDC_CFBLL(__CFBLL__)                       ((__CFBLL__) <= LTDC_COLOR_FRAME_BUFFER)
#define IS_LTDC_CFBLNBR(__CFBLNBR__)                   ((__CFBLNBR__) <= LTDC_LINE_NUMBER)
#define IS_LTDC_LIPOS(__LIPOS__)                       ((__LIPOS__) <= 0x7FFU)
#define IS_LTDC_RELOAD(__RELOADTYPE__)                 (((__RELOADTYPE__) == LTDC_RELOAD_IMMEDIATE) || ((__RELOADTYPE__) == LTDC_RELOAD_VERTICAL_BLANKING))
/**
  * @}
  */ 

/* Private functions ---------------------------------------------------------*/
/** @defgroup LTDC_Private_Functions LTDC Private Functions
  * @{
  */

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

#endif	//#ifdef __HAL_LTDC_H__
