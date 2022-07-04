#include "interrupt.h"
#include "soc_AM1808.h"
#include "timer.h"
#include "evmAM1808.h"
/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define TMR_PERIOD_LSB32               (0x0000FFFF)
#define TMR_PERIOD_MSB32               (0x0)


void watchdog_trigger(void)
{
    /* Configuration of Timer */
    TimerConfigure(SOC_TMR_1_REGS, TMR_CFG_64BIT_WATCHDOG);

    /* Set the 64 bit timer period */
    TimerPeriodSet(SOC_TMR_1_REGS, TMR_TIMER12, TMR_PERIOD_LSB32);
    TimerPeriodSet(SOC_TMR_1_REGS, TMR_TIMER34, TMR_PERIOD_MSB32);

    /* Activate the Watch Dog Timer */   
    TimerWatchdogActivate(SOC_TMR_1_REGS);
}