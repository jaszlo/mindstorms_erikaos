#include "ee.h"
#include "test/assert/inc/ee_assert.h"

unsigned int task1_started;
#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  task1_started = 1;
  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret = ActivateTask(Task1);
  EE_assert(2, (ret==E_OK), 1);

  EE_assert(3, (task1_started==0), 1);
  
  TerminateTask();
}


/*
Does:
Call ActivateTask() from non-preemptive task on suspended basic task

Expect:
No preemption of running task. Activated task becomes ready. Service returns E_OK
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Task Management (2)", result, ASSERTIONS);

  return 0;
}