/*
  ******************************************************************************
  * @file    hal_nand.c
  * @author  AisinoChip Firmware Team
  * @version V1.0.0
  * @date    2020
  * @brief   Nand HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (UART).
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 AisinoChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "hal.h" 

#ifdef HAL_NAND_MODULE_ENABLED

volatile uint8_t flag_nand_int = 0;
void WaitFlashReady(void);
/******************************************************************************
*@brief : FMC callback.
*@ret   : None
******************************************************************************/
__weak void HAL_FMC_NAND_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FMC_NAND_Callback could be implemented in the user file
   */
}

/******************************************************************************
*@brief : BCH callback.
*@ret   : None
******************************************************************************/
__weak void HAL_BCH_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_BCH_Callback could be implemented in the user file
   */
}


void FMC_NAND_IRQHandler(void)
{
    HAL_FMC_NAND_Callback();
}

void BCH_IRQHandler(void)
{
    HAL_BCH_Callback();  
}


/******************************************************************************
*@brief : Initialize nand according to the specified parameters in hnand.
*         
*@param : hnand: handle with nand parameters.
*@return: HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_Init(FMC_NAND_HandleTypeDef *hnand)
{    
    assert_param (IS_FMC_NAND_ALL_INSTANCE(hnand->Instance));   
    assert_param (IS_FMC_NAND_EDO_EN(hnand->Init.EDO_EN));
    assert_param (IS_FMC_NAND_ENDIAN_EN(hnand->Init.ENDIAN));
    assert_param (IS_FMC_NAND_FCE_EN(hnand->Init.FCE));

	__HAL_RCC_FMC_CLK_ENABLE();
    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_FMC_NAND_MspInit(hnand);
    
    hnand->Instance->CTRL = hnand->Init.EDO_EN | hnand->Init.RBN_INTEN | hnand->Init.ENDIAN | hnand->Init.FWP | hnand->Init.FCE;
    hnand->Instance->WST  = hnand->Init.TADL | hnand->Init.TRHW | hnand->Init.TWHR | hnand->Init.TREH | hnand->Init.TRP | hnand->Init.TWH | hnand->Init.TWP;

    return HAL_OK;    
}

/******************************************************************************
*@brief : Initialize the nand MSP: CLK, GPIO, NVIC
*         
*@param : hnand: handle with nand parameters.
*@return: None
******************************************************************************/
__weak void HAL_FMC_NAND_MspInit(FMC_NAND_HandleTypeDef *hnand)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    GPIO_InitTypeDef GPIO_InitStructure;
  
    /* 使能nand相关的GPIO时钟 */ 
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    /*-- GPIO 配置 -----------------------------------------------------*/

    /* 通用 GPIO 配置 */       
    GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;//配置为复用功能
    GPIO_InitStructure.Pull      = GPIO_PULLUP;
    GPIO_InitStructure.Alternate = GPIO_FUNCTION_10;//AF10   
	GPIO_InitStructure.Drive = GPIO_DRIVE_LEVEL7;	

    /*D[0:7]数据信号线 针对引脚配置*/
    GPIO_InitStructure.Pin = FMC_NAND_D0_GPIO_PIN; 
    HAL_GPIO_Init(FMC_NAND_D0_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = FMC_NAND_D1_GPIO_PIN; 
    HAL_GPIO_Init(FMC_NAND_D1_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = FMC_NAND_D2_GPIO_PIN; 
    HAL_GPIO_Init(FMC_NAND_D2_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = FMC_NAND_D3_GPIO_PIN; 
    HAL_GPIO_Init(FMC_NAND_D3_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = FMC_NAND_D4_GPIO_PIN; 
    HAL_GPIO_Init(FMC_NAND_D4_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = FMC_NAND_D5_GPIO_PIN; 
    HAL_GPIO_Init(FMC_NAND_D5_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = FMC_NAND_D6_GPIO_PIN; 
    HAL_GPIO_Init(FMC_NAND_D6_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = FMC_NAND_D7_GPIO_PIN; 
    HAL_GPIO_Init(FMC_NAND_D7_GPIO_PORT, &GPIO_InitStructure);

    /*控制信号线*/
    GPIO_InitStructure.Pin = FMC_NAND_CEN_GPIO_PIN;            //片选信号 
    HAL_GPIO_Init(FMC_NAND_CEN_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = FMC_NAND_WEN_GPIO_PIN;            //WEN
    HAL_GPIO_Init(FMC_NAND_WEN_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = FMC_NAND_REN_GPIO_PIN;            //REN
    HAL_GPIO_Init(FMC_NAND_REN_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin = FMC_NAND_CLE_GPIO_PIN;            //CLE
    HAL_GPIO_Init(FMC_NAND_CLE_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin = FMC_NAND_ALE_GPIO_PIN;            //ALE
    HAL_GPIO_Init(FMC_NAND_ALE_GPIO_PORT, &GPIO_InitStructure);
		
		
	GPIO_InitStructure.Alternate = GPIO_FUNCTION_11;      //AF11

    
    GPIO_InitStructure.Pin = FMC_NAND_CEN_GPIO_PIN;            //片选信号 
    HAL_GPIO_Init(FMC_NAND_CEN_GPIO_PORT, &GPIO_InitStructure);
		
    GPIO_InitStructure.Pin = FMC_NAND_RBN_GPIO_PIN;            //RBN
    HAL_GPIO_Init(FMC_NAND_RBN_GPIO_PORT, &GPIO_InitStructure);
		
}

/******************************************************************************
*@brief : Wait for Flash RBN rising event
*         
*@param : hnand: handle with nand parameters.
*@return: None
******************************************************************************/
static HAL_StatusTypeDef HAL_FMC_NAND_WaitFlashReady(FMC_NAND_HandleTypeDef *hnand)
{
    assert_param (IS_FMC_NAND_ALL_INSTANCE(hnand->Instance));
    
    /* wait nand not busy*/ 
    while(READ_BIT(hnand->Instance->STATUS, FMC_NAND_STATUS_POS_RBN_0)  == 0){;} 
    SET_BIT(hnand->Instance->STATUS, FMC_NAND_STATUS_POS_RBN_0);
  
	return HAL_OK;
}

/******************************************************************************
*@brief : Reset Nand Flash
*         
*@param : hnand: handle with nand parameters.
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_FlashReset(FMC_NAND_HandleTypeDef *nand)
{
    assert_param (IS_FMC_NAND_ALL_INSTANCE(nand->Instance));
    
    /* clear CE0 */
    CLEAR_BIT(nand->Instance->CTRL, FMC_NAND_CTRL_FCE_0);
    /* write RESET CMD */    
    nand->Instance->CMD = FMC_NAND_CMD_RESET;
	HAL_FMC_NAND_WaitFlashReady(nand);

    /* release CE0 */
    SET_BIT(nand->Instance->CTRL, FMC_NAND_CTRL_FCE_0);    
    return HAL_OK;
}

/******************************************************************************
*@brief : Read ID from Nand Flash
*         
*@param : hnand: handle with nand parameters.
*@param : rdata: start address to store ID
*@param : lenth: ID length
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_FlashGetID(FMC_NAND_HandleTypeDef *hnand, uint8_t rdata[], uint8_t lenth)
{
	uint8_t i;
    
    assert_param (IS_FMC_NAND_ALL_INSTANCE(hnand->Instance));
    
    /* clear CE0 */
    CLEAR_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0);
    
    /* write READ ID CMD */    
    hnand->Instance->CMD = FMC_NAND_CMD_ID;
    /* write address 00 */   
    hnand->Instance->ADDR = 0x00;    

	for(i = 0; i < lenth; i++)
	{
		*rdata++ = FMC_NAND->FMC_NAND_NECCDATA.FMC_NAND_NECCDATA_CH8; 
	}
    
    /* release CE0 */
    SET_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0); 
   
    return HAL_OK;
}

/******************************************************************************
*@brief : Erase a block
*         
*@param : hnand: handle with nand parameters.
*@param : BlockAddr: start address of the block to erase
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_FlashErase(FMC_NAND_HandleTypeDef *hnand, uint32_t BlockAddr)
{
    assert_param (IS_FMC_NAND_ALL_INSTANCE(hnand->Instance));
    
    /* clear CE0 */
    CLEAR_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0);

	hnand->Instance->CMD = FMC_NAND_CMD_ERASE1;  
	hnand->Instance->ADDR = BlockAddr & 0xff;
	hnand->Instance->ADDR = (BlockAddr >> 8) & 0xff;
	hnand->Instance->ADDR = (BlockAddr >> 16) & 0xff;
	
	hnand->Instance->CMD = FMC_NAND_CMD_ERASE2;
	HAL_FMC_NAND_WaitFlashReady(hnand);
    
    /* release CE0 */
    SET_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0); 
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Program one sector(512 bytes) 
*
*@param : hnand: handle with nand parameters.
*@param : RowAddr: row start address
*@param : ColumnAddr: column start address
*@param : wdata: start address of data to program
*@param : ecc_en:select the mode of program 
          BCH_ECC_MODE_EN : program with ecc mode
          BCH_ECC_MODE_DIS: progran with no ecc mode
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_Flash_Program(FMC_NAND_HandleTypeDef *hnand, uint32_t RowAddr, uint16_t ColumnAddr, uint8_t wdata[], uint8_t ecc_en)
{
    uint32_t i;
    uint32_t temp;
    assert_param (IS_FMC_NAND_ALL_INSTANCE(hnand->Instance));
    
    /* clear CE0 */
    CLEAR_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0);
    
    hnand->Instance->CMD = FMC_NAND_CMD_PROGRAM1;

    hnand->Instance->ADDR = (uint8_t)ColumnAddr;        // Column address
    hnand->Instance->ADDR = (uint8_t)(ColumnAddr >> 8); // Column address
    hnand->Instance->ADDR = (uint8_t)RowAddr;           // Page address
    hnand->Instance->ADDR = (uint8_t)(RowAddr >> 8);    // Page address
    hnand->Instance->ADDR = (uint8_t)(RowAddr >> 16);   // Page address
	
    /* ECC Channel */
    if(BCH_ECC_MODE_EN == ecc_en)
    {
        /* BCH encode mode */
        CLEAR_BIT(hnand->Instance->BCH_CTRL, FMC_NAND_BCH_CTRL_MODE);
        
        /* Reset Encode Channel */  //reset encode channel
        SET_BIT(hnand->Instance->BCH_STATUS, FMC_NAND_BCH_STATUS_ENCODE_CLR); 

        for(i = 0; i < (BCH_SECTOR_SIZE + BCH_INF_SIZE); i++)
        {
            hnand->Instance->FMC_NAND_ECCDATA.FMC_NAND_ECCDATA_CH8 = wdata[i];
        }

        /* Reset BCH Code PTR */
        hnand->Instance->BCH_CODEPTR = 0;
        for(i = 0; i < BCH_ECC_SIZE; i++)
        {
            hnand->Instance->FMC_NAND_ECCDATA.FMC_NAND_ECCDATA_CH8 = FMC_NAND->BCH_CODE.FMC_NAND_BCHCODE_CH8;       
        }
    }
    else
    {
        for(i = 0; i < BCH_SECTOR_SIZE; i++)
        {
            hnand->Instance->FMC_NAND_NECCDATA.FMC_NAND_NECCDATA_CH8 = wdata[i]; ;//no ecc channel
        }
    }
    hnand->Instance->CMD = FMC_NAND_CMD_PROGRAM2;    
	HAL_FMC_NAND_WaitFlashReady(hnand);

    /* release CE0 */
    SET_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0); 
    
    return HAL_OK;  
}

/******************************************************************************
*@brief : Program one sector(512 bytes) using necc channel and ecc data
*
*@param : hnand: handle with nand parameters.
*@param : RowAddr: row start address
*@param : ColumnAddr: column start address
*@param : wdata: start address of data to program
*@param : pEccByte: input ecc data
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_Flash_Program_NECC_with_ECC_CODE(FMC_NAND_HandleTypeDef *hnand, uint32_t RowAddr, uint16_t ColumnAddr, uint8_t wdata[], uint8_t pEccByte[])
{
    uint32_t i;
    uint32_t temp;
    assert_param (IS_FMC_NAND_ALL_INSTANCE(hnand->Instance));
    
    /* clear CE0 */
    CLEAR_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0);
    
    hnand->Instance->CMD = FMC_NAND_CMD_PROGRAM1;

    hnand->Instance->ADDR = (uint8_t)ColumnAddr;        // Column address
    hnand->Instance->ADDR = (uint8_t)(ColumnAddr >> 8); // Column address
    hnand->Instance->ADDR = (uint8_t)RowAddr;           // Page address
    hnand->Instance->ADDR = (uint8_t)(RowAddr >> 8);    // Page address
    hnand->Instance->ADDR = (uint8_t)(RowAddr >> 16);   // Page address
	

    for(i = 0; i < (BCH_SECTOR_SIZE + BCH_INF_SIZE); i++)
    {
        hnand->Instance->FMC_NAND_NECCDATA.FMC_NAND_NECCDATA_CH8 = wdata[i]; ;//write data using no ecc channel
    }
    for(i = 0; i < BCH_ECC_SIZE; i++)
    {
        hnand->Instance->FMC_NAND_NECCDATA.FMC_NAND_NECCDATA_CH8 = pEccByte[i]; ;//write ecc data
    }
    
    hnand->Instance->CMD = FMC_NAND_CMD_PROGRAM2;    
	HAL_FMC_NAND_WaitFlashReady(hnand);

    /* release CE0 */
    SET_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0); 
    
    return HAL_OK;  
}


