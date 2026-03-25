/*
  ******************************************************************************
  * @file    HAL_SDMMC.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of SDMMC HAL module.
  ******************************************************************************
*/
#ifndef __HAL_SDMMC_H__
#define __HAL_SDMMC_H__

#include "hal.h"


//#define SDMMC_INT_MODE


/******************************************************************************/
/*                    Peripheral Registers Bits Definition                    */
/******************************************************************************/

#define FCLK  220


#define	SDMMC_CH0								0
#define	SDMMC_CH1								1

#define	EMMC_CARD								0
#define SD_CARD									1

#define SDMMC_IDMA_DESC_NUM						16

//refer register RCC_PERCFGR
#define SDMMC_CLK_SRC_SYS_CLK					(0<<11)	//select SYS_CLK as SDIO source clock
#define SDMMC_CLK_SRC_PLL2_P_CLK				(1<<11)	//select PLL2_P_CLK as SDIO source clock
#define SDMMC_CLK_SRC_MSK						(1<<11)
#define SDMMC_CLK_SRC							SDMMC_CLK_SRC_SYS_CLK


//refer register RCC_PERCFGR
#define SDMMC_SAMPLE_CLK_DELAY_BLK				0	//DLYB enable
#define SDMMC_SAMPLE_CLK_C1_FEEDBACK			1	//card1 feedback clock
#define SDMMC_SAMPLE_CLK_C2_FEEDBACK			2	//card2 feedback clock
#define SDMMC_SAMPLE_CLK_SDIO					3	//bypass DLYB


#define SDMMC_BUS_CLK_FREQ						((FCLK/8)*1000000)


#define	SDMMC_CLK_SRC_DIV0						0	//clk src from DIV0
#define	SDMMC_CLK_SRC_DIV1						1	//clk src from DIV1 
#define	SDMMC_CLK_SRC_DIV2						2	//clk src from DIV2
#define	SDMMC_CLK_SRC_DIV3						3	//clk src from DIV3

#define	SDMMC_POWER_ON(x)						(1<<x)		  //(x:sdio_index )
#define	SDMMC_LOW_POWER(x)						(1<<(16+x))	//lowpower mode	   (x:sdio_index )

#define SDMMC_MODE_SDR							0
#define SDMMC_MODE_DDR							1

#define SDMMC_FIFO_EMPTY						(1<<2)
#define SDMMC_FIFO_FULL							(1<<3)
#define SDMMC_FIFO_TX_NOT_FULL					(1<<1)
#define SDMMC_FIFO_TX_LEV_DOWN					(1<<1)
#define SDMMC_FIFO_RX_LEV_UP					(1<<0)

#define SDMMC_TRANS_BW_1						0
#define SDMMC_TRANS_BW_4						1
#define SDMMC_TRANS_BW_8						2
#define SDMMC_TRANS_DDR_4						5
#define SDMMC_TRANS_DDR_8						6


#define SDMMC_BW_1								((0<<16)|(0<<0))
#define SDMMC_BW_4								((0<<16)|(1<<0))
#define SDMMC_BW_8								((1<<16)|(0<<0))

#define	SDMMC_TIMEOUT_RW						(0xFFFFFFUL<<8)		//timeout for RW
#define	SDMMC_TIMEOUT_RESP						(0xFF<<0)	//timeout for response

#define	SDMMC_BLOCK_SIZE						512
#define SDMMC_IDMA_MAX_SIZE						(SDMMC_BLOCK_SIZE*8)
#define SDMMC_PBL_VAL							2	//Programmable Burst Length
#define SDMMC_IDMA_RT_THREAD					(1<<(SDMMC_PBL_VAL+1))
#define	SDMMC_RX_LEVEL							(SDMMC_IDMA_RT_THREAD<<16)
#define	SDMMC_TX_LEVEL							(SDMMC_IDMA_RT_THREAD<<0)
#define	SDMMC_DEBOUNCE_COUNT					0xFFFFF;
#define	SDMMC_START_CMD							(1UL<<31)	//start cmd
#define	SDMMC_UPDATE_CLK_ONLY					(1<<21)		//update clk only	
#define	SDMMC_WAIT_PRVDATA_END					(1<<13)		//wait prv data finish	


