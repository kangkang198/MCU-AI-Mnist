
/******************************************************************************
*@file  : hal_pmu.c
*@brief : PMU HAL module driver.
******************************************************************************/
#include "hal.h" 


#ifdef HAL_PMU_MODULE_ENABLED

/******************************************************************************
* @brief : PMU Initiation.
* @param : none
* @return: none
******************************************************************************/
void HAL_PMU_Init(void)
{
    //PMU CLK Enable
    __HAL_RCC_PMU_CLK_ENABLE();
    
    HAL_SimpleDelay(10); 
}

/******************************************************************************
* @brief : enter sleep mode.
* @param : mode: Event wake-up or interrupt wake-up
* @return: none
******************************************************************************/
void HAL_PMU_EnterSleep(uint32_t mode)
{  
    /* clear SLEEPDEEP bit of Cortex System Control Register */
    CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));         

    if(mode == WAIT_FOR_INT)       
    {
        /* Wait For Interrupt */
        __WFI();
    }
    else
    {
        /*Wait For Event */
        __SEV();      
        __WFE();
        __WFE();      
    } 
   
}

/******************************************************************************
* @brief : enter stop mode.
* @param : mode: Event wake-up or interrupt wake-up
* @return: none
******************************************************************************/
void HAL_PMU_EnterStop(uint32_t mode)
{
    HAL_PMU_ClearWakeupStatus(ALL_WANKEUP_STATUS);
    
    MODIFY_REG(PMU->CTRL0, PMU_CTRL0_LPMS_Msk, PMU_CTRL0_LPMS_STOP);
    
    HAL_SimpleDelay(1000);//Waiting for PMU area clock synchronization
    
    SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));   // Set SLEEPDEEP bit of Cortex System Control Register 

    if(mode == WAIT_FOR_INT)
    {
        /* Wait For Interrupt */   
        __WFI();
    }
    else
    {
        /* Wait For Event */  
        __SEV();   
        __WFE();
        __WFE();    
    }
    /* clear SLEEPDEEP bit of Cortex System Control Register */
    CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk)); 
}

/******************************************************************************
* @brief : enter standby mode.
* @param : mode: Event wake-up or interrupt wake-up
* @return: none
******************************************************************************/
void HAL_PMU_EnterStandbyMode(uint32_t mode)
{ 
    HAL_PMU_ClearWakeupStatus(ALL_WANKEUP_STATUS);
    
    MODIFY_REG(PMU->CTRL0, PMU_CTRL0_LPMS_Msk, PMU_CTRL0_LPMS_STANDBY);//Standby Mode
    
    HAL_SimpleDelay(1000);//Waiting for PMU area clock synchronization

    SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));   // Set SLEEPDEEP bit of Cortex System Control Register 

    if(mode == WAIT_FOR_INT)
    {
        /* Wait For Interrupt */   
        __WFI();
    }
    else
    {
        /* Wait For Event */  
        __SEV();   
        __WFE();
        __WFE();
    }
    
    /* clear SLEEPDEEP bit of Cortex System Control Register */
    CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk)); 
}

/******************************************************************************
*@brief : Initialize the WakeupIO MSP: CLK, GPIO      
*@param : none.
*@return: none
******************************************************************************/
__weak void HAL_PMU_WakeupIO_MspInit(PMU_WakeUpIo_t wakeup_io)
{
    /* 
      NOTE : This function is implemented in user xxx_hal_msp.c
    */
    
    /* Prevent unused argument(s) compilation warning */
    UNUSED(NULL);
}

