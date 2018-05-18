#include "heap.h"

#define HEADER_SIZE_SMALL       ( (int) ( sizeof( byte ) + sizeof( byte ) ) )

#define ALIGN_SIZE( bytes )     ( ( (bytes) + HEAP_ALIGN - 1 ) & ~(HEAP_ALIGN - 1) )
#define ALIGN_SMALL( bytes )    ( ALIGN_SIZE( (bytes) + HEADER_SIZE_SMALL ) - HEADER_SIZE_SMALL )

namespace uh {

class Heap {
    public:
    Heap( void );
    void init( void );
    void* allocate( const uint32_t bytes );
    void free( void* memory_ptr );

    private:

    struct page_t {
        page_t* next;
        page_t* prev;
        uint32_t data_size;
        void* data;
        void* first_free;
    };

    enum {
        HEAP_ALIGN = 8
    };

    enum {
        MAX_SMALL_ALLOC = 255
    };

    enum {
        INVALID_ALLOC = 0xDD,
        SMALL_ALLOC = 0xAA,
        MEDIUM_ALLOC = 0xBB,
        LARGE_ALLOC = 0xCC,
    };

    uint32_t total_os_allocs;
    uint32_t current_pages_alloc;
    uint32_t total_requested_pages;

    uint32_t page_size;

    page_t* allocate_page( uint32_t bytes );
    void free_page( page_t* page );

    //small allocations
    void* free_first_small[(MAX_SMALL_ALLOC + 1)/HEAP_ALIGN+1];
    page_t* current_small_page;
    page_t* first_used_small_page;
    uint32_t current_small_page_offset;

    void* allocate_small( uint32_t bytes );
    void free_small( void* mem_ptr );


};

Heap::Heap( void )
{
    init();
}

void Heap::init( void )
{
    total_os_allocs = 0;
    total_requested_pages = 0;
    current_pages_alloc = 0;
    page_size = 65536 - sizeof( page_t );
    memset( free_first_small, 0, sizeof(free_first_small) );
    first_used_small_page = NULL;
    current_small_page = allocate_page( page_size );
    current_small_page_offset = ALIGN_SMALL(0);
}

void* Heap::allocate( const uint32_t bytes )
{
    if ( !bytes ) {
        return NULL;
    }

#if USE_BASE_MALLOC
    return malloc( bytes );
#else
    if ( !(bytes & ~MAX_SMALL_ALLOC) ) {
        return allocate_small( bytes );
    } else {
        return NULL;
    }
#endif
}

void Heap::free( void* memory_ptr )
{
    if ( !memory_ptr ) {
        return;
    }
#if USE_BASE_MALLOC
    free( memory_ptr );
#else
    switch( ((byte *)(memory_ptr))[-1] ) {
        case SMALL_ALLOC: {
             return free_small( memory_ptr );
        } break;
        case MEDIUM_ALLOC: {
            //TODO: support Medium allocs
        } break;
        case LARGE_ALLOC: {
            //TODO: support large allocs
        } break;
        default: {
             UH_ERROR("Invalid memory block");
        } break;
    }
#endif
}

void* Heap::allocate_small( uint32_t bytes )
{
    return NULL;
}

void Heap::free_small( void* mem_ptr )
{
    //return;
}

Heap::page_t* Heap::allocate_page( uint32_t bytes )
{
    return (page_t*)NULL;
}

/**

*/

static Heap* memory_heap = NULL;

void memory_init( void )
{
    memory_heap = new Heap;
}

void memory_cleanup( void )
{
    Heap* tmp_heap = memory_heap;
    memory_heap = NULL;
    delete tmp_heap;
}

void* memory_alloc( const uint32_t size )
{
    if ( !size ) {
        return NULL;
    }

    if ( !memory_heap ) {
        return malloc( size );
    }

    return memory_heap->allocate( size );
}

void memory_free( void* memory_ptr )
{
    if ( !memory_ptr ) {
        return;
    }

    if ( !memory_heap ) {
        free( memory_ptr );
        return;
    }
    memory_heap->free( memory_ptr );
}

} // end namespace uh
