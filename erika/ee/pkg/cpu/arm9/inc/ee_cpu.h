#ifndef __INCLUDE_ARM9_EE_CPU_H__
#define __INCLUDE_ARM9_EE_CPU_H__

#include "eecfg.h"


#ifdef __ENABLE_IO__
#include "cpu/arm9/inc/internal/debug_io.h"
#endif

#include "cpu/arm9/inc/internal/timer.h"
#include "cpu/arm9/inc/internal/interrupt.h"

#ifdef __GNU__
#include "cpu/common/inc/ee_compiler_gcc.h"
#endif

/* Initial stack offset (in words): Used in multistack. */
#ifndef ARM9_INIT_TOS_OFFSET
#define ARM9_INIT_TOS_OFFSET 10
#endif

/*************************************************************************
 HAL Types and structures
 *************************************************************************/

/* Primitive data types */
#include "cpu/common/inc/ee_types.h"

typedef EE_UINT32 EE_UREG;
typedef EE_INT32 EE_SREG;
typedef EE_UINT32 EE_FREG;
#define EE_UREG_SIZE 4

/* boolean type */
#ifndef EE_TYPEBOOL
typedef EE_UREG EE_TYPEBOOL;
#endif

/* boolean true define */
#ifndef EE_TRUE
#define EE_TRUE ((EE_TYPEBOOL)1U)
#endif

/* boolean false define */
#ifndef EE_FALSE
#define EE_FALSE ((EE_TYPEBOOL)0U)
#endif

/* ISR Priority representation type */
typedef EE_UREG EE_TYPEISR2PRIO;

/* Thread IDs */
typedef EE_INT32 EE_TID;

/* Thread IDs - unsigned version*/
typedef EE_UINT32 EE_UTID;

/* Used by the common layer to decide whether to start a new thread */
#define TID_IS_STACKED_MARK 0x80000000 // Only required for MULTI


static void EE_hal_endcycle_stacked(EE_TID thread);
static void EE_hal_endcycle_ready(EE_TID thread);

// Implemented in common files but required for scheduler
#define EE_hal_IRQ_stacked EE_hal_endcycle_stacked
#define EE_hal_IRQ_ready EE_hal_endcycle_ready


/* Use the "standard" implementation */
#include "cpu/common/inc/ee_hal_structs.h"
#include "cpu/common/inc/ee_types.h"


/******************************************************************************
 CPU Peripherals
 ******************************************************************************/

#include "cpu/arm9/inc/internal/timer.h"
#include "cpu/arm9/inc/internal/interrupt.h"

// Timer
#define EE_timer_init(p, c) timer_init(p, c)
#define EE_timer_start() timer_start()
#define EE_timer_stop() timer_stop()
#define EE_timer_clear_irq_flags() timer_clear_irq_flags

// IRQ
#define EE_irq_init() irq_init()
#define EE_irq_register(num, func) irq_register(num, func)
#define EE_irq_unregister(num) irq_unregister(num)
#define EE_irq_clear_status(num)  irq_clear_status(num)
#define EE_irq_enable() irq_enable()
#define EE_irq_disable() irq_disable()
#define EE_irq_enable_num(num) irq_enable_num(num)
#define EE_irq_disable_num(num) irq_disable_num(num)


#ifdef __MULTI__
#endif /* __MULTI__ */

/**********************************************************************/

/*
 * Interrupt Handling
 */

/** Hal Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
	irq_enable();
}

/** Hal Disable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
	irq_disable();
}

/** Hal Resume Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_resumeIRQ(EE_FREG f)
{
	(void)f; // Status changed by irq enabled
	irq_enable();
}

/** Hal Suspend Interrupts */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_suspendIRQ(void)
{
	irq_disable();
	return irq_status();
}


#endif /* __INCLUDE_ARM9_EE_CPU_H__ */
