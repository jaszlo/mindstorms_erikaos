#include "ee.h"

TASK(Task1)
{
  SetEvent(Task2, MyEvent);
  TerminateTask();
}


TASK(Task2)
{
    ActivateTask(Task1);
    EventMaskType mask;
    while(1) 
    {
        WaitEvent(MyEvent);
        GetEvent(Task2, &mask);
        if (mask & MyEvent) 
        {
          ClearEvent(MyEvent);
          put_string("Finished!\n");
          TerminateTask();
        }
  }

  

  TerminateTask();
}

int main(void)
{
  ActivateTask(Task2);
  return 0;
}