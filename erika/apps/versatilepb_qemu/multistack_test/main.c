#include "ee.h"





TASK(Task1)
{
  put_string("t1 started\n");
  ActivateTask(Task3);
  put_string("t1 finished\n");
  TerminateTask();
}

TASK(Task2) 
{
  put_string("t2 started\n");
  ActivateTask(Task1);

  EventMaskType mask;
  WaitEvent(MyEvent);
  put_string("t2 finished\n");
  TerminateTask();
}

TASK(Task3)
{
  put_string("t3 started\n");
  SetEvent(Task2, MyEvent);
  put_string("t3 finished\n");
  TerminateTask();
}

int main(void)
{
  ActivateTask(Task2);
  return 0;
}