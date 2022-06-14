#ifndef __INCLUDE_ARM9_INTERNAL_H__
#define __INCLUDE_ARM9_INTERNAL_H__

#include "cpu/arm9/inc/ee_cpu.h"
#ifdef __AM1808__
#include "mcu/am1808/inc/interrupt.h"
#endif
#ifdef __VERSATILEPB__
#include "mcu/versatilepb/inc/interrupt.h"
#endif
#include "cpu/arm9/inc/cpsr.h"

extern EE_TID EE_std_endcycle_next_tid;

extern EE_UREG EE_hal_endcycle_next_thread;
extern EE_UREG EE_hal_endcycle_next_tos;

extern EE_UREG EE_IRQ_nesting_level;

// Get current IRQ level of nesting
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_get_IRQ_nesting_level(void)
{
  return EE_IRQ_nesting_level;
}

// Save the current status of the interrupt and disable them 
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
  EE_FREG stat = cpsr_status();
  irq_disable();
  return stat;
}

// Restore the status saved before with the begin function
__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
  // Done implicitly as long as no IRQ nesting!
  //cpsr_write(f);
  //irq_enable();
}

// Prototypes for MONO and MULTI of the following ifdef
static void EE_hal_ready2stacked(EE_TID thread);
static void EE_hal_endcycle_ready(EE_TID thread);
static void EE_hal_endcycle_stacked(EE_TID thread);

#ifdef __MONO__
void EE_arm9_hal_ready2stacked(EE_ADDR thread_addr); // in Context.S
// Starts new thread
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID thread)
{
  #ifdef __DEBUG__ 
  put_string("Starting Task "); put_num(thread + 1); put_string("\n");
  #endif
  EE_arm9_hal_ready2stacked(EE_hal_thread_body[thread]);
  #ifdef __DEBUG__ 
  put_string("Finished Task "); put_num(thread + 1); put_string("\n");
  #endif
}
// Called at end of thread
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread)
{
  EE_hal_endcycle_next_thread = (EE_UREG)EE_hal_thread_body[thread];
}

// Called at the end of a thread instance 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread)
{
  EE_hal_endcycle_next_thread = 0;
  /* TID is useless */
}

#else // __MULTI__

// Starts new thread
void EE_arm9_hal_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index); // in Context.S
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID thread)
{
  EE_arm9_hal_ready2stacked(EE_hal_thread_body[thread], EE_arm9_thread_tos[thread + 1]);
}

// Called at end of thread
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread)
{
  EE_hal_endcycle_next_tos = EE_arm9_thread_tos[thread + 1];
  EE_hal_endcycle_next_thread = (EE_UREG)EE_hal_thread_body[thread];
}

// Called at the end of a thread instance 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread)
{
  EE_hal_endcycle_next_tos = EE_arm7_thread_tos[thread+1];
  EE_hal_endcycle_next_thread = 0;
}

// Called to change the active stack, typically inside blocking primitives 
// there is no mono version for this primitive.
void EE_arm9_hal_stkchange(EE_UREG, EE_UREG tos_index); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID thread)
{
  EE_arm9_hal_stkchange(0, EE_arm9_thread_tos[thread + 1]);
}
#endif

/* 
 * OO TerminateTask related stuffs
 */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

void EE_arm9_terminate_savestk(EE_ADDR sp, EE_ADDR realbody);
void EE_arm9_terminate_task(EE_ADDR sp) NORETURN;


/** Save the context and call the body of the task `tid'.  Implemented in
 * assembly */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_savestk(EE_TID t)
{
  EE_arm9_terminate_savestk(&EE_terminate_data[t], (EE_ADDR)EE_terminate_real_th_body[t]);
}

/** Restore the context saved by EE_hal_terminate_savestk() for the task `tid' and
 * return from EE_hal_terminate_savestk().  Implemented in assembly */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_task(EE_TID t)
{
  EE_arm9_terminate_task(&EE_terminate_data[t]);
}

#endif /* defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__) */

#endif /* __INCLUDE_ARM9_INTERNAL_H__ */
