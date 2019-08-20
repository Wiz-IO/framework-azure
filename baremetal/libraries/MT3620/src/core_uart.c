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

#include <mt3620-baremetal.h>
#include <core_periphery.h>

int Uart_SetFormat(uint32_t BASE, uint32_t baudrate, uint16_t databit, uint16_t parity, uint16_t stopbit)
{
    uint16_t control_word;
    uint32_t data, uart_lcr, high_speed_div, sample_count, sample_point, fraction;
    uint16_t fraction_L_mapping[] = {0x00, 0x10, 0x44, 0x92, 0x29, 0xaa, 0xb6, 0xdb, 0xad, 0xff, 0xff};
    uint16_t fraction_M_mapping[] = {0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03};
    // 100, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600
    WriteReg32(BASE, UART_RATE_STEP, 0x3); // based on sampe_count * baud_pulse, baud_rate = system clock frequency / sampe_count
    /* DLAB start */
    uart_lcr = ReadReg32(BASE, UART_LCR);
    WriteReg32(BASE, UART_LCR, (uart_lcr | UART_LCR_DLAB));
    data = UART_CLOCK_FREQ / baudrate;
    high_speed_div = (data >> 8) + 1; // divided by 256
    {
        sample_count = data / high_speed_div - 1;
        if (sample_count == 3)
        {
            sample_point = 0;
        }
        else
        {
            sample_point = sample_count / 2 - 1;
        }
        if (!(data >= 4))
            return -1;
    }
    fraction = (UART_CLOCK_FREQ * 10 / baudrate / data - (sample_count + 1) * 10) % 10;
    WriteReg32(BASE, UART_DLL, (high_speed_div & 0x00ff));
    WriteReg32(BASE, UART_DLH, ((high_speed_div >> 8) & 0x00ff));
    WriteReg32(BASE, UART_STEP_COUNT, sample_count);
    WriteReg32(BASE, UART_SAMPLE_COUNT, sample_point);
    WriteReg32(BASE, UART_FRACDIV_M, fraction_M_mapping[fraction]);
    WriteReg32(BASE, UART_FRACDIV_L, fraction_L_mapping[fraction]);
    WriteReg32(BASE, UART_LCR, uart_lcr);
    /* DLAB end */
    WriteReg32(BASE, UART_FCR, 0x77);
    control_word = ReadReg32(BASE, UART_LCR); /* DLAB start */
    control_word &= ~UART_DATA_MASK;
    control_word |= databit;
    control_word &= ~UART_STOP_MASK;
    control_word |= stopbit;
    control_word &= ~UART_PARITY_MASK;
    control_word |= parity;
    WriteReg32(BASE, UART_LCR, control_word); /* DLAB End */
    return 0;
}