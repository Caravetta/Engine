
#include "component_data.h"

namespace Engine {

template<class T> T* get_component( Entity entity )
{
     return (T*)get_component_data(entity, T::__id);
}

} // end namespace Engine

