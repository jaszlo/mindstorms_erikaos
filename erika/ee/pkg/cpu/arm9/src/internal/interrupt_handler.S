#define ASM_INC // To only include defines and not C-functions
#include "cpu/arm9/inc/internal/interrupt.h"
#include "cpu/arm9/inc/internal/timer.h"

.section .text
// Export
.globl irq_handler
// Import
.globl EE_IRQ_nesting_level;

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
  STMFD    r13!, {r0-r3, r12, lr} // lr = r14

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

  /**
   * HIPVR2 conantains a pointer to the pointer of the addres of the ISR
   * @Source: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=311
   */ 
  LDR      r0, =AINTC_HIPVR2   
  LDR      r0, [r0]            // r0 now conatins the pointer to the address of the ISR   
  
  ADD      lr, pc, #0          // Save return to this IRQ handler LR
  LDR      pc, [r0]            // Go to ISR
  
  // Decrease IRQ nesting level for ErikaOS
  LDR	r0, =EE_IRQ_nesting_level
  LDR	r1, [r0]
  SUB	r1, r1, #1
  STR	r1, [r0]     

  // Restore Context and return
  LDMFD    r13!, {r0-r3, r12, lr}

  // Note that the S in sub(S) flag toggle the IRQ bit in the CPSR register enabling IRQ atomtically
  // @Source: https://developer.arm.com/documentation/dui0489/i/arm-and-thumb-instructions/subs-pc--lr?lang=en
  SUBS     pc, lr, #0x4