#include "ee.h"
#include "test/assert/inc/ee_assert.h"

unsigned int reached = 0;
unsigned int task2_finished = 0;

#define ASSERTIONS 5
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task3)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task2);
  EE_assert(2, ret0==E_OK, 1);

  ChainTask(Task1);
  reached = 1;
  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(3, reached==0, 2);
  task2_finished = 1;
  TerminateTask();
}


TASK(Task1)
{
  EE_assert(4, task2_finished==1, 3);
  TerminateTask();
}
/*
Does:
Call ChainTask() on suspended task

Expect:
Running task is terminated, chained task becomes ready and ready task with highest priority is executed
*/
int main(void)
{
  ActivateTask(Task3);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Task Management (28)", result, ASSERTIONS);

  return 0;
}