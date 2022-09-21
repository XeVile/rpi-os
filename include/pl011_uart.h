#ifndef _UART_H_
#define _UART_H_

#include "peripherals/pl011_uart.h"

void uart_init(void);
char uart_recv(void);
void uart_send(char c);
void uart_send_string(char *str);

#endif // _UART_H_
