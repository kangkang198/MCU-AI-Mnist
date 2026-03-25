/******************************************************************************
*@file  : hal_spi.c
*@brief : This file provides firmware functions to manage the SPI HAL module
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/
#include  "hal_spi.h" 

#ifdef HAL_SPI_MODULE_ENABLED

/******************************************************************************
*@brief : SPI interrupt handler
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@return: None
*@note  : Execute HAL_SPI_IRQHandler funcion in SRAM may speed up the TXFIFO/RXFIFO operation
******************************************************************************/
__weak void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi) 
{  
    if ( (hspi->Instance->STATUS & SPI_STATUS_RX_FIFO_NOT_EMPTY) && ((hspi->Instance->IE) & SPI_IE_RX_FIFO_NOT_EMPTY_EN) )
    {
        do{
            if (hspi->Rx_Count < hspi->Rx_Size) 
            {
                hspi->Rx_Buffer[hspi->Rx_Count++] = hspi->Instance->DAT;
            }
            else break;
        }while (hspi->Instance->STATUS & SPI_STATUS_RX_FIFO_NOT_EMPTY);
    }

    if ( (hspi->Instance->STATUS & SPI_STATUS_TX_FIFO_HALF_EMPTY) && ((hspi->Instance->IE) & SPI_IE_TX_FIFO_HALF_EMPTY_EN) )
    {
        while (!(hspi->Instance->STATUS & SPI_STATUS_TX_FIFO_FULL))
        {
            if(hspi->Tx_Count < hspi->Tx_Size) 
            {
                hspi->Instance->DAT = hspi->Tx_Buffer[hspi->Tx_Count++];
            }
            else 
            {
                /* Disable TxFIFO half empty interrupt */
                CLEAR_BIT(hspi->Instance->IE, SPI_IE_TX_FIFO_HALF_EMPTY_EN);
                break;
            }
        }               
    }
    
    if ((hspi->Instance->STATUS & SPI_STATUS_TX_BATCH_DONE) && ((hspi->Instance->IE) & SPI_IE_TX_BATCH_DONE_EN) )     
    {
        /* Clear Batch Done Flag  */
        __SPI_CLEAR_FLAG(hspi->Instance, SPI_STATUS_TX_BATCH_DONE);

        /* Disable TX Batch Done Interrupt, Tx FIFO half empty Interrupt */
        CLEAR_BIT(hspi->Instance->IE, SPI_IE_TX_BATCH_DONE_EN | SPI_IE_TX_FIFO_HALF_EMPTY_EN);        

        if ( (hspi->Init.SPI_Mode == SPI_MODE_MASTER) && (hspi->KeepCS == false) )
        {
            /* CS de-active */
            __HAL_SPI_CS_RELEASE(hspi);
        }
        
        /* Tx Disable */
        CLEAR_BIT(hspi->Instance->TX_CTL, SPI_TX_CTL_EN);
        CLEAR_BIT(hspi->Instance->TX_CTL, SPI_TX_CTL_DMA_REQ_EN);

        hspi->TxState = SPI_TX_STATE_IDLE;
    }

    if ( (hspi->Instance->STATUS & SPI_STATUS_RX_BATCH_DONE) && ((hspi->Instance->IE) & SPI_STATUS_RX_BATCH_DONE) )         
    {
        /* Clear Batch Done Flag  */
        __SPI_CLEAR_FLAG(hspi->Instance, SPI_STATUS_RX_BATCH_DONE);

        /* Disable RX Batch Done Interrupt, RXFIFO not Empty interrupt */
        CLEAR_BIT(hspi->Instance->IE, SPI_IE_RX_BATCH_DONE_EN | SPI_IE_RX_FIFO_NOT_EMPTY_EN);

        while (hspi->Instance->STATUS & SPI_STATUS_RX_FIFO_NOT_EMPTY)
        {
            if (hspi->Rx_Count < hspi->Rx_Size) 
            {
                hspi->Rx_Buffer[hspi->Rx_Count++] = hspi->Instance->DAT;
            }
            else break;
        }
        /////////////
        
        if ( (hspi->Init.SPI_Mode == SPI_MODE_MASTER) && (hspi->KeepCS == false) )
        {
            /* CS de-active */
            __HAL_SPI_CS_RELEASE(hspi);
        }
        
        /* Rx Disable */
        CLEAR_BIT(hspi->Instance->RX_CTL, SPI_RX_CTL_DMA_REQ_EN);
        CLEAR_BIT(hspi->Instance->RX_CTL, SPI_RX_CTL_EN);
        
        hspi->RxState = SPI_RX_STATE_IDLE;
    }
}

/******************************************************************************
*@brief : Init low level of SPI module: GPIO, CLK, NVIC
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@return: None
******************************************************************************/
__weak void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hspi);
}

/******************************************************************************
*@brief : SPI De-Initialize the SPI clock, GPIO, IRQ.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@return: None
******************************************************************************/
__weak void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hspi);
}

