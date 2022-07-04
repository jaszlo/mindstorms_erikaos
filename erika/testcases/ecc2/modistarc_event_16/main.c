#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task2) 
{
  TerminateTask();
}

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  EventMaskType mask;
  StatusType ret1 = GetEvent(Task2, &mask);
  EE_assert(2, ret1==E_OS_ACCESS, 1);
  EE_assert(3, ~(MyEvent & mask), 2);

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
  EE_assert_summarize("ECC2 Modistarc Event Mechanism (16)", result, ASSERTIONS);
  
  return 0;
}