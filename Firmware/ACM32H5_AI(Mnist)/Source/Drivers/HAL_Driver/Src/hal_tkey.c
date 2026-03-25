/******************************************************************************
*@file  : hal_tkey.c
*@brief : TKEY HAL module driver.
******************************************************************************/
#include "hal.h" 


#ifdef HAL_TKEY_MODULE_ENABLED


/******************************************************************************
*@brief : TKEY interrupt handler       
*@param : None.
*@return: None
******************************************************************************/
__weak void HAL_TKEY_IRQHandler(void)
{
    /* 
        NOTE: This function should be modified, when the callback is needed
    */
    
    /* For Example */
    if(SET == HAL_TKEY_GetITStatus(TKEY_IT_FLAG_EOC))       //Scanning completed 
    {
        HAL_TKEY_ClearITPendingBit(TKEY_IT_FLAG_EOC);
    }
    
    if(SET == HAL_TKEY_GetITStatus(TKEY_IT_FLAG_YESTOUCH))  //Key touch event has occurred
    {
        HAL_TKEY_ClearITPendingBit(TKEY_IT_FLAG_YESTOUCH);
    }
    
    if(SET == HAL_TKEY_GetITStatus(TKEY_IT_FLAG_TIMEOUT))   //Channel scan timeout
    {
        HAL_TKEY_ClearITPendingBit(TKEY_IT_FLAG_TIMEOUT);
    }
    
    if(SET == HAL_TKEY_GetFlagStatus(TKEY_IT_FLAG_BUSY))    //Channel scan busy
    {
        TKEY->CR |= TKEY_CR_START;
    }
    
    if(SET == HAL_TKEY_GetITStatus(TKEY_IT_FLAG_DONE))      //Comparator flipping completed
    {
        HAL_TKEY_ClearITPendingBit(TKEY_IT_FLAG_DONE);
    }
    
    if(SET == HAL_TKEY_GetITStatus(TKEY_IT_FLAG_CHG))       //Each charge is completed
    {
        HAL_TKEY_ClearITPendingBit(TKEY_IT_FLAG_CHG);
    }
    
    if(SET == HAL_TKEY_GetITStatus(TKEY_IT_FLAG_CHGDONE))   //Charging frequency reaches the set number of times
    {
        HAL_TKEY_ClearITPendingBit(TKEY_IT_FLAG_CHGDONE);
    }
    
    if(SET == HAL_TKEY_GetITStatus(TKEY_IT_FLAG_MEOC))      //Mutual inductance mode channel scan completed
    {
        HAL_TKEY_ClearITPendingBit(TKEY_IT_FLAG_MEOC);
    }
    
}


/******************************************************************************
*@brief : Initialize the TKEY MSP: GPIO, CLK, NVIC        
*@param : htkey: a pointer of TKEY_HandleTypeDef structure which contains 
*                the configuration information for the specified TKEY.
*@return: None
******************************************************************************/
__weak void HAL_TKEY_MspInit(TKEY_HandleTypeDef* htkey)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htkey);
}

/******************************************************************************
*@brief : TKEY De-Initialize the TKEY clock, GPIO, IRQ.       
*@param : htkey: a pointer of TKEY_HandleTypeDef structure which contains 
*                the configuration information for the specified TKEY.
*@return: None
******************************************************************************/
__weak void HAL_TKEY_MspDeInit(TKEY_HandleTypeDef* htkey)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(htkey);
}


