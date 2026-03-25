/*
  ******************************************************************************
  * @file    HAL_FMC.h
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of FMC HAL module.
  ******************************************************************************
*/
#ifndef __HAL_FMC_H__
#define __HAL_FMC_H__

#include "hal.h"


/**
  * @brief  FMC NORSRAM Timing parameters structure definition
  */
typedef struct
{
    uint32_t AddressSetupTime;             /*!< Defines the number of HCLK cycles to configure
                                                    the duration of the address setup time. */

    uint32_t AddressHoldTime;              /*!< Defines the number of HCLK cycles to configure
                                                    the duration of the address hold time. */

    uint32_t DataSetupTime;                /*!< Defines the number of HCLK cycles to configure
                                                    the duration of the data setup time. */

    uint32_t BusTurnAroundDuration;        /*!< Defines the number of HCLK cycles to configure
                                                    the duration of the bus turnaround. */

    uint32_t CLKDivision;                  /*!< Defines the period of CLK clock output signal, 
                                                    expressed in number of HCLK cycles. */

    uint32_t DataLatency;                  /*!< Defines the number of memory clock cycles to issue
                                                    to the memory before getting the first data. */

    uint32_t AccessMode;                   /*!< Specifies the asynchronous access mode. */

}FMC_NORSRAMTimingInitTypeDef;
/**
  * @}
  */


/**
  * @brief  FMC NORSRAM Configuration Structure definition
  */
typedef struct
{
    uint32_t NSBank;                         /*!< Specifies the NOR/SRAM memory bank that will be used. */

    uint32_t DataAddressMux;                 /*!< Specifies whether the address and data values are
                                                    multiplexed on the data bus or not. */

    uint32_t MemoryType;                     /*!< Specifies the type of external memory attached to
                                                    the corresponding memory bank. */

    uint32_t MemoryDataWidth;                /*!< Specifies the external memory device width. */

    uint32_t BurstAccessMode;                /*!< Enables or disables the burst access mode for Flash memory,
                                                    valid only with synchronous burst Flash memories. */                                       

    uint32_t WaitSignalPolarity;             /*!< Specifies the wait signal polarity, valid only when accessing
                                                    the Flash memory in burst mode. */

    uint32_t WrapMode;                       /*!< Enables or disables the Wrapped burst access mode for Flash
                                                    memory, valid only when accessing Flash memories in burst mode. */

    uint32_t WaitSignalActive;               /*!< Specifies if the wait signal is asserted by the memory one
                                                    clock cycle before the wait state or during the wait state,
                                                    valid only when accessing memories in burst mode. */

    uint32_t WriteOperation;                 /*!< Enables or disables the write operation in the selected bank by the FMC. */

    uint32_t WaitSignal;                     /*!< Enables or disables the wait state insertion via wait
                                                    signal, valid for Flash memory access in burst mode. */

    uint32_t ExtendedMode;                   /*!< Enables or disables the extended mode. */

    uint32_t AsynchronousWait;               /*!< Enables or disables wait signal during asynchronous transfers,
                                                    valid only with asynchronous Flash memories. */  

    uint32_t CRAMPageSize;                   /*!< Specifies the CRAM page size. */                                                    

    uint32_t WriteMode;                     /*!< Synchronous or asynchronous write mode. */ 
  
}FMC_NORSRAMInitTypeDef;
/**
  * @}
  */
  
/** 
  * @brief  FMC SDRAM Configuration Structure definition  
  */  
typedef struct
{
    uint32_t SDBank;                      /*!< Specifies the SDRAM memory device that will be used. */

    uint32_t ColumnBitsNumber;            /*!< Defines the number of bits of column address. */

    uint32_t RowBitsNumber;               /*!< Defines the number of bits of column address. */

    uint32_t MemoryDataWidth;             /*!< Defines the memory device width. */

    uint32_t InternalBankNumber;          /*!< Defines the number of the device's internal banks. */

    uint32_t CASLatency;                  /*!< Defines the SDRAM CAS latency in number of memory clock cycles. */

    uint32_t WriteProtection;             /*!< Enables the SDRAM device to be accessed in write mode. */

    uint32_t SDClockPeriod;               /*!< Define the SDRAM Clock Period for both SDRAM devices and they allow 
                                                to disable the clock before changing frequency. */

    uint32_t ReadBurst;                   /*!< This bit enable the SDRAM controller to anticipate the next read 
                                                commands during the CAS latency and stores data in the Read FIFO. */

    uint32_t ReadPipeDelay;               /*!< Define the delay in system clock cycles on read data path. */
  
}FMC_SDRAMInitTypeDef;
/**
  * @}
  */

