#include "ee.h"
#include "test/assert/inc/ee_assert.h"

volatile unsigned int task2_finished = 0; 
#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(3, task2_finished==1, 2);

  TerminateTask();
}


TASK(Task2) 
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret = ActivateTask(Task1);
  EE_assert(2, ret==E_OK, 1);
  task2_finished = 1;
  TerminateTask();
}

/*
Does:
Call TerminateTask() 

Expect:
Running task is terminated and ready task with highest priority is executed
*/
int main(void)
{
  ActivateTask(Task2);
  
  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC1 Modistarc Task Management (23)", result, ASSERTIONS);

  return 0;
}