//SDMMC_CTRL
#define SDMMC_CTRL_CTRL_RST						(1<<0)
#define SDMMC_CTRL_FIFO_RST						(1<<1)
#define SDMMC_CTRL_IDMA_RST						(1<<2)
#define SDMMC_CTRL_INT_EN						(1<<4)
#define SDMMC_CTRL_USE_IDMA						(1<<25)	//use IDMA in data transfer

//BOMD
#define SDMMC_BMOD_IDMA_PBL						(SDMMC_PBL_VAL<<8)	//threshhold = 2^(n+1)Bytes
#define SDMMC_BMOD_SWR							(1<<0)	//IDMA soft reset, auto cleared after 1 AHB clock
#define SDMMC_BMOD_DSL_SHFT						2	//Bit[6:2]:Descriptor skip length in 32bit, only for double cache buffer descriptor
#define SDMMC_BMOD_IDMA_EN						(1<<7)	//IDMA enable

//raw int status
#define SDMMC_RINT_CARD_DCT						(1<<0)	//Card detected
#define SDMMC_RINT_RESP_ERR						(1<<1)	//Response error
#define SDMMC_RINT_CMD_CMPLT					(1<<2)	//Command completed
#define SDMMC_RINT_DAT_TRANS_CMPLT				(1<<3)	//Data transfer completed
#define SDMMC_RINT_S_FIFO_REQ					(1<<4)	//Send fifo request
#define SDMMC_RINT_R_FIFO_REQ					(1<<5)	//Receive fifo request
#define SDMMC_RINT_RESP_CRC_ERR					(1<<6)	//Response CRC error
#define SDMMC_RINT_DAT_CRC_ERR					(1<<7)	//Data CRC error
#define SDMMC_RINT_RESP_TIMOUT					(1<<8)	//Response timeout
#define SDMMC_RINT_RDAT_TIMOUT					(1<<9)	//READ data timeout
#define SDMMC_RINT_DTO_VSHINT					(1<<10)	//Data abscent timeout/Volage shift interrupted
#define SDMMC_RINT_FIFO_OV						(1<<11)	//FIFO overflow
#define SDMMC_RINT_HW_WR_LCK_ERR				(1<<12)	//hardware write lock error
#define SDMMC_RINT_SBIT_ERR						(1<<13)	//Start bit error/Busy clear error
#define SDMMC_RINT_AUTO_CMPLT_ERR				(1<<14)	//Auto complete error
#define SDMMC_RINT_EBIT_WCRC_ERR				(1<<15)	//Complete bit error in read/Without CRC in write

//IDSTS
#define SDMMC_IDSTS_TI							(1<<0)	//Data transmit completed of a descriptor
#define SDMMC_IDSTS_RI							(1<<1)	//Data receive completed of a descriptor
#define SDMMC_IDSTS_FBE							(1<<2)	//fatal bus error
#define SDMMC_IDSTS_DU							(1<<4)	//Descriptor is unavaliable
#define SDMMC_IDSTS_CES							(1<<5)	//Card error summary
#define SDMMC_IDSTS_NIS							(1<<8)	//Normal error summary
#define SDMMC_IDSTS_AIS							(1<<9)	//Abnormal interrupt summary
#define SDMMC_IDSTS_FSM_MSK						(0x0F<<13)

//IDINTEN
#define SDMMC_IDINTEN_TI						(1<<0)	//Data transmit completed of a descriptor
#define SDMMC_IDINTEN_RI						(1<<1)	//Data receive completed of a descriptor


//IDMA descriptor
#define SDMMC_IDMA_DESC_DIC						(1<<1)	//Disable interrupt on completion
#define SDMMC_IDMA_DESC_LAST					(1<<2)	//Last descriptor
#define SDMMC_IDMA_DESC_FST						(1<<3)	//First descriptor
#define SDMMC_IDMA_DESC_CHAINED					(1<<4)	//Second address chained
#define SDMMC_IDMA_DESC_ER						(1<<5)	//End of ring
#define SDMMC_IDMA_DESC_OWN						(1<<31)	//owner of descriptor, HOST or IDMAC


