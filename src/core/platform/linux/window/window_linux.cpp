#include <stdint.h>
#include <string>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <X11/Xlib.h>
#include "../../../input_system/input_manager.h"

namespace core {

#define DEFAULT_STYLE WS_BORDER | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW

struct platform_window_t {
    int         width;
    int         height;
    int         show;
    bool        should_swap;
    Window      instance;
    GLXWindow   glxWindow;
    Display*     display;
    std::string title;
};

int local_width;
int local_height;

void init( struct platform_window_t* window );

static Bool WaitForNotify( Display *dpy, XEvent *event, XPointer arg ) {
    return (event->type == MapNotify) && (event->xmap.window == (Window) arg);
}

void platform_window_update( struct platform_window_t* platform_window )
{
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

int singleBufferAttributess[] = {
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE,   GLX_RGBA_BIT,
    GLX_RED_SIZE,      1,   /* Request a single buffered color buffer */
    GLX_GREEN_SIZE,    1,   /* with the maximum number of color bits  */
    GLX_BLUE_SIZE,     1,   /* for each component                     */
    None
};

int doubleBufferAttributes[] = {
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE,   GLX_RGBA_BIT,
    GLX_DOUBLEBUFFER,  True,  /* Request a double-buffered color buffer with */
    GLX_RED_SIZE,      1,     /* the maximum number of bits per component    */
    GLX_GREEN_SIZE,    1, 
    GLX_BLUE_SIZE,     1,
    None
};
/* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXIntro.xml */
void init( struct platform_window_t* window )
{
   window->display = XOpenDisplay(NULL);
   if (window->display == NULL) {
      fprintf(stderr, "Cannot open display\n");
      exit(1);
   }
 
   //int s = DefaultScreen(window->display);
   //window->instance = XCreateSimpleWindow(window->display, 
   //     				  RootWindow(window->display, s), 
   //     				  10, 10, 100, 100, 1,
   //                                       BlackPixel(window->display, s), 
   //     				  WhitePixel(window->display, s));
   //XSelectInput(window->display, window->instance, ExposureMask | KeyPressMask);
   //XMapWindow(window->display, window->instance);

   GLXFBConfig *fbConfigs;
   int numReturned;
   fbConfigs = glXChooseFBConfig( window->display, DefaultScreen(window->display),
                                  doubleBufferAttributes, &numReturned );

   if ( fbConfigs == NULL ) {  /* no double buffered configs available */
       fbConfigs = glXChooseFBConfig( window->display, DefaultScreen(window->display),
               singleBufferAttributess, &numReturned );
       window->should_swap = False;
   }

    /* Create an X colormap and window with a visual matching the first
    ** returned framebuffer config */
    XVisualInfo *vInfo;
    vInfo = glXGetVisualFromFBConfig( window->display, fbConfigs[0] );

    init_opengl(window->display, vInfo);

    XSetWindowAttributes swa = {};
    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;
    swa.colormap = XCreateColormap( window->display, RootWindow(window->display, vInfo->screen),
                                    vInfo->visual, AllocNone );
    unsigned long swaMask = CWBorderPixel | CWColormap | CWEventMask;
    window->instance = XCreateWindow( window->display, RootWindow(window->display, vInfo->screen), 0, 0, 256, 256,
                              0, vInfo->depth, InputOutput, vInfo->visual,
                              swaMask, &swa );

    /* Create a GLX context for OpenGL rendering */
    GLXContext context = glXCreateNewContext( window->display, fbConfigs[0], GLX_RGBA_TYPE,
				 NULL, True );

    /* Create a GLX window to associate the frame buffer configuration
    ** with the created X window */
    window->glxWindow = glXCreateWindow( window->display, fbConfigs[0], window->instance, NULL );
    
    /* Map the window to the screen, and wait for it to appear */
    XMapWindow( window->display, window->instance );
    XEvent event;

    XIfEvent( window->display, &event, WaitForNotify, (XPointer) window->instance );

    /* Bind the GLX context to the Window */
    glXMakeContextCurrent( window->display, window->glxWindow, window->glxWindow, context );
}

void platform_window_swap_buffers( struct platform_window_t* platform_window )
{
    glXSwapBuffers(platform_window->display, platform_window->instance);
}

int platform_window_get_width( struct platform_window_t* platform_window )
{
    return platform_window->width;
}

int platform_window_get_height( struct platform_window_t* platform_window )
{
    return platform_window->height;
}

} //end namespace core
