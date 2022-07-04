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
  StatusType ret = SetAbsAlarm(MyAlarm, inc, cycle);
  EE_assert(2, ret==E_OK, 1);

  StatusType ret1 = CounterTick(MyCounter); // Should trigger alarm therefore preempt
  EE_assert(3, ret1==E_OK, 2);
  EE_assert(4, task2_finished==1, 3);
  TerminateTask(); 
}

TASK(Task2)
{
  task2_finished = 1;
  TerminateTask();
}
/*
Does:
Call SetAbsAlarm() for already activated alarm which will activate a task on expiration.

Expect:
Alarm is activated. Service returns E_OS_STATE.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Alarms (23)", result, ASSERTIONS);
  
  return 0;
}