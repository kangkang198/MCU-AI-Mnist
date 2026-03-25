/******************************************************************************
* @file      : HAL_FMC.c
* @version   : 1.0
* @date      : 2022.10.25
* @brief     : FMC HAL module driver
*   
* @history   :	
*   2022.10.25    lwq    create
*   
******************************************************************************/
#include "hal.h"

#ifdef HAL_FMC_MODULE_ENABLED

/******************************************************************************
* @brief : Initialize the FMC NORSRAM MSP.
* @param : none.
* @return: none
******************************************************************************/
__weak void HAL_FMC_NORSRAM_MspInit(void)
{
    
    /* Prevent unused argument(s) compilation warning */

    /* NOTE: This function Should not be modified, when the callback is needed,
    the HAL_FMC_NORSRAM_MspInit could be implemented in the user file
    */ 
}


/******************************************************************************
* @brief : Initialize the FMC NORSRAM peripheral.
* @param : hfmc: Pointer to a FMC_NORSRAMInitTypeDef structure that contains
*                the configuration information for the specified FMC module.
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NORSRAM_Init(FMC_NORSRAMInitTypeDef *hfmc)
{ 
    /* Check the parameters */
    assert_param(IS_FMC_NORSRAM_BANK(hfmc->NSBank));
    assert_param(IS_FMC_MUX(hfmc->DataAddressMux));
    assert_param(IS_FMC_MEMORY(hfmc->MemoryType));
    assert_param(IS_FMC_MEMORY_WIDTH(hfmc->MemoryDataWidth));
    assert_param(IS_FMC_BURSTMODE(hfmc->BurstAccessMode));
    assert_param(IS_FMC_WAIT_POLARITY(hfmc->WaitSignalPolarity));
    assert_param(IS_FMC_WRAP_MODE(hfmc->WrapMode));
    assert_param(IS_FMC_WAIT_SIGNAL_ACTIVE(hfmc->WaitSignalActive));
    assert_param(IS_FMC_WRITE_OPERATION(hfmc->WriteOperation));
    assert_param(IS_FMC_WAITE_SIGNAL(hfmc->WaitSignal));
    assert_param(IS_FMC_ASYNWAIT(hfmc->AsynchronousWait));
    assert_param(IS_FMC_CRAMPPAGE_SIZE(hfmc->CRAMPageSize));
    assert_param(IS_FMC_WRITE_MODE(hfmc->WriteMode));  


    /* Enable FMC clock */
    __HAL_RCC_FMC_CLK_ENABLE();

    /* Initialize the low level hardware (MSP) */
    HAL_FMC_NORSRAM_MspInit();    

    /*---------------------------- FMC SNCTL Configuration -----------------*/
    /* Clear NRBKEN, NRMUX, NRTP, NRW, NREN, SBRSTEN, NRWTPOL, WRAPEN, NRWTCFG, WREN,
            NWAITEN, EXTMODEN, ASYNCWAIT, CPS and SYNCWR bits */
    FMC_NORSRAM->SNCTLCFG[hfmc->NSBank] &= ((uint32_t)~( FMC_SNCTLX_NRBKEN_Msk | FMC_SNCTLX_NRMUX_Msk | FMC_SNCTLX_NRTP_Msk | \
                                                            FMC_SNCTLX_NRW_Msk | FMC_SNCTLX_NREN_Msk | FMC_SNCTLX_SBRSTEN_Msk | \
                                                            FMC_SNCTLX_NRWTPOL_Msk | FMC_SNCTLX_WRAPEN_Msk | FMC_SNCTLX_NRWTCFG_Msk | \
                                                            FMC_SNCTLX_WREN_Msk | FMC_SNCTLX_NRWTEN_Msk | FMC_SNCTLX_EXMODEN_Msk | \
                                                            FMC_SNCTLX_ASYNCWAIT_Msk | FMC_SNCTLX_CPS_Msk | FMC_SNCTLX_SYNCWR_Msk));

    /* Bank1 NOR/SRAM control register configuration */ 
    FMC_NORSRAM->SNCTLCFG[hfmc->NSBank] |= (uint32_t)(hfmc->DataAddressMux | \
                                                        hfmc->MemoryType | \
                                                        hfmc->MemoryDataWidth | \
                                                        hfmc->BurstAccessMode | \
                                                        hfmc->WaitSignalPolarity | \
                                                        hfmc->WrapMode | \
                                                        hfmc->WaitSignalActive | \
                                                        hfmc->WriteOperation | \
                                                        hfmc->WaitSignal | \
                                                        hfmc->ExtendedMode | \
                                                        hfmc->AsynchronousWait | \
                                                        hfmc->CRAMPageSize | \
                                                        hfmc->WriteMode);



    if(hfmc->MemoryType == FMC_MEMORY_TYPE_NOR)
    {
        FMC_NORSRAM->SNCTLCFG[hfmc->NSBank] |= (uint32_t)FMC_NORSRAM_FLASH_ACCESS_ENABLE;
    }
    
    FMC_NORSRAM->SNCTLCFG[hfmc->NSBank] |= FMC_SNCTLX_NRBKEN; 

    return HAL_OK;
}


