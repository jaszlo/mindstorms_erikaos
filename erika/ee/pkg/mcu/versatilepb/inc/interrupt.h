#ifndef __INCLUDE_ARM9_INTERRUPT__
#define __INCLUDE_ARM9_INTERRUPT__


// Primary Interrupt Controller (PL190)
#  define PIC_BASE 0x10140000
#  define PIC_INTENABLE    (volatile char*)(PIC_BASE+0x10)
#  define PIC_INTCLEAR (volatile unsigned int*)(PIC_BASE+0x14)
#  define PIC_DEFVECTADDR  (volatile unsigned int*)(PIC_BASE+0x34)


#  define TIMER1_INTBIT (1 << 4)

#define irq_bit_by_num(n) 1 << (n % 32)

// Gets global IRQ status
unsigned int irq_status(void);

// Registers the ISR of the timer. Only timer IRQ is supported as IRQs are not vectorized
void irq_register(void (*isr)(void));

// Register default handler for ISR of the timer again.
void irq_unregister(void (*isr)(void));

// Initializes PLL190 ad IRQ in general
void irq_init(void);

// Enables global IRQ
void irq_enable(void);

// Disables global IRQ
void irq_disable(void);

// Enables the IRQ given its number
void irq_enable_num(unsigned int num);

// Disables the IRQ given its number
void irq_disable_num(unsigned int num);

// Not for external use. Implemented in arm9_interrupt_hannndler.S
void irq_handler(void);


#define NUM_INTERRUPTS 1

#define IRQ_NUM_TIMER 4  // TIMER

#endif /* __INCLUDE_ARM9_INTERRUPT__ */
