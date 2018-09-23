#include "engine.h"
#include "components/components.h"
#include "components/components.cpp"
#include "component_systems/component_systems.h"
#include "component_systems/component_systems.cpp"
#include "asset_types/assets.h"
#include "asset_types/assets.cpp"
#include "renderer.h"

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
    load_opengl_extensions();

    //create the game window
    this->window = new core::Window(1000, 800, "Launcher");

    //setup component manager
    component_manager = core::Component_Manager::get_instance();

    //setup entity manager
    enitiy_manager = core::Entity_Manager::get_instance();

    //setup system manager
    system_manager = core::System_Manager::get_instance();

    //setup asset manager
    asset_manager = core::Asset_Manager::get_instance();

    archetype_manager = core::Entity_Archetype_Manager::get_instance();

    //setup event manager
    //uh::CEMS::get_instance();

    //register all components NOTE: this will need to be generated maybe
    component_manager->register_component<Position_Component>();
    component_manager->register_component<Mesh_Component>();
    component_manager->register_component<Texture_Component>();
    component_manager->register_component<Shader_Component>();
    component_manager->register_component<Static_Text_Component>();
    //component_manager->register_component<Dynamic_Text_Component>();
    //component_manager->register_component<Cube_Orbit_Component>();

    //register all systems NOTE: this will need to be generated maybe
    system_manager->register_system<Mesh_Render_System>();
    system_manager->register_system<Text_Render_System>();
    //system_manager->register_system<Test_System>();
    //system_manager->register_system<Cube_Orbit_System>();

    /************* START TEST CODE ***************/

    debug_camera = new core::Debug_Camera(core::Vector3f(0, 55, -34), core::Vector2f(1000, 800));
    debug_camera->rotate(35.89, -0.2);

    /************* END TEST CODE *****************/

    system_manager->init_systems();
}

static int count = 0;

void Engine::update()
{

    this->frame_time.update();

    //update the window
    this->window->update();

    //process an event from the event queue
    core::IEMS::process_event();

    system_manager->update_systems();

    /************* START TEST CODE ***************/
    this->debug_camera->update_projection_matrix(core::Vector2f((float)this->window->get_width(), (float)this->window->get_height()));
    this->debug_camera->update_ortho_matrix(core::Vector2f((float)this->window->get_width(), (float)this->window->get_height()));
    this->debug_camera->set_view_matrix();
    this->debug_camera->update(this->frame_time.get_delta());
    /************* END TEST CODE *****************/

    render();

    Engine::get_instance()->window->swap_buffers();
}

void Engine::shutdown()
{
    system_manager->shutdown_systems();
}
