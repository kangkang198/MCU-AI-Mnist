/******************************************************************************
* File Name:			aes.c
* Author:				  AisinoChip
* Data First Issued:	2020-06-17
* Description:		aes module driver
******************************************************************************/
#include "hal.h"

#ifdef HAL_AES_SPI1_ENABLED

#define SWAP32(a)       ((a<<24)|((a&0x0000ff00)<<8)|((a&0x00ff0000)>>8)|(a>>24))


uint32_t REG_IV1,REG_IV2,REG_IV3,REG_IV4;

//const unsigned char S[256] = {
// 99, 124, 119, 123, 242, 107, 111, 197,  48,   1, 103,  43, 254, 215, 171, 118, 
//202, 130, 201, 125, 250,  89,  71, 240, 173, 212, 162, 175, 156, 164, 114, 192, 
//183, 253, 147,  38,  54,  63, 247, 204,  52, 165, 229, 241, 113, 216,  49,  21, 
//  4, 199,  35, 195,  24, 150,   5, 154,   7,  18, 128, 226, 235,  39, 178, 117, 
//  9, 131,  44,  26,  27, 110,  90, 160,  82,  59, 214, 179,  41, 227,  47, 132, 
// 83, 209,   0, 237,  32, 252, 177,  91, 106, 203, 190,  57,  74,  76,  88, 207, 
//208, 239, 170, 251,  67,  77,  51, 133,  69, 249,   2, 127,  80,  60, 159, 168, 
// 81, 163,  64, 143, 146, 157,  56, 245, 188, 182, 218,  33,  16, 255, 243, 210, 
//205,  12,  19, 236,  95, 151,  68,  23, 196, 167, 126,  61, 100,  93,  25, 115, 
// 96, 129,  79, 220,  34,  42, 144, 136,  70, 238, 184,  20, 222,  94,  11, 219, 
//224,  50,  58,  10,  73,   6,  36,  92, 194, 211, 172,  98, 145, 149, 228, 121, 
//231, 200,  55, 109, 141, 213,  78, 169, 108,  86, 244, 234, 101, 122, 174,   8, 
//186, 120,  37,  46,  28, 166, 180, 198, 232, 221, 116,  31,  75, 189, 139, 138, 
//112,  62, 181, 102,  72,   3, 246,  14,  97,  53,  87, 185, 134, 193,  29, 158, 
//225, 248, 152,  17, 105, 217, 142, 148, 155,  30, 135, 233, 206,  85,  40, 223, 
//140, 161, 137,  13, 191, 230,  66, 104,  65, 153,  45,  15, 176,  84, 187,  22, 
//};

//const unsigned char Si[256] = {
// 82,   9, 106, 213,  48,  54, 165,  56, 191,  64, 163, 158, 129, 243, 215, 251, 
//124, 227,  57, 130, 155,  47, 255, 135,  52, 142,  67,  68, 196, 222, 233, 203, 
// 84, 123, 148,  50, 166, 194,  35,  61, 238,  76, 149,  11,  66, 250, 195,  78, 
//  8,  46, 161, 102,  40, 217,  36, 178, 118,  91, 162,  73, 109, 139, 209,  37, 
//114, 248, 246, 100, 134, 104, 152,  22, 212, 164,  92, 204,  93, 101, 182, 146, 
//108, 112,  72,  80, 253, 237, 185, 218,  94,  21,  70,  87, 167, 141, 157, 132, 
//144, 216, 171,   0, 140, 188, 211,  10, 247, 228,  88,   5, 184, 179,  69,   6, 
//208,  44,  30, 143, 202,  63,  15,   2, 193, 175, 189,   3,   1,  19, 138, 107, 
// 58, 145,  17,  65,  79, 103, 220, 234, 151, 242, 207, 206, 240, 180, 230, 115, 
//150, 172, 116,  34, 231, 173,  53, 133, 226, 249,  55, 232,  28, 117, 223, 110, 
// 71, 241,  26, 113,  29,  41, 197, 137, 111, 183,  98,  14, 170,  24, 190,  27, 
//252,  86,  62,  75, 198, 210, 121,  32, 154, 219, 192, 254, 120, 205,  90, 244, 
// 31, 221, 168,  51, 136,   7, 199,  49, 177,  18,  16,  89,  39, 128, 236,  95, 
// 96,  81, 127, 169,  25, 181,  74,  13,  45, 229, 122, 159, 147, 201, 156, 239, 
//160, 224,  59,  77, 174,  42, 245, 176, 200, 235, 187,  60, 131,  83, 153,  97, 
// 23,  43,   4, 126, 186, 119, 214,  38, 225, 105,  20,  99,  85,  33,  12, 125, 
//};

//const unsigned char Logtable[256] = {
//  0,   0,  25,   1,  50,   2,  26, 198,  75, 199,  27, 104,  51, 238, 223,   3, 
//100,   4, 224,  14,  52, 141, 129, 239,  76, 113,   8, 200, 248, 105,  28, 193, 
//125, 194,  29, 181, 249, 185,  39, 106,  77, 228, 166, 114, 154, 201,   9, 120, 
//101,  47, 138,   5,  33,  15, 225,  36,  18, 240, 130,  69,  53, 147, 218, 142, 
//150, 143, 219, 189,  54, 208, 206, 148,  19,  92, 210, 241,  64,  70, 131,  56, 
//102, 221, 253,  48, 191,   6, 139,  98, 179,  37, 226, 152,  34, 136, 145,  16, 
//126, 110,  72, 195, 163, 182,  30,  66,  58, 107,  40,  84, 250, 133,  61, 186, 
// 43, 121,  10,  21, 155, 159,  94, 202,  78, 212, 172, 229, 243, 115, 167,  87, 
//175,  88, 168,  80, 244, 234, 214, 116,  79, 174, 233, 213, 231, 230, 173, 232, 
// 44, 215, 117, 122, 235,  22,  11, 245,  89, 203,  95, 176, 156, 169,  81, 160, 
//127,  12, 246, 111,  23, 196,  73, 236, 216,  67,  31,  45, 164, 118, 123, 183, 
//204, 187,  62,  90, 251,  96, 177, 134,  59,  82, 161, 108, 170,  85,  41, 157, 
//151, 178, 135, 144,  97, 190, 220, 252, 188, 149, 207, 205,  55,  63,  91, 209, 
// 83,  57, 132,  60,  65, 162, 109,  71,  20,  42, 158,  93,  86, 242, 211, 171, 
// 68,  17, 146, 217,  35,  32,  46, 137, 180, 124, 184,  38, 119, 153, 227, 165, 
//103,  74, 237, 222, 197,  49, 254,  24,  13,  99, 140, 128, 192, 247, 112,   7, 
//};

//const unsigned char Alogtable[256] = {
//  1,   3,   5,  15,  17,  51,  85, 255,  26,  46, 114, 150, 161, 248,  19,  53, 
// 95, 225,  56,  72, 216, 115, 149, 164, 247,   2,   6,  10,  30,  34, 102, 170, 
//229,  52,  92, 228,  55,  89, 235,  38, 106, 190, 217, 112, 144, 171, 230,  49, 
// 83, 245,   4,  12,  20,  60,  68, 204,  79, 209, 104, 184, 211, 110, 178, 205, 
// 76, 212, 103, 169, 224,  59,  77, 215,  98, 166, 241,   8,  24,  40, 120, 136, 
//131, 158, 185, 208, 107, 189, 220, 127, 129, 152, 179, 206,  73, 219, 118, 154, 
//181, 196,  87, 249,  16,  48,  80, 240,  11,  29,  39, 105, 187, 214,  97, 163, 
//254,  25,  43, 125, 135, 146, 173, 236,  47, 113, 147, 174, 233,  32,  96, 160, 
//251,  22,  58,  78, 210, 109, 183, 194,  93, 231,  50,  86, 250,  21,  63,  65, 
//195,  94, 226,  61,  71, 201,  64, 192,  91, 237,  44, 116, 156, 191, 218, 117, 
//159, 186, 213, 100, 172, 239,  42, 126, 130, 157, 188, 223, 122, 142, 137, 128, 
//155, 182, 193,  88, 232,  35, 101, 175, 234,  37, 111, 177, 200,  67, 197,  84, 
//252,  31,  33,  99, 165, 244,   7,   9,  27,  45, 119, 153, 176, 203,  70, 202, 
// 69, 207,  74, 222, 121, 139, 134, 145, 168, 227,  62,  66, 198,  81, 243,  14, 
// 18,  54,  90, 238,  41, 123, 141, 140, 143, 138, 133, 148, 167, 242,  13,  23, 
// 57,  75, 221, 124, 132, 151, 162, 253,  28,  36, 108, 180, 199,  82, 246,   1, 
//};

