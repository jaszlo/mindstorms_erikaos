#include "cpu/arm9/inc/ee_irq.h"
#include "cpu/arm9/inc/ee_internal.h"
#include "eecfg.h"

#include "ee.h"
unsigned int EE_after_IRQ_lr[EE_MAX_TASK + 1]; // The last element is the LR for when a IRQ happens with no running task
EE_TID EE_get_running_task(void); // implemented in ee_internal.c

// Requires the lr value to write to be stored in r4!
void EE_write_after_IRQ_lr(void)
{
    EE_UREG link_register;
    asm("MOV %[result], r4\n" 
         : [result] "=r"(link_register)
         :
         :
    );
    EE_TID running_task = EE_get_running_task();
    if (running_task >= 0)
    {
        EE_after_IRQ_lr[running_task] = link_register;
    } else // No running task
    {
        EE_after_IRQ_lr[EE_MAX_TASK] = link_register;
    }
}

// Returns the address of the instruction to go back to from the interrupted task 
EE_INT32 EE_get_after_IRQ_lr(void)
{
    EE_TID running_task = EE_get_running_task();
    if (running_task >= 0)
    {
        return EE_after_IRQ_lr[running_task];
    } else // No running task
    {
        return EE_after_IRQ_lr[EE_MAX_TASK]; 
    }
}
