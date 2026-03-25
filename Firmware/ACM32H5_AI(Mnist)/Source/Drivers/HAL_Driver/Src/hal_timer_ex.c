/***********************************************************************
 * Filename    : hal_timer_ex.c
 * Description : TIMER driver source file
 * Author(s)   : xwl  
 * version     : V1.0
 * Modify date : 2021-04-02
 ***********************************************************************/
#include "hal.h" 

#ifdef HAL_TIMER_MODULE_ENABLED

/*********************************************************************************
* Function    : HAL_TIMER_ConfigBreakDeadTime  
* Description : configure deadtime parameter   
* Input       : timer handler, break and deadtime configuration  
* Output      : none  
* Author      : xwl                       
**********************************************************************************/  
void HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim, TIM_BreakDeadTimeConfigTypeDef * sBreakDeadTimeConfig)
{
  /* Keep this variable initialized to 0 as it is used to configure BDTR register */
    uint32_t break_deadtime_reg = 0U;

    /* Set the BDTR bits */
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_DTG,  sBreakDeadTimeConfig->DeadTime);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_LOCK, sBreakDeadTimeConfig->LockLevel);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_OSSI, sBreakDeadTimeConfig->OffStateIDLEMode);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_OSSR, sBreakDeadTimeConfig->OffStateRunMode);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_BKE, sBreakDeadTimeConfig->BreakState);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_BKP, sBreakDeadTimeConfig->BreakPolarity);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_AOE, sBreakDeadTimeConfig->AutomaticOutput);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_BKF, (sBreakDeadTimeConfig->BreakFilter << TIM_BDTR_BKF_Pos));
  
    /* Set TIMx_BDTR */
    htim->Instance->BDTR = break_deadtime_reg;  

}
  
/*********************************************************************************
* Function    : HAL_TIMEx_ConfigBreakInput  
* Description : Configures the break input source.  
* Input       :
              htim: timer handler 
              BreakInput: TIM_BREAKINPUT_BRK  
              sBreakInputConfig: Break input source configuration   
* Output      :   
* Author      : xwl                       
**********************************************************************************/
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakInput(TIM_HandleTypeDef *htim, TIMEx_BreakInputConfigTypeDef *sBreakInputConfig)
{
    uint32_t tmporx;
    uint32_t bkin_enable_mask;
    uint32_t bkin_polarity_mask;
    uint32_t bkin_enable_bitpos;
    uint32_t bkin_polarity_bitpos;   

    switch(sBreakInputConfig->Source)
    {
        case TIM_BREAKINPUTSOURCE_BKIN:
        {
            bkin_enable_mask = TIM1_AF1_BKINE;
            bkin_enable_bitpos = TIM1_AF1_BKINE_Pos;
            bkin_polarity_mask = TIM1_AF1_BKINP;
            bkin_polarity_bitpos = TIM1_AF1_BKINP_Pos;  
            break;
        }
        case TIM_BREAKINPUTSOURCE_COMP1:
        {
            bkin_enable_mask = TIM1_AF1_BKCMP1E;
            bkin_enable_bitpos = TIM1_AF1_BKCMP1E_Pos;
            bkin_polarity_mask = TIM1_AF1_BKCMP1P;
            bkin_polarity_bitpos = TIM1_AF1_BKCMP1P_Pos;
            break;
        }
        case TIM_BREAKINPUTSOURCE_COMP2:
        {
            bkin_enable_mask = TIM1_AF1_BKCMP2E;
            bkin_enable_bitpos = TIM1_AF1_BKCMP2E_Pos;
            bkin_polarity_mask = TIM1_AF1_BKCMP2P;
            bkin_polarity_bitpos = TIM1_AF1_BKCMP2P_Pos;
            break;
        }
        case TIM_BREAKINPUTSOURCE_COMP3:
        {
            bkin_enable_mask = TIM1_AF1_BKCMP3E;
            bkin_enable_bitpos = TIM1_AF1_BKCMP3E_Pos;
            bkin_polarity_mask = TIM1_AF1_BKCMP3P;
            bkin_polarity_bitpos = TIM1_AF1_BKCMP3P_Pos;
            break;
        }
        case TIM_BREAKINPUTSOURCE_COMP4:
        {
            bkin_enable_mask = TIM1_AF1_BKCMP4E;
            bkin_enable_bitpos = TIM1_AF1_BKCMP4E_Pos;
            bkin_polarity_mask = TIM1_AF1_BKCMP4P;
            bkin_polarity_bitpos = TIM1_AF1_BKCMP4P_Pos;
            break;
        }

        default:
        {
            bkin_enable_mask = 0U;
            bkin_enable_bitpos = 0U;
            bkin_polarity_mask = 0U;
            bkin_polarity_bitpos = 0U;
            return HAL_ERROR;  
        }
    }
  
    /* Get the TIMx_AF1 register value */
    tmporx = htim->Instance->AF1;

    /* Enable the break input */
    tmporx &= ~bkin_enable_mask;
    tmporx |= (sBreakInputConfig->Enable << bkin_enable_bitpos) & bkin_enable_mask;

    /* Set the break input polarity */
    tmporx &= ~bkin_polarity_mask;
    tmporx |= (sBreakInputConfig->Polarity << bkin_polarity_bitpos) & bkin_polarity_mask;

    /* Set TIMx_AF1 */
    htim->Instance->AF1 = tmporx;  
    
    return HAL_OK;  
}   


