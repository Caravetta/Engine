#ifndef __GUI_H__
#define __GUI_H__

#include "core_common.h"
#include "engine_core.h"
#include "imgui.h"
#include "imgui_canvas.h"

Engine::Rc_t init_gui( Engine::Window& window );
void gui_start_frame( void );
Engine::Rc_t render_gui( void );

#endif //__GUI_H__
