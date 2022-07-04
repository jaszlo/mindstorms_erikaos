#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 11
unsigned int task1_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  StatusType ret1 = SetEvent(Task2, IgnoredEvent);
  EE_assert(3, ret1==E_OK, 2);

  EE_TID tmp;
  StatusType ret = GetTaskState(Task2, &tmp);
  
  EE_assert(4, ret==E_OK, 3);
  EE_assert(5, tmp==WAITING, 4);
  
  StatusType ret0 = SetEvent(Task2, MyEvent);
  EE_assert(6, ret0==E_OK, 5);

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
    EE_assert(7, ret1==E_OK, 6);

    StatusType ret2 = GetEvent(Task2, &mask);
    EE_assert(8, ret2==E_OK, 7);

    if (mask & MyEvent) 
    {
      StatusType ret3 = ClearEvent(MyEvent);
      EE_assert(9, ret3==E_OK, 8);
      break;  
    }
  }

  EE_assert(10, task1_finished==1, 9);

  TerminateTask();
}
/*
Does:
Call SetEvent() from non-preemptive task on waiting extended task which is not waiting for any of the requested events

Expect:
Requested events are set. Running task is not preempted. Waiting task doesn’t become ready. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Event Mechanism (5)", result, ASSERTIONS);
  
  return 0;
}