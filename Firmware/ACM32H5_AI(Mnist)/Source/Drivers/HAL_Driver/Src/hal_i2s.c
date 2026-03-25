
/******************************************************************************
*@file  : hal_i2s.c
*@brief : I2S HAL module driver.
******************************************************************************/

#include "hal.h" 

#ifdef HAL_I2S_MODULE_ENABLED

static void HAL_I2S_InitParamter(I2S_HandleTypeDef *hi2s);

/******************************************************************************
*@brief : This function handles I2S interrupt request.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_I2S_IRQHander(I2S_HandleTypeDef *hi2s)
{
    uint32_t flag;
    uint32_t source;
    
    flag = __HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_MASK);
    source = __HAL_I2S_GET_IT_SOURCE(hi2s, I2S_IT_MASK);
    
    if ((source & I2S_IT_TXE) && (flag & I2S_FLAG_TXE))
    {
        /* Tx buffer empty callback function */
        HAL_I2S_TxEmptyCallback(hi2s);
    }  
    
    if ((source & I2S_IT_RXNE) && (flag & I2S_FLAG_RXNE))
    {
        /* Rx buffer non empty callback function */
        HAL_I2S_RxNonEmptyCallback(hi2s);
    }
    
    if ((source & I2S_IT_MSUSP) && (flag & I2S_FLAG_MSUSP))
    {
        __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MSUSP);
        /* Tx complete callback function */
        HAL_I2S_MsuspCallback(hi2s);
    }
    
    if ((source & I2S_IT_SVTC) && (flag & I2S_FLAG_SVTC))
    {
        __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_SVTC);
        /* Tx complete callback function */
        HAL_I2S_SvtcCallback(hi2s);
    }

    flag &= I2S_FLAG_FE | I2S_FLAG_UDR | I2S_FLAG_OVR;
    if ((source & I2S_IT_ERR) && (flag))
    {
        hi2s->Error |= flag;
        __HAL_I2S_CLEAR_FLAG(hi2s, flag);
        HAL_I2S_ErrorCallback(hi2s);
    }
}

/******************************************************************************
*@brief : Tx buffer empty callback function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                  the configuration information for I2S module.
*@return: None.
******************************************************************************/
__attribute__((weak)) void HAL_I2S_TxEmptyCallback(I2S_HandleTypeDef *hi2s)
{
    uint32_t over;
    
    /* Continue sending */
    if (hi2s->TxCount)
    {
        if (hi2s->pTxBuf)
            __HAL_I2S_WRITE_DATA(hi2s, *hi2s->pTxBuf++);
        else
            __HAL_I2S_WRITE_DATA(hi2s, 0);
        if (--hi2s->TxCount == 0)
        {
            over = 1;
            if (hi2s->TxEmptyCallback)
            {
                over = hi2s->TxEmptyCallback(hi2s);
            }
            if (over)
            {
                __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_TXE);
            }
        }
    }
}

/******************************************************************************
*@brief : Tx buffer empty callback function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                  the configuration information for I2S module.
*@return: None.
******************************************************************************/
__attribute__((weak)) void HAL_I2S_MsuspCallback(I2S_HandleTypeDef *hi2s)
{
    uint32_t over;
    
    over = 1;
    if (hi2s->MsuspCallback)
    {
        over = hi2s->MsuspCallback(hi2s);
    }
    if (over != 0)
    {
        hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
        __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
        hi2s->State  = I2S_STATE_READY;
    }
}

/******************************************************************************
*@brief : Tx buffer empty callback function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                  the configuration information for I2S module.
*@return: None.
******************************************************************************/
__attribute__((weak)) void HAL_I2S_SvtcCallback(I2S_HandleTypeDef *hi2s)
{
    uint32_t over;
    
    over = 1;
    if (hi2s->SvtcCallback)
    {
        over = hi2s->SvtcCallback(hi2s);
    }
    if (over != 0)
    {
        hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
        __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
        hi2s->State  = I2S_STATE_READY;
    }
}
        
/******************************************************************************
*@brief : Rx buffer non empty callback function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@return: None.
******************************************************************************/
__attribute__((weak)) void HAL_I2S_RxNonEmptyCallback(I2S_HandleTypeDef *hi2s)
{
    uint32_t over;
    volatile uint32_t temp;
      
    if (hi2s->RxCount--)
    {
        if (hi2s->pRxBuf)
            *hi2s->pRxBuf++ = __HAL_I2S_READ_DATA(hi2s);
        else
            temp = __HAL_I2S_READ_DATA(hi2s);
        
    }
    
    if (hi2s->RxCount == 0)
    {
        over = 1;
        if (hi2s->RxCpltCallback)
        {
            over = hi2s->RxCpltCallback(hi2s);
        }
        
        if (over != 0)
        {
            hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
            __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
            hi2s->State = I2S_STATE_READY;
        }
    }
}

/******************************************************************************
*@brief : Tx Error callback function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                  the configuration information for I2S module.
*@return: None.
******************************************************************************/
__attribute__((weak)) void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s)
{
    if (hi2s->ErrorCallback)
    {
        hi2s->ErrorCallback(hi2s);
    }
}

/******************************************************************************
*@brief : Tx DMA transfer complete callback function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                  the configuration information for I2S module.
*@return: None.
******************************************************************************/
__attribute__((weak)) void HAL_I2S_DMATxCpltCallback(DMA_HandleTypeDef *hdmac)
{
    I2S_HandleTypeDef *hi2s;
    
    hi2s = hdmac->Parent;
    
    /* Take the number of unsent data */
    hi2s->TxCount = __HAL_DMA_GET_TRANSFER_SIZE(hi2s->hdmactx);
    
    if (hi2s->DMATxCpltCallback)
    {
        hi2s->DMATxCpltCallback(hi2s);
    }
}

