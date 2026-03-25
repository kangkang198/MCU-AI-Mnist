/*****************************************************************
Copyright(C) 2008 - 2021, Shanghai AisinoChip Co.,Ltd.
@文件名称:	hal_norflash.c
@功能描述:	norflash模块函数。
@开发人员:	bobzhang 
@完成日期:	2023.1.18
@当前版本:	1.0
@修改记录:	
修改日期		修改人   		修改说明

******************************************************************/

/*****************************************************************
注意：如果使用 HAL_NORFLASH_ModifyData 函数，要求堆栈设置在6KB以上。
因为 HAL_NORFLASH_ModifyData 函数内部使用4KB堆栈空间，缓存扇区备份数据。
******************************************************************/

#include "hal_norflash.h"

#ifdef HAL_NORFLASH_MODULE_ENABLED

static uint8_t HAL_NORFLASH_EraseSector(uint32_t addr);
static uint8_t HAL_NORFLASH_EraseBlock32K(uint32_t addr);
static uint8_t HAL_NORFLASH_EraseBlock64K(uint32_t addr);
static uint8_t HAL_NORFLASH_ProgramPage(uint32_t addr, uint8_t *buff, uint32_t len);



//NORFLASH_ParamTypeDef NORFLASH_param = {0x200000, READ_DATA, 0, PAGE_PROGARM};
NORFLASH_ParamTypeDef NORFLASH_param = {0x200000, QUAD_IO_FAST_READ, 0x02, QUAD_PAGE_PROGRAM};

uint32_t HAL_NORFLASH_EnterCritical(void)
{
    uint32_t sr;
    sr = __get_PRIMASK();      
    __set_PRIMASK(1);
    SCB->ICSR = BIT25;   // clear systick pending bit     
    return sr;
}

void HAL_NORFLASH_ExitCritical(uint32_t sr)
{
    __set_PRIMASK(sr&0x01);
}



/*****************************************************************
@功能	NORFLASH初始化
@参数	无
@返回	HAL_OK-成功,HAL_ERROR-失败
******************************************************************/
uint8_t HAL_NORFLASH_Init(void)
{
//    uint32_t sr;
//    uint8_t paramBuff[32],ret;  
//    SPI_Flash_Parameter spiflashParam;
//    
//    spiflashParam.Command = READ_DATA;
//    spiflashParam.Delay = NORFLASH_OPRA_DELAY;
//    spiflashParam.Cont_MID = 0;  
//    spiflashParam.Dummy_bytes = 0;  
//    spiflashParam.Addr = 0;
//    spiflashParam.Addr_Length = 24;    
//    spiflashParam.Operation_length = 32;     
//    spiflashParam.Output_data = paramBuff; 
//    sr = HAL_NORFLASH_EnterCritical();
//    ret = SPI_Nor_Get_Parameter(&spiflashParam);
//    HAL_NORFLASH_ExitCritical(sr);
//    if(ret)
//    {
//        return HAL_ERROR;
//    }
//    
//    NORFLASH_param.chipSize = (paramBuff[4] | (paramBuff[5] << 8) | (paramBuff[6] << 16) | (paramBuff[7] << 24));
//    if(paramBuff[10]!=0)
//    {
//        NORFLASH_param.readCmd = paramBuff[10];
//        NORFLASH_param.readDummyBytes = paramBuff[11];  
//    }
//    else if(paramBuff[12]!=0)
//    {
//        NORFLASH_param.readCmd = paramBuff[12];
//        NORFLASH_param.readDummyBytes = paramBuff[13];  
//    }
//    else if(paramBuff[14]!=0)
//    {
//        NORFLASH_param.readCmd = paramBuff[14];
//        NORFLASH_param.readDummyBytes = paramBuff[15];  
//    }
//    else if(paramBuff[16]!=0)
//    {
//        NORFLASH_param.readCmd = paramBuff[16];
//        NORFLASH_param.readDummyBytes = paramBuff[17];  
//    }
//    else
//    {
//        NORFLASH_param.readCmd = READ_DATA;
//        NORFLASH_param.readDummyBytes = 0;  
//    }
//    
//    if(paramBuff[23]!=0)
//    {
//        NORFLASH_param.programCmd = paramBuff[23];
//    }
//    else if(paramBuff[22]!=0)
//    {
//        NORFLASH_param.programCmd = paramBuff[22];
//    }
//    else
//    {
//        NORFLASH_param.programCmd = PAGE_PROGARM; 
//    }
    
    return HAL_OK;      
}

