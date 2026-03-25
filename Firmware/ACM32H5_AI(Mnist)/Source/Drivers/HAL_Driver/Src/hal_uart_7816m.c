/******************************************************************************
* @file  :  hal_uart_7816m.c
* @brief :  UART HAL module driver for ISO7816 Master.
*          This file provides firmware functions to manage the following
*          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (UART).
* @ver   :  V1.0.0
* @date  :  2020
******************************************************************************/
#include "hal.h" 

#ifdef HAL_UART_7816M_MODULE_ENABLED

/******************************************************************************
*@brief : Config baudrate of 7816 clk 
*         
*@param : uartx_instance: which uart instance
*@param : clk_hz: uart module clk freq
*@param : baud_rate: 7816 clk baudrate
*@return: None
******************************************************************************/
static void uart_set_baud_rate(UART_TypeDef *uartx_instance, uint32_t clk_hz, uint32_t baud_rate)
{
    uint32_t temp, divider, remainder, fraction;

    temp = 16 * baud_rate;
    divider = clk_hz / temp;
    remainder =    clk_hz % temp;
    temp = 1 + (128 * remainder) / temp;
    fraction = temp / 2;

    uartx_instance->BRR = (divider<<6)| fraction;
}

/******************************************************************************
*@brief : Initialize the UART MSP: CLK, GPIO, NVIC
*         
*@param : huart: uart handle with UART parameters.
*@return: None
******************************************************************************/
__weak void HAL_UART_7816M_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef    GPIO_InitStruct ={0}; 

    UART_TypeDef *instance = huart->Instance;

    if(instance == USART1)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();
        
        /*7816 IO: PA9*/
        GPIO_InitStruct.Pin       = GPIO_PIN_9;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Drive     = GPIO_DRIVE_LEVEL3;
        GPIO_InitStruct.Alternate = GPIO_FUNCTION_1;       
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /*7816 RST: PA10*/
        GPIO_InitStruct.Pin       = GPIO_PIN_10;
        GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Drive     = GPIO_DRIVE_LEVEL3;
        GPIO_InitStruct.Alternate = GPIO_FUNCTION_1;       
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /*7816 CLK: PA8*/
        GPIO_InitStruct.Pin       = GPIO_PIN_8;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Drive     = GPIO_DRIVE_LEVEL3;
        GPIO_InitStruct.Alternate = GPIO_FUNCTION_6;       
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        NVIC_ClearPendingIRQ(USART1_IRQn);
        NVIC_EnableIRQ(USART1_IRQn);    
    }
    else if(instance == USART2)
    {
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_USART2_CLK_ENABLE();


        /*7816 IO: PB3*/
        GPIO_InitStruct.Pin       = GPIO_PIN_3;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Drive     = GPIO_DRIVE_LEVEL3;
        GPIO_InitStruct.Alternate = GPIO_FUNCTION_5;       
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


        /*7816 RST: PB4*/
        GPIO_InitStruct.Pin       = GPIO_PIN_4;
        GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Drive     = GPIO_DRIVE_LEVEL3;
        GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;       
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /*7816 CLK: PB5*/
        GPIO_InitStruct.Pin       = GPIO_PIN_5;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Drive     = GPIO_DRIVE_LEVEL3;
        GPIO_InitStruct.Alternate = GPIO_FUNCTION_5;       
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        NVIC_ClearPendingIRQ(USART2_IRQn);
        NVIC_EnableIRQ(USART2_IRQn);    
    }
}

