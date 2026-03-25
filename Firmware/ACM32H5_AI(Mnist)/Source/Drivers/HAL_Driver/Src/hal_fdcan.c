#include "hal_fdcan.h"

#ifdef HAL_FDCAN_MODULE_ENABLED

__weak void HAL_FDCAN_IRQHandler(FDCAN_HandleTypeDef *hfdcan)
{
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_RX_BUFFER_NEW_MESSAGE) != 0U)
    {
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_RX_BUFFER_NEW_MESSAGE);        
        HAL_FDCAN_RxBufferNewMessageCallback(hfdcan);
    }
    
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_RX_BUFFER_FULL) != 0U)
    {
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_RX_BUFFER_FULL);
        HAL_FDCAN_RxBufferFullCallback(hfdcan);
    }
    
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_RX_BUFFER_OVERRUN) != 0U)
    {
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_RX_BUFFER_OVERRUN);
        HAL_FDCAN_RxBufferOVCallback(hfdcan);
    }
    
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_TX_STB_COMPLETE) != 0U)
    {
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_TX_STB_COMPLETE);
        HAL_FDCAN_TXSTBCompletedCallback(hfdcan);
    }
    
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_TX_PTB_COMPLETE) != 0U)
    {
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_TX_PTB_COMPLETE);
        HAL_FDCAN_TXPTBCompletedCallback(hfdcan); 
    }
    
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_RX_BUFFER_ALMOSTFULL) != 0U)
    {
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_RX_BUFFER_ALMOSTFULL);
//        HAL_FDCAN_RxBufferAFCallback(hfdcan);
    }
    
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_TX_ABORT_COMPLETE) != 0U)
    {
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_TX_ABORT_COMPLETE);
        HAL_FDCAN_TxAbortCallback(hfdcan);
    }
    
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_ERROR) != 0U)
    {        
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_ERROR);
        HAL_FDCAN_ErrorCallback(hfdcan);
    }
    
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_BUS_ERROR) != 0U)
    {
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_BUS_ERROR);
        HAL_FDCAN_BusErrorCallback(hfdcan);
    }
    
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_ERROR_PASSIVE) != 0U)
    {
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_ERROR_PASSIVE);
        HAL_FDCAN_ErrorPassiveCallback(hfdcan);
    }
    
    if (__HAL_FDCAN_GET_FLAG(hfdcan, FDCAN_FLAG_ARBITRATION_LOST) != 0U)
    {
        __HAL_FDCAN_CLEAR_FLAG(hfdcan, FDCAN_FLAG_ARBITRATION_LOST);
        HAL_FDCAN_ArbitrationLostCallback(hfdcan);
    }
    
    if(__HAL_FDCAN_TT_GET_FLAG(hfdcan, FDCAN_TTCFG_REFMSGIF))
    {
        __HAL_FDCAN_TT_CLEAR_FLAG(hfdcan, FDCAN_TTCFG_REFMSGIF);
         printfS("REFMSGIF\r\n");
    }
    
    if(__HAL_FDCAN_TT_GET_FLAG(hfdcan, FDCAN_TTCFG_WTIF))
    {
        __HAL_FDCAN_TT_CLEAR_FLAG(hfdcan, FDCAN_TTCFG_WTIF);
         printfS("WTIF\r\n");
    }
    
    if(__HAL_FDCAN_TT_GET_FLAG(hfdcan, FDCAN_TTCFG_TTIF))
    {
        __HAL_FDCAN_TT_CLEAR_FLAG(hfdcan, FDCAN_TTCFG_TTIF);
        HAL_FDCAN_TT_TimerTriggerCallback(hfdcan);
        
    }
    
    if(__HAL_FDCAN_TT_GET_FLAG(hfdcan, FDCAN_TTCFG_TEIF))
    {
        __HAL_FDCAN_TT_CLEAR_FLAG(hfdcan, FDCAN_TTCFG_TEIF);
        printfS("TEIF\r\n");
    }

}


/**
  * @brief  Initializes the FDCAN peripheral according to the specified
  *         parameters in the FDCAN_InitTypeDef structure.
  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_FDCAN_Init(FDCAN_HandleTypeDef *hfdcan)
{
    uint32_t tickstart;

    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));    
    assert_param(IS_FDCAN_RX_BUF_MODE(hfdcan->Init.RxBufOverFlowMode));

#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
  if (hfdcan->State == HAL_FDCAN_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hfdcan->Lock = HAL_UNLOCKED;

    /* Reset callbacks to legacy functions */
    hfdcan->TxEventFifoCallback         = HAL_FDCAN_TxEventFifoCallback;         /* Legacy weak TxEventFifoCallback */
    hfdcan->RxFifo0Callback             = HAL_FDCAN_RxFifo0Callback;             /* Legacy weak RxFifo0Callback     */
    hfdcan->RxFifo1Callback             = HAL_FDCAN_RxFifo1Callback;             /* Legacy weak RxFifo1Callback     */
    hfdcan->TxFifoEmptyCallback         = HAL_FDCAN_TxFifoEmptyCallback;         /* Legacy weak TxFifoEmptyCallback */
    hfdcan->TxBufferCompleteCallback    = HAL_FDCAN_TxBufferCompleteCallback;    /* Legacy weak
                                                                                    TxBufferCompleteCallback        */
    hfdcan->TxBufferAbortCallback       = HAL_FDCAN_TxBufferAbortCallback;       /* Legacy weak
                                                                                    TxBufferAbortCallback           */
    hfdcan->HighPriorityMessageCallback = HAL_FDCAN_HighPriorityMessageCallback; /* Legacy weak
                                                                                    HighPriorityMessageCallback     */
    hfdcan->TimestampWraparoundCallback = HAL_FDCAN_TimestampWraparoundCallback; /* Legacy weak
                                                                                    TimestampWraparoundCallback     */
    hfdcan->TimeoutOccurredCallback     = HAL_FDCAN_TimeoutOccurredCallback;     /* Legacy weak
                                                                                    TimeoutOccurredCallback         */
    hfdcan->ErrorCallback               = HAL_FDCAN_ErrorCallback;               /* Legacy weak ErrorCallback       */
    hfdcan->ErrorStatusCallback         = HAL_FDCAN_ErrorStatusCallback;         /* Legacy weak ErrorStatusCallback */

    if (hfdcan->MspInitCallback == NULL)
    {
      hfdcan->MspInitCallback = HAL_FDCAN_MspInit;  /* Legacy weak MspInit */
    }

    /* Init the low level hardware: CLOCK, NVIC */
    hfdcan->MspInitCallback(hfdcan);
  }