/******************************************************************************
*@brief : read  Unique ID.
*@param : buff: save  Unique ID.
*@param : len: len of Unique ID.
*@return: HAL_OK,HAL_ERROR
******************************************************************************/
//9FH
uint8_t HAL_NORFLASH_ReadUniqueID(uint8_t *buff,uint32_t len)
{
    uint32_t sr;
    uint8_t ret;  
    SPI_Flash_Parameter spiflashParam;

    spiflashParam.SPI_Instance = (uint32_t)SPI7;
    spiflashParam.Command = SPI_READ_UNIQUE_ID;
    spiflashParam.Delay = 0xFF;
    spiflashParam.Operation_length = len;
    spiflashParam.Output_data_Addr = (uint32_t)buff;
    spiflashParam.Dummy_clks = 8;
    
    sr = HAL_NORFLASH_EnterCritical();
    ret=SPI_Nor_Read_Unique_ID(&spiflashParam);
    HAL_NORFLASH_ExitCritical(sr);
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK; 
}


/******************************************************************************
*@brief : read Manufacture ID , Device ID.
*@param : buff: save Manufacture ID , Device ID.length is 2.
*@return: HAL_OK,HAL_ERROR
******************************************************************************/
// 9FH 3 byte
uint8_t HAL_NORFLASH_ReadID(uint8_t *buff)
{
    uint32_t sr;
    uint8_t ret;  
    SPI_Flash_Parameter spiflashParam;

    spiflashParam.SPI_Instance = (uint32_t)SPI7;
    spiflashParam.Command = SPI_READ_ID_1S0S1S;
    spiflashParam.Delay = 0xFF;
    spiflashParam.Dummy_clks = 0;
    spiflashParam.Operation_length = 3;
    spiflashParam.Output_data_Addr = (uint32_t)buff;
    sr = HAL_NORFLASH_EnterCritical();
    ret=SPI_Nor_Read_MID_DID(&spiflashParam);
    HAL_NORFLASH_ExitCritical(sr);
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK; 
}

/*****************************************************************
@功能	设置低功耗模式。
@参数	mode
            BIT0=1: spi flash enter power down mode  
            BIT1=1: mcu enter deep sleep
            BIT2=1: mcu enter standby mode 
            BIT3=1: wakeup spi flash 
@返回	HAL_OK-成功,HAL_ERROR-失败
******************************************************************/
uint8_t HAL_NORFLASH_SetLowPowerMode(uint8_t mode)  
{
//    uint32_t sr;
//    uint8_t ret;  
//    SPI_Flash_Parameter spiflashParam;
//    
//    spiflashParam.Command = mode;   
//    spiflashParam.Delay = NORFLASH_OPRA_DELAY;
//    spiflashParam.Cont_MID = 0;  
//    
//    sr = HAL_NORFLASH_EnterCritical();
//    ret = SPI_Nor_Low_Power_Mode(&spiflashParam);  
//    HAL_NORFLASH_ExitCritical(sr);
//    
//    if(ret)
//    {
//        return HAL_ERROR;
//    }
	return HAL_OK;   
}

/*****************************************************************
@功能	复位MCU。复位后，系统会从ROM启动，进行各种标志判断，校验，通过后跳转到APP，失败则停留在BOOT模式。
@参数	无
@返回	无
******************************************************************/
void HAL_NORFLASH_ResetMcu(void)  
{
//    uint32_t sr;
//    uint8_t ret;  
//    SPI_Flash_Parameter spiflashParam;
//    
//    spiflashParam.Command = 0;   
//    spiflashParam.Delay = NORFLASH_OPRA_DELAY;
//    spiflashParam.Cont_MID = 0;  
//    spiflashParam.Operation_length = 0;     
//    spiflashParam.Dummy_bytes = 0; 
//    
//    sr = HAL_NORFLASH_EnterCritical();
//    ret = SPI_Nor_Flash_Reset_SOC(&spiflashParam);  
//    HAL_NORFLASH_ExitCritical(sr); 
}


