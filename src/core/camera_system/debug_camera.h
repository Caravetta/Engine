#if !defined(DEBUG_CAMERA_H)

#include "../core_common.h"
#include "../event_system/event_system.h"
#include "camera.h"

namespace core {

    class CORE_API Debug_Camera : public IEMS, public Camera {
    private:
        bool move_up;
        bool move_down;
        bool move_forward;
        bool move_backward;
        bool move_left;
        bool move_right;
        bool rotate_left;
        bool rotate_right;
        bool rotate_up;
        bool rotate_down;
        bool wire_frame;

    public:
        Debug_Camera( Vector3f position, Vector2f frame_dimesions );
        void update( float dt );

    private:
        void move_up_pressed( void * data );
        void move_down_pressed( void * data );
        void move_forward_pressed( void * data );
        void move_backward_pressed( void * data );
        void move_left_pressed( void * data );
        void move_right_pressed( void * data );
        void rotate_left_pressed( void * data );
        void rotate_right_pressed( void * data );
        void rotate_up_pressed( void * data );
        void rotate_down_pressed( void * data );
        void move_up_released( void * data );
        void move_down_released( void * data );
        void move_forward_released( void * data );
        void move_backward_released( void * data );
        void move_left_released( void * data );
        void move_right_released( void * data );
        void rotate_left_released( void * data );
        void rotate_right_released( void * data );
        void rotate_up_released( void * data );
        void rotate_down_released( void * data );
        void enable_wire_frame( void * data );
        void disable_wire_frame( void * data );
    };
} //end namespace core

#define DEBUG_CAMERA_H
#endif
