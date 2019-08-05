#ifndef __CRC32_H__
#define __CRC32_H__

#include "core_common.h"

namespace Engine {

inline uint32_t crc32( const char* string );

uint32_t crc32_update( uint32_t current_crc, const void* data, size_t byte_count );

} // end namespace Engine

#include "crc32.inl"

#endif //__CRC32_H__
