/******************************************************************************
*@file  : hal_dma.c
*@brief : DMA HAL module driver.
******************************************************************************/
#include "hal.h" 

#ifdef HAL_DMA_MODULE_ENABLED

/******************************************************************************
*@brief : This function handles DMA interrupt request.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for DMA module.
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma)
{
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
    
    /* Channel has been interrupted */
    if (hdma->DMA->INTSTATUS & (1UL << hdma->Channel))
    {
        /* Transfer complete interrupt */
        if ((hdma->DMA->INTTCSTATUS & (1UL << hdma->Channel)) && (hdma->Instance->CXCONFIG & DMA_CXCONFIG_ITC))
        {
            hdma->DMA->INTTCCLR = (1UL << hdma->Channel);
            if (hdma->XferCpltCallback)
            {
                hdma->XferCpltCallback(hdma);
            }
        }
        
		/* Transfer half interrupt */
        if ((hdma->DMA->INTTCSTATUS & ((1UL << hdma->Channel) << 8)) && (hdma->Instance->CXCONFIG & DMA_CXCONFIG_IHFTC))
		{
			hdma->DMA->INTTCCLR = 1UL << (hdma->Channel + 8);
			if (hdma->XferHalfCpltCallback)
            {
                hdma->XferHalfCpltCallback(hdma);
            }
		}
        
        /* Transfer error interrupt */
        if ((hdma->DMA->INTERRSTATUS & (1UL << hdma->Channel)) && (hdma->Instance->CXCONFIG & DMA_CXCONFIG_IE))
        {
            hdma->DMA->INTERRCLR = (1UL << hdma->Channel);
            if (hdma->XferErrorCallback)
            {
                hdma->XferErrorCallback(hdma);
            }
        }
    }
}

/******************************************************************************
*@brief : Initialize the DMA according to the specified.
*         parameters in the DMA_InitTypeDef and create the associated handle.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma) 
{
	uint32_t RequestID;
	
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(IS_DMA_MODE(hdma->Init.Mode));
	assert_param(IS_FUNCTIONAL_STATE(hdma->Init.Lock));
	assert_param(IS_DMA_DATAFLOW(hdma->Init.DataFlow));
	assert_param(IS_DMA_SRCINCDEC(hdma->Init.SrcIncDec));
	assert_param(IS_DMA_DESTINCDEC(hdma->Init.DestIncDec));
	assert_param(IS_DMA_SRCWIDTH(hdma->Init.SrcWidth));
	assert_param(IS_DMA_DESTWIDTH(hdma->Init.DestWidth));
	assert_param(IS_DMA_SRCBURST(hdma->Init.SrcBurst));
	assert_param(IS_DMA_DESTBURST(hdma->Init.DestBurst));
	assert_param(IS_DMA_SRCMASTER(hdma->Init.SrcMaster));
	assert_param(IS_DMA_DESTMASTER(hdma->Init.DestMaster));
    
    /* Init the low level hardware : clock */
    HAL_DMA_MspInit(hdma);
    
    /* calculation of the channel index */
	if ((uint32_t)(hdma->Instance) < (uint32_t)(DMA2_Channel0))
	{
        /* Check the parameters */
        assert_param(IS_DMA_REQ1ID(hdma->Init.DataFlow, hdma->Init.ReqID));
        
	    /* DMA1 */
		hdma->Channel = ((uint32_t)(hdma->Instance) - (uint32_t)(DMA1_Channel0)) >> 5;
		hdma->DMA = DMA1;
	}
	else
	{
        /* Check the parameters */
        assert_param(IS_DMA_REQ2ID(hdma->Init.DataFlow, hdma->Init.ReqID));
        
	    /* DMA2 */
		hdma->Channel = ((uint32_t)(hdma->Instance) - (uint32_t)(DMA2_Channel0)) >> 5;
		hdma->DMA = DMA2;
	}
	
    /* Enable DMA */
    hdma->DMA->CONFIG |= DMA_CONFIG_EN;
	
    /* Clear Channel Config */
    hdma->Instance->CXCONFIG = 0; 
    
    if (hdma->Init.DataFlow == DMA_DATAFLOW_M2P) 
    {
        RequestID = hdma->Init.ReqID << DMA_CXCONFIG_DESTPERIPH_Pos;
    }
    else if (hdma->Init.DataFlow == DMA_DATAFLOW_P2M) 
    {
        RequestID = hdma->Init.ReqID << DMA_CXCONFIG_SRCPERIPH_Pos;
    }
	else
	{
		RequestID = 0;
	}

    hdma->Instance->CXCONFIG = hdma->Init.DataFlow | RequestID | hdma->Init.SrcMaster | hdma->Init.DestMaster;
	if (hdma->Init.Lock)
		hdma->Instance->CXCONFIG |= DMA_CXCONFIG_LOCK;
    
    /* Config Channel Control */
    hdma->Instance->CXCTRL = DMA_CXCTRL_RITEN;
	
    /* Source or Desination address increase */
    hdma->Instance->CXCTRL |= (hdma->Init.DestIncDec | hdma->Init.SrcIncDec);
	
    /* Source or Desination date width */
    hdma->Instance->CXCTRL |= (hdma->Init.DestWidth | hdma->Init.SrcWidth);

    /* Source or Desination burst size */
    hdma->Instance->CXCTRL |= hdma->Init.SrcBurst | hdma->Init.DestBurst;
    
    if (hdma->Init.Mode == DMA_MODE_NORMAL)
        hdma->Instance->CXLLI = 0;
    else
    {
        /* Check the parameters */
        assert_param(IS_DMA_NEXTMASTER(hdma->Init.NextMaster));
        
        hdma->Instance->CXLLI = hdma->Init.NextMaster;
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : DeInitializes the DMA peripheral.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma)
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	
    /* DeInit the low level hardware */
    HAL_DMA_MspDeInit(hdma);
    
	hdma->Instance->CXCONFIG	= 0U;
	hdma->Instance->CXCTRL		= 0U;
	hdma->Instance->CXSRCADDR	= 0U;
	hdma->Instance->CXDESTADDR	= 0U;
	hdma->Instance->CXLLI		= 0U;
	
    hdma->XferCpltCallback		= NULL;
    hdma->XferHalfCpltCallback	= NULL;
	hdma->XferErrorCallback		= NULL;
	hdma->XferAbortCallback		= NULL;
	
	hdma->DMA					= 0U;
	hdma->Channel    			= 0U;

    return HAL_OK;
}

