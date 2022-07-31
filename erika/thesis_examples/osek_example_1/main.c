#include "ee.h" // ErikaOS Header

unsigned int task1_started = 0;

TASK(Task1) 
{
    task1_started++;
    if (task1_started <= 10)
    {
        put_uint(task1_started);__nl;   // Gebe aus wie vielte Aktivierung (__nl = newline Macro)
        ChainTask(Task1);               // Terminiere und Starte Task1 zehn mal neu
    } else {
        put_string("Finished!\n");
        TerminateTask();                // Terminiere Task1 endgültig
    }
}

int main(void)
{
    ActivateTask(Task1);
    return 0;
}
