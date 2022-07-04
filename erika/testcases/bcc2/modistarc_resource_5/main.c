#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 5
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];


TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);


  StatusType ret0 = GetResource(MyResource);
  EE_assert(2, ret0==E_OK, 1);


  StatusType ret1 = GetResource(MyResource);
  EE_assert(3, ret1==E_OS_ACCESS, 2); // This should return E_OS_LIMIT!

  StatusType ret2 = ReleaseResource(MyResource);
  EE_assert(4, ret2==E_OK, 3);

  TerminateTask(); 
}

/*
Does:
Call GetResource() from task with too many resources occupied in parallel.


Expect:
Service returns E_OS_LIMIT
Note:

GetResource vor ErikaOS v.2 NEVER return E_OS_LIMIT. Therefore this test can only fail if we test modistarc conform.
We Check for the value that is returned by ErikaOS or this test would never be able to pass unless we modify the kernel.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Resource Management (5)", result, ASSERTIONS);
  
  return 0;
}