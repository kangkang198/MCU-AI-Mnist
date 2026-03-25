/*
  ******************************************************************************
  * @file    System_Accelerate.c
  * @author  AisinoChip Firmware Team
  * @version V1.0.0
  * @date    2020
  * @brief   MCU Cache Peripheral Access Layer System Source File.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 AisinoChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "hal.h"

#include "system_accelerate.h"

/* Cache Size ID Register Macros */
#define CCSIDR_WAYS(x)         (((x) & SCB_CCSIDR_ASSOCIATIVITY_Msk) >> SCB_CCSIDR_ASSOCIATIVITY_Pos)
#define CCSIDR_SETS(x)         (((x) & SCB_CCSIDR_NUMSETS_Msk      ) >> SCB_CCSIDR_NUMSETS_Pos      )

#ifndef __SCB_DCACHE_LINE_SIZE
#define __SCB_DCACHE_LINE_SIZE  32U /*!< Cortex-M7 cache line size is fixed to 32 bytes (8 words). See also register SCB_CCSIDR */
#endif

#ifndef __SCB_ICACHE_LINE_SIZE
#define __SCB_ICACHE_LINE_SIZE  32U /*!< Cortex-M7 cache line size is fixed to 32 bytes (8 words). See also register SCB_CCSIDR */
#endif

/*********************************************************************************
* Function    : System_EnableIAccelerate
* Description : Enable I-Cache
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020定
**********************************************************************************/
void System_EnableIAccelerate(void)
{
    if (SCB->CCR & SCB_CCR_IC_Msk)          /* return if ICache is already enabled */
    {
        return;   
    }
    __DSB();
    __ISB();
    SCB->ICIALLU = 0UL;                     /* invalidate I-Cache */
    __DSB();
    __ISB();
    SCB->CCR |= (uint32_t)SCB_CCR_IC_Msk;   /* enable I-Cache */
    __DSB();
    __ISB();
}

/*********************************************************************************
* Function    : System_DisableIAccelerate
* Description : Disable I-Cache
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020定
**********************************************************************************/
void System_DisableIAccelerate(void)
{
    __DSB();
    __ISB();
    
    SCB->CCR &= ~(uint32_t)SCB_CCR_IC_Msk;  /* disable I-Cache */    
    SCB->ICIALLU = 0UL;                     /* invalidate I-Cache */
    __DSB();
    __ISB();
}

/*********************************************************************************
* Function    : System_InvalidateIAccelerate
* Description : Invalidate I-Cache
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020定
**********************************************************************************/
void System_InvalidateIAccelerate(void)
{
    __DSB();
    __ISB();
    SCB->ICIALLU = 0UL;
    __DSB();
    __ISB();
}

/**
  \brief   I-Cache Invalidate by address
  \details Invalidates I-Cache for the given address.
           I-Cache is invalidated starting from a 32 byte aligned address in 32 byte granularity.
           I-Cache memory blocks which are part of given address + given size are invalidated.
  \param[in]   addr    address
  \param[in]   isize   size of memory block (in number of bytes)
*/
void System_InvalidateIAccelerate_by_Addr (volatile void *addr, int32_t isize)
{
    if ( isize > 0 ) {
       int32_t op_size = isize + (((uint32_t)addr) & (__SCB_ICACHE_LINE_SIZE - 1U));
      uint32_t op_addr = (uint32_t)addr /* & ~(__SCB_ICACHE_LINE_SIZE - 1U) */;

      __DSB();

      do {
        SCB->ICIMVAU = op_addr;             /* register accepts only 32byte aligned values, only bits 31..5 are valid */
        op_addr += __SCB_ICACHE_LINE_SIZE;
        op_size -= __SCB_ICACHE_LINE_SIZE;
      } while ( op_size > 0 );

      __DSB();
      __ISB();
    }
}

