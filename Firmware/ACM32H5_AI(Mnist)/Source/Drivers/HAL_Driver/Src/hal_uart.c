/******************************************************************************
* @file  :  hal_uart.c
* @brief :  UART HAL module driver.
*          This file provides firmware functions to manage the following
*          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (UART).
* @ver   :  V1.0.0
* @date  :  2020
******************************************************************************/
#include "hal.h" 


#ifdef HAL_UART_MODULE_ENABLED

UART_TypeDef *g_DebugUart = NULL;   //printf UARTx

/* Private function prototypes -----------------------------------------------*/
static void UART_Config_BaudRate(UART_HandleTypeDef *huart);
static HAL_StatusTypeDef HAL_UART_Wait_Tx_Done(UART_HandleTypeDef *huart);

__weak void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
__weak void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
__weak void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
__weak void HAL_UART_IdleCallback(UART_HandleTypeDef *huart);
/******************************************************************************
*@brief : Handle UART interrupt request
*         
*@param : huart: uart handle with UART parameters.
*@return: None
******************************************************************************/
__weak void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    uint32_t isrflags;
    uint32_t ieits;
    uint32_t errorflags;
    uint16_t *pbuf_16;

    assert_param(IS_UART_ALL_INSTANCE(huart->Instance));

    isrflags = READ_REG(huart->Instance->ISR);
    ieits    = READ_REG(huart->Instance->IE);
    
    errorflags =(isrflags & (uint32_t)(UART_ISR_PEI | UART_ISR_OEI | UART_ISR_FEI | UART_ISR_BEI));
    
    /* which isr actually occured */
    isrflags &= ieits; 

    /* TXI */
    if (isrflags & UART_ISR_TXI)
    {
        /* Clear TXI Status */
        CLEAR_STATUS(huart->Instance->ISR, UART_ISR_TXI);
        
        pbuf_16 = (uint16_t *)huart->TxData;

        for(;;)
        {
            if(huart->TxCount == huart->TxSize) 
            {                               
                huart->TxBusy = false;
         
                /* Disable TX interrupt && error interrupt*/
                CLEAR_BIT(huart->Instance->IE, UART_IE_TXI |
                                               UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI); 

                HAL_UART_TxCpltCallback(huart);
                return;
            }

            if (READ_BIT(huart->Instance->FR, UART_FR_TXFF))
            {
                break;
            }
            
            if (huart->Init.WordLength == UART_WORDLENGTH_9B)
            {
                huart->Instance->DR = (uint16_t)(pbuf_16[huart->TxCount++] & 0x01FFU);
            }
            else
            {
                huart->Instance->DR = huart->TxData[huart->TxCount++];
            }
        }
    }

    /* RXI */
    if (isrflags & UART_ISR_RXI) 
    {
        /* Clear RXI Status */
        CLEAR_STATUS(huart->Instance->ISR, UART_ISR_RXI);
        
        pbuf_16 = (uint16_t *)huart->RxData;
                      
        while(huart->RxCount < huart->RxSize )  
        {
            if(!READ_BIT(huart->Instance->FR, UART_FR_RXFE))
            {
                /* Store Data in buffer */
                if (huart->Init.WordLength == UART_WORDLENGTH_9B)
                {
                    pbuf_16[huart->RxCount++] = (uint16_t)(huart->Instance->DR & 0x1FFU);
                }
                else
                {
                    huart->RxData[huart->RxCount++] = (uint8_t)huart->Instance->DR;	
                }                         
            }  
            else
            {
                break;
            }  
        }
        
        if(huart->RxCount == huart->RxSize )
        {
            huart->RxBusy = false;
        
            /* Disable RX and RTI interrupt && error interrupt*/
            CLEAR_BIT(huart->Instance->IE, (UART_IE_RXI | UART_IE_IDLEI |
                                            UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI));
            
            HAL_UART_RxCpltCallback(huart);
       }
    }
    /* IDLEI */
    else if(isrflags & UART_ISR_IDLEI)  
    {
        /*clear IDLE Status */
        CLEAR_STATUS(huart->Instance->ISR, UART_ISR_IDLEI);
        
        pbuf_16 = (uint16_t *)huart->RxData;

        while(!READ_BIT(huart->Instance->FR, UART_FR_RXFE))
        {
            if (huart->Init.WordLength == UART_WORDLENGTH_9B)
            {
                pbuf_16[huart->RxCount++] = (uint16_t)(huart->Instance->DR & 0x1FFU);
            }
            else
            {                    
                huart->RxData[huart->RxCount++] = (uint8_t)huart->Instance->DR;
            }
        }
        
        huart->RxBusy = false;
        
        /* Disable RX and RTI interrupt && error interrupt*/
        CLEAR_BIT(huart->Instance->IE, (UART_IE_RXI | UART_IE_IDLEI |
                                        UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI));

        

        HAL_UART_IdleCallback(huart);
    }
    
    if(isrflags & UART_ISR_TCI)  
    {
        /*clear IDLE Status */
        CLEAR_STATUS(huart->Instance->ISR, UART_ISR_TCI);
    }
    
	/* if some errors occurred */
	if(errorflags != 0)
	{
		/* UART parity error interrupt occurred */
	    if (((errorflags & UART_ISR_PEI) != 0))
	    {
	    	/* Clear parity error status */
            CLEAR_STATUS(huart->Instance->ISR, UART_ISR_PEI);
	      	huart->ErrorCode |= HAL_UART_ERROR_PE;
	    }

	    /* UART break error interrupt occurred */
	    if (((errorflags & UART_ISR_BEI) != 0))
	    {
            CLEAR_STATUS(huart->Instance->ISR, UART_ISR_BEI);
	      	huart->ErrorCode |= HAL_UART_ERROR_NE;
	    }

	    /* UART frame error interrupt occurred */
	    if (((errorflags & UART_ISR_FEI) != 0))
	    {
            CLEAR_STATUS(huart->Instance->ISR, UART_ISR_FEI);
	      	huart->ErrorCode |= HAL_UART_ERROR_FE;
	    }

	    /* UART Over-Run interrupt occurred */
	    if (((errorflags & UART_ISR_OEI) != 0))
	    {
            CLEAR_STATUS(huart->Instance->ISR, UART_ISR_OEI);
	      	huart->ErrorCode |= HAL_UART_ERROR_ORE;
	    }

        HAL_UART_ErrorCallback(huart);
	}    
}


