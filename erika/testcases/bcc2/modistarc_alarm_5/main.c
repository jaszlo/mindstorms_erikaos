#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 4
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  TickType tick_info;
  StatusType ret = GetAlarm(MyAlarm, &tick_info);
  EE_assert(2, ret==E_OK, 1);
  // Specified in OIL
  EE_assert(3, tick_info==10, 2);

  TerminateTask(); 
}

/*
Does:
Call GetAlarm() for alarm which will activate a task on expiration.

Expect:
Returns number of ticks until expiration. Service returns E_OK.
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Alarms (5)", result, ASSERTIONS);
  
  return 0;
}