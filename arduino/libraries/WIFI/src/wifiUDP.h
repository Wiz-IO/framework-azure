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

#ifndef wifiUDP_h
#define wifiUDP_h

#include <Arduino.h>
#include <Udp.h>
#include <cbuf.h>

class wifiUDP : public UDP
{
private:
    int udp_server;
    IPAddress multicast_ip;
    IPAddress remote_ip;
    uint16_t remote_port;
    char buffer[1460];
    size_t buffer_len;
    cbuf *rx_buffer;

public:
    wifiUDP() : udp_server(-1), remote_port(0), buffer_len(0), rx_buffer(0) {}
    ~wifiUDP()
    {
        stop();
        if (rx_buffer)
            delete rx_buffer;
    }
    virtual uint8_t begin(uint16_t);
    virtual uint8_t beginMulticast(IPAddress a, uint16_t p)
    {
        multicast_ip = a;
        return begin(p);
    }
    virtual void stop();
    virtual int beginPacket();
    virtual int beginPacket(IPAddress ip, uint16_t port);
    virtual int beginPacket(const char *host, uint16_t port);
    virtual int endPacket();
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);
    virtual int parsePacket();
    virtual int available();
    virtual int read();
    virtual int read(unsigned char *buffer, size_t len);
    virtual int read(char *buffer, size_t len);
    virtual int peek();
    virtual void flush();
    virtual IPAddress remoteIP();
    virtual uint16_t remotePort();
};

#endif // wifiUDP_h