/******************************************************************************
*@brief : wait Tx FIFO empty
*         
*@param : huart: uart handle with UART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef HAL_UART_Wait_Tx_Done(UART_HandleTypeDef *huart)
{	

    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));
    
	/* wait TX not busy*/
	while(READ_BIT(huart->Instance->FR, UART_FR_BUSY)); 

	return HAL_OK;
}

/******************************************************************************
*@brief : Initialize the UART MSP: CLK, GPIO, NVIC
*         
*@param : huart: uart handle with UART parameters.
*@return: None
******************************************************************************/
__weak void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
}

/******************************************************************************
*@brief : Initialize the UART DE Pin for RS485
*         
*@param : huart: uart handle with UART parameters.
*@return: None
******************************************************************************/
__weak void HAL_UART_RS485Msp_Init(UART_HandleTypeDef *huart)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
}

/******************************************************************************
*@brief : Initialize the UART according to the specified parameters in huart.
*         
*@param : huart: uart handle with UART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)
{
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));
    assert_param (IS_UART_WORDLENGTH(huart->Init.WordLength));
    assert_param (IS_UART_STOPBITS(huart->Init.StopBits));
    assert_param (IS_UART_PARITY(huart->Init.Parity));
    assert_param (IS_UART_MODE(huart->Init.Mode));
    assert_param (IS_UART_HARDWARE_FLOW_CONTROL(huart->Init.HwFlowCtl));

    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_UART_MspInit(huart);
    
    /* Config BaudRate */
    UART_Config_BaudRate(huart);
    
    /* Set the UART Communication parameters */
    huart->Instance->CR3 = huart->Init.WordLength | UART_CR3_FEN | huart->Init.StopBits | huart->Init.Parity;
    huart->Instance->CR1 = huart->Init.HwFlowCtl | huart->Init.Mode;
    
    if (huart->Init.Mode == UART_MODE_HALF_DUPLEX) 
    {
        SET_BIT(huart->Instance->CR2, UART_CR2_HDSEL);
    }
    
    __HAL_UART_ENABLE(huart);
    
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    
	return HAL_OK;
}

