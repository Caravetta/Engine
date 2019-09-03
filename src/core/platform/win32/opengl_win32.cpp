#include "opengl_win32.h"

namespace Engine {
namespace OpenGL {

#define OPENGL_LOAD( func_name, func_define )                                             \
     func_name = (func_define)wglGetProcAddress(#func_name);                              \
     if ( !func_name ) { LOG_ERROR("Failed to load " #func_name); return ENGINE_ERROR; }

PFNWGLCHOOSEPIXELFORMATARBPROC     wglChoosePixelFormatARB       = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC  wglCreateContextAttribsARB    = NULL;
PFNGLSHADERSOURCEPROC              glShaderSource                = NULL;
PFNGLCREATESHADERPROC              glCreateShader                = NULL;
PFNGLCOMPILESHADERPROC             glCompileShader               = NULL;
PFNGLGETSHADERIVPROC               glGetShaderiv                 = NULL;
PFNGLDELETESHADERPROC              glDeleteShader                = NULL;
PFNGLCREATEPROGRAMPROC             glCreateProgram               = NULL;
PFNGLATTACHSHADERPROC              glAttachShader                = NULL;
PFNGLLINKPROGRAMPROC               glLinkProgram                 = NULL;
PFNGLGETPROGRAMIVPROC              glGetProgramiv                = NULL;
PFNGLDELETEPROGRAMPROC             glDeleteProgram               = NULL;
PFNGLGENBUFFERSPROC                glGenBuffers                  = NULL;
PFNGLBINDBUFFERPROC                glBindBuffer                  = NULL;
PFNGLBUFFERDATAPROC                glBufferData                  = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC   glEnableVertexAttribArray     = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC  glDisableVertexAttribArray    = NULL;
PFNGLVERTEXATTRIBPOINTERPROC       glVertexAttribPointer         = NULL;
PFNGLDRAWARRAYSPROC                glDrawArrays                  = NULL;
PFNGLUSEPROGRAMPROC                glUseProgram                  = NULL;
PFNGLGENVERTEXARRAYPROC            glGenVertexArrays             = NULL;
PFNGLBINDVERTEXARRAYPROC           glBindVertexArray             = NULL;
PFNGLUNIFORM1FPROC                 glUniform1f                   = NULL;
PFNGLUNIFORM2FPROC                 glUniform2f                   = NULL;
PFNGLUNIFORM3FPROC                 glUniform3f                   = NULL;
PFNGLUNIFORM4FPROC                 glUniform4f                   = NULL;
PFNGLUNIFORMMATRIX4FVPROC          glUniformMatrix4fv            = NULL;
PFNGLGETUNIFORMLOCATIONPROC        glGetUniformLocation          = NULL;

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
          LOG_ERROR("Failed To Register The Window Class.");
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

     OPENGL_LOAD(glShaderSource, PFNGLSHADERSOURCEPROC);
     OPENGL_LOAD(glCreateShader, PFNGLCREATESHADERPROC);
     OPENGL_LOAD(glCompileShader, PFNGLCOMPILESHADERPROC);
     OPENGL_LOAD(glGetShaderiv, PFNGLGETSHADERIVPROC);
     OPENGL_LOAD(glDeleteShader, PFNGLDELETESHADERPROC);
     OPENGL_LOAD(glCreateProgram, PFNGLCREATEPROGRAMPROC);
     OPENGL_LOAD(glAttachShader, PFNGLATTACHSHADERPROC);
     OPENGL_LOAD(glLinkProgram, PFNGLLINKPROGRAMPROC);
     OPENGL_LOAD(glGetProgramiv, PFNGLGETPROGRAMIVPROC);
     OPENGL_LOAD(glDeleteProgram, PFNGLDELETEPROGRAMPROC);
     OPENGL_LOAD(glGenBuffers, PFNGLGENBUFFERSPROC);
     OPENGL_LOAD(glBindBuffer, PFNGLBINDBUFFERPROC);
     OPENGL_LOAD(glBufferData, PFNGLBUFFERDATAPROC);
     OPENGL_LOAD(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC);
     OPENGL_LOAD(glDisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC);
     OPENGL_LOAD(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC);
     OPENGL_LOAD(glDrawArrays, PFNGLDRAWARRAYSPROC);
     OPENGL_LOAD(glUseProgram, PFNGLUSEPROGRAMPROC);
     OPENGL_LOAD(glGenVertexArrays, PFNGLGENVERTEXARRAYPROC);
     OPENGL_LOAD(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC);
     OPENGL_LOAD(glUniform1f, PFNGLUNIFORM1FPROC);
     OPENGL_LOAD(glUniform2f, PFNGLUNIFORM2FPROC);
     OPENGL_LOAD(glUniform3f, PFNGLUNIFORM3FPROC);
     OPENGL_LOAD(glUniform4f, PFNGLUNIFORM4FPROC);
     OPENGL_LOAD(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC);
     OPENGL_LOAD(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC);

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

