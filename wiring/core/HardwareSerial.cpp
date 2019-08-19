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

#include "HardwareSerial.h"

void HardwareSerial::begin() // Configure UART to use 115200-8-N-1.
{
    WriteReg32(UART_BASE, 0x0C, 0x80); // LCR (enable DLL, DLM)
    WriteReg32(UART_BASE, 0x24, 0x3);  // HIGHSPEED
    WriteReg32(UART_BASE, 0x04, 0);    // Divisor Latch (MS)
    WriteReg32(UART_BASE, 0x00, 1);    // Divisor Latch (LS)
    WriteReg32(UART_BASE, 0x28, 224);  // SAMPLE_COUNT
    WriteReg32(UART_BASE, 0x2C, 110);  // SAMPLE_POINT
    WriteReg32(UART_BASE, 0x58, 0);    // FRACDIV_M
    WriteReg32(UART_BASE, 0x54, 223);  // FRACDIV_L
    WriteReg32(UART_BASE, 0x0C, 0x03); // LCR (8-bit word length)
}

void HardwareSerial::Write(const char *msg)
{
    while (*msg)
    {
        // When LSR[5] ->THRE is set, can write another character.
        while (!(ReadReg32(UART_BASE, 0x14) & (UINT32_C(1) << 5)))
        {
        }
        WriteReg32(UART_BASE, 0x0, *msg++);
    }
}

size_t HardwareSerial::write(uint8_t c)
{
    // When LSR[5] ->THRE is set, can write another character.
    while (!(ReadReg32(UART_BASE, 0x14) & (UINT32_C(1) << 5)))
    {
    }
    WriteReg32(UART_BASE, 0x0, c);
}

int HardwareSerial::read(void)
{
    // TODO
    return -1;
}

int HardwareSerial::available(void)
{
    // TODO
    return 0;
}

int HardwareSerial::peek(void)
{
    // TODO
    return -1;
}