/******************************************************************************
*@brief : Initialize the UART RS485 according to the specified parameters in huart.
*         
*@param : huart: uart handle with UART parameters.
*@param : de_polarity: RS485 DE Pin polarity. see @UART_RS485_DE_POL_Enum
*@param : deat_time: the time between the DE Pin activated and data transmiting.
*@param : dedt_time: the time between the last transmiting of data and the DE Pin de-activated.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_RS485_Init(UART_HandleTypeDef *huart, UART_RS485_DE_POL_Enum de_polarity, uint8_t deat_time, uint8_t dedt_time)
{
    assert_param(IS_RS485_INSTANCE(huart->Instance));
    
    if(HAL_UART_Init(huart) == HAL_OK)
    {
        UART_TypeDef *instance = huart->Instance;
        
        /* uart RTS can not be used in RS485DE.
           clear bit UART RTSen */
        CLEAR_BIT(instance->CR1, UART_CR1_RTSEN);
        
        HAL_UART_RS485Msp_Init(huart);
        
        SET_BIT(instance->BCNT, UART_BCNT_DEM);

        /* config DE Pin polarity */
        MODIFY_REG(instance->BCNT, UART_BCNT_DEP, (de_polarity << UART_BCNT_DEP_Pos));
        
        /* config deat time */
        MODIFY_REG(instance->BCNT, UART_BCNT_DEAT, (deat_time << UART_BCNT_DEAT_Pos));
        
        /* config dedt time */
        MODIFY_REG(instance->BCNT, UART_BCNT_DEDT, (dedt_time << UART_BCNT_DEDT_Pos));
    }
    else
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Initialize the UART IRDA Mode according to the specified parameters in huart.
*         
*@param : huart: uart handle with UART parameters.
*@param : is_lowpwr: config IRDA low power mode.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_IRDA_Init(UART_HandleTypeDef *huart, bool is_lowpwr)
{
    assert_param(IS_IRDA_INSTANCE(huart->Instance));
    
    if(HAL_UART_Init(huart) == HAL_OK)
    {
        uint32_t Uart_Clk;
        UART_TypeDef *instance = huart->Instance;
        
        if(instance == USART1)
        {
            Uart_Clk = HAL_RCC_GetPCLK2Freq();
        }
        else
        {
            Uart_Clk = HAL_RCC_GetPCLK1Freq();
        }
        
        SET_BIT(instance->CR1, UART_CR1_SIREN);
        
        if(is_lowpwr)
        {
            SET_BIT(instance->CR1, UART_CR1_SIRLP);
            instance->GTPR = (uint8_t)(Uart_Clk / (115200 * 16));
        }
        else
        {
            CLEAR_BIT(instance->CR1, UART_CR1_SIRLP);
        }
    }
    else
    {
        return HAL_ERROR;
    }
    
    return HAL_OK;
}


/******************************************************************************
*@brief : Initialize the Multi-UART Communication Mode 
*                   according to the specified parameters in huart.
*         
*@param : huart: uart handle with UART parameters.
*@param : addr: uart address
*@param : wakeupMode: UART waked up by idle line or address mark, 
*         see @UART_WakeupMode_Enum for more information
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t addr, UART_WakeupMode_Enum wakeupMode)
{
    if(HAL_UART_Init(huart) == HAL_OK)
    {
        /* config uart addr mode & addr */
        if(IS_UART_7BIT_ADDR_MODE(addr))
        {
            SET_BIT(huart->Instance->CR2, UART_CR2_ADDM7);
        }
        else
        {
            CLEAR_BIT(huart->Instance->CR2, UART_CR2_ADDM7);
        }
        MODIFY_REG(huart->Instance->CR2, UART_CR2_ADDR, (addr << UART_CR2_ADDR_Pos));

        /* config uart wakeup mode */
        MODIFY_REG(huart->Instance->CR2, UART_CR2_WAKE, (wakeupMode << UART_CR2_WAKE_Pos));
    }
    else
    {
        return HAL_ERROR;
    }

  __HAL_UART_ENABLE(huart);

  return HAL_OK;
}

/******************************************************************************
*@brief : DeInitialize the UART MSP
*         
*@param : huart: uart handle with UART parameters.
*@return: None
******************************************************************************/
__weak void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
}

/******************************************************************************
*@brief : DeInitialize the UART module
*         
*@param : huart: uart handle with UART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart)
{

    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));

    /* DeInit the low level hardware : GPIO, CLOCK, NVIC */
    HAL_UART_MspDeInit(huart);

	return HAL_OK;
    
}

