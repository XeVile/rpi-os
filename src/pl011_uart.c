#include "pl011_uart.h"
#include "gpio.h"
#include "utils.h"

/*
** A/, BCM2837
** CTS and RTS of following pins should be set to ALT Function 3
*/
#define TXD0 14
#define RXD0 15
#define CTS0 16
#define RTS0 17

#define TXD1 32
#define RXD1 33
#define CTS1 30
#define RTS1 31

void uart_init() {
  gpio_set_func(TXD0, GFAlt0);
  gpio_set_func(RXD0, GFAlt0);
  gpio_pin_enable(TXD0);
  gpio_pin_enable(RXD0);

  // Disable PL011 on inti
  // UARTCR -> Set UARTEN = 0
  // UARTISMC -> Set Masking off = 0
  put32(UARTCR, 0);
  put32(UARTIMSC, 0);

  /*
  ** A/Doc,
  ** BRD = UARTCLK / (16 * B_RATE)
  **
  ** Divided into two parts =>
  ** Integer + Fractional = IBRD + FBRD
  **
  ** Fractional part (6 Bits)) =>
  ** int(Remainder of IBRD * 2^6 + 0.5)
  ** (0.041666* 64 + 0.5) = ~3
  */
  put32(UARTIBRD, PL011_REG_VAL);
  put32(UARTFBRD, 3);

  // Parity bit disabled (SPS->Bit 7)
  // Set Word length to 8 Bits (Using bit 6-5)
  // Set FIFO enable (Using bit 4)
  // Therfore, 0111 << 4
  put32(UARTLCR_H, 7 << 4);

  // Enable RX -> Bit 9
  // Enable TX -> Bit 8
  // Enable UART -> Bit 0
  put32(UARTCR, (1 << 9) | (1 << 8) | (1 << 0));
}

char uart_recv(void) {
  // Check if RXFE is enabled to receive
  while (get32(UARTFR) & (1 << 4))
    ;

  // Get data and check if empty
  return (get32(UARTFR) & (0xFF));
}

void uart_send(char c) {
  // Check if TXFE is enabled to send
  while (get32(UARTFR) & (1 << 5))
    ;

  // Send character
  put32(UARTDR, c);
}

void uart_send_string(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    uart_send((char)str[i]);
  }
}
