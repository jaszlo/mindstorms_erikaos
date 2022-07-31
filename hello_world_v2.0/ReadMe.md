# Hello world on Mindstorm but better!
The files in this folder will allow to run a simple hello world on the Mindstorm via a UART.
But also allow a more complex file structure for development as well as easier deployment using kermit

## Setup and execution
Requires sensor port 1 to be used as a a serial port. How this is done is explained [here](https://botbench.com/blog/2013/08/15/ev3-creating-console-cable/)

For compilation two dependencies are required. The `gcc-arm-none-eabi` crosscompiler and the u-boot-util `mkimage`
Those can be installed (on Ubuntu) as follows.
```sh
chmod u+x configure.sh && ./configure.sh
```

In addition some hand on changes might be required in the `kermit_upload_stub` as well as in the `Makefile`.
You need to specify the line of the serial port if it differs on your machine.
Also you need to make sure you are have acces to that line.

To compile the `hello_world.c` simply run `make`. This will create the build directory with some files of which `mindstorm_app.bin` and `boot.scr` are relevant. You can change the name of your binary via the makefile variable `APP_NAME`.

For easier deployment `Kermit` is used which allows us to deploy the binary using the UART.
To do so the `boot.scr` needs to be put on the sd-card **once**.

That will ensure that when booting the script will wait for a binary via the serial port and load it into memory. Afterwards the `boot.scr` will go to the fixed entry point `start_up`. 
To ensure that the function `start_up` will always have the same address. This was done by creating a new segment `start` and telling the linker at which address he should put that specific segment.

In order to deploy after booting and a setup serial port use
```sh
make deploy
```
This should upload your binary and it should immediatly start running after kermit is finished.
Make that the serial connection has been established before calling `make deploy`.

On success the resulting output should look like the follwing
```sh
Creating kermit script
Executing script...
../erika/third_party/wermit/wermit kermit_upload
Connecting to /dev/ttyUSB0, speed 115200
 Escape character: Ctrl-\ (ASCII 28, FS): enabled
Type the escape character followed by C to get back,
or followed by ? to see other options.
----------------------------------------------------
## Total Size      = 0x0000026e = 622 Bytes
## Start Addr      = 0xC1000000
## Starting application at 0xC1000000 ...

Hallo Welt!

## Application terminated, rc = 0x0
U-Boot >
```

## Redeploymenet
In order to contionusly deploy new versions of your software you can now just enter `reset` into the serial U-Boot terminal after your proramm was finished which will reboot the mindstorm. It will again start boot.scr and wait for a file to be sent via kermit. If successful the output should look similiar to this
```sh
reading boot.scr

103 bytes read
## Executing script at c0600000
## Ready for binary (kermit) download to 0xC1000000 at 115200 bps...
``` 
You can now exit via the Kermit escape sequence (Ctrl+\\+C or Ctrl+]+C) also might differ depending on kermit version).
Make the changes you want to make to your source files. Call `make all` and then `make deploy` and the new binary should be uploaded and executed. 

# Further development
This is a barebones enviroment where nothing is prepared and you load go from the bootloader straight into your main. The only step in between is the fixed entry point i.e the `start_up` function.
In theory any .c file in the src folder should compile with the others just fine and the result will always be a single binary.
