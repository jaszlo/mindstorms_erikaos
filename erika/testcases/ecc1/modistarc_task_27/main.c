#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 5
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];


TASK(Task1) 
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret1 = GetResource(MyResource);
  EE_assert(2, ret1==E_OK, 1);

  StatusType ret2 = TerminateTask();
  EE_assert(3, ret2==E_OS_RESOURCE, 2);

  StatusType ret3 = ReleaseResource(MyResource);
  EE_assert(4, ret3==E_OK, 3);

  TerminateTask();
}

TASK(Task2)
{
  TerminateTask();
}

/*
Does:
Call ChainTask() while still occupying a resource.

Expect:
Running task is not terminated. Service returns E_OS_RESOURCE.
*/
int main(void)
{
  ActivateTask(Task1);
  
  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Task Management (27)", result, ASSERTIONS);

  return 0;
}