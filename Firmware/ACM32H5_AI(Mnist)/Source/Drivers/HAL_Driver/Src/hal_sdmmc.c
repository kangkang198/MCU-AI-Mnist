/*
  ******************************************************************************
  * @file    HAL_SDMMC.c
  * @version V1.0.0
  * @date    2020
  * @brief   SDIO HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Secure Digital Input/Output(SDIO) Peripheral.
  *           @ Initialization and de-initialization functions
  *           @ Peripheral Control functions
  *           @ Standard commnad process functions
  ******************************************************************************
*/
#include "hal.h"

#ifdef HAL_SDMMC_MODULE_ENABLED

static const uint32_t BitWidthTbl[] = {SDMMC_BW_1, SDMMC_BW_4, SDMMC_BW_8, SDMMC_BW_1, SDMMC_BW_1, SDMMC_BW_4, SDMMC_BW_8};



static void sdmmc_set_blk_size(SDMMC_HandleTypeDef *hsdmmc, uint16_t BlkSize)
{
	hsdmmc->Instance->SDMMC_BLKSIZ = BlkSize;
}


void sdmmc_card_clk_en(SDMMC_HandleTypeDef *hsdmmc)
{
	hsdmmc->Instance->SDMMC_CLKENA |= (1<<hsdmmc->Init.Ch);
	hsdmmc->Instance->SDMMC_CMD = (SDMMC_START_CMD | SDMMC_UPDATE_CLK_ONLY | SDMMC_WAIT_PRVDATA_END);
	while((hsdmmc->Instance->SDMMC_CMD & SDMMC_START_CMD) != 0);
}


void sdmmc_card_clk_dis(SDMMC_HandleTypeDef *hsdmmc)
{
	hsdmmc->Instance->SDMMC_CLKENA &= (~(1<<hsdmmc->Init.Ch));
	hsdmmc->Instance->SDMMC_CMD = (SDMMC_START_CMD | SDMMC_UPDATE_CLK_ONLY | SDMMC_WAIT_PRVDATA_END);
	while((hsdmmc->Instance->SDMMC_CMD & SDMMC_START_CMD) != 0);
	
}


/*********************************************************************************
* Function    : HAL_SDMMC_MspInit
* Description : Initialize the SDIO MSP.
* Input       : hsdmmc: SDIO handle.
* Output      : status
**********************************************************************************/
__weak void HAL_SDMMC_MspInit(SDMMC_HandleTypeDef *hsdmmc)
{
	;
}


__weak void HAL_SDMMC_Sel_IO_Voltage(uint8_t LDO_SEL)
{
	;
}


/*********************************************************************************
* Function    : HAL_SDMMC_MspDeInit
* Description : DeInitialize the SDMMC MSP.
* Input       : hsdmmc: SDIO handle.
* Output      : status
**********************************************************************************/
void HAL_SDMMC_MspDeInit(SDMMC_HandleTypeDef *hsdmmc)
{
    /* 
      NOTE: This function should be modified, when the callback is needed,
      the HAL_SDIO_MspDeInit can be implemented in the user file.
    */
	;
}

