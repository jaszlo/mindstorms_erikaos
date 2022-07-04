ifeq ($(call iseeopt, __AM1808__), yes)

EE_SRCS += pkg/mcu/am1808/src/put_char.c
EE_SRCS += pkg/mcu/am1808/src/interrupt.c
EE_SRCS += pkg/mcu/am1808/src/timer.c
EE_SRCS += pkg/mcu/am1808/src/uart.c
EE_SRCS += pkg/mcu/am1808/src/interrupt_handler.S


ifeq ($(call iseeopt, __WD_RESET__), yes)
EE_SRCS += pkg/mcu/am1808/src/watchdog/wd_timer.c
EE_SRCS += pkg/mcu/am1808/src/watchdog/watchdog.c
endif   # RESET
endif	# AM1808
