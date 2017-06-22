#pragma once

/*
 * Print.cpp - Base class that provides print() and println()
 * Copyright (c) 2008 David A. Mellis.  All right reserved.
 * Copyright (c) 2011 LeafLabs, LLC.
 * Copyright (c) 2017 Kacper Zybala
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * Modified 23 November 2006 by David A. Mellis
 * Modified 12 April 2011 by Marti Bolivar <mbolivar@leaflabs.com>
 * Rewritten 22 June 2017 by Kacper Zybala
 */

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdarg>
#include <climits>

#define DEC 10
#define OCT 8
#define BIN 2
#define HEX 16
#define BYTE 1

typedef std::string String;
typedef uint64_t uint64;
typedef uint16_t uint16;
typedef uint32_t uint32;

class Print;

class Printable
{
  public:
    virtual size_t printTo(Print& p) const = 0;
};


class Print
{
  public:
    Print() : write_error(0) {}

    int getWriteError() { return write_error; }
    void clearWriteError() { setWriteError(0); }

    virtual size_t write(uint8_t) = 0;
    size_t write(const char *str) {
      if (str == NULL) return 0;
      return write((const uint8_t *)str, strlen(str));
    }
    virtual size_t write(const uint8_t *buffer, size_t size);
    size_t write(const char *buffer, size_t size) {
      return write((const uint8_t *)buffer, size);
    }

    // print
    size_t print(char);
    size_t print(const char[]);

    size_t print(unsigned long, int base = DEC);
    size_t print(long, int base = DEC);

    size_t print(unsigned int, int base = DEC);
    size_t print(unsigned char, int base = DEC);
    size_t print(int, int base = DEC);
    size_t print(double, int digits = 2);

    size_t print(const Printable &p);
    size_t print(const String &s);

    // println
    size_t println(void);

    size_t println(const char[]);
    size_t println(char);

    size_t println(unsigned char, int base = DEC);
    size_t println(unsigned int, int base = DEC);
    size_t println(unsigned long, int base = DEC);
    size_t println(int, int base = DEC);
    size_t println(long, int base = DEC);
    size_t println(double, int digits = 2);

    size_t println(const Printable &p);
    size_t println(const String &s);

    // printf
    size_t printf(const char *fmt, ...);

  private:
    int write_error;
    size_t printNumber(unsigned long, uint8_t);
    size_t printFloat(double, uint8_t);
  protected:
    void setWriteError(int err = 1) { write_error = err; }
};
