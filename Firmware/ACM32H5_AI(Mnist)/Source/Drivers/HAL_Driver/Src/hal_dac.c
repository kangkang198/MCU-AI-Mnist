/******************************************************************************
* @file      : hal_dac.c
* @version   : 1.0
* @date      : 2022.10.29
* @brief     : DAC HAL module driver
******************************************************************************/
#include "hal_dac.h" 

#ifdef HAL_DAC_MODULE_ENABLED
/******************************************************************************
* @brief : This function uses the interruption of DMA  underrun.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @return: none
******************************************************************************/
__weak void HAL_DAC_IRQHandler(DAC_HandleTypeDef *hdac)
{
    if((hdac->Instance->SR & DAC_SR_DMAUDR1) == DAC_SR_DMAUDR1 
        || (hdac->Instance->SR & DAC_SR_DMAUDR2) == DAC_SR_DMAUDR2)
    {
//        printfS("DMA underrun happened\r\n");
        //clear the DMA underrun
        hdac->Instance->SR |= DAC_SR_DMAUDR1 | DAC_SR_DMAUDR2;        
    }
}

/******************************************************************************
* @brief : Initialize the DAC MSP.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @return: none
******************************************************************************/
__weak void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac)
{
    /* NOTE : This function should not be modified, when the callback is needed,
    the HAL_DAC_MspInit can be implemented in the user file
    */
    UNUSED(hdac);
}

/******************************************************************************
* @brief : DAC MSP De-Initialization.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @return: none
******************************************************************************/
void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac)
{
    /* 
    NOTE : This function should be modified by the user.
    the HAL_DAC_MspDeInit can be implemented in the user file.
    */
    UNUSED(hdac); 

}

