#include <algorithm>
#include "entity_group.h"

namespace Engine {

Entity_Group::Entity_Group( std::vector<Component_ID> components )
{
     std::sort(components.begin(), components.end());
     get_data_lists(__data_lists, components);
}

Entity_Group::Entity_Group( std::vector<Component_ID> include, std::vector<Component_ID> exclude )
{

}

#if 0
Component_Data_Array Entity_Group::component_data_array( Component_ID id )
{

}
#endif

} // end namespace Engine

