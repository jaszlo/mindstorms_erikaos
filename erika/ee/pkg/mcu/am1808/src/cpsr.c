#include "mcu/am1808/inc/cpsr.h"

unsigned int cpsr_status(void)
{
  unsigned int stat;
  asm(
      "mrs     %[result], CPSR\n"
      : [result] "=r"(stat));
  return stat;
}


void cpsr_write(unsigned int status) {
    asm("MSR	cpsr_c, r0");
}