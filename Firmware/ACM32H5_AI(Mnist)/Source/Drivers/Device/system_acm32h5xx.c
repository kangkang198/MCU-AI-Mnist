
/******************************************************************************
*@file  : system_acm32h5xx.c
*@brief : CMSIS Cortex-M33 Device Peripheral Access Layer System Source File
******************************************************************************/

#include "acm32h5xx_hal_conf.h"

#ifdef DATA_IN_ExtSRAM
  void SystemInit_ExtMemCtl(void); 
#endif

/******************************************************************************
*@note  : g_SystemCoreClock variable is updated in three ways:
*           1) by calling CMSIS function SystemCoreClockUpdate()
*           2) by calling HAL API function HAL_RCC_GetSysCoreClockFreq()
*           3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency 
*               If you use this function to configure the system clock; then there
*               is no need to call the 2 first functions listed above, since g_SystemCoreClock
*               variable is updated automatically.
******************************************************************************/
volatile uint32_t SystemCoreClock = 64000000;

/******************************************************************************
*@brief : configure FPU and vector table address
*         - This function is called at startup just after reset and before branch to main program. 
*         - This call is made inside the "startup_acm32h5xx.s" file
*@param : none
*@return: none
******************************************************************************/
__attribute__((weak)) void SystemInit(void)
{
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
		/* set CP10 and CP11 Full Access */
		SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));
	#endif
    
    RCC->RCHCR |= RCC_RCHCR_RCHEN;
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    while (!(RCC->RCHCR & RCC_RCHCR_RCHRDY)) {};
    RCC->RCHCR &= ~RCC_RCHCR_RCHSEL;
    RCC->CCR1 &= ~RCC_CCR1_SYSCLKSEL;
    
    RCC->PLL1CR &= ~RCC_PLL1CR_PLL1EN;
    RCC->PLL1SCR = 0;
    RCC->PLL1CR |= RCC_PLL1CR_PLL1SLEEP;
    RCC->PLL2CR &= ~RCC_PLL2CR_PLL2EN;
    RCC->PLL2SCR = 0;
    RCC->PLL2CR |= RCC_PLL2CR_PLL2SLEEP;
    RCC->PLL3CR &= ~RCC_PLL3CR_PLL3EN;
    RCC->PLL3CR |= RCC_PLL3CR_PLL3SLEEP;
        
    RCC->RCHCR &= ~RCC_RCHCR_RCHDIV;
    
    RCC->CCR2 &= ~RCC_CCR2_SYSDIV0;
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    while (!(RCC->CCR2 & RCC_CCR2_DIVDONE)) {};
    
    RCC->CCR2 &= ~RCC_CCR2_SYSDIV1;
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();
    while (!(RCC->CCR2 & RCC_CCR2_DIVDONE)) {};
    
    RCC->CCR2 &= ~(RCC_CCR2_PCLK1DIV | RCC_CCR2_PCLK2DIV | RCC_CCR2_PCLK3DIV | RCC_CCR2_PCLK4DIV);
	     
	#ifdef DATA_IN_ExtSRAM
		SystemInit_ExtMemCtl(); 
	#endif /* DATA_IN_ExtSRAM || DATA_IN_ExtSDRAM */

    SCB->VTOR = VECT_TAB_ADDR;
    
	#if (INS_ACCELERATE_ENABLE)
		System_EnableIAccelerate();
    #else
		System_DisableIAccelerate();
	#endif
}

/******************************************************************************
*@brief : Update g_SystemCoreClock variable according to Clock Register Values.
*         The SystemCoreClock variable contains the core clock (HCLK), it can
*         be used by the user application to setup the SysTick timer or configure
*         other parameters.
*           
*@note  : Each time the core clock (HCLK) changes, this function must be called
*         to update SystemCoreClock variable value. Otherwise, any configuration
*         based on this variable will be incorrect.  
*@param : none
*@return: none
******************************************************************************/
void SystemCoreClockUpdate(void)
{
    HAL_RCC_GetSysCoreClockFreq();   
}


