#if !defined(SYSTEM_MANAGER_H)

#include <vector>
#include <unordered_map>
#include "../core_common.h"
#include "system.h"
#include "../entity_system/entity.h"

namespace core {

    class CORE_API System_Manager {
    private:
        static System_Manager* instance;

        struct system_info_t {
            std::vector<Entity> entities;
            std::unordered_map<uint64_t, uint64_t> entity_map;
        };

        std::vector<system_info_t> systems_info;

    public:
        std::vector<System*> systems;


        static System_Manager* get_instance();
        template<typename T> void register_system();
        void init_systems();
        void update_systems();
        void shutdown_systems();
    };

template<typename T>
void System_Manager::register_system()
{
    systems.push_back( new T );
    systems_info.resize(systems_info.size() + 1);
}

} // end namespace core

#define SYSTEM_MANAGER_H
#endif
