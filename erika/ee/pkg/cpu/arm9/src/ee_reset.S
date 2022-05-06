/** Memory layout created by linker and this start_up code.
 * 
 * [       0xC000 0000     ]   :   Start of RAM
 * [            ...        ]
 * [       0xC100 0000     ]   :   Start of Programm (End depends on binary size)
 * [            ...        ]
 * [       0xCF00 0000     ]   :   Start of IRQ-Stack (grows towards Start of RAM)
 * [            ...        ]
 * [       0xCFFF FFFF     ]   :   End of RAM / Start of USR-Stack
 *
 * Arm memory layout is explained here
 * @Source: https://www.ti.com/lit/ds/symlink/am1808.pdf#page=13
 *
 */
// Import
.globl setup_ivt
.globl system_init

// Export
.globl reset_handler
.globl reboot

reset_handler:
    LDR SP, =USR_STACK_TOP          // Set Stack; defined in cfg/arch/cc_arm9_gnu.ld
    BL setup_ivt                    // Initialize Exception Vector table

    MRS  r0, cpsr
    BIC  r0, #0x1f                  // Clear mode bits
    ORR  r0, #0x12                  // Select IRQ mode
    MSR  cpsr, r0                   // Enter IRQ mode
    LDR  sp, =IRQ_STACK_TOP         // Set stack pointer; defined in cfg/arch/cc_arm9_gnu.ld
    BIC  r0, #0x1f                  // Clear mode bits
    ORR  r0, #0x13                  // Select SVC mode
    MSR  cpsr, r0                   // Enter SVC mode

    bl system_init                  // Goes to system_init which will then goto main after setting up ErikaOS


#define ROM_START_ADDRESS 0xfffd0000
reboot:
    LDR PC, =ROM_START_ADDRESS