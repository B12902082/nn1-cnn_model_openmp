// my_endian.h
#ifndef MY_ENDIAN_H
#define MY_ENDIAN_H

#include <stdint.h>

/* Check for the standard <endian.h> and use it if available (Linux/macOS) */
#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
#  include <endian.h>
#else
/* Windows/Generic implementation */

#  include <stdlib.h> // Required for MSVC's _byteswap_ulong

/* 1. Define a platform-specific 32-bit byte swap function */
#  if defined(_MSC_VER)
    // Microsoft Visual C++ (MSVC)
#    define __bswap_32(x) _byteswap_ulong(x)
#  elif defined(__GNUC__) || defined(__clang__)
    // GCC or Clang (e.g., MinGW/Cygwin)
#    define __bswap_32(x) __builtin_bswap32(x)
#  else
    // Generic implementation for any other compiler
#    define __bswap_32(x) \
        ((((x) & 0xff000000U) >> 24) | \
         (((x) & 0x00ff0000U) >>  8) | \
         (((x) & 0x0000ff00U) <<  8) | \
         (((x) & 0x000000ffU) << 24))
#  endif


/* 2. Define be32toh (Big Endian to Host) using the byte swap function */
#  if defined(__ORDER_LITTLE_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || defined(_WIN32)
    // If Host is Little Endian (true for Windows/x86), we must swap.
#    define be32toh(x) __bswap_32(x)
#  else
    // If Host is Big Endian, no swap is needed.
#    define be32toh(x) (x)
#  endif

#endif // Standard endian.h check

#endif // ENDIAN_COMPAT_H