/******************************************************************************
* @file  :  hal_usart.c
* @brief :  USART HAL module driver.
*          This file provides firmware functions to manage the following
*          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (USART).
* @ver   :  V1.0.0
* @date  :  2020
******************************************************************************/
#include "hal.h" 


#ifdef HAL_USART_MODULE_ENABLED

#define USART_DUMMY_DATA          ((uint16_t) 0xFFFF)

/* Private function prototypes -----------------------------------------------*/
static void USART_Config_BaudRate(USART_HandleTypeDef *husart);
static void USART_SetConfig(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef HAL_USART_Wait_Tx_Done(USART_HandleTypeDef *husart);
static HAL_StatusTypeDef USART_WaitOnFlagUntilTimeout(USART_HandleTypeDef *husart, uint32_t flag, FlagStatus status,
                                                      uint32_t tick_start, uint32_t timeout);

__weak void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart);
__weak void HAL_USART_RxCpltCallback(USART_HandleTypeDef *husart);
__weak void HAL_USART_ErrorCallback(USART_HandleTypeDef *husart);
__weak void HAL_USART_IdleCallback(USART_HandleTypeDef *husart);
/******************************************************************************
*@brief : Handle USART interrupt request
*         
*@param : husart: usart handle with USART parameters.
*@return: None
******************************************************************************/
__weak void HAL_USART_IRQHandler(USART_HandleTypeDef *husart)
{
    uint32_t isrflags;
    uint32_t ieits;
    uint32_t errorflags;
    uint16_t *pbuf_16;
    
    assert_param(IS_USART_ALL_INSTANCE(husart->Instance));

    isrflags = READ_REG(husart->Instance->ISR);
    ieits    = READ_REG(husart->Instance->IE);
    
    errorflags =(isrflags & (uint32_t)(USART_ISR_PEI | USART_ISR_OEI | USART_ISR_FEI | USART_ISR_BEI));
    
    /* which isr actually occured */
    isrflags &= ieits;    
	
    /* TXI */
    if (isrflags & USART_ISR_TXI)
    {
        /* Clear TXI Status */
        CLEAR_STATUS(husart->Instance->ISR, USART_ISR_TXI);
        
        pbuf_16 = (uint16_t *)husart->TxData;

        for(;;)
        {
            if(husart->TxCount == husart->TxSize) 
            {                               
                husart->TxBusy = false;
         
                /* Disable TX interrupt && error interrupt*/
                CLEAR_BIT(husart->Instance->IE, USART_IE_TXI |
                                               USART_IE_OEI | USART_IE_BEI | USART_IE_PEI | USART_IE_FEI); 

                HAL_USART_TxCpltCallback(husart);
                return;
            }

            if (READ_BIT(husart->Instance->FR, USART_FR_TXFF))
            {
                break;
            }
            
            if (husart->Init.WordLength == USART_WORDLENGTH_9B)
            {
                husart->Instance->DR = (uint16_t)(pbuf_16[husart->TxCount++] & 0x01FFU);
            }
            else
            {
                husart->Instance->DR = husart->TxData[husart->TxCount++];
            }
        }
    }

    /* RXI */
    if (isrflags & USART_ISR_RXI) 
    {
        /* Clear RXI Status */
        CLEAR_STATUS(husart->Instance->ISR, USART_ISR_RXI);
        
        pbuf_16 = (uint16_t *)husart->RxData;
                      
        while(husart->RxCount < husart->RxSize )  
        {
            if(!READ_BIT(husart->Instance->FR, USART_FR_RXFE))
            {
                 /* Store Data in buffer */
                 if (husart->Init.WordLength == USART_WORDLENGTH_9B)
                 {
                    pbuf_16[husart->RxCount++] = (uint16_t)(husart->Instance->DR & 0x1FFU);
                 }
                 else
                 {
                    husart->RxData[husart->RxCount++] = (uint8_t)husart->Instance->DR;	
                 }                         
            }  
            else
            {
                break;
            }  
        }
        
        if(husart->RxCount == husart->RxSize )
        {
            husart->RxBusy = false;
        
            /* Disable RX and RTI interrupt && error interrupt*/
            CLEAR_BIT(husart->Instance->IE, (USART_IE_RXI | USART_IE_IDLEI |
                                            USART_IE_OEI | USART_IE_BEI | USART_IE_PEI | USART_IE_FEI));
            
            HAL_USART_RxCpltCallback(husart);
       }
    }
    /* IDLEI */
    else if(isrflags & USART_ISR_IDLEI)  
    {
        /*clear IDLE Status */
        CLEAR_STATUS(husart->Instance->ISR, USART_ISR_IDLEI);
        
        pbuf_16 = (uint16_t *)husart->RxData;

        while(!READ_BIT(husart->Instance->FR, USART_FR_RXFE))
        {
            if (husart->Init.WordLength == USART_WORDLENGTH_9B)
            {
                pbuf_16[husart->RxCount++] = (uint16_t)(husart->Instance->DR & 0x1FFU);
            }
            else
            {                    
                husart->RxData[husart->RxCount++] = (uint8_t)husart->Instance->DR;
            }
        }
        
        husart->RxBusy = false;
        
        /* Disable RX and RTI interrupt && error interrupt*/
        CLEAR_BIT(husart->Instance->IE, (USART_IE_RXI | USART_IE_IDLEI |
                                        USART_IE_OEI | USART_IE_BEI | USART_IE_PEI | USART_IE_FEI));

        

        HAL_USART_IdleCallback(husart);
    }		
    
	/* if some errors occurred */
	if(errorflags != 0)
	{
		/* USART parity error interrupt occurred */
	    if (((errorflags & USART_ISR_PEI) != 0))
	    {
	    	/* Clear parity error status */
            CLEAR_STATUS(husart->Instance->ISR, USART_ISR_PEI);
	      	husart->ErrorCode |= HAL_USART_ERROR_PE;
	    }

	    /* USART break error interrupt occurred */
	    if (((errorflags & USART_ISR_BEI) != 0))
	    {
            CLEAR_STATUS(husart->Instance->ISR, USART_ISR_BEI);
	      	husart->ErrorCode |= HAL_USART_ERROR_NE;
	    }

	    /* USART frame error interrupt occurred */
	    if (((errorflags & USART_ISR_FEI) != 0))
	    {
            CLEAR_STATUS(husart->Instance->ISR, USART_ISR_FEI);
	      	husart->ErrorCode |= HAL_USART_ERROR_FE;
	    }

	    /* USART Over-Run interrupt occurred */
	    if (((errorflags & USART_ISR_OEI) != 0))
	    {
            CLEAR_STATUS(husart->Instance->ISR, USART_ISR_OEI);
	      	husart->ErrorCode |= HAL_USART_ERROR_ORE;
	    }

        HAL_USART_ErrorCallback(husart);
	}    
}


