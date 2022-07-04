#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 7
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret = ActivateTask(Task2); // Preempt
  EE_assert(5, ret==E_OK, 4);

  EE_assert(6, task2_finished==1, 5);

  TerminateTask(); 
}

TASK(Task2)
{
  StatusType ret0 = CounterTick(MyCounter); // Should set event
  EE_assert(2, ret0==E_OK, 1);

  EventMaskType mask;
  StatusType ret1 = GetEvent(Task2, &mask);
  EE_assert(3, ret1==E_OK, 2);
  EE_assert(4, (mask & AlarmEvent), 3);

  task2_finished = 1;
  TerminateTask();
}

/*
Does:
Expiration of alarm which sets an event while running task is non-preemptive. 
Task which owns the event is not waiting for this event and not suspended.

Expect:
Event is set.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Alarms (35)", result, ASSERTIONS);
  
  return 0;
}