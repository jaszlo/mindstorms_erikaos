# This makefile is just for deployment and calling the inner makefiel to build the am1808_ee_application

# This can be changed and will be the name of the resulting binary
export TARGET_NAME = ee_app


# Make sure ./configure.sh was called because wermit needs to be compiled for target "deploy" to work
BINARY = apps/am1808/`cat .build_helper`/build/$(TARGET_NAME).bin
WERMIT = third_party/wermit/wermit


### AM1808 
%:
	@echo am1808/$@ > .build_helper
	@$(MAKE) -C  apps/am1808/$@ all
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D apps/am1808/$@/build/$(TARGET_NAME).elf > disassembly/all.asm
	@arm-none-eabi-objdump -d apps/am1808/$@/build/$(TARGET_NAME).elf > disassembly/code.asm

### Mindstorm
mindstorm:
	$(if $(APP),,$(error APP must best set like "make mindstorm APP=<app_name>"))
	@echo mindstorm/$(APP) > .build_helper
	@$(MAKE) -C  apps/mindstorm/$(APP) all
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D apps/mindstorm/$(APP)/build/$(TARGET_NAME).elf > disassembly/all.asm
	@arm-none-eabi-objdump -d apps/mindstorm/$(APP)/build/$(TARGET_NAME).elf > disassembly/code.asm
	

# Deploy binary to ev3 mindstorm via kermit
deploy:
	@if [ -f ".build_helper" ]; then echo Deploying `cat .build_helper` application; else echo No binary to deploy found && exit; fi
	@echo Creating kermit script...
	@cat kermit_upload_stub > kermit_upload
	@echo send apps/`cat .build_helper`/build/$(TARGET_NAME).bin >> kermit_upload
	@echo connect >> kermit_upload
	@echo exit >> kermit_upload
	@echo Executing script...
	$(WERMIT) kermit_upload



### QEMU
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
	@gdb-multiarch apps/versatilepb_qemu/`cat .gdb_helper`/build/$(TARGET_NAME).elf --command=gdb_init

kill:
	@echo Terminating qemu...
	@kill $(shell ps -aux | grep qemu | head -n 2 | tail -n -1 | awk '{print $$2;exit}')


### Clean for AM1808 and QEMU
clean:
	@rm -rf apps/*/*/build kermit_upload disassembly .build_helper testcases/*/*/build
	@echo Removing build and debug files...


modistarc_bcc1:
#BCC1 Tests
	@rm -f modistarc_results
	@echo BCC1 Testcase run:
	@echo
	@echo First all testcases will be compiled. This may take a while!
	@echo Note that you will have to restart the target between testcases as well as escape C-Kermit
	@echo Make sure the target is started and the UART dongle is connected!
	@echo
	@read -p "Press enter to start testcases []" unused 
	@for dir in $(shell python testcases/sort_testcases.py `find testcases/bcc1 -mindepth 1 -maxdepth 1 -type d | xargs -n1 | sort -k3n -t _ | xargs`) ; do \
		echo Building $$dir ; \
		$(MAKE) -C $$dir 2>&1 > /dev/null ; \
	done
	@for dir in $(shell python testcases/sort_testcases.py `find testcases/bcc1 -mindepth 1 -maxdepth 1 -type d | xargs -n1 | sort -k3n -t _ | xargs`) ; do \
		stty sane > /dev/null ; \
		cat kermit_upload_stub > kermit_upload ; \
		echo send /QUIET $$dir/build/$(TARGET_NAME).bin >> kermit_upload ; \
		echo connect >> kermit_upload ; \
		echo exit >> kermit_upload ; \
		python testcases/automated_kermit.py ; \
 	done
modistarc_bcc2:
# BCC2 Tests
	@for dir in $(shell python testcases/sort_testcases.py `find testcases/bcc2 -mindepth 1 -maxdepth 1 -type d | xargs -n1 | sort -k3n -t _ | xargs`) ; do \
		stty sane > /dev/null ; \
		echo Building $$dir ; \
		$(MAKE) -C $$dir 2>&1 > /dev/null ; \
	done
	@for dir in $(shell python testcases/sort_testcases.py `find testcases/bcc2 -mindepth 1 -maxdepth 1 -type d | xargs -n1 | sort -k3n -t _ | xargs`) ; do \
		stty sane > /dev/null ; \
		cat kermit_upload_stub > kermit_upload ; \
		echo send /QUIET $$dir/build/$(TARGET_NAME).bin >> kermit_upload ; \
		echo connect >> kermit_upload ; \
		echo exit >> kermit_upload ; \
		python testcases/automated_kermit.py ; \
 	done
modistarc_ecc1:
# ECC1 Tests
	@for dir in $(shell python testcases/sort_testcases.py `find testcases/ecc1 -mindepth 1 -maxdepth 1 -type d | xargs -n1 | sort -k3n -t _ | xargs`) ; do \
		stty sane > /dev/null ; \
		echo Building $$dir ; \
		$(MAKE) -C $$dir 2>&1 > /dev/null ; \
	done
	@for dir in $(shell python testcases/sort_testcases.py `find testcases/ecc1 -mindepth 1 -maxdepth 1 -type d | xargs -n1 | sort -k3n -t _ | xargs`) ; do \
		stty sane > /dev/null ; \
		cat kermit_upload_stub > kermit_upload ; \
		echo send /QUIET $$dir/build/$(TARGET_NAME).bin >> kermit_upload ; \
		echo connect >> kermit_upload ; \
		echo exit >> kermit_upload ; \
		python testcases/automated_kermit.py ; \
 	done
