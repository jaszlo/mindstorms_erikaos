#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 5
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret = CounterTick(MyCounter); // Should Preempt preempt
  EE_assert(3, ret==E_OK, 2);
  EE_assert(4, task2_finished==1, 3);

  TerminateTask(); 
}

TASK(Task2)
{
  task2_finished = 1;
  EE_assert(2, 1, 1);
  TerminateTask();
}

/*
Does:
Expiration of alarm which activates a task with higher priority than running task while running task is preemptive.

Expect:
Task is activated. Task with highest priority is executed.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Alarms (31)", result, ASSERTIONS);
  
  return 0;
}