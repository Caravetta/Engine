#ifndef __COMPONENT_DATA_ARRAY_H__
#define __COMPONENT_DATA_ARRAY_H__

#include <vector>
#include "core_common.h"
#include "entity_group.h"
#include "component_data.h"

namespace Engine {

class Entity_Group;

class Component_Data_Array {
private:
     std::vector<Data_List>   __data_list;
     size_t                   __comp_size;

public:
     Component_Data_Array( Entity_Group group );
     uint8_t* data_at( size_t index );
     template<class T> T& operator[]( size_t index );
};

}

//#include "component_data_array.inl"

#endif //__COMPONENT_DATA_ARRAY_H__
