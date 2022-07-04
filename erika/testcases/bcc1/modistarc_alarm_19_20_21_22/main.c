#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 6
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  AlarmBaseType alarm_info;
  TickType start = -1;
  TickType cycle = 1;
  StatusType ret0 = SetAbsAlarm(MyAlarm, start, cycle);
  EE_assert(2, ret0==E_OS_VALUE, 1);

  start = 0xFFF + 1;
  StatusType ret1 = SetAbsAlarm(MyAlarm, start, cycle);
  EE_assert(3, ret1==E_OS_VALUE, 2);

  start = 1;
  cycle = -1;
  StatusType ret3 = SetAbsAlarm(MyAlarm, start, cycle);
  EE_assert(4, ret3==E_OS_VALUE, 3);

  cycle = 0xFFF + 1;
  StatusType ret4 = SetAbsAlarm(MyAlarm, start, cycle);
  EE_assert(5, ret4==E_OS_VALUE, 4);

  TerminateTask(); 
}
/*
Does:
Call SetAbsAlarm() with increment value lower than zero.
Call SetAbsAlarm() with increment value greater than maxallowedvalue.
Call SetAbsAlarm() with cycle value lower than mincycle.
Call SetAbsAlarm() with cycle value greater than maxallowedvalue.

Expect:
Services return E_OS_VALUE.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC1 Modistarc Alarms (19, 20, 21, 22)", result, ASSERTIONS);
  
  return 0;
}