/******************************************
*   Double-Data-Rate Octal SPI PSRAM
*   APS6408L-OBM-BA
******************************************/
#include "psram.h"

void APS6408L_DelayUs(uint32_t t)
{
  uint32_t i;
  for (; t > 0; t--) {
      for (i = 0; i < 44; i++);
  }
}

void APS6408L_DelayMs(uint32_t t)
{
  uint32_t i;
  for (; t > 0; t--) {
      for (i = 0; i < 44000; i++);
  }
}

/******************************************************************************
* @brief : APS6408L-OBM-BA OSPI initialization.
* @param : None
* @return: None
******************************************************************************/
void APS6408L_OBM_OSPI_Init(OSPI_HandleTypeDef *hospi)
{
    GPIO_InitTypeDef GPIO_Handle;
    
    OSPI_HandleTypeDef *XCCELAOPI_Handle = hospi;
    __HAL_RCC_OSPI1_CLK_ENABLE();
    __HAL_RCC_OSPI1_RESET();
 
    XCCELAOPI_Handle->Instance                = OSPI1;

    /* OSPI工作模式 */
    XCCELAOPI_Handle->Init.WorkMode           = OSPI_WORK_MODE_0;
    /* OSPI多线模式 */    
    XCCELAOPI_Handle->Init.XMode              = OSPI_8X_MODE;
    /* MSB/LSB在前选择 */        
    XCCELAOPI_Handle->Init.FirstBit           = OSPI_FIRSTBIT_MSB;
    /* 分频系数 */   
    XCCELAOPI_Handle->Init.BaudRatePrescaler  = OSPI_BAUDRATE_PRESCALER_2; 
    /* 采样延时 */     
    XCCELAOPI_Handle->Init.SampleShifting     = OSPI_SAMPLE_SHIFT_3HCLK;
    /* FIFO写模式 */     
    XCCELAOPI_Handle->Init.FWMode             = OSPI_FIFO_HALFWORD;
    /* FIFO读模式 */      
    XCCELAOPI_Handle->Init.FRMode             = OSPI_FIFO_HALFWORD;
    /* CS控制信号 */      
    XCCELAOPI_Handle->CSx                     = OSPI_CS_0;       

    HAL_OSPI_Init(XCCELAOPI_Handle); 

    XCCELA_RSTN_CLK_ENABLE();
    GPIO_Handle.Pin = XCCELA_RSTN_PIN;
    GPIO_Handle.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Handle.Pull = GPIO_NOPULL;
    GPIO_Handle.Drive = GPIO_DRIVE_LEVEL3;
    GPIO_Handle.Alternate = GPIO_FUNCTION_0;
    HAL_GPIO_Init(XCCELA_RSTN_GPIO, &GPIO_Handle);
    HAL_GPIO_WritePin(XCCELA_RSTN_GPIO, XCCELA_RSTN_PIN, GPIO_PIN_RESET); 

    // printfS("OSPI->BAUD = 0x%x\r\n", XCCELAOPI_Handle->Instance->BAUD);   
}

/******************************************************************************
* @brief : APS6408L-OBM-BA OSPI octal communication initialization.
* @param : None
* @return: None
******************************************************************************/
void  APS6408L_OBM_OSPI_Octal_Init(OSPI_HandleTypeDef *hospi)
{   
    OSPI_OctalInitTypeDef Xccela_OSPI_Octal = {0};
    OSPI_HandleTypeDef *XCCELAOPI_Handle = hospi;
    /* 双倍传输速率模式DTR */
    Xccela_OSPI_Octal.DTRMode = OSPI_DTRM_DTR;
    /* 数据选通使能 */         
    Xccela_OSPI_Octal.DQSMode = OSPI_DQSOE_ENABLE;
    /* 存储器类型 */     
    Xccela_OSPI_Octal.MemoryType = OSPI_MEM_XCCELA_OPI;
    /* DTR通信输出延迟 */   
    Xccela_OSPI_Octal.OutDelay = OSPI_TX_OUT_DELAY_HALF_HCLK;
    /* DQS采样使能 */  
    Xccela_OSPI_Octal.DQSSample = OSPI_DQS_SAMPLE_DISABLE;       
    
    HAL_OSPI_OctalInit(XCCELAOPI_Handle, &Xccela_OSPI_Octal);
   
}

