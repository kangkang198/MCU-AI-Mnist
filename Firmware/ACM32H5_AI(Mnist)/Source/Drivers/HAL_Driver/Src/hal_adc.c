
/******************************************************************************
* @file      : HAL_ADC.c
* @version   : 1.0
* @date      : 2022.10.29
* @brief     : ADC HAL module driver
*   
* @history   :	
*   2022.10.25    lwq    create
*   
******************************************************************************/
#include "hal.h"


#ifdef HAL_ADC_MODULE_ENABLED



/******************************************************************************
* @brief : This function handles ADC interrupt request.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: none
******************************************************************************/
__weak void HAL_ADC_IRQCallback(ADC_HandleTypeDef* hadc)
{

}

/******************************************************************************
* @brief : Handle ADC interrupt request.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: None
******************************************************************************/
void HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc)
{
    HAL_ADC_IRQCallback(hadc);
}


/******************************************************************************
* @brief : Initialize the ADC MSP.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: none
******************************************************************************/
__weak void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{   
    /* 
      NOTE : This function should be modified by the user.
      the HAL_ADC_MspInit can be implemented in the user file.
    */
    UNUSED(hadc);  
}

/******************************************************************************
* @brief : Deinitialize the ADC MSP.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: none
******************************************************************************/
__weak void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{    
    /* 
    NOTE : This function should be modified by the user.
    the HAL_ADC_MspDeInit can be implemented in the user file.
    */
    UNUSED(hadc);        
}

 /******************************************************************************
* @brief : Init the ADC module.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc)
{
    ADC_Common_TypeDef *tmpADC_Common;

    /* Check the ADC handle allocation */
    if (hadc == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ConConvMode));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DMAMode));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.OverMode));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.OverSampMode));       
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.AnalogWDGEn));
    assert_param(IS_ADC_CLOCKSOURCE(hadc->Init.ClockSource)); 
    assert_param(IS_ADC_CLOCKDIV(hadc->Init.ClockPrescaler));   
    assert_param(IS_ADC_RESOLUTION(hadc->Init.Resolution));
    assert_param(IS_ADC_DATA_ALIGN(hadc->Init.DataAlign));
    assert_param(IS_ADC_REGULAR_DISC_NUMBER(hadc->Init.NbrOfDiscConversion));    
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DiscontinuousConvMode));
    assert_param(IS_ADC_OVERSAMPLING_RATIO(hadc->Init.Oversampling.Ratio));
    assert_param(IS_ADC_RIGHTBITSHIFT(hadc->Init.Oversampling.RightBitShift));
    assert_param(IS_ADC_EXT_TRIG(hadc->Init.ExternalTrigConv));
    assert_param(IS_ADC_EXT_TRIG_EDGE(hadc->Init.ExternalTrigConvEdge));  

    if(hadc->Instance == ADC3)
    {
        tmpADC_Common = ADC3_COMMON;
    } 
    else
    {
        tmpADC_Common = ADC12_COMMON;
    } 

    /* Init the low level hardware : GPIO, CLOCK, NVIC, DMA */
    HAL_ADC_MspInit(hadc);    
    
    /* ADC regulator enable */
    SET_BIT(hadc->Instance->CR2,ADC_CR2_ADCVREGEN);
    HAL_SimpleDelay(50000);//delay 20us
    
    /* Release Reset AFE */
    SET_BIT(hadc->Instance->CR2,ADC_CR2_ADCRSTN);

    /* Select clock source */
    MODIFY_REG(tmpADC_Common->CCR, ADC_CCR_CLKMODE_Msk, hadc->Init.ClockSource);
    
    /* Set Clock DIV */
    MODIFY_REG(tmpADC_Common->CCR, ADC_CCR_ADCDIV_Msk, ((hadc->Init.ClockPrescaler - 1) << ADC_CCR_ADCDIV_Pos));
    
    
    if(hadc->Init.ChannelEn & ADC_CHANNEL_VBAT_EN)
    {
        SET_BIT(tmpADC_Common->CCR, ADC_CCR_VBATEN);//Enable VBAT    
    }
    else if(hadc->Init.ChannelEn & ADC_CHANNEL_VREF_EN)
    {
        SET_BIT(tmpADC_Common->CCR, ADC_CCR_VREFINTEN);//Enable VREF  
    }
    else if(hadc->Init.ChannelEn & ADC_CHANNEL_TEMP_EN)
    {
        SET_BIT(tmpADC_Common->CCR, ADC_CCR_TSEN);//Enable TS  
    }

    //Resolution
    hadc->Instance->CR2 &= ~(ADC_CR2_RES);
    hadc->Instance->CR2 |= hadc->Init.Resolution;

    /* Set ADC data alignment */
    hadc->Instance->CR2 &= ~(ADC_CR2_ALIGN);
    hadc->Instance->CR2 |= hadc->Init.DataAlign;

    //Set continued convert mode
    if(hadc->Init.ConConvMode)
    {
        SET_BIT(hadc->Instance->CR1,ADC_CR1_CONT);
    }
    else
    {
        CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_CONT);
    }
    //Set DMA mode
    MODIFY_REG(hadc->Instance->CR1, ADC_CR1_DMA_Msk, (hadc->Init.DMAMode << ADC_CR1_DMA_Pos));
    //Set Discontinued convert mode
    if(hadc->Init.DiscontinuousConvMode)
    {
        /* Enable the selected ADC regular discontinuous mode */
        hadc->Instance->CR1 |= (uint32_t)ADC_CR1_DISCEN;

        /* Set the number of channels to be converted in discontinuous mode */
        hadc->Instance->CR1 &= ~(ADC_CR1_DISCNUM_Msk);
        hadc->Instance->CR1 |=  ((hadc->Init.NbrOfDiscConversion-1) <<ADC_CR1_DISCNUM_Pos);
    }
    else
    {
        /* Disable the selected ADC regular discontinuous mode */
        hadc->Instance->CR1 &= ~(ADC_CR1_DISCEN);
    }

    //Overflow
    if(hadc->Init.OverMode)
    {
        SET_BIT(hadc->Instance->CR2,ADC_CR2_OVRMOD);
    }
    else
    {
        CLEAR_BIT(hadc->Instance->CR2,ADC_CR2_OVRMOD);
    }
    //Over Sample Set
    if(hadc->Init.OverSampMode)
    {
        MODIFY_REG(hadc->Instance->CR2,ADC_CR2_OVSR_Msk,hadc->Init.Oversampling.Ratio<<ADC_CR2_OVSR_Pos);   //over sample rate
        MODIFY_REG(hadc->Instance->CR2,ADC_CR2_OVSS_Msk,hadc->Init.Oversampling.RightBitShift<<ADC_CR2_OVSS_Pos); //over sample right shift.
        SET_BIT(hadc->Instance->CR2,ADC_CR2_OVSE); // Regular channel over sample en.
        if(hadc->Init.Oversampling.TriggeredMode)
        {
            SET_BIT(hadc->Instance->CR2,ADC_CR2_TROVS); // N times sample every trig.
        }
        else
        {
            CLEAR_BIT(hadc->Instance->CR2,ADC_CR2_TROVS); // 1 time sample every trig.
        }
    }

    //ExTrigSel set
    if(hadc->Init.ExternalTrigConv != ADC_SOFTWARE_START)
    {
        /* Select external trigger to start conversion */
        hadc->Instance->CR1 &= ~(ADC_CR1_EXTSEL_Msk);
        hadc->Instance->CR1 |= hadc->Init.ExternalTrigConv << ADC_CR1_EXTSEL_Pos;

        /* Select external trigger polarity */
        hadc->Instance->CR1 &= ~(ADC_CR1_EXTEN_Msk);
        hadc->Instance->CR1 |= hadc->Init.ExternalTrigConvEdge << ADC_CR1_EXTEN_Pos;
    }
    else
    {
        /* Reset the external trigger */
        hadc->Instance->CR1 &= ~(ADC_CR1_EXTSEL_Msk);
        hadc->Instance->CR1 &= ~(ADC_CR1_EXTEN_Msk);
    }

    //Clear the sequence length.
    CLEAR_BIT(hadc->Instance->SQR1,ADC_SQR1_L); //Clear the sequence length.

    return  HAL_OK;
}


