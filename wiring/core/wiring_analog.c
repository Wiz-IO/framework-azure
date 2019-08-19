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

#include <variant.h>
#include <mt3620-adc.h>

int analogRead(uint8_t channel)
{
  static int adc_enabled = 0; // auto enable
  if (0 == adc_enabled)
  {
    EnableAdc();
    adc_enabled = 1;
  }
  return ReadAdc(channel);
}

void analogWrite(uint8_t pin, int val) {}

