
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


#include "cpu/arm9/inc/ninja_timer.h"
#include "cpu/arm9/inc/ninja_memory.h"

void timer_start(unsigned int period)
{
  *TIMER0_TCR  &= ~ENAMODE34;          // Disable timer
  *TIMER0_TGCR &= ~TIM34RS_REMOVE;     // Reset timer
  *TIMER0_TGCR &= ~TIMMODE;            // Reset mode bits
  *TIMER0_TGCR |= TIMMODE_UNCHAINED;   // Set dual 32 bit unchained mode
  *TIMER0_TGCR |= TIM34RS_REMOVE;      // Remove timer from reset
  *TIMER0_PRD34 = period;              // Set timer period
  *TIMER0_TGCR &= ~PSC34;              // Reset prescaler
  *TIMER0_TGCR |= PSC34_VALUE;         // Set prescaler
  *TIMER0_INTCTLSTAT |= PRDINTSTAT34;  // Clear interrupts
  *TIMER0_INTCTLSTAT |= PRDINTEN34;    // Enable interrupts
  *TIMER0_TCR  |= ENAMODE34_CONTIN;    // Set continuously-mode, start timer

}

void timer_stop(void)
{
  *TIMER0_TCR  &= ~ENAMODE34;          // Disable timer
  *TIMER0_INTCTLSTAT |= PRDINTSTAT34;  // Clear interrupts
}
 