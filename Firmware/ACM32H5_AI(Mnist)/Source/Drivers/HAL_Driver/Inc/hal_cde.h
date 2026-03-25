/******************************************************************************
*@file  : hal_cde.h
*@brief : cde header file
*@ver   : 1.0.0
*@date  : 2023.2.3
******************************************************************************/


#ifndef _HAL_CDE_H
#define _HAL_CDE_H

#include "hal.h"

void HAL_CDE_EnableCPx(int num);

void HAL_CDE_DisableCPx(int num);

#define ROTATE_LEFT(n,x)    __ROR(x,32-n)
#define SM3_P0(x)           x^ ROTATE_LEFT(9,x) ^  ROTATE_LEFT(17,x)
#define SM3_P1(x)           x^ ROTATE_LEFT(15,x) ^  ROTATE_LEFT(23,x)
#define SM4_T1(x)           x^ ROTATE_LEFT(2,x) ^  ROTATE_LEFT(10,x) ^  ROTATE_LEFT(18,x) ^  ROTATE_LEFT(24,x)
#define SM4_T2(x)           x^ ROTATE_LEFT(13,x) ^  ROTATE_LEFT(23,x)

#define SM3_FF2(x,y,z)      (x&y)|(x&z)|(y&z)						// Rounds  16-63  x,y,z is word length;
#define SM3_GG2(x,y,z)      (x&y)|(~x&z)							// Rounds  16-63 x,y,z is word length;


/*
   Counting the number of ones in a 32 bit register.
   The output of this instruction is a 32 bit register, containing
   the number of ones
   
refrence C-code:
   
uint32_t POPCNT(uint32_t a) {
  a = (a&0x55555555) + ((a&0xaaaaaaaa)>> 1);
  a = (a&0x33333333) + ((a&0xcccccccc)>> 2);
  a = (a&0x0f0f0f0f) + ((a&0xf0f0f0f0)>> 4);
  a = (a&0x00ff00ff) + ((a&0xff00ff00)>> 8);
  a = (a&0x0000ffff) + ((a&0xffff0000)>>16);
  return a;
}   
*/
#define __HAL_CDE_POPCNT(a)       __arm_cx1a(0, (a), 1)


/*
   Reverse bit order of byte in a 32 bit register.
   For example, 0x112233344 becomes 0x8844cc22
   
refrence C-code:
   
UINT8 reverse_byte(UINT8 in_data)
{
	UINT8 temp;
	UINT8 i;

	temp = 0;
	for(i = 0; i < 8; i++)
	{
		if(in_data & (1 << i))
		{
			temp |= 0x80 >> i;
		}
	}

	return temp;
}  
*/
#define __HAL_CDE_BYTE_REVERSE(a)       __arm_cx1a(0, (a), 2)

/*
   SM3_P0
   
refrence C-code:
   
#define SM3_P0(x)           x^ ROTATE_LEFT(9,x) ^  ROTATE_LEFT(17,x)  
*/
#define __HAL_CDE_SM3_P0(a)       __arm_cx1a(0, (a), 3)

/*
   SM3_P1
   
refrence C-code:
   
#define SM3_P1(x)           x^ ROTATE_LEFT(15,x) ^  ROTATE_LEFT(23,x) 
*/
#define __HAL_CDE_SM3_P1(a)       __arm_cx1a(0, (a), 4)

/*
   SM4_T1
   
refrence C-code:
   
#define SM4_T1(x)           x^ ROTATE_LEFT(2,x) ^  ROTATE_LEFT(10,x) ^  ROTATE_LEFT(18,x) ^  ROTATE_LEFT(24,x)
*/
#define __HAL_CDE_SM4_T1(a)       __arm_cx1a(0, (a), 5)


/*
   SM4_T2
   
refrence C-code:
   
#define SM4_T2(x)           x^ ROTATE_LEFT(13,x) ^  ROTATE_LEFT(23,x) 
*/
#define __HAL_CDE_SM4_T2(a)       __arm_cx1a(0, (a), 6)

