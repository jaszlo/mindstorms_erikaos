#ifndef __INCLUDE_ARM9_IRQ_H__
#define __INCLUDE_ARM9_IRQ_H__

/* Use angled parenthesis to include the main "ee_internal.h" */
#include "cpu/arm9/inc/ee_cpu.h"

#ifdef __AM1808__
#include "mcu/am1808/inc/interrupt.h"
#endif /*__AM1808__ */
#ifdef __VERSATILEPB__
#include "mcu/versatilepb/inc/interrupt.h"
#endif /* __VERSATILEPB__ */

#ifdef __ALLOW_NESTED_IRQ__ // Not supported with current irq handler
#endif /* end __ALLOW_NESTED_IRQ__*/




#if defined(__MULTI__) && defined(__IRQ_STACK_NEEDED__)
// Not supported yet
#endif /* end __MULTI__ && __IRQ_STACK_NEEDED__*/

// Enable/Disable of IRQ is done implicitly by CPU
#define EE_ISR2_prestub(void) 	\
	//irq_disable();							
	/** TODO for nested IRQ
	 * (1) Store current IRQ priority. Softwarestack probably 
	 * (2) Set the new IRQ priority in hardware 
	 * (3) Handle the new IRQ.
	 */

#ifdef __AM1808__							
#define EE_ISR2_poststub(void) 					\
	irq_clear_status(irq_get_current_num()); 	
#endif 	/* __AM1808__ */
#ifdef __VERSATILEPB__
#define EE_ISR2_poststub(void) 
#endif /* __VERSATILEPB__ */						
  	/*irq_enable()*/;							
	/** TODO for nested IRQ
	 * 	(1) Restore previous IRQ priority if there is one
	 *  (2) Set the restored IRQ priority in hardware
	 */

#define ISR1(f)          \
	void ISR1_##f(void); \
	__IRQ void f(void)   \
	{                    \
		ISR1_##f();      \
	}                    \
	void ISR1_##f(void)


#define ISR2(f)				\
void ISR2_ ## f(void);		\
void f(void) 				\
{				       		\
	EE_ISR2_prestub(); 		\
	ISR2_ ## f();			\
	EE_ISR2_poststub();		\
}							\
void ISR2_ ## f(void)

/* Standard Macro to declare an ISR (2) */
#define ISR(f) ISR2(f)

#endif /* __INCLUDE_ARM9_IRQ_H__ */
