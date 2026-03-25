/******************************************
*   Double-Data-Rate Octal SPI PSRAM
*   APS6408L-OBM-BA
******************************************/

#ifndef __PSRAM_H__
#define __PSRAM_H__

#include  "hal.h" 

/* OSPI1_RETN-PC12-GPIO */ 
#define XCCELA_RSTN_GPIO                        GPIOC
#define XCCELA_RSTN_PIN                         GPIO_PIN_12
#define XCCELA_RSTN_CLK_ENABLE()                __HAL_RCC_GPIOC_CLK_ENABLE()
#define OSPI_MEMORY_ADDR                        OSPI1_MEM_BASE_ADDR

/* XCCELA OPI PSRAM Command */
#define XCCELAOPI_SYNC_READ                     (0x00)
#define XCCELAOPI_SYNC_WRITE                    (0x80)
#define XCCELAOPI_SYNC_READ_LINEAR_BURST        (0x20)
#define XCCELAOPI_SYNC_WRITE_LINEAR_BURST       (0xA0)
#define XCCELAOPI_MODE_REGISTER_READ            (0x40)
#define XCCELAOPI_MODE_REGISTER_WRITE           (0xC0)
#define XCCELAOPI_GLOBAL_RESET                  (0xFF)

/* Control Registers Address */
#define XCCELAOPI_MA_ADDR_0                     (0x00)
#define XCCELAOPI_MA_ADDR_1                     (0x01)
#define XCCELAOPI_MA_ADDR_2                     (0x02)
#define XCCELAOPI_MA_ADDR_3                     (0x03)
#define XCCELAOPI_MA_ADDR_4                     (0x04)
#define XCCELAOPI_MA_ADDR_8                     (0x08)

#define  APS6408L_OBM_ID                        (0x0D10)

void PSRAM_Init(void);

#endif


