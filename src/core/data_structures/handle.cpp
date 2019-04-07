#include "handle.h"

//#define HANDLE_DEBUG 1
#define DEFAULT_BLOCK_SIZE 10

#ifdef HANDLE_DEBUG
    #define HANDLE_LOG(...) LOG( __VA_ARGS__ );
#else
    #define HANDLE_LOG(...)
#endif

namespace Engine {

Handle_Manager::Handle_Manager( void )
{
    _handles.resize(DEFAULT_BLOCK_SIZE);
    _block_size = DEFAULT_BLOCK_SIZE;
    _next_free_handle = 1;

    HANDLE_LOG("Init Handle Manager block size %" PRIu64 " next free handle %" PRIu64 "",
               _block_size, _next_free_handle);

    for ( uint64_t ii = 0; ii < DEFAULT_BLOCK_SIZE; ++ii ) {
        _handles[ii].index = ii;
        _handles[ii].phase = 0;
    }
}

Handle_Manager::Handle_Manager( const uint32_t block_size )
{
    _handles.resize(block_size);
    _block_size = block_size;
    _next_free_handle = 1;

    HANDLE_LOG("Init Handle Manager block size %" PRIu64 " next free handle %" PRIu64 "",
               _block_size, _next_free_handle);

    for ( uint64_t ii = 0; ii < _block_size; ++ii ) {
        _handles[ii].index = ii;
        _handles[ii].phase = 0;
    }
}

void Handle_Manager::set_block_size( const uint32_t size )
{
    _block_size = size;
    HANDLE_LOG( "Set block size to %" PRIu64 "", _block_size );
}

Handle Handle_Manager::get_handle( void )
{
    uint64_t handle_index;

    // check for any free handles
    if ( _free_handles.empty() == true ) {
        uint64_t current_size = _handles.size();

        // check to see if more handles need to be added
        if ( current_size == _next_free_handle ) {
            _handles.resize(current_size + _block_size);

            for ( uint64_t ii = current_size; ii < _handles.size(); ++ii ) {
                _handles[ii].index = ii;
                _handles[ii].phase = 0;
            }
        }

        handle_index = _next_free_handle;
        _next_free_handle += 1;
    } else {
        handle_index = _free_handles.back();
        _free_handles.pop_back();
    }

    return _handles[handle_index];
}

void Handle_Manager::free_handle( const Handle handle )
{
    uint32_t index = handle.index;

    if ( index < _next_free_handle ) {
        if ( _handles[index].phase == handle.phase ) {
            _handles[index].phase += 1;
            _free_handles.push_back(index);
        }
    }
}

bool Handle_Manager::valid_handle( const Handle handle )
{
    bool is_valid = false;
    uint32_t index = handle.index;

    if ( index < _next_free_handle ) {
        is_valid = _handles[index].phase == handle.phase ? true : false;
    }

    return is_valid;
}

} // end namespace Engine.

