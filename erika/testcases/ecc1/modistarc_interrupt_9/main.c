#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

volatile int isr_fired = 0;
volatile int task2_fired = 0;
ISR1(timer_handler)
{
  ActivateTask(Task2);
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
  EE_assert(3, task2_fired==0, 2);
  TerminateTask();
}


TASK(Task2)
{
  task2_fired = 1;
  TerminateTask();
}

/*
Does:
Return from ISR2 i.e. value 1 in OIL. Interrupted task is non-preemptive.

Expects:
Execution of interrupted task is continued.
*/
int main(void)
{
  const unsigned int channel = 2;
  const unsigned int period = 1000; // milliseconds 
  EE_timer_init(period, channel);
  EE_timer_start();
  
  ActivateTask(Task1);
  
  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Interrupt Processing (9)", result, ASSERTIONS);

  return 0;
}