//const unsigned char iG[4][4] = {
//0x0e, 0x09, 0x0d, 0x0b, 
//0x0b, 0x0e, 0x09, 0x0d, 
//0x0d, 0x0b, 0x0e, 0x09, 
//0x09, 0x0d, 0x0b, 0x0e, 
//};

//const unsigned long rcon[30] = { 
//  0x01,0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
//  0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91 };



#define MAXROUNDS		14
#define MAXKC			8
#define	BLOCK_ROW		4
#define	BLOCK_COLUMN	4
#define BLOCK_LENGTH	16
#define SWAP_OFFSET     241
#define KEY_OFFSET      242
  
/************************************************************************
 * function   : delay
 * Description: delay for a while.  
 * input : 
 *         count: count to decrease 
 * return: none 
 ************************************************************************/
void delay(uint32_t count)
{
	volatile uint32_t delay_count;

	delay_count = count; 

	while(delay_count--);  
}
  
  
void aes_memory_copy(uint32_t *psrc, uint32_t *pdst, uint32_t len)
{
	uint32_t i;
	
	for (i  =0; i < len; i ++)
	{
		*pdst ++ = *psrc ++;
	}
}  

void aes_memory_copy_u8(uint8_t *psrc, uint8_t *pdst, uint32_t len)
{
	uint32_t i;
	
	for (i  =0; i < len; i ++)
	{
		*pdst ++ = *psrc ++;
	}
}

/******************************************************************************
*@brief : set key for aes
*@param : keyin   : pointer to buffer of key
*@param : key_len : select length of key(AES_KEY_128/ AES_KEY_192/ AES_KEY_256)
*@param : swap_en : AES_SWAP_ENABLE, AES_SWAP_DISABLE
*@return: None
******************************************************************************/
void HAL_AES_SPI_SetKey(uint32_t *keyin, uint8_t key_len, uint8_t swap_en)
{ 
    /* Enable Clock */
    __HAL_RCC_AES_SPI1_CLK_ENABLE();

	AES->CTRL = 0x00;
	if(AES_SPI_SWAP_ENABLE == swap_en)
	{
		AES->CTRL |= 0x10;		
	}

	if(AES_SPI_KEY_192 == key_len)
	{
		AES->CTRL |= (1 << 6);		
		
	}
	else if(AES_SPI_KEY_256 == key_len) 
	{
		AES->CTRL |= (2 << 6);
	}

	AES->KEYIN = keyin[0];
	AES->KEYIN = keyin[1];
	AES->KEYIN = keyin[2];
	AES->KEYIN = keyin[3];

	if(AES_SPI_KEY_192 == key_len)
	{
        AES->KEYIN = keyin[4];
		AES->KEYIN = keyin[5]; 	 
	}
	else if(AES_SPI_KEY_256 == key_len)
	{
		AES->KEYIN = keyin[4];
		AES->KEYIN = keyin[5]; 
        AES->KEYIN = keyin[6];
		AES->KEYIN = keyin[7];  
	}

	AES->CTRL |= 0x02;//key setup
	while((AES->STATE & 0x02) == 0);
	AES->STATE = 0x02;

	__HAL_RCC_AES_SPI1_CLK_DISABLE();
}

void HAL_AES_SPI_SetKey_U8(uint8_t *keyin, uint8_t key_len, uint8_t swap_en)
{
    /* Enable Clock */
    __HAL_RCC_AES_SPI1_CLK_ENABLE();
	
	AES->CTRL = 0x00; 
   
	if(AES_SPI_SWAP_ENABLE == swap_en)
	{
		AES->CTRL |= 0x10;
	}

	if(AES_SPI_KEY_192 == key_len)
	{
	    AES->CTRL |= (1 << 6);   
	}
	else if(AES_SPI_KEY_256 == key_len) 
	{
	    AES->CTRL |= (2 << 6); 
	}

	AES->KEYIN = (keyin[3] << 24) | (keyin[2]  << 16) | (keyin[1]  << 8) | keyin[0];
	keyin += 4;
	AES->KEYIN = (keyin[3] << 24) | (keyin[2]  << 16) | (keyin[1]  << 8) | keyin[0];
	keyin += 4;
	AES->KEYIN = (keyin[3] << 24) | (keyin[2]  << 16) | (keyin[1]  << 8) | keyin[0];
	keyin += 4;
	AES->KEYIN = (keyin[3] << 24) | (keyin[2]  << 16) | (keyin[1]  << 8) | keyin[0];
	keyin += 4;

	if(AES_SPI_KEY_192 == key_len)
	{
	    AES->KEYIN = (keyin[3] << 24) | (keyin[2]  << 16) | (keyin[1]  << 8) | keyin[0];
		keyin += 4;
		AES->KEYIN = (keyin[3] << 24) | (keyin[2]  << 16) | (keyin[1]  << 8) | keyin[0];
		keyin += 4;	 
	}
	else if(AES_SPI_KEY_256 == key_len)
	{
		AES->KEYIN = (keyin[3] << 24) | (keyin[2]  << 16) | (keyin[1]  << 8) | keyin[0];
		keyin += 4;
		AES->KEYIN = (keyin[3] << 24) | (keyin[2]  << 16) | (keyin[1]  << 8) | keyin[0];
		keyin += 4; 
        AES->KEYIN = (keyin[3] << 24) | (keyin[2]  << 16) | (keyin[1]  << 8) | keyin[0];
		keyin += 4;
		AES->KEYIN = (keyin[3] << 24) | (keyin[2]  << 16) | (keyin[1]  << 8) | keyin[0];
		keyin += 4;  
	}

	AES->CTRL |= 0x02;//key setup
	while((AES->STATE & 0x02) == 0);
	AES->STATE = 0x02;

	__HAL_RCC_AES_SPI1_CLK_DISABLE();
}

void aes_func(uint32_t *indata, uint32_t * outdata, uint8_t mode)
{
	AES->DATAIN = indata[ 0 ];		
	AES->DATAIN = indata[ 1 ];		
	AES->DATAIN = indata[ 2 ];		
	AES->DATAIN = indata[ 3 ];  

	AES->CTRL |= 0x01;
	while((AES->STATE & 0x01) == 0);
	AES->STATE = 0x01;

    outdata[ 0 ] = AES->DATAOUT;
    outdata[ 1 ] = AES->DATAOUT;
    outdata[ 2 ] = AES->DATAOUT;
    outdata[ 3 ] = AES->DATAOUT;	
		
	if(AES_SPI_CBC_MODE == mode)
	{
		AES->STATE |= 0x04;//clear cbc flg			 
	}	
}


void aes_func_u8(uint8_t *indata, uint8_t * outdata, uint8_t mode)
{
	uint32_t result;
	
	AES->DATAIN = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
	AES->DATAIN = (indata[7] << 24) | (indata[6]  << 16) | (indata[5]  << 8) | indata[4];
	AES->DATAIN = (indata[11] << 24) | (indata[10]  << 16) | (indata[9]  << 8) | indata[8];
	AES->DATAIN = (indata[15] << 24) | (indata[14]  << 16) | (indata[13]  << 8) | indata[12];
	
	AES->CTRL |= 0x01;
	while((AES->STATE & 0x01) == 0);
	AES->STATE = 0x01;
	
	result = AES->DATAOUT;	
	outdata[3] =  (result >> 24) & 0xff;
	outdata[2] =  (result >> 16) & 0xff;
	outdata[1] =  (result >> 8) & 0xff;
	outdata[0] =  (result) & 0xff;
	outdata += 4;

	result = AES->DATAOUT;	
	outdata[3] =  (result >> 24) & 0xff;
	outdata[2] =  (result >> 16) & 0xff;
	outdata[1] =  (result >> 8) & 0xff;
	outdata[0] =  (result) & 0xff;
	outdata += 4;
	
	result = AES->DATAOUT;	
	outdata[3] =  (result >> 24) & 0xff;
	outdata[2] =  (result >> 16) & 0xff;
	outdata[1] =  (result >> 8) & 0xff;
	outdata[0] =  (result) & 0xff;
	outdata += 4;	
	
	result = AES->DATAOUT;	
	outdata[3] =  (result >> 24) & 0xff;
	outdata[2] =  (result >> 16) & 0xff;
	outdata[1] =  (result >> 8) & 0xff;
	outdata[0] =  (result) & 0xff;
	outdata += 4;	
		
	if(AES_SPI_CBC_MODE == mode)
	{
		AES->STATE |= 0x04;//clear cbc flg			 
	}	
}


