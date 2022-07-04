
#include "board/ev3_mindstorm/inc/pininfo.h"

PinInfo pininfo[] =
{
  /* GPIO pins */
  {  0, 0x00000000, 0x00000000 }, // GP0_0 (unknown)
  {  1, 0xF0FFFFFF, 0x08000000 }, // GP0_1
  {  1, 0xFF0FFFFF, 0x00800000 }, // GP0_2
  {  1, 0xFFF0FFFF, 0x00080000 }, // ...
  {  1, 0xFFFF0FFF, 0x00008000 },
  {  1, 0xFFFFF0FF, 0x00000800 },
  {  1, 0xFFFFFF0F, 0x00000080 },
  {  1, 0xFFFFFFF0, 0x00000008 },
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0xFFF0FFFF, 0x00080000 },
  {  0, 0xFFFF0FFF, 0x00008000 },
  {  0, 0xFFFFF0FF, 0x00000800 },
  {  0, 0xFFFFFF0F, 0x00000080 },
  {  0, 0xFFFFFFF0, 0x00000008 }, // GP0_15

  {  4, 0x0FFFFFFF, 0x80000000 }, // GP1_0
  {  0, 0x00000000, 0x00000000 }, // GP1_1 (unknown)
  {  0, 0x00000000, 0x00000000 }, // ...   (unknown)
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  3, 0xFFFFFFF0, 0x00000004 },
  {  2, 0xF0FFFFFF, 0x04000000 },
  {  2, 0xFF0FFFFF, 0x00400000 },
  {  2, 0xFFF0FFFF, 0x00040000 },
  {  2, 0xFFFF0FFF, 0x00004000 },
  {  2, 0xFFFFF0FF, 0x00000400 },
  {  2, 0xFFFFFF0F, 0x00000040 },
  {  2, 0xFFFFFFF0, 0x00000008 },

  {  6, 0x0FFFFFFF, 0x80000000 },
  {  6, 0xF0FFFFFF, 0x08000000 },
  {  6, 0xFF0FFFFF, 0x00800000 },
  {  6, 0xFFF0FFFF, 0x00080000 },
  {  6, 0xFFFF0FFF, 0x00008000 },
  {  6, 0xFFFFF0FF, 0x00000800 },
  {  6, 0xFFFFFF0F, 0x00000080 },
  {  6, 0xFFFFFFF0, 0x00000008 },
  {  5, 0x0FFFFFFF, 0x80000000 },
  {  5, 0xF0FFFFFF, 0x08000000 },
  {  5, 0xFF0FFFFF, 0x00800000 },
  {  5, 0xFFF0FFFF, 0x00080000 },
  {  5, 0xFFFF0FFF, 0x00008000 },
  {  5, 0xFFFFF0FF, 0x00000800 },
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown

  {  8, 0x0FFFFFFF, 0x80000000 },
  {  8, 0xF0FFFFFF, 0x08000000 },
  {  8, 0xFF0FFFFF, 0x00800000 },
  {  8, 0xFFF0FFFF, 0x00080000 },
  {  8, 0xFFFF0FFF, 0x00008000 },
  {  8, 0xFFFFF0FF, 0x00000800 },
  {  8, 0xFFFFFF0F, 0x00000080 },
  {  8, 0xFFFFFFF0, 0x00000008 },
  {  7, 0x0FFFFFFF, 0x80000000 },
  {  7, 0xF0FFFFFF, 0x08000000 },
  {  7, 0xFF0FFFFF, 0x00800000 },
  {  7, 0xFFF0FFFF, 0x00080000 },
  {  7, 0xFFFF0FFF, 0x00008000 },
  {  7, 0xFFFFF0FF, 0x00000800 },
  {  7, 0xFFFFFF0F, 0x00000080 },
  {  7, 0xFFFFFFF0, 0x00000008 },

  {  0, 0x00000000, 0x00000000 }, // unknown
  { 10, 0xF0FFFFFF, 0x08000000 },
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  9, 0x0FFFFFFF, 0x80000000 },
  {  9, 0xF0FFFFFF, 0x08000000 },
  {  9, 0xFF0FFFFF, 0x00800000 },
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  9, 0xFFFF0FFF, 0x00008000 },
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  9, 0xFFFFFF0F, 0x00000080 },
  {  0, 0x00000000, 0x00000000 }, // unknown

  { 12, 0x0FFFFFFF, 0x80000000 },
  { 12, 0xF0FFFFFF, 0x08000000 },
  { 12, 0xFF0FFFFF, 0x00800000 },
  { 12, 0xFFF0FFFF, 0x00080000 },
  { 12, 0xFFFF0FFF, 0x00008000 },
  { 12, 0xFFFFF0FF, 0x00000800 },
  { 12, 0xFFFFFF0F, 0x00000080 },
  { 12, 0xFFFFFFF0, 0x00000008 },
  { 11, 0x0FFFFFFF, 0x80000000 },
  { 11, 0xF0FFFFFF, 0x08000000 },
  { 11, 0xFF0FFFFF, 0x00800000 },
  { 11, 0xFFF0FFFF, 0x00080000 },
  { 11, 0xFFFF0FFF, 0x00008000 },
  { 11, 0xFFFFF0FF, 0x00000800 },
  { 11, 0xFFFFFF0F, 0x00000080 },
  { 11, 0xFFFFFFF0, 0x00000008 },

  { 19, 0xF0FFFFFF, 0x08000000 },
  { 19, 0xFF0FFFFF, 0x00800000 },
  { 19, 0xFFF0FFFF, 0x00080000 },
  { 19, 0xFFFF0FFF, 0x00008000 },
  { 19, 0xFFFFF0FF, 0x00000800 },
  { 16, 0xFFFFFF0F, 0x00000080 },
  { 14, 0xFFFFFF0F, 0x00000080 },
  { 14, 0xFFFFFFF0, 0x00000008 },
  { 13, 0x0FFFFFFF, 0x80000000 },
  { 13, 0xF0FFFFFF, 0x08000000 },
  { 13, 0xFF0FFFFF, 0x00800000 },
  { 13, 0xFFF0FFFF, 0x00080000 },
  { 13, 0xFFFF0FFF, 0x00008000 },
  { 13, 0xFFFFF0FF, 0x00000800 },
  { 13, 0xFFFFFF0F, 0x00000080 },
  { 13, 0xFFFFFFF0, 0x00000008 },

  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  { 17, 0xFF0FFFFF, 0x00800000 },
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  { 17, 0xFFFFFF0F, 0x00000080 },
  { 17, 0xFFFFFFF0, 0x00000008 },
  { 16, 0x0FFFFFFF, 0x80000000 },
  { 16, 0xF0FFFFFF, 0x08000000 },
  { 16, 0xFF0FFFFF, 0x00800000 },
  { 16, 0xFFF0FFFF, 0x00080000 },
  { 16, 0xFFFF0FFF, 0x00008000 },
  { 16, 0xFFFFF0FF, 0x00000800 },

  {  0, 0x00000000, 0x00000000 }, // unknown
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  3, 0xF0FFFFFF, 0x04000000 },
  {  3, 0xFF0FFFFF, 0x00400000 },
  {  0, 0x00000000, 0x00000000 }, // unknown
  {  3, 0xFFFF0FFF, 0x00004000 },
  {  3, 0xFFFFF0FF, 0x00000400 },
  {  0, 0x00000000, 0x00000000 }, // unknown
  { 19, 0xFFFFFF0F, 0x00000080 },
  { 19, 0xFFFFFFF0, 0x00000008 },
  { 18, 0x0FFFFFFF, 0x80000000 },
  { 18, 0xF0FFFFFF, 0x08000000 },
  { 18, 0xFF0FFFFF, 0x00800000 },
  { 18, 0xFFF0FFFF, 0x00080000 },
  { 18, 0xFFFF0FFF, 0x00008000 },
  { 18, 0xFFFFF0FF, 0x00000800 },

  /* empty (no. of GPIOs) */
  {  0, 0x00000000, 0x00000000 },

  /* UART pins */
  {  3, 0xFF0FFFFF, 0x00200000 }, // UART0_TXD
  {  3, 0xFFF0FFFF, 0x00020000 }, // UART0_RXD
  {  4, 0x0FFFFFFF, 0x20000000 }, // UART1_TXD
//  {  4, 0xF0FFFFFF, 0x02000000 }, // UART1_RXD

  { 0, 0x000000000, 0x00000000 },

  /* SPI0 pins */
  {  3, 0xFFFF0FFF, 0x00001000 },
  {  3, 0xFFFFF0FF, 0x00000100 },
  {  3, 0xFFFFFFF0, 0x00000001 },
  {  3, 0xF0FFFFFF, 0x01000000 },

  {  0, 0x00000000, 0x00000000 },
};

unsigned int pininfo_size = sizeof(pininfo) / sizeof(pininfo[0]);



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
