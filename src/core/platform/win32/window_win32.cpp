#include <windows.h>
#include <gl/gl.h>
#include "window_win32.h"
#include "opengl_win32.h"

namespace Engine {

#define WGL_NUMBER_PIXEL_FORMATS_ARB      0x2000
#define WGL_DRAW_TO_WINDOW_ARB            0x2001
#define WGL_DRAW_TO_BITMAP_ARB            0x2002
#define WGL_ACCELERATION_ARB              0x2003
#define WGL_NEED_PALETTE_ARB              0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB       0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB        0x2006
#define WGL_SWAP_METHOD_ARB               0x2007
#define WGL_NUMBER_OVERLAYS_ARB           0x2008
#define WGL_NUMBER_UNDERLAYS_ARB          0x2009
#define WGL_TRANSPARENT_ARB               0x200A
#define WGL_TRANSPARENT_RED_VALUE_ARB     0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB   0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB    0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB   0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB   0x203B
#define WGL_SHARE_DEPTH_ARB               0x200C
#define WGL_SHARE_STENCIL_ARB             0x200D
#define WGL_SHARE_ACCUM_ARB               0x200E
#define WGL_SUPPORT_GDI_ARB               0x200F
#define WGL_SUPPORT_OPENGL_ARB            0x2010
#define WGL_DOUBLE_BUFFER_ARB             0x2011
#define WGL_STEREO_ARB                    0x2012
#define WGL_PIXEL_TYPE_ARB                0x2013
#define WGL_COLOR_BITS_ARB                0x2014
#define WGL_RED_BITS_ARB                  0x2015
#define WGL_RED_SHIFT_ARB                 0x2016
#define WGL_GREEN_BITS_ARB                0x2017
#define WGL_GREEN_SHIFT_ARB               0x2018
#define WGL_BLUE_BITS_ARB                 0x2019
#define WGL_BLUE_SHIFT_ARB                0x201A
#define WGL_ALPHA_BITS_ARB                0x201B
#define WGL_ALPHA_SHIFT_ARB               0x201C
#define WGL_ACCUM_BITS_ARB                0x201D
#define WGL_ACCUM_RED_BITS_ARB            0x201E
#define WGL_ACCUM_GREEN_BITS_ARB          0x201F
#define WGL_ACCUM_BLUE_BITS_ARB           0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB          0x2021
#define WGL_DEPTH_BITS_ARB                0x2022
#define WGL_STENCIL_BITS_ARB              0x2023
#define WGL_AUX_BUFFERS_ARB               0x2024
#define WGL_NO_ACCELERATION_ARB           0x2025
#define WGL_GENERIC_ACCELERATION_ARB      0x2026
#define WGL_FULL_ACCELERATION_ARB         0x2027
#define WGL_SWAP_EXCHANGE_ARB             0x2028
#define WGL_SWAP_COPY_ARB                 0x2029
#define WGL_SWAP_UNDEFINED_ARB            0x202A
#define WGL_TYPE_RGBA_ARB                 0x202B
#define WGL_TYPE_COLORINDEX_ARB           0x202C
#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB       0x2093
#define WGL_CONTEXT_FLAGS_ARB             0x2094
#define ERROR_INVALID_VERSION_ARB         0x2095
#define WGL_SAMPLE_BUFFERS_ARB            0x2041
#define WGL_SAMPLES_ARB                   0x2042
#define WGL_CONTEXT_DEBUG_BIT_ARB         0x00000001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001

struct platform_window_t {
     int       width;
     int       height;
     bool      is_closed;
     HWND      hWnd;
     HINSTANCE instance;
     HDC       hDC;
     HGLRC     hglrc;
};

bool is_closed = false;

LRESULT CALLBACK _WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
     switch( msg )
     {
          case WM_CLOSE:
               DestroyWindow(hwnd);
               is_closed = true;
          break;
          case WM_KEYDOWN:
          break;
          case WM_KEYUP:
          break;
          case WM_MOUSEMOVE:
          break;
          case WM_SIZE:
          break;
          default:
               return DefWindowProc(hwnd, msg, wParam, lParam);
     }

     return 0;
}