/******************************************************************************
* @brief : wakeup source select.
* @param : wakeup_io: wakeup source select(PMU_WAKEUP1 PMU_WAKEUP2 ...) 
* @param : polarity: 0(high level), 1(low level).
* @return: none
******************************************************************************/
void HAL_PMU_WakeupIOInit(PMU_WakeUpIo_t wakeup_io, PMU_WakeUpPolarity_t polarity)
{
    switch (wakeup_io)
    {
        case PMU_WAKEUP1: 
        case PMU_WAKEUP2: 
        case PMU_WAKEUP3: 
        case PMU_WAKEUP4: 
        case PMU_WAKEUP5: 
        {
            HAL_PMU_WakeupIO_MspInit(wakeup_io);
            /* Wakeup IO Filter Enable */
            __HAL_RCC_RTC_CLK_ENABLE();
            PMU->CTRL2 |= wakeup_io << PMU_CTRL2_WUXFILEN_Pos;

            /* Wakeup IO Enable */
            PMU->CTRL2  |= wakeup_io;
               
            if (polarity) 
            {
                PMU->CTRL3 |= wakeup_io;//low level
            }
            else 
            {
                PMU->CTRL3 &= (~wakeup_io);//high level   
            }
 
        }
        break;
        
        default: break;       
    }
}

/******************************************************************************
* @brief : DeInitialize the Wakeup IO.
* @param : wakeup_io: wakeup source select(PMU_WAKEUP1 PMU_WAKEUP2 ...) 
* @return: none
******************************************************************************/
void HAL_PMU_WakeupIODeInit(PMU_WakeUpIo_t wakeup_io)
{
    /* Wakeup IO Filter Disable */
    PMU->CTRL2 &= ~(wakeup_io << PMU_CTRL2_WUXFILEN_Pos);

    /* Wakeup IO Disable */
    PMU->CTRL2 &= (~wakeup_io);    
}

/******************************************************************************
* @brief : wakeup source select.
* @param : Wakeup_rtc: wakeup source select(RTC_WAKEUP_DATE...) 
* @return: none
******************************************************************************/
void HAL_PMU_StandbyWakeupRTCConfig(PMU_WakeUpRtc_t wakeup_rtc)
{
    switch (wakeup_rtc)    
    {
        case STANDBY_WAKEUP_WUTIE:
        case STANDBY_WAKEUP_STAMP2:
        case STANDBY_WAKEUP_STAMP1:
        case STANDBY_WAKEUP_32S:
        case STANDBY_WAKEUP_ALARM:
        case STANDBY_WAKEUP_1KHZ:
        case STANDBY_WAKEUP_256HZ:
        case STANDBY_WAKEUP_64HZ:
        case STANDBY_WAKEUP_16HZ:
        case STANDBY_WAKEUP_8HZ:
        case STANDBY_WAKEUP_4HZ:
        case STANDBY_WAKEUP_2HZ:  
        case STANDBY_WAKEUP_SEC:
        case STANDBY_WAKEUP_MIN:
        case STANDBY_WAKEUP_HOUR:
        case STANDBY_WAKEUP_DATE:        
        {	
            //Enable RTC CLK
            __HAL_RCC_RTC_CLK_ENABLE();

            //Clear flags
            SET_BIT(PMU->STCLR, (PMU_STCLR_CRTCWUF_Msk | PMU_STCLR_CSBF_Msk));

            /* RTC domain write enable */
            SET_BIT(PMU->CTRL0,PMU_CTRL0_RTCWE);
            RTC->SR = wakeup_rtc;
            RTC->IE |= wakeup_rtc;

        }break;

        default: break; 
    }
}

