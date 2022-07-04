#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 9
unsigned int task2_finished = 0;
unsigned int task1_finished = 0;
volatile int isr_fired = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];


ISR2(timer_handler)
{
  EE_timer_clear_irq_flags();
  
  if (task2_finished == 1)
  {
    EE_assert(4, task1_finished==0, 3);

    StatusType ret = SetEvent(Task3, MyEvent);
    EE_assert(5, ret==E_OK, 4);

    EE_timer_stop();
    isr_fired = 1;
  }
}

// We require this Task to fall back to from Task2 after we started the timer or else we will go back to main
TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret = ActivateTask(Task3); // Preempt
  // Task 3 will WaitEvent and preemptto Task2. After that is finished we will go back here
  EE_assert(3, ret==E_OK, 2);

  EE_irq_enable();
  while(isr_fired == 0) {} // Wait for timer intterupt

  task1_finished = 1;
  TerminateTask();
}

TASK(Task2)
{
  task2_finished = 1;
  EE_timer_start();
  TerminateTask();
}


TASK(Task3) 
{ 
  StatusType ret0 = ActivateTask(Task2);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = WaitEvent(MyEvent); // Should hold out until event set
  EE_assert(6, ret1==E_OK, 5);
  EE_assert(7, task1_finished==0, 6);
  EE_assert(8, isr_fired==1, 7);
  TerminateTask();
}

/*
Does:
Call WaitEvent() from extended task. None of the events waited for is set
Note:
Slitghtly edited to terminate instead of endlessly waiting for event that will never be set!

Expects:
Running task becomes waiting and ready task with highest priority is executed. Service returns E_OK
*/
int main(void)
{
  
  const unsigned int channel = 2;
  const unsigned int period = 0x500000; 
  EE_timer_init(period, channel);
  
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Event Mechanism (25)", result, ASSERTIONS);

  return 0;
}