#else
    if (hfdcan->State == HAL_FDCAN_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        hfdcan->Lock = HAL_UNLOCKED;

        /* Init the low level hardware: CLOCK, NVIC */
        HAL_FDCAN_MspInit(hfdcan);
    }
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

    /* Enter to RESET state */
    __HAL_FDCAN_ENTER_RESET_STATE(hfdcan);
    
    MODIFY_REG(hfdcan->Instance->CR, FDCAN_CR_FD_ISO, hfdcan->Init.FrameISOType);
    
    /* Set the nominal bit timing register */
    hfdcan->Instance->SBTR.b.PRESC = (uint8_t)hfdcan->Init.NominalPrescaler - 1;
    hfdcan->Instance->SBTR.b.SJW   = (uint8_t)hfdcan->Init.NominalSyncJumpWidth;
    hfdcan->Instance->SBTR.b.SEG1  = (uint8_t)hfdcan->Init.NominalTimeSeg1 - 2;
    hfdcan->Instance->SBTR.b.SEG2  = (uint8_t)hfdcan->Init.NominalTimeSeg2 - 1;

    /* If FD operation with BRS is selected, set the data bit timing register */
    hfdcan->Instance->FBTR.b.PRESC = (uint8_t)hfdcan->Init.DataPrescaler - 1;
    hfdcan->Instance->FBTR.b.SJW   = (uint8_t)hfdcan->Init.DataSyncJumpWidth;
    hfdcan->Instance->FBTR.b.SEG1  = (uint8_t)hfdcan->Init.DataTimeSeg1 - 2;
    hfdcan->Instance->FBTR.b.SEG2  = (uint8_t)hfdcan->Init.DataTimeSeg2 - 1;

    __HAL_FDCAN_EXIT_RESET_STATE(hfdcan);
    
    
    if((hfdcan->Init.AutoRetransmission == DISABLE) || (hfdcan->Init.Mode == FDCAN_MODE_LBME))
    {
        /* single shot mode */
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TPSS);
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TSSS);        
    }
    else
    {
        /* Auto re-transmission */
        CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_TPSS);
        CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_TSSS);        
    }
    
    if(hfdcan->Init.RxBufOverFlowMode == FDCAN_RX_BUF_BLOCKING)
    {
        /* 1 - The new message will not be stored */
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_ROM);
    }
    else
    {
        /* 0 - The oldest message will be overwritten */
        CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_ROM);
    }
    

    /* Get tick */
    tickstart = HAL_GetTick();

    /* Reset FDCAN Operation Mode */
    CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_LBME | FDCAN_CR_LBMI | FDCAN_CR_LOM | FDCAN_CR_SACK);
    
    SET_BIT(hfdcan->Instance->CR, hfdcan->Init.Mode);

    /* Initialize the error code */
    hfdcan->ErrorCode = ERR_FDCAN_NONE;

    /* Initialize the FDCAN state */
    hfdcan->State = HAL_FDCAN_STATE_READY;

    /* Return function status */
    return HAL_OK;
}


