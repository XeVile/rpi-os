#include "gpio.h"
#include "utils.h"

/*
** REFACTORED V2.0
** Easier to use for Higher level access
** GPIO Pin can be input as per documentation
** No physical address or Name need be used
*/

PinData set_pin(u8 pinNumber, GPIO_Func func) {
  PinData Pin;
  Pin.BitStart = (pinNumber * 3) % 30;
  Pin.Reg = pinNumber / 10;

  Pin.Selector = REGS_GPIO->func_sel[Pin.Reg];
  Pin.Selector &= ~(7 << Pin.BitStart);
  Pin.Selector |= ~(func << Pin.BitStart);

  return Pin;
}

void gpio_set_func(u8 pinNumber, GPIO_Func func) {
  PinData P = set_pin(pinNumber, func);
  REGS_GPIO->func_sel[P.Reg] = P.Selector;
}

void gpio_pin_enable(u8 pinNumber) {
  REGS_GPIO->pud_en = 0;
  delay(150);
  REGS_GPIO->pud_clk_en[pinNumber / 32] = 1 << (pinNumber % 32);
  delay(150);
  REGS_GPIO->pud_en = 0;
  REGS_GPIO->pud_clk_en[pinNumber / 32] = 0;
}
