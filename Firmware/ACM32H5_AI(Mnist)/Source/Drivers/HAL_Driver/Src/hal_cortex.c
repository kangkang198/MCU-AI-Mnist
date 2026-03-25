/******************************************************************************
*@file  : hal_cortex.c
*@brief : CORTEX HAL module driver
******************************************************************************/


#include "hal.h"

#if (__MPU_PRESENT == 1)
static void MPU_ConfigRegion(MPU_Type* MPUx, MPU_Region_InitTypeDef *MPU_RegionInit);
static void MPU_ConfigMemoryAttributes(MPU_Type* MPUx, MPU_Attributes_InitTypeDef *MPU_AttributesInit);
#endif /* __MPU_PRESENT */

/******************************************************************************
*@brief : Sets the priority grouping field (preemption priority and subpriority) using the required unlock sequence.
*@param : PriorityGroup: The priority grouping bits length.
*           This parameter can be one of the following values:
*           @arg NVIC_PRIORITYGROUP_0: 0 bits for pre-emption priority, 4 bits for subpriority
*           @arg NVIC_PRIORITYGROUP_1: 1 bits for pre-emption priority, 3 bits for subpriority
*           @arg NVIC_PRIORITYGROUP_2: 2 bits for pre-emption priority, 2 bits for subpriority
*           @arg NVIC_PRIORITYGROUP_3: 3 bits for pre-emption priority, 1 bits for subpriority
*           @arg NVIC_PRIORITYGROUP_4: 4 bits for pre-emption priority, 0 bits for subpriority
*@note  : When the NVIC_PriorityGroup_0 is selected, IRQ preemption is no more possible.
*           The pending IRQ priority will be managed only by the subpriority. 
*@ret   : none
******************************************************************************/
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
    /* Check the parameters */
    assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));
  
    /* Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value */
    NVIC_SetPriorityGrouping(PriorityGroup);
}

/******************************************************************************
*@brief : Sets the priority of an interrupt.
*@param : IRQn: External interrupt number.
*           This parameter can be an enumerator of IRQn_Type enumeration
*@param : PreemptPriority: The preemption priority for the IRQn channel.
*           This parameter can be a value between 0 and 15.
*           A lower priority value indicates a higher priority
*@param : SubPriority: he subpriority level for the IRQ channel.
*           This parameter can be a value between 0 and 15.
*           A lower priority value indicates a higher priority. 
*@ret   : None
******************************************************************************/
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{ 
    uint32_t prioritygroup = 0x00U;
  
    /* Check the parameters */
    assert_param(IS_NVIC_SUB_PRIORITY(SubPriority));
    assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority));
  
    prioritygroup = NVIC_GetPriorityGrouping();
  
    NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}

/******************************************************************************
*@brief : Enables a device specific interrupt in the NVIC interrupt controller.
*@param : IRQn: External interrupt number.
*           This parameter can be an enumerator of IRQn_Type enumeration 
*@ret   : None
******************************************************************************/
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Enable interrupt */
    NVIC_EnableIRQ(IRQn);
}

/******************************************************************************
*@brief : Disables a device specific interrupt in the NVIC interrupt controller.
*@param : IRQn: External interrupt number.
*           This parameter can be an enumerator of IRQn_Type enumeration 
*@ret   : None
******************************************************************************/
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Disable interrupt */
    NVIC_DisableIRQ(IRQn);
}


/******************************************************************************
*@brief : Initiates a system reset request to reset the MCU. 
*@ret   : None
******************************************************************************/
void HAL_NVIC_SystemReset(void)
{
  /* System Reset */
  NVIC_SystemReset();
}

/******************************************************************************
*@brief : Initializes the System Timer and its interrupt, and starts the System Tick Timer.
*         Counter is in free running mode to generate periodic interrupts.
*@param : TicksNum: Specifies the ticks Number of ticks between two interrupts.
*@ret   : None
******************************************************************************/
HAL_StatusTypeDef HAL_SYSTICK_Config(uint32_t TicksNum)
{
   if(SysTick_Config(TicksNum)==0)
   {
       return HAL_OK;
   }
   else
   {
       return HAL_ERROR;
   }
}

#if (__MPU_PRESENT == 1U)

