#include "ee.h"


ISR2(timer_handler)
{
  put_string("isr\n");
  EE_timer_clear_irq_flags();
}


TASK(Task1) 
{
  while(1) {}
}


int main(void)
{
  // IRQ and ErikaOS are initialized in start_up function in ee_init.c
  // Timer IRQ setup and general setup
  const unsigned int period = 500000;
  EE_irq_register(timer_handler);
  EE_timer_init(period);
  EE_timer_start();
  ActivateTask(Task1);
  // Its only possible to get past Task1 by the ISR which puts Task2 in the ready-state.
  return 0;
}