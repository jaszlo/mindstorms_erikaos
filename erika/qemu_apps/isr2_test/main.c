#include "ee.h"

/* Counters */
volatile int task2_fired = 0;
volatile int isr_fired = 0;
ISR2(timer_handler)
{
  isr_fired = 1;
  EE_timer_clear_irq_flags();
  EE_timer_stop(); // We only want one timer IRQ
  ActivateTask(Task2);
  put_string("\t\tTimer ISR finished!\n");
}

TASK(Task2)
{
  task2_fired++;
  put_string("\t\tTask2 finished\n");
  TerminateTask();
}

TASK(Task1) 
{
  while(task2_fired == 0) {
    if (isr_fired == 1) {
      Schedule();
    }
  }
  put_string("\t\tTask1 finished\n");
  TerminateTask();
}

/**
 * Expected Output:
 *  (1) "Timer ISR finished!\n"
 *  (2) "Task2 finished\n"
 *  (3) "Task1 finished\n"
 *  (4) "Success!\n"
 */
int main(void)
{
  // IRQ and ErikaOS are initialized in start_up function in ee_init.c
  // Timer IRQ setup and general setup
  const unsigned int period = 2000000;
  EE_irq_register(timer_handler);
  EE_timer_init(period);
  EE_timer_start();
  ActivateTask(Task1);
  // Its only possible to get past Task1 by the ISR which puts Task2 in the ready-state.
  put_string("\t\tSuccess!");
  return 0;
}