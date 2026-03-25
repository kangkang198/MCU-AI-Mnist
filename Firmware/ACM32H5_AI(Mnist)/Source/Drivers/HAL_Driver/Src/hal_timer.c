/***********************************************************************
 * Filename    : hal_lpuart.c
 * Description : lpuart driver source file
 * Author(s)   : xwl  
 * version     : V1.0
 * Modify date : 2019-11-19
 ***********************************************************************/
#include "hal.h" 

#ifdef HAL_TIMER_MODULE_ENABLED

static void TIMER_ETR_SetConfig(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler,
                       uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter);
static void TIMER_TI1FP1_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICFilter);  
static void TIMER_TI2FP2_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICFilter);  
static void TIMER_IC1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t filter);
static void TIMER_IC2_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t filter);  
static void TIMER_IC3_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t filter);
static void TIMER_IC4_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t filter);   

__weak void HAL_TIM_Update_Event_Callback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
}

__weak void HAL_TIM_Trig_Event_Callback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
}

__weak void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_IC_CaptureCallback could be implemented in the user file
   */
}

/**
  * @brief  Output Compare callback in non-blocking mode
  * @param  htim TIM OC handle
  * @retval None
  */
__weak void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_OC_DelayElapsedCallback could be implemented in the user file
   */
}

/**
  * @brief  PWM Pulse finished callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
__weak void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PWM_PulseFinishedCallback could be implemented in the user file
   */
}

void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)
{ 
    /* Capture compare 1 event */
    if( (htim->Instance->SR & (TIMER_SR_CC1IF|TIMER_SR_CC1OF) ) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
        {
            __HAL_TIM_CLEAR_FLAG(htim, (TIMER_SR_CC1IF|TIMER_SR_CC1OF) ); 
            
            htim->activeChannel = HAL_TIM_ACTIVE_CHANNEL_1;

            /* Input capture event */
            if( ((htim->Instance->CCMR1) & (BIT0|BIT1) ) != 0x00U)
            {
                HAL_TIM_IC_CaptureCallback(htim);
            }
            /* Output compare event */
            else
            {
                HAL_TIM_OC_DelayElapsedCallback(htim);
                HAL_TIM_PWM_PulseFinishedCallback(htim);
            }
            htim->activeChannel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
      
        }
    }
    /* Capture compare 2 event */
    if( (htim->Instance->SR & (TIMER_SR_CC2IF|TIMER_SR_CC2OF) ) != RESET)  
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
        {
            __HAL_TIM_CLEAR_FLAG(htim, (TIMER_SR_CC2IF|TIMER_SR_CC2OF) );   
            htim->activeChannel = HAL_TIM_ACTIVE_CHANNEL_2;
            /* Input capture event */
            if((htim->Instance->CCMR1 & (BIT8|BIT9) ) != 0x00U)
            {
                HAL_TIM_IC_CaptureCallback(htim);
            }
            /* Output compare event */
            else
            {

                HAL_TIM_OC_DelayElapsedCallback(htim);
                HAL_TIM_PWM_PulseFinishedCallback(htim);
            }
            htim->activeChannel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
        }
    }
    /* Capture compare 3 event */
    if( (htim->Instance->SR & (TIMER_SR_CC3IF|TIMER_SR_CC3OF) ) != RESET)    
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
        {
            __HAL_TIM_CLEAR_FLAG(htim, (TIMER_SR_CC3IF|TIMER_SR_CC3OF) );   
            htim->activeChannel = HAL_TIM_ACTIVE_CHANNEL_3;
            /* Input capture event */
            if((htim->Instance->CCMR2 & (BIT0|BIT1)) != 0x00U)
            {
                HAL_TIM_IC_CaptureCallback(htim);
            }
            /* Output compare event */
            else
            {
                HAL_TIM_OC_DelayElapsedCallback(htim);
                HAL_TIM_PWM_PulseFinishedCallback(htim);
            }
            htim->activeChannel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
        }
    }
    /* Capture compare 4 event */
    if( (htim->Instance->SR & (TIMER_SR_CC4IF|TIMER_SR_CC4OF) ) != RESET)   
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
        {
            __HAL_TIM_CLEAR_FLAG(htim, (TIMER_SR_CC4IF|TIMER_SR_CC4OF) );   
            htim->activeChannel = HAL_TIM_ACTIVE_CHANNEL_4;
            /* Input capture event */
            if((htim->Instance->CCMR2 & (BIT8|BIT9) ) != 0x00U)
            {
                HAL_TIM_IC_CaptureCallback(htim);
            }
            /* Output compare event */
            else
            {
                HAL_TIM_OC_DelayElapsedCallback(htim);
                HAL_TIM_PWM_PulseFinishedCallback(htim);
            }
            htim->activeChannel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
        }
    }
  
  
    /* TIM Update event */
    if(__HAL_TIM_GET_FLAG(htim, TIMER_SR_UIF) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_UPDATE) != RESET)  
        {
            __HAL_TIM_CLEAR_FLAG(htim, TIMER_SR_UIF);  
            HAL_TIM_Update_Event_Callback(htim);  
        }
    }
    
    
    if(__HAL_TIM_GET_FLAG(htim, TIMER_SR_TIF) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_TRIGGER) != RESET)  
        {
            __HAL_TIM_CLEAR_FLAG(htim, TIMER_SR_TIF);  
            HAL_TIM_Trig_Event_Callback(htim);  
        }
    }

}

