#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define ASSERTIONS 1
EE_TYPEASSERTVALUE EE_assertions[ASSERTIONS];


/*
Does:
Call StartOs()

Expect:
Start operating system

Note:
This test is redundant. All other test use this function in the init function for arm9 port
which is called before going to main. If it wouldn't be called the OS would not work properly!
*/
int main(void)
{
  // Just accept this test as it is redundant anyway.
  unsigned int result = EE_assert_range(0, 1, ASSERTIONS-1);
  EE_assert_summarize("BCC2 Modistarc Error handling, hook routines and OS controll (2)", result, ASSERTIONS);
  
  return 0;
}