#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 3
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1) // Extended
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret = SetEvent(Task2, MyEvent);
  EE_assert(2, ret==E_OS_ACCESS, 1);

  TerminateTask(); 
}

TASK(Task2) // Basic
{
  TerminateTask();
}
/*
Does:
Call SetEvent() for basic task

Expect:
Service returns E_OS_ACCESS
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Event Mechanism (2)", result, ASSERTIONS);
  
  return 0;
}