/******************************************************************************
*@brief : Enable the MPU.
*@param : MPU_Control: Specifies the control mode of the MPU during hard fault,
*           NMI, FAULTMASK and privileged access to the default memory
*           This parameter can be one of the following values:
*           @arg MPU_HFNMI_PRIVDEF_NONE
*           @arg MPU_HARDFAULT_NMI
*           @arg MPU_PRIVILEGED_DEFAULT
*           @arg MPU_HFNMI_PRIVDEF
*@ret   : None
******************************************************************************/
void HAL_MPU_Enable(uint32_t MPU_Control)
{
    /* Enable the MPU */
    MPU->CTRL = MPU_Control | MPU_CTRL_ENABLE_Msk;
  
    /* Enable fault exceptions */
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
  
    /* Ensure MPU setting take effects */
    __DSB();
    __ISB();
}

/******************************************************************************
*@brief : Disables the MPU. 
*@ret   : None
******************************************************************************/
void HAL_MPU_Disable(void)
{
    /* Make sure outstanding transfers are done */
    __DMB();

    /* Disable fault exceptions */
    SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;
  
    /* Disable the MPU and clear the control register*/
    MPU->CTRL = 0U;
}


/******************************************************************************
*@brief : Initializes and configures the Region and the memory to be protected.
*@param : MPU_RegionInit: Pointer to a MPU_Region_InitTypeDef structure that contains 
*           the initialization and configuration information.
*@ret   : None
******************************************************************************/
void HAL_MPU_ConfigRegion(MPU_Region_InitTypeDef *MPU_RegionInit)
{
    MPU_ConfigRegion(MPU, MPU_RegionInit);
}

/******************************************************************************
*@brief : Initialize and configure the memory attributes.
*@param : MPU_AttributesInit Pointer to a MPU_Attributes_InitTypeDef structure that contains
*           the initialization and configuration information.
*@ret   : None
******************************************************************************/
void HAL_MPU_ConfigMemoryAttributes(MPU_Attributes_InitTypeDef *MPU_AttributesInit)
{
    MPU_ConfigMemoryAttributes(MPU, MPU_AttributesInit);
}

static void MPU_ConfigRegion(MPU_Type* MPUx, MPU_Region_InitTypeDef *MPU_RegionInit)
{
    /* Check the parameters */
    assert_param(IS_MPU_REGION_NUMBER(MPU_RegionInit->Number));
    assert_param(IS_MPU_REGION_ENABLE(MPU_RegionInit->Enable));

    /* Follow ARM recommendation with Data Memory Barrier prior to MPU configuration */
    __DMB();

    /* Set the Region number */
    MPUx->RNR = MPU_RegionInit->Number;

    if (MPU_RegionInit->Enable != MPU_REGION_DISABLE)
    {
        /* Check the parameters */
        assert_param(IS_MPU_INSTRUCTION_ACCESS(MPU_RegionInit->DisableExec));
        assert_param(IS_MPU_REGION_PERMISSION_ATTRIBUTE(MPU_RegionInit->AccessPermission));
        assert_param(IS_MPU_ACCESS_SHAREABLE(MPU_RegionInit->IsShareable));

        MPUx->RBAR = (((uint32_t)MPU_RegionInit->BaseAddress & 0xFFFFFFE0U)  |
                  ((uint32_t)MPU_RegionInit->IsShareable      << MPU_RBAR_SH_Pos)  |
                  ((uint32_t)MPU_RegionInit->AccessPermission << MPU_RBAR_AP_Pos)  |
                  ((uint32_t)MPU_RegionInit->DisableExec      << MPU_RBAR_XN_Pos));

        MPUx->RLAR = (((uint32_t)MPU_RegionInit->LimitAddress & 0xFFFFFFE0U) |
                  ((uint32_t)MPU_RegionInit->AttributesIndex << MPU_RLAR_AttrIndx_Pos) |
                  ((uint32_t)MPU_RegionInit->Enable          << MPU_RLAR_EN_Pos));
    }
    else
    {
        MPUx->RBAR = 0U;
        MPUx->RLAR = 0U;
    }
}

