/******************************************************************************
*@file  : hal_i2c.c
*@brief : This file provides firmware functions to manage the I2C HAL module
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#include "hal_i2c.h" 


#ifdef HAL_I2C_MODULE_ENABLED

/* Private functions for I2C */
static HAL_StatusTypeDef I2C_Set_Clock_Speed(I2C_HandleTypeDef *hi2c, uint32_t ClockSpeed);
static HAL_StatusTypeDef I2C_Master_Request_Write(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout);
static HAL_StatusTypeDef I2C_Master_Request_Read(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout);
static HAL_StatusTypeDef I2C_Check_Device_Ready(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout);
static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout);


/******************************************************************************
*@brief : I2C interrupt handler
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@return: None
******************************************************************************/
__weak void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c)
{
    if(hi2c->Init.I2C_Mode == I2C_MODE_SLAVE)
    {
        /* Slave ADDR1 Interrupt */
        if (READ_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1))
        {
            /* Clear ADDR1 Interrupt Flag */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);
            
            CLEAR_BIT(hi2c->Instance->CR, I2C_CR_RX_ADDR1_INT_EN );

            /* Slave Transmit */
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_SRW))
            {
                hi2c->state = I2C_STATE_TX_DATA;
            }
            else
            {
                hi2c->state = I2C_STATE_RX_DATA;
            }
        }
        
        if(hi2c->state == I2C_STATE_TX_DATA)
        {
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_TXE))
            {
                if(hi2c->Tx_Count == hi2c->Tx_Size)
                {
                    ;//while(1);
                }
                else
                {
                    hi2c->Instance->DR = hi2c->Tx_Buffer[hi2c->Tx_Count++];
                }
            }
        }
        else if(hi2c->state == I2C_STATE_RX_DATA)
        {
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_RXNE))
            {
                hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
            }
        }
  
    }
    else
    {   
        
        
            
            
        /* master */
        if(hi2c->state == I2C_STATE_TX_DATA)
        {
            
            
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_TXE))
            {
                hi2c->Instance->DR = hi2c->Tx_Buffer[hi2c->Tx_Count++];
                if(hi2c->Tx_Count > hi2c->Tx_Size)
                {
                    SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
                }
            }
        }
        else{

        if((hi2c->state == I2C_STATE_RX_DATA) /*|| (hi2c->state == I2C_STATE_REQ_ADDR)*/)
        {
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_RXNE))
            {
                hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
                
                if(hi2c->Rx_Size - hi2c->Rx_Count == 1)
                {
                     /* Prepare for Generate NACK */
                    SET_BIT(hi2c->Instance->CR, I2C_CR_TACK);
                    /* Prepare for Generate STOP */
                    SET_BIT(hi2c->Instance->CR, I2C_CR_STOP); 
                }
            }
            
//            if(READ_BIT(hi2c->Instance->SR, I2C_SR_MTF))
//            {
//                //clear MTF
//                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
//                
//                if(hi2c->state == I2C_STATE_REQ_ADDR)
//                {
//                    hi2c->state = I2C_STATE_RX_DATA;
//                    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_TX_RX_FLAG);
//                    
//                }
//            }
        }
        else if(hi2c->state == I2C_STATE_REQ_ADDR)
        {
            if(READ_BIT(hi2c->Instance->SR, I2C_SR_TX_RX_FLAG))
            {
                hi2c->state = I2C_STATE_RX_DATA;
                hi2c->Instance->SR = I2C_SR_TX_RX_FLAG;//READ_BIT(hi2c->Instance->SR, I2C_SR_TX_RX_FLAG);
                if(hi2c->Rx_Size == 1)
                {
                    SET_BIT(hi2c->Instance->CR, I2C_CR_STOP); 
                }
            }
        }
    }
        
        if(READ_BIT(hi2c->Instance->SR, I2C_SR_NACKF))
        {
            //clear MTF
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_NACKF);
            
