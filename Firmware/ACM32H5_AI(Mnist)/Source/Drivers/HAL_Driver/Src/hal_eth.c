/******************************************************************************
*@file  : hal_eth.c
*@brief : ETH HAL module driver.
******************************************************************************/
#include "math.h"
#include "hal.h"

#ifdef HAL_ETH_MODULE_ENABLED

static HAL_StatusTypeDef HAL_ETH_DMATxDescListInit(ETH_HandleTypeDef *heth);
static HAL_StatusTypeDef HAL_ETH_DMARxDescListInit(ETH_HandleTypeDef *heth);

HAL_StatusTypeDef HAL_ETH_TestDelay(void);
HAL_StatusTypeDef HAL_ETH_Init(ETH_HandleTypeDef *heth)
{
	uint32_t tempreg;
	uint32_t timeout;

	assert_param(heth);
    
	if (heth->State == HAL_ETH_STATE_RESET)
    {
        HAL_ETH_MspInit(heth);
    }
    
    heth->State = HAL_ETH_STATE_BUSY;
    
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    
	// Media接口选择
    if (heth->Init.MediaInterface == ETH_MEDIA_INTERFACE_MII)
        SYSCFG->SYSCR &= ~SYSCFG_SYSCR_EPIS;
    else if (heth->Init.MediaInterface == ETH_MEDIA_INTERFACE_RMII)
        SYSCFG->SYSCR = (SYSCFG->SYSCR & ~SYSCFG_SYSCR_EPIS) | SYSCFG_SYSCR_EPIS_2;
    else
        return HAL_ERROR;
	
    SET_BIT(heth->Instance->DMABMR, ETH_DMABMR_SWR);
    timeout = ETH_TIMEOUT_SWRESET;
    while (READ_BIT(heth->Instance->DMABMR, ETH_DMABMR_SWR) != (uint32_t)RESET)
	{
		if(--timeout == 0)
		{
            heth->ErrorCode = HAL_ETH_ERROR_TIMEOUT;
			heth->State= HAL_ETH_STATE_ERROR;
			return HAL_ERROR;
		}
	}
	
    HAL_ETH_RxClockDelayConfig(heth, heth->Init.Delay.Uint, heth->Init.Delay.Len);
    
    if (HAL_ETH_SetMACAddrConfig(heth) != HAL_OK)
        return HAL_ERROR;
    if (HAL_ETH_SetSpeedConfig(heth) != HAL_OK)
        return HAL_ERROR;
    if (HAL_ETH_SetDuplexModeConfig(heth) != HAL_OK)
        return HAL_ERROR;
    
	// 配置SMI时钟
    if (HAL_ETH_ConfigSMI(heth) != HAL_OK)
        return HAL_ERROR;
    
    if (HAL_ETH_SetMACConfig(heth) != HAL_OK)
        return HAL_ERROR;
    if (HAL_ETH_SetDMAConfig(heth) != HAL_OK)
        return HAL_ERROR;
    if (HAL_ETH_SetAddrFilterConfig(heth) != HAL_OK)
        return HAL_ERROR;
    if (HAL_ETH_SetVLANFilterConfig(heth) != HAL_OK)
        return HAL_ERROR;
    if (HAL_ETH_SetL3L4FilterConfig(heth) != HAL_OK)
        return HAL_ERROR;
    if (HAL_ETH_SetMMCConfig(heth) != HAL_OK)
        return HAL_ERROR;
    if (HAL_ETH_SetPMTConfig(heth) != HAL_OK)
        return HAL_ERROR;
    if (HAL_ETH_SetPTPConfig(heth) != HAL_OK)
        return HAL_ERROR;
	
    /* Set Receive Buffs Len (must be a multiple of 4) */
    if ((heth->Init.RxBuffLen % 0x4U) != 0x0U)
    {
        heth->ErrorCode = HAL_ETH_ERROR_PARAM;
        heth->State = HAL_ETH_STATE_ERROR;
        return HAL_ERROR;
    }
    
    if (HAL_ETH_DMATxDescListInit(heth) != HAL_OK)
        return HAL_ERROR;
    if (HAL_ETH_DMARxDescListInit(heth) != HAL_OK)
        return HAL_ERROR;
    
    heth->ErrorCode = HAL_ETH_ERROR_NONE;
    heth->State = HAL_ETH_STATE_READY;

	return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_DeInit(ETH_HandleTypeDef *heth)
{
	heth->State = HAL_ETH_STATE_BUSY;

	HAL_ETH_MspDeInit(heth);

	heth->State= HAL_ETH_STATE_RESET;

	return HAL_OK;
}

__attribute__((weak)) void HAL_ETH_MspInit(ETH_HandleTypeDef *heth)
{
}

__attribute__((weak)) void HAL_ETH_MspDeInit(ETH_HandleTypeDef *heth)
{
}



HAL_StatusTypeDef HAL_ETH_InitDefaultParamter(ETH_HandleTypeDef *heth)
{
    memset((void *)heth, 0, sizeof(ETH_HandleTypeDef));
    
    heth->Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;
    heth->Init.AutoNegotiation = ENABLE;
    heth->Init.PhyAddress = 0;
    
    HAL_ETH_InitSpeedDefaultParamter(heth);
    
    HAL_ETH_InitDuplexModeDefaultParamter(heth);
    
    HAL_ETH_InitMACAddrDefaultParamter(heth);
    
    // 过滤
    HAL_ETH_InitFilterDefaultParamter(heth);
    
    // MMC
    HAL_ETH_InitMMCDefaultParamter(heth);
    
    // PMT
    HAL_ETH_InitPMTDefaultParamter(heth);
    
    // PTP
    HAL_ETH_InitPTPDefaultParamter(heth);
    
    // LPI
    HAL_ETH_SetLPIDefaultConfig(heth);
    
	// MAC配置默认值
    HAL_ETH_InitMACDefaultParamter(heth);
    
	// DMA配置默认值
    HAL_ETH_InitDMADefaultParamter(heth);
    
    return HAL_OK;
}
    
//	****************************************************************************
//  
//                              Speed
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_InitSpeedDefaultParamter(ETH_HandleTypeDef *heth)
{
    heth->Init.Speed = ETH_SPEED_100M;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetSpeedConfig(ETH_HandleTypeDef *heth)
{
	if ((heth->Instance)->MACCR & ETH_MACCR_FES)
        heth->Init.Speed = ETH_SPEED_100M;
    else
        heth->Init.Speed = ETH_SPEED_10M;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SetSpeedConfig(ETH_HandleTypeDef *heth)
{
    assert_param(IS_ETH_SPEED(heth->Init.Speed));
    
    if (heth->Init.Speed == ETH_SPEED_100M)
        (heth->Instance)->MACCR |= ETH_MACCR_FES;
    else
        (heth->Instance)->MACCR &= ~ETH_MACCR_FES;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SetSpeedDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitSpeedDefaultParamter(heth);
    HAL_ETH_SetSpeedConfig(heth);
    
    return HAL_OK;
}

//	****************************************************************************
//  
//                              Duplex Mode
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_InitDuplexModeDefaultParamter(ETH_HandleTypeDef *heth)
{
    heth->Init.DuplexMode = ETH_MODE_FULL_DUPLEX;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetDuplexModeConfig(ETH_HandleTypeDef *heth)
{
	if ((heth->Instance)->MACCR & ETH_MACCR_DM)
        heth->Init.DuplexMode = ETH_MODE_FULL_DUPLEX;
    else
        heth->Init.DuplexMode = ETH_MODE_HALF_DUPLEX;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SetDuplexModeConfig(ETH_HandleTypeDef *heth)
{
    assert_param(IS_ETH_SPEED(heth->Init.DuplexMode));
    
    if (heth->Init.DuplexMode != ETH_MODE_HALF_DUPLEX)
        (heth->Instance)->MACCR |= ETH_MACCR_DM;
    else
        (heth->Instance)->MACCR &= ~ETH_MACCR_DM;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SetDuplexModeDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitDuplexModeDefaultParamter(heth);
    HAL_ETH_SetDuplexModeConfig(heth);
    
    return HAL_OK;
}
  
    
//	****************************************************************************
//  
//                              MAC Address
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_InitMACAddrDefaultParamter(ETH_HandleTypeDef *heth)
{
    memset((void *)heth->Init.MACAddr, 0xffu, 6);
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetMACAddrConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    tmpreg = (heth->Instance)->MACA0HR;
    heth->Init.MACAddr[5] = (tmpreg >> 8) & 0xffu;
    heth->Init.MACAddr[4] = (tmpreg >> 0) & 0xffu;
    
    tmpreg = (heth->Instance)->MACA0LR;
    heth->Init.MACAddr[3] = (tmpreg >> 24) & 0xffu;
    heth->Init.MACAddr[2] = (tmpreg >> 16) & 0xffu;
    heth->Init.MACAddr[1] = (tmpreg >> 8) & 0xffu;
    heth->Init.MACAddr[0] = (tmpreg >> 0) & 0xffu;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SetMACAddrConfig(ETH_HandleTypeDef *heth)
{
    (heth->Instance)->MACA0HR = ETH_MACA0HR_AE | \
                                ((uint32_t)heth->Init.MACAddr[5] << 8) | \
                                ((uint32_t)heth->Init.MACAddr[4] << 0);
    
    // MACA1LR
    (heth->Instance)->MACA0LR = ((uint32_t)heth->Init.MACAddr[3] << 24) | \
                                ((uint32_t)heth->Init.MACAddr[2] << 16) | \
                                ((uint32_t)heth->Init.MACAddr[1] << 8) | \
                                ((uint32_t)heth->Init.MACAddr[0] << 0);
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SetMACAddrDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitMACAddrDefaultParamter(heth);
    HAL_ETH_SetMACAddrConfig(heth);
    
    return HAL_OK;
}
   

//	****************************************************************************
//  
//                              Interrupt
//  
//	****************************************************************************

#include "main.h"
__attribute__((weak)) void HAL_ETH_TxCpltCallback(ETH_HandleTypeDef *heth)
{
	(void)(heth);
}

__attribute__((weak)) void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
	(void)(heth);
}

__attribute__((weak)) void HAL_ETH_DMAErrorCallback(ETH_HandleTypeDef *heth)
{
	(void)(heth);
}

__attribute__((weak)) void HAL_ETH_MMCCallback(ETH_HandleTypeDef *heth)
{
	(void)(heth);
}

__attribute__((weak)) void HAL_ETH_PMTCallback(ETH_HandleTypeDef *heth)
{
	(void)(heth);
}

__attribute__((weak)) void HAL_ETH_LPISendEntryCallback(ETH_HandleTypeDef *heth)
{
	(void)(heth);
}

__attribute__((weak)) void HAL_ETH_LPISendExitCallback(ETH_HandleTypeDef *heth)
{
	(void)(heth);
}

__attribute__((weak)) void HAL_ETH_LPIRecvEntryCallback(ETH_HandleTypeDef *heth)
{
	(void)(heth);
}

__attribute__((weak)) void HAL_ETH_LPIRecvExitCallback(ETH_HandleTypeDef *heth)
{
	(void)(heth);
}

__attribute__((weak)) void HAL_ETH_WakeupCallback(ETH_HandleTypeDef *heth)
{
	(void)(heth);
}

void HAL_ETH_IRQHandler(ETH_HandleTypeDef *heth)
{
    volatile uint32_t temp;
    
	/* Frame received */
    if (ETH->DMASR & ETH_DMASR_RS)
	{
        if (ETH->DMAIER & ETH_DMAIER_RIE)
        {
            HAL_ETH_RxCpltCallback(heth);

            ETH->DMASR = ETH_DMASR_RS | ETH_DMASR_NIS;
            return;
        }
	}
	
	/* Frame transmitted */
    if (ETH->DMASR & ETH_DMASR_TS)
	{
        if (ETH->DMAIER & ETH_DMAIER_TIE)
        {
			HAL_ETH_TxCpltCallback(heth);

            ETH->DMASR = ETH_DMASR_TS | ETH_DMASR_NIS;
            return;
        }
	}
    
	/* ETH DMA Error */
	if(__HAL_ETH_DMA_GET_FLAG(heth, ETH_DMASR_AIS))
	{
        if (__HAL_ETH_DMA_GET_IT(heth, ETH_DMAIER_AISE)) 
        {
            heth->ErrorCode |= HAL_ETH_ERROR_DMA;
            
            if (__HAL_ETH_DMA_GET_FLAG(heth, ETH_DMASR_FBES))
            {
                heth->DMAErrorCode = READ_BIT(heth->Instance->DMASR, (ETH_DMASR_FBES | ETH_DMASR_RPSS | ETH_DMASR_TPSS));
                
                __HAL_ETH_DMA_DISABLE_IT(heth, ETH_DMAIER_NISE | ETH_DMAIER_AISE);
                
                __HAL_ETH_DMA_CLEAR_FLAG(heth, ETH_DMASR_FBES | ETH_DMASR_RPSS | ETH_DMASR_TPSS | ETH_DMASR_AIS);
                
                heth->State = HAL_ETH_STATE_ERROR;
            }
            else
            {
            
                heth->DMAErrorCode = READ_BIT(heth->Instance->DMASR, ( ETH_DMASR_ETS | ETH_DMASR_RWTS | ETH_DMASR_RBUS | \
                                                                       ETH_DMASR_TUS | ETH_DMASR_ROS | ETH_DMASR_TJTS));
                
                __HAL_ETH_DMA_CLEAR_FLAG(heth, ETH_DMASR_ETS | ETH_DMASR_RWTS | ETH_DMASR_RBUS | ETH_DMASR_TUS | \
                                             ETH_DMASR_ROS | ETH_DMASR_TJTS | ETH_DMASR_AIS);
            }
            
			HAL_ETH_DMAErrorCallback(heth);
        }
	}
    #ifdef ETH_PMT_SUPPORT
    if (READ_BIT(heth->Instance->MACISR, ETH_MACISR_PMTS))
    {
        if (READ_BIT(heth->Instance->MACIMR, ETH_MACIMR_PIM) == 0)
        {
            temp = (heth->Instance)->MACPMTCSR;
        }
    }
    #endif
    #ifdef ETH_MMC_SUPPORT
    if (READ_BIT(heth->Instance->MMCTIR, ETH_MMCTIR_TGFIS))
    {
        if (READ_BIT(heth->Instance->MMCTIMR, ETH_MMCTIMR_TGFIM) == 0)
        {
            heth->MMCCounter.TxGoodFrame = (heth->Instance)->MMCTGFCR;
        }
    }
    if (READ_BIT(heth->Instance->MMCRIR, ETH_MMCRIR_RGUFIS))
    {
        if (READ_BIT(heth->Instance->MMCRIMR, ETH_MMCRIMR_RGUFIM) == 0)
        {
            heth->MMCCounter.RxGoodUnicast = (heth->Instance)->MMCRGUFCR;
        }
    }
    #endif
    #ifdef ETH_LPI_SUPPORT
    if (READ_BIT(heth->Instance->DMASR, ETH_DMASR_LPIS))
    {
        temp = heth->Instance->MACLPICSR;
        if (temp & ETH_MACLPICSR_TLPIEN)
        {
            HAL_ETH_LPISendEntryCallback(heth);
        }
        if (temp & ETH_MACLPICSR_TLPIEX)
        {
            HAL_ETH_LPISendExitCallback(heth);
        }
        if (temp & ETH_MACLPICSR_RLPIEN)
        {
            HAL_ETH_LPIRecvEntryCallback(heth);
        }
        if (temp & ETH_MACLPICSR_RLPIEX)
        {
            HAL_ETH_LPIRecvExitCallback(heth);
        }
    }
    #endif
    
}

void HAL_ETH_WakeupIRQHandler(ETH_HandleTypeDef *heth)
{
    volatile uint32_t temp;
    
    temp = (heth->Instance)->MACPMTCSR;
    
    /* Enable the DMA reception */
    (heth->Instance)->DMAOMR |= ETH_DMAOMR_SR;
    /* Enable the DMA transmission */
    (heth->Instance)->DMAOMR |= ETH_DMAOMR_ST;
    /* Enable the MAC transmission */
    (heth->Instance)->MACCR |= ETH_MACCR_TE;
    
    HAL_ETH_WakeupCallback(heth);
}

//	****************************************************************************
//  
//                              data transmission
//  
//	****************************************************************************

//初始化发送描述符链表
static HAL_StatusTypeDef HAL_ETH_DMATxDescListInit(ETH_HandleTypeDef *heth)
{
    uint32_t i;
    uint32_t buff;
    ETH_DMADescTypeDef *tx_desc;
    
    if (heth->Init.TxDescNbr == 0)
        return HAL_ERROR;
    
    if (heth->Init.TxBuffNbr != 0)
    {
        if (heth->Init.TxDescListMode == ETH_DESC_LIST_MODE_RING)
        {
            if (heth->Init.TxBuffNbr < (heth->Init.TxDescNbr << 1))
                return HAL_ERROR;
        }
        else
        {
            if (heth->Init.TxBuffNbr < heth->Init.TxDescNbr)
                return HAL_ERROR;
        }
    }
    
    buff = (uint32_t)heth->Init.TxBuff;
    
	/* Fill each DMATxDesc descriptor with the right values */
	for(i=0; i<heth->Init.TxDescNbr; i++)
	{
        tx_desc = heth->Init.TxDesc + i;
        
        WRITE_REG(tx_desc->DESC0, 0);
        WRITE_REG(tx_desc->DESC1, 0);
        WRITE_REG(tx_desc->DESC2, 0);
        WRITE_REG(tx_desc->DESC3, 0);
        WRITE_REG(tx_desc->DESC4, 0);
        WRITE_REG(tx_desc->DESC5, 0);
        WRITE_REG(tx_desc->DESC6, 0);
        WRITE_REG(tx_desc->DESC7, 0);
        WRITE_REG(tx_desc->Buff1, 0);
        WRITE_REG(tx_desc->Buff2, 0);
        
        if (heth->Init.TxDescListMode == ETH_DESC_LIST_MODE_RING)
        {
            if (i == (heth->Init.TxDescNbr - 1))
                SET_BIT(tx_desc->DESC0, ETH_DMA_TX_DESC0_TER);
            
            if (heth->Init.TxBuffNbr != 0)
            {
                WRITE_REG(tx_desc->Buff1, buff + (heth->Init.TxBuffLen * (i << 1)));
                WRITE_REG(tx_desc->Buff2, buff + (heth->Init.TxBuffLen * ((i << 1) + 1)));
            }
            
            if ((heth->Init.TxBuffTab != 0) && (heth->Init.TxBuffNodeNbr != 0))
            {
                heth->Init.TxBuffTab[(i << 1) + 0].Buff = (uint8_t *)tx_desc->Buff1;
                heth->Init.TxBuffTab[(i << 1) + 0].Len = 0;
                heth->Init.TxBuffTab[(i << 1) + 0].next = 0;
                heth->Init.TxBuffTab[(i << 1) + 1].Buff = (uint8_t *)tx_desc->Buff2;
                heth->Init.TxBuffTab[(i << 1) + 1].Len = 0;
                heth->Init.TxBuffTab[(i << 1) + 1].next = 0;
            }
        }
        else
        {
            SET_BIT(tx_desc->DESC0, ETH_DMA_TX_DESC0_TCH);
            
            // next desc
            if (i == (heth->Init.TxDescNbr - 1))
                WRITE_REG(tx_desc->DESC3, (uint32_t)heth->Init.TxDesc);
            else
                WRITE_REG(tx_desc->DESC3, (uint32_t)(tx_desc + 1));
            
            if (heth->Init.TxBuffNbr != 0)
                WRITE_REG(tx_desc->Buff1, buff + (heth->Init.TxBuffLen * i));
            
            WRITE_REG(tx_desc->Buff2, tx_desc->DESC3);
            
            if ((heth->Init.TxBuffTab != 0) && (heth->Init.TxBuffNodeNbr != 0))
            {
                heth->Init.TxBuffTab[i].Buff = (uint8_t *)tx_desc->Buff1;
                heth->Init.TxBuffTab[i].Len = 0;
                heth->Init.TxBuffTab[i].next = 0;
            }
        }
	}
    
    heth->TxDescList.TxDescTab = heth->Init.TxDesc;
    heth->TxDescList.CurTxDesc = 0;

	/* Set Transmit Descriptor List Address Register */
	(heth->Instance)->DMATDLAR = (uint32_t)heth->Init.TxDesc;

	return HAL_OK;
}

//初始化接收描述符链表
static HAL_StatusTypeDef HAL_ETH_DMARxDescListInit(ETH_HandleTypeDef *heth)
{
    uint32_t i;
    uint32_t buff_addr;
    ETH_DMADescTypeDef *rx_desc;

    if ((heth->Init.RxDescNbr == 0) || (heth->Init.RxBuffTab == 0))
        return HAL_ERROR;
    
    if (heth->Init.RxDescListMode == ETH_DESC_LIST_MODE_RING)
    {
        if (heth->Init.RxBuffNbr < (heth->Init.RxDescNbr << 1))
            return HAL_ERROR;
        if (heth->Init.RxBuffNodeNbr < (heth->Init.RxDescNbr << 1))
            return HAL_ERROR;
    }
    else
    {
        if (heth->Init.RxBuffNbr < heth->Init.RxDescNbr)
            return HAL_ERROR;
        if (heth->Init.RxBuffNodeNbr < heth->Init.RxDescNbr)
            return HAL_ERROR;
    }
    
    buff_addr = (uint32_t)heth->Init.RxBuff;
    
	/* Fill each DMARxDesc descriptor with the right values */
	for(i=0; i<heth->Init.RxDescNbr; i++)
	{
        rx_desc = heth->Init.RxDesc + i;
        
        WRITE_REG(rx_desc->DESC0, 0);
        WRITE_REG(rx_desc->DESC1, 0);
        WRITE_REG(rx_desc->DESC2, 0);
        WRITE_REG(rx_desc->DESC3, 0);
        WRITE_REG(rx_desc->DESC4, 0);
        WRITE_REG(rx_desc->DESC5, 0);
        WRITE_REG(rx_desc->DESC6, 0);
        WRITE_REG(rx_desc->DESC7, 0);
        WRITE_REG(rx_desc->Buff1, 0);
        WRITE_REG(rx_desc->Buff2, 0);
        
        if (heth->Int.Rx == DISABLE)
            SET_BIT(rx_desc->DESC0, ETH_DMA_RX_DESC1_DIC);
        
        if (heth->Init.RxDescListMode == ETH_DESC_LIST_MODE_RING)
        {
            if (i == (heth->Init.RxDescNbr - 1))
                SET_BIT(rx_desc->DESC1, ETH_DMA_RX_DESC1_RER);
            
            // buff len
            MODIFY_REG(rx_desc->DESC1, ETH_DMA_RX_DESC1_RBS1, (heth->Init.RxBuffLen << ETH_DMA_RX_DESC1_RBS1_Pos));
            MODIFY_REG(rx_desc->DESC1, ETH_DMA_RX_DESC1_RBS2, (heth->Init.RxBuffLen << ETH_DMA_RX_DESC1_RBS2_Pos));
            
            // rx buff
            WRITE_REG(rx_desc->DESC2, buff_addr + (heth->Init.RxBuffLen * (i << 1)));
            WRITE_REG(rx_desc->DESC3, buff_addr + (heth->Init.RxBuffLen * ((i << 1) + 1)));
            
            heth->Init.RxBuffTab[(i << 1) + 0].Buff = (uint8_t *)rx_desc->DESC2;
            heth->Init.RxBuffTab[(i << 1) + 0].Len = 0;
            heth->Init.RxBuffTab[(i << 1) + 0].next = 0;
            heth->Init.RxBuffTab[(i << 1) + 1].Buff = (uint8_t *)rx_desc->DESC3;
            heth->Init.RxBuffTab[(i << 1) + 1].Len = 0;
            heth->Init.RxBuffTab[(i << 1) + 1].next = 0;
        }
        else
        {
            SET_BIT(rx_desc->DESC1, ETH_DMA_RX_DESC1_RCH);
            
            // next desc
            if (i == (heth->Init.RxDescNbr - 1))
                WRITE_REG(rx_desc->DESC3, (uint32_t)heth->Init.RxDesc);
            else
                WRITE_REG(rx_desc->DESC3, (uint32_t)(rx_desc + 1));
            
            // buff len
            MODIFY_REG(rx_desc->DESC1, ETH_DMA_RX_DESC1_RBS1, (heth->Init.RxBuffLen << ETH_DMA_RX_DESC1_RBS1_Pos));
            
            // rx buff
            WRITE_REG(rx_desc->DESC2, buff_addr + (heth->Init.RxBuffLen * i));
            
            heth->Init.RxBuffTab[i].Buff = (uint8_t *)rx_desc->DESC2;
            heth->Init.RxBuffTab[i].Len = 0;
            heth->Init.RxBuffTab[i].next = 0;
        }
        
        WRITE_REG(rx_desc->Buff1, rx_desc->DESC2);
        WRITE_REG(rx_desc->Buff2, rx_desc->DESC3);
        
        SET_BIT(rx_desc->DESC0, ETH_DMA_RX_DESC0_OWN);
        
	}
    
    heth->RxDescList.RxDescTab = heth->Init.RxDesc;
    heth->RxDescList.CurRxDesc = 0;
    heth->RxDescList.FirstRxDesc = 0;
    heth->RxDescList.RxDescNbr = 0;
    
	/* Set Transmit Descriptor List Address Register */
	(heth->Instance)->DMARDLAR = (uint32_t)heth->Init.RxDesc;

	return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetTxBuff(ETH_HandleTypeDef *heth, ETH_BuffTypeDef **buff)
{
    uint32_t i;
    uint32_t index;
    uint32_t tx_buff_index;
    uint32_t tx_buff_next_index;
    uint32_t tx_buff_first_index;
    ETH_InitTypeDef *init;
    ETH_BuffTypeDef *tx_buff;
    ETH_TxDescListTypeDef *tx_desc_list;
    ETH_DMADescTypeDef *tx_desc;
    uint32_t timeout;

    if ((heth == NULL) || (buff == NULL))
        return HAL_ERROR;
    
    init = &heth->Init;
    
    tx_desc_list = (ETH_TxDescListTypeDef *)&heth->TxDescList;
    index = tx_desc_list->CurTxDesc;
    tx_desc = &tx_desc_list->TxDescTab[index];
    
    if (init->TxDescListMode == ETH_DESC_LIST_MODE_RING)
        *buff = &init->TxBuffTab[index << 1];
    else
        *buff = &init->TxBuffTab[index];
    tx_buff = init->TxBuffTab;
    for (i=0; i<init->TxDescNbr; i++)
    {
        if (READ_BIT(tx_desc->DESC0, ETH_DMA_TX_DESC0_OWN))
            break;
        
        if (init->TxDescListMode == ETH_DESC_LIST_MODE_RING)
        {
            tx_buff_index = index << 1;
            tx_buff_next_index = tx_buff_index;
            if (++tx_buff_next_index >= init->TxBuffNodeNbr)
                tx_buff_next_index = 0;
            
            tx_buff[tx_buff_index].Buff = (uint8_t *)tx_desc->Buff1;
            tx_buff[tx_buff_index].Len = init->TxBuffLen;
            tx_buff[tx_buff_index].next = &init->TxBuffTab[tx_buff_next_index];
        
            tx_buff_index = tx_buff_next_index;
            if (++tx_buff_next_index >= init->TxBuffNodeNbr)
                tx_buff_next_index = 0;
        
            tx_buff[tx_buff_index].Buff = (uint8_t *)tx_desc->Buff1;
            tx_buff[tx_buff_index].Len = init->TxBuffLen;
            tx_buff[tx_buff_index].next = &init->TxBuffTab[tx_buff_next_index];
        }
        else
        {
            tx_buff_index = index;
            tx_buff_next_index = tx_buff_index;
            if (++tx_buff_next_index >= init->TxBuffNodeNbr)
                tx_buff_next_index = 0;
            
            tx_buff[tx_buff_index].Buff = (uint8_t *)tx_desc->Buff1;
            tx_buff[tx_buff_index].Len = init->TxBuffLen;
            tx_buff[tx_buff_index].next = &init->TxBuffTab[tx_buff_next_index];
        }
        
        index++;
        if (index >= init->TxDescNbr)
            index = 0;
        tx_desc = &tx_desc_list->TxDescTab[index];
    }
    if (i == 0)
        *buff = 0;
    else
        tx_buff[tx_buff_index].next = 0;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_Transmit(ETH_HandleTypeDef *heth, ETH_BuffTypeDef *buff, uint32_t mode, ETH_TxStatusTypeDef *pStatus)
{
    uint32_t i;
    uint32_t len;
    uint32_t index;
    uint32_t nbr;
    uint32_t desc0;
    ETH_InitTypeDef *init;
    ETH_TxDescListTypeDef *tx_desc_list;
    ETH_DMADescTypeDef *tx_desc;
    ETH_TxConfigTypeDef *pTxConfig;
    uint32_t timeout;

    if ((heth == NULL) || (buff == NULL) || (buff->Buff == NULL) || (buff->Len == 0))
        return HAL_ERROR;
    
    init = &heth->Init;
    
    if ((mode & ETH_TX_MODE_DATA_COPY) && (init->TxBuffNbr == 0))
        return HAL_ERROR;
    
    nbr = 0;
    tx_desc_list = (ETH_TxDescListTypeDef *)&heth->TxDescList;
    index = tx_desc_list->CurTxDesc;
    tx_desc = &tx_desc_list->TxDescTab[index];
    pTxConfig = &heth->TxConfig;
    
    for (i=0; i<init->TxDescNbr; i++)
    {
        if (READ_BIT(tx_desc->DESC0, ETH_DMA_TX_DESC0_OWN))
            return HAL_BUSY;
        
//        desc0 = tx_desc->DESC0 & (ETH_DMA_TX_DESC0_TER | ETH_DMA_TX_DESC0_TCH);
        desc0 = 0;
        if (mode & (ETH_TX_MODE_WAIT_TX_COMPLETE | ETH_TX_MODE_TIMESTAMP))
        {
            SET_BIT(heth->Instance->DMAIER , ETH_DMAIER_NISE | ETH_DMAIER_TIE);
        }
            SET_BIT(desc0, ETH_DMA_TX_DESC0_IC);
        
        
        MODIFY_REG(desc0, ETH_DMA_TX_DESC0_CIC, (uint32_t)pTxConfig->AutoChecksum << ETH_DMA_TX_DESC0_CIC_Pos);
        
        if (init->TxDescListMode != ETH_DESC_LIST_MODE_RING)
            SET_BIT(desc0, ETH_DMA_TX_DESC0_TCH);
        else if (index == (init->TxDescNbr - 1))
            SET_BIT(desc0, ETH_DMA_TX_DESC0_TER);
        
        if (nbr == 0)
        {
            SET_BIT(desc0, ETH_DMA_TX_DESC0_FS);
            if (pTxConfig->AutoCRC == 0)
                SET_BIT(desc0, ETH_DMA_TX_DESC0_DC);
            if (pTxConfig->AutoPad == 0)
                SET_BIT(desc0, ETH_DMA_TX_DESC0_DP);
            if (mode & ETH_TX_MODE_TIMESTAMP)
                SET_BIT(desc0, ETH_DMA_TX_DESC0_TTSE);
        }
        WRITE_REG(tx_desc->DESC0, desc0);

        // buff1 len
        if (buff->Len > init->TxBuffLen)
            len = init->TxBuffLen;
        else
            len = buff->Len;
        buff->Len -= len;
        WRITE_REG(tx_desc->DESC1, len  << ETH_DMA_TX_DESC1_TBS1_Pos);
        
        // buffer 1
        if (mode & ETH_TX_MODE_DATA_COPY)
        {
            // 数据copy
            WRITE_REG(tx_desc->DESC2, tx_desc->Buff1);
            memcpy((void *)tx_desc->DESC2, (void *)buff->Buff, len);
        }
        else
        {
            // 地址copy
            WRITE_REG(tx_desc->DESC2, (uint32_t)buff->Buff);
        }
        buff->Buff += len;
        
        while (1)
        {
            if ((buff->Len != 0) || (buff->next == 0))
                break;
            buff = buff->next;
        }
        
        // buffer 2
        if (init->TxDescListMode == ETH_DESC_LIST_MODE_RING)
        {
            if (buff->Len != 0)
            {
                // buff2 len
                if (buff->Len > init->TxBuffLen)
                    len = init->TxBuffLen;
                else
                    len = buff->Len;
                buff->Len -= len;
                MODIFY_REG(tx_desc->DESC1, ETH_DMA_TX_DESC1_TBS2, (len << ETH_DMA_TX_DESC1_TBS2_Pos));
        
                if (mode & ETH_TX_MODE_DATA_COPY)
                {
                    // 值copy
                    WRITE_REG(tx_desc->DESC3, tx_desc->Buff2);
                    memcpy((void *)tx_desc->DESC3, (void *)buff->Buff, len);
                }
                else
                {
                    // 地址copy
                    WRITE_REG(tx_desc->DESC3, (uint32_t)buff->Buff);
                }
                buff->Buff += len;
                
                while (1)
                {
                    if ((buff->Len != 0) || (buff->next == 0))
                        break;
                    buff = buff->next;
                }
            }
        }
        nbr++;
        
        if (buff->Len == 0)
            break;
    
        index++;
        if (index >= init->TxDescNbr)
            index = 0;
        tx_desc = &tx_desc_list->TxDescTab[index];
    }
    SET_BIT(tx_desc->DESC0, ETH_DMA_TX_DESC0_LS);
    
    index = tx_desc_list->CurTxDesc;
    tx_desc = &tx_desc_list->TxDescTab[index];
    while (nbr--)
    {
        SET_BIT(tx_desc->DESC0, ETH_DMA_TX_DESC0_OWN);
        
        index++;
        if (index >= init->TxDescNbr)
            index = 0;
        tx_desc = &tx_desc_list->TxDescTab[index];
    }
    tx_desc_list->CurTxDesc = index;
    
    (heth->Instance)->DMASR = ETH_DMASR_TBUS;
    (heth->Instance)->DMATPDR = 0;
    
    // 等待发送完成
    if (mode & (ETH_TX_MODE_WAIT_TX_COMPLETE | ETH_TX_MODE_TIMESTAMP))
    {
        index = tx_desc_list->CurTxDesc;
        if (index == 0)
            index = init->TxDescNbr - 1;
        else
            index--;
        tx_desc = &tx_desc_list->TxDescTab[index];
        
        timeout = 0xffffffff;
        while (1)
        {
            if (READ_BIT(tx_desc->DESC0, ETH_DMA_TX_DESC0_OWN) == 0)
                break;
            timeout--;
            if (timeout == 0)
                return HAL_ERROR;
        }
        if (pStatus)
        {
            pStatus->Status0 = READ_REG(tx_desc->DESC0);
            if (READ_BIT(tx_desc->DESC0, ETH_DMA_TX_DESC0_TTSS))
            {
                pStatus->TimestampValid = ENABLE;
                pStatus->Timestamp.sec = READ_REG(tx_desc->DESC7);
                pStatus->Timestamp.nsec = (int32_t)READ_REG(tx_desc->DESC6);
            }
            else
            {
                pStatus->TimestampValid = DISABLE;
            }
        }
    }
    
    return HAL_OK;
}

/**
  * @brief  Checks for received Packets.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval  1: A Packet is received
  *          0: no Packet received
  */
HAL_StatusTypeDef HAL_ETH_Receive(ETH_HandleTypeDef *heth, ETH_BuffTypeDef **buff, ETH_RxStatusTypeDef *pStatus)
{
    uint32_t i;
    uint32_t first_desc_index;
    uint32_t desc_nbr;
    uint32_t desc_index;
    uint32_t first_rx_buff_index;
    uint32_t curr_rx_buff_index;
    uint32_t next_rx_buff_index;
    uint32_t desc0;
    uint32_t packet_len;
    uint32_t desc_len;
    uint32_t len;
    ETH_InitTypeDef *init;
    ETH_BuffTypeDef *rx_buff;
    ETH_DMADescTypeDef *rx_desc;
    ETH_RxDescListTypeDef *rx_desc_list;

    rx_desc_list = &heth->RxDescList;
    
    if(rx_desc_list->RxDescNbr != 0U)
        return HAL_OK;
    
    *buff = 0;
    init = &heth->Init;
    rx_buff = init->RxBuffTab;
    while (1)
    {
        desc_index = rx_desc_list->CurRxDesc;
        desc_nbr = 0;
        first_desc_index = 0;
        rx_desc = &rx_desc_list->RxDescTab[desc_index];
        packet_len = 0;
        desc_len = 0;
        len = 0;
        first_rx_buff_index = 0;

        for (i=0; i<init->RxDescNbr; i++)
        {
            if (READ_BIT(rx_desc->DESC0, ETH_DMA_RX_DESC0_OWN))
            {
                if (desc_nbr == 0)
                    return HAL_OK;
                break;
            }

            desc0 = READ_REG(rx_desc->DESC0);
            
            if (READ_BIT(desc0, ETH_DMA_RX_DESC0_LS))
            {
                if (READ_BIT(desc0, ETH_DMA_RX_DESC0_FS))
                {
                    if (desc_nbr)
                        break;
                    desc_nbr = 1;
                    
                    first_desc_index = desc_index;
                    packet_len = (desc0 & ETH_DMA_RX_DESC0_FL) >> ETH_DMA_RX_DESC0_FL_Pos;
                    
                    if (init->RxDescListMode == ETH_DESC_LIST_MODE_RING)
                        first_rx_buff_index = desc_index << 1;
                    else
                        first_rx_buff_index = desc_index;
                }
                else
                {
                    desc_nbr++;
                    if (desc_nbr == 1)
                        break;
                    
                    packet_len = (desc0 & ETH_DMA_RX_DESC0_FL) >> ETH_DMA_RX_DESC0_FL_Pos;
                    if (packet_len < len)
                        break;
                    packet_len -= len;
                }
                
                if (init->RxDescListMode == ETH_DESC_LIST_MODE_RING)
                {
                    if (packet_len > (init->RxBuffLen << 1))
                        break;
                    
                    first_rx_buff_index = desc_index << 1;
                    
                    if (packet_len <= init->RxBuffLen)
                    {
                        rx_buff[curr_rx_buff_index].Buff = (uint8_t *)rx_desc->Buff1;
                        rx_buff[curr_rx_buff_index].Len = packet_len;
                        rx_buff[curr_rx_buff_index].next = 0;
                    }
                    else
                    {
                        packet_len -= init->RxBuffLen;
                        
                        next_rx_buff_index = curr_rx_buff_index;
                        next_rx_buff_index++;
                        if (next_rx_buff_index >= init->RxBuffNodeNbr)
                            next_rx_buff_index = 0;
                        
                        rx_buff[curr_rx_buff_index].Buff = (uint8_t *)rx_desc->Buff1;
                        rx_buff[curr_rx_buff_index].Len = init->RxBuffLen;
                        rx_buff[curr_rx_buff_index].next = &rx_buff[next_rx_buff_index];
                    
                        rx_buff[next_rx_buff_index].Buff = (uint8_t *)rx_desc->Buff2;
                        rx_buff[next_rx_buff_index].Len = packet_len;
                        rx_buff[next_rx_buff_index].next = 0;
                    }
                }
                else
                {
                    if (packet_len > init->RxBuffLen)
                        break;
                    
                    rx_buff[desc_index].Buff = (uint8_t *)rx_desc->Buff1;
                    rx_buff[desc_index].Len = packet_len;
                    rx_buff[desc_index].next = 0;
                }
                
                desc_index++;
                if (desc_index >= init->RxDescNbr)
                    desc_index = 0;
                
                rx_desc_list->CurRxDesc = desc_index;
                rx_desc_list->FirstRxDesc = first_desc_index;
                rx_desc_list->RxDescNbr = 1;
                
                *buff = &init->RxBuffTab[first_rx_buff_index];
                if (pStatus)
                {
                    pStatus->Status0 = rx_desc->DESC0;
                    if (READ_BIT(heth->Instance->DMABMR, ETH_DMABMR_EDFE))
                    {
                        if (READ_BIT(rx_desc->DESC0, ETH_DMA_RX_DESC0_TSV))
                        {
                            pStatus->TimestampValid = ENABLE;
                            pStatus->Timestamp.sec = rx_desc->DESC7;
                            pStatus->Timestamp.nsec = (int32_t)rx_desc->DESC6;
                        }
                    }
                }
                return HAL_OK;
            }
            else if (READ_BIT(desc0, ETH_DMA_RX_DESC0_FS))
            {
                if (desc_nbr)
                    break;
                desc_nbr = 1;
                
                first_desc_index = desc_index;
                len = 0;
                
                if (init->RxDescListMode == ETH_DESC_LIST_MODE_RING)
                {
                    len += init->RxBuffLen << 1;
                    
                    curr_rx_buff_index = desc_index << 1;
                    
                    next_rx_buff_index = curr_rx_buff_index;
                    next_rx_buff_index++;
                    if (next_rx_buff_index >= init->RxBuffNodeNbr)
                        next_rx_buff_index = 0;
                    
                    rx_buff[curr_rx_buff_index].Buff = (uint8_t *)rx_desc->Buff1;
                    rx_buff[curr_rx_buff_index].Len = init->RxBuffLen;
                    rx_buff[curr_rx_buff_index].next = &rx_buff[next_rx_buff_index];
                    
                    curr_rx_buff_index = next_rx_buff_index;
                    next_rx_buff_index++;
                    if (next_rx_buff_index >= init->RxBuffNodeNbr)
                        next_rx_buff_index = 0;
                    
                    rx_buff[curr_rx_buff_index].Buff = (uint8_t *)rx_desc->Buff2;
                    rx_buff[curr_rx_buff_index].Len = init->RxBuffLen;
                    rx_buff[curr_rx_buff_index].next = &rx_buff[next_rx_buff_index];
                }
                else
                {
                    len += init->RxBuffLen;
                    
                    next_rx_buff_index = desc_index;
                    next_rx_buff_index++;
                    if (next_rx_buff_index >= init->RxBuffNodeNbr)
                        next_rx_buff_index = 0;
                    
                    rx_buff[desc_index].Buff = (uint8_t *)rx_desc->Buff1;
                    rx_buff[desc_index].Len = init->RxBuffLen;
                    rx_buff[desc_index].next = &rx_buff[next_rx_buff_index];
                }
                
                desc_index++;
                if (desc_index >= init->RxDescNbr)
                    desc_index = 0;
                rx_desc = &rx_desc_list->RxDescTab[desc_index];
            }
            else
            {
                desc_nbr++;
                if (desc_nbr == 1)
                    break;
                
                if (init->RxDescListMode == ETH_DESC_LIST_MODE_RING)
                {
                    len += init->RxBuffLen << 1;
                    
                    curr_rx_buff_index = desc_index << 1;
                    
                    next_rx_buff_index = curr_rx_buff_index;
                    next_rx_buff_index++;
                    if (next_rx_buff_index >= init->RxBuffNodeNbr)
                        next_rx_buff_index = 0;
                    
                    rx_buff[curr_rx_buff_index].Buff = (uint8_t *)rx_desc->Buff1;
                    rx_buff[curr_rx_buff_index].Len = init->RxBuffLen;
                    rx_buff[curr_rx_buff_index].next = &rx_buff[next_rx_buff_index];
                    
                    curr_rx_buff_index = next_rx_buff_index;
                    next_rx_buff_index++;
                    if (next_rx_buff_index >= init->RxBuffNodeNbr)
                        next_rx_buff_index = 0;
                    
                    rx_buff[curr_rx_buff_index].Buff = (uint8_t *)rx_desc->Buff2;
                    rx_buff[curr_rx_buff_index].Len = init->RxBuffLen;
                    rx_buff[curr_rx_buff_index].next = &rx_buff[next_rx_buff_index];
                }
                else
                {
                    len += init->RxBuffLen;
                    
                    next_rx_buff_index = desc_index;
                    next_rx_buff_index++;
                    if (next_rx_buff_index >= init->RxBuffNodeNbr)
                        next_rx_buff_index = 0;
                    
                    rx_buff[desc_index].Buff = (uint8_t *)rx_desc->Buff1;
                    rx_buff[desc_index].Len = init->RxBuffLen;
                    rx_buff[desc_index].next = &rx_buff[next_rx_buff_index];
                }
                
                desc_index++;
                if (desc_index >= init->RxDescNbr)
                    desc_index = 0;
                rx_desc = &rx_desc_list->RxDescTab[desc_index];
            }
        }

        desc_index = rx_desc_list->CurRxDesc;
        rx_desc = &rx_desc_list->RxDescTab[desc_index];

        while (desc_nbr--)
        {
            WRITE_REG(rx_desc->DESC2, rx_desc->Buff1);
            WRITE_REG(rx_desc->DESC3, rx_desc->Buff2);
            
            SET_BIT(rx_desc->DESC0, ETH_DMA_RX_DESC0_OWN);
            
            desc_index++;
            if (desc_index >= init->RxDescNbr)
                desc_index = 0;
            rx_desc = &rx_desc_list->RxDescTab[desc_index];
        }
        
        rx_desc_list->CurRxDesc = desc_index;
        rx_desc_list->FirstRxDesc = 0;
        rx_desc_list->RxDescNbr = 0;
    }
}


/**
* @brief  This function gives back Rx Desc of the last received Packet
*         to the DMA, so ETH DMA will be able to use these descriptors
*         to receive next Packets.
*         It should be called after processing the received Packet.
* @param  heth: pointer to a ETH_HandleTypeDef structure that contains
*         the configuration information for ETHERNET module
* @retval HAL status.
*/
HAL_StatusTypeDef HAL_ETH_ReleaseRxDescriptors(ETH_HandleTypeDef *heth)
{
    uint32_t desc_nbr;
    uint32_t desc_index;
    ETH_InitTypeDef *init;
    ETH_DMADescTypeDef *rx_desc;
    ETH_RxDescListTypeDef *rx_desc_list;

    rx_desc_list = &heth->RxDescList;
    desc_nbr = rx_desc_list->RxDescNbr;
    
    if(desc_nbr == 0U)
        return HAL_OK;
    
    init = &heth->Init;
    
    desc_index = rx_desc_list->FirstRxDesc;
    
    while (desc_nbr--)
    {
        rx_desc = &rx_desc_list->RxDescTab[desc_index];
        
        WRITE_REG(rx_desc->DESC2, rx_desc->Buff1);
        WRITE_REG(rx_desc->DESC3, rx_desc->Buff2);
        
        SET_BIT(rx_desc->DESC0, ETH_DMA_RX_DESC0_OWN);
        
        desc_index++;
        if (desc_index >= init->RxDescNbr)
            desc_index = 0;
    }
    
    rx_desc_list->CurRxDesc = desc_index;
    rx_desc_list->FirstRxDesc = 0;
    rx_desc_list->RxDescNbr = 0;

    return HAL_OK;
}
    
//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_Start(ETH_HandleTypeDef *heth);
//	功能 ：	ETH开始
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：操作成功；
//	备注 ：	
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_Start(ETH_HandleTypeDef *heth)
{
//	if (heth->State != HAL_ETH_STATE_RESET)
//        return HAL_ERROR;
    
	heth->State = HAL_ETH_STATE_BUSY;

	/* Enable the MAC transmission */
	(heth->Instance)->MACCR |= ETH_MACCR_TE;

    /* Enable the MAC reception */
    (heth->Instance)->MACCR |= ETH_MACCR_RE;

    /* Set the Flush Transmit FIFO bit */
//    (heth->Instance)->DMAOMR |= ETH_DMAOMR_FTF;

    /* Enable the DMA transmission */
    (heth->Instance)->DMAOMR |= ETH_DMAOMR_ST;

    /* Enable the DMA reception */
    (heth->Instance)->DMAOMR |= ETH_DMAOMR_SR;  

    __HAL_ETH_DMA_ENABLE_IT(heth, (ETH_DMAIER_NISE | ETH_DMAIER_AISE | ETH_DMAIER_RIE | ETH_DMAIER_TIE));
    
	heth->State= HAL_ETH_STATE_READY;

	return HAL_OK;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_Stop(ETH_HandleTypeDef *heth);
//	功能 ：	ETH停止
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：操作成功；
//	备注 ：	
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_Stop(ETH_HandleTypeDef *heth)
{
//	if (heth->State != HAL_ETH_STATE_RESET)
//        return HAL_ERROR;
    
	heth->State = HAL_ETH_STATE_BUSY;

    /* Disable the DMA transmission */
    (heth->Instance)->DMAOMR &= ~ETH_DMAOMR_ST;

    /* Disable the DMA reception */
    (heth->Instance)->DMAOMR &= ~ETH_DMAOMR_SR;

    /* Disable the MAC reception */
    (heth->Instance)->MACCR &= ~ETH_MACCR_RE;

    /* Set the Flush Transmit FIFO bit */
    (heth->Instance)->DMAOMR |= ETH_DMAOMR_FTF;

    /* Disable the MAC transmission */
    (heth->Instance)->MACCR &= ~ETH_MACCR_TE;

	heth->State = HAL_ETH_STATE_READY;

	return HAL_OK;
}

//	****************************************************************************
//	函数 ：	HAL_ETH_StateTypeDef HAL_ETH_GetState(ETH_HandleTypeDef *heth);
//	功能 ：	取以太网状态
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//	输出 ：	无；
//	返回 ：	以太网状态
//	备注 ：	
//	****************************************************************************

HAL_ETH_StateTypeDef HAL_ETH_GetState(ETH_HandleTypeDef *heth)
{  
    /* Return ETH state */
    return heth->State;
}

//	****************************************************************************
//  
//                              Filter
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_InitAddrFilterDefaultParamter(ETH_HandleTypeDef *heth)
{
    ETH_AddrFilterTypeDef *pAddrFilterConfig = &heth->FilterConfig.Addr;
    
    // 地址过滤
	pAddrFilterConfig->Addr[0].Enable = DISABLE;
	pAddrFilterConfig->Addr[0].GroupFilter = DISABLE;
	pAddrFilterConfig->Addr[0].PerfectSourAddr = DISABLE;
	pAddrFilterConfig->Addr[0].GroupMask = 0;
	pAddrFilterConfig->Addr[0].Addr[0] = 0xFFU;
	pAddrFilterConfig->Addr[0].Addr[1] = 0xFFU;
	pAddrFilterConfig->Addr[0].Addr[2] = 0xFFU;
	pAddrFilterConfig->Addr[0].Addr[3] = 0xFFU;
	pAddrFilterConfig->Addr[0].Addr[4] = 0xFFU;
	pAddrFilterConfig->Addr[0].Addr[5] = 0xFFU;
	pAddrFilterConfig->Addr[1].Enable = DISABLE;
	pAddrFilterConfig->Addr[1].GroupFilter = DISABLE;
	pAddrFilterConfig->Addr[1].PerfectSourAddr = DISABLE;
	pAddrFilterConfig->Addr[1].GroupMask = 0;
	pAddrFilterConfig->Addr[1].Addr[0] = 0;
	pAddrFilterConfig->Addr[1].Addr[1] = 0;
	pAddrFilterConfig->Addr[1].Addr[2] = 0;
	pAddrFilterConfig->Addr[1].Addr[3] = 0;
	pAddrFilterConfig->Addr[1].Addr[4] = 0;
	pAddrFilterConfig->Addr[1].Addr[5] = 0;
	pAddrFilterConfig->Addr[2].Enable = DISABLE;
	pAddrFilterConfig->Addr[2].GroupFilter = DISABLE;
	pAddrFilterConfig->Addr[2].PerfectSourAddr = DISABLE;
	pAddrFilterConfig->Addr[2].GroupMask = 0;
	pAddrFilterConfig->Addr[2].Addr[0] = 0;
	pAddrFilterConfig->Addr[2].Addr[1] = 0;
	pAddrFilterConfig->Addr[2].Addr[2] = 0;
	pAddrFilterConfig->Addr[2].Addr[3] = 0;
	pAddrFilterConfig->Addr[2].Addr[4] = 0;
	pAddrFilterConfig->Addr[2].Addr[5] = 0;
	pAddrFilterConfig->ReceiveAll = DISABLE;
	pAddrFilterConfig->HashPerfectFilter = DISABLE;
	pAddrFilterConfig->SourceAddrFilter = DISABLE;
	pAddrFilterConfig->SourceAddrInverseFilter = DISABLE;
	pAddrFilterConfig->PassControlPackets = ETH_PASS_CONTROL_BLOCK_ALL;     // 配置：传输控制帧，过滤掉所有控制包，阻止它们达到应用程序
	pAddrFilterConfig->BroadcastFramesReception = ENABLE;                   // 使能：广播帧接收
	pAddrFilterConfig->PassAllMulticast = DISABLE;
	pAddrFilterConfig->DestAddrInverseFilter = DISABLE;
	pAddrFilterConfig->HushMulticastFramesFilter = DISABLE;
	pAddrFilterConfig->HashUnicastFramesFilter = DISABLE;
	pAddrFilterConfig->PromiscuousMode = DISABLE;
	pAddrFilterConfig->HashTable[0] = 0;
	pAddrFilterConfig->HashTable[1] = 0;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetAddrFilterConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_AddrFilterTypeDef *pAddrFilterConfig = &heth->FilterConfig.Addr;

	if (heth == NULL)
		return (HAL_ERROR);

    memset((void *)pAddrFilterConfig, 0, sizeof(ETH_AddrFilterTypeDef));
	
    // MACA1HR
	tmpreg = (heth->Instance)->MACA1HR;
    
    if (tmpreg & ETH_MACA1HR_AE)
        pAddrFilterConfig->Addr[0].Enable = ENABLE;
    else
        pAddrFilterConfig->Addr[0].Enable = DISABLE;
    
    if (tmpreg & ETH_MACA1HR_MBC)
    {
        pAddrFilterConfig->Addr[0].GroupFilter = ENABLE;
        pAddrFilterConfig->Addr[0].GroupMask = (tmpreg & ETH_MACA1HR_MBC) >> ETH_MACA1HR_MBC_Pos;
    }
    else
    {
        pAddrFilterConfig->Addr[0].GroupFilter = DISABLE;
        pAddrFilterConfig->Addr[0].GroupMask = 0;
    }
    
    if (tmpreg & ETH_MACA1HR_SA)
        pAddrFilterConfig->Addr[0].PerfectSourAddr = ENABLE;
    else
        pAddrFilterConfig->Addr[0].PerfectSourAddr = DISABLE;
    
    pAddrFilterConfig->Addr[0].Addr[5] = (tmpreg >> 8) & 0xff;
    pAddrFilterConfig->Addr[0].Addr[4] = (tmpreg >> 0) & 0xff;
    
    // MACA1LR
	tmpreg = (heth->Instance)->MACA1LR;
    pAddrFilterConfig->Addr[0].Addr[3] = (tmpreg >> 24) & 0xff;
    pAddrFilterConfig->Addr[0].Addr[2] = (tmpreg >> 16) & 0xff;
    pAddrFilterConfig->Addr[0].Addr[1] = (tmpreg >> 8) & 0xff;
    pAddrFilterConfig->Addr[0].Addr[0] = (tmpreg >> 0) & 0xff;
    
    // MACA2HR
	tmpreg = (heth->Instance)->MACA2HR;
    
    if (tmpreg & ETH_MACA1HR_AE)
        pAddrFilterConfig->Addr[1].Enable = ENABLE;
    else
        pAddrFilterConfig->Addr[1].Enable = DISABLE;
    
    if (tmpreg & ETH_MACA1HR_MBC)
    {
        pAddrFilterConfig->Addr[1].GroupFilter = ENABLE;
        pAddrFilterConfig->Addr[1].GroupMask = (tmpreg & ETH_MACA1HR_MBC) >> ETH_MACA1HR_MBC_Pos;
    }
    else
    {
        pAddrFilterConfig->Addr[1].GroupFilter = DISABLE;
        pAddrFilterConfig->Addr[1].GroupMask = 0;
    }
    
    if (tmpreg & ETH_MACA1HR_SA)
        pAddrFilterConfig->Addr[1].PerfectSourAddr = ENABLE;
    else
        pAddrFilterConfig->Addr[1].PerfectSourAddr = DISABLE;
    
    pAddrFilterConfig->Addr[1].Addr[5] = (tmpreg >> 8) & 0xff;
    pAddrFilterConfig->Addr[1].Addr[4] = (tmpreg >> 0) & 0xff;
    
    // MACA2LR
	tmpreg = (heth->Instance)->MACA2LR;
    pAddrFilterConfig->Addr[1].Addr[3] = (tmpreg >> 24) & 0xff;
    pAddrFilterConfig->Addr[1].Addr[2] = (tmpreg >> 16) & 0xff;
    pAddrFilterConfig->Addr[1].Addr[1] = (tmpreg >> 8) & 0xff;
    pAddrFilterConfig->Addr[1].Addr[0] = (tmpreg >> 0) & 0xff;
    
    // MACA3HR
	tmpreg = (heth->Instance)->MACA3HR;
    
    if (tmpreg & ETH_MACA1HR_AE)
        pAddrFilterConfig->Addr[2].Enable = ENABLE;
    else
        pAddrFilterConfig->Addr[2].Enable = DISABLE;
    
    if (tmpreg & ETH_MACA1HR_MBC)
    {
        pAddrFilterConfig->Addr[2].GroupFilter = ENABLE;
        pAddrFilterConfig->Addr[2].GroupMask = (tmpreg & ETH_MACA1HR_MBC) >> ETH_MACA1HR_MBC_Pos;
    }
    else
    {
        pAddrFilterConfig->Addr[2].GroupFilter = DISABLE;
        pAddrFilterConfig->Addr[2].GroupMask = 0;
    }
    
    if (tmpreg & ETH_MACA1HR_SA)
        pAddrFilterConfig->Addr[2].PerfectSourAddr = ENABLE;
    else
        pAddrFilterConfig->Addr[2].PerfectSourAddr = DISABLE;
    
    pAddrFilterConfig->Addr[2].Addr[5] = (tmpreg >> 8) & 0xff;
    pAddrFilterConfig->Addr[2].Addr[4] = (tmpreg >> 0) & 0xff;
    
    // MACA3LR
	tmpreg = (heth->Instance)->MACA3LR;
    pAddrFilterConfig->Addr[2].Addr[3] = (tmpreg >> 24) & 0xff;
    pAddrFilterConfig->Addr[2].Addr[2] = (tmpreg >> 16) & 0xff;
    pAddrFilterConfig->Addr[2].Addr[1] = (tmpreg >> 8) & 0xff;
    pAddrFilterConfig->Addr[2].Addr[0] = (tmpreg >> 0) & 0xff;
    
	// MACFFR
	tmpreg = (heth->Instance)->MACFFR;
	
	if (tmpreg & ETH_MACFFR_RA)
        pAddrFilterConfig->ReceiveAll = ENABLE;
    else
        pAddrFilterConfig->ReceiveAll = DISABLE;
	
	if (tmpreg & ETH_MACFFR_HPF)
        pAddrFilterConfig->HashPerfectFilter = ENABLE;
    else
        pAddrFilterConfig->HashPerfectFilter = DISABLE;
	
	if (tmpreg & ETH_MACFFR_SAF)
        pAddrFilterConfig->SourceAddrFilter = ENABLE;
    else
        pAddrFilterConfig->SourceAddrFilter = DISABLE;
	
	if (tmpreg & ETH_MACFFR_SAIF)
        pAddrFilterConfig->SourceAddrInverseFilter = ENABLE;
    else
        pAddrFilterConfig->SourceAddrInverseFilter = DISABLE;
    
	if ((tmpreg & ETH_MACFFR_PCF) == 0)
        pAddrFilterConfig->PassControlPackets = ETH_PASS_CONTROL_BLOCK_ALL;
    else if ((tmpreg & ETH_MACFFR_PCF) == ETH_MACFFR_PCF_0)
        pAddrFilterConfig->PassControlPackets = ETH_PASS_CONTROL_FORWARD_ALL_EXCEPT_PAUSE_FRAME;
    else if ((tmpreg & ETH_MACFFR_PCF) == ETH_MACFFR_PCF_1)
        pAddrFilterConfig->PassControlPackets = ETH_PASS_CONTROL_FORWARD_ALL;
    else if ((tmpreg & ETH_MACFFR_PCF) == (ETH_MACFFR_PCF_1 | ETH_MACFFR_PCF_0))
        pAddrFilterConfig->PassControlPackets = ETH_PASS_CONTROL_FORWARD_PASSED_ADDR_FILTER;
	
	if (tmpreg & ETH_MACFFR_DBF)
        pAddrFilterConfig->BroadcastFramesReception = DISABLE;
    else
        pAddrFilterConfig->BroadcastFramesReception = ENABLE;
	
	if (tmpreg & ETH_MACFFR_PAM)
        pAddrFilterConfig->PassAllMulticast = ENABLE;
    else
        pAddrFilterConfig->PassAllMulticast = DISABLE;
	
	if (tmpreg & ETH_MACFFR_DAIF)
        pAddrFilterConfig->DestAddrInverseFilter = ENABLE;
    else
        pAddrFilterConfig->DestAddrInverseFilter = DISABLE;
	
	if (tmpreg & ETH_MACFFR_HMC)
        pAddrFilterConfig->HushMulticastFramesFilter = ENABLE;
    else
        pAddrFilterConfig->HushMulticastFramesFilter = DISABLE;
	
	if (tmpreg & ETH_MACFFR_HUC)
        pAddrFilterConfig->HashUnicastFramesFilter = ENABLE;
    else
        pAddrFilterConfig->HashUnicastFramesFilter = DISABLE;
	
	if (tmpreg & ETH_MACFFR_PR)
        pAddrFilterConfig->PromiscuousMode = ENABLE;
    else
        pAddrFilterConfig->PromiscuousMode = DISABLE;
	
	// MACHTHR
	pAddrFilterConfig->HashTable[1] = (heth->Instance)->MACHTHR;
	
	// MACHTLR
	pAddrFilterConfig->HashTable[0] = (heth->Instance)->MACHTLR;
	
	return HAL_OK;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_ConfigMAC(ETH_HandleTypeDef *heth, ETH_MACInitTypeDef *pMACConfig);
//	功能 ：	配置MAC
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			dmaconf：配置结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_SetAddrFilterConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_AddrFilterTypeDef *pAddrFilterConfig = &heth->FilterConfig.Addr;

	if (heth == NULL)
		return (HAL_ERROR);
    
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->Addr[0].Enable));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->Addr[1].Enable));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->Addr[2].Enable));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->ReceiveAll));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->HashPerfectFilter));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->SourceAddrFilter));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->SourceAddrInverseFilter));
	assert_param(IS_ETH_PASS_CONTROL_PACKETS(pAddrFilterConfig->PassControlPackets));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->BroadcastFramesReception));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->PassAllMulticast));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->DestAddrInverseFilter));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->HushMulticastFramesFilter));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->HashUnicastFramesFilter));
	assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->PromiscuousMode));

    // MACA1HR
    if (pAddrFilterConfig->Addr[0].Enable == DISABLE)
    {
        (heth->Instance)->MACA1HR = 0;
        (heth->Instance)->MACA1LR = 0;
    }
    else
    {
        assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->Addr[0].GroupFilter));
        
        tmpreg = ETH_MACA1HR_AE;
        if (pAddrFilterConfig->Addr[0].GroupFilter == DISABLE)
        {
            assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->Addr[0].PerfectSourAddr));
            
            if (pAddrFilterConfig->Addr[0].PerfectSourAddr != DISABLE)
                tmpreg |= ETH_MACA1HR_SA;
        }
        else
        {
            assert_param(IS_ETH_ADDR_FILTER_GROUP_MASK(pAddrFilterConfig->Addr[0].GroupMask));
            
            tmpreg |= pAddrFilterConfig->Addr[0].GroupMask << ETH_MACA1HR_MBC_Pos;
        }
        
        (heth->Instance)->MACA1HR = tmpreg | \
                                    ((uint32_t)pAddrFilterConfig->Addr[0].Addr[5] << 8) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[0].Addr[4] << 0);
        
        // MACA1LR
        (heth->Instance)->MACA1LR = ((uint32_t)pAddrFilterConfig->Addr[0].Addr[3] << 24) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[0].Addr[2] << 16) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[0].Addr[1] << 8) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[0].Addr[0] << 0);
    }
    
    // MACA1HR
    if (pAddrFilterConfig->Addr[1].Enable == DISABLE)
    {
        (heth->Instance)->MACA2HR = 0;
        (heth->Instance)->MACA2LR = 0;
    }
    else
    {
        assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->Addr[1].GroupFilter));
        
        tmpreg = ETH_MACA2HR_AE;
        if (pAddrFilterConfig->Addr[1].GroupFilter == DISABLE)
        {
            assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->Addr[1].PerfectSourAddr));
            
            if (pAddrFilterConfig->Addr[1].PerfectSourAddr != DISABLE)
                tmpreg |= ETH_MACA2HR_SA;
        }
        else
        {
            assert_param(IS_ETH_ADDR_FILTER_GROUP_MASK(pAddrFilterConfig->Addr[1].GroupMask));
            
            tmpreg |= pAddrFilterConfig->Addr[1].GroupMask << ETH_MACA2HR_MBC_Pos;
        }
        
        (heth->Instance)->MACA2HR = tmpreg | \
                                    ((uint32_t)pAddrFilterConfig->Addr[1].Addr[5] << 8) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[1].Addr[4] << 0);
        
        // MACA2LR
        (heth->Instance)->MACA2LR = ((uint32_t)pAddrFilterConfig->Addr[1].Addr[3] << 24) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[1].Addr[2] << 16) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[1].Addr[1] << 8) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[1].Addr[0] << 0);
    }
    
    // MACA3HR
    if (pAddrFilterConfig->Addr[2].Enable == DISABLE)
    {
        (heth->Instance)->MACA3HR = 0;
        (heth->Instance)->MACA3LR = 0;
    }
    else
    {
        assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->Addr[2].GroupFilter));
        
        tmpreg = ETH_MACA3HR_AE;
        if (pAddrFilterConfig->Addr[2].GroupFilter == DISABLE)
        {
            assert_param(IS_FUNCTIONAL_STATE(pAddrFilterConfig->Addr[2].PerfectSourAddr));
            
            if (pAddrFilterConfig->Addr[2].PerfectSourAddr != DISABLE)
                tmpreg |= ETH_MACA3HR_SA;
        }
        else
        {
            assert_param(IS_ETH_ADDR_FILTER_GROUP_MASK(pAddrFilterConfig->Addr[2].GroupMask));
            
            tmpreg |= pAddrFilterConfig->Addr[2].GroupMask << ETH_MACA3HR_MBC_Pos;
        }
        
        (heth->Instance)->MACA3HR = tmpreg | \
                                    ((uint32_t)pAddrFilterConfig->Addr[2].Addr[5] << 8) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[2].Addr[4] << 0);
        
        // MACA3LR
        (heth->Instance)->MACA3LR = ((uint32_t)pAddrFilterConfig->Addr[2].Addr[3] << 24) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[2].Addr[2] << 16) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[2].Addr[1] << 8) | \
                                    ((uint32_t)pAddrFilterConfig->Addr[2].Addr[0] << 0);
    }
    
	// MACFFR
	tmpreg = (heth->Instance)->MACFFR;
	tmpreg &= ~(ETH_MACFFR_RA | ETH_MACFFR_HPF | ETH_MACFFR_SAF | ETH_MACFFR_PCF | ETH_MACFFR_DBF | \
                ETH_MACFFR_PAM | ETH_MACFFR_DAIF | ETH_MACFFR_HMC | ETH_MACFFR_HUC | ETH_MACFFR_PR);

    if (pAddrFilterConfig->ReceiveAll != DISABLE)
        tmpreg |= ETH_MACFFR_RA;
    
    if (pAddrFilterConfig->HashPerfectFilter != DISABLE)
        tmpreg |= ETH_MACFFR_HPF;
    
    if (pAddrFilterConfig->SourceAddrFilter != DISABLE)
        tmpreg |= ETH_MACFFR_SAF;
    
    if (pAddrFilterConfig->SourceAddrInverseFilter != DISABLE)
        tmpreg |= ETH_MACFFR_SAIF;
    
    if (pAddrFilterConfig->PassControlPackets == ETH_PASS_CONTROL_BLOCK_ALL)
        tmpreg |= 0U;
    else if (pAddrFilterConfig->PassControlPackets == ETH_PASS_CONTROL_FORWARD_ALL_EXCEPT_PAUSE_FRAME)
        tmpreg |= ETH_MACFFR_PCF_0;
    else if (pAddrFilterConfig->PassControlPackets == ETH_PASS_CONTROL_FORWARD_ALL)
        tmpreg |= ETH_MACFFR_PCF_1;
    else if (pAddrFilterConfig->PassControlPackets == ETH_PASS_CONTROL_FORWARD_PASSED_ADDR_FILTER)
        tmpreg |= ETH_MACFFR_PCF_1 | ETH_MACFFR_PCF_0;
    
    if (pAddrFilterConfig->BroadcastFramesReception == DISABLE)
        tmpreg |= ETH_MACFFR_DBF;
    
    if (pAddrFilterConfig->PassAllMulticast != DISABLE)
        tmpreg |= ETH_MACFFR_PAM;
    
    if (pAddrFilterConfig->DestAddrInverseFilter != DISABLE)
        tmpreg |= ETH_MACFFR_DAIF;
    
    if (pAddrFilterConfig->HushMulticastFramesFilter != DISABLE)
        tmpreg |= ETH_MACFFR_HMC;
    
    if (pAddrFilterConfig->HashUnicastFramesFilter != DISABLE)
        tmpreg |= ETH_MACFFR_HUC;
    
    if (pAddrFilterConfig->PromiscuousMode != DISABLE)
        tmpreg |= ETH_MACFFR_PR;
    
    (heth->Instance)->MACFFR = tmpreg;
    
	// MACHTHR
	(heth->Instance)->MACHTHR = (uint32_t)pAddrFilterConfig->HashTable[1];

	// MACHTLR
	(heth->Instance)->MACHTLR = (uint32_t)pAddrFilterConfig->HashTable[0];
	
	return HAL_OK;  
}

