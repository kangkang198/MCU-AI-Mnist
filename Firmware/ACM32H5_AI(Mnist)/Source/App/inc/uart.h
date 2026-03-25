#ifndef __UART_H__
#define __UART_H__

#include "hal.h"

void Uart_Init(UART_TypeDef *uartx, uint32_t baudrate);

#endif /* __UART_H__ */