uint32_t aes_func_dfa(uint32_t *indata, uint32_t * outdata, uint8_t mode)
{
	uint8_t delay_num;
	uint8_t rnd;
	uint32_t temp_buffer[4];

	//frist time
	aes_func(indata, outdata, mode);	
   
	//delay random time
	HAL_HRNG_GetHrng(&rnd, 1);
	delay_num  = rnd & 0xf;
	delay(delay_num);
	
	//second time
	aes_func(indata, temp_buffer, mode);
	
	if( (outdata[0] == temp_buffer[0]) &&
			(outdata[1] == temp_buffer[1]) &&
			(outdata[2] == temp_buffer[2]) &&
			(outdata[3] == temp_buffer[3])		    
		)
		{			
			delay_num  = (rnd >> 4) & 0xf;
			delay(delay_num);
			 
			if( (outdata[0] == temp_buffer[0]) &&
					(outdata[1] == temp_buffer[1]) &&
					(outdata[2] == temp_buffer[2]) &&
					(outdata[3] == temp_buffer[3])				
			)
			{
					return AES_SPI_PASS;
			}			
		}
		outdata[0] = 0;
		outdata[1] = 0;	
		outdata[2] = 0;
		outdata[3] = 0;	
		
		return AES_SPI_FAIL;	
}

uint32_t aes_func_dfa_u8(uint8_t *indata, uint8_t * outdata, uint8_t mode)
{
	uint8_t delay_num;
	uint8_t rnd;
	uint8_t temp_buffer[16];
	uint8_t i,j;
	
	//frist time
	aes_func_u8(indata, outdata, mode);	
   
	//delay random time
	HAL_HRNG_GetHrng(&rnd, 1);
	delay_num  = rnd & 0xf;
	delay(delay_num);
	
	//second time
	aes_func_u8(indata, temp_buffer, mode);
	
	for( i = 0; i < 16; i ++)
	{
		if(outdata[i] != temp_buffer[i])
		{
			for ( j = 0; j < 16; j ++)
			{
				outdata[j] = 0;
			}
			return AES_SPI_FAIL; 		    
		}
	}
	
	delay_num  = (rnd >> 4) & 0xf;
	delay(delay_num);
	
	for( i = 0; i < 16; i ++)
	{
		if(outdata[i] != temp_buffer[i])
		{
			for ( j = 0; j < 16; j ++)
			{
				outdata[j] = 0;
			}
			return AES_SPI_FAIL; 		    
		}
	}	
	
	return AES_SPI_PASS;	
}


void aes_cbc_mode_set(uint32_t * pdata, uint8_t mode)
{
	if(AES_SPI_CBC_MODE == mode)
	{
        AES->CTRL |= 0x20;
		REG_IV1 = pdata[0]; 
		REG_IV2 = pdata[1];
		REG_IV3 = pdata[2];
		REG_IV4 = pdata[3];       
	} 
	else
	{
		AES->CTRL &= (~0x20);
	}
}

uint32_t aes_crypt_security(
    uint32_t *indata,
    uint32_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint32_t *iv   
)
{
	uint32_t * pSrcData, *pDstData; 
	uint32_t i;
	uint32_t indata_bk[4];
	uint32_t temp_iv[4];
    
    __HAL_RCC_HRNG_CLK_ENABLE();
    
	if(operation == AES_SPI_DECRYPTION)//decrypt
	{
		AES->CTRL |= 0x04;
	} 
	else
	{
		AES->CTRL &= (~0x04);
	}		 
    
    AES->CTRL |= ( 1 << 8);	//VAES enable
	AES->CTRL &= 0xffff01ff;
	AES->CTRL |= (1 << 9);	//4round

	pSrcData = indata;
	pDstData = outdata;	
	
	if(AES_SPI_ECB_MODE == mode)  //ECB
	{
        aes_cbc_mode_set(iv, mode);
		for ( i = 0; i < block_len; i ++)
		{	
			aes_memory_copy(pSrcData, indata_bk, 4);	
			if(aes_func_dfa(indata_bk, pDstData,mode) != AES_SPI_PASS)
			{	
				return AES_SPI_FAIL;				
			}		
            
            __HAL_RCC_HRNG_CLK_ENABLE();
            
			pSrcData += 4;
			pDstData += 4;			
		}		
	}
	else //CBC
	{
		if(operation == AES_SPI_ENCRYPTION)
		{
			aes_cbc_mode_set(iv, mode);  //重新设置IV
			aes_memory_copy(pSrcData, indata_bk ,4);
			
			indata_bk[0] = REG_IV1 ^ indata_bk[0];
			indata_bk[1] = REG_IV2 ^ indata_bk[1];
			indata_bk[2] = REG_IV3 ^ indata_bk[2];
			indata_bk[3] = REG_IV4 ^ indata_bk[3];
		
			if(aes_func_dfa(indata_bk, pDstData, mode) != AES_SPI_PASS)
			{
				return AES_SPI_FAIL;				
			}
            
            __HAL_RCC_HRNG_CLK_ENABLE();
			
			block_len -- ;
			while(block_len -- )
			{
                aes_cbc_mode_set(pDstData, mode); //重新设置IV
				pSrcData += 4;
				pDstData += 4;
				aes_memory_copy(pSrcData, indata_bk ,4);

				indata_bk[0] = REG_IV1 ^ indata_bk[0];
				indata_bk[1] = REG_IV2 ^ indata_bk[1];
				indata_bk[2] = REG_IV3 ^ indata_bk[2];
				indata_bk[3] = REG_IV4 ^ indata_bk[3];				

				if( aes_func_dfa( indata_bk, pDstData, mode) != AES_SPI_PASS )
				{		
					return AES_SPI_FAIL;	
				}	
                
                __HAL_RCC_HRNG_CLK_ENABLE();
                
			}
		}
		else//decryption
		{
			aes_memory_copy(pSrcData, indata_bk ,4);
			aes_cbc_mode_set(iv, mode);  //重新设置IV
			temp_iv[0] = indata_bk[0];
			temp_iv[1] = indata_bk[1];
			temp_iv[2] = indata_bk[2];
			temp_iv[3] = indata_bk[3];			
			if( aes_func_dfa( indata_bk, pDstData,mode) != AES_SPI_PASS )
			{	
				return AES_SPI_FAIL;	
			}
            
            __HAL_RCC_HRNG_CLK_ENABLE();

			
			pDstData[0] = REG_IV1 ^ pDstData[0];
			pDstData[1] = REG_IV2 ^ pDstData[1];
			pDstData[2] = REG_IV3 ^ pDstData[2];
			pDstData[3] = REG_IV4 ^ pDstData[3];
	
			block_len --;

			while(block_len --)
			{		
                aes_cbc_mode_set(indata_bk, mode);                
				pSrcData += 4;
				pDstData += 4;
				aes_memory_copy(pSrcData, indata_bk ,4);

				temp_iv[0] = indata_bk[0];
				temp_iv[1] = indata_bk[1];
				temp_iv[2] = indata_bk[2];
				temp_iv[3] = indata_bk[3];	

				if( aes_func_dfa( indata_bk, pDstData, mode) != AES_SPI_PASS )
				{
					return AES_SPI_FAIL;
				}
                
                __HAL_RCC_HRNG_CLK_ENABLE();
                
			
				pDstData[0] = REG_IV1 ^ pDstData[0];
				pDstData[1] = REG_IV2 ^ pDstData[1];
				pDstData[2] = REG_IV3 ^ pDstData[2];
				pDstData[3] = REG_IV4 ^ pDstData[3];
				
			} 			
		}
	}    	

    //__HAL_RCC_HRNG_CLK_DISABLE();
	return AES_SPI_PASS; 
}



