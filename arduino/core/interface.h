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

#ifndef INTERFACE_H_
#define INTERFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include <applibs/log.h>

    unsigned int seconds(void);
    unsigned int millis(void);
    unsigned int micros(void);
    void delay(unsigned int);
    void delayMicroseconds(unsigned int us);

    long atol(const char *s);
    char *itoa(int value, char *result, int base);
    char *ltoa(long value, char *result, int base);
    char *utoa(unsigned value, char *result, int base);
    char *ultoa(unsigned long value, char *result, int base);

    uint32_t clockCyclesPerMicrosecond(void);
    uint32_t clockCyclesToMicroseconds(uint32_t a);
    uint32_t microsecondsToClockCycles(uint32_t a);

    int analogRead(uint8_t pin);
    void analogWrite(uint8_t pin, int val);    

#ifndef SERIAL_BUFFER_SIZE
#define SERIAL_BUFFER_SIZE 1024
#endif

#define ENTER_CRITICAL()  \
    do                    \
    {                     \
        __asm("cpsid i"); \
    } while (0)

#define EXIT_CRITICAL()   \
    do                    \
    {                     \
        __asm("cpsie i"); \
    } while (0)

void waitWifi(void);

#ifdef __cplusplus
} 
#endif
#endif /* INTERFACE_H_ */