/*********************************************************************************
* Function    : HAL_TIMEx_ConfigCommutEvent  
* Description : Configure the TIM commutation event sequence. This function is mandatory to use the commutation event 
                in order to update the configuration at each commutation detection on the TRGI input of the Timer.
* Input       :
              htim: timer handler 
              InputTrigger: TIM_TS_ITR0, TIM_TS_ITR1...   
              CommutationSource: TIM_COMMUTATION_TRGI, TIM_COMMUTATION_SOFTWARE  
* Output      :   
* Author      : xwl                       
**********************************************************************************/ 
void HAL_TIMEx_ConfigCommutEvent(TIM_HandleTypeDef *htim, uint32_t  InputTrigger, uint32_t  CommutationSource)
{

    if ((InputTrigger == TIM_TS_ITR0) || \
        (InputTrigger == TIM_TS_ITR1) || \
        (InputTrigger == TIM_TS_ITR2) || \
        (InputTrigger == TIM_TS_ITR3) || \
        (InputTrigger == TIM_TS_ITR4) || \
        (InputTrigger == TIM_TS_ITR5) || \
        (InputTrigger == TIM_TS_ITR6) || \
        (InputTrigger == TIM_TS_ITR7) || \
        (InputTrigger == TIM_TS_ITR8) || \
        (InputTrigger == TIM_TS_ITR9) || \
        (InputTrigger == TIM_TS_ITR10))
    {
        /* Select the Input trigger */
        htim->Instance->SMCR &= (~TIM_SMCR_TS_Msk);
        htim->Instance->SMCR |= InputTrigger;
    }

    /* Select the Capture Compare preload feature */
    htim->Instance->CR2 |= TIM_CR2_CCPC;
    /* Select the Commutation event source */
    htim->Instance->CR2 &= ~TIM_CR2_CCUS;
    htim->Instance->CR2 |= CommutationSource;

    /* Disable Commutation Interrupt */
    HAL_TIM_DISABLE_IT(htim, TIM_IT_COM);

  /* Disable Commutation DMA request */
    HAL_TIM_DISABLE_DMA(htim, TIM_DMA_COM);

}