//            if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
            {
                /* Generate Stop */
                SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
            }
            
        }
    }
    
    /* STOP Flag Interrupt */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_STOPF))
    {
        /* Clear STOPF Interrupt Flag */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_STOPF);
        
        /* Clear STOPF */
        CLEAR_BIT(hi2c->Instance->CR, I2C_CR_STOPF_INTEN);
        
        if(hi2c->state == I2C_STATE_RX_DATA)
        {
            if(hi2c->Init.I2C_Mode == I2C_MODE_MASTER)
            {
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK);
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_STOP); 
            }
        }
        
        if (hi2c->I2C_STOPF_Callback != NULL) 
        {
            hi2c->I2C_STOPF_Callback(hi2c);
        }
        
        hi2c->state = I2C_STATE_IDLE;
        
        CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TXE_INT_EN | I2C_CR_MTF_INT_EN | I2C_CR_STOPF_INTEN | I2C_CR_RXNE_INT_EN | I2C_CR_NACKF_INTEN | I2C_CR_TX_RX_FLAG_INTEN);

    }
}

/******************************************************************************
*@brief : Init low level of I2C module: GPIO, CLK, NVIC
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@return: None
******************************************************************************/
__weak void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */
    GPIO_InitTypeDef GPIO_Handle; 
    
    /* I2C1 */
    if (hi2c->Instance == I2C1)
    {
        /* Enable Clock */
        __HAL_RCC_I2C1_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /* I2C1 SDA  PB7 */
        /* I2C1 SCL  PB6 */
        GPIO_Handle.Pin            = GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_Handle.Mode           = GPIO_MODE_AF_PP;
        GPIO_Handle.Pull           = GPIO_PULLUP;
		GPIO_Handle.Drive          = GPIO_DRIVE_LEVEL3;
        GPIO_Handle.Alternate      = GPIO_FUNCTION_5;
        HAL_GPIO_Init(GPIOB, &GPIO_Handle);
        
        /* Clear Pending Interrupt */
        NVIC_ClearPendingIRQ(I2C1_IRQn);
        
        /* Enable External Interrupt */
        NVIC_EnableIRQ(I2C1_IRQn);
    }

}

/******************************************************************************
*@brief : DeInit low level of I2C module: GPIO, CLK, NVIC
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@return: None
******************************************************************************/
__weak void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */
    GPIO_InitTypeDef GPIO_Handle; 
    
    /* I2C1 */
    if (hi2c->Instance == I2C1)
    {
        /* Disable Clock */
        __HAL_RCC_I2C1_CLK_DISABLE();

        /* I2C1 SDA  PortB Pin7 */
        /* I2C1 SCL  PortB Pin6 */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);
        /* Clear Pending Interrupt */
        NVIC_ClearPendingIRQ(I2C1_IRQn);
        
        /* Disable External Interrupt */
        NVIC_DisableIRQ(I2C1_IRQn);
    }

}