HAL_StatusTypeDef HAL_ETH_SetAddrFilterDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitAddrFilterDefaultParamter(heth);
    
    return HAL_ETH_SetAddrFilterConfig(heth);
}

HAL_StatusTypeDef HAL_ETH_InitVLANFilterDefaultParamter(ETH_HandleTypeDef *heth)
{
    ETH_VLANFilterTypeDef *pVLANFilterConfig = &heth->FilterConfig.VLAN;
    
    // VLAN过滤
	pVLANFilterConfig->Enable = DISABLE;
	pVLANFilterConfig->Hash = DISABLE;
	pVLANFilterConfig->SVLAN = DISABLE;
	pVLANFilterConfig->InverseMatch = DISABLE;
	pVLANFilterConfig->Comparison12Bits = DISABLE;
	pVLANFilterConfig->Tag = 0;
	pVLANFilterConfig->HashTable = 0;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetVLANFilterConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_VLANFilterTypeDef *pVLANFilterConfig = &heth->FilterConfig.VLAN;

	if (heth == NULL)
		return (HAL_ERROR);

    memset((void *)pVLANFilterConfig, 0, sizeof(ETH_VLANFilterTypeDef));
	
	// MACFFR
	tmpreg = (heth->Instance)->MACFFR;
	
	if (tmpreg & ETH_MACFFR_VTFE)
        pVLANFilterConfig->Enable = ENABLE;
    else
        pVLANFilterConfig->Enable = DISABLE;
	
	// MACVLANTR
	tmpreg = (heth->Instance)->MACVLANTR;
	
	if (tmpreg & ETH_MACVLANTR_VTHM)
        pVLANFilterConfig->Hash = ENABLE;
    else
        pVLANFilterConfig->Hash = DISABLE;
    
	if (tmpreg & ETH_MACVLANTR_ESVL)
        pVLANFilterConfig->SVLAN = ENABLE;
    else
        pVLANFilterConfig->SVLAN = DISABLE;
    
	if (tmpreg & ETH_MACVLANTR_VTIM)
        pVLANFilterConfig->InverseMatch = ENABLE;
    else
        pVLANFilterConfig->InverseMatch = DISABLE;
    
	if (tmpreg & ETH_MACVLANTR_ETV)
        pVLANFilterConfig->Comparison12Bits = ENABLE;
    else
        pVLANFilterConfig->Comparison12Bits = DISABLE;
    
	pVLANFilterConfig->Tag = (tmpreg & ETH_MACVLANTR_VL) >> ETH_MACVLANTR_VL_Pos;
	
    // MACVHTR 
    pVLANFilterConfig->HashTable = ((heth->Instance)->MACVHTR & ETH_MACVHTR_CSVL) >> ETH_MACVHTR_CSVL_Pos;
    
	return HAL_OK;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_ConfigMAC(ETH_HandleTypeDef *heth, ETH_MACInitTypeDef *pMACConfig);
//	功能 ：	配置MAC
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			dmaconf：配置结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_SetVLANFilterConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_VLANFilterTypeDef *pVLANFilterConfig = &heth->FilterConfig.VLAN;

	if (heth == NULL)
		return (HAL_ERROR);
    
	assert_param(IS_FUNCTIONAL_STATE(pVLANFilterConfig->Enable));
	assert_param(IS_FUNCTIONAL_STATE(pVLANFilterConfig->Hash));
	assert_param(IS_FUNCTIONAL_STATE(pVLANFilterConfig->SVLAN));
	assert_param(IS_FUNCTIONAL_STATE(pVLANFilterConfig->InverseMatch));
	assert_param(IS_FUNCTIONAL_STATE(pVLANFilterConfig->Comparison12Bits));
	assert_param(IS_ETH_VLAN_TAG(pVLANFilterConfig->Tag));
	assert_param(IS_ETH_VLAN_HASH_TABLE(pVLANFilterConfig->HashTable));

	// MACFFR
	tmpreg = (heth->Instance)->MACFFR;
    tmpreg &= ~ETH_MACFFR_VTFE;
    
    if (pVLANFilterConfig->Enable != DISABLE)
        tmpreg |= ETH_MACFFR_VTFE;
    
    (heth->Instance)->MACFFR = tmpreg;
    
	// MACVLANTR
    tmpreg = 0;
    
    if (pVLANFilterConfig->Hash != DISABLE)
        tmpreg |= ETH_MACVLANTR_VTHM;
    
    if (pVLANFilterConfig->SVLAN != DISABLE)
        tmpreg |= ETH_MACVLANTR_ESVL;
    
    if (pVLANFilterConfig->InverseMatch != DISABLE)
        tmpreg |= ETH_MACVLANTR_VTIM;
    
    if (pVLANFilterConfig->Comparison12Bits != DISABLE)
        tmpreg |= ETH_MACVLANTR_ETV;

    tmpreg |= pVLANFilterConfig->Tag << ETH_MACVLANTR_VL_Pos;
    
    (heth->Instance)->MACVLANTR = (uint32_t)tmpreg;
    
    // MACVHTR
    (heth->Instance)->MACVHTR = pVLANFilterConfig->HashTable;
    
	return HAL_OK;  
}

