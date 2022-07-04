#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 5
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(4, task2_finished==1, 3);
  TerminateTask();  
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task1);
  EE_assert(2, ret0==E_OK, 1);

  EventMaskType mask;
  StatusType ret1 = GetEvent(Task1, &mask);
  EE_assert(3, ret1==E_OK, 2);

  task2_finished = 1;
  TerminateTask();
}

/*
Does:
all GetEvent() for ready extended task.

Expect:
Return current state of all event bits. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Event Mechanism (19)", result, ASSERTIONS);
  
  return 0;
}