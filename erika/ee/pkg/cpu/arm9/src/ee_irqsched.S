
//Import
.globl EE_get_after_IRQ_lr
.globl EE_get_running_task
.globl EE_oo_Schedule
.globl put_ptr
//Export
.globl EE_arm9_after_IRQ_schedule
.section .text
/** 
 * C-Implementation:
 *      void EE_arm9_after_IRQ_schedule(void)
 *      {
 *          EE_INT32 link_register = EE_get_after_IRQ_lr();
 *          // Fixup LR to go back to original context
 *          asm("MOV lr, %0"
 *              :
 *              : "r" (link_register) 
 *              : 
 *          );
 *          // Only schedule if a Task was actually running
 *          EE_TID running_task = EE_get_running_task();
 *          if (running_task >= 0) {
 *              Schedule();
 *          }
 *      }
 *  This function is never to be called by the User and only allowed to be "called" as returning from irq_handler
 *  because EE_get_after_IRQ_lr requires the setup of the LR storage done in the irq_handler
 */
EE_arm9_after_IRQ_schedule:
    BL      EE_get_after_IRQ_lr // r0 now contains new lr value
    MOV     lr, r0              // Restore original lr so it seems as if this function was called from within the interrupted Task
    PUSH    {lr}                // Save lr before scheduling
    BL      EE_get_running_task // r0 now contains the TID of the running task or EE_MAX_TASK if no task currently in running state
    CMP     r0, #0              // Now compare flag greater than or equal should be true if we want to call schedule
    BLGE    EE_oo_Schedule      // This assumes that we will later return to this function from Schedule!!!
    POP     {lr}                // Meaning we cant Schedule back to the interrupted Task!
    MOV     pc, lr
