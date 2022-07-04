#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 6
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task2)
{
  task2_finished = 1;
  TerminateTask();
}

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = GetResource(MyResource);
  EE_assert(2, ret0==E_OK, 1);
  
  StatusType ret1 = ActivateTask(Task2); 
  EE_assert(3, ret1==E_OK, 2);

  StatusType ret2 = ReleaseResource(MyResource);  // No preemption
  EE_assert(4, ret2==E_OK, 3);
  EE_assert(5, task2_finished==0, 4);

  TerminateTask(); 
}

/*
Does:
Call ReleaseResource() from non-preemptive task.


Expect:
Resource is released and running task’s priority is reset. No preemption of running task. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Resource Management (13)", result, ASSERTIONS);
  
  return 0;
}