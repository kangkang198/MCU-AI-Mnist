#include "lcd.h"

#define TIME_MEASURE_PORT						GPIOC
#define TIME_MEASURE_PIN						GPIO_PIN_6

LTDC_HandleTypeDef  Ltdc_Handler={0};

PSRAM_SECTION uint32_t ltdc_layer1_buf[LCD_MAX_LAYER_BUF_SIZE/4];
PSRAM_SECTION uint32_t ltdc_layer2_buf[LCD_MAX_LAYER_BUF_SIZE/4];

__IO uint8_t  Test_LineITCnt;
void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc)
{	
	Test_LineITCnt++;
}

/**
  * @brief  初始化LCD层
  * @param  LayerIndex:  前景层(层1)或者背景层(层0)
  * @param  FB_Address:  每一层显存的首地址
  * @param  PixelFormat: 层的像素格式
  * @retval 无
  */
void LCD_LayerInit1(uint16_t LayerIndex, uint32_t FB_Address, uint32_t PixelFormat, uint32_t XSize, uint32_t YSize, uint32_t LoadType)
{
	LTDC_LayerCfgTypeDef  layer_cfg;

	/* 层初始化 */
	layer_cfg.WindowX0 = TEST_L1_AREA_X_START;				//窗口起始位置X坐标
	layer_cfg.WindowX1 = (layer_cfg.WindowX0+XSize);	//窗口结束位置X坐标
	layer_cfg.WindowY0 = TEST_L1_AREA_Y_START;				//窗口起始位置Y坐标
	layer_cfg.WindowY1 = (layer_cfg.WindowY0+YSize);  //窗口结束位置Y坐标
	layer_cfg.PixelFormat = PixelFormat;	//像素格式
	layer_cfg.FBStartAdress = FB_Address; //层显存首地址
	layer_cfg.Alpha = 0;				//用于混合的透明度常量，范围（0—255）0为完全透明
	layer_cfg.Alpha0 = 0;					//默认透明度常量，范围（0—255）0为完全透明
	layer_cfg.Backcolor.Blue = 0;			//层背景颜色蓝色分量
	layer_cfg.Backcolor.Green = 0;		//层背景颜色绿色分量
	layer_cfg.Backcolor.Red = 0;			//层背景颜色红色分量
	layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;//层混合系数1
	layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;//层混合系数2
	layer_cfg.ImageWidth = XSize;	//LCD_GetXSize();//设置图像宽度
	layer_cfg.ImageHeight = YSize;	//LCD_GetYSize();//设置图像高度

	HAL_LTDC_ConfigLayer(&Ltdc_Handler, &layer_cfg, LayerIndex); //设置选中的层参数

//	DrawProp[LayerIndex].BackColor = LCD_COLOR_WHITE;//设置层的字体颜色
//	DrawProp[LayerIndex].pFont = &LCD_DEFAULT_FONT;//设置层的字体类型
//	DrawProp[LayerIndex].TextColor = LCD_COLOR_BLACK; //设置层的字体背景颜色

	//__HAL_LTDC_RELOAD_CONFIG(&Ltdc_Handler);//重载层的配置参数
//	HAL_LTDC_Reload(&Ltdc_Handler,LTDC_RELOAD_IMMEDIATE);  //LTDC_RELOAD_VERTICAL_BLANKING   LTDC_RELOAD_IMMEDIATE
	HAL_LTDC_Reload(&Ltdc_Handler,LoadType);  //LTDC_RELOAD_VERTICAL_BLANKING   LTDC_RELOAD_IMMEDIATE
}


