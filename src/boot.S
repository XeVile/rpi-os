#include "mm.h"

.section ".text.boot"

.globl _start
_start:
    mrs     x0, mpidr_el1   // Get the processor ID for the "first" core
    and     x0, x0, #0xFF   // Check Processor ID
    cbz     x0, master      // Hang for all non-prim CPU
    b       proc_hang       // Hangs processor

proc_hang:
    b       proc_hang

master:
    adr     x0, bss_begin
    adr     x1, bss_end
    sub     x1, x1, x0
    bl      memzero

    mov     sp, #LOW_MEMORY
    bl      kernel_main
