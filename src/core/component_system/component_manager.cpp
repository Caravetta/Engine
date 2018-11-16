#include "component_manager.h"

namespace core {
namespace Component_Manager {

std::vector<component_info> component_info_vec;

uint32_t get_max_components()
{
    return (uint32_t)component_info_vec.size();
}

uint64_t get_component_size( uint32_t component_id )
{
    CHECK_INFO( component_id != NON_VALID_ID, "This component has not been registered" );
    return component_info_vec[component_id].size;
}

component_create_function get_component_create( uint32_t component_id )
{
    CHECK_INFO( component_id != NON_VALID_ID, "This component has not been registered" );
    return component_info_vec[component_id].create_function;
}

void register_component_info( component_info comp_info )
{
    component_info_vec.push_back(comp_info);
}

} // end namespace Component_Manager
} // end namespace core
