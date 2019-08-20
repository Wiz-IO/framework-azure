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

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include "Stream.h"
#include "interface.h"

class HardwareSerial : public Stream
{
private:
  uint32_t uart_base;

public:
  HardwareSerial(uint32_t base)
  {
    uart_base = base;
  };
  ~HardwareSerial(){};
  void begin(); /* Configure UART to use 115200-8-N-1 */
  void begin(unsigned long); 
  void end(void) {}
  virtual int available(void);
  virtual int peek(void);
  virtual int read(void);
  virtual void flush(void){};
  virtual size_t write(uint8_t);
  using Print::write;
  operator bool() { return true; }

  void Write(const char *msg);
};

extern HardwareSerial Serial;

#endif