/******************************************************************************
* @brief : Release the selected RTC wakeup source.
* @param : wakeup_rtc: wakeup source select(RTC_WAKEUP_DATE...)  
* @return: none
******************************************************************************/
void HAL_PMU_StandbyWakeupRTCRelease(PMU_WakeUpRtc_t wakeup_rtc)
{
    switch (wakeup_rtc)    
    {
        case STANDBY_WAKEUP_WUTIE:
        case STANDBY_WAKEUP_STAMP2:
        case STANDBY_WAKEUP_STAMP1:
        case STANDBY_WAKEUP_32S:
        case STANDBY_WAKEUP_ALARM:
        case STANDBY_WAKEUP_1KHZ:
        case STANDBY_WAKEUP_256HZ:
        case STANDBY_WAKEUP_64HZ:
        case STANDBY_WAKEUP_16HZ:
        case STANDBY_WAKEUP_8HZ:
        case STANDBY_WAKEUP_4HZ:
        case STANDBY_WAKEUP_2HZ:  
        case STANDBY_WAKEUP_SEC:
        case STANDBY_WAKEUP_MIN:
        case STANDBY_WAKEUP_HOUR:
        case STANDBY_WAKEUP_DATE:        
        {	
            //Enable RTC CLK
            __HAL_RCC_RTC_CLK_ENABLE();
            /* RTC domain write enable */
            SET_BIT(PMU->CTRL0,PMU_CTRL0_RTCWE);
            
            RTC->SR = wakeup_rtc;
            RTC->IE &= (~wakeup_rtc);

        }break;

        default: break;
    }
}