/*********************************************************************************
* Function    : HAL_TIMER_MSP_Init
* Description : MSP init, mainly about clock, nvic   
* Input       : timer handler 
* Output      : 0: success; else:error    
* Author      : xwl                       
**********************************************************************************/
__weak uint32_t HAL_TIMER_MSP_Init(TIM_HandleTypeDef * htim)  
{
    uint32_t Timer_Instance;
    
    
    Timer_Instance = (uint32_t)(htim->Instance); 
    
    switch(Timer_Instance) 
    {
        case TIM1_BASE_ADDR: 
					
		__HAL_RCC_TIM1_CLK_ENABLE();  
        __HAL_RCC_TIM1_RESET();  
        NVIC_ClearPendingIRQ(TIM1_BRK_UP_TRG_COM_IRQn);     
        NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);  
        break; 
        
        case TIM2_BASE_ADDR: 
        
        __HAL_RCC_TIM2_CLK_ENABLE();  
        __HAL_RCC_TIM2_RESET();         
        NVIC_ClearPendingIRQ(TIM2_IRQn);     
        NVIC_EnableIRQ(TIM2_IRQn);    
        break; 

        case TIM3_BASE_ADDR: 
        
        __HAL_RCC_TIM3_CLK_ENABLE();   
        __HAL_RCC_TIM3_RESET(); 
        NVIC_ClearPendingIRQ(TIM3_IRQn);     
        NVIC_EnableIRQ(TIM3_IRQn);    
        break;  
        
        case TIM4_BASE_ADDR: 
        __HAL_RCC_TIM4_CLK_ENABLE();   
        __HAL_RCC_TIM4_RESET();         
        NVIC_ClearPendingIRQ(TIM4_IRQn);     
        NVIC_EnableIRQ(TIM4_IRQn);    
        break;
        
        case TIM5_BASE_ADDR: 
        __HAL_RCC_TIM5_CLK_ENABLE();    
        __HAL_RCC_TIM5_RESET(); 
        NVIC_ClearPendingIRQ(TIM5_IRQn);     
        NVIC_EnableIRQ(TIM5_IRQn);     
        break;
                
        case TIM6_BASE_ADDR:          
        __HAL_RCC_TIM6_CLK_ENABLE();    
        __HAL_RCC_TIM6_RESET(); 
        NVIC_ClearPendingIRQ(TIM6_IRQn);   
        NVIC_EnableIRQ(TIM6_IRQn);   
        break; 
        
        case TIM7_BASE_ADDR:             
        __HAL_RCC_TIM7_CLK_ENABLE();  
        __HAL_RCC_TIM7_RESET(); 
        NVIC_ClearPendingIRQ(TIM7_IRQn);   
        NVIC_EnableIRQ(TIM7_IRQn);   
        break; 

        case TIM8_BASE_ADDR: 
        __HAL_RCC_TIM8_CLK_ENABLE();   
        __HAL_RCC_TIM8_RESET();
        NVIC_ClearPendingIRQ(TIM8_BRK_UP_TRG_COM_IRQn);   
        NVIC_EnableIRQ(TIM8_BRK_UP_TRG_COM_IRQn); 
        break; 
        
        case TIM9_BASE_ADDR:   
        __HAL_RCC_TIM9_CLK_ENABLE();  
        __HAL_RCC_TIM9_RESET();
        NVIC_ClearPendingIRQ(TIM9_IRQn);   
        NVIC_EnableIRQ(TIM9_IRQn);   
        break; 
        
        case TIM10_BASE_ADDR:   
        __HAL_RCC_TIM10_CLK_ENABLE();   
        __HAL_RCC_TIM10_RESET();
        NVIC_ClearPendingIRQ(TIM10_IRQn);   
        NVIC_EnableIRQ(TIM10_IRQn);    
        break;  
        
        case TIM11_BASE_ADDR:   
        __HAL_RCC_TIM11_CLK_ENABLE();  
        __HAL_RCC_TIM11_RESET();
        NVIC_ClearPendingIRQ(TIM11_IRQn);   
        NVIC_EnableIRQ(TIM11_IRQn);     
        break; 
        
        case TIM12_BASE_ADDR:   
        __HAL_RCC_TIM12_CLK_ENABLE();    
        __HAL_RCC_TIM12_RESET();
        NVIC_ClearPendingIRQ(TIM12_IRQn);   
        NVIC_EnableIRQ(TIM12_IRQn);     
        break; 
        
        case TIM13_BASE_ADDR:   
        __HAL_RCC_TIM13_CLK_ENABLE();   
        __HAL_RCC_TIM13_RESET();
        NVIC_ClearPendingIRQ(TIM13_IRQn);   
        NVIC_EnableIRQ(TIM13_IRQn);     
        break; 
        
        case TIM14_BASE_ADDR:   
        __HAL_RCC_TIM14_CLK_ENABLE();  
        __HAL_RCC_TIM14_RESET();        
        NVIC_ClearPendingIRQ(TIM14_IRQn);   
        NVIC_EnableIRQ(TIM14_IRQn);     
        break; 
        
        case TIM15_BASE_ADDR:                   
        __HAL_RCC_TIM15_CLK_ENABLE();   
        __HAL_RCC_TIM15_RESET();
        NVIC_ClearPendingIRQ(TIM15_IRQn);   
        NVIC_EnableIRQ(TIM15_IRQn);  
        break;
        
        case TIM16_BASE_ADDR:        
        __HAL_RCC_TIM16_CLK_ENABLE();  
        __HAL_RCC_TIM16_RESET();        
        NVIC_ClearPendingIRQ(TIM16_IRQn);   
        NVIC_EnableIRQ(TIM16_IRQn); 
        break;
        
        case TIM17_BASE_ADDR:          
        __HAL_RCC_TIM17_CLK_ENABLE();    
        __HAL_RCC_TIM17_RESET();        
        NVIC_ClearPendingIRQ(TIM17_IRQn);   
        NVIC_EnableIRQ(TIM17_IRQn); 
        break;  
        
        case TIM18_BASE_ADDR:        
        __HAL_RCC_TIM18_CLK_ENABLE();  
        __HAL_RCC_TIM18_RESET();        
        NVIC_ClearPendingIRQ(TIM18_IRQn);   
        NVIC_EnableIRQ(TIM18_IRQn); 
        break;
        
        case TIM19_BASE_ADDR:          
        __HAL_RCC_TIM19_CLK_ENABLE();    
        __HAL_RCC_TIM19_RESET();
        NVIC_ClearPendingIRQ(TIM19_IRQn);   
        NVIC_EnableIRQ(TIM19_IRQn);   
        break;  
        
        case TIM20_BASE_ADDR:          
        __HAL_RCC_TIM20_CLK_ENABLE();     
        __HAL_RCC_TIM20_RESET();  
        NVIC_ClearPendingIRQ(TIM20_BRK_UP_TRG_COM_IRQn);   
        NVIC_EnableIRQ(TIM20_BRK_UP_TRG_COM_IRQn);  
        break; 
                
        case TIM21_BASE_ADDR:          
        __HAL_RCC_TIM21_CLK_ENABLE();    
        __HAL_RCC_TIM21_RESET();
        NVIC_ClearPendingIRQ(TIM21_IRQn);   
        NVIC_EnableIRQ(TIM21_IRQn); 
        break;  
                
        case TIM22_BASE_ADDR:          
        __HAL_RCC_TIM22_CLK_ENABLE();  
        __HAL_RCC_TIM22_RESET();        
        NVIC_ClearPendingIRQ(TIM22_IRQn);   
        NVIC_EnableIRQ(TIM22_IRQn);  
        break;  
        
        case TIM23_BASE_ADDR:          
        __HAL_RCC_TIM23_CLK_ENABLE();    
        __HAL_RCC_TIM23_RESET();
        NVIC_ClearPendingIRQ(TIM23_IRQn);   
        NVIC_EnableIRQ(TIM23_IRQn); 
        break;  
                
        case TIM24_BASE_ADDR:          
        __HAL_RCC_TIM24_CLK_ENABLE();    
        __HAL_RCC_TIM24_RESET();        
        NVIC_ClearPendingIRQ(TIM24_IRQn);   
        NVIC_EnableIRQ(TIM24_IRQn);  
        break;  
        
        case TIM25_BASE_ADDR:          
        __HAL_RCC_TIM25_CLK_ENABLE();    
        __HAL_RCC_TIM25_RESET(); 
        NVIC_ClearPendingIRQ(TIM25_IRQn);   
        NVIC_EnableIRQ(TIM25_IRQn); 
        break;  
                        
        default:
        return HAL_ERROR;  
    }
    
    return HAL_OK;    
}  


__weak uint32_t HAL_TIMER_Base_MspDeInit(TIM_HandleTypeDef * htim)  
{
    uint32_t Timer_Instance;
    
    
    Timer_Instance = (uint32_t)(htim->Instance); 
    
    switch(Timer_Instance) 
    {
        case TIM1_BASE_ADDR: 
        __HAL_RCC_TIM1_CLK_ENABLE(); 
        NVIC_ClearPendingIRQ(TIM1_BRK_UP_TRG_COM_IRQn);     
        NVIC_DisableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);           
        break; 
        
        case TIM2_BASE_ADDR: 
        __HAL_RCC_TIM2_CLK_ENABLE(); 
        NVIC_ClearPendingIRQ(TIM2_IRQn);     
        NVIC_DisableIRQ(TIM2_IRQn);   
        break; 

        case TIM3_BASE_ADDR: 
        __HAL_RCC_TIM3_CLK_ENABLE();  
        NVIC_ClearPendingIRQ(TIM3_IRQn);     
        NVIC_DisableIRQ(TIM3_IRQn);         
        break;  
        
        case TIM4_BASE_ADDR: 
        __HAL_RCC_TIM4_CLK_ENABLE(); 
        NVIC_ClearPendingIRQ(TIM4_IRQn);     
        NVIC_DisableIRQ(TIM4_IRQn);     
        break;
        
        case TIM6_BASE_ADDR:  
        __HAL_RCC_TIM6_CLK_ENABLE();  
        NVIC_ClearPendingIRQ(TIM6_IRQn);     
        NVIC_DisableIRQ(TIM6_IRQn);   
        break; 
        
        case TIM7_BASE_ADDR:  
        __HAL_RCC_TIM7_CLK_ENABLE();  
        NVIC_ClearPendingIRQ(TIM7_IRQn);     
        NVIC_DisableIRQ(TIM7_IRQn);   
        break; 
        
        case TIM8_BASE_ADDR:   
//        System_Module_Disable(EN_TIM8);  
//        NVIC_ClearPendingIRQ(TIM8_BRK_UP_TRG_COM_IRQn);     
//        NVIC_DisableIRQ(TIM8_BRK_UP_TRG_COM_IRQn);           
        break;
        
        case TIM15_BASE_ADDR:   
        __HAL_RCC_TIM15_CLK_ENABLE();  
        NVIC_ClearPendingIRQ(TIM15_IRQn);     
        NVIC_DisableIRQ(TIM15_IRQn); 
        break;
        
        case TIM16_BASE_ADDR: 
        __HAL_RCC_TIM16_CLK_ENABLE(); 
        NVIC_ClearPendingIRQ(TIM16_IRQn);     
        NVIC_DisableIRQ(TIM16_IRQn); 
        break;
        
        case TIM17_BASE_ADDR: 
        __HAL_RCC_TIM17_CLK_ENABLE(); 
        NVIC_ClearPendingIRQ(TIM17_IRQn);     
        NVIC_DisableIRQ(TIM17_IRQn);               
        break;  
        
        default:
        return HAL_ERROR;  
    }
    
    return HAL_OK;    
}  


