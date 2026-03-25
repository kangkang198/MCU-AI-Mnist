/******************************************************************************
*@file  : hal_cde.c
*@brief : cde module file
*@ver   : 1.0.0
*@date  : 2023.2.3
******************************************************************************/

//ARMCC  command line options: --target=arm-arm-none-eabi -mcpu=cortex-m33+cdecpN
//for example: --target=arm-arm-none-eabi -mcpu=cortex-m33+cdecp0

//fromelf command line option: --coprocN=CDE
//for example: fromelf.exe --bin -c --cpu=8.1-M.Main.mve.fp --coproc0=CDE --output ./Objects/Project.bin ./Objects/Project.axf
//for example: fromelf.exe --bin -c --cpu=cortex-m33 --coproc0=CDE --output ./Objects/Project.bin ./Objects/Project.axf


#include "hal.h" 

/******************************************************************************
*@brief : enable coopration processor number
*@param : num : coopration processor number
*@return: none
******************************************************************************/
void HAL_CDE_EnableCPx(int num)
{  
    SCB->CPACR |= (3UL << num*2);  //0xE000ED88
    HAL_SimpleDelay(10);
}

/******************************************************************************
*@brief : enable coopration processor number
*@param : num : coopration processor number
*@return: none
******************************************************************************/
void HAL_CDE_DisableCPx(int num)
{  
    SCB->CPACR &= ~(3UL << num*2);  //0xE000ED88
    HAL_SimpleDelay(10);
}
