#include "component_data_array.h"

namespace Engine {

struct Chunk {
     uint16_t  n_ents;
     Chunk*    prev;
     Chunk*    next;
     uint8_t*  data;
};

Component_Data_Array::Component_Data_Array( Entity_Group group )
{
     LOG("%zd", group.__data_lists.size());
     __data_list = group.__data_lists;
}

} // end namespace Engine

