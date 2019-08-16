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

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <stdio.h>
#include "Arduino.h"
#define SPI_STRUCTS_VERSION 1
#include <applibs/spi.h>

#define SPI_HAS_TRANSACTION

#define SPI_MODE0 SPI_Mode_0
#define SPI_MODE1 SPI_Mode_1
#define SPI_MODE2 SPI_Mode_2
#define SPI_MODE3 SPI_Mode_3

class SPISettings
{
public:
  SPISettings() : freq(4000000), mode(SPI_MODE0) {}
  SPISettings(uint32_t clockFreq, uint8_t bitOrder, uint8_t dataMode)
  {
    freq = clockFreq;
    mode = dataMode;
    order = bitOrder;
  }

private:
  uint32_t freq;
  uint32_t mode;
  uint32_t order;
  friend class SPIClass;
};

class SPIClass
{
private:
  int fd;
  SPI_InterfaceId interfaceId;
  SPI_ChipSelectId chipSelectId;

public:
  SPIClass(int interface, int chip_selet);
  void begin();
  void end() {}
  void setDataMode(uint32_t);
  void setClockDivider(uint32_t){};
  void setClock(uint32_t);
  void beginTransaction(SPISettings settings);
  uint8_t transfer(uint8_t data);
  inline static void endTransaction(void);
  inline static void setBitOrder(uint32_t);
};

extern SPIClass SPI;
extern SPIClass SPI1;

#endif
