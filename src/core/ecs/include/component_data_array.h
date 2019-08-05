#ifndef __COMPONENT_DATA_ARRAY_H__
#define __COMPONENT_DATA_ARRAY_H__

#include <vector>
#include "core_common.h"

namespace Engine {

enum Data_Usage_Type {
     NON_SHARED_DATA,
     SHARED_DATA,
};

struct Data_Node {
     Data_Usage_Type     usage;
     uint8_t*            data;
     uint16_t            n_elements;
};

template <class T>
class Component_Data_Array {
friend class Entity_Group;
private:
     size_t                   __total_elements;
     size_t                   __last_idx;
     size_t                   __last_node_idx;
     std::vector<Data_Node>   __data_nodes;
public:
     Component_Data_Array( void )
     {
          __total_elements = 0;
          __last_idx = 0;
          __last_node_idx = 0;
     }

     T& operator[]( size_t index )
     {
          return 0;
     }
};

} // end namespace Engine

#endif //__COMPONENT_DATA_ARRAY_H__
