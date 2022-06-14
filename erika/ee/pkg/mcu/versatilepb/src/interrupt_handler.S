// Export
.globl irq_handler
// Import
.globl isr_wrapper
.globl EE_IRQ_nesting_level
.globl EE_arm9_after_IRQ_schedule
.globl EE_write_after_IRQ_lr

.section .text
/**
 * IRQs are disabled on entering this function and enabled on leaving
 */
irq_handler:
  /** Save context:
   * r0-r3 Arguments parsed to function
   * r12: Intra-Procedure-call scratch register
   * r14/lr: Link register
   * @Source: https://en.wikipedia.org/wiki/Calling_convention
   */

  // Backup Instruction address where interrupt interrupted via function that requires the value to be stored in r4 
  SUB r4, lr, #0x4
  STMFD    r13!, {r0-r3, r12, lr} // lr = r14
  bl EE_write_after_IRQ_lr

  /**
   * Increase IRQ nesting level for ErikaOS (So for instance if ActivateTask is called inside IRQ handler
   * it is clear that the task should not be launched immediatly).
   * Note that IRQ nesting is not implemented but we increment it (to a maximum value of 1) in order for
   * OSEK-System-Services to note when they are being called from within an ISR. 
   */
  LDR	r0, =EE_IRQ_nesting_level
  LDR	r1, [r0]
  ADD	r1, r1, #1
  STR	r1, [r0]       

  ADD      lr, pc, #0        // Save return to this IRQ handler LR
  LDR      pc, =isr_wrapper  // Go to ISR

  // Decrease IRQ nesting level for ErikaOS
  LDR	r0, =EE_IRQ_nesting_level
  LDR	r1, [r0]
  SUB	r1, r1, #1
  STR	r1, [r0]     

  // Restore Context
  LDMFD    r13!, {r0-r3, r12, lr}
  
  // As we return overwrite LR so it 
  // seems for original context as if it called this function
  // In that function we restore our backed up LR
  LDR lr, =EE_arm9_after_IRQ_schedule

  // Note that the S in sub(S) flag toggle the IRQ bit in the CPSR register enabling IRQ atomtically
  // @Source: https://developer.arm.com/documentation/dui0489/i/arm-and-thumb-instructions/subs-pc--lr?lang=en  
  SUBS     pc, lr, #0x0
