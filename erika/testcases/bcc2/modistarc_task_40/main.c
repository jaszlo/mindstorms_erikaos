#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 3
#define INVALID_TASK_ID 1234
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  EE_TID tmp;
  StatusType ret = GetTaskState(INVALID_TASK_ID, &tmp);
  EE_assert(2, ret==E_OS_ID, 1);

  TerminateTask(); 
}

/*
Does:
Call GetTaskState() with invalid task ID (task does not exist)

Expect:
Service returns E_OS_ID
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Task Management (40)", result, ASSERTIONS);
  
  return 0;
}