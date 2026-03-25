/******************************************************************************
*@file  : hal_sha1.h
*@brief : Header file for SHA256 module.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __SHA256_H__
#define __SHA256_H__

#include "hal.h"


/**
  * @brief  SHA256 Configuration Structure definition
  */
typedef struct {
  uint32_t state[8];        //state (ABCD)
  uint32_t count[2];        // number of bits, modulo 2^64 (msb first) 
  uint8_t  buffer[64];      // input buffer
} SHA256_CTX;

/**********************************************************
*	extern functions
***********************************************************/
void SHA_memcpy (uint8_t *output,uint8_t *input, uint32_t len);
void SHA_memset (uint8_t *output, int value, uint32_t len);
void SHA_encode (uint8_t *output, uint32_t *input, uint32_t len);
/**********************************************************
*	extern variable
***********************************************************/
extern const unsigned char PADDING[128];

/******************************************************************************
*@brief : SHA256 initialization. Begins an SHA256 operation, writing a new context.
*         
*@param : context: the pointer of sha1 context
*@return: None
******************************************************************************/
void HAL_SHA256_Init(SHA256_CTX *context);
	
/******************************************************************************
*@brief : SHA256 block update operation. Continues an SHA256 message-digest operation, processing another message block, and updating the context.
*         
*@param : context   : context before and after transform
*@param : input     : input message
*@param : inputLen  : the byte length of input message
*@return: None
******************************************************************************/
void HAL_SHA256_Update(SHA256_CTX *context, uint8_t *input,uint32_t inputLen);

/******************************************************************************
*@brief : SHA256 finalization. Ends an MD5 message-digest operation, writing the message digest and zeroizing the context.
*         
*@param : digest    : message digest
*@param : context   : context before transform
*@return: None
******************************************************************************/
void HAL_SHA256_Final(uint8_t *digest, SHA256_CTX *context);

/******************************************************************************
*@brief : transform message to digest in SHA256 algorithm
*         
*@param : pDataIn    : start address of message to be tranformed
*@param : DataLen    : the byte length of message
*@param : pDigest    : start address of digest
*@return: None
******************************************************************************/
void HAL_SHA256_Hash(uint8_t *pDataIn,uint32_t DataLen,uint8_t *pDigest);

#endif
