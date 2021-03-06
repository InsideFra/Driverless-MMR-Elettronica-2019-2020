
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include <stddef.h>

// Stuff that is normally provided by Arduino
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define _BV(x) (1<<(x))

#define IF_SERIAL_DEBUG(x)

// Avoid spurious warnings
//#if ! defined( NATIVE ) && defined( ARDUINO )
//#define PROGMEM __attribute__(( section(".progmem.data") ))
//#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))

// Progmem is Arduino-specific
#define PRIPSTR "%S"

//typedef char const char;
//typedef uint16_t prog_uint16_t;
//#define PSTR(x) (x)
//#define printf_P printf
//#define strlen_P strlen
//#define PROGMEM

#define pgm_read_word(p) (*(p))
//#define PRIPSTR "%s"