/******************************************************************************
*@brief : Initialize the TKEY module with parameters       
*@param : hospi: a pointer of TKEY_HandleTypeDef structure which contains 
*                the configuration information for the specified TKEY.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Init(TKEY_HandleTypeDef* htkey)
{
    uint32_t u32RegTemp;
    
    /* Check the TKEY handle allocation */
    if (htkey == NULL)
    {
        return HAL_ERROR;
    } 

    /* Check TKEY Parameter */
    assert_param(IS_TKEY_MODE(htkey->Init.Mode));
    assert_param(IS_TKEY_WORK_MODE(htkey->Init.WorkMode));
    assert_param(IS_TKEY_SCAN_MODE(htkey->Init.ScanMode));
    assert_param(IS_TKEY_SHIELD(htkey->Init.ShieldEn));
    assert_param(IS_TKEY_FILTER(htkey->Init.FilterNum));
    assert_param(IS_TKEY_VLDO(htkey->Init.Vldo));
    assert_param(IS_TKEY_VREF(htkey->Init.Vref));
    assert_param(IS_TKEY_SPREAD(htkey->Init.SpreadEn));
    assert_param(IS_TKEY_SMAPLE(htkey->Init.SampleNum));    
    assert_param(IS_TKEY_CHANNEL_STATE(htkey->Init.ChannelEn));   
    
    assert_param(IS_TKEY_RADOM_JITTER(htkey->Timing.RandomJitterNum));
    assert_param(IS_TKEY_SCAN_INTERVAL(htkey->Timing.ScanInterval));
    assert_param(IS_TKEY_SCAN_CLK_PRESCALE(htkey->Timing.ScanClkPrescale));
    assert_param(IS_TKEY_SCAN_CLK_SW1HSW2L(htkey->Timing.ScanClkSW1HSW2L));
    assert_param(IS_TKEY_SCAN_CLK_SW1LSW2H(htkey->Timing.ScanClkSW1LSW2H));
    assert_param(IS_TKEY_SCAN_TIMEOUT_PWM_CYCLE(htkey->Timing.TimeoutOrPwmCycle));
    assert_param(IS_TKEY_CSDISCHARGETIME_CMPWAITTIME(htkey->Timing.DischargeTimeOrCMPWaitTime)); 
//    assert_param(IS_TKEY_SCAN_CLK_SOURCE(htkey->Timing.ScanClkSrc));
//    assert_param(IS_TKEY_CTRL_CLK_SOURCE(htkey->Timing.CtrlClkSrc));
    
    /* Init the low level hardware : GPIO, CLOCK, NVIC, DMA */
    HAL_TKEY_MspInit(htkey);
    
    /* Check if the Tkey scan is busy */
    while(TKEY->SR & TKEY_SR_BUSY);
    
    /* disable the Tkey scan */
    TKEY->CR &= ~(TKEY_CR_START); 
       
    /*---------------------------- TKEY CR Configuration -----------------*/
    u32RegTemp = ( htkey->Init.Mode | htkey->Init.WorkMode | htkey->Init.ScanMode | \
                            htkey->Init.ShieldEn | htkey->Init.SpreadEn); 
    if(htkey->Init.SpreadEn == TKEY_SPREAD_ENABLE)
    {
        u32RegTemp |= htkey->Timing.RandomJitterNum;
    }                                 
    TKEY->CR = u32RegTemp;
    
    /*---------------------------- TKEY CFGR1 Configuration -----------------*/
    TKEY->CFGR1 = ( htkey->Init.FilterNum | htkey->Init.SampleNum | htkey->Init.Vldo | htkey->Init.Vref); 
                                                       
    /*---------------------------- TKEY INTVLR Configuration -----------------*/
    TKEY->INTVLR = (htkey->Timing.ScanInterval); 
    
    /*---------------------------- TKEY DIVR Scan CLK div Configuration -----------------*/
    TKEY->DIVR = (TKEY->DIVR & (~TKEY_DIVR_SCANCLKDIV_Msk)) | (htkey->Timing.ScanClkPrescale << TKEY_DIVR_SCANCLKDIV_Pos);     
                          
    /*---------------------------- TKEY SCCR Configuration -----------------*/
    TKEY->SCCR = ((htkey->Timing.ScanClkSW1HSW2L << TKEY_SCCR_SW1H_Pos) | htkey->Timing.ScanClkSW1LSW2H); 
    
    /*---------------------------- TKEY TSETR Configuration -----------------*/
    u32RegTemp = ( htkey->Timing.TimeoutOrPwmCycle<< TKEY_TSETR_TSET_Pos) | (htkey->Timing.DischargeTimeOrCMPWaitTime <<TKEY_TSETR_CST_Pos); 
    TKEY->TSETR = u32RegTemp;
    
    /*---------------------------- TKEY CXENR Configuration -----------------*/
    TKEY->CXENR = (htkey->Init.ChannelEn);

    
    /* Enable channel overall control */
    TKEY->CR |= TKEY_CR_CHEN;     
    
    /* Enable TKEY module */
    TKEY->CR |= TKEY_CR_TKEN;
    
    /* TKEY's internal simulation module requires 10us to stabilize */
    HAL_SimpleDelay(10000);//延迟时间待定
    
    return  HAL_OK;
}

