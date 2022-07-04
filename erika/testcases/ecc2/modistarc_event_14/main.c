#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 8
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  EventMaskType mask;
  StatusType ret0 = SetEvent(Task1, MyEvent);
  
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = GetEvent(Task1, &mask);
  EE_assert(3, ret1==E_OK, 2);
  EE_assert(4, (MyEvent & mask), 3);

  StatusType ret2 = ClearEvent(MyEvent);
  EE_assert(5, ret2==E_OK, 4);


  StatusType ret3 = GetEvent(Task1, &mask);
  EE_assert(6, ret3==E_OK, 5);
  EE_assert(7, ~(MyEvent & mask), 6);

  TerminateTask();  
}
/*
Does:
Call ClearEvent() from extended task.

Expect:
Requested events are cleared. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Event Mechanism (14)", result, ASSERTIONS);
  
  return 0;
}