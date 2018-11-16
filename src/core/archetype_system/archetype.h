#ifndef __ARCHETYPE_H__
#define __ARCHETYPE_H__

#include "../core_common.h"

namespace core {

    class CORE_API Archetype {
    private:
        std::unordered_map<uint32_t, uint64_t> component_map;

    public:
        std::vector<uint32_t> used_component_ids;

        Archetype();
        void add_component( uint32_t component_id );
        bool has_component( uint32_t component_id );
        template<typename T> void add_component();
        template<typename T> bool has_component();
    };

template<typename T>
void Archetype::add_component()
{
    add_component(Component_Manager::id<T>());
}

template<typename T>
bool Archetype::has_component()
{
    return has_component(Component_Manager::id<T>());
}

} // end namespace core

#endif //__ARCHETYPE_H__
