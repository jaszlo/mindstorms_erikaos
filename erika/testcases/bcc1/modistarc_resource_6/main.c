#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 11
unsigned int task2_finished = 0;
unsigned int task3_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = GetResource(MyResource);
  EE_assert(2, ret0==E_OK, 1);

    StatusType ret1 = ActivateTask(Task2);
    EE_assert(3, ret1==E_OK, 2);

    StatusType ret2 = ForceSchedule();
    EE_assert(4, ret2==E_OK, 3);

    StatusType ret3 = ActivateTask(Task3);
    EE_assert(5, ret3==E_OK, 4);

    StatusType ret4 = ForceSchedule();
    EE_assert(6, ret4==E_OK, 5);

  StatusType ret5 = ReleaseResource(MyResource);
  EE_assert(7, ret5==E_OK, 6);

  StatusType ret6 = Schedule();
  EE_assert(10, ret6==E_OK, 9);

  TerminateTask();
}

TASK(Task2)
{
  unsigned int true = 1;
  EE_assert(9, true, 8); // See below
  task2_finished = 1;
  TerminateTask();
}

TASK(Task3)
{
  unsigned int true = 1;
  EE_assert(8, true, 7); // Just to check if Task3 before Task 2
  task3_finished = 1;
  TerminateTask();
}

/*
Does:
Test Priority Ceiling Protocol:
Call GetResource() from non-preemptive task, activate task with priority higher than 
running task but lower than ceiling priority, and force rescheduling.

Expect:
Resource is occupied and runningtask’s priority is set to resource’s ceiling priority. 
Service returns E_OK. No preemption occurs after activating the task with higher priority and rescheduling.
*/
int main()
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC1 Modistarc Resource Management (6)", result, ASSERTIONS);
  
  return 0;
}