/******************************************************************************
*@brief : Initialize the SPI module with parameters
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
{
    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(hspi->Instance));
    assert_param (IS_SPI_ALL_MODE(hspi->Init.SPI_Mode));
    assert_param (IS_SPI_WORK_MODE(hspi->Init.SPI_Work_Mode));
    assert_param (IS_SPI_X_MODE(hspi->Init.X_Mode));
    assert_param (IS_SPI_FIRST_BIT(hspi->Init.First_Bit));
    
    if(hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        assert_param (IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRate_Prescaler));
    }
    else
    {
        assert_param (IS_SPI_INSTANCE_SLAVE_MODE(hspi->Instance));
    }
    
    if(hspi->Init.X_Mode == SPI_4X_MODE)
    {
        assert_param (IS_SPI_INSTANCE_4X_MODE(hspi->Instance));
    }

    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_SPI_MspInit(hspi);
    
    /* Automatic change direction */
    hspi->Instance->CTL |= (SPI_CTL_IO_MODE);
    
    /* Set SPI Work mode */
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        SET_BIT(hspi->Instance->CTL, SPI_CTL_MST_MODE);
        MODIFY_REG(hspi->Instance->RX_CTL, SPI_RX_CTL_SSHIFT_Msk, hspi->Init.Master_SShift);
        
        assert_param(IS_SPI_CS_SEL(hspi->CSx));
        
        if((hspi->CSx ==  SPI_CS_CS1) || (hspi->CSx ==  SPI_CS_CS2))
        {
            //SET_BIT(hspi->Instance->CS, SPI_CSMAP_EN);
            
            hspi->Instance->CS = SPI_CSMAP_EN;
        }
        else
        {
            //CLEAR_BIT(hspi->Instance->CS, SPI_CSMAP_EN);
            
            hspi->Instance->CS = 0;
        }
    }
    else 
    {
        CLEAR_BIT(hspi->Instance->CTL, SPI_CTL_MST_MODE);
        
        if(hspi->Init.Slave_SofteCs_En == SPI_SLAVE_SOFT_CS_ENABLE)
        {
            SET_BIT(hspi->Instance->CTL, SPI_CTL_SWCS_EN);
            SET_BIT(hspi->Instance->CTL, SPI_CTL_SWCS);   //Soft CS set to HIGH.
        }
        else
            CLEAR_BIT(hspi->Instance->CTL, SPI_CTL_SWCS_EN);
        
        hspi->Instance->BATCH = (hspi->Instance->BATCH & (~0x000FFFFFU)) | (1 << 0);
        
        hspi->Instance->TX_CTL |= SPI_TX_CTL_MODE | (0x88 << 8);  // dummy data = 0x88  
        
        //if (hspi->Init.X_Mode != SPI_1X_MODE) 
        {
            hspi->Instance->CTL |= SPI_CTL_SFILTER | SPI_CTL_CS_FILTER;
        }
        
        /* Slave Alternate Enable */
        hspi->Instance->CTL |= SPI_CTL_SLAVE_EN;
        
        /* Slave Mode Enable Rx By Default */
        hspi->Instance->RX_CTL |= SPI_RX_CTL_EN;
    }

    /* Set SPI First Bit */
    if (hspi->Init.First_Bit == SPI_FIRSTBIT_LSB)
        SET_BIT(hspi->Instance->CTL, SPI_CTL_LSB_FIRST);
    else
        CLEAR_BIT(hspi->Instance->CTL, SPI_CTL_LSB_FIRST);

    /* Set SPI Work Mode */
    hspi->Instance->CTL = ((hspi->Instance->CTL) & (~(SPI_CTL_CPHA | SPI_CTL_CPOL))) | (hspi->Init.SPI_Work_Mode);
    
    /* Set SPI X_Mode */
    hspi->Instance->CTL = ((hspi->Instance->CTL) & (~SPI_CTL_X_MODE)) | (hspi->Init.X_Mode);

    /* Set SPI BaudRate Prescaler */
    hspi->Instance->BAUD = ((hspi->Instance->BAUD) & (~0x0000FFFF)) | (hspi->Init.BaudRate_Prescaler);

    /* Disable All Interrupt */
    hspi->Instance->IE = 0x00000000;
    
    assert_param(hspi->Instance->STATUS != 0);

    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_MEMACCInit(SPI_HandleTypeDef* hspi, SPI_MemACCInitTypeDef* MemACCParam)
{
    SPI_TypeDef* SPIx;
    assert_param (IS_SPI_MEM_INSTANCE(hspi->Instance));    
    assert_param (hspi->Init.SPI_Mode == SPI_MODE_MASTER);
    
    SPIx = hspi->Instance;
    
    SPIx->ALTER_BYTE    = MemACCParam->MemAlterByte;
    SPIx->CMD           = MemACCParam->MemCMD;
    SPIx->MEMO_ACC      = MemACCParam->MemACC;
    SPIx->CS_TOUT_VAL   = MemACCParam->MemCSTimeout;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : e-Initialize the SPI peripheral
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi)
{
    /* Check the SPI handle allocation */
    if (hspi == NULL)
    {
        return HAL_ERROR;
    }

    /* Check SPI Instance parameter */
    assert_param (IS_SPI_ALL_INSTANCE(hspi->Instance));

    hspi->RxState = SPI_RX_STATE_IDLE;
    hspi->TxState = SPI_TX_STATE_IDLE;

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
    HAL_SPI_MspDeInit(hspi);

    hspi->Rx_Size = 0;
    hspi->Tx_Size = 0;
    hspi->Rx_Count = 0;
    hspi->Tx_Count = 0;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Switch_CS(SPI_HandleTypeDef *hspi, uint8_t CSx)
{
    assert_param(IS_SPI_CS_SEL(CSx));
    
    hspi->CSx = CSx;
        
    if((hspi->CSx ==  SPI_CS_CS1) || (hspi->CSx ==  SPI_CS_CS2))
    {
        SET_BIT(hspi->Instance->CS, SPI_CSMAP_EN);
    }
    else
    {
        CLEAR_BIT(hspi->Instance->CS, SPI_CSMAP_EN);
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Transmits an amount of data by loop mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to be sent
*@param : Timeout : Transmit Timeout
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef _HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i;
    uint32_t send_cnt = 0;
    uint32_t recv_cnt = 0;
    __IO uint32_t uiTimeout;    
    HAL_StatusTypeDef Status = HAL_OK;    
    SPI_TypeDef* SPIx = hspi->Instance;

    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(SPIx));
    
    if(!Size)    return HAL_ERROR;
    if (pData == NULL)    return HAL_ERROR;
    
    hspi->Tx_Count = 0;
    hspi->Tx_Size = Size;
    hspi->Tx_Buffer = pData;
    
    uiTimeout = Timeout;

    /* Clear Batch Done Flag  */    
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);
    
    /* Tx Enable */
    hspi->Instance->TX_CTL |= SPI_TX_CTL_EN;
    /* Rx Disable */
    hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);
    
    /* Clear TX FIFO */
    __SPI_TXFIFO_RESET(SPIx);
    
    /* Set Data Size */
    SPIx->BATCH = Size;
    
    while((!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL)) && (Size > send_cnt))
    {
        SPIx->DAT = pData[send_cnt++];
    }

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {          
        /* Transmit Start */
        __HAL_SPI_TRANSSTART_CS_LOW(hspi);
    }
        
    while(Size > send_cnt)
    {
        /* Wait Tx FIFO Not Full */
        if(!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL))
        {
            SPIx->DAT = pData[send_cnt++];
            uiTimeout = Timeout;
        }
        else
        {
            /* Wait Timeout */
            if(uiTimeout)
            {
                uiTimeout--;
                if(uiTimeout == 0)
                {
                    Status = HAL_TIMEOUT;
                    goto End;
                }
            }
        }            
    }
    
    /* Wait Transmit Done */
    while (!(SPIx->STATUS & SPI_STATUS_TX_BATCH_DONE));
    
