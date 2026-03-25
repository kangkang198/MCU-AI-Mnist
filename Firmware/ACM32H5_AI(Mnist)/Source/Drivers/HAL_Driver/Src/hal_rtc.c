
/******************************************************************************
* @file      : HAL_RTC.c
* @version   : 1.0
* @date      : 2022.10.25
* @brief     : RTC HAL module driver
*   
* @history   :	
*   2022.10.25    lwq    create
*   
******************************************************************************/
#include "hal.h"

#ifdef HAL_RTC_MODULE_ENABLED



/******************************************************************************
* @brief : Initialize the RTC peripheral.
* @param : hrtc: Pointer to a RTC_ConfigTypeDef structure that contains
*                the configuration information for the specified RTC module.
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_RTC_Config(RTC_ConfigTypeDef *hrtc)
{
    /* Check RTC Parameter */
    assert_param(IS_RTC_CLOCKSRC(hrtc->ClockSource));
    assert_param(IS_RTC_COMPENSATION(hrtc->Compensation));
    assert_param(IS_RTC_COMPENSATION_VALUE(hrtc->CompensationValue));

    /* Enable PMU CLK */
    __HAL_RCC_PMU_CLK_ENABLE();		
    /* Enable RTC Moudle CLK */
    __HAL_RCC_RTC_CLK_ENABLE();

    /* Enable RTC CLK */
    SET_BIT(RCC->STDBYCTRL, RCC_STDBYCTRL_RTCEN);
    /* RTC domain write enable */
    SET_BIT(PMU->CTRL0,PMU_CTRL0_RTCWE);

    switch (hrtc->ClockSource)
    {
        case RTC_CLOCK_RC32K: 
        {
            //RC32K Enable
            RCC->STDBYCTRL |= RCC_STDBYCTRL_RCLEN;
            while(!(RCC->STDBYCTRL & RCC_STDBYCTRL_RCLRDY));			
            //RTC SEL RC32K
            RCC->STDBYCTRL &= ~RCC_STDBYCTRL_RTCSEL;

        }break;

        case RTC_CLOCK_XTL: 
        {
            RCC->STDBYCTRL = (RCC->STDBYCTRL & ~RCC_STDBYCTRL_XTLDRV) | (RCC_STDBYCTRL_XTLDRV_1 | RCC_STDBYCTRL_XTLDRV_0);

            RCC->STDBYCTRL |= RCC_STDBYCTRL_XTLEN;
            while(!(RCC->STDBYCTRL & RCC_STDBYCTRL_XTLRDY));

            //RTC SEL XTL
            RCC->STDBYCTRL |= RCC_STDBYCTRL_RTCSEL_0;
        }break;

        default: break; 
    }

    RTC->ADJUST = hrtc->Compensation | hrtc->CompensationValue;
    

    return HAL_OK;
}

/******************************************************************************
* @brief : Set RTC current time.
* @param : time: Pointer to RTC_TimeTypeDef structure
* @return: none
******************************************************************************/
void HAL_RTC_SetTime(RTC_TimeTypeDef *time)
{
    /* Check RTC Parameter */
    assert_param(IS_RTC_HOUR(time->Hour));
    assert_param(IS_RTC_MINUTES(time->Minute));
    assert_param(IS_RTC_SECONDS(time->Second));


    /* Write-Protect Disable */
    RTC->WP = RTC_WRITE_PROTECT_DISABLE;

    RTC->HOUR = time->Hour;
    RTC->MIN  = time->Minute;
    RTC->SEC  = time->Second;


    /* Write-Protect Enable */
    RTC->WP = RTC_WRITE_PROTECT_ENABLE;
}

/******************************************************************************
* @brief : Get RTC current time.
* @param : time: Pointer to RTC_TimeTypeDef structure
* @return: none
******************************************************************************/
void HAL_RTC_GetTime(RTC_TimeTypeDef *time)
{
    time->Hour   = RTC->HOUR;
    time->Minute = RTC->MIN;
    time->Second = RTC->SEC;
}


