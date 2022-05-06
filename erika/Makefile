# This makefile is just for deployment and calling the inner makefiel to build the am1808_ee_application

# This can be changed and will be the name of the resulting binary
export TARGET_NAME = am1808_ee_app

ifndef EE_APP
EE_APP=compile_test
endif

# Make sure ./configure.sh was called because wermit needs to be compiled for target "deploy" to work
WERMIT = third_party/wermit/wermit
BINARY = am1808_ee_app_$(EE_APP)/build/$(TARGET_NAME).bin
ELF = am1808_ee_app_$(EE_APP)/build/$(TARGET_NAME).elf


all: $(EE_APP)

compile_test:
	@$(MAKE) -C  am1808_ee_app_$@ all
	@arm-none-eabi-objdump -D $(ELF) > all.asm
	@arm-none-eabi-objdump -d $(ELF) > code.asm
	@echo Basic compilation worked
	@echo

coop_schedule:
	@$(MAKE) -C  am1808_ee_app_$@ all
	@arm-none-eabi-objdump -D $(ELF) > all.asm
	@arm-none-eabi-objdump -d $(ELF) > code.asm
	@echo Compilation of cooperative schedule application worked
	@echo


isr2_test:
	@$(MAKE) -C  am1808_ee_app_$@ all
	@arm-none-eabi-objdump -D $(ELF) > all.asm
	@arm-none-eabi-objdump -d $(ELF) > code.asm
	@echo Compilation of interrupt application worked
	@echo

# Deploy binary to ev3 via kermit
deploy:
	@echo Creating kermit script
	@echo Executing script...
	@cat kermit_upload_stub > kermit_upload
	@echo send $(BINARY) >> kermit_upload
	@echo connect >> kermit_upload
	@echo exit >> kermit_upload
	$(WERMIT) kermit_upload




clean:
	rm -rf am1808_ee_app*/build kermit_upload *.asm


.PHONY: clean, build deploy