/******************************************************************************
*@brief : Send an amount of data by loop mode within timeout period.
*         
*@param : huart: uart handle with UART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to be sent.
*@param : timeout: Timeout duration, unit MS, 1(ms)~~0xFFFFFFFF(wait forever)
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size, uint32_t timeout)
{
    uint16_t *pbuf_16;
    uint32_t Start_Tick;
    
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));
    
    if ((buf == NULL) || (size == 0U))
    {
      return HAL_ERROR;
    }
    
    huart->TxCount = 0;
    huart->TxData = buf;
    pbuf_16 = (uint16_t *)huart->TxData;
    
    SET_BIT(huart->Instance->CR1, UART_CR1_TXE);
    
    if (huart->Init.Mode == UART_MODE_HALF_DUPLEX) 
    {
        /* disable RX in half-duplex mode */
        CLEAR_BIT(huart->Instance->CR1, UART_CR1_RXE);
    }
    
    Start_Tick = HAL_GetTick();
    
    while (size--) 
    {
        if (huart->Init.WordLength == UART_WORDLENGTH_9B)
        {
            huart->Instance->DR = (uint16_t)(pbuf_16[huart->TxCount++] & 0x01FFU);
        }
        else
        {
            huart->Instance->DR = huart->TxData[huart->TxCount++];
        }      
        while (huart->Instance->FR & UART_FR_TXFF)
        {
            if ((HAL_GetTick() - Start_Tick) > timeout) 
            {
                return HAL_TIMEOUT;
            }
        }
    }
    
    HAL_UART_Wait_Tx_Done(huart); 

    if (huart->Init.Mode == UART_MODE_HALF_DUPLEX) 
    {
        SET_BIT(huart->Instance->CR1, UART_CR1_RXE);
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data by loop mode within timeout period.
*         
*@param : huart: uart handle with UART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to receive.
*@param : timeout: Timeout duration, unit MS, 1(ms)~~0xFFFFFFFF(wait forever)
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size, uint32_t timeout)
{
    uint16_t *pbuf_16;
    uint32_t Start_Tick;
    
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));
    
    if ((buf == NULL) || (size == 0U))
    {
      return HAL_ERROR;
    }

    huart->RxCount = 0;
    huart->RxData = buf;
    pbuf_16 = (uint16_t *)huart->RxData;
    
    /* In case RXE is disabled in transmit funtion */
    SET_BIT(huart->Instance->CR1, UART_CR1_RXE);
    
    Start_Tick = HAL_GetTick();

    while (size--) 
    {
        while(huart->Instance->FR & UART_FR_RXFE)
        {
            if ((HAL_GetTick() - Start_Tick) > timeout)  
            {
                return HAL_TIMEOUT;
            }
        }

        /* Store Data in buffer */
        if (huart->Init.WordLength == UART_WORDLENGTH_9B)
        {
            pbuf_16[huart->RxCount++] = (uint16_t)(huart->Instance->DR & 0x1FFU);
        }
        else
        {
            huart->RxData[huart->RxCount++] = (uint8_t)huart->Instance->DR;	
        }      
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data to Idle line or  BCNT time.
*         
*@param : huart: uart handle with UART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to receive.
*@param : rece_mode: by idle line, or by bit value count reached
*@param : timeout: BCNT value(relative to UART baudrate), when UART BaudRate = 115200, 
                    then set timeout = 115200,it is approximately 1 second. MAX BCNT value can be 0xFFFFFF.
*                   Only used when 'rece_mode' = RECEIVE_TOBCNT
*                             when 'rece_mode' = RECEIVE_TOIDLE, it is meaningless.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_Receive_To_IDLEorBCNT(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size, 
                                                UART_Receive_Mode_Enum rece_mode, uint32_t timeout)
{
    uint16_t *pbuf_16;
//    uint32_t Start_Tick;
    
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));
    
    if ((buf == NULL) || (size == 0U))
    {
      return HAL_ERROR;
    }

    huart->RxCount = 0;
    huart->RxData = buf;
    pbuf_16 = (uint16_t *)huart->RxData;
  
    /* In case RXE is disabled in transmit funtion */
    SET_BIT(huart->Instance->CR1, UART_CR1_RXE);
    
    CLEAR_STATUS(huart->Instance->ISR, UART_ISR_IDLEI | UART_ISR_BCNTI);
    
    if(rece_mode == RECEIVE_TOBCNT)
    {
        MODIFY_REG(huart->Instance->BCNT, UART_BCNT_BCNTVALUE, timeout);
        SET_BIT(huart->Instance->BCNT, UART_BCNT_AUTO_START_EN);
    }

    while (size--) 
    {
        while(huart->Instance->FR & UART_FR_RXFE)
        {
            if(rece_mode == RECEIVE_TOBCNT)
            {    
                if(READ_BIT(huart->Instance->ISR, UART_ISR_BCNTI))
                {
                    CLEAR_BIT(huart->Instance->BCNT, UART_BCNT_AUTO_START_EN);
                    CLEAR_STATUS(huart->Instance->ISR, UART_ISR_BCNTI);
                    return HAL_TIMEOUT;
                }
            }
            else
            {
                if(READ_BIT(huart->Instance->ISR, UART_ISR_IDLEI))
                {
                    CLEAR_STATUS(huart->Instance->ISR, UART_ISR_IDLEI);
                    while(READ_BIT(huart->Instance->ISR, UART_ISR_IDLEI))
                    {
                        CLEAR_STATUS(huart->Instance->ISR, 0);
                        CLEAR_STATUS(huart->Instance->ISR, UART_ISR_IDLEI);
                    }
                    return HAL_TIMEOUT;
                }
            }
        }

        /* Store Data in buffer */
        if (huart->Init.WordLength == UART_WORDLENGTH_9B)
        {
            pbuf_16[huart->RxCount++] = (uint16_t)(huart->Instance->DR & 0x1FFU);
        }
        else
        {
            huart->RxData[huart->RxCount++] = (uint8_t)huart->Instance->DR;	
        }
    }
    
    CLEAR_BIT(huart->Instance->BCNT, UART_BCNT_AUTO_START_EN);
    return HAL_OK;
}

