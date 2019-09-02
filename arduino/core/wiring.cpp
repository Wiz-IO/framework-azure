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
 Modified: Junxiao Shi
 */

#include "Arduino.h"

void delayMicroseconds(unsigned int us)
{
	struct timespec st;
	st.tv_sec = us / 1000000;
	st.tv_nsec = us % 1000000 * 1000;
	nanosleep(&st, NULL);
}

void delay(unsigned int ms)
{
	struct timespec st;
	st.tv_sec = ms / 1000;
	st.tv_nsec = ms % 1000 * 1000000;
	nanosleep(&st, NULL);
}

uint32_t utc(void)
{
    time_t t;
    time(&t);
    return t;
}

struct timespec app_start_time;
unsigned int millis(void)
{
	struct timespec gettime_now;
	clock_gettime(CLOCK_MONOTONIC, &gettime_now);
	return ((gettime_now.tv_sec - app_start_time.tv_sec) * 1000 +
		(gettime_now.tv_nsec - app_start_time.tv_nsec) / 1000000);	
}

unsigned int seconds(void)
{
	return millis() / 1000;
}

void yield(void) {}

boolean no_interrupt = 1;

void interrupts(void)
{
	no_interrupt = 1;
}

void noInterrupts(void)
{
	no_interrupt = 0;
}

boolean noStopInterrupts(void)
{
	return no_interrupt;
}

uint32_t clockCyclesPerMicrosecond(void)
{
	// TODO
	return 500; 
}

uint32_t clockCyclesToMicroseconds(uint32_t a)
{
	return a / clockCyclesPerMicrosecond();
}

uint32_t microsecondsToClockCycles(uint32_t a)
{
	return a * clockCyclesPerMicrosecond();
}
