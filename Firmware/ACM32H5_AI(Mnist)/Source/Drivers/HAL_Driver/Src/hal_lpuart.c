
/******************************************************************************
*@file  : hal_lpuart.c
*@brief : LPUART HAL module driver.
******************************************************************************/

#include "hal.h" 

#ifdef HAL_LPUART_MODULE_ENABLED

static void HAL_LPUART_InitParamter(LPUART_HandleTypeDef *hlpuart);

/******************************************************************************
*@brief : This function handles LPUART interrupt request.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None
******************************************************************************/
void HAL_LPUART_IRQHander(LPUART_HandleTypeDef *hlpuart)
{
    uint32_t Flag;
    uint32_t ITSource;
    uint32_t RxError;
    uint32_t Wakeup;
    
    /* Check for errors */
    Flag = __HAL_LPUART_GET_FLAG(hlpuart, LPUART_FLAG_RXOVIF | LPUART_FLAG_FEIF | \
                                          LPUART_FLAG_PEIF | LPUART_FLAG_RXIF | \
                                          LPUART_FLAG_TCIF | LPUART_FLAG_TXEIF | \
                                          LPUART_FLAG_STARTIF | LPUART_FLAG_MATCHIF | \
											LPUART_FLAG_IDLEIF | LPUART_FLAG_BCNTIF);
    
    ITSource = __HAL_LPUART_GET_IT_SOURCE(hlpuart, LPUART_IT_RXOV | LPUART_IT_FE | \
                                              LPUART_IT_PE | LPUART_IT_RX | \
                                              LPUART_IT_TC | LPUART_IT_TXE | \
                                              LPUART_IT_START | LPUART_IT_MATCH |\
												LPUART_IT_IDLE | LPUART_IT_BCNT);
    
    if ((Flag & (LPUART_FLAG_RXOVIF | LPUART_FLAG_FEIF | LPUART_FLAG_PEIF)) == 0U)
    {
        /* No error occurred */
        
        /* Receive completion interrupt */
        if ((Flag & LPUART_FLAG_RXIF) && (ITSource & LPUART_IT_RX))
        {
            /* Clear the receive completion interrupt flag */
            __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_RXIF);
            
            /* Receive completion (RXIF) callback function */
            HAL_LPUART_RxCompleteCallback(hlpuart);
        }
    }
    else
    {
        hlpuart->RxError = 0;
        
        /* some errors occurred */
        
        /* Over-Run interrupt occurred */
        if ((Flag & LPUART_FLAG_RXOVIF) && (ITSource & LPUART_IT_RXOV))
        {
            __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_RXOVIF);
            hlpuart->RxError |= LPUART_FLAG_RXOVIF;
        }
        
        /* frame error interrupt occurred */
        if ((Flag & LPUART_FLAG_FEIF) && (ITSource & LPUART_IT_FE))
        {
            __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_FEIF);
            hlpuart->RxError |= LPUART_FLAG_FEIF;
        }
        
        /* parity error interrupt occurred */
        if ((Flag & LPUART_FLAG_PEIF) && (ITSource & LPUART_IT_PE))
        {
            __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_PEIF);
            hlpuart->RxError |= LPUART_FLAG_PEIF;
        }
        
        if (Flag & (LPUART_FLAG_FEIF | LPUART_FLAG_PEIF))
        {
            /* receive completion interrupt */
            if (ITSource & LPUART_IT_RX)
            {
                __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_RXIF);
                
                /* receive complete (RXIF) callback function */
                HAL_LPUART_RxCompleteCallback(hlpuart);
            }
        }
        else
        {
            /* Receive completion (RXIF) interrupt */
            if ((Flag & LPUART_FLAG_RXIF) && (ITSource & LPUART_IT_RX))
            {
                /* Clear the receive completion interrupt flag */
                __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_RXIF);
                
                /* Receive completion (RXIF) callback function */
                HAL_LPUART_RxCompleteCallback(hlpuart);
            }
        }
        
        if (hlpuart->RxError)
        {
            /* Error callback function */
            if (hlpuart->RxErrorCallback)
            {
                hlpuart->RxErrorCallback(hlpuart);
            }
        }
    }
    
    /* transmit buffer empty interrupt */
    if ((Flag & LPUART_FLAG_TXEIF) && (ITSource & LPUART_IT_TXE))
    {
        __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_TXEIF);
        
        /* transmit empty (TXEIF) callback function */
        HAL_LPUART_TxEmptyCallback(hlpuart);
    }
    
    /* transmit complete interrupt */
    if ((Flag & LPUART_FLAG_TCIF) && (ITSource & LPUART_IT_TC))
    {
        __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_TCIF);
        
        /* transmit complete (TCIF) callback function */
        HAL_LPUART_TxCompleteCallback(hlpuart);
    }
    
    /* Bit counting interrupt */
    if ((Flag & LPUART_FLAG_BCNTIF) && (ITSource & LPUART_IT_BCNT))
    {
        __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_BCNTIF);
        
        /* Bit counting callback function */
        HAL_LPUART_BcntCallback(hlpuart);
    }
	
    /* Idle interrupt */
    if ((Flag & LPUART_FLAG_IDLEIF) && (ITSource & LPUART_IT_IDLE))
    {
        __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_IDLEIF);
        
        /* Idle callback function */
        HAL_LPUART_IdleCallback(hlpuart);
    }
	
    /* wakeup from Stop mode interrupt occurred */
    Wakeup = 0U;
    if ((Flag & LPUART_FLAG_STARTIF) && (ITSource & LPUART_IT_START))
    {
        /* Start bit wakeup */
        __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_STARTIF);
        Wakeup = 1U;
    }
    
    if ((Flag & LPUART_FLAG_MATCHIF) && (ITSource & LPUART_IT_MATCH))
    {
        /* address matching wakeup */
        __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_MATCHIF);
        Wakeup = 1U;
    }
    
    /* wakeup callback function */
    if (Wakeup)
    {
        HAL_LPUART_WakeupCallback(hlpuart);
    }
}