/******************************************************************************
*@brief : wait Tx FIFO empty
*         
*@param : husart: usart handle with USART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef HAL_USART_Wait_Tx_Done(USART_HandleTypeDef *husart)
{	

    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));
    
	/* wait TX not busy*/
	while(READ_BIT(husart->Instance->FR, USART_FR_BUSY)); 

	return HAL_OK;
}

/******************************************************************************
*@brief : Initialize the USART MSP: CLK, GPIO, NVIC
*         
*@param : husart: usart handle with USART parameters.
*@return: None
******************************************************************************/
__weak void HAL_USART_MspInit(USART_HandleTypeDef *husart)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(husart);
}

/******************************************************************************
*@brief : Initialize the USART according to the specified parameters in husart.
*         
*@param : husart: usart handle with USART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_Init(USART_HandleTypeDef *husart)
{
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));
//    assert_param (IS_USART_WORDLENGTH(husart->Init.WordLength));
//    assert_param (IS_USART_STOPBITS(husart->Init.StopBits));
//    assert_param (IS_USART_PARITY(husart->Init.Parity));
//    assert_param (IS_USART_MODE(husart->Init.Mode));
//    assert_param(IS_USART_POLARITY(husart->Init.CLKPolarity));
//    assert_param(IS_USART_PHASE(husart->Init.CLKPhase));
//    assert_param(IS_USART_LASTBIT(husart->Init.CLKLastBit));
//    assert_param (IS_USART_HARDWARE_FLOW_CONTROL(husart->Init.HwFlowCtl));
    
#if 1
    if(husart->Instance == USART1)
        __HAL_RCC_USART1_RESET();
    else if(husart->Instance == USART2)
        __HAL_RCC_USART2_RESET();
#endif
    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_USART_MspInit(husart);
    
//    /* Config BaudRate */
//    USART_Config_BaudRate(husart);
    
    /* Set the USART Communication parameters */
    USART_SetConfig(husart);
    
    
    /* In USART mode, the following bits must be kept cleared:
     - LINEN bit in the USART_CR2 register
     - HDSEL, SCEN and IREN bits in the USART_CR3 register */
    //CLEAR_BIT(husart->Instance->CR2, USART_CR2_LINEN);
    CLEAR_BIT(husart->Instance->CR2, (USART_CR2_SCEN | USART_CR2_HDSEL));
    CLEAR_BIT(husart->Instance->CR1, (USART_CR1_SIREN));
