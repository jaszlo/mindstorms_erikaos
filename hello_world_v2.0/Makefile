#####################################################################################################
# Build flow 																						#
#	A: BINARY																						#
#	 (1) Create build/*.o files from src/*.c 														#
#	 (2) Link build/*.o files to "$(APP_NAME)" elf file												#
#	 (3) Create plain binary via objcopy $(APP_NAME).bin											#
#																									#
#	B: BOOT_SCRIPT																					#
#	 (1) create boot.scr from boot.cmd (practically the same file but with a binary header)			#
#																									#
#	C: Deployment																					#
#	 (1) IF boot.scr on SD_CARD THEN (2) ELSE (1.5)													#
#	 (2) Create serial port connection																#
#	 (3) Boot mindstorm																				#
#	 (4) run "make deploy" (application should start immediatly after loading into binary)			#
# ================================================================================================= #
#	 (1.5) Copy boot.scr on a FAT32 formated SD_CARD and insert into the mindstorm					#
#####################################################################################################

# Prefix of the crosscompiler
CC_PREFIX = arm-none-eabi
# Get dir of arm libraries
LIBGCCDIR = $(shell dirname $(shell $(CC_PREFIX)-gcc -print-libgcc-file-name))
# Include of the arm library dir
INCGCCDIR = $(LIBGCCDIR)/include
# Path to kermit binary/executable
WERMIT = ../erika/third_party/wermit/wermit

# How compiler will work
COMPILATION_FLAGS = -g -O2 -pipe

# How/Which warnings are to be regarded 
WARNING_FLAGS = -Wall -Wextra -Wstrict-prototypes -Werror

# Armspecific instruction like which instruction set or abi are to be used
ARM_FLAGS = -marm -mabi=aapcs-linux -march=armv5te -mno-thumb-interwork -fno-stack-protector

# How will the enviroment be on the destinatoin machine
ENVIROMENT_FLAGS = -fno-common -msoft-float -fno-builtin -ffreestanding -nostdinc

APP_NAME = mindstorm_app
BINARY = build/$(APP_NAME).bin
TARGET = build/$(APP_NAME)
SOURCES = $(shell find src -type f)
OBJECTS = $(patsubst src/%.c, build/%.o, $(SOURCES))

# Create binary and boot script
all: build/boot.scr $(BINARY)

# Create Bootscript (only has to be done once!)
build/boot.scr: $(BINARY)
	@echo MKIMAGE boot.cmd
	@mkimage -C none -A arm -T script -d boot.cmd build/boot.scr > /dev/null

# Convert elf to plain binary
$(BINARY): $(TARGET)
	@echo OBJCOPY $(TARGET)
	@$(CC_PREFIX)-objcopy -O binary $(TARGET) $(BINARY)


# Link Object file and set entry point
$(TARGET): $(OBJECTS)
	@echo LD
	@$(CC_PREFIX)-ld -o $(TARGET) -e start_up $(OBJECTS) -g -Ttext 0xC1000030 \
	 -L$(LIBGCCDIR) -lgcc --section-start=start=0xC1000000

# Crosscompile main file files
$(OBJECTS): build/%.o : src/%.c
	@mkdir -p build
	@echo CC $^
	@$(CC_PREFIX)-gcc $(COMPILATION_FLAGS) $(ENVIROMENT_FLAGS) -isystem \
	$(INCGCCDIR) $(WARNING_FLAGS) -c $^ -o $@ 

# Deploy binary to ev3 via kermit
deploy: $(BINARY)
	@echo Creating kermit script
	@echo Executing script...
	@cat kermit_upload_stub > kermit_upload
	@echo send $(BINARY) >> kermit_upload
	@echo connect >> kermit_upload
	@echo exit >> kermit_upload
	$(WERMIT) kermit_upload

clean:
	rm -rf build kermit_upload


.PHONY: clean, test, deploy
