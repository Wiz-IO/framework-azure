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

#include "SPI.h"

#include <variant.h>
#define DEBUG_SPI
//Serial.printf

void SPIClass::begin()
{
  SPIMaster_Config config;
  int ret = SPIMaster_InitConfig(&config);
  config.csPolarity = SPI_ChipSelectPolarity_ActiveLow;
  fd = SPIMaster_Open(interfaceId, chipSelectId, &config);
  if (fd < 0)
  {
    DEBUG_SPI("[ERROR] SPIMaster_Open: errno=%d (%s)\n", errno, strerror(errno));
  }
}

void SPIClass::setDataMode(uint32_t mode)
{
  int rc = SPIMaster_SetMode(fd, SPI_Mode_3);
  if (rc != 0)
  {
    DEBUG_SPI("[ERROR] SPIMaster_SetMode: errno=%d (%s)\n", errno, strerror(errno));
  }
}

void SPIClass::setClock(uint32_t rate)
{
  int rc = SPIMaster_SetBusSpeed(fd, 400000);
  if (rc != 0)
  {
    DEBUG_SPI("[ERROR] SPIMaster_SetBusSpeed: errno=%d (%s)\n", errno, strerror(errno));
  }
}

uint8_t SPIClass::transfer(uint8_t data)
{
  uint8_t ret = 0;
  SPIMaster_WriteThenRead(fd, &data, 1, &ret, 1);
  return ret;
}

void SPIClass::beginTransaction(SPISettings settings)
{
  setDataMode(settings.mode);
  setClock(settings.freq);
  int rc = SPIMaster_SetBitOrder(fd, (SPI_BitOrder)settings.order);
  if (rc != 0)
  {
    DEBUG_SPI("[ERROR] SPIMaster_SetMode: errno=%d (%s)\n", errno, strerror(errno));
  }
}

SPIClass::SPIClass(int interface, int chip_selet) : fd(-1)
{
  interfaceId = (SPI_InterfaceId)interface;
  chipSelectId = (SPI_ChipSelectId)chip_selet;
}

SPIClass SPI(MT3620_ISU0_SPI, MT3620_SPI_CS_A);
SPIClass SPI1(MT3620_ISU1_SPI, MT3620_SPI_CS_B);
