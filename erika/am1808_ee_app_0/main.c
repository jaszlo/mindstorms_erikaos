#include "ee.h"
#include "test/assert/inc/ee_assert.h"
#define TRUE 1

/* Assertions */
enum EE_ASSERTIONS
{
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_DIM,
  FILLER
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int counter = 0;

/*
 * TASK 1
 */
TASK(Task1)
{
  char stuff[1];
  put_string("Hello world!\n");
  put_string("Iam printing stuff!\n");
  put_string("Here is an integer in decimal: ");
  short i = 1337;
  put_int(i);
  put_char('\n');
  put_string("Here is that number in binary: ");
  set_base(BIN);
  put_int(i);
  set_base(DEC);
  put_char('\n');
  put_string("And here is a pointer: ");
  char *ptr = stuff;
  put_ptr(ptr);
  put_char('\n');
  put_string("Here is the bool evaluation of that pointer == NULL: ");
  put_bool(ptr == NULL);
  put_char('\n');
}

/*
 * MAIN TASK
 */
int main(void)
{
  // TODO: Write own SystemInit or find existing implementation
  // SystemInit(); // currently implemented at ee/contrib/st/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c

  // TODO: Write EE_SystemInit for arm9
  // EE_system_init(); // currently implemented at ee/pkg/cpu/cortex_mx/src/ee_utils.c

  // This should require no changes
  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_INIT);
  result = EE_assert_last();
  ActivateTask(Task1);
  return 0;
}

/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