/*********************************************************************************
* Function    : HAL_TIMER_Slave_Mode_Config 
* Description : configure timer in slave mode  
* Input       : 
              htim: timer handler
              sSlaveConfig: slave mode parameter strcture
                            SlaveMode: TIM_SLAVE_MODE_DIS, TIM_SLAVE_MODE_ENC1...
                            InputTrigger: TIM_TS_ITR0, TIM_TS_ITR1... 
                            TriggerPolarity: TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING... 
                            TriggerPrescaler: TIM_ETR_PRESCALER_1, TIM_ETR_PRESCALER_2... 
* Output      : 0: success; else:error   
* Author      : xwl                       
**********************************************************************************/
uint32_t HAL_TIMER_Slave_Mode_Config(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *sSlaveConfig)  
{
    /*reset SMS and TS bits*/
    htim->Instance->SMCR &= (~(BIT0|BIT1|BIT2|TIM_SMCR_TS_Msk));       
    /*SET SMS bits*/
    htim->Instance->SMCR |= (sSlaveConfig->SlaveMode & (BIT0|BIT1|BIT2) ); 
    /*SET TS bits*/
    htim->Instance->SMCR |= (sSlaveConfig->InputTrigger);   
    
    switch (sSlaveConfig->InputTrigger)   
    {
        case TIM_TS_TI1FP1:  
        TIMER_TI1FP1_ConfigInputStage(htim->Instance, sSlaveConfig->TriggerPolarity, sSlaveConfig->TriggerFilter);
        break;
        
        case TIM_TS_TI2FP2: 
        TIMER_TI2FP2_ConfigInputStage(htim->Instance, sSlaveConfig->TriggerPolarity, sSlaveConfig->TriggerFilter);  
        break; 
        
        case TIM_TS_ETRF:  
        TIMER_ETR_SetConfig(htim->Instance, sSlaveConfig->TriggerPrescaler, sSlaveConfig->TriggerPolarity, sSlaveConfig->TriggerFilter);  
        break;  
        
        case TIM_TS_TI1F_ED:
        htim->Instance->CR2 |= BIT7; //ch1/2/3 xor to TI1
        break;  
        
        case TIM_TS_ITR0: 
        case TIM_TS_ITR1:
        case TIM_TS_ITR2:
        case TIM_TS_ITR3: 
        case TIM_TS_ITR4: 
        case TIM_TS_ITR5: 
        case TIM_TS_ITR6: 
        case TIM_TS_ITR7: 
        case TIM_TS_ITR8: 
        case TIM_TS_ITR9: 
        case TIM_TS_ITR10: 
        // don't need do anything here 
        break;  
        
        default:
        return 1;  
    }
    
    return 0;  
}     

/*********************************************************************************
* Function    : HAL_TIMER_Master_Mode_Config 
* Description : configure timer in master mode  
* Input       : 
              TIMx: timer instance 
              sMasterConfig: master mode parameter structure 
                             MasterSlaveMode: TIM_TRGO_RESET, TIM_TRGO_ENABLE...   
                             MasterOutputTrigger: TIM_MASTERSLAVEMODE_DISABLE, TIM_MASTERSLAVEMODE_ENABLE  
* Output      : 0: success; else:error 
* Author      : xwl                       
**********************************************************************************/
uint32_t HAL_TIMER_Master_Mode_Config(TIM_TypeDef *TIMx, TIM_MasterConfigTypeDef * sMasterConfig)    
{
    /*reset bits*/
    TIMx->SMCR &= (~BIT7);  
    TIMx->CR2  &= (~(BIT4|BIT5|BIT6));       
    
    TIMx->SMCR |= sMasterConfig->MasterSlaveMode;  
    TIMx->CR2  |= sMasterConfig->MasterOutputTrigger;     

    /* If the timer supports ADC synchronization through TRGO2, set the master mode selection 2 */
    if (IS_TIM_TRGO2_INSTANCE(TIMx))
    {
        /* Clear the MMS2 bits */
        TIMx->CR2 &= (~(BIT20|BIT21|BIT22|BIT23));
        /* Select the TRGO2 source*/
        TIMx->CR2 |= (sMasterConfig->MasterOutputTrigger2 & (BIT20|BIT21|BIT22|BIT23) ) ;   
    }

    return 0;  
}

