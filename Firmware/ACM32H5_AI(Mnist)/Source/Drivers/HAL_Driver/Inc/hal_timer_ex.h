/***********************************************************************
 * Filename    : hal_timer_ex.h
 * Description : timer driver header file
 * Author(s)   : xwl  
 * version     : V1.0
 * Modify date : 2021-03-24
 ***********************************************************************/
#ifndef __HAL_TIMER_EX_H__
#define __HAL_TIMER_EX_H__  

#include "hal.h"     


#define TIM_BDTR_DTG_Pos          (0U)
#define TIM_BDTR_DTG_Msk          (0xFFUL << TIM_BDTR_DTG_Pos)                 /*!< 0x000000FF */
#define TIM_BDTR_DTG              TIM_BDTR_DTG_Msk                             /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define TIM_BDTR_DTG_0            (0x01UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000001 */
#define TIM_BDTR_DTG_1            (0x02UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000002 */
#define TIM_BDTR_DTG_2            (0x04UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000004 */
#define TIM_BDTR_DTG_3            (0x08UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000008 */
#define TIM_BDTR_DTG_4            (0x10UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000010 */
#define TIM_BDTR_DTG_5            (0x20UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000020 */
#define TIM_BDTR_DTG_6            (0x40UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000040 */
#define TIM_BDTR_DTG_7            (0x80UL << TIM_BDTR_DTG_Pos)    

#define TIM_BDTR_LOCK_Pos         (8U)
#define TIM_BDTR_LOCK_Msk         (0x3UL << TIM_BDTR_LOCK_Pos)                 /*!< 0x00000300 */
#define TIM_BDTR_LOCK             TIM_BDTR_LOCK_Msk                            /*!<LOCK[1:0] bits (Lock Configuration) */
#define TIM_BDTR_LOCK_0           (0x1UL << TIM_BDTR_LOCK_Pos)                 /*!< 0x00000100 */
#define TIM_BDTR_LOCK_1           (0x2UL << TIM_BDTR_LOCK_Pos)    

#define TIM_BDTR_OSSI_Pos         (10U)
#define TIM_BDTR_OSSI_Msk         (0x1UL << TIM_BDTR_OSSI_Pos)                 /*!< 0x00000400 */
#define TIM_BDTR_OSSI             TIM_BDTR_OSSI_Msk                            /*!<Off-State Selection for Idle mode */
#define TIM_BDTR_OSSI_OFF_STATE   (0 << TIM_BDTR_OSSI_Pos)  
#define TIM_BDTR_OSSI_IDLE_STATE  (1 << TIM_BDTR_OSSI_Pos)   
#define TIM_BDTR_OSSR_Pos         (11U)
#define TIM_BDTR_OSSR_Msk         (0x1UL << TIM_BDTR_OSSR_Pos)                 /*!< 0x00000800 */
#define TIM_BDTR_OSSR             TIM_BDTR_OSSR_Msk                            /*!<Off-State Selection for Run mode */
#define TIM_BDTR_OSSR_OFF_STATE   (0 << TIM_BDTR_OSSR_Pos) 
#define TIM_BDTR_OSSR_INACT_STATE (1 << TIM_BDTR_OSSR_Pos) 
#define TIM_BDTR_BKE_Pos          (12U)
#define TIM_BDTR_BKE_Msk          (0x1UL << TIM_BDTR_BKE_Pos)                  /*!< 0x00001000 */
#define TIM_BDTR_BKE              TIM_BDTR_BKE_Msk                             /*!<Break enable for Break 1 */
#define TIM_BDTR_BREAK_DISABLE    0                                            /*!<Break disable for Break 1 */
#define TIM_BDTR_BKP_Pos          (13U)
#define TIM_BDTR_BKP_Msk          (0x1UL << TIM_BDTR_BKP_Pos)                  /*!< 0x00002000 */
#define TIM_BDTR_BKP              TIM_BDTR_BKP_Msk                             /*!<Break Polarity for Break 1 */
#define TIM_BDTR_ACTIVE_LOW       (0 << TIM_BDTR_BKP_Pos) 
#define TIM_BDTR_ACTIVE_HIGH      (1 << TIM_BDTR_BKP_Pos)  
#define TIM_BDTR_AOE_Pos          (14U)
#define TIM_BDTR_AOE_Msk          (0x1UL << TIM_BDTR_AOE_Pos)                  /*!< 0x00004000 */
#define TIM_BDTR_AOE              TIM_BDTR_AOE_Msk                             /*!<Automatic Output enable */
#define TIM_BDTR_MOE_Pos          (15U)
#define TIM_BDTR_MOE_Msk          (0x1UL << TIM_BDTR_MOE_Pos)                  /*!< 0x00008000 */
#define TIM_BDTR_MOE              TIM_BDTR_MOE_Msk                             /*!<Main Output enable */

