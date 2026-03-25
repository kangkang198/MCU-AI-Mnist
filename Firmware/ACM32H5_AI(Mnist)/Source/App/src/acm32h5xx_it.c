/******************************************************************************
*@file  : acm32h5xx_it.c
*@brief : Main Interrupt Service Routines
*           This file provides template for all exceptions handler and 
*           peripherals interrupt service routine.  
******************************************************************************/

#include "acm32h5xx_it.h"

void NMI_Handler(void)
{   
}


void HardFault_Handler(void)
{
    printf("HardFault_Handler\r\n");
    while (1)
    {
    }
}


void MemManage_Handler(void)
{
    printf("MemManage_Handler\r\n");
    while (1)
    {
    }
}


void BusFault_Handler(void)
{
    printf("BusFault_Handler\r\n");
    while (1)
    {
    }
}


void UsageFault_Handler(void)
{
    printf("UsageFault_Handler\r\n");
    while (1)
    {
    }
}


void SVC_Handler(void)
{
}


void DebugMon_Handler(void)
{
}


void PendSV_Handler(void)
{
}


/******************************************************************************
*@brief : System tick handler
*@param : none
*@return: none
******************************************************************************/
void SysTick_Handler(void)
{
    // lv_tick_inc(1);
	HAL_IncTick();
}


