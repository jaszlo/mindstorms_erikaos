#include "ee.h"

/* Counters */
volatile int task2_fired = 0;
volatile int isr_fired = 0;
volatile int flag = 0;

//irq_disable
extern EE_UREG EE_IRQ_nesting_level;
ISR2(timer_handler)
{
  isr_fired = 1;
  EE_timer_clear_irq_flags();
  EE_timer_stop(); // We only want one timer IRQ
  ActivateTask(Task2);
  put_string("Timer ISR finished!\n");
}

TASK(Task2)
{
  task2_fired++;
  put_string("Task2 finished\n");
  TerminateTask();
}

TASK(Task1) 
{
  while(task2_fired == 0) {
    if (isr_fired == 1) {
      Schedule();
    }
  }
  put_string("Task1 finished\n");
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
  const unsigned int channel = 2;
  const unsigned int period = 0x100000; 

  EE_timer_init(period, channel);
  EE_timer_start();

  // Its only possible to get past Task1 by the ISR which puts Task2 in the ready-state.
  ActivateTask(Task1);
  put_string("Success!\n");
  return 0;
}