/******************************************************************************
* @brief : DeInitialize the FMC_NORSRAM peripheral 
* @param : hfmc: Pointer to a FMC_NORSRAMInitTypeDef structure that contains
*                the configuration information for the specified FMC module.
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NORSRAM_DeInit(FMC_NORSRAMInitTypeDef *hfmc)
{
    /* Check the parameters */
    assert_param(IS_FMC_NORSRAM_BANK(hfmc->NSBank));

    /* De-initialize the FMC_NORSRAM device */
    FMC_NORSRAM->SNCTLCFG[hfmc->NSBank] = 0x000030DAU;
    
    FMC_NORSRAM->SNCTLCFG[hfmc->NSBank+1] = 0x0FFFFFFFU;
                                                
    FMC_NORSRAM->SNWTCFG[hfmc->NSBank] = 0x0FFFFFFFU;

    return HAL_OK;
}


/******************************************************************************
* @brief : Initialize the FMC_NORSRAM Timing according to the specified
*          parameters in the FMC_NORSRAM_TimingTypeDef
* @param : Timing Pointer to NORSRAM Timing structure
* @param : Bank NORSRAM bank number  
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NORSRAM_Timing_Init(FMC_NORSRAMTimingInitTypeDef *Timing, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
    assert_param(IS_FMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
    assert_param(IS_FMC_DATASETUP_TIME(Timing->DataSetupTime));
    assert_param(IS_FMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
    assert_param(IS_FMC_CLK_DIV(Timing->CLKDivision));
    assert_param(IS_FMC_DATA_LATENCY(Timing->DataLatency));
    assert_param(IS_FMC_ACCESS_MODE(Timing->AccessMode));
    assert_param(IS_FMC_NORSRAM_BANK(Bank));    
    
    /*---------------------------- FMC SNTCFG Configuration -----------------*/
    /* Clear ASET, AHLD, DSET, BUSLAT, CKDIV, DLAT and ASYNCMO bits */
    FMC_NORSRAM->SNCTLCFG[Bank+1] &= ((uint32_t)~(FMC_SNTCFGX_ASET_Msk | FMC_SNTCFGX_AHLD_Msk | FMC_SNTCFGX_DSET_Msk | \
                                                    FMC_SNTCFGX_BUSLAT_Msk | FMC_SNTCFGX_CKDIV_Msk | FMC_SNTCFGX_DLAT_Msk | \
                                                    FMC_SNTCFGX_ASYNCMOD_Msk));

    /* Bank1 NOR/SRAM timing register configuration */
    FMC_NORSRAM->SNCTLCFG[Bank+1] |= (uint32_t)Timing->AddressSetupTime | \
                                        (Timing->AddressHoldTime << FMC_SNTCFGX_AHLD_Pos) | \
                                        (Timing->DataSetupTime << FMC_SNTCFGX_DSET_Pos) | \
                                        (Timing->BusTurnAroundDuration << FMC_SNTCFGX_BUSLAT_Pos) | \
                                        (Timing->CLKDivision << FMC_SNTCFGX_CKDIV_Pos) | \
                                        (Timing->DataLatency << FMC_SNTCFGX_DLAT_Pos) | \
                                        Timing->AccessMode;

    return HAL_OK;
}

