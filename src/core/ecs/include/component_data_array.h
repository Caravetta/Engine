#ifndef __COMPONENT_DATA_ARRAY_H__
#define __COMPONENT_DATA_ARRAY_H__

#include <vector>
#include "core_common.h"
#include "entity_group.h"
#include "component_data.h"

namespace Engine {

class Entity_Group;

template<class T>
class Component_Data_Array {
private:
     std::vector<Data_Chunk>*      __chunk_nodes;
     size_t                        __cur_idx;
     size_t                        __cur_chunk_idx;
     size_t                        __next_idx;
     Data_Chunk*                   __next_chunk;
     T*                            __cur_data;
     size_t                        __size;

public:
     Component_Data_Array( Entity_Group& group );
     size_t size( void );
     T& operator[]( size_t index );
};

} // end namespace Engine

#include "component_data_array.inl"

#endif //__COMPONENT_DATA_ARRAY_H__
