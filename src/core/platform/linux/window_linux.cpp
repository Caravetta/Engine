#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <cstring>
#include "window_linux.h"
#include "platform_graphics.h"
#include "input_linux.h"

namespace Engine {

//typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

struct platform_window_t {
     int       width;
     int       height;
     bool      is_closed;
     Display*  display;
     Window    window;
     Screen*   screen;
     int       screenId;
     XEvent    ev;
     XVisualInfo* vis_info;
     Atom atom_delete_window;
     std::string title;
};

static bool __is_extension_supported(const char *ext_list, const char *extension) {
     return strstr(ext_list, extension) != 0;
}

struct platform_window_t* platform_window_create( int width, int height, std::string title )
{
     LOG("NUM KEYS %d", PLATFORM_KEY_COUNT);

     platform_window_t* window = new platform_window_t;

     window->width = width;
     window->height = height;
     window->title = title;
     window->is_closed = false;

     // create the display
     window->display = XOpenDisplay(NULL);
     if ( window->display == NULL ) {
          LOG_ERROR("%s: Failed to open display", __FUNCTION__);
     }

     window->screen = DefaultScreenOfDisplay(window->display);
     window->screenId = DefaultScreen(window->display);

     Rc_t rc = create_render_context(window);
     if ( rc != SUCCESS ) {
          XCloseDisplay(window->display);
          delete window;
          return NULL;
     }

     XSelectInput(window->display, window->window, KeyPressMask | KeyReleaseMask );

     // show the window
     XClearWindow(window->display, window->window);
     XMapRaised(window->display, window->window);

     return window;
}

void platform_window_update( struct platform_window_t* platform_window )
{
     if (XPending(platform_window->display) > 0) {
          XEvent ev;
          XNextEvent(platform_window->display, &ev);
          if ( ev.type == Expose ) {
               XWindowAttributes attributes;
               XGetWindowAttributes(platform_window->display, platform_window->window, &attributes);
               platform_window->width = attributes.width;
               platform_window->height = attributes.height;
          }
          if ( ev.type == ClientMessage ) {
               if ( ev.xclient.data.l[0] == platform_window->atom_delete_window ) {
                    platform_window->is_closed = true;
               }
          } else if ( ev.type == DestroyNotify ) {
               platform_window->is_closed = true;
          } else if ( ev.type == KeyPress ) {
               if ( ev.xkey.keycode < Platform_Key::PLATFORM_KEY_COUNT ) {
                    key_state[ev.xkey.keycode] = true;
               }
          } else if ( ev.type == KeyRelease ) {
               if ( ev.xkey.keycode < Platform_Key::PLATFORM_KEY_COUNT ) {
                    key_state[ev.xkey.keycode] = false;
               }
          }
     }
}

void platform_window_swap_buffers( struct platform_window_t* platform_window )
{
     //glXSwapBuffers(platform_window->display, platform_window->window);
     swap_buffer(platform_window);
}

bool platform_window_is_closed( struct platform_window_t* platform_window )
{
     return platform_window->is_closed;
}

int platform_window_get_width( struct platform_window_t* platform_window )
{
     return platform_window->width;
}

int platform_window_get_height( struct platform_window_t* platform_window )
{
     return platform_window->height;
}

} // end namespace Engine

