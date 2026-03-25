/******************************************************************************
*@file  : hal_gpio.c
*@brief : GPIO HAL module driver.
******************************************************************************/
#include "hal.h" 

#ifdef HAL_GPIO_MODULE_ENABLED

/******************************************************************************
*@brief : Initializes the GPIOx peripheral according to the specified parameters
*         in the GPIO_Init.
*@param : GPIOx: where x can be (A..F) to select the GPIO peripheral.
*@param : GPIO_Init: pointer to an GPIO_InitTypeDef structure that contains 
*         the configuration information for the specified GPIO peripheral.
*@return: None
******************************************************************************/
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t position;
    uint32_t currentPin;
    
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_ALL_PIN(GPIO_Init->Pin));
    assert_param(IS_GPIO_MODE(GPIOx, GPIO_Init->Mode));

    /* Configure Select pins */
    position = 0;
    while ((GPIO_Init->Pin) >> position != 0) 
    {
        /* Get current pin position */
        currentPin = (GPIO_Init->Pin) & (1UL << position);
        
        if (currentPin) 
        {
            if (currentPin & (GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15))
            {
                if (GPIOx == GPIOC)
                {
                    __HAL_RCC_PMU_CLK_ENABLE();
                    if (currentPin & GPIO_PIN_13)
                        PMU->IOSEL &= ~PMU_IOSEL_PC13VALUE;
                    else if (currentPin & GPIO_PIN_14)
                        PMU->IOSEL &= ~PMU_IOSEL_PC14VALUE;
                    else if (currentPin & GPIO_PIN_15)
                        PMU->IOSEL &= ~PMU_IOSEL_PC15VALUE;
                }
            }
            
            /*--------------------- GPIO Mode Configuration ------------------------*/
            if ((GPIO_Init->Mode == GPIO_MODE_ANALOG_SWITCH_OFF) || (GPIO_Init->Mode == GPIO_MODE_ANALOG_SWITCH_ON))
            {
                if (position < 8U) 
                {
                    GPIOx->AF0 &= ~(0xFUL << (position << 2));
                    GPIOx->DS0 &= ~(0xFUL << (position << 2));
                }
                else 
                {
                    GPIOx->AF1 &= ~(0xFUL << ((position - 8) << 2));
                    GPIOx->DS1 &= ~(0xFUL << ((position - 8) << 2));
                }
                GPIOx->OTYP &= ~(1UL << position);
                GPIOx->PUPD &= ~(0x3UL << (position << 1));
                GPIOx->SMIT &= ~(0x01UL << position);
                
                if (GPIO_Init->Mode == GPIO_MODE_ANALOG_SWITCH_OFF)
                    GPIOx->AIEN &= ~(0x01UL << position);
                else
                    GPIOx->AIEN |= 0x01UL << position;
            }
            else
            {
                assert_param(IS_GPIO_PULL(GPIO_Init->Pull));
                
                GPIOx->AIEN &= ~(0x01UL << position);
                
                /* Alternate Function */
                if ((GPIO_Init->Mode == GPIO_MODE_AF_PP) || (GPIO_Init->Mode == GPIO_MODE_AF_OD))
                {
                    /* Check the Alternate function parameters */
                    assert_param(IS_GPIO_FUNCTION(GPIO_Init->Alternate));
           
                    /* Configure Alternate function mapped with the current IO */
                    if (position < 8U) 
                    {
                        GPIOx->AF0 = (GPIOx->AF0 & ~(0xFUL << (position << 2))) | (GPIO_Init->Alternate << (position << 2));
                    }
                    else 
                    {
                        GPIOx->AF1 = (GPIOx->AF1 & ~(0xFUL << ((position - 8) << 2))) | (GPIO_Init->Alternate << ((position - 8) << 2));
                    }
                }
                /* In case of Output or Alternate function mode selection */
                if ((GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP) || (GPIO_Init->Mode == GPIO_MODE_AF_PP) ||
                    (GPIO_Init->Mode == GPIO_MODE_OUTPUT_OD) || (GPIO_Init->Mode == GPIO_MODE_AF_OD))
                {
                    /* Check the drive parameter */
                    assert_param(IS_GPIO_DRIVE(GPIO_Init->Drive));
                    
                    /* Configure the IO drive capability */
                    if (position < 8) 
                    {
                        GPIOx->DS0 = (GPIOx->DS0 & ~(0xFUL << (position << 2))) | (GPIO_Init->Drive << (position << 2));
                    }
                    else
                    {
                        GPIOx->DS1 = (GPIOx->DS1 & ~(0xFUL << ((position - 8) << 2))) | (GPIO_Init->Drive << ((position - 8) << 2));
                    }

                    /* Configure the IO Output Type */
                    GPIOx->OTYP = (GPIOx->OTYP & ~(1UL << position)) | (((GPIO_Init->Mode & GPIO_MODE_GPIO_OUTPUT_TYPE_MASK) >> 4) << position);
                }
                
                /* Activate the Pull-up or Pull down resistor for the current IO */
                GPIOx->PUPD = (GPIOx->PUPD & ~(0x3UL << (position << 1))) | ((GPIO_Init->Pull) << (position << 1));
                
                /* Configure schmitt input */
                GPIOx->SMIT |= 0x01UL << position;
                
            }
            
            /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
            GPIOx->MD = (GPIOx->MD & ~(0x3UL << (position << 1))) | ((GPIO_Init->Mode & GPIO_MODE_GPIO_MASK) << (position << 1));
                
            /*--------------------- EXTI Mode Configuration ------------------------*/
            /* Configure the External Interrupt or event for the current IO */
            if (GPIO_Init->Mode & GPIO_MODE_EXTI_MASK)
            {
                /* Clear EXTI interrupt flag */
				HAL_EXTI_ClearPending(position);
				
                /* Configure the EXTI for the current IO  */
				if (HAL_EXTI_SetConfigLine(GPIOx, position, GPIO_Init->Mode) != HAL_OK)
					return;
			}
			else
			{
                
                /* Check whether the current IO is configured as EXTI */
				if (HAL_EXTI_IsConfigLine(GPIOx, position) != DISABLE)
				{
                    /* Deactivate the EXTI configuration of the current IO */
					HAL_EXTI_ClearConfigLine(position);
                    
                    /* Clear EXTI interrupt flag */
					HAL_EXTI_ClearPending(position);
				}
			}
        }
        position++;
    }
}

