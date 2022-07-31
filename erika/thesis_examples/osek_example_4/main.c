#include "ee.h" // ErikaOS Header

unsigned int task2_started = 0;

TASK(Task1)
{
    GetResource(RES_SCHEDULER);         // Sperre den Scheduler

    ActivateTask(Task2);                // Versetzte Task mit höherer Priorität in Zustand Ready
                                        // Da Task1 preämptiv ist wäre hier normalerweise ein Kontextwechsel zu Task2

    while(task2_started)                // Prüfe ob Task2 schon gelaufen ist, was nicht der fall sein sollte.        
    {                                   // Ist dies der Fall ist etwas schief gelaufen und wir terminieren nie.
        (void) 0;                       // NOP
    }

    ReleaseResource(RES_SCHEDULER);     // Gebe den Scheduler frei. Damit wird an dieser Stelle zu Task2 gewechselt.
    TerminateTask();
}

TASK(Task2)
{
    task2_started = 1;
    put_string("Finished!\n");
    TerminateTask();
}

int main(void)
{
    ActivateTask(Task1);
    return 0;
}
