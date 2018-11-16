#include "engine.h"
#include "components/components.h"
#include "components/components.cpp"
#include "component_systems/component_systems.h"
#include "component_systems/component_systems.cpp"
#include "asset_types/assets.h"
#include "asset_types/assets.cpp"
#include "renderer.h"
#include "user_init.h"
#include "user_init.cpp"

Engine* Engine::instance = NULL;

Engine* Engine::get_instance()
{
    if ( instance == NULL ) {
        instance = new Engine;
    }
    return instance;
}

void Engine::init()
{

    //load opengl extentions (important this must be done before creating window)
#ifdef WINDOWS_PLATFORM
    load_opengl_extensions();
#endif

    //create the game window
    this->window = new core::Window(1000, 800, "Launcher");

    //setup job manager
    core::Job_Manager::init();

    //setup worker manager
    core::Worker_Manager::init();

    //setup entity manager
    core::Entity_Manager::init();

    core::Archetype_Manager::init();

    //setup event manager
    //uh::CEMS::get_instance();

    //register all components NOTE: this will need to be generated maybe
    core::Component_Manager::register_component<Position_Component>();
    core::Component_Manager::register_component<Mesh_Component>();
    core::Component_Manager::register_component<Texture_Component>();
    core::Component_Manager::register_component<Shader_Component>();
    core::Component_Manager::register_component<Static_Text_Component>();
    core::Component_Manager::register_component<Dynamic_Text_Component>();
    core::Component_Manager::register_component<Motion_Component>();
    core::Component_Manager::register_component<Transform>();

    //component_manager->register_component<Dynamic_Text_Component>();
    //component_manager->register_component<Cube_Orbit_Component>();

    //register all systems NOTE: this will need to be generated maybe
    core::System_Manager::register_system<Mesh_Render_System>();
    core::System_Manager::register_system<Text_Render_System>();
    core::System_Manager::register_system<Dynamic_Text_Render_System>();
    core::System_Manager::register_system<Motion_System>();
    //system_manager->register_system<Test_System>();
    //system_manager->register_system<Cube_Orbit_System>();

    /************* START TEST CODE ***************/
    user_init();

    debug_camera = new core::Debug_Camera(core::Vector3f(67, 8, 32), core::Vector2f(1000, 800));
    debug_camera->rotate(30.29, -0.2);

    /************* END TEST CODE *****************/

#ifdef WINDOWS_PLATFORM
    //TODO(JOSH): need to find better place to put this
    if ( !InitializeCriticalSectionAndSpinCount(&render_command_queue_lock, 0x00000400) ) {
        LOG_ERROR("Failed to init render lock");
    }
#endif

    core::System_Manager::init_systems();

    return;
}

void Engine::update()
{
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    this->frame_time.update();

    std::chrono::steady_clock::time_point u1 = std::chrono::steady_clock::now();
    //update the window
    this->window->update();

    //process an event from the event queue
    core::IEMS::process_event();

    core::System_Manager::update_systems();

    /************* START TEST CODE ***************/
    this->debug_camera->update_projection_matrix(core::Vector2f((float)this->window->get_width(), (float)this->window->get_height()));
    this->debug_camera->update_ortho_matrix(core::Vector2f((float)this->window->get_width(), (float)this->window->get_height()));
    this->debug_camera->set_view_matrix();
    this->debug_camera->update(this->frame_time.get_delta());
    /************* END TEST CODE *****************/

    std::chrono::steady_clock::time_point u2 = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point r1 = std::chrono::steady_clock::now();

    render();

    std::chrono::steady_clock::time_point r2 = std::chrono::steady_clock::now();

    PRINT_TIME_BLOCKS();

    Engine::get_instance()->window->swap_buffers();

    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>( t2 - t1 );
    std::chrono::duration<double> update_span = std::chrono::duration_cast<std::chrono::duration<double>>( u2 - u1 );
    std::chrono::duration<double> render_span = std::chrono::duration_cast<std::chrono::duration<double>>( r2 - r1 );

    Dynamic_Text_Component* test_dynam = core::Entity_Manager::get_component<Dynamic_Text_Component>(test_entity);
    test_dynam->text = "FPS: " + std::to_string(1000/this->frame_time.get_delta_ms());
    test_dynam->text += "\nTotal Time: " + std::to_string(time_span.count() * 1000) + "ms";
    test_dynam->text += "\nUpdate Time: " + std::to_string(update_span.count() * 1000) + "ms";
    test_dynam->text += "\nRender Time: " + std::to_string(render_span.count() * 1000) + "ms";
}

void Engine::shutdown()
{
    core::System_Manager::shutdown_systems();
}