/******************************************************************************
*@brief : Tx DMA half transfer complete callback function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                  the configuration information for I2S module.
*@return: None.
******************************************************************************/
__attribute__((weak)) void HAL_I2S_DMATxHalfCpltCallback(DMA_HandleTypeDef *hdmac)
{
    I2S_HandleTypeDef *hi2s;
    
    hi2s = hdmac->Parent;
    
    /* Take the number of unsent data */
    hi2s->TxCount = __HAL_DMA_GET_TRANSFER_SIZE(hi2s->hdmactx);
    
    if (hi2s->DMATxHalfCpltCallback)
    {
        hi2s->DMATxHalfCpltCallback(hi2s);
    }
}

/******************************************************************************
*@brief : Rx DMA transfer complete callback function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                  the configuration information for I2S module.
*@return: None.
******************************************************************************/
__attribute__((weak)) void HAL_I2S_DMARxCpltCallback(DMA_HandleTypeDef *hdmac)
{
    uint32_t over;
    I2S_HandleTypeDef *hi2s;
    
    hi2s = hdmac->Parent;
    
    over = 1;
    if (hi2s->DMARxCpltCallback)
    {
        over = hi2s->DMARxCpltCallback(hi2s);
    }
    
    if (over != 0)
    {
        hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
        __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
        hi2s->State = I2S_STATE_READY;
    }
}

/******************************************************************************
*@brief : Rx DMA hlaf transfer complete callback function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                  the configuration information for I2S module.
*@return: None.
******************************************************************************/
__attribute__((weak)) void HAL_I2S_DMARxHalfCpltCallback(DMA_HandleTypeDef *hdmac)
{
    I2S_HandleTypeDef *hi2s;
    
    hi2s = hdmac->Parent;
    
    /* Take the number of data not received */
    hi2s->RxCount = __HAL_DMA_GET_TRANSFER_SIZE(hi2s->hdmacrx);
    
    if (hi2s->DMARxHalfCpltCallback)
    {
        hi2s->DMARxHalfCpltCallback(hi2s);
    }
}

/******************************************************************************
*@brief : Rx DMA transfer error callback function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                  the configuration information for I2S module.
*@return: None.
******************************************************************************/
__attribute__((weak)) void HAL_I2S_DMAErrorCallback(DMA_HandleTypeDef *hdmac)
{
    uint32_t over;
    I2S_HandleTypeDef *hi2s;
    
    hi2s = hdmac->Parent;
    
    over = 1;
    if (hi2s->ErrorCallback)
    {
        over = hi2s->ErrorCallback(hi2s);
    }
    
    if (over)
    {
        /* abort rx dma transfer */
        HAL_DMA_Abort(hdmac);
        
        /* disable I2S Tx Rx DMA */
        __HAL_I2S_TX_RX_DMA_DISABLE(hi2s);
        
        __HAL_I2S_TX_RX_DISABLE(hi2s);
        
        /* Disable the error interrupt */
        __HAL_I2S_IT_DISABLE(hi2s,  I2S_IT_ERR);
        
        /* set the dma transfer error */
        hi2s->Error |= I2S_DMA_ERROR;
        
        /* End of reception */
        hi2s->State = I2S_STATE_READY;
    }
}

/******************************************************************************
*@brief : Initialize the I2S according to the specified.
*         parameters in the I2S_InitTypeDef and create the associated handle.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Init(I2S_HandleTypeDef *hi2s)
{
    double Freq;
    uint32_t div;
    
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param(IS_I2S_MODE(hi2s->Init.Mode));
    assert_param(IS_I2S_STANDARD(hi2s->Init.Standard));
    assert_param(IS_I2S_DATAFORMAT(hi2s->Init.DataFormat));
    assert_param(IS_I2S_MCLKOUTPUT(hi2s->Init.MCLKOutput));
    assert_param(IS_I2S_CLOCKPOLARITY(hi2s->Init.ClockPolarity));
    assert_param(IS_I2S_IOSWITCH(hi2s->Init.IOSwitch));
    
    assert_param(hi2s->Init.AudioFreq != 0u);
    
    Freq = (double)HAL_RCC_GetHCLKFreq();
    if (hi2s->Init.MCLKOutput == I2S_MCLKOUT_DISABLE)
    {
        if (hi2s->Init.DataFormat == I2S_DATA_FORMAT_16B_EXTENDED_TO_16B)
            Freq = Freq / 32;
        else
            Freq = Freq / 64;
    }
    else
    {
        Freq = Freq / 256;
    }
    assert_param(Freq >= (double)hi2s->Init.AudioFreq);
    Freq = Freq / (double)hi2s->Init.AudioFreq;
    Freq += 0.5;
    div = (uint32_t)Freq;
    if (div & 1u)
    {
        div = (div - 1) >> 1;
        assert_param(div <= 0x1FFU);
        div += I2S_PR_OF;
    }
    else
    {
        div = div >> 1;
        assert_param(div <= 0x1FFU);
    }
    
    /* Init the low level hardware : GPIO, CLOCK, CORTEX...etc */
    HAL_I2S_MspInit(hi2s);
    
    /* Disable I2S */
    __HAL_I2S_DISABLE(hi2s);
    
    /* Init the internal parameter */
    HAL_I2S_InitParamter(hi2s);
    
    hi2s->Instance->CR = hi2s->Init.Mode | hi2s->Init.Standard | hi2s->Init.DataFormat | \
                         hi2s->Init.ClockPolarity | hi2s->Init.IOSwitch;
    
    hi2s->Instance->PR = hi2s->Init.MCLKOutput | div;
    
    __HAL_I2S_ENABLE(hi2s);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : DeInitialize the I2S peripheral.
*         Before Deinitialization, the sending or receiving process needs to be aborted.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_DeInit(I2S_HandleTypeDef *hi2s)
{
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    
    __HAL_I2S_DISABLE(hi2s);
    
    /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
    HAL_I2S_MspDeInit(hi2s);
    
    /* Init the internal parameter */
    HAL_I2S_InitParamter(hi2s);
    
    return HAL_OK;
}


