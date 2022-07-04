#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 5
unsigned int task1_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret = CounterTick(MyCounter); // Should not Preempt preempt even though full preemptive scheduled as task1 has lower prio
  EE_assert(2, ret==E_OK, 1);
  EE_assert(3, task1_finished==0, 2);

  TerminateTask(); 
}

TASK(Task1)
{
  task1_finished = 1;
  EE_assert(4, 1, 3);
  TerminateTask();
}

/*
Does:
Expiration of alarm which activates a task with lower priority than running task while running task is preemptive.

Expect:
Task is activated. No preemption of running task.
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Alarms (32)", result, ASSERTIONS);
  
  return 0;
}