/*****************************************************************
@功能	flash字节读。
@参数	addr - 起始地址
@参数	buf-数据缓存，字节地址 
@参数	len-读取的字节数 
@返回	HAL_OK-成功,HAL_ERROR-失败
******************************************************************/
uint8_t HAL_NORFLASH_Read(uint32_t addr, uint8_t *buff, uint32_t len)
{
    uint32_t sr;
    uint8_t ret;  
    SPI_Flash_Parameter spiflashParam;

    spiflashParam.SPI_Instance = (uint32_t)SPI7;
    spiflashParam.Command = SPI_READ_DATA_1S1S1S_24;
    spiflashParam.Delay = 0xFFU;
    spiflashParam.Cont_MID = 0;     
    spiflashParam.Dummy_clks = 0;
    spiflashParam.Addr = addr;
    spiflashParam.Operation_length = len;     
    spiflashParam.Output_data_Addr = (uint32_t)buff;
    
    sr = HAL_NORFLASH_EnterCritical();
    ret=SPI_Nor_Read(&spiflashParam);
    HAL_NORFLASH_ExitCritical(sr);
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK; 
}




/*****************************************************************
@功能	擦除数据，支持跨扇区，不备份
@参数	addr - 擦除起始地址
@参数	len - 擦除长度
@返回	HAL_OK-成功 ,HAL_ERROR-失败
******************************************************************/
uint8_t HAL_NORFLASH_Erase(uint32_t addr, uint32_t len)
{
    uint8_t ret;
    uint32_t eraseAddr;  
       
    eraseAddr = addr &  (~NORFLASH_SECTOR_SIZE_MASK);//扇区首地址
    len += (addr &  NORFLASH_SECTOR_SIZE_MASK);
    while(len)
    {
        if(((eraseAddr&NORFLASH_BLOCK_64K_SIZE_MASK)==0) && (len>=NORFLASH_BLOCK_64K_SIZE))
        {
            ret=HAL_NORFLASH_EraseBlock64K(eraseAddr); 
            if(ret)
            {
                return HAL_ERROR;
            }
            if(len > NORFLASH_BLOCK_64K_SIZE)
            {
                len -= NORFLASH_BLOCK_64K_SIZE;
            }
            else
            {
                len = 0;
            }            
            eraseAddr += NORFLASH_BLOCK_64K_SIZE;
        }
        else if(((eraseAddr&NORFLASH_BLOCK_32K_SIZE_MASK)==0) && (len>=NORFLASH_BLOCK_32K_SIZE))
        {
            ret=HAL_NORFLASH_EraseBlock32K(eraseAddr); 
            if(ret)
            {
                return HAL_ERROR;
            }
            
            if(len > NORFLASH_BLOCK_32K_SIZE)
            {
                len -= NORFLASH_BLOCK_32K_SIZE;
            }
            else
            {
                len = 0;
            } 
            eraseAddr += NORFLASH_BLOCK_32K_SIZE;
        }
        else
        {
            ret=HAL_NORFLASH_EraseSector(eraseAddr); 
            if(ret)
            {
                return HAL_ERROR;
            } 
            
            if(len > NORFLASH_SECTOR_SIZE)
            {
                len -= NORFLASH_SECTOR_SIZE;
            }
            else
            {
                len = 0;
            }             
            eraseAddr += NORFLASH_SECTOR_SIZE;
        }
    }
    return HAL_OK;	
}

/*****************************************************************
@功能	eflash编程数据。调用本函数前，请先擦除FLASH数据；
@参数	addr - 起始地址
@参数	buff-数据缓存，字节地址 
@参数	len-写入的字节数
@返回	HAL_OK-成功,HAL_ERROR-失败
******************************************************************/
uint8_t HAL_NORFLASH_Program(uint32_t addr, uint8_t *buff, uint32_t len)
{
    uint8_t ret;
    uint32_t offset,writeLen,writeAddr;
    
    offset = addr & NORFLASH_PAGE_SIZE_MASK;
    writeAddr = addr;
    
    while(len)
    {
        if((offset+len) < NORFLASH_PAGE_SIZE)
        {
            writeLen = len;  
        }
        else
        {
            writeLen = NORFLASH_PAGE_SIZE-offset;              
        }
        
        ret = HAL_NORFLASH_ProgramPage(writeAddr,buff,writeLen);
        if(ret != HAL_OK)
            return  HAL_ERROR;
        writeAddr += writeLen;
        buff += writeLen;
        len -= writeLen;
        offset = 0;
    }
	return HAL_OK;
}