/*********************************************************************************
* Function    : HAL_SDMMC_Init
* Description : Initialize the SDIO according to the specified parameters
*               in the SDMMC_InitTypeDef
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Init(SDMMC_HandleTypeDef *hsdmmc)
{
	int i;
	
#ifdef USE_FULL_ASSERT
	if(!IS_SDMMC_CH_VLD(hsdmmc->Init.Ch))						return HAL_ERROR;
	if(!IS_SDMMC_ALL_INSTANCE(hsdmmc->Instance))				return HAL_ERROR;
    if (!IS_SDMMC_VLD_MODE(hsdmmc->Init.TransMode))      		return HAL_ERROR;
	if(!IS_SDMMC_VLD_BW(hsdmmc->Init.TransBW))					return HAL_ERROR;
#endif

    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_SDMMC_MspInit(hsdmmc);

	HAL_RCC_SDMMCClockSourceConfig(SDMMC_CLK_SRC_SYS_CLK);
	HAL_RCC_SDMMCSampleClockSourceConfig(SDMMC_SAMPLE_CLK_SDIO);

	hsdmmc->Instance->SDMMC_CTRL |= (SDMMC_CTRL_CTRL_RST | SDMMC_CTRL_FIFO_RST | SDMMC_CTRL_IDMA_RST); 	//reset SDIO Controller/FIFO/DMA
	while(hsdmmc->Instance->SDMMC_CTRL & (SDMMC_CTRL_CTRL_RST | SDMMC_CTRL_FIFO_RST | SDMMC_CTRL_IDMA_RST));

	hsdmmc->Instance->SDMMC_PWREN |= SDMMC_POWER_ON(hsdmmc->Init.Ch);
	if(SD_IO_VCC_3V3==hsdmmc->Init.SDSigVoltage)
	{
		hsdmmc->Instance->SDMMC_CLKENA |= SDMMC_LOW_POWER(hsdmmc->Init.Ch); //low power mode
	}

	hsdmmc->Instance->SDMMC_RINTSTS = 0x03FFFF;	//clear all int status of current sdio channel
	hsdmmc->Instance->SDMMC_UHS_REG = 0;


#ifdef	SDMMC_INT_MODE
	NVIC_ClearPendingIRQ(SDMMC_IRQn);
	NVIC_EnableIRQ(SDMMC_IRQn);
	hsdmmc->Instance->SDMMC_INTMASK = (0xFF|(1<<hsdmmc->Init.Ch));	//enable all int src of current sdio channel
//	hsdmmc->Instance->SDMMC_INTMASK = (((1<<2)|(1<<11))|(1<<hsdmmc->Init.Ch));	//enable all int src of current sdio channel
	hsdmmc->Instance->SDMMC_CTRL |= SDMMC_CTRL_INT_EN;
#endif

	if(hsdmmc->Init.IDmaEn)	//IDMA enabled
	{
		hsdmmc->Instance->SDMMC_CTRL |= SDMMC_CTRL_USE_IDMA;
		hsdmmc->Instance->SDMMC_BMOD = (SDMMC_BMOD_IDMA_PBL|SDMMC_BMOD_IDMA_EN);
	}

	hsdmmc->Instance->SDMMC_CTYPE = (SDMMC_BW_1<<hsdmmc->Init.Ch);	//Sigle wire mode while initialize
	hsdmmc->Instance->SDMMC_TMOUT = SDMMC_TIMEOUT_RW | SDMMC_TIMEOUT_RESP ; //Set read data and wait response timeout value
	hsdmmc->Instance->SDMMC_BLKSIZ = SDMMC_BLOCK_SIZE;
	hsdmmc->Instance->SDMMC_FIFOTH = SDMMC_RX_LEVEL | SDMMC_TX_LEVEL;
	hsdmmc->Instance->SDMMC_DEBNCE = SDMMC_DEBOUNCE_COUNT;

	if(hsdmmc->Init.CardType ==EMMC_CARD)
	{
		hsdmmc->SdEmmcRegInfo.rca = EMMC_RCA_VALUE;
		hsdmmc->SdEmmcRegInfo.hcs = EMMC_HCS;
	}
	else
	{
		hsdmmc->SdEmmcRegInfo.rca = 0;
		hsdmmc->SdEmmcRegInfo.hcs = SD_HCS;
	}

	HAL_SDMMC_Sel_IO_Voltage(SD_IO_VCC_3V3);

	return HAL_OK;
}


void sdio_idma_desc_link(SDMMC_IDMA_DESC_INFO * sdio_idma_desc)
{
	uint32_t i;
	SDMMC_IDMA_DESC_INFO *idam_desc;

	idam_desc = sdio_idma_desc;

	for(i=0; i<16; i++)
	{
		idam_desc->IDMA_Desc3_buf_addr2 = (uint32_t)(idam_desc+1);
		idam_desc++;
	}
	idam_desc->IDMA_Desc3_buf_addr2 = 0;
}


/*********************************************************************************
* Function    : HAL_SDMMC_SetClk
* Description : Set SDIO clock source and clock divide value
* Input       : hsdmmc: SDMMC handle.
*				div:	divide value
*				clk_src:clock source
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_SetClk(SDMMC_HandleTypeDef *hsdmmc, uint32_t div, uint32_t clk_src)
{
//	RCC->PER_CFGR = ((RCC->PER_CFGR & ~SDMMC_CLK_SRC_MSK) | SDMMC_CLK_SRC);

	hsdmmc->Instance->SDMMC_CLKENA &= ~(1<<hsdmmc->Init.Ch);	//stop clk
	hsdmmc->Instance->SDMMC_CMD = (SDMMC_START_CMD | SDMMC_UPDATE_CLK_ONLY | SDMMC_WAIT_PRVDATA_END);
	while((hsdmmc->Instance->SDMMC_CMD & SDMMC_START_CMD) != 0);

	hsdmmc->Instance->SDMMC_CLKSRC = ((hsdmmc->Instance->SDMMC_CLKSRC & (~(3<<(hsdmmc->Init.Ch<<1))))| (clk_src<<(hsdmmc->Init.Ch<<1)));
	hsdmmc->Instance->SDMMC_CLKDIV = ((hsdmmc->Instance->SDMMC_CLKDIV & (~(0xFF<<(clk_src<<3))))|(div<<(clk_src<<3)));
	hsdmmc->Instance->SDMMC_CMD = (SDMMC_START_CMD | SDMMC_UPDATE_CLK_ONLY | SDMMC_WAIT_PRVDATA_END);
	while((hsdmmc->Instance->SDMMC_CMD & SDMMC_START_CMD) != 0);

	hsdmmc->Instance->SDMMC_CLKENA |= (1<<hsdmmc->Init.Ch);	//enable clk
	hsdmmc->Instance->SDMMC_CMD = (SDMMC_START_CMD | SDMMC_UPDATE_CLK_ONLY | SDMMC_WAIT_PRVDATA_END);
	while((hsdmmc->Instance->SDMMC_CMD & (SDMMC_START_CMD)) != 0);

	hsdmmc->Instance->SDMMC_CLKENA |= (1<<hsdmmc->Init.Ch);	//enable clk
	hsdmmc->Instance->SDMMC_CMD = (SDMMC_START_CMD | SDMMC_UPDATE_CLK_ONLY | SDMMC_WAIT_PRVDATA_END);
	while((hsdmmc->Instance->SDMMC_CMD & (SDMMC_START_CMD)) != 0);

	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd_NoDat
* Description : Send command without argument
* Input       : hsdmmc: SDMMC handle.
*				cmd:	command
*				cmd_arg:argument of current command
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd_NoDat(SDMMC_HandleTypeDef *hsdmmc, uint32_t cmd, uint32_t cmd_arg)
{
	while(hsdmmc->Instance->SDMMC_STATUS&(1<<9));	//wait idle
	hsdmmc->Instance->SDMMC_RINTSTS = 0x03FFFF;

	hsdmmc->Instance->SDMMC_CMDARG = cmd_arg;

	hsdmmc->Instance->SDMMC_CMD = (cmd | (hsdmmc->Init.Ch<<16));

#ifdef	SDMMC_INT_MODE
	while(!(hsdmmc->Intflg&SDMMC_RINT_CMD_CMPLT));	//wait for fifo empty
	hsdmmc->Intflg &= ~SDMMC_RINT_CMD_CMPLT;
#else
	while(!(hsdmmc->Instance->SDMMC_RINTSTS&SDMMC_RINT_CMD_CMPLT));	//wait for command transfer completed
	hsdmmc->Instance->SDMMC_RINTSTS = SDMMC_RINT_CMD_CMPLT; 	//clear flg
#endif

	if(cmd == CMD1_MATCH_VCC)  //R3
	{
		if(hsdmmc->Instance->SDMMC_RINTSTS & SDMMC_RINT_RESP_TIMOUT)
		{
			hsdmmc->Instance->SDMMC_RINTSTS = SDMMC_RINT_RESP_TIMOUT;
			return HAL_ERROR;
		}
	}
	else
	{
		//error:ack/ack_crc,ack_timeout
		if(hsdmmc->Instance->SDMMC_RINTSTS & (SDMMC_RINT_RESP_ERR | SDMMC_RINT_RESP_CRC_ERR | SDMMC_RINT_RESP_TIMOUT))
		{
			hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_RESP_ERR | SDMMC_RINT_RESP_CRC_ERR | SDMMC_RINT_RESP_TIMOUT);
			return HAL_TIMEOUT;
		}
	}

	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd_RdDat
* Description : command process which return data
* Input       : hsdmmc: SDMMC handle.
*				cmd:	Command
*				cmd_arg:Argument of current command
*				length: Read data length
*				buff:	Read data buffer
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd_RdDat(SDMMC_HandleTypeDef *hsdmmc, uint32_t cmd, uint32_t cmd_arg, uint32_t length, uint32_t *buff)
{
	uint32_t i;
	uint32_t mask;
	uint32_t len, addr;
	uint32_t idma_trans_cnt=0;
	SDMMC_IDMA_DESC_INFO IdmaDesc[SDMMC_IDMA_DESC_NUM];

	hsdmmc->Instance->SDMMC_CTRL |= (SDMMC_CTRL_FIFO_RST | SDMMC_CTRL_IDMA_RST); 	//reset SDIO FIFO/DMA
	while(hsdmmc->Instance->SDMMC_CTRL & (SDMMC_CTRL_FIFO_RST | SDMMC_CTRL_IDMA_RST));

	if(hsdmmc->Init.IDmaEn)
	{
		hsdmmc->Instance->SDMMC_CTRL = SDMMC_CTRL_IDMA_RST;
		hsdmmc->Instance->SDMMC_BMOD |= SDMMC_BMOD_SWR;
		len = length;
		addr = (uint32_t)buff;
		for(i=0; i<SDMMC_IDMA_DESC_NUM; i++)
		{
			IdmaDesc[i].IDMA_Desc0_ctrl_stas = (SDMMC_IDMA_DESC_OWN|SDMMC_IDMA_DESC_CHAINED|((0==i)?SDMMC_IDMA_DESC_FST:0));	//addr2 include next descriptor address
			IdmaDesc[i].IDMA_Desc1_buf_size = ((len>=SDMMC_IDMA_MAX_SIZE)? SDMMC_IDMA_MAX_SIZE:len);
			IdmaDesc[i].IDMA_Desc2_buf_addr1 = addr;
			len -= IdmaDesc[i].IDMA_Desc1_buf_size;
			addr += IdmaDesc[i].IDMA_Desc1_buf_size;
			idma_trans_cnt++;
			if(i==(SDMMC_IDMA_DESC_NUM-1))
			{
				IdmaDesc[i].IDMA_Desc3_buf_addr2 = (uint32_t)&IdmaDesc[0];
			}
			else
			{
				IdmaDesc[i].IDMA_Desc3_buf_addr2 = (uint32_t)&IdmaDesc[i+1];
			}

			if(0==len)
			{
				IdmaDesc[i].IDMA_Desc0_ctrl_stas &= ~SDMMC_IDMA_DESC_CHAINED;
				IdmaDesc[i].IDMA_Desc0_ctrl_stas |= (SDMMC_IDMA_DESC_LAST);
				break;
			}
		}
		hsdmmc->Instance->SDMMC_CTRL |= SDMMC_CTRL_USE_IDMA;
		hsdmmc->Instance->SDMMC_DBADDR = (uint32_t)IdmaDesc;
		hsdmmc->Instance->SDMMC_IDINTEN |= SDMMC_IDINTEN_RI;
	}

	while(hsdmmc->Instance->SDMMC_STATUS&(1<<9));	//wait idle
	hsdmmc->Instance->SDMMC_RINTSTS = 0x03FFFF; 	//clear all int status

	hsdmmc->Instance->SDMMC_BYTCNT = length;
	hsdmmc->Instance->SDMMC_CMDARG = cmd_arg;
	hsdmmc->Instance->SDMMC_CMD = (cmd | (hsdmmc->Init.Ch<<16));

#ifdef	SDMMC_INT_MODE
	while(!(hsdmmc->Intflg&SDMMC_RINT_CMD_CMPLT));	//wait for fifo empty
	hsdmmc->Intflg &= ~SDMMC_RINT_CMD_CMPLT;
#else
	while(!(hsdmmc->Instance->SDMMC_RINTSTS&SDMMC_RINT_CMD_CMPLT));	//wait for command transfer completed
	hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_CMD_CMPLT|(1<<(hsdmmc->Init.Ch+16)));
	
#endif

	if(hsdmmc->Init.IDmaEn)
	{
		i=0;
		while(idma_trans_cnt)
		{
			while(!(hsdmmc->Instance->SDMMC_IDSTS&SDMMC_IDSTS_RI));
			hsdmmc->Instance->SDMMC_IDSTS = SDMMC_IDSTS_RI;

			//error:ack/ack_crc,ack_timeout
			if(hsdmmc->Instance->SDMMC_RINTSTS & (SDMMC_RINT_RESP_ERR | SDMMC_RINT_RESP_CRC_ERR | SDMMC_RINT_RESP_TIMOUT))
			{
				hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_RESP_ERR | SDMMC_RINT_RESP_CRC_ERR | SDMMC_RINT_RESP_TIMOUT | (1<<hsdmmc->Init.Ch));
				return HAL_TIMEOUT;
			}

			idma_trans_cnt--;
			if(len)
			{
				IdmaDesc[i].IDMA_Desc0_ctrl_stas = (SDMMC_IDMA_DESC_OWN|SDMMC_IDMA_DESC_CHAINED);	//addr2 include next descriptor address
				IdmaDesc[i].IDMA_Desc1_buf_size = ((len>=SDMMC_IDMA_MAX_SIZE)? SDMMC_IDMA_MAX_SIZE:len);
				IdmaDesc[i].IDMA_Desc2_buf_addr1 = addr;
				len -= IdmaDesc[i].IDMA_Desc1_buf_size;
				addr += IdmaDesc[i].IDMA_Desc1_buf_size;
				idma_trans_cnt++;
				if(i==(SDMMC_IDMA_DESC_NUM-1))
				{
					IdmaDesc[i].IDMA_Desc3_buf_addr2 = (uint32_t)IdmaDesc;
				}
				else
				{
					IdmaDesc[i].IDMA_Desc3_buf_addr2 = (uint32_t)&IdmaDesc[i+1];
				}

				if(0==len)
				{
					IdmaDesc[i].IDMA_Desc0_ctrl_stas |= SDMMC_IDMA_DESC_LAST;
				}
			}
		}
	}
	else
	{
		//error:ack/ack_crc,ack_timeout
		if(hsdmmc->Instance->SDMMC_RINTSTS & (SDMMC_RINT_RESP_ERR | SDMMC_RINT_RESP_CRC_ERR | SDMMC_RINT_RESP_TIMOUT))
		{
			hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_RESP_ERR | SDMMC_RINT_RESP_CRC_ERR | SDMMC_RINT_RESP_TIMOUT | (1<<hsdmmc->Init.Ch));
			return HAL_TIMEOUT;
		}

		for(i=0;i<((length+3)>>2);i++)
		{
			while(hsdmmc->Instance->SDMMC_STATUS&SDMMC_FIFO_EMPTY);	//wait while fifo is empty
			buff[i] = hsdmmc->Instance->SDMMC_DATA;
		}
	}

#ifdef	SDMMC_INT_MODE
	while(hsdmmc->Intflg&SDMMC_RINT_DAT_TRANS_CMPLT);	//wait for data transfer completed
	hsdmmc->Intflg &= ~SDMMC_RINT_DAT_TRANS_CMPLT;
#else
	while(!(hsdmmc->Instance->SDMMC_RINTSTS & SDMMC_RINT_DAT_TRANS_CMPLT));	//wait for data transfer completed
	hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_DAT_TRANS_CMPLT | (1<<hsdmmc->Init.Ch)); 	//clear flg
#endif

	while(hsdmmc->Instance->SDMMC_STATUS & (1<<9));	//Wait D0 idle
	
	if(hsdmmc->Instance->SDMMC_STATUS & 0x3FFE0000)		//FIFO not empty
	{
		hsdmmc->Instance->SDMMC_CTRL |= SDMMC_CTRL_FIFO_RST;	//Reset fifo
		while(hsdmmc->Instance->SDMMC_CTRL & SDMMC_CTRL_FIFO_RST);
	}

	mask = ((cmd ==CMD14_BUSTEST_R)? 0xA200 : 0xA280);
	
	if(hsdmmc->Instance->SDMMC_RINTSTS & mask)
	{
		hsdmmc->Instance->SDMMC_RINTSTS = (mask | (1<<hsdmmc->Init.Ch));
		return HAL_TIMEOUT;
	}

	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd_WrDat
* Description : command process which write data
* Input       : hsdmmc: SDMMC handle.
*				cmd:	Command
*				cmd_arg:Argument of current command
*				length: Read data length
*				buff:	Read data buffer
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd_WrDat(SDMMC_HandleTypeDef *hsdmmc, uint32_t cmd, uint32_t cmd_arg, uint32_t length, uint32_t *buff)
{
	uint32_t i;
	uint32_t len, addr;
	uint32_t idma_trans_cnt=0;
	SDMMC_IDMA_DESC_INFO IdmaDesc[SDMMC_IDMA_DESC_NUM];

	if(hsdmmc->Init.IDmaEn)
	{
		hsdmmc->Instance->SDMMC_CTRL = SDMMC_CTRL_IDMA_RST;
		hsdmmc->Instance->SDMMC_BMOD |= SDMMC_BMOD_SWR;
		len = length;
		addr = (uint32_t)buff;
		for(i=0; i<SDMMC_IDMA_DESC_NUM; i++)
		{
			IdmaDesc[i].IDMA_Desc0_ctrl_stas = (SDMMC_IDMA_DESC_OWN|SDMMC_IDMA_DESC_CHAINED|((0==i)?SDMMC_IDMA_DESC_FST:0));	//addr2 include next descriptor address
			IdmaDesc[i].IDMA_Desc1_buf_size = ((len>=SDMMC_IDMA_MAX_SIZE)? SDMMC_IDMA_MAX_SIZE:len);
			IdmaDesc[i].IDMA_Desc2_buf_addr1 = addr;
			len -= IdmaDesc[i].IDMA_Desc1_buf_size;
			addr += IdmaDesc[i].IDMA_Desc1_buf_size;
			idma_trans_cnt++;
			if(i==(SDMMC_IDMA_DESC_NUM-1))
			{
				IdmaDesc[i].IDMA_Desc3_buf_addr2 = (uint32_t)&IdmaDesc[0];
			}
			else
			{
				IdmaDesc[i].IDMA_Desc3_buf_addr2 = (uint32_t)&IdmaDesc[i+1];
			}
			if(0==len)
			{
				IdmaDesc[i].IDMA_Desc0_ctrl_stas &= ~SDMMC_IDMA_DESC_CHAINED;
				IdmaDesc[i].IDMA_Desc0_ctrl_stas |= (SDMMC_IDMA_DESC_LAST);
				break;
			}
		}

		hsdmmc->Instance->SDMMC_CTRL |= SDMMC_CTRL_USE_IDMA;
		hsdmmc->Instance->SDMMC_DBADDR = (uint32_t)IdmaDesc;
		hsdmmc->Instance->SDMMC_IDINTEN |= SDMMC_IDINTEN_TI;
	}

	while(hsdmmc->Instance->SDMMC_STATUS&(1<<9));	//wait idle
	hsdmmc->Instance->SDMMC_RINTSTS = 0x03FFFF; 	//clear all int status
	
	hsdmmc->Instance->SDMMC_BYTCNT = length;
	hsdmmc->Instance->SDMMC_CMDARG = cmd_arg;
	hsdmmc->Instance->SDMMC_CMD = (cmd | (hsdmmc->Init.Ch<<16));

#ifdef	SDMMC_INT_MODE
	while(!(hsdmmc->Intflg&SDMMC_RINT_CMD_CMPLT));	//wait for fifo empty
	hsdmmc->Intflg &= ~SDMMC_RINT_CMD_CMPLT;
#else
	while(!(hsdmmc->Instance->SDMMC_RINTSTS&SDMMC_RINT_CMD_CMPLT));	//wait for command transfer completed
	hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_CMD_CMPLT | (1<<(hsdmmc->Init.Ch+16))); 	//clear flg
#endif

	if(hsdmmc->Init.IDmaEn)
	{
		i=0;
		while(idma_trans_cnt)
		{
			while(!(hsdmmc->Instance->SDMMC_IDSTS&SDMMC_IDSTS_TI));
			hsdmmc->Instance->SDMMC_IDSTS = SDMMC_IDSTS_TI;

			//error:ack/ack_crc,ack_timeout
			if(hsdmmc->Instance->SDMMC_RINTSTS & (SDMMC_RINT_RESP_ERR | SDMMC_RINT_RESP_CRC_ERR | SDMMC_RINT_RESP_TIMOUT))
			{
				hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_RESP_ERR | SDMMC_RINT_RESP_CRC_ERR | SDMMC_RINT_RESP_TIMOUT | (1<<hsdmmc->Init.Ch));
				return HAL_TIMEOUT;
			}

			idma_trans_cnt--;
			if(len)
			{
				IdmaDesc[i].IDMA_Desc0_ctrl_stas = (SDMMC_IDMA_DESC_OWN|SDMMC_IDMA_DESC_CHAINED);	//addr2 include next descriptor address
				IdmaDesc[i].IDMA_Desc1_buf_size = ((len>=SDMMC_IDMA_MAX_SIZE)? SDMMC_IDMA_MAX_SIZE:len);
				IdmaDesc[i].IDMA_Desc2_buf_addr1 = addr;
				len -= IdmaDesc[i].IDMA_Desc1_buf_size;
				addr += IdmaDesc[i].IDMA_Desc1_buf_size;
				idma_trans_cnt++;
				if(i==(SDMMC_IDMA_DESC_NUM-1))
				{
					IdmaDesc[i].IDMA_Desc3_buf_addr2 = (uint32_t)&IdmaDesc[0];
				}
				else
				{
					IdmaDesc[i].IDMA_Desc3_buf_addr2 = (uint32_t)&IdmaDesc[i+1];
				}
				if(0==len)
				{
					IdmaDesc[i].IDMA_Desc0_ctrl_stas |= SDMMC_IDMA_DESC_LAST;
				}
			}
		}
	}
	else
	{
		//error:ack/ack_crc,ack_timeout
		if(hsdmmc->Instance->SDMMC_RINTSTS & (SDMMC_RINT_RESP_ERR | SDMMC_RINT_RESP_CRC_ERR | SDMMC_RINT_RESP_TIMOUT))
		{
			hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_RESP_ERR | SDMMC_RINT_RESP_CRC_ERR | SDMMC_RINT_RESP_TIMOUT | (1<<hsdmmc->Init.Ch));
			return HAL_TIMEOUT;
		}

		for(i=0;i<((length+3)>>2);i++)
		{
			while(!(hsdmmc->Instance->SDMMC_STATUS&SDMMC_FIFO_TX_LEV_DOWN));	//wait while fifo level is low than tx level
			hsdmmc->Instance->SDMMC_DATA = buff[i];
		}
	}

#ifdef	SDMMC_INT_MODE
	while(hsdmmc->Intflg&SDMMC_RINT_DAT_TRANS_CMPLT);	//wait for fifo empty
	hsdmmc->Intflg &= ~SDMMC_RINT_DAT_TRANS_CMPLT;
#else
	while(!(hsdmmc->Instance->SDMMC_RINTSTS & SDMMC_RINT_DAT_TRANS_CMPLT));	//wait for command transfer completed
	hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_DAT_TRANS_CMPLT | (1<<hsdmmc->Init.Ch)); 	//clear flg
#endif

	hsdmmc->Instance->SDMMC_CTRL |= SDMMC_CTRL_FIFO_RST;	//Reset fifo
	while(hsdmmc->Instance->SDMMC_STATUS & (1<<9));	//Wait card idle
	
	if(cmd !=CMD19_BUSTEST_W)
	{
		if(hsdmmc->Instance->SDMMC_RINTSTS & (SDMMC_RINT_DAT_CRC_ERR | SDMMC_RINT_EBIT_WCRC_ERR))
		{
			hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_DAT_CRC_ERR | SDMMC_RINT_EBIT_WCRC_ERR | (1<<hsdmmc->Init.Ch));
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd0_GoIdle
* Description : command process which write data
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd0_GoIdle(SDMMC_HandleTypeDef *hsdmmc)
{
	uint32_t cmd_arg;

	cmd_arg = ((hsdmmc->Init.CardType==EMMC_CARD)? 0xF0F0F0F0 : 0);
	return HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD0_GO_IDLE, cmd_arg);
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd1_SendOp
* Description : 
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd1_SendOp(SDMMC_HandleTypeDef *hsdmmc)
{
	uint32_t cmd_arg;
	uint32_t i, t=0;
	uint32_t resp_tbl[10];

	if(hsdmmc->Init.CardType != EMMC_CARD) return 0xFF;
	
	cmd_arg= (hsdmmc->SdEmmcRegInfo.hcs<<30)|EMMC_VDD_WINDOW;
	
	while(1)
	{
		if(HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD1_MATCH_VCC, cmd_arg))
		{
			return	HAL_ERROR;
		}

		if(t<10)
		{
			resp_tbl[t++] = hsdmmc->Instance->SDMMC_RESP0;
		}
		if(hsdmmc->Instance->SDMMC_RESP0 & (1UL<<31))	//Wait internal power up routine finish
		{
			for(i=0; i<t; i++)
			{
				printfS("Resp[%d]: %08x\r\n", i, resp_tbl[i]);
			}
		
			break;
		}

		i=200;
		while(i--);
	}

	if(((hsdmmc->Instance->SDMMC_RESP0>>30)&0x01) != hsdmmc->SdEmmcRegInfo.hcs)	 //capacity is not compatible
	{
		hsdmmc->SdEmmcRegInfo.hcs = ((hsdmmc->Instance->SDMMC_RESP0>>30)&0x01);
	}

	hsdmmc->SdEmmcRegInfo.ocr = hsdmmc->Instance->SDMMC_RESP0;
	
	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd2_GetCid
* Description : 
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd2_GetCid(SDMMC_HandleTypeDef *hsdmmc)
{
	if(HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD2_CID, 0))	//enter pre idle state
	{
		return HAL_ERROR;
	}

	hsdmmc->SdEmmcRegInfo.cid[0] = hsdmmc->Instance->SDMMC_RESP0;
	hsdmmc->SdEmmcRegInfo.cid[1] = hsdmmc->Instance->SDMMC_RESP1;
	hsdmmc->SdEmmcRegInfo.cid[2] = hsdmmc->Instance->SDMMC_RESP2;
	hsdmmc->SdEmmcRegInfo.cid[3] = hsdmmc->Instance->SDMMC_RESP3;
	
	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd3_Rca
* Description : 
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd3_Rca(SDMMC_HandleTypeDef *hsdmmc)
{
	uint32_t result;
	uint32_t cmd_arg;

	cmd_arg = ((hsdmmc->Init.CardType==EMMC_CARD)? (hsdmmc->SdEmmcRegInfo.rca<<16) : 0);

	if(0!=(result=HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD3_RCA, cmd_arg)))
	{
		return result;
	}

	if(hsdmmc->Init.CardType == SD_CARD)
	{
		hsdmmc->SdEmmcRegInfo.rca = (hsdmmc->Instance->SDMMC_RESP0>>16);
	}

	return HAL_OK;
}


/*********************************************************************************
* Function    : HAL_SDMMC_Cmd5_Sleep
* Description : Switch eMMC card to sleep/awake mode.
* Input       : hsdmmc: SDMMC handle.
*				sleep_awake: 1-sleep  0-awake
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd5_Sleep(SDMMC_HandleTypeDef *hsdmmc, uint8_t sleep_awake)
{
	uint32_t cmd_arg;

	if(hsdmmc->Init.CardType == SD_CARD)
	{
		return HAL_OK;
	}

	cmd_arg = (sleep_awake? (hsdmmc->SdEmmcRegInfo.rca|(1<<15)) : hsdmmc->SdEmmcRegInfo.rca);

	return HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD5_SLEEP, cmd_arg);
}



/*********************************************************************************
* Function    : HAL_EMMC_Cmd6_Switch
* Description : 
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/

HAL_StatusTypeDef HAL_EMMC_Cmd6_Switch(SDMMC_HandleTypeDef *hsdmmc, uint8_t index, uint8_t Val)
{
	uint32_t cmd_arg;

	cmd_arg = (MMC_SWITCH_MODE_WRITE_BYTE<<24) | (index<<16) | (Val<<8);
	return HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD6_SWTICH, cmd_arg);
}


HAL_StatusTypeDef HAL_SD_Cmd6_Switch(SDMMC_HandleTypeDef *hsdmmc, uint32_t cmd_arg, uint32_t *pRespBuf)
{
	uint32_t result=0;

	if(NULL == pRespBuf)
	{
		return 0x02;
	}
	sdmmc_set_blk_size(hsdmmc, 64);
	result = HAL_SDMMC_Cmd_RdDat(hsdmmc, CMD6_SWTICH, cmd_arg, 64, pRespBuf);
	sdmmc_set_blk_size(hsdmmc, SDMMC_BLOCK_SIZE);

	if(result)
	{
		return	0x01;
	}
	return 0;
}

//switch access mode of SD card
HAL_StatusTypeDef HAL_SD_Cmd6_Switch_AM(SDMMC_HandleTypeDef *hsdmmc, uint8_t AccessMode)
{
	uint32_t result=0;
	uint32_t cmd_arg;
	uint8_t tmp_buf[64];

	//bit31:  0-check mode   1-switch mode
	cmd_arg = ((1UL<<31) | 0x00000000 | (AccessMode<<0) | (3<<12));	//DDR50 mode  and 800mA limit

#if 0
	if(0!=(result=HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD6_SWTICH, cmd_arg)))
#else
	sdmmc_set_blk_size(hsdmmc, 64);
	if(0!=(result=HAL_SDMMC_Cmd_RdDat(hsdmmc, (CMD6_SWTICH|(1<<9)), cmd_arg, 64, (uint32_t *)tmp_buf)))
#endif
	{
		return result;
	}

	sdmmc_set_blk_size(hsdmmc, SDMMC_BLOCK_SIZE);
	if(SD_ACCESS_MODE_DDR50==AccessMode)
	{
		hsdmmc->Instance->SDMMC_UHS_REG |= (1UL<<(hsdmmc->Init.Ch+16));
	}
	else
	{
		hsdmmc->Instance->SDMMC_UHS_REG &= (~(1UL<<(hsdmmc->Init.Ch+16)));
	}

	return 0;
}


//send tuning pattern
HAL_StatusTypeDef HAL_SD_Cmd19_Tuning_Pattern(SDMMC_HandleTypeDef *hsdmmc)
{
	uint32_t result=0;

	if(0!=(result=HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD19_BUSTEST_W, 0)))
	{
		return result;
	}

	return 0;
}


/*********************************************************************************
* Function    : HAL_SDMMC_Cmd6_SwitchBitW
* Description : 
* Input       : hsdmmc: SDMMC handle.
*				bus_width: destinate bus width
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd6_SwitchBitW(SDMMC_HandleTypeDef *hsdmmc, uint32_t bus_width)
{
	uint32_t result=0;
	uint32_t cmd_arg;
	uint32_t temp;

	if((bus_width)==SDMMC_TRANS_BW_4)			cmd_arg = 0x03B70100;
	else if ((bus_width)==SDMMC_TRANS_BW_8) cmd_arg = 0x03B70200;
	else if ((bus_width)==SDMMC_TRANS_DDR_4) cmd_arg = 0x03B70500;
	else if ((bus_width)==SDMMC_TRANS_DDR_8) cmd_arg = 0x03B70600;
	else							return 0x01;

	result=HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD6_SWTICH, cmd_arg);
	if(result)
	{
		return	0x02;
	}

	hsdmmc->Instance->SDMMC_CTYPE &= ~((1UL<<hsdmmc->Init.Ch) | (1UL<<(16+hsdmmc->Init.Ch)));
	hsdmmc->Instance->SDMMC_CTYPE |= (BitWidthTbl[hsdmmc->Init.TransBW]<<hsdmmc->Init.Ch);

	if(SDMMC_MODE_DDR==hsdmmc->Init.TransMode)
	{
		hsdmmc->Instance->SDMMC_UHS_REG |= (1<<(hsdmmc->Init.Ch+16));
	}

	return HAL_OK;
}


HAL_StatusTypeDef HAL_SD_Acmd6_set_bus_width(SDMMC_HandleTypeDef *hsdmmc, uint32_t bus_width)
{
	uint32_t result=0;
	uint32_t cmd_arg;
	uint32_t temp;

	result=HAL_SDMMC_cmd55_app(hsdmmc);
	if(result)
	{
		return	0x01;
	}

	if((bus_width&0x03)==SDMMC_TRANS_BW_1)	 		cmd_arg = 0x00;
	else if ((bus_width&0x03)==SDMMC_TRANS_BW_4)	cmd_arg = 0x02;
	else 							return 0x02;

	result=HAL_SDMMC_Cmd_NoDat(hsdmmc, ACMD6_SET_BUS_WIDTH, cmd_arg);
	if(result)
	{
		return	0x03;
	}

	hsdmmc->Instance->SDMMC_CTYPE &= ~((1UL<<hsdmmc->Init.Ch) | (1UL<<(16+hsdmmc->Init.Ch)));
	hsdmmc->Instance->SDMMC_CTYPE |= (BitWidthTbl[hsdmmc->Init.TransBW]<<hsdmmc->Init.Ch);

	return	0;
}


/*********************************************************************************
* Function    : HAL_SDMMC_Cmd7_Sel
* Description : 
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd7_Sel(SDMMC_HandleTypeDef *hsdmmc)
{
	uint32_t cmd_arg;
	
	cmd_arg = hsdmmc->SdEmmcRegInfo.rca<<16;
	return HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD7_SELECT_CARD, cmd_arg);
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd8_GetExtCsd
* Description : 
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd8_GetExtCsd(SDMMC_HandleTypeDef *hsdmmc, uint32_t *buff)
{
	uint32_t cmd_arg;
	uint32_t result=0;

	if(hsdmmc->Init.CardType==EMMC_CARD)
	{
		cmd_arg = 0;
		return HAL_SDMMC_Cmd_RdDat(hsdmmc, CMD8_EXT_CSD_EMMC, cmd_arg, 512, buff);
	}
	else
	{
		cmd_arg = ((1<<8)|0xAA);  //2.7V~3.3V
		if(0!=(result=HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD8_EXT_CSD_SD, cmd_arg)))
		{
			return result;
		}
		
		if(hsdmmc->Instance->SDMMC_RESP0 != cmd_arg)
		{
			return HAL_ERROR;	//VCC out of range
		}
	}
	
	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd9_GetCsd
* Description : 
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd9_GetCsd(SDMMC_HandleTypeDef *hsdmmc)
{
	uint32_t result=0;

	if(0!=(result=HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD9_CSD, (hsdmmc->SdEmmcRegInfo.rca<<16))))
	{
		return result;
	}

	hsdmmc->SdEmmcRegInfo.csd[0] = hsdmmc->Instance->SDMMC_RESP0;
	hsdmmc->SdEmmcRegInfo.csd[1] = hsdmmc->Instance->SDMMC_RESP1;
	hsdmmc->SdEmmcRegInfo.csd[2] = hsdmmc->Instance->SDMMC_RESP2;
	hsdmmc->SdEmmcRegInfo.csd[3] = hsdmmc->Instance->SDMMC_RESP3;

	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd11_SwitchVoltage
* Description : switch to 1.8V bus signal level, only for SD card
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd11_SwitchVoltage(SDMMC_HandleTypeDef *hsdmmc)
{
	if(hsdmmc->Init.CardType==EMMC_CARD)
	{
		return HAL_OK;
	}

	while(hsdmmc->Instance->SDMMC_STATUS&(1<<9));	//wait idle
	hsdmmc->Instance->SDMMC_RINTSTS = 0x03FFFF;
	hsdmmc->Instance->SDMMC_CMDARG = 0;
	hsdmmc->Instance->SDMMC_CMD = (CMD11_SWITCH_VOLTAGE | (hsdmmc->Init.Ch<<16));

	//wait for Volt_switch_int
	HAL_Delay(2);
	if(!(hsdmmc->Instance->SDMMC_RINTSTS & SDMMC_RINT_DTO_VSHINT))	//Wait IO voltage switch interrupt flg
	{
		return HAL_TIMEOUT;
	}
	hsdmmc->Instance->SDMMC_RINTSTS = SDMMC_RINT_DTO_VSHINT;	//clear Volt_switch_int flg

	//stop clk
	hsdmmc->Instance->SDMMC_CLKENA &= (~(1<<hsdmmc->Init.Ch));
	hsdmmc->Instance->SDMMC_CMD = (SDMMC_START_CMD | SDMMC_UPDATE_CLK_ONLY | (1<<28));

	//switch voltage
	HAL_SDMMC_Sel_IO_Voltage(SD_IO_VCC_1V8);
	hsdmmc->Instance->SDMMC_UHS_REG |= (1<<hsdmmc->Init.Ch);
	HAL_Delay(5);

	//start clk
	hsdmmc->Instance->SDMMC_CLKENA |= (1<<hsdmmc->Init.Ch);
	HAL_Delay(1);
	hsdmmc->Instance->SDMMC_CMD = (SDMMC_START_CMD | SDMMC_UPDATE_CLK_ONLY | (1<<28));
	HAL_Delay(1);

	while(!(hsdmmc->Instance->SDMMC_RINTSTS&SDMMC_RINT_CMD_CMPLT));	//wait for command transfer completed
	hsdmmc->Instance->SDMMC_RINTSTS = (SDMMC_RINT_CMD_CMPLT|SDMMC_RINT_DTO_VSHINT);	//clear Command done flg

	return 0;
}


HAL_StatusTypeDef HAL_SDMMC_Cmd12_StopStream(SDMMC_HandleTypeDef *hsdmmc)
{
	uint32_t cmd_arg;

	cmd_arg= hsdmmc->SdEmmcRegInfo.rca<<16;

	return HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD12_STOP_STEARM, cmd_arg);
}



/*********************************************************************************
* Function    : HAL_SDMMC_Cmd16_SetBlkLen
* Description : 
* Input       : hsdmmc: SDMMC handle.
*				block_size:
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd16_SetBlkLen(SDMMC_HandleTypeDef *hsdmmc, uint32_t block_size)
{
	return HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD16_SET_BLOCKLEN, block_size);
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd17_RdSingle
* Description : read single block
* Input       : hsdmmc: SDMMC handle.
*				block_size:
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd17_RdSingle(SDMMC_HandleTypeDef *hsdmmc, uint32_t blk_addr, uint32_t *buff)
{
	uint32_t addr;

	addr = ((hsdmmc->SdEmmcRegInfo.hcs==STANDRAD_CAPACITY)? blk_addr*SDMMC_BLOCK_SIZE : blk_addr);
	
	return HAL_SDMMC_Cmd_RdDat(hsdmmc, CMD17_READ_SINGLE, addr, SDMMC_BLOCK_SIZE, buff);
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd18_RdMul
* Description : read multiple block
* Input       : hsdmmc: SDMMC handle.
*				block_size:
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd18_RdMul(SDMMC_HandleTypeDef *hsdmmc, uint32_t blk_addr, uint32_t blk_num, uint32_t *buff)
{
	uint32_t addr;

	addr = ((hsdmmc->SdEmmcRegInfo.hcs==STANDRAD_CAPACITY)? blk_addr*SDMMC_BLOCK_SIZE : blk_addr);
	
	return HAL_SDMMC_Cmd_RdDat(hsdmmc, CMD18_READ_MUL, addr, blk_num*SDMMC_BLOCK_SIZE, buff);
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd24_WrSingle
* Description : write single block
* Input       : hsdmmc: SDMMC handle.
*				block_size:
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd24_WrSingle(SDMMC_HandleTypeDef *hsdmmc, uint32_t blk_addr, uint32_t *buff)
{
	uint32_t addr;

	addr = ((hsdmmc->SdEmmcRegInfo.hcs==STANDRAD_CAPACITY)? blk_addr*SDMMC_BLOCK_SIZE : blk_addr);
	
	return HAL_SDMMC_Cmd_WrDat(hsdmmc, CMD24_WRITE_SINGLE, addr, SDMMC_BLOCK_SIZE, buff);
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd25_WrMul
* Description : write single block
* Input       : hsdmmc: SDMMC handle.
*				block_size:
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd25_WrMul(SDMMC_HandleTypeDef *hsdmmc, uint32_t blk_addr, uint32_t blk_num, uint32_t *buff)
{
	uint32_t addr;

	addr = ((hsdmmc->SdEmmcRegInfo.hcs==STANDRAD_CAPACITY)? blk_addr*SDMMC_BLOCK_SIZE : blk_addr);
	
	return HAL_SDMMC_Cmd_WrDat(hsdmmc, CMD25_WRITE_MUL, addr, blk_num*SDMMC_BLOCK_SIZE, buff);
}

/*********************************************************************************
* Function    : HAL_SDMMC_Cmd28_Erase
* Description : erase destinate block
* Input       : hsdmmc: SDMMC handle.
*				block_size:
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Cmd28_Erase(SDMMC_HandleTypeDef *hsdmmc, uint32_t blk_start_addr, uint32_t blk_num)
{
	uint32_t cmd;
	uint32_t addr;
	uint32_t result;

	cmd = ((hsdmmc->Init.CardType==EMMC_CARD)? CMD35_ERASESD_START : CMD32_ERASESD_START);
	addr = ((hsdmmc->SdEmmcRegInfo.hcs==STANDRAD_CAPACITY)? blk_start_addr*SDMMC_BLOCK_SIZE : blk_start_addr);
	if(0!=(result=HAL_SDMMC_Cmd_NoDat(hsdmmc, cmd, addr)))
	{
		return result;
	}

	cmd = ((hsdmmc->Init.CardType==EMMC_CARD)? CMD36_ERASESD_END : CMD33_ERASESD_END);
	addr += ((hsdmmc->SdEmmcRegInfo.hcs==STANDRAD_CAPACITY)? ((blk_num-1)*SDMMC_BLOCK_SIZE) : ((blk_num-1)));
	if(0!=(result=HAL_SDMMC_Cmd_NoDat(hsdmmc, cmd, addr)))
	{
		return result;
	}
	
	return HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD38_ERASE, 0);
}

/*********************************************************************************
* Function    : HAL_SDMMC_cmd55_app
* Description : 
* Input       : hsdmmc: SDMMC handle.
*				block_size:
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_cmd55_app(SDMMC_HandleTypeDef *hsdmmc)
{
	return HAL_SDMMC_Cmd_NoDat(hsdmmc, CMD55_APP, (hsdmmc->SdEmmcRegInfo.rca<<16));
}

/*********************************************************************************
* Function    : HAL_SDMMC_Acmd6_SetBusW
* Description : erase destinate block
* Input       : hsdmmc: SDMMC handle.
*				block_size:
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Acmd6_SetBusW(SDMMC_HandleTypeDef *hsdmmc)
{
	uint32_t result=0;
	uint32_t cmd_arg;

	if(0!= (result=HAL_SDMMC_cmd55_app(hsdmmc)))
	{
		return result;
	}
	
	if(hsdmmc->Init.TransBW==SDMMC_TRANS_BW_1)
	{
		cmd_arg = 0x00;
	}
	else if(hsdmmc->Init.TransBW==SDMMC_TRANS_BW_4)
	{
		cmd_arg = 0x02;
	}
	else
	{
		return HAL_ERROR;
	}

	if(0!=(result=HAL_SDMMC_Cmd_NoDat(hsdmmc, ACMD6_SET_BUS_WIDTH, cmd_arg)))
	{
		return result;
	}

	hsdmmc->Instance->SDMMC_CTYPE &= ~((1UL<<hsdmmc->Init.Ch) | (1UL<<(16+hsdmmc->Init.Ch)));
	hsdmmc->Instance->SDMMC_CTYPE |= (BitWidthTbl[hsdmmc->Init.TransBW]<<hsdmmc->Init.Ch);
	
	return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_SDMMC_Acmd41_SendCond
* Description : erase destinate block
* Input       : hsdmmc: SDMMC handle.
*				block_size:
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SDMMC_Acmd41_SendCond(SDMMC_HandleTypeDef *hsdmmc, uint8_t power_level)
{
	uint32_t result=0;
	uint32_t arg;

	while(1)
	{
		if(0!=(result=HAL_SDMMC_cmd55_app(hsdmmc)))
		{
			return result;
		}

		if(SD_IO_VCC_3V3==power_level)
		{
			arg = (hsdmmc->SdEmmcRegInfo.hcs<<30)|SD_VDD_WINDOW;
		}
		else
		{
			arg = (hsdmmc->SdEmmcRegInfo.hcs<<30)|SD_VDD_WINDOW|(1<<24)|(1<<28);
		}
		
		if(0!=(result=HAL_SDMMC_Cmd_NoDat(hsdmmc, ACMD41_SEND_COND, arg)))
		{
			return result;
		}
		
		if(hsdmmc->Instance->SDMMC_RESP0 & (1UL<<31))
		{
			break;
		}
	}

	if(((hsdmmc->Instance->SDMMC_RESP0>>30)&0x01) != hsdmmc->SdEmmcRegInfo.hcs)	//capacity is not accordance
	{
		hsdmmc->SdEmmcRegInfo.hcs = ((hsdmmc->Instance->SDMMC_RESP0>>30)&0x01);
	}
	
	hsdmmc->SdEmmcRegInfo.ocr = hsdmmc->Instance->SDMMC_RESP0;

	if(SD_IO_VCC_1V8==power_level)
	{
		if(!(hsdmmc->Instance->SDMMC_RESP0&(1<<24)))	//SD card not support 1.8V signal voltage
		{
			hsdmmc->Init.SDSigVoltage = SD_IO_VCC_3V3;
		}
	}
	
	return HAL_OK;
}


HAL_StatusTypeDef HAL_SDMMC_Acmd51_SendScr(SDMMC_HandleTypeDef *hsdmmc, uint8_t *pScr)
{
	uint32_t result=0;
	uint32_t arg;
	uint32_t scrbuf[2];

	while(1)
	{
		if(0!=(result=HAL_SDMMC_cmd55_app(hsdmmc)))
		{
			return result;
		}

		if(0!=(result=HAL_SDMMC_Cmd_RdDat(hsdmmc, ACMD51_GET_SCR, 0, 2, (uint32_t *)pScr)))
		{
			return result;
		}

		if(hsdmmc->Instance->SDMMC_RESP0 & (1UL<<31))
		{
			break;
		}
	}

	if(((hsdmmc->Instance->SDMMC_RESP0>>30)&0x01) != hsdmmc->SdEmmcRegInfo.hcs)	//capacity is not accordance
	{
		hsdmmc->SdEmmcRegInfo.hcs = ((hsdmmc->Instance->SDMMC_RESP0>>30)&0x01);
	}

	hsdmmc->SdEmmcRegInfo.ocr = hsdmmc->Instance->SDMMC_RESP0;

	return HAL_OK;
}


/*********************************************************************************
* Function    : HAL_MMC_Enum
* Description : erase destinate block
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_EMMC_Enum(SDMMC_HandleTypeDef *hsdmmc, uint32_t SrcClk)
{
	uint32_t result=0;
	uint32_t div;

//	div=(SrcClk/400000)+4;	//set SDIO bus clock to (0~400KHz)
	div=(SrcClk/100000)+4;	//set SDIO bus clock to (0~400KHz)
//	div=div/2;

	if(0!=(result = HAL_SDMMC_SetClk(hsdmmc, div, SDMMC_CLK_SRC_DIV0)))
	{
		return result;
	}

	if(0!=(result = HAL_SDMMC_Cmd0_GoIdle(hsdmmc)))
	{
		return result;
	}

	if(0!=(result = HAL_SDMMC_Cmd1_SendOp(hsdmmc)))
	{
		return result;
	}

	if(0!=(result = HAL_SDMMC_Cmd2_GetCid(hsdmmc)))
	{
		return result;
	}

	if(0!=(result = HAL_SDMMC_Cmd3_Rca(hsdmmc)))
	{
		return result;
	}

	div = SrcClk/hsdmmc->Init.BusClk;
	if(SrcClk%hsdmmc->Init.BusClk)
	{
		div++;
	}
	printfS("SDMMC CLK= %d Mhz\n", (SrcClk/div)/1000000);

	return HAL_SDMMC_SetClk(hsdmmc, div, SDMMC_CLK_SRC_DIV1);
}

/*********************************************************************************
* Function    : HAL_SD_Enum
* Description : 
* Input       : hsdmmc: SDMMC handle.
* Output      : status
**********************************************************************************/
HAL_StatusTypeDef HAL_SD_Enum(SDMMC_HandleTypeDef *hsdmmc, uint32_t SrcClk)
{
	uint32_t result=0;
	uint32_t div;

	div=(SrcClk/400000)+4;	//set SDIO bus clock to (0~400KHz)
	div=div/2;

	if(0!=(result = HAL_SDMMC_SetClk(hsdmmc, div, SDMMC_CLK_SRC_DIV0)))
	{
		return result;
	}

	if(0!=(result = HAL_SDMMC_Cmd0_GoIdle(hsdmmc)))
	{
		return result;
	}

	if(0!=(result = HAL_SDMMC_Cmd8_GetExtCsd(hsdmmc, NULL)))
	{
		return result;
	}

	if(0!=(result = HAL_SDMMC_Acmd41_SendCond(hsdmmc, hsdmmc->Init.SDSigVoltage)))
	{
		return result;
	}

	if(SD_IO_VCC_1V8==hsdmmc->Init.SDSigVoltage)	//use only while switch to 1.8V
	{
		if(0!=(result = HAL_SDMMC_Cmd11_SwitchVoltage(hsdmmc)))
		{
			return result;
		}
	}

	if(0!=(result = HAL_SDMMC_Cmd2_GetCid(hsdmmc)))
	{
		return result;
	}

	return HAL_SDMMC_Cmd3_Rca(hsdmmc);
}



#endif


