#include "ctp.h"
#include "i2c.h"
#include "delay.h"

void ctp_init(void)
{
    I2C_Init();
}

void ctp_write_reg(uint16_t reg, uint8_t *buf, uint16_t len)
{
    uint16_t i;
    I2C_Start();
    I2C_Write_Byte(GT1151Q_DEVICE_ADDR | I2C_WRITE_MODE);
    I2C_Write_Byte((uint8_t)(reg >> 8));    //HSB
    I2C_Write_Byte((uint8_t)(reg & 0xff));  //LSB
    for (i = 0; i < len; i++)
    {
        I2C_Write_Byte(buf[i]);
    }
    I2C_Stop();
}

void ctp_read_reg(uint16_t reg, uint8_t *buf, uint16_t len)
{
    uint16_t i;
    I2C_Start();
    I2C_Write_Byte(GT1151Q_DEVICE_ADDR | I2C_WRITE_MODE);
    I2C_Write_Byte((uint8_t)(reg >> 8));    //HSB
    I2C_Write_Byte((uint8_t)(reg & 0xff));  //LSB
   
    I2C_Stop();
    I2C_Start();
    I2C_Write_Byte(GT1151Q_DEVICE_ADDR | I2C_READ_MODE);
   
    for (i = 0; i < len; i++)
    {
        buf[i] = I2C_Read_Byte(i == (len - 1) ? I2C_NACK : I2C_ACK);
    }
    I2C_Stop();
}

bool ctp_is_pressed(void)
{
    uint8_t regValue;
    uint8_t pointNum;
    //¶ÁÈ¡×´Ì¬¼Ä´æÆ÷
    ctp_read_reg(GT1151Q_GSTID_REG, &regValue, 1);
    //¼ÇÂ¼´¥Ãþµã¸öÊý
    pointNum = regValue & 0x0F;
    //Çå³ý×´Ì¬¼Ä´æÆ÷
    regValue = 0;
    ctp_write_reg(GT1151Q_GSTID_REG, &regValue, 1);

    if(pointNum)
        return true;
    else 
        return false;
}

void ctp_get_xy(int16_t *x,int16_t *y)
{
    uint8_t buf[4];
    ctp_read_reg(GT1151Q_TP1_REG, buf, 4);
    *x = (int16_t)((buf[1] << 8) | buf[0]);
    *y = (int16_t)((buf[3] << 8) | buf[2]);
}


