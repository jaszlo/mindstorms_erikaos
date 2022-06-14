#include "eecfg.h"

#include "cpu/arm9/inc/modes.h"

// Export
.global	EE_arm9_hal_ready2stacked

#ifdef __MULTI__
.global EE_arm9_hal_stkchange
// Import
.extern	EE_arm9_system_tos
.extern	EE_arm9_active_tos
#endif
.extern	EE_thread_end_instance
.extern	EE_std_run_task_code
.extern irq_enable
.extern irq_disable

			
.section .text

/**
 * void EE_std_change_context( EE_TID tid )
 * 	r0 = tid
 *
 *  Pseudo code for EE_std_change_context in multistack environment:
 *  begin:
 *    tos_index = EE_std_thread_tos[tid+1];
 *    if is_not_the_current_stack(tos_index) {
 *       save_caller_saved_registers();
 *       switch_stacks(tos_index);
 *       restore_caller_saved_registers();
 *    }
 *    if (is_not_marked_stacked(tid)) {
 *       tid = EE_std_run_task_code(tid);
 *        goto begin;
 *    }
 *
 *  Please notice that the "goto begin" is actually a recursive call to
 *  EE_std_change_context_multi(), but in this way there is no stack growing.
 *
 *  For processors where the return address is saved in a register, that
 *  register must be saved in the stack too.
 *
 *  switch_stacks() should also update EE_hal_active_tos.
 */
	.global	EE_std_change_context
EE_std_change_context:
	


#ifdef __MULTI__
// 
// This code is called when we have to change the thread stack
// NOTE: r1 MUST contain tos_index, while r0 (the thread address)
// will be unchanged!!!
//
EE_arm9_change_tos:	
	// If tos_index == EE_arm9_active_tos then we do not have to switch stack
	LDR	r2, =EE_arm9_active_tos
	LDR	r3, [r2]

	CMP	r3, r1
	MOVEQ	pc, lr

	// Before changing the stack, we have to save the registers
	// that could be modified (i.e. all the registers that should
	// be preserved through function calls). Note that if there is
	// not the stack change, the system will behave like the
	// monostack version of the kernel
 	STMFD	sp!, {r4-r11}

	// from now until the LDMFD I can use r0-r11 as scratch!
	// r2=&EE_arm9_active_tos
	// r4=&EE_arm9_system_tos
	
	//
	// Save current TOS
	//
	// r4 = &EE_arm9_system_tos
	LDR	r4, =EE_arm9_system_tos
	// r3 = & EE_arm9_system_tos[EE_arm9_active_tos].SYS_tos
	ADD	r3, r4, r3, LSL#2

	// EE_arm9_system_tos[EE_arm9_active_tos].SYS_tos = sp_SYS
	STR	sp, [r3]

	//
	// New current TOS
	//
	// remember that r4 = &EE_arm9_system_tos
	// r3 = & EE_arm9_system_tos[tos_index].SYS_tos
	ADD	r3, r4, r1, LSL#2

	// sp_SYS = EE_arm9_system_tos[tos_index].SYS_tos
	LDR	sp, [r3]
	
	//
	// Update arm9_active_tos (= tos_index)
	//
	// remember that r2=&EE_arm9_active_tos
	STR	r1, [r2]

	// Here we have to restore the registers saved before the
	// stack previous change. If this is the first time we use the
	// current stack, restoring is useless.
 	LDMFD	sp!, {r4-r11}
	
	MOV	pc, lr

	
	
//
// MONO:  not defined
// MULTI: void EE_arm9_hal_stkchange(EE_UREG 0, EE_UREG tos_index)
//
// Typically called into a generic primitive to implement a blocking
// synchronization primitive.
//

EE_arm9_hal_stkchange:  
        
        // Mk: saving lr here and restoring it after EE_arm9_change_tos is mandatory, in order to
        // save lr of the preempted thread and to restore lr of the preempter thread
        //      from their respective stacks!
        STMFD   sp!, {lr}

        // switch to the TOS of the new thread
        BL      EE_arm9_change_tos

        // now the stack is changed, and we need to return to the interrupted thread!
        LDMFD   sp!, {lr}
        BX      lr
        

#endif // __MULTI__

	
//
// MONO:  void EE_arm9_hal_ready2stacked(ADDR thread_addr)
// MULTI: void EE_arm9_hal_ready2stacked(ADDR thread_addr, EE_UREG tos_index)
//
// Typically called into a generic primitive to implement preemption.
//
EE_arm9_hal_ready2stacked:	
	// We have to save LR into the stack (APCS standard)
 	STMFD	sp!, {lr}
1:	
#ifdef __MULTI__
	// Switch Stack if required to stack of new Task
	BL	EE_arm9_change_tos
#endif

	bl irq_enable

	// Jump to the preempter thread (r0 = first parameter)
	MOV	lr, pc
	BX	r0

	// EE_thread_end_instance() requires interrupts to be disabled
	bl irq_disable
		
	// Call to Scheduler 
	BL	EE_thread_end_instance
	
	/**
	 * if EE_hal_endcycle_next_thread == 0
	 *   then wake up the preempted thread
	 *   (EE_arm9_hal_endcycle_stacked executed)
	 *
	 * if EE_hal_endcycle_next_thread != 0
	 *   then activate a new thread
	 *   (EE_arm9_hal_endcycle_ready executed)
	 */
#ifdef __MULTI__
	LDR	r2, =EE_hal_endcycle_next_tos
	LDR	r1, [r2]
#endif
	
	LDR	r2, =EE_hal_endcycle_next_thread
	LDR	r0, [r2]

	// Check if next_thread was actually set if not redo from start
	CMP	r0, #0
	BNE	1b
	// Switch Stack if required to stack of preempted Task
#ifdef __MULTI__
	BL	EE_arm9_change_tos
#endif
	// Keep interrupts disabled as this will return into a primitiv that requires it or IRQ handler
	LDMFD	sp!, {lr}
	BX	lr