/******************************************************************************
* @brief : APS6408L-OBM-BA reset.
* @param : None
* @return: None
******************************************************************************/
void APS6408L_OBM_GlobalReset(OSPI_HandleTypeDef *hospi)
{
    uint16_t write_buff[5];
    OSPI_HandleTypeDef *XCCELAOPI_Handle = hospi;
    //global reset 4clocks
    write_buff[0] = XCCELAOPI_GLOBAL_RESET;
    write_buff[0] += XCCELAOPI_GLOBAL_RESET << 8;//xx
    write_buff[1] = 0x0000;//dummy cycle 1
    write_buff[2] = 0x0000;//dummy cycle 2
    write_buff[3] = 0x0000;//dummy cycle 3
    write_buff[4] = 0x0000;//dummy cycle 4
    HAL_OSPI_TransmitByHalfWord(XCCELAOPI_Handle, write_buff, 5, 0); 
}

/******************************************************************************
* @brief : APS6408L-OBM-BA power-up initialization.
* @param : None
* @return: None
******************************************************************************/
void APS6408L_OBM_PowerUp_Init(OSPI_HandleTypeDef *hospi)
{
    APS6408L_OBM_OSPI_Init(hospi);
    
    APS6408L_OBM_OSPI_Octal_Init(hospi); 
    
    APS6408L_DelayUs(200); 

    HAL_GPIO_WritePin(XCCELA_RSTN_GPIO, XCCELA_RSTN_PIN, GPIO_PIN_SET);
    
    APS6408L_DelayMs(2);    
}

/******************************************************************************
* @brief : APS6408L-OBM-BA Memory mode access initialization.
* @param : None
* @return: None
******************************************************************************/
void APS6408L_OBM_OSPI_DTR_Memory_Init(OSPI_HandleTypeDef *hospi)
{
    OSPI_MemoryInitTypeDef XCCELAOPI_Memeory_Handle;
    OSPI_HandleTypeDef *XCCELAOPI_Handle = hospi;    
   
    /* 写指令 */
	XCCELAOPI_Memeory_Handle.WriteCmd = XCCELAOPI_SYNC_WRITE;
    /* 读指令 */
	XCCELAOPI_Memeory_Handle.ReadCmd = XCCELAOPI_SYNC_READ;
    /* 交替字节 */
	XCCELAOPI_Memeory_Handle.AlterByte = 0x00;  
    /* 回卷大小 */
    XCCELAOPI_Memeory_Handle.WrapSize = 0;
    /* 突发长度（Burst Length）*/
    XCCELAOPI_Memeory_Handle.BurstLen = MEMOACC2_BURST_LEN_32;
    /* Hyperbus或xSPI模式下，RWDS为一时的LC周期数 */                    
    XCCELAOPI_Memeory_Handle.HyperXspiLC1 = 0;
    /* Hyperbus或xSPI模式下，RWDS为零时的LC周期数 */                    
    XCCELAOPI_Memeory_Handle.HyperXspiLc0 = 0;                        
    
    /* [27]突发是Linear的还是Wrapped的 */
	XCCELAOPI_Memeory_Handle.HyperBurstType = MEMOACC1_BURST_WRAPPED;
    /* [26:25]数据模式，八线模式时，此位无效 */               
	XCCELAOPI_Memeory_Handle.DataMode = 0;
    /* [24:23]交替字节模式，八线模式时，此位无效 */                      
	XCCELAOPI_Memeory_Handle.AlterByteMode = 0;
    /* [22:21]地址模式，八线模式时，此位无效 */                
	XCCELAOPI_Memeory_Handle.AddrMode = 0;
    /* [20:19]指令模式，八线模式时，此位无效 */                      
	XCCELAOPI_Memeory_Handle.InstrMode = 0;
    /* [18:17]地址长度（Hyper必须为32 bit） */                     
	XCCELAOPI_Memeory_Handle.AddrWidth = MEMOACC1_ADDR_WIDTH_32;
    /* [16:12]dummy周期长度（Hyper/xSPI无效） */                     
	XCCELAOPI_Memeory_Handle.DummyCycleSize = MEMOACC1_DUMMY_CYCLE_4;
    /* [11]读操作空指令字节使能（Hyper必须为1）,dummy使能位,有dummy时必须置1 */               
	XCCELAOPI_Memeory_Handle.ReadDummyByteEnable = MEMOACC1_READ_DUMMY_ENABLE;
    /* [10]写操作空指令字节使能（Hyper必须为1）,dummy使能位,有dummy时必须置1 */                       
	XCCELAOPI_Memeory_Handle.WriteummyByteEnable = MEMOACC1_WRITE_DUMMY_ENABLE;
    /* [8:7]]交替字节长度 8 16 24 32，八线模式时，此位无效 */	                       
	XCCELAOPI_Memeory_Handle.AlterByteSize = 0; 
    /* [6]读操作交替字节使能位，八线模式时，此位无效 */               		
	XCCELAOPI_Memeory_Handle.ReadAlterByteEnable = 0; 
    /* [5]写操作交替字节使能位，八线模式时，此位无效 */                      
	XCCELAOPI_Memeory_Handle.WriteAlterByteEnable = 0; 
    /* [4]仅发送指令一次 */                      
	XCCELAOPI_Memeory_Handle.SendInstrOnce = 0; 
    /* [3]连续读使能 */                    
    XCCELAOPI_Memeory_Handle.ContinuousModeEnable = MEMOACC1_CON_ENABLE;
    /* [2]连续模式下CS拉高等待功能不使能 */                    
	XCCELAOPI_Memeory_Handle.CsTimeoutEnable = 0;           
    // XCCELAOPI_Memeory_Handle.CsTimeoutVal = 640;   // CsTimeoutVal * tHCLK <= 3us  for high temperature, CsTimeoutVal * tHCLK  <= 8us for room temperature as PSRAM Spec                    

    HAL_OSPI_MemoryInit(XCCELAOPI_Handle, &XCCELAOPI_Memeory_Handle);
}

