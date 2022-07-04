#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 3
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];



TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret1 = ReleaseResource(MyResource);
  EE_assert(2, ret1==E_OS_NOFUNC, 1);

  TerminateTask(); 
}

/*
Does:
Call ReleaseResource() from task with resource which is not occupied.

Expect:
Service returns E_OS_NOFUNC
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Resource Management (12)", result, ASSERTIONS);
  
  return 0;
}