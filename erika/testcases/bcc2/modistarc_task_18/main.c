#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 9
unsigned int task1_finished = 0;
unsigned int task1_started = 0;
unsigned int first = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  task1_started++;
  
  if (first == 0)
  {
    first = 1;
    EE_assert(1, 1, EE_ASSERT_NIL);
    
    StatusType ret0 = ActivateTask(Task1); // Make ready - no preemption
    EE_assert(2, ret0==E_OK, 1);
    EE_assert(3, task1_started==1, 2);

    EE_TID tmp;
    StatusType ret1 = GetTaskState(Task1, &tmp);
    EE_assert(4, ret1==E_OK, 3);
    EE_assert(5, tmp==RUNNING, 4);


    StatusType ret2 = ActivateTask(Task1); // ActivateTask on ReadyTask - no preemption
    EE_assert(6, ret2==E_OK, 5);
    EE_assert(7, task1_started==1, 6);
  }

  task1_finished++;
  TerminateTask(); 

}

/*
Does:
Call ActivateTask() from preemptive task on running basic task which has not reached max. number of activations.

Expect:
No preemption of running task. Activation request is queued in ready list. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task1);
  EE_assert(8, task1_finished==3, 7);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Task Management (18)", result, ASSERTIONS);
  
  return 0;
}