/******************************************************************************
*@brief : Initialize the I2S MSP.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@return: None
******************************************************************************/
__weak void HAL_I2S_MspInit(I2S_HandleTypeDef *hi2s)
{
    UNUSED(hi2s);
}

/******************************************************************************
*@brief : DeInitialize the I2S MSP.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@return: None
******************************************************************************/
__weak void HAL_I2S_MspDeInit(I2S_HandleTypeDef *hi2s)
{
    UNUSED(hi2s);
}

/******************************************************************************
*@brief : Register a User I2S Callback.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@note    The registered callback function must be after initialization.
*@param : id: ID of the callback to be registered
*             This parameter can be a combination of @ref I2S_CallbackID.
*             @arg I2S_CALLBACKID_TXCPLT     : transfer complete callback function.
*             @arg I2S_CALLBACKID_TXHALFCPLT : transfer half complete callback function.
*             @arg I2S_CALLBACKID_TXERROR    : transfer error callback function.
*             @arg I2S_CALLBACKID_RXCPLT     : recevice completion callback function.
*             @arg I2S_CALLBACKID_RXHALFCPLT : recevice half completion callback function.
*             @arg I2S_CALLBACKID_RXERROR    : receive error callback function.
*@param : pCallback: pointer to the Callback function.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_RegisterCallback(I2S_HandleTypeDef *hi2s, uint32_t id, pI2S_CallbackTypeDef pCallback)
{
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param(IS_I2S_CALLBACKID(id));
    assert_param(pCallback != NULL);
    
	switch (id)
	{
		case  I2S_CALLBACKID_TX_EMPTY:
			
			hi2s->TxEmptyCallback = pCallback;
			break;

		case  I2S_CALLBACKID_MSUSP:
			
			hi2s->MsuspCallback = pCallback;
			break;

		case  I2S_CALLBACKID_SVTC:
			
			hi2s->SvtcCallback = pCallback;
			break;

		case  I2S_CALLBACKID_TX_CPLT:
			
			hi2s->TxCpltCallback = pCallback;
			break;

		case  I2S_CALLBACKID_RX_CPLT:
			
			hi2s->RxCpltCallback = pCallback;
			break;

		case  I2S_CALLBACKID_DMA_TX_CPLT:
			
			hi2s->DMATxCpltCallback = pCallback;
			break;

		case  I2S_CALLBACKID_DMA_TX_HALF_CPLT:
			
			hi2s->DMATxHalfCpltCallback = pCallback;
			break;

		case  I2S_CALLBACKID_DMA_RX_CPLT:
			
			hi2s->DMARxCpltCallback = pCallback;
			break;

		case  I2S_CALLBACKID_DMA_RX_HALF_CPLT:
			
			hi2s->DMARxHalfCpltCallback = pCallback;
			break;

		case  I2S_CALLBACKID_ERROR:
			
			hi2s->ErrorCallback = pCallback;
			break;

		default:
			return HAL_ERROR;
	}
	return HAL_OK;
}


/******************************************************************************
*@brief : Unregister a User I2S Callback.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@param : id: ID of the callback to be registered
*             This parameter can be a combination of @ref I2S_CallbackID.
*             @arg I2S_CALLBACKID_TXCPLT     : transfer complete callback function.
*             @arg I2S_CALLBACKID_TXHALFCPLT : transfer half complete callback function.
*             @arg I2S_CALLBACKID_TXERROR    : transfer error callback function.
*             @arg I2S_CALLBACKID_RXCPLT     : recevice completion callback function.
*             @arg I2S_CALLBACKID_RXHALFCPLT : recevice half completion callback function.
*             @arg I2S_CALLBACKID_RXERROR    : receive error callback function.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_UnRegisterCallback(I2S_HandleTypeDef *hi2s, uint32_t id)
{
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param(IS_I2S_CALLBACKID(id));
    
	switch (id)
	{
		case  I2S_CALLBACKID_TX_EMPTY:
			
			hi2s->TxEmptyCallback = NULL;
			break;

		case  I2S_CALLBACKID_MSUSP:
			
			hi2s->MsuspCallback = NULL;
			break;

		case  I2S_CALLBACKID_SVTC:
			
			hi2s->SvtcCallback = NULL;
			break;

		case  I2S_CALLBACKID_TX_CPLT:
			
			hi2s->TxCpltCallback = NULL;
			break;

		case  I2S_CALLBACKID_RX_CPLT:
			
			hi2s->RxCpltCallback = NULL;
			break;

		case  I2S_CALLBACKID_DMA_TX_CPLT:
			
			hi2s->DMATxCpltCallback = NULL;
			break;

		case  I2S_CALLBACKID_DMA_TX_HALF_CPLT:
			
			hi2s->DMATxHalfCpltCallback = NULL;
			break;

		case  I2S_CALLBACKID_DMA_RX_CPLT:
			
			hi2s->DMARxCpltCallback = NULL;
			break;

		case  I2S_CALLBACKID_DMA_RX_HALF_CPLT:
			
			hi2s->DMARxHalfCpltCallback = NULL;
			break;

		case  I2S_CALLBACKID_ERROR:
			
			hi2s->ErrorCallback = NULL;
			break;

		default:
			return HAL_ERROR;
	}
	return HAL_OK;
}

HAL_StatusTypeDef HAL_I2S_TxData(I2S_HandleTypeDef *hi2s, uint32_t Data)
{
    hi2s->Instance->TXDR = Data;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2S_RxData(I2S_HandleTypeDef *hi2s, uint32_t *pdata)
{
    *pdata = hi2s->Instance->RXDR;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Send an amount of data in blocking mode.
*@note    In blocking mode, the user cannot enable interrupt.
*@note    Users can add or ignore error handling in TxErrorCallback(). 
*         Error codes are stored in hi2s->TxError.
*@note    The last word was being sent when the function exited. 
*         The application also needs to call the HAL_I2S_GetBusyStatus() function 
*         to detect the end of sending.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be sent.
*@param : timeout: Timeout duration.
*                  The minimum value of this parameter is 1.
*                  If the value of this parameter is 0xFFFFFFFF, it will be sent until all data are sent.
*                  @node The timeout should be greater than the time of all data transfers.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Transmit(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint32_t size, uint32_t timeout)
{
    volatile uint32_t temp;
    uint32_t startTick;

    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param(pdata != NULL);
    assert_param(size != 0U);
    assert_param(timeout != 0U);
    
    /* If I2S is sending, an error is returned */
    if (hi2s->State != I2S_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking transmission can be aborted. Clear the abort flag bit */
    hi2s->Abort  = DISABLE;
    
    /* state: busy */
    hi2s->State  = I2S_STATE_BUSY;
    
    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
    
    __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
    __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MASK);
    temp = __HAL_I2S_READ_DATA(hi2s);
    
    hi2s->pTxBuf  = pdata;
    hi2s->TxCount = size;
    hi2s->Error = 0U;
    
    __HAL_I2S_TX_ENABLE(hi2s);
    if (hi2s->Init.Mode != I2S_MODE_SLAVE)
    {
        __HAL_I2S_START_ENABLE(hi2s);
    }
    
    startTick = HAL_GetTick();
    while (1)
    {
        /* Whether sending is aborted */
        if (hi2s->Abort != DISABLE)
        {
            hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN);
            hi2s->State  = I2S_STATE_READY;
            return (HAL_ERROR);
        }
        
        /* Check for errors */
        hi2s->Error = __HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_FE | I2S_FLAG_UDR);
        if (hi2s->Error)
        {
            __HAL_I2S_CLEAR_FLAG(hi2s, hi2s->Error);
            
            if (hi2s->ErrorCallback)
            {
                if (hi2s->ErrorCallback(hi2s))
                {
                    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN);
                    hi2s->State  = I2S_STATE_READY;
                    return (HAL_ERROR);
                }
            }
        }
        
        if (hi2s->TxCount)
        {
            if (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_TXE))
            {
                __HAL_I2S_WRITE_DATA(hi2s, *pdata++);
                hi2s->TxCount--;
            }
        }
        else if (hi2s->Init.Mode != I2S_MODE_SLAVE)
        {
            if (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_MSUSP))
            {
                __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MSUSP);
                hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN);
                hi2s->State  = I2S_STATE_READY;
                return HAL_OK;
            }
        }
        else
        {
            if (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_SVTC))
            {
                __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_SVTC);
                hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN);
                hi2s->State  = I2S_STATE_READY;
                return HAL_OK;
            }
        }
        
        if (timeout != 0xFFFFFFFFU)
        {
            /* Whether the sending time has expired */
            if ((HAL_GetTick() - startTick) >= timeout)
            {
                hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN);
                hi2s->State  = I2S_STATE_READY;
                return (HAL_TIMEOUT);
            }
        }
    }
}

