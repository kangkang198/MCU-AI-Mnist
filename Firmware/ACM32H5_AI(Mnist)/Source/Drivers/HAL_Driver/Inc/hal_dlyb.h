/*
  ******************************************************************************
  * @file    HAL_DLYB.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of DLYB HAL module.
  ******************************************************************************
*/
#ifndef __HAL_DLYB_H__
#define __HAL_DLYB_H__

#include "hal.h"

/******************************************************************************/
/*                    Peripheral Registers Bits Definition                    */
/******************************************************************************/



#define DLYB_SEL_MAX							12
#define DLYB_UINT_MAX							128


#define DEN_ENABLE								(1<<0)
#define SEN_ENABLE								(1<<1)




HAL_StatusTypeDef HAL_DLYB_Enable(DLYB_TypeDef *hdlyb);
HAL_StatusTypeDef HAL_DLYB_Disable(DLYB_TypeDef *hdlyb);





#endif
