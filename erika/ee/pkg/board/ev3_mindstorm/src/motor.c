#include "board/ev3_mindstorm/inc/gpio.h"
#include "board/ev3_mindstorm/inc/motor.h"

MotorPortInfo ports[] = 
{
  { GPIO_PIN(3, 15), GPIO_PIN(3,  6), GPIO_PIN(5,  4), GPIO_PIN(5, 11), GPIO_PIN(0,  4), 0x6, 0x5 },
  { GPIO_PIN(0,  3), GPIO_PIN(2,  1), GPIO_PIN(2,  5), GPIO_PIN(5,  8), GPIO_PIN(2,  9), 0x8, 0x7 },
  { GPIO_PIN(6,  8), GPIO_PIN(5,  9), GPIO_PIN(3,  8), GPIO_PIN(5, 13), GPIO_PIN(3, 14), 0xA, 0x9 },
  { GPIO_PIN(5, 10), GPIO_PIN(5,  3), GPIO_PIN(5, 15), GPIO_PIN(6,  9), GPIO_PIN(2,  8), 0xC, 0xB },
};

void motor_set_state (MotorPortID port, MotorState state)
{
  if (state == MOTOR_FORWARD)
    {
      gpio_set(ports[port].pin1, 1);
      gpio_set(ports[port].pin2, 0);
    }
  else if (state == MOTOR_BACKWARD)
    {
      gpio_set(ports[port].pin1, 0);
      gpio_set(ports[port].pin2, 1);
    }
  else
    {
      gpio_set(ports[port].pin1, 0);
      gpio_set(ports[port].pin2, 0);
    }
}

/* initialize the gpio pins necessary for sensor functions
 * this is should be done on startup
 */
void motor_init(void)
{
  unsigned int i;
  for (i = 0; i < sizeof(ports) / sizeof(ports[0]); ++i)
    {
      gpio_init_outpin(ports[i].pin1);
      gpio_init_outpin(ports[i].pin2);
      gpio_init_outpin(ports[i].pin5w);
      gpio_init_outpin(ports[i].pin5r);
      gpio_init_outpin(ports[i].pin6);
    }

  // disable pull-down
  *((volatile unsigned int*)(SYSCFG1_BASE + 0x0C)) &= ~0xFFFFFFFF;
}