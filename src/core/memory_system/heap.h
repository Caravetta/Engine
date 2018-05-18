#if !defined(HEAP_H)

#include "../core_common.h"

namespace uh {

CORE_API void memory_init( void );
CORE_API void memory_cleanup( void );

CORE_API void* memory_alloc( const uint32_t size );
CORE_API void memory_free( void* memory_ptr );

} //end namespace uh

void* operator new( size_t size ) {
    return uh::memory_alloc( (uint32_t)size );
}

void operator delete( void *ptr ) {
    return uh::memory_free( ptr );
}

void* operator new[]( size_t size ) {
    return uh::memory_alloc( (uint32_t)size );
}

void operator delete[]( void *ptr ) {
    return uh::memory_free( ptr );
}

#define HEAP_H
#endif