HAL_StatusTypeDef HAL_ETH_SetVLANFilterDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitVLANFilterDefaultParamter(heth);
    
    return HAL_ETH_SetVLANFilterConfig(heth);
}

HAL_StatusTypeDef HAL_ETH_InitL3L4FilterDefaultParamter(ETH_HandleTypeDef *heth)
{
    uint32_t i;
    ETH_L3FilterTypeDef *pL3Config;
    ETH_L4FilterTypeDef *pL4Config;
    
    // Layer3 Layer4过滤
	heth->FilterConfig.L3L4.Enable = DISABLE;
    
    for (i=0; i<2; i++)
    {
        if (i == 0)
            pL3Config = &heth->FilterConfig.L3L4.L3[0];
        else
            pL3Config = &heth->FilterConfig.L3L4.L3[1];
        
        pL3Config->ProtocolIPV6 = DISABLE;
        pL3Config->IPV4.SourAddrMatchEnable = DISABLE;
        pL3Config->IPV4.SourAddrInverseMatch = DISABLE;
        pL3Config->IPV4.SourAddrMatch = 0;
        pL3Config->IPV4.DestAddrMatchEnable = DISABLE;
        pL3Config->IPV4.DestAddrInverseMatch = DISABLE;
        pL3Config->IPV4.DestAddrMatch = 0;
        pL3Config->IPV4.Rsv1[0] = 0;
        pL3Config->IPV4.Rsv1[1] = 0;
        pL3Config->IPV4.SourAddr = 0;
        pL3Config->IPV4.DestAddr = 0;
        pL3Config->IPV4.Rsv2[0] = 0;
        pL3Config->IPV4.Rsv2[1] = 0;
    }
    
    for (i=0; i<2; i++)
    {
        if (i == 0)
            pL4Config = &heth->FilterConfig.L3L4.L4[0];
        else
            pL4Config = &heth->FilterConfig.L3L4.L4[1];
        
        pL4Config->ProtocolUDP = DISABLE;
        pL4Config->SourPortMatchEnable = DISABLE;
        pL4Config->SourPortInverseMatch = DISABLE;
        pL4Config->DestPortMatchEnable = DISABLE;
        pL4Config->DestPortInverseMatch = DISABLE;
        pL4Config->SourPort = 0;
        pL4Config->DestPort = 0;
    }
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetL3L4FilterConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_L3L4FilterTypeDef *pL3L4FilterConfig = &heth->FilterConfig.L3L4;

	if (heth == NULL)
		return (HAL_ERROR);

    memset((void *)pL3L4FilterConfig, 0, sizeof(ETH_L3L4FilterTypeDef));
	
	// MACFFR
	tmpreg = (heth->Instance)->MACFFR;
	
	if (tmpreg & ETH_MACFFR_IPFE)
        pL3L4FilterConfig->Enable = ENABLE;
    else
        pL3L4FilterConfig->Enable = DISABLE;
	
	// MACL3L4C0R 
	tmpreg = (heth->Instance)->MACL3L4C0R;
	
	if (tmpreg & ETH_MACL3L4C0R_L4DPIM0)
        pL3L4FilterConfig->L4[0].DestPortInverseMatch = ENABLE;
    else
        pL3L4FilterConfig->L4[0].DestPortInverseMatch = DISABLE;
	
	if (tmpreg & ETH_MACL3L4C0R_L4DPM0)
        pL3L4FilterConfig->L4[0].DestPortMatchEnable = ENABLE;
    else
        pL3L4FilterConfig->L4[0].DestPortMatchEnable = DISABLE;
	
	if (tmpreg & ETH_MACL3L4C0R_L4SPIM0)
        pL3L4FilterConfig->L4[0].SourPortInverseMatch = ENABLE;
    else
        pL3L4FilterConfig->L4[0].SourPortInverseMatch = DISABLE;
	
	if (tmpreg & ETH_MACL3L4C0R_L4SPM0)
        pL3L4FilterConfig->L4[0].SourPortMatchEnable = ENABLE;
    else
        pL3L4FilterConfig->L4[0].SourPortMatchEnable = DISABLE;
	
	if (tmpreg & ETH_MACL3L4C0R_L4PEN0)
        pL3L4FilterConfig->L4[0].ProtocolUDP = ENABLE;
    else
        pL3L4FilterConfig->L4[0].ProtocolUDP = DISABLE;
	
	if (tmpreg & ETH_MACL3L4C0R_L3PEN0)
    {
        pL3L4FilterConfig->L3[0].ProtocolIPV6 = ENABLE;
        
        pL3L4FilterConfig->L3[0].IPV6.AddrMatch = (tmpreg & (ETH_MACL3L4C0R_L3HDBM0_0 | ETH_MACL3L4C0R_L3HDBM0_1 | ETH_MACL3L4C0R_L3HSBM0)) >> ETH_MACL3L4C0R_L3HSBM0_Pos;
        
        if (tmpreg & ETH_MACL3L4C0R_L3DAIM0)
            pL3L4FilterConfig->L3[0].IPV6.DestAddrInverseMatch = ENABLE;
        else
            pL3L4FilterConfig->L3[0].IPV6.DestAddrInverseMatch = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C0R_L3DAM0)
            pL3L4FilterConfig->L3[0].IPV6.DestAddrMatchEnable = ENABLE;
        else
            pL3L4FilterConfig->L3[0].IPV6.DestAddrMatchEnable = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C0R_L3SAIM0)
            pL3L4FilterConfig->L3[0].IPV6.SourAddrInverseMatch = ENABLE;
        else
            pL3L4FilterConfig->L3[0].IPV6.SourAddrInverseMatch = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C0R_L3SAM0)
            pL3L4FilterConfig->L3[0].IPV6.SourAddrMatchEnable = ENABLE;
        else
            pL3L4FilterConfig->L3[0].IPV6.SourAddrMatchEnable = DISABLE;
        
        // MACL3A00R  
        pL3L4FilterConfig->L3[0].IPV6.Addr[0] = (heth->Instance)->MACL3A00R;
        
        // MACL3A10R  
        pL3L4FilterConfig->L3[0].IPV6.Addr[1] = (heth->Instance)->MACL3A10R;
        
        // MACL3A20R  
        pL3L4FilterConfig->L3[0].IPV6.Addr[2] = (heth->Instance)->MACL3A20R;
        
        // MACL3A30R  
        pL3L4FilterConfig->L3[0].IPV6.Addr[3] = (heth->Instance)->MACL3A30R;
        
    }
    else
    {
        pL3L4FilterConfig->L3[0].ProtocolIPV6 = DISABLE;
        
        pL3L4FilterConfig->L3[0].IPV4.DestAddrMatch = (tmpreg & ETH_MACL3L4C0R_L3HDBM0) >> ETH_MACL3L4C0R_L3HDBM0_Pos;
        
        pL3L4FilterConfig->L3[0].IPV4.SourAddrMatch = (tmpreg & ETH_MACL3L4C0R_L3HSBM0) >> ETH_MACL3L4C0R_L3HSBM0_Pos;
        
        if (tmpreg & ETH_MACL3L4C0R_L3DAIM0)
            pL3L4FilterConfig->L3[0].IPV4.DestAddrInverseMatch = ENABLE;
        else
            pL3L4FilterConfig->L3[0].IPV4.DestAddrInverseMatch = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C0R_L3DAM0)
            pL3L4FilterConfig->L3[0].IPV4.DestAddrMatchEnable = ENABLE;
        else
            pL3L4FilterConfig->L3[0].IPV4.DestAddrMatchEnable = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C0R_L3SAIM0)
            pL3L4FilterConfig->L3[0].IPV4.SourAddrInverseMatch = ENABLE;
        else
            pL3L4FilterConfig->L3[0].IPV4.SourAddrInverseMatch = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C0R_L3SAM0)
            pL3L4FilterConfig->L3[0].IPV4.SourAddrMatchEnable = ENABLE;
        else
            pL3L4FilterConfig->L3[0].IPV4.SourAddrMatchEnable = DISABLE;
        
        // MACL3A00R 
        pL3L4FilterConfig->L3[0].IPV4.SourAddr = (heth->Instance)->MACL3A00R;
        
        // MACL3A10R 
        pL3L4FilterConfig->L3[0].IPV4.DestAddr = (heth->Instance)->MACL3A10R;
        
    }
	
    // MACL4A0R 
    pL3L4FilterConfig->L4[0].DestPort = ((heth->Instance)->MACL4A0R & ETH_MACL4A0R_L4DP0) >> ETH_MACL4A0R_L4DP0_Pos;
    
    pL3L4FilterConfig->L4[0].SourPort = ((heth->Instance)->MACL4A0R & ETH_MACL4A0R_L4SP0) >> ETH_MACL4A0R_L4SP0_Pos;
        
	// MACL3L4C1R 
	tmpreg = (heth->Instance)->MACL3L4C1R;
	
	if (tmpreg & ETH_MACL3L4C1R_L4DPIM1)
        pL3L4FilterConfig->L4[1].DestPortInverseMatch = ENABLE;
    else
        pL3L4FilterConfig->L4[1].DestPortInverseMatch = DISABLE;
	
	if (tmpreg & ETH_MACL3L4C1R_L4DPM1)
        pL3L4FilterConfig->L4[1].DestPortMatchEnable = ENABLE;
    else
        pL3L4FilterConfig->L4[1].DestPortMatchEnable = DISABLE;
	
	if (tmpreg & ETH_MACL3L4C1R_L4SPIM1)
        pL3L4FilterConfig->L4[1].SourPortInverseMatch = ENABLE;
    else
        pL3L4FilterConfig->L4[1].SourPortInverseMatch = DISABLE;
	
	if (tmpreg & ETH_MACL3L4C1R_L4SPM1)
        pL3L4FilterConfig->L4[1].SourPortMatchEnable = ENABLE;
    else
        pL3L4FilterConfig->L4[1].SourPortMatchEnable = DISABLE;
	
	if (tmpreg & ETH_MACL3L4C1R_L4PEN1)
        pL3L4FilterConfig->L4[1].ProtocolUDP = ENABLE;
    else
        pL3L4FilterConfig->L4[1].ProtocolUDP = DISABLE;
	
	if (tmpreg & ETH_MACL3L4C1R_L3PEN1)
    {
        pL3L4FilterConfig->L3[1].ProtocolIPV6 = ENABLE;
        
        pL3L4FilterConfig->L3[1].IPV6.AddrMatch = (tmpreg & (ETH_MACL3L4C1R_L3HDBM1_0 | ETH_MACL3L4C1R_L3HDBM1_1 | ETH_MACL3L4C1R_L3HSBM1)) >> ETH_MACL3L4C1R_L3HSBM1_Pos;
        
        if (tmpreg & ETH_MACL3L4C1R_L3DAIM1)
            pL3L4FilterConfig->L3[1].IPV6.DestAddrInverseMatch = ENABLE;
        else
            pL3L4FilterConfig->L3[1].IPV6.DestAddrInverseMatch = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C1R_L3DAM1)
            pL3L4FilterConfig->L3[1].IPV6.DestAddrMatchEnable = ENABLE;
        else
            pL3L4FilterConfig->L3[1].IPV6.DestAddrMatchEnable = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C1R_L3SAIM1)
            pL3L4FilterConfig->L3[1].IPV6.SourAddrInverseMatch = ENABLE;
        else
            pL3L4FilterConfig->L3[1].IPV6.SourAddrInverseMatch = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C1R_L3SAM1)
            pL3L4FilterConfig->L3[1].IPV6.SourAddrMatchEnable = ENABLE;
        else
            pL3L4FilterConfig->L3[1].IPV6.SourAddrMatchEnable = DISABLE;
        
        // MACL3A01R  
        pL3L4FilterConfig->L3[1].IPV6.Addr[1] = (heth->Instance)->MACL3A01R;
        
        // MACL3A11R  
        pL3L4FilterConfig->L3[1].IPV6.Addr[1] = (heth->Instance)->MACL3A11R;
        
        // MACL3A21R  
        pL3L4FilterConfig->L3[1].IPV6.Addr[2] = (heth->Instance)->MACL3A21R;
        
        // MACL3A31R  
        pL3L4FilterConfig->L3[1].IPV6.Addr[3] = (heth->Instance)->MACL3A31R;
        
    }
    else
    {
        pL3L4FilterConfig->L3[1].ProtocolIPV6 = DISABLE;
        
        pL3L4FilterConfig->L3[1].IPV4.DestAddrMatch = (tmpreg & ETH_MACL3L4C1R_L3HDBM1) >> ETH_MACL3L4C1R_L3HDBM1_Pos;
        
        pL3L4FilterConfig->L3[1].IPV4.SourAddrMatch = (tmpreg & ETH_MACL3L4C1R_L3HSBM1) >> ETH_MACL3L4C1R_L3HSBM1_Pos;
        
        if (tmpreg & ETH_MACL3L4C1R_L3DAIM1)
            pL3L4FilterConfig->L3[1].IPV4.DestAddrInverseMatch = ENABLE;
        else
            pL3L4FilterConfig->L3[1].IPV4.DestAddrInverseMatch = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C1R_L3DAM1)
            pL3L4FilterConfig->L3[1].IPV4.DestAddrMatchEnable = ENABLE;
        else
            pL3L4FilterConfig->L3[1].IPV4.DestAddrMatchEnable = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C1R_L3SAIM1)
            pL3L4FilterConfig->L3[1].IPV4.SourAddrInverseMatch = ENABLE;
        else
            pL3L4FilterConfig->L3[1].IPV4.SourAddrInverseMatch = DISABLE;
    
        if (tmpreg & ETH_MACL3L4C1R_L3SAM1)
            pL3L4FilterConfig->L3[1].IPV4.SourAddrMatchEnable = ENABLE;
        else
            pL3L4FilterConfig->L3[1].IPV4.SourAddrMatchEnable = DISABLE;
        
        // MACL3A01R 
        pL3L4FilterConfig->L3[1].IPV4.SourAddr = (heth->Instance)->MACL3A01R;
        
        // MACL3A11R 
        pL3L4FilterConfig->L3[1].IPV4.DestAddr = (heth->Instance)->MACL3A11R;
        
    }
	
    // MACL4A1R 
    pL3L4FilterConfig->L4[1].DestPort = ((heth->Instance)->MACL4A1R & ETH_MACL4A1R_L4DP1) >> ETH_MACL4A1R_L4DP1_Pos;
    
    pL3L4FilterConfig->L4[1].SourPort = ((heth->Instance)->MACL4A1R & ETH_MACL4A1R_L4SP1) >> ETH_MACL4A1R_L4SP1_Pos;
    
	return HAL_OK;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_ConfigMAC(ETH_HandleTypeDef *heth, ETH_MACInitTypeDef *pMACConfig);
