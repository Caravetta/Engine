#include <algorithm>
#include <unordered_map>
#include "component_data.h"
#include "page_allocator.h"
#include "crc32.h"

namespace Engine {

struct Chunk {
     uint16_t  n_ents;
     Chunk*    prev;
     Chunk*    next;
     uint8_t*  data;
};

typedef std::unordered_map<Component_ID, size_t> Comp_Offset_Map;

struct Comp_Data_Node {
     Comp_Data_Node*               next;
     Comp_Data_Node*               prev;
     uint32_t                      id;
     std::vector<Component_ID>     components;
     std::vector<size_t>           offsets;
     Comp_Offset_Map               offset_map;
     uint32_t                      n_chunks;
     uint64_t                      total_ents;
     Chunk*                        head;
     Chunk*                        tail;
     uint16_t                      ents_per_chunk;
};

struct Entity_Map {
     uint32_t node_idx;
     uint32_t chunk_idx;
     uint16_t data_idx;
};

typedef std::unordered_map<uint32_t, Comp_Data_Node*> Comp_Data_Map;

struct Component_Data_System {
     Comp_Data_Map            data_node_map;
     std::vector<Entity_Map>  entity_map;
};

Component_Data_System* component_data_system = NULL;

Comp_Data_Node* _comp_list_exists( uint32_t crc32_id )
{
     Comp_Data_Node* data_node = NULL;

     Comp_Data_Map::const_iterator iter = component_data_system->data_node_map.find(crc32_id);
     if ( iter != component_data_system->data_node_map.end() ) {
          data_node = iter->second;
     }

     return data_node;
}

Rc_t init_component_data_system( void )
{
     Rc_t rc = SUCCESS;

     if ( component_data_system == NULL ) {
          component_data_system = new (std::nothrow) Component_Data_System;
          if ( component_data_system != NULL ) {
          } else {
               rc = MEMORY_ALLOC_FAILED;
          }
     }

     return rc;
}

void resize_map_info( size_t size )
{
     component_data_system->entity_map.resize(size);
}

size_t map_info_size( void )
{
     return component_data_system->entity_map.size();
}

Chunk* _find_chunk( Comp_Data_Node& data_node, uint32_t chunk_idx )
{
     Chunk* chunk = NULL;
     Chunk* cur_chunk = data_node.head;
     uint32_t cur_idx = 1;
     while ( cur_chunk != NULL ) {
          if ( cur_idx == chunk_idx ) {
               chunk = cur_chunk;
               break;
          }
          cur_chunk = cur_chunk->next;
          cur_idx += 1;
     }

     return chunk;
}

uint8_t* get_component_data( Handle handle, Component_ID id )
{
     std::vector<Entity_Map>& entity_map = component_data_system->entity_map;
     uint32_t handle_idx = handle_index(handle);

     Comp_Data_Node* data_node = _comp_list_exists(entity_map[handle_idx].node_idx);
     if ( data_node == NULL ) {
          LOG_ERROR("Failed to find Data Node with ID:%" PRIu32 "", entity_map[handle_idx].node_idx);
          return NULL;
     }

     // check to see if comp id is in data node and get offset
     size_t comp_offset = 0;

     Comp_Offset_Map::const_iterator iter = data_node->offset_map.find(id);
     if ( iter != data_node->offset_map.end() ) {
          comp_offset = iter->second;
     } else {
          LOG_ERROR("Failed to find Comp ID:%" PRIu32 " offset in Data Node ID:%" PRIu32 "",
                    id,
                    entity_map[handle_idx].node_idx);
          return NULL;
     }

     Chunk* chunk = _find_chunk(*data_node, entity_map[handle_idx].chunk_idx);
     if ( chunk == NULL ) {
          LOG_ERROR("Failed to find Chunk IDX:%" PRIu32 " in Data Node ID:%" PRIu32 "",
                     entity_map[handle_idx].chunk_idx,
                     entity_map[handle_idx].node_idx);
          return NULL;
     }

     uint8_t* comp_data = ((uint8_t*)chunk->data + comp_offset) +
                              (component_size(id) * entity_map[handle_idx].data_idx);

     return comp_data;
}

Chunk* _get_chunk( Comp_Data_Node& data_node )
{
     if ( (data_node.tail == NULL) || (data_node.ents_per_chunk == data_node.tail->n_ents) ) {
          // we need to grap another page/chunk

          // create new chunk
          Chunk* new_chunk = (Chunk*)allocate_page();
          new_chunk->n_ents = 0;
          new_chunk->prev = NULL;
          new_chunk->next = NULL;
          new_chunk->data = (uint8_t*)&new_chunk[1];

          // add chunk to data node
          if ( data_node.tail != NULL ) {
               new_chunk->prev = data_node.tail;
               data_node.tail->next = new_chunk;
               data_node.tail = new_chunk;
          } else {
               data_node.head = new_chunk;
               data_node.tail = new_chunk;
          }

          data_node.n_chunks += 1;
     }

     //Chunk* chunk = data_node.tail;
     return data_node.tail;
}

void _add_handle_to_node( Handle handle, Comp_Data_Node& data_node )
{
     Chunk* chunk = _get_chunk(data_node);

     std::vector<Entity_Map>& entity_map = component_data_system->entity_map;
     uint32_t handle_idx = handle_index(handle);

     entity_map[handle_idx].node_idx = data_node.id;
     entity_map[handle_idx].chunk_idx = data_node.n_chunks;
     entity_map[handle_idx].data_idx = chunk->n_ents;

     // store the handle
     Handle* p_handle = (Handle*)((uint8_t*)chunk->data + (sizeof(Handle) * chunk->n_ents));
     *p_handle = handle;

     // loop through all comps and init their mem
     for ( size_t ii = 0; ii < data_node.components.size(); ii++ ) {
          uint8_t* comp_mem = ((uint8_t*)chunk->data + data_node.offsets[ii]) +
                                   (component_size(data_node.components[ii]) * chunk->n_ents);
          comp_mem_init_func cmp_mem_init = component_mem_init(data_node.components[ii]);
          cmp_mem_init(comp_mem);
     }

     data_node.total_ents += 1;
     chunk->n_ents += 1;
}

Comp_Data_Node* _create_comp_data_node( std::vector<Component_ID>& ids, uint32_t id )
{
     size_t ent_size = sizeof(Handle);
     for ( size_t ii = 0; ii < ids.size(); ii++ ) {
          ent_size += component_size(ids[ii]);
     }

     Comp_Data_Node* new_data_node = new Comp_Data_Node;
     new_data_node->components = ids;
     new_data_node->n_chunks = 0;
     new_data_node->next = NULL;
     new_data_node->prev = NULL;
     new_data_node->head = NULL;
     new_data_node->tail = NULL;
     new_data_node->total_ents = 0;
     new_data_node->id = id;
     new_data_node->ents_per_chunk = (uint16_t)((page_size() - sizeof(Chunk)) / ent_size);
     size_t offset = sizeof(Handle) * new_data_node->ents_per_chunk;
     for ( size_t ii = 0; ii < ids.size(); ii++ ) {
          new_data_node->offsets.push_back(offset);
          new_data_node->offset_map.insert({ids[ii], offset});
          offset += (component_size(ids[ii]) * new_data_node->ents_per_chunk);
     }

     component_data_system->data_node_map.insert({id, new_data_node});;

     return new_data_node;
}

void _add_comps_to_empty_ent( Handle handle, std::vector<Component_ID>& ids )
{
     uint32_t crc32_id = crc32(ids.data(), sizeof(Component_ID) * ids.size());
     Comp_Data_Node* data_node = _comp_list_exists(crc32_id);
     if ( data_node != NULL ) {
          _add_handle_to_node(handle, *data_node);
     } else {
          data_node = _create_comp_data_node(ids, crc32_id);
          _add_handle_to_node(handle, *data_node);
     }
}

void add_handle( Handle handle )
{
     std::vector<Entity_Map>& entity_map = component_data_system->entity_map;

     entity_map[handle_index(handle)].node_idx = 0;
}

void add_handle( Handle handle, std::vector<Component_ID>& ids )
{
     std::sort(ids.begin(), ids.end());
     _add_comps_to_empty_ent(handle, ids);
}

void remove_handle( Handle handle )
{
     std::vector<Entity_Map>& entity_map = component_data_system->entity_map;
     uint32_t handle_idx = handle_index(handle);

     Entity_Map& ent_map = entity_map[handle_idx];
     Comp_Data_Node* p_data_node = NULL;

     if ( ent_map.node_idx != 0 ) {
          p_data_node = _comp_list_exists( ent_map.node_idx );
          if ( p_data_node == NULL ) {
               return;
          }
     } else {
          // has no data can just return
          return;
     }

     Comp_Data_Node& data_node = *p_data_node;

     Chunk* chunk = _find_chunk(data_node, ent_map.chunk_idx);

     if ( chunk != data_node.tail && (ent_map.data_idx - 1) != chunk->n_ents ) {
          // handle was not at the end of the tail chunk

          Handle* mv_handle = (Handle*)((uint8_t*)data_node.tail->data +
                                   (sizeof(Handle) * (data_node.tail->n_ents - 1)));

          Handle* old_handle = (Handle*)((uint8_t*)chunk->data +
                                   (sizeof(Handle) * ent_map.data_idx));

          uint32_t mv_handle_idx = handle_index((*mv_handle));
          Entity_Map& mv_ent_map = entity_map[mv_handle_idx];

          mv_ent_map.chunk_idx = ent_map.chunk_idx;
          mv_ent_map.data_idx = ent_map.data_idx;

          *old_handle = *mv_handle;

          for ( size_t ii = 0; ii < data_node.components.size(); ii++ ) {
               size_t comp_size = component_size(data_node.components[ii]);
               comp_mem_cpy_func comp_mem_cpy = component_mem_cpy(data_node.components[ii]);

               uint8_t* mv_comp = ((uint8_t*)data_node.tail->data + data_node.offsets[ii]) +
                                        (comp_size * (data_node.tail->n_ents - 1));

               uint8_t* old_comp = ((uint8_t*)chunk->data + data_node.offsets[ii]) +
                                        (comp_size * ent_map.data_idx);

               comp_mem_cpy(mv_comp, old_comp);
          }

          data_node.tail->n_ents -= 1;
     } else {
          chunk->n_ents -= 1;
     }

     // need to check if the tail chunk is empty now

     if ( data_node.tail->n_ents == 0 ) {
          Chunk* tail = data_node.tail;
          data_node.tail = tail->prev;

          free_page((void*)chunk);

          // check to see if there are no more chunks
          if ( data_node.tail == NULL ) {
               component_data_system->data_node_map.erase(ent_map.node_idx);
               delete(&data_node);
          }
     }
}

Rc_t _add_comps_to_ent( Handle handle, std::vector<Component_ID>& ids )
{
     std::vector<Entity_Map>& entity_map = component_data_system->entity_map;
     uint32_t handle_idx = handle_index(handle);

     Comp_Data_Node* p_data_node = _comp_list_exists(entity_map[handle_idx].node_idx);
     if ( p_data_node == NULL ) {
          LOG("Failed to find Component Data Node with ID: % " PRIu32 "",
               entity_map[handle_idx].node_idx);
          return ENGINE_ERROR;
     }

     //TODO(JOSH) make sure component is not already on handle

     Comp_Data_Node& old_data_node = *p_data_node;
     std::vector<Component_ID> new_ids = old_data_node.components;
     new_ids.insert( new_ids.end(), ids.begin(), ids.end() );

     std::sort(new_ids.begin(), new_ids.end());

     uint32_t crc32_id = crc32(new_ids.data(), sizeof(Component_ID) * new_ids.size());
     p_data_node = _comp_list_exists(crc32_id);
     if ( p_data_node == NULL ) {
          // need to create a new comp data node
          p_data_node = _create_comp_data_node(new_ids, crc32_id);
     }

     // Fist init the memory for the new data
     Comp_Data_Node& new_data_node = *p_data_node;
     Chunk* chunk = _get_chunk(new_data_node);

     // store the handle
     Handle* p_handle = (Handle*)((uint8_t*)chunk->data + (sizeof(Handle) * chunk->n_ents));
     *p_handle = handle;

     // loop through all comps and init their mem
     for ( size_t ii = 0; ii < new_data_node.components.size(); ii++ ) {
          uint8_t* comp_mem = ((uint8_t*)chunk->data + new_data_node.offsets[ii]) +
                                   (component_size(new_data_node.components[ii]) * chunk->n_ents);

          comp_mem_init_func cmp_mem_init = component_mem_init(new_data_node.components[ii]);
          cmp_mem_init(comp_mem);
     }

     // Second copy the comps over from old to new
     Chunk* old_chunk = _find_chunk(old_data_node, entity_map[handle_idx].chunk_idx);
     size_t old_comp_idx = 0;

     for ( size_t ii = 0; ii < new_data_node.components.size(); ii++ ) {
          if ( new_data_node.components[ii] == old_data_node.components[old_comp_idx] ) {
               // found a match, move data over and inc the old comp idx
               size_t comp_size = component_size(new_data_node.components[ii]);
               comp_mem_cpy_func comp_mem_cpy = component_mem_cpy(new_data_node.components[ii]);

               uint8_t* new_comp_mem = ((uint8_t*)chunk->data + new_data_node.offsets[ii]) +
                                             (comp_size * chunk->n_ents);

               uint8_t* old_comp_mem = ((uint8_t*)old_chunk->data + old_data_node.offsets[old_comp_idx]) +
                                             (comp_size * entity_map[handle_idx].data_idx);
               comp_mem_cpy(old_comp_mem, new_comp_mem);

               old_comp_idx += 1;
               if ( old_comp_idx >= old_data_node.components.size() ) {
                    // no more old comps to copy
                    break;
               }
          }
     }

     // Last clean up old data node
     remove_handle(handle);

     entity_map[handle_idx].node_idx = new_data_node.id;
     entity_map[handle_idx].chunk_idx = new_data_node.n_chunks;
     entity_map[handle_idx].data_idx = chunk->n_ents;

     chunk->n_ents += 1;

     return SUCCESS;
}

Rc_t handle_add_component( Handle handle, Component_ID id )
{
     Rc_t rc = SUCCESS;

     std::vector<Entity_Map>& entity_map = component_data_system->entity_map;
     uint32_t handle_idx = handle_index(handle);

     if ( entity_map[handle_idx].node_idx != 0 ) {
          std::vector<Component_ID> ids = {id};
          rc = _add_comps_to_ent(handle, ids);
     } else {
          std::vector<Component_ID> ids = {id};
          _add_comps_to_empty_ent(handle, ids);
     }

     return rc;
}

Rc_t handle_add_components( Handle handle, std::vector<Component_ID>& ids )
{
     Rc_t rc = SUCCESS;

     std::vector<Entity_Map>& entity_map = component_data_system->entity_map;
     uint32_t handle_idx = handle_index(handle);

     std::sort(ids.begin(), ids.end());

     if ( entity_map[handle_idx].node_idx != 0 ) {
          rc = _add_comps_to_ent(handle, ids);
     } else {
          _add_comps_to_empty_ent(handle, ids);
     }

     return rc;
}

Rc_t _remove_comps_from_ent( Handle handle, std::vector<Component_ID>& ids )
{
     std::vector<Entity_Map>& entity_map = component_data_system->entity_map;
     uint32_t handle_idx = handle_index(handle);

     Comp_Data_Node* p_data_node = _comp_list_exists(entity_map[handle_idx].node_idx);
     if ( p_data_node == NULL ) {
          LOG("Failed to find Component Data Node with ID: % " PRIu32 "",
               entity_map[handle_idx].node_idx);
          return ENGINE_ERROR;
     }

     //TODO(JOSH) make sure component is not already on handle

     Comp_Data_Node& old_data_node = *p_data_node;
     std::vector<Component_ID> new_ids = old_data_node.components;
     for ( size_t ii = 0; ii < ids.size(); ii++ ) {
          for ( size_t jj = 0; jj < new_ids.size(); jj++ ) {
               if ( ids[ii] == new_ids[jj] ) {
                    new_ids.erase(new_ids.begin() + jj);
                    break;
               }
          }
     }
     //new_ids.insert( new_ids.end(), ids.begin(), ids.end() );

     std::sort(new_ids.begin(), new_ids.end());

     uint32_t crc32_id = crc32(new_ids.data(), sizeof(Component_ID) * new_ids.size());
     p_data_node = _comp_list_exists(crc32_id);
     if ( p_data_node == NULL ) {
          // need to create a new comp data node
          p_data_node = _create_comp_data_node(new_ids, crc32_id);
     }

     // Fist init the memory for the new data
     Comp_Data_Node& new_data_node = *p_data_node;
     Chunk* chunk = _get_chunk(new_data_node);

     // store the handle
     Handle* p_handle = (Handle*)((uint8_t*)chunk->data + (sizeof(Handle) * chunk->n_ents));
     *p_handle = handle;

     // loop through all comps and init their mem
     for ( size_t ii = 0; ii < new_data_node.components.size(); ii++ ) {
          uint8_t* comp_mem = ((uint8_t*)chunk->data + new_data_node.offsets[ii]) +
                                   (component_size(new_data_node.components[ii]) * chunk->n_ents);

          comp_mem_init_func cmp_mem_init = component_mem_init(new_data_node.components[ii]);
          cmp_mem_init(comp_mem);
     }

     // Second copy the comps over from old to new
     Chunk* old_chunk = _find_chunk(old_data_node, entity_map[handle_idx].chunk_idx);
     size_t old_comp_idx = 0;
     for ( size_t ii = 0; ii < new_data_node.components.size(); ii++ ) {
          if ( new_data_node.components[ii] == old_data_node.components[old_comp_idx] ) {
               // found a match, move data over and inc the old comp idx

               size_t comp_size = component_size(new_data_node.components[ii]);
               comp_mem_cpy_func comp_mem_cpy = component_mem_cpy(new_data_node.components[ii]);

               uint8_t* new_comp_mem = ((uint8_t*)chunk->data + new_data_node.offsets[ii]) +
                                             (comp_size * chunk->n_ents);

               uint8_t* old_comp_mem = ((uint8_t*)old_chunk->data + old_data_node.offsets[old_comp_idx]) +
                                             (comp_size * entity_map[handle_idx].data_idx);

               comp_mem_cpy(old_comp_mem, new_comp_mem);

               old_comp_idx += 1;
               if ( old_comp_idx >= old_data_node.components.size() ) {
                    // no more old comps to copy
                    break;
               }
          }
     }

     // Last clean up old data node
     remove_handle(handle);

     entity_map[handle_idx].node_idx = new_data_node.id;
     entity_map[handle_idx].chunk_idx = new_data_node.n_chunks;
     entity_map[handle_idx].data_idx = chunk->n_ents;

     chunk->n_ents += 1;

     return SUCCESS;

}

Rc_t handle_remove_component( Handle handle, Component_ID id )
{
     std::vector<Component_ID> ids = {id};
     return _remove_comps_from_ent(handle, ids);;
}

Rc_t handle_remove_components( Handle handle, std::vector<Component_ID>& ids )
{
     return _remove_comps_from_ent(handle, ids);
}

void get_data_lists( std::vector<Data_List>& data_lists, std::vector<Component_ID>& components )
{
     for ( const auto &entry : component_data_system->data_node_map ) {
          Comp_Data_Node& data_node = *entry.second;
          if ( std::includes(data_node.components.begin(), data_node.components.end(),
                              components.begin(), components.end()) ) {
               data_lists.push_back({(uint8_t*)data_node.head, data_node.total_ents});
          }
     }
}

void comp_data_system_debug_print( void )
{
     for ( const auto &entry : component_data_system->data_node_map ) {
          Comp_Data_Node& data_node = *entry.second;
          LOG("******* Data Node *******");
          LOG("ID: %" PRIu32 "", data_node.id);
          LOG("Entities Per Chunk: %" PRIu16 "", data_node.ents_per_chunk);
          LOG("Components [ %zd ]", data_node.components.size());
          for ( size_t jj = 0; jj < data_node.components.size(); jj++ ) {
               LOG("\tID: %" PRIu32 " Size %zd Offset: %zd",
                    data_node.components[jj],
                    component_size(data_node.components[jj]),
                    data_node.offsets[jj]);
          }
          LOG("Chunks: [ %" PRIu32 " ]", data_node.n_chunks);
          uint32_t chunk_idx = 0;
          Chunk* cur_chunk = data_node.head;
          while( cur_chunk != NULL ) {
               LOG("\tChunk: [ %" PRIu32 " ]", chunk_idx++);
               LOG("\t\tNumber of Entities: %" PRIu16 "", cur_chunk->n_ents);
               cur_chunk = cur_chunk->next;
          }
     }
}

} // end namespace Engine