HAL_StatusTypeDef HAL_FDCAN_Start(FDCAN_HandleTypeDef *hfdcan)
{
#if 0    
  if (hfdcan->State == HAL_FDCAN_STATE_READY)
  {
    /* Change FDCAN peripheral state */
    hfdcan->State = HAL_FDCAN_STATE_BUSY;

    /* Request leave initialisation */
    __HAL_FDCAN_EXIT_RESET_STATE(hfdcan);

    /* Reset the FDCAN ErrorCode */
    hfdcan->ErrorCode = ERR_FDCAN_NONE;

    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Update error code */
    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;

    return HAL_ERROR;
  }
#endif
    /* Request leave initialisation */
    __HAL_FDCAN_EXIT_RESET_STATE(hfdcan);

    /* Reset the FDCAN ErrorCode */
    hfdcan->ErrorCode = ERR_FDCAN_NONE;

    /* Return function status */
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_Stop(FDCAN_HandleTypeDef *hfdcan)
{
#if 0    
  uint32_t Counter = 0U;

  if (hfdcan->State == HAL_FDCAN_STATE_BUSY)
  {
    /* Request initialisation */
    SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_INIT);

    /* Wait until the INIT bit into CCCR register is set */
    while ((hfdcan->Instance->CCCR & FDCAN_CCCR_INIT) == 0U)
    {
      /* Check for the Timeout */
      if (Counter > FDCAN_TIMEOUT_COUNT)
      {
        /* Update error code */
        hfdcan->ErrorCode |= HAL_FDCAN_ERROR_TIMEOUT;

        /* Change FDCAN state */
        hfdcan->State = HAL_FDCAN_STATE_ERROR;

        return HAL_ERROR;
      }

      /* Increment counter */
      Counter++;
    }

    /* Reset counter */
    Counter = 0U;

    /* Exit from Sleep mode */
    CLEAR_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_CSR);

    /* Wait until FDCAN exits sleep mode */
    while ((hfdcan->Instance->CCCR & FDCAN_CCCR_CSA) == FDCAN_CCCR_CSA)
    {
      /* Check for the Timeout */
      if (Counter > FDCAN_TIMEOUT_COUNT)
      {
        /* Update error code */
        hfdcan->ErrorCode |= HAL_FDCAN_ERROR_TIMEOUT;

        /* Change FDCAN state */
        hfdcan->State = HAL_FDCAN_STATE_ERROR;

        return HAL_ERROR;
      }

      /* Increment counter */
      Counter++;
    }

    /* Enable configuration change */
    SET_BIT(hfdcan->Instance->CCCR, FDCAN_CCCR_CCE);

    /* Reset Latest Tx FIFO/Queue Request Buffer Index */
    hfdcan->LatestTxFifoQRequest = 0U;

    /* Change FDCAN peripheral state */
    hfdcan->State = HAL_FDCAN_STATE_READY;

    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Update error code */
    hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_STARTED;

    return HAL_ERROR;
  }
#endif
    return HAL_OK;
}



