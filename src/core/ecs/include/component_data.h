#ifndef __COMPONENT_DATA_H__
#define __COMPONENT_DATA_H__

#include <vector>
#include <unordered_map>
#include "core_common.h"
#include "component.h"
#include "handle.h"

namespace Engine {

typedef std::unordered_map<Component_ID, size_t> Comp_Offset_Map;

struct Data_List {
     uint8_t* data;
     uint64_t total_ents;
};

struct Data_Chunk {
     Comp_Offset_Map&    offset_map;
     size_t              start;
     size_t              end;
     uint8_t*            data;
};

Rc_t init_component_data_system( void );
void resize_map_info( size_t size );
size_t map_info_size( void );

uint8_t* get_component_data( Handle handle, Component_ID id );

void add_handle( Handle handle );
void add_handle( Handle handle, std::vector<Component_ID>& ids );
void remove_handle( Handle handle );

Rc_t handle_add_component( Handle handle, Component_ID id );
Rc_t handle_add_components( Handle handle, std::vector<Component_ID>& ids );
Rc_t handle_remove_component( Handle handle, Component_ID id );
Rc_t handle_remove_components( Handle handle, std::vector<Component_ID>& ids );

size_t get_data_chunks( std::vector<Data_Chunk>& data_chunks, std::vector<Component_ID>& components );

void comp_data_system_debug_print( void );

} // end namespace Engine

#endif //__COMPONENT_DATA_H__

