ifeq ($(call iseeopt, __VERSATILEPB__), yes)

EE_SRCS += pkg/mcu/versatilepb/src/interrupt.c
EE_SRCS += pkg/mcu/versatilepb/src/interrupt_handler.S
EE_SRCS += pkg/mcu/versatilepb/src/timer.c
EE_SRCS += pkg/mcu/versatilepb/src/put_char.c
endif	# AM1808
