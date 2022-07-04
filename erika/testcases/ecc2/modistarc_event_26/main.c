#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 6
unsigned int task1_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  task1_finished = 1;
  TerminateTask();
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = SetEvent(Task2, MyEvent);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = ActivateTask(Task1); 
  EE_assert(3, ret1==E_OK, 2);

  StatusType ret2 = WaitEvent(MyEvent); // No preemption
  EE_assert(4, ret2==E_OK, 3);
  EE_assert(5, task1_finished==0, 4);

  TerminateTask();
}


/*
Does:
Call WaitEvent() from extended task. At least one event waited for is already set.

Expects:
No preemption of running task. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Event Mechanism (26)", result, ASSERTIONS);

  return 0;
}