/******************************************************************************
*@file  : hal_ltdc.c
*@brief : GPIO HAL module driver.
******************************************************************************/

#include "hal.h" 

#ifdef HAL_LTDC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/    
/* Private function prototypes -----------------------------------------------*/
static void LTDC_SetConfig(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx);
/* Private functions ---------------------------------------------------------*/

/** @defgroup LTDC_Exported_Functions LTDC Exported Functions
  * @{
  */

/** @defgroup LTDC_Exported_Functions_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim   
 ===============================================================================
                ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the LTDC
      (+) De-initialize the LTDC 

@endverbatim
  * @{
  */


HAL_StatusTypeDef HAL_LTDC_Clk_Div(uint8_t PLL2Q, uint8_t DckCfg)
{
	__ISB();
	while(0==(RCC->PLL2CR&RCC_PLL2CR_PLL2FREERUN));

	//PLL2 Qclk output Q div value set
	RCC->PLL2CFR = ((RCC->PLL2CFR & (~(0x0F<<RCC_PLL2CFR_PLL2Q_Pos))) | ((PLL2Q&0x0F)<<RCC_PLL2CFR_PLL2Q_Pos));
	RCC->PLL2CR |= RCC_PLL2CR_PLL2UPDATEEN;
	__ISB();
	while(0==(RCC->PLL2CR&RCC_PLL2CR_PLL2FREERUN));

	//LTDC pixle clk divider set
	HAL_RCC_LCDPiexlClockDivConfig(DckCfg);

	return HAL_OK;
}

/**
  * @brief  Initialize the LTDC according to the specified parameters in the LTDC_InitTypeDef.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_Init(LTDC_HandleTypeDef *hltdc)
{
  uint32_t tmp = 0, tmp1 = 0;

  /* Check the LTDC peripheral state */
  if(hltdc == NULL)
  {
    return HAL_ERROR;
  }

  /* Check function parameters */
  assert_param(IS_LTDC_ALL_INSTANCE(hltdc->Instance));
  assert_param(IS_LTDC_HSYNC(hltdc->Init.HorizontalSync));
  assert_param(IS_LTDC_VSYNC(hltdc->Init.VerticalSync));
  assert_param(IS_LTDC_AHBP(hltdc->Init.AccumulatedHBP));
  assert_param(IS_LTDC_AVBP(hltdc->Init.AccumulatedVBP));
  assert_param(IS_LTDC_AAH(hltdc->Init.AccumulatedActiveH));
  assert_param(IS_LTDC_AAW(hltdc->Init.AccumulatedActiveW));
  assert_param(IS_LTDC_TOTALH(hltdc->Init.TotalHeigh));
  assert_param(IS_LTDC_TOTALW(hltdc->Init.TotalWidth));
  assert_param(IS_LTDC_HSPOL(hltdc->Init.HSPolarity));
  assert_param(IS_LTDC_VSPOL(hltdc->Init.VSPolarity));
  assert_param(IS_LTDC_DEPOL(hltdc->Init.DEPolarity));
  assert_param(IS_LTDC_PCPOL(hltdc->Init.PCPolarity));

  if(hltdc->State == HAL_LTDC_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hltdc->Lock = HAL_UNLOCKED;
    /* Init the low level hardware */
    HAL_LTDC_MspInit(hltdc);
  }

	__HAL_RCC_LTDC_CLK_ENABLE();
	__HAL_RCC_LTDC_RESET();

	
  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Configure the HS, VS, DE and PC polarity */
  hltdc->Instance->GCR &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL);
  hltdc->Instance->GCR |=  (uint32_t)(hltdc->Init.HSPolarity | hltdc->Init.VSPolarity | \
  hltdc->Init.DEPolarity | hltdc->Init.PCPolarity);
  hltdc->Instance->GCR |= LTDC_GCR_AHB_LOCK;

  /* Set Synchronization size */
  hltdc->Instance->SSCR &= ~(LTDC_SSCR_VSH | LTDC_SSCR_HSW);
  tmp = (hltdc->Init.HorizontalSync << 16);
  hltdc->Instance->SSCR |= (tmp | hltdc->Init.VerticalSync);

  /* Set Accumulated Back porch */
  hltdc->Instance->BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
  tmp = (hltdc->Init.AccumulatedHBP << 16);
  hltdc->Instance->BPCR |= (tmp | hltdc->Init.AccumulatedVBP);

  /* Set Accumulated Active Width */
  hltdc->Instance->AWCR &= ~(LTDC_AWCR_AAH | LTDC_AWCR_AAW);
  tmp = (hltdc->Init.AccumulatedActiveW << 16);
  hltdc->Instance->AWCR |= (tmp | hltdc->Init.AccumulatedActiveH);

  /* Set Total Width */
  hltdc->Instance->TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
  tmp = (hltdc->Init.TotalWidth << 16);
  hltdc->Instance->TWCR |= (tmp | hltdc->Init.TotalHeigh);

  /* Set the background color value */
  tmp = ((uint32_t)(hltdc->Init.Backcolor.Green) << 8);
  tmp1 = ((uint32_t)(hltdc->Init.Backcolor.Red) << 16);
  hltdc->Instance->BCCR &= ~(LTDC_BCCR_BCBLUE | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCRED);
  hltdc->Instance->BCCR |= (tmp1 | tmp | hltdc->Init.Backcolor.Blue);

  /* Enable the Transfer Error and FIFO underrun interrupts */
  __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_TE | LTDC_IT_FU);
