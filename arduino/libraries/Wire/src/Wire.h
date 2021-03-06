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
  
  Modified: Junxiao Shi
 */

#ifndef TwoWire_h
#define TwoWire_h

#include <inttypes.h>

#ifdef __cplusplus
extern "C"{
#endif

extern uint8_t TWBR;

#ifdef __cplusplus
} // extern "C"
#endif

#include "Stream.h"

#define BUFFER_LENGTH 32

class TwoWire : public Stream {
  private:
    int id;
    int fd;
    uint8_t* rxBuffer;
    size_t rxBufferIndex;
    size_t rxBufferLength;
    size_t rxBufferLimit;
    uint8_t txAddress;
    uint8_t* txBuffer;
    size_t txBufferLength;
    size_t txBufferLimit;

  public:
    TwoWire(int port_id);
    ~TwoWire();
    void begin();
    void end();
    void begin(uint8_t);
    void setClock(uint32_t);
    void beginTransmission(uint8_t);
    uint8_t endTransmission(void);
    uint8_t endTransmission(uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void){}

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;

  public:
    /** \brief Change buffer size limits.
     *  \param rxLimit read buffer size.
     *  \param txLimit write buffer size.
     */
    void changeBufferLimits(size_t rxLimit, size_t txLimit);
};

extern TwoWire Wire;
extern TwoWire Wire1;

#endif