/******************************************************************************
*@brief : fast config system core clock. 
*@param : sysclkSel: system core clk select, see SYSCLK_SelectTypeDef  enum
*@param : pclk1Div: pclk1 div select
*           @arg RCC_PCLK1_DIV_1
*           @arg RCC_PCLK1_DIV_2
*           @arg RCC_PCLK1_DIV_4
*           @arg RCC_PCLK1_DIV_8
*           @arg RCC_PCLK1_DIV_16
*@param : pclk2Div: pclk2 div select
*           @arg RCC_PCLK2_DIV_1
*           @arg RCC_PCLK2_DIV_2
*           @arg RCC_PCLK2_DIV_4
*           @arg RCC_PCLK2_DIV_8
*           @arg RCC_PCLK2_DIV_16
*@note  : PLLPCLK = Fin * PLLF / PLLN / PLLP
*         PLLQCLK = Fin * PLLF / PLLN / PLLQ
*         1MHz <= ( Fin / PLLN ) <= 2MHz
*         100MHz <= ((Fin / PLLN) * PLLF) <= 550MHz
*         30MHz <= ((Fin / PLLN) * PLLF / PLLP) <= 220MHz
*         16MHz <= ((Fin / PLLN) * PLLF / PLLQ) <= 220MHz
*@return: none
******************************************************************************/
HAL_StatusTypeDef SystemClock_Config(uint32_t sysclkSel, uint32_t pclk1Div, \
                                     uint32_t pclk2Div, uint32_t pclk3Div, uint32_t pclk4Div)
{
//    uint32_t pllf;
//    uint32_t plln;
//    uint32_t pllp;
//    uint32_t pllq;
//    uint32_t sysdiv;
    RCC_OscInitTypeDef      RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef      RCC_ClkInitStruct = {0};
    
    switch(sysclkSel)
    {
        case SYSCLK_220M_SRC_RCH:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_RCH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.RCH = ENABLE;
            RCC_OscInitStruct.RCHDiv16 = ENABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_RCH_DIV16;
            RCC_OscInitStruct.PLL1.PLLF = 330;
            RCC_OscInitStruct.PLL1.PLLN = 3;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
        
        case SYSCLK_200M_SRC_RCH:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_RCH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.RCH = ENABLE;
            RCC_OscInitStruct.RCHDiv16 = ENABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_RCH_DIV16;
            RCC_OscInitStruct.PLL1.PLLF = 300;
            RCC_OscInitStruct.PLL1.PLLN = 3;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
        
        case SYSCLK_180M_SRC_RCH:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_RCH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.RCH = ENABLE;
            RCC_OscInitStruct.RCHDiv16 = ENABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_RCH_DIV16;
            RCC_OscInitStruct.PLL1.PLLF = 270;
            RCC_OscInitStruct.PLL1.PLLN = 3;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
        
        case SYSCLK_160M_SRC_RCH:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_RCH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.RCH = ENABLE;
            RCC_OscInitStruct.RCHDiv16 = ENABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_RCH_DIV16;
            RCC_OscInitStruct.PLL1.PLLF = 240;
            RCC_OscInitStruct.PLL1.PLLN = 3;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
        
        case SYSCLK_100M_SRC_RCH:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_RCH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.RCH = ENABLE;
            RCC_OscInitStruct.RCHDiv16 = ENABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_RCH_DIV16;
            RCC_OscInitStruct.PLL1.PLLF = 300;
            RCC_OscInitStruct.PLL1.PLLN = 3;
            RCC_OscInitStruct.PLL1.PLLP = 4;
            RCC_OscInitStruct.PLL1.PLLQ = 4;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
        
        case SYSCLK_80M_SRC_RCH:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_RCH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.RCH = ENABLE;
            RCC_OscInitStruct.RCHDiv16 = ENABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_RCH_DIV16;
            RCC_OscInitStruct.PLL1.PLLF = 120;
            RCC_OscInitStruct.PLL1.PLLN = 3;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_64M_SRC_RCH:
        case SYSCLK_32M_SRC_RCH:
        case SYSCLK_16M_SRC_RCH:
        case SYSCLK_8M_SRC_RCH:
        case SYSCLK_4M_SRC_RCH:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_RCH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.RCH = ENABLE;
            RCC_OscInitStruct.RCHDiv16 = ENABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_RCH_DIV16;
            RCC_OscInitStruct.PLL1.PLLF = 96;
            RCC_OscInitStruct.PLL1.PLLN = 3;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1UL << (sysclkSel - SYSCLK_64M_SRC_RCH);
            break;
            
        case SYSCLK_220M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 330;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_210M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 315;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_200M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 300;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_190M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 285;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_180M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 270;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_170M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 255;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_160M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 240;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_150M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 225;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_140M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 210;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_130M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 195;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_120M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 180;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_110M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 165;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_100M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 300;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 4;
            RCC_OscInitStruct.PLL1.PLLQ = 4;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_90M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 270;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 4;
            RCC_OscInitStruct.PLL1.PLLQ = 4;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;

        case SYSCLK_80M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 120;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;

        case SYSCLK_70M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 105;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_64M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 96;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_60M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 90;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 2;
            RCC_OscInitStruct.PLL1.PLLQ = 2;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_50M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 150;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 4;
            RCC_OscInitStruct.PLL1.PLLQ = 4;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_48M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 144;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 4;
            RCC_OscInitStruct.PLL1.PLLQ = 4;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_40M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 240;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 8;
            RCC_OscInitStruct.PLL1.PLLQ = 8;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_30M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 180;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 8;
            RCC_OscInitStruct.PLL1.PLLQ = 8;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_24M_SRC_XTH_12M:
        case SYSCLK_12M_SRC_XTH_12M:
        case SYSCLK_8M_SRC_XTH_12M:
        case SYSCLK_4M_SRC_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH | RCC_OSC_TYPE_PLL1;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_OscInitStruct.PLL1.PLL = ENABLE;
            RCC_OscInitStruct.PLL1.Source = RCC_PLL_SOURCE_XTH;
            RCC_OscInitStruct.PLL1.PLLF = 144;
            RCC_OscInitStruct.PLL1.PLLN = 9;
            RCC_OscInitStruct.PLL1.PLLP = 4;
            RCC_OscInitStruct.PLL1.PLLQ = 4;
            RCC_OscInitStruct.PLL1.PLLPCLK = ENABLE;
            RCC_OscInitStruct.PLL1.PLLQCLK = DISABLE;
            RCC_OscInitStruct.PLL1.SSC = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_PLL1PCLK;
            if (sysclkSel == SYSCLK_24M_SRC_XTH_12M)
                RCC_ClkInitStruct.SYSCLKDiv0 = 2;
            if (sysclkSel == SYSCLK_12M_SRC_XTH_12M)
                RCC_ClkInitStruct.SYSCLKDiv0 = 4;
            if (sysclkSel == SYSCLK_8M_SRC_XTH_12M)
                RCC_ClkInitStruct.SYSCLKDiv0 = 6;
            if (sysclkSel == SYSCLK_4M_SRC_XTH_12M)
                RCC_ClkInitStruct.SYSCLKDiv0 = 12;
            break;
            
        case SYSCLK_64M_RCH:
        case SYSCLK_32M_RCH:
        case SYSCLK_16M_RCH:
        case SYSCLK_8M_RCH:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_RCH;
            RCC_OscInitStruct.RCH = ENABLE;
            RCC_OscInitStruct.RCHDiv16 = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_RCH;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1UL << (sysclkSel - SYSCLK_64M_RCH);
            break;
            
        case SYSCLK_4M_RCH:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_RCH;
            RCC_OscInitStruct.RCH = ENABLE;
            RCC_OscInitStruct.RCHDiv16 = ENABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_RCH;
            RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            break;
            
        case SYSCLK_12M_XTH_12M:
        case SYSCLK_6M_XTH_12M:
        case SYSCLK_4M_XTH_12M:
            RCC_OscInitStruct.OscType = RCC_OSC_TYPE_XTH;
            RCC_OscInitStruct.XTH = ENABLE;
            RCC_OscInitStruct.XTHBypass = DISABLE;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLK_SOURCE_XTH;
            if (sysclkSel == SYSCLK_12M_XTH_12M)
                RCC_ClkInitStruct.SYSCLKDiv0 = 1;
            else if (sysclkSel == SYSCLK_6M_XTH_12M)
                RCC_ClkInitStruct.SYSCLKDiv0 = 2;
            else if (sysclkSel == SYSCLK_4M_XTH_12M)
                RCC_ClkInitStruct.SYSCLKDiv0 = 3;
            break;
            
        default:
            return (HAL_ERROR);       
    }
    
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        return (HAL_ERROR);

    RCC_ClkInitStruct.ClockType = RCC_CLOCK_TYPE_SYSCLK | \
                                  RCC_CLOCK_TYPE_SYSDIV0 | RCC_CLOCK_TYPE_SYSDIV1 | \
                                  RCC_CLOCK_TYPE_PCLK1 | RCC_CLOCK_TYPE_PCLK2 | \
                                  RCC_CLOCK_TYPE_PCLK3 | RCC_CLOCK_TYPE_PCLK4;
    RCC_ClkInitStruct.SYSCLKDiv1 = 1;
    RCC_ClkInitStruct.PCLK1Div = pclk1Div;
    RCC_ClkInitStruct.PCLK2Div = pclk2Div;
    RCC_ClkInitStruct.PCLK3Div = pclk3Div;
    RCC_ClkInitStruct.PCLK4Div = pclk4Div;
    
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
        return (HAL_ERROR);
    return (HAL_OK);
}

#ifdef DATA_IN_ExtSRAM

__attribute__((weak)) void SystemInit_ExtMemCtl(void)
{
}

#endif /* (DATA_IN_ExtSRAM) || defined (DATA_IN_ExtSDRAM) */

