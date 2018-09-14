#if !defined(ENGINE_H)

#include "../core/core.h"

    class Engine {
    private:
        static Engine* instance;
    public:
        core::Window* window;
        core::Timer frame_time;
        core::Component_Manager* component_manager;
        core::Entity_Manager* enitiy_manager;
        core::System_Manager* system_manager;
        core::Asset_Manager* asset_manager;
        core::Debug_Camera* debug_camera;
        core::Entity_Archetype_Manager* archetype_manager;

        static Engine* get_instance();
        void init();
        void update();
        void shutdown();
    };

#define ENGINE_H
#endif
