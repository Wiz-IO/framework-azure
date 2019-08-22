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

#include <interface.h>

extern "C" const unsigned int ExceptionVectorTable[116] __attribute__((section(".vector_table")));// __attribute__((used));
extern "C" void __libc_init_array(void);
extern "C" void init(void); // from variant
extern void setup();
extern void loop();

extern "C" void RTCoreMain(void)
{
    *(volatile uint32_t *)(0xE000ED08) = (uint32_t)ExceptionVectorTable; // SCB->VTOR = ExceptionVectorTable
    __libc_init_array();
    /* MAYBE IS 26000, will test soon */
    SysTick_Config(26000);  // 1 mSec isr 
    init();                 // variant
    setup();
    while (1)
    {
        loop();
    }
}