/******************************************************************************
*@brief : Receive an amount of data in blocking mode.
*@note    In blocking mode, the user cannot enable interrupt.
*@note    Users can add or ignore error handling in RxErrorCallback(). 
*         Error codes are stored in hi2s->RxError.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@param : timeout: Timeout duration.
*                  If the value of this parameter is 0, the received data will be detected only once and will not wait.
*                  If the value of this parameter is 0xFFFFFFFF, it will be received until all data are received.
*                  @node The timeout should be greater than the time of all data transfers.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Receive(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint32_t size, uint32_t timeout)
{
    volatile uint32_t temp;
    uint32_t startTick;

    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param(pdata != NULL);
    assert_param(size != 0U);
    
    /* If I2S is receiving, an error is returned */
    if (hi2s->State != I2S_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking reception can be aborted. Clear the abort flag bit */
    hi2s->Abort = DISABLE;
    
    /* state: busy */
    hi2s->State  = I2S_STATE_BUSY;
    
    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
    
    __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
    temp = __HAL_I2S_READ_DATA(hi2s);
    __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MASK);
    
    hi2s->pRxBuf  = pdata;
    hi2s->RxCount = size;
    hi2s->Error = 0U;
    
    if (hi2s->Init.Mode != I2S_MODE_SLAVE)
    {
        __HAL_I2S_START_ENABLE(hi2s);
    }
    else
    {
        hi2s->Instance->RSIZE = size;
    }
    __HAL_I2S_RX_ENABLE(hi2s);
    
    startTick = HAL_GetTick();
    while (1)
    {
        /* Whether reception is aborted */
        if (hi2s->Abort != DISABLE)
        {
            hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_REN);
            hi2s->State  = I2S_STATE_READY;
            return (HAL_ERROR);
        }
        
        /* Whether there are errors */
        hi2s->Error = __HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_FE | I2S_FLAG_OVR);
        if (hi2s->Error)
        {
            if (hi2s->Error & I2S_FLAG_OVR)
            {
                temp = __HAL_I2S_READ_DATA(hi2s);
            }
            __HAL_I2S_CLEAR_FLAG(hi2s, hi2s->Error);
            
            if (hi2s->ErrorCallback)
            {
                if (hi2s->ErrorCallback(hi2s))
                {
                    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_REN);
                    hi2s->State  = I2S_STATE_READY;
                    return (HAL_ERROR);
                }
            }
        }
        
        if (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_RXNE))
        {
            /* receive data */
            *pdata++ = (uint32_t)(__HAL_I2S_READ_DATA(hi2s));
            hi2s->RxCount--;
            
            if (hi2s->RxCount == 1)
            {
            }
            if (hi2s->RxCount == 0)
            {
                hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_REN);
                hi2s->State  = I2S_STATE_READY;
                return (HAL_OK);
            }
        }
        
        /* Whether the receiving time has expired */
        if (timeout != 0xFFFFFFFFU)
        {
            if ((HAL_GetTick() - startTick) >= timeout)
            {
                hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_REN);
                hi2s->State  = I2S_STATE_READY;
                return (HAL_TIMEOUT);
            }
        }
    }
}