HAL_StatusTypeDef HAL_FDCAN_ConfigFilter(FDCAN_HandleTypeDef *hfdcan, FDCAN_FilterTypeDef *sFilterConfig)
{
#if 0    
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    assert_param(IS_FILTER_ID_TYPE(sFilterConfig->IdType));
    assert_param(IS_VALID_FILTER_INDEX(sFilterConfig->FilterIndex));    
    
    __HAL_FDCAN_ENTER_RESET_STATE(hfdcan);

    //MODIFY_REG(hfdcan->Instance->ACFCR.w, FDCAN_ACFCR_ACFADR_Msk, sFilterConfig->FilterIndex << FDCAN_ACFCR_ACFADR_Pos);
    hfdcan->Instance->ACFCR.b.ACFADR = sFilterConfig->FilterIndex;
    
    /* select ACODE */
    //CLEAR_BIT(hfdcan->Instance->ACFCR.w, FDCAN_ACFCR_SELMASK);
    hfdcan->Instance->ACFCR.b.SELMASK = 0;
    hfdcan->Instance->ACODR.b.ACM = sFilterConfig->FilerCode & 0x1FFFFFFF;
    /* select AMASK */
    //SET_BIT(hfdcan->Instance->ACFCR.w, FDCAN_ACFCR_SELMASK);
    hfdcan->Instance->ACFCR.b.SELMASK = 1;
    hfdcan->Instance->ACODR.b.ACM = sFilterConfig->FilerMask & 0x1FFFFFFF;
    
    if(sFilterConfig->IdType == FDCAN_STANDARD_ID)
    {
        hfdcan->Instance->ACODR.b.AIDEE = 1;
        hfdcan->Instance->ACODR.b.AIDE = 0;
    }
    else if(sFilterConfig->IdType == FDCAN_EXTENDED_ID)
    {
        hfdcan->Instance->ACODR.b.AIDEE = 1;
        hfdcan->Instance->ACODR.b.AIDE = 1;
    }
    else
    {
        hfdcan->Instance->ACODR.b.AIDEE = 0;
    }
    
    __HAL_FDCAN_EXIT_RESET_STATE(hfdcan);
    
    //SET_BIT(hfdcan->Instance->ACFCR.w, sFilterConfig->FilterIndex << FDCAN_ACFCR_AE_Pos);
    hfdcan->Instance->ACFCR.b.AE |= 1 << sFilterConfig->FilterIndex;
#endif
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_NewConfigFilter(FDCAN_HandleTypeDef *hfdcan, FDCAN_NewFilterTypeDef *sFilterConfig)
{
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
//    assert_param(IS_FILTER_ID_TYPE(sFilterConfig->IdType));
    assert_param(IS_VALID_FILTER_INDEX(sFilterConfig->FilterIndex));    
    
    __HAL_FDCAN_ENTER_RESET_STATE(hfdcan);

    printfS("\r\n[过滤器%d]====================================:\r\n", sFilterConfig->FilterIndex);

    //MODIFY_REG(hfdcan->Instance->ACFCR.w, FDCAN_ACFCR_ACFADR_Msk, sFilterConfig->FilterIndex << FDCAN_ACFCR_ACFADR_Pos);
    hfdcan->Instance->ACFCR.b.ACFADR = sFilterConfig->FilterIndex;
    
    switch(sFilterConfig->FilterType)
    {
        case FDCAN_FILTER_TYPE0:
            hfdcan->Instance->ACFCR.b.SELMASK = 0;
            hfdcan->Instance->ACODR = sFilterConfig->Filter.type0.code32.w;
            hfdcan->Instance->ACFCR.b.SELMASK = 1;
            hfdcan->Instance->ACODR = sFilterConfig->Filter.type0.mask32.w;
        
            hfdcan->Instance->ACFMODE &= (~((1 << sFilterConfig->FilterIndex) << 16));    //32bit        
            hfdcan->Instance->ACFMODE &= (~(1 << sFilterConfig->FilterIndex));   //mask
            break;
        
        case FDCAN_FILTER_TYPE1:
            hfdcan->Instance->ACFCR.b.SELMASK = 0;
            hfdcan->Instance->ACODR = sFilterConfig->Filter.type1.code32.w;
            hfdcan->Instance->ACFCR.b.SELMASK = 1;
            hfdcan->Instance->ACODR = sFilterConfig->Filter.type1.code32_2.w;
            
            hfdcan->Instance->ACFMODE &= (~((1 << sFilterConfig->FilterIndex) << 16));    //32bit
            hfdcan->Instance->ACFMODE |= (1 << sFilterConfig->FilterIndex);   //mask 无效
            break;
        
        case FDCAN_FILTER_TYPE2:
            hfdcan->Instance->ACFCR.b.SELMASK = 0;
            hfdcan->Instance->ACODR = sFilterConfig->Filter.type2.code16.hw | (sFilterConfig->Filter.type2.code16_2.hw << 16);
            hfdcan->Instance->ACFCR.b.SELMASK = 1;
            hfdcan->Instance->ACODR = sFilterConfig->Filter.type2.mask16.hw | (sFilterConfig->Filter.type2.mask16_2.hw << 16);
        
            hfdcan->Instance->ACFMODE |= (1 << sFilterConfig->FilterIndex) << 16;   //16bit
            hfdcan->Instance->ACFMODE &= (~(1 << sFilterConfig->FilterIndex));   //mask
            break;
        
        case FDCAN_FILTER_TYPE3:
            hfdcan->Instance->ACFCR.b.SELMASK = 0;
            hfdcan->Instance->ACODR = sFilterConfig->Filter.type3.code16.hw | (sFilterConfig->Filter.type3.code16_2.hw << 16);                                        
            hfdcan->Instance->ACFCR.b.SELMASK = 1;
            hfdcan->Instance->ACODR = sFilterConfig->Filter.type3.code16_3.hw | (sFilterConfig->Filter.type3.code16_4.hw << 16);
        
            hfdcan->Instance->ACFMODE |= (1 << sFilterConfig->FilterIndex) << 16;   //16bit
            hfdcan->Instance->ACFMODE |= 1 << sFilterConfig->FilterIndex;   //mask 无效
            break;
    }
    
    
    __HAL_FDCAN_EXIT_RESET_STATE(hfdcan);
        
    hfdcan->Instance->ACFCR.b.AE |= 1 << sFilterConfig->FilterIndex;

    return HAL_OK;
}


HAL_StatusTypeDef HAL_FDCAN_EnableLoopBackInternal(FDCAN_HandleTypeDef *hfdcan)
{
    assert_param (IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    if(HAL_FDCAN_GetBusStatus(hfdcan) & FDCAN_BUS_TACTIVE)
        return HAL_BUSY;
    
    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_LBMI);
    
    return HAL_OK;
}

/* FDCAN should be re-initisized after calling HAL_FDCAN_DisLoopBackInternal */
HAL_StatusTypeDef HAL_FDCAN_DisLoopBackInternal(FDCAN_HandleTypeDef *hfdcan)
{
    assert_param (IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_RESET);
    
    return HAL_OK;
}


HAL_StatusTypeDef HAL_FDCAN_EnableLoopBackExternal(FDCAN_HandleTypeDef *hfdcan, bool sack)
{
    assert_param (IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    if(HAL_FDCAN_GetBusStatus(hfdcan) & FDCAN_BUS_TACTIVE)
        return HAL_BUSY;
    
    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_LBME);
    if(sack)
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_SACK);
    else
        CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_SACK);
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_DisableLoopBackExternal(FDCAN_HandleTypeDef *hfdcan)
{
    assert_param (IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_LBME);
    
    return HAL_OK;
}
/******************************************************************************
*@brief : Transmission single shot mode configuration for PTB
*         
*@param : hfdcan: a pointer of FDCAN_HandleTypeDef structure which contains 
*                 the configuration information for the specified FDCAN.
*@param : state: Mode new state. This parameter can be: ENABLE or DISABLE.
*@note  : If state is ENABLE, The transmission for PTB is configed in single shot mode,
            otherwise it is in auto-retransmission mode.
          The configuration will reset to default mode(auto-retransmission mode) 
            by module local reset.  
*@return: None
******************************************************************************/
void HAL_FDCAN_PTBTranmistSingleShot(FDCAN_HandleTypeDef *hfdcan, FunctionalState state)
{
    assert_param (IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    assert_param (IS_FUNCTIONAL_STATE(state));
    
    if(state == ENABLE)
    {
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TPSS);
    }
    else
    {
        CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_TPSS);
    }
}

/******************************************************************************
*@brief : Transmission single shot mode configuration for STB
*         
*@param : hfdcan: a pointer of FDCAN_HandleTypeDef structure which contains 
*                 the configuration information for the specified FDCAN.
*@param : state: Mode new state. This parameter can be: ENABLE or DISABLE.
*@note  : If state is ENABLE, The transmission for PTB is configed in single shot mode,
            otherwise it is in auto-retransmission mode.
          The configuration will reset to default mode(auto-retransmission mode) 
            by module local reset.  
*@return: None
******************************************************************************/
void HAL_FDCAN_STBTranmistSingleShot(FDCAN_HandleTypeDef *hfdcan, FunctionalState state)
{
    assert_param (IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    assert_param (IS_FUNCTIONAL_STATE(state));
        
    if(state == ENABLE)
    {
        __HAL_FDCAN_ENABLE_IT(hfdcan, FDCAN_IE_BUS_ERROR | FDCAN_IE_ARBITRATION_LOST);
        
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TSSS);
    }
    else
    {
        CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_TSSS);
    }
}

