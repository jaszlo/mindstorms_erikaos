ifeq ($(call iseeopt, __ARM9__), yes)

EE_SRCS += pkg/cpu/arm9/src/init.c
EE_SRCS += pkg/cpu/arm9/src/cpsr.c
EE_SRCS += pkg/cpu/arm9/src/reset.S

EE_SRCS += pkg/cpu/arm9/src/ee_internal.c
EE_SRCS += pkg/cpu/arm9/src/ee_io.c
EE_SRCS += pkg/cpu/arm9/src/ee_irq.c
EE_SRCS += pkg/cpu/arm9/src/ee_irqsched.S
EE_SRCS += pkg/cpu/arm9/src/ee_context.S
EE_SRCS += pkg/cpu/arm9/src/ee_terminate.S

endif