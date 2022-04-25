CC_PREFIX = arm-none-eabi-
LIBGCCDIR = $(shell dirname $(shell $(PREFIX)gcc -print-libgcc-file-name))
INCGCCDIR = $(LIBGCCDIR)/include
WERMIT = third_party/wermit/wermit

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

TARGET = build/start_up
SOURCES = $(shell find src -type f)
OBJECTS = $(patsubst src/%.c, build/%.o, $(SOURCES))

build/boot.scr: $(TARGET).bin $(TARGET).asm
	echo "loadb 0xC1000000" > build/boot.cmd
	echo "go 0x$(shell grep '<$(ENTRY)>' $(TARGET).asm | head -n1 | cut -d' ' -f1)" >> build/boot.cmd
	@echo Created boot.cmd
	@echo
	mkimage -C none -A arm -T script -d build/boot.cmd build/boot.scr
	@echo Generated boot.scr from boot.cmd
	@echo

# Build single asm file to get
$(TARGET).asm: $(TARGET)
	$(CC_PREFIX)objdump -d $(TARGET) > $(TARGET).asm

# Convert elf to plain binary
$(TARGET).bin: $(TARGET)
	$(CC_PREFIX)objcopy -O binary $(TARGET) $(TARGET).bin
	@echo Converted to plain binary
	@echo

# Link Object file and set entry point
$(TARGET): $(OBJECTS)
	$(CC_PREFIX)ld -o $(TARGET) -e $(ENTRY) $(OBJECTS) -g -Ttext 0xC1000030 \
	 -L$(LIBGCCDIR) -lgcc --section-start=start=0xC1000000
	@echo Linked *.o files
	@echo

# Crosscompile main file files
$(OBJECTS): build/%.o : src/%.c
	@mkdir -p build
	$(CC_PREFIX)gcc $(COMPILATION_FLAGS) $(ENVIROMENT_FLAGS) -isystem \
	$(INCGCCDIR) $(WARNING_FLAGS) -c $^ -o $@ 
	@echo Compiled $(SOURCES)
	@echo

# Deploy binary to ev3 via kermit
deploy: $(TARGET).bin
	sudo $(WERMIT) kermit_upload

# Debug option to print entry address. Requires .asm to be build first
entryaddr:
	@echo "go 0x$(shell grep '<$(ENTRY)>' $(TARGET).asm | head -n1 | cut -d' ' -f1)"

clean:
	rm -rf build


.PHONY: clean, test, deploy