HAL_StatusTypeDef HAL_FDCAN_ClearEntireSTB(FDCAN_HandleTypeDef *hfdcan)
{
    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TSALL | FDCAN_CR_TSA);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_AddMessageToPTB(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData)
{
    uint8_t i;
    
    uint8_t data_len;
    
    uint32_t* ptmp;
    
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    assert_param(IS_FDCAN_DLC(pTxHeader->FrameInfo.b.DLC));
    
    if(READ_BIT(hfdcan->Instance->CR, FDCAN_CR_TPE))
    {
        hfdcan->ErrorCode = ERR_FDCAN_PTB_LOCKED;
        return HAL_BUSY;
    }
    
    CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_TBSEL);
    
    ptmp = (uint32_t*)pTxHeader;
    
    hfdcan->Instance->TBUF[0] = *ptmp++;
    hfdcan->Instance->TBUF[1] = *ptmp;
        
    data_len = __HAL_FDCAN_DLC2LEN(pTxHeader->FrameInfo.b.DLC);
    
    for(i = 0; i < (data_len + 3) / 4; i++)
    {
        hfdcan->Instance->TBUF[2 + i] = *(uint32_t*)pTxData;
        pTxData += 4;
    }

    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_TransmitMessageByPTB(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData)
{
    HAL_StatusTypeDef status;
    
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));   
    assert_param(IS_FDCAN_DLC(pTxHeader->FrameInfo.b.DLC));    
        
    status = HAL_FDCAN_AddMessageToPTB(hfdcan, pTxHeader, pTxData);
    
    if(status)
        return status;
    
    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TPE); 
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_AddMessageToSTB(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData)
{
    uint8_t i;
    
    uint8_t data_len;
    
    uint32_t* ptmp;
    
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    assert_param(IS_FDCAN_DLC(pTxHeader->FrameInfo.b.DLC));

    if((hfdcan->Instance->CR & FDCAN_CR_TSSTAT) == (3 << FDCAN_CR_TSSTAT_Pos))
    {
        hfdcan->ErrorCode |= ERR_FDCAN_TXBUF_FULL;
        return HAL_BUSY;
    }

    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TBSEL);
    
    ptmp = (uint32_t*)pTxHeader;
    
    hfdcan->Instance->TBUF[0] = *ptmp++;
    hfdcan->Instance->TBUF[1] = *ptmp;
        
    data_len = __HAL_FDCAN_DLC2LEN(pTxHeader->FrameInfo.b.DLC);
    
    for(i = 0; i < (data_len + 3) / 4; i++)
    {
        hfdcan->Instance->TBUF[2 + i] = *(uint32_t*)pTxData;
        pTxData += 4;
    }
    
    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TSNEXT);    

    return HAL_OK;
}


HAL_StatusTypeDef HAL_FDCAN_EnableSTBPriorityMode(FDCAN_HandleTypeDef *hfdcan)
{
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TSMODE);
    return HAL_OK;    
}

HAL_StatusTypeDef HAL_FDCAN_DisableSTBPriorityMode(FDCAN_HandleTypeDef *hfdcan)
{
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_TSMODE);
    return HAL_OK;    
}

HAL_StatusTypeDef HAL_FDCAN_TransmitMessageBySTB(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData)
{
    HAL_StatusTypeDef status;
    
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    assert_param(IS_FDCAN_DLC(pTxHeader->FrameInfo.b.DLC));
    
    status = HAL_FDCAN_AddMessageToSTB(hfdcan, pTxHeader, pTxData);
    
    if(status)
        return status;
       
    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TSALL); 
    
    return HAL_OK;
}


HAL_StatusTypeDef HAL_FDCAN_EnableTxBufferRequest(FDCAN_HandleTypeDef *hfdcan, TransmitType_enum type)
{
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));    
    assert_param(IS_FDCAN_TRANSMIT_TYPE(type));
    
    if(type == FDCAN_TRANSMIT_PTB)
    {
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TPE); 
    }
    else if(type == FDCAN_TRANSMIT_STB_ALL)
    {
        if(READ_BIT(hfdcan->Instance->CR, FDCAN_CR_TSONE))
        {
            hfdcan->ErrorCode = HAL_FDCAN_ERROR_PENDING;
            return HAL_BUSY;
        }
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TSALL); 
    }
    else
    {
        if(READ_BIT(hfdcan->Instance->CR, FDCAN_CR_TSALL))
        {
            hfdcan->ErrorCode = HAL_FDCAN_ERROR_PENDING;
            return HAL_BUSY;
        }        
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TSONE); 
    }
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_AbortTxRequest(FDCAN_HandleTypeDef *hfdcan, TransmitAbortType_enum type)
{
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));        
    assert_param(IS_FDCAN_ABORT_TYPE(type));
    
    if(type == FDCAN_ABORT_PTB)
    {
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TPA); 
        while(READ_BIT(hfdcan->Instance->CR, FDCAN_CR_TPA));
    }
    else
    {
        
        SET_BIT(hfdcan->Instance->CR, FDCAN_CR_TSA); 
        while(READ_BIT(hfdcan->Instance->CR, FDCAN_CR_TSA));
    }    
    
    return HAL_OK;
}