/******************************************************************************
*@brief : Initialize the LPUART according to the specified.
*         parameters in the LPUART_InitTypeDef and create the associated handle.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Init(LPUART_HandleTypeDef *hlpuart)
{  
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    assert_param(IS_LPUART_WORDLENGTH(hlpuart->Init.WordLength));
    assert_param(IS_LPUART_STOPBITS(hlpuart->Init.StopBits));
    assert_param(IS_LPUART_PARITY(hlpuart->Init.Parity));
    assert_param(IS_LPUART_MODE(hlpuart->Init.Mode));
    assert_param(IS_LPUART_WAKEUPMODE(hlpuart->Init.WakeupMode));
    assert_param(IS_LPUART_CLOCKSOURCE(hlpuart->Init.ClockSource));
    
    /* Init the low level hardware : GPIO, CLOCK */
    HAL_LPUART_MspInit(hlpuart);
    
    /* Init the internal parameter */
    HAL_LPUART_InitParamter(hlpuart);
    
    /* set the clock source */
    if (HAL_RCC_LPUART1ClockSourceConfig(hlpuart->Init.ClockSource) != HAL_OK)
        return HAL_ERROR;
    
    /* Set baud rate */
    HAL_LPUART_SetBaudRate(hlpuart, hlpuart->Init.BaudRate);
    
    /* Set the communication parameters */
    hlpuart->Instance->LCR  =   hlpuart->Init.WordLength    | \
                                hlpuart->Init.StopBits      | \
                                hlpuart->Init.Parity        | \
                                hlpuart->Init.WakeupMode;
    
    /* Set the address matching for wakeup */
    if ((hlpuart->Init.WakeupMode == LPUART_WAKEUPMODE_ADDRNOCHECK) || \
        (hlpuart->Init.WakeupMode == LPUART_WAKEUPMODE_ADDRCHECK))
    {
        /* Check the parameters */
        assert_param(IS_LPUART_WAKEUPADDR(hlpuart->Init.WakeupAddr));
        
        hlpuart->Instance->ADDR =   hlpuart->Init.WakeupAddr;
    }
    
    /* enable tx rx */
    hlpuart->Instance->CR   =   hlpuart->Init.Mode;

    return HAL_OK; 
}

/******************************************************************************
*@brief : DeInitialize the LPUART peripheral.
*         Before Deinitialization, the sending or receiving process needs to be aborted.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_DeInit(LPUART_HandleTypeDef *hlpuart)
{
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    
    /* Disable tx */
    __HAL_LPUART_DISABLE_TX(hlpuart);
    
    /* Disable rx */
    __HAL_LPUART_DISABLE_RX(hlpuart);
    
    /* DeInit the low level hardware */
    HAL_LPUART_MspDeInit(hlpuart);
    
    /* Init the internal parameter */
    HAL_LPUART_InitParamter(hlpuart);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Initialize the LPUART MSP.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None
******************************************************************************/
__weak void HAL_LPUART_MspInit(LPUART_HandleTypeDef *hlpuart)
{
    UNUSED(hlpuart);
}

/******************************************************************************
*@brief : DeInitialize the LPUART MSP.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None
******************************************************************************/
__weak void HAL_LPUART_MspDeInit(LPUART_HandleTypeDef *hlpuart)
{
    UNUSED(hlpuart);
}

