
/******************************************************************************
*@file  : hal_iwdt.c
*@brief : IWDT HAL module driver.
******************************************************************************/

#include "hal.h" 


#ifdef HAL_IWDT_MODULE_ENABLED


static HAL_StatusTypeDef HAL_IWDT_WaitOnFlagToResetUntilTimeout(IWDT_HandleTypeDef *hiwdt, \
                                    uint32_t flags, int32_t startTick, uint32_t timeout);

/******************************************************************************
*@brief : IWDT interrupt request.
*@param : hiwdt: pointer to a IWDT_HandleTypeDef structure that contains
*                the configuration information for the specified IWDT module.
*@return: None
******************************************************************************/
void HAL_IWDT_IRQHandler(IWDT_HandleTypeDef *hiwdt)
{
    /* Check the parameters */
    assert_param(IS_IWDT_ALL_INSTANCE(hiwdt->Instance));

    if (SET == HAL_IWDT_GetPending())
    {
		HAL_IWDT_Callback(hiwdt);
        
        /* Clear interrupt pending bit of the IWDT. */
        HAL_IWDT_ClearPending();
    }
}


/******************************************************************************
*@brief : IWDT interrupt callback.
*@param : hiwdt: pointer to a IWDT_HandleTypeDef structure that contains
*                the configuration information for the specified IWDT module.
*@return: None
******************************************************************************/
__weak void HAL_IWDT_Callback(IWDT_HandleTypeDef *hiwdt)
{
    UNUSED(hiwdt);
}

/******************************************************************************
*@brief : Initialize the IWDT according to the specified parameters in the
*         IWDT_InitTypeDef and start watchdog. Before exiting function,
*         watchdog is refreshed in order to have correct time base.
*@param : hiwdt: pointer to a IWDT_HandleTypeDef structure that contains
*               the configuration information for the specified IWDT module.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_IWDT_Init(IWDT_HandleTypeDef * hiwdt)
{
    uint32_t startTime;
    
    /* Check the parameters */
    assert_param(IS_IWDT_HANDLE(hiwdt));
    assert_param(IS_IWDT_ALL_INSTANCE(hiwdt->Instance));
    assert_param(IS_IWDT_PRESCALER(hiwdt->Init.Prescaler));
    assert_param(IS_IWDT_RELOAD(hiwdt->Init.Reload));
    assert_param(IS_IWDT_WINDOW(hiwdt->Init.Window));
    assert_param(IS_IWDT_WAKEUP(hiwdt->Init.Wakeup));

    HAL_IWDT_MspInit(hiwdt);
    
    
    /* Enable IWDT. RC32K is turned on automatically */
    hiwdt->Instance->CMDR = IWDT_CMD_ENABLE;
    
    /* Enable write access to IWDT_PR */
    hiwdt->Instance->CMDR = IWDT_CMD_WRITE_ENABLE;

    /* Check flag IWDT_FLAG_PVU */
    startTime = HAL_GetTick();
    if (HAL_IWDT_WaitOnFlagToResetUntilTimeout(hiwdt, IWDT_FLAG_PVU, startTime, IWDT_PVU_TIMEOUT) != HAL_OK)
        return HAL_ERROR;
    
    /* Write to IWDT registers the Prescaler to work with */
    hiwdt->Instance->PR = hiwdt->Init.Prescaler;
	
    /* Check flag IWDT_FLAG_RVU */
    startTime = HAL_GetTick();
    if (HAL_IWDT_WaitOnFlagToResetUntilTimeout(hiwdt, IWDT_FLAG_RVU, startTime, IWDT_RVU_TIMEOUT) != HAL_OK)
        return HAL_ERROR;
    
    /* Write to IWDT registers the Reload values to work with */
    hiwdt->Instance->RLR = hiwdt->Init.Reload;
	
    /* Check flag IWDT_FLAG_WTU */
    startTime = HAL_GetTick();
    if (HAL_IWDT_WaitOnFlagToResetUntilTimeout(hiwdt, IWDT_FLAG_WTU, startTime, IWDT_WTU_TIMEOUT) != HAL_OK)
        return HAL_ERROR;
    
    /* Write to IWDT registers the Wakeup values to work with */
    if (hiwdt->Init.Reload > hiwdt->Init.Wakeup)
    {
        /* Check the parameters */
        assert_param(IS_IWDT_WAKEUPMODE(hiwdt->Init.WakeupMode));
        
        hiwdt->Instance->WUTR = hiwdt->Init.Wakeup;
        
        /* Clear interrupt pending bit of the IWDT. */
        HAL_EXTI_ClearPending(IWDT_EXTI_LINE);
        
        /* set wakeup mode. */
        HAL_EXTI_SetConfigLine(NULL, IWDT_EXTI_LINE, hiwdt->Init.WakeupMode);
    
    }
    else
    {
        /* wakeup disable */
        hiwdt->Instance->WUTR = IWDT_RELOAD_MAX_VALUE;
        
        /* Clear wakeup mode. */
        HAL_EXTI_ClearConfigLine(IWDT_EXTI_LINE);
        
        /* Clear interrupt pending bit of the IWDT. */
        HAL_EXTI_ClearPending(IWDT_EXTI_LINE);
    }
	
    /* Check flag IWDT_FLAG_WVU */
    startTime = HAL_GetTick();
    if (HAL_IWDT_WaitOnFlagToResetUntilTimeout(hiwdt, IWDT_FLAG_WVU, startTime, IWDT_WVU_TIMEOUT) != HAL_OK)
        return HAL_ERROR;
    
    /* Write to IWDT registers the window values to work with */
    if (hiwdt->Init.Reload <= hiwdt->Init.Window)
        hiwdt->Instance->WINR = IWDT_RELOAD_MAX_VALUE;
	
    /* Check all flags */
    startTime = HAL_GetTick();
    if (HAL_IWDT_WaitOnFlagToResetUntilTimeout(hiwdt, IWDT_FLAG_PVU | IWDT_FLAG_RVU | IWDT_FLAG_WVU | IWDT_FLAG_WTU | \
                                                        IWDT_FLAG_RLF, startTime, IWDT_RLF_TIMEOUT) != HAL_OK)
    {
        return HAL_ERROR;
    }
    
    if (hiwdt->Init.Reload > hiwdt->Init.Wakeup)
    {
        /* wakeup enable */
        hiwdt->Instance->CMDR = IWDT_CMD_WAKEUP_ENABLE;
    }
    
    if (hiwdt->Init.Reload > hiwdt->Init.Window)
    {
        /* Write to IWDT registers the window values to work with */
        hiwdt->Instance->WINR = hiwdt->Init.Window;
    }
    else
    {
        hiwdt->Instance->CMDR = IWDT_CMD_RELOAD;
    }
    
    /* Check all flags */
    startTime = HAL_GetTick();
    if (HAL_IWDT_WaitOnFlagToResetUntilTimeout(hiwdt, IWDT_FLAG_PVU | IWDT_FLAG_RVU | IWDT_FLAG_WVU | IWDT_FLAG_WTU | \
                                                        IWDT_FLAG_RLF, startTime, IWDT_RLF_TIMEOUT) != HAL_OK)
        return HAL_ERROR;
    
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Initialize the IWDT MSP.
*@param : hiwdt: pointer to a IWDT_HandleTypeDef structure that contains
*                the configuration information for the specified IWDT module.
*@return: None
******************************************************************************/
__weak void HAL_IWDT_MspInit(IWDT_HandleTypeDef * hiwdt)
{
    UNUSED(hiwdt);
}