/******************************************************************************
*@brief : Send an amount of data in blocking mode.
*@note    In blocking mode, the user cannot enable interrupt.
*@note    Users can add or ignore error handling in TxErrorCallback(). 
*         Error codes are stored in hi2s->TxError.
*@note    The last word was being sent when the function exited. 
*         The application also needs to call the HAL_I2S_GetBusyStatus() function 
*         to detect the end of sending.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be sent.
*@param : timeout: Timeout duration.
*                  The minimum value of this parameter is 1.
*                  If the value of this parameter is 0xFFFFFFFF, it will be sent until all data are sent.
*                  @node The timeout should be greater than the time of all data transfers.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Transmit_Receive(I2S_HandleTypeDef *hi2s, uint32_t *prxdata, uint32_t *ptxdata, uint32_t size, uint32_t timeout)
{
    volatile uint32_t temp;
    uint32_t startTick;

    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param((prxdata != 0U) || (ptxdata != 0U));
    assert_param(size != 0U);
    assert_param(timeout != 0U);
    
    /* If I2S is sending, an error is returned */
    if (hi2s->State != I2S_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking transmission can be aborted. Clear the abort flag bit */
    hi2s->Abort  = DISABLE;
    
    /* state: busy */
    hi2s->State  = I2S_STATE_BUSY;
    
    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
    
    __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
    temp = __HAL_I2S_READ_DATA(hi2s);
    __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MASK);
    
    hi2s->pTxBuf  = ptxdata;
    hi2s->pRxBuf  = prxdata;
    hi2s->TxCount = size;
    hi2s->RxCount = size;
    hi2s->Error = 0U;
    
    __HAL_I2S_TX_RX_ENABLE(hi2s);
    
    if (hi2s->Init.Mode != I2S_MODE_SLAVE)
    {
        __HAL_I2S_START_ENABLE(hi2s);
    }
    
    startTick = HAL_GetTick();
    while (1)
    {
        /* Whether sending is aborted */
        if (hi2s->Abort != DISABLE)
        {
            hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN | I2S_CR_REN);
            hi2s->State  = I2S_STATE_READY;
            return (HAL_ERROR);
        }
        
        /* Check for errors */
        hi2s->Error = __HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_FE | I2S_FLAG_OVR | I2S_FLAG_UDR);
        if (hi2s->Error)
        {
            if (hi2s->Error & I2S_FLAG_OVR)
            {
                temp = __HAL_I2S_READ_DATA(hi2s);
            }
            __HAL_I2S_CLEAR_FLAG(hi2s, hi2s->Error);
            
            if (hi2s->ErrorCallback)
            {
                if (hi2s->ErrorCallback(hi2s))
                {
                    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN | I2S_CR_REN);
                    hi2s->State  = I2S_STATE_READY;
                    return (HAL_ERROR);
                }
            }
        }
        
        if (hi2s->TxCount)
        {
            if (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_TXE))
            {
                if (ptxdata)
                {
                    __HAL_I2S_WRITE_DATA(hi2s, *ptxdata++);
                }
                else
                {
                    __HAL_I2S_WRITE_DATA(hi2s, 0);
                }
                hi2s->TxCount--;
            }
        }
            
        if (__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_RXNE))
        {
            /* receive data */
            if (prxdata)
            {
                *prxdata++ = (uint32_t)(__HAL_I2S_READ_DATA(hi2s));
            }
            else
            {
                temp = (uint32_t)(__HAL_I2S_READ_DATA(hi2s));
            }
            hi2s->RxCount--;
            
            if (hi2s->RxCount == 0)
            {
                hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN | I2S_CR_REN);
                hi2s->State  = I2S_STATE_READY;
                return (HAL_OK);
            }
        }
        
        if (timeout != 0xFFFFFFFF)
        {
            /* Whether the sending time has expired */
            if ((HAL_GetTick() - startTick) >= timeout)
            {
                hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN | I2S_CR_REN);
                hi2s->State  = I2S_STATE_READY;
                return (HAL_TIMEOUT);
            }
        }
    }
}