/******************************************************************************
*@brief : Send an amount of data in interrupt mode.
*         
*@param : huart: uart handle with UART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to send.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size)
{
    uint16_t *pbuf_16;
    
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));
    
    if (huart->TxBusy == true) 
    {
        return HAL_BUSY;
    }
    
    if (size == 0 || buf == NULL) 
    {
        return HAL_ERROR;
    }
    
    huart->TxSize  = size;
    huart->TxCount = 0;
    huart->TxData   = buf;
    huart->TxBusy   = true;
    pbuf_16 = (uint16_t *)huart->TxData;
    
    SET_BIT(huart->Instance->CR1, UART_CR1_TXE);
    
    if (huart->Init.Mode == UART_MODE_HALF_DUPLEX) 
    {
        /* disable RX in half-duplex mode */
        CLEAR_BIT(huart->Instance->CR1, UART_CR1_RXE);
    }

    /* Clear TXI Status */
    CLEAR_STATUS(huart->Instance->ISR, UART_ISR_TXI);
    /* FIFO Enable */
    SET_BIT(huart->Instance->CR3, UART_CR3_FEN);
	/*FIFO Select*/
    __HAL_UART_TXI_FIFO_LEVEL_SET(huart->Instance, UART_TX_FIFO_1_2);
    
    for(;;) 
    {	
        /*Data Size less than 16Byte */
	    if(size == huart->TxCount) 
	    {
	        huart->TxBusy = false;
			
			while ((huart->Instance->FR & UART_FR_BUSY)){}
			
            HAL_UART_TxCpltCallback(huart);
			
	        return HAL_OK;  
	    }
	    if(READ_BIT(huart->Instance->FR, UART_FR_TXFF)) 
	    {				
	         break;
	    }

        if (huart->Init.WordLength == UART_WORDLENGTH_9B)
        {
            huart->Instance->DR = (uint16_t)(pbuf_16[huart->TxCount++] & 0x01FFU);
        }
        else
        {
            huart->Instance->DR = huart->TxData[huart->TxCount++];
        }       
    }
	
    /* Enable TX interrupt */
    SET_BIT(huart->Instance->IE, UART_IE_TXI);

    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data in interrupt mode.
*         
*@param : huart: uart handle with UART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to receive.
*@return: HAL_StatusTypeDef
*@note  : HAL_UART_Receive_IT() function will stop receiving data when:
          1. Total amount of data have been received.
          2. Idle line occured.(You can use __HAL_UART_Resume_Receive_IT(__HANDLE__) Macro 
             in HAL_UART_IdleCallback() fucntion in user code to resume receving data 
             if you still want to recive all the size of data)

          There will be already datas in UART FIFO before call this function. 
          use __HAL_UART_FIFO_FLUSH(__HANDLE__) macro before calling HAL_UART_Receive_IT() 
          to flush FIFO if the data is useless.
******************************************************************************/
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size)
{
    uint16_t *pbuf_16;
    
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));
    
    if (huart->RxBusy == true) 
    {
        return HAL_BUSY;
    }

    if (size == 0 || buf == NULL) 
    {
        return HAL_ERROR;
    }
    
    huart->RxSize  = size;
    huart->RxCount = 0;
    huart->RxData  = buf;
    huart->RxBusy  = true;
    pbuf_16 = (uint16_t *)huart->RxData;
    
    SET_BIT(huart->Instance->CR1, UART_CR1_RXE);
    
    /* FIFO Enable */
    SET_BIT(huart->Instance->CR3, UART_CR3_FEN);
	/*FIFO Select*/
    __HAL_UART_RXI_FIFO_LEVEL_SET(huart->Instance, UART_RX_FIFO_1_4);
    
    /* Clear RXI && IDLEI Status */
    CLEAR_STATUS(huart->Instance->ISR, UART_ISR_RXI | UART_ISR_IDLEI);
    CLEAR_STATUS(huart->Instance->ISR, UART_ISR_PEI | UART_ISR_BEI | UART_ISR_OEI | UART_ISR_FEI);

    /* In case there are datas(which exceeded the FIFO LEVEL of triggering RXI ISR) already in UART FIFO before enabling RXI IE */
    while (size--) 
    {
        if(huart->Instance->FR & UART_FR_RXFE)
        {
            goto start_recv_it;
        }  
        if (huart->Init.WordLength == UART_WORDLENGTH_9B)
        {
            pbuf_16[huart->RxCount++] = (uint16_t)(huart->Instance->DR & 0x1FFU);
        }
        else
        {
            huart->RxData[huart->RxCount++] = (uint8_t)huart->Instance->DR;	
        }     
    }
    
    /* have been received all the size of data */
    HAL_UART_RxCpltCallback(huart);
    return HAL_OK;   
    
