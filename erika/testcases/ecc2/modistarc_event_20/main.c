#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 6
unsigned int task1_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);
 
  StatusType ret0 = ActivateTask(Task1);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = WaitEvent(MyEvent); // Preempt
  EE_assert(4, task1_finished==0, 3);
  TerminateTask();  
}

TASK(Task1)
{
  EventMaskType mask;
  StatusType ret1 = GetEvent(Task2, &mask);
  EE_assert(3, ret1==E_OK, 2);

  StatusType ret2 = SetEvent(Task2, MyEvent); // Preempt
  EE_assert(5, ret2==E_OK, 4);

  task1_finished = 1;
  TerminateTask();
}

/*
Does:
Call GetEvent() for waiting extended task.

Expect:
Return current state of all event bits. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Event Mechanism (20)", result, ASSERTIONS);
  
  return 0;
}