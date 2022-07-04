#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 5
unsigned int task1_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];


TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);
  StatusType ret0 = ActivateTask(Task2); // Preempt and goto Task2
  EE_assert(5, ret0==E_OK, 4);

  EE_assert(6, task1_finished==1, 5);
  TerminateTask();
}

TASK(Task2)
{
  StatusType ret0 = SetEvent(Task1, MyEvent); // Do NOT preempt as Task1 is ready but not waiting and has lower priority
  EE_assert(2, ret0==E_OK, 1);
  
  EE_TID tmp;
  StatusType ret1 = GetTaskState(Task1, &tmp);

  EE_assert(3, ret1==E_OK, 2);
  EE_assert(4, tmp==READY, 3);

  task1_finished = 1;
  TerminateTask();
}


/*
Does:
Call SetEvent() from non-preemptive task on ready extended task

Expect:
Requested events are set. Running task is not preempted. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Event Mechanism (9)", result, ASSERTIONS);
  
  return 0;
}