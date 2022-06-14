# Destination directory
export OUTPUT_DIR = build

# Erika sources directory
export ERIKA_FILES = ../../../ee

export GNU_ARM_ROOT = "/"

# Check the environment and use reasonable defaults
ifndef RT_DRUID_HOME
RT_DRUID_HOME = ../../third_party/rt_druid
endif

ifndef RTDRUID_SCRIPT_DIR
RTDRUID_SCRIPT_DIR=$(RT_DRUID_HOME)/evidence
endif

RTDRUID_OUTPUT = $(addprefix $(OUTPUT_DIR)/, makefile eecfg.h eecfg.c)

.PHONY: all clean

all: $(RTDRUID_OUTPUT)
	$(MAKE) -C $(OUTPUT_DIR) all


clean:
	@echo cleaning...
	rm -f -r $(OUTPUT_DIR)

# Run RT Druid
$(RTDRUID_OUTPUT): $(OUTPUT_DIR)/% : conf.oil
	@mkdir -p $(OUTPUT_DIR)
	@$(RTDRUID_SCRIPT_DIR)/generate_code.sh $(RT_DRUID_HOME) conf.oil build
	