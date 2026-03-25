/******************************************************************************
*@file  : hal_efuse.h
*@brief : Header file of EFUSE HAL module.
******************************************************************************/

#ifndef __HAL_EFUSE_H__
#define __HAL_EFUSE_H__

#include "hal.h"

#define EFUSE_1US_TIMES 1000

/** @defgroup EFUSE FLAG
  * @{
  */
  
#define EFUSE_PREREAD_FLAG		EFUSE_SR_PREREAD_DONE
#define EFUSE_UNPG_FLAG			EFUSE_SR_UNPG
#define EFUSE_DONE_FLAG			EFUSE_SR_DONE

/**
  * @}
  */

/** @defgroup EFUSE MODE
  * @{
  */
  

#define EFUSE_RBYTE		(0U << EFUSE_CTRL_MODE_Pos)
#define EFUSE_WBYTE		(1U << EFUSE_CTRL_MODE_Pos)

/**
  * @}
  */


/** @defgroup  EFUSE Private Macros
  * @{
  */
  
#define IS_EFUSE_ALL_INSTANCE(__INSTANCE__)				(((__INSTANCE__) == EFUSE1) || ((__INSTANCE__) == EFUSE2))

#define IS_EFUSE_BYTE_ADDR(__ADDR__)					((__ADDR__ )< 0x100)

#define IS_EFUSE_BIT_ADDR(__ADDR__)						((__ADDR__)<0x800)

#define IS_EFUSE_FLAG(__FLAG__)						((__FLAG__) == EFUSE_PREREAD_FLAG || \
													(__FLAG__) == EFUSE_UNPG_FLAG || \
													(__FLAG__) == EFUSE_DONE_FLAG )
													
#define IS_EFUSE_CLR_FLAG(__FLAG__)						((__FLAG__) == EFUSE_UNPG_FLAG || \
													(__FLAG__) == EFUSE_DONE_FLAG )												
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/* HAL_EFUSE_Init */
HAL_StatusTypeDef HAL_EFUSE_Init(EFUSE_TypeDef *EFUSEx);

/* HAL_EFUSE_DeInit */
void HAL_EFUSE_DeInit(EFUSE_TypeDef *EFUSEx);

HAL_StatusTypeDef HAL_EFUSE_ReadByte(EFUSE_TypeDef *EFUSEx,uint16_t byteaddr,uint8_t* data,uint32_t timeout);
HAL_StatusTypeDef HAL_EFUSE_ReadBytes(EFUSE_TypeDef *EFUSEx,uint16_t byteaddr,uint8_t* data,uint32_t len,uint32_t timeout);
HAL_StatusTypeDef HAL_EFUSE_WriteByte(EFUSE_TypeDef *EFUSEx,uint16_t byteaddr,uint8_t data,uint32_t timeout);
HAL_StatusTypeDef HAL_EFUSE_WriteBytes(EFUSE_TypeDef *EFUSEx,uint16_t byteaddr,uint8_t* data,uint32_t len,uint32_t timeout);

void HAL_EFUSE_ReadDsr(EFUSE_TypeDef *EFUSEx,uint8_t str_addr,uint8_t len,uint8_t* data);
void HAL_EFUSE_RpEnable(EFUSE_TypeDef *EFUSEx);
void HAL_EFUSE_ByteWpEnable(EFUSE_TypeDef *EFUSEx);
void HAL_EFUSE_WpEnable(EFUSE_TypeDef *EFUSEx);

FlagStatus HAL_EFUSE_GetState(EFUSE_TypeDef *EFUSEx, uint32_t flag);
void HAL_EFUSE_ClrState(EFUSE_TypeDef *EFUSEx, uint32_t flag);

void HAL_EFUSE_PowerUpSpTimeCfg(EFUSE_TypeDef *EFUSEx, uint32_t us);
void HAL_EFUSE_PowerDownHdCfg(EFUSE_TypeDef *EFUSEx, uint32_t us);
void HAL_EFUSE_ProWaitTimeCfg(EFUSE_TypeDef *EFUSEx, uint32_t us);
void HAL_EFUSE_ProTimeCfg(EFUSE_TypeDef *EFUSEx, uint32_t us);
#endif