End:
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);    
    
    /* Tx Disable */
    CLEAR_BIT(hspi->Instance->TX_CTL, SPI_TX_CTL_EN);
    
    hspi->Tx_Count = send_cnt;

    return Status;
}

/******************************************************************************
*@brief : Transmits an amount of data by loop mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to be sent
*@param : Timeout : Transmit Timeout
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef Status;
    
    Status = _HAL_SPI_Transmit(hspi, pData, Size, Timeout);
    
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER)  
    {
        /* Transmit End */
        __HAL_SPI_CS_RELEASE(hspi);
    }

    return Status;
}

/******************************************************************************
*@brief : Transmits an amount of data by loop mode witch CS kept low(Master mode).
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to be sent
*@param : Timeout : Transmit Timeout
*@return: HAL_StatusTypeDef
*@note  : CS will NOT kept low if transmitting is timed out.
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_TransmitKeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef Status;
    
    Status = _HAL_SPI_Transmit(hspi, pData, Size, Timeout);
    
    if ( (hspi->Init.SPI_Mode == SPI_MODE_MASTER) && (Status == HAL_TIMEOUT) )
    {
        /* Transmit End */
        __HAL_SPI_CS_RELEASE(hspi);
    }

    return Status;
}

/******************************************************************************
*@brief : Receive an amount of data by loop mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to receive
*@param : Timeout  : Receive Timeout
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef _HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    __IO uint32_t uiTimeout;
    uint32_t i;
    uint32_t recv_cnt = 0;
    
    SPI_TypeDef* SPIx = hspi->Instance;

    HAL_StatusTypeDef Status = HAL_OK;
        
    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(SPIx));
    
    if (pData == NULL)    return HAL_ERROR;
    
    hspi->Rx_Count = 0;
    hspi->Rx_Size = Size;
    hspi->Rx_Buffer = pData;
    uiTimeout = Timeout;
    
    /* Clear RX FIFO */
    __SPI_RXFIFO_RESET(SPIx);
    
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);
    
    SPIx->RX_CTL |= SPI_RX_CTL_EN;
    SPIx->TX_CTL &= ~SPI_TX_CTL_EN; //tx_en = 0, why send 88?
    
    SPIx->BATCH = 1;
    
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {
        /* Set Data Size */
        SPIx->BATCH = Size;
        /* Receive Start */
        __HAL_SPI_TRANSSTART_CS_LOW(hspi);
    }
    
    while ( Size > recv_cnt ) 
    { 
        if (!READ_BIT(SPIx->STATUS, SPI_STATUS_RX_FIFO_EMPTY))
        {
            pData[recv_cnt++] = SPIx->DAT;
            uiTimeout = Timeout;
            
        }
        else
        {
            if(uiTimeout)
            {
                uiTimeout--;
                if (uiTimeout == 0) 
                {
                    Status =  HAL_TIMEOUT;
                    goto End;
                }
            }
        }
    }

    /* Wait Transmit Done */
    while (!(SPIx->STATUS & SPI_STATUS_RX_BATCH_DONE));

End:   
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);    
    
    /* Rx Disable */
    CLEAR_BIT(SPIx->RX_CTL, SPI_RX_CTL_EN);
    
    hspi->Rx_Count = recv_cnt;
    
    return Status;
}

/******************************************************************************
*@brief : Receive an amount of data by loop mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to receive
*@param : Timeout  : Receive Timeout
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef Status;
    
    Status = _HAL_SPI_Receive(hspi, pData, Size, Timeout);
    
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {
        /* Receive End */
        __HAL_SPI_CS_RELEASE(hspi);
    }
    
    return Status;
}

