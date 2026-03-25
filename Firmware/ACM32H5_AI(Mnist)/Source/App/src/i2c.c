#include "i2c.h"
#include "delay.h"

//I2C接口初始化
void I2C_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct; 
    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIO_InitStruct.Pin            = I2C_SCL_PIN | I2C_SDA_PIN;
    GPIO_InitStruct.Mode           = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull           = GPIO_PULLUP;
    GPIO_InitStruct.Drive          = GPIO_DRIVE_LEVEL3;
    GPIO_InitStruct.Alternate      = GPIO_FUNCTION_0;
    HAL_GPIO_Init(I2C_GPIO, &GPIO_InitStruct);
    I2C_SCL_HIGH();
    I2C_SDA_HIGH();
    delay_ms(50);
}

void I2C_SDA_OUTPUT(void)
{
    GPIO_InitTypeDef GPIO_InitStruct; 
    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIO_InitStruct.Pin            = I2C_SDA_PIN;
    GPIO_InitStruct.Mode           = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull           = GPIO_PULLUP;
    GPIO_InitStruct.Drive          = GPIO_DRIVE_LEVEL3;
    GPIO_InitStruct.Alternate      = GPIO_FUNCTION_0;
    HAL_GPIO_Init(I2C_GPIO, &GPIO_InitStruct);
}

void I2C_SDA_INPUT(void)
{
    GPIO_InitTypeDef GPIO_InitStruct; 
    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIO_InitStruct.Pin            = I2C_SDA_PIN;
    GPIO_InitStruct.Mode           = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull           = GPIO_PULLUP;
    GPIO_InitStruct.Drive          = GPIO_DRIVE_LEVEL3;
    GPIO_InitStruct.Alternate      = GPIO_FUNCTION_0;
    HAL_GPIO_Init(I2C_GPIO, &GPIO_InitStruct);
}

//产生IIC起始信号
void I2C_Start(void)
{
    I2C_SDA_OUTPUT(); //sda线输出
    I2C_SDA_HIGH();
    I2C_SCL_HIGH();
    delay_us(4);
    I2C_SDA_LOW(); //START:when CLK is high,DATA change form high to low
    delay_us(4);
    I2C_SCL_LOW(); //钳住I2C总线，准备发送或接收数据
}

//产生IIC停止信号
void I2C_Stop(void)
{
    I2C_SDA_OUTPUT(); //sda线输出
    I2C_SCL_LOW();
    I2C_SDA_LOW();  //STOP:when CLK is high DATA change form low to high
    delay_us(4);
    I2C_SCL_HIGH();
    I2C_SDA_HIGH(); //发送I2C总线结束信号
    delay_us(4);
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t I2C_Wait_Ack(void)
{
    uint8_t overtime = 0;
    I2C_SDA_INPUT(); //SDA设置为输入
    I2C_SDA_HIGH();
    delay_us(1);
    I2C_SCL_HIGH();
    delay_us(1);
    while (I2C_SDA_GET())
    {
        overtime++;
        if (overtime > 250)
        {
            I2C_Stop();
            return 1;
        }
    }
    I2C_SCL_LOW(); //时钟输出0
    return 0;
}

//产生ACK应答
void I2C_Ack(void)
{
    I2C_SCL_LOW();
    I2C_SDA_OUTPUT();
    I2C_SDA_LOW();
    delay_us(2);
    I2C_SCL_HIGH();
    delay_us(2);
    I2C_SCL_LOW();
}

//产生NACK非应答
void I2C_NAck(void)
{
    I2C_SCL_LOW();
    I2C_SDA_OUTPUT();
    I2C_SDA_HIGH();
    delay_us(2);
    I2C_SCL_HIGH();
    delay_us(2);
    I2C_SCL_LOW();
}

//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void I2C_Write_Byte(uint8_t byte)
{
    uint8_t i;
    I2C_SDA_OUTPUT();
    I2C_SCL_LOW(); //拉低时钟开始数据传输
    for (i = 0; i < 8; i++)
    {
        if (byte & 0x80)
            I2C_SDA_HIGH();
        else
            I2C_SDA_LOW();
        byte <<= 1;
        delay_us(2);
        I2C_SCL_HIGH();
        delay_us(2);
        I2C_SCL_LOW();
        delay_us(2);
    }
    I2C_Wait_Ack();
}

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t I2C_Read_Byte(uint8_t ack)
{
    uint8_t i, receive = 0;
    I2C_SDA_INPUT(); //SDA设置为输入
    for (i = 0; i < 8; i++)
    {
        I2C_SCL_LOW();
        delay_us(2);
        I2C_SCL_HIGH();
        receive <<= 1;
        if (I2C_SDA_GET())
            receive++;
        delay_us(1);
    }
    if (!ack)
        I2C_NAck(); //发送nACK
    else
        I2C_Ack(); //发送ACK
    return receive;
}
