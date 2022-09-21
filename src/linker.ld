SECTIONS {
/* RPi loads IMG file and reads from begin */
/* .text.boot is therefore included first */
/* .text section contains kernel compiled instructions */
/* .rodata is the read only data section */
/* .data is the normal data section */
/* .bss data contains data that should be initialized to zero */
/* bss_begin and end symbol is used for aligning the section */
/* so that it starts wiht a multiple of 8 */
/*
/* Without alignment it is more difficult to use "str" instructions */
/* str only allows 8-byte aligned addresses */
    .text.boot : { *(.text.boot) }
    .text : { *.(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    . = ALIGN(0x8);
    bss_begin = .;
    .bss : { *(.bss) }
    bss_end = .;
}