//  __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_TE | LTDC_IT_FU|LTDC_IT_LI|LTDC_IT_RR);

  /* Enable LTDC by setting LTDCEN bit */
  __HAL_LTDC_ENABLE(hltdc);

  /* Initialize the error code */
  hltdc->ErrorCode = HAL_LTDC_ERROR_NONE;  

  /* Initialize the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  De-initialize the LTDC peripheral.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval None
  */

HAL_StatusTypeDef HAL_LTDC_DeInit(LTDC_HandleTypeDef *hltdc)
{
  /* DeInit the low level hardware */
  HAL_LTDC_MspDeInit(hltdc); 

	while(0 == (LTDC->CDSR&(1<<2)));	//disable ltdc while vsync is invalid to avoid screen blink
	__HAL_LTDC_DISABLE(hltdc);

  /* Initialize the error code */
  hltdc->ErrorCode = HAL_LTDC_ERROR_NONE;

  /* Initialize the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Initialize the LTDC MSP.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval None
  */
__weak void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_LTDC_MspInit could be implemented in the user file
   */ 
}

/**
  * @brief  De-initialize the LTDC MSP.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval None
  */
__weak void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_LTDC_MspDeInit could be implemented in the user file
   */
}

/**
  * @}
  */
  
/** @defgroup LTDC_Exported_Functions_Group2 IO operation functions 
 *  @brief   IO operation functions  
 *
@verbatim
 ===============================================================================
                      #####  IO operation functions  #####
 ===============================================================================  
    [..]  This section provides function allowing to:
      (+) Handle LTDC interrupt request

@endverbatim
  * @{
  */
/**
  * @brief  Handle LTDC interrupt request.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.  
  * @retval HAL status
  */
void HAL_LTDC_IRQHandler(LTDC_HandleTypeDef *hltdc)
{
  /* Transfer Error Interrupt management ***************************************/
  if(__HAL_LTDC_GET_FLAG(hltdc, LTDC_FLAG_TE) != RESET)
  {
    if(__HAL_LTDC_GET_IT_SOURCE(hltdc, LTDC_IT_TE) != RESET)
    {
      /* Disable the transfer Error interrupt */
      __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_TE);

      /* Clear the transfer error flag */
      __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_TE);

      /* Update error code */
      hltdc->ErrorCode |= HAL_LTDC_ERROR_TE;

      /* Change LTDC state */
      hltdc->State = HAL_LTDC_STATE_ERROR;

      /* Process unlocked */
      __HAL_UNLOCK(hltdc);

      /* Transfer error Callback */
      HAL_LTDC_ErrorCallback(hltdc);
    }
  }
  /* FIFO underrun Interrupt management ***************************************/
  if(__HAL_LTDC_GET_FLAG(hltdc, LTDC_FLAG_FU) != RESET)
  {
    if(__HAL_LTDC_GET_IT_SOURCE(hltdc, LTDC_IT_FU) != RESET)
    {
      /* Disable the FIFO underrun interrupt */
      __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_FU);

      /* Clear the FIFO underrun flag */
      __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_FU);

      /* Update error code */
      hltdc->ErrorCode |= HAL_LTDC_ERROR_FU;

      /* Change LTDC state */
      hltdc->State = HAL_LTDC_STATE_ERROR;

      /* Process unlocked */
      __HAL_UNLOCK(hltdc);
      
      /* Transfer error Callback */
      HAL_LTDC_ErrorCallback(hltdc);
    }
  }
  /* Line Interrupt management ************************************************/
  if(__HAL_LTDC_GET_FLAG(hltdc, LTDC_FLAG_LI) != RESET)
  {
    if(__HAL_LTDC_GET_IT_SOURCE(hltdc, LTDC_IT_LI) != RESET)
    {
      /* Disable the Line interrupt */
      __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_LI);

      /* Clear the Line interrupt flag */  
      __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_LI);

      /* Change LTDC state */
      hltdc->State = HAL_LTDC_STATE_READY;

      /* Process unlocked */
      __HAL_UNLOCK(hltdc);

      /* Line interrupt Callback */
      HAL_LTDC_LineEventCallback(hltdc);
    }
  }
  /* Register reload Interrupt management ***************************************/
  if(__HAL_LTDC_GET_FLAG(hltdc, LTDC_FLAG_RR) != RESET)
  {
    if(__HAL_LTDC_GET_IT_SOURCE(hltdc, LTDC_IT_RR) != RESET)
    {
      /* Disable the register reload interrupt */
      __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_RR);
      
      /* Clear the register reload flag */
      __HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_RR);
      
      /* Change LTDC state */
      hltdc->State = HAL_LTDC_STATE_READY;
      
      /* Process unlocked */
      __HAL_UNLOCK(hltdc);
      
      /* Register reload interrupt Callback */
      HAL_LTDC_ReloadEventCallback(hltdc);
    }
  }  
}