/******************************************************************************
*@brief : Read one sector(512 bytes) 
*         
*@param : hnand: handle with nand parameters.
*@param : RowAddr: row start address
*@param : ColumnAddr: column start address
*@param : rdata: start address of read data
*@param : ecc_en:select the mode of read 
          BCH_ECC_MODE_EN : read with ecc mode
          BCH_ECC_MODE_DIS: read with no ecc mode
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_FlashRead(FMC_NAND_HandleTypeDef *hnand, uint32_t RowAddr, uint16_t ColumnAddr, uint8_t rdata[], uint8_t auto_sel)
{
    int i;
    
    assert_param (IS_FMC_NAND_ALL_INSTANCE(hnand->Instance));
         
    /* clear CE0 */
    CLEAR_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0);
    
    hnand->Instance->CMD = FMC_NAND_CMD_READ1;
    hnand->Instance->ADDR = (uint8_t)ColumnAddr;         // Column address
    hnand->Instance->ADDR = (uint8_t)(ColumnAddr >> 8);  // Column address
    hnand->Instance->ADDR = (uint8_t)RowAddr;            // Page address
    hnand->Instance->ADDR = (uint8_t)(RowAddr >> 8);     // Page address
    hnand->Instance->ADDR = (uint8_t)(RowAddr >> 16);    // Page address

    hnand->Instance->CMD = FMC_NAND_CMD_READ2;

	HAL_FMC_NAND_WaitFlashReady(hnand);
 
    if(BCH_ECC_MODE_EN == auto_sel)
    {
        /* BCH decode mode */
        SET_BIT(hnand->Instance->BCH_CTRL, FMC_NAND_BCH_CTRL_MODE);
        
        /* Auto Correct */
        SET_BIT(hnand->Instance->BCH_CTRL, FMC_NAND_BCH_CTRL_AUTO_CORRECT);
        
        /* SRAM Base */      
        hnand->Instance->BCH_BASEADDR = (uint32_t)rdata;
        
        /* ECC Channel */        
        for(i = 0; i < (BCH_SECTOR_SIZE + BCH_INF_SIZE + BCH_ECC_SIZE); i++) 
        {
            rdata[i] = hnand->Instance->FMC_NAND_ECCDATA.FMC_NAND_ECCDATA_CH8; 
        }
        
        /* Wait Correct Done */           
        while(READ_BIT(hnand->Instance->BCH_STATUS, FMC_NAND_BCH_STATUS_CORRECT_DONE)  == 0){;}
        /* Clear Flag */             
        SET_BIT(hnand->Instance->BCH_STATUS, FMC_NAND_BCH_STATUS_CORRECT_DONE);
            
        if(READ_BIT(hnand->Instance->BCH_STATUS, FMC_NAND_BCH_STATUS_BCH_FAIL))
        {
            /* Clear Error Flag */ 
            SET_BIT(hnand->Instance->BCH_STATUS, FMC_NAND_BCH_STATUS_BCH_FAIL);
            /* release CE0 */
            SET_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0); 
            
            return HAL_ERROR;             
        }
    }
    else
    {
		for(i = 0; i < BCH_SECTOR_SIZE; i++) //
		{
			rdata[i] = FMC_NAND->FMC_NAND_NECCDATA.FMC_NAND_NECCDATA_CH8;//REG_NFM_NECC_CH8;
		}

    }    

    /* release CE0 */
    SET_BIT(hnand->Instance->CTRL, FMC_NAND_CTRL_FCE_0);     
    return HAL_OK;  
}

/******************************************************************************
*@brief : Reset ECC Channel
*  
*@return: None
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NAND_Reset_ECC_Channel(FMC_NAND_HandleTypeDef *hnand)
{
    /* Reset Channel */
    SET_BIT(hnand->Instance->BCH_CTRL, FMC_NAND_BCH_CTRL_RESET_CHANNEL);
    return HAL_OK; 
}

#endif