void LCD_LayerInit2(uint16_t LayerIndex, uint32_t FB_Address, uint32_t PixelFormat, uint32_t XSize, uint32_t YSize, uint32_t LoadType)
{
	LTDC_LayerCfgTypeDef  layer_cfg;

	/* 层初始化 */
	layer_cfg.WindowX0 = TEST_L2_AREA_X_START;				//窗口起始位置X坐标
	layer_cfg.WindowX1 = (layer_cfg.WindowX0+XSize);	//窗口结束位置X坐标
	layer_cfg.WindowY0 = TEST_L2_AREA_Y_START;				//窗口起始位置Y坐标
	layer_cfg.WindowY1 = (layer_cfg.WindowY0+YSize);  //窗口结束位置Y坐标
	layer_cfg.PixelFormat = PixelFormat;	//像素格式
	layer_cfg.FBStartAdress = FB_Address; //层显存首地址
	layer_cfg.Alpha = 0;				//用于混合的透明度常量，范围（0—255）0为完全透明
	layer_cfg.Alpha0 = 0;					//默认透明度常量，范围（0—255）0为完全透明
	layer_cfg.Backcolor.Blue = 0;			//层背景颜色蓝色分量
	layer_cfg.Backcolor.Green = 0;		//层背景颜色绿色分量
	layer_cfg.Backcolor.Red = 0;			//层背景颜色红色分量
	layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;//层混合系数1
	layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;//层混合系数2
	layer_cfg.ImageWidth = XSize;	//LCD_GetXSize();//设置图像宽度
	layer_cfg.ImageHeight = YSize;	//LCD_GetYSize();//设置图像高度

	HAL_LTDC_ConfigLayer(&Ltdc_Handler, &layer_cfg, LayerIndex); //设置选中的层参数

//	DrawProp[LayerIndex].BackColor = LCD_COLOR_WHITE;//设置层的字体颜色
//	DrawProp[LayerIndex].pFont = &LCD_DEFAULT_FONT;//设置层的字体类型
//	DrawProp[LayerIndex].TextColor = LCD_COLOR_BLACK; //设置层的字体背景颜色

	//__HAL_LTDC_RELOAD_CONFIG(&Ltdc_Handler);//重载层的配置参数
//	HAL_LTDC_Reload(&Ltdc_Handler,LTDC_RELOAD_IMMEDIATE);  //LTDC_RELOAD_VERTICAL_BLANKING   LTDC_RELOAD_IMMEDIATE
	HAL_LTDC_Reload(&Ltdc_Handler,LoadType);  //LTDC_RELOAD_VERTICAL_BLANKING   LTDC_RELOAD_IMMEDIATE
}


/**
  * @brief  设置LCD层的可视化
  * @param  L1State: 禁能或者使能 layer1
  * @retval 无
  */
void LCD_SetLayerVisible(FunctionalState L1State, FunctionalState L2State, uint32_t ReloadType)
{
	if (L1State == ENABLE)
	{
		__HAL_LTDC_LAYER_ENABLE(&Ltdc_Handler, 0);
	}
	else
	{
		__HAL_LTDC_LAYER_DISABLE(&Ltdc_Handler, 0);
	}

	if (L2State == ENABLE)
	{
		__HAL_LTDC_LAYER_ENABLE(&Ltdc_Handler, 1);
	}
	else
	{
		__HAL_LTDC_LAYER_DISABLE(&Ltdc_Handler, 1);
	}

	HAL_LTDC_Reload(&Ltdc_Handler,ReloadType);
}

/**
  * @brief  设置LCD的透明度常量
  * @param  LayerIndex: 前景层(层1)或者背景层(层0)
  * @param  Transparency: 透明度，范围（0—255）0为完全透明
  * @retval 无
  */
void LCD_SetTransparency(uint32_t LayerIndex, uint8_t Transparency)
{
	HAL_LTDC_SetAlpha(&Ltdc_Handler, Transparency, LayerIndex);
}

