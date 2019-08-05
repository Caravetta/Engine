#include <unordered_map>
#include <string>
#include <algorithm>
#include "archetype_system.h"
#include "entity.h"

namespace Engine {

/*
 * Chunk Data layout
 *
 * |------------|------------|--------------|------------------|
 * | Chunk Info | Entity IDs | Shared Comps | Non Shared Comps |
 * |------------|------------|--------------|------------------|
 */
#if 0
struct Chunk {
     struct Chunk*  next;
     uint16_t       n_elements;
     void*          data; // points to the start of entity ids
};

struct Archetype_Node {
     std::vector<Component_ID>     comp_id_vec;
     std::vector<Archetype_Usage>  comp_usage_vec;
     Chunk*                        head;
     Chunk*                        tail;
};
#endif

struct Archetype_System {
     std::unordered_map<std::string, uint64_t>    archetype_node_map;
     std::vector<Archetype_Node>                  archetype_node_vec;
};

Archetype_System* archetype_system = NULL;

#define get_entity_id( p_chunk, idx ) p_chunk->data + (sizeof(Entity) * idx)

Rc_t init_archetype_system( void )
{
     Rc_t rc = SUCCESS;

     if ( archetype_system == NULL ) {
          archetype_system = new (std::nothrow) Archetype_System;
          if ( archetype_system == NULL ) {
               rc = MEMORY_ALLOC_FAILED;
          }
     }

     return rc;
}

bool __arch_sort_func( Archetype_Comp_Info& left, Archetype_Comp_Info& right )
{
     return (left.id < right.id);
}

Rc_t add_archetype( Archetype& archetype, std::string name )
{
     Rc_t rc = SUCCESS;
     std::unordered_map<std::string, uint64_t>* p_node_map = &archetype_system->archetype_node_map;

     // check to see if archetype name already in use
     if ( p_node_map->find(name) == p_node_map->end() ) {
          std::vector<Archetype_Node>* p_archetype_nodes = &archetype_system->archetype_node_vec;
          p_archetype_nodes->push_back(Archetype_Node());
          Archetype_Node* p_archetype_node = &p_archetype_nodes->at(p_archetype_nodes->size() - 1);

          std::vector<Archetype_Comp_Info> comp_info_vec = archetype.get_component_info_vec();

          p_archetype_node->comp_id_vec.resize(comp_info_vec.size());
          p_archetype_node->comp_usage_vec.resize(comp_info_vec.size());

          p_archetype_node->archetype_name = name;

          std::sort(comp_info_vec.begin(), comp_info_vec.end(), __arch_sort_func);

          for ( size_t ii = 0; ii < comp_info_vec.size(); ii++ ) {
               p_archetype_node->comp_id_vec[ii] = comp_info_vec[ii].id;
               p_archetype_node->comp_usage_vec[ii] = comp_info_vec[ii].usage;
          }

          //TODO(JOSH): need to calc num of entities per chunk
     } else {
          rc = ARCHETYPE_ALREADY_EXISTS;
     }

     return rc;
}

Rc_t remove_archetype( std::string name )
{
     return SUCCESS;
}

Rc_t init_data_node( std::string archetype_name,  Archetype_Node_Info& data_info )
{
     return SUCCESS;
}

uint8_t* get_component_data( Component_ID id, Archetype_Node_Info& data_info )
{
     return NULL;
}

void get_archetype_nodes( std::vector<Component_ID> ids, std::vector<Archetype_Node*>* nodes )
{
     std::vector<Archetype_Node>* p_archetype_nodes = &archetype_system->archetype_node_vec;
     Archetype_Node* cur_node;

     for( size_t ii = 0; ii < p_archetype_nodes->size(); ii++ ) {
          cur_node = &p_archetype_nodes->at(ii);
          if ( std::includes(cur_node->comp_id_vec.begin(), cur_node->comp_id_vec.end(), ids.begin(), ids.end()) ) {
               nodes->push_back(cur_node);
          }
     }
}

} // end namespace Engine