/******************************************************************************
*@brief : set baud rate.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@param : baudRate: This member configures the UART communication baud rate
*                   The integer value of LPUART clock frequency divided by 
*                   baud rate is 2-254.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_SetBaudRate(LPUART_HandleTypeDef *hlpuart, uint32_t baudRate)
{
    uint32_t temp;
    float tempFloat;
    uint32_t bits;
    uint32_t ClockNum;
    uint32_t iBaudRate;
#if 1
    const uint16_t fBaudRate[4][13] = 
    {
//			0		1		2		3		4		5		6		7		8		9		10		11		12
        {0x0000, 0x0010, 0x0044, 0x0092, 0x00AA, 0x0155, 0x01B6, 0x01DD, 0x01EF, 0x01FF, 0x0000, 0x0000, 0x0000},//start+7bit+end
        {0x0000, 0x0020, 0x0084, 0x0124, 0x014A, 0x02AA, 0x02B5, 0x036D, 0x03DE, 0x03DF, 0x03FF, 0x0000, 0x0000},
        {0x0000, 0x0020, 0x0088, 0x0124, 0x0252, 0x02AA, 0x0355, 0x0575, 0x0776, 0x0777, 0x07DF, 0x07FF, 0x0000},
        {0x0000, 0x0040, 0x0108, 0x0248, 0x02A4, 0x0554, 0x0AAA, 0x0AEA, 0x0DB6, 0x0EEE, 0x0F7B, 0x0FDF, 0x0FFF},//start+8bit+pol+2end
    };
#else
    const uint16_t fBaudRate[4][12] = 
    {
//			0		1		2		3		4		5		6		7		8		9		10		11		12
        {0x0000, 0x0010, 0x0044, 0x0092, 0x00AA, 0x0155, 0x01B6, 0x01DD, 0x01EF, 0x0000, 0x0000, 0x0000},//start+7bit+end
        {0x0000, 0x0020, 0x0084, 0x0124, 0x014A, 0x02AA, 0x02B5, 0x036D, 0x03DE, 0x03DF, 0x0000, 0x0000},
        {0x0000, 0x0020, 0x0088, 0x0124, 0x0252, 0x02AA, 0x0355, 0x0575, 0x0776, 0x0777, 0x07DF, 0x0000},
        {0x0000, 0x0040, 0x0108, 0x0248, 0x02A4, 0x0554, 0x0AAA, 0x0AEA, 0x0DB6, 0x0EEE, 0x0F7B, 0x0FDF},//start+8bit+pol+2end
    };
#endif
    
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    
    /* Calculate the baud rate division factor */
    tempFloat = (float)HAL_RCC_GetLPUART1ClockFreq();//(float)HAL_RCC_GetLPUART1CLKFreq();
                       
    tempFloat = tempFloat / hlpuart->Init.BaudRate;
    iBaudRate = (uint32_t)tempFloat;
    tempFloat = tempFloat - iBaudRate;
    iBaudRate--;
    assert_param(IS_LPUART_BAUDRATE(iBaudRate));
    
    bits = 10;
    if (hlpuart->Init.WordLength != LPUART_WORDLENGTH_8B)
        bits--;
    if (hlpuart->Init.Parity != LPUART_PARITY_NONE)
        bits++;
    if (hlpuart->Init.StopBits != LPUART_STOPBITS_1B)
        bits++;
    
    tempFloat = tempFloat * bits;
    ClockNum = (uint32_t)tempFloat;
    tempFloat = tempFloat - ClockNum;
    if (tempFloat >= 0.5)
        ClockNum++;
    
    hlpuart->Instance->IBAUD = iBaudRate + ((iBaudRate >> 1) << LPUART_IBAUD_RXSAM_Pos);
    hlpuart->Instance->FBAUD = fBaudRate[bits - 9][ClockNum];
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Register a User LPUART Callback.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@param : id: ID of the callback to be registered
*             This parameter can be a combination of @ref LPUART_CallbackID.
*             @arg LPUART_CALLBACKID_TXCPLT     : transfer completion callback function.
*             @arg LPUART_CALLBACKID_TXHALFCPLT : transfer half completion callback function.
*             @arg LPUART_CALLBACKID_TXERROR    : transfer error callback function.
*             @arg LPUART_CALLBACKID_RXCPLT     : receive completion callback function.
*             @arg LPUART_CALLBACKID_RXHALFCPLT : receive half completion callback function.
*             @arg LPUART_CALLBACKID_RXERROR    : receive error callback function.
*             @arg LPUART_CALLBACKID_WAKEUP     : wakeup callback function.
*             @arg LPUART_CALLBACKID_BCNT		: bit count callback function.
*             @arg LPUART_CALLBACKID_IDLE		: idle callback function.
*@param : pCallback: pointer to the Callback function.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_RegisterCallback(LPUART_HandleTypeDef *hlpuart, uint32_t id, pLPUART_CallbackTypeDef pCallback)
{
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    assert_param(IS_LPUART_CALLBACKID(id));
    
	switch (id)
	{
		case  LPUART_CALLBACKID_TXCPLT:
			
			hlpuart->TxCpltCallback = pCallback;
			break;

		case  LPUART_CALLBACKID_TXHALFCPLT:
			
			hlpuart->TxHalfCpltCallback = pCallback;
			break;

		case  LPUART_CALLBACKID_TXERROR:
			
			hlpuart->TxErrorCallback = pCallback;
			break;

		case  LPUART_CALLBACKID_RXCPLT:
			
			hlpuart->RxCpltCallback = pCallback;
			break;

		case  LPUART_CALLBACKID_RXHALFCPLT:
			
			hlpuart->RxHalfCpltCallback = pCallback;
			break;

		case  LPUART_CALLBACKID_RXERROR:
			
			hlpuart->RxErrorCallback = pCallback;
			break;

		case  LPUART_CALLBACKID_WAKEUP:
			
			hlpuart->WakeupCallback = pCallback;
			break;
		case  LPUART_CALLBACKID_BCNT:
			
			hlpuart->BcntCallback = pCallback;
			break;
		case  LPUART_CALLBACKID_IDLE:
			
			hlpuart->IdleCallback = pCallback;
			break;

		default:
			return HAL_ERROR;
	}
	return HAL_OK;
}