void HAL_LTDC_ERR_IRQHandler(LTDC_HandleTypeDef *hltdc)
{
	/* Clear the transfer error flag */
	__HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_TE);
	__HAL_LTDC_CLEAR_FLAG(hltdc, LTDC_FLAG_FU);
}



/**
  * @brief  Error LTDC callback.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval None
  */
__weak void HAL_LTDC_ErrorCallback(LTDC_HandleTypeDef *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);
  
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_LTDC_ErrorCallback could be implemented in the user file
   */
}

/**
  * @brief  Line Event callback.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval None
  */
__weak void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);
  
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_LTDC_LineEventCallback could be implemented in the user file
   */
}

/**
  * @brief  Reload Event callback.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval None
  */
__weak void HAL_LTDC_ReloadEventCallback(LTDC_HandleTypeDef *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);
  
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_LTDC_ReloadEvenCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup LTDC_Exported_Functions_Group3 Peripheral Control functions
 *  @brief    Peripheral Control functions 
 *
@verbatim   
 ===============================================================================
                    ##### Peripheral Control functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure the LTDC foreground or/and background parameters.
      (+) Set the active layer.
      (+) Configure the color keying.
      (+) Configure the C-LUT.
      (+) Enable / Disable the color keying.
      (+) Enable / Disable the C-LUT.
      (+) Update the layer position.
      (+) Update the layer size.
      (+) Update pixel format on the fly. 
      (+) Update transparency on the fly.
      (+) Update address on the fly.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the LTDC Layer according to the specified
  *         parameters in the LTDC_InitTypeDef and create the associated handle.
  * @param  hltdc      pointer to a LTDC_HandleTypeDef structure that contains
  *                    the configuration information for the LTDC.
  * @param  pLayerCfg  pointer to a LTDC_LayerCfgTypeDef structure that contains
  *                    the configuration information for the Layer.
  * @param  LayerIdx  LTDC Layer index.
  *                    This parameter can be one of the following values:
  *                    LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigLayer(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx)
{   
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_HCONFIGST(pLayerCfg->WindowX0));
  assert_param(IS_LTDC_HCONFIGSP(pLayerCfg->WindowX1));
  assert_param(IS_LTDC_VCONFIGST(pLayerCfg->WindowY0));
  assert_param(IS_LTDC_VCONFIGSP(pLayerCfg->WindowY1));
  assert_param(IS_LTDC_PIXEL_FORMAT(pLayerCfg->PixelFormat));
  assert_param(IS_LTDC_ALPHA(pLayerCfg->Alpha));
  assert_param(IS_LTDC_ALPHA(pLayerCfg->Alpha0));
  assert_param(IS_LTDC_BLENDING_FACTOR1(pLayerCfg->BlendingFactor1));
  assert_param(IS_LTDC_BLENDING_FACTOR2(pLayerCfg->BlendingFactor2));
  assert_param(IS_LTDC_CFBLL(pLayerCfg->ImageWidth));  
  assert_param(IS_LTDC_CFBLNBR(pLayerCfg->ImageHeight));

  /* Process locked */
  __HAL_LOCK(hltdc);
  
  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Copy new layer configuration into handle structure */
  hltdc->LayerCfg[LayerIdx] = *pLayerCfg;  

  /* Configure the LTDC Layer */  
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Initialize the LTDC state*/
  hltdc->State  = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Configure the color keying.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  RGBValue  the color key value
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t RGBValue, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Configure the default color values */
  LTDC_LAYER(hltdc, LayerIdx)->CKCR &=  ~(LTDC_LxCKCR_CKBLUE | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKRED);
  LTDC_LAYER(hltdc, LayerIdx)->CKCR  = RGBValue;

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Load the color lookup table.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  pCLUT     pointer to the color lookup table address.
  * @param  CLUTSize  the color lookup table size.  
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigCLUT(LTDC_HandleTypeDef *hltdc, uint32_t *pCLUT, uint32_t CLUTSize, uint32_t LayerIdx)
{
  uint32_t tmp = 0;
  uint32_t counter = 0;
  uint32_t pcounter = 0;

  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx)); 

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;  

  for(counter = 0; (counter < CLUTSize); counter++)
  {
    if(hltdc->LayerCfg[LayerIdx].PixelFormat == LTDC_PIXEL_FORMAT_AL44)
    {
      tmp  = (((counter + 16*counter) << 24) | ((uint32_t)(*pCLUT) & 0xFF) | ((uint32_t)(*pCLUT) & 0xFF00) | ((uint32_t)(*pCLUT) & 0xFF0000));
    }
    else
    { 
      tmp  = ((counter << 24) | ((uint32_t)(*pCLUT) & 0xFF) | ((uint32_t)(*pCLUT) & 0xFF00) | ((uint32_t)(*pCLUT) & 0xFF0000));
    }
    pcounter = (uint32_t)pCLUT + sizeof(*pCLUT);
    pCLUT = (uint32_t *)pcounter;

    /* Specifies the C-LUT address and RGB value */
    LTDC_LAYER(hltdc, LayerIdx)->CLUTWR  = tmp;
  }
  
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);  

  return HAL_OK;
}

