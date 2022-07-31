#include "ee.h" // ErikaOS Header

TASK(Task1)
{   
    unsigned int inc = 1;
    unsigned int cycle = 1;
    SetAbsAlarm(MyAlarm, inc, cycle);   // Setzte absoluten Alarm. Zählerwert muss 1 erreichen.

    CounterTick(MyCounter);             // Erhöhe Zähler auf 1. Dies löst AlarmEvent aus und wechselt wieder zu Task 2

    TerminateTask();             
}

TASK(Task2)
{
    ActivateTask(Task1);                // Setze Task1 in Zustand Ready

    WaitEvent(AlarmEvent);              // Warte bis AlarmEvent gesetzt wird. Wechsel zu Task1

    EventMaskType mask;                 // Prüfe ob AlarmEvent für Task2 gesetzt wurde
    GetEvent(Task2, &mask);            
    if (mask & AlarmEvent)             
    {
        put_string("Finished!\n");
        TerminateTask();                // Terminiere nur, wenn AlarmEvent für Task2 gesetzt wurde
    } else {
        while(1)
        {
            (void) 0;                   // NOP
        }
    }

}

int main(void)
{
    ActivateTask(Task2);
    return 0;
}
