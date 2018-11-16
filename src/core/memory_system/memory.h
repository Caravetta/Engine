#ifndef __MEMORY_H__
#define __MEMORY_H__

#ifdef MEMORY_DEBUG
    void* Mem_Alloc( const uint64_t size, const char *fileName, const uint64_t lineNumber );
    void Mem_Free( void *ptr, const char *fileName, const uint64_t lineNumber );

    Mem_Alloc( size ) Mem_Alloc( size, __FILE__, __LINE__ )
    Mem_Free( ptr ) Mem_Free( ptr, __FILE__, __LINE__ )
#else
    void* Mem_Alloc( const uint64_t size );
    void Mem_Free( void *ptr );
#endif

#ifdef REDIRECT_NEWDELETE

ALWAYS_INLINE void *operator new( size_t s ) {
    return Mem_Alloc( s );
}
ALWAYS_INLINE void operator delete( void *p ) {
    Mem_Free( p );
}
ALWAYS_INLINE void *operator new[]( size_t s ) {
    return Mem_Alloc( s );
}
ALWAYS_INLINE void operator delete[]( void *p ) {
    Mem_Free( p );
}

#endif

#endif //__MEMORY_H__
