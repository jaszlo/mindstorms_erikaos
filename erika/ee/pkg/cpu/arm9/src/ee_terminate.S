
#include "cpu/arm9/inc/internal/modes.h"

.global	EE_arm9_terminate_task
.global EE_arm9_terminate_savestk
	
.section .text

	
	// r0 = &terminate_data[t]
	// r1 = terminate_real_th_body[t]()
EE_arm9_terminate_savestk:
	// save some registers:	
	// - r0-r3 do not need to be saved 9 they are already dirty
	//   with the call to this function;
	// - r4-r11 have to be saved because they maybe contain some
	//   data of the preempted threads
	// - r12 has to be saved because it is not guaranteed that the value
	//   will remain the same after we return from the TerminateTask
	// - lr has to be saved to be able to jump back to the thread final }
	//   in the thread stub into tstub.h
	// - only the data from the System level have to be saved, the others
	//   will be restored when needed directly by the prempter 
	//   threads/irqs
	//
	// Please note that the interrupt are ENABLED
	STMFD	sp!, {r4-r12,lr}
	
	// save sp_sys in terminate_data[t]
	STR sp, [r0]
	
	// jmp terminate_real_th_body[t]
	BX r1

	mov r0, #0xb00
	bl put_ptr

	// r0 = &terminate_data[t]
EE_arm9_terminate_task:
	// reload sp_sys from terminate_data[t]	
	LDR sp, [r0]
	// reload the registers saved before
	LDMFD	sp!, {r4-r12,lr}
	// return back to the caller (in tstub.c!!!)
	BX lr

