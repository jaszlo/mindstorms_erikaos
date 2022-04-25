CC_PREFIX = arm-none-eabi-
LIBGCCDIR = $(shell dirname $(shell $(PREFIX)gcc -print-libgcc-file-name))
INCGCCDIR = $(LIBGCCDIR)/include
# How compiler will work
COMPILATION_FLAGS = -g -O2 -pipe

# How to and (which) warnings
WARNING_FLAGS = -Wall -Wextra -Wstrict-prototypes -Werror

# Armspecific instruction like which instruction set or abi
ARM_FLAGS = -marm -mabi=aapcs-linux -march=armv5te -mno-thumb-interwork -fno-stack-protector

# How will the enviroment be on the destinatoin machine
ENVIROMENT_FLAGS = -fno-common -msoft-float -fno-builtin -ffreestanding -nostdinc

# Name of the entry point lable to look for
ENTRY = start_up

GET_ENTRY_POINT = $(CC_PREFIX)objdump -d hello_world | grep '<$(ENTRY)>' | sed -n 1p | cut -d' ' -f1

boot.scr: hello_world.bin hello_world.asm
	echo "loadb 0xC1000000" > boot.cmd
	echo "go 0x$(shell grep '<$(ENTRY)>' hello_world.asm | head -n1 | cut -d' ' -f1)" >> boot.cmd
	@echo Created boot.cmd
	@echo
	mkimage -C none -A arm -T script -d boot.cmd boot.scr
	@echo Generated boot.scr from boot.cmd
	@echo


hello_world.asm: hello_world
	$(CC_PREFIX)objdump -d hello_world > hello_world.asm

# Convert elf to plain binary
hello_world.bin: hello_world
	$(CC_PREFIX)objcopy -O binary hello_world hello_world.bin
	@echo Converted to plain binary
	@echo

# Link Object file and set entry point
hello_world: hello_world.o
	$(CC_PREFIX)ld -o hello_world -e hello_world hello_world.o -g -Ttext 0xC1000000 \
	 -L$(LIBGCCDIR) -lgcc
	@echo Linked *.o files
	@echo

# Crosscompile *.c files
hello_world.o: hello_world.c
	$(CC_PREFIX)gcc $(COMPILATION_FLAGS) $(ENVIROMENT_FLAGS) -isystem \
	$(INCGCCDIR)  $(WARNING_FLAGS) -o hello_world.o hello_world.c -c	
	@echo Compiled *.c files
	@echo

deploy: hello_world.bin boot.scr
	@echo Now put boot.scr and hello_world.bin on a FAT-32 formated SD-card.
	@echo Insert the SD card into the ev3 and boot it.
	@echo 

entryaddr:
	@echo "go 0x$(shell grep '<$(ENTRY)>' hello_world.asm | head -n1 | cut -d' ' -f1)"

clean:
	rm -f *.bin *.o *.src *.cmd *.asm *.log hello_world


.PHONY: clean, test
