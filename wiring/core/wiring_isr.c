/*
    Created on: 01.01.2019
    Author: Georgi Angelov

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   
 */

#include <stddef.h>
#include <stdint.h>

extern uint32_t StackTop; // &StackTop == end of TCM0
static void DefaultExceptionHandler(void);
void RTCoreMain(void);
volatile void systickHandler(void);

#define INTERRUPT_COUNT 100
#define INT_TO_EXC(i_) (16 + (i_))

volatile unsigned int ExceptionVectorTable[16 + INTERRUPT_COUNT]
    __attribute__((section(".vector_table")))
    __attribute__((used)) = {
        [0] = (unsigned int)&StackTop,
        [1] = (unsigned int)RTCoreMain,
        [2] = (unsigned int)DefaultExceptionHandler,
        [3] = (unsigned int)DefaultExceptionHandler,
        [4] = (unsigned int)DefaultExceptionHandler,
        [5] = (unsigned int)DefaultExceptionHandler,
        [6] = (unsigned int)DefaultExceptionHandler,
        [11] = (unsigned int)DefaultExceptionHandler,
        [12] = (unsigned int)DefaultExceptionHandler,
        [14] = (unsigned int)DefaultExceptionHandler,
        [15] = (unsigned int)systickHandler, // SysTick
        [INT_TO_EXC(0)... INT_TO_EXC(INTERRUPT_COUNT - 1)] = (unsigned int)DefaultExceptionHandler};

void DefaultExceptionHandler(void)
{
    for (;;)
    {
    }
}

volatile unsigned int systick = 0;
volatile void systickHandler(void) { systick++; }
