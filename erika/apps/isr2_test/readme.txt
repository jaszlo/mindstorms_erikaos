Simple application that tests the following behaviours

    (1) ISR2 Macro works and let you assign an ISR to a timer IRQ
    (2) A Running Task is interrupted by the ISR which puts a higher priority Task in the ready state
    (3) The new ready task is activated by the calling Schedule and allows the programm to terminate