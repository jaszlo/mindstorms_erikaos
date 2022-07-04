#ifndef __INCLUDE_VERSATILEPB_TIMER__
#define __INCLUDE_VERSATILEPB_TIMER__

// Timer Adresses
#define TIMER1_BASE 0x101E2000
#define TIMER1_LOAD   (volatile unsigned int*)(TIMER1_BASE+0x0)
#define TIMER1_VALUE  (volatile unsigned int*)(TIMER1_BASE+0x4)
#define TIMER1_CTRL   (volatile char*)(TIMER1_BASE+0x08)
#define TIMER1_INTCLR (volatile char*)(TIMER1_BASE+0x0C)
#define TIMER1_RIS    (volatile char*)(TIMER1_BASE+0x10)
#define TIMER1_MIS    (volatile char*)(TIMER1_BASE+0x14)


#define TIMER1_INTBIT (1 << 4)

// Initializes the timer with a given period and a IRQ channel
void timer_init(unsigned int period);

// Starts the timer. Periodic timer IRQ will occour.
void timer_start(void);

// Stops the timer. No more timer IRQ will occour.
void timer_stop(void);

// Clears the IRQ flag from the timer that pulls the IRQ line to the IRQ controller to high
void timer_clear_irq_flags(void);
#endif /* __INCLUDE_VERSATILEPB_TIMER__ */