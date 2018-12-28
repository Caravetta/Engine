#include "component_manager.h"
#include "archetype_manager.h"
#include "entity_manager.h"

namespace Engine {
namespace Component_Manager {

std::vector<component_info> component_info_vec;

component_create_function get_component_create( uint32_t component_id )
{
    CHECK_INFO( component_id != NON_VALID_ID, "This component has not been registered" );
    return component_info_vec[component_id].create_function;
}

component_copy_function get_component_copy( uint32_t component_id )
{
    CHECK_INFO( component_id != NON_VALID_ID, "This component has not been registered" );
    return component_info_vec[component_id].copy_function;
}

} // end namespace Component_Manager

uint32_t get_max_components()
{
    return (uint32_t)Component_Manager::component_info_vec.size();
}

uint64_t get_component_size( uint32_t component_id )
{
    CHECK_INFO( component_id != NON_VALID_ID, "This component has not been registered" );
    return Component_Manager::component_info_vec[component_id].size;
}

void register_component_info( component_info comp_info )
{
    Component_Manager::component_info_vec.push_back(comp_info);
}

uint8_t* get_component_data( Entity entity, uint32_t component_id )
{
    return Archetype_Manager::get_component_data_generic(Entity_Manager::get_internal_id(entity), component_id);
}

} // end namespace Engine