/**
  * @brief  Enable the color keying.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_EnableColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{  
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Enable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_COLKEN;

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;  
}
  
/**
  * @brief  Disable the color keying.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_DisableColorKeying(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Disable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_COLKEN;

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Enable the color lookup table.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_EnableCLUT(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Enable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_CLUTEN;

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Disable the color lookup table.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)   
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_DisableCLUT(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
 
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_CLUTEN;

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Enable Dither.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval  HAL status
  */

HAL_StatusTypeDef HAL_LTDC_EnableDither(LTDC_HandleTypeDef *hltdc)
{
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Enable Dither by setting DTEN bit */
  LTDC->GCR |= (uint32_t)LTDC_GCR_DEN;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Disable Dither.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval  HAL status
  */

HAL_StatusTypeDef HAL_LTDC_DisableDither(LTDC_HandleTypeDef *hltdc)
{
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Disable Dither by setting DTEN bit */
  LTDC->GCR &= ~(uint32_t)LTDC_GCR_DEN;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Set the LTDC window size.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  XSize     LTDC Pixel per line
  * @param  YSize     LTDC Line number
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetWindowSize(LTDC_HandleTypeDef *hltdc, uint32_t XSize, uint32_t YSize, uint32_t LayerIdx) 
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

  /* Check the parameters (Layers parameters)*/
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_CFBLL(XSize));
  assert_param(IS_LTDC_CFBLNBR(YSize));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY; 

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* update horizontal stop */
  pLayerCfg->WindowX1 = XSize + pLayerCfg->WindowX0;

  /* update vertical stop */  
  pLayerCfg->WindowY1 = YSize + pLayerCfg->WindowY0;

  /* Reconfigures the color frame buffer pitch in byte */
  pLayerCfg->ImageWidth = XSize;

  /* Reconfigures the frame buffer line number */
  pLayerCfg->ImageHeight = YSize;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Set the LTDC window position.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  X0        LTDC window X offset
  * @param  Y0        LTDC window Y offset
  * @param  LayerIdx  LTDC Layer index.
  *                         This parameter can be one of the following values:
  *                         LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetWindowPosition(LTDC_HandleTypeDef *hltdc, uint32_t X0, uint32_t Y0, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;
  
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_CFBLL(X0));
  assert_param(IS_LTDC_CFBLNBR(Y0));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* update horizontal start/stop */
  pLayerCfg->WindowX0 = X0;
  pLayerCfg->WindowX1 = X0 + pLayerCfg->ImageWidth;

  /* update vertical start/stop */
  pLayerCfg->WindowY0 = Y0;
  pLayerCfg->WindowY1 = Y0 + pLayerCfg->ImageHeight;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reconfigure the pixel format.
  * @param  hltdc        pointer to a LTDC_HandleTypeDef structure that contains
  *                      the configuration information for the LTDC.
  * @param  Pixelformat  new pixel format value.
  * @param  LayerIdx     LTDC Layer index.
  *                      This parameter can be one of the following values:
  *                      LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1).
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetPixelFormat(LTDC_HandleTypeDef *hltdc, uint32_t Pixelformat, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

  /* Check the parameters */
  assert_param(IS_LTDC_PIXEL_FORMAT(Pixelformat));
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];  

  /* Reconfigure the pixel format */
  pLayerCfg->PixelFormat = Pixelformat;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);   

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reconfigure the layer alpha value.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Alpha     new alpha value.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetAlpha(LTDC_HandleTypeDef *hltdc, uint32_t Alpha, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

  /* Check the parameters */
  assert_param(IS_LTDC_ALPHA(Alpha));
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* Reconfigure the Alpha value */
  pLayerCfg->Alpha = Alpha;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = LTDC_SRCR_IMR;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}
