#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 6
unsigned int task1_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];


TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task2); // Do not preempt i.e. Task1 is Non-preemptable
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = WaitEvent(MyEvent); // Preempt to higher priority Task
  EE_assert(4, ret1==E_OK, 3);

  EE_assert(5, task1_finished==1, 4);
  TerminateTask();
}

TASK(Task2)
{
  StatusType ret = SetEvent(Task1, MyEvent); // Do NOT preempt as current Task has higher priority
  EE_assert(3, ret==E_OK, 2);

  task1_finished = 1;
  TerminateTask();
}


/*
Does:
Call SetEvent() from preemptive task on waiting extended task which is waiting 
for at least one of the requested events and has lower priority than running task.

Expect:
Requested events are set. Running task is not preempted. Waiting task becomes ready. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Event Mechanism (7)", result, ASSERTIONS);
  
  return 0;
}