start_recv_it:    
	/* Enable the UART Errors interrupt */
	SET_BIT(huart->Instance->IE, UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI);
    /* Enable RX and RTI interrupt */
    SET_BIT(huart->Instance->IE, UART_IE_RXI | UART_IE_IDLEI); 
    
    return HAL_OK;
}

#ifdef HAL_DMA_MODULE_ENABLED
/******************************************************************************
*@brief : Send an amount of data in DMA mode.
*         
*@param : huart: uart handle with UART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to send.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size)
{
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));

    if (huart->TxBusy == true) 
    {
        return HAL_BUSY;
    }

    if (size == 0 || buf == NULL) 
    {
        return HAL_ERROR;
    }
    
    huart->TxSize = size;
    huart->TxCount = 0;
    huart->TxData = buf;
    huart->TxBusy = true;
    
    SET_BIT(huart->Instance->CR1, UART_CR1_TXE);
    
    if (huart->Init.Mode == UART_MODE_HALF_DUPLEX) 
    {
        /* disable RX in half-duplex mode */
        CLEAR_BIT(huart->Instance->CR1, UART_CR1_RXE);
    }

    SET_BIT(huart->Instance->CR1, UART_CR1_TXDMAE);

    __HAL_UART_TXI_FIFO_LEVEL_SET(huart->Instance, UART_TX_FIFO_1_16);

    if (HAL_DMA_Start_IT(huart->HDMA_Tx, (uint32_t)buf, (uint32_t)(&huart->Instance->DR), size))
    {
        CLEAR_BIT(huart->Instance->CR1, UART_CR1_TXDMAE);
        return HAL_ERROR;
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data in DMA mode.
*         
*@param : huart: uart handle with UART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to receive.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size)
{
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));

    if (huart->RxBusy == true) 
    {
        return HAL_BUSY;
    }

    if (size == 0 || buf == NULL) 
    {
        return HAL_ERROR;
    }
    
    huart->RxSize  = size;
    huart->RxCount = 0;
    huart->RxData  = buf;
    huart->RxBusy  = true;
    
    /* In case RXE is disabled in transmit funtion */
    SET_BIT(huart->Instance->CR1, UART_CR1_RXE);

    CLEAR_STATUS(huart->Instance->ISR, UART_ISR_IDLEI);
    
    SET_BIT(huart->Instance->CR1, UART_CR1_RXDMAE);
    
    __HAL_UART_RXI_FIFO_LEVEL_SET(huart->Instance, UART_RX_FIFO_1_16);
    
    SET_BIT(huart->Instance->IE, UART_IE_IDLEI); 
    
    /* Enable the UART Errors interrupt */
	SET_BIT(huart->Instance->IE, UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI);

    if (HAL_DMA_Start_IT(huart->HDMA_Rx, (uint32_t)(&huart->Instance->DR), (uint32_t)buf, size))
    {
        CLEAR_BIT(huart->Instance->CR1, UART_CR1_RXDMAE);
        CLEAR_BIT(huart->Instance->IE, UART_IE_IDLEI | UART_IE_OEI | UART_IE_BEI | UART_IE_PEI | UART_IE_FEI);
        return HAL_ERROR;
    }

    return HAL_OK;
}
#endif

/******************************************************************************
*@brief : Tx Transfer completed callbacks.
*         
*@param : huart: uart handle with UART parameters.
*@return: None
******************************************************************************/
__weak void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_UART_TxCpltCallback could be implemented in the user file.
    */
}

/******************************************************************************
*@brief : Rx Transfer completed callbacks.
*         
*@param : huart: uart handle with UART parameters.
*@return: None
******************************************************************************/
__weak void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_UART_RxCpltCallback could be implemented in the user file.
    */
}