/******************************************************************************
* @brief : DeInit the ADC module.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{
    /* Check the ADC handle allocation */
    if (hadc == NULL)
    {
        return HAL_ERROR;
    }
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    
    HAL_ADC_MspDeInit(hadc);

    hadc->ChannelNum = 0;
    hadc->ConvCpltCallback = NULL;
    hadc->InjectedConvCpltCallback = NULL;
    hadc->LevelOutOfWindowCallback = NULL;
    memset(&hadc->Init, 0, sizeof(hadc->Init));

    return  HAL_OK;
}
    

/******************************************************************************
* @brief : Config the regular channel.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @param : sConfig : pointer to a ADC_ChannelConfTypeDef structure that contains
*                    the configuration information for ADC channel
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig)
{   
    __IO uint32_t *Reg_ADC_OFR;	

    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_ADC_CHANNEL(sConfig->Channel));
    assert_param(IS_ADC_SEQUENCE(sConfig->Sq));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.OverSampMode)); 
    assert_param(IS_FUNCTIONAL_STATE(sConfig->Diff));
    assert_param(IS_ADC_OFFSET_NUMBER(sConfig->OffsetNumber));
    assert_param(IS_ADC_OFFSET(sConfig->Offset));
    assert_param(IS_ADC_OFFSET_CALCULATE(sConfig->OffsetCalculate));
    assert_param(IS_ADC_OFFSET_SIGN(sConfig->Offsetsign));
    assert_param(IS_ADC_REGULAR_LENGTH(hadc->ChannelNum));
    assert_param(IS_ADC_SMPCLOCK(sConfig->Smp));
    
    //In hardware oversampling mode, the offset compensation function is ignored
    if((sConfig->OffsetNumber != ADC_OFR_NONE) && (hadc->Init.OverSampMode))
    {
        return HAL_ERROR;
    }
    /* Differential mode set*/
    if(sConfig->Diff)
    {
        SET_BIT(hadc->Instance->DIFSEL, 1 << sConfig->Channel);
    }
    else
    {
        CLEAR_BIT(hadc->Instance->DIFSEL, 1 << sConfig->Channel);
    }

    /* Set Rule Sequence Conversion Order */
    if((sConfig->Sq >= 1)&&(sConfig->Sq <= 5))
    {    
        MODIFY_REG(hadc->Instance->SQR1,(ADC_SQR1_SQ1_Msk << (5*(sConfig->Sq - 1))), \
        (sConfig->Channel << (5*sConfig->Sq)));
    }
    else if((sConfig->Sq >= 6)&&(sConfig->Sq <= 11))
    {
        MODIFY_REG(hadc->Instance->SQR2,(ADC_SQR2_SQ6_Msk << (5*(sConfig->Sq-6))), \
        (sConfig->Channel << (5*(sConfig->Sq-6))));
    }
    else if((sConfig->Sq >= 12)&&(sConfig->Sq <= 16))
    {
        MODIFY_REG(hadc->Instance->SQR3,(ADC_SQR3_SQ12_Msk << (5*(sConfig->Sq-12))), \
        (sConfig->Channel << (5*(sConfig->Sq-12))));
    }
    else
    {
        return HAL_ERROR;
    }
    /* Set the length of the regular channel sequence */
    MODIFY_REG(hadc->Instance->SQR1, ADC_SQR1_L_Msk, (hadc->ChannelNum-1));

    /* Set the SMPR to every register*/
    if(sConfig->Channel <= ADC_CHANNEL_7) 
    {
        MODIFY_REG(hadc->Instance->SMPR1,(ADC_SMPR1_SMP0_Msk << (4*sConfig->Channel )), \
        (sConfig->Smp << (4*sConfig->Channel )));
    }
    else if((sConfig->Channel >= ADC_CHANNEL_8)&&(sConfig->Channel <= ADC_CHANNEL_15))
    {
        MODIFY_REG(hadc->Instance->SMPR2,(ADC_SMPR2_SMP8_Msk << (4*(sConfig->Channel-8))), \
        (sConfig->Smp << (4*(sConfig->Channel-8))));
    }
    else if((sConfig->Channel >= ADC_CHANNEL_16)&&(sConfig->Channel <= ADC_CHANNEL_18))
    {
        MODIFY_REG(hadc->Instance->SMPR3,(ADC_SMPR3_SMP16_Msk << (4*(sConfig->Channel-16))), \
        (sConfig->Smp << (4*(sConfig->Channel-16))));
    }
    else
    {
        return HAL_ERROR;
    }

    /*set Offset */
    if (sConfig->OffsetNumber != ADC_OFR_NONE)
    {
        MODIFY_REG(hadc->Instance->OFR[sConfig->OffsetNumber], 0XFFFFFFFF,  \
        (ADC_OFRX_OFFSETY_EN |(sConfig->Channel<<ADC_OFRX_OFFSETY_CH_Pos)| \
        sConfig->OffsetCalculate |sConfig->Offsetsign |sConfig->Offset));    			
    }
    else
    {
        hadc->Instance->OFR[0] &= ~ADC_OFRX_OFFSETY_EN;
        hadc->Instance->OFR[1] &= ~ADC_OFRX_OFFSETY_EN;
        hadc->Instance->OFR[2] &= ~ADC_OFRX_OFFSETY_EN;
        hadc->Instance->OFR[3] &= ~ADC_OFRX_OFFSETY_EN;
    }
    return HAL_OK;
}