/*
    CRC32 instruction for updating a 32 bit state register by 8 bit input
    data using the ISO 3309 standard.
    Polynomial representation (reversed) : 0xEDB88320
    
refrence C-code:

#define POLYNOMIAL 0xedb88320
uint32_t CRC32(uint32_t crc, uint32_t d) {
  crc = crc ^ (d&0xff);
  if (crc&1) crc = (crc>>1) ^ POLYNOMIAL;  else crc = (crc>>1);
  if (crc&1) crc = (crc>>1) ^ POLYNOMIAL;  else crc = (crc>>1);
  if (crc&1) crc = (crc>>1) ^ POLYNOMIAL;  else crc = (crc>>1);
  if (crc&1) crc = (crc>>1) ^ POLYNOMIAL;  else crc = (crc>>1);
  if (crc&1) crc = (crc>>1) ^ POLYNOMIAL;  else crc = (crc>>1);
  if (crc&1) crc = (crc>>1) ^ POLYNOMIAL;  else crc = (crc>>1);
  if (crc&1) crc = (crc>>1) ^ POLYNOMIAL;  else crc = (crc>>1);
  if (crc&1) crc = (crc>>1) ^ POLYNOMIAL;  else crc = (crc>>1);
  return crc;
}
*/

/*
   SM3_FF2
   
refrence C-code:
   
#define SM3_FF2(x,y,z)      (x&y)|(x&z)|(y&z)						// Rounds  16-63  x,y,z is word length;
*/
#define __HAL_CDE_SM3_FF2(x, y, z)  __arm_cx3a(0,x, y, z,1) 

/*
   SM3_GG2
   
refrence C-code:
   
#define SM3_GG2(x,y,z)      (x&y)|(~x&z)							// Rounds  16-63 x,y,z is word length;
*/
#define __HAL_CDE_SM3_GG2(x, y, z)  __arm_cx3a(0,x, y, z,10) 



#define __HAL_CDE_CRC32_REVERSE(crc, d)     __arm_cx2a(0, (crc), (d), 2) //cpu内部对初始值和数据以及结果进行反序

/*
CRC module for data[31:0] , crc32[31:0]=1+x^1+x^2+x^4+x^5+x^7+x^8+x^10+x^11+x^12+x^16+x^22+x^23+x^26+x^32;
多项式：0x04C11DB7
支持一次计算一个字
*/
#define __HAL_CDE_CRC32_32BIT(crc, d)     __arm_cx2a(0, (crc), (d), 1) //内部会对d 进行字内倒序，即输入d[31:0] 会转换为 {d[7:0],d[15:8],d[23:16],d[31:24]}



/*  This instruction extracts 32 bits from two 32 bit registers.
    res[ 0:23] = a[8:31]
    res[24:31] = b[0:7]

refrence C-code:

uint32_t PACK8(uint32_t a, uint32_t b) {
  return (a >> 8) | (b << 24);
}
*/
#define __HAL_CDE_PACK8(a, b)       __arm_cx3(0,(a),(b), 4)


/*  This instruction extracts 32 bits from two 32 bit registers.
    res[ 0:15] = a[16:31]
    res[16:31] = b[0:15]
    
refrence C-code:

uint32_t PACK16(uint32_t a, uint32_t b) {
  return (a >> 16) | (b << 16);
}
*/
#define __HAL_CDE_PACK16(a, b)      __arm_cx3(0,(a),(b), 5)

/*  Instruction for updating the FIR filter delay line by two 8 bit operands
    This instruction extracts 32 bits from two 32 bit registers.
    res[ 0:7] = a[24:31]
    res[8:31] = b[0:23]
    
refrence C-code:

uint32_t PACK24(uint32_t a, uint32_t b) {
  return (a >> 24) | (b << 8);
}
*/
#define __HAL_CDE_PACK24(a, b)      __arm_cx3(0,(a),(b), 6)


/*  This instruction does four 8x8 bit unsigned multiplicaltions forming
    four 16 bit products.
    The four products and the accumulator 'a' are added, and the 32 bit
    result is returned from the instruction.
    
refrence C-code:

uint32_t UMLAQ(uint32_t a, uint32_t b, uint32_t c) {
  uint16_t a0, a1, a2, a3;
  a0 = (uint16_t)((b >>  0) & 0xff) * (uint16_t)((c >>  0) & 0xff);
  a1 = (uint16_t)((b >>  8) & 0xff) * (uint16_t)((c >>  8) & 0xff);
  a2 = (uint16_t)((b >> 16) & 0xff) * (uint16_t)((c >> 16) & 0xff);
  a3 = (uint16_t)((b >> 24) & 0xff) * (uint16_t)((c >> 24) & 0xff);
  return a + (uint32_t)a0 + (uint32_t)a1 + (uint32_t)a2 + (uint32_t)a3;
}
*/
#define __HAL_CDE_UMLAQ(a, b, c)    __arm_cx3a(0,(a),(b),(c), 2)


