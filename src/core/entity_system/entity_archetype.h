#if !defined(ENTITY_ARCHETYPE_H)

#include "../core_common.h"

namespace core {

    class CORE_API Entity_Archetype {
    private:
        std::unordered_map<uint64_t, uint64_t> component_map;

    public:
        std::vector<uint64_t> used_component_ids;

        Entity_Archetype();
        void add_component( uint64_t component_id );
        bool has_component( uint64_t component_id );
        template<typename T> void add_component();
        template<typename T> bool has_component();
        void print();
    };

template<typename T>
void Entity_Archetype::add_component()
{
    add_component(Component_Manager::get_instance()->id<T>());
}

template<typename T>
bool Entity_Archetype::has_component()
{
    return has_component(Component_Manager::get_instance()->id<T>());
}

} // end namespace core

#define ENTITY_ARCHETYPE_H
#endif
