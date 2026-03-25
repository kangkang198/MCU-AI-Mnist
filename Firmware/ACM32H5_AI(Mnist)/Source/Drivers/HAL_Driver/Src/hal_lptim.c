
/******************************************************************************
*@file  : hal_lptim.c
*@brief : LPTIM HAL module driver.
******************************************************************************/

#include "hal.h" 

#ifdef HAL_LPTIM_MODULE_ENABLED


static HAL_StatusTypeDef LPTIM_WaitForFlag(LPTIM_HandleTypeDef *hlptim, uint32_t flag);
static HAL_StatusTypeDef HAL_LPTIM_Disable(LPTIM_HandleTypeDef *hlptim);

/******************************************************************************
*@brief : Handle LPTIM interrupt request.
*@param : hlptim: LPTIM handle.
*@return: None
******************************************************************************/
void HAL_LPTIM_IRQHandler(LPTIM_HandleTypeDef *hlptim)
{
    /* Compare match interrupt */
    if (__HAL_LPTIM_GET_IT_SOURCE(hlptim, LPTIM_IT_CMPM))
    {
        if (__HAL_LPTIM_GET_FLAG(hlptim, LPTIM_FLAG_CMPM))
        {
            /* Clear Compare match flag */
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_CMPM);

            if (hlptim->CompareMatchCallback)
            {
                hlptim->CompareMatchCallback(hlptim);
            }
            return;
        }
    }

    /* Autoreload match interrupt */
    if (__HAL_LPTIM_GET_IT_SOURCE(hlptim, LPTIM_IT_ARRM))
    {
        if (__HAL_LPTIM_GET_FLAG(hlptim, LPTIM_FLAG_ARRM))
        {
            /* Clear Autoreload match flag */
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_ARRM);

            if (hlptim->AutoReloadMatchCallback)
            {
                hlptim->AutoReloadMatchCallback(hlptim);
            }
            return;
        }
    }

    /* Repetition Counter update event interrupt */
    if (__HAL_LPTIM_GET_IT_SOURCE(hlptim, LPTIM_IT_REPUE))
    {
        if (__HAL_LPTIM_GET_FLAG(hlptim, LPTIM_FLAG_REPUE))
        {
            /* Clear Autoreload match flag */
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_REPUE);

            if (hlptim->RepetitionUpdateCallback)
            {
                hlptim->RepetitionUpdateCallback(hlptim);
            }
            return;
        }
    }

    /* Direction counter changed from Down to Up interrupt */
    if (__HAL_LPTIM_GET_IT_SOURCE(hlptim, LPTIM_IT_UP))
    {
        if (__HAL_LPTIM_GET_FLAG(hlptim, LPTIM_FLAG_UP))
        {
            /* Clear Direction counter changed from Down to Up flag */
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_UP);

            if (hlptim->DirectionUpCallback)
            {
                hlptim->DirectionUpCallback(hlptim);
            }
            return;
        }
    }

    /* Direction counter changed from Up to Down interrupt */
    if (__HAL_LPTIM_GET_IT_SOURCE(hlptim, LPTIM_IT_DOWN))
    {
        if (__HAL_LPTIM_GET_FLAG(hlptim, LPTIM_FLAG_DOWN))
        {
            /* Clear Direction counter changed from Up to Down flag */
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_DOWN);

            if (hlptim->DirectionDownCallback)
            {
                hlptim->DirectionDownCallback(hlptim);
            }
            return;
        }
    }

    /* Trigger detected interrupt */
    if (__HAL_LPTIM_GET_IT_SOURCE(hlptim, LPTIM_IT_EXTTRIG))
    {
        if (__HAL_LPTIM_GET_FLAG(hlptim, LPTIM_FLAG_EXTTRIG))
        {
            /* Clear Trigger detected flag */
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_EXTTRIG);

            if (hlptim->TriggerCallback)
            {
                hlptim->TriggerCallback(hlptim);
            }
            return;
        }
    }

    /* Compare write interrupt */
    if (__HAL_LPTIM_GET_IT_SOURCE(hlptim, LPTIM_IT_CMPOK))
    {
        if (__HAL_LPTIM_GET_FLAG(hlptim, LPTIM_FLAG_CMPOK))
        {
            /* Clear Compare write flag */
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_CMPOK);

            if (hlptim->CompareWriteCallback)
            {
                hlptim->CompareWriteCallback(hlptim);
            }
            return;
        }
    }

    /* Autoreload write interrupt */
    if (__HAL_LPTIM_GET_IT_SOURCE(hlptim, LPTIM_IT_ARROK))
    {
        if (__HAL_LPTIM_GET_FLAG(hlptim, LPTIM_FLAG_ARROK))
        {
            /* Clear Autoreload write flag */
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_ARROK);

            if (hlptim->AutoReloadWriteCallback)
            {
                hlptim->AutoReloadWriteCallback(hlptim);
            }
            return;
        }
    }

    /* Repetition Counter write interrupt */
    if (__HAL_LPTIM_GET_IT_SOURCE(hlptim, LPTIM_IT_REPOK))
    {
        if (__HAL_LPTIM_GET_FLAG(hlptim, LPTIM_FLAG_REPOK))
        {
            /* Clear Autoreload write flag */
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_REPOK);

            if (hlptim->RepetitionWriteCallback)
            {
                hlptim->RepetitionWriteCallback(hlptim);
            }
            return;
        }
    }

}