//    /* Set the USART Communication parameters */
//    husart->Instance->CR3 = husart->Init.WordLength | USART_CR3_FEN | husart->Init.StopBits | husart->Init.Parity;
//    husart->Instance->CR1 = husart->Init.HwFlowCtl | husart->Init.Mode;
//    
//    if (husart->Init.Mode == USART_MODE_HALF_DUPLEX) 
//    {
//        SET_BIT(husart->Instance->CR2, USART_CR2_HDSEL);
//    }
    
    __HAL_USART_ENABLE(husart);
    
    husart->ErrorCode = HAL_USART_ERROR_NONE;
    
	return HAL_OK;
}

/******************************************************************************
*@brief : DeInitialize the USART MSP
*         
*@param : husart: usart handle with USART parameters.
*@return: None
******************************************************************************/
__weak void HAL_USART_MspDeInit(USART_HandleTypeDef *husart)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(husart);
}

/******************************************************************************
*@brief : DeInitialize the USART module
*         
*@param : husart: usart handle with USART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_DeInit(USART_HandleTypeDef *husart)
{

    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));

    /* DeInit the low level hardware : GPIO, CLOCK, NVIC */
    HAL_USART_MspDeInit(husart);

	return HAL_OK;
    
}

/******************************************************************************
*@brief : Send an amount of data by loop mode within timeout period.
*         
*@param : husart: usart handle with USART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to be sent.
*@param : timeout: Timeout duration, unit MS, 1(ms)~~0xFFFFFFFF(wait forever)
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_Transmit(USART_HandleTypeDef *husart, uint8_t *buf, uint32_t size, uint32_t timeout)
{
    uint16_t *pbuf_16;
    uint32_t Start_Tick;
    
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));
    
    if ((buf == NULL) || (size == 0U))
    {
      return HAL_ERROR;
    }
    
    

    husart->TxCount = 0;
    husart->TxData = buf;
    pbuf_16 = (uint16_t *)husart->TxData;

	SET_BIT(husart->Instance->CR1, USART_CR1_TXE);
    CLEAR_BIT(husart->Instance->CR1, USART_CR1_RXE);//add 0204
    
    Start_Tick = HAL_GetTick();
    
    while (size--) 
    {
        if (husart->Init.WordLength == UART_WORDLENGTH_9B)
        {
            husart->Instance->DR = (uint16_t)(pbuf_16[husart->TxCount++] & 0x01FFU);
        }
        else
        {
            husart->Instance->DR = husart->TxData[husart->TxCount++];
        }      
        while (husart->Instance->FR & USART_FR_TXFF)
        {
            if ((HAL_GetTick() - Start_Tick) > timeout) 
            {
                return HAL_TIMEOUT;
            }
        }
    }
    
    HAL_USART_Wait_Tx_Done(husart); 
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data by loop mode within timeout period.
*         
*@param : husart: usart handle with USART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to receive.
*@param : timeout: Timeout duration, unit MS, 1(ms)~~0xFFFFFFFF(wait forever)
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_Receive(USART_HandleTypeDef *husart, uint8_t *buf, uint32_t size, uint32_t timeout)
{
    uint16_t *pbuf_16;
    uint32_t Start_Tick;
    
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));
    
    if ((buf == NULL) || (size == 0U))
    {
      return HAL_ERROR;
    }

    husart->RxCount = 0;
    husart->RxData = buf;
    pbuf_16 = (uint16_t *)husart->RxData;
    
    /* In case RXE is disabled in transmit funtion */
    SET_BIT(husart->Instance->CR1, USART_CR1_RXE);
    
    Start_Tick = HAL_GetTick();

    while (size--) 
    {
        while (husart->Instance->FR & USART_FR_TXFF)
        {
            if ((HAL_GetTick() - Start_Tick) > timeout) 
            {
                return HAL_TIMEOUT;
            }
        }
        
        //husart->Instance->DR = (USART_DUMMY_DATA & (uint16_t)0x1FF);
        
        husart->Instance->DR = (USART_DUMMY_DATA & 0xFF);
        
        while(husart->Instance->FR & USART_FR_RXFE)
        {
            if ((HAL_GetTick() - Start_Tick) > timeout)  
            {
                return HAL_TIMEOUT;
            }
        }

        /* Store Data in buffer */
        if (husart->Init.WordLength == UART_WORDLENGTH_9B)
        {
            pbuf_16[husart->RxCount++] = (uint16_t)(husart->Instance->DR & 0x1FFU);
        }
        else
        {
            husart->RxData[husart->RxCount++] = (uint8_t)husart->Instance->DR;	
        }      
    }
    
    return HAL_OK;
}

