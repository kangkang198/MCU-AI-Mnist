/******************************************************************************
*@file  : hal_aes.h
*@brief : AES module driver header file.
*@ver   : 1.0.0
*@date  : 2022.10.20
******************************************************************************/

#ifndef __AES_SPI_H__
#define __AES_SPI_H__

#include "hal.h"

#define AES_SPI_ENCRYPTION   		1
#define AES_SPI_DECRYPTION   		0
#define AES_SPI_ECB_MODE	   		0
#define AES_SPI_CBC_MODE	   		1 
#define AES_SPI_CTR_MODE	   		2 
#define AES_SPI_SWAP_ENABLE  		1
#define AES_SPI_SWAP_DISABLE 		0

#define AES_SPI_NORMAL_MODE   	    0x12345678
#define AES_SPI_SECURITY_MODE 	    0

#define AES_SPI_KEY_128             0
#define AES_SPI_KEY_192             1
#define AES_SPI_KEY_256             2

#define AES_SPI_FAIL                0x00
#define AES_SPI_PASS                0xa59ada68 

#define AES_SPI_ADDR_AUTO_ENABLE        1
#define AES_SPI_ADDR_AUTO_DISABLE       0



#define SPI7_MEM_ADDR 0x08000000

#define SPI7_MEM_EXE_ADDR 0x08002000

//#define SPI_MEM_ADDR 0x63000000
//#define SPIB_MEM_ADDR 0x08000000
//#define SPIB_MEM_ADDR 0x04000000


#define SPI8_MEM_ADDR 0x10000000
#define SPI8_MEM_EXE_ADDR 0x10002000

#define OSPI2_MEM_ADDR 0x18000000
#define OSPI2_MEM_EXE_ADDR 0x18002000

#define MEM_ADDR        SPI7_MEM_ADDR
#define MEM_EXE_ADDR    SPI7_MEM_EXE_ADDR

//#define MEM_ADDR        SPI8_MEM_ADDR
//#define MEM_EXE_ADDR    SPI8_MEM_EXE_ADDR


//#define MEM_ADDR      OSPI2_MEM_ADDR
//#define MEM_EXE_ADDR  OSPI2_MEM_EXE_ADDR





#define FIRST_SIZE  0x8000 //32K
#define SECOND_SIZE 0x20000 //128K



/******************************************************************************
*@brief : set key for aes
*@param : keyin   : pointer to buffer of key
*@param : key_len : select length of key(AES_KEY_128/ AES_KEY_192/ AES_KEY_256)
*@param : swap_en : AES_SWAP_ENABLE, AES_SWAP_DISABLE
*@return: None
******************************************************************************/
void HAL_AES_SPI_SetKey(uint32_t *keyin, uint8_t key_len, uint8_t swap_en);
void HAL_AES_SPI_SetKey_U8(uint8_t *keyin, uint8_t key_len, uint8_t swap_en);
void HAL_AES_SPI_SetKey_CTR(uint32_t *keyin, uint8_t key_len, uint8_t swap_en);

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
uint32_t HAL_AES_SPI_Crypt(
    uint32_t *indata,
    uint32_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint32_t *iv,
    uint32_t security_mode
);


uint32_t HAL_AES_SPI_Crypt_U8(
    uint8_t *indata,
    uint8_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint8_t *iv,
    uint32_t security_mode
);

void HAL_AES_SPI_Crypt_CTR(
    uint32_t *indata,
    uint32_t *outdata,
    uint32_t *iv,
    uint32_t block_len,
    uint8_t auto_en
);

void HAL_AES_Crypt_soft(uint32_t *datain, uint32_t *dataout, uint32_t *ivin, uint32_t length);

//write only once after sysreset
void otfdec_uid_set_key(uint32_t *uid, uint32_t *random);
//write only once after sysreset
void otfdec_puf_set_key(uint32_t puf_offset,uint32_t *random);
//otfdec_en : 1: select PUF + RANDOM  3: UID+RANDOM
//write only once after sysreset
void otfdec_en(uint8_t otfdec_en, uint8_t spi_sel);
void otfdec_encrypt(uint32_t *datain, uint32_t start_addr, uint32_t length,uint32_t *dataout);
void otfdec_encrypt1(uint32_t *datain, uint32_t start_addr, uint32_t length,uint32_t *dataout);
void otfdec_uid_set_key2(uint32_t *key2, uint32_t *random);
void otfdec_uid_set_key3(uint32_t *key3);


#endif
/******************************************************************************
 * end of file
*******************************************************************************/