/******************************************************************************
*@brief : Receive an amount of data by loop mode witch CS contorl.
*         This function is same as HAL_SPI_Receive except that it will 
*         control the CS state according to the param Init.KeepCS at the end of transmission
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to receive
*@param : Timeout  : Receive Timeout
*@param : CSState : The CS control State at the end of current transmission.
*                   This param can be a value of:
*                   CS_RELEASE: Relase the CS Pin at the end of transmission(CS release to HIGH)
*                   CS_HOLD   : Keep the CS Pin for next transmission(CS keep LOW)
*@return: HAL_StatusTypeDef
*@note  : It will always release CS when transmission is timed out.
*         This function can be compatible with HAL_SPI_Receive by always setting Init.KeepCS to false.
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_ReceiveKeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef Status;
    
    Status = _HAL_SPI_Receive(hspi, pData, Size, Timeout);
    
    if ( (hspi->Init.SPI_Mode == SPI_MODE_MASTER) && (Status == HAL_TIMEOUT) )
    {
        /* Receive End */
        __HAL_SPI_CS_RELEASE(hspi);
    }
    
    return Status;
}

/******************************************************************************
*@brief : SPI Wire Config
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : X_Mode : 1x/2x/4x Mode, see@ref X_MODE 
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_Wire_Config(SPI_HandleTypeDef *hspi, uint32_t X_Mode)
{
    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(hspi->Instance));
    
    /* Set SPI X_Mode */
    hspi->Instance->CTL = ((hspi->Instance->CTL) & (~SPI_CTL_X_MODE)) | X_Mode;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Transmits an amount of data by IT mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to be sent
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef _HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    SPI_TypeDef* SPIx = hspi->Instance;
    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(SPIx));
    
    /* Tx machine is running */
    if (hspi->TxState != SPI_TX_STATE_IDLE) 
    {
        return HAL_ERROR;
    }
    
    hspi->Tx_Size   = Size;
    hspi->Tx_Buffer = pData; 
    hspi->Tx_Count = 0;       
    
    /* Clear TX FIFO */
    __SPI_TXFIFO_RESET(SPIx);
    
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);
    
    /* Set Data Size */
    SPIx->BATCH = Size;

    /* Tx Enable */
    SPIx->TX_CTL |= SPI_TX_CTL_EN;
    /* Rx Disable */
    SPIx->RX_CTL &= (~SPI_RX_CTL_EN);    
    
    while (hspi->Tx_Count < hspi->Tx_Size)   
    {
        if (!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL))
            SPIx->DAT = hspi->Tx_Buffer[hspi->Tx_Count++];
        else
            break;           
    }

    /* Enable Tx FIFO half empty Interrupt and Tx batch done Interrupt*/
    SET_BIT(SPIx->IE, (SPI_IE_TX_FIFO_HALF_EMPTY_EN | SPI_IE_TX_BATCH_DONE_EN));
    
    /* Set machine is Sending */
    hspi->TxState = SPI_TX_STATE_SENDING;

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        /* Transmit Start */
        __HAL_SPI_TRANSSTART_CS_LOW(hspi);
    }
    
    return HAL_OK;
}


/******************************************************************************
*@brief : Transmits an amount of data by IT mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to be sent
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    assert_param(hspi);
    
    hspi->KeepCS = false;
    
    return _HAL_SPI_Transmit_IT(hspi, pData, Size);
}

/******************************************************************************
*@brief : Transmits an amount of data by IT mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to be sent
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_Transmit_IT_KeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    assert_param(hspi);
    
    if(hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        hspi->KeepCS = true;
    }
    
    return _HAL_SPI_Transmit_IT(hspi, pData, Size);
}

/******************************************************************************
*@brief : Receive an amount of data by IT mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to receive
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef _HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    SPI_TypeDef* SPIx = hspi->Instance;
    
    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(SPIx));
    
    /* Rx machine is running */
    if (hspi->RxState != SPI_RX_STATE_IDLE) 
    {
        return HAL_ERROR;
    }
    
    /* Clear RX FIFO */
    __SPI_RXFIFO_RESET(SPIx);
    
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);
    
    /* Rx Enable */
    SPIx->RX_CTL |= SPI_RX_CTL_EN;

    /* Set Data Size */
    SPIx->BATCH = Size;
    
    hspi->Rx_Size   = Size;
    hspi->Rx_Buffer = pData; 
    hspi->Rx_Count = 0;   

    /* Enable Rx FIFO Not Empty Interrupt */
    SET_BIT(SPIx->IE, SPI_IE_RX_FIFO_NOT_EMPTY_EN | SPI_IE_RX_BATCH_DONE_EN);
    
    /* Set Slave machine is receiving */
    hspi->RxState = SPI_RX_STATE_RECEIVING;
    
    if(hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        /* Receive Start */
        __HAL_SPI_TRANSSTART_CS_LOW(hspi);
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data by IT mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to receive
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    assert_param(hspi);
    
    hspi->KeepCS = false;
    
    return _HAL_SPI_Receive_IT(hspi, pData, Size);
}

