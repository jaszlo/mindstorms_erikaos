#include "ee.h" // ErikaOS Header

#define INVALID_TASK_ID 1234

void StartupHook(void)
{
    put_string("StartupHook\n");     // Mache etwas beim starten des Betriebsystem
}

void PreTaskHook(void) 
{
    put_string("PreTaskHook\n");    // Mache etwas for dem starten einer Task
}

TASK(Task1)
{
    ActivateTask(INVALID_TASK_ID);  // Provuziere einen Fehler, welcher die ErrorHook ausführt.
    TerminateTask();
}

void ErrorHook(StatusType Error)
{
    put_string("ErrorHook\n");      // Mache etwas wenn ein Systemfehler auftritt
}

void PostTaskHook(void) 
{
    put_string("PostTaskHook\n");   // Mache etwas wenn eine Task terminiert
}


void ShutdownHook(StatusType Error)
{
    put_string("ShutdownHook\n");   // Mache etwas wenn Systemrunterfährt
}

int main(void)
{
    ActivateTask(Task1);     
    ShutdownOS(E_OS_ID);            // Soll nur aufgerufen werden, wenn ein Fehler passiert. E_OS_ID ist ein Fehlertyp der hier willkürlich gewählt wurde.
    return 0;
}