/** 
  * @brief FMC SDRAM Timing parameters structure definition
  */
typedef struct
{
    uint32_t LoadToActiveDelay;            /*!< Defines the delay between a Load Mode Register command and 
                                              an active or Refresh command in number of memory clock cycles. */

    uint32_t ExitSelfRefreshDelay;         /*!< Defines the delay from releasing the self refresh command to 
                                              issuing the Activate command in number of memory clock cycles. */

    uint32_t SelfRefreshTime;              /*!< Defines the minimum Self Refresh period in number of memory clock 
                                              cycles. */

    uint32_t RowCycleDelay;                /*!< Defines the delay between the Refresh command and the Activate command
                                              and the delay between two consecutive Refresh commands in number of 
                                              memory clock cycles. */

    uint32_t WriteRecoveryTime;            /*!< Defines the Write recovery Time in number of memory clock cycles. */

    uint32_t RPDelay;                      /*!< Defines the delay between a Precharge Command and an other command 
                                              in number of memory clock cycles. */

    uint32_t RCDDelay;                     /*!< Defines the delay between the Activate Command and a Read/Write 
                                              command in number of memory clock cycles. */ 
}FMC_SDRAMTimingInitTypeDef;
/**
  * @}
  */
  
/** 
* @brief SDRAM command parameters structure definition
*/
typedef struct
{
  uint32_t CommandMode;                  /*!< Defines the command issued to the SDRAM device. */

  uint32_t CommandTarget;                /*!< Defines which device (1 or 2) the command will be issued to. */

  uint32_t AutoRefreshNumber;            /*!< Defines the number of consecutive auto refresh command issued
                                              in auto refresh mode. */
  uint32_t ModeRegisterDefinition;       /*!< Defines the SDRAM Mode register content */
  
}FMC_SDRAMCommandTypeDef;
/**
  * @}
  */

/** @defgroup FMC NOR/SRAM Bank
  * @{
  */
#define FMC_NORSRAM_BANK1                      (0x00000000U)
#define FMC_NORSRAM_BANK2                      (0x00000002U)
#define FMC_NORSRAM_BANK3                      (0x00000004U)
#define FMC_NORSRAM_BANK4                      (0x00000006U)
#define IS_FMC_NORSRAM_BANK(BANK)              (((BANK) == FMC_NORSRAM_BANK1) || \
                                                ((BANK) == FMC_NORSRAM_BANK2) || \
                                                ((BANK) == FMC_NORSRAM_BANK3) || \
                                                ((BANK) == FMC_NORSRAM_BANK4))
/**
  * @}
  */
  
  
/** @defgroup FMC Data Address Bus Multiplexing
  * @{
  */
#define FMC_DATA_ADDRESS_MUX_DISABLE           (0x00000000U)
#define FMC_DATA_ADDRESS_MUX_ENABLE            (0x00000002U)
#define IS_FMC_MUX(MUX)                        (((MUX) == FMC_DATA_ADDRESS_MUX_DISABLE) || \
                                                ((MUX) == FMC_DATA_ADDRESS_MUX_ENABLE))
/**
  * @}
  */

/** @defgroup FMC Memory Type
  * @{
  */
#define FMC_MEMORY_TYPE_SRAM                   (0x00000000U)
#define FMC_MEMORY_TYPE_PSRAM                  (0x00000004U)
#define FMC_MEMORY_TYPE_NOR                    (0x00000008U)
#define IS_FMC_MEMORY(MEMORY)                  (((MEMORY) == FMC_MEMORY_TYPE_SRAM) || \
                                                ((MEMORY) == FMC_MEMORY_TYPE_PSRAM)|| \
                                                ((MEMORY) == FMC_MEMORY_TYPE_NOR))
/**
  * @}
  */
  
/** @defgroup FMC NORSRAM Data Width
  * @{
  */
#define FMC_NORSRAM_MEM_BUS_WIDTH_8            (0x00000000U)
#define FMC_NORSRAM_MEM_BUS_WIDTH_16           (0x00000010U)
#define FMC_NORSRAM_MEM_BUS_WIDTH_32           (0x00000020U)
#define IS_FMC_MEMORY_WIDTH(WIDTH)             (((WIDTH) == FMC_NORSRAM_MEM_BUS_WIDTH_8) || \
                                                ((WIDTH) == FMC_NORSRAM_MEM_BUS_WIDTH_16) || \
                                                ((WIDTH) == FMC_NORSRAM_MEM_BUS_WIDTH_32))
