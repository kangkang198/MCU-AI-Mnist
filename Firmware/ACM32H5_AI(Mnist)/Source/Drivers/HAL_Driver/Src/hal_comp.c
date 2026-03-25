
/******************************************************************************
*@file  : hal_comp.c
*@brief : COMP HAL module driver.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#include "hal.h"

#ifdef HAL_COMP_MODULE_ENABLED

/******************************************************************************
*@brief : COMP MSP Initialization.such as module clock, IO share, ... 
*           COMP1 VinP: PB0, PB2
*           COMP1 VinM: DAC1,PB1,PC4,VREF_AVDD
*           COMP1 Vout: PA11(AF5), PB8(AF1), PC5(AF14), PE12(AF15), PF4(AF5)
*@param : hcomp: COMP handle
*@return: None
******************************************************************************/
__weak void HAL_COMP_MspInit(COMP_HandleTypeDef* hcomp)
{
    //Prevent unused argument(s) compilation warning
    UNUSED(hcomp);

    //NOTE : This function should not be modified. 
    //when the callback is needed,the HAL_COMP_MspInit could be implemented in the user file
}

/******************************************************************************
*@brief : COMP MSP De-Initialization.
*@param : hcomp: COMP handle
*@return: None
******************************************************************************/
__weak void HAL_COMP_MspDeInit(COMP_HandleTypeDef* hcomp)
{
    //Prevent unused argument(s) compilation warning
    UNUSED(hcomp);

    //NOTE : This function should not be modified. 
    //when the callback is needed,the HAL_COMP_MspDeInit could be implemented in the user file
}

/******************************************************************************
*@brief : Initialize the COMP. 
*@note  : If the selected comparator is locked, initialization can't be performed.
*         To unlock the configuration, perform a module reset.
*@param : hcomp: COMP handle
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef* hcomp)
{    
    uint32_t tempReg;
    
    if(hcomp == NULL)
    {
        return HAL_ERROR;
    }

    assert_param(IS_COMP_INSTANCE(hcomp->Instance));
 
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_COMP_MspInit(hcomp);  
    
    //check lock status
    if(hcomp->Instance->CR & COMP_CR_LOCK)
    {
        return HAL_ERROR;
    }

    tempReg = 0;
    
    assert_param(IS_COMP_POLARITY(hcomp->Init.Polarity));      
    assert_param(IS_COMP_BLANKSEL(hcomp->Init.BlankSel));  
    assert_param(IS_COMP_HYS(hcomp->Init.HYS)); 
    tempReg |= ((hcomp->Init.Polarity & COMP_CR_POLARITY_Msk) | \
                (hcomp->Init.BlankSel & COMP_CR_BLANKSEL_Msk) | \
                (hcomp->Init.HYS & COMP_CR_HYS_Msk));
    
    assert_param(IS_COMP_INPSEL(hcomp->Init.InPSel));
    tempReg |= hcomp->Init.InPSel & COMP_CR_INPSEL_Msk;
    
    assert_param(IS_COMP_INMSEL(hcomp->Init.InMSel));
    tempReg |= hcomp->Init.InMSel & COMP_CR_INMSEL_Msk;
    
    
    if(hcomp->Init.InMSel == COMP_INMSEL_VREF_AVDD)
    {
        assert_param(IS_COMP_CRVSEL(hcomp->Init.CrvSel)); 
        assert_param(IS_COMP_CRVEN(hcomp->Init.CrvEn)); 
        tempReg |= ((hcomp->Init.CrvSel & COMP_CR_CRV_SEL_Msk) | \
                    (hcomp->Init.CrvEn & COMP_CR_CRV_EN_Msk));
        
        if(hcomp->Init.CrvEn == COMP_CRV_ENABLE)
        {
            assert_param(IS_COMP_CRVCFG(hcomp->Init.CrvCfg));
            tempReg |= hcomp->Init.CrvCfg << COMP_CR_CRV_CFG_Pos;
        }
    }
    
    assert_param(IS_COMP_FLTEN(hcomp->Init.FltEn));
    tempReg |= hcomp->Init.FltEn & COMP_CR_FLTEN_Msk;
    if(hcomp->Init.FltEn == COMP_FLT_ENABLE)
    {
        assert_param(IS_COMP_FLTTIME(hcomp->Init.FltTime));
        tempReg |= hcomp->Init.FltTime & COMP_CR_FLTTIME_Msk;
    }
    
    CLEAR_BIT(hcomp->Instance->CR, COMP_CR_EN); //disable            

    //Write the COMP_CR register
    WRITE_REG(hcomp->Instance->CR,tempReg);

    return HAL_OK;
}

/******************************************************************************
*@brief : de-Initialize the COMP. 
*@note  : If the selected comparator is locked, de-initialization can't be performed.
*         To unlock the configuration, perform a module reset.
*@param : hcomp: COMP handle
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_COMP_DeInit(COMP_HandleTypeDef* hcomp)
{ 
    if(hcomp == NULL)
    {
        return HAL_ERROR;
    }

    assert_param(IS_COMP_INSTANCE(hcomp->Instance));

    //check lock status
    if(hcomp->Instance->CR & COMP_CR_LOCK)
    {
        return HAL_ERROR;
    }

    /* Set COMP_CSR register to reset value */
    WRITE_REG(hcomp->Instance->CR, 0x00000000UL);
    
    HAL_COMP_MspDeInit(hcomp);

    memset(&hcomp->Init, 0, sizeof(hcomp->Init));

    return HAL_OK;
}

