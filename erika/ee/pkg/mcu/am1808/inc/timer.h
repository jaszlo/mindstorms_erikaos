#ifndef __INCLUDE_AM1808_TIMER__
#define __INCLUDE_AM1808_TIMER__
#define TIMER_PERIOD 0x10000

// INTCTLSTAT bits
// as we only use TIMER0 34  (64 bit mode) only bit 16 and 17 of the TIMER0_INTCTLSTAT are really relevant
#define PRDINTSTAT34 (1 << 17)  // Bit to clear flag if timer IRQ has occoured
#define PRDINTEN34 (1 << 16)    // Bit to enable/disable timer IRQ at timer 


/**
 * This is not a complete set of all 64-bit Timer Plus registers.
 * Those are just the ones required for a very basic usage.
 * A complete list can be found in the Technical User Manual
 * @Source: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=1486
 */
#define TIMER0_BASE 0x01C20000

// Counter Registers for the Timer. 
#define TIMER0_TIM12 (volatile unsigned int *)(TIMER0_BASE + 0x10)
#define TIMER0_TIM34 (volatile unsigned int *)(TIMER0_BASE + 0x14)
// Period Register for the Timer. 
#define TIMER0_PRD12 (volatile unsigned int *)(TIMER0_BASE + 0x18)
#define TIMER0_PRD34 (volatile unsigned int *)(TIMER0_BASE + 0x1C)
// How these (Timer and Counter Registers) are used depends on the mode in which the timer is configured
// @Source: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=1480 

// (Global) Timer Controll Register to enable, disable and configure the timer
#define TIMER0_TCR (volatile unsigned int *)(TIMER0_BASE + 0x20)
#define TIMER0_TGCR (volatile unsigned int *)(TIMER0_BASE + 0x24)

// timer Interrupt Control and Status Register allows two enable, disable interrupts for all timer configurations
#define TIMER0_INTCTLSTAT (volatile unsigned int *)(TIMER0_BASE + 0x44)

// TCR bits
#define ENAMODE34 (0b11 << 22)          // Bit in TCR to enable timer AND use continous timer (reset to 0 after 'finishing' counting)
#define ENAMODE34_CONTIN (0b10 << 22)   // Only the continuos timer bit in TCR
#define ENAMODE12 (0b11 << 6)           // Does the same as the above but for different timer mode 
#define ENAMODE12_CONTIN (0b10 << 6)    //                             //
#define CLKSRC12 (1 << 8)               // Bit to set timer clock external TM64P_IN12 clock
#define CLKSRC34 (0x01000000u)          // Block diagramm: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=1469


// TGRC bits
#define PSC34_RESET (0b0000 << 8)       // Bits to reset TIM34 prescaler counter
#define PSC34_VALUE (0b1111 << 8)       // TIM34 prescaler counter bits to maximum
#define TIMMODE (0b11 << 2)             // Bits to set timer to 32-bit chained mode
#define TIMMODE_UNCHAINED (0b01 << 2)   // Bits to set timer to 32-bit unchained mode
#define TIM34RS_REMOVE (1 << 1)         // Bits to reset 3:4 timer
#define TIM12RS_REMOVE (1 << 0)         // Bits to reset 1:2 timer

// If we want to include this into .S file do ot include functions!
#ifndef ASM_INC
// Initializes the timer with a given period and a IRQ channel
void timer_init(unsigned int period, unsigned int channel);

// Starts the timer. Periodic timer IRQ will occour.
void timer_start(void);

// Stops the timer. No more timer IRQ will occour.
void timer_stop(void);

// Clears the IRQ flag from the timer that pulls the IRQ line to the IRQ controller to high
void timer_clear_irq_flags(void);

// Enables watchdog which will reset board
void timer_enable_watchdog(void);
#endif //!ASM_INC
#endif //__INCLUDE_AM1808_TIMER__