#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 11
unsigned int task2_finished = 0;
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  AlarmBaseType alarm_info;
  TickType inc = 1;
  TickType cycle = 1;
  StatusType ret0 = SetAbsAlarm(MyAlarm, inc, cycle);
  EE_assert(3, ret0==E_OK, 2);

  StatusType ret1 = CancelAlarm(MyAlarm);
  EE_assert(4, ret1==E_OK, 3);

  StatusType ret2 = CounterTick(MyCounter); // Should no longer trigger event there not preempt
  EE_assert(5, ret2==E_OK, 4);
  EE_assert(6, task2_finished==0, 5);

  StatusType ret3 = SetEvent(Task2, AlarmEvent); // Should preempt here

  EE_assert(10, task2_finished==1, 9);

  TerminateTask(); 
}

TASK(Task2)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  StatusType ret0 = ActivateTask(Task1);
  EE_assert(2, ret0==E_OK, 1);

  StatusType ret1 = WaitEvent(AlarmEvent); // Preempt to Task2
  EE_assert(7, ret1==E_OK, 6);

  EventMaskType mask;
  StatusType ret = GetEvent(Task2, &mask);
  
  EE_assert(8, ret==E_OK, 7);
  EE_assert(9, (AlarmEvent & mask), 8);
  task2_finished = 1;

  TerminateTask();
}
/*
Does:
Call CancelAlarm() for already activated alarm which will set an event on expiration.

Expect:
Alarm is cancelled. Service returns E_OS_STATE.
*/
int main(void)
{
  ActivateTask(Task2);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Alarms (28)", result, ASSERTIONS);
  
  return 0;
}