/******************************************************************************
*@file  : hal_cortex.h
*@brief : Header file of CORTEX HAL module.
******************************************************************************/

#ifndef __HAL_CORTEX_H
#define __HAL_CORTEX_H

#include "hal_def.h"

#if (__MPU_PRESENT == 1U)
typedef struct
{
  uint8_t                Enable;                /*!< Specifies the status of the region. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Enable                 */
  uint8_t                Number;                /*!< Specifies the number of the region to protect. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Number                 */
  uint32_t               BaseAddress;           /*!< Specifies the base address of the region to protect.                           */
  uint32_t               LimitAddress;          /*!< Specifies the limit address of the region to protect.                          */
  uint8_t                AttributesIndex;       /*!< Specifies the memory attributes index.
                                                     This parameter can be a value of @ref CORTEX_MPU_Attributes_Number             */
  uint8_t                AccessPermission;      /*!< Specifies the region access permission type. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Permission_Attributes  */
  uint8_t                DisableExec;           /*!< Specifies the instruction access status. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Instruction_Access            */
  uint8_t                IsShareable;           /*!< Specifies the shareability status of the protected region. 
                                                     This parameter can be a value of @ref CORTEX_MPU_Access_Shareable              */
} MPU_Region_InitTypeDef;

typedef struct
{
  uint8_t                Number;                /*!< Specifies the number of the memory attributes to configure.
                                                     This parameter can be a value of @ref CORTEX_MPU_Attributes_Number              */

  uint8_t                Attributes;            /*!< Specifies the memory attributes vue.
                                                     This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFFFF    */

} MPU_Attributes_InitTypeDef;

#endif /* __MPU_PRESENT */


/** CORTEX_Preemption_Priority_Group CORTEX Preemption Priority Group  */
#define NVIC_PRIORITYGROUP_0         0x00000007U /*!< 0 bits for pre-emption priority, 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         0x00000006U /*!< 1 bits for pre-emption priority, 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         0x00000005U /*!< 2 bits for pre-emption priority, 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         0x00000004U /*!< 3 bits for pre-emption priority, 1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4         0x00000003U /*!< 4 bits for pre-emption priority, 0 bits for subpriority */

/** CORTEX_SysTick_clock_source CORTEX _SysTick clock source  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8    0x00000000U
#define SYSTICK_CLKSOURCE_HCLK         0x00000004U


/** CORTEX_MPU_HFNMI_PRIVDEF_Control MPU HFNMI and PRIVILEGED Access control */
#if (__MPU_PRESENT == 1)

#define  MPU_HFNMI_PRIVDEF_NONE          0U
#define  MPU_HARDFAULT_NMI               2U
#define  MPU_PRIVILEGED_DEFAULT          4U
#define  MPU_HFNMI_PRIVDEF               6U

/** CORTEX_MPU_Region_Enable CORTEX MPU Region Enable */
#define  MPU_REGION_ENABLE               1U
#define  MPU_REGION_DISABLE              0U

/** CORTEX_MPU_Instruction_Access CORTEX MPU Instruction Access */
#define  MPU_INSTRUCTION_ACCESS_ENABLE   0U
#define  MPU_INSTRUCTION_ACCESS_DISABLE  1U

/** CORTEX_MPU_Access_Shareable CORTEX MPU Instruction Access Shareable */
#define  MPU_ACCESS_NOT_SHAREABLE        0U
#define  MPU_ACCESS_OUTER_SHAREABLE      1U
#define  MPU_ACCESS_INNER_SHAREABLE      3U

/** @defgroup CORTEX_MPU_Region_Permission_Attributes CORTEX MPU Region Permission Attributes */
#define  MPU_REGION_PRIV_RW              0U
#define  MPU_REGION_ALL_RW               1U
#define  MPU_REGION_PRIV_RO              2U
#define  MPU_REGION_ALL_RO               3U

/** @defgroup CORTEX_MPU_Region_Number CORTEX MPU Region Number */
#define  MPU_REGION_NUMBER0              0U
#define  MPU_REGION_NUMBER1              1U
#define  MPU_REGION_NUMBER2              2U
#define  MPU_REGION_NUMBER3              3U
#define  MPU_REGION_NUMBER4              4U
#define  MPU_REGION_NUMBER5              5U
#define  MPU_REGION_NUMBER6              6U
#define  MPU_REGION_NUMBER7              7U

