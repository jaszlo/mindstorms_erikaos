#include "cpu/arm9/inc/ee_internal.h"
#include "cpu/arm9/inc/ee_cpu.h"
#include "eecfg.h"

#define RUNNING 0U

// This file mostly exists for compilation and to declare variables required in other files.
EE_UREG EE_hal_endcycle_next_thread;
EE_UREG EE_hal_endcycle_next_tos;

extern EE_TYPESTATUS EE_th_status[];

// Get the current task in running state (can only be one as it is single core)
EE_TID EE_get_running_task(void)
{
  for (int i = 0; i < EE_MAX_TASK; i++) 
  {
    if (EE_th_status[i] == RUNNING) {
      return i;
    }
  }
  return -1;
}