/******************************************************************************
*@brief : Rx Transfer idleline callbacks.
*         
*@param : huart: uart handle with UART parameters.
*@return: None
******************************************************************************/
__weak void HAL_UART_IdleCallback(UART_HandleTypeDef *huart)
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_UART_RxCpltCallback could be implemented in the user file.
    */
}

/******************************************************************************
*@brief : Recv Error callbacks.
*         
*@param : huart: uart handle with UART parameters.
*@return: None
******************************************************************************/
__weak void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    /* 
      NOTE: This function Should be modified, when the callback is needed,
      the HAL_UART_ErrorCallback could be implemented in the user file.
    */
}

/******************************************************************************
*@brief : Config UART BaudRate
*         
*@param : huart: uart handle with UART parameters.
*@return: None
******************************************************************************/
static void UART_Config_BaudRate(UART_HandleTypeDef *huart)
{
    uint32_t pclk;
    uint32_t ibaud, fbaud;
    uint64_t tmp; 
    
    if (USART1 == huart->Instance) 
    {
        pclk = HAL_RCC_GetPCLK2Freq(); 
    }
    else
    {
        pclk = HAL_RCC_GetPCLK1Freq();  
    } 

    /* Integral part */
    ibaud = pclk / (huart->Init.BaudRate * 16);

    /* Fractional part */
    tmp = pclk % (huart->Init.BaudRate * 16);
    tmp = (tmp * 1000000) / (huart->Init.BaudRate * 16);
    fbaud     = (tmp * 64 + 500000) / 1000000;

    if (fbaud >= 64) 
    {
        MODIFY_REG(huart->Instance->BRR, UART_BRR_IBAUD_Msk, ((ibaud + 1) << UART_BRR_IBAUD_Pos));
        MODIFY_REG(huart->Instance->BRR, UART_BRR_FBAUD_Msk, (0 << UART_BRR_FBAUD_Pos));
    }
    else 
    {
        MODIFY_REG(huart->Instance->BRR, UART_BRR_IBAUD_Msk, (ibaud << UART_BRR_IBAUD_Pos));
        MODIFY_REG(huart->Instance->BRR, UART_BRR_FBAUD_Msk, (fbaud << UART_BRR_FBAUD_Pos));
    }
}

/******************************************************************************
*@brief : Return the uart State
*         
*@param : huart: uart handle with UART parameters.
*@return: HAL_BUSY or HAL_OK
******************************************************************************/
HAL_StatusTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart)
{
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));

	if(huart->TxBusy || huart->RxBusy)
	{
		return HAL_BUSY;		
	}

	return HAL_OK;
}

/******************************************************************************
*@brief : Return the uart Error
*         
*@param : huart: uart handle with UART parameters.
*@return: uart errcode
******************************************************************************/
uint32_t HAL_UART_GetError(UART_HandleTypeDef *huart)
{
  	return huart->ErrorCode;
}

#ifdef HAL_DMA_MODULE_ENABLED
/******************************************************************************
*@brief : Abort ongoing transfers(blocking mode)
*         
*@param : huart: uart handle with UART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart)
{
	assert_param (IS_UART_ALL_INSTANCE(huart->Instance));

	/*disble all interrupt*/
	huart->Instance->IE  =0x00;

	/* Disable the UART DMA Tx request if enable */
	if(READ_BIT(huart->Instance->CR1, UART_CR1_TXDMAE))
	{
		CLEAR_BIT(huart->Instance->CR1, UART_CR1_TXDMAE);

		/* Abort the UART Tx Channel   */
		if(huart->HDMA_Tx)
		{
			/*Set the UART DMA Abort callback to Null */
			huart->HDMA_Tx->XferCpltCallback =NULL;

			if(HAL_DMA_Abort(huart->HDMA_Tx)!=HAL_OK)
			{
				return HAL_TIMEOUT;
			}
		}
	}

	/* Disable the UART DMA Rx request if enable */
	if(READ_BIT(huart->Instance->CR1, UART_CR1_RXDMAE))
	{
		CLEAR_BIT(huart->Instance->CR1, UART_CR1_RXDMAE);
		
		/* Abort the UART Rx Channel   */
		if(huart->HDMA_Rx)
		{
			/*Set the UART DMA Abort callback to Null */
			huart->HDMA_Rx->XferCpltCallback =NULL;

			if(HAL_DMA_Abort(huart->HDMA_Rx)!=HAL_OK)
			{
				return HAL_TIMEOUT;
			}
		}
	}

	/*Reset Tx and Rx Transfer size*/
	huart->TxSize = 0;
	huart->RxSize = 0;

	/* Restore huart->TxBusy and huart->RxBusy to Ready */
	huart->TxBusy = false;
	huart->RxBusy = false;
		
	return HAL_OK;
}