/******************************************************************************
* @brief : Initialize the FMC_NORSRAM Extended mode Timing according to the specified
*          parameters in the FMC_NORSRAM_TimingTypeDef
* @param : Timing Pointer to NORSRAM Timing structure
* @param : Bank NORSRAM bank number  
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_NORSRAM_Extended_Timing_Init(FMC_NORSRAMTimingInitTypeDef *Timing, uint32_t Bank, uint32_t ExtendedMode)
{
    /* Check the parameters */
    assert_param(IS_FMC_NORSRAM_BANK(Bank));
    assert_param(IS_FMC_EXTENDED_MODE(ExtendedMode));
    /*---------------------------- FMC SNWTCFG Configuration -----------------*/
    /* Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
    if(ExtendedMode == FMC_EXTENDED_MODE_ENABLE)
    {
        assert_param(IS_FMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
        assert_param(IS_FMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
        assert_param(IS_FMC_DATASETUP_TIME(Timing->DataSetupTime));
        assert_param(IS_FMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
        assert_param(IS_FMC_DATA_LATENCY(Timing->DataLatency));
        assert_param(IS_FMC_ACCESS_MODE(Timing->AccessMode));

        /* Clear WASET, WAHLD, WDSET, WBUSLAT, DLAT, and WASYNCMOD bits */
        FMC_NORSRAM->SNWTCFG[Bank] &= ((uint32_t)~(FMC_SNWTCFGX_WASET_Msk | FMC_SNWTCFGX_WAHLD_Msk | FMC_SNWTCFGX_WDSET_Msk | \
                                                    FMC_SNWTCFGX_WBUSLAT_Msk | FMC_SNWTCFGX_DLAT_Msk | FMC_SNWTCFGX_WASYNCMOD_Msk));

        FMC_NORSRAM->SNWTCFG[Bank] |= (uint32_t)Timing->AddressSetupTime |
                                        (Timing->AddressHoldTime << FMC_SNWTCFGX_WAHLD_Pos )|
                                        (Timing->DataSetupTime << FMC_SNWTCFGX_WDSET_Pos) |
                                        (Timing->BusTurnAroundDuration << FMC_SNWTCFGX_WBUSLAT_Pos) |
                                        (Timing->DataLatency << FMC_SNWTCFGX_DLAT_Pos) |
                                        Timing->AccessMode;

    }
    else
    {
        FMC_NORSRAM->SNWTCFG[Bank] = 0x0FFFFFFF;
    }
    return HAL_OK;
}

/******************************************************************************
* @brief : Initialize the FMC SDRAM MSP.
* @param : none.
* @return: none
******************************************************************************/
__weak void HAL_FMC_SDRAM_MspInit(void)
{
    
    /* Prevent unused argument(s) compilation warning */

    /* NOTE: This function Should not be modified, when the callback is needed,
    the HAL_FMC_SDRAM_MspInit could be implemented in the user file
    */ 
}