/******************************************************************************
*@brief : Initialize the UART 7816 Master mode 
            according to the specified parameters in huart.
*         
*@param : huart: uart handle with UART parameters.
*@param : clk_psc: clk divison for 7816 clock output.
*@param : guard_time: 7816 Guard Time.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_7816M_Init(UART_HandleTypeDef *huart, uint32_t clk_psc, uint32_t guard_time)
{
    uint32_t uart_clk_hz, j = 0;
	volatile uint8_t temp; 
	
    UART_TypeDef *instance = huart->Instance;
    
    if(!huart)
    {
        return HAL_ERROR;
    }
		
    if (USART1 == huart->Instance) 
    {
        uart_clk_hz = HAL_RCC_GetPCLK2Freq(); 
    }
    else
    {
        uart_clk_hz = HAL_RCC_GetPCLK1Freq();  
    }

    HAL_UART_7816M_MspInit(huart);

    
    __HAL_UART_DISABLE(huart);
    
    uart_set_baud_rate(instance, uart_clk_hz, huart->Init.BaudRate);

    
    instance->CR3 = UART_WORDLENGTH_8B | UART_STOPBITS_1 | UART_PARITY_NONE | UART_TX_FIFO_1_16 | UART_RX_FIFO_1_16;  //FIFO off
        
    SET_BIT(instance->CR3, UART_CR3_PEN);     //1 parity bit
    SET_BIT(instance->CR3, UART_CR3_EPS);     //even
    
    SET_BIT(instance->CR2, UART_CR2_SCEN | UART_CR2_NACK | UART_CR2_HDSEL);   //SC EN, NACK, 1 wire mode
    
    MODIFY_REG(instance->GTPR, UART_GTPR_PSC, (clk_psc << UART_GTPR_PSC_Pos)); //PSC 48MHz/((5+1)*2) = 12 about 4MHz

    MODIFY_REG(instance->GTPR, UART_GTPR_GT, (guard_time << UART_GTPR_GT_Pos));
    
    instance->CR1 = (UART_CR1_RXE | UART_CR1_TXE |UART_CR1_UARTEN); //enable uart,rxe
    
    return HAL_OK;
		
}

/******************************************************************************
*@brief : Receive an amount of data by loop mode within timeout period.
*         
*@param : huart: uart handle with UART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to receive.
*@param : timeout: BCNT value
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_7816M_Receive(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size, uint32_t timeout)
{
    uint8_t i;
    uint8_t errortimes;
    volatile uint8_t temp; 
    HAL_StatusTypeDef err =  HAL_OK;

    errortimes = 0;
    
    SET_BIT(huart->Instance->CR1, UART_CR1_RXE);

    huart->Instance->BCNT &= ~0x0A000000;	//clear DEM and AUTO_START_EN
    huart->Instance->BCNT = (huart->Instance->BCNT & ~0xFFFFFF) | timeout;
    huart->Instance->BCNT |= 0x03000000;
    
    huart->ErrorCode = HAL_UART_ERROR_NONE;

    for (i = 0; i < size;)
    {
        while (((huart->Instance->FR & UART_FR_RXFE)==UART_FR_RXFE) && ((huart->Instance->ISR & UART_ISR_PEI)==0))//No data and no Parity Error		
        {
            if(huart->Instance->ISR & UART_ISR_BCNTI)
            {
                SET_BIT(huart->Instance->ISR, UART_ISR_BCNTI);
                err = HAL_TIMEOUT;
                goto rxend;
            }
        }
        if((huart->Instance->ISR & UART_ISR_PEI))//PE error
        {
                huart->Instance->ISR = UART_ISR_PEI;
                errortimes++;
                if(errortimes > 3)
                {
                    huart->ErrorCode |= HAL_UART_ERROR_PE;
                    err = HAL_ERROR;
                    goto rxend;
                }
                
                while ((huart->Instance->FR & UART_FR_RXFE)==UART_FR_RXFE) //No data
                {	
                        ;
                }
                
                while ((huart->Instance->FR & UART_FR_RXFE)!= UART_FR_RXFE) //have data
                {	
                        temp = huart->Instance->DR;
                }			
        }
        else
        {	            
                buf[i] = huart->Instance->DR;
                i++;
        }
    }

rxend:
    
    huart->RxCount = i;
    return err;
}

/******************************************************************************
*@brief : Send an amount of data by loop mode within timeout period.
*         
*@param : huart: uart handle with UART parameters.
*@param : buf: Pointer to data buffer.
*@param : size: Amount of data elements to be sent.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_UART_7816M_Transmit(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size)
{
    uint8_t i;
    uint8_t errortimes;
    HAL_StatusTypeDef err = HAL_OK;

    CLEAR_BIT(huart->Instance->CR1, UART_CR1_RXE);

    huart->TxCount = 0;
    
    for (i = 0; i < size; i++)
    {
        huart->Instance->DR = *buf++;
        
        while (huart->Instance->FR & UART_FR_TXFF)
        {
            if (huart->Instance->ISR & UART_ISR_FEI)  //FE error
            {
                err =  HAL_ERROR;
                goto txend;
            }
        }
    }
    
txend: 
    
    
    
    huart->TxCount = i;
    
    return err;
}

#endif  //HAL_UART_7816M_MODULE_ENABLED