/******************************************************************************
*@brief : Receive an amount of data by IT mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to receive
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_Receive_IT_KeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    assert_param(hspi);
    
    if(hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        hspi->KeepCS = true;
    }
    
    return _HAL_SPI_Receive_IT(hspi, pData, Size);
}

#ifdef HAL_DMA_MODULE_ENABLED
/******************************************************************************
*@brief : Transmits an amount of data by DMA mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to be sent
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef _HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    SPI_TypeDef* SPIx = hspi->Instance;
    
    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(SPIx));
    
    /* Rx machine is running */
    if (hspi->TxState != SPI_TX_STATE_IDLE) 
    {
        return HAL_ERROR;
    }

    /* Clear TX FIFO */
    __SPI_TXFIFO_RESET(SPIx);
    
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);
    
    /* Enable Tx Batch Done Interrupt */
    SET_BIT(SPIx->IE, SPI_STATUS_TX_BATCH_DONE);
    
    /* Set Data Size */
    SPIx->BATCH = Size;
    
    /* Tx FIFO */
    SPIx->TX_CTL &= ~SPI_TX_CTL_DMA_LEVEL;
    SPIx->TX_CTL |= SPI_TX_CTL_DMA_LEVEL_0;    

    /* Tx Enable */
    SPIx->TX_CTL |= SPI_TX_CTL_EN;
    /* Rx Disable */
    SPIx->RX_CTL &= (~SPI_RX_CTL_EN);
    
    /* Set machine is Sending */
    hspi->TxState = SPI_TX_STATE_SENDING;
    
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        /* Transmit Start */
        __HAL_SPI_TRANSSTART_CS_LOW(hspi);
    }    
    
    HAL_DMA_Start(hspi->HDMA_Tx, (uint32_t)pData, (uint32_t)&SPIx->DAT, Size);

    SPIx->TX_CTL |= SPI_TX_CTL_DMA_REQ_EN;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    assert_param(hspi);
    
    hspi->KeepCS = false;
    
    return _HAL_SPI_Transmit_DMA(hspi, pData, Size);
}

HAL_StatusTypeDef HAL_SPI_Transmit_DMA_KeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    assert_param(hspi);
    
    hspi->KeepCS = false;
    
    return _HAL_SPI_Transmit_DMA(hspi, pData, Size);
}

/******************************************************************************
*@brief : Receive an amount of data by DMA mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to receive
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef _HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    SPI_TypeDef* SPIx = hspi->Instance;
    
    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(hspi->Instance));
    
    /* Rx machine is running */
    if (hspi->RxState != SPI_RX_STATE_IDLE) 
    {
        return HAL_ERROR;
    }
    
    /* Clear RX FIFO */
    __SPI_RXFIFO_RESET(SPIx);
    
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);

    /* Enable Rx Batch Done Interrupt */
    SET_BIT(hspi->Instance->IE, SPI_STATUS_RX_BATCH_DONE);

    /* Set Data Size */
    hspi->Instance->BATCH = Size;

    /* Rx Enable */
    hspi->Instance->RX_CTL |= SPI_RX_CTL_EN;
    /* Rx FIFO */
    hspi->Instance->RX_CTL |= SPI_RX_CTL_DMA_LEVEL_0;
    
    /* Set Slave machine is receiving */
    hspi->RxState = SPI_RX_STATE_RECEIVING;

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {
        /* Receive Start */
        __HAL_SPI_TRANSSTART_CS_LOW(hspi);
    }

    HAL_DMA_Start(hspi->HDMA_Rx, (uint32_t)&hspi->Instance->DAT, (uint32_t)pData, Size);
    
    hspi->Instance->RX_CTL |= SPI_RX_CTL_DMA_REQ_EN; 
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    assert_param(hspi);
    
    hspi->KeepCS = false;
    
    return _HAL_SPI_Receive_DMA(hspi, pData, Size);
}

HAL_StatusTypeDef HAL_SPI_Receive_DMA_KeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    assert_param(hspi);
    
    if(hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        hspi->KeepCS = true;
    }
    
    return _HAL_SPI_Receive_DMA(hspi, pData, Size);
}
#endif

/******************************************************************************
*@brief : Transmits and recieve an amount of data in loop mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pTxData : Pointer to transmit data buffer
*@param : pRxData : Pointer to recieve data buffer
*@param : Size  : Amount of data to be sent and receive
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i;
    __IO uint32_t uiTimeout;    
    uint32_t send_cnt = 0;
    uint32_t recv_cnt = 0;
    HAL_StatusTypeDef Status = HAL_OK;
    SPI_TypeDef * SPIx = hspi->Instance;

    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(SPIx));
    
    if ((pTxData == NULL)||(pRxData == NULL))    return HAL_ERROR;
    
    hspi->Tx_Count = 0;
    hspi->Rx_Count = 0;
    hspi->Tx_Buffer = pTxData;
    hspi->Rx_Buffer = pRxData;
    hspi->Tx_Size = Size;   
    hspi->Rx_Size = Size;   
    uiTimeout = Timeout;
    
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);

    /* Tx Enable */
    SPIx->TX_CTL |= SPI_TX_CTL_EN;

    /* Rx Enable */
    SPIx->RX_CTL |= SPI_RX_CTL_EN;

    /* Clear TX/RX FIFO */
    __SPI_TXFIFO_RESET(SPIx);
    __SPI_RXFIFO_RESET(SPIx);
    
    while((!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL)) && (Size > send_cnt))
    {
        SPIx->DAT = pTxData[send_cnt++];
    }
        
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {       
        /* Set Data Size */
        SPIx->BATCH = Size;

        /* Transmit Start */
        __HAL_SPI_TRANSSTART_CS_LOW(hspi);
        
        while(1)
        {
            if(Size > send_cnt)
            {
                /* Wait Tx FIFO Not Full */
                if(!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL))
                {
                    SPIx->DAT = pTxData[send_cnt++];
                    uiTimeout = Timeout;
                }
            }
            
            /* Wait Rx FIFO Not Empty */
            if(!(SPIx->STATUS & SPI_STATUS_RX_FIFO_EMPTY))
            {
                pRxData[recv_cnt++] = SPIx->DAT;
                uiTimeout = Timeout;
            }
            
            if(Size == recv_cnt)
                break;
            
            /* Wait Timeout */
            if(uiTimeout)
            {
                uiTimeout--;
                if(uiTimeout == 0)
                {
                    Status = HAL_TIMEOUT;
                    goto End;
                }
            }
        }
        
    }
    else    
    {
        while(1)
        {
            /* Wait Rx FIFO Not Empty */
            if(Size > recv_cnt)
            {
                if((!(SPIx->STATUS & SPI_STATUS_RX_FIFO_EMPTY)))
                {
                    pRxData[recv_cnt++] = SPIx->DAT;
                    uiTimeout = Timeout;
                }
            }
            /* Wait Tx FIFO Not Full */
            if(Size > send_cnt)
            {
                if(!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL))
                {
                    SPIx->DAT = pTxData[send_cnt++];
                    uiTimeout = Timeout;
                }
            }
            
            if(Size == recv_cnt && Size == send_cnt)
                break;
            
            /* Wait Timeout */
            if(uiTimeout)
            {
                uiTimeout--;
                if(uiTimeout == 0)
                {
                    Status = HAL_TIMEOUT;
                    goto End;
                }
            }
        }
    }
              
    /* Wait Transmit Done */
    while (!(SPIx->STATUS & SPI_STATUS_TX_BATCH_DONE));
    
    Status = HAL_OK;