/******************************************************************************
* @brief : Initializes the FMC_SDRAM device according to the specified 
*          control parameters in the FMC_SDRAMInitTypeDef
* @param : Init: Pointer to SDRAM Initialization structure  
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_SDRAM_Init(FMC_SDRAMInitTypeDef *Init)
{
    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_BANK(Init->SDBank));
    assert_param(IS_FMC_COLUMNBITS_NUMBER(Init->ColumnBitsNumber));
    assert_param(IS_FMC_ROWBITS_NUMBER(Init->RowBitsNumber));
    assert_param(IS_FMC_SDMEMORY_WIDTH(Init->MemoryDataWidth));  
    assert_param(IS_FMC_INTERNALBANK_NUMBER(Init->InternalBankNumber));
    assert_param(IS_FMC_CAS_LATENCY(Init->CASLatency));
    assert_param(IS_FMC_WRITE_PROTECTION(Init->WriteProtection));
    assert_param(IS_FMC_SDCLOCK_PERIOD(Init->SDClockPeriod));
    assert_param(IS_FMC_READ_BURST(Init->ReadBurst));
    assert_param(IS_FMC_READPIPE_DELAY(Init->ReadPipeDelay));   

    /* Enable FMC clock */
    __HAL_RCC_FMC_CLK_ENABLE();

    /* Initialize the low level hardware (MSP) */
    HAL_FMC_SDRAM_MspInit();
    /* Set SDRAM bank configuration parameters */
    if (Init->SDBank != FMC_SDRAM_BANK2) 
    {
        /* Clear NC, NR, MWID, NB, CAS, WP, SDCLK, RBURST, and RPIPE bits */
        FMC_SDRAM->SDRCR[FMC_SDRAM_BANK1] &= ((uint32_t)~(FMC_SDRCR_NCA_Msk  | FMC_SDRCR_NRA_Msk | FMC_SDRCR_MWID_Msk | \
                                                            FMC_SDRCR_NB_Msk  | FMC_SDRCR_CAS_Msk | FMC_SDRCR_WP_Msk   | \
                                                            FMC_SDRCR_CLKDIV_Msk | FMC_SDRCR_RBURST_Msk | FMC_SDRCR_RPIPE_Msk));

        FMC_SDRAM->SDRCR[FMC_SDRAM_BANK1] |= (uint32_t)(Init->ColumnBitsNumber   |\
                                                            Init->RowBitsNumber      |\
                                                            Init->MemoryDataWidth    |\
                                                            Init->InternalBankNumber |\
                                                            Init->CASLatency         |\
                                                            Init->WriteProtection    |\
                                                            Init->SDClockPeriod      |\
                                                            Init->ReadBurst          |\
                                                            Init->ReadPipeDelay
        );                                      
    }
    else /* FMC_Bank2_SDRAM */                      
    {
        /* Clear SDCLK, RBURST, and RPIPE bits */
        FMC_SDRAM->SDRCR[FMC_SDRAM_BANK1] &= ((uint32_t)~(FMC_SDRCR_CLKDIV_Msk | FMC_SDRCR_RBURST_Msk | FMC_SDRCR_RPIPE_Msk));

        FMC_SDRAM->SDRCR[FMC_SDRAM_BANK1] |= (uint32_t)(Init->SDClockPeriod      |\
                                                Init->ReadBurst          |\
                                                Init->ReadPipeDelay);

        /* Clear NC, NR, MWID, NB, CAS, WP, SDCLK, RBURST, and RPIPE bits */
        FMC_SDRAM->SDRCR[FMC_SDRAM_BANK2] &= ((uint32_t)~(FMC_SDRCR_NCA_Msk  | FMC_SDRCR_NRA_Msk | FMC_SDRCR_MWID_Msk | \
                                                            FMC_SDRCR_NB_Msk  | FMC_SDRCR_CAS_Msk | FMC_SDRCR_WP_Msk   | \
                                                            FMC_SDRCR_CLKDIV_Msk | FMC_SDRCR_RBURST_Msk | FMC_SDRCR_RPIPE_Msk));

        FMC_SDRAM->SDRCR[FMC_SDRAM_BANK2] |= (uint32_t)(Init->ColumnBitsNumber   |\
                                                            Init->RowBitsNumber       |\
                                                            Init->MemoryDataWidth     |\
                                                            Init->InternalBankNumber  |\
                                                            Init->CASLatency          |\
                                                            Init->WriteProtection);
    }
  
    return HAL_OK;
}



