#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 4
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret = CounterTick(MyCounter); // Should not preempt
  EE_assert(2, ret==E_OK, 1);
  EE_assert(3, task2_finished==0, 2);

  TerminateTask(); 
}

TASK(Task2)
{
  task2_finished = 1;
  EE_assert(4, 1, 3);
  TerminateTask();
}

/*
Does:
Expiration of alarm which activates a task while running task is non-preemptive.

Expect:
Task is activated. No preemption of running task.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Alarms (30)", result, ASSERTIONS);
  
  return 0;
}