#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 3
volatile unsigned int isr_fired = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];



ISR1(timer_handler)
{
  isr_fired = 1;
  EE_timer_clear_irq_flags();
  EE_timer_stop();

  StatusType ret = ClearEvent(MyEvent);
  EE_assert(2, ret==E_OS_CALLEVEL, 1);

}

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);
  
  while(1)
  {
    if(isr_fired == 1)
    {
      break;
    }
  }

  TerminateTask();
}



/*
Does:
Call Call ClearEvent() from ISR category 2  i.e. value 1 in OIL.

Expect:
Service returns E_OS_CALLEVEL.
*/
int main(void)
{

  const unsigned int channel = 2;
  const unsigned int period = 0x100000; 

  EE_timer_init(period, channel);
  EE_timer_start();

  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Event Mechanism (12)", result, ASSERTIONS);
  
  return 0;
}