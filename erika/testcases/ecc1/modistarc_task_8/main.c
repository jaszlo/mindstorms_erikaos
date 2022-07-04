#include "ee.h"
#include "test/assert/inc/ee_assert.h"

unsigned int task2_started;
#define ASSERTIONS 7
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  task2_started = 1;
  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  CounterTick(Counter1); // Should activate TimerEvent but should be cleared for Task1 after ActivateTask

  StatusType ret0 = ActivateTask(Task1); // Task2 only ready
  EE_assert(2, ret0==E_OK, 1);

  // Check that task was not preempted
  EE_assert(3, task2_started==0, 2);

  EventMaskType mask;
  StatusType ret1 = GetEvent(Task1, &mask);
  EE_assert(4, ret1==E_OK, 3);

  // Check if event was cleared
  unsigned int event1 = mask & TimerEvent;
  StatusType ret2 = ClearEvent(TimerEvent);
  EE_assert(5, ret2==E_OK, 4);
  unsigned int event2 = mask & TimerEvent;
  EE_assert(6, event1==event2, 5);

  TerminateTask();
}


/*
Does:
Call ActivateTask() from preemptive task on suspended extended task which has lower priority than running task.

Expect:
No preemption of running task. Activated task becomes ready and its events are cleared. Service returns E_OK
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Task Management (8)", result, ASSERTIONS);

  return 0;
}