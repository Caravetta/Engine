#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <cstring>
#include "window_linux.h"

namespace Engine {

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

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
};

static bool __is_extension_supported(const char *ext_list, const char *extension) {
     return strstr(ext_list, extension) != 0;
}

struct platform_window_t* platform_window_create( int width, int height, std::string title )
{
     platform_window_t* window = new platform_window_t;

     window->width = width;
     window->height = height;
     window->is_closed = false;

     // create the display
     window->display = XOpenDisplay(NULL);
     if ( window->display == NULL ) {
          LOG_ERROR("%s: Failed to open display", __FUNCTION__);
     }

     window->screen = DefaultScreenOfDisplay(window->display);
     window->screenId = DefaultScreen(window->display);

     // check GLX version info
     GLint major_glx, minor_glx = 0;

     glXQueryVersion(window->display, &major_glx, &minor_glx);
     if ( major_glx <= 1 && minor_glx < 2 ) {
          LOG_ERROR("%s: GLX version 1.2 or greater is required", __FUNCTION__);
          XCloseDisplay(window->display);
          delete window;
          return NULL;
     }

     GLint glx_attributes[] = {
          GLX_X_RENDERABLE    , True,
          GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
          GLX_RENDER_TYPE     , GLX_RGBA_BIT,
          GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
          GLX_RED_SIZE        , 8,
          GLX_GREEN_SIZE      , 8,
          GLX_BLUE_SIZE       , 8,
          GLX_ALPHA_SIZE      , 8,
          GLX_DEPTH_SIZE      , 24,
          GLX_STENCIL_SIZE    , 8,
          GLX_DOUBLEBUFFER    , True,
          None
     };

     int fb_count = 0;

     GLXFBConfig* fb_configs = glXChooseFBConfig(window->display, window->screenId, glx_attributes, &fb_count);
     if ( fb_configs == NULL ) {
          LOG_ERROR("%s: Failed to retrieve framebuffer configs", __FUNCTION__);
          XCloseDisplay(window->display);
          delete window;
          return NULL;
     }

     // loop through framebuffers and pick config with most samples per pixel
     int best_fbc = -1;
     int worst_fbc = -1;
     int best_num_samp = -1;
     int worst_num_samp = 999;

     for ( int ii = 0; ii < fb_count; ++ii ) {
          XVisualInfo* vis_info = glXGetVisualFromFBConfig(window->display, fb_configs[ii]);
          if ( vis_info != NULL ) {
               int samp_buf, samples;
               glXGetFBConfigAttrib( window->display, fb_configs[ii], GLX_SAMPLE_BUFFERS, &samp_buf );
               glXGetFBConfigAttrib( window->display, fb_configs[ii], GLX_SAMPLES       , &samples  );

               if ( best_fbc < 0 || (samp_buf && samples > best_num_samp) ) {
                    best_fbc = ii;
                    best_num_samp = samples;
               }
               if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
                    worst_fbc = ii;
               worst_num_samp = samples;
          }
          XFree(vis_info);
     }

     GLXFBConfig fb_config = fb_configs[best_fbc];
     XFree(fb_configs);

     XVisualInfo* vis_info = glXGetVisualFromFBConfig(window->display, fb_config);
     if ( vis_info == NULL ) {
          LOG_ERROR("%s: Failed to create visual window", __FUNCTION__);
          XCloseDisplay(window->display);
          delete window;
          return NULL;
     }

     if ( window->screenId != vis_info->screen ) {
          LOG_ERROR("%s: Screen Ids do not match", __FUNCTION__);
          XCloseDisplay(window->display);
          delete window;
          return NULL;
     }

     // try to open the window
     XSetWindowAttributes window_attributes;

     window_attributes.border_pixel = BlackPixel(window->display, window->screenId);
     window_attributes.background_pixel = WhitePixel(window->display, window->screenId);
     window_attributes.override_redirect = True;
     window_attributes.colormap = XCreateColormap(window->display,
                                                  RootWindow(window->display, window->screenId),
                                                  vis_info->visual,
                                                  AllocNone);
     window_attributes.event_mask = ExposureMask;

     window->window = XCreateWindow(window->display,
                                    RootWindow(window->display,window->screenId),
                                    0,
                                    0,
                                    width,
                                    height,
                                    0,
                                    vis_info->depth,
                                    InputOutput,
                                    vis_info->visual,
                                    CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
                                    &window_attributes);

     XStoreName(window->display, window->window, title.c_str());

     window->atom_delete_window = XInternAtom(window->display, "WM_DELETE_WINDOW", False);
     XSetWMProtocols(window->display, window->window, &window->atom_delete_window, 1);

     // setup GLX OpenGL context
     glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
     glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );

     int context_attributes[] = {
          GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
          GLX_CONTEXT_MINOR_VERSION_ARB, 2,
          GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
          None
     };

     GLXContext context = 0;

     const char *glxExts = glXQueryExtensionsString(window->display, window->screenId);
     if ( __is_extension_supported( glxExts, "GLX_ARB_create_context") == false ) {
          LOG("%s: GLX_ARB_create_context not supported", __FUNCTION__);
          context = glXCreateNewContext( window->display, fb_config, GLX_RGBA_TYPE, 0, True );
     } else {
          context = glXCreateContextAttribsARB(window->display, fb_config, 0, true, context_attributes);
     }

     XSync( window->display, False );

     // check to see if the context is direct or indirect
     if ( glXIsDirect(window->display, context) == false ) {
          LOG("Obtained indirect rendering context");
     } else {
          LOG("Obtained direct rendering context");
     }

     glXMakeCurrent(window->display, window->window, context);

     window->vis_info = vis_info;

     LOG("GL Renderer: %s", glGetString(GL_RENDERER));
     LOG("GL Version: %s", glGetString(GL_VERSION));
     LOG("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
#if 0
     if ( Initialize(width, height) == false ) {
          glXDestroyContext(window->display, context);
          XFree(vis_info);
          XFreeColormap(window->display, window_attributes.colormap);
          XDestroyWindow(window->display, window->window);
          XCloseDisplay(window->display);
          delete window;
          return NULL;
     }
#endif
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
          }
     }
}

void platform_window_swap_buffers( struct platform_window_t* platform_window )
{
     glXSwapBuffers(platform_window->display, platform_window->window);
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

