#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 9
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  AlarmBaseType alarm_info;
  TickType inc = 1;
  TickType cycle = 1;
  StatusType ret0 = SetAbsAlarm(MyAlarm, inc, cycle);
  EE_assert(3, ret0==E_OK, 2);

  StatusType ret1 = CounterTick(MyCounter); // Should trigger event therefore preempt
  EE_assert(7, ret1==E_OK, 6);
  EE_assert(8, task2_finished==1, 7);

  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task1);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = WaitEvent(AlarmEvent); // Preempt to Task2
  EE_assert(4, ret1==E_OK, 3);

  EventMaskType mask;
  StatusType ret = GetEvent(Task2, &mask);
  
  EE_assert(5, ret==E_OK, 4);
  EE_assert(6, (AlarmEvent & mask), 5);
  task2_finished = 1;

  TerminateTask();
}
/*
Does:
Call SetAbsAlarm() for already activated alarm which will activate a task on expiration

Expect:
Alarm is activated. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Alarms (24)", result, ASSERTIONS);
  
  return 0;
}