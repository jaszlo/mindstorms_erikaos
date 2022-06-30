#define ASM_INC
#include "cpu/arm9/inc/redefine.h"

// Export
.globl EE_std_change_context

// Import
.globl EE_arm9_system_tos
.globl EE_arm9_active_tos
.globl EE_arm9_get_thread_tos
			
.section .text

// TODO: ATM we schedule back to the start of the function after TerminteTask but we want to go back to where Schedule was called


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
		  (7.5) if (tid >= 0) {
          (8) 		goto begin;
          		}
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

	// Save LR before its "destroyed" by function calls for later
	PUSH	{lr}
/** (1)  tos_index = EE_std_thread_tos[tid+1]; **/
	// Save tid to r1
	MOV 	r1, r0		

	// Get tos_index for tid ro r0 as tid is also in r1
	BL		EE_arm9_get_thread_tos	

	// Get active tos and write it to r3
	LDR		r2, =EE_arm9_active_tos
	LDR		r3, [r2]

	// r3 = EE_arm9_active_tos
	// r2 = &EE_arm9_active_tos
	// r1 = tid
	// r0 = tos_index

/** (2) if is_not_the_current_stack(tos_index) { **/
	CMP		r3, r0

	// If tos_index == active_tos we want to skip (3), (4) and (5)
	BEQ		skip_stack_change

	
/** (3) save_callee_saved_registers(); **/
	// We can use those regs as scratch registers until we restore context form stack we want to change to
 	STMFD	sp!, {r4-r11}
	
/** (4) switch_stacks(tos_index); **/

	// Save current TOS
	LDR		r4, =EE_arm9_system_tos

	// r3 = &EE_arm9_system_tos[EE_arm9_active_tos]
	ADD		r3, r4, r3, LSL#2

	// EE_arm9_system_tos[EE_arm9_active_tos] = current_sp
	STR		sp, [r3]

	// Get new TOS
	// r3 = &EE_arm9_system_tos[tos_index]
	ADD		r3, r4, r0, LSL#2

	// new_sp = EE_arm9_system_tos[tos_index]
	LDR		sp, [r3]
	
	// Update active TOS (index) 
	STR		r0, [r2]

/** (5) restore_callee_saved_registers(); **/
 	LDMFD	sp!, {r4-r11}

skip_stack_change: // This lable is also used to return from EE_arm9_change_tos

	// Write tid back to r0 
	MOV 	r0, r1 

	// EE_arm9_read_stack_mark rqeuiest to contain tid
	BL 		EE_arm9_read_stack_mark	

/** (6) if (is_not_marked_stacked(tid)) { **/
	// The conditionflag still holds true if we have did not have to change stack earlier
	// If skip_stack_change == taken && skip_std_run_task == taken then POP {lr}
	// This is required because this context switch is just supposed to go back to its original caller
	// But as we pushed LR at the beginning of the function our Stack is offset incorrectly by one PUSH
	BLNE	skip_lr_restoring 	// If we changed stack we do not want to do this
	CMP 	r0, #0 			 	// Check if the stack is marked as well  
	POPNE	{lr}				// Restore LR as described above
skip_lr_restoring:
	CMP		r0, #0

	// If stack == marked skip (7) and (8)
	// If the task is marked we already started it and dont want to start from the begining
	BNE	skip_std_run_task 

	// TID was saved in r1 restore it to r0 for function argument
	MOV 	r0, r1

/** (6.5) mark_stack(tid) [Not documented but required] **/
	BL		EE_arm9_write_stack_mark

	// Write tid back to r0 
	MOV 	r0, r1 

/** (7) tid = EE_std_run_task_code(tid); **/
	// Return value tid written to r0 where tid is supposed to be at start of the function
	BL 		EE_std_run_task_code

	// No specific value required at start of function for r3
	LDR 	r3, =EE_std_change_context


/** (8) goto begin; **/
 	MOV		pc, r3
	
skip_std_run_task: 


 	// Restore return address to original context
 	POP		{lr}

	// Return from function
	MOV		pc, lr
#endif /* __MULTI__ */