#include "mini_uart.h"
#include "gpio.h"
#include "utils.h"

#define TXD 14
#define RXD 15

void mini_uart_init() {
  /* Get the Physical address of Function Select 1
   * Map the address from 64-bit to 32-bit
   * Required for byte access

   * selector = get32(GPFSEL1);
   * // Clear Pin 14        => 0x3F200004
   * selector &= ~(7 << 12);
   * // Set ALT5 for Pin 14 => 0x3F202004
   * selector |= 2 << 12;
   * // Clear Pin 15        => 0x3F202004
   * selector &= ~(7 << 15);
   * // Set ALT5 for Pin 15 => 0x3F23A004
   * selector |= 2 << 15;
   * put32(GPFSEL1, selector);

   * similar implememntation
   */
  gpio_set_func(TXD, GFAlt5);
  gpio_set_func(RXD, GFAlt5);

  /* Implementing PULL UP and PULL DOWN states
   * 1. As per docs, a delay of 150 cycles is expected for
   *    control signal to be intercepted
   * 2. Write pins 14 and 15 into GPPUDCLOCK0/1
   * 3. Wait 150 cycles for control signal state change
   * 4. Write to same GPPUDCLOCK to remove added pins

   * put32(GPPUD, 0);
   * delay(150);
   * put32(GPPUDCLK0, (1 << 14) | (1 << 15));
   * delay(150);
   * put32(GPPUDCLK0, 0);

   * Similar implementation
   */
  gpio_pin_enable(TXD);
  gpio_pin_enable(RXD);

  /* Enable Mini UART and access to it's registers
   * Disable auto flow of control for Transmission and receiving
   * Disable Transmit and receive interrupts
   */
  put32(AUX_ENABLES, 1);
  // Extra control - for auto flow
  put32(AUX_MU_CNTL_REG, 0);
  put32(AUX_MU_IER_REG, 0);
  // Set Line Control - Enable 8-bit mode
  put32(AUX_MU_LCR_REG, 3);
  // Set Modem Control - Request-to-Send (RTS) to high
  put32(AUX_MU_MCR_REG, 0);
  // Set baud rate to approx 11520
  put32(AUX_MU_BAUD_REG, BAUD_REG_VAL);

  // Enable Transmitter and receiver
  put32(AUX_MU_CNTL_REG, 3);
}

void mini_uart_send(char c) {
  // Check if Line status bit 5 is set to 1
  // Ready for taking input if so break;
  while (!(get32(AUX_MU_LSR_REG) & 0x20)) {
  };

  put32(AUX_MU_IO_REG, c);
}

char mini_uart_recv(void) {
  // Check if Line status bit 0 is set to 1
  while (!(get32(AUX_MU_LSR_REG) & 0x01)) {
  };

  // Check if any data was received
  return (get32(AUX_MU_IO_REG) & 0xFF);
}

void mini_uart_send_string(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    mini_uart_send((char)str[i]);
  }
}
