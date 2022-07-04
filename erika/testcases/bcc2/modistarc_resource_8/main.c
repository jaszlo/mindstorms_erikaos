#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 4
unsigned int task2_finished = 0;
unsigned int task3_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = GetResource(RES_SCHEDULER);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret5 = ReleaseResource(RES_SCHEDULER);
  EE_assert(3, ret5==E_OK, 2);

  ActivateTask(Task2);
  TerminateTask();
}

TASK(Task2)
{
  unsigned int true = 1;
  EE_assert(4, true, 3);
  TerminateTask();
}
/*
Does:
Call GetResource() for resource RES_SCHEDULER.

Expect:
Resource is occupied and running task’s priority is set to resource’s ceiling priority. Service returns E_OK.
*/
int main()
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Resource Management (8)", result, ASSERTIONS);
  
  return 0;
}