//command
#define CMD0_GO_IDLE							0x8000C000     //go idle
#define CMD1_MATCH_VCC							0x80000041     //turn on for match vcc //only for EMMC
#define CMD2_CID								0x800001c2     //initial card get CID
#define CMD3_RCA								0x80000143     //comfire/read RCA to card
#define CMD5_SLEEP								0x80002145	   //switch eMMC card between sleep mode and awake mode
#define CMD6_SWTICH					    		0x80002146     //switch function
#define CMD7_SELECT_CARD						0x80002147     //select card
#define CMD8_EXT_CSD_SD							0x80002148     //get EXT_CSD (value on CMD line )
#define CMD8_EXT_CSD_EMMC						0x80002348     //get EXT_CSD (value on DATA line )
#define CMD9_CSD								0x800021c9     //get CSD
#define CMD11_SWITCH_VOLTAGE					0x9000214B     //switch to 1.8V bus signal level
//#define CMD10_CID								0x800021ca     //get CID at transfers
#define CMD12_STOP_STEARM						0x8000614c     //stop block transfers 
#define CMD13_GET_STATUS						0x8000214D     //get card status
#define CMD14_BUSTEST_R				    		0x8000234E     //bus test read
#define CMD15_INACTIVE							0x8000610F     //make card to inactive
#define CMD16_SET_BLOCKLEN						0x80002150     //set card block length
#define CMD17_READ_SINGLE						0x80002351//0xA0002351     //single block read
#define CMD18_READ_MUL							0x80003352//0xA0003352     //multipe block read
#define CMD19_BUSTEST_W							0x80002753     //bus test
//#define CMD23_PRE_ERASE						0x80002157     //pre erase for write
#define CMD24_WRITE_SINGLE						0x80002758//0xA0002758	//0x80002758     //single block write
#define CMD25_WRITE_MUL							0x80003759//0xA0003759	//0x80003759     //multipe block write
//#define CMD27_PROG_CSD						0x8000275b     //programme csd
//#define CMD28_SET_PROTECT						0x8000215c     //set protect
#define CMD29_CLR_PROTECT						0x8000215d     //clearn protect
#define CMD30_SEND_WRITE						0x8000235e     //get the status about protect
#define CMD32_ERASESD_START						0x80002160     //set start erase SD card address
#define CMD33_ERASESD_END						0x80002161     //set end erase SD card address
#define CMD35_ERASESD_START						0x80002163     //set start erase EMMC card address
#define CMD36_ERASESD_END						0x80002164     //set end erase EMMC card address
#define CMD38_ERASE								0x80002166     //confirm erase
//#define CMD40_INT_MODE						0x80002168     //into interrput mode ( Class 9命令，三星KLMxGxxEMx 不支持)

#define CMD55_APP								0x80002177     //APP CMD
#define ACMD6_SET_BUS_WIDTH			    		0x80002146     //only for SD
#define ACMD13_GET_STATUS						0x8000234d     //get status 512 bit
#define ACMD41_SEND_COND						0x80002069     //FOR SD
#define ACMD42_DISCON_DATA3						0x8000216a     //make data3 disconnect
#define ACMD51_GET_SCR							0x80002373     //get card scr
                                        		
#define	EMMC_RCA_VALUE							0x0004

#define	STANDRAD_CAPACITY						0  	//standard capacity
#define	HIGH_CAPACITY							1  	//high capacity
#define EMMC_HCS								HIGH_CAPACITY
#define SD_HCS									HIGH_CAPACITY
#define EMMC_VDD_WINDOW 						0x80FF8000   //2.7~3.6v 
#define SD_VDD_WINDOW 							0x00FF8000   //2.7~3.6v 

//CMD6 ACCESS mode, refer to EMMC5.0 6.6.1 P41
#define MMC_SWITCH_MODE_CMD_SET					0x00	/* Change the command set */
#define MMC_SWITCH_MODE_SET_BITS				0x01	/* Set bits which are 1 in value */
#define MMC_SWITCH_MODE_CLEAR_BITS				0x02	/* Clear bits which are 1 in value */
#define MMC_SWITCH_MODE_WRITE_BYTE				0x03	/* Set target to value */