/*********************************************************************************
* Function    : HAL_TIMER_Output_Config  
* Description : configure output parameter   
* Input       : 
              TIMx: timer instance  
              Output_Config: output configration parameter structure  
                             OCMode: OUTPUT_MODE_FROZEN, OUTPUT_MODE_MATCH_HIGH... 
                             Pulse: write to ccrx register 
                             OCPolarity: OC channel output polarity: OUTPUT_POL_ACTIVE_HIGH, OUTPUT_POL_ACTIVE_LOW 
                             OCNPolarity: OCN channel output polarity: OUTPUT_POL_ACTIVE_HIGH, OUTPUT_POL_ACTIVE_LOW  
                             OCFastMode: OUTPUT_FAST_MODE_DISABLE, OUTPUT_FAST_MODE_ENABLE 
                             OCIdleState: OC channel idle state, OUTPUT_IDLE_STATE_0, OUTPUT_IDLE_STATE_1
                             OCNIdleState: OCN channel idle state, OUTPUT_IDLE_STATE_0, OUTPUT_IDLE_STATE_1 
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...  
* Output      : 0: success; else:error 
* Author      : xwl                       
**********************************************************************************/
uint32_t HAL_TIMER_Output_Config(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef * Output_Config, uint32_t Channel)
{
    
    switch(Channel)
    {
        case TIM_CHANNEL_1:
        TIMx->CCER &= (~BIT0);  //disable OC1 
        if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCPolarity)
        {
            TIMx->CCER &= (~BIT1);  
        }
        else
        {
            TIMx->CCER |= (BIT1);   
        }
        
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER &= (~BIT2);  //disable OC1N  
            
            if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCNPolarity)   
            {
                TIMx->CCER &= (~BIT3);  
            }
            else
            {
                TIMx->CCER |= (BIT3);     
            }  
        }
        
        TIMx->CCMR1 &= (~0x00FFU); // reset low 8 bits   
        TIMx->CCR1 = Output_Config->Pulse;   
        if (OUTPUT_FAST_MODE_ENABLE == Output_Config->OCFastMode)  
        {
            TIMx->CCMR1 |= (BIT2);  
        }
        TIMx->CCMR1 |= (BIT3);  // preload enable     
        
        if (IS_TIM_BREAK_INSTANCE(TIMx)) 
        {
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCIdleState)
            {
                TIMx->CR2 &= (~BIT8); 
            }
            else
            {
                TIMx->CR2 |= BIT8; 
            }
            
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCNIdleState)  
            {
                TIMx->CR2 &= (~BIT9); 
            }
            else
            {
                TIMx->CR2 |= BIT9;   
            }  
            
        }
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT4|BIT5|BIT6))) | (Output_Config->OCMode << 4);   
        break;
        
        case TIM_CHANNEL_2:
        TIMx->CCER &= (~BIT4);  //disable OC2
        if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCPolarity)
        {
            TIMx->CCER &= (~BIT5);  
        }
        else
        {
            TIMx->CCER |= (BIT5);   
        }
        
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER &= (~BIT6);  //disable OC2N  
            
            if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCNPolarity)   
            {
                TIMx->CCER &= (~BIT7);  
            }
            else
            {
                TIMx->CCER |= (BIT7);     
            }  
        }
        
        TIMx->CCMR1 &= (~0xFF00U); // reset high 8 bits 
        TIMx->CCR2 = Output_Config->Pulse;   // write value to ccr before preload enable 
        if (OUTPUT_FAST_MODE_ENABLE == Output_Config->OCFastMode)  
        {
            TIMx->CCMR1 |= (BIT10);  
        }
        TIMx->CCMR1 |= (BIT11);  // preload enable 
        
        if (IS_TIM_BREAK_INSTANCE(TIMx)) 
        {
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCIdleState)
            {
                TIMx->CR2 &= (~BIT10); 
            }
            else
            {
                TIMx->CR2 |= BIT10; 
            }
            
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCNIdleState)  
            {
                TIMx->CR2 &= (~BIT11); 
            }
            else
            {
                TIMx->CR2 |= BIT11;   
            }
            
        }
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT12|BIT13|BIT14))) | (Output_Config->OCMode << 12);   
        break;
        
        case TIM_CHANNEL_3:
        TIMx->CCER &= (~BIT8);  //disable OC3  
        if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCPolarity)
        {
            TIMx->CCER &= (~BIT9);  
        }
        else
        {
            TIMx->CCER |= (BIT9);   
        }
        
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER &= (~BIT10);  //disable OC3N   
            
            if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCNPolarity)   
            {
                TIMx->CCER &= (~BIT11);  
            }
            else
            {
                TIMx->CCER |= (BIT11);     
            }  
        }
        
        TIMx->CCMR2 &= (~0x00FF); // reset low 8 bits 
        TIMx->CCMR2 |= (BIT3);  // preload enable   
        if (OUTPUT_FAST_MODE_ENABLE == Output_Config->OCFastMode)  
        {
            TIMx->CCMR2 |= (BIT2);  
        }
         
        TIMx->CCR3 = Output_Config->Pulse;      
        if (IS_TIM_BREAK_INSTANCE(TIMx)) 
        {
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCIdleState)
            {
                TIMx->CR2 &= (~BIT12); 
            }
            else
            {
                TIMx->CR2 |= BIT12; 
            }
            
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCNIdleState)  
            {
                TIMx->CR2 &= (~BIT13); 
            }
            else
            {
                TIMx->CR2 |= BIT13;     
            } 
            
        }
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT4|BIT5|BIT6))) | (Output_Config->OCMode << 4);     
        break;
        
        case TIM_CHANNEL_4: 
        TIMx->CCER &= (~BIT12);  //disable OC4  
        if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCPolarity)
        {
            TIMx->CCER &= (~BIT13);  
        }
        else
        {
            TIMx->CCER |= (BIT13);     
        }
        
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER &= (~BIT14);  //disable OC4N  
            
            if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCNPolarity)   
            {
                TIMx->CCER &= (~BIT15);  
            }
            else
            {
                TIMx->CCER |= (BIT15);     
            }  
        }
        
        TIMx->CCMR2 &= (~0xFF00); // reset high 8 bits    
        TIMx->CCR4 = Output_Config->Pulse;   
        if (OUTPUT_FAST_MODE_ENABLE == Output_Config->OCFastMode)  
        {
            TIMx->CCMR2 |= (BIT10);  // fast mode  
        }
        TIMx->CCMR2 |= (BIT11);  // preload enable 
    
        if (IS_TIM_BREAK_INSTANCE(TIMx)) 
        {
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCIdleState)
            {
                TIMx->CR2 &= (~BIT14); 
            }
            else
            {
                TIMx->CR2 |= BIT14;    
            }
            
        }
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT12|BIT13|BIT14))) | (Output_Config->OCMode << 12);     
        break;
        
        case TIM_CHANNEL_5:
        TIMx->CCER &= (~BIT16);  //disable OC5  
        if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCPolarity)
        {
            TIMx->CCER &= (~BIT17);  
        }
        else
        {
            TIMx->CCER |= (BIT17);   
        }
        
        TIMx->CCMR3 &= (~0x00FF); // reset low 8 bits 
        TIMx->CCMR3 |= (BIT3);  // preload enable   
        if (OUTPUT_FAST_MODE_ENABLE == Output_Config->OCFastMode)  
        {
            TIMx->CCMR3 |= (BIT2);  
        }
         
        TIMx->CCR5 = Output_Config->Pulse;      
        if (IS_TIM_BREAK_INSTANCE(TIMx)) 
        {
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCIdleState)
            {
                TIMx->CR2 &= (~BIT16); 
            }
            else
            {
                TIMx->CR2 |= BIT16; 
            }
        }
        TIMx->CCMR3 = (TIMx->CCMR3 & (~(BIT4|BIT5|BIT6))) | (Output_Config->OCMode << 4);     
        break;
        
        case TIM_CHANNEL_6: 
        TIMx->CCER &= (~BIT20);  //disable OC6  
        if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCPolarity)
        {
            TIMx->CCER &= (~BIT21);  
        }
        else
        {
            TIMx->CCER |= (BIT21);     
        }
        
        TIMx->CCMR3 &= (~0xFF00); // reset high 8 bits    
        TIMx->CCR6 = Output_Config->Pulse;   
        if (OUTPUT_FAST_MODE_ENABLE == Output_Config->OCFastMode)  
        {
            TIMx->CCMR3 |= (BIT10);  // fast mode  
        }
        TIMx->CCMR3 |= (BIT11);  // preload enable 
    
        if (IS_TIM_BREAK_INSTANCE(TIMx)) 
        {
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCIdleState)
            {
                TIMx->CR2 &= (~BIT18); 
            }
            else
            {
                TIMx->CR2 |= BIT18;    
            }
            
        }
        TIMx->CCMR3 = (TIMx->CCMR3 & (~(BIT12|BIT13|BIT14))) | (Output_Config->OCMode << 12);     
        break;
        
        default:
            return 1; // error parameter 
    } 
    
    return 0;  
}   


