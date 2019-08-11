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

#ifndef WIFICLIENT_H
#define WIFICLIENT_H

#include <Arduino.h>
#include "Print.h"
#include "Client.h"
#include "IPAddress.h"

class wifiClient : public Client
{
private:
	int _sock, _peeked;
	volatile uint32_t _ring;
	bool connect_true;

public:
	wifiClient();
	wifiClient(uint8_t sock);

	int connect(IPAddress ip, uint16_t port);
	int connect(const char *host, uint16_t port);
	size_t write(uint8_t);
	size_t write(const uint8_t *buf, size_t size);
	int available();
	int read();
	int read(uint8_t *buf, size_t size);
	int peek();
	void flush();
	void stop();
	uint8_t connected();

	operator bool() { return connected(); }
	wifiClient &operator=(const wifiClient &other);
	bool operator==(const bool value) { return bool() == value; }
	bool operator!=(const bool value) { return bool() != value; }
	bool operator==(const wifiClient &);
	bool operator!=(const wifiClient &rhs) { return !this->operator==(rhs); };

	friend class wifiServer;
	using Print::write;

	int setSocketOption(int option, char *value, size_t len);
	int setOption(int option, int *value);
	int getOption(int option, int *value);
	int setTimeout(uint32_t seconds);
	int setNoDelay(bool nodelay);
	bool getNoDelay();
};

#endif // WIFICLIENT_H