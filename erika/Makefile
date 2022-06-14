# This makefile is just for deployment and calling the inner makefiel to build the am1808_ee_application

# This can be changed and will be the name of the resulting binary
export TARGET_NAME = am1808_ee_app


# Make sure ./configure.sh was called because wermit needs to be compiled for target "deploy" to work
BINARY = apps/`cat .build_helper`/build/$(TARGET_NAME).bin
WERMIT = third_party/wermit/wermit

%:
	@echo $@ > .build_helper
	@$(MAKE) -C  apps/$@ all
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D apps/$@/build/$(TARGET_NAME).elf > disassembly/all.asm
	@arm-none-eabi-objdump -d apps/$@/build/$(TARGET_NAME).elf > disassembly/code.asm
	


qemu_run:
	$(if $(APP),,$(error APP must best set like "make qemu APP=<app_name>"))
	@echo $(APP) > .gdb_helper
	@$(MAKE) -C qemu_apps/$(APP) all
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D qemu_apps/$(APP)/build/$(TARGET_NAME).elf > disassembly/all.asm
	@arm-none-eabi-objdump -d qemu_apps/$(APP)/build/$(TARGET_NAME).elf > disassembly/code.asm
	@qemu-system-arm -M versatilepb -m 128M -nographic -kernel qemu_apps/$(APP)/build/$(TARGET_NAME).bin

qemu:
	$(if $(APP),,$(error APP must best set like "make qemu APP=<app_name>"))
	@echo $(APP) > .gdb_helper
	@$(MAKE) -C qemu_apps/$(APP) all
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D qemu_apps/$(APP)/build/$(TARGET_NAME).elf > disassembly/all.asm
	@arm-none-eabi-objdump -d qemu_apps/$(APP)/build/$(TARGET_NAME).elf > disassembly/code.asm
	@qemu-system-arm -M versatilepb -m 128M -nographic -kernel qemu_apps/$(APP)/build/$(TARGET_NAME).bin -s -S


gdb:
	@echo target remote localhost:1234 > .gdb_init
	@arm-none-eabi-gdb qemu_apps/`cat .gdb_helper`/build/$(TARGET_NAME).elf --command=.gdb_init

kill:
	@echo Terminating qemu...
	@kill $(shell ps -aux | grep qemu | head -n 2 | tail -n -1 | awk '{print $$2;exit}')



# Deploy binary to ev3 via kermit
deploy:
	@if [ -f ".build_helper" ]; then echo Deploying `cat .build_helper` application; else echo No binary to deploy found && exit; fi
	@echo Creating kermit script...
	@cat kermit_upload_stub > kermit_upload
	@echo send apps/`cat .build_helper`/build/$(TARGET_NAME).bin >> kermit_upload
	@echo connect >> kermit_upload
	@echo exit >> kermit_upload
	@echo Executing script...
	$(WERMIT) kermit_upload

clean:
	@rm -rf apps/*/build kermit_upload disassembly .build_helper qemu_apps/*/build
	@echo Removing build and debug files...

.PHONY: clean, build deploy