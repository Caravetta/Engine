#include <stdint.h>
#include <string>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <X11/Xlib.h>
#include "input_manager.h"

namespace Engine {

#define DEFAULT_STYLE WS_BORDER | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW

struct platform_window_t {
    int         width;
    int         height;
    int         show;
    Window      instance;
    //_XDisplay     display;
    std::string title;
};

int local_width;
int local_height;

void init( struct platform_window_t* window );

void platform_window_update( struct platform_window_t* platform_window )
{
#if 0
    XEvent e;
    XNextEvent(platform_window->display, &e);
    switch ( e.type ) {
    case MapNotify:
	break;
    case Expose:
	break;
    case ConfigureNotify:
        local_height = e.xconfigure.height;
        local_width = e.xconfigure.width;
	break;
    case VisibilityNotify:
	break;
    case DestroyNotify:
	XCloseDisplay(platform_window->display);
	break;
    case ButtonPress:
    case ButtonRelease:
        break;
    case EnterNotify:
    case MotionNotify:
    case LeaveNotify:
        Input_Manager::get_instance()->process_mouse_move(e.xmotion.x, e.xmotion.y);
	break;
    case KeyPress:
        Input_Manager::get_instance()->process_key_down((uint16_t)e.xkey.keycode);
        break;
    case KeyRelease:
        Input_Manager::get_instance()->process_key_up((uint16_t)e.xkey.keycode);
        break;
    }
        

    platform_window->width = local_width;
    platform_window->height = local_height;
#endif
}

struct platform_window_t* platform_window_create( int width, int height, std::string title )
{
    struct platform_window_t* window = new platform_window_t;
    window->width = width;
    window->height = height;
    local_width = width;
    local_height = height;
    window->title = title;
    init(window);

    return window;
}

void init( struct platform_window_t* window )
{
#if 0
   int s;
 
   window->display = XOpenDisplay(NULL);
   if (window->display == NULL) {
      fprintf(stderr, "Cannot open display\n");
      exit(1);
   }
 
   s = DefaultScreen(window->display);
   window->instance = XCreateSimpleWindow(window->display, 
					  RootWindow(window->display, s), 
					  10, 10, 100, 100, 1,
                                          BlackPixel(window->display, s), 
					  WhitePixel(window->display, s));
   XSelectInput(window->display, window->instance, ExposureMask | KeyPressMask);
   XMapWindow(window->display, window->instance);
#endif
}

void platform_window_swap_buffers( struct platform_window_t* platform_window )
{
#if 0
    glXSwapBuffers(platform_window->display, platform_window->instance);
#endif
}

int platform_window_get_width( struct platform_window_t* platform_window )
{
    return platform_window->width;
}

int platform_window_get_height( struct platform_window_t* platform_window )
{
    return platform_window->height;
}

} //end namespace Engine