static void MPU_ConfigMemoryAttributes(MPU_Type* MPUx, MPU_Attributes_InitTypeDef *MPU_AttributesInit)
{
    __IO uint32_t *mair;
    uint32_t      attr_values;
    uint32_t      attr_number;

    /* Check the parameters */
    assert_param(IS_MPU_ATTRIBUTES_NUMBER(MPU_AttributesInit->Number));
    /* No need to check Attributes value as all 0x0..0xFF possible */

    /* Follow ARM recommendation with Data Memory Barrier prior to MPUx configuration */
    __DMB();

    if(MPU_AttributesInit->Number < MPU_ATTRIBUTES_NUMBER4)
    {
        /* Program MPU_MAIR0 */
        mair = &(MPUx->MAIR0);
        attr_number = MPU_AttributesInit->Number;
    }
    else
    {
        /* Program MPU_MAIR1 */
        mair = &(MPUx->MAIR1);
        attr_number = (uint32_t)MPU_AttributesInit->Number - 4U;
    }

    attr_values = *(mair);
    attr_values &=  ~(0xFFU << (attr_number * 8U));
    *(mair) = attr_values | ((uint32_t)MPU_AttributesInit->Attributes << (attr_number * 8U));
}


// default mpu attrs
const uint8_t MPU_attrs[8] = 
{
    MPU_ATTR_NO_CACHE,
    MPU_ATTR_WRITE_THROUGH,
    MPU_ATTR_WRITE_BACK,
    MPU_ATTR_DEVICE, 
    0,
    0,
    0,
    0
};

/******************************************************************************
*@brief : MPU config.        
*@param : MPU_configInit: mpu config init parameter
*@return: void
******************************************************************************/
void HAL_MPU_Config(MPU_ConfigInitTypeDef *MPU_configInit)
{
    uint32_t i,j,count,attrIndex;
    uint32_t ctrl;
    MPU_RegionConfigTypeDef *pRegion;
    
    HAL_MPU_Disable();
    
    __DMB();
    
    //Config Memory Attributes
    MPU->MAIR0 = MPU_attrs[0] | (MPU_attrs[1]<<8) | (MPU_attrs[2]<<16) | (MPU_attrs[3]<<24);    
    MPU->MAIR1 = MPU_attrs[4] | (MPU_attrs[5]<<8) | (MPU_attrs[6]<<16) | (MPU_attrs[7]<<24);

    count = MPU_configInit->RegionCount;    
    if(count>8)
    {
        count = 8;
    }
    
    for(i=0; i<count; i++)
    {
        pRegion = MPU_configInit->RegionConfigs + i;  
        
        //get index by attribute
        attrIndex = 0; //default attr index
        for(j=0;j<8;j++)
        {
            if(MPU_attrs[j] == pRegion->Attr)
            {
                attrIndex = j;
                break; 
            }
        }        
 
        //config region
        MPU->RNR = i; 
        
        MPU->RBAR = ((pRegion->BaseAddr & MPU_RBAR_BASE_Msk) | 
                     ((pRegion->Access<<MPU_RBAR_AP_Pos) & MPU_RBAR_SH_Msk) |
                     ((pRegion->Execute<<MPU_RBAR_XN_Pos) & MPU_RBAR_XN_Msk));

        MPU->RLAR = ((pRegion->LimitAddr & MPU_RLAR_LIMIT_Msk) | 
                     ((attrIndex<<MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) |
                     (MPU_RLAR_EN_Msk));             
    }
    
    for(; i<8; i++)
    {
        MPU->RNR = i;
        MPU->RBAR = 0;
        MPU->RLAR = 0;   
    }
    
    
    ctrl = (((MPU_configInit->PrivDef<<MPU_CTRL_PRIVDEFENA_Pos)&MPU_CTRL_PRIVDEFENA_Msk) | 
            ((MPU_configInit->HfNmi<<MPU_CTRL_HFNMIENA_Pos)&MPU_CTRL_HFNMIENA_Msk) |
            (MPU_CTRL_ENABLE_Msk));             
    
    HAL_MPU_Enable(ctrl); //enable mpu
    __DMB();
}

#endif /* __MPU_PRESENT */


/******************************************************************************
*@brief : Gets the priority grouping field from the NVIC Interrupt Controller.
*@ret   : Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field)
******************************************************************************/
uint32_t HAL_NVIC_GetPriorityGrouping(void)
{
    /* Get the PRIGROUP[10:8] field value */
    return NVIC_GetPriorityGrouping();
}

/******************************************************************************
*@brief : Gets the priority of an interrupt.
*@param : IRQn: External interrupt number.
*           This parameter can be an enumerator of IRQn_Type enumeration
*@param : PriorityGroup: The priority grouping bits length.
*           This parameter can be one of the following values:
*           @arg NVIC_PRIORITYGROUP_0: 0 bits for pre-emption priority, 4 bits for subpriority
*           @arg NVIC_PRIORITYGROUP_1: 1 bits for pre-emption priority, 3 bits for subpriority
*           @arg NVIC_PRIORITYGROUP_2: 2 bits for pre-emption priority, 2 bits for subpriority
*           @arg NVIC_PRIORITYGROUP_3: 3 bits for pre-emption priority, 1 bits for subpriority
*           @arg NVIC_PRIORITYGROUP_4: 4 bits for pre-emption priority, 0 bits for subpriority
*@param : pPreemptPriority: Pointer on the Preemptive priority value (starting from 0).
*@param : pSubPriority: Pointer on the Subpriority value (starting from 0).
*@ret   : None
******************************************************************************/
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority)
{
    /* Check the parameters */
    assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));
    
    /* Get priority for Cortex-M system or device specific interrupts */
    NVIC_DecodePriority(NVIC_GetPriority(IRQn), PriorityGroup, pPreemptPriority, pSubPriority);
}