//	功能 ：	配置MAC
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			dmaconf：配置结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_SetL3L4FilterConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_L3L4FilterTypeDef *pL3L4FilterConfig = &heth->FilterConfig.L3L4;

	if (heth == NULL)
		return (HAL_ERROR);
    
	assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->Enable));
	assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L3[0].ProtocolIPV6));
	assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L3[1].ProtocolIPV6));
	assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L4[0].ProtocolUDP));
	assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L4[0].SourPortMatchEnable));
	assert_param(IS_ETH_SOUR_PORT(pL3L4FilterConfig->L4[0].SourPort));
	assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L4[0].DestPortMatchEnable));
	assert_param(IS_ETH_DEST_PORT(pL3L4FilterConfig->L4[0].DestPort));
	assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L4[1].ProtocolUDP));
	assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L4[1].SourPortMatchEnable));
	assert_param(IS_ETH_SOUR_PORT(pL3L4FilterConfig->L4[1].SourPort));
	assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L4[1].DestPortMatchEnable));
	assert_param(IS_ETH_DEST_PORT(pL3L4FilterConfig->L4[1].DestPort));

	// MACFFR
	tmpreg = (heth->Instance)->MACFFR;
    
    if (pL3L4FilterConfig->Enable != DISABLE)
        tmpreg |= ETH_MACFFR_IPFE;
    else
        tmpreg &= ~ETH_MACFFR_IPFE;
    
    (heth->Instance)->MACFFR = tmpreg;
    
	// MACL3L4C0R 
	tmpreg = 0U;
    
    if (pL3L4FilterConfig->L4[0].ProtocolUDP != DISABLE)
        tmpreg |= ETH_MACL3L4C0R_L4PEN0;
    
    if (pL3L4FilterConfig->L4[0].DestPortMatchEnable != DISABLE)
    {
        tmpreg |= ETH_MACL3L4C0R_L4DPM0;
    
        if (pL3L4FilterConfig->L4[0].DestPortInverseMatch != DISABLE)
            tmpreg |= ETH_MACL3L4C0R_L4DPIM0;
    }
    
    if (pL3L4FilterConfig->L4[0].SourPortMatchEnable != DISABLE)
    {
        tmpreg |= ETH_MACL3L4C0R_L4SPM0;
    
        if (pL3L4FilterConfig->L4[0].SourPortInverseMatch != DISABLE)
            tmpreg |= ETH_MACL3L4C0R_L4SPIM0;
    }
    
    if (pL3L4FilterConfig->L3[0].ProtocolIPV6 != DISABLE)
    {
        tmpreg |= ETH_MACL3L4C0R_L3PEN0;
        
        assert_param(IS_ETH_IPV6_ADDR_MASK(pL3L4FilterConfig->L3[0].IPV6.AddrMatch));
        
        tmpreg |= pL3L4FilterConfig->L3[0].IPV6.AddrMatch << ETH_MACL3L4C0R_L3HSBM0_Pos;
    
        if (pL3L4FilterConfig->L3[0].IPV6.DestAddrMatchEnable != DISABLE)
        {
            tmpreg |= ETH_MACL3L4C0R_L3DAM0;
            
            assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L3[0].IPV6.DestAddrInverseMatch));
            
            if (pL3L4FilterConfig->L3[0].IPV6.DestAddrInverseMatch != DISABLE)
                tmpreg |= ETH_MACL3L4C0R_L3DAIM0;
        }
        
        if (pL3L4FilterConfig->L3[0].IPV6.SourAddrMatchEnable != DISABLE)
        {
            tmpreg |= ETH_MACL3L4C0R_L3SAM0;
            
            assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L3[0].IPV6.DestAddrInverseMatch));
            
            if (pL3L4FilterConfig->L3[0].IPV6.SourAddrInverseMatch != DISABLE)
                tmpreg |= ETH_MACL3L4C0R_L3SAIM0;
        }
        
        (heth->Instance)->MACL3L4C0R = tmpreg;
        
        // MACL3A00R  
        (heth->Instance)->MACL3A00R = pL3L4FilterConfig->L3[0].IPV6.Addr[0];
        
        // MACL3A10R  
        (heth->Instance)->MACL3A10R = pL3L4FilterConfig->L3[0].IPV6.Addr[1];
        
        // MACL3A20R  
        (heth->Instance)->MACL3A20R = pL3L4FilterConfig->L3[0].IPV6.Addr[2];
        
        // MACL3A30R  
        (heth->Instance)->MACL3A30R = pL3L4FilterConfig->L3[0].IPV6.Addr[3];
    }
    else
    {
        assert_param(IS_ETH_IPV4_SOUR_ADDR_MASK(pL3L4FilterConfig->L3[0].IPV4.SourAddrMatch));
        assert_param(IS_ETH_IPV4_DEST_ADDR_MASK(pL3L4FilterConfig->L3[0].IPV4.DestAddrMatch));
        
        tmpreg |= pL3L4FilterConfig->L3[0].IPV4.DestAddrMatch << ETH_MACL3L4C0R_L3HDBM0_Pos;
        
        tmpreg |= pL3L4FilterConfig->L3[0].IPV4.SourAddrMatch << ETH_MACL3L4C0R_L3HSBM0_Pos;
        
        if (pL3L4FilterConfig->L3[0].IPV4.DestAddrMatchEnable != DISABLE)
        {
            tmpreg |= ETH_MACL3L4C0R_L3DAM0;
            
            assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L3[0].IPV4.DestAddrInverseMatch));
            
            if (pL3L4FilterConfig->L3[0].IPV4.DestAddrInverseMatch != DISABLE)
                tmpreg |= ETH_MACL3L4C0R_L3DAIM0;
        }
        
        if (pL3L4FilterConfig->L3[0].IPV4.SourAddrMatchEnable != DISABLE)
        {
            tmpreg |= ETH_MACL3L4C0R_L3SAM0;
            
            assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L3[0].IPV4.SourAddrInverseMatch));
            
            if (pL3L4FilterConfig->L3[0].IPV4.SourAddrInverseMatch != DISABLE)
                tmpreg |= ETH_MACL3L4C0R_L3SAIM0;
        }
        
        (heth->Instance)->MACL3L4C0R = tmpreg;
        
        // MACL3A00R  
        (heth->Instance)->MACL3A00R = pL3L4FilterConfig->L3[0].IPV4.SourAddr;
        
        // MACL3A10R  
        (heth->Instance)->MACL3A10R = pL3L4FilterConfig->L3[0].IPV4.DestAddr;
        
        // MACL3A20R  
        (heth->Instance)->MACL3A20R = 0;
        
        // MACL3A30R  
        (heth->Instance)->MACL3A30R = 0;
    }
	
    // MACL4A0R 
    tmpreg = 0;
    
    tmpreg |= pL3L4FilterConfig->L4[0].DestPort << ETH_MACL4A0R_L4DP0_Pos;
    
    tmpreg |= pL3L4FilterConfig->L4[0].SourPort << ETH_MACL4A0R_L4SP0_Pos;
    
    (heth->Instance)->MACL4A0R = tmpreg;
    
	// MACL3L4C1R 
	tmpreg = 0U;
    
    if (pL3L4FilterConfig->L4[1].ProtocolUDP != DISABLE)
        tmpreg |= ETH_MACL3L4C1R_L4PEN1;
    
    if (pL3L4FilterConfig->L4[1].DestPortMatchEnable != DISABLE)
    {
        tmpreg |= ETH_MACL3L4C1R_L4DPM1;
    
        if (pL3L4FilterConfig->L4[1].DestPortInverseMatch != DISABLE)
            tmpreg |= ETH_MACL3L4C1R_L4DPIM1;
    }
    
    if (pL3L4FilterConfig->L4[1].SourPortMatchEnable != DISABLE)
    {
        tmpreg |= ETH_MACL3L4C1R_L4SPM1;
    
        if (pL3L4FilterConfig->L4[1].SourPortInverseMatch != DISABLE)
            tmpreg |= ETH_MACL3L4C1R_L4SPIM1;
    }
    
    if (pL3L4FilterConfig->L3[1].ProtocolIPV6 != DISABLE)
    {
        tmpreg |= ETH_MACL3L4C1R_L3PEN1;
        
        assert_param(IS_ETH_IPV6_ADDR_MASK(pL3L4FilterConfig->L3[1].IPV6.AddrMatch));
        
        tmpreg |= pL3L4FilterConfig->L3[1].IPV6.AddrMatch << ETH_MACL3L4C1R_L3HSBM1_Pos;
    
        if (pL3L4FilterConfig->L3[1].IPV6.DestAddrMatchEnable != DISABLE)
        {
            tmpreg |= ETH_MACL3L4C1R_L3DAM1;
            
            assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L3[1].IPV6.DestAddrInverseMatch));
            
            if (pL3L4FilterConfig->L3[1].IPV6.DestAddrInverseMatch != DISABLE)
                tmpreg |= ETH_MACL3L4C1R_L3DAIM1;
        }
        
        if (pL3L4FilterConfig->L3[1].IPV6.SourAddrMatchEnable != DISABLE)
        {
            tmpreg |= ETH_MACL3L4C1R_L3SAM1;
            
            assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L3[1].IPV6.DestAddrInverseMatch));
            
            if (pL3L4FilterConfig->L3[1].IPV6.SourAddrInverseMatch != DISABLE)
                tmpreg |= ETH_MACL3L4C1R_L3SAIM1;
        }
        
        (heth->Instance)->MACL3L4C1R = tmpreg;
        
        // MACL3A01R  
        (heth->Instance)->MACL3A01R = pL3L4FilterConfig->L3[1].IPV6.Addr[0];
        
        // MACL3A11R  
        (heth->Instance)->MACL3A11R = pL3L4FilterConfig->L3[1].IPV6.Addr[1];
        
        // MACL3A21R  
        (heth->Instance)->MACL3A21R = pL3L4FilterConfig->L3[1].IPV6.Addr[2];
        
        // MACL3A31R  
        (heth->Instance)->MACL3A31R = pL3L4FilterConfig->L3[1].IPV6.Addr[3];
    }
    else
    {
        assert_param(IS_ETH_IPV4_SOUR_ADDR_MASK(pL3L4FilterConfig->L3[1].IPV4.SourAddrMatch));
        assert_param(IS_ETH_IPV4_DEST_ADDR_MASK(pL3L4FilterConfig->L3[1].IPV4.DestAddrMatch));
        
        tmpreg |= pL3L4FilterConfig->L3[1].IPV4.DestAddrMatch << ETH_MACL3L4C1R_L3HDBM1_Pos;
        
        tmpreg |= pL3L4FilterConfig->L3[1].IPV4.SourAddrMatch << ETH_MACL3L4C1R_L3HSBM1_Pos;
        
        if (pL3L4FilterConfig->L3[1].IPV4.DestAddrMatchEnable != DISABLE)
        {
            tmpreg |= ETH_MACL3L4C1R_L3DAM1;
            
            assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L3[1].IPV4.DestAddrInverseMatch));
            
            if (pL3L4FilterConfig->L3[1].IPV4.DestAddrInverseMatch != DISABLE)
                tmpreg |= ETH_MACL3L4C1R_L3DAIM1;
        }
        
        if (pL3L4FilterConfig->L3[1].IPV4.SourAddrMatchEnable != DISABLE)
        {
            tmpreg |= ETH_MACL3L4C1R_L3SAM1;
            
            assert_param(IS_FUNCTIONAL_STATE(pL3L4FilterConfig->L3[1].IPV4.SourAddrInverseMatch));
            
            if (pL3L4FilterConfig->L3[1].IPV4.SourAddrInverseMatch != DISABLE)
                tmpreg |= ETH_MACL3L4C1R_L3SAIM1;
        }
        
        (heth->Instance)->MACL3L4C1R = tmpreg;
        
        // MACL3A01R  
        (heth->Instance)->MACL3A01R = pL3L4FilterConfig->L3[1].IPV4.SourAddr;
        
        // MACL3A11R  
        (heth->Instance)->MACL3A11R = pL3L4FilterConfig->L3[1].IPV4.DestAddr;
        
        // MACL3A21R  
        (heth->Instance)->MACL3A21R = 0;
        
        // MACL3A31R  
        (heth->Instance)->MACL3A31R = 0;
    }
	
    // MACL4A1R 
    tmpreg = 0;
    
    tmpreg |= pL3L4FilterConfig->L4[1].DestPort << ETH_MACL4A1R_L4DP1_Pos;
    
    tmpreg |= pL3L4FilterConfig->L4[1].SourPort << ETH_MACL4A1R_L4SP1_Pos;
    
    (heth->Instance)->MACL4A1R = tmpreg;
    
	return HAL_OK;  
}

