ENTRY(reset_handler)
SECTIONS
{
 . = 0xc1000000;
 .text : {
    obj/pkg/cpu/arm9/src/ee_reset.o
 *(.text .rodata)
 }
 .data : { *(.data) }
 .bss : { *(.bss) }
 . = ALIGN(8);
 . = . + 0x1000; /* 4kB of stack memory */
 USR_STACK_TOP = .;
 . = . + 0x1000; /* 4kB of irq stack memory */
 IRQ_STACK_TOP = .;
}