/*  This instruction does four 8x8 bit unsigned multiplicaltions forming
    four 16 bit products.
    The four products are added, and the 32 bit result is returned from
    the instruction.

uint32_t UMUAQ(uint32_t b, uint32_t c) {
  uint16_t a0, a1, a2, a3;
  a0 = (uint16_t)((b >>  0) & 0xff) * (uint16_t)((c >>  0) & 0xff);
  a1 = (uint16_t)((b >>  8) & 0xff) * (uint16_t)((c >>  8) & 0xff);
  a2 = (uint16_t)((b >> 16) & 0xff) * (uint16_t)((c >> 16) & 0xff);
  a3 = (uint16_t)((b >> 24) & 0xff) * (uint16_t)((c >> 24) & 0xff);
  return (uint32_t)a0 + (uint32_t)a1 + (uint32_t)a2 + (uint32_t)a3;
}
*/
#define __HAL_CDE_UMUAQ(b, c)       __arm_cx3(0,(b),(c), 7)


/*  This instruction does four 8 bit signed by 8 bit unsigned multi-
    plications forming four 16 bit products.
    The four products and the accumulator 'a' are added, and the 32 bit
    result is returned from the instruction.

int32_t SUMLAQ(int32_t a, uint32_t b, uint32_t c) {
  int16_t a0, a1, a2, a3;
  a0 = (int16_t)(int8_t)((b >>  0) & 0xff) * (int16_t)(uint8_t)((c >>  0) & 0xff);
  a1 = (int16_t)(int8_t)((b >>  8) & 0xff) * (int16_t)(uint8_t)((c >>  8) & 0xff);
  a2 = (int16_t)(int8_t)((b >> 16) & 0xff) * (int16_t)(uint8_t)((c >> 16) & 0xff);
  a3 = (int16_t)(int8_t)((b >> 24) & 0xff) * (int16_t)(uint8_t)((c >> 24) & 0xff);
  return a + (int32_t)a0 + (int32_t)a1 + (int32_t)a2 + (int32_t)a3;
}
*/
#define __HAL_CDE_SUMLAQ(a, b, c)   __arm_cx3a(0,(a),(b),(c), 3)


/*  This instruction does four 8 bit signed by 8 bit unsigned multi-
    plications forming four 16 bit products.
    The four products are added, and the 32 bit result is returned from
    the instruction.

int32_t SUMUAQ(uint32_t b, uint32_t c) {
  int16_t a0, a1, a2, a3;
  a0 = (int16_t)(int8_t)((b >>  0) & 0xff) * (int16_t)(uint8_t)((c >>  0) & 0xff);
  a1 = (int16_t)(int8_t)((b >>  8) & 0xff) * (int16_t)(uint8_t)((c >>  8) & 0xff);
  a2 = (int16_t)(int8_t)((b >> 16) & 0xff) * (int16_t)(uint8_t)((c >> 16) & 0xff);
  a3 = (int16_t)(int8_t)((b >> 24) & 0xff) * (int16_t)(uint8_t)((c >> 24) & 0xff);
  return (int32_t)a0 + (int32_t)a1 + (int32_t)a2 + (int32_t)a3;
}
*/
#define __HAL_CDE_SUMUAQ(b, c)      __arm_cx3(0,(b),(c), 8)


/*
  This function calculates the hamming distance between two input registers
 
  Input registers takes any value, valid output values [0:31]
  Do not use {A} CDE type, proposed CDE instruction: cx3(p0, a, b, c, #)

uint32_t HAMMING_DIST(uint32_t b, uint32_t c) { 
  uint32_t i, a, val;
 
  val = b ^ c;
  a = 0;
  for (i = 0; i < 32; i++) {
    a = a + (val & 1);
    val = val >> 1;
  }
 
  return a;
}
*/
#define __HAL_CDE_HAMMING_DIST(b, c)   __arm_cx3(0,b,c, 9)

/*
   parity of the number of ones in a 32 bit register.
   For example, 0x11  : 0
	            0x23  : 1
                0xffff: 0  
refrence C-code:
__builtin_parity   
*/
#define __HAL_CDE_PARITY(a)       __arm_cx1a(0, (a), 7)

/*
   Reverse bit order of u16 in a 32 bit register.
   For example, 0x11223344 becomes 0x448822cc
   
refrence C-code:
   
UINT8 reverse_u16(UINT16 in_data)
{
	UINT8 temp;
	UINT8 i;

	temp = 0;
	for(i = 0; i < 16; i++)
	{
		if(in_data & (1 << i))
		{
			temp |= 0x8000 >> i;
		}
	}

	return temp;
}  
*/
#define __HAL_CDE_U16_REVERSE(a)       __arm_cx1a(0, (a), 8)

