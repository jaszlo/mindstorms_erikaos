#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 8
unsigned int task1_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  StatusType ret = SetEvent(Task2, MyEvent);
  EE_assert(3, ret==E_OK, 2);

  task1_finished = 1;
  TerminateTask();
}


TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task1);
  EE_assert(2, ret0==E_OK, 1);

  EventMaskType mask;
  
  while(1) 
  {
    StatusType ret1 = WaitEvent(MyEvent);
    EE_assert(4, ret1==E_OK, 3);

    StatusType ret2 = GetEvent(Task2, &mask);
    EE_assert(5, ret2==E_OK, 4);

    if (mask & MyEvent) 
    {
      StatusType ret3 = ClearEvent(MyEvent);
      EE_assert(6, ret3==E_OK, 5);
      break;  
    }
  }

  EE_assert(7, task1_finished==1, 6);

  TerminateTask();
}
/*
Does:
Call SetEvent() from non-preemptive task on waiting extended task which is waiting for at least one of the requested events

Expect:
Requested events are set. Running task is not preempted. Waiting task becomes ready. Service returns E_OK
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Event Mechanism (4)", result, ASSERTIONS);
  
  return 0;
}