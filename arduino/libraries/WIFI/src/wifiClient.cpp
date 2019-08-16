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

#include "wifiClient.h"
#include <interface.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <time.h>

#include <variant.h>
#define DEBUG_CLIENT 
// Serial.printf

wifiClient::wifiClient() : _sock(-1), connect_true(0), _ring(0), _peeked(0)
{
}

wifiClient::wifiClient(uint8_t sock) : _sock(-1), connect_true(1), _ring(0), _peeked(0)
{
}

void wifiClient::stop()
{
	if (_sock < 0)
		return;
	connect_true = false;
	::close(_sock);
	_sock = -1;
	_ring = _peeked = 0;
	//DEBUG_CLIENT("[TCP] stop()\n");
}

static int _connect(int sock, struct sockaddr_in *psin, unsigned int len, uint32_t timeout)
{
	int ret;
/*	
	DEBUG_CLIENT("[TCP] IP: %d.%d.%d.%d : %d\n",
				 (int)((psin->sin_addr.s_addr) & 0xFF),
				 (int)((psin->sin_addr.s_addr >> 8) & 0xFF),
				 (int)((psin->sin_addr.s_addr >> 16) & 0xFF),
				 (int)((psin->sin_addr.s_addr >> 24) & 0xFF),
				 (int)(int)ntohs(psin->sin_port));
*/
	ret = connect(sock, (struct sockaddr *)psin, len);
	if (ret < 0)
	{
		DEBUG_CLIENT("[ERROR] TCP connect %d\n", ret);
		close(sock);
		return ret;
	}
	/* SET DEFAULT */
	int enable = 1;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&enable, sizeof(enable));
	setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char *)&enable, sizeof(enable));
	//DEBUG_CLIENT("[TCP] Connected\n");
	return ret;
}

int wifiClient::connect(const char *host, uint16_t port)
{
	struct hostent *hp;
	int ret = 0;
	//DEBUG_CLIENT("[TCP] Connecting: %s : %d\n", host, (int)port);
	if (host == NULL || _sock != -1)
	{
		DEBUG_CLIENT("[ERROR] TCP socket\n");
		_sock = -1;
		return 0;
	}
	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sock < 0)
	{
		DEBUG_CLIENT("[ERROR] TCP unable to open a TCP socket\n");
		delay(1000);
		return 0;
	}
	hp = gethostbyname(host);
	if (hp == NULL)
	{
		DEBUG_CLIENT("[ERROR] TCP gethostbyname %s fail\n", host);
		delay(1000);
		return 0;
	}
	struct sockaddr_in _sin;
	memcpy(&_sin.sin_addr, hp->h_addr, sizeof(_sin.sin_addr));
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	ret = _connect(_sock, &_sin, sizeof(_sin), 20000);
	if (ret < 0)
	{
		DEBUG_CLIENT("[ERROR] TCP unable to connect to target host %s\n", host);
		return 0;
	}
	if (ret == 0)
		connect_true = true;
	setTimeout(10); // seconds
	return 1;
}

int wifiClient::connect(IPAddress ip, uint16_t port)
{
	int ret = 0;
	if (_sock != -1)
		return 0;
	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sock < 0)
	{
		DEBUG_CLIENT("[ERROR] TCP unable to open a TCP socket\n");
		return 0;
	}
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = (uint32_t)ip;
	sin.sin_port = htons(port);
	ret = _connect(_sock, &sin, sizeof(sin), 20000);
	if (ret < 0)
	{
		DEBUG_CLIENT("[ERROR] TCP unable to connect to target ip\n");
		return 0;
	}
	if (ret == 0)
		connect_true = true;
	return 1;
}

size_t wifiClient::write(uint8_t b)
{
	return write(&b, 1);
}

size_t wifiClient::write(const uint8_t *buf, size_t size)
{
	if (_sock < 0)
		return 0;
	//DEBUG_CLIENT("[TCP] write( %d )\n", size);
	if (::send(_sock, (char *)buf, size, 0) < 0)
	{
		//DEBUG_CLIENT("[ERROR] TCP write send\n");
		stop();
		size = 0;
	}
	return size;
}

