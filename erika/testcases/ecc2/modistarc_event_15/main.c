#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define INVALID_TASK_ID 1234
#define ASSERTIONS 5
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  EventMaskType mask;
  StatusType ret0 = SetEvent(INVALID_TASK_ID, MyEvent);
  
  EE_assert(2, ret0==E_OS_ID, 1);

  StatusType ret1 = GetEvent(Task1, &mask);
  EE_assert(3, ret1==E_OK, 2);
  EE_assert(4, ~(MyEvent & mask), 3);

  TerminateTask();  
}
/*
Does:
Call GetEvent() with invalid Task ID.

Expect:
Service returns E_OS_ID.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Event Mechanism (15)", result, ASSERTIONS);
  
  return 0;
}