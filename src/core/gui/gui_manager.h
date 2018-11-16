#ifndef __GUI_MANAGER_H__
#define __GUI_MANAGER_H__

#include "../core_common.h"

namespace core {
namespace Gui {

CORE_API void init( std::string vert_path, std::string frag_path );
CORE_API void render();

//Frame
typedef enum {
    FRAME_COLLAPSIBLE   = 1 << 0,
    FRAME_CLOSE_BUTTON  = 1 << 1,
    FRMAE_NOT_MOVABLE   = 1 << 2,
} frame_flags_t;

CORE_API void start_frame( std::string title, bool active, Vector3f position );
CORE_API void end_frame();

//Button
typedef enum {
    BUTTON_CLICK_ON_RELEASE = 1 << 0,
} button_flags_t;
CORE_API bool button( std::string text );

//Text
CORE_API void text( std::string text );

} // end namespace Gui
} // end namespace core

#endif //__GUI_MANAGER_H__
