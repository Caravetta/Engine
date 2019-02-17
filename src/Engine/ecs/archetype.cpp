#include "Engine.h"
#include "core_common.h"

namespace Engine {

Archetype::Archetype( void )
{

}

void Archetype::add_component( const u32 component_id )
{
    UNORDERED_MAP_ITERATOR(u32, u64) iter = component_map.find(component_id);
    if ( iter == component_map.end() ) {
        used_component_ids.push_back(component_id);
        component_map.insert({ component_id, used_component_ids.size() - 1 });
    }

}

bool Archetype::has_component( const u32 component_id )
{
    UNORDERED_MAP_ITERATOR(u32, u64) iter = component_map.find(component_id);
    if ( iter == component_map.end() ) {
        return false;
    }

    return true;
}

} // end namespace Engine