/**
  * @brief  Reconfigure the frame buffer Address.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Address   new address value.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1).
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetAddress(LTDC_HandleTypeDef *hltdc, uint32_t Address, uint32_t LayerIdx, uint32_t ReloadType)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* Reconfigure the Address */
  pLayerCfg->FBStartAdress = Address;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Set the Immediate Reload type */
  hltdc->Instance->SRCR = ReloadType;

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Function used to reconfigure the pitch for specific cases where the attached LayerIdx buffer have a width that is
  *         larger than the one intended to be displayed on screen. Example of a buffer 800x480 attached to layer for which we 
  *         want to read and display on screen only a portion 320x240 taken in the center of the buffer. The pitch in pixels 
  *         will be in that case 800 pixels and not 320 pixels as initially configured by previous call to HAL_LTDC_ConfigLayer().
  * @note   This function should be called only after a previous call to HAL_LTDC_ConfigLayer() to modify the default pitch
  *         configured by HAL_LTDC_ConfigLayer() when required (refer to example described just above).
  * @param  hltdc              pointer to a LTDC_HandleTypeDef structure that contains
  *                            the configuration information for the LTDC.
  * @param  LinePitchInPixels  New line pitch in pixels to configure for LTDC layer 'LayerIdx'.
  * @param  LayerIdx           LTDC layer index concerned by the modification of line pitch.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetPitch(LTDC_HandleTypeDef *hltdc, uint32_t LinePitchInPixels, uint32_t LayerIdx)
{
  uint32_t tmp = 0;
  uint32_t pitchUpdate = 0;
  uint32_t pixelFormat = 0;
  
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  
  /* Process locked */
  __HAL_LOCK(hltdc);
  
  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;
  
  /* get LayerIdx used pixel format */
  pixelFormat = hltdc->LayerCfg[LayerIdx].PixelFormat;
  
  if(pixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    tmp = 4;
  }
  else if (pixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    tmp = 3;
  }
  else if((pixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
          (pixelFormat == LTDC_PIXEL_FORMAT_RGB565)   || \
          (pixelFormat == LTDC_PIXEL_FORMAT_ARGB1555) || \
         (pixelFormat == LTDC_PIXEL_FORMAT_AL88))
  {
    tmp = 2;
  }
  else
  {
    tmp = 1;
  }
  
  pitchUpdate = ((LinePitchInPixels * tmp) << 16);
  
  /* Clear previously set standard pitch */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR &= ~LTDC_LxCFBLR_CFBP;
  
  /* Set the Reload type as immediate update of LTDC pitch configured above */
  LTDC->SRCR |= LTDC_SRCR_IMR;
  
  /* Set new line pitch value */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR |= pitchUpdate;
  
  /* Set the Reload type as immediate update of LTDC pitch configured above */
  LTDC->SRCR |= LTDC_SRCR_IMR;
  
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hltdc);
  
  return HAL_OK;  
}

/**
  * @brief  Define the position of the line interrupt.
  * @param  hltdc   pointer to a LTDC_HandleTypeDef structure that contains
  *                 the configuration information for the LTDC.
  * @param  Line    Line Interrupt Position.
  * @note   User application may resort to HAL_LTDC_LineEventCallback() at line interrupt generation. 
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ProgramLineEvent(LTDC_HandleTypeDef *hltdc, uint32_t Line)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LIPOS(Line));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Disable the Line interrupt */
  __HAL_LTDC_DISABLE_IT(hltdc, LTDC_IT_LI);

  /* Set the Line Interrupt position */
  LTDC->LIPCR = (uint32_t)Line;

  /* Enable the Line interrupt */
  __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_LI);

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reload LTDC Layers configuration.
  * @param  hltdc      pointer to a LTDC_HandleTypeDef structure that contains
  *                    the configuration information for the LTDC.
  * @param  ReloadType This parameter can be one of the following values :
  *                      LTDC_RELOAD_IMMEDIATE : Immediate Reload
  *                      LTDC_RELOAD_VERTICAL_BLANKING  : Reload in the next Vertical Blanking
  * @note   User application may resort to HAL_LTDC_ReloadEventCallback() at reload interrupt generation. 
  * @retval  HAL status
  */
HAL_StatusTypeDef  HAL_LTDC_Reload(LTDC_HandleTypeDef *hltdc, uint32_t ReloadType)
{
  /* Check the parameters */
  assert_param(IS_LTDC_RELOAD(ReloadType));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;  
  
  /* Enable the Reload interrupt */  
  __HAL_LTDC_ENABLE_IT(hltdc, LTDC_IT_RR);
       
  /* Apply Reload type */
  hltdc->Instance->SRCR = ReloadType;        

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hltdc);
  
  return HAL_OK;
}

