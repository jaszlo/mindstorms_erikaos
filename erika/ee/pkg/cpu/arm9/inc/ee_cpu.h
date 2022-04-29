/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/**
	@file ee_cpu.h
	@brief CPU-dependent part of HAL. Derived from pkg/cpu/pic30/inc/ee_cpu.h
	@author Gianluca Franchino
	@author Giuseppe Serano
	@date 2011
*/
#ifndef __INCLUDE_ARM9_EE_CPU_H__
#define __INCLUDE_ARM9_EE_CPU_H__

#include "eecfg.h"

#ifdef __ENABLE_IO__
#include "cpu/arm9/debug/io.h"
#endif 


#include "cpu/arm9/inc/ninja_timer.h"
#include "cpu/arm9/inc/ninja_interrupt.h"

#ifdef __GNU__
#include "cpu/common/inc/ee_compiler_gcc.h"
#endif

/* Initial stack offset (in words): Used in multistack. */
#ifndef ARM9_INIT_TOS_OFFSET
#define ARM9_INIT_TOS_OFFSET 10
#endif

/*************************************************************************
 HAL Types and structures
 *************************************************************************/

/* Primitive data types */
#include "cpu/common/inc/ee_types.h"

typedef EE_UINT32 EE_UREG;
typedef EE_INT32 EE_SREG;
typedef EE_UINT32 EE_FREG;
#define EE_UREG_SIZE 4

/* boolean type */
#ifndef EE_TYPEBOOL
typedef EE_UREG EE_TYPEBOOL;
#endif

/* boolean true define */
#ifndef EE_TRUE
#define EE_TRUE ((EE_TYPEBOOL)1U)
#endif

/* boolean false define */
#ifndef EE_FALSE
#define EE_FALSE ((EE_TYPEBOOL)0U)
#endif

#define EE_HWREG_PTR volatile EE_UREG *
#define EE_HWREG_ADDR(x) ((EE_HWREG_PTR)(x))
#define EE_HWREG(x) (*EE_HWREG_ADDR(x))

#ifdef __GNU__

/* Get current SP */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ __current_sp(void)
{
	EE_UINT32 temp;
	__ASM("mov %0, sp"
		  : "=r"(temp)
		  :);
	return temp;
}

/* Set a breakpoint */
#define __breakpoint(value) __ASM("bkpt " #value)

#endif

/* ISR Priority representation type */
typedef EE_UREG EE_TYPEISR2PRIO;

/* Thread IDs */
typedef EE_INT32 EE_TID;

/* Thread IDs - unsigned version*/
typedef EE_UINT32 EE_UTID;

/* Used by the common layer to decide whether to start a new thread */
#define TID_IS_STACKED_MARK 0x80000000

/* EE_TYPEIRQ is currently unused */

/* XXX: define EE_TIME? */

/* Use the "standard" implementation */
#include "cpu/common/inc/ee_hal_structs.h"

/******************************************************************************
 Application dependent data types
 ******************************************************************************/

#ifdef __HAS_TYPES_H__
#include "types.h"
#endif

/******************************************************************************
 CPU Peripherals
 ******************************************************************************/

#ifdef __ARM9__
#include "cpu/arm9/inc/ee_nvic.h"
#include "cpu/arm9/inc/ee_systick.h"
#endif

/******************************************************************************
 HAL Variables
 ******************************************************************************/

#ifdef __MULTI__

/* Top-of-stack of each private stack */
extern struct EE_TOS EE_arm9_system_tos[];
//#define	EE_std_system_tos EE_arm9_system_tos

/* Index of the current stack */
extern EE_UREG EE_arm9_active_tos;
#define EE_hal_active_tos EE_arm9_active_tos

/*extern	EE_UREG EE_pic30_thread_tos[];
#define	EE_std_thread_tos EE_pic30_thread_tos */
#endif /* __MULTI__ */

/*********************************************************************
 Cortex M0 interrupt disabling/enabling
 *********************************************************************/

/* Used to check the value returned by EE_arm9_disableIRQ */
#define EE_arm9_are_IRQs_enabled(ie) ((ie) ^ 1)

/**
 * Enable interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_arm9_enableIRQ(void)
{
}

/**
 * Disable interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_arm9_disableIRQ(void)
{
}

/**
 * Resume interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_arm9_resumeIRQ(EE_FREG f)
{
}

/**
 * Suspend interrupts
 */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_arm9_suspendIRQ(void)
{
	return 0;
}

/**
 * Return true (not 0) if IRQs are enabled, 0 (false) if IRQ are disabled.
 */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_arm9_get_IRQ_enabled(void)
{
	return EE_arm9_are_IRQs_enabled(0);
}

__INLINE__ EE_TYPEISR2PRIO __ALWAYS_INLINE__ EE_arm9_get_int_prio(void)
{
	return 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_arm9_set_int_prio(
	EE_TYPEISR2PRIO prio)
{
}

__INLINE__ EE_TYPEISR2PRIO __ALWAYS_INLINE__ EE_arm9_get_isr_prio(
	void)
{
	return 0;
}

/*************************************************************************
 Functions exported by the HAL to the kernel
 *************************************************************************/

/*
 * Interrupt Handling
 */

/** Hal Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
	EE_arm9_enableIRQ();
}

/** Hal Disable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
	EE_arm9_disableIRQ();
}

/** Hal Resume Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_resumeIRQ(EE_FREG f)
{
	EE_arm9_resumeIRQ(f);
}

/** Hal Suspend Interrupts */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_suspendIRQ(void)
{
	return EE_arm9_suspendIRQ();
}

/**************************************************************************
 System Initialization
***************************************************************************/

void EE_system_init(void);

/*************************************************************************
 CPU-dependent ORT support (mainly OTM)
 *************************************************************************/

/* Probably, some parts of the OTM code below does not depend on the
 * architecture.  They should be moved somewhere into pkg/cpu/common if this
 * turns out to be the case. */

#define EE_ORTI_OTM_ID_RUNNINGISR2 1
#define EE_ORTI_OTM_ID_SERVICETRACE 2

#ifdef __OO_ORTI_USE_OTM__
void EE_arm9_send_otm8(EE_UINT8 id, EE_UINT8 data);
void EE_arm9_send_otm32(EE_UINT8 id, EE_UINT32 data);

#else  /* if __OO_ORTI_USE_OTM__ */
__INLINE__ void EE_arm9_send_otm8(EE_UINT8 id, EE_UINT8 data)
{
	/* OTM disabled */
}

__INLINE__ void EE_arm9_send_otm32(EE_UINT8 id, EE_UINT32 data)
{
	/* OTM disabled */
}
#endif /* else __OO_ORTI_USE_OTM__ */

#ifdef __OO_ORTI_RUNNINGISR2__
__INLINE__ void EE_ORTI_send_otm_runningisr2(EE_ORTI_runningisr2_type isr2)
{
	EE_arm9_send_otm32(EE_ORTI_OTM_ID_RUNNINGISR2, (EE_UINT32)isr2);
}
#endif /* __OO_ORTI_RUNNINGISR2__ */

#ifdef __OO_ORTI_SERVICETRACE__
__INLINE__ void EE_ORTI_send_otm_servicetrace(EE_UINT8 srv)
{
	EE_arm9_send_otm8(EE_ORTI_OTM_ID_SERVICETRACE, srv);
}

#endif /* __OO_ORTI_SERVICETRACE__ */

#endif /* __INCLUDE_ARM9_EE_CPU_H__ */
