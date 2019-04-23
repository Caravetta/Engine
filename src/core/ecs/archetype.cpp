#include <vector>
#include <unordered_map>
#include "archetype.h"
#include "page_allocator.h"

namespace Engine {

#define MAP(x, y) std::unordered_map<x, y>

struct Chunk {
     struct Chunk*  next;
     uint16_t       n_elements;
     void*          data;
};

struct Archetype_Node {
     uint16_t                      ents_per_page;
     uint16_t                      current_idx;
     Chunk*                        head;
     Chunk*                        tail;
     MAP(Component_ID, size_t)     offset_map;
};

struct Archetype_System {
     MAP(std::string, uint64_t) archetype_map;
     std::vector<Archetype_Node> node_vec;
};

Archetype_System* archetype_system = NULL;

void _remove_chunk( void );
void _add_chunk( Chunk* chunk );

Rc_t init_archetype_system( void )
{
     Rc_t rc = SUCCESS;

     if ( archetype_system == NULL ) {
          archetype_system = new (std::nothrow) Archetype_System;
          if ( archetype_system == NULL ) {
               rc = MEMORY_ALLOC_FAILED;
          }
     } else {
          rc = ENGINE_ERROR;
     }

     return rc;
}

Rc_t add_archetype( Archetype archetype, const std::string name )
{
     Rc_t rc = SUCCESS;

     UNORDERED_MAP_ITER(std::string, uint64_t) node_iter = archetype_system->archetype_map.find(name);
     if ( node_iter == archetype_system->archetype_map.end() ) {
          std::vector<Archetype_Node>* nodes = &archetype_system->node_vec;
          nodes->push_back(Archetype_Node());

          Archetype_Node* arche_node = &nodes->at(nodes->size() - 1);
          arche_node->head = arche_node->tail = NULL;
          arche_node->ents_per_page = page_size() / archetype.archetype_size;
          arche_node->current_idx = 0;

          std::vector<Archetype_Comp_Info>* comp_info_vec = &archetype.component_info_vec;
          Archetype_Comp_Info* comp_info = NULL;
          size_t current_offset = sizeof(Entity) * arche_node->ents_per_page;

          for ( uint32_t ii = 0; ii < comp_info_vec->size(); ++ii ) {
               comp_info = &comp_info_vec->at(ii);

               switch( comp_info->usage ) {
               case ARCHETYPE_COMPONENT:
               case ARCHETYPE_SHARED: {
                    arche_node->offset_map.insert({comp_info->id, current_offset});
                    current_offset += get_component_size(comp_info->id) * arche_node->ents_per_page;
               } break;
               case ARCHETYPE_TAG: {
                    arche_node->offset_map.insert({comp_info->id, 0});
               } break;
               default:
                    LOG_ERROR( "%s: Unknown usage type %d", __FUNCTION__, comp_info->usage);
                    return ENGINE_ERROR;
               }
          }
     } else {
          LOG_ERROR("%s: Archetype %s already exists", __FUNCTION__, name);
          rc = ENGINE_ERROR;
     }

     return rc;
}

Rc_t add_entity( const Entity entity, const std::string archetype_name )
{
     return SUCCESS;
}

Archetype::Archetype( void )
{

}

} // end namespace Engine

