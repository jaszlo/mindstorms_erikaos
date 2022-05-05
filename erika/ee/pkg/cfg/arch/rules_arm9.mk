# Enable verbose output from EE_OPT
ifeq ($(call iseeopt, VERBOSE), yes)
VERBOSE = 1
endif

# ErikaOS will compile into this libee.a
ERIKALIB = libee.a

# Initial definition of target all as predefined
all:
include $(EEBASE)/pkg/cfg/dir.mk 	# sets name of dirs 
include $(PKGBASE)/cfg/verbose.mk   # specifies some output variables and so on
include $(PKGBASE)/cfg/compiler.mk 	# sets which cc_*.mk file is used to set compiler settings

ifneq ($(ONLY_LIBS), TRUE)

ifneq ($(call iseeopt, __BIN_DISTR), yes)
LIBDEP += $(ERIKALIB)
else
LIBDEP += $(EEBASE)/lib/$(ERIKALIB)
endif

endif	# ONLY_LIBS

# Includes from Compiler
INCLUDE_PATH += $(CG_INCLUDE_DIR)

# Required for limits.h
INCLUDE_PATH += $(CG_LIB_DIR)/include-fixed

# Includes all cfg.mk in collector cfg.mk
include $(PKGBASE)/cfg/cfg.mk



# Check if MCU is specified for AM1808
ifeq ($(call iseeopt, __AM1808__), yes)
ARM9_MCU_MODEL = AM1808

# No MCU model
ifndef ARM9_MCU_MODEL
$(error No known MCU model found in EE_OPT)
endif
endif

# Might be used later when actuall boot code is present
# Boot code containing _start should stay outside of the library in
# case of normal compilation
#ifeq ($(call iseeopt, __BIN_DISTR), yes)
#LIBSRCS += $(EE_BOOT_SRCS)
#else
#SRCS += $(EE_BOOT_SRCS)
#endif

# Should not be the case as we always want to compile a application
ifeq ($(call iseeopt, __NO_APP__), yes)
TARGET := $(ERIKALIB)

# we put the eecfg.c inside the library
LIBEESRCS += eecfg.c

endif


################
#
# Source files and paths
#
LIBEESRCS += $(EE_SRCS)
LIBEEOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(patsubst %.s, %.o, \
$(patsubst %.asm, %.o, $(patsubst %.S, %.o, $(LIBEESRCS))))))

LIBOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(patsubst %.s, %.o, \
$(patsubst %.asm, %.o, $(patsubst %.S, %.o, $(LIBSRCS))))))

SRCS += $(APP_SRCS)

OBJS := $(addprefix $(OBJDIR)/, $(sort $(patsubst %.cpp, %.o, \
$(patsubst %.cxx, %.o, $(patsubst %.cc, %.o, $(patsubst %.C, %.o, \
$(CXX_SRCS))))) $(patsubst %.c, %.o, $(patsubst %.s, %.o, \
$(patsubst %.asm, %.o, $(patsubst %.S, %.o, $(SRCS)))))))

# Variable used to import dependencies
ALLOBJS = $(LIBEEOBJS) $(LIBOBJS) $(OBJS) 

OBJDIRS=$(sort $(dir $(ALLOBJS)))

INCLUDE_PATH += $(PKGBASE) $(call short_native_path,$(APPBASE)) . $(CG_INLCUDE_DIR)

vpath %.c $(EE_VPATH) $(APPBASE)
vpath %.s $(EE_VPATH) $(APPBASE)
vpath %.S $(EE_VPATH) $(APPBASE)
vpath %.asm $(EE_VPATH) $(APPBASE)

## Compute common variables ##
COMPUTED_INCLUDE_PATH := $(OPT_INCLUDE)
COMPUTED_OPT_LINK := $(OPT_LINK)
COMPUTED_OPT_ASM := $(OPT_ASM)
COMPUTED_OPT_CC := $(OPT_CC)
COMPUTED_OPT_AR := $(OPT_AR)
COMPUTED_OPT_OBJDUMP := $(OPT_OBJDUMP)
COMPUTED_OPT_OBJCOPY := $(OPT_OBJCOPY)
COMPUTED_OPT_FROMELF := $(OPT_FROMELF)




