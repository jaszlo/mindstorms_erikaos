// Export
.global	EE_arm9_terminate_task
.global EE_arm9_terminate_savestk
// Import
.globl context_storage
.globl print_context
.section .text

/** Call EE_arm9_terminate_savestk(&EE_terminate_data[t], (EE_ADDR)EE_terminate_real_th_body[t], t);
 *		r0 = &terminate_data[t]
 *		r1 = terminate_real_th_body[t]()
 */
EE_arm9_terminate_savestk:
	/** Save required Registers:	
	  *   r0-r3 do not need to be saved as they are already dirty with the call to this function.
	  *   
	  *	  r4-r11 have to be saved because they may contain some data of the preempted threads.
	  *
	  *   r12 has to be saved because it is not guaranteed that the value
	  *   will remain the same after we return from the TerminateTask.
	  * 
	  *   lr has to be saved to be able to jump back to the thread final
	  *   in the thread stub into tstub.h
	  */
	// Store current context at current stack location and also write back to sp
	STMFD	sp!, {r4-r12,lr}
	
	// Store sp in terminate_data to restore current context when terminating task
	STR sp, [r0]
	
	//push {r0-r12, lr}
	//bl print_terminate_data
	//pop {r0-r12, lr}

	// Jump to Task function body
	BX r1
	
/**
 *  EE_arm9_terminate_task(&EE_terminate_data[t]);
 * 		r0 = &terminate_data[t]
 */
EE_arm9_terminate_task:

	//push {r0-r12, lr}
	//bl print_terminate_data
	//pop {r0-r12, lr}


	// Reload sp from terminate_data[t]
	LDR sp, [r0]

	// Restore context from initial sp 
	LDMFD	sp!, {r4-r12,lr}

	// Return back to the caller (in tstub.c!!!)
	BX lr