/******************************************************************************
* @brief : Initializes the FMC_SDRAM device timing according to the specified 
*          parameters in the FMC_SDRAMTimingInitTypeDef
* @param : Timing: Pointer to SDRAM Timing structure  
* @param : Bank: SDRAM bank number
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_SDRAM_Timing_Init(FMC_SDRAMTimingInitTypeDef *Timing, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_LOADTOACTIVE_DELAY(Timing->LoadToActiveDelay));
    assert_param(IS_FMC_EXITSELFREFRESH_DELAY(Timing->ExitSelfRefreshDelay));
    assert_param(IS_FMC_SELFREFRESH_TIME(Timing->SelfRefreshTime));
    assert_param(IS_FMC_ROWCYCLE_DELAY(Timing->RowCycleDelay));
    assert_param(IS_FMC_WRITE_RECOVERY_TIME(Timing->WriteRecoveryTime));
    assert_param(IS_FMC_RP_DELAY(Timing->RPDelay));
    assert_param(IS_FMC_RCD_DELAY(Timing->RCDDelay));
    assert_param(IS_FMC_SDRAM_BANK(Bank));

    /* Set SDRAM device timing parameters */ 
    if (Bank != FMC_SDRAM_BANK2) 
    {
        /* Clear TMRD, TXSR, TRAS, TRC, TWR, TRP and TRCD bits */
        FMC_SDRAM->SDRTR[FMC_SDRAM_BANK1] &= ((uint32_t)~(FMC_SDRTR_TMRD_Msk  | FMC_SDRTR_TXSR_Msk | FMC_SDRTR_TRAS_Msk | \
                                                FMC_SDRTR_TRC_Msk  | FMC_SDRTR_TWR_Msk | FMC_SDRTR_TRP_Msk | \
                                                FMC_SDRTR_TRCD_Msk));

        FMC_SDRAM->SDRTR[FMC_SDRAM_BANK1] |= (uint32_t)(((Timing->LoadToActiveDelay)-1)       |\
                                                        (((Timing->ExitSelfRefreshDelay)-1) << 4) |\
                                                        (((Timing->SelfRefreshTime)-1) << 8)      |\
                                                        (((Timing->RowCycleDelay)-1) << 12)       |\
                                                        (((Timing->WriteRecoveryTime)-1) <<16)    |\
                                                        (((Timing->RPDelay)-1) << 20)             |\
                                                        (((Timing->RCDDelay)-1) << 24));
    }
    else /* FMC_Bank2_SDRAM */
    {
        /* Clear TRC and TRP bits */
        FMC_SDRAM->SDRTR[FMC_SDRAM_BANK1] &= ((uint32_t)~(FMC_SDRTR_TRC_Msk | FMC_SDRTR_TRP_Msk));

        FMC_SDRAM->SDRTR[FMC_SDRAM_BANK1] |= (uint32_t)((((Timing->RowCycleDelay)-1) << 12)   |\
                                                (((Timing->RPDelay)-1) << 20)); 

        /* Clear TMRD, TXSR, TRAS, TRC, TWR, TRP and TRCD bits */
        FMC_SDRAM->SDRTR[FMC_SDRAM_BANK2] &= ((uint32_t)~(FMC_SDRTR_TMRD_Msk  | FMC_SDRTR_TXSR_Msk | FMC_SDRTR_TRAS_Msk | \
                                                            FMC_SDRTR_TRC_Msk  | FMC_SDRTR_TWR_Msk | FMC_SDRTR_TRP_Msk | \
                                                            FMC_SDRTR_TRCD_Msk));

        FMC_SDRAM->SDRTR[FMC_SDRAM_BANK2] |= (uint32_t)(((Timing->LoadToActiveDelay)-1)           |\
                                                        (((Timing->ExitSelfRefreshDelay)-1) << 4)  |\
                                                        (((Timing->SelfRefreshTime)-1) << 8)       |\
                                                        (((Timing->WriteRecoveryTime)-1) <<16)     |\
                                                        (((Timing->RCDDelay)-1) << 24));   
    }

    return HAL_OK;
}

/******************************************************************************
* @brief : DeInitializes the FMC_SDRAM peripheral 
* @param : Bank: SDRAM bank number
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_SDRAM_DeInit(uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_BANK(Bank));

    /* De-initialize the SDRAM device */
    FMC_SDRAM->SDRCR[Bank] = 0x000002D0;
    FMC_SDRAM->SDRTR[Bank] = 0x0FFFFFFF;    
    FMC_SDRAM->SDRCMD      = 0x00000000;
    FMC_SDRAM->SDRART      = 0x00000000;
    FMC_SDRAM->SDRSR       = 0x00000000;

    return HAL_OK;
}


/******************************************************************************
* @brief : Send Command to the FMC SDRAM bank
* @param : Command: Pointer to SDRAM command structure   
* @param : Timing: Pointer to SDRAM Timing structure
* @param : Timeout: Timeout wait value
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_SDRAM_SendCommand(FMC_SDRAMCommandTypeDef *Command, uint32_t Timeout)
{
    __IO uint32_t uiTimeout;

    /* Check the parameters */
    assert_param(IS_FMC_COMMAND_MODE(Command->CommandMode));
    assert_param(IS_FMC_COMMAND_TARGET(Command->CommandTarget));
    assert_param(IS_FMC_AUTOREFRESH_NUMBER(Command->AutoRefreshNumber));
    assert_param(IS_FMC_MODE_REGISTER(Command->ModeRegisterDefinition));  

    /* Clear CMD, CTD2, CTD1, NARF, MRD bits */
    FMC_SDRAM->SDRCMD &= ((uint32_t)~(FMC_SDRCMD_CMD_Msk  | FMC_SDRCMD_CTD2_Msk | FMC_SDRCMD_CTD1_Msk | \
                                        FMC_SDRCMD_NARF_Msk  | FMC_SDRCMD_MRD_Msk));
    /* Set command register */
    FMC_SDRAM->SDRCMD = (uint32_t)(Command->CommandMode         |\
            (Command->CommandTarget)                |\
            (((Command->AutoRefreshNumber)-1) << FMC_SDRCMD_NARF_Pos) |\
            ((Command->ModeRegisterDefinition) << FMC_SDRCMD_MRD_Pos)
            );

    uiTimeout = Timeout;

    /* wait until command is send */
    while(HAL_IS_BIT_SET(FMC_SDRAM->SDRSR, FMC_SDRSR_BUSY))
    {
        /* Check for the Timeout */
        if(uiTimeout)
        {
            uiTimeout--;
            if (uiTimeout == 0)
            {
                return HAL_TIMEOUT;             
            }
        }    
    }

    return HAL_OK;  
}

