
/******************************************************************************
 *       ninjastorms - shuriken operating system                              *
 *                                                                            *
 *    Copyright (C) 2013 - 2016  Andreas Grapentin et al.                     *
 *                                                                            *
 *    This program is free software: you can redistribute it and/or modify    *
 *    it under the terms of the GNU General Public License as published by    *
 *    the Free Software Foundation, either version 3 of the License, or       *
 *    (at your option) any later version.                                     *
 *                                                                            *
 *    This program is distributed in the hope that it will be useful,         *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *    GNU General Public License for more details.                            *
 *                                                                            *
 *    You should have received a copy of the GNU General Public License       *
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ******************************************************************************/

/**
 * Modified by Jasper Lorenz (jasper.lorenz@stud.uni-hannover.de)
 */

#include "cpu/arm9/inc/ninja_memory.h"

.section .text

// Import
.globl timer_isr

// Export
.globl irq_handler


irq_handler:
  // Save context
  push  {r0-r3, r12, lr} // r14 = lr

  // Disable timer interrupt specificly
  ldr r0, =TIMER0_INTCTLSTAT_ASM
  mov r1, CLEARTIMER34_ASM
  str r1, [r0]

  // Disable interrupts in controller
  ldr r0, =AINTC_SECR1_ASM
  mov r1, T64P0_TINT34_ASM
  str r1, [r0]
  
  bl  timer_isr
   
  // Restore state and return
  pop  {r0-r3, r12, lr}
  mov pc, lr