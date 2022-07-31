#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];
TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);
  EE_irq_disable();
  EE_assert(2, EE_irq_status()==1, 1);
  EE_irq_enable();
  EE_assert(3, EE_irq_status()==0, 2);
  TerminateTask();
}

/*
Does:
(1) Call EnableInterrupt() i.e. EE_irq_enable().
(2) Call DisableInterrupt() i.e. EE_irq_disable().
(3) Call GetInterruptDescriptor i.e. EE_irq_status().


Expects:
(1) All interrupts are enabled.
(2) All interrupts are disabled.
(3) We get the state of interrupts i.e. if they are disabled or enabled.

Note:
Those function do not have the same behaviour. But We want to test the Interrupt behaviour regardless.
Those function in proximity do the same as they enable/disable interrupts of give us information about
the state of interrupts.
*/
int main(void)
{  
  ActivateTask(Task1);
  
  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Interrupt Processing (1, 2, 3, 4, 5)", result, ASSERTIONS);
  return 0;
}