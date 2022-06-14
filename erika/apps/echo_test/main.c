#include "ee.h"

/* Counters */
volatile int task2_fired = 0;
volatile int isr_fired = 0;
volatile int flag = 0;

ISR2(uart_handler)
{
  put_string("uart\n");
}

TASK(Task2)
{
  task2_fired++;
  put_string("\t\tTask2 finished\n");
  TerminateTask();
}

TASK(Task1) 
{
  while(1);
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

  irq_enable_num(IRQ_NUM_UART0_INT);

  // Its only possible to get past Task1 by the ISR which puts Task2 in the ready-state.
  ActivateTask(Task1);
  put_string("\t\tSuccess!\n");
  return 0;
}