//true: completed; false: not completed
bool HAL_FDCAN_GetTxReqCompleted(FDCAN_HandleTypeDef *hfdcan, TransmitType_enum type)
{
    bool tx_status = false; 
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    if(type == FDCAN_TRANSMIT_PTB)
    {
        if(!READ_BIT(hfdcan->Instance->CR, FDCAN_CR_TPE))
            tx_status = true;
    }
    else if(type == FDCAN_TRANSMIT_STB_ALL)
    {
        if(!READ_BIT(hfdcan->Instance->CR, FDCAN_CR_TSALL))
            tx_status = true;
    }
    else if(type == FDCAN_TRANSMIT_STB_ONE)
    {
        if(!READ_BIT(hfdcan->Instance->CR, FDCAN_CR_TSONE))
            tx_status = true;
    }
    
    return tx_status;
}

uint32_t HAL_FDCAN_GetBusStatus(FDCAN_HandleTypeDef *hfdcan)
{
   return (hfdcan->Instance->CR & 0x7);
}


HAL_StatusTypeDef HAL_FDCAN_WaitTxCompleted(FDCAN_HandleTypeDef *hfdcan, TransmitType_enum type, uint32_t timeout)
{
    uint32_t tickstart = 0;
    
    TransmitAbortType_enum abort_cmd;
    
    abort_cmd = (type == FDCAN_TRANSMIT_PTB)? FDCAN_ABORT_PTB : FDCAN_ABORT_STB;
    
    /* Get tick */
    tickstart = HAL_GetTick();
    
    while(!HAL_FDCAN_GetTxReqCompleted(hfdcan, type))
    {
        if((HAL_GetTick() - tickstart) > timeout)
        {
            /* Update error code */
            //hfdcan->ErrorCode |= ERR_FDCAN_TIMEOUT;
            
            HAL_FDCAN_AbortTxRequest(hfdcan, abort_cmd);

            return HAL_ERROR;
        }
    }
    
    return HAL_OK;
}

/* make sure the pRxData buffer size is aligned of uint32_t */
HAL_StatusTypeDef HAL_FDCAN_GetRxMessage(FDCAN_HandleTypeDef *hfdcan, FDCAN_RxHeaderTypeDef *pRxHeader, uint8_t *pRxData)
{
    
    uint8_t idx = 0;
    uint8_t i;
    uint8_t data_len;
    
    uint32_t* ptmp;// = (uint32_t*)pRxData;
    
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    assert_param(pRxHeader);
    assert_param(pRxData);    

    if((hfdcan->Instance->CR & FDCAN_CR_RSTAT) == 0)
    {
        hfdcan->ErrorCode |= ERR_FDCAN_RXBUF_EMPTY;
        return HAL_ERROR;
    }
    
    ptmp = (uint32_t*)pRxHeader;
    
    *ptmp = hfdcan->Instance->RBUF[idx++];
    ptmp++;
    *ptmp = hfdcan->Instance->RBUF[idx++];
    ptmp++;
    
    data_len = __HAL_FDCAN_DLC2LEN(pRxHeader->FrameInfo.b.DLC);
    
    for(i = 0; i < (data_len + 3) / 4; i++)
    {
        *(uint32_t*)pRxData = hfdcan->Instance->RBUF[idx++];
        pRxData += 4;
    }
    

    *ptmp = hfdcan->Instance->RBUF[18];
    ptmp++;
    *ptmp = hfdcan->Instance->RBUF[19];
    
    /* RELease buffer slot */
    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_RREL);
    
    return HAL_OK;
}

FDCAN_RXBUF_FILL_STATE_enum HAL_FDCAN_GetRxBufFillState(FDCAN_HandleTypeDef *hfdcan)
{
    uint32_t FillLevel;
    
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));

    FillLevel = (hfdcan->Instance->CR & FDCAN_CR_RSTAT) >> FDCAN_CR_RSTAT_Pos;
    
    if((FillLevel == FDCAN_RXBUF_FULL) && READ_BIT(hfdcan->Instance->CR, FDCAN_CR_ROV))
        FillLevel = FDCAN_RXBUF_OV;
    
    return (FDCAN_RXBUF_FILL_STATE_enum)FillLevel;
}


FDCAN_TXBUF_FILL_STATE_enum HAL_FDCAN_GetTxBufFillState(FDCAN_HandleTypeDef *hfdcan)
{
    uint32_t FreeLevel;
    
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    FreeLevel = (hfdcan->Instance->CR & FDCAN_CR_TSSTAT) >> FDCAN_CR_TSSTAT_Pos;

    /* Return Tx BUF free level */
    return (FDCAN_TXBUF_FILL_STATE_enum)FreeLevel;
}


HAL_StatusTypeDef HAL_FDCAN_ConfigRxBufWarnningLimit(FDCAN_HandleTypeDef *hfdcan, uint8_t afwl)
{
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    assert_param(IS_FDCAN_AFWL(afwl));

    MODIFY_REG(hfdcan->Instance->LIMIT, FDCAN_LIMIT_AFWL_Msk, afwl << FDCAN_LIMIT_AFWL_Pos);
    
    return HAL_OK;
}


uint8_t HAL_FDCAN_GetRxBufWarnningLimit(FDCAN_HandleTypeDef *hfdcan)
{
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));    
    
    return ((hfdcan->Instance->LIMIT & FDCAN_LIMIT_AFWL_Msk) >> FDCAN_LIMIT_AFWL_Pos);
}


HAL_StatusTypeDef HAL_FDCAN_ConfigErrCntWarnningLimit(FDCAN_HandleTypeDef *hfdcan, uint8_t ecnt)
{
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));    
    
    MODIFY_REG(hfdcan->Instance->LIMIT, FDCAN_LIMIT_EWL_Msk, ecnt << FDCAN_LIMIT_EWL_Pos);
    
    return HAL_OK;
}

