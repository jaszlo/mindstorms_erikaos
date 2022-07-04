#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 6
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  AlarmBaseType alarm_info;
  StatusType ret = GetAlarmBase(MyAlarm, &alarm_info);
  EE_assert(2, ret==E_OK, 1);

  // Specified in OIL
  EE_assert(3, alarm_info.maxallowedvalue==0xFFF, 2);
  EE_assert(4, alarm_info.mincycle==1, 3);
  EE_assert(5, alarm_info.ticksperbase==1, 4);

  TerminateTask(); 
}

/*
Does:
Call GetAlarmBase().

Expect:
Return alarm base characteristics. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Alarms (2)", result, ASSERTIONS);
  
  return 0;
}