/******************************************************************************
*@brief : Initialize the I2c module with parameters
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)
{
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));
    assert_param (IS_I2C_ALL_MODE(hi2c->Init.I2C_Mode));
    
    if(hi2c->Init.I2C_Mode == I2C_MODE_MASTER)
        assert_param (IS_I2C_CLOCK_SPEED(hi2c->Init.Clock_Speed));
    else
    {
        assert_param (IS_I2C_TX_AUTO_EN(hi2c->Init.Tx_Auto_En));
        assert_param (IS_I2C_STRETCH_EN(hi2c->Init.Stretch_Mode));
    }

    /* Disable the selected I2C peripheral */
    CLEAR_BIT(hi2c->Instance->CR, I2C_CR_MEN); 

    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_I2C_MspInit(hi2c);

    switch (hi2c->Init.I2C_Mode)
    {
        /* Master Mode */
        case I2C_MODE_MASTER:
        {
            /* Set Master Mode */
            SET_BIT(hi2c->Instance->CR, I2C_CR_MASTER);
            
            /* Set Clock Speed */
            I2C_Set_Clock_Speed(hi2c, hi2c->Init.Clock_Speed);
            
            if (FILTER_ALGO_ENABLE == hi2c->Init.filter_enable) 
            {
                hi2c->Instance->FILTER = 0x303;  //config as PCLK   
            }
            /* Set SDA auto change the direction */
            if (hi2c->Init.Tx_Auto_En == TX_AUTO_ENABLE)
                SET_BIT(hi2c->Instance->CR, I2C_CR_TX_AUTO_EN);
            else
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TX_AUTO_EN);
            
            /* Enable the selected I2C peripheral */
            SET_BIT(hi2c->Instance->CR, I2C_CR_MEN);
        }break;
        
        /* Slave Mode */
        case I2C_MODE_SLAVE: 
        {
            SET_BIT(hi2c->Instance->CR, I2C_CR_TXE_SEL);
            
            if (FILTER_ALGO_ENABLE == hi2c->Init.filter_enable) 
            {
                hi2c->Instance->FILTER = 0x303;  //config as PCLK     
            }      
            /* Set SDA auto change the direction */
            if (hi2c->Init.Tx_Auto_En == TX_AUTO_ENABLE)
                SET_BIT(hi2c->Instance->CR, I2C_CR_TX_AUTO_EN);
            else
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TX_AUTO_EN);
            
            /* Set Clock Stretch Mode */
            if (hi2c->Init.Stretch_Mode == STRETCH_MODE_DISABLE)
                SET_BIT(hi2c->Instance->CR, I2C_CR_NOSTRETCH);
            else
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_NOSTRETCH);

            /* Set Address 1 */
            hi2c->Instance->SLAVE_ADDR1 = hi2c->Init.Own_Address;
            
            /* Enable the selected I2C peripheral */
            SET_BIT(hi2c->Instance->CR, I2C_CR_MEN);
        }break;
        
        default: break; 
    }
    
    hi2c->state = I2C_STATE_IDLE;

    return HAL_OK;
}