/******************************************************************************
* @brief : Program the SDRAM Memory Refresh rate.
* @param : RefreshRate: The SDRAM refresh rate value.       
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_SDRAM_ProgramRefreshRate(uint32_t RefreshRate)
{
    /* Check the parameters */
    assert_param(IS_FMC_REFRESH_RATE(RefreshRate));
    
    /* Clear COUNT bits */
    FMC_SDRAM->SDRART &= (uint32_t)~(FMC_SDRART_COUNT_Msk);
    /* Set the refresh rate in command register */
    FMC_SDRAM->SDRART |= (RefreshRate << FMC_SDRART_COUNT_Pos);

    return HAL_OK;   
}

/******************************************************************************
* @brief : Set the Number of consecutive SDRAM Memory auto Refresh commands. 
* @param : AutoRefreshNumber: Specifies the auto Refresh number.       
* @return: HAL status
******************************************************************************/
HAL_StatusTypeDef HAL_FMC_SDRAM_SetAutoRefreshNumber(uint32_t AutoRefreshNumber)
{
    /* Check the parameters */
    assert_param(IS_FMC_AUTOREFRESH_NUMBER(AutoRefreshNumber));
    
    /* Clear NARF bits */
    FMC_SDRAM->SDRCMD &= (uint32_t)~(FMC_SDRCMD_NARF_Msk);
    /* Set the Auto-refresh number in command register */
    FMC_SDRAM->SDRCMD |= (AutoRefreshNumber << FMC_SDRCMD_NARF_Pos); 

    return HAL_OK;  
}

/******************************************************************************
* @brief : Returns the indicated FMC SDRAM bank mode status.
* @param : Bank: Defines the FMC SDRAM bank. This parameter can be 
*          FMC_SDRAM_BANK1 or FMC_SDRAM_BANK2. 
* @return: The FMC SDRAM bank mode status, could be on of the following values:
*          FMC_SDRAM_NORMAL_MODE, FMC_SDRAM_SELF_REFRESH_MODE or 
*          FMC_SDRAM_POWER_DOWN_MODE.           
******************************************************************************/
uint32_t HAL_FMC_SDRAM_GetBankModeStatus(uint32_t Bank)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_BANK(Bank));

    /* Get the corresponding bank mode */
    if(Bank == FMC_SDRAM_BANK1)
    {
        tmpreg = (uint32_t)((FMC_SDRAM->SDRSR & FMC_SDRSR_STA1_Msk) >> FMC_SDRSR_STA1_Pos); 
    }
    else
    {
        tmpreg = ((uint32_t)(FMC_SDRAM->SDRSR & FMC_SDRSR_STA2_Msk) >> FMC_SDRSR_STA2_Pos);
    }

    /* Return the mode status */
    return tmpreg;
}

/******************************************************************************
* @brief : Returns the indicated FMC SDRAM status.
* @param : None. 
* @return: The FMC SDRAM status.           
******************************************************************************/
uint32_t HAL_FMC_SDRAM_GetStatus(void)
{
    /* Return the mode status */
    return (FMC_SDRAM->SDRSR);
}