#define TIM_BDTR_BKF_Pos          (16U)
#define TIM_BDTR_BKF_Msk          (0xFUL << TIM_BDTR_BKF_Pos)                  /*!< 0x000F0000 */
#define TIM_BDTR_BKF              TIM_BDTR_BKF_Msk       

#define TIM_BREAKINPUTSOURCE_BKIN     0x00000001U                               /* !< An external source (GPIO) is connected to the BKIN pin  */

#define TIM_BREAKINPUTSOURCE_COMP1    0x00000002U                               /* !< The COMP1 output is connected to the break input */
#define TIM_BREAKINPUTSOURCE_COMP2    0x00000004U                               /* !< The COMP2 output is connected to the break input */
#define TIM_BREAKINPUTSOURCE_COMP3    0x00000008U                               /* !< The COMP3 output is connected to the break input */
#define TIM_BREAKINPUTSOURCE_COMP4    0x00000010U                               /* !< The COMP4 output is connected to the break input */
#define TIM_BREAKINPUTSOURCE_SYSTEM   0xFFFFFFFFU                               // LVD, SRAM ECC Error, CPU Lockup 

#define TIM_BREAKINPUT_BRK     0x00000001U      

#define TIM_BREAKINPUTSOURCE_POLARITY_LOW      0x00000000U    

#define TIM_BREAKINPUTSOURCE_POLARITY_HIGH     0x00000001U        

#define BREAK_INPUT_FILTER_LEVEL(x)  ((x) << TIM_BDTR_BKF_Pos)   

#define TIM_BREAK_ENABLE    1
#define TIM_BREAK_DISABLE   0

#define TIM1_AF1_BKINE_Pos        (0U)
#define TIM1_AF1_BKINE_Msk        (0x1UL << TIM1_AF1_BKINE_Pos)                /*!< 0x00000001 */
#define TIM1_AF1_BKINE            TIM1_AF1_BKINE_Msk                           /*!<BRK BKIN input enable */
#define TIM1_AF1_BKCMP1E_Pos      (1U)
#define TIM1_AF1_BKCMP1E_Msk      (0x1UL << TIM1_AF1_BKCMP1E_Pos)              /*!< 0x00000002 */
#define TIM1_AF1_BKCMP1E          TIM1_AF1_BKCMP1E_Msk                         /*!<BRK COMP1 enable */
#define TIM1_AF1_BKCMP2E_Pos      (2U)
#define TIM1_AF1_BKCMP2E_Msk      (0x1UL << TIM1_AF1_BKCMP2E_Pos)              /*!< 0x00000004 */
#define TIM1_AF1_BKCMP2E          TIM1_AF1_BKCMP2E_Msk                         /*!<BRK COMP2 enable */
#define TIM1_AF1_BKCMP3E_Pos      (3U)
#define TIM1_AF1_BKCMP3E_Msk      (0x1UL << TIM1_AF1_BKCMP3E_Pos)              /*!< 0x00000008 */
#define TIM1_AF1_BKCMP3E          TIM1_AF1_BKCMP3E_Msk                         /*!<BRK COMP3 enable */
#define TIM1_AF1_BKCMP4E_Pos      (4U)
#define TIM1_AF1_BKCMP4E_Msk      (0x1UL << TIM1_AF1_BKCMP4E_Pos)              /*!< 0x00000010 */
#define TIM1_AF1_BKCMP4E          TIM1_AF1_BKCMP4E_Msk                         /*!<BRK COMP4 enable */
#define TIM1_AF1_BKINP_Pos        (9U)
#define TIM1_AF1_BKINP_Msk        (0x1UL << TIM1_AF1_BKINP_Pos)                /*!< 0x00000200 */
#define TIM1_AF1_BKINP            TIM1_AF1_BKINP_Msk                           /*!<BRK BKIN input polarity */
#define TIM1_AF1_BKCMP1P_Pos      (10U)
#define TIM1_AF1_BKCMP1P_Msk      (0x1UL << TIM1_AF1_BKCMP1P_Pos)              /*!< 0x00000400 */
#define TIM1_AF1_BKCMP1P          TIM1_AF1_BKCMP1P_Msk                         /*!<BRK COMP1 input polarity */
#define TIM1_AF1_BKCMP2P_Pos      (11U)
#define TIM1_AF1_BKCMP2P_Msk      (0x1UL << TIM1_AF1_BKCMP2P_Pos)              /*!< 0x00000800 */
#define TIM1_AF1_BKCMP2P          TIM1_AF1_BKCMP2P_Msk                         /*!<BRK COMP2 input polarity */
#define TIM1_AF1_BKCMP3P_Pos      (12U)
#define TIM1_AF1_BKCMP3P_Msk      (0x1UL << TIM1_AF1_BKCMP3P_Pos)              /*!< 0x00001000 */
#define TIM1_AF1_BKCMP3P          TIM1_AF1_BKCMP3P_Msk                         /*!<BRK COMP3 input polarity */
#define TIM1_AF1_BKCMP4P_Pos      (13U)
#define TIM1_AF1_BKCMP4P_Msk      (0x1UL << TIM1_AF1_BKCMP4P_Pos)              /*!< 0x00002000 */
#define TIM1_AF1_BKCMP4P          TIM1_AF1_BKCMP4P_Msk                         /*!<BRK COMP4 input polarity */


