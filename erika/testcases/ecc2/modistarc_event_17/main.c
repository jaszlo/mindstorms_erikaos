#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 4
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task2) 
{
  EventMaskType mask;
  StatusType ret1 = GetEvent(Task1, &mask); // Task1 should be suspended

  EE_assert(3, ret1==E_OS_STATE, 2);

  task2_finished = 1;
  TerminateTask();
}

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);
  ActivateTask(Task2); // Do not preempt
  EE_assert(2, task2_finished==0, 1);
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
  EE_assert_summarize("ECC2 Modistarc Event Mechanism (17)", result, ASSERTIONS);
  
  return 0;
}