/******************************************************************************
*@brief : De-Initialize the I2c module
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c)
{
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));
    
    hi2c->state = I2C_STATE_IDLE;
    
    HAL_I2C_MspDeInit(hi2c);
    
    hi2c->Tx_Size = 0;
    hi2c->Rx_Size = 0;
    hi2c->Tx_Count = 0;
    hi2c->Rx_Count = 0;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : send an amount of data in master mode.
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : DevAddress: I2C slave device address.
*@param : pData: Pointer to a data buffer.
*@param : Size: Total size of data to send.
*@param : Timeout: Timeout value.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t i;
    
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));
    
    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size = Size;
    hi2c->Tx_Count = 0;
    
    /* Send Write Access Request */
    if (I2C_Master_Request_Write(hi2c, DevAddress, 0) == HAL_OK)
    {
        for (i = 0; i < hi2c->Tx_Size; i++)
        {
            /* Wait TXE Flag */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_TXE, RESET, Timeout) != HAL_OK) return HAL_ERROR;
            
            /* Send Data */
            hi2c->Instance->DR = hi2c->Tx_Buffer[hi2c->Tx_Count++];
            
            /* Wait for transmission End*/
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
            
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
            
            /* Get NACK */
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
            {
                /* Generate Stop */
                SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
                
                /* Wait for the bus to idle */
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
                
                return HAL_ERROR;
            }
        }
        
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
        
        /* Wait for the bus to idle */
         if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
    }
    else
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Receive an amount of data in master mode.
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : DevAddress: I2C slave device address.
*@param : pData: Pointer to a data buffer to store data.
*@param : Size: Total size of data to receive .
*@param : Timeout: Timeout value.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t i;

    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance)); 
    
    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size = Size;
    hi2c->Rx_Count = 0; 
    
    if (1 == hi2c->Rx_Size)
    {
        __set_PRIMASK(1);    
        if (I2C_Master_Request_Read(hi2c, DevAddress, Timeout) == HAL_OK) 
        {
              // disable interrupt  
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_TX_RX_FLAG, RESET, Timeout) != HAL_OK) 
            {
                __set_PRIMASK(0);    // enable interrupt  
                
                return HAL_ERROR;
            }
            /* Clear TX_RX_FLAG */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_TX_RX_FLAG);
            /* Generate ACK */
            CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK); 
            /* Prepare for Generate NACK */
            SET_BIT(hi2c->Instance->CR, I2C_CR_TACK);
            /* Prepare for Generate STOP */
            SET_BIT(hi2c->Instance->CR, I2C_CR_STOP); 
            
             /* Wait RXNE Flag */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RXNE, RESET, Timeout) != HAL_OK) 
            {          
                __set_PRIMASK(0);    // enable interrupt    
                
                return HAL_ERROR;
            }
            
            /* Read Data */
            hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
            /* Wait for transmission End*/
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) 
            {           
                __set_PRIMASK(0);    // enable interrupt    
                
                return HAL_ERROR;
            }
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
        
            /* Wait for the bus to idle */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) 
            {               
                __set_PRIMASK(0);    // enable interrupt    
                
                return HAL_ERROR;
            }

            /* Generate ACK by default*/
            CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK);  
            
            __set_PRIMASK(0);    // enable interrupt  
            
            return HAL_OK;  
          
        }
        else
        {
            __set_PRIMASK(0);   
            
            return HAL_ERROR;  
        }
    }
    
    
    /* Send Read Access Request */
    if (I2C_Master_Request_Read(hi2c, DevAddress, Timeout) == HAL_OK)
    {
        /* Wait Master Transition receiving state */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_TX_RX_FLAG, RESET, Timeout) != HAL_OK) return HAL_ERROR;
        /* Clear TX_RX_FLAG */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_TX_RX_FLAG);
        /* Generate ACK */
        CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK); 
               
        for (i = 0; i < hi2c->Rx_Size - 1; i++)
        {
            /* Wait RXNE Flag */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RXNE, RESET, Timeout) != HAL_OK) return HAL_ERROR;
            /* Read Data */
            hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
            /* Wait for transmission End*/
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
        }
        
        __set_PRIMASK(1);            
                 
        /* Prepare for Generate NACK */
        SET_BIT(hi2c->Instance->CR, I2C_CR_TACK);
            /* Prepare for Generate STOP */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP); 
        
        __set_PRIMASK(0);    


        /* Wait RXNE Flag */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RXNE, RESET, Timeout) != HAL_OK)  
        {   
            return HAL_ERROR;  
        }
        
        /* Read Data */
        hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
        /* Wait for transmission End*/
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) 
        { 
            return HAL_ERROR;  
        }
        /* Clear MTF */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
        
        /* Wait for the bus to idle */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) 
        { 
            return HAL_ERROR;  
        }
        /* Generate ACK */
        CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK); 
        
    }
    else
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : send an amount of data in slave mode.
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : pData: Pointer to a data buffer.
*@param : Size: Total size of data to send .
*@param : Timeout: Timeout value.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i = 0;
    
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));
    
    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size = Size;
    hi2c->Tx_Count = 0;
  
    CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TXE_SEL);

    hi2c->Instance->DR = hi2c->Tx_Buffer[i++];

    hi2c->Tx_Count++;

    /* Clear RX_ADDR1 Flag */    
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);  
    /* Match the Address 1 */
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RX_ADDR1, RESET, Timeout) != HAL_OK) return HAL_ERROR;
    /* Clear RX_ADDR1 Flag */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);

    /* Slave Transmit */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_SRW))
    {
        /* BUS BUSY */
        while(READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY))
        {
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_MTF)) 
            {
                /* Clear MTF */
                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

            }

            if (READ_BIT(hi2c->Instance->SR, I2C_SR_TXE))
            {
                if (i < hi2c->Tx_Size || hi2c->Tx_Size == 0) 
                {
                    hi2c->Instance->DR = hi2c->Tx_Buffer[i++];
                    hi2c->Tx_Count++;
                }
            }
        }
        hi2c->Instance->SR = READ_REG(hi2c->Instance->SR);
    }
    else
    {
        return HAL_ERROR;
    }

    
    return HAL_OK;
}

