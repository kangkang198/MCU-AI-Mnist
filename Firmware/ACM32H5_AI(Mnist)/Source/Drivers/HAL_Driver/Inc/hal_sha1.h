/******************************************************************************
*@file  : hal_sha1.h
*@brief : Header file for SHA1 module.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __SHA1_H__
#define __SHA1_H__

#include "hal.h"

/**
  * @brief  SHA1 Configuration Structure definition
  */
typedef struct {
  uint32_t state[5];      // state (ABCD)
  uint32_t count[2];      // number of bits, modulo 2^64 (msb first) 
  uint8_t  buffer[64];    // input buffer
} SHA1_CTX;


/******************************************************************************
*@brief : SHA1 initialization. Begins an SHA1 operation, writing a new context.
*         
*@param : context: the pointer of sha1 context
*@return: None
******************************************************************************/
void HAL_SHA1_Init(SHA1_CTX *context);	

/******************************************************************************
*@brief : SHA1 block update operation. Continues an SHA1 message-digest operation, processing another message block, and updating the context.
*         
*@param : context   : context before and after transform
*@param : input     : input message
*@param : inputLen  : the byte length of input message
*@return: None
******************************************************************************/
void HAL_SHA1_Update(SHA1_CTX *context,uint8_t *input,uint32_t inputLen);

/******************************************************************************
*@brief : SHA1 finalization. Ends an MD5 message-digest operation, writing the message digest and zeroizing the context.
*         
*@param : digest    : message digest
*@param : context   : context before transform
*@return: None
******************************************************************************/
void HAL_SHA1_Final(uint8_t *digest, SHA1_CTX *context);
	
/******************************************************************************
*@brief : transform message to digest in SHA1 algorithm
*         
*@param : pDataIn    : start address of message to be tranformed
*@param : DataLen    : the byte length of message
*@param : pDigest    : start address of digest
*@return: None
******************************************************************************/
void HAL_SHA1_Hash(uint8_t *pDataIn,uint32_t DataLen,uint8_t *pDigest);
	
/**************************************************************************
* Function Name  : SHA_encode
* Description    : Encodes input (uint32_t) into output (unsigned char)[Big-Endian]
* Input          : - *input   : input data to be tranformed;
				 : -  len     : byte len of the input data(len is a multiple of 4);
* Output		 : - *output  : output data;
* Return         : None
**************************************************************************/
void SHA_encode (uint8_t *output, uint32_t *input, uint32_t len);
void SHA_memcpy (uint8_t *output,uint8_t *input, uint32_t len);
void SHA_memset (uint8_t *output, int value, uint32_t len);


#endif