/**
  * @brief  Configure the LTDC Layer according to the specified without reloading
  *         parameters in the LTDC_InitTypeDef and create the associated handle.
  *         Variant of the function HAL_LTDC_ConfigLayer without immediate reload.
  * @param  hltdc      pointer to a LTDC_HandleTypeDef structure that contains
  *                    the configuration information for the LTDC.
  * @param  pLayerCfg  pointer to a LTDC_LayerCfgTypeDef structure that contains
  *                    the configuration information for the Layer.
  * @param  LayerIdx   LTDC Layer index.
  *                    This parameter can be one of the following values:
  *                    LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigLayer_NoReload(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx)
{   
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_HCONFIGST(pLayerCfg->WindowX0));
  assert_param(IS_LTDC_HCONFIGSP(pLayerCfg->WindowX1));
  assert_param(IS_LTDC_VCONFIGST(pLayerCfg->WindowY0));
  assert_param(IS_LTDC_VCONFIGSP(pLayerCfg->WindowY1));
  assert_param(IS_LTDC_PIXEL_FORMAT(pLayerCfg->PixelFormat));
  assert_param(IS_LTDC_ALPHA(pLayerCfg->Alpha));
  assert_param(IS_LTDC_ALPHA(pLayerCfg->Alpha0));
  assert_param(IS_LTDC_BLENDING_FACTOR1(pLayerCfg->BlendingFactor1));
  assert_param(IS_LTDC_BLENDING_FACTOR2(pLayerCfg->BlendingFactor2));
  assert_param(IS_LTDC_CFBLL(pLayerCfg->ImageWidth));  
  assert_param(IS_LTDC_CFBLNBR(pLayerCfg->ImageHeight));

  /* Process locked */
  __HAL_LOCK(hltdc);
  
  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Copy new layer configuration into handle structure */
  hltdc->LayerCfg[LayerIdx] = *pLayerCfg;  

  /* Configure the LTDC Layer */  
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Do not set the Immediate Reload  */

  /* Initialize the LTDC state*/
  hltdc->State  = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Set the LTDC window size without reloading.
  *         Variant of the function HAL_LTDC_SetWindowSize without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  XSize     LTDC Pixel per line
  * @param  YSize     LTDC Line number
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetWindowSize_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t XSize, uint32_t YSize, uint32_t LayerIdx) 
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

  /* Check the parameters (Layers parameters)*/
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_CFBLL(XSize));
  assert_param(IS_LTDC_CFBLNBR(YSize));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY; 

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* update horizontal stop */
  pLayerCfg->WindowX1 = XSize + pLayerCfg->WindowX0;

  /* update vertical stop */  
  pLayerCfg->WindowY1 = YSize + pLayerCfg->WindowY0;

  /* Reconfigures the color frame buffer pitch in byte */
  pLayerCfg->ImageWidth = XSize;

  /* Reconfigures the frame buffer line number */
  pLayerCfg->ImageHeight = YSize;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Do not set the Immediate Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Set the LTDC window position without reloading.
  *         Variant of the function HAL_LTDC_SetWindowPosition without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  X0        LTDC window X offset
  * @param  Y0        LTDC window Y offset
  * @param  LayerIdx  LTDC Layer index.
  *                         This parameter can be one of the following values:
  *                         LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetWindowPosition_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t X0, uint32_t Y0, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;
  
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  assert_param(IS_LTDC_CFBLL(X0));
  assert_param(IS_LTDC_CFBLNBR(Y0));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* update horizontal start/stop */
  pLayerCfg->WindowX0 = X0;
  pLayerCfg->WindowX1 = X0 + pLayerCfg->ImageWidth;

  /* update vertical start/stop */
  pLayerCfg->WindowY0 = Y0;
  pLayerCfg->WindowY1 = Y0 + pLayerCfg->ImageHeight;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Do not set the Immediate Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reconfigure the pixel format without reloading.
  *         Variant of the function HAL_LTDC_SetPixelFormat without immediate reload.
  * @param  hltdc        pointer to a LTDC_HandleTypeDfef structure that contains
  *                      the configuration information for the LTDC.
  * @param  Pixelformat  new pixel format value.
  * @param  LayerIdx     LTDC Layer index.
  *                      This parameter can be one of the following values:
  *                      LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1).
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetPixelFormat_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Pixelformat, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

  /* Check the parameters */
  assert_param(IS_LTDC_PIXEL_FORMAT(Pixelformat));
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];  

  /* Reconfigure the pixel format */
  pLayerCfg->PixelFormat = Pixelformat;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);   

  /* Do not set the Immediate Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reconfigure the layer alpha value without reloading.
  *         Variant of the function HAL_LTDC_SetAlpha without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Alpha     new alpha value.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetAlpha_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Alpha, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

  /* Check the parameters */
  assert_param(IS_LTDC_ALPHA(Alpha));
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* Reconfigure the Alpha value */
  pLayerCfg->Alpha = Alpha;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Do not set the Immediate Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Reconfigure the frame buffer Address without reloading.
  *         Variant of the function HAL_LTDC_SetAddress without immediate reload.   
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  Address   new address value.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1).
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetAddress_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t Address, uint32_t LayerIdx)
{
  LTDC_LayerCfgTypeDef *pLayerCfg;

  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Get layer configuration from handle structure */
  pLayerCfg = &hltdc->LayerCfg[LayerIdx];

  /* Reconfigure the Address */
  pLayerCfg->FBStartAdress = Address;

  /* Set LTDC parameters */
  LTDC_SetConfig(hltdc, pLayerCfg, LayerIdx);

  /* Do not set the Immediate Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Function used to reconfigure the pitch for specific cases where the attached LayerIdx buffer have a width that is
  *         larger than the one intended to be displayed on screen. Example of a buffer 800x480 attached to layer for which we 
  *         want to read and display on screen only a portion 320x240 taken in the center of the buffer. The pitch in pixels 
  *         will be in that case 800 pixels and not 320 pixels as initially configured by previous call to HAL_LTDC_ConfigLayer().
  * @note   This function should be called only after a previous call to HAL_LTDC_ConfigLayer() to modify the default pitch
  *         configured by HAL_LTDC_ConfigLayer() when required (refer to example described just above).
  *         Variant of the function HAL_LTDC_SetPitch without immediate reload.    
  * @param  hltdc              pointer to a LTDC_HandleTypeDef structure that contains
  *                            the configuration information for the LTDC.
  * @param  LinePitchInPixels  New line pitch in pixels to configure for LTDC layer 'LayerIdx'.
  * @param  LayerIdx           LTDC layer index concerned by the modification of line pitch.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_SetPitch_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LinePitchInPixels, uint32_t LayerIdx)
{
  uint32_t tmp = 0;
  uint32_t pitchUpdate = 0;
  uint32_t pixelFormat = 0;
  
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
  
  /* Process locked */
  __HAL_LOCK(hltdc);
  
  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;
  
  /* get LayerIdx used pixel format */
  pixelFormat = hltdc->LayerCfg[LayerIdx].PixelFormat;
  
  if(pixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    tmp = 4;
  }
  else if (pixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    tmp = 3;
  }
  else if((pixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
          (pixelFormat == LTDC_PIXEL_FORMAT_RGB565)   || \
          (pixelFormat == LTDC_PIXEL_FORMAT_ARGB1555) || \
         (pixelFormat == LTDC_PIXEL_FORMAT_AL88))
  {
    tmp = 2;
  }
  else
  {
    tmp = 1;
  }
  
  pitchUpdate = ((LinePitchInPixels * tmp) << 16);
  
  /* Clear previously set standard pitch */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR &= ~LTDC_LxCFBLR_CFBP;
  
  /* Set new line pitch value */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR |= pitchUpdate;
  
  /* Do not set the Immediate Reload  */
  
  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hltdc);
  
  return HAL_OK;  
}


