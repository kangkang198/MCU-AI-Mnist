#ifndef __CTP_H__
#define __CTP_H__

#include "hal.h"

#define GT1151Q_CTRL_REG   0x8040      //GT1151Q控制寄存器
#define GT1151Q_CFGS_REG   0x8050      //GT1151Q配置起始地址寄存器
#define GT1151Q_PID_REG    0x8140      //GT1151Q产品ID寄存器

#define GT1151Q_GSTID_REG  0x814E      //GT1151Q当前检测到的触摸情况
#define GT1151Q_TP1_REG    0x8150      //第一个触摸点数据地址
#define GT1151Q_TP2_REG    0x8158      //第二个触摸点数据地址
#define GT1151Q_TP3_REG    0x8160      //第三个触摸点数据地址
#define GT1151Q_TP4_REG    0x8168      //第四个触摸点数据地址
#define GT1151Q_TP5_REG    0x8170      //第五个触摸点数据地址

//IIC设备地址（含最低位）
#define GT1151Q_DEVICE_ADDR (0x14 << 1)


#define CTP_XSIZE (800)
#define CTP_YSIZE (480)

#define CTP_I2C_NB  I2C2

#define CTP_I2C_GPIO GPIOH
#define CTP_SCL_PIN GPIO_PIN_4
#define CTP_SDA_PIN GPIO_PIN_5

#define CTP_INT_GPIO GPIOC
#define CTP_INT_PIN GPIO_PIN_9

void ctp_init(void);
bool ctp_is_pressed(void);
void ctp_get_xy(int16_t *x,int16_t *y);
#endif /* __CTP_H__ */