int wifiClient::read()
{
	uint8_t b;
	return read(&b, 1) == 1 ? b : -1;
}

int wifiClient::read(uint8_t *buf, size_t size)
{
	if (_sock < 0 || 0 == buf || 0 == size)
		return -1;
	//DEBUG_CLIENT("[TCP] read( %d )\n", size);
	int cnt = -1;
	if (_peeked > 0)
	{
		*buf++ = _ring & 0xFF;
		size--;
		cnt = 1;
		_peeked = 0;
	}
	if (size)
	{
		int rc = ::recv(_sock, (char *)buf, size, 0);
		if (rc > 0)
			cnt += rc;
	}
	return cnt;
}

int wifiClient::available()
{
	if (_sock < 0)
	{
		DEBUG_CLIENT("[ERROR] TCP available sock\n");
		return 0;
	}
#if 0    
	int cnt = -1; return ( 0 == ioctl(_sock, FIONREAD, &cnt) ) ? cnt : 0; // not exist ioctl()
#endif
	if (_peeked)
	{
		//DEBUG_CLIENT("[TCP] available _peeked = %d\n", _peeked);
		return _peeked;
	}
	//DEBUG_CLIENT("[TCP] available try recv(1)\n");
	_ring = 0;
	_peeked = ::recv(_sock, (char *)&_ring, 1, 0); // try receive
	if (_peeked > 0)
	{
		//DEBUG_CLIENT("[TCP] available recv() = %d\n", _peeked);
		return _peeked;
	}
	//DEBUG_CLIENT("[TCP] available = 0\n");
	_peeked = 0;
	return _peeked; // 0
}

int wifiClient::peek()
{
	if (_sock < 0 || !available())
	{
		DEBUG_CLIENT("[ERROR] TCP peek sock\n");
		return -1;
	}
	if (_peeked)
		return *((char *)&_ring);
	char b;
	return (recv(_sock, &b, 1, MSG_PEEK) > 0) ? b : -1;
}

void wifiClient::flush()
{
	if (_sock < 0)
		return;
	while (available())
		read();
	_ring = _peeked = 0;
}

uint8_t wifiClient::connected()
{
	return connect_true == true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool wifiClient::getNoDelay()
{
	int flag = 0;
	getOption(TCP_NODELAY, &flag);
	return flag;
}

int wifiClient::setNoDelay(bool nodelay)
{
	//long iMode = 1; //non-blocking mode is enabled > 0
	//ioctl(_sock, FIONBIO, &iMode);
	int flag = nodelay;
	return setOption(TCP_NODELAY, &flag);
}

int wifiClient::getOption(int option, int *value)
{
	socklen_t size = sizeof(int);
	int res = getsockopt(_sock, IPPROTO_TCP, option, (char *)value, &size);
	if (res < 0)
	{
		DEBUG_CLIENT("[ERROR] get IPPROTO_TCP\n");
	}
	return res;
}

int wifiClient::setOption(int option, int *value)
{
	int res = setsockopt(_sock, IPPROTO_TCP, option, (char *)value, sizeof(int));
	if (res < 0)
	{
		DEBUG_CLIENT("[ERROR] set IPPROTO_TCP\n");
	}
	return res;
}

int wifiClient::setSocketOption(int option, char *value, size_t len)
{
	int res = setsockopt(_sock, SOL_SOCKET, option, value, len);
	if (res < 0)
	{
		DEBUG_CLIENT("[ERROR] set SOL_SOCKET %X : %d\n", option, errno);
	}
	return res;
}

int wifiClient::setTimeout(uint32_t seconds)
{
	Client::setTimeout(seconds * 1000);
	struct timeval tv;
	tv.tv_sec = seconds;
	tv.tv_usec = 0;
	if (setSocketOption(SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval)) < 0)
	{
		DEBUG_CLIENT("[ERROR] set SO_RCVTIMEO\n");
		return -1;
	}
	return setSocketOption(SO_SNDTIMEO, (char *)&tv, sizeof(struct timeval));
}
