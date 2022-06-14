ifeq ($(call iseeopt, __AM1808__), yes)

EE_SRCS += pkg/mcu/am1808/src/put_char.c
EE_SRCS += pkg/mcu/am1808/src/interrupt.c
EE_SRCS += pkg/mcu/am1808/src/timer.c
EE_SRCS += pkg/mcu/am1808/src/uart.c
EE_SRCS += pkg/mcu/am1808/src/interrupt_handler.S

endif	# AM1808