typedef struct
{
  uint32_t OffStateRunMode;           // TIM off state in run mode
  uint32_t OffStateIDLEMode;          // TIM off state in IDLE mode
  uint32_t LockLevel;                 // TIM Lock level
  uint32_t DeadTime;                  // TIM dead Time
  uint32_t BreakState;                // TIM Break State
  uint32_t BreakPolarity;             // TIM Break input polarity
  uint32_t BreakFilter;               // Specifies the break input filter.
  uint32_t AutomaticOutput;           // TIM Automatic Output Enable state   
} TIM_BreakDeadTimeConfigTypeDef;     

typedef struct
{
  uint32_t Source;         /*!< Specifies the source of the timer break input.
                                This parameter can be a value of @ref TIMEx_Break_Input_Source */
  uint32_t Enable;         /*!< Specifies whether or not the break input source is enabled.
                                This parameter can be a value of @ref TIMEx_Break_Input_Source_Enable */
  uint32_t Polarity;       /*!< Specifies the break input source polarity.
                                This parameter can be a value of @ref TIMEx_Break_Input_Source_Polarity */
}
TIMEx_BreakInputConfigTypeDef;

/*******************  Bit definition for TIM_TISEL register  *********************/
#define TIM_TISEL_TI1SEL_Pos      (0U)
#define TIM_TISEL_TI1SEL_Msk      (0xFUL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x0000000F */
#define TIM_TISEL_TI1SEL          TIM_TISEL_TI1SEL_Msk                         /*!<TI1SEL[3:0] bits (TIM TI1 SEL)*/
#define TIM_TISEL_TI1SEL_0        (0x1UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000001 */
#define TIM_TISEL_TI1SEL_1        (0x2UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000002 */
#define TIM_TISEL_TI1SEL_2        (0x4UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000004 */
#define TIM_TISEL_TI1SEL_3        (0x8UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000008 */

#define TIM_TISEL_TI2SEL_Pos      (8U)
#define TIM_TISEL_TI2SEL_Msk      (0xFUL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000F00 */
#define TIM_TISEL_TI2SEL          TIM_TISEL_TI2SEL_Msk                         /*!<TI2SEL[3:0] bits (TIM TI2 SEL)*/
#define TIM_TISEL_TI2SEL_0        (0x1UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000100 */
#define TIM_TISEL_TI2SEL_1        (0x2UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000200 */
#define TIM_TISEL_TI2SEL_2        (0x4UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000400 */
#define TIM_TISEL_TI2SEL_3        (0x8UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000800 */

#define TIM_TISEL_TI3SEL_Pos      (16U)
#define TIM_TISEL_TI3SEL_Msk      (0xFUL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x000F0000 */
#define TIM_TISEL_TI3SEL          TIM_TISEL_TI3SEL_Msk                         /*!<TI3SEL[3:0] bits (TIM TI3 SEL)*/
#define TIM_TISEL_TI3SEL_0        (0x1UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00010000 */
#define TIM_TISEL_TI3SEL_1        (0x2UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00020000 */
#define TIM_TISEL_TI3SEL_2        (0x4UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00040000 */
#define TIM_TISEL_TI3SEL_3        (0x8UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00080000 */

