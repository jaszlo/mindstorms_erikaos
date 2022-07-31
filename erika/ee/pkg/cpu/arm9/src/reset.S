#define ASM_INC
#include "cpu/arm9/inc/redefine.h"
// Import
.globl system_init
.globl copy_vectors
// Export
.globl vectors_start
.globl reset_handler
.globl reboot

vectors_start:
    LDR PC, reset_handler_addr
    LDR PC, undef_handler_addr
    LDR PC, swi_handler_addr
    LDR PC, prefetch_abort_handler_addr
    LDR PC, data_abort_handler_addr
    B .
    LDR PC, irq_handler_addr
    LDR PC, fiq_handler_addr

reset_handler_addr:          .word reset_handler
undef_handler_addr:          .word undef_handler
swi_handler_addr:            .word swi_handler
prefetch_abort_handler_addr: .word prefetch_abort_handler
data_abort_handler_addr:     .word data_abort_handler
irq_handler_addr:            .word irq_handler
fiq_handler_addr:            .word fiq_handler

vectors_end:


reset_handler:
    LDR SP, =USR_STACK_TOP          // Set Stack; defined in ee/pkg/mcu/<am1808/versatilepb>/cfg/cfg.mk
    BL copy_vectors                 // Initialize Exception Vector table

    MRS  r0, cpsr
    BIC  r0, #0x1f                  // Clear mode bits
    ORR  r0, #0x12                  // Select IRQ mode
    MSR  cpsr, r0                   // Enter IRQ mode
    LDR  sp, =IRQ_STACK_TOP         // Set stack pointer; defined in ee/pkg/mcu/<am1808/versatilepb>/cfg/cfg.mk
    BIC  r0, #0x1f                  // Clear mode bits
    ORR  r0, #0x13                  // Select SVC mode
    MSR  cpsr, r0                   // Enter SVC mode


    bl system_init                  // Goes to system_init which will then goto main after setting up ErikaOS

#ifdef __AM1808__
#define ROM_START_ADDRESS 0xfffd0000
reboot:
    LDR PC, =ROM_START_ADDRESS
#endif
