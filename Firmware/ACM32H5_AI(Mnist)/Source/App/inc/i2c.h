#ifndef __I2C_H__
#define __I2C_H__

#include "hal.h"

#define I2C_GPIO GPIOH
#define I2C_SCL_PIN GPIO_PIN_4
#define I2C_SDA_PIN GPIO_PIN_5

#define I2C_WRITE_MODE (0x00)
#define I2C_READ_MODE (0x01)

#define I2C_ACK (0x01)
#define I2C_NACK (0x00)

#define I2C_SCL_HIGH()  HAL_GPIO_WritePin(I2C_GPIO,I2C_SCL_PIN,GPIO_PIN_SET)
#define I2C_SDA_HIGH()  HAL_GPIO_WritePin(I2C_GPIO,I2C_SDA_PIN,GPIO_PIN_SET)

#define I2C_SCL_LOW()   HAL_GPIO_WritePin(I2C_GPIO,I2C_SCL_PIN,GPIO_PIN_RESET)
#define I2C_SDA_LOW()   HAL_GPIO_WritePin(I2C_GPIO,I2C_SDA_PIN,GPIO_PIN_RESET)

#define I2C_SDA_GET()  HAL_GPIO_ReadPin(I2C_GPIO, I2C_SDA_PIN)

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_NAck(void);
void I2C_Write_Byte(uint8_t byte);
uint8_t I2C_Read_Byte(uint8_t ack);

#endif /* __LCD_H__ */