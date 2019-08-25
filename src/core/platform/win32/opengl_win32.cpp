#include "opengl_win32.h"

namespace Engine {
namespace OpenGL {

PFNWGLCHOOSEPIXELFORMATARBPROC     wglChoosePixelFormatARB       = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC  wglCreateContextAttribsARB    = NULL;

#define OPENGL_LOAD( func_name, func_define ) \
     func_name = (func_define)wglGetProcAddress(#func_name); \
     if ( !func_name ) { LOG_ERROR("Failed to load " #func_name); return ENGINE_ERROR; }

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

Rc_t init_opengl( void )
{
     WNDCLASSEX _wc;
     HINSTANCE instance = GetModuleHandle(NULL);
     HWND hWnd;

     _wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
     _wc.lpfnWndProc = (WNDPROC)_TempWndProc;
     _wc.cbClsExtra = 0;
     _wc.cbWndExtra = 0;
     _wc.hInstance = instance;
     _wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
     _wc.hIconSm = _wc.hIcon;
     _wc.hCursor = LoadCursor(NULL, IDC_ARROW);
     _wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
     _wc.lpszMenuName = NULL;
     _wc.lpszClassName = "TempOpenGL";
     _wc.cbSize = sizeof(WNDCLASSEX);

     if ( !RegisterClassEx(&_wc) ) {
          LOG_ERROR("Failed To Register The Window Classawdawdawd.");
          DWORD dw = GetLastError();
          UNUSED_ARG(dw);
          return ENGINE_ERROR;
     }

     hWnd = CreateWindowEx(WS_EX_APPWINDOW,
                           "TempOpenGL",
                           "TempOpenGL",
                           WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
                           0,
                           0,
                           640,
                           480,
                           NULL,
                           NULL,
                           instance,
                           NULL);

     if ( hWnd == NULL ) {
          LOG_ERROR("Failed to create temp window");
          return ENGINE_ERROR;
     }

     ShowWindow(hWnd, SW_HIDE);

     HDC deviceContext;
     PIXELFORMATDESCRIPTOR _pixelFormat;
     int error;
     HGLRC renderContext;

     deviceContext = GetDC(hWnd);
     if ( !deviceContext ) {
          LOG_ERROR("Failed to get device context");
          return ENGINE_ERROR;
     }

     // Set a temporary default pixel format.
     error = SetPixelFormat(deviceContext, 1, &_pixelFormat);
     if ( error != 1 ) {
          LOG_ERROR("Failed to set pixel format");
          return ENGINE_ERROR;
     }

     // Create a temporary rendering context.
     renderContext = wglCreateContext(deviceContext);
     if ( !renderContext ) {
          LOG_ERROR("Failed to create context");
          return ENGINE_ERROR;
     }

     // Set the temporary rendering context as the current rendering context for this window.
     error = wglMakeCurrent(deviceContext, renderContext);
     if ( error != 1 ) {
          LOG_ERROR("Failed to make context current");
          return ENGINE_ERROR;
     }

     wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
     if ( !wglCreateContextAttribsARB ) { LOG_ERROR("Failed to load wglCreateContextAttribsARB"); return ENGINE_ERROR; }

     wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
     if ( !wglChoosePixelFormatARB ) { LOG_ERROR("Failed to load wglChoosePixelFormatARB"); return ENGINE_ERROR; }

     OPENGL_LOAD(glGenVertexArrays, glGenVertexArraysProc);

     // Release the temporary rendering context now that the extensions have been loaded.
     wglMakeCurrent(NULL, NULL);
     wglDeleteContext(renderContext);
     renderContext = NULL;

     // Release the device context for this window.
     ReleaseDC(hWnd, deviceContext);
     deviceContext = 0;
     MSG msg;
     if ( PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE) ) {
          TranslateMessage(&msg);             // Translate The Message
          DispatchMessage(&msg);              // Dispatch The Message
     }
     DestroyWindow(hWnd);

     return SUCCESS;
}

} // end namespace OpenGL
} // end namespace Engine

