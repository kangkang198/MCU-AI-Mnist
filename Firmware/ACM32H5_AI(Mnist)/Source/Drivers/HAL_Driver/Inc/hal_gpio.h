/******************************************************************************
*@file  : hal_gpio.h
*@brief : Header file of GPIO HAL module.
******************************************************************************/

#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

#include "hal.h"


/**
  * @brief   GPIO Init structure definition
  */
  
typedef struct
{
    uint32_t    Pin;                /*!< Specifies the GPIO pins to be configured.
                                         This parameter can be any value of @ref GPIO_pins */

    uint32_t    Mode;               /*!< Specifies the operating mode for the selected pins.
                                         This parameter can be a value of @ref GPIO_mode */

    uint32_t    Pull;               /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                                         This parameter can be a value of @ref GPIO_pull */

    uint32_t    Drive;              /*!< Specifies the Output drive capability for the selected pins.
                                         This parameter can be a value of @ref GPIO_drive */

    uint32_t    Alternate;          /*!< Peripheral to be connected to the selected pins
                                         This parameter can be a value of @ref GPIOEx_function_selection */
} GPIO_InitTypeDef;

/**
  * @}
  */

typedef enum
{
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET
}GPIO_PinState;


/** @defgroup GPIO_pins GPIO pins
  * @{
  */
  
#define GPIO_PIN_0                              ( (uint16_t)0x0001 )  /* Pin 0 selected    */
#define GPIO_PIN_1                              ( (uint16_t)0x0002 )  /* Pin 1 selected    */
#define GPIO_PIN_2                              ( (uint16_t)0x0004 )  /* Pin 2 selected    */
#define GPIO_PIN_3                              ( (uint16_t)0x0008 )  /* Pin 3 selected    */
#define GPIO_PIN_4                              ( (uint16_t)0x0010 )  /* Pin 4 selected    */
#define GPIO_PIN_5                              ( (uint16_t)0x0020 )  /* Pin 5 selected    */
#define GPIO_PIN_6                              ( (uint16_t)0x0040 )  /* Pin 6 selected    */
#define GPIO_PIN_7                              ( (uint16_t)0x0080 )  /* Pin 7 selected    */
#define GPIO_PIN_8                              ( (uint16_t)0x0100 )  /* Pin 8 selected    */
#define GPIO_PIN_9                              ( (uint16_t)0x0200 )  /* Pin 9 selected    */
#define GPIO_PIN_10                             ( (uint16_t)0x0400 )  /* Pin 10 selected   */
#define GPIO_PIN_11                             ( (uint16_t)0x0800 )  /* Pin 11 selected   */
#define GPIO_PIN_12                             ( (uint16_t)0x1000 )  /* Pin 12 selected   */
#define GPIO_PIN_13                             ( (uint16_t)0x2000 )  /* Pin 13 selected   */
#define GPIO_PIN_14                             ( (uint16_t)0x4000 )  /* Pin 14 selected   */
#define GPIO_PIN_15                             ( (uint16_t)0x8000 )  /* Pin 15 selected   */

/**
  * @}
  */

/** @brief  PIN mask for assert test
  */

#define GPIO_ALL_PIN_MASK                       ( 0x0000FFFFU ) /* PIN mask for assert test */

/** @defgroup GPIO_mode
  * @{
  */
#define  GPIO_MODE_INPUT                        ( 0x00000000U )   /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT_PP                    ( 0x00000001U )   /*!< Output Push Pull Mode                 */
#define  GPIO_MODE_OUTPUT_OD                    ( 0x00000011U )   /*!< Output Open Drain Mode                */
#define  GPIO_MODE_AF_PP                        ( 0x00000002U )   /*!< Alternate Function Push Pull Mode     */
#define  GPIO_MODE_AF_OD                        ( 0x00000012U )   /*!< Alternate Function Open Drain Mode    */
#define  GPIO_MODE_ANALOG_SWITCH_OFF            ( 0x00000003U )   /*!< Analog Mode  */
#define  GPIO_MODE_ANALOG_SWITCH_ON             ( 0x00000013U )   /*!< Analog Mode  */
#define  GPIO_MODE_IT_RISING                    ( 0x10110000U )   /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  GPIO_MODE_IT_FALLING                   ( 0x10210000U )   /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  GPIO_MODE_IT_RISING_FALLING            ( 0x10310000U )   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
#define  GPIO_MODE_EVT_RISING                   ( 0x10120000U )   /*!< External Event Mode with Rising edge trigger detection              */
#define  GPIO_MODE_EVT_FALLING                  ( 0x10220000U )   /*!< External Event Mode with Falling edge trigger detection             */
#define  GPIO_MODE_EVT_RISING_FALLING           ( 0x10320000U )   /*!< External Event Mode with Rising/Falling edge trigger detection      */

