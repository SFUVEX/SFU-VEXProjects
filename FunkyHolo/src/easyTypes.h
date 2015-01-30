/*
 * easyTypes.h
 *
 *  Created on: Jan 29, 2015
 *      Author: awiebe
 */

#include <stdint.h>

#ifndef EASYTYPES_H_
#define EASYTYPES_H_

/**
 * For noobs who can't figure out storage types in c.
 * include this file and you can specify them as
 * s for signed
 * u for unsigned
 * and then the number of bits
 * e.g. s16 is a signed 16 bit integer
 */

typedef uint8_t u8; //unsigned char
typedef int8_t s8;  //signed char
typedef s8 byte;

typedef uint16_t u16; //ushort
typedef int16_t s16; //short

typedef uint32_t u32; //ulong
typedef int32_t s32; //long

typedef uint64_t u32; //u long long
typedef int64_t s32; //u long long

typedef char* String;


#endif /* EASYTYPES_H_ */
