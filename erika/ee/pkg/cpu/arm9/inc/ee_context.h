#include "cpu/arm9/inc/redefine.h"

#ifndef __INCLUDE_ARM9_CONTEXT__
#define __INCLUDE_ARM9_CONTEXT__

extern EE_TID EE_std_endcycle_next_tid;

/* The multistack version must be implemented in ASM; no standard
 * implementation, sorry.  This is the only function that performs context
 * switching.  The multistack version doesn't jump to the task body if its TID
 * has been marked as stacked.  This is used to switch to a task that has been
 * suspend by a previous call to EE_std_change_context(). */
#ifdef __MONO__
__DECLARE_INLINE__ void EE_std_change_context(EE_TID tid);
#endif
#ifdef __MULTI__
void EE_std_change_context(EE_TID tid);
#endif
/* Pseudo code for EE_std_change_context_multi():
     begin:
      tos_index = EE_std_thread_tos[tid+1];
      if is_not_the_current_stack(tos_index) {
          save_callee_saved_registers();
          switch_stacks(tos_index);
          restore_callee_saved_registers();
      }
      if (is_not_marked_stacked(tid)) {
          tid = EE_std_run_task_code(tid);
            goto begin;
      }

      Please notice that the "goto begin" is actually a recursive call to
      EE_std_change_context_multi(), but in this way there is no stack growing.

      Please notice also that 'tid' must NOT be saved onto the stack before
      switching stacks, otherwise when switching from another stack back to the
      current one, you would overwrite its value.

      For processors where the return address is saved in a register, that
      register must be saved in the stack too.

      switch_stacks() should also update EE_arm9_active_tos.
*/

/* Launch a new task, possibly switching to a different stack, clean up the task
 * after it ends, and call the scheduler (and switch to other tasks/stacks)
 * until there are no more tasks to switch to.  In the multistack version, also
 * change the current stack before returning if the scheduler asks for it. */
__DECLARE_INLINE__ void EE_hal_ready2stacked(EE_TID tid);


/* Launch a new task on the current stack, clean up the task after it ends, and
 * call the scheduler.  Return the next task to launch, which is "marked as
 * stacked" if there is no new task to launch. */
EE_TID EE_std_run_task_code(EE_TID tid);



/*
 * Inline implementations
 */
#ifdef __MONO__

/* With monostack, we need only the information that the task is stacked.  We
 * don't need to know which task it is, as there is no new stack to switch
 * to. */
__INLINE__ EE_TID __ALWAYS_INLINE__ EE_std_mark_tid_stacked( EE_TID tid)
{
  return ((EE_TID)-1);
}

#define EE_std_need_context_change(tid) ((tid) >= 0)

__INLINE__ void __ALWAYS_INLINE__ EE_std_change_context(EE_TID tid)
{
    do {
        tid = EE_std_run_task_code(tid);
    } while (EE_std_need_context_change(tid));
}

#endif /* __MONO__ */


#ifdef __MULTI__

// Implemented in ee_internal.c
void EE_arm9_write_stack_mark(EE_TID tid);
EE_TID EE_arm9_read_stack_mark(EE_TID tid);
//  This is simpler than bitmagic and works on every machine (simple flag array for each task if stack is marked)
__INLINE__ EE_TID __ALWAYS_INLINE__ EE_std_mark_tid_stacked(EE_TID tid)
{
    EE_arm9_write_stack_mark(tid);
    return tid;
}

/* Check if the TID is Marked Stacked */
__INLINE__ EE_TYPEBOOL __ALWAYS_INLINE__ EE_std_tid_is_marked_stacked(EE_TID tid)
{
  return EE_arm9_read_stack_mark(tid);
}

__INLINE__ EE_TYPEBOOL __ALWAYS_INLINE__ EE_std_need_context_change(EE_TID tid)
{
    EE_TYPEBOOL need_context_change;

    if ( EE_std_tid_is_marked_stacked(tid) )
    {
      need_context_change = (EE_arm9_active_tos != EE_std_thread_tos[tid]);
    } else {
      need_context_change = EE_TRUE;
    }

    return need_context_change;
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID tid)
{
    EE_TID tmp = EE_std_mark_tid_stacked(tid);
    EE_std_change_context(tmp);
}

#endif /* __MULTI__ */


/* The functions below should work for both the monostack and multistack
 * versions of the kernel, thanks to the macros defined above.  In the mono
 * version, all the stack-related stuff is ignored. */
__INLINE__ void EE_hal_ready2stacked(EE_TID tid)
{
    EE_std_change_context(tid);
}


__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID tid)
{
    EE_std_endcycle_next_tid = tid;
}

#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID tid)
{
    EE_std_endcycle_next_tid = EE_std_mark_tid_stacked(tid);
}
#else
#define EE_hal_endcycle_stacked(x) EE_hal_endcycle_stacked_impl()
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked_impl(void)
{
    EE_std_endcycle_next_tid = ((EE_TID)-1);
}
#endif

#endif /* __INCLUDE_ARM9_CONTEXT__ */