#if 0
HAL_StatusTypeDef HAL_USART_Receive(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
    uint8_t  *pbuf_8  = NULL;
    uint16_t *pbuf_16 = NULL;
  uint8_t  *prxdata8bits;
  uint16_t *prxdata16bits;
  uint16_t uhMask;
  uint32_t tickstart;

  //if (husart->State == HAL_USART_STATE_READY)
  {
    if ((pRxData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }
    
    
    husart->RxCount = 0;
    
    if (husart->Init.WordLength == USART_WORDLENGTH_9B)
    {
      pbuf_16 = (uint16_t *) buf;
    }
    else
    {
      pbuf_8  = buf;
    }

    /* Process Locked */
    //__HAL_LOCK(husart);

    //husart->ErrorCode = HAL_USART_ERROR_NONE;
    //husart->State = HAL_USART_STATE_BUSY_RX;

    /* Init tickstart for timeout management */
    tickstart = HAL_GetTick();

    //husart->RxXferSize = Size;
    //husart->RxXferCount = Size;

    /* Computation of USART mask to apply to RDR register */
    //USART_MASK_COMPUTATION(husart);
    //uhMask = husart->Mask;

    /* In case of 9bits/No Parity transfer, pRxData needs to be handled as a uint16_t pointer */
    if ((husart->Init.WordLength == USART_WORDLENGTH_9B) && (husart->Init.Parity == USART_PARITY_NONE))
    {
      prxdata8bits  = NULL;
      prxdata16bits = (uint16_t *) pRxData;
    }
    else
    {
      prxdata8bits  = pRxData;
      prxdata16bits = NULL;
    }

    /* as long as data have to be received */
    while (husart->RxXferCount > 0U)
    {
      if (husart->SlaveMode == USART_SLAVEMODE_DISABLE)
      {
        /* Wait until TXE flag is set to send dummy byte in order to generate the
        * clock for the slave to send data.
        * Whatever the frame length (7, 8 or 9-bit long), the same dummy value
        * can be written for all the cases. */
        if (USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
        {
          return HAL_TIMEOUT;
        }
        husart->Instance->TDR = (USART_DUMMY_DATA & (uint16_t)0x0FF);
      }

      /* Wait for RXNE Flag */
      if (USART_WaitOnFlagUntilTimeout(husart, USART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      if (prxdata8bits == NULL)
      {
        *prxdata16bits = (uint16_t)(husart->Instance->RDR & uhMask);
        prxdata16bits++;
      }
      else
      {
        *prxdata8bits = (uint8_t)(husart->Instance->RDR & (uint8_t)(uhMask & 0xFFU));
        prxdata8bits++;
      }

      husart->RxXferCount--;

    }

    /* Clear SPI slave underrun flag and discard transmit data */
    if (husart->SlaveMode == USART_SLAVEMODE_ENABLE)
    {
      __HAL_USART_CLEAR_UDRFLAG(husart);
      __HAL_USART_SEND_REQ(husart, USART_TXDATA_FLUSH_REQUEST);
    }

    /* At end of Rx process, restore husart->State to Ready */
    husart->State = HAL_USART_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(husart);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}
#endif
/******************************************************************************
*@brief : Send an amount of data in interrupt mode.
*         
*@param : husart: usart handle with USART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to send.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_Transmit_IT(USART_HandleTypeDef *husart, uint8_t *buf, uint32_t size)
{
    uint16_t *pbuf_16;
    
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));
    
    if (husart->TxBusy == true) 
    {
        return HAL_BUSY;
    }
    
    if (size == 0 || buf == NULL) 
    {
        return HAL_ERROR;
    }
    
    husart->TxSize  = size;
    husart->TxCount = 0;
    husart->TxData   = buf;
    husart->TxBusy   = true;
    
	SET_BIT(husart->Instance->CR1, USART_CR1_TXE);
    /* Clear TXI Status */
    CLEAR_STATUS(husart->Instance->ISR, USART_ISR_TXI);
    /* FIFO Enable */
    SET_BIT(husart->Instance->CR3, USART_CR3_FEN);
	/*FIFO Select*/
    __USART_TXI_FIFO_LEVEL_SET(USART_TX_FIFO_1_2);

    for(;;) 
    {	
        /*Data Size less than 16Byte */
	    if(size == husart->TxCount) 
	    {
	        husart->TxBusy = false;
			
			while ((husart->Instance->FR & USART_FR_BUSY)){}
			
            HAL_USART_TxCpltCallback(husart);
			
	        return HAL_OK;  
	    }
	    if(READ_BIT(husart->Instance->FR, USART_FR_TXFF)) 
	    {				
	         break;
	    }
        if (husart->Init.WordLength == USART_WORDLENGTH_9B)
        {
            husart->Instance->DR = (uint16_t)(pbuf_16[husart->TxCount++] & 0x01FFU);
        }
        else
        {
            husart->Instance->DR = husart->TxData[husart->TxCount++];
        }
    }
	
    /* Enable TX interrupt */
    SET_BIT(husart->Instance->IE, USART_IE_TXI);

    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data in interrupt mode.
*         
*@param : husart: usart handle with USART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to receive.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_Receive_IT(USART_HandleTypeDef *husart, uint8_t *buf, uint32_t size)
{
    uint16_t *pbuf_16;
    
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));
    
    if (husart->RxBusy == true) 
    {
        return HAL_BUSY;
    }

    if (size == 0 || buf == NULL) 
    {
        return HAL_ERROR;
    }
    
    husart->RxSize  = size;
    husart->RxCount = 0;
    husart->RxData  = buf;
    husart->RxBusy  = true;
    pbuf_16 = (uint16_t *)husart->RxData;
    
	SET_BIT(husart->Instance->CR1, USART_CR1_RXE);
    /* FIFO Enable */
    SET_BIT(husart->Instance->CR3, USART_CR3_FEN);
	/*FIFO Select*/
    __USART_RXI_FIFO_LEVEL_SET(USART_RX_FIFO_1_2);
	/* Clear RXI && IDLEI Status */
    CLEAR_STATUS(husart->Instance->ISR, USART_ISR_RXI | USART_ISR_IDLEI);
    CLEAR_STATUS(husart->Instance->ISR, UART_ISR_PEI | UART_ISR_BEI | UART_ISR_OEI | UART_ISR_FEI);
	/* Enable the USART Errors interrupt */
	SET_BIT(husart->Instance->IE, USART_IE_OEI | USART_IE_BEI | USART_IE_PEI | USART_IE_FEI);
    /* Enable RX and RTI interrupt */
    SET_BIT(husart->Instance->IE, USART_IE_RXI | USART_IE_IDLEI); 

    return HAL_OK;
}

#ifdef HAL_DMA_MODULE_ENABLED
/******************************************************************************
*@brief : Send an amount of data in DMA mode.
*         
*@param : husart: usart handle with USART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to send.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_Transmit_DMA(USART_HandleTypeDef *husart, uint8_t *buf, uint32_t size)
{
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));

    if (husart->TxBusy == true) 
    {
        return HAL_BUSY;
    }

    if (size == 0 || buf == NULL) 
    {
        return HAL_ERROR;
    }
    
    husart->TxSize = size;
    husart->TxCount = 0;
    husart->TxData = buf;
    husart->TxBusy = true;
    
    SET_BIT(husart->Instance->CR1, USART_CR1_TXE);

    SET_BIT(husart->Instance->CR1, USART_CR1_TXDMAE);

    __USART_TXI_FIFO_LEVEL_SET(USART_TX_FIFO_1_16);

    if (HAL_DMA_Start_IT(husart->HDMA_Tx, (uint32_t)buf, (uint32_t)(&husart->Instance->DR), size))
    {
        CLEAR_BIT(husart->Instance->CR1, UART_CR1_TXDMAE);
        return HAL_ERROR;
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data in DMA mode.
*         
*@param : husart: usart handle with USART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to receive.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_Receive_DMA(USART_HandleTypeDef *husart, uint8_t *buf, uint32_t size)
{
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));

    if (husart->RxBusy == true) 
    {
        return HAL_BUSY;
    }

    if (size == 0 || buf == NULL) 
    {
        return HAL_ERROR;
    }
    
    husart->RxSize  = size;
    husart->RxCount = 0;
    husart->RxData  = buf;
    husart->RxBusy  = true;
    
    /* In case RXE is disabled in transmit funtion */
    SET_BIT(husart->Instance->CR1, USART_CR1_RXE);

    CLEAR_STATUS(husart->Instance->ISR, USART_ISR_IDLEI);
    
    SET_BIT(husart->Instance->CR1, USART_CR1_RXDMAE);
    
    __USART_RXI_FIFO_LEVEL_SET(USART_RX_FIFO_1_16);
    
    SET_BIT(husart->Instance->IE, USART_IE_IDLEI); 
    
    /* Enable the USART Errors interrupt */
	SET_BIT(husart->Instance->IE, USART_IE_OEI | USART_IE_BEI | USART_IE_PEI | USART_IE_FEI);

    if (HAL_DMA_Start_IT(husart->HDMA_Rx, (uint32_t)(&husart->Instance->DR), (uint32_t)buf, size))
    {
        CLEAR_BIT(husart->Instance->CR1, UART_CR1_RXDMAE);
        CLEAR_BIT(husart->Instance->IE, UART_IE_IDLEI | UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI);
        return HAL_ERROR;
    }

    return HAL_OK;
}
#endif

/******************************************************************************
*@brief : Tx Transfer completed callbacks.
*         
*@param : husart: usart handle with USART parameters.
*@return: None
******************************************************************************/
__weak void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart)
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_USART_TxCpltCallback could be implemented in the user file.
    */
}