/*********************************************************************************
* @brief : Check MCU have entered standby mode
* @param : none 
* @return: 0: Not Enter Standby Mode,1: Entered Standby Mode
**********************************************************************************/
bool HAL_PMU_CheckStandbyStatus(void)
{
    if (PMU->SR & PMU_SR_SBF_Msk) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

/******************************************************************************
* @brief : Get MCU Wakeup Source.
* @param : none 
* @return: Wakeup Source(PMU_SR_WUPFX_WKUP1¡¢PMU_SR_WUPFX_WKUP2 ...)
******************************************************************************/
uint32_t HAL_PMU_GetWakeupSource(void)
{
    return PMU->SR;
}

/******************************************************************************
* @brief : Clear MCU Wakeup Status.
* @param : status:Wakeup Source(PMU_SR_WUPFX_WKUP1¡¢PMU_SR_WUPFX_WKUP2 ...)  
* @return: none
******************************************************************************/
void HAL_PMU_ClearWakeupStatus(uint32_t status)
{
    PMU->STCLR = status; 
}

/******************************************************************************
* @brief : LVD Enable.
* @param : voltage: LVD threshold voltage selection (PMU_CTRL1_LVD_SEL_171~PMU_CTRL1_LVD_SEL_290)
* @param : filter:  LVD filter time (PMU_CTRL1_FLT_TIME_1~PMU_CTRL1_FLT_TIME_4095)
* @param : filter_en: Digital filter enable (PMU_CTRL1_LVD_FLTEN)
* @return: none
******************************************************************************/
void HAL_PMU_LvdEnable(uint32_t voltage, uint32_t filter, uint32_t filter_en)
{
    assert_param(IS_PMU_LVD_VOLTAGE(voltage));
    assert_param(IS_PMU_LVD_FILTER(filter));
    PMU->CTRL1 = ((voltage) | (PMU_CTRL1_LVDEN) | (filter) | (filter_en));
    HAL_SimpleDelay(100);
}

/******************************************************************************
* @brief : LVD disable.
* @param : none
* @return: none
******************************************************************************/
void HAL_PMU_LvdDisable(void)
{
    PMU->CTRL1 &= (~PMU_CTRL1_LVDEN);
}

/******************************************************************************
* @brief : BOR Reset Enable.
* @param : voltage: BOR voltage selection (PMU_CTRL2_BOR_CFG_2V0~PMU_CTRL2_BOR_CFG_2V77)
* @return: none
******************************************************************************/
void HAL_PMU_BorResetEnable(uint32_t voltage)
{
    assert_param(IS_PMU_BOR_VOLTAGE(voltage));
    
    PMU->CTRL2 = (PMU->CTRL2 & (~(PMU_CTRL2_BORCFG))) | ((voltage) | (PMU_CTRL2_BOREN) | (PMU_CTRL2_BORRSTEN));
    HAL_SimpleDelay(100);
}

/******************************************************************************
* @brief : BOR Reset Disable.
* @param : none
* @return: none
******************************************************************************/
void HAL_PMU_BorResetDisable(void)
{
    PMU->CTRL2 &= (~((PMU_CTRL2_BOREN) | (PMU_CTRL2_BORRSTEN)));
    HAL_SimpleDelay(100);
}

/******************************************************************************
* @brief : Set the wake-up waiting time of Stop mode.
* @param : stopWaitTime: STOP wake-up waiting time
* @return: none
******************************************************************************/
void HAL_PMU_StopWaitTime(uint32_t stopWaitTime)
{
    assert_param(IS_PMU_STOP_WAKE_WAIT(stopWaitTime));
    PMU->CTRL0 &= (~PMU_CTRL0_STOPWPT_Msk);
    PMU->CTRL0 |= stopWaitTime << PMU_CTRL0_STOPWPT_Pos;   
} 

/******************************************************************************
* @brief : Set the wake-up waiting time of standby mode.
* @param : standbyWaitTime: standby wake-up waiting time
* @return: none
******************************************************************************/
void HAL_PMU_StandbypWaitTime(uint32_t standbyWaitTime)
{
    assert_param(IS_PMU_STANDBY_WAKE_WAIT(standbyWaitTime));
    PMU->CTRL2 &= (~PMU_CTRL2_STDBYWPT_Msk);
    PMU->CTRL2 |= standbyWaitTime << PMU_CTRL2_STDBYWPT_Pos;   
} 

/******************************************************************************
* @brief:  STANDBY domain IO function selection.
* @param:  PMU_Pin: specifies the STANDBY domain IO Pin.
* @param:  PMU_Func: Specify the IO pin function of STANDBY domain.
* @return: None
******************************************************************************/
void HAL_PMU_StandbyDomainPinConfig(uint32_t PMU_Pin, uint32_t PMU_Func)
{
    /* Check the parameters */
    assert_param(IS_PMU_PIN(PMU_Pin));
    assert_param(IS_PMU_PIN_FUNCTION(PMU_Func));
    
    /* PC13 pin function selection */
    if(PMU_Pin == PMU_PIN_PC13)
    {
        /* Clear PC13_SEL bits */
        PMU->IOSEL &= (~PMU_IOSEL_PC13SEL_Msk);
        
        /* Set PC13_SEL bits according to PMU_Func value */
        PMU->IOSEL |= (PMU_Func << PMU_IOSEL_PC13SEL_Pos);
    }
    /* PC14 pin function selection */
    else if(PMU_Pin == PMU_PIN_PC14)
    {
        /* Clear PC14_SEL bits */
        PMU->IOSEL &= (~PMU_IOSEL_PC14SEL_Msk);
        
        /* Set PC14_SEL bits according to PMU_Func value */
        PMU->IOSEL |= (PMU_Func << PMU_IOSEL_PC14SEL_Pos);
    }
    /* PC15 pin function selection */
    else if(PMU_Pin == PMU_PIN_PC15)
    {
        /* Clear PC15_SEL bits */
        PMU->IOSEL &= (~PMU_IOSEL_PC15SEL_Msk);
        
        /* Set PC15_SEL bits according to PMU_Func value */
        PMU->IOSEL |= (PMU_Func << PMU_IOSEL_PC15SEL_Pos);
    }
    /* PI8 pin function selection */
    else
    {
        /* Clear PI8_SEL bits */
        PMU->IOSEL &= (~PMU_IOSEL_PI8SEL_Msk);
        
        /* Set PI8_SEL bits according to PMU_Func value */
        PMU->IOSEL |= (PMU_Func << PMU_IOSEL_PI8SEL_Pos);

    }
}

/******************************************************************************
* @brief:  Set STANDBY domain IO value.
* @param:  PMU_Pin: specifies the STANDBY domain IO Pin.
* @param:  PMU_PinValue: specifies the STANDBY domain Pin Value.
* @return: None
******************************************************************************/
void HAL_PMU_SetStandbyDomainPinValue(uint32_t PMU_Pin, uint32_t PMU_PinValue)
{
    /* Check the parameters */
    assert_param(IS_PMU_PIN(PMU_Pin));
    assert_param(IS_PMU_PIN_VALUE(PMU_PinValue));
    
    /* PC13 pin function selection */
    if(PMU_Pin == PMU_PIN_PC13)
    {
        /* Clear PC13_Value bits */
        PMU->IOSEL &= (~PMU_IOSEL_PC13VALUE_Msk);
        
        /* Set PC13_Value bits according to PMU_Func value */
        PMU->IOSEL |= (PMU_PinValue << PMU_IOSEL_PC13VALUE_Pos);
    }
    /* PC14 pin function selection */
    else if(PMU_Pin == PMU_PIN_PC14)
    {
        /* Clear PC14_Value bits */
        PMU->IOSEL &= (~PMU_IOSEL_PC14VALUE_Msk);
        
        /* Set PC14_Value bits according to PMU_Func value */
        PMU->IOSEL |= (PMU_PinValue << PMU_IOSEL_PC14VALUE_Pos);
    }
    /* PC15 pin function selection */
    else if(PMU_Pin == PMU_PIN_PC15)
    {
        /* Clear PC15_Value bits */
        PMU->IOSEL &= (~PMU_IOSEL_PC15VALUE_Msk);
        
        /* Set PC15_Value bits according to PMU_Func value */
        PMU->IOSEL |= (PMU_PinValue << PMU_IOSEL_PC15VALUE_Pos);
    }
    /* PI8 pin function selection */
    else
    {
        /* Clear PI8_Value bits */
        PMU->IOSEL &= (~PMU_IOSEL_PI8VALUE_Msk);
        
        /* Set PI8_Value bits according to PMU_Func value */
        PMU->IOSEL |= (PMU_PinValue << PMU_IOSEL_PI8VALUE_Pos);
    }
}

/******************************************************************************
* @brief:  Get STANDBY domain IO value.
* @param:  PMU_Pin: specifies the STANDBY domain IO Pin.
* @return: Pin Value
******************************************************************************/
uint32_t HAL_PMU_GetStandbyDomainPinValue(uint32_t PMU_Pin)
{
    uint32_t tmp_value = 0;
    /* Check the parameters */
    assert_param(IS_PMU_PIN(PMU_Pin));
    
    /* get PC13 pin value */
    if(PMU_Pin == PMU_PIN_PC13)
    {
        tmp_value = ((PMU->IOSEL & PMU_IOSEL_PC13VALUE_Msk) >> PMU_IOSEL_PC13VALUE_Pos);
    }
    /* get PC14 pin value */
    else if(PMU_Pin == PMU_PIN_PC14)
    {
        tmp_value = ((PMU->IOSEL & PMU_IOSEL_PC14VALUE_Msk) >> PMU_IOSEL_PC14VALUE_Pos);
    }
    /* get PC15 pin value */
    else if(PMU_Pin == PMU_PIN_PC15)
    {
        tmp_value = ((PMU->IOSEL & PMU_IOSEL_PC15VALUE_Msk) >> PMU_IOSEL_PC15VALUE_Pos);
    }
    /* get PI8 pin value */
    else
    {
        tmp_value = ((PMU->IOSEL & PMU_IOSEL_PI8VALUE_Msk) >> PMU_IOSEL_PI8VALUE_Pos);
    }
    return tmp_value;
}
   

/******************************************************************************
*@brief : PMU domain pin PC13 output type.
*@param : type: output type.
*@return: None
******************************************************************************/
void HAL_PMU_StandbyDomainPinPC13OutputType(uint32_t type)
{
    /* Check the parameters */
    assert_param(IS_PMU_PIN_PC13_OUTPUT(type));
    
    /* Clear PC13_Value bits */
    PMU->IOSEL &= (~PMU_IOSEL_PC13VALUE_Msk);

    /* Set PC13_Value bits according to type value */
    PMU->IOSEL |= (type << PMU_IOSEL_PC13VALUE_Pos);
}

#endif






