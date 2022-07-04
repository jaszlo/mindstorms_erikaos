## Why are these testcases in a seperate folder?

The testcases in this folder are different because some of them wont terminate i.e. reset via the watchdog.
This is because the API call ShutdownOS by ErikaOS is not supposed reset the device but hold it in a defined state.
In order to test this behaviour these specific testcases might not reset the device and therefore cannot be run with the
other automated testcase.