/******************************************************************************
*@brief : Initialize the DMA MSP.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_DMA_MspInit(DMA_HandleTypeDef *hdma)
{
    UNUSED(hdma);
}

/******************************************************************************
*@brief : DeInitialize the DMA MSP.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_DMA_MspDeInit(DMA_HandleTypeDef *hdma)
{
    UNUSED(hdma);
}

/******************************************************************************
*@brief : Register callbacks.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : CallbackID: User Callback identifier
*                     This parameter can be a combination of @ref DMA_XfeCallbackID.
*                     @arg DMA_CALLBACKID_CPLT: Transfer completion interrupt callback function.
*                     @arg DMA_CALLBACKID_HALFCPLT: Half transfer completion interrupt callback function.
*                     @arg DMA_CALLBACKID_ERROR: Error interrupt callback function.
*                     @arg DMA_CALLBACKID_ABORT: Abort callback function.
*@param : pCallback: callback function.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, uint32_t CallbackID, \
                                     void (* pCallback)(struct __DMA_HandleTypeDef * hdma))
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(IS_DMA_CALLBACK(CallbackID));
	
	switch (CallbackID)
	{
		case  DMA_CALLBACKID_CPLT:
			
			hdma->XferCpltCallback = pCallback;
			break;

		case  DMA_CALLBACKID_HALFCPLT:
			
			hdma->XferHalfCpltCallback = pCallback;
			break;

		case  DMA_CALLBACKID_ERROR:
			
			hdma->XferErrorCallback = pCallback;
			break;

		case  DMA_CALLBACKID_ABORT:
			
			hdma->XferAbortCallback = pCallback;
			break;

		default:
			return HAL_ERROR;
	}
	
	return HAL_OK;
}

/******************************************************************************
*@brief : UnRegister callbacks.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : CallbackID: User Callback identifier
*                     This parameter can be a combination of @ref DMA_XfeCallbackID.
*                     @arg DMA_CALLBACKID_CPLT: Transfer completion interrupt callback function.
*                     @arg DMA_CALLBACKID_HALFCPLT: Half transfer completion interrupt callback function.
*                     @arg DMA_CALLBACKID_ERROR: Error interrupt callback function.
*                     @arg DMA_CALLBACKID_ABORT: Abort callback function.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, uint32_t CallbackID)
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(IS_DMA_CALLBACK(CallbackID));
	
	switch (CallbackID)
	{
		case  DMA_CALLBACKID_CPLT:
			
			hdma->XferCpltCallback = NULL;
			break;

		case  DMA_CALLBACKID_HALFCPLT:
			
			hdma->XferHalfCpltCallback = NULL;
			break;

		case  DMA_CALLBACKID_ERROR:
			
			hdma->XferErrorCallback = NULL;
			break;

		case  DMA_CALLBACKID_ABORT:
			
			hdma->XferAbortCallback = NULL;
			break;

		default:
			return HAL_ERROR;
	}
	
	return HAL_OK;
}

/******************************************************************************
*@brief : Starts the DMA Transfer.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : SrcAddr: The source memory Buffer address.
*@param : DestAddr: The destination memory Buffer address.
*@param : Size: The length of data to be transferred from source to destination.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t SrcAddr, uint32_t DestAddr, uint32_t TransferSize)
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(IS_DMA_MODE(hdma->Init.Mode));
	assert_param(IS_DMA_SRCADDR(SrcAddr));
	assert_param(IS_DMA_DESTADDR(DestAddr));
	assert_param(IS_DMA_TRANSFERSIZE(TransferSize));
	
    /* DMA Channel Disable */
    hdma->Instance->CXCONFIG &= ~DMA_CXCONFIG_EN;
	
    /* Set source address and desination address */
    hdma->Instance->CXSRCADDR  = SrcAddr;
    hdma->Instance->CXDESTADDR = DestAddr;
	
    /* Set Transfer Size */
    hdma->Instance->CXCTRL = (hdma->Instance->CXCTRL & ~DMA_TRANSFER_SIZE) | (TransferSize << DMA_CXCTRL_TRANSFERSIZE_Pos);
    
    /* Set Next Link */
    if (hdma->Init.Mode == DMA_MODE_NORMAL)
    {
        hdma->Instance->CXLLI = 0;
    }
    else
    {
        hdma->Instance->CXLLI = (hdma->Instance->CXLLI & ~DMA_CXLLI_LLI) | ((uint32_t)(&hdma->Link) & DMA_CXLLI_LLI);
        
        hdma->Link.SrcAddr = hdma->Instance->CXSRCADDR;
        hdma->Link.DestAddr = hdma->Instance->CXDESTADDR;
        hdma->Link.Next = hdma->Instance->CXLLI;
        hdma->Link.Ctrl = (hdma->Instance->CXCTRL & ~DMA_TRANSFER_SIZE) | (TransferSize << DMA_CXCTRL_TRANSFERSIZE_Pos);
    }
    
    /* Disable interrupt */
	hdma->Instance->CXCONFIG &= ~(DMA_CXCONFIG_IHFTC | DMA_CXCONFIG_ITC | DMA_CXCONFIG_IE);
	
    /* DMA Channel Enable */
    hdma->Instance->CXCONFIG |= DMA_CXCONFIG_EN;

    return HAL_OK;
}