/******************************************************************************
*@brief : send an amount of data in Master mode using IT mode.
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : pData: Pointer to a buffer to send data.
*@param : Size: Total size of data to send .
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    __IO uint32_t count = 0U;
    
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));
    
    /* Tx machine is running */
    if (hi2c->state != I2C_STATE_IDLE)
        return HAL_ERROR;
    
    /* Set I2C machine is sending */
    hi2c->state = I2C_STATE_TX_DATA;

    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size   = Size;
    hi2c->Tx_Count = 0;
    
    /* Clear MTF, To Prevent Errors */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
    
    
    SET_BIT(hi2c->Instance->CR, I2C_CR_START);


    SET_BIT(hi2c->Instance->CR, I2C_CR_TXE_INT_EN /*| I2C_CR_MTF_INT_EN */| I2C_CR_STOPF_INTEN | I2C_CR_NACKF_INTEN );
    
    /* Send Device Address */
    hi2c->Instance->DR = DevAddress & 0xFE;
    
    
    return HAL_OK;
}

/******************************************************************************
*@brief : receivd an amount of data in Master mode using IT mode.
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : pData: Pointer to a buffer to store data.
*@param : Size: Total size of data to receive .
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    uint32_t i;

    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance)); 
    
    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size = Size;
    hi2c->Rx_Count = 0; 
    
    hi2c->state = I2C_STATE_REQ_ADDR;
    
    
    /* Clear MTF, To Prevent Errors */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
    
    /* Generate Start */
    SET_BIT(hi2c->Instance->CR, I2C_CR_START);

    
    SET_BIT(hi2c->Instance->CR, I2C_CR_RXNE_INT_EN | I2C_CR_TX_RX_FLAG_INTEN | I2C_CR_STOPF_INTEN | I2C_CR_NACKF_INTEN);
    
//    SET_BIT(hi2c->Instance->CR, I2C_CR_START);
    
    /* Send Device Address */
    hi2c->Instance->DR = DevAddress | 0x01;
    
    if(hi2c->Rx_Size == 1)
    {
        SET_BIT(hi2c->Instance->CR, I2C_CR_TACK);
    }
    
    return HAL_OK;
}

