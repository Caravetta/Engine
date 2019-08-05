#ifndef __ARCHETYPE_SYSTEM_H__
#define __ARCHETYPE_SYSTEM_H__

#include <string>
#include <vector>
#include "core_common.h"
#include "archetype.h"
#include "component.h"

namespace Engine {

struct Archetype_Node_Info {
     uint64_t archetype_id    : 32;
     uint64_t chunk_idx       : 32;
};

/*
 * Chunk Data layout
 *
 * |------------|------------|--------------|------------------|
 * | Chunk Info | Entity IDs | Shared Comps | Non Shared Comps |
 * |------------|------------|--------------|------------------|
 */

struct Chunk {
     struct Chunk*  next;
     uint16_t       n_elements;
     void*          data; // points to the start of entity ids
};

struct Archetype_Node {
     std::string                   archetype_name;
     std::vector<Component_ID>     comp_id_vec;
     std::vector<Archetype_Usage>  comp_usage_vec;
     Chunk*                        head;
     Chunk*                        tail;
};

Rc_t init_archetype_system( void );
Rc_t add_archetype( Archetype& archetype, std::string name );
Rc_t remove_archetype( std::string name );
Rc_t init_data_node( std::string archetype_name,  Archetype_Node_Info& data_info );
uint8_t* get_component_data( Component_ID id, Archetype_Node_Info& data_info );
void get_archetype_nodes( std::vector<Component_ID> ids, std::vector<Archetype_Node*>* nodes );

} // end namespace Engine

#endif
