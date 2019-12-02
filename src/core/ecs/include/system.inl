
#include <new>

namespace Engine {

template<class T>
void register_system( void )
{
     T* system = new (std::nothrow) T;
     if ( system == NULL ) {
          LOG_ERROR("Failed to allocate memory for system");
          return;
     }

     register_system(system);
}

} // end namespace Engine

