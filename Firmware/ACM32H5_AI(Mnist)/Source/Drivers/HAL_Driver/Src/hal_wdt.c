
/******************************************************************************
*@file  : hal_wdt.c
*@brief : WDT HAL module driver.
******************************************************************************/

#include "hal.h" 

#ifdef HAL_WDT_MODULE_ENABLED


/******************************************************************************
*@brief : WDT interrupt request.
*@param : hwdt: pointer to a WDT_HandleTypeDef structure that contains
*                the configuration information for the specified WDT module.
*@return: None
******************************************************************************/
void HAL_WDT_IRQHandler(WDT_HandleTypeDef *hwdt)
{
    /* Check the parameters */
    assert_param(IS_WDT_ALL_INSTANCE(hwdt->Instance));

    HAL_WDT_Callback(hwdt);
}


/******************************************************************************
*@brief : WDT interrupt callback.
*@param : hwdt: pointer to a WDT_HandleTypeDef structure that contains
*                the configuration information for the specified WDT module.
*@return: None
******************************************************************************/
__weak void HAL_WDT_Callback(WDT_HandleTypeDef *hwdt)
{
    UNUSED(hwdt);
}

/******************************************************************************
*@brief : Initialize the WDG according to the specified.
*         parameters in the WDG_InitTypeDef of associated handle.
*@param : hwdt: pointer to a WDT_HandleTypeDef structure that contains
*               the configuration information for the specified WDT module.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_WDT_Init(WDT_HandleTypeDef *hwdt)
{
    /* Check the WWDG handle allocation */
    if (hwdt == NULL)
    {
    return HAL_ERROR;
    }

    /* Check the parameters */
    assert_param(IS_WDT_ALL_INSTANCE(hwdt->Instance));
    assert_param(IS_WDT_PRESCALER(hwdt->Init.Prescaler));
    assert_param(IS_WDT_MODE(hwdt->Init.Mode));

    HAL_WDT_MspInit(hwdt);
    
    /* disable the WDT */
    hwdt->Instance->CTRL &= ~WDT_CTRL_EN;
    
    /* Set WDG Prescaler and Mode*/
    hwdt->Instance->CTRL &= ~(WDT_CTRL_DIVISOR | WDT_CTRL_MODE);
    hwdt->Instance->CTRL |= hwdt->Init.Prescaler | hwdt->Init.Mode;

    /* Set WDG load */
    hwdt->Instance->LOAD = hwdt->Init.Load;

    /* Set WDG interrupt clear time */
    if (hwdt->Init.Mode == WDT_MODE_INTERRUPT)
    {
        assert_param(IS_WDT_INTCLRTIME(hwdt->Init.IntClrTime));
        hwdt->Instance->INTCLRTIME = hwdt->Init.IntClrTime;
    }
    
    /* enable the WDT */
    hwdt->Instance->CTRL |= WDT_CTRL_EN;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Initialize the WDT MSP.
*@param : hwdt: pointer to a WDT_HandleTypeDef structure that contains
*               the configuration information for the specified WDT module.
*@return: None
******************************************************************************/
__weak void HAL_WDT_MspInit(WDT_HandleTypeDef * hwdt)
{
    UNUSED(hwdt);
}




/******************************************************************************
*@brief : Refresh the WDT.
*@param : hwdt: pointer to a WDT_HandleTypeDef structure that contains
*               the configuration information for the specified WDT module.
*@return: None
******************************************************************************/

/**
  * @brief  Refresh the WWDG.
  * @param  hwwdg  pointer to a WWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_WDT_Refresh(WDT_HandleTypeDef *hwdt)
{
    hwdt->Instance->FEED = WDT_CMD_FEED_WATCHDOG;
    
    return HAL_OK;
}

#endif /* HAL_WDT_MODULE_ENABLED */

