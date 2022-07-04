#define ASM_INC
#include "cpu/arm9/inc/redefine.h"
// Export
.globl EE_std_change_context

// Import
.globl EE_arm9_system_tos
.globl EE_arm9_active_tos
.globl EE_stack_is_marked
.globl EE_std_thread_tos
.section .text

#ifdef __MULTI__
/* Pseudo code for EE_std_change_context_multi():
     begin:
      (1) tos_index = EE_std_thread_tos[tid+1];
      (2) if is_not_the_current_stack(tos_index) {
          (3) save_callee_saved_registers();
          (4) switch_stacks(tos_index);
          (5) restore_callee_saved_registers();
      }
      (6) if (is_not_marked_stacked(tid)) {
		  (6.5) mark_stack(tid) [Not documented but required]
          (7)   tid = EE_std_run_task_code(tid);
          (8) 		goto begin;
      	}

      Please notice that the "goto begin" is actually a recursive call to
      EE_std_change_context_multi(), but in this way there is no stack growing.

      Please notice also that 'tid' must NOT be saved onto the stack before
      switching stacks, otherwise when switching from another stack back to the
      current one, you would overwrite its value.

      For processors where the return address is saved in a register, that
      register must be saved in the stack too.

      switch_stacks() should also update EE_hal_active_tos.

	void EE_std_change_context(EE_TID tid);
		r0 = tid
*/

EE_std_change_context:
/** (1)  tos_index = EE_std_thread_tos[tid+1]; **/
	// Save tid to r1
	MOV 	r1, r0		

	// Get tos_index for tid to r1 ->  r1 := EE_std_thread_tos[tid + 1];
	LDR		r2, =EE_std_thread_tos  // Base Address to r2
	ADD		r1, r1, #1				// tid + 1 for tid in r1
	LDR		r1, [r2, r1, lsl #2]	// Write tos_index to r1

	// Get active tos and write it to r3
	LDR		r2, =EE_arm9_active_tos
	LDR		r3, [r2]

	// (THIS)
	// r3 = EE_arm9_active_tos
	// r2 = &EE_arm9_active_tos
	// r1 = tos_index
	// r0 = tid

/** (2) if is_not_the_current_stack(tos_index) { **/
	CMP		r3, r1

	// If tos_index == active_tos we want to skip (3), (4) and (5)
	BEQ		skip_stack_change
	
/** (3) save_callee_saved_registers(); **/
	// We can use those regs as scratch registers until we restore context form stack we want to change to
	PUSH 	{r4-r11, lr}				// Only save context when not terminating
	
/** (4) switch_stacks(tos_index); **/
	// AGain get active tos etc. to restore (THIS) register layout
	// Get active tos and write it to r3
	LDR		r2, =EE_arm9_active_tos
	LDR		r3, [r2]

	// Save current TOS
	LDR		r4, =EE_arm9_system_tos

	// r3 = &EE_arm9_system_tos[EE_arm9_active_tos]
	ADD		r3, r4, r3, LSL#2

	// EE_arm9_system_tos[EE_arm9_active_tos] = current_sp
	STR		sp, [r3]

	// Get new TOS
	// r3 = &EE_arm9_system_tos[tos_index]
	ADD		r3, r4, r1, LSL#2

	// new_sp = EE_arm9_system_tos[tos_index]
	LDR		sp, [r3]
	
	// Update active TOS (index) 
	STR		r1, [r2]

/** (5) restore_callee_saved_registers(); **/
 	POP 	{r4-r11, lr}

skip_stack_change: // This lable is also used to return from EE_arm9_change_tos

	// Check if Stack is allready marked
  	LDR		r2, =EE_stack_is_marked 	// Base Address to r2
	MOV 	r1, r0						// Write TID to r1
	ADD		r1, r1, #1					// tid + 1 for tid in r1
   	LDR 	r1, [r2, r1, lsl #2]		// Write is_stack_marked to r1

/** (6) if (is_not_marked_stacked(tid)) { **/
	CMP		r1, #0

	// If stack == marked skip (7) and (8)
	// If the task is marked we already started it and dont want to start from the begining
	BNE	skip_std_run_task 

/** (6.5) mark_stack(tid) [Not documented but required] **/
	// EE_stack_is_marked[tid + 1] = 1;
	// r2 still holds EE_stack_is_marked AND
	MOV 	r1, r0						// Write TID to r1
	ADD		r1, r1, #1					// tid + 1 for tid in r1
	MOV		r3, #1						// Write 1 to r3 as we want to store 1 at EE_stack_is_marked[tid + ]
	STR 	r3, [r2, r1, lsl #2]		// Write is_stack_marked to r1
	

/** (7) tid = EE_std_run_task_code(tid); **/
	// We never modified r1 therefore it still hold tid
	// Return value tid written to r0 where tid is supposed to be at start of the function
	PUSH    {lr}	// BL instruction will overwrit LR therefore save it
	BL 		EE_std_run_task_code
	POP		{lr}	// Restore BL from before BL instruction	
	// No specific value required at start of function for r3
	LDR 	r3, =EE_std_change_context

/** (8) goto begin; **/
 	MOV		pc, r3
	
skip_std_run_task:
	
	// Return from function
	MOV		pc, lr
#endif /* __MULTI__ */