/******************************************************************************
*@brief : Sets Pending bit of an external interrupt.
*@param : IRQn: External interrupt number.
*           This parameter can be an enumerator of IRQn_Type enumeration
*@ret   : None
******************************************************************************/
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Set interrupt pending */
    NVIC_SetPendingIRQ(IRQn);
}

/******************************************************************************
*@brief : Gets Pending Interrupt (reads the pending register in the NVIC
*         and returns the pending bit for the specified interrupt).  
*@param : IRQn: External interrupt number.
*           This parameter can be an enumerator of IRQn_Type enumeration
*@ret   : status: - 0  Interrupt status is not pending.
*                 - 1  Interrupt status is pending.
******************************************************************************/
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Return 1 if pending else 0 */
    return NVIC_GetPendingIRQ(IRQn);
}

/******************************************************************************
*@brief : Clears the pending bit of an external interrupt.
*@param : IRQn: External interrupt number.
*           This parameter can be an enumerator of IRQn_Type enumeration
*@ret   : None
******************************************************************************/
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Clear pending interrupt */
    NVIC_ClearPendingIRQ(IRQn);
}

/******************************************************************************
*@brief : Gets active interrupt ( reads the active register in NVIC and returns the active bit).  
*@param : IRQn: External interrupt number.
*           This parameter can be an enumerator of IRQn_Type enumeration
*@ret   : status: - 0  Interrupt status is not pending.
*                 - 1  Interrupt status is pending.
******************************************************************************/
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
  
    /* Return 1 if active else 0 */
    return NVIC_GetActive(IRQn);
}

/******************************************************************************
*@brief : Configures the SysTick clock source.  
*@param : CLKSource specifies the SysTick clock source.
*           This parameter can be one of the following values:
*           @arg SYSTICK_CLKSOURCE_HCLK_DIV8: AHB clock divided by 8 selected as SysTick clock source.
*           @arg SYSTICK_CLKSOURCE_HCLK: AHB clock selected as SysTick clock source.
*@ret   : None
******************************************************************************/
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource)
{
    /* Check the parameters */
    assert_param(IS_SYSTICK_CLK_SOURCE(CLKSource));
    if (CLKSource == SYSTICK_CLKSOURCE_HCLK)
    {
        SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
    }
    else
    {
        SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
    }
}


/******************************************************************************
*@brief : This function handles SYSTICK interrupt request. 
*@ret   : None
******************************************************************************/
void HAL_SYSTICK_IRQHandler(void)
{
    HAL_SYSTICK_Callback();
}

/******************************************************************************
*@brief : SYSTICK callback.
*@ret   : None
******************************************************************************/
__weak void HAL_SYSTICK_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SYSTICK_Callback could be implemented in the user file
   */
}




