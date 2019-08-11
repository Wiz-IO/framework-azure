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

#define UART_STRUCTS_VERSION 1
#include <applibs/uart.h>

class HardwareSerial : public Stream
{
private:
	int fd;
	UART_Id id;

public:
	HardwareSerial(int port_id) { id = (UART_Id)port_id; };
	~HardwareSerial(){};
	void begin(unsigned long);
	void end(void);
	virtual int available(void);
	virtual int peek(void);
	virtual int read(void);
	virtual void flush(void){};
	virtual size_t write(uint8_t);
	using Print::write;
	operator bool() { return true; }
};

extern HardwareSerial Serial;

#endif