/******************************************************************************
*@brief : Refresh the IWDT.
*@param : hiwdt: pointer to a IWDT_HandleTypeDef structure that contains
*                the configuration information for the specified IWDT module.
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_IWDT_Refresh(IWDT_HandleTypeDef *hiwdt)
{
    /* Check the parameters */
    assert_param(IS_IWDT_HANDLE(hiwdt));

    hiwdt->Instance->CMDR = IWDT_CMD_RELOAD;
    
    while (hiwdt->Instance->SR & IWDT_FLAG_RLF);
    
    return HAL_OK;
}


/******************************************************************************
*@brief : Get interrupt pending bit of the IWDT.
*@return: None
******************************************************************************/
FlagStatus HAL_IWDT_GetPending(void)
{
    return (HAL_EXTI_GetPending(IWDT_EXTI_LINE));
}  

/******************************************************************************
*@brief : Clear interrupt pending bit of the IWDT.
*@return: None.
******************************************************************************/
void HAL_IWDT_ClearPending(void)
{
    HAL_EXTI_ClearPending(IWDT_EXTI_LINE);
}

/******************************************************************************
*@brief : Handle IWDT Timeout.
*@param : hiwdt: pointer to a IWDT_HandleTypeDef structure that contains
*                the configuration information for the specified IWDT module.
*@param : flags: Specifies the IWDT flag to check.
*                This parameter can be a combination of @ref IWDT_Flag.
*                @arg IWDT_FLAG_PVU: IWDT timer prescaler value update.
*                @arg IWDT_FLAG_RVU: IWDT timer reload value update.
*                @arg IWDT_FLAG_WVU: IWDT timer window value update.
*                @arg IWDT_FLAG_WTU: IWDT timer wake-up value update.
*                @arg IWDT_FLAG_RLF: IWDT timer feeding dog completed.
*@param : startTick: Tick start value.
*@param : timeout: Timeout duration.
*@return: None.
******************************************************************************/
static HAL_StatusTypeDef HAL_IWDT_WaitOnFlagToResetUntilTimeout(IWDT_HandleTypeDef *hiwdt, \
                                    uint32_t flags, int32_t startTick, uint32_t timeout)
{
    while ((hiwdt->Instance->SR & flags) == flags)
    {
        if ((HAL_GetTick() - startTick) >= timeout)
            return (HAL_TIMEOUT);
    }
    return (HAL_OK);
}

#endif /* HAL_IWDT_MODULE_ENABLED */

/************************ (C) COPYRIGHT AISINOCHIP *****END OF FILE****/

