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

#include <interface.h>

void abort(void)
{
    while (1)
    {
    }
}

int _sbrk(int size) { return -1; }
int _open_r(struct _reent *r, const char *filename, int flags, int mode) { return -1; }
int _read_r(void *r, int fd, void *buf, size_t len) { return -1; }
int _write_r(void *r, int fd, const void *buf, size_t len) { return -1; }
int _lseek_r(void *r, int fd, int where, int whence) { return 0; }
int _close_r(void *r, int fd) { return -1; }
int _fstat_r(void *r, int fd, void *s) { return 0; }
int _stat_r(void *r, const char *path, void *st) { return 0; }

////////////////////////////////////////////////////////////////////////////
// CPP
////////////////////////////////////////////////////////////////////////////

void __cxa_finalize(void *handle) {}
void __cxa_pure_virtual(void) { abort(); }
void __cxa_deleted_virtual(void) { abort(); }

extern void (*__preinit_array_start[])(void) __attribute__((weak));
extern void (*__preinit_array_end[])(void) __attribute__((weak));
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));
extern void (*__fini_array_start[])(void) __attribute__((weak));
extern void (*__fini_array_end[])(void) __attribute__((weak));
extern void _init(void) __attribute__((weak));
extern void _fini(void) __attribute__((weak));

void __libc_init_array(void)
{
    size_t count;
    size_t i;
#if 0    
    count = __preinit_array_end - __preinit_array_start;
    for (i = 0; i < count; i++)
        __preinit_array_start[i]();
    _init();
#endif
    count = __init_array_end - __init_array_start;
    for (i = 0; i < count; i++)
        __init_array_start[i]();
}

void __libc_fini_array(void)
{
    size_t count;
    size_t i;
    count = __fini_array_end - __fini_array_start;
    for (i = count; i > 0; i--)
        __fini_array_start[i - 1]();
    _fini();
}

int abs(int j)
{
    return (j < 0 ? -j : j);
}

void reverse(char *begin, char *end)
{
    char *is = begin;
    char *ie = end - 1;
    while (is < ie)
    {
        char tmp = *ie;
        *ie = *is;
        *is = tmp;
        ++is;
        --ie;
    }
}

long atol(const char *s)
{
    long val = 0;
    if (s)
    {
        sscanf(s, "%ld", &val);
    }
    return val;
}

static const char *str_digits = "0123456789abcdef";
char *itoa(int value, char *result, int base)
{
    if (result)
    {
        if (base < 2 || base > 16)
        {
            *result = 0;
            return result;
        }
        char *out = result;
        int quotient = abs(value);
        do
        {
            const int tmp = quotient / base;
            *out = str_digits[quotient - (tmp * base)];
            ++out;
            quotient = tmp;
        } while (quotient);
        if (value < 0)
            *out++ = '-';
        reverse(result, out);
        *out = 0;
    }
    return result;
}

char *ltoa(long value, char *result, int base)
{
    if (result)
    {
        if (base < 2 || base > 16)
        {
            *result = 0;
            return result;
        }
        char *out = result;
        long quotient = abs(value);
        do
        {
            const long tmp = quotient / base;
            *out = str_digits[quotient - (tmp * base)];
            ++out;
            quotient = tmp;
        } while (quotient);
        if (value < 0)
            *out++ = '-';
        reverse(result, out);
        *out = 0;
    }
    return result;
}

char *utoa(unsigned value, char *result, int base)
{
    if (result)
    {
        if (base < 2 || base > 16)
        {
            *result = 0;
            return result;
        }
        char *out = result;
        unsigned quotient = value;
        do
        {
            const unsigned tmp = quotient / base;
            *out = str_digits[quotient - (tmp * base)];
            ++out;
            quotient = tmp;
        } while (quotient);
        reverse(result, out);
        *out = 0;
    }
    return result;
}

char *ultoa(unsigned long value, char *result, int base)
{
    if (result)
    {
        if (base < 2 || base > 16)
        {
            *result = 0;
            return result;
        }
        char *out = result;
        unsigned long quotient = value;
        do
        {
            const unsigned long tmp = quotient / base;
            *out = str_digits[quotient - (tmp * base)];
            ++out;
            quotient = tmp;
        } while (quotient);
        reverse(result, out);
        *out = 0;
    }
    return result;
}

double atof(const char *s)
{
    double val;
    sscanf(s, "%lf", &val);
    return val;
}
