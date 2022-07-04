#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 7
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  StatusType ret = ChainTask(Task2);
  EE_assert(3, ret==E_OS_LIMIT, 2);

  CounterTick(Counter1);

  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task1);
  EE_assert(2, ret0==E_OK, 1);

  EventMaskType mask;
  
  while(1) {
    StatusType ret1 = WaitEvent(TimerEvent);
    EE_assert(4, ret1==E_OK, 3);

    StatusType ret2 = GetEvent(Task2, &mask);
    EE_assert(5, ret2==E_OK, 4);

    if (mask & TimerEvent) {
        StatusType ret3 = ClearEvent(TimerEvent);
        EE_assert(6, ret3==E_OK, 4);
        break;  
      }
  }

  TerminateTask();
}

/*
Does:
Call ChainTask() on waiting extended task

Expect:
Service returns E_OS_LIMIT
*/
int main(void)
{
  ActivateTask(Task2);

   unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Task Management (33)", result, ASSERTIONS);

  return 0;
}