/******************************************************************************
*@brief : Rx Transfer completed callbacks.
*         
*@param : husart: usart handle with USART parameters.
*@return: None
******************************************************************************/
__weak void HAL_USART_RxCpltCallback(USART_HandleTypeDef *husart)
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_USART_RxCpltCallback could be implemented in the user file.
    */
}

/******************************************************************************
*@brief : Rx Transfer idleline callbacks.
*         
*@param : husart: usart handle with USART parameters.
*@return: None
******************************************************************************/
__weak void HAL_USART_IdleCallback(USART_HandleTypeDef *husart)
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_USART_RxCpltCallback could be implemented in the user file.
    */
}

/******************************************************************************
*@brief : Recv Error callbacks.
*         
*@param : husart: usart handle with USART parameters.
*@return: None
******************************************************************************/
__weak void HAL_USART_ErrorCallback(USART_HandleTypeDef *husart)
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_USART_ErrorCallback could be implemented in the user file.
    */
}


/******************************************************************************
*@brief : Return the usart State
*         
*@param : husart: usart handle with USART parameters.
*@return: HAL_BUSY or HAL_OK
******************************************************************************/
HAL_StatusTypeDef HAL_USART_GetState(USART_HandleTypeDef *husart)
{
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));

	if(husart->TxBusy || husart->RxBusy)
	{
		return HAL_BUSY;		
	}

	return HAL_OK;
}