HAL_StatusTypeDef HAL_ETH_SetL3L4FilterDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitL3L4FilterDefaultParamter(heth);
    
    return HAL_ETH_SetL3L4FilterConfig(heth);
}

HAL_StatusTypeDef HAL_ETH_InitFilterDefaultParamter(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitAddrFilterDefaultParamter(heth);
    HAL_ETH_InitVLANFilterDefaultParamter(heth);
    HAL_ETH_InitL3L4FilterDefaultParamter(heth);
    heth->FilterConfig.DropNonTCPUDP = DISABLE;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetFilterConfig(ETH_HandleTypeDef *heth)
{
	if (heth == NULL)
		return (HAL_ERROR);

    if (HAL_ETH_GetAddrFilterConfig(heth) != HAL_OK)
		return (HAL_ERROR);
	
    if (HAL_ETH_GetVLANFilterConfig(heth) != HAL_OK)
		return (HAL_ERROR);
	
    if (HAL_ETH_GetL3L4FilterConfig(heth) != HAL_OK)
		return (HAL_ERROR);
    
    if (heth->Instance->MACFFR & ETH_MACFFR_DNTU)
        heth->FilterConfig.DropNonTCPUDP = ENABLE;
    else
        heth->FilterConfig.DropNonTCPUDP = DISABLE;
    
	return HAL_OK;
}


//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_ConfigMAC(ETH_HandleTypeDef *heth, ETH_MACInitTypeDef *pMACConfig);
//	功能 ：	配置MAC
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			dmaconf：配置结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_SetFilterConfig(ETH_HandleTypeDef *heth)
{
	assert_param(IS_FUNCTIONAL_STATE(heth->FilterConfig.DropNonTCPUDP));
    
	if (heth == NULL)
		return (HAL_ERROR);
    
    if (HAL_ETH_SetAddrFilterConfig(heth) != HAL_OK)
		return (HAL_ERROR);
    
    if (HAL_ETH_SetVLANFilterConfig(heth) != HAL_OK)
		return (HAL_ERROR);
    
    if (HAL_ETH_SetL3L4FilterConfig(heth) != HAL_OK)
		return (HAL_ERROR);
    
    if (heth->FilterConfig.DropNonTCPUDP == DISABLE)
        heth->Instance->MACFFR &= ~ETH_MACFFR_DNTU;
    else
        heth->Instance->MACFFR |= ETH_MACFFR_DNTU;
    
	return HAL_OK;  
}

HAL_StatusTypeDef HAL_ETH_SetFilterDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitFilterDefaultParamter(heth);
    
    return HAL_ETH_SetFilterConfig(heth);
}

//	****************************************************************************
//  
//                              VLAN
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_InitVLANDefaultParamter(ETH_HandleTypeDef *heth)
{
    ETH_VLANTypeDef *pVLANConfig = &heth->MACConfig.VLAN;
    
	pVLANConfig->Enable = DISABLE;
	pVLANConfig->Mode = ETH_VLAN_MODE_NONE;
	pVLANConfig->SVLAN = DISABLE;
	pVLANConfig->Tag = 0;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetVLANConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_VLANTypeDef *pVLANConfig = &heth->MACConfig.VLAN;

	if (heth == NULL)
		return (HAL_ERROR);

    memset((void *)pVLANConfig, 0, sizeof(ETH_VLANTypeDef));
	
    // MACVTIRR
	tmpreg = (heth->Instance)->MACVTIRR;
    
    if (tmpreg & ETH_MACVTIRR_CSVL)
        pVLANConfig->SVLAN = ENABLE;
    else
        pVLANConfig->SVLAN = DISABLE;
    
    if (tmpreg & ETH_MACVTIRR_VLP)
        pVLANConfig->Enable = ENABLE;
    else
        pVLANConfig->Enable = DISABLE;
    
    pVLANConfig->Mode = (tmpreg & ETH_MACVTIRR_VLC) >> ETH_MACVTIRR_VLC_Pos;
    
    pVLANConfig->Tag = (tmpreg & ETH_MACVTIRR_VLT) >> ETH_MACVTIRR_VLT_Pos;
    
	return HAL_OK;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_ConfigMAC(ETH_HandleTypeDef *heth, ETH_MACInitTypeDef *pMACConfig);
//	功能 ：	配置MAC
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			dmaconf：配置结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_SetVLANConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_VLANTypeDef *pVLANConfig = &heth->MACConfig.VLAN;

	if (heth == NULL)
		return (HAL_ERROR);
    
	assert_param(IS_FUNCTIONAL_STATE(pVLANConfig->Enable));
	assert_param(IS_FUNCTIONAL_STATE(pVLANConfig->SVLAN));
	assert_param(IS_ETH_VLAN_MODE(pVLANConfig->Mode));
	assert_param(IS_ETH_VLAN_TAG(pVLANConfig->Tag));

    // MACVTIRR 
    tmpreg = 0;
    
    if (pVLANConfig->SVLAN != DISABLE)
        tmpreg |= ETH_MACVTIRR_CSVL;
    
    if (pVLANConfig->Enable != DISABLE)
        tmpreg |= ETH_MACVTIRR_VLP;
    
    tmpreg |= pVLANConfig->Mode << ETH_MACVTIRR_VLC_Pos;
    
    tmpreg |= pVLANConfig->Tag << ETH_MACVTIRR_VLT_Pos;
    
    (heth->Instance)->MACVTIRR = (uint32_t)tmpreg;
    
	return HAL_OK;  
}

HAL_StatusTypeDef HAL_ETH_SetVLANDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitVLANDefaultParamter(heth);
    
    return HAL_ETH_SetVLANConfig(heth);
}

//	****************************************************************************
//  
//                              MAC
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_InitMACDefaultParamter(ETH_HandleTypeDef *heth)
{
	// MAC配置默认值
    
    heth->MACConfig.SourceAddrControl = ETH_SOURCE_ADDRESS_REPLACE_ADDR0;           // 配置：源地址替换MAC地址1寄存器
	heth->MACConfig.Support2KPacket = ENABLE;							            // 禁止：2K数据包的IEEE 802.3as 支持
	heth->MACConfig.CRCStripTypePacket = ENABLE;					                // 禁止：类型帧的 CRC 去除
	heth->MACConfig.Watchdog = DISABLE;											    // 使能：接收看门狗
	heth->MACConfig.WatchdogTimeout = 1523U;										// 配置：接收看门狗超时
	heth->MACConfig.Jabber = DISABLE;												// 使能：发送jabber定时器
	heth->MACConfig.JumboPacket = ENABLE;									        // 禁止：巨型数据包使能
	heth->MACConfig.InterFrameGap = ETH_INTERFRAME_GAP_96BIT;                       // 配置：发送帧间间隔96位
	heth->MACConfig.CarrierSense = DISABLE;									        // 使能：载波侦听
	heth->MACConfig.ReceiveOwn = ENABLE;										    // 使能：接收自身
	heth->MACConfig.LoopbackMode = DISABLE;								            // 禁止：回送模式
    heth->MACConfig.ChecksumOffload = ENABLE;                                       // 配置：接收帧 TCP/UDP/ICMP 标头的 IPv4 校验和检查
	heth->MACConfig.RetryTransmission = ENABLE;						                // 使能：传输重试
	heth->MACConfig.AutoPadCRCStrip = ENABLE;				                        // 禁止：自动去除PAD和FCS字段
	heth->MACConfig.BackOffLimit = ETH_BACK_OFF_LIMIT_10;						    // 配置：后退限制最大10位
	heth->MACConfig.DeferralCheck = DISABLE;								        // 禁止：检查延迟
	heth->MACConfig.PreambleLen = ETH_PREAMBLE_LEN_7B;							    // 禁止：报头长度7字节

    HAL_ETH_InitVLANDefaultParamter(heth);
    
    return HAL_OK;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_GetMACConfig(ETH_HandleTypeDef *heth, ETH_MACInitTypeDef *pMACConfig);
//	功能 ：	取MAC配置
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//	输出 ：	pMACConfig：配置结构体指针；
//	返回 ：	HAL_OK：取配置成功；
//			HAL_ERROR：取配置失败；
//	备注 ：	
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_GetMACConfig(ETH_HandleTypeDef *heth)
{
	uint32_t err;
	volatile uint32_t tmpreg = 0;
    ETH_MACInitTypeDef *pMACConfig = &heth->MACConfig;

	if (heth == NULL)
		return (HAL_ERROR);

    memset((void *)pMACConfig, 0, sizeof(ETH_MACInitTypeDef));
	err = 0;
	
	// MACCR
	tmpreg = (heth->Instance)->MACCR;
	
	if ((tmpreg & ETH_MACCR_SARC_1) == 0)
		pMACConfig->SourceAddrControl = ETH_SOURCE_ADDRESS_DISABLE;
	else if ((tmpreg & ETH_MACCR_SARC) == (ETH_MACCR_SARC_1))
		pMACConfig->SourceAddrControl = ETH_SOURCE_ADDRESS_INSERT_ADDR0;
	else if ((tmpreg & ETH_MACCR_SARC) == (ETH_MACCR_SARC_2 | ETH_MACCR_SARC_1))
		pMACConfig->SourceAddrControl = ETH_SOURCE_ADDRESS_INSERT_ADDR1;
	else if ((tmpreg & ETH_MACCR_SARC) == (ETH_MACCR_SARC_1 | ETH_MACCR_SARC_0))
		pMACConfig->SourceAddrControl = ETH_SOURCE_ADDRESS_REPLACE_ADDR0;
	else if ((tmpreg & ETH_MACCR_SARC) == (ETH_MACCR_SARC_2 | ETH_MACCR_SARC_1 | ETH_MACCR_SARC_0))
		pMACConfig->SourceAddrControl = ETH_SOURCE_ADDRESS_REPLACE_ADDR1;
	
	if (tmpreg & ETH_MACCR_S2KP)
        pMACConfig->Support2KPacket = ENABLE;
    else
        pMACConfig->Support2KPacket = DISABLE;
    
	if (tmpreg & ETH_MACCR_CSTF)
        pMACConfig->CRCStripTypePacket = ENABLE;
    else
        pMACConfig->CRCStripTypePacket = DISABLE;
    
	if (((tmpreg & ETH_MACCR_WD) == 0) && ((heth->Instance)->MACWTR & ETH_MACWTR_PWE))
        pMACConfig->Watchdog = ENABLE;
    else
        pMACConfig->Watchdog = DISABLE;
    
	if (tmpreg & ETH_MACCR_JD)
        pMACConfig->Jabber = ENABLE;
    else
        pMACConfig->Jabber = DISABLE;
    
	if (tmpreg & ETH_MACCR_JE)
        pMACConfig->JumboPacket = ENABLE;
    else
        pMACConfig->JumboPacket = DISABLE;
    
	if ((tmpreg & ETH_MACCR_IFG) == 0)
        pMACConfig->InterFrameGap = ETH_INTERFRAME_GAP_96BIT;
	else if ((tmpreg & ETH_MACCR_IFG) == ETH_MACCR_IFG_0)
        pMACConfig->InterFrameGap = ETH_INTERFRAME_GAP_88BIT;
	else if ((tmpreg & ETH_MACCR_IFG) == ETH_MACCR_IFG_1)
        pMACConfig->InterFrameGap = ETH_INTERFRAME_GAP_80BIT;
	else if ((tmpreg & ETH_MACCR_IFG) == (ETH_MACCR_IFG_1 | ETH_MACCR_IFG_0))
        pMACConfig->InterFrameGap = ETH_INTERFRAME_GAP_72BIT;
	else if ((tmpreg & ETH_MACCR_IFG) == ETH_MACCR_IFG_2)
        pMACConfig->InterFrameGap = ETH_INTERFRAME_GAP_64BIT;
	else if ((tmpreg & ETH_MACCR_IFG) == (ETH_MACCR_IFG_2 | ETH_MACCR_IFG_0))
        pMACConfig->InterFrameGap = ETH_INTERFRAME_GAP_56BIT;
	else if ((tmpreg & ETH_MACCR_IFG) == (ETH_MACCR_IFG_2 | ETH_MACCR_IFG_1))
        pMACConfig->InterFrameGap = ETH_INTERFRAME_GAP_48BIT;
	else if ((tmpreg & ETH_MACCR_IFG) == (ETH_MACCR_IFG_2 | ETH_MACCR_IFG_1 | ETH_MACCR_IFG_0))
        pMACConfig->InterFrameGap = ETH_INTERFRAME_GAP_40BIT;
    
	if (tmpreg & ETH_MACCR_CSD)
        pMACConfig->JumboPacket = DISABLE;
    else
        pMACConfig->JumboPacket = ENABLE;
    
	if (tmpreg & ETH_MACCR_ROD)
        pMACConfig->ReceiveOwn = DISABLE;
    else
        pMACConfig->ReceiveOwn = ENABLE;
    
	if (tmpreg & ETH_MACCR_LM)
        pMACConfig->LoopbackMode = ENABLE;
    else
        pMACConfig->LoopbackMode = DISABLE;
    
	if (tmpreg & ETH_MACCR_IPCO)
        pMACConfig->ChecksumOffload = ENABLE;
    else
        pMACConfig->ChecksumOffload = DISABLE;
    
	if (tmpreg & ETH_MACCR_DR)
        pMACConfig->RetryTransmission = DISABLE;
    else
        pMACConfig->RetryTransmission = ENABLE;
    
	if (tmpreg & ETH_MACCR_APCS)
        pMACConfig->AutoPadCRCStrip = ENABLE;
    else
        pMACConfig->AutoPadCRCStrip = DISABLE;
    
	if ((tmpreg & ETH_MACCR_BL) == 0)
        pMACConfig->BackOffLimit = ETH_BACK_OFF_LIMIT_10;
    else if ((tmpreg & ETH_MACCR_BL) == ETH_MACCR_BL_0)
        pMACConfig->BackOffLimit = ETH_BACK_OFF_LIMIT_8;
    else if ((tmpreg & ETH_MACCR_BL) == ETH_MACCR_BL_1)
        pMACConfig->BackOffLimit = ETH_BACK_OFF_LIMIT_4;
    else if ((tmpreg & ETH_MACCR_BL) == (ETH_MACCR_BL_1 | ETH_MACCR_BL_0))
        pMACConfig->BackOffLimit = ETH_BACK_OFF_LIMIT_1;
    
	if (tmpreg & ETH_MACCR_DC)
        pMACConfig->DeferralCheck = ENABLE;
    else
        pMACConfig->DeferralCheck = DISABLE;
    
	if ((tmpreg & ETH_MACCR_PRELEN) == 0)
        pMACConfig->PreambleLen = ETH_PREAMBLE_LEN_7B;
    else if ((tmpreg & ETH_MACCR_BL) == ETH_MACCR_PRELEN_0)
        pMACConfig->PreambleLen = ETH_PREAMBLE_LEN_5B;
    else if ((tmpreg & ETH_MACCR_BL) == ETH_MACCR_PRELEN_1)
        pMACConfig->PreambleLen = ETH_PREAMBLE_LEN_3B;
    else
        err = 1;
    
    // MACWTR
	pMACConfig->WatchdogTimeout = ((heth->Instance)->MACWTR & ETH_MACWTR_WTO) >> ETH_MACWTR_WTO_Pos;
    
    err |= HAL_ETH_GetVLANConfig(heth);
    
	if (err == 0)
		return HAL_OK;
	else
		return HAL_ERROR;
}


//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_ConfigMAC(ETH_HandleTypeDef *heth, ETH_MACInitTypeDef *pMACConfig);
//	功能 ：	配置MAC
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			dmaconf：配置结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_SetMACConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg = 0;
    ETH_MACInitTypeDef *pMACConfig = &heth->MACConfig;

	if (heth == NULL)
		return (HAL_ERROR);
    
	assert_param(IS_ETH_SOURCE_ADDR_CONTROL(pMACConfig->SourceAddrControl));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->Support2KPacket));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->CRCStripTypePacket));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->Watchdog));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->Jabber));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->JumboPacket));
	assert_param(IS_ETH_INTERFRAME_GAP(pMACConfig->InterFrameGap));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->CarrierSense));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->ReceiveOwn));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->LoopbackMode));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->ChecksumOffload));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->RetryTransmission));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->AutoPadCRCStrip));
	assert_param(IS_ETH_BACK_OFF_LIMIT(pMACConfig->BackOffLimit));
	assert_param(IS_FUNCTIONAL_STATE(pMACConfig->DeferralCheck));
	assert_param(IS_ETH_PREAMBLE_LEN(pMACConfig->PreambleLen));

	// MACCR
	tmpreg = (heth->Instance)->MACCR;
	tmpreg &= 0x8520c90c;

    if (pMACConfig->SourceAddrControl == ETH_SOURCE_ADDRESS_DISABLE)
        tmpreg |= 0U;
    if (pMACConfig->SourceAddrControl == ETH_SOURCE_ADDRESS_INSERT_ADDR0)
        tmpreg |= ETH_MACCR_SARC_1;
    if (pMACConfig->SourceAddrControl == ETH_SOURCE_ADDRESS_INSERT_ADDR1)
        tmpreg |= ETH_MACCR_SARC_2 | ETH_MACCR_SARC_1;
    if (pMACConfig->SourceAddrControl == ETH_SOURCE_ADDRESS_REPLACE_ADDR0)
        tmpreg |= ETH_MACCR_SARC_1 | ETH_MACCR_SARC_0;
    if (pMACConfig->SourceAddrControl == ETH_SOURCE_ADDRESS_REPLACE_ADDR1)
        tmpreg |= ETH_MACCR_SARC_2 | ETH_MACCR_SARC_1 | ETH_MACCR_SARC_0;
    
    if (pMACConfig->Support2KPacket != DISABLE)
        tmpreg |= ETH_MACCR_S2KP;
    
    if (pMACConfig->CRCStripTypePacket != DISABLE)
        tmpreg |= ETH_MACCR_CSTF;
    
    if (pMACConfig->Watchdog == DISABLE)
        tmpreg |= ETH_MACCR_WD;
        
    if (pMACConfig->Jabber != DISABLE)
        tmpreg |= ETH_MACCR_JD;
    
    if (pMACConfig->JumboPacket != DISABLE)
        tmpreg |= ETH_MACCR_JE;
    
    if (pMACConfig->InterFrameGap == ETH_INTERFRAME_GAP_96BIT)
        tmpreg |= 0U;
    else if (pMACConfig->InterFrameGap == ETH_INTERFRAME_GAP_88BIT)
        tmpreg |= ETH_MACCR_IFG_0;
    else if (pMACConfig->InterFrameGap == ETH_INTERFRAME_GAP_80BIT)
        tmpreg |= ETH_MACCR_IFG_1;
    else if (pMACConfig->InterFrameGap == ETH_INTERFRAME_GAP_72BIT)
        tmpreg |= ETH_MACCR_IFG_1 | ETH_MACCR_IFG_0;
    else if (pMACConfig->InterFrameGap == ETH_INTERFRAME_GAP_64BIT)
        tmpreg |= ETH_MACCR_IFG_2;
    else if (pMACConfig->InterFrameGap == ETH_INTERFRAME_GAP_56BIT)
        tmpreg |= ETH_MACCR_IFG_2 | ETH_MACCR_IFG_0;
    else if (pMACConfig->InterFrameGap == ETH_INTERFRAME_GAP_48BIT)
        tmpreg |= ETH_MACCR_IFG_2 | ETH_MACCR_IFG_1;
    else if (pMACConfig->InterFrameGap == ETH_INTERFRAME_GAP_40BIT)
        tmpreg |= ETH_MACCR_IFG_2 | ETH_MACCR_IFG_1 | ETH_MACCR_IFG_0;
    
    if (pMACConfig->CarrierSense == DISABLE)
        tmpreg |= ETH_MACCR_CSD;
    
    if (pMACConfig->ReceiveOwn == DISABLE)
        tmpreg |= ETH_MACCR_ROD;
    
    if (pMACConfig->LoopbackMode != DISABLE)
        tmpreg |= ETH_MACCR_LM;
    
    if (pMACConfig->ChecksumOffload != DISABLE)
        tmpreg |= ETH_MACCR_IPCO;
    
    if (pMACConfig->RetryTransmission == DISABLE)
        tmpreg |= ETH_MACCR_DR;
    
    if (pMACConfig->AutoPadCRCStrip != DISABLE)
        tmpreg |= ETH_MACCR_APCS;
    
    if (pMACConfig->BackOffLimit == ETH_BACK_OFF_LIMIT_10)
        tmpreg |= 0U;
    else if (pMACConfig->BackOffLimit == ETH_BACK_OFF_LIMIT_8)
        tmpreg |= ETH_MACCR_BL_0;
    else if (pMACConfig->BackOffLimit == ETH_BACK_OFF_LIMIT_4)
        tmpreg |= ETH_MACCR_BL_1;
    else if (pMACConfig->BackOffLimit == ETH_BACK_OFF_LIMIT_1)
        tmpreg |= ETH_MACCR_BL_1 | ETH_MACCR_BL_1;
    
    if (pMACConfig->DeferralCheck != DISABLE)
        tmpreg |= ETH_MACCR_DC;
    
    if (pMACConfig->PreambleLen == ETH_PREAMBLE_LEN_7B)
        tmpreg |= 0U;
    else if (pMACConfig->PreambleLen == ETH_PREAMBLE_LEN_5B)
        tmpreg |= ETH_MACCR_PRELEN_0;
    else if (pMACConfig->PreambleLen == ETH_PREAMBLE_LEN_3B)
        tmpreg |= ETH_MACCR_PRELEN_1;
    
	(heth->Instance)->MACCR = (uint32_t)tmpreg;

    // MACWTR
    if (pMACConfig->Watchdog)
        (heth->Instance)->MACWTR = ETH_MACWTR_PWE | ((pMACConfig->WatchdogTimeout << ETH_MACWTR_WTO_Pos) & ETH_MACWTR_WTO);
    else
        (heth->Instance)->MACWTR = (pMACConfig->WatchdogTimeout << ETH_MACWTR_WTO_Pos) & ETH_MACWTR_WTO;
    
    // VLAN
    HAL_ETH_SetVLANConfig(heth);
    
	return HAL_OK;  
}