/**
  * @}
  */

/** @defgroup FMC NOR/SRAM Flash Access
  * @{
  */
#define FMC_NORSRAM_FLASH_ACCESS_DISABLE       (0x00000000U)
#define FMC_NORSRAM_FLASH_ACCESS_ENABLE        (0x00000040U)
/**
  * @}
  */


/** @defgroup FMC Burst Access Mode
  * @{
  */
#define FMC_BURST_ACCESS_MODE_DISABLE          (0x00000000U)
#define FMC_BURST_ACCESS_MODE_ENABLE           (0x00000100U)
#define IS_FMC_BURSTMODE(STATE)                (((STATE) == FMC_BURST_ACCESS_MODE_DISABLE) || \
                                                ((STATE) == FMC_BURST_ACCESS_MODE_ENABLE))
/**
  * @}
  */
  
/** @defgroup FMC Wait Signal Polarity
  * @{
  */
#define FMC_WAIT_SIGNAL_POLARITY_LOW           (0x00000000U)
#define FMC_WAIT_SIGNAL_POLARITY_HIGH          (0x00000200U)
#define IS_FMC_WAIT_POLARITY(POLARITY)         (((POLARITY) == FMC_WAIT_SIGNAL_POLARITY_LOW) || \
                                                ((POLARITY) == FMC_WAIT_SIGNAL_POLARITY_HIGH))
/**
  * @}
  */

/** @defgroup FMC Wrap Mode 
  * @{
  */
#define FMC_WRAP_MODE_DISABLE                  (0x00000000U)
#define FMC_WRAP_MODE_ENABLE                   (0x00000400U)
#define IS_FMC_WRAP_MODE(MODE)                 (((MODE) == FMC_WRAP_MODE_DISABLE) || \
                                                ((MODE) == FMC_WRAP_MODE_ENABLE))
/**
  * @}
  */

/** @defgroup FMC Wait Timing
  * @{
  */
#define FMC_WAITSIGNALACTIVE_BEFOREWAITSTATE   (0x00000000U)
#define FMC_WAITSIGNALACTIVE_DURINGWAITSTATE   (0x00000800U)
#define IS_FMC_WAIT_SIGNAL_ACTIVE(ACTIVE)      (((ACTIVE) == FMC_WAITSIGNALACTIVE_BEFOREWAITSTATE) || \
                                                ((ACTIVE) == FMC_WAITSIGNALACTIVE_DURINGWAITSTATE))
/**
  * @}
  */

/** @defgroup FMC Write Operation
  * @{
  */
#define FMC_WRITEOPERATION_DISABLE             (0x00000000U)
#define FMC_WRITEOPERATION_ENABLE              (0x00001000U)
#define IS_FMC_WRITE_OPERATION(OPERATION)      (((OPERATION) == FMC_WRITEOPERATION_DISABLE) || \
                                                ((OPERATION) == FMC_WRITEOPERATION_ENABLE)) 
/**
  * @}
  */

/** @defgroup FMC Wait Signal
  * @{
  */
#define FMC_WAIT_SIGNAL_DISABLE                (0x00000000U)
#define FMC_WAIT_SIGNAL_ENABLE                 (0x00002000U)
#define IS_FMC_WAITE_SIGNAL(SIGNAL)            (((SIGNAL) == FMC_WAIT_SIGNAL_DISABLE) || \
                                                ((SIGNAL) == FMC_WAIT_SIGNAL_ENABLE))
/**
  * @}
  */

/** @defgroup FMC Extended Mode
  * @{
  */
#define FMC_EXTENDED_MODE_DISABLE              (0x00000000U)
#define FMC_EXTENDED_MODE_ENABLE               (0x00004000U)
#define IS_FMC_EXTENDED_MODE(MODE)             (((MODE) == FMC_EXTENDED_MODE_DISABLE) || \
                                                ((MODE) == FMC_EXTENDED_MODE_ENABLE)) 
/**
  * @}
  */

/** @defgroup FMC Asynchronous Wait
  * @{
  */
