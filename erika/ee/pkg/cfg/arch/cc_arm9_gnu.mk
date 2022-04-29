################
#
# Select file formats
#
CG_OUT_EXTENSION := elf
# MM: Check!!!
CG_BIN_EXTENSION := bin

#
# Define crosscompiler EABI_GCC_PREFIX, EABI_GCC_EXT and EABI_GCC_VERSION
# if required. 
# As version and .exe are not used for the name of the executable
# version and ext are not set. Windows build support is not in the making!
# 
EABI_GCC_EXT := 
EABI_GCC_VERSION := 
EABI_GCC_PREFIX := arm-none-eabi


# Set base for arm libraries
CG_LIB_DIR = $(shell dirname $(shell $(EABI_GCC_PREFIX)-gcc -print-libgcc-file-name))

# Set include dir from library
CG_INCLUDE_DIR := $(CG_LIB_DIR)/include


# Not yet sure why this is required
# TODO: Understand?
ifdef TMPDIR
CG_TMPDIR := $(call native_path, $(TMPDIR))
else
CG_TMPDIR := $(call native_path, .)
endif

# Folder needs to contain gcc, ld, objcopy and objdump with arm-none-eabi prefix
BINDIR_CC = /usr/bin


# Define crosscompiler tools
# To simplify things we will ALWAYS specify these terms via this makefile and not enviromental variables
EE_CC := $(BINDIR_CC)/$(EABI_GCC_PREFIX)-gcc

EE_ASM := $(BINDIR_CC)/$(EABI_GCC_PREFIX)-gcc

EE_LINK := $(BINDIR_CC)/$(EABI_GCC_PREFIX)-ld

EE_OBJCOPY := $(BINDIR_CC)/$(EABI_GCC_PREFIX)-objcopy

EE_OBJDUMP := $(BINDIR_CC)/$(EABI_GCC_PREFIX)-objdump

EE_AR := $(BINDIR_CC)/$(EABI_GCC_PREFIX)-ar


################
#
# Add application file to dependencies
#
ifneq ($(ONLY_LIBS), TRUE)
## OPT_LIBS is used to link additional libraries (e.g., for C++ support)
OPT_LIBS += $(ERIKALIB)
TARGET = $(TARGET_NAME).$(CG_BIN_EXTENSION)
endif	# !ONLY_LIBS



################
#
# INCLUDE_PATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
OPT_INCLUDE = $(foreach d,$(INCLUDE_PATH),$(addprefix -I,$(call native_path,$d)))



################
#
# Compiler flags for arm architecture
# Compiler flags for the enviroment that the code will run
# Compiler flags for warnings
#
OPT_CC += -Os
OPT_CC += -marm -mabi=aapcs-linux -march=armv5te -mno-thumb-interwork -fno-stack-protector
OPT_CC += -fno-common -msoft-float -fno-builtin -ffreestanding -nostdinc
# Fixes this: obj/main.o uses 32-bit enums yet the output is to use variable-size enums; use of enum values across objects may fail
#	and this: libgcc.a(_udivmoddi4.o) uses variable-size enums yet the output is to use 32-bit enums; use of enum values across objects may fail
OPT_CC += -fshort-enums 
#OPT_CC += -Wall -Wextra -Wstrict-prototypes -Werror

# Compile and assemble, but do not link 
OPT_CC += -c 

# Specific option from the application makefile. Not used here probably
OPT_CC += $(CFLAGS)


################
#
# Linker flags 
#	Add LibGCC
#	Set where in memory the textsegment starts
#	Set the entry point lable
export LIB_GCC_LINK = -L$(CG_LIB_DIR) -lgcc
OPT_LINK += -Ttext 0xC1000030
OPT_LINK += -e start_up -g
OPT_LINK += --section-start=start=0xC1000000

# Specific option from the application makefile
OPT_LINK += $(LDFLAGS)


# Option for arm-none-eabi-ar to handle libee.a 
OPT_AR = r

OPT_ASM = -march=armv5te -mno-thumb-interwork -c

################
#
# Create defines for assembler compilation
# Create defines for C compilation
#
DEFS_ASM = $(addprefix -D, $(EEOPT))
DEFS_CC  = $(addprefix -D, $(EEOPT))


################
#
# Options for library generation
#
OPT_OBJCOPY += -Obinary


# Automatic dependency generation, Probably not used again
ifeq ($(call iseeopt, NODEPS), yes)

DEPENDENCY_OPT = 
make-depend =

else # NODEPS

DEPENDENCY_OPT = -MMD -MF $(subst .o,.d_tmp,$@) -MP -MT $@
make-depend = mv $3_tmp $3
endif # NODEPS




test:
	@echo $(OPT_LINK)