#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  EE_TID tmp;
  StatusType ret = GetTaskState(Task1, &tmp);
  EE_assert(2, ret==E_OK, 1);

  EE_assert(3, tmp==RUNNING, 2);

  TerminateTask(); 
}

/*
Does:
Call GetTaskState()

Expect:
Return state of queried task. Service returns E_OK
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Task Management (41)", result, ASSERTIONS);
  
  return 0;
}