#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 6
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  AlarmBaseType alarm_info;
  TickType inc = -1;
  TickType cycle = 1;
  StatusType ret0 = SetRelAlarm(MyAlarm, inc, cycle);
  EE_assert(2, ret0==E_OS_VALUE, 1);

  inc = 0xFFF + 1;
  StatusType ret1 = SetRelAlarm(MyAlarm, inc, cycle);
  EE_assert(3, ret1==E_OS_VALUE, 2);

  inc = 1;
  cycle = -1;
  StatusType ret3 = SetRelAlarm(MyAlarm, inc, cycle);
  EE_assert(4, ret3==E_OS_VALUE, 3);

  cycle = 0xFFF + 1;
  StatusType ret4 = SetRelAlarm(MyAlarm, inc, cycle);
  EE_assert(5, ret4==E_OS_VALUE, 4);

  TerminateTask(); 
}
/*
Does:
Call SetRelAlarm() with increment value lower than zero.
Call SetRelAlarm() with increment value greater than maxallowedvalue.
Call SetRelAlarm() with cycle value lower than mincycle.
Call SetRelAlarm() with cycle value greater than maxallowedvalue.

Expect:
Services return E_OS_VALUE.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC1 Modistarc Alarms (10, 11, 12, 13)", result, ASSERTIONS);
  
  return 0;
}