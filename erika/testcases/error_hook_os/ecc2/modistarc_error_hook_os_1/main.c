#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 3
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];

TASK(Task1)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

  AppModeType ret = GetActiveApplicationMode();
  EE_assert(2, ret==OSDEFAULTAPPMODE, 1);

  TerminateTask(); 
}

/*
Does:
Call GetActiveApplicationMode()

Expect:
Return current application mode
*/
int main(void)
{
  ActivateTask(Task1);

  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Error handling, hook routines and OS controll (1)", result, ASSERTIONS);
  
  return 0;
}