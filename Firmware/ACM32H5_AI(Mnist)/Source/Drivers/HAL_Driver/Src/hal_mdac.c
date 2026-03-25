/******************************************************************************
* @file      : hal_mdac.c
* @version   : 1.0
* @date      : 2023.10.16
* @brief     : MDAC HAL module driver
******************************************************************************/
#include "hal.h" 

#ifdef HAL_MDAC_MODULE_ENABLED

/******************************************************************************
* @brief : Initialize the MDAC MSP.
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @return: none
******************************************************************************/
__weak void HAL_MDAC_MspInit(MDAC_HandleTypeDef *hmdac)
{
    /* NOTE : This function should not be modified, when the callback is needed,
    the HAL_MDAC_MspInit can be implemented in the user file
    */
    UNUSED(hmdac);
}

/******************************************************************************
* @brief : MDAC MSP De-Initialization.
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @return: none
******************************************************************************/
__weak void HAL_MDAC_MspDeInit(MDAC_HandleTypeDef* hmdac)
{
    /* 
    NOTE : This function should be modified by the user.
    the HAL_MDAC_MspDeInit can be implemented in the user file.
    */
    UNUSED(hmdac); 

}

/******************************************************************************
* @brief : Initializes the MDAC peripheral according to the specified  parameters in the MDAC_HandleTypeDef.
* @param : hdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_MDAC_Init(MDAC_HandleTypeDef *hmdac)
{
    /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));

    __HAL_RCC_MDAC_RESET();
    
    __HAL_RCC_MDAC_CLK_ENABLE();

    HAL_MDAC_MspInit(hmdac);
    
    return HAL_OK;
}

/******************************************************************************
* @brief : Deinitialize the MDAC peripheral registers to their default reset values.
* @param : hdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_MDAC_DeInit(MDAC_HandleTypeDef *hmdac)
{
    /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));
    
    HAL_MDAC_MspDeInit(hmdac);
    
    __HAL_RCC_MDAC_CLK_DISABLE();

    return HAL_OK;
}

/******************************************************************************
* @brief : Configures the selected MDAC voltage channel.
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @param : Config : MDAC voltage channel configuration structure
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_MDAC_ConfigVoltageChannel(MDAC_HandleTypeDef* hmdac, uint32_t Channel, VDAC_ChannelConfigTypeDef* Config)
{
    /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));
    assert_param(IS_VDAC_CHANNEL_NUM(Channel));   
    assert_param(IS_VDAC_BUFFER_MODE(Config->BufferMode));    
    
    if(Config->SampleEn)
    {
        hmdac->Instance->VDACx_CTRL[Channel] |= MDAC_VDACX_CR_SAMPLE_EN;
    }
    else
    {
        hmdac->Instance->VDACx_CTRL[Channel] &= ~MDAC_VDACX_CR_SAMPLE_EN;
    }
    
    /* config the Voltage DAC buffer mode.  Note; config buffer mode before setting VDACx_CTRL.EN */
    MODIFY_REG(hmdac->Instance->VDACx_CTRL[Channel], MDAC_VDACX_CR_MODE_Msk, Config->BufferMode << MDAC_VDACX_CR_MODE_Pos);
    
    if(Config->SelfCalibrateEn)
    {
        HAL_MDAC_VoltageSelfcalibrate(hmdac, Channel);
    }
    else
    {
        /*  factory trimming in NVR,read to DAC_CCR */
        uint8_t trim_val;
        HAL_StatusTypeDef ret;
        ret = HAL_EFUSE_ReadByte(EFUSE1, 0x7A + Channel, &trim_val, 100000);
        
        if(ret == HAL_OK)
            MODIFY_REG(hmdac->Instance->VDACx_CTRL[Channel], MDAC_VDACX_CR_OTRIM_Msk, trim_val << MDAC_VDACX_CR_OTRIM_Pos);
    }
        
    SET_BIT(hmdac->Instance->VDACx_CTRL[Channel], MDAC_VDACX_CR_EN);
    
    return HAL_OK;  
}

/******************************************************************************
* @brief : Configures the selected MDAC current channel.
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @param : Config : MDAC current channel configuration structure
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_MDAC_ConfigCurrentChannel(MDAC_HandleTypeDef* hmdac, uint32_t Channel, IDAC_ChannelConfigTypeDef* Config)
{
    /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));    
    assert_param(IS_IDAC_ITURN(Config->ITurn));       
    assert_param(IS_IDAC_CHANNEL_NUM(Channel));
    
    if(Config->ITurn == ITURN_FACTORY)
    {
        uint8_t iturn_val;
        HAL_StatusTypeDef ret;
        ret = HAL_EFUSE_ReadByte(EFUSE1, 0x86 + Channel, &iturn_val, 100000);
        
        if(ret == HAL_OK)
            MODIFY_REG(hmdac->Instance->IDACx_CTRL[Channel], MDAC_IDACX_CR_ITURE_Msk, iturn_val << MDAC_IDACX_CR_ITURE_Pos);
    }
    else
    {
        MODIFY_REG(hmdac->Instance->IDACx_CTRL[Channel], MDAC_IDACX_CR_ITURE_Msk, Config->ITurn << MDAC_IDACX_CR_ITURE_Pos);
    }
        
    SET_BIT(hmdac->Instance->IDACx_CTRL[Channel], MDAC_IDACX_CR_EN);
    
    return HAL_OK;  
}


/******************************************************************************
* @brief : Set the specified value for MDAC voltage channel.
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @param : Channel : MDAC voltage channel index.
* @param : Data: The destination peripheral data. 
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_MDAC_SetVoltageValue(MDAC_HandleTypeDef *hmdac, uint32_t Channel, uint32_t Data)
{
    /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));
    assert_param(IS_VDAC_CHANNEL_NUM(Channel)); 

    hmdac->Instance->DACx_DOR[Channel] = Data;

    return HAL_OK;
}

/******************************************************************************
* @brief : Returns the last data output value of the selected MDAC voltage channel.
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @param : Channel : MDAC voltage channel index.
* @return: The selected MDAC voltage channel data output value
******************************************************************************/
uint32_t HAL_MDAC_GetVoltageValue(MDAC_HandleTypeDef* hmdac, uint32_t Channel)
{
   /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));
    assert_param(IS_VDAC_CHANNEL_NUM(Channel)); 

    return hmdac->Instance->DACx_DOR[Channel];

}

