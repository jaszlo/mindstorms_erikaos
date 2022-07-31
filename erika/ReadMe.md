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
The port supports ErikaOS for ARM9 for two sepperate MCUs. First the `AM1808` which is the MCU used in the `EV3 Mindstorm`.
Secondly it supports the `versatilepb` MCU to some extend. It was used during development, as QEMU can emulated this MCU. The `versatilepb` by itself is actually a board and not a MCU but is handled as such.
Note that in order to run this port on a real world `versatilepb` changes are required as it knowingly abuses the fact that some things may work on QEMU that would not work on the real hardware.
An example for this would be the put_char function for the UART which does not check if we can write to the UART buffer but simply does it as this leads to no problems in QEMU and was a simpler implementation.

## AM1808
The following steps showcase how to build and run your ErikaOS application on the `ev3 Mindstorm` i.e. `AM1808`

### Building my first application (AM1808)
To compile your first ErikaOS application a few build-tools are required to be available on your machine.
That includes `arm-none-eabi-gcc`, `u-boot-tools`, `wermit` better known as `C-Kermit` and RT-Druid.
To install and compile those dependencies simply call the configure script.
Note that JRE version 1.8 (java8) is also required but is not installed by the configure script.
```sh
chmod u+x configure.sh && ./configure.sh
```

That should have installed all required tools. In order to build your first binary, call the following from the folder of this readme.
```
make compile_test
```
There are multiple application testing various behaviour of the ErikaOS port which were created during development of the Port. 
To build any of the other application simply call `make` with the app name as the target name.
All apps that can be build this way are contained in the `apps/am1808` folder.
```sh
make <app_name>
```

### Deploying the application (AM1808)
In order for the deployment via C-Kermit to work the boot.scr file that can be found at `erika/boot.scr` needs to be put on an the FAT32 formatted sd-card used in the EV3 Mindstorm. Then boot the Mindstorm and connect the UART with your machine and run the following.
```sh
make deploy
```
This deployment process is described in more detail in `hello_world_v2.0/ReadMe.md`.
Make sure you are part of the dialout group or this will fail. Also note that the last application you build will be the application that is going to be deployed. For further detail read the Makefile targets `%:` and `deploy`. This will deploy application from the folder `apps/am1808`.

### Creating a new application (AM1808)
For this copy an existing folder of an application such as `apps/am1808/compile_test`. Lets say the new folder is named `my_application`. Leave the makefile unmodified and change the main.c conf.oil according to your needs. The sourcefiles of your application are specified via the conf.oil file.
Now in order to compile your application use the following command.
```sh
make my_application
```
Deployment works as described above.


## versatilepb
The following steps showcase how to build and run your ErikaOS application for the QEMU i.e. `versatilepb`.
It also showcases how to use GDB to debug them.

### Building and running my first application (versatilepb)
Note that besides `arm-none-eabi-gcc`, `u-boot-tools` and `wermit`, `qemu-system-arm` is also required to be installed.
This should be the case if the configure script was ran. 

In order to build and run your first binary, call the following from the folder of this readme.
```
make qemu_run APP=compile_test
```
There are multiple application testing various behaviour of the ErikaOS port which were created during development of the Port. 
You should start with the basic compilation test that just uses UART to test all print functions provided by the `ee_io.h` in the ARM9 cpu folder.
To build any of the other application simply call make with the app name as the target name.
All apps that can be build this way are contained in the `apps/versatilepb<app_name>` folder.
```sh
make qemu_run APP=<app_name>
```
To terminate QEMU use [`Ctrl + a + x`].


### Debugging my Application with GDB
All application for the QEMU i.e. `versatilepb` are build using `-g` creating debug informatoin. Therefore we can use QEMU with GDB to debug our applications.
This is done by holding QEMU and not starting it immediately.
You will be required to have two seperate terminals open. From the first one start qemu.
```sh
make qemu APP=<app_name>
```
From the seond on start gdb

```sh
make gdb
```
This runs gdb with an init script that will connect you directly to the QEMU. You can also modify it yourself to set default breakpoints etc. The file used is `.gdb_init`. You will also be required to remove the first line of the

### Creating a new application (versatilepb)
For this copy an existing folder of an application such as `apps/versatilepb/compile_test`. Lets say the new folder is named `my_application`. Leave the makefile unmodified and change the main.c conf.oil according to your needs. The sourcefiles of your application are specified via the conf.oil file.
Now in order to compile and run your application use the following command.
```sh
make qemu_run APP=my_application
```

## Continuing with development

All relevant source files can be found in the following folders

| Folder                     | Description                                                                                 |
|----------------------------|---------------------------------------------------------------------------------------------|
| ee/pkg/cpu/arm9            | Contains CPU specific code that should work for all MCUs with the same ARM9 CPU             |
| ee/pkg/mcu/am1808          | Contains MCU specific code for the `AM1808` Perepheri like the Interrupt handling etc.      |
| ee/pkg/mcu/versatilepb     | Contains MCU specific code for the `versatilepb` Perepheri like the Interrupt handling etc. |
| ee/pkg/board/ev3_mindstorm | Contains board specific code for the `ev3 Mindstorm` board using the `AM1808` MCU           |

If you want to add any new source file it will be required to be added to the Makefile variable `EE_SRC`.
You can do this in the `cfg.mk` files that can be found in the `cfg` folder of the `cpu/arm9`, `mcu/am1808`, etc. folders.

### What can be added or imporved?

* More hardware: Additional drivers for the AM1808 and versatilepb

* More Mindstorm support: More drivers for the EV3 Mindstorm

* Additional Board and MCUs support

* Optimizing time critical functions like the context switch or interrupt 


## Thesis Examples
The thesis examples can be run similiar to the qemu target to build a thesis example application run the following
```sh
make thesis_example APP=osek_example_<example_number>
```

For deployment again use the following.
```sh
make deploy
```


## MODISTARC testcase
For more information on the testsuite see [here](./testcases/readme.md)