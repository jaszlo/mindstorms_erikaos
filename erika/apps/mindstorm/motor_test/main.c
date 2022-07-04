#include "ee.h"

/* Counters */
volatile int isr_fired = 0;
volatile MotorState motor_do = MOTOR_OFF;
const MotorPortID USED_MOTOR_PORT = MOTOR_PORT_A;

ISR2(timer_handler)
{
  isr_fired = 1;
  EE_timer_clear_irq_flags();
  if (motor_do == MOTOR_OFF || motor_do == MOTOR_FORWARD)
  {
    motor_do = MOTOR_BACKWARD;
  } else {
    motor_do = MOTOR_FORWARD; 
  }
}


TASK(Task1)
{
  while (1)
  {
    if(isr_fired == 1)
    {
      isr_fired = 0;
      put_string("motor do: ");put_ptr((void*) motor_do);
      motor_set_state(USED_MOTOR_PORT, motor_do);
    }
  }
}

int main(void)
{
  // Initialize motor
  void motor_init();

  // IRQ and ErikaOS are initialized in start_up function in ee_init.c
  // Timer IRQ setup and general setup
  const unsigned int channel = 2;
  const unsigned int period = 0x100000; 

  EE_timer_init(period, channel);
  EE_timer_start();

  // Its only possible to get past Task1 by the ISR which puts Task2 in the ready-state.
  ActivateTask(Task1);
  return 0;
}