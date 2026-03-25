/******************************************************************************
*@file  : hal_exti.c
*@brief : GPIO EXTI module driver.
******************************************************************************/
#include "hal.h" 

#ifdef HAL_EXTI_MODULE_ENABLED

/******************************************************************************
*@brief : EXTI interrupt request.
*@param : Line: Exti line number.
*               This parameter can be a combination of @ref EXTI_Line.
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_EXTI_IRQHandler(uint32_t Line)
{
    assert_param(IS_EXTI_SINGLE_LINE(Line));
    
    if (Line < 32U)
    {
        if (EXTI->PDR1 & (1UL << Line))
        {
            EXTI->PDR1 = 1UL << Line;
            HAL_EXTI_LineCallback(Line);
        }
    }
    else
    {
        if (EXTI->PDR2 & (1UL << (Line - 32)))
        {
            EXTI->PDR2 = 1UL << (Line - 32);
            HAL_EXTI_LineCallback(Line);
        }
    }
}

/******************************************************************************
*@brief : EXTI interrupt callback.
*@param : Line: Exti line number.
*               This parameter can be a combination of @ref EXTI_Line.
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_EXTI_LineCallback(uint32_t Line)
{
	UNUSED(Line);
}

/******************************************************************************
*@brief : Set configuration of a dedicated Exti line.
*@param : GPIOx: where x can be (A..F) to select the GPIO peripheral.
*                This parameter is only possible for line 0 to 15.
*@param : Line:  Exti line number.
*                This parameter can be a value of @ref EXTI_Line.
*@param : Mode:  The Exit Mode to be configured for a core.
                 This parameter can be a value of @ref EXTI_Mode .
*@return: HAL Status
******************************************************************************/
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(GPIO_TypeDef *GPIOx, uint32_t Line, uint32_t Mode)
{
    uint32_t mask1=0;
    uint32_t mask2=0;
    uint32_t source;
    
    /* Check the parameters */
    assert_param(IS_EXTI_SINGLE_LINE(Line));
    assert_param(IS_EXTI_MODE(Mode));

    /* disable interrupt and event */
	if (Line < 32U)
    {
        mask1 = 1UL << Line;
        EXTI->IENR1  &= ~mask1;
        EXTI->EENR1  &= ~mask1;
        EXTI->RTENR1 &= ~mask1;
        EXTI->FTENR1 &= ~mask1;
        EXTI->PDR1    =  mask1;
    }
    else
    {
        mask2 = 1UL << (Line - 32);
        EXTI->IENR2  &= ~mask2;
        EXTI->EENR2  &= ~mask2;
        EXTI->RTENR2 &= ~mask2;
        EXTI->FTENR2 &= ~mask2;
        EXTI->PDR2    =  mask2;
    }

    /* Line0 ~ 15 trigger from GPIO */
	if (Line < 16U)
	{
        /* Check the parameters */
        assert_param(IS_EXTI_GPIO(GPIOx));
        
        /* Configure EXTI source select */
        source = ((uint32_t)GPIOx - (uint32_t)GPIOA) >> 10;
		
        if (Line < 6U) 
        {
            /* Line0 ~ 5 */
            EXTI->CR1 = (EXTI->CR1 & ~(0x1FUL << (Line * 5))) | (source << (Line * 5));
        }
        else if (Line < 12U) 
        {
            /* Line6 ~ 11 */
            EXTI->CR2 = (EXTI->CR2 & ~(0x1FUL << ((Line - 6) * 5))) | (source << ((Line - 6) * 5));
        }
        else 
        {
            /* Line12 ~ 15 */
            EXTI->CR3 = (EXTI->CR3 & ~(0x1FUL << ((Line - 12) * 5))) | (source << ((Line - 12) * 5));
        }
    }
	
    if (Mode == EXTI_MODE_IT_RISING)
    {
        /* Interrupt rising edge mode */
        if (Line < 32U)
        {
            EXTI->RTENR1 |= mask1;
            EXTI->IENR1  |= mask1;
        }
        else
        {
            EXTI->RTENR2 |= mask2;
            EXTI->IENR2  |= mask2;
        }
    }
    else if (Mode == EXTI_MODE_IT_FALLING)
    {
        /* Interrupt falling edge mode */
        if (Line < 32U)
        {
            EXTI->FTENR1 |= mask1;
            EXTI->IENR1  |= mask1;
        }
        else
        {
            EXTI->FTENR2 |= mask2;
            EXTI->IENR2  |= mask2;
        }
    }
    else if (Mode == EXTI_MODE_IT_RISING_FALLING)
    {
        /* Interrupt rising and falling edge mode */
        if (Line < 32U)
        {
            EXTI->RTENR1 |= mask1;
            EXTI->FTENR1 |= mask1;
            EXTI->IENR1  |= mask1;
        }
        else
        {
            EXTI->RTENR2 |= mask2;
            EXTI->FTENR2 |= mask2;
            EXTI->IENR2  |= mask2;
        }
    }
    else if (Mode == EXTI_MODE_EVT_RISING)
    {
        /* Event rising edge mode */
        if (Line < 32U)
        {
            EXTI->RTENR1 |= mask1;
            EXTI->EENR1  |= mask1;
        }
        else
        {
            EXTI->RTENR2 |= mask2;
            EXTI->EENR2  |= mask2;
        }
    }
    else if (Mode == EXTI_MODE_EVT_FALLING)
    {
        /* Event falling edge mode */
        if (Line < 32U)
        {
            EXTI->FTENR1 |= mask1;
            EXTI->EENR1  |= mask1;
        }
        else
        {
            EXTI->FTENR2 |= mask2;
            EXTI->EENR2  |= mask2;
        }
    }
    else if (Mode == EXTI_MODE_EVT_RISING_FALLING)
    {
        /* Event rising and falling edge mode */
        if (Line < 32U)
        {
            EXTI->RTENR1 |= mask1;
            EXTI->FTENR1 |= mask1;
            EXTI->EENR1  |= mask1;
        }
        else
        {
            EXTI->RTENR2 |= mask2;
            EXTI->FTENR2 |= mask2;
            EXTI->EENR2  |= mask2;
        }
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Clear whole configuration of a dedicated Exti line.
*@param : Line:  Exti line number.
*                This parameter can be a value of @ref EXTI_Line.
*@return: HAL Status
******************************************************************************/
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(uint32_t Line)
{
    uint32_t mask1;
    uint32_t mask2;
    
    /* Check the parameters */
    assert_param(IS_EXTI_SINGLE_LINE(Line));

    /* disable interrupt and event */
	if (Line < 32U)
    {
        mask1 = 1UL << Line;
        EXTI->IENR1  &= ~mask1;
        EXTI->EENR1  &= ~mask1;
        EXTI->RTENR1 &= ~mask1;
        EXTI->FTENR1 &= ~mask1;
        EXTI->PDR1    =  mask1;
    }
    else
    {
        mask2 = 1UL << (Line - 32);
        EXTI->IENR2  &= ~mask2;
        EXTI->EENR2  &= ~mask2;
        EXTI->RTENR2 &= ~mask2;
        EXTI->FTENR2 &= ~mask2;
        EXTI->PDR2    =  mask2;
    }

    /* Line0 ~ 15 trigger from GPIO */
	if (Line < 16U)
	{
        if (Line < 6U) 
        {
            /* Line0 ~ 5 */
            EXTI->CR1 = EXTI->CR1 & ~(0x1FUL << (Line * 5));
        }
        else if (Line < 12U) 
        {
            /* Line6 ~ 11 */
            EXTI->CR2 = EXTI->CR2 & ~(0x1FUL << ((Line - 6) * 5));
        }
        else 
        {
            /* Line12 ~ 15 */
            EXTI->CR3 = EXTI->CR3 & ~(0x1FUL << ((Line - 12) * 5));
        }
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Check whether the LINE of the specified GPIOx is configured.
*@param : GPIOx: where x can be (A..F) to select the GPIO peripheral.
*                This parameter is only possible for line 0 to 15.
*@param : Line:  Exti line number.
*                This parameter can be a value of @ref EXTI_Line.
*@return: configuration status
*         This parameter can be a value of @ref FunctionalState.
*             @arg ENABLE: Configured.
*             @arg DISABLE: Not configured.
******************************************************************************/
FunctionalState HAL_EXTI_IsConfigLine(GPIO_TypeDef *GPIOx, uint32_t Line)
{
    uint32_t mask1;
    uint32_t mask2;
    uint32_t source;
    
    /* Check the parameters */
    assert_param(IS_EXTI_SINGLE_LINE(Line));

	if (Line < 32U)
    {
        mask1 = 1UL << Line;
        if (((EXTI->IENR1 & mask1) == 0) && ((EXTI->EENR1 & mask1) == 0))
            return (DISABLE);
    }
    else
    {
        mask2 = 1UL << (Line - 32);
        if (((EXTI->IENR2 & mask2) == 0) && ((EXTI->EENR2 & mask2) == 0))
            return (DISABLE);
    }
    
	if (Line >= 16U)
    {
        return (ENABLE);
    }
    
    /* Line0 ~ 15 trigger from GPIO */
    
    /* Check the parameters */
    assert_param(IS_EXTI_GPIO(GPIOx));
    
    /* Configure EXTI source select */
    source = (GPIOx - GPIOA) >> 10;
    
    if (Line < 6U) 
    {
        /* Line0 ~ 7 */
        if (((EXTI->CR1 >> (Line * 5)) & 0x1FU) == source)
            return (ENABLE);
        else
            return (DISABLE);
    }
    else if (Line < 12U) 
    {
        /* Line8 ~ 15 */
        if (((EXTI->CR2 >> ((Line - 6) * 5)) & 0x1FU) == source)
            return (ENABLE);
        else
            return (DISABLE);
    }
    else
    {
        /* Line8 ~ 15 */
        if (((EXTI->CR3 >> ((Line - 12) * 5)) & 0x1FU) == source)
            return (ENABLE);
        else
            return (DISABLE);
    }
}

/******************************************************************************
*@brief : The specified Line generates a software interrupt.
*@param : Line:  Exti line number.
*                This parameter can be a combination of @ref EXTI_Line.
*@return: None.
******************************************************************************/
void HAL_EXTI_GenerateSWI(uint32_t Line)
{
    uint32_t mask1;
    uint32_t mask2;
    
    /* Check the parameters */
    assert_param(IS_EXTI_SINGLE_LINE(Line));

	if (Line < 32U)
    {
        mask1 = 1UL << Line;
        EXTI->SWIER1 &= ~mask1;
        EXTI->SWIER1 |=  mask1;
    }
    else
    {
        mask2 = 1UL << (Line - 32);
        EXTI->SWIER2 &= ~mask2;
        EXTI->SWIER2 |=  mask2;
    }
}

/******************************************************************************
*@brief : Get interrupt pending bit of a dedicated line.
*@param : Line:  Exti line number.
*                This parameter can be a value of @ref EXTI_Line.
*@return: interrupt pending bit status
*         This parameter can be a value of @ref FlagStatus.
*             @arg SET: interrupt is pending.
*             @arg RESET: interrupt is not pending.
******************************************************************************/
FlagStatus HAL_EXTI_GetPending(uint32_t Line)
{
    /* Check the parameters */
    assert_param(IS_EXTI_SINGLE_LINE(Line));

	if (Line < 32U)
    {
        if (EXTI->PDR1 & (1UL << Line))
            return (SET);
        else
            return (RESET);
    }
    else
    {
        if (EXTI->PDR2 & (1UL << (Line - 32)))
            return (SET);
        else
            return (RESET);
    }
}

/******************************************************************************
*@brief : Clear interrupt pending bit of a dedicated line.
*@param : Line:  Exti line number.
*                This parameter can be a combination of @ref EXTI_Line.
*@return: None.
******************************************************************************/
void HAL_EXTI_ClearPending(uint32_t Line)
{
    /* Check the parameters */
    assert_param(IS_EXTI_SINGLE_LINE(Line));

	if (Line < 32U)
    {
        EXTI->PDR1 = 1UL << Line;
    }
    else
    {
        EXTI->PDR2 = 1UL << (Line - 32);
    }
}

/******************************************************************************
*@brief : Clear all interrupt pending bit.
*@return: None.
******************************************************************************/
void HAL_EXTI_ClearAllPending(void)
{
    /* Clear pending status */
    EXTI->PDR1 = 0xFFFFFFFF;  
    EXTI->PDR2 = 0x00000007;  
}



#endif /* HAL_EXTI_MODULE_ENABLED */