/******************************************************************************
* @brief : Initializes the CAN peripheral according to the specified  parameters in the DAC_HandleTypeDef.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef *hdac)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));

    HAL_DAC_MspInit(hdac);
    
    return HAL_OK;
}

/******************************************************************************
* @brief : Deinitialize the DAC peripheral registers to their default reset values.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DAC_DeInit(DAC_HandleTypeDef* hdac)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    
    HAL_DAC_MspDeInit(hdac);

    return HAL_OK;
}

/******************************************************************************
* @brief : Configures the selected DAC channel.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : sConfig : DAC configuration structure
* @param : Channel : This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DAC_ConfigChannel(DAC_HandleTypeDef* hdac, DAC_ChannelConfTypeDef* sConfig, uint32_t Channel)
{
    uint32_t tmpreg1, tmpreg2;
    uint32_t tickstart = 0U;
    uint32_t ConnectOnChipPeripheral=0U;
    uint32_t connectOnChip;
    /* Check the DAC parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    
    assert_param(IS_DAC_TRIGGER(sConfig->DAC_Trigger));
    assert_param(IS_DAC_TRIGGER(sConfig->SawtoothStepTrigger));

    assert_param(IS_DAC_OUTPUT_BUFFER_STATE(sConfig->DAC_OutputBuffer));
    assert_param(IS_DAC_TRIMMING(sConfig->DAC_UserTrimming));
    if ((sConfig->DAC_UserTrimming) == DAC_TRIMMING_USER)
    {
        assert_param(IS_DAC_TRIMMINGVALUE(sConfig->DAC_TrimmingValue));
    }
    assert_param(IS_DAC_SAMPLEANDHOLD(sConfig->DAC_SampleAndHold));

    if(sConfig->DAC_OutputBuffer == DAC_OUTPUTBUFFER_ENABLE)
    {
         /* output buffer on */
        assert_param(IS_DAC_CHIP_CONNECTION_BUFON(sConfig->DAC_ConnectOnChipPeripheral));
    }
    else
    {
        /* output buffer off */
        if((sConfig->DAC_SampleAndHold) == DAC_SAMPLEANDHOLD_ENABLE)
        {
            /* Sample and hold mode */
            assert_param(IS_DAC_CHIP_CONNECTION_SHMODE_BUFOFF(sConfig->DAC_ConnectOnChipPeripheral));
            
            assert_param(IS_DAC_SAMPLETIME(sConfig->DAC_SampleAndHoldConfig.DAC_SampleTime));
            assert_param(IS_DAC_HOLDTIME(sConfig->DAC_SampleAndHoldConfig.DAC_HoldTime));
            assert_param(IS_DAC_REFRESHTIME(sConfig->DAC_SampleAndHoldConfig.DAC_RefreshTime));
        }
        else
        {
            /* Normal mode */
             assert_param(IS_DAC_CHIP_CONNECTION_NORMALMODE_BUFOFF(sConfig->DAC_ConnectOnChipPeripheral));
        }
    }
    
    
    assert_param(IS_DAC_CHANNEL(Channel));

    /* ## sample, hold, refresh ---------------------------------------------------------- */
    if (sConfig->DAC_SampleAndHold == DAC_SAMPLEANDHOLD_ENABLE)
    /* Sample on old configuration */
    {
        /* SampleTime */
        if (Channel == DAC_CHANNEL_1)
        {
            hdac->Instance->SHSR1 = sConfig->DAC_SampleAndHoldConfig.DAC_SampleTime;
        }
        else /* Channel 2 */
        {
            hdac->Instance->SHSR2 = sConfig->DAC_SampleAndHoldConfig.DAC_SampleTime;
        }

        /* HoldTime */
        MODIFY_REG(hdac->Instance->SHHR, DAC_SHHR_THOLD1 << (Channel & 0x10UL), (sConfig->DAC_SampleAndHoldConfig.DAC_HoldTime) << (Channel & 0x10UL));
        /* RefreshTime */
        MODIFY_REG(hdac->Instance->SHRR, DAC_SHRR_TREFRESH1 << (Channel & 0x10UL), (sConfig->DAC_SampleAndHoldConfig.DAC_RefreshTime) << (Channel & 0x10UL));
    }

    /* ## CCR---------------------------------------------------------------------------- */
    if (sConfig->DAC_UserTrimming == DAC_TRIMMING_USER)
    /* USER TRIMMING */
    {
        /* Get the DAC CCR value */
        tmpreg1 = hdac->Instance->CCR;
        /* Clear trimming value */
        tmpreg1 &= ~(((uint32_t)(DAC_CCR_OTRIM1)) << (Channel & 0x10UL));
        /* Configure for the selected trimming offset */
        tmpreg2 = sConfig->DAC_TrimmingValue;
        /* Calculate CCR register value depending on DAC_Channel */
        tmpreg1 |= tmpreg2 << (Channel & 0x10UL);
        /* Write to DAC CCR */
        hdac->Instance->CCR = tmpreg1;
    }
    else
    {
        /*  factory trimming in NVR,read to DAC_CCR */
        uint8_t trim_val;
        HAL_StatusTypeDef ret;
        if(hdac->Instance == DAC1)
            ret = HAL_EFUSE_ReadByte(EFUSE1, 0x76 + (Channel >> 4), &trim_val, 100000);
        else
            ret = HAL_EFUSE_ReadByte(EFUSE1, 0x78 + (Channel >> 4), &trim_val, 100000);
        
        if(ret == HAL_OK)
            MODIFY_REG(hdac->Instance->CCR, DAC_CCR_OTRIM1 << (Channel & 0x10UL), trim_val << (Channel & 0x10UL));
    }

    /* ## MCR---------------------------------------------------------------------------- */
    /* Get the DAC MCR value */
    tmpreg1 = hdac->Instance->MCR;
    /* Clear DAC_MCR_MODEx bits */
    tmpreg1 &= ~(((uint32_t)(DAC_MCR_MODE1)) << (Channel & 0x10UL));
    /* Configure for the selected DAC channel: mode, buffer output & on chip peripheral connect */

    if (sConfig->DAC_ConnectOnChipPeripheral == DAC_CHIPCONNECT_EXTERNAL)
    {
        connectOnChip = 0x00000000UL;
    }
    else if (sConfig->DAC_ConnectOnChipPeripheral == DAC_CHIPCONNECT_INTERNAL)
    {
        connectOnChip = DAC_MCR_MODE1_0;
    }
    else /* (sConfig->DAC_ConnectOnChipPeripheral == DAC_CHIPCONNECT_BOTH) */
    {
        if(sConfig->DAC_SampleAndHold == DAC_SAMPLEANDHOLD_ENABLE)
        {
            if (sConfig->DAC_OutputBuffer == DAC_OUTPUTBUFFER_ENABLE)
            {
                connectOnChip = DAC_MCR_MODE1_0;
            }
            else
            {
                connectOnChip = 0x00000000UL;
            }
        }
        else
        {
            connectOnChip = DAC_MCR_MODE1_0;
        }
    }

    tmpreg2 = (sConfig->DAC_SampleAndHold | sConfig->DAC_OutputBuffer | connectOnChip); 
    /* Clear DAC_MCR_DMADOUBLEx */
    tmpreg1 &= ~(((uint32_t)(DAC_MCR_DMADOUBLE1)) << (Channel & 0x10UL));
    /* Configure for the selected DAC channel: DMA double data mode */
    tmpreg2 |= (sConfig->DAC_DMADoubleDataMode == ENABLE) ? DAC_MCR_DMADOUBLE1 : 0UL;
    /* Clear DAC_MCR_SINFORMATx */
    tmpreg1 &= ~(((uint32_t)(DAC_MCR_SINFORMAT1)) << (Channel & 0x10UL));
    /* Configure for the selected DAC channel: Signed format */
    tmpreg2 |= (sConfig->DAC_SignedFormat == ENABLE) ? DAC_MCR_SINFORMAT1 : 0UL;

    /* Calculate MCR register value depending on DAC_Channel */
    tmpreg1 |= tmpreg2 << (Channel & 0x10UL);
    /* Write to DAC MCR */
    hdac->Instance->MCR = tmpreg1;

    /* ## CR ---------------------------------------------------------------------------- */
    /* DAC in normal operating mode hence clear DAC Calibraion bit DAC_CR_CENx */
    CLEAR_BIT(hdac->Instance->CR, DAC_CR_CEN1 << (Channel & 0x10UL));

    /* Get the DAC CR value */
    tmpreg1 = hdac->Instance->CR;
    /* Clear TENx, TSELx, WAVEx and MAMPx bits */
    tmpreg1 &= ~(((uint32_t)(DAC_CR_MAMP1 | DAC_CR_WAVE1 | DAC_CR_TSEL1 | DAC_CR_TEN1)) << (Channel & 0x10UL));
    /* Configure for the selected DAC channel: trigger */
    /* Set TSELx and TENx bits according to DAC_Trigger value */    
    tmpreg2 = sConfig->DAC_Trigger;
    /* Calculate CR register value depending on DAC_Channel */
    tmpreg1 |= tmpreg2 << (Channel & 0x10UL);
    /* Write to DAC CR */
    hdac->Instance->CR = tmpreg1;

    /* Disable wave generation */
    hdac->Instance->CR &= ~(DAC_CR_WAVE1 << (Channel & 0x10UL));
     
    /* ## STMODR---------------------------------------------------------------------------- */

    /* Set STRSTTRIGSELx and STINCTRIGSELx bits according to SawtoothResetTrigger & SawtoothStepTrigger values */
    tmpreg2 = ((sConfig->SawtoothResetTrigger & DAC_CR_TSEL1) >> DAC_CR_TSEL1_Pos) << DAC_STMODR_STRSTTRIGSEL1_Pos;
    tmpreg2 |= ((sConfig->SawtoothStepTrigger & DAC_CR_TSEL1) >> DAC_CR_TSEL1_Pos) << DAC_STMODR_STINCTRIGSEL1_Pos;
    
    /* Modify STMODR register value depending on DAC_Channel */
    MODIFY_REG(hdac->Instance->STMODR, (DAC_STMODR_STINCTRIGSEL1 | DAC_STMODR_STRSTTRIGSEL1) << (Channel & 0x10UL), tmpreg2 << (Channel & 0x10UL));
   
    /* Return function status */
    return HAL_OK;  
}

