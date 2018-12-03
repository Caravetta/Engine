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

    Rc_t rc = Window::create(engine_config->window_width, engine_config->window_height, engine_config->window_title);
    if ( rc != SUCCESS ) {
        LOG_ERROR("Failed to create window");
        return ENGINE_ERROR;
    }

    engine_data->active_camera = NULL;

    //TODO(JOSH): need to check the rc from the init functions
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

    Font_Manager::get_instance();

    return SUCCESS;
}

void run()
{
    System_Manager::init_systems();

    while ( !Window::is_closed() ) {
        engine_data->frame_time.update();

        Window::update();

        IEMS::process_event();
        System_Manager::update_systems();

        //TODO(JOSH): move upading the dims to an event based on window resize
        Vector2f frame_size((float)Window::get_width(), (float)Window::get_height());

        if ( engine_data->active_camera != NULL ) {
            //TODO(JOSH): move upading the proj and ortho to an event based on window resize
            engine_data->active_camera->update_projection_matrix(frame_size);
            engine_data->active_camera->update_ortho_matrix(frame_size);
            engine_data->active_camera->set_view_matrix();
        }

        render( engine_data->active_camera, (int)frame_size.x, (int)frame_size.y );

        Window::swap_buffers();
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

float get_delta_time()
{
    return engine_data->frame_time.get_delta();
}

} // end namespace Engine
