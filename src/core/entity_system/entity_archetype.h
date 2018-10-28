#ifndef __ENTITY_ARCHETYPE_H__
#define __ENTITY_ARCHETYPE_H__

#include "../core_common.h"

namespace core {

    class CORE_API Entity_Archetype {
    private:
        std::unordered_map<uint32_t, uint64_t> component_map;

    public:
        std::vector<uint32_t> used_component_ids;

        Entity_Archetype();
        void add_component( uint32_t component_id );
        bool has_component( uint32_t component_id );
        template<typename T> void add_component();
        template<typename T> bool has_component();
    };

template<typename T>
void Entity_Archetype::add_component()
{
    add_component(Component_Manager::id<T>());
}

template<typename T>
bool Entity_Archetype::has_component()
{
    return has_component(Component_Manager::get_instance()->id<T>());
}

} // end namespace core

#endif //__ENTITY_ARCHETYPE_H__
