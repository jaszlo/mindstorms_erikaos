#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 10
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  StatusType ret0 = CounterTick(MyCounter); // Should not preempt
  EE_assert(3, ret0==E_OK, 2);
  EE_TID tmp;
  StatusType ret = GetTaskState(Task2, &tmp);
  EE_assert(4, ret==E_OK, 3);
  EE_assert(5, tmp==READY, 4);
  EE_assert(6, task2_finished==0, 5);

  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task1);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = WaitEvent(AlarmEvent); // Preempt
  EE_assert(7, ret1==E_OK, 6);

  EventMaskType mask;
  StatusType ret2 = GetEvent(Task2, &mask);
  EE_assert(8, ret2==E_OK, 7);
  EE_assert(9, (mask & AlarmEvent), 8);

  task2_finished = 1;
  TerminateTask();
}

/*
Does:
Expiration of alarm which sets an event while running task is non-preemptive. 
Task which owns the event is waiting for this event.

Expect:
Event is set. Task which is owner of the event becomes ready .No preemption of running task.
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);

  EE_assert_summarize("ECC1 Modistarc Alarms (34)", result, ASSERTIONS);
  
  return 0;
}