uint8_t HAL_FDCAN_GetErrCntWarnningLimit(FDCAN_HandleTypeDef *hfdcan)
{
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));    
    
    return ((hfdcan->Instance->LIMIT & FDCAN_LIMIT_EWL_Msk) >> FDCAN_LIMIT_EWL_Pos);
    
    return HAL_OK;
}


HAL_StatusTypeDef HAL_FDCAN_ConfigRxBufOverwriteMode(FDCAN_HandleTypeDef *hfdcan, uint32_t OverwriteMode)
{
    /* Check function parameters */
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    assert_param(IS_FDCAN_RX_BUF_MODE(OverwriteMode));

    if (hfdcan->State == HAL_FDCAN_STATE_READY)
    {    
        if(hfdcan->Init.RxBufOverFlowMode == FDCAN_RX_BUF_BLOCKING)
        {
            /* 1 - The new message will not be stored */
            SET_BIT(hfdcan->Instance->CR, FDCAN_CR_ROM);
        }
        else
        {
            /* 0 - The oldest message will be overwritten */
            CLEAR_BIT(hfdcan->Instance->CR, FDCAN_CR_ROM);
        }
        
        /* Return function status */
        return HAL_OK;
    }
    else
    {
        /* Update error code */
        hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;

        return HAL_ERROR;
    }
}

HAL_StatusTypeDef HAL_FDCAN_TransceiverEnterSTBY(FDCAN_HandleTypeDef *hfdcan)
{
    SET_BIT(hfdcan->Instance->CR, FDCAN_CR_STBY);
    return HAL_OK;
}


__weak void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);
    
    /* NOTE : This function Should not be modified, when the callback is needed,
              the HAL_FDCAN_MspInit could be implemented in the user file
    */
}

HAL_StatusTypeDef HAL_FDCAN_GetErrorInfo(FDCAN_HandleTypeDef *hfdcan, FDCAN_ErrorInfo_u *errinfo)
{
    assert_param(IS_FDCAN_ALL_INSTANCE(hfdcan->Instance));
    
    if(!errinfo)
        return HAL_ERROR;
    
    errinfo->w = hfdcan->Instance->ECC.w;
    
    return HAL_OK;
}


__weak void HAL_FDCAN_RxBufferNewMessageCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}

__weak void HAL_FDCAN_RxBufferAFCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}

__weak void HAL_FDCAN_RxBufferFullCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}

__weak void HAL_FDCAN_RxBufferOVCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}

__weak void HAL_FDCAN_TXPTBCompletedCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}

__weak void HAL_FDCAN_TXSTBCompletedCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}

__weak void HAL_FDCAN_TxAbortCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}


__weak void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}

__weak void HAL_FDCAN_BusErrorCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}

__weak void HAL_FDCAN_ErrorPassiveCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}

__weak void HAL_FDCAN_ArbitrationLostCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}
/* ====================================================================================== */

__weak void HAL_FDCAN_TT_TimerTriggerCallback(FDCAN_HandleTypeDef *hfdcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hfdcan);

    /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FDCAN_RxBufferNewMessageCallback could be implemented in the user file
    */
}