/******************************************************************************
* @brief : Enable and start the ADC convertion.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
    /* Check the parameters */
    if(hadc == NULL)
    {
        return HAL_ERROR;
    }
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_ADC_EXT_TRIG(hadc->Init.ExternalTrigConv)); 
    
    hadc->Instance->SR = (ADC_SR_AWD | ADC_SR_JEOG | ADC_SR_JEOC | ADC_SR_OVERF | ADC_SR_EOG  | ADC_SR_EOC | ADC_SR_EOSMP | ADC_SR_ADRDY); 

    /* Enable the ADC */
    SET_BIT(hadc->Instance->CR2, (ADC_CR2_EN));

    /* Wait ADC ready */
    while(!(hadc->Instance->SR & ADC_SR_ADRDY));

    if(hadc->Init.ExternalTrigConv == ADC_SOFTWARE_START)
    {
        /* Start covertion */
        hadc->Instance->CR1 |= ADC_CR1_SWSTART;
    }

    /* Return function status */
    return HAL_OK;
}


/******************************************************************************
* @brief : Stop ADC conversion of regular group (and injected channels in 
*              case of auto_injection mode), disable ADC peripheral.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc)
{
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));

    if(hadc->Init.ConConvMode)
    {
        /* Set stop flag */
        SET_BIT(hadc->Instance->CR2, ADC_CR2_STP);        
        /* Waitting stop flag be cleared */    
        while(READ_BIT(hadc->Instance->CR2, ADC_CR2_STP));
    }

    /* Disable the ADC peripheral */
    (CLEAR_BIT(hadc->Instance->CR2, ADC_CR2_EN));

    /* Clear the SR register */
    hadc->Instance->SR = (ADC_SR_AWD | ADC_SR_OVERF | ADC_SR_EOG | ADC_SR_JEOC | ADC_SR_EOC | ADC_SR_ADRDY);

    /* Return function status */
    return HAL_OK;
}


/******************************************************************************
* @brief : Enable ADC, start conversion of regular group with interruption.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc)
{  
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.OverMode));
    
    /* Enable the ADC */
    SET_BIT(hadc->Instance->CR2, ADC_CR2_EN);
    /* Wait ADC ready */
    while(!(hadc->Instance->SR & ADC_SR_ADRDY));

    /* Clear the SR register */
    hadc->Instance->SR = (ADC_SR_EOG | ADC_SR_EOC);      

    hadc->Instance->IE |= (ADC_IE_EOCIE | ADC_IE_EOGIE);

    /* Enable ADC overrun interrupt */
    /* If hadc->Init.OverMode is set to ADC_OVERMODE_DISABLE, only then is
    ADC_IE_OVERFIE enabled; otherwise data overwrite is considered as normal
    behavior and no CPU time is lost for a non-processed interruption */
    if (hadc->Init.OverMode)
    {
        hadc->Instance->SR |= ADC_SR_OVERF;  
        hadc->Instance->IE |= ADC_IE_OVERFIE;
    }

    if(hadc->Init.ExternalTrigConv == ADC_SOFTWARE_START)	
    {
        /* Start covertion */
        SET_BIT(hadc->Instance->CR1,ADC_CR1_SWSTART);
    }

    /* Return function status */
    return HAL_OK;
}


/******************************************************************************
* @brief : Stop ADC conversion of regular group (and injected group in 
*              case of auto_injection mode), disable interrution of 
*              end-of-conversion, disable ADC peripheral.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc)
{
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ConConvMode));
    
    if(hadc->Init.ConConvMode)
    {
        /* Set stop flag */
        SET_BIT(hadc->Instance->CR2, ADC_CR2_STP);        
        /* Waitting stop flag be cleared */    
        while(READ_BIT(hadc->Instance->CR2, ADC_CR2_STP));
    }

    /* Disable the ADC peripheral */
    CLEAR_BIT(hadc->Instance->CR2, ADC_CR2_EN);

    /* Disable rehular interruptions */
    hadc->Instance->IE &= ~(ADC_IE_EOCIE | ADC_IE_EOGIE);  

    /* Clear the SR register */
    hadc->Instance->SR = (ADC_SR_EOG | ADC_SR_EOC);

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
* @brief : ADC retrieve conversion value intended to be used with polling or interruption.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @return: the ADC covert result
******************************************************************************/
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc)
{
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));

    return (hadc->Instance->DR);
}