/******************************************************************************
*@brief : Enable comparator.
*@param : hcomp: COMP handle
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_COMP_Enable(COMP_HandleTypeDef* hcomp)
{
    if(hcomp == NULL)
    {
        return HAL_ERROR;
    }

    assert_param(IS_COMP_INSTANCE(hcomp->Instance));
    
    //check lock status
    if(hcomp->Instance->CR & COMP_CR_LOCK)
    {
        return HAL_ERROR;
    }

    SET_BIT(hcomp->Instance->CR, COMP_CR_EN); //enable
    
    return HAL_OK;
}

/******************************************************************************
*@brief : disable comparator.
*@param : hcomp: COMP handle
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_COMP_Disable(COMP_HandleTypeDef* hcomp)
{
    if(hcomp == NULL)
    {
        return HAL_ERROR;
    }

    assert_param(IS_COMP_INSTANCE(hcomp->Instance));
        
    //check lock status
    if(hcomp->Instance->CR & COMP_CR_LOCK)
    {
        return HAL_ERROR;
    }

    CLEAR_BIT(hcomp->Instance->CR, COMP_CR_EN); //disable
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Get the output level of the comparator. the value is stored in hcomp.
*@param : hcomp: COMP handle.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_COMP_GetOutputLevel(COMP_HandleTypeDef* hcomp)
{    
    if(hcomp == NULL)
    {
        return HAL_ERROR;
    }

    assert_param(IS_COMP_INSTANCE(hcomp->Instance));
    
    hcomp->OutputLevelOrg = (hcomp->Instance->SR & COMP_SR_VCOUT1_ORG) ? 1 : 0;
    hcomp->OutputLevel    = (hcomp->Instance->SR & COMP_SR_VCOUT1) ? 1 : 0; 
    
    return HAL_OK;
}


/******************************************************************************
*@brief : start comparator.
*@param : hcomp: COMP handle
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp)
{
    return(HAL_COMP_Enable(hcomp));
}


/******************************************************************************
*@brief : stop comparator.
*@param : hcomp: COMP handle
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp)
{
    return(HAL_COMP_Disable(hcomp));
}


/******************************************************************************
*@brief : lock comparator.
*@param : hcomp: COMP handle
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef* hcomp)
{
    __IO uint32_t *pCRx;
    
    if(hcomp == NULL)
    {
        return HAL_ERROR;
    }

    assert_param(IS_COMP_INSTANCE(hcomp->Instance));
    
    //check lock status
    if(hcomp->Instance->CR & COMP_CR_LOCK)
    {
        return HAL_OK;
    }
    
    SET_BIT(hcomp->Instance->CR, COMP_CR_LOCK); //lock

    return HAL_OK;
}

#endif