#define EMMC_EXT_CSD_PARTITION_ATTRIBUTE		156	/* R/W */
#define EMMC_EXT_CSD_PARTITION_SUPPORT			160	/* RO */
#define EMMC_EXT_CSD_WR_REL_PARAM				166	/* RO */
#define EMMC_EXT_CSD_ERASE_GROUP_DEF			175	/* R/W */
#define EMMC_EXT_CSD_PART_CONFIG				179	/* R/W */
#define EMMC_EXT_CSD_ERASED_MEM_CONT			181	/* RO */
#define EMMC_EXT_CSD_BUS_WIDTH					183	/* R/W */
#define EMMC_EXT_CSD_HS_TIMING					185	/* R/W */
#define EMMC_EXT_CSD_REV						192	/* RO */
#define EMMC_EXT_CSD_STRUCTURE					194	/* RO */
#define EMMC_EXT_CSD_CARD_TYPE					196	/* RO */
#define EMMC_EXT_CSD_PART_SWITCH_TIME			199 /* RO */
#define EMMC_EXT_CSD_SEC_CNT					212	/* RO, 4 bytes */
#define EMMC_EXT_CSD_S_A_TIMEOUT				217	/* RO */
#define EMMC_EXT_CSD_REL_WR_SEC_C				222	/* RO */
#define EMMC_EXT_CSD_HC_WP_GRP_SIZE				221	/* RO */
#define EMMC_EXT_CSD_ERASE_TIMEOUT_MULT			223	/* RO */
#define EMMC_EXT_CSD_HC_ERASE_GRP_SIZE			224	/* RO */
#define EMMC_EXT_CSD_BOOT_MULT					226	/* RO */
#define EMMC_EXT_CSD_SEC_TRIM_MULT				229	/* RO */
#define EMMC_EXT_CSD_SEC_ERASE_MULT				230	/* RO */
#define EMMC_EXT_CSD_SEC_FEATURE_SUPPORT		231	/* RO */
#define EMMC_EXT_CSD_TRIM_MULT					232	/* RO */

#define EMMC_CSD_HS_TIM_BK_COMPATB				0x00	//Selecting backwards compatibility interface timing
#define EMMC_CSD_HS_TIM_HS						0x01
#define EMMC_CSD_HS_TIM_HS200					0x02
#define EMMC_CSD_HS_TIM_HS400					0x03


#define SD_ACCESS_MODE_SDR12					0x00
#define SD_ACCESS_MODE_SDR25					0x01
#define SD_ACCESS_MODE_SDR50					0x02
#define SD_ACCESS_MODE_SDR104					0x03
#define SD_ACCESS_MODE_DDR50					0x04


//SD card perfermance select in ACMD41
#define SD_PERFERMANCE_PWR_SAVE					0x00
#define SD_PERFERMANCE_MAX						0x01


//SD card IO voltage select
#define SD_IO_VCC_1V8							0
#define SD_IO_VCC_3V3							1


/*
 * @brief SDMMC Init Structure definition
 */
typedef struct
{
	uint32_t IDMA_Desc0_ctrl_stas;

	uint32_t IDMA_Desc1_buf_size;

	uint32_t IDMA_Desc2_buf_addr1;	//buffer1 address

	uint32_t IDMA_Desc3_buf_addr2;	//buffer2 address or next descriptor address
}SDMMC_IDMA_DESC_INFO;

/*
 * @brief SDMMC Init Structure definition
 */
typedef struct
{
	uint32_t ocr;

	uint32_t cid[4];

	uint32_t csd[4];

	uint32_t rca;

	uint8_t hcs; //capacity staus, 1:high capacity ,0: standrad capacity

	uint8_t rsv[3];
}SDMMC_REG_INFO;

/*
 * @brief SDMMC Init Structure definition
 */
typedef struct
{
	uint8_t Ch;							/*!< Must be channel 0 or 1. */
	
	uint8_t CardType;                  	/*!< TF card or EMMC nand. */
	
	uint8_t TransMode;                  /*!< DDR/SDR. */

	uint8_t TransBW;                  	/*!< bus width: 1bit/4bit/8bit. */

	uint8_t IDmaEn;                  	/*!< IDMA enable. */

	uint8_t SDVConvEn;              	/*!< External voltage converter control enable. */

	uint8_t SDSigVoltage;				/*!< SD card Signal voltage switch to 1.8V enable. */

	uint8_t Rsv;                  		/*!< reserved. */
	
	uint32_t BusClk;					/*!< destinate bus clock frequency in Hz. */

//	SDMMC_IDMA_DESC_INFO *DbLL;			/*!< Point to descriptor base address link list*/

}SDMMC_InitTypeDef;

/*
 * @brief  SDMMC handle Structure definition
 */
typedef struct
{
    SDMMC_TypeDef         	*Instance;          /*!< SDMMC registers base address        */

	SDMMC_REG_INFO			SdEmmcRegInfo;
	
    SDMMC_InitTypeDef		Init;              	/*!< SDMMC communication parameters      */
	
	volatile uint32_t       Intflg;             /*!< SDMMC interrupt flg while interrupt is enabled  */
}SDMMC_HandleTypeDef;