/******************************************************************************
*@brief : Start the DMA Transfer with interrupt enabled.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : SrcAddr: The source memory Buffer address.
*@param : DestAddr: The destination memory Buffer address.
*@param : Size: The length of data to be transferred from source to destination.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddr, uint32_t DestAddr, uint32_t TransferSize)
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(IS_DMA_MODE(hdma->Init.Mode));
	assert_param(IS_DMA_SRCADDR(SrcAddr));
	assert_param(IS_DMA_DESTADDR(DestAddr));
	assert_param(IS_DMA_TRANSFERSIZE(TransferSize));
    
    /* DMA Channel Disable */
    hdma->Instance->CXCONFIG &= ~DMA_CXCONFIG_EN;
	
    /* Set source address and desination address */
    hdma->Instance->CXSRCADDR  = SrcAddr;
    hdma->Instance->CXDESTADDR = DestAddr;
	
    /* Set Transfer Size and enable LLI interrupt */
    hdma->Instance->CXCTRL = (hdma->Instance->CXCTRL & ~DMA_CXCTRL_TRANSFERSIZE) | (TransferSize << DMA_CXCTRL_TRANSFERSIZE_Pos);

    /* Enable interrupt */
	hdma->Instance->CXCONFIG &= ~DMA_CXCONFIG_IHFTC;
	hdma->Instance->CXCONFIG |= DMA_CXCONFIG_ITC | DMA_CXCONFIG_IE;	
	
    if (hdma->XferHalfCpltCallback)
	{
		hdma->Instance->CXCONFIG |= DMA_CXCONFIG_IHFTC;	
	}

    /* Set Next Link */
    if (hdma->Init.Mode == DMA_MODE_NORMAL)
    {
        hdma->Instance->CXLLI = 0;
    }
    else
    {
        hdma->Instance->CXLLI = ((uint32_t)(&hdma->Link) & DMA_CXLLI_LLI) | (hdma->Instance->CXLLI & DMA_CXLLI_LM);
        hdma->Link.SrcAddr = hdma->Instance->CXSRCADDR;
        hdma->Link.DestAddr = hdma->Instance->CXDESTADDR;
        hdma->Link.Next = hdma->Instance->CXLLI;
        hdma->Link.Ctrl = (hdma->Instance->CXCTRL & ~DMA_CXCTRL_TRANSFERSIZE) | (TransferSize << DMA_CXCTRL_TRANSFERSIZE_Pos);
    }
    
    /* DMA Channel Enable */
    hdma->Instance->CXCONFIG |= DMA_CXCONFIG_EN;
	
    return HAL_OK;
}

