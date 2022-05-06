#include "ee.h"
#include "test/assert/inc/ee_assert.h"
#include "ee_irq.h"

unsigned int flag = 0;

TASK(Task3) // Priority 3
{
  put_string("\t\tTask3 activated and finished (Prio3)\n");
  TerminateTask();
}

TASK(Task2) // Priority 3
{ 
  ActivateTask(Task3);
  put_string("\t\tTask2 activated (Prio2)\n");
  Schedule(); // Should activate Task 3
  put_string("\t\tTask2 finished (Prio2)\n");
  TerminateTask();
}


TASK(Task1) 
{
  put_string("\t\tTask1 started(Prio 1)\n");
  ActivateTask(Task2);
  Schedule(); // Should activate Task 3 first
  put_string("\t\tTask1 finished (Prio1)\n");
  TerminateTask();
}


/**
 * Expected output:
 * "Task1 started(Prio 1)\n"
 * "Task2 activated (Prio2)\n"
 * "Task3 activated and finished (Prio3)\n"
 * "Task2 finished (Prio2)\n"
 * "Task1 finished (Prio1)\n"
 */
int main(void)
{
  ActivateTask(Task1);
  return 0;
}
