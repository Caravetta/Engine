#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "../core/core.h"

    class Engine {
    private:
        static Engine* instance;

    public:
        core::Window* window;
        core::Timer frame_time;
        core::Asset_Manager* asset_manager;
        core::Debug_Camera* debug_camera;
        core::Entity_Archetype_Manager* archetype_manager;

        static Engine* get_instance();
        void init();
        void update();
        void shutdown();
    };

#endif //__ENGINE_H__