ifeq ($(call iseeopt, __GNU__), yes)

SOURCEFILE = $(call native_path,$<)
else	# __GNU__

SOURCEFILE = $(call short_native_path,$(dir $<))\\$(notdir $<)
endif	# !__GNU__

TARGETFILE = $(call native_path,$@)

 

## Main rules: all clean ##
.PHONY: all clean

all: make_directories $(ALL_LIBS) $(TARGET)
	@echo "************************************"
	@echo "Compilation terminated successfully!"
	
clean:
	@-rm -rf obj *.a *.map *.sim workspace *.htm *.$(CG_BIN_EXTENSION) \
	*.$(CG_OUT_EXTENSION) 
	@echo "CLEAN";


### Target file creation ###

$(TARGET_NAME).$(CG_BIN_EXTENSION): $(TARGET_NAME).$(CG_OUT_EXTENSION)
	@echo "OBJCOPY";
	$(QUIET)$(EE_OBJCOPY) $(COMPUTED_OPT_OBJCOPY) \
	$(SOURCEFILE) $(TARGETFILE)


$(TARGET_NAME).$(CG_OUT_EXTENSION): $(OBJS) $(LINKDEP) $(LIBDEP) 
	@echo "LD";
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK) -o $@ $(OBJS) $(OPT_LIBS) $(LIB_GCC_LINK) \

	
### Object file creation ###

# Produce the object file from assembly code in a single step
$(OBJDIR)/%.o: %.S
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_ASM) $(SOURCEFILE) \
	-o $(TARGETFILE)

$(OBJDIR)/%.o: %.s
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_ASM) $(DEPENDENCY_OPT) \
  $(SOURCEFILE) -o $(TARGETFILE)

$(OBJDIR)/%.o: %.asm
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_ASM) $(DEPENDENCY_OPT) \
  $(SOURCEFILE) -o $(TARGETFILE)


# Produce the object file from C code in a single step
$(OBJDIR)/%.o: %.c
	$(VERBOSE_PRINTCC) $(EE_CC) $(COMPUTED_OPT_CC) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_CC) $(DEFS_ISR) $(DEPENDENCY_OPT) \
	$(SOURCEFILE) -o $(TARGETFILE)
	$(QUIET)$(call make-depend, $<, $@, $(subst .o,.d,$@))

##
## EE Library
##

#libee.a: $(LIBEEOBJS)
$(ERIKALIB): $(LIBEEOBJS)
	@echo "AR    $(ERIKALIB)";
	$(QUIET)$(EE_AR) $(COMPUTED_OPT_AR) $@ $^

##
## Directories
##

.PHONY: make_directories

## Objects depend on directories, but they are not remade if directories change
$(ALLOBJS): | make_directories

make_directories: $(OBJDIRS)

## Directories are (re)created only when some of them don't exist already
$(OBJDIRS): 
	@echo "MAKE_DIRECTORIES"
	$(QUIET)mkdir -p $(OBJDIRS)

# the eeopt file is generated when dealing with ONLY_LIBS!
#
# this is a phony because the source code does not depend on this file
# and its content higly depends on the EEOPT variables...
#
.PHONY: generate_eeopt
generate_eeopt:
	@echo "GEN   eeopt.h"
	$(QUIET)for x in $(EEOPT); do \
		echo \#ifndef $${x}      >> eeopt.h; \
		echo \#define $${x}      >> eeopt.h; \
		echo \#endif             >> eeopt.h; \
	done;


##
## Automatic Generation of dependencies
##
dependencies=$(subst .o,.d,$(ALLOBJS))
ifneq ($(call iseeopt, NODEPS), yes) 
ifneq ($(MAKECMDGOALS),clean)
-include $(dependencies)
endif
endif