void aes_cbc_mode_set_u8(uint8_t * pdata, uint8_t mode)
{
	if(AES_SPI_CBC_MODE == mode)
	{
        AES->CTRL |= 0x20;
		REG_IV1 = (pdata[3] << 24) | (pdata[2]  << 16) | (pdata[1]  << 8) | pdata[0];
		pdata += 4; 
		REG_IV2 = (pdata[3] << 24) | (pdata[2]  << 16) | (pdata[1]  << 8) | pdata[0];
		pdata += 4; 
		REG_IV3 = (pdata[3] << 24) | (pdata[2]  << 16) | (pdata[1]  << 8) | pdata[0];
		pdata += 4; 
		REG_IV4 = (pdata[3] << 24) | (pdata[2]  << 16) | (pdata[1]  << 8) | pdata[0];
		pdata += 4; 
	} 
	else
	{
		AES->CTRL  &= (~0x20);
	}	

}

uint32_t aes_crypt_security_u8(
    uint8_t *indata,
    uint8_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint8_t *iv   
)
{
	uint8_t * pSrcData, *pDstData; 
	uint32_t i;  
	uint8_t indata_bk[16];
//	uint32_t temp[4];
    
    __HAL_RCC_HRNG_CLK_ENABLE();

	if(operation == AES_SPI_DECRYPTION)//decrypt
	{
		AES->CTRL |= 0x04;
	} 
	else
	{
		AES->CTRL &= (~0x04);
	}		 
   
	AES->CTRL |= ( 1 << 8);	  //VAES enable
	AES->CTRL &= 0xffff01ff;
	AES->CTRL |= (1 << 9);	  //4round

	pSrcData = indata;
	pDstData = outdata;	
	
	if(AES_SPI_ECB_MODE == mode)
	{
		for ( i = 0; i < block_len; i ++)
		{		
			aes_memory_copy_u8(pSrcData, indata_bk, 16);	
			if(aes_func_dfa_u8(indata_bk, pDstData, mode) != AES_SPI_PASS)
			{		
				return AES_SPI_FAIL;				
			}			
			pSrcData += 16;
			pDstData += 16;			
		}		
	}
	else //CBC
	{
		if(operation == AES_SPI_ENCRYPTION)
		{
			aes_cbc_mode_set_u8(iv, mode);  //初始化IV，倒序
			aes_memory_copy_u8(pSrcData, indata_bk, 16);	
			
//			temp[0] = REG_IV1 ^((indata_bk[3] << 24) | (indata_bk[2]  << 16) | (indata_bk[1]  << 8) | indata_bk[0]);
//			temp[1] = REG_IV2 ^((indata_bk[7] << 24) | (indata_bk[6]  << 16) | (indata_bk[5]  << 8) | indata_bk[4]);
//			temp[2] = REG_IV3 ^((indata_bk[11] << 24) | (indata_bk[10]  << 16) | (indata_bk[9]  << 8) | indata_bk[8]);
//			temp[3] = REG_IV4 ^((indata_bk[15] << 24) | (indata_bk[14]  << 16) | (indata_bk[13]  << 8) | indata_bk[12]);
			
//			indata_bk[3] =  (temp[0] >> 24) & 0xff;
//			indata_bk[2] =  (temp[0] >> 16) & 0xff;
//			indata_bk[1] =  (temp[0] >> 8) & 0xff;
//			indata_bk[0] =  (temp[0]) & 0xff;	

//			indata_bk[7] =  (temp[1] >> 24) & 0xff;
//			indata_bk[6] =  (temp[1] >> 16) & 0xff;
//			indata_bk[5] =  (temp[1] >> 8) & 0xff;
//			indata_bk[4] =  (temp[1]) & 0xff;		
//			
//			indata_bk[11] =  (temp[2] >> 24) & 0xff;
//			indata_bk[10] =  (temp[2] >> 16) & 0xff;
//			indata_bk[9]  =  (temp[2] >> 8) & 0xff;
//			indata_bk[8]  =  (temp[2]) & 0xff;

//			indata_bk[15] =  (temp[3] >> 24) & 0xff;
//			indata_bk[14] =  (temp[3] >> 16) & 0xff;
//			indata_bk[13] =  (temp[3] >> 8) & 0xff;
//			indata_bk[12] =  (temp[3]) & 0xff;
			
			if(aes_func_dfa_u8(indata_bk, pDstData, mode) != AES_SPI_PASS)
			{
				return AES_SPI_FAIL;				
			}			
			block_len -- ;
			while(block_len -- )
			{
				aes_cbc_mode_set_u8(pDstData, mode);
				pSrcData += 16;
				pDstData += 16;
				aes_memory_copy_u8(pSrcData, indata_bk, 16);

//				temp[0] = REG_IV1 ^ ((indata_bk[3] << 24) | (indata_bk[2]  << 16) | (indata_bk[1]  << 8) | indata_bk[0]);
//				temp[1] = REG_IV2 ^ ((indata_bk[7] << 24) | (indata_bk[6]  << 16) | (indata_bk[5]  << 8) | indata_bk[4]);
//				temp[2] = REG_IV3 ^ ((indata_bk[11] << 24) | (indata_bk[10]  << 16) | (indata_bk[9]  << 8) | indata_bk[8]);
//				temp[3] = REG_IV4 ^ ((indata_bk[15] << 24) | (indata_bk[14]  << 16) | (indata_bk[13]  << 8) | indata_bk[12]);
//				
//				indata_bk[3] =  (temp[0] >> 24) & 0xff;
//				indata_bk[2] =  (temp[0] >> 16) & 0xff;
//				indata_bk[1] =  (temp[0] >> 8) & 0xff;
//				indata_bk[0] =  (temp[0]) & 0xff;	

//				indata_bk[7] =  (temp[1] >> 24) & 0xff;
//				indata_bk[6] =  (temp[1] >> 16) & 0xff;
//				indata_bk[5] =  (temp[1] >> 8) & 0xff;
//				indata_bk[4] =  (temp[1]) & 0xff;		
//				
//				indata_bk[11] =  (temp[2] >> 24) & 0xff;
//				indata_bk[10] =  (temp[2] >> 16) & 0xff;
//				indata_bk[9]  =  (temp[2] >> 8) & 0xff;
//				indata_bk[8]  =  (temp[2]) & 0xff;

//				indata_bk[15] =  (temp[3] >> 24) & 0xff;
//				indata_bk[14] =  (temp[3] >> 16) & 0xff;
//				indata_bk[13] =  (temp[3] >> 8) & 0xff;
//				indata_bk[12] =  (temp[3]) & 0xff;				
				
				if( aes_func_dfa_u8( indata_bk, pDstData, mode) != AES_SPI_PASS )
				{		
					return AES_SPI_FAIL;	
				}	
			}
		}
		else//decryption  
		{
			aes_memory_copy_u8(pSrcData, indata_bk, 16); //将输入buffer值保存至indata_bk
			aes_cbc_mode_set_u8(iv, mode);
			
			if( aes_func_dfa_u8( indata_bk, pDstData,mode) != AES_SPI_PASS )
			{	
				return AES_SPI_FAIL;	
			}
			
//			temp[0] = REG_IV1 ^ ((pDstData[3] << 24) | (pDstData[2]  << 16) | (pDstData[1]  << 8) | pDstData[0]);
//			temp[1] = REG_IV2 ^ ((pDstData[7] << 24) | (pDstData[6]  << 16) | (pDstData[5]  << 8) | pDstData[4]);
//			temp[2] = REG_IV3 ^ ((pDstData[11] << 24) | (pDstData[10]  << 16) | (pDstData[9]  << 8) | pDstData[8]);
//			temp[3] = REG_IV4 ^ ((pDstData[15] << 24) | (pDstData[14]  << 16) | (pDstData[13]  << 8) | pDstData[12]);
//			
//			pDstData[3] =  (temp[0] >> 24) & 0xff;
//			pDstData[2] =  (temp[0] >> 16) & 0xff;
//			pDstData[1] =  (temp[0] >> 8) & 0xff;
//			pDstData[0] =  (temp[0]) & 0xff;	

//			pDstData[7] =  (temp[1] >> 24) & 0xff;
//			pDstData[6] =  (temp[1] >> 16) & 0xff;
//			pDstData[5] =  (temp[1] >> 8) & 0xff;
//			pDstData[4] =  (temp[1]) & 0xff;		
//			
//			pDstData[11] =  (temp[2] >> 24) & 0xff;
//			pDstData[10] =  (temp[2] >> 16) & 0xff;
//			pDstData[9]  =  (temp[2] >> 8) & 0xff;
//			pDstData[8]  =  (temp[2]) & 0xff;

//			pDstData[15] =  (temp[3] >> 24) & 0xff;
//			pDstData[14] =  (temp[3] >> 16) & 0xff;
//			pDstData[13] =  (temp[3] >> 8) & 0xff;
//			pDstData[12] =  (temp[3]) & 0xff;				

			block_len --;

			while(block_len --)
			{			
				aes_cbc_mode_set_u8(indata_bk, mode);
				
				pSrcData += 16;
				pDstData += 16;
				
				aes_memory_copy_u8(pSrcData, indata_bk, 16);

				if( aes_func_dfa_u8( indata_bk, pDstData, mode) != AES_SPI_PASS )
				{
					return AES_SPI_FAIL;
				}	

//				temp[0] = REG_IV1 ^ ((pDstData[3] << 24) | (pDstData[2]  << 16) | (pDstData[1]  << 8) | pDstData[0]);
//				temp[1] = REG_IV2 ^ ((pDstData[7] << 24) | (pDstData[6]  << 16) | (pDstData[5]  << 8) | pDstData[4]);
//				temp[2] = REG_IV3 ^ ((pDstData[11] << 24) | (pDstData[10]  << 16) | (pDstData[9]  << 8) | pDstData[8]);
//				temp[3] = REG_IV4 ^ ((pDstData[15] << 24) | (pDstData[14]  << 16) | (pDstData[13]  << 8) | pDstData[12]);

//				pDstData[3] =  (temp[0] >> 24) & 0xff;
//				pDstData[2] =  (temp[0] >> 16) & 0xff;
//				pDstData[1] =  (temp[0] >> 8) & 0xff;
//				pDstData[0] =  (temp[0]) & 0xff;	

//				pDstData[7] =  (temp[1] >> 24) & 0xff;
//				pDstData[6] =  (temp[1] >> 16) & 0xff;
//				pDstData[5] =  (temp[1] >> 8) & 0xff;
//				pDstData[4] =  (temp[1]) & 0xff;		
//				
//				pDstData[11] =  (temp[2] >> 24) & 0xff;
//				pDstData[10] =  (temp[2] >> 16) & 0xff;
//				pDstData[9]  =  (temp[2] >> 8) & 0xff;
//				pDstData[8]  =  (temp[2]) & 0xff;

//				pDstData[15] =  (temp[3] >> 24) & 0xff;
//				pDstData[14] =  (temp[3] >> 16) & 0xff;
//				pDstData[13] =  (temp[3] >> 8) & 0xff;
//				pDstData[12] =  (temp[3]) & 0xff;								
			} 			
		}
	}    
    
    //__HAL_RCC_HRNG_CLK_DISABLE();    //disable hrng clk
    
	return AES_SPI_PASS; 
}