/******************************************************************************
* @brief : Set RTC current Date.
* @param : date: Pointer to RTC_DateTypeDef structure
* @return: none
******************************************************************************/
void HAL_RTC_SetDate(RTC_DateTypeDef *date)
{
    /* Check RTC Parameter */
    assert_param(IS_RTC_YEAR(date->Year));
    assert_param(IS_RTC_MONTH(date->Month));
    assert_param(IS_RTC_DAY(date->Date));
    assert_param(IS_RTC_WEEKDAY(date->WeekDay));


    /* Write-Protect Disable */
    RTC->WP = RTC_WRITE_PROTECT_DISABLE;

    RTC->YEAR  = date->Year;
    RTC->MONTH = date->Month;
    RTC->DAY  = date->Date;
    RTC->WEEK  = date->WeekDay;
	

    /* Write-Protect Enable */
    RTC->WP = RTC_WRITE_PROTECT_ENABLE;
}

/******************************************************************************
* @brief : Get RTC current Date.
* @param : date: Pointer to RTC_DateTypeDef structure
* @return: none
******************************************************************************/
void HAL_RTC_GetDate(RTC_DateTypeDef *date)
{
    date->Year    = RTC->YEAR;
    date->Month   = RTC->MONTH;
    date->Date    = RTC->DAY;
    date->WeekDay = RTC->WEEK;
}

/******************************************************************************
* @brief : Alarm Config.
* @param : alarm: Pointer to RTC_AlarmTypeDef structure.
* @return: none
******************************************************************************/
void HAL_RTC_AlarmConfig(RTC_AlarmTypeDef *alarm)
{
    uint32_t lu32_WeekDay;
    
    /* Check RTC Parameter */
    assert_param(IS_RTC_ALARM_MODE(alarm->u32_AlarmMode));
    assert_param(IS_RTC_ALARM_INT(alarm->u32_AlarmInterrupt));
    assert_param(IS_RTC_ALARM_DAY_MASK(alarm->u32_DayMask));
    assert_param(IS_RTC_ALARM_HOUR_MASK(alarm->u32_HourMask));
    assert_param(IS_RTC_ALARM_MIN_MASK(alarm->u32_MinMask));    
    assert_param(IS_RTC_HOUR(alarm->u32_Hours));
    assert_param(IS_RTC_MINUTES(alarm->u32_Minutes));
    assert_param(IS_RTC_SECONDS(alarm->u32_Seconds));
    
    if (alarm->u32_AlarmMode == RTC_ALM_ALM_WDS_WEEK) 
    {
        assert_param(IS_RTC_ALARM_WEEKDAY(alarm->u32_AlarmWeek));
        lu32_WeekDay = alarm->u32_AlarmWeek;
    }
    else 
    {
        assert_param(IS_RTC_DAY(alarm->u32_AlarmDay));
        lu32_WeekDay = alarm->u32_AlarmDay << RTC_ALM_ALMWEEK_ALMDAY_Pos;
    }
    
    /* Coinfig Week/Day¡¢Hour¡¢Min¡¢Sec */
    RTC->ALM = alarm->u32_AlarmMode | lu32_WeekDay | alarm->u32_Hours << RTC_ALM_ALMHOUR_Pos | alarm->u32_Minutes << RTC_ALM_ALMMIN_Pos | alarm->u32_Seconds;

    /* Interrupt Enable */
    if (RTC_ALARM_INT_ENABLE == alarm->u32_AlarmInterrupt) 
    {
        RTC->IE |= RTC_IE_ALM_IE;
    }

    MODIFY_REG(RTC->CR, RTC_CR_ALM_MSKD, alarm->u32_DayMask); 
    
    MODIFY_REG(RTC->CR, RTC_CR_ALM_MSKH, alarm->u32_HourMask); 
    
    MODIFY_REG(RTC->CR, RTC_CR_ALM_MSKM, alarm->u32_MinMask); 
}

