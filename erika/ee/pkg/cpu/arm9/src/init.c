extern int main();
#include "ee.h"
#include "cpu/arm9/inc/redefine.h"


#define EE_ISR_UNMASKED 0x00000000
#define EE_ISR_PRI_1 0x00000006U
#define EE_ISR_PRI_2 0x00000005U
#define EE_ISR_PRI_3 0x00000004U
#define EE_ISR_PRI_4 0x00000003U
#define EE_ISR_PRI_5 0x00000002U
#define EE_ISR_PRI_6 0x00000001U

void reboot(void);

void undef_handler(void)          { put_string("UNDEF EXC\n");for (;;); }
void swi_handler(void)            { put_string("SWI EXC\n");for (;;); }
void prefetch_abort_handler(void) { put_string("PREFETCH ABORT EXC\n");for (;;); }
void data_abort_handler(void)     { put_string("DATA ABORT EXC\n");for (;;); }


#include <stdint.h>
// For some reason optimization makes garbage out of this function if higher than "O1"
void copy_vectors(void)
{
    /*
    0: reset_handler
    1: undef_handler
    2: swi_handler
    3: prefetch_abort_handler
    4: data_abort_handler
    5: RESERVED
    6: irq_handler
    7: fiq_handler
    */
    #define RESERVED 5
    #define EXCEPTIONS 8
    extern uint32_t vectors_start;

	uint32_t *vectors_src = &vectors_start;
    
    #ifdef __VERSATILEPB__
	uint32_t *vectors_dst = (uint32_t *)0;
    #endif


    #ifdef __AM1808__
    /**
     *  Using CP15 (Coprocessor) to set position of the IVT which is either located at 0xFFFF0000 or 0x00000000.
     *  @Source: https://developer.arm.com/documentation/ddi0360/e/control-coprocessor-cp15/register-descriptions/c1--control-register?lang=en
     */
    asm(
        "mrc  p15, 0, r0, c1, c0, 0\n"  // (1) Read Controll Register 
        "orr  r0, #0x2000\n"            // (2) Put 13th bit to 1 to locate IVT at 0xFFFF0000 
        "mcr  p15, 0, r0, c1, c0, 0\n");// (3) Write Controll Register @Source: 
    uint32_t *vectors_dst = (uint32_t *)0xFFFF0000;
    #endif
    // 2 * EXCEPTIONS because we put  instrucitons for each exception at those addresses and then
    // the actual function behind those instruction. The instructions then load the value with a given offset to the pc
    for (int i = 0; i < 2 * EXCEPTIONS; i++)
    {
        if (i == RESERVED) {
            continue;
        }
        *(vectors_dst + i) = *(vectors_src + i);
    }
}

void system_init(void) {
    // As we might  use it and want to spar the user the call just do it here.
    EE_timer_stop();

    // Initialize AINTC
    EE_irq_init();
    // As we only vectorize IRQ for AM1808 this is only then required
    #ifdef __AM1808__
        // Cortex-MX style implementation of setting IRQ-handler 
        #ifdef EE_ARM9_TIMER_ISR
            EE_irq_register(IRQ_NUM_T64P0_TINT34, EE_ARM9_TIMER_ISR);
            // TOOD: set ISR prio to EE_ARM9_TIMER_ISR_PRI
            // EE_irq_set_prio(IRQ_NUM_T64P0_TINT34, EE_ARM9_TIMER_ISR_PRI) ?
        #endif /* EE_ARM9_TIMER_ISR */
    #endif /* __AM1808__ */

    // "Start ErikaOS"
    StartOS(OSDEFAULTAPPMODE);
    main();
    // Should only be here as long as developing
    
    // Only reboot on real hardware for faster debugging
    #ifdef __AM1808__
    reboot();
    #endif
    put_string("End of Program!\n");
    while(1);
}