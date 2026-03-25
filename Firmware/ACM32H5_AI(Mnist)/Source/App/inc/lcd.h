#ifndef __LCD_H__
#define __LCD_H__

#include "hal.h"

#ifdef LCD_ROW_COL_EXCHANGE

#define LCD_WIDTH								480
#define LCD_HEIGHT								800
#else
#define LCD_WIDTH								800
#define LCD_HEIGHT								480
#endif

#define LCD_BITS_PER_PIXLE						16
#define LCD_MAX_LAYER_BUF_SIZE					(LCD_WIDTH*LCD_HEIGHT*LCD_BITS_PER_PIXLE/8)


/* LCD pixle format */
#define ARGB8888 								LTDC_PIXEL_FORMAT_ARGB8888  /*!< ARGB8888 LTDC像素格式 */
#define RGB888 									LTDC_PIXEL_FORMAT_RGB888    /*!< RGB888 LTDC像素格式   */
#define RGB565 									LTDC_PIXEL_FORMAT_RGB565    /*!< RGB565 LTDC像素格式   */
#define ARGB1555 								LTDC_PIXEL_FORMAT_ARGB1555  /*!< ARGB1555 LTDC像素格式 */
#define ARGB4444 								LTDC_PIXEL_FORMAT_ARGB4444  /*!< ARGB4444 LTDC像素格式 */


#define LCD_HSYNC_WIDTH							1
#define LCD_VSYNC_HEIGHT						1

#define LCD_HBP									46	//Horizon back porch
#define LCD_VBP									23	//Vertical back porch
#define LCD_HFP									50	//Horizon front porch
#define LCD_VFP									13	//vertical front porch


#define TEST_L1_AREA_WIDTH						LCD_WIDTH
#define TEST_L1_AREA_HEIGHT						LCD_HEIGHT
#define TEST_L1_AREA_X_START					0
#define TEST_L1_AREA_Y_START					0
#define TEST_L1_AREA_X_END						(TEST_L1_AREA_X_START+TEST_L1_AREA_WIDTH)
#define TEST_L1_AREA_Y_END						(TEST_L1_AREA_Y_START+TEST_L1_AREA_HEIGHT)

#define TEST_L2_AREA_WIDTH						LCD_WIDTH
#define TEST_L2_AREA_HEIGHT						LCD_HEIGHT
#define TEST_L2_AREA_X_START					0
#define TEST_L2_AREA_Y_START					0
#define TEST_L2_AREA_X_END						(TEST_L2_AREA_X_START+TEST_L2_AREA_WIDTH)
#define TEST_L2_AREA_Y_END						(TEST_L2_AREA_Y_START+TEST_L2_AREA_HEIGHT)


#define LTDC_DISP_LAYER1						0
#define LTDC_DISP_LAYER2						1


#define DMA2D_LAYER_FG							1
#define DMA2D_LAYER_BG							0




#define LCD_RST_PORT							GPIOI
#define LCD_RST_PIN								GPIO_PIN_8
#define LCD_RST_PORT_CLK_ENABLE()				__HAL_RCC_GPIOI_CLK_ENABLE()
#define LCD_BL_PORT								GPIOH
#define LCD_BL_PIN								GPIO_PIN_15
#define LCD_BL_PORT_CLK_ENABLE()				__HAL_RCC_GPIOH_CLK_ENABLE()




typedef struct
{
    uint16_t width;         //LCD width
    uint16_t height;        //LCD height
    uint16_t id;            //LCD ID
    uint8_t  dir;           //0-landscape screen  1-portrait screen
    uint16_t wramcmd;       //write gui ram
    uint16_t setxcmd;       //set x coordinate
    uint16_t setycmd;       //set y coordinate
} lcd_cfg_t;

//scan direction
#define L2R_U2D  0      //letf--->right  up--->down
#define L2R_D2U  1      //letf--->right  down--->up
#define R2L_U2D  2      //right--->letf  up--->down
#define R2L_D2U  3      //right--->letf  down--->up

#define U2D_L2R  4      //up--->down  letf--->right
#define U2D_R2L  5      //up--->down  right--->left
#define D2U_L2R  6      //down--->up  letf--->right
#define D2U_R2L  7      //down--->up  right--->left

#ifdef BSP_USING_TOUCH_RES
#define DFT_SCAN_DIR  D2U_L2R  //scan direction of resister touchscreen
#endif // BSP_USING_TOUCH_RES

extern uint32_t ltdc_layer1_buf[LCD_MAX_LAYER_BUF_SIZE/4];
extern uint32_t ltdc_layer2_buf[LCD_MAX_LAYER_BUF_SIZE/4];

void Lcd_Init(void);
void lcd_fill_screen(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, void *pcolor);
void lcd_disp_init(uint32_t x,uint32_t y);
#endif /* __LCD_H__ */

