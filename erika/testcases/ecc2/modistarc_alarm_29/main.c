#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 3
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  TerminateTask(); 
}

/*
Does:
Expiration of alarm which activates a task while no tasks are currently running.

Expect:
Task is activated
*/
int main(void)
{
  StatusType ret = CounterTick(MyCounter); // Should activate task 1
  EE_assert(2, ret==E_OK, 1);
  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Alarms (29)", result, ASSERTIONS);
  
  return 0;
}