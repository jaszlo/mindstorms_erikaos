#include "ee_internal.h"
#include "eecfg.h"
#include "cpu/arm9/inc/ee_io.h"
// Global to set which thread/stack to change to required to be declared
EE_UREG EE_hal_endcycle_next_thread;
EE_UREG EE_hal_endcycle_next_tos;


extern EE_UINT32 EE_terminate_data[];

void print_terminate_data(void)
{
  for (int i = 0; i < EE_MAX_TASK; i++)
  {
    put_ptr((void*)EE_terminate_data[i]);
  }
}
#ifdef __MULTI__

// Array with SPs index of each task
extern const EE_UREG EE_std_thread_tos[];

// Array with acutal SP of each task
extern struct EE_TOS EE_arm9_system_tos[];

// Flag to check if Stack is marked of task
EE_TID EE_stack_is_marked[EE_MAX_TASK + 1];
// Marks a stack for given tid
void EE_arm9_write_stack_mark(EE_TID tid) 
{
  EE_stack_is_marked[tid + 1] = 1;
}

// Returns 1 if is marked else 0
EE_TID EE_arm9_read_stack_mark(EE_TID tid)
{
  return EE_stack_is_marked[tid + 1];
}

// Helper Functions for ee_context.S
EE_TID EE_arm9_get_thread_tos(EE_TID tid) 
{
  return EE_std_thread_tos[tid + 1];
}

void EE_arm9_write_system_tos(EE_TID tid, EE_ADDR sp)
{
  EE_arm9_system_tos[tid].SYS_tos = sp;
}

EE_ADDR EE_arm9_read_system_tos(EE_TID tid)
{
  return EE_arm9_system_tos[tid].SYS_tos;
}
// End of Helper Functions for ee_context.S

#endif 
// Declare function implemented by OS to get running task (STATIC and INLINE but we require it in ASM therefore cant be static)
EE_TID EE_stk_queryfirst(void);
EE_TID EE_get_running_task(void)
{
  return EE_stk_queryfirst();
}