/******************************************************************************
* @brief : Polling to get the results of the ADC converter.
* @param : hadc : pointer to a ADC_HandleTypeDef structure that contains
*                 the configuration information for ADC module.
* @param : pData : Destination Buffer address.
* @param : Length : Number of data to be transferred from ADC peripheral to memory.
* @param : Timeout : Polling timeout.
* @return: the ADC covert result
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_Polling(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length, uint32_t Timeout)
{
    uint32_t tmp_hal_status;
    __IO uint32_t uiTimeout; 

    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));    

    if(HAL_ADC_Start(hadc) != HAL_OK)
    {    
        return HAL_ERROR; 
    }
    if(!pData)
    {  
        return HAL_ERROR;
    }
    hadc->AdcResults = pData;
    uiTimeout = Timeout;

    while(Length)
    {
        tmp_hal_status = hadc->Instance->SR;
        if(tmp_hal_status & ADC_SR_EOC)
        {
            *hadc->AdcResults = hadc->Instance->DR;  
            hadc->Instance->SR = ADC_SR_EOC;
            hadc->AdcResults++;
            Length--;
        }
        if(tmp_hal_status & ADC_SR_OVERF)
        {
            hadc->Instance->SR = ADC_SR_OVERF;
        }        
        if(tmp_hal_status & ADC_SR_EOG)
        {
            hadc->Instance->SR = ADC_SR_EOG;
            break;
        }

        if(uiTimeout)
        {
            uiTimeout--;
            if(uiTimeout == 0)
            {
                return HAL_TIMEOUT;
            }
        }
    }

    HAL_ADC_Stop(hadc); 

    return HAL_OK;
}


/******************************************************************************
* @brief:  Configures for the selected ADC injected channel its corresponding
*          rank in the sequencer and its sample time.
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*          the configuration information for the specified ADC.
* @param:  sConfigInjected: ADC configuration structure for injected channel. 
* @return: None
******************************************************************************/
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc, ADC_InjectionConfTypeDef* sConfigInjected)
{
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->InjecOversamplingMode)); 
    assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->InjectedDiscontinuousConvMode)); 
    assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->AutoInjectedConv)); 
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.DiscontinuousConvMode)); 
    assert_param(IS_FUNCTIONAL_STATE(sConfigInjected->InjectedDiff)); 
    assert_param(IS_ADC_JDR_NUMBER(sConfigInjected->InjectedOffsetNumber));
    assert_param(IS_ADC_CHANNEL(sConfigInjected->InjectedChannel)); 
    assert_param(IS_ADC_SMPCLOCK(sConfigInjected->InjectedSamplingTime)); 
    assert_param(IS_ADC_INJECTED_RANK(sConfigInjected->InjectedRank));   
    assert_param(IS_ADC_INJECTED_LENGTH(sConfigInjected->InjectedNbrOfConversion));
    assert_param(IS_ADC_EXT_TRIG(sConfigInjected->ExternalTrigInjecConv));
    assert_param(IS_ADC_EXT_TRIG_EDGE(sConfigInjected->ExternalTrigInjecConvEdge));
    assert_param(IS_ADC_OFFSET(sConfigInjected->InjectedOffset));
    assert_param(IS_ADC_OFFSET_CALCULATE(sConfigInjected->InjectedOffsetCalculate));
    assert_param(IS_ADC_OFFSET_SIGN(sConfigInjected->InjectedOffsetSign));
    assert_param(IS_ADC_OVERSAMPLING_RATIO(sConfigInjected->InjecOversampling.Ratio));
    assert_param(IS_ADC_RIGHTBITSHIFT(sConfigInjected->InjecOversampling.RightBitShift));    
    
    //In hardware oversampling mode, the offset compensation function is ignored
    if((sConfigInjected->InjectedOffsetNumber!= ADC_JDR_NONE) && (sConfigInjected->InjecOversamplingMode))
    {       
        return HAL_ERROR;
    }
    /* JDISCEN and JAUTO bits can't be set at the same time  */
    if((sConfigInjected->InjectedDiscontinuousConvMode) && (sConfigInjected->AutoInjectedConv))
    {
        return HAL_ERROR;
    }
    /*  DISCEN and JAUTO bits can't be set at the same time */
    if((hadc->Init.DiscontinuousConvMode) && (sConfigInjected->AutoInjectedConv))
    {    
        return HAL_ERROR;
    }

    /* Diff Channel COnfig */
    if(sConfigInjected->InjectedDiff)
    {
        SET_BIT(hadc->Instance->DIFSEL,1<<sConfigInjected->InjectedChannel);       
    }
    else 
    {
        CLEAR_BIT(hadc->Instance->DIFSEL,1<<sConfigInjected->InjectedChannel);
    }

    /* Set the SMPR to every register*/
    if (sConfigInjected->InjectedChannel  <= ADC_CHANNEL_7)
    {
        MODIFY_REG(hadc->Instance->SMPR1,(ADC_SMPR1_SMP0_Msk << (4*sConfigInjected->InjectedChannel )), \
        (sConfigInjected->InjectedSamplingTime << (4*sConfigInjected->InjectedChannel )));	
    }
    else if(sConfigInjected->InjectedChannel>ADC_CHANNEL_7 || sConfigInjected->InjectedChannel<=ADC_CHANNEL_15)
    {
        MODIFY_REG(hadc->Instance->SMPR2,(ADC_SMPR2_SMP8_Msk << (4*(sConfigInjected->InjectedChannel-8))), \
        (sConfigInjected->InjectedSamplingTime << (4*(sConfigInjected->InjectedChannel-8))));
    }
    else if(sConfigInjected->InjectedChannel>ADC_CHANNEL_16 || sConfigInjected->InjectedChannel<=ADC_CHANNEL_18)
    {
        MODIFY_REG(hadc->Instance->SMPR3,(ADC_SMPR3_SMP16_Msk << (4*(sConfigInjected->InjectedChannel-16))), \
        (sConfigInjected->InjectedSamplingTime<< (4*(sConfigInjected->InjectedChannel-16))));
    }
    else
    {
        return HAL_ERROR;
    }
    /*---------------------------- ADCx JSQR Configuration -----------------*/
    //JL configuration
    hadc->Instance->JSQR &= ~(ADC_JSQR_JL);
    hadc->Instance->JSQR |= (sConfigInjected->InjectedNbrOfConversion-1)<<ADC_JSQR_JL_Pos;

    // Rank configuration 
    hadc->Instance->JSQR |= sConfigInjected->InjectedChannel <<(5*sConfigInjected->InjectedRank);

    /* Enable external trigger if trigger selection is different of software  */
    /* start.                                                                 */
    /* Note: This configuration keeps the hardware feature of parameter       */
    /*       ExternalTrigConvEdge "trigger edge none" equivalent to           */
    /*       software start.                                                  */ 
    if(sConfigInjected->ExternalTrigInjecConv != ADC_SOFTWARE_START)
    {  
        /* Select external trigger to start conversion */
        hadc->Instance->JSQR &= ~(ADC_JSQR_JEXTSEL);
        hadc->Instance->JSQR |=  sConfigInjected->ExternalTrigInjecConv << ADC_JSQR_JEXTSEL_Pos;

        /* Select external trigger polarity */
        hadc->Instance->JSQR &= ~(ADC_JSQR_JEXTEN);
        hadc->Instance->JSQR |= sConfigInjected->ExternalTrigInjecConvEdge << ADC_JSQR_JEXTEN_Pos;
    }
    else
    {
        /* Reset the external trigger */
        hadc->Instance->JSQR &= ~(ADC_JSQR_JEXTSEL);
        hadc->Instance->JSQR &= ~(ADC_JSQR_JEXTEN);  
    }

    //JAUTO configuration
    if (sConfigInjected->AutoInjectedConv)
    {
        /* Enable the selected ADC automatic injected group conversion */
        hadc->Instance->CR1 |= ADC_CR1_JAUTO;
    }
    else
    {
        /* Disable the selected ADC automatic injected group conversion */
        hadc->Instance->CR1 &= ~(ADC_CR1_JAUTO);
    }

    //InjectedDiscontinuousConvMode
    if (sConfigInjected->InjectedDiscontinuousConvMode)
    {
        /* Enable the selected ADC injected discontinuous mode */
        hadc->Instance->CR1 |= ADC_CR1_JDISCEN;
    }
    else
    {
        /* Disable the selected ADC injected discontinuous mode */
        hadc->Instance->CR1 &= ~(ADC_CR1_JDISCEN);
    }

    /*set Offset */
    if (sConfigInjected->InjectedOffsetNumber != ADC_OFR_NONE)
    {
        MODIFY_REG(hadc->Instance->OFR[sConfigInjected->InjectedOffsetNumber], 0XFFFFFFFF,  \
        (ADC_OFRX_OFFSETY_EN |(sConfigInjected->InjectedChannel<<ADC_OFRX_OFFSETY_CH_Pos) | \
        sConfigInjected->InjectedOffsetCalculate | sConfigInjected->InjectedOffsetSign | \
        sConfigInjected->InjectedOffset)); 
    }

    //Oversampling
    if (sConfigInjected->InjecOversamplingMode)
    {
        MODIFY_REG(hadc->Instance->CR2,ADC_CR2_OVSR_Msk,sConfigInjected->InjecOversampling.Ratio<<ADC_CR2_OVSR_Pos);   //over sample rate
        MODIFY_REG(hadc->Instance->CR2,ADC_CR2_OVSS_Msk,sConfigInjected->InjecOversampling.RightBitShift<<ADC_CR2_OVSS_Pos);//over sample right shift.
        SET_BIT(hadc->Instance->CR2,ADC_CR2_JOVSE); // Inject channel over sample en.		
    }
    else
    {
        CLEAR_BIT(hadc->Instance->CR2,ADC_CR2_JOVSE); // Inject channel over sample Disable.
    }

    return HAL_OK;	
}	

