/******************************************************************************
*@file  : hal_rcc.c
*@brief : RCC HAL module driver.
******************************************************************************/
#include "hal.h"

#ifdef HAL_RCC_MODULE_ENABLED

__attribute__((weak)) void HAL_RCC_ReadyIRQHandler(void)
{
    // RCH clock ready
    if ((RCC->CIR & (RCC_CIR_RCHRDYIE | RCC_CIR_RCHRDYIF)) == (RCC_CIR_RCHRDYIE | RCC_CIR_RCHRDYIF))
    {
        RCC->CIR = (RCC->CIR & ~RCC_IT_CLEAR_FLAG_MASK) | RCC_CIR_RCHRDYIC;
        HAL_RCC_RCHReadyCallback();
    }
    
    // XTH clock ready
    if ((RCC->CIR & (RCC_CIR_XTHRDYIE | RCC_CIR_XTHRDYIF)) == (RCC_CIR_XTHRDYIE | RCC_CIR_XTHRDYIF))
    {
        RCC->CIR = (RCC->CIR & ~RCC_IT_CLEAR_FLAG_MASK) | RCC_CIR_XTHRDYIC;
        HAL_RCC_XTHReadyCallback();
    }

    // PLL1 clock ready
    if ((RCC->CIR & (RCC_CIR_PLL1LOCKIE | RCC_CIR_PLL1LOCKIF)) == (RCC_CIR_PLL1LOCKIE | RCC_CIR_PLL1LOCKIF))
    {
        RCC->CIR = (RCC->CIR & ~RCC_IT_CLEAR_FLAG_MASK) | RCC_CIR_PLL1LOCKIC;
        HAL_RCC_PLL1ReadyCallback();
    }
    
    // PLL2 clock ready
    if ((RCC->CIR & (RCC_CIR_PLL2LOCKIE | RCC_CIR_PLL2LOCKIF)) == (RCC_CIR_PLL2LOCKIE | RCC_CIR_PLL2LOCKIF))
    {
        RCC->CIR = (RCC->CIR & ~RCC_IT_CLEAR_FLAG_MASK) | RCC_CIR_PLL2LOCKIC;
        HAL_RCC_PLL2ReadyCallback();
    }
    
    // PLL3 clock ready
    if ((RCC->CIR & (RCC_CIR_PLL3LOCKIE | RCC_CIR_PLL3LOCKIF)) == (RCC_CIR_PLL3LOCKIE | RCC_CIR_PLL3LOCKIF))
    {
        RCC->CIR = (RCC->CIR & ~RCC_IT_CLEAR_FLAG_MASK) | RCC_CIR_PLL3LOCKIC;
        HAL_RCC_PLL3ReadyCallback();
    }
    
    // RCL clock ready
    if ((RCC->CIR & (RCC_CIR_RCLRDYIE | RCC_CIR_RCLRDYIF)) == (RCC_CIR_RCLRDYIE | RCC_CIR_RCLRDYIF))
    {
        RCC->CIR = (RCC->CIR & ~RCC_IT_CLEAR_FLAG_MASK) | RCC_CIR_RCLRDYIC;
        HAL_RCC_RCLReadyCallback();
    }
    
    // XTL clock ready
    if ((RCC->CIR & (RCC_CIR_XTLRDYIE | RCC_CIR_XTLRDYIF)) == (RCC_CIR_XTLRDYIE | RCC_CIR_XTLRDYIF))
    {
        RCC->CIR = (RCC->CIR & ~RCC_IT_CLEAR_FLAG_MASK) | RCC_CIR_XTLRDYIC;
        HAL_RCC_XTLReadyCallback();
    }
}

__attribute__((weak)) void HAL_RCC_XTHStopIRQHandler(void)
{
    // XTH stop
    if ((RCC->CIR & (RCC_CIR_XTHSDIE | RCC_CIR_XTHSDF)) == (RCC_CIR_XTHSDIE | RCC_CIR_XTHSDF))
    {
        RCC->CIR = (RCC->CIR & ~RCC_IT_CLEAR_FLAG_MASK) | RCC_CIR_XTHSDIC;
        HAL_RCC_XTHStopCallback();
    }
}

__attribute__((weak)) void HAL_RCC_XTLStopIRQHandler(void)
{
    // XTL stop
    if ((RCC->CIR & (RCC_CIR_XTLSDIE | RCC_CIR_XTLSDF)) == (RCC_CIR_XTLSDIE | RCC_CIR_XTLSDF))
    {
        RCC->STDBYCTRL &= ~RCC_STDBYCTRL_XTLSDEN;
        RCC->STDBYCTRL &= ~RCC_STDBYCTRL_XTLEN;
        RCC->CIR = (RCC->CIR & ~RCC_IT_CLEAR_FLAG_MASK) | RCC_CIR_XTLSDIC;
        HAL_RCC_XTLStopCallback();
    }
}

/******************************************************************************
*@brief : RCH clock stable interrupt callback.
*@param : None
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_RCC_RCHReadyCallback(void)
{
}

/******************************************************************************
*@brief : RCL clock stable interrupt callback.
*@param : None
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_RCC_RCLReadyCallback(void)
{
}

/******************************************************************************
*@brief : XTH clock stable interrupt callback.
*@param : None
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_RCC_XTHReadyCallback(void)
{
}

/******************************************************************************
*@brief : XTL clock stable interrupt callback.
*@param : None
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_RCC_XTLReadyCallback(void)
{
}

/******************************************************************************
*@brief : PLL1 clock stable interrupt callback.
*@param : None
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_RCC_PLL1ReadyCallback(void)
{
}

/******************************************************************************
*@brief : PLL2 clock stable interrupt callback.
*@param : None
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_RCC_PLL2ReadyCallback(void)
{
}

/******************************************************************************
*@brief : PLL3 clock stable interrupt callback.
*@param : None
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_RCC_PLL3ReadyCallback(void)
{
}

/******************************************************************************
*@brief : PLL3 clock stable interrupt callback.
*@param : None
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_RCC_XTHStopCallback(void)
{
}

/******************************************************************************
*@brief : PLL3 clock stable interrupt callback.
*@param : None
*@return: None
******************************************************************************/
__attribute__((weak)) void HAL_RCC_XTLStopCallback(void)
{
}

