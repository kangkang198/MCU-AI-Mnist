/*
  ******************************************************************************
  * @file    HAL_Crc.c
  * @author  AisinoChip Firmware Team
  * @version V1.0.0
  * @date    2020
  * @brief   CRC HAL module driver.
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

#ifdef HAL_CRC_ENABLED

/******************************************************************************
*@brief : Initialize NFM
*@param : hnfm: pointer to the NFM handle
*@return: None
******************************************************************************/
void HAL_CRC_Init(CRC_HandleTypeDef *hcrc)
{
	__HAL_RCC_CRC_CLK_ENABLE();
	hcrc->Instance->CTRL = hcrc->Init.PolyRev | hcrc->Init.OutxorRev | hcrc->Init.InitRev | hcrc->Init.RsltRev |
	                       hcrc->Init.DataRev | hcrc->Init.PolyLen   | hcrc->Init.DataLen;

	hcrc->Instance->INIT = hcrc->Init.InitData;	
	hcrc->Instance->OUTXOR = hcrc->Init.OutXorData;
	hcrc->Instance->POLY = hcrc->Init.PolyData;
}

/******************************************************************************
*@brief : Calculate the crc calue of input data
*@param : hcrc: pointer to the CRC handle
*@return: CRC value
******************************************************************************/
uint32_t HAL_CRC_Calculate(CRC_HandleTypeDef *hcrc)
{
    int crc_cnt;
  	__HAL_RCC_CRC_CLK_ENABLE();
    
    if(CRC_DATA_LEN_2B == hcrc->Init.DataLen)
    {
        crc_cnt = hcrc->CRC_Data_Len>>1;       
        while(crc_cnt--)
        {
            hcrc->Instance->DATA = *((uint16_t*)hcrc->CRC_Data_Buff);
            hcrc->CRC_Data_Buff +=2;
        }
    }
    else if(CRC_DATA_LEN_4B == hcrc->Init.DataLen)
    {
        crc_cnt = hcrc->CRC_Data_Len>>2;
        while(crc_cnt--)
        {
            hcrc->Instance->DATA = *((uint32_t*)hcrc->CRC_Data_Buff);
            hcrc->CRC_Data_Buff +=4;
        }
    }
    else
    {
        crc_cnt = hcrc->CRC_Data_Len;
        while(crc_cnt--)
        {
            hcrc->Instance->DATA = *((uint8_t*)hcrc->CRC_Data_Buff++);
        }
    }
    __HAL_RCC_CRC_CLK_DISABLE();
	return (hcrc->Instance->DATA);

}

#endif


