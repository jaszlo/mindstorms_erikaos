#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define INVALID_RESOURCE_ID 1234

#define ASSERTIONS 3
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];


TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret1 = ReleaseResource(INVALID_RESOURCE_ID);
  EE_assert(2, ret1==E_OS_ID, 1);

  TerminateTask(); 
}

/*
Does:
Call ReleaseResource() from task with invalid resource ID.

Expect:
Service returns E_OS_ID.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Resource Management (9)", result, ASSERTIONS);
  
  return 0;
}