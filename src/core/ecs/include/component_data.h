#ifndef __COMPONENT_DATA_H__
#define __COMPONENT_DATA_H__

#include <vector>
#include "core_common.h"
#include "component.h"
#include "handle.h"

namespace Engine {

struct Data_List {
     uint8_t* data;
     uint64_t total_ents;
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

void get_data_lists( std::vector<Data_List>& data_lists, std::vector<Component_ID>& components );

void comp_data_system_debug_print( void );

} // end namespace Engine

#endif //__COMPONENT_DATA_H__

