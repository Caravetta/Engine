#ifndef __PAGE_ALLOCATOR_H__
#define __PAGE_ALLOCATOR_H__

#include "core_common.h"

namespace Engine {

Rc_t init_page_allocator( const uint16_t page_size, const uint16_t pool_size );
void destroy_page_allocator( void );
void* allocate_page( void );
void free_page( void* page );
uint16_t page_size( void );

} // end namespace Engine

#endif //__PAGE_ALLOCATOR_H__
