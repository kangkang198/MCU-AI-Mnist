/*
  ******************************************************************************
  * @file    System_Accelerate.h
  * @author  AisinoChip Firmware Team
  * @version V1.0.0
  * @date    2020
  * @brief   MCU Accelerate Peripheral Access Layer System header File.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 AisinoChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __SYSTEM_ACCELERATE_H__
#define __SYSTEM_ACCELERATE_H__

//#include "cmsis_armclang.h"
#include "stdint.h"

/* System_EnableIAccelerate */ 
void System_EnableIAccelerate(void);

/* System_DisableIAccelerate */
void System_DisableIAccelerate(void);

/* System_InvalidateIAccelerate */
void System_InvalidateIAccelerate(void);

void System_InvalidateIAccelerate_by_Addr (volatile void *addr, int32_t isize);
	
/* System_EnableDAccelerate */
void System_EnableDAccelerate(void);

/* System_DisableDAccelerate */
void System_DisableDAccelerate(void);

/* System_InvalidateDAccelerate */
void System_InvalidateDAccelerate(void);

/* System_CleanDAccelerate */
void System_CleanDAccelerate(void);

/* System_CleanInvalidateDAccelerate */
void System_CleanInvalidateDAccelerate(void);

/* System_InvalidateDAccelerate_by_Addr */
void System_InvalidateDAccelerate_by_Addr (volatile void *addr, int32_t dsize);

void System_CleanDAccelerate_by_Addr (volatile void *addr, int32_t dsize);

/* System_CleanInvalidateDAccelerate_by_Addr */
void System_CleanInvalidateDAccelerate_by_Addr (volatile void *addr, int32_t dsize);

#endif