#define  GPIO_MODE_GPIO_MASK                  	( 0x00000003u )   /*!< GPIO interrupt Mask                */
#define  GPIO_MODE_GPIO_OUTPUT_TYPE_MASK		( 0x00000010u )   /*!< GPIO interrupt Mask                */
#define  GPIO_MODE_EXTI_MASK                  	( 0x10000000u )   /*!< GPIO interrupt Mask                */

/**
  * @}
  */
  
/** @defgroup GPIO_drive
  * @brief GPIO Output drive capability
  * @{
  */
#define  GPIO_DRIVE_LEVEL0                      ( 0x00000000U )   /*!< Output drive capability up to 2mA, please refer to the product datasheet */
#define  GPIO_DRIVE_LEVEL1                      ( 0x00000001U )   /*!< Output drive capability up to 4mA, please refer to the product datasheet */
#define  GPIO_DRIVE_LEVEL2                      ( 0x00000002U )   /*!< Output drive capability up to 6mA, please refer to the product datasheet */
#define  GPIO_DRIVE_LEVEL3                      ( 0x00000003U )   /*!< Output drive capability up to 8mA, please refer to the product datasheet */
#define  GPIO_DRIVE_LEVEL4                      ( 0x00000004U )   /*!< Output drive capability up to 8mA, please refer to the product datasheet */
#define  GPIO_DRIVE_LEVEL5                      ( 0x00000005U )   /*!< Output drive capability up to 8mA, please refer to the product datasheet */
#define  GPIO_DRIVE_LEVEL6                      ( 0x00000006U )   /*!< Output drive capability up to 8mA, please refer to the product datasheet */
#define  GPIO_DRIVE_LEVEL7                      ( 0x00000007U )   /*!< Output drive capability up to 8mA, please refer to the product datasheet */

/**
  * @}
  */

/** @defgroup GPIO_pull
  * @brief GPIO Pull-Up or Pull-Down Activation
  * @{
  */
#define  GPIO_NOPULL                            ( 0x00000000U )   /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP                            ( 0x00000001U )   /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN                          ( 0x00000002U )   /*!< Pull-down activation                */

/**
  * @}
  */


/** @defgroup GPIOEx_function_selection
  * @{
  */
#define  GPIO_FUNCTION_0                        ( 0x00000000U )
#define  GPIO_FUNCTION_1                        ( 0x00000001U )
#define  GPIO_FUNCTION_2                        ( 0x00000002U )
#define  GPIO_FUNCTION_3                        ( 0x00000003U )
#define  GPIO_FUNCTION_4                        ( 0x00000004U )
#define  GPIO_FUNCTION_5                        ( 0x00000005U )
#define  GPIO_FUNCTION_6                        ( 0x00000006U )
#define  GPIO_FUNCTION_7                        ( 0x00000007U )
#define  GPIO_FUNCTION_8                        ( 0x00000008U )
#define  GPIO_FUNCTION_9                        ( 0x00000009U )
#define  GPIO_FUNCTION_10                       ( 0x0000000AU )
#define  GPIO_FUNCTION_11                       ( 0x0000000BU )
#define  GPIO_FUNCTION_12                       ( 0x0000000CU )
#define  GPIO_FUNCTION_13                       ( 0x0000000DU )
#define  GPIO_FUNCTION_14                       ( 0x0000000EU )
#define  GPIO_FUNCTION_15                       ( 0x0000000FU )

/**
  * @}
  */

/** @defgroup  GPIO Private Macros
  * @{
  */
  
#define IS_GPIO_ALL_INSTANCE(__INSTANCE__)              (((__INSTANCE__) == GPIOA) || ((__INSTANCE__) == GPIOB) || \
                                                         ((__INSTANCE__) == GPIOC) || ((__INSTANCE__) == GPIOD) || \
                                                         ((__INSTANCE__) == GPIOE) || ((__INSTANCE__) == GPIOF) || \
                                                         ((__INSTANCE__) == GPIOG) || ((__INSTANCE__) == GPIOH) || \
                                                         ((__INSTANCE__) == GPIOI) || ((__INSTANCE__) == GPIOJ) || \
                                                         ((__INSTANCE__) == GPIOK) || ((__INSTANCE__) == GPIOL) || \
                                                         ((__INSTANCE__) == GPIOM) || ((__INSTANCE__) == GPION) || \
                                                         ((__INSTANCE__) == GPIOO) || ((__INSTANCE__) == GPIOP) || \
                                                         ((__INSTANCE__) == GPIOQ))

