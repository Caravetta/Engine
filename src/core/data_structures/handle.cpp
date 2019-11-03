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
     _handle_phases.resize(DEFAULT_BLOCK_SIZE);
     _block_size = DEFAULT_BLOCK_SIZE;
     _next_free_handle = 1;

     HANDLE_LOG("Init Handle Manager block size %" PRIu64 " next free handle %" PRIu64 "",
                _block_size, _next_free_handle);

     for ( uint64_t ii = 0; ii < DEFAULT_BLOCK_SIZE; ++ii ) {
          _handle_phases[ii] = 0;
     }
}

Handle_Manager::Handle_Manager( const uint32_t block_size )
{
     _handle_phases.resize(block_size);
     _block_size = block_size;
     _next_free_handle = 1;

     HANDLE_LOG("Init Handle Manager block size %" PRIu64 " next free handle %" PRIu64 "",
                _block_size, _next_free_handle);

     for ( uint64_t ii = 0; ii < _block_size; ++ii ) {
          _handle_phases[ii] = 0;
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
          uint64_t current_size = _handle_phases.size();

          // check to see if more handles need to be added
          if ( current_size == _next_free_handle ) {
               _handle_phases.resize(current_size + _block_size);

               for ( uint64_t ii = current_size; ii < _handle_phases.size(); ++ii ) {
                    _handle_phases[ii] = 0;
               }
          }

          handle_index = _next_free_handle;
          _next_free_handle += 1;
     } else {
          handle_index = _free_handles.back();
          _free_handles.pop_back();
     }

     return (0 | ((uint64_t)_handle_phases[handle_index] << 32) | handle_index);
}

void Handle_Manager::free_handle( const Handle handle )
{
     uint32_t index = handle_index(handle);

     if ( index < _next_free_handle ) {
          if ( _handle_phases[index] == handle_phase(handle) ) {
               _handle_phases[index] += 1;
               _free_handles.push_back(index);

               //TODO:(JOSH) check to see if we can reduce the handle vec size
          }
     }
}

bool Handle_Manager::valid_handle( const Handle handle )
{
     bool is_valid = false;
     uint32_t index = handle_index(handle);

     if ( index < _next_free_handle ) {
          is_valid = _handle_phases[index] == handle_phase(handle) ? true : false;
     }

     return is_valid;
}

size_t Handle_Manager::num_handles( void )
{
     return _handle_phases.size();
}

} // end namespace Engine.