/******************************************************************************
* @brief : Alarm Enable.
* @param : none.
* @return: none
******************************************************************************/
void HAL_RTC_AlarmEnable(void)
{
    RTC->CR |= RTC_CR_ALM_EN;
}

/******************************************************************************
* @brief : Alarm Disable.
* @param : none.
* @return: none
******************************************************************************/
void HAL_RTC_AlarmDisable(void)
{
    RTC->CR &= ~RTC_CR_ALM_EN;
}


/******************************************************************************
* @brief : RTC Tamper Config.
* @param : temperx: RTC_TEMPER_1 or RTC_TEMPER_2 
* @param : temper: Pointer to RTC_TemperTypeDef structure
* @return: none
******************************************************************************/
void HAL_RTC_Tamper(RTC_Temper_t temperx, RTC_TemperTypeDef *temper)
{

    /* Check RTC Parameter */
    assert_param(IS_RTC_TEMP_EDGE(temper->u32_TemperEdge));
    assert_param(IS_RTC_TEMP_INT(temper->u32_InterruptEN));
    assert_param(IS_RTC_TEMP_CLEAR_BACKUP(temper->u32_ClearBackup));
    assert_param(IS_RTC_TEMP_FILTER(temper->u32_Filter));
    assert_param(IS_RTC_TEMP_FILTER_CLK(temper->u32_FilterClk));
    assert_param(IS_FUNCTIONAL_STATE(temper->u32_FilterEn));
    switch (temperx)
    {
        case RTC_TEMPER_1: 
        {
            /* RTC domain write enable */
            SET_BIT(PMU->CTRL0,PMU_CTRL0_RTCWE);
            
            /* Configure PC13 as tamper function */ 
            __HAL_PMU_PC13_SEL(PMU_IOSEL_PC13_SEL_RTC_TAMPER);            
            
            /* Clear Config */
            RTC->CR &= ~(RTC_CR_TAMP1RCLR | RTC_CR_TAMP1FCLR | RTC_CR_TAMP1FLTEN | RTC_CR_TAMP1FLT_Msk | RTC_CR_TS1EDGE | RTC_CR_TAMPFLTCLK_Msk);
			
            if(temper->u32_FilterEn == ENABLE)
            {
                RTC->CR |= RTC_CR_TAMP1FLTEN;
            }
            else
            {
                RTC->CR &= ~RTC_CR_TAMP1FLTEN;                
            }
            /* Edge select */
            RTC->CR |= temper->u32_TemperEdge ? RTC_CR_TS1EDGE : 0x00;
            /* Auto clear backup register */
            if (temper->u32_ClearBackup) 
            {
                RTC->CR |= temper->u32_TemperEdge ? RTC_CR_TAMP1FCLR : RTC_CR_TAMP1RCLR;
            }
            /* Temper filter clock*/
            RTC->CR |= temper->u32_FilterClk; 

            /* Temper filter */
            RTC->CR |= temper->u32_Filter << RTC_CR_TAMP1FLT_Pos;

            RTC->CR |= RTC_CR_TAMP1EN;  
            
            HAL_SimpleDelay(2000);  
            
            RTC->SR = (RTC_SR_STP1FIF | RTC_SR_STP1RIF);   
            RTC->IE &= (~(RTC_IE_STP1FIE | RTC_IE_STP1RIE));      
            
            /* Put Temper Interrupt enable here !!!*/   
            if (temper->u32_InterruptEN) 
            {
                RTC->IE |= temper->u32_TemperEdge ? RTC_IE_STP1FIE : RTC_IE_STP1RIE;
            }               
 
        }break;
        
        case RTC_TEMPER_2:
        {
            /* RTC domain write enable */
            SET_BIT(PMU->CTRL0,PMU_CTRL0_RTCWE);
            
            /* Configure PI8 as tamper function */ 
            __HAL_PMU_PI8_SEL(PMU_IOSEL_PI8_SEL_RTC_TAMPER);  
            
            /* Clear Config */
            RTC->CR &= ~(RTC_CR_TAMP2RCLR | RTC_CR_TAMP2FCLR | RTC_CR_TAMP2FLTEN | RTC_CR_TAMP2FLT_Msk | RTC_CR_TS2EDGE | RTC_CR_TAMPFLTCLK_Msk);
            
            if(temper->u32_FilterEn == ENABLE)
            {
                RTC->CR |= RTC_CR_TAMP2FLTEN;
            }
            else
            {
                RTC->CR &= ~RTC_CR_TAMP2FLTEN;                
            }

            /* Edge select */
            RTC->CR |= temper->u32_TemperEdge ? RTC_CR_TS2EDGE : 0x00;
            /* Auto clear backup register */
            if (temper->u32_ClearBackup) 
            {
                RTC->CR |= temper->u32_TemperEdge ? RTC_CR_TAMP2FCLR : RTC_CR_TAMP2RCLR;
            }
            
            /* Temper filter clock*/
            RTC->CR |= temper->u32_FilterClk;
            
            /* Temper filter */
            RTC->CR |= temper->u32_Filter << 19;
                
            RTC->CR |= RTC_CR_TAMP2EN;
            
            HAL_SimpleDelay(2000);   
            
            RTC->SR = (RTC_SR_STP2FIF|RTC_SR_STP2RIF);   
            RTC->IE &= (~(RTC_IE_STP2FIE|RTC_IE_STP2RIE));  
            
            /* Temper Interrupt */
            if (temper->u32_InterruptEN) 
            {
                RTC->IE |= temper->u32_TemperEdge ? RTC_IE_STP2FIE : RTC_IE_STP2RIE;
            }

        }break;

        default: break; 
    }
}

