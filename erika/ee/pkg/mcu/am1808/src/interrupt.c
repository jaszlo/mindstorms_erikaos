#include "mcu/am1808/inc/interrupt.h"
#include "mcu/am1808/inc/timer.h"

// Internal function definition

// ISR in ram used by irq_handler
static void (*isr_vector[NUM_INTERRUPTS])(void);

void reset_handler(void); // Implemented in ee_startup.S

static void aintc_init(void)
{

  /**
   * Information about Registers of the AINTC (ARM Interrupt Controller) 
   * @Source: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=290
   */
  *AINTC_SECR1 = 0xFFFFFFFF; // (1) Clear current interrupts
  *AINTC_GER = GER_ENABLE;   // (2) Enable global interrupts
  *AINTC_HIER |= HIER_IRQ;   // (3) Enable only IRQ interrupt line (not FIQ)s
                             //     0-1 are FIQ channels, 2-31 are IRQ channels, lower channels have higher priority


  // Set isr_vector Address to VBR 
  *AINTC_VBR = (unsigned int)isr_vector;

  //Declare ISR Size Function Pointer = 4 bytes
  *AINTC_VSR = 0x0;
}

static void default_isr(void) 
{
  while (1);
}

/**
 * MRS instruction moves regsiter from CP15 register to CPU register.
 * In this case the CPSR (Current Programm Status Register) which contains the IRQ flag.
 * MSR instruction moves register from CPU to CP15 register.
 * @Source (MRS): https://developer.arm.com/documentation/dui0489/c/arm-and-thumb-instructions/coprocessor-instructions/mrs
 * @Source (CPSR): https://developer.arm.com/documentation/ddi0406/b/System-Level-Architecture/The-System-Level-Programmers--Model/ARM-processor-modes-and-core-registers/Program-Status-Registers--PSRs-
 */
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

void irq_register(unsigned int num, void (*isr)(void))
{
  isr_vector[num] = isr;
}

void irq_unregister(unsigned int num)
{
  isr_vector[num] = default_isr;
}


/*
** These functions (irq_clear_status/irq_enable_num/irq_disable_num) assume that the SECRn/ESRn are continuous in memory.
*/
void irq_clear_status(unsigned int num)
{
 /**
   * Write single bit corresponding with IRQ-number to SECRn (System Interrupt Status Enabled/Clear Register n)
   * to clear IRQ flag for specific IRQs and allow new interrupts to be handled
   * @Source: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=301
   */
  volatile unsigned int *status_reg = AINTC_SECR1;

  unsigned int reg_nr =  num / 32;
  *(status_reg + reg_nr) |= irq_bit_by_num(num);
}

void irq_enable_num(unsigned int num)
{
  /**
   * Write single bit corresponding with IRQ-number to ESRn (system interrupt Enable Set Register n)
   * to enable specific IRQs.
   * @Source: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=303
   */
  volatile unsigned int *enable_reg = AINTC_ESR1;

  unsigned int reg_nr =  num / 32;
  *(enable_reg + reg_nr) |= irq_bit_by_num(num);
}

void irq_disable_num(unsigned int num)
{
  /**
   * Write single bit corresponding with IRQ-number to ECRn (system interrupt Enable Clear Register n)
   * to disable specific IRQs.
   * @Source: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=305
   */
  volatile unsigned int *disable_reg = AINTC_ECR1;

  unsigned int reg_nr =  num / 32;
  *(disable_reg + reg_nr) |= irq_bit_by_num(num);
}


/*
** These functions (irq_set/get_channel assume that the CMRs are continuous in memory and are
** byte accessible. 
*/
void irq_set_channel(unsigned int num, unsigned int channel)
{
    /**
     * Map specific IRQ (number) to one for 32 channels. (0-1 FIQ, 2-31 IRQ)
     * @Source (CMRn): https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=307
     * @Source (Channel Mapping): https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=287
     */
    volatile unsigned char *CMRByte = (char *)AINTC_CMR0;
    CMRByte += num;
    *CMRByte = channel;
}

unsigned int irq_get_channel(unsigned int num)
{
  volatile unsigned char *CMRByte = (char *)AINTC_CMR0;
  CMRByte += num;
  return (*CMRByte);
}


/**
 * These functions asume to be used within an ISR i.e. the IRQ status is not cleared in the AINTC.
 * This is due to the fact that the AINTC_HIPIR2 register is read in order to get the number of the interrupt
 * currently being handled.
 * @Source: https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf#page=308
 */
unsigned int irq_get_current_num(void) 
{
  /*
    ldr      r0, =AINTC_HIPIR2
    ldr      r0, [r0]  // r0 now contains the number of the IRQ currently proccesed.
  */
   unsigned int inum;
   asm (
    "ldr r0, =%0\n"
    "ldr r0, [r0]\n"
    :
    : "i" (AINTC_HIPIR2)
    :
  );
  asm(
      "mov     %[result], r0"
      : [result] "=r"(inum));
  return inum;
}

unsigned int irq_get_current_channel(void)
{
  irq_get_channel(irq_get_current_num());
}


void irq_init(void)
{
  irq_disable();
  aintc_init();
  irq_enable();
}