/*********************************************************************************
* Function    : HAL_TIMER_Capture_Config  
* Description : configure capture parameters   
* Input       : 
              TIMx: timer instance 
              Capture_Config: capture configuration parameter strcture 
                            ICPolarity: TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING... 
                            ICSelection: TIM_ICSELECTION_DIRECTTI, TIM_ICSELECTION_INDIRECTTI
                            ICFilter: TIM_IC1_FILTER_LVL(x), TIM_IC2_FILTER_LVL(x), x:0-15 
                            ICPrescaler: TIM_IC1_PRESCALER_1, TIM_IC2_PRESCALER_1... 
              Channel: channel id, TIM_CHANNEL_1, TIM_CHANNEL_2...   
* Output      : 0: success; else:error 
* Author      : xwl                       
**********************************************************************************/      
uint32_t HAL_TIMER_Capture_Config(TIM_TypeDef *TIMx, TIM_IC_InitTypeDef * Capture_Config, uint32_t Channel)  
{
    switch(Channel) 
    {
        case TIM_CHANNEL_1:   
        TIMER_IC1_SetConfig(TIMx, Capture_Config->ICPolarity, Capture_Config->ICSelection, Capture_Config->TIFilter);  
         
        /* Reset the IC1PSC Bits */
        TIMx->CCMR1 &= (~BIT2|BIT3);   
        /* Set the IC1PSC value */
        TIMx->CCMR1 |= Capture_Config->ICPrescaler;   
        break;  
        
        case TIM_CHANNEL_2:  
        TIMER_IC2_SetConfig(TIMx, Capture_Config->ICPolarity, Capture_Config->ICSelection, Capture_Config->TIFilter); 

        
        /* Reset the IC2PSC Bits */
        TIMx->CCMR1 &= (~BIT10|BIT11);
        /* Set the IC2PSC value */
        TIMx->CCMR1 |= Capture_Config->ICPrescaler;  
        break; 
        
        case TIM_CHANNEL_3:    
        TIMER_IC3_SetConfig(TIMx, Capture_Config->ICPolarity, Capture_Config->ICSelection, Capture_Config->TIFilter);    

        /* Reset the IC3PSC Bits */
        TIMx->CCMR2 &= (~BIT2|BIT3);
        /* Set the IC3PSC value */
        TIMx->CCMR2 |= Capture_Config->ICPrescaler;      
                
        break; 
        
        case TIM_CHANNEL_4:   
        TIMER_IC4_SetConfig(TIMx, Capture_Config->ICPolarity, Capture_Config->ICSelection, Capture_Config->TIFilter);         
        
        /* Reset the IC4PSC Bits */
        TIMx->CCMR2 &= (~BIT10|BIT11);   
        /* Set the IC4PSC value */
        TIMx->CCMR2 |= Capture_Config->ICPrescaler;  
        break;   
        
        default:  
        return 1;     
    }
        
    return 0;  
}    



/*********************************************************************************
* Function    : HAL_TIMER_SelectClockSource  
* Description : select timer counter source, internal or external 
* Input:
  htim : timer handler 
  sClockSourceConfig: configuration parameters, includes following members:  
                      ClockSource: TIM_CLOCKSOURCE_ITR0,  TIM_CLOCKSOURCE_ETR... 
                      ClockPolarity: TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING... 
                      ClockPrescaler: TIM_ETR_PRESCALER_1, TIM_ETR_PRESCALER_2...  
                      ClockFilter: TIM_ETR_FILTER_LVL(x), TIM_IC1_FILTER_LVL(x), TIM_IC2_FILTER_LVL(x)  
* Output      : HAL_ERROR:error, HAL_OK:OK     
* Author      : xwl                       
**********************************************************************************/  
HAL_StatusTypeDef HAL_TIMER_SelectClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef * sClockSourceConfig)
{
  htim->Instance->SMCR &= (~(BIT0|BIT1|BIT2));  
    
  switch (sClockSourceConfig->ClockSource)
  {
//    case TIM_CLOCKSOURCE_INT:
//    {
//        // do nothing here   
//        break;
//    }
    case TIM_CLOCKSOURCE_ETR:
    {

      /* Configure the ETR Clock source */
      TIMER_ETR_SetConfig(htim->Instance,
                        sClockSourceConfig->ClockPrescaler,
                        sClockSourceConfig->ClockPolarity,
                        sClockSourceConfig->ClockFilter);
      /* Enable the External clock mode2 */
      htim->Instance->SMCR |= BIT14;  // ECE=1,external clock mode 2   
      break;
    }

    case TIM_CLOCKSOURCE_TI1FP1:
    {
      
      TIMER_TI1FP1_ConfigInputStage(htim->Instance,
                               sClockSourceConfig->ClockPolarity,
                               sClockSourceConfig->ClockFilter); 
        
      MODIFY_REG(htim->Instance->SMCR, TIM_SMCR_TS_Msk, TIM_CLOCKSOURCE_TI1FP1); //Clock source select TI1FP1 
        
      htim->Instance->SMCR |= (BIT0|BIT1|BIT2);  // select external clock mode 1  
      break;
    }

    case TIM_CLOCKSOURCE_TI2FP2:
    {
      TIMER_TI2FP2_ConfigInputStage(htim->Instance,
                               sClockSourceConfig->ClockPolarity,
                               sClockSourceConfig->ClockFilter); 
        
      MODIFY_REG(htim->Instance->SMCR, TIM_SMCR_TS_Msk, TIM_CLOCKSOURCE_TI2FP2); //Clock source select TI2FP2 
        
      htim->Instance->SMCR |= (BIT0|BIT1|BIT2);  // select external clock mode 1  
      break;
    }
    case TIM_CLOCKSOURCE_TI1F_ED:
    case TIM_CLOCKSOURCE_ITR0:
    case TIM_CLOCKSOURCE_ITR1: 
    case TIM_CLOCKSOURCE_ITR2:
    case TIM_CLOCKSOURCE_ITR3:
    case TIM_CLOCKSOURCE_ITR4:
    case TIM_CLOCKSOURCE_ITR5:
    case TIM_CLOCKSOURCE_ITR6:
    case TIM_CLOCKSOURCE_ITR7:
    case TIM_CLOCKSOURCE_ITR8:
    case TIM_CLOCKSOURCE_ITR9:
    case TIM_CLOCKSOURCE_ITR10:
    {
        MODIFY_REG(htim->Instance->SMCR, TIM_SMCR_TS_Msk, sClockSourceConfig->ClockSource); //Clock source set 
        
        htim->Instance->SMCR |= (BIT0|BIT1|BIT2);  //select external clock mode 1  
        break;
    }

    default:
      return HAL_ERROR;   
  }

  return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIMER_Base_Init  
* Description : timer base initiation   
* Input       : timer handler 
* Output      : 0: success; else:error 
* Author      : xwl                       
**********************************************************************************/      
uint32_t HAL_TIMER_Base_Init(TIM_HandleTypeDef * htim)
{
    
    htim->Instance->CR1 = BIT2;  // CEN=0, URS=1, OPM = 0   
    
    //up/down/center mode 
    htim->Instance->CR1 = (htim->Instance->CR1 & (~(BIT4|BIT5|BIT6))) | ((htim->Init.CounterMode) & (BIT4|BIT5|BIT6));   
    
    if (htim->Init.ARRPreLoadEn)  
    {
        htim->Instance->CR1 |= (BIT7);        
    }
    else
    {
        htim->Instance->CR1 &= (~BIT7);   
    }    
    
    htim->Instance->ARR = htim->Init.Period; 
    htim->Instance->PSC = htim->Init.Prescaler;   
    if (IS_TIM_REPETITION_COUNTER_INSTANCE(htim->Instance))
    {
        htim->Instance->RCR = htim->Init.RepetitionCounter;   
    }
    htim->Instance->EGR = BIT0;     // no UIF generated because URS=1 

  
    htim->Instance->CR1 = (htim->Instance->CR1 & (~(BIT8|BIT9))) | ((htim->Init.ClockDivision) & (BIT8|BIT9));     
       
    htim->Instance->CR1 &= (~BIT2); //URS = 0     
    
    return 0;  
} 

/*********************************************************************************
* Function    : HAL_TIMER_Base_DeInit  
* Description : timer base deinitiation, disable Timer, turn off module clock and nvic  
* Input       : timer handler 
* Output      : HAL_OK: success; HAL_ERROR:error 
* Author      : xwl                       
**********************************************************************************/ 
HAL_StatusTypeDef HAL_TIMER_Base_DeInit(TIM_HandleTypeDef *htim)
{
  htim->Instance->CR1 &= (~BIT0);  
    
  HAL_TIMER_Base_MspDeInit(htim);     

  return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIMER_Base_Start  
* Description : start timer   
* Input       : timer instance  
* Output      : none 
* Author      : xwl                       
**********************************************************************************/      
void HAL_TIMER_Base_Start(TIM_TypeDef *TIMx)
{
    if (0 == IS_TIM_SLAVE_INSTANCE(TIMx) )     
    {
        TIMx->CR1 |= BIT0;    
        return;    
    }
    
    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )  
    {
        TIMx->CR1 |= BIT0;      
        return;     
    }
    
    return;       
}
#ifdef HAL_DMA_MODULE_ENABLED    
/*********************************************************************************
* Function    : HAL_TIMER_Base_Start_DMA     
* Description : start timer,    
* Input       : timer instance  
* Output      : HAL status  
* Author      : xwl                       
**********************************************************************************/      
HAL_StatusTypeDef HAL_TIMER_Base_Start_DMA(TIM_HandleTypeDef *htim, uint32_t start_addr, uint32_t transfer_size)   
{   
    if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_UPDATE_INDEX], start_addr, (uint32_t)(&(htim->Instance->ARR)), transfer_size))
    {
        return HAL_ERROR;  
    }
    
    if (0 == IS_TIM_SLAVE_INSTANCE(htim->Instance) )     
    {
        htim->Instance->CR1 |= BIT0;    
        return HAL_OK;    
    }
    
    if (TIM_SLAVE_MODE_TRIG != (htim->Instance->SMCR & (BIT0|BIT1|BIT2) ) )  
    {
        htim->Instance->CR1 |= BIT0;        
        return HAL_OK;     
    }
        
    return HAL_OK;       
}
#endif
/*********************************************************************************
* Function    : HAL_TIMER_Base_Stop  
* Description : stop timer 
* Input       : timer handler   
* Output      : none 
* Author      : xwl                       
**********************************************************************************/  
HAL_StatusTypeDef HAL_TIMER_Base_Stop(TIM_TypeDef *TIMx)
{
    TIMx->CR1 &= (~BIT0);  
    HAL_TIM_DISABLE_IT_EX(TIMx, TIM_IT_UPDATE);         

    return HAL_OK;   
}

