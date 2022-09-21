#ifndef _P_GPIO_H_
#define _P_GPIO_H_

#include "base.h"
#include "common.h"

struct GPIO_PinData {
  reg32 reserved;
  reg32 data[2];
};

struct GPIO_Regs {
  reg32 func_sel[6];
  struct GPIO_PinData out_set;
  struct GPIO_PinData out_clr;
  struct GPIO_PinData level;
  struct GPIO_PinData ev_det_stat;
  struct GPIO_PinData re_det_en;
  struct GPIO_PinData fe_det_en;
  struct GPIO_PinData hi_det_en;
  struct GPIO_PinData lo_det_en;
  struct GPIO_PinData async_re_det;
  struct GPIO_PinData async_fe_det;
  reg32 reserved;
  reg32 pud_en;
  reg32 pud_clk_en[2];
};

#define REGS_GPIO ((struct GPIO_Regs *)(PBASE + 0x00200000))
#define REGS_UART ((struct GPIO_Regs *)(PL011_PBASE + 0x00201000))

#define GPFSEL1 (PBASE + 0x00200004)
#define GPSET0 (PBASE + 0x0020001C)
#define GPCLR0 (PBASE + 0x00200028)
#define GPPUD (PBASE + 0x00200094)
#define GPPUDCLK0 (PBASE + 0x00200098)

#endif // _P_GPIO_H_
