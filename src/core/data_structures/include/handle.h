#ifndef __HANDLE_H__
#define __HANDLE_H__

#include <vector>
#include "core_common.h"

namespace Engine {

struct Handle {
    union {
        struct {
            uint64_t index : 32;
            uint64_t phase : 32;
        };
        uint64_t id;
    };
};

struct ENGINE_API Handle_Manager {
private:
    std::vector<Handle> _handles;
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
};

} // end namespace Engine

#endif //__HANDLE_H__
