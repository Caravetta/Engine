#ifndef __ENTITY_GROUP_H__
#define __ENTITY_GROUP_H__

#include <vector>
#include <unordered_map>
#include "core_common.h"
#include "component.h"
#include "component_data_array.h"

namespace Engine {

class ENGINE_API Entity_Group {
private:
     size_t                   __length;
     std::vector<uint8_t*>    __data_vec;

public:
     Entity_Group( std::vector<Component_ID> ids );
     template<typename T> Component_Data_Array<T> get_component_data_array( void );

private:
     size_t generate_data_nodes( Component_ID id, std::vector<Data_Node>& node_vec );
};

template<typename T>
Component_Data_Array<T> Entity_Group::get_component_data_array( void )
{
     Component_Data_Array<T> data_array;
     data_array.__total_elements = generate_data_nodes(0, data_array.__data_nodes);

     return data_array;
}

} // end namespace Engine

#endif //__ENTITY_GROUP_H__