#if 1
void aes_crypt_normal(
    uint32_t *indata,
    uint32_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint32_t *iv  
)
{	
    uint32_t i,j;
	uint32_t temp_iv[4];
    uint32_t ctr_o[4];
	uint32_t cnt[4];

   	if(operation == AES_SPI_DECRYPTION)//decrypt
    {
    	AES->CTRL |= 0x04;
    } 
	else
	{
		AES->CTRL &= (~0x04);
	} 
  	
	if(AES_SPI_CBC_MODE == mode)
	{
        AES->CTRL |= 0x20;
		AES->IVIN = iv[0]; 
		AES->IVIN = iv[1];
		AES->IVIN = iv[2];
		AES->IVIN = iv[3];	
	} 
    else if(AES_SPI_CTR_MODE == mode)
    {
//        AES->CTRL = 0x1000; //CTR mode
//        AES->CTRL |= (1<<14); //addr auto en,0x4000
        AES->CTRL |= 0x5000; //CTR mode,addr auto en
        AES->CTRL &= (~0x04);//encrypt
        AES->STARTADDR = iv[0]; 
        AES->ENDADDR = iv[1];
        AES->INIDATA = iv[2];
        AES->ADDR = iv[3];        
    }
	else  //ECB
	{
        AES->CTRL &= (~0x20); 
	}   
    
    i = 0; 	
    for( j = block_len; j > 0; j-- )
    {
        if(AES_SPI_CTR_MODE != mode)
        {
            AES->DATAIN = indata[ i ];		
            AES->DATAIN = indata[ i + 1 ];		
            AES->DATAIN = indata[ i + 2 ];		
            AES->DATAIN = indata[ i + 3 ];
        }

      	AES->CTRL |= 0x01;
		while(  (AES->STATE & 0x01) == 0);
		AES->STATE  = 0x01;			

        if(AES_SPI_CTR_MODE == mode)
        {
            ctr_o[0] = AES->DATAOUT;
            ctr_o[1] = AES->DATAOUT;
            ctr_o[2] = AES->DATAOUT;
            ctr_o[3] = AES->DATAOUT;
        
//    printf("ctr_o[0] = 0x%x\n",ctr_o[0]);
//    printf("ctr_o[1] = 0x%x\n",ctr_o[1]);
//    printf("ctr_o[2] = 0x%x\n",ctr_o[2]);
//    printf("ctr_o[3] = 0x%x\n",ctr_o[3]);
// printf("\n");	 

		outdata[ i ] = ctr_o[0] ^ indata[ i ];
		outdata[ i + 1] = ctr_o[1] ^ indata[ i + 1];
		outdata[ i + 2] = ctr_o[2] ^ indata[ i + 2];
		outdata[ i + 3] = ctr_o[3] ^ indata[ i + 3];		
			
//		indata  += 4;
//		outdata += 4;            
        }
        else
        {
            outdata[ i ]    = AES->DATAOUT;
            outdata[ i + 1] = AES->DATAOUT;
            outdata[ i + 2] = AES->DATAOUT;
            outdata[ i + 3] = AES->DATAOUT;            
        }
               
        i += 4;		
    }    
    
    AES->STATE |= 0x04;//clear cbc flg
}


#endif


