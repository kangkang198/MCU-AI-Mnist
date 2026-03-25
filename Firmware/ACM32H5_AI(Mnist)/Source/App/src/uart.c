#include "uart.h"

UART_HandleTypeDef UART_Handle;
void Uart_Init(UART_TypeDef *uartx, uint32_t baudrate)
{
    UART_Handle.Instance        = uartx;
    UART_Handle.Init.BaudRate   = baudrate;
    UART_Handle.Init.WordLength = UART_WORDLENGTH_8B;
    UART_Handle.Init.StopBits   = UART_STOPBITS_1;
    UART_Handle.Init.Parity     = UART_PARITY_NONE;
    UART_Handle.Init.Mode       = UART_MODE_TX_RX;
    UART_Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;

    HAL_UART_Init(&UART_Handle);
    
    HAL_UART_SetDebugUart(UART_Handle.Instance);
}

int _write(int file, char *ptr, int len)
{
	int i;

	for (i = 0; i < len; i++)
	{
	   __io_putchar( *ptr++ );
	}
    __io_putchar('\r');
	return len;
}