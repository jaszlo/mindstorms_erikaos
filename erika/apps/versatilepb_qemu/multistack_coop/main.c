#include "ee.h"

volatile int task2_fired = 0;

TASK(Task4) {}
TASK(Task3) {}

TASK(Task2) 
{
  task2_fired = 1;
  put_string("\t\tTask2 finished\n");
  TerminateTask();
}


TASK(Task1) 
{ 
  ActivateTask(Task2);
  while(task2_fired == 0);
  put_string("\t\tTask1 finished\n");
  TerminateTask();

}

/**
 * Expected Output: 
 *  "TimerEvent\n"
 *  "Task2 finished\n"
 *  "Task1 finished\n"
 *  "Success!\n"
 */
int main(void)
{
  ActivateTask(Task1);
  put_string("Success!\n");
  return 0;
}