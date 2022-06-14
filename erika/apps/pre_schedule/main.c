#include "ee.h"

/* Counters */
volatile int task3_fired = 0;
volatile int task2_fired = 0;

ISR2(timer_handler)
{
  EE_timer_clear_irq_flags();
  if (task2_fired == 0) { // First Timer IRQ
    ActivateTask(Task2);
    put_string("\t\tTimer1 ISR finished!\n");
  } else { // Second Timer IRQ
    EE_timer_stop(); 
    ActivateTask(Task3);
    put_string("\t\tTimer2 ISR finished!\n");
  }
}

TASK(Task3)
{
  task3_fired++;
  put_string("\t\tTask3 finished\n");
  TerminateTask();
}


TASK(Task2)
{
  task2_fired++;
  //Should become true if Schedule is called returning form IRQ starting task 3
  while(task3_fired == 0);
  put_string("\t\tTask2 finished\n");
  TerminateTask();
}

TASK(Task1) 
{
  //Should become true if Schedule is called returning form IRQ starting task 2
  while(task2_fired == 0);
  put_string("\t\tTask1 finished\n");
  TerminateTask();
}

/**
 * Expected Output:
 *  (1) "Timer1 ISR finished!\n"
 *  (2) "Timer2 ISR finished!\n"
 *  (3) "Task3 finished\n"
 *  (4) "Task2 finished\n"
 *  (5) "Task1 finished\n"
 */
int main(void)
{
  // IRQ and ErikaOS are initialized in start_up function in ee_init.c
  // Timer IRQ setup and general setup
  const unsigned int channel = 2;
  const unsigned int period = 500000; 

  EE_timer_init(period, channel);
  EE_timer_start();
  EE_irq_register(IRQ_NUM_T64P0_TINT34, timer_handler);
  // Its only possible to get past Task1 by the ISR which puts Task2 in the ready-state.
  ActivateTask(Task1);
  return 0;
}