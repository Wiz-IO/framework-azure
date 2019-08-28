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

HardwareSerial::HardwareSerial(int port_id) : id(port_id), fd(-1), peeked(0) {};

void HardwareSerial::begin(UART_Config *pUartConfig)
{
    fd = UART_Open(id, pUartConfig);
}

void HardwareSerial::begin(unsigned long baudrate)
{
    UART_Config uartConfig;
    memset(&uartConfig, 0, sizeof(UART_Config)); // non-blocking
    UART_InitConfig(&uartConfig);
    uartConfig.baudRate = baudrate;
    uartConfig.flowControl = UART_FlowControl_None;
    fd = UART_Open(id, &uartConfig);
}

size_t HardwareSerial::write(uint8_t c)
{
    int w = ::write(fd, &c, 1);
    return w == 1 ? w : 0;
}

int HardwareSerial::read(void)
{
    if (peeked)
    {
        peeked = 0;
        return pk;
    }
    char b;
    return ::read(fd, &b, 1) == 1 ? b : -1;
}

int HardwareSerial::available(void)
{
    if (fd < 0)
        return 0;
    int cnt = -1;
    return (0 == api_ioctl(fd, FIONREAD, (uint32_t)&cnt)) ? cnt : 0;
}

int HardwareSerial::peek(void)
{
    if (fd == -1 || !available())
        return -1;
    if (peeked)
    {
        return pk;
    }
    else
    {
        pk = read();
        if (pk != -1)
        {
            peeked = 1;
            return pk;
        }
    }
    return -1;
}

void HardwareSerial::flush(void)
{
    api_ioctl(fd, TCFLSH, 2); // flush both
};
