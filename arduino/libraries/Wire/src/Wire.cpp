/*
    Created on: 01.01.2019
    Author: Georgi Angelov
        http://www.wizio.eu/
        https://github.com/Wiz-IO    
		
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

extern "C"
{
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
}

#ifndef SYSROOT_2_BETA1905
#error Only Sysroot 2+Beta1905 or up !!! Project ini - Add line: board_build.sysroot = 2+Beta1905
#endif

#include "Arduino.h"
#include "Wire.h"
#include <applibs/i2c.h>

#include <variant.h>
#define DEBUG_I2C 
//Serial.printf

uint8_t TwoWire::rxBuffer[BUFFER_LENGTH];
uint8_t TwoWire::rxBufferIndex = 0;
uint8_t TwoWire::rxBufferLength = 0;

uint8_t TwoWire::txAddress = 0;
uint8_t TwoWire::txBuffer[BUFFER_LENGTH];
uint8_t TwoWire::txBufferIndex = 0;
uint8_t TwoWire::txBufferLength = 0;

TwoWire::TwoWire(int port_id) : fd(-1)
{
  id = port_id;
}

void TwoWire::begin()
{
  rxBufferIndex = 0;
  rxBufferLength = 0;
  txBufferIndex = 0;
  txBufferLength = 0;
  fd = I2CMaster_Open(id);
  DEBUG_I2C("[I2C] I2CMaster_Open = %d\n", fd);
}

void TwoWire::end(void){}

void TwoWire::setClock(uint32_t frequency)
{
  int rc = I2CMaster_SetBusSpeed(fd, I2C_BUS_SPEED_STANDARD);
  if (rc != 0)
  {
    DEBUG_I2C("[ERROR] I2CMaster_SetBusSpeed\n");
  }
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop)
{
  if (quantity > BUFFER_LENGTH)
    quantity = BUFFER_LENGTH;
  uint8_t rd = I2CMaster_Read(fd, (I2C_DeviceAddress)address, (uint8_t *)rxBuffer, quantity);
  DEBUG_I2C("[I2C] I2CMaster_Read = %d\n", (int)rd);
  rxBufferIndex = 0;
  rxBufferLength = (rd == 0) ? quantity : 0;
  return rxBufferLength;
}

void TwoWire::beginTransmission(uint8_t address)
{
  txAddress = address;
  txBufferIndex = 0;
  txBufferLength = 0;
}

uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
  uint8_t wr = I2CMaster_Write(fd, (I2C_DeviceAddress)txAddress, (uint8_t *)txBuffer, txBufferLength);
  DEBUG_I2C("[I2C] I2CMaster_Write = %d\n", (int)wr);
  txBufferIndex = 0;
  txBufferLength = 0;
  return wr;
}

uint8_t TwoWire::endTransmission(void)
{
  return endTransmission(true);
}

size_t TwoWire::write(uint8_t data)
{
  if (txBufferLength >= BUFFER_LENGTH)
    return 0;
  txBuffer[txBufferIndex] = data;
  ++txBufferIndex;
  txBufferLength = txBufferIndex;
  return 1;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
  for (size_t i = 0; i < quantity; ++i)
  {
    write(data[i]);
  }
  return quantity;
}

int TwoWire::available(void)
{
  return rxBufferLength - rxBufferIndex;
}

int TwoWire::read(void)
{
  int value = -1;
  if (rxBufferIndex < rxBufferLength)
  {
    value = rxBuffer[rxBufferIndex];
    ++rxBufferIndex;
  }
  return value;
}

int TwoWire::peek(void)
{
  int value = -1;
  if (rxBufferIndex < rxBufferLength)
  {
    value = rxBuffer[rxBufferIndex];
  }
  return value;
}

void TwoWire::begin(uint8_t address)
{
  begin();
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  return requestFrom(address, quantity, (uint8_t) true);
}

TwoWire Wire = TwoWire(AVNET_AESMS_ISU2_I2C);
TwoWire Wire1 = TwoWire(AVNET_AESMS_ISU1_I2C);
