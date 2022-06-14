#include "mcu/versatilepb/inc/timer.h"

/**
 * Registers explanation can be found in the documentation
 * @Source: https://documentation-service.arm.com/static/5e8e2102fd977155116a4aef?token=
 */
void timer_init(unsigned int period) 
{
  *TIMER1_CTRL &= ~(1 << 7);    // (1) Disable timer
  *TIMER1_CTRL |=  (1 << 6);    // (2) Set periodic-mode
  *TIMER1_CTRL &= ~(1 << 0);    // (3) Set One-Shot to wrapping mode
  *TIMER1_CTRL |=  (1 << 1);    // (4) Set 32-bit mode
  *TIMER1_INTCLR = (char)0x1;   // (5) Clear interrupts
  *TIMER1_CTRL |= 1 << 5;       // (6) Set IntEnable
  *TIMER1_LOAD  = period;       // (7) Set timer period
}


void timer_clear_irq_flags(void)
{
  *TIMER1_INTCLR = (char)0x01; // Clear interrupts
}

void timer_start () 
{
  *TIMER1_CTRL |= 1 << 7;
}

void timer_stop(void) 
{
  *TIMER1_CTRL &= ~(1 << 7);   // (1) Disable timer
  *TIMER1_INTCLR = (char)0x1;  // (2) Clear interrupts
}