#define TIM_TISEL_TI4SEL_Pos      (24U)
#define TIM_TISEL_TI4SEL_Msk      (0xFUL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x0F000000 */
#define TIM_TISEL_TI4SEL          TIM_TISEL_TI4SEL_Msk                         /*!<TI4SEL[3:0] bits (TIM TI4 SEL)*/
#define TIM_TISEL_TI4SEL_0        (0x1UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x01000000 */
#define TIM_TISEL_TI4SEL_1        (0x2UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x02000000 */
#define TIM_TISEL_TI4SEL_2        (0x4UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x04000000 */
#define TIM_TISEL_TI4SEL_3        (0x8UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x08000000 */

/*******************  TIMEx_Timer_Input_Selection TIM Extended Timer input selection  *********************/
#define TIM_TIM1_TI1_GPIO   0x00000000U                                       /*!< TIM1 input 1 is connected to GPIO */
#define TIM_TIM1_TI1_COMP1  TIM_TISEL_TI1SEL_0                                /*!< TIM1 input 1 is connected to COMP1_OUT */
#define TIM_TIM1_TI1_COMP2  TIM_TISEL_TI1SEL_1                                /*!< TIM1 input 1 is connected to COMP2_OUT */
#define TIM_TIM1_TI1_COMP3  (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)         /*!< TIM1 input 1 is connected to COMP3_OUT */
#define TIM_TIM1_TI1_COMP4  TIM_TISEL_TI1SEL_2                                /*!< TIM1 input 1 is connected to COMP4_OUT */

#define TIM_TIM1_TI2_GPIO   0x00000000U                                       /*!< TIM1 input 2 is connected to GPIO */

#define TIM_TIM1_TI3_GPIO   0x00000000U                                       /*!< TIM1 input 3 is connected to GPIO */

#define TIM_TIM1_TI4_GPIO   0x00000000U                                       /*!< TIM1 input 4 is connected to GPIO */

#define TIM_TIM2_TI1_GPIO   0x00000000U                                       /*!< TIM2 input 1 is connected to GPIO */
#define TIM_TIM2_TI1_COMP1  TIM_TISEL_TI1SEL_0                                /*!< TIM2 input 1 is connected to COMP1_OUT */
#define TIM_TIM2_TI1_COMP2  TIM_TISEL_TI1SEL_1                                /*!< TIM2 input 1 is connected to COMP2_OUT */
#define TIM_TIM2_TI1_COMP3  (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)         /*!< TIM2 input 1 is connected to COMP3_OUT */
#define TIM_TIM2_TI1_COMP4  TIM_TISEL_TI1SEL_2                                /*!< TIM2 input 1 is connected to COMP4_OUT */

#define TIM_TIM2_TI2_GPIO   0x00000000U                                       /*!< TIM2 input 2 is connected to GPIO */
#define TIM_TIM2_TI2_COMP1  TIM_TISEL_TI2SEL_0                                /*!< TIM2 input 2 is connected to COMP1_OUT */
#define TIM_TIM2_TI2_COMP2  TIM_TISEL_TI2SEL_1                                /*!< TIM2 input 2 is connected to COMP2_OUT */
#define TIM_TIM2_TI2_COMP3  (TIM_TISEL_TI2SEL_1 | TIM_TISEL_TI2SEL_0)         /*!< TIM2 input 2 is connected to COMP3_OUT */
#define TIM_TIM2_TI2_COMP4  TIM_TISEL_TI2SEL_2                                /*!< TIM2 input 2 is connected to COMP4_OUT */

#define TIM_TIM2_TI3_GPIO   0x00000000U                                       /*!< TIM2 input 3 is connected to GPIO */
#define TIM_TIM2_TI3_COMP4  TIM_TISEL_TI3SEL_0                                /*!< TIM2 input 3 is connected to COMP4_OUT */

#define TIM_TIM2_TI4_GPIO   0x00000000U                                       /*!< TIM2 input 4 is connected to GPIO */
#define TIM_TIM2_TI4_COMP1  TIM_TISEL_TI4SEL_0                                /*!< TIM2 input 4 is connected to COMP1_OUT */
#define TIM_TIM2_TI4_COMP2  TIM_TISEL_TI4SEL_1                                /*!< TIM2 input 4 is connected to COMP2_OUT */