void aes_crypt_normal_u8(
    uint8_t *indata,
    uint8_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint8_t *iv  
)
{	
    uint32_t j, result;
	uint32_t temp_iv[4];
	
	if(AES_SPI_CBC_MODE == mode)
	{
        AES->CTRL |= 0x20;
		AES->IVIN = (iv[3] << 24) | (iv[2]  << 16) | (iv[1]  << 8) | iv[0];
		iv += 4;
		AES->IVIN = (iv[3] << 24) | (iv[2]  << 16) | (iv[1]  << 8) | iv[0];
		iv += 4;
		AES->IVIN = (iv[3] << 24) | (iv[2]  << 16) | (iv[1]  << 8) | iv[0];
		iv += 4;
		AES->IVIN = (iv[3] << 24) | (iv[2]  << 16) | (iv[1]  << 8) | iv[0];
		iv += 4;			
//		if(operation == AES_DECRYPTION)//decrypt
//		{
//			AES->CTRL |= 0x04;  //decrypt
//			aes_cbc_mode_set_u8(iv,mode);   //初始化IV

//			for( j = block_len; j > 0; j-- )
//			{
//				temp_iv[0] = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
//				indata += 4;
//				temp_iv[1] = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
//				indata += 4;
//				temp_iv[2] = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
//				indata += 4;
//				temp_iv[3] = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
//				indata += 4;

//				AES->DATAIN	= temp_iv[0];			
//				AES->DATAIN	= temp_iv[1];			
//				AES->DATAIN	= temp_iv[2];			
//				AES->DATAIN	= temp_iv[3];			
//		
//				AES->CTRL |= 0x01;
//				while((AES->STATE & 0x01) == 0);
//				AES->STATE = 0x01;

//				result = REG_IV1 ^ (AES->DATAOUT);
//				outdata[3] =  (result >> 24) & 0xff;
//				outdata[2] =  (result >> 16) & 0xff;
//				outdata[1] =  (result >> 8) & 0xff;
//				outdata[0] =  (result) & 0xff;
//				outdata += 4;
//				
//				result = REG_IV2 ^ (AES->DATAOUT);
//				outdata[3] =  (result >> 24) & 0xff;
//				outdata[2] =  (result >> 16) & 0xff;
//				outdata[1] =  (result >> 8) & 0xff;
//				outdata[0] =  (result) & 0xff;
//				outdata += 4;				

//				result = REG_IV3 ^ (AES->DATAOUT);
//				outdata[3] =  (result >> 24) & 0xff;
//				outdata[2] =  (result >> 16) & 0xff;
//				outdata[1] =  (result >> 8) & 0xff;
//				outdata[0] =  (result) & 0xff;
//				outdata += 4;				
//				
//				result = REG_IV4 ^ (AES->DATAOUT);
//				outdata[3] =  (result >> 24) & 0xff;
//				outdata[2] =  (result >> 16) & 0xff;
//				outdata[1] =  (result >> 8) & 0xff;
//				outdata[0] =  (result) & 0xff;
//				outdata += 4;	
//				
//				REG_IV1 = temp_iv[0];
//				REG_IV2 = temp_iv[1];
//				REG_IV3 = temp_iv[2];
//				REG_IV4 = temp_iv[3];
//			} 
//		}
//		else //cbc, encrypt
//		{
//			AES->CTRL &= (~0x04);  //encrypt
//			aes_cbc_mode_set_u8(iv,mode); //初始化IV

//			for( j = block_len; j > 0; j-- )
//			{
//				AES->DATAIN	= ((indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0]) ^ REG_IV1;	//0x37A5AB3E		
//				indata += 4;
//				AES->DATAIN	= ((indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0]) ^ REG_IV2;	//0x0C32BA71		
//				indata += 4;
//				AES->DATAIN	= ((indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0]) ^ REG_IV3;	//0x6F177462		
//				indata += 4;
//				AES->DATAIN	= ((indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0]) ^ REG_IV4;	//0x8596B344
//				indata += 4;
//				
//				AES->CTRL |= 0x01;
//				while((AES->STATE & 0x01) == 0);
//				AES->STATE = 0x01;

//				result = AES->DATAOUT; //0x099ed143
//				outdata[3] =  (result >> 24) & 0xff;
//				outdata[2] =  (result >> 16) & 0xff;
//				outdata[1] =  (result >> 8) & 0xff;
//				outdata[0] =  (result) & 0xff;
//				REG_IV1 = result;   //更新IV
//				outdata += 4;

//				result = AES->DATAOUT;
//				outdata[3] =  (result >> 24) & 0xff;
//				outdata[2] =  (result >> 16) & 0xff;
//				outdata[1] =  (result >> 8) & 0xff;
//				outdata[0] =  (result) & 0xff;
//				REG_IV2 = result;   //更新IV
//				outdata += 4;				

//				result = AES->DATAOUT;
//				outdata[3] =  (result >> 24) & 0xff;
//				outdata[2] =  (result >> 16) & 0xff;
//				outdata[1] =  (result >> 8) & 0xff;
//				outdata[0] =  (result) & 0xff;
//				REG_IV3 = result;   //更新IV
//				outdata += 4;				
//				
//				result = AES->DATAOUT;
//				outdata[3] =  (result >> 24) & 0xff;
//				outdata[2] =  (result >> 16) & 0xff;
//				outdata[1] =  (result >> 8) & 0xff;
//				outdata[0] =  (result) & 0xff;
//				REG_IV4 = result;   //更新IV
//				outdata += 4;
//			} 
//		}
	} 
	else  //ECB mode
	{
        AES->CTRL &= (~0x20); 
//		if(operation == AES_DECRYPTION)//decrypt
//		{
//			AES->CTRL |= 0x04;
//		} 
//		else
//		{
//			AES->CTRL &= (~0x04);
//		}
// 	
//		for( j = block_len; j > 0; j-- )
//		{
//			AES->DATAIN = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
//			indata += 4;
//			AES->DATAIN = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
//			indata += 4;
//			AES->DATAIN = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
//			indata += 4;
//			AES->DATAIN = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
//			indata += 4;

//			AES->CTRL |= 0x01;
//			while((AES->STATE & 0x01) == 0);
//			AES->STATE = 0x01;

//			result = AES->DATAOUT;
//			outdata[3] =  (result >> 24) & 0xff;
//			outdata[2] =  (result >> 16) & 0xff;
//			outdata[1] =  (result >> 8) & 0xff;
//			outdata[0] =  (result) & 0xff;
//			outdata += 4;

//			result = AES->DATAOUT;
//			outdata[3] =  (result >> 24) & 0xff;
//			outdata[2] =  (result >> 16) & 0xff;
//			outdata[1] =  (result >> 8) & 0xff;
//			outdata[0] =  (result) & 0xff;
//			outdata += 4;			

//			result = AES->DATAOUT;
//			outdata[3] =  (result >> 24) & 0xff;
//			outdata[2] =  (result >> 16) & 0xff;
//			outdata[1] =  (result >> 8) & 0xff;
//			outdata[0] =  (result) & 0xff;
//			outdata += 4;		

//			result = AES->DATAOUT;
//			outdata[3] =  (result >> 24) & 0xff;
//			outdata[2] =  (result >> 16) & 0xff;
//			outdata[1] =  (result >> 8) & 0xff;
//			outdata[0] =  (result) & 0xff;
//			outdata += 4;	
//		} 
		
	}   
    
    if(operation == AES_SPI_DECRYPTION)//decrypt
    {
    	AES->CTRL |= 0x04;
    } 
	else
	{
		AES->CTRL &= (~0x04);
	} 
    
    for( j = block_len; j > 0; j-- )
    {
        AES->DATAIN = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
		indata += 4;
        AES->DATAIN = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
		indata += 4;
        AES->DATAIN = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
		indata += 4;
        AES->DATAIN = (indata[3] << 24) | (indata[2]  << 16) | (indata[1]  << 8) | indata[0];
		indata += 4;				

      	AES->CTRL |= 0x01;
		while(  (AES->STATE & 0x01) == 0);
		AES->STATE = 0x01;

		result = AES->DATAOUT;
		outdata[3] =  (result >> 24) & 0xff;
		outdata[2] =  (result >> 16) & 0xff;
		outdata[1] =  (result >> 8) & 0xff;
		outdata[0] =  (result) & 0xff;
		outdata += 4;

		result = AES->DATAOUT;
		outdata[3] =  (result >> 24) & 0xff;
		outdata[2] =  (result >> 16) & 0xff;
		outdata[1] =  (result >> 8) & 0xff;
		outdata[0] =  (result) & 0xff;
		outdata += 4;		

		result = AES->DATAOUT;
		outdata[3] =  (result >> 24) & 0xff;
		outdata[2] =  (result >> 16) & 0xff;
		outdata[1] =  (result >> 8) & 0xff;
		outdata[0] =  (result) & 0xff;
		outdata += 4;		
		
		result = AES->DATAOUT;
		outdata[3] =  (result >> 24) & 0xff;
		outdata[2] =  (result >> 16) & 0xff;
		outdata[1] =  (result >> 8) & 0xff;
		outdata[0] =  (result) & 0xff;
		outdata += 4;	
    } 
    
    AES->STATE |= 0x04;//clear cbc flg
}