/******************************************************************************
* @brief : Enables DAC and starts conversion of channel.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel : This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef *hdac, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel)); 
    uint32_t tmp1 = 0U, tmp2 = 0U;

    if (Channel == DAC_CHANNEL_1)
    {
        hdac->Instance->CR|=DAC_CR_EN1;  
        tmp1 = hdac->Instance->CR & DAC_CR_TEN1;
        tmp2 = hdac->Instance->CR & DAC_CR_TSEL1;
        /* Check if software trigger enabled */
        if ((hdac->Instance->CR & (DAC_CR_TEN1 | DAC_CR_TSEL1)) == DAC_TRIGGER_SOFTWARE)
        {
            /* Enable the selected DAC software conversion */
            hdac->Instance->SWTRIGR|=DAC_SWTRIGR_SWTRIG1;
        }
    }
    else
    {
        hdac->Instance->CR|=DAC_CR_EN2; 
        tmp1 = hdac->Instance->CR & DAC_CR_TEN2;
        tmp2 = hdac->Instance->CR & DAC_CR_TSEL2;    
        /* Check if software trigger enabled */
        if ((hdac->Instance->CR & (DAC_CR_TEN2 | DAC_CR_TSEL2)) == (DAC_TRIGGER_SOFTWARE << (Channel & 0x10UL)))
        {
            /* Enable the selected DAC software conversion */
            hdac->Instance->SWTRIGR|=DAC_SWTRIGR_SWTRIG2;
        }
    }
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
* @brief : Disables DAC and stop conversion of channel.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel : This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel)); 

    /* Disable the Peripheral */
    if (Channel == DAC_CHANNEL_1)
    {
        hdac->Instance->CR &= ~DAC_CR_EN1;  
    }
    else
    {
        hdac->Instance->CR &= ~DAC_CR_EN2;  
    }

    /* Return function status */
    return HAL_OK;
}