/******************************************************************************
*@brief : send an amount of data in slave mode using IT mode.
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : pData: Pointer to a buffer to send data.
*@param : Size: Total size of data to send .
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size)
{
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));

    /* Rx machine is running */
    if (hi2c->state != I2C_STATE_IDLE)
        return HAL_ERROR;

    /* Set Slave machine is sending */
    hi2c->state = I2C_STATE_TX_DATA;

    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size   = Size;
    hi2c->Tx_Count = 0;

    CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TXE_SEL);

    hi2c->Instance->DR = hi2c->Tx_Buffer[0];

    hi2c->Tx_Count++;

    /* Clear RX ADDR1 Flag */
    SET_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);

    SET_BIT(hi2c->Instance->CR, I2C_CR_RX_ADDR1_INT_EN | I2C_CR_TXE_INT_EN | I2C_CR_STOPF_INTEN);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : receivd an amount of data in slave mode.
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : pData: Pointer to a buffer to store data.
*@param : Size: Total size of data to receive .
*@param : Timeout: Timeout value.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i = 0;
    HAL_StatusTypeDef Status;
    
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));
    
    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size = Size;
    hi2c->Rx_Count = 0;
    
    /* Match the Address 1 */
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RX_ADDR1, RESET, Timeout) != HAL_OK) return HAL_ERROR;
    /* Clear RX_ADDR1 Flag */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);
    
    /* Slave Receive */
    if (!READ_BIT(hi2c->Instance->SR, I2C_SR_SRW))
    {
        /* Wait for transmission End*/
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
        /* Clear MTF */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

        /* BUS BUSY */
        while(READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY))
        {
            /* Receive Data */
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_RXNE))
            {
                hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
                
                /* Wait for transmission End*/
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Clear MTF */
                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

                if (hi2c->Rx_Size != 0) 
                {
                    if (hi2c->Rx_Count >= hi2c->Rx_Size) 
                    {
                        break;
                    }
                }
            }
        }
        
        /* Generate ACK */
        CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK);
        
        hi2c->Instance->SR = READ_REG(hi2c->Instance->SR);
    }
    /* Slave Transmit */
    else 
    {
       return HAL_ERROR;
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : receivd an amount of data in slave mode using IT mode.
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : pData: Pointer to a buffer to store data.
*@param : Size: Total size of data to receive .
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size)
{
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));

    /* Rx machine is running */
    if (hi2c->state != I2C_STATE_IDLE)
        return HAL_ERROR;

    /* Set Slave machine is receiving */
    hi2c->state = I2C_STATE_RX_DATA;
    
    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size   = Size;
    hi2c->Rx_Count = 0;
    
    /* Clear RX ADDR1 Flag */
    SET_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);
    /* RX ADDR1, RXNE, STOPF Interrupt Enable */
    SET_BIT(hi2c->Instance->CR, I2C_CR_RX_ADDR1_INT_EN | I2C_CR_RXNE_INT_EN | I2C_CR_STOPF_INTEN);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : receive an amount of data in slave mode using DMA mode.
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : pData: Pointer to a buffer to store data.
*@param : Size: Total size of data to receive .
*@return: HAL_StatusTypeDef
******************************************************************************/
#ifdef HAL_DMA_MODULE_ENABLED
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size)
{
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));

    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size   = Size;
    hi2c->Rx_Count = Size;

    /* DMA Enable */
    SET_BIT(hi2c->Instance->CR, I2C_CR_DMA_EN);

    /* Clear STOPF Interrupt Flag */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_STOPF);
    /* STOPF Interrupt Enable */
    SET_BIT(hi2c->Instance->CR, I2C_CR_STOPF_INTEN);

    HAL_DMA_Start(hi2c->HDMA_Rx, (uint32_t)&hi2c->Instance->DR, (uint32_t)hi2c->Rx_Buffer, hi2c->Rx_Size);

    return HAL_OK;
}