/******************************************************************************
*@brief : Unregister a User LPUART Callback.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@param : id: ID of the callback to be registered
*             This parameter can be a combination of @ref LPUART_CallbackID.
*             @arg LPUART_CALLBACKID_TXCPLT     : transfer completion callback function.
*             @arg LPUART_CALLBACKID_TXHALFCPLT : transfer half completion callback function.
*             @arg LPUART_CALLBACKID_TXERROR    : transfer error callback function.
*             @arg LPUART_CALLBACKID_RXCPLT     : receive completion callback function.
*             @arg LPUART_CALLBACKID_RXHALFCPLT : receive half completion callback function.
*             @arg LPUART_CALLBACKID_RXERROR    : receive error callback function.
*             @arg LPUART_CALLBACKID_WAKEUP     : wakeup callback function.
*             @arg LPUART_CALLBACKID_BCNT		: bit count callback function.
*             @arg LPUART_CALLBACKID_IDLE		: idle callback function.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_UnRegisterCallback(LPUART_HandleTypeDef *hlpuart, uint32_t id)
{
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    assert_param(IS_LPUART_CALLBACKID(id));
    
	switch (id)
	{
		case  LPUART_CALLBACKID_TXCPLT:
			
			hlpuart->TxCpltCallback = NULL;
			break;

		case  LPUART_CALLBACKID_TXHALFCPLT:
			
			hlpuart->TxHalfCpltCallback = NULL;
			break;

		case  LPUART_CALLBACKID_TXERROR:
			
			hlpuart->TxErrorCallback = NULL;
			break;

		case  LPUART_CALLBACKID_RXCPLT:
			
			hlpuart->RxCpltCallback = NULL;
			break;

		case  LPUART_CALLBACKID_RXHALFCPLT:
			
			hlpuart->RxHalfCpltCallback = NULL;
			break;

		case  LPUART_CALLBACKID_RXERROR:
			
			hlpuart->RxErrorCallback = NULL;
			break;

		case  LPUART_CALLBACKID_WAKEUP:
			
			hlpuart->WakeupCallback = NULL;
			break;
		case  LPUART_CALLBACKID_BCNT:
			
			hlpuart->BcntCallback = NULL;
			break;
		case  LPUART_CALLBACKID_IDLE:
			
			hlpuart->IdleCallback = NULL;
			break;
		default:
			return HAL_ERROR;
	}
	return HAL_OK;
}

/******************************************************************************
*@brief : Send an amount of data in blocking mode.
*@note    In blocking mode, the user cannot enable interrupt.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be sent.
*@param : timeout: Timeout duration.
*                  The minimum value of this parameter is 1.
*                  If the value of this parameter is 0xFFFFFFFF, it will be sent until all data are sent.
*                  @node The timeout should be greater than the time of all data transfers.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Transmit(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size, uint32_t timeout)
{
    uint32_t startTick;

    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    assert_param(pdata != NULL);
    assert_param(size != 0U);
    assert_param(timeout != 0U);
    
    /* If LPUART is sending, an error is returned */
    if (hlpuart->TxState != LPUART_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking transmission can be aborted. Clear the abort flag bit */
    hlpuart->TxAbort  = DISABLE;
    
    /* tx state: busy */
    hlpuart->TxState  = LPUART_STATE_BUSY;
    
    hlpuart->pTxBuf  = pdata;
    hlpuart->TxCount = size;
    
    startTick = HAL_GetTick();
    while (1)
    {
        if (hlpuart->TxCount)
        {
            /* Whether tx buffer is empty */
            if (__HAL_LPUART_GET_FLAG(hlpuart, LPUART_FLAG_TXE))
            {
                /* send byte */
                hlpuart->Instance->TXDR = *pdata++;
                hlpuart->TxCount--;
            }
        }
        else
        {
            /* Whether sending has ended */
            if (__HAL_LPUART_GET_FLAG(hlpuart, LPUART_FLAG_TCIF))
            {
                __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_TCIF);
    
                hlpuart->TxState  = LPUART_STATE_READY;
                return HAL_OK;
            }
        }
        
        /* Whether sending is aborted */
        if (hlpuart->TxAbort != DISABLE)
        {
            if (hlpuart->Instance->CR & LPUART_CR_TX_EN)
            {
                __HAL_LPUART_DISABLE_TX(hlpuart);
                __HAL_LPUART_ENABLE_TX(hlpuart);
            }
            hlpuart->TxState  = LPUART_STATE_READY;
            return (HAL_ERROR);
        }
        
        /* Whether the sending time has expired */
        if (timeout != 0xFFFFFFFF)
        {
            if ((HAL_GetTick() - startTick) >= timeout)
            {
                if (hlpuart->Instance->CR & LPUART_CR_TX_EN)
                {
                    __HAL_LPUART_DISABLE_TX(hlpuart);
                    __HAL_LPUART_ENABLE_TX(hlpuart);
                }
                hlpuart->TxState  = LPUART_STATE_READY;
                return (HAL_TIMEOUT);
            }
        }
    }
}