/**
  * @brief  Configure the color keying without reloading.
  *         Variant of the function HAL_LTDC_ConfigColorKeying without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  RGBValue the color key value
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LTDC_ConfigColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t RGBValue, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Configure the default color values */
  LTDC_LAYER(hltdc, LayerIdx)->CKCR &=  ~(LTDC_LxCKCR_CKBLUE | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKRED);
  LTDC_LAYER(hltdc, LayerIdx)->CKCR  = RGBValue;

  /* Do not set the Immediate Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Enable the color keying without reloading.
  *         Variant of the function HAL_LTDC_EnableColorKeying without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_EnableColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{  
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Enable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_COLKEN;

  /* Do not set the Immediate Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;  
}

/**
  * @brief  Disable the color keying without reloading.
  *         Variant of the function HAL_LTDC_DisableColorKeying without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_DisableColorKeying_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Disable LTDC color keying by setting COLKEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_COLKEN;

  /* Do not set the Immediate Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Enable the color lookup table without reloading.
  *         Variant of the function HAL_LTDC_EnableCLUT without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_EnableCLUT_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));

  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_CLUTEN;

  /* Do not set the Immediate Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @brief  Disable the color lookup table without reloading.
  *         Variant of the function HAL_LTDC_DisableCLUT without immediate reload.
  * @param  hltdc     pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values:
  *                   LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)   
  * @retval  HAL status
  */