/*********************************************************************************
* Function    : System_EnableDAccelerate
* Description : Enable D-Cache
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020定
**********************************************************************************/
void System_EnableDAccelerate(void)
{
    uint32_t ccsidr;
    uint32_t sets;
    uint32_t ways;
    
    if (SCB->CCR & SCB_CCR_DC_Msk) return;  /* return if DCache is already enabled */
    
    SCB->CSSELR = 0U;                       /* select Level 1 data cache */
    __DSB();

    ccsidr = SCB->CCSIDR;
    
    /* invalidate D-Cache */
    sets = (uint32_t)(CCSIDR_SETS(ccsidr));
    do 
    {
        ways = (uint32_t)(CCSIDR_WAYS(ccsidr));
        do 
        {
            SCB->DCISW = (((sets << SCB_DCISW_SET_Pos) & SCB_DCISW_SET_Msk) |
                          ((ways << SCB_DCISW_WAY_Pos) & SCB_DCISW_WAY_Msk));
            #if defined ( __CC_ARM )
                __schedule_barrier();
            #endif
        }while (ways-- != 0U);
    }while(sets-- != 0U);
    
    __DSB();
    
    SCB->CCR |=  (uint32_t)SCB_CCR_DC_Msk;  /* enable D-Cache */
    
    __DSB();
    __ISB();    
}

/*********************************************************************************
* Function    : System_DisableDAccelerate
* Description : Disable D-Cache
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020定
**********************************************************************************/
void System_DisableDAccelerate(void)
{
    struct {
      uint32_t ccsidr;
      uint32_t sets;
      uint32_t ways;
    } locals;

    SCB->CSSELR = 0U; /*(0U << 1U) | 0U;*/  /* select Level 1 data cache */
    __DSB();

    SCB->CCR &= ~(uint32_t)SCB_CCR_DC_Msk;  /* disable D-Cache */
    __DSB();

#if !defined(__OPTIMIZE__)
      /*
       * For the endless loop issue with no optimization builds.
       * More details, see https://github.com/ARM-software/CMSIS_5/issues/620
       *
       * The issue only happens when local variables are in stack. If
       * local variables are saved in general purpose register, then the function
       * is OK.
       *
       * When local variables are in stack, after disabling the cache, flush the
       * local variables cache line for data consistency.
       */
    SCB->DCCIMVAC = (uint32_t)&locals.sets;
    SCB->DCCIMVAC = (uint32_t)&locals.ways;
    SCB->DCCIMVAC = (uint32_t)&locals.ccsidr;    
    __DSB();
    __ISB();
#endif    
    
    locals.ccsidr = SCB->CCSIDR;

    /* clean & invalidate D-Cache */
    locals.sets = (uint32_t)(CCSIDR_SETS(locals.ccsidr));
    do 
    {
        locals.ways = (uint32_t)(CCSIDR_WAYS(locals.ccsidr));
        do 
        {
            SCB->DCCISW = (((locals.sets << SCB_DCCISW_SET_Pos) & SCB_DCCISW_SET_Msk) |
                           ((locals.ways << SCB_DCCISW_WAY_Pos) & SCB_DCCISW_WAY_Msk));
            #if defined ( __CC_ARM )
                __schedule_barrier();
            #endif
        }while(locals.ways-- != 0U);
    }while(locals.sets-- != 0U);

    __DSB();
    __ISB(); 
}

/*********************************************************************************
* Function    : System_InvalidateDAccelerate
* Description : Invalidate D-Cache
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020定
**********************************************************************************/
void System_InvalidateDAccelerate(void)
{
    uint32_t ccsidr;
    uint32_t sets;
    uint32_t ways;

    SCB->CSSELR = 0U; /*(0U << 1U) | 0U;*/  /* Level 1 data cache */
    __DSB();

    ccsidr = SCB->CCSIDR;

    /* invalidate D-Cache */
    sets = (uint32_t)(CCSIDR_SETS(ccsidr));
    do 
    {
        ways = (uint32_t)(CCSIDR_WAYS(ccsidr));
        do 
        {
            SCB->DCISW = (((sets << SCB_DCISW_SET_Pos) & SCB_DCISW_SET_Msk) |
                          ((ways << SCB_DCISW_WAY_Pos) & SCB_DCISW_WAY_Msk));
            #if defined ( __CC_ARM )
                __schedule_barrier();
            #endif
        }while(ways-- != 0U);
    }while(sets-- != 0U);

    __DSB();
    __ISB();
}

/*********************************************************************************
* Function    : System_CleanDAccelerate
* Description : Clean D-Cache
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020定
**********************************************************************************/
void System_CleanDAccelerate(void)
{
    uint32_t ccsidr;
    uint32_t sets;
    uint32_t ways;

    SCB->CSSELR = 0U; /*(0U << 1U) | 0U;*/  /* Level 1 data cache */
    __DSB();

    ccsidr = SCB->CCSIDR;

    /* clean D-Cache */
    sets = (uint32_t)(CCSIDR_SETS(ccsidr));
    do 
    {
        ways = (uint32_t)(CCSIDR_WAYS(ccsidr));
        do 
        {
            SCB->DCCSW = (((sets << SCB_DCCSW_SET_Pos) & SCB_DCCSW_SET_Msk) |
                          ((ways << SCB_DCCSW_WAY_Pos) & SCB_DCCSW_WAY_Msk));
            #if defined ( __CC_ARM )
                __schedule_barrier();
            #endif
        } while (ways-- != 0U);
    } while(sets-- != 0U);

    __DSB();
    __ISB();
}

