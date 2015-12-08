// Copyright (c) 2012-2014 Konstantin Isakov <ikm@zbackup.org> and ZBackup contributors, see CONTRIBUTORS
// Part of ZBackup. Licensed under GNU GPLv2 or later + OpenSSL, see LICENSE

#ifndef ENDIAN_HH_INCLUDED
#define ENDIAN_HH_INCLUDED

#include <stdint.h>
#include <arpa/inet.h>

#ifdef __APPLE__
#include <machine/endian.h>
#include <libkern/OSByteOrder.h>

#define htobe16(x) OSSwapHostToBigInt16(x)
#define htole16(x) OSSwapHostToLittleInt16(x)
#define be16toh(x) OSSwapBigToHostInt16(x)
#define le16toh(x) OSSwapLittleToHostInt16(x)

#define htobe32(x) OSSwapHostToBigInt32(x)
#define htole32(x) OSSwapHostToLittleInt32(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#define le32toh(x) OSSwapLittleToHostInt32(x)

#define htobe64(x) OSSwapHostToBigInt64(x)
#define htole64(x) OSSwapHostToLittleInt64(x)
#define be64toh(x) OSSwapBigToHostInt64(x)
#define le64toh(x) OSSwapLittleToHostInt64(x)
//__APPLE__

#elif __FreeBSD__
#include <sys/endian.h>

#else
#include <endian.h>
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
# ifndef htole32
#  define htobe16(x) __bswap_16 (x)
#  define htole16(x) (x)
#  define be16toh(x) __bswap_16 (x)
#  define le16toh(x) (x)

#  define htobe32(x) __bswap_32 (x)
#  define htole32(x) (x)
#  define be32toh(x) __bswap_32 (x)
#  define le32toh(x) (x)

#  define htobe64(x) __bswap_64 (x)
#  define htole64(x) (x)
#  define be64toh(x) __bswap_64 (x)
#  define le64toh(x) (x)
# endif

/// Converts the given host-order value to big-endian value
inline uint32_t toBigEndian( uint32_t v ) { return htonl( v ); }
/// Converts the given host-order value to little-endian value
inline uint32_t toLittleEndian( uint32_t v ) { return v; }
inline uint64_t toLittleEndian( uint64_t v ) { return v; }
/// Converts the given little-endian value to host-order value
inline uint32_t fromLittleEndian( uint32_t v ) { return v; }
inline uint64_t fromLittleEndian( uint64_t v ) { return v; }

#elif __BYTE_ORDER == __BIG_ENDIAN
# ifndef htole32
#  define htobe16(x) (x)
#  define htole16(x) __bswap_16 (x)
#  define be16toh(x) (x)
#  define le16toh(x) __bswap_16 (x)

#  define htobe32(x) (x)
#  define htole32(x) __bswap_32 (x)
#  define be32toh(x) (x)
#  define le32toh(x) __bswap_32 (x)

#  define htobe64(x) (x)
#  define htole64(x) __bswap_64 (x)
#  define be64toh(x) (x)
#  define le64toh(x) __bswap_64 (x)
# endif

// Note: the functions used are non-standard. Add more ifdefs if needed

/// Converts the given host-order value to big-endian value
inline uint32_t toBigEndian( uint32_t v ) { return v; }
/// Converts the given host-order value to little-endian value
inline uint32_t toLittleEndian( uint32_t v ) { return htole32( v ); }
inline uint64_t toLittleEndian( uint64_t v ) { return htole64( v ); }
/// Converts the given little-endian value to host-order value
inline uint32_t fromLittleEndian( uint32_t v ) { return le32toh( v ); }
inline uint64_t fromLittleEndian( uint64_t v ) { return le64toh( v ); }

#else

#error Please add support for architectures different from little-endian and\
 big-endian.

#endif

#endif
