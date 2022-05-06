# First ErikaOS Application

## Folders
There are quite a few folders. Here is what their are used for:
|Folder-Name | Contains ...|
|------------|-------------|
|am1808_ee_app_<app_name> | ... the source code of the erikaOS application as well as the makefile to build them|
|cortex_mx_porting_examples | ... examples of stepwise increasingly difficult erikaOS application that require the port to include more and more of erikaOS' functionality|
|ee | ... source of erikaOS but reduced to only common and the arm9 port as well as avr8 and cortex_mx for crossreference|
|third_party | ...third party tools required for development and deployment (rt_druid and kermit)|

## Building my first application
To compile your first erikaOS application a few build-tools are required to be available on your machine.
That includes `arm-none-eabi-gcc`, `u-boot-tools` and `wermit` from the third_party forlder.
To install and compile those dependencies simply call
```sh
chmod u+x configure.sh && ./configure.sh
```

That should have installed all required tools. In order to build your first binary call
```
make compile_test
```
in the folder erika (folder of this readme).
There are multiple application testing various behaviour of the erikaOS port. You should start with the basic compilation test that just uses UART to test all print functions provided by the debug_io.h
To build any of the other application simply cann
```sh
make <app_name>
```

If you just call `make` the `compile_test` application is set as the target by default. This will also be your deploy target. In order to switch which target to build and deploy by default call
```sh
export EE_TARGET=<app_name>
```

# Deploying the application
Boot the mindstorm and call
```sh
make deploy
```
Make sure you are part of the dialout group or this will fail.
This will deploy the application from the `am1808_ee_app_<app_name>` folder.