/******************************************************************************
*@brief : Receive an amount of data in blocking mode.
*@note    In blocking mode, the user cannot enable interrupt.
*@note    Users can add or ignore error handling in RxErrorCallback(). 
*         Error codes are stored in hlpuart->RxError.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@param : timeout: Timeout duration.
*                  If the value of this parameter is 0, the received data will be detected only once and will not wait.
*                  If the value of this parameter is 0xFFFFFFFF, it will be received until all data are received.
*                  @node The timeout should be greater than the time of all data transfers.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Receive(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size, uint32_t timeout)
{
    uint32_t startTick;

    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    assert_param(pdata != NULL);
    assert_param(size != 0U);
    
    /* If LPUART is receiving, an error is returned */
    if (hlpuart->RxState != LPUART_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking reception can be aborted. Clear the abort flag bit */
    hlpuart->RxAbort = DISABLE;
    
    /* rx state: busy */
    hlpuart->RxState  = LPUART_STATE_BUSY;
    
    hlpuart->pRxBuf  = pdata;
    hlpuart->RxCount = size;
    
    startTick = HAL_GetTick();
    while (1)
    {
        /* Whether there are errors */
        hlpuart->RxError = __HAL_LPUART_GET_FLAG(hlpuart, LPUART_FLAG_RXOVIF | LPUART_FLAG_FEIF | LPUART_FLAG_PEIF);
        if (hlpuart->RxError)
        {
            __HAL_LPUART_CLEAR_FLAG(hlpuart, hlpuart->RxError & (LPUART_FLAG_RXOVIF | LPUART_FLAG_FEIF | LPUART_FLAG_PEIF));
            if (hlpuart->RxErrorCallback)
            {
                hlpuart->RxErrorCallback(hlpuart);
            }
        }
        
        /* Whether reception is completed */
        if (__HAL_LPUART_GET_FLAG(hlpuart, LPUART_FLAG_RXF))
        {
            /* receive data */
            *pdata++ = hlpuart->Instance->RXDR;
            hlpuart->RxCount--;
            
            /* receive complete */
            if (hlpuart->RxCount == 0)
            {
                hlpuart->RxState  = LPUART_STATE_READY;
                return HAL_OK;
            }
        }
        
        /* Whether reception is aborted */
        if (hlpuart->RxAbort != DISABLE)
        {
            hlpuart->RxState  = LPUART_STATE_READY;
            return (HAL_ERROR);
        }
        
        if (timeout != 0xFFFFFFFF)
        {
            /* Whether the receiving time has expired */
            if ((HAL_GetTick() - startTick) >= timeout)
            {
                hlpuart->TxState  = LPUART_STATE_READY;
                return (HAL_TIMEOUT);
            }
        }
    }
}
/******************************************************************************
*@brief : Receive an amount of data to Idle line or  BCNT time.
*         
*@param : hlpuart: lpuart handle with LPUART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to receive.
*@param : rece_mode: by idle line, or by bit value count reached
*@param : timeout: BCNT value(relative to LPUART baudrate), when LPUART BaudRate = 115200, 
                    then set timeout = 115200,it is approximately 1 second. MAX BCNT value can be 0xFFFF.
*                   Only used when 'rece_mode' = LPUART_RECEIVE_TOBCNT
*                             when 'rece_mode' = LPUART_RECEIVE_TOIDLE, it is meaningless.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Receive_To_IDLEorBCNT(LPUART_HandleTypeDef *hlpuart, uint8_t *buf, uint32_t size, 
                                                LPUART_Receive_Mode_Enum rece_mode, uint32_t timeout)
{

    assert_param (IS_LPUART_INSTANCE(hlpuart->Instance));
    
    if ((buf == NULL) || (size == 0U))
    {
      return HAL_ERROR;
    }

    hlpuart->RxCount = 0;
    hlpuart->pRxBuf = buf;
    
    if(rece_mode == LPUART_RECEIVE_TOBCNT)
    {
        MODIFY_REG(hlpuart->Instance->LCR, LPUART_LCR_BCNT_VALUE, timeout<<LPUART_LCR_BCNT_VALUE_Pos);
        SET_BIT(hlpuart->Instance->LCR, LPUART_LCR_AUTO_START_EN);
		
    }

    while (size--) 
    {
        while(!(hlpuart->Instance->SR & LPUART_SR_RXF))
        {
            if(rece_mode == RECEIVE_TOBCNT)
            {    
                if(READ_BIT(hlpuart->Instance->SR, LPUART_SR_BCNTIF))
                {
					CLEAR_BIT(hlpuart->Instance->LCR, LPUART_LCR_AUTO_START_EN);
					CLEAR_STATUS(hlpuart->Instance->SR, LPUART_SR_BCNTIF);
                    return HAL_TIMEOUT;
                }
            }
            else
            {
                if(READ_BIT(hlpuart->Instance->SR, LPUART_SR_IDLEIF))
                {
                    CLEAR_STATUS(hlpuart->Instance->SR, LPUART_SR_IDLEIF);
                    while(READ_BIT(hlpuart->Instance->SR, LPUART_SR_IDLEIF))
                    {
                        CLEAR_STATUS(hlpuart->Instance->SR, 0);
                        CLEAR_STATUS(hlpuart->Instance->SR, LPUART_SR_IDLEIF);
                    }
                    return HAL_TIMEOUT;
                }
            }
        }


		hlpuart->pRxBuf[hlpuart->RxCount++] = (uint8_t)hlpuart->Instance->RXDR;	

    }
    
    CLEAR_BIT(hlpuart->Instance->LCR, LPUART_LCR_AUTO_START_EN);
	
    return HAL_OK;
}
/******************************************************************************
*@brief : Send an amount of data in interrupt mode.
*@note    In interrupt mode, sending related interrupts (TXE/TC) is forced to enable.
*@note    Users can add or ignore error handling in ErrorCallback(). 
*@note    The user can add the processing of sending completion in TxCpltCallback().
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Transmit_IT(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size)
{
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    assert_param(pdata != NULL);
    assert_param(size != 0U);
    
    /* If LPUART is sending, an error is returned */
    if (hlpuart->TxState != LPUART_STATE_READY)
        return HAL_ERROR;
    
    /* tx state: busy */
    hlpuart->TxState  = LPUART_STATE_BUSY_IT;
    
    hlpuart->pTxBuf  = pdata;
    hlpuart->TxCount = size;
    
    /* enable interrupt (TC) */
    __HAL_LPUART_ENABLE_IT(hlpuart, LPUART_IT_TXE);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data in interrupt mode.
*@note    In interrupt mode, receiving completion interrupt (RX) and error 
*         interrupt (RXOV、FE、PE) are forced enabled.
*         If an error occurs in the reception, the reception stops automatically.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Receive_IT(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size)
{
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    assert_param(pdata != NULL);
    assert_param(size != 0U);
    
    /* If LPUART is receiving, an error is returned */
    if (hlpuart->RxState != LPUART_STATE_READY)
        return HAL_ERROR;
    
    /* rx state: busy */
    hlpuart->RxState  = LPUART_STATE_BUSY_IT;
    
    hlpuart->pRxBuf  = pdata;
    hlpuart->RxCount = size;
    hlpuart->RxError = 0;
    
    /* enable interrupt (RX、PE、FE、RXOV) */
    __HAL_LPUART_ENABLE_IT(hlpuart, LPUART_IT_RXOV | LPUART_IT_FE | LPUART_IT_PE | LPUART_IT_RX);
    
    return HAL_OK;
}

#ifdef HAL_DMA_MODULE_ENABLED
/******************************************************************************
*@brief : Send an amount of data in DMA mode.
*@note    In DMA mode, the transmission related interrupt (TC/TXE) is forced to disabled.
*         the DMA transmission related interrupt (ITC/HFTC/IE) is forced to enabled.
*         If an DMA transfer error occurs in the transmission, 
*         the transmission stops automatically.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Transmit_DMA(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size)
{
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    assert_param(pdata != NULL);
    assert_param(size != 0U);
    
    /* If LPUART is sending, an error is returned */
    if (hlpuart->TxState != LPUART_STATE_READY)
        return HAL_ERROR;
    
    /* tx state: busy */
    hlpuart->TxState  = LPUART_STATE_BUSY_DMA;
    
    /* set dma callback function */
    hlpuart->hdmatx->XferCpltCallback  = HAL_LPUART_DMATxCpltCallback;
    hlpuart->hdmatx->XferErrorCallback  = HAL_LPUART_DMATxErrorCallback;
    if (hlpuart->TxHalfCpltCallback)
        hlpuart->hdmatx->XferHalfCpltCallback  = HAL_LPUART_DMATxHalfCpltCallback;
    else
        hlpuart->hdmatx->XferHalfCpltCallback  = NULL;
    
    hlpuart->pTxBuf  = pdata;
    hlpuart->TxCount = size;
    hlpuart->TxError = 0U;
    
    /* Start DMA interrupt transfer */
    if (HAL_DMA_Start_IT(hlpuart->hdmatx, (uint32_t)pdata, (uint32_t)&hlpuart->Instance->TXDR, size) != HAL_OK)
    {
        /* Set error code to DMA */
        hlpuart->TxError = LPUART_DMA_TX_ERROR;
        hlpuart->TxState  = LPUART_STATE_READY;
        return  HAL_ERROR;
    }
    
    /* enable LPUART DMA */
    __HAL_LPUART_ENABLE_DMA(hlpuart);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data in DMA mode.
