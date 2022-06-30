# First ErikaOS Application

## Folders
| Folder name  | Contains                                                                                                                     |
|--------------|------------------------------------------------------------------------------------------------------------------------------|
| apps         | Test application created during the development process of ther ErikaOS Arm9 Port for both `AM1808` and `versatilepb` (qemu) MCU |
| comp         | A folder showcasing an error with RT-Druid to not generate information about the preemptibility of tasks                     |
| dissassembly | Will be generated when building an application an contain disassembly of code and all section as well as a map file          |
| ee           | Source and build files for ErikaOS                                                                                           |
| testcase     | Testcases used by ErikaOS to validate a port. Contains some selected and imported MODISTARC testcases                        |
| third_party  | Third party tools required for development (RT-Druid for OIL-compilation and C-Kermit for binary deployment)                 |


## MCUs
The port supports ErikaOS for ARM9 for two sepperate CPUs. First the `AM1808` which is the MCU used in the ev3 Mindstorm.
Secondly it supports the `versatilepb` MCU to some extend. It was used during development as QEMU can emulated this MCU.
Note that in order to run this port on a real world `versatilepb` changes will be required as it knowingly abuses that some things
may work on QEMU that would not work on the real MCU.
An example for this would be the put_char function for the UART which does not check if we can write to the UART buffer but simply does it
as this leads to no problems in QEMU and was a simpler implementation.

## AM1808
The following steps showcase how to build and run your ErikaOS application on the ev3 Mindstorm i.e. `AM1808`

### Building my first application (AM1808)
To compile your first ErikaOS application a few build-tools are required to be available on your machine you're developing on.
That includes `arm-none-eabi-gcc`, `u-boot-tools` and `wermit` better known as `C-Kermit` from the third_party folder.
To install and compile those dependencies simply call
```sh
chmod u+x configure.sh && ./configure.sh
```

That should have installed all required tools. In order to build your first binary, call the following from the folder of this readme.
```
make compile_test
```
There are multiple application testing various behaviour of the ErikaOS port which were created during development of the Port. 
You should start with the basic compilation test that just uses UART to test all print functions provided by the ee_io.h in the ARM9 cpu folder.
To build any of the other application simply call make with the app name as the target name.
All apps that can be build this way are contained in the `apps/am1808` folder.
```sh
make <app_name>
```

### Deploying the application (AM1808)
Boot the mindstorm and call
```sh
make deploy
```
Make sure you are part of the dialout group or this will fail.
This will deploy the application from the `am1808_ee_app_<app_name>` folder.

## AM1808
The following steps showcase how to build and run your ErikaOS application on the QEMU i.e. `versatilepb`.
It also showcases how to use GDB to debug them.

### Building and running my first application (versatilepb)
Note that besides `arm-none-eabi-gcc`, `u-boot-tools` and `wermit`m `qemu-system-arm`is also required to be installed.
This should be the case if the configure script was ran. 

In order to build and run your first binary, call the following from the folder of this readme.
```
make qemu_run APP=compile_test
```
There are multiple application testing various behaviour of the ErikaOS port which were created during development of the Port. 
You should start with the basic compilation test that just uses UART to test all print functions provided by the ee_io.h in the ARM9 cpu folder.
To build any of the other application simply call make with the app name as the target name.
All apps that can be build this way are contained in the `apps/versatilepb` folder.
```sh
make qemu_run APP=<app_name>
```
To terminate QEMU use [`Ctrl + a + x`].


### Debugging my Application with GDB
All application for the QEMU i.e. `versatilepb` are build using `-g` creating debug informatoin. Therefore we can use QEMU with GDB to debug our applications.
This is done by holding QEMU and not starting it immediately.
You will be required to have to seperate terminals open. From the first one start qemu.
```sh
make qemu APP=<app_name>
```
From the seond on start gdb

```sh
make gdb
```
This runs gdb with an init script that will connect you directly to the QEMU. You can also modify it yourself to set default breakpoints etc.
The file used is `.gdb_init`