#ifdef HAL_DMA_MODULE_ENABLED
/******************************************************************************
* @brief : Enables DAC and starts conversion of channel.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel : This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* @param : pData: The destination peripheral Buffer address.
* @param : Length: The length of data to be transferred from memory to DAC peripheral
* @param : Alignment: Specifies the data alignment for DAC channel.This parameter can be one of the following values:
*          @arg DAC_ALIGN_8B_R   @arg DAC_ALIGN_12B_L   @arg DAC_ALIGN_12B_R  
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t *pData, uint32_t Length, uint32_t Alignment)
{
    HAL_StatusTypeDef status;
    uint32_t DstAddr = 0U;
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel)); 
    assert_param(IS_DAC_ALIGN(Alignment));  

    if (Channel == DAC_CHANNEL_1)
    {
        /* Enable the DAC DMA underrun interrupt */
        /* Enable the selected DAC channel2 DMA request */
        hdac->Instance->CR |= DAC_CR_EN1 | DAC_CR_DMAEN1 | DAC_CR_DMAUDIE1;   
        /* Case of use of channel 1 */
        switch (Alignment)
        {
            case DAC_ALIGN_12B_R:
                /* Get DHR12R1 address */
                DstAddr = (uint32_t)&hdac->Instance->DHR12R1;
            break;
            case DAC_ALIGN_12B_L:
                /* Get DHR12L1 address */
                DstAddr = (uint32_t)&hdac->Instance->DHR12L1;
            break;
            case DAC_ALIGN_8B_R:
                /* Get DHR8R1 address */
                DstAddr = (uint32_t)&hdac->Instance->DHR8R1;
            break;
            default:
            break;
        }
        status = HAL_DMA_Start_IT(hdac->DMA_Handle1, (uint32_t)pData, DstAddr, Length); 
    }
    else if(Channel == DAC_CHANNEL_2)
    {
        /* Enable the DAC DMA underrun interrupt */
        /* Enable the selected DAC channel2 DMA request */
        hdac->Instance->CR |= DAC_CR_EN2 | DAC_CR_DMAEN2 | DAC_CR_DMAUDIE2;   

        /* Case of use of channel 1 */
        switch (Alignment)
        {
            case DAC_ALIGN_12B_R:
                /* Get DHR12R1 address */
                DstAddr = (uint32_t)&hdac->Instance->DHR12R2;
            break;
            case DAC_ALIGN_12B_L:
                /* Get DHR12L1 address */
                DstAddr = (uint32_t)&hdac->Instance->DHR12L2;
            break;
            case DAC_ALIGN_8B_R:
                /* Get DHR8R1 address */
                DstAddr = (uint32_t)&hdac->Instance->DHR8R2;
            break;
            default:
            break;
        }
        status = HAL_DMA_Start_IT(hdac->DMA_Handle2, (uint32_t)pData, DstAddr, Length); 
    }
    else/* DualChannel */
    {
        hdac->Instance->CR |= DAC_CR_EN1 | DAC_CR_DMAEN1 | DAC_CR_DMAUDIE1 | DAC_CR_EN2 ;   
        /* Case of use of channel_1 DMA change two DAC channel */
        switch (Alignment)
        {
            case DAC_ALIGN_12B_R:
                /* Get DHR12R1 address */
                DstAddr = (uint32_t)&hdac->Instance->DHR12RD;
            break;
            case DAC_ALIGN_12B_L:
                /* Get DHR12L1 address */
                DstAddr = (uint32_t)&hdac->Instance->DHR12LD;
            break;
            case DAC_ALIGN_8B_R:
                /* Get DHR8R1 address */
                DstAddr = (uint32_t)&hdac->Instance->DHR8RD;
            break;
            default:
            break;
        }
        status = HAL_DMA_Start_IT(hdac->DMA_Handle1, (uint32_t)pData, DstAddr, Length); 
    }
    /* Return function status */
    return status;
}