HAL_StatusTypeDef HAL_FDCAN_TT_Config(FDCAN_HandleTypeDef *hfdcan, uint32_t TT_Presc)
{
    assert_param(IS_FDCAN_TT_INSTANCE(hfdcan->Instance));    
    assert_param(IS_FDCAN_TT_TPRESC(TT_Presc));
    
    CLEAR_BIT(hfdcan->Instance->TTCFG, FDCAN_TTCFG_TTEN);
    
    MODIFY_REG(hfdcan->Instance->TTCFG, FDCAN_TTCFG_T_PRESC, TT_Presc << FDCAN_TTCFG_T_PRESC_Pos);
    
    /* clear 'trigger error' interrupt flag */
    __HAL_FDCAN_TT_CLEAR_FLAG(hfdcan, FDCAN_TTCFG_TEIF);
    
    /* clear 'time trigger' interrupt flag */
    __HAL_FDCAN_TT_CLEAR_FLAG(hfdcan, FDCAN_TTCFG_TTIF);
    
    /* clear 'watch trigger' interrupt flag */
    __HAL_FDCAN_TT_CLEAR_FLAG(hfdcan, FDCAN_TTCFG_WTIF);
    
    /* Time Trigger Interrupt Enable */
    SET_BIT(hfdcan->Instance->TTCFG, FDCAN_TTCFG_TTIE);
    
    /* Watch Trigger Interrupt Flag */
    CLEAR_BIT(hfdcan->Instance->TTCFG, FDCAN_TTCFG_WTIE);
    
    SET_BIT(hfdcan->Instance->TTCFG, FDCAN_TTCFG_TTEN);
    
    SET_BIT(hfdcan->Instance->CR,  FDCAN_CR_TTTBM);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure TTCAN reference message
*         
*@param : hfdcan:       FDCAN_HandleTypeDef handler
*@param : IdType:       can be FDCAN_STANDARD_ID or FDCAN_EXTENDED_ID
*@param : Identifier :  frame ID
*@param : Payload: not  used
*
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_FDCAN_TT_ConfigReferenceMessage(FDCAN_HandleTypeDef *hfdcan, uint32_t IdType, uint32_t Identifier, uint32_t Payload)
{
    /* Check function parameters */
    assert_param(IS_FDCAN_TT_INSTANCE(hfdcan->Instance));
    assert_param(IS_FDCAN_ID_TYPE(IdType));
    
    if (IdType == FDCAN_STANDARD_ID)
    {
        assert_param(IS_FDCAN_MAX_VALUE(Identifier, 0x7FFU));
    }
    else /* IdType == FDCAN_EXTENDED_ID */
    {
        assert_param(IS_FDCAN_MAX_VALUE(Identifier, 0x1FFFFFFFU));
    }
    
    hfdcan->Instance->TTREFMSG.b.REF_ID = Identifier;
    
    hfdcan->Instance->TTREFMSG.b.REF_IDE = (IdType == FDCAN_EXTENDED_ID) ? 1 : 0;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_TT_ConfigTrigger(FDCAN_HandleTypeDef *hfdcan, FDCAN_TriggerTypeDef *sTriggerConfig)
{
    hfdcan->Instance->TTTRIGCFG.w = sTriggerConfig->TriggerType << 8 | sTriggerConfig->TTPtr | sTriggerConfig->TxEnWindow << 12;
    
    hfdcan->Instance->TTTRIG = sTriggerConfig->TimeMark & 0xFFFF;
    
    if(hfdcan->Instance->TTTRIG != sTriggerConfig->TimeMark)
        return HAL_ERROR;

    return HAL_OK;
}

void HAL_FDCAN_TT_ImmediateTrigger(FDCAN_HandleTypeDef *hfdcan, uint8_t TTPtr)
{    
    /* Select TBUF slot for the trigger */
    hfdcan->Instance->TTTRIGCFG.b.TTPTR = TTPtr;
    
    /* configure the trigger type and transmit enable window */
    hfdcan->Instance->TTTRIGCFG.b.TTYPE = FDCAN_TT_TX_IMMEDIATE_TRIGGER;
    
    hfdcan->Instance->TTTRIG = 1;
    
    return;
}


HAL_StatusTypeDef HAL_FDCAN_TT_AddMessageByTBPtr(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData, uint8_t TBPtr)
{
    uint8_t i;    
    uint8_t data_len;    
    uint32_t* ptmp;
    
    assert_param(IS_FDCAN_TT_INSTANCE(hfdcan->Instance));   
    assert_param(IS_FDCAN_DLC(pTxHeader->FrameInfo.b.DLC));        

    MODIFY_REG(hfdcan->Instance->TTCFG, FDCAN_TTCFG_TBPTR_Msk, TBPtr << FDCAN_TTCFG_TBPTR_Pos);    
    
    ptmp = (uint32_t*)pTxHeader;
    
    hfdcan->Instance->TBUF[0] = *ptmp++;
    hfdcan->Instance->TBUF[1] = *ptmp;
        
    data_len = __HAL_FDCAN_DLC2LEN(pTxHeader->FrameInfo.b.DLC);
    
    for(i = 0; i < (data_len + 3) / 4; i++)
    {
        hfdcan->Instance->TBUF[2 + i] = *(uint32_t*)pTxData;
        pTxData += 4;
    }
        
    SET_BIT(hfdcan->Instance->TTCFG, FDCAN_TTCFG_TBF);
    while(!READ_BIT(hfdcan->Instance->IR, FDCAN_IR_TSFF));
        
    return HAL_OK;
}


HAL_StatusTypeDef HAL_FDCAN_TT_EnableWatchTrigger(FDCAN_HandleTypeDef *hfdcan, uint32_t cycle_time)
{
    assert_param(IS_FDCAN_TT_INSTANCE(hfdcan->Instance));
    
    hfdcan->Instance->TTWTRIGR.w = (cycle_time & 0xFFFF);
    SET_BIT(hfdcan->Instance->TTCFG, FDCAN_TTCFG_WTIE);
    return HAL_OK;
}


HAL_StatusTypeDef HAL_FDCAN_TT_DisableWatchTrigger(FDCAN_HandleTypeDef *hfdcan)
{
    assert_param(IS_FDCAN_TT_INSTANCE(hfdcan->Instance));
    
    CLEAR_BIT(hfdcan->Instance->TTCFG, FDCAN_TTCFG_WTIE);
    return HAL_OK;
}



HAL_StatusTypeDef HAL_FDCAN_EnableTimestamp(FDCAN_HandleTypeDef *hfdcan, uint32_t ts_position)
{
    assert_param(IS_FDCAN_TT_INSTANCE(hfdcan->Instance));
    assert_param(IS_FDCAN_TIMESTAMP_POSITION(ts_position));
    
    hfdcan->Instance->TIMECFG = FDCAN_TIMCFG_TIMEEN | (ts_position << FDCAN_TIMCFG_TIMEPOS_Pos);
    return HAL_OK;
}


HAL_StatusTypeDef HAL_FDCAN_DisableTimestamp(FDCAN_HandleTypeDef *hfdcan)
{
    assert_param(IS_FDCAN_TT_INSTANCE(hfdcan->Instance));
    
    CLEAR_BIT(hfdcan->Instance->TIMECFG, FDCAN_TIMCFG_TIMEEN);
    return HAL_OK;
}

void HAL_FDCAN_GetTTS(FDCAN_HandleTypeDef *hfdcan, FDCAN_TTSTypeDef *tts)
{
    assert_param(IS_FDCAN_TT_INSTANCE(hfdcan->Instance));
    tts->tts_h = hfdcan->Instance->TTSH;
    tts->tts_l = hfdcan->Instance->TTSL;
}

#endif /* HAL_FDCAN_MODULE_ENABLED */
