#ifndef __ENTITY_GROUP_H__
#define __ENTITY_GROUP_H__

#include <vector>
#include "component.h"
#include "component_data.h"

namespace Engine {

class Entity_Group {
private:
     std::vector<Data_Chunk>  __chunk_nodes;
     size_t                   __size;
     template<class T> friend class Component_Data_Array;

public:
     Entity_Group( std::vector<Component_ID> components );
     Entity_Group( std::vector<Component_ID> include, std::vector<Component_ID> exclude );
     void print_group_info( void );
};

} // end namespace Engine

#endif //__ENTITY_GROUP_H__