/******************************************************************************
*@brief : Initialize the LPTIM according to the specified parameters in the
*         LPTIM_InitTypeDef and initialize the associated handle.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_Init(LPTIM_HandleTypeDef *hlptim)
{
    uint32_t temp;

    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

    assert_param(IS_LPTIM_CLOCK_SOURCE(hlptim->Init.ClockSource));
    assert_param(IS_LPTIM_CLOCK_PRESCALER(hlptim->Init.ClockPrescaler));
    assert_param(IS_LPTIM_TRIG_SOURCE(hlptim->Init.TriggerSource));;
    assert_param(IS_LPTIM_UPDATE_MODE(hlptim->Init.UpdateMode));
    assert_param(IS_LPTIM_WAVEFORM_POLARITY(hlptim->Init.WaveformPolarity));
    
    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_LPTIM_MspInit(hlptim);

    /* LPTIM Reset */
	{
		if (hlptim->Instance == LPTIM1)
		{
			__HAL_RCC_LPTIM1_RESET();
		}
		else if(hlptim->Instance == LPTIM2)
		{
			__HAL_RCC_LPTIM2_RESET();
		}
		else if(hlptim->Instance == LPTIM3)
		{
			__HAL_RCC_LPTIM3_RESET();
		}
		else if(hlptim->Instance == LPTIM4)
		{
			__HAL_RCC_LPTIM4_RESET();
		}
		else if(hlptim->Instance == LPTIM5)
		{
			__HAL_RCC_LPTIM5_RESET();
		}
		else if(hlptim->Instance == LPTIM6)
		{
			__HAL_RCC_LPTIM6_RESET();
		}
	}

    
    /* Set initialization parameters */
    temp = hlptim->Init.ClockPrescaler | hlptim->Init.WaveformPolarity | hlptim->Init.UpdateMode;

    if (hlptim->Init.TriggerSource != LPTIM_TRIGSOURCE_SOFTWARE)
        temp |= hlptim->Init.TriggerSource;
    
    /* Configure internal clock source, counter source */
    if (hlptim->Init.ClockSource != LPTIM_CLOCKSOURCE_EXTERNAL_INPUT1)
    {
        assert_param(IS_LPTIM_COUNTER_SOURCE(hlptim->Init.CounterSource));
        
        /* Configure LPTIM internal clock sources */
		{
			if (hlptim->Instance == LPTIM1)
			{
				if (HAL_RCC_LPTIM1ClockSourceConfig(hlptim->Init.ClockSource) != HAL_OK)
					return HAL_ERROR;
			}
			else if(hlptim->Instance == LPTIM2)
			{
				if (HAL_RCC_LPTIM2ClockSourceConfig(hlptim->Init.ClockSource) != HAL_OK)
					return HAL_ERROR;
			}
			else if(hlptim->Instance == LPTIM3)
			{
				if (HAL_RCC_LPTIM3ClockSourceConfig(hlptim->Init.ClockSource) != HAL_OK)
					return HAL_ERROR;
			}
            else if(hlptim->Instance == LPTIM4)
			{
				if (HAL_RCC_LPTIM4ClockSourceConfig(hlptim->Init.ClockSource) != HAL_OK)
					return HAL_ERROR;
			}
            else if(hlptim->Instance == LPTIM5)
			{
				if (HAL_RCC_LPTIM5ClockSourceConfig(hlptim->Init.ClockSource) != HAL_OK)
					return HAL_ERROR;
			}
            else if(hlptim->Instance == LPTIM6)
			{
				if (HAL_RCC_LPTIM6ClockSourceConfig(hlptim->Init.ClockSource) != HAL_OK)
					return HAL_ERROR;
			}
		}
        
        /* Configure counter source */
        temp |= hlptim->Init.CounterSource;
        
        /* Configure counter polarity and counter filtering, if external counter source is selected */
        if (hlptim->Init.CounterSource == LPTIM_COUNTERSOURCE_EXTERNAL)
        {
            assert_param(IS_LPTIM_COUNTER_POLARITY(hlptim->Init.CounterPolarity));
            assert_param(IS_LPTIM_COUNTER_FILTER(hlptim->Init.CounterFilter));
            
            temp |= hlptim->Init.CounterPolarity | hlptim->Init.CounterFilter;
            
            /* Configure LPTIM input1 sources */
//            if (hlptim->Instance == LPTIM1)
//            {
                assert_param(IS_LPTIM_INPUT1_SOURCE(hlptim->Init.Input1Source));

                /* Configure LPTIM Input1 sources */
                hlptim->Instance->CFGR2 |= hlptim->Init.Input1Source;
//            }
        }
        
        /* Configure trigger polarity and trigger filtering, if external trigger source is selected */
        if (hlptim->Init.TriggerSource != LPTIM_TRIGSOURCE_SOFTWARE)
        {
            assert_param(IS_LPTIM_TRIG_POLARITY(hlptim->Init.TriggerPolarity));
            assert_param(IS_LPTIM_TRIG_FILTER(hlptim->Init.TriggerFilter));
            
            temp |= hlptim->Init.TriggerPolarity | hlptim->Init.TriggerFilter;
        }
    }
    else
    {
        assert_param((hlptim->Init.CounterPolarity == LPTIM_COUNTERPOLARITY_RISING) || \
                     (hlptim->Init.CounterPolarity == LPTIM_COUNTERPOLARITY_FALLING));
        assert_param(IS_LPTIM_INPUT1_SOURCE(hlptim->Init.Input1Source));
        
        /* Configure external clock source and counter polarity */
//        temp |= hlptim->Init.ClockSource | hlptim->Init.CounterPolarity;
		temp |= LPTIM_CFGR1_CKSEL | hlptim->Init.CounterPolarity;
        
        /* Configure trigger polarity and trigger filtering, if external trigger source is selected */
        if (hlptim->Init.TriggerSource != LPTIM_TRIGSOURCE_SOFTWARE)
        {
            assert_param(IS_LPTIM_TRIG_POLARITY(hlptim->Init.TriggerPolarity));
            
            temp |= hlptim->Init.TriggerPolarity;
        }
        
        /* Configure LPTIM input sources */
//        if (hlptim->Instance == LPTIM1)
//        {
            /* Configure LPTIM Input1 sources */
            hlptim->Instance->CFGR2 |= hlptim->Init.Input1Source;
//        }
    }
    
    hlptim->RepetitionCounter   = 0U;
    hlptim->AutoReload          = 1U;
    hlptim->Compare             = 0U;
    
    /* Write to LPTIMx CFGR1 */
    hlptim->Instance->CFGR1 = temp;

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : DeInitialize the LPTIM peripheral.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_DeInit(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

    /* LPTIM Reset */
	if (hlptim->Instance == LPTIM1)
	{
		__HAL_RCC_LPTIM1_RESET();
	}
	else if(hlptim->Instance == LPTIM2)
	{
		__HAL_RCC_LPTIM2_RESET();
	}
	else if(hlptim->Instance == LPTIM3)
	{
		__HAL_RCC_LPTIM3_RESET();
	}
	else if(hlptim->Instance == LPTIM4)
	{
		__HAL_RCC_LPTIM4_RESET();
	}
	else if(hlptim->Instance == LPTIM5)
	{
		__HAL_RCC_LPTIM5_RESET();
	}
	else if(hlptim->Instance == LPTIM6)
	{
		__HAL_RCC_LPTIM6_RESET();
	}

    /* DeInit the low level hardware: CLOCK, NVIC.*/
    HAL_LPTIM_MspDeInit(hlptim);

    hlptim->RepetitionCounter           = 0U;
    hlptim->AutoReload                  = 1U;
    hlptim->Compare                     = 0U;
    
    hlptim->CompareMatchCallback        = NULL;
    hlptim->AutoReloadMatchCallback     = NULL;
    hlptim->TriggerCallback             = NULL;
    hlptim->CompareWriteCallback        = NULL;
    hlptim->AutoReloadWriteCallback     = NULL;
    hlptim->DirectionUpCallback         = NULL;
    hlptim->DirectionDownCallback       = NULL;
    hlptim->RepetitionUpdateCallback    = NULL;
    hlptim->RepetitionWriteCallback     = NULL;
    
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Initialize the LPTIM MSP.
*@param : hlpuart: pointer to a LPTIM_HandleTypeDef structure that contains
*                  the configuration information for LPTIM module.
*@return: None
******************************************************************************/
__weak void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef *hlptim)
{
    UNUSED(hlptim);
}