*@note    In DMA mode, receiving completion interrupt (RX) is forced disable. 
*         the error interrupt (RXOV、FE、PE) are forced enabled.
*         the DMA transmission related interrupt (ITC/HFTC/IE) is forced to enabled.
*         If an error occurs in the reception, the reception stops automatically.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_Receive_DMA(LPUART_HandleTypeDef *hlpuart, uint8_t *pdata, uint32_t size)
{
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    assert_param(pdata != NULL);
    assert_param(size != 0U);
    
    /* If LPUART is receiving, an error is returned */
    if (hlpuart->RxState != LPUART_STATE_READY)
        return HAL_ERROR;
    
    /* rx state: busy */
    hlpuart->RxState  = LPUART_STATE_BUSY_DMA;
    
    /* set dma callback function */
    hlpuart->hdmarx->XferCpltCallback  = HAL_LPUART_DMARxCpltCallback;
    if (hlpuart->RxHalfCpltCallback)
        hlpuart->hdmarx->XferHalfCpltCallback  = HAL_LPUART_DMARxHalfCpltCallback;
    else
        hlpuart->hdmarx->XferHalfCpltCallback  = NULL;
    hlpuart->hdmarx->XferErrorCallback  = HAL_LPUART_DMARxErrorCallback;
    
    hlpuart->pRxBuf  = pdata;
    hlpuart->RxCount = size;
    hlpuart->RxError = 0U;
    
    /* Start DMA interrupt transfer */
    if (HAL_DMA_Start_IT(hlpuart->hdmarx, (uint32_t)&hlpuart->Instance->RXDR, (uint32_t)pdata, size) != HAL_OK)
    {
        /* Set error code to DMA */
        hlpuart->RxError = LPUART_DMA_RX_ERROR;
        hlpuart->RxState  = LPUART_STATE_READY;
        return HAL_ERROR;
    }
    
    /* enable interrupt (PE、FE、RXOV) */
    if (hlpuart->RxErrorCallback)
    {
        __HAL_LPUART_ENABLE_IT(hlpuart, LPUART_IT_RXOV | LPUART_IT_FE | LPUART_IT_PE);
    }
    
    /* enable LPUART DMA */
    __HAL_LPUART_ENABLE_DMA(hlpuart);
    
    return HAL_OK;
}
#endif

/******************************************************************************
*@brief : Abort ongoing transmit transfer(block mode/interrupt mode/dma mode).
*         In blocking mode, check TxState to exit the abort function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_AbortTransmit(LPUART_HandleTypeDef *hlpuart)
{
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    
    /* If LPUART is not sent, return directly */
    if (hlpuart->TxState == LPUART_STATE_READY)
        return HAL_OK;
    
    if (hlpuart->TxState == LPUART_STATE_BUSY)
    {
        /* Abort ongoing transmit transfer(block mode) */
        
        /* enable tx abort flag */
        hlpuart->TxAbort = ENABLE;
    }
    else if (hlpuart->TxState == LPUART_STATE_BUSY_IT)
    {
        /* Abort ongoing transmit transfer(interrupt mode) */
        
        /* disable interrupt (TXE/TC) */
        __HAL_LPUART_DISABLE_IT(hlpuart, LPUART_IT_TXE | LPUART_IT_TC);
        
        if (hlpuart->Instance->CR & LPUART_CR_TX_EN)
        {
            __HAL_LPUART_DISABLE_TX(hlpuart);
            __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_TCIF);
            __HAL_LPUART_ENABLE_TX(hlpuart);
        }
        
        /* end of sending */
        hlpuart->TxState = LPUART_STATE_READY;
    }
#ifdef HAL_DMA_MODULE_ENABLED    
    else if (hlpuart->TxState == LPUART_STATE_BUSY_DMA)
    {
        /* Abort ongoing transmit transfer(dma mode) */
        
        /* abort dma transfer */
        HAL_DMA_Abort(hlpuart->hdmatx);
        
        /* Take the number of unsent data */
        hlpuart->TxCount = __HAL_DMA_GET_TRANSFER_SIZE(hlpuart->hdmatx);
        
        if (hlpuart->Instance->CR & LPUART_CR_TX_EN)
        {
            __HAL_LPUART_DISABLE_TX(hlpuart);
            __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_TCIF);
            __HAL_LPUART_ENABLE_TX(hlpuart);
        }
        
        /* end of sending */
        hlpuart->TxState = LPUART_STATE_READY;
    }
