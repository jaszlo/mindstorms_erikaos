Simple application that tests the following behaviours

    (1) Multiple mulitstack and monostack task can coexist and schedule each other
    (2) A higher priority task can switch to a lower priority ready task via WaitEvent
    (3) An Alarm triggers a timer event which reschedules to the higher priority task