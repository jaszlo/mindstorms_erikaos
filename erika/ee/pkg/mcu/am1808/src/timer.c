#include "mcu/am1808/inc/timer.h"
#include "mcu/am1808/inc/interrupt.h" // For timer interrupt flags

static unsigned int period = 0x10000;

void timer_init(unsigned int p, unsigned int channel) 
{
  irq_set_channel(IRQ_NUM_T64P0_TINT34, channel);
  irq_enable_num(IRQ_NUM_T64P0_TINT34);
  period = p;
}

void timer_start()
{
  *TIMER0_TCR &= ~ENAMODE34;          // (1) Disable timer
  *TIMER0_TCR |= CLKSRC12;            // (2) Set Timer Source to internal clock
  *TIMER0_TGCR &= ~TIM34RS_REMOVE;    // (3) Reset timer
  *TIMER0_TGCR &= ~TIMMODE;           // (4) Reset mode bits
  *TIMER0_TGCR |= TIMMODE_UNCHAINED;  // (5) Set dual 32 bit unchained mode
  *TIMER0_TGCR |= TIM34RS_REMOVE;     // (6) Remove timer from reset
  *TIMER0_PRD34 = period;             // (7) Set timer period
  *TIMER0_TGCR &= ~(PSC34_VALUE);     // (8) Reset prescaler
  *TIMER0_TGCR |= PSC34_VALUE;        // (9) Set prescaler

  *TIMER0_INTCTLSTAT |= PRDINTSTAT34; // (10) Clear interrupts
  *TIMER0_INTCTLSTAT |= PRDINTEN34;   // (11) Enable interrupts

  *TIMER0_TCR |= ENAMODE34_CONTIN;    // (12) Set continuously-mode, start timer

}

void timer_stop(void)
{
  *TIMER0_TCR &= ~ENAMODE34;              // (1) Disable timer
  *TIMER0_INTCTLSTAT |= PRDINTSTAT34;     // (2) Clear interrupts
}


void timer_clear_irq_flags(void)
{
  __asm__ __volatile__ (
    "ldr r0, =%0"
    :
    : "i" (0x01C20044) // TIMER0_INTCTLSTAT
    : "cc"
  );
  // asm("nop"); // For debugging
  __asm__ __volatile__ (
    "mov r1, %0"
    :
    : "i" (0x30000) // PRDINTSTAT34 | PRDINTEN34 == 0b11 << 16 to clear IRQ_OCCOURED flag and enbale irq again.
    : "cc"
  );
  asm __volatile__("str r1, [r0]");
}