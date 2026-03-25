/*****************************************************************
Copyright(C) 2008 - 2021, Shanghai AisinoChip Co.,Ltd.
@文件名称:	hal_norflash.h
@功能描述:	norFlash header file
@开发人员:	bobzhang 
@完成日期:	2021.1.18
@当前版本:	1.0
@修改记录:	
修改日期		修改人   		修改说明

******************************************************************/

/*****************************************************************
注意：如果使用HAL_NORFLASH_ModifyData函数，要求堆栈设置在6KB以上。
因为HAL_NORFLASH_ModifyData函数内部使用4KB堆栈空间，缓存扇区备份数据。
******************************************************************/

#ifndef _HAL_NORFLASH_H
#define _HAL_NORFLASH_H

#include "acm32h5xx_hal_conf.h"



typedef enum
{
    SPI_CMD_ID_NOT_CARE = 0x00,  
    
    SPI_READ_REGISTER_1S0S1S = 0x01, 
    
    SPI_WRITE_REGISTER1_1S1S1S, 
    
    SPI_WRITE_REGISTER2_1S1S1S, 
   
    SPI_WRITE_REGISTER3_1S1S1S, 
   
    SPI_READ_ID_1S0S1S,  
    
    SPI_READ_DATA_1S1S1S_24, // 0x03, STR, xSPI 
    SPI_READ_DATA_1S1S1S_32, // 0x13, STR, xSPI 
    
    SPI_READ_DATA_1S1S4S_24, // 0x6B, STR, xSPI 
    SPI_READ_DATA_1S4S4S_24, // 0xEB, STR, xSPI 

    SPI_ERASE_SECTOR_1S1S_24, // 0x20, STR, xSPI  
    SPI_ERASE_SECTOR_1S1S_32, // 0x21, STR, xSPI

    
    SPI_ERASE_BLOCK1_1S1S_24, // 0x52, STR, xSPI 
    SPI_ERASE_BLOCK1_1S1S_32, // 0x5C, STR, xSPI 
    
    SPI_ERASE_BLOCK2_1S1S_24, // 0xD8, STR, xSPI  
    SPI_ERASE_BLOCK2_1S1S_32, // 0xDC, STR, xSPI  
 
    
    SPI_PROG_DATA_1S1S1S_24,  // 0x02, STR, xSPI 
    SPI_PROG_DATA_1S1S1S_32,  // 0x12, STR, xSPI 
    SPI_PROG_DATA_1S1S4S_24,  // 0x32, STR, xSPI   
    
    SPI_ENTER_ADDR_32_1S,     // 0xB7, STR, xSPI
    
    SPI_EXIT_ADDR_32_1S,      // 0xE9, STR, xSPI   
    
    SPI_READ_UNIQUE_ID = 0x4B, 
    
}SPI_READ_CMD; 

typedef struct
{
    uint32_t SPI_Instance;     
    
    uint8_t  Command; //must 
    uint8_t  Delay;   //must  
    uint8_t  Cont_MID;  //must   
    uint8_t  Dummy_clks; //must     
    
    uint32_t Addr;   //must
    uint32_t Operation_length; //must 
    uint32_t Input_data_Addr; //must
    uint32_t Output_data_Addr;  //must  
            
}SPI_Flash_Parameter;

typedef uint8_t (*SPI_Nor_Func)(SPI_Flash_Parameter *); 

#define  SPI_NORFLASH_FUNC_ADDR     0x1FF07FD0
#define  SPI_Nor_Read_MID_DID       (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[0])
#define  SPI_Nor_Read_Unique_ID     (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[1])
#define  SPI_Nor_WriteRegister      (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[2])
#define  SPI_Nor_ReadRegister       (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[3])
#define  SPI_Nor_Read               (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[4])
#define  SPI_Nor_PageProgram        (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[5])
#define  SPI_Nor_Erase              (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[6])
#define  SPI_SwitchToFIFOMode       (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[8])
#define  SPI_SwitchToXIPMode        (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[9])
#define  SPI_Nor_ModifyValue        (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[10])
#define  SPI_SetEncrytionKey        (((SPI_Nor_Func *)SPI_NORFLASH_FUNC_ADDR)[11])

#define  SPI_Nor_Encrypt_Data       ((SPI_Nor_Func )0x1FF07C01)

#define READ_DATA                                (0x03) //1-1-1
#define READ_DATA_FAST                           (0x0B) //1-1-1
#define DUAL_OUTPUT_FAST_READ                    (0x3B) //1-1-2
#define QUAD_OUTPUT_FAST_READ                    (0x6B) //1-1-4
#define DUAL_IO_FAST_READ                        (0xBB) //1-2-2
#define QUAD_IO_FAST_READ                        (0xEB) //1-4-4