/******************************************************************************
* @brief : Disables DAC and stop conversion of channel.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel : This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel)); 

    /* Disable the selected DAC channel DMA request */
    /* Disable the DMA Channel */
    /* Channel1 is used */
    if(Channel == DAC_CHANNEL_1)
    { 
        hdac->Instance->CR &= ~DAC_CR_DMAEN1;
        /* Disable the Peripheral */
        hdac->Instance->CR&=~DAC_CR_EN1;
        status = HAL_DMA_Abort(hdac->DMA_Handle1);
    }

    else if(Channel == DAC_CHANNEL_2) /* Channel2 is used for */
    { 
        hdac->Instance->CR &= ~DAC_CR_DMAEN2;
        hdac->Instance->CR&=~DAC_CR_EN2;
        status = HAL_DMA_Abort(hdac->DMA_Handle2); 
    }
    else
    {
        hdac->Instance->CR &= ~DAC_CR_DMAEN1;
        hdac->Instance->CR &= ~DAC_CR_DMAEN2;
        /* Disable the Peripheral */
        hdac->Instance->CR&=~DAC_CR_EN1;
        hdac->Instance->CR&=~DAC_CR_EN2;
        status = HAL_DMA_Abort(hdac->DMA_Handle1) | HAL_DMA_Abort(hdac->DMA_Handle2);
    }

    /* Return function status */
    return status;
}
#endif

/******************************************************************************
* @brief : Set the specified data holding register value for DAC channel.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel : This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* @param : Alignment: Specifies the data alignment for DAC channel.This parameter can be one of the following values:
*          @arg DAC_ALIGN_8B_R   @arg DAC_ALIGN_12B_L   @arg DAC_ALIGN_12B_R 
* @param : Data: The destination peripheral data. 
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel)); 
    assert_param(IS_DAC_ALIGN(Alignment)); 

    tmp = (uint32_t)hdac->Instance;
    if (Channel == DAC_CHANNEL_1)
    {
        tmp += DAC_DHR12R1_ALIGNMENT(Alignment);
    }
    else
    {
        tmp += DAC_DHR12R2_ALIGNMENT(Alignment);
    }

    /* Calculate and set dual DAC data holding register value */
//    if (Alignment == DAC_ALIGN_12B_L)
//    {
//        Data = (uint32_t)Data << 4;
//    }

    /* Set the DAC channel selected data holding register */
    *(__IO uint32_t *) tmp = Data;

    /* Return function status */
    return HAL_OK;
}


/******************************************************************************
* @brief : Set the specified data holding register value for dual DAC channel.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel : This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* @param : Alignment: Specifies the data alignment for DAC channel.This parameter can be one of the following values:
*          @arg DAC_ALIGN_8B_R   @arg DAC_ALIGN_12B_L   @arg DAC_ALIGN_12B_R 
* @param : Data1: The destination peripheral data1. 
* @param : Data2: The destination peripheral data2. 
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DACEx_DualSetValue(DAC_HandleTypeDef *hdac, uint32_t Alignment, uint32_t Data1, uint32_t Data2)
{
    uint32_t data, tmp;
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_ALIGN(Alignment)); 

    /* Calculate and set dual DAC data holding register value */
    if (Alignment == DAC_ALIGN_8B_R)
    {
        data = ((uint32_t)Data2 << 8) | Data1;
    }
    else
    {
        data = ((uint32_t)Data2 << 16) | Data1;
    }
    
    /* DAC 寄存器基地址 */
    tmp = (uint32_t)hdac->Instance;
    /* 根据Alignment，加上对应的寄存器的偏移，如DAC_DHR12RD， DAC_DHR12LD， DAC_DHR8RD  */
    tmp += DAC_DHR12RD_ALIGNMENT(Alignment);

    /* Set the dual DAC selected data holding register */
    *(__IO uint32_t *)tmp = data;

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
* @brief : Returns the last data output value of the selected DAC channel.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel : This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* @return: The selected DAC channel data output value
******************************************************************************/
uint32_t HAL_DAC_GetValue(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel)); 

    /* Returns the DAC channel data output register value */
    if(Channel == DAC_CHANNEL_1)
    {
        return hdac->Instance->DOR1;
    }
    else
    {
        return hdac->Instance->DOR2;
    }

}

/******************************************************************************
* @brief : Returns the last data output value of two DAC channels.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @return: The two DAC channels data output value
******************************************************************************/
uint32_t HAL_DACEx_DualGetValue(DAC_HandleTypeDef *hdac)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    uint32_t tmp = 0U;

    tmp |= hdac->Instance->DOR1;

    tmp |= hdac->Instance->DOR2 << 16U;

    /* Returns the DAC channel data output register value */
    return tmp;
}

