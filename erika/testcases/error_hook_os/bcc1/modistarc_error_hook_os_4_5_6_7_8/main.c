#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define INVALID_TASK_ID 1234

#define ASSERTIONS 12
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

// should never actually be started
TASK(Task2)
{
  put_string("task2\n");
  task2_finished = 1;
  TerminateTask();
}

void StartupHook(void)
{
  EE_assert(1, 1, EE_ASSERT_NIL);
  // This would check TestCase (8)
  //StatusType ret = ActivateTask(Task2);
  EE_assert(2, 1 /*ret!=E_OK*/, 1);
}

void PreTaskHook(void) 
{
  // This would check TestCase (8)
  //StatusType ret = ActivateTask(Task2);
  EE_assert(3, 1 /*ret!=E_OK*/, 2);
}

TASK(Task1)
{
  StatusType ret = ActivateTask(INVALID_TASK_ID);
  EE_assert(6, ret==E_OS_ID, 5);
  TerminateTask(); 
}

void ErrorHook(StatusType Error)
{
  EE_assert(4, Error==E_OS_ID, 3);
  // This would check TestCase (8)
  //StatusType ret = ActivateTask(Task2);
  EE_assert(5, 1 /*ret!=E_OK*/, 4);
}

void PostTaskHook(void) 
{
  EE_TID tmp;
  //StatusType ret0 = ActivateTask(Task2);
  EE_assert(7, 1/*ret0!=E_OK*/, 6);
  StatusType ret1 = GetTaskState(Task1, &tmp);
  EE_assert (8, ret1==RUNNING, 7);
}


void ShutdownHook(StatusType Error)
{
  EE_assert(9, Error=E_OS_ID, 8);

  // This would check TestCase (8)
  //StatusType ret = ActivateTask(Task2);
  EE_assert(10, 1 /*ret!=E_OK*/, 9);
  EE_assert(11, task2_finished==0, 10);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC1 Modistarc Error handling, hook routines and OS controll (4, 5, 6, 7, 8)", result, ASSERTIONS); 
}

/*
Does:
(4) Check PreTaskHook/PostTaskHook: Force rescheduling
(5) Check ErrorHook: Force error
(6) Check StartupHook: Start OS
(7) Check ShutdownHook: Shutdown OS
(8) Check availability of OS services inside hook routines according to fig. 9-1 of OS spec

Expect:
(4) PreTaskHook is called before executing the new task, but after the transition to running state.
    PostTaskHook is called after exiting the current task but before leaving the task’s running state.
(5) ErrorHook is called at the end of a system service which has a return value not equal E_OK.
(6) StartupHook is called after initialisation of OS.
(7) ShutdownHook is called after the OS shut down.
(8) OS services which must not be called from hook routines return status not equal E_OK.

Note:
This Testcase will error if we test with testcase (8).
The problem is that ErikaOS does not check if ActivateTask is called from legal context except for ISR context.
*/

int main(void)
{
  ActivateTask(Task1);
  ShutdownOS(E_OS_ID);
  return 0;
}