/******************************************************************************
* @brief:  Enables the selected ADC software start conversion of the injected channels.
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*          the configuration information for the specified ADC.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc)
{
    uint32_t tmp1 = 0U, tmp2 = 0U;

    /* Clear the SR register */
    hadc->Instance->SR = (ADC_SR_AWD | ADC_SR_JEOG | ADC_SR_JEOC | ADC_SR_OVERF | ADC_SR_EOG  | ADC_SR_EOC | ADC_SR_EOSMP | ADC_SR_ADRDY); 
    
    /* Enable the ADC */
    SET_BIT(hadc->Instance->CR2, ADC_CR2_EN);
    
    /* Wait ADC ready */
    while(!(hadc->Instance->SR & ADC_SR_ADRDY));

    tmp1 = HAL_IS_BIT_CLR(hadc->Instance->JSQR, ADC_JSQR_JEXTEN);
    tmp2 = HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO);
    if(tmp1 && tmp2)
    {
        /* Start covertion */
        SET_BIT(hadc->Instance->CR1,ADC_CR1_JSWSTART);
    }

    return HAL_OK;
}


/******************************************************************************
* @brief:  Stop ADC conversion of regular group (and injected channels in 
*              case of auto_injection mode), disable ADC peripheral.
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*          the configuration information for the specified ADC.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_InjectedStop(ADC_HandleTypeDef* hadc)
{
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ConConvMode)); 
    
    if(hadc->Init.ConConvMode)
    {
        /* Set stop flag */
        SET_BIT(hadc->Instance->CR2, ADC_CR2_STP);        
        /* Waitting stop flag be cleared */    
        while(READ_BIT(hadc->Instance->CR2, ADC_CR2_STP));
    }

    /* Disable the ADC peripheral */
    CLEAR_BIT(hadc->Instance->CR2, (ADC_CR2_EN));

    /* Clear the SR register */
    hadc->Instance->SR = (ADC_SR_AWD | ADC_SR_JEOG | ADC_SR_JEOC | ADC_SR_OVERF | ADC_SR_EOG  | ADC_SR_EOC | ADC_SR_EOSMP | ADC_SR_ADRDY); 

    /* Return function status */
    return HAL_OK;
}