/******************************************************************************
* @brief : Enable or disable the selected DAC channel wave generation.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel:The selected DAC channel. his parameter can be one of the following values:
*                      @arg DAC_CHANNEL_1: DAC Channel1 selected
*                      @arg DAC_CHANNEL_2: DAC Channel2 selected
* @param : Amplitude:  Amplitude Select max triangle amplitude. This parameter can be one of the following values:
*                      @arg DAC_TRIANGLEAMPLITUDE_1: Select max triangle amplitude of 1
*                      @arg DAC_TRIANGLEAMPLITUDE_3: Select max triangle amplitude of 3
*                      @arg DAC_TRIANGLEAMPLITUDE_7: Select max triangle amplitude of 7
*                      @arg DAC_TRIANGLEAMPLITUDE_15: Select max triangle amplitude of 15
*                      @arg DAC_TRIANGLEAMPLITUDE_31: Select max triangle amplitude of 31
*                      @arg DAC_TRIANGLEAMPLITUDE_63: Select max triangle amplitude of 63
*                      @arg DAC_TRIANGLEAMPLITUDE_127: Select max triangle amplitude of 127
*                      @arg DAC_TRIANGLEAMPLITUDE_255: Select max triangle amplitude of 255
*                      @arg DAC_TRIANGLEAMPLITUDE_511: Select max triangle amplitude of 511
*                      @arg DAC_TRIANGLEAMPLITUDE_1023: Select max triangle amplitude of 1023
*                      @arg DAC_TRIANGLEAMPLITUDE_2047: Select max triangle amplitude of 2047
*                      @arg DAC_TRIANGLEAMPLITUDE_4095: Select max triangle amplitude of 4095
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude));
    /* Enable the triangle wave generation for the selected DAC channel */
    MODIFY_REG(hdac->Instance->CR, ((DAC_CR_WAVE1) | (DAC_CR_MAMP1)) << (Channel & 0x10UL), (DAC_CR_WAVE_TRIANGLE | Amplitude) << (Channel & 0x10UL));

    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
