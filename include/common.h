#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef volatile u32 reg32;

typedef struct _PinData {
  u8 BitStart, Reg;
  u32 Selector;
} PinData;

// Constants
#define MHz *1000000
#define SYS_CLK_FREQ 250 MHz
#define PL011_CLK_FREQ 48 MHz
#define BAUD_REG_VAL (unsigned int)((SYS_CLK_FREQ / (8 * BAUD_RATE)) - 1)
#define PL011_REG_VAL                                                          \
  (unsigned int)((PL011_CLK_FREQ >> 1) * (1 / (8 * SYS_CLK_FREQ)))
#define BAUD_RATE 115200

#endif //_COMMON_H_