/******************************************************************************
* @brief : Set the specified value for MDAC current channel.
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @param : Channel : MDAC current channel index.
* @param : Data: The destination peripheral data. 
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_MDAC_SetCurrentValue(MDAC_HandleTypeDef *hmdac, uint32_t Channel, uint32_t Data)
{
    /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));
    assert_param(IS_IDAC_CHANNEL_NUM(Channel)); 

    hmdac->Instance->DACx_DOR[12 + Channel] = Data;

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
* @brief : Returns the last data output value of the selected MDAC current channel.
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @param : Channel : MDAC current channel index.
* @return: The selected MDAC current channel data output value
******************************************************************************/
uint32_t HAL_MDAC_GetCurrentValue(MDAC_HandleTypeDef* hmdac, uint32_t Channel)
{
   /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));
    assert_param(IS_IDAC_CHANNEL_NUM(Channel)); 

    return hmdac->Instance->DACx_DOR[12 + Channel];

}

/******************************************************************************
* @brief : Run the self calibration of one voltage DAC channel.
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @param : Channel : The selected MDAC voltage channel.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_MDAC_VoltageSelfcalibrate(MDAC_HandleTypeDef *hmdac, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));
    assert_param(IS_VDAC_CHANNEL_NUM(Channel));

    uint32_t TrimVal;
    uint32_t ChannelEn;

    ChannelEn = READ_BIT((hmdac->Instance->VDACx_CTRL[Channel]), MDAC_VDACX_CR_EN);
    
    if(!ChannelEn)
        SET_BIT((hmdac->Instance->VDACx_CTRL[Channel]), MDAC_VDACX_CR_EN);

    SET_BIT((hmdac->Instance->VDACx_CTRL[Channel]), MDAC_VDACX_CR_CEN);

    for(TrimVal = 0; TrimVal < 32; TrimVal++)
    {
        /* Set candidate trimming */
        MODIFY_REG(hmdac->Instance->VDACx_CTRL[Channel], MDAC_VDACX_CR_OTRIM_Msk, TrimVal << MDAC_VDACX_CR_OTRIM_Pos);
        
        HAL_SimpleDelay(50000);
        
        if(READ_BIT((hmdac->Instance->VDACx_CTRL[Channel]), MDAC_VDACX_CR_CAL_FLAG))
            break;
    }

    CLEAR_BIT((hmdac->Instance->VDACx_CTRL[Channel]), MDAC_VDACX_CR_CEN);

    if(!ChannelEn)
        CLEAR_BIT((hmdac->Instance->VDACx_CTRL[Channel]), MDAC_VDACX_CR_EN);
    
    if(TrimVal > 31)
    {
        /* Restore the original TrimVal */
        
        return HAL_ERROR;
    }

    return HAL_OK;
}



/******************************************************************************
* @brief : Set the trimming mode and trimming value (user trimming mode applied).
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @param : Channel : The selected MDAC voltage channel. 
* @param : TrimVal: VDAC trim value
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_MDAC_SetVoltageTrim(MDAC_HandleTypeDef *hmdac, uint32_t Channel, uint32_t TrimVal)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));
    assert_param(IS_VDAC_CHANNEL_NUM(Channel));
    assert_param(IS_VDAC_TRIM_VALUE(TrimVal));
    
    MODIFY_REG(hmdac->Instance->VDACx_CTRL[Channel], MDAC_VDACX_CR_OTRIM_Msk, TrimVal << MDAC_VDACX_CR_OTRIM_Pos);

    return HAL_OK;
}

/******************************************************************************
* @brief : Return the MDAC voltage trim value.
* @param : hmdac : pointer to a MDAC_HandleTypeDef structure that contains
*                      the configuration information for MDAC module.
* @param : Channel : The selected MDAC voltage channel. 
* @return: The trim value of selected voltage channel.
******************************************************************************/
uint32_t HAL_MDAC_GetVoltageTrimValue(MDAC_HandleTypeDef *hmdac, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_MDAC_INSTANCE(hmdac->Instance));
    assert_param(IS_VDAC_CHANNEL_NUM(Channel));

    /* Retrieve trimming  */
    return ((hmdac->Instance->VDACx_CTRL[Channel] & MDAC_VDACX_CR_OTRIM_Msk) >> MDAC_VDACX_CR_OTRIM_Pos);
}

#endif

