#ifndef _MINI_UART_H_
#define _MINI_UART_H_

#include "common.h"
#include "peripherals/mini_uart.h"

void mini_uart_init(void);
char mini_uart_recv(void);
void mini_uart_send(char c);
void mini_uart_send_string(char *str);

#endif // _MINI_UART_H_