#endif    
    else
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Abort ongoing reception transfer(block mode/interrupt mode/dma mode).
*         In blocking mode, check TxState to exit the abort function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_LPUART_AbortReceive(LPUART_HandleTypeDef *hlpuart)
{
    /* Check the parameters */
    assert_param(IS_LPUART_HANDLE(hlpuart));
    assert_param(IS_LPUART_INSTANCE(hlpuart->Instance));
    
    /* If LPUART is not receving, return directly */
    if (hlpuart->RxState == LPUART_STATE_READY)
        return HAL_OK;
    
    if (hlpuart->RxState == LPUART_STATE_BUSY)
    {
        /* Abort ongoing transmit transfer(block mode) */
        
        /* enable rx abort flag */
        hlpuart->RxAbort = ENABLE;
    }
    else if (hlpuart->RxState == LPUART_STATE_BUSY_IT)
    {
        /* Abort ongoing transmit transfer(interrupt mode) */
        
        /* disable interrupt (RXOV/FE/PE/RX) */
        __HAL_LPUART_DISABLE_IT(hlpuart, LPUART_IT_RXOV | LPUART_IT_FE | \
                                         LPUART_IT_PE | LPUART_IT_RX);
        __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_RXOVIF | LPUART_FLAG_FEIF | \
                                         LPUART_FLAG_PEIF | LPUART_FLAG_RXIF);
        
        /* End of reception */
        hlpuart->RxState = LPUART_STATE_READY;
    }
#ifdef HAL_DMA_MODULE_ENABLED    
    else if (hlpuart->RxState == LPUART_STATE_BUSY_DMA)
    {
        /* Abort ongoing transmit transfer(dma mode) */
        
        /* disable interrupt (RXOV/FE/PE) */
        __HAL_LPUART_DISABLE_IT(hlpuart, LPUART_IT_RXOV | LPUART_IT_FE | LPUART_IT_PE);
        
        /* abort dma transfer */
        HAL_DMA_Abort(hlpuart->hdmarx);
        
        /* Take the number of unsent data */
        hlpuart->RxCount = __HAL_DMA_GET_TRANSFER_SIZE(hlpuart->hdmarx);
        
        __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_RXOVIF | LPUART_FLAG_FEIF | \
                                         LPUART_FLAG_PEIF | LPUART_FLAG_RXIF);
    
        /* End of reception */
        hlpuart->RxState = LPUART_STATE_READY;
    }
#endif    
    else
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Get sending status.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: sending status.
*         The return value can be @ ref LPUART_State value
*         @arg LPUART_STATE_READY: LPUART not sent.
*         @arg LPUART_STATE_BUSY: LPUART sending(block mode).
*         @arg LPUART_STATE_BUSY_IT: LPUART sending(interrupt mode).
*         @arg LPUART_STATE_BUSY_DMA: LPUART sending(dma mode).
******************************************************************************/
uint32_t HAL_LPUART_GetTxState(LPUART_HandleTypeDef *hlpuart)
{
    assert_param(IS_LPUART_HANDLE(hlpuart));
    return (hlpuart->TxState);
}

/******************************************************************************
*@brief : Get the receiving status.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: receiving status.
*         The return value can be @ ref LPUART_State value
*         @arg LPUART_STATE_READY: LPUART did not receive.
*         @arg LPUART_STATE_BUSY: LPUART is receiving(block mode).
*         @arg LPUART_STATE_BUSY_IT: LPUART is receiving(interrupt mode).
*         @arg LPUART_STATE_BUSY_DMA: LPUART is receiving(dma mode).
******************************************************************************/
uint32_t HAL_LPUART_GetRxState(LPUART_HandleTypeDef *hlpuart)
{
    assert_param(IS_LPUART_HANDLE(hlpuart));
    return (hlpuart->RxState);
}

/******************************************************************************
*@brief : bit counting callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_BcntCallback(LPUART_HandleTypeDef *hlpuart)
{
    if (hlpuart->BcntCallback)
    {
        hlpuart->BcntCallback(hlpuart);
    }
}
/******************************************************************************
*@brief : Idle callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_IdleCallback(LPUART_HandleTypeDef *hlpuart)
{
    if (hlpuart->IdleCallback)
    {
        hlpuart->IdleCallback(hlpuart);
    }
}
/******************************************************************************
*@brief : Tx buffer empty callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_TxEmptyCallback(LPUART_HandleTypeDef *hlpuart)
{
    if (hlpuart->TxCount)
    {
        /* Continue sending */
        hlpuart->Instance->TXDR = *hlpuart->pTxBuf++;
        hlpuart->TxCount--;
    }
    else
    {
        /* disable interrupt (TXE) */
        __HAL_LPUART_DISABLE_IT(hlpuart, LPUART_IT_TXE);
        
        /* enable interrupt (TC) */
        __HAL_LPUART_ENABLE_IT(hlpuart, LPUART_IT_TC);
    }
}

/******************************************************************************
*@brief : Tx transfer complete callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_TxCompleteCallback(LPUART_HandleTypeDef *hlpuart)
{
    /* disable interrupt (TC) */
    __HAL_LPUART_DISABLE_IT(hlpuart, LPUART_IT_TC);
    
    hlpuart->TxState  = LPUART_STATE_READY;
    
    if (hlpuart->TxCpltCallback)
    {
        hlpuart->TxCpltCallback(hlpuart);
    }
}

/******************************************************************************
*@brief : Rx transfer complete callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_RxCompleteCallback(LPUART_HandleTypeDef *hlpuart)
{
    /* The received data is put into the buffer */
    *hlpuart->pRxBuf++ = hlpuart->Instance->RXDR;
    hlpuart->RxCount--;
    
    if (hlpuart->RxCount == 0U)
    {
        /* Receiving completed */
        
        /* disable interrupt (RX/RXOV/FE/PE) */
        __HAL_LPUART_DISABLE_IT(hlpuart, LPUART_IT_RX | LPUART_IT_RXOV | \
                                         LPUART_IT_FE | LPUART_IT_PE);
        
        /* receive complete */
        hlpuart->RxState  = LPUART_STATE_READY;
        
        if (hlpuart->RxCpltCallback)
        {
            hlpuart->RxCpltCallback(hlpuart);
        }
    }
}