/*
   Counts the number of tailing zeros of a data value.
   For example, 0x00      : 32
								0x11      : 0
	              0x1122		: 1
                0x80000000: 31
refrence C-code:
__builtin_ctz

*/
#define __HAL_CDE_CTZ(a)       __arm_cx2a(0, a, 0, 3)

/*
   from back to front, which position of bit 1 in a data value.
   For example, 0x00      : 32
				0x11      : 1
	            0x1122	  : 2
                0x80000000: 32
refrence C-code:
__builtin_ffs

*/
#define __HAL_CDE_FFS(a)       __arm_cx2a(0, a, 1, 3)


/*
   byte amplification
   For example, bit[7:0] a = 01101011
								      b=1  : bit[15:0] 00 11 11 00 11 00 11 11
										  b=2	 : bit[31:0] 00000000 000 111 111 000 111 000 111 111
                      b=4  : bit[31:0] 0000 1111 1111 0000 1111 0000 1111 1111
refrence C-code:


*/
#define __HAL_CDE_BYTE_AMP(a,b)       __arm_cx2a(0, a, b, 4)

/*  This instruction extracts 8 bits from two 8 bit registers.
	
refrence C-code:
uint8_t BYTE_PACKN(uint8_t a, uint8_t b, uint8_t n) {
  return (a >> n) | (b << (8-n));
}
uint32_t WORD_PACKN(uint32_t a, uint32_t b, uint8_t n) {
	uint32_t c,c1,c2,c3,c4;
	c1 = ((a&0xff) >> n) | ((b&0xff) << (8-n));
	c2 = ((a&0xff00) >> n) | ((b&0xff00) << (8-n));
	c3 = ((a&0xff0000) >> n) | ((b&0xff0000) << (8-n));
	c4 = ((a&0xff000000) >> n) | ((b&0xff000000) << (8-n));
	c = (c1&0xff) | (c2&0xff00) | (c3&0xff0000) | (c4&0xff000000);
  return c;
}
*/
#define __HAL_CDE_BYTE_PACKN(a, b,n)       __arm_cx3a(0,(a),(b), n,11)

/*  This instruction extracts 8 bits from two 8 bit registers.
	
refrence C-code:
uint32_t BYTE3_PACKN(uint32_t a, uint8_t n) {
	uint8_t c,c1,c2,c3;
	uint8_t a1,a2,a3,a4;
	a1 = (a&0xff);
	a2 = (a&0xff00)>>8;
	a3 = (a&0xff0000)>>16;
	a4 = (a&0xff000000)>>24;
	c1 = (a1 >> n) | (a2 << (8-n));
	c2 = (a2 >> n) | (a3 << (8-n));
	c3 = (a3 >> n) | (a4 << (8-n));
	c = (c1&0xff) | ((c2<<8)&0xff00) | ((c3<<16)&0xff0000);
  return c;
}
*/
#define __HAL_CDE_3BYTE_PACKN(a,n)       __arm_cx2a(0,(a),n,5)

/*  This instruction extracts 8 bits from two 8 bit registers.
	
refrence C-code:
uint64_t BYTE7_PACKN(uint64_t a, uint8_t n) {
	uint64_t c,c1,c2,c3,c4,c5,c6,c7;
	uint8_t a1,a2,a3,a4,a5,a6,a7,a8;
	a1 = (a&0xff);
	a2 = (a&0xff00)>>8;
	a3 = (a&0xff0000)>>16;
	a4 = (a&0xff000000)>>24;
	a5 = (a&0xff00000000)>>32;
	a6 = (a&0xff0000000000)>>40;
	a7 = (a&0xff000000000000)>>48;
	a8 = (a&0xff00000000000000)>>56;
	c1 = (a1 >> n) | (a2 << (8-n));
	c2 = (a2 >> n) | (a3 << (8-n));
	c3 = (a3 >> n) | (a4 << (8-n));
	c4 = (a4 >> n) | (a5 << (8-n)); 
	c5 = (a5 >> n) | (a6 << (8-n));
	c6 = (a6 >> n) | (a7 << (8-n));
	c7 = (a7 >> n) | (a8 << (8-n));	
	c = (c1&0xff) | ((c2<<8)&0xff00) | ((c3<<16)&0xff0000) | ((c4<<24)&0xff000000) | ((c5<<32)&0xff00000000) | ((c6<<40)&0xff000000000) | ((c7<<48)&0xff000000000000);
  return c;
}
*/
#define __HAL_CDE_7BYTE_PACKN(a,n)       __arm_cx2da(0,(a),n,6)

#endif


