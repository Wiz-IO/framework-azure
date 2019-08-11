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
#include <applibs/log.h>

void HardwareSerial::begin(unsigned long baudrate)
{
    UART_Config uartConfig;
    memset(&uartConfig, 0, sizeof(UART_Config));
    UART_InitConfig(&uartConfig);
    uartConfig.baudRate = baudrate;
    uartConfig.flowControl = UART_FlowControl_None;
    fd = UART_Open(id, &uartConfig);
    //Log_Debug("[UART] fd =  %d", fd);
}

size_t HardwareSerial::write(uint8_t c)
{
    ssize_t sent = ::write(fd, &c, 1);
    return (sent == 1) ? 1 : 0;
}

int HardwareSerial::read(void)
{
    char data;
    int cnt = ::read(fd, &data, 1);
    return (cnt == 1) ? data : -1;
}

int HardwareSerial::available(void) { 
    // TODO
    return 0; 
}

int HardwareSerial::peek(void) { 
    // TODO
    return -1; 
}