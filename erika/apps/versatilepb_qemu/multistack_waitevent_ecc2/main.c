#include "ee.h"

unsigned int first = 0;
TASK(Task2) 
{
  put_string("\t\tt2 started\n");
  ActivateTask(Task1);
  WaitEvent(MyEvent); // Go back to ready t1 task and then start t1 ready task from scratch
  put_string("\t\tt2 finished\n");
  TerminateTask();
}


TASK(Task1)
{
  put_string("\t\tt1 started\n");
  if (first == 0)
  { 
    first = 1;
    ActivateTask(Task2);
  } else {
    SetEvent(Task2, MyEvent);
  }
  put_string("\t\tt1 finished\n");
  TerminateTask();
}

/*
t1 started
t2 started
t1 finished
t1 started
t2 finished
t1 finished
*/

// Both have priority of 2
int main(void)
{
  ActivateTask(Task1);
  return 0;
}