/******************************************************************************
* @brief:  Enable ADC, start conversion of injected channel with interruption.
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*          the configuration information for the specified ADC.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_InjectedStart_IT(ADC_HandleTypeDef* hadc)
{  
    uint32_t tmp1 = 0U, tmp2 = 0U;
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));

    /* Enable the ADC */
    SET_BIT(hadc->Instance->CR2, (ADC_CR2_EN));
    /* Wait ADC ready */
    while(!(hadc->Instance->SR & ADC_SR_ADRDY));

    /* Clear the SR register */
    hadc->Instance->SR = (ADC_SR_JEOC | ADC_SR_JEOG);      

    hadc->Instance->IE |= (ADC_IE_JEOCIE | ADC_IE_JEOGIE);    

    tmp1 = HAL_IS_BIT_CLR(hadc->Instance->JSQR, ADC_JSQR_JEXTEN);
    tmp2 = HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_CR1_JAUTO);
    if(tmp1 && tmp2)
    {
        /* Enable the selected ADC software conversion for injected group */
        hadc->Instance->CR1 |= ADC_CR1_JSWSTART;
    }	

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
* @brief:  Stop ADC conversion of regular group (and injected group in 
*              case of auto_injection mode), disable interrution of 
*              end-of-conversion, disable ADC peripheral.
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*          the configuration information for the specified ADC.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_InjectedStop_IT(ADC_HandleTypeDef* hadc)
{
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.ConConvMode));
    
    if(hadc->Init.ConConvMode)
    {
        /* Set stop flag */
        SET_BIT(hadc->Instance->CR2, ADC_CR2_STP);        
        /* Waitting stop flag be cleared */    
        while(READ_BIT(hadc->Instance->CR2, ADC_CR2_STP));
    }

    /* Disable the ADC peripheral */
    CLEAR_BIT(hadc->Instance->CR2, ADC_CR2_EN);

    /* Disable Inject interruptions */
    hadc->Instance->IE &= ~(ADC_IE_JEOCIE | ADC_IE_JEOGIE);    

    /* Clear the SR register */
    hadc->Instance->SR = (ADC_SR_JEOG | ADC_SR_JEOC); 

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
* @brief:  Gets the converted value from data register of injected channel.
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*          the configuration information for the specified ADC.
* @param:  InjectedRank: the ADC injected rank.
*          This parameter can be one of the following values:
*            @arg ADC_INJECTED_RANK_1: Injected Channel1 selected
*            @arg ADC_INJECTED_RANK_2: Injected Channel2 selected
*            @arg ADC_INJECTED_RANK_3: Injected Channel3 selected
*            @arg ADC_INJECTED_RANK_4: Injected Channel4 selected
* @return: the ADC covert result
******************************************************************************/
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank)
{
    __IO uint32_t tmp = 0U;
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_ADC_INJECTED_RANK(InjectedRank));

    /* Clear injected group conversion flag to have similar behaviour as        */
    /* regular group: reading data register also clears end of conversion flag. */
    hadc->Instance->SR = ADC_SR_JEOC; 

    /* Return the selected ADC converted value */ 
    tmp =  hadc->Instance->JDR[InjectedRank-1];


    return tmp;
}

/******************************************************************************
* @brief:  Poll for injected conversion complete
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*          the configuration information for the specified ADC.
* @param:  Timeout: Timeout value in millisecond.  
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_InjectedPolling(ADC_HandleTypeDef* hadc, uint32_t InjectedRank, uint32_t* pData, uint32_t Length, uint32_t Timeout)
{
    uint32_t tmp_hal_status;
    __IO uint32_t uiTimeout;  

    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));    

    if(HAL_ADC_Start(hadc) != HAL_OK)  return HAL_ERROR; 
    if(!pData)  return HAL_ERROR;

    hadc->AdcResults = pData;
    uiTimeout = Timeout;

    while(Length)
    {
        tmp_hal_status = hadc->Instance->SR;
        if(tmp_hal_status & ADC_SR_JEOC)
        {
            HAL_ADCEx_InjectedGetValue(hadc,InjectedRank);
            hadc->Instance->SR = ADC_SR_JEOC;
            hadc->AdcResults++;
            Length--;
        }

        if(tmp_hal_status & ADC_SR_OVERF)
        {
            hadc->Instance->SR = ADC_SR_OVERF;
        }        
        if(tmp_hal_status & ADC_SR_JEOG)
        {
            hadc->Instance->SR = ADC_SR_JEOG;
            break;
        }

        if(uiTimeout)
        {
            uiTimeout--;
            if(uiTimeout == 0)
            {
                return HAL_TIMEOUT;
            }
        }
    }

    return HAL_OK;
}

 /******************************************************************************
* @brief:  Enable ADC, start conversion of regular group and transfer result through DMA
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*          the configuration information for the specified ADC.
* @param:  pData : Destination Buffer address. 
* @param:  Length : Number of data to be transferred from ADC peripheral to memory. 
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
    HAL_StatusTypeDef tmp_hal_status;

    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));

    /* Specific case for first call occurrence of this function (DMA transfer */
    /* not activated and ADC disabled), DMA transfer must be activated        */
    /* with ADC disabled.                                                     */
    if (READ_BIT(hadc->Instance->CR1,ADC_CR1_DMA) == 0UL)
    {
        if(READ_BIT(hadc->Instance->CR2, ADC_CR2_EN))
        {
            /* Disable ADC */
            CLEAR_BIT(hadc->Instance->CR2, ADC_CR2_EN);
        }

        /* Enable ADC DMA mode */
        SET_BIT(hadc->Instance->CR1,ADC_CR1_DMA);
    }

    /* Enable the ADC peripheral */
    SET_BIT(hadc->Instance->CR2, ADC_CR2_EN);

    /* Clear the SR register */
    hadc->Instance->SR = (ADC_SR_AWD | ADC_SR_JEOG | ADC_SR_JEOC | ADC_SR_OVERF | \
                            ADC_SR_EOG  | ADC_SR_EOC | ADC_SR_EOSMP | ADC_SR_ADRDY);      

    /* Disable all interruptions before enabling the desired ones */
    hadc->Instance->IE &= ~(ADC_IE_EOSMPIE | ADC_IE_EOCIE | ADC_IE_EOGIE | ADC_IE_OVERFIE | \
                            ADC_IE_JEOCIE | ADC_IE_JEOGIE | ADC_IE_AWDIE);  

    /* Start the DMA channel */
    tmp_hal_status = HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&hadc->Instance->DR, (uint32_t)pData, Length);

    /* Return function status */
    return tmp_hal_status;
}

