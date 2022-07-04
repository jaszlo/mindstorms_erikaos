#include "ee.h"
#include "test/assert/inc/ee_assert.h"

unsigned int task2_finished = 0;
unsigned int task1_finished = 0;
unsigned int first = 0;
#define ASSERTIONS 7
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  if (first == 0)
  {
    first = 1;
    EE_assert(5, task2_finished==0, 4);
  }
  task1_finished++;
  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task1); // Make ready - no preemption
  EE_assert(2, ret0==E_OK, 1);

  EE_TID tmp;
  StatusType ret1 = GetTaskState(Task1, &tmp);
  EE_assert(3, ret1==E_OK, 2);
  EE_assert(4, tmp==READY, 3);

  StatusType ret2 = ChainTask(Task1); // Terminate Task and never "finish" it

  task2_finished = 1;
  TerminateTask();
}

/*
Does:
Call ChainTask() from non-preemptive task on ready basic task which has not reached max. number of activations.

Expect:
Running task is terminated, activation request is queued in ready list and ready task with highest priority is executed.
*/
int main(void)
{
  ActivateTask(Task2);
  EE_assert(6, task1_finished==2, 5);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Task Management (32)", result, ASSERTIONS);

  return 0;
}