#define FMC_ASYNCHRONOUS_WAIT_DISABLE          (0x00000000U)
#define FMC_ASYNCHRONOUS_WAIT_ENABLE           (0x00008000U)
#define IS_FMC_ASYNWAIT(STATE)                 (((STATE) == FMC_ASYNCHRONOUS_WAIT_DISABLE) || \
                                                ((STATE) == FMC_ASYNCHRONOUS_WAIT_ENABLE))
/**
  * @}
  */

/** @defgroup FMC CRAM Page Size
  * @{
  */
#define FMC_CRAMPAGE_SIZE_AUTO                 (0x00000000U)
#define FMC_CRAMPPAGE_SIZE_128                 (0x00010000U)
#define FMC_CRAMPPAGE_SIZE_256                 (0x00020000U)
#define FMC_CRAMPPAGE_SIZE_512                 (0x00030000U)
#define FMC_CRAMPPAGE_SIZE_1024                (0x00040000U)
#define IS_FMC_CRAMPPAGE_SIZE(SIZE)            (((SIZE) == FMC_CRAMPAGE_SIZE_AUTO) || \
                                                ((SIZE) == FMC_CRAMPPAGE_SIZE_128) || \
                                                ((SIZE) == FMC_CRAMPPAGE_SIZE_256) || \
                                                ((SIZE) == FMC_CRAMPPAGE_SIZE_512) || \
                                                ((SIZE) == FMC_CRAMPPAGE_SIZE_1024))
/**
  * @}
  */

/** @defgroup FMC Write Mode
  * @{
  */
#define FMC_WRITE_ASY_MODE                     (0x00000000U)
#define FMC_WRITE_SY_MODE                      (0x00080000U)
#define IS_FMC_WRITE_MODE(MODE)                (((MODE) == FMC_WRITE_ASY_MODE) || \
                                                ((MODE) == FMC_WRITE_SY_MODE))
/**
  * @}
  */

/** @defgroup FMC Address Setup Time 
  * @{
  */
#define IS_FMC_ADDRESS_SETUP_TIME(TIME)        ((TIME) <= 0xF)
/**
  * @}
  */

/** @defgroup FMC Address Hold Time 
  * @{
  */
#define IS_FMC_ADDRESS_HOLD_TIME(TIME)         ((TIME) <= 0xF)
/**
  * @}
  */

/** @defgroup FMC Data Setup Time 
  * @{
  */
#define IS_FMC_DATASETUP_TIME(TIME)            ((TIME) <= 0xFF)
/**
  * @}
  */

/** @defgroup FMC Bus Turn around Duration 
  * @{
  */
#define IS_FMC_TURNAROUND_TIME(TIME)           ((TIME) <= 0xF)
/**
  * @}
  */

/** @defgroup FMC CLK Division 
  * @{
  */
#define IS_FMC_CLK_DIV(DIV)                    ((DIV) <= 0xF)
/**
  * @}
  */

/** @defgroup FMC Data Latency 
  * @{
  */
#define IS_FMC_DATA_LATENCY(LATENCY)           ((LATENCY) <= 0xF)
/**
  * @}
  */

/** @defgroup FMC_Access_Mode FMC Access Mode
* @{
*/
#define FMC_ACCESS_MODE_A                      (0x00000000U)
#define FMC_ACCESS_MODE_B                      (0x10000000U)
#define FMC_ACCESS_MODE_C                      (0x20000000U)
#define FMC_ACCESS_MODE_D                      (0x30000000U)
#define IS_FMC_ACCESS_MODE(MODE)               (((MODE) == FMC_ACCESS_MODE_A) || \
                                                ((MODE) == FMC_ACCESS_MODE_B) || \
                                                ((MODE) == FMC_ACCESS_MODE_C) || \
                                                ((MODE) == FMC_ACCESS_MODE_D))
/**
* @}
*/



/** @defgroup FMC SDRAM Bank
  * @{
  */
#define FMC_SDRAM_BANK1                        ((uint32_t)0x00000000U)
#define FMC_SDRAM_BANK2                        ((uint32_t)0x00000001U)
#define IS_FMC_SDRAM_BANK(BANK)                (((BANK) == FMC_SDRAM_BANK1) || \
                                                ((BANK) == FMC_SDRAM_BANK2))
/**
  * @}
  */
  
  /** @defgroup FMC SDRAM Column Bits number 
  * @{
  */