/******************************************************************************
*@brief : De-Initialize the OSPI peripheral       
*@param : hospi: a pointer of OSPI_HandleTypeDef structure which contains 
*                the configuration information for the specified OSPI.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_TKEY_DeInit(TKEY_HandleTypeDef* htkey)
{
    /* Check the TKEY handle allocation */
    if (htkey == NULL)
    {
        return HAL_ERROR;
    }
    
    htkey->Init.Mode = 0;
    htkey->Init.WorkMode = 0;
    htkey->Init.ScanMode = 0;
    htkey->Init.ShieldEn = 0;;
    htkey->Init.FilterNum = 0;
    htkey->Init.Vldo = 0;
    htkey->Init.Vref = 0;
    htkey->Init.SpreadEn = 0;
    htkey->Init.ChannelEn = 0; 

    htkey->Timing.RandomJitterNum = 0;
    htkey->Timing.ScanInterval = 0;
    htkey->Timing.ScanClkPrescale = 0;
    htkey->Timing.ScanClkSW1HSW2L = 0;
    htkey->Timing.ScanClkSW1LSW2H = 0;
    htkey->Timing.TimeoutOrPwmCycle = 0;  
    
    /*Check if the Tkey scan is busy*/
    while(TKEY->SR & TKEY_SR_BUSY);
    
    /*disable the Tkey scan*/
    TKEY->CR &= ~(TKEY_CR_START); 
    
    /*disable the Tkey moudle*/
    TKEY->CR &= ~TKEY_CR_TKEN;

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
    HAL_TKEY_MspDeInit(htkey);
    

    return HAL_OK;
}

/******************************************************************************
*@brief : TKEY module enable or disable      
*@param : NewState: Specify the new state of the TKEY module.
*@return: None
******************************************************************************/
void HAL_TKEY_EnableDisable(uint32_t NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));   

    if (NewState == DISABLE)
    {
        TKEY->CR &= ~TKEY_CR_TKEN;
    }
    else
    {
        TKEY->CR |= TKEY_CR_TKEN;
        HAL_SimpleDelay(10000);//延迟时间待定
    }   
}

/******************************************************************************
*@brief : TKEY start to scan        
*@param : None.
*@return: None
******************************************************************************/
void HAL_TKEY_StartScan(void)
{
    /*Start the Tkey scan*/    
    TKEY->CR |= TKEY_CR_START;
    /* Waiting for START flag to turn to 0 */
    while(TKEY->CR & TKEY_CR_START);  
}


/******************************************************************************
*@brief : TKEY stop to scan        
*@param : None.
*@return: None
******************************************************************************/
void HAL_TKEY_StopScan(void)
{
    /* Waiting for BUSY flag to be 0 when stopping scanning */
    while(TKEY->SR & TKEY_SR_BUSY);
    /*disable the Tkey scan*/
    TKEY->CR &= ~(TKEY_CR_START);    
}

/******************************************************************************
*@brief : Read the count number of the all channels        
*@param : pScanCount : Pointing to the channel scan count buffer.
*@return: HAL status
******************************************************************************/ 
HAL_StatusTypeDef HAL_TKEY_ReadChannelCount(uint16_t *pScanCount)
{
    uint8_t temp;
    uint32_t u32RegTemp;
    
    if(pScanCount == NULL)
    {    
        return HAL_ERROR;
    }
    
    u32RegTemp = TKEY->CXENR;
    
    if(u32RegTemp == 0)
    {
        return HAL_ERROR;
    }
	for(temp = 0; temp < 16; temp++)
	{
		if (u32RegTemp & 0x01)
		{
            *pScanCount++ = TKEY->CH[temp];
		}
		u32RegTemp >>= 1;
		if(u32RegTemp == 0)
        {
			break;
        }
	}
    return HAL_OK;
}

/******************************************************************************
*@brief : Read the count number of the last channel        
*@param : None.
*@return: The scan count result of the last channel or button touch event channel
******************************************************************************/ 
uint16_t HAL_TKEY_ReadLastChannelCount(void)
{ 
    return TKEY->DR;
}

/******************************************************************************
*@brief : Get the scanning channel number in normal mode or 
*         the channel number for scanning timeout
*         get the key touch channel number in automatic mode       
*@param : None.
*@return: channel number
******************************************************************************/ 
uint8_t HAL_TKEY_GetSacnTimeoutAutoChannelNumber(void)
{   
    return ((TKEY->SR & TKEY_SR_CHNUM_Msk)>> TKEY_SR_CHNUM_Pos);
}


