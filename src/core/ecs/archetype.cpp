#include "archetype.h"

namespace Engine {

Archetype::Archetype( void )
{
     __total_comp_size = 0;
     __total_shared_comp_size = 0;
}

size_t Archetype::get_total_shared_comp_size( void )
{
     return __total_shared_comp_size;
}

size_t Archetype::get_total_comp_size( void )
{
     return __total_comp_size;
}

size_t Archetype::get_arhcetype_size( void )
{
     return (__total_shared_comp_size + __total_comp_size);
}

void Archetype::add_component( Component_ID id, Archetype_Usage usage )
{
     Archetype_Comp_Info comp_info = {id, usage};
     __component_info_vec.push_back(comp_info);
}

std::vector<Archetype_Comp_Info>& Archetype::get_component_info_vec( void )
{
     return __component_info_vec;
}

} // end namespace Engine

