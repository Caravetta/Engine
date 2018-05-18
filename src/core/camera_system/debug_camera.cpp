#include "debug_camera.h"

namespace core {

Debug_Camera::Debug_Camera( Vector3f position, Vector2f frame_dimesions )
: Camera( position, frame_dimesions )
{
    move_up = false;
    move_down = false;
    move_forward = false;
    move_backward = false;
    move_left = false;
    move_right = false;
    rotate_left = false;
    rotate_right = false;
    rotate_up = false;
    rotate_down = false;
    wire_frame = false;

    register_event(KEY_SPACE_PRESSED, this, (core::Callback)&Debug_Camera::move_up_pressed);
    register_event(KEY_X_PRESSED, this, (core::Callback)&Debug_Camera::move_down_pressed);
    register_event(KEY_W_PRESSED, this, (core::Callback)&Debug_Camera::move_forward_pressed);
    register_event(KEY_S_PRESSED, this, (core::Callback)&Debug_Camera::move_backward_pressed);
    register_event(KEY_A_PRESSED, this, (core::Callback)&Debug_Camera::move_left_pressed);
    register_event(KEY_D_PRESSED, this, (core::Callback)&Debug_Camera::move_right_pressed);
    register_event(KEY_Q_PRESSED, this, (core::Callback)&Debug_Camera::rotate_left_pressed);
    register_event(KEY_E_PRESSED, this, (core::Callback)&Debug_Camera::rotate_right_pressed);
    register_event(KEY_R_PRESSED, this, (core::Callback)&Debug_Camera::rotate_up_pressed);
    register_event(KEY_F_PRESSED, this, (core::Callback)&Debug_Camera::rotate_down_pressed);
    register_event(KEY_T_PRESSED, this, (core::Callback)&Debug_Camera::enable_wire_frame);
    register_event(KEY_Y_PRESSED, this, (core::Callback)&Debug_Camera::disable_wire_frame);

    register_event(KEY_SPACE_RELEASED, this, (core::Callback)&Debug_Camera::move_up_released);
    register_event(KEY_X_RELEASED, this, (core::Callback)&Debug_Camera::move_down_released);
    register_event(KEY_W_RELEASED, this, (core::Callback)&Debug_Camera::move_forward_released);
    register_event(KEY_S_RELEASED, this, (core::Callback)&Debug_Camera::move_backward_released);
    register_event(KEY_A_RELEASED, this, (core::Callback)&Debug_Camera::move_left_released);
    register_event(KEY_D_RELEASED, this, (core::Callback)&Debug_Camera::move_right_released);
    register_event(KEY_Q_RELEASED, this, (core::Callback)&Debug_Camera::rotate_left_released);
    register_event(KEY_E_RELEASED, this, (core::Callback)&Debug_Camera::rotate_right_released);
    register_event(KEY_R_RELEASED, this, (core::Callback)&Debug_Camera::rotate_up_released);
    register_event(KEY_F_RELEASED, this, (core::Callback)&Debug_Camera::rotate_down_released);
}

void Debug_Camera::update( float dt )
{
    if ( move_up ) {
        move(0 , 100 * dt, 0);
    }
    if ( move_down ) {
        move(0 , -100 * dt, 0);
    }
    if ( move_forward ) {
        move(0, 0, 100 * dt);
    }
    if ( move_backward ) {
        move(0, 0, -100 * dt);
    }
    if ( rotate_left ) {
        rotate(-2 * dt, 0);
    }
    if ( rotate_right ) {
        rotate(2 * dt, 0);
    }
    if ( rotate_up ) {
        rotate(0, 2 * dt);
    }
    if ( rotate_down ) {
        rotate(0, -2 * dt);
    }
    if (wire_frame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_CULL_FACE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
    }
}

void Debug_Camera::move_up_pressed( void * data )
{
    move_up = true;
}

void Debug_Camera::move_down_pressed( void * data )
{
    move_down = true;
}

void Debug_Camera::move_forward_pressed( void * data )
{
    move_forward = true;
}

void Debug_Camera::move_backward_pressed( void * data )
{
    move_backward = true;
}

void Debug_Camera::move_left_pressed( void * data )
{
    move_left = true;
}

void Debug_Camera::move_right_pressed( void * data )
{
    move_right = true;
}

void Debug_Camera::rotate_left_pressed( void * data )
{
    rotate_left = true;
}

void Debug_Camera::rotate_right_pressed( void * data )
{
    rotate_right = true;
}

void Debug_Camera::rotate_up_pressed( void * data )
{
    rotate_up = true;
}

void Debug_Camera::rotate_down_pressed( void * data )
{
    rotate_down = true;
}

void Debug_Camera::move_up_released( void * data )
{
    move_up = false;
}

void Debug_Camera::move_down_released( void * data )
{
    move_down = false;
}

void Debug_Camera::move_forward_released( void * data )
{
    move_forward = false;
}

void Debug_Camera::move_backward_released( void * data )
{
    move_backward = false;
}

void Debug_Camera::move_left_released( void * data )
{
    move_left = false;
}

void Debug_Camera::move_right_released( void * data )
{
    move_right = false;
}

void Debug_Camera::rotate_left_released( void * data )
{
    rotate_left = false;
}

void Debug_Camera::rotate_right_released( void * data )
{
    rotate_right = false;
}

void Debug_Camera::rotate_up_released( void * data )
{
    rotate_up = false;
}

void Debug_Camera::rotate_down_released( void * data )
{
    rotate_down = false;
}

void Debug_Camera::enable_wire_frame( void * data )
{
    wire_frame = true;
}

void Debug_Camera::disable_wire_frame( void * data )
{
    wire_frame = false;
}

} //end namespace core
