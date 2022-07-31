#include "ee.h"

volatile int task2_fired = 0;

ISR2(timer_handler)
{
  EE_timer_clear_irq_flags();
  CounterTick(Counter1);
}

TASK(Task2) 
{
  ActivateTask(Task1);
  EventMaskType mask;
  while(1) {
    WaitEvent(TimerEvent);
    GetEvent(Task2, &mask);

    if (mask & TimerEvent) {
      ClearEvent(TimerEvent);
      EE_timer_stop();
      break;  
    }
  }
  task2_fired = 1;
  put_string("\t\tTask2 finished\n");
  TerminateTask();
}


/*
 * TASK 1
 */
TASK(Task1)
{
  while(task2_fired == 0) {}
  put_string("\t\tTask1 finished\n");
  TerminateTask();
}


/**
 * Expected Output: 
 *  "Task2 finished\n"
 *  "Task1 finished\n"
 *  "Success!\n"
 */
int main(void)
{

  // Set Alarm
  unsigned int tick_till_alarm = 10;
  unsigned int is_not_cyclic = 0;
  //SetRelAlarm(Alarm1, tick_till_alarm, is_not_cyclic);
  
  // Set timer IRQ for Counter and Alarm
  const unsigned int period = 2000; // milliseconds;
  const unsigned int channel = 2;
  EE_irq_register(IRQ_NUM_T64P0_TINT34, timer_handler);
  EE_timer_init(period, channel);
  EE_timer_start();
  
  // Start initial Task
  ActivateTask(Task2);
  put_string("\t\tSuccess!\n");
  return 0;
}