End:    
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);

    /* Tx Disable */
    SPIx->TX_CTL &= (~SPI_TX_CTL_EN);
    
    /* Rx Disable */
    SPIx->RX_CTL &= (~SPI_RX_CTL_EN);

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {
        /* Transmit End */
        __HAL_SPI_CS_RELEASE(hspi);
    }
    
    hspi->Tx_Count = send_cnt;
    hspi->Rx_Count = recv_cnt;

    return Status;
}

/******************************************************************************
*@brief : Get Tx state.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@return: SPI Tx State
******************************************************************************/
uint8_t HAL_SPI_GetTxState(SPI_HandleTypeDef *hspi)
{
    return hspi->TxState;
}

/******************************************************************************
*@brief : Get Rx state.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@return: SPI Rx State
******************************************************************************/
uint8_t HAL_SPI_GetRxState(SPI_HandleTypeDef *hspi)
{
    return hspi->RxState;
}

//////////////////////////////////////////////////////////////////////////////////
static void HAL_SPI_CloseTx(SPI_HandleTypeDef* hspi)
{
    /* Tx Disable */
    hspi->Instance->TX_CTL &= (~SPI_TX_CTL_EN);
    
    /* Disable TxFIFO half empty interrupt */
    CLEAR_BIT(hspi->Instance->IE, SPI_IE_TX_FIFO_HALF_EMPTY_EN | SPI_IE_TX_BATCH_DONE_EN);
        
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(hspi->Instance, SPI_STATUS_BATCH_DONE);
    
    __SPI_TXFIFO_RESET(hspi->Instance);
    
    /* Set machine is DILE */
    hspi->TxState = SPI_TX_STATE_IDLE;
    
    if(hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        __HAL_SPI_CS_RELEASE(hspi);
    }
}

static void HAL_SPI_CloseRx(SPI_HandleTypeDef* hspi)
{
    /* Rx Disable */
    hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);
    
    /* Disable RxFIFO not empty interrupt */
    CLEAR_BIT(hspi->Instance->IE, SPI_IE_RX_FIFO_NOT_EMPTY_EN | SPI_IE_RX_BATCH_DONE_EN);
        
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(hspi->Instance, SPI_STATUS_BATCH_DONE);
    
    __SPI_RXFIFO_RESET(hspi->Instance);
    
    /* Set machine is DILE */
    hspi->RxState = SPI_RX_STATE_IDLE;
    
    if(hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        __HAL_SPI_CS_RELEASE(hspi);
    }
}

HAL_StatusTypeDef HAL_SPI_WaitTxTimeout(SPI_HandleTypeDef *hspi, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
    
    while(hspi->TxState != SPI_TX_STATE_IDLE)
    {
        /* Wait Timeout */
        if(timeout)
        {
            timeout--;
            if(timeout == 0)
            {
                status = HAL_TIMEOUT;
                break;
            }
        }
    }
    
    if(status == HAL_TIMEOUT)
    {
        HAL_SPI_CloseTx(hspi);
    }
	
	return status;
}

HAL_StatusTypeDef HAL_SPI_WaitRxTimeout(SPI_HandleTypeDef *hspi, uint32_t timeout)
{ 
    HAL_StatusTypeDef status = HAL_OK;
    
    while(hspi->RxState != SPI_RX_STATE_IDLE)
    {
        /* Wait Timeout */
        if(timeout)
        {
            timeout--;
            if(timeout == 0)
            {
                status = HAL_TIMEOUT;
                break;
            }
        }
    }
    
    if(status == HAL_TIMEOUT)
    {
        HAL_SPI_CloseRx(hspi);
    }
	
	return status;
}