/******************************************************************************
*@brief : Pause the UART DMA Transfer
*         
*@param : huart: uart handle with UART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart)
{
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));

    if(READ_BIT(huart->Instance->CR1, UART_CR1_TXDMAE))
    {
        /* Disable the UART DMA Tx request */
        CLEAR_BIT(huart->Instance->CR1, UART_CR1_TXDMAE);
    }

    if (READ_BIT(huart->Instance->CR1, UART_CR1_RXDMAE))
    {
        /* Disable RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts */
        CLEAR_BIT(huart->Instance->IE, UART_IE_OEI | UART_IE_PEI | UART_IE_BEI | UART_IE_FEI);

        /* Disable the UART DMA Rx request */
        CLEAR_BIT(huart->Instance->CR1, UART_CR1_RXDMAE);
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Resume the UART DMA Transfer
*         
*@param : huart: uart handle with UART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart)
{
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));

    if (huart->TxBusy == false)
    {
        /* Enable the UART DMA Tx request */
        SET_BIT(huart->Instance->CR1, UART_CR1_TXDMAE);
    }

    if (huart->RxBusy == false)
    {
        /* Reenable PE and ERR (Frame error, noise error, overrun error) interrupts */
        SET_BIT(huart->Instance->IE, UART_IE_OEI | UART_IE_PEI | UART_IE_BEI | UART_IE_FEI);

        /* Enable the UART DMA Rx request */
        SET_BIT(huart->Instance->CR1, UART_CR1_RXDMAE);
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Stop the UART DMA Transfer
*         
*@param : huart: uart handle with UART parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart)
{
    assert_param (IS_UART_ALL_INSTANCE(huart->Instance));
    
    if(huart->Instance->CR1 & UART_CR1_TXDMAE)
    {
        CLEAR_BIT(huart->Instance->CR1, UART_CR1_TXDMAE);
        if(huart->HDMA_Tx != NULL)
        {
            HAL_DMA_Abort(huart->HDMA_Tx);
        }
        
        CLEAR_BIT(huart->Instance->IE, (UART_IE_TXI));
    }
    
    if(huart->Instance->CR1 & UART_CR1_RXDMAE)
    {
        CLEAR_BIT(huart->Instance->CR1, UART_CR1_RXDMAE);
        if(huart->HDMA_Rx != NULL)
        {
            HAL_DMA_Abort(huart->HDMA_Rx);
        }

        CLEAR_BIT(huart->Instance->IE, (UART_IE_RXI | UART_IE_PEI));

        CLEAR_BIT(huart->Instance->IE, UART_IE_IDLEI);
    }

  return HAL_OK;
}
#endif

/******************************************************************************
*@brief : uart module enter into mute mode
*         
*@param : huart: uart handle with UART parameters.
*@return: HAL_OK
******************************************************************************/
HAL_StatusTypeDef HAL_UART_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart)
{
    SET_BIT(huart->Instance->CR2, UART_CR2_RWU);
    return HAL_OK;
}

/******************************************************************************
*@brief : uart module exit from mute mode
*         
*@param : huart: uart handle with UART parameters.
*@return: HAL_OK
******************************************************************************/
HAL_StatusTypeDef HAL_UART_MultiProcessor_ExitMuteMode(UART_HandleTypeDef *huart)
{
    CLEAR_BIT(huart->Instance->CR2, UART_CR2_RWU);
    return HAL_OK;
}

/******************************************************************************
*@brief : which uart instance is selected for debug using
*         
*@param : UARTx: UART instance.
*@return: None
******************************************************************************/
void HAL_UART_SetDebugUart(UART_TypeDef *UARTx)
{
    if(UARTx != NULL)
    {
        assert_param (IS_UART_ALL_INSTANCE(UARTx));
    }
    g_DebugUart = UARTx;
}
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))

/******************************************************************************
*@brief : re-direct fputc to uart port
*         
*@param : ch:  character to send
*@param : f: a pointer to FILE struct, no use in uart re-directing
*@return: character sent
******************************************************************************/
__weak int fputc(int ch, FILE *f)
{
    if(g_DebugUart)
    {
        g_DebugUart->DR = ch;    
        while ((g_DebugUart->FR & UART_FR_BUSY));        
    }
    return ch;
}
#elif defined (__GNUC__) 

__weak int __io_putchar(int ch)  
{  
    g_DebugUart->DR = ch; 
    while ((g_DebugUart->FR & UART_FR_BUSY));  
    return ch;  
}   

#endif
#endif //HAL_UART_MODULE_ENABLED