/******************************************************************************
* @brief:  Configures the ADC multi-mode
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*          the configuration information for the specified ADC.
* @param:  multimode:  pointer to an ADC_MultiModeTypeDef structure that contains 
*                     the configuration information for  multimode.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef* hadc, ADC_MultiModeTypeDef* multimode)
{
    ADC_Common_TypeDef *tmpADC_Common;
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_ADC_MODE(multimode->Mode));
    assert_param(IS_ADC_DMA_ACCESS_MODE(multimode->DMAAccessMode));
    assert_param(IS_ADC_SAMPLING_DELAY(multimode->TwoSamplingDelay));
    

    if(hadc->Instance == ADC3)
    {
        tmpADC_Common = ADC3_COMMON;
    } 
    else
    {
        tmpADC_Common = ADC12_COMMON;
    } 

    /* Set ADC mode */
    tmpADC_Common->CCR &= ~(ADC_CCR_DUALMOD_Msk);
    tmpADC_Common->CCR |= multimode->Mode << ADC_CCR_DUALMOD_Pos;

    /* Set the ADC DMA access mode */
    tmpADC_Common->CCR &= ~(ADC_CCR_DMADUAL_Msk);
    tmpADC_Common->CCR |= multimode->DMAAccessMode << ADC_CCR_DMADUAL_Pos;

    /* Set delay between two sampling phases */
    tmpADC_Common->CCR &= ~(ADC_CCR_DELAY_Msk);
    tmpADC_Common->CCR |= multimode->TwoSamplingDelay << ADC_CCR_DELAY_Pos;


    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
* @brief:  Enables ADC DMA request after last transfer (Multi-ADC mode) and enables ADC peripheral
*          This function must be used only with the ADC master.   
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*          the configuration information for the specified ADC.
* @param:  pData:  Pointer to buffer in which transferred from ADC peripheral to memory will be stored. 
* @param:  Length: The length of data to be transferred from ADC peripheral to memory. 
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
    HAL_StatusTypeDef tmp_hal_status;
    ADC_Common_TypeDef *tmpADC_Common;
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    
    if(hadc->Instance == ADC3)
    {
        tmpADC_Common = ADC3_COMMON;
    } 
    else
    {
        tmpADC_Common = ADC12_COMMON;
    } 

    /* Specific case for first call occurrence of this function (DMA transfer */
    /* not activated and ADC disabled), DMA transfer must be activated        */
    /* with ADC disabled.                                                     */
    if (READ_BIT(hadc->Instance->CR1,ADC_CR1_DMA) == 0UL)
    {
        if(READ_BIT(hadc->Instance->CR2, ADC_CR2_EN))
        {
            /* Disable ADC */
            CLEAR_BIT(hadc->Instance->CR2, ADC_CR2_EN);
        }

        /* Enable ADC DMA mode */
        SET_BIT(hadc->Instance->CR1,ADC_CR1_DMA);
    }

    /* Enable the ADC peripheral */
    SET_BIT(hadc->Instance->CR2, ADC_CR2_EN);

    /* Clear the SR register */
    hadc->Instance->SR = (ADC_SR_AWD | ADC_SR_JEOG | ADC_SR_JEOC | ADC_SR_OVERF | \
                            ADC_SR_EOG  | ADC_SR_EOC | ADC_SR_EOSMP | ADC_SR_ADRDY);      

    /* Disable all interruptions before enabling the desired ones */
    hadc->Instance->IE &= ~(ADC_IE_EOSMPIE | ADC_IE_EOCIE | ADC_IE_EOGIE | \
                                ADC_IE_OVERFIE | ADC_IE_JEOCIE | ADC_IE_JEOGIE | ADC_IE_AWDIE);  

    /* Start the DMA channel */
    tmp_hal_status = HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&tmpADC_Common->CDR, (uint32_t)pData, Length);

    /* Return function status */
    return tmp_hal_status;

}