#define TIM_TIM3_TI1_GPIO   0x00000000U                                       /*!< TIM3 input 1 is connected to GPIO */
#define TIM_TIM3_TI1_COMP1  TIM_TISEL_TI1SEL_0                                /*!< TIM3 input 1 is connected to COMP1_OUT */
#define TIM_TIM3_TI1_COMP2  TIM_TISEL_TI1SEL_1                                /*!< TIM3 input 1 is connected to COMP2_OUT */
#define TIM_TIM3_TI1_COMP3  (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)         /*!< TIM3 input 1 is connected to COMP3_OUT */
#define TIM_TIM3_TI1_COMP4  TIM_TISEL_TI1SEL_2                                /*!< TIM3 input 1 is connected to COMP4_OUT */

#define TIM_TIM3_TI2_GPIO   0x00000000U                                       /*!< TIM3 input 2 is connected to GPIO */
#define TIM_TIM3_TI2_COMP1  TIM_TISEL_TI2SEL_0                                /*!< TIM3 input 2 is connected to COMP1_OUT */
#define TIM_TIM3_TI2_COMP2  TIM_TISEL_TI2SEL_1                                /*!< TIM3 input 2 is connected to COMP2_OUT */
#define TIM_TIM3_TI2_COMP3  (TIM_TISEL_TI2SEL_1 | TIM_TISEL_TI2SEL_0)         /*!< TIM3 input 2 is connected to COMP3_OUT */
#define TIM_TIM3_TI2_COMP4  TIM_TISEL_TI2SEL_2                                /*!< TIM3 input 2 is connected to COMP4_OUT */

#define TIM_TIM3_TI3_GPIO   0x00000000U                                       /*!< TIM3 input 3 is connected to GPIO */
#define TIM_TIM3_TI3_COMP3  TIM_TISEL_TI3SEL_0                                /*!< TIM3 input 3 is connected to COMP3_OUT */

#define TIM_TIM3_TI4_GPIO   0x00000000U                                       /*!< TIM3 input 4 is connected to GPIO */

#define TIM_TIM4_TI1_GPIO   0x00000000U                                       /*!< TIM4 input 1 is connected to GPIO */
#define TIM_TIM4_TI1_COMP1  TIM_TISEL_TI1SEL_0                                /*!< TIM4 input 1 is connected to COMP1_OUT */
#define TIM_TIM4_TI1_COMP2  TIM_TISEL_TI1SEL_1                                /*!< TIM4 input 1 is connected to COMP2_OUT */
#define TIM_TIM4_TI1_COMP3  (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)         /*!< TIM4 input 1 is connected to COMP3_OUT */
#define TIM_TIM4_TI1_COMP4  TIM_TISEL_TI1SEL_2                                /*!< TIM4 input 1 is connected to COMP4_OUT */

#define TIM_TIM4_TI2_GPIO   0x00000000U                                       /*!< TIM4 input 2 is connected to GPIO */
#define TIM_TIM4_TI2_COMP1  TIM_TISEL_TI2SEL_0                                /*!< TIM4 input 2 is connected to COMP1_OUT */
#define TIM_TIM4_TI2_COMP2  TIM_TISEL_TI2SEL_1                                /*!< TIM4 input 2 is connected to COMP2_OUT */
#define TIM_TIM4_TI2_COMP3  (TIM_TISEL_TI2SEL_1 | TIM_TISEL_TI2SEL_0)         /*!< TIM4 input 2 is connected to COMP3_OUT */
#define TIM_TIM4_TI2_COMP4  TIM_TISEL_TI2SEL_2                                /*!< TIM4 input 2 is connected to COMP4_OUT */

#define TIM_TIM4_TI3_GPIO   0x00000000U                                       /*!< TIM4 input 3 is connected to GPIO */

#define TIM_TIM4_TI4_GPIO   0x00000000U                                       /*!< TIM4 input 4 is connected to GPIO */

#define TIM_TIM8_TI1_GPIO   0x00000000U                                       /*!< TIM8 input 1 is connected to GPIO */
#define TIM_TIM8_TI1_COMP1  TIM_TISEL_TI1SEL_0                                /*!< TIM8 input 1 is connected to COMP1_OUT */
#define TIM_TIM8_TI1_COMP2  TIM_TISEL_TI1SEL_1                                /*!< TIM8 input 1 is connected to COMP2_OUT */
#define TIM_TIM8_TI1_COMP3  (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)         /*!< TIM8 input 1 is connected to COMP3_OUT */
#define TIM_TIM8_TI1_COMP4  TIM_TISEL_TI1SEL_2                                /*!< TIM8 input 1 is connected to COMP4_OUT */

