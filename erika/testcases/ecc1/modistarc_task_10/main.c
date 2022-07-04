#include "ee.h"
#include "test/assert/inc/ee_assert.h"

unsigned int task1_started;
#define ASSERTIONS 5
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  task1_started = 1;
  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret1 = ActivateTask(Task1);
  EE_assert(2, (ret1==E_OK), 1);

  StatusType ret2 = ActivateTask(Task1);
  EE_assert(3, (ret2==E_OS_LIMIT), 1);

  EE_assert(4, (task1_started==0), 1);

  TerminateTask();
}

/*
Does:
Call ActivateTask() on ready extended task

Expect:
Service returns E_OS_LIMIT
*/
int main(void)
{
  ActivateTask(Task2);

   unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Task Management (10)", result, ASSERTIONS);

  return 0;
}