/******************************************************************************
* @brief:  Config the analog watchdog.   
* @param:  hadc: pointer to a ADC_HandleTypeDef structure that contains
*               the configuration information for the specified ADC.
* @param:  AnalogWDGConfig : pointer to a ADC_AnalogWDGConfTypeDef structure that contains
*               the configuration information for ADC analog watchdog. 
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig)
{                                 
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(hadc->Instance));
    assert_param(IS_FUNCTIONAL_STATE(hadc->Init.AnalogWDGEn));
    assert_param(IS_ADC_CHANNEL(AnalogWDGConfig->RegularChannel));
    assert_param(IS_ADC_CHANNEL(AnalogWDGConfig->InjectChannel));
    assert_param(IS_ADC_ANALOG_WATCHDOG(AnalogWDGConfig->WatchdogMode));
    assert_param(IS_ADC_THRESHOLD(AnalogWDGConfig->HighThreshold));
    assert_param(IS_ADC_THRESHOLD(AnalogWDGConfig->LowThreshold));
    assert_param(IS_FUNCTIONAL_STATE(AnalogWDGConfig->ITMode));
    
    
    if (hadc->Init.AnalogWDGEn)
    {
        /* Clear AWDEN, JAWDEN and AWDSGL bits */
        hadc->Instance->CR1 &= (~(ADC_CR1_AWDSGL_Msk | ADC_CR1_JAWDEN_Msk | ADC_CR1_AWDEN_Msk));
        
        /* Set the analog watchdog enable mode */
        hadc->Instance->CR1 |= AnalogWDGConfig->WatchdogMode;
        
        /* Configure ADC analog watchdog interrupt */
        if(AnalogWDGConfig->ITMode)
        {
            hadc->Instance->IE |= ADC_IE_AWDIE;
        }
        else
        {
            hadc->Instance->IE &= ~ADC_IE_AWDIE;
        }
       
        if(AnalogWDGConfig->WatchdogMode & ADC_CR1_AWDSGL) 
        {
            /* Select the analog watchdog regular channel */
            if(AnalogWDGConfig->WatchdogMode & ADC_CR1_AWDEN)
            {
                /* Clear AWDCH bits */
                hadc->Instance->CR1 &= (~ADC_CR1_AWDCH_Msk);
                hadc->Instance->CR1 |= AnalogWDGConfig->RegularChannel;
            }
            /* Select the analog watchdog inject channel */
            if(AnalogWDGConfig->WatchdogMode & ADC_CR1_JAWDEN)
            {
                /* Clear AWDCH bits */
                hadc->Instance->CR1 &= (~ADC_CR1_AWDJCH_Msk);
                hadc->Instance->CR1 |= (AnalogWDGConfig->InjectChannel << ADC_CR1_AWDJCH_Pos);                
            }
        }
    }
    
    if(AnalogWDGConfig->Diff)
    {
        hadc->Instance->HTR = AnalogWDGConfig->HighThreshold<<16;
        hadc->Instance->LTR = AnalogWDGConfig->LowThreshold<<16;
    }
    else
    {
        hadc->Instance->HTR = AnalogWDGConfig->HighThreshold;
        hadc->Instance->LTR = AnalogWDGConfig->LowThreshold;
    }
    
    /* Return function status */
    return HAL_OK;
}


/******************************************************************************
* @brief:  Checks whether the specified ADC flag is set or not.
* @param:  ADCx: where x can be 1/2/3 to select the ADC peripheral.
* @param:  ADC_FLAG: specifies the flag to check.                                               
* @return: The new state of ADC_FLAG (SET or RESET).
******************************************************************************/
FlagStatus HAL_ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(ADCx));
    assert_param(IS_ADC_FLAG(ADC_FLAG));

    /* Check the status of the specified ADC flag */
    if ((ADCx->SR & ADC_FLAG) != RESET)
    {
        /* ADC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_FLAG status */
    return  bitstatus;
}

/******************************************************************************
* @brief:  Clears the ADCx's pending flags.
* @param:  ADCx: where x can be 1/2/3 to select the ADC peripheral.
* @param:  ADC_FLAG: specifies the flag to clear.                       
* @return: None
******************************************************************************/
void HAL_ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(ADCx));
    assert_param(IS_ADC_FLAG(ADC_FLAG));

    /* Clear the selected ADC flags */
    ADCx->SR = ADC_FLAG;
}


/******************************************************************************
* @brief:  Enables or disables the specified ADC interrupts.
* @param:  ADCx: where x can be 1/2/3 to select the ADC peripheral.
* @param:  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled.                   
* @param:  NewState: new state of the specified ADC interrupts.
*          This parameter can be: ENABLE or DISABLE.
* @return: None.
******************************************************************************/
void HAL_ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState)  
{
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_IT_FLAG(ADC_IT));    

    if (NewState != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        ADCx->IE |= ADC_IT;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        ADCx->IE &= (~ADC_IT);
    }
}

/******************************************************************************
* @brief:  Checks whether the specified ADC interrupt has occurred or not.
* @param:  ADCx: where x can be 1/2/3 to select the ADC peripheral.
* @param:  ADC_IT: specifies the ADC interrupt source to check.                       
* @return: The new state of ADC_FLAG (SET or RESET).
******************************************************************************/
ITStatus HAL_ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(ADCx));
    assert_param(IS_ADC_IT_FLAG(ADC_IT));

    /* Get the ADC_IT enable bit status */
    enablestatus = (ADCx->IE & ADC_IT) ;

    /* Check the status of the specified ADC interrupt */
    if (((ADCx->SR & ADC_IT) != RESET) && enablestatus)
    {
        /* ADC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_IT is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_IT status */
    return  bitstatus;
}

/******************************************************************************
* @brief:  Clears the ADC's interrupt pending bits.
* @param:  ADCx: where x can be 1/2/3 to select the ADC peripheral.
* @param:  ADC_IT: specifies the ADC interrupt pending bit to clear.
* @return: none
******************************************************************************/
void HAL_ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT)
{
    /* Check the parameters */
    assert_param(IS_ADC_INSTANCE(ADCx));
    assert_param(IS_ADC_IT_FLAG(ADC_IT));
    
    if((ADCx->IE & ADC_IT)!= RESET)
    {
        /* Clear the interrupt pending bits in the RTC_SR register */
        ADCx->SR = ADC_IT;
    } 
}

#endif



