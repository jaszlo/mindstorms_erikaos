#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

volatile int isr_fired = 0;

ISR2(timer_handler)
{
  isr_fired = 1;

  StatusType ret = WaitEvent(MyEvent);
  EE_assert(2, ret=E_OS_CALLEVEL, 1);

  EE_timer_clear_irq_flags();
  EE_timer_stop();
}


TASK(Task1) 
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  while(1) 
  {
    if (isr_fired == 1)
    {
      break;
    }
  } 
  EE_assert(3, isr_fired==1, 2);

  TerminateTask();
}

/*
Does:
Call WaitEvent() from ISR category 3 i.e. value 2 in OIL

Expects:
Service returns E_OS_CALLEVEL
*/
int main(void)
{
  const unsigned int channel = 2;
  const unsigned int period = 1000; // milliseconds 
  EE_timer_init(period, channel);
  EE_timer_start();
  
  ActivateTask(Task1);
  
  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Event Mechanism (24)", result, ASSERTIONS);

  return 0;
}