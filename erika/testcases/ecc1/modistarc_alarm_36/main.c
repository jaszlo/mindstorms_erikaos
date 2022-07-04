#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 6
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(3, 1, 2);
  StatusType ret0 = CounterTick(MyCounter); // Set event therefore preempt
  EE_assert(5, ret0==E_OK, 4);
  EE_assert(6, task2_finished==1, 5);
  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task1);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = WaitEvent(AlarmEvent); // Preempt
  EE_assert(4, ret1==E_OK, 3);
  task2_finished = 1;
  TerminateTask();
}

/*
Does:
Expiration of alarm which sets an event while running task is preemptive. 
Task which owns the event is waiting for this event.

Expect:
Event is set. Task which is owner of the event becomes ready. 
Task with highest priority is executed (Rescheduling).
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Alarms (36)", result, ASSERTIONS);
  
  return 0;
}