/******************************************************************************
*@brief : Return the usart Error
*         
*@param : husart: usart handle with USART parameters.
*@return: usart errcode
******************************************************************************/
uint32_t HAL_USART_GetError(USART_HandleTypeDef *husart)
{
  	return husart->ErrorCode;
}

#ifdef HAL_DMA_MODULE_ENABLED
/******************************************************************************
*@brief : Abort ongoing transfers(blocking mode)
*         
*@param : husart: usart handle with USART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_Abort(USART_HandleTypeDef *husart)
{
	assert_param (IS_USART_ALL_INSTANCE(husart->Instance));

	/*disble all interrupt*/
	husart->Instance->IE  =0x00;

	/* Disable the USART DMA Tx request if enable */
	if(READ_BIT(husart->Instance->CR1, USART_CR1_TXDMAE))
	{
		CLEAR_BIT(husart->Instance->CR1, USART_CR1_TXDMAE);

		/* Abort the USART Tx Channel   */
		if(husart->HDMA_Tx)
		{
			/*Set the USART DMA Abort callback to Null */
			husart->HDMA_Tx->XferCpltCallback =NULL;

			if(HAL_DMA_Abort(husart->HDMA_Tx)!=HAL_OK)
			{
				return HAL_TIMEOUT;
			}
		}
	}

	/* Disable the USART DMA Rx request if enable */
	if(READ_BIT(husart->Instance->CR1, USART_CR1_RXDMAE))
	{
		CLEAR_BIT(husart->Instance->CR1, USART_CR1_RXDMAE);
		
		/* Abort the USART Rx Channel   */
		if(husart->HDMA_Rx)
		{
			/*Set the USART DMA Abort callback to Null */
			husart->HDMA_Rx->XferCpltCallback =NULL;

			if(HAL_DMA_Abort(husart->HDMA_Rx)!=HAL_OK)
			{
				return HAL_TIMEOUT;
			}
		}
	}

	/*Reset Tx and Rx Transfer size*/
	husart->TxSize = 0;
	husart->RxSize = 0;

	/* Restore husart->TxBusy and husart->RxBusy to Ready */
	husart->TxBusy = false;
	husart->RxBusy = false;
		
	return HAL_OK;
}

