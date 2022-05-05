#include "ee.h"
#include "test/assert/inc/ee_assert.h"
#include "ee_irq.h"
#include "cpu/arm9/inc/debug_io.h"
volatile unsigned int flag = 0;
#define TIMER_LOAD_VALUE 0x100000


void timer_isr(void)
{
  flag = 1;
}

TASK(Task1)
{
}

int main(void)
{
  timer_stop();
  init_interrupt_handling();
  timer_start(TIMER_LOAD_VALUE);
  short i = 0;
  while (1)
  {
    if (flag)
    {
      put_num(i++);
      put_string(" Timer-Interupt\n");
      flag = 0;
      irq_enable();
    }
  }
  return 0;
}
