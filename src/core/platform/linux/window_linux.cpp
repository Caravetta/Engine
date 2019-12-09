#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <cstring>
#include <vector>
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
     std::vector<key_event_cb> key_callbacks;
     std::vector<mouse_position_cb> mouse_pos_callbacks;
     std::vector<mouse_button_cb> mouse_button_callbacks;
     std::vector<resize_cb> resize_callbacks;
};

static bool __is_extension_supported(const char *ext_list, const char *extension) {
     return strstr(ext_list, extension) != 0;
}

struct platform_window_t* platform_window_create( int width, int height, std::string title )
{
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

     XSelectInput(window->display, window->window,
                  KeyPressMask | KeyReleaseMask | PointerMotionMask |
                  ButtonPressMask | ButtonReleaseMask | StructureNotifyMask );

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
               LOG("State %c:%d", ev.xkey.state, ev.xkey.state);
               LOG("Keycode %c:%d", ev.xkey.keycode, ev.xkey.keycode);
               char c_key = (char)XLookupKeysym(&ev.xkey, 0);
               LOG("KEY %" PRIu32 "", (uint32_t)XLookupKeysym(&ev.xkey, 0));
               if ( c_key > 0 ) {
                    for ( size_t ii = 0; ii < platform_window->key_callbacks.size(); ii++ ) {
                         platform_window->key_callbacks[ii](c_key, true);
                    }
               }
          } else if ( ev.type == KeyRelease ) {
               char c_key = (char)XLookupKeysym(&ev.xkey, 0);
               for ( size_t ii = 0; ii < platform_window->key_callbacks.size(); ii++ ) {
                    platform_window->key_callbacks[ii](c_key, false);
               }
          } else if ( ev.type == MotionNotify ) {
               int mx = ev.xmotion.x;
               int my = ev.xmotion.y;
               for ( size_t ii = 0; ii < platform_window->mouse_pos_callbacks.size(); ii++) {
                    platform_window->mouse_pos_callbacks[ii](mx, my);
               }
          } else if ( ev.type == ButtonPress ) {
               for ( size_t ii = 0; ii < platform_window->mouse_button_callbacks.size(); ii++) {
                    platform_window->mouse_button_callbacks[ii](ev.xbutton.button, true);
               }
          } else if ( ev.type == ButtonRelease ) {
               for ( size_t ii = 0; ii < platform_window->mouse_button_callbacks.size(); ii++) {
                    platform_window->mouse_button_callbacks[ii](ev.xbutton.button, false);
               }
          } else if ( ev.type == ConfigureNotify ) {
               LOG("width %d height %d", ev.xconfigure.width, ev.xconfigure.height);
               platform_window->width = ev.xconfigure.width;
               platform_window->height = ev.xconfigure.height;
               for ( size_t ii = 0; ii < platform_window->resize_callbacks.size(); ii ++ ) {
                    platform_window->resize_callbacks[ii]((int32_t)ev.xconfigure.width, (int32_t)ev.xconfigure.height);
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

int platform_window_add_key_event_cb( struct platform_window_t* platform_window, key_event_cb callback )
{
     platform_window->key_callbacks.push_back(callback);
     return 0;
}

int platform_window_add_mouse_pos_cb( struct platform_window_t* platform_window, mouse_position_cb callback )
{
     platform_window->mouse_pos_callbacks.push_back(callback);
     return 0;
}

int platform_window_add_mouse_button_cb( struct platform_window_t* platform_window, mouse_button_cb callback )
{
     platform_window->mouse_button_callbacks.push_back(callback);
     return 0;
}

int platform_window_add_resize_cb( struct platform_window_t* platform_window, resize_cb callback )
{
     platform_window->resize_callbacks.push_back(callback);
     return 0;
}

} // end namespace Engine