* @brief : Enable or disable the selected DAC channel wave generation.
* @param : hdac: pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel: The selected DAC channel. his parameter can be one of the following values:
*                      @arg DAC_CHANNEL_1: DAC Channel1 selected
*                      @arg DAC_CHANNEL_2: DAC Channel2 selected
* @param : Amplitude: Amplitude Unmask DAC channel LFSR for noise wave generation. This parameter can be one of the following values:
*                     @arg DAC_LFSRUNMASK_BIT0: Unmask DAC channel LFSR bit0 for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS1_0: Unmask DAC channel LFSR bit[1:0] for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS2_0: Unmask DAC channel LFSR bit[2:0] for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS3_0: Unmask DAC channel LFSR bit[3:0] for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS4_0: Unmask DAC channel LFSR bit[4:0] for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS5_0: Unmask DAC channel LFSR bit[5:0] for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS6_0: Unmask DAC channel LFSR bit[6:0] for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS7_0: Unmask DAC channel LFSR bit[7:0] for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS8_0: Unmask DAC channel LFSR bit[8:0] for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS9_0: Unmask DAC channel LFSR bit[9:0] for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS10_0: Unmask DAC channel LFSR bit[10:0] for noise wave generation
*                     @arg DAC_LFSRUNMASK_BITS11_0: Unmask DAC channel LFSR bit[11:0] for noise wave generation
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude));
    /* Enable the noise wave generation for the selected DAC channel */
    MODIFY_REG(hdac->Instance->CR, ((DAC_CR_WAVE1) | (DAC_CR_MAMP1)) << (Channel & 0x10UL), (DAC_CR_WAVE_NOISE | Amplitude) << (Channel & 0x10UL));
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
* @brief : Run the self calibration of one DAC channel.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : sConfig : sConfig DAC channel configuration structure
* @param : Channel : The selected DAC channel. his parameter can be one of the following values:
*                      @arg DAC_CHANNEL_1: DAC Channel1 selected
*                      @arg DAC_CHANNEL_2: DAC Channel2 selected
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DACEx_SelfCalibrate(DAC_HandleTypeDef *hdac, DAC_ChannelConfTypeDef *sConfig, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel));

    HAL_StatusTypeDef status = HAL_OK;

    __IO uint32_t tmp;
    uint32_t trimmingvalue;
    uint32_t laststatus=0;
    uint32_t nowstatus=0;

    SET_BIT((hdac->Instance->CR), (DAC_CR_EN1 << (Channel & 0x10UL)));
    tmp = (uint32_t)hdac->Instance;
    if (Channel == DAC_CHANNEL_1)
    {
        tmp += DAC_DHR12R1_ALIGNMENT(DAC_ALIGN_12B_R);
    }
    else
    {
        tmp += DAC_DHR12R2_ALIGNMENT(DAC_ALIGN_12B_R);
    }

    *(__IO uint32_t *) tmp = 0x0800U;

    /* Enable the selected DAC channel calibration */
    /* i.e. set DAC_CR_CENx bit */
    SET_BIT((hdac->Instance->CR), (DAC_CR_CEN1 << (Channel & 0x10UL)));

    /* Init trimming counter */
    /* Medium value ,trimmingvalue:0-31(0x1f)*/
    for(trimmingvalue = 0; trimmingvalue < 32; trimmingvalue++)
    {
        /* Set candidate trimming */
        MODIFY_REG(hdac->Instance->CCR, (DAC_CCR_OTRIM1 << (Channel & 0x10UL)), (trimmingvalue << (Channel & 0x10UL)));
        
        HAL_SimpleDelay(50000);
        
        laststatus=nowstatus;
        nowstatus=(hdac->Instance->SR & (DAC_SR_CALFLAG1 << (Channel & 0x10UL)))>>(DAC_SR_CALFLAG1_Pos +Channel);
        /* tOFFTRIMmax delay x ms as per datasheet (electrical characteristics */
        /* i.e. minimum time needed between two calibration steps */
        if (nowstatus == 1 && laststatus == 0)
        {
            break;
        }
    }

    /* Disable the selected DAC channel calibration */
    /* i.e. clear DAC_CR_CENx bit */
    CLEAR_BIT((hdac->Instance->CR), (DAC_CR_CEN1 << (Channel & 0x10UL)));

    /* Disable the selected DAC channel */
    CLEAR_BIT((hdac->Instance->CR), (DAC_CR_EN1 << (Channel & 0x10UL)));

    sConfig->DAC_TrimmingValue = trimmingvalue;
    sConfig->DAC_UserTrimming = DAC_TRIMMING_USER;

    return status;
}



/******************************************************************************
* @brief : Set the trimming mode and trimming value (user trimming mode applied).
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : sConfig : sConfig DAC channel configuration structure
* @param : Channel : The selected DAC channel. his parameter can be one of the following values:
*                      @arg DAC_CHANNEL_1: DAC Channel1 selected
*                      @arg DAC_CHANNEL_2: DAC Channel2 selected
* @param : NewTrimmingValue: DAC new trimming value
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DACEx_SetUserTrimming(DAC_HandleTypeDef *hdac, DAC_ChannelConfTypeDef *sConfig, uint32_t Channel, uint32_t NewTrimmingValue)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_Calibration_TRIM(NewTrimmingValue));

    /* Check the DAC handle allocation */
    if (hdac == NULL)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Set new trimming */
        MODIFY_REG(hdac->Instance->CCR, (DAC_CCR_OTRIM1 << (Channel & 0x10UL)), (NewTrimmingValue << (Channel & 0x10UL)));
        /* Update trimming mode */
        sConfig->DAC_UserTrimming = DAC_TRIMMING_USER;
        sConfig->DAC_TrimmingValue = NewTrimmingValue;
    }
    return status;
}



/******************************************************************************
* @brief : Return the DAC trimming value.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel : The selected DAC channel. his parameter can be one of the following values:
*                      @arg DAC_CHANNEL_1: DAC Channel1 selected
*                      @arg DAC_CHANNEL_2: DAC Channel2 selected
* @return: Trimming value : range: 0->31
******************************************************************************/
uint32_t HAL_DACEx_GetTrimOffset(DAC_HandleTypeDef *hdac, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel));

    /* Retrieve trimming  */
    return ((hdac->Instance->CCR & (DAC_CCR_OTRIM1 << (Channel & 0x10UL))) >> (Channel & 0x10UL));
}