/******************************************************************************
*@brief : Pause the USART DMA Transfer
*         
*@param : husart: usart handle with USART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_DMAPause(USART_HandleTypeDef *husart)
{
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));

    if(READ_BIT(husart->Instance->CR1, USART_CR1_TXDMAE))
    {
        /* Disable the USART DMA Tx request */
        CLEAR_BIT(husart->Instance->CR1, USART_CR1_TXDMAE);
    }

    if (READ_BIT(husart->Instance->CR1, USART_CR1_RXDMAE))
    {
        /* Disable RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts */
        CLEAR_BIT(husart->Instance->IE, USART_IE_OEI | USART_IE_PEI | USART_IE_BEI | USART_IE_FEI);

        /* Disable the USART DMA Rx request */
        CLEAR_BIT(husart->Instance->CR1, USART_CR1_RXDMAE);
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Resume the USART DMA Transfer
*         
*@param : husart: usart handle with USART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_DMAResume(USART_HandleTypeDef *husart)
{
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));

    if (husart->TxBusy == false)
    {
        /* Enable the USART DMA Tx request */
        SET_BIT(husart->Instance->CR1, USART_CR1_TXDMAE);
    }

    if (husart->RxBusy == false)
    {
        /* Reenable PE and ERR (Frame error, noise error, overrun error) interrupts */
        SET_BIT(husart->Instance->IE, USART_IE_OEI | USART_IE_PEI | USART_IE_BEI | USART_IE_FEI);

        /* Enable the USART DMA Rx request */
        SET_BIT(husart->Instance->CR1, USART_CR1_RXDMAE);
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Stop the USART DMA Transfer
*         
*@param : husart: usart handle with USART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_USART_DMAStop(USART_HandleTypeDef *husart)
{
    assert_param (IS_USART_ALL_INSTANCE(husart->Instance));
    
    if(husart->Instance->CR1 & USART_CR1_TXDMAE)
    {
        CLEAR_BIT(husart->Instance->CR1, USART_CR1_TXDMAE);
        if(husart->HDMA_Tx != NULL)
        {
            HAL_DMA_Abort(husart->HDMA_Tx);
        }
        
        CLEAR_BIT(husart->Instance->IE, (USART_IE_TXI));
    }
    
    if(husart->Instance->CR1 & USART_CR1_RXDMAE)
    {
        CLEAR_BIT(husart->Instance->CR1, USART_CR1_RXDMAE);
        if(husart->HDMA_Rx != NULL)
        {
            HAL_DMA_Abort(husart->HDMA_Rx);
        }

        CLEAR_BIT(husart->Instance->IE, (USART_IE_RXI | USART_IE_PEI));

        CLEAR_BIT(husart->Instance->IE, USART_IE_IDLEI);
    }

  return HAL_OK;
}
#endif

/**
  * @brief  Handle USART Communication Timeout.
  * @param  husart USART handle.
  * @param  Flag Specifies the USART flag to check.
  * @param  Status the Flag status (SET or RESET).
  * @param  Tickstart Tick start value
  * @param  Timeout timeout duration.
  * @retval HAL status
  */
static HAL_StatusTypeDef USART_WaitOnFlagUntilTimeout(USART_HandleTypeDef *husart, uint32_t flag, FlagStatus status,
                                                      uint32_t tick_start, uint32_t timeout)
{
  /* Wait until flag is set */
  while ((__HAL_USART_GET_FLAG(husart, flag) ? SET : RESET) == status)
  {
    /* Check for the Timeout */
    if (timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tick_start) > timeout) || (timeout == 0U))
      {
        //husart->State = HAL_USART_STATE_READY;

        /* Process Unlocked */
        //__HAL_UNLOCK(husart);

        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}

/******************************************************************************
*@brief : Config USART BaudRate
*         
*@param : husart: usart handle with USART parameters.
*@return: None
******************************************************************************/
static void USART_Config_BaudRate(USART_HandleTypeDef *husart)
{
    uint32_t pclk;
    uint32_t ibaud, fbaud;
    uint64_t tmp; 
    
    if (USART1 == husart->Instance) 
    {
        pclk = HAL_RCC_GetPCLK2Freq(); 
    }
    else
    {
        pclk = HAL_RCC_GetPCLK1Freq();  
    } 

    /* Integral part */
    ibaud = pclk / (husart->Init.BaudRate * 16);

    /* Fractional part */
    tmp = pclk % (husart->Init.BaudRate * 16);
    tmp = (tmp * 1000000) / (husart->Init.BaudRate * 16);
    fbaud     = (tmp * 64 + 500000) / 1000000;

    if (fbaud >= 64) 
    {
        MODIFY_REG(husart->Instance->BRR, USART_BRR_IBAUD_Msk, ((ibaud + 1) << USART_BRR_IBAUD_Pos));
        MODIFY_REG(husart->Instance->BRR, USART_BRR_FBAUD_Msk, (0 << USART_BRR_FBAUD_Pos));
    }
    else 
    {
        MODIFY_REG(husart->Instance->BRR, USART_BRR_IBAUD_Msk, (ibaud << USART_BRR_IBAUD_Pos));
        MODIFY_REG(husart->Instance->BRR, USART_BRR_FBAUD_Msk, (fbaud << USART_BRR_FBAUD_Pos));
    }
}

/**
  * @brief  Configures the USART peripheral.
  * @param  husart Pointer to a USART_HandleTypeDef structure that contains
  *                the configuration information for the specified USART module.
  * @retval None
  */
static void USART_SetConfig(USART_HandleTypeDef *husart)
{
  uint32_t tmpreg = 0x00U;
  uint32_t pclk;

  /* Check the parameters */
  assert_param(IS_USART_POLARITY(husart->Init.CLKPolarity));
  assert_param(IS_USART_PHASE(husart->Init.CLKPhase));
  assert_param(IS_USART_LASTBIT(husart->Init.CLKLastBit));
  assert_param(IS_USART_BAUDRATE(husart->Init.BaudRate));
  assert_param(IS_USART_WORDLENGTH(husart->Init.WordLength));
  assert_param(IS_USART_STOPBITS(husart->Init.StopBits));
  assert_param(IS_USART_PARITY(husart->Init.Parity));
  assert_param(IS_USART_MODE(husart->Init.Mode));

  /* The LBCL, CPOL and CPHA bits have to be selected when both the transmitter and the
     receiver are disabled (TE=RE=0) to ensure that the clock pulses function correctly. */
  CLEAR_BIT(husart->Instance->CR1, (USART_CR1_TXE | USART_CR1_RXE));

  /*---------------------------- USART CR2 Configuration ---------------------*/
  tmpreg = husart->Instance->CR2;
  /* Clear CLKEN, CPOL, CPHA and LBCL bits */
  tmpreg &= (uint32_t)~((uint32_t)(USART_CR2_CPHA | USART_CR2_CPOL | USART_CR2_CLKEN | USART_CR2_LBCL));
  /* Configure the USART Clock, CPOL, CPHA and LastBit -----------------------*/
  /* Set CPOL bit according to husart->Init.CLKPolarity value */
  /* Set CPHA bit according to husart->Init.CLKPhase value */
  /* Set LBCL bit according to husart->Init.CLKLastBit value */
  tmpreg |= (uint32_t)(USART_CLOCK_ENABLE | husart->Init.CLKPolarity |
                       husart->Init.CLKPhase | husart->Init.CLKLastBit);
  /* Write to USART CR2 */
  WRITE_REG(husart->Instance->CR2, (uint32_t)tmpreg);

  /*-------------------------- USART CR3 Configuration -----------------------*/
  tmpreg = husart->Instance->CR3;

  /* Clear M, PCE, PS, TE, RE and OVER8 bits */
  tmpreg &= (uint32_t)~((uint32_t)(USART_CR3_WLEN | USART_CR3_PEN | USART_CR3_SPS | USART_CR3_EPS| \
                                   USART_CR3_STP2));

  /* Configure the USART Word Length, Parity and mode, stop bits */
  tmpreg |= (uint32_t)husart->Init.WordLength | husart->Init.Parity | husart->Init.StopBits;

  /* Write to USART CR1 */
  WRITE_REG(husart->Instance->CR3, (uint32_t)tmpreg);
  
  
  husart->Instance->CR1 = husart->Init.Mode;

  /* Clear CTSE and RTSE bits */
  CLEAR_BIT(husart->Instance->CR1, (USART_CR1_RTSEN | USART_CR1_CTSEN));

  USART_Config_BaudRate(husart);
}

#endif //HAL_USART_MODULE_ENABLED