#define FMC_SDRAM_COLUMN_BITS_NUM_8            ((uint32_t)0x00000000U)
#define FMC_SDRAM_COLUMN_BITS_NUM_9            ((uint32_t)0x00000001U)
#define FMC_SDRAM_COLUMN_BITS_NUM_10           ((uint32_t)0x00000002U)
#define FMC_SDRAM_COLUMN_BITS_NUM_11           ((uint32_t)0x00000003U)
#define IS_FMC_COLUMNBITS_NUMBER(COLUMN)       (((COLUMN) == FMC_SDRAM_COLUMN_BITS_NUM_8)  || \
                                                ((COLUMN) == FMC_SDRAM_COLUMN_BITS_NUM_9)  || \
                                                ((COLUMN) == FMC_SDRAM_COLUMN_BITS_NUM_10) || \
                                                ((COLUMN) == FMC_SDRAM_COLUMN_BITS_NUM_11))
/**
  * @}
  */

/** @defgroup FMC SDRAM Row Bits number
  * @{
  */
#define FMC_SDRAM_ROW_BITS_NUM_11              ((uint32_t)0x00000000U)
#define FMC_SDRAM_ROW_BITS_NUM_12              ((uint32_t)0x00000004U)
#define FMC_SDRAM_ROW_BITS_NUM_13              ((uint32_t)0x00000008U)
#define IS_FMC_ROWBITS_NUMBER(ROW)             (((ROW) == FMC_SDRAM_ROW_BITS_NUM_11) || \
                                                ((ROW) == FMC_SDRAM_ROW_BITS_NUM_12) || \
                                                ((ROW) == FMC_SDRAM_ROW_BITS_NUM_13))
/**
  * @}
  */

/** @defgroup FMC SDRAM Memory Bus Width
  * @{
  */
#define FMC_SDRAM_MEM_BUS_WIDTH_8              ((uint32_t)0x00000000U)
#define FMC_SDRAM_MEM_BUS_WIDTH_16             ((uint32_t)0x00000010U)
#define FMC_SDRAM_MEM_BUS_WIDTH_32             ((uint32_t)0x00000020U)
#define IS_FMC_SDMEMORY_WIDTH(WIDTH)           (((WIDTH) == FMC_SDRAM_MEM_BUS_WIDTH_8)  || \
                                                ((WIDTH) == FMC_SDRAM_MEM_BUS_WIDTH_16) || \
                                                ((WIDTH) == FMC_SDRAM_MEM_BUS_WIDTH_32))
/**
  * @}
  */

/** @defgroup FMC SDRAM Internal Banks Number
  * @{
  */
#define FMC_SDRAM_INTERN_BANKS_NUM_2           ((uint32_t)0x00000000U)
#define FMC_SDRAM_INTERN_BANKS_NUM_4           ((uint32_t)0x00000040U)
#define IS_FMC_INTERNALBANK_NUMBER(NUMBER)     (((NUMBER) == FMC_SDRAM_INTERN_BANKS_NUM_2) || \
                                                ((NUMBER) == FMC_SDRAM_INTERN_BANKS_NUM_4))
/**
  * @}
  */

/** @defgroup FMC SDRAM CAS Latency
  * @{
  */
#define FMC_SDRAM_CAS_LATENCY_1                ((uint32_t)0x00000080U)
#define FMC_SDRAM_CAS_LATENCY_2                ((uint32_t)0x00000100U)
#define FMC_SDRAM_CAS_LATENCY_3                ((uint32_t)0x00000180U)
#define IS_FMC_CAS_LATENCY(LATENCY)            (((LATENCY) == FMC_SDRAM_CAS_LATENCY_1) || \
                                                ((LATENCY) == FMC_SDRAM_CAS_LATENCY_2) || \
                                                ((LATENCY) == FMC_SDRAM_CAS_LATENCY_3))
/**
  * @}
  */

/** @defgroup FMC SDRAM Write Protection
  * @{
  */
#define FMC_SDRAM_WRITE_PROTECTION_DISABLE     ((uint32_t)0x00000000U)
#define FMC_SDRAM_WRITE_PROTECTION_ENABLE      ((uint32_t)0x00000200U)
#define IS_FMC_WRITE_PROTECTION(__WRITE__)     (((__WRITE__) == FMC_SDRAM_WRITE_PROTECTION_DISABLE) || \
                                                ((__WRITE__) == FMC_SDRAM_WRITE_PROTECTION_ENABLE))	
/**
  * @}
  */

/** @defgroup FMC SDRAM Clock Period
  * @{
  */
