#include "ee.h"
#include "test/assert/inc/ee_assert.h"

unsigned int task2_started;
#define ASSERTIONS 7
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  
  EE_assert(1, 1, EE_ASSERT_NIL);

  CounterTick(Counter1); // Should activate TimerEvent but should be cleared for Task1 after ActivateTask

  StatusType ret0 = ActivateTask(Task2); // Start Task2
  EE_assert(5, ret0==E_OK, 4);

  // Check that task was preempted
  EE_assert(6, task2_started==1, 5);

  TerminateTask();
}

TASK(Task2)
{
  task2_started = 1;

  EventMaskType mask;
  StatusType ret0 = GetEvent(Task1, &mask);
  EE_assert(2, ret0==E_OK, 1);

  // Check if event was cleared
  unsigned int event1 = mask & TimerEvent;
  StatusType ret1 = ClearEvent(TimerEvent);
  EE_assert(3, ret1==E_OK, 2);
  unsigned int event2 = mask & TimerEvent;

  EE_assert(4, event1==event2, 3);

  TerminateTask(); 
}


/*
Does:
Call ActivateTask() from preemptive task on suspended extended task which has higher priority than running task

Expect:
Running task is preempted. Activated task becomes running and its events are cleared. Service returns E_OK
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Task Management (7)", result, ASSERTIONS);

  return 0;
}