/*--------------------------------------------------------------------------------------*/
/******************************************************************************
*@brief : Transmits and recieve an amount of data in loop mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pTxData : Pointer to transmit data buffer
*@param : pRxData : Pointer to recieve data buffer
*@param : Size  : Amount of data to be sent and receive
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_TransmitReceiveNoneBatch(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i;
    __IO uint32_t uiTimeout;    
    uint32_t send_cnt = 0;
    uint32_t recv_cnt = 0;
    HAL_StatusTypeDef Status = HAL_OK;
    SPI_TypeDef * SPIx = hspi->Instance;

    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(SPIx));
    
    if ((pTxData == NULL)||(pRxData == NULL))    return HAL_ERROR;
    
    hspi->Tx_Count = 0;
    hspi->Rx_Count = 0;
    hspi->Tx_Buffer = pTxData;
    hspi->Rx_Buffer = pRxData;
    hspi->Tx_Size = Size;   
    hspi->Rx_Size = Size;   
    uiTimeout = Timeout;
    
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);

    /* Tx Enable */
    SPIx->TX_CTL |= SPI_TX_CTL_EN;

    /* Rx Enable */
    SPIx->RX_CTL |= SPI_RX_CTL_EN;

    /* Clear TX/RX FIFO */
    __SPI_TXFIFO_RESET(SPIx);
    __SPI_RXFIFO_RESET(SPIx);
    
    while((!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL)) && (Size > send_cnt))
    {
        SPIx->DAT = pTxData[send_cnt++];
    }
    
    /* Set Data Size */
    SPIx->BATCH = 0;
        
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {       
        /* Transmit Start */
        __HAL_SPI_TRANSSTART_CS_LOW(hspi);
        
        while(1)
        {
            if(Size > send_cnt)
            {
                /* Wait Tx FIFO Not Full */
                if(!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL))
                {
                    SPIx->DAT = pTxData[send_cnt++];
                    uiTimeout = Timeout;
                }
            }
            
            /* Wait Rx FIFO Not Empty */
            if(!(SPIx->STATUS & SPI_STATUS_RX_FIFO_EMPTY))
            {
                pRxData[recv_cnt++] = SPIx->DAT;
                uiTimeout = Timeout;
            }
            
            if(Size == recv_cnt)
                break;
            
            /* Wait Timeout */
            if(uiTimeout)
            {
                uiTimeout--;
                if(uiTimeout == 0)
                {
                    Status = HAL_TIMEOUT;
                    goto End;
                }
            }
        }
        
    }
    else    
    {
        while(1)
        {
            /* Wait Rx FIFO Not Empty */
            if(Size > recv_cnt)
            {
                if((!(SPIx->STATUS & SPI_STATUS_RX_FIFO_EMPTY)))
                {
                    pRxData[recv_cnt++] = SPIx->DAT;
                    uiTimeout = Timeout;
                }
            }
            /* Wait Tx FIFO Not Full */
            if(Size > send_cnt)
            {
                if(!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL))
                {
                    SPIx->DAT = pTxData[send_cnt++];
                    uiTimeout = Timeout;
                }
            }
            
            if(Size == recv_cnt && Size == send_cnt)
                break;
            
            /* Wait Timeout */
            if(uiTimeout)
            {
                uiTimeout--;
                if(uiTimeout == 0)
                {
                    Status = HAL_TIMEOUT;
                    goto End;
                }
            }
        }
    }

End:    
//    /* Clear Batch Done Flag  */
//    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);

    
    /* Rx Disable */
    SPIx->RX_CTL &= (~SPI_RX_CTL_EN);
    
    /* Tx Disable */
    SPIx->TX_CTL &= (~SPI_TX_CTL_EN);

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {
        /* Transmit End */
        __HAL_SPI_CS_RELEASE(hspi);
    }
    
    hspi->Tx_Count = send_cnt;
    hspi->Rx_Count = recv_cnt;

    return Status;
}

/******************************************************************************
*@brief : Transmits an amount of data by loop mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to be sent
*@param : Timeout : Transmit Timeout
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef _HAL_SPI_TransmitNoneBatch(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i;
    uint32_t send_cnt = 0;
    uint32_t recv_cnt = 0;
    __IO uint32_t uiTimeout;    
    HAL_StatusTypeDef Status = HAL_OK;    
    SPI_TypeDef* SPIx = hspi->Instance;

    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(SPIx));
    
    if(!Size)    return HAL_ERROR;
    if (pData == NULL)    return HAL_ERROR;
    
    hspi->Tx_Count = 0;
    hspi->Tx_Size = Size;
    hspi->Tx_Buffer = pData;
    
    uiTimeout = Timeout;

    /* Clear Batch Done Flag  */    
//    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);
    
    /* Tx Enable */
    hspi->Instance->TX_CTL |= SPI_TX_CTL_EN;
    /* Rx Disable */
    hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);
    
    /* Clear TX FIFO */
    __SPI_TXFIFO_RESET(SPIx);
    
    SPIx->BATCH = 0;
        
    while((!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL)) && (Size > send_cnt))
    {
        SPIx->DAT = pData[send_cnt++];
    }

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {          
        /* Transmit Start */
        __HAL_SPI_TRANSSTART_CS_LOW(hspi);
    }
        
    while(Size > send_cnt)
    {
        /* Wait Tx FIFO Not Full */
        if(!(SPIx->STATUS & SPI_STATUS_TX_FIFO_FULL))
        {
            SPIx->DAT = pData[send_cnt++];
            uiTimeout = Timeout;
        }
        else
        {
            /* Wait Timeout */
            if(uiTimeout)
            {
                uiTimeout--;
                if(uiTimeout == 0)
                {
                    Status = HAL_TIMEOUT;
                    goto End;
                }
            }
        }            
    }
    