/** @defgroup CORTEX_MPU_Attributes_Number CORTEX MPU Memory Attributes Number */
#define  MPU_ATTRIBUTES_NUMBER0          0U
#define  MPU_ATTRIBUTES_NUMBER1          1U
#define  MPU_ATTRIBUTES_NUMBER2          2U
#define  MPU_ATTRIBUTES_NUMBER3          3U
#define  MPU_ATTRIBUTES_NUMBER4          4U
#define  MPU_ATTRIBUTES_NUMBER5          5U
#define  MPU_ATTRIBUTES_NUMBER6          6U
#define  MPU_ATTRIBUTES_NUMBER7          7U

/** @defgroup CORTEX_MPU_Attributes CORTEX MPU Attributes */
#define  MPU_DEVICE_nGnRnE          0x0U  /* Device, noGather, noReorder, noEarly acknowledge. */
#define  MPU_DEVICE_nGnRE           0x4U  /* Device, noGather, noReorder, Early acknowledge.   */
#define  MPU_DEVICE_nGRE            0x8U  /* Device, noGather, Reorder, Early acknowledge.     */
#define  MPU_DEVICE_GRE             0xCU  /* Device, Gather, Reorder, Early acknowledge.       */

#define  MPU_WRITE_THROUGH          0x0U  /* Normal memory, write-through. */
#define  MPU_NOT_CACHEABLE          0x4U  /* Normal memory, non-cacheable. */
#define  MPU_WRITE_BACK             0x4U  /* Normal memory, write-back.    */

#define  MPU_TRANSIENT              0x0U  /* Normal memory, transient.     */
#define  MPU_NON_TRANSIENT          0x8U  /* Normal memory, non-transient. */

#define  MPU_NO_ALLOCATE            0x0U  /* Normal memory, no allocate.         */
#define  MPU_W_ALLOCATE             0x1U  /* Normal memory, write allocate.      */
#define  MPU_R_ALLOCATE             0x2U  /* Normal memory, read allocate.       */
#define  MPU_RW_ALLOCATE            0x3U  /* Normal memory, read/write allocate. */

#define OUTER(__ATTR__)        ((__ATTR__) << 4U)
#define INNER_OUTER(__ATTR__)  ((__ATTR__) | ((__ATTR__) << 4U))


//@defgroup MPU_HFNMI_xxxx
//@{
#define MPU_HFNMI_DISABLE               (0) // MPU is disabled during HardFault and NMI handlers
#define MPU_HFNMI_ENABLE                (1) // The MPU is enabled during HardFault and NMI handlers
//@}

//@defgroup MPU_PRIVDEF_xxxx
//@{
#define MPU_PRIVDEF_DISABLE             (0) // Disables use of the default memory map
#define MPU_PRIVDEF_ENABLE              (1) // Enables use of the default memory map  as a background region for privileged software accesses
//@}

//@defgroup MPU_ACCESS_xxxx
//@{
#define MPU_ACCESS_PRIV_READ_WRITE      (0) // Read/write by privileged code only
#define MPU_ACCESS_ALL_READ_WRITE       (1) // Read/write by any privilege level
#define MPU_ACCESS_PRIV_READ_ONLY       (2) // Read-only by privileged code only
#define MPU_ACCESS_ALL_READ_ONLY        (3) // Read-only by any privilege level
//@}

//@defgroup MPU_EXECUTE_xxxx
//@{
#define MPU_EXECUTE_ENABLE              (0) // Enables execution
#define MPU_EXECUTE_DISABLE             (1) // Disables execution
//@}

//@defgroup MPU_ATTR_xxxx
//@{
#define MPU_ATTR_NO_CACHE               (0x44) //normal memory,non-cacheable
#define MPU_ATTR_WRITE_THROUGH           (0xAA) //normal memory,write-through,read-allocation
#define MPU_ATTR_WRITE_BACK             (0xFF) //normal memory,write-back,read-allocation,write-allocation
#define MPU_ATTR_DEVICE                 (0x00) //device memory¡ê?nGnRnE
//@}

