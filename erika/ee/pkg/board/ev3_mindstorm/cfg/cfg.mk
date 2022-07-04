
ifeq ($(call iseeopt, __MINDSTORM__), yes)
EE_SRCS += pkg/board/ev3_mindstorm/src/motor.c
EE_SRCS += pkg/board/ev3_mindstorm/src/gpio.c
EE_SRCS += pkg/board/ev3_mindstorm/src/pininfo.c
endif
