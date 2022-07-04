#include "ee.h"
#include "test/assert/inc/ee_assert.h"

unsigned int task2_started;
#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret = ActivateTask(Task2);

  EE_assert(2, (ret==E_OK), 1);

  EE_assert(3, (task2_started==1), 1);
  TerminateTask(); 
}

TASK(Task2)
{
  task2_started = 1;
  TerminateTask();
}

/*
Does:
Call ActivateTask() from preemptive task on suspended basic task which has higher priority than running task

Expect:
Running task is preempted. Activated task becomes running. Service returns E_OK
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Task Management (3)", result, ASSERTIONS);

  return 0;
}