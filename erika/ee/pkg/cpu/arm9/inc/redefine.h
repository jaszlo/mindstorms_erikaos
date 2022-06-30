/**
 * RT-Druid generates eecfg.h which contains generated defines relevant for the System.
 * As RT-Druid has no existing port it is being used with a workaround.
 * The workaround uses the cortex-m as a base for the OIL-compilation.
 * In order to use the generated cortex specific defines from the eecfg.h but with arm specific
 * names this file will redefine those defines.
 */

#ifndef __INCLUDE_ARM9_REDEFINE__
#define __INCLUDE_ARM9_REDEFINE__
#include "eecfg.h"


#ifndef ASM_INC 
// IRQ and TIMER redefinition
    #ifdef EE_CORTEX_MX_TIMER_ISR
        void EE_CORTEX_MX_TIMER_ISR(void);
        #define  EE_ARM9_TIMER_ISR EE_CORTEX_MX_TIMER_ISR
    #endif

    #ifdef EE_CORTEX_MX_TIMER_ISR_PRI
        #define EE_ARM9_TIMER_ISR_PRI EE_CORTEX_MX_TIMER_ISR_PRI
    #endif
#endif /* ASM_INC */


#ifdef __MULTI__
    #ifndef ASM_INC
    extern EE_UREG EE_cortex_mx_active_tos;
    #endif /* ASM_INC */

    // Stack redifinitions
    #define EE_arm9_system_tos EE_cortex_mx_system_tos

    // Index for the array above that returns 
    #define EE_arm9_active_tos EE_cortex_mx_active_tos
#endif
#endif /* __INCLUDE_ARM9_REDEFINE__ */