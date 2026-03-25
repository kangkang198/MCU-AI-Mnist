/******************************************************************************
* @file  :  hal_uart_7816m.h
* @brief :  header file
* @ver   :  V1.0.0
* @date  :  2020
******************************************************************************/
#ifndef __HAL_UART_7816M_H__
#define __HAL_UART_7816M_H__

#include "acm32h5xx_hal_conf.h"


HAL_StatusTypeDef HAL_UART_7816M_Init(UART_HandleTypeDef *huart, uint32_t clk_psc, uint32_t guard_time);
HAL_StatusTypeDef HAL_UART_7816M_Receive(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size, uint32_t timeout);
HAL_StatusTypeDef HAL_UART_7816M_Transmit(UART_HandleTypeDef *huart, uint8_t *buf, uint32_t size);

#endif
