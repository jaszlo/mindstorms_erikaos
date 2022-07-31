#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 3
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

volatile int isr_fired = 0;

ISR2(timer_handler)
{
  isr_fired = 1;
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
  EE_assert(2, isr_fired==1, 1);

  TerminateTask();
}

/*
Does:
Interrupt of running task.

Expects:
Interrupt is executed.
*/
int main(void)
{
  const unsigned int channel = 2;
  const unsigned int period = 1000; // milliseconds 
  EE_timer_init(period, channel);
  EE_timer_start();

  ActivateTask(Task1);
  
  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Interrupt Processing (6)", result, ASSERTIONS);

  return 0;
}