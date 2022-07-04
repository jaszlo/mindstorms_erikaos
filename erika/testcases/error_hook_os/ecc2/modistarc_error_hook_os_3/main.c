#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 1
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];


/*
Does:
Call ShutdownOS()

Expect:
Shutdown operating system
*/
int main(void)
{
  // Shutting down OS with arbitrary Error.
  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("ECC2 Modistarc Error handling, hook routines and OS controll (3)", result, ASSERTIONS);
  ShutdownOS(E_OS_STATE);
  // Should not be reached
  put_string("ECC Modistarc Error handling, hook routines and OS controll (3) failed! Disregard above text!\n");
  
  return 0;
}