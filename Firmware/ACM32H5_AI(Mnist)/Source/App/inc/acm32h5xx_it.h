/******************************************************************************
*@file  : acm32h5xx_it.h
*@brief : This file contains the headers of the interrupt handlers  
******************************************************************************/

#ifndef __ACM32H5XX_IT_H
#define __ACM32H5XX_IT_H

#include "hal.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#endif


