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

static constexpr size_t DEFAULT_BUFFER_LIMIT = 32;

TwoWire::TwoWire(int port_id)
  : id(port_id)
  , fd(-1)
  , rxBuffer(nullptr)
  , rxBufferLength(0)
  , rxBufferLimit(0)
  , txAddress(0)
  , txBuffer(nullptr)
  , txBufferLength(0)
  , txBufferLimit(0)
{
}

TwoWire::~TwoWire()
{
  end();
}

void TwoWire::begin()
{
  if (fd >= 0) {
    DEBUG_I2C("[I2C] already open\n");
    return;
  }
  changeBufferLimits(DEFAULT_BUFFER_LIMIT, DEFAULT_BUFFER_LIMIT);
  fd = I2CMaster_Open(id);
  DEBUG_I2C("[I2C] I2CMaster_Open = %d\n", fd);
}

void TwoWire::end()
{
  if (fd >= 0) {
    close(fd);
    fd = -1;
  }
  if (rxBuffer != nullptr) {
    delete[] rxBuffer;
    rxBufferLimit = 0;
  }
  if (txBuffer != nullptr) {
    delete[] txBuffer;
    txBufferLimit = 0;
  }
}

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
  if (txBufferLength > 0 && address != txAddress) {
    endTransmission(true);
  }

  quantity = min(quantity, rxBufferLimit);
  ssize_t res = -1;
  if (txBufferLength > 0) {
    res = I2CMaster_WriteThenRead(fd, static_cast<I2C_DeviceAddress>(address),
                                  txBuffer, txBufferLength, rxBuffer, quantity);
    DEBUG_I2C("[I2C] I2CMaster_WriteThenRead = %d, errno = %d\n", res, errno);
  } else {
    res = I2CMaster_Read(fd, static_cast<I2C_DeviceAddress>(address), rxBuffer, quantity);
    DEBUG_I2C("[I2C] I2CMaster_Read = %d, errno = %d\n", res, errno);
  }

  rxBufferIndex = 0;
  rxBufferLength = res < 0 ? 0 : res - txBufferLength;
  txBufferLength = 0;
  return rxBufferLength;
}

void TwoWire::beginTransmission(uint8_t address)
{
  txAddress = address;
  txBufferLength = 0;
}

uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
  if (!sendStop) {
    return 0;
  }

  int res = I2CMaster_Write(fd, static_cast<I2C_DeviceAddress>(txAddress),
                            txBuffer, txBufferLength);
  DEBUG_I2C("[I2C] I2CMaster_Write = %d, errno = %d\n", res, errno);
  txBufferLength = 0;

  if (res < 0) {
    switch (errno) {
      case ENXIO:
        return 3;
      default:
        return 4;
    }
  }
  return 0;
}

uint8_t TwoWire::endTransmission(void)
{
  return endTransmission(true);
}

size_t TwoWire::write(uint8_t data)
{
  if (txBufferLength >= txBufferLimit) {
    return 0;
  }
  txBuffer[txBufferLength++] = data;
  return 1;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
  size_t count = 0;
  for (size_t i = 0; i < quantity; ++i) {
    count += write(data[i]);
  }
  return count;
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

void TwoWire::changeBufferLimits(size_t rxLimit, size_t txLimit)
{
  rxLimit = max(1, rxLimit);
  txLimit = max(1, txLimit);

  if (rxBufferLimit != rxLimit) {
    if (rxBuffer != nullptr) {
      delete[] rxBuffer;
    }
    rxBufferLimit = rxLimit;
    rxBuffer = new uint8_t[rxBufferLimit];
    rxBufferIndex = 0;
    rxBufferLength = 0;
  }

  if (txBufferLimit != txLimit) {
    if (txBuffer != nullptr) {
      delete[] txBuffer;
    }
    txBufferLimit = txLimit;
    txBuffer = new uint8_t[txBufferLimit];
    txBufferLength = 0;
  }
}

TwoWire Wire = TwoWire(AVNET_AESMS_ISU2_I2C);
TwoWire Wire1 = TwoWire(AVNET_AESMS_ISU1_I2C);
