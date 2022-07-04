#ifndef __INCLUDE_ARM9_INTERNAL_H__
#define __INCLUDE_ARM9_INTERNAL_H__

#include "cpu/arm9/inc/ee_cpu.h"
#include "cpu/arm9/inc/cpsr.h"
#include "cpu/arm9/inc/ee_context.h"


// Required to set the next thread to start after IRQ schedule
extern EE_TID EE_std_endcycle_next_tid;
extern EE_UREG EE_hal_endcycle_next_thread;
extern EE_UREG EE_hal_endcycle_next_tos;

// SP index for each Task and shared SP 
extern const EE_UREG EE_std_thread_tos[];

// Getter and Setter of IRQ_nesting level require variable 
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

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

void EE_arm9_terminate_savestk(EE_ADDR sp, EE_ADDR realbody);
void EE_arm9_terminate_task(EE_ADDR sp) NORETURN;


/** Save the context and call the body of the task `tid'.  Implemented in
 * assembly */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_savestk(EE_TID tid)
{
  EE_arm9_terminate_savestk(&EE_terminate_data[tid], (EE_ADDR)EE_terminate_real_th_body[tid]);
}


void EE_arm9_write_stack_unmarked(EE_TID tid); // Implemented in ee_internal.c

/** Restore the context saved by EE_hal_terminate_savestk() for the task `tid' and
 * return from EE_hal_terminate_savestk().  Implemented in assembly */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_task(EE_TID tid)
{
  #ifdef __MULTI__
  EE_arm9_write_stack_unmarked(tid); // Unmark stack 
  #endif /* __MULTI__ */
  EE_arm9_terminate_task(&EE_terminate_data[tid]);
}

#endif /* defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__) */

#endif /* __INCLUDE_ARM9_INTERNAL_H__ */