/******************************************************************************
*@brief : Parameter configuration for automatic mode        
*@param : pBaseline: Pointing to the channel baseline buffer
*@param : pThreshold: Pointing to the channel threshold buffer
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_TKEY_AutoConfig(TKEY_AutoConfigTypeDef *hauto)
{
    uint8_t temp;
    uint32_t u32RegTemp;
    
    /* Check the parameters */
    assert_param(IS_TKEY_FILTER(hauto->FilterNum));
    
    u32RegTemp = TKEY->CXENR;
    
    if(u32RegTemp == 0)
    {
        return HAL_ERROR;
    }
	for(temp = 0; temp < 16; temp++)
	{
		if (u32RegTemp & 0x01)
		{ 
            /* Set the baseline value for channel x */
            TKEY->CH[temp] = hauto->Baseline[temp];
            
            /* Set the threshold value for channel x */
            TKEY->TH[temp] = hauto->Threshold[temp];
		}
		u32RegTemp >>= 1;
		if(u32RegTemp == 0)
        {
			break;
        }
	}
    
    /* Set hardware filtering times */
    TKEY->CFGR1 = (TKEY->CFGR1 & (~(TKEY_CFGR1_FLTSEL_Msk))) | hauto->FilterNum;

    /* Enable automatic mode */
    TKEY->CR |= TKEY_CR_AUTO;
    
    return HAL_OK;
}


/******************************************************************************
*@brief : CSA mode parameter configuration        
*@param : hcsa: a pointer of TKEY_CSAConfigTypeDef structure which contains 
*                the CSA mode configuration information for the specified TKEY.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_TKEY_CSAConfig(TKEY_CSAConfigTypeDef* hcsa)
{
    /* Check the parameters */
    assert_param(IS_TKEY_CHGNUMDONE(hcsa->ChargeNumDoneEn)); 
    assert_param(IS_TKEY_CHGEACHDONE(hcsa->ChargeEachDoneEN));
    assert_param(IS_TKEY_CSDISCHARGETIME_CMPWAITTIME(hcsa->DischargeTime));
    assert_param(IS_TKEY_COMPFILTERNUM(hcsa->ComparerFilterNum));
    assert_param(IS_TKEY_COMPFILTER(hcsa->ComparerFilterEN));
    assert_param(IS_TKEY_CHARGENUM(hcsa->ChargeNum));
    assert_param(IS_TKEY_CHARGEDONEWAITTIME(hcsa->ChargeDoneWaitTime)); 

    /* Cs capacitor discharge time */
    TKEY->TSETR = (TKEY->TSETR & (~TKEY_TSETR_CST_Msk)) | hcsa->DischargeTime;  
    
    /* Comparator filtering settings */
    if(hcsa->ComparerFilterEN == TKEY_COMPFILTER_ENABLE)
    {
        TKEY->CFLTR = (hcsa->ComparerFilterNum << TKEY_CFLTR_CFLTNUM_Pos | hcsa->ComparerFilterEN);
    }
    else
    {
        TKEY->CFLTR = hcsa->ComparerFilterEN;
    }
    
    /* Charging numbers setting */
    TKEY->NSETR = hcsa->ChargeNum;
    
    /* Set the waiting time after reaching the set number of charges */
    TKEY->TWAITR = hcsa->ChargeDoneWaitTime;
    
    /* Enable charging times to reach the function,  enable each charge to complete the function*/
    TKEY->CR = (TKEY->CR & (~(TKEY_CR_CHGDONEEN_Msk | TKEY_CR_CHGEN_Msk))) | hcsa->ChargeNumDoneEn | hcsa->ChargeEachDoneEN;
    
    return HAL_OK;
}


/******************************************************************************
*@brief : CSD mode parameter configuration        
*@param : hcsd: a pointer of TKEY_CSDConfigTypeDef structure which contains 
*                the CSD mode configuration information for the specified TKEY.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_TKEY_CSDConfig(TKEY_CSDConfigTypeDef* hcsd)
{
    /* Check the parameters */
    assert_param(IS_TKEY_DISMS(hcsd->DischargeMode));
    assert_param(IS_TKEY_PRECHARGE(hcsd->PrechargeEn));
    assert_param(IS_TKEY_DISCHARGECURRENT(hcsd->DischargeCurrent));
    assert_param(IS_TKEY_DISCHARGERES(hcsd->DischargeRes));
    assert_param(IS_TKEY_SAMPLEBITCLKDIV(hcsd->SampleBitClkDiv));
    
    /* Set discharge current and resistance */
    TKEY->CFGR2 = (hcsd->DischargeCurrent << TKEY_CFGR2_IDISSEL_Pos) | (hcsd->DischargeRes);
    
    /* Set clock division for sampling bit streams */
    TKEY->DIVR = (TKEY->DIVR & (~TKEY_DIVR_SMPCLKDIV_Msk)) | hcsd->SampleBitClkDiv;
    
    /* Set discharge mode, enable precharge */
    TKEY->CR = (TKEY->CR & (~(TKEY_CR_DISMS_Msk | TKEY_CR_PCEN_Msk))) | (hcsd->DischargeMode) | (hcsd->PrechargeEn);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Mutual inductance mode parameter configuration        