/******************************************************************************
* @brief : RTC Tamper Enable.
* @param : temperx: RTC_TEMPER_1 or RTC_TEMPER_2 
* @return: none
******************************************************************************/
void HAL_RTC_TamperEnable(RTC_Temper_t temperx)
{
    if (temperx == RTC_TEMPER_1) 
    {
        RTC->CR |= RTC_CR_TAMP1EN;
    }
    else 
    {
        RTC->CR |= RTC_CR_TAMP2EN;
    }
}

/******************************************************************************
* @brief : RTC Tamper Disable.
* @param : temperx: RTC_TEMPER_1 or RTC_TEMPER_2 
* @return: none
******************************************************************************/
void HAL_RTC_TamperDisable(RTC_Temper_t temperx)
{
    if (temperx == RTC_TEMPER_1) 
    {
        RTC->CR &= ~RTC_CR_TAMP1EN;
    }
    else 
    {
        RTC->CR &= ~RTC_CR_TAMP2EN;
    }
}

/******************************************************************************
* @brief : Sets wakeup timer.
* @param : hrtcTimer: pointer to a RTC_HandleTypeDef structure 
* @return: none
******************************************************************************/
void HAL_RTC_SetWakeUpTimer(RTC_WUTimerTypeDef *hrtcTimer)
{
    /* Check the parameters */
    assert_param(IS_RTC_WAKEUP_CLOCK(hrtcTimer->u32_WuckSel));
    assert_param(IS_RTC_WAKEUP_COUNTER(hrtcTimer->WakeUpCounter));
    assert_param(IS_FUNCTIONAL_STATE(hrtcTimer->u32_InterruptEN));
    
    //Disable WakeUp Timer
    RTC->CR &= ~RTC_CR_WUTE;

    while(!(RTC->SR & RTC_SR_WUTWF));

    RTC->WUTR = hrtcTimer->WakeUpCounter;

    RTC->CR &= ~RTC_CR_WUCKSEL_Msk;
    RTC->CR |= hrtcTimer->u32_WuckSel;
    
    RTC->IE &= ~RTC_IE_WUTIE_Msk;
    if(hrtcTimer->u32_InterruptEN == ENABLE)
    {
        RTC->IE |= RTC_IE_WUTIE;
    }

    //Enable Wakeup Timer
    RTC->CR |= RTC_CR_WUTE;
    while(!(RTC->SR & RTC_SR_WUTWF));

}