/*********************************************************************************
* Function    : HAL_TIMER_OnePulse_Init     
* Description : start timer with one pulse mode 
* Input       : 
              htim: timer handler 
              mode: 0 means normal mode, 1 means one pulse mode  
* Output      : HAL_OK, success; HAL_ERROR, fail     
* Author      : xwl                       
**********************************************************************************/        
HAL_StatusTypeDef HAL_TIMER_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t mode)
{
    /* Check the TIM handle allocation */
    if(htim == NULL)
    {
        return HAL_ERROR;
    }

    HAL_TIMER_Base_Init(htim);    
  
    /*reset  the OPM Bit */
    htim->Instance->CR1 &= (~BIT3);   
    if (0 != mode)
    {
        /*set  the OPM Bit */  
        htim->Instance->CR1 |= BIT3; 
    }  

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIM_PWM_Output_Start      
* Description : start timer output 
* Input       : 
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...    
* Output      : : 0: success; else:error    
* Author      : xwl                       
**********************************************************************************/    
uint32_t HAL_TIM_PWM_Output_Start(TIM_TypeDef *TIMx, uint32_t Channel)  
{
    
    switch(Channel)
    {
        case TIM_CHANNEL_1: 
        TIMx->CCER |= BIT0; 
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER |= BIT2;  
        }
        break; 
        
        case TIM_CHANNEL_2:  
        TIMx->CCER |= BIT4; 
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER |= BIT6;  
        }
        break;  
        
        case TIM_CHANNEL_3:   
        TIMx->CCER |= BIT8; 
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER |= BIT10;    
        }
        break;  
        
        case TIM_CHANNEL_4: 
        TIMx->CCER |= BIT12;   
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER |= BIT14;    
        }
        break;  
        
        case TIM_CHANNEL_5: 
        TIMx->CCER |= BIT16;
        break;  
        
        case TIM_CHANNEL_6: 
        TIMx->CCER |= BIT20;
        break;  
        
        default:
            return 1;  
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx) != 0)  
    {
        /* Enable the main output */
        TIMx->BDTR |= BIT15;     
    }
    
    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )    
    {
        TIMx->CR1 |= BIT0;         
    }
    
    return 0;  
}  
/*********************************************************************************
* Function    : HAL_TIM_PWM_Output_Stop       
* Description : stop timer pwm output 
* Input       : 
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...    
* Output      : : 0: success; else:error    
* Author      : xwl                       
**********************************************************************************/ 
HAL_StatusTypeDef HAL_TIM_PWM_Output_Stop(TIM_TypeDef *TIMx, uint32_t Channel)    
{

    switch(Channel)
    {
        case TIM_CHANNEL_1: 
        TIMx->CCER &= (~(BIT0 | BIT2)); 
        break; 
        
        case TIM_CHANNEL_2:  
        TIMx->CCER &= (~(BIT4 | BIT6));    
        break;  
        
        case TIM_CHANNEL_3:   
        TIMx->CCER &= (~(BIT8 | BIT10));   
        break;  
        
        case TIM_CHANNEL_4: 
        TIMx->CCER &= (~(BIT12));       
        break;  
        
        case TIM_CHANNEL_5: 
        TIMx->CCER &= (~(BIT16));       
        break;  
        
        case TIM_CHANNEL_6: 
        TIMx->CCER &= (~(BIT20));       
        break;  
        
        default:
            return HAL_ERROR;  
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx) != 0)  
    {
        /* Enable the main output */
        TIMx->BDTR &= (~BIT15);     
    }
    
    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )    
    {
        TIMx->CR1 &= (~BIT0);         
    }
    
  /* Return function status */
  return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIMER_OC_Start      
* Description : start timer output 
* Input       : 
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...    
* Output      : : 0: success; else:error    
* Author      : xwl                       
**********************************************************************************/    
uint32_t HAL_TIMER_OC_Start(TIM_TypeDef *TIMx, uint32_t Channel)    
{
    
    switch(Channel)
    {
        case TIM_CHANNEL_1: 
        TIMx->CCER |= BIT0; 
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER |= BIT2;  
        }
        break; 
        
        case TIM_CHANNEL_2:  
        TIMx->CCER |= BIT4; 
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER |= BIT6;  
        }
        break;  
        
        case TIM_CHANNEL_3:   
        TIMx->CCER |= BIT8; 
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER |= BIT10;    
        }
        break;  
        
        case TIM_CHANNEL_4: 
        TIMx->CCER |= BIT12;   
        break;  
        
        case TIM_CHANNEL_5: 
        TIMx->CCER |= BIT16;   
        break;  
        
        case TIM_CHANNEL_6: 
        TIMx->CCER |= BIT20;   
        break;  
        
        default:
            return 1;  
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx) != 0)  
    {
        /* Enable the main output */
        TIMx->BDTR |= BIT15;     
    }
    
    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )    
    {
        TIMx->CR1 |= BIT0;         
    }
    
    return 0;  
}  

/*********************************************************************************
* Function    : HAL_TIMER_OCxN_Start       
* Description : start timer OCxN output 
* Input       : 
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...    
* Output      : : 0: success; else:error    
* Author      : xwl                       
**********************************************************************************/    
uint32_t HAL_TIMER_OCxN_Start(TIM_TypeDef *TIMx, uint32_t Channel)    
{
    
    switch(Channel)
    {
        case TIM_CHANNEL_1: 
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER |= BIT2;  
        }
        break; 
        
        case TIM_CHANNEL_2:  
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER |= BIT6;  
        }
        break;  
        
        case TIM_CHANNEL_3:   
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )  
        {
            TIMx->CCER |= BIT10;    
        }
        break;  
        
        case TIM_CHANNEL_4: 
        TIMx->CCER |= BIT12;   
        break;
        
        default:
            return 1;  
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx) != 0)  
    {
        /* Enable the main output */
        TIMx->BDTR |= BIT15;     
    }
    
    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )    
    {
        TIMx->CR1 |= BIT0;         
    }
    
    return 0;  
} 