modistarc_ecc2:
# ECC1 Tests
	@for dir in $(shell python testcases/sort_testcases.py `find testcases/ecc2 -mindepth 1 -maxdepth 1 -type d | xargs -n1 | sort -k3n -t _ | xargs`) ; do \
		stty sane > /dev/null ; \
		echo Building $$dir ; \
		$(MAKE) -C $$dir 2>&1 > /dev/null ; \
	done
	@for dir in $(shell python testcases/sort_testcases.py `find testcases/ecc2 -mindepth 1 -maxdepth 1 -type d | xargs -n1 | sort -k3n -t _ | xargs`) ; do \
		stty sane > /dev/null ; \
		cat kermit_upload_stub > kermit_upload ; \
		echo send /QUIET $$dir/build/$(TARGET_NAME).bin >> kermit_upload ; \
		echo connect >> kermit_upload ; \
		echo exit >> kermit_upload ; \
		python testcases/automated_kermit.py ; \
 	done

modistarc: modistarc_bcc1 modistarc_ecc1 modistarc_bcc2 modistarc_ecc2
	@echo Finished!

# For Testing individual testcases
single_bcc1_modistarc:
	$(if $(APP),,$(error APP must best set like "make single_bcc_modistarc APP=<app_name>"))
	@$(MAKE) -C testcases/bcc1/$(APP)
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D  testcases/bcc1/$(APP)/build/ee_app.elf > disassembly/all.asm
	@arm-none-eabi-objdump -d  testcases/bcc1/$(APP)/build/ee_app.elf > disassembly/code.asm
	@cat kermit_upload_stub > kermit_upload
	@echo send testcases/bcc1/$(APP)/build/$(TARGET_NAME).bin >> kermit_upload
	@echo connect >> kermit_upload
	@echo exit >> kermit_upload
	@$(WERMIT) kermit_upload

single_ecc1_modistarc:
	$(if $(APP),,$(error APP must best set like "make single_ecc_modistarc APP=<app_name>"))
	@$(MAKE) -C testcases/ecc1/$(APP)
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D  testcases/ecc1/$(APP)/build/ee_app.elf > disassembly/all.asm
	@arm-none-eabi-objdump -d  testcases/ecc1/$(APP)/build/ee_app.elf > disassembly/code.asm
	@cat kermit_upload_stub > kermit_upload
	@echo send testcases/ecc1/$(APP)/build/$(TARGET_NAME).bin >> kermit_upload
	@echo connect >> kermit_upload
	@echo exit >> kermit_upload
	@$(WERMIT) kermit_upload



# For Testing individual testcases
single_bcc2_modistarc:
	$(if $(APP),,$(error APP must best set like "make single_bcc_modistarc APP=<app_name>"))
	@$(MAKE) -C testcases/bcc2/$(APP)
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D  testcases/bcc2/$(APP)/build/ee_app.elf > disassembly/all.asm
	@arm-none-eabi-objdump -d  testcases/bcc2/$(APP)/build/ee_app.elf > disassembly/code.asm
	@cat kermit_upload_stub > kermit_upload
	@echo send testcases/bcc2/$(APP)/build/$(TARGET_NAME).bin >> kermit_upload
	@echo connect >> kermit_upload
	@echo exit >> kermit_upload
	@$(WERMIT) kermit_upload

single_ecc2_modistarc:
	$(if $(APP),,$(error APP must best set like "make single_ecc_modistarc APP=<app_name>"))
	@$(MAKE) -C testcases/ecc2/$(APP)
	@mkdir -p disassembly
	@arm-none-eabi-objdump -D  testcases/ecc2/$(APP)/build/ee_app.elf > disassembly/all.asm
	@arm-none-eabi-objdump -d  testcases/ecc2/$(APP)/build/ee_app.elf > disassembly/code.asm
	@cat kermit_upload_stub > kermit_upload
	@echo send testcases/ecc2/$(APP)/build/$(TARGET_NAME).bin >> kermit_upload
	@echo connect >> kermit_upload
	@echo exit >> kermit_upload
	@$(WERMIT) kermit_upload


dev:
	@echo Make sure the target is started and the UART dongle is connected!
	@echo
	@read -p "Press enter to start testcases []" unused 
	@for dir in `find test/event -mindepth 1 -maxdepth 1 -type d | xargs -n1 | sort -k3n -t _ | xargs` ; do \
		echo                              Building $$dir; \
		$(MAKE) -C $$dir > /dev/null; \
	done
	@for dir in `find test/event -mindepth 1 -maxdepth 1 -type d | xargs -n1 | sort -k3n -t _ | xargs` ; do \
		stty sane > /dev/null ; \
		cat kermit_upload_stub > kermit_upload ; \
		echo send /QUIET $$dir/build/$(TARGET_NAME).bin >> kermit_upload ; \
		echo connect >> kermit_upload ; \
		echo exit >> kermit_upload ; \
		echo Testing $$dir ; \
		python automated_kermit.py ; \
	done
	@stty sane > /dev/null ; \

.PHONY: clean, build deploy