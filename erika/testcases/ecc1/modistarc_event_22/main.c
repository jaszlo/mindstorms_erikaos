#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 5
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];



TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = GetResource(MyResource);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = WaitEvent(MyEvent); 
  EE_assert(3, ret1==E_OS_RESOURCE, 2);

  StatusType ret2 = ReleaseResource(MyResource);
  EE_assert(4, ret2==E_OK, 3);
  TerminateTask();
}

/*
Does:
Call WaitEvent() from extended task which occupies a resource.
Expect:
Service returns E_OS_ACCESS.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Event Mechanism (22)", result, ASSERTIONS);
  
  return 0;
}