uint32_t HAL_AES_SPI_Crypt(
    uint32_t *indata,
    uint32_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint32_t *iv,
    uint32_t security_mode
)
{
	uint32_t flag;

    /* Enable Clock */
    __HAL_RCC_AES_SPI1_CLK_ENABLE();
    
	if(security_mode == AES_SPI_NORMAL_MODE)
	{
		aes_crypt_normal(indata, outdata, block_len, operation, mode, iv);
        __HAL_RCC_AES_SPI1_CLK_DISABLE();
		return 	AES_SPI_PASS;	
	}
	else
	{
        __HAL_RCC_HRNG_CLK_ENABLE();
        
		flag =  aes_crypt_security(indata, outdata, block_len, operation, mode, iv);
        
        __HAL_RCC_HRNG_CLK_DISABLE();        
        __HAL_RCC_AES_SPI1_CLK_DISABLE();

		return flag;
	}	
}


uint32_t HAL_AES_SPI_Crypt_U8(
    uint8_t *indata,
    uint8_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint8_t *iv,
    uint32_t security_mode
)
{
	uint32_t flag;

    /* Enable Clock */
    __HAL_RCC_AES_SPI1_CLK_ENABLE();

	if(security_mode == AES_SPI_NORMAL_MODE)
	{
		aes_crypt_normal_u8(indata, outdata, block_len, operation, mode, iv);
        __HAL_RCC_AES_SPI1_CLK_DISABLE();
		return 	AES_SPI_PASS;	
	}
	else
	{
		flag =  aes_crypt_security_u8(indata, outdata, block_len, operation, mode, iv);
        __HAL_RCC_AES_SPI1_CLK_DISABLE();
		return flag;
	}
}




//uint32_t aes_crypt_CTR(uint32_t *indata, uint32_t *outdata, uint32_t block_len, uint8_t operation, uint32_t *ctr_iv, uint32_t *counter_val)
//{
//	uint32_t ctr_o[4];
//	uint32_t i;
//	uint32_t cnt[4];
//	for(i = 0; i < 4; i++)
//	{
//		cnt[i] = ctr_iv[i];
//	}
//	
//	if(block_len == 0)
//	{
//		return AES_FAIL;
//	}
//	
////	enable_module(BIT_AES);
////	REG_AESCTRL = 0;
////	REG_UAC_CTRL = 0x0;
//    
//    /* Enable Clock */
//    __HAL_RCC_AESSPI1_CLK_ENABLE();
//	

//	for(i = 0; i < block_len; i++)
//	{
//		printf("cnt = 0x%08x %08x %08x %08x\n",cnt[0],cnt[1],cnt[2],cnt[3]);
//		aes_func(cnt, ctr_o, AES_ECB_MODE);
//		printf("ctr_o = 0x%08x %08x %08x %08x\n",ctr_o[0],ctr_o[1],ctr_o[2],ctr_o[3]);
//		printf("indata = 0x%08x %08x %08x %08x\n\n",indata[0],indata[1],indata[2],indata[3]);

//		outdata[0] = ctr_o[0] ^ indata[0];
//		outdata[1] = ctr_o[1] ^ indata[1];
//		outdata[2] = ctr_o[2] ^ indata[2];
//		outdata[3] = ctr_o[3] ^ indata[3];
//		printf("outdata = 0x%08x %08x %08x %08x\n\n",outdata[0],outdata[1],outdata[2],outdata[3]);
//				
//		indata  += 4;
//		outdata += 4;		
//		cnt[3]++;
//		if(cnt[3] == 0x00000000)
//			cnt[2]++;
//	}	
//	
//	disable_module(BIT_AES);
//	
//	return AES_PASS;
//}

/******************************************************************************

 * Name:     aes_set_key
 * Function: aes_set_key
 * Input:
		keyin		 --	pointer to buffer of key 
		key_len		 --	select length of key(AES_KEY_128/ AES_KEY_192/ AES_KEY_256) 					
		swap_en      -- AES_SWAP_ENABLE, AES_SWAP_DISABLE						
 * Return:	 None
*******************************************************************************/
void HAL_AES_SetKey_CTR(uint32_t *keyin, uint8_t key_len, uint32_t *iv, uint8_t swap_en)
{ 
    /* Enable Clock */
    __HAL_RCC_AES_SPI1_CLK_ENABLE();
    
    AES_SPI1->CTRL = (1<<13);// sel high 5 bit
//  AES->CTRL = 0x1000; //CTR mode
    
	if(AES_SPI_SWAP_ENABLE == swap_en)
	{
		AES_SPI1->CTRL |= 0x10;		
	}
    
    if(AES_SPI_KEY_192 == key_len)
	{
	    AES_SPI1->CTRL |= (1 << 6);   
	}
	else if(AES_SPI_KEY_256 == key_len) 
	{
	    AES_SPI1->CTRL |= (2 << 6); 
	}
    
    //key128  	
	AES_SPI1->KEYIN = keyin[0];
	AES_SPI1->KEYIN = keyin[1];
	AES_SPI1->KEYIN = keyin[2];
	AES_SPI1->KEYIN = keyin[3];
    
	if(AES_SPI_KEY_192 == key_len)
	{
//		AES->CTRL |= (1 << 6);		
        AES_SPI1->KEYIN = keyin[4];
        AES_SPI1->KEYIN = keyin[5];		
	}
	else if(AES_SPI_KEY_256 == key_len)
	{
//        AES->CTRL |= (2 << 6);
		AES_SPI1->KEYIN = keyin[4];
		AES_SPI1->KEYIN = keyin[5]; 
	    AES_SPI1->KEYIN = keyin[6];
		AES_SPI1->KEYIN = keyin[7];  
	}
    
    AES_SPI1->STARTADDR = iv[0]; 
	AES_SPI1->ENDADDR = iv[1];
	AES_SPI1->INIDATA = iv[2];
	AES_SPI1->ADDR = iv[3];
    
//    __HAL_RCC_AESSPI1_CLK_DISABLE();

}

void HAL_AES_SPI_Crypt_CTR(
    uint32_t *indata,
    uint32_t *outdata,
    uint32_t *iv,
    uint32_t block_len,
    uint8_t auto_en
)
{
	uint32_t i,j;
	uint32_t ctr_o[4];
	uint32_t cnt[4];	
    
    /* Enable Clock */
    __HAL_RCC_AES_SPI1_CLK_ENABLE();
   
	AES_SPI1->CTRL &= (~0x04);//encrypt
    AES_SPI1->CTRL |= (1<<13);//AES mode
    
	if(AES_SPI_ADDR_AUTO_ENABLE == auto_en)
	{
//        AES_SPI->CTRL = 0x1000; //CTR EN, CTR mode
//		AES_SPI->CTRL |= 0x4000;
        AES_SPI1->CTRL |= (1<<14);//ADDR auto 
        AES_SPI1->CTRL |= (1<<12);//CTR EN, CTR mode 
	}
    else
    {
        AES_SPI1->CTRL &= ~0x1000; //clr CTR mode
        AES_SPI1->CTRL &= ~(1<<5); //clr CBC mode
        AES_SPI1->CTRL &= ~(1<<14);//clr addr_auto
        for(i = 0; i < 4; i++)
        {
            cnt[i] = iv[i];
        }
//printf("222 -- AES->CTRL = 0x%x\n",AES->CTRL);

    } 
   
    AES_SPI1->STARTADDR = iv[0]; 
	AES_SPI1->ENDADDR = iv[1];
	AES_SPI1->INIDATA = iv[2];
	AES_SPI1->ADDR = iv[3];
    
//    i = 0; 	
    for( j = block_len; j > 0; j-- )
    {
        if(AES_SPI_ADDR_AUTO_DISABLE == auto_en)
        {
//            AES->STARTADDR = cnt[0]; 
//            AES->ENDADDR = cnt[1];
//            AES->INIDATA = cnt[2];
//            AES->ADDR = cnt[3];  
//            printf("cnt[3] = 0x%x\n",cnt[3]);
              AES_SPI1->DATAIN = cnt[  0];		
              AES_SPI1->DATAIN = cnt[  1 ];		
              AES_SPI1->DATAIN = cnt[  2 ];		
              AES_SPI1->DATAIN = cnt[  3 ];
            
//                printf("cnt[0] = 0x%x\n",cnt[0]);
//                printf("cnt[1] = 0x%x\n",cnt[1]);
//                printf("cnt[2] = 0x%x\n",cnt[2]);
//                printf("cnt[3] = 0x%x\n",cnt[3]);
        }

		AES_SPI1->CTRL |= 0x01;
		while(  (AES_SPI1->STATE & 0x01) == 0);
		AES_SPI1->STATE = 0x01;		

		ctr_o[0] = AES_SPI1->DATAOUT;
		ctr_o[1] = AES_SPI1->DATAOUT;
		ctr_o[2] = AES_SPI1->DATAOUT;
		ctr_o[3] = AES_SPI1->DATAOUT;
        
//    printf("ctr_o[0] = 0x%x\n",ctr_o[0]);
//    printf("ctr_o[1] = 0x%x\n",ctr_o[1]);
//    printf("ctr_o[2] = 0x%x\n",ctr_o[2]);
//    printf("ctr_o[3] = 0x%x\n",ctr_o[3]);
// printf("\n");	 
//        
//            printf("indata[0] = 0x%x\n",indata[0]);
//    printf("indata[1] = 0x%x\n",indata[1]);
//    printf("indata[2] = 0x%x\n",indata[2]);
//    printf("indata[3] = 0x%x\n",indata[3]);
// printf("\n");	

		outdata[0] = ctr_o[0] ^ indata[0];
		outdata[1] = ctr_o[1] ^ indata[1];
		outdata[2] = ctr_o[2] ^ indata[2];
		outdata[3] = ctr_o[3] ^ indata[3];		

//            printf("outdata[0] = 0x%x\n",outdata[0]);
//    printf("outdata[1] = 0x%x\n",outdata[1]);
//    printf("outdata[2] = 0x%x\n",outdata[2]);
//    printf("outdata[3] = 0x%x\n",outdata[3]);
// printf("\n");
 
		indata  += 4;
		outdata += 4;		
        
        if(AES_SPI_ADDR_AUTO_DISABLE == auto_en)
        {
            cnt[3] += 0x10;  
//              cnt[3] += 0x1;  
        }
	
	}
 
 	__HAL_RCC_AES_SPI1_CLK_DISABLE();    
}