/******************************************************************************
*@brief : send an amount of data in slave mode using DMA mode.
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : pData: Pointer to a data buffer.
*@param : Size: Total size of data to send .
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size)
{
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));

    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size   = Size;
    hi2c->Tx_Count = Size;
    
    /* Must Set TXE_SEL In DMA Mode !!! */
    SET_BIT(hi2c->Instance->CR, I2C_CR_TXE_SEL);
    /* DMA Enable */
    SET_BIT(hi2c->Instance->CR, I2C_CR_DMA_EN);

    HAL_DMA_Start_IT(hi2c->HDMA_Tx, (uint32_t)hi2c->Tx_Buffer, (uint32_t)&hi2c->Instance->DR, hi2c->Tx_Size);

    return HAL_OK;
}
#endif
/******************************************************************************
*@brief : Write an amount of data in blocking mode to a specific memory address
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : DevAddress : Target device address
*@param : MemAddress : MemAddress Internal memory address
*@param : MemAddSize : MemAddSize Size of internal memory address
*@param : pData      : Pointer to data buffer
*@param : Size       : Amount of data to be sent
*@param : Timeout    : Timeout value
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t i;
    
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));

    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size   = Size;
    hi2c->Tx_Count = 0;
    
    /* Bus Busy */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY)) 
        return HAL_ERROR;
    
    /* Send Write Access Request */
    if (I2C_Master_Request_Write(hi2c, DevAddress,0) == HAL_OK)
    {
        /* If Memory address size is 8Bit */
        if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
        {
            /* Send Memory Address */
            hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
        }
        /* If Memory address size is 16Bit */ 
        else
        {
            /* Send Memory Address MSB*/
            hi2c->Instance->DR = I2C_MEM_ADD_MSB(MemAddress);
            /* Wait for transmission End*/
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
            /* Send Memory Address LSB*/
            hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
        }
        
        /* Wait for transmission End*/
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
        /* Clear MTF */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
        
        /* Get NACK */
        if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
        {
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
            
            /* Wait for the bus to idle */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK)  return HAL_ERROR;
            
            return HAL_ERROR;
        }
        /* Get ACK */
        else 
        {
            for (i = 0; i < hi2c->Tx_Size; i++)
            {
                /* Wait TXE Flag */
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_TXE, RESET, Timeout)!= HAL_OK)  return HAL_ERROR;
                
                /* Send Data */
                hi2c->Instance->DR = hi2c->Tx_Buffer[hi2c->Tx_Count++];
                
                /* Wait for transmission End*/
                 if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Clear MTF */
                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
                
                /* Get NACK */
                if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
                {
                    /* Generate Stop */
                    SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
                    
                    /* Wait for the bus to idle */
                    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK)  return HAL_ERROR;
                    return HAL_ERROR;
                }
            }
            
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
            
            /* Wait for the bus to idle */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK)  return HAL_ERROR;
            /* Check Device Ready */
            while(I2C_Check_Device_Ready(hi2c, DevAddress, Timeout) != HAL_OK);
        }
    }
    else
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Read an amount of data in blocking mode to a specific memory address
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : DevAddress : Target device address
*@param : MemAddress : MemAddress Internal memory address
*@param : MemAddSize : MemAddSize Size of internal memory address
*@param : pData      : Pointer to data buffer
*@param : Size       : Amount of data to read
*@param : Timeout    : Timeout value
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t i;
    
    /* Check I2C Parameter */
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));

    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size   = Size;
    hi2c->Rx_Count = 0;
    
    /* Bus Busy */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY)) 
        return HAL_ERROR;
    
    /* Send Write Access Request */
    if (I2C_Master_Request_Write(hi2c, DevAddress,0) == HAL_OK)
    {
        /* If Memory address size is 8Bit */
        if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
        {
            /* Send Memory Address */
            hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
        }
        /* If Memory address size is 16Bit */ 
        else
        {
            /* Send Memory Address MSB*/
            hi2c->Instance->DR = I2C_MEM_ADD_MSB(MemAddress);
            /* Wait for transmission End*/
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
            /* Send Memory Address LSB*/
            hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
        }
        
        /* Wait for transmission End*/
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
        /* Clear MTF */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
        
        /* Get NACK */
        if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
        {
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
            
            /* Wait for the bus to idle */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK)  return HAL_ERROR;
            
            return HAL_ERROR;
        }
        /* Get ACK */
        else
        {
            /* Send Write Read Request */
            if (I2C_Master_Request_Read(hi2c, DevAddress, Timeout) == HAL_OK)
            {
                /* Wait Master Transition receiving state */
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_TX_RX_FLAG, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Clear TX_RX_FLAG */
                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_TX_RX_FLAG);

                /* Generate ACK */
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK);

                for (i = 0; i < hi2c->Rx_Size - 1; i++)
                {
                    /* Wait RXNE Flag */
                    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RXNE, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                    /* Read Data */
                    hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
                    /* Wait for transmission End*/
                    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                    /* Clear MTF */
                    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
                }

                /* Prepare for Generate NACK */
                SET_BIT(hi2c->Instance->CR, I2C_CR_TACK);
                /* Prepare for Generate STOP */
                SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);

                /* Wait RXNE Flag */
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RXNE, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Read Data */
                hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
                /* Wait for transmission End*/
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Clear MTF */
                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

                /* Wait for the bus to idle */
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Generate ACK */
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK);
            }
            else 
            {
            /* Get NACK */
            return HAL_ERROR;
            }
        }
    }
    else
    {
    return HAL_ERROR;
    }

    return HAL_OK;
}

/******************************************************************************
*@brief : Get Slave Rx State
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*
*@return: Slave State
******************************************************************************/
uint8_t HAL_I2C_GetSlaveRxState(I2C_HandleTypeDef *hi2c)
{
    return hi2c->state;
}

/******************************************************************************
*@brief : Get Slave Tx State
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*
*@return: Slave State
******************************************************************************/
uint8_t HAL_I2C_GetSlaveTxState(I2C_HandleTypeDef *hi2c)
{
    return hi2c->state;
}