/******************************************************************************
* @brief:  Writes a data in a specified RTC Backup data register.
* @param:  RTC_BKP_DR: RTC Backup data Register number.
*          This parameter can be: RTC_BKP_DRx where x can be from 0 to 15 to 
*          specify the register.
* @param:  Data: Data to be written in the specified RTC Backup data register.                     
* @return: None
******************************************************************************/
void HAL_RTC_WriteBackupRegister(uint32_t RTC_BKP_DR, uint32_t Data)
{
    /* Check the parameters */
    assert_param(IS_RTC_BKP(RTC_BKP_DR));
    RTC->BAKUP[RTC_BKP_DR] = Data;
}

/******************************************************************************
* @brief:  Reads data from the specified RTC Backup data Register.
* @param:  RTC_BKP_DR: RTC Backup data Register number.
*          This parameter can be: RTC_BKP_DRx where x can be from 0 to 15 to 
*          specify the register.                   
* @return: Read value
******************************************************************************/
uint32_t HAL_RTC_ReadBackupRegister(uint32_t RTC_BKP_DR)
{
    uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_RTC_BKP(RTC_BKP_DR));

    tmp = RTC->BAKUP[RTC_BKP_DR];

    /* Read the specified register */
    return tmp;
}


/******************************************************************************
* @brief:  Enables or disables the specified RTC interrupts.
* @param:  RTC_IT: specifies the RTC interrupt sources to be enabled or disabled. 
* @param:  NewState: new state of the specified RTC interrupts.
*          This parameter can be: ENABLE or DISABLE.
* @return: None
******************************************************************************/
void HAL_RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RTC_IT_FLAG(RTC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the RTC_IT Interrupt in the RTC_IE */
        RTC->IE |= RTC_IT ;
    }
    else
    {
        /* Disable the RTC_IT Interrupt in the RTC_IE */
        RTC->IE &= (~RTC_IT);
    }
}

/******************************************************************************
* @brief:  Checks whether the specified RTC flag is set or not.
* @param:  RTC_FLAG: specifies the flag to check.
* @return: The new state of RTC_FLAG (SET or RESET).
******************************************************************************/
FlagStatus HAL_RTC_GetFlagStatus(uint32_t RTC_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_RTC_IT_FLAG(RTC_FLAG));

    /* Return the status of the flag */
    if ((RTC->SR & RTC_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/******************************************************************************
* @brief:  Clears the RTC's pending flags.
* @param:  RTC_FLAG: specifies the RTC flag to clear.
* @return: None
******************************************************************************/
void HAL_RTC_ClearFlag(uint32_t RTC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_RTC_IT_FLAG(RTC_FLAG));

    /* Clear the Flags in the RTC_ISR register */
    RTC->SR = RTC_FLAG;  
}

/******************************************************************************
* @brief:  Checks whether the specified RTC interrupt has occurred or not.
* @param:  RTC_IT: specifies the RTC interrupt source to check.
* @return: The new state of RTC_IT (SET or RESET).
******************************************************************************/
ITStatus HAL_RTC_GetITStatus(uint32_t RTC_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_RTC_IT_FLAG(RTC_IT));

    /* Get the status of the Interrupt */
    if (((RTC->IE & RTC_IT) != (uint32_t)RESET) && ((RTC->SR & RTC_IT) != (uint32_t)RESET))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/******************************************************************************
* @brief:  Clears the RTC's interrupt pending bits.
* @param:  RTC_IT: specifies the RTC interrupt pending bit to clear.
* @return: none
******************************************************************************/
void HAL_RTC_ClearITPendingBit(uint32_t RTC_IT)
{
    /* Check the parameters */
    assert_param(IS_RTC_IT_FLAG(RTC_IT));
    
    if((RTC->IE & RTC_IT)!= RESET)
    {
        /* Clear the interrupt pending bits in the RTC_SR register */
        RTC->SR = RTC_IT;
    } 
}


#endif