/******************************************************************************
*@brief : Wakeup callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_WakeupCallback(LPUART_HandleTypeDef *hlpuart)
{
    if (hlpuart->WakeupCallback)
    {
        hlpuart->WakeupCallback(hlpuart);
    }
}

#ifdef HAL_DMA_MODULE_ENABLED
/******************************************************************************
*@brief : Tx DMA transfer complete callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_DMATxCpltCallback(DMA_HandleTypeDef *hdma)
{
    LPUART_HandleTypeDef *hlpuart;
    
    hlpuart = hdma->Parent;
    
    /* clear flag (TCIF) */
    __HAL_LPUART_CLEAR_FLAG(hlpuart, LPUART_FLAG_TCIF);
    
    /* Take the number of unsent data */
    hlpuart->TxCount = __HAL_DMA_GET_TRANSFER_SIZE(hlpuart->hdmatx);
    
    /* tx DMA transfer complete */
    hlpuart->TxState = LPUART_STATE_READY;
    
    if (hlpuart->TxCpltCallback)
    {
        hlpuart->TxCpltCallback(hlpuart);
    }
}

/******************************************************************************
*@brief : Tx DMA half transfer complete callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_DMATxHalfCpltCallback(DMA_HandleTypeDef *hdma)
{
    LPUART_HandleTypeDef *hlpuart;
    
    hlpuart = hdma->Parent;
    
    /* Take the number of unsent data */
    hlpuart->TxCount = __HAL_DMA_GET_TRANSFER_SIZE(hlpuart->hdmatx);
    
    if (hlpuart->TxHalfCpltCallback)
    {
        hlpuart->TxHalfCpltCallback(hlpuart);
    }
}

/******************************************************************************
*@brief : Tx DMA transfer error callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_DMATxErrorCallback(DMA_HandleTypeDef *hdma)
{
    LPUART_HandleTypeDef *hlpuart;
    
    hlpuart = hdma->Parent;
    
    /* abort tx dma transfer */
    HAL_DMA_Abort(hdma);
    
    /* set the dma transfer error */
    hlpuart->TxError |= LPUART_DMA_TX_ERROR;
    
    /* Take the number of unsent data */
    hlpuart->TxCount = __HAL_DMA_GET_TRANSFER_SIZE(hlpuart->hdmatx);
    
    /* end of sending */
    hlpuart->TxState = LPUART_STATE_READY;
    
    if (hlpuart->TxErrorCallback)
    {
        hlpuart->TxErrorCallback(hlpuart);
    }
}

/******************************************************************************
*@brief : Rx DMA transfer complete callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_DMARxCpltCallback(DMA_HandleTypeDef *hdma)
{
    LPUART_HandleTypeDef *hlpuart;
    
    hlpuart = hdma->Parent;
    
    /* if no error occurs in reception, disable interrupt (RXOV/FE/PE) */
    __HAL_LPUART_DISABLE_IT(hlpuart, LPUART_IT_RXOV | LPUART_IT_FE | LPUART_IT_PE);
    
    /* Take the number of data not received */
    hlpuart->RxCount = __HAL_DMA_GET_TRANSFER_SIZE(hlpuart->hdmarx);
    
    /* End of reception */
    hlpuart->RxState = LPUART_STATE_READY;
    
    if (hlpuart->RxCpltCallback)
    {
        hlpuart->RxCpltCallback(hlpuart);
    }
}

/******************************************************************************
*@brief : Rx DMA hlaf transfer complete callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_DMARxHalfCpltCallback(DMA_HandleTypeDef *hdma)
{
    LPUART_HandleTypeDef *hlpuart;
    
    hlpuart = hdma->Parent;
    
    /* Take the number of data not received */
    hlpuart->RxCount = __HAL_DMA_GET_TRANSFER_SIZE(hlpuart->hdmarx);
    
    if (hlpuart->RxHalfCpltCallback)
    {
        hlpuart->RxHalfCpltCallback(hlpuart);
    }
}

/******************************************************************************
*@brief : Rx DMA transfer error callback function.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
__weak void HAL_LPUART_DMARxErrorCallback(DMA_HandleTypeDef *hdma)
{
    LPUART_HandleTypeDef *hlpuart;
    
    hlpuart = hdma->Parent;
    
    /* abort rx dma transfer */
    HAL_DMA_Abort(hdma);
    
    /* set the dma transfer error */
    hlpuart->RxError = LPUART_DMA_RX_ERROR;
    
    /* End of reception */
    hlpuart->RxState = LPUART_STATE_READY;
    
    if (hlpuart->RxErrorCallback)
    {
        hlpuart->RxErrorCallback(hlpuart);
    }
}
#endif

/******************************************************************************
*@brief : Init the internal parameter.
*@param : hlpuart: pointer to a LPUART_HandleTypeDef structure that contains
*                  the configuration information for LPUART module.
*@return: None.
******************************************************************************/
static void HAL_LPUART_InitParamter(LPUART_HandleTypeDef *hlpuart)
{
    hlpuart->TxState                = 0U;
    hlpuart->TxError                = 0U;
    hlpuart->pTxBuf                 = 0U;
    hlpuart->TxCount                = 0U;
    hlpuart->TxAbort                = 0U;
    
    hlpuart->RxState                = 0U;
    hlpuart->RxError                = 0U;
    hlpuart->pRxBuf                 = 0U;
    hlpuart->RxCount                = 0U;
    hlpuart->RxAbort                = 0U;
    
    hlpuart->TxCpltCallback         = NULL;
    hlpuart->TxHalfCpltCallback     = NULL;
    hlpuart->TxErrorCallback        = NULL;
    hlpuart->RxCpltCallback         = NULL;
    hlpuart->RxHalfCpltCallback     = NULL;
    hlpuart->RxErrorCallback        = NULL;
    hlpuart->WakeupCallback         = NULL;
}

#endif /* HAL_LPUART_MODULE_ENABLED */

/************************ (C) COPYRIGHT AISINOCHIP *****END OF FILE****/