#define FMC_SDRAM_CLOCK_DISABLE                ((uint32_t)0x00000000U)
#define FMC_SDRAM_CLOCK_PERIOD_2               ((uint32_t)0x00000800U)
#define FMC_SDRAM_CLOCK_PERIOD_3               ((uint32_t)0x00000C00U)
#define FMC_SDRAM_CLOCK_PERIOD_4               ((uint32_t)0x00000400U)
#define IS_FMC_SDCLOCK_PERIOD(__PERIOD__)      (((__PERIOD__) == FMC_SDRAM_CLOCK_DISABLE)  || \
                                                ((__PERIOD__) == FMC_SDRAM_CLOCK_PERIOD_2) || \
                                                ((__PERIOD__) == FMC_SDRAM_CLOCK_PERIOD_3) || \
                                                ((__PERIOD__) == FMC_SDRAM_CLOCK_PERIOD_4))
/**
  * @}
  */

/** @defgroup FMC SDRAM Read Burst
  * @{
  */
#define FMC_SDRAM_RBURST_DISABLE               ((uint32_t)0x00000000U)
#define FMC_SDRAM_RBURST_ENABLE                ((uint32_t)0x00001000U)
#define IS_FMC_READ_BURST(__RBURST__)          (((__RBURST__) == FMC_SDRAM_RBURST_DISABLE) || \
                                                ((__RBURST__) == FMC_SDRAM_RBURST_ENABLE))
/**
  * @}
  */
  
/** @defgroup FMC SDRAM Read Pipe Delay
  * @{
  */
#define FMC_SDRAM_RPIPE_DELAY_0                ((uint32_t)0x00000000U)
#define FMC_SDRAM_RPIPE_DELAY_1                ((uint32_t)0x00002000U)
#define FMC_SDRAM_RPIPE_DELAY_2                ((uint32_t)0x00004000U)
#define IS_FMC_READPIPE_DELAY(__DELAY__)       (((__DELAY__) == FMC_SDRAM_RPIPE_DELAY_0) || \
                                                ((__DELAY__) == FMC_SDRAM_RPIPE_DELAY_1) || \
                                                ((__DELAY__) == FMC_SDRAM_RPIPE_DELAY_2))
/**
  * @}
  */
  
/** @defgroup FMC SDRAM write to read delay
  * @{
  */
#define FMC_SDRAM_W2R_DELAY_0                   ((uint32_t)0x00000000U) 
#define FMC_SDRAM_W2R_DELAY_HALF_SDCLK          ((uint32_t)0x00008000U)       
#define IS_FMC_W2R_DELAY(__DELAY__)             (((__DELAY__) == FMC_SDRAM_W2R_DELAY_0) || \
                                                ((__DELAY__) == FMC_SDRAM_W2R_DELAY_HALF_SDCLK))        
/**
  * @}
  */ 

/** @defgroup FMC SDRAM burst read fifo length
  * @{
  */
#define FMC_SDRAM_BURST_READ_FIFO_LEN_0         ((uint32_t)0x00000000U)
#define FMC_SDRAM_BURST_READ_FIFO_LEN_1         ((uint32_t)0x00010000U) 
#define FMC_SDRAM_BURST_READ_FIFO_LEN_2         ((uint32_t)0x00020000U) 
#define FMC_SDRAM_BURST_READ_FIFO_LEN_3         ((uint32_t)0x00030000U) 
#define FMC_SDRAM_BURST_READ_FIFO_LEN_4         ((uint32_t)0x00040000U) 
#define FMC_SDRAM_BURST_READ_FIFO_LEN_5         ((uint32_t)0x00050000U) 
#define FMC_SDRAM_BURST_READ_FIFO_LEN_6         ((uint32_t)0x00060000U) 
#define FMC_SDRAM_BURST_READ_FIFO_LEN_7         ((uint32_t)0x00070000U) 
#define IS_FMC_BURST_READ_FIFO_LEN(__LEN__)     (((__LEN__) == FMC_SDRAM_BURST_READ_FIFO_LEN_0) || \
                                                ((__LEN__) == FMC_SDRAM_BURST_READ_FIFO_LEN_1) || \
                                                ((__LEN__) == FMC_SDRAM_BURST_READ_FIFO_LEN_2) || \
                                                ((__LEN__) == FMC_SDRAM_BURST_READ_FIFO_LEN_3) || \
                                                ((__LEN__) == FMC_SDRAM_BURST_READ_FIFO_LEN_4) || \
                                                ((__LEN__) == FMC_SDRAM_BURST_READ_FIFO_LEN_5) || \
                                                ((__LEN__) == FMC_SDRAM_BURST_READ_FIFO_LEN_6) || \
                                                ((__LEN__) == FMC_SDRAM_BURST_READ_FIFO_LEN_7))       