#define SET_BURST_WITH_WRAP                      (0x77)

#define PAGE_PROGARM                             (0x02)  //1-1-1   
#define DUAL_PAGE_PROGARM                        (0xA2)  //1-1-2
#define EXT_DUAL_PAGE_PROGARM                    (0xD2)  //1-2-2
#define QUAD_PAGE_PROGRAM                        (0x32)  //1-1-4
#define EXT_QUAD_PAGE_PROGRAM                    (0x38)  //1-4-4  


#define SECTOR_ERASE                             (0x20)
#define BLOCK_ERASE_32K                          (0x52)
#define BLOCK_ERASE_64K                          (0xd8)
#define CHIP_ERASE                               (0xC7)

#define READ_DEVICE_ID                           (0x90)
#define READ_ID                                  (0x9F)
#define READ_UNIQUE_ID                           (0x4B)


#define  SPI_SHIFT_ZERO          0
#define  SPI_SHIFT_1HCLK         1
#define  SPI_SHIFT_1P5HCLK       2
#define  SPI_SHIFT_2HCLK         3 
#define  SPI_SHIFT_2P5HCLK       4 
#define  SPI_SHIFT_3HCLK         5    

typedef struct
{
    uint32_t chipSize;
    uint8_t readCmd;
    uint8_t readDummyBytes;
    uint8_t programCmd;
}NORFLASH_ParamTypeDef;


#define NORFLASH_PAGE_SIZE            (256)
#define NORFLASH_PAGE_SIZE_MASK       (NORFLASH_PAGE_SIZE-1)

#define NORFLASH_SECTOR_SIZE          (4096)
#define NORFLASH_SECTOR_SIZE_MASK     (NORFLASH_SECTOR_SIZE-1)

#define NORFLASH_BLOCK_32K_SIZE       (32*1024)
#define NORFLASH_BLOCK_32K_SIZE_MASK  (NORFLASH_BLOCK_32K_SIZE-1)

#define NORFLASH_BLOCK_64K_SIZE       (64*1024)
#define NORFLASH_BLOCK_64K_SIZE_MASK  (NORFLASH_BLOCK_64K_SIZE-1)


void HAL_NORFLASH_CfgSpiShift1_Insram(void);
void HAL_NORFLASH_CfgSpiDiv4Shift0_Insram(void);
void HAL_NORFLASH_XipPlainReadBytes_Insram(uint32_t addr, void *buff, uint32_t bytelen);
void HAL_NORFLASH_XipPlainReadWords_Insram(uint32_t addr, void *buff, uint32_t wordlen);


uint32_t HAL_NORFLASH_EnterCritical(void);
void HAL_NORFLASH_ExitCritical(uint32_t sr);


//uint8_t HAL_NORFLASH_Init(void);

uint8_t HAL_NORFLASH_ReadUniqueID(uint8_t *buff,uint32_t len);

//返回两字节的Manufacture ID 和 Device ID
uint8_t HAL_NORFLASH_ReadID(uint8_t *buff);

//擦除数据，支持跨扇区
uint8_t HAL_NORFLASH_Erase(uint32_t addr, uint32_t len);

//字节读，支持跨页
uint8_t HAL_NORFLASH_Read(uint32_t addr, uint8_t *buff, uint32_t len);

//编程数据，支持跨页
uint8_t HAL_NORFLASH_Program(uint32_t addr, uint8_t *buff, uint32_t len);

//写字节数据。扇区对齐时，自动擦除再写。未扇区对齐时，会自动备份擦除再写。本函数内部使用4KB堆栈空间，缓存扇区备份数据。
uint8_t HAL_NORFLASH_ModifyData(uint32_t addr, uint8_t *buff, uint32_t len);

uint8_t HAL_NORFLASH_EraseBootFlag(void);

uint8_t HAL_NORFLASH_SetEncryptionKey(uint8_t * key_input);
uint8_t HAL_NORFLASH_EncryptProgram(uint32_t addr, uint32_t *data_in, uint32_t len, uint32_t *data_out);

uint8_t HAL_NORFLASH_ModifySPIControllerParam(uint32_t write_addr, uint32_t * p_value, uint32_t len); 

uint8_t HAL_NORFLASH_SetLowPowerMode(uint8_t mode);
void HAL_NORFLASH_ResetMcu(void);  

uint8_t HAL_NORFLASH_ModifyDivShift(uint32_t div, uint32_t shift_clk);    

#endif