/*********************************************************************************
* Function    : System_CleanInvalidateDAccelerate
* Description :  Cleans and Invalidates D-Cache
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
void System_CleanInvalidateDAccelerate(void)
{
    uint32_t ccsidr;
    uint32_t sets;
    uint32_t ways;

    SCB->CSSELR = 0U; /*(0U << 1U) | 0U;*/  /* Level 1 data cache */
    __DSB();

    ccsidr = SCB->CCSIDR;

                                            /* clean & invalidate D-Cache */
    sets = (uint32_t)(CCSIDR_SETS(ccsidr));
    do {
      ways = (uint32_t)(CCSIDR_WAYS(ccsidr));
      do {
        SCB->DCCISW = (((sets << SCB_DCCISW_SET_Pos) & SCB_DCCISW_SET_Msk) |
                       ((ways << SCB_DCCISW_WAY_Pos) & SCB_DCCISW_WAY_Msk)  );
        #if defined ( __CC_ARM )
          __schedule_barrier();
        #endif
      } while (ways-- != 0U);
    } while(sets-- != 0U);

    __DSB();
    __ISB();
}

/*********************************************************************************
* Function    : System_InvalidateDAccelerate
* Description : Invalidate D-Cache by addr
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020定
**********************************************************************************/
void System_InvalidateDAccelerate_by_Addr (volatile void *addr, int32_t dsize)
{
    if ( dsize > 0 ) {
       int32_t op_size = dsize + (((uint32_t)addr) & (__SCB_DCACHE_LINE_SIZE - 1U));
      uint32_t op_addr = (uint32_t)addr /* & ~(__SCB_DCACHE_LINE_SIZE - 1U) */;

      __DSB();

      do {
        SCB->DCIMVAC = op_addr;             /* register accepts only 32byte aligned values, only bits 31..5 are valid */
        op_addr += __SCB_DCACHE_LINE_SIZE;
        op_size -= __SCB_DCACHE_LINE_SIZE;
      } while ( op_size > 0 );

      __DSB();
      __ISB();
    }
}

/*********************************************************************************
* Function    : System_CleanDAccelerate_by_Addr
* Description : Cleans D-Cache for the given address
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
void System_CleanDAccelerate_by_Addr (volatile void *addr, int32_t dsize)
{
    if ( dsize > 0 ) {
       int32_t op_size = dsize + (((uint32_t)addr) & (__SCB_DCACHE_LINE_SIZE - 1U));
      uint32_t op_addr = (uint32_t)addr /* & ~(__SCB_DCACHE_LINE_SIZE - 1U) */;

      __DSB();

      do {
        SCB->DCCMVAC = op_addr;             /* register accepts only 32byte aligned values, only bits 31..5 are valid */
        op_addr += __SCB_DCACHE_LINE_SIZE;
        op_size -= __SCB_DCACHE_LINE_SIZE;
      } while ( op_size > 0 );

      __DSB();
      __ISB();
    }
}

/*********************************************************************************
* Function    : System_CleanInvalidateDAccelerate_by_Addr
* Description : Cleans and invalidates D_Cache for the given address
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
void System_CleanInvalidateDAccelerate_by_Addr (volatile void *addr, int32_t dsize)
{
    if ( dsize > 0 ) {
       int32_t op_size = dsize + (((uint32_t)addr) & (__SCB_DCACHE_LINE_SIZE - 1U));
      uint32_t op_addr = (uint32_t)addr /* & ~(__SCB_DCACHE_LINE_SIZE - 1U) */;

      __DSB();

      do {
        SCB->DCCIMVAC = op_addr;            /* register accepts only 32byte aligned values, only bits 31..5 are valid */
        op_addr +=          __SCB_DCACHE_LINE_SIZE;
        op_size -=          __SCB_DCACHE_LINE_SIZE;
      } while ( op_size > 0 );

      __DSB();
      __ISB();
    }
}



