#ifndef __HANDLE_H__
#define __HANDLE_H__

#include <vector>
#include "core_common.h"

namespace Engine {

#define handle_index( handle ) ( handle & 0x00000000FFFFFFFF )
#define handle_phase( handle ) ( handle >> 32 )

typedef uint64_t Handle;

struct Handle_Manager {
private:
     std::vector<uint32_t> _handle_phases;
     std::vector<uint64_t> _free_handles;
     uint64_t _next_free_handle;
     uint64_t _block_size;
public:
     Handle_Manager( void );
     Handle_Manager( const uint32_t block_size );
     void set_block_size( const uint32_t size );
     Handle get_handle( void );
     void free_handle( const Handle handle );
     bool valid_handle( const Handle handle );
     size_t num_handles( void );
};

} // end namespace Engine

#endif //__HANDLE_H__
