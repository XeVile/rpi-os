#ifndef _GPIO_H_
#define _GPIO_H_

#include "common.h"
#include "peripherals/gpio.h"

/*
** Following BCM2837 Documentation
*/
typedef enum _GPIO_Func {
  GFInput = 0,
  GFOutput = 1,
  GFAlt0 = 4,
  GFAlt1 = 5,
  GFAlt2 = 6,
  GFAlt3 = 7,
  GFAlt4 = 3,
  GFAlt5 = 2
} GPIO_Func;

PinData set_pin(u8 pinNumber, GPIO_Func func);

void gpio_set_func(u8 pinNumber, GPIO_Func func);

void gpio_pin_enable(u8 pinNumber);

#endif //_GPIO_H_
