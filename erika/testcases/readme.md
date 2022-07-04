# Test Suite Structure:

Tests will be classified according to the following service groups:
• Task management
• Interrupt processing
• Event mechanism
• Resource management
• Alarms
• Error handling, hook routines and OS execution control (including start-up/shutdown of OS).

Additional test variance is created through the following categories:
* Conformance class:
    - BCC1 
    - BCC2 
    - ECC1 
    - ECC2 
* Scheduling policy:
    - non-preemptive
    - mixed-preemptive
    - full-preemptive

The Testcases are specified [here](https://www.osek-vdx.org/mod_20/ostestplan20.pdf).
The numbers correspond to the testcase number in that document. Note that if a number is missing from the testcases here
Some of the testcases only exists for the ECC1 or BCC2 and ECC2 conformance class and therefore will only be found in their correpsonding folder.

### Excluded Tests and additional information
The following task management tests are only available in the ecc2/bcc2 folder because they test BCC2 and ECC2 specific behaviour
* 5
* 12, 13, 14
* 17, 18
* 32

In addition ErikaOS does not provide the following API-Calls. 
* EnableInterrupt()
* DisableInterrupt()
* GetInterruptDescriptor()

Instead Enable/Disable behaviour will be tested via the ARM9 specific functions EE_irq_enable, EE_irq_disable, EE_irq_status.
This means that modistarc interrupt 1 to 5 are not the same as specified but still test similiar bevahiour.
Also we do not support nested interrupts and this means interrupt test 7 and 8 are missing.

When reading the testcases source code note that some testcases have the exact same code but they test different behaviour as the OIL files differ.

## Running the testcases

(1) Connect the UART dongle
(2) Start the ev3 Mindstorm
(3) Make sure C-Kermit is compiled and python installed
(4) Call `make modistarc` Check stdout or modistarc_results file for testcase results

Note: Compilation will take a while!