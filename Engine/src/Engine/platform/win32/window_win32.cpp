#include <stdint.h>
#include <string>
#include <windows.h>
#include "window_win32.h"
#include "opengl.h"
#include "input_manager.h"

namespace Engine {

#define DEFAULT_STYLE WS_BORDER | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW

struct platform_window_t {
    int         width;
    int         height;
    int         show;
    HWND        hWnd;
    HINSTANCE   instance;
    HDC         hDC;
    HGLRC       hglrc;
    std::string title;
    bool        is_closed;
};

int local_width;
int local_height;
bool is_closed = false;

void init( struct platform_window_t* window, DWORD dwStyle );

LRESULT CALLBACK _WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch( msg )
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            is_closed = true;
        break;
        case WM_KEYDOWN:
            Input_Manager::get_instance()->process_key_down((uint16_t)wParam);
        break;
        case WM_KEYUP:
            Input_Manager::get_instance()->process_key_up((uint16_t)wParam);
        break;
        case WM_MOUSEMOVE:
            Input_Manager::get_instance()->process_mouse_move(LOWORD(lParam), HIWORD(lParam));
        break;
        case WM_SIZE: {
            local_width = LOWORD(lParam);
            local_height = HIWORD(lParam);
        }
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
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

    platform_window->width = local_width;
    platform_window->height = local_height;
    platform_window->is_closed = is_closed;
}

bool platform_window_is_closed( struct platform_window_t* platform_window )
{
    return platform_window->is_closed;
}

struct platform_window_t* platform_window_create( int width, int height, std::string title )
{
    struct platform_window_t* window = new platform_window_t;
    window->width = width;
    window->height = height;
    local_width = width;
    local_height = height;
    window->title = title;
    window->instance = GetModuleHandle(NULL);

    init(window, DEFAULT_STYLE);

    return window;
}

void init( struct platform_window_t* window, DWORD dwStyle )
{
    WNDCLASSEX wc;
    window->is_closed = false;

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
    wc.lpszClassName = window->title.c_str();
    wc.cbSize = sizeof(WNDCLASSEX);
    //TODO: need to make wc.lpszClassName more robust

    if ( !RegisterClassEx(&wc) ) {
        //TODO: add in logging
        DWORD dw = GetLastError();
        return;
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
                                window->title.c_str(),
                                window->title.c_str(),
                                dwStyle,
                                screen_pos_x,
                                screen_pos_y,
                                screenWidth,
                                screenHeight,
                                parent_hwnd, NULL,
                                window->instance,
                                NULL);

    if ( window->hWnd == NULL ) {
        return;
    }

    init_opengl(&window->hDC, &window->hWnd, &window->hglrc);

    ShowWindow(window->hWnd, SW_SHOW);
    SetForegroundWindow(window->hWnd);
    SetFocus(window->hWnd);
}

void platform_window_swap_buffers( struct platform_window_t* platform_window )
{
    SwapBuffers(platform_window->hDC);
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