HAL_StatusTypeDef HAL_ETH_SetMACDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitMACDefaultParamter(heth);
    
    return HAL_ETH_SetMACConfig(heth);
}

HAL_StatusTypeDef HAL_ETH_InitDMADefaultParamter(ETH_HandleTypeDef *heth)
{
//    memset((void *)&heth->DMAConfig, 0, sizeof(ETH_DMAInitTypeDef));
    
	// DMA配置默认值
	heth->DMAConfig.DropTCPIPChecksumErrorFrame = ENABLE;			//禁止：丢弃TCP/IP校验错误帧
	heth->DMAConfig.ReceiveStoreForward = ENABLE;							//使能：接收存储并转发
	heth->DMAConfig.FlushReceivedFrame = ENABLE;				//禁止：禁止刷新接收帧
	heth->DMAConfig.TransmitStoreForward = ENABLE;  						//使能：发送存储并并转发
	heth->DMAConfig.TransmitThresholdControl = ETH_TRANSMIT_THRESHOLD_CONTROL_64BYTES;				//配置：发送阈值控制：64字节
	heth->DMAConfig.ForwardErrorFrames = DISABLE;							//禁止：转发错误帧
	heth->DMAConfig.ForwardUndersizedGoodFrames = DISABLE;			//禁止：转发过小的好帧
	heth->DMAConfig.ReceiveThresholdControl = ETH_RECEIVED_THRESHOLD_CONTROL_64BYTES;					//配置：接收阈值控制：64字节
	heth->DMAConfig.SecondFrameOperate = ENABLE;							//使能：处理第二个帧

	heth->DMAConfig.MixedBurst = DISABLE;											//禁止：混合突发
	heth->DMAConfig.AddressAlignedBeats = ENABLE;							//使能：地址对齐节拍
	heth->DMAConfig.PBL8xMode = DISABLE;												//禁止： 8xPBL 模式
	heth->DMAConfig.UseSeparatePBL = ENABLE;									//禁止： 使用单独的 PBL
	heth->DMAConfig.RxDMABurstLen = ETH_RX_DMA_BURST_LEN_32BEAT;								//配置： DMA突发接收长度:32字节
	heth->DMAConfig.FixedBurst = ENABLE;											//使能：固定突发
	heth->DMAConfig.RxTxPriorityRatio = ETH_RX_TX_PRIORITY_RATIO_4_1;								//配置： Rx Tx 优先级比
	heth->DMAConfig.TxDMABurstLen = ETH_TX_DMA_BURST_LEN_32BEAT;								//配置： DMA突发发送长度：32字节
	heth->DMAConfig.EnhancedDescriptorFormat = ENABLE;					//使能：增强描述符格式
	heth->DMAConfig.DescriptorSkipLen = 0x02;														//配置：描述符跳过长度：0字
	heth->DMAConfig.DMAArbitration = ETH_DMA_ARBITRATION_ROUNDROBIN;								//配置： DMA仲裁，循环调度
    
    return HAL_OK;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_GetDMAConfig(ETH_HandleTypeDef *heth, ETH_DMAInitTypeDef *pDMAConfig);
//	功能 ：	取DMA配置
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//	输出 ：	pDMAConfig：配置结构体指针；
//	返回 ：	HAL_OK：取配置成功；
//			HAL_ERROR：取配置失败；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_GetDMAConfig(ETH_HandleTypeDef *heth)
{
	uint32_t err;
	volatile uint32_t tmpreg = 0;
    ETH_DMAInitTypeDef *pDMAConfig = &heth->DMAConfig;

	if (heth == NULL)
		return (HAL_ERROR);
    
	err = 0;
	
	// DMAOMR
	tmpreg = (heth->Instance)->DMAOMR;
	
    if (tmpreg & ETH_DMAOMR_DTCEFD)
        pDMAConfig->DropTCPIPChecksumErrorFrame = ENABLE;
    else
        pDMAConfig->DropTCPIPChecksumErrorFrame = DISABLE;
	
    if (tmpreg & ETH_DMAOMR_RSF)
        pDMAConfig->ReceiveStoreForward = ENABLE;
    else
        pDMAConfig->ReceiveStoreForward = DISABLE;

    if (tmpreg & ETH_DMAOMR_DFRF)
        pDMAConfig->FlushReceivedFrame = DISABLE;
    else
        pDMAConfig->FlushReceivedFrame = ENABLE;
	
    if (tmpreg & ETH_DMAOMR_TSF)
        pDMAConfig->TransmitStoreForward = ENABLE;
    else
        pDMAConfig->TransmitStoreForward = DISABLE;

    if ((tmpreg & ETH_DMAOMR_TTC) == 0)
        pDMAConfig->TransmitThresholdControl = ETH_TRANSMIT_THRESHOLD_CONTROL_64BYTES;
    else if ((tmpreg & ETH_DMAOMR_TTC) == ETH_DMAOMR_TTC_0)
        pDMAConfig->TransmitThresholdControl = ETH_TRANSMIT_THRESHOLD_CONTROL_128BYTES;
    else if ((tmpreg & ETH_DMAOMR_TTC) == ETH_DMAOMR_TTC_1)
        pDMAConfig->TransmitThresholdControl = ETH_TRANSMIT_THRESHOLD_CONTROL_192BYTES;
    else if ((tmpreg & ETH_DMAOMR_TTC) == (ETH_DMAOMR_TTC_1 | ETH_DMAOMR_TTC_0))
        pDMAConfig->TransmitThresholdControl = ETH_TRANSMIT_THRESHOLD_CONTROL_256BYTES;
    else if ((tmpreg & ETH_DMAOMR_TTC) == ETH_DMAOMR_TTC_2)
        pDMAConfig->TransmitThresholdControl = ETH_TRANSMIT_THRESHOLD_CONTROL_40BYTES;
    else if ((tmpreg & ETH_DMAOMR_TTC) == (ETH_DMAOMR_TTC_2 | ETH_DMAOMR_TTC_0))
        pDMAConfig->TransmitThresholdControl = ETH_TRANSMIT_THRESHOLD_CONTROL_32BYTES;
    else if ((tmpreg & ETH_DMAOMR_TTC) == (ETH_DMAOMR_TTC_2 | ETH_DMAOMR_TTC_1))
        pDMAConfig->TransmitThresholdControl = ETH_TRANSMIT_THRESHOLD_CONTROL_24BYTES;
    else if ((tmpreg & ETH_DMAOMR_TTC) == (ETH_DMAOMR_TTC_2 | ETH_DMAOMR_TTC_1 | ETH_DMAOMR_TTC_0))
        pDMAConfig->TransmitThresholdControl = ETH_TRANSMIT_THRESHOLD_CONTROL_16BYTES;
    
    if (tmpreg & ETH_DMAOMR_FEF)
        pDMAConfig->ForwardErrorFrames = ENABLE;
    else
        pDMAConfig->ForwardErrorFrames = DISABLE;
	
    if (tmpreg & ETH_DMAOMR_FUGF)
        pDMAConfig->ForwardUndersizedGoodFrames = ENABLE;
    else
        pDMAConfig->ForwardUndersizedGoodFrames = DISABLE;
    
    if ((tmpreg & ETH_DMAOMR_RTC) == 0)
        pDMAConfig->ReceiveThresholdControl = ETH_RECEIVED_THRESHOLD_CONTROL_64BYTES;
    else if ((tmpreg & ETH_DMAOMR_RTC) == ETH_DMAOMR_RTC_0)
        pDMAConfig->ReceiveThresholdControl = ETH_RECEIVED_THRESHOLD_CONTROL_32BYTES;
    else if ((tmpreg & ETH_DMAOMR_RTC) == ETH_DMAOMR_RTC_1)
        pDMAConfig->ReceiveThresholdControl = ETH_RECEIVED_THRESHOLD_CONTROL_96BYTES;
    else if ((tmpreg & ETH_DMAOMR_RTC) == (ETH_DMAOMR_RTC_1 | ETH_DMAOMR_RTC_0))
        pDMAConfig->ReceiveThresholdControl = ETH_RECEIVED_THRESHOLD_CONTROL_128BYTES;
    
	
    if (tmpreg & ETH_DMAOMR_OSF)
        pDMAConfig->SecondFrameOperate = ENABLE;
    else
        pDMAConfig->SecondFrameOperate = DISABLE;
	
	// DMABMR
	tmpreg = (heth->Instance)->DMABMR;
	
    if (tmpreg & ETH_DMABMR_MB)
        pDMAConfig->MixedBurst = ENABLE;
    else
        pDMAConfig->MixedBurst = DISABLE;
	
    if (tmpreg & ETH_DMABMR_AAB)
        pDMAConfig->AddressAlignedBeats = ENABLE;
    else
        pDMAConfig->AddressAlignedBeats = DISABLE;
	
    if (tmpreg & ETH_DMABMR_EPM)
        pDMAConfig->PBL8xMode = ENABLE;
    else
        pDMAConfig->PBL8xMode = DISABLE;
	
    if (tmpreg & ETH_DMABMR_USP)
        pDMAConfig->UseSeparatePBL = ENABLE;
    else
        pDMAConfig->UseSeparatePBL = DISABLE;
    
    if ((tmpreg & ETH_DMABMR_RDP) == ETH_DMABMR_RDP_0)
        pDMAConfig->RxDMABurstLen = ETH_RX_DMA_BURST_LEN_1BEAT;
    else if ((tmpreg & ETH_DMABMR_RDP) == ETH_DMABMR_RDP_1)
        pDMAConfig->RxDMABurstLen = ETH_RX_DMA_BURST_LEN_2BEAT;
    else if ((tmpreg & ETH_DMABMR_RDP) == ETH_DMABMR_RDP_2)
        pDMAConfig->RxDMABurstLen = ETH_RX_DMA_BURST_LEN_4BEAT;
    else if ((tmpreg & ETH_DMABMR_RDP) == (ETH_DMABMR_RDP_3))
        pDMAConfig->RxDMABurstLen = ETH_RX_DMA_BURST_LEN_8BEAT;
    else if ((tmpreg & ETH_DMABMR_RDP) == (ETH_DMABMR_RDP_4))
        pDMAConfig->RxDMABurstLen = ETH_RX_DMA_BURST_LEN_16BEAT;
    else if ((tmpreg & ETH_DMABMR_RDP) == (ETH_DMABMR_RDP_5))
        pDMAConfig->RxDMABurstLen = ETH_RX_DMA_BURST_LEN_32BEAT;
    else
        err = 1;
	
    if (tmpreg & ETH_DMABMR_FB)
        pDMAConfig->FixedBurst = ENABLE;
    else
        pDMAConfig->FixedBurst = DISABLE;
    
    if ((tmpreg & ETH_DMAOMR_RTC) == 0)
        pDMAConfig->RxTxPriorityRatio = ETH_RX_TX_PRIORITY_RATIO_1_1;
    else if ((tmpreg & ETH_DMAOMR_RTC) == ETH_DMABMR_PM_0)
        pDMAConfig->RxTxPriorityRatio = ETH_RX_TX_PRIORITY_RATIO_2_1;
    else if ((tmpreg & ETH_DMAOMR_RTC) == ETH_DMABMR_PM_1)
        pDMAConfig->RxTxPriorityRatio = ETH_RX_TX_PRIORITY_RATIO_3_1;
    else if ((tmpreg & ETH_DMAOMR_RTC) == (ETH_DMABMR_PM_1 | ETH_DMABMR_PM_0))
        pDMAConfig->RxTxPriorityRatio = ETH_RX_TX_PRIORITY_RATIO_4_1;
    else
        err = 1;
    
    if ((tmpreg & ETH_DMABMR_RDP) == ETH_DMABMR_PBL_0)
        pDMAConfig->TxDMABurstLen = ETH_RX_DMA_BURST_LEN_1BEAT;
    else if ((tmpreg & ETH_DMABMR_RDP) == ETH_DMABMR_PBL_1)
        pDMAConfig->TxDMABurstLen = ETH_RX_DMA_BURST_LEN_2BEAT;
    else if ((tmpreg & ETH_DMABMR_RDP) == ETH_DMABMR_PBL_2)
        pDMAConfig->TxDMABurstLen = ETH_RX_DMA_BURST_LEN_4BEAT;
    else if ((tmpreg & ETH_DMABMR_RDP) == (ETH_DMABMR_PBL_3))
        pDMAConfig->TxDMABurstLen = ETH_RX_DMA_BURST_LEN_8BEAT;
    else if ((tmpreg & ETH_DMABMR_RDP) == (ETH_DMABMR_PBL_4))
        pDMAConfig->TxDMABurstLen = ETH_RX_DMA_BURST_LEN_16BEAT;
    else if ((tmpreg & ETH_DMABMR_RDP) == (ETH_DMABMR_PBL_5))
        pDMAConfig->TxDMABurstLen = ETH_RX_DMA_BURST_LEN_32BEAT;
    else
        err = 1;
	
    if (tmpreg & ETH_DMABMR_EDFE)
        pDMAConfig->EnhancedDescriptorFormat = ENABLE;
    else
        pDMAConfig->EnhancedDescriptorFormat = DISABLE;
    
	pDMAConfig->EnhancedDescriptorFormat = (tmpreg & ETH_DMABMR_EDFE) >> ETH_DMABMR_EDFE_Pos;
	
	pDMAConfig->DescriptorSkipLen = (tmpreg & ETH_DMABMR_DSL) >> ETH_DMABMR_DSL_Pos;
	
    if (tmpreg & ETH_DMABMR_DA)
        pDMAConfig->DMAArbitration = ETH_DMA_ARBITRATION_RX_PRIOR_TX;
    else
        pDMAConfig->DMAArbitration = ETH_DMA_ARBITRATION_ROUNDROBIN;
    
	if (err == 0)
		return HAL_OK;
	else
		return HAL_ERROR;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_ConfigDMA(ETH_HandleTypeDef *heth, ETH_DMAInitTypeDef *pDMAConfig);
//	功能 ：	配置DMA
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			pDMAConfig：配置结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_SetDMAConfig(ETH_HandleTypeDef *heth)
{
	uint32_t tmpreg = 0;
    ETH_DMAInitTypeDef *pDMAConfig = &heth->DMAConfig;

	if (heth == NULL)
		return (HAL_ERROR);

	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->DropTCPIPChecksumErrorFrame));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->ReceiveStoreForward));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->FlushReceivedFrame));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->TransmitStoreForward));
	assert_param(IS_ETH_TRANSMIT_THRESHOLD_CONTROL(pDMAConfig->TransmitThresholdControl));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->ForwardErrorFrames));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->ForwardUndersizedGoodFrames));
	assert_param(IS_ETH_RECEIVED_THRESHOLD_CONTROL(pDMAConfig->ReceiveThresholdControl));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->SecondFrameOperate));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->MixedBurst));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->AddressAlignedBeats));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->PBL8xMode));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->UseSeparatePBL));
	assert_param(IS_ETH_RX_DMA_BURST_LEN(pDMAConfig->RxDMABurstLen));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->FixedBurst));
	assert_param(IS_ETH_RX_TX_PRIORITY_RATIO(pDMAConfig->RxTxPriorityRatio));
	assert_param(IS_ETH_TX_DMA_BURST_LEN(pDMAConfig->TxDMABurstLen));
	assert_param(IS_FUNCTIONAL_STATE(pDMAConfig->EnhancedDescriptorFormat));
	assert_param(IS_ETH_DESCRIPTOR_SKIP_LEN(pDMAConfig->DescriptorSkipLen));
	assert_param(IS_ETH_DMA_ARBITRATION(pDMAConfig->DMAArbitration));

	// DMAOMR
	tmpreg = (heth->Instance)->DMAOMR;
	tmpreg &= 0xF8DE3F23U;
    
    if (pDMAConfig->DropTCPIPChecksumErrorFrame != DISABLE)
        tmpreg |= ETH_DMAOMR_DTCEFD;
    
    if (pDMAConfig->ReceiveStoreForward != DISABLE)
        tmpreg |= ETH_DMAOMR_RSF;
    
    if (pDMAConfig->FlushReceivedFrame == DISABLE)
        tmpreg |= ETH_DMAOMR_DFRF;
    
    if (pDMAConfig->TransmitStoreForward != DISABLE)
        tmpreg |= ETH_DMAOMR_TSF;
    
    if (pDMAConfig->TransmitThresholdControl == ETH_TRANSMIT_THRESHOLD_CONTROL_64BYTES)
        tmpreg |= 0;
    else if (pDMAConfig->TransmitThresholdControl == ETH_TRANSMIT_THRESHOLD_CONTROL_128BYTES)
        tmpreg |= ETH_DMAOMR_TTC_0;
    else if (pDMAConfig->TransmitThresholdControl == ETH_TRANSMIT_THRESHOLD_CONTROL_192BYTES)
        tmpreg |= ETH_DMAOMR_TTC_1;
    else if (pDMAConfig->TransmitThresholdControl == ETH_TRANSMIT_THRESHOLD_CONTROL_256BYTES)
        tmpreg |= ETH_DMAOMR_TTC_1 | ETH_DMAOMR_TTC_0;
    else if (pDMAConfig->TransmitThresholdControl == ETH_TRANSMIT_THRESHOLD_CONTROL_40BYTES)
        tmpreg |= ETH_DMAOMR_TTC_2;
    else if (pDMAConfig->TransmitThresholdControl == ETH_TRANSMIT_THRESHOLD_CONTROL_32BYTES)
        tmpreg |= ETH_DMAOMR_TTC_2 | ETH_DMAOMR_TTC_0;
    else if (pDMAConfig->TransmitThresholdControl == ETH_TRANSMIT_THRESHOLD_CONTROL_24BYTES)
        tmpreg |= ETH_DMAOMR_TTC_2 | ETH_DMAOMR_TTC_1;
    else if (pDMAConfig->TransmitThresholdControl == ETH_TRANSMIT_THRESHOLD_CONTROL_16BYTES)
        tmpreg |= ETH_DMAOMR_TTC_2 | ETH_DMAOMR_TTC_1 | ETH_DMAOMR_TTC_0;
    
    if (pDMAConfig->ForwardErrorFrames != DISABLE)
        tmpreg |= ETH_DMAOMR_FEF;
    
    if (pDMAConfig->ForwardUndersizedGoodFrames != DISABLE)
        tmpreg |= ETH_DMAOMR_FUGF;

    if (pDMAConfig->ReceiveThresholdControl == ETH_RECEIVED_THRESHOLD_CONTROL_64BYTES)
        tmpreg |= 0;
    else if (pDMAConfig->ReceiveThresholdControl == ETH_RECEIVED_THRESHOLD_CONTROL_32BYTES)
        tmpreg |= ETH_DMAOMR_RTC_0;
    else if (pDMAConfig->ReceiveThresholdControl == ETH_RECEIVED_THRESHOLD_CONTROL_96BYTES)
        tmpreg |= ETH_DMAOMR_RTC_1;
    else if (pDMAConfig->ReceiveThresholdControl == ETH_RECEIVED_THRESHOLD_CONTROL_128BYTES)
        tmpreg |= ETH_DMAOMR_RTC_1 | ETH_DMAOMR_RTC_0;
    
    if (pDMAConfig->SecondFrameOperate != DISABLE)
        tmpreg |= ETH_DMAOMR_OSF;
    
	(heth->Instance)->DMAOMR = (uint32_t)tmpreg;
    
	// DMABMR
    tmpreg = 0;
    
    if (pDMAConfig->MixedBurst != DISABLE)
        tmpreg |= ETH_DMABMR_MB;
    
    if (pDMAConfig->AddressAlignedBeats != DISABLE)
        tmpreg |= ETH_DMABMR_AAB;
    
    if (pDMAConfig->PBL8xMode != DISABLE)
        tmpreg |= ETH_DMABMR_EPM;
    
    if (pDMAConfig->UseSeparatePBL != DISABLE)
        tmpreg |= ETH_DMABMR_USP;
    
    if (pDMAConfig->RxDMABurstLen == ETH_RX_DMA_BURST_LEN_1BEAT)
        tmpreg |= ETH_DMABMR_RDP_0;
    else if (pDMAConfig->RxDMABurstLen == ETH_RX_DMA_BURST_LEN_2BEAT)
        tmpreg |= ETH_DMABMR_RDP_1;
    else if (pDMAConfig->RxDMABurstLen == ETH_RX_DMA_BURST_LEN_4BEAT)
        tmpreg |= ETH_DMABMR_RDP_2;
    else if (pDMAConfig->RxDMABurstLen == ETH_RX_DMA_BURST_LEN_8BEAT)
        tmpreg |= ETH_DMABMR_RDP_3;
    else if (pDMAConfig->RxDMABurstLen == ETH_RX_DMA_BURST_LEN_16BEAT)
        tmpreg |= ETH_DMABMR_RDP_4;
    else if (pDMAConfig->RxDMABurstLen == ETH_RX_DMA_BURST_LEN_32BEAT)
        tmpreg |= ETH_DMABMR_RDP_5;
    
    if (pDMAConfig->FixedBurst != DISABLE)
        tmpreg |= ETH_DMABMR_FB;
    
    if (pDMAConfig->RxTxPriorityRatio == ETH_RX_TX_PRIORITY_RATIO_1_1)
        tmpreg |= 0;
    else if (pDMAConfig->RxTxPriorityRatio == ETH_RX_TX_PRIORITY_RATIO_2_1)
        tmpreg |= ETH_DMABMR_PM_0;
    else if (pDMAConfig->RxTxPriorityRatio == ETH_RX_TX_PRIORITY_RATIO_3_1)
        tmpreg |= ETH_DMABMR_PM_1;
    else if (pDMAConfig->RxTxPriorityRatio == ETH_RX_TX_PRIORITY_RATIO_4_1)
        tmpreg |= ETH_DMABMR_PM_1 | ETH_DMABMR_PM_0;
    
    if (pDMAConfig->TxDMABurstLen == ETH_TX_DMA_BURST_LEN_1BEAT)
        tmpreg |= ETH_DMABMR_PBL_0;
    else if (pDMAConfig->TxDMABurstLen == ETH_TX_DMA_BURST_LEN_2BEAT)
        tmpreg |= ETH_DMABMR_PBL_1;
    else if (pDMAConfig->TxDMABurstLen == ETH_TX_DMA_BURST_LEN_4BEAT)
        tmpreg |= ETH_DMABMR_PBL_2;
    else if (pDMAConfig->TxDMABurstLen == ETH_TX_DMA_BURST_LEN_8BEAT)
        tmpreg |= ETH_DMABMR_PBL_3;
    else if (pDMAConfig->TxDMABurstLen == ETH_TX_DMA_BURST_LEN_16BEAT)
        tmpreg |= ETH_DMABMR_PBL_4;
    else if (pDMAConfig->TxDMABurstLen == ETH_TX_DMA_BURST_LEN_32BEAT)
        tmpreg |= ETH_DMABMR_PBL_5;
    
    if (pDMAConfig->EnhancedDescriptorFormat != DISABLE)
        tmpreg |= ETH_DMABMR_EDFE;
    
    tmpreg |= (pDMAConfig->DescriptorSkipLen << ETH_DMABMR_DSL_Pos) & ETH_DMABMR_DSL;
    
    if (pDMAConfig->DMAArbitration != ETH_DMA_ARBITRATION_ROUNDROBIN)
        tmpreg |= ETH_DMABMR_DA;
    else
        tmpreg |= 0;
    
    (heth->Instance)->DMABMR = (uint32_t)tmpreg;
    
	return HAL_OK; 
}