/******************************************************************************
* @brief : Enables or disables the selected DAC channel Sawtooth wave generation.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel : The selected DAC channel. his parameter can be one of the following values:
*                      @arg DAC_CHANNEL_1: DAC Channel1 selected
*                      @arg DAC_CHANNEL_2: DAC Channel2 selected
* @param : Polarity : Sawtooth direction. @arg DAC_SAWTOOTH_POLARITY_DECREMENT, @arg DAC_SAWTOOTH_POLARITY_INCREMENT
* @param : ResetData : Sawtooth reset value
* @param : StepData : Sawtooth increasing/decreasing value
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DACEx_SawtoothWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Polarity, uint32_t ResetData, uint32_t StepData)
{
    /* Check the parameters */
    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel));
    assert_param(IS_DAC_SAWTOOTH_POLARITY(Polarity));

    if (Channel == DAC_CHANNEL_1)
    {
        /* Configure the sawtooth wave generation data parameters */
        MODIFY_REG(hdac->Instance->STR1, DAC_STR1_STINCDATA1 | DAC_STR1_STDIR1 | DAC_STR1_STRSTDATA1, \
        (StepData << DAC_STR1_STINCDATA1_Pos) | Polarity | (ResetData << DAC_STR1_STRSTDATA1_Pos));
    }
    else
    {
        /* Configure the sawtooth wave generation data parameters */
        MODIFY_REG(hdac->Instance->STR2, DAC_STR2_STINCDATA2 | DAC_STR2_STDIR2 | DAC_STR2_STRSTDATA2, \
        (StepData << DAC_STR2_STINCDATA2_Pos) | Polarity | (ResetData << DAC_STR2_STRSTDATA2_Pos));
    }

    /* Enable the sawtooth wave generation for the selected DAC channel */
    MODIFY_REG(hdac->Instance->CR, (DAC_CR_WAVE1) << (Channel & 0x10UL), (uint32_t)(DAC_CR_WAVE_SAWTOOTH) << (Channel & 0x10UL));
    
    /* Return function status */
    return HAL_OK;
}

/******************************************************************************
* @brief : DAC channel Sawtooth wave Reset by software.
* @param : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module.
* @param : Channel : The selected DAC channel. his parameter can be one of the following values:
*                      @arg DAC_CHANNEL_1: DAC Channel1 selected
*                      @arg DAC_CHANNEL_2: DAC Channel2 selected
* @return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_DACEx_SawtoothWaveDataResetBySoftware(DAC_HandleTypeDef *hdac, uint32_t Channel)
{
    HAL_StatusTypeDef status = HAL_OK;

    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel));


    if (((hdac->Instance->STMODR >> (Channel & 0x10UL)) & DAC_STMODR_STRSTTRIGSEL1) == 0U /* SW TRIGGER */)
    {
        if (Channel == DAC_CHANNEL_1)
        {
            /* Enable the selected DAC software conversion */
            SET_BIT(hdac->Instance->SWTRIGR, DAC_SWTRIGR_SWTRIG1);
        }
        else
        {
            /* Enable the selected DAC software conversion */
            SET_BIT(hdac->Instance->SWTRIGR, DAC_SWTRIGR_SWTRIG2);
        }
    }
    else
    {
        status = HAL_ERROR;
    }

    /* Return function status */
    return status;
}

/**
  * @brief  Trig sawtooth wave step
  * @note   This function allows to generate step  in sawtooth wave in case of
  *         SW trigger has been configured for this usage.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected (1)
  *
  *         (1) On this STM32 serie, parameter not available on all instances.
  *             Refer to device datasheet for channels availability.
  * @retval HAL status
  */
/*
  该函数是锯齿波软件触发函数
*/
HAL_StatusTypeDef HAL_DACEx_SawtoothWaveDataStep(DAC_HandleTypeDef *hdac, uint32_t Channel)
{
    HAL_StatusTypeDef status = HAL_OK;

    assert_param(IS_DAC_INSTANCE(hdac->Instance));
    assert_param(IS_DAC_CHANNEL(Channel));

    if (((hdac->Instance->STMODR >> (Channel & 0x10UL)) & DAC_STMODR_STINCTRIGSEL1) == 0U /* SW TRIGGER */)
    {

        if (Channel == DAC_CHANNEL_1)
        {
            /* Enable the selected DAC software conversion */
            SET_BIT(hdac->Instance->SWTRIGR, DAC_SWTRIGR_SWTRIGB1);
        }
        else
        {
            /* Enable the selected DAC software conversion */
            SET_BIT(hdac->Instance->SWTRIGR, DAC_SWTRIGR_SWTRIGB2);
        }
    }
    else
    {
        status = HAL_ERROR;
    }

    /* Return function status */
    return status;
}

#endif /* HAL_DAC_MODULE_ENABLED */