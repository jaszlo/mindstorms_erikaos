#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 3
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1) // Extended
{
  TerminateTask();
}

TASK(Task2) // Basic
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret = SetEvent(Task1, MyEvent);
  EE_assert(2, ret==E_OS_STATE, 1);

  TerminateTask();
}
/*
Does:
Call SetEvent() for suspended extended task

Expect:
Service returns E_OS_STATE
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Event Mechanism (3)", result, ASSERTIONS);
  
  return 0;
}