HAL_StatusTypeDef HAL_LTDC_DisableCLUT_NoReload(LTDC_HandleTypeDef *hltdc, uint32_t LayerIdx)
{
  /* Check the parameters */
  assert_param(IS_LTDC_LAYER(LayerIdx));
 
  /* Process locked */
  __HAL_LOCK(hltdc);

  /* Change LTDC peripheral state */
  hltdc->State = HAL_LTDC_STATE_BUSY;

  /* Disable LTDC color lookup table by setting CLUTEN bit */
  LTDC_LAYER(hltdc, LayerIdx)->CR &= ~(uint32_t)LTDC_LxCR_CLUTEN;

  /* Do not set the Immediate Reload  */

  /* Change the LTDC state*/
  hltdc->State = HAL_LTDC_STATE_READY; 

  /* Process unlocked */
  __HAL_UNLOCK(hltdc);

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup LTDC_Exported_Functions_Group4 Peripheral State and Errors functions
 *  @brief    Peripheral State and Errors functions 
 *
@verbatim   
 ===============================================================================
                  ##### Peripheral State and Errors functions #####
 ===============================================================================  
    [..]
    This subsection provides functions allowing to
      (+) Check the LTDC handle state.
      (+) Get the LTDC handle error code.  

@endverbatim
  * @{
  */ 

/**
  * @brief  Return the LTDC handle state.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval HAL state
  */
HAL_LTDC_StateTypeDef HAL_LTDC_GetState(LTDC_HandleTypeDef *hltdc)
{
  return hltdc->State;
}

/**
  * @brief  Return the LTDC handle error code.
  * @param  hltdc  pointer to a LTDC_HandleTypeDef structure that contains
  *               the configuration information for the LTDC.
* @retval LTDC Error Code
*/
uint32_t HAL_LTDC_GetError(LTDC_HandleTypeDef *hltdc)
{
  return hltdc->ErrorCode;
}

/**
  * @}
  */

/**
  * @brief  Configures the LTDC peripheral 
  * @param  hltdc   :  Pointer to a LTDC_HandleTypeDef structure that contains
  *                   the configuration information for the LTDC.
  * @param  pLayerCfg Pointer LTDC Layer Configuration structure
  * @param  LayerIdx  LTDC Layer index.
  *                   This parameter can be one of the following values: LTDC_LAYER_1 (0) or LTDC_LAYER_2 (1)
  * @retval None
  */
static void LTDC_SetConfig(LTDC_HandleTypeDef *hltdc, LTDC_LayerCfgTypeDef *pLayerCfg, uint32_t LayerIdx)
{
  uint32_t tmp = 0;
  uint32_t tmp1 = 0;
  uint32_t tmp2 = 0;

  /* Configure the horizontal start and stop position */
  tmp = ((pLayerCfg->WindowX1 + ((hltdc->Instance->BPCR & LTDC_BPCR_AHBP) >> 16)) << 16);
  LTDC_LAYER(hltdc, LayerIdx)->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
  LTDC_LAYER(hltdc, LayerIdx)->WHPCR = ((pLayerCfg->WindowX0 + ((hltdc->Instance->BPCR & LTDC_BPCR_AHBP) >> 16U) + 1U) | tmp);

  /* Configure the vertical start and stop position */
  tmp = ((pLayerCfg->WindowY1 + (hltdc->Instance->BPCR & LTDC_BPCR_AVBP)) << 16);
  LTDC_LAYER(hltdc, LayerIdx)->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
  LTDC_LAYER(hltdc, LayerIdx)->WVPCR  = ((pLayerCfg->WindowY0 + (hltdc->Instance->BPCR & LTDC_BPCR_AVBP) + 1U) | tmp);

  /* Specifies the pixel format */
  LTDC_LAYER(hltdc, LayerIdx)->PFCR &= ~(LTDC_LxPFCR_PF);
  LTDC_LAYER(hltdc, LayerIdx)->PFCR = (pLayerCfg->PixelFormat);

  /* Configure the default color values */
  tmp = ((uint32_t)(pLayerCfg->Backcolor.Green) << 8);
  tmp1 = ((uint32_t)(pLayerCfg->Backcolor.Red) << 16);
  tmp2 = (pLayerCfg->Alpha0 << 24);  
  LTDC_LAYER(hltdc, LayerIdx)->DCCR &= ~(LTDC_LxDCCR_DCBLUE | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCALPHA);
  LTDC_LAYER(hltdc, LayerIdx)->DCCR = (pLayerCfg->Backcolor.Blue | tmp | tmp1 | tmp2); 

  /* Specifies the constant alpha value */
  LTDC_LAYER(hltdc, LayerIdx)->CACR &= ~(LTDC_LxCACR_CONSTA);
  LTDC_LAYER(hltdc, LayerIdx)->CACR = (pLayerCfg->Alpha);

  /* Specifies the blending factors */
  LTDC_LAYER(hltdc, LayerIdx)->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
  LTDC_LAYER(hltdc, LayerIdx)->BFCR = (pLayerCfg->BlendingFactor1 | pLayerCfg->BlendingFactor2);

  /* Configure the color frame buffer start address */
  LTDC_LAYER(hltdc, LayerIdx)->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
  LTDC_LAYER(hltdc, LayerIdx)->CFBAR = (pLayerCfg->FBStartAdress);

  if(pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    tmp = 4;
  }
  else if (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    tmp = 3;
  }
  else if((pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
    (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_RGB565)   || \
      (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_ARGB1555) || \
        (pLayerCfg->PixelFormat == LTDC_PIXEL_FORMAT_AL88))
  {
    tmp = 2;
  }
  else
  {
    tmp = 1;
  }

  /* Configure the color frame buffer pitch in byte */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR  &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
  LTDC_LAYER(hltdc, LayerIdx)->CFBLR  = (((pLayerCfg->ImageWidth * tmp) << 16) | (((pLayerCfg->WindowX1 - pLayerCfg->WindowX0) * tmp)  + 3));
  /* Configure the frame buffer line number */
  LTDC_LAYER(hltdc, LayerIdx)->CFBLNR  &= ~(LTDC_LxCFBLNR_CFBLNBR);
  LTDC_LAYER(hltdc, LayerIdx)->CFBLNR  = (pLayerCfg->ImageHeight);

  /* Enable LTDC_Layer by setting LEN bit */  
  LTDC_LAYER(hltdc, LayerIdx)->CR |= (uint32_t)LTDC_LxCR_LEN;
}

/**
  * @}
  */

#endif /* HAL_LTDC_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

