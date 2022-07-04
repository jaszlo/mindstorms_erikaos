#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret1 = ActivateTask(Task1);
  EE_assert(2, ret1==E_OK, 1);

  StatusType ret2 = ActivateTask(Task1);
  EE_assert(3, ret2==E_OS_LIMIT, 1);

  TerminateTask();
}

/*
Does:
Call ActivateTask() from task level with invalid task ID (task does not exist)

Expect:
Service returns E_OS_ID
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC1 Modistarc Task Management (11)", result, ASSERTIONS);
  
  return 0;
}