LRESULT CALLBACK _TempWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
     switch( msg )
     {
          case WM_CLOSE:
          break;
          default:
               return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

struct platform_window_t* platform_window_create( int width, int height, std::string title )
{
     platform_window_t* window = new platform_window_t;

     window->width = width;
     window->height = height;
     window->is_closed = false;
     WNDCLASSEX wc;

     wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
     wc.lpfnWndProc = (WNDPROC)_WndProc;
     wc.cbClsExtra = 0;
     wc.cbWndExtra = 0;
     wc.hInstance = window->instance;
     wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
     wc.hIconSm = wc.hIcon;
     wc.hCursor = LoadCursor(NULL, IDC_ARROW);
     wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
     wc.lpszMenuName = NULL;
     wc.lpszClassName = title.c_str();
     wc.cbSize = sizeof(WNDCLASSEX);
     //TODO: need to make wc.lpszClassName more robust

     if ( !RegisterClassEx(&wc) ) {
          //TODO: add in logging
          DWORD dw = GetLastError();
          UNUSED_ARG(dw);
          return NULL;
     }

     int screenWidth = GetSystemMetrics(SM_CXSCREEN);
     int screenHeight = GetSystemMetrics(SM_CYSCREEN);
     int screen_pos_x = 0;
     int screen_pos_y = 0;

     if ( 0 ) {
        //TODO: add in code to handle full screen
     }
     else {
          screenWidth = window->width;
          screenHeight = window->height;
          screen_pos_x = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
          screen_pos_y = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
     }

     HWND parent_hwnd = NULL;

     window->hWnd = CreateWindowEx(WS_EX_APPWINDOW,
                                   title.c_str(),
                                   title.c_str(),
                                   WS_BORDER | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
                                   screen_pos_x,
                                   screen_pos_y,
                                   screenWidth,
                                   screenHeight,
                                   parent_hwnd, NULL,
                                   window->instance,
                                   NULL);

     if ( window->hWnd == NULL ) {
          return NULL;
     }

     int attributeListInt[30];
     int pixelFormat[1];
     unsigned int formatCount;
     int result;
     PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
     int attributeList[5];

     //init_opengl(&window->hDC, &window->hWnd, &window->hglrc);
     window->hDC = GetDC(window->hWnd);
     if ( !window->hWnd ) {
          LOG_ERROR("Failed to get window context");
          return NULL;
     }

     // Support for OpenGL rendering.
     attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
     attributeListInt[1] = TRUE;

     // Support for rendering to a window.
     attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
     attributeListInt[3] = TRUE;

     // Support for hardware acceleration.
     attributeListInt[4] = WGL_ACCELERATION_ARB;
     attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;

     // Support for 24bit color.
     attributeListInt[6] = WGL_COLOR_BITS_ARB;
     attributeListInt[7] = 24;

     // Support for 24 bit depth buffer.
     attributeListInt[8] = WGL_DEPTH_BITS_ARB;
     attributeListInt[9] = 24;

     // Support for double buffer.
     attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
     attributeListInt[11] = TRUE;

     // Support for swapping front and back buffer.
     attributeListInt[12] = WGL_SWAP_METHOD_ARB;
     attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;

     // Support for the RGBA pixel type.
     attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
     attributeListInt[15] = WGL_TYPE_RGBA_ARB;

     // Support for a 8 bit stencil buffer.
     attributeListInt[16] = WGL_STENCIL_BITS_ARB;
     attributeListInt[17] = 8;

     //attributeList[18] = WGL_CONTEXT_PROFILE_MASK_ARB;
     //attributeList[19] = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;

     attributeListInt[18] = WGL_SAMPLE_BUFFERS_ARB;
     attributeListInt[19] = 1;

     attributeListInt[20] = WGL_SAMPLES_ARB;
     attributeListInt[21] = 4;

     // Null terminate the attribute list.
     attributeListInt[22] = 0;

     result = OpenGL::wglChoosePixelFormatARB(window->hDC, attributeListInt, NULL, 1, pixelFormat, &formatCount);
     if ( result != 1 ) {
          LOG_ERROR("Failed to choose pixel format");
          return NULL;
     }

     // If the video card/display can handle our desired pixel format then we set it as the current one.
     result = SetPixelFormat(window->hDC, pixelFormat[0], &pixelFormatDescriptor);
     if ( result != 1 ) {
          LOG_ERROR("Failed to set pixel format");
          return NULL;
     }

     // Set the 4.0 version of OpenGL in the attribute list.
     attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
     attributeList[1] = 3;
     attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
     attributeList[3] = 2;
     int attribs[] =
     {
          WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
          WGL_CONTEXT_MINOR_VERSION_ARB, 2,
          WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
          WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
          //WGL_SAMPLE_BUFFERS_ARB, 1, // Number of buffers (must be 1 at time of writing)
          //WGL_SAMPLES_ARB, 4,
          0
     };

     attributeList[4] = 0;

     // Create a OpenGL 4.0 rendering context.
     window->hglrc = OpenGL::wglCreateContextAttribsARB(window->hDC, 0, attribs);
     if ( window->hglrc == NULL ) {
          LOG_ERROR("Failed to get rendering context");
          return NULL;
     }

     // Set the rendering context to active.
     result = wglMakeCurrent(window->hDC, window->hglrc);
     if ( result != 1 ) {
          LOG_ERROR("Failed to set rendering context");
          return NULL;
     }

     ShowWindow(window->hWnd, SW_SHOW);
     SetForegroundWindow(window->hWnd);
     SetFocus(window->hWnd);

     return window;
}

void platform_window_update( struct platform_window_t* platform_window )
{
     MSG msg;
     if ( PeekMessage(&msg, platform_window->hWnd, 0, 0, PM_REMOVE) ) {
          if ( msg.message == WM_QUIT ) {
               return;
          }
          else {
               TranslateMessage(&msg);             // Translate The Message
               DispatchMessage(&msg);              // Dispatch The Message
          }
     }

     //platform_window->width = local_width;
     //platform_window->height = local_height;
     platform_window->is_closed = is_closed;
}

void platform_window_swap_buffers( struct platform_window_t* platform_window )
{
     SwapBuffers(platform_window->hDC);
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