*@param : hmutual: a pointer of TKEY_MutualConfigTypeDef structure which contains 
*                the CSD Mutual inductance configuration information for the specified TKEY.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_TKEY_MutualConfig(TKEY_MutualConfigTypeDef* hmutual)
{
    /* Check the parameters */
    assert_param(IS_TKEY_MUTUAL_DELAY_TIME(hmutual->MutualDelayTime));
    assert_param(IS_TKEY_MUTUAL_DELAY_STATE(hmutual->MutualDelayEn));
    assert_param(IS_TKEY_MUTUAL_RESET(hmutual->MutualResetEn));
    assert_param(IS_TKEY_MUTUAL_CHANNEL_STATE(hmutual->MutualChannelEn));
    
    /* Disable mutual inductance mode */
    TKEY->MUTUALR &= ~TKEY_MUTUALR_MUTUALEN;
    
    /* clear MTXDLY MTXDLYEN MTXRST bits */   
    TKEY->MUTUALR &= ~(TKEY_MUTUALR_MTXDLY_Msk | TKEY_MUTUALR_MTXDLYEN_Msk | TKEY_MUTUALR_MTXRST_Msk);
    
    /* set MTXDLY MTXDLYEN MTXRST bits */   
    TKEY->MUTUALR |= (hmutual->MutualDelayTime << TKEY_MUTUALR_MTXDLY_Pos) | (hmutual->MutualDelayEn) | (hmutual->MutualResetEn);
    
    /* Enable mutual inductance transmission channel */
    if(hmutual->MutualChannelEn > 0xffff)
    {
        TKEY->TXENR[0] = hmutual->MutualChannelEn & 0xffff;
        TKEY->TXENR[1] = (hmutual->MutualChannelEn >> 16) & 0x3ff;             
    }
    else
    {
        TKEY->TXENR[0] = hmutual->MutualChannelEn;        
    }

    /* Enable mutual inductance mode */
    TKEY->MUTUALR |= TKEY_MUTUALR_MUTUALEN;     
        
    return HAL_OK;
}

/******************************************************************************
*@brief : TKEY mutual inductance mode enable or disable      
*@param : NewState: Specify the new state of the TKEY mutual inductance mode.
*@return: None
******************************************************************************/
void HAL_TKEY_MutualEnableDisable(uint32_t NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));   

    if (NewState == DISABLE)
    {
        TKEY->MUTUALR &= ~TKEY_MUTUALR_MUTUALEN;
    }
    else
    {
        TKEY->MUTUALR |= TKEY_MUTUALR_MUTUALEN; 
    }   
}


/******************************************************************************
*@brief : TKEY automatic mode enable or disable      
*@param : NewState: Specify the new state of the TKEY automatic mode.
*@return: None
******************************************************************************/
void HAL_TKEY_AutoEnableDisable(uint32_t NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));   

    if (NewState == DISABLE)
    {
        TKEY->CR &= ~TKEY_CR_AUTO;
    }
    else
    {
        TKEY->CR |= TKEY_CR_AUTO;
    }   
}

/******************************************************************************
*@brief : Set resistance compensation        
*@param : res: Compensated resistance.
*@return: None
******************************************************************************/
void HAL_TKEY_ResCompensate(uint8_t res)
{
    /* Check the parameters */
    assert_param(IS_TKEY_RESCOMPENSTATE(res));
    TKEY->CFGR1 = (TKEY->CFGR1 & (~TKEY_CFGR1_RCPSEL_Msk)) | (res << TKEY_CFGR1_RCPSEL_Pos); 
}