#define TIM_TIM8_TI2_GPIO   0x00000000U                                       /*!< TIM8 input 2 is connected to GPIO */

#define TIM_TIM8_TI3_GPIO   0x00000000U                                       /*!< TIM8 input 3 is connected to GPIO */

#define TIM_TIM8_TI4_GPIO   0x00000000U                                       /*!< TIM8 input 4 is connected to GPIO */

#define TIM_TIM15_TI1_GPIO  0x00000000U                                       /*!< TIM15 input 1 is connected to GPIO */
#define TIM_TIM15_TI1_COMP1 TIM_TISEL_TI1SEL_0                                /*!< TIM15 input 1 is connected to COMP1_OUT */
#define TIM_TIM15_TI1_COMP2 TIM_TISEL_TI1SEL_1                                /*!< TIM15 input 1 is connected to COMP2_OUT */
#define TIM_TIM15_TI1_MCO   (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)         /*!< TIM15 input 1 is connected to MCO */
#define TIM_TIM15_TI1_RX1   TIM_TISEL_TI1SEL_2                                /*!< TIM15 input 1 is connected to UART1 RX */

#define TIM_TIM15_TI2_GPIO  0x00000000U                                       /*!< TIM15 input 2 is connected to GPIO */
#define TIM_TIM15_TI2_COMP2 TIM_TISEL_TI2SEL_0                                /*!< TIM15 input 2 is connected to COMP2_OUT */
#define TIM_TIM15_TI2_COMP3 TIM_TISEL_TI2SEL_1                                /*!< TIM15 input 2 is connected to COMP3_OUT */
#define TIM_TIM15_TI2_MCO   (TIM_TISEL_TI2SEL_1 | TIM_TISEL_TI2SEL_0)         /*!< TIM15 input 2 is connected to MCO */
#define TIM_TIM15_TI2_RX2   TIM_TISEL_TI2SEL_2                                /*!< TIM15 input 2 is connected to UART2 RX */

#define TIM_TIM16_TI1_GPIO    0x00000000U                                     /*!< TIM16 input 1 is connected to GPIO */
#define TIM_TIM16_TI1_MCO     TIM_TISEL_TI1SEL_0                              /*!< TIM16 input 1 is connected to MCO */
#define TIM_TIM16_TI1_HSE_32  TIM_TISEL_TI1SEL_1                              /*!< TIM16 input 1 is connected to HSE/32 */
#define TIM_TIM16_TI1_RTC_WK  (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)       /*!< TIM16 input 1 is connected to RTC_WAKEUP */
#define TIM_TIM16_TI1_LSI     TIM_TISEL_TI1SEL_2                              /*!< TIM16 input 1 is connected to LSI RC32K */

#define TIM_TIM17_TI1_GPIO    0x00000000U                                     /*!< TIM17 input 1 is connected to GPIO */
#define TIM_TIM17_TI1_MCO     TIM_TISEL_TI1SEL_0                              /*!< TIM17 input 1 is connected to MCO */
#define TIM_TIM17_TI1_USB_SOF TIM_TISEL_TI1SEL_1                              /*!< TIM17 input 1 is connected to USB_SOF */
#define TIM_TIM17_TI1_RTC_WK  (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)       /*!< TIM17 input 1 is connected to RTC_WAKEUP */
#define TIM_TIM17_TI1_LSI     TIM_TISEL_TI1SEL_2                              /*!< TIM17 input 1 is connected to LSI RC32K */


extern void HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim, TIM_BreakDeadTimeConfigTypeDef * sBreakDeadTimeConfig);
extern HAL_StatusTypeDef HAL_TIMEx_ConfigBreakInput(TIM_HandleTypeDef *htim, TIMEx_BreakInputConfigTypeDef *sBreakInputConfig);
extern void HAL_TIMEx_ConfigCommutEvent(TIM_HandleTypeDef *htim, uint32_t  InputTrigger, uint32_t  CommutationSource);
extern HAL_StatusTypeDef  HAL_TIMEx_TISelection(TIM_HandleTypeDef *htim, uint32_t TISelection, uint32_t Channel);

#endif  




