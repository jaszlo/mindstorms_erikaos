#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 3
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  AlarmBaseType alarm_info;
  TickType inc = 1;
  TickType cycle = 1;
  StatusType ret = SetRelAlarm(MyAlarm, inc, cycle);
  EE_assert(2, ret==E_OS_STATE, 1);

  TerminateTask(); 
}
/*
Does:
Call SetRelAlarm() for already activated alarm which will set an event on expiration

Expect:
Service returns E_OS_STATE
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC1 Modistarc Alarms (9)", result, ASSERTIONS);
  
  return 0;
}