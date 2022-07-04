#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 5
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task2)
{
  StatusType ret = GetResource(MyResource); // Resource allready taken
  EE_assert(3, ret==E_OS_ACCESS, 2);
  TerminateTask();
}

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);


  StatusType ret0 = GetResource(MyResource);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = ActivateTask(Task2); // Preempt
  EE_assert(4, ret1==E_OK, 3);

  StatusType ret2 = ReleaseResource(MyResource);
  EE_assert(5, ret2==E_OK, 4);

  TerminateTask(); 
}

/*
Does:
Call GetResource() from task which has no access to this resource.

Expect:
Service returns E_OS_ACCESS
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC1 Modistarc Resource Management (1)", result, ASSERTIONS);
  
  return 0;
}