/******************************************************************************
*@brief : Set I2C Clock Speed
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : ClockSpeed: I2C Clock Speed
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef I2C_Set_Clock_Speed(I2C_HandleTypeDef *hi2c, uint32_t ClockSpeed)
{
    uint32_t APB_Clock;

    APB_Clock = HAL_RCC_GetPCLK1Freq();

    hi2c->Instance->CLK_DIV = APB_Clock / (4 * ClockSpeed) - 1;

    return HAL_OK;
}

/******************************************************************************
*@brief  This function handles I2C Communication Timeout.
*@param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
*        the configuration information for I2C module
*@param  Flag specifies the I2C flag to check.
*@param  Status The new Flag status (SET or RESET).
*@param  Timeout Timeout duration
*@param  Tickstart Tick start value
*@retval HAL status
******************************************************************************/
static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout)
{
    __IO uint32_t lu32_Timeout;
    /* have no timeout */
    if (Timeout == 0) 
    {
        while (__HAL_I2C_GET_FLAG(hi2c, Flag)==Status);
    }
    else 
    {
        lu32_Timeout = Timeout * 0xFF;
            
        while (__HAL_I2C_GET_FLAG(hi2c, Flag)==Status)
        {
            if (lu32_Timeout-- == 0) 
            {
                return HAL_ERROR;
            }
        }
    }
    return HAL_OK;
}

/******************************************************************************
*@brief : I2C Write Access Request
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : DevAddress: Device address
*@param : Timeout: Timeout value
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef I2C_Master_Request_Write(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout)
{
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));
    
    /* Generate Start */
    SET_BIT(hi2c->Instance->CR, I2C_CR_START);

    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_STARTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;

    /* Clear MTF, To Prevent Errors */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

    /* Send Device Address */
    hi2c->Instance->DR = DevAddress & 0xFE;

    /* Wait for transmission End*/
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
    /* Clear MTF */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

    /* Get NACK */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
    {
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
        
        /* Wait for the bus to idle */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
        
        return HAL_ERROR;
    }
    /* Get ACK */
    else 
    {
        return HAL_OK;
    }
}

/******************************************************************************
*@brief : I2C Read Access Request
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : DevAddress: Device address
*@param : Timeout: Timeout value
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef I2C_Master_Request_Read(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout)
{
    assert_param (IS_I2C_ALL_INSTANCE(hi2c->Instance));
    
    /* Generate Start */
    SET_BIT(hi2c->Instance->CR, I2C_CR_START);
    
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_STARTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;

    /* Clear MTF, To Prevent Errors */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
    
    /* Send Device Address */
    hi2c->Instance->DR = DevAddress | 0x01;
    
    /* Wait for transmission End */
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
    /* Clear MTF */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
    
    /* Get NACK */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
    {
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
        
        /* Wait for the bus to idle */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
        
        return HAL_ERROR;
    }
    /* Get ACK */
    else 
    {
        return HAL_OK;
    }
}

/******************************************************************************
*@brief : Check Device Ready
*         
*@param : hi2c: a pointer of I2C_HandleTypeDef structure which contains 
*         the configuration information for the specified I2C.
*@param : DevAddress: Device address
*@param : Timeout: Timeout value
*@return: HAL_StatusTypeDef
******************************************************************************/
static HAL_StatusTypeDef I2C_Check_Device_Ready(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout)
{
    /* Bus Busy */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY)) 
        return HAL_ERROR;

    /* Generate Start */
    SET_BIT(hi2c->Instance->CR, I2C_CR_START);
    
    /* Send Device Address */
    hi2c->Instance->DR = DevAddress;
    
    /* Wait for transmission End */
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
    /* Clear MTF */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
    
    /* Get NACK */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
    {
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
        
        /* Wait for the bus to idle */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
        
        return HAL_ERROR;
    }
    /* Get ACK */
    else 
    {
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
        
        /* Wait for the bus to idle */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
        
        return HAL_OK;
    }
}

#endif  //HAL_I2C_MODULE_ENABLED
