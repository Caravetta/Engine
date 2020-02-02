#include <windows.h>
#include <vector>
#include <windowsx.h>
#include "window_win32.h"
#include "platform_graphics.h"
#include "input_win32.h"

namespace Engine {

struct platform_window_t {
     int       width;
     int       height;
     bool      is_closed;
     HWND      hWnd;
     HINSTANCE instance;
     HDC       hDC;
     HGLRC     hglrc;
     //std::vector<key_event_cb> key_callbacks;
     std::vector<mouse_position_cb> mouse_pos_callbacks;
     std::vector<mouse_button_cb> mouse_button_callbacks;
     std::vector<resize_cb> resize_callbacks;
};

bool is_closed = false;
platform_window_t* cur_window = NULL;

LRESULT CALLBACK _WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
     switch( msg )
     {
          case WM_CLOSE:
               DestroyWindow(hwnd);
               is_closed = true;
          break;
          case WM_KEYDOWN:
               platform_key_event(wParam, true);
          break;
          case WM_KEYUP:
               platform_key_event(wParam, false);
          break;
          case WM_MOUSEMOVE: {
               int mx = GET_X_LPARAM(lParam);
               int my = GET_Y_LPARAM(lParam);

               platform_mouse_move_event((float)mx, (float)my);

               for ( size_t ii = 0; ii < cur_window->mouse_pos_callbacks.size(); ii++) {
                    cur_window->mouse_pos_callbacks[ii](mx, my);
               }
          } break;
          case WM_LBUTTONDOWN:
               for ( size_t ii = 0; ii < cur_window->mouse_button_callbacks.size(); ii++) {
                    cur_window->mouse_button_callbacks[ii](1, true);
               }
          break;
          case WM_LBUTTONUP:
               for ( size_t ii = 0; ii < cur_window->mouse_button_callbacks.size(); ii++) {
                    cur_window->mouse_button_callbacks[ii](1, false);
               }
          break;
          case WM_SIZE: {
               int mx = GET_X_LPARAM(lParam);
               int my = GET_Y_LPARAM(lParam);

               if ( cur_window != NULL ) {
                    for ( size_t ii = 0; ii < cur_window->resize_callbacks.size(); ii ++ ) {
                         cur_window->resize_callbacks[ii]((int32_t)mx, (int32_t)my);
                    }

                    cur_window->width = mx;
                    cur_window->height = my;
               }
          } break;
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
          window->width -= 16;
          window->height -= 39;
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

     Rc_t rc = create_render_context(window);
     if ( rc != SUCCESS ) {
          return NULL;
     }

     ShowWindow(window->hWnd, SW_SHOW);
     SetForegroundWindow(window->hWnd);
     SetFocus(window->hWnd);

     cur_window = window;

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

     platform_window->is_closed = is_closed;
}

void platform_window_swap_buffers( struct platform_window_t* platform_window )
{
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

#if 0
int platform_window_add_key_event_cb( struct platform_window_t* platform_window, key_event_cb callback )
{
     platform_window->key_callbacks.push_back(callback);
     return 0;
}
#endif

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