/******************************************************************************
*@brief : DeInitialize the LPTIM MSP.
*@param : hlpuart: pointer to a LPTIM_HandleTypeDef structure that contains
*                  the configuration information for LPTIM module.
*@return: None
******************************************************************************/
__weak void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef *hlptim)
{
    UNUSED(hlptim);
}

/******************************************************************************
*@brief : Configure Count Value.
*@param : hlptim: LPTIM handle.
*@param : RepetitionCounter: Specifies the Repetition counter value.
*         This parameter must be a value between 0x00 and 0xFF.
*@param : Period: Specifies the Autoreload value.
*         This parameter must be a value between 0x0000 and 0xFFFF.
*@param : PulseOrTimeout: Specifies the compare value.
*         This parameter must be a value between 0x0000 and 0xFFFF.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_ConfigCountValue(LPTIM_HandleTypeDef *hlptim, uint8_t RepetitionCounter, \
                                             uint16_t Period, uint16_t PulseOrTimeout)
{
    /* Check the LPTIM handle allocation */
    if ((hlptim == NULL) || (PulseOrTimeout >= Period))
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    assert_param(IS_LPTIM_REPETITION_COUNTER(RepetitionCounter));
    assert_param(IS_LPTIM_PERIOD(Period));
    assert_param(IS_LPTIM_PULSE(PulseOrTimeout));

    hlptim->RepetitionCounter   = RepetitionCounter;
    hlptim->AutoReload          = Period;
    hlptim->Compare             = PulseOrTimeout;
    
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Enable interrupt.
*@param : hlptim: LPTIM handle.
*@param : IT: interrupt.
*             This parameter can be a combination of @ref LPTIM_IT.
*             @arg LPTIM_IT_REPOK:  Repetition counter write complete interrupt.
*             @arg LPTIM_IT_REPUE:  Repetition counter update event interrupt
*             @arg LPTIM_IT_ARROK:  Autoreload write complete interrupt
*             @arg LPTIM_IT_ARRM:   Autoreload match interrupt
*             @arg LPTIM_IT_CMPOK:  Compare write complete interrupt
*             @arg LPTIM_IT_CMPM:   Compare match interrupt
*             @arg LPTIM_IT_EXTTRIG:External trigger interrupt
*             @arg LPTIM_IT_DOWN:   "switch to down direction" interrupt
*             @arg LPTIM_IT_UP:     "switch to up direction" interrupt
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_EnableIT(LPTIM_HandleTypeDef *hlptim, uint32_t IT)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    assert_param(IS_LPTIM_IT(IT));

    __HAL_LPTIM_ENABLE_IT(hlptim, IT);
    
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Disable interrupt.
*@param : hlptim: LPTIM handle.
*@param : IT: interrupt.
*             This parameter can be a combination of @ref LPTIM_IT.
*             @arg LPTIM_IT_REPOK:  Repetition counter write complete interrupt.
*             @arg LPTIM_IT_REPUE:  Repetition counter update event interrupt
*             @arg LPTIM_IT_ARROK:  Autoreload write complete interrupt
*             @arg LPTIM_IT_ARRM:   Autoreload match interrupt
*             @arg LPTIM_IT_CMPOK:  Compare write complete interrupt
*             @arg LPTIM_IT_CMPM:   Compare match interrupt
*             @arg LPTIM_IT_EXTTRIG:External trigger interrupt
*             @arg LPTIM_IT_DOWN:   "switch to down direction" interrupt
*             @arg LPTIM_IT_UP:     "switch to up direction" interrupt
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_DisableIT(LPTIM_HandleTypeDef *hlptim, uint32_t IT)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    assert_param(IS_LPTIM_IT(IT));

    __HAL_LPTIM_DISABLE_IT(hlptim, IT);
    
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Start the LPTIM PWM generation.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_PWM_Start(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    assert_param(IS_LPTIM_REPETITION_COUNTER(hlptim->RepetitionCounter));
    assert_param(IS_LPTIM_PERIOD(hlptim->AutoReload));
    assert_param(IS_LPTIM_PULSE(hlptim->Compare));

    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Reset WAVE bit to set PWM mode */
    hlptim->Instance->CFGR1 &= ~LPTIM_CFGR1_WAVE;

    /* Enable the Peripheral */
    __HAL_LPTIM_ENABLE(hlptim);

    /* Start timer in continuous mode */
    __HAL_LPTIM_START_CONTINUOUS(hlptim);

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Stop the LPTIM PWM generation.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_PWM_Stop(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Start the LPTIM One pulse generation.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Start(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    assert_param(IS_LPTIM_REPETITION_COUNTER(hlptim->RepetitionCounter));
    assert_param(IS_LPTIM_PERIOD(hlptim->AutoReload));
    assert_param(IS_LPTIM_PULSE(hlptim->Compare));

    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Reset WAVE bit to set one pulse mode */
    hlptim->Instance->CFGR1 &= ~LPTIM_CFGR1_WAVE;

    /* Enable the Peripheral */
    __HAL_LPTIM_ENABLE(hlptim);

    /* Start timer in single (one shot) mode */
    __HAL_LPTIM_START_SINGLE(hlptim);

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Stop the LPTIM One pulse generation.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_OnePulse_Stop(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Start the LPTIM in Set once mode.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Start(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    assert_param(IS_LPTIM_REPETITION_COUNTER(hlptim->RepetitionCounter));
    assert_param(IS_LPTIM_PERIOD(hlptim->AutoReload));
    assert_param(IS_LPTIM_PULSE(hlptim->Compare));

    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Set WAVE bit to enable the set once mode */
    hlptim->Instance->CFGR1 |= LPTIM_CFGR1_WAVE;

    /* Enable the Peripheral */
    __HAL_LPTIM_ENABLE(hlptim);

    /* Start timer in single (one shot) mode */
    __HAL_LPTIM_START_SINGLE(hlptim);

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Stop the LPTIM Set once mode.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_SetOnce_Stop(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Start the Encoder interface.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_Encoder_Start(LPTIM_HandleTypeDef *hlptim)
{
    uint32_t temp;

    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    assert_param(IS_LPTIM_PERIOD(hlptim->AutoReload));
    assert_param(hlptim->Init.ClockSource != LPTIM_CLOCKSOURCE_EXTERNAL_INPUT1);
    assert_param(hlptim->Init.CounterSource == LPTIM_COUNTERSOURCE_EXTERNAL);
    assert_param(IS_LPTIM_INPUT2_SOURCE(hlptim->Init.Input2Source));
    
    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Get the LPTIMx CFGR2 value */
    temp = hlptim->Instance->CFGR2;

    /* Clear CKPOL bits */
    temp &= (uint32_t)(~LPTIM_CFGR2_IN2SEL_Msk);

    /* Set Input polarity */
    temp |=  hlptim->Init.Input2Source;

    /* Write to LPTIMx CFGR */
    hlptim->Instance->CFGR2 = temp;

    /* Set ENC bit to enable the encoder interface */
    hlptim->Instance->CFGR1 |= LPTIM_CFGR1_ENC;

    /* Enable the Peripheral */
    __HAL_LPTIM_ENABLE(hlptim);

    /* Start timer in continuous mode */
    __HAL_LPTIM_START_CONTINUOUS(hlptim);

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Stop the Encoder interface.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_Encoder_Stop(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    
    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Reset ENC bit to disable the encoder interface */
    hlptim->Instance->CFGR1 &= ~LPTIM_CFGR1_ENC;

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Start the Timeout function.
* @note   The first trigger event will start the timer, any successive
*         trigger event will reset the counter and the timer restarts.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_Timeout_Start(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    assert_param(IS_LPTIM_PERIOD(hlptim->AutoReload));
    assert_param(IS_LPTIM_PULSE(hlptim->Compare));

    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Set TIMOUT bit to enable the timeout function */
    hlptim->Instance->CFGR1 |= LPTIM_CFGR1_TIMEOUT;

    /* Enable the Peripheral */
    __HAL_LPTIM_ENABLE(hlptim);

    /* Start timer in continuous mode */
    __HAL_LPTIM_START_CONTINUOUS(hlptim);

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Stop the Timeout function.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_Timeout_Stop(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    
    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Reset TIMOUT bit to enable the timeout function */
    hlptim->Instance->CFGR1 &= ~LPTIM_CFGR1_TIMEOUT;

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Start the Counter mode.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_Counter_Start(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));
    assert_param(IS_LPTIM_PERIOD(hlptim->AutoReload));
    assert_param(IS_LPTIM_PULSE(hlptim->Compare));

    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Enable the Peripheral */
    __HAL_LPTIM_ENABLE(hlptim);

    /* Start timer in continuous mode */
    __HAL_LPTIM_START_CONTINUOUS(hlptim);

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Stop the Counter mode.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_Counter_Stop(LPTIM_HandleTypeDef *hlptim)
{
    /* Check the LPTIM handle allocation */
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

    /* Disable LPTIM */
    if (HAL_LPTIM_Disable(hlptim) != HAL_OK)
        return HAL_ERROR;
    
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
*@brief : Register a User LPTIM callback to be used instead of the weak predefined callback
*@param : hlptim: LPTIM handle.
*@param : CallbackID: ID of the callback to be registered
*                     This parameter can be a combination of @ref LPTIM_CallbackID.
*                     @arg @ref LPTIM_CALLBACKID_COMPARE_MATCH     :  Compare match Callback ID
*                     @arg @ref LPTIM_CALLBACKID_AUTORELOAD_MATCH  :  Auto-reload match Callback ID
*                     @arg @ref LPTIM_CALLBACKID_TRIGGER           :  External trigger event detection Callback ID
*                     @arg @ref LPTIM_CALLBACKID_COMPARE_WRITE     :  Compare register write complete Callback ID
*                     @arg @ref LPTIM_CALLBACKID_AUTORELOAD_WRITE  :  Auto-reload register write complete Callback ID
*                     @arg @ref LPTIM_CALLBACKID_DIRECTION_UP      :  Up-counting direction change Callback ID
*                     @arg @ref LPTIM_CALLBACKID_DIRECTION_DOWN    :  Down-counting direction change Callback ID
*                     @arg @ref LPTIM_CALLBACKID_REPETITION_UPDATE :  Repetition counter update event Callback ID
*                     @arg @ref LPTIM_CALLBACKID_REPETITION_WRITE  :  Repetition counter write complete Callback ID
*@param : pCallback pointer to the callback function
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_RegisterCallback(LPTIM_HandleTypeDef *hlptim,
                                             uint32_t CallbackID,
                                             pLPTIM_CallbackTypeDef pCallback)
{
    if ((hlptim == NULL) || (pCallback == NULL))
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

    switch (CallbackID)
    {
        case LPTIM_CALLBACKID_COMPARE_MATCH :
            
            hlptim->CompareMatchCallback = pCallback;
            break;

        case LPTIM_CALLBACKID_AUTORELOAD_MATCH :
            
            hlptim->AutoReloadMatchCallback = pCallback;
            break;

        case LPTIM_CALLBACKID_TRIGGER :
            
            hlptim->TriggerCallback = pCallback;
            break;

        case LPTIM_CALLBACKID_COMPARE_WRITE :
            
            hlptim->CompareWriteCallback = pCallback;
            break;

        case LPTIM_CALLBACKID_AUTORELOAD_WRITE :
            
            hlptim->AutoReloadWriteCallback = pCallback;
            break;

        case LPTIM_CALLBACKID_DIRECTION_UP :
            
            hlptim->DirectionUpCallback = pCallback;
            break;

        case LPTIM_CALLBACKID_DIRECTION_DOWN :
            
            hlptim->DirectionDownCallback = pCallback;
            break;

        case LPTIM_CALLBACKID_REPETITION_UPDATE :
            
            hlptim->RepetitionUpdateCallback = pCallback;
            break;

        case LPTIM_CALLBACKID_REPETITION_WRITE :
            
            hlptim->RepetitionWriteCallback = pCallback;
            break;

        default :
            
            return HAL_ERROR;
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Unregister a LPTIM callback
*@param : hlptim: LPTIM handle.
*@param : CallbackID: ID of the callback to be registered
*                     This parameter can be a combination of @ref LPTIM_CallbackID.
*                     @arg @ref LPTIM_CALLBACKID_COMPARE_MATCH     :  Compare match Callback ID
*                     @arg @ref LPTIM_CALLBACKID_AUTORELOAD_MATCH  :  Auto-reload match Callback ID
*                     @arg @ref LPTIM_CALLBACKID_TRIGGER           :  External trigger event detection Callback ID
*                     @arg @ref LPTIM_CALLBACKID_COMPARE_WRITE     :  Compare register write complete Callback ID
*                     @arg @ref LPTIM_CALLBACKID_AUTORELOAD_WRITE  :  Auto-reload register write complete Callback ID
*                     @arg @ref LPTIM_CALLBACKID_DIRECTION_UP      :  Up-counting direction change Callback ID
*                     @arg @ref LPTIM_CALLBACKID_DIRECTION_DOWN    :  Down-counting direction change Callback ID
*                     @arg @ref LPTIM_CALLBACKID_REPETITION_UPDATE :  Repetition counter update event Callback ID
*                     @arg @ref LPTIM_CALLBACKID_REPETITION_WRITE  :  Repetition counter write complete Callback ID
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPTIM_UnRegisterCallback(LPTIM_HandleTypeDef *hlptim,
                                               uint32_t CallbackID)
{
    if (hlptim == NULL)
        return HAL_ERROR;

    /* Check the parameters */
    assert_param(IS_LPTIM_INSTANCE(hlptim->Instance));

    switch (CallbackID)
    {
        case LPTIM_CALLBACKID_COMPARE_MATCH :
            
            hlptim->CompareMatchCallback = NULL;
            break;

        case LPTIM_CALLBACKID_AUTORELOAD_MATCH :
            
            hlptim->AutoReloadMatchCallback = NULL;
            break;

        case LPTIM_CALLBACKID_TRIGGER :
            
            hlptim->TriggerCallback = NULL;
            break;

        case LPTIM_CALLBACKID_COMPARE_WRITE :
            
            hlptim->CompareWriteCallback = NULL;
            break;

        case LPTIM_CALLBACKID_AUTORELOAD_WRITE :
            
            hlptim->AutoReloadWriteCallback = NULL;
            break;

        case LPTIM_CALLBACKID_DIRECTION_UP :
            
            hlptim->DirectionUpCallback = NULL;
            break;

        case LPTIM_CALLBACKID_DIRECTION_DOWN :
            
            hlptim->DirectionDownCallback = NULL;
            break;

        case LPTIM_CALLBACKID_REPETITION_UPDATE :
            
            hlptim->RepetitionUpdateCallback = NULL;
            break;

        case LPTIM_CALLBACKID_REPETITION_WRITE :
            
            hlptim->RepetitionWriteCallback = NULL;
            break;

        default :   
			
            return HAL_ERROR;
    }
    return HAL_OK;
}

/* Private functions ---------------------------------------------------------*/

/** @defgroup LPTIM_Private_Functions LPTIM Private Functions
  * @{
  */

/******************************************************************************
*@brief : LPTimer Wait for flag set
*@param : hlptim: LPTIM handle.
*@param : flag: The lptim flag.
*@return: HAL status
******************************************************************************/
static HAL_StatusTypeDef LPTIM_WaitForFlag(LPTIM_HandleTypeDef *hlptim, uint32_t flag)
{
    uint32_t count = 120000000U;
    
    while (count--)
    {
        if (__HAL_LPTIM_GET_FLAG(hlptim, flag))
            return HAL_OK;
    }

    return HAL_TIMEOUT;
}

/******************************************************************************
*@brief : Disable LPTIM HW instance.
*@param : hlptim: LPTIM handle.
*@return: HAL status
******************************************************************************/
static HAL_StatusTypeDef HAL_LPTIM_Disable(LPTIM_HandleTypeDef *hlptim)
{
    uint32_t tmpclksource = 0;
    uint32_t tmpIER;
    uint32_t tmpCFGR1;
    uint32_t tmpCFGR2;

//    __disable_irq();

    /* Save LPTIM source clock */
	{
	if (hlptim->Instance == LPTIM1)
	{
        if (HAL_RCC_GetLPTIM1ClockSource(&tmpclksource) != HAL_OK)
            return HAL_ERROR;
	}
	else if(hlptim->Instance == LPTIM2)
	{
        if (HAL_RCC_GetLPTIM2ClockSource(&tmpclksource) != HAL_OK)
            return HAL_ERROR;
	}
	else if(hlptim->Instance == LPTIM6)
	{
        if (HAL_RCC_GetLPTIM6ClockSource(&tmpclksource) != HAL_OK)
            return HAL_ERROR;
	}
	else if(hlptim->Instance == LPTIM3)
	{
        if (HAL_RCC_GetLPTIM3ClockSource(&tmpclksource) != HAL_OK)
            return HAL_ERROR;
	}
	else if(hlptim->Instance == LPTIM4)
	{
        if (HAL_RCC_GetLPTIM4ClockSource(&tmpclksource) != HAL_OK)
            return HAL_ERROR;
	}
	else if(hlptim->Instance == LPTIM5)
	{
        if (HAL_RCC_GetLPTIM5ClockSource(&tmpclksource) != HAL_OK)
            return HAL_ERROR;
	}
    else
    {
        return HAL_ERROR;
    }
	}


    /* Save LPTIM configuration registers */
    tmpIER = hlptim->Instance->IER;
    tmpCFGR1 = hlptim->Instance->CFGR1;
    tmpCFGR2 = hlptim->Instance->CFGR2;

    /*********** Reset LPTIM ***********/
    /* LPTIM Reset */
	{
	if (hlptim->Instance == LPTIM1)
	{
		__HAL_RCC_LPTIM1_RESET();
	}
	else if(hlptim->Instance == LPTIM2)
	{
		__HAL_RCC_LPTIM2_RESET();
	}
	else if(hlptim->Instance == LPTIM3)
	{
		__HAL_RCC_LPTIM3_RESET();
	}
	else if(hlptim->Instance == LPTIM4)
	{
		__HAL_RCC_LPTIM4_RESET();
	}
	else if(hlptim->Instance == LPTIM5)
	{
		__HAL_RCC_LPTIM5_RESET();
	}
	else if(hlptim->Instance == LPTIM6)
	{
		__HAL_RCC_LPTIM6_RESET();
	}
	}
    /*********** Restore LPTIM Config ***********/
    
    if ((hlptim->RepetitionCounter != 0UL) || (hlptim->AutoReload != 1UL) || (hlptim->Compare != 0U))
    {
        /* Force LPTIM source kernel clock from PCLK */
		if (hlptim->Instance == LPTIM1)
		{
            HAL_RCC_LPTIM1ClockSourceConfig(LPTIM_CLOCKSOURCE_INTERNAL_PCLK);
		}
		else if(hlptim->Instance == LPTIM2)
		{
            HAL_RCC_LPTIM2ClockSourceConfig(LPTIM_CLOCKSOURCE_INTERNAL_PCLK);
		}
		else if(hlptim->Instance == LPTIM3)
		{
            HAL_RCC_LPTIM3ClockSourceConfig(LPTIM_CLOCKSOURCE_INTERNAL_PCLK);
		}
        else if(hlptim->Instance == LPTIM4)
		{
            HAL_RCC_LPTIM4ClockSourceConfig(LPTIM_CLOCKSOURCE_INTERNAL_PCLK);
		}
        else if(hlptim->Instance == LPTIM5)
		{
            HAL_RCC_LPTIM5ClockSourceConfig(LPTIM_CLOCKSOURCE_INTERNAL_PCLK);
		}
        else if(hlptim->Instance == LPTIM6)
		{
            HAL_RCC_LPTIM6ClockSourceConfig(LPTIM_CLOCKSOURCE_INTERNAL_PCLK);
		}

        
        hlptim->Instance->CR |= LPTIM_CR_ENABLE;

        if (hlptim->RepetitionCounter != 0UL)
        {
            hlptim->Instance->RCR = hlptim->RepetitionCounter;

            if (LPTIM_WaitForFlag(hlptim, LPTIM_FLAG_REPOK) != HAL_OK)
                return HAL_TIMEOUT;
            
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_REPOK);
        }

        if (hlptim->AutoReload != 0UL)
        {
            hlptim->Instance->ARR = hlptim->AutoReload;

            if (LPTIM_WaitForFlag(hlptim, LPTIM_FLAG_ARROK) != HAL_OK)
                return HAL_TIMEOUT;
            
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_ARROK);
        }

        if (hlptim->Compare != 0UL)
        {
            hlptim->Instance->CMP = hlptim->Compare;

            if (LPTIM_WaitForFlag(hlptim, LPTIM_FLAG_CMPOK) != HAL_OK)
                return HAL_TIMEOUT;
            
            __HAL_LPTIM_CLEAR_FLAG(hlptim, LPTIM_FLAG_CMPOK);
        }

        hlptim->Instance->CR &= ~(LPTIM_CR_ENABLE);
        
        /* Restore LPTIM source kernel clock */
		if (hlptim->Instance == LPTIM1)
		{
            HAL_RCC_LPTIM1ClockSourceConfig(tmpclksource);
		}
		else if(hlptim->Instance == LPTIM2)
		{
            HAL_RCC_LPTIM2ClockSourceConfig(tmpclksource);
		}
		else if(hlptim->Instance == LPTIM3)
		{
            HAL_RCC_LPTIM5ClockSourceConfig(tmpclksource);
		}
        else if(hlptim->Instance == LPTIM4)
		{
            HAL_RCC_LPTIM4ClockSourceConfig(tmpclksource);
		}
        else if(hlptim->Instance == LPTIM5)
		{
            HAL_RCC_LPTIM5ClockSourceConfig(tmpclksource);
		}
        else if(hlptim->Instance == LPTIM6)
		{
            HAL_RCC_LPTIM6ClockSourceConfig(tmpclksource);
		}
    }

    /* Restore configuration registers (LPTIM should be disabled first) */
    hlptim->Instance->CFGR2 = tmpCFGR2;
    hlptim->Instance->CFGR1 = tmpCFGR1;
    hlptim->Instance->IER = tmpIER;

//    __enable_irq();
    
    return HAL_OK;
}

#endif /* HAL_LPTIM_MODULE_ENABLED */

/************************ (C) COPYRIGHT AISINOCHIP *****END OF FILE****/
