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

void system_init(void) {
    // As we might  use it and want to spar the user the call just do it here.
    EE_timer_stop();

    // Initialize AINTC
    EE_irq_init();
    // Cortex-MX style implementation of setting IRQ-handler 
    #ifdef EE_ARM9_TIMER_ISR
        EE_irq_register(IRQ_NUM_T64P0_TINT34, EE_ARM9_TIMER_ISR);
        // TOOD: set ISR prio to EE_ARM9_TIMER_ISR_PRI
        // EE_irq_set_prio(IRQ_NUM_T64P0_TINT34, EE_ARM9_TIMER_ISR_PRI) ?
    #endif

    // "Start ErikaOS"
    StartOS(OSDEFAULTAPPMODE);
    main();
    // Should only be here as long as developing
    reboot();
    while(1);
}