/******************************************************************************
*@brief : Set capacitance compensation        
*@param : cap: Compensated capacitance.
*@return: None
******************************************************************************/
void HAL_TKEY_CapCompensate(uint8_t cap)
{
    /* Check the parameters */
    assert_param(IS_TKEY_CAPCOMPENSTATE(cap));
    TKEY->CFGR1 = (TKEY->CFGR1 & (~TKEY_CFGR1_CCPSEL_Msk)) | (cap << TKEY_CFGR1_CCPSEL_Pos); 
}


/******************************************************************************
*@brief : Set the interval time between two sets of scans         
*@param : time : the interval time.
*@return: None
******************************************************************************/ 
void HAL_TKEY_ScanIntervalConfig(uint16_t time)
{
    /* Check TKEY Parameter */
    assert_param(IS_TKEY_SCAN_INTERVAL(time));
    /* TKEY INTVLR Configuration */
    TKEY->INTVLR = time; 
}


/******************************************************************************
*@brief : Read the interval time between two sets of scans         
*@param : None.
*@return: the interval time
******************************************************************************/ 
uint16_t HAL_TKEY_ReadScanInterval(void)
{
    return TKEY->INTVLR;
}

/******************************************************************************
*@brief : Enables or disables the specified TKEY interrupts.
*@param : irq: specifies the TKEY interrupt sources to be enabled or disabled.                   
*@param : NewState: new state of the specified TKEY interrupts.
*                   This parameter can be: ENABLE or DISABLE.
*@return: None.
******************************************************************************/
void HAL_TKEY_ITConfig(uint32_t irq, FunctionalState NewState)  
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_TKEY_IT_FLAG(irq));    

    if (NewState != DISABLE)
    {
        /* Enable the selected TKEY interrupts */
        TKEY->IER |= irq;
    }
    else
    {
        /* Disable the selected TKEY interrupts */
        TKEY->IER &= (~irq);
    }
}

/******************************************************************************
*@brief : Checks whether the specified TKEY flag is set or not.
*@param : flag: specifies the flag to check.                                               
*@return: The new state of flag (SET or RESET).
******************************************************************************/
FlagStatus HAL_TKEY_GetFlagStatus(uint32_t flag)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_TKEY_IT_FLAG(flag));

    /* Check the status of the specified TKEY flag */
    if ((TKEY->SR & flag) != RESET)
    {
        /* flag is set */
        bitstatus = SET;
    }
    else
    {
        /* flag is reset */
        bitstatus = RESET;
    }
    /* Return the TKEY_FLAG status */
    return  bitstatus;
}

/******************************************************************************
*@brief : Clears the TKEY's pending flags.
*@param : flag: specifies the flag to clear.                       
*@return: None
******************************************************************************/
void HAL_TKEY_ClearFlag(uint32_t flag)
{
    /* Check the parameters */
    assert_param(IS_TKEY_IT_FLAG(flag));

    /* Clear the selected TKEY flags */
    TKEY->SR = flag;
}

/******************************************************************************
*@brief : Checks whether the specified TKEY interrupt has occurred or not.
*@param : irq: specifies the TKEY interrupt source to check.                       
*@return: The new state of irq (SET or RESET).
******************************************************************************/
ITStatus HAL_TKEY_GetITStatus(uint32_t irq)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* Check the parameters */
    assert_param(IS_TKEY_IT_FLAG(irq));

    /* Get the irq enable bit status */
    enablestatus = (TKEY->IER & irq) ;

    /* Check the status of the specified TKEY interrupt */
    if (((TKEY->SR & irq) != RESET) && enablestatus)
    {
        /* irq is set */
        bitstatus = SET;
    }
    else
    {
        /* irq is reset */
        bitstatus = RESET;
    }
    /* Return the irq status */
    return  bitstatus;
}

/******************************************************************************
*@brief : Clears the TKEY's interrupt pending bits.
*@param : irq: specifies the TKEY interrupt pending bit to clear.
*@return: None
******************************************************************************/
void HAL_TKEY_ClearITPendingBit(uint32_t irq)
{
    /* Check the parameters */
    assert_param(IS_TKEY_IT_FLAG(irq));
    
    if((TKEY->IER & irq)!= RESET)
    {
        /* Clear the interrupt pending bits in the TKEY_SR register */
        TKEY->SR = irq;
    } 
}


/******************************************************************************
*@brief : Get enabled TKEY interrupt.
*@param : None.                       
*@return: TKEY interrupt enabled.
******************************************************************************/
uint16_t HAL_TKEY_GetIT(void)
{
    /* Return the irq */
    return  TKEY->IER;
}

#endif







