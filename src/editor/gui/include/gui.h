#ifndef __GUI_H__
#define __GUI_H__

#include "core_common.h"
#include "imgui.h"

Engine::Rc_t init_gui( const int32_t fb_width, const int32_t fb_height );
void gui_start_frame( void );
Engine::Rc_t render_gui( void );
void gui_key_event_callback( char key, bool is_pressed );
void gui_mouse_pos_callback( int x_pos, int y_pos );
void gui_mouse_button_callback( int button, bool is_pressed );
void gui_resize_callback( int32_t width, int32_t height );

#endif //__GUI_H__
