
//Import
.globl EE_get_after_IRQ_lr
.globl EE_get_running_task
.globl EE_after_IRQ_preemption
.globl put_ptr
.globl intctl_disable
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
    STMFD    sp!, {r0-r3, r12}          // Again save context
    BL      EE_get_after_IRQ_lr         // r0 now contains new lr value
    MOV     lr, r0                      // Restore original lr so it seems as if this function was called from within the interrupted Task
    PUSH    {lr}                        // Save lr before scheduling
    BL      EE_get_running_task         // r0 now contains the TID of the running task or EE_MAX_TASK if no task currently in running state
    CMP     r0, #0                      // Now compare flag greater than or equal should be true if we want to call schedule
    
    BL      intctl_enable               // Enable interrupts for either AINTC or PL190 depending on which MCU is being used
                                        // Respective disable call in
                                        // mcu/(am1808 or versatilepb)/src/interrupt_handler.S 

    BLGE    EE_after_IRQ_preemption     // Call "Scheduler" This will check if we even want to preempt
    BL      irq_enable                  // Enable interrupts again
    POP     {lr}                        // Meaning we cant Schedule back to the interrupted Task!
    LDMFD    sp!, {r0-r3, r12}          // Again restore context
    MOV     pc, lr
