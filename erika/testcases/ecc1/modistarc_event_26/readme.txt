Simple application that tests the following behaviours

    (1) ISR2 Macro works and lets you assign an ISR to the timer interrupt
    (2) A Running Task is interrupted by the timer interrupt which puts a higher priority Task in the ready state
    (3) The new ready task is activated by calling Schedule and allows the programm to terminate