/******************************************************************************
*@brief : De-initializes the GPIOx peripheral registers to their default reset values.
*@param : GPIOx: where x can be (A..F) to select the GPIO peripheral.
*@param : GPIO_Pin: specifies the port bit to be written.
*@return: None
******************************************************************************/
void HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
    uint32_t position = 0;
    uint32_t currentPin;
    
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_ALL_PIN(GPIO_Pin));
    
    /* Configure Select pins */
    while (GPIO_Pin >> position != 0U)
    {
        /* Get current pin position */
        currentPin = GPIO_Pin & (1UL << position);
        
        if (currentPin)
        {
            /* SET GPIO Function */
            if (position < 8U)
            {
                GPIOx->AF0 &= ~(0xFU << (position << 2U));
                GPIOx->DS0 &= ~(0xFU << (position << 2U));
            }
            else
            {
                GPIOx->AF1 &= ~(0xFU << ((position - 8U) << 2U));
                GPIOx->DS1 &= ~(0xFU << ((position - 8U) << 2U));
            }

            /* Deactivate the Pull-up and Pull-down resistor for the current IO */
            GPIOx->PUPD &= ~(0x3U << (position << 1U));
            
            /* Configure the default value for output type */
            GPIOx->OTYP &= ~currentPin;
			
            /* Configure the default value for schmitt input */
			GPIOx->SMIT &= ~currentPin;
			
            GPIOx->AIEN &= ~currentPin;
            
            /* Configure IO Direction mode to Analog*/
            GPIOx->MD |= ((0x03U) << (position << 1U));

            /* Check whether the current IO is configured as EXTI */
            if (HAL_EXTI_IsConfigLine(GPIOx, position) != DISABLE)
            {
                /* Deactivate the EXTI configuration of the current IO */
                HAL_EXTI_ClearConfigLine(position);
                
                /* Clear EXTI interrupt flag */
                HAL_EXTI_ClearPending(position);
            }
        }
        position++;
    }
}

/******************************************************************************
*@brief : Set or clear the selected data port bit.
*@param : GPIOx: where x can be (A..F) to select the GPIO peripheral.
*@param : GPIO_Pin: specifies the port bit to be written.
*@param : PinState: specifies the value to be written to the selected bit.
*         This parameter must be a value of @ref GPIO_PinState.
*             @arg GPIO_PIN_RESET: clear the port pin.
*             @arg GPIO_PIN_SET: set the port pin.
*@return: None
******************************************************************************/
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, GPIO_PinState PinState)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_ALL_PIN(GPIO_Pin));
    assert_param(IS_GPIO_PIN_ACTION(PinState));

    if (GPIO_PIN_RESET == PinState) 
    {
        GPIOx->BSC = GPIO_Pin << 16U;
    }
    else 
    {
        GPIOx->BSC = GPIO_Pin;
    }
}

/******************************************************************************
*@brief : Read the specified input port pin.
*@param : GPIOx: where x can be (A..F) to select the GPIO peripheral.
*@param : GPIO_Pin: specifies the port bit to be written.
*@return: The input port pin value.
******************************************************************************/
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_SINGLE_PIN(GPIO_Pin));
    
    if (GPIOx->IDATA & GPIO_Pin) 
    {
        return GPIO_PIN_SET;
    }
    else 
    {
        return GPIO_PIN_RESET;
    }
}

/******************************************************************************
*@brief : Toggle the specified GPIO pin.
*@param : GPIOx: where x can be (A..F) to select the GPIO peripheral.
*@param : GPIO_Pin: specifies the port bit to be written.
*@return: None.
******************************************************************************/
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_ALL_PIN(GPIO_Pin));

    if (GPIOx->ODATA & GPIO_Pin)
    {
        GPIOx->BSC = GPIO_Pin << 16;
    }
    else
    {
        GPIOx->BSC = GPIO_Pin;
    }
}

/******************************************************************************
*@brief : Lock GPIO Pins configuration registers.
*@param : GPIOx: where x can be (A..F) to select the GPIO peripheral.
*@param : GPIO_Pin: specifies the port bit to be written.
*@return: HAL Status.
******************************************************************************/
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
    __IO uint32_t temp = GPIO_LOCK_LOCK_KEY;
    
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_ALL_PIN(GPIO_Pin));

    /* Apply lock key write sequence */
    temp |= GPIO_Pin;
    
    /* Set LOCKx bit(s): LOCKK='1' + LOCK[15-0] */
    GPIOx->LOCK = temp;
    
    /* Reset LOCKx bit(s): LOCKK='0' + LOCK[15-0] */
    GPIOx->LOCK = GPIO_Pin;
    
    /* Set LOCKx bit(s): LOCKK='1' + LOCK[15-0] */
    GPIOx->LOCK = temp;
    
    /* Read LOCK register. This read is mandatory to complete key lock sequence */
    temp = GPIOx->LOCK;

    /* read again in order to confirm lock is active */
    if (GPIOx->LOCK & GPIO_LOCK_LOCK_KEY)
        return HAL_OK;
    else
        return HAL_ERROR;
}

#endif /* HAL_GPIO_MODULE_ENABLED */


