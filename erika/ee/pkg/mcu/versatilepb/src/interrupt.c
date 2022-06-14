#include "mcu/versatilepb/inc/interrupt.h"

#define IVT_OFFSET (unsigned int) 0x0

static void default_isr(void) 
{
  return;
}

#include "cpu/arm9/inc/ee_io.h"
void (*TIMER_ISR_PTR)(void) = default_isr;

void isr_wrapper(void) 
{
  (*TIMER_ISR_PTR)();
}

void irq_register(void (*isr)(void)) {
  TIMER_ISR_PTR = isr;
}

void irq_unregister(void (*isr)(void)) {
  TIMER_ISR_PTR = default_isr;
}


void irq_disable_num(unsigned int num)
{
  *PIC_INTCLEAR |= irq_bit_by_num(num);
}

void irq_enable_num(unsigned int num)
{
  *PIC_INTENABLE |= irq_bit_by_num(num);
}

void PL190_init (void)
{
  *PIC_INTENABLE |= 2; // unmask interrupt bit for software interrupt
  *PIC_INTENABLE |= irq_bit_by_num(IRQ_NUM_TIMER); // enable timer irq
}


unsigned int irq_status(void)
{
  unsigned int stat;
  // Get IRQ status from the 7th bit of the CPSR register
  asm(
      "mrs     r0, CPSR\n"
      "and     %[result], r0, #0xC0"
      : [result] "=r"(stat));
  return (stat & 0b10000000) >> 7;
}

void irq_enable(void)
{
  asm(
      "mrs  r1, cpsr\n"       // (1) Read CPSR to r1
      "bic  r1, r1, #0x80\n"  // (2) Bit clear toggles 7th bit to 0
      "msr  cpsr_c, r1\n");   // (3) Write r1 to CPSR
}

void irq_disable(void)
{
  asm(
      "mrs  r0, CPSR\n"       // (1) Read CPSR to r0
      "orr  r0, #0x80\n"      // (2) Set 7th bit to 1
      "msr  CPSR, r0");       // (3) Write r0 to CPSR
}


void irq_init(void)
{
  PL190_init();
  irq_enable();
}