/******************************************************************************
*@brief : Initialize linked list.
*@param : Link: Initialize linked list node.
*@param : Link_Init: pointer to an DMA_LinkInitTypeDef structure that contains 
*                    the configuration information for the specified Link.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_InitLink(DMA_LinkTypeDef *Link, DMA_LinkInitTypeDef *Link_Init)
{
    /* Check the parameters */
	assert_param(Link != NULL);
	assert_param(Link_Init != NULL);
	assert_param(IS_DMA_SRCADDR(Link_Init->SrcAddr));
	assert_param(IS_DMA_DESTADDR(Link_Init->DestAddr));
    assert_param(IS_DMA_NEXT(Link_Init->Next));
    assert_param(IS_DMA_NEXTMASTER(Link_Init->NextMaster));
	assert_param(IS_DMA_RAWIT(Link_Init->RawInt));
	assert_param(IS_DMA_SRCINCDEC(Link_Init->SrcIncDec));
	assert_param(IS_DMA_DESTINCDEC(Link_Init->DestIncDec));
	assert_param(IS_DMA_SRCWIDTH(Link_Init->SrcWidth));
	assert_param(IS_DMA_DESTWIDTH(Link_Init->DestWidth));
	assert_param(IS_DMA_SRCBURST(Link_Init->SrcBurst));
	assert_param(IS_DMA_DESTBURST(Link_Init->DestBurst));
	assert_param(IS_DMA_TRANSFERSIZE(Link_Init->TransferSize));

	Link->SrcAddr = Link_Init->SrcAddr;
	Link->DestAddr = Link_Init->DestAddr;
	Link->Next = (Link_Init->Next & DMA_CXLLI_LLI) | Link_Init->NextMaster;
	Link->Ctrl = Link_Init->RawInt | Link_Init->SrcIncDec | Link_Init->DestIncDec | \
                 Link_Init->SrcWidth | Link_Init->DestWidth | Link_Init->SrcBurst | \
                 Link_Init->DestBurst | Link_Init->TransferSize ;

    return HAL_OK;
}

/******************************************************************************
*@brief : Set the next node of the linked node.
*@param : Curr: current linked node.
*@param : Next: next linked node.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_SetLinkNext(DMA_LinkTypeDef *Curr, DMA_LinkTypeDef *Next)
{
    /* Check the parameters */
    assert_param(IS_DMA_NEXT(Curr));
    assert_param(IS_DMA_NEXT(Next));
	
    Curr->Next = (Curr->Next & ~DMA_CXLLI_LLI) | ((uint32_t)Next & DMA_CXLLI_LLI);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : DMA link transfer start.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : Link: First node of linked list.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_Start_Link(DMA_HandleTypeDef *hdma, DMA_LinkTypeDef *Link)
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(Link != NULL);

    /* DMA Channel Disable */
    hdma->Instance->CXCONFIG &= ~DMA_CXCONFIG_EN;
	
    /* Set source address and desination address */
    hdma->Instance->CXSRCADDR  = Link->SrcAddr;
    hdma->Instance->CXDESTADDR = Link->DestAddr;

    /* Set Next Link */
    hdma->Instance->CXLLI = Link->Next;

    /* Set Transfer Size */
    hdma->Instance->CXCTRL = Link->Ctrl;

    hdma->Instance->CXCONFIG &= ~(DMA_CXCONFIG_IHFTC | DMA_CXCONFIG_ITC | DMA_CXCONFIG_IE);
    
    /* DMA Channel Enable */
    hdma->Instance->CXCONFIG |= DMA_CXCONFIG_EN;

    return HAL_OK;
}

