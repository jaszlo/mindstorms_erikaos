#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 6
unsigned int task1_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  StatusType ret = SetEvent(Task2, MyEvent); // Preempt and goto Task2
  EE_assert(5, ret==E_OK, 4);

  task1_finished = 1;
  TerminateTask();
}


TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task1);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = WaitEvent(MyEvent);
  EE_assert(3, ret1==E_OK, 2);

  EE_assert(4, task1_finished==0, 3);
  TerminateTask();
}

/*
Does:
Call SetEvent() from preemptive task on waiting extended task which is waiting 
for at least one of the requested events and has higher priority than running task.

Expect:
Requested events are set. Running task becomes ready(is preempted). Waiting task becomes running. Service returns E_OK
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Event Mechanism (6)", result, ASSERTIONS);
  
  return 0;
}