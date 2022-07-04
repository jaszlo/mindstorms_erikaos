#include "ee.h"

volatile int flag = 0;

ISR2(timer_handler)
{
  flag = 1;
  EE_timer_clear_irq_flags();
  ActivateTask(Task2);
}

TASK(Task2)
{
  put_string("\tTask2!\n");
  TerminateTask();
}

TASK(Task1) 
{
  while(1) {
    if(flag == 1) {
      flag = 0;
      put_string("Task1!\n");
    }
  }
  TerminateTask();
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