End:
    while(!(SPIx->STATUS & SPI_STATUS_TX_FIFO_EMPTY));
    while(READ_BIT(SPIx->STATUS, SPI_STATUS_TX_BUSY));
    
    /* Tx Disable */
    CLEAR_BIT(hspi->Instance->TX_CTL, SPI_TX_CTL_EN);
    
    hspi->Tx_Count = send_cnt;

    return Status;
}

HAL_StatusTypeDef HAL_SPI_TransmitNoneBatch(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef Status;
    
    Status = _HAL_SPI_TransmitNoneBatch(hspi, pData, Size, Timeout);
    
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER)  
    {
        /* Transmit End */
        __HAL_SPI_CS_RELEASE(hspi);
    }

    return Status;
}

HAL_StatusTypeDef HAL_SPI_TransmitNoneBatchKeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef Status;
    
    Status = _HAL_SPI_TransmitNoneBatch(hspi, pData, Size, Timeout);
    
    if ( (hspi->Init.SPI_Mode == SPI_MODE_MASTER) && (Status == HAL_TIMEOUT) )
    {
        /* Transmit End */
        __HAL_SPI_CS_RELEASE(hspi);
    }

    return Status;
}

/******************************************************************************
*@brief : Receive an amount of data by loop mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to receive
*@param : Timeout  : Receive Timeout
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef _HAL_SPI_ReceiveNoneBatch(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    __IO uint32_t uiTimeout;
    uint32_t i;
    uint32_t recv_cnt = 0;
    
    SPI_TypeDef* SPIx = hspi->Instance;

    HAL_StatusTypeDef Status = HAL_OK;
        
    /* Check SPI Parameter */
    assert_param (IS_SPI_ALL_INSTANCE(SPIx));
    
    if (pData == NULL)    return HAL_ERROR;
    
    hspi->Rx_Count = 0;
    hspi->Rx_Size = Size;
    hspi->Rx_Buffer = pData;
    uiTimeout = Timeout;
    
    /* Clear RX FIFO */
    __SPI_RXFIFO_RESET(SPIx);
    
    /* Clear Batch Done Flag  */
    __SPI_CLEAR_FLAG(SPIx, SPI_STATUS_BATCH_DONE);
    
    SPIx->RX_CTL |= SPI_RX_CTL_EN;
    SPIx->TX_CTL &= ~SPI_TX_CTL_EN; //tx_en = 0, why send 88?
    
    SPIx->BATCH = 0;

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {
        /* Receive Start */
        __HAL_SPI_TRANSSTART_CS_LOW(hspi);
    }
    
    while ( Size > recv_cnt ) 
    { 
        if (!READ_BIT(SPIx->STATUS, SPI_STATUS_RX_FIFO_EMPTY))
        {
            pData[recv_cnt++] = SPIx->DAT;
            uiTimeout = Timeout;
            
        }
        else
        {
            if(uiTimeout)
            {
                uiTimeout--;
                if (uiTimeout == 0) 
                {
                    Status =  HAL_TIMEOUT;
                    goto End;
                }
            }
        }
    }

End:    
    /* Rx Disable */
    CLEAR_BIT(SPIx->RX_CTL, SPI_RX_CTL_EN);
    
    hspi->Rx_Count = recv_cnt;
    
    return Status;
}

/******************************************************************************
*@brief : Receive an amount of data by loop mode.
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to receive
*@param : Timeout  : Receive Timeout
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_ReceiveNoneBatch(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef Status;
    
//    Status = _HAL_SPI_ReceiveNoneBatch(hspi, pData, Size, Timeout);
    if(((hspi->Instance->CTL & SPI_CTL_X_MODE_Msk) == SPI_1X_MODE) && (hspi->Instance->CTL & SPI_CTL_MST_MODE))
        Status = HAL_SPI_TransmitReceiveNoneBatch(hspi, pData, pData, Size, Timeout);
    else
        Status = _HAL_SPI_ReceiveNoneBatch(hspi, pData, Size, Timeout);
    
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {
        /* Receive End */
        __HAL_SPI_CS_RELEASE(hspi);
    }
    
    return Status;
}

/******************************************************************************
*@brief : Receive an amount of data by loop mode witch CS contorl.
*         This function is same as HAL_SPI_Receive except that it will 
*         control the CS state according to the param Init.KeepCS at the end of transmission
*         
*@param : hspi: a pointer of SPI_HandleTypeDef structure which contains 
*         the configuration information for the specified SPI.
*@param : pData : Pointer to data buffer
*@param : Size  : Amount of data to receive
*@param : Timeout  : Receive Timeout
*@param : CSState : The CS control State at the end of current transmission.
*                   This param can be a value of:
*                   CS_RELEASE: Relase the CS Pin at the end of transmission(CS release to HIGH)
*                   CS_HOLD   : Keep the CS Pin for next transmission(CS keep LOW)
*@return: HAL_StatusTypeDef
*@note  : It will always release CS when transmission is timed out.
*         This function can be compatible with HAL_SPI_Receive by always setting Init.KeepCS to false.
******************************************************************************/
HAL_StatusTypeDef HAL_SPI_ReceiveNoneBatchKeepCS(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef Status;
    
    Status = _HAL_SPI_Receive(hspi, pData, Size, Timeout);
    
    if ( (hspi->Init.SPI_Mode == SPI_MODE_MASTER) && (Status == HAL_TIMEOUT) )
    {
        /* Receive End */
        __HAL_SPI_CS_RELEASE(hspi);
    }
    
    return Status;
}

#endif //HAL_SPI_MODULE_ENABLED

