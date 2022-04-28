# This makefile is just for deployment and calling the inner makefiel to build the am1808_ee_application

# This can be changed and will be the name of the resulting binary
export TARGET_NAME = am1808_ee_app

# Make sure ./configure.sh was called because wermit needs to be compiled for target "deploy" to work
WERMIT = third_party/wermit/wermit
BINARY = am1808_ee_app/build/$(TARGET_NAME).bin

build:
	@$(MAKE) -C  am1808_ee_app clean all

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
	rm -rf am1808_ee_app/build kermit_upload


.PHONY: clean, build deploy
