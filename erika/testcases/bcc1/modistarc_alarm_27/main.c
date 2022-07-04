#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 5
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  AlarmBaseType alarm_info;
  TickType inc = 1;
  TickType cycle = 0;
  StatusType ret0 = SetAbsAlarm(MyAlarm, inc, cycle);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = CancelAlarm(MyAlarm);
  EE_assert(3, ret1==E_OK, 2);

  StatusType ret2 = CounterTick(MyCounter); // Should no longer trigger alarm therefore not start task2
  EE_assert(4, ret2==E_OK, 3);
  EE_assert(5, task2_finished==0, 4);

  TerminateTask(); 
}

TASK(Task2)
{
  task2_finished = 1;
  TerminateTask();
}
/*
Does:
Call CancelAlarm() for already activated alarm which will activate a task on expiration.

Expect:
Alarm is cancelled. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC1 Modistarc Alarms (27)", result, ASSERTIONS);
  
  return 0;
}