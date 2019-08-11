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

#include <Arduino.h>
#include <variant.h>
#include <applibs/gpio.h>

#define ARRAYLEN(x) (sizeof(x) / sizeof((x)[0]))
static PinDescription *getArduinoPin(uint8_t arduinoPin)
{
  for (int i = 0; i < ARRAYLEN(pinsMap); i++)
    if (pinsMap[i].arduino == arduinoPin)
      return &pinsMap[i];
  return NULL;
}

void pinMode(uint8_t arduinoPin, uint8_t mode)
{
  PinDescription *n = getArduinoPin(arduinoPin);
  if (n)
  {
    if (INPUT == mode)
    {
      n->fd = GPIO_OpenAsInput(arduinoPin);
    }
    else
    {
      //TODO modes
      n->fd = GPIO_OpenAsOutput(arduinoPin, GPIO_OutputMode_PushPull, GPIO_Value_High);
    }
  }
}

void digitalWrite(uint8_t pin, uint8_t val)
{
  PinDescription *n = getArduinoPin(pin);
  if (n)
  {
    GPIO_SetValue(n->fd, (GPIO_Value_Type)val);
  }
}

int digitalRead(uint8_t pin)
{
  GPIO_Value_Type val;
  PinDescription *n = getArduinoPin(pin);
  if (n)
    return GPIO_GetValue(n->fd, &val) ? -1 : val;
  return -1;
}
