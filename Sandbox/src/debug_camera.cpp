#include "debug_camera.h"

typedef struct {
    Engine::Camera* camera;
} debug_camera_t;

debug_camera_t camera;

Engine::Camera* get_debug_camera()
{
    return camera.camera;
}

void move_up_pressed( void* data, size_t data_size )
{
    //UNUSED_ARG( data );
    //UNUSED_ARG( data_size );
    camera.camera->move(0 , 100 * Engine::get_delta_time(), 0);
}

void move_down_pressed( void* data, size_t data_size )
{
    camera.camera->move(0 , -100 * Engine::get_delta_time(), 0);
}

void move_left_pressed( void* data, size_t data_size )
{
    camera.camera->move(-1000 * Engine::get_delta_time(), 0, 0);
}

void move_right_pressed( void* data, size_t data_size )
{
    camera.camera->move(1000 * Engine::get_delta_time(), 0, 0);
}

void rotate_left_pressed( void* data, size_t data_size )
{
    camera.camera->rotate(-2 * Engine::get_delta_time(), 0);
}

void rotate_right_pressed( void* data, size_t data_size )
{
    camera.camera->rotate(2 * Engine::get_delta_time(), 0);
}

void rotate_up_pressed( void* data, size_t data_size )
{
    camera.camera->rotate(0, 2 * Engine::get_delta_time());
}

void rotate_down_pressed( void* data, size_t data_size )
{
    camera.camera->rotate(0, -2 * Engine::get_delta_time());
}

void move_forward_pressed( void* data, size_t data_size )
{
    camera.camera->move(0, 0, 100 * Engine::get_delta_time());
}

void move_backward_pressed( void* data, size_t data_size )
{
    camera.camera->move(0, 0, -100 * Engine::get_delta_time());
}

void debug_camera_init()
{
    camera.camera = new Engine::Camera(Engine::Vector3f(0, 1, 55), Engine::Vector2f(800, 800));
    Engine::subscribe_to_event("KEY_W_PRESSED", &move_forward_pressed);
    Engine::subscribe_to_event("KEY_S_PRESSED", &move_backward_pressed);
    Engine::subscribe_to_event("KEY_A_PRESSED", &move_left_pressed);
    Engine::subscribe_to_event("KEY_D_PRESSED", &move_right_pressed);
    Engine::subscribe_to_event("KEY_Q_PRESSED", &rotate_left_pressed);
    Engine::subscribe_to_event("KEY_E_PRESSED", &rotate_right_pressed);
    Engine::subscribe_to_event("KEY_X_PRESSED", &move_down_pressed);
    Engine::subscribe_to_event("KEY_SPACE_PRESSED", &move_up_pressed);
    Engine::subscribe_to_event("KEY_R_PRESSED", &rotate_up_pressed);
    Engine::subscribe_to_event("KEY_F_PRESSED", &rotate_down_pressed);
}