#define IS_SDMMC_CH_VLD(CH)    				(((CH) == SDMMC_CH0) || \
											((CH) == SDMMC_CH1))

#define IS_SDMMC_ALL_INSTANCE(INSTANCE)    	((INSTANCE) == SDMMC)

#define IS_SDMMC_VLD_MODE(MODE)    			(((MODE) == SDMMC_MODE_SDR) || \
											((MODE) == SDMMC_MODE_DDR))

#define IS_SDMMC_VLD_BW(BW)    				(((BW) == SDMMC_TRANS_BW_1) || \
											((BW) == SDMMC_TRANS_BW_4) || \
											((BW) == SDMMC_TRANS_BW_8) || \
											((BW) == SDMMC_TRANS_DDR_4) || \
											((BW) == SDMMC_TRANS_DDR_8))
											




extern HAL_StatusTypeDef HAL_SDMMC_Init(SDMMC_HandleTypeDef *hsdmmc);

extern HAL_StatusTypeDef HAL_SDMMC_SetClk(SDMMC_HandleTypeDef *hsdmmc, uint32_t div, uint32_t clk_src);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd0_GoIdle(SDMMC_HandleTypeDef *hsdmmc);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd1_SendOp(SDMMC_HandleTypeDef *hsdmmc);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd2_GetCid(SDMMC_HandleTypeDef *hsdmmc);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd3_Rca(SDMMC_HandleTypeDef *hsdmmc);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd5_Sleep(SDMMC_HandleTypeDef *hsdmmc, uint8_t sleep_awake);

extern HAL_StatusTypeDef HAL_EMMC_Cmd6_Switch(SDMMC_HandleTypeDef *hsdmmc, uint8_t index, uint8_t Val);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd6_SwitchBitW(SDMMC_HandleTypeDef *hsdmmc, uint32_t bus_width);

extern HAL_StatusTypeDef HAL_SD_Acmd6_set_bus_width(SDMMC_HandleTypeDef *hsdmmc, uint32_t bus_width);

extern HAL_StatusTypeDef HAL_SD_Cmd6_Switch_AM(SDMMC_HandleTypeDef *hsdmmc, uint8_t AccessMode);


extern HAL_StatusTypeDef HAL_SDMMC_Cmd7_Sel(SDMMC_HandleTypeDef *hsdmmc);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd8_GetExtCsd(SDMMC_HandleTypeDef *hsdmmc, uint32_t *buff);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd9_GetCsd(SDMMC_HandleTypeDef *hsdmmc);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd11_SwitchVoltage(SDMMC_HandleTypeDef *hsdmmc);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd16_SetBlkLen(SDMMC_HandleTypeDef *hsdmmc, uint32_t block_size);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd17_RdSingle(SDMMC_HandleTypeDef *hsdmmc, uint32_t blk_addr, uint32_t *buff);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd18_RdMul(SDMMC_HandleTypeDef *hsdmmc, uint32_t blk_addr, uint32_t blk_num, uint32_t *buff);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd24_WrSingle(SDMMC_HandleTypeDef *hsdmmc, uint32_t blk_addr, uint32_t *buff);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd25_WrMul(SDMMC_HandleTypeDef *hsdmmc, uint32_t blk_addr, uint32_t blk_num, uint32_t *buff);

extern HAL_StatusTypeDef HAL_SDMMC_Cmd28_Erase(SDMMC_HandleTypeDef *hsdmmc, uint32_t blk_start_addr, uint32_t blk_num);

extern HAL_StatusTypeDef HAL_SDMMC_cmd55_app(SDMMC_HandleTypeDef *hsdmmc);

extern HAL_StatusTypeDef HAL_SDMMC_Acmd6_SetBusW(SDMMC_HandleTypeDef *hsdmmc);

extern HAL_StatusTypeDef HAL_SDMMC_Acmd41_SendCond(SDMMC_HandleTypeDef *hsdmmc, uint8_t power_level);

extern HAL_StatusTypeDef HAL_EMMC_Enum(SDMMC_HandleTypeDef *hsdmmc, uint32_t SrcClk);

extern HAL_StatusTypeDef HAL_SD_Enum(SDMMC_HandleTypeDef *hsdmmc, uint32_t SrcClk);



#endif
