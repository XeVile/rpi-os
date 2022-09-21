#include "mini_uart.h"

void kernel_main(void) {
  mini_uart_init();
  mini_uart_send_string("Hello World, Finally\r\n");
  mini_uart_send_string("BOARD: RaspberryPi 3\r\n");

  while (1) {
    mini_uart_send(mini_uart_recv());
  }
}
