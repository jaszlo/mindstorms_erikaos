#include "ee.h"
#include "test/assert/inc/ee_assert.h"

unsigned int reached = 0;
unsigned int task1_finished = 0;

#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  if (task1_finished == 0) // To prevent endless recursion!
  {
    EE_assert(1, 1, EE_ASSERT_NIL);

    StatusType ret0 = ActivateTask(Task2);
    EE_assert(2, ret0==E_OK, 1);

    ChainTask(Task1);
    reached = 1;
  } else {
    TerminateTask();
  }
}

TASK(Task2)
{
  EE_assert(3, reached==0, 2);
  task1_finished = 1;
  TerminateTask();
}

/*
Does:
Call ChainTask() on running task

Expect:
Running task is terminated, chained task becomes ready and ready task with highest priority is executed
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Task Management (29)", result, ASSERTIONS);

  return 0;
}