/******************************************************************************
*@brief : DMA link transfer start.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : Link: First node of linked list.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_Start_Link_IT(DMA_HandleTypeDef *hdma, DMA_LinkTypeDef *Link)
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(Link != NULL);

    /* DMA Channel Disable */
    hdma->Instance->CXCONFIG &= ~DMA_CXCONFIG_EN;
	
    /* Set source address and desination address */
    hdma->Instance->CXSRCADDR  = Link->SrcAddr;
    hdma->Instance->CXDESTADDR = Link->DestAddr;
    hdma->Instance->CXLLI = Link->Next;
    hdma->Instance->CXCTRL = Link->Ctrl;

    hdma->Instance->CXCONFIG |= DMA_CXCONFIG_ITC | DMA_CXCONFIG_IE;
    hdma->Instance->CXCONFIG &= ~DMA_CXCONFIG_IHFTC;
    if (hdma->XferHalfCpltCallback)
        hdma->Instance->CXCONFIG |= DMA_CXCONFIG_IHFTC;
	
    /* DMA Channel Enable */
    hdma->Instance->CXCONFIG |= DMA_CXCONFIG_EN;

    return HAL_OK;
}

/******************************************************************************
*@brief : Abort the DMA Transfer .
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma)
{
    uint32_t timeout;

    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));

    /* Disable interrupt */
    hdma->Instance->CXCONFIG &= ~(DMA_CXCONFIG_IHFTC | DMA_CXCONFIG_ITC | DMA_CXCONFIG_IE);
    
    /* DMA Channel Abort */
    hdma->Instance->CXCONFIG |= DMA_CXCONFIG_HALT;
    
    /* Wait until data clearing in FIFO  */
    timeout = DMA_ABORT_TIMEOUT;
    while (hdma->Instance->CXCONFIG & DMA_CXCONFIG_ACTIVE)
    {
        if (timeout-- == 0)
			return HAL_ERROR;
    }
    
    /* Disable interrupt */
    hdma->Instance->CXCONFIG &= ~(DMA_CXCONFIG_HALT | DMA_CXCONFIG_EN);
    /* Clear TC ERR Falg */
    hdma->DMA->INTTCCLR  |= (1UL << hdma->Channel) | (1UL << (hdma->Channel + 8));
    hdma->DMA->INTERRCLR |= (1UL << hdma->Channel);

    /* Wait until the channel is closed  */
    timeout = DMA_ABORT_TIMEOUT;
    while (hdma->DMA->ENCHSTATUS & (1U << hdma->Channel))
    {
        if (timeout-- == 0)
            return HAL_TIMEOUT;
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Enable interrupt.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : IT: interrupt
*             This parameter can be a combination of @ref DMA_IT.
*             @arg DMA_IT_TC: transmission completion interrupt.
*             @arg DMA_IT_HTC: indicating half transmission completion interrupt.
*             @arg DMA_IT_ERR: error interrupt.
*             @arg DMA_IT_RAW: raw interrupt.
*@return: HAL status
******************************************************************************/
FunctionalState HAL_DMA_GetITSource(DMA_HandleTypeDef *hdma, uint32_t IT)
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(IS_DMA_IT(IT));

    if ((hdma->Instance->CXCONFIG & IT) == 0)
        return (DISABLE);
    else
        return (ENABLE);
}