/*****************************************************************
@功能	eflash写字节数据。自动擦除扇区再写入，支持跨页写。本函数内部使用4KB堆栈空间，缓存扇区备份数据。
@参数	addr - 起始地址
@参数	buff-数据缓存，字节地址 
@参数	len-写入的字节数
@返回	HAL_OK-成功,HAL_ERROR-失败
******************************************************************/
uint8_t HAL_NORFLASH_ModifyData(uint32_t addr, uint8_t *buff, uint32_t len)
{
    uint16_t offset; 
    uint16_t writeLen;
    uint32_t writeAddr;
    uint8_t *writePtr;    
    uint8_t  flash_buff[NORFLASH_SECTOR_SIZE];

    offset = (addr & NORFLASH_SECTOR_SIZE_MASK);	//在扇区内偏移
    writeAddr = addr - offset;                  //扇区起始地址

    while(len>0)
    {
        //本次写入长度
        if(len <= (NORFLASH_SECTOR_SIZE - offset))//写入数据不大于扇区内剩余空间，没有超过扇区范围
        {
            writeLen = len;
        }
        else
        {
            writeLen = NORFLASH_SECTOR_SIZE - offset;
        } 
        
        if(writeLen != NORFLASH_SECTOR_SIZE)//不是整扇区写入
        {
            HAL_NORFLASH_Read(writeAddr, flash_buff, NORFLASH_SECTOR_SIZE);//读出整扇区的内容
            memcpy(flash_buff+offset,buff,writeLen);
            
            writePtr = flash_buff;
        }
        else//整页写入
        {
            writePtr = buff;
        }
        
        //先擦除后写入1个扇区
        
        if(HAL_NORFLASH_EraseSector(writeAddr)!=HAL_OK)
        {
            return HAL_ERROR;
        }
        
        if(HAL_NORFLASH_Program(writeAddr,writePtr,NORFLASH_SECTOR_SIZE)!= HAL_OK)  
        {        
            return  HAL_ERROR;
        }
		     
        offset = 0;				                   //偏移位置为0 
        writeAddr += NORFLASH_SECTOR_SIZE;	       //写地址偏移        
        buff += writeLen;  	           //指针偏移
        len -= writeLen;	           //字节数递减
    }
	return HAL_OK;
}


