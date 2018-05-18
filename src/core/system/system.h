#if !defined(SYSTEM_H)

#include "../core_common.h"

namespace core {

    class System {
    public:
        enum component_usage {
            COMPONENT_READ_ONLY         = 1 << 0,
            COMPONENT_WRITE_ONLY        = 1 << 1,
            COMPONENT_READ_AND_WRITE    = 1 << 2,
        };

        struct component_info_t {
            uint64_t            component_id;
            component_usage     usage;
        };

        struct system_config_t {
            std::vector<component_info_t> components;
        };

    protected:
        system_config_t config;
        std::vector<Entity>* entities;

        void add_component( uint64_t component_id, component_usage usage );
        void add_component( uint64_t component_id );

    public:
        System(){};
        System( const System &s ){ LOG("System copy")}
        system_config_t get_system_config();
        void set_entity_vector( std::vector<Entity>* entities_vector );

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void shutdown() = 0;
    };

    void System::add_component( uint64_t component_id, component_usage usage )
    {
        uint64_t index = config.components.size();
        config.components.resize(config.components.size() + 1);
        config.components[index].component_id = component_id;
        config.components[index].usage = usage;
    }

    void System::add_component( uint64_t component_id )
    {
        uint64_t index = config.components.size();
        config.components.resize(config.components.size() + 1);
        config.components[index].component_id = component_id;
        config.components[index].usage = COMPONENT_READ_AND_WRITE;
    }

    System::system_config_t System::get_system_config()
    {
        return config;
    }
    void System::set_entity_vector( std::vector<Entity>* entities_vector )
    {
        this->entities = entities_vector;
    }

} // end namespace core

#define SYSTEM_H
#endif