#define IS_GPIO_ALL_PIN(__PIN__)                        ((((uint32_t)(__PIN__) &  GPIO_ALL_PIN_MASK) != 0) &&   \
                                                         (((uint32_t)(__PIN__) & ~GPIO_ALL_PIN_MASK) == 0))

#define IS_GPIO_SINGLE_PIN(__PIN__)                     (((__PIN__) == GPIO_PIN_0)     ||\
                                                         ((__PIN__) == GPIO_PIN_1)     ||\
                                                         ((__PIN__) == GPIO_PIN_2)     ||\
                                                         ((__PIN__) == GPIO_PIN_3)     ||\
                                                         ((__PIN__) == GPIO_PIN_4)     ||\
                                                         ((__PIN__) == GPIO_PIN_5)     ||\
                                                         ((__PIN__) == GPIO_PIN_6)     ||\
                                                         ((__PIN__) == GPIO_PIN_7)     ||\
                                                         ((__PIN__) == GPIO_PIN_8)     ||\
                                                         ((__PIN__) == GPIO_PIN_9)     ||\
                                                         ((__PIN__) == GPIO_PIN_10)    ||\
                                                         ((__PIN__) == GPIO_PIN_11)    ||\
                                                         ((__PIN__) == GPIO_PIN_12)    ||\
                                                         ((__PIN__) == GPIO_PIN_13)    ||\
                                                         ((__PIN__) == GPIO_PIN_14)    ||\
                                                         ((__PIN__) == GPIO_PIN_15))
 
#define IS_GPIO_MODE(__GPIO__, __MODE__)                (((__MODE__) == GPIO_MODE_INPUT)                ||\
                                                         ((__MODE__) == GPIO_MODE_OUTPUT_PP)            ||\
                                                         ((__MODE__) == GPIO_MODE_OUTPUT_OD)            ||\
                                                         ((__MODE__) == GPIO_MODE_AF_PP)                ||\
                                                         ((__MODE__) == GPIO_MODE_AF_OD)                ||\
                                                         ((__MODE__) == GPIO_MODE_IT_RISING)            ||\
                                                         ((__MODE__) == GPIO_MODE_IT_FALLING)           ||\
                                                         ((__MODE__) == GPIO_MODE_IT_RISING_FALLING)    ||\
                                                         ((__MODE__) == GPIO_MODE_EVT_RISING)           ||\
                                                         ((__MODE__) == GPIO_MODE_EVT_FALLING)          ||\
                                                         ((__MODE__) == GPIO_MODE_EVT_RISING_FALLING)   ||\
                                                         ((__MODE__) == GPIO_MODE_ANALOG_SWITCH_OFF)   ||\
                                                         ((__MODE__) == GPIO_MODE_ANALOG_SWITCH_ON))


#define IS_GPIO_PULL(__PULL__)				            (((__PULL__) == GPIO_NOPULL)   ||\
                                                         ((__PULL__) == GPIO_PULLUP)   ||\
                                                         ((__PULL__) == GPIO_PULLDOWN))

#define IS_GPIO_DRIVE(__DRIVE__)			            (((__DRIVE__) == GPIO_DRIVE_LEVEL0)     ||\
                                                         ((__DRIVE__) == GPIO_DRIVE_LEVEL1)     ||\
                                                         ((__DRIVE__) == GPIO_DRIVE_LEVEL2)     ||\
                                                         ((__DRIVE__) == GPIO_DRIVE_LEVEL3)     ||\
                                                         ((__DRIVE__) == GPIO_DRIVE_LEVEL4)     ||\
                                                         ((__DRIVE__) == GPIO_DRIVE_LEVEL5)     ||\
                                                         ((__DRIVE__) == GPIO_DRIVE_LEVEL6)     ||\
                                                         ((__DRIVE__) == GPIO_DRIVE_LEVEL7))

#define IS_GPIO_PIN_ACTION(__ACTION__)                  (((__ACTION__) == GPIO_PIN_RESET) || \
                                                         ((__ACTION__) == GPIO_PIN_SET))

#define IS_GPIO_FUNCTION(__FUNCTION__)		            (((__FUNCTION__) == GPIO_FUNCTION_0) ||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_1) ||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_2) ||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_3) ||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_4) ||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_5) ||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_6) ||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_7) ||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_8) ||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_9) ||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_10)||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_11)||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_12)||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_13)||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_14)||\
                                                         ((__FUNCTION__) == GPIO_FUNCTION_15))
                                     
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/* HAL_GPIO_Init */
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);

/* HAL_GPIO_DeInit */
void HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);

/* HAL_GPIO_WritePin */
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, GPIO_PinState PinState);

/* HAL_GPIO_ReadPin */
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);

/* HAL_GPIO_TogglePin */
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);

HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);

#endif
