/******************************************************************************
*@file  : hal_hrng.h
*@brief : HRNG module driver header file.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __HRNG_H__
#define __HRNG_H__

#include "hal.h" 

/******************************************************************************
*@brief : Initialize the hrng module
*            
*@return: None
******************************************************************************/
void HAL_HRNG_Init(void);

/******************************************************************************
*@brief : DeInitializes the hrng module
*            
*@return: None
******************************************************************************/
void HAL_HRNG_DeInit(void);

/******************************************************************************
*@brief : get 8bit random number
*            
*@return: 8 bit random number
******************************************************************************/
uint8_t HAL_HRNG_GetHrng_8(void);

/******************************************************************************
*@brief : get 32bit random number
*            
*@return: 32 bit random number
******************************************************************************/
uint32_t HAL_HRNG_GetHrng_32(void);

/******************************************************************************
*@brief : get random number
*         
*@param : hdata    : the start address of random number
*@param : byte_len £ºthe byte length of random number       
*@return: 0        : hrng data is ok
*         1        : hrng data is bad
******************************************************************************/
uint8_t HAL_HRNG_GetHrng(uint8_t *hdata, uint32_t byte_len);

#endif



