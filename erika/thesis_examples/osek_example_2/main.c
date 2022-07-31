#include "ee.h" // ErikaOS Header

volatile unsigned int isr_fired = 0;

ISR2(timer_handler)
{
    isr_fired = 1;
}

TASK(Task1) 
{
    while (isr_fired == 0)              // Warte bis Interrupt passiert und abgeschlossen ist
    { 
    
        (void) 0;                       // Nop 
    }
    put_string("Finished!\n");
    TerminateTask();
}

int main(void)
{
    const unsigned int channel = 2;
    const unsigned int period = 0x100000; 

    EE_timer_init(period, channel);
    EE_timer_start();
    ActivateTask(Task1);                // Kann nur terminieren wenn Interruptroutine aufgerufen wird.
    return 0;
}
