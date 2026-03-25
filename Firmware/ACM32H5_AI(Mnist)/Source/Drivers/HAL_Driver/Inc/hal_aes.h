/******************************************************************************
*@file  : hal_aes.h
*@brief : AES module driver header file.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __AES_H__
#define __AES_H__

#include "hal.h"

#define AES_ENCRYPTION   		1
#define AES_DECRYPTION   		0
#define AES_ECB_MODE	   		0
#define AES_CBC_MODE	   		1 
#define AES_CTR_MODE	   		2 

#define AES_SWAP_ENABLE  		1
#define AES_SWAP_DISABLE 		0

#define AES_NORMAL_MODE   	    0x12345678
#define AES_SECURITY_MODE 	    0

#define AES_ADDR_AUTO_ENABLE    1
#define AES_ADDR_AUTO_DISABLE   0

#define AES_KEY_128             0
#define AES_KEY_192             1
#define AES_KEY_256             2

#define AES_FAIL                0x00
#define AES_PASS                0xa59ada68 

/******************************************************************************
*@brief : set key for aes
*@param : keyin   : pointer to buffer of key
*@param : key_len : select length of key(AES_KEY_128/ AES_KEY_192/ AES_KEY_256)
*@param : swap_en : AES_SWAP_ENABLE, AES_SWAP_DISABLE
*@return: None
******************************************************************************/
void HAL_AES_SetKey(uint32_t *keyin, uint8_t key_len, uint8_t swap_en);
void HAL_AES_SetKey_U8(uint8_t *keyin, uint8_t key_len, uint8_t swap_en);

/******************************************************************************
*@brief : function for aes encryption and decryption
*@param : indata        : pointer to buffer of input data
*@param : outdata       : pointer to buffer of output data
*@param : block_len     : block(128bit) length for aes cryption
*@param : operation     : AES_ENCRYPTION,AES_DECRYPTION
*@param : mode          : AES_ECB_MODE, AES_CBC_MODE
*@param : iv            : initial vector for CBC mode
*@param : security_mode : AES_NORMAL_MODE, AES_SECURITY_MDOE
*@return: None
******************************************************************************/
uint32_t HAL_AES_Crypt(
    uint32_t *indata,
    uint32_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint32_t *iv,
    uint32_t security_mode
);


uint32_t HAL_AES_Crypt_U8(
    uint8_t *indata,
    uint8_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint8_t *iv,
    uint32_t security_mode
);

void HAL_AES_Crypt_CTR(
    uint32_t *indata,
    uint32_t *outdata,
    uint32_t *iv,
    uint32_t block_len,
uint8_t auto_en
);

void HAL_AES_SetKey_CTR(uint32_t *keyin, uint8_t key_len, uint32_t *iv, uint8_t swap_en);

#endif
/******************************************************************************
 * end of file
*******************************************************************************/