/**
  * @}
  */  
  

/** @defgroup FMC SDRAM Command Mode
  * @{
  */
#define FMC_SDRAM_CMD_NORMAL_MODE              ((uint32_t)0x00000000U)
#define FMC_SDRAM_CMD_CLK_ENABLE               ((uint32_t)0x00000001U)
#define FMC_SDRAM_CMD_PALL                     ((uint32_t)0x00000002U)
#define FMC_SDRAM_CMD_AUTOREFRESH_MODE         ((uint32_t)0x00000003U)
#define FMC_SDRAM_CMD_LOAD_MODE                ((uint32_t)0x00000004U)
#define FMC_SDRAM_CMD_SELFREFRESH_MODE         ((uint32_t)0x00000005U)
#define FMC_SDRAM_CMD_POWERDOWN_MODE           ((uint32_t)0x00000006U)
#define IS_FMC_COMMAND_MODE(__COMMAND__)       (((__COMMAND__) == FMC_SDRAM_CMD_NORMAL_MODE)      || \
                                                ((__COMMAND__) == FMC_SDRAM_CMD_CLK_ENABLE)       || \
                                                ((__COMMAND__) == FMC_SDRAM_CMD_PALL)             || \
                                                ((__COMMAND__) == FMC_SDRAM_CMD_AUTOREFRESH_MODE) || \
                                                ((__COMMAND__) == FMC_SDRAM_CMD_LOAD_MODE)        || \
                                                ((__COMMAND__) == FMC_SDRAM_CMD_SELFREFRESH_MODE) || \
                                                ((__COMMAND__) == FMC_SDRAM_CMD_POWERDOWN_MODE))
/**
  * @}
  */
  
/**
  * @brief FMC SDRAM Load Mode Register
  */
#define FMC_SDRAM_LOAD_MODE_BURST_LENGTH_1             ((uint16_t)0x0000)
#define FMC_SDRAM_LOAD_MODE_BURST_LENGTH_2             ((uint16_t)0x0001)
#define FMC_SDRAM_LOAD_MODE_BURST_LENGTH_4             ((uint16_t)0x0002)
#define FMC_SDRAM_LOAD_MODE_BURST_LENGTH_8             ((uint16_t)0x0004)
#define FMC_SDRAM_LOAD_MODE_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define FMC_SDRAM_LOAD_MODE_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define FMC_SDRAM_LOAD_MODE_CAS_LATENCY_2              ((uint16_t)0x0020)
#define FMC_SDRAM_LOAD_MODE_CAS_LATENCY_3              ((uint16_t)0x0030)
#define FMC_SDRAM_LOAD_MODE_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define FMC_SDRAM_LOAD_MODE_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
#define FMC_SDRAM_LOAD_MODE_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)  
/**
  * @}
  */

/** @defgroup FMC SDRAM Command Target
  * @{
  */
#define FMC_SDRAM_CMD_TARGET_BANK2             FMC_SDRCMD_CTD2
#define FMC_SDRAM_CMD_TARGET_BANK1             FMC_SDRCMD_CTD1
#define FMC_SDRAM_CMD_TARGET_BANK1_2           ((uint32_t)0x00000018U)
#define IS_FMC_COMMAND_TARGET(__TARGET__)      (((__TARGET__) == FMC_SDRAM_CMD_TARGET_BANK1) || \
                                                ((__TARGET__) == FMC_SDRAM_CMD_TARGET_BANK2) || \
                                                ((__TARGET__) == FMC_SDRAM_CMD_TARGET_BANK1_2)) 
/**
  * @}
  */

/** @defgroup FMC SDRAM Mode Status 
  * @{
  */
#define FMC_SDRAM_NORMAL_MODE                  ((uint32_t)0x00000000U)
#define FMC_SDRAM_SELF_REFRESH_MODE            ((uint32_t)0x00000001U)
#define FMC_SDRAM_POWER_DOWN_MODE              ((uint32_t)0x00000002U)


/** @defgroup FMC SDRAM LoadToActive Delay
  * @{
  */
#define IS_FMC_LOADTOACTIVE_DELAY(__DELAY__)   (((__DELAY__) > 0) && ((__DELAY__) <= 16))
/**
  * @}
  */
  