static void lcd_gpio_init(void)
{
    GPIO_InitTypeDef    GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin       = LCD_RST_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;
	GPIO_InitStruct.Drive = GPIO_DRIVE_LEVEL4;
	__HAL_RCC_GPIOI_CLK_ENABLE();//
    HAL_GPIO_Init(LCD_RST_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = LCD_BL_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;
	GPIO_InitStruct.Drive = GPIO_DRIVE_LEVEL4;
	__HAL_RCC_GPIOH_CLK_ENABLE();//
    HAL_GPIO_Init(LCD_BL_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_BL_PORT, LCD_BL_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_BL_PORT, LCD_BL_PIN, GPIO_PIN_RESET);

#if 1
{
    GPIO_InitTypeDef    GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin       = TIME_MEASURE_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;
	GPIO_InitStruct.Drive = GPIO_DRIVE_LEVEL4;
	__HAL_RCC_GPIOC_CLK_ENABLE();//
    HAL_GPIO_Init(TIME_MEASURE_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(TIME_MEASURE_PORT, TIME_MEASURE_PIN, GPIO_PIN_RESET);
}
#endif
}


//LCD reset
static void lcd_rst(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
	HAL_SimpleDelay(50);
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
	HAL_SimpleDelay(50);
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
}


//LCD backlight on
static void lcd_bl_on(void)
{
	HAL_GPIO_WritePin(LCD_BL_PORT, LCD_BL_PIN, GPIO_PIN_SET);
}

//LCD backlight off
static void lcd_bl_off(void)
{
	HAL_GPIO_WritePin(LCD_BL_PORT, LCD_BL_PIN, GPIO_PIN_RESET);
}


static void ltdc_init(void)
{
    /* LTDC Initialization -------------------------------------------------------*/

    /* Polarity configuration */
    /* Initialize the horizontal synchronization polarity as active low */
    Ltdc_Handler.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    /* Initialize the vertical synchronization polarity as active low */
    Ltdc_Handler.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    /* Initialize the data enable polarity as active low */
    Ltdc_Handler.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    /* Initialize the pixel clock polarity as input pixel clock */
    Ltdc_Handler.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

    /* Timing configuration */
    /* Horizontal synchronization width = Hsync - 1 */
    Ltdc_Handler.Init.HorizontalSync = LCD_HSYNC_WIDTH - 1;
    /* Vertical synchronization height = Vsync - 1 */
    Ltdc_Handler.Init.VerticalSync = LCD_VSYNC_HEIGHT - 1;
    /* Accumulated horizontal back porch = Hsync + HBP - 1 */
    Ltdc_Handler.Init.AccumulatedHBP = LCD_HSYNC_WIDTH + LCD_HBP - 1;
    /* Accumulated vertical back porch = Vsync + VBP - 1 */
    Ltdc_Handler.Init.AccumulatedVBP = LCD_VSYNC_HEIGHT + LCD_VBP - 1;
    /* Accumulated active width = Hsync + HBP + Active Width - 1 */
    Ltdc_Handler.Init.AccumulatedActiveW = LCD_HSYNC_WIDTH + LCD_HBP + LCD_WIDTH - 1;
    /* Accumulated active height = Vsync + VBP + Active Heigh - 1 */
    Ltdc_Handler.Init.AccumulatedActiveH = LCD_VSYNC_HEIGHT + LCD_VBP + LCD_HEIGHT - 1;
    /* Total height = Vsync + VBP + Active Heigh + VFP - 1 */
    Ltdc_Handler.Init.TotalHeigh = Ltdc_Handler.Init.AccumulatedActiveH + LCD_VFP;
    /* Total width = Hsync + HBP + Active Width + HFP - 1 */
    Ltdc_Handler.Init.TotalWidth = Ltdc_Handler.Init.AccumulatedActiveW + LCD_HFP;

    /* Configure R,G,B component values for LCD background color */
    Ltdc_Handler.Init.Backcolor.Blue = 0;
    Ltdc_Handler.Init.Backcolor.Green = 0;
    Ltdc_Handler.Init.Backcolor.Red = 0;

    Ltdc_Handler.Instance = LTDC;

	HAL_LTDC_Init(&Ltdc_Handler);

#if 1
    NVIC_ClearPendingIRQ(LTDC_IRQn);
    NVIC_SetPriority(LTDC_IRQn, 0x00);
	NVIC_EnableIRQ(LTDC_IRQn);
#endif

#if 1
    NVIC_ClearPendingIRQ(LTDC_ERR_IRQn);
    NVIC_SetPriority(LTDC_ERR_IRQn, 0x00);
	NVIC_EnableIRQ(LTDC_ERR_IRQn);
#endif
}

/**
  * @brief  使能显示
  * @retval 无
  */
void LCD_DisplayOn(void)
{
	/* 开显示 */
	__HAL_LTDC_ENABLE(&Ltdc_Handler);
	lcd_bl_on();
}

/**
  * @brief  禁能显示
  * @retval 无
  */
void LCD_DisplayOff(void)
{
	/* 关显示 */
	__HAL_LTDC_DISABLE(&Ltdc_Handler);
	lcd_bl_off();
}


/**
  * @brief  éè??LCD?o3???μ?ê×μ??·
  * @param  LayerIndex: ?°?°2?(2?1)?ò??±3?°2?(2?0)
  * @param  Address: LCD?o3???μ?ê×μ??·
  * @retval ?T
  */
void LCD_SetLayerAddress(uint32_t LayerIndex, uint32_t Address, uint32_t ReloadType)
{
	HAL_LTDC_SetAddress(&Ltdc_Handler, Address, LayerIndex, ReloadType);
}

void lcd_disp_init(uint32_t x,uint32_t y)
{
	uint32_t i, j;
	/* LCD 第一层初始化 */ 
	LCD_LayerInit1(0, (uint32_t)ltdc_layer1_buf,RGB565,x,y, LTDC_RELOAD_IMMEDIATE);
	LCD_LayerInit2(1, (uint32_t)ltdc_layer2_buf,RGB565,x,y, LTDC_RELOAD_IMMEDIATE);

    /* 配置第一和第二层的透明度,最小值为0，最大值为255*/
	LCD_SetTransparency(0, 255);
	LCD_SetTransparency(1, 0);
	
    memset(ltdc_layer1_buf, 0 ,sizeof(ltdc_layer1_buf));
	memset(ltdc_layer2_buf, 0 ,sizeof(ltdc_layer2_buf));
    
	LCD_SetLayerVisible(ENABLE, DISABLE, LTDC_RELOAD_IMMEDIATE);

	/* display enable */ 
	LCD_DisplayOn(); 
}

#if 0
void lcd_fill_array(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
	int i, j;
	lv_area_t DestArea;
	int ret;
	uint8_t *pBuf;

	pBuf = (uint16_t *)ltdc_layer1_buf;
	pBuf += ((y_start*LCD_WIDTH+x_start)*(LCD_BITS_PER_PIXLE/8));

	DestArea.x1 = x_start;
	DestArea.x2 = x_end;
	DestArea.y1 = y_start;
	DestArea.y2 = y_end;

	if(0!=(ret=dma2d_pic_cpy(DMA2D_INPUT_RGB565, pBuf, &DestArea, pcolor, 1)))
	{
		printfS("dma2d_pic_cpy() err: %d\r\n", ret);
	}
}
#else	//LVGL 2 buffer, and (driver->direct_mode = 1)
HAL_StatusTypeDef  HAL_Get_Reload_status(LTDC_HandleTypeDef *hltdc)
{
	return (hltdc->Instance->SRCR ? HAL_BUSY : HAL_OK);
}

void lcd_fill_screen(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, void *pcolor)
{
	HAL_GPIO_WritePin(TIME_MEASURE_PORT, TIME_MEASURE_PIN, GPIO_PIN_SET);
	LCD_SetLayerAddress(LTDC_DISP_LAYER1, (uint32_t)pcolor, LTDC_RELOAD_VERTICAL_BLANKING);
//	printfS("==: %d * %d  Addr:0x%08x\r\n", (x_end-x_start+1), (y_end-y_start+1), (uint32_t)pcolor);
	while(HAL_Get_Reload_status(&Ltdc_Handler));
	HAL_GPIO_WritePin(TIME_MEASURE_PORT, TIME_MEASURE_PIN, GPIO_PIN_RESET);
}
#endif


/**
  * @brief  时钟配置
  * @retval 无
  */
void LCD_ClockConfig(void)
{
	/* use external 12MHz crystal oscillator, LTDC clock =  (12*200/9)/PLL2Q/DckCfg */
	HAL_RCC_PLL2Config(ENABLE, RCC_PLL_SOURCE_XTH, 9, 200, 2, 15);
	HAL_RCC_PLL2QCLKConfig(ENABLE);

	HAL_LTDC_Clk_Div(RCC_PLL2CR_Q_DIV_9, RCC_DCKCFG_DIV_2);
}

void Lcd_Init(void)
{
	lcd_gpio_init();
	lcd_rst();
	lcd_bl_on();
	LCD_ClockConfig();
	ltdc_init();
}

void LTDC_IRQHandler(void)
{
	HAL_LTDC_IRQHandler(&Ltdc_Handler);
}

void LTDC_ERR_IRQHandler(void)
{
	extern void HAL_LTDC_ERR_IRQHandler(LTDC_HandleTypeDef *hltdc);

	printfS("E:%x\r\n", LTDC->ISR);
	HAL_LTDC_ERR_IRQHandler(&Ltdc_Handler);
}
