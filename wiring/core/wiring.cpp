/*
 Copyright (c) 2011 Arduino.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Modified: Georgi Angelov 
 */

#include <Wiring.h>

void delay(unsigned int t)
{
	uint32_t elapsed;
	uint32_t start = millis();
	do
	{
		elapsed = millis() - start;
	} while (elapsed < t);
}

unsigned int seconds(void) { return millis() / 1000; }

void yield(void) {}

boolean no_interrupt = 1;
volatile uint32_t prevBasePri;

void interrupts(void)
{
	no_interrupt = 1;
	RestoreIrqs(prevBasePri);
}

void noInterrupts(void)
{
	no_interrupt = 0;
	prevBasePri = BlockIrqs();
}

boolean noStopInterrupts(void)
{
	return no_interrupt;
}

uint32_t clockCyclesPerMicrosecond(void)
{
	// TODO ??
	return 200;
}

uint32_t clockCyclesToMicroseconds(uint32_t a) { return a / clockCyclesPerMicrosecond(); }

uint32_t microsecondsToClockCycles(uint32_t a) { return a * clockCyclesPerMicrosecond(); }