/** @defgroup FMC SDRAM ExitSelfRefresh Delay
  * @{
  */
#define IS_FMC_EXITSELFREFRESH_DELAY(__DELAY__) (((__DELAY__) > 0) && ((__DELAY__) <= 16))
/**
  * @}
  */ 
     
/** @defgroup FMC SDRAM SelfRefresh Time
  * @{
  */  
#define IS_FMC_SELFREFRESH_TIME(__TIME__)      (((__TIME__) > 0) && ((__TIME__) <= 16))
/**
  * @}
  */
  
/** @defgroup FMC SDRAM RowCycle Delay
  * @{
  */  
#define IS_FMC_ROWCYCLE_DELAY(__DELAY__)       (((__DELAY__) > 0) && ((__DELAY__) <= 16))
/**
  * @}
  */  
  
/** @defgroup FMC SDRAM Write Recovery Time
  * @{
  */  
#define IS_FMC_WRITE_RECOVERY_TIME(__TIME__)   (((__TIME__) > 0) && ((__TIME__) <= 16))
/**
  * @}
  */         
  
/** @defgroup FMC SDRAM RP Delay
  * @{
  */  
#define IS_FMC_RP_DELAY(__DELAY__)             (((__DELAY__) > 0) && ((__DELAY__) <= 16))
/**
  * @}
  */ 
  
/** @defgroup FMC SDRAM RCD Delay
  * @{
  */  
#define IS_FMC_RCD_DELAY(__DELAY__)            (((__DELAY__) > 0) && ((__DELAY__) <= 16))
/**
  * @}
  */
  
/** @defgroup FMC SDRAM AutoRefresh Number
  * @{
  */  
#define IS_FMC_AUTOREFRESH_NUMBER(__NUMBER__)  (((__NUMBER__) > 0) && ((__NUMBER__) <= 16))
/**
  * @}
  */

/** @defgroup FMC SDRAM ModeRegister Definition
  * @{
  */
#define IS_FMC_MODE_REGISTER(__CONTENT__)      ((__CONTENT__) <= 8191)
/**
  * @}
  */

/** @defgroup FMC SDRAM Refresh rate
  * @{
  */
#define IS_FMC_REFRESH_RATE(__RATE__)          ((__RATE__) <= 8191)
/**
  * @}
  */




HAL_StatusTypeDef HAL_FMC_NORSRAM_Init(FMC_NORSRAMInitTypeDef *hFMC);

HAL_StatusTypeDef HAL_FMC_NORSRAM_DeInit(FMC_NORSRAMInitTypeDef *hFMC);

HAL_StatusTypeDef HAL_FMC_NORSRAM_Timing_Init(FMC_NORSRAMTimingInitTypeDef *Timing, uint32_t Bank);

HAL_StatusTypeDef HAL_FMC_NORSRAM_Extended_Timing_Init(FMC_NORSRAMTimingInitTypeDef *Timing, uint32_t Bank, uint32_t ExtendedMode);

HAL_StatusTypeDef HAL_FMC_SDRAM_Init(FMC_SDRAMInitTypeDef *Init);

HAL_StatusTypeDef HAL_FMC_SDRAM_Timing_Init(FMC_SDRAMTimingInitTypeDef *Timing, uint32_t Bank);

HAL_StatusTypeDef HAL_FMC_SDRAM_DeInit(uint32_t Bank);

HAL_StatusTypeDef HAL_FMC_SDRAM_SendCommand(FMC_SDRAMCommandTypeDef *Command, uint32_t Timeout);

HAL_StatusTypeDef HAL_FMC_SDRAM_ProgramRefreshRate(uint32_t RefreshRate);

HAL_StatusTypeDef HAL_FMC_SDRAM_SetAutoRefreshNumber(uint32_t AutoRefreshNumber);

uint32_t HAL_FMC_SDRAM_GetBankModeStatus(uint32_t Bank);

uint32_t HAL_FMC_SDRAM_GetStatus(void);

void HAL_FMC_SDRAM_ITConfig(FunctionalState NewState);

FlagStatus HAL_FMC_SDRAM_GetITStatus(void);

void HAL_FMC_SDRAM_ClearITPendingBit(void);

void HAL_FMC_SDRAM_BurstReadFifoLength(uint32_t FifoLen, uint32_t Bank);

void HAL_FMC_SDRAM_W2RDelay(uint32_t W2RDelay, uint32_t Bank);

#endif
