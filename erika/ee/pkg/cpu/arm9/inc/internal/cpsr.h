#ifndef __INCLUDE_ARM9_CPSR__
#define __INCLUDE_ARM9_CPSR__


// Gets all status bits from CPSR register
unsigned int cpsr_status(void);

// Writes complete int to CPSR register
void cpsr_write(unsigned int status);

#endif /* __INCLUDE_ARM9_CPSR__ */