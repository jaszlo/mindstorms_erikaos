# Hello world on Mindstorm
The files in this folder will allow to run a simple hello world on the Mindstorm via a UART serial port.

## Setup
Requires sensor port 1 to be used as a a serial port. How this is done is explained [here](https://botbench.com/blog/2013/08/15/ev3-creating-console-cable/)

For compilation two dependencies are required. The `gcc-arm-none-eabi` crosscompiler and the u-boot-util `mkimage`
Those can be installed (on Ubuntu) as follows.
```sh
chmod u+x configure.sh && ./configure.sh
```

To compile the `hello_world.c` simply run `make`. This will create the following files `hello_world.asm hello_world.bin hello_world.o boot.cmd boot.scr` of which only `hello_world.bin` and `boot.scr` are relevant for execution.

## Execution
In order to run the hello world program it is required to have a 32-FAT formatted sd-card on which `boot.scr` and `hello_world.bin` are coppied.
Then after inserting and booting Mindstorm the serial console should read like the following.
```
[...]
60 bytes read
## Starting application at 0xC10000BC ...
Hello World!
## Application terminated, rc = 0x1
U-Boot >
``` 
