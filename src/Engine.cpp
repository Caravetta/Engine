#include "Engine.h"
#include "core_common.h"
#include "window.h"
#include "input_manager.h"
#include "system_manager.h"
#include "timer.h"
#include "renderer.h"
#include "archetype_manager.h"
#include "font_manager.h"
#include "job_manager.h"
#include "entity_manager.h"
#include "worker_manager.h"
#include "mesh_manager.h"
#include "event_system.h"
#include "texture_manager.h"
#include "token_parser.h"
#include "header_parser.h"
#include "material_manager.h"

namespace Engine {

typedef struct {
    Timer   frame_time;
    Camera* active_camera;
} engine_data_t;

engine_data_t* engine_data;

Rc_t init( engine_config_t* engine_config )
{
    engine_data = new (std::nothrow) engine_data_t;
    if ( engine_data == NULL ) {
        LOG_ERROR("Failed to allocate engine data");
        return ENGINE_ERROR;
    }

    //std::vector<std::string> files;
    //files.push_back("res/test.txt");
    //Token_Parser::tokenize_file("res/test.txt" );
    //Introspection::parse_headers(&files);

    Rc_t rc = Event_Manager::init();

    rc = Input_Manager::init();

    rc = Window::create(engine_config->window_width, engine_config->window_height, engine_config->window_title);
    if ( rc != SUCCESS ) {
        LOG_ERROR("Failed to create window");
        return ENGINE_ERROR;
    }

    engine_data->active_camera = NULL;

    //TODO(JOSH): need to check the rc from the init functions

    rc = Material_Manager::init();
    if ( rc != SUCCESS ) {
        LOG("Failed to init Material_Manager");
        return ENGINE_ERROR;
    }

    rc = Component_Manager::init();
    if ( rc != SUCCESS ) {
        return ENGINE_ERROR;
    }

    rc = Job_Manager::init();
    if ( rc != SUCCESS ) {
        return ENGINE_ERROR;
    }

    rc = Worker_Manager::init();
    if ( rc != SUCCESS ) {
        return ENGINE_ERROR;
    }

    rc = Entity_Manager::init();
    if ( rc != SUCCESS ) {
        return ENGINE_ERROR;
    }

    rc = Archetype_Manager::init();
    if ( rc != SUCCESS ) {
        return ENGINE_ERROR;
    }

    rc = Mesh_Manager::init();
    if ( rc != SUCCESS ) {
        return ENGINE_ERROR;
    }

    rc = Texture_Manager::init();
    if ( rc != SUCCESS ) {
        return ENGINE_ERROR;
    }

    Font_Manager::init();

    return SUCCESS;
}

void run()
{
    System_Manager::init_systems();

    while ( !Window::is_closed() ) {
        engine_data->frame_time.update();

        Window::update();

        Event_Manager::process_event();
        System_Manager::update_systems();

        //TODO(JOSH): move upading the dims to an event based on window resize
        Vector2f frame_size((float)Window::get_width(), (float)Window::get_height());

        render( engine_data->active_camera, (int)frame_size.x, (int)frame_size.y );

        Window::swap_buffers();

        Entity_Manager::update();
    }

}

void shutdown()
{
    System_Manager::shutdown_systems();
}

void set_active_camera( Camera* camera )
{
    engine_data->active_camera = camera;
}

Camera* get_active_camera( void )
{
    return engine_data->active_camera;
}

float get_delta_time()
{
    return engine_data->frame_time.get_delta();
}

Rc_t create_event( std::string event_name )
{
    return Event_Manager::create_event_id(event_name);
}

Rc_t subscribe_to_event( std::string event_name, void (*callback)(void*, size_t) )
{
    return Event_Manager::subscribe_to_event(event_name, callback);
}

Rc_t broadcast_event( std::string event_name, void* data, size_t data_size )
{
    return Event_Manager::broadcast_event(event_name, data, data_size);
}

bool is_key_pressed( key_t key )
{
    return Input_Manager::is_key_pressed(key);
}

/****************************************/
/*                                      */
/*        Mesh Engine Calls             */
/*                                      */
/****************************************/

Mesh_Handle load_to_graphics_api( Mesh* mesh )
{
    return Mesh_Manager::load_to_graphics_api(mesh, MESH_STATIC_DRAW);
}

Mesh_Handle load_to_graphics_api( Mesh* mesh , mesh_usage_t usage_type )
{
    return Mesh_Manager::load_to_graphics_api(mesh, usage_type);
}

Rc_t update_mesh( Mesh_Handle handle, Mesh* mesh )
{
    return Mesh_Manager::update_mesh(handle, mesh);
}

/****************************************/
/*                                      */
/*       Texture Engine Calls           */
/*                                      */
/****************************************/

Texture_Handle load_texture_to_graphics_api( Texture* texture )
{
    return Texture_Manager::load_to_graphics_api(texture);
}

/****************************************/
/*                                      */
/*      Material Engine Calls           */
/*                                      */
/****************************************/

Material_Handle register_material( std::string material_name, Material material )
{
    return Material_Manager::register_material(material_name, material);
}

Material_Handle get_material_handle( std::string material_name )
{
    return Material_Manager::get_material_handle(material_name);
}

Material* get_material( std::string material_name )
{
    return Material_Manager::get_material(material_name);
}

} // end namespace Engine
