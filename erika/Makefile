# This makefile is just for deployment and calling the inner makefiel to build the am1808_ee_application

# This can be changed and will be the name of the resulting binary
export TARGET_NAME = ee_app


# Make sure ./configure.sh was called because wermit needs to be compiled for target "deploy" to work
BINARY = apps/am1808/`cat .build_helper`/build/$(TARGET_NAME).bin
WERMIT = third_party/wermit/wermit

%:
	@echo $@ > .build_helper
	@$(MAKE) -C  apps/am1808/$@ all
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D apps/am1808/$@/build/$(TARGET_NAME).elf > disassembly/all.asm
	@arm-none-eabi-objdump -d apps/am1808/$@/build/$(TARGET_NAME).elf > disassembly/code.asm
	


qemu_run:
	$(if $(APP),,$(error APP must best set like "make qemu APP=<app_name>"))
	@echo $(APP) > .gdb_helper
	@$(MAKE) -C apps/versatilepb_qemu/$(APP) all
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D apps/versatilepb_qemu/$(APP)/build/$(TARGET_NAME).elf > disassembly/all.asm
	@arm-none-eabi-objdump -d apps/versatilepb_qemu/$(APP)/build/$(TARGET_NAME).elf > disassembly/code.asm
	@qemu-system-arm -M versatilepb -m 128M -nographic -kernel apps/versatilepb_qemu/$(APP)/build/$(TARGET_NAME).bin

qemu:
	$(if $(APP),,$(error APP must best set like "make qemu APP=<app_name>"))
	@echo $(APP) > .gdb_helper
	@$(MAKE) -C apps/versatilepb_qemu/$(APP) all
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D apps/versatilepb_qemu/$(APP)/build/$(TARGET_NAME).elf > disassembly/all.asm
	@arm-none-eabi-objdump -d apps/versatilepb_qemu/$(APP)/build/$(TARGET_NAME).elf > disassembly/code.asm
	@qemu-system-arm -M versatilepb -m 128M -nographic -kernel apps/versatilepb_qemu/$(APP)/build/$(TARGET_NAME).bin -s -S


gdb:
	@gdb-multiarch apps/versatilepb_qemu/`cat .gdb_helper`/build/$(TARGET_NAME).elf --command=.gdb_init

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
	@rm -rf apps/am1808/*/build apps/versatilepb_qemu/*/build kermit_upload disassembly .build_helper
	@echo Removing build and debug files...


# could be automated via `find apps/versatilepb_qemu/ -mindepth 1 -type d` but then has no order
TEST_APPS = compile_test coop_schedule isr2_test pre_schedule multistack_coop multistack_isr2_test multistack_waitevent
test:
	@echo Use "CTRL + a + x" to terminate QEMU
	@echo Use "CRTL + c"     to abort testcases after qemu was exited
	@read -p "Press enter to start testcases" unused 
	@ for file in $(TEST_APPS) ; do \
		echo -e "\t\t\t\t\t\t\t\t\t\tTesting $$file" ; \
		$(MAKE) -C apps/versatilepb_qemu/$$file > /dev/null ; \
		qemu-system-arm -M versatilepb -m 128M -nographic -kernel apps/versatilepb_qemu/$$file/build/$(TARGET_NAME).bin ; \
		read -p "Press enter to continue" unused ; \
	done
	@make clean


modistarc:
	@$(MAKE) -C testcases/$(APP) all

.PHONY: clean, build deploy