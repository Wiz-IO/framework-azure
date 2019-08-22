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

HardwareSerial::HardwareSerial(int port_id) : id(port_id), fd(-1), ring_buffer(0), ring_count(0){};

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
    if (fd < 0)
        return 0;
    ssize_t sent = ::write(fd, &c, 1);
    return (sent == 1) ? 1 : 0;
}

char HardwareSerial::get()
{
    char data = ring_buffer & 0xFF;
    ring_buffer >>= 8;
    ring_count--;
    return data;
}

int HardwareSerial::read(char *buf, int size)
{
#define MIN(a, b) ((a) < (b) ? a : b)
    if (fd < 0 || NULL == buf || size < 1)
        return -1;
    int rd = 0;
    if (ring_count > 0)
    {
        int m = MIN(size, ring_count);
        while (m > 0)
        {
            *buf++ = get();
            size--;
            rd++;
            m--;
        }
    }
    if (size)
    {
        int cnt = ::read(fd, buf, size);
        if (cnt > 0)
            rd += cnt;
    }
    return (rd) ? rd : -1;
}

int HardwareSerial::read(void)
{
    char data;
    return (1 == this->read(&data, 1)) ? data : 0;
}

/// NOT EXIST ioctl(serial_fd, FIONREAD, &bytes_avail);
int HardwareSerial::available(void)
{
    if (fd < 0)
        return 0;
    if (ring_count > 0)
        return ring_count;
    ring_count = ::read(fd, &ring_buffer, sizeof(ring_buffer)); /* max 8 bytes */
    return (ring_count > 0) ? ring_count : 0;
}

int HardwareSerial::peek(void)
{
    if (available())
    {
        if (ring_count > 0)
            return ring_buffer & 0xFF; // get ring_char[0]
    }
    return -1;
}

void HardwareSerial::flush(void)
{
    ring_buffer = 0;
    ring_count = 0;
    while (read() > 0)
    {
    }
};