/*********************************************************************************
* Function    : HAL_TIMER_OC_Stop      
* Description : stop timer output 
* Input       : 
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...    
* Output      : : 0: success; else:error    
* Author      : xwl                       
**********************************************************************************/ 
HAL_StatusTypeDef HAL_TIMER_OC_Stop(TIM_TypeDef *TIMx, uint32_t Channel)    
{

    switch(Channel)
    {
        case TIM_CHANNEL_1: 
        TIMx->CCER &= (~(BIT0 | BIT2)); 
        break; 
        
        case TIM_CHANNEL_2:  
        TIMx->CCER &= (~(BIT4 | BIT6));    
        break;  
        
        case TIM_CHANNEL_3:   
        TIMx->CCER &= (~(BIT8 | BIT10));   
        break;  
        
        case TIM_CHANNEL_4: 
        TIMx->CCER &= (~(BIT12));       
        break;  
        
        case TIM_CHANNEL_5: 
        TIMx->CCER &= (~(BIT16));       
        break;  
        
        case TIM_CHANNEL_6: 
        TIMx->CCER &= (~(BIT20));       
        break;  
        
        default:
            return HAL_ERROR;  
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx) != 0)  
    {
        /* Enable the main output */
        TIMx->BDTR &= (~BIT15);     
    }
    
    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )    
    {
        TIMx->CR1 &= (~BIT0);         
    }
    
  /* Return function status */
  return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIM_Capture_Start      
* Description : start timer capture  
* Input       : 
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...    
* Output      : : 0: success; else:error    
* Author      : xwl                       
**********************************************************************************/    
uint32_t HAL_TIM_Capture_Start(TIM_TypeDef *TIMx, uint32_t Channel)    
{
    
    switch(Channel)
    {
        case TIM_CHANNEL_1: 
        TIMx->CCER |= BIT0; 
        break; 
        
        case TIM_CHANNEL_2:  
        TIMx->CCER |= BIT4; 
        break;  
        
        case TIM_CHANNEL_3:   
        TIMx->CCER |= BIT8;   
        break;  
        
        case TIM_CHANNEL_4: 
        TIMx->CCER |= BIT12;   
        break;  
        
        default:
            return 1;  
    }
    
    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )    
    {
        TIMx->CR1 |= BIT0;         
    }
        
    return 0;  
}    


/*********************************************************************************
* Function    : HAL_TIM_Capture_Stop      
* Description : stop timer capture  
* Input       : 
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...    
* Output      : : 0: success; else:error    
* Author      : xwl                       
**********************************************************************************/    
uint32_t HAL_TIM_Capture_Stop(TIM_TypeDef *TIMx, uint32_t Channel)    
{
    
    switch(Channel)
    {
        case TIM_CHANNEL_1: 
        TIMx->CCER &= (~BIT0); 
        break; 
        
        case TIM_CHANNEL_2:  
        TIMx->CCER &= (~BIT4); 
        break;  
        
        case TIM_CHANNEL_3:   
        TIMx->CCER &= (~BIT8);  
        break;  
        
        case TIM_CHANNEL_4: 
        TIMx->CCER &= (~BIT12);         
        break;  
        
        default:
            return 1;  
    }
    
    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )    
    {
        TIMx->CR1 &= (~BIT0);            
    }
        
    return 0;  
}    


/*********************************************************************************
* Function    : HAL_TIMEx_ETRSelection      
* Description : select ETR signal, it can ben GPIO, COMP1_OUT, COMP2_OUT, ADC analog watchdog output 
* Input       : 
              htim: timer handler 
              ETRSelection: ETR_SELECT_GPIO, ETR_SELECT_IN1...         
* Output      : HAL_OK, Success; HAL_ERROR:Fail     
* Author      : xwl                       
**********************************************************************************/ 
HAL_StatusTypeDef  HAL_TIMEx_ETRSelection(TIM_HandleTypeDef *htim, uint32_t ETRSelection)
{
    HAL_StatusTypeDef status = HAL_OK;
  
    htim->Instance->AF1 &= (~ETR_SELECT_MASK);      
    htim->Instance->AF1 |= ETRSelection;  
  
    return status;
}   

/*********************************************************************************
* Function    : HAL_TIMER_ReadCapturedValue      
* Description : read capture value as channel  
* Input       : 
              htim: timer handler  
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...    
* Output      : capture value     
* Author      : xwl                       
**********************************************************************************/     
uint32_t HAL_TIMER_ReadCapturedValue(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  uint32_t capture_data = 0U;

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {
      /* Return the capture 1 value */
      capture_data =  htim->Instance->CCR1;
      break;
    }
    case TIM_CHANNEL_2:
    {
      /* Return the capture 2 value */
      capture_data =   htim->Instance->CCR2;
      break;
    }
    case TIM_CHANNEL_3:
    {
      /* Return the capture 3 value */
      capture_data =   htim->Instance->CCR3;
      break;
    }
    case TIM_CHANNEL_4:
    {
      /* Return the capture 4 value */
      capture_data =   htim->Instance->CCR4;
      break;
    }
    default:
      break;
  }

  return capture_data;
}   

/*********************************************************************************
* Function    : HAL_TIMER_GenerateEvent  
* Description : Generate event by software
* Input:
  htim : timer handler 
  EventSource: TIM_EVENTSOURCE_UPDATE, TIM_EVENTSOURCE_CC1...
* Output      : HAL_ERROR:error, HAL_OK:OK     
* Author      : xwl                       
**********************************************************************************/ 
HAL_StatusTypeDef HAL_TIMER_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource)
{
  htim->Instance->EGR = EventSource;

  return HAL_OK;
} 

/*********************************************************************************
* Function    : HAL_TIMER_Clear_Capture_Flag        
* Description : clear capture flag as channel id   
* Input       : 
              htim: timer handler  
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...    
* Output      : capture value     
* Author      : xwl                       
**********************************************************************************/
void HAL_TIMER_Clear_Capture_Flag(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    switch (Channel)
    {
        case TIM_CHANNEL_1:
        {
            htim->Instance->SR &= (~(BIT1|BIT9));  
            break;  
        }
        case TIM_CHANNEL_2:
        {
            htim->Instance->SR &= (~(BIT2|BIT10));  
            break;
        }
        case TIM_CHANNEL_3:
        {
            htim->Instance->SR &= (~(BIT3|BIT11));  
            break;
        }
        case TIM_CHANNEL_4:
        {
            htim->Instance->SR &= (~(BIT4|BIT12));      
            break;
        }
        default:
        break;
    }
}

/*********************************************************************************
* Function    : TIMER_ETR_SetConfig  
* Description : configure ETR channel polarity, prescaler and filter 
* Input:
  TIMx : timer instance  
  TIM_ExtTRGPrescaler: TIM_ETR_PRESCALER_1, TIM_ETR_PRESCALER_2...  
  TIM_ExtTRGPolarity:  TIM_ETR_POLAIRTY_HIGH, TIM_ETR_POLAIRTY_LOW
  ExtTRGFilter:  TIM_ETR_FILTER_LVL(x), x=0-15  
* Output      : none  
* Author      : xwl                       
**********************************************************************************/ 
static void TIMER_ETR_SetConfig(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler, uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
  /* Reset the ETR Bits */
  TIMx->SMCR &= (~0xFF00U);     

  /* Set the Prescaler, the Filter value and the Polarity */
  TIMx->SMCR |= (TIM_ExtTRGPrescaler | TIM_ExtTRGPolarity | ExtTRGFilter);   
}

/*********************************************************************************
* Function    : TIMER_TI1FP1_ConfigInputStage  
* Description : configure TI1FP1 channel polarity and filter 
* Input:
  TIMx : timer instance    
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...   
  Filter:  TIM_TI1_FILTER_LVL(x), x=0-15  
* Output      : none  
* Author      : xwl                       
**********************************************************************************/ 
static void TIMER_TI1FP1_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t Filter)
{    
    TIMx->CCER &= (~BIT0);  //Disable the Channel 1: Reset the CC1E Bit   
    TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT0|BIT1)) | BIT0);    // CH1 as input 
  
    TIMx->CCMR1 &= (~0xF0U); // reset TI1 filter   
    TIMx->CCMR1 |= Filter; 
    
    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_RISING;   
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_FALLING;      
    }
    else
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_BOTH;     
    }
}