/******************************************************************************
*@brief : Enable interrupt.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : IT: interrupt
*             This parameter can be a combination of @ref DMA_IT.
*             @arg DMA_IT_TC: transmission completion interrupt.
*             @arg DMA_IT_HTC: indicating half transmission completion interrupt.
*             @arg DMA_IT_ERR: error interrupt.
*             @arg DMA_IT_RAW: raw interrupt.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_EnableIT(DMA_HandleTypeDef *hdma, uint32_t IT)
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(IS_DMA_IT(IT));

    hdma->Instance->CXCONFIG |= IT;
    
	return HAL_OK;
}

/******************************************************************************
*@brief : Disable interrupt.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : IT: interrupt
*             This parameter can be a combination of @ref DMA_IT.
*             @arg DMA_IT_TC: transmission completion interrupt.
*             @arg DMA_IT_HTC: indicating half transmission completion interrupt.
*             @arg DMA_IT_ERR: error interrupt.
*             @arg DMA_IT_RAW: raw interrupt.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_DisableIT(DMA_HandleTypeDef *hdma, uint32_t IT)
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(IS_DMA_IT(IT));

    hdma->Instance->CXCONFIG &= ~IT;
    
	return HAL_OK;
}

/******************************************************************************
*@brief : Clear the DMA flag.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : Flag: DMA flag
*               This parameter can be a combination of the following:
*               @arg DMA_FLAG_TC: indicating transmission completion interrupt occur.
*               @arg DMA_FLAG_HTC: indicating half transmission completion interrupt occur.
*               @arg DMA_FLAG_ERR: indicating error interrupt occur.
*               @arg DMA_FLAG_RTC: indicating raw transmission completion interrupt occur.
*               @arg DMA_FLAG_RHTC: indicating raw half transmission completion interrupt occur.
*               @arg DMA_FLAG_RERR: indicating raw error interrupt occur.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_DMA_ClearFlag(DMA_HandleTypeDef *hdma, uint32_t Flag)
{
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(IS_DMA_FLAG(Flag));

	if (Flag &( DMA_FLAG_TC | DMA_FLAG_RTC))
		hdma->DMA->INTTCCLR = 1UL << hdma->Channel;
	if (Flag &( DMA_FLAG_HTC | DMA_FLAG_RHTC))
		hdma->DMA->INTTCCLR = 1UL << (hdma->Channel + 8);
	if (Flag &( DMA_FLAG_ERR | DMA_FLAG_RERR))
		hdma->DMA->INTERRCLR = 1UL << hdma->Channel;
		
	return HAL_OK;
}

/******************************************************************************
*@brief : Returns the DMA flag.
*@param : hdma: pointer to a DMA_HandleTypeDef structure that contains
*               the configuration information for the specified DMA Channel.
*@param : Flag: DMA flag
*               This parameter can be a combination of the following:
*               @arg DMA_FLAG_IT: indicating transmission completion interrupt or error interrupt occur.
*               @arg DMA_FLAG_TC: indicating transmission completion interrupt occur.
*               @arg DMA_FLAG_HTC: indicating half transmission completion interrupt occur.
*               @arg DMA_FLAG_ERR: indicating error interrupt occur.
*               @arg DMA_FLAG_RTC: indicating raw transmission completion interrupt occur.
*               @arg DMA_FLAG_RHTC: indicating raw half transmission completion interrupt occur.
*               @arg DMA_FLAG_RERR: indicating raw error interrupt occur.
*@return: DMA flag
******************************************************************************/
FlagStatus HAL_DMA_GetFlag(DMA_HandleTypeDef *hdma, uint32_t Flag)
{
    uint32_t Status;
    
    /* Check the parameters */
	assert_param(IS_DMA_HANDLE(hdma));
	assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
	assert_param(IS_DMA_FLAG(Flag));

    Status = 0;
	if (Flag & DMA_FLAG_TC)
	{
		if (hdma->DMA->INTTCSTATUS & (1UL << hdma->Channel))
            Status |= DMA_FLAG_TC;
	}
	if (Flag & DMA_FLAG_HTC)
	{
		if (hdma->DMA->INTTCSTATUS & (1UL << (hdma->Channel + 8)))
            Status |= DMA_FLAG_HTC;
	}
	if (Flag & DMA_FLAG_ERR)
	{
		if (hdma->DMA->INTERRSTATUS & (1UL << hdma->Channel))
            Status |= DMA_FLAG_ERR;
	}
	if (Flag & DMA_FLAG_RTC)
	{
		if (hdma->DMA->RAWINTTCSTATUS & (1UL << hdma->Channel))
            Status |= DMA_FLAG_RTC;
	}
	if (Flag & DMA_FLAG_RHTC)
	{
		if (hdma->DMA->RAWINTTCSTATUS & (1UL << (hdma->Channel + 8)))
            Status |= DMA_FLAG_RHTC;
	}
	if (Flag & DMA_FLAG_RERR)
	{
		if (hdma->DMA->RAWINTERRSTATUS & (1UL << hdma->Channel))
            Status |= DMA_FLAG_RERR;
	}
	
	return (Status);
}

#endif /* HAL_DMA_MODULE_ENABLED */