/*********************************************************************************
* Function    : HAL_TIMEx_ConfigCommutEvent  
* Description : Configure the TIM commutation event sequence. This function is mandatory to use the commutation event 
                in order to update the configuration at each commutation detection on the TRGI input of the Timer.
* Input       :
              htim: timer handler 
              Channel: specifies the TIM Channel   
              TISelection£º specifies the timer input source.
                            please refer the define.
                            For example for TIM1:
*         For TIM1 this parameter can be one of the following values:
*            TIM_TIM1_TI1_GPIO:                TIM1 TI1 is connected to GPIO
*            TIM_TIM1_TI1_COMP1:               TIM1 TI1 is connected to COMP1 output
*            TIM_TIM1_TI1_COMP2:               TIM1 TI1 is connected to COMP2 output
*            TIM_TIM1_TI1_COMP3:               TIM1 TI1 is connected to COMP3 output
*            TIM_TIM1_TI1_COMP4:               TIM1 TI1 is connected to COMP4 output
* Output      : HAL status 
**********************************************************************************/ 
HAL_StatusTypeDef  HAL_TIMEx_TISelection(TIM_HandleTypeDef *htim, uint32_t TISelection, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  switch (Channel)
  {
    case TIM_CHANNEL_1:
      MODIFY_REG(htim->Instance->TISEL, TIM_TISEL_TI1SEL, TISelection);
      break;
    case TIM_CHANNEL_2:
      MODIFY_REG(htim->Instance->TISEL, TIM_TISEL_TI2SEL, TISelection);
      break;
    case TIM_CHANNEL_3:
      MODIFY_REG(htim->Instance->TISEL, TIM_TISEL_TI3SEL, TISelection);
      break;
    case TIM_CHANNEL_4:
      MODIFY_REG(htim->Instance->TISEL, TIM_TISEL_TI4SEL, TISelection);
      break;
    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/*********************************************************************************
* Function    : HAL_TIMEx_Encoder_MspInit  
* Description : Initializes Encoder MSP.
* Input       :
              htim: timer handler 
* Output      : None 
**********************************************************************************/ 
__WEAK void HAL_TIMEx_Encoder_MspInit(TIM_HandleTypeDef *htim)
{

}

/*********************************************************************************
* Function    : HAL_TIMEx_Encoder_MspDeInit  
* Description : DeInitializes Encoder MSP.
* Input       :
              htim: timer handler 
* Output      : None 
**********************************************************************************/ 
__WEAK void HAL_TIMEx_Encoder_MspDeInit(TIM_HandleTypeDef *htim)
{

}

/*********************************************************************************
* Function    : HAL_TIMEx_HallSensor_Init  
* Description : Configure the TIM encoder mode.
* Input       :
              htim: timer handler 
              EncoderMode: TIM encoder mode, only can be: TIM_SLAVE_MODE_ENC1, TIM_SLAVE_MODE_ENC2, TIM_SLAVE_MODE_ENC3;
* Output      : HAL status 
**********************************************************************************/ 
HAL_StatusTypeDef HAL_TIMEx_Encoder_Init(TIM_HandleTypeDef *htim, uint8_t EncoderMode)
{    

    /* Init the low level hardware : GPIO, CLOCK, NVIC and DMA */
    HAL_TIMEx_Encoder_MspInit(htim);

    /* Configure the encoder mode */
	htim->Instance->SMCR = (htim->Instance->SMCR & ~(BIT0|BIT1|BIT2) | EncoderMode);
    
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIMEx_Encoder_Enable  
* Description : Enable the TIM encoder.
* Input       :
              htim: timer handler 
* Output      : HAL status 
**********************************************************************************/ 
HAL_StatusTypeDef HAL_TIMEx_Encoder_Enable(TIM_HandleTypeDef *htim)
{    

    /* Enable the TIM */
    htim->Instance->CR1 |= BIT0;

    return HAL_OK;
}

uint32_t HAL_TIMEx_Encoder_GetValue(TIM_HandleTypeDef *htim)
{      
    return ((uint32_t)htim->Instance->CNT);
}

#endif