/******************************************************************************
*@brief : Send an amount of data in interrupt mode.
*@note    In interrupt mode, the transmission related interrupts (TXE/ERR) are forced enabled.
*@note    Users can add or ignore error handling in ErrorCallback(). 
*         Error codes are stored in hi2s->TxError.
*@note    When the callback function TxCpltCallback() is called, the last word is being sent. 
*         The application also needs to call the HAL_I2S_GetBusyStatus() function 
*         to detect the end of sending.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Transmit_IT(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint32_t size)
{
    volatile uint32_t temp;
    uint32_t tempCR;
    uint32_t tempPR;
    
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param(pdata);
    assert_param(size != 0U);
    
    /* If I2S is sending, an error is returned */
    if (hi2s->State != I2S_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking transmission can be aborted. Clear the abort flag bit */
    hi2s->Abort  = DISABLE;
    
    /* state: busy */
    hi2s->State  = I2S_STATE_BUSY_IT;
    
    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
    
    __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
    temp = __HAL_I2S_READ_DATA(hi2s);
    __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MASK);
    
    hi2s->pTxBuf  = pdata;
    hi2s->TxCount = size;
    hi2s->Error = 0U;
    
    if (hi2s->Init.Mode != I2S_MODE_SLAVE)
    {
        __HAL_I2S_IT_ENABLE(hi2s, I2S_IT_TXE | I2S_IT_MSUSP | I2S_IT_ERR);
        __HAL_I2S_TX_ENABLE(hi2s);
        __HAL_I2S_START_ENABLE(hi2s);
    }
    else
    {
        __HAL_I2S_IT_ENABLE(hi2s, I2S_IT_TXE | I2S_IT_SVTC | I2S_IT_ERR);
        __HAL_I2S_TX_ENABLE(hi2s);
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data in interrupt mode.
*@note    In interrupt mode, receiving completion interrupt (RXNE/ERR) are forced enabled.
*         If an error occurs in the reception, the reception stops automatically.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Receive_IT(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint32_t size)
{
    volatile uint32_t temp;
    uint32_t tempCR;
    uint32_t tempPR;
    
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param(pdata);
    assert_param(size != 0U);
    
    /* If I2S is receiving, an error is returned */
    if (hi2s->State != I2S_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking reception can be aborted. Clear the abort flag bit */
    hi2s->Abort = DISABLE;
    
    /* state: busy */
    hi2s->State  = I2S_STATE_BUSY_IT;
    
    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
    
    __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
    temp = __HAL_I2S_READ_DATA(hi2s);
    __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MASK);
    
    hi2s->pRxBuf  = pdata;
    hi2s->RxCount = size;
    hi2s->Error = 0U;
    
    __HAL_I2S_IT_ENABLE(hi2s, I2S_IT_RXNE | I2S_IT_ERR);
    
    __HAL_I2S_RX_ENABLE(hi2s);
    if (hi2s->Init.Mode != I2S_MODE_SLAVE)
    {
        hi2s->Instance->RSIZE = size;
        __HAL_I2S_START_ENABLE(hi2s);
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Send an amount of data in interrupt mode.
*@note    In interrupt mode, the transmission related interrupts (TXE/ERR) are forced enabled.
*@note    Users can add or ignore error handling in ErrorCallback(). 
*         Error codes are stored in hi2s->TxError.
*@note    When the callback function TxCpltCallback() is called, the last word is being sent. 
*         The application also needs to call the HAL_I2S_GetBusyStatus() function 
*         to detect the end of sending.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Transmit_Receive_IT(I2S_HandleTypeDef *hi2s, uint32_t *prxdata, uint32_t *ptxdata, uint32_t size)
{
    volatile uint32_t temp;
    
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param((prxdata != 0U) || (ptxdata != 0U));
    assert_param(size != 0U);
    
    /* If I2S is sending, an error is returned */
    if (hi2s->State != I2S_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking transmission can be aborted. Clear the abort flag bit */
    hi2s->Abort  = DISABLE;
    
    /* state: busy */
    hi2s->State  = I2S_STATE_BUSY_IT;
    
    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
    
    __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
    temp = __HAL_I2S_READ_DATA(hi2s);
    __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MASK);
    
    hi2s->pTxBuf  = ptxdata;
    hi2s->TxCount = size;
    hi2s->pRxBuf  = prxdata;
    hi2s->RxCount = size;
    hi2s->Error = 0U;
    
    /* enable interrupt (TXE/RXNE/ERR) */
    __HAL_I2S_IT_ENABLE(hi2s, I2S_IT_TXE | I2S_IT_RXNE | I2S_IT_ERR);
    
    __HAL_I2S_TX_RX_ENABLE(hi2s);
    if (hi2s->Init.Mode != I2S_MODE_SLAVE)
    {
        __HAL_I2S_START_ENABLE(hi2s);
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Send an amount of data in DMA mode.
*@note    In DMA mode, the tx buffer empty interrupt (TXE) is forced to disabled.
*         the error interrupt (ERR) is forced to enabled.
*         the DMA transmission related interrupt (ITC/HFTC/IE) is forced to enabled.
*         If an DMA transfer error occurs in the transmission, 
*         the transmission stops automatically.
*@note    When the callback function TxCpltCallback() is called, the last word is being sent. 
*         The application also needs to call the HAL_I2S_GetBusyStatus() function 
*         to detect the end of sending.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Transmit_DMA(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint16_t size)
{
    volatile uint32_t temp;
    
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param(pdata != NULL);
    assert_param(size != 0U);
    
    /* If I2S is sending, an error is returned */
    if (hi2s->State != I2S_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking transmission can be aborted. Clear the abort flag bit */
    hi2s->Abort  = DISABLE;
    
    /* state: busy */
    hi2s->State  = I2S_STATE_BUSY_DMA;
    
    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
    
    __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
    temp = __HAL_I2S_READ_DATA(hi2s);
    __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MASK);
    
    /* set dmac callback function */
    hi2s->hdmactx->XferCpltCallback  = HAL_I2S_DMATxCpltCallback;
    if (hi2s->DMATxHalfCpltCallback)
        hi2s->hdmactx->XferHalfCpltCallback  = HAL_I2S_DMATxHalfCpltCallback;
    else
        hi2s->hdmactx->XferHalfCpltCallback  = NULL;
    hi2s->hdmactx->XferErrorCallback  = HAL_I2S_DMAErrorCallback;
    
    hi2s->pTxBuf  = pdata;
    hi2s->TxCount = size;
    hi2s->Error = 0U;
    
    __HAL_I2S_IT_ENABLE(hi2s,  I2S_IT_ERR);
    __HAL_I2S_TX_ENABLE(hi2s);
    if (hi2s->Init.Mode != I2S_MODE_SLAVE)
    {
        __HAL_I2S_IT_ENABLE(hi2s,  I2S_IT_MSUSP);
        __HAL_I2S_START_ENABLE(hi2s);
    }
    else
    {
        __HAL_I2S_IT_ENABLE(hi2s,  I2S_IT_SVTC);
    }
    
    /* Start DMA interrupt transfer */
    if (HAL_DMA_Start_IT(hi2s->hdmactx, (uint32_t)pdata, (uint32_t)&hi2s->Instance->TXDR, size) != HAL_OK)
    {
        /* DMA sending failed */
        HAL_DMA_Abort(hi2s->hdmactx);
        hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN);
        __HAL_I2S_IT_DISABLE(hi2s,  I2S_IT_ERR);
        hi2s->Error = I2S_DMA_TX_ERROR;
        hi2s->State  = I2S_STATE_READY;
        return  HAL_ERROR;
    }
    
    __HAL_I2S_TX_DMA_ENABLE(hi2s);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data in DMA mode.
*@note    In DMA mode, rx buffer non empty interrupt (RXNE) is forced disable. 
*         the error interrupt (ERR) is forced enabled.
*         the DMA transmission related interrupt (ITC/HFTC/IE) is forced to enabled.
*         If an DMA transfer error occurs in the reception, 
*         the reception stops automatically.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Receive_DMA(I2S_HandleTypeDef *hi2s, uint32_t *pdata, uint16_t size)
{
    volatile uint32_t temp;
    uint32_t tempCR;
    uint32_t tempPR;
    
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param(pdata != NULL);
    assert_param(size != 0U);
    
    /* If I2S is sending, an error is returned */
    if (hi2s->State != I2S_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking transmission can be aborted. Clear the abort flag bit */
    hi2s->Abort  = DISABLE;
    
    /* state: busy */
    hi2s->State  = I2S_STATE_BUSY_DMA;
    
    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
    
    __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
    temp = __HAL_I2S_READ_DATA(hi2s);
    __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MASK);
    
    /* set dma callback function */
    hi2s->hdmacrx->XferCpltCallback  = HAL_I2S_DMARxCpltCallback;
    hi2s->hdmacrx->XferErrorCallback  = HAL_I2S_DMAErrorCallback;
    if (hi2s->DMARxHalfCpltCallback)
        hi2s->hdmacrx->XferHalfCpltCallback  = HAL_I2S_DMARxHalfCpltCallback;
    else
        hi2s->hdmacrx->XferHalfCpltCallback  = NULL;
    
    hi2s->pRxBuf  = pdata;
    hi2s->RxCount = size;
    hi2s->Error = 0U;
    
    __HAL_I2S_IT_ENABLE(hi2s,  I2S_IT_ERR);
    __HAL_I2S_RX_ENABLE(hi2s);
    if (hi2s->Init.Mode != I2S_MODE_SLAVE)
    {
        hi2s->Instance->RSIZE = size;
        __HAL_I2S_START_ENABLE(hi2s);
    }
    /* Start DMA interrupt transfer */
    if (HAL_DMA_Start_IT(hi2s->hdmacrx, (uint32_t)&hi2s->Instance->RXDR, (uint32_t)pdata, size) != HAL_OK)
    {
        /* Set error code to DMA */
        HAL_DMA_Abort(hi2s->hdmacrx);
        hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_REN);
        __HAL_I2S_IT_DISABLE(hi2s,  I2S_IT_ERR);
        hi2s->Error = I2S_DMA_RX_ERROR;
        hi2s->State  = I2S_STATE_READY;
        return HAL_ERROR;
    }
    
    __HAL_I2S_RX_DMA_ENABLE(hi2s);
    
    return HAL_OK;
}
/******************************************************************************
*@brief : Send an amount of data in DMA mode.
*@note    In DMA mode, the tx buffer empty interrupt (TXE) is forced to disabled.
*         the error interrupt (ERR) is forced to enabled.
*         the DMA transmission related interrupt (ITC/HFTC/IE) is forced to enabled.
*         If an DMA transfer error occurs in the transmission, 
*         the transmission stops automatically.
*@note    When the callback function TxCpltCallback() is called, the last word is being sent. 
*         The application also needs to call the HAL_I2S_GetBusyStatus() function 
*         to detect the end of sending.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@param : pdata: Pointer to data buffer.
*@param : size: Amount of data elements to be received.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Transmit_Receive_DMA(I2S_HandleTypeDef *hi2s, uint32_t *prxdata, uint32_t *ptxdata, uint16_t size)
{
    volatile uint32_t temp;
    
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    assert_param(size != 0U);
    
    /* If I2S is sending, an error is returned */
    if (hi2s->State != I2S_STATE_READY)
        return HAL_ERROR;
    
    /* Blocking transmission can be aborted. Clear the abort flag bit */
    hi2s->Abort  = DISABLE;
    
    /* state: busy */
    hi2s->State  = I2S_STATE_BUSY_DMA;
    
    hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_STOP | I2S_CR_TEN | I2S_CR_REN | I2S_CR_TXDMAEN | I2S_CR_RXDMAEN);
    
    __HAL_I2S_IT_DISABLE(hi2s, I2S_IT_MASK);
    temp = __HAL_I2S_READ_DATA(hi2s);
    __HAL_I2S_CLEAR_FLAG(hi2s, I2S_FLAG_MASK);
    
    /* set dmac callback function */
    hi2s->hdmactx->XferCpltCallback  = HAL_I2S_DMATxCpltCallback;
    if (hi2s->DMATxHalfCpltCallback)
        hi2s->hdmactx->XferHalfCpltCallback  = HAL_I2S_DMATxHalfCpltCallback;
    else
        hi2s->hdmactx->XferHalfCpltCallback  = NULL;
    hi2s->hdmactx->XferErrorCallback  = HAL_I2S_DMAErrorCallback;
    
    /* set dma callback function */
    hi2s->hdmacrx->XferCpltCallback  = HAL_I2S_DMARxCpltCallback;
    hi2s->hdmacrx->XferErrorCallback  = HAL_I2S_DMAErrorCallback;
    if (hi2s->DMARxHalfCpltCallback)
        hi2s->hdmacrx->XferHalfCpltCallback  = HAL_I2S_DMARxHalfCpltCallback;
    else
        hi2s->hdmacrx->XferHalfCpltCallback  = NULL;
    
    hi2s->pTxBuf  = ptxdata;
    hi2s->TxCount = size;
    hi2s->pRxBuf  = prxdata;
    hi2s->RxCount = size;
    hi2s->Error = 0U;
    
    
    __HAL_I2S_IT_ENABLE(hi2s,  I2S_IT_ERR);
    __HAL_I2S_TX_RX_ENABLE(hi2s);
    if (hi2s->Init.Mode != I2S_MODE_SLAVE)
    {
        __HAL_I2S_START_ENABLE(hi2s);
    }
    
    /* Start DMA interrupt transfer */
    if (HAL_DMA_Start_IT(hi2s->hdmactx, (uint32_t)ptxdata, (uint32_t)&hi2s->Instance->TXDR, size) != HAL_OK)
    {
        /* DMA sending failed */
        HAL_DMA_Abort(hi2s->hdmactx);
        hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN | I2S_CR_REN);
        __HAL_I2S_IT_DISABLE(hi2s,  I2S_IT_ERR);
        hi2s->Error = I2S_DMA_TX_ERROR;
        hi2s->State  = I2S_STATE_READY;
        return  HAL_ERROR;
    }
    
    /* Start DMA interrupt transfer */
    if (HAL_DMA_Start_IT(hi2s->hdmacrx, (uint32_t)&hi2s->Instance->RXDR, (uint32_t)prxdata, size) != HAL_OK)
    {
        /* Set error code to DMA */
        HAL_DMA_Abort(hi2s->hdmactx);
        HAL_DMA_Abort(hi2s->hdmacrx);
        hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN | I2S_CR_REN);
        __HAL_I2S_IT_DISABLE(hi2s,  I2S_IT_ERR);
        hi2s->Error = I2S_DMA_RX_ERROR;
        hi2s->State  = I2S_STATE_READY;
        return HAL_ERROR;
    }
    
    __HAL_I2S_TX_RX_DMA_ENABLE(hi2s);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Abort ongoing transmit transfer(block mode/interrupt mode/dma mode).
*         In blocking mode, check TxState to exit the abort function.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_I2S_Abort(I2S_HandleTypeDef *hi2s)
{
    volatile uint32_t temp;
    
    /* Check the parameters */
    assert_param(IS_I2S_HANDLE(hi2s));
    assert_param(IS_I2S_INSTANCE(hi2s->Instance));
    
    /* If I2S is not sent, return directly */
    if (hi2s->State == I2S_STATE_READY)
        return HAL_OK;
    
    if (hi2s->State == I2S_STATE_BUSY)
    {
        /* Abort ongoing transmit transfer(in block mode) */
        
        /* enable tx abort flag */
        hi2s->Abort = ENABLE;
        return HAL_OK;
    }
    
    if (hi2s->State == I2S_STATE_BUSY_IT)
    {
        /* Abort ongoing transmit transfer(interrupt mode) */
        
        /* disable interrupt (TXE/ERR) */
        __HAL_I2S_IT_ENABLE(hi2s, I2S_IT_TXE | I2S_IT_RXNE | I2S_IT_MSUSP | I2S_IT_ERR);
        hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN | I2S_CR_REN);
        
        /* end of sending */
        hi2s->State = I2S_STATE_READY;
        return HAL_OK;
    }
    
    if (hi2s->State == I2S_STATE_BUSY_DMA)
    {
        /* Abort ongoing transmit transfer(dma mode) */
        
        /* disable interrupt (ERR) */
        __HAL_I2S_IT_DISABLE(hi2s,  I2S_IT_ERR);
        
        /* abort dma transfer */
        HAL_DMA_Abort(hi2s->hdmactx);
        
        hi2s->Instance->CR &= ~(I2S_CR_START | I2S_CR_TEN | I2S_CR_REN);
        
        /* disable I2S Tx DMA */
        __HAL_I2S_TX_RX_DMA_DISABLE(hi2s);
    
        /* end of sending */
        hi2s->State = I2S_STATE_READY;
        return HAL_OK;
    }
    
    return HAL_ERROR;
}

