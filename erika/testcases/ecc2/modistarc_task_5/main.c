#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 6
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task2);
  EE_assert(2, ret0==E_OK, 1);
  EE_assert(3, task2_finished==0, 2);

  EE_TID tmp;
  StatusType ret1 = GetTaskState(Task2, &tmp);
  EE_assert(4, ret1==E_OK, 3);
  EE_assert(5, tmp==READY, 4);

  TerminateTask(); 
}

TASK(Task2)
{
  task2_finished = 1;
  TerminateTask();
}

/*
Does:
Call ActivateTask() from preemptive task on suspended basic task which has equal priority as running task.

Expect:
No preemption of running task. Activated task becomes ready. Service return E_OK.
*/
int main(void)
{
  ActivateTask(Task1);
  EE_assert(6, task2_finished==1, 5);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Task Management (5)", result, ASSERTIONS);
  
  return 0;
}