/******************************************************************************
*@brief : Initializes the RCC Oscillators according to the specified parameters
*         in the RCC_OscInitTypeDef.
*@param : RCC_OscInit: pointer to an RCC_OscInitTypeDef structure that contains 
*         the configuration information for the RCC Oscillators.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInit)
{
    /* Check the parameters */
    assert_param(IS_RCC_OSC_TYPE(RCC_OscInit->OscType));
    
    /*------------------------------- RCH Configuration ------------------------*/
    if (RCC_OscInit->OscType & RCC_OSC_TYPE_RCH)
    {
        if (HAL_RCC_RCHConfig(RCC_OscInit->RCH, RCC_OscInit->RCHDiv16) != HAL_OK)
            return HAL_ERROR;
    }
    
    /*------------------------------- RCL Configuration ------------------------*/
    if (RCC_OscInit->OscType & RCC_OSC_TYPE_RCL)
    {
        if (HAL_RCC_RCLConfig(RCC_OscInit->RCL) != HAL_OK)
            return HAL_ERROR;
    }
    
    /*------------------------------- XTH Configuration ------------------------*/
    if (RCC_OscInit->OscType & RCC_OSC_TYPE_XTH)
    {
        if (HAL_RCC_XTHConfig(RCC_OscInit->XTH, RCC_OscInit->XTHBypass) != HAL_OK)
            return HAL_ERROR;
    }
    
    /*------------------------------- XTL Configuration ------------------------*/
    if (RCC_OscInit->OscType & RCC_OSC_TYPE_XTL)
    {
        if (HAL_RCC_XTLConfig(RCC_OscInit->XTL, RCC_OscInit->XTLBypass) != HAL_OK)
            return HAL_ERROR;
    }
    
    /*------------------------------- PLL1 Configuration ------------------------*/
    if (RCC_OscInit->OscType & RCC_OSC_TYPE_PLL1)
    {
        if (RCC_OscInit->PLL1.SSC == DISABLE)
        {
            if (HAL_RCC_PLL1Config(RCC_OscInit->PLL1.PLL, RCC_OscInit->PLL1.Source, RCC_OscInit->PLL1.PLLN, \
                                   RCC_OscInit->PLL1.PLLF, RCC_OscInit->PLL1.PLLP, RCC_OscInit->PLL1.PLLQ) != HAL_OK)
                return HAL_ERROR;
        }
        else
        {
            if (HAL_RCC_PLL1SSCConfig(RCC_OscInit->PLL1.PLL, RCC_OscInit->PLL1.Source, RCC_OscInit->PLL1.PLLN, \
                                      RCC_OscInit->PLL1.PLLF, RCC_OscInit->PLL1.PLLP, RCC_OscInit->PLL1.PLLQ, \
                                      RCC_OscInit->PLL1.SSC, RCC_OscInit->PLL1.SSCMode, RCC_OscInit->PLL1.SSCSpectrum, \
                                      RCC_OscInit->PLL1.SSCStep) != HAL_OK)
                return HAL_ERROR;
        }
        
        if (HAL_RCC_PLL1PCLKConfig(RCC_OscInit->PLL1.PLLPCLK) != HAL_OK)
            return HAL_ERROR;
        
        if (HAL_RCC_PLL1QCLKConfig(RCC_OscInit->PLL1.PLLQCLK) != HAL_OK)
            return HAL_ERROR;
    }
    
    /*------------------------------- PLL2 Configuration ------------------------*/
    if (RCC_OscInit->OscType & RCC_OSC_TYPE_PLL2)
    {
        if (RCC_OscInit->PLL1.SSC == DISABLE)
        {
            if (HAL_RCC_PLL2Config(RCC_OscInit->PLL2.PLL, RCC_OscInit->PLL2.Source, RCC_OscInit->PLL2.PLLN, \
                                   RCC_OscInit->PLL2.PLLF, RCC_OscInit->PLL2.PLLP, RCC_OscInit->PLL2.PLLQ) != HAL_OK)
                return HAL_ERROR;
        }
        else
        {
            if (HAL_RCC_PLL2SSCConfig(RCC_OscInit->PLL2.PLL, RCC_OscInit->PLL2.Source, RCC_OscInit->PLL2.PLLN, \
                                      RCC_OscInit->PLL2.PLLF, RCC_OscInit->PLL2.PLLP, RCC_OscInit->PLL2.PLLQ, \
                                      RCC_OscInit->PLL1.SSC, RCC_OscInit->PLL1.SSCMode, RCC_OscInit->PLL1.SSCSpectrum, \
                                      RCC_OscInit->PLL1.SSCStep) != HAL_OK)
                return HAL_ERROR;
        }
        
        if (HAL_RCC_PLL2PCLKConfig(RCC_OscInit->PLL2.PLLPCLK) != HAL_OK)
            return HAL_ERROR;
        
        if (HAL_RCC_PLL2QCLKConfig(RCC_OscInit->PLL2.PLLQCLK) != HAL_OK)
            return HAL_ERROR;
    }
    
    /*------------------------------- PLL3 Configuration ------------------------*/
    if (RCC_OscInit->OscType & RCC_OSC_TYPE_PLL3)
    {
        if (HAL_RCC_PLL3Config(RCC_OscInit->PLL3.PLL, RCC_OscInit->PLL3.Source, RCC_OscInit->PLL3.PLLN, \
                               RCC_OscInit->PLL3.PLLF, RCC_OscInit->PLL3.PLLP, RCC_OscInit->PLL3.PLLQ) != HAL_OK)
            return HAL_ERROR;
        
        if (HAL_RCC_PLL3PCLKConfig(RCC_OscInit->PLL3.PLLPCLK) != HAL_OK)
            return HAL_ERROR;
        
        if (HAL_RCC_PLL3QCLKConfig(RCC_OscInit->PLL3.PLLQCLK) != HAL_OK)
            return HAL_ERROR;
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Initializes the RCC Oscillators according to the specified parameters
*         in the RCC_OscInitTypeDef.
*@param : RCC_OscInit: pointer to an RCC_OscInitTypeDef structure that contains 
*         the configuration information for the RCC Oscillators.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_RCHConfig(FunctionalState RCH, FunctionalState Div16)
{
    uint32_t temp;
    uint32_t timeout;
    
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(RCH));
    
    if (RCH == DISABLE)
    {
        if ((RCC->CCR1 & RCC_CCR1_SYSCLKSEL_1) == 0)
            return (HAL_ERROR);
        
        if ((RCC->PLL1CR & (RCC_PLL1CR_PLL1SLEEP | RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1SRCSEL)) == RCC_PLL1CR_PLL1EN)
            return (HAL_ERROR);
        
        if ((RCC->PLL2CR & (RCC_PLL2CR_PLL2SLEEP | RCC_PLL2CR_PLL2EN | RCC_PLL2CR_PLL2SRCSEL)) == RCC_PLL2CR_PLL2EN)
            return (HAL_ERROR);
        
        if ((RCC->PLL3CR & (RCC_PLL3CR_PLL3SLEEP | RCC_PLL3CR_PLL3EN | RCC_PLL3CR_PLL3SRCSEL)) == RCC_PLL3CR_PLL3EN)
            return (HAL_ERROR);
        
        /* disable RCH */
        RCC->RCHCR &= ~(RCC_RCHCR_RCHEN | RCC_RCHCR_RCHDIV);
        HAL_SimpleDelay(2);
        timeout = RCC_RCHP_UNREADY_TIMEOUT;
        while (RCC->RCHCR & RCC_RCHCR_RCHRDY)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
    }
    else
    {
        /* Check the parameters */
        assert_param(IS_FUNCTIONAL_STATE(Div16));
        
        if (Div16 == DISABLE)
        {
            if ((RCC->PLL1CR & (RCC_PLL1CR_PLL1SLEEP | RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1SRCSEL)) == RCC_PLL1CR_PLL1EN)
                return (HAL_ERROR);
            
            if ((RCC->PLL2CR & (RCC_PLL2CR_PLL2SLEEP | RCC_PLL2CR_PLL2EN | RCC_PLL2CR_PLL2SRCSEL)) == RCC_PLL2CR_PLL2EN)
                return (HAL_ERROR);
            
            if ((RCC->PLL3CR & (RCC_PLL3CR_PLL3SLEEP | RCC_PLL3CR_PLL3EN | RCC_PLL3CR_PLL3SRCSEL)) == RCC_PLL3CR_PLL3EN)
                return (HAL_ERROR);
            
            RCC->RCHCR &= ~RCC_RCHCR_RCHDIV;
        }

        RCC->RCHCR |= RCC_RCHCR_RCHEN;
        
        HAL_SimpleDelay(5);
        
        timeout = RCC_RCH_READY_TIMEOUT;
        while ((RCC->RCHCR & RCC_RCHCR_RCHRDY) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
        if (Div16)
            RCC->RCHCR |= RCC_RCHCR_RCHDIV;
        
        if ((RCC->CCR1 & RCC_CCR1_SYSCLKSEL) == RCC_SYSCLK_SOURCE_RCH)
        {
            temp = SystemCoreClock;
            SystemCoreClock = HAL_RCC_GetSysCoreClockFreq();
            if (temp != SystemCoreClock)
            {
                HAL_InitTick(g_systickHandle.intPrio,g_systickHandle.msPeriod);
            }
        }
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Initializes the RCC Oscillators according to the specified parameters
*         in the RCC_OscInitTypeDef.
*@param : RCC_OscInit: pointer to an RCC_OscInitTypeDef structure that contains 
*         the configuration information for the RCC Oscillators.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_RCLConfig(FunctionalState RCL)
{
    uint32_t timeout;
    
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(RCL));
    
    if (RCL == DISABLE)
    {
        if ((RCC->STDBYCTRL & (RCC_STDBYCTRL_RTCEN | RCC_STDBYCTRL_RTCSEL)) == RCC_STDBYCTRL_RTCEN)
            return (HAL_ERROR);
        
        /* disable RCL */
        RCC->STDBYCTRL = (RCC->STDBYCTRL & ~(RCC_STDBYCTRL_RCLDIS | RCC_STDBYCTRL_RCLEN)) | \
                          (0x0AUL << RCC_STDBYCTRL_RCLDIS_Pos);

        HAL_SimpleDelay(2);
        timeout = RCC_RCL_UNREADY_TIMEOUT;
        while (RCC->STDBYCTRL & RCC_STDBYCTRL_RCLRDY)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
    }
    else
    {
        /* enable RCL */
        RCC->STDBYCTRL |= RCC_STDBYCTRL_RCLEN;
        HAL_SimpleDelay(5);
        /* Wait till RCL is ready */
        timeout = RCC_RCL_READY_TIMEOUT;
        while (!(RCC->STDBYCTRL & RCC_STDBYCTRL_RCLRDY))
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Initializes the RCC Oscillators according to the specified parameters
*         in the RCC_OscInitTypeDef.
*@param : RCC_OscInit: pointer to an RCC_OscInitTypeDef structure that contains 
*         the configuration information for the RCC Oscillators.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_XTHConfig(FunctionalState XTH, FunctionalState Bypass)
{
//    volatile uint32_t temp;
    uint32_t timeout;
    
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(XTH));
    
    if (DISABLE == XTH)
    {
        if ((RCC->CCR1 & RCC_CCR1_SYSCLKSEL) == RCC_CCR1_SYSCLKSEL_1)
            return (HAL_ERROR);
        
        if ((RCC->PLL1CR & (RCC_PLL1CR_PLL1SLEEP | RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1SRCSEL)) == (RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1SRCSEL))
            return (HAL_ERROR);
        
        if ((RCC->PLL2CR & (RCC_PLL2CR_PLL2SLEEP | RCC_PLL2CR_PLL2EN | RCC_PLL2CR_PLL2SRCSEL)) == (RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1SRCSEL))
            return (HAL_ERROR);
        
        if ((RCC->PLL3CR & (RCC_PLL3CR_PLL3SLEEP | RCC_PLL3CR_PLL3EN | RCC_PLL3CR_PLL3SRCSEL)) == (RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1SRCSEL))
            return (HAL_ERROR);
        
        /* disable XTH */
        RCC->XTHCR &= ~RCC_XTHCR_XTHEN;
        HAL_SimpleDelay(2);
        timeout = RCC_XTH_UNREADY_TIMEOUT;
        while (RCC->XTHCR & RCC_XTHCR_XTHRDY)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
    }
    else
    {
        /* Check the parameters */
        assert_param(IS_FUNCTIONAL_STATE(Bypass));
        
        if ((RCC->CCR1 & RCC_CCR1_SYSCLKSEL) == RCC_CCR1_SYSCLKSEL_1)
        {
            if (Bypass)
            {
                if ((RCC->XTHCR & RCC_XTHCR_XTHBYP) == 0)
                    return (HAL_ERROR);
            }
            else
            {
                if (RCC->XTHCR & RCC_XTHCR_XTHBYP)
                    return (HAL_ERROR);
            }
        }
        
        if (Bypass)
            RCC->XTHCR |= RCC_XTHCR_XTHRDYTIME | RCC_XTHCR_XTHBYP | RCC_XTHCR_XTHEN;
        else
            RCC->XTHCR = (RCC->XTHCR & ~RCC_XTHCR_XTHBYP) | RCC_XTHCR_XTHRDYTIME | RCC_XTHCR_XTHEN;

        HAL_SimpleDelay(5);
        timeout = RCC_XTH_READY_TIMEOUT;
        while (!(RCC->XTHCR & RCC_XTHCR_XTHRDY))
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Initializes the RCC Oscillators according to the specified parameters
*         in the RCC_OscInitTypeDef.
*@param : RCC_OscInit: pointer to an RCC_OscInitTypeDef structure that contains 
*         the configuration information for the RCC Oscillators.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_XTLConfig(FunctionalState XTL, FunctionalState Bypass)
{
    uint32_t timeout;
    
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(XTL));
    
    if (DISABLE == XTL)
    {
        if ((RCC->STDBYCTRL & (RCC_STDBYCTRL_RTCEN | RCC_STDBYCTRL_RTCSEL)) == (RCC_STDBYCTRL_RTCEN | RCC_STDBYCTRL_RTCSEL))
            return (HAL_ERROR);
        
        /* disable XTL */
        RCC->STDBYCTRL &= ~RCC_STDBYCTRL_XTLEN;
        HAL_SimpleDelay(5);
        timeout = RCC_XTL_UNREADY_TIMEOUT;
        while (RCC->STDBYCTRL & RCC_STDBYCTRL_XTLRDY)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
    }
    else
    {
        /* Check the parameters */
        assert_param(IS_FUNCTIONAL_STATE(Bypass));
        
        /* XTL oscillator bypass configuration */
        if (Bypass)
        {
            RCC->STDBYCTRL = (RCC->STDBYCTRL & ~RCC_STDBYCTRL_XTLDRV) | RCC_STDBYCTRL_XTLBYP | \
                              RCC_STDBYCTRL_XTLDRV_1 | RCC_STDBYCTRL_XTLDRV_0 | RCC_STDBYCTRL_XTLEN;
        }
        else
        {
            RCC->STDBYCTRL = (RCC->STDBYCTRL & ~(RCC_STDBYCTRL_XTLBYP | RCC_STDBYCTRL_XTLDRV)) | \
                              RCC_STDBYCTRL_XTLDRV_1 | RCC_STDBYCTRL_XTLDRV_0 | RCC_STDBYCTRL_XTLEN;
        }
        HAL_SimpleDelay(5);
        timeout = RCC_XTL_READY_TIMEOUT;
        while ((RCC->STDBYCTRL & RCC_STDBYCTRL_XTLRDY) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
        RCC->STDBYCTRL |= RCC_STDBYCTRL_XTLDRV_2;
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Initializes the RCC Oscillators according to the specified parameters
*         in the RCC_OscInitTypeDef.
*@param : RCC_OscInit: pointer to an RCC_OscInitTypeDef structure that contains 
*         the configuration information for the RCC Oscillators.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_PLL1Config(FunctionalState PLL1, uint32_t ClockSource, \
                                     uint32_t PLLN, uint32_t PLLF, uint32_t PLLP, uint32_t PLLQ)
{
    uint32_t lock;
    uint32_t timeout;
    #ifdef USE_FULL_ASSERT
    double freq;
    #endif
    
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(PLL1));
    
    /* check whether the current configured clock is the system clock */
    if ((RCC->CCR1 & RCC_CCR1_SYSCLKSEL) == (RCC_CCR1_SYSCLKSEL_0 | RCC_CCR1_SYSCLKSEL_1))
        return (HAL_ERROR);
    
    if (PLL1 == DISABLE)
    {
        /* disable PLL1 */
        RCC->PLL1CR &= ~RCC_PLL1CR_PLL1EN;
        /* enter sleep mode */
        RCC->PLL1CR |= RCC_PLL1CR_PLL1SLEEP;
        HAL_SimpleDelay(15);
    }
    else
    {
        /* Check the parameters */
        assert_param(IS_RCC_PLL_CLOCK_SOURCE(ClockSource));
        assert_param(IS_RCC_PLL1_PLLN(PLLN));
        assert_param(IS_RCC_PLL1_PLLF(PLLF));
        assert_param(IS_RCC_PLL1_PLLP(PLLP));
        assert_param(IS_RCC_PLL1_PLLQ(PLLQ));
        
        if (ClockSource == RCC_PLL_SOURCE_RCH_DIV16)
        {
            if ((RCC->RCHCR & (RCC_RCHCR_RCHDIV | RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY)) != \
                              (RCC_RCHCR_RCHDIV | RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY))
                return (HAL_ERROR);
            lock = RCC_PLL1CR_PLL1FREERUN;
            #ifdef USE_FULL_ASSERT
            freq = (double)4000000;
            #endif
        }
        else
        {
            if ((RCC->XTHCR & (RCC_XTHCR_XTHRDY | RCC_XTHCR_XTHEN)) != (RCC_XTHCR_XTHRDY | RCC_XTHCR_XTHEN))
                return (HAL_ERROR);
            lock = RCC_PLL1CR_PLL1LOCK;
            #ifdef USE_FULL_ASSERT
            freq = (double)XTH_VALUE;
            #endif
        }

        // FCLK_VCO=FCLKIN*F/N; FCLK_P=FCLK_VCO /P; FCLK_Q=FCLK_VCO /Q

        #ifdef USE_FULL_ASSERT
        assert_param((freq >= 1000000) && (freq <= 132000000));
        freq = freq / PLLN;
        assert_param((freq >= 1000000) && (freq <= 2000000));
        freq = freq * PLLF;
        assert_param((freq >= 100000000) && (freq <= 550000000));
        assert_param(((freq / PLLP) >= 30000000) && ((freq / PLLP) <= 220000000));
        assert_param(((freq / PLLQ) >= 16000000) && ((freq / PLLQ) <= 220000000));
        #endif
        
        RCC->PLL1CR |= RCC_PLL1CR_PLL1LOCKSEL;
        RCC->PLL1CR &= ~(RCC_PLL1CR_PLL1PCLKEN | RCC_PLL1CR_PLL1QCLKEN);
        if (ClockSource == RCC_PLL_SOURCE_RCH_DIV16)
            RCC->PLL1CR &= ~RCC_PLL1CR_PLL1SRCSEL;
        else
            RCC->PLL1CR |= RCC_PLL1CR_PLL1SRCSEL;
        /* lock delay 400us */
        RCC->PLL1CR = (RCC->PLL1CR & ~RCC_PLL1CR_PLL1LOCKDLY) | \
                      ((((uint32_t)(((double)400 * SystemCoreClock) / ((double)512 * 1000000))) \
                      << RCC_PLL1CR_PLL1LOCKDLY_Pos) & RCC_PLL1CR_PLL1LOCKDLY);
        /* enable PLL1 */
        RCC->PLL1CR |= RCC_PLL1CR_PLL1EN;
        RCC->PLL1SCR = 0;
        /* exit sleep mode */
        RCC->PLL1CR &= ~RCC_PLL1CR_PLL1SLEEP;
        
        HAL_SimpleDelay(15);
        /* Wait till PLL is ready */
        timeout = RCC_PLL1_READY_TIMEOUT;
        while ((RCC->PLL1CR & RCC_PLL1CR_PLL1FREERUN) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
        RCC->PLL1CFR = (((PLLQ) << RCC_PLL1CFR_PLL1Q_Pos) & RCC_PLL1CFR_PLL1Q) | \
                       (((((PLLP) >> 1) - 1) << RCC_PLL1CFR_PLL1P_Pos) & RCC_PLL1CFR_PLL1P) | \
                       (((PLLN) << RCC_PLL1CFR_PLL1N_Pos) & RCC_PLL1CFR_PLL1N) | \
                       (((PLLF) << RCC_PLL1CFR_PLL1F_Pos) & RCC_PLL1CFR_PLL1F);
        
        
        if (ClockSource == RCC_PLL_SOURCE_XTH)
        {
            RCC->PLL1CR &= ~RCC_PLL1CR_PLL1LOCKSEL;
        }
        /* update pll */
        RCC->PLL1CR |= RCC_PLL1CR_PLL1UPDATEEN;
        HAL_SimpleDelay(15);
        /* Wait till PLL is ready */
        timeout = RCC_PLL1_READY_TIMEOUT;
        while ((RCC->PLL1CR & lock) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
        
        
        RCC->PLL1CR |= RCC_PLL1CR_PLL1PCLKEN;
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Initializes the RCC Oscillators according to the specified parameters
*         in the RCC_OscInitTypeDef.
*@param : RCC_OscInit: pointer to an RCC_OscInitTypeDef structure that contains 
*         the configuration information for the RCC Oscillators.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_PLL1SSCConfig(FunctionalState PLL1, uint32_t ClockSource, \
                            uint32_t PLLN, uint32_t PLLF, uint32_t PLLP, uint32_t PLLQ, \
                            FunctionalState SSC, uint32_t Mode, uint32_t Spectrum, uint32_t Step)
{
    uint32_t lock;
    uint32_t timeout;
    #ifdef USE_FULL_ASSERT
    double freq;
    #endif
    
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(PLL1));
    
    /* check whether the current configured clock is the system clock */
    if ((RCC->CCR1 & RCC_CCR1_SYSCLKSEL) == (RCC_CCR1_SYSCLKSEL_0 | RCC_CCR1_SYSCLKSEL_1))
        return (HAL_ERROR);
    
    if (PLL1 == DISABLE)
    {
        /* disable PLL1 */
        RCC->PLL1CR &= ~RCC_PLL1CR_PLL1EN;
        RCC->PLL1SCR = 0;
        /* enter sleep mode */
        RCC->PLL1CR |= RCC_PLL1CR_PLL1SLEEP;
        HAL_SimpleDelay(15);
    }
    else
    {
        /* Check the parameters */
        assert_param(IS_RCC_PLL_CLOCK_SOURCE(ClockSource));
        assert_param(IS_RCC_PLL1_PLLN(PLLN));
        assert_param(IS_RCC_PLL1_PLLF(PLLF));
        assert_param(IS_RCC_PLL1_PLLP(PLLP));
        assert_param(IS_RCC_PLL1_PLLQ(PLLQ));
        
        if (ClockSource == RCC_PLL_SOURCE_RCH_DIV16)
        {
            if ((RCC->RCHCR & (RCC_RCHCR_RCHDIV | RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY)) != \
                              (RCC_RCHCR_RCHDIV | RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY))
                return (HAL_ERROR);
            lock = RCC_PLL1CR_PLL1FREERUN;
            #ifdef USE_FULL_ASSERT
            freq = (double)4000000;
            #endif
        }
        else
        {
            if ((RCC->XTHCR & (RCC_XTHCR_XTHRDY | RCC_XTHCR_XTHEN)) != (RCC_XTHCR_XTHRDY | RCC_XTHCR_XTHEN))
                return (HAL_ERROR);
            lock = RCC_PLL1CR_PLL1LOCK;
            #ifdef USE_FULL_ASSERT
            freq = (double)XTH_VALUE;
            #endif
        }

        // FCLK_VCO=FCLKIN*F/N; FCLK_P=FCLK_VCO /P; FCLK_Q=FCLK_VCO /Q

        #ifdef USE_FULL_ASSERT
        assert_param((freq >= 1000000) && (freq <= 132000000));
        freq = freq / PLLN;
        assert_param((freq >= 1000000) && (freq <= 2000000));
        freq = freq * PLLF;
        assert_param((freq >= 100000000) && (freq <= 550000000));
        assert_param(((freq / PLLP) >= 30000000) && ((freq / PLLP) <= 222000000));
        assert_param(((freq / PLLQ) >= 16000000) && ((freq / PLLQ) <= 222000000));
        #endif
        
        RCC->PLL1CR |= RCC_PLL1CR_PLL1LOCKSEL;
        RCC->PLL1CR &= ~(RCC_PLL1CR_PLL1PCLKEN | RCC_PLL1CR_PLL1QCLKEN);
        if (ClockSource == RCC_PLL_SOURCE_RCH_DIV16)
            RCC->PLL1CR &= ~RCC_PLL1CR_PLL1SRCSEL;
        else
            RCC->PLL1CR |= RCC_PLL1CR_PLL1SRCSEL;
        /* lock delay 400us */
        RCC->PLL1CR = (RCC->PLL1CR & ~RCC_PLL1CR_PLL1LOCKDLY) | \
                      ((((uint32_t)(((double)400 * SystemCoreClock) / ((double)512 * 1000000))) \
                      << RCC_PLL1CR_PLL1LOCKDLY_Pos) & RCC_PLL1CR_PLL1LOCKDLY);
        /* enable PLL1 */
        RCC->PLL1CR |= RCC_PLL1CR_PLL1EN;
    
        if (SSC == DISABLE)
        {
            RCC->PLL1SCR = 0;
        }
        else
        {
            RCC->PLL1SCR = ((Step << RCC_PLL1SCR_PLL1SSCSTP_Pos) & RCC_PLL1SCR_PLL1SSCSTP) | \
                            ((Spectrum << RCC_PLL1SCR_PLL1SSCPER_Pos) & RCC_PLL1SCR_PLL1SSCPER) | \
                            Mode | RCC_PLL1SCR_PLL1SSCEN;
        }
        
        /* exit sleep mode */
        RCC->PLL1CR &= ~RCC_PLL1CR_PLL1SLEEP;
        
        HAL_SimpleDelay(15);
        /* Wait till PLL is ready */
        timeout = RCC_PLL1_READY_TIMEOUT;
        while ((RCC->PLL1CR & RCC_PLL1CR_PLL1FREERUN) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
        RCC->PLL1CFR = (((PLLQ) << RCC_PLL1CFR_PLL1Q_Pos) & RCC_PLL1CFR_PLL1Q) | \
                       (((((PLLP) >> 1) - 1) << RCC_PLL1CFR_PLL1P_Pos) & RCC_PLL1CFR_PLL1P) | \
                       (((PLLN) << RCC_PLL1CFR_PLL1N_Pos) & RCC_PLL1CFR_PLL1N) | \
                       (((PLLF) << RCC_PLL1CFR_PLL1F_Pos) & RCC_PLL1CFR_PLL1F);
        
        if (ClockSource == RCC_PLL_SOURCE_XTH)
        {
            RCC->PLL1CR &= ~RCC_PLL1CR_PLL1LOCKSEL;
        }
        /* update pll */
        RCC->PLL1CR |= RCC_PLL1CR_PLL1UPDATEEN;
        HAL_SimpleDelay(15);
        /* Wait till PLL is ready */
        timeout = RCC_PLL1_READY_TIMEOUT;
        while ((RCC->PLL1CR & lock) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
    }
    
    return (HAL_OK);
}

HAL_StatusTypeDef HAL_RCC_PLL1PCLKConfig(FunctionalState PLL1PCLK)
{
    /* check whether the current configured clock is the system clock */
    if ((RCC->CCR1 & RCC_CCR1_SYSCLKSEL) == (RCC_CCR1_SYSCLKSEL_1 | RCC_CCR1_SYSCLKSEL_0))
        return (HAL_ERROR);
    
    if (PLL1PCLK == DISABLE)
        RCC->PLL1CR &= ~RCC_PLL1CR_PLL1PCLKEN;
    else
        RCC->PLL1CR |= RCC_PLL1CR_PLL1PCLKEN;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RCC_PLL1QCLKConfig(FunctionalState PLL1QCLK)
{
    if (PLL1QCLK == DISABLE)
        RCC->PLL1CR &= ~RCC_PLL1CR_PLL1QCLKEN;
    else
        RCC->PLL1CR |= RCC_PLL1CR_PLL1QCLKEN;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Initializes the RCC Oscillators according to the specified parameters
*         in the RCC_OscInitTypeDef.
*@param : RCC_OscInit: pointer to an RCC_OscInitTypeDef structure that contains 
*         the configuration information for the RCC Oscillators.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_PLL2Config(FunctionalState PLL2, uint32_t ClockSource, \
                            uint32_t PLLN, uint32_t PLLF, uint32_t PLLP, uint32_t PLLQ)
{
    uint32_t lock;
    uint32_t timeout;
    #ifdef USE_FULL_ASSERT
    double freq;
    #endif
    
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(PLL2));
    
    if (PLL2 == DISABLE)
    {
        /* disable PLL2 */
        RCC->PLL2CR &= ~RCC_PLL2CR_PLL2EN;
        /* enter sleep mode */
        RCC->PLL2CR |= RCC_PLL2CR_PLL2SLEEP;
        HAL_SimpleDelay(15);
    }
    else
    {
        /* Check the parameters */
        assert_param(IS_RCC_PLL_CLOCK_SOURCE(ClockSource));
        assert_param(IS_RCC_PLL2_PLLN(PLLN));
        assert_param(IS_RCC_PLL2_PLLF(PLLF));
        assert_param(IS_RCC_PLL2_PLLP(PLLP));
        assert_param(IS_RCC_PLL2_PLLQ(PLLQ));
        
        if (ClockSource == RCC_PLL_SOURCE_RCH_DIV16)
        {
            if ((RCC->RCHCR & (RCC_RCHCR_RCHDIV | RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY)) != \
                              (RCC_RCHCR_RCHDIV | RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY))
                return (HAL_ERROR);
            lock = RCC_PLL2CR_PLL2FREERUN;
            #ifdef USE_FULL_ASSERT
            freq = (double)4000000;
            #endif
        }
        else
        {
            if ((RCC_XTHCR_XTHRDY | RCC_XTHCR_XTHEN) != (RCC->XTHCR & (RCC_XTHCR_XTHRDY | RCC_XTHCR_XTHEN)))
                return (HAL_ERROR);
            lock = RCC_PLL2CR_PLL2LOCK;
            #ifdef USE_FULL_ASSERT
            freq = (double)XTH_VALUE;
            #endif
        }
        
        // FCLK_VCO=FCLKIN*F/N; FCLK_P=FCLK_VCO /P; FCLK_Q=FCLK_VCO /Q
        #ifdef USE_FULL_ASSERT
        assert_param((freq >= 1000000) && (freq <= 132000000));
        freq = freq / PLLN;
        assert_param((freq >= 1000000) && (freq <= 2000000));
        freq = freq * PLLF;
        assert_param((freq >= 100000000) && (freq <= 550000000));
        assert_param(((freq / PLLP) >= 30000000) && ((freq / PLLP) <= 220000000));
        assert_param(((freq / PLLQ) >= 16000000) && ((freq / PLLQ) <= 220000000));
        #endif
        
        RCC->PLL2CR |= RCC_PLL2CR_PLL2LOCKSEL;
        RCC->PLL2CR &= ~(RCC_PLL2CR_PLL2PCLKEN | RCC_PLL2CR_PLL2QCLKEN);
        if (ClockSource == RCC_PLL_SOURCE_RCH_DIV16)
            RCC->PLL2CR &= ~RCC_PLL2CR_PLL2SRCSEL;
        else
            RCC->PLL2CR |= RCC_PLL2CR_PLL2SRCSEL;
        /* lock delay 400us */
        RCC->PLL2CR = (RCC->PLL2CR & ~RCC_PLL2CR_PLL2LOCKDLY) | \
                      ((((uint32_t)(((double)400 * SystemCoreClock) / ((double)512 * 1000000))) \
                      << RCC_PLL2CR_PLL2LOCKDLY_Pos) & RCC_PLL2CR_PLL2LOCKDLY);
        /* enable PLL2 */
        RCC->PLL2CR |= RCC_PLL2CR_PLL2EN;
        RCC->PLL2SCR = 0;
        /* exit sleep mode */
        RCC->PLL2CR &= ~RCC_PLL2CR_PLL2SLEEP;
        HAL_SimpleDelay(15);
        /* Wait till PLL is ready */
        timeout = RCC_PLL2_READY_TIMEOUT;
        while ((RCC->PLL2CR & RCC_PLL2CR_PLL2FREERUN) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
        
        RCC->PLL2CFR = (((PLLQ) << RCC_PLL2CFR_PLL2Q_Pos) & RCC_PLL2CFR_PLL2Q) | \
                       (((((PLLP) >> 1) - 1) << RCC_PLL2CFR_PLL2P_Pos) & RCC_PLL2CFR_PLL2P) | \
                       (((PLLN) << RCC_PLL2CFR_PLL2N_Pos) & RCC_PLL2CFR_PLL2N) | \
                       (((PLLF) << RCC_PLL2CFR_PLL2F_Pos) & RCC_PLL2CFR_PLL2F);
        
        if (ClockSource == RCC_PLL_SOURCE_XTH)
        {
            RCC->PLL2CR &= ~RCC_PLL2CR_PLL2LOCKSEL;
        }
        /* update pll */
        RCC->PLL2CR |= RCC_PLL2CR_PLL2UPDATEEN;
        HAL_SimpleDelay(15);
        /* Wait till PLL is ready */
        timeout = RCC_PLL2_READY_TIMEOUT;
        while ((RCC->PLL2CR & lock) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Initializes the RCC Oscillators according to the specified parameters
*         in the RCC_OscInitTypeDef.
*@param : RCC_OscInit: pointer to an RCC_OscInitTypeDef structure that contains 
*         the configuration information for the RCC Oscillators.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_PLL2SSCConfig(FunctionalState PLL2, uint32_t ClockSource, \
                            uint32_t PLLN, uint32_t PLLF, uint32_t PLLP, uint32_t PLLQ, \
                            FunctionalState SSC, uint32_t Mode, uint32_t Spectrum, uint32_t Step)
{
    uint32_t lock;
    uint32_t timeout;
    #ifdef USE_FULL_ASSERT
    double freq;
    #endif
    
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(PLL2));
    
    if (PLL2 == DISABLE)
    {
        /* disable PLL2 */
        RCC->PLL2CR &= ~RCC_PLL2CR_PLL2EN;
        /* enter sleep mode */
        RCC->PLL2CR |= RCC_PLL2CR_PLL2SLEEP;
        HAL_SimpleDelay(15);
    }
    else
    {
        /* Check the parameters */
        assert_param(IS_RCC_PLL_CLOCK_SOURCE(ClockSource));
        assert_param(IS_RCC_PLL2_PLLN(PLLN));
        assert_param(IS_RCC_PLL2_PLLF(PLLF));
        assert_param(IS_RCC_PLL2_PLLP(PLLP));
        assert_param(IS_RCC_PLL2_PLLQ(PLLQ));
        
        if (ClockSource == RCC_PLL_SOURCE_RCH_DIV16)
        {
            if ((RCC->RCHCR & (RCC_RCHCR_RCHDIV | RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY)) != \
                              (RCC_RCHCR_RCHDIV | RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY))
                return (HAL_ERROR);
            lock = RCC_PLL2CR_PLL2FREERUN;
            #ifdef USE_FULL_ASSERT
            freq = (double)4000000;
            #endif
        }
        else
        {
            if ((RCC_XTHCR_XTHRDY | RCC_XTHCR_XTHEN) != (RCC->XTHCR & (RCC_XTHCR_XTHRDY | RCC_XTHCR_XTHEN)))
                return (HAL_ERROR);
            lock = RCC_PLL2CR_PLL2LOCK;
            #ifdef USE_FULL_ASSERT
            freq = (double)XTH_VALUE;
            #endif
        }
        
        // FCLK_VCO=FCLKIN*F/N; FCLK_P=FCLK_VCO /P; FCLK_Q=FCLK_VCO /Q
        #ifdef USE_FULL_ASSERT
        assert_param((freq >= 1000000) && (freq <= 132000000));
        freq = freq / PLLN;
        assert_param((freq >= 1000000) && (freq <= 2000000));
        freq = freq * PLLF;
        assert_param((freq >= 100000000) && (freq <= 550000000));
        assert_param(((freq / PLLP) >= 30000000) && ((freq / PLLP) <= 220000000));
        assert_param(((freq / PLLQ) >= 16000000) && ((freq / PLLQ) <= 220000000));
        #endif
        
        RCC->PLL2CR |= RCC_PLL2CR_PLL2LOCKSEL;
        RCC->PLL2CR &= ~(RCC_PLL2CR_PLL2PCLKEN | RCC_PLL2CR_PLL2QCLKEN);
        if (ClockSource == RCC_PLL_SOURCE_RCH_DIV16)
            RCC->PLL2CR &= ~RCC_PLL2CR_PLL2SRCSEL;
        else
            RCC->PLL2CR |= RCC_PLL2CR_PLL2SRCSEL;
        /* lock delay 400us */
        RCC->PLL2CR = (RCC->PLL2CR & ~RCC_PLL2CR_PLL2LOCKDLY) | \
                      ((((uint32_t)(((double)400 * SystemCoreClock) / ((double)512 * 1000000))) \
                      << RCC_PLL2CR_PLL2LOCKDLY_Pos) & RCC_PLL2CR_PLL2LOCKDLY);
        /* enable PLL2 */
        RCC->PLL2CR |= RCC_PLL2CR_PLL2EN;
                              
        if (SSC == DISABLE)
        {
            RCC->PLL2SCR = 0;
        }
        else
        {
            RCC->PLL2SCR = ((Step << RCC_PLL2SCR_PLL2SSCSTP_Pos) & RCC_PLL2SCR_PLL2SSCSTP) | \
                            ((Spectrum << RCC_PLL2SCR_PLL2SSCPER_Pos) & RCC_PLL2SCR_PLL2SSCPER) | \
                            Mode | RCC_PLL2SCR_PLL2SSCEN;
        }
        
        /* exit sleep mode */
        RCC->PLL2CR &= ~RCC_PLL2CR_PLL2SLEEP;
        HAL_SimpleDelay(15);
        /* Wait till PLL is ready */
        timeout = RCC_PLL2_READY_TIMEOUT;
        while ((RCC->PLL2CR & RCC_PLL2CR_PLL2FREERUN) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
        
        RCC->PLL2CFR = (((PLLQ) << RCC_PLL2CFR_PLL2Q_Pos) & RCC_PLL2CFR_PLL2Q) | \
                       (((((PLLP) >> 1) - 1) << RCC_PLL2CFR_PLL2P_Pos) & RCC_PLL2CFR_PLL2P) | \
                       (((PLLN) << RCC_PLL2CFR_PLL2N_Pos) & RCC_PLL2CFR_PLL2N) | \
                       (((PLLF) << RCC_PLL2CFR_PLL2F_Pos) & RCC_PLL2CFR_PLL2F);
        
        if (ClockSource == RCC_PLL_SOURCE_XTH)
        {
            RCC->PLL2CR &= ~RCC_PLL2CR_PLL2LOCKSEL;
        }
        /* update pll */
        RCC->PLL2CR |= RCC_PLL2CR_PLL2UPDATEEN;
        HAL_SimpleDelay(15);
        /* Wait till PLL is ready */
        timeout = RCC_PLL2_READY_TIMEOUT;
        while ((RCC->PLL2CR & lock) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
    }
    
    return (HAL_OK);
}

HAL_StatusTypeDef HAL_RCC_PLL2PCLKConfig(FunctionalState PLL2PCLK)
{
    if (PLL2PCLK == DISABLE)
        RCC->PLL2CR &= ~RCC_PLL2CR_PLL2PCLKEN;
    else
        RCC->PLL2CR |= RCC_PLL2CR_PLL2PCLKEN;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RCC_PLL2QCLKConfig(FunctionalState PLL2QCLK)
{
    if (DISABLE == PLL2QCLK)
        RCC->PLL2CR &= ~RCC_PLL2CR_PLL2QCLKEN;
    else
        RCC->PLL2CR |= RCC_PLL2CR_PLL2QCLKEN;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Initializes the RCC Oscillators according to the specified parameters
*         in the RCC_OscInitTypeDef.
*@param : RCC_OscInit: pointer to an RCC_OscInitTypeDef structure that contains 
*         the configuration information for the RCC Oscillators.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_PLL3Config(FunctionalState PLL3, uint32_t ClockSource, \
                                     uint32_t PLLN, uint32_t PLLF, uint32_t PLLP, uint32_t PLLQ)
{
    uint32_t lock;
    uint32_t timeout;
    #ifdef USE_FULL_ASSERT
    double freq;
    #endif
    
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(PLL3));
    
    if (DISABLE == PLL3)
    {
        /* disable PLL3 */
        RCC->PLL3CR &= ~RCC_PLL3CR_PLL3EN;
        /* enter sleep mode */
        RCC->PLL3CR |= RCC_PLL3CR_PLL3SLEEP;
    }
    else
    {
        /* Check the parameters */
        assert_param(IS_RCC_PLL_CLOCK_SOURCE(ClockSource));
        assert_param(IS_RCC_PLL3_PLLN(PLLN));
        assert_param(IS_RCC_PLL3_PLLF(PLLF));
        assert_param(IS_RCC_PLL3_PLLP(PLLP));
        assert_param(IS_RCC_PLL3_PLLQ(PLLQ));
        
        if (RCC_PLL_SOURCE_RCH_DIV16 == ClockSource)
        {
            if ((RCC->RCHCR & (RCC_RCHCR_RCHDIV | RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY)) != \
                              (RCC_RCHCR_RCHDIV | RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY))
                return (HAL_ERROR);
            lock = RCC_PLL3CR_PLL3FREERUN;
            #ifdef USE_FULL_ASSERT
            freq = (double)4000000;
            #endif
        }
        else
        {
            if ((RCC_XTHCR_XTHRDY | RCC_XTHCR_XTHEN) != (RCC->XTHCR & (RCC_XTHCR_XTHRDY | RCC_XTHCR_XTHEN)))
                return (HAL_ERROR);
            lock = RCC_PLL3CR_PLL3LOCK;
            #ifdef USE_FULL_ASSERT
            freq = (double)XTH_VALUE;
            #endif
        }

        // FCLK_VCO=FCLKIN*F/N; FCLK_P=FCLK_VCO /P; FCLK_Q=FCLK_VCO /Q

        #ifdef USE_FULL_ASSERT
        assert_param((freq >= 1000000) && (freq <= 50000000));
        freq = freq / PLLN;
        freq = freq * PLLF;
        assert_param((freq >= 200000000) && (freq <= 500000000));
        assert_param(((freq / PLLP) >= 25000000) && ((freq / PLLP) <= 220000000));
        assert_param(((freq / PLLQ) >= 25000000) && ((freq / PLLQ) <= 220000000));
        #endif
        
        RCC->PLL3CR |= RCC_PLL3CR_PLL3LOCKSEL;
        RCC->PLL3CR &= ~(RCC_PLL3CR_PLL3PCLKEN | RCC_PLL3CR_PLL3QCLKEN);
        if (ClockSource == RCC_PLL_SOURCE_RCH_DIV16)
            RCC->PLL3CR &= ~RCC_PLL3CR_PLL3SRCSEL;
        else
            RCC->PLL3CR |= RCC_PLL3CR_PLL3SRCSEL;
        /* lock delay 110us */
        RCC->PLL3CR = (RCC->PLL3CR & ~RCC_PLL3CR_PLL3LOCKDLY) | \
                      ((((uint32_t)(((double)110 * SystemCoreClock) / ((double)512 * 1000000))) \
                      << RCC_PLL3CR_PLL3LOCKDLY_Pos) & RCC_PLL3CR_PLL3LOCKDLY);
        /* enable PLL2 */
        RCC->PLL3CR |= RCC_PLL3CR_PLL3EN;
        /* exit sleep mode */
        RCC->PLL3CR &= ~RCC_PLL3CR_PLL3SLEEP;
        HAL_SimpleDelay(15);
        /* Wait till PLL is ready */
        timeout = RCC_PLL3_READY_TIMEOUT;
        while ((RCC->PLL3CR & RCC_PLL3CR_PLL3FREERUN) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }

        RCC->PLL3CFR = ((((PLLQ) == 1 ? 0 : ((PLLQ) == 2 ? 1 : ((PLLQ) == 4 ? 2 : 3))) << RCC_PLL3CFR_PLL3Q_Pos) & RCC_PLL3CFR_PLL3Q) | \
                       ((((PLLP) == 1 ? 0 : ((PLLP) == 2 ? 1 : ((PLLP) == 4 ? 2 : 3))) << RCC_PLL3CFR_PLL3P_Pos) & RCC_PLL3CFR_PLL3P) | \
                       ((((PLLN) - 1) << RCC_PLL3CFR_PLL3N_Pos) & RCC_PLL3CFR_PLL3N) | \
                       ((((PLLF) - 1) << RCC_PLL3CFR_PLL3F_Pos) & RCC_PLL3CFR_PLL3F);
        
        if (ClockSource == RCC_PLL_SOURCE_XTH)
        {
            RCC->PLL3CR &= ~RCC_PLL3CR_PLL3LOCKSEL;
        }
        /* update pll */
        RCC->PLL3CR |= RCC_PLL3CR_PLL3UPDATEEN;
        HAL_SimpleDelay(15);
        /* Wait till PLL is ready */
        timeout = RCC_PLL3_READY_TIMEOUT;
        while ((RCC->PLL3CR & lock) == 0)
        {
            if (timeout-- == 0)
                return (HAL_TIMEOUT);
        }
    }
    
    return (HAL_OK);
}

HAL_StatusTypeDef HAL_RCC_PLL3PCLKConfig(FunctionalState PLL3PCLK)
{
    if (PLL3PCLK == DISABLE)
        RCC->PLL3CR &= ~RCC_PLL3CR_PLL3PCLKEN;
    else
        RCC->PLL3CR |= RCC_PLL3CR_PLL3PCLKEN;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RCC_PLL3QCLKConfig(FunctionalState PLL3QCLK)
{
    if (PLL3QCLK == DISABLE)
        RCC->PLL3CR &= ~RCC_PLL3CR_PLL3QCLKEN;
    else
        RCC->PLL3CR |= RCC_PLL3CR_PLL3QCLKEN;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RCC_ITConfig(uint32_t IT, FunctionalState NewStatus)
{
    /* Check the parameters */
    assert_param(IS_RCC_IT(IT));
    
    if (NewStatus)
        RCC->CIR |= ((IT & RCC_IT_READY_MASK) << 8) | ((IT & RCC_IT_STOP_MASK) >> 3);
    else
        RCC->CIR &= ~((((IT & RCC_IT_READY_MASK)) << 8) | ((IT & RCC_IT_STOP_MASK) >> 3));
    
    return HAL_OK;
}

uint32_t HAL_RCC_GetITFlag(uint32_t IT)
{
    /* Check the parameters */
    assert_param(IS_RCC_IT(IT));
    
    if ((RCC->CIR & IT) == IT)
        return true;
    else
        return false;
}

HAL_StatusTypeDef HAL_RCC_ClearITFlag(uint32_t IT)
{
    /* Check the parameters */
    assert_param(IS_RCC_IT(IT));
    
    RCC->CIR |=  ((IT & RCC_IT_READY_MASK) << 16) | ( (IT & RCC_IT_STOP_MASK) >> 2);
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Initializes the CPU, AHB and APB buses clocks according to the 
*         specified parameters in the RCC_ClkInitTypeDef.
*@param : RCC_ClkInit: pointer to an RCC_ClkInitTypeDef structure that
*         contains the configuration information for the RCC peripheral.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInit)
{
    /* Check the parameters */
    assert_param(IS_RCC_CLOCK_TYPE(RCC_ClkInit->ClockType));
    
    /* first level frequency division of system clock */
    if (RCC_ClkInit->ClockType & RCC_CLOCK_TYPE_SYSDIV0)
    {
        if (HAL_RCC_SYSCLKDiv0Config(RCC_ClkInit->SYSCLKDiv0) != HAL_OK)
            return HAL_ERROR;
    }
    
    /* second level frequency division of system clock */
    if (RCC_ClkInit->ClockType & RCC_CLOCK_TYPE_SYSDIV1)
    {
        if (HAL_RCC_SYSCLKDiv1Config(RCC_ClkInit->SYSCLKDiv1) != HAL_OK)
            return HAL_ERROR;
    }
    
    /* frequency division of PCLK1 clock */
    if (RCC_ClkInit->ClockType & RCC_CLOCK_TYPE_PCLK1)
    {
        if (HAL_RCC_PCLK1DivConfig(RCC_ClkInit->PCLK1Div) != HAL_OK)
            return HAL_ERROR;
    }
    
    /* frequency division of PCLK2 clock */
    if (RCC_ClkInit->ClockType & RCC_CLOCK_TYPE_PCLK2)
    {
        if (HAL_RCC_PCLK2DivConfig(RCC_ClkInit->PCLK2Div) != HAL_OK)
            return HAL_ERROR;
    }
    
    /* frequency division of PCLK3 clock */
    if (RCC_ClkInit->ClockType & RCC_CLOCK_TYPE_PCLK3)
    {
        if (HAL_RCC_PCLK3DivConfig(RCC_ClkInit->PCLK3Div) != HAL_OK)
            return HAL_ERROR;
    }
    
    /* frequency division of PCLK4 clock */
    if (RCC_ClkInit->ClockType & RCC_CLOCK_TYPE_PCLK4)
    {
        if (HAL_RCC_PCLK4DivConfig(RCC_ClkInit->PCLK4Div) != HAL_OK)
            return HAL_ERROR;
    }
    
    /* system clok source configuration */
    if (RCC_ClkInit->ClockType & RCC_CLOCK_TYPE_SYSCLK)
    {
        if (HAL_RCC_SYSCLKSourceConfig(RCC_ClkInit->SYSCLKSource) != HAL_OK)
            return HAL_ERROR;
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Switch the system clock.
*@param : SYSCLKSource: SYSCLK clock source.
*         This parameter must be a value of @ref RCC_Sysclk_Source.
*             @arg RCC_SYSCLKSOURCE_RCH: RCH clock selected as SYSCLK source
*             @arg RCC_SYSCLKSOURCE_RCL: RCL clock selected as SYSCLK source
*             @arg RCC_SYSCLKSOURCE_XTH: XTH clock selected as SYSCLK source
*             @arg RCC_SYSCLKSOURCE_XTL: XTL clock selected as SYSCLK source
*             @arg RCC_SYSCLKSOURCE_PLL1PCLK: PLL1PCLK clock selected as SYSCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_SYSCLKSourceConfig(uint32_t ClockSource)
{
    uint32_t temp;
    
    /* Check the parameters */
    assert_param(IS_RCC_SYSCLK_SOURCE(ClockSource));
    
    if (ClockSource == RCC_SYSCLK_SOURCE_RCH)
    {
        /* Check whether the RCH clock is turned on and running stably */
        if ((RCC->RCHCR & (RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY)) != (RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY))
            return HAL_ERROR;
        
        /* system clok source configuration */
        RCC->CCR1 = RCC->CCR1 & ~RCC_CCR1_SYSCLKSEL;
    }
    else if (RCC_SYSCLK_SOURCE_XTH == ClockSource)
    {
        /* Check whether the XTH clock is turned on and running stably */
        if ((RCC->XTHCR & (RCC_XTHCR_XTHEN | RCC_XTHCR_XTHRDY)) != (RCC_XTHCR_XTHEN | RCC_XTHCR_XTHRDY))
            return HAL_ERROR;
        
        /* system clok source configuration */
        RCC->CCR1 = (RCC->CCR1 & ~RCC_CCR1_SYSCLKSEL) | RCC_CCR1_SYSCLKSEL_1;
    }
    else
    {
        /* Check whether the PLL clock is turned on and running stably */
        if (RCC->PLL1CR & RCC_PLL1CR_PLL1SRCSEL)
        {
            if ((RCC->PLL1CR & (RCC_PLL1CR_PLL1SLEEP | RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1PCLKEN | RCC_PLL1CR_PLL1LOCK)) != \
                                                      (RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1PCLKEN | RCC_PLL1CR_PLL1LOCK))
                return HAL_ERROR;
        }
        else
        {
            if ((RCC->PLL1CR & (RCC_PLL1CR_PLL1SLEEP | RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1PCLKEN | RCC_PLL1CR_PLL1FREERUN)) != \
                                                      (RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1PCLKEN | RCC_PLL1CR_PLL1FREERUN))
                return HAL_ERROR;
        }
        
        /* system clok source configuration */
        RCC->CCR1 = (RCC->CCR1 & ~RCC_CCR1_SYSCLKSEL) | RCC_CCR1_SYSCLKSEL_1 | RCC_CCR1_SYSCLKSEL_0;
    }
    
    temp = SystemCoreClock;
    SystemCoreClock = HAL_RCC_GetSysCoreClockFreq();
    if (temp != SystemCoreClock)
    {
        HAL_InitTick(g_systickHandle.intPrio,g_systickHandle.msPeriod);
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_SYSCLKDiv0Config(uint32_t Div)
{
    uint32_t temp;
    uint32_t timeout;
    
    /* Check the parameters */
    assert_param(IS_RCC_SYSCLK_DIV(Div));
    
    RCC->CCR2 = (RCC->CCR2 & ~RCC_CCR2_SYSDIV0) | (((Div - 1) << RCC_CCR2_SYSDIV0_Pos) & RCC_CCR2_SYSDIV0);
    HAL_SimpleDelay(5);
    /* Wait till the update frequency division to complete */
    timeout = 256u;
    while ((RCC->CCR2 & RCC_CCR2_DIVDONE) == 0)
    {
        if (timeout-- == 0)
            return (HAL_TIMEOUT);
    }
    
    temp = SystemCoreClock;
    SystemCoreClock = HAL_RCC_GetSysCoreClockFreq();
    if (temp != SystemCoreClock)
    {
        HAL_InitTick(g_systickHandle.intPrio,g_systickHandle.msPeriod);
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_SYSCLKDiv1Config(uint32_t Div)
{
    uint32_t temp;
    uint32_t timeout;
    
    /* Check the parameters */
    assert_param(IS_RCC_SYSCLK_DIV(Div));
    
    RCC->CCR2 = (RCC->CCR2 & ~RCC_CCR2_SYSDIV1) | (((Div - 1) << RCC_CCR2_SYSDIV1_Pos) & RCC_CCR2_SYSDIV1);
    
    HAL_SimpleDelay(2);
    
    /* Wait till the update frequency division to complete */
    timeout = 256u;
    while ((RCC->CCR2 & RCC_CCR2_DIVDONE) == 0)
    {
        if (timeout-- == 0)
            return (HAL_TIMEOUT);
    }
    
    temp = SystemCoreClock;
    SystemCoreClock = HAL_RCC_GetSysCoreClockFreq();
    if (temp != SystemCoreClock)
    {
        HAL_InitTick(g_systickHandle.intPrio,g_systickHandle.msPeriod);
    }
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_PCLK1DivConfig(uint32_t Div)
{
    /* Check the parameters */
    assert_param(IS_RCC_PCLK_DIV(Div));
    
    RCC->CCR2 = (RCC->CCR2 & ~RCC_CCR2_PCLK1DIV) | ((Div == 1 ? 0 : \
                                                    (Div == 2 ? 4 : \
                                                    (Div == 4 ? 5 : \
                                                    (Div == 8 ? 6 : 7)))) << RCC_CCR2_PCLK1DIV_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_PCLK2DivConfig(uint32_t Div)
{
    /* Check the parameters */
    assert_param(IS_RCC_PCLK_DIV(Div));
    
    RCC->CCR2 = (RCC->CCR2 & ~RCC_CCR2_PCLK2DIV) | ((Div == 1 ? 0 : \
                                                    (Div == 2 ? 4 : \
                                                    (Div == 4 ? 5 : \
                                                    (Div == 8 ? 6 : 7)))) << RCC_CCR2_PCLK2DIV_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_PCLK3DivConfig(uint32_t Div)
{
    /* Check the parameters */
    assert_param(IS_RCC_PCLK_DIV(Div));
    
    RCC->CCR2 = (RCC->CCR2 & ~RCC_CCR2_PCLK3DIV) | ((Div == 1 ? 0 : \
                                                    (Div == 2 ? 4 : \
                                                    (Div == 4 ? 5 : \
                                                    (Div == 8 ? 6 : 7)))) << RCC_CCR2_PCLK3DIV_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_PCLK4DivConfig(uint32_t Div)
{
    /* Check the parameters */
    assert_param(IS_RCC_PCLK_DIV(Div));
    
    RCC->CCR2 = (RCC->CCR2 & ~RCC_CCR2_PCLK4DIV) | ((Div == 1 ? 0 : \
                                                    (Div == 2 ? 4 : \
                                                    (Div == 4 ? 5 : \
                                                    (Div == 8 ? 6 : 7)))) << RCC_CCR2_PCLK4DIV_Pos);
    
    return (HAL_OK);
}


/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_HRNGSClockDivConfig(uint32_t Div)
{
    /* Check the parameters */
    assert_param(IS_RCC_HRNGS_CLK_DIV(Div));
    
    /* FLTCLK clok source configuration */
    RCC->CCR2 = (RCC->CCR2 & ~RCC_CCR2_HRNGSDIV) | (((Div - 1) << RCC_CCR2_HRNGSDIV_Pos) & RCC_CCR2_HRNGSDIV);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_FLTClockSourceConfig(uint32_t ClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_FLT_CLK_SOURCE(ClockSource));
    
    /* FLTCLK clok source configuration */
    RCC->CCR2 = (RCC->CCR2 & ~RCC_CCR2_FLTCLKSEL) | ((ClockSource << RCC_CCR2_FLTCLKSEL_Pos) & RCC_CCR2_FLTCLKSEL);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure LPUART1 clock source.
*@param : ClockSource: LPUART1 clock source.
*         This parameter must be a value of @ref RCC_LPUART1_CLK_Source.
*             @arg RCC_LPUART1_CLK_SOURCE_RCL : 
*             @arg RCC_LPUART1_CLK_SOURCE_XTL :
*             @arg RCC_LPUART1_CLK_SOURCE_PCLK1_DIV4 : 
*             @arg RCC_LPUART1_CLK_SOURCE_PCLK1_DIV8 : 
*             @arg RCC_LPUART1_CLK_SOURCE_PCLK1_DIV16 : 
*             @arg RCC_LPUART1_CLK_SOURCE_PCLK1_DIV32 : 
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_LPUART1ClockSourceConfig(uint32_t ClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPUART1_CLK_SOURCE(ClockSource));
    
    /* FLTCLK clok source configuration */
    if (ClockSource <= RCC_LPUART1_CLK_SOURCE_XTL)
        RCC->PERCFGR = (RCC->PERCFGR & ~(RCC_PERCFGR_LPUART1CKS | RCC_PERCFGR_LPUART1DIV)) | \
                       (ClockSource << RCC_PERCFGR_LPUART1CKS_Pos);
    else
        RCC->PERCFGR = (RCC->PERCFGR & ~(RCC_PERCFGR_LPUART1CKS | RCC_PERCFGR_LPUART1DIV)) | \
                       RCC_PERCFGR_LPUART1CKS_1 | ((ClockSource - 2) << RCC_PERCFGR_LPUART1DIV_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM1_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM1_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM1_CLK_SOURCE_RCH: RCH clock selected as FLTCLK source
*             @arg RCC_LPTIM1_CLK_SOURCE_XTL: XTL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_LPTIM1ClockSourceConfig(uint32_t ClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM1_CLK_SOURCE(ClockSource));
    
    /* FLTCLK clok source configuration */
    RCC->PERCFGR = (RCC->PERCFGR & ~RCC_PERCFGR_LPTIM1CKS) | (ClockSource << RCC_PERCFGR_LPTIM1CKS_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM2_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM2_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM2_CLK_SOURCE_RCH: RCH clock selected as FLTCLK source
*             @arg RCC_LPTIM2_CLK_SOURCE_XTL: XTL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_LPTIM2ClockSourceConfig(uint32_t ClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM2_CLK_SOURCE(ClockSource));
    
    /* FLTCLK clok source configuration */
    RCC->PERCFGR = (RCC->PERCFGR & ~RCC_PERCFGR_LPTIM2CKS) | (ClockSource << RCC_PERCFGR_LPTIM2CKS_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM345_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCH: RCH clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_XTL: XTL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_LPTIM3ClockSourceConfig(uint32_t ClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM3_CLK_SOURCE(ClockSource));
    
    /* FLTCLK clok source configuration */
    RCC->PERCFGR = (RCC->PERCFGR & ~RCC_PERCFGR_LPTIM345CKS) | (ClockSource << RCC_PERCFGR_LPTIM345CKS_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM345_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCH: RCH clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_XTL: XTL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_LPTIM4ClockSourceConfig(uint32_t ClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM4_CLK_SOURCE(ClockSource));
    
    /* FLTCLK clok source configuration */
    RCC->PERCFGR = (RCC->PERCFGR & ~RCC_PERCFGR_LPTIM345CKS) | (ClockSource << RCC_PERCFGR_LPTIM345CKS_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM345_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCH: RCH clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_XTL: XTL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_LPTIM5ClockSourceConfig(uint32_t ClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM5_CLK_SOURCE(ClockSource));
    
    /* FLTCLK clok source configuration */
    RCC->PERCFGR = (RCC->PERCFGR & ~RCC_PERCFGR_LPTIM345CKS) | (ClockSource << RCC_PERCFGR_LPTIM345CKS_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM6_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM6_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM6_CLK_SOURCE_RCH: RCH clock selected as FLTCLK source
*             @arg RCC_LPTIM6_CLK_SOURCE_XTL: XTL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_LPTIM6ClockSourceConfig(uint32_t ClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM6_CLK_SOURCE(ClockSource));
    
    /* FLTCLK clok source configuration */
    RCC->PERCFGR = (RCC->PERCFGR & ~RCC_PERCFGR_LPTIM6CKS) | (ClockSource << RCC_PERCFGR_LPTIM6CKS_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_SDMMC_CLK_SOURCE_SYSCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_SDMMC_CLK_SOURCE_PLL2PCLK: PLL2P clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_SDMMCClockSourceConfig(uint32_t ClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_SDMMC_CLK_SOURCE(ClockSource));
    
    /* FLTCLK clok source configuration */
    RCC->PERCFGR = (RCC->PERCFGR & ~RCC_PERCFGR_SDMMCCKS) | (ClockSource << RCC_PERCFGR_SDMMCCKS_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_SDIO_CLK_SOURCE_SYSCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_SDIO_CLK_SOURCE_PLL2_P_CLK: PLL2P clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_SDMMCSampleClockSourceConfig(uint32_t SampleClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_SDMMC_SCLK_SOURCE(SampleClockSource));
    
    /* FLTCLK clok source configuration */
    RCC->PERCFGR = (RCC->PERCFGR & ~RCC_PERCFGR_SDMMCSCKS) | (SampleClockSource << RCC_PERCFGR_SDMMCSCKS_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_SDIO_CLK_SOURCE_SYS_CLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_SDIO_CLK_SOURCE_PLL2_P_CLK: PLL2P clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_LCDPiexlClockDivConfig(uint32_t Div)
{
    /* Check the parameters */
    assert_param(IS_RCC_LCD_CLK_DIV(Div));
    
    /* FLTCLK clok source configuration */
    RCC->DCKCFG = (RCC->DCKCFG & ~RCC_DCKCFG_LCDDIV) | ((Div == 2 ? 0 : \
                                                        (Div == 4 ? 1 : \
                                                        (Div == 8 ? 2 : 3))) << RCC_DCKCFG_LCDDIV_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_RTC_CLK_SOURCE_RCL: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_RTC_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_RTCClockSourceConfig(uint32_t ClockSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_RTC_CLK_SOURCE(ClockSource));
    
    /* FLTCLK clok source configuration */
    RCC->STDBYCTRL = (RCC->STDBYCTRL & ~RCC_STDBYCTRL_RTCSEL) | (ClockSource << RCC_STDBYCTRL_RTCSEL_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Initializes the CPU, AHB and APB buses clocks according to the 
*         specified parameters in the RCC_ClkInitTypeDef.
*@param : RCC_ClkInit: pointer to an RCC_ClkInitTypeDef structure that
*         contains the configuration information for the RCC peripheral.
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetClock(RCC_ClkInitTypeDef  *RCC_ClkInit)
{
    uint32_t temp;
    
    if (RCC_ClkInit == NULL)
        return HAL_ERROR;
    
    HAL_RCC_GetSYSCLKSource(&RCC_ClkInit->SYSCLKSource);
    
    RCC_ClkInit->SYSCLKDiv0 = ((RCC->CCR2 & RCC_CCR2_SYSDIV0) >> RCC_CCR2_SYSDIV0_Pos) + 1;
    RCC_ClkInit->SYSCLKDiv1 = ((RCC->CCR2 & RCC_CCR2_SYSDIV1) >> RCC_CCR2_SYSDIV1_Pos) + 1;
    
    temp = (RCC->CCR2 & RCC_CCR2_PCLK1DIV) >> RCC_CCR2_PCLK1DIV_Pos;
    if (temp < 4)
        temp = 1;
    else
        temp = 1 << (temp - 3);
    RCC_ClkInit->PCLK1Div = temp;
    
    temp = (RCC->CCR2 & RCC_CCR2_PCLK2DIV) >> RCC_CCR2_PCLK2DIV_Pos;
    if (temp < 4)
        temp = 1;
    else
        temp = 1 << (temp - 3);
    RCC_ClkInit->PCLK2Div = temp;
    
    temp = (RCC->CCR2 & RCC_CCR2_PCLK3DIV) >> RCC_CCR2_PCLK3DIV_Pos;
    if (temp < 4)
        temp = 1;
    else
        temp = 1 << (temp - 3);
    RCC_ClkInit->PCLK3Div = temp;
    
    temp = (RCC->CCR2 & RCC_CCR2_PCLK4DIV) >> RCC_CCR2_PCLK4DIV_Pos;
    if (temp < 4)
        temp = 1;
    else
        temp = 1 << (temp - 3);
    RCC_ClkInit->PCLK4Div = temp;
    
    RCC_ClkInit->ClockType = RCC_CLOCK_TYPE_SYSCLK | RCC_CLOCK_TYPE_SYSDIV0 | RCC_CLOCK_TYPE_SYSDIV1 | \
                             RCC_CLOCK_TYPE_PCLK1 | RCC_CLOCK_TYPE_PCLK2 | RCC_CLOCK_TYPE_PCLK3 | RCC_CLOCK_TYPE_PCLK4;
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Switch the system clock.
*@param : SYSCLKSource: SYSCLK clock source.
*         This parameter must be a value of @ref RCC_Sysclk_Source.
*             @arg RCC_SYSCLKSOURCE_RCH: RCH clock selected as SYSCLK source
*             @arg RCC_SYSCLKSOURCE_RCL: RCL clock selected as SYSCLK source
*             @arg RCC_SYSCLKSOURCE_XTH: XTH clock selected as SYSCLK source
*             @arg RCC_SYSCLKSOURCE_XTL: XTL clock selected as SYSCLK source
*             @arg RCC_SYSCLKSOURCE_PLLCLK: PLL clock selected as SYSCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetSYSCLKSource(uint32_t *pClockSource)
{
    uint32_t source;
    
    if (pClockSource == NULL)
        return HAL_ERROR;
        
    source = (RCC->CCR1 & RCC_CCR1_SYSCLKSEL) >> RCC_CCR1_SYSCLKSEL_Pos;
    
    if (source <= 1)
        source = RCC_SYSCLK_SOURCE_RCH;
    else if (source == 2)
        source = RCC_SYSCLK_SOURCE_XTH;
    else
        source = RCC_SYSCLK_SOURCE_PLL1PCLK;
    
    *pClockSource = source;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetHRNGSlowClockDiv(uint32_t *pClockDiv)
{
    if (pClockDiv == NULL)
        return HAL_ERROR;
        
    *pClockDiv = ((RCC->CCR2 & RCC_CCR2_HRNGSDIV) >> RCC_CCR2_HRNGSDIV_Pos) + 1;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetFLTClockSource(uint32_t *pClockSource)
{
    if (pClockSource == NULL)
        return HAL_ERROR;
    
    *pClockSource = (RCC->CCR2 & RCC_CCR2_FLTCLKSEL) >> RCC_CCR2_FLTCLKSEL_Pos;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPUART1_CLK_SOURCE_RCL: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPUART1_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*             @arg RCC_LPUART1_CLK_SOURCE_PCLK: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetLPUART1ClockSource(uint32_t *pClockSource)
{
    uint32_t source;
    
    if (pClockSource == NULL)
        return HAL_ERROR;
    
    source = (RCC->PERCFGR & RCC_PERCFGR_LPUART1CKS) >> RCC_PERCFGR_LPUART1CKS_Pos;
    
    if (source <= 1)
    {
        *pClockSource = source;
        return HAL_OK;
    }
    
    if (source == 2)
    {
        source = (RCC->PERCFGR & RCC_PERCFGR_LPUART1DIV) >> RCC_PERCFGR_LPUART1DIV_Pos;
        *pClockSource = source + 2;
        return HAL_OK;
    }
    
    return HAL_ERROR;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM1_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM1_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM1_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM1_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetLPTIM1ClockSource(uint32_t *pClockSource)
{
    if (pClockSource == NULL)
        return HAL_ERROR;
        
    *pClockSource = (RCC->PERCFGR & RCC_PERCFGR_LPTIM1CKS) >> RCC_PERCFGR_LPTIM1CKS_Pos;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM2_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM2_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM2_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM2_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetLPTIM2ClockSource(uint32_t *pClockSource)
{
    if (pClockSource == NULL)
        return HAL_ERROR;
        
    *pClockSource = (RCC->PERCFGR & RCC_PERCFGR_LPTIM2CKS) >> RCC_PERCFGR_LPTIM2CKS_Pos;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM345_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetLPTIM3ClockSource(uint32_t *pClockSource)
{
    if (pClockSource == NULL)
        return HAL_ERROR;
        
    *pClockSource = (RCC->PERCFGR & RCC_PERCFGR_LPTIM345CKS) >> RCC_PERCFGR_LPTIM345CKS_Pos;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM345_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetLPTIM4ClockSource(uint32_t *pClockSource)
{
    if (pClockSource == NULL)
        return HAL_ERROR;
        
    *pClockSource = (RCC->PERCFGR & RCC_PERCFGR_LPTIM345CKS) >> RCC_PERCFGR_LPTIM345CKS_Pos;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM345_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetLPTIM5ClockSource(uint32_t *pClockSource)
{
    if (pClockSource == NULL)
        return HAL_ERROR;
        
    *pClockSource = (RCC->PERCFGR & RCC_PERCFGR_LPTIM345CKS) >> RCC_PERCFGR_LPTIM345CKS_Pos;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM6_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM6_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM6_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM6_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetLPTIM6ClockSource(uint32_t *pClockSource)
{
    if (pClockSource == NULL)
        return HAL_ERROR;
        
    *pClockSource = (RCC->PERCFGR & RCC_PERCFGR_LPTIM6CKS) >> RCC_PERCFGR_LPTIM6CKS_Pos;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_SDIO_CLK_SOURCE_SYS_CLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_SDIO_CLK_SOURCE_PLL2_P_CLK: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetSDMMCClockSource(uint32_t *pClockSource)
{
    if (pClockSource == NULL)
        return HAL_ERROR;
        
    *pClockSource = (RCC->PERCFGR & RCC_PERCFGR_SDMMCCKS) >> RCC_PERCFGR_SDMMCCKS_Pos;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_SDIO_CLK_SOURCE_SYS_CLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_SDIO_CLK_SOURCE_PLL2_P_CLK: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetSDMMCSampleClockSource(uint32_t *pClockSource)
{
    if (pClockSource == NULL)
        return HAL_ERROR;
        
    *pClockSource = (RCC->PERCFGR & RCC_PERCFGR_SDMMCSCKS) >> RCC_PERCFGR_SDMMCSCKS_Pos;

    return HAL_OK;
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_RTC_CLK_SOURCE_RCL: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_RTC_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RCC_GetRTCClockSource(uint32_t *pClockSource)
{
//    uint32_t source;
    
    if (pClockSource == NULL)
        return HAL_ERROR;
        
    if (RCC->STDBYCTRL & RCC_STDBYCTRL_RTCSEL_1)
        return HAL_ERROR;
    
    *pClockSource = (RCC->STDBYCTRL & RCC_STDBYCTRL_RTCSEL) >> RCC_STDBYCTRL_RTCSEL_Pos;
    
    return HAL_OK;
}

/******************************************************************************
*@brief : Returns RC64M infact value
*@return: RC64M val
******************************************************************************/
uint32_t HAL_RCC_GetRCHTrimFreq(void)
{
    uint32_t freq;
    
    HAL_EFUSE_RpEnable(EFUSE1);
    HAL_EFUSE_ReadBytes(EFUSE1, 0x1C, (uint8_t *)&freq, 4, 100000);
    
    if ((freq > 76800000) || (freq < 51200000))
        return 64000000;
    else
        return freq;
}

/******************************************************************************
*@brief : Returns RC32K infact value
*@return: RC32K val
******************************************************************************/
uint32_t HAL_RCC_GetRCLTrimFreq(void)
{
    uint32_t freq;
    
    HAL_EFUSE_RpEnable(EFUSE1);
    HAL_EFUSE_ReadBytes(EFUSE1, 0x20, (uint8_t *)&freq, 4, 100000);
    
    if ((freq > 39321) || (freq < 26214))
        return 32768;
    else
        return freq;
}

/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetRCHFreq(void)
{
    uint32_t freq;
    
    if ((RCC->RCHCR & (RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY)) != (RCC_RCHCR_RCHEN | RCC_RCHCR_RCHRDY))
        return (0);
    
    freq = HAL_RCC_GetRCHTrimFreq();
    
    if (RCC->RCHCR & RCC_RCHCR_RCHDIV)
        freq = freq >> 4;
    
    return (freq);
}

/******************************************************************************
*@brief : Returns RCL infact value
*@return: RCL val
******************************************************************************/
uint32_t HAL_RCC_GetRCLFreq(void)
{
    if ((RCC->STDBYCTRL & (RCC_STDBYCTRL_RCLEN | RCC_STDBYCTRL_RCLRDY)) != (RCC_STDBYCTRL_RCLEN | RCC_STDBYCTRL_RCLRDY))
        return (0);
    
    return (HAL_RCC_GetRCLTrimFreq());
}


/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetXTHFreq(void)
{
    if ((RCC->XTHCR & (RCC_XTHCR_XTHEN | RCC_XTHCR_XTHRDY)) == (RCC_XTHCR_XTHEN | RCC_XTHCR_XTHRDY))
        return (XTH_VALUE);
    else
        return 0;
}

/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetXTLFreq(void)
{
    if ((RCC->STDBYCTRL & (RCC_STDBYCTRL_XTLEN | RCC_STDBYCTRL_XTLRDY)) == (RCC_STDBYCTRL_XTLEN | RCC_STDBYCTRL_XTLRDY))
        return (32768U);
    else
        return (0);
}

/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetPLL1Freq(void)
{
    uint32_t freq;
    uint32_t plln;
    uint32_t pllf;
    
    if (RCC->PLL1CR & RCC_PLL1CR_PLL1SRCSEL)
    {
        if ((RCC->PLL1CR & (RCC_PLL1CR_PLL1SLEEP | RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1LOCK | RCC_PLL1CR_PLL1PCLKEN)) != \
                                                  (RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1LOCK | RCC_PLL1CR_PLL1PCLKEN))
        {
            return (0);
        }
        freq = HAL_RCC_GetXTHFreq();
    }
    else
    {
        if ((RCC->PLL1CR & (RCC_PLL1CR_PLL1SLEEP | RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1FREERUN | RCC_PLL1CR_PLL1PCLKEN)) != \
                                                  (RCC_PLL1CR_PLL1EN | RCC_PLL1CR_PLL1FREERUN | RCC_PLL1CR_PLL1PCLKEN))
        {
            return (0);
        }
        freq = HAL_RCC_GetRCHFreq();
    }
    
    if (freq == 0)
        return (0);
    
    plln = (RCC->PLL1CFR & RCC_PLL1CFR_PLL1N_Msk) >> RCC_PLL1CFR_PLL1N_Pos;
    if (plln == 0)
        plln = 1;
    
    pllf = (RCC->PLL1CFR & RCC_PLL1CFR_PLL1F_Msk) >> RCC_PLL1CFR_PLL1F_Pos;
    if (pllf < 50)
        pllf = 50;
    
    freq = (uint32_t)((uint64_t)freq * pllf / plln);
    
    return (freq);
}

/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetPLL1PFreq(void)
{
    uint32_t freq;
    uint32_t pllp;
    
    freq = HAL_RCC_GetPLL1Freq();
    if (freq == 0)
        return (0);
    
    pllp = (RCC->PLL1CFR & RCC_PLL1CFR_PLL1P_Msk) >> RCC_PLL1CFR_PLL1P_Pos;
    pllp = (pllp + 1) << 1;
    
    freq = freq / pllp;
    
    return (freq);
}

/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetPLL2Freq(void)
{
    uint32_t freq;
    uint32_t plln;
    uint32_t pllf;
    
    if (RCC->PLL2CR & RCC_PLL2CR_PLL2SRCSEL)
    {
        if ((RCC->PLL2CR & (RCC_PLL2CR_PLL2SLEEP | RCC_PLL2CR_PLL2EN | RCC_PLL2CR_PLL2LOCK | RCC_PLL2CR_PLL2PCLKEN)) != \
                                                  (RCC_PLL2CR_PLL2EN | RCC_PLL2CR_PLL2LOCK | RCC_PLL2CR_PLL2PCLKEN))
        {
            return (0);
        }
        freq = HAL_RCC_GetXTHFreq();
    }
    else
    {
        if ((RCC->PLL2CR & (RCC_PLL2CR_PLL2SLEEP | RCC_PLL2CR_PLL2EN | RCC_PLL2CR_PLL2FREERUN | RCC_PLL2CR_PLL2PCLKEN)) != \
                                                  (RCC_PLL2CR_PLL2EN | RCC_PLL2CR_PLL2FREERUN | RCC_PLL2CR_PLL2PCLKEN))
        {
            return (0);
        }
        freq = HAL_RCC_GetRCHFreq();
    }
    
    if (freq == 0)
        return (0);
    
    plln = (RCC->PLL2CFR & RCC_PLL2CFR_PLL2N_Msk) >> RCC_PLL2CFR_PLL2N_Pos;
    if (plln == 0)
        plln = 1;
    
    pllf = (RCC->PLL2CFR & RCC_PLL2CFR_PLL2F_Msk) >> RCC_PLL2CFR_PLL2F_Pos;
    if (pllf < 50)
        pllf = 50;
    
    freq = (uint32_t)((uint64_t)freq * pllf / plln);
    
    return (freq);
}

/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetPLL2QFreq(void)
{
    uint32_t freq;
    uint32_t pllq;
    
    freq = HAL_RCC_GetPLL2Freq();
    if (freq == 0)
        return (0);
    
    pllq = (RCC->PLL2CFR & RCC_PLL2CFR_PLL2Q_Msk) >> RCC_PLL2CFR_PLL2Q_Pos;
    if (pllq == 0)
        pllq = 1;
    
    freq = freq / pllq;
    
    return (freq);
}

/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetPLL2PFreq(void)
{
    uint32_t freq;
    uint32_t pllp;
    
    freq = HAL_RCC_GetPLL2Freq();
    if (freq == 0)
        return (0);
    
    pllp = (RCC->PLL2CFR & RCC_PLL2CFR_PLL2P_Msk) >> RCC_PLL2CFR_PLL2P_Pos;
    pllp = (pllp + 1) << 1;
    
    freq = freq / pllp;
    
    return (freq);
}

/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetPLL3Freq(void)
{
    uint32_t freq;
    uint32_t plln;
    uint32_t pllf;
    
    if (RCC->PLL3CR & RCC_PLL3CR_PLL3SRCSEL)
    {
        if ((RCC->PLL3CR & (RCC_PLL3CR_PLL3SLEEP | RCC_PLL3CR_PLL3EN | RCC_PLL3CR_PLL3LOCK | RCC_PLL3CR_PLL3QCLKEN)) != \
                                                  (RCC_PLL3CR_PLL3EN | RCC_PLL3CR_PLL3LOCK | RCC_PLL3CR_PLL3QCLKEN))
        {
            return (0);
        }
        freq = HAL_RCC_GetXTHFreq();
    }
    else
    {
        if ((RCC->PLL3CR & (RCC_PLL3CR_PLL3SLEEP | RCC_PLL3CR_PLL3EN | RCC_PLL3CR_PLL3FREERUN | RCC_PLL3CR_PLL3QCLKEN)) != \
                                                  (RCC_PLL3CR_PLL3EN | RCC_PLL3CR_PLL3FREERUN | RCC_PLL3CR_PLL3QCLKEN))
        {
            return (0);
        }
        freq = HAL_RCC_GetRCHFreq();
    }
    
    if (freq == 0)
        return (0);
    
    plln = ((RCC->PLL3CFR & RCC_PLL3CFR_PLL3N_Msk) >> RCC_PLL3CFR_PLL3N_Pos) + 1;
    
    pllf = ((RCC->PLL3CFR & RCC_PLL3CFR_PLL3F_Msk) >> RCC_PLL3CFR_PLL3F_Pos) + 1;
    
    freq = (uint32_t)((uint64_t)freq * pllf / plln);
    
    return (freq);
}

/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetPLL3QFreq(void)
{
    uint32_t freq;
    uint32_t pllq;
    
    freq = HAL_RCC_GetPLL3Freq();
    if (freq == 0)
        return (0);
    
    pllq = (RCC->PLL3CFR & RCC_PLL3CFR_PLL3Q_Msk) >> RCC_PLL3CFR_PLL3Q_Pos;
    if (pllq == 0)
        pllq = 1;
    else if (pllq == 1)
        pllq = 2;
    else if (pllq == 2)
        pllq = 4;
    else
        pllq = 8;
    
    freq = freq / pllq;
    
    return (freq);
}

/******************************************************************************
*@brief : Returns RCH infact value
*@return: RCH val
******************************************************************************/
uint32_t HAL_RCC_GetPLL3PFreq(void)
{
    uint32_t freq;
    uint32_t pllp;
    
    freq = HAL_RCC_GetPLL3Freq();
    if (freq == 0)
        return (0);
    
    pllp = (RCC->PLL3CFR & RCC_PLL3CFR_PLL3P_Msk) >> RCC_PLL3CFR_PLL3P_Pos;
    if (pllp == 0)
        pllp = 1;
    else if (pllp == 1)
        pllp = 2;
    else if (pllp == 2)
        pllp = 4;
    else
        pllp = 8;
    
    freq = freq / pllp;
    
    return (freq);
}

/******************************************************************************
*@brief : Returns the SYSCLK frequency
*@return: SYSCLK frequency
******************************************************************************/
uint32_t HAL_RCC_GetSYSCLKFreq(void)
{
    uint32_t source;
    
    source = (RCC->CCR1 & RCC_CCR1_SYSCLKSEL) >> RCC_CCR1_SYSCLKSEL_Pos;
    
    if (source < 1)
        return HAL_RCC_GetRCHFreq();
    
    if (source == 2)
        return HAL_RCC_GetXTHFreq();
    
    return HAL_RCC_GetPLL1PFreq();
}

/******************************************************************************
*@brief : Returns the SysCoreClock frequency
*@return: SysCoreClock frequency
******************************************************************************/
uint32_t HAL_RCC_GetSysCoreClockFreq(void)
{
    uint32_t div;
    uint32_t freq = 0U;
    
    freq = HAL_RCC_GetSYSCLKFreq();
    
    /* first level frequency division of system clock */
    div = ((RCC->CCR2 & RCC_CCR2_SYSDIV0) >> RCC_CCR2_SYSDIV0_Pos) + 1;
    
    freq = freq / div;
    
    /* second level frequency division of system clock */
    div = ((RCC->CCR2 & RCC_CCR2_SYSDIV1) >> RCC_CCR2_SYSDIV1_Pos) + 1;
    
    freq = freq / div;
    
    SystemCoreClock = freq;
    
    return (freq);
}

/******************************************************************************
*@brief : Returns the FCLK (Core) frequency
*@return: FCLK frequency
******************************************************************************/
uint32_t HAL_RCC_GetFCLKFreq(void)
{
    return SystemCoreClock;
}

/******************************************************************************
*@brief : Returns the HCLK (AHB CLK) frequency
*@return: HCLK frequency
******************************************************************************/
uint32_t HAL_RCC_GetHCLKFreq(void)
{
    return SystemCoreClock;
}

/******************************************************************************
*@brief : Returns the PCLK1 (APB1 CLK) frequency
*@return: PCLK1 frequency
******************************************************************************/
uint32_t HAL_RCC_GetPCLK1Freq(void)
{
    if ((RCC->CCR2 & RCC_CCR2_PCLK1DIV_2) == 0)
        return (SystemCoreClock);
    
    return (SystemCoreClock >> (((RCC->CCR2 & (RCC_CCR2_PCLK1DIV_0 | RCC_CCR2_PCLK1DIV_1)) >> RCC_CCR2_PCLK1DIV_Pos) + 1));
}

/******************************************************************************
*@brief : Returns the PCLK2 (APB2 CLK) frequency
*@return: PCLK2 frequency
******************************************************************************/
uint32_t HAL_RCC_GetPCLK2Freq(void)
{
    if ((RCC->CCR2 & RCC_CCR2_PCLK2DIV_2) == 0)
        return (SystemCoreClock);
    
    return (SystemCoreClock >> (((RCC->CCR2 & (RCC_CCR2_PCLK2DIV_0 | RCC_CCR2_PCLK2DIV_1)) >> RCC_CCR2_PCLK2DIV_Pos) + 1));
}

/******************************************************************************
*@brief : Returns the PCLK2 (APB2 CLK) frequency
*@return: PCLK2 frequency
******************************************************************************/
uint32_t HAL_RCC_GetPCLK3Freq(void)
{
    if ((RCC->CCR2 & RCC_CCR2_PCLK3DIV_2) == 0)
        return (SystemCoreClock);
    
    return (SystemCoreClock >> (((RCC->CCR2 & (RCC_CCR2_PCLK3DIV_0 | RCC_CCR2_PCLK3DIV_1)) >> RCC_CCR2_PCLK3DIV_Pos) + 1));
}

/******************************************************************************
*@brief : Returns the PCLK2 (APB2 CLK) frequency
*@return: PCLK2 frequency
******************************************************************************/
uint32_t HAL_RCC_GetPCLK4Freq(void)
{
    if ((RCC->CCR2 & RCC_CCR2_PCLK4DIV_2) == 0)
        return (SystemCoreClock);
    
    return (SystemCoreClock >> (((RCC->CCR2 & (RCC_CCR2_PCLK4DIV_0 | RCC_CCR2_PCLK4DIV_1)) >> RCC_CCR2_PCLK4DIV_Pos) + 1));
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetHRNGSClockFreq(void)
{
    return (SystemCoreClock / (((RCC->CCR2 & RCC_CCR2_HRNGSDIV) >> RCC_CCR2_HRNGSDIV_Pos) + 1));
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_FLT_CLK_SOURCE_PCLK_DIV32: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_FLT_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetFLTClockFreq(void)
{
    if ((RCC->CCR2 & RCC_CCR2_FLTCLKSEL) == 0)
        return (HAL_RCC_GetPCLK1Freq() >> 5);
    else
        return (HAL_RCC_GetRCLFreq());
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPUART1_CLK_SOURCE_RCL: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPUART1_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*             @arg RCC_LPUART1_CLK_SOURCE_PCLK: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetLPUART1ClockFreq(void)
{
    uint32_t source;
    
    source = (RCC->PERCFGR & RCC_PERCFGR_LPUART1CKS) >> RCC_PERCFGR_LPUART1CKS_Pos;
    
    if (source == 0)
        return (HAL_RCC_GetRCLFreq());
    
    if (source == 1)
        return (HAL_RCC_GetXTLFreq());
    
    if (source == 2)
        return (HAL_RCC_GetPCLK1Freq() >> (((RCC->PERCFGR & RCC_PERCFGR_LPUART1DIV) >> RCC_PERCFGR_LPUART1DIV_Pos) + 2));
    
    return (0);
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM1_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM1_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM1_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM1_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetLPTIM1ClockFreq(void)
{
    uint32_t source;
    
    source = (RCC->PERCFGR & RCC_PERCFGR_LPTIM1CKS) >> RCC_PERCFGR_LPTIM1CKS_Pos;
    
    if (source == 0)
        return (HAL_RCC_GetPCLK1Freq());
    
    if (source == 1)
        return (HAL_RCC_GetRCLFreq());
    
    if (source == 2)
        return (HAL_RCC_GetRCHFreq());
    
    return (HAL_RCC_GetXTLFreq());
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM2_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM2_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM2_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM2_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetLPTIM2ClockFreq(void)
{
    uint32_t source;
    
    source = (RCC->PERCFGR & RCC_PERCFGR_LPTIM2CKS) >> RCC_PERCFGR_LPTIM2CKS_Pos;
    
    if (source == 0)
        return (HAL_RCC_GetPCLK1Freq());
    
    if (source == 1)
        return (HAL_RCC_GetRCLFreq());
    
    if (source == 2)
        return (HAL_RCC_GetRCHFreq());
    
    return (HAL_RCC_GetXTLFreq());
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM345_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetLPTIM3ClockFreq(void)
{
    uint32_t source;
    
    source = (RCC->PERCFGR & RCC_PERCFGR_LPTIM345CKS) >> RCC_PERCFGR_LPTIM345CKS_Pos;
    
    if (source == 0)
        return (HAL_RCC_GetPCLK3Freq());
    
    if (source == 1)
        return (HAL_RCC_GetRCLFreq());
    
    if (source == 2)
        return (HAL_RCC_GetRCHFreq());
    
    return (HAL_RCC_GetXTLFreq());
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM345_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetLPTIM4ClockFreq(void)
{
    uint32_t source;
    
    source = (RCC->PERCFGR & RCC_PERCFGR_LPTIM345CKS) >> RCC_PERCFGR_LPTIM345CKS_Pos;
    
    if (source == 0)
        return (HAL_RCC_GetPCLK3Freq());
    
    if (source == 1)
        return (HAL_RCC_GetRCLFreq());
    
    if (source == 2)
        return (HAL_RCC_GetRCHFreq());
    
    return (HAL_RCC_GetXTLFreq());
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM345_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCL: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM345_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetLPTIM5ClockFreq(void)
{
    uint32_t source;
    
    source = (RCC->PERCFGR & RCC_PERCFGR_LPTIM345CKS) >> RCC_PERCFGR_LPTIM345CKS_Pos;
    
    if (source == 0)
        return (HAL_RCC_GetPCLK3Freq());
    
    if (source == 1)
        return (HAL_RCC_GetRCLFreq());
    
    if (source == 2)
        return (HAL_RCC_GetRCHFreq());
    
    return (HAL_RCC_GetXTLFreq());
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_LPTIM6_CLK_SOURCE_PCLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_LPTIM6_CLK_SOURCE_RCL: RCL selected as FLTCLK source
*             @arg RCC_LPTIM6_CLK_SOURCE_RCH: RCL clock selected as FLTCLK source
*             @arg RCC_LPTIM6_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetLPTIM6ClockFreq(void)
{
    uint32_t source;
    
    source = (RCC->PERCFGR & RCC_PERCFGR_LPTIM6CKS) >> RCC_PERCFGR_LPTIM6CKS_Pos;
    
    if (source == 0)
        return (HAL_RCC_GetPCLK3Freq());
    
    if (source == 1)
        return (HAL_RCC_GetRCLFreq());
    
    if (source == 2)
        return (HAL_RCC_GetRCHFreq());
    
    return (HAL_RCC_GetXTLFreq());
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_SDMMC_CLK_SOURCE_SYS_CLK: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_SDMMC_CLK_SOURCE_PLL2_P_CLK: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetSDMMCClockFreq(void)
{
    if ((RCC->PERCFGR & RCC_PERCFGR_SDMMCCKS) == 0)
        return (HAL_RCC_GetHCLKFreq());
    else
        return (HAL_RCC_GetPLL2PFreq());
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_RTC_CLK_SOURCE_RCL: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_RTC_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetLCDPiexlClockFreq(void)
{
    return (HAL_RCC_GetPLL2QFreq() >> (((RCC->DCKCFG & RCC_DCKCFG_LCDDIV) >> RCC_DCKCFG_LCDDIV_Pos) + 1));
}

/******************************************************************************
*@brief : Configure FLTCLK (LVD and COMP) clock source.
*@param : ClockSource: LVD and COMP clock source.
*         This parameter must be a value of @ref RCC_FLT_CLK_Source.
*             @arg RCC_RTC_CLK_SOURCE_RCL: clock after pclk 32 frequency division selected as FLTCLK source
*             @arg RCC_RTC_CLK_SOURCE_XTL: RCL clock selected as FLTCLK source
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_GetRTCClockFreq(void)
{
    uint32_t source;
    
    if ((RCC->STDBYCTRL & RCC_STDBYCTRL_RTCEN) == 0)
        return (0);
    
    source = (RCC->STDBYCTRL & RCC_STDBYCTRL_RTCSEL) >> RCC_STDBYCTRL_RTCSEL_Pos;
    
    if (source == 0)
        return (HAL_RCC_GetRCLFreq());
    
    if (source == 1)
        return (HAL_RCC_GetXTLFreq());
    
    return (0);
}

/******************************************************************************
*@brief : Configure MCO output.
*@param : MCO_Init: pointer to an RCC_MCOInitTypeDef structure that contains 
*         the configuration information for the MCO output.
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_MCOConfig(RCC_MCOInitTypeDef *MCO_InitStruct)
{
    volatile uint32_t temp;
    
    /* Check the parameters */
    assert_param(IS_RCC_MCO(MCO_InitStruct->MCO));
    assert_param(IS_FUNCTIONAL_STATE(MCO_InitStruct->MCO1));
    assert_param(IS_FUNCTIONAL_STATE(MCO_InitStruct->MCO2));
    
    temp = MCO_InitStruct->MCO;
    
    if (MCO_InitStruct->MCO1)
    {
        assert_param(IS_RCC_MCO1_DIV(MCO_InitStruct->MCO1Div));
        assert_param(IS_FUNCTIONAL_STATE(MCO_InitStruct->MCO1RevPol));
        
        /* MCO1 clock polarity configuration */
        if (MCO_InitStruct->MCO1RevPol)
            temp |= RCC_CLKOCR_MCO1POL;
        
        /* MCO1 division configuration */
        temp |= RCC_CLKOCR_MCO1SEL | RCC_CLKOCR_MCO1EN | ((MCO_InitStruct->MCO1Div - 1) << RCC_CLKOCR_MCO1DIV_Pos);
    }
    else
    {
        assert_param(IS_FUNCTIONAL_STATE(MCO_InitStruct->MCO1RevPol));
        
        /* MCO1 clock polarity configuration */
        if (MCO_InitStruct->MCO1RevPol)
            temp |= RCC_CLKOCR_MCO1POL;
    }
    
    if (MCO_InitStruct->MCO2)
    {
        assert_param(IS_RCC_MCO2_DIV(MCO_InitStruct->MCO2Div));
        assert_param(IS_FUNCTIONAL_STATE(MCO_InitStruct->MCO2RevPol));
        
        /* MCO1 clock polarity configuration */
        if (MCO_InitStruct->MCO2RevPol != DISABLE)
            temp |= RCC_CLKOCR_MCO2POL;
        
        /* MCO1 division configuration */
        temp |= RCC_CLKOCR_MCO2EN | (((MCO_InitStruct->MCO2Div - 1) << RCC_CLKOCR_MCO2DIV_Pos) & RCC_CLKOCR_MCO2DIV);
    }
    else
    {
        assert_param(IS_FUNCTIONAL_STATE(MCO_InitStruct->MCO2RevPol));
        
        /* MCO1 clock polarity configuration */
        if (MCO_InitStruct->MCO2RevPol != DISABLE)
            temp |= RCC_CLKOCR_MCO2POL;
    }
    
    RCC->CLKOCR = temp;
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure MCO1 output.
*@param : MCO_Init: pointer to an RCC_MCOInitTypeDef structure that contains 
*         the configuration information for the MCO output.
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_MCO1Config(uint32_t MCO, uint32_t NewStatus, uint32_t Div)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewStatus));
    
    if (NewStatus == DISABLE)
    {
        RCC->CLKOCR = (RCC->CLKOCR & ~RCC_CLKOCR_MCO1EN) | RCC_CLKOCR_MCO1SEL;
        return HAL_OK;
    }
    
    assert_param(IS_RCC_MCO(MCO));
    assert_param(IS_RCC_MCO1_DIV(Div));
    
    RCC->CLKOCR = (RCC->CLKOCR & ~(RCC_CLKOCR_MCO1DIV | RCC_CLKOCR_MCOCLKS)) | \
                   RCC_CLKOCR_MCO1EN | RCC_CLKOCR_MCO1SEL | \
                  ((Div - 1) << RCC_CLKOCR_MCO1DIV_Pos) | \
                  (MCO << RCC_CLKOCR_MCOCLKS_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Configure MCO1 output.
*@param : MCO_Init: pointer to an RCC_MCOInitTypeDef structure that contains 
*         the configuration information for the MCO output.
*@return: HAL status
******************************************************************************/
uint32_t HAL_RCC_MCO2Config(uint32_t MCO, uint32_t NewStatus, uint32_t Div)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewStatus));
    
    if (DISABLE == NewStatus)
    {
        RCC->CLKOCR = RCC->CLKOCR & ~RCC_CLKOCR_MCO2EN;
        return HAL_OK;
    }
    
    assert_param(IS_RCC_MCO(MCO));
    assert_param(IS_RCC_MCO2_DIV(Div));
    
    RCC->CLKOCR = (RCC->CLKOCR & ~(RCC_CLKOCR_MCO2DIV | RCC_CLKOCR_MCOCLKS)) | RCC_CLKOCR_MCO2EN | \
                  ((Div - 1) << RCC_CLKOCR_MCO2DIV_Pos) | (MCO << RCC_CLKOCR_MCOCLKS_Pos);
    
    return (HAL_OK);
}

/******************************************************************************
*@brief : Software reset
*@return: None
******************************************************************************/
void HAL_RCC_SoftwareReset(void)
{
    RCC->RCR &= ~RCC_RCR_SRST_MAP;
}

/******************************************************************************
*@brief : Standby software reset
*@return: None
******************************************************************************/
void HAL_RCC_StandbyReset(void)
{
    /* check RTC clock source */
    RCC->STDBYCTRL &= ~RCC_STDBYCTRL_STDBYRST;
}

/******************************************************************************
*@brief : Software reset
*@return: None
******************************************************************************/
void HAL_RCC_LockupResetConfig(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState)
        RCC->RCR |= RCC_RCR_LOCKRST_EN;
    else
        RCC->RCR &= ~RCC_RCR_LOCKRST_EN;
}

/******************************************************************************
*@brief : Software reset
*@return: None
******************************************************************************/
void HAL_RCC_IWDTResetConfig(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState)
        RCC->RCR |= RCC_RCR_IWDTRST_EN;
    else
        RCC->RCR = (RCC->RCR & ~(RCC_RCR_IWDTRST_DIS | RCC_RCR_IWDTRST_EN)) | (0xB5UL << RCC_RCR_IWDTRST_DIS_Pos);
}

/******************************************************************************
*@brief : Software reset
*@return: None
******************************************************************************/
void HAL_RCC_WDTResetConfig(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState)
        RCC->RCR |= RCC_RCR_WDTRST_EN;
    else
        RCC->RCR &= ~RCC_RCR_WDTRST_EN;
}

/******************************************************************************
*@brief : Software reset
*@return: None
******************************************************************************/
void HAL_RCC_LVDResetConfig(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState)
        RCC->RCR |= RCC_RCR_LVDRST_EN;
    else
        RCC->RCR &= ~RCC_RCR_LVDRST_EN;
}

/******************************************************************************
*@brief : Software reset
*@return: None
******************************************************************************/
uint32_t HAL_RCC_GetResetSource(void)
{
    return (RCC->RSR & RCC_RESET_SOURCE_MASK);
}

/******************************************************************************
*@brief : Software reset
*@return: None
******************************************************************************/
void HAL_RCC_ClearAllResetSource(void)
{
    RCC->RSR = RCC_RSR_RSTFLAGCLR;
}

#endif /* HAL_RCC_MODULE_ENABLED */

