#include <algorithm>
#include "entity_group.h"

namespace Engine {

struct Chunk {
     uint16_t  n_ents;
     Chunk*    prev;
     Chunk*    next;
     uint8_t*  data;
};

Entity_Group::Entity_Group( std::vector<Component_ID> components )
{
     std::sort(components.begin(), components.end());
     __size = get_data_chunks(__chunk_nodes, components);
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