/*********************************************************************************
* Function    : TIMER_TI2FP2_ConfigInputStage  
* Description : configure TI2FP2 channel polarity and filter 
* Input:
  TIMx : timer instance    
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...   
  Filter:  TIM_TI2_FILTER_LVL(x), x=0-15  
* Output      : none  
* Author      : xwl                       
**********************************************************************************/ 
static void TIMER_TI2FP2_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t Filter)
{    
    TIMx->CCER &= (~BIT4);  //Disable the Channel 2: Reset the CC2E Bit   
    TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT8|BIT9)) | BIT8);    // CH2 as input 
  
    TIMx->CCMR1 &= (~0xF000U); // reset TI2 filter    
    TIMx->CCMR1 |= Filter;   
    
    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_RISING;   
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_FALLING;      
    }
    else
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_BOTH;     
    }
}

/*********************************************************************************
* Function    : TIMER_IC1_SetConfig  
* Description : configure TI1FP1 or TI2FP1 channel polarity and filter 
* Input:
  TIMx : timer instance    
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...   
  Filter:  TIM_TI1_FILTER_LVL(x), x=0-15  
* Output      : none  
* Author      : xwl                       
**********************************************************************************/ 
void TIMER_IC1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t Filter)
{
    /* Disable the Channel 1: Reset the CC1E Bit */
    TIMx->CCER &= (~BIT0);  

    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_RISING;   
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_FALLING;      
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_RISING_FALLING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_BOTH;     
    }
        
    if(TIM_ICSELECTION_DIRECTTI == TIM_ICSelection)     
    {
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT0|BIT1))) | BIT0;   
        TIMx->CCMR1 &= (~0xF0U);  
    }
    else
    {
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT0|BIT1))) | BIT1;     
        TIMx->CCMR1 &= (~0xF000U);    
    }
    
    TIMx->CCMR1 |= Filter;  
       
}

/*********************************************************************************
* Function    : TIMER_IC2_SetConfig  
* Description : configure TI1FP2 or TI2FP2 channel polarity and filter 
* Input:
  TIMx : timer instance    
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...   
  Filter:  TIM_TI2_FILTER_LVL(x), x=0-15  
* Output      : none  
* Author      : xwl                       
**********************************************************************************/ 
static void TIMER_IC2_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t Filter)
{
    /* Disable the Channel 2, Reset the CC2E Bit */
    TIMx->CCER &= (~BIT4); 
    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_RISING;    
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_FALLING;         
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_RISING_FALLING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_BOTH;       
    }
        
    if(TIM_ICSELECTION_DIRECTTI == TIM_ICSelection)     
    {
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT8|BIT9))) | BIT8; 
        TIMx->CCMR1 &= (~0xF000U);   
    }
    else
    {
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT8|BIT9))) | BIT9; 
        TIMx->CCMR1 &= (~0xF0U);     
    }
    
    TIMx->CCMR1 |= Filter;     
      
}  

/*********************************************************************************
* Function    : TIMER_IC3_SetConfig  
* Description : configure TI3FP3 or TI4FP3 channel polarity and filter 
* Input:
  TIMx : timer instance    
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...   
  Filter:  TIM_TI3_FILTER_LVL(x), x=0-15  
* Output      : none  
* Author      : xwl                       
**********************************************************************************/ 
static void TIMER_IC3_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t Filter)
{
    /* Disable the Channel 3, Reset the CC3E Bit */
    TIMx->CCER &= (~BIT8); 
    
    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC3_SLAVE_CAPTURE_POL_RISING;    
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC3_SLAVE_CAPTURE_POL_FALLING;         
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_RISING_FALLING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC3_SLAVE_CAPTURE_POL_BOTH;       
    }
        
    if(TIM_ICSELECTION_DIRECTTI == TIM_ICSelection)        
    {
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT0|BIT1))) | BIT0;    
        TIMx->CCMR2 &= (~0xF0U);    
    }
    else
    {
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT0|BIT1))) | BIT1;       
        TIMx->CCMR2 &= (~0xF000U);     
    }
     

    TIMx->CCMR2 |= Filter;  
}


/*********************************************************************************
* Function    : TIMER_IC4_SetConfig  
* Description : configure TI3FP4 or TI4FP4 channel polarity and filter 
* Input:
  TIMx : timer instance    
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...   
  Filter:  TIM_TI4_FILTER_LVL(x), x=0-15  
* Output      : none  
* Author      : xwl                             
**********************************************************************************/ 
static void TIMER_IC4_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t Filter)
{
     /* Disable the Channel 3, Reset the CC3E Bit */
    TIMx->CCER &= (~BIT12);   
    
    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC4_SLAVE_CAPTURE_POL_RISING;    
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)  
    {
        TIMx->CCER |= TIM_CC4_SLAVE_CAPTURE_POL_FALLING;         
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_RISING_FALLING == TIM_ICPolarity)    
    {
        TIMx->CCER |= TIM_CC4_SLAVE_CAPTURE_POL_BOTH;         
    }

    if(TIM_ICSELECTION_DIRECTTI == TIM_ICSelection)     
    {
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT8|BIT9))) | BIT8;    
        TIMx->CCMR2 &= (~0xF000U);    
    }
    else
    {
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT8|BIT9))) | BIT9;    
        TIMx->CCMR2 &= (~0xF0U);           
    }

    TIMx->CCMR2 |= Filter;     
       
}








/*********************************************************************************
* Function    : HAL_TIMER_64_Base_Init    
* Description : start 64 bit timer   
* Input       : timer instance  
* Output      : none 
* Author      : xwl                       
**********************************************************************************/      
void HAL_TIMER_64_Base_Init(TIM_64_HandleTypeDef *htim)  
{   
    
    htim->Instance->CTRL = htim->Instance->CTRL & (~(0x7FU << 1)); 
    htim->Instance->CTRL |= ( (htim->Init.Cnt_Mode << 1) | (htim->Init.Prescaler << 2)   );  
    
    htim->Instance->CTRL = (htim->Instance->CTRL & (~(1U << 9) ) ) | (htim->Init.ARR_Preload_En << 9);     
    
    if (TIM_64_ARR_MODE == htim->Init.Cnt_Mode) 
    {
        htim->Instance->ARR_LOW = htim->Init.Period_Low;
        htim->Instance->ARR_HIGH = htim->Init.Period_High;             
        htim->Instance->CTRL |= BIT10;  // Load ARR value         
    }
    
    htim->Instance->CNT_LOW = htim->Init.Count_Low; 
    htim->Instance->CNT_HIGH = htim->Init.Count_High;    
    
    htim->Instance->CTRL |= BIT11;  // Load Initial count value    
    
    return;       
}

/*********************************************************************************
* Function    : HAL_TIMER_64_Enable_Interrupt    
* Description : enable 64 bit timer interrupt 
* Input       : timer instance  
* Output      : none 
* Author      : xwl                       
**********************************************************************************/      
void HAL_TIMER_64_Enable_Interrupt(TIM_64BIT_TypeDef *TIMx)
{   
    TIMx->CTRL |= BIT8;    
    
    return;       
}


/*********************************************************************************
* Function    : HAL_TIMER_64_Base_Start    
* Description : start 64 bit timer   
* Input       : timer instance  
* Output      : none 
* Author      : xwl                       
**********************************************************************************/      
void HAL_TIMER_64_Base_Start(TIM_64BIT_TypeDef *TIMx)
{   
    TIMx->CTRL |= BIT0;    
    
    return;       
}


/*********************************************************************************
* Function    : HAL_TIMER_64_Base_Start    
* Description : start 64 bit timer   
* Input       : timer instance  
* Output      : none 
* Author      : xwl                       
**********************************************************************************/      
long long HAL_TIMER_64_Base_Read_Count(TIM_64BIT_TypeDef *TIMx)
{   
    volatile long long low, high, high_2;   
    
    while(1)
    {
        high = TIMx->CNT_HIGH; 
        low = TIMx->CNT_LOW;       
        high_2 = TIMx->CNT_HIGH;   
        
        if (high_2 == high)
        {
            break; 
        }
    }
    
    
    return (high << 32) + low;          
}

#endif