HAL_StatusTypeDef HAL_ETH_SetDMADefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitDMADefaultParamter(heth);
    
    return HAL_ETH_SetDMAConfig(heth);
}

//	****************************************************************************
//  
//                              Flow Control
//  
//	****************************************************************************

uint32_t HAL_ETH_GetFlowCtrlStatus(ETH_HandleTypeDef *heth)
{
	if (heth == NULL)
		return (0);
    
    if (heth->Instance->MACFCR & ETH_MACFCR_FCB_BPA)
        return (1);
    else
        return (0);
}

HAL_StatusTypeDef HAL_ETH_RecvFlowCtrlEnable(ETH_HandleTypeDef *heth, uint32_t pausetime)
{
	volatile uint32_t tmpreg;
    
	if (heth == NULL)
		return (HAL_ERROR);
    
    if (heth->Instance->MACFCR & ETH_MACFCR_FCB_BPA)
        return HAL_ERROR;
    
    tmpreg = heth->Instance->MACFCR & ~ETH_MACFCR_PT;
    
    tmpreg |= (pausetime << ETH_MACFCR_PT_Pos) & ETH_MACFCR_PT;
    tmpreg |= ETH_MACFCR_TFCE;
    
    heth->Instance->MACFCR = tmpreg | ETH_MACFCR_FCB_BPA;
    
//    heth->Instance->MACFCR |= ETH_MACFCR_FCB_BPA;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_RecvFlowCtrlDisable(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    
	if (heth == NULL)
		return (HAL_ERROR);
    
    if (heth->Instance->MACFCR & ETH_MACFCR_FCB_BPA)
        return HAL_ERROR;
    
    tmpreg = heth->Instance->MACFCR & ~ETH_MACFCR_PT;
    
    tmpreg |= ETH_MACFCR_TFCE;
    
    heth->Instance->MACFCR = tmpreg | ETH_MACFCR_FCB_BPA;
    
//    heth->Instance->MACFCR |= ETH_MACFCR_FCB_BPA;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SendFlowCtrlEnable(ETH_HandleTypeDef *heth, uint32_t unicast_pause_frame_detect)
{
	volatile uint32_t tmpreg;
    
	if (heth == NULL)
		return (HAL_ERROR);
    
    if (heth->Instance->MACFCR & ETH_MACFCR_FCB_BPA)
        return HAL_ERROR;
    
    tmpreg = heth->Instance->MACFCR;
    
    if (unicast_pause_frame_detect)
        tmpreg |= ETH_MACFCR_UPFD;
    else
        tmpreg &= ~ETH_MACFCR_UPFD;
    
    tmpreg |= ETH_MACFCR_RFCE;
    
    heth->Instance->MACFCR = tmpreg;
    
//    heth->Instance->MACFFR |= BIT7 | BIT6;
    
    
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SendFlowCtrlDisable(ETH_HandleTypeDef *heth)
{
	if (heth == NULL)
		return (HAL_ERROR);
    
    if (heth->Instance->MACFCR & ETH_MACFCR_FCB_BPA)
        return HAL_ERROR;
    
    heth->Instance->MACFCR &= ~(ETH_MACFCR_UPFD | ETH_MACFCR_RFCE);
    
    return HAL_OK;
}

uint32_t HAL_ETH_GetBackPressureStatus(ETH_HandleTypeDef *heth)
{
	if (heth == NULL)
		return (0);
    
    if (heth->Instance->MACFCR & ETH_MACFCR_FCB_BPA)
        return (1);
    else
        return (0);
}

HAL_StatusTypeDef HAL_ETH_BackPressureEnable(ETH_HandleTypeDef *heth)
{
	if (heth == NULL)
		return (HAL_ERROR);
    
    if (heth->Instance->MACFCR & ETH_MACFCR_FCB_BPA)
        return HAL_ERROR;
    
    heth->Instance->MACFCR |= ETH_MACFCR_TFCE | ETH_MACFCR_FCB_BPA;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_BackPressureDisable(ETH_HandleTypeDef *heth)
{
	if (heth == NULL)
		return (HAL_ERROR);
    
    heth->Instance->MACFCR &= ~(ETH_MACFCR_FCB_BPA);
    heth->Instance->MACFCR &= ~(ETH_MACFCR_TFCE);
    
    return HAL_OK;
}


//	****************************************************************************
//  
//                              MMC
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_InitMMCDefaultParamter(ETH_HandleTypeDef *heth)
{
    // MMC
    heth->MMCConfig.UpdateForDroppedBroadcast = 0;
    heth->MMCConfig.FullHalfPreset = 0;
    heth->MMCConfig.Preset = 0;
    heth->MMCConfig.ResetOnRead = 0;
    heth->MMCConfig.StopRollover = 0;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetMMCCounter(ETH_HandleTypeDef *heth)
{
    ETH_MMCCounterTypeDef *pMMCCounter = &heth->MMCCounter;
    
	if (heth == NULL)
		return (HAL_ERROR);
    
    pMMCCounter->TxGoodFrameSingleCollision = heth->Instance->MMCTGFSCCR;
    pMMCCounter->TxGoodFrameMultipleCollision = heth->Instance->MMCTGFMCCR;
    pMMCCounter->TxGoodFrame = heth->Instance->MMCTGFCR;
    pMMCCounter->RxCRCErr = heth->Instance->MMCRFCECR;
    pMMCCounter->RxAlignmentErr = heth->Instance->MMCRFAECR;
    pMMCCounter->RxGoodUnicast = heth->Instance->MMCRGUFCR;
    
	return HAL_OK; 
}

HAL_StatusTypeDef HAL_ETH_GetMMCConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_MMCInitTypeDef *pMMCConfig = &heth->MMCConfig;
    
	if (heth == NULL)
		return (HAL_ERROR);
    
    memset((void *)pMMCConfig, 0, sizeof(ETH_MMCInitTypeDef));
    tmpreg = heth->Instance->MMCCR;
    
    if (tmpreg & ETH_MMCCR_UCDBC)
        pMMCConfig->UpdateForDroppedBroadcast = 1;
    
    if (tmpreg & ETH_MMCCR_CNTPRSTLVL)
        pMMCConfig->FullHalfPreset = 1;
    
    if (tmpreg & ETH_MMCCR_CNTPRST)
        pMMCConfig->Preset = 1;
    
    if (tmpreg & ETH_MMCCR_RSTONRD)
        pMMCConfig->ResetOnRead = 1;
    
    if (tmpreg & ETH_MMCCR_CNTSTOPRO)
        pMMCConfig->StopRollover = 1;
    
	return HAL_OK; 
}

HAL_StatusTypeDef HAL_ETH_SetMMCConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_MMCInitTypeDef *pMMCConfig = &heth->MMCConfig;
    
	if (heth == NULL)
		return (HAL_ERROR);
    
    tmpreg = 0;
    
    if (pMMCConfig->UpdateForDroppedBroadcast)
        SET_BIT(tmpreg, ETH_MMCCR_UCDBC);
    
    if (pMMCConfig->FullHalfPreset)
        SET_BIT(tmpreg, ETH_MMCCR_CNTPRSTLVL);
    
    if (pMMCConfig->Preset)
        SET_BIT(tmpreg, ETH_MMCCR_CNTPRST);
    
    if (pMMCConfig->ResetOnRead)
        SET_BIT(tmpreg, ETH_MMCCR_RSTONRD);
    
    if (pMMCConfig->StopRollover)
        SET_BIT(tmpreg, ETH_MMCCR_CNTSTOPRO);
    
    WRITE_REG(heth->Instance->MMCCR, tmpreg);
    
	return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SetMMCDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitMMCDefaultParamter(heth);
    
    return HAL_ETH_SetMMCConfig(heth);
}

HAL_StatusTypeDef HAL_ETH_MMCFreezeCounter(ETH_HandleTypeDef *heth, FunctionalState cmd)
{
    assert_param(IS_FUNCTIONAL_STATE(cmd));
    
	if (heth == NULL)
		return (HAL_ERROR);
    
    if (cmd == DISABLE)
    {
        CLEAR_BIT(heth->Instance->MMCCR, ETH_MMCCR_CNTFREEZ);
    }
    else
    {
        SET_BIT(heth->Instance->MMCCR, ETH_MMCCR_CNTFREEZ);
    }
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_MMCResetCounter(ETH_HandleTypeDef *heth)
{
	if (heth == NULL)
		return (HAL_ERROR);
    
    SET_BIT(heth->Instance->MMCCR, ETH_MMCCR_CNTRST);
    
    return HAL_OK;
}


//	****************************************************************************
//  
//                              LPI
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_InitLPIDefaultParamter(ETH_HandleTypeDef *heth)
{
    // MMC
    heth->LPIConfig.TxAuto = 0;
    heth->LPIConfig.TxClockGateCtrlInvalid = 0;
    heth->LPIConfig.EntryTime = 100;
    heth->LPIConfig.ExtiTime = 10;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_GetLPIConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_LPITypeDef *pLPIConfig = &heth->LPIConfig;
    
	if (heth == NULL)
		return (HAL_ERROR);
    
    memset((void *)pLPIConfig, 0, sizeof(ETH_LPITypeDef));
    
    tmpreg = heth->Instance->MACLPICSR;
    
    if (tmpreg & ETH_MACLPICSR_LPITXA)
        pLPIConfig->TxAuto = 1;
    
    if (SYSCFG->SYSCR & SYSCFG_SYSCR_ETHMAC_TX_CLKGE)
        pLPIConfig->TxClockGateCtrlInvalid = 1;
    
    if (tmpreg & ETH_MACLPICSR_PLSEN)
        pLPIConfig->EntryTime = (heth->Instance->MACLPITCR & ETH_MACLPITCR_LST) >> ETH_MACLPITCR_LST_Pos;
    
    pLPIConfig->ExtiTime = (heth->Instance->MACLPITCR & ETH_MACLPITCR_TWT) >> ETH_MACLPITCR_TWT_Pos;
    
	return HAL_OK; 
}

HAL_StatusTypeDef HAL_ETH_SetLPIConfig(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tmpreg;
    ETH_LPITypeDef *pLPIConfig = &heth->LPIConfig;
    
	if (heth == NULL)
		return (HAL_ERROR);
    
    if (pLPIConfig->TxClockGateCtrlInvalid)
        SYSCFG->SYSCR |= SYSCFG_SYSCR_ETHMAC_TX_CLKGE;
    else
        SYSCFG->SYSCR &= ~SYSCFG_SYSCR_ETHMAC_TX_CLKGE;
    
    heth->Instance->MACLPITCR = (((uint32_t)pLPIConfig->EntryTime << ETH_MACLPITCR_LST_Pos) & ETH_MACLPITCR_LST) | \
                                (((uint32_t)pLPIConfig->ExtiTime << ETH_MACLPITCR_TWT_Pos) & ETH_MACLPITCR_TWT);
    
    tmpreg = heth->Instance->MACLPICSR & ~(ETH_MACLPICSR_LPITXA | ETH_MACLPICSR_PLSEN);
    
    if (pLPIConfig->TxAuto)
        tmpreg |= ETH_MACLPICSR_LPITXA;
    
    heth->Instance->MACLPICSR = tmpreg;
    
	return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SetLPIDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitLPIDefaultParamter(heth);
    
    return HAL_ETH_SetLPIConfig(heth);
}

HAL_StatusTypeDef HAL_ETH_EnterLPIMode(ETH_HandleTypeDef *heth)
{
	if (heth == NULL)
		return (HAL_ERROR);
    
    heth->Instance->MACLPICSR |= ETH_MACLPICSR_LPIEN;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_ExitLPIMode(ETH_HandleTypeDef *heth)
{
	if (heth == NULL)
		return (HAL_ERROR);
    
    heth->Instance->MACLPICSR &= ~ETH_MACLPICSR_LPIEN;
    
    return HAL_OK;
}



//	****************************************************************************
//  
//                              PMT
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_InitPMTDefaultParamter(ETH_HandleTypeDef *heth)
{
    memset((void *)&heth->PMTConfig, 0, sizeof(ETH_PMTInitTypeDef));
    
    return HAL_OK;
}
//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_GetPMTConfig(ETH_HandleTypeDef *heth, ETH_PMTInitTypeDef *pPMTConfig);
//	功能 ：	取PMT配置
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//	输出 ：	pPMTConfig：配置结构体指针；
//	返回 ：	HAL_OK：取配置成功；
//			HAL_ERROR：取配置失败；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_GetPMTConfig(ETH_HandleTypeDef *heth)
{
	uint32_t i;
	uint32_t err;
	volatile uint32_t tmpreg;
    ETH_PMTInitTypeDef *pPMTConfig = &heth->PMTConfig;

	if (heth == NULL)
		return (HAL_ERROR);
    
	err = 0;
    (heth->Instance)->MACPMTCSR |= ETH_MACPMTCSR_RWFFPR;
    
    pPMTConfig->Filter[0].Mask = (heth->Instance)->MACRWUFF;
	pPMTConfig->Filter[1].Mask = (heth->Instance)->MACRWUFF;
	pPMTConfig->Filter[2].Mask = (heth->Instance)->MACRWUFF;
	pPMTConfig->Filter[3].Mask = (heth->Instance)->MACRWUFF;
    
    tmpreg = (heth->Instance)->MACRWUFF;
	pPMTConfig->Filter[0].Cmd = tmpreg & 0x0f;
	pPMTConfig->Filter[1].Cmd = (tmpreg >> 8) & 0x0f;
	pPMTConfig->Filter[2].Cmd = (tmpreg >> 16) & 0x0f;
	pPMTConfig->Filter[3].Cmd = (tmpreg >> 24) & 0x0f;
    
    tmpreg = (heth->Instance)->MACRWUFF;
	pPMTConfig->Filter[0].Offset = tmpreg & 0xff;
	pPMTConfig->Filter[1].Offset = (tmpreg >> 8) & 0xff;
	pPMTConfig->Filter[2].Offset = (tmpreg >> 16) & 0xff;
	pPMTConfig->Filter[3].Offset = (tmpreg >> 24) & 0xff;
    
    tmpreg = (heth->Instance)->MACRWUFF;
	pPMTConfig->Filter[0].CRC16 = tmpreg & 0xffff;
	pPMTConfig->Filter[1].CRC16 = (tmpreg >> 16) & 0xffff;
    
    tmpreg = (heth->Instance)->MACRWUFF;
	pPMTConfig->Filter[2].CRC16 = tmpreg & 0xffff;
	pPMTConfig->Filter[3].CRC16 = (tmpreg >> 16) & 0xffff;
    
    if ((heth->Instance)->MACPMTCSR & ETH_MACPMTCSR_GU)
        pPMTConfig->GlobalUnicast = 1;
    else
        pPMTConfig->GlobalUnicast = 0;

    
    for (i=0; i<8; i++)
    {
        tmpreg = (heth->Instance)->MACRWUFF;
    }
    
    for (i=0; i<4; i++)
    {
        if (pPMTConfig->Filter[i].Mask & BIT31)
        {
            err = 1;
            break;
        }
        if (pPMTConfig->Filter[i].Offset < 12)
        {
            err = 1;
            break;
        }
    }
    
	if (err == 0)
		return HAL_OK;
	else
		return HAL_ERROR;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_SetPMTConfig(ETH_HandleTypeDef *heth, ETH_PMTInitTypeDef *pPMTConfig);
//	功能 ：	配置PMT
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			pPMTConfig：配置结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_SetPMTConfig(ETH_HandleTypeDef *heth)
{
	uint32_t i;
	uint32_t tmpreg;
    ETH_PMTInitTypeDef *pPMTConfig = &heth->PMTConfig;

	if (heth == NULL)
		return (HAL_ERROR);
    
    (heth->Instance)->MACPMTCSR |= ETH_MACPMTCSR_RWFFPR;
    
    for (i=0; i<4; i++)
    {
        (heth->Instance)->MACRWUFF = pPMTConfig->Filter[i].Mask;
    }
    
    tmpreg = pPMTConfig->Filter[0].Cmd & 0x0f;
    tmpreg |= (pPMTConfig->Filter[1].Cmd & 0x0f) << 8;
    tmpreg |= (pPMTConfig->Filter[2].Cmd & 0x0f) << 16;
    tmpreg |= (pPMTConfig->Filter[3].Cmd & 0x0f) << 24;
    (heth->Instance)->MACRWUFF = tmpreg;
    
    tmpreg = pPMTConfig->Filter[0].Offset & 0xff;
    tmpreg |= (pPMTConfig->Filter[1].Offset & 0xff) << 8;
    tmpreg |= (pPMTConfig->Filter[2].Offset & 0xff) << 16;
    tmpreg |= (pPMTConfig->Filter[3].Offset & 0xff) << 24;
    (heth->Instance)->MACRWUFF = tmpreg;
    
    tmpreg = pPMTConfig->Filter[0].CRC16 & 0xffff;
    tmpreg |= (pPMTConfig->Filter[1].CRC16 & 0xffff) << 16;
    (heth->Instance)->MACRWUFF = tmpreg;
    
    tmpreg = pPMTConfig->Filter[2].CRC16 & 0xffff;
    tmpreg |= (pPMTConfig->Filter[3].CRC16 & 0xffff) << 16;
    (heth->Instance)->MACRWUFF = tmpreg;
    
    if (pPMTConfig->GlobalUnicast)
        (heth->Instance)->MACPMTCSR |= BIT9;
    else
        (heth->Instance)->MACPMTCSR &= ~BIT9;
    
	return HAL_OK; 
}

HAL_StatusTypeDef HAL_ETH_SetPMTDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitPMTDefaultParamter(heth);
    
    return HAL_ETH_SetPMTConfig(heth);
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_EnterPowerDownMode(ETH_HandleTypeDef *heth, uint32_t WakeupFrameEnable, uint32_t MagicPacketEnable);
//	功能 ：	进入掉电模式
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//	输入 ：	WakeupMode：唤醒模式；bit0：中断唤醒；bit1：事件唤醒；
//	输入 ：	WakeupFrameEnable：唤醒帧使能；
//	输入 ：	MagicPacketEnable：魔术包使能；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//	备注 ：	
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_EnterPowerDownMode(ETH_HandleTypeDef *heth, uint32_t WakeupMode, uint32_t WakeupFrameEnable, uint32_t MagicPacketEnable)
{
    uint32_t tmpreg;
    uint32_t timeout;
    
    if ((WakeupFrameEnable == 0) && (MagicPacketEnable == 0))
        return (HAL_ERROR);
    
    
    /* Disable the DMA transmission */
    (heth->Instance)->DMAOMR &= ~ETH_DMAOMR_ST;
    
    timeout = 0xffffff;
    while ((heth->Instance)->DMASR & ETH_DMASR_TS)
    {
        if (--timeout == 0)
            return (HAL_TIMEOUT);
    }
    
    /* Disable the MAC transmission */
    (heth->Instance)->MACCR &= ~ETH_MACCR_TE;
    
    /* Disable the MAC reception */
    (heth->Instance)->MACCR &= ~ETH_MACCR_RE;
    
    timeout = 0xffffff;
    while (((heth->Instance)->MACDBGR & ETH_MACDBGR_RFFL) != 0)
    {
        if (--timeout == 0)
            return (HAL_TIMEOUT);
    }
    
    /* Disable the DMA reception */
    (heth->Instance)->DMAOMR &= ~ETH_DMAOMR_SR;
    
    __HAL_RCC_EXTI_CLK_ENABLE();
    
    EXTI->RTENR2 &= ~BIT1;
    EXTI->FTENR2 &= ~BIT1;
    EXTI->PDR2 = BIT1;
    if (WakeupMode & BIT0)
        EXTI->IENR2 |= BIT1;
    else
        EXTI->IENR2 &= ~BIT1;
    if (WakeupMode & BIT1)
        EXTI->EENR2 |= BIT1;
    else
        EXTI->EENR2 &= ~BIT1;
    EXTI->RTENR2 |= BIT1;
    
    if (WakeupMode)
        (heth->Instance)->MACIMR &= ~ETH_MACIMR_PIM;
    else
        (heth->Instance)->MACIMR |= ETH_MACIMR_PIM;
    
    if (WakeupFrameEnable)
        (heth->Instance)->MACPMTCSR |= ETH_MACPMTCSR_WFE;
    else
        (heth->Instance)->MACPMTCSR &= ~ETH_MACPMTCSR_WFE;
    
    if (MagicPacketEnable)
        (heth->Instance)->MACPMTCSR |= ETH_MACPMTCSR_MPE;
    else
        (heth->Instance)->MACPMTCSR &= ~ETH_MACPMTCSR_MPE;
    
    (heth->Instance)->MACPMTCSR |= ETH_MACPMTCSR_PD;
    
    (heth->Instance)->MACCR |= ETH_MACCR_RE;
    
    return (HAL_OK);
}


//	****************************************************************************
//  
//                              PTP
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_InitPTPDefaultParamter(ETH_HandleTypeDef *heth)
{
    uint32_t i;
    
    memset((void *)&heth->PTPConfig, 0, sizeof(ETH_PTPInitTypeDef));
    
    heth->PTPConfig.IPV4Message = ENABLE;
    heth->PTPConfig.DigitalRollover = ENABLE;
    heth->PTPConfig.FineUpdate = ENABLE;
    
    return HAL_OK;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_GetPMTConfig(ETH_HandleTypeDef *heth, ETH_PMTInitTypeDef *pPMTConfig);
//	功能 ：	取PMT配置
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//	输出 ：	pPMTConfig：配置结构体指针；
//	返回 ：	HAL_OK：取配置成功；
//			HAL_ERROR：取配置失败；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_GetPTPConfig(ETH_HandleTypeDef *heth)
{
	uint32_t i;
	uint32_t err;
	volatile uint32_t tmpreg;
    ETH_PTPInitTypeDef *pPTPConfig = &heth->PTPConfig;

	if (heth == NULL)
		return (HAL_ERROR);
    
    err = 0;
    memset((void *)pPTPConfig, 0, sizeof(ETH_PTPInitTypeDef));
    
    // PTPTSCR
    tmpreg = (heth->Instance)->PTPTSCR;
    
    if (tmpreg & ETH_PTPTSCR_ASEN3)
        pPTPConfig->Auxi[3] = ENABLE;
    if (tmpreg & ETH_PTPTSCR_ASEN2)
        pPTPConfig->Auxi[2] = ENABLE;
    if (tmpreg & ETH_PTPTSCR_ASEN2)
        pPTPConfig->Auxi[1] = ENABLE;
    if (tmpreg & ETH_PTPTSCR_ASEN2)
        pPTPConfig->Auxi[0] = ENABLE;
    
    if (tmpreg & ETH_PTPTSCR_EMAFPFF)
        pPTPConfig->MACAddrFilter = ENABLE;
    
    pPTPConfig->Clock = (tmpreg & ETH_PTPTSCR_SPPFTS) >> ETH_PTPTSCR_SPPFTS_Pos;
    
    if (tmpreg & ETH_PTPTSCR_ESFMRTM)
        pPTPConfig->MasterMessage = ENABLE;
    
    if (tmpreg & ETH_PTPTSCR_ETSFEM)
        pPTPConfig->EventMessage = ENABLE;
    
    if (tmpreg & ETH_PTPTSCR_EPPFSIP4U)
        pPTPConfig->IPV4Message = ENABLE;
    
    if (tmpreg & ETH_PTPTSCR_EPPFSIP6U)
        pPTPConfig->IPV6Message = ENABLE;
    
    if (tmpreg & ETH_PTPTSCR_EPPEF)
        pPTPConfig->EthernetFrame = ENABLE;
    
    if (tmpreg & ETH_PTPTSCR_TSPTPPSV2E)
        pPTPConfig->Ver2 = ENABLE;
    
    if (tmpreg & ETH_PTPTSCR_TSR)
        pPTPConfig->DigitalRollover = ENABLE;
    
    if (tmpreg & ETH_PTPTSCR_TSARFE)
        pPTPConfig->AllFrames = ENABLE;
    
    if (tmpreg & ETH_PTPTSCR_TFCU)
        pPTPConfig->FineUpdate = ENABLE;
    
    // PTPPPSCR
    tmpreg = (heth->Instance)->PTPPPSCR ;
    
    if ((tmpreg & ETH_PTPPPSCR_TRGTMODSEL) == ETH_PTPPPSCR_TRGTMODSEL_0)
        err = 1;
    else
        pPTPConfig->PPS.TargetTimeFunc = (tmpreg & ETH_PTPPPSCR_TRGTMODSEL) >> ETH_PTPPPSCR_TRGTMODSEL_Pos;
    
    if (tmpreg & ETH_PTPPPSCR_PPSEN)
    {
        pPTPConfig->PPS.Mode = ETH_PTP_PPS_OUTPUT_MODE_CMD;
        pPTPConfig->PPS.Output.Cmd = (tmpreg & ETH_PTPPPSCR_PPSCMD) >> ETH_PTPPPSCR_PPSCMD_Pos;
    }
    else
    {
        pPTPConfig->PPS.Mode = ETH_PTP_PPS_OUTPUT_MODE_CTRL;
        pPTPConfig->PPS.Output.Freq = (tmpreg & ETH_PTPPPSCR_PPSCTRL) >> ETH_PTPPPSCR_PPSCTRL_Pos;
    }
    
    // PTPPPSIR
     pPTPConfig->PPS.Interval = (heth->Instance)->PTPPPSIR;
    
    // PTPPPSWR
     pPTPConfig->PPS.Width = (heth->Instance)->PTPPPSWR;
    
	if (err == 0)
		return HAL_OK;
	else
		return HAL_ERROR;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_SetPMTConfig(ETH_HandleTypeDef *heth, ETH_PMTInitTypeDef *pPMTConfig);
//	功能 ：	配置PMT
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			pPMTConfig：配置结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//	备注 ：	
//	****************************************************************************
HAL_StatusTypeDef HAL_ETH_SetPTPConfig(ETH_HandleTypeDef *heth)
{
	uint32_t i;
	volatile uint32_t tmpreg;
    ETH_PTPInitTypeDef *pPTPConfig = &heth->PTPConfig;

	if (heth == NULL)
		return (HAL_ERROR);
    
    // PTPTSCR
    tmpreg = (heth->Instance)->PTPTSCR & ~0x1e07ff02;
    
    if (pPTPConfig->Auxi[3] != DISABLE)
        tmpreg |= ETH_PTPTSCR_ASEN3;
    if (pPTPConfig->Auxi[2] != DISABLE)
        tmpreg |= ETH_PTPTSCR_ASEN2;
    if (pPTPConfig->Auxi[1] != DISABLE)
        tmpreg |= ETH_PTPTSCR_ASEN1;
    if (pPTPConfig->Auxi[0] != DISABLE)
        tmpreg |= ETH_PTPTSCR_ASEN0;
    
    if (pPTPConfig->MACAddrFilter != DISABLE)
        tmpreg |= ETH_PTPTSCR_EMAFPFF;
    
    tmpreg |= ((uint32_t)pPTPConfig->Clock << ETH_PTPTSCR_SPPFTS_Pos) & ETH_PTPTSCR_SPPFTS;
    
    if (pPTPConfig->MasterMessage != DISABLE)
        tmpreg |= ETH_PTPTSCR_ESFMRTM;
    
    if (pPTPConfig->EventMessage != DISABLE)
        tmpreg |= ETH_PTPTSCR_ETSFEM;
    
    if (pPTPConfig->IPV4Message != DISABLE)
        tmpreg |= ETH_PTPTSCR_EPPFSIP4U;
    
    if (pPTPConfig->IPV6Message != DISABLE)
        tmpreg |= ETH_PTPTSCR_EPPFSIP6U;
    
    if (pPTPConfig->EthernetFrame != DISABLE)
        tmpreg |= ETH_PTPTSCR_EPPEF;
    
    if (pPTPConfig->Ver2 != DISABLE)
        tmpreg |= ETH_PTPTSCR_TSPTPPSV2E;
    
    if (pPTPConfig->DigitalRollover != DISABLE)
    {
        tmpreg |= ETH_PTPTSCR_TSR;
        ETH->PTPSSIR = 20u;
    }
    else
    {
        ETH->PTPSSIR = 43u;
    }
    
    if (pPTPConfig->AllFrames != DISABLE)
        tmpreg |= ETH_PTPTSCR_TSARFE;
    
    if (pPTPConfig->FineUpdate != DISABLE)
        tmpreg |= ETH_PTPTSCR_TFCU;
    
    (heth->Instance)->PTPTSCR = tmpreg;
    
    // PTPTSCR
    tmpreg = (heth->Instance)->PTPPPSCR & ~0x0000007f;
    
    tmpreg |= ((uint32_t)pPTPConfig->PPS.TargetTimeFunc << ETH_PTPPPSCR_TRGTMODSEL_Pos) & ETH_PTPPPSCR_TRGTMODSEL;
    
    if (pPTPConfig->PPS.Mode == ETH_PTP_PPS_OUTPUT_MODE_CMD)
    {
        tmpreg |= ETH_PTPPPSCR_PPSEN;
        tmpreg |= ((uint32_t)pPTPConfig->PPS.Output.Cmd << ETH_PTPPPSCR_PPSCMD_Pos) & ETH_PTPPPSCR_PPSCMD;
    }
    else
    {
        tmpreg |= ((uint32_t)pPTPConfig->PPS.Output.Freq << ETH_PTPPPSCR_PPSCTRL_Pos) & ETH_PTPPPSCR_PPSCTRL;
    }
    
    // PTPPPSIR
     (heth->Instance)->PTPPPSIR = pPTPConfig->PPS.Interval;
    
    // PTPPPSWR
     (heth->Instance)->PTPPPSWR = pPTPConfig->PPS.Width;
    
	return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_SetPTPDefaultConfig(ETH_HandleTypeDef *heth)
{
    HAL_ETH_InitPTPDefaultParamter(heth);
    
    return HAL_ETH_SetPTPConfig(heth);
}

HAL_StatusTypeDef HAL_ETH_PTPStart(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp)
{
    uint64_t temp;
    uint32_t timeout;
    ETH_TypeDef *eth = heth->Instance;
    
    if (timestamp->nsec & BIT31)
        return HAL_ERROR;
    
    // 禁止时间戳中断
    eth->MACIMR |= ETH_MACIMR_TIM;
    
    // 使能时间戳
    eth->PTPTSCR |= ETH_PTPTSCR_TE;
    
    if (heth->PTPConfig.DigitalRollover)
        eth->PTPSSIR  = 20;
    else
        eth->PTPSSIR  = 43;
    
    if (heth->PTPConfig.FineUpdate)
    {
        eth->PTPTSAR = (uint32_t)(pow(2,32) * 50000000 / HAL_RCC_GetHCLKFreq());
        
        timeout = ETH_PTP_TIMEOUT;
        while (eth->PTPTSCR & ETH_PTPTSCR_TARU)
        {
            if (--timeout == 0)
                return HAL_ERROR;
        }
        
        eth->PTPTSCR |= ETH_PTPTSCR_TARU;
        
        timeout = ETH_PTP_TIMEOUT;
        while (eth->PTPTSCR & ETH_PTPTSCR_TARU)
        {
            if (--timeout == 0)
                return HAL_ERROR;
        }
        
        eth->PTPTSCR |= ETH_PTPTSCR_TFCU;
    }
    else
    {
        eth->PTPTSCR &= (~(uint32_t)ETH_PTPTSCR_TFCU);
    }
    
    eth->PTPTSHUR = timestamp->sec;
    if (heth->PTPConfig.DigitalRollover)
        eth->PTPTSLUR = timestamp->nsec;
    else
        eth->PTPTSLUR = (uint32_t)((uint64_t)timestamp->nsec * 0x80000000 / 1000000000);
    
    
    timeout = ETH_PTP_TIMEOUT;
    while (eth->PTPTSCR & ETH_PTPTSCR_TI)
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }
    eth->PTPTSCR |= ETH_PTPTSCR_TI;
    
    timeout = ETH_PTP_TIMEOUT;
    while (eth->PTPTSCR & ETH_PTPTSCR_TI)
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_PTPStop(ETH_HandleTypeDef *heth)
{
    uint32_t timeout;
    ETH_TypeDef *eth = heth->Instance;
    ETH_TimestampTypeDef timestamp;
    
    // 禁止时间戳中断
    eth->MACIMR |= ETH_MACIMR_TIM;
    
    // 禁止时间戳中断触发
    eth->PTPTSCR &= ~ETH_PTPTSCR_TITE;
    
    // 禁止时间戳
    eth->PTPTSCR &= ~ETH_PTPTSCR_TE;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_PTPAdjFreq(ETH_HandleTypeDef *heth, int32_t freq)
{
    uint32_t sysclk;
    uint32_t timeout;
    ETH_TypeDef *eth = heth->Instance;
    
    sysclk = HAL_RCC_GetHCLKFreq();
    
    if (freq >= 0)
    {
        sysclk += freq;
    }
    else
    {
        freq = -freq;
        sysclk -= freq;
    }
     
    eth->PTPTSAR = (uint32_t)(pow(2,32) * 50000000 / sysclk);
        
    timeout = ETH_PTP_TIMEOUT;
    while (eth->PTPTSCR & ETH_PTPTSCR_TARU)
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }
    
    eth->PTPTSCR |= ETH_PTPTSCR_TARU;
    
    timeout = ETH_PTP_TIMEOUT;
    while (eth->PTPTSCR & ETH_PTPTSCR_TARU)
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_PTPUpdateOffset(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp)
{
    uint32_t sign;
    uint32_t addend;
    uint32_t timeout;
    ETH_TypeDef *eth = heth->Instance;

    sign = 0;
    if (timestamp->nsec & ETH_PTPTSLUR_AST)
    {
        sign = ETH_PTPTSLUR_AST;
        timestamp->nsec &= ~ETH_PTPTSLUR_AST;
    }

    timeout = ETH_PTP_TIMEOUT;
    while (eth->PTPTSCR & ETH_PTPTSCR_TU)
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }
    timeout = ETH_PTP_TIMEOUT;
    while (eth->PTPTSCR & ETH_PTPTSCR_TI)
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }
    
    /* read old addend register value*/
    addend = ETH->PTPTSAR;

    eth->PTPTSHUR = timestamp->sec;
    if (heth->PTPConfig.DigitalRollover)
        eth->PTPTSLUR = sign | (uint32_t)timestamp->nsec;
    else
        eth->PTPTSLUR = sign | (uint32_t)((uint64_t)timestamp->nsec * 0x80000000 / 1000000000);
    
    eth->PTPTSCR |= ETH_PTPTSCR_TU;
    
    timeout = ETH_PTP_TIMEOUT;
    while (eth->PTPTSCR & ETH_PTPTSCR_TU)
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }

    // 更新
    ETH->PTPTSAR = addend;
    
    timeout = ETH_PTP_TIMEOUT;
    while (eth->PTPTSCR & ETH_PTPTSCR_TARU)
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }
    
    eth->PTPTSCR |= ETH_PTPTSCR_TARU;
    
    timeout = ETH_PTP_TIMEOUT;
    while (eth->PTPTSCR & ETH_PTPTSCR_TARU)
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_PTPTimeSetTime(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp)
{
    uint32_t sign;
    uint32_t timeout;
    ETH_TypeDef *eth = heth->Instance;

    sign = 0;
    if (timestamp->nsec & ETH_PTPTSLUR_AST)
    {
        sign = ETH_PTPTSLUR_AST;
        timestamp->nsec &= ~ETH_PTPTSLUR_AST;
    }
    
    ETH->PTPTSHUR = timestamp->sec;
    if (ETH->PTPTSCR & ETH_PTPTSCR_TSR)
        ETH->PTPTSLUR = sign | timestamp->nsec;
    else
        ETH->PTPTSLUR = sign | (uint32_t)((uint64_t)timestamp->nsec * (uint64_t)0x80000000 / (uint64_t)1000000000);
    
    ETH->PTPTSCR |= ETH_PTPTSCR_TI;
    
    timeout = ETH_PTP_TIMEOUT;
    while (eth->PTPTSCR & ETH_PTPTSCR_TI)
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_PTPGetSystemTime(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp)
{
    if (heth->Instance->PTPTSCR & ETH_PTPTSCR_TSR)
        timestamp->nsec = (int32_t)ETH->PTPTSLR;
    else
        timestamp->nsec = (int32_t)(((uint64_t)ETH->PTPTSLR * (uint64_t)1000000000) >> 31);
    timestamp->sec = ETH->PTPTSHR;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_PTPGetTargetTime(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp)
{
    uint32_t timeout;
    
    timeout = ETH_PTP_TIMEOUT;
    while (heth->Instance->PTPTTLR & ETH_PTPTTLR_TTRB )
    {
        if (--timeout == 0)
            return HAL_ERROR;
    }
    
    if (heth->Instance->PTPTSCR & ETH_PTPTSCR_TSR)
        timestamp->nsec = (int32_t)ETH->PTPTTLR;
    else
        timestamp->nsec = (int32_t)(((uint64_t)ETH->PTPTTLR * (uint64_t)1000000000) >> 31);
    timestamp->sec = ETH->PTPTTHR ;
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_PTPSetTargetTime(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp)
{
    if (timestamp->nsec & ETH_PTPTSLUR_AST)
        return HAL_ERROR;
    
    heth->Instance->PTPTTHR = timestamp->sec;
    if (heth->Instance->PTPTSCR & ETH_PTPTSCR_TSR)
        heth->Instance->PTPTTLR = (uint32_t)timestamp->nsec;
    else
        heth->Instance->PTPTTLR = (uint32_t)((uint64_t)timestamp->nsec * (uint64_t)0x80000000 / (uint64_t)1000000000);
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ETH_PTPGetAuxiliaryTime(ETH_HandleTypeDef *heth, ETH_TimestampTypeDef *timestamp)
{
    if (heth->Instance->PTPTSCR & ETH_PTPTSCR_TSR)
        timestamp->nsec = (int32_t)ETH->PTPATSNR;
    else
        timestamp->nsec = (int32_t)(((uint64_t)ETH->PTPATSNR * (uint64_t)1000000000) >> 31);
    timestamp->sec = ETH->PTPATSSR;
    
    return HAL_OK;
}

uint32_t HAL_ETH_PTPGetAuxiTimeStatus(ETH_HandleTypeDef *heth, ETH_PTPAuxiTimeStatusTypeDef *status)
{
	volatile uint32_t tempreg;
    
    tempreg = heth->Instance->PTPTSSR;
    
    status->AuxiNbr = (tempreg & ETH_PTPTSSR_ATSNS) >> ETH_PTPTSSR_ATSNS_Pos;
    
    if (tempreg & ETH_PTPTSSR_ATSTM)
        status->AuxiTriggerMissed = ENABLE;
    else
        status->AuxiTriggerMissed = DISABLE;
    
    if (tempreg & ETH_PTPTSSR_ATSTI_0)
        status->AuxiTrigger[0] = ENABLE;
    else
        status->AuxiTrigger[0] = DISABLE;
    
    if (tempreg & ETH_PTPTSSR_ATSTI_1)
        status->AuxiTrigger[1] = ENABLE;
    else
        status->AuxiTrigger[1] = DISABLE;
    
    if (tempreg & ETH_PTPTSSR_ATSTI_2)
        status->AuxiTrigger[2] = ENABLE;
    else
        status->AuxiTrigger[2] = DISABLE;
    
    if (tempreg & ETH_PTPTSSR_ATSTI_3)
        status->AuxiTrigger[3] = ENABLE;
    else
        status->AuxiTrigger[3] = DISABLE;
    
    return HAL_OK;
}


//	****************************************************************************
//  
//                              SMI
//  
//	****************************************************************************

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_ConfigSMI(ETH_HandleTypeDef *heth)
//	功能 ：	配置SMI
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//	输出 ：	无；
//	返回 ：	HAL_OK：配置成功；
//			HAL_ERROR：时钟频率不在有效范围之内；
//	备注 ：	
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_ConfigSMI(ETH_HandleTypeDef *heth)
{
	volatile uint32_t tempreg;
	uint32_t hclk;
	
	//SMI时钟配置
	tempreg = (heth->Instance)->MACMIIAR;
	
	tempreg &= ~ETH_MACMIIAR_CR;

	hclk = HAL_RCC_GetHCLKFreq();

	if (hclk < 20000000)
		return (HAL_ERROR);
	else if (hclk < 35000000)
		tempreg |= ETH_MACMIIAR_CR_1;
	else if (hclk <= 60000000)
		tempreg |= ETH_MACMIIAR_CR_1 | ETH_MACMIIAR_CR_0;
	else if (hclk < 100000000)
		tempreg |= 0;
	else if (hclk < 150000000)
		tempreg |= ETH_MACMIIAR_CR_0;
	else if (hclk < 250000000)
		tempreg |= ETH_MACMIIAR_CR_2;
	else if (hclk < 300000000)
		tempreg |= ETH_MACMIIAR_CR_2 | ETH_MACMIIAR_CR_0;
	else
		return (HAL_ERROR);
	
	(heth->Instance)->MACMIIAR = (uint32_t)tempreg;
	
	return (HAL_OK);
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_ReadPHYRegister(ETH_HandleTypeDef *heth, uint16_t PHYReg, uint32_t *RegValue);
//	功能 ：	读PHY寄存器
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			PHYReg：寄存器地址；
//	输出 ：	RegValue：读出数据指针；
//	返回 ：	HAL_OK：读成功；
//			HAL_BUSY：忙；
//			HAL_TIMEOUT：读超时；
//			HAL_ERROR：PHY地址错误；
//	备注 ：	
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_ReadPHYRegister(ETH_HandleTypeDef *heth, uint32_t PHYAddr, uint32_t PHYReg, uint32_t *RegValue)
{
	volatile uint32_t tmpreg;     
	uint32_t tickstart = 0;

    if (READ_BIT(heth->Instance->MACMIIAR, ETH_MACMIIAR_MB))
        return HAL_BUSY;
    
    WRITE_REG(tmpreg, heth->Instance->MACMIIAR);
    
    MODIFY_REG(tmpreg, ETH_MACMIIAR_PA, (PHYAddr << ETH_MACMIIAR_PA_Pos));
    MODIFY_REG(tmpreg, ETH_MACMIIAR_MR, (PHYReg << ETH_MACMIIAR_MR_Pos));
    CLEAR_BIT(tmpreg, ETH_MACMIIAR_MW);
    SET_BIT(tmpreg, ETH_MACMIIAR_MB);
    WRITE_REG(heth->Instance->MACMIIAR, tmpreg);
    
	// 等待读完成
	tickstart = HAL_GetTick();
	while(READ_BIT(heth->Instance->MACMIIAR, ETH_MACMIIAR_MB))
	{
		if((HAL_GetTick() - tickstart ) > ETH_TIMEOUT_PHY_WRITE)
			return HAL_TIMEOUT;
	}

    if (RegValue)
    {
        *RegValue = (uint16_t)(heth->Instance->MACMIIDR);
    }

	heth->State = HAL_ETH_STATE_READY;

	return HAL_OK;
}

//	****************************************************************************
//	函数 ：	HAL_StatusTypeDef HAL_ETH_WritePHYRegister(ETH_HandleTypeDef *heth, uint16_t PHYReg, uint32_t RegValue);
//	功能 ：	写PHY寄存器
//	输入 ：	heth：ETH_HandleTypeDef结构体指针；
//			PHYReg：寄存器地址；
//			RegValue：写入数据；
//	输出 ：	无；
//	返回 ：	HAL_OK：写成功；
//			HAL_BUSY：忙；
//			HAL_TIMEOUT：写超时；
//			HAL_ERROR：PHY地址错误；
//	备注 ：	
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_WritePHYRegister(ETH_HandleTypeDef *heth, uint32_t PHYAddr, uint32_t PHYReg, uint32_t RegValue)
{
	volatile uint32_t tmpreg = 0;
	uint32_t tickstart = 0;

    if (READ_BIT(heth->Instance->MACMIIAR, ETH_MACMIIAR_MB))
        return HAL_BUSY;
    
    WRITE_REG(tmpreg, heth->Instance->MACMIIAR);
    
    MODIFY_REG(tmpreg, ETH_MACMIIAR_PA, (PHYAddr << ETH_MACMIIAR_PA_Pos));
    MODIFY_REG(tmpreg, ETH_MACMIIAR_MR, (PHYReg << ETH_MACMIIAR_MR_Pos));
    SET_BIT(tmpreg, ETH_MACMIIAR_MW);
    SET_BIT(tmpreg, ETH_MACMIIAR_MB);
    
    WRITE_REG(heth->Instance->MACMIIDR, RegValue);
    
    WRITE_REG(heth->Instance->MACMIIAR, tmpreg);
    
	//等待写入完成
	tickstart = HAL_GetTick();
	while(READ_BIT(heth->Instance->MACMIIAR, ETH_MACMIIAR_MB))
	{
		if((HAL_GetTick() - tickstart ) >= ETH_TIMEOUT_PHY_READ)
			return HAL_TIMEOUT;
	}

	return HAL_OK; 
}

//	****************************************************************************
//  
//                              Rx Delay
//  
//	****************************************************************************

HAL_StatusTypeDef HAL_ETH_RxClockDelayConfig(ETH_HandleTypeDef *heth, uint32_t uint, uint32_t len)
{
    SYSCFG->SYSCR |= SYSCFG_SYSCR_ETHMAC_RX_DLYSEL;
    ETH_DLYB->CR = DLYB_CR_DEN;
    ETH_DLYB->CR |= DLYB_CR_SEN;
    ETH_DLYB->CFGR = ((uint << DLYB_CFGR_UNIT_Pos) & DLYB_CFGR_UNIT_Msk) | ((len << DLYB_CFGR_SEL_Pos) & DLYB_CFGR_SEL_Msk);
    HAL_SimpleDelay(10);
    ETH_DLYB->CR &= ~DLYB_CR_SEN;
    
    return HAL_OK;
}


#endif