/*****************************************************************
@功能	擦除BOOT标志
@参数	无
@返回	HAL_OK-成功 ,HAL_ERROR-失败
******************************************************************/
uint8_t HAL_NORFLASH_EraseBootFlag(void)
{
    uint8_t ret;
    uint8_t val[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    HAL_NORFLASH_ModifyData(0x1018, val, 4);
    
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK;  
}


void otfdec_key_reverse(uint8_t *data_in, uint32_t *data_out)
{
    uint32_t i;
    
    i = 0; 
    
    for(i = 0; i < 4; i++)  
    {
        data_out[i] =  (data_in[15-4*i] << 24) + (data_in[14-i*4] << 16) + (data_in[13-i*4] << 8) + (data_in[12-i*4] << 0);  
    }
}


// input value: pointer to 16 bytes key 
// return value: 1 means valid, other value means invalid  
uint8_t HAL_NORFLASH_SetEncryptionKey(uint8_t * key_input)  
{
    uint32_t sr;
    uint8_t ret;
    uint32_t key_reverse[8];
    SPI_Flash_Parameter spiflashParam;  
    
    otfdec_key_reverse( (uint8_t *)key_input, key_reverse);   
    key_reverse[7] = 0xFE01;  
    
    spiflashParam.SPI_Instance = (uint32_t)SPI7;
    spiflashParam.Command = SPI_CMD_ID_NOT_CARE;
    spiflashParam.Cont_MID = 0;  
    spiflashParam.Addr = 0;
    spiflashParam.Delay = 0xFFU;
    spiflashParam.Operation_length = 0;
    spiflashParam.Input_data_Addr = (uint32_t)key_reverse; 
    spiflashParam.Dummy_clks = 0; 

    sr = HAL_NORFLASH_EnterCritical();
    ret=SPI_SetEncrytionKey(&spiflashParam);
    HAL_NORFLASH_ExitCritical(sr);
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK; 
}

/*****************************************************************
@功能	加密编程。禁止跨页边界（256字节对齐）编程。
@参数	addr - 起始地址。必须加上0x08000000的基地址。非最后一页时，必须以128字节对齐
@参数	buff-数据缓存，地址必须4字节对齐。
@参数	wordLen-写入的WORD长度，非最后一页时，必须为32字长（128字节）或64字长（256字节）。 
@返回	HAL_OK-成功 ,HAL_ERROR-失败
******************************************************************/
uint8_t HAL_NORFLASH_EncryptProgram(uint32_t addr, uint32_t *data_in, uint32_t len, uint32_t *data_out)
{    
    SPI_Flash_Parameter  spiflashParam;   
    uint8_t ret; 
    uint32_t sr;
    
    spiflashParam.SPI_Instance = (uint32_t)SPI7;
    spiflashParam.Command = SPI_PROG_DATA_1S1S1S_24;
    spiflashParam.Cont_MID = 0;  
    spiflashParam.Addr = addr; 
    spiflashParam.Delay = 0xFFU;
    spiflashParam.Operation_length = len;  
    spiflashParam.Input_data_Addr = (uint32_t)data_in;     
    spiflashParam.Output_data_Addr = (uint32_t)data_out;   
    spiflashParam.Dummy_clks = 0; 
    
    sr = HAL_NORFLASH_EnterCritical();  
    ret = ( SPI_Nor_Encrypt_Data)(&spiflashParam);    
    HAL_NORFLASH_ExitCritical(sr);
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK;   

}

/*****************************************************************
@功能	修改SPI控制器寄存器配置
@参数	write_addr - SPI 寄存器地址
@参数	p_value-配置数据。
@参数	len-按字的长度 
@返回	HAL_OK-成功 ,HAL_ERROR-失败
******************************************************************/
uint8_t HAL_NORFLASH_ModifySPIControllerParam(uint32_t write_addr, uint32_t * p_value, uint32_t len)   
{
    SPI_Flash_Parameter  spiflashParam;   
    uint8_t ret;
    uint32_t sr;
       
    spiflashParam.SPI_Instance = (uint32_t)SPI7; 
    spiflashParam.Command = SPI_CMD_ID_NOT_CARE;     
    spiflashParam.Cont_MID = 0; 
    spiflashParam.Addr = write_addr;  
    spiflashParam.Delay = 0xFFU;      
    spiflashParam.Operation_length = len;  
    spiflashParam.Input_data_Addr = (uint32_t)p_value;    

    sr = HAL_NORFLASH_EnterCritical();  
    ret = (SPI_Nor_ModifyValue)(&spiflashParam);    
    HAL_NORFLASH_ExitCritical(sr);
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK;   
}  


/*****************************************************************
@功能	Modify baud rate of SPI
@参数	div: spi baud configuration, can set to 2, 4, 6, 8...
@参数	shift_clk- SPI_SHIFT_ZERO, SPI_SHIFT_1HCLK, ... 
@返回	0-成功 , others-失败
******************************************************************/
uint8_t HAL_NORFLASH_ModifyDivShift(uint32_t div, uint32_t shift_clk)   
{
    uint32_t reg_addr;
    uint32_t spi_data_write[4] = {0,}; 
    uint8_t ret;
    
    spi_data_write[0] = div; 
    spi_data_write[1] = SPI7->CTL;
    spi_data_write[2] = SPI7->TX_CTL;
    
    if (shift_clk < SPI_SHIFT_2P5HCLK)
    {
        spi_data_write[3] = (SPI7->RX_CTL & ~((0x3 << 8) | BIT24) ) | (shift_clk << 8);   
    }
    else if(shift_clk == SPI_SHIFT_2P5HCLK)
    {
        spi_data_write[3] = (SPI7->RX_CTL & ~((0x3 << 8) | BIT24) ) | (0x1 << 24);   
    }
    else if(shift_clk == SPI_SHIFT_3HCLK)
    {
        spi_data_write[3] = (SPI7->RX_CTL & ~((0x3 << 8) | BIT24) ) | (0x1 << 24) | (1 << 8);   
    }
    else
    {
        return 1; 
    }
    
    reg_addr = (uint32_t)(&(SPI7->BAUD));
    
    ret = HAL_NORFLASH_ModifySPIControllerParam(reg_addr, spi_data_write, 4);  
    
    return ret;   
} 



/*****************************************************************
@功能	扇区擦除
@参数	addr - 擦除起始地址
@返回	HAL_OK-成功 ,HAL_ERROR-失败
******************************************************************/
static uint8_t HAL_NORFLASH_EraseSector(uint32_t addr)
{
    uint32_t sr;
    uint8_t ret;  
    SPI_Flash_Parameter spiflashParam;
    
    spiflashParam.SPI_Instance = (uint32_t)SPI7;
    spiflashParam.Command = SPI_ERASE_SECTOR_1S1S_24;
    spiflashParam.Delay = 0xFFU;
    spiflashParam.Cont_MID = 0;  
    spiflashParam.Addr = addr;

    sr = HAL_NORFLASH_EnterCritical();    
    ret=SPI_Nor_Erase(&spiflashParam);
    HAL_NORFLASH_ExitCritical(sr);
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK; 
}

/*****************************************************************
@功能	32K块擦除
@参数	addr - 擦除起始地址
@返回	HAL_OK-成功 ,HAL_ERROR-失败
******************************************************************/
static uint8_t HAL_NORFLASH_EraseBlock32K(uint32_t addr)
{
    uint32_t sr;
    uint8_t ret;  
    SPI_Flash_Parameter spiflashParam;
    uint32_t offset;  
    
    offset = addr & 0x00FFFFFFU; 

    if (offset < 64 * 1024)
    {
        return HAL_ERROR;   
    }

    spiflashParam.SPI_Instance = (uint32_t)SPI7;
    spiflashParam.Command = SPI_ERASE_BLOCK1_1S1S_24;
    spiflashParam.Delay = 0xFFU;
    spiflashParam.Cont_MID = 0;  
    spiflashParam.Addr = addr;
    sr = HAL_NORFLASH_EnterCritical();
    ret=SPI_Nor_Erase(&spiflashParam);
    HAL_NORFLASH_ExitCritical(sr);
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK; 
}

/*****************************************************************
@功能	64K块擦除
@参数	addr - 擦除起始地址
@返回	HAL_OK-成功 ,HAL_ERROR-失败
******************************************************************/
static uint8_t HAL_NORFLASH_EraseBlock64K(uint32_t addr)
{
    uint32_t sr;
    uint8_t ret; 
    uint32_t offset;     
    SPI_Flash_Parameter spiflashParam;
    
    offset = addr & 0x00FFFFFFU; 

    if (offset < 64 * 1024)
    {
        return HAL_ERROR;   
    }    
    spiflashParam.SPI_Instance = (uint32_t)SPI7;
    spiflashParam.Command = SPI_ERASE_BLOCK2_1S1S_24;
    spiflashParam.Delay = 0xFFU;
    spiflashParam.Cont_MID = 0;  
    spiflashParam.Addr = addr;
    sr = HAL_NORFLASH_EnterCritical();    
    ret=SPI_Nor_Erase(&spiflashParam);
    HAL_NORFLASH_ExitCritical(sr);
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK; 
}

static uint8_t HAL_NORFLASH_ProgramPage(uint32_t addr, uint8_t *buff, uint32_t len)
{
    uint32_t sr;
    uint8_t ret;  
    SPI_Flash_Parameter spiflashParam;  

    spiflashParam.SPI_Instance = (uint32_t)SPI7;
    spiflashParam.Command = SPI_PROG_DATA_1S1S1S_24;
    spiflashParam.Cont_MID = 0;  
    spiflashParam.Addr = addr;
    spiflashParam.Delay = 0xFFU;
    spiflashParam.Operation_length = len;
    spiflashParam.Input_data_Addr = (uint32_t)buff;
    spiflashParam.Dummy_clks = 0; 

    sr = HAL_NORFLASH_EnterCritical();
    ret=SPI_Nor_PageProgram(&spiflashParam);
    //System_InvalidateIAccelerate();
    HAL_NORFLASH_ExitCritical(sr);
    if(ret)
    {
        return HAL_ERROR;
    }
	return HAL_OK; 
}

#endif /* HAL_NORFLASH_MODULE_ENABLED */