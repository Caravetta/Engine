#include "entity_group.h"
#include "archetype_system.h"

namespace Engine {

Entity_Group::Entity_Group( std::vector<Component_ID> ids )
{
     get_archetype_nodes(ids, (std::vector<Archetype_Node*>*)&__data_vec);

     Archetype_Node* cur_node;

     for ( size_t ii = 0; ii < __data_vec.size(); ii++ ) {
          cur_node = (Archetype_Node*)__data_vec[ii];
          LOG("ii: %d name: %s", (int)ii, cur_node->archetype_name.c_str());
     }
}

size_t Entity_Group::generate_data_nodes( Component_ID id, std::vector<Data_Node>& node_vec )
{
     return 0;
}

} // end namespace Engine