//otfdec_en : 1: select PUF + RANDOM  3: UID+RANDOM
//write only once after sysreset
void otfdec_en(uint8_t otfdec_en, uint8_t spi_sel)
{
	AES_SPI1->OTFDEC_CTRL = otfdec_en;
    AES_SPI1->OTFDEC_SPI_CTRL = spi_sel;
    
//    printf("spi_sel = 0x%x\n", spi_sel);
//    printf("AES_SPI1->OTFDEC_CTRL = 0x%x\n", AES_SPI1->OTFDEC_SPI_CTRL);

}

void otfdec_encrypt1(uint32_t *datain, uint32_t start_addr, uint32_t length,uint32_t *dataout)
{	
	uint32_t i;
	uint32_t ctr_o[4];	
	uint32_t addr;
	uint8_t otfdec_en;

	
	otfdec_en = AES_SPI1->OTFDEC_CTRL;
//	AES_SPI1->ENDADDR = MEM_ADDR + FIRST_SIZE -1; //32k
	
	if(otfdec_en)
	{
		AES_SPI1->CTRL = 0x8000;//encrypt
		
		addr = start_addr;
		AES_SPI1->ADDR = addr;
		for( i = length; i > 0; i-- )
		{
			AES_SPI1->ADDR1 = addr;
			addr += 16;  
			AES_SPI1->CTRL |= 0x01;
			while(  (AES_SPI1->STATE & 0x01) == 0);
			AES_SPI1->STATE = 0x01;		

			ctr_o[3] = AES_SPI1->DATAOUT1;
			ctr_o[2] = AES_SPI1->DATAOUT1;
			ctr_o[1] = AES_SPI1->DATAOUT1;
			ctr_o[0] = AES_SPI1->DATAOUT1;		
			
			dataout[0] = ctr_o[0] ^ datain[0];
			dataout[1] = ctr_o[1] ^ datain[1];
			dataout[2] = ctr_o[2] ^ datain[2];
			dataout[3] = ctr_o[3] ^ datain[3];		
//			if(i==length)
//			{			
//				str_printf("ctr_o[0] is 0x%x!\n",ctr_o[0]);
//				str_printf("datain[0] is 0x%x!\n",datain[0]);
//				str_printf("dataout[0] is 0x%x!\n",dataout[0]);	
//			}				
			datain  += 4;
			dataout += 4;		
			
		}
  }
	else
	{
		for( i = 0; i <(length<<2); i++)
		{
			dataout[i] = datain[i];
		}
	}
}

void otfdec_encrypt(uint32_t *datain, uint32_t start_addr, uint32_t length,uint32_t *dataout)
{	
	uint32_t i;
	uint32_t ctr_o[4];	
	uint32_t addr;
	uint8_t otfdec_en;

	
	otfdec_en = AES_SPI1->OTFDEC_CTRL;
//	AES_SPI1->ENDADDR2 = MEM_ADDR + SECOND_SIZE -1; //128k
	
	if(otfdec_en)
	{
		AES_SPI1->CTRL = 0x000;//encrypt
		
		addr = start_addr;
		
		for( i = length; i > 0; i-- )
		{
			AES_SPI1->ADDR = addr;
			addr += 16;  
			AES_SPI1->CTRL |= 0x01;
			while(  (AES_SPI1->STATE & 0x01) == 0);
			AES_SPI1->STATE = 0x01;		

			ctr_o[0] = AES_SPI1->DATAOUT;
			ctr_o[1] = AES_SPI1->DATAOUT;
			ctr_o[2] = AES_SPI1->DATAOUT;
			ctr_o[3] = AES_SPI1->DATAOUT;		
			
			dataout[0] = ctr_o[0] ^ datain[0];
			dataout[1] = ctr_o[1] ^ datain[1];
			dataout[2] = ctr_o[2] ^ datain[2];
			dataout[3] = ctr_o[3] ^ datain[3];		
//			if(i==length)
//			{			
//				str_printf("ctr_o[0] is 0x%x!\n",ctr_o[0]);
//				str_printf("datain[0] is 0x%x!\n",datain[0]);
//				str_printf("dataout[0] is 0x%x!\n",dataout[0]);	
//			}				
			datain  += 4;
			dataout += 4;		
			
		}
  }
	else
	{
		for( i = 0; i <(length<<2); i++)
		{
			dataout[i] = datain[i];
		}
	}
}


//write only once after sysreset
void otfdec_uid_set_key(uint32_t *uid, uint32_t *random)
{   
	AES_SPI1->UID = uid[0]; 
	AES_SPI1->UID = uid[1];
	AES_SPI1->UID = uid[2];
	AES_SPI1->UID = uid[3];

	AES_SPI1->RAND0 = random[0]; 
	AES_SPI1->RAND1 = random[1];
	AES_SPI1->ENDADDR = MEM_ADDR + FIRST_SIZE -1; //32k
}

void otfdec_uid_set_key2(uint32_t *key2, uint32_t *random)
{
	AES_SPI1->KEYIN2 = key2[0]; 
	AES_SPI1->KEYIN2 = key2[1];
	AES_SPI1->KEYIN2 = key2[2];
	AES_SPI1->KEYIN2 = key2[3];

	AES_SPI1->RAND2 = random[0]; 
	AES_SPI1->RAND3 = random[1];
	
	AES_SPI1->ENDADDR2 = MEM_ADDR + SECOND_SIZE -1; //128k
}

void otfdec_uid_set_key3(uint32_t *key3)
{
	AES_SPI1->KEYIN3 = key3[0]; 
	AES_SPI1->KEYIN3 = key3[1];
	AES_SPI1->KEYIN3 = key3[2];
	AES_SPI1->KEYIN3 = key3[3];
}

void otfdec_update_random23(uint32_t *random)
{
	uint32_t temp;
	AES_SPI1->OTFDEC_SPI_CTRL |= 0x20;
	temp = AES_SPI1->OTFDEC_SPI_CTRL;
	random[0] = AES_SPI1->RAND2;
	random[1] = AES_SPI1->RAND3;
}


#endif