/******************************************************************************
*@brief : Get sending status.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module.
*@return: sending status.
*         The return value can be @ ref I2S_State value
*         @arg I2S_STATE_READY: I2S not sent.
*         @arg I2S_STATE_BUSY: I2S sending(block mode).
*         @arg I2S_STATE_BUSY_IT: I2S sending(interrupt mode).
*         @arg I2S_STATE_BUSY_DMA: I2S sending(dma mode).
******************************************************************************/
uint32_t HAL_I2S_GetState(I2S_HandleTypeDef *hi2s)
{
    assert_param(IS_I2S_HANDLE(hi2s));
    
    return (hi2s->State);
}



/******************************************************************************
*@brief : Init the internal parameter.
*@param : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                  the configuration information for I2S module.
*@return: None.
******************************************************************************/
static void HAL_I2S_InitParamter(I2S_HandleTypeDef *hi2s)
{
    hi2s->State     = 0U;
    hi2s->Abort     = 0U;
    hi2s->pTxBuf    = 0U;
    hi2s->TxCount   = 0U;
    hi2s->pRxBuf    = 0U;
    hi2s->RxCount   = 0U;
    
    hi2s->MsuspCallback             = NULL;
    hi2s->TxCpltCallback            = NULL;
    hi2s->RxCpltCallback            = NULL;
    hi2s->DMATxCpltCallback         = NULL;
    hi2s->DMATxHalfCpltCallback     = NULL;
    hi2s->DMARxCpltCallback         = NULL;
    hi2s->DMARxHalfCpltCallback     = NULL;
    hi2s->ErrorCallback             = NULL;
}

#endif /* HAL_I2S_MODULE_ENABLED */

/************************ (C) COPYRIGHT AISINOCHIP *****END OF FILE****/