/******************************************************************************
* @brief : APS6408L-OBM-BA Test.
* @param : None
* @return: None
******************************************************************************/
void PSRAM_Init(void)
{ 
    OSPI_HandleTypeDef XCCELAOPI_Handle;
    APS6408L_OBM_PowerUp_Init(&XCCELAOPI_Handle);

    APS6408L_OBM_OSPI_DTR_Memory_Init(&XCCELAOPI_Handle);
    
    HAL_OSPI_MemoryEnableDisable(&XCCELAOPI_Handle,  MEMOACC1_MEMORY_ENABLE); //[1]存储器访问使能
}

void SystemInit_ExtMemCtl(void)
{
    PSRAM_Init();
}

#if 0
#define OBM_BUFF_LEN            (256)
#define OBM_HALF_BUFF_LEN       (OBM_BUFF_LEN/2)
#define OBM_QUARTER_UFF_LEN     (OBM_BUFF_LEN/4)
#define OBM_DATA_16BIT          (0x1616)
#define OBM_DATA_32BIT          (0x32323232)
// OSPI_HandleTypeDef XCCELAOPI_Handle;
// OSPI_MemoryInitTypeDef XCCELAOPI_Memeory_Handle;
// OSPI_OctalInitTypeDef Xccela_OSPI_Octal = {0};
void APS6408L_OBM_OSPI_DTR_Memory_8bit_Write_Read(void)
{
    volatile uint8_t *pMem8;
    volatile uint16_t *pMem16;
    uint16_t i, err_count = 0;
    uint8_t writeBuf[OBM_BUFF_LEN];
    uint8_t readBuf[OBM_BUFF_LEN]; 
    
    // HAL_OSPI_MemoryEnableDisable(&XCCELAOPI_Handle,  MEMOACC1_MEMORY_ENABLE); //[1]存储器访问使能
    
    pMem8 = (volatile uint8_t *) (OSPI_MEMORY_ADDR + 0x1000);
    pMem16 = (volatile uint16_t *) (OSPI_MEMORY_ADDR + 0x1000);
    for(i = 0; i < OBM_BUFF_LEN; i++)
    {
        writeBuf[i] = i;
        *(pMem16 + i) = 0x0000;
    }
    
    //写
    printfS("Memory write in 8-bit mode...\r\n"); 
    for(i = 0; i < OBM_BUFF_LEN; i++)
    {
        *(pMem8 + i) = writeBuf[i];
    }    

    HAL_Delay(10);

    //读
    pMem8 = (volatile uint8_t *) (OSPI_MEMORY_ADDR + 0x1000);
    printfS("Memory read in 8-bit mode...\r\n"); 
    memset(readBuf, 0 , OBM_BUFF_LEN);
    for( i = 0; i < OBM_BUFF_LEN; i ++)
    {
        readBuf[i] = *(pMem8 + i);
    }
	//比对
    for(i = 0; i < OBM_BUFF_LEN; i++)
    {
        if(readBuf[i] != writeBuf[i])
        {
            printfS("[%d]: Write = 0x%02x, Read = 0x%02x\r\n", i, writeBuf[i], readBuf[i]); 
            err_count++;
        }
    }
    
    if(err_count)
    {
        printfS("APS6408L_OBM Memory 8-bit read fail!!!\r\n");
    }
    else
    {
        printfS("APS6408L_OBM Memory 8-bit read Success!!!\r\n");
    }
    printfS("************************************************\r\n"); 
    
    
}
#endif