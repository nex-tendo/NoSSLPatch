#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

#define RETURN_TO_HBL 			(0)
#define RETURN_TO_NEXT_APP 		(-3)