/******************************************************************************
* @brief : Set Burst read FIFO length.
* @param : FifoLen: fifo length.
* @param : Bank: Defines the FMC SDRAM bank. This parameter can be 
*          FMC_SDRAM_BANK1 or FMC_SDRAM_BANK2.
* @return: None.           
******************************************************************************/
void HAL_FMC_SDRAM_BurstReadFifoLength(uint32_t FifoLen, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_BURST_READ_FIFO_LEN(FifoLen));
    assert_param(IS_FMC_SDRAM_BANK(Bank));
    
    if(FifoLen == FMC_SDRAM_BURST_READ_FIFO_LEN_0)
    {
        FMC_SDRAM->SDRCR[Bank] &= ~(FMC_SDRCR_RBURST);
    }
    else
    {
        FMC_SDRAM->SDRCR[Bank] |= (FMC_SDRCR_RBURST);
        FMC_SDRAM->SDRCR[Bank] &= ~(FMC_SDRCR_BDEPTH_Msk);
        FMC_SDRAM->SDRCR[Bank] |= FifoLen;
    }        
}

/******************************************************************************
* @brief : Set write to read continuous operation with SDCLK delay.
* @param : W2RDelay: Number of delayed SDCLK.This parameter can be 
*          FMC_SDRAM_W2R_DELAY_0 or FMC_SDRAM_W2R_DELAY_HALF_SDCLK.
* @param : Bank: Defines the FMC SDRAM bank. This parameter can be 
*          FMC_SDRAM_BANK1 or FMC_SDRAM_BANK2.
* @return: None.           
******************************************************************************/
void HAL_FMC_SDRAM_W2RDelay(uint32_t W2RDelay, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_W2R_DELAY(W2RDelay));
    assert_param(IS_FMC_SDRAM_BANK(Bank));
    
    FMC_SDRAM->SDRCR[Bank] &= ~(FMC_SDRCR_W2RDLY_Msk);
    FMC_SDRAM->SDRCR[Bank] |= W2RDelay;    
}

/******************************************************************************
* @brief : Enable or disable the SDRAM device refresh error interrupt.
* @param : NewState: new state of the specified SDRAM interrupts.
*          This parameter can be: ENABLE or DISABLE.
* @return: None.           
******************************************************************************/
void HAL_FMC_SDRAM_ITConfig(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the refresh error interrupt */
        FMC_SDRAM->SDRART |= FMC_SDRART_RFEIE ;
    }
    else
    {
        /* Disable the refresh error interrupt */
        FMC_SDRAM->SDRART &= (~FMC_SDRART_RFEIE);
    }
} 

/******************************************************************************
* @brief:  Checks whether the specified SDRAM interrupt has occurred or not.
* @param:  None.
* @return: SET or RESET.
******************************************************************************/
FlagStatus HAL_FMC_SDRAM_GetITStatus(void)
{
    FlagStatus bitstatus = RESET;

    /* Return the status of the flag */
    if (((FMC_SDRAM->SDRART & FMC_SDRART_RFEIE) != (uint32_t)RESET) && ((FMC_SDRAM->SDRSR & FMC_SDRSR_RFE) != (uint32_t)RESET))
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
* @brief:  Clears the SDRAM's interrupt pending bits.
* @param:  None.
* @return: None
******************************************************************************/
void HAL_FMC_SDRAM_ClearITPendingBit(void)
{
    if((FMC_SDRAM->SDRART & FMC_SDRART_RFEIE) != (uint32_t)RESET)
    {
        /* Clear the interrupt pending bits in the SDRART register */
        FMC_SDRAM->SDRART |= FMC_SDRART_CRFE;
    } 
}


/******************************************************************************
* @brief:  SDRAM Refresh error callback.
* @param:  None.
* @return: None
******************************************************************************/
__weak void HAL_SDRAM_RefreshErrorCallback(void)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(NULL);

    /* NOTE: This function Should not be modified, when the callback is needed,
            the HAL_SDRAM_RefreshErrorCallback could be implemented in the user file
    */
}

/******************************************************************************
* @brief:  This function handles SDRAM refresh error interrupt request.
* @param:  None.
* @return: None
******************************************************************************/
__weak void HAL_SDRAM_IRQHandler(void)
{
    /* Check SDRAM interrupt Rising edge flag */
    if (SET == HAL_FMC_SDRAM_GetITStatus())
    {
        /* SDRAM refresh error interrupt callback */
        HAL_SDRAM_RefreshErrorCallback();
        /* Clear SDRAM refresh error interrupt pending bit */
        HAL_FMC_SDRAM_ClearITPendingBit();
    }
}


#endif