typedef struct
{
    uint32_t BaseAddr;  // the lower inclusive limit of the selected MPU memory region,lower 5 bits fixed to 0b'00000
    uint32_t LimitAddr; // the upper inclusive limit of the selected MPU memory region,lower 5 bits fixed to 0b'11111
    uint8_t Access;     // read/write access permissions. @ref MPU_ACCESS_xxxx
    uint8_t Execute;    // execute permissions. @ref MPU_EXECUTE_xxxx
    uint8_t Attr;       // attributes, @ref MPU_ATTR_xxxx
}MPU_RegionConfigTypeDef;

typedef struct
{
    uint8_t HfNmi;      // @ref MPU_HFNMI_xxxx    
    uint8_t PrivDef;    // @ref MPU_PRIVDEF_xxxx  
    uint8_t RegionCount;  // region count.    
    MPU_RegionConfigTypeDef *RegionConfigs; //region configs.
}MPU_ConfigInitTypeDef;

#endif /* __MPU_PRESENT */


void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
HAL_StatusTypeDef HAL_SYSTICK_Config(uint32_t TicksNum);

uint32_t HAL_NVIC_GetPriorityGrouping(void);
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);

void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);

#if (__MPU_PRESENT == 1U)
void HAL_MPU_Enable(uint32_t MPU_Control);
void HAL_MPU_Disable(void);
void HAL_MPU_ConfigRegion(MPU_Region_InitTypeDef *MPU_RegionInit);
void HAL_MPU_ConfigMemoryAttributes(MPU_Attributes_InitTypeDef *MPU_AttributesInit);
void HAL_MPU_Config(MPU_ConfigInitTypeDef *MPU_configInit);
#endif /* __MPU_PRESENT */


/** @defgroup CORTEX_Private_Macros CORTEX Private Macros */
#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PRIORITYGROUP_0) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_1) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_2) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_3) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_4))

#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10U)

#define IS_NVIC_SUB_PRIORITY(PRIORITY)         ((PRIORITY) < 0x10U)

#define IS_NVIC_DEVICE_IRQ(IRQ)                ((IRQ) >= (IRQn_Type)0x00U)

#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SYSTICK_CLKSOURCE_HCLK) || \
                                       ((SOURCE) == SYSTICK_CLKSOURCE_HCLK_DIV8))

#if (__MPU_PRESENT == 1U)
#define IS_MPU_REGION_ENABLE(STATE) (((STATE) == MPU_REGION_ENABLE) || \
                                     ((STATE) == MPU_REGION_DISABLE))

#define IS_MPU_INSTRUCTION_ACCESS(STATE) (((STATE) == MPU_INSTRUCTION_ACCESS_ENABLE) || \
                                          ((STATE) == MPU_INSTRUCTION_ACCESS_DISABLE))

#define IS_MPU_ACCESS_SHAREABLE(STATE)   (((STATE) == MPU_ACCESS_OUTER_SHAREABLE) || \
                                          ((STATE) == MPU_ACCESS_INNER_SHAREABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_SHAREABLE))

#define IS_MPU_REGION_PERMISSION_ATTRIBUTE(TYPE) (((TYPE) == MPU_REGION_PRIV_RW) || \
                                                  ((TYPE) == MPU_REGION_ALL_RW)  || \
                                                  ((TYPE) == MPU_REGION_PRIV_RO)     || \
                                                  ((TYPE) == MPU_REGION_ALL_RO))

#define IS_MPU_REGION_NUMBER(NUMBER)    (((NUMBER) == MPU_REGION_NUMBER0) || \
                                         ((NUMBER) == MPU_REGION_NUMBER1) || \
                                         ((NUMBER) == MPU_REGION_NUMBER2) || \
                                         ((NUMBER) == MPU_REGION_NUMBER3) || \
                                         ((NUMBER) == MPU_REGION_NUMBER4) || \
                                         ((NUMBER) == MPU_REGION_NUMBER5) || \
                                         ((NUMBER) == MPU_REGION_NUMBER6) || \
                                         ((NUMBER) == MPU_REGION_NUMBER7))

#define IS_MPU_ATTRIBUTES_NUMBER(NUMBER)  (((NUMBER) == MPU_ATTRIBUTES_NUMBER0) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER1) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER2) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER3) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER4) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER5) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER6) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER7))
#endif /* __MPU_PRESENT */

#endif
